#define GGRAPH

#include <alloc.h>
#include <math.h>
#include <mem.h>
#include <dir.h>
#include <bios.h>
#include <stdlib.h>
#include <graphics.h>
#include <windows.h>
#include "t3000hlp.h"

#include "recstruc.h"
#include "_msdos.h"

/*#ifdef __cplusplus

	int max (int value1, int value2);

	int max(int value1, int value2)
	{
		return ( (value1 > value2) ? value1 : value2);
	}

#endif
//#define max(a,b)    (((a) > (b)) ? (a) : (b))
*/

#define  FORWARD  1
#define  BACK     0

#include "t3000def.h"
#include "mtkernel.h"
#include "vga12.h"
#include "xms.h"
#include "serial.h"

#include "ggrid.h"
#include "graph.h"
#include "rs485.h"

extern int mode_text;
extern int error_net;
//extern int networkaddress;

extern int line_style;
#define DOTTED 2
#define FILL 1

#define BUTON 1
#define INTRIND 2
#define BLACKCOLOR 4
#define WHITECOLOR 5
#define USERCOLOR 6

#define MAX_ENTRY_PIXTABLE 14
#define MAX_PIXTABLE 562

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
extern int Brown;
extern int Magenta;

extern int maxx;
extern int maxy;

extern int ipxport, rs485port;
extern byte serial_access;
extern unsigned read_mon_flag;

extern dig_range_form huge dig_range_array[];
extern an_range_form huge var_range_array[];
extern an_range_form huge out_range_array[];
extern an_range_form huge in_range_array[];

extern char station_name[NAME_SIZE];
extern int  station_num;

extern int simulator;
extern int local_panel;

extern Panel_info1 panel_info1;
extern char Station_NAME[NAME_SIZE];
extern int  Station_NUM;

extern char present_analog_monitor;
extern char GAlarm, gAlarm, GAlarmold;
extern int alarm_col;
extern int alarm_time;
extern char alarm_beep;

extern char huge *heap_amon;
extern Heap_dmon huge *heap_dmon;

extern unsigned int MAX_HEAP_AMON;
extern int xsign,ysign;
extern char showsign;
extern GWDialog *pm;
extern Panel *ptr_panel;

//extern GWindow *gauge;
extern void creategauge(GWindow **gauge, char *buf);
extern void deletegauge(GWindow **gauge);
extern void showgauge(GWindow *w, long coef, long ntot);

extern void set_PIC_RS485(void);
extern void reset_PIC_RS485(void);
extern void memsize(void);

extern char *lin_text;
extern char huge *lin_menu;
extern char huge *lin_hor;
extern char huge *lin_ver;
extern int dxscreen, dyscreen;

extern int extended_memory;
extern char nothing;
extern int int_dos;
extern char int_disk;

extern int local_request(int panel, int network);
void move_screen(int sx, int sy, int jx, int jy, int where, int size);
void msettextstyle(int font, int dir, int chars);
//extern char huge  des[MAX_DES];
//int savedes();
//int loaddes();

//#include "burstruct.h"
extern signed char point_des[AY+1];
extern int fground;

extern int lat_char_n;
extern int lung_char_n;
extern int font_type,charsize;

extern int refresh;
extern Point_Net amon_inputs[MAX_POINTS_IN_MONITOR];

extern unsigned first_free;
extern int MAX_HEAP_DIGM;

extern char graphsave;
extern char null_buf[10];
extern Pshape ARROW;
extern int bioskey_new(int cmd);
extern void dealloc_mem( char far **under1, char far **under2, char far **under3, char far **under4, int *flag);
extern void alloc_mem(int sx, int sy, int jx, int jy, char far **under1, char far **under2, char far **under3, char far **under4, int *flag);
extern void put_image(int sx, int sy, int jx, int jy, char far **under1, char far **under2, char far **under3, char far **under4, int *flag);
extern int pointtotext(char *buf,Point_Net *point);
extern int pointtotext(char *buf,Point_T3000 *point);
extern char *ispoint(char *token,int *num_point,byte *var_type, byte *point_type, int *num_panel, int *num_net, int network=0, byte panel=0, int *netpresent=0);
extern int	get_point_info(Point_info *point_info, char **des=NULL, char **label=NULL, char **ontext=NULL, char **offtext=NULL, char pri=0, int network = 0xFFFF);
extern void ftoa(float f, int length, int ndec, char *buf);
extern GWDialog *DisplayMessage(int lx, int ly, int rx, int ry, char *message,GWDialog **Er, int fcolor=Black);
extern void DeleteMessage(GWDialog *p);
extern void DisplayMessage(int lx, int ly, int rx, int ry, char *title, char *message, GWindow **Er1, int fcolor=Black, GWindow *Er2=NULL, long delay=0);
extern void DeleteMessage(GWindow *p);
extern char * intervaltotext(char *textbuf, long seconds , unsigned minutes , unsigned hours, char *c=":");
extern char *ltrim(char *text);
extern void chbkg(int lx, int ly, int width, int bkgnd, int frgnd, int unchangecol=127, int height = 0);
extern int Display_alarm(int);
extern int net_call(int command, int arg,  char *data, uint *length , int dest,
				 int network, int others=0, int timeout=TIMEOUT_NETCALL,
				 char *returnargs=NULL, int *length_returnargs=NULL,
				 char *sendargs=NULL, int length_sendargs=0, char bytearg=0, int port=-1);
extern size_t ffread(void *ptr, size_t size, size_t n, FILE *stream);
extern size_t ffwrite(const void *ptr, size_t size, size_t n, FILE * stream);

int readnettable(int ind, hot_box *viewport, int panel, int network);

long removebuf(long l1);
char *upreadmontable(int ind, int panel, int network, long *length, long &timeread, char direction, long **mon_table,
							Header_amon **pheaders, int &nheaders, int type, char *serptr=NULL);
long psample(long *interv, Str_monitor_point *amon);
void readtable(int ind, hot_box *viewports);
int movefile(char *label,long nsample, FILE **h);
long whatinterv(unsigned long *timefirstsample,unsigned long *timelastsample);
float readvalue(long l, int ind);
long readvalue(long l, int ind, int type);
int	scale(unsigned long timelastsample, hot_box *viewport);
int printrange(int topx,int topy, long time_first_sample, long time_last_sample, char *p);
int print_alarm_word(void);
int	updatemem(int ind, int panel, int network, int type=0);
char *newnetmem(int ind, int *, char * = NULL);
int	updatememdig(int ind, int panel, int network, int type=0 );

long readvaluedig(void);
unsigned readdigtable(int ind, long **dmon_table, int type=0);
int movefiledig(char *label,long nbytes,FILE **hh);
int newmem(int ind, int ssample, long ttime_last_sample, char *pmon_table, long **pmem_table, int *index_last_value, char *last_mem_block, int *nsample_mem_block, Header_amon *headers, int *ind_headers, int type=0);
int addmem(int ind, long interv, int sample, long time_last_sample, char *pmon_table, long **pmem_table, char *last_mem_block, int *nsample_mem_block, Header_amon *headers, int *ind_headers );
void setscale(hot_box *viewport);

int dialog_select(int n_entry, char *arraytext, int save, int x, int y, int bkgnd, int tbkgnd, char *title=NULL, char col=10);

extern char huge *ctrlbreak_text;
extern char huge *colon;
extern char modify_monitor;
extern unsigned long timesec1970, timestart;
extern int communication;

GWindow *gaugem;
int max_entry;

#define LX 8

struct FieldStruct huge array_g_struct[] =
		{
		{"NAME"   , 'N',0,10,0}
		}    ;

	union {
		int i;
		char ch[2];
		} key;

struct inputs_group {
		int n;
		char inputs[MAX_POINTS_IN_MONITOR];
//		float min,max;
		long min,max;
		char unit;
//		char units[MAX_POINTS_IN_MONITOR];
		} inputs_group[7];
int ind_inputs_group;

int num_monitors;
int current_mon;
Str_monitor_point *current_analog_mon;
Str_monitor_work_data *current_mon_workdata;
long time_last_sample;
long time_first_sample;
int index_last_sample;
long interv;
int sample;
signed char inputs_viewport[MAX_POINTS_IN_MONITOR];
signed char digital_inputs;
int First_sample;
int Last_sample;
unsigned long Time_last_sample;           // ,Time_last_screen;
unsigned long Time_first_sample;          //,Time_first_screen;
int FIRST_sample;
int LAST_sample;
unsigned long TIME_last_sample;
unsigned long TIME_first_sample;
char zoom, notscale;
int lxzoom,lyzoom,rxzoom,ryzoom;
int npixunit_ver, npixunit_hor;
//int first;
char view_name[41];
char (*array)[41];
//float *mon_table;
long *mon_table, *dmon_table;
HANDLE mon_table_handle, dmon_table_handle;
char *mem_dmon_table;
char save_monitor=0;
char save_monitor_command=0;
int MEM_sample;
int TOTAL_sample;
int file_sample;
char *ext=".MON";
char til='~';
long amon_file_length=40000L; //1500; //40000L;
long dmon_file_length=20000L;  //400 ; //20000L;
//static FILE *h1;
char many_blocks=0;
Header_amon *headers;
Header_dmon *headers_dig;
int ind_headers, ind_headers_dig;
long interval,lastinterval;
long timerange,TIMErange;
char huge array_timerange_custom[][11]={{" minutes  "},{"  hours   "},{"  days    "},{"  months  "}};
char huge array_timerange[][11]={{" 1 hour   "},{"  4 hours "},{"  1 day   "},{"  4 days  "},{"  custom  "},{"  maxim   "}};
char huge *numberof="    Number of ";
char huge *timerangetext_mo = " Mo: ";
char huge *timerangetext_days = " Days: ";
char huge *timerangetext_hours = " Hours: ";
char huge *timerangetext_min = " Min: ";
long refresh_graph_time;
char last_mem_block;
int nsample_mem_block;
long *pmem_table;
long time_last_sample_mem;
char cy_pix_unit;
char cx_pix_unit;
char cxy_pix_unit;
int (*pix_table)[MAX_ENTRY_PIXTABLE][MAX_PIXTABLE];
HANDLE pix_table_handle;
long ltime;
char justsavemem;
double npix_sample_hor;
int i_read,i_read_dig;
int j_read,j_read_dig,k_read_dig;
long time_sample_last_read;
int xlast;
char refresh_graph_mode;
char save_monitor_status;
int index_last_value;

int	nsample_mem_dig_block;
int nsample_mem_dig;
int nsample_mem_dig_mon[MAX_ANALM];
int IND;
long TIME_READVALUE_DIG,TIMESAMPLE,TIMEFIRSTNEXTHEADER;
int ONOFF;
char	init_heap_dmon;

float value_read;
long value1_read,value2_read;
long l2_read,l1_read,timefirst_read;
long timesample_read;
unsigned dgtimelast;
long analtime;
int nr_mon_save;
char local_graph;
//char disk_accessed;
FILE *hmove;

long galarm_read_time;
char updatedtime;

struct point_info_table {
		Point_info point_info;
		char *ontext;
		char *offtext;
		} point_info_table[MAX_POINTS_IN_MONITOR];

/********Functii auxiliare**************************/

extern char *rtrim(char *text);

/********Constructor***************/
#pragma option -Z

GGraph::GGraph( int lx, int ly, int rx, int ry, int stk, int ppanel, int net, int l)
							:GWDialog(lx,ly,rx,ry,stk,0)  // constructor (the same as GView)
{
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.055  ********
// ********       begin       ********
// ***********************************
	Flag_help=IMPOTENT;
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.055  ********
// ********        end        ********
// ***********************************
	int j=0;
	panel = ppanel;
	network = net;
	local = l;
	local_graph = l;
	onoff=0;
	for(int i=0;i<MAX_POINTS_IN_MONITOR;i++)
	 {
		ptablex[i]=0;
		ptabley[i]=0;
	 }
	color[0]=9;
	color[1]=10;
	color[2]=11;
	color[3]=12;
	color[4]=13;
	color[5]=14;
	color[6]=6;
	color[7]=3;
	color[8]=2;
	color[9]=4;
	color[10]=5;
	color[11]=7;
	color[12]=1;
	color[13]=8;

	viewport=0;
	nviewports=1;

	big_viewport.top.x=ltop.x+4;
	big_viewport.top.y=ltop.y+16+12;
	big_viewport.bot.x=rbottom.x-4;
	big_viewport.bot.y=rbottom.y-47;

	big.top.x=big_viewport.top.x+56;
	big.top.y=big_viewport.top.y+12;
	big.bot.x=big_viewport.bot.x-8;
	big.bot.y=big_viewport.bot.y-26;

	for(i=0;i<10;i++)
	{
	 viewports[i].top.x=big_viewport.top.x+56;
	 viewports[i].top.y=big_viewport.top.y+12;
	 viewports[i].bot.x=big_viewport.bot.x-8;
	 viewports[i].bot.y=big_viewport.bot.y-26;
	}
	int x=ltop.x+9;
	for(i=0;i<7;i++)
	 {
		Label[i].top.x = x; Label[i].bot.x = x+66;
		Label[i].top.y = rbottom.y-37; Label[i].bot.y= Label[i].top.y+13;
		Label[i+7].top.x = x; Label[i+7].bot.x = x+66;
		Label[i+7].top.y = Label[i].bot.y+4; Label[i+7].bot.y= Label[i+7].top.y+13;
		x += 90;
	 }
//	hot_box Zoom_out;
//	hot_box Zoom_in;
//	hot_box Left;
//	hot_box Right;
//	hot_box Label[16];
	Exit.top.x=ltop.x+12;	Exit.bot.x=Exit.top.x+34;
	Exit.top.y=ltop.y+4+4;	Exit.bot.y=Exit.top.y+12;
	View.top.x=Exit.bot.x+8;	View.bot.x=View.top.x+34;
	View.top.y=Exit.top.y;	View.bot.y=Exit.bot.y;
	Save.top.x=View.bot.x+8;	Save.bot.x=Save.top.x+34;
	Save.top.y=View.top.y;	Save.bot.y=View.bot.y;
	Delete.top.x=Save.bot.x+8;	Delete.bot.x=Delete.top.x+50;  //90
	Delete.top.y=View.top.y;	Delete.bot.y=View.bot.y;
	Reset.top.x=Delete.bot.x+8;	Reset.bot.x=Reset.top.x+42;
	Reset.top.y=View.top.y;	Reset.bot.y=View.bot.y;
	Timerange.top.x=Reset.bot.x+8;	Timerange.bot.x=Timerange.top.x+74;
	Timerange.top.y=View.top.y;	Timerange.bot.y=View.bot.y;

	Left.top.x=Timerange.bot.x+40;	Left.bot.x=Left.top.x+25;
	Left.top.y=View.top.y;	Left.bot.y=View.bot.y;
	Right.top.x=Left.bot.x+8;	Right.bot.x=Right.top.x+25;
	Right.top.y=View.top.y;	Right.bot.y=View.bot.y;
	Zoomout.top.x=Right.bot.x+8;	Zoomout.bot.x=Zoomout.top.x+33;
	Zoomout.top.y=View.top.y;	Zoomout.bot.y=View.bot.y;
	Zoomin.top.x=Zoomout.bot.x+8;	Zoomin.bot.x=Zoomin.top.x+33;
	Zoomin.top.y=View.top.y;	Zoomin.bot.y=View.bot.y;

	Zoomoutint.top.x=Zoomin.bot.x+8;	Zoomoutint.bot.x=Zoomoutint.top.x+33;
	Zoomoutint.top.y=View.top.y;	Zoomoutint.bot.y=View.bot.y;
	Up.top.x=Zoomoutint.bot.x+8;	Up.bot.x=Up.top.x+25;
	Up.top.y=View.top.y;	Up.bot.y=View.bot.y;
	Down.top.x=Up.bot.x+8;	Down.bot.x=Down.top.x+25;
	Down.top.y=View.top.y;	Down.bot.y=View.bot.y;

	for(i=0;i<MAX_POINTS_IN_MONITOR;i++)
	 inputs_viewport[i]=-1;

	digital_inputs = 0;
	memset(inputs_group,0,sizeof(inputs_group));
	ind_inputs_group=0;
	zoom =0;
	first = 0;
	mon_table=0;
	dmon_table=0;
	mon_table_handle=0;
	dmon_table_handle=0;
	headers = 0;
	headers_dig = 0;
   ind_headers = ind_headers_dig = justsavemem = 0;
	timerange=TIMErange=3600L*24L;
	status = SUCCESS;
	npix_sample=0;
//mfarmalloc((char far **)&pix_table, MAX_ENTRY_PIXTABLE*MAX_PIXTABLE*2,1);
//memsize();
	mfarmalloc((char far **)&pix_table, MAX_ENTRY_PIXTABLE*MAX_PIXTABLE*2,pix_table_handle);
//memsize();
	memset(pix_table, 0 , MAX_ENTRY_PIXTABLE*MAX_PIXTABLE*2);
	memcpy(array_struct, array_g_struct, sizeof(array_g_struct));
	memset(point_info_table, 0, MAX_POINTS_IN_MONITOR*sizeof(struct point_info_table));
	linex=0;liney=0;
	set_semaphore_dos();
	ulinex=(char far *) farmalloc((unsigned long)1024);
	clear_semaphore_dos();
};

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.056  ********
// ********       begin       ********
// ***********************************
GGraph::GGraph( int flag_help,char *need_help,int lx, int ly, int rx, int ry, int stk, int ppanel, int net, int l)
							:GWDialog(lx,ly,rx,ry,stk,0)  // constructor (the same as GView)
{
	Flag_help=flag_help;
	GGraph( lx, ly, rx, ry, stk, ppanel, net, l);
};
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.056  ********
// ********        end        ********
// ***********************************

int put_button(int x,	int y, char *text, int dx, int dy, int bkgnd, int frgnd,int how)
{
 char c;
 char *pc;
 int w=White;
 int b=Black;

// set_semaphore(&screen);
 setfillstyle(SOLID_FILL, bkgnd);
 bar(x,	y, x+dx,y+dy);
 if(how==INTRIND) {w=Black;b=White;};
 if(how==WHITECOLOR) {b=White;};
 if(how==BLACKCOLOR) {w=Black;};
 if(how==USERCOLOR) {w=frgnd;b=frgnd;};
 moveto(x+dx,y);
 setcolor(w);
 lineto(x,y);
 lineto(x,y+dy);
 setcolor(b);
 lineto(x+dx,y+dy);
 lineto(x+dx,y);

 setcolor(frgnd);
 moveto(x+3,y+4);
 if(text)
 if((pc=strchr(text,til)))
 {
	*pc=0;
	outtext(text);
	*(pc++)=til;
	c = *(pc+1);
	*(pc+1)=0;
	setcolor(White);
	outtext(pc);
	setcolor(frgnd);
	*(++pc) = c;
	outtext(pc);
 }
 else
	 outtextxy(x+3,y+4,text);
 // clear_semaphore(&screen);
}

void GGraph::GShowGraph(int vspot)
{
 char buf[10],*p;
 int i,r,j;
 char lit[2]={'A',0};
 hide_pointer();
 GShowWindow(vspot);
 hide_pointer();
 put_button(big_viewport.top.x,	big_viewport.top.y,NULL,big_viewport.bot.x-big_viewport.top.x+1,big_viewport.bot.y-big_viewport.top.y+1,Black,Green,USERCOLOR);
// set_semaphore(&screen);
 setfillstyle(SOLID_FILL, Lightgray);
 bar(ltop.x+1, ltop.y+1, rbottom.x-1, ltop.y+10);
// clear_semaphore(&screen);
 put_button(tx+4,	ltop.y+4,NULL,bx-tx-7,21,Lightgray,Black,INTRIND);

 put_button(Exit.top.x,	Exit.top.y,"e~Xit",36,14,Lightgray,Black,BUTON);
 put_button(View.top.x,	View.top.y,"~Load",36,14,Lightgray,Black,BUTON); //76
 put_button(Save.top.x,	Save.top.y,"~Save",36,14,Lightgray,Black,BUTON);
 put_button(Delete.top.x,	Delete.top.y,"~Delete",52,14,Lightgray,Black,BUTON);
 put_button(Reset.top.x,	Reset.top.y,"~Reset",44,14,Lightgray,Black,BUTON);
 put_button(Timerange.top.x,	Timerange.top.y,"~Time base",76,14,Lightgray,Black,BUTON);

 put_button(Left.top.x,	Left.top.y,"  ",28,14,Lightgray,Black,BUTON);
 put_button(Right.top.x,	Right.top.y,"  ",28,14,Lightgray,Black,BUTON);
// put_button(Zoomout.top.x,	Zoomout.top.y,"  ",36,14,Lightgray,Black,BUTON);
 put_button(Zoomout.top.x,	Zoomout.top.y,"    ",36,14,Lightgray,Black,BUTON);

// put_button(Zoomin.top.x,	Zoomin.top.y,"  ",36,14,Lightgray,Black,BUTON);
 put_button(Zoomin.top.x,	Zoomin.top.y,"    ",36,14,Lightgray,Black,BUTON);
 put_button(Zoomoutint.top.x,	Zoomout.top.y,"    ",36,14,Lightgray,Black,BUTON);

 // set_semaphore(&screen);
 outtextxy(Zoomout.top.x+20-3,Zoomout.top.y+7-3,"+");
 circle(Zoomout.top.x+20,Zoomout.top.y+7,5);
 moveto(Zoomout.top.x+20-5,Zoomout.top.y+6+2);
 lineto(Zoomout.top.x+20-11,Zoomout.top.y+6+4);


 outtextxy(Zoomin.top.x+20-3,Zoomin.top.y+7-3,"-");
 circle(Zoomin.top.x+20,Zoomin.top.y+7,5);
 moveto(Zoomin.top.x+20-5,Zoomin.top.y+6+2);
 lineto(Zoomin.top.x+20-11,Zoomin.top.y+6+4);

 circle(Zoomoutint.top.x+20,Zoomoutint.top.y+7,5);
 moveto(Zoomoutint.top.x+20-5,Zoomoutint.top.y+6+2);
 lineto(Zoomoutint.top.x+20-11,Zoomoutint.top.y+6+4);
 // clear_semaphore(&screen);


/*
 put_button(Up.top.x,	Up.top.y,"  ",28,14,Lightgray,Black,BUTON);
 put_button(Down.top.x,	Down.top.y,"  ",28,14,Lightgray,Black,BUTON);
*/

 put_button(tx+4,	Label[0].top.y-5,NULL,bx-tx-7,38,Lightgray,Black,INTRIND);
 for(i=0;i<MAX_POINTS_IN_MONITOR;i++)
 {
	byte var_type, point_type;
	int num_net,num_point, num_panel;
	pointtotext(buf,&amon_inputs[i]);
	p=ispoint(rtrim(buf),&num_point,&var_type, &point_type, &num_panel, &num_net, network, panel);
//	put_button(Label[i].top.x,	Label[i].top.y,(p?p:""),64,13,(strlen(p)?color[i]:Lightgray),Black,BUTON);
	put_button(Label[i].top.x,	Label[i].top.y,(p?p:NULL),64,13,Lightgray,Black,BUTON);
	// set_semaphore(&screen);
	setcolor(color[i]);
	if(i>=9)
	{
	 outtextxy(Label[i].bot.x+2,Label[i].top.y+3,lit);
	 lit[0]++;
	}
	else
	 outtextxy(Label[i].bot.x+2,Label[i].top.y+3,itoa(i+1,buf,10));
	// clear_semaphore(&screen);

 }
//// put_button(big_viewport.top.x-4,	big_viewport.top.y-4,NULL,big_viewport.bot.x-big_viewport.top.x+1+8,
////						big_viewport.bot.y-big_viewport.top.y+1+8,Lightgray,Black,USERCOLOR);
// put_button(big_viewport.top.x,	big_viewport.top.y,NULL,big_viewport.bot.x-big_viewport.top.x+1,big_viewport.bot.y-big_viewport.top.y+1,Black,Green,USERCOLOR);
//set_semaphore(&screen);
 setfillstyle(SOLID_FILL, Black);
//// clear_semaphore(&screen);
// put_button(big_viewport.top.x,	big_viewport.top.y,big_viewport.bot.x,big_viewport.bot.y,"",Black,Green,USERCOLOR);
 GWindow *D;
 DisplayMessage(200, 150, 500, 204, ctrlbreak_text," Reading data...   ",&D);

	 char *des,*label;
	if( !local )
	{
/*
	 if( net_call(READPOINTINFOTABLE_T3000, current_mon, (char *)point_info_table, 0, panel, network) )
	 {
		DeleteMessage(D);
		display_pointer();
		return;
	 }
*/
	 for(i=0;i<MAX_POINTS_IN_MONITOR;i++)
	 {
		 point_info_table[i].point_info.units=current_analog_mon->range[i];
		 if(i<current_analog_mon->anum_inputs)
				point_info_table[i].point_info.digital_analog = 1;
		 else
				point_info_table[i].point_info.digital_analog = 0;
	 }
	}
	for(i=0;i<MAX_POINTS_IN_MONITOR;i++)
	 if(!amon_inputs[i].zero())
	 {
		 if(local)
		 {
			point_info_table[i].point_info.point=amon_inputs[i];
			status=get_point_info(&point_info_table[i].point_info, &des, &label, &point_info_table[i].ontext, &point_info_table[i].offtext,local,network);
		 }
		 else
		 {
			r=point_info_table[i].point_info.units;
			if( !point_info_table[i].point_info.digital_analog )
			{
			 j=dig_range_array[r].value % 2;
			 point_info_table[i].ontext= &(dig_range_array[r].dunits[!j][0]);
			 point_info_table[i].offtext= &(dig_range_array[r].dunits[j][0]);
			}
		 }
	 }

// if(station_num != Station_NUM)
 if(!local)
 {
	 status=readnettable(current_mon, viewports, panel, network);
 }
 else
	 readtable(current_mon,viewports);

 if(status)
 {
	Delay(2000);
	DeleteMessage(D);
	display_pointer();
	return;
 }
// if(ptr_panel->analog_mon[current_mon-1].ind_views)
 if(current_analog_mon->ind_views)
	 timerange = TIMErange = current_analog_mon->views[0].timerange;
 if(current_analog_mon->ind_views)
 {
	for(int j=0;j<MAX_POINTS_IN_MONITOR;j++)
	 if(current_analog_mon->views[0].onoff & (1<<j))
		 drawpoint(j);
 }
 else
	for(int j=0;j<current_analog_mon->num_inputs;j++)
	 drawpoint(j);

 scale(TIME_last_sample, &viewports[0]);

/*
 if(sample)
 {
	drawgrid(sample, interv, 0);
	drawver();
 }
*/
DeleteMessage(D);
drawall();
psample(&interv, current_analog_mon);
refresh_graph_time = interv*18+40;
display_pointer();

}

// where=1 all table
int minmax(int where, int ind,long *min, long *max)
{
 asm push es;
 long value;
 long timefirst;
 int nsample;
 if(interval)
 {
	timefirst = Time_first_sample;
	nsample = (TIME_last_sample - TIME_first_sample)/interval;
	Time_first_sample = TIME_last_sample - nsample*interval;
	if(Time_first_sample < TIME_first_sample) Time_first_sample = TIME_first_sample;
	for(int i=0;i<(where?nsample:Last_sample);i++)
	{
	 value = readvalue(i, ind, 1);
	 if(value!=-10000000L)
	 {
		if(value<*min)
			if(value>-100000L) *min=value;
		if(value>*max)
			if(value<1000000L) *max=value;
	 }
	}
	Time_first_sample = timefirst;
 }
asm pop es;
}

