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
#ifndef _REGHELPER_INCLUDED
#define _REGHELPER_INCLUDED

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

LONG GetSettingInt(HKEY hkey, TCHAR szKeyName[], LONG nDefault);
BOOL GetSettingBool(HKEY hkey, TCHAR szKeyName[], BOOL nDefault);
LONG GetSettingStr(HKEY hkey, TCHAR szKeyName[], TCHAR szDefault[], TCHAR szReturnStr[], DWORD nSize);
LONG GetSettingBinary(HKEY hkey, TCHAR szKeyName[], void *buf, ULONG nNumBytes);

LONG WriteSettingInt(HKEY hkey, TCHAR szKeyName[], LONG nValue);
LONG WriteSettingBool(HKEY hkey, TCHAR szKeyName[], BOOL nValue);
LONG WriteSettingStr(HKEY hkey, TCHAR szKeyName[], TCHAR szString[]);
LONG WriteSettingBinary(HKEY hkey, TCHAR szKeyName[], void *buf, UINT nNumBytes);


#ifdef __cplusplus
}
#endif

#endif
