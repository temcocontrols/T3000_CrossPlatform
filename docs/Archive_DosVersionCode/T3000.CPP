/*************************************************************
*
* Defines:  PANELSTATION;
*						SERIAL_COMM;
*						NETWORK_COMM;
*           CONTROL;
*           MEMORY_1M
*
**************************************************************/
#define MAIN
#define MOUSE_TEXT

#include <conio.h>
#include <dos.h>
#include <process.h>
#include <dir.h>
#include <graphics.h>
#include <sys\stat.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#include <windows.h>
#include "t3000def.h"
#include "baseclas.h"
#include "gwin.h"
#include "mouse.h"
#include "gmbar.h"
//#include "mask.h"
#include "ggrid.h"
#include "gedit.h"
#include "recstruc.h"
#include "serial.h"
#include "mtkernel.h"
#include "parser.h"
#include <display.hpp>
//#include "netbios.h"
#include "net_bac.h"
#include "netb_bac.h"
#include "ipx.h"
#include "tifcodec.hpp"
#include "imgviewr.hpp"
#include "rs485.h"
#include "ptp.h"
#include "t3000hlp.h"

#define min(a,b)    (((a) < (b)) ? (a) : (b))

#define EGAVGA 9
#define ESC 27

/* next lines moved to gmbar.h
#define M0 0
#define M1 10
#define M2 20
#define M3 30
#define M4 40
#define M5 50
#define M6 60
*/

#define CNF_VER             0
#define CNF_RESERVED        CNF_VER+2
#define CNF_STATION_NUM     CNF_RESERVED+10
#define CNF_STATION_NAME    CNF_STATION_NUM+2
#define CNF_NETWORK_NUMBER  CNF_STATION_NAME+16
#define CNF_NR_BOARDS       CNF_NETWORK_NUMBER+2+16
#define CNF_SIZE_BOARD_INFO CNF_NR_BOARDS+2
#define CNF_BOARD           CNF_SIZE_BOARD_INFO+2
#define CNF_SIZE_COMM_INFO  CNF_BOARD+MAX_BOARDS*sizeof(Board_info)
#define CNF_COMM_INFO       CNF_SIZE_COMM_INFO+2
#define CNF_IPX_enabled     CNF_COMM_INFO+MAX_COMM_INFO*sizeof(Comm_Info)
#define CNF_MODEM           CNF_IPX_enabled+1
#define CNF_PROGRAM_PATH  CNF_MODEM+sizeof(ModemCapabilities)
#define CNF_PROGRAM_DES   CNF_PROGRAM_PATH+64
#define CNF_PROGRAM_BASIC CNF_PROGRAM_DES+64
#define CNF_PROGRAM_MONITOR  CNF_PROGRAM_BASIC+64
#define CNF_PROGRAM_GRAPHICS CNF_PROGRAM_MONITOR+64
#define CNF_DEFAULT_PROGRAM  CNF_PROGRAM_GRAPHICS+64
#define CNF_CONSOLE          CNF_DEFAULT_PROGRAM+13
#define CNF_RINGS            CNF_CONSOLE+1
#define CNF_STATION_LIST     CNF_RINGS+1
#define CNF_IND_PASS         CNF_STATION_LIST+MAX_STATIONS*sizeof(Station_point)
#define CNF_IORATE_OFF       CNF_IND_PASS+sizeof(Password_point)*MAX_PASSW

//#define CNF_MODEM_12         CNF_COMM_INFO+3*sizeof(Comm_Info)
//#define CNF_PROGRAM_PATH_12  CNF_MODEM_12+sizeof(ModemCapabilities)
//#define CNF_STATION_LIST_12  CNF_PROGRAM_PATH_12+5*64+13+1+1

#define MAX_INPUT_BUFFER 2000

extern int netstatus_show(void);
extern int checkpointpresence(int num_point,int point_type,int num_panel,int num_net, int panel, int network);
extern int checkmaxpoints(int num_point,int point_type,int num_panel,int num_net);
extern void desinstalled(void);
extern int findroutingentry(int port, int network, int &j, int t=1);
extern int pointtotext(char *buf,Point_Net *point);
extern int height_char_size(void);
extern int width_char_size(void);
extern unsigned int CalcDataCRC(unsigned char dataValue, unsigned int crcValue);
extern int checkport(int com, int t=0);
extern int readdes_serial(void);
extern int tif(char *argv,int x1, int x2, int y1,int y2);
extern void msettextstyle(int font, int dir, int chars);
extern void reset_PIC_mask(byte PIC_mask);
extern int install_port(int com=-1);
extern int dialog_select(int n_entry, char *arraytext, int save, int x, int y, int bkgnd, int tbkgnd, char *title=NULL, char col=10);
extern void result_ser(RS232Error result, int rs485=0);
extern int netcall(BACnetPDU pdutype, int service, int network, int dest, char *data, int *length , int command, int arg,  int sign=0);
extern struct remote_local_list  remote_local_list[MAXREMOTEPOINTS];
//extern int ind_remote_local_list;
extern REMOTE_POINTS  _far remote_points_list[MAXREMOTEPOINTS82];
extern char remote_points_OUT;
//extern WANT_POINTS  	   want_points_list[MAXREMOTEPOINTS];

extern char IPX_enabled;
extern char enable_ints;
extern int select_tmp;
extern char printAlarms;
extern int ipxport, rs485port;

struct input_buffer {
		unsigned time;
		union {
			int   i;
			char  key[2];
			} key;
		};

extern struct input_buffer inp_buffer[11];
extern struct input_buffer *input_buffer;//[MAX_INPUT_BUFFER];
extern int ind_input_buffer;
extern int def_macro;
extern char check_annual_routine_flag;
extern char huge *pressanykey;

struct input_buffer *ptr_input_buffer;
icon *points_icon;

int pixvar;

int Black=BLACK;                 //0
int Blue=BLUE;                   //1
int Green=LIGHTBLUE;                 //2
int Cyan=CYAN;                   //3
int Red=RED;                     //4
int Green1=WHITE; 						 //5
int Blue1=DARKGRAY;                 //6
int Lightgray=LIGHTGRAY;         //7

int Darkgray=BROWN;           //8
int Lightblue=GREEN;         //9
int Lightgreen=LIGHTGREEN;       //10
int Lightcyan=LIGHTCYAN;         //11
int Lightred=LIGHTRED;           //12
int Lightmagenta=LIGHTMAGENTA;   //13
int Yellow=YELLOW;               //14
int White=MAGENTA;                 //15
int Brown;
int Magenta;

int Overscan=Black;

void changechar(int arg=0);
void restorechar(int arg=0);
int setmousetext(void);
int setregister(int set);
extern int localnetwork(int net);


extern char _far sendtime, sendtime_ipx;
extern char month_days[12];
extern rgb *grp_current_pal;
extern char int_disk1;
extern int i_files;
extern char far Icon_name_table[MAX_ICON_NAME_TABLE][14];
//extern char ind_object_t, ind_object_d;
#ifdef NETWORK_COMM
extern OPERATOR_LIST operator_list;
extern byte panels_number;
extern NETBIOS_Presence	Netbios_state;
extern USERS_RECORD	user;
extern DIRECT_POINT_RECORD	direct_point;
extern Netbios *pnet;
extern int NET_EXIT;
#endif

#ifdef NET_BAC_COMM
extern NetBios_Bac *pnet;
extern IPX         *pipx;
extern int NET_EXIT;
#endif

extern char far NetworkName[16];
extern int time_run_MSTP;
extern long timesave;
extern int mouse_inst;
extern char display_amons;
extern int setvectint8;
extern int communication, int_dos;
extern int dontch;
extern int prg_active;
extern char test_tiff;
extern Time_block ora_current;
extern struct  time ora_start;         // ora la inceputul programului
extern unsigned long  ora_current_sec; // ora curenta exprimata in secunde
extern int milisec;
extern long microsec;
extern char updatedtime;

extern int ISA_uarts[4];
extern ModemCapabilities ModemDataBase[1];
//extern Serial  *ser_rs485;
Serial *ser_ptr;
extern int SERIAL_EXIT;
extern Dial_list_point dial_list_data;
extern  int error_net;
extern byte 	number_of_sessions;
extern char null_buf[10];
extern char huge *default_string;
extern Point_Net localopenscreen;
extern int network_select, panel_select, network_sel_tmp, panel_sel_tmp;
extern ulong *pactivepanels;
extern Station_point *pstation_list_sel;
extern long galarm_read_time;
extern char *updatebuffer;

char _far tempbuf[65];
char control;
char printamon;

byte ser_sessions[2] = { 0, 0};
char far com_buf[10][5] = {"N/A ", "COM1", "COM2", "COM3", "COM4",
										 "com5", "com6", "com7", "com8",
										 "bus"};
char huge connection_type_text[9][14] = {"Not Installed",
														"SerialRS232  ",
														"Modem        ",
														"RS485        ",
														"Asyncron mode",
														"Ipx/Spx      ",
														"TCP/IP       ",
														"Netbios      ",
														"Mouse        "};
char huge tables_text[5][10]={{" Table 1 "},{" Table 2 "},{" Table 3 "},{" Table 4 "},{" Table 5 "}};
char huge *autodetect="Auto Detect";
char huge *ctrlbreak_text="    CTRL/Break - Interrupt";
char huge *ok_button    =" < OK > ";
char huge *cancel_button="<Cancel>";
char huge *exit_button    =" <eXit> ";
char huge *noexit_button  ="<No exit>";
char huge *version ="2.59";    // May 14, 19998
int Version = 259;    //2.56
int cnf_version;

char huge *loadpanel_text ="Load panel ";
char huge *savepanel_text ="Save panel ";
char huge *renamefile_text ="Rename file ";
char huge *deletefile_text ="Delete file ";
char huge *rebootm = " The panel is saving it's PRG into the Flash memory.         It will take about 30 seconds.";
char *saveprgflashtxt = " The program was not saved in the Flash memory!";
char _far *panel_text1="PANEL ";
char _far *wait_text = " Wait ...";
char huge *signature = "!@#$";

Password_struct passwords;
char Password[9];
char User_name[16];
char password[9];
char user_name[16];
char access_level;
unsigned long rights_access;
char default_group;
char screen_right[2*((MAX_GRPS%8)?MAX_GRPS/8+1:MAX_GRPS/8)];
char program_right[2*((MAX_PRGS%8)?MAX_PRGS/8+1:MAX_PRGS/8)];
char right_access;
char default_prg[13];
char remote_path[65];
char huge array_sel_path[][11]={{"Common    "},{"Separate  "}};
/*
char program_path[64];
char descriptor_path[64];
char basic_path[64];
char monitor_path[64];
char graphics_path[64];
*/

//int connection_established = 0;
//Comm_Info  comm_info[4] = { { COM0, ILLEGAL_IRQ, 19200 }, { COM0, ILLEGAL_IRQ, 2400 }, {COM0, ILLEGAL_IRQ, 19200 }, { COM2, IRQ3, 0 } };
Comm_Info huge c_info[MAX_COMM_INFO] = { { COM1, IRQ4, 38400, 0 }, { COM2, IRQ3, 38400, 0 }, {COM3, IRQ4, 38400 }, {COM4, IRQ3, 38400, 0 },
													 { COM5, IRQ4, 38400, 0 }, { COM6, IRQ3, 38400, 0 }, {COM7, IRQ4, 38400 }, {COM8, IRQ3, 38400, 0 },
													 { COM0, ILLEGAL_IRQ, 0, MOUSE_LINK } };
Comm_Info *comm_info;

byte modem_present = 0;
byte modem_active = 0;
byte console_mode;
byte number_rings=1;
char keyboard_data;

char _far netoperation[MAX_STATIONS];
Station_point station_list[MAX_STATIONS];
int ind_station;
char station_name[NAME_SIZE];
int  station_num;

Panel_info1 Panel_Info1,panel_info1;
unsigned long Active_Panels;
char Panel_Type = T3000;
char Station_NAME[NAME_SIZE]="PANEL1";
int  Station_NUM=1;

char read_inputs_rate;
char write_outputs_rate;

int local_panel;
int simulator;
int start_apl=0;
int nr_boards=1,nnr_boards;
int grid_record_number;
int entry_selected;
char main_screen;

int extended_memory;
XmsDes *Des;
int maxx;
int maxy;

Str_array_point huge arights[14] =
					 {{"Outs",R_READ_ONLY},{"Ins",R_READ_ONLY},{"Vars",R_READ_ONLY},{"Cons",R_READ_ONLY},
						{"Wrs",R_READ_ONLY},{"Ars",R_READ_ONLY},{"Prgs",R_READ_ONLY},{"Tables",R_READ_ONLY},
						{"Dmons",R_READ_ONLY},{"Amons",R_READ_ONLY},{"Screens",R_READ_ONLY},{"Arrays",R_READ_ONLY},
						{"Config",R_READ_ONLY},{"File op",R_READ_ONLY}};
char arights_grid;

char GAlarm, gAlarm;
char GAlarmold;
int alarm_time;
int alarm_col;
char alarm_beep;
int exit_apl = 0;
int logout;
int qtt;
//char huge supervisor[]="TEMCO";
char huge supervisor[]="TRAVEL";

int ex_apl=1;
char LOADPRG, loadprgremote;
static FILE *h;

Point_Net nested_grp[MAX_NEST_GRP];
int ind_nested_grp;
Point_Net current_opened_grp;

//char timebuf[9];
//char datebuf[9];

Board_info	boards[MAX_BOARDS]={256,1,7372,200, 250, 0,0,0,0,0,0,0};
FILEHANDLE syslist_handle;

union seg_sel {
 unsigned long l;
 struct {
	unsigned sel;
	unsigned seg;
 } seg_sel;
} seg_sel;
rgb init_pal[16];
unsigned ega_selector;

char EGA_data_block[30];
char *SAVE_PTR;
char text_auxiliary[13];

//char huge text_auxiliary[13];
//char *SAVE_PTR;
//char huge EGA_data_block[30];
char far characters_font[] =
			{
			 0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,     // ³ left
			 0x80,0x80,0x80,0x80,0x80,0x80,

//			 0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,     // ³ left-1
//			 0x40,0x40,0x40,0x40,0x40,0x40,
			 0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,     // ³ left-1
			 0x60,0x60,0x60,0x60,0x60,0x60,

			 0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,    // ³ right
			 0x01,0x01,0x01,0x01,0x01,0x01,

			 0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,    // ³ right-1
			 0x02,0x02,0x02,0x02,0x02,0x02,

			 0x0ff,0,0,0,0,0,0,0,0,0,                        // Ä  up
			 0,0,0,0,0,0,

			 0,0x0ff,0,0,0,0,0,0,0,0,                        // Ä  up-1
			 0,0,0,0,0,0,

			 0,0,0,0,0,0,0,0,0,0,                        // Ä dn
			 0,0,0,0,0,0x0ff,


			 0,0,0,0,0,0,0,0,0,0,                        // Ä dn-1
			 0,0,0,0,0x0ff,0,

			 0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,       //  laterale
			 0x81,0x81,0x81,0x81,0x81,0x81,

			 0x0,0,0xff,0,0,0,0,0,0,0,                                 // sus-jos
			 0,0,0,0,0,0xff,

			 0xff,0x80,0x80,0x80,0x80,0x80,0x9f,0x9f,0x9f,0x80,       //  exit
			 0x80,0x80,0x80,0x80,0x80,0xff,

			 0xff,0x01,0x01,0x01,0x01,0x01,0xf9,0xf9,0xf9,0x01,       //  exit
			 0x01,0x01,0x01,0x01,0x01,0xff,


			0,0,0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0xfa,0x98,
			0x18,0x0c,0x0c,0x0,0x0,0,

			 0xff,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,     // ³ left top
			 0x80,0x80,0x80,0x80,0x80,0x80,

			 0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,     // ³ left bottom
			 0x80,0x80,0x80,0x80,0x80,0xff,

			 0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,    // ³ right bottom
			 0x01,0x01,0x01,0x01,0x01,0xff,

			 0xff,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,    // ³ right bottom
			 0x01,0x01,0x01,0x01,0x01,0x01,

			 0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xf8,0x0,0x0,      // Ù;
			 0x0,0x0,0x0,0x0,0x0,0x0,

			 0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0x18,0x18,0x18,      // Ú
			 0x18,0x18,0x18,0x18,0x18,

			 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,     //Û
			 0xff,0xff,0xff,0xff,0xff,0xff,

			 0x0,0x7f,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,     // ³ left-1 top
			 0x60,0x60,0x60,0x60,0x60,0x60,

			 0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,     // ³ left-1 bottom
			 0x60,0x60,0x60,0x60,0x7f,0x0,

			 0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,    // ³ right-1 bottom
			 0x06,0x06,0x06,0x06,0xfe,0x0,

			 0x0,0xfe,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,    // ³ right-1 top
			 0x06,0x06,0x06,0x06,0x06,0x06,

//			 0xff,0x81,0x81,0x81,0x89,0x9d,0xbe,0xff,0x99,0x99,            // arrow up
//			 0x99,0x99,0x81,0x81,0x81,0xff,


			 0xff,0x81,0x81,0x81,0x99,0xbd,0x7e,0xff,0x99,0x99,            // arrow up
			 0x99,0x99,0x81,0x81,0x81,0xff,

			 0xff,0x81,0x81,0x81,0x99,0x99,0x99,0x99,0xff,0xbe,            // arrow down
			 0x9d,0x89,0x081,0x81,0x81,0xff,

			 0x0,0x0,0xff,0x80,0x82,0x86,0x8e,0x9e,0xbf,0xbf,0x9e,            // arrow left1
			 0x8e,0x86,0x82,0x80,0xff,

			 0x0,0x0,0xff,0x01,0x01,0x01,0x01,0x01,0xf1,0xf1,0x01,            // arrow left2
			 0x01,0x01,0x01,0x01,0xff,

			 0x0,0x0,0xff,0x80,0x80,0x80,0x80,0x80,0x8f,0x8f,0x80,            // arrow left2
			 0x80,0x80,0x80,0x80,0xff,

			 0x0,0x0,0xff,0x01,0x41,0x61,0x71,0x79,0xfd,0xfd,0x79,            // arrow down2
			 0x71,0x61,0x41,0x01,0xff,

			 80,0,0,0,0,0,0,0,0,0,                        // . left-top
			 0,0,0,0,0,0,

			 0,0,0,0,0,0,0,0,0,0,                        // . left-bottom
			 0,0,0,0,0,80,

			 0,0,0,0,0,0,0,0,0,0,                        // . right-bottom
			 0,0,0,0,0,1,

			 1,0,0,0,0,0,0,0,0,0,                        // . right-top
			 0,0,0,0,0,0,

			};


//extern "C" int changechar(void);
//extern int restorechar(void);

//extern char buffer[4096];

//#define stack_PROJ_SIZE 7000U
//extern unsigned _stklen = 12288U;         //  12288U;

#define MODE_TEXT 1
#define MODE_GRAPHIC 0
#define TEXT_FOND_COLOR White

char huge *lin_read ="±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±";
//char *lin_text="ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ";
char huge *lin_text  ="                                                                                 ";
char huge *prg_text  ="*.PRG";
//char iconf[4]={0x0f,0x0f,0x0f,0x0f};
//char oconf[4]={0x0f0,0x0f0,0x0f0,0x0f0};

extern signed char point_des[AY+1];
//extern char huge h_amon[];
//extern char huge *heap_amon;

extern Pshape ARROW;
extern char huge *blank;
extern char huge *na;
extern char huge *on;
extern char huge *off;

extern int maxx;
extern int maxy;
extern char text;
extern int mode_text;
extern int mode_graph;
int fond_color;

extern char simulate;
extern int lat_char_n;
extern int lung_char_n;
extern int font_type,charsize;
extern char blocked1;


	union key {
		int i;
		char ch[2];
		} ;

//extern unsigned _stklen = stack_PROJ_SIZE;         //  12288U;

extern HANDLE heap_buf_handle, heap_grp_handle, heap_amon_handle;
extern HANDLE heap_dmon_handle, heap_array_handle;
extern unsigned int MAX_HEAP_BUF, MAX_HEAP_GRP, MAX_HEAP_AMON, MAX_HEAP_ARRAY;
extern unsigned int MAX_HEAP_DIGM;
//extern long huge *heap_array;
//extern char huge *heap_buf;
//extern char huge *heap_grp;
//extern char huge *heap_amon;
//extern Heap_dmon huge *heap_dmon;
extern long *heap_array;
extern char *heap_buf;
extern char *heap_grp;
extern char *heap_amon;
extern Heap_dmon *heap_dmon;
//extern long huge heap_array[];
//extern char huge heap_buf[];
//extern char huge heap_grp[];
//extern char huge heap_amon[];
//extern struct heap_dmon huge heap_dmon[];
extern char huge *estab_text;
extern char far  *panelmis;
extern char far  *pointins;

extern int nsample_mem_dig;
extern unsigned first_free;

extern char just_load;
extern char onemin;

extern char huge *lin_menu;
extern char huge *lin_hor;
extern char huge *lin_ver;

extern int dxscreen, dyscreen;

extern char point_cod[MAX_TBL_BANK][5];

extern Str_tbl_point custom_tab[MAX_TABS];

extern dig_range_form huge dig_range_array[];
//extern range_form huge range_array[MAX_RANGE];

extern struct {
	char name[5];
	int cod_point;
	int point_type;
	int size;
	} points_cod[12];


byte cod_command[AY+1]={M2+3,M2+2,24,25,26,27,21,M3+1,0,M3+0,20,28};

char maxtbl;
char interface_mode;
char oldpath[65];
int oldrive;
int refresh_time_init=150;
int refresh;
unsigned long t;
int refresh_time;
unsigned long grp_time;
unsigned long display_grp_time;
char present_analog_monitor, save_prg_flag;
extern char save_monitor;
extern char save_monitor_command;
extern unsigned long timesec1970;
extern unsigned long timestart;
extern unsigned long ind_heap_buf;
extern unsigned long ind_heap_grp;
extern int disconnect_time;

//int xcur_grp[10],ycur_grp[10]; // x=1; y=23
//char ind_xcur, ind_ycur;
int programs_size;
byte serial_access = 0;
byte serial_panel_type;
Panel_info1 serial_panel_info1;
int exec_program(char *prog);
void About(void);

extern int netstat_show(void); 
extern void set16( rgb * pal, int nclrs );
extern int texttointerval( char *textbuffer,char *seconds , char *minutes , char *hours, char c=':' );
extern uint search_point( Point &point, char *buff, char * & point_adr,
																		uint & point_length, Search_type order );
extern int local_request(int panel, int network);
extern int local_request(int panel);
extern unsigned int countlength(int command, int arg);
extern int grp_proc(int current_point, byte panel, int network, int call_type, GGrid *pgrid = NULL);
extern void infoscreen(void);
extern void resetop(void);
extern void saveoldprg(char *fname,char type=2);
extern void init_boards_struct( void );
extern void save_m(void);
extern void exit_proj(void);
void  getkey(void);
extern int amon_routine(byte num_point,byte num_panel,int net,int call_type,int x,GGrid *pgrid);
extern int fnc_group(Control_group_point *block,int current_point,GGrid *pgrid,int call_type,int panel,int display, int *retpoint);
extern int	repeat_grp(void);
extern void annual_routine(int current_point,int panel,int network,int type);
extern void weekly_routine(int current_point,int panel,int network,int type);
extern int edit_program(Str_program_point *block, int current_point, int station, int network);
extern char *ispoint(char *token,int *num_point,byte *var_type, byte *point_type, int *num_panel, int *num_net, int network=0, byte panel=0, int *netpresent=0);
extern int net_call(int command, int arg,  char *data, uint *length , int dest,
				 int network, int others=0, int timeout=TIMEOUT_NETCALL,
				 char *returnargs=NULL, int *length_returnargs=NULL,
				 char *sendargs=NULL, int length_sendargs=0, char bytearg=0, int port=-1);
extern void adjust_readtime( Time_block *time_buf );
extern void adjust_writetime(Time_block *time_buf, Time_block_mini *timemini);
extern void memsize(void);
extern void chbkg(int lx, int ly, int width, int bkgnd, int frgnd, int unchangecol=127, int height = 0);
extern char *lalign(char *buf, int n);
extern void ftoa(float f, int length, int ndec, char *buf);
//extern char huge *Heap_alloc(int bytes);
//extern int Heap_dealloc(char huge **old);
extern char *Heap_alloc(int bytes);
extern int Heap_dealloc(char **old);
extern char huge *Heap_grp_alloc(int bytes);
extern void initanalogmon(void);
extern int print_alarm_word(void);
extern char *rtrim(char *text);
extern void upcustomunit(Units_element	*punits);
extern char * intervaltotext(char *textbuf, long seconds , unsigned minutes , unsigned hours, char *c=":");
extern void DisplayMessage(int lx, int ly, int rx, int ry, char *title, char *message, GWindow **Er1, int fcolor=Black, GWindow *Er2=NULL, long delay=0);
extern void DisplayMessageT(int lx, int ly, int rx, int ry, char *title, char *message, GWindow **Er1, int fcolor=Black, GWindow *Er2=NULL, long delay=0);
extern void DeleteMessage(GWindow *p);
extern char wingets(char far *ptr, int row, int col, int width,
				 int bkgnd, int frgnd, char which_type='A', char *sablon=NULL, char retnokey=0);
//extern void load_icon( char *fn, TIFFIMAGEDEF *idef, TiffDecoder  *tifd, char **pcx_buf );
//extern void load_icon( char *fn, struct icon huge *ptr_icon);
extern void Border(int ltopx, int ltopy, int rbottomx, int rbottomy, int colour,int bcolour);

void DisplayError(int lx, int ly, int rx, int ry, char *message,int bkgnd, int frgnd, int tbkgnd, int fcolor=Black);
int ReadYesNoButton(int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							int bkgndrreadcolor, int readcolor, char *text, char *yes, char *no,
							char okchar='O', char cancelchar='C', char xok=3, char xcancel=1);
extern int ReadYesNo(int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							int bkgndrreadcolor, int readcolor, char *text, char yes='Y', char no='N', char s=0);
extern int ReadWindow(int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							 int bkgndreadcolor, int readcolor, char *text, char *buf, int width, char *sablon=NULL);
void Bordergr(int ltopx, int ltopy, int rbottomx, int rbottomy, int colour, int bkgnd, int bcolour,int butcol, int how, int out);
int	saveloadpoint(int type, int point_type, int n_points, int size, int panel, int panel_type, FILE *h, char *buf);
int comman_line(int lx, int ly, int rx, int ry, int fond_color, GEdit *edit=NULL);
void pfarfree(HANDLE handle);
void clear_color(int lx, int length, int ly, int ry, char *lin_text, int bkgnd, int frgnd);
void terminal_mode(void);
void updatetimevars(void);
int check_access(int ptype, int num=-1, int mes=R_NA);
int minioperations(void);
int savenetwork(void);
int mini_operations(Panel_info1 *panel_info, char *fname=NULL, int arg=0);

void save_config(int what);

extern void pdate(GWDialog *D);
extern void ptime(GWDialog *D);

void select_panel(int type, int net_no, int where=0);
void filetransfer_routine(void);
void creategauge(GWindow **gauge, char *buf);
void deletegauge(GWindow **gauge);
void showgauge(GWindow *w, float coef, long ntot);
void wait(long sec);
void mouseint(void);
int get_access(int ex=0);
void disconnect_serial(int d=0);

void PutCheckBox(int lx, int ly, char *string, int fondcolor, int bkgnd, int frgnd);
void CheckBox(int lx, int ly, int bkgnd, int frgnd);
void UnCheckBox(int lx, int ly, int bkgnd, int frgnd);
extern void boardconfig(void);
extern void miniconfig(void);
void mouseport(GWDialog *D);
void mport(GWDialog *D);
void sport(GWDialog *D);
void mouseirq(GWDialog *D);
void mirq(GWDialog *D);
void sirq(GWDialog *D);
void mouserate(GWDialog *D);
void mrate(GWDialog *D);
void srate(GWDialog *D);
void adetect(GWDialog *D);
void portconfig(void);
void pmodemconfigdefault(GWDialog *D);

void setup(void);
void hardware(void);

////////////////////////////////
//
//  print function
//
#define DELAY_TIME 3000
#define LINE_A4 64
#define PORTNUM 0   //select printport
#define STATUS_PRINT  0   // prints char in abyte
#define STATUS_INIT  i   // prints char in abyte
#define STATUS_READ   2   // reads the printer status
FILE *fpp; // pointer to printer
int PRINTFLAG=0; // status :  1 - print   0 - display  when show amon
int pprint(void);
int countline(FILE *s);
int sendtoprint(void);
int status_printer(void);
int headprint(void);
int footprint(int total_page_number, int number_of_page);
int printpoint(int man, int Panel_type, int Panel, int Network, int arg=0,int flag=0);
//int number_points[20];

extern int basicprogram1( char *source, char *code, Str_program_point *prg,
					int currentprogram, int panel, int network);

int print_basic(int l, byte *s);
void controlbasicSource(void);
int syslistprint( void );

///////////

GWDialog *pm;
//extern GPopUp PPtab[11];
			 char array_access_level[] = {
/*
									0x03,0x03,0x03,0x01,0x03,0x03,0x03,0x03,0x03,0x03,
									0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
									0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
									0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
									0x03,0x03,0x03,0x01,0x01,0x03,0x03,0x03,0x03,0x03,
									0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
									0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03
*/
									0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,
									0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,
									0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,
									0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,
									0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,
									0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,
									0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F
									};

			 int  listonscreen[10] = {0x50,0x01,0,0,0x05};
			 char huge *graphic_grp_message[]={{"~Group Elements"},{"~Refresh time"},{"e~Xit"},0};
			 char huge *grp_message[]={{"~Load"},{"~Send"},{"~Edit"},{"e~Xit"},0};
			 char huge *panel_message[]={{"~Load"},{"~Save"},{"~Rename"},{"~Erase"},{"E~xit"},0};
			 char huge *message[]={{"  ~Miscellaneous   "},{"  ~Panel  "},{"  ~Control  "},{"  ~Data   "},{"  Con~Figuration  "},0};
			 char huge *list1[]={
								{"~Connect"},
								{"~Disconnect"},
								{"~About      "},
//								{"~Prg->Dbf   "},
//								{"~Dbf->Prg   "},
//								{"~Run Demo"},
								{"~Network status"},
								{"~File Transfer"},
								{"l~Oad descriptors"},
//								{"~Mini operations"},
								{"~Update mini"},
///////////////////////
// print menu add here
								{"~Print.....ctrl-P"},
////////////////////
								{"e~Xit.......Alt-X"},
								{"~Logout.....Alt-L"},0};
			 char huge *list2[]={
								{"~File"},
								{"~Select Panel"},
								{"~Print Panel"},
								{"~Clear Panel"},
								{"Sa~ve network"},0};

			 char huge *list3[]={
								{"~Screens..........Alt-S"},
								{"~Programs.........Alt-P"},
								{"~Inputs...........Alt-I"},
								{"~Outputs..........Alt-O"},
								{"~Variables........Alt-V"},
								{"~Controllers......Alt-C"},
								{"~Weekly routines..Alt-W"},
								{"~Annual routines..Alt-A"},
								{"Arra~Ys...........Alt-Y"},0};
			char huge *list4[]={
								{"~Monitors.......Alt-M"},
								{"~Tables.........Alt-T"},
								{"Custom ~units        "},
//								{"~Hi/Low alarms       "},
								{"~Alarm Log           "},
/**************************************
**********  William add  *************
********     11.19.1997  *************
**************************************/
								{"~Netstat........Alt-N"},0};
//			char huge *list5[]={
//								{"Descriptor ~Files"},
//								{"~Load descriptor All"},
//								{"L~oad descriptor One"},
//								{"~Send descriptor All"},
//								{"S~end descriptor One"},
//								{"P~rint descriptor One"},
//								{"~Print descriptor All"},0};
			 char huge *list6[]={
								{"Set~Up        "},
//								{"Panel ~Names       "},
								{"U~ser List    "},
//								{"Cust~om units      "},
								{"~Hardware     "},0};
//								{"~Graphic/Text Mode"},0};
//								{"Panel ~Configuration"},
//								{"~Communications"},
//								{"~Graphic/Text Mode"},0};
			 char huge *list7[]={
								{"~Default program"},
								{"File ~Paths"},
								{"~Time and Date"},
//								{"~Enable Ethernet"},
								{"Print ~Alarms"},
								{"~Operation mode"},0};

			 char huge *list8[]={
								{"~COM ports          "},
								{"~Panel configuration"},0};
//								{"M~odem configuration"},
//								{"~Terminal mode"},
//								{"~Mini configuration"},
//								{"~T3000 configuration"},0};
//								{"~Reset operations"},0};

			 char huge *list9[]={
								{"  ~Load    "},
								{"  ~Save    "},
								{"  ~Prg->Flash"},0};
//								{"  ~Rename  "},
//								{"  ~Erase   "},0};
//								{"  E~xit"},0};
			 char huge *list10[]={
								{"~Read File "},
								{"~Send File "},
								{"~Delete File"},
								{"~Rename File"},
								{"~Update network"},0};
			 char huge *list11[]={
								{"Send ~Data "},
								{"Send ~Code"},
								{"~Read flash"},
								{"~Erase sector"},0};
			 char huge *list12[]={
								{"~Panel "},
								{"~Network"},0};

	char huge **message_list[7]={list1,list2,list3,list4,list6};

	unsigned char tbl_bank[MAX_TBL_BANK]={
											MAX_OUTS,     //OUT
											MAX_INS,     //IN
											MAX_VARS,      //VAR
											MAX_CONS,     //CON
											MAX_WR,        //WR
											MAX_AR,          //AR
											MAX_PRGS,     //PRG
											MAX_TABS,
											32,           //DMON
											MAX_ANALM,       //AMON
											MAX_GRPS,      //GRP
											MAX_ARRAYS,
											MAX_ALARMS,
											MAX_UNITS,
											MAX_PASSW
										 };
