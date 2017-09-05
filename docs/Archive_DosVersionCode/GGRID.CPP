#define GGRID


#include <math.h>
#include <mem.h>
#include <dir.h>
#include <bios.h>
#include <graphics.h>
extern void *newalloc(long size);
extern void newdelete(void *ptr);
#include "ggrid.h"
#include "T3000hlp.h"

#include "recstruc.h"
#include "serial.h"

#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))

#include "mtkernel.h"
#include "vga12.h"
#include "xms.h"
#include "rs485.h"
extern int mode_text;
extern int error_net;
extern int networkaddress;

extern char arights_grid;
extern int line_style;
extern FILEHANDLE syslist_handle;
extern int grid_record_number;
extern int entry_selected;
#define DOTTED 2
#define FILL 1

#define ESC 27

extern int Black;                 //0
extern int Blue;                   //1
extern int Green;                 //2
extern int Cyan;                   //3
extern int Darkgray;           //8
extern int White;                 //15
extern int Green1;   //13
extern int Lightgray;         //7

extern int Red;                     //4
extern int Lightblue;         //9
extern int Lightgreen;       //10
extern int Lightcyan;         //11
extern int Lightred;           //12
extern int Yellow;               //14
extern int Blue1;

#ifdef NETWORK_COMM
extern OPERATOR_LIST	operator_list;
extern NETBIOS_Presence	Netbios_state;
#endif

//extern Password_point	passwords[MAX_PASSW];
extern Password_struct passwords;
extern Station_point station_list[32];

extern char station_name[NAME_SIZE];
extern int  station_num;

extern int local_panel;
extern int simulator;

extern char Station_NAME[NAME_SIZE];
extern int  Station_NUM;

extern char present_analog_monitor;
extern int fond_color;

//extern long huge heap_array[];
extern long huge *heap_array;
extern int communication;
extern int refresh_time;

extern Panel_info1 panel_info1;
extern Str_tbl_point custom_tab[MAX_TABS];

extern GWDialog *pm;
extern Panel *ptr_panel;
extern void DeleteMessage(GWDialog *p);
extern void DisplayMessage(int lx, int ly, int rx, int ry, char *title, char *message, GWindow **Er1, int fcolor=Black, GWindow *Er2=NULL, long delay=0);
extern void DisplayMessageT(int lx, int ly, int rx, int ry, char *title, char *message, GWindow **Er1, int fcolor=Black, GWindow *Er2=NULL, long delay=0);
extern int bioskey_new(int cmd);
extern void save_config(int what);
extern int local_request(int panel, int network);

extern int sendtoprint(void);
extern unsigned int countlength(int point_type, int arg);
extern void memsize(void);
extern long psample(long *interv, int mon);
extern void mclrscr(char x1, char y1, char x2, char y2, char col);
extern int initamoninputsscreen(void);
extern int check_access(int ptype, int num=-1, int mes=R_NA);
extern int net_call(int command, int arg,  char *data, uint *length , int dest,
				 int network, int others=0, int timeout=TIMEOUT_NETCALL,
				 char *returnargs=NULL, int *length_returnargs=NULL,
				 char *sendargs=NULL, int length_sendargs=0, char bytearg=0, int port=-1);
extern void update_alarm_tbl(Alarm_point *block, int max_points_bank );
extern int localnetwork(int net);

extern char huge *ctrlbreak_text;
extern char *lin_text;
extern char huge *lin_menu;
extern char huge *lin_hor;
extern char huge *lin_ver;
extern int dxscreen, dyscreen;

extern int extended_memory;
extern unsigned long  microsec; // ora curenta exprimata in secunde
//extern char showsign;

extern void save_m(void);
void move_screen(int sx, int sy, int jx, int jy, int where, int size);
void msettextstyle(int font, int dir, int chars);
extern void upcustomunit(Units_element	*punits);
extern void result_ser(RS232Error result, int rs485=0);
void clear_color(int lx, int length, int ly, int ry, char *lin_text, int bkgnd, int frgnd);
//extern char huge  des[MAX_DES];
//int savedes();
//int loaddes();

//#include "burstruct.h"
signed char point_des[AY+1]={DOUT,DIN,DVAR,-1,DWR,DAR,DPRG,-1,-1,DAMON,DGRP,DAY};
extern char huge point_cod[MAX_TBL_BANK][5];
extern Str_netstat_point *netstatbuf;

int lat_char_n;
int lung_char_n;
int font_type=DEFAULT_FONT;
int charsize=1;

int modify_child;
char display_amons;
extern char monitor_accessed, save_prg_flag;
//static GWindow huge *D;

extern char check_annual_routine_flag;
extern char check_weekly_routine_flag;
//char refresh_table[24];
extern int refresh;
extern Point_Net amon_inputs[MAX_POINTS_IN_MONITOR];
extern int max_entry;
extern char save_monitor;
extern char save_monitor_command, save_monitor_status;
extern char modify_monitor;
extern int max_entry_array;
extern byte serial_access;
extern char GAlarm, gAlarm;

Dial_list_point dial_list_data;

void *GGrid::operator new(size_t size)
{
 return (newalloc(size));
}
void GGrid::operator delete(void *ptr)
{
 newdelete(ptr);
}

RecordStruct::~RecordStruct()
	 {
		mfarfree( Recstruct_handle );
	 };

void RecordStruct::RecStruct(int nfields, struct FieldStruct huge *recstruct)
		 {
			mfarmalloc((char far **)&Recstruct , (sizeof(struct FieldStruct))*nfields, Recstruct_handle);
			if (Recstruct == NULL)
//			if ((Recstruct =  (struct FieldStruct *)farmalloc((sizeof(struct FieldStruct))*nfields)) == NULL)
			{
			 printf("FXENGINE Not enough memory to allocate RecStruct in class RecordStruct\n");
			 exit(2);  // terminate program if out of memory
			}
			 memcpy(Recstruct, recstruct, nfields*32);
		 };

void HHeader::HSet(int nfields,struct FieldStruct *recstruct, int nrecords)
{
 struct date d;
 set_semaphore_dos();
 getdate(&d);
 clear_semaphore_dos();
 header.id = 0x03;
 header.d.da_year = d.da_year % 100;
 header.d.da_mon = d.da_day ;
 header.d.da_day = d.da_mon ;

 header.n_records = nrecords ;

 header.header_size = 32 + nfields*32 + 1 ;

 header.record_size = 0 ;

 int n=1;
 for(int i=0; i<nfields ; i++)
	 {
		header.record_size += recstruct[i].l ;
		recstruct[i].position = n;
		n += recstruct[i].l;
	 };
 header.record_size++;
};

extern void  getkey(void);

extern unsigned char tbl_bank[MAX_TBL_BANK];
extern Pshape ARROW;
extern void dealloc_mem( char far **under1, char far **under2, char far **under3, char far **under4, int *flag);
extern void alloc_mem(int sx, int sy, int jx, int jy, char far **under1, char far **under2, char far **under3, char far **under4, int *flag);
extern void put_image(int sx, int sy, int jx, int jy, char far **under1, char far **under2, char far **under3, char far **under4, int *flag);
extern void initanalogmon(void);

void scrollup(int topx, int topy, int endx, int endy, char attr);


/********Functii auxiliare**************************/

char *rtrim(char *text);

/********Constructor***************/

GGrid::GGrid( int lx, int ly, int rx, int ry, int stk, char *fname,
					byte Point_type, byte Panel_type, byte Panel, int Network,
					signed char Type, byte Point_num, int f_type, int csize, char dprint)
					:GWDialog(lx,ly,rx,ry,0,1,f_type,csize,dprint)
{
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.008  ********
// ********       begin       ********
// ***********************************
 Flag_help=IMPOTENT;
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.008  ********
// ********        end        ********
// ***********************************
 GGInit( lx, ly, rx, ry, stk, fname, Point_type, Panel_type, Panel, Network,
				 Type, Point_num);
};

// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.009  ********
// ********       begin       ********
// ***********************************
GGrid::GGrid(int flag_help,char *need_help, int lx, int ly, int rx, int ry, int stk, char *fname,
					byte Point_type, byte Panel_type, byte Panel, int Network,
					signed char Type, byte Point_num, int f_type, int csize, char dprint)
					:GWDialog(lx,ly,rx,ry,0,1,f_type,csize,dprint)
{
 Flag_help=flag_help;
 GGInit( lx, ly, rx, ry, stk, fname, Point_type, Panel_type, Panel, Network,
				 Type, Point_num);
};
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.009  ********
// ********        end        ********
// ***********************************

/********Constructor***************/

GGrid::GGrid( int lx, int ly, int rx, int ry, char far *ptitle,
				 uint bkgclr, uint title_bkgclr, uint border_frgclr, int stk, char *fname,
				 byte Point_type, byte Panel_type, byte Panel, int Network,
				 signed char Type, byte Point_num, int f_type, int csize, char dprint)
				 :GWDialog(lx,ly,rx,ry,0,1,f_type,csize,dprint)
{
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.010  ********
// ********       begin       ********
// ***********************************
	Flag_help=IMPOTENT;
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.010  ********
// ********        end        ********
// ***********************************
	GGInit( lx, ly, rx, ry, stk, fname, Point_type, Panel_type, Panel, Network,
				  Type, Point_num);
	GWSet(ptitle, bkgclr, title_bkgclr, border_frgclr);
};
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.011  ********
// ********       begin       ********
// ***********************************
GGrid::GGrid( int flag_help,char *need_help,int lx, int ly, int rx, int ry, char far *ptitle,
				 uint bkgclr, uint title_bkgclr, uint border_frgclr, int stk, char *fname,
				 byte Point_type, byte Panel_type, byte Panel, int Network,
				 signed char Type, byte Point_num, int f_type, int csize, char dprint)
				 :GWDialog(lx,ly,rx,ry,0,1,f_type,csize,dprint)
{
	Flag_help=flag_help;
	GGInit( lx, ly, rx, ry, stk, fname, Point_type, Panel_type, Panel, Network,
				  Type, Point_num);
	GWSet(ptitle, bkgclr, title_bkgclr, border_frgclr);
};
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.011  ********
// ********        end        ********
// ***********************************

/*************************************/

void GGrid::GGInit( int lx, int ly, int rx, int ry, int stk, char *fname,
					byte Point_type, byte Panel_type, byte Panel, int Network,
					signed char Type, byte Point_num)
{
 asm push es;
 grid = stk;
 header_bkgcolour = Cyan;
 fh=0;
 obj.out=NULL;
 Gpanel      = Panel;
 Gnetwork    = Network;
 Gpanel_type = Panel_type;
 Gtype       = Type;
 Gpoint_num  = Point_num;
 Glocal      = 0;
 if( local_request(Gpanel, Network) )
		 Glocal = 1;
 bank=0;
 modify=FALSE;
 max_points_bank = 0;
 index_max_bank=0;
 grid_error = 0;
 if (fname)
 {
	movedata( FP_SEG(fname), FP_OFF(fname),FP_SEG(filename), FP_OFF(filename), strlen(fname)+1 );
//	strcpy(filename,fname);
	if ((grid_error=FXOpen(filename,&fh,READWRITE))==FX_OPEN_ERROR)
		 return;
	FXGetRecStruct(fh,&recstruct);
	FXNRecs(fh,&NRec );
//	FXFileInfo(fh, &fileinfo);
	FXNFields(fh,&fields_number);
 }
 else
 {
	 filename[0]=0;
	 descriptor=YES;
	 point_type = Point_type;
	 create_obj();
 }
 w_lfield = 1;
 w_urecord = 1;
 w_record = 1;
 w_field = 1;
 memset(refresh_table, 0, 24);
 modify_child=0;
 asm pop es;
};

void GGrid::create_obj(void)
{
 uint r=0;
 asm push es;
	 if(Gtype==INDIVIDUAL)
		{
		 max_points_bank = 1;
//		 max_bank = 0;
		}
	 else
		{
		 if(point_type < MAX_TBL_BANK)
			 max_points_bank = tbl_bank[point_type];
		 else
		    max_points_bank = 1;
//		 max_bank = tbl_bank[point_type][0];
		}
	 max_bank = 0;
	 switch (point_type) {
		case OUT:
						 title_status=1;
						 obj.out = new Output_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)obj.out->block;
#ifdef NETWORK_COMM
						 operator_list.buffer = ptr_block;
						 operator_list.length = index_max_bank*sizeof(Str_out_point);
#endif
						 break;
		case IN:
						 title_status=1;
						 obj.in = new Input_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)obj.in->block;
#ifdef NETWORK_COMM
						 operator_list.buffer=ptr_block;
						 operator_list.length = index_max_bank*sizeof(Str_in_point);
#endif
						 break;
		case VAR:
						 title_status=1;
						 obj.var = new Var_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)obj.var->block;
#ifdef NETWORK_COMM
						 operator_list.buffer=ptr_block;
						 operator_list.length = index_max_bank*sizeof(Str_variable_point);
#endif
						 break;
		case CON:
						 title_status=1;
						 obj.con = new Controller_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)obj.con->block;
#ifdef NETWORK_COMM
						 operator_list.buffer=ptr_block;
						 operator_list.length = index_max_bank*sizeof(Str_controller_point);
#endif
						 break;
		case WR:
						 title_status=1;
						 obj.wr = new Weekly_routine_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)obj.wr->block;
#ifdef NETWORK_COMM
						 operator_list.buffer=ptr_block;
						 operator_list.length = index_max_bank*sizeof(Str_weekly_routine_point);
#endif
						 break;

		case WR_TIME:
						 title_status=1;
						 max_bank = 0;
						 max_points_bank = 8;
						 obj.wr_time = new Weekly_routine_time_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 descriptor=NO;
						 ptr_block = (char *)obj.wr_time->block;
#ifdef NETWORK_COMM
						 operator_list.buffer=ptr_block;
						 operator_list.length = index_max_bank*sizeof(Wr_one_day);
#endif
						 break;
		case AR:
						 title_status=1;
						 obj.ar = new Annual_routine_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)obj.ar->block;
#ifdef NETWORK_COMM
						 operator_list.buffer=ptr_block;
						 operator_list.length = index_max_bank*sizeof(Str_annual_routine_point);
#endif
						 break;
		case AR_Y:
						 title_status=1;
						 max_bank = 0;
						 max_points_bank = 7;
						 obj.ar_y = new Annual_routine_time_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 descriptor=NO;
						 ptr_block = (char *)obj.ar_y->block;
#ifdef NETWORK_COMM
						 operator_list.buffer=ptr_block;
#endif
						 break;
		case PRG:
						 obj.prg = new Program_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)obj.prg->block;
#ifdef NETWORK_COMM
						 operator_list.buffer=ptr_block;
						 operator_list.length = index_max_bank*sizeof(Str_program_point);
#endif
						 break;
		case GRP:
						 title_status=1;
						 obj.grp = new Control_group_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)obj.grp->block;
#ifdef NETWORK_COMM
						 operator_list.buffer=ptr_block;
						 operator_list.length = index_max_bank*sizeof(Control_group_point);
#endif
						 break;
		case GRAPHIC_GRP:
						 max_bank = 0;
						 max_points_bank = MAX_ELEM;
						 obj.ggrp = new Control_graphic_group_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)obj.ggrp->block;
#ifdef NETWORK_COMM
						 operator_list.buffer=ptr_block;
#endif
//						 operator_list.length = index_max_bank*sizeof(Control_graphic_group_point);
						 break;
		case USER_NAME:
//						 max_bank = 0;
//						 max_points_bank = MAX_PASSW;
						 obj.user_name = new Password_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)obj.user_name->block;
//						 ptr_block = (char *)&passwords;
						 break;
		case CSTATION:
		case STATION:
						 max_bank = 0;
						 max_points_bank = MAX_STATIONS;
//						 obj.st = new Station_block(this, Gpanel_type,Gpanel,Gsub_panel,Gnet_type,bank);
						 if(point_type==CSTATION)
							 obj.st = new Station_block(this,Gpanel_type,Gpanel,Gnetwork,CSTATION,Gpoint_num);
						 else
							 obj.st = new Station_block(this,Gpanel_type,Gpanel,Gnetwork,STATION,Gpoint_num);
						 ptr_block = (char *)&station_list;
						 break;
		case NETSTATUS:
						 max_bank = 0;
						 max_points_bank = MAX_STATIONS;
						 obj.ns = new Netstatus_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)obj.ns->block;
						 break;
		case NETSTAT:
						 max_bank = 0;
						 max_points_bank = MAX_NETSTATS;
						 obj.netstat = new Netstat_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)netstatbuf;
						 break;
		case MONSETUP:
						 break;
		case ALARMM:
						 title_status=1;
						 max_points_bank = MAX_ALARMS;
						 max_bank = 0;
						 obj.alarmm = new Alarm_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)obj.alarmm->block;
#ifdef NETWORK_COMM
						 operator_list.buffer=ptr_block;
						 operator_list.length = index_max_bank*sizeof(Alarm_point);
#endif
						 break;
		case ALARMS:
						 title_status=1;
						 max_points_bank = MAX_ALARMS_SET;
						 max_bank = 0;
						 obj.alarms = new Alarm_set_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)obj.alarms->block;
#ifdef NETWORK_COMM
						 operator_list.buffer=ptr_block;
						 operator_list.length = index_max_bank*sizeof(Alarm_set_point);
#endif
						 break;
		case TBL:
						 title_status=1;
						 max_points_bank = 16;
						 max_bank = 0;
						 obj.tbl = new Tbl_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)obj.tbl->block;
/*
#ifdef NETWORK_COMM
						 operator_list.buffer=ptr_block;
						 operator_list.length = index_max_bank*5*sizeof(Tbl_point) ;
#endif
*/
						 break;
		case UNIT:
						 title_status=0;
//						 max_points_bank = MAX_UNITS;
//						 max_bank = 0;
						 obj.units = new Units_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)obj.units->block;
#ifdef NETWORK_COMM
						 operator_list.buffer=ptr_block;
						 operator_list.length = index_max_bank*sizeof(Units_element);
#endif
						 break;
		case AMON:
						 monitor_accessed=1;
						 modify_monitor = 0;
						 title_status=1;
						 obj.amon = new Monitor_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)obj.amon->block;
#ifdef NETWORK_COMM
						 operator_list.buffer=ptr_block;
						 operator_list.length = index_max_bank*sizeof(Str_analog_monitor_point);
#endif
						 break;
		case AMON_INPUTS:
						 title_status=1;
						 max_points_bank = 16;
						 max_bank = 0;
						 obj.amon_input = new Amon_inputs_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 break;
		case ARRAY1:
						 max_bank = 0;
						 max_points_bank = max_entry;
						 obj.array = new Array1_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 break;
		case CONNECT_COM:
						 max_bank = 0;
						 max_points_bank = 4;
						 obj.ccom = new Connect_com_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 break;
		case NET_SEL:
						 max_bank = 0;
						 max_points_bank = 32;
						 obj.net = new Net_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 break;
		case AY:
						 title_status=0;
						 obj.ay = new Array_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)obj.ay->block;
#ifdef NETWORK_COMM
						 operator_list.buffer=ptr_block;
						 operator_list.length = index_max_bank*sizeof(Str_array_point);
#endif
						 break;
		case AYVALUE:
						 title_status=0;
						 max_points_bank = max_entry_array;
						 max_bank = 0;
						 obj.ayvalue = new Ayvalue_block(this,Gpanel_type,Gpanel,Gnetwork,Gtype,Gpoint_num);
						 ptr_block = (char *)obj.ayvalue->block;
