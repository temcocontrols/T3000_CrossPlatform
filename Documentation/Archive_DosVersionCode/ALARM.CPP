// atof
#define NEW
#include <windows.h>
#include "recstruc.h"
#include "fxengine.h"
#include "t3000def.h"
#include <string.h>
#include "ggrid.h"
#include "gedit.h"
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include "rs485.h"
#include "ptp.h"
#include "ipx.h"

#define min(a,b)    (((a) < (b)) ? (a) : (b))

#define OFF 0
#define ON 1


#include "mtkernel.h"
#include "gmbar.h"
#include "graph.h"
#include "serial.h"

#define MODE_TEXT 1
#define MODE_GRAPHIC 0
#define TEXT_FOND_COLOR White


#define INDIVIDUAL -1

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

extern char maxtbl;
extern unsigned long timesec1970,timestart;
extern char huge *lin_hor;
extern int fground;

extern int mode_text;
extern char huge *message[];


extern int  Station_NUM;
extern int local_panel;

extern Str_array_point	huge arights[14];
extern char arights_grid;
extern unsigned long display_grp_time;
extern char *screen_right_tmp;
extern long rights_access_tmp;
extern Panel_info1 Panel_Info1;
extern char new_alarm_flag;

extern char GAlarm;

extern int fond_color;
extern int FONDCOLOR;
#define  BOXCOLOR  Cyan

extern int lat_char_n;
extern int lung_char_n;

enum {PROGR=0, OPERATOR=1 };

	union key {
		int i;
		char ch[2];
		} ;

#include <color.hpp>

extern Serial *ser_ptr;
//class GMenuBar;
extern GMenuBar G;
extern char *lin_text;

extern int on_screen;
extern int picture_write;

extern  char huge *grp_message[];
extern  char huge *graphic_grp_message[];

//extern char huge heap_grp[];
extern Panel *ptr_panel;
extern int  station_num;

extern char huge *lin_menu;
//extern int nofond;

extern int findroutingentry(int port, int network, int &j, int t=1);
extern int tif(char *argv,int x1, int x2, int y1,int y2);

extern void Border(int ltopx, int ltopy, int rbottomx, int rbottomy, int colour,int bcolour);
extern char *ltrim(char *text);
extern void msettextstyle(int font, int dir, int chars);
extern char *rtrim(char *text);

extern unsigned char tbl_bank[MAX_TBL_BANK];
extern Comm_Info *comm_info;
extern char huge connection_type_text[8][14];
extern char far com_buf[10][5];

extern void memsize(void);
extern char *lalign(char *buf, int n);
extern char *ralign(char *buf, int n);
extern void ftoa(float f, int length, int ndec, char *buf);
//int findlabel(int panel_type, Sub_a_b net_type, int panel,Point_main_sub point, char *buf);
//extern int findpoint(int panel_type,Sub_a_b net_type, int panel, Point_main_sub point,char *buf);
extern int look(char *buf,Point *point,int panel_type,Sub_a_b net_type,int panel,int sub_panel);
extern int pointtotext(char *buf,Point_Net *point);
extern int pointtotext(char *buf,Point_T3000 *point);
extern texttointerval( char *textbuffer,unsigned char *seconds , unsigned char *minutes , unsigned char *hours, char c = ':' );
extern char * intervaltotext(char *textbuf, long seconds , unsigned minutes , unsigned hours, char *c=":");
extern void Bordergr(int ltopx, int ltopy, int rbottomx, int rbottomy, int colour, int bkgnd, int bcolour,int butcol, int how, int out);
extern int print_alarm_word(void);
extern int checkport(int com, int t=0);
extern int net_call(int command, int arg,  char *data, uint *length , int dest,
				 int network, int others=0, int timeout=TIMEOUT_NETCALL,
				 char *returnargs=NULL, int *length_returnargs=NULL,
				 char *sendargs=NULL, int length_sendargs=0, char bytearg=0, int port=-1);
extern void select_panel(int type, int net_no, int where=0);

extern int GetRange_Out(int range);
extern int GetRange_In(int range);
extern int GetRange_Var(int range);

/* the ranges and units of the items used */

char huge *ack = "ACK";
extern char huge *blank3;
extern char huge *grp;
extern char huge *Main;
extern char huge *Mini;
extern char huge *Suba;
extern char huge *Subb;
extern char huge *man;
extern char huge *autom;
extern char huge *nulbuf;
extern char huge *yes;
extern char huge *Yes;
extern char huge *No;
extern char huge *lin;
extern char huge *on;
extern char huge *off;
extern char huge *colon;
extern char huge *zero;
extern char huge *enabl;
extern char huge *disabl;
extern char huge *snothing;

char huge *direct="Direct";
char huge *invers="Invers";
char huge *rights[4]={"View ","Edit ","NoAcc","Indiv"};
char huge *state_text[]={"Installed","Not Installed","Established"};
char huge *installed_text="Installed";
char huge *established_text="Active";
char huge *inactive_text="Inactive";

/*
enum tok_func	{
					ABS=0x32, TIME_ON=0x3C,TIME_OFF=0x3D,INT=0x36, INTERVAL=0x3E, LN=0x4D, LN_1=0x4E, SQR=0x39, Status=0x47,
					AVG=0x33, MAX=0x37, MIN=0x38, CONPROP=0x56, CONRATE=0x57, CONRESET=0x58, Tbl=0x3A, WR_ON=0x40, WR_OFF=0x41,
					DOM=0x52, DOW=0x35, DOY=0x34, POWER_LOSS=0x4C, SCANS=0x4B, TIME=0x3B, UNACK=0x42,
					};
*/

struct save_message {
		char type;
		int point;
		char cond_type;
		char count;
		char message[ALARM_MESSAGE_SIZE];
		long time;
		};

extern Str_tbl_point custom_tab[MAX_TABS];
int max_entry_array;
ulong *pactivepanels;
Station_point *pstation_list_sel, **pstation_list;
int network_select, network_sel_tmp;
int panel_select, panel_sel_tmp;
int setunreachabil=0;
//**********************************
//    class Alarm_block
//**********************************
Alarm_block::Alarm_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				 :Block(pthis, pt, p, net, type, pnum, N_ALARMM, (char *)&line_buf)
{
			pgrid = pthis;
			if(maxtbl)
			{
				 number_of_points=maxtbl;           //MAX_OUTPUT;
				 maxtbl = 0;
			}
			else
				number_of_points=tbl_bank[ALARMM];           //MAX_;
			set_semaphore_dos();
			block=new Alarm_point[number_of_points];
			clear_semaphore_dos();
			if( checklocal() )
			{
				memmove(block,&ptr_panel->alarms[0],number_of_points*sizeof(Alarm_point));
				for(int i=0; i<MAX_ALARMS ;i++)
					ptr_panel->alarms[i].change_flag = 0;
				sortalarm();
			}
			else
				memset(block,'\0',number_of_points*sizeof(Alarm_point));
			r.RecStruct(N_ALARMM,alarmm_struct);
			h.HSet(N_ALARMM,r.RecStruct(1),number_of_points);
}

