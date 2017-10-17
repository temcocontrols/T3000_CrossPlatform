#ifndef _NET_BAC_H
#define _NET_BAC_H

//#include "netbios.h"
#include "baseclas.h"
#include "rs485.h"
#include "ptp.h"
#include "serial.h"
#include "aio.h"

#define NET_NMAXSENDFRAME       4
#define NET_NMAXRECEIVEFRAME    4

typedef enum { SENDING_DG, SENT_DG, SEND_ERROR, IDLE_SD } SENDING_DG_STATUS;

typedef enum { WAITING_DG, RECEIVED_DG, REC_ERROR, IDLE_DG } DATAGRAM_STATUS;


typedef enum { DRIVER_INSTALLED, DRIVER_NOT_INSTALLED } Driver_Status;

typedef struct  {
		FRAME Frame;
		char  ReceivedValidFrame;
		char  ReceivedInvalidFrame;
		char  status;
} NET_RECEIEVE_FRAME;

class NET_RECEIVEDFRAMEPOOL
{
	public:
		NET_RECEIEVE_FRAME *ReceivedFrame;
	public:
		void Init_frame_pool( NET_RECEIEVE_FRAME *buffer );
		void *NextFreeEntry(void);
		int  RemoveEntry( NET_RECEIEVE_FRAME *frame);
};

/*
typedef struct {
		unsigned int Preamble;
		byte FrameType;
		byte Destination;
		byte Source;
		unsigned int Length;
		byte HeaderCRC;
		char Buffer[MAXFRAMEBUFFER+2+1];  //2-CRC , 1-'FF'
	 } FRAME;
*/
typedef struct {
	uint Preamble;
	byte FrameType;
	byte Destination;
	byte Source;
	uint Length;
	byte HeaderCRC;
	char Buffer[MAXFRAMEBUFFER];
	uint DataCRC;
//  byte Terminator;
	unsigned char being_used    : 1;
	unsigned char locked        : 1;
	unsigned char reply_flag    : 1;
	unsigned char number        : 2;
	unsigned char delay         : 2;
	unsigned char sending       : 1;
} SEND_FRAME_ENTRY;


class NET_SENDFRAMEPOOL
{
	byte no_of_used_frames;
	public:
		SEND_FRAME_ENTRY *Frame;
	public:
		void Init_frame_pool( SEND_FRAME_ENTRY *buffer );
//		SEND_FRAME_ENTRY *NextFreeEntry( int reply, int command=0 );
		SEND_FRAME_ENTRY *NextFreeEntry( int reply );
		SEND_FRAME_ENTRY *FrameAvailable( int reply );
		void RemoveSentEntry( SEND_FRAME_ENTRY *frame_ptr );
		void Unlock_frame( SEND_FRAME_ENTRY *frame );
		int  FramesInUse( void );
};

typedef struct
{
		signed char  number;
		byte  state;
		byte  type;
		union {
		FRAME *rec;
		SEND_FRAME_ENTRY *send;
		} frame;

} Command_State;

typedef struct
{
	unsigned char l;
	unsigned char h;
} REGISTER_2x8;

typedef union
{
	REGISTER_2x8  r;
	unsigned int  w;
	unsigned long e;
} REGISTER_DATA;

typedef struct
{
	REGISTER_DATA   DI;
	REGISTER_DATA   SI;
	REGISTER_DATA   BP;
	REGISTER_DATA   RES;
	REGISTER_DATA   BX;
	REGISTER_DATA   DX;
	REGISTER_DATA   CX;
	REGISTER_DATA   AX;
	unsigned int    flags;
	unsigned int    ES;
	unsigned int    DS;
	unsigned int    FS;
	unsigned int    GS;
	unsigned int    IP;
	unsigned int    CS;
	unsigned int    SP;
	unsigned int    SS;

	} REAL_MODE_REGISTERS;



class NET_BAC : public ConnectionData
{
	protected:

		Command_State     	send_list[NET_NMAXSENDFRAME];
		Command_State     	rec_list[NET_NMAXRECEIVEFRAME];
		byte            		rec_comm_active;
		byte            		rec_br_comm_active;

		byte                ControlBlocksQueueSize;
		byte    		        available_CBs;
		byte                last_assigned_CB;

		unsigned int 				real_Send_pool_DS;
		unsigned int 				real_Receive_pool_DS;

	public:

		Driver_Status       state;
    int                 port_state;
		T3000_ERROR			 		comm_status;
		char 					 			*data;

		NET_SENDFRAMEPOOL   SendFramePool;
		FRAME 							*ReceiveFramePool;

		byte                activity;
		byte                routing_entry;
		unsigned long       time;
		byte                end_task;
		int                 dayofyear;

	protected:

		void InitNetData( Panel_info1 *info, byte task_no );
		void ReleaseRealMemory( void );
		int Get_ControlBlock( void );
		void Release_ControlBlock( byte index );

		virtual void ResetInUseField( byte index ) = 0;
		virtual byte TestInUseField( byte index ) = 0;
		virtual byte TestCompletion( byte index ) = 0;
		virtual void CopySourceAddress( byte source_index, byte cb_index ) = 0;
		virtual void ResetControlBlock( byte index ) = 0;
		virtual byte FinalResultCode( byte index ) = 0;

		virtual int TestDriverPresence( void ) = 0;

		virtual int SendFrame( byte list_index ) = 0;
		virtual int ReceiveFrame( byte list_index ) = 0;

public:

		void initData( Panel_info1 *info );
		virtual int OpenCommunication( void ) = 0;
		virtual int CloseCommunication( void ) = 0;
		virtual int GetLocalAddress( void ) = 0;
//		int Sendinfo( int status, int panel, int dest=255 );
		void SignOff( void );
		int  CheckForCommandCompletion( void );
		void NetControl( void );
		void sendFrameTask();
		void receiveFrameTask();
};

#endif //_NET_BAC_H


