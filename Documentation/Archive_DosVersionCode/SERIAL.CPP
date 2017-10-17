//**********************************************
//                                             *
//	Serial.cpp - Member functions for      	   *
//	Serial.h                                   *
//                                             *
//**********************************************
#ifdef SERIAL_COMM

#include <windows.h>
#include <graphics.h>
#include "ggrid.h"
#include "graph.h"
#include "serial.h"
#include "rs232.h"
#include "mtkernel.h"
#include "_msdos.h"
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <bios.h>
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

extern void chbkg(int lx, int ly, int width, int bkgnd, int frgnd, int unchangecol=127, int height = 0);
extern void *DisplayMessage(int lx, int ly, int rx, int ry, char *title, char *message, GWindow **Er1, int fcolor=Black, GWindow *Er2=NULL, long delay=0);
extern void DeleteMessage(GWindow *p);

extern int dtr;

void communication_sign(long, long);

int SERIAL_EXIT, MODEM_EXIT, RS485_EXIT;
//char carry_detect;

//extern Comm_Info comm_info[MAX_COMM_INFO];
extern Comm_Info *comm_info;

char RS485_PIC_mask;
char sleep_modem;
//char indsign;     //,showsign;
int xsign,ysign;
long data_const, data_length_const;
int disconnect_time=-1;
char enable_ints;

char huge *trying_mess = "Trying on COM0 with IRQ0 !";
char huge *err_inst_text = " Error. COM   not installed! ";

typedef struct {
	RS232PortName port_name;
	irq_name irq_port;
	} Port_list;

Port_list port_list[20] = { {COM1, IRQ4}, {COM2, IRQ3}, {COM3, IRQ5}, {COM4, IRQ3},
		{COM3, IRQ4}, {COM3, IRQ7}, {COM1, IRQ5}, {COM2, IRQ5}, {COM4, IRQ5},
		{COM1, IRQ3}, {COM1, IRQ6}, {COM1, IRQ7}, {COM2, IRQ4},
		{COM2, IRQ6}, {COM2, IRQ7}, {COM3, IRQ3},  {COM3, IRQ6}, {COM4, IRQ4},
		{COM4, IRQ6}, {COM4, IRQ7} };


Serial :: Serial( byte c_port, int p_no )
{
	activity = FREE;
//	media = m_type;
	com_port = c_port;
	port_number = p_no;
	media = comm_info[com_port].connection;
//	if( media == SERIAL_LINK )	task_number = SERIAL;
//	if( media == MODEM_LINK )	task_number = MODEM;
	Set_mode( SLAVE );
	port = NULL;
	modem_obj = NULL;
	ser_data = NULL;
	connection_established = 0;
	port_status = NOT_INSTALLED;
	modem_present = 0;
	modem_active = 0;
};


Serial::~Serial()
{
	Delete_port();
};

long Serial::ReadBaudRate( void )
{
 if( media == SERIAL_LINK || media == RS485_LINK)
 {
	if(port)
	  return port->ReadBaudRate();
	else
	  return 2400;
 }
 else
	if(modem_obj)
	  return modem_obj->local_baud_rate;
}

void Serial::FlushRXbuffer()
{
	asm push es;
	if(port)
		port->FlushRXBuffer();
	asm pop es;
}

void Serial::FlushTXbuffer()
{
	asm push es;
	if(port)
		port->FlushTXBuffer();
	asm pop es;
}

void Serial::Set_mode( int smode )
{
  Routing_table[port_number].port_status_vars.mode = smode;
}

int Serial::Read_mode( void )
{
  return (Routing_table[port_number].port_status_vars.mode);
}

