#ifndef _BASECLAS_H
#define _BASECLAS_H

#include "t3000def.h"
#include "recdef.h"
#include "color.hpp"
#include "tif.hpp"
#include "tifcodec.hpp"
#include "rs232.h"

extern void *newalloc(long size);
extern void newdelete(void *ptr);

class GGrid;

typedef struct {
	long     time;
	unsigned onoff  : 1 ;  // 0=OFF 1=ON
	unsigned next   :15 ;
} Heap_dmon;

typedef struct {
	char view_name[11];
	char onoff;
	long timerange;
} Views;

typedef union 	{
	Analog_units_equate analog_unit;
	Digital_units_equate digital_unit;
} Point_info_units;

/* Point*/
class Point{
 public:
	byte number		;
	byte point_type;
};

/* Point_T3000;*/
class Point_T3000 {
 public:
	byte number		;
	byte point_type;
	byte panel	 ;
 public:
	void setzero(void);
	int zero(void);
	int cmp(byte num, byte p_type, byte p);
	void putpoint( byte num, byte p_type, byte p);
	void getpoint( byte *num, byte *p_type, byte *p);
	int operator==(Point_T3000 a);
	void operator=(const Point_T3000 &copy);
};

/* Point_Net_T3000;*/
class Point_Net {
 public:
	byte number		;
	byte point_type;
	byte panel		;
	int  network;
 public:
	void setzero(void);
	int zero(void);
	int cmp(	byte num, byte p_type, byte p, int  net);
	void putpoint(	byte num, byte p_type, byte p, int  net);
	void getpoint(	byte *num, byte *p_type, byte *p, int *net);
	int operator==(Point_Net compare);
	void operator=(const Point_Net &copy);
};

typedef struct{
		long prev_header;
		char n_inputs;
		Point_Net      inputs[MAX_POINTS_IN_MONITOR];
		unsigned long time_last_sample[MAX_POINTS_IN_MONITOR];
		unsigned     n_sample[MAX_POINTS_IN_MONITOR];
		long offset[MAX_POINTS_IN_MONITOR];
		char onoff[MAX_POINTS_IN_MONITOR];
} Header_dmon;

typedef struct{
		 long prev_header;
		 char n_inputs;
		 Point_Net inputs[MAX_POINTS_IN_MONITOR];
		 long interval;
		 unsigned long time_last_sample;
		 unsigned n_sample;
} Header_amon;

typedef struct {
	Point_Net point;
	long point_value;
	unsigned auto_manual	     : 1;  // 0=auto, 1=manual
	unsigned digital_analog	   : 1;  // 0=digital, 1=analog
	unsigned description_label : 3;  // 0=display description, 1=display label
	unsigned security	         : 2;  // 0-3 correspond to 2-5 access level
	unsigned decomisioned	     : 1;  // 0=normal, 1=point decommissioned
	unsigned units             : 8;
} Point_info;


typedef struct {
	byte number_subA_panels; // ( 1 byte ; 0-124 )
	byte number_subB_panels; // ( 1 byte ; 0-124 )
	} Stat_x;

typedef struct {
	byte   panel;
	int    network;
	char   panel_name[16];
	char   network_name[16];
  } PanelId;

typedef struct {
	byte   panel_type;
	ulong  active_panels;
	 unsigned int des_length;
	int    version;
	byte   panel_number;
	char   panel_name[NAME_SIZE];
	int    network;
	char   network_name[NAME_SIZE];
} Panel_info1;

typedef struct {
	byte   channel_descriptor;
	byte   cards_status;
	byte   cards_power;
	byte   power_down;
  } Panel_info2;

typedef struct {
	byte   port_name;
	ulong  baud_rate;
	byte   media_type;
	byte   prg_number;
	} MiniCommInfo;

typedef byte  Subtype;; // (1 byte ; 128-252 = types 1-125, 253=type 0)


typedef byte Sub_a_b; //	(1 byte ; 0=SubA, 1=SubB)


typedef byte Mass_x;; // (1 byte , bit0; 0=bad, 1=good)


class icon {
 public:
	char name[13];
	int  width;
	int  height;
	rgb  pal[16];
  signed char status;
	TIFFIMAGEDEF idef;
	TiffDecoder  tifd;

	icon(void);
	icon( char *fn );
	void load_icon( char *fn );
	~icon( void );
};

class Icon 
{
 public:
	int  x,y;
	signed char bkgnd_color;
	char *image_under;
	icon *ptr_icon;
	Icon(icon *p, int bkgnd = -9);
	int draw_icon(int x, int y, char copy = 0, rgb *current_pal=NULL, char save_under=1);
	~Icon(void);
};


