#include <windows.h>
#include "virtual.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <dos.h>
#include <process.h>
#include <dir.h>
#include <sys\stat.h>
#include <alloc.h>
#include <string.h>
#include <time.h>
#include <graphics.h>
#include <xms.h>

#define OFF 0
#define On 1

#define LONGTIMETEST -123456789L

#define TIME_VIRTUAL 5
//enum {PROJ=0, VIRTUAL=1 };
enum {PROGR=0, OPERATOR=1 };

#include "mtkernel.h"
#include "graph.h"
#include "parser.h"
#include "rs485.h"
#include "ptp.h"
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

extern void mputs(char *);


extern int dtr;
extern int ipxport, rs485port;
extern Panel_info1 Panel_Info1;
extern int mode_text;
extern char control;
extern unsigned  print_sem; // i/o semaphore

extern int inkey(char* adr, int num, int max, int port);
extern int pointtotext(char *buf,Point_Net *point);
extern int pointtotext(char *buf,Point_T3000 *point);
extern char *rtrim(char *text);

extern Panel *ptr_panel;
extern int isdelimit(char c);
extern int GetRange_Out(int range);
extern int GetRange_In(int range);
extern int GetRange_Var(int range);
extern void chbkg(int lx, int ly, int width, int bkgnd, int frgnd);
extern void reinstallrs485(void);
extern void updatetimevars(void);


extern Comm_Info *comm_info;
extern REMOTE_POINTS _far	remote_points_list[MAXREMOTEPOINTS82];

extern int  station_num;
extern char Station_NAME[NAME_SIZE];
extern int  Station_NUM;
extern int extended_memory;
extern XmsDes *Des;
extern int local_panel;
extern char present_analog_monitor;
extern char GAlarm;
extern unsigned char blocked, blocked1;

extern POOL print_message_pool;
extern char print_flag, action,save_alarm_flag;
//extern char huge heap_amon[];
extern unsigned first_free;
extern int nsample_mem_dig;
extern int nsample_mem_dig_mon[MAX_ANALM];
extern int MAX_HEAP_DIGM;
extern Heap_dmon huge *heap_dmon;  // 5000

extern char dial_buffer[40];
extern unsigned  t3000_flag; // i/o semaphore
extern Point_Net localopenscreen;
extern char DIAL_action, DIAL_dial;
#ifndef WORKSTATION

void longtoa(long f, int length, int ndec, char *buf);

void check_annual_routine(void);
void check_weekly_routine(void);
int checkalarmset(void);
int savemonitordata(void);
int exec_program(int current_prg, unsigned char *prog_code, long *stack, int port=COM0);
int interpret();
long operand(char **prg, char **buf, char *local, char *perr=NULL);
long veval_exp(char **prg, char *local, int port=COM0, char *perr=NULL);
static long pop(int port);
static void push(long value, int port);
unsigned long poplong(int port);
void pushlong(unsigned long value,int port);
void put_local_var(char *p, long value, char *local);
int put_local_array(char *p, long value, long v1, long v2, char *local);
int put_point(Point point, long value, int prog_op, int v=0, char *perr=NULL );
int get_point(Point point, long *value, char **p);
int get_point(Point_Net point, long *value, char **p, int mon=0);
long getvalelem(char **prg, long l, long c, char *local,char *perr=NULL);
int phone(char *message);
int	print(char *message);
int outputd(char* adr, int num, int port);
void alarm(void);
int	hangup(void);    	// end phone call
int	call(void);
int declare(void);
void dalarmrestore(char *mes, int prg, int panel);
int generatealarm(char *mes, int prg, int panel, int type, char alarmatall,char indalarmpanel,char *alarmpanel,char printalarm);
//int dalarm(char *mes, int prg, int panel);
int get_ay_elem(char **prg, long *value, char *local, char *perr=NULL);

extern load_program( char *p, char *fname);

//extern char LOCAL_POINT;
//extern char CONST_VALUE;
char *end;
int cur_line;

char *prog_name[16];
int num_prog;
long monsecunit[3]={60, 3600, 3600*24L};

long _far stack_com[22];
long _far stack_virt[22];
static long *index_stack;
static long *index_stack_virt;
char far vmessage[ALARM_MESSAGE_SIZE+26+10];

char called_program=0, end_program=0;

//static unsigned char *prog_virt;
//static unsigned char *prog_com;

unsigned alarm_flag,error_flag;

int portA_printer, portB_printer;
int cond;
unsigned int alarm_id;

char alarm_at_all;
char print_at_all;
char alarm_panel[5];
char print_panel[5];
char ind_alarm_panel;
char ind_print_panel;
char check_annual_routine_flag;
char check_weekly_routine_flag;
char printAlarms=1;
/*
struct alarm {
			unsigned modem     		 :1 ;
			unsigned printer  	 	 :1 ;
			unsigned screen   		 :1 ;
			unsigned restored      :1 ;
			unsigned acknowledged  :1 ;
			unsigned long alarm_time ;
			char alarm_count;
			char alarm_message[70];
			};
*/

extern char month_days[12];
extern char save_monitor;
//extern int alarm_time;
extern unsigned long timesec1970;
extern unsigned long timestart,ora_current_sec;
//extern struct  time ora_current;
extern Time_block ora_current;
extern int milisec;
extern char dayofweek;
extern char onesec,onemin,tenmin,tensec, twomin;
extern char save_monitor_command;
extern char	init_heap_dmon;
extern char new_alarm_flag;

static struct  time tt;
static int i,j,*pi;
//static unsigned point;
//static float *t,value;
static long *t;
static long l,v,value;

long op1,op2;
static long n, *pn;

char just_load=1;
char timeout, timeout_asyn;
int miliseclast, miliseclast_cur;

char huge *cardtext = "THE CONTROL CARD IS OUT OF ORDER";
char *line_mes = "         =         ; Low =          ; High =           ";

int g_ind_remote_local_list;
struct remote_local_list *g_remote_local_list;

char *time_buf;

static int point_type,num_point, num_panel, var_type;
char u[2]={0,0};

extern dig_range_form huge dig_range_array[];

int putmessage(int prg=0, int type=0, int ind=0, long value=0, long setvalue=0);    // ind alarm_set
int putmessage(char *mes, int prg, int type, char alarmatall,char indalarmpanel,char *alarmpanel);
//#define CONTROL 1
char reset1;
char run_board_flag;
int virtual_time=1500;
long timesave=120000;
//char readclock_flag;
long timereadclock;
int onesec_virtual;
//uint far xxxx[100],ind_xxxx;
char read_inputs_rate_tmp, write_outputs_rate_tmp;
extern char read_inputs_rate, write_outputs_rate;

void resetc(void)
{
	disable();
	if(mode_text)
		mxyputs(60,2,"RESET CARD");
	ptr_panel->Aio_Control( RESET_CARD, NULL, 0 );
	enable();
	delay(400);
	disable();
	ptr_panel->Config_dacqd_card();
	enable();
}

int fnc_exec_virtual_code(void)
{
 char time_sample;
 for(;;)
 {
	register int i;
	int k;

	time_sample=0;
/*
	if(onesec)
	{
		if(tensec++ == 10) tensec = 0;
		timestart++;
		ora_current_sec++;
		if(++ora_current.ti_sec == 60)
		{
		 onemin++;
		 if(tenmin++ == 10) tenmin = 0;
		 ora_current.ti_sec = 0;
		 if(++ora_current.ti_min == 60)
		 {
			ora_current.ti_min = 0;
			if(++ora_current.ti_hour == 24)
			{
			 ora_current.ti_hour=0;
			 ora_current_sec = 0;
			 if(++ora_current.dayofweek==7)
				 ora_current.dayofweek=0;
			 if( ++ora_current.dayofmonth==month_days[ora_current.month]+1 )
			 {
				 ora_current.dayofmonth=1;
				 if( ++ora_current.month == 12 )
						ora_current.month = 0;
			 }
			 if(++ora_current.dayofyear==366)
			 {
					ora_current.dayofyear=0;
					++ora_current.year;
					month_days[1]=28;
			 }
			 else
				if(ora_current.dayofyear==365)
				{
				 if( ora_current.year&0x03 )
				 {
					ora_current.dayofyear=0;
					++ora_current.year;
					month_days[1]=28;
				 }
				 else
					month_days[1]=29;
				}
			 check_annual_routine_flag=1;
//			 readclock_flag=1;
			}
		 }
	 }
	 if(present_analog_monitor)
	 {
		for(i=0;i<MAX_ANALM;i++)
		 if(ptr_panel->analog_mon[i].num_inputs)
		 {
			if(ptr_panel->monitor_work_data[i].next_sample_time)
				ptr_panel->monitor_work_data[i].next_sample_time--;
		 }
		time_sample=1;
	 }
	 onesec = 0;
	}
*/
//	set_semaphore(&t3000_flag);
/*
	miliseclast_cur = miliseclast;
	miliseclast = 0;
*/
/*	virtual_time = 1500;*/

//
// read inputs
//

	if(control && blocked1<8)
	{
	 if( !read_inputs_rate_tmp )
	 {
		blocked = 0;
		run_board_flag = 1;
		ptr_panel->Aio_Control( GET_ALL, (unsigned char *)ptr_panel->in_data, 0 );
		run_board_flag = 0;
		if(blocked) blocked1++;
		else {blocked1=0;reset1=0;}
		ptr_panel->convert_in();
		read_inputs_rate_tmp = read_inputs_rate;
	 }
	 else
			read_inputs_rate_tmp--;
	}

	if (onemin)
	{
		check_weekly_routine_flag = 1;
		if(control && blocked1<8)
		{
		 for( i=0; i<ptr_panel->table_bank[IN]; i++ )
		 {
			 if( ptr_panel->inputs[i].range==P0_255p_min )
			 {
				 ptr_panel->inputs[i].value = 1000L * ptr_panel->in_aux[i].ticks;
				 ptr_panel->in_aux[i].ticks= 0;
			 }
		 }
		}
	}
	if( check_annual_routine_flag )
		check_annual_routine();
	if( check_weekly_routine_flag )
		check_weekly_routine();

//
// run programs
//
// set_semaphore(&t3000_flag);
 miliseclast_cur = miliseclast;
 miliseclast = 0;
 for(i=0;i<MAX_PRGS;i++)
 {
//	if( ptr_panel->program_codes[i])       //  pointer to code
	if( ptr_panel->programs[i].bytes)
	{
	 set_semaphore(&t3000_flag);
	 if( ptr_panel->programs[i].bytes)
	 {
		if( !ptr_panel->programs[i].com_prg )    //  run as a normal program
		{
		 if( ptr_panel->programs[i].on_off)   //  pointer to code
		 {
			exec_program(i,ptr_panel->program_codes[i],stack_virt);
		 }
		}
	 }
	 clear_semaphore(&t3000_flag);
	}
 }
// clear_semaphore(&t3000_flag);
/*
		else                                     //  run as a com program
		{
			exec_program(i,ptr_panel->program_codes[i],1);
		}
*/
 if(just_load) just_load = 0;

//
// write outputs
//
 if(control && blocked1<8)
 {
	if( !write_outputs_rate_tmp )
	{
	 ptr_panel->convert_out();
	 blocked=0;
	 run_board_flag = 1;
	 ptr_panel->Aio_Control( SET_ALL, (unsigned char *)ptr_panel->out_data, 0 );
	 run_board_flag = 0;
	 if(blocked) blocked1++;
	 else {blocked1=0;reset1=0;}
	 if (!tenmin)
	 {
		blocked=0;
		run_board_flag = 1;
		ptr_panel->Aio_Control( SET_RATE, NULL, 0 );
		run_board_flag = 0;
		if(blocked) blocked1++;
		else blocked1=0;
		tenmin++;
	 }
	 write_outputs_rate_tmp = write_outputs_rate;
	}
	else
		write_outputs_rate_tmp--;
 }
 if(control && blocked1>=8)
 {
	resetc();
	if(!control)
	{
	if(mode_text)
		mxyputs(20, 23, cardtext, Black, Lightgreen);
	else
		outtextxy(150, 460, cardtext);
	reset1 = 1;
	}
	else
	reset1 = 0;
	blocked1=0;
 }


//
// save monitor data
//

// if( time_sample )
 if( tasks[VIRTUAL].delay_time <=0 )
 {
/*
	 if(ind_xxxx<99)
		 xxxx[ind_xxxx++]=ora_current_sec;
*/
	 set_semaphore(&t3000_flag);
	 savemonitordata();
	 clear_semaphore(&t3000_flag);
 }

 checkalarmset();

 if( !tensec )
 {
  Str_controller_point *pc;
	pc = ptr_panel->controllers;
  for(i=0;i<MAX_CONS;pc++,i++)
  {
	if(!pc->input.zero())
	 if(pc->auto_manual==AUTO)
		 ptr_panel->Controller(i);
	}
	tensec++;
 }
/*** read the system clock ***/
 if( ora_current.ti_hour==23 )
 {
		 if( ora_current.ti_min==0 )
			timereadclock = 1800000l;  /* 30 minutes */
		 if( timereadclock > 0 )
			timereadclock -= miliseclast_cur;
		 else
		 {
	     updatetimevars();
			 timereadclock = 3600000l;  /* 1hour */
		 }
 }
/********************************/
/*
 if(readclock_flag)
 {
	readclock_flag=0;
	updatetimevars();
 }
*/
// clear_semaphore(&t3000_flag);
// if(onesec_virtual<=0) 	onesec_virtual = 990000;
 msleep(TIME_VIRTUAL);
 }
}

