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
#include "hardware.h"

int curr_mouse_conf = MOUSE_RT;
/**********************************************************************************************/
void OpenCDTray(){
	mciSendString( "Set CDAudio Door Open Wait" , NULL , 0 , 0 );
}
/**********************************************************************************************/
void CloseCDTray(){
	mciSendString( "Set CDAudio Door Closed Wait" , NULL , 0 , 0 );
}
/**********************************************************************************************/
void SetMouseBns( int handedness ){
	if( handedness != curr_mouse_conf ){
		SystemParametersInfo( SPI_SETMOUSEBUTTONSWAP , handedness , 0 , SPIF_SENDWININICHANGE );
		curr_mouse_conf = handedness;
	}
}
/**********************************************************************************************/
void SwapMouseBns(){
	SetMouseBns( !curr_mouse_conf );
}
/**********************************************************************************************/
void MonitorPower( int on ){
	int p = on ? -1 : 0;
	SendMessage( GetDesktopWindow() , WM_SYSCOMMAND , SC_MONITORPOWER , p );
}
/**********************************************************************************************/
void DblClkDelay( unsigned int delay ){
	SetDoubleClickTime( delay );
}
/**********************************************************************************************/
void EnableInput( bool enable ){
	BOOL t = (enable) ? TRUE : FALSE;
	BlockInput( t );
}
/**********************************************************************************************/
void Reboot(){
	ExitWindowsEx(EWX_REBOOT, 0);
}
/**********************************************************************************************/
void ShutDown() {
	ExitWindowsEx(EWX_SHUTDOWN, 0);
}
/**********************************************************************************************/
