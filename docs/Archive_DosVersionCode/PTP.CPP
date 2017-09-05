// pentru PTP_SENDPOOL trimit direct din pool pentru a
// economisi spatiu
#include <mem.h>
#include <windows.h>
#include <graphics.h>
#include "t3000def.h"
#include "pc8250.h"
#include "queue.h"
#include "mtkernel.h"
#include "aio.h"
#include "ptp.h"

#define _PTP_DOT_C

extern int exec_program(int current_prg, unsigned char *prog_code, long *stack, int port=COM0);
extern unsigned char CalcHeaderCRC(unsigned char dataValue, unsigned char crcValue);
extern unsigned int CalcDataCRC(unsigned char dataValue, unsigned int crcValue);
extern int networklayer( int service, int priority, int network, int destination, int source,
						char *asdu_npdu, int length_asdu_npdu, char *apci, int length_apci,
						int data_expecting_reply=BACnetDataNotExpectingReply, int clientserver=CLIENT, int port = -1 );

extern long _far stack_com[22];
extern Panel_info1 Panel_Info1;
extern Panel *ptr_panel;
extern Comm_Info *comm_info;
extern char Station_NAME[NAME_SIZE];
extern int  Station_NUM;
extern int Version;
//extern char number_rings;
//extern char ring_counts;
extern unsigned long timestart;    // sec de la inceputul programului
extern long microsec;
extern unsigned long timestart;    // sec de la inceputul programului
extern char STSMremoveflag;
//int PTP_Tframe_abort = PTP_FRAME_ABORT;
char trigger_sequence[] = "BACnet\x0d";
char ring_sequence[] = "RING";

int xdelay=1;
//FRAME_QUEUE SendFramePool, ReceiveFramePool;
char table_crc8[256] =
  {
	0x00,0xFE,0xFF,0x01,0xFD,0x03,0x02,0xFC,0xF9,0x07,0x06,0xF8,0x04,0xFA,0xFB,0x05,
	0xF1,0x0F,0x0E,0xF0,0x0C,0xF2,0xF3,0x0D,0x08,0xF6,0xF7,0x09,0xF5,0x0B,0x0A,0xF4,
	0xE1,0x1F,0x1E,0xE0,0x1C,0xE2,0xE3,0x1D,0x18,0xE6,0xE7,0x19,0xE5,0x1B,0x1A,0xE4,
	0x10,0xEE,0xEF,0x11,0xED,0x13,0x12,0xEC,0xE9,0x17,0x16,0xE8,0x14,0xEA,0xEB,0x15,
	0xC1,0x3F,0x3E,0xC0,0x3C,0xC2,0xC3,0x3D,0x38,0xC6,0xC7,0x39,0xC5,0x3B,0x3A,0xC4,
	0x30,0xCE,0xCF,0x31,0xCD,0x33,0x32,0xCC,0xC9,0x37,0x36,0xC8,0x34,0xCA,0xCB,0x35,
	0x20,0xDE,0xDF,0x21,0xDD,0x23,0x22,0xDC,0xD9,0x27,0x26,0xD8,0x24,0xDA,0xDB,0x25,
	0xD1,0x2F,0x2E,0xD0,0x2C,0xD2,0xD3,0x2D,0x28,0xD6,0xD7,0x29,0xD5,0x2B,0x2A,0xD4,
	0x81,0x7F,0x7E,0x80,0x7C,0x82,0x83,0x7D,0x78,0x86,0x87,0x79,0x85,0x7B,0x7A,0x84,
	0x70,0x8E,0x8F,0x71,0x8D,0x73,0x72,0x8C,0x89,0x77,0x76,0x88,0x74,0x8A,0x8B,0x75,
	0x60,0x9E,0x9F,0x61,0x9D,0x63,0x62,0x9C,0x99,0x67,0x66,0x98,0x64,0x9A,0x9B,0x65,
	0x91,0x6F,0x6E,0x90,0x6C,0x92,0x93,0x6D,0x68,0x96,0x97,0x69,0x95,0x6B,0x6A,0x94,
	0x40,0xBE,0xBF,0x41,0xBD,0x43,0x42,0xBC,0xB9,0x47,0x46,0xB8,0x44,0xBA,0xBB,0x45,
	0xB1,0x4F,0x4E,0xB0,0x4C,0xB2,0xB3,0x4D,0x48,0xB6,0xB7,0x49,0xB5,0x4B,0x4A,0xB4,
	0xA1,0x5F,0x5E,0xA0,0x5C,0xA2,0xA3,0x5D,0x58,0xA6,0xA7,0x59,0xA5,0x5B,0x5A,0xA4,
	0x50,0xAE,0xAF,0x51,0xAD,0x53,0x52,0xAC,0xA9,0x57,0x56,0xA8,0x54,0xAA,0xAB,0x55
  };

unsigned int table_crc16[256] = {
	0x0000,0x1189,0x2312,0x329b,0x4624,0x57ad,0x6536,0x74bf,0x8c48,0x9dc1,0xaf5a,0xbed3,0xca6c,0xdbe5,0xe97e,0xf8f7,
	0x1081,0x0108,0x3393,0x221a,0x56a5,0x472c,0x75b7,0x643e,0x9cc9,0x8d40,0xbfdb,0xae52,0xdaed,0xcb64,0xf9ff,0xe876,
	0x2102,0x308b,0x0210,0x1399,0x6726,0x76af,0x4434,0x55bd,0xad4a,0xbcc3,0x8e58,0x9fd1,0xeb6e,0xfae7,0xc87c,0xd9f5,
	0x3183,0x200a,0x1291,0x0318,0x77a7,0x662e,0x54b5,0x453c,0xbdcb,0xac42,0x9ed9,0x8f50,0xfbef,0xea66,0xd8fd,0xc974,
	0x4204,0x538d,0x6116,0x709f,0x0420,0x15a9,0x2732,0x36bb,0xce4c,0xdfc5,0xed5e,0xfcd7,0x8868,0x99e1,0xab7a,0xbaf3,
	0x5285,0x430c,0x7197,0x601e,0x14a1,0x0528,0x37b3,0x263a,0xdecd,0xcf44,0xfddf,0xec56,0x98e9,0x8960,0xbbfb,0xaa72,
	0x6306,0x728f,0x4014,0x519d,0x2522,0x34ab,0x0630,0x17b9,0xef4e,0xfec7,0xcc5c,0xddd5,0xa96a,0xb8e3,0x8a78,0x9bf1,
	0x7387,0x620e,0x5095,0x411c,0x35a3,0x242a,0x16b1,0x0738,0xffcf,0xee46,0xdcdd,0xcd54,0xb9eb,0xa862,0x9af9,0x8b70,
	0x8408,0x9581,0xa71a,0xb693,0xc22c,0xd3a5,0xe13e,0xf0b7,0x0840,0x19c9,0x2b52,0x3adb,0x4e64,0x5fed,0x6d76,0x7cff,
	0x9489,0x8500,0xb79b,0xa612,0xd2ad,0xc324,0xf1bf,0xe036,0x18c1,0x0948,0x3bd3,0x2a5a,0x5ee5,0x4f6c,0x7df7,0x6c7e,
	0xa50a,0xb483,0x8618,0x9791,0xe32e,0xf2a7,0xc03c,0xd1b5,0x2942,0x38cb,0x0a50,0x1bd9,0x6f66,0x7eef,0x4c74,0x5dfd,
	0xb58b,0xa402,0x9699,0x8710,0xf3af,0xe226,0xd0bd,0xc134,0x39c3,0x284a,0x1ad1,0x0b58,0x7fe7,0x6e6e,0x5cf5,0x4d7c,
	0xc60c,0xd785,0xe51e,0xf497,0x8028,0x91a1,0xa33a,0xb2b3,0x4a44,0x5bcd,0x6956,0x78df,0x0c60,0x1de9,0x2f72,0x3efb,
	0xd68d,0xc704,0xf59f,0xe416,0x90a9,0x8120,0xb3bb,0xa232,0x5ac5,0x4b4c,0x79d7,0x685e,0x1ce1,0x0d68,0x3ff3,0x2e7a,
	0xe70e,0xf687,0xc41c,0xd595,0xa12a,0xb0a3,0x8238,0x93b1,0x6b46,0x7acf,0x4854,0x59dd,0x2d62,0x3ceb,0x0e70,0x1ff9,
	0xf78f,0xe606,0xd49d,0xc514,0xb1ab,0xa022,0x92b9,0x8330,0x7bc7,0x6a4e,0x58d5,0x495c,0x3de3,0x2c6a,0x1ef1,0x0f78
  };