void check_annual_routine( void )
{
	int i;
	byte mask;
	byte octet_index;
	Str_annual_routine_point *pr;

	pr = ptr_panel->annual_routines;
	for( i=0; i<MAX_AR; i++, pr++ )
	{
	 if( pr->auto_manual == AUTO )
	 {
		mask = 0x01;
/* Assume bit0 from octet0 = Jan 1st */
/* octet_index = ora_current.day_of_year / 8;*/
		octet_index = ora_current.dayofyear >> 3;
		/* bit_index = ora_current.day_of_year % 8;*/
/*		bit_index = ora_current.day_of_year & 0x07;*/
		mask = mask << ( ora_current.dayofyear & 0x07 );
		if( ptr_panel->ar_dates[i][octet_index] & mask )
			pr->value = 1;
		else
			pr->value = 0;
   }
	}
	 check_annual_routine_flag=0;
}

void check_weekly_routine(void)
{
 register int i,j,k,n;
 signed char w;
 Wr_one_day *p;
 Str_weekly_routine_point *pw;
 pw = ptr_panel->weekly_routines;
 w = ora_current.dayofweek-1;
 if (w<0) w = 6;
 for(i=0;i<MAX_WR;pw++,i++)
 {
	if(!pw->auto_manual)
	{
	 if(!pw->override_2.zero())
	 {
		get_point(*((Point *)&pw->override_2), &value, NULL);
		pw->override_2_value = value?1:0;
		if(value)
		{
		 w = 8;
//		 pw->value = On;
//		 continue;
		}
	 }
	 else
		 pw->override_2_value = OFF;

	 if(!pw->override_1.zero())
	 {
		get_point(*((Point *)&pw->override_1), &value, NULL);
		pw->override_1_value = value?1:0;
		if(value)
		{
		 w = 7;
//		 pw->value = On;
//		 continue;
		}
	 }
	 else
		 pw->override_1_value = OFF;

	 p = &ptr_panel->wr_times[i][w];
	 for(j=7; j>=0; j--)
	 {
		if( p->time2[(j<<1)+1] || p->time2[j<<1] )
			break;
	 }
	 n = -1;
	 if(j>=0)
	 {
		 for(k=0; k<=j; k++)
		 {
			 if( !k )
			 {
				 if( (ora_current.ti_hour < p->time2[(k<<1)+1]) ||
						 (ora_current.ti_hour == p->time2[(k<<1)+1] && ora_current.ti_min < p->time2[k<<1]) )
				 {
          n = j;
					break;
				 }
			 }
			 if( ora_current.ti_hour > p->time2[(k<<1)+1] || (ora_current.ti_hour == p->time2[(k<<1)+1] && ora_current.ti_min >= p->time2[k<<1]) )
			 {
				 if(n>=0)
				 {
					if( p->time2[(k<<1)+1] > p->time2[(n<<1)+1] || (p->time2[(k<<1)+1] == p->time2[(n<<1)+1] && p->time2[k<<1] >= p->time2[n<<1]) )
           n = k;
				 }
				 else
					 n = k;
			 }
		 }
	 }
	 if(n<0)
	 {
		pw->value = OFF;
		continue;
	 }
	 if(n%2)
		pw->value = OFF;
	 else
		pw->value = On;
	}
 }

/*
 Str_controller_point *pc;
 pc = ptr_panel->controllers;
 for(i=0;i<MAX_CONS;pc++,i++)
 {
	if(pc->input)
	 ptr_panel->Controller(i);
 }
*/
	onemin = 0;
	if(reset1)
	{
	 control = 1;
	 resetc();
	 if(!control)
	 {
	  if(mode_text)
		mxyputs(20, 23, cardtext, Black, Lightgreen);
	  else
		outtextxy(150, 460, cardtext);
	 }
	 else
	 {
	  blocked1=0;
	  reset1 = 0;
	 }
	}
  check_weekly_routine_flag = 0;
}

int savemonitordata(void)
{
 Point_Net point;
 if(present_analog_monitor)
 {
  Str_monitor_point *pmon;
  Str_monitor_work_data *pmon_workdata;
	register int i;
  pmon = ptr_panel->analog_mon;
  pmon_workdata = ptr_panel->monitor_work_data;
	for(i=0;i<MAX_ANALM;pmon++,pmon_workdata++,i++)
	{
	if(pmon->status)
	 if(pmon->num_inputs)
	 {
//		if(onesec_virtual)
		{
//		 onesec_virtual=0;
		 if(pmon->anum_inputs)
		 {
			t = (long *)pmon_workdata->data_segment;
			if(pmon_workdata->start)
			{
			 if(!pmon_workdata->next_sample_time)
			 {
				for(j=0; j<pmon->anum_inputs;j++)
				{
				 value=0;
				 if(pmon->inputs[j].point_type)
				 {
					if(pmon_workdata->head_index>=MAX_SAMPLE_MEM+5) pmon_workdata->head_index=0;
					point=pmon->inputs[j];
//			 if( point.panel+1==Station_NUM && point.network==NetworkAddress )
//				 get_point(*((Point *)&point), &value, NULL);
//			 else
					get_point(point, &value, NULL, 1);

					l=pmon_workdata->head_index*pmon->anum_inputs+j;
					t[l] = value;
				 }
				} //end for
				l = ((unsigned long)pmon->hour_interval_time*3600L+
					(unsigned long)pmon->minute_interval_time*60L+
					(unsigned long)pmon->second_interval_time);
//		  pmon_workdata->last_sample_time += l;
				pmon_workdata->last_sample_time = timesec1970 + timestart;
				pmon_workdata->next_sample_time = l;
				pmon_workdata->head_index++;

//			 time(&l);

//		if(ptr_panel->analog_mon[i].head_index>=255-5)
				if(pmon_workdata->head_index>=MAX_SAMPLE_MEM)
				 save_monitor |= 0x01;
				if(pmon_workdata->head_index>=(long)pmon->max_time_length*monsecunit[pmon->unit] / l )
				{
				 save_monitor |= 0x01;
				 save_monitor_command=1;
				}
			 } //if(!pmon->next_sample_time)
			}
			else //if(pmon->start)
			{
			 pmon_workdata->last_sample_time = timesec1970 + timestart;
			 l = (unsigned long)pmon->hour_interval_time*3600L+
				 (unsigned long)pmon->minute_interval_time*60L+
				 (unsigned long)pmon->second_interval_time;
			 pmon_workdata->last_sample_time -= l;
//		 if( !((tt.ti_hour*3600+tt.ti_min*60+tt.ti_sec) % l) )

			 if( !( ora_current_sec % l) )
			 {
				pmon_workdata->start=1;
			 }
			}
		 } // if anum_inputs
		}
// save digital value
		if(!init_heap_dmon)
		if(pmon->num_inputs - pmon->anum_inputs)
		{
//		int ndig = ptr_panel->analog_mon[i].num_inputs - ptr_panel->analog_mon[i].anum_inputs;
		for(j=pmon->anum_inputs; j < pmon->num_inputs ; j++)
		{
//			get_point(*((Point *)&pmon->inputs[j]), &value, NULL);
			get_point(pmon->inputs[j], &value, NULL,1);
			if( (pmon_workdata->start_index_dig[j-pmon->anum_inputs] == 0x0FFFF) || (heap_dmon[pmon_workdata->end_index_dig[j-pmon->anum_inputs]].onoff ^ (value?1:0) ) )
			{
			 unsigned n;
/*
			 n=1;
			 if( pmon_workdata->start_index_dig[j-pmon->anum_inputs] != 0x0FFFF)
				 if( heap_dmon[pmon_workdata->end_index_dig[j-pmon->anum_inputs]].time>=timesec1970 + timestart )
					n=0;
       if(n)
*/
			 {
				heap_dmon[first_free].time = timesec1970 + timestart;
				heap_dmon[first_free].onoff = value?1:0;
				n = pmon_workdata->end_index_dig[j-pmon->anum_inputs];
				pmon_workdata->end_index_dig[j-pmon->anum_inputs] = first_free;
				first_free = heap_dmon[first_free].next;
				if(pmon_workdata->start_index_dig[j-pmon->anum_inputs] == 0x0FFFF)
					pmon_workdata->start_index_dig[j-pmon->anum_inputs] = pmon_workdata->end_index_dig[j-pmon->anum_inputs];
				else
				{
//					heap_dmon[pmon_workdata->end_index_dig[j-pmon->anum_inputs]].next = 0;
					heap_dmon[n].next = pmon_workdata->end_index_dig[j-pmon->anum_inputs];
				}

				if(++nsample_mem_dig>=MAX_HEAP_DIGM-100)
				{
				 save_monitor |= 0x02;
				}
				nsample_mem_dig_mon[i]++;
			 }
			}

		}
	  } //end if digital

	 } // if num_inputs
  } // for
  if (save_monitor)
		resume(AMONITOR);
 }
}

