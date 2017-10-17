// ******************** START OF ISR_8250.CPP ********************
// All of the code used in the 8250 interrupt service
// routine is found in this file.  The Queue class inline
// functions are pulled in from QUEUE.H

#ifdef SERIAL_COMM


#include <windows.h>
//#include <conio.h>
#include "t3000def.h"
#include "pc8250.h"
#include "_pc8250.h"
#include "ascii.h"
#include "rs485.h"
#include "ptp.h"
#include "router.h"

#define word word

//#define TEST

//#pragma inline

extern char xbuf[10];
extern int mode_text;
int xerr;
//extern char number_rings;
extern int dtr;
extern int  Station_NUM;
extern char ring_sequence[];
extern char huge *lin_text;

extern char table_crc8[256];
extern unsigned int table_crc16[256];
int int_occured = 0;

// Prototypes for the internal handlers called by the ISR.

void handle_modem_status_interrupt( struct isr_data_block *data );
void handle_tx_interrupt( struct isr_data_block *data );
void handle_rx_interrupt( struct isr_data_block *data );

#ifdef TEST
char far tempor[5000];
int far tempx,tempy,tempor_ind,MAXtempor=5000;
#endif

// This is the main body of the 8250 interrupt handler.  It
// sits in a loop, repeatedly reading the Interrupt ID
// Register, and dispatching a handler based on the
// interrupt type.  The line status interrupt is so simple
// that it doesn't merit its own handler.

void isr_8250( struct isr_data_block * data )
{
	int_occured++;
	STI();
	for ( ; ; )
	{
		switch( INPUT( data->uart + INTERRUPT_ID_REGISTER ) & 7 )
		{
			case IIR_MODEM_STATUS_INTERRUPT :
					handle_modem_status_interrupt( data );
					break;
			case IIR_TX_HOLDING_REGISTER_INTERRUPT :
					handle_tx_interrupt( data );
					break;
			case IIR_RX_DATA_READY_INTERRUPT :
					handle_rx_interrupt( data );
					break;
			case IIR_LINE_STATUS_INTERRUPT :
					asm push es;
					data->ls_int_count++;
					data->line_status |= INPUT( data->uart + LINE_STATUS_REGISTER );
					if( data->line_status&LSR_OVERRUN_ERROR || data->line_status&LSR_FRAMING_ERROR ||
							data->line_status&LSR_PARITY_ERROR)
					{
					  Routing_table[data->port_number].port_status_vars.SilenceTimer=0;
					  Routing_table[data->port_number].port_status_vars.ReceiveError=TRUE;
					  Routing_table[data->port_number].port_status_vars.EventCount++;
					}
	        asm pop es;
					break;
			default :
					int_occured--;
					return;
		}
	}
}

// The modem status interrupt handler has to do three
// things.  It has to handle RTS/CTS handshaking.  It has
// to handle DTR/DSR handshaking, and it has to update the
// modem_status member of the isr_data structure.

void handle_modem_status_interrupt( struct isr_data_block *data )
{
	 data->modem_status =
		 (unsigned int)
					 INPUT( data->uart + MODEM_STATUS_REGISTER );
	 if ( data->handshaking & rts_cts )
			if ( data->modem_status & MSR_DELTA_CTS ) // Has CTS changed?
				if ( data->modem_status & MSR_CTS ) {
					 if ( data->blocked & rts_cts ) {
			 data->blocked &= ~rts_cts;
			 jump_start( data );
					 }
				} else {
					 if ( !( data->blocked & rts_cts ) )
							data->blocked |= rts_cts;
				}
	 if ( data->handshaking & dtr_dsr )
	 if ( data->modem_status & MSR_DELTA_DSR )
				if ( data->modem_status & MSR_DSR ) {
					 if ( data->blocked & dtr_dsr ) {
							data->blocked &= ~dtr_dsr;
							jump_start( data );
					 }
		 } else {
		if ( !( data->blocked & dtr_dsr ) )
							data->blocked |= dtr_dsr;
				}
	 if(data->media == MODEM_LINK)
	 {
		 Routing_table[data->port_number].port_status_vars.physical_connection_state = data->modem_status & MSR_CD ? 1 : 0;
		 if( !(data->modem_status & MSR_CD) )
			resume( Routing_table[data->port_number].task );
	 }
/*
	 if ( data->modem_status & MSR_RI )
	 {
		 ring_counts++;
		 ring_reset_time=(number_rings-ring_counts)<<7;
	 }
*/
}

// The TX interrupt is fairly simple.  All it has to do is
// transmit the next character, if one is available.  Depending
// on whether or not a character is available, it will set or
// clear the tx_running member.  Note that here and in
// jump_start(), the handshake_char gets first shot at going
// out.  This is normally an XON or XOFF.

