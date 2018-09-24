//**********************************************************************
//
//  Here is defined the class used for interfacing with the AIO board
//
//**********************************************************************

#include <graphics.h>
#include <windows.h>
#include "aio.h"
#include "gwin.h"
#include <stdio.h>
#include "mtkernel.h"
#include "rs485.h"

#define MAX_TRY 20000
#define SCAN_RATE 3

//#pragma inline

extern char * rtrim( char * );
extern NETWORK_POINTS	_far network_points_list[MAXNETWORKPOINTS];
extern REMOTE_POINTS _far  remote_points_list[MAXREMOTEPOINTS82];
extern unsigned char tbl_bank[MAX_TBL_BANK];

extern int nsample_mem_dig;
extern int nsample_mem_dig_mon[MAX_ANALM];
extern Heap_dmon huge *heap_dmon;  // 5000
extern unsigned first_free;
extern int MAX_HEAP_DIGM;

extern Password_struct passwords;
extern Panel *ptr_panel;

extern Board_info	boards[MAX_BOARDS];
extern char present_analog_monitor;
extern int programs_size;
extern Str_tbl_point custom_tab[MAX_TABS];

char version_string[12];

Aio::Aio( byte nr_boards)
{
	init_info_table();
	number_of_boards = nr_boards;
	int i, j, k;

	clearpanel();
	card_type = VER2_CARD;
	Config_dacqd_card();
///////////////
	for(i=j=k=0; i<number_of_boards; i++ )
	{
		j += boards[i].no_outs;
		k += boards[i].no_ins;
	}
//	table_bank[0] = control?j:MAX_OUTS; // set to 0 at the end
//	table_bank[1] = control?k:MAX_INS; //     - || -

	table_bank[OUT] = j; // set to 0 at the end
	table_bank[IN] = k; //     - || -


	table_bank[VAR]       = MAX_VARS;
	table_bank[CON]       = MAX_CONS;
	table_bank[WR]        = MAX_WR;
	table_bank[AR]        = MAX_AR;
	table_bank[PRG]       = MAX_PRGS;
	table_bank[TBL]       = MAX_TABS;
	table_bank[DMON]      = MAX_DIGM;
	table_bank[AMON]      = MAX_ANALM;
	table_bank[GRP]       = MAX_GRPS;
	table_bank[AY]        = MAX_ARRAYS;
	table_bank[ALARMM]    = MAX_ALARMS;
	table_bank[UNIT]      = MAX_UNITS;
	table_bank[USER_NAME] = MAX_PASSW;

	memcpy( tbl_bank, table_bank, sizeof(tbl_bank));
}


Aio::~Aio()
{
}