typedef struct
{
	Point_info 	point_info; 				/* 11 bytes*/

	unsigned 	show_point		: 1;
	unsigned 	icon_name_index: 7;
	unsigned 	nr_element     : 8;

	long        high_limit;
	long        low_limit;

	unsigned 	graphic_y_coordinate	: 10;
	unsigned 	off_low_color			: 4;
	unsigned 	type_icon	  	      : 2;

	unsigned 	graphic_x_coordinate	: 10;
	unsigned 	on_high_color			: 4;
	unsigned 	display_point_name	: 1;
	unsigned 	default_icon			: 1;

	unsigned 	text_x_coordinate    : 7;
	unsigned 	modify               : 1;
	unsigned 	point_absent         : 1;    // 0 - point present, 1 - point absent
	unsigned 	where_point          : 2;
	unsigned 	text_y_coordinate    : 5;

	signed char bkgnd_icon;

	unsigned		xicon                : 10;
	unsigned 	text_place				: 4;
	unsigned 	text_present			: 1;
	unsigned 	icon_present			: 1;

	unsigned		yicon                : 10;
	unsigned 	text_size		      : 2;
	unsigned 	normal_color	      : 4;

}	Str_grp_element; /*8+2+4+4+2+2+1+1+2+2 = 32*/

typedef struct
{
	char        *ptr_save_bkgnd;
	byte        nchar;
	struct Icon *icon;
} Str_grp_work_data;

typedef struct
{
	Str_grp_element	   huge *ptrgrp;
	int 						nr_elements;
} Control_group_elements;

typedef struct
{
 public:
	byte current_group;
	byte nummber_of_groups;
	Str_grp_element *str_grp_element;
} Str_grp_block;

typedef struct
{
	int second;		// 0-59
	int minute;    		// 0-59
	int hour;      		// 0-23
	int day;       		// 0-31
	int month;     		// 0-11
	int year;      		// 0-99
	int weekday;   		// 0-6, 0=Sunday
	int day_of_year; 	// 0-365
	int unused;
} Time_block_sm;


typedef struct {
	byte grpsize;       // 0-6 inputs per analog monitor
	byte number_of_mon; // 0-99 monitors with this definition
	byte length;        // 0-255 data elements
	unsigned digital_analog	:1;  // 0-digital monitor, 1-analog monitor
	unsigned unused		   :3;
	unsigned two_or_4_bytes :1;  // 0=2 byte s per analog sample, 1=4 byte s
	unsigned not_used	      :3;
} Monitor_element;

class Block
{
 public:
	HHeader h	;
	RecordStruct r;
	GGrid *pgrid;
	byte current_point,panel_type,panel;
	int network;
	byte number_of_points;
	byte bank;
//	Sub_a_b net_type;
	byte point_number;
	signed char type;
	int fields_number;


	char *ptr_line_buf;

	 Block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum, int fields, char *p_line_buf);
	 int GetAlpha(FIELDHANDLE hfield, int bufsize, char *dest);
	 int PutAlpha(FIELDHANDLE hfield, char *buf);
	 char *GetFldName(FIELDHANDLE hfield);
	 int GetFldSize(FIELDHANDLE hfield);
	 int NextRec(void);
	 int FirstRec(void);
	 int GotoRec(RECORDNUMBER record_number);
	 int NRec(void);
	 int NFields(void);
	 void nr_point(char *buf);
	 void SetBank(byte b);
	 int getalpha(FIELDHANDLE field, char *dest, int length);
	 int getpoint(FIELDHANDLE field, Point_Net point, char *dest, int read);
	 int getpoint(FIELDHANDLE field, Point_T3000 point, char *dest, int read);
	 int readint(FIELDHANDLE field, int *pi,  int length, char *p, int read, int min=0, int max=0);
//	 int readfloat(FIELDHANDLE field, float *pf,  int length, int dec, char *p, int read, float min=-1000000000, float max=1000000000);
	 int readfloat(FIELDHANDLE field, long *pf,  int length, int dec, char *p, int read, float min=-1000000000, float max=1000000000);
	 int readinterval(FIELDHANDLE field, char *buf, long *seconds , int *minutes, int *hours );
	 int checklocal(void); 
	 void *operator new(size_t size){return(newalloc((long)size));};
	 void operator delete(void *ptr){newdelete(ptr);};
};

typedef struct {
	char user_name[8];
	unsigned port	: 1;
	unsigned unused	: 15;
	long log_on_time;
	long log_off_time;
	} User_element;

typedef struct
{
	unsigned int current_user;
	unsigned number_of_users;
	User_element *block;
} User_block;

typedef struct {
	 char direct;
	 char digital_units_off[12];       //12 bytes; string)
	 char digital_units_on[12];        //12 bytes; string)
} Units_element;             // 30 bytes;

class Units_block  : public Block
{
 public:
	Units_element *block;
	struct UNITS_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField

	 Units_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Units_block();
};

/*************************************
**********  William add  *************
********     11.19.1997  *************
**********   code begin  *************
**************************************/
/*
typedef struct
{
	char description[21]; 	      // (21 bytes; string)
	char roomnumber[4];		// 4 bytes: string
	int  sensorid;			// 2 bytes: int hardware number
	byte sensoradd;  // 1 byte: max sensor address is 256
	unsigned room_temp		  : 6; // range 0 -- 40 .C
	unsigned auto_manual		: 1;  // (1 bit; 0=auto, 1=manual)
	unsigned room_status    : 1;  // 0 - empty  1 - occupied
	unsigned set_temp			  : 5;  // range 10 - 30 .C
	unsigned unused 			  : 3;

	byte auto_time; // time left to auto control 15-120 min(step 5 min),last

} Str_netstat_point;  // 21+4+2+1+2+1=31
*/