void handle_tx_interrupt( struct isr_data_block *data )
{
	 int c,i;
	 asm push es;
	 if ( data->send_handshake_char >= 0 )
	 {
			OUTPUT( data->uart + TRANSMIT_HOLDING_REGISTER,
					 data->send_handshake_char );
			data->send_handshake_char = -1;
	 }
	 else
		if ( data->blocked )
		{
			 data->tx_running = 0;
		}
		else
		{
/*
			c = data->TXQueue.Remove();
			if ( c >= 0 )
			{
				OUTPUT( data->uart + TRANSMIT_HOLDING_REGISTER, c );
			}
*/
			c = data->TXQueue.Remove();
			if ( c >= 0 )
			{
				if( data->uart_type == UART_16550 )
					i = 15;
				else
					i = 0;
//				CLI();
/*
#ifdef TEST
			tempor[0]=(c>>4);
			if(tempor[0]>9)
				 tempor[0]+=65;
			else
				 tempor[0]+=48;
			tempor[1]=(c&0x0F);
			if(tempor[1]>9)
				 tempor[1]+=65;
			else
				 tempor[1]+=48;
			mxyputs(tempx,tempy,tempor, BLACK, WHITE);
			tempx+=3;
#endif
*/
#ifdef TEST
			if( tempor_ind < MAXtempor )
			{
				tempor[tempor_ind++]=c;
			}
#endif
				OUTPUT( data->uart + TRANSMIT_HOLDING_REGISTER, c );
				while( i-- > 0 )
				{
				 c = data->TXQueue.Remove();
				 if ( c >= 0 )
				 {
/*
#ifdef TEST
			tempor[0]=(c>>4);
			if(tempor[0]>9)
				 tempor[0]+=65;
			else
				 tempor[0]+=48;
			tempor[1]=(c&0x0F);
			if(tempor[1]>9)
				 tempor[1]+=65;
			else
				 tempor[1]+=48;
			mxyputs(tempx,tempy,tempor, BLACK, WHITE);
			tempx+=3;
#endif
*/
#ifdef TEST
			if( tempor_ind < MAXtempor )
			{
				tempor[tempor_ind++]=c;
			}
#endif
					OUTPUT( data->uart + TRANSMIT_HOLDING_REGISTER, c );
				 }
				 else
				 {
					break;
				 }
				}
//				STI();
			}
      else
			{
			 data->tx_running = 0;
			 if(data->media == RS485_LINK)
			 {
/*
				c=0xA0;
				while( !(INPUT(data->uart + LINE_STATUS_REGISTER)&0x40) && c)
				{
				 c--;
				};  //TRANSMITTER_EMPTY
*/
//				c=0x10;
//        while(c-->0);
				for(c=0;c<0x20;c++);   // delay for last char
				CLI();
				c = INPUT( data->uart + MODEM_CONTROL_REGISTER );
//				c |= MCR_DTR;
				if(dtr)
					c |= MCR_DTR;
				else
					c &= ~MCR_DTR;
				OUTPUT( data->uart + MODEM_CONTROL_REGISTER, c );
				if( tasks[data->task].status == SLEEPING )
					 tasks[data->task].status = READY;
//					 asm mov word ptr DGROUP:_tasks[bx],1
				OUTPUT( data->uart + INTERRUPT_ENABLE_REGISTER,
				 IER_RX_DATA_READY + IER_MODEM_STATUS + IER_LINE_STATUS );
				STI();
			 }
			 else
			 {
//			  disable();
				if( tasks[data->task].status == SLEEPING )
					 tasks[data->task].status = READY;
//			  enable();
				OUTPUT( data->uart + INTERRUPT_ENABLE_REGISTER,
				 IER_RX_DATA_READY + IER_MODEM_STATUS + IER_LINE_STATUS );
			 }
/*
			 OUTPUT( data->uart + INTERRUPT_ENABLE_REGISTER,
				 IER_RX_DATA_READY + IER_MODEM_STATUS + IER_LINE_STATUS );
*/
			}
		}
	 asm pop es;
}

// The RX interrupt handler is divided into two nearly
// independent sections.  The first section just reads in the
// character that has just been received and stores it in a
// buffer.  If the UART type is a 16550, up to 16 characters
// might be read in.  The next section of code handles the
// possibility that a handshaking trigger has just occurred,
// modifies any control lines or sends an XOFF as needed.

