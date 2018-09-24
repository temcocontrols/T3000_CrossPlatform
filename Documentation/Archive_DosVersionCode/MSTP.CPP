#define RS485

#include <mem.h>
#include <windows.h>
#include <graphics.h>
#include "aio.h"
#include "mtkernel.h"
#include "serial.h"
#include "rs485.h"
#include "gwin.h"       
#include "giflzw.hpp"
#include "ptp.h"
#include "net_bac.h"

//#define RS485_LINK    0
#define ON   1
#define OFF  0
#define CTRLBREAK			      -1

/*
int rr1, rr2;
char rrr_buf[20];
*/
int Max_frame_minirouter=270;

//char tttt, tt=1, ttt, zzzz, yy[10];
//int xdest, xsource;
extern byte serial_access;
extern byte serial_panel_type;
extern char control;
extern char new_alarm_flag;
extern int maxelem_grouppool;
extern int curelem_grouppool;
extern char huge *lin_text;
extern int NetworkAddress;
extern char far NetworkName[NAME_SIZE];
extern char table_crc8[256];

extern Panel_info1 Panel_Info1;
extern char Station_NAME[NAME_SIZE];
extern int  Station_NUM;
extern Station_point station_list[32];
extern int  station_num;
extern Comm_Info *comm_info;

extern int ipxport, rs485port;
extern int Version;
extern char gAlarm;
extern char network_points_flag;
extern int MAX_HEAP_BUF;
extern int programs_size;
extern char save_monitor_status;
extern char action;
extern int mode_text;
extern Panel  *ptr_panel;
extern int RS485_EXIT;
extern int  Station_NUM;
extern unsigned long timestart;    // sec de la inceputul programului
extern Time_block ora_current;
//extern long time_slave[2];
//extern char tx_running[3];
extern unsigned long starttime;
extern long microsec;
extern char huge *ctrlbreak_text;
extern long data_const, data_length_const;
//extern char showsign;
extern char readmon_flag, savemon_flag, update_prg_flag, readfiles_flag;
extern struct TSMTable *STSMtable_ptr, *STSMtable_ptr_readmon, *STSMtable_ptr_files;
extern int STSMtable_ptr_port, STSMtable_ptr_readmon_port, STSMtable_ptr_files_port;
extern char sendinfoflag;
extern int setunreachabil;
extern int tswitch;      		// task index

extern int net_call(int command, int arg,  char *data, uint *length , int dest,
				 int network, int others=0, int timeout=TIMEOUT_NETCALL,
				 char *returnargs=NULL, int *length_returnargs=NULL,
				 char *sendargs=NULL, int length_sendargs=0, char bytearg=0, int port=-1);
void updatetimevars(void);
extern int writepropertystate(BACnetObjectIdentifier obj, long lvalue, int t=0);
extern int writepropertyvalue(BACnetObjectIdentifier obj, long lvalue);
extern int writepropertyauto(BACnetObjectIdentifier obj, int auto_manual);
extern void communication_sign(long done, long total);
extern uint search_point( Point &point, char *buff, char * & point_adr,
																		uint & point_length, Search_type order );
//extern int	get_point_info(Point_info *point_info, char **des=NULL, char **label=NULL, char **ontext=NULL, char **offtext=NULL, char pri=0, int network = 0xFFFF);
extern int get_point_info1(Point_info *point_info);

void SendFrame(FRAME *frame);
int networklayer( int service, int priority, int network, int destination, int source,
						char *asdu_npdu, int length_asdu_npdu, char *apci, int length_apci,
						int data_expecting_reply=BACnetDataNotExpectingReply, int clientserver=CLIENT, int port = -1);
int checkTSMtimeout(int update);
unsigned char CalcHeaderCRC(unsigned char dataValue, unsigned char crcValue);
unsigned int CalcDataCRC(unsigned char dataValue, unsigned int crcValue);
int compressdata(char *dest, int length_dest, char *source, int length_source, int *l);
int uncompress(char *dest, int length_dest, char *source, int length_source);
int encodetag(char cl, char t, char *tag, unsigned length);

// list used by router to store the request for a diferrent network
Point_Net             _far request_router_points_list[MAXREMOTEPOINTS82];
NETWORK_POINTS      	_far response_router_points_list[MAXNETWORKPOINTS];

extern NETWORK_POINTS	_far network_points_list[MAXNETWORKPOINTS];
//WANT_POINTS		   want_points_list[MAXREMOTEPOINTS];
extern REMOTE_POINTS  _far remote_points_list[MAXREMOTEPOINTS82];
extern int remote_list_last_index_mstp, remote_list_last_index_ipx;
extern char int_disk, int_disk1;

char NotResponse,NotResponse1=1;
char iamnewonnet, iwanttodisconnect;
char netpointsflag=1;
signed char wantpointsentry, wantpointsentry_router;
signed char np_ipx_networkpoints_type, np_rs485_networkpoints_type;
signed char wp_ipx_networkpoints_type, wp_rs485_networkpoints_type;
int timepoints=400;
char _far sendtime, sendtime_ipx;
int maxFrame;
//char writeretry_flag;
//MSTP *mstpport1;

//           if time want points
// used for ethernet port
int sendpoints(char *asdu, char type, int port, int net) //0 want_points, 1 network_points
{
	class ConnectionData *cdata;
	class Point_Net point;
	int  i,j,k,l,length_apci,np;
	REMOTE_POINTS *premote_points_list;

	cdata = (class ConnectionData *)Routing_table[port].ptr;
//	asdu += MAXAPCI;
	i=0;
	np=0;
	if(type==SEND_WANTPOINTS_COMMAND)
	{
	 k=0;
	 if( rs485port==-1 ) wp_ipx_networkpoints_type=0; // only ethernet installed
	 premote_points_list = &remote_points_list[remote_list_last_index_ipx];
	 for(j=remote_list_last_index_ipx; j<MAXREMOTEPOINTS82; j++, premote_points_list++)
	 {
		if( !wp_ipx_networkpoints_type)
		{
		 if( premote_points_list->info.point.point_type )
		 {
			if( rs485port!=-1 )
			{
				if(premote_points_list->info.point.network==cdata->panel_info1.network )
				{
				 memcpy(&asdu[k+2], &premote_points_list->info.point, sizeof(point));
				 k += sizeof(point);
				 np++;
				 if( np >= MAXREMOTEPOINTS82_FRAME)
				 {
					remote_list_last_index_ipx = j+1;
					break;
				 }
				}
			}
			else
			{
			 memcpy(&asdu[k+2], &premote_points_list->info.point, sizeof(point));
			 if( premote_points_list->info.point.network==0xFFFF )
			 {
				memcpy(&((class Point_Net*)&asdu[k+2])->network,&cdata->panel_info1.network,2);
			 }
			 k += sizeof(point);
			 np++;
			 if( np >= MAXREMOTEPOINTS82_FRAME)
			 {
					remote_list_last_index_ipx = j+1;
					break;
			 }
			}
		 }
		}
		else
		{
		 if( request_router_points_list[j].point_type )
		 {
			if(request_router_points_list[j].network==cdata->panel_info1.network )
			{
			 memcpy(&asdu[k+2], &request_router_points_list[j], sizeof(point));
			 k += sizeof(point);

			 if( --wantpointsentry_router < 0 ) wantpointsentry_router=0;
			 memset(&request_router_points_list[j], 0, sizeof(Point_Net));
			 np++;
			 if( np >= MAXREMOTEPOINTS82_FRAME)
			 {
					remote_list_last_index_ipx = j+1;
					break;
			 }

			}
		 }
		}
	 }
	 if( j >= MAXREMOTEPOINTS82)
	 {
		remote_list_last_index_ipx = 0;
	 }
	 if(++wp_ipx_networkpoints_type>=2) wp_ipx_networkpoints_type=0;
	 memcpy(&asdu[0], &k, 2);
	 i = k+2;
	}
	else
	{
	 memcpy(&asdu[0], &cdata->panel_info1.network, 2);
	 asdu[2] = TS;
	 k=0;
	 np=0;
	 if( rs485port==-1 ) np_ipx_networkpoints_type=0; // only ethernet installed
	 for(j=0; j<MAXNETWORKPOINTS; j++)
	 {
		if( !np_ipx_networkpoints_type)
		{
		if( network_points_list[j].info.point.point_type )
		{
		 if(network_points_list[j].info.point.network==cdata->panel_info1.network )
		 {
			if( get_point_info1(&network_points_list[j].info)==SUCCESS )
			{
			 memcpy(&asdu[k+5], &network_points_list[j], sizeof(NETWORK_POINTS));
			 k += sizeof(NETWORK_POINTS);
			 np++;
			}
			if( --wantpointsentry < 0 ) wantpointsentry=0;
			memset(&network_points_list[j], 0, sizeof(NETWORK_POINTS));
			if( np >= MAXNETWORKPOINTS) break;
		 }
		}
		}
		else
		{
		if( response_router_points_list[j].info.point.point_type )
		{
		 if( response_router_points_list[j].info.point.network!=cdata->panel_info1.network )
		 {
			 memcpy(&asdu[k+5], &response_router_points_list[j], sizeof(NETWORK_POINTS));
			 k += sizeof(NETWORK_POINTS);
			 memset(&response_router_points_list[j], 0, sizeof(NETWORK_POINTS));
			 np++;
			 if( np >= MAXNETWORKPOINTS) break;
		 }
		}
		}
	 }
	 if(++np_ipx_networkpoints_type>=2) np_ipx_networkpoints_type=0;
	 memcpy(&asdu[3], &k, 2);
	 i = k+5;
	}

	if(k)
	{
//	 if(type==SEND_NETWORKPOINTS_COMMAND)
//		 memset(network_points_list, 0, sizeof(network_points_list));
	 return i;
	}
	return 0;
}


//           if time want points
void MSTP::sendpoints(char *asdu, char type) //0 want_points, 1 network_points
{
// NETWORK_POINTS		*np;
 class Point_Net point;
// char apci[MAXAPCI];
 REMOTE_POINTS *premote_points_list;
 int  i,j,k,l,length_apci,np;
	asdu += MAXAPCI;
	i=0;

	if(!type)
	{
	 k=0;
	 np=0;
	 if( ipxport==-1 ) wp_rs485_networkpoints_type=0; // only rs485 installed
	 premote_points_list = &remote_points_list[remote_list_last_index_mstp];
	 for(j=remote_list_last_index_mstp; j<MAXREMOTEPOINTS82; j++, premote_points_list++)
	 {
//		if( !remote_points_list[j].info.point.zero() )
		if( !wp_rs485_networkpoints_type)
		{
		if( premote_points_list->info.point.point_type )
		{
		 if( ipxport!=-1 )
		 {
			if(premote_points_list->info.point.network==panel_info1.network ||
				 premote_points_list->info.point.network==0xFFFF )
			{
			 memcpy(&asdu[k+2], &premote_points_list->info.point, sizeof(point));
			 memcpy(&((class Point_Net*)&asdu[k+2])->network,&panel_info1.network,2);
			 k += sizeof(point);
			 np++;
			 if( np >= MAXREMOTEPOINTS82_FRAME)
			 {
				remote_list_last_index_mstp = j+1;
				break;
			 }
			}
		 }
		 else
		 {
			 memcpy(&asdu[k+2], &premote_points_list->info.point, sizeof(point));
			 if( premote_points_list->info.point.network==0xFFFF )
			 {
				 memcpy(&((class Point_Net*)&asdu[k+2])->network,&panel_info1.network,2);
			 }
			 k += sizeof(point);
			 np++;
			 if( np >= MAXREMOTEPOINTS82_FRAME)
			 {
				remote_list_last_index_mstp = j+1;
				break;
			 }
		 }
		}
		}
		else
		{
		if( request_router_points_list[j].point_type )
		{
			if(request_router_points_list[j].network==panel_info1.network )
			{
			 memcpy(&asdu[k+2], &request_router_points_list[j], sizeof(point));
			 k += sizeof(point);

			 if( --wantpointsentry_router < 0 ) wantpointsentry_router=0;
			 memset(&request_router_points_list[j], 0, sizeof(Point_Net));
			 np++;
			 if( np >= MAXREMOTEPOINTS82_FRAME)
			 {
				remote_list_last_index_mstp = j+1;
				break;
			 }
			}
		}
		}
	 }
	 if( j >= MAXREMOTEPOINTS82)
	 {
		remote_list_last_index_mstp = 0;
	 }
	 if(++wp_rs485_networkpoints_type>=2) wp_rs485_networkpoints_type=0;
	 memcpy(&asdu[0], &k, 2);
	 i = k+2;
	}
	else
	{
//----------------	 memcpy(&asdu[0], &NetworkAddress, 2);
	 memcpy(&asdu[0], &panel_info1.network, 2);
	 asdu[2] = TS;
	 k=0;
	 np=0;
//	 np = network_points_list;
	 if( ipxport==-1 ) np_rs485_networkpoints_type=0; // only rs485 installed
	 for(j=0; j<MAXNETWORKPOINTS; j++)
	 {
//		if( !network_points_list[j].info.point.zero() )
		if( !np_rs485_networkpoints_type)
		{
		if( network_points_list[j].info.point.point_type )
		{
//		 get_point_info(&network_points_list[j].info,NULL,NULL,NULL,NULL,1, network_points_list[j].info.point.network);
		 if( network_points_list[j].info.point.network==panel_info1.network )
		 {
			if( get_point_info1(&network_points_list[j].info)==SUCCESS )
			{
			 memmove(asdu+k+5, &network_points_list[j], sizeof(NETWORK_POINTS));
			 k += sizeof(NETWORK_POINTS);
			 np++;
			}
			if( --wantpointsentry < 0 ) wantpointsentry=0;
			memset(&network_points_list[j], 0, sizeof(NETWORK_POINTS));
			if( np >= MAXNETWORKPOINTS) break;
		 }
		}
		}
		else
		{
		// route the router network points list
		if( response_router_points_list[j].info.point.point_type )
		{
		 if( response_router_points_list[j].info.point.network!=panel_info1.network )
		 {
			 memmove(asdu+k+5, &response_router_points_list[j], sizeof(NETWORK_POINTS));
			 k += sizeof(NETWORK_POINTS);
			 memset(&response_router_points_list[j], 0, sizeof(NETWORK_POINTS));
			 np++;
			 if( np >= MAXNETWORKPOINTS) break;
		 }
		}
		}
	 }
	 if(++np_rs485_networkpoints_type>=2) np_rs485_networkpoints_type=0;
	 memcpy(&asdu[3], &k, 2);
	 i = k+5;
	}
	if(k)
	{
	asdu -= MAXAPCI;
	asdu[0] = (BACnetUnconfirmedRequestPDU<<4);
	asdu[1] = UnconfirmedPrivateTransfer;
	asdu[2]=0x09;           //tag
	asdu[3]=VendorID;
	asdu[4]=0x1A;           //tag
	asdu[5]=50;
	asdu[6]=72+type;
	i += 3;           // 3 bytes args
	length_apci = 7+encodetag(1, 2, &asdu[7], i);
	asdu[length_apci++]=0;                 			//extra low
	asdu[length_apci++]=0;             				//extra high
	asdu[length_apci++]=0;                  		//reserved

	memmove(&asdu[length_apci], &asdu[MAXAPCI], i);
//	memcpy(&asdu[length_apci], &asdu[MAXAPCI], i);
	i += length_apci-3;
	if( !replyflag )
	{
	 replyflag = 1;
//	networklayer( N_UNITDATArequest, NORMALmessage, NetworkAddress, 255, TS, asdu, i, apci, length_apci, BACnetDataNotExpectingReply, 0, port_number);
//------------	 networklayer( N_UNITDATArequest, NORMALmessage, NetworkAddress, 255, TS, asdu, i, asdu, 0, BACnetDataNotExpectingReply, 0, port_number);
	 networklayer( N_UNITDATArequest, NORMALmessage, panel_info1.network, 255, TS, asdu, i, asdu, 0, BACnetDataNotExpectingReply, 0, port_number);
	 if( replyflag==2 )
		 SendFrame((FRAME *)&ServerBuffer,1);
	 replyflag=0;
// wait 40ms * nr_char / 100 / 6.8 = 40 * nr_char * 10 / 100 / 68 = 4 * nr_char / 68
// 4.4ms per remote point for type=1
	 if(type)
	 {
		 j = ((1+k/sizeof(NETWORK_POINTS))*46/68)+1;
		 if( j<7 ) j = 7;
		 msleep( j );
	 }
	 else
	 {
// 1.5ms per remote point for type=0
		j = ((1+k/sizeof(point))*15/68)+1;
		if( j<7 ) j=7;
		msleep( j );
/*
		if(i>200)
		{
		 if(i>375)
			msleep(14);
		 else
			msleep(10);
		}
		else
			msleep(8);
*/
	 }
//	 delay(14);
	}
/*
	if(type)
	 memset(network_points_list, 0, sizeof(network_points_list));
*/
	}
}

MSTP_RECEIVEDFRAMEPOOL::MSTP_RECEIVEDFRAMEPOOL(void)
{
//  entry=0;
	memset(ReceivedFrame,0,sizeof(ReceivedFrame));
}

/*
int MSTP_RECEIVEDFRAMEPOOL::NextFreeEntry(int t)
{
 int i,j;
 asm push es;
 j = entry;
 for(i=0; i<MSTP_NMAXRECEIVEDFRAMEPOOL; i++)
 {
	disable();
	if( !ReceivedFrame[j].status )
	{
	  ReceivedFrame[j].status=2;
	  enable();
		break;
	}
	enable();
	if ( ++j >= MSTP_NMAXRECEIVEDFRAMEPOOL ) j=0;
 }
 asm pop es;
 if ( i >= MSTP_NMAXRECEIVEDFRAMEPOOL ) return -1;
 return j;
*/
/*
 unsigned char h,temp_head;
 asm push es;
  h = temp_head = HeadFrame;
 if( overflow ) return -1;
 if ( ++temp_head >= MSTP_NMAXRECEIVEDFRAMEPOOL )
	 temp_head = 0;
 lockedhead=1;
 if ( temp_head == TailFrame )
	 overflow=1;
 HeadFrame = temp_head;
 ReceivedFrame[h].ReceivedValidFrame=FALSE;
 ReceivedFrame[h].ReceivedInvalidFrame=FALSE;
 asm pop es;
 return h;
}
*/

void *MSTP_RECEIVEDFRAMEPOOL::NextFreeEntry( void )
{
// int nextentry;
 int i;
// int j;
 asm push es;
// j = entry;
 for(i=0; i<MSTP_NMAXRECEIVEDFRAMEPOOL; i++)
 {
	if( !ReceivedFrame[i].status )
	{
	  ReceivedFrame[i].status=2;
		break;
	}
//	if ( ++j >= MSTP_NMAXRECEIVEDFRAMEPOOL ) j=0;
 }
 asm pop es;
 if ( i >= MSTP_NMAXRECEIVEDFRAMEPOOL ) return 0;
 return (void *)&ReceivedFrame[i];
/*
 asm push es;
 if( (t = NextFreeEntry()) >=0 )
 {
	asm pop es;
	return (void *)&ReceivedFrame[t];
 }
 else
 {
	asm pop es;
	return 0;
 }
*/
}

int MSTP_RECEIVEDFRAMEPOOL::RemoveEntry(MSTP_ReceivedFrame *pframe)
{
 int i;
// int j;
 asm push es;
 pframe->ReceivedValidFrame = pframe->ReceivedInvalidFrame = FALSE;
// j = entry;
 for(i=0; i< MSTP_NMAXRECEIVEDFRAMEPOOL; i++)
 {
	if( ReceivedFrame[i].status==1 ) break;
//	if ( ++j >= MSTP_NMAXRECEIVEDFRAMEPOOL ) j=0;
 }
 asm pop es;
 if ( i >= MSTP_NMAXRECEIVEDFRAMEPOOL ) return -1;
 memcpy(pframe, &ReceivedFrame[i], sizeof(MSTP_ReceivedFrame));
// if ( ++entry >= MSTP_NMAXRECEIVEDFRAMEPOOL ) entry=0;
 ReceivedFrame[i].ReceivedValidFrame=0;
 ReceivedFrame[i].ReceivedInvalidFrame=0;
 ReceivedFrame[i].status=0;
 return 1;
}

/*
void SENDFRAMEPOOL::Unlockhead(void)
{
 asm push es; lockedhead=0; asm pop es;
}
*/

MSTP_SENDFRAMEPOOL::MSTP_SENDFRAMEPOOL(void)
{
	entry=access=0;
	memset(status,0,sizeof(status));
}

int SENDFRAMEPOOL::NextFreeEntry(void)
{
	int h,temp_head;
	int r,i;
	asm push es;
	if( access && lockedhead )
	{
	 asm pop es;
	 return -1;
	}
	access=1;
	h = temp_head = HeadFrame;
	if( overflow )
	{
	 h = -1;
	}
	else
	{
	 if ( ++temp_head >= PTP_NMAXSENDFRAMEPOOL )
		temp_head = 0;
	 lockedhead=1;
	 if ( temp_head == TailFrame )
		overflow=1;
	 HeadFrame = temp_head;
	}
	access=0;
	asm pop es;
	return h;
}


int MSTP_SENDFRAMEPOOL::NextFreeEntry(void)
{
 int i;
 int j;
 asm push es;
 if( access )
 {
	asm pop es;
	return -1;
 }
// Jan 98
// disable();
 access=1;
// Jan 98
// enable();

/*
 if(command)
 {
	for(i=0; i<MSTP_NMAXSENDFRAMEPOOL; i++)
	{
	 if( status[i] )
	 {
//		if(Frame[i].Buffer[8]==command)
		{
		 asm pop es;
		 access=0;
		 return -1;
		}
   }
	}
 }
*/
 j = entry;
 for(i=0; i<MSTP_NMAXSENDFRAMEPOOL; i++)
 {
	if( !status[j] )
	{
		status[j]=2;
		enable();
		break;
	}
	if ( ++j >= MSTP_NMAXSENDFRAMEPOOL ) j=0;
 }
 asm pop es;
 access=0;
 if ( i >= MSTP_NMAXSENDFRAMEPOOL ) return -1;
 return j;

}

int MSTP_SENDFRAMEPOOL::RemoveEntry(FRAME *frame)
{
 int i,j;
 asm push es;
 j = entry;
 for(i=0; i<MSTP_NMAXSENDFRAMEPOOL; i++)
 {
	if( status[j]==1 ) break;
	if ( ++j >= MSTP_NMAXSENDFRAMEPOOL ) j=0;
 }
 if ( i >= MSTP_NMAXSENDFRAMEPOOL )
 {
  asm pop es;
	return -1;
 }
 memcpy( frame, &Frame[j], sizeof(FRAME));
 entry=j;
 status[j]=0;
 asm pop es;
 return 1;
}

int MSTP_SENDFRAMEPOOL::Query(void)
{
 int ret=0;
 for(int i=0; i<MSTP_NMAXSENDFRAMEPOOL; i++)
 {
	if( status[i] ) ret++;
 }
 return ret;
}

int MSTP_SENDFRAMEPOOL::CheckEntry(int dest, int source)
{
 int ret=0;
 for(int i=0; i<MSTP_NMAXSENDFRAMEPOOL; i++)
 {
	if( status[i] )
	 if( Frame[i].Destination==dest && Frame[i].Source==source)
		ret++;
 }
 return ret;
}


void MSTP_SENDFRAMEPOOL::Empty(void)
{
	entry=access=0;
	memset(status,0,sizeof(status));
}

//extern int timecount;
//extern int Ncount,NNcount;

//int xxx,yyy,zzz, bbb;
//unsigned long qqq,aaa;

//
// status&0x01 - station ON: station_name
// status&0x02 - station ON: time syncronization
// status&0x04 - station ON: read descriptors
//