#ifdef NETWORK_COMM
						 operator_list.buffer=ptr_block;
						 operator_list.length = index_max_bank*sizeof(Str_ayvalue_point);
#endif
						 break;
	 }
	 NRec = obj.out->NRec();
	 fields_number = obj.out->NFields();
	 index_max_bank=max_points_bank;   // !!!!! il primesc de la doru
	 obj.out->FirstRec();

//	 if( !local_panel && point_type != CSTATION && point_type!=STATION && point_type!=USER_NAME && point_type != AMON_INPUTS && point_type != ARRAY1 && !arights_grid)
//	if( (!local_panel && Gpanel==station_num) || Gpanel!=Station_NUM )
	if( !Glocal )
	 if( point_type!=NETSTATUS && point_type!=NETSTAT && point_type != AMON_INPUTS && point_type != ARRAY1 && point_type != GRAPHIC_GRP
			&& point_type != CONNECT_COM && point_type != NET_SEL && !arights_grid )
	 {
		 GWindow D(mode_text?25:200, mode_text?7:150, mode_text?55:500, mode_text?11:200, NO_STACK,0);
//		DisplayMessage(mode_text?25:200, mode_text?7:150, mode_text?55:500, mode_text?11:200, ctrlbreak_text, " Reading data...   ", NULL, Black, &D);
		 DisplayMessageT(25, 7, 55, 11, ctrlbreak_text, " Reading data...   ", NULL, Black, &D);

		 RS232Error res;
		 unsigned b = 0,t = point_type+1;
		 if(Gtype==INDIVIDUAL)
		 {
//			 b=((Gpanel-1)<<11) + ((point_type+1)<<7)+ Gnet_type-1;
			 b=((point_type+1)<<8)+ Gpoint_num-1;
			 t=20;
		 }
		 if(point_type == AR_Y || point_type == WR_TIME || point_type == AYVALUE)
		 {
			t = point_type + 1;
			if(point_type == AR_Y)
			 b = obj.ar_y->routine_num-1;
			if(point_type == WR_TIME)
			 b = obj.wr_time->routine_num-1;
			if(point_type == AYVALUE)
			 b = obj.ayvalue->current_array;
		 }
		 if( point_type == CSTATION || point_type==STATION )
		 {
			t = 50; b = 21;
		 }
		 if( point_type != CSTATION && point_type!=STATION)
		 {
			r = countlength(t, b);
		  grid_error = net_call(t, b, (char *)ptr_block, &r, Gpanel, Gnetwork, NETCALL_RETRY|NETCALL_SIGN, TIMEOUT_NETCALL);
		 }
		 D.GReleaseWindow();
	}

	if (point_type==ALARMM) obj.alarmm->sortalarm();
	if (point_type==AMON && !grid_error) initamoninputsscreen();
 asm pop es;
}

void GGrid::GRead(int type)
{
	 char *ptr_obj;
	 int npoint;
	 switch (point_type) {
		case OUT:
		case IN:
		case VAR:
		case CON:
		case WR:
		case AR:
		case PRG:
		case GRP:
		case AMON:
		case TBL:
		case AY:
		case UNIT:
						 npoint=0;
						 if(Gtype==INDIVIDUAL)
								npoint =  Gpoint_num-1;                // num_point
//						 if(local_panel && !arights_grid)
						 if(Glocal && !arights_grid)
								memmove(ptr_block, ptr_panel->info[point_type].address + npoint*ptr_panel->info[point_type].str_size,index_max_bank*ptr_panel->info[point_type].str_size);
						 else
						 {
//						 if((local_panel && Gsub_panel!=INDIVIDUAL) || (!local_panel && Gsub_panel==INDIVIDUAL))
//								memmove(obj.out->block,ptr_panel->outputs,index_max_bank*sizeof(Str_out_point));
#ifdef NETWORK_COMM
							operator_list.buffer=ptr_block;
							operator_list.length = index_max_bank*ptr_panel->info[point_type].str_size;
#endif
						 }
						 break;
		case USER_NAME:
//						 if(local_panel && !arights_grid)
						 if(Glocal && !arights_grid)
								memmove(ptr_block, ptr_panel->info[point_type].address,2+index_max_bank*ptr_panel->info[point_type].str_size);
						 else
						 {
						 }
						 break;
		case WR_TIME:
						 if( serial_access )
						 {
							ptr_obj = (char *)obj.wr_time;
						 }
#ifdef NETWORK_COMM
						 else
						 {
						 operator_list.buffer=(char *)obj.wr_time->block;
//						 operator_list.length = index_max_bank*sizeof(Str_weekly_routine_time_point);
						 }
#endif
						 break;
		case AR_Y:
						 if( serial_access )
						 {
//							obj.ar_y->panel_type = T3000;
							ptr_obj = (char *)obj.ar_y;
						 }
#ifdef NETWORK_COMM
						 else
						 {
						 operator_list.buffer=(char *)obj.ar_y->block;
						 }
#endif
						 break;
		case GRAPHIC_GRP:
						 if( serial_access )
						 {
//							obj.ggrp->panel_type = T3000;
							ptr_obj = (char *)obj.ggrp;
						 }
#ifdef NETWORK_COMM
						 else
						 {
						 operator_list.buffer=(char *)obj.ggrp->block;
//						 operator_list.length = index_max_bank*sizeof(Control_graphic_group_point);
						 }
#endif
						 break;
		case AMON_INPUTS:
						 memmove(obj.amon_input->block,amon_inputs,index_max_bank*sizeof(Point_Net));
						 return;
		case MONSETUP:
						 break;
		case ALARMS:
//						 if((local_panel && Gtype!=INDIVIDUAL) || (Gtype==INDIVIDUAL && Gpanel==Station_NUM && Gnetwork==NetworkAddress))
						 if( Glocal )
								memmove(obj.alarms->block,ptr_panel->alarms_set,index_max_bank*sizeof(Alarm_set_point));
						 else
						 if( serial_access )
						 {
//							obj.alarms->panel_type = T3000;
							ptr_obj = (char *)obj.alarms;
						 }
#ifdef NETWORK_COMM
						 else
						 {
						 operator_list.buffer=(char *)obj.alarms->block;
						 operator_list.length = index_max_bank*sizeof(Alarm_set_point);
						 }
#endif
						 break;
		case ALARMM:
						 break;
		case CSTATION:
		case STATION:
    case NETSTAT:
    case NETSTATUS:
						 break;
		case ARRAY1:
						 break;
		case CONNECT_COM:
		case NET_SEL:
						 break;
		case AYVALUE:
//						 if((local_panel && Gtype!=INDIVIDUAL) || (Gtype==INDIVIDUAL && Gpanel==Station_NUM && Gnetwork==NetworkAddress))
						 if( Glocal )
								memmove(obj.ayvalue->block,ptr_panel->arrays_data[obj.ayvalue->current_array],index_max_bank*sizeof(Str_ayvalue_point));
#ifdef NETWORK_COMM
						 operator_list.buffer=(char *)obj.ayvalue->block;
						 operator_list.length = index_max_bank*sizeof(Str_ayvalue_point);
#endif
						 break;
	 }

// if( !local_panel && point_type != CSTATION && point_type!=STATION && point_type!=USER_NAME && point_type != AMON_INPUTS && point_type != ARRAY1 && !arights_grid)
//	if( (!local_panel && Gpanel==station_num) || Gpanel!=Station_NUM )
	if(!Glocal)
	if( point_type!=NETSTATUS && point_type!=NETSTAT && point_type != CSTATION && point_type!=STATION && point_type != AMON_INPUTS && point_type != ARRAY1 && point_type != GRAPHIC_GRP
		 && point_type != CONNECT_COM && point_type != NET_SEL && !arights_grid)
//	if( serial_access )
	{
	 RS232Error res;
	 unsigned b = 0,t = point_type+1;
	 int i=0,j=0;
	 if(Gtype==INDIVIDUAL)
	 {
			 b=((point_type+1)<<8)+ Gpoint_num-1;
			 t=20;
	 }
	 else
	 {
	  if(type == SMALLBANK)
	  {
		if( (i = w_urecord - 1 - 4) < 0 ) i = 0;
		if( (j = w_drecord - 1 + 4) >= NRec) j = NRec-1;

		b = ((128 + j - i + 1) << 8) + i;
	  }
	  else
		b=((point_type+1)<<8)+ Gpoint_num-1;
    }

	 if(point_type == AR_Y || point_type == WR_TIME)
	 {
			t = point_type + 1;
			if(point_type == AR_Y)
			 b = obj.ar_y->routine_num-1;
			if(point_type == WR_TIME)
			 b = obj.wr_time->routine_num-1;
			if(point_type == AYVALUE)
			 b = obj.ayvalue->current_array;
	 }
	 npoint = countlength(t, b);
	 res = net_call(t, b, ptr_block+i*ptr_panel->info[point_type].str_size, (uint *)&npoint, Gpanel, Gnetwork, NETCALL_RETRY, TIMEOUT_NETCALL);
	}
/*
	else
	{
		GReadNet(0);
	}
*/
}

/*
void GGrid::GReadNet(int com)
{
#ifdef NETWORK_COMM
 if(point_type != CSTATION && point_type!=STATION && point_type!=USER_NAME && point_type != AMON_INPUTS
		&& point_type != ARRAY1	&& !arights_grid)
 {
///////////////
	 if(!local_panel || (Gtype==INDIVIDUAL && Gpanel!=Station_NUM))
		if( Netbios_state == NB_INSTALLED )
				{
				 if(Gtype==INDIVIDUAL)
					{
					 memcpy( operator_list.name, station_list[Gpanel-1].hard_name, 16 );
					 operator_list.command[0]=Gpanel;
					}
				 else
					{
					 memcpy( operator_list.name, station_list[station_num-1].hard_name, 16 );
					 operator_list.command[0]=station_num;
					}
				 operator_list.command[1]=0;
				 operator_list.command[2]=point_type+1+com;
				 uint arg;
				 if(Gtype==INDIVIDUAL)
					{
					 arg=((Gpanel-1)<<11)+ ((point_type+1)<<7)+ Gnet_type-1;
					 operator_list.command[2]=20+com;
					}
				 else
					arg	= bank;
				 memcpy( (3+operator_list.command),(char *)&arg,2);
				 operator_list.command[5]=0;

//				 operator_list.buffer=(char *)obj.out->block;

				 operator_list.state = REQUEST;
				 resume(NETWORK);
				 task_switch();

				 while(operator_list.state!=DONE && operator_list.state!=ERROR);
//				 suspend(NETWORK);
				 if(operator_list.state==ERROR)
							{
								FClose(fh,obj);
								error_net=1;
								return ;
							}
				}
///////////////
	}
#endif
}
*/

GGrid::~GGrid( )
{
	if (fh)
//		FClose(fh,obj);
	;
	else
	 switch (point_type) {
		case WR_TIME:
						 delete obj.wr_time;
						 break;
		case AR_Y:
						 delete obj.ar_y;
						 break;
		case GRAPHIC_GRP:
						 delete obj.ggrp;
						 break;
		case WR:
						 delete obj.wr;
						 break;
		case AR:
						 delete obj.ar;
						 break;
		case AY:
						 delete obj.ay;
						 break;
		case TBL:
						 delete obj.tbl;
						 break;
		case NET_SEL:
						 delete obj.net;
						 break;
		case CSTATION:
						 delete obj.st;
						 break;
		case NETSTAT:
						 delete obj.netstat;
						 break;
		case NETSTATUS:
						 delete obj.ns;
						 break;
		default:
						 if(obj.out) delete obj.out;
						 break;
//		case IN:
//						 delete(obj.in);
//						 break;
	 }
}

/********************************************/

int GGrid::GWx(int col)
{
 int lat;

 if(mode_text)
	 lat  = 1;
 else
	 lat  = textwidth(" ");
	 if(mode_text)
			return(tx+(col-1)*lat);
	 else
			return(tx+COL_SPACE+col*lat);
};

/********************************************/

int GGrid::GWy(int row)
{
 int lung;

 if(mode_text)
	 lung = 1;
 else
	 lung = textheight("H")+LINE_SPACE;
	 if(mode_text)
			return(ty+(row-1)*lung);
	 else
			return(ty+3+row*(LINE_SPACE+lung));
};

/***********************************/
void GGrid::GWGoto(int row, int col)
{
// if(mode_text)
// {
// lat  = 1;
// lung = 1;
// }
// else
// {
// lat  = textwidth(" ");
// lung = textheight("H")+LINE_SPACE;
// }
 if((row<=nrows)&&(col<=ncols))
	 if(mode_text)
			mgotoxy(tx+(col-1)*lat_char_n,ty+(row-1)*lung_char_n);
	 else
//		moveto(tx+COL_SPACE+col*lat,ty+3+row*(LINE_SPACE+lung));
//			if(row)
				moveto(tx+COL_SPACE+col*lat_char_n,ty+3+row*(LINE_SPACE+(lung_char_n+LINE_SPACE)));
//				moveto(tx+(col-1)*lat,ty+(row-1)*(LINE_SPACE+lung));
//			else
//				moveto(tx+(col-1)*lat,ty+4+(row-1)*(LINE_SPACE+lung));
};

/**********************************/
//start printrecord
int GGrid::GPrintRecord(int w_frecord)
{
	int ii,kk,l1,length,t,jj;
	char buf[MAX_ALPHA+1],buf_temp[MAX_ALPHA+1];
	char string[2],string1[2],temp[4];
	buf_temp[0]='\0';
	string[0]='\n';string[1]='\0';
	string1[0]=' ';string1[1]='\0';
	ii=1;   length=0;
	FGotoRec(fh,obj,w_frecord);
	l1=0;
	if (FGetRec(fh,obj)==FX_EOF)	return 0;

// get number of line and store into buf_temp if blank go next
// else write to FILE
	FGetAlpha(fh,obj,ii,MAX_ALPHA,buf);
	jj=0;

	if( point_type!=WR_TIME && point_type!=AR_Y )
	{
		t=min(atoi(buf),line_count);
		if(t>9)
		{
			strcat(buf_temp,string1);
			strcat(buf_temp,itoa(t,temp,10));
		}
		else
		{
			strcat(buf_temp,string1);
			strcat(buf_temp,string1);
			strcat(buf_temp,itoa(t,temp,10));
		}
	}
	else
	{
		while( jj<=strlen(buf)){buf_temp[jj]=buf[jj];jj++;}
		buf_temp[jj]=string[1];
		if(strlen(buf)==2){	strcat(buf_temp,string1); }
	}

	FGetAlpha(fh,obj,ii+1,MAX_ALPHA,buf);
	jj=0;kk=0;

	while( kk <= strlen( buf )){ if( buf[kk++] == ' ' ) jj++; }
											// count blank space
	if(	jj == strlen( buf ) && point_type != AR_Y ){ return 0; }
											// if field blank then return
	else
	{
		fwrite(buf_temp,strlen(buf_temp),1,pf);
		fwrite("|",1,1,pf);
		fwrite(buf,strlen(buf),1,pf);
		fwrite("|",1,1,pf);
	}	//else write num and field label to file

	for(ii=w_lfield+2;ii<=w_rfield+1;ii++)
	{
		FGetAlpha(fh,obj,ii,MAX_ALPHA,buf);
		if(point_type==ALARMM && ii==4)
		{
			for(register aa=0;aa<strlen(buf);aa++)
			{
				if(buf[aa]=='\n'){buf[aa]=' ';}
				continue;
			}
		}

		if(field_wide[ii]!=-1 && point_type!=AR_Y)
		{
			length=field_wide[ii-1]-strlen(buf);
			for(kk=0;kk<length;kk++){ strcat(buf," "); }
			fwrite(buf,strlen(buf),1,pf);
			fwrite("|",1,1,pf);
		}
		else if(point_type==AR_Y)
		{
			fwrite(buf,strlen(buf),1,pf);
			fwrite("|",1,1,pf);
		}

	}
	fwrite(string,strlen(string),1,pf);
	return 1;
}
// end of printrecord
/**********************************/
void GGrid::GGPutRecord(int w_frecord, int bkgnd, int frgnd)
{
char buf[MAX_ALPHA+1];
//if(mode_text)
//{
// mtextbackground(colour);
// mtextcolor(Black);
//}
FGotoRec(fh,obj,w_frecord);
fground = -1;
if (FGetRec(fh,obj)==FX_EOF)
	return;
//hide_pointer();
//for(int i=w_lfield+w_field-1;i<=w_rfield;i++)
for(int i=w_lfield;i<=w_rfield;i++)
{
FGetAlpha(fh,obj,i,MAX_ALPHA,buf);
if(point_type == AMON_INPUTS && w_record>obj.amon_input->anum_inputs )
 frgnd = White;
GWPuts(w_record,t_fields[i-1],buf,bkgnd,(fground==-1?frgnd:fground));
int l=t_fields[i-1]+max(strlen(rtrim(FFldName(fh, obj, i))),FFldSize(fh, obj, i));
//GWGoto(w_record,l);
if(mode_text)
 if(l!=bx-tx+2)
	 moutchar(tx+(l-1),ty+(w_record-1),'³',bkgcolour,Black);
}
//display_pointer();
}

void GGrid::GGPutField(int field,int bkgnd, int frgnd)
{
char buf[MAX_ALPHA+1];
if (field>=w_lfield && field<=w_rfield)
 {
	FGetAlpha(fh,obj,field,MAX_ALPHA,buf);
	GWPuts(w_record,t_fields[field-1],buf,bkgnd,frgnd);
 }
}

void GGrid::GGHideCur(int col)
{
 int lx;
 char buf[MAX_ALPHA+1];         //max width field
 hide_pointer();
// if(mode_text)
// {
// lung=1;
// lat=1;
// textattr(attribute);
// }
// else
// {
//	settextstyle(2, 0, 0);
//	lung=textheight("H")+LINE_SPACE;
//	lat=textwidth(" ");
//	c=getcolor();
// }

 if (w_field==1)
		lx=tx;
 else
		lx=tx+(t_fields[w_field+w_lfield-1-1]-1)*lat_char_n + (mode_text ? 0 : 4);
// GWPuts(ty+(w_record-1)*lung,lx,rtrim((char *)recstruct[i].field_name));
 if(mode_text)
 {
 FGotoRec(fh,obj,w_urecord+w_record-1);
 if (FGetRec(fh,obj)==FX_EOF)
		return;
// FGetAlpha(fh,obj,w_lfield+w_field-1,MAX_ALPHA,buf);
// GWPuts(w_record,t_fields[w_lfield+w_field-1-1],buf);
// mtextcolor(Black);
// mtextbackground(colour);
 if(point_type==AR_Y)
 {
	textattr(attribute);
	FGetAlpha(fh,obj,w_lfield+w_field-1,MAX_ALPHA,buf);
	GWPuts(w_record,t_fields[w_lfield+w_field-1-1],buf,(unsigned int)attribute/16,Black);
//	mtextcolor(Black);
//	mtextbackground(colour);
 }
 else
	 GGPutRecord(w_urecord+w_record-1,bkgcolour,Black);
 }
 else
 {
/* setlinestyle(SOLID_LINE, 0xffff, 1);
 setcolor(Lightgray);
 prectangle(lx,ty+(w_record)*(LINE_SPACE+lung),tx+(t_fields[w_field+w_lfield-1]-1)*lat+4,ty+(w_record+1)*(LINE_SPACE+lung),Lightgray);

 setlinestyle(DOTTED_LINE, 0xffff, 1);
 setcolor(col);
 prectangle(lx,ty+(w_record)*(LINE_SPACE+lung),tx+(t_fields[w_field+w_lfield-1]-1)*lat+4,ty+(w_record+1)*(LINE_SPACE+lung),col);
 setcolor(c);
*/
// line_style=DOTTED;
 prectangle(lx,ty+(w_record)*(LINE_SPACE+(lung_char_n+LINE_SPACE)),tx+(t_fields[w_field+w_lfield-1]-1)*lat_char_n+4,ty+(w_record+1)*(LINE_SPACE+(lung_char_n+LINE_SPACE)),col);
 line_style=FILL;
// settextstyle(DEFAULT_FONT, HORIZ_DIR,1);
 }
 display_pointer();
}


