#ifndef _RS485_H

#define _RS485_H

#include "serial.h"
#include "baseclas.h"
//  0000 0xxx   BACnetPDU type
//  0000 x000   sign;
//  000x 0000   compress;
#define NETCALL_BACnetPduType     0x07
#define NETCALL_SIGN              0x08
//#define NETCALL_COMPRESS          0x10
#define NETCALL_NOTTIMEOUT        0x10
#define NETCALL_NOTCTRLBREAK      0x20
#define NETCALL_NOTCHANGENETADR   0x40
//#define NETCALL_IAMPANELOFF       0x80
#define NETCALL_SOURCE255         0x80
#define NETCALL_RETRY             0x0100
#define NETCALL_CHECKDUPLICATE    0x0200
#define NETCALL_WRITERETRY        0x0400

//#define MAX_FRAME_SIZE				500
//#define MAX_QUEUE_ENTRIES 			1
//#define MAX_APDU_LENGTH          400
#define NMAXFRAMEPOOL				  1
#define PTP_NMAXRECEIVEDFRAMEPOOL  3
#define PTP_NMAXSENDFRAMEPOOL      4          

#define	N_RETRIES			1
//#define	T_CONN_REQ		15000		/* MILI_SEC */
#define	T_CONN_REQ		   273
//#define	T_CONN_RSP		15000		/* MILI_SEC */
#define	T_CONN_RSP		   273		// ticks
//#define	T_FRAME_ABORT	2000		/* MILI_SEC */
#define	PTP_Tframe_abort 37
//#define	T_HEARTBEAT		15000		/* MILI_SEC */
#define	T_HEARTBEAT		   273      //ticks
//#define	T_INACTIVITY	60000		/* MILI_SEC */
#define	T_INACTIVITY	   1190     // ~ 1min 30sec
//#define	T_RESPONSE		5000		/* MILI_SEC */
#define	T_RESPONSE		   91
/* #define	T_SILENCE */

#define ABSENT                  -1
#define ILLEGAL                 -1
#define STSM_ILLEGAL            -1
#define CTSM_ILLEGAL            -1
#define LOCALNETWORK            -1
#define BROADCAST           0xFFFF

#define TIMERESOLUTION    6.865686

#define SENDINFO_IAMPANELOFF 0x01
#define READYFORDES          0x02
#define LASTSTCONNECTED      0x04
#define FIRSTTOKEN           0x08
#define SENDINFO_PANELOFF    0x10
#define SENDINFO_TIME        0x20
#define SENDINFO_IAMONNET    0x40
// TS "This Station", node address
// NS "Next Station", node address
// PS "Poll Station", node address
#define NMAX_INFO_FRAMES          1
#define NMAX_MASTER              32   //127
#define NMAX_POLL                50
#define NRETRY_TOKEN              2
#define NMIN_OCTETS               4
#define TFRAME_ABORT             40
#define TFRAME_GAP               15
#define TNO_TOKEN               500
#define TPOSTDRIVE                1
#define TREPLY_DELAY            270    //250 
#define TREPLY_TIMEOUT          300    //255
#define TROFF                     1
#define TSLOT                    15    //10
#define TTURNAROUND              10
#define TUSAGE_DELAY             15
#define TUSAGE_TIMEOUT           50    //20

#define WINDOWSIZE                1

#define MAXFRAMEBUFFER          490
#define MAXFRAME                (8+MAXFRAMEBUFFER+2+1)
#define MAXAPDUSIZE             (MAXFRAMEBUFFER-40)
#define MAXAPCI                 40
#define MAXASDUSIZE             (MAXAPDUSIZE-MAXAPCI)

#define MSTP_NMAXRECEIVEDFRAMEPOOL  2
#define MSTP_NMAXSENDFRAMEPOOL      6        

#define MAXServerTSMTable      5
#define MAXClientTSMTable      4

typedef enum {CLIENT, SERVER} ServiceSource;

typedef enum {DL_UNITDATArequest, DL_UNITDATAindication} DATALINKPrimitive;
typedef enum {N_UNITDATArequest, N_UNITDATAindication} NETWORKPrimitive;