//void sendinfo(FRAME *frame, int status, int panel, int dest=255 )
int sendinfo(char *Buffer, int status, int panel, int dest, int port )
{
 class ConnectionData *cdata;
 int i=0, l;
 cdata = (class ConnectionData *)Routing_table[port].ptr;

		Buffer[i++]=0x2D;               			//Octet String, L>4
		Buffer[i] = 3+2;     // panel_num
		if( status&0x01 )
			Buffer[i] += sizeof(Station_NAME)+2;
		if( status&0x02 )
			Buffer[i] += sizeof(Time_block);  // time
		if( status&0x08 )
			Buffer[i] += 2+22+2+NAME_SIZE;  // panel_to_receive,system_name,network,network_name
		l = i;
		i++;
// parameters
		Buffer[i++]=status;                 				//extra low
		Buffer[i++]=0;             				//extra high
		Buffer[i++]=0;                  				//reserved
		memcpy( &Buffer[i], &panel, 2);
		i += 2;
		if( (status&0x01)==ON )
		{
			unsigned int l1;
			l1 = cdata->panel_info1.des_length;
			memcpy( &Buffer[i], Station_NAME, sizeof(Station_NAME));
			i += sizeof(Station_NAME);
			memcpy( &Buffer[i], &l1, 2);
			i += 2;
			Buffer[i++] = cdata->panel_info1.panel_type;
			memcpy( &Buffer[i], (char*)&cdata->panel_info1.version, 2);
			i += 2;
			memcpy( &Buffer[i], (char*)&ptr_panel->table_bank, sizeof(ptr_panel->table_bank));
			i += sizeof(ptr_panel->table_bank);
			Buffer[l] += 1+2+sizeof(ptr_panel->table_bank);
		}
		if( status&0x02 )
		{
			memcpy( &Buffer[i], (char*)&ora_current, sizeof(Time_block));
			i += sizeof(struct tm);
		}
		if( status&0x08 )
		{
//  Aug 29, 1997  ->
			l = cdata->OS;
			memcpy( &Buffer[i], &l, 2);
			i += 2;
			memcpy( &Buffer[i], (char*)ptr_panel->system_name, 22);
			i += 22;
			memcpy( &Buffer[i], (char*)&cdata->panel_info1.network, 2);
			i += 2;
			memcpy( &Buffer[i], (char*)cdata->panel_info1.network_name, NAME_SIZE);
			i += NAME_SIZE;
//  Aug 29, 1997  <-
		}
		return i;
}

int sendinfo(FRAME *frame, int status, int panel, int port )
{
 class ConnectionData *cdata;
 char *Buffer;
 int i=0, l;
 cdata = (class ConnectionData *)Routing_table[port].ptr;

		frame->FrameType = BACnetDataNotExpectingReply;
		frame->Destination = 255;
		frame->Source = TS;
		Buffer = frame->Buffer;
// npci
		Buffer[i++]=0x01;      // npci  version BACnet
		Buffer[i++]=0x00;      // npci  local network
// apci
		Buffer[i++] = (BACnetUnconfirmedRequestPDU<<4);
		Buffer[i++] = UnconfirmedPrivateTransfer;
// asdu - service request
		Buffer[i++]=0x09;           //tag
		Buffer[i++]=VendorID;
		Buffer[i++]=0x1A;           //tag
		Buffer[i++]=50+100;
		Buffer[i++]=70;

		i += sendinfo(&Buffer[i], status, panel, 255, port );

		frame->Length = i;
		((class MSTP *)Routing_table[port].ptr)->SendFrame((FRAME*)frame);
		msleep(7);

		return i;
}

/*
//void sendinfo(FRAME *frame, int status, int panel, int dest=255 )
void MSTP::sendinfo(FRAME *frame, int status, int panel, int dest )
{
 int i=0, l;
		frame->FrameType = BACnetDataNotExpectingReply;
		frame->Destination = dest;
		frame->Source = TS;
// npci
		frame->Buffer[i++]=0x01;      // npci  version BACnet
		frame->Buffer[i++]=0x00;      // npci  local network
// apci
		frame->Buffer[i++] = (BACnetUnconfirmedRequestPDU<<4);
		frame->Buffer[i++] = UnconfirmedPrivateTransfer;
// asdu - service request
		frame->Buffer[i++]=0x09;           //tag
		frame->Buffer[i++]=VendorID;
		frame->Buffer[i++]=0x1A;           //tag
		frame->Buffer[i++]=50+100;
		frame->Buffer[i++]=70;
		frame->Buffer[i++]=0x2D;               			//Octet String, L>4
//	  if(status&0x10)
//		  frame->Buffer[i++]=3+2+sizeof(Station_NAME);  // L
//	  else
		{
		frame->Buffer[i] = 3+2;     // panel_num
//		if( (status&0x01)==ON )
		if( status&0x01 )
			frame->Buffer[i] += sizeof(Station_NAME)+2;
//		if( (status&0x02)==0x02 )
		if( status&0x02 )
			frame->Buffer[i] += sizeof(Time_block);  // time
//		if( (status&0x08)==0x08 )
		if( status&0x08 )
			frame->Buffer[i] += 2+22+2;  // panel_to_receive,system_name,network
		l = i;
		i++;
		}
// parameters
		frame->Buffer[i++]=status;                 				//extra low
		frame->Buffer[i++]=0;             				//extra high
		frame->Buffer[i++]=0;                  				//reserved
		memcpy( &frame->Buffer[i], &panel, 2);
		i += 2;
		if( (status&0x01)==ON )
		{
//		  Point point;
//		  unsigned int l = search_point( point, NULL, NULL, 0, LENGTH );
//		  station_list[Station_NUM-1].des_length = l;
			unsigned int l;
			l = panel_info1.des_length;
			memcpy( &frame->Buffer[i], Station_NAME, sizeof(Station_NAME));
			i += sizeof(Station_NAME);
			memcpy( &frame->Buffer[i], &l, 2);
			i += 2;
//  Aug 29, 1997  ->
//			if( station_list[NS-1].version )
//			{
//			 if( (panel_info1.panel_type == T3000 && panel_info1.version >= 216) ||	(panel_info1.panel_type == MINI_T3000 && panel_info1.version >= 110) )
//			 {
			frame->Buffer[i++] = panel_info1.panel_type;
			memcpy( &frame->Buffer[i], (char*)&panel_info1.version, 2);
			i += 2;
			memcpy( &frame->Buffer[i], (char*)&ptr_panel->table_bank, sizeof(ptr_panel->table_bank));
			i += sizeof(ptr_panel->table_bank);
			frame->Buffer[l] += 1+2+sizeof(ptr_panel->table_bank);
//			 }
//			}
//  Aug 29, 1997  <-
		}
		if( status&0x02 )
		{
			memcpy( &frame->Buffer[i], (char*)&ora_current, sizeof(Time_block));
			i += sizeof(struct tm);
		}
		if( status&0x08 )
		{
//  Aug 29, 1997  ->
			l = OS;
			memcpy( &frame->Buffer[i], &l, 2);
		  i += 2;
			memcpy( &frame->Buffer[i], (char*)ptr_panel->system_name, 22);
			i += 22;
			memcpy( &frame->Buffer[i], (char*)&panel_info1.network, 2);
			i += 2;
//  Aug 29, 1997  <-
		}

// end parameters
//	  frame->Buffer[i++]=0x2f;           				//closing tag
		frame->Length = i;

		delay(1);
		SendFrame(frame);
		msleep(8);
}
*/

MSTP::MSTP( int c_port, int n_port ):Serial( c_port, n_port )
{
	Point point;
//	memset(&need_info, 0, sizeof(need_info));
	need_info = (1l<<(Station_NUM-1));
	memset(&panel_info1, 0, sizeof(panel_info1));
	panel_info1.active_panels = 1l<<(Station_NUM-1);
	memset(station_list,0,sizeof(station_list));
	strcpy(station_list[Station_NUM-1].name,Station_NAME);
	station_list[Station_NUM-1].state = 1;
	station_list[Station_NUM-1].panel_type = Panel_Info1.panel_type;
	station_list[Station_NUM-1].version = Version;
	memcpy(station_list[Station_NUM-1].tbl_bank,ptr_panel->table_bank,sizeof(ptr_panel->table_bank));
	panel_info1.network = comm_info[c_port].NetworkAddress;
	memcpy(panel_info1.network_name,comm_info[c_port].NetworkName,NAME_SIZE);
	strcpy(panel_info1.panel_name,Station_NAME);
	panel_info1.des_length = search_point( point, NULL, NULL, 0, LENGTH );
	station_list[Station_NUM-1].des_length = panel_info1.des_length;
	panel_info1.panel_number = Station_NUM;
	panel_info1.version = Version;
	panel_info1.panel_type = Panel_Info1.panel_type;

	MSTP_ReceiveFrameStatus=RECEIVE_FRAME_IDLE;
//	MSTP_MASTERState=MSTP_MASTER_IDLE;
	MSTP_Master_initialize();
	ServerTSM_flag=-1;
	port_number = n_port;
	Install_port();
//	ptr_ser_pool = &ser_pool;
//   ptr_h =  (Header_pool *)ser_pool.buf;
//	ser_p = this;
}

void MSTP::MSTP_Master_initialize(void)
{
 TS = Station_NUM;  //node address
 NS = TS;
 PS = TS;
 OS = TS;
 TokenCount = NPoll;
 SoleMaster = FALSE;
// ReceivedValidFrame = ReceivedInvalidFrame = FALSE;
// MSTP_MASTERState = MSTP_MASTER_IDLE;
// SilenceTimer=0;
 FirstToken=0;
 timepoints=400;
 wantpointsentry = 0;
 memset(network_points_list, 0, sizeof(network_points_list));
 wantpointsentry_router = 0;
 memset(request_router_points_list, 0, sizeof(request_router_points_list));
 memset(response_router_points_list, 0, sizeof(response_router_points_list));
 wp_rs485_networkpoints_type = 0;
 np_rs485_networkpoints_type = 0;
 }

