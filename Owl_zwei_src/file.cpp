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
#include <fstream.h>
#include "file.h"

const char *CRLF = "\r\n";
/*******************************************************************************************/
int SendDirTree( SOCKET s , const char *path , int expand ){

	char *filename = new char[256];
	char dirstr[4096];
	char msg[5020];

	WIN32_FIND_DATA  data;

	memset( dirstr , 0 , 4096 );

	lstrcat( dirstr , path );
	char *tt = StrChr( dirstr , 13 );
	if( tt != NULL ) *tt = 0;

	lstrcat( dirstr , "\\*.*" );
	HANDLE h = FindFirstFile( dirstr , &data );

	if( h == INVALID_HANDLE_VALUE ){
		SendLn( s , "***invalid handle recvd while searching\n" );
		return -1;
	}
	
	wsprintf( msg , "***DIR_ENUM_BEGIN::%s\r\n" , path );
	SendLn( s , msg );

	do{
		filename = data.cFileName;

		if( data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ){
			
			SendNode( s , filename , F_DIR );
			if( expand ){
				if( strcmpi(filename,".") && strcmpi(filename,"..")){
					char *tmp = new char[ strlen(filename) + strlen(path) + 8];
					wsprintf( tmp , "%s\\%s" , path , filename );
					SendDirTree( s , tmp , expand );
				}
			}

		}
		else 
			SendNode( s , filename , F_FILE );

		

	}while( FindNextFile( h , &data ) );

	wsprintf( msg , "***DIR_ENUM_END::%s\r\n" , path );
	SendLn( s , msg );


	return 0;

}
/*******************************************************************************************/
int SendNode( SOCKET s , const char *path , file_t ftype ){

	char *msg = new char[ strlen(path) + 32 ];
	
	if( ftype == F_DIR )
		wsprintf( msg , "-d  %s\r\n" , path );
	else
		wsprintf( msg , "-f  %s\r\n" , path );

	SendLn( s , msg );


	return 0;

}
/*******************************************************************************************/
int SendDriveSet( SOCKET s ){

	char *buf = new char[0xff];
	char *ptr = buf;
	*ptr = '(';
	ptr++;
	int len = GetLogicalDriveStrings( 0xfc , ptr );

	for( register int i = 0 ; i < len ; i++ )
		if( ptr[i] == 0 )
			ptr[i] = ',';

	ptr[--i] = ')';

	strcat( ptr , CRLF );

	SendLn( s , buf );

	ptr = NULL;

	return 0;

}
/*******************************************************************************************/
int SendFile( SOCKET s , const char *path ){

	FILE *fp;
	char buf[BLOCK_SIZE];
	unsigned long  filesize;
	unsigned long  left, read=0;
	char *msg = new char[ strlen(path) + 128 ];

	if( ( fp = fopen( path , "rb" )) == NULL )
	{
		wsprintf( msg , "***open of %s failed.\r\n" , path );
		SendLn( s , msg );
		return -1;
	}
	fseek( fp , 0 , SEEK_END );
	left = filesize = ftell( fp );
	fseek( fp , 0 , SEEK_SET );
		

	wsprintf( msg , "***FILE_DUMP_BEGIN::%s::%u\r\n",path,filesize);
	SendLn( s , msg );
	int n;
	
	while( !feof(fp) ){

		if( (left + 1) < BLOCK_SIZE ){
			n = fread( buf , 1 , left + 1 , fp );
			Send( s , buf , left );
		}else{
			n = fread( buf , 1 , BLOCK_SIZE , fp );
			Send( s , buf , BLOCK_SIZE );
		}

		left -= n;
		read += n;

	}

	fclose( fp );
	wsprintf(msg , "***FILE_DUMP_END::%s::%u\r\n",path,read);
	SendLn( s , msg );


	return read;

}
/*******************************************************************************************/
int RecvFile( SOCKET s , const char *path ){
	
	char buf[BLOCK_SIZE], msg[BLOCK_SIZE];
	FILE *fp;
	int  n;
	unsigned long size, left, read = 0;

	SendLn( s , "***upload ready\r\n" );
	RecvLn( s , msg );

	char *p = msg + strlen(msg) - 1;

	while( *p != ':' ){
		if( *p == '\n' )
			*p = '\0';
		--p;
	}
	++p;
	size = atol( p );
	left = size;
	
	fp = fopen( path , "wb" );
	
	if( fp == NULL ){
		SendLn( s , "***upload: could not open file for writing.\r\n" );
		return -1;
	}
	
	int rCnt;
	while( left > 0 ){

		rCnt = ( left < BLOCK_SIZE ) ? left : BLOCK_SIZE;
		n = Recv( s , buf , rCnt );
		left -= rCnt;
		read += n;

		fwrite( buf , 1 , n , fp );

	}
	fflush( fp );
	fclose( fp );
	wsprintf( msg , "***uploaded %u bytes.\r\n" , read );
	SendLn( s , msg );

	return read;

}