typedef enum {NORMALmessage, URGENTmessage, CRITICALEQUIPTMENTmessage, LIFESAFETYmessage } NetworkPriority;

typedef enum { CONF_SERVrequest, CONF_SERVindication, CONF_SERVresponse, CONF_SERVconfirm,
					UNCONF_SERVrequest, UNCONF_SERVindication, ERRORrequest, ERRORindication,
					REJECTrequest, REJECTindication, SEGMENT_ACKrequest,  SEGMENT_ACKindication,
					ABORTrequest, ABORTindication } ServicePrimitive;

typedef enum { APFLOWCONTROL, AEFLOWCONTROL } FlowControl;

typedef enum { BACnetConfirmedRequestPDU, BACnetUnconfirmedRequestPDU, BACnetSimpleACKPDU,
					BACnetComplexACKPDU, BACnetSegmentACKPDU, BACnetErrorPDU, BACnetRejectPDU,
					BACnetAbortPDU } BACnetPDU;

typedef enum { acknowledgeAlarm, confirmedCOVNotification, confirmedEventNotification,
					getAlarmSummary, getEnrollmentSummary, subscribeCOV, atomicReadFile, atomicWriteFile,
					addListElement, removeListElement, createObject, deleteObject, readProperty,
					readPropertyConditional, readPropertyMultiple, writeProperty, writePropertyMultiple,
					deviceCommunicationControl, confirmedPrivateTransfer, confirmedTestMessage,
					reinitializeDevice, vtOpen, vtClose, vtData, authenticate, requestKey
					} BACnetConfirmedServiceChoice;

typedef enum { AcknowledgeAlarm, ConfirmedCOVNotification, ConfirmedEventNotification,
					GetAlarmSummary, GetEnrollmentSummary, SubscribeCOV, AtomicReadFile, AtomicWriteFile,
					AddListElement, RemoveListElement, CreateObject, BACDeleteObject, ReadProperty,
					ReadPropertyConditional, ReadPropertyMultiple, WriteProperty, WritePropertyMultiple,
					DeviceCommunicationControl, ConfirmedPrivateTransfer, ConfirmedTestMessage,
					ReinitializeDevice, VtOpen, VtClose, VtData, Authenticate, RequestKey
					} BACnetConfirmedServiceRequest;

typedef enum { iAm, iHave, unconfirmedCOVNotification, unconfirmedEventNotification,
					unconfirmedPrivateTransfer, unconfirmedTestMessage, timeSyncronization,
					whoHas, whoIs } BACnetUnconfirmedServiceChoice;

typedef enum { IAm, IHave, UnconfirmedCOVNotification, UnconfirmedEventNotification,
					UnconfirmedPrivateTransfer, UnconfirmedTestMessage, TimeSyncronization,
					WhoHas, WhoIs } BACnetUnconfirmedServiceRequest;

typedef enum {ANALOG_INPUT, ANALOG_OUTPUT, ANALOG_VALUE,
				  BINARY_INPUT, BINARY_OUTPUT, BINARY_VALUE,
				  CALENDAR, CLASS, COMMAND, DEVICE, EVENT_ENROLLMENT,
				  BAC_FILE, GROUP, LOOP, MULTISTATE_INPUT, MULTISTATE_OUTPUT,
				  BAC_PROGRAM, SCHEDULE, T3000_OBJECT_TYPE=64 } BACnetObjectType;

typedef enum {OPERATIONAL, OPERATIONAL_READ_ONLY, DOWNLOAD_REQUIRED,
				  DOWNLOAD_IN_PROGRESS, NON_OPERATIONAL} BACnetDeviceStatus;

typedef enum {} BACnetServicesSupported;
typedef enum {} BACnetObjectTypesSupported;

typedef enum {SEGMENTED_BOTH, SEGMENTED_TRANSMIT, SEGMENTED_RECEIVE, NO_SEGMENTATION} BACnetSegmentation;

typedef enum {OTHER, BUFFEROVERFLOW, INVALIDAPDUINTHISSTATE, PREEMTEDBYHIGHERPRIORITYTASK,
				  SEGMENTATIONNOTSUPPORTED } BACnetAbortReason;


