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
#ifndef __OWL_TASKBAR_H__
#define __OWL_TASKBAR_H__

#include <windows.h>
#include "misc.h"

extern HWND hStartBn;
extern HWND hTaskBar;
extern bool bTBInited;
extern bool bCtrlFlyStart;

//--------------------------------------
void TBInit();
//--------------------------------------
void ShowTaskBar( bool show );
//--------------------------------------
void ShowStartBn( bool show );
//--------------------------------------
void FlyStartBn( bool start );
//--------------------------------------
void ShowClock( bool show );
//--------------------------------------
void EnableTaskBar( bool enable );
//--------------------------------------
DWORD WINAPI flyStartProc( LPVOID ptr );
//--------------------------------------

#endif