// structure for single netstat
typedef struct{
	char description[21];//modify by dina long, Feb.3,1998
	int  sensorid;        // 2 bytes , for hardware number
	byte sensoradd;      // 1 byte: max sensor address 32
//	byte valve;        // 1 byte: 0% - 100%
//	byte cov;          // cov define by user , range 0.1 -- 0.5
	byte version;        // netstat version
	long room_temp;
	long set_temp;
	byte auto_manual;
/*
	unsigned room_temp		:6;
	unsigned auto_manual	:1;
	unsigned occupied		  :1;
	unsigned set_temp		  :5;
	unsigned fanspeed     :2;
	unsigned status			  :1; // 1-heat 0-cool
	unsigned acting_type	:4; // set netstat to act as a dirrerent type
	unsigned change_flag	:1; // 0 - no change, slaver report IM_OK
							            	// 1 - change,  slaver report change
*/
} Str_netstat_point; // 2+ 1+1+1+1+ 1+1+ 1=9

/*
// structure for netstat in t3000
typedef struct
{
	char description[12]; 	      // (21 bytes; string)
//	char label[9];
//	char roomnumber[4];		// 4 bytes: string
//	byte auto_time; // time left to auto control 15-120 min(step 5 min),last
	Str_netstat_point  single;
} Str_netstat_point_T3000;  // 21+9+4+1+9=44
*/

class Netstat_block : public Block
{
 public:
	Str_netstat_point *block;
	struct NETSTAT_LineBuf line_buf;
	char stuff;  //  un octet de zero pt apel ultim field cu GetField

	 Netstat_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Netstat_block();
};
/**************************************
**********  William add  *************
********     11.19.1997  *************
**********    code end   *************
**************************************/

typedef struct
{
	char description[21]; 	       /* (21 bytes; string)*/
	char label[9];		       /* (9 bytes; string)*/

	long value;		       /* (4 bytes; long) */

	unsigned auto_manual	   : 1;  /* (1 bit; 0=auto, 1=manual)*/
	unsigned digital_analog : 1;  /* (1 bit; 0=digital, 1=analog)*/
	unsigned access_level	: 3;  /* (3 bits; 0-5)*/
	unsigned control        : 1;  /* (1 bit; 0=off, 1=on)*/
	unsigned digital_control: 1;  /* (1 bit)*/
	unsigned decom	       	: 1;  /* (1 bit; 0=ok, 1=point decommissioned)*/
	unsigned range          : 8;	/* (1 Byte ; output_range_equate)*/

	byte m_del_low;  /* (1 Byte ; if analog then low)*/
	byte s_del_high; /* (1 Byte ; if analog then high)*/
	unsigned int delay_timer;      /* (2 bytes;  seconds,minutes)*/

} Str_out_point;  /* 21+4+2+2+9 = 40 */

class Output_block : public Block
{
 public:
	Str_out_point *block;
	struct OUT_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField

	 Output_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Output_block();
};


typedef struct
{
	char description[21]; 	      /* (21 bytes; string)*/
	char label[9];		      	/* (9 bytes; string)*/

	long value;		     						/* (4 bytes; long)*/

	unsigned filter		      : 3;  /* (3 bits; 0=1,1=2,2=4,3=8,4=16,5=32,6=64,7=128)*/
	unsigned decom		      : 1;  /*	(1 bit; 0=ok, 1=point decommissioned)*/
	unsigned sen_on		      : 1;  /* (1 bit)*/
	unsigned sen_off	      : 1;  /* (1 bit)*/
	unsigned control 	      : 1; /*  (1 bit; 0=OFF, 1=ON)*/
	unsigned auto_manual		: 1;  /* (1 bit; 0=auto, 1=manual)*/
	unsigned digital_analog	: 1;  /* (1 bit; 0=digital, 1=analog)*/
	unsigned calibration_sign         : 1;  /* (0 positive; 1 negativ)*/
	unsigned calibration_increment    : 1;  /* (1 bit;  0=0.1, 1=1.0)*/
	unsigned unused         	       : 5;


	byte  calibration;  /* (8 bits; -256.0 to 256.0 / -25.6 to 25.6 (msb is sign))*/

	byte        range;	      			/* (1 Byte ; input_range_equate)*/

} Str_in_point; /* 21+1+4+1+1+9+1 = 38 */

class Input_block : public Block
{
 public:
	Str_in_point *block;
	struct IN_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField

	 Input_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Input_block();
};


typedef struct
{
	char description[21];	      /*  (21 bytes; string)*/
	char label[9];		      /*  (9 bytes; string)*/

	long value;		      /*  (4 bytes; float)*/

	unsigned auto_manual	   : 1;  /*  (1 bit; 0=auto, 1=manual)*/
	unsigned digital_analog	: 1;  /*  (1 bit; 0=digital, 1=analog)*/
	unsigned control	      : 1;
	unsigned unused		   : 5;
	unsigned range          : 8; /*  (1 Byte ; variable_range_equate)*/

}	Str_variable_point; /* 21+9+4+2 = 36*/

