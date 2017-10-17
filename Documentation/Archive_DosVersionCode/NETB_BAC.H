/******************************************************************/
/*                                                                */
/* 							NETB_BAC.H                                         */
/*                                                                */
/******************************************************************/
#ifndef _NETB_BAC_H
#define _NETB_BAC_H

#include "net_bac.h"

#define NcbQueueSize          12

/* Symbolic names for NetBIOS commands  */

#define RESET_CMD                       0x032
#define CANCEL                          0x035
#define UNLINK                          0x070
#define STATUS                          0x0b3
#define STATUS_WAIT                     0x033
#define TRACE                           0x0f9
#define TRACE_WAIT                      0x079
#define ADD_NAME                        0x0b0
#define ADD_NAME_WAIT                   0x030
#define ADD_GROUP_NAME                  0x0b6
#define ADD_GROUP_NAME_WAIT             0x036
#define DELETE_NAME                     0x0b1
#define DELETE_NAME_WAIT                0x031
#define CALL                            0x090
#define CALL_WAIT                       0x010
#define LISTEN                          0x091
#define LISTEN_WAIT                     0x011
#define HANG_UP                         0x092
#define HANG_UP_WAIT                    0x012
#define SEND                            0x094
#define SEND_WAIT                       0x014
#define SEND_NO_ACK                     0x0f1
#define SEND_NO_ACK_WAIT                0x071
#define CHAIN_SEND                      0x097
#define CHAIN_SEND_WAIT                 0x017
#define CHAIN_SEND_NO_ACK               0x0f2
#define CHAIN_SEND_NO_ACK_WAIT          0x072
#define RECEIVE                         0x095
#define RECEIVE_WAIT                    0x015
#define RECEIVE_ANY                     0x096
#define RECEIVE_ANY_WAIT                0x016
#define SESSION_STATUS                  0x0b4
#define SESSION_STATUS_WAIT             0x034
#define SEND_DATAGRAM                   0x0a0
#define SEND_DATAGRAM_WAIT              0x020
#define SEND_BROADCAST_DATAGRAM         0x0a2
#define SEND_BROADCAST_DATAGRAM_WAIT    0x022
#define RECEIVE_DATAGRAM                0x0a1
#define RECEIVE_DATAGRAM_WAIT           0x021
#define RECEIVE_BROADCAST_DATAGRAM      0x0a3
#define RECEIVE_BROADCAST_DATAGRAM_WAIT 0x023

#define NETBIOS_INVALID_COMMAND         0x07F
#define ERROR_INVALID_COMMAND           0x003

class NetBios_Bac;

/* Network Control Block (NCB)  */
typedef struct
	 {
	 byte NCB_COMMAND;               /* command id                         */
	 byte NCB_RETCODE;               /* immediate return code              */
	 byte NCB_LSN;                   /* local session number               */
	 byte NCB_NUM;                   /* network name number                */
	 void far *NCB_BUFFER_PTR;       /* address of message packet          */
	 uint NCB_LENGTH;                /* length of message packet           */
	 byte NCB_CALLNAME[16];          /* name of the other computer         */
	 byte NCB_NAME[16];              /* our network name                   */
	 byte NCB_RTO;                   /* receive time-out in 500 ms. incrs. */
	 byte NCB_STO;                   /* send time-out - 500 ms. increments */
	 void interrupt (NetBios_Bac::*POST_FUNC)(__CPPARGS); /* address of POST routine         */
	 byte NCB_LANA_NUM;              /* adapter number (0 or 1)            */
	 byte NCB_CMD_CPLT;              /* final return code                  */
	 byte NCB_RESERVE[16];           /* Reserved area                      */
	 unsigned in_use     : 4;      /* extra parameters used to indicate if the NCB
																		is used or not; == 0 => not used, != 0 => in use */
	 unsigned index      : 3;     /* command associated with this NCB */
	 unsigned tyepe      : 1;     /* command type associated with this NCB */
	 }
	 NCB;

typedef struct {
			unsigned char   card_id[6];
		  unsigned char   release_level;
			unsigned char   reserved1;
		  unsigned char   type_of_adapter;
			unsigned char   old_or_new_parameters;
		  unsigned int    reporting_period_minutes;
			unsigned int    frame_reject_recvd_count;
		  unsigned int    frame_reject_sent_count;
		  unsigned int    recvd_frame_errors;
			unsigned int    unsuccessful_transmissions;
		  unsigned long   good_transmissions;
		  unsigned long   good_receptions;
		  unsigned int    retransmissions;
		  unsigned int    exhausted_resource_count;
			unsigned int    t1_timer_expired_count;
			unsigned int    ti_timer_expired_count;
		  char            reserved2[4];
		  unsigned int    available_ncbs;
			unsigned int    max_ncbs_configured;
		  unsigned int    max_ncbs_possible;
			unsigned int    buffer_or_station_busy_count;
			unsigned int    max_datagram_size;
			unsigned int    pending_sessions;
			unsigned int    max_sessions_configured;
			unsigned int    max_sessions_possible;
			unsigned int    max_frame_size;
			int             name_count;
			struct {
				char            tbl_name[16];
				unsigned char   tbl_name_number;
				unsigned char   tbl_name_status;
				} name_table[20];
			}
			ADAPTER_DATA;

typedef struct {
			unsigned char  name_num;
			unsigned char  session_count;
			unsigned char  junk1;
			unsigned char  junk2;
//		  A_SESSION      session_data[40];
			}
			STATUS_INFO;

class NetBios_Bac : public NET_BAC
{

	NCB far  			  		*ncb_array;
	unsigned int        real_ncb_DS;

	private:

		void interrupt command_post(__CPPARGS);
		uint adapter_status( byte ncb , char *remotename, uint real_data_segment );

//		void set_panel_name( char *name, byte dest );
		int  NetBios_call( uint ncb_index );

		uint adapter_status( byte ncb , char *remotename );
		uint send_datagram( byte ncb, char *mess, uint length, byte index, char *name );
		uint receive_datagram( byte ncb, char *buffer, byte index, byte type );
		uint add_name( byte ncb, char *name, byte type );
		uint delete_name( byte ncb, char *name );
		uint cancel( byte ncb, NCB *ptr );

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

	NetBios_Bac( Panel_info1 *info, byte task_no );

	int GetLocalAddress( void );
	int CloseCommunication( void );
	int OpenCommunication( void );

//	void delete_names( void );
	int reset_adapter( void );

	~NetBios_Bac();
};

#endif //_NETB_BAC_H