//int nr;
void handle_rx_interrupt( struct isr_data_block *data )
{
//	 int mcr;
//	 int lsr;
	 int insert;
	 int c_lsr_mcr;
	 register PORT_STATUS_variables *ps;

	 asm push es;
// The receive data section
	 for ( ; ; )
	 {
			c_lsr_mcr = INPUT( data->uart + RECEIVE_BUFFER_REGISTER );

#ifdef TEST1
			if(c_lsr_mcr==0x55)
			{
				 tempy++;
				 if(tempy>=24) tempy=1;
				 tempx=1;
			 lin_text[80];
			 mxyputs(tempx,tempy,lin_text);
			 lin_text[80]=' ';
			}

			tempor[0]=(c_lsr_mcr>>4);
			if(tempor[0]>9)
				 tempor[0]+=55;
			else
				 tempor[0]+=48;
			tempor[1]=(c_lsr_mcr&0x0F);
			if(tempor[1]>9)
				 tempor[1]+=55;
			else
				 tempor[1]+=48;
			mxyputs(tempx,tempy,tempor, BLACK, WHITE  );
			tempx+=3;
#endif
#ifdef TEST
			if( tempor_ind < MAXtempor )
			{
				tempor[tempor_ind++]=c_lsr_mcr;
			}
#endif

			if ( data->handshaking & xon_xoff )
			{
				 if ( c_lsr_mcr == XON )
				 {
						data->blocked &= ~xon_xoff;
						jump_start( data );
						asm pop es;
						return;
				 }
				 else
					if ( c_lsr_mcr == XOFF )
					{
						data->blocked |= xon_xoff;
								 asm pop es;
						return;
					}
			}
//		 insert=1;
		if(data->media == RS485_LINK )
	  {
			ps = &Routing_table[data->port_number].port_status_vars;
		  if(!data->rx_int_count)
		  {
//			if( ps->ReceiveFrameStatus == RECEIVE_FRAME_IDLE  && ps->validint)
			if( ps->validint )
			{
				data->rx_int_count=1;
//				insert=0;
				if( ps->ReceiveError==TRUE )
				{
/*
if (mode_text)
{
 mxyputs(2,10,itoa(xerr++, xbuf,10));
}
*/
				 ps->ReceiveError=FALSE; ps->Preamble1=ps->Preamble2=0;
				 if( ps->ReceiveFrameStatus == RECEIVE_FRAME_DATA )
				 {
					((struct MSTP_ReceivedFrame *)data->recframe)->ReceivedInvalidFrame = TRUE;
					ps->validint = 0;
					if( tasks[ps->task].status != DEAD && tasks[ps->task].status != RUNNING )
						tasks[ps->task].status = READY;
					((struct MSTP_ReceivedFrame *)data->recframe)->status = 1;
				 }
				 ps->ReceiveFrameStatus = RECEIVE_FRAME_IDLE;
				}
				if( ps->Preamble1 && ps->SilenceTimer>Tframe_abort )
				{
/*
if (mode_text)
{
 mxyputs(2,11,itoa(xerr++, xbuf,10));
}
*/
				 ps->Preamble1=ps->Preamble2=0;
				 if( ps->ReceiveFrameStatus == RECEIVE_FRAME_DATA )
				 {
					((struct MSTP_ReceivedFrame *)data->recframe)->status = 0;
//				  ((class MSTP *)Routing_table[data->port_number].ptr)->ReceivedFramePool.Clear();
				 }
				 ps->ReceiveFrameStatus = RECEIVE_FRAME_IDLE;
				}
				if( ps->Preamble2 )
				{
				 if( ps->ReceiveFrameStatus == RECEIVE_FRAME_IDLE )
				 {
					ps->HeaderCRC = table_crc8[ps->HeaderCRC^c_lsr_mcr];
					switch ( ps->HEADERState ) {
					 case HEADER_HeaderCRC:
						if( ps->HeaderCRC == 0x55 )
						{
							if ( ps->FrameType==Token )
							{
							 ((class MSTP *)Routing_table[data->port_number].ptr)->panel_info1.active_panels |= (1l<<(ps->Source-1));
//							 ((class MSTP *)Routing_table[data->port_number].ptr)->station_list[ps->Source-1].state = 1;
							}

							if( ps->Destination != Station_NUM && ps->Destination != 255)
							{
							ps->Preamble1=ps->Preamble2=0;
							break;
							}
//					   if( (data->recframe = ((class MSTP *)Routing_table[data->port_number].ptr)->ReceivedFramePool.NextFreeEntry())!=0 )
							 if( !((class MSTP *)Routing_table[data->port_number].ptr)->ReceivedFramePool.ReceivedFrame[0].status )
							 {
								data->recframe = ((class MSTP *)Routing_table[data->port_number].ptr)->ReceivedFramePool.ReceivedFrame;
								((struct MSTP_ReceivedFrame *)data->recframe)->status = 2;

								((struct MSTP_ReceivedFrame *)data->recframe)->Frame.Length = ps->Length;
								((struct MSTP_ReceivedFrame *)data->recframe)->Frame.FrameType = ps->FrameType;
								((struct MSTP_ReceivedFrame *)data->recframe)->Frame.Destination = ps->Destination;
								((struct MSTP_ReceivedFrame *)data->recframe)->Frame.Source = ps->Source;
								if(!ps->Length)
								{
								 ((struct MSTP_ReceivedFrame *)data->recframe)->ReceivedValidFrame = TRUE;
//							 ((class MSTP *)Routing_table[data->port_number].ptr)->ReceivedFramePool.Unlockhead();
								 ((struct MSTP_ReceivedFrame *)data->recframe)->status = 1;
//							 resume( ps->task );
								 ps->validint = 0;
								 if( tasks[ps->task].status != DEAD && tasks[ps->task].status != RUNNING )
								 tasks[ps->task].status = READY;
								}
								else
								{
								 data->ptr = ((struct MSTP_ReceivedFrame *)data->recframe)->Frame.Buffer;
								 data->length = 0;
								 ps->DataCRC=0xffff;
								 ps->ReceiveFrameStatus = RECEIVE_FRAME_DATA;
								 break;
								}
							 }
						}
						ps->Preamble1=ps->Preamble2=0;
						break;
					 case HEADER_Length2:
						ps->Length += c_lsr_mcr;
						if(ps->Length > MAXFRAMEBUFFER+2+1)
						{
						 ps->Preamble1=ps->Preamble2=0;
						 break;
						}
						ps->HEADERState = HEADER_HeaderCRC;
						break;
					 case HEADER_Length1:
						ps->Length = c_lsr_mcr<<8;
						ps->HEADERState = HEADER_Length2;
						break;
					 case HEADER_Source:
						ps->Source = c_lsr_mcr;
						ps->HEADERState = HEADER_Length1;
						break;
					 case HEADER_Destination:
/*
						if( (c_lsr_mcr != Station_NUM && c_lsr_mcr != 255) ||
							 (c_lsr_mcr == 255 && (ps->FrameType==Token || ps->FrameType==BACnetDataExpectingReply ||
														  ps->FrameType==TestRequest
															// or a proprietary type known to
														  )
							 )
						  )
						{
						 ps->Preamble1=ps->Preamble2=0;
						 break;
						}
						else
*/
						{
						 ps->Destination = c_lsr_mcr;
						 ps->HEADERState = HEADER_Source;
						 break;
						}
					 case HEADER_FrameType:
						ps->FrameType = c_lsr_mcr;
						ps->HEADERState = HEADER_Destination;
						break;
					}
				 }
				 else  //RECEIVE_FRAME_DATA
				 {
					ps->DataCRC= (ps->DataCRC >> 8 ) ^ table_crc16[ (ps->DataCRC&0xFF) ^ c_lsr_mcr ];
					if( data->length < ps->Length )
					{
					 data->length++;
					 *data->ptr++ = c_lsr_mcr;
					}
					else
					{
					 if( data->length++ == ps->Length+1 )
					 {
					  if( ps->DataCRC==0x0f0b8 )
						 ((struct MSTP_ReceivedFrame *)data->recframe)->ReceivedValidFrame = TRUE;
					  else
						 ((struct MSTP_ReceivedFrame *)data->recframe)->ReceivedInvalidFrame = TRUE;
//					  ((class MSTP *)Routing_table[data->port_number].ptr)->ReceivedFramePool.Unlockhead();
						((struct MSTP_ReceivedFrame *)data->recframe)->status = 1;
//					  resume( ps->task );
						ps->validint = 0;
					  if( tasks[ps->task].status != DEAD && tasks[ps->task].status != RUNNING )
						tasks[ps->task].status = READY;
					  ps->ReceiveFrameStatus = RECEIVE_FRAME_IDLE;
						ps->Preamble1=ps->Preamble2=0;
					 }
					}
				 }
				}  // if Preamble2
				else
				{
				 if(ps->Preamble1)  //0x55
				 {
					if(c_lsr_mcr==0xff)
					{
					 ps->Preamble2=0xFF;
					 ps->HeaderCRC=0xFF;
					 ps->HEADERState=HEADER_FrameType;
//					data->RXQueue.Clear();
					}
					else
					if(c_lsr_mcr!=0x55)
					{
					 ps->Preamble1=0;
					}
				 }
				 else
					if(c_lsr_mcr==0x55)
					{
					ps->Preamble1=0x55;
					ps->Preamble2=0;
					}
				}
			}
			data->rx_int_count=0;
			ps->SilenceTimer=0;
			ps->EventCount++;
/*
			if(insert && ps->validint)
			 if ( !data->RXQueue.Insert( (char) c_lsr_mcr ) )
				data->overflow = 1;
*/
			}
		  else
			{
			 ps->ReceiveError=TRUE; ps->EventCount++;
			 ps->SilenceTimer=0;
			}
		}
	  else
		{
		if(data->media == ASYNCRON_LINK )
		{
			if ( !data->RXQueue.Insert( (char) c_lsr_mcr ) )
				data->overflow = 1;
		}
		else     // PTP connection
		{
		 if(data->media == SERIAL_LINK || data->media == MODEM_LINK)
		 {
//		  PTP CONNECTION WITH RECEIVE FRAME
		 insert=1;
		 ps = &Routing_table[data->port_number].port_status_vars;
		 if( ps->connection != PTP_IDLE )
		 {
		  if(c_lsr_mcr!=XON && c_lsr_mcr!=XOFF)
			{
//			if( PTP_ReceiveFrameStatus == PTP_IDLE  && validint)
			if( c_lsr_mcr == 0x10 )
			{
				data->rx_control_char = 1;
				insert=0;
			}
			else
			{
			  if( data->rx_control_char )
			  {
				  c_lsr_mcr &= ~0x80;
				  data->rx_control_char = 0;
				}
			  if( ps->connection == PTP_DISCONNECTED )
			  {
				  if( trigger_sequence[ data->tr_index ] == c_lsr_mcr ) data->tr_index++;
				  else data->tr_index = 0;
				  if( data->tr_index == 7 )
					{
						ps->connection = PTP_REC_TRIGGER_SEQ;
						data->tr_index = 0;
						resume( ps->task );
					}
					insert=0;
				}
			}
//			if( insert && ps->ReceiveFrameStatus == RECEIVE_FRAME_IDLE )
			if( insert )
			{
//				insert=0;
				if( ps->ReceiveError==TRUE )
				{
				 ps->ReceiveError=FALSE; ps->Preamble1=ps->Preamble2=0;
//				 if( ps->ReceiveFrameStatus == RECEIVE_FRAME_DATA )
				 if( data->recframe )
				 {
						((struct PTP_ReceivedFrame *)data->recframe)->flags.ReceivedInvalidFrame = TRUE;
//					   ((class PTP *)Routing_table[data->port_number].ptr)->ReceivedFramePool.Unlockhead();
						((struct PTP_ReceivedFrame *)data->recframe)->status = 1;
						data->recframe = NULL;
						if( ps->connection == PTP_CONNECTED )
						{
								 resume(ps->task+PTP_reception);
						}
						else
								 resume( ps->task );
				 }
//				 ps->ReceiveFrameStatus = RECEIVE_FRAME_IDLE;
				}
				if( ps->Preamble1 && ps->SilenceTimer>PTP_Tframe_abort )
				{
				 ps->Preamble1=ps->Preamble2=0;
//				 if( ps->ReceiveFrameStatus == RECEIVE_FRAME_DATA )
				 if( data->recframe )
				 {
						((struct PTP_ReceivedFrame *)data->recframe)->flags.ReceivedInvalidFrame = TRUE;
//					   ((class PTP *)Routing_table[data->port_number].ptr)->ReceivedFramePool.Unlockhead();
						((struct PTP_ReceivedFrame *)data->recframe)->status = 1;
						data->recframe = NULL;
						if( ps->connection == PTP_CONNECTED )
						{
								 resume(ps->task+PTP_reception);
						}
						else
								 resume( ps->task );
				 }
//				 ps->ReceiveFrameStatus = RECEIVE_FRAME_IDLE;
				}
				 if( ps->Preamble2 )
				 {
					if( ps->ReceiveFrameStatus == RECEIVE_FRAME_IDLE )
					{
					ps->HeaderCRC = table_crc8[ps->HeaderCRC^c_lsr_mcr];
					switch ( ps->HEADERState ) {
					case HEADER_HeaderCRC:
					{
//					 ps->HeaderCRC = table_crc8[ps->HeaderCRC^c_lsr_mcr];
					 if( ps->HeaderCRC == 0x55 )
					 {
						if(!ps->Length)
						{
							insert=2;
							switch ( ps->FrameType ) {
							 case HEARTBEAT_XON:
							 {
								ps->PTP_comm_status.transmission_blocked = 0;
								break;
							 }
							 case HEARTBEAT_XOFF:
							 {
								ps->PTP_comm_status.transmission_blocked = 1;
								break;
							 }
							 case DATA_ACK_0_XON:
								if( ps->PTP_comm_status.TxSequence_number == 0 )
								{
								/*	Ack0 XON	*/
								ps->PTP_comm_status.ack0received = 1;
								ps->PTP_comm_status.transmission_blocked = 0;
								}
								else
								{
								/*	Duplicate XON	*/
								ps->PTP_comm_status.transmission_blocked = 0;
								}
								break;
							 case DATA_ACK_0_XOFF:
								if( ps->PTP_comm_status.TxSequence_number == 0 )
								{
								/*	Ack0 XOFF	*/
								ps->PTP_comm_status.ack0received = 1;
								ps->PTP_comm_status.transmission_blocked = 1;
							  }
							  else
							  {
								/*	Duplicate XOFF	*/
								ps->PTP_comm_status.transmission_blocked = 1;
								}
							  break;
							 case DATA_ACK_1_XON:
								if( ps->PTP_comm_status.TxSequence_number == 0 )
								{
								/*	Duplicate XON	*/
								ps->PTP_comm_status.transmission_blocked = 0;
								}
								else
							  {
								/*	Ack1 XON	*/
								ps->PTP_comm_status.ack1received = 1;
								ps->PTP_comm_status.transmission_blocked = 0;
								}
								break;
							 case DATA_ACK_1_XOFF:
								if( ps->PTP_comm_status.TxSequence_number == 0 )
								{
								/*	Duplicate XOFF	*/
								ps->PTP_comm_status.transmission_blocked = 1;
								}
							  else
							  {
								/*	Ack1 XOFF	*/
								ps->PTP_comm_status.ack1received = 1;
								ps->PTP_comm_status.transmission_blocked = 1;
								}
								break;
							 case DATA_NAK_0_XOFF:
									if( ps->PTP_comm_status.TxSequence_number == 0 )
									{
										ps->PTP_comm_status.nak0received = 1;
										ps->PTP_comm_status.transmission_blocked = 1;
									}
									else
									{
										ps->PTP_comm_status.transmission_blocked = 1;
									}
									break;
							 case DATA_NAK_1_XOFF:
									if( ps->PTP_comm_status.TxSequence_number == 1 )
									{
										ps->PTP_comm_status.nak1received = 1;
										ps->PTP_comm_status.transmission_blocked = 1;
									}
									else
									{
										ps->PTP_comm_status.transmission_blocked = 1;
									}
									break;
							 case DATA_NAK_0_XON:
									if( ps->PTP_comm_status.TxSequence_number == 0 )
									{
										ps->PTP_comm_status.nak0received = 1;
										ps->PTP_comm_status.transmission_blocked = 0;
									}
									else
									{
										ps->PTP_comm_status.transmission_blocked = 0;
									}
									break;
							 case DATA_NAK_1_XON:
									if( ps->PTP_comm_status.TxSequence_number == 1 )
									{
										ps->PTP_comm_status.nak1received = 1;
										ps->PTP_comm_status.transmission_blocked = 0;
									}
									else
									{
										ps->PTP_comm_status.transmission_blocked = 0;
									}
									break;
							 default:
								if( (data->recframe = ((class PTP *)Routing_table[data->port_number].ptr)->ReceivedFramePool.NextFreeEntry())!=0 )
								{
								((struct PTP_ReceivedFrame *)data->recframe)->Frame.Length = 0;
								((struct PTP_ReceivedFrame *)data->recframe)->Frame.FrameType = ps->FrameType;
								((struct PTP_ReceivedFrame *)data->recframe)->flags.ReceivedValidFrame = TRUE;
//								((class PTP *)Routing_table[data->port_number].ptr)->ReceivedFramePool.Unlockhead();
								((struct PTP_ReceivedFrame *)data->recframe)->status = 1;
								data->recframe = NULL;
								if( ps->FrameType==CONNECT_REQUEST || ps->FrameType==CONNECT_RESPONSE ||
									 ps->FrameType==DISCONNECT_REQUEST || ps->FrameType==DISCONNECT_RESPONSE )
								{
								 resume( ps->task );
								}
								else
								 if( ps->connection == PTP_CONNECTED )
								 {
									 resume(ps->task+PTP_reception);
								 }
							  }
								insert=0;
							  break;
							}
						  if (insert==2)
							{
							 ps->InactivityTimer = 0;
							 resume( ps->task+PTP_transmission );
							 insert=0;
							}
							ps->Preamble1=ps->Preamble2=0;
						}
						else    //DATA
						{
						 if( (data->recframe = ((class PTP *)Routing_table[data->port_number].ptr)->ReceivedFramePool.NextFreeEntry())!=0 )
						 {
							((struct PTP_ReceivedFrame *)data->recframe)->Frame.Length = ps->Length;
							((struct PTP_ReceivedFrame *)data->recframe)->Frame.FrameType = ps->FrameType;
							data->ptr = ((struct PTP_ReceivedFrame *)data->recframe)->Frame.Buffer;
							data->length = 0;
							ps->DataCRC=0xffff;

							if(ps->Length > MAXFRAMEBUFFER+2+1)
							{
							 ((struct PTP_ReceivedFrame *)data->recframe)->flags.ReceivedInvalidFrame = TRUE;
//					   ((class PTP *)Routing_table[data->port_number].ptr)->ReceivedFramePool.Unlockhead();
							 ((struct PTP_ReceivedFrame *)data->recframe)->status = 1;
							 data->recframe = NULL;
							 if( ps->connection == PTP_CONNECTED )
							 {
								 resume(ps->task+PTP_reception);
							 }
							 else
								 resume( ps->task );
							 ps->ReceiveFrameStatus = RECEIVE_FRAME_IDLE;
							 ps->Preamble1=ps->Preamble2=0;
							}
							else
								ps->ReceiveFrameStatus = RECEIVE_FRAME_DATA;
						 }
						 else
						 {
							ps->Preamble1=ps->Preamble2=0;
						 }
						}
					 }
					 else
					 {
						ps->Preamble1=ps->Preamble2=0;
					 }
					}
					break;
					case HEADER_Length2:
					{
//					 insert=1;
//					 ps->HeaderCRC=CalcHeaderCRC(c_lsr_mcr, ps->HeaderCRC );
//					 ps->HeaderCRC = table_crc8[ps->HeaderCRC^c_lsr_mcr];
					 ps->Length += c_lsr_mcr;
//					 data->recframe->Frame.Length += c_lsr_mcr;
					 ps->HEADERState = HEADER_HeaderCRC;
					}
					break;
					case HEADER_Length1:
					{
//					 insert=1;
//					 ps->HeaderCRC=CalcHeaderCRC(c_lsr_mcr, ps->HeaderCRC );
//					 ps->HeaderCRC = table_crc8[ps->HeaderCRC^c_lsr_mcr];
					 ps->Length = c_lsr_mcr<<8;
//					 data->recframe->Frame.Length = c_lsr_mcr<<8;
					 ps->HEADERState = HEADER_Length2;
					}
					break;
					case HEADER_FrameType:
					{
//					  ps->HeaderCRC = table_crc8[ps->HeaderCRC^c_lsr_mcr];
						ps->FrameType = c_lsr_mcr;
						ps->HEADERState = HEADER_Length1;
					}
					break;
					}
					}
					else  //RECEIVE_FRAME_DATA
					{
					ps->DataCRC= (ps->DataCRC >> 8 ) ^ table_crc16[ (ps->DataCRC&0xFF) ^ c_lsr_mcr ];
//					ps->DataCRC=CalcDataCRC(c_lsr_mcr, ps->DataCRC);
					if( data->length < ps->Length )
					{
					 data->length++;
					 *data->ptr++ = c_lsr_mcr;
					}
					else
					{
					 if( data->length++ == ps->Length+1 )
					 {
						if( ps->DataCRC==0x0f0b8 )
						 ((struct PTP_ReceivedFrame *)data->recframe)->flags.ReceivedValidFrame = TRUE;
						else
						 ((struct PTP_ReceivedFrame *)data->recframe)->flags.ReceivedInvalidFrame = TRUE;
//					  ((class PTP *)Routing_table[data->port_number].ptr)->ReceivedFramePool.Unlockhead();
						((struct PTP_ReceivedFrame *)data->recframe)->status = 1;
								 data->recframe = NULL;
						if( ps->connection == PTP_CONNECTED )
						{
						resume(ps->task+PTP_reception);
						}
						else
						resume( ps->task );
						ps->ReceiveFrameStatus = RECEIVE_FRAME_IDLE;
						ps->Preamble1=ps->Preamble2=0;
					 }
					}
					}
				 }
				 else
				 {
				 if(ps->Preamble1)  //0x55
				 {
					if(c_lsr_mcr==0xff)
					{
//					 data->RXQueue.Clear();
					 ps->HeaderCRC=0xFF;
					 ps->HEADERState=HEADER_FrameType;
					 ps->Preamble2=0xFF;
					 data->rx_control_char = 0;
					}
					else
					if(c_lsr_mcr!=0x55)
					{
					 ps->Preamble1=0;
					}
				 }
				 else
					if(c_lsr_mcr==0x55)
					{
					 ps->Preamble1=0x55;
					 ps->Preamble2=0;
				   ps->ReceiveFrameStatus = RECEIVE_FRAME_IDLE;
					}
				}
			}
			}// end if XON or XOFF
			ps->SilenceTimer=0;
//			EventCount++;
//			if(insert && validint)
/*
			if(insert)
			 if ( !data->RXQueue.Insert( (char) c_lsr_mcr ) )
				data->overflow = 1;
*/
		 }
		 else
		 {
//			ps->SilenceTimer=0;
			insert=1;
			if(ps->mode == SLAVE)
			 if( ps->ring < ps->rings_number || ps->time_modem<0 )
			 {
				if( ring_sequence[ data->tr_index ] == c_lsr_mcr ) data->tr_index++;
			  else data->tr_index = 0;
				if( data->tr_index == 4 )
			  {
				if( ps->ring++ > 0 )
				{
				 if(ps->time_modem < 0) ps->ring = 1;
				}
				ps->time_modem = 10000L;
				data->tr_index = 0;
				if( ps->ring >= ps->rings_number )
				{
				 resume( ps->task );
				 ps->time_modem = 60000L;
				}
			  }
				insert=0;
			 }
			 if(insert)
			  if ( !data->RXQueue.Insert( (char) c_lsr_mcr ) )
				data->overflow = 1;
		 }
		 }
		}
		}

		if ( data->uart_type == UART_8250 )
			break;
		c_lsr_mcr = INPUT( data->uart + LINE_STATUS_REGISTER );
		data->line_status |= c_lsr_mcr;
		if ( ( c_lsr_mcr & LSR_DATA_READY ) == 0 )
				break;
	 }
// The handshaking section

	 if ( data->handshaking )
	 {
			if ( data->RXQueue.InUseCount() > HighWaterMark ) {
						if ( ( data->handshaking & rts_cts ) &&
									!( data->blocking & rts_cts ) ) {
								c_lsr_mcr = INPUT( data->uart + MODEM_CONTROL_REGISTER );
								c_lsr_mcr &= ~MCR_RTS;
								OUTPUT( data->uart + MODEM_CONTROL_REGISTER, c_lsr_mcr );
								data->blocking |= rts_cts;
				}
						if ( ( data->handshaking & dtr_dsr ) &&
									!( data->blocking & dtr_dsr ) ) {
								c_lsr_mcr = INPUT( data->uart + MODEM_CONTROL_REGISTER );
					 c_lsr_mcr &= ~MCR_DTR;
								OUTPUT( data->uart + MODEM_CONTROL_REGISTER, c_lsr_mcr );
								data->blocking |= dtr_dsr;
						}
						if ( ( data->handshaking & xon_xoff ) &&
								 !( data->blocking & xon_xoff ) ) {
								data->blocking |= xon_xoff;
					 if ( data->send_handshake_char == XON ) {
										data->send_handshake_char = -1;
								} else {
										data->send_handshake_char = XOFF;
							jump_start( data );
								}
						}
				}
	 }
    asm pop es;
}