PTP_RECEIVEDFRAMEPOOL::PTP_RECEIVEDFRAMEPOOL(void)
{
  memset(ReceivedFrame,0,sizeof(ReceivedFrame));
}

/*
int PTP_RECEIVEDFRAMEPOOL::NextFreeEntry(void)
{
 unsigned char temp_head;
 int h;
 h = temp_head = HeadFrame;
 if( overflow ) return -1;
 if ( ++temp_head >= PTP_NMAXRECEIVEDFRAMEPOOL )
	 temp_head = 0;
 lockedhead=1;
 if ( temp_head == TailFrame )
	 overflow=1;
 HeadFrame = temp_head;
 ReceivedFrame[h].flags.ReceivedValidFrame=FALSE;
 ReceivedFrame[h].flags.ReceivedInvalidFrame=FALSE;
 return h;
}
*/

void *PTP_RECEIVEDFRAMEPOOL::NextFreeEntry( void )
{
 int i;
 asm push es;
 for(i=0; i<PTP_NMAXRECEIVEDFRAMEPOOL; i++)
 {
	if( !ReceivedFrame[i].status )
	{
	  ReceivedFrame[i].status=2;
	  break;
	}
 }
 asm pop es;
 if ( i >= PTP_NMAXRECEIVEDFRAMEPOOL ) return 0;
 return (void *)&ReceivedFrame[i];
}

/*
void *PTP_RECEIVEDFRAMEPOOL::NextFreeEntry( int t)
{
// signed char nextentry;
 if( (t = NextFreeEntry()) >=0 )
	return (void *)&ReceivedFrame[t];
 else
	return 0;
}
*/

/*
FRAMEPOOL::FRAMEPOOL(void)
{
 TailFrame=HeadFrame=0;
 lockedhead=overflow=0;
}

//	This function will create a new entry in the FramePool
//		and in case of success will return 1 otherwise 0

signed char FRAMEPOOL::NextFreeEntry(void)
{
 unsigned char h,temp_head;
	h = temp_head = HeadFrame;
 if( overflow ) return -1;
 if ( ++temp_head >= NMAXFRAMEPOOL )
	 temp_head = 0;
 lockedhead=1;
 if ( temp_head == TailFrame )
	 overflow=1;
 HeadFrame = temp_head;
 memset( &Entry[h].flags, 0, 2 );
// Entry[h].flags.ReceivedValidFrame=FALSE;
// Entry[h].flags.ReceivedInvalidFrame=FALSE;
 return h;
}

int FRAMEPOOL::RemoveEntry( char *buffer )
{
	int t,r;
	FRAME_ENTRY	*pframe;
	if( HeadFrame == TailFrame && !overflow )
	{
//	HeadFrame = TailFrame = 0;
	return -1;
	}
	t=TailFrame+1;
	if ( t >= NMAXFRAMEPOOL )
	 t = 0;
	if( t==HeadFrame && lockedhead ) return -1;

	pframe = &Entry[TailFrame];
	PTP_FrameType = pframe->Entry.FrameType;
	PTP_Destination = pframe->Entry.Destination;
	PTP_Source = pframe->Entry.Source;
	PTP_DataLength = pframe->Entry.Length;
	memcpy( buffer, pframe->Entry.Buffer, PTP_DataLength);

//	::ReceivedInvalidFrame = pframe->flags.ReceivedInvalidFrame;
//	::ReceivedValidFrame = pframe->flags.ReceivedValidFrame;

	if( overflow ) { overflow=0; };
	TailFrame++;
	if( TailFrame >= NMAXFRAMEPOOL )
		TailFrame = 0;
	return 1;
}

void FRAMEPOOL::Unlockhead(void)
{
	lockedhead=0;
}
*/

int PTP_RECEIVEDFRAMEPOOL::RemoveEntry(void *f)
{
 int i;
// int j;
 PTP_ReceivedFrame *frame;
 frame = (PTP_ReceivedFrame *)f;
 frame->flags.ReceivedValidFrame = frame->flags.ReceivedInvalidFrame = FALSE;
 for(i=0; i<PTP_NMAXRECEIVEDFRAMEPOOL; i++)
 {
	if( ReceivedFrame[i].status==1 ) break;
 }
 if ( i >= PTP_NMAXRECEIVEDFRAMEPOOL ) return -1;
 memcpy(frame, &ReceivedFrame[i], sizeof(PTP_ReceivedFrame));
 ReceivedFrame[i].flags.ReceivedValidFrame=0;
 ReceivedFrame[i].flags.ReceivedInvalidFrame=0;
 ReceivedFrame[i].status=0;
 return 1;
}
/*
int PTP_RECEIVEDFRAMEPOOL::RemoveEntry(void *f)
{
  int t,r;
//  struct PTP_ReceivedFrame  *pframe;
  PTP_ReceivedFrame *frame;
  frame = (PTP_ReceivedFrame *)f;
  frame->flags.ReceivedValidFrame = frame->flags.ReceivedInvalidFrame = FALSE;
  disable();
  if ( HeadFrame == TailFrame && !overflow )
  {
	enable();
	return -1;
  }
  t=TailFrame+1;
  if ( t >= PTP_NMAXRECEIVEDFRAMEPOOL )
	 t = 0;
  if( t==HeadFrame && lockedhead )
  {
	enable();
	return -1;
  }
  memcpy(frame, &ReceivedFrame[TailFrame], sizeof(PTP_ReceivedFrame));
  if ( overflow ) {overflow=0;};
  TailFrame++;
  if ( TailFrame >= PTP_NMAXRECEIVEDFRAMEPOOL )
	 TailFrame = 0;
  enable();
  return 1;
}
*/

/*
int PTP_SENDFRAMEPOOL::RemoveEntry(PTP_FRAME *frame, char dest, char source)
{
  int t,r,i,j;
  if ( HeadFrame == TailFrame && !overflow )
  {
//	HeadFrame = TailFrame = 0;
	r = -1;
  }
  else
  {
	t=TailFrame+1;
	if ( t >= PTP_NMAXSENDFRAMEPOOL )
	  t = 0;
	if( t==HeadFrame && lockedhead )
	{
		r = -1;
	}
	else
	{
	  memcpy( frame, &Frame[TailFrame], MAXFRAME);
//	  MSTP_SendFrameType = Frame[TailFrame].FrameType;
//	  MSTP_SendDestination = Frame[TailFrame].Destination;
//	  MSTP_SendSource = Frame[TailFrame].Source;
	  if ( overflow ) {overflow=0;};
	  TailFrame++;
	  if ( TailFrame >= PTP_NMAXSENDFRAMEPOOL )
		TailFrame = 0;
	  r = 1;
	}
  }
 return r;
}
*/

int PTP_SENDFRAMEPOOL::RemoveEntry(PTP_FRAME **frame)
{
  int t,r,i,j;
  if( access ) return -1;
  access=1;
  if ( HeadFrame == TailFrame && !overflow )
  {
	r = -1;
  }
  else
  {
	t=TailFrame+1;
	if ( t >= PTP_NMAXSENDFRAMEPOOL )
	  t = 0;
	if( t==HeadFrame && lockedhead )
	{
		r = -1;
	}
	else
	{
	  *frame = &Frame[TailFrame];
	  r = 1;
	}
  }
  access=0;
  return r;
}

void PTP_SENDFRAMEPOOL::AdvanceTail(void)
{
  int t,r,i,j;
	if ( overflow ) {overflow=0;};
	TailFrame++;
	if ( TailFrame >= PTP_NMAXSENDFRAMEPOOL )
		TailFrame = 0;
}

