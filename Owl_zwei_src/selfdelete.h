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
#ifndef __SELFDELETE_H__
#define __SELFDELETE_H__
//-------C does not have the bool datatype-----------------------------
#define bool int
#define true 1
#define false 0

//---------------------------------------------------------------------
#include <windows.h>

#ifdef __cplusplus
extern "C"{
#endif
//---------------------------------------------------------------------
BOOL check_for_deinstall( const char *argvstr );
//---------------------------------------------------------------------
void DeleteMaster( const char *exe , DWORD pid );
//---------------------------------------------------------------------
void SelfDelete();
//---------------------------------------------------------------------
void DoUninstall( const char *argstr );
//---------------------------------------------------------------------
char** c_split( const char *delim , const char *str , char **result );
//---------------------------------------------------------------------
#ifdef __cplusplus
}
#endif

#endif 
