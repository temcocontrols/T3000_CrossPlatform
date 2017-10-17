// ******************** START OF PC8250.CPP ********************
//
//
//
// This file contains most of the code used in the PC8250
// class.  The remainder of the code can be found in
// ISR_8250.CPP, which has the ISR and its support code.

#ifdef SERIAL_COMM

#include <alloc.h>
#include <windows.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <ctype.h>
#include "baseclas.h"
#include "rs232.h"
#include "pc8250.h"
#include "_pc8250.h"
#include "mtkernel.h"
#include "ascii.h"
#include "rs485.h"

extern int Black;					    //0
extern int Blue;              //1
extern int Green;             //2
extern int Cyan;              //3
extern int Red;               //4
extern int Green1; 				    //5
extern int Blue1;             //6
extern int Lightgray;         //7

extern int Darkgray;          //8
extern int Lightblue;         //9
extern int Lightgreen;       	//10
extern int Lightcyan;         //11
extern int Lightred;          //12
extern int Lightmagenta;   	  //13
extern int Yellow;            //14
extern int White;             //15
extern int Brown;
extern int Magenta;

extern int dtr;
// Data used to initialize UART addresses and IRQ lines.

int ISA_uarts[]            = { 0x3f8,  0x2f8,  0x3e8,  0x2e8 };
static irq_name ISA_IRQs[]   = { IRQ4,   IRQ3,   IRQ4,   IRQ3 };
/*static int MCA_uarts[]            = { 0x03f8, 0x02f8, 0x3220, 0x3228,
								 0x4220, 0x4228, 0x5220, 0x5228 };
static enum irq_name MCA_IRQs[]   = { IRQ4,   IRQ3,   IRQ3,   IRQ3,
								 IRQ3,   IRQ3,   IRQ3,   IRQ3 };
*/
//extern Comm_Info *comm_info;
//extern Comm_Info huge comm_rs485;
// This is the one and only constructor for an object of class
// PC8250.  A quick look at PC8250.H will show you that all of
// the parameters in the list except the port have default
// values, so the list isn't as overwhelming as it might look.

PC8250::PC8250(
			 RS232PortName port,
			 long baud_rate,
			 char parity,
			 int word_length,
			 int stop_bits,
			 int dtr,
			 int rts,
			 int xon_xoff,
			 int rts_cts,
			 int dtr_dsr,
			 Handler *handler,
			 int uart_address,
			 irq_name irq_line )
{
	 if (setpc8250(
       1,
			 port,
			 baud_rate,
			 parity,
			 word_length,
			 stop_bits,
			 dtr,
			 rts,
			 xon_xoff,
			 rts_cts,
			 dtr_dsr,
			 handler,
			 uart_address,
			 irq_line )
			);
}

int PC8250::setpc8250(
       int t,
			 RS232PortName port,
			 long baud_rate,
			 char parity,
			 int word_length,
			 int stop_bits,
			 int dtr,
			 int rts,
			 int xon_xoff,
			 int rts_cts,
			 int dtr_dsr,
			 Handler *handler,
			 int uart_address,
			 irq_name irq_line )
{
		int mcr,err;
		interrupt_handler = handler;
		port_name = port;
		error_status = RS232_SUCCESS;

// This section of code initializes most of the items in the
// isr_data structure, which contains all of the items used in
// the ISR.
		if(t)
		{
		 set_semaphore_dos();
		 isr_data = new isr_data_block;
		 clear_semaphore_dos();
		 if ( isr_data == 0 ) {
				error_status = RS232_MEMORY_ALLOCATION_ERROR;
				return 1;
		 }
		 memset(isr_data, 0, sizeof(struct isr_data_block));
		}
		set_uart_address_and_irq( handler, uart_address, irq_line );
		if(t)
		 if ( error_status < RS232_SUCCESS )
				return 1;
/*
		isr_data->overflow = 0;
		isr_data->tx_running = 0;
		isr_data->tx_int_count = 0;
		isr_data->rx_int_count = 0;
		isr_data->ls_int_count = 0;
		isr_data->ms_int_count = 0;
		isr_data->line_status = 0;
		isr_data->handshaking = 0;
		isr_data->blocking = 0;
		isr_data->blocked = 0;
*/
		isr_data->send_handshake_char = -1;
/*
// PC8250 has to share the debug output with the parent
// class.  To determine where our first line starts, we call the
// FormatDebugOutput() function from our parent class.

		first_debug_output_line = RS232::FormatDebugOutput();
		debug_line_count = FormatDebugOutput();
*/
// Determine whether the UART is there and what type it is.

		check_uart();
		if(t)
		 if ( error_status < RS232_SUCCESS )
		  return 1;

//  Save all of the old UART settings, and then set it to the
//  new ones passed to the constructor.

		if(t)
		{
		 read_settings();
		 saved_settings = settings;
		}
		settings.Adjust( baud_rate,
				 parity,
				 word_length,
				 stop_bits,
				 dtr,
				 rts,
				 xon_xoff,
				 rts_cts,
				 dtr_dsr );
		write_settings();

// Here we set up the interrupt handler, then turn on
// interrupts.  After this code is done the UART will be
// running.

		OUTPUT( isr_data->uart + INTERRUPT_ENABLE_REGISTER, 0 );
		mcr = INPUT( isr_data->uart + MODEM_CONTROL_REGISTER );
		mcr |= MCR_OUT2;
		mcr &= ~MCR_LOOPBACK;
		OUTPUT( isr_data->uart + MODEM_CONTROL_REGISTER, mcr );
		if ( interrupt_handler == 0 ) {
		 error_status = ConnectToIrq( irq,
								isr_data, (void (*)(void *))
								isr_8250 );
		 if ( error_status < RS232_SUCCESS ) {
			OUTPUT( isr_data->uart + MODEM_CONTROL_REGISTER, 0 );
			OUTPUT( isr_data->uart + INTERRUPT_ENABLE_REGISTER, 0 );
			return 1;
		 }
		} else {
		 error_status = interrupt_handler->AddPort( port_name,
										 isr_data );
		 if ( error_status < RS232_SUCCESS )
			return 1;
		}
		INPUT( isr_data->uart );  // Clear any pending interrupts
		INPUT( isr_data->uart + INTERRUPT_ID_REGISTER );
		CLI();
		isr_data->modem_status =
		 (unsigned int)
			INPUT( isr_data->uart + MODEM_STATUS_REGISTER );
		OUTPUT( isr_data->uart + INTERRUPT_ENABLE_REGISTER,
			IER_RX_DATA_READY + IER_TX_HOLDING_REGISTER_EMPTY +
			IER_MODEM_STATUS + IER_LINE_STATUS );
		OUTPUT( 0x20, 0xc0 + IRQ3 - 1 );
		STI();

// Finally, set up the last few parameters and exit.

		Dtr( settings.Dtr );
		Rts( settings.Rts );
		XonXoffHandshaking( settings.XonXoff );
		RtsCtsHandshaking( settings.RtsCts );
		DtrDsrHandshaking( settings.DtrDsr );
		return 1;
}

