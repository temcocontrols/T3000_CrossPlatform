#include <conio.h>
#include <dos.h>
#include <process.h>
#include <dir.h>
#include <sys\stat.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <graphics.h>
#include <windows.h>
#include "aio.h"
#include "baseclas.h"
#include "recstruc.h"
#include "mtkernel.h"
#include "gwin.h"
#include "gmbar.h"
#include "serial.h"
#include "net_bac.h"
#include "netb_bac.h"
#include "ipx.h"
#include "rs485.h"
#include "ptp.h"
#include "t3000hlp.h"

#define ESC 27
#define TOPPANELX 10
#define TOPPANELY 3
#define BOTPANELX 65
#define BOTPANELY 10

#define MAX_INPUT_BUFFER 2000

union key {
	int i;
	char ch[2];
	} ;
extern int nettask(void);
extern void memsize(void);
void desinstalled(void);
int install_port(int com=-1);
void clear_color(int lx, int length, int ly, int ry, char *lin_text, int bkgnd, int frgnd);
extern void setlocalpanel(int net=0);
extern char *ErrorName( RS232Error error );
//extern int netcall(BACnetPDU pdutype, int service, int network, int dest, char *data, int *length , int command, int arg, char compress=0);
extern int texttointerval( char *textbuffer,char *seconds , char *minutes , char *hours, char c=':' );
extern char * intervaltotext(char *textbuf, long seconds , unsigned minutes , unsigned hours, char *c=":");
extern void chbkg(int lx, int ly, int width, int bkgnd, int frgnd, int unchangecol=127, int height = 0);
extern int net_call(int command, int arg,  char *data, uint *length , int dest,
				 int network, int others=0, int timeout=TIMEOUT_NETCALL,
				 char *returnargs=NULL, int *length_returnargs=NULL,
				 char *sendargs=NULL, int length_sendargs=0, char bytearg=0, int port=-1);
extern void DisplayMessageT(int lx, int ly, int rx, int ry, char *title, char *message, GWindow **Er1, int fcolor=Black, GWindow *Er2=NULL, long delay=0);
extern void *DisplayMessage(int lx, int ly, int rx, int ry, char *title, char *message, GWindow **Er1, int fcolor=Black, GWindow *Er2=NULL, long delay=0);
extern void DeleteMessage(GWindow *p);
extern char *rtrim(char *text);
extern int check_access(int ptype, int num=-1, int mes=R_NA);
extern void scrollup(int topx, int topy, int endx, int endy, char attr);
extern void ftoa(float f, int length, int ndec, char *buf);
extern void getpassword(char *pass, char *text);
extern void blocked( int id );
extern void blocked_suspended( int id );
extern void blocked_resume( int id );
extern void getkey(void);
extern void disconnect_serial(int d=0);
extern void upcustomunit(Units_element	*punits);
extern int dialog_select(int n_entry, char *arraytext, int save, int x, int y, int bkgnd, int tbkgnd, char *title=NULL, char col=10);

extern int refresh_time;
extern char network_points_flag, sendinfoflag;
extern unsigned SilenceTimer;
extern fond_color;
#define MAX_RATES 11
extern char huge stack_PTP[stack_PTP_SIZE*RS232TASKS];
extern char huge stack_MSTP_Master_node[stack_MSTP_Master_node_SIZE*RS485TASKS];
extern char huge stack_NETTASK[stack_NETTASK_SIZE];
//extern char huge stack_rs485_receive_frame[stack_rs485_receive_frame_SIZE];

struct input_buffer {
		unsigned time;
		union {
			int   i;
			char  key[2];
			} key;
		};

extern struct input_buffer *input_buffer;//[MAX_INPUT_BUFFER];
extern int ind_input_buffer;

extern int ipxport, rs485port;
extern char ipxfinished;
extern int Version;
extern char default_prg[13];
extern int time_run_MSTP;
extern char validint;
extern int time_key;
extern char simulate;
extern int time_last_key;
extern int def_macro;
extern int disconnect_time;
extern char iamnewonnet, iwanttodisconnect;

typedef struct {
	RS232PortName port_name;
	irq_name irq_port;
	} Port_list;
extern Port_list port_list[20];
//extern Comm_Info comm_info[MAX_COMM_INFO];
extern Comm_Info *comm_info;
extern Board_info	boards[MAX_BOARDS];
extern Serial *ser_ptr;
extern byte serial_access;
extern char far com_buf[10][5];
extern char huge connection_type_text[9][14];
extern ModemCapabilities ModemDataBase[1];

extern Panel *ptr_panel;
extern GMenuBar G;
extern int  station_num;
extern int local_panel;
extern int mode_text;
extern int nr_boards,nnr_boards;
extern int  Station_NUM;
extern char Station_NAME[NAME_SIZE];
extern Station_point station_list[MAX_STATIONS];
extern char station_name[NAME_SIZE];
extern unsigned char tbl_bank[MAX_TBL_BANK];
extern char password[9];

extern char far NetworkName[NAME_SIZE];
extern unsigned long timestart;

extern char huge *trying_mess;
extern char huge *default_string;
extern char huge *list10[];
extern char huge *lin_text;
extern char huge *ctrlbreak_text;
extern char huge *autodetect;
extern char huge *ok_button;
extern char huge *cancel_button;
extern char huge *lin_menu;
extern char huge *lin_hor;
extern char huge *lin_ver;
extern char huge *na;
extern char huge *on;
extern char huge *off;
extern int dxscreen, dyscreen;
extern char text;
extern uint filetransfer;
extern long data_const, data_length_const;
extern char keyboard_data;
extern char _far tempbuf[65];
extern int mouse_inst;
extern xscreen, yscreen;
extern char control;
extern char blocked1;
extern char huge *version;
extern char int_disk1;
extern Panel_info1 Panel_Info1, panel_info1;
extern char DIAL_action, DIAL_checkconnection;
extern struct  time time_str;
extern struct  date date_dtr;
#ifdef NET_BAC_COMM
extern NetBios_Bac *pnet;
extern IPX         *pipx;
extern int NET_EXIT;
#endif
extern char IPX_enabled, tmp_IPX_enabled;
extern int ipxtempNetworkAddress;
int ReadYesNo(int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							int bkgndrreadcolor, int readcolor, char *text, char yes='Y', char no='N', char s=1);
void Border(int ltopx, int ltopy, int rbottomx, int rbottomy, int colour,int bcolour);
nldirectories(GWDialog *D, char *dir, char *nname, uint *nrfiles, uint *nrdirectories,
							int *upfiles, int *updir, union key *key, int local	);
void mouseint(void);
void save_config(int what);

void pfiles(GWDialog *D);
void pdirectories(GWDialog *D);
void pdrives(GWDialog *D)   ;
void pfup(GWDialog *D)      ;
void pfdn(GWDialog *D)      ;
void pfname(GWDialog *D);
void conportmini1(GWDialog *D);
void conportmini2(GWDialog *D);
void ratemini1(GWDialog *D);
void ratemini2(GWDialog *D);


extern char huge *portconfl1;
extern char huge *invalpanelnr;
extern char huge *sourcefile;
extern char huge *destfile;
extern char huge *local_text;
extern char huge *remote_text;
extern char huge *more_text;
extern char huge *autoac_text;
extern char huge *userac_text;
extern char huge *async_text;
extern char huge *estab_text;
extern char huge array_miniconf[][16];
extern char	read_inputs_rate;
extern char write_outputs_rate;

byte no_outs, no_ins;
//char huge files[500][13];
extern char huge (*files)[13];
int i_files;
extern char huge directories[50][13];
int i_directories;
char drives[10][3];
int i_drives;
char name[13];
int Blu;

extern char huge *pressanykey;
char (*b)[4];
char (*f)[7];
char (*s)[5];

//char ind_object_t, ind_object_d;
unsigned update_t3000exe=0xffff;
char updatenet;
extern char autodetect_state;
unsigned long rate[] = { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 57600, 115200 };
Comm_Info *pcomminfo;
MiniCommInfo *pcomminfomini;
char activate_tmp;

void adjust_readtime( Time_block *time_buf )  // mini->T3000
{
				Time_block_mini timemini;
				if( panel_info1.panel_type == MINI_T3000 )
				{
				 memcpy(&timemini, time_buf, sizeof(Time_block_mini) );
				 time_buf->ti_sec=timemini.ti_sec;         // 0-59
				 time_buf->ti_min=timemini.ti_min;         // 0-59
				 time_buf->ti_hour=timemini.ti_hour;           // 0-23
				 time_buf->dayofmonth=timemini.dayofmonth;   // 1-31
				 time_buf->month=timemini.month;          // 0-11
				 time_buf->year=timemini.year;           // year - 1900
				 time_buf->dayofweek=timemini.dayofweek;        // 0-6 ; 0=sunday
				 time_buf->dayofyear=timemini.dayofyear;    // 0-365 gmtime
				 time_buf->isdst=timemini.isdst;
				}
}

void adjust_writetime(Time_block *time_buf, Time_block_mini *timemini)
{
				if( panel_info1.panel_type == MINI_T3000 )
				{
				  timemini->ti_sec=time_buf->ti_sec;         // 0-59
				  timemini->ti_min=time_buf->ti_min;         // 0-59
				  timemini->ti_hour=time_buf->ti_hour;           // 0-23
				  timemini->dayofmonth=time_buf->dayofmonth;   // 1-31
				  timemini->month=time_buf->month;          // 0-11
				  timemini->year=time_buf->year;           // year - 1900
				  timemini->dayofweek=time_buf->dayofweek;        // 0-6 ; 0=sunday
				  timemini->dayofyear=time_buf->dayofyear;    // 0-365 gmtime
				  timemini->isdst=time_buf->isdst;
				}
}

// how: 0,4-simplu    1-button    2-umbra   3=simplu-1, 5 - button-dreapta interior
// bkgnd - window bkgnd, bcolour - culoarea din jur
void Bordergr(int ltopx, int ltopy, int rbottomx, int rbottomy, int colour, int bkgnd, int bcolour,int butcol, int how, int out)
{
 char buf[81];
 int up,down,left,right, lt, lb, rt, rb;
 buf[80]=0;
 bkgnd &= 0x07;
 lin_menu[rbottomx-ltopx+1]=0;
 for(int j=ltopy;j<=rbottomy;j++)
			mxyputs(ltopx,j,lin_menu,bkgnd,colour);
 lin_menu[rbottomx-ltopx+1]=lin_menu[0];

 if(text == ASCII_FONT)
 {
	out = 0;
	how = 0;
	lin_hor[rbottomx-ltopx+1]=0;
	mxyputs(ltopx,ltopy,lin_hor,bkgnd,colour);
	mxyputs(ltopx,rbottomy,lin_hor,bkgnd,colour);
	lin_hor[rbottomx-ltopx+1]=lin_hor[0];

	dxscreen--;
	dyscreen++;
	lin_ver[rbottomy-ltopy+1]=0;
	mxyputs(ltopx,ltopy,lin_ver,bkgnd,colour);
	mxyputs(rbottomx,ltopy,lin_ver,bkgnd,colour);
	lin_ver[rbottomy-ltopy+1]=lin_ver[0];
	dxscreen++;
	dyscreen--;

	if(rbottomy!=ltopy)
	{
	 lt = 'Ú';
	 lb = 'À';
	 rt = '¿';
	 rb = 'Ù';
	}
	else
	{
	 lt = lb = rt = rb = ' ';
	}
 }
 else
 {
 if(how==0 || how==4)
 {
	if(out)
	{
	 up = 6+200;
	 down = 4+200;
	 left = 2+200;
	 right = 0+200;
	}
	else
	{
	 up = 4+200;
	 down = 6+200;
	 left = 0+200;
	 right = 2+200;
	 lt = 13+200;
	 lb = 14+200;
	 rt = 16+200;
	 rb = 15+200;
	}
 }
 if(how==1 || how == 5)
 {
	if(out)
	{
	 up = 7+200;
	 down = 4+200;
	 left = 3+200;
	 right = 0+200;
	}
	else
	{
	 up = 5+200;
	 down = 6+200;
	 left = 3+200;
	 if(how==1)
		 right = 0+200;
	 else
		 right = 2+200;
	}
 }
 if(how==3)
 {
	if(out)
	{
	 up = 7+200;
	 down = 5+200;
	 left = 3+200;
	 right = 1+200;
	}
	else
	{
	 up = 5+200;
	 down = 7+200;
	 left = 1+200;
	 right = 3+200;
	 lt = 20+200;
	 lb = 21+200;
	 rt = 23+200;
	 rb = 22+200;
	}
 }

 memset(buf, up, 80);
 buf[rbottomx-ltopx+1]=0;
// mxyputs(ltopx,ltopy,buf,out?bcolour:bkgnd,how==1&&!out?butcol:colour);
 mxyputs(ltopx,out?ltopy-1:ltopy,buf,out?bcolour:bkgnd,(how==1||how==5)&&!out?butcol:colour);

 dxscreen--;
 dyscreen++;
 memset(buf, left, 80);
 buf[rbottomy-ltopy+1]=0;
// mxyputs(out?ltopx:(how==1?ltopx-1:ltopx),ltopy,buf,(out || how==1)?bcolour:bkgnd,colour);
 mxyputs(out?ltopx-1:(how==1?ltopx-1:ltopx),ltopy,buf,(out || how==1 || how==5)?bcolour:bkgnd,colour);
 memset(buf, right, 80);
 buf[rbottomy-ltopy+1]=0;
// mxyputs(out?rbottomx:(how==1?rbottomx+1:rbottomx),ltopy,buf,(out || how==1)?bcolour:bkgnd,colour);
 mxyputs(out?rbottomx+1:(how==1?rbottomx+1:rbottomx),ltopy,buf,(out || how==1)?bcolour:bkgnd,colour);
 dxscreen++;
 dyscreen--;

 memset(buf, down, 80);
 buf[rbottomx-ltopx-(how==5?1:-1)]=0;
// mxyputs(ltopx,rbottomy,buf,out?bcolour:bkgnd,colour);
 mxyputs(ltopx+(how==5?1:0),out?rbottomy+1:rbottomy,buf,out?bcolour:bkgnd,colour);
 }

 if(!out && (how==0 || how==3))
 {
	moutchar(ltopx,ltopy,lt,bkgnd,colour);
	moutchar(ltopx,rbottomy,lb,bkgnd,colour);
	moutchar(rbottomx,ltopy,rt,bkgnd,colour);
	moutchar(rbottomx,rbottomy,rb,bkgnd,colour);
 }
 if(out && how==4)
 {
	moutchar(ltopx,ltopy,' ',bcolour,colour);
	moutchar(ltopx,rbottomy,' ',bcolour,colour);
	moutchar(rbottomx,ltopy,' ',bcolour,colour);
	moutchar(rbottomx,rbottomy,' ',bcolour,colour);
 }
	return;
}

int ReadWindow(int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							 int bkgndreadcolor, int readcolor, char *text, char *buf, int width, char *sablon=NULL)
{
// set_semaphore_dos();
 GWDialog *D = new GWDialog(x1,y1,x2,y2,0,0);
// clear_semaphore_dos();
 D->exitCR = 1;
 D->GWSet(NULL,bkgnd,tcolor);
 D->GShowWindow(DIALOG);

 D->GWPuts(1,3, text, bkgnd, frgnd);
 D->GDDef_object(NULL, 3+strlen(text), 1, width, bkgndreadcolor ,readcolor, buf, bkgndreadcolor ,readcolor,sablon);

 while(!D->HandleEvent());

// set_semaphore_dos();
 if(D) delete D;
// clear_semaphore_dos();
}

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.022  ********
// ********       begin       ********
// ***********************************
int ReadWindow_help(int Flag_help,int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							 int bkgndreadcolor, int readcolor, char *text, char *buf, int width, char *sablon)
{
// set_semaphore_dos();
 GWDialog *D = new GWDialog(Flag_help,"need_help",x1,y1,x2,y2,0,0);
// clear_semaphore_dos();
 D->exitCR = 1;
 D->GWSet(NULL,bkgnd,tcolor);
 D->GShowWindow(DIALOG);

 D->GWPuts(1,3, text, bkgnd, frgnd);
 D->GDDef_object(NULL, 3+strlen(text), 1, width, bkgndreadcolor ,readcolor, buf, bkgndreadcolor ,readcolor,sablon);

 while(!D->HandleEvent());

// set_semaphore_dos();
 if(D) delete D;
// clear_semaphore_dos();
}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.022  ********
// ********        end        ********
// ***********************************

int ReadWindow2(int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							 int bkgndreadcolor, int readcolor, char *text1, char *text2,
							 char *buf1, char *buf2, int width)
{
 int i;
 GWDialog *D = new GWDialog(x1,y1,x2,y2,0,0);
 D->exitCR = 1;
 D->GWSet(NULL,bkgnd,tcolor);
 D->GShowWindow(DIALOG);

 D->GWPuts(1,2, text1, bkgnd, frgnd);
 D->GWPuts(2,2, text2, bkgnd, frgnd);
 D->GDDef_object(NULL, 2+strlen(text1), 1, width, bkgndreadcolor ,readcolor, buf1, bkgndreadcolor ,readcolor);
 D->GDDef_object(NULL, 2+strlen(text2), 2, width, bkgndreadcolor ,readcolor, buf2, bkgndreadcolor ,readcolor);
 while( !(i=D->HandleEvent()) );
 if(D) delete D;
 return i;
}



int ReadYesNoButton(int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
						  int bkgndrreadcolor, int readcolor, char *text, char *yes, char *no,
						  char okchar, char cancelchar, char xok, char xcancel)
{
				 int l1=strlen(yes)-1;
				 int l2=strlen(no)-1;
				 GWDialog *D;
				 if( !mode_text )
				 {
					x1 *= 8;
					x2 *= 8;
					y2 = y1*19 + (y2-y1)*12 + 20;
					y1 *= 19;
				 }
				 D = new GWDialog(x1,y1,x2,y2,NO_STACK,0,SMALL_FONT,5,1);
				 D->enter = 1;
				 D->GWSet(NULL,bkgnd,tcolor);
				 D->GShowWindow(DIALOG);

				 if( mode_text )
				 {
				  Bordergr(x1+6, y1+4, x1+6+l1, y1+4, Black, bkgndrreadcolor, Lightgray, Black, 0, 1);
				  Bordergr(x1+6+l1+4, y1+4, x1+6+l1+4+l2, y1+4, Black, bkgndrreadcolor, Lightgray, Black, 0, 1);
				 }
				 D->GWPuts(1,3, text, bkgnd, frgnd);

				 D->GDDef_object(NULL,5,mode_text?3:2,8,bkgndrreadcolor,Black,yes,bkgndrreadcolor,readcolor,NULL,0,okchar,xok);
				 D->GDDef_object(NULL,5+l1+4,mode_text?3:2,9,bkgndrreadcolor,Black,no,bkgndrreadcolor,readcolor,NULL,1,cancelchar,xcancel);
				 D->index_cur = 0;
				 while(!(D->HandleEvent()));
				 char ok=D->ok;
				 delete D;
				 if(ok) return 1;
				 else return 0;
}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.023  ********
// ********       begin       ********
// ***********************************
int ReadYesNoButton_help(int Flag_help,int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
						  int bkgndrreadcolor, int readcolor, char *text, char *yes, char *no,
						  char okchar, char cancelchar, char xok, char xcancel)
{
				 int l1=strlen(yes)-1;
				 int l2=strlen(no)-1;
				 GWDialog *D;
				 if( !mode_text )
				 {
					x1 *= 8;
					x2 *= 8;
					y2 = y1*19 + (y2-y1)*12 + 20;
					y1 *= 19;
				 }
				 D = new GWDialog(Flag_help,"need_help",x1,y1,x2,y2,NO_STACK,0,SMALL_FONT,5,1);
				 D->enter = 1;
				 D->GWSet(NULL,bkgnd,tcolor);
				 D->GShowWindow(DIALOG);

				 if( mode_text )
				 {
				  Bordergr(x1+6, y1+4, x1+6+l1, y1+4, Black, bkgndrreadcolor, Lightgray, Black, 0, 1);
				  Bordergr(x1+6+l1+4, y1+4, x1+6+l1+4+l2, y1+4, Black, bkgndrreadcolor, Lightgray, Black, 0, 1);
				 }
				 D->GWPuts(1,3, text, bkgnd, frgnd);

				 D->GDDef_object(NULL,5,mode_text?3:2,8,bkgndrreadcolor,Black,yes,bkgndrreadcolor,readcolor,NULL,0,okchar,xok);
				 D->GDDef_object(NULL,5+l1+4,mode_text?3:2,9,bkgndrreadcolor,Black,no,bkgndrreadcolor,readcolor,NULL,1,cancelchar,xcancel);
				 D->index_cur = 0;
				 while(!(D->HandleEvent()));
				 char ok=D->ok;
				 delete D;
				 if(ok) return 1;
				 else return 0;
}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.023  ********
// ********        end        ********
// ***********************************

