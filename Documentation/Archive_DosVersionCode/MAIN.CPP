#define MTKERNEL

//#pragma inline
#include <stdio.h>
#include <dos.h>
#include <mem.h>
#include <alloc.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <sys\timeb.h>
#include <bios.h>
#include <graphics.h>
#include "mouse.h"
#include <windows.h>
#include "aio.h"
#include "t3000def.h"
#include "mtkernel.h"
#include "vga12.h"
//#include "netbios.h"
#include "color.hpp"
#include "colormap.hpp"
#include "rs485.h"
#include "t3000hlp.h"


#define EGAVGA 9
#define TEXT_FOND_COLOR White


extern void mclrscr(char x1, char y1, char x2, char y2, char col);
extern void get16( rgb * pal, int nclrs );

extern Pshape ARROW;
extern int Black;
extern int White;
extern int dtr;
extern int maxx;
extern int maxy;
extern char text, interface_mode;
extern int mode_graph;
extern int fond_color;
extern int lat_char_n;
extern int lung_char_n;
extern void changechar(int arg=0);
extern void restorechar(int arg=0);
extern int setmousetext(void);
extern int setregister(int set);
extern char control;
extern char *ontext;
extern rgb init_pal[16];
extern Panel *ptr_panel;
extern int mode_text;

extern int serial_init( void );
extern int modem_init( void );
extern int dial_init( void );
extern int miscellaneous_init( void );
extern int fnc_exec_virtual_code(void);
extern int savemonitors(void);
extern int alarmtask(void);
extern int nettask(void);
extern int proj(void);
extern int MSTP_Master_node( void );
extern int rs485_receive_frame( void );
extern int ServerTSM( void );

#ifdef NET_BAC_COMM
extern int net_bac_task(void);
char huge stack_NET_BAC[stack_NETWORK_SIZE];
#endif

//char huge stack_PROJ[stack_PROJ_SIZE];

#ifndef WORKSTATION
char huge stack_VIRTUAL[stack_VIRTUAL_SIZE];
char huge stack_MONITOR[stack_MONITOR_SIZE];
#endif
char huge stack_DIAL[stack_DIAL_SIZE];
char huge stack_MISCELLANEOUS[stack_MISCELLANEOUS_SIZE];
char huge stack_ALARMTASK[stack_ALARMTASK_SIZE];
char huge stack_NETTASK[stack_NETTASK_SIZE];
char huge stack_MSTP_Master_node[stack_MSTP_Master_node_SIZE*RS485TASKS];
//char huge stack_rs485_receive_frame[stack_rs485_receive_frame_SIZE];
char huge stack_ServerTSM[stack_ServerTSM_SIZE];
char huge stack_PTP[stack_PTP_SIZE*RS232TASKS];

void interrupt ( *oldhandler)(__CPPARGS);
//void interrupt ( *oldhandler_mouse)(__CPPARGS);

//extern "C" void setcallback(void);
//extern "C" void realint8(void);
//extern "C" void hook(void);
//extern "C" void unhook(void);

/*
#ifdef NETWORK_COMM
extern int task_control(void);
char huge stack_NETWORK[stack_NETWORK_SIZE];
#endif
*/

/* Timer interrupt task sheduller */
//static unsigned pri,i,j;
//unsigned char *ptr_dos_flag;
int xscreen=10, yscreen=10;
int dxscreen=1, dyscreen=0;

//unsigned ss_proj,	sp_proj;

//unsigned int statistic_period, statistic[3];
int line_style=1;

//int_regs *r;

int time_key=1;
char simulate;
int time_last_key;

struct input_buffer {
		unsigned time;
		union {
			int   i;
			char  key[2];
			} key;
		};
struct input_buffer inp_buffer[11]
		={
						 {0,32},
						 {0,'G'},
						 {0,'R'},
						 {0,'P'},
						 {0,'$'},
						 {0,'$'},
						 {0,'$'},
						 {0,'$'},
						 {0,'$'},
						 {0,'$'}
		 };
struct input_buffer *input_buffer;

int ind_input_buffer;
int def_macro;

unsigned segA000;

unsigned long timesec1970;  // sec la inceputul programului
unsigned long timestart;    // sec de la inceputul programului
//unsigned long ora_start_sec;

char month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
struct  time ora_start;         // ora la inceputul programului
unsigned long  ora_current_sec; // ora curenta exprimata in secunde
//struct  time  ora_current;      // ora curenta
Time_block ora_current;
int milisec;
long microsec;
//char dayofweek;
//struct dosdate_t dos_date;
char onesec,onemin,tenmin,tensec;
//long onesec_virtual;
extern int pixvar;
extern int miliseclast;
extern byte console_mode;

int indarray;
//int int_dos;

unsigned real_ss;
real_mode_str real_mode_callback;
real_mode_str real_mode;
void (*real_oldHandler)(void);