int MSTP::MSTP_Master_node( MSTP *mstp )
{
/* if two RS485 ports installed, no variables on stack
	 are allowed */
 int mcr;
 struct isr_data_block *isr_data;
 Settings *settings;
 FRAME frame;
 char TimeOut, resetport;
 int n,dayofyear, countr, reply_delay;
 struct MSTP_ReceivedFrame recframe;
 PORT_STATUS_variables *ps;
 ps = &Routing_table[mstp->port_number].port_status_vars;
 ps->HeartbeatTimer=0;
 if( mstp->port_status == NOT_INSTALLED )
	suspend(MSTP_MASTER);
 else
 {
	 ps->validint = 1;
	 network_points_flag++;
 }
 netpointsflag=0;
 mstp->panelconnected = 0;
 mstp->panelOff = 0;
 mstp->receivedpollformaster = 0;
 mstp->newpanelbehind = 0;
 mstp->laststation_connected = -1;
 mstp->receivedtoken = 0;
 dayofyear=ora_current.dayofyear;
 countr = 10;
 resetport = 700;
 while( 1 )
 {
	 TS = Station_NUM;  //node address
	 switch ( ps->MSTP_MASTERState ){
		 case MSTP_MASTER_IDLE:
// 		LostToken
			if( ps->SilenceTimer*TIMERESOLUTION >= TNO_TOKEN || !resetport)
			{
				if(!resetport)
				{
					resetport = 700;
					countr=1;
				}
				if(mstp->FirstToken)
				{
// Taiwan 11/08/97
// MSTP locked. Put enable() to unlock the interrupt
// TBD
				 mstp->FirstToken = 0;
				 mstp->newpanelbehind = 0;
//				 memset(&mstp->need_info, 0, sizeof(mstp->need_info));
				 mstp->need_info = (1l<<(TS-1));
				 mstp->panel_info1.active_panels = 1l<<(TS-1);
				 memset(mstp->station_list,0,sizeof(mstp->station_list));
				 strcpy(mstp->station_list[Station_NUM-1].name,Station_NAME);
				 mstp->station_list[TS-1].state = 1;
				 mstp->station_list[TS-1].des_length = mstp->panel_info1.des_length;
				 mstp->station_list[TS-1].panel_type = mstp->panel_info1.panel_type;
				 mstp->station_list[TS-1].version = Version;
				 memcpy(mstp->station_list[TS-1].tbl_bank,ptr_panel->table_bank,sizeof(ptr_panel->table_bank));
				 mstp->NS = TS;
				 mstp->PS = TS;
				 mstp->OS = TS;
				 mstp->SoleMaster = FALSE;
				}

				countr--;
				if( !countr )
				{
				 countr = 3;
				 if( ((class MSTP *)Routing_table[mstp->port_number].ptr)->port )
				 {
					disable();
					((class MSTP *)Routing_table[mstp->port_number].ptr)->port->discon();
					((class MSTP *)Routing_table[mstp->port_number].ptr)->port->setpc8250(
					 0,
					 comm_info[((class MSTP *)Routing_table[mstp->port_number].ptr)->com_port].port_name,
					 comm_info[((class MSTP *)Routing_table[mstp->port_number].ptr)->com_port].baudrate,
					 'N', 8, 1, dtr, 1, DISABLE, DISABLE, DISABLE,
					 0, 0, comm_info[((class MSTP *)Routing_table[mstp->port_number].ptr)->com_port].int_name
					 );
					enable();
				 }
				}

				ps->validint = 1;
				if(mstp->panelOff)
				{
				 ps->SilenceTimer = 0;
				}
				ps->MSTP_MASTERState = MSTP_MASTER_NO_TOKEN;
				break;
			}
			countr = 1;
			if(mstp->ReceivedFramePool.RemoveEntry(&recframe)>=0)
			{
//       ps->HeartbeatTimer=0;
			 if(mstp->panelOff) break;
//        ReceivedInvalidFrame
			 if( recframe.ReceivedInvalidFrame == TRUE )
			 {
//				ReceivedInvalidFrame = FALSE;
				ps->validint = 1;
				break;
			 }
			 if( recframe.ReceivedValidFrame == TRUE )
			 {
//				ReceivedValidFrame = FALSE;
//          ReceivedUnwantedFrame
				if( (recframe.Frame.Destination != TS && recframe.Frame.Destination != 255) ||
					 (recframe.Frame.Destination == 255 && (recframe.Frame.FrameType==Token ||
															recframe.Frame.FrameType==BACnetDataExpectingReply ||
															recframe.Frame.FrameType==TestRequest))    // or a proprietary type known to
																										// this node and which expects a reply
					 // or FrameType has a value which indicates a standard or proprietary type
					 // which is not known to this node
				  )
				{
				 ps->validint = 1;
				 break;
				}
//          ReceivedToken
				if( recframe.Frame.Destination == TS && recframe.Frame.FrameType==Token )
				{
         resetport = 700;
				 mstp->UsedToken = FALSE;
				 if( mstp->receivedtoken == 0 )
				 {
						// indicates the panel received the token. It is used in
						// connection with NETTASK. It is used when you want to
						// assure that the token goes ones around the network
						// before to take an action.
						// Ex. If you want to broadcast a command and then to continue
						// after the token goes around the network, set mstp->receivedtoken=0
						// and then wait until mstp->receivedtoken becomes 1.
						mstp->receivedtoken = 1;
						if( tasks[NETTASK].status == SLEEPING )
								 resume(NETTASK);
				 }

				 if(!iamnewonnet)
				 {
					if(mstp->OS!=recframe.Frame.Source)
					{
           // a new panel behind me ON network 
					 mstp->newpanelbehind = 1;
					}
				 }
				 else
					if(mstp->receivedpollformaster==0)
					{
					 // received token before poll for master. There is another panel
					 // with the same panel number. The panel does not respond to the received token
					 mstp->panelconnected = 3;
					 break;
					}
				 mstp->OS=recframe.Frame.Source;
				 if(ready_for_descriptors&0x02)
				 {
					 sendinfo(&frame, 0x04, Station_NUM, mstp->port_number);
					 ready_for_descriptors &= 0xfc;   //first 2 biti set to 0
/*
					mstp->sendinfo_flag|=READYFORDES;
					sendinfoflag = 1;
					resume(NETTASK);
*/
				 }
//---------
//           if first token then broadcast information about its: system name, etc
				 if( mstp->laststation_connected>=0 )
				 {
					--mstp->laststation_connected;
					if( mstp->FirstToken >= 2 )
					{
						if(!mstp->newpanelbehind)
						{
							sendinfo(&frame, ON, Station_NUM, mstp->port_number);
						}
						else
						{
							sendinfo(&frame, ON|0x08, Station_NUM, mstp->port_number);
						}
/*
						if(TS<mstp->OS)
						{
							sendinfo(&frame, 0x02, Station_NUM, mstp->port_number);
						}
*/
					}
					if( mstp->laststation_connected<0 )
					{
						mstp->newpanelbehind=0;
						if( mstp->need_info!=mstp->panel_info1.active_panels )
							sendinfo(&frame, ON, Station_NUM, mstp->port_number);
						if(TS<mstp->OS)
							sendtime=1;
					}
				 }

				 if( mstp->FirstToken < 2 )
				 {
					mstp->FirstToken++;
					if(!mstp->newpanelbehind)
					{
							sendinfo(&frame, ON, Station_NUM, mstp->port_number);
					}
					else
					{
							sendinfo(&frame, ON|0x08, Station_NUM, mstp->port_number);
					}
/*
					if(TS<mstp->OS)
					{
							sendinfo(&frame, 0x02, Station_NUM, mstp->port_number);
					}
*/
				 }

//---------
//           send info
				 if( netpointsflag )
				 {
					if(wantpointsentry || wantpointsentry_router)
					{
						mstp->SendFrame(NULL);  //pad same bytes to announce its presents
						mstp->sendpoints(frame.Buffer, 1);  //network points
					}
					netpointsflag=0;
//					wantpointsentry=0;
					timepoints = 50;
				 }
				 if(!timepoints)
				 {
					mstp->SendFrame(NULL);  //pad same bytes to announce its presents
					mstp->sendpoints(frame.Buffer, 0);  //want points
					netpointsflag++;
				 }

//  syncronize time
				 if(sendtime)
				 {
					 sendtime=0;
					 sendinfo(&frame, 0x02, Station_NUM, mstp->port_number);
					 dayofyear = 0;
				 }
				 else
				 if( dayofyear!=ora_current.dayofyear )
				 {
						dayofyear=ora_current.dayofyear;
						if(TS<mstp->OS)
						{
							sendinfo(&frame, 0x02, Station_NUM, mstp->port_number);
/*
						 sendinfoflag = 1;
						 mstp->sendinfo_flag|=SENDINFO_TIME;
						 resume(NETTASK);
*/
						}
				 }
				 mstp->FrameCount     = 0;
				 ps->MSTP_MASTERState = MSTP_MASTER_USE_TOKEN;
				 break;
				}
//          ReceivedPollForMaster
				if( recframe.Frame.Destination == TS && recframe.Frame.FrameType==PollForMaster )
				{
/*
				 disable();
				 mstp->ReceivedFramePool.Clear();
				 enable();
*/
//      		 SendFrame ReplayToPollForMaster
				 ps->validint = 1;
				 frame.FrameType = ReplyToPollForMaster;
				 frame.Destination = recframe.Frame.Source;
				 frame.Source = TS;
				 frame.Length = 0;
				 mstp->SendFrame(&frame);
				 mstp->FirstToken = 0;
				 mstp->receivedpollformaster = recframe.Frame.Source;
				 break;
				}
				if(mstp->receivedpollformaster==0)
				{
					 /* received frame before poll for master. There is another panel*/
					 /* with the same panel number. The panel does not respond to the received token*/
					 break;
				}
//          ReceivedDataNoReply
				if( (recframe.Frame.Destination == TS || recframe.Frame.Destination == 255) &&
					 (recframe.Frame.FrameType==BACnetDataNotExpectingReply || recframe.Frame.FrameType==TestResponse)
					 // or a proprietary type known to this node which does not expect a reply
				  )
				{
// 			 indicate the successful reception to the higher layer
				 if(!int_disk && !int_disk1 && !STSMremoveflag)
					networklayer( DL_UNITDATAindication, NORMALmessage, 0, recframe.Frame.Destination, recframe.Frame.Source,
										recframe.Frame.Buffer, recframe.Frame.Length, NULL, 0, recframe.Frame.FrameType, SERVER, mstp->port_number);
				 ps->validint = 1;
				 break;
				}
//          ReceivedDataNeedingReply
				if( recframe.Frame.Destination == TS &&
					 (recframe.Frame.FrameType==BACnetDataExpectingReply || recframe.Frame.FrameType==TestRequest)
					 // or a proprietary type known to this node which expects a reply
				  )
				{
//           indicate the successful reception to the higher layer
//				 if(int_disk || save_monitor_status)
				 if( int_disk || int_disk1 || STSMremoveflag )
				 {
//					ps->MSTP_MASTERState = MSTP_MASTER_IDLE;
					ps->validint = 1;
				 }
				 else
				 {
					if( !replyflag )
					{
					 replyflag=1;
					 networklayer( DL_UNITDATAindication, NORMALmessage, 0, recframe.Frame.Destination, recframe.Frame.Source,
									recframe.Frame.Buffer, recframe.Frame.Length, NULL, 0, recframe.Frame.FrameType, SERVER, mstp->port_number);
//				  replyflag=0;
					 ps->MSTP_MASTERState = MSTP_MASTER_ANSWER_DATA_REQUEST;
					}
				  else
				  {
				  }
				 }
				 break;
				}
			 }
			}
			ps->validint=1;
//			if( ps->SilenceTimer < (int)(TNO_TOKEN/TIMERESOLUTION) )
/*
			if( ps->SilenceTimer < Tno_token )
			{
				 if( ((int)(TNO_TOKEN/TIMERESOLUTION)+1-ps->SilenceTimer)>20 )
					 msleep(19);
				 else
					 msleep( (int)(TNO_TOKEN/TIMERESOLUTION)-ps->SilenceTimer);
			}
*/
			if( ps->SilenceTimer < Tno_token-1 )
			{
				 msleep(Tno_token-ps->SilenceTimer);
         resetport--;
			}
			break;
		 case MSTP_MASTER_USE_TOKEN:
			 if( mstp->SendFramePool.RemoveEntry(&frame)<0 )
			 {
//          NothingToSend

/*
//          BACnet version
				FrameCount = Nmax_info_frames;
				MSTP_MASTER_State = MSTP_MASTER_DONE_WITH_TOKEN;
				next = 1;
*/
				if( mstp->TokenCount < NPoll && mstp->SoleMaster==TRUE )
				{
//          mstp->SoleMaster
				mstp->FrameCount = 0;
				mstp->TokenCount = NPoll;
				mstp->SoleMaster = FALSE;
				ps->SilenceTimer = 0;
				ps->MSTP_MASTERState = MSTP_MASTER_IDLE;
				ps->validint = 1;
				}
				else
				{
				mstp->FrameCount = Nmax_info_frames;
				ps->MSTP_MASTERState = MSTP_MASTER_DONE_WITH_TOKEN;
				}
			 }
			 else
			 {
//         SendNoWait
//			  if( MSTP_SendFrameType==TestResponse || MSTP_SendFrameType==BACnetDataNotExpectingReply )
				if( frame.FrameType==TestResponse || frame.FrameType==BACnetDataNotExpectingReply )
					// or a proprietary type which does not expect a reply
			  {
				 mstp->SendFrame(&frame);
				 mstp->FrameCount++;
// wait to allow frame processing in the other panels
				 msleep(15);
				 ps->validint = 1;
/*
				 if(frame.Buffer[8]==SEND_WANTPOINTS_COMMAND || frame.Buffer[8]==SEND_NETWORKPOINTS_COMMAND)
					 msleep(7);
*/
				 ps->MSTP_MASTERState = MSTP_MASTER_DONE_WITH_TOKEN;
				}
//         SendAndWait
				if( frame.FrameType==TestRequest || frame.FrameType==BACnetDataExpectingReply )
					// or a proprietary type which expects a reply
				{
/*
				 disable();
				 mstp->ReceivedFramePool.Clear();
				 enable();
*/
				 ps->validint = 1;
				 ps->EventCount = 0;
				 mstp->SendFrame(&frame);
				 mstp->FrameCount++;
				 ps->MSTP_MASTERState = MSTP_MASTER_WAIT_FOR_REPLY;
				}
			 }
			 break;
		 case MSTP_MASTER_WAIT_FOR_REPLY:
				TimeOut=FALSE;
//			  timerunMSTP = Treply_timeout;
//			  ps->HeartbeatTimer = Treply_timeout;
//			  msleep(120);
//			  msleep(Treply_timeout - ps->SilenceTimer);
			  msleep(Treply_timeout);
//			  timerunMSTP=0xffff;
//			  ps->HeartbeatTimer=0xffff;
//			  if(mstp->ReceivedFramePool.RemoveEntry(ClientBuffer)<0) TimeOut=TRUE;
				if(mstp->ReceivedFramePool.RemoveEntry(&recframe)<0)
				{
				 if( ps->EventCount >= Nmin_octets )
				 {
				  ps->EventCount = 0;
				  if( Treply_timeout>ps->SilenceTimer )
					  msleep(Treply_timeout-ps->SilenceTimer);
				  if(mstp->ReceivedFramePool.RemoveEntry(&recframe)<0)
				  {
						if( ps->EventCount >= Nmin_octets )
						{
						  ps->EventCount = 0;
						  if( Treply_timeout>ps->SilenceTimer )
							  msleep(Treply_timeout-ps->SilenceTimer);
						  if(mstp->ReceivedFramePool.RemoveEntry(&recframe)<0)
						  {
							 TimeOut=TRUE;
						  }
						  else
						  {
								memcpy(ClientBuffer, recframe.Frame.Buffer, recframe.Frame.Length);
						  }
						}
						else
						 TimeOut=TRUE;
				  }
				  else
				  {
						memcpy(ClientBuffer, recframe.Frame.Buffer, recframe.Frame.Length);
					}
				 }
				 else
				 {
					mstp->SendFrame(NULL);  //pad same bytes to announce its presents
          msleep(16);        // allow the requested panel to finish processing 
					TimeOut=TRUE;
					if(NotResponse1)
						NotResponse = 1;
				 }
				}
				else
				{
					memcpy(ClientBuffer, recframe.Frame.Buffer, recframe.Frame.Length);
			  }
//        ReplayTimeout
//			 if( SilenceTimer >= Treply_timeout )
			 if( TimeOut )
			 {
				mstp->FrameCount = Nmax_info_frames;
				ps->MSTP_MASTERState = MSTP_MASTER_DONE_WITH_TOKEN;
				break;
			 }
//			 if( SilenceTimer < Treply_timeout )
			 if( !TimeOut )
			 {
//         InvalidFrame
				if( recframe.ReceivedInvalidFrame == TRUE )
				{
//				 ReceivedInvalidFrame = FALSE;
				 ps->MSTP_MASTERState = MSTP_MASTER_DONE_WITH_TOKEN;
				 break;
			  }
//         ReceivedReply
				if( recframe.ReceivedValidFrame == TRUE &&
					recframe.Frame.Destination == TS &&
					( recframe.Frame.FrameType==BACnetDataNotExpectingReply ||
					  recframe.Frame.FrameType==TestResponse)
					  // or a proprietary type which indicates a reply
					)
			  {
//           indicate successful reception to the higher layer
				 networklayer( DL_UNITDATAindication, NORMALmessage, 0, recframe.Frame.Destination, recframe.Frame.Source,
									ClientBuffer, recframe.Frame.Length, NULL, 0, recframe.Frame.FrameType, CLIENT, mstp->port_number);
//				 ReceivedValidFrame = FALSE;
				 ps->MSTP_MASTERState = MSTP_MASTER_DONE_WITH_TOKEN;
				 break;
				}
//         ReceivePostpone
			  if( recframe.ReceivedValidFrame == TRUE &&
					recframe.Frame.Destination == TS &&
					recframe.Frame.FrameType==ReplyPostponed )
				{
//				 ReceivedValidFrame = FALSE;
				 ps->MSTP_MASTERState = MSTP_MASTER_DONE_WITH_TOKEN;
				 break;
				}
//         ReceivedUnexpectedFrame
				if( recframe.ReceivedValidFrame == TRUE &&
					(recframe.Frame.Destination != TS ||
					 recframe.Frame.FrameType!=BACnetDataNotExpectingReply ||
						recframe.Frame.FrameType!=TestResponse)
						// or a proprietary reply frame
					)
			  {
//				 ReceivedValidFrame = FALSE;
				 ps->MSTP_MASTERState = MSTP_MASTER_IDLE;
				 ps->validint = 1;
				 break;
				}
			 }
			 break;
		 case MSTP_MASTER_DONE_WITH_TOKEN:
//        SendAnotherFrame
			 if( mstp->FrameCount < Nmax_info_frames)
			 {
				 ps->MSTP_MASTERState = MSTP_MASTER_USE_TOKEN;
				 break;
			 }
			 if( mstp->FrameCount >= Nmax_info_frames)
			 {
//         mstp->SoleMaster
				if( mstp->TokenCount < NPoll && mstp->SoleMaster==TRUE )
				{
				mstp->FrameCount = 0;
				mstp->TokenCount++;
				ps->MSTP_MASTERState = MSTP_MASTER_USE_TOKEN;
				break;
				}
//         SendToken
				ps->validint = 1;
				if( (mstp->TokenCount < NPoll && mstp->SoleMaster==FALSE) ||
					 ( mstp->NS==(TS+1)%(Nmax_master+1) ) )
				{
//				if ( timebetweentoken < 25 )
				if ( ps->InactivityTimer < 21 )
				{
				 if( mstp->UsedToken == FALSE )
					mstp->SendFrame(NULL);  //pad same bytes to announce its presents
//				 timerunMSTP = 31 - timebetweentoken;
//				 ps->HeartbeatTimer = 31 - timebetweentoken;
//				 msleep(9);
				 if ( ps->InactivityTimer < 20 )
					 msleep(20 - ps->InactivityTimer);
//				 timerunMSTP=0xffff;
//				 ps->HeartbeatTimer=0xffff;
				}
				mstp->TokenCount++;
				frame.FrameType = Token;
				frame.Destination = mstp->NS;
				if(!mstp->panelOff)
				 frame.Source = TS;
				else
				 frame.Source = mstp->OS;
				frame.Length = 0;
				ps->EventCount = 0;
				mstp->SendFrame(&frame);  //Token
				mstp->RetryCount = 0;
				ps->MSTP_MASTERState = MSTP_MASTER_PASS_TOKEN;
				break;
				}
//         SendMaintanencePFM
				if( mstp->TokenCount >= NPoll && mstp->NS!=(mstp->PS+1)%(Nmax_master+1) )
				{
				mstp->PS = (mstp->PS+1)%(Nmax_master+1);
				frame.FrameType = PollForMaster;
				frame.Destination = mstp->PS;
				frame.Source = TS;
				frame.Length = 0;
				mstp->SendFrame(&frame);  // PollForMaster to PS
				mstp->RetryCount = 0;
				ps->MSTP_MASTERState = MSTP_MASTER_POLL_FOR_MASTER;
				break;
			  }
//         ResetMaintenancePFM
			  if( mstp->TokenCount >= NPoll && mstp->NS==(mstp->PS+1)%(Nmax_master+1) )
			  {
				mstp->PS = TS;
				frame.FrameType = Token;
				frame.Destination = mstp->NS;
				frame.Source = TS;
				frame.Length = 0;
				ps->EventCount = 0;
				mstp->SendFrame(&frame);  // Token to NS
				mstp->RetryCount = mstp->TokenCount = 0;
				ps->MSTP_MASTERState = MSTP_MASTER_PASS_TOKEN;
				break;
			  }
			 }
			 break;
		 case MSTP_MASTER_PASS_TOKEN:
				ps->validint = 1;
				ps->InactivityTimer = 0;
				if( ps->EventCount < Nmin_octets )
					msleep(Tusage_timeout);
				TimeOut=TRUE;
//        SawTokenUser
//			 if( SilenceTimer < Tusage_timeout && EventCount > Nmin_octets )
			 ps->validint = 1;
			 if( ps->EventCount >= Nmin_octets )
			 {
				ps->MSTP_MASTERState = MSTP_MASTER_IDLE;
				break;
			 }
//        RetrySendToken
//			 if( SilenceTimer >= Tusage_timeout && RetryCount < Nretry_token )
			 if( mstp->RetryCount < Nretry_token )
			 {
				mstp->RetryCount++;
				frame.FrameType = Token;
				frame.Destination = mstp->NS;
				frame.Source = TS;
				frame.Length = 0;
				ps->EventCount = 0;
				mstp->SendFrame(&frame);  // Token to NS
				break;
			 }
//        FindNewSuccessor
//			 if( SilenceTimer >= Tusage_timeout && RetryCount >= Nretry_token )
			 if( mstp->RetryCount >= Nretry_token )
			 {
/*
if(!a5)
if (mode_text)
{
 mxyputs(2,5,"                         ");
 mxyputs(2,5,itoa(xvar++, xbuf,10));
 mxyputs(10,5,itoa(ps->EventCount, xbuf,10));
 a5=1;
}
*/
				if(mstp->NS != Station_NUM )
				{
//				 lost_connection = timestart;
//				 mstp->sendinfo(&frame, OFF, mstp->NS);
/*
					sendinfoflag = 1;
					mstp->nextpanelisoff = mstp->NS;
					mstp->sendinfo_flag|=SENDINFO_PANELOFF;
					resume(NETTASK);
*/
					sendinfo(&frame, OFF, mstp->NS, mstp->port_number);
//***				 station_list[mstp->NS-1].state = 0;
				 mstp->station_list[mstp->NS-1].state = 0;
				 mstp->station_list[mstp->NS-1].des_length = 0;
				 mstp->station_list[mstp->NS-1].panel_type = 0;
				 mstp->station_list[mstp->NS-1].version = 0;
				 mstp->panel_info1.active_panels &= ~(1l<<(mstp->NS-1));
				 mstp->need_info &= ~(1l<<(mstp->NS-1));
				 ready_for_descriptors = 0;
				}

				mstp->PS = (mstp->NS+1)%(Nmax_master+1);
				frame.FrameType = PollForMaster;
				frame.Destination = mstp->PS;
				frame.Source = TS;
				frame.Length = 0;
				ps->EventCount = 0;
				mstp->SendFrame(&frame);  // PollForMaster to PS
				mstp->NS = TS;
				mstp->RetryCount = mstp->TokenCount = 0;
				ps->MSTP_MASTERState = MSTP_MASTER_POLL_FOR_MASTER;
/*
if(!a3)
if (mode_text)
{
 mxyputs(2,3,"                         ");
 mxyputs(2,3,itoa(xvar++, xbuf,10));
 mxyputs(10,3,"Retry>2, PFM");
 a3=1;
}
*/
				break;
			 }
			 break;
		 case MSTP_MASTER_NO_TOKEN:
//        SawFrame
			 ps->validint = 1;
			 if( (ps->SilenceTimer*TIMERESOLUTION < TNO_TOKEN + (TSLOT*TS)) && ps->EventCount>Nmin_octets )
			 {
				ps->MSTP_MASTERState = MSTP_MASTER_IDLE;
				break;
			 }
//        GenerateToken
			 if( (ps->SilenceTimer*TIMERESOLUTION >= TNO_TOKEN + (TSLOT*TS)) &&
					(ps->SilenceTimer*TIMERESOLUTION < TNO_TOKEN + (TSLOT*(TS+1))) )
			 {
/*
if(!a2)
if (mode_text)
{
 mxyputs(2,2,"                         ");
 mxyputs(2,2,itoa(xvar++, xbuf,10));
 mxyputs(10,2,"Generate token");
 a2=1;
}
*/
				mstp->PS = (TS+1)%(Nmax_master+1);
				frame.FrameType = PollForMaster;
				frame.Destination = mstp->PS;
				frame.Source = TS;
				frame.Length = 0;
				ps->EventCount = 0;
				mstp->SendFrame(&frame);  // PollForMaster to PS
				mstp->NS = TS;
				mstp->RetryCount = mstp->TokenCount = 0;
				ps->MSTP_MASTERState = MSTP_MASTER_POLL_FOR_MASTER;
				break;
			 }
			 if( ps->SilenceTimer*TIMERESOLUTION >= TNO_TOKEN + (TSLOT*(TS+1)) )
			 {
				ps->SilenceTimer=0;
				ps->MSTP_MASTERState = MSTP_MASTER_IDLE;
				break;
			 }
			 break;
		 case MSTP_MASTER_POLL_FOR_MASTER:
			 TimeOut=FALSE;
//			  timerunMSTP=Tusage_timeout;
//			  ps->HeartbeatTimer=Tusage_timeout;
//			  msleep(100);
//			  msleep(Tusage_timeout - ps->SilenceTimer);
//			  timerunMSTP=0xffff;
//			  ps->HeartbeatTimer=0xffff;
			 if(mstp->ReceivedFramePool.RemoveEntry(&recframe)<0)
			 {
				msleep(Tusage_timeout);
				if(mstp->ReceivedFramePool.RemoveEntry(&recframe)<0)
				{
				 if( ps->EventCount >= Nmin_octets )
				 {
					msleep(Tusage_timeout);
					if(mstp->ReceivedFramePool.RemoveEntry(&recframe)<0)
						 TimeOut=TRUE;
				 }
				 else TimeOut=TRUE;
				}
       }
			 ps->validint = 1;
			 if( !TimeOut )
			 {
//         ReceivedReplyToPFM
			  if( recframe.ReceivedValidFrame == TRUE &&
					recframe.Frame.Destination == TS &&
					recframe.Frame.FrameType==ReplyToPollForMaster )
			  {
				 mstp->NS = recframe.Frame.Source;
				 ps->EventCount = 0;
				 frame.FrameType = Token;
				 frame.Destination = mstp->NS;
				 frame.Source = TS;
				 frame.Length = 0;
				 mstp->SendFrame(&frame);  // Token to NS
				 mstp->PS = TS;
				 mstp->RetryCount = mstp->TokenCount = 0;
//				ReceivedValidFrame = FALSE;
				 ps->MSTP_MASTERState = MSTP_MASTER_PASS_TOKEN;
//				 if(!iamnewonnet)
//					 newpanelon = mstp->NS;
				 break;
				}
//         ReceivedUnexpectedFrame
				if( recframe.ReceivedValidFrame == TRUE &&
					(recframe.Frame.Destination != TS ||
					 recframe.Frame.FrameType!=ReplyToPollForMaster) )
				{
//				ReceivedValidFrame = FALSE;
				ps->MSTP_MASTERState = MSTP_MASTER_IDLE;
				break;
			  }
			 }
//        SoleMaster
			 if(mstp->SoleMaster == TRUE &&
//				  (ps->SilenceTimer>Tusage_timeout ||
					( TimeOut ||
					recframe.ReceivedInvalidFrame==TRUE) )
			 {
				mstp->FrameCount=0;
//				ReceivedInvalidFrame = FALSE;
				ps->MSTP_MASTERState = MSTP_MASTER_USE_TOKEN;
				break;
			 }
//        DoneWithPFM
			 if(mstp->SoleMaster == FALSE && mstp->NS!=TS &&
//				  (ps->SilenceTimer>Tusage_timeout ||
				  ( TimeOut ||
					recframe.ReceivedInvalidFrame==TRUE) )
			 {
				ps->EventCount=0;
				frame.FrameType = Token;
				frame.Destination = mstp->NS;
				frame.Source = TS;
				frame.Length = 0;
				mstp->SendFrame(&frame);  // Token to NS
				mstp->RetryCount=0;
//				ReceivedInvalidFrame = FALSE;
				ps->MSTP_MASTERState = MSTP_MASTER_PASS_TOKEN;
				break;
			 }
//        SendNextPFM
			 if(mstp->SoleMaster == FALSE && mstp->NS==TS && TS!=(mstp->PS+1)%(Nmax_master+1) &&
//				  (ps->SilenceTimer>Tusage_timeout ||
				  ( TimeOut ||
					 recframe.ReceivedInvalidFrame==TRUE) )
			 {
				mstp->PS=(mstp->PS+1)%(Nmax_master+1);
				frame.FrameType = PollForMaster;
				frame.Destination = mstp->PS;
				frame.Source = TS;
				frame.Length = 0;
        ps->EventCount = 0;     //Add Dec 1997
				mstp->SendFrame(&frame);  // PollForMaster to PS
				mstp->RetryCount=0;
//				ReceivedInvalidFrame = FALSE;
				break;
			 }
//        DeclareSoleMaster
			 if(mstp->SoleMaster == FALSE && mstp->NS==TS && TS==(mstp->PS+1)%(Nmax_master+1) &&
//				  (ps->SilenceTimer>Tusage_timeout ||
				  ( TimeOut ||
					 recframe.ReceivedInvalidFrame==TRUE) )
			 {
				mstp->SoleMaster = TRUE;
				mstp->FrameCount=0;
//				ReceivedInvalidFrame = FALSE;
				ps->MSTP_MASTERState = MSTP_MASTER_USE_TOKEN;
				ready_for_descriptors = 0;
				mstp->panelconnected=2;
				break;
			 }
			 break;
		 case MSTP_MASTER_ANSWER_DATA_REQUEST:
/*
//         reply
//         if a reply is available from the higher layers within Treply_delay
//         after the reception of the final octet of the requesting frame
				SendFrame(&frame);
				mstp->MSTP_MASTERState = MSTP_MASTER_IDLE;
//         DeferredReply
//         if no reply available
				frame.FrameType = ReplyPostponed;
				frame.Destination = MSTP_Source;
				frame.Source = TS;
				frame.Length = 0;
				SendFrame(&frame);
				mstp->MSTP_MASTERState = MSTP_MASTER_IDLE;
*/
/*			 if( SendFramePool.RemoveEntry(&frame, MSTP_Source, MSTP_Destination)>=0 )
			 {
				SendFrame(&frame);
				mstp->MSTP_MASTERState = MSTP_MASTER_IDLE;
			 }
			 else
			 {
			  mxyputs(70,2,"ReplyPostponed");
			  frame.FrameType = ReplyPostponed;
			  frame.Destination = MSTP_Source;
			  frame.Source = TS;
			  frame.Length = 0;
			  SendFrame(&frame);
			  mstp->MSTP_MASTERState = MSTP_MASTER_IDLE;
			 }
*/
			 ps->validint = 1;
			 if( replyflag==2 )   // there is response
			 {
				if( tasks[tswitch].ps->SilenceTimer <= Treply_delay )
					mstp->SendFrame((FRAME *)&ServerBuffer[0]);
				else
				{
				 n = mstp->SendFramePool.NextFreeEntry();
				 if( n >=0  )
				 {
// move the frame from ServerBuffer in the queue
					 memcpy( &mstp->SendFramePool.Frame[n], ServerBuffer, sizeof(mstp->SendFramePool.Frame[n]));
			     mstp->SendFramePool.status[n]=1;
				 }
				}
       }
			 replyflag=0;
			 ps->MSTP_MASTERState = MSTP_MASTER_IDLE;
			 break;
	 }
 }
// delete ser_rs485;
// ser_rs485 = NULL;
 resume_suspend( PROJ, MSTP_MASTER ); //		task_switch();
}

//int clientprocedure( ClientTSMStateEnum state, char command, int bank, char *asdu, char **data, int lmax, unsigned int &length, unsigned int &length_asdu, unsigned int &last_length)
int clientprocedure( char command, int bank, char *asdu, char **data, int lmax, unsigned int &length, unsigned int &length_asdu, unsigned int &last_length)
{
 unsigned int l;
 int str_new_size;
 char *ptr;
 byte no_points;
 Bank_Type tbank;
 tbank = *((Bank_Type *)&bank);
 if(command > 100)
 {
//  ctype = WRITE;
	command -= 100;
 }
 else
 {
	return READ;
//	 ctype = READ;
 }

//	if( length > lmax )
	{
		if( serial_access && (serial_access!=station_num) && serial_panel_type==MINI_T3000 )
		{
//			if(command!=WRITEPROGRAMCODE_T3000)
				lmax =   Max_frame_minirouter;
				maxFrame = Max_frame_minirouter;
		}
	}

	str_new_size = lmax;
	switch( command )            //command
	{
		case OUT+1:
		case IN+1:
		case VAR+1:
		case CON+1:
		case WR+1:
		case AR+1:
		case PRG+1:
		case GRP+1:
		case AMON+1:
		case AY+1:
		case ALARMM+1:
		{
		  ptr = (char *)&ptr_panel->info[command-1];
		  str_new_size = ((Info_Table *)ptr)->str_size;
			break;
		}
	}
 if( length > lmax )
 {
	l = lmax/str_new_size;
	length_asdu = l*str_new_size;
	length -= length_asdu;
 }
 else
 {
	length_asdu = length;
	length = 0;
 }
 if(*data)
 {
	memcpy(asdu, *data, length_asdu);
	*data += length_asdu;
 }
 last_length += length_asdu;
 return WRITE;
}

// cl=0 application,  cl=1 context; t=tag number
int encodetag(char cl, char t, char *tag, unsigned length)
{
  int n=0;
  if( length <= 4 )
  {
	tag[0]=(t<<4)+(cl<<3)+ length;
	n=1;
  }
  if( length >= 5 && length<=253 )
  {
	tag[0]=(t<<4)+(cl<<3)+0x05;
	tag[1]=length;
	n=2;
  }
	if( length >= 254 && length<=65535 )
  {
	tag[0]=(t<<4)+(cl<<3)+0x05;
	tag[1]=254;
	tag[2]=(length>>8);
	tag[3]=length&0x00FF;
	n=4;
	}
	return n;
}

int decodetag(char *tag, unsigned int *length)
{
  unsigned int n=0, l=0;
  l = tag[0]&0x07;
  if( l <= 4 )
  {
	n=1;
  }
  if( l==5 )
  {
	n=2;
	l = tag[1];
	if( l==254 )
	{
	 n=4;
	 l = ( ((unsigned int)tag[2]) << 8)+tag[3];
	}
	}
	*length = l;
	return n;
}

char xxxx;

