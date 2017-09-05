#ifndef _AIO_H
#define _AIO_H
#include "baseclas.h"

/*
#define MAX_OUTS	32
#define MAX_INS	32
#define MAX_VARS	128
#define MAX_CONS	16
#define MAX_WR		16
#define MAX_AR		8
#define MAX_PRGS	32
#define MAX_TABS	5
#define MAX_DIGM	1
#define MAX_ANALM	16
#define MAX_GCONS	32
#define MAX_GRPS 	32
#define MAX_ARRAYS	16
#define MAX_INFO_TYPE 50
*/

#define MAX_BOARDS	4

#define BOARD_PRESENT	0


/*
///////
#define MAX_OUTS	3
#define MAX_INS	1
#define MAX_VARS	1
#define MAX_CONS	1
#define MAX_WR		1
#define MAX_AR		1
#define MAX_PRGS	1
#define MAX_TABS	1
#define MAX_DIGM	1
#define MAX_ANALM	1
#define MAX_GCONS	1
#define MAX_GRPS 	1
#define MAX_ARRAYS	1
#define MAX_ALARMS  1
#define MAX_WRT     1
#define MAX_ARD      1
#define MAX_STAT    1
#define MAX_AMON   1
#define MAX_DMON   1
#define MAX_UNITS  1
#define MAX_PASSW  1
#define MAX_GRP    1
#define MAX_TIME    1
#define MAX_MONSET   1
#define MAX_USERS     1
#define MAX_DST        1
// #define MAX_
#define PROGRAM_SIZE 100
#define MAX_ELEM	3

#define uint	unsigned int

#define MAX_BOARDS	1
////////
*/

typedef struct {
		uint		base_adr;
		byte		board_number;
		long		quartz_freq;
		uint		sample_time;
		uint 		watchdog_interval;
		byte		no_outs;
		byte		no_ins;
		byte		in_mask;
		byte		out_mask;
		byte		status;
		unsigned watchdog_flag	:1;
		unsigned unused		:7;
		} 			Board_info;

typedef struct {
		byte		status;
		byte		in_mask;
		byte		out_mask;
		} 	Aux_board_info;

typedef enum { SET_POINT, GET_POINT, SET_ALL, GET_ALL, SET_RATE, DESCRIPTION,
	GET_STATUS, TEST_INTERFACE, RESET_PC, RESET_CARD, WATCHDOG_ON, WATCHDOG_OFF,
	SET_WATCHDOG, GET_NO_POINTS, GET_ALL_POINTS, POWER_TOGGLE, VERSION = 0x0A0,
	SPECIAL = 0xE0 } Order;

typedef enum { AIO_OK, AIO_BLOCKED, AIO_ERROR, FUNCTION_NOT_AVAILABLE } Aio_Error;

typedef enum { VER0_CARD, VER1_CARD, VER2_CARD } Card_Type;

typedef struct {
	int		filter_last;
	long	filter_sum;
	uint	average;
	uint	last;
	uint 	ticks;
	}			In_aux;

typedef struct {
	long	old_err;
	long 	error_area;
	long 	oi;
	}	Con_aux;

typedef struct {
	char *address;
	int str_size;
	int max_points;
	char *name;
	} Info_Table;


