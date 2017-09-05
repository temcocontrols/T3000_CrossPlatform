//*********************************************************
//                                                        *
//       SEIAL.H - IN THIS HEADER ARE DEFINED ALL      	  *
//       TYPES AND CLASSES USED FOR SERIAL COMMUNICATIONS *
//                                                        *
//*********************************************************


#ifndef SERIAL_H

#define SERIAL_H

#include "PC8250.H"
#include "recdef.h"
#include "t3000def.h"
#include "modem.h"
#include "crc.h"
#include "_msdos.h"
#include "baseclas.h"
//#include "netbios.h"
#define DISCONNECT_TIME 33000
#define SERIAL_BUF_SIZE (long)MAX_SAMPLE*(long)MAX_INP*4L+MAX_INP*MAXSAMPLEUPDATE*4+MAX_MEM_DIG_BUF+400+MAX_HEADERS_AMON*sizeof(Header_amon)+MAX_HEADERS_DMON*sizeof(Header_dmon)+810
                        // 28000
typedef enum { BACKGND, FGND } Exec_mode;

typedef enum { UNUSED_MODE, BLOCK, SIMPLE, SPECIAL_COMMAND } Handling_mode;

typedef enum { MASTER, SLAVE, STOPED } Serial_mode;

typedef enum { LOCAL_PORT, MODEM_PORT } Port_type;

typedef enum { FREE, BUSY } Serial_activity;

typedef enum { T3000_FAIL = PC8250_NEXT_FREE_ERROR, T3000_DESTINATION_ERROR,
			T3000_SOURCE_ERROR, T3000_COMMAND_ERROR, T3000_CHECKSUM_ERROR,
			T3000_SYNC_ERROR, T3000_LENGTH_ERROR, CRC_BAD, COMM_ERROR,
			UNRECOVERABLE_ERROR, USER_ABORT, T3000_NEXT_FREE_ERROR,
			T3000_NEXT_FREE_WARNING = PC8250_NEXT_FREE_WARNING }
			T3000_ERROR;


typedef struct {
	unsigned position 	: 8;
	unsigned no_points 	: 7;
	unsigned bank_type	: 1;
	} Bank_Type;

/*
	ModemCapabilities	modem_cap;
	Modem 			modem( *port, modem_cap.name );
	ModemError		modem_status;
*/

class Serial : public ConnectionData
{
private:
	PanelType				partner;
	Connection_port	   conn_port;
	T3000_ERROR			   comm_status;
	uint 						partner_no;
	byte						PIC_mask;
	byte						RIB_out[6];
public:
	Serial_activity 				activity;
//	byte                 		port_number;
//	byte                 		com_port;
//	Media_type			   		media;
	byte								RIB_in[6];
	int                         direction;
//	char 								*ser_data;
//   POOL                       ser_pool;
	byte 								modem_active;
	byte 								modem_present;
//	task_id							task_number;
	byte 								connection_established;
	uint 								length_in;
	PC8250							*port;
	Port_Status					   port_status;
	Modem 							*modem_obj;
	ModemError					   modem_status;
	Exec_mode						ex_mode;
//	Serial_mode 				   mode;
//	Station_point 			      remote_list[ MAX_STATIONS ];

	Serial( byte c_port, int p_no );
	~Serial();

	void FlushRXbuffer();
	void FlushTXbuffer();
	void Set_mode( int mode );
	int  Read_mode( void );
	void Install_port();
	void Delete_port();
//	void Set_working_port( Port_type w_port );
	Serial_activity Get_activity( void );
	long ReadBaudRate( void );
//	char *Error_Name( RS232Error error );
	void Reset_PIC_mask();
	void Set_PIC_mask();

#ifdef PANELSTATION

	friend int execute_command( Media_type media,  Command_type comm,
													void *s_port, char *ser_data=NULL,
													struct TSMTable *ptrtable=NULL, int destport=-1 );
#endif

};

inline Serial_activity Serial::Get_activity( void ) { return activity; }

#endif // ifndef SERIAL_H
