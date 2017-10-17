#define ROUTER

#include <windows.h>
#include <graphics.h>
#include "t3000def.h"
#include "aio.h"
#include "ptp.h"
#include "net_bac.h"
#define ON   1
#define OFF  0
/*
int rr3;
extern char rrr_buf[20];
*/
extern int Station_NUM;

// status :   0  - free
//            0x05 PTP installed   ( 0000 0101 )
//            0x07 PTP active      ( 0000 0111 )
//            0x11 RS485 installed { 0001 0001 )
//            0x13 RS485 active    { 0001 0011 )
//            ETHERNET             { 0010 0011 )

extern int  station_num;
extern int local_panel;
extern int timepoints;
extern char wantpointsentry;
extern char iamnewonnet;
extern char netpointsflag;
extern NETWORK_POINTS	_far network_points_list[MAXNETWORKPOINTS];
extern Comm_Info *comm_info;
extern Panel *ptr_panel;

extern int	get_point_info(Point_info *point_info, char **des=NULL, char **label=NULL, char **ontext=NULL, char **offtext=NULL, char pri=0, int network = 0xFFFF);
extern int net_call(int command, int arg,  char *data, uint *length , int dest,
				 int network, int others=0, int timeout=TIMEOUT_NETCALL,
				 char *returnargs=NULL, int *length_returnargs=NULL,
				 char *sendargs=NULL, int length_sendargs=0, char bytearg=0, int port=-1);
extern int generatealarm(char *mes, int prg, int panel, int type, char alarmatall,char indalarmpanel,char *alarmpanel,char printalarm);

extern ROUTING_TABLE Routing_table[MAX_Routing_table];
extern char action;

NetworkSession NetSession[5];
int ind_sess;
int remote_net;
char network_points_flag, new_alarm_flag, sendinfoflag;
int ipxport=-1, rs485port=-1;
// command: 0 - update routing table

//int router(int service, int command, int network=LOCALNETWORK, int MACadr=0, int port_number=-1, char termination_time_value=60)
// send=2  send only PTP in OUTBOUND state
// send=1  send Iamrouter even there is no other port installed ( used only in PTP )