/*
	unsigned char tbl1_bank[12]={16,     //OUT
															 16,     //IN
															 16,      //VAR
															 16,     //CON
															 16,        //WR
																8,          //AR
															 16,     //PRG
															 16,         //TBL
															 16,     //DMON
															 16,       //AMON
															 16,      //GRP
															 16};      //AY
*/
//class Panel;

/*
 char *ptitle[30]={{"Outputs"},
						{"Inputs"},
						{"Variables"},
						{"Controllers"},
						{"Weekly routines"},
						{"Anual Routines"},
						{"Programs"},
						{""},
						{"Analog Monitors"},
						{"Groups"}
						};
*/

//GGrid *wgrid[3] ;
//int ind_wgrid=-1;
GMenuBar G(1,1,80,1,Lightgray,Black,White,5,POPUPMENU,message_list,SMALL_FONT,5, 1);
//GMenuBar G(1,1,80,1,Lightgray,Black,White,5,POPUPMENU,message_list);
unsigned high_mem_block;

#define TOPPANELX 10
#define TOPPANELY 3
#define BOTPANELX 65
#define BOTPANELY 10

//GWindow w(TOPPANELX,TOPPANELY,BOTPANELX,BOTPANELY,0,0);
GWindow *gauge;

Panel *ptr_panel;

Panel::Panel(Panel &copy):Aio(copy.number_of_boards)
{
	*this = copy;
}

void Panel::operator=(const Panel &copy)
{
	if(this == &copy) return;
	Aio( copy.number_of_boards);
	strcpy(Program_Path, copy.Program_Path);
	strcpy(Descriptor_Path, copy.Descriptor_Path);
	strcpy(Basic_Path, copy.Basic_Path);
	strcpy(Monitor_Path, copy.Monitor_Path);
	strcpy(Graphics_Path, copy.Graphics_Path);
	strcpy(DataBase_Path, copy.DataBase_Path);
	strcpy(Default_Program, copy.Default_Program);
//	memset((void *)panel_name,'\0',32*20);

	GlPanel=station_num;
//	GlSub_panel=0;
	GlPanel_type = T3000;
	GlNetwork = networkaddress;
}

Panel::Panel(void) : Aio(nr_boards)
{
	start_apl=1;
	ptr_panel = this;
	strcpy(Program_Path, oldpath);
	strcpy(Descriptor_Path, oldpath);
	strcpy(Basic_Path, oldpath);
	strcpy(Monitor_Path, oldpath);
	strcpy(Graphics_Path, oldpath);
	strcpy(DataBase_Path, oldpath);
//	Program_Path[0] = Descriptor_Path[0] = Basic_Path[0] = 	Monitor_Path[0]
//	= Graphics_Path[0] = DataBase_Path[0] = 0;
   Default_Program[0] = 0;

	if( (h=fopen("config.cnf","rb+"))!=NULL)
	 {
//		 fseek(h,20+MAX_BOARDS*sizeof(Board_info)+3*sizeof(Comm_Info)+sizeof(ModemCapabilities),SEEK_SET);
		 fseek(h,CNF_PROGRAM_PATH,SEEK_SET);
		 fread(Program_Path, 64, 1, h);
		 fread(Descriptor_Path, 64, 1, h);
		 fread(Basic_Path, 64, 1, h);
		 fread(Monitor_Path, 64, 1, h);
		 fread(Graphics_Path, 64, 1, h);
		 fread(Default_Program, 13, 1, h);
		 fread(&console_mode, 1, 1, h);
		 fread(&number_rings, 1, 1, h);
		 memcpy(default_prg, Default_Program, 13);
//		mxyputs(1,2,Program_Path,Black, White);
//		mxyputs(2,2,Default_Program,Black, White);
		 fclose(h);
	 }

//	memset((void *)panel_name,'\0',32*20);

	GlPanel=station_num;
	GlNetwork=networkaddress;
	GlPanel_type = T3000;
//	display_pointer();
}

int readdes_serial(void)
{
		unsigned long activepanels;
		uint l, l1, net_length=0;
		int i,result=ERROR_COMM;
		Panel_info1 panel_info;
		GWindow *D=NULL;
		char pnr[10];

		activepanels = panel_info1.active_panels;
//		activepanels = activepanels | (1L<<(station_num-1));
		for(i=0;i<MAX_STATIONS;i++)
			if( ((activepanels&(1L<<i)) && !station_list[i].state ) || loadprgremote==i+1 )
			{
				if( (result=net_call(COMMAND_50, PANEL_INFO1_COMMAND, (char*)&panel_info, 0, i+1, networkaddress,NETCALL_RETRY))!=SUCCESS )
				 result = net_call(COMMAND_50, PANEL_INFO1_COMMAND, (char*)&panel_info, 0, i+1, networkaddress);
				if(result==SUCCESS)
				{
					station_list[i].state = 1;
					memcpy(station_list[i].name, panel_info.panel_name, sizeof(Station_NAME));
					station_list[i].des_length=panel_info.des_length;
				}
				else
				{
					 activepanels &= ~(1L<<i);
           station_list[i].state = 0;
				}
			}
    loadprgremote=0;
		l=net_length=0;
		for(i=0;i<MAX_STATIONS;i++)
//		 if( (activepanels&(1L<<i)) )
		 if( station_list[i].state )
		 {
			 net_length += station_list[i].des_length;
		 }
		set_semaphore_dos();
		if(Des)
		{
			delete Des;
			Des = 0;
		}
		if(net_length)
			Des = new XmsDes(net_length);
		clear_semaphore_dos();

		if(net_length)
		{
		 D = new GWindow(mode_text?19:200, mode_text?7:150, mode_text?61:500, mode_text?11:200, NO_STACK,0);
		 DisplayMessageT(19, 7, 59, 11, ctrlbreak_text, "Reading descriptors        ", NULL, Blue, D);
		 strcpy(pnr,panel_text1);
		 for(i=0;i<MAX_STATIONS;i++)
//			if( (activepanels&(1L<<i)) )
			if( station_list[i].state )
			{
				char b[3];
				int k=0;
				b[0] = '.'; b[1] = 0;
				if(D)
				{
				 lin_text[10]=0;
				 D->GWPuts(1, 26, lin_text, Lightblue, Black);
				 D->GWPuts(2, 16, lin_text, Lightblue, Black);
				 lin_text[10]=' ';
				 itoa(i+1, &pnr[6],10);
				 D->GWPuts(2, 16, pnr, Lightblue, Black);
				 for(int j=0;j<=AY;j++)
				 if(point_des[j]>=0)
				 {
					 Delay(100);
					 l1=0;
					 if( (result=net_call(47, j+1, Des->buffer, &l1, i+1, networkaddress))!=SUCCESS )
						result=net_call(47, j+1, Des->buffer, &l1, i+1, networkaddress);
					 if( result==SUCCESS )
					 {
						if(l+l1>net_length) break;
						l += l1;
						Des->put(i+1,j,l1);
						D->GWPuts(1, 26 + k++, b, Lightblue, Black);
					 }
					 else
						 break;
				 }
				}
			}
		}
		if(D) {DeleteMessage(D); D=NULL;}
		return result;
}

void countdeslength(void)
{
	int j;
	Point point;
	unsigned int length;
	length = search_point( point, NULL, NULL, 0, LENGTH );
	Panel_Info1.des_length = length;
	for(j=0; j<MAX_Routing_table ; j++)
	{
//		if( (Routing_table[j].status&RS485_ACTIVE)==RS485_ACTIVE )
		if( (Routing_table[j].status&IPX_ACTIVE)==IPX_ACTIVE ||
				(Routing_table[j].status&TCPIP_ACTIVE)==TCPIP_ACTIVE ||
				(Routing_table[j].status&RS485_ACTIVE)==RS485_ACTIVE )
		{
			((class ConnectionData *)Routing_table[j].ptr)->station_list[Station_NUM-1].des_length=length;
			((class ConnectionData *)Routing_table[j].ptr)->panel_info1.des_length=length;
		}
	}
}

int read_descriptors(void)
{
		uint l1;
		int i,result=ERROR_COMM;
		Panel_info1 panel_info;
		Station_point *station_list;
		GWindow *D=NULL;
		uint l,net_length;
		unsigned long activepanels;
		char pnr[10];
		for(l1=0; l1<MAX_Routing_table ; l1++)
		{
//		 if( (Routing_table[l1].status&RS485_ACTIVE)==RS485_ACTIVE )
		if( (Routing_table[l1].status&IPX_ACTIVE)==IPX_ACTIVE ||
				(Routing_table[l1].status&TCPIP_ACTIVE)==TCPIP_ACTIVE ||
				(Routing_table[l1].status&RS485_ACTIVE)==RS485_ACTIVE )
		 {
			if( Routing_table[l1].Port.network == networkaddress ) break;
		 }
		}
		if( l1<MAX_Routing_table )
		{
		 if( (ready_for_descriptors&0x08) || (main_screen&0x02) )
		 {
			DisplayMessageT(30, 8, 50, 12, NULL, wait_text, NULL, Blue, NULL, 7000);
//			Delay(4000);
		 }
//		station_list = ((class MSTP *)Routing_table[l1].ptr)->station_list;
		 activepanels = ((class ConnectionData *)Routing_table[l1].ptr)->panel_info1.active_panels;
		 for(i=0;i<MAX_STATIONS;i++)
			if( (activepanels&(1L<<i)) && Station_NUM!=i+1 )
			{
				if( !(((class ConnectionData *)Routing_table[l1].ptr)->need_info&(1l<<i)) )
				{
				 if( (result=net_call(COMMAND_50, PANEL_INFO1_COMMAND, (char*)&panel_info, 0, i+1, networkaddress,NETCALL_RETRY|NETCALL_NOTTIMEOUT))!=SUCCESS )
					result = net_call(COMMAND_50, PANEL_INFO1_COMMAND, (char*)&panel_info, 0, i+1, networkaddress,NETCALL_NOTTIMEOUT);
				 if(result==SUCCESS)
				 {
					((class ConnectionData *)Routing_table[l1].ptr)->station_list[i].state = 1;
					 memcpy( ((class ConnectionData *)Routing_table[l1].ptr)->station_list[i].name, panel_info.panel_name, sizeof(Station_NAME));
					 ((class ConnectionData *)Routing_table[l1].ptr)->station_list[i].des_length=panel_info.des_length;
				 }
				 else
					 activepanels &= ~(1L<<i);
				}
		 }

//		Delay(3000);
		station_list = ((class ConnectionData *)Routing_table[l1].ptr)->station_list;
//		activepanels = ((class MSTP *)Routing_table[l1].ptr)->panel_info1.active_panels;
		l=net_length=0;
		for(i=0;i<MAX_STATIONS;i++)
		 if( (activepanels&(1L<<i)) && Station_NUM!=i+1 )
		 {
			 net_length += station_list[i].des_length;
		 }

		set_semaphore_dos();
		if(Des)
		{
			delete Des;
			Des = 0;
		}
		if(net_length)
			Des = new XmsDes(net_length);
		clear_semaphore_dos();

		if(net_length)
		{
		 D = new GWindow(mode_text?18:200, mode_text?7:150, mode_text?61:510, mode_text?11:200, NO_STACK,0);
		 DisplayMessageT(18, 7, 61, 11, ctrlbreak_text, "Reading descriptors        ", NULL, Blue, D);
		 strcpy(pnr,panel_text1);
		 for(i=0;i<MAX_STATIONS;i++)
			if(Station_NUM!=i+1)
			if( (activepanels&(1L<<i)) )
			{
				char b[3];
				int k=0;
				b[0] = '.'; b[1] = 0;
//				station_list[i].state &= ~0x02;
				if(D)
				{
				 lin_text[10]=0;
				 D->GWPuts(1, 26, lin_text, Lightblue, Black);
				 D->GWPuts(2, 16, lin_text, Lightblue, Black);
				 lin_text[10]=' ';
				 itoa(i+1, &pnr[6],10);
				 D->GWPuts(2, 16, pnr, Lightblue, Black);
				 for(int j=0;j<=AY;j++)
				 if(point_des[j]>=0)
				 {
					 Delay(100);
					 l1=0;
					 if( (result=net_call(47, j+1, Des->buffer, &l1, i+1, networkaddress,NETCALL_RETRY))!=SUCCESS )
						result=net_call(47, j+1, Des->buffer, &l1, i+1, networkaddress);
					 if( result==SUCCESS )
					 {
						if(l+l1>net_length) break;
						l += l1;
						Des->put(i+1,j,l1);
						D->GWPuts(1, 26 + k++, b, Lightblue, Black);
					 }
					 else
						 break;
				 }
				}
			}
		}
		if(D) {DeleteMessage(D); D=NULL;}
		}
	  return result;
}

void repeat(void)
{
 int man;
// char xbuf[30];
	G.GShowMenuBar(message,listonscreen);
//	G.GShowMenuBar(message);
	if(!mode_text) msettextstyle(DEFAULT_FONT, HORIZ_DIR,1);
	qtt=0;
	logout=0;
//	memsize();
	do {
//		 set_pointer_shape(ARROW);
/*
		 if( ready_for_descriptors )
		  if( ser_rs485->port_status == INSTALLED )
		  {
			  read_descriptors();
			  ready_for_descriptors = 0;
		  }
*/
		 if(ready_for_descriptors&0x08)
		 {
			read_descriptors();
			ready_for_descriptors &= ~0x08;
		 }
		 display_pointer();
		 if(!timesave)
		 {
		  if( save_prg_flag )
		  {
			 ptr_panel->savefile(ptr_panel->Default_Program, &Panel_Info1, ptr_panel->table_bank, 1);
			 save_prg_flag = 0;
		  }
		  timesave=300000;
		 }
		 main_screen=1;
		 man=G.GReturn();
		 main_screen=0;
		 if(man == -4)
		 {
			 if(!local_request(station_num))
			 {
				if( gAlarm )
				 man = M3+3;      //ALARMM
			 }
			 else
			 {
				if( GAlarm )
				 man = M3+3;      //ALARMM
			 }
		 }
		 if(man == 68)
		 {
			memsize();
			continue;
		 }
		 if(man == 0x70)
		 {
			if(!local_panel)
			{
			resetop();
			}
			continue;
		 }
		 if(man == 0x71)
		 {
			if(local_panel)
			{
				if(mode_text)
				{
					ptr_panel->go_graphic();
					interface_mode = MODE_GRAPHIC;
				}
				else
				{
					 ptr_panel->go_text();
					 interface_mode = MODE_TEXT;
				}
			}
			continue;
		 }

		 if(man == -32)
		 {
			man = comman_line(2, 21, 79, 23, fond_color);
		 }
		 ptr_panel->Select(man);
		 print_alarm_word();

/*
							xbuf[0]=0;
							if( Routing_table[0].ptr )
							{
								itoa( ((Header_pool *)(	((Serial *)Routing_table[0].ptr)->ser_pool.buf ))->length
									,xbuf,10);
							}
						 strcat(xbuf,"  ");
							if( Routing_table[1].ptr )
							{
								itoa( ((Header_pool *)(	((Serial *)Routing_table[1].ptr)->ser_pool.buf ))->length
								  ,&xbuf[strlen(xbuf)],10);
							}
						 strcat(xbuf,"  ");
						 for(int i=0; i<MAXServerTSMTable; i++)
						 {
							itoa( ServerTSMTable.table[i].state, &xbuf[strlen(xbuf)], 10);
						 }
						 mxyputs(50,3,xbuf,Black,White);
*/
	} while(!qtt && !logout);

//	if(logout)
//		G.RestoreArea();
//	if(qtt)
//	{
//	}
 }



extern char *ralign(char *,int );
extern int savedes();
extern int loaddes();
extern GWControl Control;
extern edit(char *);
//char ptr[60];
unsigned char *mesaj;
void ChangeDir();
void About();
void ChangeFile(char *ptr);
//unsigned _ovrbuffer = 0x500;

extern char huge  des[MAX_DES];
int error_net=0;

char subpbuf[5]; //for read sub_panel


//output_form output[128];


#define OUT 0
//GGrid w(10,10,60,20,0,"prgs.dbf");
//GEdit e(1,1,80,24,1);
//GWindow mes(3,17,78,23,1);

// char *message[]={{"~Convert"},{"~Edit"},{"~Miscellaneous"},{"E~xit"},0};
//void Panel::showpoints(int man, int arg)
void showpoints(int man, int Panel_type, int Panel, int Network, int arg=0, int maxtbl=0)
{
				int ptype,mrow,rx,lx,stk=GRIDINS,ttype=0,ly,ry;
        uint l1;
				char ca=0, *ptitle;
//				mrow=8;
				mrow   = 16;
				ptitle = NULL;
				lx = 2;
				ly = 3;
				rx = 79;
				ry = 21;
				switch (man) {
				 case M0+0:
							ptype=CONNECT_COM;
							lx=19; rx=62;
							ly = 7;
							stk = GRID;
							mrow=4;
							ca=1;
							break;
				 case M1+1:
							ptype=NET_SEL;
							lx=5; rx=46;
							ly = 5;
							stk = GRID;
							ca=1;
							ptitle = "Network List";
							break;
				 case M2+0:
							ptype=GRP;
							lx=10; rx=71;
							break;
				 case M2+1:
							ptype=PRG;
							lx=10; rx=72;
//							mrow=5;
							break;
				 case M2+3:
							ptype=OUT;
							stk = GRID;
							break;
				 case M2+2:
							ptype=IN;
							rx=80;
							stk = GRID;
							break;
				 case M2+4:
							ptype=VAR;
							stk = GRID;
							lx=8; rx=72;
//							mrow=16;
							break;
				 case M2+5:
							ptype=CON;
//							mrow=8;
							break;
				 case M2+6:
							ptype=WR;
//							mrow=4;
							break;
				 case M2+7:
							ptype=AR;
							lx=18; rx=63;
				         ly = 6;
//							mrow=2;
							mrow=8;
							break;
				 case M2+8:
							ptype=AY;
							lx=30; rx=50;
							break;
				 case M3+0:
							ptype=AMON;
							lx=6;rx=59;
							if( panel_info1.panel_type == MINI_T3000 && (panel_info1.version>110 && panel_info1.version<260) )
								 return;
							break;
				 case M3+1:
							ptype=TBL;
							ttype=INDIVIDUAL;
							lx=30;rx=50;
							ca=1;
							break;
/*
				 case M3+2:
							ptype=ALARMS;
							ca=1;
							break;
*/
				 case M3+2:
							ptype=UNIT;
							mrow=8;
							lx=15;rx=65;
							ca=1;
							break;
				 case M3+3:
							rx=80;lx=2;
							ptype=ALARMM;
							ca=1;
							break;
/*************** add by dina long********************/
/* Adi
				case M3+4:
							ptype=NETSTAT;
							stk  = GRID;
							break;
*/
/*************** add by dina long*******************/
				 }

				if( (ca) || (check_access(ptype)!=R_NA) )
				{
				 GGrid *wgrid;
				 int row;
				 row=mrow;
				 switch(ptype){
				 case GRP:
				 case PRG:
				 case OUT:
				 case IN:
				 case VAR:
				 case CON:
				 case WR:
				 case AR:
				 case AY:
				 case AMON:
				 case UNIT:
					 row=min(mrow,tbl_bank[ptype]);
					 break;
/************* add by dina long*********************/
/* Adi
				 case NETSTAT:
				 row=min(mrow,32);
					 break;
*/
/************* add by dina long********************/
				 }
				 error_net=0;
				 ry = ly+row+2;
				 if(!mode_text)
				 {
					lx--;
					lx = lx*8;
					ly = ly*8;
					rx = rx*8-3;
					ry = ly + row*20 + 24 + 24 + 17;
					switch(ptype){
						 case IN:
							 rx -= 10;   //6;
							 lx += 4;   //6;
							 break;
						 case WR:
							 rx -= 4;   //6;
							 lx += 4;
							 break;
						 case AR:
						 case PRG:
							 rx += 16;
							 break;
						 case VAR:
							 rx += 8;
							 break;
						 case AY:
							 rx += 18;
							 break;
					}
				 }
//				 wgrid=new GGrid(lx,ly,rx,ly+row+2,stk,NULL,ptype,Panel_type,Panel,Network,ttype,arg);
				 wgrid=new GGrid( lx, ly, rx, ry, ptitle, Lightgray, Darkgray, Black,
													stk, NULL, ptype, Panel_type, Panel, Network, ttype, arg,SMALL_FONT,5,1);
				 if(!wgrid->grid_error)
				 {
					if (!error_net)
					{
					if(!mode_text)
					{
//						wgrid->save = 0;   //NO_SAVE
					}
//					wgrid->GWSet(ptitle,Lightgray,Darkgray);
					display_amons = 1;
					wgrid->GShowGrid();
					display_amons = 0;
					refresh = 1;
					refresh_time = refresh_time_init;
					while (!wgrid->HandleEvent())
					{
					 unsigned long l;
					 if(!refresh_time && ptype!=ALARMM && ptype!=AMON && ptype!=AMON_INPUTS
						 && ptype!=ALARMS && ptype!=TBL && ptype!=UNIT && ptype!=CONNECT_COM
						 && ptype!=NET_SEL && ptype!=GRP)
					 {
						 if(wgrid->modify)
						 {
							 wgrid->GSend(SENDPOINTS);
							 wgrid->modify = 0;
						 }
						 else
							 wgrid->GRead(SMALLBANK);
						 int w_orecord = wgrid->w_record;
						 int w_ofield = wgrid->w_field;

						 wgrid->w_nfields = 0;
						 wgrid->t_fields[wgrid->w_lfield-1]=1;
						 wgrid->w_field = 1;
						 wgrid->GGDrawGrid(Black);
						 wgrid->GGHideCur(Black);
						 wgrid->w_record = w_orecord;
						 wgrid->w_field = w_ofield;
						 wgrid->GGShowCur(Black);

						 refresh_time = refresh_time_init;
					 }
					 print_alarm_word();
					};
					}
				 }
				 delete wgrid;
				 refresh = 0;
//		 set_pointer_shape(ARROW);
				 display_pointer();
				}

}

void reset_serial(void)
{
 serial_access = 0;
 serial_panel_type = T3000;
 local_panel = 1;
 ser_ptr = NULL;
}

void getpassword(char *pass, char *text)
{
/*
 int l = (strlen(text)+14)/2;
		 hide_pointer();
		 Bordergr(40-l, 9, 40+l, 13, Black, Lightgray, White, White, 1, 0);
		 mxyputs( 42-l, 11,  text, Lightgray, Black);
		 chbkg(28+l,11, 8, Darkgray, White);
		 mgotoxy(28+l,11);
		 mgets(pass,0,Darkgray, White);
		 clear_color(39-l, 42+l, 9, 13, lin_text, fond_color, Black);
		 display_pointer();
*/
		 ReadWindow(mode_text?25:180, mode_text?7:140, mode_text?60:450, mode_text?11:200, Lightgray, Darkgray, Black,
							 Cyan, White, text, pass, 8, "********");
		 rtrim(pass);
}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.040  ********
// ********       begin       ********
// ***********************************
void getpassword_help(int Flag_help,char *pass, char *text)
{
		 ReadWindow_help(Flag_help,mode_text?25:180, mode_text?7:140, mode_text?60:450, mode_text?11:200, Lightgray, Darkgray, Black,
							 Cyan, White, text, pass, 8, "********");
		 rtrim(pass);
}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.040  ********
// ********        end        ********
// ***********************************

typedef struct {
	char l_panel_info1;
	Panel_info1 panel_info1;
	char l_tbl_bank;
	unsigned char tbl_bank[MAX_TBL_BANK];
	char l_default_prg;
	char default_prg[13];
	char l_units;
	Units_element units[MAX_UNITS];
	char l_gAlarm;
	char gAlarm;
} INFODATA;

int  Panel::connect_panel_proc(int tt)
{
		 unsigned char tbl_bank1[MAX_TBL_BANK];
		 Panel_info1 panel_info;
		 char default_prg1[13];
		 RS232Error result;
		 Time_block time_buf;
		 uint l1;
		 int net;
		 INFODATA *id=NULL;

			set_semaphore_dos();
			id = new INFODATA;
			clear_semaphore_dos();

			memcpy( tbl_bank1, tbl_bank, sizeof(tbl_bank1));
			memcpy( default_prg1, default_prg, 13);
			panel_info = panel_info1;
			gAlarm = 0;

		 result = ERROR_COMM;
//		 if(!tt && !serial_access )
		 {
			 l1=0;
			 result = net_call(COMMAND_50, INFODATA_COMMAND, (char*)id, &l1, station_num, networkaddress,NETCALL_NOTTIMEOUT|NETCALL_RETRY);
			 if( !l1 )  result = ERROR_COMM;
		 }
		 if( result != RS232_SUCCESS )
		 {
			result = net_call(COMMAND_50, PANEL_INFO1_COMMAND, (char*)&panel_info1, 0, station_num, networkaddress,NETCALL_RETRY);
			if( result == RS232_SUCCESS )
			{
				Delay(100);
				l1 = sizeof(tbl_bank);
				result=net_call(COMMAND_50, TABLEPOINTS_COMMAND, (char *)tbl_bank, &l1, station_num, networkaddress,NETCALL_RETRY);
			}
			if( result == RS232_SUCCESS )
			{
					 Delay(100);
					 result = net_call(COMMAND_50, DEFAULT_PRG_COMMAND, default_prg, 0, station_num, networkaddress,NETCALL_RETRY);
			}
			if( result == RS232_SUCCESS )
			{
				Units_element	*punits;
				set_semaphore_dos();
				punits = new Units_element[MAX_UNITS];
				clear_semaphore_dos();
				memset(punits,0,sizeof(Units_element)*MAX_UNITS);
				Delay(100);
				if( net_call(UNIT+1, 0, (char *)punits, 0, station_num, networkaddress,NETCALL_RETRY)==SUCCESS)
				{
				 upcustomunit(punits);
				}
				set_semaphore_dos();
				delete punits;
				clear_semaphore_dos();
			}
			if( (panel_info1.panel_type == T3000 && panel_info1.version >= 216) ||
					(panel_info1.panel_type == MINI_T3000 && panel_info1.version >= 107) )
				if( result == RS232_SUCCESS )
				{
				 Delay(100);
				 result = net_call(COMMAND_50, ALARM_NOTIFY_COMMAND, &gAlarm, 0, station_num, networkaddress,NETCALL_RETRY);
				 galarm_read_time=timestart+60;
				}
		 }
		 else
		 {
			 panel_info1 = id->panel_info1;
			 memcpy( (char *)tbl_bank, id->tbl_bank, sizeof(tbl_bank));
			 memcpy( default_prg, id->default_prg, 13);
			 upcustomunit(id->units);
       gAlarm = id->gAlarm;
		 }
		 if(tt)
		 {
			if( result == RS232_SUCCESS )
			{
			 if( panel_info1.panel_type == T3000 || panel_info1.version >= 245 )
			 {
				Delay(100);
				result = net_call(COMMAND_50, STATION_LIST_COMMAND, (char*)station_list, 0, station_num, networkaddress,NETCALL_RETRY);
			 }
			 else
			 {
				for( int i=0; i<32; i++ )
				{
				 station_list[i].state = 0;
				 station_list[i].des_length = 0;
				}
				station_list[station_num-1].state = 1;
				station_list[station_num-1].des_length = panel_info1.des_length;
				memcpy((char*)station_list[station_num-1].name, panel_info1.panel_name, NAME_SIZE);
			 }
			}
			if( result == RS232_SUCCESS )
			{
			 Delay(100);
			 result = net_call(PASS+1, 0, (char *)&::passwords, 0, station_num, networkaddress, NETCALL_RETRY, 30);
			}
			if( result == RS232_SUCCESS )
			{
				 Delay(100);
				 result = net_call(TIME_COMMAND, 0, (char *)&time_buf, 0, station_num, networkaddress,NETCALL_RETRY, TIMEOUT_NETCALL);
			}
			if( result == RS232_SUCCESS )
			{
				adjust_readtime(&time_buf);
				t = mktime((struct tm *)&time_buf);
				disable();
				stime((time_t *)&t);
//				memcpy(&ora_current, &time_buf, sizeof(Time_block));
				updatetimevars();
				enable();
//				memcpy( (char*)station_list, (char*)ser_ptr->remote_list,
//																								32*sizeof( Station_point ) );
			}
		 }
		 if( result!=SUCCESS )
		 {
			memcpy( tbl_bank, tbl_bank1, sizeof(tbl_bank));
			memcpy( default_prg, default_prg1, 13);
			panel_info1 = panel_info;
		 }
			set_semaphore_dos();
			delete id;
			clear_semaphore_dos();
		 return result;
}

void setlocalpanel(int net=0)
{
			local_panel = 1;
			station_num=Station_NUM;
			if(net)
				networkaddress=net;
			else
				networkaddress=NetworkAddress;
			panel_info1 = Panel_Info1;
			memcpy( tbl_bank, ptr_panel->table_bank, sizeof(tbl_bank));
			memcpy( default_prg, ptr_panel->Default_Program, 13);
			upcustomunit(ptr_panel->units);
			ptr_panel->GlPanel = station_num;
			ptr_panel->GlNetwork = networkaddress;
			ptr_panel->GlPanel_type = T3000;
}