class Var_block : public Block
{
 public:
	Str_variable_point *block;
	struct VAR_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField

	 Var_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Var_block();
};

typedef struct
{
	Point_T3000 input;	      /* (2 bytes; point)*/
	long input_value; 	      /* (4 bytes; float)*/
	long value;		      /* (4 bytes; float)*/
	Point_T3000 setpoint;	      /* (2 bytes; point)*/
	long setpoint_value;	      /* (4 bytes; float)*/
	byte units;    /* (1 Byte ; Analog_units_equate)*/

	unsigned auto_manual	    : 1; /* (1 bit; 0=auto, 1=manual)*/
	unsigned action		    : 1; /* (1 bit; 0=direct, 1=reverse)*/
	unsigned repeats_per_min : 1; /* (1 bit; 0=repeats/hour,1=repeats/min)*/
	unsigned unused		    : 1; /* (1 bit)*/
	unsigned prop_high	    : 4; /* (4 bits; high 4 bits of proportional bad)*/

	unsigned proportional    : 8;   /* (1 Byte ; 0-2000 with prop_high)*/
	byte reset;	      /* (1 Byte ; 0-255)*/
	byte bias;	      /* (1 Byte ; 0-100)*/
	byte rate;	      /* (1 Byte ; 0-2.00)*/
}	Str_controller_point; /* 2+4+4+2+4+1+1+4 = 24*/

class Controller_block : public Block
{
public:
	Str_controller_point *block;
	struct CON_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField

	 Controller_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Controller_block();
};

typedef struct
{
	char description[21];		     /* (21 bytes; string)*/
	char label[9];		      	     /*	(9 bytes; string)*/

	unsigned value 			   :1;  /* (1 bit; 0=off, 1=on)*/
	unsigned auto_manual		   :1;  /* (1 bit; 0=auto, 1=manual)*/
	unsigned override_1_value	:1;  /* (1 bit; 0=off, 1=on)*/
	unsigned override_2_value	:1;  /* (1 bit; 0=off, 1=on)*/
	unsigned off               :1;
	unsigned unused			   :11; /* (11 bits)*/

	Point_T3000 override_1;	     /* (2 bytes; point)*/
	Point_T3000 override_2;	     /* (2 bytes; point)*/

}	Str_weekly_routine_point; /* 21+2+2+2+10 = 38*/

class Weekly_routine_block : public Block
{
public:
	Str_weekly_routine_point *block;
	struct WR_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField

	 Weekly_routine_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Weekly_routine_block();
};

typedef struct
{
	char description[21]; 	    /* (21 bytes; string)*/
	char label[9];		      		/* (9 bytes; string)*/
	unsigned value				   : 1;  /* (1 bit; 0=off, 1=on)*/
	unsigned auto_manual	      : 1;  /* (1 bit; 0=auto, 1=manual)*/
	unsigned unused				: 14; 	/* ( 12 bits)*/
}	Str_annual_routine_point;   /* 21+9+2=32 bytes*/

class Annual_routine_block : public Block
{
public:
	Str_annual_routine_point *block;
	struct AR_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField

	 Annual_routine_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Annual_routine_block();
};

typedef struct
{
	char description[21]; 	        // (21 bytes; string)*/
	char label[9];			           // (9 bytes; string)*/

	unsigned int bytes;		        // (2 bytes; size in bytes of program)*/
	unsigned     on_off      : 1;    // (1 bit; 0=off; 1=on)*/
	unsigned     auto_manual : 1;    // (1 bit; 0=auto; 1=manual)*/
	unsigned     com_prg	    : 1;	  // (1 bit; 0=normal , 1=com program)*/
	unsigned     errcode	    : 5;	  // (1 bit; 0=normal end, 1=too long in program)*/
	byte         unused;                // because of mini's

}	Str_program_point;	  /* 21+9+2+1+1 = 34 bytes*/

class Program_block : public Block
{
public:
	Str_program_point *block;
	byte *code;
	int length;
	struct PRG_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField

	 Program_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Program_block();
};

typedef struct
{
	Point_T3000 input;		      	// (2 byte s; point)
	byte seconds_on_time;	// (1 byte ; 0-59)
	byte minutes_on_time;	// (1 byte ; 0-59)
	unsigned int hours_on_time;	// (2 byte s; 0-65535)
	unsigned long start_time;	// (4 byte s; time)
	unsigned int head_index;	// (2 byte s; index to next data entry)
	byte wrap_flag;	// (1 byte ; 0=no wrap, 1=data wrapped)
	byte reset_flag;	// (1 byte ; 0=not reset, 1=reset)
	unsigned int total_starts;	// (2 byte s; 0-65535 starts since start_time)
	byte day_starts;	// (1 byte ; 0-255 starts since 0:00 Hrs)
	byte data_length; 	// (1 byte ; 0-254 on/off times recorded)
	unsigned int data_segment;	// (2 byte s; used internally by panel)
} Str_digital_monitor_point;