PTP::PTP( int c_port, int n_port ):Serial( c_port, n_port )
{
/*
	active_panels = 1<<(Station_NUM-1);
	memset(station_list,0,sizeof(station_list));
	strcpy(station_list[Station_NUM-1].name,Station_NAME);
	station_list[Station_NUM-1].state = 1;
	NetworkAddress = comm_info[c_port].NetworkAddress;
	memcpy(NetworkName,comm_info[c_port].NetworkName,NAME_SIZE);
*/
	memset(&panel_info1, 0, sizeof(panel_info1));
	memset(station_list,0,sizeof(station_list));
/*---------
//	Point point;
	memset(&need_info, 0, sizeof(need_info));
//	memset(&panel_info1, 0, sizeof(panel_info1));
//	panel_info1.active_panels = 1l<<(Station_NUM-1);
//	memset(station_list,0,sizeof(station_list));
//	strcpy(station_list[Station_NUM-1].name,Station_NAME);
//	station_list[Station_NUM-1].state = 1;
	panel_info1.network = comm_info[c_port].NetworkAddress;
	memcpy(panel_info1.network_name,comm_info[c_port].NetworkName,NAME_SIZE);
	strcpy(panel_info1.panel_name,Station_NAME);
//	panel_info1.des_length = search_point( point, NULL, NULL, 0, LENGTH );
//	station_list[Station_NUM-1].des_length = panel_info1.des_length;
	panel_info1.panel_number = Station_NUM;
	panel_info1.version = Version;
----------*/

	ResponseTimer = T_RESPONSE;
	frame_send_timer = 0;
	password_needed = 0;
	password_OK = 0;

	reception_state = 0;
	transmission_state = 0;
	sendframe_flag = 0;
	connection_state = PTP_DISCONNECTED;
	Install_port();
}


/*
int PTP::PTP_receive_frame_state_machine( PTP* ptp )
{
 signed char next;
 int c,index,x;
 signed char nextentry=-1;
 struct PTP_ReceivedFrame *pframe;
 Byte work_byte, rec_frame_ready;
 struct port_status_variables *ps;
// suspend(PTP_RECEIVEFRAME);
 ps = &Routing_table[ptp->port_number].port_status_vars;
 while( 1 )
 {
  if( ptp->port_status == INSTALLED && ptp->connection_state != PTP_DISCONNECTED )
  {
	if(ps->ReceiveFrameStatus != RECEIVE_FRAME_IDLE)
	{
	 if( (nextentry = ptp->ReceivedFramePool.NextFreeEntry()) >=0 )
	 {
	  pframe = &ptp->ReceivedFramePool.ReceivedFrame[nextentry];
	  while(ps->ReceiveFrameStatus != RECEIVE_FRAME_IDLE)
	  {
		next=0;
		if( ps->SilenceTimer > PTP_Tframe_abort || ps->ReceiveError==TRUE)
		{
		 ps->ReceiveError=FALSE;
		 pframe->flags.ReceivedInvalidFrame = TRUE;
		 ps->SilenceTimer=0;
		 break;
		}
		asm push es;
		if( ( c = ptp->port->isr_data->RXQueue.Remove() ) < 0 )
		{
		 asm pop es;
		 continue;
		}
		asm pop es;
		ps->SilenceTimer=0;
//	   EventCount++;
		switch(ps->ReceiveFrameStatus) {
		  case RECEIVE_FRAME_HEADER:
//				ps->HeaderCRC=CalcHeaderCRC(c, ps->HeaderCRC );
				ps->HeaderCRC = table_crc8[ps->HeaderCRC^c];
				switch( ps->HEADERState ) {
						case HEADER_FrameType:
							  pframe->Frame.FrameType = c;
							  ps->HEADERState = HEADER_Length1;
							  break;
						case HEADER_Length1:
							  pframe->Frame.Length = c<<8;
							  ps->HEADERState = HEADER_Length2;
							  break;
						case HEADER_Length2:
							  pframe->Frame.Length += c;
							  ps->HEADERState = HEADER_HeaderCRC;
							  index = 0;
							  break;
						case HEADER_HeaderCRC:
							  if( ps->HeaderCRC != 0x55 )
							  {
								 pframe->flags.ReceivedInvalidFrame = TRUE;
							  }
							  else
								if(!pframe->Frame.Length)
								{
								 pframe->flags.ReceivedValidFrame = TRUE;
								}
								else
								{
								  ps->DataCRC=0xffff;
								  ps->ReceiveFrameStatus = RECEIVE_FRAME_DATA;
								  break;
								}
								next=1;
								break;
				}
				break;
		  case RECEIVE_FRAME_DATA:
//				ps->DataCRC=CalcDataCRC(c, ps->DataCRC);
				ps->DataCRC= (ps->DataCRC >> 8) ^ table_crc16[ (ps->DataCRC&0xFF) ^ c ];
				if( index < pframe->Frame.Length )
				{
				  pframe->Frame.Buffer[index++]=c;
				}
				else
				{
				 if( index++ == pframe->Frame.Length+1 )
				 {
				  if( ps->DataCRC==0x0f0b8 )
					 pframe->flags.ReceivedValidFrame = TRUE;
				  else
					 pframe->flags.ReceivedInvalidFrame = TRUE;
				  next=1;
				 }
				}
				break;
		}
		if( next ) break;
	  } //	end while(PTP_Receive_Frame_Status != PTP_IDLE)
	  ptp->ReceivedFramePool.Unlockhead();

	  if( ptp->connection_state == PTP_CONNECTED )
	  {
			resume(ptp->task+PTP_RECEPTION);
	  }
	  else
			resume( ptp->task );
	 }
	} // end if(MSTP_ReceiveFrameStatus != MSTP_IDLE)
//	else  frame lost
  }
//  ps->validint = 0;
  ps->Preamble1=ps->Preamble2=0;
//  ReceiveError=FALSE;
//  SilenceTimer=0;
  disable();
  ps->ReceiveFrameStatus = RECEIVE_FRAME_IDLE;
  suspend(ptp->task+PTP_RECEIVEFRAME);
 }
}
*/

void PTP::PTP_SendFrame( PTP_FRAME *frame, int task, int retry )
{
 char *p, buf[8];
 int crc,ind;
 unsigned int length, rate;
 unsigned long l;

//  rate = ReadBaudRate()/200;
  rate = ReadBaudRate() / 10;
  set_semaphore(&sendframe_flag);
/*
// in cazul in care celalalt receptioneaza mai incet

  if( lastsend_timesec == timestart )
  {
	 if ( microsec < lastsend_timemicro + 100000L )
		delay( 120 );
  }
  else
  {
	if( timestart == lastsend_timesec + 1 )
	 if ( 1000000L - lastsend_timemicro + microsec < 100000 )
		delay( 120 );
  }
*/
  if(frame)
  {
	if(!retry)
	{
	 frame->Preamble = 0x0FF55;
	 frame->HeaderCRC = 0x0FF;
	 p = (char *)&frame->FrameType;
// switch the low and high bytes of Length -> BAC frame
	 length = frame->Length;
	 frame->Length = ( (*((char *)&length))<<8 ) + *( (((char *)&length)+1) );
// end switch
	 for(int i=0; i<3; i++)
	 {
	  frame->HeaderCRC=CalcHeaderCRC(*p++, frame->HeaderCRC);
	 }
	 frame->HeaderCRC = ~frame->HeaderCRC;
	 ind=0;
	 if(length)
	 {
	  p = frame->Buffer;
	  crc = 0x0ffff;
	  for(ind=0; ind<length; ind++)
		crc=CalcDataCRC(*p++, crc);
	  crc = ~crc;
	  memcpy(&frame->Buffer[ind], &crc, 2);
	  ind += 2;
	 }
//	frame->Buffer[ind++]=0x0ff;  //pad MSTP
	}
	else
	{
	 ind  = ( (*((char *)&frame->Length))<<8 ) + *( (((char *)&frame->Length)+1) ) + 2;
	}
  }
/*
	else
	{
	memset(buf, 0x55, 6);
	buf[6]=0x015;
	buf[7]=0x0ff;
	ind = 0;
	frame = (PTP_FRAME *)&buf[0];
	}
*/
	delay(xdelay);
	Set_PIC_mask();
	port->isr_data->task = task;
	port->write_buffer( (char *)frame, ind+6, 1 );
	if( ind > (60L*(long)rate)/1000 )     // 60ms*Rate/1000
	{
		msleep(30L*1000L/rate+10);            // 1500char*1000ms/rate/50ms
		if( port->isr_data->tx_running )
		{
		l = timestart;
		while( port->isr_data->tx_running )
		{
		 if(timestart > l+2)
		 {
		  break;
		 }
		}
	  }
  }
  else
  {
	l = timestart;
	while( port->isr_data->tx_running )
	{
	 if(timestart > l+6)
	 {
		break;
	 }
	}
	}
	Routing_table[port_number].port_status_vars.SilenceTimer=0;
	Reset_PIC_mask();
	if( port->isr_data->tx_running )
	{
	 OUTPUT( port->isr_data->uart + INTERRUPT_ENABLE_REGISTER,
				IER_RX_DATA_READY + IER_MODEM_STATUS + IER_LINE_STATUS );
	 port->FlushTXBuffer();
	 port->resettxrunning();
	}
	else
	{
/*
	 l = timestart+2;
	 while( (INPUT(port->isr_data->uart + LINE_STATUS_REGISTER)&0x40)==0 )  //TRANSMITTER_EMPTY
	 {
		if(timestart > l)
		{
		break;
		}
	 }
*/
  }
//	HeartbeatTimer = T_HEARTBEAT;
//	tasks[task+PTP_TRANSMISSION].sleep = T_HEARTBEAT;
  Routing_table[port_number].port_status_vars.HeartbeatTimer = 0;
//  lastsend_timemicro = microsec;
//  lastsend_timesec = timestart;
  clear_semaphore(&sendframe_flag);
}

