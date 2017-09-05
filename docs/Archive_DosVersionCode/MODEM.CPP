// ********************** START OF MODEM.CPP **********************
//
//
// This file contains all of the code for the Modem class.  It should
// be compile and linked with any program wanting to use the class.

#include <alloc.h>
#include <windows.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "t3000def.h"
#include "portable.h"
#include "rs232.h"
#include "modem.h"
#include "_msdos.h"
#include <bios.h>
#include "serial.h"
#include "gwin.h"
#include "router.h"

#define CTRLBREAK	     -1
//extern long time_slave;
//extern Comm_Info huge comm_info[MAX_COMM_INFO];
extern void *DisplayMessage(int lx, int ly, int rx, int ry, char *title, char *message, GWindow **Er1, int fcolor=Black, GWindow *Er2=NULL, long delay=0);
extern Comm_Info *comm_info;
extern int disconnect_time;
extern int mode_text;
extern char huge *trying_mess;
GWindow *Modem_answer;
char nr_line_modem_answer;
char autodetect_state;
char huge *default_string="AT &F&C1&D2V1";
//char huge *pickuptext=" Pick up the phone handset and manually dial the number:                                                            When you hear the answer tone from the remote computer:         1. Hit any key                                       2.Wait one second             3.Hang up the handset";
/*
char huge *pickuptext=" Pick up the phone handset and ask for extension        .               Hit any key now.";
char huge *hanguptext="     When the connection is made hit any key first                then hang up the phone";
*/
extern char huge *pressanykey;
//#include <iostream.h>

// The modem capability database is used to define all of the
// attributes used by a particular brand of modem.  These are
// stored in the application, which is practical when just a few
// are defined.  A bigger database might have to be moved into a
// conventional file.

ModemCapabilities ModemDataBase[] = {
{ "Generic Modem",
	"AT &F&C1&D2V1",
	"AT S0=0",
	"NO CARRIER\0ERROR\0NO DIALTONE\0BUSY\0NO ANSWER\0\0\0",
	"",
	"",
	38400L,
	0,
	1
},
/*
{ "Old Modem",
	"AT",
	"\0",
	"NO CARRIER\0ERROR\0NO DIALTONE\0BUSY\0NO ANSWER\0\0",
	"",
	"",
	300L,
	0,
	0
},
{ "Dallas Modem",
	"ATS=QV1X4 &C1 &D2 &K3  S36=7\V1W1",
	"\0",
	"NO CARRIER\0ERROR\0NO DIALTONE\0BUSY\0NO ANSWER\0\0",
	"",
	"",
	2400L,
	0,
	0
},

{ "Hayes Compatible",
	"AT &F B1E1Q0V1X4 Y0 &C1 &D2 S7=90",
	"\0",
	"NO CARRIER\0ERROR\0NO DIALTONE\0BUSY\0NO ANSWER\0\0",
	"",
	"",
	2400L,
	0,
	0
},
{ "Practical Peripherals 14400FX",
	"AT &F0 &C1 &D2 S95=44",
	"\0",
	"NO CARRIER\0ERROR\0NO DIALTONE\0BUSY\0NO ANSWER\0\0",
	"CLASS 5\0V.42BIS\0\0",
	"LAP-M\0ALT\0\0",
	57600L,
	1,
	1
},
{ "Intel SatisFAXtion 400e",
	"AT &F",
	"\0",
	"NO CARRIER\0ERROR\0NO DIALTONE\0BUSY\0NO ANSWER\0\0",
	"COMP\0\0",
	"LAPM\0MNP\0REL\0\0",
	57600L,
	1,
	1
},
*/
{ ""
} };

// The modem constructur sets up the capability database for the
// modem of the particular name, but doesn't do much else.  If the
// brand name mode is not found via an exact match, the generic Hayes
// compatible definition is used.