int ClientTransactionStateMachine(
			 ServicePrimitive Event,  int Service, FlowControl flowcontrol, int network,
			 int destination, int source, char invokeID, char *data, unsigned int *data_length,
			 char command, int arg, char vendorID, long timeout = TIMEOUT_NETCALL,
			 char *returnargs=NULL, int *length_returnargs=NULL,
			 char *sendargs=NULL, int length_sendargs=0,
			 char bytearg=0, int task = -1, int port = -1, int others = 0
			)
{
 char apci[MAXAPCI], asdu[MAXAPDUSIZE], *ptr, laststate;
 char next, win_size, retry=0, compressed=0, invokeid;
 char PDUtype, seg, mor, sa, maxresp, nosequence, windowsize, srv;
 int	cmd,current, error, service, length_apci = 4;
 long l;
 unsigned int n;
 unsigned int length, length_asdu, last_length, data_length_pack;
 struct CTSMTable *ptable;

 GWindow *D=NULL;

 length_asdu = 0;
 length = *data_length;
 error = RS232_SUCCESS;
 next=1;
// ClientSA = source;
// ClientDA = destination;
// PTRReceivedClientAPDU = NULL;
// LengthReceivedClientAPDU = 0;

 if ((current=ClientTSMTable.newentry(task, network, destination, source, invokeID)) == CTSM_ILLEGAL)
 {
	return ERROR_COMM;   //reject PDU
 }
 cmd=0;
 ptable = &ClientTSMTable.table[current];
 ptable->others = others;
 maxFrame=MAXASDUSIZE;
 while(next)
 {
	switch ( ptable->CTSM_State ){
	 case CTSM_IDLE:
			if (Event == UNCONF_SERVrequest)
			{
//			  send_Unconf_Req PDU
				apci[0] = (BACnetUnconfirmedRequestPDU<<4);
				apci[1] = UnconfirmedPrivateTransfer;

				apci[2]=0x09;             // Context Tag 0( Unsigned, Length=1)
				apci[3]=VendorID;
				apci[4]=0x1A;             // Context Tag 1( Unsigned, Length=2)
				apci[5] = command;
				apci[6] = *(byte*)&arg;   //   arg low

				if((command==50+100) && apci[6]==70)
				{
					length_asdu = sendinfo(asdu, (int)(*((byte*)&arg+1)), *((int*)data), destination, port );
					length_apci = 7;
				}
				else
				{
					if( command==50 && (apci[6]==SEND_WANTPOINTS_COMMAND || apci[6]==SEND_NETWORKPOINTS_COMMAND) )
					{
					 cmd=apci[6];
					 length_asdu = sendpoints(asdu, apci[6], port, apci[6]); //SEND_WANTPOINTS_COMMAND want_points, SEND_NETWORKPOINTS_COMMAND network_points
					 if(!length_asdu)
					 {
//						CTSM_State=CTSM_IDLE;
						next=0;
            break;
					 }
					 length_apci = 7;
					}
					n = 3+length_asdu+length_sendargs;      // 3 = arg low, arg high, res
																								 // 2 = length of sendags
					length_apci = 7 + encodetag(1, 2, &apci[7], n);
// parameters
					if(command==50 || command==150)
					{
					 apci[length_apci++] = *((byte*)&arg+1);      //extra high
					 apci[length_apci++] = 0;
					}
					else
					{
					 apci[length_apci++] = *(byte*)&arg;      //extra low
					 apci[length_apci++] = *((byte*)&arg+1);  //extra high
					}
					apci[length_apci++] = bytearg;                 //reserved

					if(command <= 100)
					{
					 if(sendargs)
					 {
						length_asdu = (length_sendargs>MAXAPDUSIZE)?0:length_sendargs;
						memcpy(asdu, sendargs, length_asdu);
					 }
					}
					else
					{
					 memcpy(asdu, data, *data_length);
					 length_asdu = *data_length;
					}
				}
				networklayer( N_UNITDATArequest, NORMALmessage, network, destination, source, asdu, length_asdu, apci, length_apci, BACnetDataNotExpectingReply,CLIENT,port);
//				CTSM_State=CTSM_IDLE;
				next=0;
			}
			if (Event == CONF_SERVrequest)
			{
/*         if(APDU > max_APDU_length_supported)
				{
				 send Conf_Req PDU with
						segmented_msg = TRUE
						more_follows = TRUE
				 CTSM_State=CTSM_SEGMENTING_REQUEST;
				}
				if(APDU <= max_APDU_length_supported)
				{
				 send Conf_Req PDU with
						segmented_msg = FALSE
				 CTSM_State=CTSM_AWAIT_CONFIRMATION;
				}
*/
			 if (Service==ConfirmedPrivateTransfer)
			 {
				win_size = 0;
				last_length = 0;
				nosequence = 1;
				while( ++win_size<=WINDOWSIZE )
				{
				 if(command > 100)       //  Write
				 {
//					clientprocedure( ptable->CTSM_State, command, arg, &asdu[0], &data, MAXASDUSIZE, length, length_asdu, last_length);
					clientprocedure( command, arg, &asdu[0], &data, maxFrame, length, length_asdu, last_length);
					if(length)
					{               //segmented message
					 apci[0] = (BACnetConfirmedRequestPDU<<4)|0x0c ;
					 ptable->CTSM_State=CTSM_SEGMENTING_REQUEST;
					 mor=1;
					}
					else
					{
					 apci[0] = (BACnetConfirmedRequestPDU<<4);
					 ptable->CTSM_State=CTSM_AWAIT_CONFIRMATION;
					 mor=0;
					}
				 }
				 else                   //read
				 {
					apci[0] = (BACnetConfirmedRequestPDU<<4)+(1<<1);
					ptable->CTSM_State=CTSM_AWAIT_CONFIRMATION;
					mor = 0;
				 }
				 apci[1] = 0x03;  //up to 480 bytes
				 apci[2] = invokeID;
				 if(mor)
				 {
					apci[3] = nosequence++;
					apci[4] = WINDOWSIZE;
					apci[5] = Service;
					length_apci = 6;
				 }
				 else
				 {
					apci[3] = Service;
					length_apci = 4;
				 }
				 apci[length_apci++] = 0x09;            // Context Tag 0( Unsigned, Length=1)
				 apci[length_apci++] = vendorID;
				 apci[length_apci++] = 0x1A;            // Context Tag 1( Unsigned, Length=2)
				 apci[length_apci++] = command;
				 apci[length_apci++] = *(byte*)&arg;
				 if(command > 100)
					 n = 3+length_asdu;      // 3 = arg low, arg high, res
				 else
					 n = 3+length_asdu+length_sendargs;      // 3 = arg low, arg high, res
																		// 2 = length of sendags
				 if(mor)
					n += 2;  //  2 = data length
				 length_apci += encodetag(1, 2, &apci[length_apci], n);
// parameters
				 if(command==50 || command==150)
				 {
					apci[length_apci++] = *(((byte*)&arg)+1);      //extra high
					apci[length_apci++] = 0;
				 }
				 else
				 {
					apci[length_apci++] = *(byte*)&arg;      //extra low
					apci[length_apci++] = *(((byte*)&arg)+1);  //extra high
				 }
				 apci[length_apci++] = bytearg;                 //reserved
				 if(mor)
				 {
					memcpy(&apci[length_apci], data_length, 2);
					length_apci += 2;
				 }

				 if(command <= 100)
					 if(sendargs)
					 {
						length_asdu = (length_sendargs>MAXAPDUSIZE)?0:length_sendargs;
						memcpy(asdu, sendargs, length_asdu);
					 }

//				 PTRReceivedClientAPDU = NULL;
//				 LengthReceivedClientAPDU = 0;
				 NotResponse = 0;
				 laststate = CTSM_IDLE;
				 if( !networklayer( N_UNITDATArequest, NORMALmessage, network, destination, source, asdu, length_asdu, apci, length_apci, BACnetDataExpectingReply,CLIENT+(others<<8)) )
				 {
			    error = RS232_ERROR;
					next = 0;
					break;
				 }
				 if(!mor) break;
				}
				win_size=0;
			 }
			 else
			 {
					apci[0] = (BACnetConfirmedRequestPDU<<4);
					apci[1] = 0x03;  //up to 480 bytes
					apci[2] = invokeID;
					apci[3] = Service;
					length_apci = 4;
					ptable->CTSM_State=CTSM_AWAIT_CONFIRMATION;
					mor = 0;
					networklayer( N_UNITDATArequest, NORMALmessage, network, destination, source, data, *data_length, apci, length_apci, BACnetDataExpectingReply);
					break;
			 }
			}
			break;
	 case CTSM_SEGMENTING_REQUEST:
/*
			if (Event == SEGMENT_ACK.indication // with server==TRUE)
			{
			 if (not final APDU segment)
			 {
				send Conf_Req PDU with
						segmented_msg = TRUE
						more_follows = TRUE
			 }
			 if (final APDU segment)
			 {
				send Conf_Req PDU with
					  segmented_msg = TRUE
						more_follows = FALSE
			 }
			 if (no more APDU segments)
			 {
				 CTSM_State=CTSM_AWAIT_CONFIRMATION;
			 }
			}
*/
			error = RS232_ERROR;
//			l = timestart;
			if( ptable->task  >= 0 )
			{
				 if( !ptable->state )
//					 msleep((int)(((int)(timeout))*18));  //18.2
					 msleep(220);             //11sec 
			}
			else
			{
//				tasks[tswitch].delay_time = timeout*1000L;
					tasks[tswitch].delay_time = 12000L;
/*
				if(xxxx==1)
				{
					while ( tasks[tswitch].delay_time>=0 );
					xxxx++;
				}
				else
					while ( !ptable->state && tasks[tswitch].delay_time>=0 );
*/
				while ( !ptable->state && tasks[tswitch].delay_time>=0 )
				{
				 if( bioskey_new(1) == CTRLBREAK )
				 {
					if( (others&NETCALL_NOTCTRLBREAK)!=NETCALL_NOTCTRLBREAK )
					{
					 error = USER_ABORT;
					 break;
					}
				 }
				 if(NotResponse && laststate == CTSM_IDLE)
						break;
				}
			}
			if( ptable->state )
//			if( ptable->state && ( !((others&NETCALL_WRITERETRY)==NETCALL_WRITERETRY) || (((others&NETCALL_WRITERETRY)==NETCALL_WRITERETRY) && retry  || (!retry && nosequence!=10 && nosequence!=20 && nosequence!=30&& nosequence!=80&& nosequence!=100&& nosequence!=120))) )
//			if( ptable->state && ( !((others&NETCALL_WRITERETRY)==NETCALL_WRITERETRY) || (((others&NETCALL_WRITERETRY)==NETCALL_WRITERETRY) && retry  || (!retry && nosequence!=2 && nosequence!=3 && nosequence!=4 && nosequence!=5 && nosequence!=6 && nosequence!=100 && nosequence!=120))) )
			{
				invokeid = ptable->data[1];
//				if( invokeid==invokeID )
//				{
				PDUtype  = ptable->data[0]>>4;
				srv      = (ptable->data[0]&0x01)&&1;
				memcpy(apci, ptable->data, MAXAPCI);
				if(PDUtype==BACnetRejectPDU)
					error = RS232_REJECT;
				else
					error = RS232_SUCCESS;
				retry = 0;
//				}
			}

			if( error == RS232_ERROR && !( NotResponse && laststate == CTSM_IDLE) )
			{
				if( ((others&NETCALL_WRITERETRY)==NETCALL_WRITERETRY) && retry++ < 1 )   //1
				{                               //retry count not exceed
/*
char xxxx[5];
itoa(nosequence-1,xxxx,10);
mxyputs(20,20,xxxx,Black,White);
*/
			   length += last_length;
				 data -= last_length;
//				 last_length = 0;
				 nosequence--;

				 if(!win_size) last_length = 0;
				 while(++win_size<=WINDOWSIZE && ptable->CTSM_State==CTSM_SEGMENTING_REQUEST)
				 {
					if(mor)
					{
					 clientprocedure( command, arg, asdu, &data, maxFrame, length, length_asdu, last_length);
					 if(length)
					 {               //segmented message
						apci[0] = (BACnetConfirmedRequestPDU<<4)|0x0c ;
						mor=1;
					 }
					 else
					 {
						apci[0] = (BACnetConfirmedRequestPDU<<4)|0x08;
						mor=0;
						ptable->CTSM_State=CTSM_AWAIT_CONFIRMATION;
						laststate = CTSM_SEGMENTING_REQUEST;
					 }
					 apci[1] = 0x03;  //up to 480 bytes
					 apci[2] = invokeID;
					 apci[3] = nosequence++;
					 apci[4] = WINDOWSIZE;
					 apci[5] = Service;
					 apci[6] = 0x09;            // Context Tag 0( Unsigned, Length=1)
					 apci[7] = vendorID;
					 apci[8] = 0x1A;            // Context Tag 1( Unsigned, Length=2)
					 apci[9] = command;
					 apci[10] = *(byte*)&arg;
 					 if( nosequence==2 )  //resend first frame
					 {
						n = 3+length_asdu;      // 3 = arg low, arg high, res
						n += 2;  //  2 = data length
						length_apci = 11+encodetag(1, 2, &apci[11], n);
						if(command==50 || command==150)
						{
						 apci[length_apci++] = *(((byte*)&arg)+1);      //extra high
						 apci[length_apci++] = 0;
						}
						else
						{
						 apci[length_apci++] = *(byte*)&arg;      //extra low
						 apci[length_apci++] = *(((byte*)&arg)+1);  //extra high
						}
						apci[length_apci++] = bytearg;                 //reserved
						memcpy(&apci[length_apci], data_length, 2);
						length_apci += 2;
					 }
					 else
						length_apci = 11+encodetag(1, 2, &apci[11], length_asdu);
					 ptable->state = 0;
					 networklayer( N_UNITDATArequest, NORMALmessage, network, destination, source, asdu, length_asdu, apci, length_apci, BACnetDataExpectingReply);
					 laststate = CTSM_SEGMENTING_REQUEST;
//					 if(ptable->others&NETCALL_SIGN) communication_sign(data_const+(*data_length)-length,data_length_const?data_length_const:*data_length);
					}
/*
					else
					{
					 ptable->state = 0;
					 ptable->CTSM_State=CTSM_AWAIT_CONFIRMATION;
					 laststate = CTSM_SEGMENTING_REQUEST;
					}
*/
				 }
				 win_size=0;
				 break;
				}
			}
			if( error == RS232_ERROR || (error == USER_ABORT || error == RS232_REJECT) || retry >=1 )
			{
			 apci[0] = (BACnetAbortPDU<<4);   //server=FALSE
			 apci[1] = invokeID;
			 apci[2] = 0;           //other reasons
			 length_apci = 3;
			 networklayer( N_UNITDATArequest, NORMALmessage, network, destination, source, NULL, 0, apci, length_apci, BACnetDataNotExpectingReply);
//			 CTSM_State=CTSM_IDLE;
			 next=0;
			 if( error == RS232_ERROR )
				if(NotResponse && laststate == CTSM_IDLE)
				 delay(2000);
			 break;
			}
/*
// retry
			if(error == RS232_ERROR)	//timeout
			{
			 retry++;
			 length += last_length;
			 *data -= last_length;
//			 last_length = 0;
			 nosequence--;
			 win_size=0;
			 PDUtype = BACnetSegmentACKPDU;
			 CTSM_State=CTSM_IDLE;
			 next=0;
			 break;
			}
*/
			if (PDUtype == BACnetSegmentACKPDU)
			{
			 if(!win_size) last_length = 0;
			 while(++win_size<=WINDOWSIZE && ptable->CTSM_State==CTSM_SEGMENTING_REQUEST)
			 {
				if(mor)
				{
//				 clientprocedure( CTSM_State, command, arg, asdu, &data, MAXASDUSIZE, length, length_asdu, last_length);
				 clientprocedure( command, arg, asdu, &data, maxFrame, length, length_asdu, last_length);
				 if(length)
				 {               //segmented message
					apci[0] = (BACnetConfirmedRequestPDU<<4)|0x0c ;
					mor=1;
				 }
				 else
				 {
					apci[0] = (BACnetConfirmedRequestPDU<<4)|0x08;
					mor=0;
					ptable->CTSM_State=CTSM_AWAIT_CONFIRMATION;
					laststate = CTSM_SEGMENTING_REQUEST;
				 }
				 apci[1] = 0x03;  //up to 480 bytes
				 apci[2] = invokeID;
				 apci[3] = nosequence++;
				 apci[4] = WINDOWSIZE;
				 apci[5] = Service;
				 apci[6] = 0x09;            // Context Tag 0( Unsigned, Length=1)
				 apci[7] = vendorID;
				 apci[8] = 0x1A;            // Context Tag 1( Unsigned, Length=2)
				 apci[9] = command;
				 apci[10] = *(byte*)&arg;
				 length_apci = 11+encodetag(1, 2, &apci[11], length_asdu);
				 ptable->state = 0;
				 networklayer( N_UNITDATArequest, NORMALmessage, network, destination, source, asdu, length_asdu, apci, length_apci, BACnetDataExpectingReply);
				 laststate = CTSM_SEGMENTING_REQUEST;
				 if(ptable->others&NETCALL_SIGN) communication_sign(data_const+(*data_length)-length,data_length_const?data_length_const:*data_length);
				}
				else
				{
				 ptable->state = 0;
				 ptable->CTSM_State=CTSM_AWAIT_CONFIRMATION;
				 laststate = CTSM_SEGMENTING_REQUEST;
				}
			 }
			 win_size=0;
			 retry=0;
			 break;
			}
/*
			if (Event == ABORT.indication with server==TRUE)
			{
			send ABORT.indication
				CTSM_State=CTSM_IDLE;
				next=0;
			}
*/
			if (PDUtype == BACnetAbortPDU && srv)
			{
//			 CTSM_State=CTSM_IDLE;
			 error = RS232_ERROR;
			 next=0;
			 break;
			}
/*			if (unexpected PDU from server)
			{
			send Abort PDU with server = FALSE
				CTSM_State=CTSM_IDLE;
				next=0;
			}
		 if (timeout waiting for PDU)
		 {
			if(retry count not exceed)
			{
				resend previous CONF_req PDU segment
				 CTSM_State=CTSM_SEGMENTING_REQUEST;
			}
			if(retry count exceeded)
			{
				send CONF_SERV.confirm(-)
				 CTSM_State=CTSM_IDLE;
			 next=0;
			}
		 }
			if (Event == ABORT.request)
			{
			send Abort PDU with server = FALSE
				CTSM_State=CTSM_IDLE;
				next=0;
			}
*/
//			CTSM_State=CTSM_IDLE;
			error = RS232_ERROR;
			next=0;
			break;
	 case CTSM_AWAIT_CONFIRMATION:
			error = RS232_ERROR;
//       wait for respons
//			l = timestart;
			if( ptable->task  >= 0 )
			{
				 if( !ptable->state )
					 msleep((int)(((int)(timeout))*18));   //18.2
			}
			else
			{
				if( laststate == CTSM_SEGMENTING_REQUEST )
					tasks[tswitch].delay_time = 12000L;
				else
					tasks[tswitch].delay_time = timeout*1000L;
//				while ( !ptable->state && timestart < l+timeout )
				while ( !ptable->state && tasks[tswitch].delay_time>=0 )
				{
				 if( bioskey_new(1) == CTRLBREAK )
				  if( (others&NETCALL_NOTCTRLBREAK)!=NETCALL_NOTCTRLBREAK )
					{
					 error = USER_ABORT;
					 break;
				  }
				 if(NotResponse && laststate == CTSM_IDLE)
						break;
				}
			}
			if( ptable->state )
			{
				invokeid = ptable->data[1];
//				if( invokeid==invokeID )
//				{
				PDUtype  = ptable->data[0]>>4;
				srv      = (ptable->data[0]&0x01)&&1;
				memcpy(apci, ptable->data, MAXAPCI);
				if(PDUtype==BACnetRejectPDU)
					error = RS232_REJECT;
				else
					error = RS232_SUCCESS;
//				}
			}
			if(error!=SUCCESS)		//timeout
			{
/*
			if (Event == ABORT.request)
			{
//         send Abort PDU with server = FALSE
				CTSM_State=CTSM_IDLE;
				next=0;
			}
*/
			 if(NotResponse && laststate == CTSM_IDLE)
			 {
				next=0;
				break;
			 }
			 apci[0] = (BACnetAbortPDU<<4);   //server=FALSE
			 apci[1] = invokeID;
			 apci[2] = 0;           //other reasons
			 length_apci = 3;
			 if(destination!=255)
				 networklayer( N_UNITDATArequest, NORMALmessage, network, destination, source, NULL, 0, apci, length_apci, BACnetDataNotExpectingReply);
//			 CTSM_State=CTSM_IDLE;
			 next=0;
			 break;
			}
			if (PDUtype == BACnetSimpleACKPDU)
			{
//			  send CONF_SERV.cnf(+)
//				CTSM_State=CTSM_IDLE;
				next=0;
				break;
			}
/*			if (Event == Complex_ACK PDU with segmented_msg = FALSE)
			{
				send CONF_SERV.cnf(+)
				CTSM_State=CTSM_IDLE;
				next=0;
			}
			if (CTSM_Event == Complex_ACK PDU with segmented_msg = TRUE
																more_follows = TRUE )
			{
				if(segmentation is to be done by AE)
				{
				 send SegmentACK PDU with server = FALSE
				 CTSM_State=CTSM_AE_SEGMENTED_CONFIRMATION;
				}
				if(segmentation is to be done by AP)
				{
				 send CONF_SERV.cnf(+) with more_follows = TRUE
				 CTSM_State=CTSM_AP_SEGMENTED_CONFIRMATION;
				}
			}
*/
			if (PDUtype == BACnetComplexACKPDU)
			{
			 seg = (apci[0] & 0x08)&&1;
			 mor = (apci[0] & 0x04)&&1;
			 if(seg)
			 {
				nosequence = apci[2];
				windowsize = apci[3];
				service = apci[4];
				sa = 5;
				if( nosequence != 1 )
				{      //error
				 error = RS232_ERROR;
//				 CTSM_State=CTSM_IDLE;
				 next=0;
				 break;
				}
			 }
			 else
			 {
				service = apci[2];
				sa = 3;
			 }
			 if (service==Service)
			 {
/*
				application octet string
				check vendorID and command from asdu respons
					0x21;            // Application Tag 2( Unsigned, Length=1)
					PTRtable->vendorID;
					0x21;            // Application Tag 2( Unsigned, Length=1)
					PTRtable->command;
*/
				sa += decodetag(&apci[sa], &n);  //vendorid
				if( vendorID == apci[sa] )
				{
				sa += n;
				sa += decodetag(&apci[sa], &n);  //service
				if( (command == apci[sa]) && ( command!=50 || (command==50 &&  *(byte*)&arg==apci[sa+1])) )
				{
				sa += n;
				sa += decodetag(&apci[sa], (unsigned *)&last_length);   //asdu length
				if(seg==TRUE && mor==TRUE)  // segmented_msg = TRUE and
													// more_follows = TRUE
				{
/*
				if(segmentation is to be done by AE)
				{
				 send SegmentACK PDU with server = FALSE
				 CTSM_State=CTSM_AE_SEGMENTED_CONFIRMATION;
				}
*/
//      2 bytes - total length of response data
				data_length_pack =  *((unsigned int *)(&ptable->data[sa]));
				sa += 2;
//      READPROGRAMCODE_T3000 : 4 byte : 2 bytes - programs pool, 2 bytes - programs pool used
//      READGROUPELEMENTS_T3000 4 byte : 2 bytes - max_elements, 2 bytes - cur_elements
				if( command == READPROGRAMCODE_T3000 || command == READGROUPELEMENTS_T3000 )
				{
					if( returnargs )
						memcpy(returnargs, &ptable->data[sa], 4);
					sa += 4;
				}
				ptable->LengthReceivedClientAPDU -= sa;
				if(data)
				{
				 if(!compressed)
				 {
					memcpy(data, &ptable->data[sa], ptable->LengthReceivedClientAPDU);
				 }
				 else
				 {
					ptable->LengthReceivedClientAPDU=uncompress(data, data_length_pack,  &ptable->data[sa], ptable->LengthReceivedClientAPDU);
				 }
				 *data_length += ptable->LengthReceivedClientAPDU;
				}
				if( flowcontrol == AEFLOWCONTROL )
				{
				 if(data)
					data += ptable->LengthReceivedClientAPDU;
				 last_length = ptable->LengthReceivedClientAPDU;
				 ptable->state = 0;
				 if( ++win_size >= windowsize )
				 {
					apci[0] = (BACnetSegmentACKPDU<<4);
					apci[1] = invokeID;
					apci[2] = nosequence;
					apci[3] = WINDOWSIZE;

					apci[4] = 0x09;            // Context Tag 0( Unsigned, Length=1)
					apci[5] = vendorID;
					apci[6] = 0x1A;            // Context Tag 1( Unsigned, Length=2)
					apci[7] = command;
					apci[8] = *(byte*)&arg;
					apci[9] = BACnetDataExpectingReply;
					length_apci = 10;
					networklayer( N_UNITDATArequest, NORMALmessage, network, destination, source, NULL, 0, apci, length_apci, BACnetDataExpectingReply);
					laststate = CTSM_AWAIT_CONFIRMATION;
					win_size = 0;
				 }
				 ptable->CTSM_State=CTSM_AE_SEGMENTED_CONFIRMATION;
				}
/*
				if(segmentation is to be done by AP)
				{
				 send CONF_SERV.cnf(+) with more_follows = TRUE
				 CTSM_State=CTSM_AP_SEGMENTED_CONFIRMATION;
				}
*/
				if( flowcontrol == APFLOWCONTROL )
				{
				 if(data)
				 {
					memcpy(data, &ptable->data[sa], ptable->LengthReceivedClientAPDU - sa);
					*data_length += ptable->LengthReceivedClientAPDU-sa;
				 }
				 ptable->CTSM_State=CTSM_AE_SEGMENTED_CONFIRMATION;
				 next = 0;
				}
				break;
			 }
			 else
			 {
/*        check vendorID and command from asdu respons
					0x21;            // Application Tag 2( Unsigned, Length=1)
					PTRtable->vendorID;
					0x21;            // Application Tag 2( Unsigned, Length=1)
					PTRtable->command;
*/
//      READPROGRAMCODE_T3000 : 4 byte : 2 bytes - programs pool, 2 bytes - programs pool used
//      READGROUPELEMENTS_T3000 4 byte : 2 bytes - max_elements, 2 bytes - cur_elements
				 if( command == READPROGRAMCODE_T3000 || command == READGROUPELEMENTS_T3000 )
				 {
					if( returnargs )
						memcpy(returnargs, &ptable->data[sa], 4);
					sa += 4;
				 }
				 ptable->LengthReceivedClientAPDU -= sa;
/*  no compression for the moment
					if( (PTRReceivedClientAPDU[3]&0x01) )     //compressed?
					{
					memcpy(&n, PTRReceivedClientAPDU+4, 2);
					LengthReceivedClientAPDU -= 2;
					LengthReceivedClientAPDU=uncompress(data, n,  PTRReceivedClientAPDU+6, LengthReceivedClientAPDU);
					}
					else
*/
				 {
					if(data)
						memcpy(data, &ptable->data[sa], ptable->LengthReceivedClientAPDU);
					}
					*data_length += ptable->LengthReceivedClientAPDU;
//					CTSM_State=CTSM_IDLE;
					next=0;
					break;
				 }
				}
				}
			 }
			}
/*
			if (CTSM_Event == ErrorPDU)
			{
				send CONF_SERV.cnf(-)
				CTSM_State=CTSM_IDLE;
				next=0;
			}
*/
/*
			if (CTSM_Event == RejectPDU with server=TRUE)
			{
				send REJECT.indication
				CTSM_State=CTSM_IDLE;
			  next=0;
			}
*/
/*
			if (CTSM_Event == AbortPDU with server=TRUE)
			{
			  send ABORT.indication
			  CTSM_State=CTSM_IDLE;
			  next=0;
			}
*/
			if (PDUtype == BACnetAbortPDU && srv)
			{
			 error = RS232_ERROR;
			 next=0;
			 break;
			}
/*
			if (CTSM_Event == Unexpected PDU from server)
			{
				send AbortPDU with server=FALSE
			  CTSM_State=CTSM_IDLE;
			  next=0;
			}
*/
/*
		 if (timeout waiting for PDU)
		 {
			if(retry count not exceed and
				APDU > max_APDU_length_supported)
			{
				 send Conf_Req PDU with
					  segmented_msg = TRUE
						more_follows = TRUE
				 CTSM_State=CTSM_SEGMENTING_REQUEST;
			  }
			if(retry count not exceed and
				APDU <= max_APDU_length_supported)
			{
				 send Conf_Req PDU with
					  segmented_msg = FALSE
			  }
			if(retry count exceeded)
			{
				send CONF_SERV.confirm(-)
				 CTSM_State=CTSM_IDLE;
			 next=0;
			}
		 }
*/
/*
			if (Event == ABORT.request)
			{
//         send Abort PDU with server = FALSE
				CTSM_State=CTSM_IDLE;
				next=0;
			}
*/
//			CTSM_State=CTSM_IDLE;
			error = RS232_ERROR;
			next=0;
			break;
	 case CTSM_AE_SEGMENTED_CONFIRMATION:

			error = RS232_ERROR;
			if( ptable->task  >= 0 )
			{
				 if( !ptable->state )
					 msleep((int)(((int)(timeout))*18));  //18.2
			}
			else
			{
				tasks[tswitch].delay_time = timeout*1000L;
				while ( !ptable->state && tasks[tswitch].delay_time>=0 )
				{
				 if( bioskey_new(1) == CTRLBREAK )
				  if( (others&NETCALL_NOTCTRLBREAK)!=NETCALL_NOTCTRLBREAK )
					{
					 error = USER_ABORT;
					 break;
				  }
				}
			}
			if( ptable->state )
			{
				invokeid = ptable->data[1];
//				if( invokeid==invokeID )
//				{
				PDUtype  = ptable->data[0]>>4;
				srv      = (ptable->data[0]&0x01)&&1;
				memcpy(apci, ptable->data, MAXAPCI);
				error = RS232_SUCCESS;
//				}
			}
			if(error!=SUCCESS)		//timeout
			{
			 apci[0] = (BACnetAbortPDU<<4);   //server=FALSE
			 apci[1] = invokeID;
			 apci[2] = 0;           //other reasons
			 length_apci = 3;
			 if(destination!=255)
				 networklayer( N_UNITDATArequest, NORMALmessage, network, destination, source, NULL, 0, apci, length_apci, BACnetDataNotExpectingReply);
//			 CTSM_State=CTSM_IDLE;
			 next=0;
			 break;
			}
/*
			if (CTSM_Event == Complex_ACK PDU with segmented_msg = TRUE
																more_follows = TRUE )
			{
				 send SegmentACK PDU with server = FALSE
				 if(buffer full or other reasons)
				 {
					send Abort PDU with server=FALSE
					send CONF_SERV.cnf(-)
					CTSM_State=CTSM_IDLE;
					next=0;
				 }
			}
			if (CTSM_Event == Complex_ACK PDU with segmented_msg = TRUE
																more_follows = FALSE )
			{
				send SegmentACK PDU with server = FALSE
				send CONF_SERV.cnf(+)
				CTSM_State=CTSM_IDLE;
				next=0;
			}
*/
			if (PDUtype == BACnetComplexACKPDU)
			{
			 seg = (apci[0] & 0x08)&&1;
			 mor = (apci[0] & 0x04)&&1;
//			 invokeid = apci[1];
			 if(seg)
			 {
//			  if( apci[2] < nosequence-(win_size?win_size-1:windowsize-1) || apci[2] > nosequence+windowsize-win_size)
				if( apci[2] < nosequence-(win_size?win_size-1:windowsize-1) || apci[2] > nosequence+1)
				{      //error
				 ptable->state = 0;
				 break;
//				 CTSM_State=CTSM_IDLE;
//				 error = RS232_ERROR;
//				 next=0;
//				 break;
				}
				if( apci[2] == nosequence-(win_size?win_size-1:windowsize-1 ) )   // server resent last segment
				{
				 if(data)
					data -= last_length;
				 *data_length -= last_length;
				 last_length = 0;
				 win_size = 0;
				}
				if( apci[2] == nosequence+1 && !win_size ) // next segment
				 last_length = 0;

				nosequence = apci[2];
				windowsize = apci[3];
				service = apci[4];
				sa=5;
			 }
			 else
			 {
				service = apci[2];
				sa = 3;
			 }
/*
				application octet string
				have to check vendorID and command from asdu respons
					0x21;            // Application Tag 2( Unsigned, Length=1)
					PTRtable->vendorID;
					0x21;            // Application Tag 2( Unsigned, Length=1)
					PTRtable->command;
*/
			 if (service==Service)
			 {
				sa += decodetag(&apci[sa], &n);  //vendorid
				if( vendorID == apci[sa] )
				{
				 sa += n;
				 sa += decodetag(&apci[sa], &n);  //service
				 if( (command == apci[sa]) && ( command!=50 || (command==50 &&  *(byte*)&arg==apci[sa+1])) )
				 {
					sa += n;
					sa += decodetag(&apci[sa], (unsigned *)&last_length);   //asdu length
					if(seg && nosequence==1)   // resent first segment
					{
//      2 bytes - total length of response data
					 data_length_pack = *((unsigned int *)(&ptable->data[sa]));
					 sa += 2;
//      READPROGRAMCODE_T3000 : 4 byte : 2 bytes - programs pool, 2 bytes - programs pool used
//      READGROUPELEMENTS_T3000 4 byte : 2 bytes - max_elements, 2 bytes - cur_elements
					 if( command == READPROGRAMCODE_T3000 || command == READGROUPELEMENTS_T3000 )
					 {
						if( returnargs )
							memcpy(returnargs, &ptable->data[sa], 4);
						sa += 4;
					 }
					}
					ptable->LengthReceivedClientAPDU -= sa;
					if(data)
					{
					 if(!compressed)
					 {
						memcpy(data, &ptable->data[sa], ptable->LengthReceivedClientAPDU);
					 }
					 else
						ptable->LengthReceivedClientAPDU=uncompress(data, data_length_pack-(*data_length),  &ptable->data[sa], ptable->LengthReceivedClientAPDU);
					 data += ptable->LengthReceivedClientAPDU;
					 last_length = ptable->LengthReceivedClientAPDU;
					 *data_length += ptable->LengthReceivedClientAPDU;

					 if(ptable->others&NETCALL_SIGN) communication_sign(data_const+(*data_length),data_length_const?data_length_const:data_length_pack);
					}
					if( seg==TRUE )
					{
					 ptable->state = 0;
					 if( ++win_size >= windowsize )
					 {
						apci[0] = (BACnetSegmentACKPDU<<4);
						apci[1] = invokeID;
						apci[2] = nosequence;
						apci[3] = WINDOWSIZE;
						apci[4] = 0x09;            // Context Tag 0( Unsigned, Length=1)
						apci[5] = vendorID;
						apci[6] = 0x1A;            // Context Tag 1( Unsigned, Length=2)
						apci[7] = command;
						apci[8] = *(byte*)&arg;
// Added February 14, for router reason, to detect if the
// request is NotExpected reply
						apci[9] =  BACnetDataExpectingReply;
						if( mor==FALSE )
							apci[9] = BACnetDataNotExpectingReply;
						length_apci = 10;
						networklayer( N_UNITDATArequest, NORMALmessage, network, destination, source, NULL, 0, apci, length_apci, mor==TRUE?BACnetDataExpectingReply:BACnetDataNotExpectingReply);
						win_size = 0;
					 }
					}
					if(mor==FALSE)
					{
					 ptable->CTSM_State=CTSM_IDLE;
					 next=0;
					}
				 }
				 else
				 {
					ptable->CTSM_State=CTSM_IDLE;
					error = RS232_ERROR;
					next=0;
				 }
				}
				else
				{
				 ptable->CTSM_State=CTSM_IDLE;
				 error = RS232_ERROR;
				 next=0;
				}
			 }
			 else
			 {
				ptable->CTSM_State=CTSM_IDLE;
				error = RS232_ERROR;
				next=0;
			 }
			 break;
			}
			if (PDUtype == BACnetAbortPDU && srv)
			{
//			 CTSM_State=CTSM_IDLE;
			 error = RS232_ERROR;
			 next=0;
			 break;
			}
/*
			if (CTSM_Event == AbortPDU with server==TRUE)
			{
//         send ABORT.indication
				CTSM_State=CTSM_IDLE;
				next=0;
			}
			if (unexpected PDU from server)
			{
//         send Abort PDU with server = FALSE
				CTSM_State=CTSM_IDLE;
				next=0;
			}
//       if (timeout waiting for PDU)
//       {
//           send CONF_SERV.confirm(-)
//			    CTSM_State=CTSM_IDLE;
// 			 next=0;
//       }
			if (Event == ABORT.request)
			{
//         send Abort PDU with server = FALSE
				CTSM_State=CTSM_IDLE;
				next=0;
			}
*/
//			 CTSM_State=CTSM_IDLE;
			 error = RS232_ERROR;
			 next=0;
			 break;
	} // end switch
 }  // end while
// ClientSA = 0;
// ClientDA = 0;
 ClientTSMTable.free(current);
 return error;
}