int PTP::init_idle_state(int m)
{
 PORT_STATUS_variables *ps;
 ps = &Routing_table[port_number].port_status_vars;
 memset( &ps->PTP_comm_status, 0, sizeof(PTP_COMMUNICATION_flags) );
 ps->PTP_comm_status.reception_blocked = Q_NOT_BLOCKED;
 ps->PTP_comm_status.transmission_blocked = 1;
 ps->physical_connection_state = SERIAL_ACTIVE;
 reception_state = 0;
 transmission_state = 0;
 activity = FREE;
 connection_state = PTP_DISCONNECTED;
 ps->connection = PTP_DISCONNECTED;
 if( media==MODEM_LINK )
 {
	 ps->physical_connection_state = CONNECTION_INACTIVE;
	connection_state = PTP_IDLE;
	ps->connection = PTP_IDLE;
	if(m && Read_mode()==SLAVE)
		modem_obj->Initialize();
	FlushRXbuffer();
	FlushTXbuffer();
 }
// memset(ReceivedFramePool.ReceivedFrame,0,sizeof(ReceivedFramePool.ReceivedFrame));
// ReceivedFramePool.Clear();
 SendFramePool.Clear();
 Routing_table[port_number].status=PTP_INSTALLED;
 memset( Routing_table[port_number].Port.networks_list, 0, sizeof(Routing_table[port_number].Port.networks_list));
}