int router(int service, int command, ROUTER_PARAMETERS *r=NULL, int	port_number=-1, int send=0)
{
 signed char nextentry;
 FRAME *pframe;
 char s,t,npci[40];
 int length_npci,i,j,k,l,m,m1;
// Serial *sptr;
 ConnectionData *cdata;

 if( service==N_UNITDATArequest )
 {
	if( command==Who_Is_Router_To_Network )
	{
/*
		 npci[1]=0x80;
		 npci[2]=Who_Is_Router_To_Network;
		 npci[3]=DNET;
		 for(j=0; j<MAX_Routing_table; j++)
		 {
			if(Routing_table[i].status&PTP_ACTIVE && i<>port)
			 (class PTP *)Routing_table[i].ptr->sendframe(npci, 4);
		 }

	npci[0]=0x01;
	npci[1]=0x80;
	npci[2]=Who_Is_Router_To_Network;
	for(int i=0; i<MAX_Routing_table; i++)
	{
	 if( Routing_table[i].status&&PTP_ACTIVE && i<>port_number)
	 {
			length_npci=2;
			if(network<>-1)
			{
			 npci[2]=network;
			 length_npci=3;
			}
			if( (nextentry = SendFramePool.NextFreeEntry()) < 0 ) return 0;
		  pframe = &SendFramePool.Frame[nextentry];
		  pframe->FrameType = BACnetDataNotExpectingReply;
		  pframe->Destination = 255;
		  pframe->Source = TS;
		  pframe->Length = length_npci;
		  memcpy(pframe->Buffer, npci, length_npci);
		  SendFramePool.Unlockhead();
//		  networklayer( N_UNITDATArequest, NORMALmessage, LOCALNETWORK, 255, TS, asdu, i, apci, length_apci, BACnetDataNotExpectingReply, CLIENT, Routing_table[i].ptr);
	 }
	 if( Routing_table[i].status&0x07 )
	 {
	 }
	}
*/
	}
	if( command==Establish_Connection_To_Network )
	{
		if(port_number>=0)
		{
		 if( (Routing_table[port_number].status&PTP_INSTALLED) == PTP_INSTALLED )
		 {
			 if(!(Routing_table[port_number].status^PTP_ACTIVE) ) return 0;
			 ((class PTP *)Routing_table[port_number].ptr)->NL_parameters.primitive = DL_CONNECT_REQUEST;
			 blocked_resume( Routing_table[port_number].port_status_vars.task );
		 }
		}
	}
}
if( command==I_Am_Router_To_Network || command==I_Am_Router_To_Network_Prop || command==Initialize_Routing_Table)
{
 if(service==N_UNITDATArequest)
 {
	npci[0]=0x01;        //VERSION
	npci[1]=0xF0;        //network message, DNET, DLEN, Hopcount, SNET,SLEN=0
	npci[2]=0xFF;           //global networks
	npci[3]=0xFF;           //global networks
	npci[4]=0;                //broadcast MAC DADR
//	memcpy( &npci[5], &NetworkAddress, 2);   //SNET
	l = NetworkAddress;
	memcpy( &npci[5], &l, 2);   //SNET
	npci[7]=Station_NUM;      //SADR
	npci[8]=5;                //HopCount
	npci[9]=command;           //I_Am_Router_To_Network;
	l = 10;
	if( command==I_Am_Router_To_Network || command==I_Am_Router_To_Network_Prop )
	{
	 if(send==2)
	 {  // send only PTP in OUTBOUND state
			length_npci = l;
			if(!(Routing_table[port_number].status^PTP_ACTIVE))
			{
			 if(port_number>=0)
			 {
				cdata = (class ConnectionData *)Routing_table[port_number].ptr;
				m = cdata->panel_info1.network;
			 }
	     memcpy( &npci[5], &m, 2);   //SNET
			 ((class PTP *)Routing_table[port_number].ptr)->sendframe(length_npci, npci);
			}
	 }
	 else
	 {
		if( command==I_Am_Router_To_Network_Prop )
		 npci[l++]=VendorID;
		for(k=0; k<MAX_Routing_table; k++)
		{
		 length_npci = l;
		 if( (Routing_table[k].status&PORT_ACTIVE)==PORT_ACTIVE )
		 {
			t=0;
			for(i=0; i<MAX_Routing_table; i++)
			{
//		 if( i!=k && !Routing_table[i].status )
//			t++;
			 if( i!=k && ( (Routing_table[i].status&PORT_ACTIVE)==PORT_ACTIVE) )
			 {
//				t++;
//		  if( Routing_table[i].Port.network!=0xFFFF )
				if( Routing_table[i].Port.network )
				{
//			if( Routing_table[i].Port.network!=NetworkAddress )
				 s=0;
//				 if( (Routing_table[i].status&RS485_ACTIVE)==RS485_ACTIVE ||
//						 (Routing_table[i].status&IPX_ACTIVE)==IPX_ACTIVE )
				 {
					if( Routing_table[i].Port.network!=Routing_table[k].Port.network )
					{
					 memcpy(&npci[length_npci], &Routing_table[i].Port.network, 2);
					 length_npci += 2;
					 if( command==I_Am_Router_To_Network_Prop )
					 {
						npci[length_npci]=0; npci[length_npci+1]=0;
						if( (Routing_table[i].status&PTP_ACTIVE)==PTP_ACTIVE )
						 npci[length_npci] = Routing_table[i].Port.address;
						length_npci += 2;
					 }
					 s=1;
					}
         }
				 for(j=0; j<MAX_reachable_networks; j++)
//					if( Routing_table[i].Port.networks_list[j].status >= TEMPORARY_UNREACHABIL )
					if( Routing_table[i].Port.networks_list[j].status == REACHABLE )
					{
					 if( Routing_table[i].Port.networks_list[j].network!=Routing_table[k].Port.network )
					 {
						memcpy(&npci[length_npci], &Routing_table[i].Port.networks_list[j].network, 2);
						length_npci += 2;
						if( command==I_Am_Router_To_Network_Prop )
						{
						 if(Routing_table[i].Port.networks_list[j].half_router_address==0)
							npci[length_npci] = Routing_table[i].Port.networks_list[j].router_address;
						 else
							npci[length_npci] = Routing_table[i].Port.networks_list[j].half_router_address;
						 npci[length_npci+1]=0;
						 length_npci += 2;
						}
						s=1;
					 }
					}
				 if(s) t++;
				}
			 }
			}
			cdata = (class ConnectionData *)Routing_table[k].ptr;
			m = cdata->panel_info1.network;
			memcpy( &npci[5], &m, 2);   //SNET
			if(!(Routing_table[k].status^PTP_ACTIVE))
			{
			 ((class PTP *)Routing_table[k].ptr)->sendframe(length_npci, npci);
			}
			if( (Routing_table[k].status&RS485_ACTIVE)==RS485_ACTIVE )
			{
			 if( t||send )
			 {
			// build frame
				if( (nextentry = ((class MSTP *)Routing_table[k].ptr)->SendFramePool.NextFreeEntry()) >= 0 )
				{
				 pframe = &((class MSTP *)Routing_table[k].ptr)->SendFramePool.Frame[nextentry];
				 pframe->FrameType = BACnetDataNotExpectingReply;
				 pframe->Destination = 255;
				 pframe->Source = TS;
				 pframe->Length = length_npci;
				 memcpy(pframe->Buffer, npci, length_npci);
//				((class MSTP *)Routing_table[k].ptr)->SendFramePool.Unlockhead();
				 ((class MSTP *)Routing_table[k].ptr)->SendFramePool.status[nextentry]=1;
				}
			 }
			}
			if( (Routing_table[k].status&IPX_ACTIVE)==IPX_ACTIVE ||
					(Routing_table[k].status&TCPIP_ACTIVE)==TCPIP_ACTIVE   )
			{
			 if( t||send )
			 {
			// build frame
					pframe = (FRAME *)((class NET_BAC *)Routing_table[k].ptr)->SendFramePool.NextFreeEntry(0);
					if( pframe == NULL )
						return -1;
					pframe->FrameType = BACnetDataNotExpectingReply;
					pframe->Destination = 255;
					pframe->Source = Station_NUM;
					pframe->Length = length_npci;
					memcpy(pframe->Buffer, npci, length_npci);
					((class NET_BAC *)Routing_table[k].ptr)->SendFramePool.Unlock_frame(
																									 (SEND_FRAME_ENTRY*)pframe );
					resume( ((class NET_BAC *)Routing_table[k].ptr)->task_number );
			 }
			}
		 }
		}
	 }
	}
	if( command==Initialize_Routing_Table)
	{
//   1 byte :  Number of ports
//   2 bytes:  Connected DNET
//   1 byte :  Port ID   :  0  -  purje the DNET from routing table
//
	 if(port_number!=-1)
	 {
		m1 = l++;

			length_npci = l;
			k=port_number;
			t=0;
			for(i=0; i<MAX_Routing_table; i++)
			{
			 if( i!=k && ( (Routing_table[i].status&PORT_ACTIVE)==PORT_ACTIVE) )
			 {
				 s=0;
				 if( Routing_table[i].Port.network!=Routing_table[k].Port.network )
				 {
					memcpy(&npci[length_npci], &Routing_table[i].Port.network, 2);
					length_npci += 2;
					npci[length_npci++]=0;
					s=1;
				 }
				 for(j=0; j<MAX_reachable_networks; j++)
					if( Routing_table[i].Port.networks_list[j].status == REACHABLE )
					{
					 if( Routing_table[i].Port.networks_list[j].network!=Routing_table[k].Port.network )
					 {
						memcpy(&npci[length_npci], &Routing_table[i].Port.networks_list[j].network, 2);
						length_npci += 2;
						npci[length_npci++]=0;
						s=1;
					 }
					}
				 if(s) t++;
			 }
			}
			cdata = (class ConnectionData *)Routing_table[k].ptr;
			m = cdata->panel_info1.network;
			memcpy( &npci[5], &m, 2);   //SNET
			npci[m1] = t;
			if(t)
			{
			 if(!(Routing_table[k].status^PTP_ACTIVE))
			 {  // do not send on ptp
//				((class PTP *)Routing_table[k].ptr)->sendframe(length_npci, npci);
					;
			 }
			 if( (Routing_table[k].status&RS485_ACTIVE)==RS485_ACTIVE )
			 {
			// build frame
				if( (nextentry = ((class MSTP *)Routing_table[k].ptr)->SendFramePool.NextFreeEntry()) >= 0 )
				{
				 pframe = &((class MSTP *)Routing_table[k].ptr)->SendFramePool.Frame[nextentry];
				 pframe->FrameType = BACnetDataNotExpectingReply;
				 pframe->Destination = 255;
				 pframe->Source = TS;
				 pframe->Length = length_npci;
				 memcpy(pframe->Buffer, npci, length_npci);
//				((class MSTP *)Routing_table[k].ptr)->SendFramePool.Unlockhead();
				 ((class MSTP *)Routing_table[k].ptr)->SendFramePool.status[nextentry]=1;
				}
			 }
			 if( (Routing_table[k].status&IPX_ACTIVE)==IPX_ACTIVE ||
					(Routing_table[k].status&TCPIP_ACTIVE)==TCPIP_ACTIVE   )
			 {
			// build frame
					pframe = (FRAME *)((class NET_BAC *)Routing_table[k].ptr)->SendFramePool.NextFreeEntry(0);
					if( pframe == NULL )
						return -1;
					pframe->FrameType = BACnetDataNotExpectingReply;
					pframe->Destination = 255;
					pframe->Source = Station_NUM;
					pframe->Length = length_npci;
					memcpy(pframe->Buffer, npci, length_npci);
					((class NET_BAC *)Routing_table[k].ptr)->SendFramePool.Unlock_frame(
																									 (SEND_FRAME_ENTRY*)pframe );
					resume( ((class NET_BAC *)Routing_table[k].ptr)->task_number );
			 }
			}

		k=port_number;
		length_npci = l;
		memcpy(&npci[length_npci], &Routing_table[k].Port.network, 2);
		length_npci += 2;
		npci[length_npci++]=0;
		t=1;
		for(j=0; j<MAX_reachable_networks; j++)
			if( Routing_table[k].Port.networks_list[j].status == REACHABLE )
			{
				for(i=0; i<MAX_Routing_table; i++)
				{
				 if(i!=k && Routing_table[k].Port.networks_list[j].network==Routing_table[i].Port.network) break;
				}
				if(i>=MAX_Routing_table)
				{
				 memcpy(&npci[length_npci], &Routing_table[k].Port.networks_list[j].network, 2);
				 length_npci += 2;
				 npci[length_npci++]=0;
				 t++;
        }
			}
		npci[m1] = t;

		for(i=0; i<MAX_Routing_table; i++)
		{
		 if( i!=k && ( (Routing_table[i].status&PORT_ACTIVE)==PORT_ACTIVE) )
		 {
			cdata = (class ConnectionData *)Routing_table[i].ptr;
			m = cdata->panel_info1.network;
			memcpy( &npci[5], &m, 2);   //SNET
			if(!(Routing_table[i].status^PTP_ACTIVE))
			{
				((class PTP *)Routing_table[i].ptr)->sendframe(length_npci, npci);
			}
			if( (Routing_table[i].status&RS485_ACTIVE)==RS485_ACTIVE )
			{
			// build frame
				if( (nextentry = ((class MSTP *)Routing_table[i].ptr)->SendFramePool.NextFreeEntry()) >= 0 )
				{
				 pframe = &((class MSTP *)Routing_table[i].ptr)->SendFramePool.Frame[nextentry];
				 pframe->FrameType = BACnetDataNotExpectingReply;
				 pframe->Destination = 255;
				 pframe->Source = TS;
				 pframe->Length = length_npci;
				 memcpy(pframe->Buffer, npci, length_npci);
//				((class MSTP *)Routing_table[k].ptr)->SendFramePool.Unlockhead();
				 ((class MSTP *)Routing_table[i].ptr)->SendFramePool.status[nextentry]=1;
				}
			}
			 if( (Routing_table[i].status&IPX_ACTIVE)==IPX_ACTIVE ||
					(Routing_table[i].status&TCPIP_ACTIVE)==TCPIP_ACTIVE   )
			 {
			// build frame
					pframe = (FRAME *)((class NET_BAC *)Routing_table[i].ptr)->SendFramePool.NextFreeEntry(0);
					if( pframe == NULL )
						return -1;
					pframe->FrameType = BACnetDataNotExpectingReply;
					pframe->Destination = 255;
					pframe->Source = Station_NUM;
					pframe->Length = length_npci;
					memcpy(pframe->Buffer, npci, length_npci);
					((class NET_BAC *)Routing_table[i].ptr)->SendFramePool.Unlock_frame(
																									 (SEND_FRAME_ENTRY*)pframe );
					resume( ((class NET_BAC *)Routing_table[i].ptr)->task_number );
			 }
		 }
		}
//////
	 }
	 else
	 {
		m1 = l++;
		for(k=0; k<MAX_Routing_table; k++)
		{
		 length_npci = l;
		 if( (Routing_table[k].status&PORT_ACTIVE)==PORT_ACTIVE )
		 {
			t=0;
			for(i=0; i<MAX_Routing_table; i++)
			{
			 if( i!=k && ( (Routing_table[i].status&PORT_ACTIVE)==PORT_ACTIVE) )
			 {
				 s=0;
				 if( Routing_table[i].Port.network!=Routing_table[k].Port.network )
				 {
					memcpy(&npci[length_npci], &Routing_table[i].Port.network, 2);
					length_npci += 2;
					npci[length_npci++]=0;
					s=1;
				 }
				 for(j=0; j<MAX_reachable_networks; j++)
					if( Routing_table[i].Port.networks_list[j].status == REACHABLE )
					{
					 if( Routing_table[i].Port.networks_list[j].network!=Routing_table[k].Port.network )
					 {
						memcpy(&npci[length_npci], &Routing_table[i].Port.networks_list[j].network, 2);
						length_npci += 2;
						npci[length_npci++]=0;
						s=1;
					 }
					}
				 if(s) t++;
			 }
			}
			cdata = (class ConnectionData *)Routing_table[k].ptr;
			m = cdata->panel_info1.network;
			memcpy( &npci[5], &m, 2);   //SNET
			npci[m1] = t;
			if(t)
			{
			 if(!(Routing_table[k].status^PTP_ACTIVE))
			 {  // do not send on serial port
//			((class PTP *)Routing_table[k].ptr)->sendframe(length_npci, npci);
				 ;
			 }
			 if( (Routing_table[k].status&RS485_ACTIVE)==RS485_ACTIVE )
			 {
			// build frame
				if( (nextentry = ((class MSTP *)Routing_table[k].ptr)->SendFramePool.NextFreeEntry()) >= 0 )
				{
				 pframe = &((class MSTP *)Routing_table[k].ptr)->SendFramePool.Frame[nextentry];
				 pframe->FrameType = BACnetDataNotExpectingReply;
				 pframe->Destination = 255;
				 pframe->Source = TS;
				 pframe->Length = length_npci;
				 memcpy(pframe->Buffer, npci, length_npci);
//				((class MSTP *)Routing_table[k].ptr)->SendFramePool.Unlockhead();
				 ((class MSTP *)Routing_table[k].ptr)->SendFramePool.status[nextentry]=1;
				}
			 }
			 if( (Routing_table[k].status&IPX_ACTIVE)==IPX_ACTIVE ||
					(Routing_table[k].status&TCPIP_ACTIVE)==TCPIP_ACTIVE   )
			 {
			// build frame
					pframe = (FRAME *)((class NET_BAC *)Routing_table[k].ptr)->SendFramePool.NextFreeEntry(0);
					if( pframe == NULL )
						return -1;
					pframe->FrameType = BACnetDataNotExpectingReply;
					pframe->Destination = 255;
					pframe->Source = Station_NUM;
					pframe->Length = length_npci;
					memcpy(pframe->Buffer, npci, length_npci);
					((class NET_BAC *)Routing_table[k].ptr)->SendFramePool.Unlock_frame(
																									 (SEND_FRAME_ENTRY*)pframe );
					resume( ((class NET_BAC *)Routing_table[k].ptr)->task_number );
			 }
			}
		 }
		}   // end for k
	 } // else -1
	}
 }
 else
 {
	if(service==DL_UNITDATAindication)
	{
	 if( command==Initialize_Routing_Table )
	 {
		 i = *((char *)r->data);
		 r->data++;
		 for(j = 0; j<i; j++)
		 {
			m = *((int *)r->data);
			r->data += 2;
			if(!(*(r->data)))
			{
				 for(k=0; k<MAX_reachable_networks; k++)
					if( Routing_table[port_number].Port.networks_list[k].status == REACHABLE )
					{
					 if( Routing_table[port_number].Port.networks_list[k].network==m )
					 {
						 memset( &Routing_table[port_number].Port.networks_list[k], 0, sizeof(struct reachable_networks));
					 }
					}
			}
      r->data++;
		 }
	 }
	 else
	 {
		if(port_number>=0)
		{
/*
		 if( (Routing_table[port_number].status&PTP_INSTALLED)==PTP_INSTALLED )
			sptr = (class PTP *)Routing_table[port_number].ptr;
		 else
			sptr = (class MSTP *)Routing_table[port_number].ptr;
*/
			cdata = (class ConnectionData *)Routing_table[port_number].ptr;
//		 l = comm_info[cdata->com_port].NetworkAddress;
			l = cdata->panel_info1.network;
		}
		else
		 l = NetworkAddress;
//		if(r->SNET!=l || ((Routing_table[port_number].status&PTP_ACTIVE)==PTP_ACTIVE))
		if( ((Routing_table[port_number].status&PTP_ACTIVE)==PTP_ACTIVE) )
		{
		 Routing_table[port_number].Port.network = r->SNET;
		 Routing_table[port_number].Port.address = r->SADR[0];
		}
//	  memset( Routing_table[port_number].Port.networks_list, 0, sizeof(Routing_table[port_number].Port.networks_list));
		for(l=0;l<MAX_reachable_networks;l++)
		 if(Routing_table[port_number].Port.networks_list[l].router_address == r->SADR[0])
		 {
			memset( &Routing_table[port_number].Port.networks_list[l], 0, sizeof(struct reachable_networks));
		 }
		remote_net = r->SNET;
		if( command==I_Am_Router_To_Network_Prop )
		 k = 4;
		else
		 k = 2;
		for(i=0; i<(r->len/k); i++)
		{
		 j = *((int *)r->data);
		 if( j!=r->SNET || Routing_table[port_number].Port.address!=r->SADR[0] )
		 {
			l=MAX_reachable_networks;
			if( (Routing_table[port_number].status&PTP_ACTIVE)!=PTP_ACTIVE )
			{
			 for(l=0;l<MAX_Routing_table;l++)
			 {
// if one port that has the same network number as 'j' (another network connection) and that port
// is active, the 'j' network will not connect properly to this network
				if( Routing_table[l].Port.network==j && ((Routing_table[l].status&PORT_ACTIVE)==PORT_ACTIVE) ) break;
			 }
			}
			if(l>=MAX_reachable_networks)
			{
			 for(l=0;l<MAX_reachable_networks;l++)
				if(Routing_table[port_number].Port.networks_list[l].network == j) break;
			 if(l>=MAX_reachable_networks)
			 {
				for(l=0;l<MAX_reachable_networks;l++)
				 if(!Routing_table[port_number].Port.networks_list[l].network) break;
				if(l<MAX_reachable_networks)
				{
				 Routing_table[port_number].Port.networks_list[l].status = REACHABLE;
				 Routing_table[port_number].Port.networks_list[l].network = j;
				 Routing_table[port_number].Port.networks_list[l].router_address = r->SADR[0];
				 if( command==I_Am_Router_To_Network_Prop )
				 {
					Routing_table[port_number].Port.networks_list[l].half_router_address = *((int *)(r->data+2));
				 }
				 else
					Routing_table[port_number].Port.networks_list[l].half_router_address = 0;
				}
			 }
			}
		 }
		 if( command==I_Am_Router_To_Network_Prop )
			r->data += 4;
		 else
			r->data += 2;
		}
	 }
	}
 }
}
}


