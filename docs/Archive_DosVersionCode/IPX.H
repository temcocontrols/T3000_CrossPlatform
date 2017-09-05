#ifndef _IPX_H
#define _IPX_H

#include "net_bac.h"

#define IPX_SPX_OpenSocket           0x00
#define IPX_SPX_CloseSocket          0x01
#define IPX_GetLocalTarget           0x02
#define IPX_SendPacket               0x03
#define IPX_ListenForPacket          0x04
#define IPX_Schedule_IPX_Event       0x05
#define IPX_CancelEvent              0x06
#define IPX_GetIntervalMarker        0x08
#define IPX_GetInternetworkAddress   0x09
#define IPX_RelenquishControl        0x0A
#define IPX_DisconnectFromTarget     0x0B

#define NODE_ADR_LENGTH       6
#define NETWORK_ADR_LENGTH    4

#define IPX_PACKET_TYPE       4

#define DOS_INT            0x21
#define DOS_MULTIPLEX      0x2F
#define IPX_SPX_INSTALLED  0xFF

#define MAX_NAME_SIZE        47
#define MAX_FRAGMENT_COUNT    2
#define IPX_MAX_CONNECTIONS 250

#define  USER_BINDERY_OBJECT_TYPE 0x0001

#define LONG_LIVED_SOCKET  0x0FF
#define SHORT_LIVED_SOCKET 000

typedef struct
{
	unsigned char NetworkNumber[NETWORK_ADR_LENGTH];
	unsigned char NodeAddress[NODE_ADR_LENGTH];

} IpxNetworkAddress;

typedef struct
{
	unsigned char NetworkNumber[NETWORK_ADR_LENGTH];
	unsigned char NodeAddress[NODE_ADR_LENGTH];
	unsigned int  Socket;

} TargetAddress;

typedef struct
{
	byte Data[4];

} IpxArea;

typedef struct
{
	uint ConnectionId;
	byte Unused[2];

} SpxArea;

typedef struct
{
	void far *Ptr;                   /* fill these in */
	uint      Length;                /* fill these in */

} FragmentDescriptorStruct;

typedef struct
{
	void far *LinkAddress;
	void (far *EventServiceRoutine)();           /* fill this in  */
	byte     InUseFlag;
	byte     CompletionCode;
	uint     SocketNumber;                       /* fill this in  */

	byte     WorkSpace[4];

	byte     DriverWorkSpace[12];
	byte     ImmediateAddress[NODE_ADR_LENGTH];  /* IPX send ==> fill in */
	uint     FragmentCount;                      /* fill this in  */

	FragmentDescriptorStruct FragmentDescriptor[MAX_FRAGMENT_COUNT];

}	Ecb;

typedef struct
{
	uint 		CheckSum;
	uint 		Length;
	byte 		TransportControl;
	byte 		PacketType;                /* IPX send ==> fill this in */
	byte 		DestinationNetwork[NETWORK_ADR_LENGTH]; /* fill this in */
	byte 		DestinationNode[NODE_ADR_LENGTH];       /* fill this in */
	uint 		DestinationSocket;                      /* fill this in */
	byte 		SourceNetwork[NETWORK_ADR_LENGTH];
	byte 		SourceNode[NODE_ADR_LENGTH];
	uint 		SourceSocket;

}	IpxHeader;

typedef struct
{
	Ecb					ecb;
	IpxHeader  	header;

	unsigned in_use    : 4;      /* used to indicate if the CB is used or not
																			== 0 => not used, != 0 => in use */
	unsigned index     : 3;     /* command associated with this CB */
	unsigned type      : 1;     /* command type associated with this CB */

} IpxControlBlock;


class IPX : public NET_BAC
{
		IpxControlBlock	*array;
		uint 	socket;

		unsigned int real_array_DS;
		unsigned int Ipx_segment_call;
		unsigned int Ipx_offset_call;

		int IpxCall( REAL_MODE_REGISTERS *rm_ptr );
		int swab( unsigned int data );
		int IxpGetInternetworkAddress( IpxNetworkAddress *AddressStructPtr );
		int IpxSpxOpenSocket( unsigned int *SocketNumber );
		int IpxSpxCloseSocket( unsigned int *SocketNumber );
		int IpxGetLocalTarget( byte *request, byte *reply );
		int IpxDisconnectFromTarget( TargetAddress *target );
		int IpxListenForPacket( byte ecb_index, byte frame_index, uint socket );
		int IpxSendPacket( byte ecb_index, char *packet, uint socket, uint length, byte *adr_ptr );
		int IpxScheduleIpxEvent( void );
		int IpxRelinquishControl( void );

	private:
		/* virtual functions that are overloaded */
		void ResetInUseField( byte index );
		virtual byte TestInUseField( byte index );
		virtual byte TestCompletion( byte index );
		virtual void CopySourceAddress( byte source_index, byte cb_index );
		virtual void ResetControlBlock( byte index );
		virtual byte FinalResultCode( byte index );

		virtual int TestDriverPresence( void );

		virtual int SendFrame( byte list_index );
		virtual int ReceiveFrame( byte list_index );

	public:

		IPX( Panel_info1 *info, byte task_no );
		int GetLocalAddress( void );
		int CloseCommunication( void );
		int OpenCommunication( void );
    void InitIPX( void );
		~IPX();
};

#endif //_IPX_H