int checkalarmset()
{
//!! float value,value1,value2;
// float value1,value2;
 long value1,value2;
 char *p,*p1,*p2;
 Alarm_set_point *ptr;
 ptr = ptr_panel->alarms_set;
 for(i=0;i<MAX_ALARMS_SET;ptr++,i++)
 {
	if(!ptr->point.zero())
	{
	get_point(*((Point *)&ptr->point), &value, &p);
	if(!p)
	{
	 get_point(*((Point *)&ptr->point1), &value1, &p1);
	 if(value1==ptr->cond1)
	 {
		if(ptr->nrmes>0)
			if(ptr_panel->alarms[ptr->nrmes-1].ddelete)
				{
				 memset(&ptr_panel->alarms[ptr->nrmes-1],0,sizeof(Alarm_point));
//				 ptr_panel->alarms[ptr->nrmes-1].ddelete = 0;
//				 ptr_panel->alarms[ptr->nrmes-1].alarm = 0;
				 ptr->nrmes=0;
				}

		get_point(*((Point *)&ptr->normal), &value2, &p2);
		if(value < value2+ptr->waylow || value > value2+ptr->wayhi )
		{
		 if(ptr->nrmes<=0)
		 {                                              // nu exista mes
			ptr->nrmes=putmessage(0, 1, i, value, value2);
		 }
//		 else    // exista mes
//		 {
//			if(!ptr_panel->alarms_set[nrmes-1].acknowledged)
//				GAlarm = 1;
//		 }
		}
		else   //verylow
		{
		 if(value < value2+ptr->low || value > value2+ptr->hi )
		 {
			if(ptr->nrmes==-1)
			{                                              // se asteapta count=0
			 if(ptr->count--==0)
			 {
				ptr->nrmes=putmessage(0, 1, i, value, value2);
			 }
			}
			else
			{
			 if(ptr->nrmes==0)
			 {
				ptr->count = ptr->time/TIME_VIRTUAL;
				ptr->nrmes=-1;
			 }
			 else
			 {
				if(ptr_panel->alarms[ptr->nrmes-1].restored)
				{
				 ptr_panel->alarms[ptr->nrmes-1].restored = 0;
				 if(!ptr_panel->alarms[ptr->nrmes-1].acknowledged)
					 {
						ptr_panel->ind_alarms++;
						GAlarm = 1;
					 }
//				 ptr_panel->alarms[ptr->nrmes].acknowledged = 0;
//         GAlarm = 1;
				}
			 }
			}
		 }
		 else //<low
		 {
			if(ptr->nrmes>0)
			{
				if(!ptr_panel->alarms[ptr->nrmes-1].restored)
				{
				 ptr_panel->alarms[ptr->nrmes-1].restored = 1;
				 if(!ptr_panel->alarms[ptr->nrmes-1].acknowledged)
					 if(!(--ptr_panel->ind_alarms)) GAlarm = 0;
				 ptr->nrmes=0;
				}
			}
			else
			{
			 ptr->nrmes=0;
			}
		 }
		} //<verylow
	 } //cond1
	}
	} // if ptr->point
 } //for
}

//******************************************
// return: -1 no space; >=0 alarm index
//******************************************
int checkalarmentry(void)
{
 long value1;
 int i,j,k;

 Alarm_point *ptr;
 ptr = ptr_panel->alarms;
 for(j=0;j<MAX_ALARMS;ptr++,j++)
		if(!ptr->alarm && !ptr->ddelete ) break;     // ddelete=1; the user delete the alarm
                                                 // but it was not sent yet to the destination panels
 if(j>=MAX_ALARMS)
 {
	ptr = ptr_panel->alarms;
	i=0;
	for(j=0;j<MAX_ALARMS;ptr++,j++)
	{
		if( ptr->restored && !ptr->change_flag )
		{
		 i=j;
		 break;
		}
	}
	if(j>=MAX_ALARMS)
	{
	 ptr = ptr_panel->alarms;
	 i=0;
	 for(j=0;j<MAX_ALARMS;ptr++,j++)
	 {
		if( ptr->acknowledged  && !ptr->change_flag )
		{
		 i=j;
		 break;
		}
	 }
	 if(j>=MAX_ALARMS)
	 {
		ptr = ptr_panel->alarms;
		i=0;
		for(j=0;j<MAX_ALARMS;ptr++,j++)
		{
		 if( ptr->ddelete && !ptr->change_flag )
		 {
			i=j;
			break;
		 }
		}
		if(j>=MAX_ALARMS)
		{
		 ptr = ptr_panel->alarms;
		 value1 = ptr->alarm_time;
		 i=0;
		 for(j=0;j<MAX_ALARMS;ptr++,j++)
			if(value1>ptr->alarm_time&& ptr->change_flag!=2 )
			{
			 value1 = ptr->alarm_time;
			 i=j;
			}
		 if(j>=MAX_ALARMS)
			j=-1;
		 else
		 {
			j = i;
			ptr_panel->alarms[j].alarm = 0;
			--ptr_panel->ind_alarms;
		 }
    }
   }
	}
 }
 return j;
}

int putmessage(int prg, int type, int ind, long value, long setvalue)    // ind alarm_set
{
}

//int putmessage(int ind, float value, float setvalue)    // ind alarm_set
//**************************************************
// return:  0 - no space; >=1 - alarm index
//**************************************************
int putmessage(char *mes, int prg, int type, char alarmatall,char indalarmpanel,char *alarmpanel)
{
// char buf[30],*p;
 int i,j,k;
 char *p;
 Alarm_point *ptr;
 j = checkalarmentry();
 if(j>=0)
 {
	ptr = &ptr_panel->alarms[j];
	memset(ptr,0,sizeof(Alarm_point));
	ptr->change_flag  = 2;
	ptr->alarm        = 1;
	ptr->no           = j;
	ptr->alarm_panel  = Station_NUM;
	ptr->alarm_time   = timesec1970+timestart;
	ptr->alarm_count  = ALARM_MESSAGE_SIZE;
	ptr->prg          = prg;
	ptr->alarm_id     = alarm_id++;
	ptr->type         = type;
	ptr->panel_type   = Panel_Info1.panel_type;

	ptr->alarm_count = strlen(mes);
	strcpy(ptr->alarm_message,mes);

	if(alarmatall)
	{
		ptr->where1     = 255;
	}
	if( indalarmpanel )
	{
		p = &ptr->where1;
		for(k=0;(k<indalarmpanel)&&(k<5);k++,p++)
		{
		 *p = alarmpanel[k];
		}
	}
	ptr->change_flag  = 0;
	if( ++ptr_panel->ind_alarms > MAX_ALARMS) ptr_panel->ind_alarms = MAX_ALARMS;
	GAlarm = 1;
 }
 else
	j=-1;
 return j+1;    // 0 - no space; n - alarm index
}