//Send Info:
//     0x00  panel off
//     0x01  panel ON
//     0x02  time
//     0x04  ready for des (RS485)
//     0x08  system name, network number  (RS485)
//     0x10  I want to connect to net (IPX)
//     0x20  I am on net (IPX)

int nettask(void)
{
 class ConnectionData *cdata;
 int j,k,repeat=0,nextentry;
 int sendinfo_flag_tmp;
 unsigned int i;
 char ttime=600;
 Alarm_point *ptr;
 Panel_info1 *panel_info;
 unsigned long activepanels;
 unsigned char tbl_bank1[MAX_TBL_BANK];
 while(1)
 {
	while(1)
	{
/*
	 if(network_points_flag)
	 {
		 if(netpointsflag==2)
		 {
			 for(j=0; j<MAXNETWORKPOINTS; j++)
			 {
				if( network_points_list[j].info.point.point_type )
				{
				 get_point_info(&network_points_list[j].info,NULL,NULL,NULL,NULL,1, network_points_list[j].info.point.network);
				}
			 }
			 ttime = 1000;
			 netpointsflag=3;
			 continue;
		 }
	 }
*/
/*
	 if(network_points_flag)
	 {
		 if(netpointsflag==2)
		 {
				 if(wantpointsentry)
				 {
					for(j=0; j<MAXNETWORKPOINTS; j++)
					{
					 if( network_points_list[j].info.point.point_type )
					 {
						get_point_info(&network_points_list[j].info,NULL,NULL,NULL,NULL,1, network_points_list[j].info.point.network);
					 }
					}
					wantpointsentry = 2;
					if(rs485port!=-1)
					{
					 net_call(COMMAND_50, SEND_NETWORKPOINTS_COMMAND, 0, 0, 255, Routing_table[rs485port].Port.network, BACnetUnconfirmedRequestPDU,    //|NETCALL_NOTTIMEOUT,
											 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,rs485port);
					}
					if(ipxport!=-1)
					{
					 net_call(COMMAND_50, SEND_NETWORKPOINTS_COMMAND, 0, 0, 255, Routing_table[ipxport].Port.network, BACnetUnconfirmedRequestPDU,     //|NETCALL_NOTTIMEOUT,
											 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,ipxport);
					}
					memset(network_points_list, 0, sizeof(network_points_list));
				 }
				 wantpointsentry = 0;
				 netpointsflag=1;
		 }
		 if (netpointsflag==1)
		 {
				 if(rs485port!=-1)
				 {
					net_call(COMMAND_50, SEND_WANTPOINTS_COMMAND+(1<<8), 0, 0, 255, Routing_table[rs485port].Port.network, BACnetUnconfirmedRequestPDU,   //|NETCALL_NOTTIMEOUT,
											 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,rs485port);
					if(ipxport!=-1)
					{
					 net_call(COMMAND_50, SEND_WANTPOINTS_COMMAND, 0, 0, 255, Routing_table[ipxport].Port.network, BACnetUnconfirmedRequestPDU,           //|NETCALL_NOTTIMEOUT,
											 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,ipxport);
					}
				 }
				 else
				 {
					if(ipxport!=-1)
						net_call(COMMAND_50, SEND_WANTPOINTS_COMMAND+(1<<8), 0, 0, 255, Routing_table[ipxport].Port.network, BACnetUnconfirmedRequestPDU,    //|NETCALL_NOTTIMEOUT,
											 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,ipxport);
				 }
				 netpointsflag=0;
				 if(ttime==38)
				 {
					ttime = 34;
				 }
				 else
					ttime = 38;
		 }
	 }
	 else
*/
	 if(sendinfoflag)
	 {
		sendinfoflag = 0;
		for(k=0; k<MAX_Routing_table ; k++)
		{
/*
		 if( (Routing_table[k].status&RS485_ACTIVE) == RS485_ACTIVE )
		 {
			cdata = (class ConnectionData *)Routing_table[k].ptr;
			if(cdata->sendinfo_flag)
			{
				 sendinfo_flag_tmp = cdata->sendinfo_flag;
				 cdata->sendinfo_flag = 0;
				 i=2;
				 j=Station_NUM;

//           if first token then broadcast information about its: system name, etc
				 while( cdata->FirstToken < 2 )
				 {
					cdata->FirstToken++;
					if(!cdata->newpanelbehind)
					{
						net_call(COMMAND_50+100, 70+(ON<<8), (char *)&j, &i, 255, Routing_table[k].Port.network, BACnetUnconfirmedRequestPDU, //|NETCALL_NOTTIMEOUT,
											 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,k);
					}
					else
					{
						net_call(COMMAND_50+100, 70+((ON|0x08)<<8), (char *)&j, &i, 255, Routing_table[k].Port.network, BACnetUnconfirmedRequestPDU|NETCALL_NOTTIMEOUT,
									 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,k);
					}
					cdata->receivedtoken = 0;
					msleep(600);
					msleep(20);
					if(TS<cdata->OS)
					{
						 net_call(COMMAND_50+100, 70+(0x02<<8), (char *)&j, &i, 255, Routing_table[k].Port.network, BACnetUnconfirmedRequestPDU|NETCALL_NOTTIMEOUT,
							 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,k);
						 cdata->receivedtoken = 0;
						 msleep(600);
						 msleep(20);
					}
				 }

				 if( cdata->laststation_connected>=0 )
				 {
					if( cdata->FirstToken >= 2 )
					{
					 while( --(cdata->laststation_connected) >= 0 )
					 {
//-> Sep 05, 1997
						if(!cdata->newpanelbehind)
						{
							net_call(COMMAND_50+100, 70+(ON<<8), (char *)&j, &i, 255, Routing_table[k].Port.network, BACnetUnconfirmedRequestPDU|NETCALL_NOTTIMEOUT,
											 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,k);
						}
						else
						{
							net_call(COMMAND_50+100, 70+((ON|0x08)<<8), (char *)&j, &i, 255, Routing_table[k].Port.network, BACnetUnconfirmedRequestPDU|NETCALL_NOTTIMEOUT,
											 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,k);
						}
						cdata->receivedtoken = 0;
						msleep(600);
						msleep(20);
						if(TS<cdata->OS)
						{
						 net_call(COMMAND_50+100, 70+(0x02<<8), (char *)&j, &i, 255, Routing_table[k].Port.network, BACnetUnconfirmedRequestPDU|NETCALL_NOTTIMEOUT,
							 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,k);
						 cdata->receivedtoken = 0;
						 msleep(600);
						 msleep(20);
					  }
//<-
					 }
					}
					cdata->laststation_connected=-1;
					cdata->newpanelbehind=0;
					if(ready_for_descriptors&0x01)
					{
							action=1;
							if( tasks[MISCELLANEOUS].status == SUSPENDED )
								 resume(MISCELLANEOUS);
					}
				 }

				 if(ready_for_descriptors&0x02)
				 {
					net_call(COMMAND_50+100, 70+(0x04<<8), (char *)&j, &i, cdata->NS, Routing_table[k].Port.network, BACnetUnconfirmedRequestPDU|NETCALL_NOTTIMEOUT,
											 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,k);
					msleep(20);
					ready_for_descriptors &= 0xfc;   //first 2 biti set to 0
				 }

				 if( sendinfo_flag_tmp&SENDINFO_TIME )
				 {
					 net_call(COMMAND_50+100, 70+(0x02<<8), (char *)&j, &i, 255, Routing_table[k].Port.network, BACnetUnconfirmedRequestPDU|NETCALL_NOTTIMEOUT,
											 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,k);
					 msleep(20);
				 }

				 if( sendinfo_flag_tmp&SENDINFO_PANELOFF )
				 {
					j = cdata->nextpanelisoff;
					net_call(COMMAND_50+100, 70+(OFF<<8), (char *)&j, &i, 255, Routing_table[k].Port.network, BACnetUnconfirmedRequestPDU|NETCALL_NOTTIMEOUT,
											 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,k);
					j = Station_NUM;
					msleep(20);
				 }
			}
		 }
*/
		 if( (Routing_table[k].status&IPX_ACTIVE) == IPX_ACTIVE )
		 {
			cdata = (class ConnectionData *)Routing_table[k].ptr;
			if(cdata->sendinfo_flag)
			{
				 sendinfo_flag_tmp = cdata->sendinfo_flag;
				 cdata->sendinfo_flag = 0;
				 i=2;
				 j=Station_NUM;

//           if first token then broadcast information about its: system name, etc
				 while( cdata->FirstToken<2 && cdata->FirstToken>=0 )
				 {
					if( iamnewonnet )
					{
// send I want to connect to net
					 net_call(COMMAND_50+100, 70+(0x10<<8), (char *)&j, &i, 255, Routing_table[k].Port.network, BACnetUnconfirmedRequestPDU, //|NETCALL_SOURCE255,  //|NETCALL_NOTTIMEOUT
											 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,k);
					 delay(400);
					 net_call(COMMAND_50+100, 70+(0x10<<8), (char *)&j, &i, 255, Routing_table[k].Port.network, BACnetUnconfirmedRequestPDU, //|NETCALL_SOURCE255,  //|NETCALL_NOTTIMEOUT
											 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,k);
					 delay(4000);
					 iamnewonnet = 0;
					 if( !cdata->panelconnected )
					 {
// -> send first a command I am off
						net_call(COMMAND_50+100, 70+(OFF<<8), (char *)&j, &i, 255, Routing_table[k].Port.network, BACnetUnconfirmedRequestPDU,    //|NETCALL_NOTTIMEOUT,
											 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,k);
						delay(1000);
// <-
					 }
					}
					if( cdata->panelconnected ) break;
					cdata->FirstToken++;
					net_call(COMMAND_50+100, 70+(ON<<8), (char *)&j, &i, 255, Routing_table[k].Port.network, BACnetUnconfirmedRequestPDU, //|NETCALL_NOTTIMEOUT,
											 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,k);
					delay(1000);
				 }
				 if( cdata->panelconnected ) continue;

				 if( cdata->laststation_connected>=0 )
				 {
					if( cdata->FirstToken >= 2 )
					{
					 while( --(cdata->laststation_connected) >= 0 )
					 {
							net_call(COMMAND_50+100, 70+(ON<<8), (char *)&j, &i, 255, Routing_table[k].Port.network, BACnetUnconfirmedRequestPDU, //|NETCALL_NOTTIMEOUT,
											 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,k);
							delay(500);
					 }
					}
					cdata->laststation_connected=-1;
				 }

				 if( sendinfo_flag_tmp&SENDINFO_PANELOFF )
				 {
					j = cdata->nextpanelisoff;
					net_call(COMMAND_50+100, 70+(OFF<<8), (char *)&j, &i, 255, Routing_table[k].Port.network, BACnetUnconfirmedRequestPDU, //|NETCALL_NOTTIMEOUT,
											 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,k);
					j = Station_NUM;
					delay(100);
				 }
				 if( (sendinfo_flag_tmp&LASTSTCONNECTED) || (sendinfo_flag_tmp&FIRSTTOKEN) || (sendinfo_flag_tmp&SENDINFO_TIME) )
				 {
					for(i=0;i<(Station_NUM-1);i++)
					{
					 if(cdata->panel_info1.active_panels&(0x01<<i)) break;
					}
					if( i>=(Station_NUM-1) )
					{
						net_call(COMMAND_50+100, 70+(0x02<<8), (char *)&j, &i, 255, Routing_table[k].Port.network, BACnetUnconfirmedRequestPDU,  //|NETCALL_NOTTIMEOUT,
									 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,k);
						delay(100);
					}
				 }
				 if( sendinfo_flag_tmp&SENDINFO_IAMONNET )
				 {
					if(cdata->newpanelbehind)
					{
					 cdata->newpanelbehind = 0;
					 net_call(COMMAND_50+100, 70+(0x20<<8), (char *)&j, &i, 255, Routing_table[k].Port.network, BACnetUnconfirmedRequestPDU, //|NETCALL_SOURCE255, //|NETCALL_NOTTIMEOUT
											 TIMEOUT_NETCALL,NULL,NULL,NULL,0,0,k);
					 generatealarm("Panel number conflict on network!", 0, Station_NUM, GENERAL_ALARM, 1, 0, NULL, 0);
					}
				 }
			}
		 } // end if IPX
		}
		continue;
	 }
/*
// if a ethernet panel becomes accidentally off it is not signaled
	 if( pipx != NULL )
	 {
		if( pipx->port_state==IPX_ACTIVE )
		{
		 if( tasks[NETWORK1].delay_time < 0 )
		 {
			activepanels = ((class ConnectionData *)Routing_table[pipx->port_number].ptr)->panel_info1.active_panels;
			for(j=0;j<MAX_STATIONS;j++)
			 if( (j+1)!=Station_NUM && (activepanels&(1L<<j)) )
			 {
				i = sizeof(tbl_bank);
				if(net_call(COMMAND_50, TABLEPOINTS_COMMAND, (char *)tbl_bank1, &i, station_num, networkaddress);
			 }
			tasks[NETWORK1].delay_time = 2000;
		 }
		}
	 }
*/
	 break;
	}
/*	msleep(timepoints);*/
	msleep(ttime);
/*
	 if(!netpointsflag)
		 netpointsflag=2;
*/
//	suspend(NETTASK);
 }
}