Modem::Modem( RS232 &rs232_port, char *modem_name, Serial *s )
{
		int i;
//    putch('1');
		port = &rs232_port;
		serptr = s;
//		modem_data = &ModemDataBase[ 0 ];
		modem_data = &comm_info[serptr->com_port].modemdata;
		for ( i = 0 ; *ModemDataBase[ i ].name != '\0' ; i++ ) {
		 if ( strcmp( modem_name, ModemDataBase[ i ].name ) == 0 ) {
			modem_data = &ModemDataBase[ i ];
			break;
		 }
		}
		modem_data->initial_baud_rate = comm_info[serptr->com_port].baudrate;
		tone_dial = 1;
		carrier_timeout = 60000L;
}

// The usual translation routine is used to print out the error
// names in more descriptive form.

char *Modem::ErrorName( ModemError status )
{
		switch ( status ) {
		 case MODEM_SUCCESS           : return "Success";
		 case MODEM_NO_RESPONSE       : return "No Response";
		 case MODEM_NO_CONNECTION     : return "No Connection";
		 case MODEM_DISCONNECT_FAILED : return "Disconnect failed";
		 case MODEM_USER_ABORT        : return "User abort";
		 case MODEM_RING							: return "Ringing";
		 default                      : return "Unknown Error";
		}
}

// The initialization routine just has to send out the initialization
// string, then wait for a response.  It inserts an extra one second
// delay in this routine, because some modems need a little extra time
// to handle initialization.

ModemError Modem::Initialize( void )
{
		if( serptr->Read_mode() == MASTER )
		{
		 Modem_answer = new GWindow(19,6,61,17,NO_STACK,0);
		 Modem_answer->GWSet("Initializing modem",Cyan,Blue);
		 Modem_answer->GShowWindow(0);
//		Modem_answer->GWPuts(1,2,"Initializing modem",Cyan,Black);
		 nr_line_modem_answer=1;
		 if(autodetect_state) Modem_answer->GWPuts(nr_line_modem_answer++,2,trying_mess,Cyan,Black);
		}
		ModemError status=MODEM_SUCCESS;
		port->Dtr( 1 );
			Delay(400);
		port->Write( "ATZ\r" );
		wait_for_response( 4000 );
		port->Set( modem_data->initial_baud_rate );
		port->RtsCtsHandshaking( modem_data->handshaking );
//		port->DtrDsrHandshaking( modem_data->handshaking );
		port->Write( '\r' );
		wait_for_response( 2000 );
//		Delay(2000);
/*
		time_modem = 2000;
		while( time_modem > 0 )
		{
			 port->IdleFunction();
		}
*/
		if( modem_data->first_init_string[0] )
		{
			port->Write( modem_data->first_init_string );
			port->Write( '\r' );
			if( (status = wait_for_response( 5000 )) == MODEM_SUCCESS )
				if( modem_data->second_init_string[0] )
				{
					port->Write( modem_data->second_init_string );
					port->Write( '\r' );
					status = wait_for_response( 5000 );
				}
			if( serptr->Read_mode() == MASTER )
			{
			 Modem_answer->GWPuts(nr_line_modem_answer++,2,ErrorName(status),Cyan,Black);
			 Delay(2000);
			}
		}
		if( serptr->Read_mode() == MASTER )
		{
			Modem_answer->GReleaseWindow();
			if( Modem_answer )
			{
			 delete Modem_answer;
			 Modem_answer = NULL;
			}
		}
		return status;
}

// This protected routine is used to read lines of data back from the
// modem, generally after a response to a command.  It reads the
// characters in, echos them using the echo routine, and tries to
// assemble a complete line.  A '\n' character is used to terminate the
// line, or a timeout.

void Modem::read_line( char *buffer, int buf_size )
{
		int c;
		char *p = buffer;
		*buffer = '\0';
//		mtextbackground(BLACK);
//		mtextcolor(WHITE);
		for ( ; ; ) {
		 c = port->Read( 5000 );
		 if ( c < 0 )
			break;
//		 if( ser_m->mode == MASTER )
//			 echo( (char) c );
		 *buffer++ = (char) c;
		 if ( --buf_size <= 1 )
		 break;
		 if ( c == '\n' )
			break;
		}
		*buffer = '\0';
		if( serptr->Read_mode() == MASTER )
			if( Modem_answer )
			 if(p[0]&&p[0]!=0x0D)
			 {
				if(nr_line_modem_answer==8) nr_line_modem_answer--;
				Modem_answer->GWPuts(nr_line_modem_answer++,2,p,Cyan,Black);
			 }
}