void Panel::Select(int man)
{
// char *message[]={{" ~Convert"},{"~Edit"},{"~Miscellaneous"},{" E~xit"},0};
 int i,j,one_net=-1;
 switch(man){
	case M1+1:

		for(j=0,i=0; i<MAX_Routing_table ; i++)
		{
		 if( (Routing_table[i].status&PORT_ACTIVE)==PORT_ACTIVE )
		 {
			for(int k=0; k<MAX_reachable_networks; k++)
			 if( Routing_table[i].Port.networks_list[k].status == REACHABLE )
			 {
				j++;
			 }
			j++;
			one_net=i;
		 }
		}
		if(j!=1) one_net = -1;

/*
		one_net=-1;
		for(j=0,i=0; i<MAX_Routing_table ; i++)
		{
		 if( (Routing_table[i].status&PTP_ACTIVE)==PTP_ACTIVE )
		 {
			one_net=i;
			break;
		 }
//		 if( !j && (Routing_table[i].status&RS485_ACTIVE)==RS485_ACTIVE )
			if( !j && ( (Routing_table[i].status&IPX_ACTIVE)==IPX_ACTIVE ||
				(Routing_table[i].status&TCPIP_ACTIVE)==TCPIP_ACTIVE ||
				(Routing_table[i].status&RS485_ACTIVE)==RS485_ACTIVE ) )
		 {
			j=1;
			one_net=i;
		 }
		}
*/
	case M0+0:
	case M2+0:
	case M2+1:
	case M2+2:
	case M2+3:
	case M2+4:
	case M2+5:
	case M2+6:
	case M2+7:
	case M2+8:
	case M3+0:
	case M3+2:
/****************add by dina long********************/
// Adi	case M3+4:
/****************add by dina long*******************/
	case M3+3: //		if(panel_info1.panel_type == MINI_T3000) break;
	 if(one_net<0)
	 {
		entry_selected = 0;
		G.ShowunderMBar();
		showpoints(man, GlPanel_type, GlPanel, GlNetwork);
//		showpoints(man);
		G.GShowMenuBar(message);
//				 ChangeDir();
	 }
	 else
	 {
		network_sel_tmp = Routing_table[one_net].Port.network;
		panel_sel_tmp = station_num;

//		if( (Routing_table[one_net].status&RS485_ACTIVE)==RS485_ACTIVE )
		if( (Routing_table[one_net].status&IPX_ACTIVE)==IPX_ACTIVE ||
				(Routing_table[one_net].status&TCPIP_ACTIVE)==TCPIP_ACTIVE ||
				(Routing_table[one_net].status&RS485_ACTIVE)==RS485_ACTIVE )
		{
		 pactivepanels = &((ConnectionData*)Routing_table[one_net].ptr)->panel_info1.active_panels;
		 pstation_list_sel = &((ConnectionData*)Routing_table[one_net].ptr)->station_list[0];
		}
		else
		{
		 pactivepanels = &panel_info1.active_panels;
		 pstation_list_sel = &station_list[0];
		}
		::select_panel(CSTATION, Routing_table[one_net].Port.network, 1);
		network_select = network_sel_tmp;
		panel_select   = panel_sel_tmp;
	 }

	 if(man==(M0+0))
	 {
		int com_select,system_entry,l;
		com_select = entry_selected-1;
		if( com_select >= 0)
		if( comm_info[com_select].connection )
		{
		if( comm_info[com_select].connection == SERIAL_LINK || comm_info[com_select].connection == MODEM_LINK )
		{
		  if( comm_info[com_select].connection!=MOUSE_LINK )
		  {
			if ( (l=checkport(com_select)) >= 0 )
			{
			if( (Routing_table[l].status&PTP_ACTIVE)!=PTP_ACTIVE )
			{
			  system_entry = -1;
			  if( comm_info[com_select].connection==MODEM_LINK )
				{
				 entry_selected = 0;
				 if( FXOpen("syslist.dbf", &syslist_handle, READWRITE ) == FX_OPEN_ERROR )
					 if(FXCreate( "syslist.dbf", 5, dial_struct, &syslist_handle )!=FX_OPEN_ERROR)
						 for(int i=0; i<32;i++) FXPutRec(syslist_handle);
				 FXClose( syslist_handle );

				 GGrid *system_list;
// ********  the old code  ********
//				 system_list = new GGrid(3,3,76,21,"System List",Lightgray,Darkgray,Black,
//																 GRID,"syslist.dbf",0,0,0,0,0,0);
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.041  ********
// ********       begin       ********
// ***********************************
				 system_list = new GGrid(0,"need_help",3,3,76,21,"System List",Lightgray,Darkgray,Black,
																 GRID,"syslist.dbf",0,0,0,0,0,0);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.041  ********
// ********        end        ********
// ***********************************
//				 system_list->GWSet("System List", Lightgray,Darkgray);
				 system_list->GShowGrid();
				 while (!system_list->HandleEvent());
				 delete system_list;
				 if( !entry_selected ) return;
				 system_entry = entry_selected-1;
			  }
			  if( serial_access ) disconnect_serial(1);
			  GWindow *D=NULL;
//				 D = new GWindow(mode_text?19:200, mode_text?7:150, mode_text?61:500, mode_text?11:200, NO_STACK,0);
			  serial_access = 1;
				local_panel = 0;

			  if( ((class PTP *)Routing_table[l].ptr)->activity == BUSY )
			  { serial_access = 0; return; }
			  ser_ptr = (class PTP *)Routing_table[l].ptr;
			  ser_ptr->Set_mode( MASTER );
//			  DisplayMessage(mode_text?19:200, mode_text?7:150, mode_text?61:500, mode_text?11:200, ctrlbreak_text, "  Connecting to serial...  ", &D, Blue);
			  RS232Error result;
			  if( system_entry>=0 )
			  {
//						 ser_ptr = (Serial *)Routing_table[comm_info[com_select].port_num].ptr;
//						 ser_ptr->Set_mode( MASTER );
						 if( ser_ptr->modem_active )
						 {
//							 DisplayMessage(mode_text?19:200, mode_text?7:150, mode_text?61:500, mode_text?11:200, ctrlbreak_text, "  Trying modem connection...  ", &D, Blue);
//							 DisplayMessage(19, 7, 61, 11, "    CTRL/Break - Interrupt  ", "   Connecting to modem...     ", NULL, Blue, &D);
							 if( ( ser_ptr->modem_status = ser_ptr->modem_obj->Initialize() ) != MODEM_SUCCESS )
							 {
//								 D.GReleaseWindow();
//								 if(D) DeleteMessage(D);
//								 clear_color(1, 78, 5, 20, lin_text, fond_color, Black);
								 reset_serial();
								 return;
							 }
							 DisplayMessage(mode_text?19:200, mode_text?7:150, mode_text?61:500, mode_text?11:200, ctrlbreak_text, "Wait for modem connection...", &D, Blue);
							 if( ser_ptr->modem_status = ser_ptr->modem_obj->Dial( dial_list_data.phone_number ) != MODEM_SUCCESS )
							 {
//								 D.GReleaseWindow();
								 if(D) DeleteMessage(D);
//								 clear_color(1, 78, 5, 20, lin_text, fond_color, Black);
								 ser_ptr->modem_obj->Disconnect();
								 reset_serial();
								 return;
							 }
                      Delay(1000);
							 if(D) {DeleteMessage(D);D=NULL;};
							 Routing_table[ser_ptr->port_number].port_status_vars.connection = PTP_DISCONNECTED;
							 ((class PTP *)Routing_table[ser_ptr->port_number].ptr)->connection_state = PTP_DISCONNECTED;
						 }
						 else
						 {
//								if(D) DeleteMessage(D);
								DisplayMessageT(20, 7, 60, 11, NULL, " Modem port not installed ", NULL, Blue, NULL, 1500);
								reset_serial();
								return;
						 }
				 }
				if(ser_ptr)
				{
				 ser_ptr->activity = BUSY;
				 refresh_time_init = 200;
				 disconnect_time = DISCONNECT_TIME;
				 if( ser_ptr->ReadBaudRate()<14400 ) refresh_time_init = 400;
				 memcpy( (char*)ptr_panel->local_stations, (char*)station_list,
							 MAX_STATIONS*sizeof( Station_point ) );
				 memcpy( (char*)&passwords, (char*)&::passwords,sizeof( passwords ) );
				 memset( (char*)station_list, 0, MAX_STATIONS*sizeof( Station_point ) );
				 if( ser_ptr->modem_active )
				 {
						Delay(1000);
				 }
				 ser_ptr->port->FlushRXBuffer();
				 ser_ptr->port->FlushTXBuffer();
				 estab_text[strlen(estab_text)-5]=com_select+0x31;
				 DisplayMessage(mode_text?15:200, mode_text?7:150, mode_text?65:500, mode_text?11:200, ctrlbreak_text, estab_text, &D, Blue);
         Delay(1000);
				 if ( (result=net_call(50, ESTABLISH_CONNECTION_PORT, NULL, 0, com_select, 0xFFFF, 0, 50) ) == SUCCESS )
				 {
					if( (result=connect_panel_proc(1))==RS232_SUCCESS )
					{
					 if(D) {DeleteMessage(D);D=NULL;};
//					D.GReleaseWindow();
//					clear_color(1, 78, 5, 20, lin_text, fond_color, Black);
					 serial_panel_info1      = panel_info1;
					 serial_panel_type       = panel_info1.panel_type;
					 ptr_panel->GlPanel      = station_num;
					 ptr_panel->GlNetwork    = networkaddress;
					 ptr_panel->GlPanel_type = panel_info1.panel_type;
					 char b[80];
					 strcpy(b,"  Connected to panel ");
					 strcat(b,station_list[station_num-1].name);
					 DisplayMessageT(20, 7, 60, 11, ctrlbreak_text, b, &D, Blue);
					}
					else
					{
					 if(D) {DeleteMessage(D);D=NULL;};
					 disconnect_serial();
					 DisplayMessageT(20, 7, 60, 11, NULL, "  Communication error !  ", &D, Blue);
				  }
				 }
				 else
				 {
					if(D) {DeleteMessage(D);D=NULL;};
					if(result==ERROR_NET)
					{
					 DisplayMessageT(20, 7, 60, 11, NULL, "           Connection failed.              Change the local network number.", &D, Blue);
					 Delay(7000);
          }
				 }
				 entry_selected = 0;
				 Delay(3000);
//				 D.GReleaseWindow();
				 if(D) DeleteMessage(D);
#ifdef SERIAL_COMM
				 if( result==SUCCESS )
					if( serial_access )
					{
						readdes_serial();
					}


				 if( result!=SUCCESS )
				 {
				  disconnect_serial(1);
				 }
				 else
				 {
				  if(!get_access(ESC))
					disconnect_serial(1);
				 }
				 if( result==SUCCESS )
				 {
			    serial_access = station_num;
					strcpy(remote_path, oldpath);
				  rtrim(dial_list_data.des_file);
				  if( strlen(dial_list_data.des_file) )
				  {
					 strcat(remote_path,"\\");
					 strcat(remote_path,dial_list_data.des_file);
					 set_semaphore_dos();
					 if( chdir(remote_path) )
					 {
						mkdir( dial_list_data.des_file );
						chdir(remote_path);
					 }
					 clear_semaphore_dos();
				  }
				 }
#endif
				}
			}
			else
			{
			  DisplayMessageT(20, 7, 60, 11, NULL, " Connection already established! ", NULL, Blue, NULL, 2000);
			}
			}
		  }
			else
		  {
			DisplayMessageT(20, 7, 60, 11, NULL, " This is a mouse port! ", NULL, Blue, NULL, 2000);
		  }
		}
		else
		{
		  if( comm_info[com_select].connection == RS485_LINK )
			  DisplayMessageT(20, 7, 60, 11, NULL, " RS485 network installed! ", NULL, Blue, NULL, 2000);
			else
			  DisplayMessageT(20, 7, 60, 11, NULL, " Ayncron Mode installed! ", NULL, Blue, NULL, 2000);
		}
	  }
		else
	  {
			DisplayMessageT(20, 7, 60, 11, NULL, " COM port not installed! ", NULL, Blue, NULL, 2000);
	  }
	 }
	 if(man==(M1+1))
	 {
		RS232Error error;
		int l1, st, net;
//		unsigned char tbl_bank1[MAX_TBL_BANK];
//		Panel_info1 panel_info;
//		char default_prg1[13];
		if( station_num!=panel_select || networkaddress!=network_select)
		{
		 st = station_num;
		 net= networkaddress;
		 l1 = local_panel;
		 station_num=panel_select;
		 networkaddress=network_select;
//		 if(station_num==Station_NUM && networkaddress==NetworkAddress) local_panel=1;
		 if(station_num==Station_NUM && localnetwork(networkaddress) ) local_panel=1;
		 else local_panel=0;
//		 memcpy( tbl_bank1, tbl_bank, sizeof(tbl_bank1));
//		 memcpy( default_prg1, default_prg, 13);
//		 panel_info = panel_info1;
		 if(!local_panel)
		 {
//  memsize();
			if( (error=ptr_panel->connect_panel_proc())!=SUCCESS )
			{
			 station_num = st;
			 networkaddress = net;
			 local_panel=l1;
			}
			if(networkaddress!=net)
			{
			 read_descriptors();
			}
		 }
		 else
		 {
			 setlocalpanel(networkaddress);
		 }
		 ptr_panel->GlPanel = station_num;
		 ptr_panel->GlNetwork = networkaddress;
		 ptr_panel->GlPanel_type = panel_info1.panel_type;

		 display_pointer();
/*
		 if( serial_access && error==SUCCESS )
		 {
			readdes_serial();
		 }
*/
		}
		}
		break;
/*	case 24:
				 GGrid ww(10,10,60,20,0,"prgs.dbf",OUT,GlPanel_type,GlPanel,GlSub_panel,GlNet_type);
				 ww.GWSet("Program",Lightgray,Lightgray);
				 ww.GShowGrid();
				 while (!ww.HandleEvent());
*/
//				 ChangeDir();
	case M3+1:
				 int i;
				 i=dialog_select( min(tbl_bank[TBL],5), (char *)tables_text, 0, 32, 6, Cyan,Blue,NULL,9);  // 0=don't save
				 if(i>=0)
				 {
					G.ShowunderMBar();
					showpoints(man,GlPanel_type, GlPanel, GlNetwork,i+1);
					G.GShowMenuBar(message);
				 }
				 break;
/**************************************
**********  William add  *************
********     11.19.1997  *************
**********   code begin  *************
**************************************/
	case M3+4:
//				  netstat_show();
					break;
/**************************************
**********  William add  *************
********     11.19.1997  *************
**********    code end   *************
**************************************/
	case M4+0:
				 if( check_access(12)!=R_NA )
					 setup();
				 break;
/*
	case M4+1:
				 select_panel(STATION);
				 break;
*/
	case M4+1:
		{
		 if( check_access(12)!=R_NA )
		 {
			GGrid *wgrid;
			GWindow *wwin;
			char *p;
			hide_pointer();
			p = "      ENTER - select     INS - add      DEL - delete       ";
      wwin=NULL;
			if(mode_text)
			{
			 Bordergr(10, 4, 70, 22, Blue, Lightblue, White, White, 1, 0);
//		Border(10,4,70,22, Lightgreen, Green );
//		mtextcolor(Black) ;
			 mxyputs(11,21,p,Lightgray,Black);
			}
			else
			{
				wwin=new GWindow(78,60,562,430,"Password system",Lightgray,Darkgray,Black,NO_STACK,0);
				wwin->GShowWindow(WIN_ERROR);
				wwin->GWPuts(15,1,p,Lightgray,Black);
			}
//		set_semaphore_dos();
			wgrid=new GGrid(mode_text?13:100,mode_text?7:110,mode_text?29:250,mode_text?19:360,GRID,NULL,USER_NAME,GlPanel_type,GlPanel,GlNetwork);
//		clear_semaphore_dos();
			wgrid->GWSet(NULL,Lightgray,Darkgray);
			wgrid->GShowGrid();
			while (!wgrid->HandleEvent());
			delete wgrid;
			if(mode_text)
			{
			 clear_color(9, 64, 4, 22, lin_text, fond_color, Black);
			}
			else
			 if(wwin)
			 {
         wwin->GReleaseWindow();
				 delete wwin;
			 }
		 }
		}
				 break;
//	case M4+3:
//				 boardconfig();
//				 strcpy(station_list[Station_NUM-1].name,Station_NAME);
//				 break;
	case M4+2:
					 hardware();
//				 portconfig();
				 break;
/*
	case M4+5:
				 if(mode_text)
					 go_graphic();
				 else
					 go_text();
				 break;
*/
	case M0+1:
			 disconnect_serial(1);
			 break;
	case M0+2:
			About();
//	exec_program(ptr_panel->program_codes[0]);
			break;
	case M0+3:
			netstatus_show();
//			infoscreen();
			break;
	case M0+4:
			if(!local_panel && panel_info1.panel_type==T3000)
				filetransfer_routine();
			else
				G.pGPopUpTable[0].ReleasePopUp(-1);
			break;
	case M0+5:
			if( serial_access )
				readdes_serial();
			else
				read_descriptors();
			break;
	case M0+6:
			minioperations();
/*
			if(!local_panel)
				mini_operations( &panel_info1 );
*/
			break;
	case M0+7:
			pprint();
			break;
	case M0+8:
//		savedes();

// ********  the old code  ********
//		if(ReadYesNoButton(24, 8, 55, 14, Lightgray, Darkgray, Black,	Cyan, White,
//								 "   Exit application ?", exit_button, noexit_button, 'X', 'N'))
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.042  ********
// ********       begin       ********
// ***********************************
		if(ReadYesNoButton_help(7,24, 8, 55, 14, Lightgray, Darkgray, Black,	Cyan, White,
								 "   Exit application ?", exit_button, noexit_button, 'X', 'N'))
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.042  ********
// ********        end        ********
// ***********************************
		{
		 char pass[15]={0};
// ********  the old code  ********
//		 getpassword(pass, " Password : ");
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.043  ********
// ********       begin       ********
// ***********************************
		 getpassword_help(7,pass, " Password : ");
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.043  ********
// ********        end        ********
// ***********************************
		 if( !strcmp(pass,password) || !strcmp(pass,supervisor) )
		 {
			if(serial_access) disconnect_serial(1);
			qtt=1;
			exit_apl=1;
		 }
		}
		break;
	case M0+9:
		if(serial_access) disconnect_serial(1);
		logout=1;
		break;
	case M1+0:
		file();
		break;
/*
	case M1+1:
			select_panel(CSTATION);
			break;
*/
	case M1+2:
			pprint();
			break;
	case M1+3:
#ifndef WORKSTATION
					 set_semaphore(&t3000_flag);
//					 suspend(VIRTUAL);
#endif
// ********  the old code  ********
//					 if(ReadYesNo(25, 9, 58, 13, Lightgray, Darkgray, Black,
//													Cyan, White, "Clear panel? (Y/N): "))
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.044  ********
// ********       begin       ********
// ***********************************
					 if(ReadYesNo_help(13,25, 9, 58, 13, Lightgray, Darkgray, Black,
													Cyan, White, "Clear panel? (Y/N): "))
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.044  ********
// ********        end        ********
// ***********************************
					 {
						 if( local_panel )
							 clearpanel();
						 else
						 {
							 if( net_call(CLEARPANEL_T3000, 0, NULL, 0 ,station_num, networkaddress)!=SUCCESS )
							 {
									net_call(CLEARPANEL_T3000, 0, NULL, 0 ,station_num, networkaddress);
							 }
							 DisplayMessageT(20, 7, 60, 11, NULL, " Wait for panel initialization... ", NULL, Blue, NULL, 5000);
				 }
					 }
#ifndef WORKSTATION
					 clear_semaphore(&t3000_flag);
//					 resume(VIRTUAL);
#endif
					break;
	case M1+4:
       savenetwork();
//	Select SERIAL CONNECTION
//			ser_p->Set_working_port( LOCAL_PORT );
			break;
	case M1+5:
//	Select MODEM CONNECTION
//			ser_p->Set_working_port( MODEM_PORT );
			break;
	default:break;
			}
};


void About(void)
{
 GWindow *A= new GWindow((mode_text)?18:150,(mode_text)?8:100,(mode_text)?62:500,(mode_text)?15:240,NO_STACK,0);

 A->GWSet("About",Lightblue,Blue);
 A->GShowWindow(WIN_ERROR);

 A->GWPuts(1,2,"Building Automation and Control System",Lightblue,Blue);
 A->GWPuts(2,2,"            TEMCO CONTROLS",Lightblue,Blue);
 A->GWPuts(3,2,"          T3000 , Version ",Lightblue,Blue);
 A->GWPuts(3,28,version,Lightblue,Blue);
 A->GWPuts(4,2,"         Copyright (C) Aug, 97",Lightblue,Blue);

 while(!A->HandleEvent());
 delete A;
};


/***********************************************************/


//void main(int argc, char *argv[])
int proj()
{
 int i,j,n;
 setvectint8 = 0;

 disable();
 asm {                    // timer resolution
	  mov al,34h
	  out 43h,al
	  mov ax,8192
	  out 40h,al
	  mov al,ah
	  out 40h,al
 }
 enable();

 mfarmalloc((char far **)&heap_buf, MAX_HEAP_BUF+MAX_HEAP_GRP, heap_buf_handle);
 heap_grp = ((char *)heap_buf)+MAX_HEAP_BUF;

 mfarmalloc((char far **)&heap_amon, (long)MAX_HEAP_AMON+(long)MAX_HEAP_DIGM*sizeof(Heap_dmon)+(long)MAX_HEAP_ARRAY*4L, heap_amon_handle);
 heap_dmon = (Heap_dmon *)(((char *)heap_amon)+(long)MAX_HEAP_AMON);
 heap_array = (long *)(((char *)heap_dmon)+(long)MAX_HEAP_DIGM*sizeof(Heap_dmon));

 updatebuffer = new char[1024*5];

/*
 mfarmalloc((char far **)&heap_amon, MAX_HEAP_AMON, heap_amon_handle);
 mfarmalloc((char far **)&heap_grp, MAX_HEAP_GRP, heap_grp_handle);
 mfarmalloc((char far **)&heap_buf, MAX_HEAP_BUF, heap_buf_handle);
 mfarmalloc((char far **)&heap_dmon, (long)MAX_HEAP_DIGM*sizeof(Heap_dmon),  heap_dmon_handle);
 mfarmalloc((char far **)&heap_array, MAX_HEAP_ARRAY*4L,  heap_array_handle);
*/
 if( !interface_mode && mode_text)
 {
  ptr_panel->go_graphic(1);
 }
 if( interface_mode && !mode_text)
 {
  ptr_panel->go_text();
 }
 if( !interface_mode && !mode_text)
 {
  ptr_panel->go_graphic(2);
 }

 comm_info = (Comm_Info *) c_info;
 for(i=0; i<MAX_COM; i++)
 {
  strcpy(&comm_info[i].modemdata.first_init_string[0], default_string);
  comm_info[i].rings=1;
  comm_info[i].NetworkAddress=NetworkAddress;
  memcpy(comm_info[i].NetworkName,NetworkName,NAME_SIZE);
 }
//	load_icon("monitor.tif", &points_icon[AMON].idef, &points_icon[AMON].tifd,
//											 &points_icon[AMON].map);
	points_icon = new icon[AY+1];
//	for(i=0;i < AY+1; i++)
//	  points_icon[i].status = 1;
	points_icon[AMON].load_icon("monitor.tif");
	points_icon[PRG].load_icon("program.tif");
	points_icon[WR].load_icon("wr.tif");

	input_buffer=inp_buffer;
	if( simulate || def_macro )
	{
		mfarmalloc((char far **)&ptr_input_buffer, sizeof(struct input_buffer)*MAX_INPUT_BUFFER);
	  input_buffer=ptr_input_buffer;
	}
	if(simulate)
	{
	 if ((h=fopen("demo.mac","rb+"))!=NULL)
	 {
	  fread(ptr_input_buffer,sizeof(struct input_buffer),MAX_INPUT_BUFFER,h);
	  fclose(h);
	 }
	}

#ifndef WORKSTATION
	FILE *fhandle;
	if( (fhandle=fopen("config.cnf","rb+"))!=NULL)
	{
//		 int n,j;
//		 fread(&n, 2, 1, fhandle);    //ver
	 fseek(fhandle,0,SEEK_END);
	 if( ftell(fhandle) )
	 {
		 fseek(fhandle,CNF_VER,SEEK_SET);
		 fread(&cnf_version, 2, 1, fhandle);    //config.cnf version
		 if(cnf_version >= 227)
		 {
			fseek(fhandle,CNF_STATION_NUM,SEEK_SET);
			fread(&Station_NUM, 2, 1, fhandle);
			fread(Station_NAME, 16, 1, fhandle);
			fread(&NetworkAddress, 1, 2, fhandle);
			fread(&NetworkName, 16, 1, fhandle);

			fread(&nr_boards, 2, 1, fhandle);
			fread(&n, 2, 1, fhandle);    //size
			for(i=0;i<MAX_BOARDS;i++)
			{
			 if(sizeof(Board_info)>=n)
				fread(&boards[i], n, 1, fhandle);
			 else
			 {
				fread(&boards[i], sizeof(Board_info), 1, fhandle);
				fseek(fhandle,n-sizeof(Board_info),SEEK_CUR);
			 }
			}
			fread(&n, 2, 1, fhandle);   //size comm_info
			j=MAX_COMM_INFO;
			for(i=0;i<j;i++)
			{
			 if(sizeof(Comm_Info)>=n)
				fread(&comm_info[i], n, 1, fhandle);
			 else
			 {
				fread(&comm_info[i], sizeof(Comm_Info), 1, fhandle);
				fseek(fhandle,n-sizeof(Comm_Info),SEEK_CUR);
			 }
			}
			fread(&IPX_enabled, 1, 1, fhandle);
//		 fread(&ModemDataBase[0], sizeof(ModemCapabilities), 1, fhandle);
//		 fseek(fhandle,CNF_NETWORK_NUMBER,SEEK_SET);
//		 fread(&NetworkAddress, 1, 2, fhandle);

			if(cnf_version > 255)
			{
			 fseek(fhandle,CNF_IORATE_OFF,SEEK_SET);
			 fread(&read_inputs_rate, 1, 1, fhandle);
			 fread(&write_outputs_rate, 1, 1, fhandle);
			}

			fclose(fhandle);
//		 strcpy(station_list[Station_NUM-1].name,Station_NAME);
		 }
		 else
		 {
			fclose(fhandle);
			DisplayMessageT(10, 7, 70, 11, NULL, " Old configuration file! Created a new one. ",NULL, Black, NULL, 4000);
			init_boards_struct();
		 }
	 }
	 else
	 {
		 fclose(fhandle);
		 remove("config.cnf");
		 init_boards_struct();
	 }
	}
	else
	{
		 init_boards_struct();
	}
//	ind_station=1;
//	strcpy(Station_NAME,"Station 1       ");
//	Station_NUM=1;
	strcpy(station_name, Station_NAME);
	station_num=Station_NUM;
	local_panel=1;
	networkaddress = NetworkAddress;
	Panel_Info1.panel_type   = Panel_Type;
	Panel_Info1.panel_number = Station_NUM;
	Panel_Info1.network      = NetworkAddress;
	Panel_Info1.version      = Version;
	memcpy(Panel_Info1.network_name, NetworkName, sizeof(Panel_Info1.network_name));
	memcpy(Panel_Info1.panel_name, Station_NAME, sizeof(Panel_Info1.panel_name));
	Panel_Info1.active_panels = (1L<<(Station_NUM-1));
	panel_info1 = Panel_Info1;
#endif
#ifdef WORKSTATION
	strcpy(station_name, "Station 1       ");
	station_num=1;
	local_panel=0;
#endif
 memset(&passwords,'\0',sizeof(passwords));
//**************
// strcpy(passwords.passwords[0].name,"");
// strcpy(passwords.passwords[0].password,supervisor);
// passwords.passwords[0].access_level=0;
// passwords.ind_passwords = 1;
 access_level=0;
//**************

 if( (fhandle=fopen("config.cnf","rb+"))!=NULL)
 {
//		 fseek(fhandle,20+MAX_BOARDS*sizeof(Board_info)+3*sizeof(Comm_Info)+sizeof(ModemCapabilities)+64*5+13,SEEK_SET);
		 fseek(fhandle,CNF_STATION_LIST,SEEK_SET);

		 {
			fread(station_list,sizeof(Station_point),MAX_STATIONS,fhandle);
		 }
		 fread(&passwords.ind_passwords,2,1,fhandle);
		 fread(passwords.passwords,sizeof(Password_point),passwords.ind_passwords,fhandle);
//		 fread(input_buffer,sizeof(struct input_buffer),MAX_INPUT_BUFFER,fhandle);
		 fclose(fhandle);
 }

 strcpy(station_list[Station_NUM-1].name,Station_NAME);
// station_list[Station_NUM-1].version = Version;
/*
 asm {
	mov ah,0bh
	mov bh,0
	mov bl,9
	int 10h
	}
*/
// mouse_installed();

// move_mouse(17,1);

	hide_pointer();

	for(i=0; i<4; i++)
	{
	 if( comm_info[i].connection == MOUSE_LINK )
	 {
		 comm_info[i].connection = 0;
		 comm_info[i].baudrate = 38400L;
	 }
	}
	mouseint();

/*   FEB 28     97
	for(i=COM1; i<=COM4; i++)
	{
	 if(comm_info[MOUSE_COMM_ENTRY].port_name!=i && comm_info[i].connection!=RS485_LINK)
	 {
	  OUTPUT( ISA_uarts[i] + MODEM_CONTROL_REGISTER, 0 );
	  OUTPUT( ISA_uarts[i] + INTERRUPT_ENABLE_REGISTER, 0 );
	 }
	}
*/
/*
#ifndef WORKSTATION
	if(!Station_NUM)
	{
	 strcpy(Station_NAME, "OPERATOR");
	 Station_NUM=1;
	 if( access_level==0)
	 {
		boardconfig();
	 }
	 else
	 {
		control=0;
	 }
	logout=1;
	strcpy(station_list[Station_NUM-1].name,Station_NAME);
	strcpy(station_name, Station_NAME);
	station_num=Station_NUM;
	local_panel=1;
	}
#endif
//setvectint8 = 0;


	ser_list.state = IDLE;
#ifdef NETWORK_COMM
	operator_list.state = IDLE;
	direct_point.state = DIRECT_IDLE;
#endif
	Station_point *stp;
	for(i=0,stp=station_list; i < 32; stp++,i++)
		{
		 if(i+1!=Station_NUM)
			 stp->state = 0;
		 else
		 {
			 stp->state = 1;
			 strcpy( stp->name, Station_NAME );
		 }
		 stp->des_length = 0;
		}
*/
 {
	GWindow D(mode_text?20:200, mode_text?7:150, mode_text?60:500, mode_text?11:200, NO_STACK,0);
//	GWindow *D=NULL;
	oldrive=getdisk();
	getcwd(oldpath,60);
	if(oldpath[strlen(oldpath)-1]=='\\') oldpath[strlen(oldpath)-1]=0;
	if(!ptr_panel)
	{
		ptr_panel = new Panel();

	  updatetimevars();
		resume(VIRTUAL);
	  resume(DIAL);

		if(!ptr_panel)
		{
			mxyputs(10,10,"Not enough memory!");
			exit(0);
		}

		if(cnf_version < 140)
		{
			save_config(CNF_ALL);
			cnf_version = Version;
		}

#ifndef WORKSTATION
	if(!Station_NUM)
	{
	 strcpy(Station_NAME, "PANEL1");
	 Station_NUM=1;
	 if( control )
	 {
		boardconfig();
	 }
	 logout=1;
	 strcpy(station_list[Station_NUM-1].name,Station_NAME);
	 strcpy(station_name, Station_NAME);
	 station_num=Station_NUM;
	 local_panel=1;
	}
#endif
//setvectint8 = 0;

	ptr_panel->GlPanel=station_num;
	ptr_panel->GlNetwork = networkaddress;

#ifdef NETWORK_COMM
	operator_list.state = IDLE;
	direct_point.state = DIRECT_IDLE;
#endif
	Station_point *stp;
	for(i=0,stp=station_list; i < MAX_STATIONS; stp++,i++)
		{
		 if(i+1!=Station_NUM)
			 stp->state = 0;
		 else
		 {
			 stp->state = 1;
			 strcpy( stp->name, Station_NAME );
		 }
		 stp->des_length = 0;
		}

		if(logout)
		{
		 save_config(CNF_ALL);
		 logout = 0;
		}
		resume(NETTASK);
#ifdef NETWORK_COMM
		user.state = REQUEST_HOSTS_NAMES;
		if(tasks[NETWORK].status!=DEAD)
		{
//			DisplayMessage(20, 7, 60, 11, "  Connecting to network...  ",&D, Blue);
			DisplayMessageT(20, 7, 60, 11, NULL, "  Connecting to network...  ", NULL, Blue, &D);
			resume(NETWORK);
			suspend(PROJ);
		}
		if( Netbios_state != NB_INSTALLED )
		{
			kill_task(NETWORK);
		}
		else
		{
			while( user.state != RECEIVED_NAMES && user.state != NO_NAMES );
		}
#endif
#ifdef NET_BAC_COMM
/*
		pnet = NULL;
		pnet = new NetBios_Bac( &Panel_Info1, (byte)NETWORK1 );

		if( pnet->state != DRIVER_INSTALLED )
		{
			delete pnet;
			pnet = NULL;
		}
		else
		{
			DisplayMessageT( 20, 6, 60, 10, NULL, "   NetBios detected...", NULL, Blue, &D);
			delay(3000);
		}
*/
		pipx = NULL;
		if( IPX_enabled )
		{
		 pipx = new IPX( &Panel_Info1, (byte)NETWORK1 );

		 if( pipx->state != DRIVER_INSTALLED )
		 {
			delete pipx;
			pipx = NULL;
		 }
		 else
		 {
			DisplayMessageT( 20, 6, 60, 10, NULL, "  Network driver detected...", NULL, Blue, &D);
			delay(1000);
		 }
    }
#endif
	}
//	if(D) DeleteMessage(D);
	D.GReleaseWindow();

/*
#ifdef NET_BAC_COMM
	if( pipx  != NULL )
	{
		if( pipx->state == DRIVER_INSTALLED )
		{
			for(int j=0; j<MAX_Routing_table ; j++)
			{
				if( !Routing_table[j].status )
				{
					pipx->routing_entry = j;
					Routing_table[j].ptr = pipx;
					Routing_table[j].Port.address = Station_NUM;
					Routing_table[j].Port.network = NetworkAddress;
					Routing_table[j].status = IPX_ACTIVE;
					Routing_table[j].task = NETWORK1;
					((ConnectionData*)Routing_table[j].ptr)->task_number = NETWORK1;
					Routing_table[j].port_status_vars.task = NETWORK1;
					Routing_table[j].port_status_vars.connection = IPX_CONNECTED;
					break;
				}
			}
			NET_EXIT = 0;
			resume(NETWORK1);
			task_switch();
		}
	}
#endif
*/

//	resume(MSTP_MASTER);

//	if( XMS_installed() ) extended_memory = TRUE;

#ifdef NETWORK_COMM
	if( Netbios_state == NB_INSTALLED && panels_number )
	{
	 ind_station = (int)panels_number;
//	 if(extended_memory)
	 {
//		DisplayMessage(20, 7, 60, 11, " Reading descriptors... ",&D);
		DisplayMessageT(20, 7, 60, 11, ctrlbreak_text, " Reading descriptors... ", NULL, Black, &D);
		int net_length=0;
		for(i=0,Station_point *p=station_list; p < &station_list[MAX_STATIONS]; p++,i++)
//		for(i=0;i<32;i++)
		 if(p.state && Station_NUM!=i+1)
			 net_length += p.des_length;
		Des = new XmsDes(net_length);
		for(i=0;i<MAX_STATIONS;i++)
		if(Station_NUM!=i+1)
		 if(station_list[i].state)
			{
				for(int j=0;j<=AY;j++)
				 if(point_des[j]>=0)
					{
					 Delay(100);
					 net_call(47, j+1, Des->buffer, 0, i+1);
					 int l;
//					 Des->put(i+1,point_des[j],operator_list.length);
					 Des->put(i+1,j,operator_list.length);
					}
//				operator_list.state = END;
//				resume(NETWORK);
//				suspend( PROJ );
//				while( operator_list.state != DONE && operator_list.state != ERROR );
			}
//			else
//			 station_list[i].name[0]=0;
//			if(D) DeleteMessage(D);
			 D.GReleaseWindow();
	 }
	}
#endif
 }
	 if(!console_mode)
	 if(!LOADPRG)
	 {
		tempbuf[0] = 0;
		strcpy(tempbuf, ptr_panel->Program_Path);
		if(strlen(tempbuf)) strcat(tempbuf,"\\");
		strcat(tempbuf, ptr_panel->Default_Program);
		ptr_panel->loadprg(tempbuf, &Panel_Info1, ptr_panel->table_bank, 1, control);
		LOADPRG=1;
	 }

	G.GShowMenuBar(message,listonscreen);
	G.ShowunderMBar();
	install_port();

	main_screen = 0x02;

//	 Bordergr(1, 1, 80, 25, Blue1, White, Black, Blue1, 3, 0);
	 while(!exit_apl)
	 {
	  int x,y;
		set_semaphore_dos();
		if( (h=fopen("T3000.TIF","r")) != NULL )
		{
		 fclose(h);
		 clear_semaphore_dos();
		 if( mode_text )
		 {
			ptr_panel->go_graphic(1);
		 }
/*
		if(mode_text )
		{
		 mode_text = MODE_GRAPHIC;
		 hide_pointer();
		 restorechar();
		 setgraphmode(getgraphmode());
		 msettextstyle(SMALL_FONT, 0, 5);
		 Green=GREEN;                 //2
		 White=WHITE; 						 //5
		 Darkgray=DARKGRAY;                 //6
		 Brown=BROWN;           //8
		 Lightblue=LIGHTBLUE;         //9
		 Magenta=MAGENTA;                 //15
		 asm {
			mov ax,21h
			int 33h
		 }
		}
*/
		 hide_pointer();
		 rgb pal1[16];
/////  delete next line
		 delay(2000);
		 set_semaphore(&screen);
		 grp_current_pal=(rgb *)pal1;
		 tif("T3000.TIF",0,0,maxx,maxy);
		 Darkgray=closest_rgb( init_pal[Darkgray], grp_current_pal, 16);
//		set16( init_pal, 0 );
		 clear_semaphore(&screen);
		 display_pointer();
		}
		else
		{
		 clear_semaphore_dos();
		 Bordergr(1, 1, 80, 25, Blue1, White, Black, Blue1, 3, 0);
    }
/*
		if(ex_apl==1)
		{
		x=3;y=2;
		Bordergr(x, y, x+30, y+7, Lightred, Black, Black, Lightred, 3, 0);
		mxyputs( x+2, y+1,  "Real Time facilities", Black, White);
		Delay(50);
		x += 2; y += 2;
		Bordergr(x, y, x+30, y+7, Lightcyan, Blue, Black, Lightred, 3, 0);
		mxyputs( x+2, y+1,  "Compiler and editor", Blue, White);
		Delay(50);
		x += 2; y += 2;
		Bordergr(x, y, x+30, y+7, Black, Red, Black, Lightred, 3, 0);
		mxyputs( x+2, y+1,  "Serial communication", Red, White);
		Delay(50);
		x += 2; y += 2;
		Bordergr(x, y, x+30, y+7, Cyan, Darkgray, Black, Lightred, 3, 0);
		mxyputs( x+2, y+1,  "Modem communication", Darkgray, White);
		Delay(50);
		x += 2; y += 2;
		Bordergr(x, y, x+30, y+7, Black, Lightblue, Black, Lightred, 3, 0);
		mxyputs( x+2, y+1,  "Network communication", Lightblue, White);
		Delay(50);
		x += 2; y += 2;
		Bordergr(x, y, x+30, y+7, Lightgreen, Lightgray, Black, Lightred, 3, 0);
		mxyputs( x+2, y+1,  "Database interface", Lightgray, White);
		Delay(50);
		x += 2; y += 2;
		Bordergr(x, y, x+30, y+7, Lightcyan, Cyan, Black, Lightred, 3, 0);
		mxyputs( x+2, y+1,  "Graphical processes", Cyan, White);
		Delay(50);
		x += 2; y += 2;
		Bordergr(x, y, x+30, y+7, Lightblue, Blue, Black, Lightred, 3, 0);
		mxyputs( x+2, y+1,  "Graphic user interface", Blue, White);
	  }
*/
	  ex_apl=0;
	  get_access();
	  memcpy(Password, password, sizeof(Password));
	  memcpy(User_name, user_name, sizeof(User_name));
	  if(default_group)
	  {
		itoa(default_group, tempbuf, 10);
		for(i=0;i<strlen(tempbuf); i++)
		{
		 input_buffer[i+4].key.i=tempbuf[i];
		}
		input_buffer[i+4].key.i=13;
		simulate=1;
		ind_input_buffer=0;
	  }

	  if( interface_mode && !mode_text )
	  {
		 ptr_panel->go_text();
	  }
	  if( !interface_mode && !mode_text )
	  {
		 ptr_panel->go_graphic(2);
		 set16( init_pal, 0 );
		 Darkgray=DARKGRAY;                 //6
	  }
/*
	  if(!mode_text && interface_mode)
	  {
			lat_char_n = 1;
			lung_char_n = 1;
			Green=LIGHTBLUE;                 //2
			Green1=WHITE; 						 //5
			Blue1=DARKGRAY;                 //6
			Darkgray=BROWN;           //8
			Lightblue=GREEN;         //9
			White=MAGENTA;                 //15
			fond_color=TEXT_FOND_COLOR;
			mode_text = MODE_TEXT;
			hide_pointer();
			cleardevice();
		  restorecrtmode();
		  changechar();
		  setregister(1);
		  asm {
				mov ax,21h
				int 33h
			}
		  setmousetext();
		  move_mouse(30,20);
		  mclrscr(1, 1, 80, 25, White);
		  hidecur();
		  display_pointer();
	  }
*/
	  repeat();
//	Bordergr(1, 1, 80, 25, Blue1, White, Black, Blue1, 3, 0);
	 }   //while

	if(qtt)
	{

#ifndef WORKSTATION
	kill_task(VIRTUAL);
#endif

/*
		present_analog_monitor=0;
		save_monitor = 0x01 | 0x02;
		save_monitor_command = 1;
		save_m();
*/
		if(Des)
		{
		 delete Des;
		 Des = 0;
		}


/*
		present_analog_monitor=0;
		save_monitor = 0x01 | 0x02;
		save_monitor_command = 1;
		resume(AMONITOR);
		task_switch();
*/

		suspend(AMONITOR);
//		kill_task(AMONITOR);

		exit_apl=1;
/*
				 if( Netbios_state == NB_INSTALLED && number_of_sessions )
				 {
					 operator_list.state = END;
					 resume(NETWORK);
					 suspend(PROJ);
					 while(operator_list.state!=DONE && operator_list.state!=ERROR);

					 if(operator_list.state==ERROR)
							{
								error_net=1;
							}
				 }
///////////////
*/
///////////////
#ifdef NETWORK_COMM
			if( Netbios_state == NB_INSTALLED )
			{
//				 operator_list.name[0]='Z';
				 operator_list.state = EXIT;
				 resume(NETWORK);
				 suspend(PROJ);
				 while(operator_list.state!=DONE && operator_list.state!=ERROR);

				 if(operator_list.state==ERROR)
							{
//								FClose(fh,obj);
								error_net=1;
//								return ;
							}
///////////////

				 NET_EXIT=1;
				 resume(NETWORK);
				 task_switch();
				 enable();
				 while(pnet) ;
				 kill_task(NETWORK);
			}
#endif

		  NET_EXIT=1;
			desinstalled();

/*
#ifdef NET_BAC_COMM
			if( pipx  != NULL )
			{
				if( pipx->state == DRIVER_INSTALLED )
				{
					 NET_EXIT=1;
					 resume(NETWORK1);
					 task_switch();
					 enable();
					 while(pipx);
					 kill_task(NETWORK1);
				}
			}
#endif
*/

//				 SERIAL_EXIT=1;
//				 resume(SERIAL);
//				 task_switch();
//				 while(ser_p);
//				 kill_task(SERIAL);

//				set_semaphore_dos();
			kill_task(NETWORK1);
			kill_task(MSTP_MASTER);
			kill_task(SERVERTSM);
//		  kill_task(RS485_RECEIVEFRAME);
		  kill_task(DIAL);
/*
				delete ser_rs485;
				ser_rs485 = NULL;

				tasks[SERIAL].count = NULL;
				tasks[SERIAL].wake_up = NULL;
				delete ser_p;
				ser_p = NULL;

				tasks[MODEM].count = NULL;
				tasks[MODEM].wake_up = NULL;
				delete ser_m;
				ser_m = NULL;
*/
		 present_analog_monitor=0;
		 save_monitor = 0x01 | 0x02;
		 save_monitor_command = 1;
		 save_m();

	G.ReleaseMBar();
	}
//	Panel PANEL(STANDARD, COM1, 9600, 'N', 8, 1, A);
//	mxyputs(30, 11, "Saving configuration...", White, Black);
/*
	if( (fhandle=fopen("config.cnf","wb+"))!=NULL)
	 {
		 fwrite(&Station_NUM, 2, 1, fhandle);
		 fwrite(Station_NAME, 16, 1, fhandle);
		 fwrite(&nr_boards, 2, 1, fhandle);

		 fwrite(boards, MAX_BOARDS*sizeof(Board_info), 1, fhandle);
		 fwrite(comm_info, 3 * sizeof(Comm_Info), 1, fhandle);
		 fwrite(&ModemDataBase[0], sizeof(ModemCapabilities), 1, fhandle);

		 fwrite(ptr_panel->Program_Path, 64, 1, fhandle);
		 fwrite(ptr_panel->Descriptor_Path, 64, 1, fhandle);
		 fwrite(ptr_panel->Basic_Path, 64, 1, fhandle);
		 fwrite(ptr_panel->Monitor_Path, 64, 1, fhandle);
		 fwrite(ptr_panel->Graphics_Path, 64, 1, fhandle);
		 fwrite(ptr_panel->Default_Program, 13, 1, fhandle);
		 fwrite(&console_mode, 1, 1, fhandle);
		 fwrite(&number_rings, 1, 1, fhandle);

		 fwrite(station_list,sizeof(Station_point),32,fhandle);
		 fwrite(&passwords.ind_passwords,2,1,fhandle);
		 fwrite(passwords.passwords,sizeof(Password_point),passwords.ind_passwords,fhandle);
//		 if(def_macro)
//			 input_buffer[ind_input_buffer].key.key[0] = '$';
//		 fwrite(input_buffer,sizeof(struct input_buffer),MAX_INPUT_BUFFER,fhandle);

		 fclose(fhandle);
	 }
*/

//	closegraph();
/*
	asm {
	  mov al,30h
	  out 43h,al
	  mov ax,0
	  out 40h,al
	  mov al,ah
	  out 40h,al
	}
*/
	 if(def_macro)
	 {
		input_buffer[ind_input_buffer].key.key[0] = '$';
		if ((h=fopen("demo.mac","wb+"))!=NULL)
		{
		  fwrite(input_buffer,sizeof(struct input_buffer),MAX_INPUT_BUFFER,h);
		  fclose(h);
		}
    }
 disable();
 asm {						//restore initial resolution
	  mov al,34h
	  out 43h,al
	  mov ax,0
	  out 40h,al
	  mov al,ah
	  out 40h,al
 }
 enable();

		pfarfree(heap_buf_handle);
//		pfarfree(heap_array_handle);
//		pfarfree(heap_dmon_handle);
//		pfarfree(heap_grp_handle);
		pfarfree(heap_amon_handle);
		if( ptr_input_buffer )
		{
			mfarfree(ptr_input_buffer);
	   }

		if( updatebuffer )
			 delete updatebuffer;
		if(ptr_panel) delete ptr_panel;

		points_icon[AMON].~icon();
		points_icon[PRG].~icon();
		points_icon[WR].~icon();

		enable_ints=1;
		reset_PIC_mask(0);
		exit_proj();
//		kill_task(PROJ);
}