// Any time transmit interrupts need to be restarted, this
// routine is called to do the job.  It gets the interrupts
// running again by sending a single character out the TX
// register manually.  When that character is done
// transmitting, the next TX interrupt will start.  The
// tx_running member of the class keeps track of when we can
// expect another TX interrupt and when we can't.

void jump_start( struct isr_data_block *data )
{
	 int c,i;

// Both tx_running and blocked can change behind my back in the
// ISR, so I have to disable interrupts if I want to be able to
// count on them.

/*
	 CLI();
	 if ( !data->tx_running )
	 {
			OUTPUT( data->uart + INTERRUPT_ENABLE_REGISTER,
			 IER_RX_DATA_READY + IER_TX_HOLDING_REGISTER_EMPTY +
			 IER_MODEM_STATUS + IER_LINE_STATUS );

			if ( ( c = data->send_handshake_char ) != -1 )
				data->send_handshake_char = -1;
			else if ( !data->blocked )
				c = data->TXQueue.Remove();
			if ( c >= 0 )
			{
				data->tx_running = 1;
				OUTPUT( data->uart, c );
			}
	 }
	 STI();
*/

	 CLI();
	 asm push es;
	 if ( !data->tx_running )
	 {
/*
			OUTPUT( data->uart + INTERRUPT_ENABLE_REGISTER,
			 IER_RX_DATA_READY + IER_TX_HOLDING_REGISTER_EMPTY +
			 IER_MODEM_STATUS + IER_LINE_STATUS );
*/
			OUTPUT( data->uart + INTERRUPT_ENABLE_REGISTER,
			 IER_TX_HOLDING_REGISTER_EMPTY + IER_MODEM_STATUS + IER_LINE_STATUS );
/*
			if( data->uart_type == UART_16550 )
			{
			// reset xmit FIFO
				OUTPUT( data->uart + FIFO_CONTROL_REGISTER, FCR_XMIT_FIFO_RESET );
			// enable FIFO
				OUTPUT( data->uart + FIFO_CONTROL_REGISTER, FCR_FIFO_ENABLE );
			}
*/

			if ( ( c = data->send_handshake_char ) != -1 )
				data->send_handshake_char = -1;
			else
			 if ( !data->blocked )
			 {
				if( data->uart_type == UART_16550 )
					i = 16;
				else
					i = 1;
				while( i-- > 0 )
				{
				 c = data->TXQueue.Remove();
				 if ( c >= 0 )
				 {
/*
#ifdef TEST
			if(c==0x55)
			{
			 tempor[0]='T';
			 tempor[1]=':';
			 tempy++;
			 if(tempy>=24) tempy=0;
			 tempx=0;
			 lin_text[80];
			 mxyputs(tempx,tempy,lin_text);
			 lin_text[80]=' ';
			 mxyputs(tempx,tempy,tempor);
			tempx+=3;
			}
			tempor[0]=(c>>4);
			if(tempor[0]>9)
				 tempor[0]+=65;
			else
				 tempor[0]+=48;
			tempor[1]=(c&0x0F);
			if(tempor[1]>9)
				 tempor[1]+=65;
			else
				 tempor[1]+=48;
			mxyputs(tempx,tempy,tempor);
			tempx+=3;
#endif
*/
#ifdef TEST
			if( tempor_ind < MAXtempor )
			{
			 if(i==15)
				tempor[tempor_ind++]='*';
			 tempor[tempor_ind++]=c;
			}
#endif
					data->tx_running = 1;
					 OUTPUT( data->uart + TRANSMIT_HOLDING_REGISTER, c );
				 }
				 else
					break;
				}
			 }
	 }
	 asm pop es;
	 STI();

}