int ReadYesNo(int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							int bkgndrreadcolor, int readcolor, char *text, char yes, char no, char s)
{
						 char buf1[2];
						 if(s)
						 {
							buf1[0]=yes;
						 }
						 else
						 {
							buf1[0]=no;
						 }
						 buf1[1]=0;

						 ReadWindow(x1,y1,x2,y2, bkgnd, tcolor, frgnd,
												bkgndrreadcolor, readcolor, text, buf1, 1);
						 strupr(buf1);
						 if(buf1[0]==yes)
							 return 1;
						 else
							 return 0;
}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.024  ********
// ********       begin       ********
// ***********************************
int ReadYesNo_help(int Flag_help,int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							int bkgndrreadcolor, int readcolor, char *text, char yes, char no, char s)
{
						 char buf1[2];
						 if(s)
						 {
							buf1[0]=yes;
						 }
						 else
						 {
							buf1[0]=no;
						 }
						 buf1[1]=0;

						 ReadWindow_help(Flag_help,x1,y1,x2,y2, bkgnd, tcolor, frgnd,
												bkgndrreadcolor, readcolor, text, buf1, 1);
						 strupr(buf1);
						 if(buf1[0]==yes)
							 return 1;
						 else
							 return 0;
}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.024  ********
// ********        end        ********
// ***********************************
void result_ser(RS232Error result, int rs485=0)
{
 int i=0;
	if( result != RS232_SUCCESS )
	{
//	 if(rs485)
	 {
//	  if(!ser_rs485->port) i=1;
	  if(result==RS232_ERROR)
		  result=RS232_TIMEOUT;
	 }
//	 if(!i)
//		 DisplayMessage(mode_text?20:200, mode_text?9:150, mode_text?60:500, mode_text?13:200, NULL, rs485?ser_rs485->Error_Name( result ):ser_ptr->Error_Name( result ), NULL, Blue, NULL, result==RS232_REJECT?2000:5000);
		 DisplayMessage(mode_text?20:200, mode_text?9:150, mode_text?60:500, mode_text?13:200, NULL, ErrorName( result ), NULL, Blue, NULL, result==RS232_REJECT?2000:2000);
	}
}

int getfiles(char *term, char (*files)[13], int nmax, int local)
{
 uint done;
 int i=0;
 struct ffblk block;
 if(local)
 {
	set_semaphore_dos();
	done=findfirst(term,&block,FA_ARCH);
	clear_semaphore_dos();
	while(!done && i < nmax)
	{
	 strcpy((char *)files,block.ff_name);
	 files++;
	 i++;
	 set_semaphore_dos();
	 done=findnext(&block);
	 clear_semaphore_dos();
	}
 }
 else
 {
	done = 13;
	if(net_call(50+100, 44, term, &done, station_num, networkaddress)!=SUCCESS) return 0;
	Delay(100);
	GWindow *D;
	DisplayMessage(19, 8, 59, 12, ctrlbreak_text," Reading directories...   ",&D);
	if(net_call(50, 40, (char *)files, 0, station_num, networkaddress, NETCALL_SIGN)!=SUCCESS)
	{
	 DeleteMessage(D);
	 return 0;
	}
	DeleteMessage(D);
	Delay(100);
	memcpy(&i, files, 2);
	if(i) memmove(files, ((char *)files)+2, i*13);
 }
 return i;
}

int getdirectories(char *ndir, char (*directories)[13], int nmax, int local)
{
 uint done;
 int i=0;
 struct ffblk block;
 if(local)
 {
	set_semaphore_dos();
	done=findfirst("*.*",&block,FA_DIREC);
	clear_semaphore_dos();
	while(!done && i<nmax)
	{
	 if (block.ff_attrib == 0x10)
		if ( (strlen(block.ff_name)==1 && block.ff_name[0]!='.') || (strlen(block.ff_name)>1	) )
		 {
			strcpy((char *)directories,block.ff_name);
			directories++;
			i++;
		 }
	 set_semaphore_dos();
	 done=findnext(&block);
	 clear_semaphore_dos();
	}
 }
 else
 {
	done = 65;
	if(net_call(50+100, 43, ndir, &done, station_num, networkaddress)!=SUCCESS) return 0;
	Delay(100);
	GWindow *D;
	DisplayMessage(19, 8, 59, 12, ctrlbreak_text," Reading directories...   ",&D);
	if(net_call(50, 41, (char *)directories, 0, station_num, networkaddress, NETCALL_SIGN)!=SUCCESS)
	{
	 DeleteMessage(D);
	 return 0;
	}
	DeleteMessage(D);
	Delay(100);
	memcpy(&i, directories, 2);
	if(i) memmove(directories, ((char *)directories)+2, i*13);
 }
 return i;
}

uint GetFile(char *title, char *defaultname, char *path, char *term, char *ptrpath, int hx, int hy, uint noread, int bkgnd, int frgnd, int local)
{
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.034  ********
// ********       begin       ********
// ***********************************
 GWDialog *D;
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.034  ********
// ********        end        ********
// ***********************************
 int Lightgra = bkgnd;
 int Blu = frgnd;
 uint nrfiles, nrdirectories;
 hot_box hotname={2+hx,3+hy,15+hx,3+hy};
 hot_box hotfile={3+hx,5+hy,15+hx,13+hy};
 hot_box hotdir={23+hx,5+hy,36+hx,9+hy};
 hot_box hotdrive={23+hx,13+hy,36+hx,13+hy};
 hot_box hotuf={17+hx,5+hy,17+hx,5+hy};
 hot_box hotdf={17+hx,13+hy,17+hx,13+hy};
 hot_box hotud={37+hx,5+hy,37+hx,5+hy};
 hot_box hotdd={37+hx,9+hy,37+hx,9+hy};
 char ocwd[65];
 char tmp[65];
 char drive[3];
 char dir[65];
 char nname[13];
 char ext[4];
// char fullname[75];

 int disk;
//  int done,i=0,colour;
 long l;
 int done,i=0,colour;
 int last_cur,firstrun,secondrun;
 int last_m=0;
 int upfiles=0, updir=0;
 struct ffblk block;

 struct nume{
				char  names[13];
			};
 struct nume *tab;


 char *file;
 char odir[65];
 int col;

 ocwd[0]=0;
 i_files=0;
 i_directories=0;
 i_drives=0;

 if(local)
 {
	set_semaphore_dos();
   disk=getdisk();
	getcwd(ocwd,64);
	strcpy(odir,ocwd);
	if(path)
	if(path[0])
	 {
		strcpy(ocwd, path);
		chdir(ocwd);
	 }
	clear_semaphore_dos();
 }
 else
	if(net_call(50, 42, ocwd, 0, station_num, networkaddress)!=SUCCESS) return 0;

 set_semaphore_dos();
 files = new char huge [500][13];
 clear_semaphore_dos();

 if(ocwd[strlen(ocwd)-1] != '\\')
		strcat(ocwd,"\\");

	set_semaphore_dos();
	fnsplit(ocwd,drive,dir,name,ext);

	if(local)
		setdisk(toupper(drive[0])-'A');
	clear_semaphore_dos();

	strcpy(dir,ocwd);
//	dir[strlen(dir)-1]=0;

//	strcpy(name,"*.");
//	strcat(name,term);

//	strcpy(name,term);
	if( strlen(defaultname) )
	{
	 strcpy(name,defaultname);
	}
	else
	{
		memcpy(name,lin_text,12);
		name[8] = 0;
  }
	strcpy(nname,"*.*");
//	getcwd(ncwd,50);
//	strcat(ncwd,"\\");
//	strcat(ncwd,name);

//	strcpy(fullname, ocwd);
//	strcat(fullname, name);

 memset(directories, 0, sizeof(directories));
 memset(files, 0, sizeof(files));
 Delay(200);
 nrfiles=getfiles(term, files, 500, local);
 Delay(200);
 nrdirectories=getdirectories(dir, directories, 50,local);
 if(!nrdirectories)
 {
  if(local)
  {
	 set_semaphore_dos();
	 chdir(odir);
	 clear_semaphore_dos();
  }
  set_semaphore_dos();
  delete files;
  clear_semaphore_dos();
  return 0;
 }
// ********  the old code  ********
// GWDialog *D=new GWDialog(hx,hy,hx+55,hy+16,NO_STACK,0);
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.025  ********
// ********       begin       ********
// ***********************************
 if (!strcmp(title,"Load panel "))
 {
	D=new GWDialog(100,"need help",hx,hy,hx+55,hy+16,NO_STACK,0);
 }
 else
 {
	if (!strcmp(title,"Save panel "))
	{
		D=new GWDialog(101,"need help",hx,hy,hx+55,hy+16,NO_STACK,0);
	}
	else
	{
		if (!strcmp(title,"Save file"))
		{
			D=new GWDialog(21,"need_help",hx,hy,hx+55,hy+16,NO_STACK,0);
		}
		else
		{
			if (!strcmp(title,"Load file"))
			{
				D=new GWDialog(21,"need_help",hx,hy,hx+55,hy+16,NO_STACK,0);
			}
			else
			{
				D=new GWDialog(hx,hy,hx+55,hy+16,NO_STACK,0);
			}
		}
	}
 }
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.025  ********
// ********        end        ********
// ***********************************
 D->GWSet(title,Lightgra,Blu);
 D->GShowWindow(DIALOG);

 D->GWPuts(1,2,"File Name :",Lightgra,Black);
 D->GWPuts(1,22,"Directories :",Lightgra,Black);
 D->GWPuts(10,22,"Drives :",Lightgra,Black);
// file=new char[60];

 D->GDPuts(2,2,name,12,Cyan,Black);
 D->GDPuts(2,22, dir,30,Lightgra,Black);
// col=getcolor();

 Border(hx+3,hy+4,hx+17,hy+14,Black,Lightgra);
 moutchar(hx+17, hy+5, '', Lightgra, Black );
 moutchar(hx+17, hy+13, '', Lightgra, Black );
 Border(hx+23,hy+4,hx+37,hy+10,Black,Lightgra);
// mtextcolor(Black);
// mtextbackground(Lightgra);
 moutchar(hx+37, hy+5, '', Lightgra, Black );
 moutchar(hx+37, hy+9, '', Lightgra, Black );
 Border(hx+23,hy+12,hx+37,hy+14,Black,Lightgra);
 D->GDPuts(12,23, drive,12,Cyan,Black);
 drives[i_drives][0]=drive[0];
 drives[i_drives][1]=drive[1];


 for(i=1;i<=5 && i<=nrdirectories;i++)
 {
		D->GDPuts(i+3,23,&directories[i_directories+i-1][0],12,Lightgra,Black);
 }

 for(i=1;i<=9 && i<=nrfiles;i++)
 {
		D->GDDef_object(pfiles,3,i+3,12,Lightgra,Black);
//		D->GDDef_object(NULL,3,i+3,12,Lightgra,Black,&files[i_files][0],Blu,White);
		D->GDPuts(i+3,3,&files[i_files+i-1][0],12,Lightgra,Black);
 }

 D->index_cur=0;
 MouseStatus stat;
	union key key;
key.i=0;
int cur=2;
D->select=1;
D->updown=0;
firstrun=1;
secondrun=0;
key.ch[0]='\t';
last_m=-1;

while (1)
{

 if (bioskey_new(1) || D->first)
 {
	if(!D->first)
	{
		key.i = bioskey_new(0);
// ********  the old code  ********
//		if (key.ch[0]==0)  key.ch[0]=key.ch[1];
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.026  ********
// ********       begin       ********
// ***********************************
		if (key.ch[0]==0)
		{
			key.ch[0]=key.ch[1];
			if (key.ch[0]==F1KEY)
			{
				if (!strcmp(title,"Load panel "))
				{
					T3000help(100);
				}
				else
				{
					if (!strcmp(title,"Save panel "))
					{
						T3000help(101);
					}
					else
					{
						if (!strcmp(title,"Save file"))
						{
							T3000help(21);
						}
						else
						{
							if (!strcmp(title,"Load file"))
							T3000help(21);
						}
					}
				}
			}
		}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.026  ********
// ********        end        ********
// ***********************************
	}
//	GGHideCur(Black);
	if (key.ch[0]==27)  //esc
	{
	 D->GReleaseWindow();
	 D->esc=1;
	 break;
	}

	if (key.ch[0]=='\t' )  //tab
	{
	 key.ch[0]=0;
	 if (!last_m)
		 chbkg(D->objects[D->index_cur]->box.top.x,D->objects[D->index_cur]->box.top.y, D->objects[D->index_cur]->width, D->objects[D->index_cur]->bkgnd, D->objects[D->index_cur]->frgnd);

	 if (D->index_obj)
		for(int i=0;i<D->index_obj;i++)
//			 mfarfree(D->handle_obj[i]);
				 {
					mfarfree(D->objects[i]);
					D->objects[i]=NULL;
				 }

	D->index_obj=0;
	D->nrobj=D->last_mouse=D->esc=0;
	D->select=1;
	D->updown=0;
	D->first = 1;

	 cur++;
	 if(secondrun)
	 {
		secondrun=0;
		cur = 5;
	 }
	 if (cur==5) cur=1;
	 if (cur==1)
	 {
			D->index_cur=0;
			D->select=0;
			D->GDDef_object(pfname,2,2,12,Cyan,Black);
			D->GDPuts(2,2,name,12,Cyan,Black);
			D->index_cur=0;
	 }
	 if (cur==2)
	 {
//		 i_files=0;
		 if (nrfiles)
		 {
		 D->index_cur=0;
		 for(i=upfiles+1;i<=upfiles+9 && i<=nrfiles;i++)
			 {
				D->GDDef_object(pfiles,3,i-upfiles+3,12,Lightgra,Black);
//				D->GDDef_object(NULL,3,i-upfiles+3,12,Lightgra,Black,&files[i_files][0],Blu,White);
				D->GDPuts(i-upfiles+3,3,&files[i-1][0],12,Lightgra,Black);
			 }
		 D->index_cur=i_files-upfiles+1;
		 i_files++;
		 if ( D->index_cur >= nrfiles )
				 {
					D->index_cur--;
					i_files--;
				 }
		 }
		 else
		 {
			cur=3;
/*			D->index_cur=0;
			D->select=0;
			D->GDDef_object(pfname,2,2,12,Cyan,Black);
//			D->GDPuts(2,2,name,12,Cyan,Black);
			D->index_cur=0;
*/		 }

		}
	 if (cur==3)
		{
		 if (!last_m)
			 upfiles = i_files-D->index_cur;
//		 i_directories=0;
		 D->index_cur=0;
		 for(i=updir+1;i<=updir+5 && i<=nrdirectories;i++)
		 {
				D->GDDef_object(pdirectories,23,i-updir+3,12,Lightgra,Black);
				D->GDPuts(i-updir+3,23,&directories[i-1][0],12,Lightgra,Black);
		 }
		 D->index_cur=i_directories-updir+1;
		 i_directories++;
		 if ( D->index_cur >= nrdirectories )
						{
						 D->index_cur--;
						 i_directories--;
						}
		}
	 if (cur==4)
		{
		 if (!last_m)
				updir=i_directories-D->index_cur;
			D->index_cur=0;
			D->select=0;
			D->GDDef_object(pdrives,23,12,12,Cyan,Black);
			D->GDPuts(12,23,&drives[i_drives][0],12,Cyan,Black);
			D->index_cur=0;
		}
	 if(firstrun)
	 {
		firstrun=0;
		secondrun=1;
		last_m=-1;
		D->first = 1;
		key.ch[0] = '\t';
		continue;
	 }
	 last_m=0;
	 }

	if ( key.ch[0]==80 || key.ch[0]==72 || D->first )  //tab
	{
	 if (D->last_mouse == 0 )
			 chbkg(D->objects[D->index_cur]->box.top.x,D->objects[D->index_cur]->box.top.y, D->objects[D->index_cur]->width, D->objects[D->index_cur]->bkgnd, D->objects[D->index_cur]->frgnd);
	 if( !D->last_mouse )
	 if (D->updown )
		 {
			D->index_cur++;
			if (cur==2)
				i_files++;
			if (cur==3)
				i_directories++;
		 }
	 else
	 {
		 D->index_cur--;
			if (cur==2)
				i_files--;
			if (cur==3)
				i_directories--;
		}
	 D->first = 0;
	 D->last_mouse=0;
	 if (D->index_cur>=D->index_obj)
		 {
			D->index_cur--;
			if (cur==2)
			 if(i_files<nrfiles)
				for(i=1;i<=9 && i<nrfiles;i++)
					D->GDPuts(i+3,3,&files[i_files-(9-i)][0],12,Lightgra,Black);
			 else
				i_files--;
			if (cur==3)
			 if(i_directories<nrdirectories)
				for(i=1;i<=5 && i<nrdirectories;i++)
					D->GDPuts(i+3,23,&directories[i_directories-(5-i)][0],12,Lightgra,Black);
			 else
				i_directories--;
		 }

	 if (D->index_cur<0)
		 {
			D->index_cur++;
			if (cur==2)
			 if(i_files>=0)
				for(i=1;i<=9 && i<nrfiles;i++)
					D->GDPuts(i+3,3,&files[i_files+i-1][0],12,Lightgra,Black);
			 else
				i_files++;
			if (cur==3)
			 if(i_directories>=0)
				for(i=1;i<=5 && i<nrdirectories;i++)
					D->GDPuts(i+3,23,&directories[i_directories+i-1][0],12,Lightgra,Black);
			 else
				i_directories++;
		 }
	 if(cur==2)
	 {
     l=-1;
	  if( local )
	  {
		set_semaphore_dos();
		int hh;
		if( (hh=open(&files[i_files][0],O_RDONLY))!=NULL )
		{
		 l = filelength(hh);
		 close(hh);
		}
		clear_semaphore_dos();
	  }
	  else
	  {
      l=0;
/*
		strcpy(tmp, dir);
		strcat(tmp, &files[i_files][0]);
		Delay(300);
		if(net_call(50+100, 45, tmp, 65, station_num)==SUCCESS)
		{
		 Delay(300);
		 net_call(50, 46, (char *)&l, 4, station_num);
		}
*/
	  }
	  char bb[11];
	  ltoa(l, bb, 10);
	  l=strlen(bb);
	  D->GDPuts(14,40,bb,l,Lightgra,Black);
	  D->GDPuts(14,40+l," bytes ",8,Lightgra,Black);
	 }
	 else
	  D->GDPuts(14,40,"             " ,13,Lightgra,Black);

//	 D->objects[index_cur]->D->f(this);
	 if ( D->objects[D->index_cur])
//			 GDGets(D->objects[D->index_cur]->ptr, D->objects[D->index_cur]->yrel, D->objects[D->index_cur]->xrel, D->objects[D->index_cur]->width,D->objects[D->index_cur]->sbkgnd,D->objects[D->index_cur]->sfrgnd);
		 D->objects[D->index_cur]->f(D);
	 else
				 D->last='\t';
	 if ( D->last=='\t')
		 {
			key.ch[0]='\t';
			D->first = 1;
		 }
	 if (D->last == 80)
		 {
			D->updown=1;
			D->first = 1;
		 }
	 if ( D->last == 72) {D->updown=0;D->first = 1;}   //up
	 if (D->last == 0) D->last_mouse = 1;
	 if (D->last == 27) D->esc = 1;
	 if (D->last==13)
			 {
				if (cur==1)
				 {
					if(strchr(name, '*') || name[0]==' ' )
					{
//						strcpy(fullname, ocwd);
//						strcat(fullname, name);
						for(i=upfiles+1;i<=upfiles+9 && i<=nrfiles;i++)
						{
						 D->GDPuts(i-upfiles+3,3,&files[i-1][0],12,Lightgra,Lightgra);
						}
				i_files = upfiles = 0;
						nrfiles=getfiles(name[0]==' '?term:name, files, 500, local);
						key.ch[0]='\t';
						D->first = 1;
					}
					else
					{
					 D->GReleaseWindow();
					 break;
					}
				 }
				if (cur==2)
				 {
					 strcpy(name,files[i_files]);
					 D->GReleaseWindow();
					 break;
				 }
				if (cur==3)
					{
						 nldirectories(D, dir, name[0]==' '?term:name, &nrfiles, &nrdirectories,
													 &upfiles, &updir, &key, local);

					}
			 }
	 }
 }
 if(mouse_inside(D->close_spot.top.x,
		 D->close_spot.top.y,
		 D->close_spot.bot.x,
		 D->close_spot.bot.y) || D->esc )
		{
			mouse_status(stat);
			if(stat.leftButton || D->esc || D->last_mouse)
			 {
			 D->esc = 1;
			 D->GReleaseWindow();
			 break;
			 }
		}


// i=0;
 for(int i=0;i<D->index_obj;i++)
 {
 if(mouse_inside(D->objects[i]->box.top.x,
		 D->objects[i]->box.top.y,
		 D->objects[i]->box.bot.x,
		 D->objects[i]->box.bot.y))
		{
			mouse_status(stat);
			if(stat.leftButton || D->last_mouse)
			 {
			 D->first = 1;
			 D->last_mouse=1;
			 last_cur=D->index_cur;
			 D->index_cur = i;
			 chbkg(D->objects[last_cur]->box.top.x,D->objects[last_cur]->box.top.y, D->objects[last_cur]->width, D->objects[last_cur]->bkgnd, D->objects[D->index_cur]->frgnd);
			 if(cur==2)
				 i_files += i-last_cur;
			 if(cur==3)
				 {
					i_directories += i-last_cur;
					for(long j=0;j<100000;j++);
					mouse_status(stat);
					if(stat.leftButton)
						{
						 nldirectories(D, dir, name[0]==' '?term:name, &nrfiles, &nrdirectories,
													 &upfiles, &updir, &key, local);

////////////

////////////////////
	 D->first = 0;
	 D->last_mouse=0;
						}

				 }

			 break;
			 }
		}
 }

 if ( i < D->index_obj)  continue;



if(mouse_inside(hotuf.top.x,
		 hotuf.top.y,
		 hotuf.bot.x,
		 hotuf.bot.y) && cur==2)
		 {
			mouse_status(stat);
			if(stat.leftButton || D->last_mouse)
			 {
				 D->updown=0;D->first = 1;					//up
				 D->last_mouse=0;
			 }
		}

if(mouse_inside(hotud.top.x,
		 hotud.top.y,
		 hotud.bot.x,
		 hotud.bot.y) && cur==3)
		 {
			mouse_status(stat);
			if(stat.leftButton || D->last_mouse)
			 {
				 D->updown=0;D->first = 1;					//up
				 D->last_mouse=0;
			 }
		}
if(mouse_inside(hotdd.top.x,
		 hotdd.top.y,
		 hotdd.bot.x,
		 hotdd.bot.y) && cur==3)
		{
			mouse_status(stat);
			if(stat.leftButton || D->last_mouse)
			 {
				 D->updown=1;D->first = 1;					//up
				 D->last_mouse=0;
			 }
		}

if(mouse_inside(hotdf.top.x,
		 hotdf.top.y,
		 hotdf.bot.x,
		 hotdf.bot.y) && cur==2)
		{
			mouse_status(stat);
			if(stat.leftButton || D->last_mouse)
			 {
				 D->updown=1;D->first = 1;					//up
				 D->last_mouse=0;
			 }
		}



 if(mouse_inside(hotname.top.x,
		 hotname.top.y,
		 hotname.bot.x,
		 hotname.bot.y) )
		{
			mouse_status(stat);
			if(stat.leftButton || D->last_mouse)
			 {
				if (cur==2)
					 upfiles = i_files - D->index_cur;
				if (cur==3)
					 updir = i_directories - D->index_cur;
				D->last_mouse=0;
				key.ch[0]='\t';
				cur=4;
				chbkg(D->objects[D->index_cur]->box.top.x,D->objects[D->index_cur]->box.top.y, D->objects[D->index_cur]->width, D->objects[D->index_cur]->bkgnd, D->objects[D->index_cur]->frgnd);
				last_m=1;
				D->first = 1;
			 }
		}
 if(mouse_inside(hotfile.top.x,
		 hotfile.top.y,
		 hotfile.bot.x,
		 hotfile.bot.y) )
		{
			mouse_status(stat);
			if(stat.leftButton || D->last_mouse)
			 {
				if (cur==3)
					 updir = i_directories - D->index_cur;
				D->last_mouse=0;
				key.ch[0]='\t';
				cur=1;
				if (nrfiles)
				chbkg(D->objects[D->index_cur]->box.top.x,D->objects[D->index_cur]->box.top.y, D->objects[D->index_cur]->width, D->objects[D->index_cur]->bkgnd, D->objects[D->index_cur]->frgnd);
				last_m=1;
				D->first = 1;
			 }
		}
 if(mouse_inside(hotdir.top.x,
		 hotdir.top.y,
		 hotdir.bot.x,
		 hotdir.bot.y) )
		{
			mouse_status(stat);
			if(stat.leftButton || D->last_mouse)
			 {
				if (cur==2)
					 upfiles = i_files - D->index_cur;
				D->last_mouse=0;
				key.ch[0]='\t';
				cur=2;
				if (nrdirectories)
				chbkg(D->objects[D->index_cur]->box.top.x,D->objects[D->index_cur]->box.top.y, D->objects[D->index_cur]->width, D->objects[D->index_cur]->bkgnd, D->objects[D->index_cur]->frgnd);
				last_m=1;
				D->first = 1;
			 }
		}
 if(mouse_inside(hotdrive.top.x,
		 hotdrive.top.y,
		 hotdrive.bot.x,
		 hotdrive.bot.y) )
		{
			mouse_status(stat);
			if(stat.leftButton || D->last_mouse)
			 {
				if (cur==2)
					 upfiles = i_files - D->index_cur;
				if (cur==3)
					 updir = i_directories - D->index_cur;
				D->last_mouse=0;
				key.ch[0]='\t';
				cur=3;
				chbkg(D->objects[D->index_cur]->box.top.x,D->objects[D->index_cur]->box.top.y, D->objects[D->index_cur]->width, D->objects[D->index_cur]->bkgnd, D->objects[D->index_cur]->frgnd);
				last_m=1;
				D->first = 1;
			 }
		}

// if (i==index_obj) first=1;
}

					 set_semaphore_dos();
//					 disk=getdisk();
					 if(local)
						getcwd(dir,64);
//					 drive[0]=disk+'A';
//					 drive[1]=':';
//					 drive[2]=0;
//					 strcpy(ptrpath,drive);
					 i = D->esc;
					 if(strlen(rtrim(name)))
					 {
						strcpy(ptrpath,dir);
						if(ptrpath[strlen(ptrpath)-1] != '\\')
							strcat(ptrpath,"\\");
						term = strchr(term,'.');
						if(!strchr(term,'*'))
						{
						 char *p;
						 if( (p = strchr(name,'.')) ) *p = 0;
						 if(strlen(name) > 8) name[8] = 0;
						 strcat(name, term);
						}
						strcat(ptrpath,name);
					 }
					 else
						i=1;
					 if(local)
					 {
						setdisk(disk);
						chdir(odir);
					 }
					 clear_semaphore_dos();
					 delete D;
					 delete files;
					 if(i)
						 return 0;
					 else
						 return 1;
/*
		D->GDDef_object(pfup,18,5,1,MAGENTA,Black);
		D->GDPuts(5,18,"u",1,MAGENTA,White);

		D->GDDef_object(pfdn,18,15,1,MAGENTA,Black);
		D->GDPuts(15,18,"d",1,MAGENTA,White);

*/
};