//char xxxx[10],gg=22;
int buildservice(char *asdu, unsigned *length_asdu, int entryServerTSMTable)
{
 struct TSMTable *ptrtable;
 int l;
 ptrtable = &ServerTSMTable.table[entryServerTSMTable];
 if( ptrtable->length > MAXASDUSIZE )
 {
	l = MAXASDUSIZE/ptrtable->entitysize;
	*length_asdu = l*ptrtable->entitysize;
 }
 else
 {
	*length_asdu = ptrtable->length;
 }
 l = *length_asdu;
 if( !ptrtable->compressed )
	 memcpy(asdu, ptrtable->data,*length_asdu );
 else
	 *length_asdu = compressdata(asdu, *length_asdu, ptrtable->data, ptrtable->length, &l);
 ptrtable->data += l;
 ptrtable->last_length += l;
 ptrtable->length -= l;
}

int execservice(char *asdu, unsigned *length_asdu, int entryServerTSMTable)
{
 struct TSMTable *ptrtable;
 unsigned int l;
 ptrtable = &ServerTSMTable.table[entryServerTSMTable];
 memcpy(ptrtable->data,asdu,*length_asdu);
 ptrtable->data += *length_asdu;
 ptrtable->last_length += *length_asdu;
 ptrtable->length += *length_asdu;
}

/*
void pex1(struct TSMTable *PTRtable, int port)
{
  ((Serial *)Routing_table[port].ptr)->length_in = PTRtable->length;
  ((Serial *)Routing_table[port].ptr)->RIB_in[2] = PTRtable->command;
	memcpy(&((Serial *)Routing_table[port].ptr)->RIB_in[3], &PTRtable->arg, 2);
}
*/

/*
void pex1(struct TSMTable *PTRtable)
{
	ser_rs485->length_in = PTRtable->length;
	ser_rs485->RIB_in[2] = PTRtable->command;
	memcpy(&ser_rs485->RIB_in[3], &PTRtable->arg, 2);
}
*/
int serverBACnet(int port, ServicePrimitive event, char service, char *asdu, int length_asdu, int entryServerTSMTable, int *ind=NULL, int destport=-1)
{
 BACnetObjectIdentifier obj;
 T3000PropertyIdentifier property;
 uint i;
 long lval;

 if( service==WriteProperty )
 {
//	buf[0] = 0x0B;           //Context Tag 0(L=3)
	memcpy(&obj, asdu+1, 3);
//	buf[4] = 0x1A;           //Context Tag 1(L=2)
	memcpy(&property, asdu+5, 2);
//	buf[7] = 0x3E;           //Opening Tag 3
	i = 8;
	switch( property ){
	 case property_value:
//			buf[l++] = 0x34;       //Application Tag 3(L=4)
			i++;
			lval = ((long)(*(asdu+i)))<<24;
			i++;
			lval += ((long)(*(asdu+i)))<<16;
			i++;
			lval += ((long)(*(asdu+i)))<<8;
			i++;
			lval += *(asdu+i);
			i++;
			writepropertyvalue(obj, lval);
			break;
	 case property_auto_manual:
//			buf[l++] = 0x31;       //Application Tag 3(L=1)
			i++;
			lval = *(asdu+i);
			i++;
			writepropertyauto(obj, lval);
			break;
	 case property_state:
//			buf[l++] = 0x31;       //Application Tag 3(L=1)
			i++;
			lval = *(asdu+i);
			i++;
			writepropertystate(obj, lval,1);
			break;
	}
//	buf[l++] = 0x3F;           //Closing Tag 3
 }
}

int serverprocedure( int port, ServicePrimitive event, char *asdu, int length_asdu, int entryServerTSMTable, int *ind=NULL, int destport=-1)
{
 byte comm_code, ex_high;
 unsigned int bank, n, ret, i, j;
 char res,*ptr, extralow, extrahigh, comm_type;
// unsigned int length;
 long t;
 Bank_Type tbank;
 int vendorID;
 struct TSMTable *ptrtable;
// Serial *sptr;
 class ConnectionData *cdata;
 void *pobj;
 pobj = Routing_table[port].ptr;

/*
 if( (Routing_table[port].status&PTP_INSTALLED)==PTP_INSTALLED )
	 sptr = (class PTP *)Routing_table[port].ptr;
 else
	 sptr = (class MSTP *)Routing_table[port].ptr;
*/
 cdata = (class ConnectionData *)Routing_table[port].ptr;

 ptrtable = &ServerTSMTable.table[entryServerTSMTable];
// ptrtable->service = service;

 n = 0;
 if( ind )
  *ind = -1;     //read command
 comm_type = 0;  // read command
 if( ptrtable->service==ConfirmedPrivateTransfer || ptrtable->service==UnconfirmedPrivateTransfer )
 {
			n += decodetag(&asdu[0], &i);  //vendorid
//		  memcpy(&vendorID, &asdu[n], sizeof(vendorID));
			vendorID = asdu[n];
			n += i;
			n += decodetag(&asdu[n], &i);  //service
			comm_code =asdu[n];
			if( comm_code==50 || comm_code==50+100)
			{
			 bank = *(unsigned char*)(&asdu[n+1]);
			 extralow  = bank;
			}
			ptrtable->command = comm_code;
			ptrtable->vendorID = vendorID;
 // parameters
			n += i;
			n += decodetag(&asdu[n], &j);   //asdu length
			if( comm_code!=50 && comm_code!=50+100)
			{
			 bank = *(unsigned int*)(&asdu[n]);
			 tbank = *(Bank_Type *)(&bank);
			 extralow  = asdu[n];
			 extrahigh = asdu[n+1];
			}
			else
			 extrahigh = asdu[n];
			res = asdu[n+2];
			memcpy(&ptrtable->arg, &bank, 2);
			ptrtable->res=res;
//		  ptrtable->compressed = res&0x01;      //now without compression
 // end parameters
			if(comm_code > 100)
			{
			 comm_type = 1;  // write command
			 comm_code -= 100;
			 if( ind )
			 {
				*ind = n + 3;  // 3 = arg, command
			 }
			}
			asdu += n+3;       // 3 = arg, command
			n += 3;
 }
 if( event==CONF_SERVindication )
 {
	switch (ptrtable->service) {
	 case ConfirmedPrivateTransfer:
			if( !comm_type )   // read request
			{
			 length_asdu -= n;
			 memcpy(ptrtable->read_data, &length_asdu, 2);
			 memcpy(((char*)(ptrtable->read_data))+2, asdu, length_asdu);
			 if(comm_code == COMMAND_50 && ( bank == 40 || bank == 41 || bank == 42  || bank == 47 || bank == 48) )
			 {
				ptrtable->data = cdata->ser_data;
				ptrtable->length = 0;
				ptrtable->timeout = 500;
				STSMtable_ptr_files = ptrtable;
				STSMtable_ptr_files_port = port;
				readfiles_flag=1;
				action=1;
				if( tasks[MISCELLANEOUS].status == SUSPENDED )
					resume(MISCELLANEOUS);
				return ReplyPostponed;
			 }
			 if(comm_code == READMONITORDATA_T3000)
			 {
				if( readmon_flag )
				{
					return REJECTrequest;
				}
				ptrtable->data = cdata->ser_data;
				ptrtable->length = 0;
				ptrtable->timeout = 800;
				STSMtable_ptr_readmon = ptrtable;
				STSMtable_ptr_readmon_port = port;
				readmon_flag=1;
				action=1;
				if( tasks[MISCELLANEOUS].status == SUSPENDED )
					resume(MISCELLANEOUS);
				return ReplyPostponed;
			 }
			 i=execute_command( cdata->media, SEND, pobj, cdata->ser_data, ptrtable,destport);
			 if (i)
			 {
				return REJECTrequest;
			 }
			}
			break;
	}
	return CONF_SERVresponse;
 }
 if( event==UNCONF_SERVindication )
 {
	switch (ptrtable->service) {
	 case UnconfirmedPrivateTransfer:
			switch( comm_code ) {
			 case 50:
				ptrtable->command = 0;   //not write obisnuit
				cdata = (class ConnectionData *)Routing_table[port].ptr;
				if ( extralow==70 )
				{
/*
					if( extrahigh&0x10 )
					{
					memcpy(&n, asdu, 2);
//***					if(!station_list[n-1].state)
					if(!cdata->station_list[n-1].state)
					{
//***					  station_list[n-1].state = 1;
						cdata->station_list[n-1].state = 1;
						cdata->panel_info1.active_panels |= (1<<(n-1));
					}
//***					strcpy( station_list[n-1].name, &asdu[2] );
					strcpy( cdata->station_list[n-1].name, &asdu[2] );
					}
					else
*/
					i=0;
					j = n;     // nr bytes received
					if( extrahigh&0x01==ON )
					{
					 memcpy(&n, asdu, 2);
					 i+=2;
//					 if( !(cdata->panel_info1.active_panels&(1l<<(n-1))) )
					 if( n < 1 || n>32 ) break;
					 if( n!=Station_NUM )
					 {
						if( !(cdata->need_info&(1l<<(n-1))) )
						{
						 cdata->need_info |= (1l<<(n-1));
						 cdata->laststation_connected = 3;
						 cdata->station_list[n-1].state = 1;
						 cdata->panel_info1.active_panels |= (1l<<(n-1));
						 cdata->send_info = 3;
						 new_alarm_flag |= 0x04;
						 resume(ALARMTASK);
						}
						memcpy( cdata->station_list[n-1].name, &asdu[2], sizeof(Station_NAME));
						i+=sizeof(Station_NAME);
						memcpy(&cdata->station_list[n-1].des_length, &asdu[2+sizeof(Station_NAME)], 2);
						i+=2;
					 }
					 else
						i+=sizeof(Station_NAME)+2;
//  Aug 29, 1997  ->
					 if( ((extrahigh==0x01)&&(length_asdu>31)) ||
								((extrahigh&0x02)&&(length_asdu>(31+sizeof(Time_block)))) ||
								(extrahigh&0x08)
							)
					 {
						if( n!=Station_NUM )
						{
						 cdata->station_list[n-1].panel_type=asdu[i++];
						 memcpy(&cdata->station_list[n-1].version, &asdu[i], 2);
						 i+=2;
						 memcpy(cdata->station_list[n-1].tbl_bank, &asdu[i], sizeof(ptr_panel->table_bank));
						 i += sizeof(ptr_panel->table_bank);
						}
						else
						 i+=1+2+sizeof(ptr_panel->table_bank);
					 }
					 else
							cdata->panelconnected = 2;
//  Aug 29, 1997  <-
					}
					if(extrahigh&0x02)
					{
						if( !(extrahigh&0x01) )
						{
						 memcpy(&n, asdu, 2);
									 i+=2;
						}
						if( (t=mktime((struct tm *)&asdu[i]))!=-1)
						{
						 disable();
						 stime((time_t *)&t);
//						 memcpy(&ora_current, &asdu[i], sizeof(Time_block));
						 updatetimevars();
						 enable();
						 i += sizeof(Time_block);
						}
					}
					if(extrahigh&0x08)
					{
//  Aug 29, 1997  ->
						 memcpy(&n, &asdu[i], 2);
						 i+=2;
					   if( n < 1 || n>32 ) break;
						 if( n==TS )
						 {
							if( iamnewonnet )
							{
							 memcpy((char*)ptr_panel->system_name, &asdu[i], 22);
							 i += 22;
							 memcpy( (char*)&cdata->panel_info1.network, &asdu[i], 2);
							 i += 2;
							 memcpy( (char*)cdata->panel_info1.network_name, &asdu[i], NAME_SIZE);
							 i += NAME_SIZE;
							 cdata->panelconnected = 1;
              }
						 }
//  Aug 29, 1997  <-
					}
					if(extrahigh&0x04)
					{
						if( !(ready_for_descriptors&0x04) )
						{
						ready_for_descriptors = 1;
						action=1;
						if( tasks[MISCELLANEOUS].status == SUSPENDED )
						 resume(MISCELLANEOUS);
						}
						else
						{
						ready_for_descriptors = 0;
						}
					}
//					if( !(extrahigh&0x01)  )     // panel OFF
					if( !extrahigh )     // panel OFF
					{
/*
if(!a4)
if (mode_text)
{
 mxyputs(2,4,"                         ");
 mxyputs(2,4,itoa(xvar++, xbuf,10));
 mxyputs(10,4,"Receive panel OFF");
 a4=1;
}
*/
					 memcpy(&n, asdu, 2);
					 if( n < 1 || n>32 ) break;
					 if( n == Station_NUM )
					 {
						((MSTP *)Routing_table[port].ptr)->FirstToken = 0;
					 }
					 else
					 {
						cdata->station_list[n-1].state = 0;
						cdata->station_list[n-1].des_length = 0;
						cdata->station_list[n-1].panel_type = 0;
						cdata->station_list[n-1].version=0;
						cdata->panel_info1.active_panels &= ~(1l<<(n-1));
						cdata->need_info &= ~(1l<<(n-1));
					 }
					 ready_for_descriptors = 0;
					}
					if( extrahigh&0x10 )
					{ // received I want to connect to net
						 memcpy(&n, &asdu[i], 2);
						 if( n < 1 || n>32 ) break;
						 i+=2;
						 if( n==Station_NUM && !iamnewonnet )

						 {
							 cdata->newpanelbehind = n;
						 }
					}
					if( extrahigh&0x20 )
					{ // received I am on net (conflict)
						 memcpy(&n, &asdu[i], 2);
						 if( n < 1 || n>32 ) break;
						 i+=2;
						 if( n==Station_NUM )
						 {
							 if( iamnewonnet )
								cdata->panelconnected = n;
						 }
					}
					if( (extrahigh&0x01)==ON )
					{
				 // send only if ON
/*
						rr1++;
						sprintf( rrr_buf, "%d", rr1 );
						mxyputs(10,10,"NU_request_70");
						mxyputs(30,10,rrr_buf );
*/
						router(N_UNITDATArequest, I_Am_Router_To_Network_Prop, NULL, port);
					}
				}
				if ( extralow==SEND_WANTPOINTS_COMMAND || extralow==SEND_NETWORKPOINTS_COMMAND )
				{
				 if( length_asdu-n > 0 )
				 {
					// received a list the points requested be other panels
					if(extralow==SEND_WANTPOINTS_COMMAND) //get want points
					{
					 Point_Net *wantpoints;
					 memcpy(&n, asdu, 2);
					 n /= sizeof(Point_Net);
					 wantpoints = (Point_Net *)(asdu+2);
//					 if(wantpointsentry!=2)
						for(int i=0; i<n && i<MAXREMOTEPOINTS82 ; i++, wantpoints++)
						{
						 if( wantpoints->network == cdata->panel_info1.network )
						 {
							if( wantpoints->panel+1 == cdata->panel_info1.panel_number )
							{
//							wantpointsentry=1;
							 for(j=0; j<MAXNETWORKPOINTS; j++)
							 {
								if(*wantpoints==network_points_list[j].info.point) break;
							 }
							 if( j>=MAXNETWORKPOINTS )
							 {
								for(j=0; j<MAXNETWORKPOINTS; j++)
								{
								 if(!network_points_list[j].info.point.point_type)
								 {
									network_points_list[j].info.point = *wantpoints;
									wantpointsentry++;
									break;
								 }
								}
							 }
							}
						 }
						 else
						 {
							if( rs485port!=-1 && ipxport!=-1 )
							{
							 for(j=0; j<MAXREMOTEPOINTS82; j++)
							 {
								if(*wantpoints==request_router_points_list[j]) break;
							 }
							 if( j>=MAXREMOTEPOINTS82 )
							 {
								for(j=0; j<MAXREMOTEPOINTS82; j++)
								{
								 if(!request_router_points_list[j].point_type)
								 {
									request_router_points_list[j] = *wantpoints;
									wantpointsentry_router++;
									break;
								 }
								}
							 }
							}
						 }
						}
					}
					// resceived response from the panels
					if(extralow==SEND_NETWORKPOINTS_COMMAND)
					{
					 NETWORK_POINTS	*networkpoints, pinfo;
					 Point_info	 	*info;
					 int net, net1;
					 char panel, des_label;
					 net1 = cdata->panel_info1.network;
					 memcpy(&net, asdu, 2);
					 asdu += 2;
					 panel = *asdu++;
					 memcpy(&n, asdu, 2);
					 n /= sizeof(NETWORK_POINTS);
					 networkpoints = (NETWORK_POINTS	*)(asdu+2);
					 for(i=0; i<n && i<MAXNETWORKPOINTS; i++, networkpoints++)
					 {
						memcpy(&pinfo,networkpoints,sizeof(NETWORK_POINTS));
						if(rs485port==port)
						{
								pinfo.info.point.network = 0xFFFF;
						}
						else
						 if(ipxport==port)
						 {
							if(rs485port==-1)
							{
								 pinfo.info.point.network = 0xFFFF;
							}
						 }

						for(j=0; j<MAXREMOTEPOINTS82; j++)
						{
						 info = &remote_points_list[j].info;
						 if( networkpoints->info.point.point_type )
							if( networkpoints->info.point==info->point ||
									pinfo.info.point==info->point )
							{
							 des_label = info->description_label;
							 net       = info->point.network;
//							memcpy((void *)&remote_points_list[j].info, (void *)&networkpoints->info, sizeof(Point_info));
							 memcpy((void *)info, (void *)&pinfo.info, sizeof(Point_info));
							 info->description_label = des_label;
							 info->point.network = net;
//							break;
							}
						 if( rs485port!=-1 && ipxport!=-1 )
						 {
							 for(int k=0; k<MAXNETWORKPOINTS; k++)
							 {
								if( networkpoints->info.point==response_router_points_list[k].info.point ) break;
							 }
							 if( k>=MAXNETWORKPOINTS )
							 {
								for(k=0; k<MAXNETWORKPOINTS; k++)
								{
								 if(!response_router_points_list[k].info.point.point_type)
								 {
									memcpy((void *)&response_router_points_list[k], (void *)networkpoints, sizeof(NETWORK_POINTS));
  								break;
								 }
								}
							 }
						 }
						}

					 }
					}
				 }
				}
				if ( extralow==ALARM_NOTIFY_COMMAND )
				{
					gAlarm = 1;
				}
				if ( extralow==SEND_INFO_COMMAND )
				{
					if(extrahigh==SENDINFO_IAMPANELOFF)
					{
					 memcpy(&n, asdu, 2);        // panel# that is OFF
//					 cdata->panelOff = n;
					 if( n == Station_NUM )
					 {
						((MSTP *)Routing_table[port].ptr)->FirstToken = 0;
					 }
					 else
					 {
						cdata->station_list[n-1].state = 0;
						cdata->station_list[n-1].des_length = 0;
						cdata->station_list[n-1].panel_type = 0;
						cdata->station_list[n-1].version=0;
						cdata->panel_info1.active_panels &= ~(1l<<(n-1));
						cdata->need_info &= ~(1l<<(n-1));
						memset(cdata->station_list[n-1].name, ' ', sizeof(Station_NAME)-1);
						memset(cdata->station_list[n-1].tbl_bank,0,sizeof(ptr_panel->table_bank));

						if( ((MSTP *)Routing_table[port].ptr)->NS == n )
						{
						 memcpy(&i, asdu+4, 2);        // the next panel# for the panel# that is the OFF
						 ((MSTP *)Routing_table[port].ptr)->NS = i;    // reset the NS
						}
						if( ((MSTP *)Routing_table[port].ptr)->OS == n ) // change OS?
						{
						 memcpy(&i, asdu+2, 2);        // the originate panel# for the panel# that is the OFF
						 ((MSTP *)Routing_table[port].ptr)->OS = i;
						}
					 }
					}
				}
				break;
			 case SEND_ALARM_COMMAND:
				return 2;
			 case 20:
				ptrtable->length = length_asdu - n;
				return 2;
			}
			break;
	}
	return 1;
 }
}

