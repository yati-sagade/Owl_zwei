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
#ifndef __OWL_MOUSE_H__
#define __OWL_MOUSE_H__

#include <windows.h>
#include "misc.h"

#define MOUSEBN_LT	0
#define MOUSEBN_CT	1
#define MOUSEBN_RT	2

extern bool			bCtrlFlyMousePtr;
extern unsigned int uiFlyMouseDelay;
extern int			nCtrlClick;

//-----------------------------------------------------------------------------
void FlyMousePtr( bool start );
//-----------------------------------------------------------------------------
void FlyMousePtrClick( bool start );
//-----------------------------------------------------------------------------
DWORD WINAPI flyMouseProc( LPVOID ptr );
//-----------------------------------------------------------------------------
void RestrictMouseMovementTo( int left , int top , int right , int bottom ); 
//-----------------------------------------------------------------------------
void ShowMouseCursor( bool show );
//-----------------------------------------------------------------------------
void MouseClick(unsigned int button);
//-----------------------------------------------------------------------------
void MouseClickPoint( unsigned int x,unsigned int y, unsigned int button);
//-----------------------------------------------------------------------------
void SetMousePos( unsigned int x , unsigned int y );
//-----------------------------------------------------------------------------

#endif

