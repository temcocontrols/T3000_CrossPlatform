#if defined(SERIAL_COMM) || defined(NETWORK)

#include <windows.h>
#include <graphics.h>
#include <dos.h>
#include <dir.h>
#include <string.h>
//#include "netbios.h"
#include "baseclas.h"
#include "mtkernel.h"
#include "graph.h"
#include "serial.h"
#include "aio.h"
#include "ggrid.h"
#include "rs485.h"
#include "router.h"
#include "ptp.h"

#define DELETE_ELEMENT 0
#define ADD_ELEMENT    1
#define UPDATE_ELEMENT 2

class GEdit;
extern Point_Net localopenscreen;
extern char GAlarm;
extern char Panel_Type;
extern unsigned long Active_Panels;
extern int NetworkAddress;
extern char pixul;
struct point_info_table {
		Point_info point_info;
		char *ontext;
		char *offtext;
		};
extern int printalarmproc(char *mes, int j);
extern void updatetimevars(void);
extern int	print(char *message);
extern int checkalarmentry(void);
//extern int checkforalarm(char *mes, int prg, int panel, int t=0);
extern int checkforalarm(char *mes, int prg, int panel, int id = 0 );
extern uint search_point( Point &point, char *buff, char * & point_adr,
																		uint & point_length, Search_type order );
extern int get_point(Point point, long *value, char **p);
extern unsigned long ReadTime( void );
extern int update_prg(char *buf, int ind_prg, char *code, Str_program_point *ptrprg, int panel, GEdit *pe=NULL);    // buff=0 local, #0 dist
extern int send_grp(int local, int index_obj, int current_grp, Str_grp_element *group_element, int curline=2, int curcol=1, int panel=0, int network=0, int elem_index=0);
extern void update_value_grp_elem(Str_grp_element *group_element, int nr_elements, int pri=0);
extern char *readmontable(int ind, int *length, long **mon_table, int type, char * = NULL);  //type = 1 retea, 2 serial  ; 0 local
extern char *newnetmem(int ind, int *, char * =NULL);
extern char *updatenetmemdig(int ind, int *length, char * = NULL);
extern int put_point_info(Point_info *point_info);
extern int	get_point_info(Point_info *point_info, char **des=NULL, char **label=NULL, char **ontext=NULL, char **offtext=NULL, char pri=0, int network = 0xFFFF);
//extern char * rtrim( char * );
extern void save_m(void);
extern void initanalogmon(void);
extern int getfiles(char *term, char (*files)[13], int nmax, int local);
extern int getdirectories(char *nname, char (*directories)[13], int nmax, int local);
extern void update_alarm_tbl(Alarm_point *block, int max_points_bank );

extern char printAlarms;
extern Time_block ora_current;
extern char user_name[16];
extern Station_point station_list[32];
extern Password_struct passwords;
//extern Password_point passwords[MAX_PASSW];
extern char * rtrim( char * );
extern char Station_NAME[NAME_SIZE];
extern int  Station_NUM;
//extern OPERATOR_LIST	ser_list[2];
//extern OPERATOR_LIST	operator_list;
extern int White;
extern Panel *ptr_panel;
//extern int connection_established;
extern Str_tbl_point custom_tab[MAX_TABS];
extern char control;
extern char carry_detect;
extern char sleep_modem;
extern char save_passwords, save_file, load_file, save_default,updatenet_flag;
extern char action;
extern char saveloadfilename[13];
extern char save_monitor_status;
extern char present_analog_monitor;
extern char save_monitor;
extern char save_monitor_command, save_monitor_status;
extern char monitor_accessed;
extern char *ptr_filetransfer;
extern long length_filetransfer;
extern char filetransfer_flag, filetransfer;
extern char huge filetransfername[65];
extern char save_prg_flag;
extern char int_disk1;
extern char check_annual_routine_flag;
extern char new_alarm_flag;
extern char _far sendtime, sendtime_ipx;

extern unsigned char tbl_bank[MAX_TBL_BANK];
extern unsigned update_t3000exe;
extern unsigned read_mon_flag;
extern unsigned long timesec1970;  // sec la inceputul programului
extern unsigned long timestart;    // sec de la inceputul programului
extern unsigned long  ora_current_sec; // ora curenta exprimata in secunde
extern Time_block ora_current;
extern struct time ora_start;         // ora la inceputul programului
extern int milisec;
extern long microsec;
extern Panel_info1 Panel_Info1;
extern char heap_grp_flag1, heap_grp_flag2;
extern char far Icon_name_table[MAX_ICON_NAME_TABLE][14];

extern char huge current_path[65],filename_tmp[65];
char term_tr[13];