/*
void change_settings( long baud_rate = UNCHANGED,
											int parity = UNCHANGED,
											int word_length = UNCHANGED,
											int stop_bits = UNCHANGED,
											int dtr = DISABLE,
											int rts = DISABLE,
											int xon_xoff = DISABLE,
											int rts_cts = DISABLE,
											int dtr_dsr = DISABLE )
{
		read_settings();
//		saved_settings = settings;
		settings.Adjust( baud_rate,
										 parity,
										 word_length,
										 stop_bits,
										 dtr,
										 rts,
										 xon_xoff,
										 rts_cts,
										 dtr_dsr );
		write_settings();
		Dtr( settings.Dtr );
		Rts( settings.Rts );
		XonXoffHandshaking( settings.XonXoff );
		RtsCtsHandshaking( settings.RtsCts );
		DtrDsrHandshaking( settings.DtrDsr );
}
*/
void PC8250::set_uart_address_and_irq( Handler *handler,
								 int uart_address,
								irq_name irq_line )
{

// If I have a handler or have a defined irq_line, I won't
// use the default IRQs.  If I have a uart_address, I won't
// use the default UART address.

		if ( handler == 0 && irq_line == ILLEGAL_IRQ )
		{
		//	   if ( Bus() == ISA_BUS ) {
			if ( port_name > COM4 )
			 error_status = RS232_PORT_NOT_FOUND;
			else
			 irq = ISA_IRQs[ port_name ];
	 /*  } else {
			if ( port_name > COM8 )
			 error_status = RS232_PORT_NOT_FOUND;
			else
			 irq = MCA_IRQs[ port_name ];
		 }*/
		} else
		 irq = irq_line;

		if ( uart_address == 0 ) {
//	   if ( Bus() == ISA_BUS ) {
			if ( port_name > COM4 )
			 error_status = RS232_PORT_NOT_FOUND;
			else
			 isr_data->uart = ISA_uarts[ port_name ];
/*	   } else {
			if ( port_name > COM8 )
			 error_status = RS232_PORT_NOT_FOUND;
			else
			 isr_data->uart = MCA_uarts[ port_name ];
		 } */
		} else
			 isr_data->uart = uart_address;
		 for( int i=0; i<4; i++ )
		 {
				if( isr_data->uart == ISA_uarts[i] ) break;
		 }
/*
		 isr_data->task = 0;
		 if( i == comm_info[MODEM_LINK].port_name )
		 {
				isr_data->task = MODEM_LINK;
		 }
		 if( i == comm_info[RS485_LINK].port_name )
		 {
				isr_data->task = RS485_LINK;
		 }
*/
//		 if( i == comm_rs485.port_name )
//		 {
//				isr_data->task = RS485_LINK;
//		 }
}

// The destructor has a much easier time of it than the
// constructor.  It disables interrupts, then restores the line
// settings of the UART.