void pfiles(GWDialog *D)
{
 D->GDGets(&files[i_files][0],(D->index_cur)+4,3,12,Blu,White);
}
void pdirectories(GWDialog *D)
{
 D->GDGets(&directories[i_directories][0],(D->index_cur)+4,23,12,Blu,White);
}
void pdrives(GWDialog *D)
{
 D->GDGets(&drives[i_drives][0],(D->index_cur)+12,23,2,Blu,White);
}
void pfname(GWDialog *D)
{
 D->GDGets(name,2,2,12,Blu,White);
}


void Border(int ltopx, int ltopy, int rbottomx, int rbottomy, int colour,int bcolour)
{
 int bcol = bcolour;
 bcolour &= 0x07;
 lin_menu[rbottomx-ltopx+1]=0;
 for(int j=ltopy;j<=rbottomy;j++)
			mxyputs(ltopx,j,lin_menu,bcolour,bcol);
 lin_menu[rbottomx-ltopx+1]=lin_menu[0];


 lin_hor[rbottomx-ltopx+1]=0;
 mxyputs(ltopx,ltopy,lin_hor,bcolour,colour);
 mxyputs(ltopx,rbottomy,lin_hor,bcolour,colour);
 lin_hor[rbottomx-ltopx+1]='Ä';

 dxscreen--;
 dyscreen++;
 lin_ver[rbottomy-ltopy+1]=0;
 mxyputs(ltopx,ltopy,lin_ver,bcolour,colour);
 mxyputs(rbottomx,ltopy,lin_ver,bcolour,colour);
 lin_ver[rbottomy-ltopy+1]='³';
 dxscreen++;
 dyscreen--;

//	mtextcolor(Black);
	moutchar(ltopx,ltopy,'Ú',bcolour,colour);
	moutchar(ltopx,rbottomy,'À',bcolour,colour);
	moutchar(rbottomx,ltopy,'¿',bcolour,colour);
	moutchar(rbottomx,rbottomy,'Ù',bcolour,colour);
	return;
}

nldirectories(GWDialog *D, char *dir, char *nname, uint *nrfiles, uint *nrdirectories,
							int *upfiles, int *updir, union key *key, int local	)
{
	int Lightgra = Lightblue;
	int done;
	struct ffblk block;
	if(local)
	{
	 dir[0]=0;
	 set_semaphore_dos();
	 setdisk(toupper(drives[0][0])-'A');
	 chdir(directories[i_directories]);
	 getcwd(dir, 64);
	 clear_semaphore_dos();
	 strcat(dir,"\\");
	}
	else
	{
	 if(!strcmp((char *)&directories[i_directories], ".."))
	 {
		dir[strlen(dir)-1]=0;
		char *p=strrchr(dir, '\\');
		if(p) *(p+1)=0;
	 }
	 else
	 {
		strcat(dir,(char *)&directories[i_directories]);
		strcat(dir,"\\");
	 }
	}
//	getcurdir(0, dir);
	D->GDPuts(2,22,dir ,30,Lightgra,Black);

	 for(int i=1;i<=9 && i<=*nrfiles;i++)
	 {
		D->GDPuts(i+3,3,&files[i_files+i-1][0],12,Lightgra,Lightgra);
	 }

	 key->ch[0]=0;
	 chbkg(D->objects[D->index_cur]->box.top.x,D->objects[D->index_cur]->box.top.y, D->objects[D->index_cur]->width, D->objects[D->index_cur]->bkgnd, D->objects[D->index_cur]->frgnd);

	 if (D->index_obj)
		for(int i=0;i<D->index_obj;i++)
//			 mfarfree(D->handle_obj[i]);
				 {
					mfarfree(D->objects[i]);
					D->objects[i]=NULL;
				 }

	 for(i=1;i<=5 && i<=*nrdirectories;i++)
			 {
				D->GDPuts(i+3,23,&directories[i_directories+i-1][0],12,Lightgra,Lightgra);
			 }

	*nrdirectories=getdirectories(dir, directories, 50,local);

	*nrfiles=getfiles(nname, files, 500, local);

 i_files=0;
 *upfiles=0;
 for(i=1;i<=9 && i<=*nrfiles;i++)
	 {
		D->GDPuts(i+3,3,&files[i_files+i-1][0],12,Lightgra,Black);
	 }


	D->index_cur=-1;
	D->index_obj=0;
	D->nrobj=D->last_mouse=D->esc=0;
	D->select=1;
	D->updown=0;
	D->first = 1;

		 *updir=0;
		 i_directories=0;
		 for(i=1;i<=5 && i<=*nrdirectories;i++)
			 {
				D->GDDef_object(pdirectories,23,i+3,12,Lightgra,Black);
				D->GDPuts(i+3,23,&directories[i_directories+i-1][0],12,Lightgra,Black);
			 }
 D->index_cur=0;
}


int sendfile(char *source, char *dest, int panel, int mes=1)
{
	RS232Error result;
	int n;
	char err=0;
	char buf1[65];
	uint rate=1920;
	unsigned long tstart;
	GWindow *D;
	FILE *h;
	buf1[0]=0;

	filetransfer=0;
	set_semaphore_dos();
	int_disk1++;
	if( (h=fopen(source,"rb+"))!=NULL )
	{
	 int_disk1--;
	 char *ptr=new char [MAX_FILE_TRANSFER_BUF];
	 clear_semaphore_dos();
	 unsigned long t;
	 DisplayMessage(mode_text?15:200, mode_text?7:150, mode_text?64:500, mode_text?11:200, ctrlbreak_text, " File length         bytes. Sent    ", &D);
	 n=65;
	 result=net_call(50+100, 35, dest, (uint *)&n, panel, networkaddress);
	 set_semaphore_dos();
	 disconnect_time = -1;
	 if(result == RS232_SUCCESS)
	 {
		int_disk1++;
		fseek(h, 0, SEEK_END);
		data_length_const = ftell(h);
		fseek(h, 0, SEEK_SET);
		int_disk1--;
		ltoa(data_length_const, ptr, 10);
		D->GWPuts(1,19,ptr,Lightblue,Black);
/*
		if(serial_access)
		{
			rate = ser_ptr->ReadBaudRate()/10;
		}
		else
		{
			rate = ser_rs485->ReadBaudRate()/10;
		}
*/
		if(mode_text)
		{
			mxyputs(25,8,"Transfer to panel ",Lightblue,Black);
			itoa(panel,buf1,10);
			mxyputs(43,8,buf1,Lightblue,Black);
			mxyputs(17,10,"Estimated time ",Lightblue,Black);
			intervaltotext(buf1, data_length_const/MAX_FILE_TRANSFER_BUF+data_length_const/rate, 0 , 0);
			mxyputs(32,10,buf1,Lightblue,Black);
			mxyputs(40,10," Elapsed time ",Lightblue,Black);
		}
		Delay(500);
		data_const=0;
		tstart = timestart;
		while( data_const <= data_length_const)
		{
			int_disk1++;
			n=fread(ptr+2, 1, Version>=213?(MAX_FILE_TRANSFER_BUF-2):6000, h);
			int_disk1--;
			clear_semaphore_dos();
			if( data_const == data_length_const ) n=0;
			memcpy(ptr, &n, 2);
			intervaltotext(buf1, timestart-tstart, 0 , 0);
			if(mode_text)
				mxyputs(54,10,buf1,Lightblue,Black);
//			Delay(2100);
			t=timestart;
			while(!filetransfer && timestart < t+40 && result!=USER_ABORT)
			{
			 rate = 1;
			 result=net_call(50, 37, (char *)&filetransfer, &rate, panel, networkaddress);
			 if( result!=RS232_SUCCESS && result!=USER_ABORT) Delay(5000);
			 Delay(400);
			}
			if(!filetransfer){err=1; break;}
			rate = n+2;
			if( (result=net_call(50+100, 36, ptr, &rate, panel, networkaddress, NETCALL_SIGN, 30))!=SUCCESS )
			{
				if(result==USER_ABORT) {err=1;break;}
				Delay(2000);
				rate = n + 2;
				if(net_call(50+100, 36, ptr, &rate, panel, networkaddress, NETCALL_SIGN, 30)!=SUCCESS)
				 {err=1;break;}
			}
			data_const += n?n:1;
			filetransfer=0;
			set_semaphore_dos();
		}
	 }
	 int_disk1++;
	 fclose(h);
	 int_disk1--;
	 delete ptr;
	 clear_semaphore_dos();
	 disconnect_time = DISCONNECT_TIME;
	 DeleteMessage(D);
	 if(mes)
	 {
		 if(err)
			DisplayMessage(20, 7, 60, 11, NULL, " Error transfer file! ", NULL, Blue, NULL, -1);
		 else
			DisplayMessage(22, 7, 58, 11, NULL, " File sent. O.K. ", NULL, Blue, NULL, -1);
	 }
	}
	else
	{
	 int_disk1--;
		clear_semaphore_dos();
	}
	filetransfer=0;
	return err;
}

void updatet3000(int panel)
{
 int n;
 char buf1[13];
		  if(updatenet) return;
		  updatenet = 1;
		  strcpy(buf1, "T3000.EXE");
		  n = 0;
		  if(!panel)
		  {
			update_t3000exe = 0;
			update_t3000exe |= (1<<(Station_NUM-1));
		  }
			for(int i=0; i<MAX_STATIONS; i++)
			{
			if( (!panel && i+1!=Station_NUM) || (panel && i+1==panel) )
			 if(station_list[i].state)
			 {
				while(n++ < 3)
			  {
				if( !sendfile(buf1, buf1, i+1, 0) )
				{
				 update_t3000exe |= (1<<i);
				 break;
				}
				Delay(30000);
				Delay(30000);
			  }
			 }
		  }
		  updatenet = 0;
}

void filetransfer_routine(void)
{
	GPopUp *popup;
	set_semaphore_dos();
	popup = new GPopUp(1,6,(char **)&list10,0,5);
	clear_semaphore_dos();
	int man,n;
	uint j;
	man = popup->GReturn();
	G.pGPopUpTable[0].ReleasePopUp(-1);
	set_semaphore_dos();
	delete popup;
	clear_semaphore_dos();
	if(man!=4)
		if(local_panel) return;
	char err=0,ptr[30];
	char buf1[65],buf2[151];
	uint rate=1920;
	unsigned long tstart;
	GWindow *D;
	FILE *h;
	buf1[0]=0;buf2[0]=0;
	if(man==1)
	{
	 strcpy(ptr,local_text);
	 strcat(ptr,sourcefile);
	 if(!GetFile(ptr,NULL,NULL,"*.*",buf1,TOPPANELX+3,TOPPANELY+3,1,Lightblue,Blue, 1)) return;
	 strcpy(ptr,remote_text);
	 strcat(ptr,destfile);
	 if(!GetFile(ptr,NULL,NULL,"*.*",buf2,TOPPANELX+3,TOPPANELY+3,1,Lightblue,Blue, local_panel)) return;
	 sendfile(buf1, buf2, station_num);
	}
	if(man==0)
	{
	 strcpy(ptr,remote_text);
	 strcat(ptr,sourcefile);
	 if(!GetFile(ptr,NULL,NULL,"*.*",buf1,TOPPANELX+3,TOPPANELY+3,1,Lightblue,Blue, local_panel)) return;
	 strcpy(ptr,local_text);
	 strcat(ptr,destfile);
	 if(!GetFile(ptr,NULL,NULL,"*.*",buf2,TOPPANELX+3,TOPPANELY+3,1,Lightblue,Blue, 1)) return;
	 long length;
	 filetransfer=0;
	 Delay(100);
	 n = 65;
	 if(net_call(50+100, 39, buf1, (uint *)&n, station_num, networkaddress)==SUCCESS)
	 {
		Delay(5000);
		n = 4;
		if(net_call(50, 38, (char *)&length, (uint *)&n, station_num, networkaddress)==SUCCESS)
		{
		 if(length)
		 {
			set_semaphore_dos();
			if( (h=fopen(buf2,"wb+"))!=NULL )
			{
			 char *ptr=new char [MAX_FILE_TRANSFER_BUF];
			 clear_semaphore_dos();
			 unsigned long t;
			 DisplayMessage(mode_text?15:200, mode_text?7:150, mode_text?64:500, mode_text?11:200, ctrlbreak_text, " File length         bytes. Read    ", &D);
			 data_length_const = length;
			 ltoa(data_length_const, ptr, 10);
			 D->GWPuts(1,19,ptr,Lightblue,Black);
/*
			 if(serial_access)
			 {
				rate = ser_ptr->ReadBaudRate()/10;
			 }
			 else
			 {
				rate = ser_rs485->ReadBaudRate()/10;
			 }
*/
			 if(mode_text)
			 {
				mxyputs(17,10,"Estimated time ",Lightblue,Black);
				intervaltotext(buf1, data_length_const/MAX_FILE_TRANSFER_BUF+data_length_const/rate, 0 , 0);
				mxyputs(32,10,buf1,Lightblue,Black);
				mxyputs(40,10," Elapsed time ",Lightblue,Black);
			 }
			 RS232Error result = RS232_SUCCESS;
			 data_const=0;
			 disconnect_time = -1;
			 tstart = timestart;
			 while( data_const < data_length_const)
			 {
				intervaltotext(buf1, timestart-tstart, 0 , 0);
				if(mode_text)
					mxyputs(54,10,buf1,Lightblue,Black);
//				Delay(2100);
				t=timestart;
				while(!filetransfer && timestart < t+40 && result!=USER_ABORT)
				{
				 rate=1;
				 result=net_call(50, 37, (char *)&filetransfer, &rate, station_num, networkaddress);
				 if( result!=RS232_SUCCESS && result!=USER_ABORT) Delay(5000);
				 Delay(400);
				}
				if(!filetransfer) {err=1;break;}
//				Delay(100);
				rate = n+2;
				if( (result=net_call(50, 36, ptr, &rate, station_num, networkaddress, NETCALL_SIGN, 30))!=SUCCESS)
				{
					if(result==USER_ABORT) {err=1;break;}
					Delay(2000);
				  rate = n+2;
				  if(net_call(50, 36, ptr, &rate, station_num, networkaddress, 30)!=SUCCESS)
				  {err=1;break;}
				}
				memcpy(&n, ptr, 2);
				if(!n) {break;}
				set_semaphore_dos();
				fwrite(ptr+2, 1, n, h);
				clear_semaphore_dos();
				data_const += n;
				filetransfer=0;
			 }
			 set_semaphore_dos();
			 fclose(h);
			 delete ptr;
			 clear_semaphore_dos();
			 DeleteMessage(D);
			 disconnect_time = DISCONNECT_TIME;
			 filetransfer=0;
			 if(err)
				DisplayMessage(20, 7, 60, 11, NULL, " Error transfer file! ", NULL, Blue, NULL, -1);
			 else
				DisplayMessage(22, 7, 58, 11, NULL, " File transfered. O.K. ", NULL, Blue, NULL, -1);
			}
			else
			 clear_semaphore_dos();
		 }
		}
	 }
	}
	data_const=0;
	if(man==2 || man==3)
		if(GetFile(man==2?"Delete file":"Rename file",NULL,NULL,"*.*",buf1,TOPPANELX+3,TOPPANELY+3,1,Lightblue,Blue, local_panel))
		{
		  if(man==3)
		  {
							char *q;
							strcpy(buf2, "  Rename file ");
							strcat(buf2, strupr(buf1));
							strcat(buf2, " as : ");
							q=&buf2[strlen(buf2)];
							memset(q,0,65);
							ReadWindow(13, 9, 77, 13, Lightgray, Darkgray, Black,
							 Cyan, White, buf2, q, 12);
							if(strlen(q))
							{
//							 rename(buf1, buf2);
							 memcpy(buf2,q,65);
							 memcpy(&buf2[65],buf1,65);
							 n = 130;
							 net_call(50+100, 48, buf2, (uint *)&n, station_num, networkaddress);
							}
		  }
		  if(man==2)
		  {
							strcpy(buf2, " Delete file ");
							strcat(buf2, strupr(buf1));
							strcat(buf2, " ? (Y/N): ");
							if(ReadYesNo(15, 9, 75, 13, Lightgray, Darkgray, Black,
													Cyan, White, buf2))
							{
							 n=65;
							 net_call(50+100, 47, buf1, (uint *)&n, station_num, networkaddress);
							}
		  }
		}
	if(man==4)
	{
		int t=-1;
		if(ReadYesNo(15, 9, 65, 13, Lightgray, Darkgray, Black,
						 Cyan, White, "update One panel/All panels? (O/A): ", 'O', 'A') )
		{
		  buf1[0]=0;
		  ReadWindow(27,9,50,13, Lightgray,  Darkgray,  Black,
										 Cyan, White, "Panel number: ", buf1, 2);
		  rate = atoi(buf1);
			if( rate>0 && rate<MAX_STATIONS ) t=rate;
		}
		else
		{
			t=0;
		}
		if(t!=-1)
		{
		 if(ReadYesNo(15, 9, 65, 13, Lightgray, Darkgray, Black,
						 Cyan, White, "Start updating T3000.EXE on network? (Y/N): "))
		 {
			if(!local_panel && serial_access)
		  {
			int i = 3;
			t++;
			while(i--)
			{
			 n = 2;
			 if( net_call(50+100,76,(char *)&t,(uint *)&n,station_num, networkaddress)==SUCCESS ) break;
			 Delay(15000);
			}
		  }
		  else
		  {
			updatet3000(t);
		  }
		 }
		}
	}
}