int exec_program(int current_prg, unsigned char *prog_code, long *stack, int port)
{
 int nbytes;
 int type_var,ind,i,ana_dig;
 int id,len,nprog,nitem,lvar,ndeclare;
 int then_else;
 char *return_pointer, *decl_prog, *p_buf, *p, *q;
 unsigned long r;
 long *i_stack, *idecl_stack, *pn;
 long value, v1,v2;
 char *local, perr, *prog;
 struct remote_local_list *r_remote, *remote_local_list;
 int r_ind_remote;
 int ind_remote_local_list;
 Point point;
 Point_Net point_net;

 then_else = alarm_flag = error_flag = 0;

// struct remote_local_list remote_local_list[30];

 prog=prog_code;
/*
 if(port==COM0)
	 prog_virt=prog_code;
 else
	 prog_com=prog_code;
*/
 if (called_program)
	 {
		if (*(prog+2+3)!=DECLARE)
			 return 1;
	 }
 else
 {
	 if(port==COM0)
		index_stack = stack;
	 else
	  index_stack_virt = stack;
 }

 memcpy(&nbytes, prog, 2);
 prog += nbytes+2+3;
 memcpy(&nbytes, prog, 2);       //LOCAL VARIABLES
 local = (prog+2);

 prog += 2 + nbytes;
 memcpy(&nbytes, prog, 2);       //time
 prog += 2;
 p_buf = prog + nbytes;
 time_buf = prog;

 memcpy(&ind_remote_local_list,prog+nbytes,2);      // remote points
 remote_local_list = (struct remote_local_list *)(prog+nbytes+2);
// memcpy(remote_local_list,prog+nbytes+2,ind_remote_local_list*sizeof(struct remote_local_list));

 while (prog < p_buf)
 {
		cond = veval_exp(&prog,local);
		pn = (long *)(prog+1);
		if (cond)
		{
			if(*prog++)
			{
			 if(just_load) *pn = 0;
			 (*pn) += miliseclast_cur;
			}
			else
			{
			 *(prog-1) = 1;
			 *pn = 0;
			}
	 }
	 else
			if(*prog++)
			{
			 *(prog-1) = 0;
			 *pn = 0;
			}
			else
			{
			 if(just_load) *pn = 0;
			 (*pn) += miliseclast_cur;
			}
	 prog += 4;
 }

 prog=prog_code;
 p_buf=prog;
 memcpy(&nbytes, prog, 2);

 g_ind_remote_local_list = ind_remote_local_list;
 g_remote_local_list = remote_local_list;

 p_buf += 2;
 prog += 2;

 prog = prog + *((int*)(prog + nbytes + 1));

 if(port!=COM0)
 {
	port=COM0;
  for(i=0; i<MAX_Routing_table ; i++)
  {
	 if( (Routing_table[i].status&ASYNCRON_INSTALLED) == ASYNCRON_INSTALLED )
	 {
		if( comm_info[((class ASYNCRON *)Routing_table[i].ptr)->com_port].program_nr == current_prg+1 )
		{
//			 com_type = (class ASYNCRON *)Routing_table[i].ptr)->com_port;
			 port = i;
			 break;
		}
	 }
	}
	if( i>=MAX_Routing_table ) return 1;
 }

 alarm_at_all = OFF;
 ind_alarm_panel = 0;
 timeout = 0;
 timeout_asyn = 0;
 perr = 0;
 while(*prog!=0xfe)   //1
 {
	 if( port==COM0)
	 {
		 if (timeout>=6)
		 {
			ptr_panel->programs[current_prg].errcode = 1;
			break;
		 }
	 }
	 else
	 {
		 if (timeout_asyn>=3)
		 {
			 clear_semaphore(&t3000_flag);
			 msleep(10);
		   set_semaphore(&t3000_flag);
       timeout_asyn = 0;
		 }
	 }
	 lvar = 0;
	 if(!then_else)
	 {
		 if (*prog!=0x01)
		 {
			printf("ERROR!!!!!!Virtual!!!!!!!!!!!!!!\n");
			exit(1);
		 }
		 prog++;			// step over 01
		 memcpy(&cur_line, prog, 2);
		 prog += 2;
	 }
	 else
		 if (*prog==0x01)
		 {
			 then_else = 0;
		 	 continue;
		 }

	 switch (*prog++) {
			case ASSIGN:
			case ASSIGNAR:
			case ASSIGNARRAY_1:
			case ASSIGNARRAY_2:
			case STARTPRG:
			case OPEN:
			case ENABLEX:
			case STOP:
			case CLOSE:
			case DISABLEX:
								id = *(prog-1);
								if (id == ASSIGN || id == ASSIGNAR)
										 ana_dig=ANALOG;
								else
										 ana_dig=DIGITAL;

								if (*prog >= LOCAL_VARIABLE && *prog <= STRING_TYPE_ARRAY)
								{
											type_var = LOCAL;
											p = prog;
											prog++;
											prog += 2;
								}
								else
								  if (*prog == LOCAL_POINT_PRG)
								  {
										  prog++;
										  type_var = LOCAL_POINT_PRG;
										  point = *((Point *)prog);
										  prog += sizeof(Point);
									}
								  else
								  {
									  if (*prog == REMOTE_POINT_PRG)
										{
												prog++;
												type_var = REMOTE_POINT_PRG;
												point_net = *((Point_Net *)prog);
												prog += sizeof(Point_Net);
									  }
									}
								if ( id==OPEN )
								{
									 if (type_var == LOCAL_POINT_PRG)
									 {
										if ( point.point_type - 1 == GRP )
										{
											*((Point *)&localopenscreen) = point;
											localopenscreen.panel = Station_NUM-1;
											localopenscreen.network = 0xFFFF;      //NetworkAddress;
											break;
										}
									 }
									 if (type_var == REMOTE_POINT_PRG)
									 {
										if ( point_net.point_type - 1 == GRP )
										{
											localopenscreen = point_net;
									    break;
										}
									 }
								}
								if (id==STARTPRG || id==OPEN || id==ENABLEX) value = 1000L;
								if (id==STOP || id==CLOSE || id==DISABLEX) value = 0L;
								if (id==ASSIGN)
								{
									 value=veval_exp(&prog,local,port,&perr);
									 if (type_var == LOCAL)
											put_local_var(p,value,local);
								}
								else
								 if (id==ASSIGNARRAY_1)
								 {
										v2 = 0;
//										v1 = veval_exp(local);
										v1 = 1;
										v2 = veval_exp(&prog,local,port,&perr);
										value=veval_exp(&prog,local,port,&perr);
//										if (type_var == LOCAL)
										if(put_local_array(p,value,v1,v2/1000L,local))
										 perr=3;
								 }
								 else
									if (id==ASSIGNARRAY_2)
									{
										v2 = 0;
										v1 = veval_exp(&prog,local,port,&perr);
										v2 = veval_exp(&prog,local,port,&perr);
										value=veval_exp(&prog,local,port,&perr);
//										if (type_var == LOCAL)
										if(	put_local_array(p,value,v1/1000L,v2/1000L,local) )
										 perr=3;
									}
									else
									{
									 if (id==ASSIGNAR)
									 {
											ana_dig = (int)(veval_exp(&prog,local)/1000)-1;
											value=veval_exp(&prog,local);
									 }
									 else
									 {
									  if (type_var == LOCAL)
											put_local_var(p,value,local);
									 }
									}
//									if (type_var == LOCAL)
//										put_local_var(p,value,local);
								if (type_var == LOCAL_POINT_PRG)
								{
										put_point(point,value,PROGR,ana_dig,&perr);
								}
								if( perr )
								{
									ptr_panel->programs[current_prg].errcode = perr;
									perr = 0;
								}
								break;
			case PHONE:
									len = *prog++;
									i=0;
									while(*prog!=0x01 && i<len) vmessage[i++] = *prog++;
									vmessage[i]=0;
									phone(vmessage);
									break;
			case REM:
			case DIM:
			case INTEGER_TYPE:
			case BYTE_TYPE:
			case STRING_TYPE:
			case LONG_TYPE:
			case FLOAT_TYPE:
									len = *prog++;
									prog += len;
									break;
			case PRINT:
								 {
									nitem = *prog++;
									i=0;
									vmessage[0]=0;
									for(int j=0;j<nitem;j++)
									{
										switch (*prog++) {
											case DATE:
											case TIME:
																time_t t;
																mtime(&t);
																strcat(&vmessage[i],mctime(&t));
																p=&vmessage[i];
																i += strlen(p)-1;
																vmessage[i]=0;
																break;
											case BEEP:
																vmessage[i++]=0x07;
																break;
											case USER_A:
																strcpy(&vmessage[i],"USER_A");
																i += strlen("USER_A");
																break;
											case USER_B:
																strcpy(&vmessage[i],"USER_B");
																i += strlen("USER_B");
																break;
											case STRING:
																len = *prog++;
																memcpy(&vmessage[i],prog,len);
																i += len;
																vmessage[i] = 0;
																prog += len;
																break;
											default:
															 {
																prog--;
																value = operand(&prog, &p,local);
																if (p)
																	 {
																		strcpy(&vmessage[i],p);
																	 }
																 else
//																		gcvt(value, 3 , &message[i]);
																	 {
//																		ftoa((float)value/(float)1000., 7, 2, &message[i] );
																		longtoa(value,7,2, &vmessage[i]);
																	 }
																while (vmessage[i++]!=0);
																i--;
															 }
																break;
									 }
									}
                           if(*prog==0xFF) prog++;
									print(vmessage);
								 }
									break;
			case CLEARX:              // clear all local variables to zero
/*
									for(ind=0;ind<MAX_VAR;ind++)
											local[ind]=0;
*/
/*
// bad cod
									int t=0,j,k;
									for(ind=0;ind<ind_local_table; )
									{
										j += 1+local_table[j];
										if( !strcmp(&local_table[j], vars_table[cur].name) ) break;
										j += 1+strlen(&local_table[j]);
									}
*/
									break;
			case ENDPRG:
									if (called_program)
									{
/*
// bad cod  - local vars wrong
										 called_program--;
										 prog = decl_prog;
										 for(i=0; i<ndeclare; i++)
										 {
											if (*prog >= 0x082 && *prog <= 0x09B)
											 {
												*(idecl_stack+i) = local[(char)*prog-0x082] ;
												prog += 1;
												continue;
											 }
											if (*prog == LOCAL_POINT_PRG )
											 {
												prog++;
												point = *((Point *)prog);
												prog += sizeof(Point);
												get_point(point,idecl_stack+i,NULL);
												continue;
											 }
											}
*/
									}
									return 1;      // end program
//									break;
			case RETURN:
//									return 1;
									r = poplong(port);
									prog=(char *)MK_FP((unsigned)r,r>>16);

									break;
			case HANGUP:
									hangup();      // end phone call
									break;
			case SET_PRINTER:
									switch (*prog) {
											case 'A': portA_printer = ALL_PRINT; break;
											case 'a': portA_printer = ONLY_PRINT; break;
											case 'B': portB_printer = ALL_PRINT; break;
											case 'b': portB_printer = ONLY_PRINT; break;
											case '0': portA_printer = portB_printer = DISCONNECT_PRINT; break;
									}
									prog++;
									break;
			case RUN_MACRO:
									num_prog = *prog++;      // end program
									break;
			case ON:
									nitem = veval_exp(&prog,local);
									if (nitem < 1 || nitem > *(prog+1))
											{
											 while(*prog!=0x01) prog++;
											 break;
											}
									if (*prog==GOSUB)   //gosub
										 {
											return_pointer =  prog + 2 + *(prog+1)*2;
											r = (((unsigned long)FP_OFF(return_pointer)) << 16)+FP_SEG(return_pointer);
											pushlong(r,port);
										 }
									memcpy(&i, prog + 2 + (nitem-1)*2, 2);
									prog = p_buf + i - 2;
									break;
			case GOSUB:

									return_pointer =  prog + 2 ;
									memcpy(&i, prog, 2);
									prog = p_buf + i - 2;
									r = (((unsigned long)FP_OFF(return_pointer)) << 16)+FP_SEG(return_pointer);
									pushlong(r,port);
									break;

			case ON_ALARM:
									if (alarm_flag)
									{
										memcpy(&i, prog, 2);
										prog = p_buf + i - 2;
										alarm_flag=0;
									}
									else
									 prog += 2;
									break;
			case ON_ERROR:
									if (error_flag)
									{
										memcpy(&i, prog, 2);
										prog = p_buf + i - 2;
										error_flag=0;
									}
									else
									 prog += 2;
									break;
			case GOTOIF:
			case GOTO:
									memcpy(&i, prog, 2);
									prog = p_buf + i - 2;
									break;
			case Alarm:
									if ((p=(char *)memchr(prog,LT,30))!=NULL)
										i=LT;
									else
										if ((p=(char *)memchr(prog,GT,30))!=NULL)
											i=GT;
									*p=0xFF;
									v1= veval_exp(&prog,local);
									v2= veval_exp(&prog,local);
									value = veval_exp(&prog,local);
									len = *prog++;
									memcpy(vmessage, prog, len);
									vmessage[len]=0;
									prog += len;
									if (*prog++)
									{
									if (i==LT)
										if ( v1 > v2+value )
												*(prog-1) = 0;
									if (i==GT)
										if ( v1 < v2 - value)
												*(prog-1) = 0;
									}
									else
									{
									if (i==LT)
										if ( v1 < v2 )
											 {
												*(prog-1) = 1;
												alarm_flag = 1;
												alarm();
											 }
									if (i==GT)
										if ( v1 > v2 )
											 {
												*(prog-1) = 1;
												alarm_flag = 1;
												alarm();
											 }
									 }
									*p=i;
									break;
			case ALARM_AT:
									if (*prog==0xFF)
									{
										 alarm_at_all = On;
										 prog++;
									}
									else
									{
										 while(*prog)
											 alarm_panel[ind_alarm_panel++]=*prog++;
										 prog++;
									}
									break;
			case PRINT_AT:
									if (*prog==0xFF)
									{
										alarm_at_all = On;
										prog++;
									}
									else
									{
										while(*prog)
											 print_panel[ind_print_panel++]=*prog++;
										prog++;
									}
									break;
			case CALLB:
// bad cod  - local vars wrong
									r_ind_remote = ind_remote_local_list;
									r_remote = remote_local_list;

									nprog = *prog++;
									nitem = *prog++;

									return_pointer =  prog ;
									i_stack = index_stack;
									for(i=0; i<nitem; i++)
										 push(veval_exp(&prog,local),port);
									r = (((unsigned long)FP_OFF(return_pointer)) << 16)+FP_SEG(return_pointer);
									pushlong(r,port);

									if( ptr_panel->program_codes[nprog])    //  pointer to code
									 {
										called_program++;
										exec_program(nprog, (char *)ptr_panel->program_codes[nprog],i_stack);
									 }
//									call();
									r = poplong(port);
									prog=(char *)MK_FP((unsigned)r,r>>16);
									for(i=0; i<nitem; i++)
										{
										if ((*prog >= 0x082 && *prog <= 0x09B) && *(prog+1)==0x0FF)
										 {
											local[(char)*prog-0x082] = *(i_stack+i);
											prog += 2;
											continue;
										 }
										if (*prog == LOCAL_POINT_PRG && *(prog+sizeof(Point))==0x0FF)
										 {
											prog++;
											point = *((Point *)prog);
											prog += sizeof(Point);
											prog++;
											put_point(point,*(i_stack+i),PROGR,ana_dig);
											continue;
										 }
										while(*prog++!=0x0FF) ;
										}

									index_stack=i_stack;
									 g_ind_remote_local_list = r_ind_remote;
									 g_remote_local_list = r_remote;
//									while(*prog!='\x1') prog++;
									break;
			case DALARM:
								 {
									alarm_flag = 0;
									cond = veval_exp(&prog,local);  // condition
									memcpy(&value,prog,4);    // delay time
									prog += 4;

									len = *prog++;

									if (cond)         // test condition
									{
										memcpy(vmessage, prog, len);
										vmessage[len]=0;
										prog += len;
										if(just_load)
										 memcpy(prog,&value,4);
										memcpy(&v1,prog,4);
										if( v1>0 )
										{
										 v1 -= miliseclast_cur;
										 memcpy(prog, &v1, 4);
										}
										if (v1<=0)      // delayed time elapsed
										{
//										 i=dalarm(message, current_prg+1, Station_NUM);
										 i=generatealarm(vmessage, current_prg+1, Station_NUM, VIRTUAL_ALARM, alarm_at_all, ind_alarm_panel, alarm_panel, printAlarms);
										 if ( i > 0 )    // new alarm message
										 {
/*
											 new_alarm_flag |= 0x01;  // send the alarm to the destination panels
											 resume(ALARMTASK);
											 if(printAlarms)
											 {
												 strcat(&vmessage[strlen(vmessage)],"\\n");
												 print(vmessage);  // print to printer
												 ptr_panel->alarms[i-1].printer = 1;
											 }
*/
											 alarm_flag = 1;
										 }
										}
									}
									else
									{      // condition is false
										memcpy(&v1,prog+len,4);
										if (v1<=0)   // test for restore
										{
										 memcpy(vmessage, prog, len);
										 vmessage[len]=0;
										 dalarmrestore(vmessage,current_prg+1,Station_NUM);
										 new_alarm_flag |= 0x01;  // send the alarm to the destination panels
										 resume(ALARMTASK);
										}
										prog += len;
										memcpy(prog,&value,4);
									}
									prog += 4;
							 }
							 break;
			case DECLARE:
// bad code - local vars wrong
									if (called_program==0)
										 return 1;
									ndeclare = *prog++;
									idecl_stack=index_stack-ndeclare-1;
									decl_prog = prog;
									for(i=0; i<ndeclare; i++)
									 {
										if (*prog >= 0x82 && *prog <= 0x9B)
										 {
											local[(char)*prog-0x082] = *(idecl_stack+i);
											prog += 1;
											continue;
										 }
										if (*prog == LOCAL_POINT_PRG )
										 {
											prog++;
											point = *((Point *)prog);
											prog += sizeof(Point);
											if ( point.point_type-1 == OUT || point.point_type-1 == IN)
												{
												 called_program--;
												 return 0;
												}
											put_point(point,*(idecl_stack+i),PROGR,ana_dig);
											continue;
										 }
										}
//									declare();
//									while(*prog!='\x1') prog++;
									break;
			case REMOTE_GET:
/*
								 {
									char *p;
									point = *((Point *)(prog+2));
									get_point(point,&value,&p);
									if (*prog >= 0x82 && *prog <= 0x9B)
									{
									}
									if (*prog == LOCAL_POINT_PRG)
									 {
										memcpy(&point, prog+1,2);
										put_point(point,value,ana_dig,PROGR);
									 }
									while(*prog!='\x1') prog++;
								 }
*/
									break;

			case REMOTE_SET:
/*
									point = *((Point *)prog);
									prog += sizeof(Point);
									value = operand(NULL,local);
									put_point(point,value,ana_dig,PROGR);
*/
									break;
			case FOR:
// bad cod  - local vars wrong
//									lvar = *prog++;
									p = prog;
									prog += 3;
									long val1;
									val1 = veval_exp(&prog,local);
									long val2;
									val2 = veval_exp(&prog,local);
									long step;
									step = veval_exp(&prog,local);
//									local[(char)lvar-'\x82'] = (int)((val2-val1)/step)+1 ;
									if(val2>=val1)
									{
									 put_local_var(p,val1,local);
//									local[(char)lvar-0x082] = val1 ;
									 prog += 2;
//											interpret();
									}
									else
									{
									 memcpy(&lvar, prog, 2);
									 prog = p_buf + lvar - 2;
									}
									break;
			case NEXT:
// bad cod - local vars wrong
								 {
									memcpy(&lvar, prog, 2);
									prog = p_buf + lvar - 2 + 4;
//									lvar = *prog++;
                           p = prog;
									prog += 3;
									val1 = veval_exp(&prog,local);
									val2 = veval_exp(&prog,local);
									step = veval_exp(&prog,local);
//									local[(char)lvar-'\x82'] = (int)((val2-val1)/step)+1 ;
//									local[(char)lvar-0x082] += step ;
									q = prog;
									prog = p;
									value=operand(&prog, NULL,local,&perr);    //	veval_exp(local);
									value += step;
									put_local_var(p,value,local);
//									if(local[(char)lvar-0x082]<=val2)
									prog = q;
									if(value<=val2)
									{
									 prog += 2;
									}
									else
									{
									 memcpy(&lvar, prog, 2);
									 prog = p_buf + lvar - 2;
									}
								 }
								 break;
			case IF:
									then_else = 1;
									cond = veval_exp(&prog,local);
									if (cond)
									 {
//										then_else = 1;
//										prog += 2;
										prog++; prog++;
									 }
									else
									 {
//										memcpy(&i, prog, 2);
//										prog = p_buf + i -2;
										prog = p_buf + *((int *)prog) -2;
										if( *prog == 0x01 || *prog == 0xFE)      //TEST DACA EXISTA ELSE
											then_else = 0;
									 }
//									then_else = 1;
									break;
			case IFP:
//									then_else = 0;
									cond = veval_exp(&prog,local);
									if (cond)
									 if (!*prog++)
									 {
										*(prog-1) = 1;
//										prog += 2;
										prog++; prog++;
									 }
									 else
									 {
//										memcpy(&i, prog, 2);
//										prog = p_buf + i -2;
										prog = p_buf + *((int *)prog) -2;
									 }
									else
									{
										*prog++ = 0;
//										memcpy(&i, prog, 2);
//										prog = p_buf + i -2;
										prog = p_buf + *((int *)prog) -2;
									}

									then_else = 1;
									if( *prog == 0x01 || *prog == 0xFE)      //TEST DACA EXISTA ELSE
										then_else = 0;
									break;
			case IFM:
//									then_else = 0;
									cond = veval_exp(&prog,local);
									if (!cond)
									 if (*prog++)
									 {
										*(prog-1) = 0;
//										prog += 2;
										prog++; prog++;
									 }
									 else
									 {
//										memcpy(&i, prog, 2);
//										prog = p_buf + i -2;
										prog = p_buf + *((int *)prog) -2;
									 }
									else
									{
										*prog++ = 1;
//										memcpy(&i, prog, 2);
//										prog = p_buf + i -2;
										prog = p_buf + *((int *)prog) -2;
									}
									then_else = 1;
									if( *prog == 0x01 || *prog == 0xFE)      //TEST DACA EXISTA ELSE
										then_else = 0;
									break;
			case ELSE:
									prog++;
//									memcpy(&i, prog, 2);
//									prog = p_buf + i -2;
									prog = p_buf + *((int *)prog) -2;
									break;
			case WAIT:
									return_pointer = prog-4;
									if (*prog==0xA1)
									{
											memcpy(&r,++prog,4);
											prog += 4;
									}
									else
									{
											r = (unsigned long)veval_exp(&prog,local);
									}

//							 long n;
							 memcpy(&value,prog,4);
							 value += miliseclast_cur;
							 if (value/1000L >= r)
							 {
									memset(prog,0,4);
									*((int *)(p_buf + nbytes + 1))=0;
                  timeout = 0;
							 }
							 else
							 {
									memcpy(prog,&value,4);
									*((int *)(p_buf + nbytes + 1))=return_pointer-p_buf;
									return 1;
							 }
							 prog += 4;
							 break;
	 }
	}
}