void PC8250::discon( void )
{
	 if ( error_status == RS232_SUCCESS ) {
		 OUTPUT( isr_data->uart + INTERRUPT_ENABLE_REGISTER, 0 );
		 OUTPUT( isr_data->uart + MODEM_CONTROL_REGISTER, 0 );
		 if ( interrupt_handler == 0 )
			DisconnectFromIRQ( irq );
		 else
			interrupt_handler->DeletePort( port_name );
		 settings = saved_settings;
		write_settings();
		Dtr( settings.Dtr );
		Rts( settings.Rts );
		if(isr_data->media == RS485_LINK)
			Dtr( dtr );
	 }
}

PC8250::~PC8250( void )
{
	 discon();
	 set_semaphore_dos();
	 if ( isr_data != 0 )
		delete isr_data;
	 clear_semaphore_dos();
}

// This routine determines if a UART is present, and if so,
// whether or not it is a 16550.  If it is a 16550, the FIFO is
// enabled with a trigger at 14 bytes.

void PC8250::check_uart( void )
{
    int temp;

		OUTPUT( isr_data->uart + FIFO_CONTROL_REGISTER, 0 );
		temp = INPUT( isr_data->uart + INTERRUPT_ID_REGISTER );
		if ( ( temp & 0xf8 ) != 0 ) {
		 isr_data->uart_type = UART_UNKNOWN;
		 error_status = RS232_PORT_NOT_FOUND;
		 return;
		}
		OUTPUT( isr_data->uart + FIFO_CONTROL_REGISTER,
			FCR_FIFO_ENABLE + FCR_TRIGGER_14 );
//		OUTPUT( isr_data->uart + FIFO_CONTROL_REGISTER, 0 );
		temp = INPUT( isr_data->uart + INTERRUPT_ID_REGISTER );
		if ( ( temp & 0xf8 ) == 0xc0 )
		{
		 isr_data->uart_type = UART_16550;
		 fifo_setting = 14;
		}
		else
		{
		 isr_data->uart_type = UART_8250;
		 fifo_setting = 0;
		 OUTPUT( isr_data->uart + FIFO_CONTROL_REGISTER, 0 );
		}
}

// After any function that reads data from the ISR buffers,
// this routine is called.  If the read operation dropped us
// below a handshaking trigger point, this routine will figure
// out what action to take.

void PC8250::check_rx_handshaking()
{
 asm push es;
		int mcr;

// Take a quick exit if we aren't handshaking, blocking, or if
// the RX Queue is not below the low-water mark.

		if ( !isr_data->handshaking || !isr_data->blocking )
		{
		 asm pop es;
		 return;
		}
		if ( isr_data->RXQueue.InUseCount() > LowWaterMark )
		{
		 asm pop es;
		 return;
		}

// If RTS/CTS handshaking is in effect, I raise RTS.

		if ( ( isr_data->handshaking & rts_cts ) &&
			( isr_data->blocking & rts_cts ) ) {
		 CLI();
		 mcr = INPUT( isr_data->uart + MODEM_CONTROL_REGISTER );
		 mcr |= MCR_RTS;
		 OUTPUT( isr_data->uart + MODEM_CONTROL_REGISTER, mcr );
		 isr_data->blocking &= ~rts_cts;
		 STI();
		}

// If DTR/DSR handshaking is in effect, I raise DTR.

		if ( ( isr_data->handshaking & dtr_dsr ) &&
			( isr_data->blocking & dtr_dsr ) ) {
		 CLI();
		 mcr = INPUT( isr_data->uart + MODEM_CONTROL_REGISTER );
		 mcr |= MCR_DTR;
		 OUTPUT( isr_data->uart + MODEM_CONTROL_REGISTER, mcr );
		 isr_data->blocking &= ~dtr_dsr;
		 STI();
		}

// If XON/XOFF is in effect, I send an XON.  Note that if
// there is a pending XOFF that never made it out, I cancel it
// and don't send anything else.

		if ( ( isr_data->handshaking & xon_xoff ) &&
			( isr_data->blocking & xon_xoff ) ) {
			CLI();
			isr_data->blocking &= ~xon_xoff;
			if ( isr_data->send_handshake_char == XOFF )
			 isr_data->send_handshake_char = -1;
			else {
			 isr_data->send_handshake_char = XON;
			 jump_start( isr_data );
			}
			STI();
		}
 asm pop es;
}

// This routine just pulls out a byte and checks for
// handshaking activity.

int PC8250::read_byte( void )
{
	asm push es;
	 int c;

//    if ( error_status < 0 )
//	   return error_status;
		c = isr_data->RXQueue.Remove();
		if ( c < 0 )
		{
		 asm pop es;
		 return RS232_TIMEOUT;
		}
		check_rx_handshaking();
    asm pop es;
		return c;
}

// When sending a byte to the output buffer, I have to check
// to see if the TX interrupt system needs to be restarted.

int PC8250::write_byte( int c )
{
//    if ( error_status < 0 )
//	   return error_status;
    if ( !isr_data->TXQueue.Insert( (unsigned char) c ) )
	   return RS232_TIMEOUT;
    if ( !isr_data->tx_running && !isr_data->blocked )
	   jump_start( isr_data );
    return RS232_SUCCESS;
}

// read_buffer() pulls in only as many bytes as are
// immediately available.  Any high-level functions such as
// timing out or looking for a terminator are handled by one of
// the higher level Read() routines from class RS232.

