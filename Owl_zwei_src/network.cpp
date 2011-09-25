/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *   Owl Zwei - Remote Administration Toolkit For Windows                    *
 *                                                                           * 
 *   Copyright 2010 Yati Sagade                                              *
 *                                                                           *
 *   This file is part of Owl Zwei.                                          *
 *                                                                           *
 *   Owl Zwei is free software: you can redistribute it and/or modify        *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation, either version 3 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   Owl Zwei is distributed in the hope that it will be useful,             *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with Owl Zwei.  If not, see <http://www.gnu.org/licenses/>.       *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "network.h"

unsigned int   max_listen_queue = LISTENQ;
bool		   netinited        = false;
unsigned short owl_port         = OWL_PORT;

#pragma comment(lib,"Wininet.lib")

/*******************************************************************************************************/
void owl_network_init(){
	WSAData wsaData;
	WORD    wVer;
	wVer = MAKEWORD( WSOCKLO , WSOCKHI );
	if( WSAStartup( wVer , &wsaData ) )
		return;
	netinited = true;
}
/*******************************************************************************************************/
SOCKET start_server( unsigned short port ){

   SOCKET listenfd;
   struct sockaddr_in serv;
   int n;

   if( !netinited ) owl_network_init();

   if( (listenfd = WSASocket( AF_INET , SOCK_STREAM , IPPROTO_TCP , NULL , 0 ,0 )) == INVALID_SOCKET )
      return ESOCK;
   
   memset( &serv , 0 , sizeof(serv) );
   
   serv.sin_family      = AF_INET;
   serv.sin_port        = htons( port );
   serv.sin_addr.s_addr = htonl( INADDR_ANY );   
   
   n = bind( listenfd , (struct sockaddr*)(&serv) , sizeof(serv) );
   
   if( n == SOCKET_ERROR )
      return EBIND;
   
   n = listen( listenfd , max_listen_queue );
   
   if( n == SOCKET_ERROR )
      return ELISN;

   return listenfd;

}
/*******************************************************************************************************/
SOCKET connect_to( const char *host , unsigned short port ){

	if( !netinited ) owl_network_init();

	SOCKET connfd;
	struct sockaddr_in serv;
	struct hostent *h = NULL;

	if( (connfd = WSASocket( AF_INET , SOCK_STREAM , IPPROTO_TCP , NULL , 0 ,0 )) == INVALID_SOCKET )
       return ESOCK;

	memset( &serv , 0 , sizeof(serv) );
   
    serv.sin_family = AF_INET;
    serv.sin_port   = htons( port );
    serv.sin_addr.s_addr = htonl( inet_addr( host ) );

	if( serv.sin_addr.s_addr == INADDR_NONE ){
		h = gethostbyname( host );
		if( host == NULL ){
			closesocket( connfd );
			return EHOST;
		}
		memcpy( &serv.sin_addr , h->h_addr_list[0] , h->h_length );
	}
		
   
    int n = WSAConnect( connfd , (struct sockaddr*)(&serv) , sizeof(serv) , NULL , NULL , NULL , NULL );
    
	if( n == SOCKET_ERROR )
       return ECONN;
   
	return connfd;

}
/*******************************************************************************************************/
SOCKET accept_connection( SOCKET listenfd , struct sockaddr *client , size_t *clilen ){

	SOCKET connfd = WSAAccept( listenfd , client , (int*)clilen , NULL , 0 );
	return connfd;

}
/*******************************************************************************************************/
int Recv( SOCKET sockfd , void *__buf , size_t __len ){

    int left = __len;
    int read = 0;
    int n;

    if( (sockfd < 0)  || ( __buf == NULL) || ( __len <= 0 ) )
       return -1;

    while( left )
	{
       n = recv( sockfd , (char*)(__buf) , left , 0 );
       if( !n )
          break;
       read += n;
       left -= n;
    }
   
    return read;
}
/*******************************************************************************************************/
int RecvLn( SOCKET connfd , char *buf ){
    char *ptr = buf;
    int n;
    while( 1 )
	{
       n = recv( connfd , ptr , sizeof(char) , 0 );
       if( !n )
          break;
	   if( *ptr == 13 )
		  break;
       ++ptr;
      
    }
    *ptr = '\0';
    return ( ptr - buf );
}
/*******************************************************************************************************/
int Send( SOCKET connfd , const void *buf , size_t size ){

	const char *ptr = ( const char * )buf;
	return send( connfd , ptr , size , 0 );

}
/*******************************************************************************************************/
int SendLn( SOCKET connfd , const char *buf ){
	
	return send( connfd , buf , strlen(buf) , 0 );

}
/*******************************************************************************************************/
bool IsConnectedToNet(void){
	DWORD flags;
	InternetGetConnectedState( &flags, 0 );
	char *dummy_site = "www.microsoft.com";
	/*if( (flags & INTERNET_CONNECTION_LAN)||(flags & INTERNET_CONNECTION_MODEM)||(flags & INTERNET_CONNECTION_PROXY) ){
		SOCKET s = connect_to( dummy_site, 80 );
		if( s >= 0 ){
			closesocket(s);
			return true;
		}
	}*/
	if( gethostbyname(dummy_site) != NULL )
		return true;


	return false;
}
/*******************************************************************************************************/