Alarm_block::sortalarm()
{
 int i,j,t=0;
 char c;
 Alarm_point l;
/*
 for(int i=0;i<128;i++)
	 nrmes[i] = i;
*/
 for(j=0; j<number_of_points ;j++)
	if(!block[j].alarm)
		memset(&block[j],0,sizeof(Alarm_point));

 for(j=0; j<number_of_points ;j++)
	for(i=0; i<number_of_points-1 ;i++)
	 if( !block[i].alarm || block[i].ddelete)
	 {
		l = block[i];
		block[i] = block[i+1];
		block[i+1] = l;
//		t=1;

//		c=nrmes[i];
//		nrmes[i] = nrmes[i+1];
//		nrmes[i+1]=c;
	 }

 do {
	t=0;
	for(int i=0; i<number_of_points-1 ;i++)
	{
	 if( block[i].alarm_time < block[i+1].alarm_time)
	 {
		l = block[i];
		block[i] = block[i+1];
		block[i+1] = l;
		t=1;
//		c=nrmes[i];
//		nrmes[i] = nrmes[i+1];
//		nrmes[i+1]=c;
	 }
	}
 } while (t==1);
}

Alarm_block::~Alarm_block()
{
 set_semaphore_dos();
 delete block;
 clear_semaphore_dos();
}


int Alarm_block::savemessage(char count, char type, int point, char cond_type, char *mes, long time_mes)
{
}

int alarm_savemessage1(Alarm_point *palarm)
{
 FILE *h;
 char buf[100];
 set_semaphore_dos();
 if((h=fopen("ALARMS.MSG","r+b"))==NULL)
	 if((h=fopen("ALARMS.MSG","w+b"))==NULL)
		 {
			clear_semaphore_dos();
			return 1;
		 }
 fseek(h, 0, SEEK_END);
 if( ftell(h) > 20000 )
 {
	fclose(h);
	h=fopen("ALARMS.MSG","w+b");
 }
 fwrite(palarm,1, sizeof(Alarm_point),h);
 fclose(h);
 clear_semaphore_dos();
}


void update_alarm_tbl(Alarm_point *block, int max_points_bank )
{
 int i,j;
 char alarmtask=0;
 Alarm_point *ptr;

 ptr = ptr_panel->alarms;
 for( j=0; j<ptr_panel->table_bank[ALARMM]; ptr++, j++ )
 {
		if(	ptr->alarm )
		{
		 if( ptr->change_flag ) continue;
		 ptr->change_flag = 2;
		 for( i=0; i<max_points_bank;i++ )
		 {
			if(	block[i].alarm )
			{
			 if( ptr->no == block[i].no ) break;
			}
		 }
		 if( i>=max_points_bank )
		 {
			ptr->change_flag=0;
			continue;
		 }
		 if( block[i].ddelete )
		 {
/*
			if( !ptr->restored )
			{
				if(--ptr_panel->ind_alarms==0)
							GAlarm = 0;
			}
*/
///
			if( !ptr->restored && !ptr->acknowledged )
			{
				if(--ptr_panel->ind_alarms==0)
							GAlarm = 0;
			}
///
			ptr->alarm        = 0;
			ptr->change_flag  = 0;
			ptr->restored     = 0;
			ptr->acknowledged = 0;
			ptr->ddelete      = 1;
			ptr->original     = 0;
			if(ptr->alarm_panel==Station_NUM)
			{
							ptr->where_state1 = 0;
							ptr->where_state2 = 0;
							ptr->where_state3 = 0;
							ptr->where_state4 = 0;
							ptr->where_state5 = 0;
			}
			alarmtask |= 0x02;
			continue;
		 }
		 if( block[i].acknowledged )
		 {
			if( !ptr->acknowledged )
			{
///
				if( !ptr->restored )
				{
				 if(--ptr_panel->ind_alarms==0)
							GAlarm = 0;
				}
///
				ptr->acknowledged = 1;
				ptr->original     = 0;
				if(ptr->alarm_panel==Station_NUM)
				{
							ptr->where_state1 = 0;
							ptr->where_state2 = 0;
							ptr->where_state3 = 0;
							ptr->where_state4 = 0;
							ptr->where_state5 = 0;
				}
				alarmtask |= 0x01;
			}
		 }
		 ptr->change_flag=0;
		}
 }
 if( alarmtask )
 {
		 new_alarm_flag |= 0x01;  // send the alarm to the destination panels
		 if( alarmtask & 0x02 )
         new_alarm_flag |= 0x02;
		 resume(ALARMTASK);
 }
}
/*
int alarm_savemessage1(char count, char type, int point, char cond_type, char *mes, long time_mes)
{
 FILE *h;
 char buf[100];
 buf[0]=count;
 buf[1]=type;
 buf[2]=point;
 buf[3]=cond_type;
 memcpy(&buf[4],&time_mes,4);
 memcpy(&buf[8],mes,count-13);
 set_semaphore_dos();
 if((h=fopen("ALARMS.MSG","r+b"))==NULL)
	 if((h=fopen("ALARMS.MSG","w+b"))==NULL)
		 {
			clear_semaphore_dos();
			return 1;
		 }
 fseek(h, 0, SEEK_END);
 if( ftell(h) > 20000 )
 {
	fclose(h);
	h=fopen("ALARMS.MSG","w+b");
 }
 fwrite(buf,1,count,h);
 fclose(h);
 clear_semaphore_dos();
}
*/

int alarm_savemessage(Alarm_point *ptr, int number_of_points, int f=0)
{
  for(int i=0;i<number_of_points;i++)
	if( ptr[i].alarm && !ptr[i].ddelete )
//		alarm_savemessage1( ptr[i].alarm_count+13, TEMPERATURE, ptr[i].point, ptr[i].cond_type , ptr[i].alarm_message, ptr[i].alarm_time);
		alarm_savemessage1( ptr );

  if(f)
  {
	 for(i=0;i<number_of_points;i++)
			if(ptr[i].alarm)
			{
				 ptr[i].ddelete = 1;
				 if(!ptr[i].restored)
				 {
					if(--ptr_panel->ind_alarms==0)
					{
						GAlarm = 0;
						print_alarm_word();
					}
				 }
			 }

  }
  else
  {
	memset(ptr,'\0',number_of_points*sizeof(Alarm_point));
	ptr->alarm = 1;
	ptr->alarm_panel = Station_NUM;
	ptr->alarm_time = timesec1970+timestart;
	ptr->alarm_count = ALARM_MESSAGE_SIZE;
	ptr_panel->ind_alarms=1;
	strcpy(ptr->alarm_message,"    Alarm messages saved on disk! ");
	GAlarm = 0;
  }
}

int Alarm_block::Read(int field, char key)
{
 unsigned ax,bx,es;
 char buf[MAX_ALPHA+1],l;
 char *p;
 unsigned bytes=0;
 if(key==INSERT)
 {
 }
 else
	if(key==46)   //Alt-C
	{
		 alarm_savemessage(block, number_of_points,1);
/*
		 for(int i=0;i<number_of_points;i++)
			if((block+i)->alarm && !(block+i)->ddelete)
				alarm_savemessage((block+i)->alarm_count+13, TEMPERATURE, (block+i)->point, (block+i)->cond_type , (block+i)->alarm_message, (block+i)->alarm_time);
		 for(i=0;i<number_of_points;i++)
			if((block+i)->alarm)
			{
				(block+current_point)->ddelete = 1;
				 if(!(block+i)->restored)
				 {
					if(--ptr_panel->ind_alarms==0)
					{
						GAlarm = 0;
						print_alarm_word();
					}
				 }
			 }
*/
//		 GAlarm = 0;
//     ptr_panel->ind_alarms = 0;
		 pgrid->GSend();
		 memset(block,'\0',number_of_points*sizeof(Alarm_point));
		 pgrid->GGReDrawGrid();
	}
	else
	{
	 switch (field) {
		case ALARMM_NR:
		case ALARMM_PANEL:
		case ALARMM_MESSAGE:
						break;
		case ALARMM_ACK:
						if( (block+current_point)->alarm_time )
						{
						 l=(block+current_point)->acknowledged;
						 if (l==OFF)
						 {
							 strcpy(buf,ack);
							 l=ON;
							(block+current_point)->acknowledged=l;
							 PutAlpha(field, buf);
						 }
						}
						break;
		case ALARMM_RES:
						break;
		case ALARMM_DEL:
						if((block+current_point)->alarm)
						{
						 if(!(block+current_point)->ddelete)
						 {
//							alarm_savemessage1((block+current_point)->alarm_count+13, TEMPERATURE, (block+current_point)->point, (block+current_point)->cond_type , (block+current_point)->alarm_message, (block+current_point)->alarm_time);
							 alarm_savemessage1(block+current_point);
							 (block+current_point)->ddelete = 1;
//						 sortalarm();
//						 pgrid->GGReDrawGrid();
							 strcpy(buf,Yes);
							 PutAlpha(field, buf);
//							 if((block+current_point)->restored)
//									 (block+current_point)->alarm = 0;
//							 else
/*
							 if(!(block+current_point)->restored)
							 {
								if(--ptr_panel->ind_alarms==0)
								{
									GAlarm = 0;
									print_alarm_word();
								}
							 }
*/
						 }
						}
						break;
		case ALARMM_TIME:
						break;
		}
 pgrid->GGPutField(field,Lightgray,Black);
	}
}

