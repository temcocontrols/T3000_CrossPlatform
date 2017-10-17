#ifndef _PTP_H
#define _PTP_H				/* avoid recompilation */

#include "serial.h"
#include "rs485.h"

#define Uint unsigned int
#define Byte unsigned char

typedef enum
	{
		CONNECTION_INACTIVE, MODEM_ACTIVE, SERIAL_ACTIVE 
	}
	Physical_Connection_State;


typedef enum
	{
		NO_ROUTE_TO_DNET = 0x01, ROUTER_BUSY, UNKNOWN_MESSAGE_TYPE, OTHER_ERROR
	}
	Router_Rejection_reasons;

typedef enum
	{
		PTP_IDLE, PTP_PREAMBLE, PTP_HEADER, PTP_HEADER_CRC, PTP_DATA,
		PTP_DATA_CRC, INBOUND, OUTBOUND, PTP_CONNECTED, PTP_DISCONNECTED, PTP_DISCONNECTING,
		PTP_REC_TRIGGER_SEQ, PTP_SEND_TRIGGER_SEQ, MSTP_CONNECTED, MSTP_DISCONNECTED,
		IPX_CONNECTED, IPX_DISCONNECTED, TCPIP_CONNECTED, TCPIP_DISCONNECTED,
    NETBIOS_CONNECTED, NETBIOS_DISCONNECTED 
	}
	PTP_States;

typedef enum { REC_IDLE, REC_READY, DATA_ACK, DATA_NAK, DATA } PTP_REC_States;

typedef enum { TR_IDLE, TR_PENDING, TR_READY, TR_BLOCKED } PTP_TR_States;

typedef enum
	{
		HEARTBEAT_XOFF = 0, HEARTBEAT_XON, DATA_0, DATA_1, DATA_ACK_0_XOFF,
		DATA_ACK_1_XOFF, DATA_ACK_0_XON, DATA_ACK_1_XON, DATA_NAK_0_XOFF,
		DATA_NAK_1_XOFF, DATA_NAK_0_XON, DATA_NAK_1_XON, CONNECT_REQUEST,
		CONNECT_RESPONSE, DISCONNECT_REQUEST, DISCONNECT_RESPONSE,
		TEST_REQUEST, TEST_RESPONSE
	}
	Standard_Frame_Types;

typedef enum
	{
		DL_IDLE, DL_UNITDATA_REQUEST, DL_UNITDATA_INDICATION, DL_UNITDATA_RESPONSE,
		DL_CONNECT_REQUEST, DL_CONNECT_INDICATION, DL_CONNECT_RESPONSE,
		DL_DISCONNECT_REQUEST, DL_TEST_REQUEST, DL_TEST_RESPONSE,
		DL_CONNECT_ATTEMPT_FAILED
	}
	DL_Primitives;

typedef enum
	{
		CONFIRMED, UNCONFIRMED, ERROR_SERV, REJECT, SEGMENT_ACK,
		ABORT_SERV, CONNECT, DISCONNECT
	}
	Services;

typedef enum { Q_BLOCKED, Q_ALMOST_BLOCKED, Q_NOT_BLOCKED } Blocked_States;

typedef enum
	{
		APP_REQUEST, APP_INDICATION, APP_RESPONSE, APP_CONNECT_REQUEST,
		APP_CONNECT_INDICATION, APP_CONNECT_RESPONSE, APP_DISCONNECT_REQUEST,
		APP_TEST_REQUEST, APP_TEST_RESPONSE
	}
	APP_Primitives;

typedef enum
	{
		APP_IDLE, APP_SEGMENTING_REQUEST, APP_SEGMENTED_REQUEST,
		APP_AWAIT_CONFIRMATION, APP_AWAIT_RESPONSE,
		APP_SEGMENTED_CONFIRMATION, APP_SEGMENTING_RESPONSE
	}
	APP_States;

typedef struct {
	unsigned ReceivedValidFrame   	:1;
	unsigned ReceivedInvalidFrame	   :1;
	unsigned sending_frame_now			:1;
	unsigned send_done					:1;
	unsigned send_ok						:1;
	unsigned retry_count					:2;
	unsigned in_use						:1;
	}	FRAME_flags;