void GGrid::GGShowCur(int col)
{
 int lx;
 char buf[MAX_ALPHA+1];         //max width field
 hide_pointer();
 if (w_field==1)
		lx=tx;
 else
		lx=tx+(t_fields[w_field+w_lfield-1-1]-1)*lat_char_n + (mode_text ? 0 : 4);
// GWPuts(ty+(w_record-1)*lung,lx,rtrim((char *)recstruct[i].field_name));
 FGotoRec(fh,obj,w_urecord+w_record-1);
 if (FGetRec(fh,obj)==FX_EOF)
		return;
 FGetAlpha(fh,obj,w_lfield+w_field-1,MAX_ALPHA,buf);
 if(mode_text)
 {
	GWGoto(w_record,t_fields[w_lfield+w_field-1-1]);
	asm {
		mov ah,08
		mov bh,0
		int 10h
		}
	attribute=_AH;

	if(point_type!=AR_Y)
	 GGPutRecord(w_urecord+w_record-1,bkgcolour,Blue);

	GWPuts(w_record,t_fields[w_lfield+w_field-1-1],buf,col,bkgcolour);
 }
 else
 {
  prectangle(lx,ty+(w_record)*(LINE_SPACE+(lung_char_n+LINE_SPACE)),tx+(t_fields[w_field+w_lfield-1]-1)*lat_char_n+4,ty+(w_record+1)*(LINE_SPACE+(lung_char_n+LINE_SPACE)),White);
// setcolor(c);
// settextstyle(DEFAULT_FONT, HORIZ_DIR,1);
 }
 display_pointer();
}

/*int savedes()
{
 FILE *h;
 char fname[64],xbuf[30],xbuf1[10];
 unsigned int n,l,pos,poscur,posrest;
 unsigned long length;
 int x,k;
 if ((h=fopen("des.des","wb+"))==NULL)
		 {
		 printf("Error open save descriptor file");
		 exit(0);
		 }
 memcpy(&length,&des[0],4);
 n=fwrite(des,length,1,h);
 fclose(h);
}
*/
/*
int loaddes()
{
 FILE *h;
 char fname[64],xbuf[30],xbuf1[10];
 unsigned int n,l,pos,poscur,posrest;
 unsigned long length;
 int x,k;

 if ((h=fopen("des.des","rb+"))==NULL)
		 {
		 printf("Error open load descriptor file");
		 exit(0);
		 }
 fread(des,4,1,h);
 mmemcpy(&length,&des[0],4);
 fclose(h);
 if ((h=fopen("des.des","rb+"))==NULL)
		 {
		 printf("Error open load descriptor file");
		 exit(0);
		 }
 fread(des,length+4,1,h);
 fclose(h);
}
*/
/*
int GGrid::readdes()
{
 FILE *h;
 char fname[64],xbuf[30];
 unsigned long n,l,lpanel,pos,pospanel,poscur,posrest,length,lposcur;
 int x,k;
// if ((h=fopen("d:\\des.des","rb+"))==NULL)
		 {
//		 printf("Error open descriptor file");
//		 exit(0);
		 }

// GWDialog *p=DisplayMessage("Loading...");

 mmemcpy(&l, &des[0], 4);
 length = l;
 pos = 4;
		for(int j=1; j<=Gpanel; j++)
		 {
			 if ((j==Gpanel) && (Gpanel_type==STANDARD || Gpanel_type==MINI_MAIN)) break;
			 mmemcpy(&l, &des[pos], 4);
			 pos += l+4;
			 if ((j==Gpanel) && (Gpanel_type==SUB_MINI) && (Gnet_type==SUBA)) break;
			 mmemcpy(&l, &des[pos], 4);
			 pos += l+4;
			 if ((j==Gpanel) && (Gpanel_type==SUB_MINI) && (Gnet_type==SUBB)) break;
			 mmemcpy(&l, &des[pos], 4);
			 pos += l+4;
		 }
//	 if (Gsub_panel == 0)
//		 {
			pospanel = pos;
			mmemcpy(&lpanel, &des[pos], 4);
			pos += 4;

			if (Gpanel_type==SUB_MINI)
			{
			 k=1;
//			 lnet=lpanel;
			 while (lpanel > pos-pospanel-4)
				 {
					mmemcpy(&l, &des[pos], 4);
					if (k==Gsub_panel)
						break;
					pos += l+4;
					k++;
				 }
			 if (k==Gsub_panel)
					{
//					 lnet -= lpanel;
//					 possubnet=pospanel;
//					 pospanel=pos;
					 pos += 4;
				 }
			}

			n = k = 0;
			while (point_type!=k && k<=AY)
							 { n++; k++; }
			for( k=0; k<n; k++)
			{
			 mmemcpy(&l, &des[pos], 2);
			 pos += l+2;
			}
			poscur = pos;
			lposcur=0;
			if (lpanel > poscur-(pospanel+4))
				mmemcpy(&lposcur,&des[pos],2);
			pos += 2;

			n=0;

			if (lposcur)
			{
				for(j=0;j<bank*max_points_bank;j++)
				{
				 x=des[pos++];
				 pos += x;
				 x=des[pos++];
				 pos += x;
				}
			}
			if(lposcur>pos-(poscur+2))
			{
			for(l=0;l<NRec;l++)        // pina la index_max_bank
			 {
				xbuf[0]=0;
				switch (point_type) {
					case OUT:
									 x=des[pos++];
									 mmemcpy(xbuf,&des[pos],x);
									 obj.out->PutField(OUT_FULL_LABEL,xbuf);   //full_label
									 pos += x;
									 x=des[pos++];
									 xbuf[0]=0;
									 mmemcpy(xbuf,&des[pos],x);
									 obj.out->PutField(OUT_LABEL,xbuf);   //label
									 pos += x;
									 obj.out->NextRec();
									 break;
					case IN:
									 x=des[pos++];
									 mmemcpy(xbuf,&des[pos],x);
									 obj.in->PutField(IN_FULL_LABEL,xbuf);   //full_label
									 pos += x;
									 x=des[pos++];
									 xbuf[0]=0;
									 mmemcpy(xbuf,&des[pos],x);
									 obj.in->PutField(IN_LABEL,xbuf);   //label
									 pos += x;
									 obj.in->NextRec();
									 break;
					case VAR:
									 x=des[pos++];
									 mmemcpy(xbuf,&des[pos],x);
									 obj.var->PutField(VAR_FULL_LABEL,xbuf);   //full_label
									 pos += x;
									 x=des[pos++];
									 xbuf[0]=0;
									 mmemcpy(xbuf,&des[pos],x);
									 obj.var->PutField(VAR_LABEL,xbuf);   //label
									 pos += x;
									 obj.var->NextRec();
									 break;

					}
			}
			}
//	DeleteMessage(p);
}
*/


/*
int GGrid::send()
{
 FILE *h;
 char fname[64],xbuf[30],xbuf1[30];
 unsigned long n,pos,poscur,posrest,lposcur,lpanel,pospanel, posbank, l, length;
 unsigned long possubnet,lnet;
	int x,k;
// if ((h=fopen("d:\\des.des","rb+"))==NULL)
		 {
//		 printf("Error open descriptor file");
//		 exit(0);
		 }

 mmemcpy(&l, &des[0], 4);
 length = l;
 pos = 4;
		for(int j=1; j<=Gpanel; j++)
		 {
			 if ((j==Gpanel) && (Gpanel_type==STANDARD || Gpanel_type==MINI_MAIN)) break;
			 mmemcpy(&l, &des[pos], 4);
			 pos += l+4;
			 if ((j==Gpanel) && (Gpanel_type==SUB_MINI) && (Gnet_type==SUBA)) break;
			 mmemcpy(&l, &des[pos], 4);
			 pos += l+4;
			 if ((j==Gpanel) && (Gpanel_type==SUB_MINI) && (Gnet_type==SUBB)) break;
			 mmemcpy(&l, &des[pos], 4);
			 pos += l+4;
		 }
//	 if (Gsub_panel == 0)
//		 {
			pospanel = pos;
			mmemcpy(&lpanel, &des[pos], 4);
			pos += 4;

			if (Gpanel_type==SUB_MINI)
			{
			 k=1;
			 lnet=lpanel;
			 while (lnet > pos-pospanel-4)
				 {
					mmemcpy(&lpanel, &des[pos], 4);
					if (k==Gsub_panel)
						break;
					pos += lpanel+4;
					k++;
				 }
			 if (k==Gsub_panel)
					lnet -= lpanel;
				possubnet=pospanel;
				pospanel=pos;
				pos += 4;
			}

			n = k = 0;
			if (lpanel)
			{
			while (point_type!=k && k<=AY)
							 { n++; k++; }
			for( k=0; k<n; k++)
			{
			 l=0;
			 mmemcpy(&l, &des[pos], 2);
			 pos += l+2;
			}
			poscur = pos;
			lposcur=0;
			if (lpanel > poscur-(pospanel+4))
				mmemcpy(&lposcur,&des[pos],2);
			}
			else
			 {
				poscur = pos;
				lposcur=0;
			 }
			pos += 2;

			if (lposcur)
				for(j=0;j<bank*max_points_bank;j++)        //atentie la VAR - max_points diferit de la bank la bank
				{
				 x=des[pos++];
				 pos += x;
				 x=des[pos++];
				 pos += x;
				}
			n=0;
			posbank=pos;
			if (lposcur>pos-poscur-2)
				for(j=0;j<max_points_bank;j++)
				{
				 x=des[pos++];
				 pos += x;
				 x=des[pos++];
				 pos += x;
				}

			if (lposcur)
			 {
				posrest = pos;       // + lposcur;
				lpanel -= lposcur+2;
			 }
			else
			 {
				posrest = pos - 2;
			 }

			lposcur = lposcur-(pos-posbank);
			pos = posbank;

//			if (lpanel==0)
//				{
//					memmove(&des[posrest+DAY*2],&des[posrest],length-posrest);
//					mmemset(&des[posrest],'\0',DAY*2);
//					length += DAY*2;
//					posrest += point_des[point_type]*2+2;
//					pos = posrest;
//					poscur = pos-2;
//					lpanel = DAY*2;
//				}

			memmove(&des[MAX_DES-(length-posrest+1)],&des[posrest],length-posrest);


			n=0;
			for(l=0;l<NRec;l++)
			 {
				for(int i=0;i<30;i++)
				{xbuf[i]=0;
				 xbuf1[i]=0;
				}
				switch (point_type) {
					case OUT:
									 obj.out->GotoRec(l+1);
									 obj.out->GetField(OUT_FULL_LABEL,xbuf);   //full_label
									 obj.out->GetField(OUT_LABEL,xbuf1);   //label
									 break;
					case IN:
									 obj.in->GotoRec(l+1);
									 obj.in->GetField(IN_FULL_LABEL,xbuf);   //full_label
									 obj.in->GetField(IN_LABEL,xbuf1);   //label
									 break;
					case VAR:
									 obj.var->GotoRec(l+1);
									 obj.var->GetField(VAR_FULL_LABEL,xbuf);   //full_label
									 obj.var->GetField(VAR_LABEL,xbuf1);   //label
									 break;

					}

			 x = mstrlen(rtrim(xbuf));
			 if (x)
					{x++; n += x+1;}
			 else n++;
			 des[pos++]=x;
			 mmemcpy(&des[pos],xbuf,x);
			 pos += x;
			 x = mstrlen(rtrim(xbuf1));
			 if (x)
					{x++; n += x+1;}
			 else n++;
			 des[pos++]=x;
			 mmemcpy(&des[pos],xbuf1,x);
			 pos += x;
			}
			lposcur += n;
			lpanel += lposcur+2;
			mmemcpy(&des[poscur],&lposcur,2);
//			if (lposcur)
//				lpanel -= (lposcur+2);
//			lpanel += n+2;
			mmemcpy(&des[pospanel],&lpanel,4);
			memmove(&des[pos],&des[MAX_DES-(length-posrest+1)],length-posrest);
			length=pos + length-posrest;
			mmemcpy(&des[0],&length,4);
			if (Gpanel_type==SUB_MINI)
			{
			 if(lnet==0)
				lnet += 4;
			 lnet += lpanel;
			 mmemcpy(&des[possubnet],&lnet,4);
			}
}
*/

int GGrid::FGetRec(FILEHANDLE fh, pointer_point_obj  obj)
{
 if (fh)
		 return(FXGetRec(fh));
 else
 switch (point_type) {
	 case OUT: return(obj.out->GetRec());
	 case IN: return(obj.in->GetRec());
	 case VAR: return(obj.var->GetRec());
	 case CON: return(obj.con->GetRec());
	 case WR: return(obj.wr->GetRec());
	 case WR_TIME: return(obj.wr_time->GetRec());
	 case AR: return(obj.ar->GetRec());
	 case AR_Y: return(obj.ar_y->GetRec());
	 case PRG: return(obj.prg->GetRec());
	 case GRP: return(obj.grp->GetRec());
	 case GRAPHIC_GRP: return(obj.ggrp->GetRec());
	 case AMON: return(obj.amon->GetRec());
	 case AMON_INPUTS: return(obj.amon_input->GetRec());
//	 case MONSETUP: return(obj.mon->GetRec());
	 case ALARMS: return(obj.alarms->GetRec());
	 case ALARMM: return(obj.alarmm->GetRec());
	 case TBL: return(obj.tbl->GetRec());
	 case UNIT: return(obj.units->GetRec());
	 case USER_NAME: return(obj.user_name->GetRec());
	 case CSTATION:
	 case STATION: return(obj.st->GetRec());
	 case NETSTAT: return(obj.netstat->GetRec());
	 case NETSTATUS:return(obj.ns->GetRec());
	 case ARRAY1: return(obj.array->GetRec());
	 case CONNECT_COM: return(obj.ccom->GetRec());
	 case NET_SEL: return(obj.net->GetRec());
	 case AY: return(obj.ay->GetRec());
	 case AYVALUE: return(obj.ayvalue->GetRec());
	 }
	return 0;
}

char *GGrid::FFldName(FILEHANDLE hfile,pointer_point_obj  obj, FIELDHANDLE hfield)
{
 if (fh)
		return(FXFldName(hfile, hfield));
//		return((char *)recstruct[hfield-1].field_name);
 else
/*		switch (point_type) {
			 case OUT: return(obj.out->GetFldName(hfield)); break;
			 case IN: return(obj.in->GetFldName(hfield)); break;
			 case VAR: return(obj.var->GetFldName(hfield)); break;
			 case CON: return(obj.con->GetFldName(hfield)); break;
		}
*/
	return(obj.out->GetFldName(hfield));
	}

int GGrid::FNextRec(FILEHANDLE hfile, pointer_point_obj  obj)
{
 if(!hfile)
/*		switch (point_type) {
			 case OUT: obj.out->NextRec(); break;
			 case IN: obj.in->NextRec(); break;
			 case VAR: obj.var->NextRec(); break;
			 case CON: obj.con->NextRec(); break;
		}
*/
		obj.out->NextRec();
}

int GGrid::FFldSize(FILEHANDLE hfile,pointer_point_obj  obj, FIELDHANDLE hfield)
{
 if (fh)
		return(FXFldSize(hfile, hfield));
//				return(recstruct[hfield-1].l);
 else
/*		switch (point_type) {
			 case OUT: return(obj.out->GetFldSize(hfield)); break;
			 case IN: return(obj.in->GetFldSize(hfield)); break;
			 case VAR: return(obj.var->GetFldSize(hfield)); break;
			 case CON: return(obj.con->GetFldSize(hfield)); break;
		}
*/
		return(obj.out->GetFldSize(hfield));
}

int	GGrid::FPutAlpha(FILEHANDLE fh,pointer_point_obj obj,FIELDHANDLE hfield,char *buf)
{
 if (fh)
		FXPutAlpha(fh, hfield, buf);
 else
/* switch (point_type) {
	 case OUT: obj.out->PutAlpha(hfield, buf); break;
	 case IN: obj.in->PutAlpha(hfield, buf); break;
	 case VAR: obj.var->PutAlpha(hfield, buf); break;
	 case CON: obj.con->PutAlpha(hfield, buf); break;
	 }
*/
	 obj.out->PutAlpha(hfield, buf);
}



int GGrid::FGetAlpha(FILEHANDLE fh,pointer_point_obj obj,FIELDHANDLE hfield,int bufsize,char *dest)
{
 if (fh)
		FXGetAlpha(fh, hfield, bufsize, dest);
 else
/* switch (point_type) {
	 case OUT: obj.out->GetAlpha(hfield, bufsize, dest); break;
	 case IN: obj.in->GetAlpha(hfield, bufsize, dest); break;
	 case VAR: obj.var->GetAlpha(hfield, bufsize, dest); break;
	 case CON: obj.con->GetAlpha(hfield, bufsize, dest); break;
	 }
*/
	 obj.out->GetAlpha(hfield, bufsize, dest);
}

int GGrid::FGotoRec(FILEHANDLE fh, pointer_point_obj  obj,RECORDNUMBER record_number)
{
 if (fh)
		 FXGotoRec(fh,record_number);
 else
/* switch (point_type) {
	 case OUT: obj.out->GotoRec(record_number); break;
	 case IN: obj.in->GotoRec(record_number); break;
	 case VAR: obj.var->GotoRec(record_number); break;
	 case CON: obj.con->GotoRec(record_number); break;
	 }
*/
	 obj.out->GotoRec(record_number);
}

int GGrid::FClose(FILEHANDLE fh, pointer_point_obj  obj)
{
 if (fh)
		 FXClose(fh);
}

void GGrid::GGReDrawGrid()
{
// int lung=textheight("H")+LINE_SPACE;
	w_nfields = 0;
	t_fields[w_lfield-1]=1;
	w_field = 1;
 if(!mode_text)
 {
	setfillstyle(SOLID_FILL, Lightgray);
	bar(tx,ty+LINE_SPACE+lung_char_n+1,bx-1,by-1);
 }
 GGDrawGrid(Black);
 GGHideCur(Black);
 w_record = 1;
 w_field = 1;
}

