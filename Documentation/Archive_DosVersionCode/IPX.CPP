#ifdef NET_BAC_COMM

#include <windows.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <mem.h>
#include <bios.h>
#include <conio.h>
#include <string.h>
#include <process.h>
#include "gwin.h"
#include "baseclas.h"
#include "mtkernel.h"
#include "t3000def.h"
#include "graph.h"
#include "net_bac.h"
#include "ipx.h"

#define ON   1
#define OFF  0

int NET_EXIT;

extern char Station_NAME[NAME_SIZE];
extern int  Station_NUM;
extern int mode_text;
extern int mode_graph;

extern void *DisplayMessage(int lx, int ly, int rx, int ry, char *message, GWindow **Er, int fcolor=Black);
extern void DisplayMessageT(int lx, int ly, int rx, int ry, char *title, char *message, GWindow **Er1, int fcolor=Black, GWindow *Er2=NULL, long delay=0);
extern void DeleteMessage(GWindow *p);
extern void mputnum( unsigned long num );
extern long timestart;

IPX         *pipx;
char        IPX_enabled=1, tmp_IPX_enabled;
int ipxtempNetworkAddress;
char ipxfinished;

IPX::IPX( Panel_info1 *info, byte task_no )
{
	unsigned long par_sel;
	unsigned int i;
	SEND_FRAME_ENTRY *sendframe_buffer;

	ControlBlocksQueueSize = 8;
	par_sel = GlobalDosAlloc( (unsigned int)(ControlBlocksQueueSize*sizeof( IpxControlBlock ) ) );
	i = par_sel&0x0ffff;  /* i = protDS */
	real_array_DS = par_sel>>16;      /* j = realDS */
	array = ( IpxControlBlock far *)MK_FP( i, 0 );

  InitIPX();

	if( TestDriverPresence() == 0 )
	{
		InitNetData( info, task_no  );
		state = DRIVER_INSTALLED;
		media = IPX_LINK;
		socket = 0x4444;
	}
	else
		state = DRIVER_NOT_INSTALLED;
}

IPX::~IPX()
{
	ReleaseRealMemory();
	GlobalDosFree( FP_SEG( array ) );
}

void IPX::InitIPX( void )
{
	memset( array, 0, ControlBlocksQueueSize*sizeof(IpxControlBlock));
	available_CBs = ControlBlocksQueueSize - 1;
	last_assigned_CB = ControlBlocksQueueSize - 2;
}

int IPX::IpxSpxOpenSocket( unsigned int *SocketNumber )
{
	REAL_MODE_REGISTERS real_data_regs;

	memset( &real_data_regs, 0, sizeof( REAL_MODE_REGISTERS ) );

	real_data_regs.AX.w = SHORT_LIVED_SOCKET;
	real_data_regs.BX.w = IPX_SPX_OpenSocket;
	real_data_regs.DX.w = swab( *SocketNumber );
	real_data_regs.CS = Ipx_segment_call;
	real_data_regs.IP = Ipx_offset_call;

	if( !IpxCall( &real_data_regs ) )
	{
		switch( real_data_regs.AX.w & 0x0FF ) /* CompletionCode */
		{
			case 0x00 :
					*SocketNumber = real_data_regs.DX.w;
					return 0;
			case 0xFE :
//				printf("[Failure, full socket table]");
					break;
			case 0xFF :
//					printf("[Failure, socket already open]");
					break;
			default   :
//					printf("[Unknown completion code (%02X)]", CompletionCode);
					break;
		}
		return ( real_data_regs.AX.w & 0x0FF );
	}
	else
		return -1;
}

