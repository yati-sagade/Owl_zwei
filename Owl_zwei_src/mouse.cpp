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
#include "mouse.h"

bool bCtrlFlyMousePtr = false;
unsigned int uiFlyMouseDelay = 100;
int nCtrlClick = 0;
/***************************************************************************************/
void FlyMousePtr( bool start ){
	
	bCtrlFlyMousePtr = false;
	bCtrlFlyMousePtr = start;
	nCtrlClick = 0;
	
	if( start )
		new_thread( flyMouseProc , &nCtrlClick );

}
/***************************************************************************************/
void FlyMousePtrClick( bool start ){
	
	bCtrlFlyMousePtr = false;
	bCtrlFlyMousePtr = start;
	nCtrlClick = 1;
	
	if( start )
		new_thread( flyMouseProc , &nCtrlClick );

}
/***************************************************************************************/
DWORD WINAPI flyMouseProc( LPVOID ptr ){
	
	int click = *(int*)ptr;
	int sw = GetSystemMetrics( SM_CYSCREEN );
	int sh = GetSystemMetrics( SM_CXSCREEN );
	HWND hPt;

	while( bCtrlFlyMousePtr ){
	
		POINT p = { rand() % sw , rand() % sh };
		SetCursorPos( p.x , p.y );
		Sleep( uiFlyMouseDelay );
		
		if( click ){
			hPt = WindowFromPoint( p );
			SendMessage( hPt , WM_LBUTTONDOWN , MK_LBUTTON , MAKELONG( p.x , p.y ) );
		}

		POINT q = { rand() % sw , rand() % sh };
		SetCursorPos( q.x , q.y );

		if( click ){
			SendMessage( hPt , WM_MOUSEMOVE , 0 , MAKELONG( q.x , q.y ) );
			SendMessage( hPt , WM_LBUTTONUP , 0 , MAKELONG( q.x , q.y ) );
		}
	}
	return 0;

}
/***************************************************************************************/
void RestrictMouseMovementTo( int left , int top , int right , int bottom ){
	
	RECT r;

	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;

	ClipCursor( &r );

}
/***************************************************************************************/
void ShowMouseCursor( bool show ){

	ShowCursor( show ? TRUE : FALSE );

}
/***************************************************************************************/
void MouseClick(unsigned int button) {
	
	switch(button) {

	case MOUSEBN_LT:
		mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL); 
		mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL); 
    break; 

    case MOUSEBN_CT: 
		mouse_event(MOUSEEVENTF_MIDDLEDOWN, NULL, NULL, NULL, NULL); 
		mouse_event(MOUSEEVENTF_MIDDLEUP, NULL, NULL, NULL, NULL); 
    break; 

    case MOUSEBN_RT: 
		mouse_event(MOUSEEVENTF_RIGHTDOWN, NULL, NULL, NULL, NULL); 
		mouse_event(MOUSEEVENTF_RIGHTUP, NULL, NULL, NULL, NULL); 
    break;

	}

}
/***************************************************************************************/
void MouseClickPoint( unsigned int x,unsigned int y, unsigned int button) {
	
	switch(button) {

	case MOUSEBN_LT:
		mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, NULL, NULL); 
		mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL); 
    break; 

    case MOUSEBN_CT: 
		mouse_event(MOUSEEVENTF_MIDDLEDOWN, x, y, NULL, NULL); 
		mouse_event(MOUSEEVENTF_MIDDLEUP, x, y, NULL, NULL); 
    break; 

    case MOUSEBN_RT: 
		mouse_event(MOUSEEVENTF_RIGHTDOWN, x, y, NULL, NULL); 
		mouse_event(MOUSEEVENTF_RIGHTUP, x, y, NULL, NULL); 
    break;

	}

}
/***************************************************************************************/
void SetMousePos( unsigned int x , unsigned int y ){

	SetCursorPos( x , y );

}
/***************************************************************************************/