/*
void portconfig(void)
{
 set_semaphore_dos();
 GWDialog *D = new GWDialog(20,6,60,16,NO_STACK,0);
 clear_semaphore_dos();
 D->GWSet("Communications",Lightgray,Darkgray);
 D->GShowWindow(DIALOG);

 D->GWPuts(1,14,"PORT   IRQ   Rate",Lightgray,Black);

 D->GWPuts(3,3,"Serial   : ",Lightgray,Black);
 D->GWPuts(4,3,"Modem    : ",Lightgray,Black);
 D->GWPuts(5,3,"Mouse    : ",Lightgray,Black);
 D->GWPuts(6,3,"Printer  : ",Lightgray,Black);

 char port[5],irq[5],brate[10];
 strcpy(port,"com ");
 strcpy(irq,"irq ");
 for(int i=0;i<2;i++)
 {
	port[3] = 0x31 + comm_info[i].port_name;
	D->GWPuts(3+i, 14, port, Cyan, Black);
	irq[3] = 0x30 + comm_info[i].int_name;
	D->GWPuts(3+i, 20, irq, Cyan, Black);
	for(int j = 0; j< 5;j++)
	if ( comm_info[i].baudrate == rate[j])
		break;
	if( j==5) j=0;
	itoa(rate[j], brate, 10);
	D->GWPuts(3+i,26, brate, Cyan, Black);
 }

 D->GDDef_object(sport,14,3,4,Cyan,Black);
 D->GDDef_object(mport,14,4,4,Cyan,Black);
 D->GDDef_object(sirq,20,3,4,Cyan,Black);
 D->GDDef_object(mirq,20,4,4,Cyan,Black);
 D->GDDef_object(srate,26,3,4,Cyan,Black);
 D->GDDef_object(mrate,26,4,4,Cyan,Black);

 while(!D->HandleEvent());
 set_semaphore_dos();
 if(D) delete D;
 clear_semaphore_dos();

 ModemDataBase[0].initial_baud_rate = comm_info[1].baudrate;
 if( modem_active )
 {
		ser_p->modem_port->Set( comm_info[1].baudrate );
 }
 else
 {
		ser_p->ser_port->Set( comm_info[0].baudrate );
 }

}
*/

//void showcommon(int lx,int ly,int rx,int ry,Panel *p, int type = 0)
void showcommon(int lx,int ly,int rx,int ry,Panel *p)
{
// ********  the old code  ********
// GWDialog *D = new GWDialog(lx+2,ly+3,rx-2,ly+6,NO_STACK,0);
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.5 NO.059  ********
// ********       begin       ********
// ***********************************
 GWDialog *D = new GWDialog(201,"need_help",lx+2,ly+3,rx-2,ly+6,NO_STACK,0);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.5 NO.059  ********
// ********        end        ********
// ***********************************

 D->GWSet("File Path",Lightgray,Darkgray);
// D->save = 0;
 D->GShowWindow(DIALOG);
 D->GWPuts(1,2,"Directory   :",Lightgray,Black);
 D->GDDef_object(NULL,16,1,45,Cyan,Black,p->Program_Path,Blue,White);
 while(!D->HandleEvent());
 if(D) delete D;
 strcpy(p->Descriptor_Path, p->Program_Path);
 strcpy(p->Basic_Path, p->Program_Path);
 strcpy(p->Monitor_Path, p->Program_Path);
 strcpy(p->Graphics_Path, p->Program_Path);

/*
// set_semaphore_dos();
 GWDialog *D = new GWDialog(lx+2,ly+3,rx-2,ly+6,NO_STACK,0);
// clear_semaphore_dos();
 D->GWSet(NULL,Lightgray,Darkgray);
 D->save = 0;
 D->GShowWindow(DIALOG);
 D->GWPuts(1,2,"Directory      :",Lightgray,Black);
 D->GDDef_object(NULL,19,1,40,Cyan,Black,p->Program_Path,Blue,White);
 if(type)
	 while(!D->HandleEvent());
 else
	 D->GReleaseWindow();
// set_semaphore_dos();
 if(D) delete D;
// clear_semaphore_dos();

 strcpy(p->Descriptor_Path, p->Program_Path);
 strcpy(p->Basic_Path, p->Program_Path);
 strcpy(p->Monitor_Path, p->Program_Path);
 strcpy(p->Graphics_Path, p->Program_Path);
*/
}

//void showseparate(int lx,int ly,int rx,int ry,Panel *p, int type = 0)
void showseparate(int lx,int ly,int rx,int ry,Panel *p)
{
// ********  the old code  ********
// GWDialog *D = new GWDialog(lx,ly,rx,ry,NO_STACK,0);
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.5 NO.060  ********
// ********       begin       ********
// ***********************************
 GWDialog *D = new GWDialog(201,"need_help",lx,ly,rx,ry,NO_STACK,0);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.5 NO.060  ********
// ********        end        ********
// ***********************************
 D->GWSet("File Paths",Lightgray,Darkgray);
// D->save = 0;
 D->GShowWindow(DIALOG);

 D->GWPuts(1,2,"Programs       :",Lightgray,Black);
 D->GWPuts(2,2,"Descriptors    :",Lightgray,Black);
 D->GWPuts(3,2,"Control Basic  :",Lightgray,Black);
 D->GWPuts(4,2,"Monitor Data   :",Lightgray,Black);
 D->GWPuts(5,2,"Graphics       :",Lightgray,Black);

 D->GDDef_object(NULL,19,1,45,Cyan,White,p->Program_Path,Blue,White);
 D->GDDef_object(NULL,19,2,45,Cyan,White,p->Descriptor_Path,Blue,White);
 D->GDDef_object(NULL,19,3,45,Cyan,White,p->Basic_Path,Blue,White);
 D->GDDef_object(NULL,19,4,45,Cyan,White,p->Monitor_Path,Blue,White);
 D->GDDef_object(NULL,19,5,45,Cyan,White,p->Graphics_Path,Blue,White);
 while(!D->HandleEvent());
 if(D) delete D;
/*
// set_semaphore_dos();
 GWDialog *D = new GWDialog(lx+2,ly+11,rx-2,ly+18,NO_STACK,0);
// clear_semaphore_dos();
 D->GWSet("File Paths",Lightgray,Darkgray);
 D->save = 0;
 D->GShowWindow(DIALOG);

 D->GWPuts(1,2,"Programs       :",Lightgray,Black);
 D->GWPuts(2,2,"Descriptors    :",Lightgray,Black);
 D->GWPuts(3,2,"Control Basic  :",Lightgray,Black);
 D->GWPuts(4,2,"Monitor Data   :",Lightgray,Black);
 D->GWPuts(5,2,"Graphics       :",Lightgray,Black);

 D->GDDef_object(NULL,19,1,40,Cyan,Black,p->Program_Path,Blue,White);
 D->GDDef_object(NULL,19,2,40,Cyan,Black,p->Descriptor_Path,Blue,White);
 D->GDDef_object(NULL,19,3,40,Cyan,Black,p->Basic_Path,Blue,White);
 D->GDDef_object(NULL,19,4,40,Cyan,Black,p->Monitor_Path,Blue,White);
 D->GDDef_object(NULL,19,5,40,Cyan,Black,p->Graphics_Path,Blue,White);
 if(type)
	 while(!D->HandleEvent());
 else
	 D->GReleaseWindow();

// set_semaphore_dos();
 if(D) delete D;
// clear_semaphore_dos();
*/
}

void Panel::Path()
{
 int i;
 i=dialog_select( 2, (char *)array_sel_path, 0, 32, 7, Lightgray, Darkgray, "Path");  // 0=don't save
 if(i>=0)
 {
	if (i==0)
	{
	 showcommon(6,5,76,10,this);
	}
	if (i==1)
	{
	 showseparate(6, 7, 76, 15, this);
	}
 }

/*
 int lx = 6, ly = 3, rx = 76, ry = 22;
 hot_box h1,h2;
 h1.top.x = h1.bot.x = lx+4;
 h1.top.y = h1.bot.y = ly+1;
 h2.top.x = h2.bot.x = lx+4;
 h2.top.y = h2.bot.y = ly+9;

 hide_pointer();
 Bordergr(lx, ly, rx, ry, Blue, Lightblue, White, White, 1, 0);
 PutCheckBox(lx+4, ly+1, "Common directory",  White, Lightblue, Black);
 PutCheckBox(lx+4, ly+9, "Separate directory", White, Lightblue, Black);

 showcommon(lx,ly,rx,ry,this);
 showseparate(lx, ly, rx, ry, this);

 int esc=0 ;
 int onedir = 0, dir = 0;
 while(1)
 {
	MouseStatus stat;
	union {
		int i;
		char ch[2];
		} key;
	if (bioskey_new(1) || esc )                //kbhit())
	{
	 if(!esc)
		key.i = bioskey_new(0);
	 if (key.ch[0] == 27 || esc)
		 {
			hide_pointer();
			lin_text[rx-lx+3]=0;
			for(int i=2;i<=25;i++)
			{
			 mxyputs(lx-1,i,lin_text,fond_color,Black);
			}
			lin_text[rx-lx+3]=lin_text[0];
			display_pointer();
			return ;
		 }
	 if (key.ch[0] == 0 && key.ch[1] == 0x2E)
	 {
		 onedir = 1;
	 }
	 if (key.ch[0] == 0 && key.ch[1] == 0x1F)
	 {
		 onedir = 2;
	 }
	}
	mouse_status(stat);
	if( (stat.leftButton && (mouse_inside(h1.top.x,
		 h1.top.y, h1.bot.x, h1.bot.y) || mouse_inside(lx+2,ly+3,rx-2,ly+6))) || onedir==1)
		{
		 UnCheckBox(lx+4, ly+9, White, Black);
		 CheckBox(lx+4, ly+1, White, Black);
		 dir = 1;
		 showcommon(lx, ly, rx, ry, this,1);
		 showseparate(lx, ly, rx, ry, this);
		 showcommon(lx, ly, rx, ry, this);
		 UnCheckBox(lx+4, ly+1, White, Black);
		 onedir = 0;
		}
	 if( (stat.leftButton && (mouse_inside(h2.top.x,
		 h2.top.y, h2.bot.x, h2.bot.y) || mouse_inside(lx+2,ly+11,rx-2,ly+18))) || onedir==2)
		{
		 UnCheckBox(lx+4, ly+1, White, Black);
		 CheckBox(lx+4, ly+9, White, Black);
		 dir = 0;
		 onedir = 0;
		 showseparate(lx, ly, rx, ry, this,1);
		 showseparate(lx, ly, rx, ry, this);
		 showcommon(lx, ly, rx, ry, this);
		 UnCheckBox(lx+4, ly+9, White, Black);
		}
 }
*/
 if(Program_Path[strlen(Program_Path)-1] == '\\')  Program_Path[strlen(Program_Path)-1]=0;
 if(Descriptor_Path[strlen(Descriptor_Path)-1] == '\\')  Descriptor_Path[strlen(Descriptor_Path)-1]=0;
 if(Basic_Path[strlen(Basic_Path)-1] == '\\')  Basic_Path[strlen(Basic_Path)-1]=0;
 if(Monitor_Path[strlen(Monitor_Path)-1] == '\\')  Monitor_Path[strlen(Monitor_Path)-1]=0;
 if(Graphics_Path[strlen(Graphics_Path)-1] == '\\')  Graphics_Path[strlen(Graphics_Path)-1]=0;
}

/***************************************************/

/*
void ChangeDir(void)
{
 char drv[3],dr[40],nm[9],ext[4];
 BOOLEAN out=0;
 int col;


 mtextcolor(Black);


 GWDialog D(20,4,60,15,NO_STACK,0);

 D.GWSet("Change Directory",Lightgray,MAGENTA);

 D.GShowWindow(DIALOG);

 D.GWPuts(1,2,"New directory:",Lightgray,Black);

 char * dir;

 dir=new char[60];

 do
 {
	D.GDGets(dir,2,2,20,Lightblue,White);
	if(strlen(dir)==0)
		{
		 delete [] dir;
		 D.GReleaseWindow();
//		 textcolor(col);
		 return;
		}

//	bar(5+19*textwidth(" "),                410+textheight("H"),
//		 6+(19+strlen(wkdir))*textwidth(" "),410+textheight("H")*2);

	fnsplit(dir,drv,dr,nm,ext);
	int i;
	setdisk(toupper(drv[0])-'A');
	i=strlen(dr);

	strcpy(wkdir,drv);

	if(i!=0)
		dr[i-1]=0;

	strcat(wkdir,dr);

	if(chdir(dr)==-1)
	 {
		DisplayError("Invalid name");
		out=0;
		}
	else out=1;
 }while(!out);

 delete [] dir;
 D.GReleaseWindow();
 mtextcolor(Black);
 mgotoxy(50,19);
 puts(wkdir);
// textcolor(col);


};
*/


void Panel::select_panel(int type)
{
/*
		RS232Error error;
		int l1, st, net;
		unsigned char tbl_bank1[MAX_TBL_BANK];
		Panel_info1 panel_info1;
		char default_prg1[13];
		GGrid *wgrid;
		hide_pointer();
//		Bordergr(10, 3, 70, 25, Blue, Lightblue, White, White, 1, 0);
//		if(type==STATION)
//			mxyputs(11,24,"       ENTER - edit mod        DEL - delete               ",Lightgray,Black);
//		else
//			mxyputs(11,24,"            ENTER - select control station                ",Lightgray,Black);

		if(type==STATION)
			wgrid=new GGrid(22,4,58,22,GRID,NULL,type,GlPanel_type,GlPanel,GlNetwork);
		else
			wgrid=new GGrid(29,6,54,24,GRID,NULL,type,GlPanel_type,GlPanel,GlNetwork);
		if(!mode_text)
		{
				wgrid->ltop.x=10;wgrid->ltop.y=30;
				wgrid->rbottom.x=630;wgrid->rbottom.y=425;
				wgrid->save = 0;   //NO_SAVE
		}
		wgrid->GWSet("Select Panel",Lightgray,Darkgray);
		wgrid->GShowGrid();
		while (!wgrid->HandleEvent());
		delete wgrid;

		if(station_num==Station_NUM && networkaddress==NetworkAddress) local_panel=1;
		else local_panel=0;

//		memcpy( tbl_bank, table_bank, sizeof(tbl_bank));
		memcpy( tbl_bank1, tbl_bank, sizeof(tbl_bank1));
		memcpy( default_prg1, default_prg, 13);
		panel_info1 = Panel_Info1;
		st = station_num;
		net = networkaddress;
		if(!local_panel)
		{
		  if( (error=connect_panel_proc())!=SUCCESS )
		  {
			station_num = st;
			networkaddress = net;
			memcpy( tbl_bank, tbl_bank1, sizeof(tbl_bank));
			memcpy( default_prg, default_prg1, 13);
			Panel_Info1 = panel_info1;
//			local_panel=1;
//			memcpy( tbl_bank, table_bank, sizeof(tbl_bank));
//			Panel_Info1.panel_type = Panel_Type;
		  }
		}
		GlPanel = station_num;
		GlNetwork = networkaddress;
//		hide_pointer();
//		clear_color(5, 72, 2, 25, lin_text, fond_color, Black);

		display_pointer();
		if( serial_access && error==SUCCESS && st != station_num )
		{
		  readdes_serial();
		}
*/
}

void select_panel(int type, int net_no, int where)
{
		RS232Error error;
		int l1, st, net;
		unsigned char tbl_bank1[MAX_TBL_BANK];
		Panel_info1 panel_info;
		char default_prg1[13];
		GGrid *wgrid;
		hide_pointer();
//		Bordergr(10, 3, 70, 25, Blue, Lightblue, White, White, 1, 0);
//		if(type==STATION)
//			mxyputs(11,24,"       ENTER - edit mod        DEL - delete               ",Lightgray,Black);
//		else
//			mxyputs(11,24,"            ENTER - select control station                ",Lightgray,Black);

//  memsize();
		if(type==STATION)
			wgrid=new GGrid(22,4,58,22,GRID,NULL,type,ptr_panel->GlPanel_type,ptr_panel->GlPanel,ptr_panel->GlNetwork);
		else
			wgrid=new GGrid(where?25:50,where?4:5,where?50:75,where?(4+16+2):(5+16+2),GRID,NULL,type,ptr_panel->GlPanel_type,ptr_panel->GlPanel,net_no);
//  memsize();
		if(!mode_text)
		{
/*
				wgrid->ltop.x=lx*width_char_size();wgrid->ltop.y=ly*height_char_size();
				wgrid->rbottom.x=rx*width_char_size()-1;wgrid->rbottom.y=(ly+row)*height_char_size()+32;
				wgrid->save = 0;   //NO_SAVE
*/
		}
		wgrid->GWSet("Select Panel",Lightgray,Darkgray);
//  memsize();
		wgrid->GShowGrid();
//  memsize();
		refresh_time = 40;
		while (!wgrid->HandleEvent())
		{
		 if(!refresh_time)
		 {
			 for(int i=0; i<32; i++)
			 {
					if(	(*pactivepanels)&(1L<<i) )
						(wgrid->obj.st->block+i)->state = 1;
			 }
			 int w_orecord = wgrid->w_record;
			 int w_ofield = wgrid->w_field;
			 wgrid->w_nfields = 0;
			 wgrid->t_fields[wgrid->w_lfield-1]=1;
			 wgrid->w_field = 1;
			 wgrid->GGDrawGrid(Black);
			 wgrid->GGHideCur(Black);
			 wgrid->w_record = w_orecord;
			 wgrid->w_field = w_ofield;
			 wgrid->GGShowCur(Black);
 			 refresh_time = 60;
			 print_alarm_word();
		 }
		}
//  memsize();
		delete wgrid;
//  memsize();

//		if(station_num==Station_NUM && networkaddress==NetworkAddress) local_panel=1;
//		if(station_num==Station_NUM && localnetwork(networkaddress) ) local_panel=1;
//		else local_panel=0;

/*
		memcpy( tbl_bank1, tbl_bank, sizeof(tbl_bank1));
		memcpy( default_prg1, default_prg, 13);
		panel_info = Panel_Info1;
		st = station_num;
		net = networkaddress;
		if(!local_panel)
		{
		  if( (error=ptr_panel->connect_panel_proc())!=SUCCESS )
		  {
			station_num = st;
			networkaddress = net;
			memcpy( tbl_bank, tbl_bank1, sizeof(tbl_bank));
			memcpy( default_prg, default_prg1, 13);
			Panel_Info1 = panel_info;
//			local_panel=1;
//			memcpy( tbl_bank, table_bank, sizeof(tbl_bank));
//			Panel_Info1.panel_type = Panel_Type;
		  }
		}
		ptr_panel->GlPanel = station_num;
		ptr_panel->GlNetwork = networkaddress;
//		hide_pointer();
//		clear_color(5, 72, 2, 25, lin_text, fond_color, Black);

		display_pointer();
		if( serial_access && error==SUCCESS && st != station_num )
		{
			readdes_serial();
		}
*/
}

/*
void pselect(GWDialog *D)
{
 D->GDGets(&ptr_panel->panel_name[D->index_cur][0],(D->index_cur)%16,4+((D->index_cur)/16)*24,20,Blue,White);
}
*/


//void far * far _graphgetmem(unsigned size)
//{
//			 char far *p;
//			 char huge *q;
//			 mfarmalloc((char far **)&p,size);
//			 q = (char huge *)p;
//			 return q;
//				 return farmalloc(size);

//}

/* called by the graphics kernel to free memory */
//void far _graphfreemem(void far *ptr, unsigned size)
//{
//			 mfarfree((char *)ptr);
//}

void Panel::go_graphic(int t)
{
				 G.ReleaseMBar();
				 hide_pointer();
				 if(t!=2)
				 {
				  restorechar();
				  setgraphmode(getgraphmode());
             }
				 mode_text = MODE_GRAPHIC;
				 lat_char_n = textwidth(" ");
				 lung_char_n = textheight("H");
				 font_type=DEFAULT_FONT;
				 charsize=1;
				 Green=GREEN;                 //2
				 White=WHITE; 						 //5
				 Darkgray=DARKGRAY;                 //6
				 Brown=BROWN;           //8
				 Lightblue=LIGHTBLUE;         //9
				 Magenta=MAGENTA;                 //15
				 fond_color = White;
				 setcolor(Darkgray);
				 setfillstyle(SOLID_FILL,fond_color);
				 bar(0,0,maxx,maxy);
				 prectangle(2,2,maxx-2,maxy-2,Black);
				 setcolor(White);
				 prectangle(1,1,maxx-1,maxy-1,White);
				 setcolor(Black);
				 mouse_installed();
				 G.ltop.x = 3;
				 G.ltop.y = 3;
				 G.rbottom.x = maxx-3;
				 if( G.font == DEFAULT_FONT )
					G.rbottom.y = G.ltop.x + 22;
				 else
					G.rbottom.y = G.ltop.x + 3+6+12+6;
				 G.selectbkgcolour = Lightblue;
				 G.highlight = White;
//				 set_pointer_shape(ARROW);
				 if(!t)
					 G.GShowMenuBar(message,listonscreen);
				 msettextstyle(DEFAULT_FONT, HORIZ_DIR,1);
				 display_pointer();
}

void Panel::go_text(void)
{
//				 G.RestoreArea();
				 G.ReleaseMBar();
				 G.ltop.x = 1;
				 G.ltop.y = 1;
				 G.rbottom.x = 80;
				 G.rbottom.y = 1;

				 hide_pointer();
				 restorecrtmode();
				 changechar();
				 Green=LIGHTBLUE;                 //2
				 Green1=WHITE; 						 //5
				 Blue1=DARKGRAY;                 //6
				 Darkgray=BROWN;           //8
				 Lightblue=GREEN;         //9
             White=MAGENTA;                 //15
				 fond_color=TEXT_FOND_COLOR;
				 setregister(1);
				 mode_text = MODE_TEXT;
				 lat_char_n = 1;
				 lung_char_n = 1;

//				 setpalette(BROWN,8);
//				 setpalette(Green,88);
//				 setpalette(MAGENTA,99);
//				 setbkcolor(Darkgray);
//				 fond_color = Darkgray;

				 mouse_installed();
				 setmousetext();
				 mgotoxy(30,17);
				 clear_color(1, 80, 1, 25, lin_text, fond_color, Black);
/*
					for( int y=1;y<=25;y++)
					{
						mxyputs(1,y,lin_text,fond_color,Black);
					}
*/
				 G.selectbkgcolour = Lightblue;
				 G.highlight = White;
				 G.GShowMenuBar(message,listonscreen);
				 display_pointer();
}

/*
void txms(void)
{
	 int x=mode_text;
	 if(mode_text)
		 ptr_panel->go_graphic();
	moveto(10,10);
			{
			XmsMem pXms;
			pXms.Save(0,0, 400, 400);
			if(pXms.status==1)
				{
				 pXms.Restore(	0,0, 400, 400);
				}
			}
	 if(x)
		 ptr_panel->go_text();
}
*/

int program_routine(int num_point,int point_type,int num_panel,int num_net)
{
//	int i;
	asm push es;
			if(!mode_text)
			{
				lat_char_n = 1;
				lung_char_n = 1;
				Green=LIGHTBLUE;                 //2
				Green1=WHITE; 						 //5
				Blue1=DARKGRAY;                 //6
				Darkgray=BROWN;           //8
				Lightblue=GREEN;         //9
				White=MAGENTA;                 //15
				fond_color=TEXT_FOND_COLOR;
				mode_text = MODE_TEXT;
				hide_pointer();
            cleardevice();
				restorecrtmode();
				changechar();
				setregister(1);
				asm {
					mov ax,21h
					int 33h
					}
				setmousetext();
				move_mouse(30,20);
				display_pointer();
			}

		Str_program_point block;
		if (!local_request(num_panel,num_net))
		{
			Delay(100);
//			i = countlength(20, ((point_type+1)<<8) + num_point-1);
			if( net_call(20, ((point_type+1)<<8)+ num_point-1, (char *)&block, 0 ,num_panel, num_net,NETCALL_RETRY) )
			{
				asm pop es;
				return 1;
			}
		}
		else
			memmove(&block,&ptr_panel->programs[num_point-1],sizeof(Str_program_point));

		if( edit_program(&block, num_point-1, num_panel, num_net) )
		{
		 asm pop es;
		 return 1;
		}

//		if(!local_panel || num_panel!=Station_NUM)
		if (!local_request(num_panel,num_net))
		{
			Delay(100);
			net_call(20+100, ((point_type+1)<<8)+ num_point-1, (char *)&block, 0, num_panel, num_net,NETCALL_RETRY);
		}
		else
			memmove(&ptr_panel->programs[num_point-1], &block, sizeof(Str_program_point));
asm pop es;
}