typedef struct {
		unsigned instance              :14;
		unsigned object_type_low       :2;
		unsigned object_type_hi        :7;
		unsigned proprietary           :1;  // 0=standard; 1=proprietary
	} BACnetObjectIdentifier;

typedef struct {
	char hour;
	char minute;
	char second;
	char hundredths;
} Time;

typedef struct {
	char year;
	char month;
	char dayofmonth;
	char dayofweek;
} Date;

typedef struct {
	} BACnetAddress;

typedef union {
	  BACnetObjectIdentifier device;
	  BACnetAddress          address;
	} BACnetRecipient;

typedef struct {
	} BACnetRecipients;

typedef struct {
	} BACnetAddressBinding;

typedef struct {
	BACnetObjectIdentifier     Object_Identifier;
	char                       Object_Name[22];
	BACnetObjectType           Object_Type;
	BACnetDeviceStatus         System_Status;
	char                       Vendor_Name[16];
	unsigned int               Vendor_Identifier;
	char                       Model_Name[8];
	char                       Firmware_Revision[8];
	char                       Application_Software_Version[21];
	char						      Location[21];
	char						      Description[21];
	char                       Protocol_Version;
	char                       Protocol_Conformance_Class;
	BACnetServicesSupported     Protocol_Services_Supported;
	BACnetObjectTypesSupported  ProtocolObjectTypesSupported;
//	BACnetObjectIdentifier    Object_List[N];
	unsigned int					Max_APDU_Length_Supported;
	BACnetSegmentation         Segmentation_Supported;
	Time                       Local_Time;
	Date                       Local_Date;
	int                        UTC_Offset;
	char                       Daylight_Savings_Status;
	unsigned int               APDU_Segment_Timeout;
	unsigned int               APDU_Timeout;
	char                       Number_of_APDU_Retries;
	BACnetRecipients           Time_Syncronizaton_Recipients;
	unsigned int               Max_Master;
	unsigned int               Max_Info_Frames;
	BACnetAddressBinding       Device_Address_Binding;
 } BACnetDevice;


typedef enum { Token=0, PollForMaster, ReplyToPollForMaster, TestRequest, TestResponse,
					BACnetDataExpectingReply, BACnetDataNotExpectingReply, ReplyPostponed
				 } FrameTypeEnum;

typedef enum { MSTP_MASTER_IDLE, MSTP_MASTER_USE_TOKEN, MSTP_MASTER_WAIT_FOR_REPLY,
					MSTP_MASTER_DONE_WITH_TOKEN, MSTP_MASTER_PASS_TOKEN, MSTP_MASTER_NO_TOKEN,
					MSTP_MASTER_POLL_FOR_MASTER, MSTP_MASTER_ANSWER_DATA_REQUEST } MSTP_MASTERStateEnum;

typedef enum { CTSM_IDLE, CTSM_SEGMENTING_REQUEST, CTSM_AWAIT_CONFIRMATION,
					CTSM_AE_SEGMENTED_CONFIRMATION }	ClientTSMStateEnum;

typedef enum { STSM_IDLE, STSM_SEGMENTING_REQUEST, STSM_AWAIT_RESPONSE, STSM_SEGMENTING_RESPONSE
				 }	ServerTSMStateEnum;

typedef struct {
	  unsigned int Preamble;
	  byte FrameType;
		byte Destination;
	  byte Source;
	  unsigned int Length;
	  byte HeaderCRC;
	  char Buffer[MAXFRAMEBUFFER+2+1];  //2-CRC , 1-'FF'
	 } FRAME;

typedef struct
{
	int  				service;
	int 				network;
	int 				destination;
	int 				source;
	char 				*apci;
	unsigned int   length_apci;
	char 				*asdu;
	char 				*npdu;
	unsigned int   length;
	int 				port;
	char 				*semaphore;
	unsigned priority						:2;
	unsigned data_expecting_reply		:1;
	unsigned clientserver       		:1;
	unsigned AtoN							:1;
	unsigned DtoN							:1;
	unsigned NtoA							:1;
	unsigned NtoD							:1;
} NL_PARAMETERS;