int GGraph::drawver()
{
 char buf[10];
 long min,max;
 float npix_s;
//!! long *t;
 int m,v,dxw,dyw,dxv,dyv,l,xminw,xmaxw,yminw,ymaxw,xminv,yminv,npixunit,nunit;
//!! t=mon_table;
// t = (float *)ptr_panel->analog_mon[current_mon-1].data_segment;
 dyv=viewports[0].bot.y-viewports[0].top.y;

 min = 10000000L;
 max = -10000000L;
 v=0;
 for(int i=0;i<ind_inputs_group;i++)
	if(inputs_group[i].n>v)
		{
		 m=i;
		 v=inputs_group[i].n;
		}
 if(v)
 {
	if(inputs_group[m].min!=10000000L)
	{
	 min=(inputs_group[m].min-1000)/1000;
	 max=(inputs_group[m].max+1000)/1000;
	}
 }

 if(min == 10000000L)
	npixunit = 32;
 else
 {
  yminw = min;
  ymaxw = max;
  if(yminw%5) yminw = ((int)(yminw/5)-(yminw<0?1:0) ) * 5;
  if(ymaxw%5) ymaxw = ((int)(ymaxw/5)+1) * 5;
	if(max - ymaxw > 0 && max - ymaxw < 1) ymaxw++;
	 if(yminw == ymaxw)
	 {
		yminw -= 5;
		ymaxw += 5;
	 }
  dyw = ymaxw-yminw;
// setcolor(color[ind]);
  npix_s = (float)dyv/(float)dyw;

  if(zoom)
  {
		min = ryzoom/npix_s + yminw;
		max = lyzoom/npix_s + yminw;
		yminw = min;
		ymaxw = max;
		if(yminw%5) yminw = ((int)(yminw/5)-(yminw<0?1:0) ) * 5;
		if(ymaxw%5) ymaxw = ((int)(ymaxw/5)+1) * 5;
		if(max - ymaxw > 0 && max - ymaxw < 1) ymaxw++;
		if(yminw == ymaxw)
		{
			yminw -= 5;
			ymaxw += 5;
		}
		dyw = ymaxw-yminw;
		npix_s = (float)dyv/(float)dyw;
  }
  nunit = (float)dyw / 7 ;
  if((l=nunit%5) == 0 || l==1 || l==2) l=0;
  else  l=1;
  nunit = (nunit/5+l)*5;
  if(!nunit) nunit=5;

  npixunit = (int)(nunit * npix_s+0.5);
  if(npixunit<40)
  {
		nunit *= 2;
		npixunit = (int)(nunit * npix_s+0.5);
  }
  if(npixunit_ver == npixunit && cx_pix_unit)
  {
//			cy_pix_unit = 1;
			cxy_pix_unit = 1;
  }
  else
  {
//			cy_pix_unit = 0;
			cxy_pix_unit = 0;
			if(cx_pix_unit)
			 {
				cx_pix_unit = 0;
				drawgrid(sample, interval, time_first_sample);
			 }
  }
  npixunit_ver = npixunit;
  cx_pix_unit = 1;

//	bar(big_viewport.top.x,	viewports[0].top.y-4,viewports[0].top.x-1,viewports[0].bot.y+4);
 }

 hide_pointer();
 line_style = DOTTED;
 int j=0;
// set_semaphore(&screen);
 for(i=(int)viewports[0].bot.y;i>=(int)viewports[0].top.y;i-=npixunit)
 {
//		if(!cy_pix_unit)
//		{
		 pline(viewports[0].top.x,i,viewports[0].bot.x,i,Lightgray);
		 line_style = FILL;
		 pline(viewports[0].top.x-4,i,viewports[0].top.x+4,i,White);
		 line_style = DOTTED;
//		}
		if(min!=10000000L)
		{
		 if(dyw>1)
			 itoa(yminw, buf, 10);
		 else
			 ftoa(yminw, 5, 1, buf);
		 setcolor(color[inputs_group[m].inputs[0]]);
		 if(i-5 < (int)viewports[0].top.y) i=i+5;
		 set_semaphore(&screen);
		 outtextxy( viewports[0].top.x-(strlen(buf)+1)*8,i-4,buf);  //48
		 clear_semaphore(&screen);
		 yminw += nunit;
		}
 }
 if(v)
 {
		set_semaphore(&screen);
/*
		switch (amon_inputs[inputs_group[m].inputs[0]].point_type-1){
			case OUT:
				 outtextxy(viewports[0].top.x-48,viewports[0].top.y-10,out_range_array[inputs_group[m].unit].aunits);
				 break;
			case IN:
				 outtextxy(viewports[0].top.x-48,viewports[0].top.y-10,in_range_array[inputs_group[m].unit].aunits);
				 break;
			case VAR:
				 outtextxy(viewports[0].top.x-48,viewports[0].top.y-10,var_range_array[inputs_group[m].unit].aunits);
				 break;
		}
*/
		outtextxy(viewports[0].top.x-48,viewports[0].top.y-10,var_range_array[inputs_group[m].unit].aunits);
		clear_semaphore(&screen);
		for(i=0;i<inputs_group[m].n;i++)
		{
			setfillstyle(SOLID_FILL, color[inputs_group[m].inputs[i]]);
			bar(viewports[0].top.x-(i+2)*8,viewports[0].bot.y-24,viewports[0].top.x-(i+1)*8,viewports[0].bot.y-12);
//			outtextxy(viewports[0].top.x-(i+2)*8,viewports[0].bot.y-16,"Û");
		}
 }
// clear_semaphore(&screen);
 v=1;
 if(min!=10000000L)
 {
  setfillstyle(SOLID_FILL, Black);
  bar(big_viewport.top.x+1, big_viewport.top.y+1, viewports[0].top.x-56, viewports[0].bot.y+4);
  for(i=0;i<ind_inputs_group;i++)
  {
	if(i!=m)
	{
	 min=(inputs_group[i].min-1000)/1000;
	 max=(inputs_group[i].max+1000)/1000;
	 yminw = min;
	 ymaxw = max;
	 if(yminw%5) yminw = ((int)(yminw/5)-(yminw<0?1:0) ) * 5;
	 if(ymaxw%5) ymaxw = ((int)(ymaxw/5)+1) * 5;
	 if(max - ymaxw > 0 && max - ymaxw < 1) ymaxw++;
	 if(yminw == ymaxw)
	 {
		yminw -= 5;
		ymaxw += 5;
	 }
	 dyw = ymaxw-yminw;
// setcolor(color[ind]);
	 npix_s = (float)dyv/(float)dyw;

	 if(zoom)
	 {
		min = ryzoom/npix_s + yminw;
		max = lyzoom/npix_s + yminw;
		yminw = min;
		ymaxw = max;
		if(yminw%5) yminw = ((int)(yminw/5)-(yminw<0?1:0) ) * 5;
		if(ymaxw%5) ymaxw = ((int)(ymaxw/5)+1) * 5;
		if(max - ymaxw > 0 && max - ymaxw < 1) ymaxw++;
		if(yminw == ymaxw)
		{
		 yminw -= 5;
		 ymaxw += 5;
		}
		dyw = ymaxw-yminw;
		npix_s = (float)dyv/(float)dyw;
	 }
	 nunit = (float)dyw / 7 ;
	 if((l=nunit%5) == 0 || l==1 || l==2) l=0;
	 else  l=1;
	 nunit = (nunit/5+l)*5;
	 if(!nunit) nunit=5;

	 npixunit = (int)(nunit * npix_s+0.5);
	 if(npixunit<40)
	 {
		nunit *= 2;
		npixunit = (int)(nunit * npix_s+0.5);
	 }
//!!	 npixunit_ver = npixunit;

	 hide_pointer();
	 set_semaphore(&screen);
	 setcolor(color[inputs_group[i].inputs[0]]);
	 for(j=(int)viewports[0].bot.y;j>=(int)viewports[0].top.y;j-=npixunit)
	 {
		pline(viewports[0].top.x-4,j,viewports[0].top.x+4,j,color[inputs_group[i].inputs[0]]);
		if(dyw > 1)
			itoa(yminw, buf, 10);
		else
			ftoa(yminw, 5, 1, buf);
		if(j-5 < (int)viewports[0].top.y) j=j+5;
		outtextxy( viewports[0].top.x-(v*56)-(strlen(buf)+1)*8,j-4,buf);    //48
		yminw += nunit;
	 }
/*
	 switch (amon_inputs[inputs_group[i].inputs[0]].point_type-1){
			case OUT:
				 outtextxy(viewports[0].top.x-(v*56)-48,viewports[0].top.y-10,out_range_array[inputs_group[i].unit].aunits);
				 break;
			case IN:
				 outtextxy(viewports[0].top.x-(v*56)-48,viewports[0].top.y-10,in_range_array[inputs_group[i].unit].aunits);
				 break;
			case VAR:
				 outtextxy(viewports[0].top.x-(v*56)-48,viewports[0].top.y-10,var_range_array[inputs_group[i].unit].aunits);
				 break;
	 }
*/
	 outtextxy(viewports[0].top.x-(v*56)-48,viewports[0].top.y-10,var_range_array[inputs_group[i].unit].aunits);
	 for(j=0;j<inputs_group[i].n;j++)
	 {
		setfillstyle(SOLID_FILL, color[inputs_group[i].inputs[j]]);
		bar(viewports[0].top.x-(v*56)-(j+2)*8,viewports[0].bot.y-24,viewports[0].top.x-(v*56)-(j+1)*8,viewports[0].bot.y-12);
//		outtextxy(viewports[0].top.x-(v*56)-(j+2)*8,viewports[0].bot.y-16,"Û");
	 }
	 clear_semaphore(&screen);
	 v++;
	}
	}
 }
// clear_semaphore(&screen);
 int k;
 for(i=0;i<MAX_POINTS_IN_MONITOR;i++)
	if((k=inputs_viewport[i])>0)
		{
//		 Point_info point_info;
//		 char *des,*label,*ontext,*offtext;
//		 memcpy(&point_info.point_name,&amon_inputs[i],2);
//		 get_point_info(&point_info, &des, &label, &ontext, &offtext);

		 set_semaphore(&screen);
		 setcolor(color[i]);
		 if(point_info_table[i].ontext)
			 outtextxy(viewports[k].top.x-(strlen(point_info_table[i].ontext))*8-1,viewports[k].top.y-1, point_info_table[i].ontext);
		 if(point_info_table[i].offtext)
			 outtextxy(viewports[k].top.x-(strlen(point_info_table[i].offtext))*8-1,viewports[k].bot.y-6, point_info_table[i].offtext);
		 clear_semaphore(&screen);
		}

 line_style = FILL;
// set_semaphore(&screen);
 pline(viewports[0].top.x,viewports[0].bot.y,viewports[0].bot.x,viewports[0].bot.y,White);
// clear_semaphore(&screen);
 display_pointer();

}

#pragma option -Z-

int GGraph::drawgrid(int sample, long interv,long first_sample)
{
	char b[30];
	char *buf=b;
	int dxv=viewports[0].bot.x-viewports[0].top.x;
	int dyv=viewports[0].bot.y-viewports[0].top.y;
	npix_sample_hor  = npix_sample;  //val anterioara
	npix_sample = (double)dxv/(double)(sample-1);
	if( (npix_sample > npix_sample_hor) && npix_sample_hor && !justsavemem && !notscale)
	{
//	 justsavemem = 0;
	 npix_sample = npix_sample_hor = 0;
	 setscale(viewports);
	 npix_sample = (double)dxv/(double)(sample-1);
	 cxy_pix_unit = cx_pix_unit = 0;
	}
	notscale=0;
	long time_sample = first_sample;
	nsample_unit = (int)((double)80./npix_sample) + 1;
	npix_unit = (int)(nsample_unit * npix_sample+0.5);
//	Last_sample = First_sample + (int)((float)dxv/npix_sample);
	Last_sample = sample -1 ;
	if(Last_sample > LAST_sample) Last_sample = LAST_sample;
	hide_pointer();

	setfillstyle(SOLID_FILL, Black);
//	if(npixunit_hor==npix_unit && cy_pix_unit)
	if(cx_pix_unit)
	{
//		cx_pix_unit = 1;
		bar(big.top.x-20,	big.bot.y+6,big.bot.x+8,big.bot.y+24); // scriu scala x
	}
	else
	{
//		cx_pix_unit = 0;
		bar(big_viewport.top.x+1, big_viewport.top.y+1, big_viewport.bot.x-1, big_viewport.bot.y-1);
	}
 int j=1;
 if(digital_inputs)
	{
	 for(int i=0; i<MAX_POINTS_IN_MONITOR; i++)
	 {
		if(inputs_viewport[i] > 0)
		 {
			 bar(viewports[j].top.x+1, viewports[j].top.y, viewports[j].bot.x-1, viewports[j].bot.y);
			 j++;
		 }
	 }
	}
// set_semaphore(&screen);
// bar(big.top.x,	big.top.y,big_viewport.bot.x,big.bot.y+24);
// bar(big_viewport.top.x,	big.bot.y+1,big.bot.x+8,big.bot.y+24);
// bar(big_viewport.top.x,	big.top.y-15,big.top.x-1,big.bot.y+4);

//!! bar(big_viewport.top.x+1, big_viewport.top.y+1, big_viewport.bot.x-1, big_viewport.bot.y-1);

 if(cx_pix_unit)
	{
	 for(int i=big.top.x;i<=big.bot.x;i+=npixunit_hor)
	 {
		 pline(i,big.top.y,i,big.bot.y+4,Black);
	 }
	}

 line_style = DOTTED;
 setcolor(Lightgray);
 j=0;
	for(int i=big.bot.y;i>=viewports[0].bot.y;i-=32)
	 {
		pline(big.top.x,i,big.bot.x,i,Lightgray);
	 }

	npixunit_hor=npix_unit;
	pline(big.top.x,big.top.y,big.bot.x,big.top.y,Lightgray);
	j=0;
	memset(null_buf,' ',8);
	null_buf[8]=0;
	for(i=big.top.x;i<=big.bot.x;i+=npix_unit)
	 {
//		if(!cx_pix_unit)
//		{
		 pline(i,big.top.y,i,big.bot.y+4,Lightgray);
		 line_style = FILL;
		 pline(i,big.bot.y-4,i,big.bot.y+4,White);
		 line_style = DOTTED;
//		}
		if(time_sample)
		{
		 buf=ctime(&time_sample);
		 buf[10]=0;buf[19]=0;  //16
		 if( (Time_last_sample - Time_first_sample) > 3600) buf[16]=0;
		 if(i+25 > big.bot.x) i -= 16;
//		 outtextxy(i-20, big.bot.y+16, null_buf);
		 outtextxy(i-20, big.bot.y+16, &buf[4]);
//		 outtextxy(i-20, big.bot.y+6, null_buf);
		 outtextxy(i-20, big.bot.y+6, &buf[11]);
		 time_sample += nsample_unit * interv;
		}
	 }
 pline(big.bot.x,big.top.y,big.bot.x,big.bot.y,Lightgray);

 line_style = FILL;
 pline(big.top.x,big.top.y,big.top.x,big.bot.y,White);
 pline(big.top.x,big.bot.y,big.bot.x,big.bot.y,White);
 pline(viewports[0].top.x,viewports[0].bot.y,viewports[0].bot.x,viewports[0].bot.y,White);

 if(digital_inputs)
	{
	 bar(big_viewport.top.x+1, viewports[0].bot.y+1, big_viewport.bot.x, viewports[0].bot.y+14);
	 setfillstyle(SOLID_FILL, Lightgray);
	 bar(big_viewport.top.x, viewports[0].bot.y+6, big_viewport.bot.x, viewports[0].bot.y+9);
	 pline(big_viewport.top.x,viewports[0].bot.y+6,big_viewport.bot.x,viewports[0].bot.y+6,Green);
	 pline(big_viewport.top.x,viewports[0].bot.y+9,big_viewport.bot.x,viewports[0].bot.y+9,Green);

	 pline(big.top.x,viewports[0].bot.y+15,big.top.x,big.bot.y,White);
	}
 setfillstyle(SOLID_FILL, Black);
 strcpy(b,intervaltotext(NULL, (long)(interval-(interval/60)*60-(interval/3600)*3600)  , interval/60 , interval/3600 ));
 outtextxy(big.bot.x-80,big.top.y-9,b);
 printrange(big.top.x+16,big.top.y-9, Time_first_sample, Time_last_sample, NULL);
// clear_semaphore(&screen);
 display_pointer();
// drawver();
}

int updateminmax()
{
 asm push es;
 struct inputs_group *pinp;
 long min, max;
 pinp = inputs_group;
 for(int i=0;i<ind_inputs_group;pinp++,i++)
 {
	 min = 10000000L; max = -10000000L;
	 for(int k=0;k<pinp->n;k++)
		 minmax(1,pinp->inputs[k],&min,&max);
	 pinp->min=min;
	 pinp->max=max;
 }
 asm pop es;
}

int GGraph::upgroup(int type,int ind)  //type=1 add; =0 del
{
//	Point_info point_info;
//	char *des,*label;
	char *p,buf[10];
	long min,max;

	time_sample_last_read = 0x7FFFFFFF;
	cx_pix_unit = 0;
	min = 10000000L;
	max = -10000000L;
	minmax(1,ind,&min,&max);
//	if(min>5) min = int(min)-5;
//	else min = int(min);

//	memcpy(&point_info.point_name,&amon_inputs[ind],2);
//	get_point_info(&point_info, &des, &label);
	char u;
	u=point_info_table[ind].point_info.units;
	switch (amon_inputs[ind].point_type-1){
		case OUT:
		  u=out_range_array[u].value;
		  break;
		case IN:
		  u=in_range_array[u].value;
		  break;
	}
	for(int i=0;i<ind_inputs_group;i++)
	 if(u==inputs_group[i].unit) break;
	if(i==ind_inputs_group)
	{													//nu exista group
	 inputs_group[ind_inputs_group].min = min;
	 inputs_group[ind_inputs_group].max = max;
	 inputs_group[ind_inputs_group].n=1;
	 inputs_group[ind_inputs_group].inputs[0] = ind;
	 inputs_group[ind_inputs_group].unit = u;
//	 memcpy(inputs_group[ind_inputs_group].units,"deg.C",6);
	 ind_inputs_group++;
	 cx_pix_unit = 0;
	}
	else
	{
	 if(type==1)
	 {
		if(min<inputs_group[i].min) inputs_group[i].min=min;
		if(max>inputs_group[i].max) inputs_group[i].max=max;
		inputs_group[i].n++;
		inputs_group[i].inputs[inputs_group[i].n-1] = ind;
	 }
	 else
	 {
		if(--inputs_group[i].n==0)
		{
		 cx_pix_unit = 0;
		 for(int j=i;j<ind_inputs_group-1;j++)
			inputs_group[j]=inputs_group[j+1];
		 ind_inputs_group--;
		}
		else
		{
		 for(int j=0;j<inputs_group[i].n+1;j++)
			if(inputs_group[i].inputs[j]==ind) break;
		 for(int k=j;k<inputs_group[i].n;k++)
			inputs_group[i].inputs[k]=inputs_group[i].inputs[k+1];
		 min = 10000000L;
		 max = -10000000L;
		 for(k=0;k<inputs_group[i].n;k++)
			 minmax(1,inputs_group[i].inputs[k],&min,&max);
		 inputs_group[i].min=min;
		 inputs_group[i].max=max;
		}
	}
 }
 big.top.x = big_viewport.top.x + (ind_inputs_group?ind_inputs_group:1)*56;
 viewports[0].top.x = big.top.x ;
 int k;
 for(i=0;i<MAX_POINTS_IN_MONITOR;i++)
	if((k=inputs_viewport[i])>0)
		 viewports[k].top.x = big.top.x;
}

GGraph::~GGraph( )
{
/*
 for(int i=0;i<14;i++)
	{
	 if(ptablex[i]) delete ptablex[i];
	 if(ptabley[i]) delete ptabley[i];
	}
*/
	set_semaphore_dos();
	if( ulinex )
	 farfree(ulinex);

	if(headers)
			delete headers;
	if(headers_dig)
			delete headers_dig;
	clear_semaphore_dos();

//	if(dmon_table)
	if(dmon_table_handle)
	{
		 if(local)  //station_num == Station_NUM
//			 delete dmon_table;
			mfarfree(dmon_table_handle);
		 dmon_table=0;
		 dmon_table_handle=0;
	}
	if(mon_table_handle)
	{
//memsize();
		 mfarfree(mon_table_handle);
//memsize();
		 mon_table=0;
		 mon_table_handle=0;
	}
	if(pix_table)
	{
//    memsize();
	 mfarfree(pix_table_handle);						 //delete pix_table;
   pix_table = NULL;
//    memsize();
	}
//	 mfarfree((char *)pix_table, 1);						 //delete pix_table;
//	set_semaphore_dos();
//	clear_semaphore_dos();
}

/********************************************/
/*
int GGraph::GWx(int col)
{
 uint lat,lung;

 if(mode_text)
	 lat  = 1;
 else
	 lat  = textwidth(" ");
	 if(mode_text)
			return(tx+(col-1)*lat);
	 else
			return(tx+COL_SPACE+col*lat);
};

int GGraph::GWy(int row)
{
 uint lat,lung;

 if(mode_text)
	 lung = 1;
 else
	 lung = textheight("H")+LINE_SPACE;
	 if(mode_text)
			return(ty+(row-1)*lung);
	 else
			return(ty+3+row*(LINE_SPACE+lung));
};
*/
/***********************************/
/*
void GGrid::GWGoto(uint row, uint col)
{
 uint lat,lung;

 if((row<=nrows)&&(col<=ncols))
	 if(mode_text)
			mgotoxy(tx+(col-1)*lat_char_n,ty+(row-1)*lung_char_n);
	 else
				moveto(tx+COL_SPACE+col*lat_char_n,ty+3+row*(LINE_SPACE+(lung_char_n+LINE_SPACE)));
};
*/
int GGraph::drawpoint(int ind)
{
//						Point_info point_info;
//						char *des,*label;
						byte var_type, point_type;
						int num_net,num_point, num_panel;
						char *p,buf[10];
						pointtotext(buf,&amon_inputs[ind]);
						p=ispoint(rtrim(buf),&num_point,&var_type, &point_type, &num_panel, &num_net, network, station_num);
//						memcpy(&point_info.point_name,&amon_inputs[ind],2);
//						get_point_info(&point_info, &des, &label);
						if(onoff & (1<<ind))
						 {
							onoff &= ~(1<<ind);
							hide_pointer();
							put_button(Label[ind].top.x,	Label[ind].top.y,(p?p:NULL),64,13,Lightgray,Black,BUTON);
							display_pointer();
							setcolor(Black);
							if(!point_info_table[ind].point_info.digital_analog)
							{																//digital
							 viewports[0].bot.y += 32;
							 if(inputs_viewport[ind]!=digital_inputs)
							 {
								for(int i=ind+1;i<MAX_POINTS_IN_MONITOR;i++)
								 {
									 if(inputs_viewport[i]>0)
									 {
										inputs_viewport[i]--;
										viewports[i].top.y += 32;
										viewports[i].bot.y += 32;
									 }
								 }
							 }
							if(digital_inputs) digital_inputs--;
							inputs_viewport[ind]=-1;
							if(!digital_inputs) viewports[0].bot.y += 15;

							}
							else
							 {
								inputs_viewport[ind]=-1;
								upgroup(0,ind);
							 }
						 }
						else
						 {
							setcolor(color[ind]);
							onoff |= (1<<ind);
							hide_pointer();
							put_button(Label[ind].top.x,	Label[ind].top.y,(p?p:NULL),64,13,(strlen(p)?color[ind]:Lightgray),Black,BUTON);
							display_pointer();
							if(point_info_table[ind].point_info.digital_analog)
							{																//analog
							 inputs_viewport[ind]=0;
							 upgroup(1,ind);
							}
							else
							{																//digital
							 signed char v=0;
							 for(int i=0;i<ind;i++)
								if(inputs_viewport[i]>0) v=inputs_viewport[i];

							 inputs_viewport[ind] = v+1;
							 for(i=ind+1;i<MAX_POINTS_IN_MONITOR;i++)
								if(inputs_viewport[i]>0) inputs_viewport[i]++;

							 for(i=ind;i<MAX_POINTS_IN_MONITOR;i++)
								if((v=inputs_viewport[i])>0)
								{
								 viewports[v].top.x = big.top.x;
								 viewports[v].bot.x = big.bot.x;
								 viewports[v].top.y = ((v-1)?(viewports[v-1].bot.y-28-28):big.bot.y-28);
								 viewports[v].bot.y = viewports[v].top.y+24;
								}
							 digital_inputs++;
							 if(digital_inputs==1)
								 viewports[0].bot.y -= 32+15;
							 else
								 viewports[0].bot.y -= 32;

							}
						 }
}


int GGraph::drawall()
{
           MouseStatus stat;
					 mouse_status(stat);
					 linex = stat.where.x;
	         liney = stat.where.y;
					 if(sample > 1)
					 {
						cy_pix_unit = 1;
						drawgrid(sample, interval, time_first_sample);
						drawver();
						for(int i=0;i<MAX_POINTS_IN_MONITOR;i++)
							if(onoff & (1<<i))
								draw(i);
					 }
}