int icommand(char *buf, int from, byte panel, int network)
{
 char *ptitle,test;
 ptitle = NULL;
 GGrid *wgrid;
 byte var_type,point_type;
 int  num_net,num_point,num_panel;
 int x,n=0;
 if( ispoint(buf,&num_point,&var_type,&point_type,&num_panel,&num_net,network,panel) )
 {

 if( local_request(panel,network) )
 {
		if ( num_net==network )
		 if( rs485port!=-1 && ipxport!=-1 )
		 {
			 num_net=(( class ConnectionData *)Routing_table[rs485port].ptr)->panel_info1.network;
	 		 network = num_net;
		 }
 }

 if( (test=checkpointpresence(num_point,point_type,num_panel,num_net,panel,network))==0 )
		DisplayMessage(20,7,60,11, NULL, panelmis, NULL, Black, NULL, 2500);
 if(test)
		x = checkmaxpoints(num_point,point_type,num_panel,num_net);

 if(num_point<=x && test)
 {
	n=cod_command[point_type];
	if(check_access(point_type, num_point-1)!=R_NA)
	{
	if( (from && (point_type==OUT || point_type==IN || point_type==VAR
							|| point_type==CON)) ||
			(!from && (point_type==OUT || point_type==IN || point_type==VAR
							|| point_type==CON || point_type==PRG || point_type==WR
							|| point_type==AR || point_type==GRP)) )
				{
				 int row;
				 row=1;
				 error_net=0;
				int rx=79,lx=2,stk=GRIDINS;
				switch (point_type) {
				 case GRP:
							lx=13; rx=68;
							break;
				 case PRG:
				 case OUT:
				 case IN:
							stk = GRID;
							break;
				 case CON:
				 case WR:
							break;
				 case VAR:
							lx=9; rx=72;
							break;
				 case AR:
							lx=12; rx=69;
							break;
				 case AMON:
							lx=8;rx=53;
							break;
				 case TBL:
							lx=5;rx=75;
							break;
				 }
//				 set_semaphore_dos();
				 wgrid=new GGrid(lx,6,rx,6+row+2,stk,NULL,point_type,T3000,num_panel,num_net,INDIVIDUAL,num_point,SMALL_FONT,5,1);
//				 clear_semaphore_dos();
				 if(!wgrid->grid_error)
				 {
					if (!error_net)
					{
					if(!mode_text)
					{
						wgrid->ltop.x=lx*width_char_size();wgrid->ltop.y=6*height_char_size();
						wgrid->rbottom.x=rx*width_char_size()-1;wgrid->rbottom.y=(6+row)*height_char_size()+32;
						wgrid->save = 0;   //NO_SAVE
					}
//					wgrid->GWSet(ptitle[point_type],Lightgray,Darkgray);
					wgrid->GWSet(ptitle,Lightgray,Darkgray);
					wgrid->GShowGrid();
					refresh = 1;
//				 refresh_time = ReadTime();
					refresh_time = refresh_time_init;
//				 time_t t;
//				 t = mtime(NULL);
					while (!wgrid->HandleEvent())
					{
							if(!refresh_time)
							{
								 if(wgrid->modify)
										wgrid->GSend();
								 else
										wgrid->GRead();
								 int w_orecord = wgrid->w_record;
								 int w_ofield = wgrid->w_field;

								wgrid->w_nfields = 0;
								wgrid->t_fields[wgrid->w_lfield-1]=1;
								wgrid->w_field = 1;
								wgrid->GGDrawGrid(Black);
								wgrid->GGHideCur(Black);
								wgrid->w_record = w_orecord;
								wgrid->w_field = w_ofield;
								wgrid->GGShowCur(Black);

								refresh_time = refresh_time_init;
							}
					}
				  }
				 }
//				 set_semaphore_dos();
				 delete wgrid;
//				 clear_semaphore_dos();
				 refresh = 0;
				 display_pointer();
				 n=-1;
				 return n;
				}

		 if(from && point_type==PRG)
			 program_routine(num_point,point_type,num_panel,num_net);

		 if(from && point_type==WR)
			 weekly_routine(num_point,num_panel,num_net,INDIVIDUAL);

		 if(from && point_type==AR)
			 annual_routine(num_point,num_panel,num_net,INDIVIDUAL);

		 if(from && point_type==AMON)
		 {
		 amon_routine(num_point,num_panel,num_net,INDIVIDUAL,0,NULL);
		 if(mode_text)
			 {
				G.save=0;
				G.GShowMenuBar(message);
				G.save=1;
				clear_color(1, 80, 2, 25, lin_text, fond_color, Black);
/*
				for( int y=2;y<=25;y++)
				{
					mxyputs(1,y,lin_text,fond_color,Black);
				}
*/
			 }
		 }

		if(from && point_type==GRP)
		{
		 ind_nested_grp=0;
		 memset(&localopenscreen, 0, sizeof(Point_Net));
		 if(grp_proc(num_point, num_panel, num_net, INDIVIDUAL)==27) n=27;
		 if(default_group) n=27;
		}
	 return n;
	}
 }
 else
	if(test)
		DisplayMessage(20,7,60,11, NULL, pointins, NULL, Black, NULL, 2000);
 }
}

int comman_line(int lx, int ly, int rx, int ry, int fond_color, GEdit *edit)
{
 unsigned char tbl_bank1[MAX_TBL_BANK];
 char buf[21];
 int n,j,num_panel,num_net;
 uint l1;
 char pbuf[7];
 char pc[11],*p,*q;
 while(1)
 {
 memset(buf,0,21);
 Bordergr(lx, ly, rx, ry, Black ,Lightgray,fond_color,fond_color,1,0);
 mxyputs(lx+1, (ly+ry)/2," >                                                     ",Lightgray,Black);
 mgotoxy(lx+3,22);
 n = (int)wingets(buf, (ly+ry)/2, lx+3, 20, Lightgray, Black);
 for( int y=ly-1;y<=24;y++)
 {
		mxyputs(1,y,lin_text,fond_color,Black);
 }

 if(n==27)
 {
		 n = -1;
		 break;
 }
 for(int i=0; i<=AY;i++)
 {
	 p = buf;
	 num_net=0;
	 num_panel=0;
	 if ( (q=strchr(buf,'.'))!=NULL )
	 {
		memcpy(pc,buf,min( (int)(q-buf),10));
		pc[min((int)(q-buf),10)]=0;
		q++;
		num_net = atoi(pc);
		p = q;
      if(!num_net) continue; 
	 }
	 num_panel = atoi(p);
	 if(num_panel)
	 {
		 j=0;
		 while(p[j])
		 {
			if(!isdigit(p[j])) break;
			j++;
		 }
		 p = &p[j];
	 }
	 else
		if(num_net) continue;
	 strcpy(pbuf,point_cod[i]);
	 strcat(pbuf,"S");
	 if(!strcmp(pbuf,p))
		 break;
 }
 if(i<=AY)
 {
		n=cod_command[i];
//	 ptr_panel->showpoints(n, T3000, station_num, networkaddress);
		if(!num_net) num_net=networkaddress;
		if(!num_panel) num_panel=station_num;
		if(local_request(num_panel,num_net))
		{
			maxtbl = ptr_panel->table_bank[i];
			showpoints(n, T3000, num_panel, num_net);
		}
		else
		{
     j=0;
		 l1 = sizeof(tbl_bank);
		 if( (j=net_call(COMMAND_50, TABLEPOINTS_COMMAND, (char *)tbl_bank1, &l1, num_panel, num_net, NETCALL_NOTTIMEOUT)) != SUCCESS )
			 j=net_call(COMMAND_50, TABLEPOINTS_COMMAND, (char *)tbl_bank1, &l1, num_panel, num_net);
		 if(j==SUCCESS)
		 {
			maxtbl = tbl_bank1[i];
			showpoints(n, T3000, num_panel, num_net);
		 }
		}
/*
	 showpoints(n, T3000, num_panel, num_net, 0, 1);
*/
	 G.GShowMenuBar(message);
 }
 else
 {
	 num_net = networkaddress;
	 if ( (q=strchr(buf,'.'))!=NULL )
	 {
		memcpy(pc,buf,min( (int)(q-buf),10));
		pc[min((int)(q-buf),10)]=0;
		q++;
		num_net = atoi(pc);
		if(num_net)
		{
     memmove(buf, q, strlen(q)+1);
		}
		else
	   num_net = networkaddress;
	 }
	 n=icommand(buf, 1, station_num, num_net);
 }

	if(edit) edit->showedit(edit->beginscreen);
	if(n==27) {n=-1;break;}
 }
 hidecur();
 return n;
}


/*
static unsigned int huge m[100];


unsigned int i=0,j=0;
asm push es

_ES=FP_SEG(&m[0]);
_SI=FP_OFF(&m[0]);
_CX=0;
asm {
	 xor dx,dx
		}
memloop: asm  mov ah,48h
asm {
		 mov bx,0ffffh
		 int 21h
		 or bx,bx
		 jz done
		 add dx,bx
		 mov ah,48h
		 int 21h
		 mov es:[si],ax
		 inc si
		 inc si
		 inc cx
		}
//		m[i++]=(char huge *)MK_FP(j,0);
asm		jmp memloop
done:
asm mov i,cx
	nr=(unsigned long)_DX*16;
	for(j=0;j<i;j++)
	{
	 _ES=m[j];
	asm  mov ah,49h
	asm 	 int 21h
	}
asm pop es
	 mcprintf("total mem 21h : %s \n\r",ltoa(nr,xbuf,10));
*/

int	saveloadpoint(int type, int point_type, int n_points, int size, int panel, int panel_type, FILE *h, char *buf)
{
 int r;
 uint length;
 int n=2;
 length = n_points*size;
// delay(500);
 while(n--)
 {
	if( (r=net_call( type + point_type+1 , 0, buf, &length , panel, networkaddress,NETCALL_RETRY))==SUCCESS ) break;
 }
// Delay(150);
 if( r==SUCCESS )
 {
	if(!type)
	{
	 n = length / size;
	 if( panel_type==MINI_T3000 )
	 {
		if( point_type==OUT )
		 n = MAX_OUTS_MINI;
		if( point_type==IN )
		 n = MAX_INS_MINI;
	 }
	 set_semaphore_dos();
	 fwrite(	&n, 2, 1, h);
	 fwrite(	&size, 2, 1, h);
	 fwrite(	buf, size, n, h);
   clear_semaphore_dos();
	}
 }
 return r;
}

void changechar(int arg)
{
char **p1,*p2,*p3, *p4, *ptext_auxiliary;
int n = 34;
int o=200;

	 if( text == ASCII_FONT) return;
	 if(arg)
	 {
		if((seg_sel.l=GlobalDosAlloc(1000))==0)
		{
		 text=ASCII_FONT;
		 return;
		}
	 }

	 p1 = (char **)MK_FP(__Seg0040,0xa8);
	 SAVE_PTR = *p1;
	 if(arg)
	 {
		_BX = FP_SEG(*p1);
		asm {
		 mov ax,0002h
		 int 31h
		 mov WORD PTR ega_selector, ax
		}
	 }

	 p4 = (char *)MK_FP(ega_selector, FP_OFF(*p1));
	 p3 = (char *)MK_FP(seg_sel.seg_sel.sel, 0);
//	 memcpy(EGA_data_block, p4, 28);
	 memcpy(p3, p4, 32);
	 if(arg)
	 {
		memcpy(p3 + 47, characters_font, sizeof(characters_font));
	 }
//	 *p1 = (char *)EGA_data_block;
//	 p2 = (char *)&EGA_data_block[0] + 8;
	 p2 = p3 + 8;
//	 p3 = (char *)text_auxiliary;
//	 memcpy(p2,&p3,4);
	 p4 = (char *)MK_FP(seg_sel.seg_sel.seg, 34);
	 memcpy(p2,&p4,4);
	 if(arg)
	 {
		ptext_auxiliary = p3 + 34;
		ptext_auxiliary[0] = 16;
		ptext_auxiliary[1] = 0;
		memcpy(&ptext_auxiliary[2],&n,2);
		memcpy(&ptext_auxiliary[4],&o,2);
//	 p3 = characters_font;
		p4 += 13;
//	 memcpy(&text_auxiliary[6],&p3,4);
		memcpy(&ptext_auxiliary[6],&p4,4);
		ptext_auxiliary[10] = 0x0ff;
		ptext_auxiliary[11] = 3;
		ptext_auxiliary[12] = 0x0ff;
	 }
	 *p1 = (char *)MK_FP(seg_sel.seg_sel.seg,0);

	asm {
	 mov ah,0
	 mov al,83h
	 int 10h
	}
}
void restorechar(int arg)
{
char **p1;
	 if( text == ASCII_FONT) return;

	 p1 = (char **)MK_FP(__Seg0040,0xa8);
	 *p1=SAVE_PTR;
	 if(arg)
	 {
		GlobalDosFree(seg_sel.seg_sel.sel);
		asm {
			mov ah,0
			mov al,83h
			int 10h
		}
	 }	
}


int setregister(int set)
{
char GReen,MAgenta,LIghtblue,DArkgray,WHite,BRown;
if(set)
{
 GReen=GREEN;MAgenta=MAGENTA,LIghtblue=LIGHTBLUE,DArkgray=DARKGRAY,WHite=WHITE,BRown=BROWN;
}
else
{
 GReen=LIGHTBLUE;MAgenta=WHITE,LIghtblue=GREEN,DArkgray=BROWN,WHite=MAGENTA,BRown=DARKGRAY;
}

for(char i=0;i<16;i++)
{
 char n=0;
 if(i==GReen)
				 n=1*8+3;
 if(i==MAgenta)
//					 n=7*8+7;
					 n=255;
 if(i==BRown)
					 n=7*8+0;
 if(i==DArkgray)
					 n=3*8+0;
 if(i==WHite)
					 n=5*8+2;
 if(i==LIghtblue)
					 n=0*8+2;

 if(n)
 {
 _BL = i;
 _BH = n;
 asm{
	mov ah,10h
	mov al,0
//	mov bl,i       //registrul
//	mov bh,n
	int 10h
	}
 }
}
/*
 asm{
	mov ah,10h
	mov al,3
	mov bl,0
	int 10h
 }
*/

/*
 _ES = FP_SEG(Black);
 _BX = FP_OFF(Black);
 asm{
	mov ah,10h
	mov al,2
//	mov bl,i       //registrul
//	mov bh,n
	int 10h
*/
}

int setmousetext(void)
{
 if(text)
	 _DX = 251;
 else
	 _DX = 0x00d4;
 asm{
	 mov ax,000ah
	 mov bx,0
	 mov cx,0f000h
//	 mov dx,00d4h
	 int 33h
	}
}

/*
void showgauge(GWindow *w, float coef, float ntot)
{
 int i = ntot / coef;
 if(i)
 {
	lin_read[i]=0;
	w->GWPuts(3,  5, lin_read, Black, White);
	lin_read[i]=lin_read[0];
 }
}
*/

/*
void showgauge(GWindow *w, float coef, long ntot)
{
 long l;
 int i;
 if(w)
 {
	l = (long)(coef*1000);
// int i = ntot / coef;
	i = ntot*1000 / l;
	if(i)
	{
	 lin_read[i]=0;
	 w->GWPuts(3,  5, lin_read, Black, White);
	 lin_read[i]=lin_read[0];
	}
 }	
}
*/
void showgauge(GWindow *w, char *text)
{
 int i;
 if(w)
 {
	w->GWPuts(3,  12, "      ", Black, Black);
	w->GWPuts(3,  12, text, Black, White);
 }
}


void showgauge(GWindow *w, long coef, long ntot)
{
// long l = (long)(coef*1000);
// int i = ntot / coef;
 int i;
 if(w)
 {
	i = ntot*1000 / coef;
	if(i)
	{
	 lin_read[i]=0;
/*
	 if(!mode_text)
	 {
		 set_semaphore(&screen);
		 settextstyle(DEFAULT_FONT, HORIZ_DIR,1);
		 clear_semaphore(&screen);
	 }
*/
	 w->GWPuts(3,  5, lin_read, Black, White);
/*
	 if(!mode_text)
	 {
		 set_semaphore(&screen);
		 settextstyle(font_type,HORIZ_DIR,charsize);
		 clear_semaphore(&screen);
	 }
*/
	 lin_read[i]=lin_read[0];
	}
 }
}

void creategauge(GWindow **gauge, char *buf)
{
//	set_semaphore_dos();
	*gauge = new GWindow(mode_text?25:200,mode_text?7:150,mode_text?55:440,mode_text?14:250,NO_STACK,0);
//	clear_semaphore_dos();
	if(*gauge)
	{
	 (*gauge)->GWSet(NULL, Lightblue, Blue, Blue);
	 (*gauge)->GShowWindow(WIN_ERROR);
	 if(!mode_text)
	 {
		 msettextstyle(DEFAULT_FONT, HORIZ_DIR,1);
	 }
	 (*gauge)->GWPuts(1, (55 - 25 - strlen(buf))/2, buf, Lightblue, White);
	 lin_text[20]=0;
	 (*gauge)->GWPuts(3, 5, lin_text, Black, Black);
	 lin_text[20]=' ';
/*
	 if(!mode_text)
	 {
		 msettextstyle(SMALL_FONT, 0, 5);
	 }
*/
	}
}

void deletegauge(GWindow **gauge)
{
 if(*gauge)
 {
	(*gauge)->GReleaseWindow();
//	set_semaphore_dos();
	delete (*gauge);
	*gauge = NULL;
//	clear_semaphore_dos();
 }
}

void setindexremote(char *buf)
{
	int bytes;
	struct remote_local_list *r;
	int ind_r;
	memcpy(&bytes,buf,2);
	bytes += 2+3;

	bytes += *((int *)(buf+bytes))+2; //local table
	bytes += *((int *)(buf+bytes))+2;  //time on-off

	memcpy(&ind_r, buf+bytes, 2);
	r = (struct remote_local_list *)(buf+bytes+2);
	for(int i=0;i<ind_r;i++,r++)
		r->index = -1;
}

int updateremotepoint(Point_Net point, int network)
{
	if( point.zero() ) return -1;
	if( point.point_type-1 == GRP || point.point_type-1 == AMON ) return -1;
	if( point.network == 0xFFFF ) point.network = network;
  for(int j=0; j < MAXREMOTEPOINTS82; j++)
  {
	 if( remote_points_list[j].info.point == point )
	 {
	  break;
	 }
	}
	if(j==MAXREMOTEPOINTS82)
	{
	for(j=0;j<MAXREMOTEPOINTS82;j++)
	{
	 if( remote_points_list[j].info.point.zero() )
	 {
		memset(&remote_points_list[j].info, 0, sizeof(Point_info));
		remote_points_list[j].info.point=point;
		remote_points_list[j].state = REMOTE_OK;
		remote_points_list[j].read = 1;
    remote_points_OUT++;
		break;
	 }
	}
  }
	if(j==MAXREMOTEPOINTS82)
	{
	 j=0;
	 if( remote_points_list[j].info.point.zero() )
	 {
		memset(&remote_points_list[j].info, 0, sizeof(Point_info));
		remote_points_list[j].info.point=point;
		remote_points_list[j].state = REMOTE_OK;
		remote_points_list[j].read = 1;
	 }
	}
	remote_points_list[j].count++;
//  want_points_list[j].point=point;
//  want_points_list[j].point.network = NetworkAddress;
  return j;
}


void deleteremotepoint(Point_Net point, int network)
{
  if( point.network == 0xFFFF ) point.network = network;
  for(int j=0; j < MAXREMOTEPOINTS82; j++)
  {
	 if(remote_points_list[j].info.point==point)
	 {
	  break;
	 }
  }
  if(j<MAXREMOTEPOINTS82)
  {
	 if( !(--remote_points_list[j].count) )
	 {
		 memset(&remote_points_list[j],0,sizeof(REMOTE_POINTS));
//		 remote_points_list[j].info.point.setzero();
//		 want_points_list[j].point.setzero();
//		 want_points_list[j].destination = 255;
     remote_points_OUT--;
	 }
	}
}

void updateremotepoints(int ind_remote_local_list, struct remote_local_list *remote_local_list)
{
 int j;
 for(int i=0;i<ind_remote_local_list;i++)
 {
	if( (j=updateremotepoint(remote_local_list[i].point,remote_local_list[i].point.network)) >= 0 )
		remote_local_list[i].index=j;
 }
}

void grp_updateremotepoint(Control_group_elements cgrp)
{
  Str_grp_element *p;
  p = cgrp.ptrgrp;
	for(int i=0;i<cgrp.nr_elements;i++,p++)
	if(p->point_info.point.panel+1!=Station_NUM)
	{
	 updateremotepoint(p->point_info.point,p->point_info.point.network);
	}
}

int Panel::loadprg(char *file, Panel_info1 *panel_info, unsigned char *tblbank, int local, int contr)
{
	char *buf,btext[8];
	long length, coef;
	int i,k,m,l1,c1,nitem, ver, vermini, ret, st;
	uint n,j, l;
	Str_program_point *pprg;
							 set_semaphore_dos();
							 buf=new char[7500];   //7000

							 ret = SUCCESS; //ERROR_COMM;
							 st = panel_info->panel_number;
							 if ((h=fopen(file,"rb+"))==NULL)
							 {
								 clear_semaphore_dos();
								 if(contr)
									 DisplayMessageT(20, 7, 60, 11, NULL, " File not loaded! ",NULL, Black, NULL, 1000);
								 onemin = 1;
//								 resume(VIRTUAL);
							 }
							 else
							 {
								 m = 1;
								 fread( buf, 26, 1, h); //time and date
								 fread( buf, 4, 1, h);  //signature
								 if ( !memcmp(buf, signature, 4) )
								 {
									fread(	&n, 2, 1, h);   //panel number
								  fread(	&m, 2, 1, h);   //network number
								  fread(	&ver, 2, 1, h);       //ver T3000
								  fread(	&vermini, 2, 1, h);   //ver mini
								  fread(	buf, 1, 32, h); // reserved bytes
									clear_semaphore_dos();
								  if ( ver < 210 || ver==0x2020 )
								  {
									DisplayMessageT(10, 7, 70, 11, NULL, "File not loaded. File version less then 2.10!",NULL, Black, NULL, 3500);
									m=0;
									}
								 }
								 else
								 {
									clear_semaphore_dos();
									m=0;
									DisplayMessageT(10, 7, 70, 11, NULL, "File not loaded. File corrupt.",NULL, Black, NULL, 3500);
								 }

								 if( n != st && m )
								 {
										strcpy(buf, "File for panel ");
										itoa(n, &buf[strlen(buf)], 10);
										strcat(buf, ". Load as panel ");
//										itoa(station_num, &buf[strlen(buf)], 10);
										itoa(n, &buf[strlen(buf)], 10);
										strcat(buf, " ? (Y/N) : ");
										if(ReadYesNo(15, 9, 75, 13, Lightgray, Darkgray, Black,
													Cyan, White, buf ))
										{
											if(!control)
											{
											 if(local)
											 {
												station_list[Station_NUM-1].state=0;
												station_num = Station_NUM = n;
												strcpy(station_name, station_list[station_num-1].name);
												strcpy(Station_NAME, station_name);
												station_list[station_num-1].state=1;
												ptr_panel->GlPanel=station_num;
												panel_info->panel_number = station_num;
											 }
											 else
                        m=0;
											}
										}
										else
											m = 0;
								 }
								if (m)
								{
#ifndef WORKSTATION
									if(local)
										set_semaphore(&t3000_flag);
//										suspend(VIRTUAL);
#endif
									m=ERROR_COMM;
									if(local)
									{
										clearpanel();
										m=SUCCESS;
									}
									else
									{
										if( (m=net_call(CLEARPANEL_T3000, 0, buf, 0 , st, networkaddress))!=SUCCESS )
											m=net_call(CLEARPANEL_T3000, 0, buf, 0 , st, networkaddress);
										if( m==SUCCESS)
										{
											 loadprgremote=st;
											 DisplayMessageT(20, 7, 60, 11, NULL, " Wait for panel initialization... ", NULL, Blue, NULL, 5000);
											 l = sizeof(tbl_bank);
											 m=net_call(COMMAND_50, TABLEPOINTS_COMMAND, (char *)tblbank, &l, st, networkaddress,NETCALL_RETRY);
										}
									}
								 if(m==SUCCESS)
								 {
									set_semaphore_dos();
									coef = ftell(h);    // save file pointer
									fseek(h, 0, SEEK_END);
									length = ftell(h);
									fseek(h, coef, SEEK_SET);   // restore file pointer
									coef = ((length*1000L)/20000L)*1000L + (((length*1000L)%20000L)*1000L)/20000L ;
//									float coef = (float)length/20.;
									long ltot = 0;
									clear_semaphore_dos();

									creategauge(&gauge,"Loading file");
									strcpy(buf,panel_text1);
									lin_text[10]=0;
									gauge->GWPuts(5, 10, lin_text, Lightblue, Black);
									lin_text[10]=' ';
									itoa(st, &buf[6],10);
									gauge->GWPuts(5, 10, buf, Lightblue, White);

									if(local)
									{
									 present_analog_monitor=0;
									 programs_size = 0;
									 first_free = 0;
									 for(i=0; i < MAX_HEAP_DIGM-1; i++)
										 heap_dmon[i].next = i+1;
									 nsample_mem_dig = 0;
									}

									set_semaphore_dos();
									int max_prg, max_grp;
									for(i=OUT; i<=UNIT; i++)
									{
									 showgauge(gauge, info[i].name);
									 if(i==AMON)
									 {
//										 if( panel_info1.panel_type == MINI_T3000 && panel_info1.version>110
//										 if( panel_info1.version>110 && vermini >= 230  )
										 if( ver>=230 && vermini )
												 continue;
										 if( ver<230 && vermini >= 230 )
										 {
											 delete buf;
											 clear_semaphore_dos();
											 DisplayMessage(12, 7, 68, 11, NULL, "File not loaded. Versions conflict!",NULL, Black, NULL, 5000);
											 return ERROR_COMM;
										 }
									 }

									 if(i==ALARMM)
										if( ver < 216 )
										{
										 fread( &n, 2, 1, h);
										 fread( &nitem, 2, 1, h);
										 fread(	buf, n, nitem ,h);
										 continue;
										}
									 if(i!=DMON && i!=ALARMM)
									 {
										fread( &n, 2, 1, h);
										fread( &nitem, 2, 1, h);
										l = min(n,info[i].max_points);
										if(i==GRP)
											max_grp = n;
										if(i==PRG)
										{
											max_prg = n;
										}
										if(local)
										{
										 if(nitem == info[i].str_size)
										 {
											 fread(	info[i].address, nitem, l ,h);
										 }
										 else
										 {
											 m = min(nitem, info[i].str_size);
											 for(j=0; j<l; j++)
											 {
												 fread(	info[i].address+j*info[i].str_size, m, 1 ,h);
												 if(nitem > info[i].str_size)
														fseek(h, nitem-info[i].str_size, SEEK_CUR);
											 }
										 }
										 if(n > l)
											fseek(h, (n-l)*nitem, SEEK_CUR);
										}
										else
										{
//										 memset(buf,0,7000);
										 fread(	buf, n, nitem ,h);
										 l = min(n,tblbank[i]);
										 if(i==PRG)
										 {
											pprg = (Str_program_point *)buf;
											for(j=0;j<l;j++,pprg++)
											{
											 pprg->bytes = 0;
											}
										 }
										 if( i!=ALARMM )
										 {
											if(i==AMON)
											{
											 if( panel_info->panel_type == T3000 )
											 {
												clear_semaphore_dos();
												if( saveloadpoint(100,i,l,nitem,st,panel_info->panel_type,h,buf) )
													ret = ERROR_COMM;
												set_semaphore_dos();
											 }
											 else
											 {
												if( panel_info->version <= 110 )
												{
												 clear_semaphore_dos();
												 if(saveloadpoint(100,i,l,nitem,st,panel_info->panel_type,h,buf))
													ret = ERROR_COMM;
												 set_semaphore_dos();
												}
											 }
											}
											else
											{
											 clear_semaphore_dos();
											 if(saveloadpoint(100,i,l,nitem,st,panel_info->panel_type,h,buf))
													ret = ERROR_COMM;
											 set_semaphore_dos();
											}
										 }

//										 if(n > l)
//											fseek(h, (n-l)*nitem, SEEK_CUR);
										}
										ltot += n*nitem+2;
										showgauge(gauge, coef, ltot);
									 }
									 if(local)
									 {
										if(i==PRG)
											for(j=0; j < info[i].max_points; j++)
												programs[j].errcode = 0;
										if(i==AMON)
										{
											for(j=0;j < info[i].max_points; j++)
											 for(k=0;k<5;k++)
												monitor_work_data[j].start_index_dig[k] = 0x0FFFF;
											for(j=0;j<info[i].max_points; j++)
											{
											 analog_mon[j].double_flag=1;
											}
											for(j=0;j<info[i].max_points; j++)
												for(k=0;k<analog_mon[j].num_inputs;k++)
												{
												if(analog_mon[j].inputs[k].panel+1!=Station_NUM)
												{
													updateremotepoint(analog_mon[j].inputs[k],analog_mon[j].inputs[k].network);
												}
												}
										}
										if(i==AY)
										{
										 long *p = heap_array;
										 for(j=0; j<info[i].max_points; j++)
										 {
											if(arrays[j].length)
											{
												arrays_data[j] =  p;
												p += arrays[j].length;
											}
											else
											 arrays_data[j] =  0;
										 }
										}
									 }
									}
									clear_semaphore_dos();

									char *p,*q;
									HANDLE handle;
									int n1;
                  handle = 0;
									if(local)
									{
									 ind_heap_buf = 0;
									 memset(heap_buf, 0, MAX_HEAP_BUF);
									 mfarmalloc(&p, PROGRAM_SIZE, handle);
									 if (p==NULL)
									 {
										 mxyputs(10,10,"Error alloc");
										 abort();
									 }
//									for(int i=0;i< MAX_PRGS;i++)
//										 Heap_dealloc(&program_codes[i]);
									}

// load programs code
//									l=min(MAX_PRGS,max_prg);
									btext[0]='P';
									btext[1]='R';
									btext[2]='G';
									btext[3]=' ';
									btext[4]=' ';
									btext[5]=0;
									l = min(max_prg,tblbank[PRG]);
									for(i=0;i< l;i++)
									{
									 itoa(i,&btext[3],10);
									 showgauge(gauge, btext);
									 if(local)
									 {
										set_semaphore_dos();
										fread(	&n, 2, 1, h);
										fread( p, n, 1, h);
										clear_semaphore_dos();
										if(n)
										{
										 q = p;
										 memcpy(&n1, q, 2);
										 q += n1 + 2 + 3;
										 memcpy(&n1, q, 2);
										 q += 2;              //local variables
										 for(j=0;j<n1; )
										 {
											switch(q[j]){
												case FLOAT_TYPE:
												case LONG_TYPE:
													k = 4;
													break;
												case INTEGER_TYPE:
													k = 2;
													break;
												case BYTE_TYPE:
													k = 1;
													break;
												default:
													{
													switch(q[j]){
														case FLOAT_TYPE_ARRAY:
														case LONG_TYPE_ARRAY:
															k = 4;
															break;
														case INTEGER_TYPE_ARRAY:
															k = 2;
															break;
														case BYTE_TYPE_ARRAY:
														case STRING_TYPE:
//														case STRING_TYPE_ARRAY:
															k = 1;
															break;
													 }
													 memcpy(&l1, &q[j+1], 2);
													 memcpy(&c1, &q[j+3], 2);
													 if(l1)
														k *= l1*c1;
													 else
														k *= c1;
													 j += 4;
													}
													break;
											}
											j++;
											memset(&q[j], 0, k);
											j += k;
											j += 1+strlen(&q[j]);
										 }
										 q += n1;
										 memcpy(&n1, q, 2);   //time
										 q += 2+n1;
										 memcpy(&n1,q,2);    //ind_remote_local_list
										 q += 2;         //remote_local_list
										 updateremotepoints(n1, (struct remote_local_list *)q);
										}
										if ((program_codes[i]=Heap_alloc(n))!=NULL)
										{
//										set_semaphore(&t3000_flag);
										 movedata(FP_SEG(p),FP_OFF(p) ,FP_SEG(program_codes[i]),FP_OFF(program_codes[i]), n);
//										clear_semaphore(&t3000_flag);
										}
										programs[i].bytes=n;
										programs_size += n;
										ltot += n+2;
										showgauge(gauge, coef, ltot);
									 }
									 else
									 {
										set_semaphore_dos();
										fread(	&n, 2, 1, h);
										fread( buf, n, 1, h);
										ltot += n+2;
										clear_semaphore_dos();
										if(!n)
										{
										 n=11;
										 memset(buf,0,n);
										 buf[2]=0xfe;
										}
										setindexremote(buf);
										if(net_call(16+100,  i, buf, &n , st, networkaddress,NETCALL_RETRY))
											ret = ERROR_COMM;
									 }
									}
									set_semaphore_dos();
									for(i=l;i<max_prg;i++)
									{
										fread(	&n, 2, 1, h);
										fread( buf, n, 1, h);
										ltot += n+2;
									}
									clear_semaphore_dos();
/*
									if(local)
									 if(max_prg > MAX_PRGS)
										for(i=0;i< max_prg-MAX_PRGS;i++)
										{
										 set_semaphore_dos();
										 fread(	&n, 2, 1, h);
										 fread( p, n, 1, h);
										 ltot += n+2;
										 clear_semaphore_dos();
										}
*/
									if(local)
									 mfarfree(handle);
									showgauge(gauge, coef, ltot);
									showgauge(gauge, "WR-T");

									set_semaphore_dos();
									m = MAX_WR * 9 * sizeof(Wr_one_day);
									fread(	&n, 2, 1, h);
									l = min(n,m);
									if(local)
									{
										fread( wr_times, l, 1, h);
										if(n > m)
										 fseek(h, n-m, SEEK_CUR);
										clear_semaphore_dos();
									}
									else
									{
										fread( buf, n, 1, h);
										j = 9*sizeof(Wr_one_day);
										l = min(n/j, tblbank[WR]);
										clear_semaphore_dos();
										for(i=0;i<l;i++)
										{
										 if(net_call(WR_TIME+1+100, i, (char *)&buf[i*j], &j,st, networkaddress,NETCALL_RETRY))
												ret = ERROR_COMM;
										}
									}
									ltot += n+2;
									showgauge(gauge, coef, ltot);
									showgauge(gauge, "AR-D");

									set_semaphore_dos();
									m = MAX_AR * 46;
									fread(	&n, 2, 1, h);
									l = min(n,m);
									if(local)
									{
									 fread( ar_dates, l, 1, h);
									 if(n > m)
										fseek(h, n-m, SEEK_CUR);
									 clear_semaphore_dos();
									}
									else
									{
										fread( buf, n, 1, h);
										clear_semaphore_dos();
										l = min(n/46, tblbank[AR]);
										j=46;
										for(i=0;i<l;i++)
										{
										 if(net_call(AR_Y+1+100, i, &buf[i*46], &j, st, networkaddress,NETCALL_RETRY))
												ret = ERROR_COMM;
										}
									}
									ltot += n+2;
									showgauge(gauge, coef, ltot);

									if(local)
									{
									 ind_heap_grp=0;
									 memset(heap_grp, 0, MAX_HEAP_GRP);
									 mfarmalloc(&p, MAX_ELEM*sizeof(Str_grp_element), handle);
									 if (p==NULL)
									 {
										 mxyputs(10,10,"Error alloc");
										 abort();
									 }
//									for(i=0;i< MAX_GRPS;i++)
//										 Heap_grp_dealloc((char huge **)&control_group_elements[i].ptrgrp,control_group_elements[i].nr_elements*sizeof(Str_grp_element));
									}
									Str_grp_element *pgrp;
									nitem = sizeof(Str_grp_element);
									set_semaphore_dos();
									fread(	&nitem, 2, 1, h);
									clear_semaphore_dos();

//								  l=min(MAX_GRPS,max_grp);
									 btext[0]='G';
									 btext[1]='R';
									 btext[2]='P';
									 btext[3]=' ';
									 btext[4]=' ';
									 btext[5]=0;
									l=min(tblbank[GRP],max_grp);
									for(i=0;i< l;i++)
									{
									 itoa(i,&btext[3],10);
									 showgauge(gauge, btext);
									 if(local)
									 {
										set_semaphore_dos();
										fread(	&n, 2, 1, h);
										fread( p, n, 1, h);
									  clear_semaphore_dos();
										pgrp = (Str_grp_element *)p;
										for(j=0; j<n/sizeof(Str_grp_element); j++, pgrp++ )
										{
										 pgrp->point_absent = 0;
										 if(pgrp->point_info.point.point_type==OUT+1)
											if(pgrp->point_info.point.number+1>tblbank[OUT])
												pgrp->point_absent = 1;
										 if(pgrp->point_info.point.point_type==IN+1)
											if(pgrp->point_info.point.number+1>tblbank[IN])
												pgrp->point_absent = 1;
										}
										ltot += n+2;
										if ((control_group_elements[i].ptrgrp=(Str_grp_element *)Heap_grp_alloc(n))!=NULL)
											movedata(FP_SEG(p),FP_OFF(p) ,FP_SEG(control_group_elements[i].ptrgrp),FP_OFF(control_group_elements[i].ptrgrp), n);
										control_group_elements[i].nr_elements=n/sizeof(Str_grp_element);
										grp_updateremotepoint(control_group_elements[i]);
									 }
									 else
									 {
									  set_semaphore_dos();
										fread(	&n, 2, 1, h);
										fread( buf, n, 1, h);
									  clear_semaphore_dos();
										pgrp = (Str_grp_element *)buf;
										for(j=0; j<n/sizeof(Str_grp_element); j++, pgrp++ )
										{
										 pgrp->point_absent = 0;
										 if(pgrp->point_info.point.point_type==OUT+1)
											if(pgrp->point_info.point.number+1>tblbank[OUT])
												pgrp->point_absent = 1;
										 if(pgrp->point_info.point.point_type==IN+1)
											if(pgrp->point_info.point.number+1>tblbank[IN])
												pgrp->point_absent = 1;
										}
										if(net_call(19+100, i, (char *)buf, &n, st, networkaddress,NETCALL_RETRY))
												ret = ERROR_COMM;
										ltot += n+2;
									 }
									}
									set_semaphore_dos();
									for(i=l;i<max_grp;i++)
									{
										fread(	&n, 2, 1, h);
										fread( buf, n, 1, h);
										ltot += n+2;
									}
 									clear_semaphore_dos();
/*
									if(local)
									 if(max_grp > MAX_GRPS)
										for(int i=0;i< max_grp-MAX_GRPS;i++)
										{
										 fread(	&n, 2, 1, h);
										 fread( p, n, 1, h);
										 ltot += n+2;
										}
*/
									showgauge(gauge, coef, length);

									set_semaphore_dos();
//                  read icon_name_table
									n=0;
									fread( &n, 2, 1, h);
									if(local)
									{
									 fread( Icon_name_table, n, 1, h);
									 clear_semaphore_dos();
									}
									else
									{
										memset(buf,0,n);
										fread( buf, n, 1, h);
										clear_semaphore_dos();
										if(net_call(COMMAND_50+100, ICON_NAME_TABLE_COMMAND, (char*)buf, (unsigned int *)&n, st, networkaddress, NETCALL_RETRY))
												ret = ERROR_COMM;
									}
									if(local)
									{
									 mfarfree(handle);
									 upcustomunit(ptr_panel->units);
									}
									set_semaphore_dos();
									fclose(h);
									clear_semaphore_dos();
									deletegauge(&gauge);

#ifndef WORKSTATION
									if(local)
									{
									 just_load = 1;
									 onemin = 1;
									}
#endif
									if(local)
									{
									 initanalogmon();
									 pixvar = 1;
									}
									countdeslength();
								 }
								 else
								 {
										set_semaphore_dos();
										fclose(h);
										clear_semaphore_dos();
										ret = ERROR_COMM;
								 }
								 if(local)
								 {
									 clear_semaphore(&t3000_flag);
								 }
								}
								else
								{
									onemin = 1;
//									resume(VIRTUAL);
									set_semaphore_dos();
									fclose(h);
									clear_semaphore_dos();
									ret = ERROR_COMM;
								}
							 }
	set_semaphore_dos();
	delete buf;
	clear_semaphore_dos();
	if(panel_info->panel_type == MINI_T3000)
	{
	 if(panel_info->version>=230)
	 {
		if(ret==SUCCESS)
		{
		 if( net_call(COMMAND_50, WRITEPRGFLASH_COMMAND, NULL, 0, st, networkaddress)!=SUCCESS )
			 if( net_call(COMMAND_50, WRITEPRGFLASH_COMMAND, NULL, 0, st, networkaddress)!=SUCCESS )
			 {
				 ret = ERROR_COMM;
				 DisplayMessage(12, 7, 68, 11, NULL, saveprgflashtxt,NULL, Black, NULL, 5000);
				 return ret;
			 }
		 DisplayMessage(12, 7, 68, 11, NULL, rebootm,NULL, Black, NULL, 32000);
		 return ret;
		}
		DisplayMessage(12, 7, 68, 11, NULL, saveprgflashtxt,NULL, Black, NULL, 5000);
	 }
	}
  return ret;
}