int PC8250::read_buffer( char *buffer, unsigned int count )
{
asm push es;
int flag=0;
		if(count==0) flag=1;
		ByteCount = 0;
//    if ( error_status < 0 )
//	   return error_status;
		while ( isr_data->RXQueue.InUseCount() ) {
		 if ( count <= 0 )
			break;
		 *buffer++ = (char) isr_data->RXQueue.Remove();
		 count--;
		 ByteCount++;
		}
		if(flag) *buffer = '\0';
		if ( ByteCount > 0 )
		 check_rx_handshaking();
		if ( count > 0 )
		{
		 asm pop es;
		 return RS232_TIMEOUT;
		}
		else
		{
		 asm pop es;
		 return RS232_SUCCESS;
		}
}

// write_buffer() sends as many characters as the buffer can
// immediately manage.  Like read_buffer(), it relies on higher
// level routines from class RS232 to perform the nicer functions
// such as adding termination, timing, etc.

// type = 1 PTP connection
int PC8250::write_buffer( char *buffer, unsigned int count, int type )
{
asm push es;
		int mcr;
		ByteCount = 0;
//    if ( error_status < 0 )
//	   return error_status;
		for ( ; ; )
		{
		 if ( count == 0 )
			break;
		 if( type )
		 {
		  if( *buffer==0x10 || *buffer==0x11 || *buffer==0x13 )
		  {
			if ( !isr_data->TXQueue.Insert( 0x10 ) )
			 break;
			if ( !isr_data->TXQueue.Insert( *buffer|0x90 ) )
			 break;
			buffer++;
			count--;
			ByteCount++;
			continue;
		  }
		 }
		 if ( !isr_data->TXQueue.Insert( *buffer ) )
			break;
		 buffer++;
		 count--;
		 ByteCount++;
		}
		if ( !isr_data->tx_running && !isr_data->blocked )
		{
			if(isr_data->media == RS485_LINK)
			{
			 CLI();
			 mcr = INPUT( isr_data->uart + MODEM_CONTROL_REGISTER );
			 if ( !dtr )
				mcr |= MCR_DTR;
			 else
				mcr &= ~MCR_DTR;
			 OUTPUT( isr_data->uart + MODEM_CONTROL_REGISTER, mcr );
			 STI();
		 }
		 jump_start( isr_data );
		}
		if ( count > 0 )
		{
		 asm pop es;
		 return RS232_TIMEOUT;
		}
		else
		{
		 asm pop es;
		 return RS232_SUCCESS;
		}
}

// The Queue functions make it easy to flush the RX queue.
// After emptying it all, we need to be sure that handshaking
// gets managed.

int PC8250::FlushRXBuffer( void )
{
asm push es;
		CLI();
		isr_data->RXQueue.Clear();
		STI();
		if(isr_data->media != RS485_LINK)
			check_rx_handshaking();
asm pop es;
		return RS232_SUCCESS;

}

// write_settings() is a protected routine called by the
// constructor and the public Set() function.   It is long and
// stringy, mostly because setting up the UART is just a long
// case of setting or clearing bits in control registers.  It
// might be possible to modularize this code, but it wouldn't be
// particularly useful.

RS232Error PC8250::write_settings( void )
{
asm push es;
		int lcr;
		int divisor_high;
		int divisor_low;
		RS232Error status = RS232_SUCCESS;
		long result_baud;

		if ( settings.BaudRate <= 0 || settings.BaudRate > 115200L ) {
		 settings.BaudRate = 9600;
		 status = RS232_ILLEGAL_BAUD_RATE;
		}
		divisor_low = (int) ( ( 115200L / settings.BaudRate ) & 0xff );
		divisor_high = (int) ( ( 115200L / settings.BaudRate ) >> 8 );
		result_baud = 115200L / ( 115200L / settings.BaudRate );
		if ( result_baud != settings.BaudRate ) {
		 settings.BaudRate = result_baud;
		 status = RS232_ILLEGAL_BAUD_RATE;
		}
		lcr = INPUT( isr_data->uart + LINE_CONTROL_REGISTER );
		lcr |= LCR_DLAB;
		CLI();
		OUTPUT( isr_data->uart + LINE_CONTROL_REGISTER, lcr );
		OUTPUT( isr_data->uart + DIVISOR_LATCH_LOW, divisor_low );
		OUTPUT( isr_data->uart + DIVISOR_LATCH_HIGH, divisor_high );
		lcr &= ~LCR_DLAB;
		OUTPUT( isr_data->uart + LINE_CONTROL_REGISTER, lcr );
		STI();
		lcr &= ~LCR_PARITY_MASK;
		switch ( toupper( settings.Parity ) ) {
		 case 'O' :
			lcr |= LCR_PARITY_ENABLE;
			break;
		 case 'E' :
			lcr |= LCR_PARITY_ENABLE + LCR_EVEN_PARITY_SELECT;
			break;
		 case 'M' :
			lcr |= LCR_PARITY_ENABLE + LCR_STICK_PARITY;
			break;
		 case 'S' :
			lcr |= LCR_PARITY_ENABLE +
					LCR_EVEN_PARITY_SELECT +
					LCR_STICK_PARITY;
			break;
		 default :
			settings.Parity = 'N';
			status = RS232_ILLEGAL_PARITY_SETTING;
		 case 'N' :
			break;
		}
		lcr &= ~LCR_WORD_LENGTH_MASK;
		switch ( settings.WordLength ) {
		 case 5 :
			break;
		 case 6 :
			lcr |= LCR_WORD_LENGTH_SELECT_0;
			break;
		 case 7 :
			lcr |= LCR_WORD_LENGTH_SELECT_1;
			break;
		 default :
			settings.WordLength = 8;
			status = RS232_ILLEGAL_WORD_LENGTH;
		 case 8 :
			lcr |= LCR_WORD_LENGTH_SELECT_0 + LCR_WORD_LENGTH_SELECT_1;
			break;
		}
		lcr &= ~LCR_STOP_BITS;
		switch ( settings.StopBits ) {
		 default :
			settings.StopBits = 1;
			status = RS232_ILLEGAL_STOP_BITS;
		 case 1 :
			break;
		 case 2 :
			lcr |= LCR_STOP_BITS;
			break;
		}
		OUTPUT( isr_data->uart + LINE_CONTROL_REGISTER, lcr );
		asm pop es;
		return status;
}