int Alarm_block::GetRec(void)
{
	int i;

	memset(&line_buf,' ',sizeof(struct ALARMM_LineBuf));
	if (current_point+1 > number_of_points) return FX_EOF;

	for(i=0; i<fields_number; i++)
		{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
		}
}

int Alarm_block::GetField(int field, char *buf)
{
	char xbuf[15];   // used for itoa fcn
	int l;

	l=0;
	switch (field) {
		case ALARMM_NR:
/*
					 int i;
					 l=1;
					 for(i=0;i<bank;i++)
							l += tbl_bank[ALARMM];
					 memcpy(buf,ralign(itoa(l+current_point,xbuf,10),L_ALARMM_NR),L_ALARMM_NR);
*/
				 nr_point(buf);
				 break;
		case ALARMM_PANEL:
					 l = (block+current_point)->alarm_panel;
					 memcpy(buf,ralign(itoa(l,xbuf,10),L_ALARMM_PANEL),L_ALARMM_PANEL);
					l=L_ALARMM_PANEL;
					break;
		case ALARMM_MESSAGE:
					 char *p;
					 p=lalign((block+current_point)->alarm_message,L_ALARMM_MESSAGE);
					 memcpy(buf , p,L_ALARMM_MESSAGE);
					 l=L_ALARMM_MESSAGE;
				 break;
		case ALARMM_ACK:
						l=(block+current_point)->acknowledged;
						if (l==ON)
							 strcpy(buf,ack);
						else
							 strcpy(buf,blank3);
					 break;
		case ALARMM_RES:
						l=(block+current_point)->restored;
						if (l==ON)
						{
							 strcpy(buf,Yes);
						}
						break;
		case ALARMM_DEL:
						if( (block+current_point)->alarm_time )
						{
						 if(!(block+current_point)->ddelete)
							strcpy(buf,No);
						 else
							strcpy(buf,Yes);
						}
						else
							strcpy(buf,"  ");
						break;
		case ALARMM_TIME:
					 long t,dl;
					 t=(block+current_point)->alarm_time;
					 if(t)
					 {
						if(panel_type!=T3000)
						{
						 t += timezone;
//						 if ( daylight ) t -= 3600;
						}
						memcpy(buf, ctime(&t),L_ALARMM_TIME);
					 }
					 else
						memset(buf, ' ',L_ALARMM_TIME);
					 break;
		}
 return l;
}



//**********************************
//    class Alarm_set_point
//**********************************

Alarm_set_block::Alarm_set_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				 :Block(pthis, pt, p, net, type, pnum, N_ALARMS, (char *)&line_buf)
	 {
		 int npoint=0;
//			if(sp==INDIVIDUAL)
//			 {
//				number_of_points=1;           //MAX_OUTPUT;
//				npoint =  nt-1;                // num_point
//			 }
//			else
		 number_of_points=MAX_ALARMS_SET;           //MAX_;
		 set_semaphore_dos();
		 block=new Alarm_set_point[number_of_points];
		 clear_semaphore_dos();
//		 if((local_panel &&  type!=INDIVIDUAL) || (type==INDIVIDUAL && p==Station_NUM))
		 if( checklocal() )
				memmove(block,&ptr_panel->alarms_set[npoint],number_of_points*sizeof(Alarm_set_point));
		 else
				memset(block,'\0',number_of_points*sizeof(Alarm_set_point));
		 r.RecStruct(N_ALARMS,alarms_struct);
		 h.HSet(N_ALARMS,r.RecStruct(1),number_of_points);
	 }

Alarm_set_block::~Alarm_set_block()
{
 set_semaphore_dos();
 delete block;
 clear_semaphore_dos();
}