int PTP::PTP_connection_termination_state_machine( PTP* ptp )
{
 int i, nextentry;
 int TimeOut;
 long l;
 PORT_STATUS_variables *ps;
 struct PTP_ReceivedFrame rec_frame;
 struct {
	  unsigned int Preamble;
	  byte FrameType;
	  unsigned int Length;
	  byte HeaderCRC;
	  char Buffer[6+2+1];  //2-CRC , 1-'FF'
	 } frame;
 ps = &Routing_table[ptp->port_number].port_status_vars;
 while( 1 )
 {
//	if( ptp->port_status == INSTALLED )
		switch( ptp->connection_state )
		{
			case PTP_IDLE:
				if( ptp->media == MODEM_LINK )  //	&& modem_active
				{
				 if( ps->ring >= ps->rings_number )
				 {
					if( ptp->modem_obj->Answer() != MODEM_SUCCESS )
					{
						ps->ring = 0;
//						ring_counts = 0;
						ptp->FlushRXbuffer();
						ptp->FlushTXbuffer();
					}
					else
					{
//						ring_counts = 0;
						ptp->activity = BUSY;
//						if(ptp->modem_obj->local_baud_rate==1200)
//							Delay(11000);
//						else
//							Delay(3500);
						ptp->port->FlushRXBuffer();
						ptp->port->FlushTXBuffer();
						ptp->connection_state = PTP_DISCONNECTED;
						ps->physical_connection_state = MODEM_ACTIVE;
						ps->connection = PTP_DISCONNECTED;
						ps->ring = 0;
						ptp->NL_parameters.primitive = DL_IDLE;
						break;
					}
				 }
				}
				suspend(ptp->task);
				break;
			case PTP_DISCONNECTED:
				if( ptp->NL_parameters.primitive == DL_CONNECT_REQUEST )
				{
					ptp->connection_state=OUTBOUND;
					ps->connection = PTP_SEND_TRIGGER_SEQ;
					ptp->NL_parameters.primitive = DL_IDLE;
					ptp->FlushTXbuffer();
					ptp->port->Write( trigger_sequence, strlen(trigger_sequence), 1000);
					l = timestart;
					while( ptp->port->isr_data->tx_running )
					{
					 if(timestart > l+6)
					 {
					  break;
					 }
					}
					ptp->RetryCount=0;
					break;
				}
				if( ps->connection == PTP_REC_TRIGGER_SEQ )
				{
					frame.FrameType = CONNECT_REQUEST;
					frame.Length = 0;
					ptp->PTP_SendFrame((PTP_FRAME  *)&frame, ps->task);
					ptp->RetryCount=0;
					ptp->connection_state = INBOUND;
					break;
				}
				Routing_table[ptp->port_number].status=PTP_INSTALLED;
				suspend(ptp->task);
/*
				if( ps->physical_connection_state==CONNECTION_INACTIVE )
				{
					ptp->init_idle_state();
				}
*/
				break;
			case OUTBOUND:
				/* Connect Request Received*/
				TimeOut=FALSE;
				msleep(T_CONN_REQ);
				if(ptp->ReceivedFramePool.RemoveEntry(&rec_frame)<0) TimeOut=TRUE;
//          Timeout
//			   if( ResponseTimer >= Tconn_rqst )
				if( !TimeOut && rec_frame.flags.ReceivedInvalidFrame ) TimeOut=TRUE;
				if( TimeOut )
				{
					if( ps->physical_connection_state!=CONNECTION_INACTIVE && ptp->RetryCount < N_RETRIES )
					{
					/*	Connect Request Timeout	*/
						ptp->FlushTXbuffer();
						ptp->port->Write( trigger_sequence, strlen(trigger_sequence), 1000 );
						l = timestart;
						while( ptp->port->isr_data->tx_running )
						{
						 if(timestart > l+6)
						 {
						  break;
						 }
					   }
						ptp->RetryCount++;
						break;
					}
					else
					{
					/*	Connect Request Failure	*/
					/* signal network layer	*/
/*						N_UNITDATA_parameters.primitive = DL_UNITDATA_INDICATION;*/
						ptp->NL_parameters.primitive = DL_CONNECT_ATTEMPT_FAILED;
//						ptp->NL_parameters.AtoN = 0;
//						ptp->NL_parameters.DtoN = 1;
//						networklayer();
						ptp->init_idle_state();
						break;
					}
				}

				if( rec_frame.flags.ReceivedValidFrame )
					if( rec_frame.Frame.FrameType == CONNECT_REQUEST )
					{
//						  ptp->ReceivedFramePool.Clear();
						  ptp->SendFramePool.Clear();

						  ps->PTP_comm_status.TxSequence_number = 0;
						  ps->PTP_comm_status.RxSequence_number = 0;
						  ptp->NL_parameters.primitive = DL_CONNECT_INDICATION;
//						  ptp->NL_parameters.AtoN = 0;
//						  ptp->NL_parameters.DtoN = 1;
//						  ptp->NL_parameters.npdu = rec_frame->Buffer;
//						  ptp->NL_parameters.length_npdu = rec_frame->Length;
//						  networklayer();
						  ptp->connection_state = PTP_CONNECTED;
						  Routing_table[ptp->port_number].status=PTP_ACTIVE;
//						  Routing_table[ptp->port_number].Port.network = 0xFFFF;
						  Routing_table[ptp->port_number].Port.network = 0;
						  ps->InactivityTimer = 0;
						  ps->connection = PTP_CONNECTED;
						  frame.FrameType = CONNECT_RESPONSE;
						  frame.Length = 0;
						  ptp->PTP_SendFrame((PTP_FRAME *)&frame, ps->task);

						  resume(ptp->task+PTP_reception);
						  resume(ptp->task+PTP_transmission);
							router(N_UNITDATArequest, I_Am_Router_To_Network, NULL, ptp->port_number,2);
							Delay(6000);
//						  router(N_UNITDATArequest, I_Am_Router_To_Network_Prop, NULL, ptp->port_number);
						  break;
					}
					break;
			case INBOUND:
			/*	The net layer has recognized that the calling device wishes to
			establish a BACnet connection, and the local device is waiting for
			a Connect Response frame from the calling device	*/
			/*	Valid Connect Response Received	*/
				TimeOut=FALSE;
				msleep(T_CONN_RSP);
				if(ptp->ReceivedFramePool.RemoveEntry(&rec_frame)<0) TimeOut=TRUE;
//          Timeout
//			   if( ResponseTimer >= Tconn_rqst )
				if( !TimeOut && rec_frame.flags.ReceivedInvalidFrame ) TimeOut=TRUE;
				if( TimeOut )
				{
					if( ps->physical_connection_state!=CONNECTION_INACTIVE && ptp->RetryCount < N_RETRIES )
					{
					/*	Connect Request Timeout	*/
						ptp->FlushTXbuffer();
						frame.FrameType = CONNECT_REQUEST;
						frame.Length = 0;
						ptp->PTP_SendFrame((PTP_FRAME *)&frame, ps->task, 1);
						ptp->RetryCount++;
						break;
					}
					else
					{
					/*	Connect Request Failure	*/
					/* signal network layer	*/
/*						N_UNITDATA_parameters.primitive = DL_UNITDATA_INDICATION;*/
						ptp->init_idle_state();
						break;
					}
				}
				if( rec_frame.flags.ReceivedValidFrame )
				{
					if( rec_frame.Frame.FrameType == CONNECT_RESPONSE )
					{
						if( !ptp->password_needed || ptp->password_OK )
						{
							  ps->InactivityTimer = 0;
							  ps->connection = PTP_CONNECTED;
							  ps->PTP_comm_status.TxSequence_number = 0;
							  ps->PTP_comm_status.RxSequence_number = 0;
							  ptp->connection_state = PTP_CONNECTED;
//							  ptp->ReceivedFramePool.Clear();
							  ptp->SendFramePool.Clear();
							  Routing_table[ptp->port_number].status=PTP_ACTIVE;
//							  Routing_table[ptp->port_number].Port.network = 0xFFFF;
							  Routing_table[ptp->port_number].Port.network = 0;
							  resume(ptp->task+PTP_reception);
							  resume(ptp->task+PTP_transmission);
								for(i=0; i<MAX_Routing_table; i++)
								{
								 if( (Routing_table[i].status&RS485_ACTIVE)==RS485_ACTIVE || (Routing_table[i].status&IPX_ACTIVE)==IPX_ACTIVE) break;
								}
								if(i<MAX_Routing_table)
								{
								 ptp->panel_info1 = ((class ConnectionData *)Routing_table[i].ptr)->panel_info1;
								}
								else
								{
								 ptp->panel_info1 = Panel_Info1;
								}
								Delay(3000);
								router(N_UNITDATArequest, I_Am_Router_To_Network_Prop, NULL, ptp->port_number,1);
								msleep(110);     // 6 sec
								router(N_UNITDATArequest, I_Am_Router_To_Network_Prop, NULL, ptp->port_number,1);
								break;
						}
						else
						{
								frame.FrameType = DISCONNECT_REQUEST;
								frame.Length = 1;
								frame.Buffer[0] = '02';
								ptp->PTP_SendFrame((PTP_FRAME *)&frame, ps->task);
								ptp->connection_state = PTP_DISCONNECTING;
								ptp->RetryCount=0;
								break;
						 }
					}
					if( rec_frame.Frame.FrameType == DISCONNECT_REQUEST )
					{
							frame.FrameType = DISCONNECT_RESPONSE;
							frame.Length = 0;
							ptp->PTP_SendFrame((PTP_FRAME *)&frame, ps->task);
							ptp->connection_state = PTP_DISCONNECTED;
							ps->connection=PTP_DISCONNECTED;
							ptp->activity = FREE;
							if( ptp->media==MODEM_LINK )
							{
								ptp->connection_state = PTP_IDLE;
								ps->connection = PTP_IDLE;
								ptp->modem_obj->Initialize();
							}
							break;
					}
				}
				break;
			case PTP_CONNECTED:
			/*	The connection procedure has been completed and the two devices
			are exchanging BACnet PDUs. The data link remains in this
			connection_state until termination	*/
				TimeOut=FALSE;
				suspend(ptp->task);
				/*	Connection Lost	*/
				if( ps->physical_connection_state!=CONNECTION_INACTIVE )
				/*	Network disconnect	*/
				{
				 if( ptp->NL_parameters.primitive == DL_DISCONNECT_REQUEST )
				 {
					ptp->NL_parameters.primitive = DL_IDLE;
					frame.FrameType = DISCONNECT_REQUEST;
					frame.Length = 0;
					ptp->PTP_SendFrame((PTP_FRAME *)&frame, ps->task);
//					ptp->ResponseTimer = 0;
					ptp->connection_state = PTP_DISCONNECTING;
					break;
				 }
				 if(ptp->ReceivedFramePool.RemoveEntry(&rec_frame)>=0)
				 {
				  if( rec_frame.flags.ReceivedValidFrame )
				  {
				 /*	Disconnect request received	*/
					if( rec_frame.Frame.FrameType == DISCONNECT_REQUEST )
					{
					 frame.FrameType = DISCONNECT_RESPONSE;
					 frame.Length = 0;
					 ptp->PTP_SendFrame((PTP_FRAME *)&frame, ps->task);
					 Delay(500);
					}
					if( rec_frame.Frame.FrameType == CONNECT_REQUEST )
					{
					 frame.FrameType = CONNECT_RESPONSE;
					 frame.Length = 0;
					 ptp->PTP_SendFrame((PTP_FRAME *)&frame, ps->task);
					 ptp->connection_state = PTP_CONNECTED;
					 break;
					}
				  }
				 }
				}
				router(N_UNITDATArequest, Initialize_Routing_Table, NULL, ptp->port_number, 1);
        delay(2000);
				router(N_UNITDATArequest, Initialize_Routing_Table, NULL, ptp->port_number, 1);
//				router(N_UNITDATArequest, I_Am_Router_To_Network_Prop, NULL, ptp->port_number,1);
        delay(2000);
				ptp->init_idle_state();
				break;
			case PTP_DISCONNECTING:
			/*	The network layer has requested termination of the data link. The
			device is waiting for a Disconnect Response frame from the peer device*/
				/* Disconnect Response Received */
				TimeOut=FALSE;
				msleep(T_CONN_RSP);
				if(ptp->ReceivedFramePool.RemoveEntry(&rec_frame)<0) TimeOut=TRUE;
//          Timeout
//			   if( ResponseTimer >= Tconn_rsp )
				if( !TimeOut && rec_frame.flags.ReceivedInvalidFrame ) TimeOut=TRUE;
				if( TimeOut )
				{
					if( ps->physical_connection_state!=CONNECTION_INACTIVE && ptp->RetryCount < N_RETRIES )
					{
						/*	Disconnect response timeout	*/
						frame.FrameType = DISCONNECT_REQUEST;
						frame.Length = 0;
						ptp->PTP_SendFrame((PTP_FRAME *)&frame, ps->task, 1);
						ptp->RetryCount++;
//						ptp->ResponseTimer=0;
						break;
					}
				}
				else
				if( rec_frame.flags.ReceivedValidFrame )
				{
					/*	Disconnect request received */
					if( rec_frame.Frame.FrameType == DISCONNECT_REQUEST )
					{
							frame.FrameType = DISCONNECT_RESPONSE;
							frame.Length = 0;
							ptp->PTP_SendFrame((PTP_FRAME *)&frame, ps->task);
							Delay(500);
					}
					else
					 if( rec_frame.Frame.FrameType != DISCONNECT_RESPONSE )
					 {
						/*	Disconnect response timeout	*/
						frame.FrameType = DISCONNECT_REQUEST;
						frame.Length = 0;
						ptp->PTP_SendFrame((PTP_FRAME *)&frame, ps->task, 1);
						ptp->RetryCount++;
//						ptp->ResponseTimer=0;
						break;
					 }
				}
				router(N_UNITDATArequest, Initialize_Routing_Table, NULL, ptp->port_number, 1);
        delay(2000);
				router(N_UNITDATArequest, Initialize_Routing_Table, NULL, ptp->port_number, 1);
//				router(N_UNITDATArequest, I_Am_Router_To_Network_Prop, NULL, ptp->port_number,1);
        delay(2000);
				ptp->init_idle_state();
				break;
		}
 }
}