//void ServerTransactionStateMachine(
//		 int network, int destination, int source, char *apdu, int length_apdu, int entrytimeout=-1)
void ServerTransactionStateMachine( int port, int network, int destination,
																		int source, char *apdu, int length_apdu,
																		int entrytimeout=-1, int destport=-1 )
{
 char apci[MAXAPCI];
 char s1,s,next,win_size, postponed;
 char *asdu;
 int  n, length_apci, current, STSM_Event, STSM_PDUtype;
 unsigned length_asdu, l;
 char STSM_SEG, STSM_MOR, STSM_SA, STSM_MaxResp, STSM_InvokeID;
 char STSM_NoSeq=1, STSM_WinSize, STSM_Service, STSM_SRV, STSM_REASON;
 signed char STSM_State;
 struct TSMTable *PTRtable;
// Serial *sptr;
class ConnectionData *cdata;
 void *pobj;
 pobj = Routing_table[port].ptr;
/*
 if( (Routing_table[port].status&PTP_INSTALLED)==PTP_INSTALLED )
	 sptr = (class PTP *)Routing_table[port].ptr;
 else
	 sptr = (class MSTP *)Routing_table[port].ptr;
*/
 cdata = (class ConnectionData *)Routing_table[port].ptr;

postponed=0;
if(entrytimeout<0)
 {
	if( STSMremoveflag ) return;
	STSM_Event = apdu[0]>>4;
	switch ( STSM_Event ) {
	  case BACnetUnconfirmedRequestPDU:
			 STSM_Service = apdu[1];
			 STSM_InvokeID = 255;
			 n=2;
			 break;
	  case BACnetConfirmedRequestPDU:
			 STSM_SEG      = (apdu[0]&0x08)&&1;
			 STSM_MOR      = (apdu[0]&0x04)&&1;
			 STSM_SA       = (apdu[0]&0x02)&&1;
			 STSM_MaxResp  = apdu[1];
			 STSM_InvokeID = apdu[2];
			 if( STSM_SEG )  STSM_NoSeq   = apdu[3];
			 if( STSM_SEG )  STSM_WinSize = apdu[4];
			 if( STSM_SEG ) {STSM_Service = apdu[5]; n=6;}
			 else           {STSM_Service = apdu[3]; n=4;};
			 break;
	  case BACnetSegmentACKPDU:
			 STSM_SRV      = (apdu[0]&0x01)&&1;
			 STSM_InvokeID = apdu[1];
			 STSM_NoSeq    = apdu[2];
			 STSM_WinSize  = apdu[3];
			 n=4;
			 if( STSM_SRV == TRUE )
			 {
//			  LengthReceivedClientAPDU = length_apdu;
//				PTRReceivedClientAPDU = apdu;
				ClientTSMTable.received(destination, source, apdu, length_apdu);
				return;
			 }
			 break;
		case BACnetAbortPDU:
			 STSM_SRV      = (apdu[0]&0x01)&&1;
			 STSM_InvokeID = apdu[1];
			 STSM_REASON   = apdu[2];
			 n =3;
			 break;
		default:
			 ClientTSMTable.received(destination, source, apdu, length_apdu);
/*
			 if(destination==ClientSA && source==ClientDA)
			 {
				memcpy(ClientBuffer, apdu, length_apdu);
				LengthReceivedClientAPDU = length_apdu;
				PTRReceivedClientAPDU = ClientBuffer;
			 }
*/
			 return;
  }
  asdu = &apdu[n];
  length_asdu = length_apdu-n;

  if ((current=ServerTSMTable.lookid(network, destination, source, STSM_Service, STSM_InvokeID, &cdata->ser_pool)) == STSM_ILLEGAL)
	{
	return;   //reject PDU
  }
  if ( ServerTSM_flag == current )
  {
	 return;
  }
 }
 else
 {
//  STSMremoveflag=1;
	current = entrytimeout;
	asdu = apdu;
 }
 ServerTSM_flag = current;
 PTRtable = &ServerTSMTable.table[current];
 if(entrytimeout>=0)
 {
  network = PTRtable->network;
  destination = PTRtable->destination;
  source = PTRtable->source;
 }
 if( PTRtable->state >= 16 )
 {
	if( PTRtable->state >= 32 )
	{
xxxx++;
	 PTRtable->state -= 32;
	 entrytimeout=-1;
	 postponed=1;
	 STSM_Event = CONF_SERVresponse;
	 s1=STSM_IDLE;
	}
	else
	{
	 PTRtable->state = STSM_IDLE;
	}
	STSM_Service = ConfirmedPrivateTransfer;
 }
 STSM_State = PTRtable->state;
 STSM_InvokeID = PTRtable->invokeID;
 next=1;
 while(next)
 {
  switch ( STSM_State ){
	 case STSM_IDLE:
			if	(PTRtable->timeout<=0 && entrytimeout>=0	)
			{     //something wrong
				ServerTSMTable.free(current);
				STSM_State=STSM_IDLE;
				next=0;
				reject = 0;
				break;
			}
/*
			if (Event == Abort PDU)
			{
				discard PDU
				STSM_State=STSM_IDLE;
			}
*/
			if (STSM_Event ==  BACnetAbortPDU)
			{
			 ServerTSMTable.free(current);
			 STSM_State=STSM_IDLE;
			 reject = 0;
			 next = 0;
			 break;
			}

/*
			if (STSM_Event == BACnetUnconfirmedRequestPDU)
			{
				send UNCONF_SERV.indication
				STSM_State=STSM_IDLE;
				next=0;
			}
*/
			if (STSM_Event == BACnetUnconfirmedRequestPDU)
			{
			 if( STSM_Service==ConfirmedPrivateTransfer || STSM_Service==UnconfirmedPrivateTransfer )
			 {
				if( serverprocedure( port, UNCONF_SERVindication, asdu, length_asdu, current, &n, destport)==2 )
				{
				 if( n >= 0 )
				 {    				 //writing
					asdu += n;
					length_asdu -= n;
					execute_command( cdata->media, TRANSFER_DATA,  pobj,
							asdu, PTRtable, destport);
				 }
				}
			 }
			 ServerTSMTable.free(  current);
			 next=0;
			 break;
			}
/*
			if (STSM_Event == Conf_ReqPDU && with segmented_msg=FALSE)
			{
				send CONF_SERV.indication
				STSM_State=STSM_AWAIT_RESPONSE;
			}
*/
/*			 if (STSM_Event == BACnetConfirmedRequestPDU && reject)
			 {
			  apci[0] = (BACnetRejectPDU<<4);
			  apci[1] = STSM_InvokeID;
			  apci[2] = 0;
			  length_apci = 3;
			  networklayer( N_UNITDATArequest, NORMALmessage, network, source, destination, NULL, 0, apci, length_apci, BACnetDataNotExpectingReply);
			  ServerTSMTable.free(current);
			  next=0;
			  break;
			}
*/
			if (STSM_Event == BACnetConfirmedRequestPDU && STSM_SEG == FALSE)
			{
			 if( STSM_Service==ConfirmedPrivateTransfer )
			 {
				STSM_Event = serverprocedure( port, CONF_SERVindication, asdu, length_asdu, current, &n, destport);
				if(STSM_Event == REJECTrequest)
				{
				 apci[0] = (BACnetRejectPDU<<4);
				 apci[1] = STSM_InvokeID;
				 apci[2] = 0;
				 length_apci = 3;
				 networklayer( N_UNITDATArequest, NORMALmessage, network, source, destination, NULL, 0, apci, length_apci, BACnetDataNotExpectingReply);
				 ServerTSMTable.free(  current);
				 next=0;
				 break;
				}
				if(STSM_Event == ReplyPostponed)
				{
				 length_apci = 0;
				 if( (Routing_table[port].status&RS485_ACTIVE)==RS485_ACTIVE )
				 {
					networklayer( N_UNITDATArequest, NORMALmessage, network, source, destination, NULL, 0, apci, length_apci, ReplyPostponed);
				 }
				 PTRtable->state = STSM_AWAIT_RESPONSE+16;
				 next=0;
				 reject = 1;
				 break;
				}
				if( n < 0 )
				{                 // reading
				 STSM_State=STSM_AWAIT_RESPONSE;
				 s1=STSM_IDLE;
				}
				else
				{    				 //writing
				 asdu += n;
				 length_asdu -= n;
				 if( !(l=cdata->ser_pool.alloc(length_asdu)) )
				 {                                  // reject
					apci[0] = (BACnetRejectPDU<<4);
					apci[1] = STSM_InvokeID;
					apci[2] = 0;
					length_apci = 3;
					networklayer( N_UNITDATArequest, NORMALmessage, network, source, destination, NULL, 0, apci, length_apci, BACnetDataNotExpectingReply);
					ServerTSMTable.free(  current);
					next=0;
					break;
				 }
				 PTRtable->data = cdata->ser_data + l;
				 PTRtable->pool_index = l;
				 PTRtable->length = 0;
				 execservice(asdu, &length_asdu, current);
				 STSM_Event = CONF_SERVresponse;
				 STSM_State=STSM_AWAIT_RESPONSE;
				 s1=STSM_SEGMENTING_REQUEST;
				 reject = 1;
				}
				break;
			 }
			 else
			 {
					STSM_Event = serverBACnet( port, CONF_SERVindication, STSM_Service, asdu, length_asdu, current, &n, destport);
					apci[0] = (BACnetSimpleACKPDU<<4);
					apci[1] = STSM_InvokeID;
					apci[2] = STSM_Service;
					length_apci = 3;
					n = BACnetDataNotExpectingReply;
					networklayer( N_UNITDATArequest, NORMALmessage, network, source, destination,
												NULL, 0, apci, length_apci, n);
					ServerTSMTable.free(  current);
					next = 0;
					break;
			 }
			}
/*
			if (Event == Conf_req PDU with segmented_msg=TRUE
			{                              more_follows=TRUE)
				if(able to accept segment)
				{
				send SegmentACK PDU with server=TRUE
				STSM_State=STSM_SEGMENTED_REQUEST;
				}
				if(not able to accept segment)
				{
				send Abort PDU with server=TRUE
				STSM_State=STSM_IDLE;
				}
			}
*/
			if (STSM_Event == BACnetConfirmedRequestPDU && STSM_SEG == TRUE && STSM_MOR==TRUE)
			{
				PTRtable->windowsize=STSM_WinSize;
				STSM_Event = serverprocedure( port, CONF_SERVindication, asdu, length_asdu, current, &n, destport);
				memcpy(&l, asdu+n, 2);     // data_length
				n += 2;
				asdu += n;
				length_asdu -= n;
				if( !(l=cdata->ser_pool.alloc(l)) )
				{                                  // reject
//				if(STSM_Event == REJECTrequest)
//				{
				 apci[0] = (BACnetRejectPDU<<4);
				 apci[1] = STSM_InvokeID;
				 apci[2] = 0;
				 length_apci = 3;
				 networklayer( N_UNITDATArequest, NORMALmessage, network, source, destination, NULL, 0, apci, length_apci, BACnetDataNotExpectingReply);
				 ServerTSMTable.free(  current);
				 next=0;
				 break;
//				}
				}
				PTRtable->data = cdata->ser_data + l;
				PTRtable->pool_index = l;
				PTRtable->length = 0;
				execservice(asdu, &length_asdu, current);
				if(++PTRtable->noseg >= PTRtable->windowsize)
				{
				 apci[0] = (BACnetSegmentACKPDU<<4)|1;
				 apci[1] = STSM_InvokeID;
				 apci[2] = PTRtable->noseq;
				 apci[3] = PTRtable->windowsize;
				 apci[4] = 0x21;            // Application Tag 2( Unsigned, Length=1)
				 apci[5] = PTRtable->vendorID;
				 apci[6] = 0x22;            // Application Tag 2( Unsigned, Length=2)
				 apci[7] = PTRtable->command;
				 apci[8] = *((byte*)&PTRtable->arg);
				 length_apci = 9;
				 PTRtable->timeout = 350;
				 PTRtable->retrycount = 0;
				 networklayer( N_UNITDATArequest, NORMALmessage, network, source, destination, NULL, 0, apci, length_apci, BACnetDataNotExpectingReply);
				 PTRtable->noseg=0;
				}
				STSM_State=STSM_SEGMENTING_REQUEST;
				PTRtable->state = STSM_SEGMENTING_REQUEST;
				next=0;
				reject = 1;
				break;
			}
/*
			if (Event == SegmentACK PDU)
			{
				send Abort PDU with server=TRUE
				STSM_State=STSM_IDLE;
				next=0;
			}
*/
			if (STSM_Event == BACnetSegmentACKPDU)
			{
			  apci[0] = (BACnetAbortPDU<<4)|1;
			  apci[1] = STSM_InvokeID;
			  apci[2] = INVALIDAPDUINTHISSTATE;
				length_apci = 3;
				networklayer( N_UNITDATArequest, NORMALmessage, network, source, destination, NULL, 0, apci, length_apci, BACnetDataNotExpectingReply);
			  ServerTSMTable.free(  current);
			  next=0;
				break;
			}
			next=0;
			break;
	 case STSM_SEGMENTING_REQUEST:
/*			if (Event == Conf_req PDU with segmented_msg=TRUE
			{                              more_follows=TRUE)
			  if(able to accept segment)
			  {
				send SegmentACK PDU with server=TRUE
			  }
			  if(not able to accept segment)
			  {
				send Abort PDU with server=TRUE
				STSM_State=STSM_IDLE;
			  }
			}
*/
/*
			if (Event == Conf_req PDU with segmented_msg=TRUE
			{                              more_follows=FALSE)
				send SegmentACK PDU with server=TRUE
				send CONF_SERV.indication
				STSM_State=STSM_IDLE;
			}
*/
			if	(PTRtable->timeout<=0 && entrytimeout>=0	)
			{     //timeout
				 ServerTSMTable.free(  current);
				 STSM_State=STSM_IDLE;
				 next=0;
				 reject = 0;
				 break;
			}
/*
			if (Event == Abort PDU)
			{
				send ABORT.indication
			  STSM_State=STSM_IDLE;
			}
*/
			if (STSM_Event ==  BACnetAbortPDU)
			{
			 ServerTSMTable.free(current);
			 STSM_State=STSM_IDLE;
			 reject = 0;
			 next = 0;
			 break;
			}
			if (STSM_Event == BACnetConfirmedRequestPDU && STSM_SEG == TRUE)
			{
//				if( STSM_NoSeq < PTRtable->noseq-(PTRtable->nosegment?PTRtable->nosegment-1:PTRtable->windowsize-1) || STSM_NoSeq > PTRtable->noseq+1)
				if( STSM_NoSeq < PTRtable->noseq || STSM_NoSeq > PTRtable->noseq+1)
				{
				 next=0;
				 break;
				}
				s=0;
//				if( STSM_NoSeq == PTRtable->noseq-(PTRtable->nosegment?PTRtable->nosegment-1:PTRtable->windowsize-1 ) )    /* client resent last segment(s)*/
				if( STSM_NoSeq == PTRtable->noseq )    // client resent last segment(s)
				{
				 if( PTRtable->noseq==1 )    // first segment
				 {
					 s=1;
					 PTRtable->data -= PTRtable->last_length;
					 STSM_Event = serverprocedure( port, CONF_SERVindication, asdu, length_asdu, current, &n, destport);
//					 memcpy(&l, asdu+n, 2);     // data_length
					 n += 2;                    // data_length
					 asdu += n;
					 length_asdu -= n;
					 PTRtable->length = 0;
//					 execservice(asdu, &length_asdu, current);
				 }
				 else
				 {
					PTRtable->data -= PTRtable->last_length;
					PTRtable->length -= PTRtable->last_length;
//				 PTRtable->noseq = STSM_NoSeq;
				 }
				 PTRtable->noseg = 0;
				 PTRtable->last_length = 0;
				}
				if( STSM_NoSeq  == PTRtable->noseq+1 && !PTRtable->noseg ) // next segment
					PTRtable->last_length = 0;

				PTRtable->noseq = STSM_NoSeq;
				if(!s)
				{
				 n = decodetag(&asdu[0], &l);  //vendorid
				 n += l;
				 n += decodetag(&asdu[n], &l);  //service
				 n += l;
				 n += decodetag(&asdu[n], &l);
				 asdu += n;   //asdu length
				 length_asdu -= n;
        }
				execservice(asdu, &length_asdu, current);
				if(STSM_MOR==TRUE)
				{
				 if(++PTRtable->noseg >= PTRtable->windowsize)
				 {
					apci[0] = (BACnetSegmentACKPDU<<4)|1;
					apci[1] = STSM_InvokeID;
					apci[2] = PTRtable->noseq;
					apci[3] = PTRtable->windowsize;
					apci[4] = 0x21;            // Application Tag 2( Unsigned, Length=1)
					apci[5] = PTRtable->vendorID;
					apci[6] = 0x22;            // Application Tag 2( Unsigned, Length=2)
					apci[7] = PTRtable->command;
				  apci[8] = *((byte*)&PTRtable->arg);
				  length_apci = 9;
//				  PTRtable->timeout = 320;
				  PTRtable->timeout = 350;
					PTRtable->retrycount = 0;
					networklayer( N_UNITDATArequest, NORMALmessage, network, source, destination, NULL, 0, apci, length_apci, BACnetDataNotExpectingReply);
					PTRtable->noseg = 0;
				 }
				 next=0;
				}
				else
				{
				 STSM_Event = CONF_SERVresponse;
				 STSM_State=STSM_AWAIT_RESPONSE;
				 s1=STSM_SEGMENTING_REQUEST;
				}
				break;
			}

/*
			if (unexpected PDU from client)
			{
//         send Abort PDU with server = TRUE
			  STSM_State=STSM_IDLE;
			  next=0;
			}
*/
			next=0;
			break;
	 case STSM_AWAIT_RESPONSE:
/*			if (STSM_Event == CONF_SERV.response(+))
				if(APDU <= max_APDU_length_supported)
				{
				 send Simple_ACK PDU or
				 send Complex_ACK PDU with
						segmented_msg = FALSE
				 STSM_State=STSM_IDLE;
				}
				if(APDU > max_APDU_length_supported)
				{
				 send Complex_ACK PDU with
						segmented_msg = TRUE
						more_follows = TRUE
				 STSM_State=STSM_SEGMENTING_RESPONSE;
				}
*/
			if	(PTRtable->timeout<=0 && entrytimeout>=0	)
			{     //timeout
				ServerTSMTable.free(  current);
				STSM_State=STSM_IDLE;
				next=0;
				reject = 0;
				break;
			}
/*
			if (CTSM_Event == AbortPDU)
			{
				send ABORT.indication
				STSM_State=STSM_IDLE;
			}
*/
			if (STSM_Event ==  BACnetAbortPDU)
			{
			 ServerTSMTable.free(current);
			 STSM_State=STSM_IDLE;
			 reject = 0;
			 next = 0;
			 break;
			}
			if (STSM_Event == CONF_SERVresponse)
			{
//			  if(PTRtable->length > MAXASDUSIZE && s1==STSM_IDLE )
				if( s1==STSM_IDLE )
				{
				 buildservice(asdu, &length_asdu, current);
//				 if(PTRtable->length > MAXASDUSIZE)
				 if(PTRtable->length)
					apci[0] = (BACnetComplexACKPDU<<4)|0x0c;
				 else
					apci[0] = (BACnetComplexACKPDU<<4)|0x08;
//				 apci[0] = (BACnetComplexACKPDU<<4)|0x0c;
				 apci[1] = STSM_InvokeID;
				 apci[2] = PTRtable->noseq++;
				 apci[3] = PTRtable->windowsize;
				 apci[4] = STSM_Service;
				 apci[5] = 0x21;            // Application Tag 2( Unsigned, Length=1)
				 apci[6] = PTRtable->vendorID;
				 apci[7] = 0x22;            // Application Tag 2( Unsigned, Length=2)
				 apci[8] = PTRtable->command;
				 apci[9] = *((byte*)&PTRtable->arg);
				 if(PTRtable->length)
				 {
					if( PTRtable->command == READPROGRAMCODE_T3000 || PTRtable->command == READGROUPELEMENTS_T3000 )
						n = 10+encodetag(0, 6,	&apci[10], length_asdu+2+4 );   //2 bytes - total length of response data
					else                                                       //4 byte max_elements/space, cur_element/space_used
						n = 10+encodetag(0, 6,	&apci[10], length_asdu+2 );   //2 bytes - total length of response data
					l = PTRtable->length+length_asdu;
					memcpy(&apci[n], &l, 2);
					length_apci = n+2;
				 }
				 else
				 {
					if( PTRtable->command == READPROGRAMCODE_T3000 || PTRtable->command == READGROUPELEMENTS_T3000 )
						length_apci = 10+encodetag(0, 6,	&apci[10], length_asdu+4);
					else
						length_apci = 10+encodetag(0, 6,	&apci[10], length_asdu);
				 }
				 if( PTRtable->command == READPROGRAMCODE_T3000 )   // add 4 bytes with more info: programs pool length, occupied bytes
				 {
					memcpy(&apci[length_apci], &MAX_HEAP_BUF, 2);
					memcpy(&apci[length_apci+2], &programs_size, 2);
					length_apci += 4;
				 }
				 if( PTRtable->command == READGROUPELEMENTS_T3000 )   // add 4 bytes with more info: max_elemgrouppoll, curelem_grouppool
				 {
					memcpy(&apci[length_apci], &maxelem_grouppool, 2);
					memcpy(&apci[length_apci+2], &curelem_grouppool, 2);
					length_apci += 4;
				 }
				 if(PTRtable->compressed)  //compressed in one frame
					if( !PTRtable->length)
					{
					 apci[0] = (BACnetSimpleACKPDU<<4);
					 apci[1] = STSM_InvokeID;
					 apci[2] = STSM_Service;
					 apci[3] = 0x21;            // Application Tag 2( Unsigned, Length=1)
					 apci[4] = PTRtable->vendorID;
					 apci[5] = 0x22;            // Application Tag 2( Unsigned, Length=1)
					 apci[6] = PTRtable->command;
					 apci[7] = *((byte*)&PTRtable->arg);
					 n = 8+encodetag(0, 6,	&apci[8], PTRtable->last_length);
					 length_apci = n+2;
					 n = BACnetDataNotExpectingReply;
					 s=STSM_IDLE;
					}
				 n = BACnetDataNotExpectingReply;
				 if(PTRtable->length)
				 {
					STSM_Event = BACnetSegmentACKPDU;
					STSM_SRV=FALSE;
					PTRtable->timeout = 210;
					PTRtable->retrycount = 0;
//					PTRtable->last_length = 0;
					reject = 1;
					s=STSM_SEGMENTING_RESPONSE;
				 }
				 else
					 s=STSM_IDLE;
			  }
			  else
			  {
				 apci[0] = (BACnetSimpleACKPDU<<4);
				 apci[1] = STSM_InvokeID;
				 apci[2] = STSM_Service;
				 apci[3] = 0x21;            // Application Tag 2( Unsigned, Length=1)
				 apci[4] = PTRtable->vendorID;
				 apci[5] = 0x22;            // Application Tag 2( Unsigned, Length=1)
				 apci[6] = PTRtable->command;
				 apci[7] = *((byte*)&PTRtable->arg);
				 length_apci = 8;
				 n = BACnetDataNotExpectingReply;
				 length_asdu=0;
				 s=STSM_IDLE;
			  }
			  networklayer( N_UNITDATArequest, NORMALmessage, network, source, destination,
								 asdu, length_asdu, apci, length_apci, n);
			  PTRtable->noseg++;
			  STSM_State = s;
			 if (s==STSM_IDLE)
			 {
				if(PTRtable->command>100)
				{                           //writing - run exec
				 if( PTRtable->command==100+READPROGRAMCODE_T3000)
				 {
				  if(!update_prg_flag)
				  {
					PTRtable->timeout = 210;
					PTRtable->data -= PTRtable->length;
					STSMtable_ptr = PTRtable;
					STSMtable_ptr_port = port;
					update_prg_flag = 1;
					action=1;
					if( tasks[MISCELLANEOUS].status == SUSPENDED )
					 resume(MISCELLANEOUS);
					STSM_State=STSM_IDLE;
//				   reject = 0;
					next = 0;
					break;
				  }
				 }
				 if( PTRtable->command==100+(AMON+1) )
				 {
				  if( !savemon_flag )
				  {
					PTRtable->timeout = 210;
					PTRtable->data -= PTRtable->length;
					STSMtable_ptr = PTRtable;
					STSMtable_ptr_port = port;
					savemon_flag = 1;
					action=1;
					if( tasks[MISCELLANEOUS].status == SUSPENDED )
					 resume(MISCELLANEOUS);
					STSM_State=STSM_IDLE;
//				   reject = 0;
					next = 0;
					break;
					}
				 }
				 else
				 {
//				  pex1(PTRtable, port);
						execute_command( cdata->media, TRANSFER_DATA,  pobj,
							PTRtable->data - PTRtable->length, PTRtable, destport);
				 }
				}
				ServerTSMTable.free(  current);
				STSM_State=STSM_IDLE;
				reject = 0;
				next = 0;
			 }
			 else
				PTRtable->state = s;
			 break;
			}
/*
			if (CTSM_Event == CONF_SERV.response(-))
			{
				send Error PDU
			  STSM_State=STSM_IDLE;
			}
*/
/*
			if (unexpected PDU from client)
			{
//         send Abort PDU with server = TRUE
			  STSM_State=STSM_IDLE;
			}
*/
/*
			if (timeout waiting for PDU)
			{
			  send Abort PDU with server = TRUE
			  STSM_State=STSM_IDLE;
			}
*/
			next=0;
			break;
	 case STSM_SEGMENTING_RESPONSE:
/*       if (timeout waiting for PDU)
			{
			  if(retry count not exceed )
			  {
				 resend previous ComplexACK PDU segment(s)
			  }
			  if(retry count exceed )
			  {
				STSM_State=STSM_IDLE;
				next=0;
			  }
			}
*/
if(xxxx++==2)
	xxxx = 3;

			if	(PTRtable->timeout<=0 && entrytimeout>=0	)
			{                            		 //timeout waiting for PDU
				if(	PTRtable->retrycount++ < 1 )   //1
				{                               //retry count not exceed
				ServerTSMTable.resetsegments(current);
				while( ++PTRtable->noseg <= PTRtable->windowsize && STSM_State==STSM_SEGMENTING_RESPONSE)
				{
				 if(PTRtable->length)
				 {
					buildservice(asdu, &length_asdu, current);
					if(PTRtable->length)
						apci[0] = (BACnetComplexACKPDU<<4)|0x0c;
					else
						apci[0] = (BACnetComplexACKPDU<<4)|0x08;
					apci[1] = PTRtable->invokeID;
					apci[2] = PTRtable->noseq++;
					apci[3] = PTRtable->windowsize;
					apci[4] = PTRtable->service;
					apci[5] = 0x21;            // Application Tag 2( Unsigned, Length=1)
					apci[6] = PTRtable->vendorID;
					apci[7] = 0x22;            // Application Tag 2( Unsigned, Length=1)
					apci[8] = PTRtable->command;
					apci[9] = *((byte*)&PTRtable->arg);
					if( PTRtable->noseq == 2 ) //resend first segment
					{
					 if(PTRtable->length)
					 {
						if( PTRtable->command == READPROGRAMCODE_T3000 || PTRtable->command == READGROUPELEMENTS_T3000 )
							n = 10+encodetag(0, 6,	&apci[10], length_asdu+2+4 );   //2 bytes - total length of response data
						else                                                       //4 byte max_elements/space, cur_element/space_used
							n = 10+encodetag(0, 6,	&apci[10], length_asdu+2 );   //2 bytes - total length of response data
						l = PTRtable->length+length_asdu;
						memcpy(&apci[n], &l, 2);
						length_apci = n+2;
					 }
					 if( PTRtable->command == READPROGRAMCODE_T3000 )   // add 4 bytes with more info: programs pool length, occupied bytes
					 {
						memcpy(&apci[length_apci], &MAX_HEAP_BUF, 2);
						memcpy(&apci[length_apci+2], &programs_size, 2);
						length_apci += 4;
					 }
					 if( PTRtable->command == READGROUPELEMENTS_T3000 )   // add 4 bytes with more info: max_elemgrouppoll, curelem_grouppool
					 {
						memcpy(&apci[length_apci], &maxelem_grouppool, 2);
						memcpy(&apci[length_apci+2], &curelem_grouppool, 2);
						length_apci += 4;
					 }
					}
					else
					{
						n = 10+encodetag(0, 6,	&apci[10], length_asdu);
						length_apci = n;
					}
					PTRtable->timeout = 210;
					networklayer( N_UNITDATArequest, NORMALmessage, network, source, destination, asdu, length_asdu, apci, length_apci, BACnetDataNotExpectingReply);
				 }
				 else       // no more APDU segments
				 {
					ServerTSMTable.free(  current);
					STSM_State=STSM_IDLE;
					reject = 0;
				 }
				}
				PTRtable->noseg = 0;
				}
				else                             //retry count exceed
				{
				ServerTSMTable.free(  current);
				STSM_State=STSM_IDLE;
				reject = 0;
			  }
			  next=0;
				break;
/*
				ServerTSMTable.free(current);
			  STSM_State=STSM_IDLE;
				next=0;
			  break;
*/
			}
/*
			if (Event == SegmentACKPDU with server=FALSE)
			{
			 if (not final APDU segment)
			 {
				send ComplexACK PDU with
					  segmented_msg = TRUE
					  more_follows = TRUE
			 }
			 if (final APDU segment)
			 {
				send ComplexACK PDU with
					  segmented_msg = TRUE
					  more_follows = FALSE
			 }
			 if (no more APDU segments)
			 {
				 STSM_State=STSM_IDLE;
				 next=0;
			 }
			}
*/
			if( entrytimeout >=0 )
			{
			 next=0; break;
			}
/*
			if( Abort PDU with server = FALSE)
			{
				 send ABORT.indication
//			    STSM_State=STSM_IDLE;
				 next=0;
			}
*/
			if (STSM_Event ==  BACnetAbortPDU)
			{
				 ServerTSMTable.free(current);
				 STSM_State=STSM_IDLE;
				 reject = 0;
				 next = 0;
				 break;
			}
			if (STSM_Event == BACnetSegmentACKPDU && STSM_SRV==FALSE)
			{
			 if(PTRtable->noseg==0)	PTRtable->last_length = 0;
			 while( ++PTRtable->noseg <= PTRtable->windowsize && STSM_State==STSM_SEGMENTING_RESPONSE)
			 {
			  if(PTRtable->length)
			  {
				buildservice(asdu, &length_asdu, current);
//				if(PTRtable->length > MAXASDUSIZE)
				if(PTRtable->length)
				 apci[0] = (BACnetComplexACKPDU<<4)|0x0c;
				else
				 apci[0] = (BACnetComplexACKPDU<<4)|0x08;
				apci[1] = PTRtable->invokeID;
				apci[2] = PTRtable->noseq++;
				apci[3] = PTRtable->windowsize;
				apci[4] = PTRtable->service;
				apci[5] = 0x21;            // Application Tag 2( Unsigned, Length=1)
				apci[6] = PTRtable->vendorID;
				apci[7] = 0x22;            // Application Tag 2( Unsigned, Length=1)
				apci[8] = PTRtable->command;
				apci[9] = *((byte*)&PTRtable->arg);
				n = 10+encodetag(0, 6,	&apci[10], length_asdu);
				length_apci = n;
				PTRtable->timeout = 210;
				PTRtable->retrycount = 0;
				networklayer( N_UNITDATArequest, NORMALmessage, network, source, destination, asdu, length_asdu, apci, length_apci, BACnetDataNotExpectingReply);
			  }
			  else       // no more APDU segments
			  {
				ServerTSMTable.free(  current);
				STSM_State=STSM_IDLE;
				reject = 0;
			  }
			 }
			 PTRtable->noseg=0;
			 next=0;
			 break;
			}
/*
			if (unexpected PDU from client)
			{
//         send Abort PDU with server = TRUE
			  STSM_State=STSM_IDLE;
			  next=0;
			}
*/
			next=0;
			break;
	 default:
			ServerTSMTable.free(  current);
			STSM_State=STSM_IDLE;
			next=0;
			reject = 0;
			break;
  } // end switch
 }  // end while
// clear_semaphore(&ServerTSM_flag);
 ServerTSM_flag = -1;
// STSMremoveflag =  0;
 if(postponed) return;
 if(entrytimeout<0)
 {
	n = checkTSMtimeout(-1);
	if( tasks[SERVERTSM].status!=READY )
	{
	 if (n==10000)
		suspend(SERVERTSM);
	 else
		msleep(SERVERTSM,n);
	}
 }
}