task_struct tasks[NUM_TASKS];
unsigned  read_mon_flag = 0; // i/o semaphore
unsigned  dos_flag = 0; // i/o semaphore
unsigned  dos_host = 0;
//unsigned  serial_wait[2] = { 0, 0 }; // i/o semaphore
unsigned  screen = 0; // i/o semaphore
//unsigned  memory = 0; // i/o semaphore
unsigned  t3000_flag = 0; // i/o semaphore
unsigned  print_sem = 0; // i/o semaphore

char far *vid_mem;	// pointer to video memory

unsigned oldss, oldsp;
int tswitch = 0;      		// task index
//static char tasking = 1;           // tasking system enabled
//static char single_task = 0;       // single task flag off

int setvectint8;
int communication;
int gdriver, grmode, errorcode;
char timecount;

char loaddesstart;
struct timeb tb;

/*
task_struct *ptasks;
char tts[20][12];
char (*ts1)[12]=tts;
char *pc;
int indts;
//int tic[20][10];
*/


//   /C /G /A /N=networknumber /D=NO
void main(int argc, char *argv[])
{
	text = ASCII_FONT;
	interface_mode = MODE_TEXT;
	console_mode=0;
	loaddesstart=1;
	control = 1;
	for( int i=1; i<argc; i++)
	{
			if( *argv[i] == '/' )
			{
				 if(!strcmp( argv[i] + 1, "C"))
				 {
					// control=1
					control = 1;
					console_mode=0;
					continue;
				 }
				 if(!strcmp( argv[i] + 1, "S"))
				 {
					// simulator: control = 0
						control = 0;
						continue;
				 }
				 if(!strcmp( argv[i] + 1, "H"))
				 {
					  // new setchar = 0
					  text = 0;
					  continue;
				 }
				 if(!strcmp( argv[i] + 1, "G"))
				 {
					 // new setchar = 0
						interface_mode = MODE_GRAPHIC;
						continue;
				 }
				 if(!strcmp( argv[i] + 1, "A"))
				 {
						text = ASCII_FONT;
						continue;
				 }
				 if(!strcmp( argv[i] + 1, "G"))
				 {
						// network number
						if(  *(argv[i] + 2)=='=' )
							 NetworkAddress = atoi((argv[i] + 3)) ;
						continue;
				 }
				 if(!strcmp( argv[i] + 1, "D=NO"))
				 {
						loaddesstart=0;
						continue;
				 }
				 if(!strcmp( argv[i] + 1, "DTR=1"))
				 {
						dtr = 1;
						continue;
				 }
				 if(!strcmp( argv[i] + 1, "L"))
				 {
						def_macro = 1;
						continue;
				 }
				 if(!strcmp( argv[i] + 1, "DEMO"))
				 {
						simulate = 1;
						continue;
				 }
			}
	}

	segA000 = FP_SEG(MK_FP(__SegA000,0));

	init_tasks();
	mclrscr(1, 1, 80, 25, Lightgray);
	errorcode=biosprint(1, 0, 0);
	errorcode=biosprint(2, 0, 0);
	if ( !(errorcode&0x10) || (!errorcode || (errorcode&0x01) || (errorcode&0x20) || (errorcode&0x08)) )
	{
		mxyputs(30,10,"Printer not ready...", Lightgray, Black);
	  delay(500);
	}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.058  ********
// ********       begin       ********
// ***********************************
	Init_help();
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.058  ********
// ********        end        ********
// ***********************************

	if( !(bioskey(2)&0x40) )
	{
	 asm {
		mov al,0edh
		out 60h,al
		mov cx,2100h
		}
	 delay:  asm  loop delay
	 asm {
		mov al,04h
		out 60h,al
	 }
	 ontext=(char *)MK_FP(__Seg0040,0x17);
	 *ontext |= 0x40;
	 delay(3000);
	}

	errorcode = registerbgifont(small_font);

/* detect graphics hardware available */
	mode_graph = 1;
	gdriver=DETECT;
	detectgraph(&gdriver, &grmode);
  if(gdriver==HERCMONO)
	{
	 errorcode = registerbgidriver(Herc_driver);
	 mode_graph = HERCMONO;
	 text = ASCII_FONT;
	}
	else
	if(gdriver==VGA)
	{
		errorcode = registerbgidriver(EGAVGA_driver);
		mode_graph = EGAVGA;
	}
	else
/*
	 if(gdriver==CGA)
	 {
		errorcode = registerbgidriver(CGA_driver);
		mode_graph = EGAVGA;
	 }
	 else
*/
		mode_graph = 0;

	if (errorcode < 0 && mode_graph)
  {
//	 printf("Graphics error: %s\n", grapherrormsg(errorcode));
//	 printf("Press any key to halt:");
//	 getch();
	 exit(1);
	}

///////////////------------
	fond_color = TEXT_FOND_COLOR;
	lat_char_n = 1;
	lung_char_n = 1;

	changechar(1);
	setregister(1);
	setmousetext();
//////////////////--------------

/* initialize graphics and local variables */
	initgraph(&gdriver, &grmode, "");

/* read result of initialization */
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
	 printf("Graphics error: %s\n", grapherrormsg(errorcode));
//	 printf("Press any key to halt:");
//	 getch();
	 exit(1); /* terminate with an error code */
	}

	maxx = getmaxx();
	maxy = getmaxy();
	settextstyle(SMALL_FONT, 0, 5);