struct CTSMTable {
	 signed char        state;
	 int                task;
	 int  		          network;
	 int  		          destination;
	 int  		          source;
	 unsigned char      invokeID;
	 ClientTSMStateEnum CTSM_State;
	 int  		          others;
//	 char 		     noseq;
//	 char 		     retrycount;
//	 int  		     timeout;
	 char               data[MAXFRAME];    // read data parameters
	 unsigned			      LengthReceivedClientAPDU;
//	 unsigned      length;              //length of data to be send
//	 unsigned 	   last_length;         //length of last segment(s)
//	 char     	   noseg;               //no of segs received
//	 char     	   windowsize;
//	 int      	   entitysize;
//	 char     	   vendorID;
//	 char     	   command;
//	 int      	   arg;
//	 char     	   service;
//	 char          compressed;
} ;

class ClientTSMTable {
 public:
	struct CTSMTable table[MAXClientTSMTable];
 public:
	ClientTSMTable(void);
	int newentry(int task, int n, int d, int s, int id);
	void received(int s, int d, char *data, unsigned length);
	void free( int entry=-1 );
};

#ifdef RS485
unsigned client_entry;

ClientTSMTable::ClientTSMTable(void)
{
 for(int i=0; i<MAXClientTSMTable; i++)
 {
	table[i].state = CTSM_ILLEGAL;
	table[i].task  = CTSM_ILLEGAL;
	table[i].LengthReceivedClientAPDU=0;
 }
}

int ClientTSMTable::newentry(int task, int n, int d, int s, int id)
{
 int i;
 set_semaphore(&client_entry);
 for(i=0; i<MAXClientTSMTable; i++)
 {
	if(table[i].state == CTSM_ILLEGAL) break;
 }
 if (i<MAXClientTSMTable)
 {
	table[i].state                   = 0;
	table[i].task                    = task;
	table[i].network                 = n;
	table[i].destination             = d;
	table[i].source                  = s;
	table[i].invokeID                = id;
	table[i].LengthReceivedClientAPDU=0;
	table[i].CTSM_State              = CTSM_IDLE;
// table[i].noseq = 1;
// table[i].noseg = 0;
// table[i].length = 0;
// table[i].last_length = 0;
// table[i].windowsize  = WINDOWSIZE;
// table[i].compressed = 0;
// table[i].retrycount = 0;
 }
 else
	i=-1;
 clear_semaphore(&client_entry);
 return i;
}

void ClientTSMTable::received(int s, int d, char *data, unsigned length)
{
	 int j;
	 for(j=0; j<MAXClientTSMTable; j++)
	 {
				if(	!table[j].state )
				{
					if( s==table[j].source && d==table[j].destination )
					{
//						if( table[j].data[1]==table[j].invokeID )
						if( data[1]==table[j].invokeID )
						{
							memcpy(table[j].data, data, length);
						  table[j].LengthReceivedClientAPDU = length;
							table[j].state = 1;
							if( table[j].task >= 0 )
								resume(table[j].task);
            }
						break;
					}
				}
	 }
}

void ClientTSMTable::free( int entry )
{
 set_semaphore(&client_entry);
 if(entry>=0 && entry<MAXClientTSMTable )
 {
	table[entry].state = CTSM_ILLEGAL;
	table[entry].task  = CTSM_ILLEGAL;
 }
 clear_semaphore(&client_entry);
}
#endif

#ifdef RS485
//char sawtoken;
char  replyflag;
//int  LengthReceivedClientAPDU;
//char *PTRReceivedClientAPDU;
//unsigned int timerunMSTP=0xffff;

//int  		NetworkAddress=1;
char 		VendorID=1;
char 		RS485_RECEIVEFRAMEswitchflag;
//unsigned Timebetweentoken;
int      ServerTSM_flag=-1;

//byte     MSTP_Preamble1;
//byte     MSTP_Preamble2;
//byte 		MSTP_HeaderCRC;
//byte 		MSTP_FrameType;
//char 		MSTP_Destination;
//char 		MSTP_Source;
//unsigned MSTP_DataCRC;
//unsigned MSTP_DataLength;

