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
/*HUGE thanks to http://www.catch22.net/tuts/selfdel.asp for the concept!!*/

#include "selfdelete.h"
/*******************************************************************************************/
BOOL check_for_deinstall( const char *argstr ){
	char *arr[0xa];
	int i;
	if( !lstrcmp( argstr , "" ) || argstr == NULL )
		return FALSE;
	c_split( "::" , argstr , (char**)arr );
	for( i = 0 ; arr[i] ; i++ );
	if( i != 2 )
		return FALSE;
	return TRUE;
}
/*******************************************************************************************/
void DoUninstall( const char *argstr ){
	char *arr[0xa];
	char *exepath;
	DWORD pid;
	if( !lstrcmp( argstr , "" ) || argstr == NULL )
		return;
	c_split( "::" , argstr , (char**)arr );

	exepath = arr[0];
	pid = (DWORD)atol(arr[1]);
	DeleteMaster( exepath , pid );
}
/*******************************************************************************************/
void DeleteMaster( const char *exe , DWORD pid ){
	unsigned long err;
	HANDLE hProcess;
	char str[128];
	hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | SYNCHRONIZE , FALSE , pid );
	if( hProcess ){	
		WaitForSingleObject( hProcess , INFINITE );
		CloseHandle( hProcess );
	}
	DeleteFile( exe );
}
/*******************************************************************************************/
void SelfDelete(void){
	HANDLE hTemp;
	char   szPath[MAX_PATH];
	char   szTemp[MAX_PATH];
	char   argstr[2*MAX_PATH + 0x20];
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	unsigned ret;

	GetTempPath( MAX_PATH , szTemp );
	lstrcat( szTemp , "selfdel.exe" );
	
	GetModuleFileName( NULL , szPath , MAX_PATH );

	CopyFile( szPath , szTemp , FALSE );

	hTemp = CreateFile( szTemp , GENERIC_READ , FILE_SHARE_READ|FILE_SHARE_DELETE , 0 ,
						OPEN_EXISTING , FILE_FLAG_DELETE_ON_CLOSE , 0 );
	memset( &pi , 0 , sizeof(PROCESS_INFORMATION) );
	memset( &si , 0 , sizeof(STARTUPINFO) );

	si.cb = sizeof(STARTUPINFO);
	wsprintf( argstr , "\"%s\" %s::%u" , szTemp , szPath , GetCurrentProcessId() );

	ret = CreateProcess( 0, argstr, 0, 0, FALSE, NORMAL_PRIORITY_CLASS, 0, 0, &si, &pi );

	Sleep( 200 );
	CloseHandle( hTemp );
}
/*******************************************************************************************/
char** c_split( const char *delim , const char *str , char **result ){

	int dlen = strlen(delim);
	int i = 0,j;
	char *p = (char*)str;
	char *q;

	while( ( q = strstr( p , delim )) != NULL ){
		if( q == p ){
			result[i++] = "";
			p += dlen;
			continue;
		}
		result[i] = (char*)malloc( sizeof(char)*(q - p + 1) );
		j = 0;
		while( p != q ){
			result[i][j++] = *p++;
		}
		result[i][j] = '\0';
		p += dlen;
		i++;
	}
	result[i] = (char*)malloc(strlen(p) + 1);
	strcpy(result[i],p);
	result[++i] = NULL;
	return result;
}
/*******************************************************************************************/