int IPX::IpxSpxCloseSocket( unsigned int *SocketNumber )
{
	REAL_MODE_REGISTERS real_data_regs;

	memset( &real_data_regs, 0, sizeof( REAL_MODE_REGISTERS ) );

	real_data_regs.AX.w = SHORT_LIVED_SOCKET;
	real_data_regs.BX.w = IPX_SPX_CloseSocket;
	real_data_regs.DX.w = *SocketNumber;
	real_data_regs.CS = Ipx_segment_call;
	real_data_regs.IP = Ipx_offset_call;

	if( !IpxCall( &real_data_regs ) )
		return 0;
	else
		return 1;

}

int IPX::IpxGetLocalTarget( byte *request, byte *reply )
{
}

int IPX::IpxDisconnectFromTarget( TargetAddress *target )
{
	REAL_MODE_REGISTERS real_data_regs;
	unsigned int real_ES, selector;
	unsigned long par_sel;
	TargetAddress *rm_target;

	par_sel = GlobalDosAlloc( (unsigned int)sizeof( TargetAddress ) );
	selector = par_sel&0x0ffff;
	real_ES = par_sel>>16;
	rm_target = ( TargetAddress far *)MK_FP( real_ES, selector );
	memcpy( rm_target, target, sizeof( TargetAddress ) );

	memset( &real_data_regs, 0, sizeof( REAL_MODE_REGISTERS ) );

	real_data_regs.BX.w = IPX_DisconnectFromTarget;
	real_data_regs.ES = real_ES;
	real_data_regs.SI.w = 0;
	real_data_regs.CS = Ipx_segment_call;
	real_data_regs.IP = Ipx_offset_call;

	real_ES = IpxCall( &real_data_regs );
	memcpy( target, rm_target, sizeof( TargetAddress ) );

	if( !real_ES )
		return 0;
	else
		return 1;
}

int IPX::IpxListenForPacket( byte ecb_index, byte frame_index, uint socket )
{
	REAL_MODE_REGISTERS real_data_regs;
	Ecb *ecb_ptr;

	ecb_ptr = (Ecb*)(array+ecb_index);

	ecb_ptr->EventServiceRoutine = NULL;
	ecb_ptr->SocketNumber = socket;
	ecb_ptr->FragmentCount = 2;
	/*  real mode pointer to IpxHeader*/
	ecb_ptr->FragmentDescriptor[0].Ptr = MK_FP( real_array_DS, ( FP_OFF(ecb_ptr)+ sizeof(Ecb) ) );
	ecb_ptr->FragmentDescriptor[0].Length = sizeof(IpxHeader);
	/*  real mode pointer to FRAME */
	ecb_ptr->FragmentDescriptor[1].Ptr = MK_FP( real_Receive_pool_DS, frame_index*sizeof(FRAME));
	ecb_ptr->FragmentDescriptor[1].Length = sizeof(FRAME);

	real_data_regs.BX.w = IPX_ListenForPacket;
	real_data_regs.ES = real_array_DS;
	real_data_regs.SI.w = ecb_index*sizeof(IpxControlBlock);
	real_data_regs.CS = Ipx_segment_call;
	real_data_regs.IP = Ipx_offset_call;

	if( !IpxCall( &real_data_regs ) )
		return real_data_regs.AX.r.l;
	else
		return -1;
}