//int execute_command( Media_type media, byte session, Command_type comm, Netbios *net_p,
//							void *s_port,	char *ser_data, struct TSMTable *ptrtable, int destport)
int execute_command( Media_type media, Command_type comm, void *s_port,
										 char *ser_data, struct TSMTable *ptrtable, int destport )
{
asm push es
	byte comm_code, ex_high=0;
	uint bank, res, n, len;
	char *data_pointer, *ptr, moved=0;
	uint length, entitysize=0;
	Bank_Type tbank;
	int i;
	long l;
	union {
	Serial *sr;
	ConnectionData *cd;
	} port_ptr;
	Point point;
/*
	if( media == SERIAL_LINK || media == MODEM_LINK)
	 ser_port = (class PTP *)s_port;
	if( media == RS485_LINK )
	 ser_port = (class MSTP *)s_port;
*/
	port_ptr.cd = (class ConnectionData *)s_port;
	port_ptr.sr = (class Serial *)s_port;

#ifdef NETWORK_COMM
	if( media == NETBIOS )
	{
		comm_code = net_p->ses_info[session].buffer[2] % 50;
		_fmemcpy( &bank, net_p->ses_info[session].buffer+3, 2);
		tbank = *(Bank_Type *)(net_p->ses_info[session].buffer+3);
	}
	else
#endif
	{
		comm_code =  ptrtable->command % 50;
		bank = ptrtable->arg;
		tbank = *((Bank_Type *)&ptrtable->arg);
	}
	if( !comm_code ) comm_code += 50;
	switch( comm_code )
	{
		case OUT+1:
		case IN+1:
		case VAR+1:
		case CON+1:
		case WR+1:
		case AR+1:
		case PRG+1:
		case GRP+1:
		case AY+1:
		{
			if( comm_code==CON+1 )
			{
			 Str_controller_point *pc;
			 pc = ptr_panel->controllers;
			 for(i=0; i<MAX_CONS;pc++,i++)
			 {
				 get_point(*((Point *)&pc->input), &pc->input_value, NULL);
				 get_point(*((Point *)&pc->setpoint), &pc->setpoint_value, NULL);
			 }
			}

			ptr = (char *)&ptr_panel->info[comm_code-1];
			entitysize = ((Info_Table *)ptr)->str_size;
			if( tbank.bank_type )
			{
				data_pointer = (char *)((Info_Table *)ptr)->address +
												tbank.position * ((Info_Table *)ptr)->str_size;
				length = ((Info_Table *)ptr)->str_size * tbank.no_points;
				n = tbank.no_points;
			}
			else
			{
				n = ptr_panel->table_bank[comm_code-1];
				length = ((Info_Table *)ptr)->str_size * n;
				data_pointer = (char *)((Info_Table *)ptr)->address + bank * length;
//								 ((Info_Table *)ptr)->str_size * ptr_panel->table_bank[comm_code-1][bank+1];
			}
/*
			if( comm_code == PRG+1 )
			{
			 Str_program_point *p, *q;
			 if( ptrtable->command > 100 )
			 {
				p = (Str_program_point *)ser_data;
				q = (Str_program_point *)data_pointer;
				for(i=0; i<n; i++)
					memcpy(&p->bytes, &q->bytes, 2);
			 }
			}
*/
			break;
		}
		case 8:
		{
			data_pointer = (char *)custom_tab;
			length = MAX_TABS*sizeof(Str_tbl_point);
			entitysize = sizeof( Str_tbl_point);
			break;
		}
		case 9:
		{
/*
			if( tbank.bank_type )
			{
				data_pointer = (char *)ptr_panel->digital_mon + tbank.position *
						sizeof( Str_digital_monitor_point );
				length = sizeof( Str_digital_monitor_point ) * tbank.no_points;
			}
			else
			{
				data_pointer = (char *)ptr_panel->digital_mon + bank *
						sizeof( Str_digital_monitor_point ) * ptr_panel->table_bank[8][bank+1];
				length = sizeof( Str_digital_monitor_point ) * ptr_panel->table_bank[8][bank+1];
			}
*/
			break;
		}
		case 10:
		{
			int vi, l;
			if( tbank.bank_type )
			{
					vi = tbank.position;
					l = tbank.no_points;
					data_pointer = (char *)ptr_panel->analog_mon + vi*sizeof( Str_monitor_point );
					length = sizeof( Str_monitor_point ) * l;
//					memmove( ser_port->ser_data, data_pointer, length );
			}
			else
			{
					l =  ptr_panel->table_bank[9];
					vi = bank * l;
					data_pointer = (char *)ptr_panel->analog_mon + vi * sizeof( Str_monitor_point );
					length = sizeof( Str_monitor_point ) * l;
			}
//			if( media == SERIAL_LINK || media == MODEM_LINK || media == RS485_LINK )
				if( ptrtable->command > 100 )
				{
				 if( length == ptrtable->length )
				 {
					if(!monitor_accessed)
					{
					 if(!read_mon_flag)
					 {
						present_analog_monitor=0;
						save_monitor = 0x01 | 0x02;
						save_monitor_command = 1;
						save_m();
						save_monitor_command=0;
						save_monitor_status = 0;

						data_pointer = ser_data;
						for(i=vi, ptr=(char *)&ptr_panel->analog_mon[vi]; i<(vi+l); i++, ptr += sizeof(Str_monitor_point))
						{
						 memmove((void *)ptr, data_pointer, sizeof(Str_monitor_point));
						 data_pointer +=  sizeof(Str_monitor_point);
						}
						initanalogmon();
						save_prg_flag = 1;
					 }
					}
				 }
				 asm pop es;
				 return 0;
				}
/*			if( media == SERIAL_LINK )
			{
#ifdef SERIAL_COMM
				memmove( ser_port->ser_data, data_pointer, length );
				data_pointer = ser_port->ser_data;
#endif
			}
*/
#ifdef NETWORK_COMM
			if( media == NETBIOS )
			{
				if( length > SES_BUF_LEN-8 ) net_p->ses_info[session].need_buffer = 1;
				if( comm == SEND_DATA )
				{
					memmove( net_p->ses_info[session].data, data_pointer, length );
					data_pointer = net_p->ses_info[session].data;
				}
			}
#endif
			break;
		}
/*
		case 11:
		{
			if( tbank.bank_type )
			{
				data_pointer = (char*)ptr_panel->control_groups + tbank.position *
						sizeof( Control_group_point ) * tbank.no_points;
				length = sizeof( Control_group_point ) * tbank.no_points;
			}
			else
			{
				data_pointer = (char*)ptr_panel->control_groups + bank *
						sizeof( Control_group_point ) * ptr_panel->table_bank[10][bank+1];
				length = sizeof( Control_group_point ) * ptr_panel->table_bank[10][bank+1];
			}
			break;
		}
		case 12:
		{
			if( tbank.bank_type )
			{
				data_pointer = (char *)ptr_panel->arrays + tbank.position *
																										sizeof( Str_array_point );
				length = sizeof( Str_array_point ) * tbank.no_points;
			}
			else
			{
				data_pointer = (char *)ptr_panel->arrays + bank *
										sizeof( Str_array_point ) * ptr_panel->table_bank[11][bank+1];
				length = sizeof( Str_array_point ) * ptr_panel->table_bank[11][bank+1];
			}
			break;
		}
*/
		case ALARMM+1:
		{
				data_pointer = (char*)ptr_panel->alarms;
//				length = MAX_ALARMS * sizeof(Alarm_point);
				length = ptr_panel->info[comm_code-1].str_size * ptr_panel->table_bank[comm_code-1];
				if( ptrtable->command > 100 )
				{
				 if( length == ptrtable->length )
				 {
					 update_alarm_tbl((Alarm_point *)ser_data, ptrtable->length / sizeof(Alarm_point));
				 }
				 asm pop es;
				 return 0;
				}
				else
				{
				 for(int i=0; i<MAX_ALARMS ;i++)
					ptr_panel->alarms[i].change_flag = 0;
				}
				break;
		}
		case UNIT+1:
		{
			data_pointer = (char *)ptr_panel->units;
			length = sizeof( Units_element ) * 8;
			break;
		}
/*
		case 15:
		{
			data_pointer = (char*)ptr_panel->system_name;
			length = 22;
			break;
		}
*/
		case READPROGRAMCODE_T3000:
		{
#ifdef NETWORK_COMM
		 if( media == NETBIOS  )
		 {
			if( comm == TRANSFER_DATA )
			{
				update_prg( net_p->ses_info[session].data, bank, NULL, NULL, Station_NUM );
			}
			if( comm == TRANSFER_COMMAND )
			{
				update_prg( net_p->ses_info[session].buffer+8, bank, NULL, NULL, Station_NUM );
			}
			if( comm == SEND_COMMAND )
			{
				len = 8;
				if( net_p->ses_info[session].ses_own == REMOTE )
					length = ptr_panel->programs[bank].bytes;
				if( net_p->ses_info[session].ses_own == LOCAL_OPERATOR )
					length = operator_list.length;
				_fmemcpy( (net_p->ses_info[session].buffer+6), (char*)&length, 2);
				net_p->ses_info[session].buffer[2] += 100;
				net_p->ses_info[session].buffer[5] = ptr_panel->lock[15];
				if( length < SES_BUF_LEN - 8 )
				{
					if( net_p->ses_info[session].ses_own == REMOTE )
						_fmemcpy( net_p->ses_info[session].buffer + 8, ptr_panel->program_codes[bank], length );
					if( net_p->ses_info[session].ses_own == LOCAL_OPERATOR )
						_fmemcpy( net_p->ses_info[session].buffer + 8, operator_list.buffer, length );
					len += length;
				}
				net_p->ses_info[session].state = SENDING_COMMAND;
				net_p->send( session, net_p->ses_info[session].buffer, len );
			}
			if( comm == SEND_DATA )
			{
				if( net_p->ses_info[session].ses_own == REMOTE )
				{
					length = ptr_panel->programs[bank].bytes;
					net_p->ses_info[session].data = ptr_panel->program_codes[bank];
				}
				if( net_p->ses_info[session].ses_own == LOCAL_OPERATOR )
				{
					_fmemcpy( &length, net_p->ses_info[session].buffer+6, 2 );
					net_p->ses_info[session].data = operator_list.buffer;
				}
				net_p->ses_info[session].state = SENDING_DATA;
				net_p->send( session, net_p->ses_info[session].data, length );
			}
		 asm pop es
			return 0;
		 }
		 else
#endif
		 {
#ifdef SERIAL_COMM
				if(ptrtable->command > 100)
				{
					update_prg( ser_data, bank, NULL, NULL, Station_NUM );
					save_prg_flag = 1;
					asm pop es
					return 0;
				}
				else
				{
				 length = ptr_panel->programs[bank].bytes;
				 data_pointer = ptr_panel->program_codes[bank];
				}
#endif
				break;
		 }
		}
		case WR_TIME+1:
		{
			if( tbank.bank_type )
			{
				data_pointer = (char *)ptr_panel->wr_times;
				length = 0;
			}
			else
			{
				data_pointer = (char *)ptr_panel->wr_times + bank * 9 *
																	sizeof( Wr_one_day );
				length = sizeof( Wr_one_day ) * 9;
			}
			break;
		}
		case AR_Y+1:
			if( tbank.bank_type )
			{
				data_pointer = (char *)ptr_panel->ar_dates;
				length = 0;
			}
			else
			{
				data_pointer = (char *)ptr_panel->ar_dates + bank * 46;
				length = 46;
			}
			break;
		case READGROUPELEMENTS_T3000:
		{
#ifdef NETWORK_COMM
			if( media == NETBIOS  )
			{
				if( comm == TRANSFER_COMMAND || comm == TRANSFER_DATA )
				{
					_fmemcpy( &length, net_p->ses_info[session].buffer+6, 2 );
				}
				if( comm == TRANSFER_COMMAND )
				{
					send_grp( 2, length / sizeof( Str_grp_element ), bank, ( Str_grp_element *)(net_p->ses_info[session].buffer+8) );
					asm pop es
					return 0;
				}
				if( comm == TRANSFER_DATA )
				{
					send_grp( 2, length / sizeof( Str_grp_element ), bank, ( Str_grp_element *)net_p->ses_info[session].data );
					asm pop es
					return 0;
				}
				data_pointer = (char *)ptr_panel->control_group_elements[bank].ptrgrp;
				length = ptr_panel->control_group_elements[bank].nr_elements * sizeof( Str_grp_element );
			}
			else
#endif
			{
#ifdef SERIAL_COMM
				if(ptrtable->command > 100)
				{
					send_grp( 2, ptrtable->length / sizeof( Str_grp_element ), bank, ( Str_grp_element *)(ser_data) );
					save_prg_flag = 1;
					asm pop es
					return 0;
				}
				else
				{
//				 Str_grp_element group_element;
				 Control_group_elements *grp;
				 if( !heap_grp_flag1 )
				 {
					heap_grp_flag2++;
					grp = &ptr_panel->control_group_elements[bank];
					length = ( grp->nr_elements ) * sizeof( Str_grp_element );
//				 if(media==RS485_LINK)
//					if( media == SERIAL_LINK || media == MODEM_LINK || media == RS485_LINK )
					{
					 if( !(l=port_ptr.cd->ser_pool.alloc(length)) )
					 {
						asm pop es;
						return 1;
					 }
					 else
					 {
						ser_data = port_ptr.cd->ser_data+l;
						ptrtable->pool_index = l;
					 }
					}
					update_value_grp_elem(grp->ptrgrp,grp->nr_elements,3);
					movedata( FP_SEG(grp->ptrgrp), FP_OFF(grp->ptrgrp),
									 FP_SEG(ser_data), FP_OFF(ser_data), length);
					data_pointer = ser_data;
					moved = 1;
					entitysize = sizeof( Str_grp_element );
					heap_grp_flag2--;
				 }
				 else
				 {
					asm pop es;
					return 1;
				 }
				}
#endif
				break;
			}
		}
		case 20:
		{
#ifdef NETWORK_COMM
			if( media == NETBIOS  )
			{
				point = *(Point *)(net_p->ses_info[session].buffer + 3);
			}
			else
#endif
			{
#ifdef SERIAL_COMM
				point = *((Point *)&ptrtable->arg);
#endif
			}
			{
				switch( point.point_type)
				{
					case OUTPUT:
					case INPUT:
					case VARIABLE:
					case CONTROLLER:
					case WEEKLY_ROUTINE:
					case ANNUAL_ROUTINE:
					case PROGRAM:
					case CONTROL_GROUP:
					case AY+1:
					case TBL+1:
					{
						length = ptr_panel->info[point.point_type-1].str_size;
						data_pointer = (char *)ptr_panel->info[point.point_type-1].address + point.number*length;
						break;
					}
					case DIGITAL_MONITOR:
					{
						break;
					}
					case ANALOG_MONITOR:
					{
						data_pointer = (char*)ptr_panel->analog_mon + point.number * sizeof( Str_monitor_point );
						length = sizeof( Str_monitor_point );
//						if( media == SERIAL_LINK  || media == RS485_LINK )
//						if( media == SERIAL_LINK || media == MODEM_LINK || media == RS485_LINK )
							if( ptrtable->command > 100 )
							{
							 if( length == ptrtable->length )
							 {
//								 Str_monitor_point *p;
//								 char huge *q;
//								 p = (Str_monitor_point *)data_pointer;
//								 q =  p->data_segment;
//								 memmove(data_pointer, ser_data, sizeof(Str_analog_monitor_point)-35);
								 memmove(data_pointer, ser_data, sizeof(Str_monitor_point));
//								 p->data_segment=q;
								 save_prg_flag = 1;
							 }
							 asm pop es;
							 return 0;
							}
#ifdef NETWORK_COMM
						if( media == NETBIOS )
						{
							if( length > SES_BUF_LEN-8 ) net_p->ses_info[session].need_buffer = 1;
							if( comm == SEND_DATA )
							{
								_fmemcpy( net_p->ses_info[session].data, data_pointer, length );
								data_pointer = net_p->ses_info[session].data;
							}
						}
#endif
						break;
					}
					default :
					{
//						DisplayMessage(20, 7, 60, 11, " Wrong point type ",NULL, Blue,NULL,1000);
						break;
					}
			  }
/*
			  if( point.point_type == PROGRAM )
				  if( ptrtable->command > 100 )
					 memcpy(&(((Str_program_point *)ser_data)->bytes), &((Str_program_point *)data_pointer)->bytes, 2);
*/
			}
			break;
		}
		case TIME_COMMAND:
		{
//			data_pointer = (char*)ptr_panel->time_block;
			data_pointer = (char*)&ora_current;
			length = sizeof(Time_block);
			if( ptrtable->command > 100 )
			{
			 if( length == ptrtable->length )
			 {
				struct  time t;
				struct date d;
				disable();
				memmove(data_pointer, ser_data, sizeof(Time_block));
				t.ti_hund=0; t.ti_sec=ora_current.ti_sec+1;
				t.ti_min=ora_current.ti_min; t.ti_hour=ora_current.ti_hour;
				settime(&t);
//				gettime(&ora_start);
//				timesec1970=time(NULL);
//				ora_current_sec = (unsigned long)ora_start.ti_hour*3600L+(unsigned long)ora_start.ti_min*60L+(unsigned long)ora_start.ti_sec;
//				timestart=0;
//				milisec = 0;
//				microsec = 0;
				d.da_year = ora_current.year + 1900;
				d.da_day = ora_current.dayofmonth;
				d.da_mon = ora_current.month+1;
				setdate(&d);
				updatetimevars();
        sendtime = 1;
        sendtime_ipx = 1;
				enable();
			 }
			 asm pop es;
			 return 0;
			}
			break;
		}
		case UPDATEMEMMONITOR_T3000:
		case READMONITORDATA_T3000:
		{
			long *mon_table;
#ifdef NETWORK_COMM
			if( media == NETBIOS  )
			{
				if( comm == SEND_COMMAND )
				{
					len = 8;
					if( net_p->ses_info[session].ses_own == REMOTE )
					{
						if(comm_code==22)
							net_p->ses_info[session].data = readmontable( bank, (int *)&length, &mon_table, 1 );
						if(comm_code==23 )
							if(  bank < 0x8000 )
								net_p->ses_info[session].data = newnetmem(bank, (int *)&length);
							else
								net_p->ses_info[session].data = updatenetmemdig(bank-0x8000, (int *)&length);
					}
					_fmemcpy( (net_p->ses_info[session].buffer+6), (char*)&length, 2);
					net_p->ses_info[session].buffer[2] += 100;
					net_p->ses_info[session].buffer[5] = ptr_panel->lock[comm_code];
					if( length < SES_BUF_LEN - 8 )
					{
						if( net_p->ses_info[session].ses_own == REMOTE )
						{
							_fmemcpy( net_p->ses_info[session].buffer + 8, net_p->ses_info[session].data, length );
							set_semaphore_dos();
							delete net_p->ses_info[session].data;
							clear_semaphore_dos();
						}
						len += length;
					}
					net_p->ses_info[session].state = SENDING_COMMAND;
					net_p->send( session, net_p->ses_info[session].buffer, len );
			 asm pop es
					return 0;
				}
				if( comm == SEND_DATA )
				{
					net_p->ses_info[session].need_buffer = 1;
					if( net_p->ses_info[session].ses_own == REMOTE )
					{
						length = *(int*)(net_p->ses_info[session].buffer+6);
						data_pointer = net_p->ses_info[session].data;
					}
				}
			}
			else
#endif
			{
#ifdef SERIAL_COMM
					char *p;
					if(comm_code==READMONITORDATA_T3000)
					{
//						if( free_pool_index ) {asm pop es; return 1;}
						if( !(l=port_ptr.cd->ser_pool.alloc(SERIAL_BUF_SIZE-800)) ) { asm pop es; return 1;}
						else
						{
						 ser_data = port_ptr.cd->ser_data+l;
						 ptrtable->pool_index = l;
						}
						p = readmontable( bank, (int *)&length, &mon_table, 2 , ser_data);
					}
					if(comm_code==UPDATEMEMMONITOR_T3000)
					{
						if( !(l=port_ptr.cd->ser_pool.alloc(7000)) ) { asm pop es; return 1;}
						else
						{
						 ser_data = port_ptr.cd->ser_data+l;
						 ptrtable->pool_index = l;
						}
//						if( SERIAL_BUF_SIZE - free_pool_index < 6500 ){asm pop es; return 1;}
						if(  bank < 0x8000 )
							p = newnetmem(bank, (int *)&length, ser_data);
						else
							p = updatenetmemdig(bank-0x8000, (int *)&length, ser_data);
					}
//					memmove( ser_p->ser_data, p, length );
//					mfarfree((HANDLE)FP_SEG(p));
//				delete p;
					data_pointer = ser_data;
					moved = 1;
					break;
#endif
			}
			break;
		}
		case 24:
		{
// not needed from 2.27 version
			struct point_info_table *point_info_table;
			Point_Net *pi;
			length = MAX_POINTS_IN_MONITOR*sizeof(struct point_info_table);
			if( !(l=port_ptr.cd->ser_pool.alloc(length)) ) { asm pop es; return 1;}
			else
			{
				 ser_data = port_ptr.cd->ser_data+l;
				 ptrtable->pool_index = l;
			}
//			 if (free_pool_index+length>=SERIAL_BUF_SIZE){ asm pop es; return 1;}
			point_info_table = (struct point_info_table *)ser_data;
			data_pointer = ser_data;
			memset(ser_data, 0, length);
			pi = &ptr_panel->analog_mon[bank-1].inputs[0];
			for(i=0;i<MAX_POINTS_IN_MONITOR;i++,pi++)
			{
			if(!pi->zero())
			{
			 memcpy(&point_info_table->point_info.point,pi,sizeof(Point_Net));
			 get_point_info(&point_info_table->point_info, NULL, NULL, NULL, NULL, 1, NetworkAddress);
			}
			point_info_table++;
			}
			moved = 1;
			break;
		}
		case READGROUPELEMENT_T3000:
/*
				Point_info inf;
				if( media == NETBIOS )
				{
#ifdef NETWORK_COMM
					point = *(Point_main *)(net_p->ses_info[session].buffer + 3);
					if( comm == SEND_COMMAND )
					{
						memset( net_p->ses_info[session].buffer, 0, 8 );
						get_point_info( &inf, NULL, NULL, NULL, NULL, 0, NetworkAddress );
						net_p->ses_info[session].buffer[2] = 125;
						_fmemcpy(net_p->ses_info[session].buffer+3, &point, sizeof( Point_main ) );
						net_p->ses_info[session].buffer[6] = sizeof( Point_info );
						_fmemcpy( net_p->ses_info[session].buffer+8, &inf, sizeof( Point_info ) );
						net_p->send( session, net_p->ses_info[session].buffer, 16 );
						net_p->ses_info[session].state = SENDING_COMMAND;
					}
					if( comm == TRANSFER_COMMAND )
						put_point_info( (Point_info *)(net_p->ses_info[session].buffer+8) );
			 asm pop es
					return 0;
#endif
				}
				else
				{
#ifdef SERIAL_COMM
					point = *((Point *)&ptrtable->arg);
					if( comm == SEND_COMMAND )
					{
					}
					if( comm == TRANSFER_COMMAND || comm == TRANSFER_DATA )
					{
						put_point_info( (Point_info *)ser_data );
						asm pop es
						return 0;
					}
#endif
				}
				break;

*/
				if(ptrtable->command > 100)
				{
				 send_grp( (bank&0x00FF)+3, ptrtable->length / sizeof( Str_grp_element ), (bank>>8), ( Str_grp_element *)(ser_data), 2, 1, 0, 0, ptrtable->res );
				 save_prg_flag = 1;
				}
				asm pop es
				return 0;
		case 27:
		{
			data_pointer = (char*)ptr_panel->units;
			break;
		}
		case 29:
		{
//			data_pointer = (char*)ptr_panel->dst_block;
			break;
		}
/*		case 35:
		{
			_fmemcpy( system_name, (void*)net_p->ses_info[session].data, length );
			break;
		}*/
/*		case 38:
		{
			_fmemcpy( system_name, (void*)net_p->ses_info[session].data, length );
			break;
		}********************/
		case 30:
		{
			data_pointer = (char *)ptr_panel->arrays_data[bank];
			length = ptr_panel->arrays[bank].length*sizeof(Str_ayvalue_point);
			break;
		}
		case 40:
		{
//			data_pointer = (char*)ptr_panel->mon_setup;
			break;
		}
		case PASS+1:
		{
			data_pointer = (char *)&passwords;
//			length = sizeof( Password_point ) * MAX_PASSW;
			length = sizeof( passwords );
			if( ptrtable->command > 100 )
			{
			 save_passwords=1;
			 action=1;
			 if( tasks[MISCELLANEOUS].status == SUSPENDED )
				 resume(MISCELLANEOUS);
			}
			break;
		}
		case 47:
		{
			uint type;
			len = 0;
#ifdef NETWORK_COMM
			if(media == NETBIOS )
			{
				if( comm == SEND_COMMAND )
				{
					_fmemcpy( &len, net_p->ses_info[session].buffer+3, 2 );
					point.point_type = len;
					len = 0;
					length = search_point( point, NULL, NULL, 0, LENGTH_POINT );
					_fmemcpy( net_p->ses_info[session].buffer+6, &length, 2 );
					if( length < SES_BUF_LEN - 8 )
					{
						search_point( point, net_p->ses_info[session].buffer+8, NULL, 0,
																				DESCRIPTOR_POINT );
						len = length + 8;
					}
					else
					{
						len = 8;
						net_p->ses_info[session].need_buffer++;
					}
					net_p->ses_info[session].state = SENDING_COMMAND;
					net_p->send( session, net_p->ses_info[session].buffer, len );
			 asm pop es
					return 0;
				}
				if( comm == SEND_DATA )
				{
					_fmemcpy( &length, net_p->ses_info[session].buffer+6, 2 );
					_fmemcpy( &type, net_p->ses_info[session].buffer+3, 2 );
					point.point_type = type;
					search_point( point, net_p->ses_info[session].data, NULL, 0,
																				DESCRIPTOR_POINT );
					net_p->ses_info[session].state = SENDING_DATA;
					net_p->send( session, net_p->ses_info[session].data, length );
					asm pop es
					return 0;
				}
			}
			else
#endif
			{
#ifdef SERIAL_COMM
				if( comm == SEND )
				{
//					len = ptrtable->arg;
					point.point_type = ptrtable->arg;
					length = search_point( point, NULL, NULL, 0, LENGTH_POINT );
					if( !(l=port_ptr.cd->ser_pool.alloc(length)) ) { asm pop es; return 1;}
					else
					{
					 ser_data = port_ptr.cd->ser_data+l;
					 ptrtable->pool_index = l;
					}
/*
					if(media==RS485_LINK)
					 if (free_pool_index+length>=SERIAL_BUF_SIZE){ asm pop es; return 1;}
*/
					data_pointer = ser_data;
					search_point( point, data_pointer, NULL, 0, DESCRIPTOR_POINT );
					moved = 1;
				}
#endif
			}
			break;
		}
		case 48:
		{
			data_pointer = (char*)ptr_panel->arrays;
			break;
		}
		case 49:
		{
//			data_pointer = (char*)ptr_panel->array_data;
			break;
		}
		case 50:
		{
#ifdef NETWORK_COMM
			if( media == NETBIOS )
			{
			 ex_high = net_p->ses_info[session].buffer[3];
			}
			else
#endif
#ifdef SERIAL_COMM
			ex_high = ptrtable->arg;
#endif
			switch( ex_high )
			{
				case 20:
						if( port_ptr.sr->media == MODEM_LINK && port_ptr.sr->modem_active )
						{
						 port_ptr.sr->connection_established = 0;
//						 sleep_modem = 1;
						 long time = ReadTime();
						 while ( Routing_table[port_ptr.sr->port_number].port_status_vars.physical_connection_state && ( ( ReadTime() - time ) < 10000 ) );
//						 msleep( 180 );
//						 sleep_modem = 0;
						 port_ptr.sr->modem_obj->Initialize();
						}
						port_ptr.sr->FlushRXbuffer();
						port_ptr.sr->FlushTXbuffer();
						port_ptr.sr->activity = FREE;
						asm pop es
						return 0;
				case 21:
//					if( ptr_panel )
//						station_list[Station_NUM-1].des_length = search_point( point, NULL, NULL, 0, LENGTH );
//					data_pointer = (char*)station_list;
					length = MAX_STATIONS * sizeof( Station_point );

					if( media == IPX_LINK || media == TCPIP_LINK || media == RS485_LINK )
					{
					 if( destport!=-1 )
					 {
						((class ConnectionData *)Routing_table[destport].ptr)->station_list[Station_NUM-1].des_length = search_point( point, NULL, NULL, 0, LENGTH );
						((class ConnectionData *)Routing_table[destport].ptr)->panel_info1.des_length = ((class ConnectionData *)Routing_table[destport].ptr)->station_list[Station_NUM-1].des_length;
						data_pointer = (char*)(((class ConnectionData *)Routing_table[destport].ptr)->station_list);
					 }
					 else
					 {
						((class ConnectionData *)s_port)->station_list[Station_NUM-1].des_length = search_point( point, NULL, NULL, 0, LENGTH );
						((class ConnectionData *)s_port)->panel_info1.des_length = ((class ConnectionData *)s_port)->station_list[Station_NUM-1].des_length;
						data_pointer = (char*)(((class ConnectionData *)s_port)->station_list);
					 }
					}
					else
					{
					 for(i=0; i<MAX_Routing_table; i++)
					 {
						if( (Routing_table[i].status&PORT_ACTIVE)==PORT_ACTIVE)
						{
							if( Routing_table[i].Port.network==NetworkAddress ) break;
						}
					 }
					 if(i<MAX_Routing_table)
					 {
// port NetworkAddress on RS485, IPX or TCPIP
						if( (Routing_table[i].status&IPX_ACTIVE)==IPX_ACTIVE ||
								(Routing_table[i].status&TCPIP_ACTIVE)==TCPIP_ACTIVE ||
								(Routing_table[i].status&RS485_ACTIVE)==RS485_ACTIVE   )
						{
						 ((class ConnectionData *)Routing_table[i].ptr)->station_list[Station_NUM-1].des_length = search_point( point, NULL, NULL, 0, LENGTH );
						 ((class ConnectionData *)Routing_table[i].ptr)->panel_info1.des_length = ((class ConnectionData *)Routing_table[i].ptr)->station_list[Station_NUM-1].des_length;
						 data_pointer = (char*)(((class ConnectionData *)Routing_table[i].ptr)->station_list);
						}
						else
						{
						 station_list[Station_NUM-1].des_length = search_point( point, NULL, NULL, 0, LENGTH );
						 data_pointer = (char*)station_list;
						}
					 }
					 else
					 {
						station_list[Station_NUM-1].des_length = search_point( point, NULL, NULL, 0, LENGTH );
						data_pointer = (char*)station_list;
					 }
					}
					break;
				case 22:
//					data_pointer = (char*)ptr_panel->table_bank;
//					length = 55;
					break;
				case 30:
				case 31:
					data_pointer = saveloadfilename;
//			length = sizeof( Password_point ) * MAX_PASSW;
					length = 13;
					if(ex_high == 30)
						save_file=1;
					else
						load_file=1;
					action=1;
					if( tasks[MISCELLANEOUS].status == SUSPENDED )
					 resume(MISCELLANEOUS);
					break;
				case 32:
				case 33:
					data_pointer = (char*)ptr_panel->Default_Program;
					length = 13;
					if(ex_high == 33)
					{
					 save_default=1;
					 action=1;
					 if( tasks[MISCELLANEOUS].status == SUSPENDED )
						resume(MISCELLANEOUS);
					}
					break;
				case 35:
				case 39:
					data_pointer = filetransfername;
					length = 65;
					if(ex_high == 35)
						filetransfer_flag=1;
					else
						filetransfer_flag=2;
					action=1;
					if( tasks[MISCELLANEOUS].status == SUSPENDED )
						resume(MISCELLANEOUS);
					break;
				case 36:
					if(!ptr_filetransfer)
					{
					 asm pop es
					 return 0;
					}
					data_pointer = ptr_filetransfer;
					if( ptrtable->command > 100 )
					{
						length = (*((unsigned *)ser_data)) + 2;
						if(length > MAX_FILE_TRANSFER_BUF) length = MAX_FILE_TRANSFER_BUF;
						else filetransfer = 0;
					}
					else
					{
						length = (*((unsigned *)ptr_filetransfer)) + 2;
						if(length > MAX_FILE_TRANSFER_BUF) length = MAX_FILE_TRANSFER_BUF;
					}
//					else filetransfer = 0;
					break;
				case 37:
					data_pointer = &filetransfer;
					length = 1;
					break;
				case 38:
					data_pointer = (char *)&length_filetransfer;
					length = 4;
					break;
				case 40:
				 char cur[65];
				 {
					if( !(l=port_ptr.cd->ser_pool.alloc(7000)) ) { asm pop es; return 1;}
					else
					{
						 ser_data = port_ptr.cd->ser_data+l;
						 ptrtable->pool_index = l;
					}
					cur[0]=0;
					set_semaphore_dos();
					getcwd(cur,64);
					chdir(current_path);
					clear_semaphore_dos();
					i=getfiles(term_tr, (char (*)[13])(((char *)ser_data)+2), 499,1);
					set_semaphore_dos();
					chdir(cur);
					clear_semaphore_dos();
					length = i*13 + 2;
					memcpy(ser_data, &i, 2);
					data_pointer = ser_data;
					moved=1;
				 }
				 break;
				case 41:
				 {
					if( !(l=port_ptr.cd->ser_pool.alloc(1500)) ) { asm pop es; return 1;}
					else
					{
						 ser_data = port_ptr.cd->ser_data+l;
						 ptrtable->pool_index = l;
					}
					cur[0]=0;
					set_semaphore_dos();
					getcwd(cur,64);
					chdir(current_path);
					clear_semaphore_dos();
					i=getdirectories(NULL, (char (*)[13])(((char *)ser_data)+2), 49, 1);
					set_semaphore_dos();
					chdir(cur);
					clear_semaphore_dos();
					length = i*13+2;
					memcpy(ser_data, &i, 2);
					data_pointer = ser_data;
					moved=1;
				 }
				 break;
				case 42:
				 {
					current_path[0]=0;
					set_semaphore_dos();
					getcwd(current_path,64);
					clear_semaphore_dos();
					length = 65;
					data_pointer = current_path;
				 }
				 break;
				case 43:
					length = 65;
					data_pointer = current_path;
					if(ser_data[strlen(ser_data)-2]!=':')
						 ser_data[strlen(ser_data)-1]=0;
					break;
				case 44:
					length = 13;
					data_pointer = term_tr;
					break;
				case 45:
					data_pointer = filename_tmp;
					length = 65;
					break;
				case 46:
					int hh;
					set_semaphore_dos();
					l=-1;
		 int_disk1++;
					if( (hh=open(filename_tmp,O_RDONLY))!=NULL)
					{
					 l = filelength(hh);
					 close(hh);
					}
		 int_disk1--;
					clear_semaphore_dos();
					data_pointer = (char *)&l;
					length = 4;
					break;
				case 47:
				case 48:
					if( ptrtable->command > 100 )
					{
					set_semaphore_dos();
					if(ex_high == 47)
						remove(ser_data);
					else
						rename(&ser_data[65],ser_data);
					clear_semaphore_dos();
					}
					asm pop es
					return 0;
				case 50:
					if(control)
					{
					 ptr_panel->Aio_Control( RESET_PC, NULL, 0 );
					}
					asm pop es
					return 0;
				case ALARM_NOTIFY_COMMAND:
					length = 1;
					data_pointer = (char *)&GAlarm;
					break;
				case 75:
					length = sizeof(tbl_bank);
					data_pointer = (char *)ptr_panel->table_bank;
					break;
				case 76:
					if( ptrtable->command > 100 )
					{
//					 updatenet_flag=1;
					 memcpy(&updatenet_flag, ser_data, 2);
					 action=1;
					 if( tasks[MISCELLANEOUS].status == SUSPENDED )
						resume(MISCELLANEOUS);
					 asm pop es
					 return 0;
					}
					else
					{
						length = 2;
						data_pointer = (char *)&update_t3000exe;
					}
					break;
				case PANEL_INFO1_COMMAND:
					length = sizeof(Panel_info1);
					len  = search_point( point, NULL, NULL, 0, LENGTH );
//					if( media == RS485_LINK )
					if( media == IPX_LINK || media == TCPIP_LINK || media == RS485_LINK )
					{
					 if( destport!=-1 )
					 {
						 ((class ConnectionData *)Routing_table[destport].ptr)->panel_info1.des_length=len;
						 ((class ConnectionData *)Routing_table[destport].ptr)->station_list[Station_NUM-1].des_length=len;
						 data_pointer = (char *)&(((class ConnectionData *)Routing_table[destport].ptr)->panel_info1);
					 }
					 else
					 {
						 ((class ConnectionData *)s_port)->panel_info1.des_length=len;
						 ((class ConnectionData *)s_port)->station_list[Station_NUM-1].des_length=len;
						 data_pointer = (char *)&(((class ConnectionData *)s_port)->panel_info1);
					 }
					}
					else
					{
					 data_pointer = (char *)&Panel_Info1;
					 Panel_Info1.des_length=len;
/*
					 for(i=0; i<MAX_Routing_table; i++)
					 {
						if( (Routing_table[i].status&PORT_ACTIVE)==PORT_ACTIVE)
						{
							if( Routing_table[i].Port.network==NetworkAddress ) break;
						}
					 }

					 if(i<MAX_Routing_table)
// port NetworkAddress on RS485, IPX or TCPIP
						if( (Routing_table[i].status&IPX_ACTIVE)==IPX_ACTIVE ||
								(Routing_table[i].status&TCPIP_ACTIVE)==TCPIP_ACTIVE ||
								(Routing_table[i].status&RS485_ACTIVE)==RS485_ACTIVE   )
						{
						 ((class ConnectionData *)Routing_table[i].ptr)->panel_info1.des_length=len;
						 data_pointer = (char *)&(((class ConnectionData *)Routing_table[i].ptr)->panel_info1);
						}
*/
/*
					 for(i=0; i<MAX_Routing_table; i++)
					 {
						if( (Routing_table[i].status&RS485_ACTIVE)==RS485_ACTIVE || (Routing_table[i].status&IPX_ACTIVE)==IPX_ACTIVE) break;
					 }
					 if(i<MAX_Routing_table)
					 {
						 ((class ConnectionData *)Routing_table[i].ptr)->panel_info1.des_length=len;
						 data_pointer = (char *)&(((class ConnectionData *)Routing_table[i].ptr)->panel_info1);
					 }
*/
					 if( destport!=-1 )
					 {
						 ((class ConnectionData *)Routing_table[destport].ptr)->panel_info1.des_length=len;
						 ((class ConnectionData *)Routing_table[destport].ptr)->station_list[Station_NUM-1].des_length=len;
						 data_pointer = (char *)&(((class ConnectionData *)Routing_table[destport].ptr)->panel_info1);
					 }
					 else
					 {
						((class ConnectionData *)s_port)->panel_info1.des_length=len;
						((class ConnectionData *)s_port)->station_list[Station_NUM-1].des_length=len;
						data_pointer = (char *)&(((class ConnectionData *)s_port)->panel_info1);
					 }
					}
					break;
				case ICON_NAME_TABLE_COMMAND:
					length = sizeof(Icon_name_table);
					data_pointer = (char *)Icon_name_table;
					break;
				case OPENSCREEN_COMMAND:
					data_pointer = (char *)&localopenscreen;
					length = sizeof(Point_Net);
					break;
				case INFODATA_COMMAND:
					if( !(l=port_ptr.cd->ser_pool.alloc(510)) )
					{
						asm pop es;
						return 1;
					}
					else
					{
						ser_data = port_ptr.cd->ser_data+l;
						ptrtable->pool_index = l;
					}
					data_pointer = ser_data;
					length = 0;

					*data_pointer++ = sizeof(Panel_info1);
					len  = search_point( point, NULL, NULL, 0, LENGTH );
					if( media == IPX_LINK || media == TCPIP_LINK || media == RS485_LINK )
					{
					 if( destport!=-1 )
					 {
						 ((class ConnectionData *)Routing_table[destport].ptr)->panel_info1.des_length=len;
						 *((Panel_info1*)data_pointer) = (((class ConnectionData *)Routing_table[destport].ptr)->panel_info1);
					 }
					 else
					 {
						 ((class ConnectionData *)s_port)->panel_info1.des_length=len;
						 *((Panel_info1*)data_pointer) = (((class ConnectionData *)s_port)->panel_info1);
					 }
					}
					else
					{
					 *((Panel_info1*)data_pointer) = Panel_Info1;
					 Panel_Info1.des_length=len;
					 if( destport!=-1 )
					 {
						 ((class ConnectionData *)Routing_table[destport].ptr)->panel_info1.des_length=len;
						 *((Panel_info1*)data_pointer) = (((class ConnectionData *)Routing_table[destport].ptr)->panel_info1);
					 }
					 else
					 {
						((class ConnectionData *)s_port)->panel_info1.des_length=len;
						*((Panel_info1*)data_pointer) = (((class ConnectionData *)s_port)->panel_info1);
					 }
					}
					length += 1+sizeof(Panel_info1);
					data_pointer += sizeof(Panel_info1);

					*data_pointer++ = sizeof(tbl_bank);
					memcpy( data_pointer, (char *)ptr_panel->table_bank, sizeof(tbl_bank));
					length += 1+sizeof(tbl_bank);
					data_pointer += sizeof(tbl_bank);

					*data_pointer++ = 13;
					memcpy( data_pointer, (char*)ptr_panel->Default_Program, 13);
					length += 14;
					data_pointer += 13;

					*data_pointer++ = sizeof( Units_element ) * 8;
					memcpy( data_pointer, (char *)ptr_panel->units, sizeof( Units_element ) * 8);
					length += 1+sizeof( Units_element ) * 8;
					data_pointer += sizeof( Units_element ) * 8;

					*data_pointer++ = 1;
					*data_pointer = GAlarm;
					length += 2;

					data_pointer = ser_data;
					moved = 1;
					break;
			}
			break;
		}
		case SEND_ALARM_COMMAND:
		{
		 Alarm_point *ptr,*ptr1;
		 Panel_info1 *panel_info;
		 ptr = (Alarm_point *)ser_data;
			 if(	ptr->alarm_panel==Station_NUM || ptr->where1==255 || (ptr->where1==Station_NUM||ptr->where2==Station_NUM||
															 ptr->where3==Station_NUM||ptr->where4==Station_NUM||
															 ptr->where5==Station_NUM ) )
			 {
				if( !bank )
				{
				 if( (i=checkforalarm((char *)&ptr->alarm_id,ptr->prg,ptr->alarm_panel,1)) > 0 )
				 {
					if( ptr_panel->alarms[i-1].change_flag != 2 )
					{           // the alarm does not change its state in this moment
					 if( ptr->restored && !ptr_panel->alarms[i-1].restored )
					 {                // restored alarm
						ptr_panel->alarms[i-1].restored = 1;
						if(--ptr_panel->ind_alarms==0)
						 GAlarm = 0;
						if(ptr->alarm_panel==Station_NUM)
						{
						 ptr_panel->alarms[i-1].where_state1 = 0;
						 ptr_panel->alarms[i-1].where_state2 = 0;
						 ptr_panel->alarms[i-1].where_state3 = 0;
						 ptr_panel->alarms[i-1].where_state4 = 0;
						 ptr_panel->alarms[i-1].where_state5 = 0;
						 new_alarm_flag |= 0x01;  // send the alarm to the destination panels
						 resume(ALARMTASK);
						}
					 }
					 else
					 {
						if( ptr->acknowledged && !ptr_panel->alarms[i-1].acknowledged )
						{                // acknowledged alarm
///
						 if( !ptr_panel->alarms[i-1].restored )
						 {
							if(--ptr_panel->ind_alarms==0)
								GAlarm = 0;
						 }
///
						 ptr_panel->alarms[i-1].acknowledged = 1;
						 if(ptr->alarm_panel==Station_NUM)
						 {
							ptr_panel->alarms[i-1].where_state1 = 0;
							ptr_panel->alarms[i-1].where_state2 = 0;
							ptr_panel->alarms[i-1].where_state3 = 0;
							ptr_panel->alarms[i-1].where_state4 = 0;
							ptr_panel->alarms[i-1].where_state5 = 0;
							new_alarm_flag |= 0x01;  // send the alarm to the destination panels
							resume(ALARMTASK);
						 }
						}
					 }
					}
				 }
				 else
				 {
					if( !ptr->restored && !ptr->acknowledged )
					{         // new alarm
					 i = checkalarmentry();
					 if(i>=0 && ptr_panel->alarms[i].change_flag != 2 )
					 {
						ptr1 = &ptr_panel->alarms[i];
						ptr1->change_flag  = 2;
						memcpy(ptr1,ptr,sizeof(Alarm_point));
						ptr1->alarm        = 1;
						ptr1->no           = i;
						ptr1->ddelete      = 0;
						ptr1->original     = 0;
						ptr1->change_flag  = 0;
						if( ++ptr_panel->ind_alarms > MAX_ALARMS) ptr_panel->ind_alarms = MAX_ALARMS;
						GAlarm = 1;
						if(printAlarms)
						{
						 memmove((char *)ptr, ptr->alarm_message,ALARM_MESSAGE_SIZE+1);
						 printalarmproc((char *)ptr, i);
/*
						 set_semaphore_dos();
						 char *buf = new char[ ALARM_MESSAGE_SIZE+26+10 ];
						 clear_semaphore_dos();
						 strcpy(buf, ptr->alarm_message);
						 strcat(buf,"\\f");
						 print(buf);  // print to printer
						 set_semaphore_dos();
						 delete buf;
						 clear_semaphore_dos();
*/
						}
					 }
					}
				 }
				}
				else
				{
				 if( (i=checkforalarm((char *)&ptr->alarm_id,ptr->prg,ptr->alarm_panel,1)) > 0 )
				 {
					if( !ptr_panel->alarms[i-1].restored && !ptr_panel->alarms[i-1].acknowledged )
					{
					 if(--ptr_panel->ind_alarms==0)
							GAlarm = 0;
					}
					ptr_panel->alarms[i-1].alarm        = 0;
					ptr_panel->alarms[i-1].change_flag  = 0;
					ptr_panel->alarms[i-1].restored     = 0;
					ptr_panel->alarms[i-1].acknowledged = 0;
					ptr_panel->alarms[i-1].ddelete      = 1;
			    ptr_panel->alarms[i-1].original     = 0;
					if(ptr->alarm_panel==Station_NUM)
					{
						 ptr->where_state1 = 0;
						 ptr->where_state2 = 0;
						 ptr->where_state3 = 0;
						 ptr->where_state4 = 0;
						 ptr->where_state5 = 0;
						 new_alarm_flag |= 0x02;  // send the alarm to the destination panels
						 resume(ALARMTASK);
					}
				 }
				}
			 }
		}
	}
#ifdef NETWORK_COMM
	if( media == NETBIOS  )
	{
		switch( comm )
		{
			case SEND_COMMAND:
			{
				len = 8;
				net_p->ses_info[session].buffer[5] = ptr_panel->lock[comm_code];
				net_p->ses_info[session].buffer[2] = comm_code+100;
				_fmemcpy( (net_p->ses_info[session].buffer+6), (char*)&length, 2);
				if( length <= SES_BUF_LEN-8 )
				{
					_fmemcpy( net_p->ses_info[session].buffer+8, data_pointer, length );
					len += length;
				}
				net_p->ses_info[session].state = SENDING_COMMAND;
				net_p->send( session, net_p->ses_info[session].buffer, len );
				break;
			}
			case TRANSFER_DATA:
			{
				_fmemcpy( &length, net_p->ses_info[session].buffer+6, 2 );
				if( net_p->ses_info[session].ses_own == REMOTE )
					_fmemcpy( data_pointer, net_p->ses_info[session].data, length );
				break;
			}
			case TRANSFER_COMMAND:
			{
				_fmemcpy( &length, net_p->ses_info[session].buffer+6, 2 );
				if( net_p->ses_info[session].ses_own == LOCAL_OPERATOR )
					_fmemcpy( operator_list.buffer, net_p->ses_info[session].buffer+8, length );
				else _fmemcpy( data_pointer, net_p->ses_info[session].buffer+8, length );
				break;
			}
			case SEND_DATA:
			{
				if( net_p->ses_info[session].ses_own == REMOTE )
					net_p->ses_info[session].data = data_pointer;
				if( net_p->ses_info[session].ses_own == LOCAL_OPERATOR )
					net_p->ses_info[session].data = operator_list.buffer;
//				if( net_p->ses_info[session].ses_own == LOCAL_DRIVER )
//					net_p->ses_info[session].data = ser_list.buffer;
				net_p->ses_info[session].state = SENDING_DATA;
				net_p->send( session, net_p->ses_info[session].data, length );
				break;
			}
		}
	}
	else
#endif
	{
#ifdef SERIAL_COMM
		if( ptrtable->command > 100 )
		{
			if( length == ptrtable->length )
			{
				_fmemcpy( data_pointer, ser_data, length );
				save_prg_flag = 1;
				if ( comm_code==AR_Y+1 )
				{
				 check_annual_routine_flag=1;
				}
			}
		}
		else
		{
//		  memmove( ser_port->ser_data, data_pointer, length );
			if(!moved)
			{
//			if(media==RS485_LINK && !moved)
//			  if ( free_pool_index+length>=SERIAL_BUF_SIZE){ asm pop es; return 1;}
			if( !(l=port_ptr.cd->ser_pool.alloc(length)) )
				{ asm pop es; return 1;}
			else
			{
			 ser_data = port_ptr.cd->ser_data+l;
			 ptrtable->pool_index = l;
			}
			movedata( FP_SEG(data_pointer), FP_OFF(data_pointer),
							FP_SEG(ser_data), FP_OFF(ser_data), length);
			}
//		  if(media==RS485_LINK)
//		  if( media == SERIAL_LINK || media == MODEM_LINK || media == RS485_LINK )
			{
			 ptrtable->data   = ser_data;
			 ptrtable->length = length;
			 if(entitysize)
				 ptrtable->entitysize = entitysize;
			 else
			 {
				if(length<MAXASDUSIZE)
					ptrtable->entitysize = length;
				else
					ptrtable->entitysize = MAXASDUSIZE;
			 }
			 if(ex_high==36) filetransfer = 0;
			}
/*
			else
			{
			RS232Error result;
			ptr = ser_port->RIB_out;
			*ptr = RIB_in[1];
			*(ptr+1) = Station_NUM;
			*(ptr+2) = comm_code + 100;
			*(ptr+3) = *(byte*)&bank;
			*(ptr+4) = *( (byte*)&bank + 1);
			*(ptr+5) = ptr_panel->lock[comm_code];
			ser_port->Set_PIC_mask();
//			result = ser_port->Command( SEND, BACKGND, ptr, length, ser_data );
			ser_port->Reset_PIC_mask();
			if( result != RS232_SUCCESS )
			{
				Delay(1000);
				ser_port->FlushRXbuffer();
				ser_port->FlushTXbuffer();
			}
			else
			 if(ex_high==36) filetransfer = 0;
			}
*/
		}
	}
#endif
 asm pop es
 return 0;
}
#endif