long veval_exp(char **prg, char *local, int port, char *perr)
{
 int i, m;
 long n;
 char *p,*prog;;
 signed char w;
 unsigned long timer;
// time_t timer;
 struct tm *tblock;
 prog = *prg;

 if (*prog >= LOCAL_VARIABLE && *prog <= REMOTE_POINT_PRG )
	push(operand(&prog, NULL,local,perr),port);

 while( !isdelimit(*prog))         // && code < )
 {
	switch (*prog++) {
		case PLUS:
							 push(pop(port) + pop(port),port);
							 break;
		case MINUS:
							 push(-pop(port) + pop(port),port);
							 break;
		case MINUSUNAR:
							 push(-pop(port),port);
							 break;
		case POW:
							 op2 = pop(port); op1 = pop(port);
							 m = op2/1000L;
							 n = op1;
							 if(m>1)
							 {
								for(i=0;i<m-1;i++)
								 n = (n/1000L)*op1 + (n%1000L)*op1/1000L;
							 }
							 push( n,port );
							 break;
		case MUL:
							 op2 = pop(port); op1 = pop(port);
							 push( (op1/1000L)*op2 + (op1%1000L)*op2/1000L,port );
							 break;
		case DIV:
							 op2 = pop(port); op1 = pop(port);
							 if(op2==0)
									push(1000L,port);
							 else
								 push( (op1/op2)*1000L + ((op1%op2)*1000L)/op2,port );
							 break;
		case MOD:
							 op2 = pop(port); op1 = pop(port);
							 if(op2==0)
								 push(1000L,port);
							 else
								 push( ((op1/1000L)%(op2/1000L)) * 1000L,port );
							 break;
		case XOR:
							 op2 = pop(port)/1000L; op1 = pop(port)/1000L;
							 push((op2 ^ op1)*1000L, port);
							 break;
		case OR:
							 op2 = pop(port); op1 = pop(port);
							 push(op2 || op1, port);
							 break;
		case AND:
							 op2 = pop(port); op1 = pop(port);
							 push(op2 && op1, port);
							 break;
		case NOT:
							 op1 = !pop(port);
							 push(op1, port);
							 break;
		case GT:
							 op2 = pop(port); op1 = pop(port);
							 push(op1 > op2, port);
							 break;
		case GE:
							 op2 = pop(port);
//							  op1 = pop(port);
							 push(pop(port) >= op2, port);
							 break;
		case LT:
							 op2 = pop(port); op1 = pop(port);
							 push(op1 < op2, port);
							 break;
		case LE:
							 op2 = pop(port);
//							  op1 = pop(port);
							 push(pop(port) <= op2, port);
							 break;
		case EQ:
							 op2 = pop(port); op1 = pop(port);
							 push(op1 == op2, port);
							 break;
		case NE:
							 push(pop(port) != pop(port), port);
							 break;
		case ABS:
							 push(labs(pop(port)), port);
							 break;
		case LN:
							 push((float)log(pop(port)), port);
							 break;
		case LN_1:
							 push((float)exp(pop(port)), port);
							 break;
		case SQR:
							 push((float)sqrt(pop(port)), port);
							 break;
		case INT:
							 push( pop(port)/1000L * 1000L, port );
							 break;
		case SENSOR_ON:
							{
							 op1 = pop(port);
							 push(ptr_panel->inputs[((Point *) (prog-3))->number].sen_on, port);
							}
							break;
		case SENSOR_OFF:
							{
							 pop(port);
							 push(ptr_panel->inputs[((Point *) (prog-3))->number].sen_off, port);
							}
							break;
		case INTERVAL:
							if(just_load)
//										if(n == -77)
							{
							 n = (unsigned long)pop(port);
							 push(0, port);
							}
							else
							{
							 memcpy(&n,prog,4);
							 n -= miliseclast_cur;
							 if (n>0)
							 {
									pop(port);
									push(0, port);
							 }
							 else
							 {
									 if( n+miliseclast_cur == LONGTIMETEST )
									 {
										 n = (unsigned long)pop(port);
										 push(0, port);
									 }
									 else
									 {
										n = (unsigned long)pop(port);
										push(1, port);
									 }
							 }
							}
							memcpy(prog,&n,4);
							prog += 4;
							break;
	 case TIME_ON:
								 pn = (long *)(time_buf+(*(int *)prog));
								 if( *((char *)pn - 1) )
									 push(*pn, port);
								 else
									 push(0, port);
								 prog += 2;
								 break;
	 case TIME_OFF:
								 pn = (long *)(time_buf+(*(int *)prog));
								 if( *((char *)pn - 1) )
									 push(0, port);
								 else
									 push(*pn, port);
								 prog += 2;
								 break;
	 case TIME_FORMAT:
							 break;
	 case RUNTIME:
							 i = (int)pop(port)/1000L;
							 if(!i)
							 {
								 push((long)miliseclast_cur*1000l,port);
							 }
							 else
								 push(0,port);
							 break;
	 case Status:
								 i = (int)pop(port)/1000L;
								 if( rs485port!=-1 )
								 {
									 if(i==Station_NUM)
									 {
										 if( (( class ConnectionData *)Routing_table[rs485port].ptr)->OS==Station_NUM )
										 {
											push(0,port);
										 }
										 else
										 {
											push(1000L,port);
										 }
									 }
									 else
									 {
										if( (( class ConnectionData *)Routing_table[rs485port].ptr)->panel_info1.active_panels&(1l<<(i-1)) )
											push(1000L,port);
										else
											push(0,port);
									 }
								 }
								 else
									push(0,port);

/*
								 for(i=0; i<MAX_Routing_table; i++)
								 {
									if( (Routing_table[i].status&RS485_ACTIVE)==RS485_ACTIVE )
									{
									 if(n==Station_NUM)
									 {
										 if( ((class MSTP *)Routing_table[i].ptr)->OS=recframe.Frame.Source;)
									 }
									 else
									 {
										if( (((class MSTP *)Routing_table[i].ptr)->panel_info1.active_panels)&(1<<(n-1)) )
										{
										 push(1000, port);
										 break;
										}
									 }
									}
								 }
								 if( i>=MAX_Routing_table )
								 {
									push(0, port);
								 }
*/
								 break;
	 case AVG:
							 {
								m = *prog++;
								value=0;
								for(i=0;i<m;i++)
									value += pop(port);
								push(value/m, port);
								break;
							 }
	 case MAX:
							 {
								m = *prog++;
								value=pop(port);
								for(i=0;i<m-1;i++)
									if((v=pop(port)) > value) value = v;
								push(value, port);
								break;
							 }
	 case MIN:
							 {
								m = *prog++;
								value=pop(port);
								for(i=0;i<m-1;i++)
									if((v=pop(port)) < value) value = v;
								push(value, port);
								break;
							 }
	 case CONPROP:
							 m = (int)pop(port);
							 i=(int)pop(port);
							 if(m>4000) m=4000;
							 if(m<0) m=0;
							 n=m;
							 if (ptr_panel->controllers[i-1].auto_manual==AUTO)
							 {
								ptr_panel->controllers[i-1].proportional = (char)n;
								ptr_panel->controllers[i-1].prop_high = (char)(n/256);
							 }
							 push((long)n, port);
							 break;
	 case CONRATE:
							 value=pop(port);
							 i=(int)pop(port);
							 if (value<0) value=0;
//							 if(value>0.2) value=0.2;
							 if(value>200L) value=200L;
//							 n=(int)(value*100);
							 n=(int)(value/10);
							 if (ptr_panel->controllers[i-1].auto_manual==AUTO)
								 ptr_panel->controllers[i-1].rate = (char)n;
//							 push(((float)n)/100, port);
							 push((long)n*10, port);
							 break;
	 case CONRESET:
							 m=(int)pop(port);
							 i=(int)pop(port);
							 if(m>255) m=255;
							 if(m<0) m=0;
							 n=m;
							 if (ptr_panel->controllers[i-1].auto_manual==AUTO)
								 ptr_panel->controllers[i-1].reset = (char)n;
							 push((long)n, port);
/*
							 m=(int)pop(port);
							 i=(int)pop(port)/1000L;
							 m=0;
							 if( rs485port!=-1 )
							 {
								m=(( class ConnectionData *)Routing_table[rs485port].ptr)->panel_info1.active_panels&(1l<<(i-1));
							 }
							 if(m)
								push(1000L,port);
							 else
								push(0,port);
*/
							 break;
	 case Tbl:
						 push(1, port);
						 break;
	 case WR_ON:
	 case WR_OFF:
						{
						 i=pop(port)/1000;   //which time on
						 n=pop(port)/1000;   //routine_number

						 w = ora_current.dayofweek-1;
						 if (w<0) w = 6;
						 p =(char *)ptr_panel->wr_times[n-1][w].time2;

						 if(*(prog-1)==WR_ON)
								 value = (long)p[4*(i-1)+1]*3600L + (long)p[4*(i-1)]*60L;
						 else
								 value = (long)p[4*(i-1)+3]*3600L + (long)p[4*(i-1)+2]*60L;
						 push(value*1000L, port);
						 break;
						}
	case DOM:
	case DOW:
	case DOY:
 	case MOY:
					 {
						/* gets time of day */
//						set_semaphore_dos();
//						timer = mtime(NULL);
//						clear_semaphore_dos();
//						 tblock = localtime(&timer);
						 timer = timesec1970 + timestart;
						 tblock = localtime((const long *)&timer);
						 switch( *(prog-1) )
						 {
							case DOM:
								value = (tblock->tm_mday)*1000L;
								break;
							case DOW:
								value = tblock->tm_wday*1000L;
								break;
							case DOY:
								value = (tblock->tm_yday+1)*1000L;
								break;
							case MOY:
								value = (tblock->tm_mon+1)*1000L;
                break;
						 }
						 push(value, port);
						 break;
						}
	case POWER_LOSS:
						 push(0, port);
						 break;
	case SCANS:
						 push(1, port);    // nr scanari pe secunda
						 break;
	case SUN:
						 push(0, port);
						 break;
	case MON:
						 push(1000, port);
						 break;
	case TUE:
						 push(2000, port);
						 break;
	case WED:
						 push(3000, port);
						 break;
	case THU:
						 push(4000, port);
						 break;
	case FRI:
						 push(5000, port);
						 break;
	case SAT:
						 push(6000, port);
						 break;
//						push((long)*(prog-1), port);
//						break;
	case JAN:
						 push(1000, port);
						 break;
	case FEB:
						 push(2000, port);
						 break;
	case MAR:
						 push(3000, port);
						 break;
	case APR:
						 push(4000, port);
						 break;
	case MAY:
						 push(5000, port);
						 break;
	case JUN:
						 push(6000, port);
						 break;
	case JUL:
						 push(7000, port);
						 break;
	case AUG:
						 push(8000, port);
						 break;
	case SEP:
						 push(9000, port);
						 break;
	case OCT:
						 push(10000, port);
						 break;
	case NOV:
						 push(11000, port);
						 break;
	case DEC:
						 push(12000, port);
						 break;
	case TIME:
					 {
/*						struct dostime_t t;

						set_semaphore_dos();
						_dos_gettime(&t);
						clear_semaphore_dos();
						value = t.hour*3600 + t.minute*60 + t.second;
*/
						value =  ora_current_sec;
						push(value * 1000L, port);
						break;
					 }
	case USER_A:
					 push(1, port);
					 break;
	case USER_B:
					 push(0, port);
					 break;
	case UNACK:
					 push(0, port);
					 break;
	case INKEYD:
					 i = pop(port)/1000;   //offset last char
					 m = (int)(pop(port)/1000);   //nr. of chars
					 n = pop(port)/1000;          //offset
					 if( n >= i )
						 push( -1000l, port );
					 else
						 push( inkey( local + n, m, i-n, port)*1000l, port );
//					 push( inkey( local + (pop(port)/1000), pop(port)/1000, port)*1000l, port );
					 break;
	case OUTPUTD:
					 push( outputd( local + (pop(port)/1000), pop(port)/1000, port)*1000l, port );
					 break;
	case ASSIGNARRAY:
					 if (*prog >= LOCAL_VARIABLE && *prog <= STRING_TYPE_ARRAY)    // local var
						push( ((long)*((int *)(prog+1)))*1000L, port );
					 prog += 3;
					 break;
	case ASSIGNARRAY_1:
					 push(getvalelem(&prog, 1, pop(port)/1000L, local, perr), port);
					 break;
	case ASSIGNARRAY_2:
					 push(getvalelem(&prog, pop(port)/1000L, pop(port)/1000L, local, perr), port);
					 break;
	default:
							prog--;
							push(operand(&prog,NULL,local,perr), port);
	}
 }
 if (*prog==0xFF) prog++;
 *prg = prog;
 return pop(port);
}

