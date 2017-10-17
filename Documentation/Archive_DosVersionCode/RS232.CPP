// *********************** START OF RS232.CPP ***********************
//
//
//
// This C++ file contains the definitions for all functions defined for
// the base class.  Most of these are dummy functions that only return
// a warning message to the calling routine.  A well defined derived
// class will usually define new versions of these virtual functions,
// which means they will never be called.
//

#ifdef SERIAL_COMM
#include "portable.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "t3000def.h"
#include "rs232.h"

// FlushRXBuffer() doesn't have to be defined for every
// derived class.  This default function should be able to flush
// the buffer using the mandatory read_buffer() function.
// Classes such as PC8250 that have direct access to their
// receive buffer can implement more efficient versions than this
// if they want.

int RS232::FlushRXBuffer( void )
{
    char buf[ 32 ];

asm push es;
		for ( ; ; ) {
//				if ( error_status != RS232_SUCCESS )
//						return error_status;
				read_buffer( buf, 32 );
				if ( ByteCount == 0 )
						break;
		}
asm pop es;
		return RS232_SUCCESS;
}

// Peek( void ) isn't a virtual function.  This is one of the
// few normal member functions in class RS232.  It peeks at a
// single byte using the Peek( char *, int ) function.

int RS232::Peek( void )
{
		char c;
		int status;

//		if ( error_status < RS232_SUCCESS )
//				return error_status;
		if ( ( status = Peek( &c, 1 ) ) < RS232_SUCCESS )
				return status;
		if ( ByteCount < 1 )
				return RS232_TIMEOUT;
		return (int) c;
}

//
// This member function returns the character translation for one
// of the error codes defined in the base class.  It is called by
// the ErrorName() function for a derived class after checking to
// see if the error code is not a new one defined by the derived
// class.

/*
char * RS232::ErrorName( int error )
{
		switch ( error ) {
				case RS232_SUCCESS                 :
						return( "Success" );

				case RS232_WARNING                 :
						return( "General Warning" );
				case RS232_FUNCTION_NOT_SUPPORTED  :
						return( "Function not supported" );
				case RS232_TIMEOUT                 :
						return( "Timeout" );
				case RS232_ILLEGAL_BAUD_RATE       :
						return( "Illegal baud rate" );
				case RS232_ILLEGAL_PARITY_SETTING  :
            return( "Illegal parity setting" );
        case RS232_ILLEGAL_WORD_LENGTH     :
            return( "Illegal word length" );
        case RS232_ILLEGAL_STOP_BITS       :
            return( "Illegal stop bits" );
        case RS232_ILLEGAL_LINE_NUMBER     :
            return( "Illegal line number" );
        case RS232_NO_TERMINATOR           :
            return( "No terminator" );
        case RS232_NO_MODEM_RESPONSE       :
            return( "No modem response" );
        case RS232_DTR_NOT_SUPPORTED       :
						return( "DTR control not supported" );
        case RS232_RTS_NOT_SUPPORTED       :
            return( "RTS control not supported" );
        case RS232_RTS_CTS_NOT_SUPPORTED   :
            return( "RTS/CTS handshaking not supported" );
        case RS232_DTR_DSR_NOT_SUPPORTED   :
						return( "DTR/DSR handshaking not supported" );
        case RS232_XON_XOFF_NOT_SUPPORTED  :
            return( "XON/XOFF handshaking not supported" );

        case RS232_ERROR                   :
            return( "General Error" );
        case RS232_IRQ_IN_USE              :
            return( "IRQ line in use" );
        case RS232_PORT_NOT_FOUND          :
            return( "Port not found" );
        case RS232_PORT_IN_USE             :
            return( "Port in use" );
        case RS232_ILLEGAL_IRQ             :
						return( "Illegal IRQ" );
		  case RS232_MEMORY_ALLOCATION_ERROR :
				return( "Memory allocation error" );
	     case RS232_REJECT: return( "Request rejected" );
		  case RS232_PANEL_OFF 					 :
		  default                            :
            return( "???" );
		}
}
*/
/*
//
// The base class contributes four lines of output to the Debug
// output.  Note that it returns the number 4 if called with a
// null buffer, to pass this information on.  The four lines of
// output contain everything the base class knows about the port,
// which are its current settings, saved settings, port name, and
// error status. For line numbers greater than three, the derived
// class provides additional lines of debug output.  Note that
// this function is called by the version of FormatDebugOutput()
// defined for the derived class.

int RS232::FormatDebugOutput( char *buffer, int line_number )
{
    if ( buffer == 0 )
	   return 4;

		switch( line_number ) {

	   case 0 :
		  sprintf( buffer, "Base class: RS232  "
					    "COM%-2d  "
					    "Status: %-35.35s",
					    port_name + 1,
							ErrorName( error_status ) );
		  return RS232_SUCCESS;
	   case 1 :
		  sprintf( buffer, "Byte count: %5u  "
					    "Elapsed time: %9ld  "
					    "TX Free: %5u  "
							"RX Used: %5u",
					    ByteCount,
					    ElapsedTime,
					    TXSpaceFree(),
					    RXSpaceUsed() );
		  return RS232_SUCCESS;
		 case 2 :
		  sprintf( buffer,
				 "Saved port: %6ld,%c,%2d,%2d  "
				 "DTR,RTS: %2d,%2d  "
				 "XON/OFF,RTS/CTS,DTR/DSR: %2d,%2d,%2d",
				 saved_settings.BaudRate,
				 saved_settings.Parity,
				 saved_settings.WordLength,
				 saved_settings.StopBits,
				 saved_settings.Dtr,
				 saved_settings.Rts,
				 saved_settings.XonXoff,
				 saved_settings.RtsCts,
				 saved_settings.DtrDsr );
		  return RS232_SUCCESS;

	   case 3 :
		  sprintf( buffer,
				 "Current port: %6ld,%c,%1d,%1d  "
				 "DTR,RTS: %2d,%2d  "
				 "XON/OFF,RTS/CTS,DTR/DSR: %2d,%2d,%2d",
				 settings.BaudRate,
				 settings.Parity,
				 settings.WordLength,
				 settings.StopBits,
				 settings.Dtr,
				 settings.Rts,
				 settings.XonXoff,
				 settings.RtsCts,
				 settings.DtrDsr );
		  return RS232_SUCCESS;

		 default :
		  return RS232_ILLEGAL_LINE_NUMBER;
    }
}
  */