/*
int rs485_receive_frame()
{
 signed char next;
 int c,index;
 signed char nextentry;
 struct ReceivedFrame *pframe;
 suspend(RS485_RECEIVEFRAME);
 while( !SERIAL_EXIT )
 {
  if( ser_rs485->port_status == INSTALLED )
	{
	if(MSTP_ReceiveFrameStatus != MSTP_IDLE)
	{
	if( (nextentry = ReceivedFramePool.NextFreeEntry()) >=0 )
	{
	pframe = &ReceivedFramePool.ReceivedFrame[nextentry];
	while(MSTP_ReceiveFrameStatus != MSTP_IDLE)
	{
	 next=0;
	 if( SilenceTimer > Tframe_abort || ReceiveError==TRUE)
	 {
		 if( ReceiveError==TRUE ) ReceiveError=FALSE;
		 pframe->ReceivedInvalidFrame = TRUE;
		 SilenceTimer=0;
//		 MSTP_Preamble1=MSTP_Preamble2=0;
//		 MSTP_Receive_Frame_Status = MSTP_IDLE;
//		 continue;
		 break;
	 }
//	 if( ( c = ser_rs485->port->Read( 0 ) ) < 0 ) continue;
	 if( ( c = ser_rs485->port->read_byte() ) < 0 ) continue;
	 SilenceTimer=0;
//	 EventCount++;
	 switch(MSTP_ReceiveFrameStatus) {
		case MSTP_HEADER:
				MSTP_HeaderCRC=CalcHeaderCRC(c, MSTP_HeaderCRC);
				switch( MSTP_HEADERState ) {
						case MSTP_HEADER_FrameType:
//							  MSTP_FrameType = c;
							  pframe->Frame.FrameType = c;
							  MSTP_HEADERState = MSTP_HEADER_Destination;
							  break;
						case MSTP_HEADER_Destination:
//							  MSTP_Destination = c;
							  pframe->Frame.Destination = c;
							  MSTP_HEADERState = MSTP_HEADER_Source;
							  break;
						case MSTP_HEADER_Source:
//							  MSTP_Source = c;
							  pframe->Frame.Source = c;
							  MSTP_HEADERState = MSTP_HEADER_Length1;
							  break;
						case MSTP_HEADER_Length1:
//							  MSTP_DataLength = c<<8;
								pframe->Frame.Length = c<<8;
							  MSTP_HEADERState = MSTP_HEADER_Length2;
								break;
						case MSTP_HEADER_Length2:
//							  MSTP_DataLength += c;
							  pframe->Frame.Length += c;
							  MSTP_HEADERState = MSTP_HEADER_HeaderCRC;
//							  index_InputBuffer = 0;
							  index = 0;
							  break;
						case MSTP_HEADER_HeaderCRC:
							  if( MSTP_HeaderCRC != 0x55 )
							  {
								 pframe->ReceivedInvalidFrame = TRUE;
							  }
							  else
								if(!pframe->Frame.Length)
								{
								 pframe->ReceivedValidFrame = TRUE;
								}
								else
								{
									MSTP_DataCRC=0xffff;
								  MSTP_ReceiveFrameStatus = MSTP_DATA;
								  break;
								}
//							  MSTP_Preamble1=MSTP_Preamble2=0;
//							  MSTP_Receive_Frame_Status = MSTP_IDLE;
							  next=1;
							  break;
				}
				break;
		case MSTP_DATA:
				MSTP_DataCRC=CalcDataCRC(c, MSTP_DataCRC);
//				if( index_InputBuffer < MSTP_DataLength )
				if( index < pframe->Frame.Length )
				{
//				  InputBuffer[index_InputBuffer++]=c;
				  pframe->Frame.Buffer[index++]=c;
				}
				else
				{
//				 if( index_InputBuffer == MSTP_DataLength+1 )
				 if( index++ == pframe->Frame.Length+1 )
				 {
				  if( MSTP_DataCRC==0x0f0b8 )
					 pframe->ReceivedValidFrame = TRUE;
				  else
					 pframe->ReceivedInvalidFrame = TRUE;
//				  MSTP_Preamble1=MSTP_Preamble2=0;
//				  MSTP_Receive_Frame_Status = MSTP_IDLE;
				  next=1;
				 }
				}
				break;
	 }
	 if( next ) break;
	} //	end while(MSTP_Receive_Frame_Status != MSTP_IDLE)
	ReceivedFramePool.Unlockhead();
	resume(MSTP_MASTER);
	}
  } // end if(MSTP_ReceiveFrameStatus != MSTP_IDLE)
//	else  frame lost
  }
//  c=ser_rs485->port->Read(0);
  c=ser_rs485->port->read_byte();
	MSTP_Preamble1=MSTP_Preamble2=0;
  if(ReceiveError==FALSE && SilenceTimer<Tframe_abort)
  {
	  if(c==0xFF)
		 c=ser_rs485->port->read_byte();
//		 c=ser_rs485->port->Read(0);
	  if( c>=0 )
	  {
		if( c==0x55 )
		{
		 MSTP_Preamble1=0x55;
		 c=ser_rs485->port->read_byte();
//		 c=ser_rs485->port->Read( 0 );
		 if( c>=0 )
		 {
		  if( c==0xff )
		  {
			MSTP_Preamble2=0xff;
			MSTP_ReceiveFrameStatus=MSTP_HEADER;
			MSTP_HeaderCRC=0xff;
			MSTP_HEADERState=MSTP_HEADER_FrameType;
			SilenceTimer=0;
			continue;
		  }
		  else
		  {
			MSTP_Preamble1=MSTP_Preamble2=0;
		  }
		 }
		}
	  }
  }
//  ReceiveError=FALSE;
//  SilenceTimer=0;
  ser_rs485->port->FlushRXBuffer();
  MSTP_ReceiveFrameStatus = MSTP_IDLE;
  suspend(RS485_RECEIVEFRAME);
 }
}
*/

/*
int MSTP::MSTP_receive_frame(MSTP *mstp)
{

 signed char next;
 int c,index,x;
 signed char nextentry=-1;
 struct MSTP_ReceivedFrame *pframe;
 struct port_status_variables *ps;
 ps = &Routing_table[mstp->port_number].port_status_vars;

 while( !RS485_EXIT )
 {
  {
	if(ps->ReceiveFrameStatus != RECEIVE_FRAME_IDLE)
	{
	if( (nextentry = mstp->ReceivedFramePool.NextFreeEntry()) >=0 )
	{
	pframe = &mstp->ReceivedFramePool.ReceivedFrame[nextentry];
	while(ps->ReceiveFrameStatus != RECEIVE_FRAME_IDLE)
	{
	 next=0;
	 if( ps->SilenceTimer > Tframe_abort || ps->ReceiveError==TRUE)
	 {
		 if( ps->ReceiveError==TRUE ) ps->ReceiveError=FALSE;
		 pframe->ReceivedInvalidFrame = TRUE;
		 ps->SilenceTimer=0;
		 break;
	 }
	 asm push es;
	 if( ( c = mstp->port->isr_data->RXQueue.Remove() ) < 0 )
	 {
	  asm pop es;
	  continue;
	 }
	 asm pop es;
	 ps->SilenceTimer=0;
	 switch(ps->ReceiveFrameStatus) {
		case RECEIVE_FRAME_HEADER:
//				ps->HeaderCRC=CalcHeaderCRC(c, ps->HeaderCRC);
				ps->HeaderCRC = table_crc8[ps->HeaderCRC^c];
				switch( ps->HEADERState ) {
						case HEADER_FrameType:
							  pframe->Frame.FrameType = c;
							  ps->HEADERState = HEADER_Destination;
								break;
						case HEADER_Destination:
								pframe->Frame.Destination = c;
							  ps->HEADERState = HEADER_Source;
							  break;
						case HEADER_Source:
							  pframe->Frame.Source = c;
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
								 pframe->ReceivedInvalidFrame = TRUE;
							  }
							  else
								if(!pframe->Frame.Length)
								{
								 pframe->ReceivedValidFrame = TRUE;
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
				ps->DataCRC=CalcDataCRC(c, ps->DataCRC);
				if( index < pframe->Frame.Length )
				{
				  pframe->Frame.Buffer[index++]=c;
				}
				else
				{
				 if( index++ == pframe->Frame.Length+1 )
				 {
				  if( ps->DataCRC==0x0f0b8 )
					 pframe->ReceivedValidFrame = TRUE;
				  else
					 pframe->ReceivedInvalidFrame = TRUE;
				  next=1;
				 }
				}
				break;
	 }
	 if( next ) break;
	} //	end while(MSTP_Receive_Frame_Status != MSTP_IDLE)
	mstp->ReceivedFramePool.Unlockhead();
	resume(MSTP_MASTER);
	}
  } // end if(MSTP_ReceiveFrameStatus != MSTP_IDLE)
//	else  frame lost
  }

	ps->validint = 0;
  ps->Preamble1=ps->Preamble2=0;
	disable();
  ps->ReceiveFrameStatus = RECEIVE_FRAME_IDLE;
  suspend(RS485_RECEIVEFRAME);
 }
 resume_suspend( PROJ, RS485_RECEIVEFRAME );
}
*/

