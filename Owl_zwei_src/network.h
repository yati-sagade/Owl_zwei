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
#ifndef __OWL_NETWORK_H__
#define __OWL_NETWORK_H__

#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <wininet.h>


#define LISTENQ	1024
extern  unsigned int max_listen_queue;
extern  bool         netinited;
extern  unsigned short owl_port;
//------------------------------------------------------------------------------------------
#define WSOCKLO	2
#define WSOCKHI	2
//------------------------------------------------------------------------------------------
#define ERR		-1
#define ESOCK	-2
#define ECONN	-3
#define EBIND	-4
#define ELISN	-5
#define ERECV	-6
#define ESEND	-7
#define EHOST	-8
//------------------------------------------------------------------------------------------
#define MAX_BUF_SIZE	1024
//------------------------------------------------------------------------------------------
#define OWL_PORT		4000
//------------------------------------------------------------------------------------------

SOCKET start_server( unsigned short port );
//------------------------------------------------------------------------------------------
SOCKET connect_to( const char *host , unsigned short port );
//------------------------------------------------------------------------------------------
SOCKET accept_connection( SOCKET listenfd , struct sockaddr *client , size_t *client_len );
//------------------------------------------------------------------------------------------
int    Recv( SOCKET connfd , void *buf , size_t size );
//------------------------------------------------------------------------------------------
int    RecvLn( SOCKET connfd , char *buf );
//------------------------------------------------------------------------------------------
int    Send( SOCKET connfd , const void *buf , size_t size );
//------------------------------------------------------------------------------------------
int    SendLn( SOCKET connfd , const char *buf );
//------------------------------------------------------------------------------------------
int    SendFile( SOCKET connfd , const char *file_path );
//------------------------------------------------------------------------------------------
bool IsConnectedToNet(void);
//------------------------------------------------------------------------------------------
#endif