// setusercharsize(4,3,4,3);

// setpalette(Black,0);
// setpalette(Green,88);
// setpalette(MAGENTA,99);
// setpalette(BROWN,8);

	mode_text = MODE_GRAPHIC;
	mouse_installed();
// set_pointer_shape(ARROW);
	get16( init_pal, 0 );

/*
 restorecrtmode();
 fond_color = TEXT_FOND_COLOR;
 lat_char_n = 1;
 lung_char_n = 1;

 changechar(1);
 setregister(1);
 setmousetext();
*/

	tasks[VIRTUAL].delay_time = 50000;
	#ifdef NETWORK_COMM
	 make_task((taskptr) task_control, stack_NETWORK , stack_NETWORK_SIZE, NETWORK);  //-sizeof( int_regs )
	#endif
	#ifdef NET_BAC_COMM
	 make_task((taskptr) net_bac_task, stack_NET_BAC, stack_NETWORK_SIZE, NETWORK1 );  //-sizeof( int_regs )
	#endif
	 make_task((taskptr) proj, (char *)MK_FP(_SS, 0), stack_PROJ_SIZE , PROJ);
//	 make_task((taskptr) proj, stack_PROJ, stack_PROJ_SIZE , PROJ);
//	 make_task((taskptr) serial_init, stack_SERIAL, stack_SERIAL_SIZE, SERIAL);  //-sizeof( int_regs )
//	 make_task((taskptr) modem_init, stack_MODEM, stack_MODEM_SIZE, MODEM);  //-sizeof( int_regs )
	 make_task((taskptr) dial_init, stack_DIAL, stack_DIAL_SIZE, DIAL);  //-sizeof( int_regs )
	 make_task((taskptr) miscellaneous_init, stack_MISCELLANEOUS, stack_MISCELLANEOUS_SIZE, MISCELLANEOUS);  //-sizeof( int_regs )
	#ifndef WORKSTATION
	 make_task((taskptr) fnc_exec_virtual_code, stack_VIRTUAL, stack_VIRTUAL_SIZE, VIRTUAL); //-sizeof( int_regs )
	 make_task((taskptr) savemonitors, stack_MONITOR, stack_MONITOR_SIZE, AMONITOR); //-sizeof( int_regs )
 	 make_task((taskptr) alarmtask, stack_ALARMTASK, stack_ALARMTASK_SIZE, ALARMTASK); //-sizeof( int_regs )
	 make_task((taskptr) nettask, stack_NETTASK, stack_NETTASK_SIZE, NETTASK); //-sizeof( int_regs )
	#endif
//	 make_task((taskptr) MSTP_Master_node, stack_MSTP_Master_node, stack_MSTP_Master_node_SIZE, MSTP_MASTER);  //-sizeof( int_regs )
//	 make_task((taskptr) rs485_receive_frame, stack_rs485_receive_frame, stack_rs485_receive_frame_SIZE, RS485_RECEIVEFRAME);  //-sizeof( int_regs )
	make_task((taskptr) ServerTSM, stack_ServerTSM, stack_ServerTSM_SIZE, SERVERTSM);  //-sizeof( int_regs )

/*
	for( byte j=0;j<3;j++) statistic[j] = 0;
	 statistic_period = 2 * PROGRAM_INTERVAL / 55;
*/
	ftime(&tb);

	gettime(&ora_start);

	timesec1970=time(NULL);
	memcpy(&ora_current, localtime((const long *)&timesec1970), sizeof(struct tm) );

	ora_current_sec = (unsigned long)ora_start.ti_hour*3600L+(unsigned long)ora_start.ti_min*60L+(unsigned long)ora_start.ti_sec;
	milisec = (int)ora_start.ti_hund * 10;
	microsec = (int)ora_start.ti_hund * 10000;
	if( ora_current.year&0x03 )
		month_days[1]=28;
	else
		month_days[1]=29;

	#ifdef DEMO
	 simulate = 1;
	#endif
	multitask();

	if(mode_text)
	{
		restorechar(1);
		setregister(0);
		setgraphmode(getgraphmode());
	}
	closegraph();

//	 restorecrtmode();

	textbackground(Black);
	clrscr();
	textcolor(White);

	cprintf("                                 End Program\n\r                 ");
}