void upcustomunit(Units_element	*punits)
{
 for(int i=0;i<MAX_UNITS;i++)
 {
	int x,y, z;
	z = custom_digital1 - DIG1;
	x =  min(5,strlen(punits[i].digital_units_off));
	memcpy(dig_range_array[z+i].range_text, punits[i].digital_units_off,x);
	dig_range_array[z+i].range_text[x]='/';
	y =  min(5,strlen(punits[i].digital_units_on));
	memcpy(&dig_range_array[z+i].range_text[x+1], punits[i].digital_units_on,x);
	dig_range_array[z+i].range_text[x+1+y]=0;
	strcpy(dig_range_array[z+i].dunits[1], punits[i].digital_units_on);
	strcpy(dig_range_array[z+i].dunits[0], punits[i].digital_units_off);
 }
}


/*
void savepath(void)
{
set_semaphore_dos();
	if( (h=fopen("config.cnf","rb+"))!=NULL)
	{
//	 fseek(h,20+MAX_BOARDS*sizeof(Board_info)+3*sizeof(Comm_Info)+sizeof(ModemCapabilities),SEEK_SET);
	 fseek(h,CNF_PROGRAM_PATH,SEEK_SET);
	 fwrite(ptr_panel->Program_Path, 64, 1, h);
	 fwrite(ptr_panel->Descriptor_Path, 64, 1, h);
	 fwrite(ptr_panel->Basic_Path, 64, 1, h);
	 fwrite(ptr_panel->Monitor_Path, 64, 1, h);
	 fwrite(ptr_panel->Graphics_Path, 64, 1, h);
	 fwrite(ptr_panel->Default_Program, 13, 1, h);
	 fclose(h);
	}
clear_semaphore_dos();
}
*/
int savenetwork(void)
{
	uint man,i, ret;
	unsigned char tbl_bank1[MAX_TBL_BANK];
	unsigned long activepanels;
	Panel_info1 panel_info;
	char buf1[13], default_prg1[13];
	if( ReadYesNo(20, 9, 65, 13, Lightgray, Darkgray, Black, Cyan, White, "Proceed with saving? (Y/N): ") )
	{
				memset(&netoperation[0],0,MAX_STATIONS);
				delay(1000);
        activepanels = 0;
				if(serial_access)
				{
					activepanels = serial_panel_info1.active_panels;
				}
				else
				{
				 if( rs485port!=-1 )
					activepanels = ((class ConnectionData *)Routing_table[rs485port].ptr)->panel_info1.active_panels;
        }
				for(man=0;man<MAX_STATIONS;man++)
				 if( (activepanels&(1L<<man)) && Station_NUM!=man+1 )
				 {
					ret = 0;
					if( net_call(COMMAND_50, PANEL_INFO1_COMMAND, (char*)&panel_info, 0, man+1, networkaddress,NETCALL_RETRY|NETCALL_NOTTIMEOUT)==SUCCESS )
					{
// save the .prg first
					 i = sizeof(tbl_bank);
					 if( net_call(COMMAND_50, TABLEPOINTS_COMMAND, (char *)tbl_bank1, &i, panel_info.panel_number, networkaddress,NETCALL_RETRY)!=SUCCESS )
						 ret = 1;
					 if( net_call(COMMAND_50, DEFAULT_PRG_COMMAND, default_prg1, 0, panel_info.panel_number, networkaddress, NETCALL_RETRY)!=SUCCESS )
						 ret = 1;

					 if(!ret)
					 {
						if( strlen(rtrim(default_prg1)) )
						{
						 strcpy(buf1, default_prg1);
						}
						else
						{
						 strcpy(buf1, panel_text1);
						 itoa(panel_info.panel_number, &buf1[5], 10);
						 strcat(buf1,"$.PRG");
						}
						saveoldprg(buf1,1);
						if(ptr_panel->savefile(buf1, &panel_info, tbl_bank1, 0)!=SUCCESS)
						{
						 saveoldprg(buf1,0);
						 delay(5000);
// repeat
						 saveoldprg(buf1,1);
						 if(ptr_panel->savefile(buf1, &panel_info, tbl_bank1, 0)!=SUCCESS)
						 {
							saveoldprg(buf1,0);
							ret = 1;
						 }
						}
						delay(5000);
					 }
					}
					else
					 ret=1;

					if(ret)
						netoperation[man] = 0x0; // not saved
					else
					{
						netoperation[man] = 0x04; // saved
					}
				 }
	}
}

int minioperations(void)
{
	GPopUp *popup;
	char *fname, buf[5];
	int man,n,startpanel;
	uint j;
	unsigned long activepanels;
	Panel_info1 panel_info;

	set_semaphore_dos();
	popup = new GPopUp(1,9,(char **)&list12,0,2);
	clear_semaphore_dos();
	man = popup->GReturn();
	G.pGPopUpTable[0].ReleasePopUp(-1);
	set_semaphore_dos();
	delete popup;
	clear_semaphore_dos();

	if(man==0)
	{
	 if(!local_panel)
		mini_operations( &panel_info1 );
	}
	if(man==1)
	{
			 GWindow *A;
			 A= new GWindow(10,6,70,16,NO_STACK,0);
			 A->GWSet("Hit any key to continue",Lightblue,Blue);
			 A->GShowWindow(WIN_ERROR);
			 A->GWPuts(1,3,"For every panel connected to the network, the updating",Lightblue,Blue);
			 A->GWPuts(2,3,"procedure is as follow:",Lightblue,Blue);
			 A->GWPuts(3,7,"1. The program file is saved",Lightblue,Blue);
			 A->GWPuts(4,7,"2. The firmware is updated",Lightblue,Blue);
			 A->GWPuts(5,7,"3. The previous saved program file is loaded",Lightblue,Blue);
			 A->GWPuts(6,3,"When finished, check the 'Network status' screen in the",Lightblue,Blue);
			 A->GWPuts(7,3,"field 'Update/Prg' for the result of updating",Lightblue,Blue);
			 while(!A->HandleEvent());
			 delete A;

			 buf[0]='1';
			 buf[1]=0;
			 ReadWindow(15, 8, 65, 11, Lightgray, Darkgray, Black,
							 Cyan, White, "The updating will start with panel number: ", buf, 2);
			 startpanel = atoi(buf);
			 if( startpanel<1 || startpanel>32 ) return 1;
			 startpanel--;

			 set_semaphore_dos();
			 fname = new char[65];
			 clear_semaphore_dos();
			 fname[0]=0;
			 ReadWindow(24, 7, 56, 11, Lightgray, Darkgray, Black,
							 Cyan, White, "File name : ", fname, 12);

			 if( strlen(fname) )
			 {
				memset(&netoperation[startpanel],0,MAX_STATIONS-startpanel);
				delay(1000);
        activepanels = 0;
				if( serial_access )
					activepanels = serial_panel_info1.active_panels;
				else
				{
				 if( rs485port!=-1 )
					activepanels = ((class ConnectionData *)Routing_table[rs485port].ptr)->panel_info1.active_panels;
				}
				for(man=startpanel;man<MAX_STATIONS;man++)
				 if( (activepanels&(1L<<man)) && Station_NUM!=man+1 )
				 {
					n = 1;
					if( net_call(COMMAND_50, PANEL_INFO1_COMMAND, (char*)&panel_info, 0, man+1, networkaddress,NETCALL_RETRY|NETCALL_NOTTIMEOUT)==SUCCESS )
					{
					 if( (n=mini_operations(&panel_info, fname, 2))>0 )
					 {
							delay(10000);
							n=mini_operations(&panel_info, fname, 2);
					 }
					 if(n>0)
						netoperation[man] = 0x0; // not updated
					 else
					 {
						if(!n)
						 netoperation[man] = 0x03; // updated, loaded
						else
						{
						 if(n==-1)
							netoperation[man] = 0x01; // updated, not loaded
						}
					 }
					}
					if(n==USER_ABORT)
						break;
					delay(5000);
				 }
			 }
			 set_semaphore_dos();
			 delete fname;
			 clear_semaphore_dos();
	}
}

// arg == 0  ask if want Update firmware
//                       to save .prg
// arg == 1  update firmware without to save .prg
// arg == 2  save .prg, update firmware, load .prg

//   result = 0;   OK
//   result = -1;  Updated, .prg not loaded

//   result = 1;   not a MINI_T3000
//   result = 2;   error save .prg
//   result = 3;   don't want firmare update
//   result = 4;   file not found
//   result = 5;   error READFLASHSTATUS_COMMAND
//   result = 6;   Not enough memory
int mini_operations(Panel_info1 *panel_info, char *fname, int arg)
{
 unsigned char tbl_bank1[MAX_TBL_BANK];
 char buf[13], buf1[13], cont, default_prg1[13];
 char *p, *q, nrblock;
 int n,crc,result,crc_file;
 GWindow *D=NULL;
 long j, addr, length, l, buffer_length, l1;
 unsigned i;

 result = 1;
 if( panel_info->panel_type == MINI_T3000 )
 {
	 if( !arg )
	 {
		if(ReadYesNo(5, 9, 75, 13, Lightgray, Darkgray, Black, Cyan, White, "The PRG will be erased. Do you want to save it now? (Y/N): "))
		{
		 if( ptr_panel->file(1)!=SUCCESS)
		 {
			 return 2;
		 }
		}
	 }
	 else
		if(arg==2)
		{
// save the .prg first
			 i = sizeof(tbl_bank);
			 if( net_call(COMMAND_50, TABLEPOINTS_COMMAND, (char *)tbl_bank1, &i, panel_info->panel_number, networkaddress,NETCALL_RETRY)!=SUCCESS )
				 return 2;
			 if( net_call(COMMAND_50, DEFAULT_PRG_COMMAND, default_prg1, 0, panel_info->panel_number, networkaddress, NETCALL_RETRY)!=SUCCESS )
				 return 2;

			 if( strlen(rtrim(default_prg1)) )
			 {
				 strcpy(buf1, default_prg1);
			 }
			 else
			 {
				 strcpy(buf1, panel_text1);
				 itoa(panel_info->panel_number, &buf1[5], 10);
				 strcat(buf1,"$.PRG");
			 }
			 saveoldprg(buf1,1);
			 if(ptr_panel->savefile(buf1, panel_info, tbl_bank1, 0)!=SUCCESS)
			 {
				 saveoldprg(buf1,0);
				 delay(5000);
// repeat
				 saveoldprg(buf1,1);
				 if(ptr_panel->savefile(buf1, panel_info, tbl_bank1, 0)!=SUCCESS)
				 {
					saveoldprg(buf1,0);
					return 2;
				 }
			 }
			 delay(5000);
		}

	 if( !arg )
	 {
		 if( !ReadYesNo(20, 9, 65, 13, Lightgray, Darkgray, Black, Cyan, White, "Update mini firmware ? (Y/N): ") )
			 return 3;
	 }
	 {
		if( !fname )
		{
		 buf[0]=0;
		 ReadWindow(24, 7, 56, 11, Lightgray, Darkgray, Black,
							 Cyan, White, "File name : ", buf, 12);
		}
		else
		 strcpy(buf,fname);
		if( strlen(buf) )
		{
      nrblock=0;
// send data
			set_semaphore_dos();
			if ((h=fopen(buf,"rb"))!=NULL)
			{
			 clear_semaphore_dos();
			 SectorInfo si[8];  // 7+buffer_length
			 length =  sizeof(SectorInfo);
//  read flash status
					i=0;
			 if( ( result = net_call(COMMAND_50, READFLASHSTATUS_COMMAND, (char *)&si, &i, panel_info->panel_number, networkaddress, NETCALL_RETRY))!=SUCCESS)
			 {
				 fclose(h);
				 return 5;
			 }
			 memcpy(&buffer_length, si, 4);   // buffer_available
			 set_semaphore_dos();
			 if( buffer_length > 65535 ) buffer_length = 65535;
			 p = new char[buffer_length];
			 clear_semaphore_dos();
			 q = p;
			 if(!p)
			 {
				if(D) DeleteMessage(D);
				DisplayMessageT(20, 7, 60, 11, NULL, "Not enough memory ! ", NULL, Blue, NULL, 10000);
				fclose(h);
				return 6;
			 }
			 cont=0;
			 if(!arg)
			 {
				 if(ReadYesNo(20, 9, 65, 13, Lightgray, Darkgray, Black, Cyan, White, "Proceed with update ? (Y/N): "))
					cont = 1;
			 }
			 else
         cont = 1;
       if(cont)
			 {
// check file format
				set_semaphore_dos();
				fread(&crc_file,1,2,h);
			  fread(&addr,1,4,h);
			  fread(&l,1,4,h);
			  while(!feof(h))
			  {
				 clear_semaphore_dos();
				 if(l>buffer_length-8)
				 {
				  DisplayMessageT(20, 7, 60, 11, NULL, " Error buffer length! ", NULL, Blue, NULL, 10000);
				  result=ERROR_COMM;
				  break;
				 }
				 set_semaphore_dos();
				 fread(p,l,1,h);
				 clear_semaphore_dos();
				 crc = 0;
				 for(j=0; j<l; j++)
					crc=CalcDataCRC(p[j], crc);
				 if(crc!=crc_file)
				 {
				  DisplayMessageT(20, 7, 60, 11, NULL, " Wrong CRC ! ", NULL, Blue, NULL, 10000);
				  result=ERROR_COMM;
				  break;
				 }
				 set_semaphore_dos();
				 fread(&crc_file,1,2,h);
				 fread(&addr,1,4,h);
				 fread(&l,1,4,h);
				}
				fseek(h,0,SEEK_SET);
			  clear_semaphore_dos();
//
			 if( result == SUCCESS )
			 {
			  DisplayMessage(mode_text?19:200, mode_text?7:150, mode_text?61:500, mode_text?11:200, ctrlbreak_text, "The update will take about four minutes!", NULL, Blue, NULL, 3000);
			  set_semaphore_dos();
			  fread(&crc_file,1,2,h);
				fread(&addr,1,4,h);
			  fread(&l,1,4,h);
			  while(!feof(h))
			  {
				clear_semaphore_dos();
				cont = 1;
				length = 0;
				p = q;
				crc = 0;
				if(l>buffer_length-8)
				{
				 DisplayMessageT(20, 7, 60, 11, NULL, " Error buffer length! ", NULL, Blue, NULL, 10000);
				 break;
				}
				set_semaphore_dos();
				while(!feof(h) && length + l + 8 <= buffer_length )
				{
				 clear_semaphore_dos();
				 memcpy(p+length, &addr, 4);
				 memcpy(p+length+4, &l, 4);
				 set_semaphore_dos();
				 fread(p+length+8,l,1,h);

				 clear_semaphore_dos();
				 length += 8;
				 for(j=0; j<l; j++)
					crc=CalcDataCRC(p[length+j], crc);
				 length += l;
				 set_semaphore_dos();
			    fread(&crc_file,1,2,h);
				 fread(&addr,1,4,h);
				 fread(&l,1,4,h);
				}
				clear_semaphore_dos();
				if( length > 65535 )
				{
					i = 65535;
				}
				else
				{
				  i = length;
				}
				strcpy(tempbuf,"Sending data to ");
				memcpy(&tempbuf[16], panel_info->panel_name, NAME_SIZE);
				tempbuf[16+NAME_SIZE]=0;
				rtrim(tempbuf);
				strcat(tempbuf,"...   ");
				DisplayMessageT(18, 7, 62, 11, (nrblock?NULL:ctrlbreak_text), tempbuf, &D);
				while(i)
				{
//  how to continue:  0 - continue  1 - reset
/*
				 if( panel_info1.version > 243 )
					 writeretry_flag=1;
*/
				 if( ( result = net_call(COMMAND_50+100, ((unsigned)(cont<<15))+(unsigned)SENDDATAMINI_COMMAND, p, &i, panel_info->panel_number, networkaddress, (panel_info->version>246?NETCALL_WRITERETRY:0)|NETCALL_SIGN|(nrblock?NETCALL_NOTCTRLBREAK:0)))!=SUCCESS)
//				 if( ( result = net_call(COMMAND_50+100, ((unsigned)(cont<<15))+(unsigned)SENDDATAMINI_COMMAND, p, &i, station_num, networkaddress, NETCALL_SIGN))!=SUCCESS )
				 {
					 if(result==USER_ABORT) break;
					 Delay(2000);
//					if( ( result = net_call(COMMAND_50+100, ((unsigned)(cont<<15))+(unsigned)SENDDATAMINI_COMMAND, p, &i, station_num, networkaddress, NETCALL_SIGN))!=SUCCESS)
					 if( ( result = net_call(COMMAND_50+100, ((unsigned)(cont<<15))+(unsigned)SENDDATAMINI_COMMAND, p, &i, panel_info->panel_number, networkaddress, (panel_info->version>246?NETCALL_WRITERETRY:0)|NETCALL_SIGN|(nrblock?NETCALL_NOTCTRLBREAK:0)))!=SUCCESS)
					 {
						if(result==USER_ABORT) break;
						Delay(1000);
//					 if( ( result = net_call(COMMAND_50+100, ((unsigned)(cont<<15))+(unsigned)SENDDATAMINI_COMMAND, p, &i, station_num, networkaddress, NETCALL_SIGN))!=SUCCESS)
						if( ( result = net_call(COMMAND_50+100, ((unsigned)(cont<<15))+(unsigned)SENDDATAMINI_COMMAND, p, &i, panel_info->panel_number, networkaddress, (panel_info->version>246?NETCALL_WRITERETRY:0)|NETCALL_SIGN|(nrblock?NETCALL_NOTCTRLBREAK:0)))!=SUCCESS)
						{
					   if(result==USER_ABORT) break;
						 DisplayMessageT(20, 7, 60, 11, NULL, " Error send data! ", NULL, Blue, NULL, 10000);
						 break;
						}
					 }
				 }
				 p += i;
				 i = length - i;
				 cont = 0;
				}
				if(D) {DeleteMessage(D); D=NULL;}
				if( result == SUCCESS )
				{
// write command
				 i=0;
				 Delay(3000);
				 if( (result = net_call(COMMAND_50, WRITEDATAMINI_COMMAND, (char *)&si, &i, panel_info->panel_number, networkaddress))!=SUCCESS )
					if( (result = net_call(COMMAND_50, WRITEDATAMINI_COMMAND, (char *)&si, &i, panel_info->panel_number, networkaddress))!=SUCCESS )
//						if( (result = net_call(COMMAND_50, WRITEDATAMINI_COMMAND, (char *)&si, &i, station_num, networkaddress))!=SUCCESS )
						{
						 DisplayMessageT(20, 7, 60, 11, NULL, " Error send command! ", NULL, Blue, NULL, 10000);
						 break;
						}
// wait for mini
				 if(serial_access)      // do not disconnect
				 {
/*
					if( (n = findroutingentry(-1, network, j)) >= 0)
*/
					if( serial_access == station_num )
						T_Inactivity = 2100;
				 }
				 Delay(1000);
				 DisplayMessageT(15, 7, 65, 11, NULL, "Waiting for mini to write data...(max 3 min)", &D);
				 result=ERROR_COMM;
				 l1 = timestart+timesec1970;
				 Delay(15000);
				 while( timestart+timesec1970<l1+180 )
				 {
					i=0;
					if( (result = net_call(COMMAND_50, READSTATUSWRITEFLASH_COMMAND, (char *)&si, &i, panel_info->panel_number, networkaddress, NETCALL_NOTTIMEOUT))==SUCCESS )
					{
					 if( *(((char *)&si)+1) )
					 {
            nrblock++;
						if ( crc !=  *(((int *)&si)+1) ) result=ERROR_COMM;
						Delay(1000);
						break;
					 }
					 result=ERROR_COMM;
				  }
				 }
				 if(serial_access)
				 {
					  T_Inactivity = T_INACTIVITY;
				 }
				 Delay(5000);
				 if(D) {DeleteMessage(D); D=NULL;}
				 if( result==ERROR_COMM )
				 {
					DisplayMessageT(20, 7, 60, 11, NULL, " Error write data! ", NULL, Blue, NULL, 10000);
					break;
				 }
				}
				else
				 break;

				set_semaphore_dos();
				}
				Delay(1000);
				clear_semaphore_dos();
				if( result==SUCCESS )
				{
				 i=0;
				 if( (result=net_call(COMMAND_50, RESTARTMINI_COMMAND, (char *)&si, &i, panel_info->panel_number, networkaddress))!=SUCCESS )
					 if( (result=net_call(COMMAND_50, RESTARTMINI_COMMAND, (char *)&si, &i, panel_info->panel_number, networkaddress))!=SUCCESS )
						 DisplayMessageT(20, 7, 60, 11, NULL, " Error send command! ", NULL, Blue, NULL, 10000);
				 if(serial_access)
				 {
					if( serial_access == station_num )
						disconnect_serial(1);
				 }
				 else
				 {
					setlocalpanel(networkaddress);
				 }
				 if( result==SUCCESS )
				 {
					DisplayMessageT(16, 7, 64, 11, NULL,   "                Update O.K.!                    The panel will reboot in about 20 seconds. ", NULL, Blue, NULL, 20000);
					DisplayMessageT(20, 7, 60, 11, NULL, " You have to reconnect...! ",NULL, Black, NULL, 2000);
				 }
				}
//			  if(D) DeleteMessage(D);
			  }
			 }
			 set_semaphore_dos();
			 delete q;
			 fclose(h);
			 clear_semaphore_dos();
		  }
		  else
			{
			 clear_semaphore_dos();
			 DisplayMessage(20, 10, 60, 14, pressanykey, "File not found!", NULL, Blue, NULL, 5000);
			 return 4;
			}
		}
		else
			 return 3;
	 }
 }
 else
	 result = 1;  // not a MINI_T3000
 if(!arg)
 {
		 if( result!=SUCCESS )
			DisplayMessage(20, 7, 60, 11, NULL, "Error update firmware!", NULL, Blue, NULL, -1);
		 else
			DisplayMessage(22, 7, 58, 11, NULL, "Firmware updated O.K.", NULL, Blue, NULL, -1);
 }
 if(arg==2)
 {
	DisplayMessageT(30, 8, 50, 12, NULL, wait_text, NULL, Blue, NULL, 40000);
	if( result==SUCCESS )
	{
	 i = 13;
	 if( net_call(50+100, 33, buf1, &i, panel_info->panel_number, networkaddress,NETCALL_RETRY)==SUCCESS)
		if( ptr_panel->loadprg(buf1,panel_info,tbl_bank1,0)!=SUCCESS )
		{
		 delay(2000);
		 if( ptr_panel->loadprg(buf1,panel_info,tbl_bank1,0)!=SUCCESS )
      result = -1;
		}
  }
 }
 return result;
}

void updatetimevars(void)
{
	disable();
	gettime(&ora_start);
	timesec1970=time(NULL);
	memcpy(&ora_current, localtime((const long *)&timesec1970), sizeof(struct tm) );
	ora_current_sec = (unsigned long)ora_start.ti_hour*3600L+(unsigned long)ora_start.ti_min*60L+(unsigned long)ora_start.ti_sec;
	timestart=0;
	milisec = (int)ora_start.ti_hund * 10;
	microsec = (int)ora_start.ti_hund * 10000;
	if( ora_current.year&0x03 )
		month_days[1]=28;
	else
		month_days[1]=29;

  updatedtime = 1;
/*
	save_monitor = 0x01 | 0x02;
	save_monitor_command = 1;
	resume(AMONITOR);
*/
	enable();
}