/*
void ptime(GWDialog *D)
{
 struct  time t;
 D->GDGetsablon(timebuf,D->objects[ind_object_t]->yrel, D->objects[ind_object_t]->xrel,8,Blu,White,"NN:NN:NN");
 texttointerval( timebuf, &t.ti_sec , &t.ti_min , &t.ti_hour );
 t.ti_hund=0;
 if(t.ti_sec || t.ti_min || t.ti_hour)
 {
	 settime(&t);
	 i_files = 1;
 }
}
*/
/*
void pdate(GWDialog *D)
{
 struct date d;
 D->GDGetsablon(datebuf,D->objects[ind_object_d]->yrel, D->objects[ind_object_d]->xrel,8,Blu,White,"NN-NN-NN");
 d.da_year = 0;
 texttointerval( datebuf, (char *)&d.da_year , &d.da_day , &d.da_mon, '-' );
 if(d.da_year)
 {
	d.da_year += 1900;
	setdate(&d);
	i_files = 1;
 }
}
*/

void pio(GWDialog *D)
{
 union key key;
 MouseStatus stat;
 int i,j;
 char c[2]={" "};
 i=D->index_cur/8;
 j=D->index_cur%8;
 while(1)
 {
	if(bioskey_new(1))
	{
	 key.i = bioskey_new(0);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.027  ********
// ********       begin       ********
// ***********************************
	 if ((key.ch[0]==0)&&(key.ch[1]==F1KEY))
	 {
		T3000help(301);
	 }
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.027  ********
// ********        end        ********
// ***********************************
	 if (key.ch[0]==ESC){ D->last=ESC;break;}
	 if (key.ch[1]==LEFT){ D->last=UP;break;}
	 if (key.ch[1]==RIGHT){ D->last=DOWN;break;}
	 if(key.ch[0]==13)
	 {
		 keyboard_data=1;
		 if( boards[i].in_mask & 1<<j )
		 {
			boards[i].in_mask &= ~(1<<j);
			boards[i].out_mask |= 1<<j;
			c[0]='O';
//			boards[i].no_outs += 16;
//			boards[i].no_ins -= 16;
			no_outs += 16;
			no_ins -= 16;
		 }
		 else
			if( boards[i].out_mask & 1<<j )
			{
			 boards[i].out_mask &= ~(1<<j);
//			 boards[i].no_outs -= 16;
			 no_outs -= 16;
			 c[0]=' ';
			}
			else
			{
			 boards[i].in_mask |= 1<<j;
//			 boards[i].no_ins += 16;
			 no_ins += 16;
			 c[0]='I';
			}
		 D->GWPuts(2+i,15+j*2,c,Black,White);
	 }
	}
	else
	{
	 mouse_status(stat);
	 if(stat.leftButton )
	 {
		D->last_mouse=1;
		break;
	 }
	}
 }
}

void pnboards(GWDialog *D)
{
 char cnrboards[2];
 itoa(nnr_boards, cnrboards, 10);
 D->GDGets(cnrboards,1,22,1,Blue,White);
// nnr_boards=atoi(cnrboards);   //FOR THE MOMENT nr_boards=1
 D->GWPuts(1,22,itoa(nr_boards,cnrboards,10),Blue,White);
 for(int i=5;i<D->index_obj;i++)
 {
	if( D->objects[i] )
	{
		mfarfree(D->objects[i]);
		D->objects[i]=NULL;
	}
 }
 D->index_obj = 5;
 D->GWPuts(7,23,"BOARD-1  BOARD-2  BOARD-3  BOARD-4",Lightgray,Black);

 lin_menu[34]=0;
 D->GWPuts(8,23,lin_menu,Lightgray,Black);
 D->GWPuts(9,23,lin_menu,Lightgray,Black);
 D->GWPuts(10,23,lin_menu,Lightgray,Black);
 lin_menu[34]=lin_menu[0];

 for(i=0;i<nnr_boards; i++)
 {
	char p[8]={"BOARD-1"};
	p[6]='0'+i+1;
	D->GWPuts(7,23+i*9,p,Lightgray,White);
 }

 for(i=0;i<nnr_boards; i++)
 {
	D->GDDef_object(NULL,26+i*9,8,3,Cyan,Black,(char *)(b+i),Blue,White);
	D->GDDef_object(NULL,23+i*9,9,6,Cyan,Black,(char *)(f+i),Blue,White);
	D->GDDef_object(NULL,25+i*9,10,4,Cyan,Black,(char *)(s+i),Blue,White);
 }
 D->index_cur = 0;


 if(ptr_panel->card_type>=VER1_CARD)
 {
	GWDialog *D1 = new GWDialog(21,10,60,18,NO_STACK,0);
	D1->GWSet("I/O Board Configuration",Lightgray,Darkgray);
	D1->GShowWindow(DIALOG);

	D1->GWPuts(2,5,"BOARD 1 : ",Lightgray,Black);
	D1->GWPuts(3,5,"BOARD 2 : ",Lightgray,Black);
	D1->GWPuts(4,5,"BOARD 3 : ",Lightgray,Black);
	D1->GWPuts(5,5,"BOARD 4 : ",Lightgray,Black);

	D1->GWPuts(1,15,"1 2 3 4 5 6 7 8",Lightgray,Black);
	char p[8]={"BOARD 1"};
	for(i=0;i<nr_boards; i++)
	{
	p[6]='0'+i+1;
	D1->GWPuts(2+i,5,p,Lightgray,White);
	}

  char c[2]={" "};
  for(i=0;i<nr_boards; i++)
  {
	boards[i].no_ins = 0;
	boards[i].no_outs = 0;
	for(int j=0;j<8;j++)
	{
	 c[0]=' ';
	 if( boards[i].in_mask & 1<<j )
	 {
		c[0]='I';
		boards[i].no_ins += 16;
	 }
	 if( boards[i].out_mask & 1<<j )
	 {
		c[0]='O';
		boards[i].no_outs += 16;
	 }
	 D1->GWPuts(2+i,15+j*2,c,Cyan,Black);
	 D1->GDDef_object(pio,15+j*2,2+i,1,Cyan,Black,NULL,Blue,White);
	}
	}
  while(!D1->HandleEvent());
  if(D1) delete D1;
 }
}

void pcomsetup(GWDialog *D)
{
}

void miniconfig(void)
{
 char timebuf[9];
 char datebuf[9];
 char cnrboards[2],cnrpanel[4],cNetworkAddress[6];
 uint i;
 int  err=0;
 if( panel_info1.panel_type == MINI_T3000 )
 {
//	miniconfig();
	char stationname[NAME_SIZE];
	char networkname[NAME_SIZE];
	struct  time t;
	struct  date d;
	Time_block time_buf;
	RS232Error result;
	PanelId panelid;
	int ii;
	ii=dialog_select( 2, (char *)array_miniconf, 0, 32, 7, Lightgray, Darkgray, "Mini config",15);  // 0=don't save
	if(ii>=0)
	{
	 if (ii==0)
	 {
			stationname[0] = 0;
			if(net_call(TIME_COMMAND, 0, (char *)&time_buf, 0, station_num, networkaddress,NETCALL_RETRY)==SUCCESS)
			{
// ********  the old code  ********
//			 GWDialog *D = new GWDialog(5,6,75,17,NO_STACK,0);
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.028  ********
// ********       begin       ********
// ***********************************
			 GWDialog *D = new GWDialog(301,"need_help",5,6,75,17,NO_STACK,0);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.028  ********
// ********        end        ********
// ***********************************
			 D->GWSet("Minipanel Configuration",Lightgray,Darkgray);
			 D->GShowWindow(DIALOG);

			 D->GWPuts(1,2,"Panel number   : ",Lightgray,Black);
			 D->GWPuts(2,2,"Panel name     : ",Lightgray,Black);
			 D->GWPuts(3,2,"Network number : ",Lightgray,Black);
			 Bordergr(11, 12, 27, 12, Black, Cyan, Lightgray, Black, 0, 1);
			 D->GWPuts(5,5,"   COMM Settings",Cyan,Black);

			 D->GWPuts(1,36,"Current time is     : ",Lightgray,Black);
			 D->GWPuts(2,36,"New Time ( hh:mm:ss): ",Lightgray,Black);
			 D->GWPuts(3,36,"Current date is     : ",Lightgray,Black);
			 D->GWPuts(4,36,"New Date ( mm-dd-yy): ",Lightgray,Black);

//			D->GWPuts(7,20,"I/O Cards Configuration",Lightgray,Black);
//			D->GWPuts(8,17,"Analog Port 1      Analog Port 2",Lightgray,Black);

			 ultoa((unsigned long)((unsigned)station_num), cnrpanel, 10);
			 ultoa((unsigned long)((unsigned)networkaddress), cNetworkAddress, 10);
//			memcpy( stationname, station_list[station_num-1].name, NAME_SIZE);
			 memcpy( stationname, panel_info1.panel_name, NAME_SIZE);
			 stationname[16]=0;
			 memcpy( networkname, panel_info1.network_name, NAME_SIZE);
			 networkname[16]=0;
//			if(net_call(TIME_COMMAND, 0, (char *)&time_buf, 0, station_num, networkaddress)==SUCCESS)
			 {
			 adjust_readtime(&time_buf);
			 t.ti_sec  = time_buf.ti_sec;
			 t.ti_min  = time_buf.ti_min;
			 t.ti_hour = time_buf.ti_hour;
			 d.da_year  = time_buf.year+1900;
			 d.da_mon = time_buf.month+1;
			 d.da_day = time_buf.dayofmonth;
			 }
//			 else
//			 {
//					 gettime(&t);
//					 getdate(&d);
//			 }
			 strcpy(timebuf, intervaltotext( NULL, (long)t.ti_sec , t.ti_min , t.ti_hour));
			 D->GDPuts(1,58, timebuf, 8 ,Lightgray,Black);
			 strcpy(datebuf, intervaltotext( NULL, (long)d.da_year%100 , d.da_day , d.da_mon, "-"));
			 D->GDPuts(3,58, datebuf, 8 ,Lightgray,Black);

/*
			gettime(&t);
			strcpy(timebuf, intervaltotext( NULL, (long)t.ti_sec , t.ti_min , t.ti_hour));
			D->GDPuts(1,58, timebuf, 8 ,Lightgray,Black);
			getdate(&d);
			strcpy(datebuf, intervaltotext( NULL, (long)d.da_year%100 , d.da_day , d.da_mon, "-"));
			D->GDPuts(3,58, datebuf, 8 ,Lightgray,Black);
*/
			 memset( timebuf, '0', 8);
			 memset( datebuf, '0', 8);
			 timebuf[2] = timebuf[5] = ':';
			 datebuf[2] = datebuf[5] = '-';
			 timebuf[8] = 0;
			 datebuf[8] = 0;
			 D->GDPuts(2,58, timebuf , 8 ,Cyan,Black);
			 D->GDPuts(4,58, datebuf , 8 ,Cyan,Black);

//			ind_object_t=4; ind_object_d=5;
			 D->GDDef_object(NULL,19,1,3,Cyan,Black,cnrpanel,Blue,White);
			 D->GDDef_object(NULL,19,2,16,Cyan,Black,stationname,Blue,White);
			 D->GDDef_object(NULL,19,3,5,Cyan,Black,cNetworkAddress,Blue,White);
			 D->GDDef_object(pcomsetup,8,5,13,Cyan,Black);
//			D->GDDef_object(ptime,58,2,8,Cyan,Black);
//			D->GDDef_object(pdate,58,4,8,Cyan,Black);
			 D->GDDef_object(NULL,58,2,8,Cyan,Black,timebuf, Black, White, "NN:NN:NN");
			 D->GDDef_object(NULL,58,4,8,Cyan,Black,datebuf, Black, White, "NN-NN-NN");

//			i_files = 0;     // flag for time or date changing
			 D->enter=1;
			 keyboard_data=0;
			 D->index_cur = 0;
			 while(!D->HandleEvent());
			 if(D) delete D;

			 if(keyboard_data)
			 if(check_access(12) == R_READ_WRITE)
			 {
// ********  the old code  ********
//				if(ReadYesNo(20, 7, 64, 11, Lightgray, Darkgray, White,
//								Cyan, Black, "Save new configuration? (Y/N): "))
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.029  ********
// ********       begin       ********
// ***********************************
				if(ReadYesNo_help(301,20, 7, 64, 11, Lightgray, Darkgray, White,
								Cyan, Black, "Save new configuration? (Y/N): "))
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.029  ********
// ********        end        ********
// ***********************************
				{
				if( panel_info1.panel_type == MINI_T3000 )
				{
				 Time_block_mini timemini;
//				 if(i_files)
				 {
/*
					gettime(&t);
					getdate(&d);
					time_buf.ti_sec=t.ti_sec;
					time_buf.ti_min=t.ti_min;
					time_buf.ti_hour=t.ti_hour;
					time_buf.dayofmonth=d.da_day;
					time_buf.month=d.da_mon-1;
					time_buf.year=d.da_year-1900;
*/
					texttointerval( timebuf, &t.ti_sec , &t.ti_min , &t.ti_hour );
					t.ti_hund=0;
					d.da_year = 0;
					texttointerval( datebuf, (char *)&d.da_year , &d.da_day , &d.da_mon, '-' );
					i=0;
					if(t.ti_sec || t.ti_min || t.ti_hour)
					{
					 time_buf.ti_sec=t.ti_sec;
					 time_buf.ti_min=t.ti_min;
					 time_buf.ti_hour=t.ti_hour;
					 i=1;
					}
					if(d.da_year)
					{
					 time_buf.dayofmonth=d.da_day;
					 time_buf.month=d.da_mon-1;
					 time_buf.year=d.da_year;
					 i=1;
					}
					if(i)
					{
					 time_buf.isdst = -1;
					 if (mktime((struct tm *)&time_buf) == -1)
						time_buf.dayofweek = 7;
					 adjust_writetime(&time_buf, &timemini);
					 i = sizeof(Time_block_mini);
					 result = net_call(TIME_COMMAND+100, 0, (char *)&timemini, &i, station_num, networkaddress,NETCALL_RETRY);
					}
				 }
				 if( station_num!=atoi(cnrpanel) || networkaddress!=atoi(cNetworkAddress) ||
						strcmp( stationname, panel_info1.panel_name) ||
							 strcmp( networkname, panel_info1.network_name) )
				 {
					if( atoi(cnrpanel) >= 1 && atoi(cnrpanel) <= MAX_STATIONS )
					{
					 int k1;
					 k1 = atoi(cnrpanel);
					 for(int j1=0;j1<MAX_STATIONS;j1++)
						if( (j1+1)!=panel_info1.panel_number && (panel_info1.active_panels&(1L<<j1)) && k1==j1+1 )
						{
							 DisplayMessage(10, 7, 70, 11, pressanykey, "Panel number already on network. Panel number unchanged!", NULL, Black, NULL, 60000);
							 err = 1;
							 break;
						}
					 if( !err )
					 {
						if(ReadYesNo(5, 9, 75, 13, Lightgray, Darkgray, Black, Cyan, White, "The PRG will be erased. Do you want to save it now? (Y/N): "))
						{
							if( ptr_panel->file(1)!=SUCCESS)
							{
							 return;
							}
						}
						panel_info1.panel_number = atoi(cnrpanel);
						panel_info1.network = atoi(cNetworkAddress);
						memcpy( panel_info1.panel_name, stationname, NAME_SIZE);
						memcpy( panel_info1.network_name, networkname, NAME_SIZE);
						i = sizeof(Panel_info1);
						if( (result=net_call(COMMAND_50+100, PANEL_INFO1_COMMAND, (char*)&panel_info1, &i, station_num, networkaddress,NETCALL_RETRY))==SUCCESS)
						{
						 disconnect_serial(1);
						 panel_info1 = Panel_Info1;
						 memcpy( tbl_bank, ptr_panel->table_bank, sizeof(tbl_bank));
						 memcpy( default_prg, ptr_panel->Default_Program, 13);
						 upcustomunit(ptr_panel->units);
						 station_num=Panel_Info1.panel_number;
						 networkaddress=Panel_Info1.network;
						 DisplayMessage(18, 7, 62, 11, NULL, " The panel will update it's configuration.     It will reboot in about 30 seconds.  ",NULL, Black, NULL, 30000);
						 DisplayMessage(20, 7, 60, 11, NULL, " You have to reconnect...! ",NULL, Black, NULL, 2000);
						}
						else
						{
						 panel_info1.panel_number = station_num;
						 panel_info1.network = networkaddress;
						}
					 }
					}
					else
						DisplayMessage(10, 7, 70, 11, pressanykey, invalpanelnr, NULL, Black, NULL, 60000);
				 }
				}
				}
			 }
			 else
				DisplayMessage(mode_text?18:150, mode_text?7:150, mode_text?62:510, mode_text?11:210, NULL, " Unsaved changes. Unauthorized access! ", NULL, Black, NULL, 1500);
			}
	 }
	 if (ii==1)
	 {
		 Panel_info2 panel_info2;
		 MiniCommInfo minicomminfo[2];
		 result = net_call(COMMAND_50, MINICOMMINFO_COMMAND, (char*)&minicomminfo, 0, station_num, networkaddress);
		 if( result == RS232_SUCCESS )
		 {
			pcomminfomini=minicomminfo;
			GWDialog *D = new GWDialog(mode_text?20:120,mode_text?7:80,mode_text?65:568,mode_text?17:350,NO_STACK,0,SMALL_FONT,5,1);
			D->GWSet("Ports Setting",Lightgray,Darkgray);
			D->GShowWindow(DIALOG);

			D->GWPuts(1,2,"Connection     PORT    Rate    Program No",Lightgray,Black);

			hide_pointer();
			if(mode_text)
			{
				Bordergr(40, 15, 47, 15, Black, Cyan, Lightgray, Black, 0, 1);
				Bordergr(29, 15, 37, 15, Black, Cyan, Lightgray, Black, 0, 1);
			}
			display_pointer();
			D->enter=1;
			char brate[8], p1[3],p2[3];
			for(i=0;i<2;i++)
			{
			 D->GWPuts(3+i, 2, connection_type_text[minicomminfo[i].media_type], Cyan, Black);
			 D->GWPuts(3+i, 17, com_buf[i+1], Cyan, Black);
			 ltoa( minicomminfo[i].baud_rate, brate, 10);
			 D->GWPuts( 3+i,24, 6, brate, Cyan, Black);
			 ltoa( minicomminfo[i].prg_number, brate, 10);
			 D->GWPuts( 3+i, 36, 2, brate, Cyan, Black);
			}
			itoa(minicomminfo[0].prg_number,p1,10);
			itoa(minicomminfo[1].prg_number,p2,10);
			D->GDDef_object(conportmini1,2,3,13,Cyan,Black);
			D->GDDef_object(conportmini2,2,4,13,Cyan,Black);
			D->GDDef_object(ratemini1,24,3,6,Cyan,Black);
			D->GDDef_object(ratemini2,24,4,6,Cyan,Black);
			D->GDDef_object(NULL,36,3,2,Cyan,Black,p1,Blue,White);
			D->GDDef_object(NULL,36,4,2,Cyan,Black,p2,Blue,White);
			D->GDDef_object(NULL,8,mode_text?7:5,8,Cyan,Black,ok_button,Cyan,White,NULL,0,'O',3);
			D->GDDef_object(NULL,19,mode_text?7:5,8,Cyan,Black,cancel_button,Cyan,White,NULL,1,'C',1);
			D->index_cur=0;

			keyboard_data=0;
			while(!D->HandleEvent());
			char ok=D->ok;
			if(D) delete D;

			if( ok && check_access(12)==R_READ_WRITE )
			{
			 if(ReadYesNo(20, 7, 64, 11, Lightgray, Darkgray, White,
													Cyan, Black, "Set new configuration? (Y/N): "))
			 {
				ii=0;
				for(i=0;i<2;i++)
				{
				 if( minicomminfo[i].media_type==SERIAL_LINK || minicomminfo[i].media_type==RS485_LINK ) ii=1;
				}
				if(ii)
				{
				 minicomminfo[0].prg_number=atoi(p1);
				 minicomminfo[1].prg_number=atoi(p2);
				 i=2*sizeof(MiniCommInfo);
				 if( (result = net_call(COMMAND_50+100, MINICOMMINFO_COMMAND, (char*)&minicomminfo, &i, station_num, networkaddress))==SUCCESS)
				 {
					disconnect_serial(1);
					panel_info1 = Panel_Info1;
					memcpy( tbl_bank, ptr_panel->table_bank, sizeof(tbl_bank));
					memcpy( default_prg, ptr_panel->Default_Program, 13);
					upcustomunit(ptr_panel->units);
					station_num=Panel_Info1.panel_number;
					networkaddress=Panel_Info1.network;
					DisplayMessage(12, 7, 68, 11, NULL, " Wait for panel to set the new configuration.               It will take about 30 seconds.",NULL, Black, NULL, 30000);
				 }
				}
				else
				{
					DisplayMessage(2, 7, 78, 11, NULL, " At least one port should be set up as serial or network connection!",NULL, Black, NULL, 5000);
				}
			 }
			}
		 }
	 }
	}
 }
}