int sendalarm(int arg, Alarm_point *ptr, Panel_info1 *panel_info, int t=0)
{
 unsigned int i;
 int ret=0;
			i = sizeof(Alarm_point);
			if(	ptr->where1==255 )
			{
				if( !ptr->where_state1 || t )
				{
					net_call(SEND_ALARM_COMMAND+100, arg, (char *)ptr, &i, 255, panel_info->network, BACnetUnconfirmedRequestPDU|NETCALL_NOTTIMEOUT);
					ptr->where_state1=1;
				}
			}
			else
			{
			 if( ptr->where1 && !t )
			 {
				if( arg || !ptr->where_state1 )
				 if( panel_info->active_panels&(1<<(ptr->where1-1)) )
				 {
					if( net_call(SEND_ALARM_COMMAND+100, arg, (char *)ptr, &i, ptr->where1, panel_info->network, NETCALL_NOTTIMEOUT)==SUCCESS )
					 ptr->where_state1=1;
					else
					 ret=1;
				 }
				 else
					 ret=1;
				i = sizeof(Alarm_point);
				if( ptr->where2 )
				 if( arg || !ptr->where_state2 )
					if( panel_info->active_panels&(1<<(ptr->where2-1)) )
					{
					 if( net_call(SEND_ALARM_COMMAND+100, arg, (char *)ptr, &i, ptr->where2, panel_info->network, NETCALL_NOTTIMEOUT)==SUCCESS )
						 ptr->where_state2=1;
					 else
						ret=1;
					}
					else
					 ret=1;
				i = sizeof(Alarm_point);
				if( ptr->where3 )
				 if( arg || !ptr->where_state3 )
					if( panel_info->active_panels&(1<<(ptr->where3-1)) )
					{
					 if( net_call(SEND_ALARM_COMMAND+100, arg, (char *)ptr, &i, ptr->where3, panel_info->network, NETCALL_NOTTIMEOUT)==SUCCESS )
						 ptr->where_state3=1;
					 else
						ret=1;
					}
					else
					 ret=1;
				i = sizeof(Alarm_point);
				if( ptr->where4 )
				 if( arg || !ptr->where_state4 )
					if( panel_info->active_panels&(1<<(ptr->where4-1)) )
					{
					 if( net_call(SEND_ALARM_COMMAND+100, arg, (char *)ptr, &i, ptr->where4, panel_info->network, NETCALL_NOTTIMEOUT)==SUCCESS )
						 ptr->where_state4=1;
					 else
						ret=1;
					}
					else
					 ret=1;
				i = sizeof(Alarm_point);
				if( ptr->where5 )
				 if( arg || !ptr->where_state5 )
					if( panel_info->active_panels&(1<<(ptr->where5-1)) )
					{
					 if( net_call(SEND_ALARM_COMMAND+100, arg, (char *)ptr, &i, ptr->where5, panel_info->network, NETCALL_NOTTIMEOUT)==SUCCESS )
						 ptr->where_state5=1;
					 else
						ret=1;
					}
					else
					 ret=1;
			 }
			}
 return ret;
 }