// This protected routine is used to wait for an OK message
// after a modem command is sent.  If it doesn't get it within
// 2 seconds, and error is returned.  Most commands going to the
// modem can expect an OK response.  The two notable exceptions
// are the dialing and answer commands.

ModemError Modem::wait_for_response( long time )
{
		char buffer[ 81 ];
		ModemError status;
		long time_r = ReadTime();

		while ( ( ReadTime() - time_r ) < time )
		{
		 read_line( buffer, 81 );
		 if ( strncmp( buffer, "OK", 2 ) == 0 )
			return MODEM_SUCCESS;
		 if ( ( status = UserAbort() ) != MODEM_SUCCESS )
			return status;
		}
		return MODEM_NO_RESPONSE;
}

// During dialing, the Dial routine has to scan the input stream for
// lots of different strings that can indicate various things about
// protocols, data compression, and connections.  This command is used
// to scan for a list of strings stored in the format used by the
// modem capability database.

char *Modem::scan_strings( char *buffer, char *strings )
{
		char *t, *p = NULL;

		while ( *strings )
		{
			if ( ( p = strstr( buffer, strings ) ) != NULL )
			{
				if( serptr->Read_mode() == MASTER )
				{
					t = p;
					for( ; *t != 0; t++ ) echo( *t );
				}
				return p;
			}
			strings += strlen( strings ) + 1;
		}
		return p;
}

ModemError Modem::Wait_for_ring( void )
{
/*
	char buffer[81], *p;
	int len,i=0;
	int rings=0;
	if( (port->RXSpaceUsed()) < 8*(number_rings-1)+2 )
			 return MODEM_NO_RESPONSE;
	long time = ReadTime();
	while ( ( ReadTime() - time ) < 8000  && rings < number_rings)
	{
	  if( (len=number_rings-1-rings) < 0 ) break; 
	  while( ( port->RXSpaceUsed() >= 8*len+3) && rings < number_rings )
	  {
		 read_line( buffer, 81 );
		 if( (scan_strings( buffer, "RING\0\0" )) != 0  )
		  rings++;
	  }
	}
	if(rings>=number_rings)
		return MODEM_RING;
	else
	 if(rings==0)
		return MODEM_NO_RING;
	 else
		return MODEM_NO_RESPONSE;
*/
}

// This routine is called by both the Answer and Dial routines.
// It has to scan the incoming lines of data not just for the
// "CONNECT" message, but also the protocol and compression strings
// as well.  Additionally, if the baud rate is not locked, it has
// to detect the new baud rate on connection.

ModemError Modem::wait_for_connection( long time_out )
{
		char *connect;
		char buffer[ 100 ];
		long ct = carrier_timeout;
		ModemError status;
		int i;
		compressing = 0;
		protocol = 0;
		if(time_out) ct = time_out;
		long time = ReadTime();
		while ( ( ReadTime() - time ) < ct )
		{
			read_line( buffer, 100 );
			if( connect = scan_strings( buffer, modem_data->fail_strings ) )
			{
				if( *connect )
				{
//					char mess[] = "Fail strings";
//					for( i=0; mess[i] != 0; i++ ) echo( mess[i] );
//					for( i=0; connect[i] != 0; i++ ) echo( connect[i] );
					if(mode_text && serptr->Read_mode() == MASTER)
					 mxyputs(19+(42-strlen(connect))/2,10,connect,Lightblue,Black);
					return MODEM_NO_CONNECTION;
				}
			}
			if( scan_strings( buffer, modem_data->compression_strings ) )
				compressing = 1;
			if ( scan_strings( buffer, modem_data->protocol_strings ) )
				protocol = 1;
			if ( ( connect = strstr( buffer, "CONNECT" ) ) != 0 )
			{
/*
				if ( !modem_data->locked_baud_rate )
				{
					local_baud_rate = atol( connect + 8 );
					if ( local_baud_rate !=0 )
						port->Set( local_baud_rate );
				}
				else
*/
				 local_baud_rate = modem_data->initial_baud_rate;
				if(!local_baud_rate) local_baud_rate = 1200;
				if(mode_text && serptr->Read_mode() == MASTER)
				  mxyputs(19+(42-strlen(buffer))/2,10,buffer,Lightblue,Black);
//				port->Set( local_baud_rate );
				return MODEM_SUCCESS;
			}
			if ( ( status = UserAbort() ) != MODEM_SUCCESS )
				return status;
		}
		return MODEM_NO_CONNECTION;
}