//unsigned IndexBuffer;
//char 		Buffer[MSTP_MAXFRAMEBUFFER];
//char 		FrameCount;
//char     ReceiveError;
//int      EventCount;
//unsigned SilenceTimer;
//char     UsedToken;
//unsigned MSTP_EventCount;
//byte 		NS; 	// Next Station
//byte 		PS;    // Poll Station
  byte 		TS;    // This Station
//byte 		ReceivedInvalidFrame;
//byte 		ReceivedValidFrame;
//byte 		RetryCount;
//byte 		SoleMaster;
//byte 		TokenCount;

//FRAME 	frame={0x55FF};

byte 	Nmax_info_frames      = NMAX_INFO_FRAMES;
byte	Nmax_master           = NMAX_MASTER;
byte	NPoll                 = NMAX_POLL;
byte 	Nretry_token          = NRETRY_TOKEN;
byte 	Nmin_octets           = NMIN_OCTETS;
int  	Tframe_abort          = TFRAME_ABORT/TIMERESOLUTION;
byte 	Tframe_gap            = TFRAME_GAP;
int	  Tno_token             = TNO_TOKEN/TIMERESOLUTION;
int 	Tpostdrive            = TPOSTDRIVE;
int 	Treply_delay          = TREPLY_DELAY/TIMERESOLUTION;
int 	Treply_timeout        = TREPLY_TIMEOUT/TIMERESOLUTION;
int 	Troff                 = TROFF;
float	Tslot                 = TSLOT/TIMERESOLUTION;;
int 	Tturnaround           = TTURNAROUND/TIMERESOLUTION;
int 	Tusage_delay          = TUSAGE_DELAY;
int 	Tusage_timeout        = TUSAGE_TIMEOUT/TIMERESOLUTION;
int 	T_Inactivity          = T_INACTIVITY;

//HEADERStateEnum               MSTP_HEADERState;
//ReceiveFrameStatusEnum        MSTP_ReceiveFrameStatus=RECEIVE_FRAME_IDLE;
//MSTP_MASTERStateEnum          MSTP_MASTERState=MSTP_MASTER_IDLE;
//ClientTSMStateEnum            CTSM_State;

unsigned sendframepool_flag;
//char disable_485transmitter;
//char FirstToken;
int  laststation_connected=-1;
char ready_for_descriptors=0x01|0x04;   //0x01 read_des
													 //0x02 ; 0x04 start_read_des
//unsigned free_pool_index;

//byte 		MSTP_SendFrameType;
//char 		MSTP_SendDestination;
//char 		MSTP_SendSource;
//char ClientSA, ClientDA;
//char validint=0;
//int timeonnet, mstpnotrun=10000;
//int time_run_MSTP = 6000;

 ClientTSMTable ClientTSMTable;
//uint number_of_remote_points;

//long lost_connection;
 char reject;
//char disabletransmitter;
 char STSMremoveflag;
//Header_pool *ptr_h;
 int dtr;

#else
extern int  NetworkAddress;
extern char VendorID;
extern char RS485_RECEIVEFRAMEswitchflag;

//extern byte     	MSTP_Preamble1;
//extern byte     	MSTP_Preamble2;
//extern byte 		MSTP_HeaderCRC;
//extern byte 		MSTP_FrameType;
//extern byte 		MSTP_Destination;
//extern byte 		MSTP_Source;
//extern unsigned   MSTP_DataCRC;
//extern unsigned   MSTP_DataLength;
//extern unsigned int IndexBuffer;
//extern char Buffer[MSTP_MAXFRAMEBUFFER];
//extern char       ReceiveError;
//extern int        EventCount;
//extern unsigned   SilenceTimer;
//extern unsigned   MSTP_EventCount;
//extern byte 		MSTP_FrameCount;
//extern byte NS; 	// Next Station
//extern byte PS;    // Poll Station
	extern byte TS;    // This Station
//extern byte ReceivedInvalidFrame;
//extern byte ReceivedValidFrame;
//extern byte RetryCount;
//extern byte SoleMaster;
//extern byte TokenCount;

//extern FRAME frame;

