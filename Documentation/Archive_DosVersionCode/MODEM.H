// ********************** START OF MODEM.H **********************
//
// This header file has all of the definitions and prototypes
// needed to use the Modem class.  This file should be included
// by any module that uses the Modem class.
//

#ifndef _MODEM_DOT_H
#define _MODEM_DOT_H

#include "rs232.h"
#include <conio.h>
#include "mtkernel.h"
class Serial;
class RS232;

enum ModemError
			{
					MODEM_SUCCESS                 = 0,
					MODEM_NO_RESPONSE             = -100,
					MODEM_NO_RING                 = -101,
					MODEM_NO_CONNECTION           = -102,
					MODEM_DISCONNECT_FAILED       = -103,
					MODEM_RING							= -104,
					MODEM_USER_ABORT              = -105
			};

// This structure defines the layout of the modem capability
// database elements.  At present, all of the definitions that
// can be used to define a particular brand or type of modem
// are stored in a static array in MODEM.CPP.  A commercial
// application might store these off line in a database.

struct ModemCapabilities {
		char name[41];
		char first_init_string[41];
		char second_init_string[41];
		char fail_strings[61];
		char compression_strings[41];
		char protocol_strings[41];
		long initial_baud_rate;
		int locked_baud_rate;
		int handshaking;
};

// The Modem class definition

class Modem {
	public:
		 long local_baud_rate;
	protected :
		 Serial *serptr;
		 RS232 *port;
		 ModemCapabilities *modem_data;
		 int tone_dial;
		 int protocol;
		 int compressing;
		 long carrier_timeout;
		 ModemError wait_for_response( long time );
		 ModemError wait_for_connection( long time_out = 0 );
		 virtual void echo( char c ) { mputchar( c, BLACK, WHITE ); }
		 void read_line( char *buffer, int buf_size );
		 char *scan_strings( char *buffer, char *strings );

	public :
		 Modem( RS232 &rs232_port, char *modem_name, Serial *s );
		 ModemError Initialize( void );
		 ModemError Answer( void );
		 ModemError Dial( char *number, int  = 0 );
		 ModemError Wait_for_ring( void );
		 ModemError Disconnect( void );
		 ModemError SendCommand( char * );
//	   int ReadRegister( int reg );
		 virtual ModemError UserAbort( void );
		 void PulseDial( void ){ tone_dial = 0; }
		 void ToneDial( void ){ tone_dial = 1; }
		 void SetCarrierTimeout( long length ){ carrier_timeout = length; }
		 char *ErrorName( ModemError status );
       virtual void DumpState( void );
		 int Protocol( void ){ return protocol; }
		 int Compressing( void ){ return compressing; }
};


#endif // #ifdef _MODEM_DOT_H

// ********************** END OF MODEM.H **********************