int GGraph::HandleEvent()
{
	long interv;
	MouseStatus stat;
	long timesample, max_file, l, l1, l2, timeread;
	Header_amon *pheaders, *pheaders1;
	int nheaders,ssample,n,i;

 if(!refresh_graph_time && status==SUCCESS)
 {
	refresh_graph_mode = 1;
	if(justsavemem)
	{
		if(ind_headers)
			analtime = headers[ind_headers-1].time_last_sample;
		if(mon_table_handle)
		{
		 mfarfree(mon_table_handle);
//		 delete mon_table;
		 mon_table=0;
		 mon_table_handle=0;
		}
//		if(dmon_table)
		if(dmon_table_handle)
		{
		 if(local)  //station_num == Station_NUM
//			 delete dmon_table;
			 mfarfree(dmon_table_handle);
		 dmon_table=0;
		 dmon_table_handle=0;
		}
		set_semaphore_dos();
		if(headers)
				delete headers;
		if(headers_dig)
				delete headers_dig;
		clear_semaphore_dos();

//		for(i=0;i<14;i++)
//		 inputs_viewport[i]=-1;
//		digital_inputs = 0;
//		memset(inputs_group,0,sizeof(struct inputs_group));
//		ind_inputs_group=0;
//	zoom =0;
//	first = 0;
//	mon_table=0;
		headers = 0;
		headers_dig = 0;
		asm push es;
		npix_sample = 0;
	 asm pop es;
//	timerange=TIMErange=3600L*24L;
//	set_semaphore_dos();
//	pix_table = (int (*)[2][530])new int[2][530];
//	clear_semaphore_dos();
// if(station_num != Station_NUM)
 if(!local)
 {
//	 if( (status=readnettable(current_mon,viewports,panel,network)) != SUCCESS)
	 GWindow *D;
	 hide_pointer();
	 DisplayMessage(200, 150, 500, 204, ctrlbreak_text," Reading data...   ",&D);
	 status=readnettable(current_mon,viewports,panel,network);
	 DeleteMessage(D);
	 display_pointer();

	 if( status!=SUCCESS )
			{status = ERROR_COMM; return 0;}
 }
 else
	 readtable(current_mon,viewports);

//		if(ptr_panel->analog_mon[current_mon-1].ind_views)
// {
//	timerange = TIMErange = ptr_panel->analog_mon[current_mon-1].views[0].timerange;
//	scale(TIME_last_sample, &viewports[0]);
//	for(int j=0;j<14;j++)
//	 if(ptr_panel->analog_mon[current_mon-1].views[0].onoff & (1<<j))
//		 drawpoint(j);
// }
	 justsavemem = 0;
	}

	if(ind_headers_dig)
	{
	 ltime = 0;
		 for(i=0; i < headers_dig[ind_headers_dig-1].n_inputs; i++)
			if(headers_dig[ind_headers_dig-1].time_last_sample[i] > ltime) ltime  = headers_dig[ind_headers_dig-1].time_last_sample[i];

//		 if(station_num != Station_NUM)
		 if(!local)
		 {
			 if((status=updatememdig(current_mon-1, panel, network, 1))!=SUCCESS)
			 {
//				status = ERROR_UPDATE;
				justsavemem = 1;
				refresh_graph_time = 0;
				status=SUCCESS;
				return 0;
			 }
		 }
		 else
			 updatememdig(current_mon-1, panel, network);
	}
	if(ind_headers)
	{
	 ltime = headers[ind_headers-1].time_last_sample;
//	 if(station_num != Station_NUM)
	 if(!local)
	 {
/*		if( panel_info1.panel_type == T3000 )*/
		{
		 if((status=updatemem(current_mon-1, panel, network, 1))!=SUCCESS)
		 {
//			 status = ERROR_UPDATE;
			 justsavemem = 1;
			 refresh_graph_time = 0;
			 status=SUCCESS;
			 return 0;
		 }
		}
/*
		else
			status=ERROR_UPDATE;
*/
	 }
	 else
		 updatemem(current_mon-1, panel, network);

	TIME_last_sample = headers[ind_headers-1].time_last_sample;
	TIME_first_sample = headers[0].time_last_sample-(headers[0].n_sample-1)*headers[0].interval;
//	timerange = TIMErange;
	if(!Time_last_sample)
	{
		Time_last_sample = TIME_last_sample;
		Time_first_sample = TIME_first_sample;
	}
	else
	{
		if(analtime)
		 {
			ltime = analtime;
			analtime = 0;
		 }
		Time_last_sample += headers[ind_headers-1].time_last_sample - ltime;
		Time_first_sample += headers[ind_headers-1].time_last_sample - ltime;
	}
	updateminmax();
 }
 if(ind_headers_dig && !ind_headers)
 {
		 unsigned long l,max = 0;
		 for(i=0; i < headers_dig[ind_headers_dig-1].n_inputs; i++)
				if(headers_dig[ind_headers_dig-1].time_last_sample[i] > max) max = headers_dig[ind_headers_dig-1].time_last_sample[i];
		 TIME_last_sample = max;
		 unsigned long min = 0x0ffffffff;
		 for(i=0; i < headers_dig[0].n_inputs; i++)
				if((l=*((long *)(headers_dig[0].prev_header)+headers_dig[0].offset[i])) < min) min = l;
		TIME_first_sample = min;
//		scale(TIME_last_sample, viewports);
		if(nsample_mem_dig_mon[current_mon-1])
		{
		 Time_last_sample += TIME_last_sample - ltime + ((TIME_last_sample - ltime)?0:dgtimelast);
		 Time_first_sample += TIME_last_sample - ltime + ((TIME_last_sample - ltime)?0:dgtimelast);
		}
		else
		{
		 Time_last_sample = TIME_last_sample;
		 Time_first_sample = TIME_first_sample;
		}
 }
	scale(Time_last_sample, &viewports[0]);
	drawall();

	psample(&interv, current_analog_mon);
	refresh_graph_time = interv * 18 + 40;
	refresh_graph_mode = 0;
//
//	if(save_monitor_status)
//	{
//		resume(AMONITOR);
//		task_switch();
//	}
//


 }

// if (bioskey_new(1) || first || status!=SUCCESS)                //kbhit())
 if (bioskey_new(1) || first || status==ERROR_COMM)                //kbhit())
 {
	if(!first && status!=ERROR_COMM)
		key.i = bioskey_new(0);
//	if (key.ch[0] == 27 || key.ch[0] == 'X' || status!=SUCCESS)
	if (key.ch[0] == 27 || key.ch[0] == 'X' || status==ERROR_COMM)
		 {
			GReleaseWindow();
			if(!mode_text)
				msettextstyle(DEFAULT_FONT, HORIZ_DIR,1);
			first=0;
			return 1;
		 }

	 if(('1'<=key.ch[0] && key.ch[0]<='9') || ('A'<=key.ch[0] && key.ch[0]<='E'))
	 {
						int ind;
						if('1'<=key.ch[0] && key.ch[0]<='9')
							ind=key.ch[0]-'1';
						else
							ind=key.ch[0] - 'A' + 9;
						if(!amon_inputs[ind].zero())
						{
						 drawpoint(ind);
						 drawall();
						}
						first = 0;
	 }

	if (key.ch[0]==0)
	switch (key.ch[1]){
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.057  ********
// ********       begin       ********
// ***********************************
	 case F1KEY:
			{
				T3000help(Flag_help);
			}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.057  ********
// ********        end        ********
// ***********************************
	 case 77:
						break;
	 case 75:
						break;
	 case 73:                                    //pgup
	 case 72:
						break;
	 case 81:                                // pgdn
	 case 80:
						break;
	 case 82: key.ch[0]='\x0D';					 // insert
						break;
	 case 83: key.ch[0]='\x0D';					 // delete
						break;
	 case 132: 															// CTRL/PgUp
	 case 118: key.ch[0]='\x0D';					 // CTRL/PgDn
						break;
		 default:
						break;
	 }
	 if (key.ch[0] == '\t');
	 if (key.ch[0] == '\x0D')
			 {
			 }
 }
// display_pointer();
 mouse_status(stat);
 if(stat.leftButton || key.ch[0] == 'L' || key.ch[0] == 'S' ||
											 key.ch[0] == 'D' || key.ch[0] == 'R' ||
											 key.ch[0] == '+' || key.ch[0] == '-' ||
											 key.ch[0] == 'Z' || key.ch[0] == 'T' ||
											 (key.ch[0] == 0 && key.ch[1] == 75)  ||
											 (key.ch[0] == 0 && key.ch[1] == 77) )
 {
	if(mouse_inside(Zoomout.top.x,
		 Zoomout.top.y,
		 Zoomout.bot.x,
		 Zoomout.bot.y) || key.ch[0] == '+')
		{
			mouse_status(stat);
			if(stat.leftButton || key.ch[0] == '+')
			 {
					key.i = -1;
					if(stat.leftButton)
						while(!get_button_released(BLEFT,stat));
					l = (Time_last_sample - Time_first_sample) / 2L;
					if(l>=interval)
					{
						timerange /= 2L;
									if(timerange > l) timerange = l;
						Time_first_sample += l;
						scale(Time_last_sample, &viewports[0]);
						cx_pix_unit = 0;
						notscale=1;
						drawall();
					}
			 }
		}

	if(mouse_inside(Zoomin.top.x,
		 Zoomin.top.y,
		 Zoomin.bot.x,
		 Zoomin.bot.y) || key.ch[0] == '-')
		{
			mouse_status(stat);
			if(stat.leftButton || key.ch[0] == '-')
			 {
					key.i = -1;
					if(stat.leftButton)
						while(!get_button_released(BLEFT,stat));
					l = (Time_last_sample - Time_first_sample);
					time_first_sample = Time_first_sample;
					if(( Time_first_sample - l ) < TIME_first_sample) Time_first_sample = TIME_first_sample;
					else Time_first_sample -= l;
					if(time_first_sample != Time_first_sample)
					{
						timerange *= 2L;
						scale(Time_last_sample, &viewports[0]);
						notscale=1;
						drawall();
					}
			 }
		}
	if(mouse_inside(Zoomoutint.top.x,
		 Zoomoutint.top.y,
		 Zoomoutint.bot.x,
		 Zoomoutint.bot.y) || key.ch[0] == 'Z')
		{
			char *l1,*l2;
			set_semaphore_dos();
			l1 = new char [2048];
      l2 = l1 + 1024;
			clear_semaphore_dos();
			get_button_pressed(BLEFT,stat);
			get_button_released(BLEFT,stat);
			if(key.ch[0] != 'Z')
				while(!get_button_released(BLEFT,stat));
			key.i = -1;
			GWindow *m;
			DisplayMessage(370, 10, 630, 60, NULL, "    Select left margin !",&m);
			move_mouse(big.top.x+1,big.top.y+10);
			mouse_status(stat);

			 lxzoom=stat.where.x;
			 hide_pointer();
			 mgetimage_10(lxzoom, big.top.y, lxzoom, big.bot.y,l1);
			 moveto(lxzoom,big.top.y);
			 setcolor(EGA_YELLOW);
			 lineto(lxzoom,big.bot.y);
			 display_pointer();

			while(!get_button_released(BLEFT,stat))
			{
				mouse_status(stat);
				if((n=bioskey_new(1)))
				{
				 key.i=bioskey_new(0);
				 if(key.ch[0]==0 && key.ch[1]==77)
					 if(bioskey_new(2)& 0x02) stat.where.x += 16;
					 else stat.where.x += 2;
				 if(key.ch[0]==0 && key.ch[1]==75)
					 if(bioskey_new(2)& 0x02) stat.where.x -= 16;
					 else stat.where.x -= 2;
				 move_mouse(stat.where.x,stat.where.y);
				}
				if(lxzoom!=stat.where.x && (stat.where.x < big.bot.x && stat.where.x > big.top.x)
					 && (stat.where.y < big.bot.y && stat.where.y > big.top.y))
				{
				hide_pointer();
				mputimage_10(lxzoom, big.top.y,lxzoom,big.bot.y,l1);
				lxzoom=stat.where.x;
				mgetimage_10(lxzoom,big.top.y,lxzoom,big.bot.y,l1);
				moveto(lxzoom,big.top.y);
				setcolor(EGA_YELLOW);
				lineto(lxzoom,big.bot.y);
				display_pointer();
				}
				if(n && key.ch[0]==13)  break;
			}
//			putimage(lxzoom,big.top.y,l1,COPY_PUT);

			DeleteMessage(m);
			DisplayMessage(370, 10, 630, 60, NULL, "    Select right margin !",&m);

			move_mouse(lxzoom+1,big.top.y+10);

			 rxzoom=stat.where.x;
			 hide_pointer();
			 mgetimage_10(rxzoom, big.top.y, rxzoom, big.bot.y,l2);
			 moveto(rxzoom,big.top.y);
			 setcolor(EGA_YELLOW);
			 lineto(rxzoom,big.bot.y);
			 display_pointer();

//			get_button_released(BLEFT,stat);
			while(!get_button_released(BLEFT,stat))
			{
				mouse_status(stat);
				if((n=bioskey_new(1)))
				{
				 key.i=bioskey_new(0);
				 if(key.ch[0]==0 && key.ch[1]==77)
					 if(bioskey_new(2)& 0x02) stat.where.x += 16;
					 else stat.where.x += 2;
				 if(key.ch[0]==0 && key.ch[1]==75)
					 if(bioskey_new(2)& 0x02) stat.where.x -= 16;
					 else stat.where.x -= 2;
				 move_mouse(stat.where.x,stat.where.y);
				}
				if(rxzoom!=stat.where.x && (stat.where.x < big.bot.x && stat.where.x > lxzoom)
					 && (stat.where.y < big.bot.y && stat.where.y > big.top.y))
				{
				 hide_pointer();
				 mputimage_10(rxzoom, big.top.y,rxzoom,big.bot.y,l2);
				 rxzoom=stat.where.x;
				 mgetimage_10(rxzoom,big.top.y,rxzoom,big.bot.y,l2);
				 moveto(rxzoom,big.top.y);
				 setcolor(EGA_YELLOW);
				 lineto(rxzoom,big.bot.y);
				 display_pointer();
				}
				if(n && key.ch[0]==13)  break;
			}
			hide_pointer();
			mputimage_10(lxzoom,big.top.y,lxzoom,big.bot.y,l1);
			mputimage_10(rxzoom,big.top.y,rxzoom,big.bot.y,l2);
			set_semaphore_dos();
      delete l1;
			clear_semaphore_dos();

			display_pointer();
			ryzoom=0;
			lyzoom=viewports[0].bot.y-viewports[0].top.y;
			DeleteMessage(m);

			sample = (rxzoom-lxzoom+1)/npix_sample+1;
			if(sample>=1)
			{
				 int first;
				 first = (lxzoom-viewports[0].top.x)/npix_sample;
				 Time_first_sample +=  first*interval;
				 Time_last_sample  = Time_first_sample + sample*interval;
				 timerange = 0;
				 scale(Time_last_sample, &viewports[0]);
				 cx_pix_unit = 0;
				 notscale=1;
				 drawall();
/*
				 drawgrid(sample, interv, time_first_sample);
				 drawver();
				 for(int i=0;i<14;i++)
						if(onoff & (1<<i))
							draw(i);
*/
			}
			else
				sample = 1;

	 }

	if(mouse_inside(Right.top.x,
		 Right.top.y,
		 Right.bot.x,
		 Right.bot.y) || (key.ch[0] == 0 && key.ch[1] == 77))
		{
			mouse_status(stat);
			if(stat.leftButton || (key.ch[0] == 0 && key.ch[1] == 77))
			 {
					ssample=0;n=0;
					key.i = -1;
					if(stat.leftButton)
						while(!get_button_released(BLEFT,stat));
					timesample = Time_last_sample;
					interv = Time_last_sample - Time_first_sample;
					Time_last_sample += nsample_unit*interval;
					if(Time_last_sample > TIME_last_sample)
					{
					  if( local_request(panel,network) )
						{
						if( TIME_last_sample < current_mon_workdata->last_sample_time )  // no more data in memory
						{
						 char *buf;
						 max_file=(long)MAX_SAMPLE*(long)MAX_INP*4L;
						 set_semaphore_dos();
						 buf = new char[max_file>>1];
						 clear_semaphore_dos();
						 if(buf)
						 {
						  status = ERROR_UPDATE;
							l=0;
							if( TIME_last_sample > current_mon_workdata->last_sample_saved_time )
						  {
							 n=1;
						  }
						  else
						  {
							 l = (max_file>>1);
							 timeread = TIME_last_sample+1;
							 upreadmontable(current_mon, panel, network, &l, timeread, FORWARD,
												  (long **)&buf, &pheaders, nheaders, 0);
						  }
							for(i=0,l1=0; i<ind_headers; i++)
							{
							  l1 += headers[i].n_sample*headers[i].n_inputs;
							}  // l1 nr sample from buf
							l *= 4;   // nr byte's cititi
							l2 = (max_file>>1)-((long)current_analog_mon->anum_inputs*4L);
							if( l <  l2 )
							{
								ssample = ((max_file>>1)-l) / ((long)current_analog_mon->anum_inputs*4L);
								psample(&l2, current_analog_mon);
								set_semaphore(&t3000_flag);
								if(ssample > current_mon_workdata->head_index)
								{
									ssample = current_mon_workdata->head_index;
//									status = SUCCESS;
								}
								timeread = current_mon_workdata->last_sample_time - ((long)(current_mon_workdata->head_index-ssample))*l2;
								clear_semaphore(&t3000_flag);
								pmem_table = (long *)(buf+l);
								ssample = newmem(current_mon-1, ssample, n?headers[ind_headers-1].time_last_sample:timeread,
													 (char *)(pmem_table), &pmem_table, &index_last_value, &last_mem_block, &nsample_mem_block, n?headers:pheaders, n?&ind_headers:&nheaders, n);
								if(n) headers[ind_headers-1].n_sample -= ssample;
								l += ( (long)ssample*(long)current_analog_mon->anum_inputs*4L);
							}
							if( l1*4L+l > max_file)
							{
							  l1 = l/4L;
								l1=removebuf(l1);
							}
							if(n)
							{
							 headers[ind_headers-1].n_sample += ssample;
							 headers[ind_headers-1].time_last_sample = timeread;
							}
							memmove(mon_table + l1, buf, l);
							pmem_table = mon_table + (l1 + l/4);
							set_semaphore_dos();
							delete buf;
							if(!n)
							 pheaders1 = new Header_amon[nheaders+ind_headers];
							clear_semaphore_dos();
							if(!n)
							{
							 memmove(pheaders1, headers, sizeof(Header_amon)*ind_headers);
							 memmove(&pheaders1[ind_headers], pheaders, sizeof(Header_amon)*nheaders);
							 ind_headers += nheaders;
							 buf = (char *)(mon_table + l1);
							 for(i=ind_headers-nheaders; i<ind_headers; i++)
							 {
								 pheaders1[i].prev_header = (long)((long *)buf);
								 buf += (long)pheaders1[i].n_sample*(long)pheaders1[i].n_inputs*4L;
							 }
							 set_semaphore_dos();
							 if(headers)
								delete headers;
							 if(pheaders)
								delete pheaders;
							 clear_semaphore_dos();
							 headers = pheaders1;
							}
							setscale(viewports);
							updateminmax();
							Time_last_sample=timesample+nsample_unit*interval;
							if(Time_last_sample > TIME_last_sample)
							  Time_last_sample = TIME_last_sample;
							Time_first_sample=Time_last_sample - interv;
							if(Time_first_sample > TIME_first_sample)
								Time_first_sample = TIME_first_sample;
						  }
							else
						  {
							Time_last_sample=timesample;
							DisplayMessage(200, 150, 500, 200, NULL, "Enough memory!", NULL, Blue, NULL, 1000);
							return 0;
						  }
						}
						else
						{
						 Time_last_sample = timesample;
						 DisplayMessage(200, 150, 500, 200, NULL, "No more data!", NULL, Blue, NULL, 1000);
						 return 0;
						}
					  }
					  else
						{
						 Time_last_sample = timesample;
						 DisplayMessage(200, 150, 500, 200, NULL, "No more data!", NULL, Blue, NULL, 1000);
						 return 0;
					  }
//					 Time_last_sample = TIME_last_sample;
					}
					else
						Time_first_sample += Time_last_sample-timesample	;
//					if(time_last_sample!=Time_last_sample)
					{
					 scale(Time_last_sample, &viewports[0]);
					 notscale=1;
					 drawall();
					}
/*
					time_first_sample += nsample_unit*interv;
					First_sample += nsample_unit;
					if(First_sample<LAST_sample)
					{
					}
					else
					{
					 First_sample -= nsample_unit;
					 time_first_sample -= nsample_unit*interv;
					}
*/
			 }
		}

	if(mouse_inside(Left.top.x,
		 Left.top.y,
		 Left.bot.x,
		 Left.bot.y) || (key.ch[0] == 0 && key.ch[1] == 75))
		{
			mouse_status(stat);
			if(stat.leftButton || (key.ch[0] == 0 && key.ch[1] == 75))
			 {
					key.i = -1;
					if(stat.leftButton)
						while(!get_button_released(BLEFT,stat));
					timesample = Time_first_sample;
					interv = Time_last_sample - Time_first_sample;
					Time_first_sample -= nsample_unit*interval;
					if(Time_first_sample < TIME_first_sample)
					{
//						 timeread = (TIME_last_sample + TIME_first_sample)/2;
						 timeread = TIME_first_sample-1;
						 max_file=(long)MAX_SAMPLE*(long)MAX_INP*4L;
						 char *buf;
						 set_semaphore_dos();
						 buf = new char[max_file>>1];
						 clear_semaphore_dos();
						 if(buf)
						 {
//						  timefirst = TIME_first_sample;
						  l = (max_file>>1);
						  memmove(buf, mon_table, l);
						  if(upreadmontable(current_mon, panel, network, &l, timeread, BACK,
												  &mon_table, &pheaders, nheaders, 0))
							{
							l *= 4;
							memmove((char *)mon_table+(max_file>>1)+l, (char *)mon_table+(max_file>>1), (max_file>>1)-l);
							memmove((char *)mon_table+l, buf, max_file>>1);
							l1 = (max_file - l)/4L;
							n=0;
							for(i=0; i<ind_headers; i++)
							{
							 headers[i].prev_header = (long)((char *)headers[i].prev_header + l);
							 if( n+headers[i].n_sample*headers[i].n_inputs > l1 )
							 {
							  for(int j=0; j<headers[i].n_sample; j++)
								{
								if( n+headers[i].n_inputs > l1 )
								{
								 headers[i].time_last_sample -= (headers[i].n_sample-j)*headers[i].interval;
								 headers[i].n_sample = j;
								 if(!j) ind_headers = i;
								 else ind_headers = i+1;
								 break;
								}
								n += headers[i].n_inputs;
							  }
							  break;
							 }
							 n += headers[i].n_sample*headers[i].n_inputs;
							}
							set_semaphore_dos();
							delete buf;
							pheaders1 = new Header_amon [nheaders+ind_headers];
							clear_semaphore_dos();
							memcpy(pheaders1, pheaders, sizeof(Header_amon) * nheaders);
							memcpy(&pheaders1[nheaders], headers, sizeof(Header_amon) * ind_headers);
							ind_headers += nheaders;

							set_semaphore_dos();
							if(headers)
								delete headers;
							if(pheaders)
								delete pheaders;
							clear_semaphore_dos();
							status = ERROR_UPDATE;
							headers = pheaders1;
							setscale(viewports);
							updateminmax();
							l=nsample_unit;
							Time_first_sample=timesample-nsample_unit*interval;
							if(Time_first_sample < TIME_first_sample)
							  Time_first_sample = TIME_first_sample;
							Time_last_sample=Time_first_sample + interv;
							if(Time_last_sample > TIME_last_sample)
							  Time_last_sample = TIME_last_sample;
////
/*
							for(i=0; i<ind_headers_dig; i++)
							{
							 if( headers_dig[i].time_last_sample[ > l1 )
							 {
							  for(int j=0; j<headers[i].n_sample; j++)
								{
								if( n+headers[i].n_inputs > l1 )
								{
								 headers[i].time_last_sample -= (headers[i].n_sample-j)*headers[i].interval;
								 headers[i].n_sample = j;
								 if(!j) ind_headers = i;
								 else ind_headers = i+1;
								 break;
								}
								n += headers[i].n_inputs;
								}
							  break;
							 }
							 n += headers[i].n_sample*headers[i].n_inputs;
							}

						  if(upreaddigmontable(current_mon, &l, timeread, BACK,
												  &mon_table, &pheaders, nheaders, 0))
*/
////
							}
						  else
							{
							set_semaphore_dos();
							delete buf;
							clear_semaphore_dos();
							Time_first_sample=timesample;
							DisplayMessage(200, 150, 500, 200, NULL, "No more data!", NULL, Blue, NULL, 1000);
							return 0;
						  }
						 }
						 else
						 {
							Time_first_sample=timesample;
							DisplayMessage(200, 150, 500, 200, NULL, "Enough memory!", NULL, Blue, NULL, 1000);
							return 0;
						 }
					}
					else
					{
						 l=nsample_unit;
						 Time_last_sample -= l*interval;
					}
					if(l)
					{
						scale(Time_last_sample, &viewports[0]);
						notscale=1;
						drawall();
					}
/*
						drawgrid(sample, interv, time_first_sample);
						drawver();
						for(int i=0;i<14;i++)
							if(onoff & (1<<i))
								draw(i);
*/
			 }
		}

	if(mouse_inside(Reset.top.x,
		 Reset.top.y,
		 Reset.bot.x,
		 Reset.bot.y) || key.ch[0] == 'R')
		{
			mouse_status(stat);
			if(stat.leftButton || key.ch[0] == 'R')
			{
			 if(ind_headers)
			 {
				 TIME_last_sample = headers[ind_headers-1].time_last_sample;
				 TIME_first_sample = headers[0].time_last_sample-(headers[0].n_sample-1)*headers[0].interval;
			 }
			 else
				if(ind_headers_dig )
				{
				 unsigned long l,max = 0;
				 for(i=0; i < headers_dig[ind_headers_dig-1].n_inputs; i++)
						if(headers_dig[ind_headers_dig-1].time_last_sample[i] > max) max = headers_dig[ind_headers_dig-1].time_last_sample[i];
				 TIME_last_sample = max;
				 unsigned long min = 0x0ffffffff;
				 for(i=0; i < headers_dig[0].n_inputs; i++)
					 if((l=*((long *)(headers_dig[0].prev_header)+headers_dig[0].offset[i])) < min) min = l;
				 TIME_first_sample = min;
				}
				timerange = TIMErange;
				scale(TIME_last_sample, &viewports[0]);
/*
				 sample=LAST_sample+1;
				 time_last_sample = TIME_last_sample;
				 time_first_sample = TIME_first_sample;
*/
				 drawall();
			 }
		}

	if(mouse_inside(Save.top.x,
		 Save.top.y,
		 Save.bot.x,
		 Save.bot.y) || key.ch[0] == 'S')
		{
			mouse_status(stat);
			if(stat.leftButton || key.ch[0] == 'S')
			 {
					char name[11];
					memset(name,' ',10);
					if(stat.leftButton)
						while(!get_button_released(BLEFT,stat));
					name[11]=0;
					if(current_analog_mon->ind_views >= MAX_VIEWS)
					{
//					 GWDialog *D;
					 DisplayMessage(200, 150, 500, 200, NULL, "     To many views  ",NULL,Black,NULL,1500);
//					 while(!bioskey_new(1));
//					 key.i = bioskey_new(0);
//					 DeleteMessage(D);
					}
					else
					{
					 GWDialog *D;
					 DisplayMessage(200, 150, 500, 200, "    View name : ",&D);
					 name[0]=0;
					 D->GDGets(name,1,16,10,Blue,White);
					 for(i=0;i<MAX_VIEWS;i++)
							if(!strcmp(rtrim(name),current_analog_mon->views[i].view_name)) break;
					 if(strlen(name) && i==MAX_VIEWS)
					 {
						memcpy(current_analog_mon->views[current_analog_mon->ind_views].view_name,name,10);
						current_analog_mon->views[current_analog_mon->ind_views].onoff = onoff;
						current_analog_mon->views[current_analog_mon->ind_views++].timerange = TIMErange;
						modify_monitor=2;
					 }
					 DeleteMessage(D);
					}
			 }
		}
	if(mouse_inside(View.top.x,
		 View.top.y,
		 View.bot.x,
		 View.bot.y) || key.ch[0] == 'L')
		{
			mouse_status(stat);
			if(stat.leftButton || key.ch[0] == 'L')
			{
			 set_semaphore_dos();
			 char (*arrayl)[11] = new char [MAX_VIEWS][11];
			 clear_semaphore_dos();
			 memset((char *)arrayl,' ',MAX_VIEWS*11);
			 for(i=0;i<MAX_VIEWS;i++)
			 {
				 strcpy((char *)(arrayl+i),current_analog_mon->views[i].view_name);
       }
			 n=dialog_select( MAX_VIEWS, (char *)arrayl, 1, View.top.x,View.bot.y+10,Lightgray,Lightgray);  // 0=don't save
			 if(n>=0)
			 {
				onoff=0;
				viewport=0;
				nviewports=1;
				for(i=0;i<10;i++)
				{
				 viewports[i].top.x=big_viewport.top.x+56;
				 viewports[i].top.y=big_viewport.top.y+12;
				 viewports[i].bot.x=big_viewport.bot.x-8;
				 viewports[i].bot.y=big_viewport.bot.y-26;
				}
				for(i=0;i<MAX_POINTS_IN_MONITOR;i++)
				 inputs_viewport[i]=-1;
				digital_inputs = 0;
				memset(inputs_group,0,sizeof(inputs_group));
				ind_inputs_group=0;
				zoom =0;

					timerange = TIMErange = current_analog_mon->views[n].timerange;
					scale(TIME_last_sample, &viewports[0]);
					for(int j=0;j<MAX_POINTS_IN_MONITOR;j++)
					{
					 byte var_type, point_type;
					 int  num_point,num_net, num_panel;
					 char *p,buf[10];
					 pointtotext(buf,&amon_inputs[j]);
					 p=ispoint(rtrim(buf),&num_point,&var_type, &point_type, &num_panel, &num_net, network, station_num);
					 hide_pointer();
					 put_button(Label[j].top.x,	Label[j].top.y,(p?p:NULL),64,13,Lightgray,Black,BUTON);
					 display_pointer();
					 if(current_analog_mon->views[n].onoff & (1<<j))
						 drawpoint(j);
					}
			 }
			 set_semaphore_dos();
			 delete arrayl;
			 clear_semaphore_dos();
			 cx_pix_unit = 0;
			 drawall();
			}
		}

	if(mouse_inside(Delete.top.x,
		 Delete.top.y,
		 Delete.bot.x,
		 Delete.bot.y) || key.ch[0] == 'D')
		{
			mouse_status(stat);
			if(stat.leftButton || key.ch[0] == 'D')
			 {
				 set_semaphore_dos();
				 char (*arrayl)[11] = new char [MAX_VIEWS][11];
				 clear_semaphore_dos();
				 memset((char *)arrayl,' ',MAX_VIEWS*11);
				 for(i=0;i<MAX_VIEWS;i++)
					 strcpy((char *)(arrayl+i),current_analog_mon->views[i].view_name);
//					memcpy(arrayl+i,current_analog_mon->views[i].view_name,11);
				 n=dialog_select( MAX_VIEWS, (char *)arrayl, 1, Delete.top.x,Delete.bot.y+10,Lightgray,Lightgray);  // 0=don't save
				 if(n>=0)
				 {
					current_analog_mon->ind_views--;
					for(int j=n;j<current_analog_mon->ind_views;j++)
					 current_analog_mon->views[j]=current_analog_mon->views[j+1];
					current_analog_mon->views[j].view_name[0] = 0;
					modify_monitor=2;
				 }
				 set_semaphore_dos();
				 delete [] arrayl;
				 clear_semaphore_dos();
//				 TIMErange = timerange;
//				 scale(TIME_last_sample, &viewports[0]);
				 cx_pix_unit = 0;
				 drawall();
			 }
		}

	if(mouse_inside(Timerange.top.x,
		 Timerange.top.y,
		 Timerange.bot.x,
		 Timerange.bot.y) || key.ch[0] == 'T')
		{
			mouse_status(stat);
			if(stat.leftButton || key.ch[0] == 'T')
			{
				 l=0;
				 i=dialog_select( 6, (char *)array_timerange, 1, Timerange.top.x,Timerange.bot.y+10,Lightgray,Lightgray);  // 0=don't save

				 if(i>=0)
				 {
					if(i==5)
					 {
						timerange=0;
						Time_first_sample = TIME_first_sample;
						Time_last_sample = TIME_last_sample;
					 }
					else
					 {
						 switch (i) {
							case 0:  // 1 hour
										timerange = 3600L;
										break;
							case 1:  // 4 hours
										timerange = 3600L*4L;
										break;
							case 2:
										timerange = 24L*3600L;
										break;
							case 3:
										timerange = 4L*24L*3600L;
										break;
							case 4:
										n=dialog_select( 4, (char *)array_timerange_custom, 1, Timerange.top.x+120,Timerange.bot.y+10+80+(i-1)*20,Lightgray,Lightgray);  // 0=don't save

									 char buf[25],name[5];
                            name[0]=0;
									 strcpy(buf,numberof);
									 strcat(buf,view_name);
									 strcat(buf,colon);

									 GWDialog *D;
									 DisplayMessage(200, 340, 500, 390, buf,&D);
									 D->GDGets(name,1,23,3,Blue,White);
									 l=atol(name);
									 if(l)
									 {
									  switch (n) {
										case 0:
												timerange = l*60L;
												break;
										case 1:
												timerange = l*3600L;
												break;
										case 2:
												timerange = l*24L*3600L;
												break;
										case 3:
												timerange = l*24L*3600L*31L;
												break;
										}
									 }
									 else l=-1;
									 DeleteMessage(D);
									 break;
							}

					 }
//					char buf[5];
//					outtextxy(100,0,itoa(timerange,buf,10));
					if(l!=-1)
					{
					 TIMErange = timerange;
					 scale(TIME_last_sample, &viewports[0]);
					}
					 npixunit_hor=0;
					 cx_pix_unit = 0;
					 drawall();
					}
			 }
		}

	if(mouse_inside(Exit.top.x,
		 Exit.top.y,
		 Exit.bot.x,
		 Exit.bot.y) || key.ch[0] == 'X')
		{
			mouse_status(stat);
			if(stat.leftButton || key.ch[0] == 'X')
			 {
				first = 1;
				key.ch[0] = 27;
				return 0;
			 }
		}


key.i=0;
	for(i=0;i<MAX_POINTS_IN_MONITOR;i++)
	if(mouse_inside(Label[i].top.x,
		 Label[i].top.y,
		 Label[i].bot.x,
		 Label[i].bot.y))
		{
			mouse_status(stat);
			if(stat.leftButton)
			 {
				while(!get_button_released(BLEFT,stat));
				first = 1;
				if(i>=9)
					key.ch[0] = 'A' + i - 9;
				else
					key.ch[0] = '1' + i;
				break;
			 }
		}

/*
	if(mouse_inside(Up.top.x,
		 Up.top.y,
		 Up.bot.x,
		 Up.bot.y))
		{
			mouse_status(stat);
			if(stat.leftButton)
			 {
					int l=lyzoom-ryzoom;
					lyzoom += npixunit_ver;
					if(lyzoom>viewports[0].bot.y-viewports[0].top.y)
								lyzoom =viewports[0].bot.y-viewports[0].top.y;
					ryzoom = lyzoom-l;
					drawgrid(sample, interv, time_first_sample);
					drawver();
					for(int i=0;i<14;i++)
							if(onoff & (1<<i))
								draw(i);
			 }
		}
	if(mouse_inside(Down.top.x,
		 Down.top.y,
		 Down.bot.x,
		 Down.bot.y))
		{
			mouse_status(stat);
			if(stat.leftButton)
			 {
					int l=lyzoom-ryzoom;
					ryzoom -= npixunit_ver;
					if(ryzoom<0)
								ryzoom = 0;
					lyzoom = ryzoom+l;
					drawgrid(sample, interv, time_first_sample);
					drawver();
					for(int i=0;i<14;i++)
							if(onoff & (1<<i))
								draw(i);
			 }
		}
*/
 }
/*
 if(mouse_inside(viewports[0].top.x,viewports[0].top.y,viewports[0].bot.x,viewports[0].bot.y))
 {
	mouse_status(stat);
	if( stat.where.x!=linex || stat.where.y!=liney )
	{
	 if( linex )
	 {
		hide_pointer();
		mputimage_10(linex,viewports[0].top.y,linex,viewports[0].bot.y+4,ulinex);
		linex = 0;
//		mputimage_10(viewports[0].top.x,liney,viewports[0].bot.x,liney,uliney);
	 }
	}
	if( !linex )
	{
	 mgetimage_10(stat.where.x,viewports[0].top.y,stat.where.x,viewports[0].bot.y+4,ulinex);
//	 mgetimage_10(viewports[0].top.x,stat.where.y,viewports[0].bot.x,stat.where.y,uliney);
	 pline(stat.where.x,viewports[0].top.y,stat.where.x,viewports[0].bot.y+4,White);
//	 pline(viewports[0].top.x,stat.where.y,viewports[0].bot.x,stat.where.y,White);
	 linex = stat.where.x;
	 liney = stat.where.y;


	 long min,max;
	 double dx,dy;
	 int y,ind,v,dxw,dyw,dxv,dyv,l,yminw,ymaxw,ana_dig=0,yw,xw;
	 char buf[10];
	 int *ppix_table;

	 y = viewports[0].top.y+4;
	 for(ind=0;ind<MAX_POINTS_IN_MONITOR;ind++)
		if(onoff & (1<<ind))
		{
						ppix_table =(int *)((int *)pix_table+(MAX_PIXTABLE*ind));

						v=inputs_viewport[ind];
						dxv=viewports[v].bot.x-viewports[v].top.x;
						dyv=viewports[v].bot.y-viewports[v].top.y;
						dxw = Last_sample;

						l=0;
						for(int i=0;i<ind_inputs_group;i++)
						{
						 for(int j=0;j<inputs_group[i].n;j++)
							if(ind==inputs_group[i].inputs[j])
								{
								 l=1;
								 break;
								}
						 if(l) break;
						}
					 if(i!=ind_inputs_group)
					 {
						min=(inputs_group[i].min-1000)/1000;
						max=(inputs_group[i].max+1000)/1000;
					 }
					 else
					 {
						min=0;
						max=100;
					 }

					yminw = min;
					ymaxw = max;
					if(yminw%5) yminw = ((int)(yminw/5)-(yminw<0?1:0) ) * 5;
					if(ymaxw%5) ymaxw = ((int)(ymaxw/5)+1) * 5;
					if(max - ymaxw > 0 && max - ymaxw < 1) ymaxw++;
					if(yminw == ymaxw)
					{
						yminw -= 5;
						ymaxw += 5;
					}
					dyw = ymaxw-yminw;
					if(Last_sample)
					{
							dx = (double)dxv/(double)dxw;
							dy = (double)dyv/(double)dyw;
					}
					else
					{
							dx = 1;
							dy = 1;
					}
					xw = ppix_table[(linex-viewports[v].top.x) * dx];

//					yw = dy * (liney-viewports[v].top.y);
					setcolor(color[ind]);
					ftoa(xw, 5, 1, buf);
					set_semaphore(&screen);
					outtextxy( viewports[0].top.x+4, y, buf);  //48
					y = y + 12;
					clear_semaphore(&screen);

		}

	 display_pointer();
	}
 }
*/
 return 0;
}

long removebuf(long l1)
{
 int n = 0;
 for(int i=0; i<ind_headers; i++)
 {
	 if( n+headers[i].n_sample*headers[i].n_inputs > l1 )
	 {
	  for(int j=0; j<headers[i].n_sample; j++)
	  {
		if( n+headers[i].n_inputs > l1 )
		{
		 headers[i].n_sample -= j;
		 headers[i].prev_header = (long)((long *)headers[i].prev_header + j*headers[i].n_inputs);
		 break;
		}
		n += headers[i].n_inputs;
	  }
	  break;
	 }
	 n += headers[i].n_sample*headers[i].n_inputs;
 }
 ind_headers -= i;
 memcpy(headers, &headers[i], sizeof(Header_amon)*ind_headers);
 l1=0;

 for(i=0; i<ind_headers; i++)
 {
  headers[i].prev_header = (long)((long *)headers[i].prev_header - n);
  l1 += (long)headers[i].n_sample*(long)headers[i].n_inputs;
 }
 memmove(mon_table, mon_table+n, l1*4);
 return l1;
}

int scale(unsigned long timelastsample, hot_box *viewport)
{
//				 sample=psample(&interv, current_mon-1);
	long min,max;
	long linterval,timer;
	if(timerange) timer = timerange;
	else  timer =  Time_last_sample - Time_first_sample;

//	if(timelastsample>0)
	{
	Time_last_sample = timelastsample ;
	Time_first_sample = timelastsample - timer;
//	if(Time_first_sample<0) Time_first_sample=0;
	interval=whatinterv(&Time_first_sample,&Time_last_sample);
	do
	{
	 if(Time_first_sample < Time_last_sample-(viewport[0].bot.x-viewport[0].top.x+1)*interval)
			Time_first_sample	= Time_last_sample-(viewport[0].bot.x-viewport[0].top.x+1)*interval ;
	 if(Time_first_sample < TIME_first_sample)
			Time_first_sample = Time_last_sample-((Time_last_sample-TIME_first_sample)/interval)*interval;
	 interval=whatinterv(&Time_first_sample,&Time_last_sample);
	 sample = (Time_last_sample-Time_first_sample)/interval+1;
	 Time_first_sample = Time_last_sample-(sample-1)*interval ;
	 linterval=interval;
	 interval=whatinterv(&Time_first_sample,&Time_last_sample);
	} while(interval!=linterval);

	 time_first_sample = Time_first_sample;
	 time_last_sample = Time_last_sample;

	 First_sample = FIRST_sample = 0;
	 Last_sample = LAST_sample = sample-1;
	 if(interval!=lastinterval)
	 {
		for(int i=0;i<ind_inputs_group;i++)
		{
		 cx_pix_unit = 0;
		 time_sample_last_read = 0x7FFFFFFF;
		 min = 10000000L;
		 max = -10000000L;
		 for(int k=0;k<inputs_group[i].n;k++)
			 minmax(1,inputs_group[i].inputs[k],&min,&max);
		 inputs_group[i].min=min;
		 inputs_group[i].max=max;
		}
		lastinterval = interval;
	 }
	}
}