extern byte Nmax_info_frames;
extern byte NPoll;
extern byte Nmax_master;
extern byte Nretry_token;
extern byte Nmin_octets;
extern int  Tframe_abort;
extern byte Tframe_gap;
extern int Tno_token;
extern int Tpostdrive;
extern int Treply_delay;
extern int Treply_timeout;
extern int Troff;
extern int Tslot;
extern int Tturnaround;
extern int Tusage_delay;
extern int Tusage_timeout;
extern int T_Inactivity;

//extern HEADERStateEnum               MSTP_HEADERState;
//extern ReceiveFrameStatusEnum        MSTP_ReceiveFrameStatus;
//extern MSTP_MASTERStateEnum          MSTP_MASTERState;
extern ClientTSMStateEnum            CTSM_State;
extern char disable_485transmitter;
extern char ready_for_descriptors;
//extern unsigned free_pool_index;
#endif

/*
class RECEIVEDFRAMEPOOL
{
 protected:
	signed char TailFrame;
	signed char HeadFrame;
	char overflow;
	char lockedhead;
 public:
	RECEIVEDFRAMEPOOL(void ){ TailFrame=HeadFrame=lockedhead=overflow=0;}
	void Clear(void){TailFrame=HeadFrame=lockedhead=overflow=0;}
	inline void Unlockhead(void){lockedhead=0;}
//	virtual int NextFreeEntry(void)=0;
};
*/

struct MSTP_ReceivedFrame {
	  FRAME Frame;
	  char  ReceivedValidFrame;
	  char  ReceivedInvalidFrame;
	  char  status;
};


class MSTP_RECEIVEDFRAMEPOOL
{
 public:
//	char  entry;
	struct MSTP_ReceivedFrame ReceivedFrame[MSTP_NMAXRECEIVEDFRAMEPOOL];
 public:
	MSTP_RECEIVEDFRAMEPOOL(void);
//	int NextFreeEntry(void);
	void *NextFreeEntry(void);
	int  RemoveEntry(MSTP_ReceivedFrame *frame);
};


class SENDFRAMEPOOL
{
 protected:
	signed char TailFrame;
	signed char HeadFrame;
	char overflow;
	char lockedhead;
	char access;

 public:
	SENDFRAMEPOOL(void) { TailFrame=HeadFrame=lockedhead=overflow=access=0;}
	void Clear(void){TailFrame=HeadFrame=lockedhead=overflow=access=0;}
	inline void Unlockhead(void){lockedhead=0;}
	int NextFreeEntry(void);
};

class MSTP_SENDFRAMEPOOL
{
 public:
	FRAME Frame[MSTP_NMAXSENDFRAMEPOOL];
	char  status[MSTP_NMAXSENDFRAMEPOOL];
	char  entry, access;
 public:
	MSTP_SENDFRAMEPOOL(void);
	int NextFreeEntry(void);
	int RemoveEntry(FRAME *buffer);
	int Query(void);
	void Empty(void);
  int CheckEntry(int dest, int source);
};

struct TSMTable {
	 signed char   state;
	 int  		   network;
	 int  		   destination;
	 int  		   source;
	 unsigned char invokeID;
	 char 		   noseq;
	 char 		   retrycount;
	 int  		   timeout;
	 unsigned      pool_index;
	 POOL          *ser_pool;
	 char          read_data[MAXASDUSIZE];    // read data parameters
	 char          *data;               	   // data
	 unsigned      length;              //length of data to be send
	 unsigned 	   last_length;         //length of last segment(s)
	 char     	   noseg;               //no of segs received
	 char     	   windowsize;
	 int      	   entitysize;
	 char     	   vendorID;
	 char     	   command;
	 int      	   arg;
   char          res;
	 char     	   service;
	 char          compressed;
	} ;

class ServerTSMTable {
 public:
  struct TSMTable table[MAXServerTSMTable];
 public:
  ServerTSMTable(void);
  int lookid(int n, int d, int s, char service, int id, POOL *spool);
  void free( int entry=-1, int n=0, int d=0, int s=0, int id=0);
  void resetsegments(int entry);
};

#ifdef RS485

ServerTSMTable::ServerTSMTable(void)
{
 for(int i=0; i<MAXServerTSMTable; i++)
  table[i].state = STSM_ILLEGAL;
}