void Serial::Install_port()
{
  port_status = NOT_INSTALLED;
  modem_present = 0;
  modem_active = 0;
  activity = FREE;
  Set_mode( MASTER );
  if( comm_info[com_port].port_name!=COM0 )
  {
	if( !( port = new PC8250( comm_info[com_port].port_name, comm_info[com_port].baudrate, 'N', 8, 1,
		media==RS485_LINK?dtr:DISABLE, media==RS485_LINK?1:DISABLE, DISABLE, DISABLE, DISABLE, 0, 0, comm_info[com_port].int_name ) ) )
	{
			 mxyputs( 24,10, "\nMemory allocation error !!!\n");
			 port_status = NOT_INSTALLED;
	}
	else
	{
			if( port->ErrorStatus() != RS232_SUCCESS )
			{
					port_status = NOT_INSTALLED;
					err_inst_text[11] = com_port+0x31;
					DisplayMessage(20, 7, 60, 11, NULL, err_inst_text,NULL, Blue, NULL, 2000);
/*
					if( media == MODEM_LINK )
						DisplayMessage(20, 7, 60, 11, NULL, " Error opening MODEM port ! ",NULL, Blue, NULL, 1100);
					else
						DisplayMessage(20, 7, 60, 11, NULL, " Error opening port COM  ! ",NULL, Blue, NULL, 1000);
*/
			}
			else
			{
			  port->isr_data->media = media;
			  port->isr_data->port_number = port_number;
			  port_status = INSTALLED;
			}
	}
//	if(port_status == INSTALLED && media != RS485_LINK)
	if( port_status == INSTALLED )
	{
	 if( media!=ASYNCRON_LINK )
	 {
	  if(ser_data)
	  {
		mfarfree(ser_data);
		ser_data = NULL;
	  }
	  mfarmalloc(&ser_data, SERIAL_BUF_SIZE);
	  ser_pool.init_pool(ser_data, SERIAL_BUF_SIZE);
    }
	}
	if( media == MODEM_LINK && port_status == INSTALLED )
	{
		if( ( modem_obj = new Modem( *port, "Generic Modem", this ) ) == NULL )
		{
			 DisplayMessage(20, 7, 60, 11, NULL, " Unable to install the modem ! ",NULL, Blue,NULL,1500);
			 modem_obj = NULL;
			 modem_present = 0;
		}
		else
		{
			modem_present = 1;
			if( ( modem_status = modem_obj->Initialize() ) != MODEM_SUCCESS )
			{
				 modem_active = 0;
             port_status = NOT_INSTALLED;
			}
			else
			{
				modem_active = 1;
			}
		}
		Delay(1000);
		port->FlushRXBuffer();
		port->FlushTXBuffer();
	}
  }
  Set_mode( SLAVE );
}

void Serial::Delete_port()
{
	int i = 0;
	if( media == MODEM_LINK && modem_active )
	{
		if ( Read_mode()==SLAVE )
		{
			i = 1;
			Set_mode(MASTER);
		}
		if( ( modem_status = modem_obj->Disconnect() ) != MODEM_SUCCESS )
		{
		}
		modem_active = 0;
		if ( i )
		{
			Set_mode(SLAVE);
		}
	}
	if( modem_obj != NULL ) delete modem_obj;
	modem_present = 0;
	modem_obj = NULL;
	if( port != NULL ) delete port;
	port_status = NOT_INSTALLED;
	port=NULL;
	activity = FREE;
	if(ser_data)
		mfarfree(ser_data);
	ser_data = NULL;
}


//char * Serial::Error_Name( RS232Error error )
char *ErrorName( RS232Error error )
{
	switch ( error ) {
		case RS232_SUCCESS                 : return( "Success" );
		case RS232_WARNING                 : return( "General Warning" );
		case RS232_FUNCTION_NOT_SUPPORTED  : return( "Function not supported" );
		case RS232_TIMEOUT                 : return( "Timeout" );
		case RS232_ILLEGAL_BAUD_RATE       : return( "Illegal baud rate" );
		case RS232_ILLEGAL_PARITY_SETTING  : return( "Illegal parity setting" );
		case RS232_ILLEGAL_WORD_LENGTH     : return( "Illegal word length" );
		case RS232_ILLEGAL_STOP_BITS       : return( "Illegal stop bits" );
		case RS232_ILLEGAL_LINE_NUMBER     : return( "Illegal line number" );
		case RS232_NO_TERMINATOR           : return( "No terminator" );
		case RS232_NO_MODEM_RESPONSE       : return( "No modem response" );
		case RS232_DTR_NOT_SUPPORTED       : return( "DTR control not supported" );
		case RS232_RTS_NOT_SUPPORTED       : return( "RTS control not supported" );
		case RS232_RTS_CTS_NOT_SUPPORTED   : return( "RTS/CTS handshaking not supported" );
		case RS232_DTR_DSR_NOT_SUPPORTED   : return( "DTR/DSR handshaking not supported" );
		case RS232_XON_XOFF_NOT_SUPPORTED  : return( "XON/XOFF handshaking not supported" );
		case RS232_ERROR                   : return( "General Error" );
		case RS232_IRQ_IN_USE              : return( "IRQ line in use" );
		case RS232_PORT_NOT_FOUND          : return( "Port not found" );
		case RS232_PORT_IN_USE             : return( "Port in use" );
		case RS232_ILLEGAL_IRQ             : return( "Illegal IRQ" );
		case RS232_MEMORY_ALLOCATION_ERROR : return( "Memory allocation error" );
		case RS232_REJECT                  : return( "Request rejected" );
		case RS232_PANEL_OFF 				  :
		case PC8250_UART_NOT_FOUND         : return( "UART not found" );
		case PC8250_HANDSHAKE_LINE_IN_USE  : return( "Handshake line in use" );

		case T3000_FAIL		              : return( "T3000 communication failed" );
		case T3000_SYNC_ERROR	           : return( "T3000 syncronization error" );
		case T3000_DESTINATION_ERROR       : return ( "Destination error" );
		case T3000_SOURCE_ERROR	           : return( "Source error " );
		case T3000_COMMAND_ERROR           : return( "Command error" );
		case T3000_CHECKSUM_ERROR          : return( "Checksum error" );
		case CRC_BAD                       : return( "CRC error" );
		case COMM_ERROR                    : return( "Communication error" );
		case UNRECOVERABLE_ERROR           : return( "Unrecoverable error" );
		case USER_ABORT                    : return( "User Abort !!!" );

		default                            : return( "Undefined error" );
	}
}