int Alarm_set_block::Read(int field, char key)
{
 unsigned ax,bx,es;
 char buf[MAX_ALPHA+1],l;
 char *p;
 unsigned bytes=0;
 if(key==DELETE)
 {
 }
 else
 if(key==INSERT)
		{
		}
	else
	{
//	if(current_point <= ind_alarms_set)
	{
	 switch (field) {
		case ALARMS_GATE:
		case ALARMS_POINT:
		case ALARMS_NORM:
					{
/*
					 Point_T3000 point;
					 byte num_point,var_type, point_type, num_panel;
					 if(field == ALARMS_GATE)
						 point=(block+current_point)->point1;
					 if(field == ALARMS_POINT)
						 point=(block+current_point)->point);
					 if(field == ALARMS_NORM)
						{
						 num_point = (block+current_point)->normal;
						 memcpy(&point,&num_point,2);
						}

						GetAlpha(field, MAX_ALPHA, buf);
						pgrid->GDGets(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
						if((p=ispoint(rtrim(buf),&num_point,&var_type, &point_type, &num_panel)) || !strlen(rtrim(buf)),panel)
//						look(buf,&point,panel_type,net_type,panel,sub_panel);
						{
						if(strlen(rtrim(buf)))
						{
						 strcpy(buf,p);
						 point.panel = num_panel-1;point.number = num_point-1;point.point_type = point_type+1;
						}
						else
						 point.panel = point.number = point.point_type = 0;

						ralign(lalign(buf,L_ALARMS_POINT),L_ALARMS_POINT);
						PutAlpha(field, buf);
						if(field == ALARMS_GATE)
							(block+current_point)->point1=point;
					 if(field == ALARMS_POINT)
							(block+current_point)->point=point;
					 if(field == ALARMS_NORM)
						 {
							memcpy(&num_point,&point,2);
							(block+current_point)->normal=num_point;
						 }
						}
*/
					 }
					 break;
		case ALARMS_COND:
						l=(block+current_point)->cond1;
						if (l==ON)
							 {
							 strcpy(buf,(char *)off);
							 l=OFF;
							 }
						else
							{
							 strcpy(buf,(char *)on);
							 l=ON;
							}
					 (block+current_point)->cond1=l;
					 PutAlpha(field, buf);
					 break;
		case ALARMS_WAYLOW:
		case ALARMS_LOW:
		case ALARMS_HI:
		case ALARMS_WAYHI:
//						float *pf;
						long *pf;
						switch (field) {
								case ALARMS_WAYLOW:
											pf = &(block+current_point)->waylow;
											break;
								case ALARMS_LOW:
											pf = &(block+current_point)->low;
											break;
								case ALARMS_NORM:
											pf = &(block+current_point)->normal;
											break;
								case ALARMS_HI:
											pf = &(block+current_point)->hi;
											break;
								case ALARMS_WAYHI:
											pf = &(block+current_point)->wayhi;
											break;
						}
						GetAlpha(field, MAX_ALPHA, buf);
						pgrid->GDGets(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
						PutAlpha(field, buf);
						*pf=(long)(atof(buf)*1000);
						break;

		case ALARMS_TIME:
					 int sec,min,hours;
						long l;
						hours =  (block+current_point)->time/18.2/3600;
						l = (block+current_point)->time/18.2 - hours*3600;
						min = l/60;
						sec = (l-min*60);
					 readinterval(field, buf, (long *)&sec ,&min,&hours);
					 (block+current_point)->time = (sec+min*60+hours*3600)*18.2;
					 PutAlpha(field, buf);
					 break;
			}
	 pgrid->GGPutField(field,Lightgray,Black);
//	 if(current_point == ind_alarms_set && (block+current_point)->point)
//		ind_alarms_set++;
	}
 }
}


int Alarm_set_block::GetRec(void)
{
	int i ;

	memset(&line_buf,' ',sizeof(struct ALARMS_LineBuf));
	if (current_point+1 > number_of_points) return(FX_EOF);
	for(i=0; i<fields_number; i++)
		{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
		}
}

int Alarm_set_block::GetField(int field, char *buf)
{
	char xbuf[15];   // used for itoa fcn
	int l;

	l=0;
	switch (field) {
		case ALARMS_GATE:
		case ALARMS_POINT:
		case ALARMS_NORM:
					{
/*
					 Point_T3000 point;
					 int num_point,var_type, point_type, num_panel;
					 char *p;
					 if(field == ALARMS_GATE)
						 memcpy(&point,&(block+current_point)->point1,2);
					 else
						 memcpy(&point,&(block+current_point)->point,2);
					 if(field == ALARMS_NORM)
						{
						 num_point = (block+current_point)->normal;
						 memcpy(&point,&num_point,2);
						}

					 if (!pointtotext(buf,&point,STANDARD))
					 {
						p=ispoint(rtrim(buf),&num_point,&var_type, &point_type, &num_panel,panel);
						strcpy(buf,p);
						ralign(lalign(buf,L_ALARMS_POINT),L_ALARMS_POINT);
					 }
					 else
							 memcpy(buf,snothing,8);

					 l=L_ALARMS_POINT;
*/
					}
					 break;
		case ALARMS_COND:
						l=(block+current_point)->cond1;
						if (l==OFF)
							 strcpy(buf,off);
						else
							 strcpy(buf,on);
					 break;
		case ALARMS_WAYLOW:
		case ALARMS_LOW:
		case ALARMS_HI:
		case ALARMS_WAYHI:
//						float value;
						long value;
						switch (field) {
								case ALARMS_WAYLOW:
											value = (block+current_point)->waylow;
											break;
								case ALARMS_LOW:
											value = (block+current_point)->low;
											break;
								case ALARMS_NORM:
											value = (block+current_point)->normal;
											break;
								case ALARMS_HI:
											value = (block+current_point)->hi;
											break;
								case ALARMS_WAYHI:
											value = (block+current_point)->wayhi;
											break;
						}
						ftoa((float)value/1000,L_ALARMS_WAYLOW , 1, buf);
						break;
		case ALARMS_TIME:
						int sec,min,hours;
						long l;
						hours =  (block+current_point)->time/18.2/3600;
						l = (block+current_point)->time/18.2 - hours*3600;
						min = l/60;
						sec = (l-min*60);
						memcpy(buf,intervaltotext( NULL, (long)sec , min, hours),8);
						break;
		}
 return l;
}



int Display_alarm(int ind_mes)
{
 char *file;
 char drv[3],dr[40],nm[9],ex[5],
			drv1[3],dr1[40],nm1[9],ex1[5];
 int col;

/*
 _BH = 5*8+4;
 _BL = Green;
 asm{
	mov ah,10h
	mov al,0
//	mov bl,i       //registrul
//	mov bh,n
	int 10h
 }
*/
 GWindow D(4,9,74,14,NO_STACK,0);

 D.GWSet("Alarm message",Lightgray,Red);

 D.GShowWindow(DIALOG);

 time_t t;
 time(&t);
 char buf[50];
 strcpy(buf,ctime(&t));
 D.GWPuts(2,43,buf, Lightgray, Black);
 Bordergr(7, 10, 16, 12, White, Red, Lightgray, White, 4, 1);
 D.GWPuts(1,4,"Ignore",Red, Black);

 Bordergr(19, 10, 34, 12, White, Darkgray, Lightgray, White, 4, 1);
 D.GWPuts(1,16,"Acknowledged",Darkgray, White);

 Bordergr(37, 10, 46, 12, White, Darkgray, Lightgray, White, 4, 1);
 D.GWPuts(1,34,"Delete",Darkgray,White);
 lin_text[ALARM_MESSAGE_SIZE]=0;
 D.GWPuts(3,0,lin_text,Darkgray,Red);
 lin_text[ALARM_MESSAGE_SIZE]=lin_text[0];
 D.GWPuts(3,0,(char *)ptr_panel->alarms[ind_mes].alarm_message,Darkgray,White);
 while(!D.HandleEvent());

/*
 _BH = 1*8+3;
 _BL = Green;
 asm{
	mov ah,10h
	mov al,0
	int 10h
 }
*/

};



//**********************************
//    class Units_block
//**********************************

Units_block::Units_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				 :Block(pthis, pt, p, net, type, pnum, N_UNITS, (char *)&line_buf)
	 {
		 int npoint=0;
//			if(sp==INDIVIDUAL)
//			 {
//				number_of_points=1;           //MAX_OUTPUT;
//				npoint =  nt-1;                // num_point
//			 }
//			else
		 number_of_points=MAX_UNITS;           //MAX_;
		 set_semaphore_dos();
		 block=new Units_element[number_of_points];
		 clear_semaphore_dos();
//		 if((local_panel &&  type!=INDIVIDUAL) || (type==INDIVIDUAL && p==Station_NUM))
		 if( checklocal() )
				memmove(block,&ptr_panel->units[npoint],number_of_points*sizeof(Units_element));
		 else
				memset(block,'\0',number_of_points*sizeof(Units_element));
		 r.RecStruct(N_UNITS,units_struct);
		 h.HSet(N_UNITS,r.RecStruct(1),number_of_points);
	 }

Units_block::~Units_block()
{
 set_semaphore_dos();
 delete block;
 clear_semaphore_dos();
}

int Units_block::Read(int field, char key)
{
 unsigned ax,bx,es;
 char buf[MAX_ALPHA+1],l;
 char *p;
 unsigned bytes=0;
 switch (field) {
		case UNITS_NUM:
					 break;
		case UNITS_NORMAL:
					char l;
					if (!(block+current_point)->direct)
					{
					 strcpy(buf,(char *)invers);
					 l=1;
					}
					else
					{
					 strcpy(buf,(char *)direct);
					 l=0;
					}
					(block+current_point)->direct = l;
//					 getalpha(field, (block+current_point)->analog_units, L_UNITS_ANALOG);
					 break;
		case UNITS_DIGON:
					 getalpha(field, (block+current_point)->digital_units_on, L_UNITS_DIGON);
					 break;
		case UNITS_DIGOFF:
					 getalpha(field, (block+current_point)->digital_units_off, L_UNITS_DIGOFF);
					 break;
	}
	pgrid->GGPutField(field,Lightgray,Black);
}


int Units_block::GetRec(void)
{
	int i ;

	memset(&line_buf,' ',sizeof(struct UNITS_LineBuf));
	if (current_point+1 > number_of_points) return(FX_EOF);
	for(i=0; i<fields_number; i++)
		{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
		}
}

int Units_block::GetField(int field, char *buf)
{
	char xbuf[15];   // used for itoa fcn
	int l;

	l=0;
	switch (field) {
		case UNITS_NUM:
				 memcpy(buf,ralign(itoa(current_point+1,xbuf,10),L_UNITS_NUM),L_UNITS_NUM);
				 break;
		case UNITS_NORMAL:
					if (!(block+current_point)->direct)
					{
					 strcpy(buf,(char *)direct);
					}
					else
					{
					 strcpy(buf,(char *)invers);
					}
//				 memcpy(buf , lalign((block+current_point)->analog_units,L_UNITS_ANALOG),L_UNITS_ANALOG);
				 l=L_UNITS_NORMAL;
				 break;
		case UNITS_DIGON:
				 memcpy(buf , lalign((block+current_point)->digital_units_on,L_UNITS_DIGON),L_UNITS_DIGON);
				 l=L_UNITS_DIGON;
				 break;
		case UNITS_DIGOFF:
				 memcpy(buf , lalign((block+current_point)->digital_units_off,L_UNITS_DIGOFF),L_UNITS_DIGOFF);
				 l=L_UNITS_DIGOFF;
				 break;
		}
 return l;
}


//**********************************
//    class Tbl_block
//**********************************

Tbl_block::Tbl_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				 :Block(pthis, pt, p, net, type, pnum, N_TBL, (char *)&line_buf)
	 {
		 int npoint=0;
		 number_of_points=16;           //MAX_TBLPUT;
		 tblno = pnum;
		 set_semaphore_dos();
		 block=new Str_tbl_point;
		 clear_semaphore_dos();
//		 if((local_panel &&  type!=INDIVIDUAL) || (type==INDIVIDUAL && p==Station_NUM))
     	 if( checklocal() )
			memmove(block, &custom_tab[tblno-1], sizeof(Str_tbl_point));
		 else
			memset(block,'\0', sizeof(Str_tbl_point));
		 r.RecStruct(N_TBL,tbl_struct);
		 h.HSet(N_TBL,r.RecStruct(1),number_of_points);
	 }

Tbl_block::~Tbl_block()
{
 set_semaphore_dos();
 delete block;
 clear_semaphore_dos();
}

int Tbl_block::Read(int field, char key)
{
 char buf[50],l;
 switch (field) {
		case TBL_VALUE1:
						 long f;
						 readfloat(field, &f, L_TBL_VALUE1, 2, NULL,2, 0, 5.00);
						 block->table[current_point].value=(int)( (float)f/(float)1000 * 4096 / 5 + 0.5);
						 break;
		case TBL_UNIT1:
						 readfloat(field, &block->table[current_point].unit, L_TBL_UNIT1, 2, NULL,1);
						 break;
		}
 pgrid->GGPutField(field,Lightgray,Black);
}


int Tbl_block::GetRec(void)
{
	int i;
	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,'\0',sizeof(struct TBL_LineBuf));

	for(i=0; i<fields_number; i++)
		{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
		}
}