void ServerTSMTable::resetsegments(int entry)
{
  table[entry].length += table[entry].last_length;
  table[entry].data -= table[entry].last_length;
  table[entry].noseq -= table[entry].windowsize;
  table[entry].last_length = 0;
  table[entry].noseg = 0;
}

int ServerTSMTable::lookid(int n, int d, int s, char service, int id, POOL *spool)
{
 int j;
 j=-1;
 for(int i=0; i<MAXServerTSMTable; i++)
 {
	if(table[i].state != STSM_ILLEGAL)
	{
	 if(table[i].invokeID == id)
	 {
		if(table[i].network==n && table[i].destination == d && table[i].source==s)
		return i;
	 }
	}
	else
	 if(j<0)
		j=i;
 }
 if (i==MAXServerTSMTable && j>=0)
 {
  i=j;
  table[i].network = n;
  table[i].destination = d;
	table[i].source = s;
  table[i].invokeID = id;
  table[i].service = service;
	table[i].state = STSM_IDLE;
  table[i].noseq = 1;
	table[i].noseg = 0;
//  table[i].length = MAXASDUSIZE;
  table[i].length = 0;
  table[i].last_length = 0;
  table[i].windowsize  = WINDOWSIZE;
//  table[i].pool_index = free_pool_index;
  table[i].pool_index = 0xFFFF;
  table[i].ser_pool   = spool;
  table[i].compressed = 0;
  table[i].retrycount = 0;
	return i;
 }
 return -1;
}

void ServerTSMTable::free( int entry, int n, int d, int s, int id)
{
 unsigned l;
 if(entry<0)
	for(entry=0; entry<MAXServerTSMTable; entry++)
	{
	 if(table[entry].state != STSM_ILLEGAL)
	 {
		if(table[entry].invokeID == id)
		{
		 if(table[entry].network==n && table[entry].destination == d && table[entry].source==s)
		 {
			break;
		 }
		}
	 }
	}
 if(entry>=0 && entry<MAXServerTSMTable )
 {
	table[entry].ser_pool->free(table[entry].pool_index);
	table[entry].state = STSM_ILLEGAL;
/*
	l = 0;
	for(entry=0; entry<MAXServerTSMTable; entry++)
	{
		if(table[entry].state != STSM_ILLEGAL)
		if(table[entry].pool_index > l) l = table[entry].pool_index;
	}
	free_pool_index = l;
*/
 }
}
#endif

class Serial;

class MSTP : public Serial
{
	public:
//		unsigned Timebetweentoken;
		int      ServerTSM_flag;
		byte 		RetryCount;
		byte 		SoleMaster;
		byte 		TokenCount;
		char 		FrameCount;
		char     UsedToken;
		byte task;
		MSTP_SENDFRAMEPOOL            SendFramePool;
		MSTP_RECEIVEDFRAMEPOOL        ReceivedFramePool;
		HEADERStateEnum               MSTP_HEADERState;
		ReceiveFrameStatusEnum        MSTP_ReceiveFrameStatus;
//		MSTP_MASTERStateEnum          MSTP_MASTERState;
	private:
		byte connection_state;

	public:
		MSTP( int c_port, int nr_port );
		void MSTP_Master_initialize(void);
		void sendpoints(char *asdu, char type);     //0 want_points, 1 network_points
//		void sendinfo(FRAME *frame, int status, int panel, int dest=255 );
		void SendFrame(FRAME *frame, char wait=0);
//		static int MSTP_receive_frame( MSTP *mstp );
		static int MSTP_Master_node( MSTP *mstp );
};

#ifdef RS485
//MSTP_SENDFRAMEPOOL     SendFramePool;
//MSTP_RECEIVEDFRAMEPOOL ReceivedFramePool;
char ClientBuffer[MAXFRAME];
char ServerBuffer[MAXFRAME];
class ServerTSMTable ServerTSMTable;
#else
//extern MSTP_RECEIVEDFRAMEPOOL RECEIVEDFramePool;
//extern MSTP_SENDFRAMEPOOL     SendFramePool;
extern char ClientBuffer[MAXFRAME];
extern ServerTSMTable ServerTSMTable;
#endif

#endif