int PTP::PTP_reception_state_machine( PTP *ptp )
{
 int i, nextentry;
 int TimeOut;
 struct PTP_ReceivedFrame rec_frame;
 struct {
	  unsigned int Preamble;
	  byte FrameType;
	  unsigned int Length;
	  byte HeaderCRC;
	  char Buffer[6+2+1];  //2-CRC , 1-'FF'
	 } sframe;
 PORT_STATUS_variables *ps;
 ps = &Routing_table[ptp->port_number].port_status_vars;

//	if( ptp->port_status == INSTALLED && ptp->connection_state == CONNECTED )
	while( 1 )
	{
		switch( ptp->reception_state )
		{
			case REC_IDLE:
			/*	The receiver is waiting for the data link to be established
				between the local device and the peer device. The receiver waits
				to be notified that a peer device is ready to communicate	*/
				/*	Connection Established	*/
				if( ptp->connection_state == PTP_CONNECTED )
				{
					 ps->PTP_comm_status.RxSequence_number = 0;
					 ps->PTP_comm_status.reception_blocked = Q_NOT_BLOCKED;
					 ptp->reception_state = REC_READY;
					 break;
				}
				suspend(ptp->task+PTP_reception);
				break;
/*			case REC_NO_READY: - only in version II */
			case REC_READY:
			/*	The device is ready to receive frames from the peer device	*/
				if(ptp->ReceivedFramePool.RemoveEntry(&rec_frame)>=0)
				{
				 if( rec_frame.flags.ReceivedValidFrame )
				 {
					ps->InactivityTimer = 0;
					if( rec_frame.Frame.FrameType == DATA_0 || rec_frame.Frame.FrameType == DATA_1 )
					{
						ptp->reception_state = DATA;
						break;
					}
					if( DATA_ACK_0_XOFF <= rec_frame.Frame.FrameType &&
						  rec_frame.Frame.FrameType <= DATA_ACK_1_XON )
					{
						ptp->reception_state = DATA_ACK;
						break;
					}
					if( DATA_NAK_0_XOFF <= rec_frame.Frame.FrameType &&
						  rec_frame.Frame.FrameType <= DATA_NAK_1_XON )
					{
						ptp->reception_state = DATA_NAK;
						break;
					}
/*
// tratat in ISR_8250
					if( rec_frame.Frame.FrameType == HEARTBEAT_XON )
					{
					  ptp->PTP_comm_status.transmission_blocked = 0;
					  resume( ptp->task+PTP_transmission );
					  break;
					}
					if( rec_frame.Frame.FrameType == HEARTBEAT_XOFF )
					{
						ptp->PTP_comm_status.transmission_blocked = 1;
						resume( ptp->task+PTP_transmission );
						break;
					}
*/
					if( rec_frame.Frame.FrameType == TEST_REQUEST )
					{
/*
						if( ptp->SendFramePool.NextFreeEntry() )
						{
							frame = &ptp->SendFramePool.Entry[SendFramePool.HeadFrame];
							frame->FrameType = TEST_RESPONSE;
							frame->Length = 0;
							PTP_send_frame();
							PTP_comm_status.received_valid_frame = 0;
							ps->InactivityTimer = 0;
							reception_state = REC_READY;
							break;
						}
*/
					}
					if( rec_frame.Frame.FrameType == TEST_RESPONSE )
					{
/*
						NL_parameters.primitive = DL_UNITDATA_INDICATION;
						NL_parameters.npdu = rec_frame->Buffer;
						NL_parameters.length_npdu = rec_frame->Length;
						NL_parameters.AtoN = 0;
						NL_parameters.DtoN = 1;
						networklayer();
						PTP_comm_status.received_valid_frame = 0;
						ps->InactivityTimer = 0;
						reception_state = REC_READY;
						break;
*/
					}
					break;
				 }
				 if( rec_frame.flags.ReceivedInvalidFrame )
				 {
						/*	Bad Data0 / Full buffers	*/
						ps->InactivityTimer = 0;
						if( rec_frame.Frame.FrameType == DATA_0 )
						{
							/* Discard frame */
							/* Clear( &rec_queue );*/
							if( ps->PTP_comm_status.reception_blocked == Q_BLOCKED )
									sframe.FrameType = DATA_NAK_0_XOFF;
							else
									sframe.FrameType = DATA_NAK_0_XON;
							sframe.Length = 0;
							ptp->PTP_SendFrame((PTP_FRAME *)&sframe, ps->task+PTP_reception);
							break;
						}
						/*	Bad Data1 / Full buffers	*/
						if( rec_frame.Frame.FrameType == DATA_1 )
						{
							/* Discard Frame */
							/*Clear( &rec_queue );*/
							if( ps->PTP_comm_status.reception_blocked == Q_BLOCKED )
									sframe.FrameType = DATA_NAK_1_XOFF;
							else
									sframe.FrameType = DATA_NAK_1_XON;
							sframe.Length = 0;
							ptp->PTP_SendFrame((PTP_FRAME *)&sframe, ps->task+PTP_reception);
							break;
						}
						/* Discard Frame */
						/*	Clear( &rec_queue );	*/
						break;
				 }
				}
				if( ptp->connection_state == PTP_DISCONNECTED )
				{
						ptp->reception_state = REC_IDLE;
						break;
				}
				suspend(ptp->task+PTP_reception);
				break;
			case DATA:
			/*	In this state the device has received a Data frame for processing */
				if( rec_frame.Frame.FrameType == DATA_0 )
				{
					if( ps->PTP_comm_status.RxSequence_number == 1 )
					{
							if( ps->PTP_comm_status.reception_blocked == Q_BLOCKED )
//								Duplicate0_FullBuffers
								sframe.FrameType = DATA_ACK_0_XOFF;
							else
//								Duplicate0
								sframe.FrameType = DATA_ACK_0_XON;
//								Discard frame
					}
					else
					{
							if( ps->PTP_comm_status.reception_blocked == Q_BLOCKED )
							{
//									Data0_FullBuffers
//									Clear( &rec_queue );
								sframe.FrameType = DATA_NAK_0_XOFF;
							}
							else
							{
								//	DL_UNITDATA.indication
								ptp->NL_parameters.primitive = DL_UNITDATA_INDICATION;
								ptp->NL_parameters.AtoN = 0;
								ptp->NL_parameters.DtoN = 1;
								ptp->NL_parameters.npdu = rec_frame.Frame.Buffer;
								ptp->NL_parameters.length_npdu = rec_frame.Frame.Length;

								ps->PTP_comm_status.RxSequence_number = 1;
								if( ps->PTP_comm_status.reception_blocked == Q_NOT_BLOCKED )
								//	New Data0
									sframe.FrameType = DATA_ACK_0_XON;
								if( ps->PTP_comm_status.reception_blocked == Q_ALMOST_BLOCKED )
								//	Last Data0
									sframe.FrameType = DATA_ACK_0_XOFF;
								sframe.Length = 0;
								ptp->PTP_SendFrame((PTP_FRAME *)&sframe, ps->task+PTP_reception);

								 if( !STSMremoveflag )
									 networklayer( DL_UNITDATAindication, NORMALmessage, 0, 0, 0,
										 rec_frame.Frame.Buffer, rec_frame.Frame.Length, NULL, 0, 0, SERVER, ptp->port_number);
								 ptp->reception_state = REC_READY;
								 break;
							}
						}
				}
				if( rec_frame.Frame.FrameType == DATA_1 )
				{
					if( ps->PTP_comm_status.RxSequence_number == 0 )
					{
							if( ps->PTP_comm_status.reception_blocked == Q_BLOCKED )
//								Duplicate0_FullBuffers
								sframe.FrameType = DATA_ACK_1_XOFF;
							else
//								Duplicate0
								sframe.FrameType = DATA_ACK_1_XON;
//								Discard frame
					}
					else
					{
							if( ps->PTP_comm_status.reception_blocked == Q_BLOCKED )
							{
//									Data0_FullBuffers
//									Clear( &rec_queue );
								sframe.FrameType = DATA_NAK_1_XOFF;
							}
							else
							{
								//	DL_UNITDATA.indication
								ptp->NL_parameters.primitive = DL_UNITDATA_INDICATION;
								ptp->NL_parameters.AtoN = 0;
								ptp->NL_parameters.DtoN = 1;
								ptp->NL_parameters.npdu = rec_frame.Frame.Buffer;
								ptp->NL_parameters.length_npdu = rec_frame.Frame.Length;

								ps->PTP_comm_status.RxSequence_number = 0;
								if( ps->PTP_comm_status.reception_blocked == Q_NOT_BLOCKED )
								//	New Data0
									sframe.FrameType = DATA_ACK_1_XON;
								if( ps->PTP_comm_status.reception_blocked == Q_ALMOST_BLOCKED )
								//	Last Data0
									sframe.FrameType = DATA_ACK_1_XOFF;
								sframe.Length = 0;
								ptp->PTP_SendFrame((PTP_FRAME *)&sframe, ps->task+PTP_reception);

								if( !STSMremoveflag )
									networklayer( DL_UNITDATAindication, NORMALmessage, 0, 0, 0,
									       rec_frame.Frame.Buffer, rec_frame.Frame.Length, NULL, 0, 0, SERVER, ptp->port_number);
								ptp->reception_state = REC_READY;
								break;
							}
					}
				}
				sframe.Length = 0;
				ptp->PTP_SendFrame((PTP_FRAME *)&sframe, ps->task+PTP_reception);
				ptp->reception_state = REC_READY;
				break;
			case DATA_ACK:
/*
				//	In this state the device has received a Data Ack frame for processing
				if( ps->PTP_comm_status.TxSequence_number == 0 )
				{
					if( rec_frame.Frame.FrameType  == DATA_ACK_1_XON )
					{
						//	Duplicate XON
						ps->PTP_comm_status.transmission_blocked = 0;
					}
					if( rec_frame.Frame.FrameType == DATA_ACK_1_XOFF )
					{
						//	Duplicate XOFF
						ps->PTP_comm_status.transmission_blocked = 1;
					}
					if( rec_frame.Frame.FrameType == DATA_ACK_0_XON )
					{
						//	Ack0 XON
						ps->PTP_comm_status.ack0received = 1;
						ps->PTP_comm_status.transmission_blocked = 0;
						resume( ptp->task+PTP_transmission );
					}
					if( rec_frame.Frame.FrameType == DATA_ACK_0_XOFF )
					{
						//	Ack0 XOFF
						ps->PTP_comm_status.ack0received = 1;
						ps->PTP_comm_status.transmission_blocked = 1;
						resume( ptp->task+PTP_transmission );
					}
					ptp->reception_state = REC_READY;
					break;
				}
				if( ps->PTP_comm_status.TxSequence_number == 1 )
				{
					if( rec_frame.Frame.FrameType == DATA_ACK_0_XON )
					{
						//	Duplicate XON
						ps->PTP_comm_status.transmission_blocked = 0;
					}
					if( rec_frame.Frame.FrameType == DATA_ACK_0_XOFF )
					{
						//	Duplicate XOFF
						ps->PTP_comm_status.transmission_blocked = 1;
					}
					if( rec_frame.Frame.FrameType == DATA_ACK_1_XON )
					{
						//	Ack1 XON
						ps->PTP_comm_status.ack1received = 1;
						ps->PTP_comm_status.transmission_blocked = 0;
						resume( ptp->task+PTP_transmission );
					}
					if( rec_frame.Frame.FrameType == DATA_ACK_1_XOFF )
					{
						//	Ack1 XOFF
						ps->PTP_comm_status.ack1received = 1;
						ps->PTP_comm_status.transmission_blocked = 1;
						resume( ptp->task+PTP_transmission );
					}
					ptp->reception_state = REC_READY;
					break;
				}
*/
				ptp->reception_state = REC_READY;  //DATA_ACK tratat in ISR_PC8250
				break;
			case DATA_NAK:
				/*	In this state the device has received a Data Nak
																					frame for processing */
/*
				if( ps->PTP_comm_status.TxSequence_number == 0 )
				{
					if( rec_frame.Frame.FrameType == DATA_NAK_1_XON )
					{
						//	Duplicate XON
						ps->PTP_comm_status.transmission_blocked = 0;
					}
					if( rec_frame.Frame.FrameType == DATA_NAK_1_XOFF )
					{
						//	Duplicate XOFF
						ps->PTP_comm_status.transmission_blocked = 1;
					}
					if( rec_frame.Frame.FrameType == DATA_NAK_0_XON )
					{
						//	Ack0 XON
						ps->PTP_comm_status.nak0received = 1;
						ps->PTP_comm_status.transmission_blocked = 0;
					}
					if( rec_frame.Frame.FrameType == DATA_NAK_0_XOFF )
					{
						//	Ack0 XOFF
						ps->PTP_comm_status.nak0received = 1;
						ps->PTP_comm_status.transmission_blocked = 1;
					}
					ptp->reception_state = REC_READY;
					break;
				}
				if( ps->PTP_comm_status.TxSequence_number == 1 )
				{
					if( rec_frame.Frame.FrameType == DATA_NAK_0_XON )
					{
						//	Duplicate XON
						ps->PTP_comm_status.transmission_blocked = 0;
					}
					if( rec_frame.Frame.FrameType == DATA_NAK_0_XOFF )
					{
						//	Duplicate XOFF
						ps->PTP_comm_status.transmission_blocked = 1;
					}
					if( rec_frame.Frame.FrameType == DATA_NAK_1_XON )
					{
						//	Ack1 XON
						ps->PTP_comm_status.nak1received = 1;
						ps->PTP_comm_status.transmission_blocked = 0;
					}
					if( rec_frame.Frame.FrameType == DATA_NAK_1_XOFF )
					{
						//	Ack1 XOFF
						ps->PTP_comm_status.nak1received = 1;
						ps->PTP_comm_status.transmission_blocked = 1;
					}
					ptp->reception_state = REC_READY;
					break;
				}
*/
				ptp->reception_state = REC_READY;  //DATA_NAK tratat in ISR_PC8250
				break;

		}
	}
}