void setup(void)
{
	GPopUp *popup;
	set_semaphore_dos();
// ********  the old code  ********
//	popup = new GPopUp( mode_text?50:400,mode_text?3:56,(char **)&list7,0,5, SMALL_FONT, 5, 1);
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.045  ********
// ********       begin       ********
// ***********************************
	popup = new GPopUp(MENU_SETUP,"need help",mode_text?50:400,mode_text?3:56,(char **)&list7,0,6, SMALL_FONT, 5, 1);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.045  ********
// ********        end        ********
// ***********************************
	clear_semaphore_dos();
	uint i;
	i=popup->GReturn();
	G.pGPopUpTable[4].ReleasePopUp(-1);
	set_semaphore_dos();
	delete popup;
	clear_semaphore_dos();
	char timebuf[9];
	char datebuf[9];

	switch (i) {
	 case 0:
				{
				 char *p,*q;
				 if(local_panel) q=ptr_panel->Default_Program;
				 else q=default_prg;

				 if((p=strrchr(q,'.'))!=NULL)
				 {
					*p=0;
				 }
				 keyboard_data=0;
// ********  the old code  ********
//				 ReadWindow(mode_text?20:140, mode_text?7:140, mode_text?60:450, mode_text?11:200, Lightgray, Darkgray, Black,
//							 Cyan, White, "Default panel program : ", q, 8);
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.046  ********
// ********       begin       ********
// ***********************************
				 ReadWindow_help(200,mode_text?20:140, mode_text?7:140, mode_text?60:450, mode_text?11:200, Lightgray, Darkgray, Black,
							 Cyan, White, "Default panel program : ", q, 8);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.046  ********
// ********        end        ********
// ***********************************
				 if(keyboard_data)
				 {
					if(!strchr(q,'.'))
					{
					 if( strlen(rtrim(q)) )
					 {
						if(strlen(q) > 8)
						 strcpy(&q[8],".PRG");
						else
						 strcat(q,".PRG");
					 }
					 if(local_panel)
					 {
						save_config(CNF_PATH_INFO);
						strcpy(default_prg, ptr_panel->Default_Program);
					 }
					 else
					 {
						i = 13;
						net_call(50+100, 33, default_prg, &i, station_num, networkaddress);
					 }
					}
				 }
				 else
				 {
					if( strlen(q) )
						strcat(q,".PRG");
				 }
				 break;
				}
	 case 1:
//				 G.ShowunderMBar();
				 ptr_panel->Path();
					save_config(CNF_PATH_INFO);
//				 savepath();
//				 G.GShowMenuBar(message);
				 break;
	 case 2:
				 Time_block tb;
				 struct  time t;
				 struct  date d;
				 Time_block_mini timemini;
				 GWDialog *D;
//  ********  the old code  ********
//				 D = new GWDialog(17,8,63,15,NO_STACK,0);
// *********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.047  ********
// ********       begin       ********
// ***********************************
				 D = new GWDialog(202,"need_help",17,8,63,15,NO_STACK,0);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.047  ********
// ********        end        ********
// ***********************************
				 D->exitCR = 1;
				 D->GWSet("",Lightgray,Darkgray);
				 D->GShowWindow(DIALOG);

				 D->GWPuts(1,2,"   Current time is      : ",Lightgray,Black);
				 D->GWPuts(2,2,"   New Time ( hh:mm:ss) : ",Lightgray,Black);

				 D->GWPuts(4,2,"   Current date is      : ",Lightgray,Black);
				 D->GWPuts(5,2,"   New Date ( mm-dd-yy) : ",Lightgray,Black);

				 if(!local_panel)
				 {
					if( net_call(TIME_COMMAND, 0, (char *)&tb, 0, station_num, networkaddress)==SUCCESS )
					{
					 adjust_readtime(&tb);
					 t.ti_sec  = tb.ti_sec;
					 t.ti_min  = tb.ti_min;
					 t.ti_hour = tb.ti_hour;
					 d.da_year  = tb.year+1900;
					 d.da_mon = tb.month+1;
					 d.da_day = tb.dayofmonth;
					}
					else
					{
					 if(D)
					 {
             D->GReleaseWindow();
						 delete D;
					 }
           break;
					}
				 }
				 else
					 gettime(&t);
				 strcpy(timebuf, intervaltotext( NULL, (long)t.ti_sec , t.ti_min , t.ti_hour));
				 D->GDPuts(1,26, timebuf, 8 ,Lightgray,Black);
				 if(local_panel)
					 getdate(&d);
				 strcpy(datebuf, intervaltotext( NULL, (long)d.da_year%100 , d.da_day , d.da_mon, "-"));
				 D->GDPuts(4,26, datebuf, 8 ,Lightgray,Black);

				 memset( timebuf, '0', 8);
				 memset( datebuf, '0', 8);
				 timebuf[2] = timebuf[5] = ':';
				 datebuf[2] = datebuf[5] = '-';
				 timebuf[8] = 0;
				 datebuf[8] = 0;
				 D->GDPuts(2,26, timebuf , 8 ,Cyan,Black);
				 D->GDPuts(5,26, datebuf , 8 ,Cyan,Black);

//				 ind_object_t=0; ind_object_d=1;
//				 D->GDDef_object(ptime,26,2,8,Cyan,Black);
				 D->GDDef_object(NULL,26,2,8,Cyan,Black,timebuf, Black, White, "NN:NN:NN");
//				 D->GDDef_object(pdate,26,5,8,Cyan,Black);
				 D->GDDef_object(NULL,26,5,8,Cyan,Black,datebuf, Black, White, "NN-NN-NN");
//				 i_files = 0;     // flag for time or date changing
				 while(!(D->HandleEvent()));
				 delete D;
				 texttointerval( timebuf, &t.ti_sec , &t.ti_min , &t.ti_hour );
				 t.ti_hund=0;
				 d.da_year = 0;
				 texttointerval( datebuf, (char *)&d.da_year , &d.da_day , &d.da_mon, '-' );
/*
	if(d.da_year)
 {
	d.da_year += 1900;
	setdate(&d);
	i_files = 1;
 }

 if(t.ti_sec || t.ti_min || t.ti_hour)
 {
	 settime(&t);
	 i_files = 1;
 }
*/
				 if(!local_panel)
				 {
					i=0;
					if(t.ti_sec || t.ti_min || t.ti_hour)
					{
//					gettime(&t);
//					getdate(&d);
					 tb.ti_sec=t.ti_sec;
					 tb.ti_min=t.ti_min;
					 tb.ti_hour=t.ti_hour;
					 i=1;
					}
					if(d.da_year)
					{
					 tb.dayofmonth=d.da_day;
					 tb.month=d.da_mon-1;
					 tb.year=d.da_year;
					 i=1;
					}
					if(i)
					{
					 tb.isdst = -1;
					 if (mktime((struct tm *)&tb) == -1)
						tb.dayofweek = 7;
					 if( panel_info1.panel_type == MINI_T3000 )
					 {
						adjust_writetime(&tb, &timemini);
						i = sizeof(Time_block_mini);
						net_call(TIME_COMMAND+100, 0, (char *)&timemini, &i, station_num, networkaddress,NETCALL_RETRY);
					 }
					 else
					 {
						i = sizeof(Time_block);
						net_call(TIME_COMMAND+100, 0, (char *)&tb, &i, station_num, networkaddress,NETCALL_RETRY);
					 }
					}
				 }
				 else
				 {
					i=0;
					if(t.ti_sec || t.ti_min || t.ti_hour)
					{
						 settime(&t);
						 i=1;
					}
					if(d.da_year)
					{
							d.da_year += 1900;
							setdate(&d);
							i=1;
							check_annual_routine_flag=1;
					}
					if(i)
					{
            sendtime = 1;
						sendtime_ipx = 1;
						updatetimevars();
					}
				 }
				 break;
	 case 4:
				 if(!control)
				 {
// ********  the old code  ********
//					if(ReadYesNo(20, 9, 60, 13, Lightgray, Darkgray, Black,	Cyan, White,
//								 "  Console mode?(Y/N): "))
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.048  ********
// ********       begin       ********
// ***********************************
					if(ReadYesNo_help(203,20, 9, 60, 13, Lightgray, Darkgray, Black,	Cyan, White,
								 "  Console mode?(Y/N): "))
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.048  ********
// ********        end        ********
// ***********************************
					{
					 console_mode=1;
#ifndef WORKSTATION
					 suspend(VIRTUAL);
#endif
					}
					else
					{
					 console_mode=0;
#ifndef WORKSTATION
					 resume(VIRTUAL);
#endif
					}
					save_config(CNF_CONSOLE_INFO);
				 }
				 break;
	 case 3:
// ********  the old code  ********
//					if(ReadYesNo(20, 9, 60, 13, Lightgray, Darkgray, Black,	Cyan, White,
//								 "  Print alarms?(Y/N): ",'Y','N',printAlarms))
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.5 NO.061  ********
// ********       begin       ********
// ***********************************
					if(ReadYesNo_help(204,20, 9, 60, 13, Lightgray, Darkgray, Black,	Cyan, White,
								 "  Print alarms?(Y/N): ",'Y','N',printAlarms))
// ***********************************
// ********      mao hui      ********
// ********  1997.8.5 NO.061  ********
// ********        end        ********
// ***********************************
					{
					 printAlarms=1;
					}
					else
					{
					 printAlarms=0;
					}
				 break;
/*
	 case 4:
					if(ReadYesNo(20, 9, 60, 13, Lightgray, Darkgray, Black,	Cyan, White,
								 "  Enable Ethernet?(Y/N): ",'Y','N',IPX_enabled))
					{
					 IPX_enabled=1;
					}
					else
					{
					 IPX_enabled=0;
					}
				 break;
*/
	}

}

void hardware(void)
{
	GPopUp *popup;
	int i=-1;
	if( check_access(12)!=R_NA )
	{
	 set_semaphore_dos();
// ********  the old code ********
//	 popup= new GPopUp(mode_text?47:386,mode_text?5:87,(char **)&list8,0,2,SMALL_FONT,5,1);
// *******************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.049  ********
// ********       begin       ********
// ***********************************
	 popup= new GPopUp(MENU_HARDWARE,"need help",mode_text?47:386,mode_text?5:87,(char **)&list8,0,2,SMALL_FONT,5,1);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.049  ********
// ********        end        ********
// ***********************************
	 clear_semaphore_dos();
	 i=popup->GReturn();
	 set_semaphore_dos();
	 delete popup;
	 clear_semaphore_dos();
	}
	G.pGPopUpTable[4].ReleasePopUp(-1);

	switch (i) {
	 case 0:
				 if(serial_access) disconnect_serial(1);
				 portconfig();
				 break;
//	 case 1:
//				 modemconfig();
//				 break;
	 case 1:
				 if( panel_info1.panel_type == MINI_T3000 )
					 miniconfig();
				 else
					 boardconfig();
//				 miniconfig();
				 break;
	 case 2:
//				 boardconfig();
//				 terminal_mode();
				 break;
/*
	 case 4:
				 if(control)
				 {
				  char pass[15]={0};
				  getpassword(pass, " Reset acquisition card password: ");
				  if( !strcmp(pass,"RESET") )
				  {
					disable();
					ptr_panel->Aio_Control( RESET_CARD, NULL, 0 );
					ptr_panel->Config_dacqd_card();
					enable();
				  }
				 }
				 break;
*/
	}

}


int Panel::savefile(char *buf1, Panel_info1 *panel_info, unsigned char *tblbank, int local)
{
 int i,r=SUCCESS;
 int n,nitem,st,net, ver, vermini;
 uint l;
 Str_out_point   		 *poutputs;
 Str_in_point    		 *pinputs;
 char *pold_outs_ins, *ptr, btext[8];

								st = panel_info->panel_number;
								if(local)
								{
									 net = NetworkAddress;
								}
								else
								{
									 net = networkaddress;
								}
//		 int_disk1++;
								set_semaphore_dos();
								char *buf=new char[7500];
								clear_semaphore_dos();

								pold_outs_ins = NULL;
								if( !local && panel_info->panel_type == MINI_T3000 )
								{
								 set_semaphore_dos();
								 pold_outs_ins = new char [MAX_OUTS_MINI*sizeof(Str_out_point)+MAX_INS_MINI*sizeof(Str_in_point)];
								 clear_semaphore_dos();
								 memset(pold_outs_ins,0,MAX_OUTS_MINI*sizeof(Str_out_point)+MAX_INS_MINI*sizeof(Str_in_point));
								 poutputs = (Str_out_point *)pold_outs_ins;
								 pinputs  = (Str_in_point *)(pold_outs_ins+MAX_OUTS_MINI*sizeof(Str_out_point));
								 for(i=0; i < MAX_OUTS_MINI; i++)
									poutputs[i].digital_analog = 1;
								 for(i=0; i < MAX_INS_MINI; i++)
								 {
									pinputs[i].filter = 6;
									pinputs[i].digital_analog = 1;
								 }
								 set_semaphore_dos();
								 if ((h=fopen(buf1,"rb"))!=NULL)
								 {
									fread( tempbuf, 26, 1, h); //time and date
									fread( tempbuf, 4, 1, h);  //signature
									if ( !memcmp(tempbuf, signature, 4) )
									{
									fread(	&n, 2, 1, h);   //panel number
									fread(	&nitem, 2, 1, h);   //network number
									fread(	&ver, 2, 1, h);       //ver T3000
									fread(	&vermini, 2, 1, h);   //ver mini
									fread(	tempbuf, 1, 32, h); // reserved bytes
									if ( ver >= 210 && ver!=0x2020 )
									{
									 if( n == st )
									 {
//									  fseek(h,70,SEEK_SET);  //  information - length 44 bytes
										fread( &n, 2, 1, h);
										fread( &nitem, 2, 1, h);
//								  fread(pold_outs_ins,1,32*sizeof(Str_out_point),h);
										if( vermini )
											fread((char *)poutputs,n,nitem,h);
										else
										{
											fread((char *)poutputs,MAX_OUTS_MINI,nitem,h);
											fread(buf,n-MAX_OUTS_MINI,nitem,h);
										}

//								  fseek(h,4,SEEK_CUR);
										fread( &n, 2, 1, h);
										fread( &nitem, 2, 1, h);
//								  fread(pold_outs_ins+32*sizeof(Str_out_point),1,32*sizeof(Str_in_point),h);
										if( vermini )
											fread((char *)pinputs,n,nitem,h);
										else
										{
											fread((char *)pinputs,MAX_INS_MINI,nitem,h);
											fread((char *)buf,n-MAX_INS_MINI,nitem,h);
										}
									 }
									}
													}
									fclose(h);
								 }
								 clear_semaphore_dos();
								}
									set_semaphore_dos();
									if ((h=fopen(buf1,"wb+"))==NULL)
									{
//									 strcpy(buf, "Error !!!. File not saved                  ");
									 if(pold_outs_ins)
										delete  pold_outs_ins;
									 if(buf)
										 delete buf;
									 clear_semaphore_dos();
									 DisplayMessageT(20, 7, 60, 11, NULL, " Error create file ! ", NULL, Blue, NULL, 3000);
//				int_disk1--;
									 return ERROR_COMM;
									}
//									char *buf=new char[7000];
									clear_semaphore_dos();
									creategauge(&gauge,"Saving file");
									strcpy(buf,panel_text1);
									lin_text[10]=0;
									gauge->GWPuts(5, 10, lin_text, Lightblue, Black);
									lin_text[10]=' ';
									itoa(st, &buf[6],10);
									gauge->GWPuts(5, 10, buf, Lightblue, White);

									long length;
									if(local)
									{
									 length = sizeof(outputs) + sizeof(inputs) + sizeof(vars) + sizeof(controllers) +
																sizeof(analog_mon) + sizeof(arrays) + sizeof(custom_tab) + sizeof(alarms_set) +
																sizeof(weekly_routines) + sizeof(annual_routines) + sizeof(control_groups) +
																MAX_WR * 9 * sizeof(Wr_one_day) + MAX_AR * 46 + sizeof(units);
									 for(i=0;i< MAX_GRPS;i++)
										if(local)
										{
										 if(control_group_elements[i].ptrgrp)
											length += control_group_elements[i].nr_elements*sizeof(Str_grp_element);
										}
									 for(i=0;i< MAX_PRGS;i++)
										if(local)
										{
										 length  += programs[i].bytes;
										}
									}
									else
										length = 13+tblbank[PRG]+tblbank[WR]+tblbank[AR]+tblbank[GRP];
//									float coef = (float)length/20.;
									long coef = ((length*1000L)/20000L)*1000L + (((length*1000L)%20000L)*1000L)/20000L ;
									long ltot = 0;

									set_semaphore_dos();
//  information - length 40 bytes
									t = (long)timesec1970 + (long)timestart;
									ptr = ctime((const long *)&t);
									fwrite( ptr, 26, 1, h);         //time and date
									fwrite( signature, 4, 1, h);    //signature
									fwrite(	&st, 2, 1, h);          //panel number
									fwrite(	&net, 2, 1, h);      //network number
									n = Version;
									fwrite(	&n, 2, 1, h);            //version T3000
									if( local || panel_info->panel_type == T3000 )
										n=0;
									else
										n = panel_info->version;
									fwrite(	&n, 2, 1, h);            //version mini
									memset(buf,0,1000);
									fwrite(	buf, 32, 1, h);      //reserved 32 bytes
									clear_semaphore_dos();

									for(i=0; i<=UNIT; i++)
									{
									 if(i==AMON)
									 {
										 if( !local && panel_info->panel_type == MINI_T3000 )
												continue;
									 }
									 if(i!=DMON && i!=ALARMM)
									 {
										showgauge(gauge, info[i].name);

										nitem = info[i].str_size;
										n = info[i].max_points;
										if(local)
										{
											set_semaphore_dos();
											fwrite(	&n, 2, 1, h);
											fwrite(	&nitem, 2, 1, h);
											fwrite(	info[i].address, nitem, n, h);
								    	clear_semaphore_dos();
											ltot += n*nitem;
										}
										else
										{
											n = tblbank[i];
											ptr = buf;
											if( i==OUT )
											{
											 if( pold_outs_ins ) ptr = (char *)poutputs;
											}
											if( i==IN )
											{
											 if( pold_outs_ins ) ptr = (char *)pinputs;
											}
											if( (r=saveloadpoint(0, i, n, nitem, st,panel_info->panel_type, h, ptr))!=SUCCESS)
													 break;
											ltot++;
										}
										showgauge(gauge, coef, ltot);
									 }
									}

									if(r==SUCCESS)
									{
//									for( i=0;i<MAX_PRGS;i++)
									 btext[0]='P';
									 btext[1]='R';
									 btext[2]='G';
									 btext[3]=' ';
									 btext[4]=' ';
									 btext[5]=0;
									for( i=0;i<tblbank[PRG];i++)
									{
									 itoa(i,&btext[3],10);
									 showgauge(gauge, btext);
									 if(local)
									 {
										n = programs[i].bytes;
										ltot += n;
										set_semaphore_dos();
										fwrite(	&n, 2, 1, h);
										fwrite( program_codes[i], n, 1, h);
									  clear_semaphore_dos();
									 }
									 else
									 {
										l=0;
										delay(30);
										if( (r=net_call(16, i, buf, &l , st, networkaddress,NETCALL_RETRY))!=SUCCESS ) break;
										set_semaphore_dos();
										fwrite(	&l, 2, 1, h);
										fwrite( buf, l, 1, h);
									  clear_semaphore_dos();
//										Delay(100);
										ltot++;
									 }
									 showgauge(gauge, coef, ltot);
									}
//									showgauge(gauge, coef, ltot);
									}
									if(r==SUCCESS)
									{
									 showgauge(gauge, "WR-T");

									 nitem = 9 * sizeof(Wr_one_day);
//									n = MAX_WR * nitem;
									 n = tblbank[WR] * nitem;
									 set_semaphore_dos();
									 fwrite(	&n, 2, 1, h);
									 if(local)
									 {
										fwrite( wr_times, n, 1, h);
										clear_semaphore_dos();
										ltot += n;
									 }
									 else
									 {
//									 char block[9 * sizeof(Wr_one_day)];
//									 for(i=0;i< MAX_WR;i++)
										clear_semaphore_dos();
										for( i=0;i<tblbank[WR];i++)
										{
										 delay(30);
										 if( (r=net_call(WR_TIME+1, i, buf, 0 , st, networkaddress,NETCALL_RETRY))!=SUCCESS ) break;
//										Delay(100);
										 set_semaphore_dos();
										 fwrite( buf, nitem, 1, h);
										 clear_semaphore_dos();
										 ltot++;
										}
									 }
									 showgauge(gauge, coef, ltot);
									}
									if(r==SUCCESS)
									{
									 showgauge(gauge, "AR-D");
//									n = MAX_AR * 46;
									 n = tblbank[AR] * 46;
									 set_semaphore_dos();
									 fwrite(	&n, 2, 1, h);
									 if(local)
									 {
										fwrite( ar_dates, n, 1, h);
										clear_semaphore_dos();
										ltot += n;
									 }
									 else
									 {
//									 char block[46];
//									 for(i=0;i< MAX_AR;i++)
										clear_semaphore_dos();
										for( i=0;i<tblbank[AR];i++)
										{
										 delay(30);
										 if( (r=net_call(AR_Y+1, i, buf, 0 , st, networkaddress,NETCALL_RETRY))!=SUCCESS ) break;
//										Delay(100);
										 set_semaphore_dos();
										 fwrite( buf, 46, 1, h);
										 clear_semaphore_dos();
										 ltot++;
										}
									 }
									 showgauge(gauge, coef, ltot);
									}
									if(r==SUCCESS)
									{
									 Str_grp_element *buff=NULL;
									 set_semaphore_dos();
									 if(!local)
										buff = new Str_grp_element[MAX_ELEM];
									 n = sizeof(Str_grp_element);
									 fwrite(&n, 2, 1, h);
									 clear_semaphore_dos();
									 btext[0]='G';
									 btext[1]='R';
									 btext[2]='P';
									 btext[3]=' ';
									 btext[4]=' ';
									 btext[5]=0;
									 for( i=0;i<tblbank[GRP];i++)
									 {
										itoa(i,&btext[3],10);
										showgauge(gauge, btext);
										if(local)
										{
										 if(control_group_elements[i].ptrgrp)
											n = control_group_elements[i].nr_elements*sizeof(Str_grp_element);
										 else
											n = 0;
										 ltot += n;
										 set_semaphore_dos();
										 fwrite(	&n, 2, 1, h);
										 fwrite( control_group_elements[i].ptrgrp, n, 1, h);
										 clear_semaphore_dos();
										}
										else
										{
										 l=0;
										 delay(30);
										 if( (r=net_call(19, i, (char *)buff, &l, st, networkaddress,NETCALL_RETRY))!=SUCCESS)
										 {
                      l=0;
											if( (r=net_call(19, i, (char *)buff, &l, st, networkaddress,NETCALL_RETRY))!=SUCCESS)
											 break;
										 }
//										Delay(100);
										 set_semaphore_dos();
										 fwrite(	&l, 2, 1, h);
										 fwrite( buff, l, 1, h);
										 clear_semaphore_dos();
										 ltot++;
										}
										showgauge(gauge, coef, ltot);
									 }
//								showgauge(gauge, coef, length);
									 if(!local && buff)
									 {
										set_semaphore_dos();
										delete [] buff;
										clear_semaphore_dos();
									 }
									}
									if(r==SUCCESS)
									{
									 if(local)
									 {
										n = sizeof(Icon_name_table);
										set_semaphore_dos();
										fwrite(	&n, 2, 1, h);
										fwrite( Icon_name_table, n, 1, h);
										clear_semaphore_dos();
									 }
									 else
									 {
										n=0;
										r=net_call(COMMAND_50, ICON_NAME_TABLE_COMMAND, (char*)buf, (unsigned int *)&n, st, networkaddress, NETCALL_RETRY);
										if(r==SUCCESS)
										{
										 n = sizeof(Icon_name_table);
										 set_semaphore_dos();
										 fwrite(	&n, 2, 1, h);
										 fwrite( buf, n, 1, h);
										 clear_semaphore_dos();
										}
                   }
									}
									else
									{
									 DisplayMessageT(20, 9, 60, 13, NULL, " Error saving file! ", NULL, Blue, NULL, 5000);
									}

								 set_semaphore_dos();
								 fclose(h);
								 deletegauge(&gauge);
								 delete [] buf;
								 if(pold_outs_ins)
								 	 delete  pold_outs_ins;
								 clear_semaphore_dos();
								 if( local )
									save_prg_flag = 0;
//		 int_disk1--;
 return r;
}



int Panel::file(int man)
{
	GPopUp *popup;
	uint l;
  int ret=SUCCESS;
	if(man==-1)
	{
	 set_semaphore_dos();
// ******** the old code  ********
//	popup = new GPopUp(mode_text?19:119,mode_text?3:55,(char **)&list9,0,3,SMALL_FONT,5,1);
// *******************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.050  ********
// ********       begin       ********
// ***********************************
	 popup = new GPopUp(MENU_FILE,"need_help",mode_text?19:119,mode_text?3:55,(char **)&list9,0,3,SMALL_FONT,5,1);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.050  ********
// ********        end        ********
// ***********************************
	 clear_semaphore_dos();
//	int man;
	 man = popup->GReturn();
	 G.pGPopUpTable[1].ReleasePopUp(-1);
	 set_semaphore_dos();
	 delete popup;
	 clear_semaphore_dos();
	}				if(man==2)
					{
							if(panel_info1.panel_type == MINI_T3000)
							{
							 if( (ret=net_call(COMMAND_50, WRITEPRGFLASH_COMMAND, NULL, 0, station_num, networkaddress,NETCALL_RETRY))!=SUCCESS )
								 ret=net_call(COMMAND_50, WRITEPRGFLASH_COMMAND, NULL, 0, station_num, networkaddress);
							 DisplayMessage(12, 7, 68, 11, NULL, rebootm, NULL, Black, NULL, 32000);
							}
							return ret;
					}
					 if( man!=-1 )
					 {
						char buf1[65], buf2[65], buf[80], *q;
						union key key;
						char v = 0;
						buf1[0]=0;
						strcpy(tempbuf,prg_text);
						if(!local_panel && (man==0 || man==1))
						{
							 v=3;
							 if(panel_info1.panel_type != MINI_T3000)
							 {
								if( strlen(rtrim(default_prg)) )
								{
								 strcpy(buf1, default_prg);
								}
								v=2;
							 }
						}
/*
						if(ReadYesNo(20, 9, 60, 13, Lightblue, Blue, Black,	Cyan, White,
								 " Remote/Local station ? (R/L) : ",'R','L'))
						{
						 ReadWindow(20, 7, 60, 11, Lightgray, Darkgray, Black,
							 Cyan, White, " Program name : ", buf1, 8);
						 if(!strchr(buf1,'.'))
						 {
							 strcat(buf1,".PRG");
						 }
						 v=2;
						}
*/
					 if(v==0 || v==3)
					 {
						switch (man) {
							case 0:
								 strcpy(buf, loadpanel_text);
								 break;
							case 1:
								 strcpy(buf, savepanel_text);
								 break;
							case 2:
								 strcpy(buf, renamefile_text);
								 break;
							case 3:
								 strcpy(buf, deletefile_text);
								 break;
						}
						if(GetFile(buf,default_prg,Program_Path,tempbuf,buf1,TOPPANELX+3,TOPPANELY+3,1,Lightblue,Blue))
						{
							if(v==0) v=1;
							if(v==3) v=2;
						}
						else
						 v=0;
					 }

					 if(man==1)
						if(v)
						{
							strcpy(buf, savepanel_text);
							itoa(station_num, &buf[strlen(buf)],10);
							strcat(buf, " as ");
							strcat(buf, strupr(buf1));
							strcat(buf, " ? (Y/N): ");

// ********  the old code  ********
//							if(ReadYesNo(15, 9, 75, 13, Lightgray, Darkgray, Black,
//													Cyan, White, buf))
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.051  ********
// ********       begin       ********
// ***********************************
							if(ReadYesNo_help(101,15, 9, 75, 13, Lightgray, Darkgray, Black,
													Cyan, White, buf))
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.051  ********
// ********        end        ********
// ***********************************
							{
							 if(v==2 && !local_panel)
							 {
								int i = 3;
								if( panel_info1.panel_type == MINI_T3000 )
								{
								 saveoldprg(buf1,1);
								 if((ret=savefile(buf1, &panel_info1, tbl_bank, 0))!=SUCCESS)
								 {
									saveoldprg(buf1,0);
								 }
								}
								else
								{
									while(i--)
									{
									l = 13;
									if( net_call(50+100,30,buf1,&l,station_num, networkaddress)==SUCCESS ) break;
									Delay(1000);
									}
								}
//								Delay(3000);
//								savefile(buf1, 0);
							 }
							 else
							 {
								saveoldprg(buf1,2);
//								if(v==1 && !local_panel)
//									savefile(buf1, 0);
								if(v==1 && local_panel)
									savefile(buf1, &Panel_Info1, ptr_panel->table_bank, 1);
							 }
							}
						}
					 if(man==0)
						if(v)
						{
							strcpy(buf, loadpanel_text);
							strcat(buf, strupr(buf1));
							strcat(buf, " ? (Y/N): ");

// ********  the old code  ********
//							if(ReadYesNo(15, 9, 75, 13, Lightgray, Darkgray, Black,
//													Cyan, White, buf))
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.052  ********
// ********       begin       ********
// ***********************************
							if(ReadYesNo_help(100,15, 9, 75, 13, Lightgray, Darkgray, Black,
													Cyan, White, buf))
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.052  ********
// ********        end        ********
// ***********************************
							{
							 if(v==2 && !local_panel)
							 {
								unsigned int i = 2;
								if( panel_info1.panel_type == MINI_T3000 )
								{
								 if( (q=strrchr(buf1,'\\')) == NULL )
									strcpy(default_prg, buf1);
								 else
									strcpy(default_prg, q+1);
								 i = 13;
								 if( net_call(50+100, 33, default_prg, &i, station_num, networkaddress,NETCALL_RETRY)==SUCCESS)
									 loadprg(buf1,&panel_info1,tbl_bank,0);
								}
								else
								{
								 while(i--)
								 {
									l = 13;
									if( net_call(50+100,31,buf1,&l,station_num,networkaddress,NETCALL_RETRY)==SUCCESS ) break;
									Delay(1000);
								 }
								 Delay(100);
								 if(serial_access)	disconnect_serial(1);
								}
							 }
							 else
							 {
//								if(v==1 && !local_panel)
//									loadprg(buf1);
								if(v==1 && local_panel)
									loadprg(buf1,&Panel_Info1,ptr_panel->table_bank, 1);
							 }
							}
						}
/*
						if(man==2)
						{
							strcpy(buf, renamefile_text);
							strcat(buf, strupr(buf1));
							strcat(buf, " as : ");
							memset(buf2,0,65);
							ReadWindow(13, 9, 77, 13, Lightgray, Darkgray, Black,
							 Cyan, White, buf, buf2, 8);
							if(strlen(buf2))
							{
							 char *p;
							 if( (p = strchr(buf2,'.')) ) *p = 0;
							 strcat(buf2, ".prg");
							 set_semaphore_dos();
							 rename(buf1, buf2);
							 clear_semaphore_dos();
							}
						}
						if(man==3)
						{
							strcpy(buf, deletefile_text);
							strcat(buf, strupr(buf1));
							strcat(buf, " ? (Y/N): ");

							if(ReadYesNo(15, 9, 75, 13, Lightgray, Darkgray, Black,
													Cyan, White, buf))
							{
							 set_semaphore_dos();
							 remove(buf1);
							 clear_semaphore_dos();
							}
						}
*/
					 }
 return ret;
}

/*
void upcustomunit(void)
{
 for(int i=0;i<MAX_UNITS;i++)
 {
	int x,y, z;
	z = custom_digital1 - DIG1;
	x =  min(5,strlen(ptr_panel->units[i].digital_units_off));
	memcpy(dig_range_array[z+i].range_text, ptr_panel->units[i].digital_units_off,x);
	dig_range_array[z+i].range_text[x]='/';
	y =  min(5,strlen(ptr_panel->units[i].digital_units_on));
	memcpy(&dig_range_array[z+i].range_text[x+1], ptr_panel->units[i].digital_units_on,x);
	dig_range_array[z+i].range_text[x+1+y]=0;
	strcpy(dig_range_array[z+i].dunits[1], ptr_panel->units[i].digital_units_on);
	strcpy(dig_range_array[z+i].dunits[0], ptr_panel->units[i].digital_units_off);
 }
}
*/


void  getkey(void)
{
 while(!bioskey_new(1));
 int i = bioskey_new(0);
}

void wait(long sec)
{
 long l;
 l = timestart;
 while(timestart < l+sec);
}

void pfarfree(HANDLE handle)
{
	GlobalUnlock( handle);
 	GlobalFree( handle );
}

/*
#ifdef N87
float operator*(float op1, float op2)
{
	return( (op1/1000L)*op2 + (op1%1000L)*op2/1000L );
}
#endif
*/

/*
size_t ffread(void *ptr, size_t size, size_t n, FILE *stream)
{
 int_dos = 1;
 fread( ptr, size, n, stream);
 int_dos = 0;
}

size_t ffwrite(const void *ptr, size_t size, size_t n, FILE * stream)
{
 int_dos = 1;
 fwrite( ptr, size, n, stream);
 int_dos = 0;
}
*/

void clear_color(int lx, int length, int ly, int ry, char *lin_text, int bkgnd, int frgnd)
{
 if( mode_text )
 {
  hide_pointer();
  lin_text[length]=0;
  for(int j=ly;j<=ry;j++)
  {
	mxyputs(lx,j,lin_text,bkgnd,frgnd);
  }
  lin_text[length]=lin_text[0];
  display_pointer();
 }
}

HANDLE graph_h;
void far * far pascal _graphgetmem(unsigned size)
{
			 char far *p;
//			 char huge *q;
//			 mfarmalloc((char far **)&p,size);
//			 q = (char huge *)p;
//			 return q;
//				 return farmalloc(size);
			 p = GlobalLock( graph_h = GlobalAlloc(GMEM_MOVEABLE,size));
			 return p;
}

/* called by the graphics kernel to free memory */
void far pascal _graphfreemem(void far *ptr, unsigned size)
{
 GlobalUnlock( graph_h);
 GlobalFree( graph_h );
//			 mfarfree((char *)ptr);
}


int check_access(int ptype, int num, int mes)
{
 if( access_level==0 )
	right_access = R_READ_WRITE;
 else
	if( access_level==1 )
	 right_access = R_READ_ONLY;
	else
	{
	 right_access = (rights_access>>(ptype*2L))&0x03;
	 if(num != -1 && ptype == GRP && right_access == R_IND)
	 {
		right_access = (screen_right[num*2/8]>>((num*2)%8))&0x03;
	 }
	}
 if( ((mes&R_NA) && right_access == R_NA) || ((mes&1) && right_access == R_READ_ONLY) )
	 DisplayMessage(mode_text?20:160, mode_text?7:150, mode_text?60:500, mode_text?11:210, NULL, " Unauthorized access! ", NULL, Black, NULL, 1200);

 return right_access;
}

void printtime(void)
{
	 char *ptr;
	 t = (long)timesec1970 + (long)timestart;
	 set_semaphore_dos();
	 ptr = ctime((const long *)&t);
	 clear_semaphore_dos();
	 ptr[24] = 0;
	 mxyputs(51,2,ptr,White,Blue1);
}