int GGraph::draw(int ind)
{
						long min,max;
						float value;
						double dx,dy;
						int x3,y3,x2,y2,x1,y1,x,y,v,dxw,dyw,dxv,dyv,l,yminw,ymaxw,ana_dig=0,on_off;
						long first;
						char xxx[3];
						int *ppix_table=(int *)((int *)pix_table+(MAX_PIXTABLE*ind));
//						Point_info point_info;

//						memcpy(&point_info.point_name,&amon_inputs[ind],2);
//						get_point_info(&point_info, &des, &label);

						v=inputs_viewport[ind];
//!!						t=mon_table;
//						t = (float *)ptr_panel->analog_mon[current_mon-1].data_segment;
						dxv=viewports[v].bot.x-viewports[v].top.x;
						dyv=viewports[v].bot.y-viewports[v].top.y;
						dxw = Last_sample;

//						xminw=First_sample;
//						xmaxw=sample;
//						xminv=viewports[v].top.x;
//						yminv=480-viewports[v].bot.y;

						l=0;
						for(int i=0;i<ind_inputs_group;i++)
						{
						 for(int j=0;j<inputs_group[i].n;j++)
							if(ind==inputs_group[i].inputs[j])
								{
								 l=1;
								 break;
								}
						 if(l) break;
						}
					 if(i!=ind_inputs_group)
					 {
						min=(inputs_group[i].min-1000)/1000;
						max=(inputs_group[i].max+1000)/1000;
					 }
					 else
					 {
						min=0;
						max=100;
					 }

					yminw = min;
					ymaxw = max;
					if(yminw%5) yminw = ((int)(yminw/5)-(yminw<0?1:0) ) * 5;
					if(ymaxw%5) ymaxw = ((int)(ymaxw/5)+1) * 5;
					if(max - ymaxw > 0 && max - ymaxw < 1) ymaxw++;
					if(yminw == ymaxw)
					{
						yminw -= 5;
						ymaxw += 5;
					}
					dyw = ymaxw-yminw;

					if(zoom)
					{
						min = ryzoom/((float)dyv/(float)dyw) + yminw;
						max = lyzoom/((float)dyv/(float)dyw) + yminw;
						yminw = min;
						ymaxw = max;
						if(yminw%5) yminw = ((int)(yminw/5)-(yminw<0?1:0) ) * 5;
						if(ymaxw%5) ymaxw = ((int)(ymaxw/5)+1) * 5;
						if(max - ymaxw > 0 && max - ymaxw < 1) ymaxw++;
						if(yminw == ymaxw)
						{
							yminw -= 5;
							ymaxw += 5;
						}
					}

					if(inputs_viewport[ind])
					{
							ymaxw = 1;
							yminw=0;
							ana_dig = 1;
					}
					dyw = ymaxw-yminw;

					setcolor(color[ind]);

//						if(!ptablex[ind]) ptablex[ind] = new unsigned[1024];
//						if(!ptabley[ind]) ptabley[ind] = new unsigned[1024];
//						ind_ptable[ind] = 0;
						hide_pointer();
						setviewport(viewports[v].top.x,viewports[v].top.y,viewports[v].bot.x,viewports[v].bot.y,1);

//!!						l = First_sample*ptr_panel->analog_mon[current_mon-1].num_inputs+ind;
						if(Last_sample)
						{
							dx = (double)dxv/(double)dxw;
							dy = (double)dyv/(double)dyw;
						}
						else
						{
							dx = 1;
							dy = 1;
						}

					 if(!ana_dig)
					 {
						first = First_sample-1;
						do
						{
						 first++;
						 value=readvalue(first,ind);
						} while (value==-10000. && first<=Last_sample);
//						 x=(int)(dx*(first-xminw)+0.5);
						 x=dx*first+0.5;
						 y=dy*(value-yminw)+0.5;
						 x1=x;y1 = y;
						 x2 = npix_sample_hor*first+0.5;
//						int y=(int)((float)dyv/(float)dyw*(t[l]-yminw)+0.5);
// set_semaphore(&screen);
						x3 = x + 4;
						y3 = dyv-y - 4;
						setcolor(Black);
						outtextxy(x2+4, dyv - (*ppix_table)-4, "Û");
						setcolor(color[ind]);
						moveto(x,dyv-y);
//						int x=dxv/dxw*(First_sample-xminw)+xminv;
//						int y=(float)dyv/(float)dyw*(t[l]-yminw)+yminv;
//						moveto(x,480-y);
//						ptablex[ind][ind_ptable[ind]] = x;
//						ptabley[ind][ind_ptable[ind]++] = 480-y;
						for(i=first+1;i<=Last_sample;i++)
						{
//!!						 l = i*ptr_panel->analog_mon[current_mon-1].num_inputs+ind;

//						 int x=dxv/dxw*(i-xminw)+xminv;
//						 int y=(float)dyv/(float)dyw*(t[l]-yminw)+yminv;
//						 lineto(x,480-y);

//!!						 x=(int)(dx*(i-xminw)+0.5);
						 x=dx*i+0.5;
						 if((value = readvalue(i,ind))!=-10000.)
						 {
							y=dy*(value-yminw)+0.5;
//						 int y=(int)((float)dyv/(float)dyw*(t[l]-yminw)+0.5);
							if(cxy_pix_unit)
							{
							 setcolor(Black);
							 moveto(x2,dyv - (*ppix_table));
							 x2 = npix_sample_hor*i+0.5;
							 if(x2<=xlast)
								 lineto(x2,dyv - (*(ppix_table+1)));
							 setcolor(color[ind]);
							 moveto(x1,dyv - y1);
							}
							*ppix_table++ = y1;
							y1 = y;

							lineto(x,dyv-y);
						 }
						 x1 = x;
//						 ptablex[ind][ind_ptable[ind]] = x;
//						 ptabley[ind][ind_ptable[ind]++] = 480-y;
						}
						*ppix_table++ = y1;
						xlast = x1;
						moveto(x3,y3);
						setcolor(Black);
						outtextxy(x3, y3, "Û");
						setcolor(color[ind]);
						outtextxy(x3, y3, itoa(ind + 1, xxx,10));
					 }
					 else
					 {
//						if(!ind_headers)
						{
//							dx = (float)dxv/(float)(Time_last_sample - Time_first_sample);
							dx = dx/(double)interval;
//							dy = (double)dyv/(double)dyw;
							dy = dyv;
						}
						IND = ind;
						TIME_READVALUE_DIG = -1;
						if ( (on_off=(int)readvaluedig()) >= 0)
						{
						x=0;
//						y=on_off?(int)dy:0;
//						x1=x;y1 = y;
//						x2 = npix_sample_hor*first+0.5;
						moveto(x,on_off?0:dyv);
						TIME_READVALUE_DIG = 0;

//						int y=(int)((float)dyv/(float)dyw*(t[l]-yminw)+0.5);
// set_semaphore(&screen);
//						int x=dxv/dxw*(First_sample-xminw)+xminv;
//						int y=(float)dyv/(float)dyw*(t[l]-yminw)+yminv;
//						moveto(x,480-y);
//						ptablex[ind][ind_ptable[ind]] = x;
//						ptabley[ind][ind_ptable[ind]++] = 480-y;
						while( (first=readvaluedig()) >= 0)
						{
//						 int x=dxv/dxw*(i-xminw)+xminv;
//						 int y=(float)dyv/(float)dyw*(t[l]-yminw)+yminv;
//						 lineto(x,480-y);
						 x=dx*(first-Time_first_sample)+0.5;
//						 y=(on_off?(int)dy:0);
//						 int y=(int)((float)dyv/(float)dyw*(t[l]-yminw)+0.5);
/*
							if(cxy_pix_unit)
							{
							 setcolor(Black);
							 moveto(x2,dyv - (*ppix_table));
							 x2 = npix_sample_hor*i+0.5;
							 if(x2<=xlast)
								 lineto(x2,dyv - (*(ppix_table+1)));
							 setcolor(color[ind]);
							 moveto(x1,dyv - y1);
							}
							*ppix_table++ = y1;
							y1 = y;
*/
						 lineto(x,on_off?0:dyv);
						 on_off = ONOFF;
//						 y=(on_off?(int)dy:0);
						 lineto(x,on_off?0:dyv);
						}
						 x=dxv;
//						 y=(on_off?(int)dy:0);
						 lineto(x,on_off?0:dyv);
						}
					 }
						setviewport(0,0,maxx,maxy,1);
//clear_semaphore(&screen);
/*
					if(cxy_pix_unit)
					{
						setcolor(Black);
						moveto(x2,dyv - (*ppix_table));
						while(x2<xlast)
						{
							 x2 = npix_sample_hor*(i++) + 0.5;
							 lineto(x2,dyv - (*(ppix_table+1)));
							 *ppix_table++ = y1;
						}
					}
*/
						display_pointer();
 }

long readvaluedig(void)
{
 int k,i,k1;
 char onoff, lonoff;
 Header_dmon *hdig;

 if(TIME_READVALUE_DIG < 0)
 {
	TIMESAMPLE = Time_first_sample;
	i_read_dig = 0;  // headers_dig number
	j_read_dig = 0;
	k_read_dig = 0;  // point number
	hdig = headers_dig;
	for(i=0;i<ind_headers_dig;hdig++,i++)
	{
	 TIMEFIRSTNEXTHEADER = 0x7FFFFFFF;
	 for(k=0; k < (int)hdig->n_inputs; k++)
		if(amon_inputs[IND]==hdig->inputs[k]) break;
	 if(k == (int)hdig->n_inputs) continue;
   if( !hdig->n_sample[k] ) continue;
	 if (TIMESAMPLE <= hdig->time_last_sample[k])
	 {
		if(i<ind_headers_dig-1)
		{
		 for(k1=0; k1 < (int)((hdig+1)->n_inputs); k1++)
			if(amon_inputs[IND]==(hdig+1)->inputs[k1]) break;
		 if( !(hdig+1)->n_sample[k1] ) continue;
		 if(k1 < (int)((hdig+1)->n_inputs))
		 {
			TIMEFIRSTNEXTHEADER=*((long *)((hdig+1)->prev_header)+(hdig+1)->offset[k1]);
			if( TIMESAMPLE >= TIMEFIRSTNEXTHEADER )
				continue;
		 }
		}
		break;
	 }
	}
	k_read_dig = k;
	if(i)
	{
	 lonoff = !(hdig-1)->onoff[k];
	 for(int j=0; j<(hdig-1)->n_sample[k]; j++)
		 lonoff = !lonoff;
	}
	if(i==ind_headers_dig)
	{
	 if(!ind_headers_dig)	return -1L;
	 return lonoff;
	}
	i_read_dig = i;
	ONOFF = !hdig->onoff[k];
//	if(!i) lonoff = hdig->onoff[k];
	lonoff = hdig->onoff[k];
	for(int j=0; j<hdig->n_sample[k]; j++)
	{
	 if( TIMESAMPLE < *((long *)(hdig->prev_header)+hdig->offset[k]+j) )
	 {
//		TIMESAMPLE = *((long *)(headers_dig[i].prev_header)+headers_dig[i].offset[k]+j);
		if (!j) ONOFF = lonoff;
		j_read_dig = j;
		break;
	 }
	 ONOFF = !ONOFF;
	}
	return ONOFF;
 }
 if(TIME_READVALUE_DIG == 0)
 {
	if (TIMESAMPLE > headers_dig[ind_headers_dig-1].time_last_sample[k_read_dig]) return -1L;

et1:
	hdig = &headers_dig[i_read_dig];
	if(	j_read_dig >= hdig->n_sample[k_read_dig])
	{
	 for(i=++i_read_dig;i<ind_headers_dig;i++)
	 {
		TIMEFIRSTNEXTHEADER = 0x7FFFFFFF;
		for(k=0; k < (int)headers_dig[i].n_inputs; k++)
		 if(amon_inputs[IND]==headers_dig[i].inputs[k]) break;
		if(k == (int)headers_dig[i].n_inputs) continue;
		if( !headers_dig[i].n_sample[k] ) continue;
		TIMESAMPLE	= *((long *)(headers_dig[i].prev_header)+headers_dig[i].offset[k]);
		if(i<ind_headers_dig-1)
		{
		 for(k1=0; k1 < (int)(headers_dig[i+1].n_inputs); k1++)
			if(amon_inputs[IND]==headers_dig[i+1].inputs[k1]) break;
		 if( !headers_dig[i+1].n_sample[k1] ) continue;
		 if(k1 < (int)(headers_dig[i+1].n_inputs))
		 {
			TIMEFIRSTNEXTHEADER=*((long *)(headers_dig[i+1].prev_header)+headers_dig[i+1].offset[k1]);
			if( TIMESAMPLE >= TIMEFIRSTNEXTHEADER )
				continue;
		 }
		}
		break;
	 }
	 if(i==ind_headers_dig) return -1L;
	 i_read_dig = i;
	 k_read_dig = k;
	 j_read_dig = 0;
	 hdig = &headers_dig[i];
//	 ONOFF = hdig->onoff[k];
	}
//	if(	j_read_dig++ < headers_dig[i_read_dig].inputs[k_read_dig])
	{
		TIMESAMPLE	= *((long *)(hdig->prev_header)+hdig->offset[k_read_dig]+j_read_dig);
		if( TIMESAMPLE  > Time_last_sample ) return -1;
		if( TIMESAMPLE  >= TIMEFIRSTNEXTHEADER )
		{
			j_read_dig = hdig->n_sample[k_read_dig];
			goto et1;
		}

		if(j_read_dig) ONOFF = !ONOFF;
		else ONOFF = hdig->onoff[k_read_dig];
		j_read_dig++;
		return ( TIMESAMPLE );
	}
 }

/*
 if(TIME_READVALUE_DIG)
 {
	for(i=0;i<ind_headers_dig;i++)
	{
	 for(k=0; k < (int)headers_dig[i].n_inputs; k++)
		if(amon_inputs[IND]==headers_dig[i].inputs[k]) break;
	 if(k == (int)headers_dig[i].n_inputs) continue;
	 if (TIME_READVALUE_DIG <= headers_dig[i].time_last_sample[k]) break;
	}
	if(i==ind_headers_dig) return -1L;

// for(j=j_read;j<headers[i].n_sample;j++)
	onoff = headers_dig[i].onoff[k];
	for(int j=0; j<headers_dig[i].n_sample[k]; j++)
	{
	 if( TIME_READVALUE_DIG < *((long *)(headers_dig[i].prev_header)+headers_dig[i].offset[k]+j) )
	 {
		break;
	 }
	 onoff = !onoff;
	}
// i_read = i;
// j_read = j-1;
// time_sample_last_read = timesample;
	return ((long)onoff);
 }
*/
}

float readvalue(long l, int ind)
{
asm push es;
 register int j;
 timesample_read = Time_first_sample + l * interval;
 if(timesample_read < time_sample_last_read)
 {
	i_read = 0;
	j_read = 0;
 }
 for(int i=i_read;i<ind_headers;i++)
	if (timesample_read <= headers[i].time_last_sample) break;
 if( i != i_read ) j_read = 0;
 timefirst_read = headers[i].time_last_sample - (headers[i].n_sample-1)*headers[i].interval;
 for(j=0;j<headers[i].n_inputs;j++)
 {
	if(amon_inputs[ind]==headers[i].inputs[j])
	{
	 ind = j;
	 break;
	}
 }
 if(j==headers[i].n_inputs)
 {
	asm pop es;
	return -10000.;
 }
 for(j=j_read;j<headers[i].n_sample;j++)
 {
	l1_read = (long)j * headers[i].interval;
	l1_read += timefirst_read;
	if(timesample_read == l1_read)
	{
//		value_read =*((float *)headers[i].prev_header+(j*headers[i].n_inputs+ind));
		value_read =((float)*((long *)headers[i].prev_header+(j*headers[i].n_inputs+ind)))/1000.;
		break;
	}
	else
		if(timesample_read < l1_read)
		{
//			value1_read = *((float *)headers[i].prev_header+((j-1)*headers[i].n_inputs+ind));
//			value2_read = *((float *)headers[i].prev_header+((j)*headers[i].n_inputs+ind));
//!!			value1_read = (float)(*((long *)headers[i].prev_header+((j-1)*headers[i].n_inputs+ind)))/1000;
//!!			value2_read = (float)(*((long *)headers[i].prev_header+((j)*headers[i].n_inputs+ind)))/1000;
//!!			value_read = (value2_read-value1_read)*(timesample_read-(l1_read-headers[i].interval))/headers[i].interval + value1_read;
			value1_read = *((long *)headers[i].prev_header+((j?j-1:j)*headers[i].n_inputs+ind));
			value2_read = *((long *)headers[i].prev_header+((j)*headers[i].n_inputs+ind));
			value_read = ((float)((value2_read-value1_read)*(timesample_read-(l1_read-headers[i].interval))/headers[i].interval + value1_read))/1000.;
			break;
		}
 }
 i_read = i;
 if(j)
	 j_read = j-1;
 else
	 j_read = 0;
 time_sample_last_read = timesample_read;

asm pop es;
 if(value_read >= -100. && value_read < 1000.)
	 return value_read;
 else
	 return 0;
}

long readvalue(long l, int ind, int type)
{
asm push es;
 register int j;
 long value_read;
 timesample_read = Time_first_sample + l * interval;
 if(timesample_read < time_sample_last_read)
 {
	i_read = 0;
	j_read = 0;
 }
 for(int i=i_read;i<ind_headers;i++)
	if (timesample_read <= headers[i].time_last_sample) break;
 if( i != i_read ) j_read = 0;
 timefirst_read = headers[i].time_last_sample - (headers[i].n_sample-1)*headers[i].interval;
 for(j=0;j<headers[i].n_inputs;j++)
 {
	if(amon_inputs[ind]==headers[i].inputs[j])
	{
	 ind = j;
	 break;
	}
 }
 if(j==headers[i].n_inputs)
 {
	asm pop es;
	return -10000000L;
 }
 for(j=j_read;j<headers[i].n_sample;j++)
 {
	l1_read = (long)j * headers[i].interval;
	l1_read += timefirst_read;
	if(timesample_read == l1_read)
	{
//		value_read =*((float *)headers[i].prev_header+(j*headers[i].n_inputs+ind));
		value_read =(*((long *)headers[i].prev_header+(j*headers[i].n_inputs+ind)));
		break;
	}
	else
		if(timesample_read < l1_read)
		{
//			value1_read = *((float *)headers[i].prev_header+((j-1)*headers[i].n_inputs+ind));
//			value2_read = *((float *)headers[i].prev_header+((j)*headers[i].n_inputs+ind));
//!!			value1_read = (float)(*((long *)headers[i].prev_header+((j-1)*headers[i].n_inputs+ind)))/1000;
//!!			value2_read = (float)(*((long *)headers[i].prev_header+((j)*headers[i].n_inputs+ind)))/1000;
//!!			value_read = (value2_read-value1_read)*(timesample_read-(l1_read-headers[i].interval))/headers[i].interval + value1_read;
			value1_read = *((long *)headers[i].prev_header+((j?j-1:j)*headers[i].n_inputs+ind));
			value2_read = *((long *)headers[i].prev_header+((j)*headers[i].n_inputs+ind));
			value_read = (((value2_read-value1_read)*(timesample_read-(l1_read-headers[i].interval))/headers[i].interval + value1_read));
			break;
		}
 }
 i_read = i;
 if(j)
	 j_read = j-1;
 else
	 j_read = 0;
 time_sample_last_read = timesample_read;

asm pop es;
 if(value_read >= -100000L && value_read < 1000000L)
	 return value_read;
 else
	 return 0;
}

long psample(long *interv, Str_monitor_point *amon)
{
 unsigned long i;
 switch (amon->unit) {
	case 0: i = (long)amon->max_time_length*60L;
					break;
	case 1: i = (long)amon->max_time_length*3600L;
					break;
	case 2: i = (long)amon->max_time_length*3600L*24L;
					break;
	}
 *interv =  (amon->hour_interval_time*3600L+
							amon->minute_interval_time*60L+
							amon->second_interval_time);
 return i / *interv;
}

int printrange(int topx,int topy, long time_first_sample, long time_last_sample, char *p)
{
 long l,r,m=0,h=0,d=0,o=0;
 char b[10];
 if(!p)
 {
	setfillstyle(SOLID_FILL, Black);
	bar(topx,topy,topx+30*8,topy+8);
 }
 else
	p[0] = 0;
// if(timerange) r = timerange;
// else r = Time_last_sample - Time_first_sample;
 r = time_last_sample - time_first_sample;
 o = r/(3600L*24L*30L);
 r = r - o*(3600L*24L*30L);
 d = r/(3600L*24L);
 r = r - d * (3600L*24L);
 h = r/(3600L);
 r = r - h * (3600L);
 m = r/(60L);

 if(!mode_text)
		moveto(topx,topy);

 if(o)
 {
	if(!p)
	{
	 outtext(timerangetext_mo);
	 outtext(ltoa(o,b,10));
	}
	else
	{
	 strcpy(p,ltoa(o,b,10));
	 strcat(p," mo ");
	}
 }
 if(d)
 {
	if(!p)
	{
	 outtext(timerangetext_days);
	 outtext(ltoa(d,b,10));
	}
	else
	{
	 strcat(p,ltoa(d,b,10));
	 strcat(p," d ");
	}
 }
 if(h)
 {
	if(!p)
	{
	 outtext(timerangetext_hours);
	 outtext(ltoa(h,b,10));
	}
	else
	{
	 strcat(p,ltoa(h,b,10));
	 strcat(p," h ");
	}
 }
 if(m)
 {
	if(!p)
	{
	 outtext(timerangetext_min);
	 outtext(ltoa(m,b,10));
	}
	else
	{
	 strcat(p,ltoa(m,b,10));
	 strcat(p," m");
	}
 }
}

int addmem(int ind, long interv, int sample, long time_last_sample, char *pmon_table, long **pmem_table, char *last_mem_block, int *nsample_mem_block, Header_amon *headers, int *ind_headers )
{
 unsigned k;
 int j,v = 0;
// long *t = (long *)ptr_panel->analog_mon[ind].data_segment;
 long *t = (long *)ptr_panel->monitor_work_data[ind].data_segment;

	 if(headers[(*ind_headers)-1].interval == interv)
		 if(headers[(*ind_headers)-1].n_inputs == ptr_panel->analog_mon[ind].anum_inputs)
		 {
			for(int i=0;i<headers[(*ind_headers)-1].n_inputs;i++)
			{
			 for(j=0;j<headers[(*ind_headers)-1].n_inputs;j++)
				{
				 if(headers[(*ind_headers)-1].inputs[i] == ptr_panel->analog_mon[ind].inputs[j]) break;
				}
			 if(j==headers[(*ind_headers)-1].n_inputs) break;
			}
			if(j!=headers[(*ind_headers)-1].n_inputs)
			{
			 time_last_sample_mem = headers[(*ind_headers)-1].time_last_sample;
			 headers[(*ind_headers)-1].time_last_sample = time_last_sample;
			 headers[(*ind_headers)-1].n_sample += sample;
			 memcpy(pmon_table, t,sample * ptr_panel->analog_mon[ind].anum_inputs * 4);
			 v=1;
			 *last_mem_block = 2;
			 *nsample_mem_block = sample;
			 *pmem_table = (long *)(pmon_table+sample * ptr_panel->analog_mon[ind].anum_inputs * 4);
			}
		 }
 return v;
}
//type = 1 noile valori, 0 toata mem
int newmem(int ind, int ssample, long ttime_last_sample, char *pmon_table, long **pmem_table, int *index_last_value, char *last_mem_block, int *nsample_mem_block, Header_amon *headers, int *ind_headers, int type)
{
 long l,offset;
 int n;
 long *t = (long *)ptr_panel->monitor_work_data[ind].data_segment;

	 if(type)
	 {
		 headers[(*ind_headers)-1].time_last_sample = ttime_last_sample;
		 if(ssample >= *index_last_value )
		 {
			 n = ssample - *index_last_value;
			 headers[(*ind_headers)-1].n_sample += n;
		 }
		 else
		 {
			 n = MAX_SAMPLE_MEM - *index_last_value;
			 headers[(*ind_headers)-1].n_sample += n;

		 }
		 l = (*index_last_value)*ptr_panel->analog_mon[ind].anum_inputs;
		 memcpy(*pmem_table, &t[l], n * ptr_panel->analog_mon[ind].anum_inputs * 4);
		 *pmem_table += n * ptr_panel->analog_mon[ind].anum_inputs;

		 if(ssample < *index_last_value )
		 {
			 memcpy(*pmem_table, t, ssample * ptr_panel->analog_mon[ind].anum_inputs * 4);
			 *pmem_table += ssample * ptr_panel->analog_mon[ind].anum_inputs;
		 }
		 *index_last_value = ssample;
		 return n;
	 }

	 if(ssample || (ptr_panel->monitor_work_data[ind].saved && !(*ind_headers)) || type)
	 {
	 (*ind_headers)++;
	 headers[(*ind_headers)-1].time_last_sample = ttime_last_sample;
	 headers[(*ind_headers)-1].n_sample = ssample;
	 headers[(*ind_headers)-1].n_inputs = ptr_panel->analog_mon[ind].anum_inputs;
	 memcpy(&headers[(*ind_headers)-1].inputs[0],&ptr_panel->analog_mon[ind].inputs[0],MAX_POINTS_IN_MONITOR*sizeof(Point_Net));
	 psample(&headers[(*ind_headers)-1].interval, &ptr_panel->analog_mon[ind]);
	 headers[(*ind_headers)-1].prev_header = (long)pmon_table;
	 if(ptr_panel->monitor_work_data[ind].saved && !((*ind_headers)-1))
	 {
		 headers[(*ind_headers)-1].n_sample = MAX_SAMPLE_MEM;
		 offset = (MAX_SAMPLE_MEM-ssample) * ptr_panel->analog_mon[ind].anum_inputs * 4;
		 l = ssample*ptr_panel->analog_mon[ind].anum_inputs;
		 memcpy(pmon_table, &t[l], offset);
		 pmon_table += offset;
	 }
	 memcpy(pmon_table, t,ssample * ptr_panel->analog_mon[ind].anum_inputs * 4);
	 *last_mem_block = 1;
	 *nsample_mem_block = headers[(*ind_headers)-1].n_sample;
	 *index_last_value = ssample;
	 *pmem_table = (long *)(pmon_table + ssample * ptr_panel->analog_mon[ind].anum_inputs*4);
	 return ssample;
	 }
 return 0;
}

char *newnetmem(int ind, int *length, char *serptr)
{
asm push es;
 long l,offset,time_last_sample;
 int n,ind_last_value,sample;
// HANDLE handle=0;

 ind_last_value = ind >> 7;
 ind -= ind_last_value << 7;
// ind_last_value--;
 long *t = (long *)ptr_panel->monitor_work_data[ind].data_segment;

 sample = ptr_panel->monitor_work_data[ind].head_index;
 time_last_sample = ptr_panel->monitor_work_data[ind].last_sample_time;

 char *p;
 if(serptr)
 {
	p = serptr;
	if(sample<ind_last_value || nr_mon_save)
	{
		p[0] = 0xff; p[1] = 0xff;
		*length = 2;
		asm pop es;
		return p;
	}
 }
 else
 {
	return 0;
//	exit(1);
/*
	set_semaphore_dos();
	p = new char[1000];
	clear_semaphore_dos();
*/
//	mfarmalloc((char far **)&p, 1000 , handle);
 }
 char *q = p;
 memcpy(p, &sample, 2);
 memcpy(p+2, &time_last_sample, 4);

		 if(sample >= ind_last_value )
		 {
			 n = sample - ind_last_value;
		 }
		 else
		 {
			 n = MAX_SAMPLE_MEM - ind_last_value;
		 }

		memcpy(p+6, &n, 2);
		n *= ptr_panel->analog_mon[ind].anum_inputs;
		memcpy(p+8, &n, 2);

		l = ind_last_value*ptr_panel->analog_mon[ind].anum_inputs;
		p += 10;
		memcpy(p, &t[l], n * 4);
		p += n * 4;
		if(sample < ind_last_value )
		 {
			 memcpy(p, t, sample * ptr_panel->analog_mon[ind].anum_inputs * 4);
			 p += sample * ptr_panel->analog_mon[ind].anum_inputs * 4;
		 }
		*length = p-q;
asm pop es;
		return q;
}
//  nsample_mem_dig_block_loc, l, header_dmon, l values
char *updatenetmemdig(int ind, int *length, char *serptr=NULL)
{
asm push es;
//	HANDLE handle;
	long l, interv;
	int	*nsample_mem_dig_block_loc;
	int j=0;
	Header_dmon *header_dmon;
	long *ptable;     //  = new long[1000];
	if(serptr)
		ptable = (long *)serptr;
	else
	{
	 set_semaphore_dos();
	 ptable = new long[1000];
	 clear_semaphore_dos();
	//	mfarmalloc((char far **)&ptable, 4*1000, handle);
	}
	nsample_mem_dig_block_loc = (int *)ptable;
	header_dmon	= (Header_dmon *)(((char *)ptable)+6);
	ptable = (long *)((char *)ptable + 6 + sizeof(Header_dmon));
	psample(&interv, &ptr_panel->analog_mon[ind]);
	*nsample_mem_dig_block_loc = 0;
	l = 0;
set_semaphore(&read_mon_flag);
 if(nsample_mem_dig_mon[ind])
 {
	int l1;
//	*nsample_mem_dig_block_loc = nsample_mem_dig_mon[ind];

	header_dmon->prev_header = 0;
	header_dmon->n_inputs = ptr_panel->analog_mon[ind].num_inputs-ptr_panel->analog_mon[ind].anum_inputs;
	memcpy(header_dmon->inputs,&ptr_panel->analog_mon[ind].inputs[ptr_panel->analog_mon[ind].anum_inputs],header_dmon->n_inputs*sizeof(Point_Net));
	for(int i=0;i<ptr_panel->analog_mon[ind].num_inputs-ptr_panel->analog_mon[ind].anum_inputs;i++)
	{
	 if(ptr_panel->monitor_work_data[ind].start_index_dig[i] != 0x0FFFF)
	 {
		l1 = 0;
		header_dmon->offset[i] = l;
		for(j=ptr_panel->monitor_work_data[ind].start_index_dig[i]; j != ptr_panel->monitor_work_data[ind].end_index_dig[i]; j = heap_dmon[j].next)
		{
		 *ptable++ = heap_dmon[j].time;
		 l1++;
		}
		*ptable++ = heap_dmon[j].time;
		header_dmon->time_last_sample[i] = heap_dmon[j].time;
		l1++;
		l += l1;
		header_dmon->n_sample[i] = l1;
		header_dmon->onoff[i] = heap_dmon[ptr_panel->monitor_work_data[ind].start_index_dig[i]].onoff;
	 }
	}
	*nsample_mem_dig_block_loc = l;
 }
clear_semaphore(&read_mon_flag);

	memcpy(nsample_mem_dig_block_loc+1,&l,4);
 *length = 6 + sizeof(Header_dmon) + l*4;
 asm pop es;
 return (char *)nsample_mem_dig_block_loc;
}


