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
#ifndef __OWL_SYSTEMINFO_H__
#define __OWL_SYSTEMINFO_H__

#include "misc.h"
#include "windows.h"

extern bool bDirInit;
extern char szCurrDir[];
//-------------------------------------------------------------------------
typedef enum{
	U_FREE = 0,
	U_USED,
	U_TOTAL
}usage_param_t;
//-------------------------------------------------------------------------
bool isConnected();
//-------------------------------------------------------------------------
unsigned long GetMaxMem();
//-------------------------------------------------------------------------
unsigned long GetBusyMem();
//-------------------------------------------------------------------------
unsigned long GetFreeMem();
//-------------------------------------------------------------------------
char* sysdir();
//-------------------------------------------------------------------------
char* windir();
//-------------------------------------------------------------------------
unsigned __int64 GetDiskUsage( const char *volume , usage_param_t u_type );
//-------------------------------------------------------------------------
bool is_NT();
//-------------------------------------------------------------------------
void init_dir();
//-------------------------------------------------------------------------
void cd( const char *dirname );
//-------------------------------------------------------------------------
#endif