int Tbl_block::GetField(int field, char *buf)
{
	char xbuf[15];   // used for itoa fcn
	int l;

	l=0;
	switch (field) {
		case TBL_VALUE1:
						 long f;
						 f = ((float)block->table[current_point].value*5./4096.)*1000+0.5;
						 readfloat(field, &f, L_TBL_VALUE1, 2, buf, 0);
						 break;
		case TBL_UNIT1:
						 readfloat(field, &block->table[current_point].unit, L_TBL_UNIT1, 2, buf, 0);
						 break;
		}
 return l;
}


//**********************************
//    class Ays_block
//**********************************

Array_block::Array_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				 :Block(pthis, pt, p, net, type, pnum, N_AY, (char *)&line_buf)
	 {
 asm push es;
		 int npoint=0;
//			if(sp==INDIVIDUAL)
//			 {
//				number_of_points=1;           //MAX_OUTPUT;
//				npoint =  nt-1;                // num_point
//			 }
//			else
		 if(arights_grid == 0)
		 {
			if(maxtbl)
			{
				 number_of_points=maxtbl;           //MAX_OUTPUT;
				 maxtbl = 0;
			}
			else
			 number_of_points=tbl_bank[AY];           //MAX_OUTPUT;
		 }
		 if(arights_grid == 1)
			 number_of_points=AY+1+2;           //MAX_OUTPUT;
		 if(arights_grid == 2)
			 number_of_points=tbl_bank[GRP];           //MAX_OUTPUT;
		 set_semaphore_dos();
		 block=new Str_array_point[number_of_points];
		 clear_semaphore_dos();
		 if(arights_grid == 0)
		 {
//			if((local_panel &&  type!=INDIVIDUAL) || (type==INDIVIDUAL && p==Station_NUM))
			if( checklocal() )
				memmove(block,&ptr_panel->arrays[npoint],number_of_points*sizeof(Str_array_point));
			else
				memset(block,'\0',number_of_points*sizeof(Str_array_point));
		 }
		 if(arights_grid == 1)
		 {
			memmove(block,arights,number_of_points*sizeof(Str_array_point));
			for(int i=0; i<number_of_points; i++)
			{
			 (block+i)->length = (rights_access_tmp>>(i*2L))&0x03;
			}
		 }
		 if(arights_grid == 2)
		 {
			for(int i=0; i<number_of_points; i++)
			{
			 strcpy((block+i)->label,ptr_panel->control_groups[i].label);
			 (block+i)->length = (screen_right_tmp[i*2/8]>>((i*2)%8))&0x03;
			}
		 }

		 if(arights_grid == 0)
			 r.RecStruct(N_AY,ay_struct);
		 else
			 r.RecStruct(N_AY,arights_struct);

		 h.HSet(N_AY,r.RecStruct(1),number_of_points);
 asm pop es;
	 }

Array_block::~Array_block()
{
 set_semaphore_dos();
 delete block;
 clear_semaphore_dos();
}

int Array_block::Read(int field, char key)
{
 asm push es;
// unsigned ax,bx,es;
// char buf[MAX_ALPHA+1],l;
// unsigned bytes=0;
 if(key==INSERT)
 {
	if(arights_grid == 0)
	{
	 max_entry_array = (block+current_point)->length;
//	GGrid *p;
	 int ny = 16;
	 if(max_entry_array < 16) ny = max_entry_array;
//	set_semaphore_dos();
//	p=new GGrid(43,6,63,6+ny+2,GRID,NULL,AYVALUE,STANDARD,panel,sub_panel,current_point+1);
//	clear_semaphore_dos();
	 GGrid *p=NULL;
	 p = new GGrid(43,6,63,6+ny+2,GRID,NULL,AYVALUE,T3000,panel,network,type,current_point+1);
	 if(!p->grid_error)
	 {
	  p->GWSet(NULL,Lightgray,Darkgray);
	  p->GShowGrid();
	  while (!p->HandleEvent());
//	set_semaphore_dos();
//	delete p;
//	clear_semaphore_dos();
	 }
	 if(p) delete p;
	}
	else
	{
	 if(arights_grid == 1 && (block+current_point)->length==3)
	 {
		arights_grid = 2;
		GGrid p1(30,6,55,6+16+2,GRID,NULL,AY,STANDARD,0,0,0);
		p1.GWSet("Screen rights",Lightgray,Darkgray);
		p1.GShowGrid();
		while (!p1.HandleEvent());
		arights_grid = 1;
	 }
	}
 }
 else
 {
	switch (field) {
		case AY_NUM:
					 break;
		case AY_LABEL:
					 if(arights_grid == 0)
						 getalpha(field, (block+current_point)->label, L_AY_LABEL);
					 break;
		case AY_LENGTH:
						 int v;
						 v=(int)(block+current_point)->length;
						 if(arights_grid == 0)
							 readint(field, &v,  L_AY_LENGTH, NULL, 2, 0, 255);
						 else
						 {
							v++;
							if(v>3) v=0;
							if(arights_grid == 1 && current_point!=GRP && v>2) v=0;
							if(arights_grid == 2 && v>2) v=0;
//							strcpy(buf, rights[v]);
							PutAlpha(field, rights[v]);
						 }
						 if( arights_grid == 2 )
						 {
							 screen_right_tmp[current_point*2/8] &= ~(0x03<<((current_point*2)%8));
							 screen_right_tmp[current_point*2/8] |= v<<((current_point*2)%8);
						 }
						 if( arights_grid == 1 )
						 {
							 rights_access_tmp &=  (~( (long)3<<(current_point*2L)));
							 rights_access_tmp |= ( (long)v<<(current_point*2L));
						 }
						 (block+current_point)->length = (char)v;
						 break;
	}
	pgrid->GGPutField(field,Lightgray,Black);
   pgrid->modify = TRUE;
 }
 asm pop es;
}