void boardconfig(void)
{
 char cnrboards[2],cnrpanel[4],cNetworkAddress[6];
 char inr[5], outr[5];
 int i, err=0;
 set_semaphore_dos();
 b=new char [4][4];
 f=new char [4][7];
 s=new char [4][5];
 clear_semaphore_dos();


 if( panel_info1.panel_type == T3000 )
 {
// ********  the old code  ********
//	GWDialog *D = new GWDialog(12,6,70,17,NO_STACK,0);
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.030  ********
// ********       begin       ********
// ***********************************
	GWDialog *D = new GWDialog(301,"need_help",12,6,70,20,NO_STACK,0);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.030  ********
// ********        end        ********
// ***********************************
	D->enter = 2;
	D->GWSet("T3000 Panel Configuration",Lightgray,Darkgray);
	D->GShowWindow(DIALOG);

	D->GWPuts(1,1,"Number of PC boards: ",Lightgray,Black);
	D->GWPuts(1,25,"Panel number  : ",Lightgray,Black);
	D->GWPuts(2,25,"Panel name    : ",Lightgray,Black);
//  D->GWPuts(3,25,"Network number: ",Lightgray,Black);
	D->GWPuts(4,1,"Read inputs rate   : ",Lightgray,Black);
	D->GWPuts(5,1,"Write outputs rate : ",Lightgray,Black);

	D->GWPuts(9,1,"Base address [hexa] : ",Lightgray,Black);
	D->GWPuts(10,1,"Quartz frequence    : ",Lightgray,Black);
	D->GWPuts(11,1,"Watchdog interval   : ",Lightgray,Black);
	D->GWPuts(8,1,"Board status        : ",Lightgray,Black);

	D->GWPuts(7,23,"BOARD-1  BOARD-2  BOARD-3  BOARD-4",Lightgray,Black);
	for(i=0;i<nr_boards; i++)
	{
	 char p[8]={"BOARD-1"};
	 p[6]='0'+i+1;
	 D->GWPuts(7,23+i*9,p,Lightgray,White);
	 if(control && blocked1<8)
		D->GWPuts(8,26+i*9,on,Lightgray,Black);
	 else
		D->GWPuts(8,26+i*9,off,Lightgray,Black);
	}

	itoa(read_inputs_rate, inr, 10);
	itoa(write_outputs_rate, outr, 10);

	itoa(Station_NUM, cnrpanel, 10);
	itoa(NetworkAddress, cNetworkAddress, 10);
	nnr_boards=nr_boards;

	for(i=0;i<nr_boards; i++)
	{
	 if(!boards[i].base_adr)
	 {
//		 boards[i].base_adr = 100+i*8-(i/2>=1?6:0);
		 boards[i].base_adr = 256;
		 boards[i].quartz_freq = 7372;
		 boards[i].watchdog_interval = 250;
	 }
	 itoa(boards[i].base_adr, b[i], 16);
	 ftoa((float)boards[i].quartz_freq/1000., 6, 3, f[i]);
	 itoa(boards[i].watchdog_interval, s[i], 10);
	}

// D->GDDef_object(NULL,20,1,1,Cyan,Black,cnrboards,Blue,White);
	D->GDDef_object(pnboards,22,1,1,Cyan,Black);
	D->GDDef_object(NULL,41,1,3,Cyan,Black,cnrpanel,Blue,White);
	D->GDDef_object(NULL,41,2,16,Cyan,Black,Station_NAME,Blue,White);
//	D->GDDef_object(NULL,41,3,5,Cyan,Black,cNetworkAddress,Blue,White);

	D->GDDef_object(NULL,23,4,2,Cyan,Black,inr,Blue,White);
	D->GDDef_object(NULL,23,5,2,Cyan,Black,outr,Blue,White);

	for(i=0;i<nr_boards; i++)
	{
	 D->GDDef_object(NULL,26+i*9,8,3,Cyan,Black,(char *)(b+i),Blue,White);
	 D->GDDef_object(NULL,23+i*9,9,6,Cyan,Black,(char *)(f+i),Blue,White);
	 D->GDDef_object(NULL,25+i*9,10,4,Cyan,Black,(char *)(s+i),Blue,White);
	}


	keyboard_data=0;
	no_outs = boards[0].no_outs;
	no_ins  = boards[0].no_ins;
	D->index_cur = 0;
	while(!D->HandleEvent());
// set_semaphore_dos();
	if(D) delete D;
// clear_semaphore_dos();

	if(keyboard_data)
	if(check_access(12) == R_READ_WRITE)
	{
// ********  the old code  *********
//	if(ReadYesNo(20, 7, 64, 11, Lightgray, Darkgray, White,
//													Cyan, Black, "Save new configuration? (Y/N): "))
// *********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.031  ********
// ********       begin       ********
// ***********************************
	if(ReadYesNo_help(301,20, 7, 64, 11, Lightgray, Darkgray, White,
													Cyan, Black, "Save new configuration? (Y/N): "))
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.031  ********
// ********        end        ********
// ***********************************
	{
	 if( atoi(cnrpanel) >= 1 && atoi(cnrpanel) <= MAX_STATIONS )
	 {
	 if(local_panel && Station_NUM == station_num)
	 {
		unsigned long activepanels;
		int k;
		k = atoi(cnrpanel);
		for(i=0; i<MAX_Routing_table ; i++)
		{
		 if( (Routing_table[i].status&RS485_ACTIVE)==RS485_ACTIVE || (Routing_table[i].status&IPX_ACTIVE)==IPX_ACTIVE )
		 {
			activepanels = ((class ConnectionData *)Routing_table[i].ptr)->panel_info1.active_panels;
			for(int j=0;j<MAX_STATIONS;j++)
			 if( (j+1)!=Station_NUM && (activepanels&(1L<<j)) && k==j+1 )
			 {
				 DisplayMessage(10, 7, 70, 11, pressanykey, "Panel number already on network. Panel number unchanged!", NULL, Black, NULL, 60000);
				 err = 1;
				 break;
			 }
		 }
		}
		if( !err )
		{
		 desinstalled();

		 station_list[Station_NUM-1].state=0;
		 Panel_Info1.active_panels &= ~(1l<<(Station_NUM-1));
		 memset(station_list[Station_NUM-1].name, ' ', sizeof(Station_NAME)-1);
		 nr_boards=nnr_boards;
		 station_num=atoi(cnrpanel);
		 strcpy(station_list[station_num-1].name,Station_NAME);
		 strcpy(station_name, Station_NAME);
		 if(ptr_panel)
		 {
			ptr_panel->GlPanel=station_num;
//		 ptr_panel->GlNetwork=atoi(cNetworkAddress);
		 }
		 Station_NUM=atoi(cnrpanel);
//		NetworkAddress=atoi(cNetworkAddress);
		 station_list[Station_NUM-1].state=1;

		 Panel_Info1.panel_number = Station_NUM;
//		Panel_Info1.network      = NetworkAddress;
		 Panel_Info1.active_panels  |= (1l<<(Station_NUM-1));
//		memcpy(Panel_Info1.network_name, NetworkName, sizeof(Panel_Info1.network_name));
		 memcpy(Panel_Info1.panel_name, Station_NAME, sizeof(Panel_Info1.panel_name));
//	  strcpy(Station_NAME, station_list[Station_NUM-1].name);

		 for(i=0;i<nr_boards; i++)
		 {
			int j=atoi(b[i]);
			boards[i].base_adr = j/100*256+(j/10)%10*16+(j%10)%10;
			boards[i].quartz_freq=7371;          //atof(f[i])*1000;
			boards[i].watchdog_interval=atoi(s[i]);
		 }
		 boards[0].no_outs=no_outs;
		 boards[0].no_ins =no_ins;
		 save_config( CNF_BOARD_INFO );
		 TS = Station_NUM;

		 read_inputs_rate = atoi(inr);
		 write_outputs_rate = atoi(outr);

// update info in comm_info
//		 desinstalled();
/*
		for(i=0; i<MAX_COM; i++)
		{
		 if( comm_info[i].connection==RS485_LINK ||
				 comm_info[i].connection==SERIAL_LINK ||
				 comm_info[i].connection==MODEM_LINK )
//				 (comm_info[i].connection==SERIAL_LINK && control) )
		 {
			comm_info[i].NetworkAddress = NetworkAddress;
			memcpy(comm_info[i].NetworkName, Panel_Info1.network_name, sizeof(comm_info[i].NetworkName));
		 }
		}
*/
		 save_config(CNF_COMM);
		 save_config(CNF_IORATE);
		 install_port();
		}
	 }
	 }
	 else
		 DisplayMessage(10, 7, 70, 11, pressanykey, invalpanelnr, NULL, Black, NULL, 60000);
	}
//	if(control && ptr_panel)
	if(ptr_panel)
	{
	 if(local_panel)
	 {
		if(control)
		{
		disable();
		ptr_panel->Config_dacqd_card();
		enable();
		}
		for(int k=0,j=0,i=0;i<ptr_panel->number_of_boards;i++)
		{
		j += boards[i].no_outs;
		k += boards[i].no_ins;
		}
//	  ptr_panel->table_bank[0] = control?j:MAX_OUTS; // set to 0 at the end
//	  ptr_panel->table_bank[1] = control?k:MAX_INS; //     - || -
		ptr_panel->table_bank[0] = j; // set to 0 at the end
		ptr_panel->table_bank[1] = k; //     - || -
		memcpy( tbl_bank, ptr_panel->table_bank, sizeof(tbl_bank));
	 }
	}
	}
	else
	 DisplayMessage(mode_text?18:150, mode_text?7:150, mode_text?62:510, mode_text?11:210, NULL, " Unsaved changes. Unauthorized access! ", NULL, Black, NULL, 1500);
 }

 set_semaphore_dos();
 delete b;
 delete f;
 delete s;
 clear_semaphore_dos();
}

void resetop(void)
{
/*
 int last=0,i;
	 GWDialog *D;
	 D = new GWDialog(20,8,60,14,NO_STACK,0);
//	 D->exitCR = 1;
	 D->select = 1;
//				 D->enter = 1;
	 D->GWSet("",Lightgray,Darkgray);
	 D->GShowWindow(DIALOG);
	 hide_pointer();
	 Bordergr(27, 10, 51, 10, Black, Cyan, Lightgray, Black, 0, 1);
	 Bordergr(27, 12, 51, 12, Black, Cyan, Lightgray, Black, 0, 1);
	 display_pointer();
	 D->GDDef_object(NULL, 7,1, 24, Cyan, Black, "Reset Acquisition Board", Darkgray , White);
	 D->GDDef_object(NULL, 7,3, 24, Cyan, Black, "Reset System", Darkgray , White);
	 while(!(D->HandleEvent()));
	 last=D->last;
	 i=D->index_cur;
	 delete D;
	 if( last==13 )
	 {
		char pass[9]={0};
		getpassword(pass);
		if( !strcmp(pass,password) )
		{
		 if( i==0 )
		 {
			if(control)
			{
			 ptr_panel->Aio_Control( RESET_CARD, NULL, 0 );
			}
		 }
		 if( i==1 )
		 {
			if(control)
			{
			 ptr_panel->Aio_Control( RESET_PC, NULL, 0 );
         }
		 }
		} 
	 }
*/
	uint l;
	char pass[15]={0};
	getpassword(pass, " Remote reset password: ");
	if( !strcmp(pass,"RESET") )
	{
	 l=1;
	 net_call(50+100, 50, pass, &l, station_num, networkaddress);
	}
}

void PutCheckBox(int lx, int ly, char *string, int fondcolor, int bkgnd, int frgnd)
{
	Bordergr(lx, ly, lx, ly, Black, fondcolor, bkgnd, bkgnd, 3, 1);
	mxyputs(lx + 2, ly, string, fondcolor, frgnd);
	moutchar(lx + 2, ly , string[0], fondcolor, Lightred);
}

void CheckBox(int lx, int ly, int bkgnd, int frgnd)
{
 moutchar(lx, ly, 'X', bkgnd, frgnd);
}
void UnCheckBox(int lx, int ly, int bkgnd, int frgnd)
{
 moutchar(lx, ly, ' ', bkgnd, frgnd);
}

void pactivate(GWDialog *D)
{
		  activate_tmp += 1;
		  if(activate_tmp > 1)
			 activate_tmp = 0;
		  switch (activate_tmp)
		  {
			 case 1:  D->GWPuts(i_files,24,autoac_text,Lightgray,Black);
						 break;
			 case 0:	 D->GWPuts(i_files,24,userac_text,Lightgray,Black);
						 break;
		  }
}

void pmodemconfigdefault(GWDialog *D)
{
	  strcpy(tempbuf, default_string);
	  D->GDPuts(1,24, tempbuf, 40 ,Cyan,Black);
}

void portscreen(GWDialog *D, int s)
{
 char irq[6],brate[10];
 strcpy(irq,"irq");
 for(int i=s;i<s+4;i++)
 {
//	D->GWPuts(3+i, 14, com_buf[comm_info[i].port_name+1], Cyan, Black);
	D->GWPuts(3+i, 2, connection_type_text[comm_info[i].connection], Cyan, Black);
	D->GWPuts(3+i, 17, com_buf[i+1], Cyan, Black);
	if(comm_info[i].int_name==ILLEGAL_IRQ)
		D->GWPuts(3+i, 23, na, Cyan, Black);
	else
	{
		itoa(comm_info[i].int_name, &irq[3], 10);
		if(strlen(irq)==4) strcat(irq," ");
		D->GWPuts(3+i, 23, irq, Cyan, Black);
	}
	ltoa( comm_info[i].baudrate, brate, 10);
	D->GWPuts( 3+i,30, 6, brate, Cyan, Black);
 }
}

void portscreenmini(GWDialog *D, int s)
{
 char irq[6],brate[10];
 strcpy(irq,"irq");
 for(int i=s;i<s+2;i++)
 {
	D->GWPuts(3+i, 2, connection_type_text[comm_info[i].connection], Cyan, Black);
	D->GWPuts(3+i, 17, com_buf[i+1], Cyan, Black);
	ltoa( comm_info[i].baudrate, brate, 10);
	D->GWPuts( 3+i,30, 6, brate, Cyan, Black);
 }
}

void pnext(GWDialog *D)
{
}

void adetect(GWDialog *D)
{
	union key key;
	char irq[6],p[5];
	int k;
	Comm_Info *comm_info_temp;
	if(check_access(12) == R_READ_WRITE)
	{
		int i;
		set_semaphore_dos();
		comm_info_temp = new Comm_Info[MAX_COMM_INFO];
		clear_semaphore_dos();
		mouseint();
		memcpy(comm_info_temp, comm_info, sizeof(Comm_Info)*MAX_COMM_INFO);
		autodetect_state=1;
		desinstalled();
		for(int j=0; j<MAX_COM; j++)
		  comm_info[j].connection=0;
		mouseint();
		for(i=0; i<MAX_COM; i++)
		{
		 if( comm_info[i].connection!=MOUSE_LINK )
		 {
		  comm_info[i].connection = MODEM_LINK;
		  for(int j=IRQ3; j<=IRQ7; j++)
		  {
			Delay( 300 );
			comm_info[i].int_name = j;
// Display message trying...
			trying_mess[13] = '1' + comm_info[i].port_name;
			trying_mess[23] = '0' + comm_info[i].int_name;
			k=install_port(i);
			if(k>=0)
			 if( ((class PTP *)Routing_table[k].ptr)->modem_active || ((class PTP *)Routing_table[k].ptr)->modem_status == MODEM_USER_ABORT) break;
			desinstalled();
		  }
		  if( j > IRQ7 )
			  comm_info[i]=comm_info_temp[i];
		 }
		}
		autodetect_state=0;
		desinstalled();
		install_port();
		portscreen(D, 0);
		memcpy(pcomminfo, comm_info, sizeof(Comm_Info)*MAX_COMM_INFO);
		set_semaphore_dos();
		delete [] comm_info_temp;
		clear_semaphore_dos();
	 }
	 else
		 DisplayMessage(mode_text?19:160, mode_text?8:160, mode_text?61:500, mode_text?12:220, NULL, " Unauthorized access! ", NULL, Black, NULL, 1200);
}