////////////////////////// start printgrid
int GGrid::GPrintGrid(int rows)
{
	 char field_name[100],s[3], buf[100];
	 int l,l1,i,j,k,c1, w_orecord,length,temp;

	 FGotoRec(fh,obj,w_urecord);
	 i=w_lfield+w_field-1-1;
	 l = t_fields[i]-1;
	 l1=max(strlen(rtrim(FFldName(fh, obj, i+1))),FFldSize(fh, obj, i+1));
	 w_nfields=0;
	 field_wide[w_nfields]=l1;
	 temp=field_wide[w_nfields];
	 if((pf=fopen("point.txt","at+"))==NULL)
	 {
		gotoxy(10,20);
		printf("can't not open file error!");
	 }
	 s[0]='\n';s[1]='\n';s[2]='\0';
	 fwrite(s,strlen(s),1,pf);
//	 if((point_type!=13) || (point_type!=AR_Y))
	 {
		 strcpy(buf," [ Panel ");
		 itoa(Gpanel,&buf[strlen(buf)],10);
//		 strcat(buf,", ");
//		 strcat(buf,panel_info1.panel_name);
		 if(point_type<=USER_NAME)
		 {
			 strcat(buf,", ");
			 strcat(buf,point_cod[point_type]);
		 }
		 strcat(buf," ]");
		 strcat(buf,"         ");
	 }
	 if( point_type!=AR_Y || point_type!=UNIT)
	 {
		 fwrite(buf,strlen(buf),1,pf);
		 time_date(buf);
		 fwrite(buf,strlen(buf),1,pf);
	 }
	 fwrite(s,strlen(s),1,pf);

	 while (w_nfields<fields_number)
	 {
		w_nfields++;
		movedata( FP_SEG(FFldName(fh,obj,i+1)), FP_OFF(FFldName(fh,obj,i+1)),FP_SEG(field_name), FP_OFF(field_name), strlen(FFldName(fh,obj,i+1)) + 1);
		strlwr(&field_name[1]);
		rtrim(field_name);
		length=l1-strlen(field_name);
		for(k=0;k<length;k++)
		{
			strcat(field_name," ");
		}
		if(point_type!=AR_Y)
		{
			fwrite(field_name,strlen(field_name),1,pf);
			fwrite("|",1,1,pf);
		}
		if((mode_text ? (l!=(bx-tx+2)/lat_char_n) : (l!=2*lat_char_n+(bx-tx-2-COL_SPACE)/lat_char_n)))
		{
			i++;
			if(i == fields_number) break;
			l1=max(strlen(rtrim(FFldName(fh, obj, i+1))),FFldSize(fh, obj, i+1));
			field_wide[w_nfields]=l1;
			temp=field_wide[w_nfields];
		}
	 t_fields[i]=mode_text ? l+1 : l ;
	 w_rfield = i;
	 w_nlfield = mode_text? (bx-tx+1-l*lat_char_n) / lat_char_n : (bx-tx-2-l*lat_char_n) / lat_char_n;
	}

 field_wide[i+1]=-1;
 fwrite("\n",1,1,pf);

 w_orecord = w_record;
 i=w_urecord;
 w_nrecords = 0;
 w_record = 0;
 i=0;
 int flag;
 flag=0;
 line_count=1;
 while(i++<rows)
 {
		w_nrecords++;
		w_record++;
		flag=GPrintRecord(w_urecord+w_record-1);
		if(flag==1)
		{
			line_count++;
		}
 }
 w_drecord = i-1;

 fclose(pf);
 return line_count;
}
/////////////////////////////  end of printgrid
// get time & date
void GGrid::time_date(char *temp)
{
	 struct time t;
	 struct date d;
	 int i;

	 temp[0]='\0';
	 gettime(&t);
	 i=t.ti_hour>=12? t.ti_hour%12:t.ti_hour;
	 if(t.ti_hour>=12)
		strcat(temp,"PM ");
	 else
		strcat(temp,"AM ");
	 itoa(i,&temp[strlen(temp)],10);
	 strcat(temp," : ");

	 i=t.ti_min;
	 itoa(i,&temp[strlen(temp)],10);
	 strcat(temp," : ");

	 i=t.ti_sec;
	 itoa(i,&temp[strlen(temp)],10);
	 strcat(temp,"  ");

	 getdate(&d);

	 i=d.da_year;
	 itoa(i,&temp[strlen(temp)],10);
	 strcat(temp," . ");

	 i=d.da_mon;
	 itoa(i,&temp[strlen(temp)],10);
	 strcat(temp," . ");

	 i=d.da_day;
	 itoa(i,&temp[strlen(temp)],10);
	 strcat(temp,"\0");
}
// end of time & date

void GGrid::GGDrawGrid(int col)
{
 char field_name[20];
 int l,l1,i,k,c1, w_orecord ;
 hide_pointer();
// if(mode_text)
// {
// lat=1;
// lung=1;
// }
// else
// {
// setlinestyle(DOTTED_LINE,0xff,1);
// c1=getcolor();
// setcolor(col);
// lat=textwidth(" ");
// lung=textheight("H")+LINE_SPACE;
// }

//if(!refresh)
{

 if(!mode_text)
 {
	c1=getcolor();
	setcolor(col);
 }

 FGotoRec(fh,obj,w_urecord);
// w_lfield = 1;
 i=w_lfield+w_field-1-1;
 l = t_fields[i]-1;
// l1 = max(mstrlen(rtrim((char *)recstruct[i].field_name)),recstruct[i].l)*8 + 3;
 l1=max(strlen(rtrim(FFldName(fh, obj, i+1))),FFldSize(fh, obj, i+1));
// w_nfields = 0;
/////// lin_ver[by-ty+1]=0;
 while ( (mode_text ? (l+l1<=(bx-tx+1)/lat_char_n) : (l+l1<=(bx-tx-2-COL_SPACE)/lat_char_n)) && w_nfields<fields_number) {
		w_nfields++;
		movedata( FP_SEG(FFldName(fh,obj,i+1)), FP_OFF(FFldName(fh,obj,i+1)),FP_SEG(field_name), FP_OFF(field_name), strlen(FFldName(fh,obj,i+1)) + 1);
//		strcpy(field_name, FFldName(fh,obj,i+1));
		strlwr(&field_name[1]);
//		display_pointer();
		GWPuts(0,mode_text ? l+1 : l ,rtrim(field_name),header_bkgcolour,col);
		t_fields[i]=mode_text? l+1 : l;

//		hide_pointer();
		l=l+l1+SPACE_CHAR;
		if((mode_text ? (l!=(bx-tx+2)/lat_char_n) : (l!=2*lat_char_n+(bx-tx-2-COL_SPACE)/lat_char_n)))
		if(mode_text)
		{
//		mgotoxy(tx+(l-1)*lat,ty-1);


		moutchar( tx+(l-1)*lat_char_n,ty-1,'³' , header_bkgcolour, col );

/*
		dxscreen--;
		dyscreen++;
		mxyputs(tx+(l-1)*lat,ty,lin_ver,colour,Black);
		dxscreen++;
		dyscreen--;
*/
//		l1 = max(mstrlen(rtrim((char *)recstruct[i].field_name)),recstruct[i].l)*8 + 3;
		}
		else
		{
//		setcolor(col);
		pline(tx+(l-1)*lat_char_n+4,ty,tx+(l-1)*lat_char_n+4,by,col);
		}
		i++;
		if(i == fields_number) break;
		l1=max(strlen(rtrim(FFldName(fh, obj, i+1))),FFldSize(fh, obj, i+1));
 }
	t_fields[i]=mode_text ? l+1 : l ;
/////////	lin_ver[by-ty+1]='³';


 w_rfield = i;
 w_nlfield = mode_text? (bx-tx+1-l*lat_char_n) / lat_char_n : (bx-tx-2-l*lat_char_n) / lat_char_n;
// w_orecord = 0;

}
//else
 w_orecord = w_record;
 i=w_urecord;
 w_nrecords = 0;
 w_record = 0;
 if(mode_text)
 {
 l1= 1;
 l = 0;
// mtextbackground(colour);
 }
 else
 {
 l1= LINE_SPACE+(lung_char_n+LINE_SPACE);
 l = LINE_SPACE+(lung_char_n+LINE_SPACE);
 }
 hide_pointer();
 while (l+l1 <= (by-ty+(mode_text? 1:-2))) {
		w_nrecords++;
		w_record++;
//		display_pointer();
		if(refresh && w_orecord==w_record)
			GGPutRecord(w_urecord+w_record-1,bkgcolour,Blue);
		else
			GGPutRecord(w_urecord+w_record-1,bkgcolour,Black);
//		hide_pointer();
		l=l+l1;
		if(!mode_text)
			pline(tx,ty+l,bx,ty+l,col);
		i++;
 }
 w_drecord = i-1;
 if(!mode_text)
	{
	 setcolor(c1);
	 line_style=FILL;
	}
 display_pointer();
}


void GGrid::GShowGrid(void)
{
 int lung;
/*
 if(!mode_text)
 {
	msettextstyle(font_type, 0, charsize);
 }
*/
 GShowWindow(grid);
 if(title_status)
 {
	 char buf[50];
	 strcpy(buf,"[ ");
	 strcat(buf,"Panel ");
	 itoa(Gpanel,&buf[strlen(buf)],10);
//	 strcat(buf,", ");
//	 strcat(buf,panel_info1.panel_name);
	 rtrim(buf);
	 if(point_type <= USER_NAME)
	 {
		strcat(buf,", ");
		strcat(buf,point_cod[point_type]);
	 }
	 strcat(buf," ]");

	 hide_pointer();
	 if(mode_text)
	 {
		if((int)strlen(buf)<(int)rbottom.x-(int)(ltop.x+11))
			mxyputs(ltop.x+5,ltop.y,buf,title_bkgcolour,Lightgray);
	 }
	 else
	 {
		setcolor(White);
		outtextxy(ltop.x+40,ltop.y+3,buf);
	 }
	 strcpy(buf,"Ctrl-P Print");
	 if(point_type!=AMON_INPUTS)
	 if(mode_text)
			mxyputs(rbottom.x-14,ltop.y,buf,title_bkgcolour,White);
	 else
	 {
		setcolor(White);
		outtextxy(rbottom.x-140,ltop.y+3,buf);
	 }
	 display_pointer();
 }
 hide_pointer();
 if(mode_text)
 {
	lin_menu[bx-tx+1]=0;
	mxyputs(tx,ty-1,lin_menu,header_bkgcolour,header_bkgcolour);
	lin_menu[bx-tx+1]=lin_menu[0];
 }
 else
 {
	setcolor(Black);
	setfillstyle(SOLID_FILL,header_bkgcolour);
	bar(tx,ty,bx,ty+LINE_SPACE+(lung_char_n+LINE_SPACE));
	prectangle(tx,ty,bx,ty+LINE_SPACE+(lung_char_n+LINE_SPACE),Black);
 }

 display_pointer();
// w_lfield=1;
 w_field = w_lfield;
 w_nfields = 0;
 w_field = 1;
 t_fields[w_field-1]=1;
 GGDrawGrid(Black);
 if(!mode_text)
	 pline(tx,ty,tx,by,Black);
 w_field = 1; w_record = 1;
 GGShowCur(Black);
//	settextstyle(DEFAULT_FONT, HORIZ_DIR,1);
}


int GGrid::GSend(int type)
{
	 char *ptr_obj;
	 uint j,i;
			if(modify )             //&& descriptor)
									{
//									 mgotoxy(60,4);
//									 cprintf("Sending...");

									 int l=0;
//									 save_prg_flag = 1;
/*
									 for(i=0;i<bank;i++)
										 l += tbl_bank[point_type][i+1];
*/
									 if(Gtype==INDIVIDUAL)
										 l=Gpoint_num-1;
									 switch (point_type) {
											case OUT:
											case IN:
											case VAR:
											case CON:
											case WR:
											case AR:
											case PRG:
											case GRP:
//														 ptr_panel->outputs=obj.out;
//														 ptr_panel->Outputs(WRITE);
//														if((local_panel && Gtype!=INDIVIDUAL) || (Gtype==INDIVIDUAL && Gpanel==Station_NUM && Gnetwork==NetworkAddress))
														if( Glocal )
														{
															 memmove(ptr_panel->info[point_type].address+l*ptr_panel->info[point_type].str_size, ptr_block, max_points_bank*ptr_panel->info[point_type].str_size);
															 save_prg_flag = 1;
															 if(point_type==AR)
																 check_annual_routine_flag=1;
														}
#ifdef NETWORK_COMM
														 else
															{
															 operator_list.buffer=ptr_block;
															 operator_list.length=max_points_bank*ptr_panel->info[point_type].str_size;
															}
#endif
														 break;
											case WR_TIME:
//														 ptr_panel->wr_times=obj.wr_time;
//														 ptr_panel->Weekly_Routine_Times(WRITE,obj.wr_time->routine_num-1);
//														 if((local_panel && Gtype!=INDIVIDUAL) || (Gtype==INDIVIDUAL && Gpanel==Station_NUM && Gnetwork==NetworkAddress))
														 if( Glocal )
														 {
															 memmove(&ptr_panel->wr_times[obj.wr_time->routine_num-1][0], obj.wr_time->block, max_points_bank*sizeof(Wr_one_day));
															 save_prg_flag = 1;
                               check_weekly_routine_flag = 1;
														 }
														 else
														 if( serial_access )
														 {
//															obj.wr_time->panel_type = T3000;
															ptr_obj = (char *)obj.wr_time;
														 }
#ifdef NETWORK_COMM
														 else
															{
															 operator_list.buffer=(char *)obj.wr_time->block;
															 operator_list.length=max_points_bank*sizeof(Wr_one_day);
															}
#endif
														 break;
											case AR_Y:
//														 ptr_panel->ar_dates=obj.ar_y;
//														 ptr_panel->Annual_Routine_Dates(WRITE,obj.ar_y->routine_num-1);
//														 if((local_panel && Gtype!=INDIVIDUAL) || (Gtype==INDIVIDUAL && Gpanel==Station_NUM && Gnetwork==NetworkAddress))
														 if( Glocal )
														 {
															 memmove(&ptr_panel->ar_dates[obj.ar_y->routine_num-1][0], obj.ar_y->block_year, 46);
															 save_prg_flag = 1;
															 check_annual_routine_flag=1;
														 }
														 else
														 if( serial_access )
														 {
//															obj.ar_y->panel_type = T3000;
															ptr_obj = (char *)obj.ar_y;
														 }
#ifdef NETWORK_COMM
														 else
															{
															 operator_list.buffer=(char *)obj.ar_y->block;
															 operator_list.length=46;
															}
#endif
														 break;
											case AMON:
//														if((local_panel && Gtype!=INDIVIDUAL) || (Gtype==INDIVIDUAL && Gpanel==Station_NUM && Gnetwork==NetworkAddress))
														if( Glocal )
														{
															 int x=0;
															 if(modify_monitor==1)
															 {
																while(save_monitor_status);
																present_analog_monitor=0;
																save_monitor = 0x01 | 0x02;
																save_monitor_command = 1;
																save_m();
																save_monitor_command=0;
																save_monitor_status = 0;
//																resume(AMONITOR);
//																task_switch();
																x=1;
															 }
															 memmove(ptr_panel->analog_mon, ptr_block, max_points_bank*ptr_panel->info[point_type].str_size);
/*
															 char huge *p;
															 for(i=0; i< max_points_bank; i++)
															 {
																 p =  ptr_panel->analog_mon[l].data_segment;
																 memmove(&ptr_panel->analog_mon[l], (char *)(obj.amon->block+i),
																			sizeof(Str_analog_monitor_point)-35);   //-(2+MAX_VIEWS*sizeof(struct views))-4);
																			 // 37-MAX_VIEWS*sizeof(struct views)); // nu trebuie modificat start_index_dig si end_index_dig
																 ptr_panel->analog_mon[l].data_segment=p;
																 l++;
															 }
*/
															 if(x)
															 {
																 initanalogmon();
															 }
															 save_prg_flag = 1;
														}
#ifdef NETWORK_COMM
														else
															{
															 operator_list.buffer=(char *)obj.amon->block;
															 operator_list.length=max_points_bank*sizeof(Str_analog_monitor_point);
															}
#endif
														 break;
											case AMON_INPUTS:
														 memmove(amon_inputs, (char *)obj.amon_input->block, sizeof(amon_inputs));
														 break;
											case MONSETUP:
/*
														if((local_panel && Gsub_panel!=INDIVIDUAL) || (Gsub_panel==INDIVIDUAL && Gpanel==Station_NUM))
															{
															 present_analog_monitor=0;
															 memmove(&ptr_panel->mon_setup[l], (char *)obj.mon->block, max_points_bank*sizeof(Monitor_element));
															 int k=0;
															 for(int i=0;i<MAX_MONSET;i++)
															 {
																if(!ptr_panel->mon_setup[i].analog_digital && ptr_panel->mon_setup[i].grpsize)
																 {
																	for(int j=0;j<ptr_panel->mon_setup[i].number_of_mon;j++)
																	 {
																		ptr_panel->analog_mon[k].num_inputs=ptr_panel->mon_setup[i].grpsize;
																		ptr_panel->analog_mon[k].data_length=ptr_panel->mon_setup[i].length;
																		ptr_panel->analog_mon[k].double_flag=ptr_panel->mon_setup[i].two_or_4_bytes;
																		ptr_panel->analog_mon[k].hour_interval_time=0;
																		ptr_panel->analog_mon[k].minute_interval_time=15;
																		ptr_panel->analog_mon[k].second_interval_time=0;
																		ptr_panel->analog_mon[k].next_sample_time=(0*3600+15*60+0)*18.2;
																		k++;
																	 }
																 }
															 }
															 for(i=k;i<MAX_ANALM;i++)
															 {
																ptr_panel->analog_mon[k].num_inputs = 0;
																ptr_panel->analog_mon[k].data_segment = 0;
																ptr_panel->analog_mon[k].next_sample_time = 0;
															 }
															 char huge *p=heap_amon;
															 for(i=0;i<k;i++)
															 {
																ptr_panel->analog_mon[i].data_segment=p;
																p += ptr_panel->analog_mon[i].data_length*ptr_panel->analog_mon[i].num_inputs*
																		 (ptr_panel->analog_mon[i].double_flag*2+2);
															 }
															if(k) present_analog_monitor=1;
															}
														 else
															{
															 operator_list.buffer=(char *)obj.mon->block;
															 operator_list.length=max_points_bank*sizeof(Monitor_element);
															}
*/
														 break;
											case ALARMS:
//														 if((local_panel && Gtype!=INDIVIDUAL) || (Gtype==INDIVIDUAL && Gpanel==Station_NUM && Gnetwork==NetworkAddress))
														 if( Glocal )
														 {
															 memmove(&ptr_panel->alarms_set[0], (char *)obj.alarms->block, max_points_bank*sizeof(Alarm_set_point));
															 save_prg_flag = 1;
														 }
														 else
														 if( serial_access )
														 {
//															obj.alarms->panel_type = T3000;
															ptr_obj = (char *)obj.alarms;
														 }
#ifdef NETWORK_COMM
														 else
															{
															 operator_list.buffer=(char *)obj.alarms->block;
															 operator_list.length=max_points_bank*sizeof(Alarm_set_point);
															}
#endif
														 break;
											case ALARMM:
//														 if((local_panel && Gtype!=INDIVIDUAL) || (Gtype==INDIVIDUAL && Gpanel==Station_NUM && Gnetwork==NetworkAddress))
														 if( Glocal )
														 {
															update_alarm_tbl(obj.alarmm->block,max_points_bank);
														 }
/*
															 if(obj.alarmm->block[i].alarm)
															 {
																if(!obj.alarmm->block[i].ddelete)
																	 ptr_panel->alarms[obj.alarmm->nrmes[i]]=obj.alarmm->block[i];
																else
																	 memset(&ptr_panel->alarms[obj.alarmm->nrmes[i]],0,sizeof(Alarm_point));
															 }
*/
														break;
											case TBL:
														{
														int t;
/*
														for(int i=0;i<5;i++)
														{
														t=0;
														do
														{
														 for(int j=0; j<15; j++)
														 {
															if(obj.tbl->block[i][j].value > obj.tbl->block[i][j+1].value)
															{
															 int x;
															 t=1;
															 x = obj.tbl->block[i][j].value;
															 obj.tbl->block[i][j].value = obj.tbl->block[i][j+1].value;
															 obj.tbl->block[i][j+1].value = x;
															}
														 }
														}	while (t);
														}
*/														
//														if((local_panel && Gtype!=INDIVIDUAL) || (Gtype==INDIVIDUAL && Gpanel==Station_NUM && Gnetwork==NetworkAddress))
													  if( Glocal )
														{
															 memmove((char *)&custom_tab[obj.tbl->tblno-1], (char *)obj.tbl->block, sizeof(Str_tbl_point));
															 save_prg_flag = 1;
														}
														else
														 if( serial_access )
														 {
//															obj.tbl->panel_type = T3000;
															ptr_obj = (char *)obj.tbl;
														 }
/*
#ifdef NETWORK_COMM
														 else
															{
															 operator_list.buffer=(char *)obj.tbl->block;
															 operator_list.length=max_points_bank*5*sizeof(Tbl_point);
															}
#endif
*/														break;
													  }
											case UNIT:
													 {
//														 if((local_panel && Gtype!=INDIVIDUAL) || (Gtype==INDIVIDUAL && Gpanel==Station_NUM && Gnetwork==NetworkAddress))
														 if( Glocal )
														 {
															 memmove(&ptr_panel->units[0], (char *)obj.units->block, max_points_bank*sizeof(Units_element));
															 upcustomunit(ptr_panel->units);
															 save_prg_flag = 1;
														 }
														 else
														 if( serial_access )
														 {
//															obj.units->panel_type = T3000;
															ptr_obj = (char *)obj.units;
														 }
#ifdef NETWORK_COMM
														 else
															{
															 operator_list.buffer=(char *)obj.units->block;
															 operator_list.length=max_points_bank*sizeof(Units_element);
															}
#endif
														 break;
														}
											case USER_NAME:
//														if((local_panel && Gtype!=INDIVIDUAL) || (Gtype==INDIVIDUAL && Gpanel==Station_NUM && Gnetwork==NetworkAddress))
														if( Glocal )
														{
															 memmove(ptr_panel->info[point_type].address+l*ptr_panel->info[point_type].str_size, ptr_block, 2+max_points_bank*ptr_panel->info[point_type].str_size);
															 save_config(CNF_PASS_INFO);
															 save_prg_flag = 1;
														}
														if( serial_access )
														{
															ptr_obj = (char *)obj.user_name;
														}
//														memmove(&passwords.passwords[0], obj.user_name->block, max_points_bank*sizeof(Password_point));
														break;
											case STATION:
/*
														 memmove(&station_list[0], obj.st->block, max_points_bank*sizeof(Station_point));
														 strcpy(station_name, station_list[station_num-1].name);
														 if(station_num==Station_NUM)
																strcpy(Station_NAME, station_list[station_num-1].name);
														 save_config(CNF_BOARD_INFO|CNF_STATION_INFO);
*/
														 break;
											case CSTATION:
//														 strcpy(station_name, station_list[station_num-1].name);
														 break;
											case NETSTAT:
														 break;
											case NETSTATUS:
														 break;
											case AY:
//														if (local_panel)
														if(Glocal)
														{
															memmove(&ptr_panel->arrays[l], (char *)obj.ay->block, max_points_bank*sizeof(Str_array_point));
															l = 0;
															long *p = heap_array;
															for(i=0; i<MAX_ARRAYS; i++)
															{
															 if(ptr_panel->arrays[i].length)
															 {
																ptr_panel->arrays_data[i] =  p;
																p += ptr_panel->arrays[i].length;
															 }
															 else
																ptr_panel->arrays_data[i] =  0;
															}
															save_prg_flag = 1;
														}
#ifdef NETWORK_COMM
														else
														{
															operator_list.buffer=(char *)obj.ay->block;
															operator_list.length=max_points_bank*sizeof(Str_array_point);
														}
#endif
														break;
											case AYVALUE:
														 break;
											}
//	if( (!local_panel && Gpanel==station_num) || Gpanel!=Station_NUM )
 if( !Glocal )
	if (point_type!=NETSTATUS && point_type!=NETSTAT && point_type!=STATION && point_type!=CSTATION && point_type != ARRAY1  && point_type != AMON_INPUTS && point_type != GRAPHIC_GRP
		 && point_type != CONNECT_COM && point_type != NET_SEL )
//	if( serial_access)
	{
	 RS232Error sub;
	 if(point_type != AMON || (point_type==AMON && modify_monitor))
	 {
	 if(type==SENDPOINTS)
	 {
		Point point;
//		point.panel = Gpanel-1;
		point.point_type = point_type+1;
		for(i = 0; i<=w_drecord - w_urecord; i++)
		{
		 if(refresh_table[i])
		 {
			point.number = w_urecord + i - 1;
			Delay(150);
			j = countlength(20, *((int *)&point) );
			sub = net_call(20+100, *((int *)&point),  (char *)ptr_block+point.number*j, &j, Gpanel, Gnetwork, NETCALL_RETRY, TIMEOUT_NETCALL);
		 }
		}
	 }
	 else
	 {
		int t=point_type+1, b = 0;
		if(Gtype==INDIVIDUAL)
		{
		 b=((point_type+1)<<8)+ Gpoint_num-1;
		 t=20;
		}
		if(point_type == AR_Y)
		{
		 b = obj.ar_y->routine_num-1;
		 t=point_type+1;
		}
		if(point_type == WR_TIME)
		{
		 b = obj.wr_time->routine_num-1;
		 t=point_type+1;
		}
		if(point_type == AYVALUE)
		{
		 b = obj.ayvalue->current_array;
		 t=point_type+1;
		}
		GWindow D(mode_text?25:200, mode_text?7:150, mode_text?55:500, mode_text?11:200, NO_STACK,0);
//		DisplayMessage(mode_text?25:200, mode_text?7:150, mode_text?55:500, mode_text?11:200, ctrlbreak_text, " Sending data...   ", NULL, Black, &D);
		DisplayMessageT(25, 7, 55, 11, ctrlbreak_text, " Sending data...   ", NULL, Black, &D);
		Delay(100);
		i = countlength(t, b);
//		sub = net_call(t+100, b, ptr_block, &i, Gpanel, Gnetwork, ( ((panel_info1.version>246)&&(t>OUT)&&(t<=AY+1))?NETCALL_WRITERETRY:0)|NETCALL_RETRY|NETCALL_SIGN, TIMEOUT_NETCALL);
		sub = net_call(t+100, b, ptr_block, &i, Gpanel, Gnetwork, NETCALL_RETRY|NETCALL_SIGN, TIMEOUT_NETCALL);
		D.GReleaseWindow();
		if(sub==SUCCESS)
		{
			if(point_type == UNIT)
			 upcustomunit((Units_element *)ptr_block);
			if(point_type == ALARMM)
			{
				if( (panel_info1.panel_type == T3000 && panel_info1.version >= 216) ||
					(panel_info1.panel_type == MINI_T3000 && panel_info1.version >= 107) )
				 net_call(COMMAND_50, ALARM_NOTIFY_COMMAND, &gAlarm, 0, station_num, networkaddress);
			}
		}
	 }
//		sub = ser_ptr->Serial_control( point_type+1, WRITE, Gpanel, ptr_obj, 0 );
//		if(serial_access)
//		 result_ser(sub);
//		else
//		 result_ser(sub,1);
//		ser_ptr->Serial_control( 33, READ, 0, 0, sub );
		memset(refresh_table, 0, 24);
//		if( sub == 34 ) mxyputs( 40, 23, "Sending Error !!!" );
//		else if( sub == 33 ) mxyputs( 40, 23, "Sending OK !!!" );]
	}
  }
/*
	else
		GReadNet(100);
*/
/*
	if (!local_panel && point_type!=STATION && point_type!=CSTATION && point_type!=USER_NAME)
///////////////
	if( Netbios_state == NB_INSTALLED )
				{
				 memcpy( operator_list.name, station_list[station_num-1].name, 16 );
				 operator_list.command[0]=station_num;
				 operator_list.command[1]=0;
				 operator_list.command[2] = point_type+101;
				 uint nr_bank = bank;
				 memcpy(&operator_list.command[3],&nr_bank, 2);
				 operator_list.command[5]=0;
//				 operator_list.buffer=(char *)obj.out->block;

				 operator_list.state = REQUEST;
				 resume(NETWORK);
				 task_switch();

				 while(operator_list.state!=DONE && operator_list.state!=ERROR);
				 suspend(NETWORK);
				 if(operator_list.state==ERROR)
							{
//								FClose(fh,obj);
								error_net=1;
//								return ;
							}
///////////////
				}
*/
/*
									 if(mode_text)
									 {
									 mgotoxy(60,4);
										mtextbackground(Black);
										mtextcolor(Lightgray);
										 mcputs("±±±±±±±±±±");
										}
*/
//									 DeleteMessage(pm);
									}
			modify=FALSE;
}