int Array_block::GetRec(void)
{
	int i ;

	memset(&line_buf,' ',sizeof(struct AY_LineBuf));
	if (current_point+1 > number_of_points) return(FX_EOF);
	for(i=0; i<fields_number; i++)
		{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
		}
}

int Array_block::GetField(int field, char *buf)
{
 asm push es;
	char xbuf[15];   // used for itoa fcn
	int l;

	l=0;
	switch (field) {
		case AY_NUM:
				 memcpy(buf,ralign(itoa(current_point+1,xbuf,10),L_AY_NUM),L_AY_NUM);
				 break;
		case AY_LABEL:
					 char *p;
					 p=lalign((block+current_point)->label,L_AY_LABEL);
					 memcpy(buf , p,L_AY_LABEL);
					 l=L_AY_LABEL;
					 break;
		case AY_LENGTH:
						 int v;
						 v=(int)(block+current_point)->length;
						 if(arights_grid == 0)
						 {
							readint(field, &v,  L_AY_LENGTH, buf, 0);
						 }
						 else
						 {
							strcpy(buf, rights[v]);
						 }
							break;
		}
 asm pop es;
 return l;
}


//**********************************
//    class Ayvalue_block
//**********************************

Ayvalue_block::Ayvalue_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				 :Block(pthis, pt, p, net, type, pnum, N_AYVALUE, (char *)&line_buf)
	 {
 asm push es;
		 current_array = pnum-1;
		 number_of_points = max_entry_array;           //MAX_OUTPUT;
		 set_semaphore_dos();
		 block=new Str_ayvalue_point[number_of_points];
		 clear_semaphore_dos();
//		 if((local_panel &&  type!=INDIVIDUAL) || (type==INDIVIDUAL && p==Station_NUM))
		 if( checklocal() )
				memmove(block,ptr_panel->arrays_data[current_array],number_of_points*sizeof(Str_ayvalue_point));
		 else
				memset(block,'\0',number_of_points*sizeof(Str_ayvalue_point));
		 r.RecStruct(N_AYVALUE,ayvalue_struct);
		 h.HSet(N_AYVALUE,r.RecStruct(1),number_of_points);
 asm pop es;
	 }

Ayvalue_block::~Ayvalue_block()
{
 set_semaphore_dos();
 delete block;
 clear_semaphore_dos();
}

int Ayvalue_block::Read(int field, char key)
{
}

int Ayvalue_block::GetRec(void)
{
	int i ;

	memset(&line_buf,' ',sizeof(struct AYvalue_LineBuf));
	if (current_point+1 > number_of_points) return(FX_EOF);
	for(i=0; i<fields_number; i++)
		{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
		}
}

int Ayvalue_block::GetField(int field, char *buf)
{
	char xbuf[15];   // used for itoa fcn
	int l;

 asm push es;
	l=0;
	switch (field) {
		case AYVALUE_NUM:
				 memcpy(buf,ralign(itoa(current_point+1,xbuf,10),L_AYVALUE_NUM),L_AYVALUE_NUM);
				 break;
		case AYVALUE_VALUE:
				 readfloat(field, &(block+current_point)->value, L_AYVALUE_VALUE, 1, buf,0);
				 break;
		}
 asm pop es;
 return l;
}

//**********************************
//    class Connect_com_block
//**********************************

Connect_com_block::Connect_com_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				 :Block(pthis, pt, p, net, type, pnum, N_COM, (char *)&line_buf)
	 {
		 pgrid = pthis;
		 number_of_points=4;
		 set_semaphore_dos();
		 block=new Comm_Info [MAX_COMM_INFO];
		 clear_semaphore_dos();
//		 if((local_panel &&  type!=INDIVIDUAL) || (type==INDIVIDUAL && p==Station_NUM))
//		 if( checklocal() )
			memmove(block, comm_info, MAX_COMM_INFO*sizeof(Comm_Info));
//		 else
//			memset(block,'\0', MAX_COMM_INFO*sizeof(Comm_Info));
		 r.RecStruct(N_COM,com_struct);
		 h.HSet(N_COM,r.RecStruct(1),number_of_points);
	 }

Connect_com_block::~Connect_com_block()
{
 set_semaphore_dos();
 delete block;
 clear_semaphore_dos();
}

int Connect_com_block::Read(int field, char key)
{
}

int Connect_com_block::GetRec(void)
{
	int i ;
	memset(&line_buf,' ',sizeof(struct COM_LineBuf));
	if (current_point+1 > number_of_points) return(FX_EOF);
	for(i=0; i<fields_number; i++)
		{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
		}
}

int Connect_com_block::GetField(int field, char *buf)
{
	char xbuf[15];   // used for itoa fcn
	int l;

 asm push es;
	l=0;
	switch (field) {
		case COM_CONNECT:
				 strcpy(buf,connection_type_text[(block+current_point)->connection]);
				 ralign(buf,L_COM_CONNECT);
				 break;
		case COM_PORT:
				 strcpy(buf,com_buf[current_point+1]);
				 ralign(buf,L_COM_PORT);
				 break;
		case COM_STATE:
				 if( !((block+current_point)->connection) )
				 {
					strcpy(buf,connection_type_text[0]);
				 }
				 else
				 {
					strcpy(buf,installed_text);
				  if ( (l=checkport((block+current_point)->port_name, 1)) >= 0 )
				  {
					if( (Routing_table[l].status&PTP_ACTIVE)==PTP_ACTIVE ||
						(Routing_table[l].status&RS485_ACTIVE)==RS485_ACTIVE )
					{
					 strcat(buf,",");
					 strcat(buf,established_text);
					}
					else
					{
					 strcat(buf,",");
					 strcat(buf,inactive_text);
					}
              }
				 }
				 break;
		}
 asm pop es;
 return l;
}

//**********************************
//    class Net_block
//**********************************