// This non-virtual member function operates by repeatedly
// calling the read_byte() function for the derived class.  It
// handles the optional milliseconds parameter, which determines
// how long the function will wait for input before returning a
// timeout.  The idle function is called while waiting.

int RS232::Read( long milliseconds )
{
		int c;
		long start_time;
		int idle_status = RS232_SUCCESS;

		ElapsedTime = 0;
		ByteCount = 0;
//		if ( error_status < RS232_SUCCESS )
//		{
//		 return error_status;
//		}
    start_time = ReadTime();
    for ( ; ; ) {
		 c = read_byte();
	   if ( c >= 0 )
		  break;
	   if ( milliseconds != FOREVER &&
		  ( ReadTime() - start_time ) >= milliseconds )
		  break;
	   if ( ( idle_status = IdleFunction() ) < RS232_SUCCESS )
		  break;
    }
    ElapsedTime = ReadTime() - start_time;
    if ( idle_status < RS232_SUCCESS )
	   return idle_status;
    if ( c >= 0 ) {
	   ByteCount = 1;
	   return c;
		}
		return RS232_TIMEOUT;
}

// This non-virtual member function of class RS232 operates by
// repeatedly calling the virtual function write_byte() for the
// derived class.  The milliseconds parameter defines how long
// the function will keep trying before giving up.  While
// waiting, the idle function is called.

int RS232::Write( int c, long milliseconds )
{
    int write_status;
    int idle_status = RS232_SUCCESS;
		long start_time;

	 ElapsedTime = 0;
	 ByteCount = 0;
//    if ( error_status < 0 )
//	   return error_status;
	 start_time = ReadTime();
	 for ( ; ; ) {
		write_status = write_byte( c );
		if ( write_status != RS232_TIMEOUT )
		  break;
		if ( milliseconds != FOREVER &&
		  ( ReadTime() - start_time ) >= milliseconds )
		  break;
		if ( ( idle_status = IdleFunction() ) < RS232_SUCCESS )
		  break;
	 }
	 ElapsedTime = ReadTime() - start_time;
	 if ( idle_status < RS232_SUCCESS )
		 return idle_status;
	 if ( write_status < RS232_SUCCESS )
		return write_status;
	 ByteCount = 1;
	 return RS232_SUCCESS;
}

