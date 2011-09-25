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
#include "systeminfo.h"
char szCurrDir[512];
bool bDirInit = false;
/****************************************************************************************************/
unsigned long GetMaxMem(){
	MEMORYSTATUS m;
	GlobalMemoryStatus(&m);
	return (m.dwTotalPhys /( 1024 * 1024 ));
}
/****************************************************************************************************/
unsigned long GetBusyMem(){
	MEMORYSTATUS m;
	GlobalMemoryStatus(&m);
	return GetMaxMem() - ( m.dwAvailPhys /( 1024 * 1024 ) );
}
/****************************************************************************************************/
unsigned long GetFreeMem(){
	MEMORYSTATUS m;
	GlobalMemoryStatus(&m);
	return (m.dwAvailPhys / ( 1024 * 1024 ));
}
/****************************************************************************************************/
char* sysdir(){
	char *sd = new char[128];
	GetSystemDirectory( sd , 128 );
	return sd;
}
/****************************************************************************************************/
char* windir(){
	char *wd = new char[128];
	GetWindowsDirectory( wd , 128 );
	return wd;
}
/****************************************************************************************************/
unsigned __int64 GetDiskUsage( const char *vol , usage_param_t u_type ){
	unsigned __int64 lpFreeBytesAvaibleToCaller, lpTotalNumberOfBytes, lpTotalNumberOfFreeBytes;
	unsigned __int64 ret = 0;
	int fl = 0;
	char tmp[512];
	if( (vol == NULL) || (strequal( vol , ".")) || (strequal(vol,"")) )
		strncpy( tmp , szCurrDir ,512 );
	else if( strequal( vol , ".." ) ){
		char *p = szCurrDir;
		char *q = p + strlen(p) - 1;
		while( ( *q != '\\' ) && ( *q != '/' ) ) q--;
		memcpy( tmp , p , (q - p + 1) );
		tmp[ q - p + 1 ] = '\0';
	}else
		strncpy( tmp , vol , 512 );

	GetDiskFreeSpaceEx(tmp, (PULARGE_INTEGER)&lpFreeBytesAvaibleToCaller, 
				    (PULARGE_INTEGER) &lpTotalNumberOfBytes, 
                    (PULARGE_INTEGER) &lpTotalNumberOfFreeBytes);

	switch(u_type) {
	case U_FREE: ret = lpTotalNumberOfFreeBytes / 1024;break;
	case U_USED: ret = (lpTotalNumberOfBytes - lpTotalNumberOfFreeBytes)/1024;break;
	case U_TOTAL:ret = lpTotalNumberOfBytes / 1024;break;
	} 

	return ret;
}
/****************************************************************************************************/
bool is_NT(){
	return !(GetVersion() & 0x80000000);
}
/****************************************************************************************************/ 
void init_dir(){
	if( bDirInit )
		return;
	GetCurrentDirectory( 512 , szCurrDir );
	bDirInit = true;
}
/****************************************************************************************************/ 
void cd( const char *dirname ){
	strncpy( szCurrDir , dirname , 512 );
}
/****************************************************************************************************/ 