void Aio::clearpanel(void)
{
	present_analog_monitor=0;
	programs_size = 0;
	ind_alarms = 0;
	ind_alarms_set = 0;
	memset(outputs,'\0',MAX_OUTS*sizeof(Str_out_point));
	for(int i=0; i < MAX_OUTS; i++)
		outputs[i].digital_analog = 1;
	memset(out_data,'\0',MAX_OUTS*sizeof(uint));
	memset(inputs,'\0',MAX_INS*sizeof(Str_in_point));
	for(i=0; i < MAX_INS; i++)
	{
		inputs[i].filter = 6;
		inputs[i].digital_analog = 1;
	}
	memset(in_aux,0,MAX_INS*sizeof(In_aux));
	memset(in_data,'\0',MAX_INS*sizeof(uint));
	memset(vars,'\0',MAX_VARS*sizeof(Str_variable_point));
	for(i=0; i < MAX_VARS; i++)
		vars[i].digital_analog = 1;
	memset(controllers,'\0',MAX_CONS*sizeof(Str_controller_point));
	memset(con_aux,0,MAX_CONS*sizeof(Con_aux));
	memset(programs,'\0',MAX_PRGS*sizeof(Str_program_point));
	for(i=0; i < MAX_PRGS; i++)
	{
		programs[i].on_off = 1;
	}
	memset(program_codes,'\0',MAX_PRGS*sizeof(char *));
	memset(control_groups,'\0',MAX_GRPS*sizeof(Control_group_point));
	for(i=0; i < MAX_GRPS; i++)
	{
		control_groups[i].update_time = 15;
	}
	memset(control_group_elements,'\0',MAX_GRPS*sizeof(Control_group_elements));
//	memset(group_elements,'\0',MAX_ELEM*sizeof(Str_grp_element));
	memset(weekly_routines,'\0',MAX_WR*sizeof(Str_weekly_routine_point));
	memset(wr_times,'\0',MAX_WR*9*sizeof(Wr_one_day ));
	memset(annual_routines,'\0',MAX_AR*sizeof(Str_annual_routine_point));
	memset(ar_dates,'\0',MAX_AR*46*sizeof(byte));
	memset(analog_mon,'\0',MAX_ANALM*sizeof(Str_monitor_point));
	memset(monitor_work_data,'\0',MAX_ANALM*sizeof(Str_monitor_work_data));
	for(i=0;i<MAX_ANALM; i++)
	{
	 analog_mon[i].minute_interval_time = 15;
	 analog_mon[i].max_time_length = 3;
	 analog_mon[i].unit = 2;
	 analog_mon[i].double_flag=1;
	 analog_mon[i].status = 1;
	 for(int j=0;j<MAX_POINTS_IN_MONITOR;j++)
	 {
		monitor_work_data[i].start_index_dig[j] = 0x0FFFF;
	 }
	}
	memset(arrays,'\0',MAX_ARRAYS*sizeof(Str_array_point));
	memset(arrays_data,'\0',MAX_ARRAYS*sizeof(long *));

//	memset(mon_setup,'\0',MAX_MONSET*sizeof(Monitor_element));
	memset(&passwords,'\0',sizeof(passwords));

	memset(alarms,'\0',MAX_ALARMS*sizeof(Alarm_point));
	memset(alarms_set,'\0',MAX_ALARMS_SET*sizeof(Alarm_set_point));
	memset(units,'\0',MAX_UNITS*sizeof(Units_element));
	memset(custom_tab,'\0',MAX_TABS*sizeof(Str_tbl_point));

	first_free = 0;
	for(i=0; i < MAX_HEAP_DIGM-1; i++)
		 heap_dmon[i].next = i+1;
	nsample_mem_dig = 0;
	memset(nsample_mem_dig_mon, 0, 2*MAX_ANALM);
	memset(remote_points_list, 0, sizeof(remote_points_list));
//   memset(want_points_list, 0, sizeof(want_points_list));
  memset(network_points_list, 0, sizeof(network_points_list));
}