extern int mode_text ;

void set_PIC_mask(byte *PIC_mask)
{
//	byte pic_mask;
//	pic_mask = PIC_mask;
	byte mask=0x02;
	asm {
			in al, 21h
			or al, BYTE PTR mask
			out 21h, al
		 }
	enable_ints++;
	if(comm_info[MOUSE_COMM_ENTRY].int_name !=  ILLEGAL_IRQ)
	{
		if( comm_info[MOUSE_COMM_ENTRY].int_name < IRQ8 )
		{
		 mask = 1<<(comm_info[MOUSE_COMM_ENTRY].int_name);
		 asm {
			in al, 21h
		 }
//		 *PIC_mask = _AL;
		 asm {
			or al, BYTE PTR mask
			out 21h, al
		 }
		}
		else
		{
		 mask=1<<(comm_info[MOUSE_COMM_ENTRY].int_name - IRQ8);
		 asm {
			in al, 0a1h
			 }
//		 *PIC_mask = _AL;
		 asm {
			or al, BYTE PTR mask
			out 0a1h, al
		 }
		}
	}
}

void Serial::Set_PIC_mask()
{
	set_PIC_mask(&PIC_mask);
}

void reset_PIC_mask(byte PIC_mask)
{
//	byte pic_mask;
//	pic_mask = PIC_mask;
  byte mask=~0x02;
  if( !(--enable_ints) )
  {
	asm {
			in  al, 21h
			and al, BYTE PTR mask
			out 21h, al
		 }
	if(comm_info[MOUSE_COMM_ENTRY].int_name !=  ILLEGAL_IRQ)
	{
	 if( comm_info[MOUSE_COMM_ENTRY].int_name < IRQ8 )
	 {
		 mask=~( 1<<(comm_info[MOUSE_COMM_ENTRY].int_name)) ;
		 asm {
			in  al, 21h
			and al, BYTE PTR mask
			out 21h, al
		 }
	 }
	 else
	 {
		 mask=~( 1<<(comm_info[MOUSE_COMM_ENTRY].int_name - IRQ8)) ;
		 asm {
			in  al, 0a1h
			and al, BYTE PTR mask
			out 0a1h, al
		 }
//	  _AL = PIC_mask;
//	  asm out 0a1h, al
	 }
	}
  }
}

void Serial::Reset_PIC_mask()
{
	reset_PIC_mask(PIC_mask);
}

void communication_sign(long done, long total)
{
 char buf[8];
 if(xsign)
 {
	ltoa(done*100l/total, buf, 10);
	strcat(buf,"%");
	if(mode_text)
		mxyputs(xsign,ysign,buf,Lightblue,Black);
	else
	{
		chbkg(xsign, ysign, 32,  Lightblue, Lightblue);
		outtextxy(xsign, ysign, buf);
	}
 }
}
#endif