void MSTP::SendFrame(FRAME *frame, char wait)
{
 RS232Error status;
 char *p, buf[8];
 int crc,ind;
 unsigned int length, rate;
 unsigned long l;
 PORT_STATUS_variables *ps;
 if(	((class MSTP *)Routing_table[port_number].ptr)->port_status != INSTALLED )
   return;
 ps = &Routing_table[port_number].port_status_vars;
// if( ser_rs485 )
 {
//  period = 50000L / ser_rs485->ReadBaudRate();
	rate = ReadBaudRate()/10;
//  HeaderCRC
//  DataCRC
	if(frame)
	{
	 if(frame->Source==255)
	 {
		if(iwanttodisconnect)
		{
		 panelOff = 1;
		 iwanttodisconnect=0;
		 frame->Source = TS;
		}
	 }
	 frame->Preamble = 0x0FF55;
	 frame->HeaderCRC = 0x0FF;
	 p = (char *)&frame->FrameType;
// switch the low and high bytes of Length -> BAC frame
	 length = frame->Length;
	 frame->Length = ( (*((char *)&length))<<8 ) + *( (((char *)&length)+1) );
// end switch
	 for(ind=0; ind<5; ind++)
		frame->HeaderCRC=CalcHeaderCRC(*p++, frame->HeaderCRC);
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
	 frame->Buffer[ind++]=0x0ff;
	}
	else
	{
	 memset(buf, 0x55, 6);
	 buf[6]=0x015;
	 buf[7]=0x0ff;
	 ind = 0;
	 frame = (FRAME *)&buf[0];
	}
// feb 06,97
//	 if( !ps->HeartbeatTimer )
	switch(rate/480){
	 case 0:
	 case 1:
		 delay(8);
		 break;
	 case 2:
		 delay(5);
		 break;
	 case 4:
		 delay(3);
		 break;
	 case 8:
		 delay(2);
		 break;
	 default:
		 delay(1);
		 break;
	}
//	delay(5);
//	 msleep(1);
//  while (SilenceTimer < Tturnaround );
//  ser_rs485->Set_PIC_mask();
//  ser_rs485->port->Dtr( 0 );
  Set_PIC_mask();
//  port->Dtr( 0 );

//  port->Dtr( !dtr );

	//  port->Rts( 0 );
// disable the receiver and enable the transmit line driver
	status = port->write_buffer( (char *)frame, ind+8 );
/*
	if( ind > (60L*(long)rate)/1000 )     // 60ms*Rate/1000
	{
		msleep(250l*1000l/rate);            // 1500char*1000ms/rate/6ms
	}
	else
*/
	if( ind > (wait?510:((60L*(long)rate)/1000 ) ) )   // 60ms*Rate/1000
	{
//		msleep(250l*1000l/rate);            // 1500char*1000ms/rate/6ms
		msleep(ind*333l/rate);            // nr_char*1000ms/rate/6ms(6=ticks)  = 2 * time need
	}
	else
	{
//	 l = timestart+4;
	 switch(rate/480){
		case 0:
		case 1:
		 l = 2000;
		 break;
		default:
		case 2:
		 l = 1000;
		 break;
		case 4:
		case 8:
		 l = 600;
		 break;
	 }
	 tasks[tswitch].delay_time = l;
	 while( port->isr_data->tx_running )
	 {
//		if(timestart > l)
		if( tasks[tswitch].delay_time<=0 )
		{
		 break;
		}
	 }
	}
	Routing_table[port_number].port_status_vars.SilenceTimer=0;
	Reset_PIC_mask();
	if(port->isr_data->tx_running)
	{
	 port->Dtr( dtr );
//	 port->Rts(1);
	 OUTPUT( port->isr_data->uart + INTERRUPT_ENABLE_REGISTER,
				IER_RX_DATA_READY + IER_MODEM_STATUS + IER_LINE_STATUS );
//	 port->Rts(0);
	 FlushTXbuffer();
	 port->resettxrunning();
  }
	else
  {
	 port->settings.Dtr = dtr;
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

// wait until the final stop bit of the most significant CRC octet
// has been transmitted but not more than Tpostdrive after
//  while(ser_p->port->TXSpaceUsed());
// (becose I sent a 0x0ff byte at the end of frame,
//  I can disable now the transmiter line driver)

// disable the transmit line driver
	UsedToken = TRUE;
 }
}

char getID(void)
{
 return random(254);
}

int networklayer( int service, int priority, int network, int destination, int source,
						char *asdu_npdu, int length_asdu_npdu, char *apci, int length_apci,
						int data_expecting_reply, int clientserver, int port)
{
 signed char n;
 char npci[MAXAPCI];
 int i, j, length_npci, nextentry, router_address;
 FRAME *pframe;
 int DNET, SNET, MessageType, dnet, snet, ses_ind;
 char Control, DLEN, SLEN, VendorID, DADR[6], SADR[6], direct;
 signed char HopCount;
 ROUTER_PARAMETERS r;
// Serial *sptr;
class ConnectionData *cdata;
 snet=dnet=DNET=SNET=0;

 if( service==N_UNITDATArequest )
 {
		router_address = destination;
//  if ( network == NetworkAddress || network == LOCALNETWORK)
	npci[0]=0x01;
	if ( network != BROADCAST )
	{
// find routing entry
		snet = 0; dnet = MAX_Routing_table;
		if( port >= 0 ) {snet = port; dnet = port+1;}
		for(i=snet; i<dnet; i++)
		{
		 j=-1;
		 if( (Routing_table[i].status&PORT_ACTIVE)==PORT_ACTIVE )
			if( Routing_table[i].Port.network==network )
			{
				 break;
			}
			else
			{
				for(j=0; j<MAX_reachable_networks; j++)
				 if( ((Routing_table[i].Port.networks_list[j].status&REACHABLE) == REACHABLE) &&
						Routing_table[i].Port.networks_list[j].network==network)
				 {
					 router_address=Routing_table[i].Port.networks_list[j].router_address;
					 break;
				 }
				if(j<MAX_reachable_networks) break;
			}
		}
//  check result
		if (i<dnet)
		{
		 npci[0]=0x01;
		 if( network == Routing_table[i].Port.network &&
				 ( ((Routing_table[i].status&RS485_INSTALLED)==RS485_INSTALLED)  ||
					 ((Routing_table[i].status&TCPIP_INSTALLED)==TCPIP_INSTALLED)  ||
					 ((Routing_table[i].status&IPX_INSTALLED)==IPX_INSTALLED) ) )
		 {    // local network
			 npci[1]=0x00;     //DNET, DADR, SNET, SADR absent
			 length_npci=2;
		 }
		 else
		 {
/*
			 if( (Routing_table[i].status&PTP_INSTALLED)==PTP_INSTALLED )
				sptr = (class PTP *)Routing_table[i].ptr;
			 else
				sptr = (class MSTP *)Routing_table[i].ptr;
*/
			 cdata = ( class ConnectionData *)Routing_table[i].ptr;
			 npci[1]=0x50;
			 memcpy( &npci[2], &network, 2);
			 npci[4]=destination;
			 memcpy( &npci[5], &cdata->panel_info1.network, 2);
			 npci[7]=Station_NUM;
			 npci[8]=5;
			 length_npci=9;
		 }

		 if(!(Routing_table[i].status^PTP_ACTIVE))
		 {
			((class PTP *)Routing_table[i].ptr)->sendframe(length_npci, npci, length_asdu_npdu, asdu_npdu, length_apci, apci);
		 }
		 if( (Routing_table[i].status&RS485_ACTIVE)==RS485_ACTIVE )
		 {
// build frame
			if(replyflag==1)
			{
			 pframe = (FRAME *)&ServerBuffer[0];
			}
			else
			{
			 if( ((class MSTP *)Routing_table[i].ptr)->OS==Station_NUM)
			 {
				return 0;
			 }
			 if( ((clientserver>>8)&NETCALL_CHECKDUPLICATE)==NETCALL_CHECKDUPLICATE )
			 {
				 if( ((class MSTP *)Routing_table[i].ptr)->SendFramePool.CheckEntry(router_address, source) )
						return 0;
			 }
			 nextentry = ((class MSTP *)Routing_table[i].ptr)->SendFramePool.NextFreeEntry();
			 if( nextentry < 0 ) return 0;
			 pframe = &((class MSTP *)Routing_table[i].ptr)->SendFramePool.Frame[nextentry];
			}
//	if( (nextentry = SendFramePool.NextFreeEntry()) >=0 )
//	{
//	 pframe = &SendFramePool.Frame[nextentry];
			pframe->FrameType = data_expecting_reply;
			pframe->Destination = router_address;
			pframe->Source = source;
			pframe->Length = length_npci+length_apci+length_asdu_npdu;
			memcpy(pframe->Buffer, npci, length_npci);
			memcpy(&pframe->Buffer[length_npci], apci, length_apci);
			memcpy(&pframe->Buffer[length_npci+length_apci], asdu_npdu, length_asdu_npdu);

			if(replyflag!=1)
			{
//			((class MSTP *)Routing_table[i].ptr)->SendFramePool.Unlockhead();
			 ((class MSTP *)Routing_table[i].ptr)->SendFramePool.status[nextentry]=1;
			}
			else
			 replyflag=2;
//	}
		 }
#ifdef NET_BAC_COMM
		 if( (Routing_table[i].status&IPX_ACTIVE)==IPX_ACTIVE
				|| (Routing_table[i].status&TCPIP_ACTIVE)==TCPIP_ACTIVE )
		 {
// build frame
			if(replyflag==1)
			{
			 pframe = (FRAME *)&ServerBuffer;
			}
			else
			{
				pframe = (FRAME *)((class NET_BAC *)Routing_table[i].ptr)->SendFramePool.NextFreeEntry(0);
				if( pframe == NULL )
					return 0;
			}
			pframe->FrameType = data_expecting_reply;
			pframe->Destination = router_address;
			pframe->Source = source;
			pframe->Length = length_npci+length_apci+length_asdu_npdu;
			memcpy(pframe->Buffer, npci, length_npci);
			memcpy(&pframe->Buffer[length_npci], apci, length_apci);
			memcpy(&pframe->Buffer[length_npci+length_apci], asdu_npdu, length_asdu_npdu);

			((class NET_BAC *)Routing_table[i].ptr)->SendFramePool.Unlock_frame(
																									 (SEND_FRAME_ENTRY*)pframe );
			resume( ((class NET_BAC *)Routing_table[i].ptr)->task_number );
		 }
#endif // NET_BAC_COMM
		}
	}
	else
	{

	}
 }
 if( service==DL_UNITDATAindication )
 {
	memcpy(npci, asdu_npdu, MAXAPCI);
	Control = npci[1];
	switch (Control&0x60) {
	 case 0x00: dnet = ABSENT;   //this panel
					n = 2;
					break;
	 case 0x40: memcpy(&DNET, &npci[2], 2);   //DNET, HopCount, DADR one octet
					DADR[0] = npci[4];
					DLEN = 1;
					n = 5;
					break;
	 case 0x60: memcpy(&DNET, &npci[2], 2);   //DNET, DLEN, HopCount
					DLEN = npci[4];               // DLEN=0 broadcast MAC DADR
					if (!DLEN) DADR[0]=0xFF;      // DLEN>0 length DADR
					else memcpy(DADR, &npci[5], DLEN);
					n = 5+DLEN;
					break;
	}
	switch (Control&0x18) {
	 case 0x00: snet = ABSENT;
					break;
	 case 0x10: memcpy(&SNET, &npci[n], 2);
					SADR[0] = npci[n+2];
					SLEN = 1;
					n += 3;
					break;
	 case 0x18: memcpy(&SNET, &npci[n], 2);
					SLEN = npci[n+2];
					memcpy(&SADR, &npci[n+3], SLEN);
					n += 3+SLEN;
					break;
	}
	if ( dnet!=ABSENT ) HopCount = npci[n++];
	if ( snet==ABSENT )
	{
		SNET = Routing_table[port].Port.network;
		SADR[0] = source;
	}
	if ( Control&0x80 )
	{
	 MessageType=npci[n++];
	 if ( MessageType>=0x80 && MessageType<=0xFF ) VendorID = npci[n++];
	 direct = 0;
	 if( dnet==ABSENT || DNET==0xFFFF )
	 {  //global broadcast
		//interpret si send
		r.SNET = SNET;
		r.SLEN = SLEN;
		memcpy(r.SADR, SADR, 6);
		r.len = length_asdu_npdu-n;
		r.data = &asdu_npdu[n];
/*
						rr2++;
						sprintf( rrr_buf, "%d", rr2 );
						mxyputs(10,12,"NU_indication");
						mxyputs(30,12,rrr_buf );
*/

		router(DL_UNITDATAindication, MessageType, &r, port);
	 }
	 --HopCount;
	 if( dnet!=ABSENT )
	 {
		for(i=0; i<MAX_Routing_table; i++)
		{
		 if( (Routing_table[i].status&PORT_ACTIVE)==PORT_ACTIVE)
		 {
			if( DNET == BROADCAST )
			{
			}
			else
			if( Routing_table[i].Port.network==DNET )
			{
			 if(!(Routing_table[i].status^PTP_ACTIVE))
			 {
				npci[0]=0x01;
				npci[1]=0x90;
				memcpy(&npci[2], &SNET, 2);
				npci[4]=SADR[0];
				npci[5]=MessageType;
				((class PTP *)Routing_table[i].ptr)->sendframe(6, npci, length_asdu_npdu-n, &asdu_npdu[n]);
			 }
			 break;
			}
			else
			{
			 if(HopCount)
				for(j=0; j<MAX_reachable_networks; j++)
				 if( ((Routing_table[i].Port.networks_list[j].status&REACHABLE) == REACHABLE) &&
						Routing_table[i].Port.networks_list[j].network==DNET)
				 {
					 if(!(Routing_table[i].status^PTP_ACTIVE))
					 {
						 npci[1]=0xD0;
						 memcpy(&npci[5], &SNET, 2);
						 npci[7]=SADR[0];
						 npci[8]=HopCount;
						 npci[9]=MessageType;
						 ((class PTP *)Routing_table[i].ptr)->sendframe(10, npci, length_asdu_npdu-n, &asdu_npdu[n]);
					 }
					 break;
				 }
			}
		 }
		}
/*
		if( i >= MAX_Routing_table )
		{
		// Who_Is_Router_To_Network
		 if( DNET != GLOBAL )
		 {
			npci[1]=0x80;
			npci[2]=Who_Is_Router_To_Network;
			memcpy(&npci[3], DNET, 2);
			for(int j=0; j<MAX_Routing_table; j++)
			{
			if(Routing_table[i].status&PTP_ACTIVE && i!=port)
			 ((class PTP *)Routing_table[i].ptr)->sendframe(4, npci);
			}
		 }
		}
*/
	 }
	 else
	 {
		npci[1]=0x90;
		memcpy(&npci[2], &SNET, 2);
		npci[4]=SADR[0];
		npci[5]=MessageType;
		for(j=0; j<MAX_Routing_table; j++)
		{
		 if( !(Routing_table[i].status^PTP_ACTIVE) && j!=port)
			((class PTP *)Routing_table[j].ptr)->sendframe(6, npci, length_asdu_npdu-n, &asdu_npdu[n]);
		}
	 }
	}
	else
	{
	 i=0;
// request on local panel
	 if(port>=0)
	 {
/*
		if( (Routing_table[port].status&PTP_INSTALLED)==PTP_INSTALLED )
		 sptr = (class PTP *)Routing_table[port].ptr;
		else
		 sptr = (class MSTP *)Routing_table[port].ptr;
*/
//		j = comm_info[cdata->com_port].NetworkAddress;
		cdata = ( class ConnectionData *)Routing_table[port].ptr;
		j = cdata->panel_info1.network;
	 }
	 else
		j = NetworkAddress;

	 if ( dnet==ABSENT || (dnet!=ABSENT && DNET == j && (DADR[0] == Station_NUM || DADR[0] == 0xFF) ) )
	 {
		if( clientserver&0x0FF == CLIENT )
		{
			ClientTSMTable.received(destination, SADR[0], &asdu_npdu[n], length_asdu_npdu-n);
		}
		else
		{
		 if ( dnet==ABSENT ) DADR[0] = destination;
		 network = SNET;
		 ServerTransactionStateMachine(port, network, DADR[0], SADR[0],
						&asdu_npdu[n], length_asdu_npdu-n );
		}
		i=1;
	 }
// request on remote panel
	 if ( !i && dnet!=ABSENT )
	 {
		for(i=0; i<MAX_Routing_table; i++)
		{
		 if( i!=port && (Routing_table[i].status&PORT_ACTIVE)==PORT_ACTIVE )
		 {
			if( Routing_table[i].Port.network==DNET )
			{
// connected direct to DNET
			 if( (Routing_table[i].status&RS485_ACTIVE)==RS485_ACTIVE ||
					 (Routing_table[i].status & IPX_ACTIVE) == IPX_ACTIVE ||
					 (Routing_table[i].status & TCPIP_ACTIVE) == TCPIP_ACTIVE )
			 {
				// request directed to a network ( RS485/IPX/TCPIP) port
				if ( DADR[0] == Station_NUM || DADR[0] == 0xFF )
				{
				 // more then one network (RS485/IPX/TCPIP) installed on this panel
				 if( clientserver&0x0FF == CLIENT )
				 {
//					LengthReceivedClientAPDU = length_asdu_npdu-n;
//					PTRReceivedClientAPDU = &asdu_npdu[n];
						ClientTSMTable.received(DADR[0], SADR[0], &asdu_npdu[n], length_asdu_npdu-n);
				 }
				 else
				 {
					network = SNET;
					ServerTransactionStateMachine(port, network, DADR[0], SADR[0],
						&asdu_npdu[n], length_asdu_npdu-n, -1, i );
				 }
						 return 1;
				}
				else
				{
// send further on network
				 npci[0]=0x01;
				 npci[1]=0x10;
				 memcpy(&npci[2], &SNET, 2);
				 npci[4]=SADR[0];
				 length_npci = 5;
				}
			 }
			 else
			 {
//
//------------				if( DNET == NetworkAddress )
				if( DNET == j )
				{
				 // request on local network
				 npci[0]=0x01;
				 npci[1]=0x10;
				 memcpy(&npci[2], &SNET, 2);
				 npci[4]=SADR[0];
				 length_npci = 5;
				}
				else
				{
				 // request on other network
				 npci[1]=0x50;
				 memcpy(&npci[2], &DNET, 2);
				 npci[4]=DADR[0];
				 memcpy(&npci[5], &SNET, 2);
				 npci[7]=SADR[0];
				 npci[8]=HopCount;
				 length_npci = 9;
				}
			 }
			 if(!(Routing_table[i].status^PTP_ACTIVE))
			 {
				 ((class PTP *)Routing_table[i].ptr)->sendframe(length_npci, npci, length_asdu_npdu-n, &asdu_npdu[n]);
			 }
			 if( (Routing_table[i].status&RS485_ACTIVE)==RS485_ACTIVE )
			 {
					// build frame
					nextentry = ((class MSTP *)Routing_table[i].ptr)->SendFramePool.NextFreeEntry();
					if( nextentry >= 0 )
					{
					pframe = &((class MSTP *)Routing_table[i].ptr)->SendFramePool.Frame[nextentry];
					if( !data_expecting_reply )
						pframe->FrameType = (DADR[0]==255?BACnetDataNotExpectingReply:BACnetDataExpectingReply);
					else
						pframe->FrameType = data_expecting_reply;

					switch (asdu_npdu[n]>>4){    /*0+n*/
								case BACnetUnconfirmedRequestPDU:
								case BACnetAbortPDU:
										pframe->FrameType = BACnetDataNotExpectingReply;
										break;
								case BACnetSegmentACKPDU:
										if(asdu_npdu[n+9]==BACnetDataNotExpectingReply)  /*9+n*/
											pframe->FrameType = BACnetDataNotExpectingReply;
										break;
					}

					pframe->Destination = DADR[0];
					pframe->Source = TS;           //SADR[0];
					pframe->Length = length_npci+length_asdu_npdu-n;
					memcpy(pframe->Buffer, npci, length_npci);
					memcpy(&pframe->Buffer[length_npci], &asdu_npdu[n],  length_asdu_npdu-n);
//					((class MSTP *)Routing_table[i].ptr)->SendFramePool.Unlockhead();
					((class MSTP *)Routing_table[i].ptr)->SendFramePool.status[nextentry]=1;
					}
			 }
#ifdef NET_BAC_COMM
			 if( (Routing_table[i].status & IPX_ACTIVE) == IPX_ACTIVE ||
					 (Routing_table[i].status & TCPIP_ACTIVE) == TCPIP_ACTIVE )
			 {
					// build frame
					pframe = (FRAME *)((class NET_BAC *)Routing_table[i].ptr)->SendFramePool.NextFreeEntry(0);
					if( pframe != NULL )
					{
						if( !data_expecting_reply )
							pframe->FrameType = (DADR[0]==255?BACnetDataNotExpectingReply:BACnetDataExpectingReply);
						else
							pframe->FrameType = data_expecting_reply;
						pframe->Destination = DADR[0];
						pframe->Source = Station_NUM;           //SADR[0];
						pframe->Length = length_npci+length_asdu_npdu-n;
						memcpy(pframe->Buffer, npci, length_npci);
						memcpy(&pframe->Buffer[length_npci], &asdu_npdu[n],  length_asdu_npdu-n);
						((class NET_BAC *)Routing_table[i].ptr)->SendFramePool.Unlock_frame(
																									 (SEND_FRAME_ENTRY*)pframe );
						resume( ((class NET_BAC *)Routing_table[i].ptr)->task_number );
					}
			 }
#endif
			 break;
			}
			else
			{
			 if(HopCount)
				for(j=0; j<MAX_reachable_networks; j++)
				 if( ((Routing_table[i].Port.networks_list[j].status&REACHABLE) == REACHABLE) &&
						Routing_table[i].Port.networks_list[j].network==DNET)
				 {
					 if( SNET==(( class ConnectionData *)Routing_table[i].ptr)->panel_info1.network && SADR[0]==Station_NUM )
					 {  // i sent the request; call the server
						if( clientserver&0x0FF == CLIENT )
						{
						 ClientTSMTable.received(DADR[0], SADR[0], &asdu_npdu[n], length_asdu_npdu-n);
						}
						else
						{
						 network = SNET;
						 ServerTransactionStateMachine(port, network, DADR[0], SADR[0],
							&asdu_npdu[n], length_asdu_npdu-n, -1, i );
						}
						Routing_table[i].Port.networks_list[j].status = UNREACHABLE;
            setunreachabil = DNET;
            break;
					 }
					 if(!(Routing_table[i].status^PTP_ACTIVE))
					 {
						 npci[1]=0x50;
						 memcpy(&npci[2], &DNET, 2);
						 npci[4]=DADR[0];
						 memcpy(&npci[5], &SNET, 2);
						 npci[7]=SADR[0];
						 npci[8]=HopCount;
						 ((class PTP *)Routing_table[i].ptr)->sendframe(9, npci, length_asdu_npdu-n, &asdu_npdu[n]);
					 }
					 else
					 {
						if( (Routing_table[i].status & IPX_ACTIVE) == IPX_ACTIVE ||
								(Routing_table[i].status & RS485_ACTIVE) == RS485_ACTIVE )
						{
						 npci[1]=0x50;
						 memcpy(&npci[2], &DNET, 2);
						 npci[4]=DADR[0];
						 memcpy(&npci[5], &SNET, 2);
						 npci[7]=SADR[0];
						 npci[8]=HopCount;
						 length_npci = 9;
						 if( (Routing_table[i].status&RS485_ACTIVE)==RS485_ACTIVE )
						 {
					// build frame
							nextentry = ((class MSTP *)Routing_table[i].ptr)->SendFramePool.NextFreeEntry();
							if( nextentry >= 0 )
							{
							pframe = &((class MSTP *)Routing_table[i].ptr)->SendFramePool.Frame[nextentry];
							if( !data_expecting_reply )
								pframe->FrameType = (DADR[0]==255?BACnetDataNotExpectingReply:BACnetDataExpectingReply);
							else
								pframe->FrameType = data_expecting_reply;
							pframe->Destination = DADR[0];
							pframe->Source = TS;           //SADR[0];
							pframe->Length = length_npci+length_asdu_npdu-n;
							memcpy(pframe->Buffer, npci, length_npci);
							memcpy(&pframe->Buffer[length_npci], &asdu_npdu[n],  length_asdu_npdu-n);
//					((class MSTP *)Routing_table[i].ptr)->SendFramePool.Unlockhead();
							((class MSTP *)Routing_table[i].ptr)->SendFramePool.status[nextentry]=1;
							}
						 }
#ifdef NET_BAC_COMM
						 if( (Routing_table[i].status & IPX_ACTIVE) == IPX_ACTIVE ||
								 (Routing_table[i].status & TCPIP_ACTIVE) == TCPIP_ACTIVE )
						 {
					// build frame
							pframe = (FRAME *)((class NET_BAC *)Routing_table[i].ptr)->SendFramePool.NextFreeEntry(0);
							if( pframe != NULL )
							{
								if( !data_expecting_reply )
									pframe->FrameType = (DADR[0]==255?BACnetDataNotExpectingReply:BACnetDataExpectingReply);
								else
									pframe->FrameType = data_expecting_reply;
								pframe->Destination = DADR[0];
								pframe->Source = Station_NUM;           //SADR[0];
								pframe->Length = length_npci+length_asdu_npdu-n;
								memcpy(pframe->Buffer, npci, length_npci);
								memcpy(&pframe->Buffer[length_npci], &asdu_npdu[n],  length_asdu_npdu-n);
								((class NET_BAC *)Routing_table[i].ptr)->SendFramePool.Unlock_frame(
																										 (SEND_FRAME_ENTRY*)pframe );
								resume( ((class NET_BAC *)Routing_table[i].ptr)->task_number );
							}
						 }
#endif
						}
					 }
					 break;
				 }
			}
		 }
		}
		if( (Routing_table[port].status&RS485_ACTIVE)==RS485_ACTIVE )
		{
				// build frame response postpond
				 if(replyflag==1)
				 {
					pframe = (FRAME *)&ServerBuffer;
					pframe->FrameType = ReplyPostponed;
					pframe->Destination = source;
					pframe->Source = TS;
					pframe->Length = 0;
					replyflag=2;
				 }
		}
	 }
	}
 }
}

int checkTSMtimeout(int update)
{
 int	n = 10000;
	for(int i=0; i<MAXServerTSMTable; i++)
	{
	 if( ServerTSMTable.table[i].state != STSM_ILLEGAL )
	 {
		if ( ServerTSMTable.table[i].timeout < n ) {n = ServerTSMTable.table[i].timeout; };
	 }
	}
	if(update>0)
	{
	 if(n!=10000)
	 {
		for(int i=0; i<MAXServerTSMTable; i++)
		{
		 if( ServerTSMTable.table[i].state != STSM_ILLEGAL )
		 {
			ServerTSMTable.table[i].timeout -= n;
			if( ServerTSMTable.table[i].timeout < 0 ) ServerTSMTable.table[i].timeout = 0 ;
		 }
		}
//		n=0;
	 }
	}
	return n;
}

void ServerTSM(void)
{
 int n, j;
 char apdu[MAXAPDUSIZE];
// suspend(SERVERTSM);
 while(1)
 {
	while(1)
	{
	 for(int i=0; i<MAXServerTSMTable; i++)
	 {
		STSMremoveflag=1;
		if( ServerTSMTable.table[i].state != STSM_ILLEGAL )
		{
		 if( ServerTSMTable.table[i].timeout <= 0 )
		 {
			j = i;
			ServerTransactionStateMachine( 0, 0, 0, 0, apdu, 0, i);
		 }
		}
		STSMremoveflag=0;
	 }
	 STSMremoveflag=1;
	 n = checkTSMtimeout(1);
	 STSMremoveflag=0;
	 if (n>0) break;
	}
	if( n == 10000 )
		suspend(SERVERTSM);
	else
		msleep(n);
 }
}

unsigned char CalcHeaderCRC(unsigned char dataValue, unsigned char crcValue)
{
 unsigned int crc;
 crc = crcValue ^ dataValue;
 crc = crc ^ (crc<<1) ^ (crc<<2) ^ (crc<<3)
			  ^ (crc<<4) ^ (crc<<5) ^ (crc<<6) ^ (crc<<7);
 return (crc&0xfe) ^ ((crc >> 8)&1);
}

unsigned int CalcDataCRC(unsigned char dataValue, unsigned int crcValue)
{
 unsigned int crcLow;
 crcLow = (crcValue & 0xff) ^ dataValue;
 return (crcValue >> 8) ^ (crcLow<<8) ^ (crcLow<<3) ^ (crcLow<<12)
			  ^ (crcLow>>4) ^ (crcLow&0x0f) ^ ((crcLow&0x0f) << 7);
}

int compressdata(char *dest, int length_dest, char *source, int length_source, int *l)
{
/*
 int r;
 length_dest -= 10;
 char x;
 x = *source;
 *source = *(source+1);
 *(source+1) = x;
 GifEncoder enc( 8, dest+2, length_dest);
 enc.init();
 *l=enc.encode( source, length_source);
 enc.term();
 r = enc.bytecnt;
 if( r > 0 )
 {
	memcpy(dest, &r, 2);
 }
 dest[r++] = 0;
 dest[r++] = 0;
 dest[r++] = 0x3b;

 x = *source;
 *source = *(source+1);
 *(source+1) = x;
 return r;
*/
}

int uncompress(char *dest, int length_dest, char *source, int length_source)
{
/*
 int l;
 GifDecoder dec( 8, source, length_source);
 dec.init();
 l=dec.decode( dest, length_dest);
 dec.term();
 return l;
*/
}


