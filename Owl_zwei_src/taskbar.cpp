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
#include "taskbar.h"

HWND hStartBn;
HWND hTaskBar;
bool bCtrlFlyStart = false;
bool bTBInited = false;
/************************************************************************************/
void TBInit(){
	hTaskBar = FindWindow( "Shell_TrayWnd" , NULL );
	hStartBn = FindWindowEx( hTaskBar , 0 , "Button" , NULL );
	bTBInited = true;
}
/************************************************************************************/
void ShowTaskBar( bool show ){
	BOOL t = show ? SW_SHOW : SW_HIDE;
	if( !bTBInited ) TBInit();
	ShowWindow( hTaskBar , t );
}
/************************************************************************************/
void ShowStartBn( bool show ){
	BOOL t = show ? SW_SHOW : SW_HIDE;
	if( !bTBInited ) TBInit();
	ShowWindow( hStartBn , t );
}
/************************************************************************************/
void FlyStartBn( bool start ){
	if( !bTBInited ) TBInit();
	bCtrlFlyStart = start;
	if( start )
		new_thread( flyStartProc , NULL );
}
/************************************************************************************/
DWORD WINAPI flyStartProc( LPVOID ptr ){
	SetParent( hStartBn , 0 );
	int i;
	HANDLE h;

	int top = GetSystemMetrics( SM_CYSCREEN ) - 23;

	SetWindowPos( hStartBn , HWND_TOPMOST , 4 , top,
					50 , 20 , SWP_SHOWWINDOW );
	UpdateWindow( hStartBn );

	h = CreateEvent( NULL , TRUE , FALSE , "delay_fly" );
	while( bCtrlFlyStart ){
		for( i = 0 ; i < 50 ; i++ ){
			top -= 4;
			
			SetWindowPos( hStartBn , HWND_TOPMOST , 4 ,
					           top , 50 , 20 , SWP_SHOWWINDOW );
		
			WaitForSingleObject( h , 15 );
		}
		for( ; i > 0; i-- ){
			top += 4;
			SetWindowPos( hStartBn , HWND_TOPMOST , 4 ,
				               top , 50 , 20 , SWP_SHOWWINDOW );
			WaitForSingleObject( h , 15 );
		}
	}
	SetParent( hStartBn , hTaskBar );
	return 0;
}
/************************************************************************************/
void ShowClock( bool show ){

	if( !bTBInited ) TBInit();
	HWND hWnd = FindWindowEx( hTaskBar , 0 , "TrayNotifyWnd" , NULL );
	hWnd = FindWindowEx( hWnd , 0 , "TrayClockWClass" , NULL );
	ShowWindow( hWnd , ( show ? SW_SHOW : SW_HIDE ) );
	
}
/************************************************************************************/
void EnableTaskBar( bool enable ){
	
	if( !bTBInited ) TBInit();
	EnableWindow( hTaskBar , (enable ? TRUE : FALSE) );

}
/************************************************************************************/


	