/*
// This routine dials and then has another routine do the hard work
// of waiting for a response.

ModemError Modem::Dial( char *dial_string, int blind )
{
 long time_out=0;
 char *ext = 0;
		ext=strchr(dial_string,'O');
		port->Dtr( 1 );
		port->Write( "ATD" );
		if ( tone_dial )
			port->Write( 'T' );
		else
			port->Write( 'P' );
		port->Write( dial_string );
		port->Write( '\r' );
		if(blind)
		{
		 time_out = strlen(dial_string)*1100L;
		}
		if(ext)
		{
		 memcpy(pickuptext+(strlen(pickuptext)-39),ext+1,strlen(ext+1));
		 Delay(4000);
		 DisplayMessage(10, 7, 70, 11, pressanykey, pickuptext, NULL, Black, NULL, 12000);
		 port->Write( "ATH\r" );
		 Delay(1000);
		 DisplayMessage(10, 7, 70, 11, pressanykey, hanguptext, NULL, Black, NULL, 500000);
		 port->Dtr( 1 );
		 Delay(400);
		 port->Write( "ATDT\r" );
		}
		return wait_for_connection(time_out);
}
*/

ModemError Modem::Dial( char *dial_string, int blind )
{
 GWindow *A;
 long time_out=0;
		if(dial_string[0]=='O')
		{
		 A= new GWindow(10,7,70,15,NO_STACK,0);
		 A->GWSet("About",Lightblue,Blue);
		 A->GShowWindow(WIN_ERROR);
		 A->GWPuts(1,3,"Pick up the phone handset and manually dial the number: ",Lightblue,Blue);
		 A->GWPuts(2,20,&dial_string[1],Lightblue,Blue);
		 A->GWPuts(3,3,"When you hear the answer tone from the remote computer:",Lightblue,Blue);
		 A->GWPuts(4,20,"1. Hit any key",Lightblue,Blue);
		 A->GWPuts(5,20,"2. Wait one second",Lightblue,Blue);
		 A->GWPuts(6,20,"3. Hang up the handset",Lightblue,Blue);
		 while(!A->HandleEvent());
		 delete A;
//		 memcpy(&pickuptext[59],&dial_string[1],strlen(&dial_string[1]));
//		 DisplayMessage(10, 7, 70, 11, pressanykey, pickuptext, NULL, Black, NULL, 500000);
		}
		else
			port->Dtr( 1 );
		port->Write( "ATD" );
		if(dial_string[0]!='O')
		{
		 if ( tone_dial )
			port->Write( 'T' );
		 else
			port->Write( 'P' );
		 port->Write( dial_string );
		}
		port->Write( '\r' );
		if(blind)
		{
		 time_out = strlen(dial_string)*1100L;
		}
		return wait_for_connection(time_out);
}

// This routine sends the answer command, then lets the other routine
// wait for success or failure.

ModemError Modem::Answer( void )
{
		port->Dtr( 1 );
		Delay(300);
		port->Write( "ATA\r" );
		return wait_for_connection();
}

// Although all of the modems in the database are supposed to be set
// up so that dropping DTR causes a disconnect, some may slip through
// the net.  If dropping DTR doesn't cause a disconnect, the
// escape sequence is sent, followed by a Hangup message.

ModemError Modem::Disconnect( void )
{
		disconnect_time = -1;
		port->Dtr( 0 );
		Delay(1600);
/*
		time_modem = 1500;
		while ( time_modem > 0 )
			port->IdleFunction();
*/
		port->Dtr( 1 );
		Delay(400);
		port->Write( "AT\r" );
		if ( wait_for_response( 2000 ) == MODEM_SUCCESS )
		{
			port->Set( modem_data->initial_baud_rate );
			return MODEM_SUCCESS;
		}
		port->Write( "+++" );
		wait_for_response( 1500 );
		port->Write( "ATH0\r" );
		if ( wait_for_response( 3000 ) == MODEM_SUCCESS )
		{
			port->Set( modem_data->initial_baud_rate );
			return MODEM_SUCCESS;
		}
		return MODEM_DISCONNECT_FAILED;
}