int pirq(GWDialog *D, int i)
{
 union key key;
 char irq[6];
 if(pcomminfo[i].int_name!=ILLEGAL_IRQ)
 {
  strcpy(irq,"irq");
// irq[3] = 0x30 + comm_info[i].int_name;
  itoa(pcomminfo[i].int_name, &irq[3], 10);
 }
 else
  strcpy(irq,na);
// while(1)
// {
//	D->select = 1;
//	D->GDGets(irq,3+i,20,4,Black,White);
//	D->select = 0;
//	if(	D->last == 13)
//	{
	 if(check_access(12) == R_READ_WRITE)
	 {
	  if(pcomminfo[i].port_name!=COM0)
	  {
		pcomminfo[i].int_name += 1;
		if(pcomminfo[i].int_name > 15) pcomminfo[i].int_name = 1;
//		irq[3] = 0x30 + comm_info[i].int_name;
		itoa(pcomminfo[i].int_name, &irq[3], 10);
		if(strlen(irq)==4) strcat(irq," ");
		D->GWPuts(3+i,23, irq, Cyan, Black);
	  }
	 }
	 else
		 DisplayMessage(mode_text?19:160, mode_text?8:160, mode_text?61:500, mode_text?12:220, NULL, " Unauthorized access! ", NULL, Black, NULL, 1200);
//	 continue;
//	}
//	break;
// }
}

int pconport(GWDialog *D, int i)
{
	union key key;
	char irq[6],p[5];
		strcpy(irq,"irq");
		if(check_access(12) == R_READ_WRITE)
		{
		 if( pcomminfo[i].connection != MOUSE_LINK )
		 {
			pcomminfo[i].connection += 1;
			if(pcomminfo[i].connection == RS485_LINK)
			 pcomminfo[i].NetworkAddress = 9999;
			if(pcomminfo[i].connection == SERIAL_LINK||pcomminfo[i].connection == MODEM_LINK)
			{
//				pcomminfo[i].NetworkAddress=NetworkAddress;
				pcomminfo[i].NetworkAddress=9999;
			}
			if(pcomminfo[i].connection > ASYNCRON_LINK)
			 pcomminfo[i].connection = 0;
			D->GWPuts(3+i, 2, connection_type_text[pcomminfo[i].connection], Cyan, Black);
			pcomminfo[i].int_name = pcomminfo[i].port_name%2?3:4;
			{
			itoa(pcomminfo[i].int_name, &irq[3], 10);
			if(strlen(irq)==4) strcat(irq," ");
			D->GWPuts(3+i,23, irq, Cyan, Black);
		  }
		 }
		}
		else
		 DisplayMessage(mode_text?19:160, mode_text?8:160, mode_text?61:500, mode_text?12:220, NULL, " Unauthorized access! ", NULL, Black, NULL, 1200);
//		continue;
//	 }
//	 break;
//	}
}

int pconportmini(GWDialog *D, int i)
{
		if(check_access(12) == R_READ_WRITE)
		{
			pcomminfomini[i].media_type += 1;

//			if(pcomminfo[i].connection == RS485_LINK)
//			 pcomminfo[i].NetworkAddress=NetworkAddress;
			if( pcomminfomini[i].media_type == MODEM_LINK ) pcomminfomini[i].media_type++;
			if(pcomminfomini[i].media_type > ASYNCRON_LINK)
			 pcomminfomini[i].media_type = 1;
			D->GWPuts(3+i, 2, connection_type_text[pcomminfomini[i].media_type], Cyan, Black);
		}
		else
		 DisplayMessage(mode_text?19:160, mode_text?8:160, mode_text?61:500, mode_text?12:220, NULL, " Unauthorized access! ", NULL, Black, NULL, 1200);
}

/*
int pport(GWDialog *D, int i)
{
	union key key;
	char irq[6],p[5];
// strcpy(port,"com ");
	strcpy(irq,"irq");
// port[3] = 0x31 + comm_info[i].port_name;
//	while(1)
//	{
//	 strcpy(p,&com_buf[comm_info[i].port_name+1][0]);
//	 D->select = 1;
//	 D->GDGets(p,3+i,14,4,Black,White);
//	 D->select = 0;
//	 if(D->last == 13)
//	 {
		if(check_access(12) == R_READ_WRITE)
		{
		  comm_info[i].port_name += 1;
		  if(comm_info[i].port_name > 3)
			 if (i!=2)  comm_info[i].port_name = COM0;
		  if(comm_info[i].port_name > 4)
			 comm_info[i].port_name = COM0;
//		port[3] = 0x31 + comm_info[i].port_name;
		  D->GWPuts(3+i,16, com_buf[comm_info[i].port_name+1], Cyan, Black);
		  if(comm_info[i].port_name == COM0)
			 comm_info[i].int_name = ILLEGAL_IRQ;
		  else
			 comm_info[i].int_name = comm_info[i].port_name%2?3:4;
//		 irq[3] = 0x30 + comm_info[i].int_name;
		  if(comm_info[i].int_name==ILLEGAL_IRQ)
			D->GWPuts(3+i, 22, na, Cyan, Black);
		  else
		  {
			itoa(comm_info[i].int_name, &irq[3], 10);
			if(strlen(irq)==4) strcat(irq," ");
			D->GWPuts(3+i,22, irq, Cyan, Black);
		  }
		}
		else
		 DisplayMessage(mode_text?19:160, mode_text?8:160, mode_text?61:500, mode_text?12:220, NULL, " Unauthorized access! ", NULL, Black, NULL, 1200);
}
*/

int prate(GWDialog *D, int i)
{
	union key key;
	char brate[7],irate,blank[7];
	memset(blank,' ',6);
	blank[6]=0;
	for(int j = 0; j< MAX_RATES;j++)
	 if ( pcomminfo[i].baudrate == rate[j])
		break;
	if( (irate = j) > MAX_RATES-1) irate = 0;
	ltoa(rate[irate], brate, 10);
//	while(1)
//	{
//	 D->select = 1;
//	 D->GDGets(brate,3+i,26,4,Black,White);
//	 D->select = 0;
//	 if(	D->last == 13)
//	 {
		if(check_access(12) == R_READ_WRITE)
		{
		 if(++irate > MAX_RATES-1) irate = 0;
		 ltoa(rate[irate], brate, 10);
		 D->GWPuts(3+i,30, blank, Lightgray, Lightgray);
		 D->GWPuts(3+i,30, brate, Cyan, Black);
		}
		else
		 DisplayMessage(mode_text?19:160, mode_text?8:160, mode_text?61:500, mode_text?12:220, NULL, " Unauthorized access! ", NULL, Black, NULL, 1200);
//		continue;
//	 }
//	 break;
//	}
	pcomminfo[i].baudrate = rate[irate];
}

int pratemini(GWDialog *D, int i)
{
	char brate[8],irate,blank[7];
	memset(blank,' ',6);
	blank[6]=0;
	for(int j = 0; j< MAX_RATES;j++)
	 if ( pcomminfomini[i].baud_rate == rate[j])
		break;
	irate = j;
	if(check_access(12) == R_READ_WRITE)
	{
		 if(++irate > MAX_RATES-3) irate = 0;
		 ltoa(rate[irate], brate, 10);
		 D->GWPuts(3+i,24, blank, Lightgray, Lightgray);
		 D->GWPuts(3+i,24, brate, Cyan, Black);
	}
	else
		 DisplayMessage(mode_text?19:160, mode_text?8:160, mode_text?61:500, mode_text?12:220, NULL, " Unauthorized access! ", NULL, Black, NULL, 1200);
	pcomminfomini[i].baud_rate = rate[irate];
}

void conport1(GWDialog *D)
{
 pconport(D, 0);
}
void conport2(GWDialog *D)
{
 pconport(D, 1);
}
void conport3(GWDialog *D)
{
 pconport(D, 2);
}
void conport4(GWDialog *D)
{
 pconport(D, 3);
}

void conportmini1(GWDialog *D)
{
 pconportmini(D, 0);
}
void conportmini2(GWDialog *D)
{
 pconportmini(D, 1);
}

/*
void mport(GWDialog *D)
{
 pport(D, 1);
}
void sport(GWDialog *D)
{
 pport(D, 0);
}
void s485port(GWDialog *D)
{
 pport(D, 2);
}
void mouseport(GWDialog *D)
{
 pport(D, 3);
}
*/
void eport(GWDialog *D)
{
 char ptr[5];
 if(check_access(12) == R_READ_WRITE)
 {
		if(tmp_IPX_enabled)
		{
			tmp_IPX_enabled=0;
			strcpy(ptr,"No ");
		}
		else
		{
			tmp_IPX_enabled=1;
			strcpy(ptr,"Yes");
		}
		D->GWPuts(8,17, ptr, Cyan, Black);
 }
 else
		 DisplayMessage(mode_text?19:160, mode_text?8:160, mode_text?61:500, mode_text?12:220, NULL, " Unauthorized access! ", NULL, Black, NULL, 1200);
}

void irq1(GWDialog *D)
{
 pirq(D, 0);
}
void irq2(GWDialog *D)
{
 pirq(D, 1);
}
void irq3(GWDialog *D)
{
 pirq(D, 2);
}
void irq4(GWDialog *D)
{
 pirq(D, 3);
}

void rate1(GWDialog *D)
{
 prate(D, 0);
}
void rate2(GWDialog *D)
{
 prate(D, 1);
}
void rate3(GWDialog *D)
{
 prate(D, 2);
}
void rate4(GWDialog *D)
{
 prate(D, 3);
}

void ratemini1(GWDialog *D)
{
 pratemini(D, 0);
}
void ratemini2(GWDialog *D)
{
 pratemini(D, 1);
}

// com = 10 - ethernet
void pmore(int com)
{
 char buf[10]={'A','T',' ','S','0','=',0,0};
 char buf1[8];
 FILE *fhandle;
 GWDialog *D;
 int number_rings,y;

 if(com==10)
 {
		D = new GWDialog(7,8,73,17,NO_STACK,0);
		D->enter = 1;
		D->GWSet("",Lightgray,Darkgray);
		D->GShowWindow(DIALOG);
		Bordergr(22, 15, 31, 15, Black, Cyan, Lightgray, Black, 0, 1);
		Bordergr(37, 15, 46, 15, Black, Cyan, Lightgray, Black, 0, 1);
		itoa(ipxtempNetworkAddress,buf,10);
		memcpy(tempbuf,NetworkName,NAME_SIZE);
		D->GWPuts(1,2,"Network number : ",Lightgray,Black);
		D->GWPuts(2,2,"Network name   : ",Lightgray,Black);
		D->GDDef_object(NULL, 24,1, 5, Cyan, Black, buf, Darkgray , White);
		D->GDDef_object(NULL, 24,2, 16, Cyan, Black, tempbuf, Darkgray , White);
		D->GDDef_object(NULL,15,6,8,Cyan,Black,ok_button,Cyan,White,NULL,0,'O',3);
		D->GDDef_object(NULL,30,6,8,Cyan,Black,cancel_button,Cyan,White,NULL,1,'C',1);
		D->index_cur = 0;
		while(!(D->HandleEvent()));
		char ok=D->ok;
		delete D;
		if(ok)
			if(check_access(12) == R_READ_WRITE)
			{
			 ipxtempNetworkAddress=atoi(buf);
			 memcpy(NetworkName,tempbuf,NAME_SIZE);
			}
 }
 else
	if(pcomminfo[com].connection && pcomminfo[com].connection!=MOUSE_LINK)
	{
//	 char net_no[6], net_name[17];
	 strcpy(tempbuf, &pcomminfo[com].modemdata.first_init_string[0]);
	 number_rings = pcomminfo[com].rings;
	 activate_tmp = pcomminfo[com].activate;
//	 itoa(pcomminfo[com].NetworkAddress,net_no,10);
//	 memcpy(net_name,pcomminfo[com].NetworkName,NAME_SIZE);
	 y = 1;
		D = new GWDialog(7,8,73,17,NO_STACK,0);
//				 D->exitCR = 1;
		D->enter = 1;
		D->GWSet("",Lightgray,Darkgray);
		D->GShowWindow(DIALOG);
		Bordergr(22, 15, 31, 15, Black, Cyan, Lightgray, Black, 0, 1);
		Bordergr(37, 15, 46, 15, Black, Cyan, Lightgray, Black, 0, 1);
		switch ( pcomminfo[com].connection ) {
		case SERIAL_LINK:
		case MODEM_LINK:
		{
//---------
		 itoa(pcomminfo[com].NetworkAddress,buf1,10);
		 D->GWPuts(1,2,"Network number : ",Lightgray,Black);
		 D->GDDef_object(NULL, 24,1, 5, Cyan, Black, buf1, Darkgray , White);
//-----------

		 if( pcomminfo[com].connection == MODEM_LINK )
					 Bordergr(52, 15, 60, 15, Black, Cyan, Lightgray, Black, 0, 1);
		 if( pcomminfo[com].connection == MODEM_LINK )
		 {
					D->GWPuts(2,2,"Initializing string : ",Lightgray,Black);
					D->GWPuts(3,2,"Answer rings number : ",Lightgray,Black);
					y = 4;
		 }
		 else
			 y = 2;
		 D->GWPuts(y,2,"Connection activate : ",Lightgray,Black);
		 i_files = y;
		 if(pcomminfo[com].activate)
					D->GWPuts(y,24,autoac_text,Lightgray,Black);
		 else
					D->GWPuts(y,24,userac_text,Lightgray,Black);
		 if( pcomminfo[com].connection == MODEM_LINK )
					 D->GWPuts(6,45,"Default",Cyan,Black);

		 itoa(number_rings, &buf[6], 10);

		 if( pcomminfo[com].connection == MODEM_LINK )
		 {
					D->GDDef_object(NULL, 24,2, 40, Cyan, Black, tempbuf, Darkgray , White);
					D->GDDef_object(NULL, 24,3, 2, Cyan, Black, &buf[6], Darkgray , White);
		 }
		 D->GDDef_object(pactivate,24,y,13,Cyan,Black);
		 D->GDDef_object(NULL,15,6,8,Cyan,Black,ok_button,Cyan,White,NULL,0,'O',3);
		 D->GDDef_object(NULL,30,6,8,Cyan,Black,cancel_button,Cyan,White,NULL,1,'C',1);
		 if( pcomminfo[com].connection == MODEM_LINK )
		 {
					D->GDDef_object(pmodemconfigdefault,45,6,7,Cyan,Black);
		 }
		 D->index_cur = 0;
		 while(!(D->HandleEvent()));
		 char ok=D->ok;
		 delete D;
		 if(ok)
		  if(check_access(12) == R_READ_WRITE)
			{
			 strcpy(&pcomminfo[com].modemdata.first_init_string[0], tempbuf);
//	 strcpy(&ModemDataBase[0].second_init_string[0], buf);
			 number_rings=atoi(&buf[6]);
			 if(!number_rings) number_rings=1;
			 pcomminfo[com].rings=number_rings;
			 pcomminfo[com].activate=activate_tmp;
			 pcomminfo[com].NetworkAddress=atoi(buf1);
//			 save_config( CNF_MODEM_INFO );
		  }
		  else
			DisplayMessage(mode_text?18:150, mode_text?7:150, mode_text?62:510, mode_text?11:210, NULL, " Unsaved changes. Unauthorized access! ", NULL, Black, NULL, 1500);
		 break;
		}
	  case ASYNCRON_LINK:
	  {
		 y = pcomminfo[com].program_nr;
		 D->GWPuts(1,2,"Program number : ",Lightgray,Black);
		 itoa(y, buf, 10);
		 D->GDDef_object(NULL, 24,1, 2, Cyan, Black, buf, Darkgray , White);
		 D->GDDef_object(NULL,15,6,8,Cyan,Black,ok_button,Cyan,White,NULL,0,'O',3);
		 D->GDDef_object(NULL,30,6,8,Cyan,Black,cancel_button,Cyan,White,NULL,1,'C',1);
		 D->index_cur = 0;
		 while(!(D->HandleEvent()));
		 char ok=D->ok;
		 delete D;
		 if(ok)
			if(check_access(12) == R_READ_WRITE)
			{
			 y=atoi(buf);
//			 if(!number_rings) number_rings=1;
			 if( y > tbl_bank[PRG] ) y=0;
			 if( y!= pcomminfo[com].program_nr )
			 {
				if( pcomminfo[com].program_nr )
				 if( ptr_panel->programs[pcomminfo[com].program_nr-1].com_prg )
				 {
					ptr_panel->programs[pcomminfo[com].program_nr-1].com_prg=0;
				 }
				pcomminfo[com].program_nr=y;
				if(y)
				{
				 ptr_panel->programs[y-1].com_prg=1;
				}
			 }
			}
			else
			DisplayMessage(mode_text?18:150, mode_text?7:150, mode_text?62:510, mode_text?11:210, NULL, " Unsaved changes. Unauthorized access! ", NULL, Black, NULL, 1500);
		 break;
	  }
	  case RS485_LINK:
	  {
		 itoa(pcomminfo[com].NetworkAddress,buf,10);
		 memcpy(tempbuf,pcomminfo[com].NetworkName,NAME_SIZE);
		 D->GWPuts(1,2,"Network number : ",Lightgray,Black);
		 D->GWPuts(2,2,"Network name   : ",Lightgray,Black);
		 D->GDDef_object(NULL, 24,1, 5, Cyan, Black, buf, Darkgray , White);
		 D->GDDef_object(NULL, 24,2, 16, Cyan, Black, tempbuf, Darkgray , White);
		 D->GDDef_object(NULL,15,6,8,Cyan,Black,ok_button,Cyan,White,NULL,0,'O',3);
		 D->GDDef_object(NULL,30,6,8,Cyan,Black,cancel_button,Cyan,White,NULL,1,'C',1);
		 D->index_cur = 0;
		 while(!(D->HandleEvent()));
		 char ok=D->ok;
		 delete D;
		 if(ok)
			if(check_access(12) == R_READ_WRITE)
		  {
			 pcomminfo[com].NetworkAddress=atoi(buf);
			 memcpy(pcomminfo[com].NetworkName,tempbuf,NAME_SIZE);
			}
		 break;
	  }
	  }
	 }
}

void more1(GWDialog *D)
{
 pmore(0);
}
void more2(GWDialog *D)
{
 pmore(1);
}
void more3(GWDialog *D)
{
 pmore(2);
}
void more4(GWDialog *D)
{
 pmore(3);
}
void more5(GWDialog *D)
{
 pmore(10);
}