int alarmtask(void)
{
 int j,ret, ret1, retry;
 unsigned int i;
 char alf;
 Alarm_point *ptr;
 Panel_info1 *panel_info;
 ret = 0;
 ret1 = 0;
 while(1)
 {
	alf = 0;
	while(1)
	{
	 if(ret1 || new_alarm_flag)
	 {
		alf |= new_alarm_flag;
		new_alarm_flag = 0;
    ret1 = 0;
		retry = 3;
 //		net_call(COMMAND_50, ALARM_NOTIFY_COMMAND, NULL, 0, 255, NetworkAddress, BACnetUnconfirmedRequestPDU|NETCALL_NOTTIMEOUT);
		for(j=0; j<MAX_Routing_table; j++)
		{
				if( (Routing_table[j].status&RS485_ACTIVE)==RS485_ACTIVE ||
						(Routing_table[j].status&IPX_ACTIVE)==IPX_ACTIVE     ||
						(Routing_table[j].status&TCPIP_ACTIVE)==TCPIP_ACTIVE   )
				{
					 panel_info = &(((class ConnectionData *)Routing_table[j].ptr)->panel_info1);
					 break;
				}
		}
		if( j>=MAX_Routing_table ) continue;

		while(retry)
		{
		 alf |= new_alarm_flag;
		 ret = 0;
		 ptr = ptr_panel->alarms;
		 for(j=0;j<MAX_ALARMS;ptr++,j++)
		 {
			if(	ptr->alarm_panel==Station_NUM )
			{
			 if( ptr->alarm )
			 {
/*			if( !ptr->restored && !ptr->acknowledged ) */
				{
				 if( alf == 0x04 )
				 {
						ret |= sendalarm(0, ptr, panel_info, 1);
				 }
				 else
					ret |= sendalarm(0, ptr, panel_info);
				}
			 }
			 else
			 {
				if( alf&0x02 )
				{
				 if( ptr->ddelete )
				 {
					 if( sendalarm(1, ptr, panel_info) )  //delete alarm
					 {        //error
						 ret |= 1;
					 }
					 else   //success
						 ptr->ddelete = 0;
				 }
				}
			 }
			}
			else
			{           // sent to the panel originated from
			 if( alf&0x02 || alf&0x01 )
			 {
				i = sizeof(Alarm_point);
				if( ptr->alarm )
				{
				 if( !ptr->original )
				 {
					if( net_call(SEND_ALARM_COMMAND+100, 0, (char *)ptr, &i, ptr->alarm_panel, panel_info->network, NETCALL_NOTTIMEOUT)==SUCCESS )
//				 net_call(SEND_ALARM_COMMAND+100, 0, (char *)ptr, &i, ptr->alarm_panel, panel_info->network, NETCALL_NOTTIMEOUT);
					{
					 ptr->original = 1;
					}
					else
					{
					 if( retry==1 )
					 {
							 net_call(SEND_ALARM_COMMAND+100, 0, (char *)ptr, &i, 255, panel_info->network, BACnetUnconfirmedRequestPDU|NETCALL_NOTTIMEOUT);
							 ptr->original = 1;
					 }
					 else
							 ret |= 1;
					}
				 }
				}
				else
				 if( alf&0x02 )
				 {
					if( ptr->ddelete )
					{
					 if( !ptr->original )
					 {
						if( net_call(SEND_ALARM_COMMAND+100, 1, (char *)ptr, &i, ptr->alarm_panel, panel_info->network, NETCALL_NOTTIMEOUT)==SUCCESS )
//						 net_call(SEND_ALARM_COMMAND+100, 1, (char *)ptr, &i, ptr->alarm_panel, panel_info->network, NETCALL_NOTTIMEOUT);
						{
						 ptr->original = 1;
						 ptr->ddelete = 0;
						}
						else
						{
						 if( retry==1 )
						 {       //broadcast
							 net_call(SEND_ALARM_COMMAND+100, 1, (char *)ptr, &i, 255, panel_info->network, BACnetUnconfirmedRequestPDU|NETCALL_NOTTIMEOUT);
							 ptr->original = 1;
							 ptr->ddelete = 0;
						 }
						 else
							ret |= 1;
						}
					 }
					}
				 }
			 }
			}
		 }
		 if (ret)
		 {
			retry--;
			msleep(40);
		 }
		 else
			break;
		}  // end while retry
		continue;
	 }
	 break;
	}
	if(ret)
	{
		msleep(1200);       //1 min
		ret1=1;
	}
	else
	{
//		suspend(ALARMTASK);
		msleep(5000);       //4.5 min
		ret1=1;
		new_alarm_flag |= 0x04;
	}
 }
}