// read_settings() is the protected inverse of
// write_settings().  This routine just reads in the state of the
// UART into a settings object.  This is done when the routine
// starts up, so that the RS232 class will always have the saved
// settings available for restoration when the RS232 port is
// closed.

void PC8250::read_settings( void )
{
asm push es;
		int lcr;
		int mcr;
		int divisor_low;
		int divisor_high;

		lcr = INPUT( isr_data->uart + LINE_CONTROL_REGISTER );
		lcr |= LCR_DLAB;
		CLI();
		OUTPUT( isr_data->uart + LINE_CONTROL_REGISTER, lcr );
		divisor_low = INPUT( isr_data->uart + DIVISOR_LATCH_LOW );
		divisor_high = INPUT( isr_data->uart + DIVISOR_LATCH_HIGH );
		lcr &= ~LCR_DLAB;
		OUTPUT( isr_data->uart + LINE_CONTROL_REGISTER, lcr );
		STI();

		if ( divisor_high | divisor_low )
		 settings.BaudRate = 115200L / ( ( divisor_high << 8 ) + divisor_low );
		else
		 settings.BaudRate = -1;
		switch ( lcr & LCR_PARITY_MASK ) {
		 case LCR_PARITY_ENABLE :
			settings.Parity = 'O';
			break;
		 case LCR_PARITY_ENABLE + LCR_EVEN_PARITY_SELECT :
			settings.Parity = 'E';
			break;
		 case LCR_PARITY_ENABLE + LCR_STICK_PARITY :
			settings.Parity = 'M';
			break;
		 case LCR_PARITY_ENABLE +
			 LCR_EVEN_PARITY_SELECT +
			 LCR_STICK_PARITY :
			settings.Parity = 'S';
			break;
		 default :
			settings.Parity = 'N';
			break;
		}
		switch ( lcr & LCR_WORD_LENGTH_MASK ) {
		 case 0 :
			settings.WordLength = 5;
			break;
		 case LCR_WORD_LENGTH_SELECT_0 :
			settings.WordLength = 6;
			break;
		 case LCR_WORD_LENGTH_SELECT_1 :
			settings.WordLength = 7;
			break;
		 case LCR_WORD_LENGTH_SELECT_0 + LCR_WORD_LENGTH_SELECT_1 :
			settings.WordLength = 8;
			break;
		}
		switch ( lcr & LCR_STOP_BITS ) {
		 case 0 :
			settings.StopBits = 1;
			break;
		 default :
			settings.StopBits = 2;
			break;
		}
		mcr = INPUT( isr_data->uart + MODEM_CONTROL_REGISTER );
		settings.Dtr = ( mcr & MCR_DTR ) != 0;
		settings.Rts = ( mcr & MCR_RTS ) != 0;
		settings.XonXoff = -1;
		settings.RtsCts = -1;
		settings.DtrDsr = -1;
asm pop es;
}

// Set() takes advantage of code used by the constructor to
// set up some of the UART parameters.

RS232Error PC8250::Set( long baud_rate,
						int parity,
				    int word_length,
				    int stop_bits )
{
    settings.Adjust( baud_rate,
				 parity,
				 word_length,
				 stop_bits,
				 UNCHANGED,
				 UNCHANGED,
				 UNCHANGED,
				 UNCHANGED,
				 UNCHANGED );
    return write_settings();
}

// This virtual routine is easily handled by a Queue member
// function.

int PC8250::TXSpaceFree( void )
{
//    if ( error_status < RS232_SUCCESS )
//	   return error_status;
		return isr_data->TXQueue.FreeCount();
}

// The same thing is true here.

int PC8250::RXSpaceUsed( void )
{
//    if ( error_status < RS232_SUCCESS )
//	   return error_status;
    return isr_data->RXQueue.InUseCount();
}