int get_access(int ex)
{
 char text_buf[241], textflag=0, text_index=0;
 int i,j,gray;
 char *text1 = "NAME     : ";
 char *text2 = "PASSWORD : ";
 char *ptr;
 long n,m;
 if(!mode_text)
 {
  GWindow *D;
	memset(text_buf, 0, 241);
	set_semaphore_dos();
	if( (h=fopen("T3000.TXT","r")) != NULL )
	{
		fread(text_buf, 1, 240, h);
		fclose(h);
		i = strlen(text_buf);
		j = 0;
		while( j+i < 240 )
		{
			memcpy( &text_buf[j], text_buf, i);
			j+=i;
		}
		textflag=j;
	}
	clear_semaphore_dos();
	msettextstyle(DEFAULT_FONT, HORIZ_DIR,1);
//  D = new GWindow(356,340,614,418,0,0);
	D = new GWindow(356,100,614,178,0,0);
	D->GWSet(NULL, Lightgray,Darkgray);
	D->GShowWindow(WIN_ERROR);
	D->GWPuts(1,2,text1, Lightgray, Black);
	D->GWPuts(2,2,text2, Lightgray, Black);
	select_tmp = 0;
	n=timestart;
	m=n;
	while(1)
	{
	 user_name[0]=0;
	 set_semaphore(&screen);
	 if( textflag )
	 {
		setfillstyle(SOLID_FILL, Lightgray);
		bar(4,maxy-28,maxx-4,maxy-4);
		prectangle(4,maxy-28,maxx-4,maxy-4, White);
		prectangle(12,maxy-25,maxx-12,maxy-7, Black);
		prectangle(12,maxy-7,maxx-12,maxy-7, White);
		prectangle(maxx-12,maxy-25,maxx-12,maxy-7, White);
	 }
	 setfillstyle(SOLID_FILL,Black);
	 bar(D->GWx(2)+strlen(text2)*lat_char_n-2, D->GWy(2)-2, D->GWx(2)+(strlen(text2)+9)*lat_char_n,D->GWy(2)+textheight("H")+2);
	 bar(D->GWx(2)+strlen(text2)*lat_char_n-2, D->GWy(1)-2, D->GWx(2)+(strlen(text2)+16)*lat_char_n,D->GWy(1)+textheight("H")+2);
	 pline(D->GWx(2)+strlen(text2)*lat_char_n-1,D->GWy(1),D->GWx(2)+strlen(text2)*lat_char_n-1,D->GWy(1)+textheight("H"),Yellow);
	 clear_semaphore(&screen);
	 while((i=wingets(user_name, D->GWy(1), D->GWx(2)+strlen(text1)*lat_char_n, 16, Black, White, 'A', NULL, 1))==1)
	 {
		if(!timesave)
		{
		 if( save_prg_flag )
		 {
			ptr_panel->savefile(ptr_panel->Default_Program, &Panel_Info1, ptr_panel->table_bank, 1);
			save_prg_flag = 0;
		 }
		 timesave=300000;
		}
		if(!ex)
		{
		 if( timestart > m+1 )
		 {
			if( textflag )
			{
			 set_semaphore(&screen);
			 setfillstyle(SOLID_FILL, Lightgray);
			 bar(14,maxy-19,maxx-14,maxy-8);
			 setcolor(Black);
			 if( text_index+76 < 240 )
			 {
				textflag = text_buf[text_index+76];
				text_buf[text_index+76]=0;
			 }
			 outtextxy(16,maxy-19,&text_buf[text_index]);
			 clear_semaphore(&screen);
			 if( text_index+76 < 240 )
				text_buf[text_index+76] = textflag;
			 if( ++text_index >= 240 ) text_index=0;
			 m=timestart;
			}
		 }
		 if( timestart > n+19 )
		 {
			t = (long)timesec1970 + (long)timestart;
			ptr = ctime((const long *)&t);
			ptr[24] = 0;
			set_semaphore(&screen);
			setfillstyle(SOLID_FILL,Darkgray);
			bar(D->ltop.x+40,D->ltop.y+1, D->ltop.x+240, D->ltop.y+11);
			setcolor(Black);
			outtextxy(D->ltop.x+40, D->ltop.y+2, ptr);
			clear_semaphore(&screen);
			n=timestart;
		 }
		}
		print_alarm_word();
	 }
//  chbkg(D->GWx(2)+strlen(text1)*lat_char_n, D->GWy(1), 16, Black, White);
	 password[0]=0;
	 set_semaphore(&screen);
	 pline(D->GWx(2)+strlen(text2)*lat_char_n-1,D->GWy(2),D->GWx(2)+strlen(text2)*lat_char_n-1,D->GWy(2)+textheight("H"),Yellow);
	 clear_semaphore(&screen);
	 while((i=wingets(password, D->GWy(2), D->GWx(2)+strlen(text2)*lat_char_n, 9, Black, White, 'S', "********", 1))==1)
	 {
		print_alarm_word();
	 }
	 for(i=0;i<MAX_PASSW;i++)
		 if(!strcmp(rtrim(user_name),rtrim(passwords.passwords[i].name)) && !strcmp(rtrim(password),passwords.passwords[i].password) &&
				passwords.passwords[i].password[0] ) break;
	 if(i!=MAX_PASSW)
			break;
	 if( !user_name[0] && !strcmp(rtrim(password),supervisor) ) break;
	}
// chbkg(tx+col*lat_char_n,ty + (row ? 3+row*(2*LINE_SPACE+lung_char_n)+2+2:3+2), width*lat_char_n, Lightgray, Black);

/*

 GWDialog *D = new GWDialog(mode_text?45:360,mode_text?16:340,mode_text?77:600,mode_text?22:440,0,0);
 D->exitCR = 1;
 D->GWSet(NULL, Lightgray,Darkgray);
 D->GShowWindow(DIALOG);

 D->GWPuts(1,2,text1, Lightgray, Black);
 D->GWPuts(2,2,text2, Lightgray, Black);
 D->GDDef_object(NULL, 2+strlen(text1), 1, 16, Darkgray ,Darkgray, user_name, Darkgray ,White);
 D->GDDef_object(NULL, 2+strlen(text2), 2, 9 , Darkgray ,Darkgray, password, Darkgray ,White,"*********");
 D->retnokey = 1;
 while( !(i=D->HandleEvent()) );
 if(D) delete D;
*/
   D->GReleaseWindow();
	 if(D) delete D;
  }
  else
  {
	 Bordergr(45, 4, 77, 10, Blue1, Lightgray, White, White, 1, 0);
	 mxyputs( 46, 5,  "ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿", Lightgray, Black);
	 mxyputs( 46, 6,  "³ NAME     :                 ³", Lightgray, Black);
	 mxyputs( 46, 7,  "ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´", Lightgray, Black);
	 mxyputs( 46, 8,  "³ PASSWORD :                 ³", Lightgray, Black );
	 mxyputs( 46, 9,  "ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ", Lightgray, Black);

	 if(!ex)
		printtime();
	 while(1)
	 {
//	 chbkg(59,6, 15, Darkgray, White);
		chbkg(59,8, 8, Darkgray, White);
		int r;

		j=-1;
		n=timestart;
		grp_time = 120;
		lin_text[16]=0;
		mxyputs(59,6,lin_text,Darkgray, White);
		lin_text[16]=' ';
//	 chbkg(59,6, 15, Darkgray, White);
		mgotoxy(59,6);
		while((r=mgets(user_name,-1,Darkgray, White))==0)
		{
		 char x[50],y[50];
		 if(!timesave)
		 {
			if( save_prg_flag )
			{
			ptr_panel->savefile(ptr_panel->Default_Program, &Panel_Info1, ptr_panel->table_bank, 1);
			save_prg_flag = 0;
			}
			timesave=300000;
		 }
		 if(!ex)
		 {
			if( timestart > n+19 )
			{
			 printtime();
			 n=timestart;
			}
		 }
		 print_alarm_word();
//
//	if(!grp_time)
//	{
//	 if(Station_NUM)
//	 {
//		if(start_apl)
//		{
//			repeat_grp();
//			ex_apl=1;
//			Bordergr(1, 1, 80, 25, Blue1, White, Black, Blue1, 3, 0);
//		}
//		ex_apl=2;
//		break;
//	 }
//	}
		}
//	if(ex_apl) continue;
		if(r!=ex)    //27
		{
//	 if(!user_name[0]) strcpy(user_name,supervisor);
		 lin_text[8]=0;
		 mxyputs(59,8,lin_text,Darkgray, White);
		 lin_text[8]=' ';
		 mgotoxy(59,8);
		 mgets(password,0,Darkgray, White);

		 hidecur();
		 for(i=0;i<MAX_PASSW;i++)
			if(!strcmp(rtrim(user_name),rtrim(passwords.passwords[i].name)) && !strcmp(password,passwords.passwords[i].password) &&
					passwords.passwords[i].password[0] ) break;
		 if(i!=MAX_PASSW)
			break;
		 if( !user_name[0] && !strcmp(password,supervisor) ) break;
		}
		else
		{
		 clear_color(1,80,2,15,lin_text,fond_color,Black);
		 return 0;
		}
	 }
	}
	if( !user_name[0] && !strcmp(password,supervisor) )
	{
	 access_level = 0;
	 default_group=0;
	 rights_access=0;
	}
	else
	{
	 access_level = passwords.passwords[i].access_level;
	 if(ex!=ESC)    //27
		station_num = passwords.passwords[i].default_panel;
	 default_group=passwords.passwords[i].default_group;
	 memcpy(screen_right,  passwords.passwords[i].screen_right, sizeof(passwords.passwords[i].screen_right));
	 rights_access=passwords.passwords[i].rights_access;
	}
	if(station_num == 0)
		 {
#ifndef WORKSTATION
			station_num = Station_NUM;
			memcpy(station_name, station_list[station_num-1].name,NAME_SIZE);
			local_panel = 1;
#endif
		 ;
		 }
	else
		{
		 memcpy(station_name, station_list[station_num-1].name,NAME_SIZE);
		 local_panel = 0;
		 if(ex!=ESC)    //27
		 {
			if(station_num==Station_NUM) local_panel = 1;
			 else  local_panel = 0;
		 }
		}
//	mtextbackground(Black);
//	mtextcolor(Cyan);
//	mgotoxy(1,1);
	i = 1;
	if(ex==ESC)    //27
	 i=2;
	clear_color(1,80,i,25,lin_text,fond_color,Black);

// textbackground(6);
//	clrscr();
	return 1;
}

void disconnect_serial(int d)
{
	  RS232Error result;
	  if(ser_ptr)
		if(ser_ptr->Read_mode() == MASTER )
		{
			set_semaphore_dos();
			chdir(oldpath);
			clear_semaphore_dos();
			disconnect_time=-1;
			GWindow *D=NULL;
			if(d==1)
			 DisplayMessage(mode_text?20:160, mode_text?7:150, mode_text?60:500, mode_text?11:210, ctrlbreak_text, "  Wait for disconnection...  ", &D);

/*
			for(int i=0; i<MAX_Routing_table; i++)
			{
				 if( (i!=ser_ptr->port_number) &&  Routing_table[i].Port.network==Routing_table[ser_ptr->port_number].Port.network )
						if( Routing_table[i].reachabil_status == USER_UNREACHABIL )
							 Routing_table[i].reachabil_status = REACHABIL;
			}
*/
			if( serial_access && d!=2)
			{
				((class PTP *)Routing_table[ser_ptr->port_number].ptr)->NL_parameters.primitive = DL_DISCONNECT_REQUEST;
			  resume(((class PTP *)Routing_table[ser_ptr->port_number].ptr)->task);
			  Delay(3000);
//				result = net_call(50+100, 20, NULL, 0, station_num, networkaddress, 0, 20);
//				result = ser_ptr->Serial_control( 50, WRITE, 0, NULL, 20 );
			}
			if( ser_ptr->modem_active )
			{
				if( ( ser_ptr->modem_status = ser_ptr->modem_obj->Disconnect() ) != MODEM_SUCCESS )
				{
				 ;
				}
				ser_ptr->connection_established = 0;
				Delay(1000);
			}
			ser_ptr->activity = FREE;
			if( serial_access )
			{
				ser_ptr->FlushRXbuffer();
				ser_ptr->FlushTXbuffer();
				setlocalpanel();
				serial_access = 0;
				ser_ptr->Set_mode( SLAVE );
				if(console_mode) ser_ptr->Set_mode( MASTER );
				else
				{
				 memcpy( (char*)station_list, (char*)ptr_panel->local_stations,
																								MAX_STATIONS*sizeof( Station_point ) );
				 memcpy( (char*)&passwords, (char*)&ptr_panel->passwords,	sizeof( passwords ) );
				}
				memcpy(password, Password, sizeof(password));
				memcpy(user_name, User_name, sizeof(user_name));
				((class PTP *)Routing_table[ser_ptr->port_number].ptr)->panel_info1.network = comm_info[ser_ptr->com_port].NetworkAddress;
			}
	   Delay(1000);
		 refresh_time_init = 150;
		 ser_ptr = NULL;
		 if(D) DeleteMessage(D);
		}
}

/*
	2 bytes  : version
	10 bytes : reserved
	2 bytes  : Station_NUM
	16 bytes : Station_NAME
	2 bytes  : nr_boards
	2 bytes  : sizeof(Board_info);
	MAX_BOARDS*sizeof(Board_info) bytes  : boards
	2 bytes  : sizeof(Comm_Info)
	MAX_COMM_INFO * sizeof(Comm_Info) bytes : comm_info
*/
void save_config(int what)
{
	char buf[13]={0,0,0,0,0};
	char fname[65];
	int n;
	FILE *h;
	strcpy(fname, oldpath);
	strcat(fname,"\\config.cnf");
	set_semaphore_dos();
	if( (h=fopen(fname,"rb+"))==NULL)
		if( (h=fopen(fname,"wb+"))==NULL)
		{
			clear_semaphore_dos();
			return;
		}

	 fseek(h,CNF_VER ,SEEK_SET);
	 fwrite(&Version, 2, 1, h);
	 fwrite(buf, 10, 1, h);
	 if( what & CNF_BOARD_INFO )
	 {
		 fseek(h,CNF_STATION_NUM,SEEK_SET);
		 fwrite(&Station_NUM, 2, 1, h);
		 fwrite(Station_NAME, 16, 1, h);
		 fwrite(&NetworkAddress, 1, 2, h);
		 fwrite(NetworkName, 16, 1, h);

		 fwrite(&nr_boards, 2, 1, h);
		 n=sizeof(Board_info);
		 fwrite(&n, 2, 1, h);
		 fwrite(boards, MAX_BOARDS*sizeof(Board_info), 1, h);
	 }
	 if( what & CNF_COMM )
	 {
		 fseek(h,CNF_SIZE_COMM_INFO, SEEK_SET);
		 n=sizeof(Comm_Info);
		 fwrite(&n, 2, 1, h);
		 fwrite(comm_info, MAX_COMM_INFO * sizeof(Comm_Info), 1, h);
		 fwrite(&IPX_enabled, 1, 1, h);
	 }
/*
	 if( what & CNF_MODEM_INFO )
	 {
		 fseek(h,CNF_MODEM,SEEK_SET);
		 fwrite(&ModemDataBase[0], sizeof(ModemCapabilities), 1, h);
	 }
*/
	 if( what & CNF_PATH_INFO )
	 {
		 fseek(h,CNF_PROGRAM_PATH,SEEK_SET);
		 fwrite(ptr_panel->Program_Path, 64, 1, h);
		 fwrite(ptr_panel->Descriptor_Path, 64, 1, h);
		 fwrite(ptr_panel->Basic_Path, 64, 1, h);
		 fwrite(ptr_panel->Monitor_Path, 64, 1, h);
		 fwrite(ptr_panel->Graphics_Path, 64, 1, h);
		 fwrite(ptr_panel->Default_Program, 13, 1, h);
	 }
	 if( what & CNF_CONSOLE_INFO )
	 {
		 fseek(h,CNF_CONSOLE, SEEK_SET);
		 fwrite(&console_mode, 1, 1, h);
	 }
/*
	 if( what & CNF_MODEM_INFO )
	 {
		 fseek(h,CNF_RINGS, SEEK_SET);
		 fwrite(&number_rings, 1, 1, h);
	 }
*/
	 if( what & CNF_STATION_INFO )
	 {
		 fseek(h,CNF_STATION_LIST,SEEK_SET);
		 fwrite(station_list,sizeof(Station_point),MAX_STATIONS,h);
	 }
	 if( what & CNF_PASS_INFO )
	 {
		 fseek(h,CNF_IND_PASS,SEEK_SET);
		 fwrite(&passwords.ind_passwords,2,1,h);
 //		 fwrite(passwords.passwords,sizeof(Password_point),passwords.ind_passwords,h);
		 fwrite(passwords.passwords,sizeof(Password_point),MAX_PASSW,h);
	 }

	 if( what & CNF_IORATE )
	 {
		 fseek(h,CNF_IORATE_OFF,SEEK_SET);
		 fwrite(&read_inputs_rate,1,1,h);
		 fwrite(&write_outputs_rate,1,1,h);
	 }

	 fclose(h);

	clear_semaphore_dos();
}

/////////////////////////////
// print function source:
//
/////////////////////////////

int pprint(void)
{
	int i,j,errorcode;
	char *string,file[20];
//	fprintf(stdprn,"%c%c%c",27,91,75);  // initializes the printer porter
//	errorcode=biosprint(1, 0, 0);   // initializes the printer porter
//	errorcode=biosprint(2, 0, 0);   // reads the printer status
/*	if ( !(errorcode&0x10) || (!errorcode || (errorcode&0x01) || (errorcode&0x20) || (errorcode&0x08)) )
	{
		mxyputs(30,10,"Printer not ready...", Lightgray, Black);
		mxyputs(26,12,"Please turn on your printer.", Lightgray, Black);

		delay(DELAY_TIME);

		mxyputs(30,10,"                    ", White,White);
		mxyputs(26,12,"                            ", White, White);
		return 0;
	}
	*/
	string="point.txt";
	strcpy(file,string);

	remove(file);

	FILE *f;
/*
	if((f=fopen("point.txt","at+"))==NULL)
	{
		mxyputs(30,10,"can't not open file error!",Lightgray,Black);
		delay(DELAY_TIME);
		mxyputs(30,10,"                          ",White,White);
	}
*/
// **************************************************************
// *******  Adi Aug 27/97 ***************************************
// *************   begin  ***************************************
	printpoint( 21,panel_info1.panel_type,station_num,networkaddress,0);
	printpoint( 20,panel_info1.panel_type,station_num,networkaddress,0);
	printpoint( 22,panel_info1.panel_type,station_num,networkaddress,0);
	printpoint( 23,panel_info1.panel_type,station_num,networkaddress,0);

	printpoint( 24,panel_info1.panel_type,station_num,networkaddress,0);
	printpoint( 25,panel_info1.panel_type,station_num,networkaddress,0);

	j=printpoint( 26,panel_info1.panel_type,station_num,networkaddress,0);
	for(i=0; i<j-1; i++)		//tbl_bank[WR]
		printpoint( 1,panel_info1.panel_type,station_num,networkaddress,i+1,0);

	j=printpoint( 27,panel_info1.panel_type,station_num,networkaddress,0);
	for(i=0; i<j-1; i++)		//tbl_bank[AR]
		printpoint( 2,panel_info1.panel_type,station_num,networkaddress,i+1,0);

	printpoint( 28,panel_info1.panel_type,station_num,networkaddress,0);
	PRINTFLAG=1;
	if( panel_info1.panel_type==T3000 )
		printpoint( 30,panel_info1.panel_type,station_num,networkaddress,0);
	PRINTFLAG=0;
	printpoint( 32,panel_info1.panel_type,station_num,networkaddress,0);
	printpoint( 33,panel_info1.panel_type,station_num,networkaddress,0);

	controlbasicSource();

//	syslistprint();    // moved out from printpoint

// ***************  Adi Aug 27/97 *******************************
// *****************   end        *******************************
// **************************************************************

//	sendtoprint();
	if(sendtoprint()==-1)
		if(remove(file)==0)return 0;
		else return -1;
	else
		return 0;

}

int printpoint(int man, int Panel_type, int Panel, int Network, int arg,int flag)
{
				int l,point_type,rx,lx,stk=GRIDINS,ttype=0,ly,ry,row,point_size;
				unsigned long temp;
				char ca=0, *ptitle;
//				mrow   = 16;
				ptitle = NULL;

				lx = 2;	ly = 3;	rx = 79; ry = 21;
			switch (man) {
				 case 1:
							point_type=WR_TIME;
							ttype = INDIVIDUAL;
							row=8;
							break;
				 case 2:
							point_type=AR_Y;
							row=7;
							ttype = INDIVIDUAL;
							break;
				 case M2+0:
							point_type=GRP;
//							row=number_points[point_type];
							break;
				 case M2+1:
							point_type=PRG;
//							row=number_points[point_type];
							break;
				 case M2+3:
							point_type=OUT;
//							row=number_points[point_type];
							stk = GRID;
							break;
				 case M2+2:
							point_type=IN;
//							row=number_points[point_type];
							stk = GRID;
							break;
				 case M2+4:
							point_type=VAR;
//							row=number_points[point_type];
							stk = GRID;
							break;
				 case M2+5:
							point_type=CON;
//							row=number_points[point_type];
							break;
				 case M2+6:
							point_type=WR;
//							row=number_points[point_type];
							break;
				 case M2+7:
							point_type=AR;
//							row=number_points[point_type];
							break;
				 case M2+8:
							point_type=AY;
//							row=number_points[point_type];
							break;
				 case M3+0:
							point_type=AMON;
              printamon = 1;
//							row=number_points[point_type];
							break;
				 case M3+2:
							point_type=UNIT;
//							row=number_points[point_type];
							break;
				 case M3+3:
							point_type=ALARMM;
//							row=number_points[point_type];
							break;
				 }
// **************************************************************
// *******  Adi Aug 27/97 ***************************************
// *************   begin  ***************************************
				 if( man!=1 && man!=2 )
					row=tbl_bank[point_type];
// *************   end  *****************************************
// **********  Adi Aug 27/97 ************************************
// **************************************************************

//				ptr_panel->info[point_type].str_size; // point size
//				row=tbl_bank[point_type];
/*				if( (ca) || (check_access(point_type)!=R_NA) )
				{
				 GGrid *wgrid;
				 int row;
				 row=mrow;
				 switch(point_type){
				 case GRP:
				 case PRG:
				 case OUT:
				 case IN:
				 case VAR:
				 case CON:
				 case WR:
				 case AR:
				 case AY:
				 case AMON:
				 case UNIT:
					 row=min(mrow,tbl_bank[point_type]);

					 break;
				 }
*/
		GGrid *wgrid;
		wgrid=new GGrid( lx, ly, rx, ry, ptitle, Lightgray, Darkgray, Black,
						 stk, NULL, point_type, Panel_type, Panel, Network,
						 ttype, arg, SMALL_FONT,5,1);
//		row=number_points[point_type];// get from #4392

		if(point_type==AR_Y)
		{
			for(int i = 0; i<4;i++) {
				wgrid->obj.ar_y->Quarter(i);
				l=wgrid->GPrintGrid(row);
			}
		}
		else
			l=wgrid->GPrintGrid(row);

//		if(point_type==PRG) { syslistprint(); }
		delete wgrid;
    printamon = 0;
		return l;
}

int print_basic(int l, byte *s)
{
	char temp[150];
	char c[2],r[3],t[2];
	int i;
	t[1]='\0';
	i=0;
	c[0]='\n';	c[1]='\0';
	r[0]='\r';	r[1]='0';	r[2]='\0';
	FILE *f;
	if((f=fopen("point.txt","at+"))==NULL)
	{
		mxyputs(30,10,"can't not open file error!",Lightgray,Black);
		delay(DELAY_TIME);
		lin_text[27]=0;
		mxyputs(30,10,lin_text,White,White);
		lin_text[27]=' ';
	}

	fwrite(c,1,1,f);
	fwrite(c,1,1,f);
	while(*s!=c[1])  //end of file
	{
		while(*s!=r[0])      // end of line \r\n, here judge \r
		{
			t[0]=*s;
			fwrite(t,1,1,f);
			s++;
		}
		s++;
		t[0]=*s;
		fwrite(t,1,1,f);
		s++;
	}
	fclose(f);
}


void controlbasicSource(void)
{
	byte var_type,point_type;
	int  num_net,num_point,num_panel;
	char buf[40];
	Point_Net p;
	Str_program_point *prgs;
	set_semaphore_dos();
	char *programsource = new char [PROGRAM_SIZE];
	prgs = new Str_program_point [32];
	clear_semaphore_dos();
	int length,r,ret;
	set_semaphore_dos();
	char *code = new char [PROGRAM_SIZE];
	clear_semaphore_dos();
	Str_program_point block;
  unsigned t[2];

	for( int i = 0;  i< tbl_bank[PRG]; i++ )
	{
		r=1;
		if (!local_request(station_num,networkaddress))
		{
			Delay(100);
			if( net_call(20, ((PRG+1)<<8)+ i, (char *)&block, 0 ,station_num, networkaddress) )
			{
				r=0;
			}
		}
		else
			memmove(&block,&ptr_panel->programs[i],sizeof(Str_program_point));

    ret = 0;
		if(r)
		{
		 if( local_request(station_num, networkaddress) )
		 {
			movedata(FP_SEG(ptr_panel->program_codes[i]),FP_OFF(ptr_panel->program_codes[i]) ,FP_SEG(code),FP_OFF(code), block.bytes);
		 }
		 else
		 {
			 Delay(100);
			 ret=net_call(READPROGRAMCODE_T3000, i, code, 0, station_num, networkaddress, NETCALL_SIGN, TIMEOUT_NETCALL, (char *)&t[0]);
		 }

		 if(!ret)
		 {
			length = basicprogram1(programsource, code,
				&block, i+1, station_num, networkaddress);

			if( length )
			{
			p.putpoint(i, PRG + 1, station_num-1, networkaddress);
			pointtotext(buf,&p);
			strcpy(buf,ispoint(buf,&num_point,&var_type, &point_type, &num_panel, &num_net));
			strcat(buf,"\r\n----------\r\n");
			print_basic(strlen(buf),buf);
			}
		  print_basic(length,programsource);
		 }
		}

	}

	set_semaphore_dos();
	delete programsource;
	delete prgs;
	clear_semaphore_dos();

}

int printchar(char c)
{
 int n;
		if ( (n=biosprint(2, 0, 0))&0x10 )
		{
			while( !((n=biosprint(2, 0, 0))&0x80) )
			{
				if ( n&0x01 || n&0x20 || n&0x08 ) break;
			}
			if ( n&0x80 && n&0x10)
			{
				biosprint(0, c, 0);
				while( !((n=biosprint(2, 0, 0))&0x80) )
				{
				 if ( n&0x01 || n&0x20 || n&0x08 ) break;
				}
//				if ( !(n&0x80 && n&0x10) ) break;
			}
		}
		if ( n&0x80 && n&0x10)
		{
		 return 1;
		}
/*
 int errorcode;
 errorcode=biosprint(2, 0, 0);
 if ( !(errorcode&0x10) || (!errorcode || (errorcode&0x01) || (errorcode&0x20) || (errorcode&0x08)) )
	 return 1;
 return 0;
*/
 return 0;
}

int sendtoprint(void)
{
	char *file;
	int page_number,i,errorcode;
	int c;                 //Adi Aug 27,97
	register line=0;
	FILE *f;

	fpp=stdprn;

 // Adi Aug27,97
 errorcode=biosprint(1, 0, 0);
 errorcode=biosprint(2, 0, 0);
 if ( !(errorcode&0x10) || (!errorcode || (errorcode&0x01) || (errorcode&0x20) || (errorcode&0x08)) )
 {
		DisplayMessageT(20, 7, 60, 11, NULL, " Printer not ready! ", NULL, Blue, NULL, 3000);
 }
 else
 {
	set_semaphore_dos();
	if((f=fopen("point.txt","rt"))!=NULL)
	{
//		mxyputs(30,10,"Not busy.\n",Lightgray,Black);
//		delay(DELAY_TIME);
//		mxyputs(30,10,"           ",White,White);
	 if((page_number=countline(f))==-1){
		mxyputs(30,10,"Data empty!\n",Lightgray,Black);
		delay(DELAY_TIME);
		lin_text[13]=0;
		mxyputs(30,10,lin_text,White,White);
		lin_text[13]=' ';
		fclose(f);                     // Adi Aug27,97
		clear_semaphore_dos();
		return 0;
	 }
	 fseek(f, 0, SEEK_SET	);
//	 fclose(f);
	}
	else
	{
		mxyputs(30,10,"Open file error!",Lightgray,Black);
		delay(DELAY_TIME);
		lin_text[22]=0;
		mxyputs(30,10,lin_text,White,White);
		lin_text[22]=' ';
		clear_semaphore_dos();
		return 0;
	}
	clear_semaphore_dos();

	for( register page=1; page<=page_number; page++ )
	{
		headprint();
		line=0;

		set_semaphore_dos();
		while(((c=fgetc(f))!=EOF) && (line++<=LINE_A4))
		{
			while(c!='\n' && c!=EOF )     //   Adi Aug 27,97
			{
				printchar(c);
//					fputc(c,fpp);
				c=fgetc(f);
			}
				printchar('\n');
				printchar('\r');
//			 fputc('\n',fpp);
//			 fputc('\r',fpp);
		// send a return to printer;
			clear_semaphore_dos();
			set_semaphore_dos();
		}
		if(c==EOF && line < LINE_A4	)
		{
			i=LINE_A4 - line;
			while(i--!=0 )
			{
				printchar('\n');
				printchar('\r');
//				fputc('\n',fpp);
//				fputc('\r',fpp);
			}
		}
		footprint(page_number,page);
		clear_semaphore_dos();
		set_semaphore_dos();
	}
	fclose(f);
 }
// fclose(fpp);

 remove("print.txt");
 c=rename("point.txt","print.txt");
 clear_semaphore_dos();
/*
	file="point.txt";
	if (remove(file) == 0)
		return 0;
	else
		return -1;
*/
 return 0;
}


int countline(FILE *s)
{
		int i,page_number;
		int c;                 //Adi Aug 27,97
		i=0;
		c=fgetc(s);
		if(c==EOF)
		{
			mxyputs(30,10,"Data empty!\n",Lightgray,Black);
			delay(DELAY_TIME);
			lin_text[13]=0;
			mxyputs(30,10,lin_text,Lightgray,Black);
			lin_text[13]=' ';
			return -1;
		}
		while(c!=EOF)
		{
				while(c!='\n'&&c!=EOF)    // Adi Aug 27,97
				{
					c=fgetc(s);
				}
				i++;
				c=fgetc(s);
		}

		if( i % LINE_A4 != 0)
		page_number = i/LINE_A4+1;
	else
		page_number = i/LINE_A4;

		return page_number;
}


int footprint(int total_page_number, int number_of_page)
{
	char *c,temp[30];
	c=" / ";
	temp[0]='\0';
	int length,i=0;

	char string[10],string1[10];
	itoa(total_page_number,string,10);
	itoa(number_of_page,string1,10);
	strcat(temp,string1);
	strcat(temp,c);
	strcat(temp,string);
	length=strlen(temp);

	while(temp[i]!='\0')
	{
		printchar(temp[i++]);
//			fputc(temp[i++],fpp);  //fpp
	}
		printchar('\n');
		printchar('\r');
		printchar('\n');
		printchar('\r');
//	 fputc('\n',fpp);
//	 fputc('\r',fpp);
//	 fputc('\n',fpp);
//	 fputc('\r',fpp);
		printchar(13);
//		printchar(12);
//	 fprintf(stdprn,"%c%c",13,12);

	if(i==length)return 1;
	else return 0;
}

int headprint(void)
{
	int spacefill,i,j=0;
	char *ptr;

	ptr="Copyright@ Temco Control Ltd.Co";

	spacefill = ( 80-strlen( ptr ) ) / 2 ;
	i=spacefill+strlen(ptr);

	while(spacefill--)
	{
		printchar(' ');
//			fputc(' ',fpp);   //fpp
	}
	while(*ptr!='\0')
	{
		printchar(*ptr);
//			fputc(*ptr,fpp);
		ptr++;  j++;
	}
		printchar('\n');
		printchar('\r');
//	 fputc('\n',fpp);
//	 fputc('\r',fpp);
	if(i==j) return 0;
	else return -1;
}

/*
int status_printer(void)
{
	int status;

	status=biosprint(STATUS_READ,0,PORTNUM);
	if (status & 0x01){
	  mxyputs(30,10,"Device time out.\n",Lightgray,Black);
	  delay(DELAY_TIME);
	  mxyputs(30,10,"                  ",White,White);
	  exit(0);
	}
	if (status & 0x08){
	  mxyputs(30,10,"I/O error.\n",Lightgray,Black);
	  delay(DELAY_TIME);
	  mxyputs(30,10,"            ",White,White);
	  exit(0);
	}
// if (status & 0x10){
//	  printf("Selected.\n");
//	  return 1;
//   }
	if (status & 0x20){
	  mxyputs(30,10,"Out of paper.\n",Lightgray,Black);
	  delay(DELAY_TIME);
	  mxyputs(30,10,"               ",White,White);
	  return 0;
	}

	if (status & 0x40){
	  mxyputs(30,10,"Acknowledge.\n",Lightgray,Black);
	  delay(DELAY_TIME);
	  mxyputs(30,10,"              ",White,White);
	  return 1;
	}
//   if (status & 0x80)
//	  mxyputs(30,10,"Not busy.\n",Lightgray,black);
		delay(DELAY_TIME);
	  mxyputs(30,10,"           ",White,White);

} */

int syslistprint( void )
{
	 FILE *f;
	 FILEHANDLE fh;
	 RECORDNUMBER NRec;
	 int fields_number,i,j,k,l1,kk,jj,field_wide[]={20,30,15};
	 char buf[80],string[2];
	 string[0]='\n';
	 string[1]='\0';
	 const char *s="System List";
	 char *field_name[]={"Sys_Name            ",         // char sys_name
						"Phone_List                    ",// char phone_list
						"Directory      "         // char directory
						};
											//	 char menu_file[15];
											//	 int  baud_rate;
										// these two needn't to be printed
	if((f=fopen("point.txt","at+"))==NULL)
	{
		gotoxy(10,20);
		printf("can't not open file error!");
	}

	if( FXOpen("syslist.dbf", &fh, READWRITE ) == FX_SUCCESS )
	{
		FXNRecs( fh, &NRec ); //data number
		FXNFields(fh,&fields_number);

		fwrite(s, strlen(s), 1, f);
		fwrite(string,strlen(string),1,f);

		for( i=0;i<3;i++)
		{
			fwrite(field_name[i],strlen(field_name[i]),1,f);
			fwrite("|",1,1,f);
		}
		fwrite(string,strlen(string),1,f);

		for( i=0; i<NRec; i++)
		{
			FXGetRec(fh);
			kk=0;jj=0;
			for( j=0; j<fields_number-2; j++) // don't print last two field
			{
					FXGetAlpha( fh, j+1, FXFldSize(fh, j+1), buf);
								//	 the buf store the field contents
					if(j==0)
					{
						while(kk<=strlen(buf)){if(buf[kk++]==' ')jj++;}
							// count blank space
						if(jj==strlen(buf))
						{
             fclose(f);
						 return 0;
						}
							// if field blank then return
				  }
				  l1=field_wide[j]-strlen(buf);
				  for( k=0;k<l1;k++)
				  {
					   strcat(buf," ");
				  }
				  fwrite(buf,strlen(buf),1,f);
				  fwrite("|",1,1,f);
			}
            fwrite(string,strlen(string),1,f);
		}
	}
	FXClose( fh );
	fclose(f);
	return 1;
}

////////////////////////////////*/