int PTP::PTP_transmission_state_machine(  PTP *ptp )
{
 PTP_FRAME *pframe;
 int i, nextentry;
 struct {
	  unsigned int Preamble;
	  byte FrameType;
	  unsigned int Length;
	  byte HeaderCRC;
	  char Buffer[6+2+1];  //2-CRC , 1-'FF'
	 } sframe;

 PORT_STATUS_variables *ps;
 ps = &Routing_table[ptp->port_number].port_status_vars;
 while( 1 )
 {
//	if( ser_ptp->port_status == INSTALLED && connection_state == CONNECTED )
		switch( ptp->transmission_state )
		{
			case TR_IDLE:
				/*	In this state the transmitter is waiting for the data link to be
				established between the local device and the peer device. The
				transmitter waits to be notified that a peer device is ready to
				communicate	*/
				if( ptp->connection_state == PTP_CONNECTED )
				{
						if( ps->PTP_comm_status.reception_blocked == Q_NOT_BLOCKED )
							sframe.FrameType = HEARTBEAT_XON;
						else
							sframe.FrameType = HEARTBEAT_XOFF;
						sframe.Length = 0;
						ptp->PTP_SendFrame((PTP_FRAME *)&sframe, ps->task+PTP_transmission);
						ps->PTP_comm_status.TxSequence_number = 0;
						ptp->transmission_state = TR_BLOCKED;
						msleep(4);
						break;
				}
				suspend(ptp->task+PTP_transmission);
				break;
			case TR_BLOCKED:
			/*	In this state the peer device has indicated that it is not ready
			to receive data frames. The local device may have data ready to transmit.
			The local device periodically transmits a Heartbeat frame to maintain
			the data link, and waits for the peer device to become ready to receive
			data or for the termination of the data link.	*/
				/*	Send Request	*/
/*
				if( ptp->NL_parameters.primitive = DL_UNITDATA_REQUEST )
				{
					break;
				}
*/
				/*	Peer Receiver Ready	*/
				if( !ps->PTP_comm_status.transmission_blocked )
				{
					ptp->transmission_state = TR_READY;
					break;
				}
				if( ptp->connection_state == PTP_DISCONNECTED )
				{
					ptp->transmission_state = TR_IDLE;
					break;
				}
				suspend(ptp->task+PTP_transmission);
/*
				msleep(ptp->HeartbeatTimer);
				ptp->HeartbeatTimer = tasks[ptp->task+PTP_TRANSMISSION].sleep;
				if( ptp->HeartbeatTimer < 2 )
*/
				if( Routing_table[ptp->port_number].port_status_vars.HeartbeatTimer >= T_HEARTBEAT )
				{
				 if( ps->PTP_comm_status.reception_blocked == Q_NOT_BLOCKED )
					sframe.FrameType = HEARTBEAT_XON;
				 else
					sframe.FrameType = HEARTBEAT_XOFF;
				 sframe.Length = 0;
				 ptp->PTP_SendFrame((PTP_FRAME *)&sframe, ps->task+PTP_transmission);
				 msleep(4);
				}
				break;
			case TR_READY:
			/*	The peer device has indicated its readiness to receive data frames
			but the local device has no data ready to transmit. The local device
			periodically transmits a Heartbeat frame to maintain the data link, and
			waits for a local request to transmit data or for the termination of
			the data link	*/
				if( !ps->PTP_comm_status.transmission_blocked )
				{
				 if ( ptp->SendFramePool.RemoveEntry(&pframe) >= 0 )
				 {
					if( ps->PTP_comm_status.reception_blocked == Q_NOT_BLOCKED )
					{
					 if( pframe->FrameType == DATA_0 )
						pframe->FrameType += ps->PTP_comm_status.TxSequence_number;
					 ptp->PTP_SendFrame(pframe, ps->task+PTP_transmission);
//					 ptp->SendFramePool.AdvanceTail();
					 ptp->RetryCount = 0;
//					 ptp->AcknowledgementTimer = 0;
					 ptp->transmission_state = TR_PENDING;
					 ptp->ResponseTimer = T_RESPONSE;
				   msleep( 4 );
					 break;
					}
				 }
				}
				else
				{
					ptp->transmission_state = TR_BLOCKED;
					break;
				}
//				msleep(ptp->HeartbeatTimer);
//				ptp->HeartbeatTimer = tasks[ptp->task+PTP_TRANSMISSION].sleep;
				suspend(ptp->task+ PTP_transmission);
				if( ptp->connection_state == PTP_DISCONNECTED )
				{
					ptp->transmission_state = TR_IDLE;
					break;
				}
				/*	Send Request	*/
				if( Routing_table[ptp->port_number].port_status_vars.HeartbeatTimer >= T_HEARTBEAT )
				{
				 if( ps->PTP_comm_status.reception_blocked == Q_NOT_BLOCKED )
					sframe.FrameType = HEARTBEAT_XON;
				 else
					sframe.FrameType = HEARTBEAT_XOFF;
				 sframe.Length = 0;
				 ptp->PTP_SendFrame((PTP_FRAME *)&sframe, ps->task+PTP_transmission);
				}
				break;
			case TR_PENDING:
				/*	Send Request	*/
				/*	Disconnected	*/
				if( ptp->connection_state == PTP_DISCONNECTED )
				{
					ptp->SendFramePool.AdvanceTail();
					ptp->transmission_state = TR_IDLE;
					break;
				}
				/*	Receive Acknowledgement	*/
				if( ( ps->PTP_comm_status.ack0received && ps->PTP_comm_status.TxSequence_number == 0 ) ||
					 ( ps->PTP_comm_status.ack1received && ps->PTP_comm_status.TxSequence_number == 1 ) )
				{
					ptp->SendFramePool.AdvanceTail();
					ps->PTP_comm_status.TxSequence_number = 1 - ps->PTP_comm_status.TxSequence_number;
					ps->PTP_comm_status.ack0received = 0;
					ps->PTP_comm_status.ack1received = 0;
					ptp->transmission_state = TR_READY;
/*
					if ( ptp->HeartbeatTimer > T_RESPONSE - ptp->ResponseTimer )
						ptp->HeartbeatTimer -= T_RESPONSE - ptp->ResponseTimer;
					else
						ptp->HeartbeatTimer = 1;
*/
					break;
				}
				msleep(ptp->ResponseTimer-4);
				ptp->ResponseTimer = tasks[ptp->task+PTP_transmission].sleep;
				if( !ptp->ResponseTimer )
//				&& ( ( ptp->PTP_comm_status.reject0received && ptp->PTP_comm_status.TxSequence_number == 0 ) ||
//						( ptp->PTP_comm_status.reject1received && ptp->PTP_comm_status.TxSequence_number == 1 ) ) )
//						(	ptp->response_timer > T_RESPONSE ) )
				{
					if( ptp->RetryCount < N_RETRIES )
					{
						/*	Retry	*/
						ptp->RetryCount++;
//						ptp->transmission_state = TR_PENDING;
						ptp->ResponseTimer = T_RESPONSE;
						ptp->PTP_SendFrame(pframe, ps->task+PTP_transmission, 1);
						break;
					}
					else
					{
						/*	Retries failed	*/
						ptp->SendFramePool.AdvanceTail();
						ptp->RetryCount = 0;
//						response_timer = 0;
						ptp->transmission_state = TR_READY;
						break;
					}
				}
				break;
		}
 }
}