// The 8250 UART doesn't have an intelligent BREAK function,
// so we have to just sit on the line while the BREAK goes out.
// Hopefully the IdleFunction() can do something useful while
// this takes place.

int PC8250::Break( long milliseconds )
{
    int lcr;
    long timer;

//    if ( error_status < RS232_SUCCESS )
//		 return error_status;
		timer = ReadTime() + milliseconds;
		lcr = INPUT( isr_data->uart + LINE_CONTROL_REGISTER);
		lcr |= LCR_SET_BREAK;
		OUTPUT( isr_data->uart + LINE_CONTROL_REGISTER, lcr );
		while ( ReadTime() < timer )
		 IdleFunction();
		lcr &= ~LCR_SET_BREAK;
		OUTPUT( isr_data->uart + LINE_CONTROL_REGISTER, lcr );
		return RS232_SUCCESS;
}

// The four modem status functions just check the bits that
// were read in the last time a modem status interrupt took
// place, and return them to the calling routine.

int PC8250::Cd( void )
{
//    if ( error_status < RS232_SUCCESS )
//	   return error_status;
		return ( isr_data->modem_status & MSR_CD ) ? 1 : 0;
}

int PC8250::Ri( void )
{
//    if ( error_status < RS232_SUCCESS )
//	   return error_status;
    return ( isr_data->modem_status & MSR_RI ) ? 1 : 0;
}

int PC8250::Cts( void )
{
//    if ( error_status < RS232_SUCCESS )
//	   return error_status;
    return ( isr_data->modem_status & MSR_CTS ) ? 1 : 0;
}

int PC8250::Dsr( void )
{
//    if ( error_status < RS232_SUCCESS )
//		 return error_status;
    return ( isr_data->modem_status & MSR_DSR ) ? 1 : 0;
}

// The four line status routines are similar to the modem
// status routines in that they just check a bit in a data
// member.  However, they also have an optional parameter that
// can be used to clear the error flag.  This is just a matter of
// clearing the same bit.

int PC8250::ParityError( int reset )
{
    int return_value;

//    if ( error_status < RS232_SUCCESS )
//	   return error_status;
    return_value =
		 ( isr_data->line_status & LSR_PARITY_ERROR ) ? 1 : 0;
    if ( reset != UNCHANGED && reset != 0 ) {
	   CLI();
		 isr_data->line_status &= ~LSR_PARITY_ERROR;
	   STI();
    }
    return return_value;
}

int PC8250::BreakDetect( int reset )
{
    int return_value;

//    if ( error_status < RS232_SUCCESS )
//	   return error_status;
    return_value =
	   ( isr_data->line_status & LSR_BREAK_DETECT ) ? 1 : 0;
    if ( reset != UNCHANGED && reset != 0 ) {
	   CLI();
	   isr_data->line_status &= ~LSR_BREAK_DETECT;
	   STI();
    }
    return return_value;
}

int PC8250::FramingError( int reset )
{
    int return_value;

//    if ( error_status < RS232_SUCCESS )
//	   return error_status;
    return_value =
		( isr_data->line_status & LSR_FRAMING_ERROR ) ? 1 : 0;
    if ( reset != UNCHANGED && reset != 0 ) {
	   CLI();
	   isr_data->line_status &= ~LSR_FRAMING_ERROR;
	   STI();
    }
    return return_value;
}

int PC8250::HardwareOverrunError( int reset )
{
		int return_value;

//    if ( error_status < RS232_SUCCESS )
//	   return error_status;
    return_value =
		( isr_data->line_status & LSR_OVERRUN_ERROR ) ? 1 : 0;
    if ( reset != UNCHANGED && reset != 0 ) {
	   CLI();
	   isr_data->line_status &= ~LSR_OVERRUN_ERROR;
	   STI();
    }
    return return_value;
}

// This just reads in the status bit from the isr_data
// structure, and optionally clears it.

int PC8250::SoftwareOverrunError( int clear )
{
    int temp = isr_data->overflow;
		if ( clear )
	   isr_data->overflow = 0;
    return temp;
}

// The three handshaking functions all have approximately the
// same mode of operation.  If the setting parameter is set to
// UNCHANGED, they just return a boolean indicating whether or
// not handshaking is in effect.  If handshaking is being turned
// on or off, things become a little more complicated.  The
// major complication is that after setting the bits needed by
// the ISR to handshake, they also have to take action to make
// sure the control lines and XON/XOFF output are where they need
// to be to accurately get things started.

int PC8250::XonXoffHandshaking( int setting )
{
    if ( setting != UNCHANGED ) {
	   if ( setting )
		  isr_data->handshaking |= xon_xoff;
		 else {
		  isr_data->handshaking &= ~xon_xoff;
		  isr_data->blocked &= ~xon_xoff;
// If blocking, I need to send an XON
		  if ( isr_data->blocking & xon_xoff ) {
			 CLI();
			 if ( isr_data->send_handshake_char == -1 )
				isr_data->send_handshake_char = XON;
			 else
				isr_data->send_handshake_char = -1;
			 STI();
		  }
		  // Restart TX if I was blocked, or have to send and XON
		  jump_start( isr_data );
		  isr_data->blocking &= ~xon_xoff;
	   }
	   settings.XonXoff = ( setting != 0 );
    }
    return( ( isr_data->handshaking & xon_xoff ) != 0 );
}