void Aio::init_info_table( void )
{
	int i;
	memset( info, 0, 18*sizeof( Info_Table ) );
	for( i=0; i<18; i++ )
	{
		switch( i )
		{
			case OUT:
				info[i].address = (char *)outputs;
				info[i].str_size = sizeof( Str_out_point );
				info[i].name = "OUT";
				info[i].max_points = MAX_OUTS;
				break;
			case IN:
				info[i].address = (char *)inputs;
				info[i].str_size = sizeof( Str_in_point );
				info[i].name = "IN";
				info[i].max_points = MAX_INS;
				break;
			case VAR:
				info[i].address = (char *)vars;
				info[i].str_size = sizeof( Str_variable_point );
				info[i].name = "VAR";
				info[i].max_points = MAX_VARS;
				break;
			case CON:
				info[i].address = (char *)controllers;
				info[i].str_size = sizeof( Str_controller_point );
				info[i].name = "CON";
				info[i].max_points = MAX_CONS;
				break;
			case WR:
				info[i].address = (char *)weekly_routines;
				info[i].str_size = sizeof( Str_weekly_routine_point );
				info[i].name = "WR";
				info[i].max_points = MAX_WR;
				break;
			case AR:
				info[i].address = (char *)annual_routines;
				info[i].str_size = sizeof( Str_annual_routine_point );
				info[i].name = "AR";
				info[i].max_points = MAX_AR;
				break;
			case PRG:
				info[i].address = (char *)programs;
				info[i].str_size = sizeof( Str_program_point );
				info[i].name = "PRG";
				info[i].max_points = MAX_PRGS;
				break;
			case TBL:
				info[i].address = (char *)custom_tab;
				info[i].str_size = sizeof( Str_tbl_point );
				info[i].name = "TBL";
				info[i].max_points = MAX_TABS;
				break;
			case DMON:
				info[i].address = NULL;
				info[i].name = "";
				break;
			case AMON:
				info[i].address = (char *)analog_mon;
				info[i].str_size = sizeof( Str_monitor_point );
				info[i].name = "AMON";
				info[i].max_points = MAX_ANALM;
				break;
			case GRP:
				info[i].address = (char *)control_groups;
				info[i].str_size = sizeof( Control_group_point );
				info[i].name = "GRP";
				info[i].max_points = MAX_GRPS;
				break;
			case AY:
				info[i].address = (char *)arrays;
				info[i].str_size = sizeof( Str_array_point );
				info[i].name = "AY";
				info[i].max_points = MAX_ARRAYS;
				break;
			case ALARMM:          //12
				info[i].address = (char *)alarms;
				info[i].str_size = sizeof( Alarm_point );
				info[i].name = "ALR";
				info[i].max_points = MAX_ALARMS;
				break;
			case UNIT:
				info[i].address = (char *)units;
				info[i].str_size = sizeof( Units_element );
				info[i].name = "UNITS";
				info[i].max_points = MAX_UNITS;
				break;
			case USER_NAME:
				info[i].address = (char *)&::passwords;
				info[i].str_size = sizeof( Password_point );
				info[i].name = "PASS";
				info[i].max_points = MAX_PASSW;
				break;
			case ALARMS:          //12
				info[i].address = (char *)alarms_set;
				info[i].str_size = sizeof( Alarm_set_point );
				info[i].name = "ALRS";
				info[i].max_points = MAX_ALARMS_SET;
				break;
/*	case 15: {
//		  &system_info[i].name = data;
			System_Name(  ctype );
				info[i].name = "";
			break;
		}
	case 16: {
			program_code = ( byte * ) data;
			result = Program_Code( ctype, code_length, subscript );
				info[i].name = "";
			break;
		}************************/
			case WR_TIME:
				info[i].address = (char *)wr_times;
				info[i].str_size = 9*sizeof( Wr_one_day );
				info[i].name = "WR_T";
				break;
			case AR_Y:                //17
				info[i].address = (char *)ar_dates;
				info[i].str_size = 46;
				info[i].name = "AR_D";
				break;
		}
	}
}

/* Point_T3000;*/
int Point_T3000::cmp(byte num, byte p_type, byte p)
{
 if(number==num && point_type==p_type && panel==p) return 1;
 else return 0;
}

void Point_T3000::putpoint( byte num, byte p_type, byte p)
{
 number = num;
 point_type = p_type;
 panel = p;
}

void Point_T3000::getpoint( byte *num, byte *p_type, byte *p)
{
 *num = number;
 *p_type = point_type;
 *p = panel;
}

void Point_T3000::setzero(void)
{
 number = 0;
 point_type = 0;
 panel = 0;
}

int Point_T3000::zero(void)
{
 if( point_type != 0 ) return 0;
 else return 1;
}

int Point_T3000::operator==(Point_T3000 a)
{
 int i=0;
 if(     a.number != number     ) return 0;
 if( a.point_type != point_type ) return 0;
 if(      a.panel != panel      ) return 0;
 return 1;
}

void Point_T3000::operator=(const Point_T3000 &copy)
{
 int i=0;
 if(this == &copy) return;
 number = copy.number;
 point_type = copy.point_type;
 panel = copy.panel;
}

/* Point_Net_T3000;*/
int Point_Net::cmp(	byte num, byte p_type, byte p, int  net)
{
 if(number==num && point_type==p_type && panel==p && network==net) return 1;
 else return 0;
}

void Point_Net::putpoint( byte num, byte p_type, byte p, int  net)
{
 number = num;
 point_type = p_type;
 panel = p;
 network = net;
}