class Digital_monitor_block:public Block
{
public:
	byte current_point;
	byte number_of_points;
	Str_digital_monitor_point	*block;
};

typedef struct
{
	char label[9];		      	  					/* 9 bytes; string */

	Point_Net    inputs[MAX_POINTS_IN_MONITOR];	/* 28 bytes; array of Point_T3000 */
	byte			 range[MAX_POINTS_IN_MONITOR]; /* 14 bytes */

	byte second_interval_time; 				/* 1 byte ; 0-59 */
	byte minute_interval_time; 				/* 1 byte ; 0-59 */
	byte hour_interval_time;   				/* 1 byte ; 0-255 */

	byte max_time_length;      /* the length of the monitor in time units */

	Views views[MAX_VIEWS];			/* 16 x MAX_VIEWS bytes */

	unsigned num_inputs     :4; 	/* total number of points */
	unsigned anum_inputs    :4; 	/* number of analog points */
	unsigned unit 				:2; 	/* 2 bits - minutes=0, hours=1, days=2	*/
	unsigned ind_views		:2; 	/* number of views */
	unsigned wrap_flag		:1;		/* (1 bit ; 0=no wrap, 1=data wrapped)*/
	unsigned status			:1;		/* monitor status 0=OFF / 1=ON */
	unsigned reset_flag		:1; 	/* 1 bit; 0=no reset, 1=reset	*/
	unsigned double_flag	   :1; 	/* 1 bit; 0= 4 bytes data, 1= 2 bytes data */

}	Str_monitor_point; 		/* 9+28+14+3+1+48+2 = 147 bytes */

typedef struct
{
	char huge *data_segment;
	unsigned start   :1;    	          // (1 bit)
	unsigned saved	  :1;    	          // (1 bit)
	unsigned unused  :6;    	          // (6 bits)
	unsigned long next_sample_time;
	unsigned int  head_index;	    // (2 byte s; index to next data entry)
	unsigned long last_sample_time;	    // (4 byte s; time)
	unsigned long last_sample_saved_time;	    // (4 byte s; time)
	unsigned int  start_index_dig[MAX_POINTS_IN_MONITOR];
	unsigned int  end_index_dig[MAX_POINTS_IN_MONITOR];

}	Str_monitor_work_data;

class Monitor_block: public Block
{
 public:
	Str_monitor_point 	*block;
	struct AMON_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField

	 Monitor_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 int compute_size(void);
	 ~Monitor_block();
};

class Amon_inputs_block: public Block
{
 public:
	Point_Net *block;
	int anum_inputs;
	struct AMON_INPUT_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField

	 Amon_inputs_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Amon_inputs_block();
};

typedef struct
{
	char description[21];				/* (21 bytes; string)	*/
	char label[9];							/* (9 bytes; string)	*/
	char picture_file[11];			/* (11 bytes; string)	*/

	byte                 update_time;       /* refresh time */
	unsigned mode			   :1;				/* (1 bit ; 0=text, 1=graphic)	*/
  unsigned state       :1;        // 1 group displayed on screen 
	unsigned xcur_grp    :14;
	int    	             ycur_grp;
} Control_group_point;				/* (size = 46 bytes)	*/

class Control_group_block: public Block
{
public:
	Control_group_point *block;
	struct GRP_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField

	 Control_group_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
//	 int fnc_group(void);
//	 int graphic_mode(void);
	 ~Control_group_block();

};

class Control_graphic_group_block: public Block
{
public:
	Str_grp_element *block;
	struct G_GRP_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField

	 Control_graphic_group_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Control_graphic_group_block();
};

class Str_table_block
{
public:
	byte number_of_arrays;
	Analog_units_equate table1_units;
	char unused1[5];
	Analog_units_equate table2_units;
	char unused2[5];
	Analog_units_equate table3_units;
	char unused3[5];
	Analog_units_equate table4_units;
	char unused4[5];
	Analog_units_equate table5_units;
	char unused5[5];
	float *table1_array;
	float *table2_array;
	float *table3_array;
	float *table4_array;
	float *table5_array;

//	Str_table_block( byte );
//	~Str_table_block();
};


typedef struct 		// (size = 11 byte s)
{
	char label[9];		     // (9 byte s; string)
	int  length;  	 // (1 byte ; 0-255)
} Str_array_point;

class Array_block: public Block
{
 public:
	Str_array_point *block;
	struct AY_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField

	 Array_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Array_block();
};

typedef struct
{
	long value;
} Str_ayvalue_point;

class Ayvalue_block: public Block
{
 public:
	Str_ayvalue_point *block;
	struct AYvalue_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField
	int current_array;

	 Ayvalue_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Ayvalue_block();
};