long getvalelem(char **prg, long l, long c, char *local, char *perr)
{
 char *p,*prog;
 long n,i;
 prog = *prg;
 i=0;
 if( *prog == ASSIGNARRAY)
 {
	prog++;
	i = *((int *)(prog+1));
	*prg = prog;
 }
 if (*prog >= STRING_TYPE && *prog <= STRING_TYPE_ARRAY )    // local var
 {
	p = local + *((int *)(prog+1));
	prog += 3;
	*prg = prog;
	if( *((int *)(p-4)) )
	{
		if( l<1 || l>*((int *)(p-4)) || c<1 || c>*((int *)(p-2)) )
		{
		 if(perr)
			*perr=INDEX_OUT_OF_RANGE;
		 if(!i)
			 return 0;
		 else
			 return ( (long)i*1000L );
		}
	}
	else
	{
		if( c<1 || c>*((int *)(p-2)) )
		{
		 if(perr)
			*perr=INDEX_OUT_OF_RANGE;
		 if(!i)
			 return 0;
		 else
			 return ( (long)i*1000L );
		}
	}
	switch(*(prog-3)){
		case FLOAT_TYPE_ARRAY:
		case LONG_TYPE_ARRAY:
				if(!i)
					return ( *((long *)&p[( (l-1)*( (*((int *)(p-2)))-1 ) + c-1 ) * 4 ]) );
				else     //address
					return ( (long)(i + ( (l-1)*( (*((int *)(p-2)))-1 ) + c-1 ) * 4)*1000L  );
				break;
		case INTEGER_TYPE_ARRAY:
				if(!i)
					return ( (long)(*((int *)&p[( (l-1)*( (*((int *)(p-2)))-1 ) + c-1 ) * 2 ]))*1000L );
				else
					return ( (long)(i+(( (l-1)*( (*((int *)(p-2)))-1 ) + c-1 ) * 2 ))*1000L );
				break;
		case BYTE_TYPE_ARRAY:
				if(!i)
					return ( (long)(p[( (l-1)*( (*((int *)(p-2)))-1 ) + c-1 ) ])*1000L );
				else
					return ( (long)(i+(( (l-1)*( (*((int *)(p-2)))-1 ) + c-1 ) ))*1000L );
				break;
		case STRING_TYPE:
				if(!i)
					return ( (long)(p[ c-1 ])*1000L );
				else
					return ( (long)(i+c-1)*1000L );
				break;
	}
 }
 return 0;
}