void Point_Net::getpoint( byte *num, byte *p_type, byte *p, int *net)
{
 *num = number;
 *p_type = point_type;
 *p = panel;
 *net = network;
}

void Point_Net::setzero(void)
{
 number = 0;
 point_type = 0;
 panel = 0;
 network = 0;
}

int Point_Net::zero(void)
{
 if( point_type != 0 ) return 0;
 else return 1;
}

int Point_Net::operator==(Point_Net compare)
{
 int i=0;
 if(   	compare.number != number     ) return 0;
 if( compare.point_type != point_type ) return 0;
 if(      compare.panel != panel      ) return 0;
 if(   compare.network  != network    ) return 0;
 return 1;
}

void Point_Net::operator=(const Point_Net &copy)
{
 int i=0;
 if(this == &copy) return;
 number = copy.number;
 point_type = copy.point_type;
 panel = copy.panel;
 network = copy.network;
}

uint search_point( Point &point, char *buff, char * & point_adr,
																		uint & point_length, Search_type order )
{
	asm push es
	byte i, j, no_of_points, type, position = 255;
	uint label_pos, length = 0, name_length, label_length;
	char *data_pointer, *p_name, *p_label;
	byte desc;
	for( i=1;i<13;i++)
	{
		name_length = label_length = label_pos = desc = 0;
		no_of_points = ptr_panel->table_bank[i-1];
		data_pointer = (char *)ptr_panel->info[i-1].address;
		point_length = ptr_panel->info[i-1].str_size;
		switch( i )
		{
			case OUT+1:
			case IN+1:
			case VAR+1:
			case WR+1:
			case AR+1:
			case PRG+1:
			case GRP+1:
				label_pos = 21;
				break;
			case AMON+1:
			case AY+1:
			case TBL+1:
				desc = 255;
				break;
			default:
			{
				continue;
			}
		}
		if( label_pos < 255 )
		{
			if( order == DESCRIPTOR_POINT || order == LENGTH_POINT )
			{
				if( point.point_type == i )
				{
					for( j=0;j<no_of_points;j++)
					{
						if( desc != 255 )
							name_length = 1+strlen( p_name=rtrim( data_pointer+j*point_length ) );
						if( label_pos != 255 )
							label_length = 1+strlen( p_label=rtrim( data_pointer+j*point_length+label_pos ) );
						length += ( name_length + label_length );
						if( order == DESCRIPTOR_POINT )
						{
							if( desc != 255 )
							{
								_fmemcpy( buff, p_name, name_length );
								buff += name_length;
							}
							if( label_pos != 255 )
							{
								_fmemcpy( buff, p_label, label_length );
								buff += label_length;
							}
						}
					}
				}
				else continue;
			}
			else
			{
				for( j=0;j<no_of_points;j++)
				{
					if( order == COMPARE )
					{
						if( !strcmp( buff, rtrim(data_pointer+j*point_length+label_pos) ) )
						{
							position = j;
							point_adr = data_pointer+j*point_length;
							break;
						}
					}
					else
					{
						if( desc != 255 )
							name_length = 1+strlen( p_name=rtrim( data_pointer+j*point_length ) );
						if( label_pos != 255 )
							label_length = 1+strlen( p_label=rtrim( data_pointer+j*point_length+label_pos ) );
						length += ( name_length + label_length );
						if( order == ALL_DESCRIPTORS )
						{
							if( desc != 255 )
							{
								_fmemcpy( buff, p_name, name_length );
								buff += name_length;
							}
							if( label_pos != 255 )
							{
							  _fmemcpy( buff, p_label, label_length );
							  buff += label_length;
							}
						}
					}
				}
			}
		}
		if( position < no_of_points )
		{
			type = i;
			break;
		}
	}
	if( order == COMPARE )
	{
		if( i < 13 )
		{
			point.number = position;
			point.point_type = type;
			asm pop es
			return 1;
		}
		else {asm pop es; return 0;}
	}
	else {asm pop es; return length;}
asm pop es;
}

