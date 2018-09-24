// ************************* START OF RS232.H *************************
//
//
//
// This header file contains the definitions for the base class RS232.
//
#ifndef _RS232_DOT_H
#define _RS232_DOT_H

#include "portable.h"
#include "modem.h"
#include <conio.h>

typedef enum  {  IRQ0 = 0, IRQ1, IRQ2,  IRQ3,  IRQ4,  IRQ5,  IRQ6,  IRQ7,
					  IRQ8,     IRQ9, IRQ10, IRQ11, IRQ12, IRQ13, IRQ14, IRQ15,
					  ILLEGAL_IRQ = -1 } irq_name;

typedef enum {
						COM0 = -1, COM1, COM2, COM3, COM4, COM5, COM6, COM7, COM8, BUS
				 } RS232PortName;

#define MAX_COM 8

typedef struct {
	RS232PortName     port_name;
	irq_name			    int_name;
	long               baudrate;
	unsigned int   connection:4;
	unsigned int     activate:4;
	ModemCapabilities modemdata;
	char                  rings;
   char             program_nr;
   int                  unused;
	int          NetworkAddress;
	char NetworkName[NAME_SIZE];
  }  Comm_Info;
/*
typedef struct {
	RS232PortName	port_name;
	irq_name			int_name;
	unsigned baudrate;
	}	Comm_Info;
*/

typedef enum  {     RS232_SUCCESS                 = 0,
// Warning errors
						  RS232_WARNING                 = -100,
						  RS232_FUNCTION_NOT_SUPPORTED,
						  RS232_TIMEOUT,
						  RS232_ILLEGAL_BAUD_RATE,
						  RS232_ILLEGAL_PARITY_SETTING,
						  RS232_ILLEGAL_WORD_LENGTH,
						  RS232_ILLEGAL_STOP_BITS,
						  RS232_ILLEGAL_LINE_NUMBER,
						  RS232_NO_MODEM_RESPONSE,
						  RS232_NO_TERMINATOR,
						  RS232_DTR_NOT_SUPPORTED,
						  RS232_RTS_NOT_SUPPORTED,
						  RS232_RTS_CTS_NOT_SUPPORTED,
						  RS232_DTR_DSR_NOT_SUPPORTED,
						  RS232_XON_XOFF_NOT_SUPPORTED,
						  RS232_NEXT_FREE_WARNING,
// Fatal Errors
						  RS232_ERROR                   = -200,
						  RS232_IRQ_IN_USE,
						  RS232_PORT_NOT_FOUND,
						  RS232_PORT_IN_USE,
						  RS232_ILLEGAL_IRQ,
						  RS232_MEMORY_ALLOCATION_ERROR,
						  RS232_PANEL_OFF,
						  RS232_USER_ABORT,
						  RS232_REJECT,
						  RS232_NEXT_FREE_ERROR
						  } RS232Error;

//
// These constants are used as parameters to RS232 member functions.
//

const int UNCHANGED = -1;
const int FOREVER = -1;
const int DISABLE = 0;
const int CLEAR = 0;
const int ENABLE = 1;
const int SET = 1;
const int RESET = 1;
const int REMOTE_CONTROL = -1;

//
// The Settings class provides a convenient mechanism for saving or
// assigning the state of a port.
//

class Settings
{
	 public :
		  long BaudRate;
		  char Parity;
		  int WordLength;
		  int StopBits;
		  int Dtr;
		  int Rts;
		  int XonXoff;
		  int RtsCts;
		  int DtrDsr;
		  void Adjust( long baud_rate,
							int parity,
							int word_length,
							int stop_bits,
							int dtr,
							int rts,
							int xon_xoff,
							int rts_cts,
							int dtr_dsr );
};

//
// Class RS232 is the abstract base class used for any serial port
// class.  RS232 cannot be instantiated.  Only fully defined classes
// derived from RS232 can actually be created and used.
//

class RS232
{
	 protected :
		RS232PortName port_name;
		Settings saved_settings;
	 public:
		Settings settings;
	 protected :
		RS232Error error_status;
//	   int debug_line_count;

// Mandatory protected functions

		virtual int read_buffer( char *buffer,
							unsigned int count ) = 0;
		virtual int write_buffer( char *buffer,
							 unsigned int count = -1, int type = 0 ) = 0;
		virtual int read_byte( void ) = 0;
		virtual int write_byte( int c ) = 0;

	 public :
		unsigned int ByteCount;
		long ElapsedTime;

//  Mandatory functions.  All derived classes must define these.

		virtual RS232Error Set( long baud_rate = UNCHANGED,
						  int parity = UNCHANGED,
						  int word_length = UNCHANGED,
						  int stop_bits = UNCHANGED ) = 0;
		virtual int TXSpaceFree( void ) = 0;
		virtual int RXSpaceUsed( void ) = 0;
		virtual int Cd( void ) = 0;
		virtual int Ri( void ) = 0;
		virtual int Cts( void ) = 0;
		virtual int Dsr( void ) = 0;
		virtual int ParityError( int clear = UNCHANGED ) = 0;
		virtual int BreakDetect( int clear = UNCHANGED ) = 0;
		virtual int FramingError( int clear = UNCHANGED ) = 0;
		virtual int HardwareOverrunError( int clear = UNCHANGED ) = 0;

// Optional Functions.  Derived class are not required to support these.

		virtual ~RS232( void ){ ; }
		virtual int Break( long milliseconds = 300 );
		virtual int SoftwareOverrunError( int clear = UNCHANGED );
		virtual int XonXoffHandshaking( int setting = UNCHANGED );
		virtual int RtsCtsHandshaking( int setting = UNCHANGED );
		virtual int DtrDsrHandshaking( int setting = UNCHANGED );
		virtual int Dtr( int setting = UNCHANGED );
		virtual int Rts( int setting = UNCHANGED );
		virtual int Peek( void *buffer, unsigned int count );
		virtual int RXSpaceFree( void );
		virtual int TXSpaceUsed( void );
		virtual int FlushRXBuffer( void );
		virtual int FlushTXBuffer( void );
//		virtual char *ErrorName( int error );
		virtual int IdleFunction( void );
/*        virtual int FormatDebugOutput( char *buffer = 0,
								 int line_number = -1 );*/

// Non virtual functions.  These work the same for all classes.

		int Read( void *buffer,
				unsigned int count,
				long milliseconds = 0 );
		int Read( void *buffer,
				unsigned int count,
				long milliseconds,
				char *terminator );
		int Write( void *buffer,
				 unsigned int count = 0,
				 long milliseconds = 0,
				 char *terminator = 0 );
		int Read( long milliseconds = 0 );
		int Write( int c, long milliseconds = 0 );
		int Peek( void );
		int ReadSettings( Settings &copy ) { copy = settings;
									return RS232_SUCCESS; }
		long ReadBaudRate( void ) { return settings.BaudRate; }
		RS232Error ErrorStatus( void ) { return error_status; }
//	   int DebugLineCount( void ) { return debug_line_count; }
};

// A Miscellaneous support function.  This may be implemented
// differently by different environments.

unsigned long ReadTime( void );

#endif  // #ifndef _RS232_DOT_H

// *************************** END OF RS232.H ***************************