int	updatememdig(int ind, int panel, int network, int type)
{
asm push es;
//	HANDLE handle=0;
	long l,l1,nsample, interv, f,max_file,nbytes;
	unsigned long t[3];
	Header_dmon *header_dmon;
	int	nsample_mem_dig_block_loc;
	int n,j,i,first,k;
	char *p,*pmon_table;
	Mini_Monitor_Block *mb;
	max_file=MAX_MEM_DIG_BUF;
	psample(&interv, &ptr_panel->analog_mon[ind]);
	long *ptable = (long *)mem_dmon_table;

	l=0;
	if(type)
	{
	 mfarmalloc((char far **)&p, MAX_MEM_DIG_BUF+400+MAX_HEADERS_DMON*sizeof(Header_dmon));
	 if(!p)
	 {
		 asm pop es;
		 return ERROR_COMM;
	 }
	 Delay(500);
	 if( panel_info1.panel_type == T3000 )
	 {
		if(net_call(23, ind|0x8000, p, 0, panel, network)!=SUCCESS)
		{
		 if(net_call(23, ind|0x8000, p, 0, panel, network)!=SUCCESS)
		 {
//		if (handle) mfarfree(handle);
			mfarfree(p);
			asm pop es;
			return ERROR_COMM;
		 }
		}
		memcpy(&nsample_mem_dig_block_loc, p, 2);
		memcpy(&l, p+2, 4);
		header_dmon = (Header_dmon *)(p+6);
		if( nsample_mem_dig_block_loc < nsample_mem_dig_block)
		{
			mfarfree(p);
			asm pop es;
			return ERROR_COMM;
		}
		if(!nsample_mem_dig_block_loc || nsample_mem_dig_block_loc==nsample_mem_dig_block)
		{
			mfarfree(p);
			asm pop es;
			return SUCCESS;
		}
		if(!nsample_mem_dig_block)
		{
			ind_headers_dig++;
		}
		nsample_mem_dig_block = nsample_mem_dig_block_loc;
		memcpy(&headers_dig[ind_headers_dig-1], header_dmon, sizeof(Header_dmon));
		headers_dig[ind_headers_dig-1].prev_header = (long)ptable;
		memcpy(ptable, p + 6 + sizeof(Header_dmon), l*4);
//		delete p;
		mfarfree(p);
	}
	else
	{
			t[0] = 400+MAX_HEADERS_DMON*sizeof(Header_dmon);
			t[1] = 0;
			for(i = 0; i<headers_dig[ind_headers_dig-1].n_inputs; i++)
			{
				if( headers_dig[ind_headers_dig-1].time_last_sample[i] > t[1] )
					 t[1] = headers_dig[ind_headers_dig-1].time_last_sample[i];
			}
			t[2] = timesec1970 + timestart;
			n=0;
			if(net_call(UPDATEMEMMONITOR_T3000, (DIGITALDATA<<8)+ind, p, (unsigned int *)&n, panel, network, NETCALL_SIGN, 40,
					NULL, NULL, (char *)t, 12)!=SUCCESS)
			{
			 mfarfree(p);
			 asm pop es;
			 return ERROR_COMM;
			}
			if( n == 2 )
			{
			 mfarfree(p);
			 asm pop es;
			 return ERROR_COMM;
			}
			if( ind_headers_dig == 1 ) ind_headers_dig++;
			mb = (Mini_Monitor_Block *)p;
			pmon_table = (char *)p;
			l = 0;
			l1 = 0;
			headers_dig[ind_headers_dig-1].prev_header=(long)mem_dmon_table;
			headers_dig[ind_headers_dig-1].n_inputs = mb->no_points;
			for(i = 0; i<headers_dig[0].n_inputs; i++)
			{
				headers_dig[ind_headers_dig-1].offset[i] = l;
				l1=0;
				first = 1;
				for(nbytes=0; nbytes<n;)
				{
				 for(k=0;k<MAX_DIGITAL_SAMPLES_PER_BLOCK;k++)
				 {
					 if( mb->data.digital[k].point_no == i )
					 {
						 if(first)
						 {
							 headers_dig[ind_headers_dig-1].onoff[i] = !mb->data.digital[k].value;
							 first=0;
						 }
						 *ptable++ = mb->data.digital[k].time;
						 l1++;
					 }
				 }
				 nbytes += ( sizeof(Mini_Monitor_Block)-5*MAX_DIGITAL_SAMPLES_PER_BLOCK+5*mb->index );
				 mb = (Mini_Monitor_Block *)(((char *)mb)+sizeof(Mini_Monitor_Block)-5*MAX_DIGITAL_SAMPLES_PER_BLOCK+5*mb->index);
				}
				l += l1;
				headers_dig[ind_headers_dig-1].n_sample[i] = l1;
				headers_dig[ind_headers_dig-1].time_last_sample[i] = *(ptable-1);
			}
			mfarfree(p);
	}
 }
 else
 {
	if(!nsample_mem_dig_mon[ind] || nsample_mem_dig_mon[ind]==nsample_mem_dig_block )  return SUCCESS;
	if(!nsample_mem_dig_block)
	{
		ind_headers_dig++;
	}
//	headers_dig[ind_headers_dig-1].prev_header = (long)ptable ;
	headers_dig[ind_headers_dig-1].n_inputs = ptr_panel->analog_mon[ind].num_inputs-ptr_panel->analog_mon[ind].anum_inputs;
	memcpy(headers_dig[ind_headers_dig-1].inputs,&ptr_panel->analog_mon[ind].inputs[ptr_panel->analog_mon[ind].anum_inputs],headers_dig[ind_headers_dig-1].n_inputs*sizeof(Point_Net));
//	nsample_mem_dig_block = nsample_mem_dig_mon[ind];
	set_semaphore(&read_mon_flag);
	headers_dig[ind_headers_dig-1].prev_header = (long)mem_dmon_table;
	for(int i=0;i<ptr_panel->analog_mon[ind].num_inputs-ptr_panel->analog_mon[ind].anum_inputs;i++)
	{
	 if(ptr_panel->monitor_work_data[ind].start_index_dig[i] != 0x0FFFF)
	 {
		l1 = 0;
		headers_dig[ind_headers_dig-1].offset[i] = l;
		for(j=ptr_panel->monitor_work_data[ind].start_index_dig[i]; j != ptr_panel->monitor_work_data[ind].end_index_dig[i]; j = heap_dmon[j].next)
		{
		 *ptable++ = heap_dmon[j].time;
		 l1++;
		}
		*ptable++ = heap_dmon[j].time;
//		headers_dig[ind_headers_dig-1].time_last_sample[i] = heap_dmon[j].time;
		headers_dig[ind_headers_dig-1].time_last_sample[i] = *(ptable-1);
		headers_dig[ind_headers_dig-1].onoff[i] = heap_dmon[ptr_panel->monitor_work_data[ind].start_index_dig[i]].onoff;
		l1++;
		l += l1;
		headers_dig[ind_headers_dig-1].n_sample[i] = l1;
	 }
	}
	 clear_semaphore(&read_mon_flag);
	nsample_mem_dig_block = l;
 }

 f = ((char *)mem_dmon_table + (long)l * 4L) - (char *)dmon_table;
	if( (nbytes=f-max_file) > 0)
	{
	 int k = 0;
	 do
	 {
		nsample = 0;
		for(int i=0;i<headers_dig[k].n_inputs;i++)
		{
		 nsample += headers_dig[k].n_sample[i];
		}
		long nsamplelast = 0;
		for(i=0;i<headers_dig[ind_headers_dig-1].n_inputs;i++)
		{
		 nsamplelast += headers_dig[ind_headers_dig-1].n_sample[i];
		}
		char *plast = (char *)((long *)headers_dig[ind_headers_dig-1].prev_header + nsamplelast);

	 if( nbytes>=(long)nsample*4L)
	 {
		for(j = 0;j < ind_headers_dig-1;j++)
			headers_dig[j] = headers_dig[j+1];
		ind_headers_dig--;
		nbytes -= (long)nsample*4L;
		memmove(dmon_table, dmon_table + nsample, plast - (char *)headers_dig[0].prev_header);
		for(j = 0;j < ind_headers_dig;j++)
		 headers_dig[j].prev_header = (long)((long *)headers_dig[j].prev_header-nsample);
		if(ind_headers_dig>1)
		{
		 mem_dmon_table -= (nsample*4L);
		 if(mem_dmon_table < dmon_table) mem_dmon_table = (char *)dmon_table;
		}
		if(nbytes<0L)
		{
		 nbytes=0L;
		 break;
		}
	 }
	 else
	 {
		if(nbytes)
		{
		 l = nbytes%4L?nbytes/4L+1:nbytes/4L;
//		 l1 = l%(long)(headers_dig[k].n_inputs)?l/(long)(headers_dig[k].n_inputs)+1L:l/(long)(headers_dig[k].n_inputs);
		 f=nsample;
		 nsample=0;
		 long ll = 0;
		 for(i=0;i<headers_dig[k].n_inputs;i++)
		 {
			l1 = (headers_dig[k].n_sample[i] * l)/f;
			l1 += (headers_dig[k].n_sample[i] * l)%f?1:0;
			memmove( (long *)headers_dig[k].prev_header+headers_dig[k].offset[i] , (long *)headers_dig[k].prev_header+headers_dig[k].offset[i] + l1,  plast - (char *)((long *)headers_dig[k].prev_header+headers_dig[k].offset[i] + l1)  );
			for(int m=i+1; m<headers_dig[k].n_inputs; m++)
				headers_dig[k].offset[m] -= l1;

			headers_dig[k].offset[i] = ll;
			headers_dig[k].n_sample[i] -= l1;
			ll += headers_dig[k].n_sample[i];
			nsample += l1;
			if(l1%2)
				headers_dig[k].onoff[i] = !headers_dig[k].onoff[i];

/*
			if(headers_dig[k].n_sample[i]<l1)
			{
			 l = l-headers_dig[k].n_sample[i];
			 if( headers_dig[k].n_inputs-i-1 )
				 l1 = l%(long)(headers_dig[k].n_inputs-i-1)?l/(long)(headers_dig[k].n_inputs-i-1)+1L:l/(long)(headers_dig[k].n_inputs-i-1);
			 else
				 l1 -= headers_dig[k].n_sample[i];

			 memmove( (long *)headers_dig[k].prev_header+headers_dig[k].offset[i] , (long *)headers_dig[k].prev_header+headers_dig[k].offset[i] + headers_dig[k].n_sample[i], plast - (char *)((long *)headers_dig[k].prev_header+headers_dig[k].offset[i] + headers_dig[k].n_sample[i]) );
			 for(int m=i+1; m<headers_dig[k].n_inputs; m++)
				 headers_dig[k].offset[m] -= headers_dig[k].n_sample[i];

			 headers_dig[k].n_sample[i] = 0;
			 nsample += headers_dig[k].n_sample[i];
			}
			else
			{
			 l = l-l1;

			 memmove( (long *)headers_dig[k].prev_header+headers_dig[k].offset[i] , (long *)headers_dig[k].prev_header+headers_dig[k].offset[i] + l1,  plast - (char *)((long *)headers_dig[k].prev_header+headers_dig[k].offset[i] + l1)  );
			 for(int m=i+1; m<headers_dig[k].n_inputs; m++)
				 headers_dig[k].offset[m] -= l1;

			 headers_dig[k].offset[i] = ll;
			 headers_dig[k].n_sample[i] -= l1;
			 ll += headers_dig[k].n_sample[i];
			 nsample += l1;
			 if(l1%2)
				 headers_dig[k].onoff[i] = !headers_dig[k].onoff[i];
			}
			if (l <= 0) break;
*/
		 }
		 break;
		}
	 }
	} while(1);

	 if(nbytes)
	 {
		for(j = k+1;j < ind_headers_dig;j++)
		 headers_dig[j].prev_header = (long)((long *)headers_dig[j].prev_header-nsample);
		if(ind_headers_dig>1)
			 mem_dmon_table -= (nsample*4L);
	 }
	}
	asm pop es;
	return SUCCESS;
}


int	updatemem(int ind, int panel, int network, int type)
{
asm push es;
	long interv, f,max_file,nbytes,t[3];
	int n,j,v=0;
	char *p,*pmon_table;
	Mini_Monitor_Block *mb;
	max_file=(long)MAX_SAMPLE*(long)MAX_INP;
	psample(&interv, current_analog_mon);

	if(type)
	{
		mfarmalloc((char far **)&p, MAX_INP*MAXSAMPLEUPDATE*4+MAX_HEADERS_AMON*sizeof(Header_amon));
//		set_semaphore_dos();
//		char *p = new char[1200*4];
//		clear_semaphore_dos();
		if(!p )
		{
			exit( 1);
		}
		else
		{
		 Delay(200);
		 if( panel_info1.panel_type == T3000 )
		 {
			if(net_call(UPDATEMEMMONITOR_T3000, ind+128*index_last_value, p, 0, panel, network)!=SUCCESS)
			{
/*
		 set_semaphore_dos();
		 delete [] p;
		 clear_semaphore_dos();
*/
			 if(net_call(UPDATEMEMMONITOR_T3000, ind+128*index_last_value, p, 0, panel, network)!=SUCCESS)
			 {
				mfarfree(p);
				asm pop es;
				return ERROR_COMM;
			 }
			}
			memcpy(&sample, p, 2);
			if(sample==-1)
			{
/*
		 set_semaphore_dos();
		 delete [] p;
		 clear_semaphore_dos();
*/
				mfarfree(p);
				asm pop es;
				return ERROR_COMM;
			}
			memcpy(&time_last_sample, p+2, 4);
			headers[ind_headers-1].time_last_sample=time_last_sample;
			memcpy(&n, p+6, 2);
			headers[ind_headers-1].n_sample += n;
			memcpy(&n, p+8, 2);
			memcpy(pmem_table, p+10, n*4);
			pmem_table += n;
			index_last_value = sample;
/*
		set_semaphore_dos();
		delete [] p;
		clear_semaphore_dos();
*/
			mfarfree(p);
		 }
		 else
		 {
			t[0] = MAX_INP*MAXSAMPLEUPDATE*4+MAX_HEADERS_AMON*sizeof(Header_amon);
			t[1] = headers[ind_headers-1].time_last_sample + 1 - timezone;
			t[2] = timesec1970 + timestart - timezone;
			n=0;
			if(net_call(UPDATEMEMMONITOR_T3000, (ANALOGDATA<<8)+ind, p, (unsigned int *)&n, panel, network, NETCALL_SIGN, 40,
					NULL, NULL, (char *)t, 12)!=SUCCESS)
			{
			 mfarfree(p);
			 asm pop es;
			 return ERROR_COMM;
			}
			if( n == 2 )
			{
			 mfarfree(p);
			 asm pop es;
			 return ERROR_COMM;
			}
			if( n == 0 )
			{
			  mfarfree(p);
				asm pop es;
				return SUCCESS;
			}
			mb = (Mini_Monitor_Block *)p;
			pmon_table = (char *)p;
			for(nbytes=0; nbytes<n;)
			{
			 j = mb->index/mb->no_points;
			 headers[ind_headers-1].n_sample += j;
			 headers[ind_headers-1].time_last_sample = mb->start_time+headers[ind_headers-1].interval*(j-1)+timezone;
			 memmove(pmem_table, (char *)(mb->data.analog), (mb->index)*4);
			 pmem_table += mb->index;
			 j = sizeof(Mini_Monitor_Block)-4*MAX_ANALOG_SAMPLES_PER_BLOCK+4*mb->index;
			 nbytes += j;
			 mb = (Mini_Monitor_Block *)(((char *)mb)+j);
			}
			mfarfree(p);
		 }
		}
  }
	else
	{
//	 set_semaphore(&t3000_flag);
	 sample = ptr_panel->monitor_work_data[ind].head_index;
	 time_last_sample = ptr_panel->monitor_work_data[ind].last_sample_time;
//	 clear_semaphore(&t3000_flag);
//	max_file -= (long)sample*(long)ptr_panel->analog_mon[ind].num_inputs*4L;
	 if(last_mem_block)
	 {
		newmem(ind, sample, time_last_sample, (char *)pmem_table, &pmem_table, &index_last_value, &last_mem_block, &nsample_mem_block, headers, &ind_headers,1);
	 }
	 else
		newmem(ind, sample, time_last_sample, (char *)pmem_table, &pmem_table, &index_last_value,&last_mem_block, &nsample_mem_block, headers, &ind_headers);
	}

	 f = pmem_table - mon_table;
	 if(( nbytes = (f - max_file  )) > 0)
	 {
	 int i = 0;
	 do
	 {
	 if(nbytes>(long)(headers[i].n_sample-1)*(long)headers[i].n_inputs)
	 {
		long l = (long)headers[i].n_sample*(long)headers[i].n_inputs;
		nbytes -= l;
		if(nbytes<0L) nbytes=0L;
		for(j = 0;j < ind_headers-1;j++)
			headers[j] = headers[j+1];
		ind_headers--;
		for(j = 1;j < ind_headers;j++)
		 headers[j].prev_header = (long)((long *)headers[j].prev_header-l);
		pmem_table -= l;
		memmove(mon_table, mon_table + l, max_file*4L);
	 }
	 else
	 {
		if(nbytes)
		{
		 long l1 = nbytes/(long)(headers[i].n_inputs);
		 l1 += (nbytes%(long)(headers[i].n_inputs)?1:0);
		 headers[i].n_sample -= l1;
		 memmove(mon_table, mon_table + l1*(long)headers[i].n_inputs, max_file*4L);
		 for(j = 1;j < ind_headers;j++)
			 headers[j].prev_header = (long)((long *)headers[j].prev_header-l1*(long)headers[j].n_inputs);
		 pmem_table -= l1*(long)headers[i].n_inputs;
		 break;
		}
		else
		 break;
	 }
	 } while(1);
	}
	asm pop es;
	return SUCCESS;


/*
	 if(last_mem_block == 1) ind_headers--;
	 else
		 if(last_mem_block == 2)
		 {
			 headers[ind_headers-1].time_last_sample = time_last_sample_mem;
			 headers[ind_headers-1].n_sample -= nsample_mem_block;
		 }

	 if(ind_headers)
		 if(sample)
			 v = addmem(ind, interv, sample, time_last_sample, (char *)pmem_table);
	 if(!v)
	 {
		newmem(ind, sample, time_last_sample, (char *)pmem_table);
	 }

	 if(( nbytes = (f + (long)nsample_mem_block * ptr_panel->analog_mon[ind].num_inputs) - max_file  ) > 0)
	 {
	 int i = 0;
	 do
	 {
	 if(nbytes>(long)(headers[i].n_sample-1)*(long)headers[i].n_inputs)
	 {
		long l = (long)headers[i].n_sample*(long)headers[i].n_inputs;
		nbytes -= l;
		if(nbytes<0L) nbytes=0L;
		for(j = 0;j < ind_headers-1;j++)
			headers[j] = headers[j+1];
		ind_headers--;
		for(j = 0;j < ind_headers;j++)
		 headers[i].prev_header -= (long)((long *)headers[i].prev_header-l);
		pmem_table -= l;
		memmove(mon_table, mon_table + l, max_file*4L);
	 }
	 else
	 {
		if(nbytes)
		{
		 long l1 = nbytes/(long)(headers[i].n_inputs);
		 headers[i].n_sample -= l1;
		 memmove(mon_table, mon_table + l1*(long)headers[i].n_inputs, max_file);
		 for(j = 0;j < ind_headers;j++)
			 headers[i].prev_header -= (long)((long *)headers[i].prev_header-l1*(long)headers[i].n_inputs);
		 pmem_table -= l1*(long)headers[i].n_inputs;
		 break;
		}
		else
		 break;
	 }
	 } while(1);
	}
*/
}

int findleftrighttime(FILE *h1, long timeread, long &timeleft, long &timeright,
							 int &nheaders, long max_file, int direction)
{
 Header_amon header_amon;
 long m,offset,l;
	  set_semaphore_dos();
		fseek(h1, 0, SEEK_SET);
	  fread(&offset, 4, 1, h1);
	  fseek(h1, offset, SEEK_SET);
	  nheaders=0;
	  fread(&header_amon, sizeof(Header_amon), 1, h1);
	  clear_semaphore_dos();
	  if(direction==FORWARD)
	  {
		if( timeread>=header_amon.time_last_sample )
		{
		  timeleft = timeright =  header_amon.time_last_sample;
		  return 0;
		}
		if( (timeleft=header_amon.time_last_sample-(header_amon.n_sample-1)*header_amon.interval) < timeread )
		{
		 while( (m=header_amon.time_last_sample-(header_amon.n_sample-1)*header_amon.interval) > timeread)
		 {
		  if(header_amon.prev_header)
		  {
			set_semaphore_dos();
			fseek(h1, (long)header_amon.prev_header, SEEK_SET);
			fread(&header_amon, sizeof(Header_amon), 1, h1);
			clear_semaphore_dos();
		  }
		  else
			break;
		 }
		 timeleft=0;
		 l=0;
		 for(;m<=header_amon.time_last_sample; m += header_amon.interval )
		 {
			if( m >= timeread ) {timeleft = m; break;}
			l++;
		 }
		 if(!timeleft)
		 {
			set_semaphore_dos();
			fseek(h1, (long)header_amon.n_sample*(long)header_amon.n_inputs*4L, SEEK_CUR);
			fread(&header_amon, sizeof(Header_amon), 1, h1);
			clear_semaphore_dos();
			timeleft = header_amon.time_last_sample-(header_amon.n_sample-1)*header_amon.interval;
		 }
		 else
		 {
		  set_semaphore_dos();
		  fseek(h1, (long)l*(long)header_amon.n_inputs*4L, SEEK_CUR);
		  clear_semaphore_dos();
		  header_amon.n_sample -= l;
		 }
		}
		do
		{
		  timeright = header_amon.time_last_sample;
		  if((m=(long)header_amon.n_sample*header_amon.n_inputs*4L-max_file)>=0L)
		  {
			l = m%(header_amon.n_inputs*4L)?m/(header_amon.n_inputs*4L)+1:m/(header_amon.n_inputs*4L);
			l++;
			header_amon.n_sample -= l;
			timeright = header_amon.time_last_sample-(l-1)*header_amon.interval;
			nheaders++;
			break;
		  }
		  else
		  {
			nheaders++;
			max_file -= (long)header_amon.n_sample*header_amon.n_inputs*4L;
			set_semaphore_dos();
			fseek(h1, (long)header_amon.n_sample*(long)header_amon.n_inputs*4L, SEEK_CUR);
			fread(&header_amon, sizeof(Header_amon), 1, h1);
			if ( feof(h1) )
			{
				 clear_semaphore_dos();
				 break;
			}
			clear_semaphore_dos();
		  }
		} while (1);
	  }
	  if(direction!=FORWARD)
	  {
		if( header_amon.time_last_sample <= timeread )
		{
		  timeright = header_amon.time_last_sample;
//		  l = header_amon.n_sample*header_amon.n_inputs;
		}
		else
		{
		 while( (m=header_amon.time_last_sample-(header_amon.n_sample-1)*header_amon.interval) > timeread)
		 {
		  if(header_amon.prev_header)
			{
			set_semaphore_dos();
			fseek(h1, (long)header_amon.prev_header, SEEK_SET);
			fread(&header_amon, sizeof(Header_amon), 1, h1);
			clear_semaphore_dos();
		  }
			else
			break;
		 }
		 timeright=0;
		 for(;m<=header_amon.time_last_sample; m += header_amon.interval )
		 {
			if( m > timeread ) {timeright = m-header_amon.interval; break;}
			if( m == timeread ) {timeright = m; break;}
		 }
		 if(!timeright)
		 {
		  timeright = header_amon.time_last_sample;
//		  l = header_amon.n_sample*header_amon.n_inputs;
		 }
		}

		if(!header_amon.prev_header)
		{
		 nheaders++;
		 timeleft = header_amon.time_last_sample-(header_amon.n_sample-1)*header_amon.interval;
		 m = timeright;
		 l = 1;
		 while( m >=  timeleft )
		 {
			if( (l*header_amon.n_inputs*4L-max_file)>0L )
		  {
			timeleft = m + header_amon.interval;
			break;
		  }
		  m -= header_amon.interval;
			l++;
		 }
		}
		else
		{
		 set_semaphore_dos();
		 fseek(h1, (long)header_amon.prev_header, SEEK_SET);
		 clear_semaphore_dos();
		 do
		 {
		  set_semaphore_dos();
		  fread(&header_amon, sizeof(Header_amon), 1, h1);
		  clear_semaphore_dos();
		  timeleft = header_amon.time_last_sample-(header_amon.n_sample-1)*header_amon.interval;
		  if((m=(long)header_amon.n_sample*header_amon.n_inputs*4L-max_file)>=0L)
		  {
			l = m%(header_amon.n_inputs*4L)?m/(header_amon.n_inputs*4L)+1:m/(header_amon.n_inputs*4L);
			header_amon.n_sample -= l;
			timeleft = header_amon.time_last_sample-(header_amon.n_sample-1)*header_amon.interval;
			nheaders++;
			break;
		  }
		  else
		  {
			nheaders++;
			if(header_amon.prev_header)
			 {
				max_file -= (long)header_amon.n_sample*header_amon.n_inputs*4L;
				set_semaphore_dos();
				fseek(h1, (long)header_amon.prev_header, SEEK_SET);
				clear_semaphore_dos();
			 }
			 else
				break;
		  }
		 } while (1);
		}
		if(timeleft>=timeright) return 0;
	  }
 return 1;
}

int readfileleftrighttime(FILE *h1, long &timeleft, long &timeright, Header_amon *pheaders, char *pmon_table)
{
 Header_amon header_amon;
 long m,offset,l, timeread, pos;
 int n, ind_headers=0;
	  set_semaphore_dos();
	  fseek(h1, 0, SEEK_SET);
	  fread(&offset, 4, 1, h1);
	  fseek(h1, offset, SEEK_SET);
	  fread(&header_amon, sizeof(Header_amon), 1, h1);
	  clear_semaphore_dos();
	  while( (m=header_amon.time_last_sample-(header_amon.n_sample-1)*header_amon.interval) > timeleft)
		{
		  if(header_amon.prev_header)
		  {
			set_semaphore_dos();
			fseek(h1, (long)header_amon.prev_header, SEEK_SET);
			fread(&header_amon, sizeof(Header_amon), 1, h1);
			clear_semaphore_dos();
		  }
		  else
			break;
	  }
	  for(n=0;m<=header_amon.time_last_sample; m += header_amon.interval, n++ )
		if( m >= timeleft ) { break;}
	  if(n>=header_amon.n_sample) return 0;

	  header_amon.n_sample -= n;

	  set_semaphore_dos();
	  fseek(h1, (long)n*(long)header_amon.n_inputs*4L, SEEK_CUR);
	  clear_semaphore_dos();
	  timeread = m;
	  l=0;
	  while(timeread <= timeright)
	  {
//		pos = ftell(h1) + header_amon.n_sample*header_amon.n_inputs*4;
		if(timeright <= header_amon.time_last_sample)
		{
		 for( n=0; timeread <= timeright; timeread += header_amon.interval, n++)
		 {
		  if( timeread > timeright )
			break;
		 }
		 header_amon.time_last_sample -= (header_amon.n_sample-n)*header_amon.interval;
	    header_amon.n_sample = n;
		}
		else
		{
		 n = header_amon.n_sample;
		 timeread = header_amon.time_last_sample;
		}
		pheaders[ind_headers] = header_amon;
		pheaders[ind_headers].prev_header =(long) pmon_table;
		set_semaphore_dos();
		fread(pmon_table,(long)n*header_amon.n_inputs*4L , 1, h1);
		pmon_table += (long)n*header_amon.n_inputs*4L;
		l += n*header_amon.n_inputs;
		fseek(h1, (long)n*(long)header_amon.n_inputs*4L, SEEK_CUR);
		fread(&header_amon, sizeof(Header_amon), 1, h1);
		clear_semaphore_dos();
		ind_headers++;
	  }
 return l;
}


char *upreadmontable(int ind, int panel, int network, long *length, long &timeread, char direction, long **montable,
							Header_amon **pheaders, int &nheaders, int type, char *serptr)  //type = 1 retea, 2 = serial||modem ; 0 local
{
	Point_Net p;
	unsigned k;
	int num_panel,num_point,num_net,j,i,v,n,ssample,iindex_last_value, nsample_mem_block_net, ind_headers_net;
	byte var_type, point_type;
	Header_amon header_amon, h_amon, *headers_net;
	long m,f,max_file,l,offset,timeleft,timeright,*pmem_table_net, time_last_sample_net;
	char label[13],buf[13],*filename,*pmon_table, last_mem_block_net;
	FILE *h1;
//!!	float *t,lasts[14];
	long *t;

	if( local_request(panel) )
	{
	set_semaphore_dos();
	filename = new char[80];
	clear_semaphore_dos();

	p.putpoint(ind-1, AMON + 1, panel-1, network);
	pointtotext(buf,&p);

	strcpy(label,ispoint(rtrim(buf),&num_point,&var_type, &point_type, &num_panel, &num_net, network, panel));
	strcat(label,ext);
	ind--;
	max_file=*length;

	if(type==2)
	{
		*montable = (long *)serptr;
	}
//	else
//		mfarmalloc((char far **)mon_table, (max_file/4+140+(type?MAX_MEM_DIG_BUF/4+100 + 110 + 110 :0))*4,mon_table_handle);

	if(type) (*mon_table)++;
//	ssample = 0;
//	 if(!type)
//		 time_last_sample = timeread;
//	 else
//		 time_last_sample_net = timeread;

//	 if(type)
//		iindex_last_value = ssample;
//	 else
//		index_last_value = ssample;

////////////
//	if(type)
//		pheaders = &headers_net;
//	else
//		pheaders = &headers;

//	if(!type)
//	{
//	 last_mem_block = 0;
//	 nsample_mem_block = 0;
//	 ind_headers = 0;
//	}
//	else
//	{
//	 last_mem_block_net = 0;
//	 nsample_mem_block_net = 0;
//	 ind_headers_net = 0;
//	}

	pmon_table=(char *)(*montable);

	v=0;
	n=-1;
	l=0;
	filename[0] = 0;
	strcpy(filename, ptr_panel->Monitor_Path);
	if(strlen(filename)) strcat(filename, "\\");
	strcat(filename, label);
	timeright = 0;
	set_semaphore_dos();
	if((h1=fopen(filename,"r+b"))!=NULL)
	{
		clear_semaphore_dos();
		set_semaphore(&read_mon_flag);
		*length = 0;
		if(findleftrighttime(h1, timeread, timeleft, timeright, nheaders, max_file, direction))
		{
		 if( (direction!=FORWARD && timeleft <= timeread) ||
				(direction==FORWARD && timeright >= timeread) )
		 {
			set_semaphore_dos();
			(*pheaders) = new Header_amon[nheaders+2];
			clear_semaphore_dos();
			*length=readfileleftrighttime(h1, timeleft, timeright, *pheaders, (char *) *montable);
			clear_semaphore(&read_mon_flag);
			set_semaphore_dos();
			fclose(h1);
			if(filename)
		    delete filename;
			clear_semaphore_dos();
			timeread = timeright;
			return (char *)*montable;
		 }
		}
		clear_semaphore(&read_mon_flag);
		set_semaphore_dos();
		fclose(h1);
	}
	if(filename)
		delete filename;
	clear_semaphore_dos();
	}
	return 0;
}