// This routine gives the user an opportunity to abort during long
// sequences, such as dialing.

ModemError Modem::UserAbort( void )
{
		if( bioskey_new(1) == CTRLBREAK )
//		if( ( bioskey(1)&0xff ) == 27 && (bioskey(2)&0x04 ))
		{
		 bioskey_new(0);
		 return MODEM_USER_ABORT;
		}
		return MODEM_SUCCESS;
}

// ReadRegister() not only asks for the register value, it then
// scans it in and converts it from ASCII to binary so it can be
// used by the program.

/*int Modem::ReadRegister( int reg )
{
    char buffer[ 81 ];
    long timeout;
    int value;
    ModemError status;

    sprintf( buffer, "ATS%d?\r", reg );
    port->Write( buffer );
    timeout = ReadTime() + 3000;
    value = (int) MODEM_NO_RESPONSE;
		while ( timeout > ReadTime() ) {
	   read_line( buffer, 80 );
	   if ( strncmp( buffer, "OK", 2 ) == 0 )
		  break;
	   if ( ( status = UserAbort() ) != MODEM_SUCCESS )
		  return status;
	   if ( isdigit( *buffer ) )
		  value = atoi( buffer );
    }
    return value;
}
  */
// This is the generic routine to send a command of your choice.  It
// assumes the command will get an OK message in return.

ModemError Modem::SendCommand( char *command )
{
    port->Write( command );
    port->Write( '\r' );
		return wait_for_response( 2000 );
}

// This routine is generally only useful during debugging.  It
// dumps the state of the Modem structure out to the screen.

void Modem::DumpState( void )
{
/*
	 char *p,buf[10];;

	 mputs("\nModem Status:\n\nName:                 ");
	 mputs(modem_data->name);
	 mputs("\nInit string:          ");
	 mputs(modem_data->first_init_string);

//	 mputs("\nFail strings:         ");
//	 p = modem_data->fail_strings;
//	 while ( *p ) {
//		cout << p;
//		p += strlen( p ) + 1;
//		if ( *p )
//		  cout << ", ";
//	 }
//	 cout << '\n';

	 mputs("Compression strings:  ");
	 p = modem_data->compression_strings;
	 while ( *p ) {
		mputs( p );
		p += strlen( p ) + 1;
		if ( *p )
		  mputs(", ");
	 }
	 mputs("\nProtocol strings:     ");
	 p = modem_data->protocol_strings;
	 while ( *p ) {
		mputs(p);
		p += strlen( p ) + 1;
		if ( *p )
		  mputs(", ");
	 }
	 mputs("\nInitial baud rate:    ");
	 mputs(ltoa(modem_data->initial_baud_rate,buf,10));
	 mputs("\nBaud rate locked:     ");
	 mputs((( modem_data->locked_baud_rate ) ? "Y" : "N"));
	 mputs("\nHardware handshaking: ");
	 mputs( (( modem_data->handshaking ) ? "Y" : "N"));
	 mputs("\nDialing method:       ");
	 mputs((( tone_dial ) ? "Tone" : "Pulse" ));
	 mputs("\nCarrier timeout:      ");
	 mputs( ltoa(carrier_timeout,buf,10) );
	 mputs("\nConnected:            ");
	 if(port)
	 {
	  mputs((( port->Cd() ) ? "Y" : "N" ));
	  if ( !port->Cd() )
			return;
	  mputs("\nLocal baud rate:      ");
	  mputs(ltoa(local_baud_rate,buf,10));
	  mputs("\nCompressing:          ");
	  mputs((( compressing ) ? "Y" : "N" ));
	  mputs("\nProtocol:             ");
	  mputs((( protocol ) ? "Y" : "N" ));
	 } 
*/
}

// ********************** END OF MODEM.CPP **********************