class Aio
{
public:
	byte GlPanel, GlPanel_type;
	int  GlNetwork;
//	Sub_a_b GlNet_type;
	Card_Type						       card_type;
	byte 								       number_of_boards;
	byte								       panel_number;
	byte 								       user_number;
	int								         time;  // scan interval in seconds
	char 								       system_name[22];
//	char 								master_password[20];
	byte								       table_bank[MAX_TBL_BANK];
	byte								       lock[MAX_INFO_TYPE];
	In_aux							       in_aux[MAX_INS];
	Con_aux							       con_aux[MAX_CONS];
	Info_Table					       info[18];
//	Str_grp_element				group_elements[MAX_ELEM];
	Str_out_point   				   outputs[MAX_OUTS];
	Str_in_point    				   inputs[MAX_INS];
//	char                       in_control[MAX_INS];
	Str_variable_point			   vars[MAX_VARS];
//	char                       var_control[MAX_VARS];
	Str_controller_point 		   controllers[MAX_CONS];
	Str_monitor_point				   analog_mon[MAX_ANALM];
	Str_monitor_work_data      monitor_work_data[MAX_ANALM];
	Str_weekly_routine_point   weekly_routines[MAX_WR];
	Wr_one_day                 wr_times[MAX_WR][9];
	Str_annual_routine_point	 annual_routines[MAX_AR];
	byte                       ar_dates[MAX_AR][46];
	Str_program_point	 			   programs[MAX_PRGS];
	byte 			     				     *program_codes[MAX_PRGS];   //  pointer to code
	Control_group_point	 		   control_groups[MAX_GRPS];
	Control_group_elements     control_group_elements[MAX_GRPS];
	Station_point					     local_stations[32];
	Password_struct            passwords;
	Alarm_point 				       alarms[MAX_ALARMS];
	int                        ind_alarms;
	Alarm_set_point 		       alarms_set[MAX_ALARMS_SET];
	int                        ind_alarms_set;
	Str_array_point 				   arrays[MAX_ARRAYS];
	long 							       	 *arrays_data[MAX_ARRAYS];
	char 		            		   *program_code;
	unsigned int        		   code_length;
	Units_element					     units[MAX_UNITS];
	int						             in_data[MAX_OUTS];
	int						             out_data[MAX_INS];
//	char                       Icon_name_table[MAX_ICON_NAME_TABLE][14];
  Str_netstat_point          netstats[MAX_NETSTATS];
public:
	void clearpanel(void);
	Aio( byte nr_boards);
	~Aio();
	Aio_Error Aio_Control( Order comm, byte *data_buffer, byte p_number );
	void Aio::Config_dacqd_card( void );
	void	Controller( byte p_number );
//	void Aio::setcodeprg(int routine_num);
	void convert_in();
	void convert_out();
	long convert_in_point( byte, byte );
private:
	long calibration( byte point );
	long test_match( Analog_input_range_equate range, uint raw );
	long test_match_custom( Analog_input_range_equate  range, long raw );
	uint filter( uint sample, byte point );
	void init_info_table( void );
//	void Aio::setcodeprg(int routine_num);
};

class GWDialog;

class Panel:public Aio
{
public:
			char Program_Path[64]   ;
			char Descriptor_Path[64];
			char Basic_Path[64]     ;
			char Monitor_Path[64]   ;
			char Graphics_Path[64]  ;
			char DataBase_Path[64]  ;
			char Default_Program[64];
//			char panel_name[32][20];

			int qt;
	 public:


//			Panel(PanelType type, RS232PortName name, unsigned int baud_rate,
//	char parity, byte length, byte stop, Connection_port port_conn );
			Panel();
			Panel(Panel &copy);
			void operator=(const Panel &copy);

			byte	point_type;
			void select_panel(int);
			void select_subpanel();
			void subselect(GWDialog *D);
//			void Select(int man,char **argv, char **message);
			void Select(int man);
			int  connect_panel_proc(int t=0);
			void Path();
			void go_graphic(int t=0);
			void go_text(void);
//			void showpoints(int man, int arg=0);
			int loadprg(char *file, Panel_info1 *panel_info, unsigned char *tblbank, int local=1, int control=1);
			int file(int man=-1);
			int savefile(char *, Panel_info1 *panel_info, unsigned char *tblbank, int local=1);

			friend void file_path_o1(GWDialog *D);
			friend void file_path_o2(GWDialog *D);
			friend void file_path_o3(GWDialog *D);
			friend void file_path_o4(GWDialog *D);
			friend void file_path_o5(GWDialog *D);
			friend void pselect(GWDialog *D);

};
#endif