typedef struct
{
	unsigned online_to_network 	  	 :1;  // (1 bit; 0=no, 1=yes)
	unsigned program_installed 	 	 :1;  // (1 bit; 0=no, 1=yes)
	unsigned mainnet_outpoints_low 	 :6;  // (6 bits; 0-127 with outpoints_high_bit)
	byte scan_rate;	     			 						// (1 byte ; 0-255 scans in 3 seconds)
	unsigned version 		 					:11; // (11 bits; 0-2047 // 0.00 - 20.47)
	unsigned network_controller_flag    :1;  // (1 bit; 0=32ioboard, 1=network controller board)
	unsigned port_configuration	 	 	:3;  // (3 bits; Port_configuration_equate)
	unsigned mini_panel_flag	 		 	:1;  // (1 bit; 0=standard_panel, 1=mini_panel)
	char panel_name[18];		      				// (18 byte s; string)
	unsigned outpoints_high_bit	 	 	:1;  // (1 bit; MSB of mainnet outpoints)
	unsigned unused		      	 		:7;  // (7 bits)
	unsigned int memory_remaining;	      // (2 byte s)
	unsigned line_status 	      	   :1;  // (1 bit; used internally by panel)
	unsigned mainnet_inpoints	 		   :7;  // (7 bits; 0-127)

} Str_status_point;

class Status_block
{
public:
	byte number_of_points;
	Str_status_point *block;
};

typedef struct {

	Point_Net point;

	unsigned 	modem     	  : 1;
	unsigned 	printer		    : 1;
	unsigned 	alarm			    : 1;
	unsigned 	restored      : 1;
	unsigned 	acknowledged  : 1;
	unsigned	ddelete		    : 1;
	unsigned  type          : 2; /* DDDD */
	unsigned  cond_type     : 4;
	unsigned  level         : 4; /* DDDD */

	unsigned long 		alarm_time;
	char 			        alarm_count;
	char 			        alarm_message[ALARM_MESSAGE_SIZE+1];
	char              none[5];
	unsigned char panel_type     :4;
	unsigned char dest_panel_type:4;
	unsigned int      alarm_id;
	byte              prg;

	byte alarm_panel;   /* (1 byte ; 1-32, panel alarm originated from)	*/
	byte where1;	      /* (1 byte ; panel# to send alarm to, 255 = all)	*/
	byte where2;	      /* (1 byte ; panel# to send alarm to, 0 = none)	*/
	byte where3;	      /* (1 byte ; panel# to send alarm to, 0 = none)	*/
	byte where4;	      /* (1 byte ; panel# to send alarm to, 0 = none)	*/
	byte where5;	      /* (1 byte ; panel# to send alarm to, 0 = none)	*/
	unsigned where_state1  :1;	      /* (1 byte ; panel# to send alarm to, 255 = all)	*/
	unsigned where_state2  :1;	      /* (1 byte ; panel# to send alarm to, 255 = all)	*/
	unsigned where_state3  :1;	      /* (1 byte ; panel# to send alarm to, 255 = all)	*/
	unsigned where_state4  :1;	      /* (1 byte ; panel# to send alarm to, 255 = all)	*/
	unsigned where_state5  :1;	      /* (1 byte ; panel# to send alarm to, 255 = all)	*/
	unsigned change_flag   :2;
	unsigned original      :1;
	unsigned no            :8;
//	unsigned line          :11;
//	byte     no;
} Alarm_point;

class Alarm_block: public Block
{
public:
	Alarm_point *block;
	struct ALARMM_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField
//	char nrmes[128];
	 Alarm_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 int sortalarm(void);
	 int savemessage(char count, char type, int point, char cond_type, char *mes, long time_mes);
	 ~Alarm_block();
};

typedef struct
{
	Point_T3000 point;
	Point_T3000 point1;
	unsigned cond1;
	long waylow;
	long low;
	long normal;
	long hi;
	long wayhi;
	unsigned time;
	signed char nrmes;
	unsigned count;
} Alarm_set_point;

class Alarm_set_block: public Block
{
public:
	Alarm_set_point *block;
	struct ALARMS_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField
	 Alarm_set_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Alarm_set_block();
};

/*
class Password_point	// (size = 22 byte s)
{
public:
	char name[10]; 		       // (10 byte s; string)
	char code[9]; 		       // (9 byte s; string)
	unsigned master_group 	   :6; // (6 bits; 0-63)
	unsigned unused		   :2; // (2 bits)
	byte access_level;    // (1 byte ; 0-99)
	byte master_menu;     // (1 byte ; 0-30)

//	Password_point( void *x );
};
*/

typedef struct
{
	char name[16]; 		       // (10 byte s; string)
	char password[9]; 		       // (9 byte s; string)
	byte access_level;    // (1 byte ; 0-99)
	unsigned long rights_access;
	byte default_panel;
	byte default_group;
	char screen_right[8];     // 2 biti per grp
	char program_right[8];    // 2 biti per prg
} Password_point;

typedef struct {
		int ind_passwords;
		Password_point	passwords[MAX_PASSW];
} Password_struct;

class Password_block: public Block
{
public:
	Password_struct *block;
	struct USER_NAME_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField
	Password_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	int GetRec(void);
	int GetField(int , char *);
	int Read(int , char);
	~Password_block();
};

typedef struct	// (size = 6 byte s)
{
	int value; 		       // (10 byte s; string)
	long unit; 		       // (9 byte s; string)
}  Tbl_point;

typedef struct
{
	char label[9];		      // (9 bytes; string)*/
	Tbl_point table[16];
} Str_tbl_point;      // size = 9+6*16 = 105