Net_block::Net_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				 :Block(pthis, pt, p, net, type, pnum, N_NET, (char *)&line_buf)
	 {
		 Panel_info1 panel_info;
		 int i,j,k,l,m,n,n1,n2,dupl,k1;
		 pgrid = pthis;
		 number_of_points=32;
		 set_semaphore_dos();
		 block= new Net_point[number_of_points];
		 pstation_list = new Station_point *[32];
		 clear_semaphore_dos();
		 memset(block,'\0', number_of_points*sizeof(Net_point));
		 memset(activepanels,'\0',sizeof(activepanels));
		 m = 0;
		 memset(pstation_list, 0, 32 * sizeof(Station_point *));
//		 if((local_panel &&  type!=INDIVIDUAL) || (type==INDIVIDUAL && p==Station_NUM))
		 j=0;
		 for(i=0; i<MAX_Routing_table; i++)
		 {
			if( (Routing_table[i].status&PORT_ACTIVE)==PORT_ACTIVE )
			{
			 if( !ser_ptr || ( ser_ptr && ((i==ser_ptr->port_number) || Routing_table[i].Port.network!=Routing_table[ser_ptr->port_number].Port.network)) )
			 {
				k =  Routing_table[i].Port.network;
				for(k1=0;k1<j;k1++)
				{
					if( (block+k1)->net_no == k ) break;
				}
				if(k1>=j)
				{
				 (block+j)->net_no = k;
				 if( (Routing_table[i].status&PTP_ACTIVE)==PTP_ACTIVE )
					(block+j)->net_con = ((class PTP *)Routing_table[i].ptr)->media;
				 else
				 {
					if( (Routing_table[i].status&RS485_ACTIVE)==RS485_ACTIVE )
					 (block+j)->net_con = ((class MSTP *)Routing_table[i].ptr)->media;
					else
					 (block+j)->net_con = ((class IPX *)Routing_table[i].ptr)->media;
				 }

				 if( k==networkaddress ) record_select = j+1;
//				if( k==NetworkAddress ) m = k;
				 if( (block+j)->net_con==RS485_LINK || (block+j)->net_con==IPX_LINK )
				 {
//			  m = k;
					memcpy((block+j)->net_name,((class ConnectionData *)Routing_table[i].ptr)->panel_info1.network_name,NAME_SIZE);
					activepanels[j]=((class ConnectionData *)Routing_table[i].ptr)->panel_info1.active_panels;
					*(pstation_list+j)=&(((class ConnectionData *)Routing_table[i].ptr)->station_list[0]);
				  j++;
				 }
				 else
					if (net_call(COMMAND_50, PANEL_INFO1_COMMAND, (char*)&panel_info, 0,  Routing_table[i].Port.address, k)==RS232_SUCCESS )
					{
					 memcpy((block+j)->net_name,panel_info.network_name,NAME_SIZE);
					 activepanels[j]=panel_info.active_panels;
					 if(activepanels[j])
						 j++;
					}
				}
			 }
			 for(l=0; l<MAX_reachable_networks; l++)
				if( Routing_table[i].Port.networks_list[l].status == REACHABLE )
				{
				 k = Routing_table[i].Port.networks_list[l].network;
				 if( ser_ptr )
					if( k==(( class ConnectionData *)Routing_table[ser_ptr->port_number].ptr)->panel_info1.network ) break;
				 (block+j)->net_no = k;
				 if( (Routing_table[i].status&PTP_ACTIVE)==PTP_ACTIVE )
					(block+j)->net_con = ((class PTP *)Routing_table[i].ptr)->media;
				 else
				 {
					if( (Routing_table[i].status&RS485_ACTIVE)==RS485_ACTIVE )
						(block+j)->net_con = ((class MSTP *)Routing_table[i].ptr)->media;
					else
						(block+j)->net_con = ((class IPX *)Routing_table[i].ptr)->media;
				 }

				 dupl=0;
				 for(k1=0;k1<j;k1++)
				 {
						if( (block+k1)->net_no == k ) break;
				 }
				 if(k1<j)
				 {
						dupl=1;
				 }

				 if(!dupl)
				 {
					memset((block+j)->net_name,' ',NAME_SIZE);
					n = Routing_table[i].Port.networks_list[l].half_router_address;
					if (net_call(COMMAND_50, PANEL_INFO1_COMMAND, (char*)&panel_info, 0, n?n:Routing_table[i].Port.networks_list[l].router_address, k)==RS232_SUCCESS )
					{
					 memcpy((block+j)->net_name,panel_info.network_name,NAME_SIZE);
					 activepanels[j]=panel_info.active_panels;
					}
					if( setunreachabil )
					{

					 for(k1=0; k1<MAX_Routing_table; k1++)
					 {
						 if( Routing_table[k1].Port.network==k )
						 {
							 if( (Routing_table[k1].status&RS485_ACTIVE)==RS485_ACTIVE || (Routing_table[k1].status&IPX_ACTIVE)==IPX_ACTIVE )
							 {
								if( (Routing_table[k1].status&RS485_ACTIVE)==RS485_ACTIVE )
								 (block+j)->net_con = ((class MSTP *)Routing_table[k1].ptr)->media;
								else
								 (block+j)->net_con = ((class IPX *)Routing_table[k1].ptr)->media;

								if( k==networkaddress ) record_select = j+1;
								memcpy((block+j)->net_name,((class ConnectionData *)Routing_table[k1].ptr)->panel_info1.network_name,NAME_SIZE);
								activepanels[j]=((class ConnectionData *)Routing_table[k1].ptr)->panel_info1.active_panels;
								*(pstation_list+j)=&(((class ConnectionData *)Routing_table[k1].ptr)->station_list[0]);
								break;
							 }
						 }
					 }
					 if(k1>=MAX_Routing_table) j--;
					 setunreachabil=0;
					}
					if( activepanels[j] )
						j++;
				 }
				}
			}
/*
			if(!m)
			{
			 m = j;
			 (block+j)->net_no = NetworkAddress;
//			 (block+j)->net_con = ((Serial*)Routing_table[i].ptr)->media;
				memcpy((block+j)->net_name,Panel_Info1.network_name,NAME_SIZE);
				activepanels[j]=Panel_Info1.active_panels;
			}
*/
		 }
		 for(k1=0;k1<j;k1++)
		 {
				if( (block+k1)->net_no == NetworkAddress ) break;
		 }
		 if(k1>=j)
		 {
			 (block+j)->net_no = NetworkAddress;
				(block+j)->net_con=RS485_LINK;
				memcpy((block+j)->net_name,Panel_Info1.network_name,NAME_SIZE);
				activepanels[j]=Panel_Info1.active_panels;
		 }
		 r.RecStruct(N_NET,net_struct);
		 h.HSet(N_NET,r.RecStruct(1),number_of_points);
		 network_select = network_sel_tmp = networkaddress;
		 panel_select   = station_num;
}

Net_block::~Net_block()
{
 set_semaphore_dos();
 delete block;
 if(pstation_list)
	 delete pstation_list;
 clear_semaphore_dos();
}

int Net_block::Read(int field, char key)
{
 int i;
 if(key==INSERT || key==ENTER || key=='\t')
 {
	if( (block+current_point)->net_con )
  {
	network_sel_tmp = (block+current_point)->net_no;
	i = pgrid->w_record;
	pgrid->w_record = record_select;
	pgrid->GGPutRecord(pgrid->w_urecord+record_select-1,pgrid->bkgcolour,Black);
	pgrid->w_record = i;
	pgrid->GGPutRecord(pgrid->w_urecord+pgrid->w_record-1,pgrid->bkgcolour,Lightred);
	if ( network_sel_tmp==network_select )
		panel_sel_tmp = panel_select;
	else
		panel_sel_tmp = 0;

	select_panel(CSTATION, (block+current_point)->net_no);
	if(panel_sel_tmp)
	{
		network_select = network_sel_tmp;
		panel_select   = panel_sel_tmp;
		record_select  = current_point+1;
	}
	else
	{
		network_sel_tmp = network_select;
	}
	}
 }
}