int GGrid::HandleEvent(void)
{
	union {
		int i;
		char ch[2];
		} key;
	uint dx;
	MouseStatus stat;


 if (bioskey_new(1) || esc)                //kbhit())
 {
	if(!esc)
	{
		key.i = bioskey_new(0);
	}
	GGHideCur(Black);
	if (key.ch[0] == 27 || esc==1 || (key.ch[0] == '\t' && point_type==AMON_INPUTS)
											|| (key.ch[0] == '\t' && point_type==CSTATION) )
	{
			if( point_type==AMON )
			{
			 monitor_accessed=0;
			 if(mode_text)
//				 clear_color(50, 30, ltop.y, rbottom.y, lin_text, fond_color, Black);
				 clear_color(50, 30, 3, 21, lin_text, fond_color, Black);
			 else
			 {
				 setfillstyle(SOLID_FILL, fond_color);
				 bar(400, 30, 640, 450);
			 }
			}
			if( point_type==NET_SEL )
			{
			 if(mode_text)
				 clear_color(50, 30, ltop.y, rbottom.y, lin_text, fond_color, Black);
			}
			GReleaseWindow();

			GSend();
//			savedes();
			FClose(fh,obj);

			if(!mode_text)
				msettextstyle(DEFAULT_FONT, HORIZ_DIR,1);
			return 1;
	}
	if (key.ch[0]==0)
	switch (key.ch[1]){
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.012  ********
// ********       begin       ********
// ***********************************
	 case F1KEY:
			{
				switch (point_type)
				{
					case	OUT:
							{
								T3000help(23);
							}
							break;
					case 	IN:
							{
								T3000help(22);
							}
							break;
					case 	VAR:
							{
								T3000help(24);
							}
							break;
					case 	CON:
							{
								T3000help(25);
							}
							break;
					case 	WR:
							{
								T3000help(26);
							}
							break;
					case 	AR:
							{
								T3000help(27);
							}
							break;
					case 	PRG:
							{
								T3000help(21);
							}
							break;
					case 	GRP:
							{
								T3000help(20);
							}
							break;
					case 	AMON:
							{
								T3000help(30);
							}
							break;
					case 	ALARMM:
							{
								T3000help(33);
							}
							break;
					case 	TBL:
							{
								T3000help(31);
							}
							break;
					case 	UNIT:
							{
								T3000help(32);
							}
							break;
					case 	USER_NAME:
							{
								T3000help(41);
							}
							break;
					case 	STATION:
							{
								T3000help(40);
							}
							break;
					case 	AY:
							{
								T3000help(28);
							}
							break;
					case 	CONNECT_COM:
							{
								T3000help(0);
							}
							break;
					case 	NET_SEL:
							{
								T3000help(11);
							}
							break;
					case ARRAY1:
							{
					  			if (Gpoint_num==9)
								{
									T3000help(31);
								}
								else
								{
									T3000help(201);
								}
							}
							break;
// ********  the unknow type  *********
					case WR_TIME:
							{
								T3000help(1);
							}
							break;
					case AR_Y:
							{
								T3000help(2);
							}
							break;
					case GRAPHIC_GRP:
							{
								T3000help(3);
							}
							break;
					case AMON_INPUTS:
							{
								T3000help(4);
							}
							break;
					case ALARMS:
							{
								T3000help(5);
							}
							break;
					case CSTATION:
							{
								T3000help(6);
							}
							break;
					default:
							{
								T3000help(Flag_help);
							}
				}
			}; break;
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.012  ********
// ********        end        ********
// ***********************************
	 case ENDKEY:
								GGLeftRightGrid(ENDKEY);
								return 0;
	 case RIGHT: if (w_field==w_nfields)    //right
						 {
							if (w_rfield < fields_number)
								{
								GGLeftRightGrid(LEFT);
								return 0;
								}
						 }
						else w_field += 1;
						break;
	 case HOME:
								GGLeftRightGrid(HOME);
								return 0;
	 case LEFT: if (w_field==1)
							{
							if ( w_lfield > 1 )     //left
								{
								GGLeftRightGrid(RIGHT);
								return 0;
								}
							}
						else w_field -= 1;
						break;
	 case PGUP:                                    //pgup
						 if(point_type==AR_Y)
								 {
									key.ch[0]='\x0D';
									break;
								 }

							 if (w_urecord>1)
								 {
/*									int i=0;
									while(w_urecord>1 && i++<w_nrecords)
										GGUpDownGrid(UP);
*/
										GGUpDownGrid(PGUP);
									return 0;
								 }
							else
							 {
								change_bank(UP);
								GGShowCur(Black);
								return 0;
							 }

	 case UP:
						 if (w_record==1)                  //up
						 {
						 if (w_urecord>1)
							{
							GGUpDownGrid(UP);
							return 0;
							}
							else
							 {
								change_bank(UP);
								GGShowCur(Black);
								return 0;
							 }

						 }
						else w_record -= 1;
						break;
	 case PGDN:                                // pgdn
						 if(point_type==AR_Y)
								 {
									key.ch[0]='\x0D';
									break;
								 }
						 if (w_drecord<NRec)
							{
/*									int i=0;
									while(w_drecord<NRec && i++<w_nrecords)
										GGUpDownGrid(DOWN);
									return 0;
*/
										GGUpDownGrid(PGDN);
									return 0;
							}
							else
							 {
								change_bank(DOWN);
								GGShowCur(Black);
								return 0;
							 }

	 case DOWN: if (w_record==w_nrecords)        //down
						 {
						 if (w_drecord<NRec)
							{
							GGUpDownGrid(DOWN);
							return 0;
							}
						 else
							{
							change_bank(DOWN);
							GGShowCur(Black);
							return 0;
							}

						 }
						else w_record += 1;
						break;
	 case 46: // Alt-C
	 case 25: // Alt-P
	 case INSERT:
			 if( filename[0] )
			 {
				 char buff[16];
				 pointer_point_obj sl_point;
				 sl_point.sl = 0;
				 entry_selected = w_urecord + w_record - 1;
				 FGotoRec( syslist_handle, sl_point, entry_selected );
				 FGetRec( syslist_handle, sl_point );
				 FGetAlpha( syslist_handle, sl_point, 1, 20, dial_list_data.system_name );
				 FGetAlpha( syslist_handle, sl_point, 2, L_DIAL_PHONE_NUMBER, dial_list_data.phone_number );
				 dial_list_data.phone_number[L_DIAL_PHONE_NUMBER-1] = 0 ;
				 FGetAlpha( syslist_handle, sl_point, 3, 15, dial_list_data.des_file );
				 FGetAlpha( syslist_handle, sl_point, 4, 15, dial_list_data.menu_file );
				 FGetAlpha( syslist_handle, sl_point, 5, 10, buff );
				 dial_list_data.baud_rate = atoi( buff );
//				 FGetAlpha( syslist_handle, sl_point, 6, 15, dial_list_data.link_number );
				 esc++;
				 if( !strlen(rtrim(dial_list_data.phone_number)) )
					 entry_selected=0;
			}
		 else key.ch[0]='\x0D';					 // insert
						break;
	 case DELETE: key.ch[0]='\x0D';					 // delete
						break;
	 case 132: 															// CTRL/PgUp
	 case 118: key.ch[0]='\x0D';					 // CTRL/PgDn
						break;
		 default:
						break;
	 }
	 else
		if (key.ch[0]==ENTER)
		{
		  key.ch[1] = '\x0D';
		  if(check_access(point_type, w_record-1)==R_READ_ONLY)
			 return 0;
		}
		else
		{
		 if (key.ch[0]==0x10)
		 {
			GPrintGrid(max_points_bank);
			sendtoprint();
		 }
		}

	 if (key.ch[0] == '\t')
				if(point_type==AMON || point_type==NET_SEL)
				 {
					 key.ch[0]='\x0D';
					 key.ch[1]='\t';
				 }
				else
				if (w_field==w_nfields)
						 {
								if (w_rfield < fields_number)
								{
								GGLeftRightGrid(LEFT);
								return 0;
								}
							else
								{
									GReleaseWindow();
									GWSet("Program",Lightgray,Darkgray);
									w_lfield = 1;
									w_urecord = 1;
									int ow_record = w_record;
									w_field = 1;
									GShowGrid();
									GGHideCur(Black);
									w_field = 1;
									w_record = ow_record;
								}
						 }
						else w_field += 1;

	 GGShowCur(Black);
	 if (key.ch[0] == '\x0D')
	 {
				int r=0,col;
				if(mode_text)
					 col=Black;
				else
				{
				 settextstyle(SMALL_FONT, 0, 5);
//				 lat  = textwidth(" ");
//				 lung = textheight("H")+LINE_SPACE;
				}

				GGHideCur(Black);
				index_obj = 0;
					GDDef_object(NULL,t_fields[w_field+w_lfield-1-1]-1,w_record-1,FFldSize(fh, obj, w_field+w_lfield-1),Black,White);
				if( !filename[0] )
				{
//				modify = TRUE;
				 refresh_table[w_record-1] = 1;
				 modify_child = 0;
				 switch (point_type) {
						case OUT:
						 obj.out->Read(w_field+w_lfield-1, key.ch[1]); break;
						case IN:
						 obj.in->Read(w_field+w_lfield-1, key.ch[1]); break;
						case VAR:
						 obj.var->Read(w_field+w_lfield-1, key.ch[1]); break;
						case CON:
						 obj.con->Read(w_field+w_lfield-1, key.ch[1]); break;
						case WR:
						 obj.wr->Read(w_field+w_lfield-1, key.ch[1]);
						 if( key.ch[1] == INSERT && modify_child )
							 {
								refresh_time = 0;
							 }
						 break;
						case WR_TIME:
						 obj.wr_time->Read(w_field+w_lfield-1, key.ch[1]); break;
						case AR:
						 obj.ar->Read(w_field+w_lfield-1, key.ch[1]);
						 if( key.ch[1] == INSERT && modify_child )
							 {
								refresh_time = 0;
							 }
						 break;
						case AR_Y:
						 col=obj.ar_y->Read(w_field+w_lfield-1, key.ch[1]);
						 break;
						case PRG:
						 obj.prg->Read(w_field+w_lfield-1, key.ch[1]);
/*
						 if( key.ch[1] == INSERT && modify_child )
							 {
								refresh_time = 0;
							 }
*/
						 break;
						case GRP:
						 r = obj.grp->Read(w_field+w_lfield-1, key.ch[1]);
						 break;
						case GRAPHIC_GRP:
						 obj.ggrp->Read(w_field+w_lfield-1, key.ch[1]);
						 break;
						case AMON:
						 obj.amon->Read(w_field+w_lfield-1, key.ch[1]); break;
						case AMON_INPUTS:
						 obj.amon_input->Read(w_field+w_lfield-1, key.ch[1]); break;
//						case MONSETUP:
//						 obj.mon->Read(w_field+w_lfield-1, this,key.ch[1]); break;
						case ALARMS:
						 modify = TRUE;
						 obj.alarms->Read(w_field+w_lfield-1, key.ch[1]); break;
						case ALARMM:
						 modify = TRUE;
						 obj.alarmm->Read(w_field+w_lfield-1, key.ch[1]);
						 break;
						case TBL:
						 modify = TRUE;
						 obj.tbl->Read(w_field+w_lfield-1, key.ch[1]); break;
						case UNIT:
						 modify = TRUE;
						 obj.units->Read(w_field+w_lfield-1, key.ch[1]); break;
						case USER_NAME:
						 modify=FALSE;
						 obj.user_name->Read(w_field+w_lfield-1, key.ch[1]);
						 break;
						case CSTATION:
						 obj.st->Read(w_field+w_lfield-1, key.ch[1]);
						 break;
						case STATION:
						 modify = TRUE;
						 obj.st->Read(w_field+w_lfield-1, key.ch[1]);
						 break;
						case NETSTAT:
						 obj.netstat->Read(w_field+w_lfield-1, key.ch[1]);
						 break;
						case NETSTATUS:
						 obj.ns->Read(w_field+w_lfield-1, key.ch[1]);
						 break;
						case ARRAY1:
						 modify = TRUE;
						 obj.array->Read(w_field+w_lfield-1, key.ch[1]);
						 GReleaseWindow();
						 if(!mode_text)
								msettextstyle(DEFAULT_FONT, HORIZ_DIR,1);
						 return 1;
						case AY:
						 modify = TRUE;
						 obj.ay->Read(w_field+w_lfield-1, key.ch[1]);
						 if(arights_grid) modify = 0;
						 break;
						case CONNECT_COM:
						 if( key.ch[1]==INSERT )
						 {
						  r=ESC;
						 }
						 break;
						case NET_SEL:
						 obj.net->Read(w_field+w_lfield-1, key.ch[1]);
						 break;
				 }
				 entry_selected = w_record+w_urecord-1;
//					modify = TRUE;
//					refresh_table[w_record-1] = TRUE;
				}
				else
				{
					char buf[40];
					FGetAlpha(fh,obj,w_field+w_lfield-1,MAX_ALPHA,buf);
					GDGets(buf,w_record,t_fields[w_field+w_lfield-1-1],recstruct[w_field+w_lfield-1-1].l*lat_char_n,Black,White);
					FGotoRec(fh,obj,w_record+w_urecord-1);
					FGetRec(fh,obj);
					FGotoRec(fh,obj,w_record+w_urecord-1);
					FXPutAlpha(fh,w_field+w_lfield-1,buf);
					FXPutRec(fh);
					flushall();
				}
//					mfarfree(handle_obj[index_cur]);
				mfarfree(objects[index_cur]);
				objects[index_cur]=NULL;
				index_obj = 0;

/*					FGetAlpha(fh,obj,w_field+w_lfield-1,MAX_ALPHA,buf);
					GDGets(buf,w_record,t_fields[w_field+w_lfield-1-1],recstruct[w_field+w_lfield-1-1].l*lat,Black,White);
					FGotoRec(fh,obj,w_record+w_urecord-1);
					FGetRec(fh,obj);
					FGotoRec(fh,obj,w_record+w_urecord-1);
					FXPutAlpha(fh,w_field+w_lfield-1,buf);
					FXPutRec(fh);
					flushall();
*/				 GGShowCur(col);
				 if( r == ESC ) esc = 1;
				 else esc = 0;
	 }



//	 while (kbhit())	key.i = bioskey_new(0);
 }

 mouse_status(stat);
 if(stat.leftButton)
 {

 if(mouse_inside(close_spot.top.x,
		 close_spot.top.y,
		 close_spot.bot.x,
		 close_spot.bot.y))
		{
			mouse_status(stat);
			if(stat.leftButton)
			 {
				while(!get_button_released(BLEFT,stat));
				esc = 1;
				return 0;
			 }
		}
 if(mouse_inside(lscroll.top.x,
		 lscroll.top.y,
		 lscroll.bot.x,
		 lscroll.bot.y))
		{
			mouse_status(stat);
			if(stat.leftButton)
			 {
						for(int i=0;i<2000;i++);
						GGHideCur(Black);
						 if (w_field==1)
							{
							if ( w_lfield > 1 )     //left
								{
								GGLeftRightGrid(RIGHT);
								return 0;
								}
							}
						else w_field -= 1;
						GGShowCur(Black);
						return 0;
			 }
		}
 if(mouse_inside(rscroll.top.x,
		 rscroll.top.y,
		 rscroll.bot.x,
		 rscroll.bot.y))
		{
			mouse_status(stat);
			if(stat.leftButton)
			 {
						for(int i=0;i<2000;i++);
						GGHideCur(Black);
						if (w_field==w_nfields)
						 {
							if (w_rfield < fields_number)
								{
								GGLeftRightGrid(LEFT);
								return 0;
								}
						 }
						else w_field += 1;
						GGShowCur(Black);
						return 0;
			 }
		}
 if(mouse_inside(uscroll.top.x,
		 uscroll.top.y,
		 uscroll.bot.x,
		 uscroll.bot.y))
		{
			mouse_status(stat);
			if(stat.leftButton)
			 {
						for(int i=0;i<12000;i++);
//						while(!get_button_released(BLEFT,stat));
						GGHideCur(Black);
						if (w_record==1)                  //up
						 {
						 if (w_urecord>1)
							{
							GGUpDownGrid(UP);
							return 0;
							}
						 }
						else w_record -= 1;
						GGShowCur(Black);
						return 0;
			 }
		}
 if(mouse_inside(dscroll.top.x,
		 dscroll.top.y,
		 dscroll.bot.x,
		 dscroll.bot.y))
		{
			mouse_status(stat);
			if(stat.leftButton)
			 {
						for(int i=0;i<12000;i++);
						GGHideCur(Black);
						if (w_record==w_nrecords)        //down
						 {
						 if (w_drecord<NRec)
							{
							GGUpDownGrid(DOWN);
							return 0;
							}
						 }
						else w_record += 1;
						GGShowCur(Black);
						return 0;
			 }
		}

 if(mouse_inside(ziscroll.top.x,
		 ziscroll.top.y,
		 ziscroll.bot.x,
		 ziscroll.bot.y))
		{
			mouse_status(stat);
			if(stat.leftButton)
			 {
				GGZoomInGrid();
				return 0;
			 }
		}
 if(mouse_inside(zoscroll.top.x,
		 zoscroll.top.y,
		 zoscroll.bot.x,
		 zoscroll.bot.y))
		{
			mouse_status(stat);
			if(stat.leftButton)
			 {
				GGZoomOutGrid();
				return 0;
			 }
		}
 if(mode_text)
 {
	dx = 0;
 }
 else
 {
//	settextstyle(2, 0, 0);
//	lat=textwidth(" ");
//	lung=textheight("H")+LINE_SPACE;
	dx=24;
 }
 if(mouse_inside(mscroll.top.x,
		 mscroll.top.y,
		 mscroll.bot.x,
		 mscroll.bot.y))
		{
			mouse_status(stat);
			if(stat.leftButton)
			 {
				GGSizeGrid();
				return 0;
			 }
		}
 if(mouse_inside(tx+dx,
		 ltop.y,
		 bx-dx,
		 mode_text? ltop.y:ty))
		{
			mouse_status(stat);
			if(stat.leftButton)
			 {
				GGMoveGrid(ANYWHERE);
				return 0;
				}
		}
//	lat=1;
//	lung=1;
/*	for(int i=w_urecord;i<=w_drecord;i++)
	 for(int j=w_lfield;j<=w_rfield;j++)
		if(mouse_inside(tx+(t_fields[j-1]-1)*lat,
				 ty+(i-w_urecord)*(lung),
				 tx+(t_fields[j]-1)*lat,
				 ty+(i-w_urecord)*(lung)))
				 {
					GGHideCur(Black);
					w_record = i-w_urecord+1;
					w_field = j-w_lfield+1;
					GGShowCur(Black);
					return 0;
				 }
*/
	while(!get_button_released(BLEFT,stat));
et1:

	for(int i=w_urecord;i<=w_drecord;i++)
	{
	 if(mouse_inside(tx-1, ty+(i-w_urecord+(mode_text?0:1))*(LINE_SPACE+lung_char_n),
									 tx-1, ty+(i-w_urecord+(mode_text?0:1)+(mode_text?0:1))*(LINE_SPACE+lung_char_n)))
	 {
				GGHideCur(Black);
				w_record = i-w_urecord+1;
				w_field = 1;
				GGShowCur(Black);
				esc = INSERT;
				key.ch[0]=0;
				key.ch[1]=INSERT;
				return 0;
	 }
	 for(int j=w_lfield;j<=w_rfield;j++)
		if(mouse_inside(tx+(t_fields[j-1]-(mode_text?1:0))*lat_char_n+(mode_text?0:4),
				 ty+(i-w_urecord+(mode_text?0:1))*(LINE_SPACE+lung_char_n),
				 tx+(t_fields[j]-(mode_text?1:0))*lat_char_n+(mode_text?0:4),
				 ty+(i-w_urecord+(mode_text?0:1)+(mode_text?0:1))*(LINE_SPACE+lung_char_n)))
				 {
					GGHideCur(Black);
					w_record = i-w_urecord+1;
					w_field = j-w_lfield+1;
					GGShowCur(Black);
					char doubleclick = 0;
//					while(!get_button_released(BLEFT,stat));
					long l = microsec;
					long l1 ;
					while(1)
					{
					 l1 = microsec;
					 if(l1-l >= 0)
					 {
						 if(l1-l > 130000L)
							 break;
					 }
					 else
					 {
						 if(l-l1 < 130000L)
							 break;
					 }
					 mouse_status(stat);
					 if(stat.leftButton)
					 {
						doubleclick = 1;
						break;
					 }
					}

					if(stat.leftButton)
						while(!get_button_released(BLEFT,stat));
					if( doubleclick==1 )
					{
						esc=key.ch[0]=13;
					}
//					settextstyle(DEFAULT_FONT, HORIZ_DIR,1);
					return 0;
				 }
	}
	esc = 0;
	return 0;
//	settextstyle(DEFAULT_FONT, HORIZ_DIR,1);
 }
 if(stat.rightButton)
	 {
				while(!get_button_released(BRIGHT,stat));
				esc = INSERT;
				key.ch[0]=0;
				key.ch[1]=INSERT;
				goto et1;
	 }

 return 0;
}
/*	for(int i=w_urecord;i<=w_drecord;i++)
	 for(int j=w_lfield;j<=w_rfield;j++)
		if(mouse_inside(tx+(t_fields[j-w_lfield]-1)*lat+4,
				 ty+(i-w_urecord+1)*(LINE_SPACE+lung),
				 tx+(t_fields[j+1-w_lfield]-1)*lat+4,
				 ty+(i-w_urecord+1+1)*(LINE_SPACE+lung)))
				 {
					GGHideCur(Black);
					w_record = i-w_urecord+1;
					w_field = j-w_lfield+1;
					GGShowCur(White);
					settextstyle(DEFAULT_FONT, HORIZ_DIR,1);
					return 0;
				 }
	settextstyle(DEFAULT_FONT, HORIZ_DIR,1);
 }
 return 0;
}
*/



