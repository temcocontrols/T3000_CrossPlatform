// ********************** START OF PC8250.H **********************
//
//
// This header file has all of the definitions and prototypes
// needed to use the PC8250 class.  This file should be included
// by any code that needs to access this class.


#ifndef _PC8250_DOT_H
#define _PC8250_DOT_H

#include "rs232.h"
#include "queue.h"
#include "pcirq.h"
#include "_8250.h"

extern void *newalloc(long size);
extern void newdelete(void *ptr);
// A few type definitions used with this class.

enum PC8250Error {
	   PC8250_UART_NOT_FOUND        = RS232_NEXT_FREE_ERROR,
	   PC8250_NEXT_FREE_ERROR,
	   PC8250_HANDSHAKE_LINE_IN_USE = RS232_NEXT_FREE_WARNING,
	   PC8250_NEXT_FREE_WARNING };

enum UARTType { UART_8250, UART_16550, UART_UNKNOWN };

enum handshaking_bits {  dtr_dsr = 1, rts_cts = 2, xon_xoff = 4 };

class PC8250;

// The ISR data is contained in a conventional C structure instead of
// a class.  The ISR is much easier to work with as a normal C function
// instead of a member function, and as such it wants to work with
// structures instead of classes.

struct isr_data_block {
	 int      uart;
	 UARTType uart_type;
	 char     port_number;
	 char     media;
	 char     task;
	 volatile int          overflow;
	 volatile char         tx_running;
	 volatile unsigned int rx_int_count;
	 volatile unsigned int tx_int_count;
	 volatile unsigned int ms_int_count;
	 volatile unsigned int ls_int_count;
	 volatile unsigned int line_status;
	 unsigned int          handshaking;
	 volatile unsigned int blocking;
	 volatile unsigned int blocked;
	 volatile int          send_handshake_char;
	 volatile unsigned int modem_status;
	 Queue TXQueue;
	 Queue RXQueue;
	 char                      rx_control_char;
	 char                      tr_index;
	 void							  *recframe;
	 int                       length;
	 char                     *ptr;
};

// The Handler class is used when multiple ports share an
// interrupt, such as on a multiport board or a Microchannel bus.

class Handler {
    public :
	   virtual RS232Error AddPort( RS232PortName port_name,
							 struct isr_data_block *data ) = 0;
	   virtual void DeletePort( RS232PortName port_name ) = 0;
};

class PC8250 : public RS232
{
	 public:
		struct isr_data_block *isr_data;
	 private :
		irq_name irq;
		int interrupt_number;
//        int first_debug_output_line;
		int fifo_setting;
		Handler *interrupt_handler;

		void check_uart( void );
		void read_settings( void );
		RS232Error write_settings( void );
		void set_uart_address_and_irq( Handler *handler,
								 int uart_address,
								 irq_name irq_line );
		virtual int read_buffer( char *buffer,
							unsigned int count );
//		virtual int write_buffer( char *buffer,
//							 unsigned int count = -1 );
//	   virtual int read_byte( void );
		virtual int write_byte( int c );
		void check_rx_handshaking( void );

	 public :
		virtual int write_buffer( char *buffer,
							 unsigned int count = -1, int type = 0 );
		virtual int read_byte( void );
      void resettxrunning(void){isr_data->tx_running=0;}

		PC8250( RS232PortName port_name,
			 long baud_rate = UNCHANGED,
			 char parity = UNCHANGED,
			 int word_length = UNCHANGED,
			 int stop_bits = UNCHANGED,
			 int dtr = DISABLE,
			 int rts = DISABLE,
			 int xon_xoff = DISABLE,
			 int rts_cts = DISABLE,
			 int dtr_dsr = DISABLE,
			 Handler *handler = 0,
			 int uart_address = 0,
			 irq_name irq_line = ILLEGAL_IRQ );
		 int setpc8250(
				 int t,
         RS232PortName port_name,
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
				 irq_name irq_line
				);
     void discon( void );
		 virtual ~PC8250( void );
	   virtual RS232Error Set( long baud_rate = UNCHANGED,
						  int parity = UNCHANGED,
						  int word_length = UNCHANGED,
						  int stop_bits = UNCHANGED );
	   virtual int TXSpaceFree( void );
	   virtual int RXSpaceUsed( void );
	   virtual int Break( long milliseconds = 300 );
	   virtual int Cd( void );
	   virtual int Ri( void );
	   virtual int Cts( void );
	   virtual int Dsr( void );
	   virtual int ParityError( int clear = UNCHANGED );
	   virtual int BreakDetect( int clear = UNCHANGED );
	   virtual int FramingError( int clear = UNCHANGED );
	   virtual int HardwareOverrunError( int clear = UNCHANGED );
	   virtual int SoftwareOverrunError( int clear = UNCHANGED );
	   virtual int XonXoffHandshaking( int setting = UNCHANGED );
	   virtual int RtsCtsHandshaking( int setting = UNCHANGED );
	   virtual int DtrDsrHandshaking( int setting = UNCHANGED );
	   virtual int Dtr( int setting = UNCHANGED );
	   virtual int Rts( int setting = UNCHANGED );
	   virtual int PeekBuffer( void *buffer, unsigned int count );
	   virtual int RXSpaceFree( void );
	   virtual int TXSpaceUsed( void );
	   virtual int FlushRXBuffer( void );
	   virtual int FlushTXBuffer( void );
//	   virtual char * ErrorName( int error );
/*	   virtual int FormatDebugOutput( char *buffer = 0,
							    int line_number = -1 ); */
		void *operator new(size_t size){return(newalloc((long)size));};
      void operator delete(void *ptr){newdelete(ptr);};
};

#endif // #ifndef _PC8250_DOT_H

// ************************ END OF PC8250.H ***********************