long localvalue(char *p, char *local)
{
  long l;
  switch(*p){
		case FLOAT_TYPE:
		case LONG_TYPE:
				l = *((long *)&local[*((int *)(p+1))]);
				break;
		case INTEGER_TYPE:
					l = (long)(*((int *)&local[*((int *)(p+1))]))*1000L;
					break;
		case BYTE_TYPE:
					l = (long)((signed char)local[*((int *)(p+1))])*1000L;
					break;
	}
	return l;
}

long operand(char **prg, char **buf,char *local, char *perr)
{
 char *prog;
 prog = *prg;
 if (*prog >= LOCAL_VARIABLE && *prog <= BYTE_TYPE)    // local var
 {
	prog += 3;
	if(buf)
		*buf=0;
	*prg = prog;
	return localvalue(prog-3, local);
 }

 if (*prog == LOCAL_POINT_PRG)
 {
	if( (((Point *)(prog+1))->point_type)-1==AY )
	{
		++prog;
		get_ay_elem(&prog, &value, local, perr);
	}
	else
	{
		get_point(*((Point *)(++prog)), &value, buf);
		prog += sizeof(Point);
	}
	*prg = prog;
	return value;              // = read point
 }
 if (*prog == REMOTE_POINT_PRG)
 {
	if( (((Point_Net *)(prog+1))->point_type)-1==AY )
	{
	 char *p;
	 int num;
	 ++prog;
	 p = prog;
	 prog += sizeof(Point_Net);
	 num = veval_exp(&prog,local)/1000L-1;
	 get_point(*((Point_Net *)p), &value, buf);
	}
	else
	{
	 get_point(*((Point_Net *)(++prog)), &value, buf);
	 prog += sizeof(Point_Net);
	}
	*prg = prog;
	return value;              // = read point
 }
 if (*prog == CONST_VALUE_PRG)
 {
	prog += 5;
	if(buf)
		*buf=0;
	*prg = prog;
	return *((long *)(prog-4));
 }
 return 0;
}

int get_ay_elem(char **prg, long *value, char *local, char *perr)
{
 char *prog;
 int num;
 byte point_type,num_point;
 prog = *prg;
 point_type = (((Point *)(prog))->point_type)-1;
 num_point = ((Point *)(prog))->number;
 prog += sizeof(Point);
 num = veval_exp(&prog,local)/1000L-1;
 if(num < ptr_panel->arrays[num_point].length & num >= 0)
 {
	 long *p =  ptr_panel->arrays_data[num_point];
	 *value = *(p + num);
 }
 else
 {
	 *value = 0;
	 if(perr)
		 *perr = 4;
 }
 *prg = prog;
}

int get_point(Point_Net point, long *value, char **buf, int mon)
{
 int i;
// if( point.panel+1==Station_NUM && point.network==NetworkAddress )
 if( point.panel+1==Station_NUM && point.network==0xFFFF )
 {
//	if( point.network == 0xFFFF ) point.network = NetworkAddress;
	get_point( *((Point *)&point), value, buf);
 }
 else
 {
  *value = 0;
	if(!mon)
	{
 //  if( point.network == 0xFFFF ) point.network = NetworkAddress;
	 for(i=0;i<g_ind_remote_local_list;i++)
		if( point==g_remote_local_list[i].point
/*
		||
			(point.panel==g_remote_local_list[i].point.panel &&
			point.number==g_remote_local_list[i].point.number &&
			point.point_type==g_remote_local_list[i].point.point_type &&
			point.network==NetworkAddress && g_remote_local_list[i].point.network==0xFFFF)
*/
		 )
		{
		 if(remote_points_list[g_remote_local_list[i].index].write)
		 {
			remote_points_list[g_remote_local_list[i].index].read_write=1;
			remote_points_list[g_remote_local_list[i].index].write=0;
		 }
		 *value=(long)(remote_points_list[g_remote_local_list[i].index].info.point_value);
     break;
		}
	}
	else
	{
		for(i=0;i<MAXREMOTEPOINTS82;i++)
		{
		 if( remote_points_list[i].info.point.point_type )
		 {
			if( remote_points_list[i].info.point==point )
			{
			 *value=(long)(remote_points_list[i].info.point_value);
       break;
			}
		 }
		}
	}

 }
}

int get_point(Point point, long *value, char **buf)
{
 int range;
 char i;
 byte point_type,num_point;
 point_type = point.point_type-1;
 num_point = point.number;

 if(num_point < ptr_panel->table_bank[point_type])
 {
 	switch (point_type) {
	 case OUT:
						if(!ptr_panel->outputs[num_point].digital_analog) // DIGITAL
						{
							*value=ptr_panel->outputs[num_point].control?1000L:0L;
							i=0;
							range = ptr_panel->outputs[num_point].range;
							if(buf)
							{
								range -= DIG1;
//								*buf = &(dig_range_array[range].dunits[ptr_panel->outputs[num_point].control^(dig_range_array[range].value % 2)][0]);
								*buf = &(dig_range_array[range].dunits[ptr_panel->outputs[num_point].control][0]);
							}
//						 else
//								*buf = 0;
						}
						else
							*value=ptr_panel->outputs[num_point].value;
					break;
	 case IN:
						if(!ptr_panel->inputs[num_point].digital_analog)
						{
							*value=ptr_panel->inputs[num_point].control?1000L:0L;
							i=0;
							range = GetRange_In(ptr_panel->inputs[num_point].range);
							if(buf)
//							if(ptr_panel->inputs[num_point].analog_digital==DIG)
							{
								range -= DIG1;
//								*buf = &(dig_range_array[range].dunits[ptr_panel->inputs[num_point].control^(dig_range_array[range].value % 2)][0]);
								*buf = &(dig_range_array[range].dunits[ptr_panel->inputs[num_point].control][0]);
							}
//							else
//							*buf = 0;
						}
						else
            {
							*value=ptr_panel->inputs[num_point].value;
            }
						break;
	 case VAR:
						if(!ptr_panel->vars[num_point].digital_analog)
						{
//							char m = 0;
//							if( ON_OFF <= range && range <= HIGH_LOW ) m = 1;
//							*value = (m^(ptr_panel->vars[num_point].value && 0x01)) ? 1000 : 0;
							*value = ptr_panel->vars[num_point].value;
							i=0;
							range = GetRange_Var(ptr_panel->vars[num_point].range);
							if(buf)
//							if(ptr_panel->inputs[num_point].analog_digital==DIG)
								*buf = &(dig_range_array[range].dunits[ptr_panel->vars[num_point].control][0]);
//							else
//								*buf = 0;
						}
						else
							*value=ptr_panel->vars[num_point].value;
						break;
	 case CON:
					*value=ptr_panel->controllers[num_point].value;
					break;
	 case WR:
					*value=ptr_panel->weekly_routines[num_point].value?1000L:0;
					break;
	 case AR:
					*value=ptr_panel->annual_routines[num_point].value;
					break;
	 case PRG:
					*value=ptr_panel->programs[num_point].on_off;
					break;
	 case GRP:
					*value=ptr_panel->control_groups[num_point].state?1000L:0;
					break;
	 }
 }
 else
	 *value = 0;
 return num_point;
}

/*
void write_point(unsigned char mode,float *value,unsigned char num_point)
{
}

void read_point(unsigned char mode, float *value, unsigned char num_point)
{
 *value = 5;
}
*/

void push(long value,int port)
{
 if(port==COM0)
	 *index_stack++ = value;
 else
	 *index_stack_virt++ = value;
}


//float pop(void)
long pop(int port)
{
 if(port==COM0)
	 return (*(--index_stack));
 else
	 return (*(--index_stack_virt));
}

void pushlong(unsigned long value,int port)
{
 if(port==COM0)
	 memcpy(index_stack++, &value, 4);
 else
	 memcpy(index_stack_virt++, &value, 4);
}


unsigned long poplong(int port)
{
 unsigned long value;
 if(port==COM0)
 {
	memcpy( &value, --index_stack, 4);
 }
 else
	memcpy( &value, --index_stack_virt, 4);
 return (value);
}


int phone(char *message)    // phone call
{
 strcpy(dial_buffer, message);
 DIAL_dial  =1;
 DIAL_action=1;
 if( tasks[DIAL].status == SUSPENDED )
		 resume(DIAL);
// resume(DIAL);
}