class Tbl_block: public Block
{
public:
	Str_tbl_point  *block;
	int tblno;
	struct TBL_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField
	Tbl_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	int GetRec(void);
	int GetField(int , char *);
	int Read(int , char);
	~Tbl_block();
};

typedef struct
{
	char name[41]; 		       // (10 byte s; string)
} Array1_point;

class Array1_block: public Block
{
public:
	Array1_point *block;
	struct ARRAY1_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField
	 Array1_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Array1_block();
};

typedef struct
{
	char hard_name[NAME_SIZE];         // (17 bytes; string)
	char name[NAME_SIZE]; 		       // (17 bytes; string)
	byte number;
	unsigned des_length;
	unsigned descksum;
	byte state;
	byte panel_type;
	int  version;
	byte tbl_bank[MAX_TBL_BANK];
} Station_point;

class Station_block: public Block
{
public:
	Station_point *block;
	struct ST_LineBuf line_buf;
	char stuff[2];         // un octet de zero pt apel ultim field cu GetField
	int stype;

	 Station_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Station_block();
};

typedef struct 		// (size = 16 byte s)
{
	union {
	 struct {
		byte time_on_minutes1;		// (1 byte ; 0-59)
		byte time_on_hours1;		// (1 byte ; 0-23)
		byte time_off_minutes1;	// (1 byte ; 0-59)
		byte time_off_hours1;		// (1 byte ; 0-23)
		byte time_on_minutes2;		// (1 byte ; 0-59)
		byte time_on_hours2;		// (1 byte ; 0-23)
		byte time_off_minutes2;	// (1 byte ; 0-59)
		byte time_off_hours2;		// (1 byte ; 0-23)
		byte time_on_minutes3;		// (1 byte ; 0-59)
		byte time_on_hours3;		// (1 byte ; 0-23)
		byte time_off_minutes3;	// (1 byte ; 0-59)
		byte time_off_hours3;		// (1 byte ; 0-23)
		byte time_on_minutes4;		// (1 byte ; 0-59)
		byte time_on_hours4;		// (1 byte ; 0-23)
		byte time_off_minutes4;	// (1 byte ; 0-59)
		byte time_off_hours4;		// (1 byte ; 0-23)
		} time1;
		char time2[16];
	};
} Wr_one_day;

class Weekly_routine_time_block : public Block
{
public:
	byte number_of_days;
	byte block[9][16];
//	Wr_one_day block[9];	// (array of  wr_one_day types)
	Wr_one_day *wr_day;
	int routine_num;
	struct WR_TIME_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField

	 Weekly_routine_time_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Weekly_routine_time_block();
};

class Annual_routine_time_block : public Block
{
public:
	byte number_of_days;
	byte *block;
	byte block_year[46];
	byte year[6*7*3];
	byte quarter;
	int routine_num;
	struct AR_Y_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField

	 Annual_routine_time_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 int Quarter(byte quarter);
	 int ShowDates(byte quarter);
	 ~Annual_routine_time_block();
};

// Note: January 1 is bit 0 of the first byte , January 2 is bit 1 of the first
// byte  and so on. February is always considered to have 29 days.


typedef struct
{
	unsigned int dst_on_day;	// (2 byte s; 1-366, day of year dst starts)
	unsigned int dst_off_day;	// (2 byte s; 1-366, day of year dst ends)
} Daylight_savings_block;

typedef struct
{
	unsigned host_panel	: 7;	// (7 bits, 1-32)
	unsigned suba_subb	: 1;	// (1 bit, 0=subA, 1=subB)
} Host_block;

typedef struct
{
		char system_name[L_DIAL_SYSTEM_NAME];   		//
		char phone_number[L_DIAL_PHONE_NUMBER];    	//
		char des_file[L_DIAL_DES_FILE];     				//
		char menu_file[L_DIAL_MENU_FILE];          	//
		int  baud_rate;          										//
		char link_number[L_DIAL_LINK_NUMBER];   		//
} Dial_list_point; 

class Dial_list_block : public Block
{
	public:
		Dial_list_point *block;
		struct DIAL_LineBuf line_buf;
		char stuff;         // un octet de zero pt apel ultim field cu GetField

		Dial_list_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
		int GetRec(void);
		int GetField(int , char *);
		int Read(int , char);
		~Dial_list_block();
};

class Connect_com_block: public Block
{
 public:
	Comm_Info *block;
	struct COM_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField

	 Connect_com_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Connect_com_block();
};

typedef struct
{
	int  net_no;
	char net_name[17];
	int  net_con;
} Net_point;

class Net_block: public Block
{
 public:
	Net_point *block;
   ulong  activepanels[32];
   int record_select;
	struct NET_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField

	 Net_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Net_block();
};

typedef struct
{
	char name[16]; 	        // (21 bytes; string)*/
	char type[5];			           // (9 bytes; string)*/
	char version[5];			           // (9 bytes; string)*/
	char prg[8];			           // (9 bytes; string)*/
	char update[10];			           // (9 bytes; string)*/
	char note[8];
}	Str_netstatus_point;	  /* 21+9+2+1+1 = 34 bytes*/