void portconfig(void)
{
 set_semaphore_dos();
 pcomminfo = new Comm_Info[MAX_COMM_INFO];
 clear_semaphore_dos();
 memcpy( pcomminfo, comm_info, sizeof(Comm_Info)*MAX_COMM_INFO);
 tmp_IPX_enabled = IPX_enabled;
 ipxtempNetworkAddress=NetworkAddress;
// ********  the old code  ********
// GWDialog *D = new GWDialog(mode_text?15:120,mode_text?5:80,mode_text?71:568,mode_text?20:350,NO_STACK,0,SMALL_FONT,5,1);
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.032  ********
// ********       begin       ********
// ***********************************
 GWDialog *D = new GWDialog(300,"need_help",mode_text?15:120,mode_text?5:80,mode_text?71:568,mode_text?20:350,NO_STACK,0,SMALL_FONT,5,1);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.032  ********
// ********        end        ********
// ***********************************

 D->GWSet("Communications",Lightgray,Darkgray);
 D->GShowWindow(DIALOG);

 D->GWPuts(1,2,"Connection     PORT    IRQ   Rate",Lightgray,Black);

// D->GWPuts(9, 3,"Mouse    : ",Lightgray,Black);
// D->GWPuts(10,3,"Printer  : ",Lightgray,Black);

 hide_pointer();
 if(mode_text)
 {
	Bordergr(56, 18, 68, 18, Black, Cyan, Lightgray, Black, 0, 1);
	Bordergr(41, 18, 53, 18, Black, Cyan, Lightgray, Black, 0, 1);
	Bordergr(30, 18, 37, 18, Black, Cyan, Lightgray, Black, 0, 1);
	Bordergr(19, 18, 26, 18, Black, Cyan, Lightgray, Black, 0, 1);

	Bordergr(53, 9, 60,  9, Black, Cyan, Lightgray, Black, 0, 1);
	Bordergr(53, 10, 60, 10, Black, Cyan, Lightgray, Black, 0, 1);
	Bordergr(53, 11, 60, 11, Black, Cyan, Lightgray, Black, 0, 1);
	Bordergr(53, 12, 60, 12, Black, Cyan, Lightgray, Black, 0, 1);
	Bordergr(53, 14, 60, 14, Black, Cyan, Lightgray, Black, 0, 1);
 }
 display_pointer();
 D->GWPuts(3,38,more_text,Cyan,Black);
 D->GWPuts(4,38,more_text,Cyan,Black);
 D->GWPuts(5,38,more_text,Cyan,Black);
 D->GWPuts(6,38,more_text,Cyan,Black);
 D->GWPuts(8,38,more_text,Cyan,Black);

 D->GWPuts(8,2,"Ethernet    ",Cyan,Black);
 if(IPX_enabled)
	 D->GWPuts(8,17,"Yes ",Cyan,Black);
 else
	 D->GWPuts(8,17,"No  ",Cyan,Black);

 D->GWPuts(mode_text?12:10,41,"Next screen",Cyan,Black);
 D->GWPuts(mode_text?12:10,26,autodetect,Cyan,Black);
 D->enter=1;
 portscreen(D, 0);

 D->GDDef_object(conport1,2,3,13,Cyan,Black);
 D->GDDef_object(conport2,2,4,13,Cyan,Black);
 D->GDDef_object(conport3,2,5,13,Cyan,Black);
 D->GDDef_object(conport4,2,6,13,Cyan,Black);

// D->GDDef_object(sport,14,3,4,Cyan,Black);
// D->GDDef_object(mport,14,4,4,Cyan,Black);
// D->GDDef_object(s485port,14,5,4,Cyan,Black);
// D->GDDef_object(mouseport,14,6,4,Cyan,Black);
 D->GDDef_object(irq1,23,3,5,Cyan,Black);
 D->GDDef_object(irq2,23,4,5,Cyan,Black);
 D->GDDef_object(irq3,23,5,5,Cyan,Black);
 D->GDDef_object(irq4,23,6,5,Cyan,Black);
 D->GDDef_object(rate1,30,3,6,Cyan,Black);
 D->GDDef_object(rate2,30,4,6,Cyan,Black);
 D->GDDef_object(rate3,30,5,6,Cyan,Black);
 D->GDDef_object(rate4,30,6,6,Cyan,Black);
 D->GDDef_object(more1,38,3,7,Cyan,Black);
 D->GDDef_object(more2,38,4,7,Cyan,Black);
 D->GDDef_object(more3,38,5,7,Cyan,Black);
 D->GDDef_object(more4,38,6,7,Cyan,Black);

 D->GDDef_object(eport,17,8,4,Cyan,Black);
 D->GDDef_object(more5,38,8,7,Cyan,Black);

 D->GDDef_object(NULL,3,mode_text?12:10,8,Cyan,Black,ok_button,Cyan,White,NULL,0,'O',3);
 D->GDDef_object(NULL,14,mode_text?12:10,8,Cyan,Black,cancel_button,Cyan,White,NULL,1,'C',1);
 D->GDDef_object(adetect,26,mode_text?12:10,11,Cyan,Black);
 D->GDDef_object(pnext,41,mode_text?12:10,11,Cyan,Black);
 D->index_cur=0;

 keyboard_data=0;
 while(!D->HandleEvent());
// set_semaphore_dos();
 char ok=D->ok;
 if(D) delete D;
// clear_semaphore_dos();

 int i,err;
 if( ok && check_access(12)==R_READ_WRITE )
 {
	err = 0;
	for(i=0;i<MAX_COM;i++)
	{
	 if(pcomminfo[i].connection == RS485_LINK)
	 {
			if( pcomminfo[i].NetworkAddress == ipxtempNetworkAddress )
			{
			 err=1;
			 DisplayMessage(5, 10, 75, 14, pressanykey,"Error!. There are two ports with the same network number.", NULL, Blue, NULL, 30000);
			 break;
			}
	 }
	}
	if(!err)
	{
		for(i=0;i<MAX_COM;i++)
		{
		 if(pcomminfo[i].connection == SERIAL_LINK || pcomminfo[i].connection == MODEM_LINK )
		 {
			if( pcomminfo[i].NetworkAddress == 9999 )
			{
				for(int j=0;j<MAX_COM;j++)
				{
				 if(pcomminfo[j].connection == RS485_LINK ) break;
				}
				if(j<MAX_COM)
				 pcomminfo[i].NetworkAddress = pcomminfo[j].NetworkAddress;
				else
				 pcomminfo[i].NetworkAddress = ipxtempNetworkAddress;
			}
		 }
		}
		desinstalled();
		memcpy( comm_info, pcomminfo, sizeof(Comm_Info)*MAX_COMM_INFO);
	}
	set_semaphore_dos();
	delete pcomminfo;
	clear_semaphore_dos();
	pcomminfo = NULL;
	if(!err)
	{
	 NetworkAddress = ipxtempNetworkAddress;
	 IPX_enabled = tmp_IPX_enabled;
//	ModemDataBase[0].initial_baud_rate = comm_info[MODEM_LINK].baudrate;
	 i=-1;
	 while(++i<MAX_COM)
	 {
		if(comm_info[MOUSE_COMM_ENTRY].int_name==comm_info[i].int_name && i!=comm_info[MOUSE_COMM_ENTRY].port_name)
		{
		 comm_info[i].connection = 0;
		}
	 }
	 save_config(CNF_COMM);
//	save_config(CNF_MODEM_INFO);
	 install_port();
	}
 }
 else
 {
	set_semaphore_dos();
	delete pcomminfo;
	clear_semaphore_dos();
	pcomminfo = NULL;
 }
}

void mouseint(void)
{
 signed char j=0,i;
 if(mouse_inst)
 {
  asm mov ax,24h
  asm int 33h
  j = _CL;
 }
 i=BUS;
 if(j==IRQ3) i=COM2;
 if(j==IRQ4) i=COM1;
 comm_info[MOUSE_COMM_ENTRY].port_name = i;
 if(!j)
 {
  j = ILLEGAL_IRQ;
  comm_info[MOUSE_COMM_ENTRY].port_name = COM0;
 }

 comm_info[MOUSE_COMM_ENTRY].int_name = j;

 if(comm_info[MOUSE_COMM_ENTRY].port_name != COM0 && i!=BUS)
 {
  comm_info[i] = comm_info[MOUSE_COMM_ENTRY];
 }

/*
 signed char j=0,i;
 if(mouse_inst)
 {
  asm mov ax,24h
  asm int 33h
  j = _CL;
 }
 i=BUS;
 if(j==IRQ3) i=COM2;
 if(j==IRQ4) i=COM1;
 comm_info[MOUSE_COMM].port_name = i;
 if(!j)
 {
  j = ILLEGAL_IRQ;
  comm_info[MOUSE_COMM].port_name = COM0;
 }
 comm_info[MOUSE_COMM].int_name = j;
 for(int k=0; k<3; k++)
 {
  if(comm_info[k].int_name == j)
  {
	comm_info[k].port_name = COM0;
	comm_info[k].int_name = ILLEGAL_IRQ;
  }
 }
*/
}

int handle_command( Modem *modem )
{
		int c;
		int i;
		ModemError status;
		char *command;
		int registers[ 11 ];
		char buf[20];

		mputs("\n\rAnswer Exit Dial Hangup Initialize Product-ID Read-regs Status\n\r\n\rEnter command: ", Blue, White);
		while(!bioskey_new(1));                //kbhit())
		c = bioskey_new(0);
		mputchar((char)c, Blue, White);
		mputchar(13, Blue, White);
		mputchar(10, Blue, White);
		switch ( toupper( c ) ) {
		  case 'A' :
//						command = "Answer";
						status = modem->Answer();
						break;
		  case 'D' :
//						command = "Dial";
						mputs("Dial number:",Blue,White);
						movetoxy(xscreen+1, yscreen+1);
						mgets(buf,1,Blue,White);
						status = modem->Dial( buf );
						break;
		  case 'E' :
		  case 27 :
						return 1;
		  case 'H' :
//				command = "Hangup";
				status = modem->Disconnect();
				break;
		  case 'I' :
//						command = "Initialize";
						status = modem->Initialize();
						break;
		  case 'P' :
//				command = "Product ID code";
				status = modem->SendCommand( "ATI0" );
				break;
		  case 'R' :
/*
				for ( i = 1 ; i < 11 ; i++ )
								registers[ i ] = modem->ReadRegister( i );
						for ( i = 1 ; i < 11 ; i++ ) {
					 cout << "Register " << i << " = ";
					 cout << registers[ i ] << '\n';
						}
*/
				return 0;
		  case 'S' :
				modem->DumpState();
				return 0;
		  default  :
//						cout << (char) 7; return 0;
						return 0;
		}
//		mputs(command);
//		mputs("returnd: ");
		mputs(modem->ErrorName( status ));
		mputchar(13, Blue, White);
		mputchar(10, Blue, White);

//		cout << command << " returned: " << modem.ErrorName( status ) << '\n';
		return 0;
}

void terminal_mode(void)
{
	int c;
	ModemError init;
	Serial *ser_m;
	int big;
	char *buf;
	int xold,yold;
	xold = xscreen;
	yold = yscreen;
	xscreen = yscreen = 0;
	if(mode_text)
	{
		big = 80*25*2;
		mfarmalloc((char far **)&buf, (unsigned long)big);
		mgettext(1, 1, 80, 25,(void *)buf);
	}
	mclrscr(1, 1, 80, 25, Blue);
//		init = modem.Initialize();
//		cout << "\nInitialization returned:  "
//				 << modem.ErrorName( init )
//				 << '\n';
		union key key;
		for(int i=0; i<MAX_Routing_table; i++)
		{
		 if( Routing_table[i].status&PTP_INSTALLED==PTP_INSTALLED )
		  if(((class PTP *)Routing_table[i].ptr)->media == MODEM_LINK )
		  {
			 break;
		  }
		}
		if(i>=MAX_Routing_table) { return;}
		ser_m = (class PTP *)Routing_table[i].ptr;
		for ( ; ; ) {
				if (bioskey_new(1))                //kbhit())
				{
						key.i = bioskey_new(0);
						if ( key.ch[0] == 27 ) {
								if ( handle_command( ser_m->modem_obj ) )
										break;
						} else
								ser_m->port->Write( key.ch[0] );
				}
				if ( ( c = ser_m->port->Read() ) > 0 )
						mputchar((char)c, Blue, White);
				if(yscreen > 24)
				{
					yscreen = 24;
					scrollup( 1, 1, 80, 24, (Blue<<4)+White);
				}
		}
		xscreen=xold;
		yscreen=yold;
		if(buf)
		{
		 mputtext(1, 1, 80, 25, (void *)buf);
		 mfarfree (buf);
		}
		return ;
}

int bioskey_new(int cmd)
{
 int i;
 if(simulate)
 {
	 if( bioskey(1) )
	 {
		i=bioskey(0);
		if( i==(F10KEY<<8))
		{
		 simulate = 0;
		 return 0;
    }
	 }
	 if(cmd)
	 {
		if(input_buffer[ind_input_buffer].key.key[0]=='$')
		{
			simulate = 0;
			return 0;
		}
		else
		{
			if( !time_key )
			{
				if(input_buffer[ind_input_buffer].key.key[0])
					return (input_buffer[ind_input_buffer].key.key[0]);
				else
					return ( input_buffer[ind_input_buffer].key.i);
			}
			else
				return 0;
		}
	 }
	 else
	 {
		time_key = input_buffer[ind_input_buffer+1].time;
		if(input_buffer[ind_input_buffer].key.key[0])
			return (input_buffer[ind_input_buffer++].key.key[0]);
		else
		{
			return ( input_buffer[ind_input_buffer++].key.i );
		}
	 }
 }
 else
 {
	if(cmd)
	{
	 i=bioskey(cmd);
	 if(serial_access)
	  if( ser_ptr )
		if( ser_ptr->Read_mode() == MASTER &&  disconnect_time>0)
		{
		  if(cmd==1 && i) disconnect_time = DISCONNECT_TIME;
		}
	 return i;
	}
	else
	{
	 i = bioskey(cmd);
	 if(def_macro)
	 {
	  if( ind_input_buffer < MAX_INPUT_BUFFER-2 )
		{
/*
		 time_last_key = 10;
		 if(ind_input_buffer)
		 {
			if( !input_buffer[ind_input_buffer-1].key.key[0] &&
				 (input_buffer[ind_input_buffer-1].key.key[1]==RIGHT ||
					input_buffer[ind_input_buffer-1].key.key[1]==LEFT  ||
					input_buffer[ind_input_buffer-1].key.key[1]==UP  ||
					input_buffer[ind_input_buffer-1].key.key[1]==DOWN))
					 time_last_key = 2;
		 }
*/
		 input_buffer[ind_input_buffer].key.i = i;
		 input_buffer[ind_input_buffer++].time = time_last_key;
//		if(time_last_key<60) time_last_key = 60;
		 time_last_key = 0;
		}

/*
		if(!input_buffer[ind_input_buffer].key.key[0])
		{
			switch(input_buffer[ind_input_buffer].key.key[1]) {
				case LEFT:
				case UP:
				case DOWN:
				case RIGHT:
				case DELETE:
				case PGUP:
				case PGDN:
				case HOME:
				case ENDKEY:
					input_buffer[ind_input_buffer++].time = 200;
					break;
				default:
					input_buffer[ind_input_buffer++].time = 300;
					break;
			}
		}
		else
		{
			if(input_buffer[ind_input_buffer].key.key[0] > 'A' && input_buffer[ind_input_buffer].key.key[0] < 'Z')
				input_buffer[ind_input_buffer++].time = 200;
			else
				input_buffer[ind_input_buffer++].time = 500;
		}
		if(ind_input_buffer >= MAX_INPUT_BUFFER) ind_input_buffer=0;
*/
	 }
	 return (i);
	}
 }
}

void pinfoscreen(GWDialog *D)
{
}

void pupdatet3000(GWDialog *D)
{
 unsigned updatet, k;
 int j;
 char buf[22], p1[8], p2[9], *ok, *er;
 ok=p1; er=p2;
 strcpy(ok,"  O.K.");
 strcpy(er,"  ERROR");
 GWindow *D1;
 D1 = new GWindow(30,5,55,22,NO_STACK,0);
 D1->GWSet(NULL,Lightblue,Blue);
 D1->GShowWindow(WIN_ERROR);

 if(!local_panel && serial_access)
 {
	k = 2;
	if( net_call(50,76,(char *)&updatet,&k,station_num, networkaddress)!=SUCCESS ) return;
 }
 else
  updatet = update_t3000exe;
 k = 1;
 for(int i=0;i<MAX_STATIONS;i++)
 {
	if(station_list[i].state)
	{
	j=0;
	if(updatet&(1<<i)) j=1;
	strcpy(buf, "Panel ");
	itoa(i+1, &buf[6], 10);
	strcat(buf, j?ok:er);
	D1->GWPuts(k++,3, buf, Lightblue, White);
  }
 }
 getkey();
 D1->GReleaseWindow();
 delete D1;
}

void infoscreen(void)
{
 char buf[80];
// ********  the old code  ********
// GWDialog *D = new GWDialog(15,6,65,17,NO_STACK,0);
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.035  ********
// ********       begin       ********
// ***********************************
 GWDialog *D = new GWDialog(3,"need help",15,6,65,17,NO_STACK,0);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.035  ********
// ********        end        ********
// ***********************************
 D->GWSet(NULL,Lightgray,Darkgray);
 D->GShowWindow(DIALOG);

 D->GWPuts(1,3,"Panel name : ",Lightgray,Black);
 D->GWPuts(1,16,Station_NAME,Lightgray,Black);
 D->GWPuts(3,3,"EPROM version ",Lightgray,Black);
 ptr_panel->Aio_Control( VERSION, buf, 0);
 memset(buf,0,50);
 D->GWPuts(3,17,buf,Lightgray,Black);
 D->GWPuts(3,27,"T3000 version ",Lightgray,Black);
 if( panel_info1.panel_type==MINI_T3000 )
 {
  D->GWPuts(4,27,"MINI version ",Lightgray,Black);
	itoa(panel_info1.version,buf,10);
	memmove(&buf[strlen(buf)-1], &buf[strlen(buf)-2], 3);
	buf[strlen(buf)-3]='.';
	D->GWPuts(4,40,buf,Lightgray,Black);
 }
 D->GWPuts(3,41,version,Lightgray,Black);
 D->GWPuts(5,3,"LINES STATUS",Lightgray,Black);
 D->GWPuts(6,5,"Modem",Lightgray,Black);
/*
 if(ser_m)
 {
	if(ser_m->port_status == INSTALLED)
	{
		strcpy(buf, "Installed     ");
		if(ser_m->activity == FREE)
		 strcat(buf, "Disconnected");
		else
		 strcat(buf, "Connected");
	}
	else
	  strcpy(buf, "Not Installed  ");
 }
 D->GWPuts(6,14,buf,Lightgray,Black);
*/
 D->GWPuts(7,5,"Serial",Lightgray,Black);
/*
 if(ser_p)
 {
	if(ser_p->port_status == INSTALLED)
	{
	  strcpy(buf, "Installed       ");
	  if(ser_p->activity == FREE)
		 strcat(buf, "Disconnected");
	  else
		 strcat(buf, "Connected");
	}
	else
	  strcpy(buf, "Not Installed  ");
 }
 D->GWPuts(7,14,buf,Lightgray,Black);
*/
 D->GWPuts(8,5,"Network",Lightgray,Black);
 strcpy(buf, "Not Installed");
 D->GWPuts(8,14,buf,Lightgray,Black);

 hide_pointer();
 Bordergr(48, 8, 58, 8, Black, Cyan, Lightgray, Black, 0, 1);
 if( panel_info1.panel_type==T3000 )
	Bordergr(47, 16, 63, 16, Black, Cyan, Lightgray, Black, 0, 1);
 display_pointer();
 D->GWPuts(1,34, " Notes ",Cyan,Black);
 if( panel_info1.panel_type==T3000 )
  D->GWPuts(9,33, " Update T3000 ",Cyan,Black);
 D->enter=1;
 if( panel_info1.panel_type==T3000 )
	 D->GDDef_object(pupdatet3000,31,9,14,Cyan,Black);
 D->GDDef_object(pinfoscreen,32,1,7,Cyan,Black);
 D->index_cur=0;

 keyboard_data=0;
 while(!D->HandleEvent());
 if(D) delete D;
}

void reinstallrs485(void)
{
/*
  if( ser_rs485 != NULL )
  {
	if( ser_rs485->port_status == NOT_INSTALLED )
		;
	//	  time_run_MSTP = 5000;
	else
	{
//	 validint = 0;
	 blocked( MSTP_MASTER );
	 blocked( SERVERTSM );
	 blocked( RS485_RECEIVEFRAME );
	 ser_rs485->Delete_port();
	 ser_rs485->Install_port();
	 blocked_suspended( RS485_RECEIVEFRAME );
	 blocked_suspended( SERVERTSM );
	 if( ser_rs485->port_status == NOT_INSTALLED )
		suspend(MSTP_MASTER);
	 else
	 {
//	  SilenceTimer=0;
		blocked_resume( MSTP_MASTER );
//	  validint = 1;
	 }
	}
	}
*/
}