int PTP::sendframe(int length_npci, char* npci, int length_asdu_npdu, char* asdu_npdu, int length_apci, char *apci)
{
 int nextentry;
 PTP_FRAME *pframe;

	 if( (nextentry = SendFramePool.NextFreeEntry()) < 0 ) return 0;
	 pframe = &SendFramePool.Frame[nextentry];
//	 pframe->Length = length_npci+length_apci+length_asdu_npdu;
	 pframe->FrameType = DATA_0;
	 pframe->Length = length_npci+length_apci+length_asdu_npdu;
	 memcpy(pframe->Buffer, npci, length_npci);
	 if( length_apci )
	  memcpy(&pframe->Buffer[length_npci], apci, length_apci);
	 if( length_asdu_npdu )
	  memcpy(&pframe->Buffer[length_npci+length_apci], asdu_npdu, length_asdu_npdu);
	 SendFramePool.Unlockhead();
	 resume(task+PTP_transmission);
	 return 1;
}

int PTP::sendframe(PTP_FRAME *frame)
{
 int nextentry;
 PTP_FRAME *pframe;

	 if( (nextentry = SendFramePool.NextFreeEntry()) < 0 ) return 0;
	 pframe = &SendFramePool.Frame[nextentry];
	 pframe->FrameType = frame->FrameType;
	 pframe->Length = frame->Length;
	 SendFramePool.Unlockhead();
	 resume(task+PTP_transmission);
	 return 1;
}


ASYNCRON::ASYNCRON( int c_port, int n_port ):Serial( c_port, n_port )
{
 PORT_STATUS_variables *ps;
 ps = &Routing_table[port_number].port_status_vars;
 memset( &ps->PTP_comm_status, 0, sizeof(PTP_COMMUNICATION_flags) );
 program_number = 0;
 Install_port();
}

int ASYNCRON::ASYNCRON_task( ASYNCRON* async )
{
 int i, nextentry;
 int TimeOut;
 long l;
 PORT_STATUS_variables *ps;
 ps = &Routing_table[async->port_number].port_status_vars;
 while( 1 )
 {
//
// run programs
//
	if( async->program_number )
	{
	 if( Routing_table[async->port_number].status == ASYNCRON_INSTALLED )
	 {
		set_semaphore(&t3000_flag);
		if( ptr_panel->program_codes[async->program_number-1])       //  pointer to code
		 if( ptr_panel->programs[async->program_number-1].com_prg )    //  run as a normal program
		 {
			exec_program(async->program_number-1,ptr_panel->program_codes[async->program_number-1],stack_com,1);
		 }
		clear_semaphore(&t3000_flag);
	 }
	}
	msleep(10);
 }
}

int inkey(char* adr, int num, int max, int port)
{
	if( port!=COM0 )
	{
		if( num > max ) num = max;
		if( Routing_table[port].status == ASYNCRON_INSTALLED )
		{
		 ((class ASYNCRON *)Routing_table[port].ptr)->port->Read( (char *)adr, num);
		 return (((class ASYNCRON *)Routing_table[port].ptr)->port->ByteCount);
		}
	}
	return 0;
}