int IPX::IpxSendPacket( byte ecb_index, char *packet, uint socket, uint length, byte *adr_ptr )
{
	REAL_MODE_REGISTERS real_data_regs;
	Ecb *ecb_ptr;
	IpxHeader *header_ptr;

	ecb_ptr = (Ecb *)(array+ecb_index);

	header_ptr = (IpxHeader *)( (char*)(ecb_ptr) + sizeof(Ecb) );

	header_ptr->PacketType = IPX_PACKET_TYPE;
	memcpy( header_ptr->DestinationNetwork, adr_ptr, NETWORK_ADR_LENGTH+NODE_ADR_LENGTH+2 );
	memcpy( ecb_ptr->ImmediateAddress, adr_ptr+NETWORK_ADR_LENGTH, NODE_ADR_LENGTH );

	ecb_ptr->EventServiceRoutine = NULL;
	ecb_ptr->SocketNumber = socket;
	ecb_ptr->FragmentCount = 2;
	/*  real mode pointer to IpxHeader*/
	ecb_ptr->FragmentDescriptor[0].Ptr = MK_FP( real_array_DS, FP_OFF(header_ptr) );
	ecb_ptr->FragmentDescriptor[0].Length = sizeof(IpxHeader);
	/*  real mode pointer to FRAME */
	ecb_ptr->FragmentDescriptor[1].Ptr = MK_FP( real_Send_pool_DS, FP_OFF(packet));
	ecb_ptr->FragmentDescriptor[1].Length = length;

	real_data_regs.CS = Ipx_segment_call;
	real_data_regs.IP = Ipx_offset_call;

	real_data_regs.BX.w = IPX_SendPacket;
	real_data_regs.ES = real_array_DS;
	real_data_regs.SI.w = FP_OFF( ecb_ptr );
	real_data_regs.CS = Ipx_segment_call;
	real_data_regs.IP = Ipx_offset_call;

	if( !IpxCall( &real_data_regs ) )
		return 0;
	else
		return -1;
}

/*
int IPX::IpxScheduleIpxEvent( void )
{
}
*/

int IPX::IpxRelinquishControl( void )
{
	REAL_MODE_REGISTERS real_data_regs;
	real_data_regs.BX.w = IPX_RelenquishControl;
	real_data_regs.CS = Ipx_segment_call;
	real_data_regs.IP = Ipx_offset_call;
	disable();
	if( !IpxCall( &real_data_regs ) )
	{
		enable();
		return 0;
	}
	else
	{
		enable();
		return -1;
	}
}

/* virtual functions that are overloaded */
void IPX::ResetInUseField( byte index )
{
	array[index].in_use = 0;
}

byte IPX::TestInUseField( byte index )
{
	return array[index].in_use;
}

byte IPX::TestCompletion( byte index )
{
	//IpxRelinquishControl();
	if( array[index].ecb.InUseFlag == 0 )
		return 1;
	else
		return 0;
}

void IPX::CopySourceAddress( byte source_index, byte cb_index )
{
 if( source_index < 32 && source_index >=0 )
 {
	station_list[source_index].state = ON;
	memset( station_list[source_index].hard_name, 0, 16 );
	/*  copy the following fields from the received header
	byte 		SourceNetwork[NETWORK_ADR_LENGTH];
	byte 		SourceNode[NODE_ADR_LENGTH];
	uint 		SourceSocket;
	*/
	memcpy( station_list[source_index].hard_name+4, array[cb_index].header.SourceNetwork , 12 );
 }
}

void IPX::ResetControlBlock( byte index )
{
	memset( &array[index], 0, sizeof(IpxControlBlock));
	array[index].in_use = 7;
}

byte IPX::FinalResultCode( byte index )
{
	return array[index].ecb.CompletionCode;
}

int IPX::SendFrame( byte list_index )
{
	SEND_FRAME_ENTRY *frame;
	char dest_adr[12];
	byte status;

	frame = send_list[list_index].frame.send;

	memset( dest_adr, 0, 12 );
	if( frame->Destination == 0x0FF )
	{
		memcpy( dest_adr, station_list[panel_info1.panel_number-1].hard_name+4, 12 );
		memset( dest_adr+4, '\xFF', 6 );
	}
	else
		memcpy( dest_adr, station_list[frame->Destination-1].hard_name+4, 12 );

	status = IpxSendPacket( send_list[list_index].number, (char*)frame, socket, frame->Length+8, dest_adr );
	return status;
}

int IPX::ReceiveFrame( byte list_index )
{
	byte status;
	status = IpxListenForPacket( rec_list[list_index].number, list_index, socket );
	return status;
}

int IPX::GetLocalAddress( void )
{
	int status;
	status = IxpGetInternetworkAddress( ( IpxNetworkAddress * )
											 ( station_list[panel_info1.panel_number-1].hard_name+4 ) );
	memcpy( station_list[panel_info1.panel_number-1].hard_name+14, &socket, 2 );
	return status;
}