int PC8250::RtsCtsHandshaking( int setting )
{
    int old_setting;

    if ( setting != UNCHANGED ) {
	   old_setting = isr_data->handshaking & rts_cts;
	   isr_data->handshaking &= ~rts_cts;
	   isr_data->blocking &= ~rts_cts;
	   isr_data->blocked &= ~rts_cts;
	   if ( setting ) {
		  Rts( 1 );
		  CLI();
		  if ( ( isr_data->modem_status & MSR_CTS ) == 0 )
			 isr_data->blocked |= rts_cts;
		  isr_data->handshaking |= rts_cts;
		  STI();
		  settings.Rts = REMOTE_CONTROL;
	   } else {
		  if ( old_setting )
			 Rts( 1 ); //If turning handshaking off, set RTS high
		  if ( isr_data->blocked == 0 )
			 jump_start( isr_data );
	   }
	   settings.RtsCts = ( setting != 0 );
    }
    return( ( isr_data->handshaking & rts_cts ) != 0 );
}

int PC8250::DtrDsrHandshaking( int setting )
{
    int old_setting;

    if ( setting != UNCHANGED ) {
	   old_setting = isr_data->handshaking & dtr_dsr;
	   isr_data->handshaking &= ~dtr_dsr;
	   isr_data->blocking &= ~dtr_dsr;
	   isr_data->blocked &= ~dtr_dsr;
	   if ( setting ) {
		  Dtr( 1 );
			CLI();
		  if ( ( isr_data->modem_status & MSR_DSR ) == 0 )
			 isr_data->blocked |= dtr_dsr;
		  isr_data->handshaking |= dtr_dsr;
		  STI();
		  settings.Dtr = REMOTE_CONTROL;
	   } else {
		  if ( old_setting )
			 Dtr( 1 ); //If turning handshaking off, set RTS high
		  if ( isr_data->blocked == 0 )
			 jump_start( isr_data );
	   }
	   settings.DtrDsr = ( setting != 0 );
    }
    return( ( isr_data->handshaking & dtr_dsr ) != 0 );
}

// Just reading the state of the control line is relatively
// easy.  The setting returned is just the stored value in the
// settings element.  However, both of the next two routines have
// to handle setting or clearing the line as well.  This only
// gets complicated if handshaking is turned on.  If it is, these
// routines refuse to play with the control lines.

int PC8250::Dtr( int setting )
{
    int mcr;

    if ( setting != UNCHANGED ) {
	   if ( isr_data->handshaking & dtr_dsr )
		  return PC8250_HANDSHAKE_LINE_IN_USE;
	   else {
		  settings.Dtr = setting;
		  CLI();
		  mcr = INPUT( isr_data->uart + MODEM_CONTROL_REGISTER );
		  if ( setting )
			 mcr |= MCR_DTR;
		  else
			 mcr &= ~MCR_DTR;
		  OUTPUT( isr_data->uart + MODEM_CONTROL_REGISTER, mcr );
			STI();
	   }
    }
    return settings.Dtr;
}

int PC8250::Rts( int setting )
{
    int mcr;

    if ( setting != UNCHANGED ) {
	   if ( isr_data->handshaking & rts_cts )
		  return PC8250_HANDSHAKE_LINE_IN_USE;
	   else {
		  settings.Rts = setting;
		  CLI();
		  mcr = INPUT( isr_data->uart + MODEM_CONTROL_REGISTER );
		  if ( setting )
			 mcr |= MCR_RTS;
		  else
			 mcr &= ~MCR_RTS;
		  OUTPUT( isr_data->uart + MODEM_CONTROL_REGISTER, mcr );
		  STI();
	   }
    }
    return settings.Rts;
}

// PeekBuffer uses the class Queue function to read as many
// bytes as possible from the RXBuffer.

int PC8250::PeekBuffer( void *buffer, unsigned int count )
{
//    if ( error_status < RS232_SUCCESS )
//	   return error_status;
    ByteCount =
		isr_data->RXQueue.Peek( (unsigned char *) buffer, count );
//    ( (char *) buffer )[ ByteCount ] = '\0';
    return RS232_SUCCESS;
}

// The next two functions just return a count using a Queue
// class primitive function.

int PC8250::RXSpaceFree( void )
{
//    if ( error_status < RS232_SUCCESS )
//	   return error_status;
    return isr_data->RXQueue.FreeCount();
}

int PC8250::TXSpaceUsed( void )
{
//    if ( error_status < RS232_SUCCESS )
//	   return error_status;
    return isr_data->TXQueue.InUseCount();
}

// Flushing the TX buffer is easy when using the Queue class
// primitive.