char *readmontable(int ind, int *length, long **mon_table, int type, char *serptr=NULL)  //type = 1 retea, 2 = serial||modem ; 0 local
{
	Point_Net p;
	unsigned k;
	int lesslast,j,i,v,n,ssample,iindex_last_value, nsample_mem_block_net, ind_headers_net;
	int network;
	byte var_type,point_type;
	int num_net,num_point,num_panel;
//	byte num_point,var_type, point_type, num_panel;
	Header_amon header_amon, h_amon, **pheaders, *headers_net;
	unsigned long f,timefirstsample;
	long m,max_file,l,offset,*pmem_table_net, time_last_sample_net;
	char label[13],buf[13],*filename,*pmon_table, last_mem_block_net;
	FILE *h1;
//!!	float *t,lasts[14];
	long *t, *lasts;        //lasts[MAX_POINTS_IN_MONITOR] = 4*14 = 56;
	set_semaphore_dos();
	filename = new char[80];
	clear_semaphore_dos();

	if( rs485port!=-1 )
	{
	 network=(( class ConnectionData *)Routing_table[rs485port].ptr)->panel_info1.network;
	}
	else
	 network = NetworkAddress;

	p.putpoint(ind-1, AMON + 1, Station_NUM-1, network);
	pointtotext(buf,&p);
//	for(i=0;i<MAX_POINTS_IN_MONITOR;i++) lasts[i]=0;

	strcpy(label,ispoint(rtrim(buf),&num_point,&var_type, &point_type, &num_panel, &num_net, network, Station_NUM));
//	strcpy(label,ispoint(rtrim(buf),(int *)&i, (byte *)&i, (byte *)&i, (int *)&i, &i, network, Station_NUM));
	strcat(label,ext);
	lesslast=0;
	ind--;
	max_file=(long)MAX_SAMPLE*(long)MAX_INP*4L;      // 200*14*4

	set_semaphore(&read_mon_flag);
	if(type==2)
	{
//		mon_table_handle=0;
		max_file = (max_file>(SERIAL_BUF_SIZE-800)?SERIAL_BUF_SIZE-800:max_file);
		*mon_table = (long *)serptr;
	}
	else
	{
//  (long)MAX_SAMPLE*(long)MAX_INP*4+MAX_INP*10*4+(type?MAX_MEM_DIG_BUF/4+100 + 110 + 110 :0))*4,mon_table_handle);

		l = max_file+MAX_INP*MAXSAMPLEUPDATE*4+(type?(MAX_MEM_DIG_BUF+400 + MAX_HEADERS_AMON*sizeof(Header_amon) + MAX_HEADERS_DMON*sizeof(Header_dmon)) :0);
		mfarmalloc((char far **)mon_table, l, mon_table_handle);
	}

	if(type) (*mon_table)++;
//!!	t = (float *)ptr_panel->analog_mon[ind].data_segment;
	t = (long *)ptr_panel->monitor_work_data[ind].data_segment;
////////
//	 set_semaphore(&t3000_flag);
	 ssample = ptr_panel->monitor_work_data[ind].head_index;
	 if(!type)
		 time_last_sample = ptr_panel->monitor_work_data[ind].last_sample_time;
	 else
		 time_last_sample_net = ptr_panel->monitor_work_data[ind].last_sample_time;

//	 clear_semaphore(&t3000_flag);
///////
	 if(type)
		iindex_last_value = ssample;
	 else
		index_last_value = ssample;

////////////
	if(type)
		pheaders = &headers_net;
	else
		pheaders = &headers;

	if(!type)
	{
	 last_mem_block = 0;
	 nsample_mem_block = 0;
	 ind_headers = 0;
	}
	else
	{
	 last_mem_block_net = 0;
	 nsample_mem_block_net = 0;
	 ind_headers_net = 0;
	}

	pmon_table=(char *)(*mon_table);
	if(!type)
		pmem_table = *mon_table;
	else
		pmem_table_net = *mon_table;

	v=0;
	n=-1;
	l=0;
	 k=0;
	filename[0] = 0;
	strcpy(filename, ptr_panel->Monitor_Path);
	if(strlen(filename)) strcat(filename, "\\");
	strcat(filename, label);
	set_semaphore_dos();
int_disk=1;
	if((h1=fopen(filename,"r+b"))!=NULL)
	{
		lasts=(long *)&filename[0];        //lasts[MAX_POINTS_IN_MONITOR] = 4*14 = 56;
		for(i=0;i<MAX_POINTS_IN_MONITOR;i++) lasts[i]=0;
int_disk=0;
		max_file -= (long)ssample*(long)ptr_panel->analog_mon[ind].anum_inputs*4L;
int_disk=1;
		fread(&offset, 4, 1, h1);
		fseek(h1, offset, SEEK_SET);
int_disk=0;
		clear_semaphore_dos();
		do
		{
		 set_semaphore_dos();
int_disk=1;
		 fread(&header_amon, sizeof(Header_amon), 1, h1);
int_disk=0;
		 clear_semaphore_dos();
		 if( !ptr_panel->monitor_work_data[ind].saved )
			ptr_panel->monitor_work_data[ind].last_sample_saved_time = header_amon.time_last_sample;
		 if(n<0)
		 {
//		 psample(&interv, current_analog_mon);
			psample(&interv, &ptr_panel->analog_mon[ind]);
		  if(ssample)
			 timefirstsample = (type?time_last_sample_net:time_last_sample)-(ssample-1)*(long)interv;
			else
			 timefirstsample = timesec1970 + timestart;

		  if( timefirstsample < header_amon.time_last_sample)
		  {
			lesslast=1;
         break;
		  }
		  else
		  {
			k=0;
			f=header_amon.time_last_sample+header_amon.interval;
			if( timefirstsample > f)
			{
			 set_semaphore_dos();
int_disk=1;
			 fseek(h1, (long)(header_amon.n_sample-1)*4L*(long)header_amon.n_inputs, SEEK_CUR);
			 fread(lasts, header_amon.n_inputs*4,1,h1);
int_disk=0;
			 clear_semaphore_dos();
			 while(timefirstsample > f && k<2000)
			 {
				k++;
				f += header_amon.interval;
			 }
			 max_file -= (long)k*header_amon.n_inputs*4L;
			 if( k >= 2000 ) max_file=-1;
			 if(max_file<0) max_file=-1;
			 set_semaphore_dos();
int_disk=1;
			 fseek(h1, (long)(offset+sizeof(Header_amon)), SEEK_SET);
int_disk=0;
			 clear_semaphore_dos();
			}
			}
			if(max_file==-1) break;
		 }
		 if((m=(long)header_amon.n_sample*header_amon.n_inputs*4L-max_file)>=0L)
		 {
//			if(m)
			l = m%(header_amon.n_inputs*4L)?m/(header_amon.n_inputs*4L)+1:m/(header_amon.n_inputs*4L);
			set_semaphore_dos();
int_disk=1;
			fseek(h1, (long)l*(long)header_amon.n_inputs*4L, SEEK_CUR);
int_disk=0;
			clear_semaphore_dos();
			header_amon.n_sample -= l;
			n++;
			break;
		 }
		 else
		 {
			n++;
			if (n>=MAX_HEADERS_AMON-2) break;
			if(header_amon.prev_header)
			{
				max_file -= (long)header_amon.n_sample*header_amon.n_inputs*4L;
				set_semaphore_dos();
int_disk=1;
				fseek(h1, (long)header_amon.prev_header, SEEK_SET);
int_disk=0;
				clear_semaphore_dos();
			}
			else
				break;
		 }
		} while (1);

     if(!lesslast)
		if(max_file!=-1)
		{
		 set_semaphore_dos();
		 (*pheaders) = new Header_amon[n+2];
		 clear_semaphore_dos();
		 for(;(type?ind_headers_net:ind_headers)<=n;type?ind_headers_net++:ind_headers++)
		 {

		 (*pheaders)[type?ind_headers_net:ind_headers] = header_amon;
		 (*pheaders)[type?ind_headers_net:ind_headers].prev_header =(long) pmon_table;
	 set_semaphore_dos();

int_disk=1;
		 fread(pmon_table,header_amon.n_sample*header_amon.n_inputs*4 , 1, h1);
int_disk=0;
		 pmon_table += header_amon.n_sample*header_amon.n_inputs*4;
int_disk=1;
		 fread(&header_amon, sizeof(Header_amon), 1, h1);
int_disk=0;
	 clear_semaphore_dos();
		 }
		 if(!type)
			 pmem_table = (long *)pmon_table;
		 else
			 pmem_table_net = (long *)pmon_table;

		 if(lesslast)
		 {
			j=(type?ind_headers_net:ind_headers)-1;
			set_semaphore_dos();
			while (1)
			{
			 f = (*pheaders)[j].time_last_sample - ((*pheaders)[j].n_sample-1)*(*pheaders)[j].interval;
			 if(timefirstsample<=f)
			 {
				j--;
				continue;
			 }
			 else
			 {
				m=0;
				for(i=0;i<(*pheaders)[j].n_sample;i++)
				{
				 if(timefirstsample<=f)
				 {
					(*pheaders)[j].n_sample=m;
					(*pheaders)[j].time_last_sample = f-(*pheaders)[j].interval;
					type?ind_headers_net:ind_headers=j+1;
					break;
				 }
				 else
				 {
					m++;
					f += (*pheaders)[j].interval;
				 }
				}
				break;
			} //while
			clear_semaphore_dos();
		 }
		 }
		}
	 set_semaphore_dos();
int_disk=1;
	 fclose(h1);
int_disk=0;
	 clear_semaphore_dos();
	}
	else
	{
		clear_semaphore_dos();
		lasts=(long *)&filename[0];        //lasts[MAX_POINTS_IN_MONITOR] = 4*14 = 56;
		for(i=0;i<MAX_POINTS_IN_MONITOR;i++) lasts[i]=0;
	}

	int_disk=0;

	if(type?ind_headers_net:ind_headers)
	{
	 if(k)
	 {
		(*pheaders)[(type?ind_headers_net:ind_headers)-1].n_sample += k;
		(*pheaders)[(type?ind_headers_net:ind_headers)-1].time_last_sample = f-(*pheaders)[(type?ind_headers_net:ind_headers)-1].interval;
		for(i=0;i<k;i++)
		 {
			memcpy(pmon_table, lasts, (*pheaders)[(type?ind_headers_net:ind_headers)-1].n_inputs*4);
			pmon_table += (*pheaders)[(type?ind_headers_net:ind_headers)-1].n_inputs*4;
		 }
		if(!type)
			pmem_table = (long *)pmon_table;
		else
			pmem_table_net = (long *)pmon_table;
	 }
	 if(ssample)
		 v = addmem(ind, interv, ssample, type?time_last_sample_net:time_last_sample, pmon_table, type?&pmem_table_net:&pmem_table, type?&last_mem_block_net:&last_mem_block, type?&nsample_mem_block_net:&nsample_mem_block, *pheaders, type?&ind_headers_net:&ind_headers);
	}
	else
	 {
		 set_semaphore_dos();
		(*pheaders) = new Header_amon;
		 clear_semaphore_dos();
	 }
	if(!v)
	{
	 newmem(ind, ssample, type?time_last_sample_net:time_last_sample, pmon_table, type?&pmem_table_net:&pmem_table,type?&iindex_last_value:&index_last_value, type?&last_mem_block_net:&last_mem_block, type?&nsample_mem_block_net:&nsample_mem_block, *pheaders, type?&ind_headers_net:&ind_headers);
	}
	 clear_semaphore(&read_mon_flag);

	set_semaphore_dos();
	if(filename)
	 delete filename;
	clear_semaphore_dos();

	 if(type)
	 {
		l=0;
		for(i=0;i<ind_headers_net;i++)
			l += (long)(*pheaders)[i].n_sample*(long)(*pheaders)[i].n_inputs;
		*((*mon_table)-1) = l;
		pmon_table = (char *)(*mon_table) + l*4;
		memcpy(pmon_table, &iindex_last_value, 2);
		memcpy(pmon_table+2,&last_mem_block_net, 1);
		memcpy(pmon_table+3,&nsample_mem_block_net, 2);
		memcpy(pmon_table+5, &ssample, 2);
		l = (pmem_table_net - (*mon_table)) * 4L;
		memcpy(pmon_table+7, &l, 2);
		memcpy(pmon_table+9,&ind_headers_net, 2);
		memmove(pmon_table + 11, (*pheaders), ind_headers_net*sizeof(Header_amon));
		pmon_table += 11 + ind_headers_net*sizeof(Header_amon);
		set_semaphore_dos();
		delete (*pheaders);
		clear_semaphore_dos();
		*length = pmon_table - (char *)((*mon_table)-1);
	 }

	 if(type) dmon_table = (long *)pmon_table;
//	 l=readdigtable(ind+1, ind_headers?headers[0].time_last_sample-(headers[0].n_sample-1)*headers[0].interval:0, ind_headers?headers[ind_headers-1].time_last_sample:0, &dmon_table, type);
	 l=readdigtable(ind+1, &dmon_table, type);
	 if(type)
	 {
		*length += l;
		return (char *)((*mon_table)-1);
	 }
	 sample = ssample;
}

void setscale(hot_box *viewport)
{
	 cx_pix_unit = 0;
	 time_sample_last_read = 0x7FFFFFFF;
	 if(ind_headers)
	 {
		TIME_last_sample = headers[ind_headers-1].time_last_sample;
		TIME_first_sample = headers[0].time_last_sample-(headers[0].n_sample-1)*headers[0].interval;
		if(!justsavemem)
			scale(TIME_last_sample, viewport);
	 }
	 else
		if(ind_headers_dig )
		{
		 unsigned long l,max = 0;
		 for(int i=0; i < headers_dig[ind_headers_dig-1].n_inputs; i++)
				if(headers_dig[ind_headers_dig-1].time_last_sample[i] > max) max = headers_dig[ind_headers_dig-1].time_last_sample[i];
		if(TIME_last_sample)
			dgtimelast =  (long)max - TIME_last_sample;
		TIME_last_sample = max;
		 unsigned long min = 0x0ffffffff;
		 for(i=0; i < headers_dig[0].n_inputs; i++)
				if((l=*((long *)(headers_dig[0].prev_header)+headers_dig[0].offset[i])) < min) min = l;
		TIME_first_sample = min;
		if( TIME_last_sample == TIME_first_sample)
		{
		 TIME_last_sample = TIME_first_sample = 0;
		 time_first_sample = time_last_sample = 0;
		 Time_first_sample = Time_last_sample = 0;
		 First_sample = FIRST_sample = 0;
		 Last_sample = LAST_sample = 0;
		 interval = lastinterval = interv = 0;
		 sample = 0;
		 timerange = 0;
		 return;
		}
		if(!justsavemem)
			scale(TIME_last_sample, viewport);
		}
		else
		{
		 TIME_last_sample = TIME_first_sample = 0;
		 time_first_sample = time_last_sample = 0;
		 Time_first_sample = Time_last_sample = 0;
		 First_sample = FIRST_sample = 0;
		 Last_sample = LAST_sample = 0;
		 interval = lastinterval = interv = 0;
		 sample = 0;
		 timerange = 0;
		}
}

/*============================================================================*/
int readnettable(int ind, hot_box *viewport, int panel, int network)
/*============================================================================*/
{
	long interv, max_file, l, l1, t[2], *ptable;
	uint max_file_analog, max_file_dig, nrbytes;
	int i, j, k, first,dummy,prev_size;
	char *pmon_table;
	i = j = k = first = interv = max_file = l= l1 = dummy = 0;
	max_file=(long)MAX_SAMPLE*(long)MAX_INP*4L;
	max_file_dig = MAX_MEM_DIG_BUF;
	current_mon = ind;

	dmon_table_handle=0;
	l = max_file+MAX_INP*MAXSAMPLEUPDATE*4L+(long)max_file_dig+400L + MAX_HEADERS_AMON*sizeof(Header_amon) + MAX_HEADERS_DMON*sizeof(Header_dmon);

	if( panel_info1.panel_type == MINI_T3000 )
	{
	 Mini_Monitor_Block *mb;
	 Point_Net inp[MAX_POINTS_IN_MONITOR];
	 long interval,kl;
	 int n_inputs;

	 max_file_analog = (int)(max_file);
	 max_file_analog = (max_file_analog/sizeof(Mini_Monitor_Block))*sizeof(Mini_Monitor_Block);
	 l = max_file_analog + MAX_INP*10*4L + MAX_HEADERS_AMON*sizeof(Header_amon);
	 mfarmalloc((char far **)&mon_table, (long)l, mon_table_handle);

	 t[0] = max_file_analog;
	 t[1] = timesec1970 + timestart - timezone;

	 if(net_call(READMONITORDATA_T3000, (ANALOGDATA<<8)+ind, (char *)mon_table, &max_file_analog, panel, network, NETCALL_SIGN, 40,
					NULL, NULL, (char *)t, 8)!=SUCCESS)
		 return ERROR_COMM;


	 mb = (Mini_Monitor_Block *)mon_table;
	 j=0;
	 memset(inp, 0, sizeof(Point_Net)*MAX_POINTS_IN_MONITOR);
	 interval = 0;
	 n_inputs = 0;
	 for(nrbytes=0; nrbytes<max_file_analog;)
	 {
		interv = mb->second_interval_time+mb->minute_interval_time*60+
						 mb->hour_interval_time*3600;
		if(!memcmp(mb->inputs,inp, sizeof(Point_Net)*mb->no_points) &&
			 interval==interv && n_inputs == mb->no_points)
		{
		 ;
		}
		else
		{
		 j++;
		 memcpy(inp, mb->inputs, sizeof(Point_Net)*MAX_POINTS_IN_MONITOR);
		 interval = interv;
		 n_inputs = mb->no_points;
		}
		 nrbytes += sizeof(Mini_Monitor_Block)-4*MAX_ANALOG_SAMPLES_PER_BLOCK+4*mb->index;
		 mb = (Mini_Monitor_Block *)(((char *)mb)+sizeof(Mini_Monitor_Block)-4*MAX_ANALOG_SAMPLES_PER_BLOCK+4*mb->index);
	 }
	 ind_headers = j;
	 set_semaphore_dos();
	 headers = new Header_amon[ind_headers+1];
	 clear_semaphore_dos();
	 mb = (Mini_Monitor_Block *)mon_table;
	 pmon_table = (char *)mon_table;

	 j=0;

	 prev_size = 0;
	 for(nrbytes=0; nrbytes<max_file_analog;)
	 {
		(headers+j)->prev_header=(long)pmon_table;
		memcpy((headers+j)->inputs, mb->inputs, sizeof(Point_Net)*MAX_POINTS_IN_MONITOR);
		interv = mb->second_interval_time+mb->minute_interval_time*60+
						 mb->hour_interval_time*3600;
		(headers+j)->interval = interv;
		(headers+j)->n_inputs = mb->no_points;

		if(mb->no_points == 0)
		{
		 return ERROR_COMM;
		}/*devide by ZERO!!!*/
		(headers+j)->n_sample = mb->index/mb->no_points;
		(headers+j)->time_last_sample = mb->start_time+interv*(((headers+j)->n_sample)-1)+timezone;
		kl = sizeof(Mini_Monitor_Block)-4*MAX_ANALOG_SAMPLES_PER_BLOCK+4*mb->index;

		prev_size  =  (mb->index)*4;
		memmove(pmon_table, (char *)(mb->data.analog), (mb->index)*4);
		pmon_table += prev_size;

		nrbytes += kl;
		mb = (Mini_Monitor_Block *)(((char *)mb)+ kl);

		while(nrbytes<max_file_analog)
		{
		 interv = mb->second_interval_time+mb->minute_interval_time*60+
						 mb->hour_interval_time*3600;
		 if(!memcmp(mb->inputs,(headers+j)->inputs, sizeof(Point_Net)*(headers+j)->n_inputs) &&
			 (headers+j)->interval==interv && (headers+j)->n_inputs == mb->no_points)
		 {
			 if(mb->no_points == 0)
			 {
				return ERROR_COMM;
			 }/*devide by ZERO!!!*/
			 (headers+j)->n_sample += mb->index/mb->no_points;
			 (headers+j)->time_last_sample = mb->start_time+interv*(mb->index/mb->no_points-1)+timezone;
			 kl = sizeof(Mini_Monitor_Block)-4*MAX_ANALOG_SAMPLES_PER_BLOCK+4*mb->index;
			 prev_size  =  (mb->index)*4;
			 memmove(pmon_table, (char *)(mb->data.analog), (mb->index)*4);
			 pmon_table += prev_size;
			 nrbytes += kl;
			 mb = (Mini_Monitor_Block *)(((char *)mb) + kl);
		 }
		 else
			break;
		}
		j++;
	 }
	 pmem_table = (long *)pmon_table;

	 t[0] = headers[0].time_last_sample-(headers[0].n_sample-1)*headers[0].interval;
	 t[1] = headers[ind_headers-1].time_last_sample;


// read digital
//QQ
/*
	 if(net_call(READMONITORDATA_T3000, (DIGITALBUFSIZE<<8)+ind, (char *)&l, NULL, panel, network, NETCALL_SIGN, 40,
					NULL, NULL, (char *)t, 8)!=SUCCESS)
		 return ERROR_COMM;
	 max_file_dig = l;
	 l += 400+MAX_HEADERS_DMON*sizeof(Header_dmon);
	 mfarmalloc((char far **)&dmon_table, (long)l, dmon_table_handle);

	 if( !dmon_table )
	 {
		max_file_dig = MAX_MEM_DIG_BUF;
		l = max_file_dig+400+MAX_HEADERS_DMON*sizeof(Header_dmon);
		mfarmalloc((char far **)&dmon_table, (long)l, dmon_table_handle);
	 }

	 if( dmon_table )
	 {
		 if(net_call(READMONITORDATA_T3000, (DIGITALDATA<<8)+ind, (char *)dmon_table, &max_file_dig, panel, network, NETCALL_SIGN, 40,
					NULL, NULL, (char *)t, 8)!=SUCCESS)
		 return ERROR_COMM;
		 ind_headers_dig=1;
		 set_semaphore_dos();
		 headers_dig = new Header_dmon[ind_headers_dig+1];
		 clear_semaphore_dos();
		 mb = (Mini_Monitor_Block *)dmon_table;
		 pmon_table = (char *)dmon_table;
		 j=0;
		 headers_dig[0].prev_header=(long)pmon_table;
		 headers_dig[0].n_inputs = mb->no_points;
		 nrbytes = 0;
		 while(nrbytes<max_file_analog)
		 {
			nrbytes += sizeof(Mini_Monitor_Block)-4*MAX_ANALOG_SAMPLES_PER_BLOCK+4*mb->index;
			if( nrbytes>=max_file_analog ) break;
			mb = (Mini_Monitor_Block *)(((char *)mb)+sizeof(Mini_Monitor_Block)-4*MAX_ANALOG_SAMPLES_PER_BLOCK+4*mb->index);
		 }
		 memcpy(headers_dig[0].inputs, mb->inputs, sizeof(Point_Net)*MAX_POINTS_IN_MONITOR);
		 l = 0;
		 l1 = 0;
		 mb = (Mini_Monitor_Block *)pmon_table;
		 ptable = (long *)pmon_table;
		 for(i = 0; i<headers_dig[0].n_inputs; i++)
		 {
			headers_dig[0].offset[i] = l;
			l1=0;
			first = 1;
			for(nrbytes=0; nrbytes<max_file_dig;)
			{
			 for(k=0;k<MAX_DIGITAL_SAMPLES_PER_BLOCK;k++)
			 {
				 if( mb->data.digital[k].point_no == i )
				 {
					 if(first)
					 {
						 headers_dig[0].onoff[i] = !mb->data.digital[k].value;
						 first=0;
					 }
					 *ptable++ = mb->data.digital[k].time;
					 l1++;
				 }
			 }
			 nrbytes += sizeof(Mini_Monitor_Block)-4*MAX_ANALOG_SAMPLES_PER_BLOCK+4*mb->index;
			 mb = (Mini_Monitor_Block *)(((char *)mb)+sizeof(Mini_Monitor_Block)-4*MAX_ANALOG_SAMPLES_PER_BLOCK+4*mb->index);
			}
			l += l1;
			headers_dig[0].n_sample[i] = l1;
			headers_dig[0].time_last_sample[i] = *(ptable-1);
		 }
	 }

	*/
	}
	else
	{
	 mfarmalloc((char far **)&mon_table, l, mon_table_handle);
	 Delay(500);
	 if(net_call(READMONITORDATA_T3000, ind, (char *)mon_table, 0, panel, network, NETCALL_SIGN, 40))
		 return ERROR_COMM;
	 l=mon_table[0];
	 mon_table++;
	 pmon_table = (char *)mon_table + l*4;
	 pmem_table = (long *)pmon_table;
	 memcpy(&index_last_value, pmon_table, 2);
	 memcpy(&last_mem_block, pmon_table+2, 1);
	 memcpy(&nsample_mem_block, pmon_table+3, 2);
	 memcpy(&sample, pmon_table+5, 2);
//	memcpy(&l, pmon_table+7, 2);
//	pmem_table = (long *)((char *)mon_table + l);
	 memcpy(&ind_headers, pmon_table+9, 2);
	 set_semaphore_dos();
	 headers = new Header_amon[ind_headers+1];
	 clear_semaphore_dos();
//	headers = (Header_amon *)(mon_table + 650);
	 memmove(headers, pmon_table + 11, ind_headers*sizeof(Header_amon));
	 pmon_table += 11 + ind_headers*sizeof(Header_amon);

	 memcpy(&l, pmon_table, 4);
//	 dmon_table = (long *) (((char*)mon_table) + max_file+MAX_INP*10*4 + MAX_HEADERS_AMON*sizeof(Header_amon) + MAX_HEADERS_DMON*sizeof(Header_dmon));
	 dmon_table = (long *) (((char*)mon_table) + max_file+MAX_INP*MAXSAMPLEUPDATE*4 + MAX_HEADERS_AMON*sizeof(Header_amon));
	 pmon_table += 4;

	 memcpy(&nsample_mem_dig_block, pmon_table + l*4 , 2);
	 mem_dmon_table =  (char *)(dmon_table + (l-nsample_mem_dig_block));
	 memcpy(&ind_headers_dig, pmon_table+2+l*4, 2);
	 set_semaphore_dos();
	 headers_dig = new Header_dmon[ind_headers_dig+1];
	 clear_semaphore_dos();
	 memmove(headers_dig, pmon_table + 4 + l*4, ind_headers_dig*sizeof(Header_dmon));

	 memmove(dmon_table, pmon_table, l*4);
	 pmon_table += l*4;

	 l=0;
	 for(int i=0;i<ind_headers; i++)
	 {
		headers[i].prev_header = (long)((char *)(mon_table)+l);
		l += (long)headers[i].n_sample*(long)headers[i].n_inputs*4L;
	 }
	 l=0;
	 for(i=0;i<ind_headers_dig; i++)
	 {
		headers_dig[i].prev_header = (long)(dmon_table+l);
		for(int j=0;j<headers_dig[i].n_inputs;j++)
			 l += headers_dig[i].n_sample[j];
	 }

	}


	setscale(viewport);
	justsavemem = 0;

	return SUCCESS;
}