// This non-virtual member function of class RS232 writes out
// a buffer using the virtual write_buffer() routine.  It has
// two additional parameters beyond those used by write_buffer(),
// which are a timeout value and a terminator.  The terminator
// can be used to automatically append a CR/LF pair to output
// strings.

int RS232::Write( void *buffer,
					 unsigned int count,
					 long milliseconds,
					 char *terminator )
{
	 char *b = ( char * ) buffer;
	 long start_time;
	 unsigned int byte_count;
	 int idle_status = RS232_SUCCESS;
	 int write_status;

	 ElapsedTime = 0;
	 ByteCount = 0;
//    if ( error_status < 0 )
//	   return error_status;

	 byte_count = 0;
	 start_time = ReadTime();
	 if ( count == 0 )
	  count = strlen( b );
	 for ( ; ; ) {
		 write_status = write_buffer( b, count );
		 byte_count += ByteCount;
		 b += ByteCount;
		 count -= ByteCount;
/*
		 if ( count == 0 && terminator != 0 ) {
			count += strlen( terminator );
			b = terminator;
			terminator = 0;
			continue;
		 }
*/
		 if ( write_status != RS232_TIMEOUT || count == 0 )
			break;
		 if ( milliseconds != FOREVER &&
			 ( ReadTime() - start_time ) >= milliseconds )
			break;
		 if ( ( idle_status == IdleFunction() ) < RS232_SUCCESS )
			break;
	 }
	 ElapsedTime = ReadTime() - start_time;
	 ByteCount = byte_count;
	 if ( idle_status < RS232_SUCCESS )
		 return idle_status;
	 if ( write_status < RS232_SUCCESS )
		return write_status;
	 else if ( count > 0 )
			  return RS232_TIMEOUT;
			else
	       return RS232_SUCCESS;
}

// There are two versions of the non-virtual ReadBuffer()
// function defined for the base class.  They differ only in what
// causes their normal termination.  This version terminates only
// when it reads in a full buffer of data, or times out.  The
// next version stops when it sees the terminator string
// specified as a parameter.

int RS232::Read( void *buffer, unsigned int count, long milliseconds )
{
asm push es;
		long start_time;
		unsigned int byte_count;
		char *b = (char *) buffer;
		int read_status, flag=0;
		int idle_status = RS232_SUCCESS;

		if(!count) flag = 1;
		ElapsedTime = 0;
		ByteCount = 0;
//		if ( error_status < 0 )
//		{
//		 return error_status;
//		}
		start_time = ReadTime();
		byte_count = 0;
		for ( ; ; ) {
		 read_status = read_buffer( b, count );
		 byte_count += ByteCount;
		 count -= ByteCount;
		 b += ByteCount;
		 if ( read_status != RS232_TIMEOUT || count == 0 )
			break;
		 if ( milliseconds != FOREVER &&
			( ReadTime() - start_time ) >= milliseconds )
			break;
		 if ( ( idle_status = IdleFunction() ) < RS232_SUCCESS )
			break;
		}
		if(flag) *b = '\0';
		ElapsedTime = ReadTime() - start_time;
		ByteCount = byte_count;
		if ( idle_status < RS232_SUCCESS )
		{
		 asm pop es;
		 return idle_status;
		}
		else
		{
		 asm pop es;
		 return read_status;
		}
}

// This version of ReadBuffer() looks for a termination string
// in the incoming data stream.  Because of this, it has to read
// in characters one at a time instead of in blocks.  It looks
// for the terminator by doing a strncmp() after every new
// character is read in, which is probably not the most efficient
// way of doing it.