int outputd(char* adr, int num, int port)
{
  int i;
  i = 0;
	if( port!=COM0 )
  {
//	 ((class ASYNCRON *)Routing_table[port].ptr)->port->Dtr( !dtr );

	 ((class ASYNCRON *)Routing_table[port].ptr)->port->write_buffer( (char *)adr, num );
	 l = timestart;
	 while( ((class ASYNCRON *)Routing_table[port].ptr)->port->isr_data->tx_running )
	 {
		if(timestart > l+6)
		{
		break;
		}
	 }

//	 ((class ASYNCRON *)Routing_table[port].ptr)->port->Dtr( dtr );

	 i=num-((class ASYNCRON *)Routing_table[port].ptr)->port->isr_data->TXQueue.InUseCount();
	 if( ((class ASYNCRON *)Routing_table[port].ptr)->port->isr_data->tx_running )
	 {
		OUTPUT( ((class ASYNCRON *)Routing_table[port].ptr)->port->isr_data->uart + INTERRUPT_ENABLE_REGISTER,
					IER_RX_DATA_READY + IER_MODEM_STATUS + IER_LINE_STATUS );
		 ((class ASYNCRON *)Routing_table[port].ptr)->port->FlushTXBuffer();
		 ((class ASYNCRON *)Routing_table[port].ptr)->port->resettxrunning();
	 }
	}
	return i;
}

int print(char *message)  // print to printer
{
	set_semaphore(&print_sem);
	if( print_message_pool.put( message, strlen(message)+1 ) )
	{
	 action=1;
	 print_flag=1;
	 if( tasks[MISCELLANEOUS].status == SUSPENDED )
		 resume(MISCELLANEOUS);
	}
	clear_semaphore(&print_sem);
  return 0;
}

int	hangup()    	// end phone call
{
}

void alarm(void)
{
 putmessage();    // alarm
}

void dalarmrestore(char *mes, int prg, int panel)
{
 int j;
 Alarm_point *ptr;

 ptr = ptr_panel->alarms;
 for(j=0;j<MAX_ALARMS;ptr++,j++)
 {
	if( ptr->alarm )
	 if( ptr->alarm_panel==panel )
		if( ptr->prg==prg )
		 if( !ptr->restored )
			if (ptr->alarm_count == strlen(mes) )
			 if( !strcmp(ptr->alarm_message, mes) )
			 {
				ptr->restored = 1;
				ptr->where_state1 = 0;
				ptr->where_state2 = 0;
				ptr->where_state3 = 0;
				ptr->where_state4 = 0;
				ptr->where_state5 = 0;
/*
				if(--ptr_panel->ind_alarms==0)
					 GAlarm = 0;
*/
				if( !ptr->acknowledged )
				{
				 if(--ptr_panel->ind_alarms==0)
							GAlarm = 0;
				}
				return;
			 }
 }
}

int checkforalarm(char *mes, int prg, int panel, int id = 0 )
{
 Alarm_point *ptr;
 ptr = ptr_panel->alarms;
 for(j=0;j<MAX_ALARMS;ptr++,j++)
 {
	if( ptr->alarm )
	 if( ptr->alarm_panel == panel )
		if( ptr->prg==prg )
		 if( !id )
		 {
			if( !ptr->restored )
			 if (ptr->alarm_count == strlen(mes) )
				if( !strcmp(ptr->alarm_message, mes) )
				{
				 return j+1;          // existing alarm
				}
		 }
		 else
		 {
			if( ptr->alarm_id == *((int *)mes) )
				return j+1;           // existing alarm
		 }
 }
 return 0;  // alarm does not exist
}

int printalarmproc(char *mes, int j)
{
 long t;

		 t=ptr_panel->alarms[j-1].alarm_time;
		 if(ptr_panel->alarms[j-1].panel_type!=T3000)
		 {
			t += timezone;
			if ( daylight ) t -= 3600;
		 }
		 memmove(mes+26, mes, L_ALARMM_TIME);
		 memcpy(mes, ctime(&t),26);
		 mes[25] = ':';

		 strcat(&mes[strlen(mes)],"\\n");
		 print(mes);  // print to printer
		 ptr_panel->alarms[j-1].printer = 1;
}

// ret:  0 - no space for alarm, 1 - n alarm index, -1 message already on
//int dalarm(char *mes, int prg, int panel)
int generatealarm(char *mes, int prg, int panel, int type, char alarmatall,char indalarmpanel,char *alarmpanel,char printalarm)
{
 long t;
 int j;
 if( checkforalarm(mes,prg,panel)>0 ) return -1;
 j=putmessage(mes,prg,type,alarmatall,indalarmpanel,alarmpanel);    // alarm
 if ( j > 0 )    // new alarm message
 {
	 new_alarm_flag |= 0x01;  // send the alarm to the destination panels
	 resume(ALARMTASK);
	 if(printalarm)
	 {
		 printalarmproc(mes,j);
	 }
 }
 return j;
}

int	call()
{
}

int declare()
{
}

void put_local_var(char *p, long value, char *local)
{
  switch(*p){
		case FLOAT_TYPE:
		case LONG_TYPE:
				*((long *)&local[*((int *)(p+1))])=value;
				break;
		case INTEGER_TYPE:
					*((int *)&local[*((int *)(p+1))])=(int)(value/1000L);
					break;
		case BYTE_TYPE:
					local[*((int *)(p+1))]=(char)(value/1000L);
					break;
	}
}

int put_local_array(char *p, long value, long v1, long v2, char *local)
{
	int k;
	if( *((int *)&local[ *((int *)(p+1)) - 4]) )
	{
	 if ( v1<=0 || v1 > *((int *)&local[ *((int *)(p+1)) - 4]) ||
			v2<=0 || v2 > *((int *)&local[ *((int *)(p+1)) - 2]) )
			return 1;
	}
	else
	{
	 if (	v2<=0 || v2 > *((int *)&local[ *((int *)(p+1)) - 2]) )
			return 1;
	}
	switch(*p){
		case FLOAT_TYPE_ARRAY:
		case LONG_TYPE_ARRAY:
				k=4;
				break;
		case INTEGER_TYPE_ARRAY:
				k=2;
				break;
		case BYTE_TYPE_ARRAY:
//		case STRING_TYPE_ARRAY:
				k=1;
				break;
  }
  k = *((int *)(p+1)) + (( v1-1 ) * ( *((int *)&local[((*((int *)(p+1)))-2)]) ) + v2-1) * k;
  switch(*p){
		case FLOAT_TYPE_ARRAY:
		case LONG_TYPE_ARRAY:
				*((long *)&local[k])=value;
				break;
		case INTEGER_TYPE_ARRAY:
				*((int *)&local[k])=(int)(value/1000L);
				break;
		case BYTE_TYPE_ARRAY:
//		case STRING_TYPE_ARRAY:
				local[k]=(char)(value/1000L);
				break;
	}
  return 0;
}

int put_point(Point_Net point, long value, int prog_op, int v)
{
}

//int put_point(int point, float value, int ana_dig, int prog_op)
int put_point(Point point, long value, int prog_op, int v, char *perr)
{
 union {
		Str_out_point *pout;
		Str_in_point *pin;
		Str_variable_point *pvar;
 } ptr;
 byte point_type,num_point;
 point_type = point.point_type-1;
 num_point = point.number;
// write value to point
/*
 if(point.panel+1!=Station_NUM)
 {
#ifdef NETWORK_COMM
	for(int i=0;i<g_ind_remote_local_list;i++)
	if(!memcmp(point,&g_remote_local_list[i].point,2))
	 {
		if(remote_points_list[g_remote_local_list[i].index].read)
			{
			remote_points_list[g_remote_local_list[i].index].read_write=1;
			remote_points_list[g_remote_local_list[i].index].read=0;
			}
//		remote_points_list[g_remote_local_list[i].index].info.point_value=(float)value/(float)1000.;
		remote_points_list[g_remote_local_list[i].index].info.point_value=value;
		remote_points_list[g_remote_local_list[i].index].change=1;
	 }
#endif
 }
 else
*/
 if(num_point < ptr_panel->table_bank[point_type])
 {
	switch (point_type) {
	 case OUT:
				ptr.pout = &ptr_panel->outputs[num_point];
				if( ptr.pout->auto_manual == AUTO || (ptr.pout->auto_manual == MAN && prog_op==OPERATOR))
				{
						if(!ptr.pout->digital_analog) // DIGITAL
						{
						   if( value ) value = 1000L;
							 ptr.pout->control=(int)(value && 1 );
						}
						else
						{
							switch (ptr.pout->range){
								 case V0_10:
										if (value>10000) value = 10000;
										if (value<0)  value = 0;
										break;
								 case P0_100:
								 case P0_100_Open:
								 case	P0_100_Close:
										if (value>100000) value = 100000;
										if (value<0)   value = 0;
										break;
								 case P0_20psi:
								 case I_0_20ma:
										if (value>20000) value = 20000;
										if (value<0)   value = 0;
										break;
							}
						}
						ptr.pout->value=value;
				}
				break;
	 case IN:
				ptr.pin = &ptr_panel->inputs[num_point];
				if( ptr.pin->auto_manual == AUTO || (ptr.pin->auto_manual == MAN && prog_op==OPERATOR))
					{
						char dig_ana;
								ptr.pin->value=value;
						if( !ptr.pin->digital_analog )
							 ptr.pin->control=(int)(value && 0x1);
					}
					break;
	 case VAR:
					ptr.pvar = &ptr_panel->vars[num_point];
				   if( ptr.pvar->auto_manual == AUTO || (ptr.pvar->auto_manual == MAN && prog_op==OPERATOR))
					{
						ptr.pvar->value=value;
						if( !ptr.pvar->digital_analog )
						{
							ptr.pvar->control=(int)(value && 0x01);
						}
					}
					break;
	 case CON:
					if( ptr_panel->controllers[num_point].auto_manual == AUTO )
						ptr_panel->controllers[num_point].value=value;
					break;
	 case WR:
					if( ptr_panel->weekly_routines[num_point].auto_manual == AUTO  || (ptr_panel->weekly_routines[num_point].auto_manual == MAN && prog_op==OPERATOR))
						ptr_panel->weekly_routines[num_point].value=value?1:0;
					break;
	 case AR:
					if( ptr_panel->annual_routines[num_point].auto_manual == AUTO )
						ptr_panel->annual_routines[num_point].value=value;
					break;
	 case PRG:
					if( ptr_panel->programs[num_point].auto_manual == AUTO )
						ptr_panel->programs[num_point].on_off=value;
					break;
	 case AMON:
					ptr_panel->analog_mon[num_point].status=value;
					break;
	 case AY:
					if(v >= ptr_panel->arrays[num_point].length || v < 0)
					{
						v = 0;
						if(perr)
						 *perr = 5;
					}
					else
					{
					 long *p =  ptr_panel->arrays_data[num_point];
					 *(p + v) = value;
					}
					break;
	 }
 }
 return num_point;
}
#endif