class Netstatus_block : public Block
{
public:
	Str_netstatus_point *block;
	struct NS_LineBuf line_buf;
	char stuff;         // un octet de zero pt apel ultim field cu GetField

	 Netstatus_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum);
	 int GetRec(void);
	 int GetField(int , char *);
	 int Read(int , char);
	 ~Netstatus_block();
};

typedef struct
{
	int  ti_sec;         // 0-59
	int  ti_min;         // 0-59
	int  ti_hour;           // 0-23
	int  dayofmonth;   // 1-31
	int  month;          // 0-11
	int  year;           // year - 1900
	int  dayofweek;        // 0-6 ; 0=sunday
	int  dayofyear;    // 0-365 gmtime
	int  isdst;
} Time_block;

typedef struct
{
	byte  ti_sec;         // 0-59
	byte  ti_min;         // 0-59
	byte  ti_hour;           // 0-23
	byte  dayofmonth;   // 1-31
	byte  month;          // 0-11
	byte  year;           // year - 1900
	byte  dayofweek;        // 0-6 ; 0=sunday
	int   dayofyear;    // 0-365 gmtime
	signed char isdst;
} Time_block_mini;

struct remote_local_list {
	 Point_Net point;
	 int index;
	 };

/*
typedef struct
{
	Point_Net   point;
} WANT_POINTS;
*/

typedef struct
{
	Point_info		info;
}	NETWORK_POINTS;

typedef struct
{
	char			  	state;
	Point_info	 	info;
	char           count;
	unsigned		 	read			:2;
	unsigned		 	write			:2;
	unsigned		 	read_write	:2;
	unsigned		 	change		:2;
}	REMOTE_POINTS;

class ConnectionData
{
	public:
		signed char FirstToken;
		byte 		NS; 	// Next Station
		byte 		PS;    // Poll Station
//		byte 		TS;    // This Station
		byte 		OS;    // Original Station
		Panel_info1 			panel_info1;
		unsigned long 		need_info;
		Station_point 		station_list[MAX_STATIONS];
		POOL              ser_pool;
		Media_type			  media;
		char 							*ser_data;
		byte						  task_number;
		signed char       send_info;
		byte              routing_table_entry;
		byte              com_port;
	  byte           		port_number;
		int               laststation_connected;
		signed char       laststation_connectedflag;
		char              panelconnected;
		int               panelOff;
		int               receivedpollformaster;
    int               newpanelbehind;
    char              sendinfo_flag;
    char              receivedtoken;
    byte              nextpanelisoff;
	public :
		ConnectionData(void){};
		~ConnectionData(void){};
};


typedef struct              /* 5 bytes */
{
	unsigned point_no  :4;
	unsigned unused    :3;
	unsigned value     :1;
	long             time;
} Digital_sample;        /* 5 bytes */

typedef struct              /* 645 bytes */
{
	Point_Net     inputs[MAX_POINTS_IN_MONITOR]; /* 70 bytes; array of Point_Net */

	unsigned monitor	       :4; /* monitors' number */
	unsigned no_points       :4; /* number of points in block */

/*	unsigned tenths_of_seconds    : 4; /* 4 bits ; 0-15 */
/*	unsigned second_interval_time : 6; /* 6 bits ; 0-59 */
/*	unsigned minute_interval_time : 6; /* 6 bits ; 0-59 */

	byte second_interval_time; /* 1 Byte ; 0-59 */
	byte minute_interval_time; /* 1 Byte ; 0-59 */
	byte hour_interval_time;   /* 1 Byte ; 0-255 */

	unsigned priority	       :2; /* 0-block empty, 1-low, 2-medium, 3-high */
	unsigned first_block     :1; /* 1 - this block is the first in the chain */
	unsigned last_block      :1; /* 1 - this block is the last in the chain */
	unsigned analog_digital  :1; /* 0 - analog, 1 - digital */
	unsigned block_state     :1; /* 0 = unused, 1 = used */
	unsigned fast_sampling   :1; /* 0 = normal sampling 1 = fast sampling */
	unsigned wrap_around     :1; /* 1 - wrapped  */

	long          start_time; /* time of first sample */

	uint          index;      /* pointer to the new free location in block */
														/* equal with the number of samples in block */
	byte          next_block; /* pointer to the next block in chain
																255 = last block in chain */
	byte          block_no;      /* position of block in chain */

	unsigned      last_digital_state : 14;
	unsigned      not_used           :  2;
/*  unsigned      index_fast         :  2;*/

	union {
	long           analog[MAX_ANALOG_SAMPLES_PER_BLOCK];  /*  140*4 = 560 bytes  */
	Digital_sample digital[MAX_DIGITAL_SAMPLES_PER_BLOCK]; /* 112 */
	byte           raw_byte[4*MAX_ANALOG_SAMPLES_PER_BLOCK]; /* 560 */
	uint           raw_int[2*MAX_ANALOG_SAMPLES_PER_BLOCK];  /* 280 */
	} data;

}	Mini_Monitor_Block;         /* 645 bytes */







#endif // _BASECLASS_H