int IPX::CloseCommunication( void )
{
	return IpxSpxCloseSocket( &socket );
}

int IPX::OpenCommunication( void )
{
	return IpxSpxOpenSocket( &socket );
}

////////////////////////////////////////////////////

int net_bac_task( void )
{
		DisplayMessageT( 20, 6, 60, 10, NULL, "  Initializing adapter parameters... ", NULL, Blue, NULL, 1000);
		if( pipx->GetLocalAddress()  )
		{
//			delay( 3000 );
			DisplayMessageT( 20, 6, 60, 10, NULL, "          Adapter error !!!            Network services unavailable !!!", NULL, Blue, NULL, 3000);
			NET_EXIT = 1;
		}
		else
		{
			if( pipx->OpenCommunication() )
			{
//				delay( 3000 );
				DisplayMessageT( 20, 6, 60, 10, NULL, "          Adapter error !!!            Network services unavailable !!!", NULL, Blue, NULL, 3000);
				NET_EXIT = 1;
			}
			else
			{
//				delay( 3000 );
				DisplayMessageT( 20, 6, 60, 10, NULL, " Adapter succesfully initialized !!!      Network services available !!!", NULL, Blue, NULL, 1500);
			}
		}
//		delay( 3000 );
//		D.GReleaseWindow();
//		tasks[NETWORK1].delay_time = 120000L;

		while( !NET_EXIT || NET_EXIT==2 )
		{
		 pipx->time = timestart;
		 while( !NET_EXIT )
		 {
			pipx->activity = 0;
			pipx->NetControl();
			if( !pipx->activity )
				msleep( 4 );      // 2
		 }
		 if(NET_EXIT==2)
		 {
			pipx->SignOff();
			ipxfinished = 1;
			pipx->CloseCommunication();
			suspend(NETWORK1);
			NET_EXIT = 0;
			pipx->OpenCommunication();
			ipxfinished=0;
//   	  tasks[NETWORK1].delay_time = 120000;
		 }
		}
		pipx->SignOff();
		pipx->CloseCommunication();
		pipx = NULL;
//		suspend( NETWORK1 );
		kill_task( NETWORK1 );
		return 1;
/*
		GWindow D(mode_text?20:200, mode_text?7:150, mode_text?60:500, mode_text?11:200, NO_STACK,0);
		DisplayMessageT( 20, 6, 60, 10, NULL, "  Initializing adapter parameters... ", NULL, Blue, &D);
		if( pipx->GetLocalAddress()  )
		{
			delay( 3000 );
			D.GReleaseWindow();
			DisplayMessageT( 20, 6, 60, 10, NULL, "          Adapter error !!!            Network services unavailable !!!", NULL, Blue, &D);
			NET_EXIT = 1;
		}
		else
		{
			if( pipx->OpenCommunication() )
			{
				delay( 3000 );
				D.GReleaseWindow();
				DisplayMessageT( 20, 6, 60, 10, NULL, "          Adapter error !!!            Network services unavailable !!!", NULL, Blue, &D);
				NET_EXIT = 1;
			}
			else
			{
				delay( 3000 );
				D.GReleaseWindow();
				DisplayMessageT( 20, 6, 60, 10, NULL, " Adapter succesfully initialized !!!      Network services available !!!", NULL, Blue, &D);
			}
		}
		delay( 3000 );
		D.GReleaseWindow();
		pipx->time = timestart;
		while( !NET_EXIT )
		{
			pipx->activity = 0;
			pipx->NetControl();
			if( !pipx->activity )
//				suspend( NETWORK1 );
				msleep( 2 );
		}

		pipx->SignOff();
		pipx->CloseCommunication();
		pipx = NULL;
		suspend( NETWORK1 );
		return 1;
*/
}


#endif