//  input:  t=1  check all posible networks
//          t=0  check only direct connected networks

//  ret: -1 network number  not found
//       >=0 and j=-1  direct connected network
//       >=0 and j>=0  reachable network
//
int findroutingentry(int port, int network, int &j, int t=1)
{
		int i;
		j=-1;
		for(i=0; i<MAX_Routing_table; i++)
		{
		 if( (Routing_table[i].status&PORT_ACTIVE)==PORT_ACTIVE )
			if( Routing_table[i].Port.network==network )
			{
				 break;
			}
			else
			{
				for(j=0; j<MAX_reachable_networks; j++)
				 if( (t && ((Routing_table[i].Port.networks_list[j].status&REACHABLE) == REACHABLE)) &&
						Routing_table[i].Port.networks_list[j].network==network)
				 {
//					 destination=Routing_table[i].Port.networks_list[j].router_address;
					 break;
				 }
				if(j<MAX_reachable_networks) break;
				j = -1;
			}
		}
		if (i<MAX_Routing_table)
		{
			return i;
		}
		else
			return -1;
}

// ret: 1 direct connected network
//      0 reachable network
int localnetwork(int net)
{
	 int i,j;
	 i=findroutingentry(0, net, j);
	 if(i!=-1)
	 {
		if( (Routing_table[i].status&PTP_ACTIVE)==PTP_ACTIVE)
		{
			return 0;
		}
	 }
	 if(j!=-1) return 0;
/*
			for(int j=0; j<MAX_Routing_table ; j++)
			{
				if( ((Routing_table[j].status&RS485_ACTIVE)==RS485_ACTIVE) || ((Routing_table[j].status&IPX_ACTIVE)==IPX_ACTIVE))
				{
					if ( Routing_table[j].Port.network == net ) return 1;
				}
			}
			return 0;
*/
	 return 1;
}