int Net_block::GetRec(void)
{
	int i ;
	memset(&line_buf,' ',sizeof(struct NET_LineBuf));
	if (current_point+1 > number_of_points) return(FX_EOF);
	for(i=0; i<fields_number; i++)
	{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
	}

//	memcpy(amon_inputs,(block+current_point)->inputs,sizeof(amon_inputs));
//	if(display_amons==1)
//	 display_amons=2;
//	if(display_amons==0 || display_amons==2)
	{
	 pactivepanels = &activepanels[current_point];
	 pstation_list_sel = pstation_list[current_point];
	 if( (block+current_point)->net_no )
	 {
		if ( (block+current_point)->net_no==network_select )
			panel_sel_tmp = panel_select;
		else
			panel_sel_tmp = 0;
		GGrid p(50,5,75,5+16+2,GRID,NULL,CSTATION,ptr_panel->GlPanel_type,ptr_panel->GlPanel,(block+current_point)->net_no);
//	 GGrid p(64,3,73,3+16+2,GRID,NULL,AMON_INPUTS,current_point+1,panel,network,type,(block+current_point)->anum_inputs);
		p.save=0;
		p.GWSet("Panels List",Lightgray,Darkgray);
//	 nofond=1;
		p.GShowGrid();
//	 nofond=0;
		p.GGHideCur(Black);
	  p.GReleaseWindow();
//	 if(display_amons==2)
//		display_amons=3;
	 }
	}
	if( (block+current_point)->net_no==network_sel_tmp )
	{
	 pgrid->fground=Lightred;
	}
	return FX_SUCCESS;
}

int Net_block::GetField(int field, char *buf)
{
	char xbuf[15];   // used for itoa fcn
	int l;

 asm push es;
	l=0;
	switch (field) {
		case NET_NO:
				 buf[0]=0;
				 if( (block+current_point)->net_no )
				 {
					itoa((block+current_point)->net_no,buf,10);
				 }
				 ralign(buf,L_NET_NO);
				 break;
		case NET_NAME:
				 memcpy(buf, (block+current_point)->net_name, L_NET_NAME);
				 break;
		case NET_CON:
				 if((block+current_point)->net_con)
				 {
					 strcpy(buf,connection_type_text[(block+current_point)->net_con]);
					 ralign(buf,L_NET_CON);
             }
				 else
					 memset(buf, ' ', L_NET_CON);
				 break;
		}
 asm pop es;
 return l;
}


//**********************************
//    class Dial_list_block
//**********************************
/*

Dial_list_block::Dial_list_block(GGrid *pthis, int pt, int p, int sp, Sub_a_b nt, byte b)
										:Block(pthis, pt, p, sp, nt, b, N_PRG, (char *)&line_buf)
{
	number_of_points=MAX_LIST;           //;
	set_semaphore_dos();
	block = new Dial_list_point[number_of_points];
	clear_semaphore_dos();
	if(local_panel)
	else
		memset(block,'\0',number_of_points*sizeof(Str_program_point));
	r.RecStruct(N_PRG,prg_struct);
	h.HSet(N_PRG,r.RecStruct(1),number_of_points);
}

Dial_list_block::~Dial_list_block()
{
	set_semaphore_dos();
	delete block;
	clear_semaphore_dos();
}



int Dial_list_block::Read(int field, GGrid *pthis,char key)
{
 unsigned ax,bx,es;
 char buf[50],l;
 char *p;
 unsigned bytes=0;
 if(key==INSERT)
		{
//		 ptrprg=this;
		 ptrprg=block+current_point;
		 current_point_prg = current_point;
		 int old_mode=MODE_TEXT;
		 if(!mode_text)
			{
//			 save_screen(&screen);
//			 G.HideMBar();
			 old_mode=mode_text;
			 ptr_panel->go_text();
			}
		 pgrid->modify = FALSE;
		 if(old_mode==MODE_GRAPHIC)
			{
			 ptr_panel->go_graphic();
			 mode_text = MODE_GRAPHIC;
//			 G.DisplayMBar();
			 int old_rec=pgrid->w_record;
			 int old_field=pgrid->w_field;
//				pgrid->w_nfields = 0;
//				pgrid->w_field = 1;
//				pgrid->t_fields[pgrid->w_field-1]=1;
				pgrid->RestoreArea();
				pgrid->on_screen=0;
				pgrid->GShowGrid();
				pgrid->GGHideCur(Black);
				pgrid->w_record = old_rec;
				pgrid->w_field = old_field;
//			 restore_screen(screen);
			}
		}
	else
	{
		switch (field)
		{
			case DIAL_SYSTEM_NAME:
				 getalpha(field, (block+current_point)->system_name, L_DIAL_SYSTEM_NAME );
				 break;
			case DIAL_PHONE_NUMBER:
				 getalpha(field, (block+current_point)->phone_number, L_DIAL_PHONE_NUMBER );
				 break;
			case DIAL_DESCRIPTOR_FILE:
				 getalpha(field, (block+current_point)->descriptor_file, L_DIAL_DESCRIPTOR_FILE );
				 break;
			case DIAL_MENU_FILE:
				 getalpha(field, (block+current_point)->menu_file, L_DIAL_MENU_FILE );
				 break;
			case DIAL_BAUD_RATE:
				 GetAlpha(field, MAX_ALPHA, buf);
				 pthis->GDGets(buf,pthis->w_record,pthis->t_fields[field-1],GetFldSize(field),Black,White);
				 l = atoi(buf);
				 PutAlpha(field, buf);
				 break;
			case DIAL_LINK_NUMBER:
				 getalpha(field, (block+current_point)->link_number, L_DIAL_MENU_FILE );
				 break;
		}
 pgrid->GGPutField(field,Lightgray,Black);
	}
}


int Dial_list_block::GetRec(void)
{
	int i,j ;
	int ana_dig ;
	int auto_man ;
	int range ;
	char * ch[2],buf[10];

	char c[9],TEXT_POINT[5],type[5],TEXT_TYPE[5];

	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,'\0',sizeof(struct DIAL_LineBuf));

	for(i=0; i<fields_number; i++)
		{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
		}
	return FX_SUCCESS;
}

int Dial_list_block::GetField(int field, char *buf)
{
	char xbuf[15];   // used for itoa fcn
	int l;

	l=0;
	switch (field)
	{
		case DIAL_SYSTEM_NAME:
						memcpy(buf, lalign((block+current_point)->system_name,L_DIAL_SYSTEM_NAME),L_DIAL_SYSTEM_NAME );
						l = L_DIAL_SYSTEM_NAME;
				 break;
		case DIAL_PHONE_NUMBER:
						memcpy(buf, lalign((block+current_point)->phone_number, L_DIAL_PHONE_NUMBER), L_DIAL_PHONE_NUMBER );
						l = L_DIAL_PHONE_NUMBER;
				 break;
		case DIAL_DESCRIPTOR_FILE:
						memcpy(buf, lalign((block+current_point)->descriptor_file, L_DIAL_DESCRIPTOR_FILE), L_DIAL_DESCRIPTOR_FILE );
						l = L_DIAL_DESCRIPTOR_FILE;
				 break;
		case DIAL_MENU_FILE:
						memcpy(buf, lalign((block+current_point)->menu_file, L_DIAL_MENU_FILE), L_DIAL_MENU_FILE );
						l = L_DIAL_MENU_FILE;
				 break;
		case DIAL_BAUD_RATE:
					 readint(field, (int *)&((block+current_point)->baud_rate),  L_PRG_SIZE, buf, 0);
					 l=L_BAUD_RATE;
				 break;
		case DIAL_LINK_NUMBER:
						memcpy(buf, lalign((block+current_point)->link_number, L_DIAL_MENU_FILE), L_DIAL_MENU_FILE );
						l = L_DIAL_LINK_NUMBER;
				 break;
		}
 return l;
}

*/