// *********************** END OF ISR_8250.CPP ***********************

#endif



/*
//		  PTP CONNECTION WITHOUT RECEIVE FRAME
		 else     // PTP connection
		 {
			if(c_lsr_mcr!=XON && c_lsr_mcr!=XOFF)
		  {
//			if( PTP_ReceiveFrameStatus == PTP_IDLE  && validint)
			ps = &Routing_table[data->port_number].port_status_vars;
			if( c_lsr_mcr == 0x10 )
			{
				data->rx_control_char = 1;
				insert=0;
			}
			else
			{
			  if( data->rx_control_char )
			  {
				  c_lsr_mcr &= ~0x80;
				  data->rx_control_char = 0;
				}
			  if( ps->connection == PTP_DISCONNECTED )
			  {
				  if( trigger_sequence[ data->tr_index ] == c_lsr_mcr ) data->tr_index++;
				  else data->tr_index = 0;
				  if( data->tr_index == 7 )
				  {
						ps->connection = PTP_REC_TRIGGER_SEQ;
						data->tr_index = 0;
						resume( ps->task );
				  }
				  insert=0;
			  }
			}
			if( insert && ps->ReceiveFrameStatus == RECEIVE_FRAME_IDLE )
//			if( insert )
			{
				insert=0;
				if( ps->ReceiveError==TRUE ) {ps->ReceiveError=FALSE; ps->Preamble1=ps->Preamble2=0;};
				if( ps->Preamble1 && ps->SilenceTimer>PTP_Tframe_abort ) {ps->Preamble1=ps->Preamble2=0;};
				 if( ps->Preamble2 )
				 {
					switch ( ps->HEADERState ) {
					case HEADER_HeaderCRC:
					{
					 ps->HeaderCRC = table_crc8[ps->HeaderCRC^c_lsr_mcr];
					 if( ps->HeaderCRC == 0x55 )
					 {
						if(!ps->Length)
						{
						  insert=2;
						  switch ( ps->FrameType ) {
							 case HEARTBEAT_XON:
							 {
							  ps->PTP_comm_status.transmission_blocked = 0;
							  break;
							 }
							 case HEARTBEAT_XOFF:
							 {
							  ps->PTP_comm_status.transmission_blocked = 1;
							  break;
							 }
							 case DATA_ACK_0_XON:
							  if( ps->PTP_comm_status.TxSequence_number == 0 )
								{
								//	Ack0 XON
								ps->PTP_comm_status.ack0received = 1;
								ps->PTP_comm_status.transmission_blocked = 0;
							  }
							  else
							  {
								//	Duplicate XON
								ps->PTP_comm_status.transmission_blocked = 0;
							  }
							  break;
							 case DATA_ACK_0_XOFF:
							  if( ps->PTP_comm_status.	TxSequence_number == 0 )
							  {
								//	Ack0 XOFF
								ps->PTP_comm_status.ack0received = 1;
								ps->PTP_comm_status.transmission_blocked = 1;
							  }
							  else
							  {
								//	Duplicate XOFF
								ps->PTP_comm_status.transmission_blocked = 1;
								}
							  break;
							 case DATA_ACK_1_XON:
							  if( ps->PTP_comm_status.TxSequence_number == 0 )
							  {
								//	Duplicate XON
								ps->PTP_comm_status.transmission_blocked = 0;
								}
							  else
							  {
								//	Ack1 XON
								ps->PTP_comm_status.ack1received = 1;
								ps->PTP_comm_status.transmission_blocked = 0;
							  }
							  break;
							 case DATA_ACK_1_XOFF:
							  if( ps->PTP_comm_status.TxSequence_number == 0 )
							  {
								//	Duplicate XOFF
								ps->PTP_comm_status.transmission_blocked = 1;
							  }
							  else
								{
								//	Ack1 XOFF
								ps->PTP_comm_status.ack1received = 1;
								ps->PTP_comm_status.transmission_blocked = 1;
							  }
							  break;
							 default:
								insert=0;
							  break;
						  }
						  if (insert==2)
						  {
							 ps->InactivityTimer = 0;
							 resume( ps->task+PTP_TRANSMISSION );
						  }
						}
					 }
					 if(!insert)
					 {
					  insert=1;
					  ps->ReceiveFrameStatus=RECEIVE_FRAME_HEADER;
					  ps->HeaderCRC=0xff;
						ps->HEADERState=HEADER_FrameType;
					  if( tasks[ps->task+PTP_RECEIVEFRAME].status == SUSPENDED )
					  {
						  tasks[ps->task+PTP_RECEIVEFRAME].sleep = 0;
						  tasks[ps->task+PTP_RECEIVEFRAME].status = READY;
					  }
					 }
					 else
					 {
					  insert = 0;
					  ps->Preamble1=ps->Preamble2=0;
					  data->RXQueue.Clear();
					 }
					}
					break;
					case HEADER_Length2:
					{
					 insert=1;
					 ps->HeaderCRC = table_crc8[ps->HeaderCRC^c_lsr_mcr];
					 ps->Length += c_lsr_mcr;
					 ps->HEADERState = HEADER_HeaderCRC;
					}
					break;
					case HEADER_Length1:
					{
					 insert=1;
					 ps->HeaderCRC = table_crc8[ps->HeaderCRC^c_lsr_mcr];
					 ps->Length = c_lsr_mcr<<8;
					 ps->HEADERState = HEADER_Length2;
					}
					break;
					case HEADER_FrameType:
					{
					 if( c_lsr_mcr == DATA_0 || c_lsr_mcr == DATA_1 )
					 {
					  insert=1;
					  ps->ReceiveFrameStatus=RECEIVE_FRAME_HEADER;
					  if( tasks[ps->task+PTP_RECEIVEFRAME].status == SUSPENDED )
					  {
						  tasks[ps->task+PTP_RECEIVEFRAME].sleep = 0;
						  tasks[ps->task+PTP_RECEIVEFRAME].status = READY;
					  }
					 }
					 else
					 {
					  insert=1;
					  ps->HeaderCRC = table_crc8[ps->HeaderCRC^c_lsr_mcr];
					  ps->FrameType = c_lsr_mcr;
					  ps->HEADERState = HEADER_Length1;
					 }
					}
					break;
				  }
				 }
				 else
				 {
				 if(ps->Preamble1)  //0x55
				 {
				  if(c_lsr_mcr==0xff)
				  {
					 data->RXQueue.Clear();
					 ps->HeaderCRC=0xFF;
					 ps->HEADERState=HEADER_FrameType;
					 ps->Preamble2=0xFF;
				  }
				  else
					if(c_lsr_mcr!=0x55)
					{
					 ps->Preamble1=0;
					}
				 }
				 else
				  if(c_lsr_mcr==0x55)
					{
					ps->Preamble1=0x55;
					ps->Preamble2=0;
				  }
				}
				}
			}
//			data->rx_int_count=0;
			ps->SilenceTimer=0;
//			EventCount++;
//			if(insert && validint)
			if(insert)
			 if ( !data->RXQueue.Insert( (char) c_lsr_mcr ) )
				data->overflow = 1;
//
//		  }
//		  else
//		  {
//			 ps->ReceiveError=TRUE; ps->EventCount++;
//		  }

		 } // end if XON or XOFF
*/