int checkpointpresence(int num_point,int point_type,int num_panel,int num_net,int panel,int network)
{
 unsigned long activepanels;
 int i,j;

 i=findroutingentry(0, num_net, j);
 if(i>=0)
 {
	 if( (Routing_table[i].status&PTP_ACTIVE)==PTP_ACTIVE)
	 {
			return 1;
	 }
	 else
	 {
		 if(j==-1)
		 {  // direct connected
			activepanels = ((class ConnectionData *)Routing_table[i].ptr)->panel_info1.active_panels;
			num_panel--;
			if( activepanels&(1L<<num_panel) )
			 return 1;
			else
			 return 0;
		 }
		 else
			 return 1;
	 }
 }
 if( rs485port==-1 && ipxport==-1 )
 {
	 if( num_net==NetworkAddress && num_panel==	Station_NUM )
			 return 1;
 }
 return 0;
}

int checkmaxpoints(int num_point,int point_type,int num_panel,int num_net)
{
 unsigned char tbl_bank1[MAX_TBL_BANK];
 unsigned long activepanels;
 int i,j,t;
 t=0;
 i=findroutingentry(0, num_net, j);
 if(i>=0)
 {
	 if( (Routing_table[i].status&PTP_ACTIVE)==PTP_ACTIVE)
	 {
			t=1;
	 }
	 else
	 {
		 if(j==-1)
		 {  // direct connected
			return ( ((class ConnectionData *)Routing_table[i].ptr)->station_list[num_panel-1].tbl_bank[point_type]);
		 }
		 else
			t=1;
	 }
 }
 if(t)
 {
	t=sizeof(ptr_panel->table_bank);
	if( net_call(COMMAND_50, TABLEPOINTS_COMMAND, (char *)tbl_bank1, (unsigned int *)&t, num_panel, num_net,NETCALL_RETRY)==SUCCESS)
	{
	 return tbl_bank1[point_type];
	}
 }
 else
 {
	if( rs485port==-1 && ipxport==-1 )
	{
	 if( num_net==NetworkAddress && num_panel==	Station_NUM )
			 return ptr_panel->table_bank[point_type];
  }
 }
 return 0;
}

int local_request(int panel)
{
 if( (!local_panel && panel==Station_NUM && panel!=station_num ) || (local_panel && panel==Station_NUM) )
	return 1;
 else
	return 0;
}

int local_request(int panel, int network)
{
 if( panel==Station_NUM && localnetwork(network) )
	return 1;
 else
	return 0;
}

int ptpnetwork(int net)
{
	 int i,j;
	 i=findroutingentry(0, net, j);
	 if(i!=-1)
	 {
		if( (Routing_table[i].status&PTP_ACTIVE)==PTP_ACTIVE)
		{
			return 1;
		}
	 }
   return 0;
}

/*
int belongtowhichnet(int num_panel, int num_net, int network)
{

}
*/