/*
int readnettable(int ind, hot_box *viewport, int panel, int network)
{
	long interv, max_file, l, l1, t[2], *ptable;
	uint max_file_analog, max_file_dig, nrbytes;
	int i, j, k, first;
	char *pmon_table;
	max_file=(long)MAX_SAMPLE*(long)MAX_INP*4L;
	max_file_dig = MAX_MEM_DIG_BUF;
	current_mon = ind;
//	set_semaphore_dos();
//	mon_table = new long[ max_file/4+140 + max_file_dig/4+100 + 110 + 110];
//	clear_semaphore_dos();
//#ifdef MEMORY_1M
//	mon_table = (long *)MK_FP(0xB400, 0 );
//#else
//memsize();
	dmon_table_handle=0;
	l = max_file+MAX_INP*MAXSAMPLEUPDATE*4L+(long)max_file_dig+400L + MAX_HEADERS_AMON*sizeof(Header_amon) + MAX_HEADERS_DMON*sizeof(Header_dmon);
//	mfarmalloc((char far **)&mon_table, l, mon_table_handle);
//memsize();
//#endif
	if( panel_info1.panel_type == MINI_T3000 )
	{
	 Mini_Monitor_Block *mb;
	 Point_Net inp[MAX_POINTS_IN_MONITOR];
	 long interval,kl;
	 int n_inputs;
//	 max_file_analog = (int)(max_file+MAX_INP*10*4)
	 max_file_analog = (int)(max_file);
	 max_file_analog = (max_file_analog/sizeof(Mini_Monitor_Block))*sizeof(Mini_Monitor_Block);
	 l = max_file_analog + MAX_INP*10*4L + MAX_HEADERS_AMON*sizeof(Header_amon);
	 mfarmalloc((char far **)&mon_table, (long)l, mon_table_handle);

	 t[0] = max_file_analog;
	 t[1] = timesec1970 + timestart;

	 if(net_call(READMONITORDATA_T3000, (ANALOGDATA<<8)+ind, (char *)mon_table, &max_file_analog, panel, network, NETCALL_SIGN, 40,
					NULL, NULL, (char *)t, 8)!=SUCCESS)
		 return ERROR_COMM;

//	 nrbytes = max_file_analog/sizeof(Mini_Monitor_Block);
	 mb = (Mini_Monitor_Block *)mon_table;
	 j=0;
	 memset(inp, 0, sizeof(Point_Net)*MAX_POINTS_IN_MONITOR);
	 interval = 0;
	 n_inputs = 0;
	 for(nrbytes=0; nrbytes<max_file_analog;)
	 {
		interv = mb->second_interval_time+mb->minute_interval_time*60+
						 mb->hour_interval_time*3600;
		if(!memcmp(mb->inputs,inp, sizeof(Point_Net)*mb->no_points) &&
			 interval==interv && n_inputs == mb->no_points)
		{
		 ;
		}
		else
		{
		 j++;
		 memcpy(inp, mb->inputs, sizeof(Point_Net)*MAX_POINTS_IN_MONITOR);
		 interval = interv;
		 n_inputs = mb->no_points;
		}
		 nrbytes += sizeof(Mini_Monitor_Block)-4*MAX_ANALOG_SAMPLES_PER_BLOCK+4*mb->index;
		 mb = (Mini_Monitor_Block *)(((char *)mb)+sizeof(Mini_Monitor_Block)-4*MAX_ANALOG_SAMPLES_PER_BLOCK+4*mb->index);
	 }
	 ind_headers = j;
	 set_semaphore_dos();
	 headers = new Header_amon[ind_headers+1];
	 clear_semaphore_dos();
	 mb = (Mini_Monitor_Block *)mon_table;
	 pmon_table = (char *)mon_table;
	 j=0;

	 for(nrbytes=0; nrbytes<max_file_analog;)
	 {
		(headers+j)->prev_header=(long)pmon_table;
		memcpy((headers+j)->inputs, mb->inputs, sizeof(Point_Net)*MAX_POINTS_IN_MONITOR);
		interv = mb->second_interval_time+mb->minute_interval_time*60+
						 mb->hour_interval_time*3600;
		(headers+j)->interval = interv;
		(headers+j)->n_inputs = mb->no_points;
		(headers+j)->n_sample = mb->index/mb->no_points;
		(headers+j)->time_last_sample = mb->start_time+interv*(((headers+j)->n_sample)-1);
		kl = sizeof(Mini_Monitor_Block)-4*MAX_ANALOG_SAMPLES_PER_BLOCK+4*mb->index;
		memmove( pmon_table, (char *)(mb->data.analog), (headers+j)->n_sample*(headers+j)->n_inputs*4 );
		pmon_table += (headers+j)->n_sample*(headers+j)->n_inputs*4;
//		mb++;    // skip header
		nrbytes += kl;
		mb = (Mini_Monitor_Block *)(((char *)mb)+ kl);
//		i++;
//		while(i<nrblock)
		while(nrbytes<max_file_analog)
		{
		 interv = mb->second_interval_time+mb->minute_interval_time*60+
						 mb->hour_interval_time*3600;
		 if(!memcmp(mb->inputs,(headers+j)->inputs, sizeof(Point_Net)*(headers+j)->n_inputs) &&
			 (headers+j)->interval==interv && (headers+j)->n_inputs == mb->no_points)
		 {
			(headers+j)->n_sample += mb->index/mb->no_points;
			(headers+j)->time_last_sample = mb->start_time+interv*(((headers+j)->n_sample)-1);
			kl = sizeof(Mini_Monitor_Block)-4*MAX_ANALOG_SAMPLES_PER_BLOCK+4*mb->index;
			memmove(pmon_table, (char *)(mb->data.analog), (headers+j)->n_sample*(headers+j)->n_inputs*4);
			pmon_table += (headers+j)->n_sample*(headers+j)->n_inputs*4;
//			mb++;    // skip header
			nrbytes += kl;
			mb = (Mini_Monitor_Block *)(((char *)mb) + kl);
//			i++;
		 }
		 else
			break;
		}
		j++;
	 }
	 pmem_table = (long *)pmon_table;

// read digital
	 t[0] = headers[0].time_last_sample-(headers[0].n_sample-1)*headers[0].interval;
	 t[1] = headers[ind_headers-1].time_last_sample;
	 if(net_call(READMONITORDATA_T3000, (DIGITALBUFSIZE<<8)+ind, (char *)&l, NULL, panel, network, NETCALL_SIGN, 40,
					NULL, NULL, (char *)t, 8)!=SUCCESS)
		 return ERROR_COMM;
	 max_file_dig = l;
	 l += 400+MAX_HEADERS_DMON*sizeof(Header_dmon);
	 mfarmalloc((char far **)&dmon_table, (long)l, dmon_table_handle);
	 if( !dmon_table )
	 {
		max_file_dig = MAX_MEM_DIG_BUF;
		l = max_file_dig+400+MAX_HEADERS_DMON*sizeof(Header_dmon);
		mfarmalloc((char far **)&dmon_table, (long)l, dmon_table_handle);
	 }
	 if( dmon_table )
	 {
		 if(net_call(READMONITORDATA_T3000, (DIGITALDATA<<8)+ind, (char *)dmon_table, &max_file_dig, panel, network, NETCALL_SIGN, 40,
					NULL, NULL, (char *)t, 8)!=SUCCESS)
		 return ERROR_COMM;
		 ind_headers_dig=1;
		 set_semaphore_dos();
		 headers_dig = new Header_dmon[ind_headers_dig+1];
		 clear_semaphore_dos();
		 mb = (Mini_Monitor_Block *)dmon_table;
		 pmon_table = (char *)dmon_table;
		 j=0;
		 headers_dig[0].prev_header=(long)pmon_table;
		 headers_dig[0].n_inputs = mb->no_points;
		 nrbytes = 0;
		 while(nrbytes<max_file_analog)
		 {
			nrbytes += sizeof(Mini_Monitor_Block)-4*MAX_ANALOG_SAMPLES_PER_BLOCK+4*mb->index;
			if( nrbytes>=max_file_analog ) break;
			mb = (Mini_Monitor_Block *)(((char *)mb)+sizeof(Mini_Monitor_Block)-4*MAX_ANALOG_SAMPLES_PER_BLOCK+4*mb->index);
		 }
		 memcpy(headers_dig[0].inputs, mb->inputs, sizeof(Point_Net)*MAX_POINTS_IN_MONITOR);
		 l = 0;
		 l1 = 0;
		 mb = (Mini_Monitor_Block *)pmon_table;
		 ptable = (long *)pmon_table;
		 for(i = 0; i<headers_dig[0].n_inputs; i++)
		 {
			headers_dig[0].offset[i] = l;
			l1=0;
			first = 1;
			for(nrbytes=0; nrbytes<max_file_dig;)
			{
			 for(k=0;k<MAX_DIGITAL_SAMPLES_PER_BLOCK;k++)
			 {
				 if( mb->data.digital[k].point_no == i )
				 {
					 if(first)
					 {
						 headers_dig[0].onoff[i] = !mb->data.digital[k].value;
						 first=0;
					 }
					 *ptable++ = mb->data.digital[k].time;
					 l1++;
				 }
			 }
			 nrbytes += sizeof(Mini_Monitor_Block)-4*MAX_ANALOG_SAMPLES_PER_BLOCK+4*mb->index;
			 mb = (Mini_Monitor_Block *)(((char *)mb)+sizeof(Mini_Monitor_Block)-4*MAX_ANALOG_SAMPLES_PER_BLOCK+4*mb->index);
			}
			l += l1;
			headers_dig[0].n_sample[i] = l1;
			headers_dig[0].time_last_sample[i] = *(ptable-1);
		 }
	 }
	}
	else
	{
	 mfarmalloc((char far **)&mon_table, l, mon_table_handle);
	 Delay(500);
	 if(net_call(READMONITORDATA_T3000, ind, (char *)mon_table, 0, panel, network, NETCALL_SIGN, 40))
		 return ERROR_COMM;
	 l=mon_table[0];
	 mon_table++;
	 pmon_table = (char *)mon_table + l*4;
	 pmem_table = (long *)pmon_table;
	 memcpy(&index_last_value, pmon_table, 2);
	 memcpy(&last_mem_block, pmon_table+2, 1);
	 memcpy(&nsample_mem_block, pmon_table+3, 2);
	 memcpy(&sample, pmon_table+5, 2);
//	memcpy(&l, pmon_table+7, 2);
//	pmem_table = (long *)((char *)mon_table + l);
	 memcpy(&ind_headers, pmon_table+9, 2);
	 set_semaphore_dos();
	 headers = new Header_amon[ind_headers+1];
	 clear_semaphore_dos();
//	headers = (Header_amon *)(mon_table + 650);
	 memmove(headers, pmon_table + 11, ind_headers*sizeof(Header_amon));
	 pmon_table += 11 + ind_headers*sizeof(Header_amon);

	 memcpy(&l, pmon_table, 4);
//	 dmon_table = (long *) (((char*)mon_table) + max_file+MAX_INP*10*4 + MAX_HEADERS_AMON*sizeof(Header_amon) + MAX_HEADERS_DMON*sizeof(Header_dmon));
	 dmon_table = (long *) (((char*)mon_table) + max_file+MAX_INP*MAXSAMPLEUPDATE*4 + MAX_HEADERS_AMON*sizeof(Header_amon));
	 pmon_table += 4;

	 memcpy(&nsample_mem_dig_block, pmon_table + l*4 , 2);
	 mem_dmon_table =  (char *)(dmon_table + (l-nsample_mem_dig_block));
	 memcpy(&ind_headers_dig, pmon_table+2+l*4, 2);
	 set_semaphore_dos();
	 headers_dig = new Header_dmon[ind_headers_dig+1];
	 clear_semaphore_dos();
	 memmove(headers_dig, pmon_table + 4 + l*4, ind_headers_dig*sizeof(Header_dmon));

	 memmove(dmon_table, pmon_table, l*4);
	 pmon_table += l*4;

	 l=0;
	 for(int i=0;i<ind_headers; i++)
	 {
		headers[i].prev_header = (long)((char *)(mon_table)+l);
		l += (long)headers[i].n_sample*(long)headers[i].n_inputs*4L;
	 }
	 l=0;
	 for(i=0;i<ind_headers_dig; i++)
	 {
		headers_dig[i].prev_header = (long)(dmon_table+l);
		for(int j=0;j<headers_dig[i].n_inputs;j++)
			 l += headers_dig[i].n_sample[j];
	 }
	}
	setscale(viewport);
	justsavemem = 0;
	return SUCCESS;
}
*/

// pt type = 1 , programul apelant trebuie sa faca delete pe pointerul returnat
//char *readmontable(int ind, int *length, long **mon_table, int type)  //type = 1 retea ; 0 local
//unsigned readdigtable(int ind, long time_last_sample, long time_first_sample, long **dmon_table, int type)
unsigned readdigtable(int ind, long **dmon_table, int type)
{
	Point_Net p;
	int num_point,num_net, num_panel,nsample,j,i,v,k,n,ssample, ind_headers_dig_loc, nsample_mem_dig_block_loc;
  int network;
	byte var_type, point_type;
	Header_dmon header_dmon, header_dmon1,h_dmon, **pheaders, *headers_net;
	long ltot,m,max_file,l,offset,*pmem_table_net, l2,l1, *ptable;
	char label[13],*filename,*pmon_table;
	char *mem_dmon_table_loc;
	FILE *h1;
//!!	float *t,lasts[14];
//	long *t;

	set_semaphore_dos();
	filename = new char[80];
	clear_semaphore_dos();
	if( rs485port!=-1 )
	{
	 network=(( class ConnectionData *)Routing_table[rs485port].ptr)->panel_info1.network;
	}
	else
	 network = NetworkAddress;
	memset( &header_dmon, 0, sizeof(Header_dmon) );
	p.putpoint(ind-1, AMON + 1, Station_NUM-1, network);
	pointtotext(filename,&p);
	strcpy(label,ispoint(rtrim(filename),&num_point,&var_type, &point_type, &num_panel, &num_net, network, Station_NUM));
	strcat(label,".DIG");

	ind--;
	max_file=MAX_MEM_DIG_BUF;
//	set_semaphore_dos();
	if(!type)
	{
		mfarmalloc((char far **)dmon_table, (max_file/4+180)*4,dmon_table_handle);
//	 *dmon_table = new long[max_file/4+180];
	}
//	clear_semaphore_dos();
	if(!(*dmon_table)) exit(1);
	if(type) (*dmon_table)++;

	set_semaphore(&read_mon_flag);
	ssample = nsample_mem_dig_mon[ind];
/*
	 if(!type)
		 time_last_sample = ptr_panel->analog_mon[ind].last_sample_time;
	 else
		 time_last_sample_net = ptr_panel->analog_mon[ind].last_sample_time;
*/
////////////
	if(type)
		pheaders = &headers_net;
	else
		pheaders = &headers_dig;

	nsample_mem_dig_block_loc = 0;
	ind_headers_dig_loc = 0;
	ltot = 0;

	pmon_table=(char *)(*dmon_table);
	mem_dmon_table_loc =  pmon_table;
	v=0;
	n=-1;
	l=0;
	filename[0] = 0;
	strcpy(filename, ptr_panel->Monitor_Path);
	if(strlen(filename)) strcat(filename, "\\");
	strcat(filename, label);
	v=0;
	l2 = 4;
	max_file -= (long)(ssample+50)*4L;
	var_type = 1;
	set_semaphore_dos();
	if( ptr_panel->analog_mon[ind].num_inputs-ptr_panel->analog_mon[ind].anum_inputs )
	if (max_file > 8)
	 if( (h1=fopen(filename,"r+b"))!=NULL)
	 {
		var_type = 0;
		fread(&offset, 4, 1, h1);
		fseek(h1, offset, SEEK_SET);
		clear_semaphore_dos();
		do
		{
		 l2 = ftell(h1);
		 set_semaphore_dos();
		 fread(&header_dmon, sizeof(Header_dmon), 1, h1);
		 clear_semaphore_dos();

		 nsample = 0;
		 for(i=0;i<header_dmon.n_inputs;i++)
			 nsample += header_dmon.n_sample[i];

		 if((m=(long)(ltot+nsample)*4L-max_file)>=0L)
		 {
//			if(m)
//			{
				l = m%4L?m/4L+1:m/4L;
				l2 = ftell(h1);
				header_dmon.prev_header = (long)(*dmon_table);
				header_dmon1 = header_dmon;
				for(i=0;i<header_dmon.n_inputs;i++)
				{
				 l1 = (header_dmon.n_sample[i] * l)/nsample;
				 l1 += (header_dmon.n_sample[i] * l)%nsample?1:0;
				 if( (int)header_dmon.n_sample[i] - l1 < 0 ) header_dmon.n_sample[i]=0;
				 else header_dmon.n_sample[i] -= l1;
				}
				ltot=0;
				set_semaphore_dos();
				for(i=0;i<header_dmon.n_inputs;i++)
				{
				 if(header_dmon.n_sample[i])
				 {
					header_dmon.offset[i] = ltot;
					fseek(h1, (header_dmon1.offset[i]+(header_dmon1.n_sample[i]-header_dmon.n_sample[i]))*4L+l2, SEEK_SET);
					fread(((char *)header_dmon.prev_header)+ltot*4L, header_dmon.n_sample[i]*4L, 1, h1);
					ltot += header_dmon.n_sample[i];
				 }
				}
			  clear_semaphore_dos();
				if(ltot)
				{
				 n++;
				 v=1;
				}
				l2 += nsample*4L;
//			} //end if m
				break;
		 }
		 else
		 {
			n++;
			if(n>=MAX_HEADERS_DMON-2) {ltot = 0; break;}
			if(header_dmon.prev_header)
			 {
				ltot += nsample;
				set_semaphore_dos();
				fseek(h1, (long)header_dmon.prev_header, SEEK_SET);
				clear_semaphore_dos();
			 }
			else
			 {
				ltot = 0;
				break;
			 }
		 }
		} while (1);

		if(n>=0)
		{
		 set_semaphore_dos();
		 (*pheaders) = new Header_dmon[n+2];
		 clear_semaphore_dos();
		 if(!(*pheaders)) exit(1);
		 memset((*pheaders) , 0, (n+2) * sizeof(header_dmon));
		}
		if(v)
		{
		 (*pheaders)[0] = header_dmon;
		 ind_headers_dig_loc = 1;
//	pmon_table = (char *)(*dmon_table + ((*pheaders)[0].offset[(*pheaders)[0].n_inputs-1] + (*pheaders)[0].n_sample[(*pheaders)[0].n_inputs-1]) * 4L);
		 pmon_table = (char *)(*dmon_table + ((*pheaders)[0].offset[(*pheaders)[0].n_inputs-1] + (*pheaders)[0].n_sample[(*pheaders)[0].n_inputs-1]) );
		}

		set_semaphore_dos();

		fseek(h1, 0 , SEEK_END);
		l1 = ftell(h1);
		fseek(h1, l2 , SEEK_SET);
		while(l2 < l1)
		{
		  fread((*pheaders)+ind_headers_dig_loc++, sizeof(Header_dmon), 1, h1);
		  (*pheaders)[ind_headers_dig_loc-1].prev_header = (long )pmon_table;
		  nsample = 0;
		  for(i=0;i<(*pheaders)[ind_headers_dig_loc-1].n_inputs;i++)
		  {
			 nsample += (*pheaders)[ind_headers_dig_loc-1].n_sample[i];
		  }
		  fread(pmon_table, nsample*4L , 1, h1);
		  pmon_table += nsample*4L;
		  l2 += sizeof(Header_dmon) + nsample*4L;
		  ltot += nsample;
		}
		fclose(h1);
		clear_semaphore_dos();
	 }
	 else
		clear_semaphore_dos();

	set_semaphore_dos();
	if(filename)
	 delete filename;
	clear_semaphore_dos();

	if(var_type)
	if(!ind_headers_dig_loc)
	{
	 set_semaphore_dos();
	 (*pheaders) = new Header_dmon[n+2];
	 if(!(*pheaders)) exit(1);
	 memset((*pheaders) , 0, (n+2) * sizeof(header_dmon));
	 clear_semaphore_dos();
	}

 mem_dmon_table_loc =  pmon_table;
 l = 0;
// if(ssample)
 if(nsample_mem_dig_mon[ind])
 {
//	nsample_mem_dig_block_loc = ssample;
	ind_headers_dig_loc++;

	ptable = (long *)pmon_table;
	(*pheaders)[ind_headers_dig_loc-1].prev_header = (long)ptable;
	(*pheaders)[ind_headers_dig_loc-1].n_inputs = ptr_panel->analog_mon[ind].num_inputs-ptr_panel->analog_mon[ind].anum_inputs;
	memcpy((*pheaders)[ind_headers_dig_loc-1].inputs,&ptr_panel->analog_mon[ind].inputs[ptr_panel->analog_mon[ind].anum_inputs],(*pheaders)[ind_headers_dig_loc-1].n_inputs*sizeof(Point_Net));
	init_heap_dmon = 1;
	for(i=0;i<ptr_panel->analog_mon[ind].num_inputs-ptr_panel->analog_mon[ind].anum_inputs;i++)
	{
	 if(ptr_panel->monitor_work_data[ind].start_index_dig[i] != 0x0FFFF)
	 {
		l1 = 0;
		(*pheaders)[ind_headers_dig_loc-1].offset[i] = l;
		for(j=ptr_panel->monitor_work_data[ind].start_index_dig[i]; j != ptr_panel->monitor_work_data[ind].end_index_dig[i]; j = heap_dmon[j].next)
		{
		 *ptable++ = heap_dmon[j].time;
		 l1++;
		}
		*ptable++ = heap_dmon[j].time;
		(*pheaders)[ind_headers_dig_loc-1].time_last_sample[i] = heap_dmon[j].time;
		l1++;
		l += l1;
		(*pheaders)[ind_headers_dig_loc-1].n_sample[i] = l1;
		(*pheaders)[ind_headers_dig_loc-1].onoff[i] = heap_dmon[ptr_panel->monitor_work_data[ind].start_index_dig[i]].onoff;
	 }
	}
	nsample_mem_dig_block_loc = nsample_mem_dig_mon[ind];
	init_heap_dmon = 0;
 }
 clear_semaphore(&read_mon_flag);
 if(!type)
 {
  ind_headers_dig = ind_headers_dig_loc;
  mem_dmon_table = mem_dmon_table_loc;
  nsample_mem_dig_block = nsample_mem_dig_block_loc;
 }
 else
 {
		*((*dmon_table)-1) = l+ltot;
		l = (l+ltot) *4;
		pmon_table = (char *)(*dmon_table) + l;
		memcpy(pmon_table,&nsample_mem_dig_block_loc, 2);
		memcpy(pmon_table+2, &ind_headers_dig_loc, 2);
		memmove(pmon_table + 4, (*pheaders), ind_headers_dig_loc*sizeof(Header_dmon));
		l += 4 + 4 + ind_headers_dig_loc*sizeof(Header_dmon);
		set_semaphore_dos();
		delete (*pheaders);
		clear_semaphore_dos();
		return l;
 }
}

void readtable(int ind, hot_box *viewport)
{
	readmontable(ind, NULL, &mon_table, 0);
	setscale(viewport);
}

long whatinterv(unsigned long *timefirstsample,unsigned long *timelastsample)
{
 unsigned long k,timefirst;
 long max = -10000;
 if(!ind_headers)
 {
//	max = (unsigned long)ptr_panel->analog_mon[current_mon-1].hour_interval_time*3600L+
//				 (unsigned long)ptr_panel->analog_mon[current_mon-1].minute_interval_time*60L+
//				 (unsigned long)ptr_panel->analog_mon[current_mon-1].second_interval_time;
	max = (unsigned long)current_analog_mon->hour_interval_time*3600L+
				 (unsigned long)current_analog_mon->minute_interval_time*60L+
				 (unsigned long)current_analog_mon->second_interval_time;
	if( *timelastsample < *timefirstsample + max)
     return max;

	k = *timelastsample;
	while(k >= *timefirstsample)
		k -= max;
	k += max;
	if (k != *timelastsample)
		*timefirstsample = k;
	return max;
 }
 for(int i=0;i<ind_headers;i++)
	if(*timefirstsample<=headers[i].time_last_sample) break;
 for(int j=i;j<ind_headers;j++)
	{
	 if(max<headers[j].interval) max=headers[j].interval;
	 if(*timelastsample<=headers[j].time_last_sample) break;
	}
 timefirst = headers[j].time_last_sample - (headers[j].n_sample-1)*headers[j].interval;
 for(k=timefirst;k<=headers[j].time_last_sample;k += headers[j].interval)
	 if(*timelastsample <= k)
		break;
	*timefirstsample += k - *timelastsample;
	*timelastsample = k;
 return max;
}


void savemonitor(int ind)
{
	byte var_type, point_type;
	int num_net,num_point, num_panel;
	int network,handle,i,j,nsample,old;
//  byte num_point,var_type, point_type, num_panel;
	char *label1,label[13],buf[13],*filename,*table=NULL;
	Point_Net p;
//	float *t,lasts[14];
	long *t, *lasts;    //,lasts[MAX_POINTS_IN_MONITOR];
	Header_amon *header_amon;
	unsigned long f,timelastsample,timefirstsample;
	long k,last,l1,l2,interv,l,offset;
	FILE *h;
	if( rs485port!=-1 )
	{
	 network=(( class ConnectionData *)Routing_table[rs485port].ptr)->panel_info1.network;
	}
	else
	 network = NetworkAddress;
	p.putpoint(ind-1, AMON + 1, Station_NUM-1, network);
	pointtotext(buf,&p);
	strcpy(label,ispoint(rtrim(buf),&num_point,&var_type, &point_type, &num_panel, &num_net, network, Station_NUM));
//	strcpy(label,ispoint(rtrim(buf),(int *)&num_net,(byte *)&num_net, (byte *)&num_net, (int *)&num_net, &num_net, network, Station_NUM));
	strcat(label,ext);
  ind--;
  t = (long *)ptr_panel->monitor_work_data[ind].data_segment;
//////
//	set_semaphore(&t3000_flag);
  nsample = ptr_panel->monitor_work_data[ind].head_index;
  timelastsample = ptr_panel->monitor_work_data[ind].last_sample_time;
  ptr_panel->monitor_work_data[ind].head_index=0;
	l = nsample * ptr_panel->analog_mon[ind].anum_inputs * 4;
//	set_semaphore(&t3000_flag);
//	present_analog_monitor=0;
	mfarmalloc((char far **)&table, l + 65 + MAX_POINTS_IN_MONITOR*4 + sizeof(Header_amon));
	if(table)
	{
//	set_semaphore_dos();
//	table = new char[l];
//	clear_semaphore_dos();
	memcpy(table,t,l);
//	clear_semaphore(&t3000_flag);
//	present_analog_monitor=1;
//	clear_semaphore(&t3000_flag);
//////
	psample(&interv, &ptr_panel->analog_mon[ind]);
	timefirstsample = timelastsample-(nsample-1)*interv;

	filename = table+l;
	lasts = (long *)(filename+64);
	header_amon = (Header_amon *)(lasts+MAX_POINTS_IN_MONITOR);
	old=0;
	offset=0;
	filename[0] = 0;
	strcpy(filename, ptr_panel->Monitor_Path);
	if(strlen(filename)) strcat(filename, "\\");
	strcat(filename, label);
	i=0;
	if( strchr(filename, ':') )
	  i = filename[0] - 'A' + 1;

	set_semaphore_dos();

	struct diskfree_t free;
int_disk = 1;
	j = _dos_getdiskfree(i, &free);
int_disk = 0;
	if ( j != 0)
	{
		l1 = 100000l;
	}
	else
		l1 = (long) free.avail_clusters * (long) free.bytes_per_sector
			 * (long) free.sectors_per_cluster;

int_disk = 1;
	num_net=0;
	if((h=fopen(filename,"r+b"))!=NULL)
	{
	 fseek(h, 0, SEEK_END);
	 l2 = ftell(h);
	 fseek(h, 0, SEEK_SET);
int_disk = 0;
	 if( l1+l2 < amon_file_length+6000 )
	 {
int_disk = 1;
		fclose(h);
int_disk = 0;
		clear_semaphore_dos();
		h = NULL;
		old = 1;
	 }
	 else
	 {
int_disk = 1;
		fread(&offset, 4, 1, h);
		fseek(h, offset, SEEK_SET);
		fread(header_amon, sizeof(Header_amon), 1, h);
int_disk = 0;
		clear_semaphore_dos();
		if( timefirstsample <= header_amon->time_last_sample)
		{
		 set_semaphore_dos();
		 while (1)
		 {
			f = header_amon->time_last_sample - ((long)header_amon->n_sample-1)*(long)header_amon->interval;
			if(timefirstsample<=f && header_amon->prev_header)
			{
int_disk = 1;
			fseek(h, (long)header_amon->prev_header, SEEK_SET);
			fread(header_amon, sizeof(Header_amon), 1, h);
int_disk = 0;
			if( feof(h) )
			{
			 num_net=1;
			 fclose(h);
			 h=fopen(filename,"w+b");
			 break;
			};
			continue;
		 }
		 else
		 {
			clear_semaphore_dos();
			k=0;
			for(i=0;i<header_amon->n_sample;i++)
			{
			 if(timefirstsample<=f)
			 {
				header_amon->n_sample=k;
				header_amon->time_last_sample = f-header_amon->interval;
				set_semaphore_dos();
int_disk = 1;
				l1=ftell(h);
				fseek(h, l1-(long)sizeof(Header_amon), SEEK_SET);
				fwrite(header_amon, sizeof(Header_amon), 1, h);
int_disk = 0;
				l1 += (long)k*4L*(long)header_amon->n_inputs;
int_disk = 1;
				fclose(h);
				int handle = open(filename, O_RDWR|O_BINARY);
				chsize(handle, l1);
				h = fdopen(handle, "r+b");
				fseek(h, offset, SEEK_SET);
				fread(header_amon, sizeof(Header_amon), 1, h);
int_disk = 0;
				clear_semaphore_dos();
				break;
			 }
			 else
			 {
				k++;
				f += header_amon->interval;
			 }
			}
			break;
		 } //if
		} //while
	 } //if
	 else
	 {
		k=0;
//		f=header_amon.time_last_sample+header_amon.interval;
		f=header_amon->time_last_sample+interv;
		if( timefirstsample > f)
		{
		 last=(long)header_amon->n_sample;
		 set_semaphore_dos();
int_disk = 1;
		 l1=ftell(h);
		 fseek(h, l1+(last-1)*4L*(long)header_amon->n_inputs, SEEK_SET);
		 fread(lasts, header_amon->n_inputs*4,1,h);
int_disk = 0;
		 clear_semaphore_dos();
		 while(timefirstsample > f && k<3000)
		 {
			k++;
			f += header_amon->interval;
		 }
       if(k>=3000) k=30000;
		 header_amon->n_sample += k;
		 header_amon->time_last_sample = f-header_amon->interval;
		 set_semaphore_dos();
		int_disk = 1;
		 fseek(h, l1-(long)sizeof(Header_amon), SEEK_SET);
		 fwrite(header_amon, sizeof(Header_amon), 1, h);
		int_disk = 0;
		 clear_semaphore_dos();
		 l1 += (long)header_amon->n_sample*4L*(long)header_amon->n_inputs;
		 l2 = psample(&interv, &ptr_panel->analog_mon[ind])*4L*(long)header_amon->n_inputs;
		 if(amon_file_length < l2) l2 =  amon_file_length;
		 Delay(100);
		 set_semaphore_dos();
		 if(l1 > l2)
		 {
			hmove = h;
			if(movefile(filename,(l1-l2)+(long)sizeof(Header_amon),&h))
			{
int_disk = 1;
				fread(&offset, 4, 1, h);
				fseek(h, offset, SEEK_SET);
				fread(header_amon, sizeof(Header_amon), 1, h);
				fseek(h, (long)(header_amon->n_sample-k)*4L*(long)header_amon->n_inputs, SEEK_CUR);
int_disk = 0;
				for(i=0;i<k;i++)
				{
int_disk = 1;
					fwrite(lasts,header_amon->n_inputs*4,1,h);
int_disk = 0;
				}
			}
			else
			{
			 header_amon->n_sample = (l2-sizeof(Header_amon)-4)/(header_amon->n_inputs*4);
			 offset = 4;
int_disk = 1;
			 fwrite(&offset,4,1,h);
			 header_amon->prev_header = 0;
			 fwrite(header_amon, sizeof(Header_amon), 1, h);
int_disk = 0;
			 for(i=0;i<header_amon->n_sample;i++)
			 {
int_disk = 1;
					fwrite(lasts,header_amon->n_inputs*4,1,h);
int_disk = 0;
			 }

			}
		 }
		 else
		 {
int_disk = 1;
			fseek(h, 0L, SEEK_END);
int_disk = 0;
			for(i=0;i<k;i++)
			{
int_disk = 1;
				fwrite(lasts,header_amon->n_inputs*4,1,h);
int_disk = 0;
			}
		 }
		 clear_semaphore_dos();
/*
		 fclose(h);
		 handle = open(label, O_RDWR);
		 chsize(handle, l1);
		 h = fdopen(handle, "rb+");
		 fseek(h, offset, SEEK_SET);
		 fread(&header_amon, sizeof(Header_amon), 1, h);
*/
		}
	 }
    if(!num_net)
	  if(header_amon->interval == interv)
		 if(header_amon->n_inputs == ptr_panel->analog_mon[ind].anum_inputs)
		 {
			for(i=0;i<header_amon->n_inputs;i++)
			{
			 for(j=0;j<header_amon->n_inputs;j++)
				{
//				 memcpy(&k,&ptr_panel->analog_mon[ind].inputs[j],2);
				 if(header_amon->inputs[i] == ptr_panel->analog_mon[ind].inputs[j]) break;
				}
			 if(j==header_amon->n_inputs) break;
			}
			if(j!=header_amon->n_inputs)
			{
			 header_amon->time_last_sample = timelastsample;
			 header_amon->n_sample += nsample;
			 set_semaphore_dos();
int_disk = 1;
			 fseek(h, offset, SEEK_SET);
			 fwrite(header_amon, sizeof(Header_amon), 1, h);
int_disk = 0;
			 clear_semaphore_dos();
int_disk = 1;
			 l1 = ftell(h);
int_disk = 0;
			 l1=l1+(long)header_amon->n_sample*4L*(long)header_amon->n_inputs;
			 l2 = psample(&interv, &ptr_panel->analog_mon[ind])*4L*(long)header_amon->n_inputs+sizeof(Header_amon)+4;
			 if(amon_file_length < l2) l2 =  amon_file_length;
			 Delay(100);
			 set_semaphore_dos();
			 if(l1 > l2)
			 {
				hmove = h;
				movefile(filename,(l1-l2),&h);
			 }
int_disk = 1;
			 fseek(h, 0L, SEEK_END);
int_disk = 0;
			 clear_semaphore_dos();
			 old = 1;
			}
		 }
	 }
	}
	else
	{
	 if((h=fopen(filename,"w+b"))==NULL)
	 {
		;  //       luata o actiune: second file_server
		old = 1;
	 }
int_disk = 0;
	 clear_semaphore_dos();
	}
	if(!old)
	{
		header_amon->n_inputs = ptr_panel->analog_mon[ind].anum_inputs;
		memcpy(&header_amon->inputs[0],&ptr_panel->analog_mon[ind].inputs[0],MAX_POINTS_IN_MONITOR*sizeof(Point_Net));
		psample(&header_amon->interval, &ptr_panel->analog_mon[ind]);
		header_amon->time_last_sample = timelastsample;
		header_amon->prev_header = offset;
		header_amon->n_sample = nsample;
		set_semaphore_dos();
		if(offset==0)
		{
			offset=4;
int_disk = 1;
			fseek(h, 0L, SEEK_SET);
			fwrite(&offset, 4, 1, h);
int_disk = 0;
		}
int_disk = 1;
		fseek(h, 0L, SEEK_END);
		offset=ftell(h);
int_disk = 0;
		clear_semaphore_dos();
		l2 = psample(&interv, &ptr_panel->analog_mon[ind])*4L*(long)header_amon->n_inputs+sizeof(Header_amon)+4;
		if(amon_file_length < l2) l2 =  amon_file_length;
		Delay(100);
		set_semaphore_dos();
		if(offset+(long)nsample*4L*(long)header_amon->n_inputs+sizeof(Header_amon)>l2)
		{
				 hmove = h;
				 header_amon->prev_header=movefile(filename,(offset+(long)nsample*4L*(long)header_amon->n_inputs+sizeof(Header_amon)-l2),&h);
		}
int_disk = 1;
		fseek(h, 0L, SEEK_END);
		offset=ftell(h);
		fseek(h, 0L, SEEK_SET);
		fwrite(&offset, 4, 1, h);
		fseek(h, 0L, SEEK_END);
		fwrite(header_amon, sizeof(Header_amon), 1, h);
int_disk = 0;
		clear_semaphore_dos();
	}
	if(h)
	{
	 set_semaphore_dos();
int_disk = 1;
	 fwrite(table, l, 1, h);
	 fclose(h);
int_disk = 0;
	 clear_semaphore_dos();
	}
	if(table)
//	 delete [] table;
	  mfarfree(table);
  }
	if(nsample) ptr_panel->monitor_work_data[ind].last_sample_saved_time = timelastsample;
  Delay(1000);
}