void GGrid::GGZoomOutGrid(void)
{
//putimage(ltop.x,ltop.y,under1,COPY_PUT);
//farfree(under1);
//on_screen=0;
GReleaseWindow();
inltop.x=ltop.x;inltop.y=ltop.y;inrbottom.x=rbottom.x;inrbottom.y=rbottom.y;
if(mode_text)
	{ltop.x=1;ltop.y=3;rbottom.x=78;rbottom.y=20;}
else
	{ltop.x=10;ltop.y=30;rbottom.x=630;rbottom.y=450;}

GWSet("Program",Lightgray,Darkgray);

GShowGrid();
}

void GGrid::GGZoomInGrid(void)
{
GReleaseWindow();
ltop.x=inltop.x;ltop.y=inltop.y;rbottom.x=inrbottom.x;rbottom.y=inrbottom.y;
GWSet("Program",Lightgray,Darkgray);
GShowGrid();
}
/*
void GGrid::GGLeftGrid(void)
{
 int x,y,col;
 int lx,ly,rx,ry;
 lx = ltop.x; ly=ltop.y;rx=rbottom.x;ry=rbottom.y;
 GTestMove(LEFT,&lx,&ly,&rx,&ry);
 if (lx == ltop.x)
		return;
 GReleaseWindow();
 ltop.x = lx;
 GWSet("Program",Lightgray,DARKGRAY);
 GShowGrid();
}
*/
void GGrid::GGUpDownGrid(int where)
{
//	char far *under,*u1,*u2,*u3,*u4,*uu1,*uu2,*uu3,*uu4;
//	struct textsettingstype texttypeinfo;
//	int lx,ly,rx,ry,col,x,y;
	int col,x,y,flag,put_record,del_record,ow_field;
	MouseStatus stat;
	GGHideCur(Black);
	hide_pointer();
	get_button_released(BRIGHT,stat);
	get_button_released(BLEFT,stat);
	mouse_motion(&x,&y);
	get_button_pressed(BLEFT,stat);
	get_button_released(BLEFT,stat);

	ow_field=w_field;
	w_field =1;

//	if(mode_text)
//	{
//	 lat=1;
//	 lung=1;
//	}
//	else
//	{
//	col = getcolor();
//	settextstyle(2, 0, 0);
//	lat=textwidth(" ");
//	lung=textheight("H")+LINE_SPACE;
//	}
	if(!mode_text)
		col = getcolor();

		switch (where) {
		case UP:
				if (w_urecord>1)
				{
				 del_record = w_urecord;
				 w_urecord -= 1;
				 put_record = w_urecord;
				 w_drecord -= 1;
				 w_record = 1;
				 if(mode_text)
				 {
				 window(tx,ty,bx,by);
				 mgotoxy(tx,ty);
				 insline();
				 window(1,1,80,25);
//				 mtextcolor(Black);
				 }
				 else
					{
					 move_screen(tx,ty+1+LINE_SPACE+(lung_char_n+LINE_SPACE), bx,ty+1+w_nrecords*(LINE_SPACE+(lung_char_n+LINE_SPACE)), DOWN, (LINE_SPACE+(lung_char_n+LINE_SPACE)));
//					 setcolor(Lightgray);
					 GGPutRecord(del_record,Lightgray,Lightgray);
//					 setcolor(col);
////					 setfillstyle(SOLID_FILL, Lightgray);
////					 bar(tx,ty+LINE_SPACE+1+lung, bx,ty+LINE_SPACE+lung+1*(LINE_SPACE+lung)-2);
					}

				 GGPutRecord(put_record,Lightgray,col);
				}
/*				else
				 if (filename==NULL)
						 if (bank!=0)
							 {
								// write_panel(tip point,bank, index_max_bank, *ptrbuffer
								send();
								bank--;
								delete obj.out;
								create_obj();
								 w_lfield = 1;
								 w_urecord = 1;
								 w_record = 1;
								 w_field = 1;
								w_field = w_lfield;
								w_nfields = 0;
								t_fields[w_field-1]=1;
								GGDrawGrid(Black);
								w_field = 1; w_record = 1;
								GGShowCur(Black);
								// display_pointer();
							 }
	*/
				break;
		case PGUP:
//					w_urecord>1 && i++<w_nrecords)
				w_urecord -= w_nrecords;
				if(w_urecord<1) w_urecord=1;
//				put_field = w_lfield;
				w_field = w_lfield;
				w_nfields = 0;
				w_field = 1;
				t_fields[w_field-1]=1;
				if(mode_text)
				{
/*
				 scrollup(tx-1,ty-1,bx-1,by-1);
				 lin_menu[bx-tx+1]=0;
				 mxyputs(tx,ty,lin_menu,colour,colour);
				 lin_menu[bx-tx+1]='Û';
*/
				}
			 else
				 {
				 setfillstyle(SOLID_FILL, Lightgray);
				 bar(tx,ty+LINE_SPACE+(lung_char_n+LINE_SPACE)+1,bx-1,by-1);
				 }
				GGDrawGrid(Black);
				GGHideCur(Black);
				w_record = 1;
				w_field = 1;
				break;
		case DOWN:
				if (w_drecord<NRec)
				{
				 w_urecord += 1;
				 del_record = w_drecord;
				 w_drecord += 1;
				 put_record = w_drecord;
				 w_record = w_nrecords;
				 GWGoto(w_nrecords,1);
				 if(mode_text)
				 {
					 scrollup(tx-1,ty-1,bx-1,by-1, (bkgcolour<<4)+bkgcolour);
				 }
				 else
					{
					 move_screen(tx,ty+LINE_SPACE+(lung_char_n+LINE_SPACE)+1+LINE_SPACE+(lung_char_n+LINE_SPACE),bx,by-1, UP, (LINE_SPACE+(lung_char_n+LINE_SPACE)));
					 setcolor(Lightgray);
					 GGPutRecord(del_record,Lightgray,Lightgray);
					 setcolor(col);
//					 setfillstyle(SOLID_FILL, Lightgray);
//					 bar(tx,ty+LINE_SPACE+lung+1+(w_nrecords-1)*(LINE_SPACE+lung), bx,ty+LINE_SPACE+lung+w_nrecords*(LINE_SPACE+lung)-2);
					}

				 GGPutRecord(put_record,Lightgray,col);
				}
/*				else
				 if (filename==NULL)
						 if (bank!=max_bank)
							 {
								// write_panel(tip point,bank, index_max_bank, *ptrbuffer
								send();
								bank++;
								delete obj.out;
								create_obj();
								 w_lfield = 1;
								 w_urecord = 1;
								 w_record = 1;
								 w_field = 1;
								w_field = w_lfield;
								w_nfields = 0;
								t_fields[w_field-1]=1;
								GGDrawGrid(Black);
								w_field = 1; w_record = 1;
								GGShowCur(Black);
								// display_pointer();
							 }
*/
				break;
		case PGDN:
//					w_urecord>1 && i++<w_nrecords)
				w_drecord += w_nrecords;
				if(w_drecord>NRec) w_urecord = NRec-w_nrecords;
				else 	w_urecord += w_nrecords;

//				put_field = w_lfield;
				w_field = w_lfield;
				w_nfields = 0;
				w_field = 1;
				t_fields[w_field-1]=1;
				if(mode_text)
				{
				 scrollup(tx-1,ty-1,bx-1,by-1, (bkgcolour<<4)+bkgcolour);
				}
			 else
				 {
				 setfillstyle(SOLID_FILL, Lightgray);
				 bar(tx,ty+LINE_SPACE+(lung_char_n+LINE_SPACE)+1,bx-1,by-1);
				 }
				GGDrawGrid(Black);
				GGHideCur(Black);
				w_record = 1;
				w_field = 1;
				break;
	 }
	display_pointer();

// GReleaseWindow();
// ltop.x=lx;ltop.y=ly;rbottom.x=rx;rbottom.y=ry;
// GWSet("Program",Lightgray,DARKGRAY);
// GShowGrid();
//	display_pointer();
	get_button_pressed(BLEFT,stat);
	get_button_released(BLEFT,stat);
	w_field=ow_field;
	GGShowCur(Black);
}