void desinstalled_one(int j, int type=1)
{
 int k=0;
 unsigned long t;
 GWindow *D=NULL;
 if( (Routing_table[j].status&PTP_INSTALLED)==PTP_INSTALLED )
 {
//	router(N_UNITDATArequest, Initialize_Routing_Table, NULL, j,1);
//	router(N_UNITDATArequest, Initialize_Routing_Table, NULL, j,1);
	if( (Routing_table[j].status&PTP_ACTIVE)==PTP_ACTIVE )
	{
		 ((class PTP *)Routing_table[j].ptr)->NL_parameters.primitive = DL_DISCONNECT_REQUEST;
		 resume(((class PTP *)Routing_table[j].ptr)->task);
		 Delay(1000);
	}
	disable();
	tasks[((class PTP *)Routing_table[j].ptr)->task+6].status=DEAD;
	tasks[((class PTP *)Routing_table[j].ptr)->task+3].status=DEAD;
	tasks[((class PTP *)Routing_table[j].ptr)->task].status=DEAD;
	Routing_table[j].status = 0;
	delete (class PTP *)Routing_table[j].ptr;
	 memset(&Routing_table[j].port_status_vars,0,sizeof(PORT_STATUS_variables));
	enable();
	Routing_table[j].Port.address = 0;
	Routing_table[j].Port.network = 0;
 }
 if( (Routing_table[j].status&RS485_INSTALLED)==RS485_INSTALLED )
 {
	 unsigned int i;
	 int ts[3];
//	 router(N_UNITDATArequest, Initialize_Routing_Table, NULL, j);
//	 router(N_UNITDATArequest, Initialize_Routing_Table, NULL, j);
//	 delay(5000);
	 if(type)
	 {
		ts[0] = Routing_table[j].Port.address;
		ts[1] = ((class MSTP *)Routing_table[j].ptr)->OS;
		ts[2] = ((class MSTP *)Routing_table[j].ptr)->NS;
		i = 6;

//		refresh_time = 550;
//		while(tasks[NETTASK].status==SLEEPING && refresh_time);
		suspend(NETTASK);

		DisplayMessage(12, 10, 68, 14, NULL, "Wait to disconnect the ports...",&D);
		iwanttodisconnect = 1;
		net_call(COMMAND_50+100, SEND_INFO_COMMAND+(SENDINFO_IAMPANELOFF<<8), (char *)ts, &i, 255, Routing_table[j].Port.network, BACnetUnconfirmedRequestPDU|NETCALL_NOTTIMEOUT|NETCALL_SOURCE255,
						 TIMEOUT_NETCALL, NULL, NULL, NULL, 0, 0, j);
		refresh_time = 550;
		while( ((((class MSTP *)Routing_table[j].ptr)->SoleMaster) == FALSE) && !(((class MSTP *)Routing_table[j].ptr)->panelOff) && refresh_time );
		iwanttodisconnect = 0;
	 }
	 network_points_flag--;

//	 refresh_time = 550;
//	 while(tasks[NETTASK].status==SLEEPING && refresh_time);
	 suspend(NETTASK);
	 disable();
//
	 make_task((taskptr) nettask, stack_NETTASK, stack_NETTASK_SIZE, NETTASK);
//
	 tasks[((class MSTP *)Routing_table[j].ptr)->task].status=DEAD;
	 Routing_table[j].status = 0;
	 delete (class MSTP *)Routing_table[j].ptr;
	 memset(&Routing_table[j].port_status_vars,0,sizeof(PORT_STATUS_variables));
	 enable();
	 Routing_table[j].Port.address = 0;
	 Routing_table[j].Port.network = 0;
	 if(type)
//		if(timestart < t+7)
		if(refresh_time > 400)
		{
//		 delay((t+7-timestart)*1000);
		 delay(4000);
		}
	 if(D){ DeleteMessage(D); D=NULL;};
 }
 if( (Routing_table[j].status&ASYNCRON_INSTALLED)==ASYNCRON_INSTALLED )
 {
//	suspend(VIRTUAL);
	set_semaphore(&t3000_flag);
	disable();
	tasks[((class ASYNCRON *)Routing_table[j].ptr)->task].status=DEAD;
	Routing_table[j].status = 0;
	delete (class ASYNCRON *)Routing_table[j].ptr;
	memset(&Routing_table[j].port_status_vars,0,sizeof(PORT_STATUS_variables));
	enable();
	Routing_table[j].Port.address = 0;
	Routing_table[j].Port.network = 0;
	clear_semaphore(&t3000_flag);
//	resume(VIRTUAL);
 }
 memset( Routing_table[j].Port.networks_list, 0, sizeof(Routing_table[j].Port.networks_list));
}

void desinstalled(void)
{
 unsigned long t;
 int k=-1,i;
 router(N_UNITDATArequest, Initialize_Routing_Table, NULL, -1);
 router(N_UNITDATArequest, Initialize_Routing_Table, NULL, -1);
 delay(5000);

 rs485port=-1;
 ipxport  =-1;
 disconnect_serial(1);
 setlocalpanel();

// refresh_time = 550;
// while(tasks[NETTASK].status==SLEEPING && refresh_time);

 for(int j=0; j<MAX_Routing_table ; j++)
 {
	 if( (Routing_table[j].status&IPX_INSTALLED)==IPX_INSTALLED )
	 {
		 k = j;
#ifdef NET_BAC_COMM
	if( k>=0 )
	{
	 if( (Routing_table[k].status&IPX_INSTALLED)==IPX_INSTALLED )
	 {
		network_points_flag--;
		if( !NET_EXIT )
		{
		 NET_EXIT = 2;
		 refresh_time = 80;
		 while(!ipxfinished && refresh_time);
		}
		if( NET_EXIT== 1 )
		{
			resume(NETWORK1);
			task_switch();
			enable();
			while(pipx);
//			kill_task(NETWORK1);
		}
		if( pipx )
			pipx->port_state=0;
		Routing_table[k].status = 0;
		memset(&Routing_table[k].port_status_vars,0,sizeof(PORT_STATUS_variables));
		Routing_table[k].Port.address = 0;
		Routing_table[k].Port.network = 0;
    memset( Routing_table[k].Port.networks_list, 0, sizeof(Routing_table[k].Port.networks_list));
	 }
	}
#endif
	 }
	 else
		 desinstalled_one(j);
 }
}

int install_one_port(int i)
{
 int l, result, net;
 unsigned long t;
 char *buf;
 GWindow *D;
	l = -1;
	if(comm_info[i].connection!=0 && comm_info[i].connection!=MOUSE_LINK )
	{
	 for(int j=0; j<MAX_Routing_table ; j++)
	 {
		if(!Routing_table[j].status)
		{
		 if( comm_info[i].connection == RS485_LINK )
		 {
			DisplayMessage(12, 10, 68, 14, NULL, "Wait to install the RS485 port...",&D);
			Routing_table[j].ptr = new MSTP(i,j);
			if ( ((class MSTP *)Routing_table[j].ptr)->port_status == NOT_INSTALLED )
			{
				if(D){ DeleteMessage(D); D=NULL;};
				delete (class MSTP *)Routing_table[j].ptr;
				break;
			}
			iamnewonnet=1;
			Routing_table[j].Port.address = Station_NUM;
			Routing_table[j].Port.network = comm_info[i].NetworkAddress;
			((class MSTP *)Routing_table[j].ptr)->panel_info1.network = comm_info[i].NetworkAddress;
			((class MSTP *)Routing_table[j].ptr)->panel_info1.panel_number = Station_NUM;
//			((class PTP *)Routing_table[j].ptr)->port->isr_data->port_number = j;
//			((class PTP *)Routing_table[j].ptr)->port_number = j;
//			Routing_table[j].port_status_vars.connection = MSTP_DISCONNECTED;
			Routing_table[j].status = RS485_ACTIVE;
			for(int k=MSTP_MASTER; k<MSTP_MASTER+RS485TASKS; k++)
			{
			 if(tasks[k].status==DEAD)
			 {
				Routing_table[j].task = k;
				((class MSTP *)Routing_table[j].ptr)->task   = k;
				Routing_table[j].port_status_vars.task       = k;
				Routing_table[j].port_status_vars.connection = MSTP_CONNECTED;
				((class MSTP *)Routing_table[j].ptr)->port->isr_data->task = k;
//				make_task( (taskptr) MSTP::MSTP_receive_frame, stack_rs485_receive_frame, stack_rs485_receive_frame_SIZE, RS485_RECEIVEFRAME, Routing_table[j].ptr);
				make_task( (taskptr) MSTP::MSTP_Master_node, stack_MSTP_Master_node+(k-MSTP_MASTER)*stack_MSTP_Master_node_SIZE,
								stack_MSTP_Master_node_SIZE, k, Routing_table[j].ptr, j);
				((class MSTP *)Routing_table[j].ptr)->panelconnected = 0;
				net = comm_info[i].NetworkAddress;
				resume(k);
				refresh_time = 800;
				while( !((class MSTP *)Routing_table[j].ptr)->panelconnected && refresh_time );
				if(D){ DeleteMessage(D); D=NULL;};
				if(((class MSTP *)Routing_table[j].ptr)->panelconnected==1)
				{  // received network number
//				 if( net != ((class MSTP *)Routing_table[j].ptr)->panel_info1.network )
//				 {
					net = ((class MSTP *)Routing_table[j].ptr)->panel_info1.network;
					Routing_table[j].Port.network = net;
					for(int n1=0; n1<MAX_Routing_table ; n1++)
					{
					 if( Routing_table[n1].status )
					 {
						if( n1!=j && Routing_table[n1].Port.network==net )
						{
//            two ports with the same number
							desinstalled_one(j);
							j = -1;
							set_semaphore_dos();
							buf = new char [100];
							clear_semaphore_dos();
							strcpy(buf, "Port      not installed. There is another    port with the same network number!");
							memcpy(&buf[5], &com_buf[i+1], 4);
							DisplayMessage(18, 10, 62, 14, pressanykey, buf, NULL, Blue, NULL, 30000);
//							DisplayMessage(12, 10, 70, 14, NULL, buf,&D);
//							if(D){ DeleteMessage(D); D=NULL;};
							set_semaphore_dos();
							delete buf;
							clear_semaphore_dos();
							break;
						}
					 }
					}
//				 }
				}
				else
				{
				 if(((class MSTP *)Routing_table[j].ptr)->panelconnected==3)     // conflict
				 {
							desinstalled_one(j,0);
							j = -1;
							set_semaphore_dos();
							buf = new char [100];
							clear_semaphore_dos();
							strcpy(buf, portconfl1);
							memcpy(&buf[5], &com_buf[i+1], 4);
							DisplayMessage(22, 10, 66, 14, pressanykey, buf, NULL, Blue, NULL, 30000);
							set_semaphore_dos();
							delete buf;
							clear_semaphore_dos();
							break;
				 }
				}
				networkaddress=Routing_table[j].Port.network;
				ptr_panel->GlNetwork = networkaddress;
				break;
			 }
			}
			l=j;
			iamnewonnet=0;
//		  if(D){ DeleteMessage(D); D=NULL;};
			break;
		 }
		 else
		 {
			if( comm_info[i].connection == SERIAL_LINK || comm_info[i].connection == MODEM_LINK )
			{
			 DisplayMessage(12, 10, 68, 14, NULL, "Wait to install the serial port...",&D);
			 Routing_table[j].port_status_vars.connection = PTP_IDLE;
			 Routing_table[j].ptr = (class PTP *) new PTP(i,j);
			 if ( ((class PTP *)Routing_table[j].ptr)->port_status == NOT_INSTALLED )
			 {
				if(D){ DeleteMessage(D); D=NULL;};
				delete (class PTP *)Routing_table[j].ptr;
				break;
			 }
			 Routing_table[j].Port.address = 0;
			 Routing_table[j].Port.network = 0;
			 Routing_table[j].status = PTP_INSTALLED;
			 ((class PTP *)Routing_table[j].ptr)->init_idle_state(0);
			 ((class PTP *)Routing_table[j].ptr)->panel_info1.network = comm_info[i].NetworkAddress;
			 ((class PTP *)Routing_table[j].ptr)->panel_info1.panel_number = Station_NUM;
			 for(int k=PTP_CONNECTION; k<PTP_CONNECTION+RS232TASKS; k++)
			 {
				if(tasks[k].status==DEAD)
				{
				Routing_table[j].task = k;
				((class PTP *)Routing_table[j].ptr)->task = k;
				Routing_table[j].port_status_vars.task = k;
				((class PTP *)Routing_table[j].ptr)->port->isr_data->task = k;
				Routing_table[j].port_status_vars.rings_number = comm_info[i].rings;
//				((class PTP *)Routing_table[j].ptr)->port->isr_data->task = k+PTP_RECEIVEFRAME;
//				memset( &Routing_table[j].port_status_vars.PTP_comm_status, 0, 2 );
//				Routing_table[j].port_status_vars.PTP_comm_status.reception_blocked = Q_NOT_BLOCKED;
//				Routing_table[j].port_status_vars.PTP_comm_status.transmission_blocked = 1;
				make_task( (taskptr) PTP::PTP_connection_termination_state_machine, stack_PTP+(k-PTP_CONNECTION)*stack_PTP_SIZE, stack_PTP_CONNECTION_SIZE, k, Routing_table[j].ptr, j);
				make_task( (taskptr) PTP::PTP_reception_state_machine, stack_PTP+(k-PTP_CONNECTION)*stack_PTP_SIZE+stack_PTP_CONNECTION_SIZE, stack_PTP_RECEPTION_SIZE, k+PTP_reception, Routing_table[j].ptr);
//				make_task( (taskptr) PTP::PTP_receive_frame_state_machine, stack_PTP+(k-PTP_CONNECTION)*4096+1024+1024, 1024, k+PTP_RECEIVEFRAME, Routing_table[j].ptr);
				make_task( (taskptr) PTP::PTP_transmission_state_machine,  stack_PTP+(k-PTP_CONNECTION)*stack_PTP_SIZE+stack_PTP_CONNECTION_SIZE+stack_PTP_RECEPTION_SIZE, stack_PTP_TRANSMISSION_SIZE, k+PTP_transmission, Routing_table[j].ptr);
//				comm_info[i].port_num = j;
				break;
				}
			 }
			 if(D){ DeleteMessage(D); D=NULL;};
			 if(k<PTP_CONNECTION+RS232TASKS)
			 {
				if(comm_info[i].activate)
				{
				estab_text[strlen(estab_text)-5]=i+0x31;
				DisplayMessage(12, 10, 68, 14, ctrlbreak_text, estab_text,&D);
				if ( (result=net_call(50, ESTABLISH_CONNECTION_PORT, NULL, 0, i, 0xFFFF, NETCALL_NOTCHANGENETADR, 40) ) == SUCCESS )
				{
				 if(D){ DeleteMessage(D); D=NULL;};
				 DisplayMessage(20, 10, 60, 14, NULL, "Connection established.", NULL, Blue, NULL, 1200);
				}
				if(D){ DeleteMessage(D); D=NULL;};
				DIAL_checkconnection=1;
				DIAL_action=1;
				if( tasks[DIAL].status == SUSPENDED )
				 resume(DIAL);
				}
			 }
			 l=j;
			 break;
		  }
			else
			{
			if( comm_info[i].connection == ASYNCRON_LINK )
			{
       set_semaphore(&t3000_flag);
//			 suspend(VIRTUAL);
			 Routing_table[j].ptr = new ASYNCRON(i,j);
			 if ( ((class ASYNCRON *)Routing_table[j].ptr)->port_status == NOT_INSTALLED )
			 {
				delete (class ASYNCRON *)Routing_table[j].ptr;
				clear_semaphore(&t3000_flag);
//				resume(VIRTUAL);
				break;
			 }
			 Routing_table[j].Port.address = 0;
			 Routing_table[j].Port.network = 0;
			 Routing_table[j].status = ASYNCRON_INSTALLED;
			 if( comm_info[i].program_nr )
			 {
				((class ASYNCRON *)Routing_table[j].ptr)->program_number = comm_info[i].program_nr;
				ptr_panel->programs[comm_info[i].program_nr-1].com_prg=1;
			 }
			 for(int k=PTP_RECEPTION; k<PTP_RECEPTION+RS232TASKS; k++)
			 {
				if(tasks[k].status==DEAD)
				{
				 Routing_table[j].task = k;
				 ((class ASYNCRON *)Routing_table[j].ptr)->task = k;
				 Routing_table[j].port_status_vars.task = k;
				 ((class ASYNCRON *)Routing_table[j].ptr)->port->isr_data->task = k;
//				 make_task( (taskptr) ASYNCRON::ASYNCRON_task, stack_PTP+(k-PTP_CONNECTION)*stack_PTP_SIZE, stack_PTP_CONNECTION_SIZE, k, Routing_table[j].ptr, j);
				 make_task( (taskptr) ASYNCRON::ASYNCRON_task, stack_PTP+(k-PTP_RECEPTION)*stack_PTP_SIZE+stack_PTP_CONNECTION_SIZE, stack_PTP_RECEPTION_SIZE, k, Routing_table[j].ptr, j);
				 resume(k);
				 break;
				}
			 }
			 l=j;
			 clear_semaphore(&t3000_flag);
//			 resume(VIRTUAL);
			 break;
			}
			}
		 }
		}
	 }
	}
//	if(com>=0) break;
 return l;
}


int install_port(int com)
{
 int l,media;
 unsigned long t;
 GWindow *D;
 char buf[16];

 if( com>=0 && com<MAX_COM)
	 l = install_one_port(com);
 else
 {
	 suspend(NETTASK);
	 make_task((taskptr) nettask, stack_NETTASK, stack_NETTASK_SIZE, NETTASK);
	 network_points_flag = 0;
	 sendinfoflag = 0;

	 for(int i=0; i<MAX_COM; i++)
	 {
		if( comm_info[i].connection==SERIAL_LINK || comm_info[i].connection==MODEM_LINK ||
				comm_info[i].connection==ASYNCRON_LINK )
			l = install_one_port(i);
	 }
#ifdef NET_BAC_COMM

	if( IPX_enabled )
	{
		if( pipx==NULL )
		{
		 pipx = new IPX( &Panel_Info1, (byte)NETWORK1 );

		 if( pipx->state != DRIVER_INSTALLED )
		 {
			delete pipx;
			pipx = NULL;
		 }
		 else
		 {
			DisplayMessageT(20, 6, 60, 10, NULL, "  Network driver detected...", NULL, Blue, NULL, 1000);
		 }
		}
	}

	if( pipx != NULL )
	{
	 if(IPX_enabled)
	 {
		if( pipx->state == DRIVER_INSTALLED )
		{
			for(int j=0; j<MAX_Routing_table ; j++)
			{
				if( !Routing_table[j].status )
				{
					pipx->port_state=IPX_ACTIVE;
					pipx->port_number = j;
					Routing_table[j].ptr = pipx;
					Routing_table[j].Port.address = Station_NUM;
					Routing_table[j].Port.network = NetworkAddress;
					Routing_table[j].status = IPX_ACTIVE;
					Routing_table[j].task = NETWORK1;
					((ConnectionData*)Routing_table[j].ptr)->task_number = NETWORK1;
					Routing_table[j].port_status_vars.task = NETWORK1;
					Routing_table[j].port_status_vars.connection = IPX_CONNECTED;
					if( NET_EXIT==2 )
					{
					 memcpy(buf,pipx->station_list[pipx->panel_info1.panel_number-1].hard_name,16);
					 pipx->InitIPX();
					 pipx->initData( &Panel_Info1 );
					 memcpy(pipx->station_list[pipx->panel_info1.panel_number-1].hard_name,buf,16);
          }
					pipx->panelconnected = 0;
					break;
				}
			}
			NET_EXIT = 0;
			iamnewonnet=1;
			DisplayMessage(12, 12, 68, 16, NULL, "Wait to install the network port...",&D);
			resume(NETWORK1);
			task_switch();
			delay(5000);
			if(D){ DeleteMessage(D); D=NULL;};
			iamnewonnet=0;
			if(pipx->panelconnected)
			{    // there is another panel with the same number
			 if(pipx)
				 pipx->port_state=0;
			 Routing_table[j].status = 0;
			 memset(&Routing_table[j].port_status_vars,0,sizeof(PORT_STATUS_variables));
			 Routing_table[j].Port.address = 0;
			 Routing_table[j].Port.network = 0;
			 DisplayMessage(18, 10, 62, 14, pressanykey, " Network port not installed. Panel number     conflict. Change the panel number!", NULL, Blue, NULL, 30000);
			}
			else
			{ // ipx installed
			 network_points_flag++;
	     ipxport  = j;
			}
		}
	 }
	}
#endif
//  for(media=SERIAL_LINK; media<=RS485_LINK; media++)  //serial-modem-rs485
/*
	for(media=SERIAL_LINK; media<=ASYNCRON_LINK; media++)  //serial-modem-rs485
	{
	 for(int i=0; i<MAX_COM; i++)
	 {
		if( comm_info[i].connection==media )
			l = install_one_port(i);
	 }
	}
*/
	 delay(1000);
	 for(i=0; i<MAX_COM; i++)
	 {
		if( comm_info[i].connection==RS485_LINK )
			if( (l=install_one_port(i))!=-1 )
				rs485port=l;
	 }
	 if(rs485port!=-1)
	 {
		ready_for_descriptors=0x08;
	 }
 }
 return l;
}

int checkport(int com, int t=0)  //t=0 check for PTP_INSTALLED
																 //t=1 check for PORT_INSTALLED
{
	for(int i=0; i<MAX_Routing_table ; i++)
	{
		if( (Routing_table[i].status&PTP_INSTALLED) == PTP_INSTALLED )
		{
		if( ((class PTP *)Routing_table[i].ptr)->com_port==com )	break;
		}
		else
		if( (Routing_table[i].status&RS485_INSTALLED) == RS485_INSTALLED )
		{
		 if(t)
			if( ((class MSTP *)Routing_table[i].ptr)->com_port==com )	break;
		}
	}
	if(i>=MAX_Routing_table)
	{
	 return -1;
	}
	return i;
}


long aftolproc(char *avalue)
{
 long l;
 char *ptr;
 ptr = strrchr(avalue,'.');
 if(ptr)
 {
	 *ptr=0;
	 l=atoi(avalue)*1000L;
	 l+=atoi(ptr+1);
 }
 else
	 l=atoi(avalue)*1000L;
 return l;
}

float atofproc(char *avalue)
{
 return aftolproc(avalue)/1000;
}