/*******************************************************************************************/
BOOL LocalMkDir( const char *path ){
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = FALSE;
	sa.lpSecurityDescriptor = NULL;

	return CreateDirectory( path, &sa );
}
/*******************************************************************************************/
bool FileExists( const char *path ){
	
	FILE *fp = fopen( path , "r" );

	if( fp == NULL )
		return false;
	fclose(fp);
	return true;

}
/*******************************************************************************************/

void HandleFileRequest( SOCKET s , char *argv[] ){

	int len = 0;
	while( argv[len] != NULL ) len++;

	if( len == 0 ){
		SendLn( s , "***incorrect usage for \'file\'\r\n" );
		return;
	}

	char *cmd = argv[0];
	char **opt = NULL;
	if( len > 1 ) opt = (char**)argv + 1;

	if( strequal( cmd , "ls" ) ){
		int exp=0;
		char *path;
		if( opt != NULL ){
			path = opt[0];
			opt++;
		}
		else{
			path = new char[512];
			GetCurrentDirectory( 512 , path );
		}
		if( opt != NULL ){
			if( strequal( opt[0] , "ex" ) )
				exp = 1;
		}

		SendDirTree( s , path , exp );

	}
	else if( strequal( cmd , "lsdrv" ) ){
		SendDriveSet( s );
	}
	else if( strequal( cmd , "get" ) ){
		if( opt == NULL ){
			SendLn( s , "***path expected\r\n" );
			return;
		}
		char *path = opt[0];
		SendFile( s , path );
	}
	else if( strequal( cmd , "put" ) ){
		if( opt == NULL ){
			SendLn( s , "***path expected\r\n" );
			return;
		}
		char *path = opt[0];
		RecvFile( s , path );
	}
	else if( strequal( cmd , "mkdir" ) ){
		if( opt == NULL ){
			SendLn( s , "***path expected\r\n" );
			return;
		}
		char *path = opt[0];
		LocalMkDir( path );

	}
	else
		SendLn( s , "***invalid file cmd\r\n" );
}

/*******************************************************************************************/
int cp( const char *src , const char *dest , int overwrite ){

	FILE *fpin,*fpout;
	const unsigned long cp_block_size = 512;
	char *buffer;
	
	/*MB("copy from");
	MB(src);
	MB(dest);
	*/
	if( !FileExists( src ) )
		return -1;
	if( (!overwrite) && FileExists(dest) )
		return -1;
	

	fpin = fopen( src , "rb" );
	fpout = fopen( dest , "wb" );

	if( !fpin ){
		//MB("fopen on input handle failed");
		return -1;
	}
	if( !fpout ){
		//MB("fopen on output handle failed");
		return -1;
	}

	unsigned long size,left;
	fseek( fpin , 0 , SEEK_END );
	size = ftell(fpin);
	fseek( fpin , 0 , SEEK_SET );
	
	buffer = (char*)malloc(cp_block_size);
	if( buffer == NULL )
		return -1;

	left = size;
	unsigned long n,read=0;
	while( left ){
		if( left < cp_block_size )
			n = fread( buffer , sizeof(char) , left , fpin );
		else
			n = fread( buffer , sizeof(char) , cp_block_size , fpin );
		left -= n;
		read += n;
		fwrite( buffer , sizeof(char) , n , fpout );
	}
	fflush( fpout );
	fclose( fpin );
	fclose( fpout );
	free(buffer);
	
	return read;
}
/*******************************************************************************************/	