int savemonitordig(int ind)
{
	int num_point,num_net, num_panel,i,j,nsample,old;
	int network;
	byte var_type, point_type;
	char label[13],buf[13],filename[64],*table=NULL;
	Point_Net p;
	Header_dmon header_dmon;
//	Str_analog_monitor_point current_analog_mon;
	long k,last,l1,l2,interv,l,offset,offset1,timelastsample,timefirstsample;
	FILE *h;
//	memcpy(&current_analog_mon, &ptr_panel->analog_mon[ind-1], sizeof(Str_analog_monitor_point));
	if( rs485port!=-1 )
	{
	 network=(( class ConnectionData *)Routing_table[rs485port].ptr)->panel_info1.network;
	}
	else
	 network = NetworkAddress;

	memset( &header_dmon, 0, sizeof(	header_dmon ));
	p.putpoint(ind-1, AMON + 1, Station_NUM-1, network);
	pointtotext(buf,&p);
	strcpy(label,ispoint(rtrim(buf),&num_point,&var_type, &point_type, &num_panel, &num_net, network, Station_NUM));
	strcat(label,".DIG");
	ind--;

	offset=4;
	offset1=0;
	filename[0] = 0;
	strcpy(filename, ptr_panel->Monitor_Path);
	if(strlen(filename)) strcat(filename, "\\");
	strcat(filename, label);
	i=0;
	if( strchr(filename, ':') )
		i = filename[0] - 'A' + 1;
/*
	header_dmon.n_inputs = current_analog_mon.num_inputs - current_analog_mon.anum_inputs;
	memcpy(&header_dmon.inputs,&current_analog_mon.inputs[current_analog_mon.anum_inputs],header_dmon.n_inputs*sizeof(Point_Net));
	for(i=0;i<header_dmon.n_inputs; i++)
	{
		header_dmon.time_last_sample[i] = heap_dmon[current_analog_mon.end_index_dig[i]].time;
		header_dmon.onoff[i] = !heap_dmon[current_analog_mon.start_index_dig[i]].onoff;
	}
*/
	struct diskfree_t free;
	set_semaphore_dos();
int_disk = 1;
	j=_dos_getdiskfree(i, &free);
int_disk = 0;
	if (j!= 0)
	{
		l1 = 100000l;
	}
	else
		l1 = (long) free.avail_clusters * (long) free.bytes_per_sector
			 * (long) free.sectors_per_cluster;
//mxyputs(10,11, "After getdiskfree dig");
int_disk = 1;
	if((h=fopen(filename,"r+b"))!=NULL)
	{
	 fseek(h, 0L, SEEK_END);
	 l = ftell(h);
	 fseek(h, 0, SEEK_SET);
int_disk = 0;
	 if( l1+l < dmon_file_length +dmon_file_length  + 5000)
	 {
		h = NULL;
	 }
	 else
	 {
int_disk = 1;
		fread(&offset1, 4, 1, h);
int_disk = 0;
//	 fseek(h, offset, SEEK_SET);
//	 fread(&header_dmon, sizeof(Header_dmon), 1, h);
		clear_semaphore_dos();
		set_semaphore_dos();
//	 if( timefirstsample <= header_dmon.time_last_sample)
		{
		} //if
//		fseek(h, 0L, SEEK_END);
//		offset = ftell(h);
//		l=ftell(h);
		offset = l;

int_disk = 1;
		fseek(h, 0L, SEEK_SET);
int_disk = 0;
		l2 = (nsample_mem_dig+50)*4 + (long)sizeof(Header_dmon);
		if(dmon_file_length < l+l2)
/*

//			movefiledig(filename,(l+l2-dmon_file_length),&h);
//			clear_semaphore_dos();
//			set_semaphore_dos();
//			h = fopen(filename,"r+b");
//			fclose(h);
//			h = fopen(filename,"r+b");
//			fseek(h, 0L, SEEK_SET);
			fread(&offset1, 4, 1, h);
*/
		{
		 clear_semaphore_dos();

		 if(movefiledig(filename,(l+l2-dmon_file_length),&h))
//		 if(offset1)
		 {
int_disk = 1;
				fread(&offset1, 4, 1, h);
				fseek(h, 0L, SEEK_END);
				offset = ftell(h);
int_disk = 0;
		 }
		 else
		 {
				offset1 = 0;
				offset = 4;
		 }
		}
	 }
	}
	else
	{
	 if((h=fopen(filename,"w+b"))==NULL)
	 {
		;  //       luata o actiune: second file_server
	 }
	 offset=4;
int_disk = 0;
	}
	if(h)
	{
	 clear_semaphore_dos();
	 set_semaphore_dos();
	 init_heap_dmon = 1;
	 header_dmon.n_inputs = ptr_panel->analog_mon[ind].num_inputs - ptr_panel->analog_mon[ind].anum_inputs;
	 memcpy(&header_dmon.inputs,&ptr_panel->analog_mon[ind].inputs[ptr_panel->analog_mon[ind].anum_inputs],header_dmon.n_inputs*sizeof(Point_Net));
	 for(i=0;i<header_dmon.n_inputs; i++)
	 {
		header_dmon.time_last_sample[i] = heap_dmon[ptr_panel->monitor_work_data[ind].end_index_dig[i]].time;
		header_dmon.onoff[i] = heap_dmon[ptr_panel->monitor_work_data[ind].start_index_dig[i]].onoff;
	 }

int_disk = 1;
	 fseek(h, 0L, SEEK_SET);
	 fwrite(&offset,4,1,h);
	 fseek(h, 0L, SEEK_END);
	 fwrite(&header_dmon, sizeof(Header_dmon), 1, h);
int_disk = 0;
	 l = 0;
	 for(i=0;i<header_dmon.n_inputs;i++)
	 {
		l1 = 0;
		header_dmon.offset[i] = l;
		if(ptr_panel->monitor_work_data[ind].start_index_dig[i] != 0x0FFFF)
		{
		 for(j=ptr_panel->monitor_work_data[ind].start_index_dig[i]; j != ptr_panel->monitor_work_data[ind].end_index_dig[i]; j = heap_dmon[j].next)
		 {
int_disk = 1;
			fwrite(&heap_dmon[j].time, 4, 1, h);
int_disk = 0;
			l1++;
		 }
int_disk = 1;
		 fwrite(&heap_dmon[j].time, 4, 1, h);
int_disk = 0;
		 l1++;
    }
		header_dmon.n_sample[i] = l1;
		l += l1;
	 }
	 init_heap_dmon = 0;
	 header_dmon.prev_header = offset1;
int_disk = 1;
	 fseek(h, offset, SEEK_SET);
	 fwrite(&header_dmon, sizeof(Header_dmon), 1, h);
	 fclose(h);
int_disk = 0;
	}
	clear_semaphore_dos();
}

void filecopy(FILE *dest, FILE *h, long offset, long length)
//void filecopy(long dest, FILE *h, long offset, long length)
{
 clear_semaphore_dos();
 set_semaphore_dos();
int_disk = 1;
 fseek(h, offset, SEEK_SET);
int_disk = 0;
 char *p = new char[8096];
 int n = 8096;
 long l=0;
 clear_semaphore_dos();
int_disk = 1;
 while(l<length && !feof(h))
 {
int_disk = 0;
	if(l+n>=length) n=length-l;
//	fseek(h, offset, SEEK_SET);
	set_semaphore_dos();
//	fseek(h, offset, SEEK_SET);
	//   disk_accessed = 1;
int_disk = 1;
	fread(p,n,1,h);
	//   disk_accessed = 0;
	if(feof(h)) break;
//	offset = ftell(h);
//	fseek(h, dest, SEEK_SET);
//	fwrite(p,n,1,h);
//	dest = ftell(h);
	//   disk_accessed = 1;
	fwrite(p,n,1,dest);
	//   disk_accessed = 0;
int_disk = 0;
	clear_semaphore_dos();
	l += n;
//	offset += n;
 }
int_disk = 0;
 set_semaphore_dos();
 if(p) delete [] p;
}

void filecopyrest(FILE *dest, FILE *h, long offset)
//void filecopyrest(long dest, FILE *h, long offset)
{
 Header_dmon header_dmon;
 long prev;
 int nsample;
 long l = ftell(dest);
int_disk = 1;
 fseek(dest, 0, SEEK_SET);
 fread(&prev, 4, 1, dest);
 fseek(dest, l, SEEK_SET);
 while(!feof(h))
 {
	fseek(h, offset, SEEK_SET);
	//   disk_accessed = 1;
	fread(&header_dmon, sizeof(Header_dmon), 1, h);
	//   disk_accessed = 0;
	if(feof(h)) break;
	offset=ftell(h);
	header_dmon.prev_header = prev;
	prev = ftell(dest);
//	prev = dest;
	//   disk_accessed = 1;
	fwrite(&header_dmon,sizeof(Header_dmon),1,dest);
	//   disk_accessed = 0;
//	fseek(h, dest, SEEK_SET);
//	fwrite(&header_dmon,sizeof(Header_dmon),1,h);
//	dest=ftell(h);
int_disk = 0;
	nsample = 0;
	for(int i=0;i<header_dmon.n_inputs;i++)
	{
	 nsample += header_dmon.n_sample[i];
	}
	filecopy(dest, h, ftell(h), nsample*4L);
//	filecopy(dest, h, offset, nsample*4L);
	offset += nsample*4L;
//	dest += nsample*4L;
int_disk = 1;
 }
 fseek(dest, 0L, SEEK_SET);
// fseek(h, 0L, SEEK_SET);
 //   disk_accessed = 1;
 fwrite(&prev, 4, 1, dest);
int_disk = 0;
 //   disk_accessed = 0;
// fwrite(&prev, 4, 1, h);
}


int movefiledig(char *label,long nbytes,FILE **hh)
{

 int n,nsample;
 long offset,l,ls,ld,l1,l2,l3;
 char *p;
 Header_dmon header_dmon,header_dmon1;

 set_semaphore_dos();
 FILE *tempfp;
int_disk = 1;
 tempfp = fopen("tmp","w+b");
// dest = 4;
 fseek(*hh, 0L, SEEK_END);
 l=ftell(*hh);
int_disk = 0;
 if(nbytes >= l-4)
 {
	clear_semaphore_dos();
	offset=0;
 }
 else
 {
int_disk = 1;
	fseek(*hh, 0L, SEEK_SET);
	fread(&offset, 4, 1, *hh);
	fseek(*hh, 4L, SEEK_SET);
//	offset=ftell(*hh);
	fread(&header_dmon, sizeof(Header_dmon), 1, *hh);
int_disk = 0;
	clear_semaphore_dos();
	nbytes = nbytes%4L?nbytes/4L+1:nbytes/4L;
	do
	{
	nsample = 0;
	for(int i=0;i<header_dmon.n_inputs;i++)
	{
	 nsample += header_dmon.n_sample[i];
	}
	if(nbytes>=(long)(nsample))
	{
	 nbytes -= (long)nsample+sizeof(Header_dmon)/4L;
	 if(nbytes<0L)
		 nbytes=0L;
	 set_semaphore_dos();
int_disk = 1;
	 fseek(*hh, (long)nsample*4L, SEEK_CUR);
	 if(!feof(*hh) && nbytes)
	 {
			offset=ftell(*hh);
			fread(&header_dmon, sizeof(Header_dmon), 1, *hh);
	 }
int_disk = 0;
	 clear_semaphore_dos();
	}
	else
	{
	 set_semaphore_dos();
int_disk = 1;
	 l2 = ftell(*hh);    // dupa header
int_disk = 0;
	 header_dmon.prev_header = 0;
	 header_dmon1 = header_dmon;
	 if(nbytes)
		{
		 long ll=0;
		 clear_semaphore_dos();
		 l = nbytes;
//		 l1 = l%(long)(header_dmon.n_inputs)?l/(long)(header_dmon.n_inputs)+1L:l/(long)(header_dmon.n_inputs);
		 for(i=0;i<header_dmon.n_inputs;i++)
		 {
			l1 = (header_dmon.n_sample[i] * l)/nsample;
			l1 += (header_dmon.n_sample[i] * l)%nsample?1:0;
			header_dmon1.offset[i] = ll;
			if( (int)header_dmon1.n_sample[i] - l1 < 0 ) header_dmon1.n_sample[i]=0;
			else header_dmon1.n_sample[i] -= l1;
			ll += header_dmon1.n_sample[i];
			if(l1%2)
				 header_dmon1.onoff[i] = !header_dmon1.onoff[i];

/*
			if(header_dmon.n_sample[i]<l1)
			{
			 l = l-header_dmon.n_sample[i];
			 l1 = l%(long)(header_dmon.n_inputs-i-1)?l/(long)(header_dmon.n_inputs-i-1)+1L:l/(long)(header_dmon.n_inputs-i-1);
			 header_dmon1.n_sample[i] = 0;
			}
			else
			{
			 l = l-l1;
			 header_dmon1.offset[i] = ll;
			 header_dmon1.n_sample[i] -= l1;
			 ll += header_dmon1.n_sample[i];
			 if(l1%2)
				 header_dmon1.onoff[i] = !header_dmon1.onoff[i];
			}
*/
		 }
		 set_semaphore_dos();
int_disk = 1;
		 fseek(tempfp, 0L, SEEK_SET);
		 offset = 4;
		 fwrite(&offset,4,1,tempfp);
//		 fseek(*hh, dest, SEEK_SET);
		 fwrite(&header_dmon1, sizeof(Header_dmon), 1, tempfp);
//		 dest += sizeof(Header_dmon);
		 l3 = ftell(tempfp);
int_disk = 0;
		 for(i=0;i<header_dmon.n_inputs;i++)
		 {
			if(header_dmon1.n_sample[i])
			{
//			 header_dmon1.offset[i] = ftell(tempfp) - l3;
			 filecopy(tempfp, *hh, header_dmon.offset[i]*4L+l2+(header_dmon.n_sample[i]-header_dmon1.n_sample[i])*4L, header_dmon1.n_sample[i]*4L);
//			 header_dmon1.offset[i] = ftell(tempfp) - l3;
//			 filecopy(tempfp, *hh, header_dmon.offset[i]+l2+(header_dmon.n_sample-header_dmon1.n_sample)*4L, header_dmon1.n_sample[i]*4L);
			}
		 }
int_disk = 1;
		 fseek(tempfp, 4L, SEEK_SET);
//		 fwrite(&header_dmon1, sizeof(Header_dmon), 1, *hh);
		 fwrite(&header_dmon1, sizeof(Header_dmon), 1, tempfp);
		 fseek(tempfp, 0L, SEEK_END);
int_disk = 0;
//		 fseek(*hh, l2+nsample*4L, SEEK_SET);
		 filecopyrest(tempfp, *hh, l2+nsample*4L);
	 }
	 else
		{
		 offset = 0;
//		 fseek(*hh, 0L, SEEK_SET);
int_disk = 1;
		 fwrite(&offset,4,1,tempfp);
int_disk = 0;
//		 fwrite(&offset,4,1,*hh);
		 filecopyrest(tempfp, *hh, l2);
//		 filecopyrest(4, *hh, l2);
		 clear_semaphore_dos();
//		 ld = l - l2 + 4;
		}
		break;
	 }
	}while (1);
 }
 set_semaphore_dos();
int_disk = 1;
 fclose(*hh);
 fclose(tempfp);
// disable();
 remove(label);
int_disk = 0;
// enable();
 clear_semaphore_dos();
 set_semaphore_dos();
// disable();
int_disk = 1;
 rename("tmp", label);
// enable();

// fseek(*hh, 0L, SEEK_SET);
// fwrite(&offset,4,1,*hh);
// fclose(*hh);

// handle = open(label, O_RDWR|O_BINARY);
// chsize(handle, ld);
// *hh = fdopen(handle, "r+b");
 *hh = fopen(label,"r+b");
 fseek(*hh, 0L, SEEK_SET);
int_disk = 0;
 if(offset) return 1;
 else return 0;
}


int movefile(char *label,long nbytes,FILE **hh)
{
 int handle,n;
 long offset,l,ls,ld,l1;
 char *p;
 Header_amon header_amon;
 FILE *h;
// h = *hh;
 h = hmove;
int_disk = 1;
 fseek(h, 0L, SEEK_END);
 l=ftell(h);
int_disk = 0;
 if(nbytes > l-4)
 {
	ld = 0;
	offset=0;
 }
 else
 {
int_disk = 1;
 fseek(h, 0L, SEEK_SET);
 fread(&offset, 4, 1, h);
 fseek(h, 4L, SEEK_SET);
 fread(&header_amon, sizeof(Header_amon), 1, h);
int_disk = 0;
 clear_semaphore_dos();
 set_semaphore_dos();
 do
 {
	if(nbytes>=(long)(header_amon.n_sample-1)*(long)header_amon.n_inputs*4L)
	{
	 nbytes -= (long)header_amon.n_sample*(long)header_amon.n_inputs*4L+sizeof(Header_amon);
	 if(nbytes<0L) nbytes=0L;
int_disk = 1;
	 fseek(h, (long)header_amon.n_sample*4L*(long)header_amon.n_inputs, SEEK_CUR);
	 fread(&header_amon, sizeof(Header_amon), 1, h);
int_disk = 0;
	}
	else
	{
	 header_amon.prev_header = 0;
	 if(nbytes)
	 {
		 l1 = nbytes%(long)(header_amon.n_inputs*4L)?nbytes/(long)(header_amon.n_inputs*4)+1L:nbytes/(long)(header_amon.n_inputs*4);
		 header_amon.n_sample -= l1;
int_disk = 1;
		 ls = ftell(h);
int_disk = 0;
		 ls=ls+l1*(long)header_amon.n_inputs*4L-sizeof(Header_amon);
	 }
	 else
	 {
int_disk = 1;
		 ls=ftell(h);
int_disk = 0;
		 ls=ls-(long)sizeof(Header_amon);
	 }
int_disk = 1;
	 fseek(h, (long)ls, SEEK_SET);
	 fwrite(&header_amon, sizeof(Header_amon), 1, h);
//	 fseek(*hh, ls, SEEK_SET);
int_disk = 0;
	 clear_semaphore_dos();
	 for(ld = offset; ld > ls; )
	 {
		set_semaphore_dos();
int_disk = 1;
		fseek(h, ld, SEEK_SET);
		fread(&header_amon, sizeof(Header_amon), 1, h);
int_disk = 0;
		ld = header_amon.prev_header;
		header_amon.prev_header -= (ls-4);
		if (header_amon.prev_header < 0) header_amon.prev_header = 4;
int_disk = 1;
		fseek(h, ftell(h)-(long)sizeof(Header_amon), SEEK_SET);
		fwrite(&header_amon, sizeof(Header_amon), 1, h);
int_disk = 0;
		clear_semaphore_dos();
	 }
	 ld = 4;
	 if(offset!=4)
	 {
		 offset -= (ls-4);
		 if(offset<0) offset = 4;
	 }
	 set_semaphore_dos();
	 p = new char[8096];
	 n=8096;
	 while(ls<l && !feof(h))
	 {
		if(ls+n>=l) n=l-ls;
int_disk = 1;
		fseek(h, ls, SEEK_SET);
		fread(p,n,1,h);
		fseek(h, ld, SEEK_SET);
		fwrite(p,n,1,h);
int_disk = 0;
		ls += n;
		ld += n;
	 }
	 if(p) delete [] p;
	 break;
	}
 }while (1);
 }
int_disk = 1;
 fseek(h, 0L, SEEK_SET);
 fwrite(&offset,4,1,h);
 fclose(h);
 handle = open(label, O_RDWR|O_BINARY);
 chsize(handle, ld);
 *hh = fdopen(handle, "r+b");
 fseek(*hh, 0L, SEEK_SET);
int_disk = 0;
 if(offset) return offset;
 else return 0;
}

void save_m(void)
{
 int save;
 char ut;
 set_semaphore(&read_mon_flag);
//set_PIC_RS485();
ut = updatedtime;
updatedtime=0;
while(save_monitor)
{
 int i;
 save_monitor_status = 1;
 save = save_monitor;
 save_monitor = 0;
/* while(refresh_graph_mode)
		{
		 suspend(AMONITOR);
		}
*/
 if(save & 0x01)       //save analog
 {
	long coef = ( (num_monitors?num_monitors*1000L:1000L)/20000L)*1000L + (((num_monitors?num_monitors*1000L:1000L)%20000L)*1000L)/20000L ;
//	float coef = ((float)(num_monitors?num_monitors:1))/20.;
	long ltot = 0;
	if(!ut)
		creategauge(&gaugem,"Saving analog monitors...");
	for(i=0;i<MAX_ANALM;i++)
	{
//	if(ptr_panel->analog_mon[i].head_index>=ptr_panel->analog_mon[i].data_length-5)
	if(ptr_panel->monitor_work_data[i].head_index>=MAX_SAMPLE_MEM || save_monitor_command)
	{
	 if(ptr_panel->monitor_work_data[i].head_index>=MAX_SAMPLE_MEM)
		 ptr_panel->monitor_work_data[i].saved	= 1;
	 if(ptr_panel->monitor_work_data[i].head_index)
	 {
		 nr_mon_save=i;
		 savemonitor(i+1);
		 nr_mon_save=0;
		 if(!ut)
			 showgauge(gaugem, coef, ++ltot);
	 }
	 if(current_mon-1 == i)
		if(local_graph) justsavemem = 1;
	}
 }
	if(!ut)
		showgauge(gaugem, coef, num_monitors?num_monitors:1);
/*
	if(mode_text)
		mxyputs(50,3,"Before deletegauge",Black, White);
	else
	 {
		setfillstyle(SOLID_FILL, Black);
		bar(400,24,600,32);
		setcolor(White);
		outtextxy(400,24,"Before deletegauge");
	 }
*/
	if(!ut)
		deletegauge(&gaugem);
/*
	if(mode_text)
		mxyputs(50,3,"After deletegauge",Black, White);
	else
	 {
		setfillstyle(SOLID_FILL, Black);
		bar(400,24,600,32);
		setcolor(White);
		outtextxy(400,24,"After deletegauge");
	 }
*/
 }
 if(save & 0x02)       //save digital
 {
	for( i = 0;i<MAX_ANALM;i++)
//	 if(ptr_panel->analog_mon[i].num_inputs-ptr_panel->analog_mon[i].anum_inputs)
	 if(nsample_mem_dig_mon[i])
	 {
		 savemonitordig(i+1);
		 if(!(save & 0x01))
			 if(current_mon-1 == i)
				if(local_graph) justsavemem = 1;
	 }

	init_heap_dmon = 1;
	for( i = 0;i<MAX_ANALM;i++)
//	 if(ptr_panel->analog_mon[i].num_inputs-ptr_panel->analog_mon[i].anum_inputs)
	{
		 memset(ptr_panel->monitor_work_data[i].start_index_dig,0xFF,MAX_POINTS_IN_MONITOR*2);
		 memset(ptr_panel->monitor_work_data[i].end_index_dig,0,MAX_POINTS_IN_MONITOR*2);
/*		 for(int j=0;j<5;j++)
		 {
				ptr_panel->monitor_work_data[i].start_index_dig[j] = 0x0FFFF;
				ptr_panel->monitor_work_data[i].end_index_dig[j] = 0;
		 }
*/
	}

	first_free = 0;
	for(i=0; i < MAX_HEAP_DIGM-1; i++)
		 heap_dmon[i].next = i+1;
	nsample_mem_dig = 0;
	memset(nsample_mem_dig_mon, 0, 2*MAX_ANALM);
	init_heap_dmon = 0;
 }
}
//reset_PIC_RS485();
clear_semaphore(&read_mon_flag);
}

void savemonitors(void)
{
// int save;
while(1)
{
/*
 if(GAlarm)
	 if(alarm_time--)
	 {
		if(mode_text)
			mxyputs(76,1,"ALARM",Red+8, Lightred);
		else
		{
		 if(alarm_col==Lightred)
		 {
	// set_semaphore(&screen);
			chbkg((76-1)*8, 0, 40, Red, Red);
			chbkg((76-1)*8, 8, 40, Red, Red);
			alarm_col=Red;
	// clear_semaphore(&screen);
		 }
		 else
		 {
	// set_semaphore(&screen);
			chbkg((76-1)*8, 0, 40, Lightred, Lightred);
			chbkg((76-1)*8, 8, 40, Lightred, Lightred);
			alarm_col=Lightred;
	// clear_semaphore(&screen);
		 }

//		 setcolor(Lightred);
//		 outtextxy((76-1)*8,0,"ALARM");
		}
		alarm_time = 6;
	 }
*/

if(!save_monitor_status)
{
 save_m();
 save_monitor_command=0;
// if (save_monitor) continue;
 save_monitor_status = 0;
}
suspend(AMONITOR);
}
}

void initanalogmon(void)
{
//	 char huge *p=heap_amon;
	 long l,l1;
	 char *p=heap_amon;
	 num_monitors=0;
	 l = 0;
	 for(int i=0;i<MAX_ANALM;i++)
	 {
		if(ptr_panel->analog_mon[i].num_inputs!=0) num_monitors++;
		if(ptr_panel->analog_mon[i].anum_inputs==0)
		{
			ptr_panel->monitor_work_data[i].data_segment = 0;
		}
		else
		{
		  ptr_panel->monitor_work_data[i].data_segment=p;
		  long interv,sample;
//		sample=psample(&interv,i);
		  sample = MAX_SAMPLE_MEM+5;
		  l1 = sample * ptr_panel->analog_mon[i].anum_inputs*
				 (ptr_panel->analog_mon[i].double_flag*2+2);
		  if( l+l1 < MAX_HEAP_AMON )
		  {
			p += l1;
			l += l1;
		  }
		  else
		  {
			ptr_panel->monitor_work_data[i].data_segment = 0;
			ptr_panel->analog_mon[i].status = 0;
		  }

//																	time((long *)&ptr_panel->analog_mon[i].last_sample_time);

//***********
// long t = timesec1970 + timestart;
// long l = ptr_panel->analog_mon[0].last_sample_saved_time;
// if( l > t )
// {
//	char buf[81];
//	l -= t;
//	printrange(0, 0, 0, l, buf);
//	ptr_panel->alarms[ptr_panel->ind_alarms].alarm_panel = Station_NUM;
//	ptr_panel->alarms[ptr_panel->ind_alarms].alarm_time = t;
//	ptr_panel->alarms[ptr_panel->ind_alarms].alarm_count = 69;
//	strcpy(&ptr_panel->alarms[ptr_panel->ind_alarms].alarm_message[0],"Lost ");
//	strcat(&ptr_panel->alarms[ptr_panel->ind_alarms].alarm_message[5],buf);
//	strcat(&ptr_panel->alarms[ptr_panel->ind_alarms].alarm_message[strlen(ptr_panel->alarms[ptr_panel->ind_alarms].alarm_message)]," of data at ");
//	long interv;
//	psample(&interv, &ptr_panel->analog_mon[i]);
//	t += (MAX_SAMPLE_MEM) * interv;
//	strcpy(buf,ctime(&t));
//	buf[20]=0;
//	strcat(&ptr_panel->alarms[ptr_panel->ind_alarms].alarm_message[strlen(ptr_panel->alarms[ptr_panel->ind_alarms].alarm_message)],buf);
//	strcat(&ptr_panel->alarms[ptr_panel->ind_alarms].alarm_message[strlen(ptr_panel->alarms[ptr_panel->ind_alarms].alarm_message)]," in ");
//	strcat(&ptr_panel->alarms[ptr_panel->ind_alarms].alarm_message[strlen(ptr_panel->alarms[ptr_panel->ind_alarms].alarm_message)],itoa(Station_NUM,buf,10));
//	strcat(&ptr_panel->alarms[ptr_panel->ind_alarms].alarm_message[strlen(ptr_panel->alarms[ptr_panel->ind_alarms].alarm_message)],"-AMON");
//	strcat(&ptr_panel->alarms[ptr_panel->ind_alarms].alarm_message[strlen(ptr_panel->alarms[ptr_panel->ind_alarms].alarm_message)],itoa(i+1,buf,10));
//	ptr_panel->ind_alarms++;
//	Display_alarm(ptr_panel->ind_alarms-1);
//	GAlarm = 1;
// }
//***************
		}
		ptr_panel->monitor_work_data[i].next_sample_time = 0;
		ptr_panel->monitor_work_data[i].start = 0;
		ptr_panel->monitor_work_data[i].saved = 0;
		ptr_panel->monitor_work_data[i].head_index = 0;
	 }
if(num_monitors)
{
 present_analog_monitor=1;
}
}


// save = 0 save; save = 2 no_save, nothing = 1(fond color);  save = 1 no_save, nothing = 0(stay on screen);
int dialog_select(int n_entry, char *arraytext, int save, int x, int y, int bkgnd, int tbkgnd, char *title, char col)
{
				 int i;
				 view_name[0]=0;
				 max_entry = n_entry;
				 set_semaphore_dos();
				 array = new char [max_entry][41];
				 clear_semaphore_dos();
				 for( i=0; i<max_entry; i++)
				 {
					strcpy(&array[i][0],arraytext);
//					arraytext=strchr(arraytext,0)+1;
					arraytext += col+1;
				 }
//         memcpy(array,arraytext,max_entry*11);
//         graphsave=1;
//				 set_semaphore_dos();
				 GGrid *wgrid=new GGrid(x,y,x+(mode_text?col+1:(col+1)*8+20),y+(mode_text?max_entry+2:45+(max_entry)*20),GRID,NULL,ARRAY1,0,0,0,0,col);
//				 clear_semaphore_dos();
				 if(save)
					{
					 wgrid->save = 0;
					 if(save==1)
						 nothing = 0;
					}
				 wgrid->GWSet(title,bkgnd,tbkgnd);
				 wgrid->GShowGrid();
				 while (!wgrid->HandleEvent());
				 nothing = 1;
				 delete wgrid;
				 i = -1;
				 if(strlen(rtrim(view_name)))
				 {
					for(i=0;i<max_entry;i++)
					 if(!strcmp(ltrim(rtrim(view_name)),ltrim(rtrim(array[i])))) break;
				 }
				 set_semaphore_dos();
				 delete [] array;
				 clear_semaphore_dos();
				 return i;
}