int RS232::Read( void *buffer,
				unsigned int count,
				long milliseconds,
				char *terminator )
{
asm push es;
		long start_time;
		unsigned int byte_count;
		char *b = (char *) buffer;
		int idle_status = RS232_SUCCESS;
		int c;
		int term_len, flag=0;

		if(!count) flag = 1;
		term_len = strlen( terminator );
		ElapsedTime = 0;
		ByteCount = 0;
//		if ( error_status < 0 )
//		{
//		 return error_status;
//		}
		start_time = ReadTime();
		byte_count = 0;
		for ( ; ; ) {
		 c = read_byte();
		 if ( c >= 0 ) {
			byte_count++;
			count--;
			*b++ = (char) c;
			if ( byte_count >= (unsigned int) term_len ) {
			 if ( strncmp( b - term_len, terminator, term_len ) == 0 ) {
				b -= term_len;
				c = RS232_SUCCESS;
				byte_count -= term_len;
				break;
			 }
			}
			if ( count == 0 )
			 break;
		 } else {
			if ( c != RS232_TIMEOUT )
			 break;
			if ( milliseconds != FOREVER &&
				( ReadTime() - start_time ) >= milliseconds )
			 break;
			if ( ( idle_status = IdleFunction() ) < RS232_SUCCESS )
			 break;
		 }
		}
		if(flag) *b = '\0';
		ElapsedTime = ReadTime() - start_time;
		ByteCount = byte_count;
		if ( idle_status < RS232_SUCCESS )
		{
		 asm pop es;
		 return idle_status;
		}
		else if ( c < RS232_SUCCESS )
		{
		 asm pop es;
		 return c;
		}
		else
		{
		 asm pop es;
		 return RS232_SUCCESS;
		}
}

// All of the remaining functions defined here are optional
// functions that won't be defined for every class.  The default
// versions of these virtual functions just return an error
// message.

int RS232::Break( long duration )
{
    UNUSED( duration );
    return RS232_FUNCTION_NOT_SUPPORTED;
}

int RS232::SoftwareOverrunError( int clear )
{
    UNUSED( clear );
    return RS232_FUNCTION_NOT_SUPPORTED;
}

int RS232::FlushTXBuffer( void )
{
    return RS232_FUNCTION_NOT_SUPPORTED;
}

int RS232::RXSpaceFree( void )
{
    return RS232_FUNCTION_NOT_SUPPORTED;
}

int RS232::TXSpaceUsed( void )
{
    return RS232_FUNCTION_NOT_SUPPORTED;
}

int RS232::XonXoffHandshaking( int enable )
{
    UNUSED( enable );
    return RS232_FUNCTION_NOT_SUPPORTED;
}

int RS232::RtsCtsHandshaking( int enable )
{
    UNUSED( enable );
    return RS232_FUNCTION_NOT_SUPPORTED;
}

int RS232::DtrDsrHandshaking( int enable )
{
    UNUSED( enable );
    return RS232_FUNCTION_NOT_SUPPORTED;
}

int RS232::Dtr( int setting )
{
    UNUSED( setting );
    return RS232_FUNCTION_NOT_SUPPORTED;
}

int RS232::Rts( int setting )
{
    UNUSED( setting );
    return RS232_FUNCTION_NOT_SUPPORTED;
}

int RS232::Peek( void *buffer, unsigned int count )
{
    UNUSED( buffer );
    UNUSED( count );
    return RS232_FUNCTION_NOT_SUPPORTED;
}

void Settings::Adjust( long baud_rate,
				   int parity,
				   int word_length,
				   int stop_bits,
				   int dtr,
				   int rts,
				   int xon_xoff,
				   int rts_cts,
				   int dtr_dsr )
{
    if ( baud_rate != UNCHANGED )
		  BaudRate = baud_rate;
    if ( parity != UNCHANGED )
	   Parity = (char) toupper( parity );
    if ( word_length != UNCHANGED )
	   WordLength = word_length;
    if ( stop_bits != UNCHANGED )
	   StopBits = stop_bits;
    if ( dtr != UNCHANGED )
	   Dtr = dtr;
    if ( rts != UNCHANGED )
	   Rts = rts;
    if ( xon_xoff != UNCHANGED )
	   XonXoff = xon_xoff;
    if ( rts_cts != UNCHANGED )
	   RtsCts = rts_cts;
    if ( dtr_dsr != UNCHANGED )
	   DtrDsr = dtr_dsr;
}

// ************************** END OF RS232.CPP **************************

#endif