void GGrid::GGLeftRightGrid(int where)
{
//	int lx,ly,rx,ry;
	int col,x,y,n,m,i,n1,lung;
	int flag,put_field,del_field;
	int ow_record, ow_field;
	MouseStatus stat;
	ow_record = w_record; ow_field = w_field;
	GGHideCur(Black);
	hide_pointer();

	get_button_released(BRIGHT,stat);
	get_button_released(BLEFT,stat);
	mouse_motion(&x,&y);
	get_button_pressed(BRIGHT,stat);
	get_button_pressed(BLEFT,stat);

 if(mode_text)
 {
 lung = 1;
 }
 else
 {
 settextstyle(SMALL_FONT, 0, 5);
 lung = textheight("H")+LINE_SPACE;
 }

	if (where == LEFT)
		{
		// max w_rfield
		n=max(strlen(rtrim(FFldName(fh, obj, w_rfield-1+1))),FFldSize(fh, obj, w_rfield-1+1));
		// max next field
		n1=max(strlen(rtrim(FFldName(fh, obj, w_rfield+1))),FFldSize(fh, obj, w_rfield+1))+1;
		i=w_lfield;
		m = t_fields[i]-1;
		while(( t_fields[w_rfield]-t_fields[i]+n1 ) > (bx-tx+1)/lat_char_n )
								m = t_fields[++i]-1;
		}


		switch (where) {
		case ENDKEY:
					if(w_field == w_rfield-w_lfield+1 && w_rfield == fields_number) break;
		case LEFT:
/*
				if(mode_text)
				{
				mmovetext(tx+t_fields[i]-1,ty-1,bx,by,tx,ty-1);
				w_lfield = i+1;
				w_field = put_field = w_rfield-(i+1)+2;
				count_fields();
				window(tx+t_fields[w_lfield+w_field-1-1]-1,ty,bx,by);
				mtextbackground(colour);
				mclrscr();
				window(1,1,80,25);
				mtextcolor(fcolour);
				mgotoxy(tx+t_fields[w_lfield+w_field-1-1]-1,ty-1);
				for(i=tx+t_fields[w_lfield+w_field-1-1]-1;i<bx;i++)
					mputch('Û');
				mtextcolor(Black);
				}
				else
				{
				 move_screen(tx+(t_fields[i]-1)*lat,ty-1,bx,by, LEFT, (t_fields[i]-1)*lat);
				w_lfield = i+1;
				w_field = put_field = w_rfield-(i+1)+2;
				count_fields();
				}
				w_nfields = w_field-1;
				GGDrawGrid(Black);
				GGHideCur(Black);
				w_field = w_rfield-w_lfield+1;
*/
				if(where == ENDKEY)
				{
				 w_lfield = 1;
				 count_fields();
				 if(w_rfield != fields_number)
					 if(point_type == OUT)
						w_lfield = 2;
					 else
						w_lfield = 4;
				 else
				 {
					GGHideCur(Black);
					w_field = w_rfield-w_lfield+1;
					break;
				 }
				}
				else
				{
				 w_rfield += 1;
				 if(w_rfield > fields_number)
						w_lfield = 1;
				 else
						w_lfield++;
				}
				if(mode_text)
				{
				 mclrscr(tx,ty,bx,by,bkgcolour);
				 mclrscr(tx,ty-1,bx,ty-1,header_bkgcolour);
				}
				else
				{
				 setfillstyle(SOLID_FILL, Lightgray);
				 bar(tx+1,ty+1+LINE_SPACE+lung,bx-1,by-1);
				 setfillstyle(SOLID_FILL, Cyan);
				 bar(tx,ty+1,bx-1,ty-1+LINE_SPACE+lung);
				}

//				w_nfields = w_field-1;
//				GGDrawGrid(Black);
//				GGHideCur(Black);
//				w_field = w_rfield-w_lfield+1;
				w_field = 1;
				count_fields();
				w_field = w_lfield;
				w_nfields = 0;
				w_field = 1;
				t_fields[w_field-1]=1;
				GGDrawGrid(Black);
				GGHideCur(Black);
				w_field = w_rfield-w_lfield+1;
				break;
		case HOME:
				if(w_lfield == 1 && w_field == 1) break;
		case RIGHT:
				if(where==HOME)
				{
				 if(w_rfield-w_lfield+1 == fields_number)
				 {
					w_field = 1;
					break;
				 }
				 else
					 w_lfield = 1;
				}
				else
				{
				 w_lfield -= 1;
//				 put_field = w_lfield;
				}
				if(mode_text)
				{
				 mclrscr(tx,ty,bx,by,bkgcolour);
				 mclrscr(tx,ty-1,bx,ty-1,header_bkgcolour);
				}
				else
				{
				 setfillstyle(SOLID_FILL, Lightgray);
				 bar(tx,ty+1+LINE_SPACE+lung,bx-1,by-1);
				 setfillstyle(SOLID_FILL, Cyan);
				 bar(tx,ty+1,bx-1,ty-1+LINE_SPACE+lung);
				}

				w_field = 1;
				count_fields();
				w_field = w_lfield;
				w_nfields = 0;
				w_field = 1;
				t_fields[w_field-1]=1;
				GGDrawGrid(Black);
				GGHideCur(Black);
				w_field = 1;
				break;
/*				alloc_mem(tx+1,ty+1,tx+1+(t_fields[i-1])*lat,by, &u1,&u2,&u3,&u4, &flag);

				w_field = 1;
				setcolor(Cyan);
				GWPuts(0,t_fields[w_lfield-1],rtrim((char *)recstruct[w_lfield-1].field_name));

				del_field = w_lfield;
				w_lfield -= 1;
				put_field = w_lfield;
				w_rfield -= 1;
				w_field = 1;
				t_fields[w_lfield] =t_fields[w_rfield-1]+max(mstrlen(rtrim((char *)recstruct[w_rfield].field_name)),recstruct[w_rfield].l)+1;

				GGPutCol1(1,Lightgray);
				put_image(tx+1+(t_fields[w_lfield])*lat,ty+1, tx++(t_fields[i-1]+t_fields[w_lfield])*lat,by, &u1, &u2, &u3,&u4, &flag);
				del_field = w_rfield;
				w_rfield += 1;
				put_field = w_rfield;
				w_lfield = i+1;
				w_field = w_nfields;
				t_fields[w_rfield] =t_fields[w_rfield-1]+max(mstrlen(rtrim((char *)recstruct[w_rfield].field_name)),recstruct[w_rfield].l)+1;
*/
	 }
	display_pointer();

// GReleaseWindow();
// ltop.x=lx;ltop.y=ly;rbottom.x=rx;rbottom.y=ry;
// GWSet("Program",Lightgray,DARKGRAY);
// GShowGrid();
//	display_pointer();
	get_button_pressed(BLEFT,stat);
	get_button_released(BLEFT,stat);
	display_pointer();
//	w_record = 1; w_field = 1;
	w_nfields = w_rfield-w_lfield+1;
	w_record = ow_record;
	GGShowCur(Black);
}

void GGrid::GGSizeGrid(void)
{
//	char far *under,*u1,*u2,*u3,*u4,*uu1,*uu2,*uu3,*uu4;
	MouseStatus stat;
	int x,y,col,dx,dy;
 int lx,ly,rx,ry;
 lx = ltop.x; ly=ltop.y;rx=rbottom.x;ry=rbottom.y;
 if(mode_text)
	 GTestMove(SIZE,&lx,&ly,&rx,&ry);
 else
		Graphic_GTestMove(SIZE,&lx,&ly,&rx,&ry);

 GReleaseWindow();
 ltop.x=lx;ltop.y=ly;rbottom.x=rx;rbottom.y=ry;
 GWSet("Program",Lightgray,Darkgray);
 GShowGrid();
 display_pointer();
}

void GGrid::GGMoveGrid(int where)
{
//	char far *under,*u1,*u2,*u3,*u4,*uu1,*uu2,*uu3,*uu4;
	int lx,ly,rx,ry;
	MouseStatus stat;
	int x,y,col,dx,dy;
	hide_pointer();
	lx = ltop.x; ly=ltop.y;rx=rbottom.x;ry=rbottom.y;
	display_pointer();
	if(mode_text)
		GTestMove(where,&lx,&ly,&rx,&ry);
	else
		Graphic_GTestMove(where,&lx,&ly,&rx,&ry);
	hide_pointer();

/*	uint big1= imagesize(ltop.x,ltop.y,rbottom.x,rbottom.y)+4;
	if( (under=(char far *) farmalloc((unsigned long)big1))==NULL )
		 {
			 DisplayError("ERROR IN MEM ALLOCATION3");
			 exit(0);
		 }
	getimage(ltop.x,ltop.y,rbottom.x,rbottom.y,under);
//	putimage(ltop.x, ltop.y, under, XOR_PUT);
//	putimage(ltop.x, ltop.y, under1, COPY_PUT);
	putimage(ltop.x, ltop.y, under1, COPY_PUT);
	farfree(under1);
	ltop.x = lx; ltop.y = ly;
	rbottom.x = rx; rbottom.y = ry;
	big1= imagesize(ltop.x,ltop.y,rbottom.x,rbottom.y)+4;
	if( (under1=(char far *) farmalloc((unsigned long)big1))==NULL )
		 {
			 DisplayError("ERROR IN MEM ALLOCATION2");
			 exit(0);
		 }
	getimage(ltop.x,ltop.y,rbottom.x,rbottom.y,under1);
	putimage(ltop.x, ltop.y, under, COPY_PUT);
	farfree(under);
	tx=ltop.x+3;
	ty=ltop.y+textheight(title)+16;
//  bx=rbottom.x;
	dx=dy=24;
	bx=rbottom.x-dx;
//	by=rbottom.y-3;
	by=rbottom.y-3-dy;

	close_spot.top.x=tx;
	close_spot.top.y=ltop.y;
	close_spot.bot.x=tx+dx;
	close_spot.bot.y=ty;

	lscroll.top.x=tx;
	lscroll.top.y=by;
	lscroll.bot.x=tx+dx;
	lscroll.bot.y=rbottom.y-3;

	rscroll.top.x=bx-dx;
	rscroll.top.y=by;
	rscroll.bot.x=bx;
	rscroll.bot.y=rbottom.y-3;

	uscroll.top.x=bx;
	uscroll.top.y=ty;
	uscroll.bot.x=rbottom.x;
	uscroll.bot.y=ty+dy;

	dscroll.top.x=bx;
	dscroll.top.y=by-dy;
	dscroll.bot.x=rbottom.x;
	dscroll.bot.y=by;

	ziscroll.top.x=bx;
	ziscroll.top.y=ltop.y;
	ziscroll.bot.x=rbottom.x;
	ziscroll.bot.y=ty;

	zoscroll.top.x=bx-dx;
	zoscroll.top.y=ltop.y;
	zoscroll.bot.x=bx;
	zoscroll.bot.y=ty;

	mscroll.top.x=bx;
	mscroll.top.y=by;
	mscroll.bot.x=rbottom.x;
	mscroll.bot.y=rbottom.y;
*/

GReleaseWindow();
	ltop.x = lx; ltop.y = ly;
	rbottom.x = rx; rbottom.y = ry;
GWSet(NULL,Lightgray,Darkgray);
GShowGrid();

 display_pointer();
}






char *rtrim(char *text)
{
	int n,i;
	n=strlen(text);
	for (i=n-1;i>=0;i--)
			if (text[i]!=' ')
					break;
	text[i+1]='\0';
	return text;
}

void GGrid::GTestMove(int where,int *plx,int *ply,int *prx,int *pry)
{
//	char far *under;
//	uint big1,big;
	MouseStatus stat;
	MouseStatus s;
	int x,y,col,dx,dy;
	hide_pointer();
//	int lat,lung;
	int lx,ly,rx,ry,llx,lly,rrx,rry;
	lx=*plx;ly=*ply;rx=*prx;ry=*pry;
	get_button_released(BRIGHT,stat);
	get_button_released(BLEFT,stat);
//	getlinesettings(lineinfo);
/*
	mtextcolor(White);
	mtextbackground(White);

	 big = (rx-lx+1)*(ry-ly+1)*2;
	 mfarmalloc((char far **)&under , (unsigned long)big);
	 if( under==NULL )
	 {
//		DisplayError("ERROR IN MEM ALLOCATION");
		exit(0);
		}

	mgettext(lx, ly, rx, ry,under);
*/
	mouse_motion(&x,&y);
	mouse_status(s);
	int cx=s.where.x;
	int cy=s.where.y;
	while(!get_button_released(BLEFT,stat))
	 {
		mouse_status(s);
//		mouse_motion(&x,&y);
		x = s.where.x-cx;
		y = s.where.y-cy;

		if (x!=0 || y!=0)
		{
		cx=s.where.x;
		cy=s.where.y;

		llx=lx;lly=ly;rrx=rx;rry=ry;

/*
		if (where==ANYWHERE)
		{
		 mputtext(lx,
			 ly,
			rx,
			ry,under1);
		 mfarfree( under1 );
		}
*/
		switch (where) {
/*
		case ANYWHERE:
				lx += x; ly += y ; rx += x ; ry += y;
				if (lx <= 0) {	rx = rx-lx+1;lx=1; }
				if (rx >= 79) {	lx = lx-(rx-79)-1;rx=79-1; }
				if (ly <= 0) {	ry = ry-ly+1;ly=1; }
				if (ry > 24) {	ly = ly-(ry-24)-1;ry=24-1; }
	 big1 = (rx-lx+1)*(ry-ly+1)*2;
	 if( (under1=(char far *)farmalloc((unsigned long)big1))==NULL )
	 {
//		DisplayError("ERROR IN MEM ALLOCATION");
		exit(0);
		}

	gettext(lx,
		 ly,
		 rx,
		 ry,under1);

	puttext(lx,
		 ly,
		 rx,
		 ry,under);


//	movetext(llx,lly,rrx,rry,lx,ly);
				break;
*/
		case ANYWHERE:
				lx += x; ly += y ; rx += x ; ry += y;
				if (lx <= 0) {	rx = rx-lx+1;lx=1; }
				if (rx >= 80) {	lx = lx-(rx-80)-1;rx=80-1; }
				if (ly <= 0) {	ry = ry-ly+1;ly=1; }
				if (ry > 24) {	ly = ly-(ry-24)-1;ry=24-1; }
				break;
		case SIZE:
				lx += 0; ly += 0 ; rx += x ; ry += y;
				if (rx >= 80)  rx=80-1;
				if (rx < lx+17) rx=lx+17;
				if (ry > 24)   ry=24-1;
				if (ry < ly+3) ry=ly+3;
				break;
/*
		case RIGHT:
				if (x < 0)
					 break;
				lx += 0; ly += 0 ; rx += x ; ry += 0;
				if (lx <= 0) {	rx = rx-lx+1;lx=1; }
				if (rx >= getmaxx()) {	lx = lx-(rx-getmaxx())-1;rx=getmaxx()-1; }
				if (ly <= 0) {	ry = ry-ly+1;ly=1; }
				if (ry > getmaxy()) {	ly = ly-(ry-getmaxy())-1;ry=getmaxy()-1; }
				break;
		case LEFT:
				if (x > 0)
					 break;
				lx += x; ly += 0 ; rx += 0 ; ry += 0;
				if (lx <= 0) {	rx = rx-lx+1;lx=1; }
				if (rx >= getmaxx()) {	lx = lx-(rx-getmaxx())-1;rx=getmaxx()-1; }
				if (ly <= 0) {	ry = ry-ly+1;ly=1; }
				if (ry > getmaxy()) {	ly = ly-(ry-getmaxy())-1;ry=getmaxy()-1; }
				break;
		case UP:
				if (y > 0)
					 break;
				lx += 0; ly += y/2 ; rx += 0 ; ry += 0;
				if (lx <= 0) {	rx = rx-lx+1;lx=1; }
				if (rx >= getmaxx()) {	lx = lx-(rx-getmaxx())-1;rx=getmaxx()-1; }
				if (ly <= 0) {	ry = ry-ly+1;ly=1; }
				if (ry > getmaxy()) {	ly = ly-(ry-getmaxy())-1;ry=getmaxy()-1; }
				break;
		case DOWN:
				if (y < 0)
					 break;
				lx += 0; ly += 0 ; rx += 0 ; ry += y/2;
				if (lx <= 0) {	rx = rx-lx+1;lx=1; }
				if (rx >= getmaxx()) {	lx = lx-(rx-getmaxx())-1;rx=getmaxx()-1; }
				if (ly <= 0) {	ry = ry-ly+1;ly=1; }
				if (ry > getmaxy()) {	ly = ly-(ry-getmaxy())-1;ry=getmaxy()-1; }
				break;
*/
		 }
			 if(mode_text && where == ANYWHERE)
			 {
				 char *buf;
				 HANDLE h;
				 mfarmalloc((char far **)&buf , (unsigned long)(rbottom.x-ltop.x+1)*(rbottom.y-ltop.y+1)*2, h);
				 if( buf!=NULL )
				 {
					hide_pointer();
					mgettext(ltop.x,ltop.y,rbottom.x,rbottom.y,buf);
					RestoreArea();
					ltop.x=lx;ltop.y=ly;rbottom.x=rx;rbottom.y=ry;
					SaveArea();
					hide_pointer();
					mputtext(ltop.x,ltop.y,rbottom.x,rbottom.y, buf);
					display_pointer();
					mfarfree(h);
				 }
			 }
			 else
			 {
				GReleaseWindow();
				ltop.x=lx;ltop.y=ly;rbottom.x=rx;rbottom.y=ry;
				GWSet(NULL,Lightgray,Darkgray);
				GShowGrid();
			 }
	 }
	}

	mouse_motion(&x,&y);
	get_button_pressed(BLEFT,stat);
	get_button_released(BLEFT,stat);
	*plx=lx;*ply=ly;*prx=rx;*pry=ry;
	display_pointer();
 }