typedef struct {
	FRAME_flags flags;
	uint DataIndex;
	byte FrameType;
	byte Destination;
	byte Source;
	uint Length;
	byte HeaderCRC;
	char Buffer[MAXFRAMEBUFFER+2+1];
	uint DataCRC;
	} FRAME_ENTRY;

typedef struct {
	  unsigned int Preamble;
	  byte FrameType;
	  unsigned int Length;
	  byte HeaderCRC;
	  char Buffer[MAXFRAMEBUFFER+2+1];  //2-CRC , 1-'FF'
	 } PTP_FRAME;

struct PTP_ReceivedFrame {
	  PTP_FRAME   Frame;
	  FRAME_flags flags;
     char  status;
//	  char  ReceivedValidFrame;
//	  char  ReceivedInvalidFrame;
};

class PTP_RECEIVEDFRAMEPOOL
{
 public:
	struct PTP_ReceivedFrame ReceivedFrame[PTP_NMAXRECEIVEDFRAMEPOOL];
 public:
	PTP_RECEIVEDFRAMEPOOL(void);
//	int  NextFreeEntry(void);
//	void *NextFreeEntry(int);
	void *NextFreeEntry(void);
	int  RemoveEntry(void *);
};

class PTP_SENDFRAMEPOOL:public SENDFRAMEPOOL
{
 public:
	PTP_FRAME Frame[PTP_NMAXSENDFRAMEPOOL];
 public:
	int RemoveEntry(PTP_FRAME **pframe);
	void AdvanceTail(void);
};

typedef struct
{
	DL_Primitives primitive;
	int destination_panel;
	Uint DNET;
	char dest_MAC_address[6];
	Byte dest_LSAP;
	int source_panel;
	Uint SNET;
	char source_MAC_address[6];
	Byte source_LSAP;
	char apci[10];
	Uint length_apci;
	char *asdu;
	Uint length_asdu;
	char *apdu;
	Uint length_apdu;
	char *npdu;
	Uint length_npdu;
	unsigned priority						:2;
	unsigned data_expecting_reply		:1;
	unsigned AtoN							:1;
	unsigned DtoN							:1;
	unsigned NtoA							:1;
	unsigned NtoD							:1;
	unsigned unused						:1;
} UNITDATA_PARAMETERS;


class PTP : public Serial
{
	public:
		UNITDATA_PARAMETERS NL_parameters;
		ulong frame_send_timer;
		unsigned ResponseTimer;
		byte  RetryCount;
		unsigned sendframe_flag;
		Byte password_needed, password_OK;
		byte task;
//		PTP_States   PTP_ReceiveFrameStatus;
//		int  LengthReceivedClientAPDU;
//		char *PTRReceivedClientAPDU;
		PTP_SENDFRAMEPOOL     SendFramePool;
		PTP_RECEIVEDFRAMEPOOL ReceivedFramePool;
		byte connection_state;

	private:

//		byte physical_connection_state;

//		uint char_period;
//		char trigger_sequence[7] = "BACnet\x0d";
//		char trigger_sequence[7];
//		byte rec_trigger_sequence;
//		long lastsend_timemicro;
//		unsigned long  lastsend_timesec;

		byte reception_state;
		byte transmission_state;
//		byte rec_frame_state;
//		byte send_frame_state;
		byte ReceptionBlocked;

	public:
      void PTP_SendFrame( PTP_FRAME *frame, int task, int retry=0 );
		int sendframe(int=0 , char*p1 = NULL, int=0, char*p2 = NULL, int=0, char*p3 = NULL);
		int sendframe(PTP_FRAME *frame);
      int init_idle_state(int m=1);
//		static int PTP_receive_frame_state_machine( PTP *ptp );
		static int PTP_connection_termination_state_machine( PTP *ptp );
		static int PTP_reception_state_machine( PTP *ptp );
		static int PTP_transmission_state_machine( PTP *ptp );

		PTP( int c_port, int nr_port );
};

class ASYNCRON : public Serial
{
	public:
		byte task;
      int  program_number;
	public:
		ASYNCRON( int c_port, int nr_port );
		static int ASYNCRON_task( ASYNCRON* async );
};

	void crc_header( char octet, unsigned char *header_CRC );
	void crc_data( char octet, uint *data_CRC );

/*
#ifdef _PTP_DOT_C

	void start_send();

	int Wake_Up_Transmit(void);

#else

	extern void start_send();

	extern int Wake_Up_Transmit(void);

#endif
*/

#endif