int PC8250::FlushTXBuffer( void )
{
//    if ( error_status < RS232_SUCCESS )
//	   return error_status;
asm push es;
		CLI();
		isr_data->TXQueue.Clear();
		STI();
asm pop es;
		return RS232_SUCCESS;
}
/*
// The debug output routine has three possible modes.  If the
// buffer passed to it is a null, it means it should just return
// the total number of lines used by the the output, which is 6
// plus the number used by the base class.  If the line number
// requested is less than where we start, the request is passed
// up the line to the base class.  Finally, if it is one of our
// lines, the buffer is formatted and returned to the calling
// routine.

int PC8250::FormatDebugOutput( char *buffer, int line_number )
{
    if ( buffer == 0 )
	   return( first_debug_output_line +  6 );
    if ( line_number < first_debug_output_line )
	   return RS232::FormatDebugOutput( buffer, line_number );
    switch( line_number - first_debug_output_line ) {
	   case 0 :
		  sprintf( buffer,
				 "Derived class: PC8250   "
				 "UART: %04x  "
				 "Overflow: %1d  "
				 "TX Running: %1d  "
				 "Line Status: %02x",
				 isr_data->uart,
				 ( isr_data->overflow ) ? 1 : 0,
				 ( isr_data->tx_running ) ? 1 : 0,
				 isr_data->line_status );
		  break;
	   case 1 :
			sprintf( buffer,
				 "TX Head, Tail, Count %4d %4d %4d  "
				 "RX Head,Tail,Count %4d %4d %4d",
				 isr_data->TXQueue.Head(),
				 isr_data->TXQueue.Tail(),
				 isr_data->TXQueue.InUseCount(),
				 isr_data->RXQueue.Head(),
				 isr_data->RXQueue.Tail(),
				 isr_data->RXQueue.InUseCount() );
		  break;
	   case 2 :
		  sprintf( buffer,
				 "Counts: TX: %5u  RX: %5u  MS: %5u  LS: %5u  "
				 "CTS/DSR/RI/CD: %d%d%d%d",
				 isr_data->tx_int_count,
				 isr_data->rx_int_count,
				 isr_data->ms_int_count,
				 isr_data->ls_int_count,
				 ( isr_data->modem_status & MSR_CTS ) ? 1 : 0,
				 ( isr_data->modem_status & MSR_DSR ) ? 1 : 0,
				 ( isr_data->modem_status & MSR_RI ) ? 1 : 0,
				 ( isr_data->modem_status & MSR_CD ) ? 1 : 0 );
		  break;
	   case 3 :
		  sprintf( buffer,
				 "Handshake DTR/RTS/XON : %d%d%d  "
				 "Blocking: %d%d%d  "
				 "Blocked: %d%d%d  "
				 "Handshake char: %04x",
				 ( isr_data->handshaking & dtr_dsr ) ? 1 : 0,
				 ( isr_data->handshaking & rts_cts ) ? 1 : 0,
				 ( isr_data->handshaking & xon_xoff ) ? 1 : 0,
				 ( isr_data->blocking & dtr_dsr ) ? 1 : 0,
				 ( isr_data->blocking & rts_cts ) ? 1 : 0,
				 ( isr_data->blocking & xon_xoff ) ? 1 : 0,
				 ( isr_data->blocked & dtr_dsr ) ? 1 : 0,
				 ( isr_data->blocked & rts_cts ) ? 1 : 0,
				 ( isr_data->blocked & xon_xoff ) ? 1 : 0,
				 isr_data->send_handshake_char );
		  break;
		 case 4 :
		  sprintf( buffer,
				 "Parity Err: %d  "
				 "Break Det: %d  "
				 "Overrun Err: %d  "
				 "Framing Err: %d  "
				 "FIFO Setting: %2d",
				 ( isr_data->line_status & LSR_PARITY_ERROR ) ? 1 : 0,
				 ( isr_data->line_status & LSR_BREAK_DETECT ) ? 1 : 0,
				 ( isr_data->line_status & LSR_OVERRUN_ERROR ) ? 1 : 0,
				 ( isr_data->line_status & LSR_FRAMING_ERROR ) ? 1 : 0,
				 fifo_setting );
		  break;
	   case 5 :
		  char *uart_name;
		  switch( isr_data->uart_type ) {
			 case UART_8250  : uart_name = "8250";    break;
			 case UART_16550 : uart_name = "16550";   break;
			 default         : uart_name = "Unknown"; break;
		  }
			sprintf( buffer,
				 "Uart type: %-7s",
				 uart_name );
		  break;
	   default :
		  return RS232_ILLEGAL_LINE_NUMBER;
    }
    return RS232_SUCCESS;
}
*/
// Just like the debug format routine, ErrorName has to pass
// most requests up the line to the base class, saving only a few
// for it to respond to.

/*
char * PC8250::ErrorName( int error )
{
	 if ( error < RS232_NEXT_FREE_ERROR && error >= RS232_ERROR )
		return RS232::ErrorName( error );
	 if ( error < RS232_NEXT_FREE_WARNING && error >= RS232_WARNING )
		return RS232::ErrorName( error );
		if ( error >= RS232_SUCCESS )
		return RS232::ErrorName( error );
	 switch ( error ) {
		case PC8250_UART_NOT_FOUND        : return( "UART not found" );
		case PC8250_HANDSHAKE_LINE_IN_USE : return( "Handshake line in use" );
		default                           : return( "Undefined error" );
	 }
}
*/

#endif