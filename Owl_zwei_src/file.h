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
#ifndef __OWL_FILE_H__
#define __OWL_FILE_H__

#include "network.h"
#include "misc.h"


#define BLOCK_SIZE	1024

enum file_t{ F_DIR = 0 , F_FILE };
extern const char *CRLF;

//----------------------------------------------------------------
int  SendDirTree( SOCKET s , const char *dirPath , int expand );
//----------------------------------------------------------------
int  SendNode( SOCKET s , const char *fileName , enum file_t ftype );
//----------------------------------------------------------------
int  SendDriveSet( SOCKET s );
//----------------------------------------------------------------
BOOL  LocalMkDir( const char *path );
//----------------------------------------------------------------
bool FileExists( const char *path );
//----------------------------------------------------------------
int  SendFile( SOCKET s , const char *path );
//----------------------------------------------------------------
int  RecvFile( SOCKET s , const char *path );
//----------------------------------------------------------------
//BOOL LocalRmDir( const char *path );
//----------------------------------------------------------------
void HandleFileRequest( SOCKET s , char *argv[] );
//----------------------------------------------------------------
int cp( const char *src , const char *dest , int overwrite );
//----------------------------------------------------------------

#endif