void GGrid::Graphic_GTestMove(int where,int *plx,int *ply,int *prx,int *pry)
{
	char far *under,*u1,*u2,*u3,*u4,*uu1,*uu2,*uu3,*uu4;
	uint big1,big2;
	MouseStatus stat;
	int x,y,col,dx,dy;
	struct linesettingstype far *lineinfo;
//	getlinesettings(lineinfo);
	hide_pointer();
	int lx,ly,rx,ry;
	lx=*plx;ly=*ply;rx=*prx;ry=*pry;
	get_button_released(BRIGHT,stat);
	get_button_released(BLEFT,stat);
//	getlinesettings(lineinfo);
	col = getcolor();
	setlinestyle(DOTTED_LINE,0xff,1);
  line_style=DOTTED;
	setcolor(White);

//	lx = ltop.x; ly=ltop.y;rx=rbottom.x;ry=rbottom.y;
//	big1= imagesize(lx,ly,rx,ly);
//	big2= imagesize(rx,ly+1,rx,ry-1);

	big1=1024;      //641;
	big2=1024;      //481;

	u1=(char far *) farmalloc((unsigned long)big1);
//	big2= imagesize(rx,ly+1,rx,ry-1);
	u2=(char far *) farmalloc((unsigned long)big2);
//	big1= imagesize(lx,ry,rx,ry);
	u3=(char far *) farmalloc((unsigned long)big1);
//	big2= imagesize(lx,ly+1,lx,ry-1);
	u4=(char far *) farmalloc((unsigned long)big2);
//	uu1=(char far *) farmalloc((unsigned long)big1);
//	uu2=(char far *) farmalloc((unsigned long)big2);
//	uu3=(char far *) farmalloc((unsigned long)big1);
//	uu4=(char far *) farmalloc((unsigned long)big2);
//	if (u1==NULL || u2==NULL ||u3==NULL ||u4==NULL||uu1==NULL || uu2==NULL ||uu3==NULL ||uu4==NULL)
	if ( u1==NULL || u2==NULL ||u3==NULL ||u4==NULL )
	{
    return;
	}
	mgetimage_10(lx,ly,rx,ly,u1);
	mgetimage_10(rx,ly+1,rx,ry-1,u2);
	mgetimage_10(lx,ry,rx,ry,u3);
	mgetimage_10(lx,ly+1,lx,ry-1,u4);

//	putimage(lx,ly,u1,XOR_PUT);
//	putimage(rx,ly+1,u2,XOR_PUT);
//	putimage(lx,ry,u3,XOR_PUT);
//	putimage(lx,ly+1,u4,XOR_PUT);

	prectangle(lx,ly,rx,ry,Black);

//	mgetimage_10(lx,ly,rx,ly,uu1);
//	mgetimage_10(rx,ly+1,rx,ry-1,uu2);
//	mgetimage_10(lx,ry,rx,ry,uu3);
//	mgetimage_10(lx,ly+1,lx,ry-1,uu4);

	mouse_motion(&x,&y);
	while(!get_button_released(BLEFT,stat))
	 {
		mouse_motion(&x,&y);

//		putimage(lx,ly,uu1,XOR_PUT);
//		putimage(rx,ly+1,uu2,XOR_PUT);
//		putimage(lx,ry,uu3,XOR_PUT);
//		putimage(lx,ly+1,uu4,XOR_PUT);

		mputimage_10(lx,ly,rx,ly,u1);
		mputimage_10(rx,ly+1,rx,ry-1,u2);
		mputimage_10(lx,ry,rx,ry,u3);
		mputimage_10(lx,ly+1,lx,ry-1,u4);
//		mputimage_10(lx,ly,u1,COPY_PUT);
//		mputimage_10(rx,ly+1,u2,COPY_PUT);
//		mputimage_10(lx,ry,u3,COPY_PUT);
//		mputimage_10(lx,ly+1,u4,COPY_PUT);

		switch (where) {
		case ANYWHERE:
				lx += x; ly += y/2 ; rx += x ; ry += y/2;
				if (lx <= 0) {	rx = rx-lx+1;lx=1; }
				if (rx >= getmaxx()) {	lx = lx-(rx-getmaxx())-1;rx=getmaxx()-1; }
				if (ly <= 0) {	ry = ry-ly+1;ly=1; }
				if (ry > getmaxy()) {	ly = ly-(ry-getmaxy())-1;ry=getmaxy()-1; }
				break;
		case SIZE:
				lx += 0; ly += 0 ; rx += x ; ry += y/2;
				if (lx <= 0) {	rx = rx-lx+1;lx=1; }
				if (rx >= getmaxx()) {	lx = lx-(rx-getmaxx())-1;rx=getmaxx()-1; }
				if (ly <= 0) {	ry = ry-ly+1;ly=1; }
				if (ry > getmaxy()) {	ly = ly-(ry-getmaxy())-1;ry=getmaxy()-1; }
				break;
/*
		case RIGHT:
				if (x < 0)
					 break;
				lx += 0; ly += 0 ; rx += x ; ry += 0;
				if (lx <= 0) {	rx = rx-lx+1;lx=1; }
				if (rx >= getmaxx()) {	lx = lx-(rx-getmaxx())-1;rx=getmaxx()-1; }
				if (ly <= 0) {	ry = ry-ly+1;ly=1; }
				if (ry > getmaxy()) {	ly = ly-(ry-getmaxy())-1;ry=getmaxy()-1; }
				break;
		case LEFT:
				if (x > 0)
					 break;
				lx += x; ly += 0 ; rx += 0 ; ry += 0;
				if (lx <= 0) {	rx = rx-lx+1;lx=1; }
				if (rx >= getmaxx()) {	lx = lx-(rx-getmaxx())-1;rx=getmaxx()-1; }
				if (ly <= 0) {	ry = ry-ly+1;ly=1; }
				if (ry > getmaxy()) {	ly = ly-(ry-getmaxy())-1;ry=getmaxy()-1; }
				break;
		case UP:
				if (y > 0)
					 break;
				lx += 0; ly += y/2 ; rx += 0 ; ry += 0;
				if (lx <= 0) {	rx = rx-lx+1;lx=1; }
				if (rx >= getmaxx()) {	lx = lx-(rx-getmaxx())-1;rx=getmaxx()-1; }
				if (ly <= 0) {	ry = ry-ly+1;ly=1; }
				if (ry > getmaxy()) {	ly = ly-(ry-getmaxy())-1;ry=getmaxy()-1; }
				break;
		case DOWN:
				if (y < 0)
					 break;
				lx += 0; ly += 0 ; rx += 0 ; ry += y/2;
				if (lx <= 0) {	rx = rx-lx+1;lx=1; }
				if (rx >= getmaxx()) {	lx = lx-(rx-getmaxx())-1;rx=getmaxx()-1; }
				if (ly <= 0) {	ry = ry-ly+1;ly=1; }
				if (ry > getmaxy()) {	ly = ly-(ry-getmaxy())-1;ry=getmaxy()-1; }
				break;
*/
	 }

//	farfree(u1);farfree(u2);farfree(u3);farfree(u4);
//	farfree(uu1);farfree(uu2);farfree(uu3);farfree(uu4);
//	big1= imagesize(lx,ly,rx,ly);
//	big2= imagesize(rx,ly+1,rx,ry-1);
//	u1=(char far *) farmalloc((unsigned long)big1);
//	u2=(char far *) farmalloc((unsigned long)big2);
//	u3=(char far *) farmalloc((unsigned long)big1);
//	u4=(char far *) farmalloc((unsigned long)big2);
//	uu1=(char far *) farmalloc((unsigned long)big1);
//	uu2=(char far *) farmalloc((unsigned long)big2);
//	uu3=(char far *) farmalloc((unsigned long)big1);
//	uu4=(char far *) farmalloc((unsigned long)big2);
//	if (u1==NULL || u2==NULL ||u3==NULL ||u4==NULL||uu1==NULL || uu2==NULL ||uu3==NULL ||uu4==NULL)
//		 {
//			 DisplayError("ERROR IN MEM ALLOCATION1");
//			 exit(0);
//		 }
		mgetimage_10(lx,ly,rx,ly,u1);
		mgetimage_10(rx,ly+1,rx,ry-1,u2);
		mgetimage_10(lx,ry,rx,ry,u3);
		mgetimage_10(lx,ly+1,lx,ry-1,u4);

//		putimage(lx,ly,u1,XOR_PUT);
//		putimage(rx,ly+1,u2,XOR_PUT);
//		putimage(lx,ry,u3,XOR_PUT);
//		putimage(lx,ly+1,u4,XOR_PUT);

		prectangle(lx,ly,rx,ry,Black);

//		getimage(lx,ly,rx,ly,uu1);
//		getimage(rx,ly+1,rx,ry-1,uu2);
//		getimage(lx,ry,rx,ry,uu3);
//		getimage(lx,ly+1,lx,ry-1,uu4);

	 }
//	putimage(lx,ly,uu1,XOR_PUT);
//	putimage(rx,ly+1,uu2,XOR_PUT);
//	putimage(lx,ry,uu3,XOR_PUT);
//	putimage(lx,ly+1,uu4,XOR_PUT);

		mputimage_10(lx,ly,rx,ly,u1);
		mputimage_10(rx,ly+1,rx,ry-1,u2);
		mputimage_10(lx,ry,rx,ry,u3);
		mputimage_10(lx,ly+1,lx,ry-1,u4);
//	putimage(lx,ly,u1,COPY_PUT);
//	putimage(rx,ly+1,u2,COPY_PUT);
//	putimage(lx,ry,u3,COPY_PUT);
//	putimage(lx,ly+1,u4,COPY_PUT);

	farfree(u1);farfree(u2);farfree(u3);farfree(u4);
//	farfree(uu1);farfree(uu2);farfree(uu3);farfree(uu4);
//	setlinestyle(lineinfo->linestyle,lineinfo->upattern,lineinfo->thickness);
	setcolor(col);

	mouse_motion(&x,&y);
	get_button_pressed(BLEFT,stat);
	get_button_released(BLEFT,stat);
	*plx=lx;*ply=ly;*prx=rx;*pry=ry;
	line_style=FILL;
	display_pointer();
 }


void scrollup(int topx, int topy, int endx, int endy, char attr)
{
// union REGS r;
 asm {
	push ax
  push bx
  push cx
  push dx
  mov ah, 6
  mov al, 1
  mov ch, BYTE PTR topy
  mov cl, BYTE PTR topx
  mov dh, BYTE PTR endy
  mov dl, BYTE PTR endx
  mov bh, BYTE PTR attr
  int 10h
  pop dx
  pop cx
  pop bx
  pop ax
 }
/*
 r.h.ah = 6;
 r.h.al = 1;
 r.h.ch = topy;
 r.h.cl = topx;
 r.h.dh = endy;
 r.h.dl = endx;
 r.h.bh = attr;
 int86(0x10, &r, &r);
*/
}

void GGrid::count_fields(void)
{
 int i,l,l1;
 i=w_lfield-1;
 l = 0;
 l1=max(strlen(rtrim(FFldName(fh, obj, i+1))),FFldSize(fh, obj, i+1));
 w_nfields = 0;
 while (mode_text ? (l+l1<=(bx-tx+1)/lat_char_n) : (l+l1<=(bx-tx-2-COL_SPACE)/lat_char_n))
 {
		w_nfields++;
		t_fields[i]=l+1;
		l=l+l1+SPACE_CHAR;
		i++;
		if(i == fields_number) break;
		l1=max(strlen(rtrim(FFldName(fh, obj, i+1))),FFldSize(fh, obj, i+1));
 }
// t_fields[i]=l+1;
 t_fields[i]=mode_text ? l+1 : l ;
 w_rfield = i;
}


void GGrid::change_bank(int how)
{
 GWDialog *p;
			 if (filename[0]==0)
					{
					 if ((how==UP) && (bank!=0) )
								{
								 if(modify)    // && descriptor)
									{
									 GSend();
 //									 send();
 //									 ptr_panel->Burke_control(1, WRITE, (char *)obj.out);
/*									 switch (point_type) {
											case OUT:
														 ptr_panel->outputs=obj.out;
														 ptr_panel->Outputs(WRITE);
														 break;
											case IN:
														 ptr_panel->inputs=obj.in;
														 ptr_panel->Inputs(WRITE);
														 break;
											case VAR:
														 ptr_panel->vars=obj.var;
														 ptr_panel->Variable(WRITE);
														 break;
											case CON:
														 ptr_panel->controllers=obj.con;
														 ptr_panel->Controllers(WRITE);
														 break;
											case WR:
														 ptr_panel->weekly_routines=obj.wr;
														 ptr_panel->Weekly_Routines(WRITE);
														 break;
											case WR_TIME:
														 ptr_panel->wr_times=obj.wr_time;
														 ptr_panel->Weekly_Routine_Times(WRITE,obj.wr_time->routine_num-1);
														 break;
											case AR:
														 ptr_panel->annual_routines=obj.ar;
														 ptr_panel->Annual_Routines(WRITE);
														 break;
											case AR_Y:
//														 ptr_panel->ar_dates=obj.ar_y;
//														 ptr_panel->Annual_Routine_Dates(WRITE,obj.ar_y->routine_num);
														 break;
											case PRG:
														 ptr_panel->programs=obj.prg;
														 ptr_panel->Programs(WRITE);
														 break;
											}
*/
//									 DeleteMessage(pm);
//			savedes();
//									 p=DisplayMessage("Sending...");
//									 send();
//									 DeleteMessage(p);
									}
									bank--;
								}
					 else
						 if ((how==DOWN) && (bank!=max_bank) )
							 {
								 if(modify )      //&& descriptor)
									{
									 GSend();
 //									 ptr_panel->Burke_control(1, WRITE, (char *)obj.out);
/*									 switch (point_type) {
											case OUT:
														 ptr_panel->outputs=obj.out;
														 ptr_panel->Outputs(WRITE);
														 break;
											case IN:
														 ptr_panel->inputs=obj.in;
														 ptr_panel->Inputs(WRITE);
														 break;
											case VAR:
														 ptr_panel->vars=obj.var;
														 ptr_panel->Variable(WRITE);
														 break;
											case CON:
														 ptr_panel->controllers=obj.con;
														 ptr_panel->Controllers(WRITE);
														 break;
											case WR:
														 ptr_panel->weekly_routines=obj.wr;
														 ptr_panel->Weekly_Routines(WRITE);
														 break;
											case WR_TIME:
														 ptr_panel->wr_times=obj.wr_time;
														 ptr_panel->Weekly_Routine_Times(WRITE,obj.wr_time->routine_num-1);
														 break;
											case AR:
														 ptr_panel->annual_routines=obj.ar;
														 ptr_panel->Annual_Routines(WRITE);
														 break;
											case AR_Y:
//														 ptr_panel->ar_dates=obj.ar_y;
//														 ptr_panel->Annual_Routine_Dates(WRITE,obj.ar_y->routine_num);
														 break;
											case PRG:
														 ptr_panel->programs=obj.prg;
														 ptr_panel->Programs(WRITE);
														 break;
											}
*/
//									 send();
									}
									bank++;
							 }
						 else
								return;
					modify=FALSE;
					// write_panel(tip point,bank, index_max_bank, *ptrbuffer
					delete obj.out;
					create_obj();
//					w_lfield = 1;
					w_urecord = 1;
					w_record = 1;
					w_field = 1;
					w_nfields = 0;
//					t_fields[w_field-1]=1;
					GGDrawGrid(Black);
					w_field = 1; w_record = 1;
					GGShowCur(Black);
					// display_pointer();
				}
}






void move_screen(int sx, int sy, int jx, int jy, int where, int size)
{
 uint big1,big2,big3,big4;
 char *under1;
 HANDLE under1_handle;
 // settextstyle(2, 0, 0);
// int lat=textwidth(" ");
// int lung=textheight("H")+LINE_SPACE;
 int l=4;
 int n=(jy-sy+1)/(l*size);
 int r=(jy-sy+1)%(l*size);
// char vline[640];
 switch (where){
 case UP:
	{

	 if(extended_memory)
	 {
/*
			hide_pointer();    // hides the mouse cursor during reading
			XmsMem *pXms = new XmsMem;
			pXms->Save(sx,sy+size, jx, jy);
			if(pXms->status==1)
			 {
				pXms->Restore(sx, sy, jx, jy-size);
				if(pXms) delete pXms;
				display_pointer(); //displays the mouse cursor after
				break;
			 }
			else
				 if(pXms) delete pXms;
*/
	 ;
	 }

/*
 for(int ii=sy;ii+size<jy;ii += size)
 {
	float f= ((float)((unsigned long)(jx-sx)*(unsigned long)(ii+size-ii)*4))/8/3;
	mfarmalloc((char far **)&under1, (unsigned long)f);
	if (under1==NULL )
	 {
		DisplayError("ERROR IN MEM ALLOCATION");
		exit(0);
		}

	mmgetimage(sx, ii, jx, ii+size,(signed char **)&under1);
	mmputimage(sx,  ii-size,  jx,	 ii,(signed char *)under1);
	mfarfree(under1);
 }
	float f= ((float)((unsigned long)(jx-sx)*(unsigned long)(r)*4))/8/DIVIMAGE;
	mfarmalloc((char far **)&under1, (unsigned long)f);
	if (under1==NULL )
	 {
		DisplayError("ERROR IN MEM ALLOCATION");
		exit(0);
		}

	mmgetimage(sx, jy-r, jx, jy,(signed char **)&under1);
	mmputimage(sx,  jy-r-size,  jx,	 jy-r,(signed char *)under1);
	mfarfree(under1);
*/
	big1 = mimagesize(sx, sy, jx, sy+l*size)+1000;
	mfarmalloc((char far **)&under1, (unsigned long)big1 , under1_handle	);
	if( under1==NULL )
	{
		DisplayError("ERROR IN MEM ALLOCATION");
		exit(0);
	}
 for(int ii=sy;ii+l*size<jy;ii += l*size)
 {
/*
	big1 = imagesize(sx, ii, jx, ii+l*size);
	if( (under1=(char far *)farmalloc((unsigned long)big1))==NULL )
	 {
		DisplayError("ERROR IN MEM ALLOCATION");
		exit(0);
		}
*/
	getimage(sx, ii, jx, ii+l*size, under1);
	putimage(sx,ii-size,under1,COPY_PUT);
//	mfarfree(under1);
 }
	getimage(sx, jy-r, jx, jy, under1);
	putimage(sx,jy-r-size,under1,COPY_PUT);
	mfarfree(under1_handle);
  }
 break;
 case DOWN:
 {
	big1 = mimagesize(sx, jy-l*size, jx, jy)+1000;
	mfarmalloc((char far **)&under1, (unsigned long)big1 , under1_handle	);
	if( under1==NULL )
	 {
		DisplayError("ERROR IN MEM ALLOCATION");
		exit(0);
		}
 for(int ii=jy;ii-l*size>sy;ii -= l*size)
 {
	mgetimage(sx, ii-l*size, jx, ii, under1);
	mputimage(sx,ii-(l-1)*size,under1,COPY_PUT);
 }
	mgetimage(sx, sy, jx, sy+(l-1)*size, under1);
	mputimage(sx,sy+size,under1,COPY_PUT);
	mfarfree(under1_handle);
 break;
 }
 case LEFT:
/* for( ii=sx;ii+40<jx;ii += 40)
 {
	big1 = imagesize(ii, sy, ii+40,jy);
	if( (under1=(char far *)farmalloc((unsigned long)big1))==NULL )
	 {
		DisplayError("ERROR IN MEM ALLOCATION");
		exit(0);
		}
	getimage(ii, sy, ii+40, jy, under1);
	putimage(ii-size,sy,under1,COPY_PUT);
	mfarfree(under1);
 }
	big1 = imagesize(jx-r, sy, jx, jy);
	if( (under1=(char far *)farmalloc((unsigned long)big1))==NULL )
	 {
		DisplayError("ERROR IN MEM ALLOCATION");
		exit(0);
		}
	getimage(jx-r, sy, jx, jy, under1);
	putimage(jx-r-size,sy,under1,COPY_PUT);
	mfarfree(under1);
*/
 l=2;
 int ssize=40;
 big1 = mimagesize(sx, sy, jx, sy+ssize)+1000;
 mfarmalloc((char far **)&under1, (unsigned long)big1 , under1_handle	);
 if( under1==NULL )
	 {
		DisplayError("ERROR IN MEM ALLOCATION");
		exit(0);
		}
 for(int ii=sy;ii+ssize<jy;ii += ssize)
 {
//	big1 = imagesize(sx, ii, jx, ii+ssize);
//	if( (under1=(char far *)farmalloc((unsigned long)big1))==NULL )
//	 {
//		DisplayError("ERROR IN MEM ALLOCATION");
//		exit(0);
//		}
	mgetimage(sx, ii, jx, ii+ssize, under1);
	mputimage(sx-size,ii,under1,COPY_PUT);
//	mfarfree(under1);
 }
	mgetimage(sx, jy-r, jx, jy, under1);
	mputimage(sx-size,jy-r,under1,COPY_PUT);
	mfarfree(under1_handle);
 break;
 }

}


void msettextstyle(int font, int dir, int chars)
{
	set_semaphore(&screen);
	settextstyle(font, dir, chars);
	font_type=font; charsize=chars;
	lat_char_n = textwidth(" ");
	lung_char_n = textheight("H");
	clear_semaphore(&screen);
}

