#define NEW
#include <windows.h>
#include "graphics.h"
#include "recstruc.h"
#include "fxengine.h"
#include "t3000def.h"
#include "parser.h"
#include <string.h>
#include "ggrid.h"
#include "gedit.h"
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include "t3000hlp.h"

#define min(a,b)    (((a) < (b)) ? (a) : (b))

#define CTRLBREAK			      -1
#define OFF 0
#define ON 1
#define  FONDCOLOR  Lightgray
#define  BOXCOLOR  Cyan


#include "mtkernel.h"
#include "gmbar.h"
#include "serial.h"
#include "rs485.h"
#include "ptp.h"
#include "router.h"

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

//#ifdef NETWORK_COMM
//extern OPERATOR_LIST operator_list;
//#endif

extern char NotResponse1;
extern long data_const, data_length_const;
extern char maxtbl;
extern int tswitch;      		// task index
extern Panel_info1 panel_info1;
extern int remote_net;
extern int MAX_HEAP_BUF;
extern int programs_size;
extern unsigned long timestart;
extern byte serial_access;
extern int NET_EXIT;
//extern USERS_RECORD	user;
extern  int error_net;
//extern Netbios *pnet;
//extern NETBIOS_Presence	Netbios_state;

extern char station_name[NAME_SIZE];
extern int  station_num;
extern int  Station_NUM;
extern int ipxport, rs485port;
extern char check_annual_routine_flag;


extern char printamon;
extern char display_amons;
extern int mode_text;
extern GMenuBar G;
extern int fground;
extern char control;

extern Password_struct passwords;
//extern Password_point	passwords[MAX_PASSW];
//extern int ind_passwords;
extern REMOTE_POINTS _far  remote_points_list[MAXREMOTEPOINTS82];
extern int local_panel;
extern int simulator;

extern Station_point station_list[32];
extern unsigned  t3000_flag;
extern Comm_Info *comm_info;

extern char nothing;
extern char view_name[41];
extern char (*array)[41];
extern char access_level;
extern char arights_grid;
//extern char refresh_table[24];
extern int modify_child;
extern int communication;
extern XmsDes *Des;
extern Time_block ora_current;

static GWindow *D;
char *screen_right_tmp;
long rights_access_tmp;
unsigned char lastid;

typedef union {
	 char  c[4];
	 long  big;
 } big_indian;

enum {PROGR=0, OPERATOR=1 };

	union key {
		int i;
		char ch[2];
		} ;

//class GMenuBar;
class GWDialog;
extern GMenuBar G;

extern char huge *heap_grp;
extern unsigned long ind_heap_grp;
//extern char huge heap_buf[];
extern char *heap_buf;
extern unsigned long ind_heap_buf;
extern unsigned high_mem_block;
extern int DORU_SYSTEM;
extern Panel *ptr_panel;

extern int pcx(char *argv);

extern void deleteremotepoint(Point_Net point, int network);
extern int updateremotepoint(Point_Net point, int network);
extern int local_request(int panel, int network);
extern int findroutingentry(int port, int network, int &j, int t=1);
extern char wingets(char far *ptr, int row, int col, int width,
				 int bkgnd, int frgnd, char which_type='A', char *sablon=NULL, char retnokey = 0);
extern char getID(void);
extern void memsize(void);
extern int ClientTransactionStateMachine(
			 ServicePrimitive Event,  int Service, FlowControl flowcontrol, int network,
			 int destination, int source, char invokeID, char *data, unsigned int *data_length,
			 char command, int arg, char vendorID, long timeout = TIMEOUT_NETCALL,
			 char *returnargs=NULL, int *length_returnargs=NULL,
			 char *sendargs=NULL, int length_sendargs=0, char bytearg=0, int task=-1, int port=-1,
			 int others = 0
			  );
extern void result_ser(RS232Error result, int rs485=0);
extern int bioskey_new(int cmd);
extern int ReadYesNo(int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							int bkgndrreadcolor, int readcolor, char *text, char yes='Y', char no='N', char s=0);
extern int dialog_select(int n_entry, char *arraytext, int save, int x, int y, int bkgnd, int tbkgnd, char *title=NULL, char col=10);
extern int mgets(char *str,int viz, int bkgnd, int frgnd);
extern char *rtrim(char *text);
extern void chbkg(int lx, int ly, int width, int bkgnd, int frgnd, int unchangecol=127, int height = 0);
extern void Border(int ltopx, int ltopy, int rbottomx, int rbottomy, int colour,int bcolour);
extern char *ispoint(char *token,int *num_point,byte *var_type, byte *point_type, int *num_panel, int *num_net, int network=0, byte panel=0, int *netpresent=0);
extern int put_point(Point point, long value, int prog_op, int v=0, char *perr=NULL );
extern int get_point(Point point, long *value, char **p);
extern long psample(long *interv, Str_monitor_point *amon);
extern int amon_routine(byte num_point,byte num_panel,int net,int call_type,int x,GGrid *pgrid);
extern void DisplayMessage(int lx, int ly, int rx, int ry, char *title, char *message, GWindow **Er1, int fcolor=Black, GWindow *Er2=NULL, long delay=0);
extern void DisplayMessageT(int lx, int ly, int rx, int ry, char *title, char *message, GWindow **Er1, int fcolor=Black, GWindow *Er2=NULL, long delay=0);
extern void DeleteMessage(GWindow *p);
extern int checkport(int com, int t=0);

extern unsigned char tbl_bank[MAX_TBL_BANK];


extern char user_name[16];
extern char password[16];

extern int max_entry;
extern long amon_file_length;
extern int refresh_time;

char uname[16];
char upassword[9];
static char dgroup[3];  //acces[3]
char ddefault[3];
char acces;

//char huge *Heap_alloc(int bytes);
char *Heap_alloc(int bytes);
//int Heap_dealloc(char huge **old);
int Heap_dealloc(char **old);
//int Heap_move(char huge *old,  char huge *newp, int ind);
int Heap_move(char *old,  char *newp, int ind);

void restore_screen(char *screen);
void save_screen(char **screen);


void pname(GWDialog *D);
void paccess(GWDialog *D);
void ppassword(GWDialog *D);
void pdefault(GWDialog *D);
void prights(GWDialog *D);

int writepropertyservice(Point_Net point, T3000PropertyIdentifier property, long val=0);
int	put_point_info(Point_info *point_info);
int	get_point_info(Point_info *point_info, char **des=NULL, char **label=NULL, char **ontext=NULL, char **offtext=NULL, char pri=0, int network = 0xFFFF);
char *lalign(char *buf, int n);
char *ralign(char *buf, int n);
char *ltrim(char *text);
void ftoa(float f, int length, int ndec, char *buf);
void longtoa(long f, int length, int ndec, char *buf);
//int findlabel(int panel_type, Sub_a_b net_type, int panel,Point_main_sub point, char *buf);
//int findpoint(int panel_type,Sub_a_b net_type, int panel, Point point,char *buf);
int look(char *buf,Point *point,int panel_type,Sub_a_b net_type,int panel,int sub_panel);
int pointtotext(char *buf,Point_Net *point);
int pointtotext(char *buf,Point_T3000 *point);
int texttointerval( char *textbuffer,char *seconds , char *minutes , char *hours, char c=':' );
extern char * intervaltotext(char *textbuf, long seconds , unsigned minutes , unsigned hours, char *c=":");
int net_call(int command, int arg,  char *data, uint *length , int dest,
				 int network, int others=0, int timeout=TIMEOUT_NETCALL,
				 char *returnargs=NULL, int *length_returnargs=NULL,
				 char *sendargs=NULL, int length_sendargs=0, char bytearg=0, int port=-1);
int initamoninputsscreen(void);


int GetRange_Out(int range);
int GetRange_In(int range);
int GetRange_Var(int range);

//int nofond=0;
int index_max_amon_input;
Point_Net amon_inputs[MAX_POINTS_IN_MONITOR];
char modify_monitor;

unsigned int line_array[50][2];
int ind_line_array;

/* the ranges and units of the items used */
char gdescriptor[22];
char glabel[17];
char gpointname[17];

//char huge program_buf[2000];

static char *ast="********";
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
extern char huge *sun;
extern char huge *mon;
extern char huge *tue;
extern char huge *wed;
extern char huge *thu;
extern char huge *fri;
extern char huge *sat;
extern char huge *enabl;
extern char huge *disabl;
extern char huge *snothing;
extern char huge *analog_text;
extern char huge *digital_text;
extern char huge *slash;
extern char huge *hours;
extern char huge *days;
extern char huge *minut;
extern char huge *tout;
extern char huge *tioutrar;
extern char huge *tioutwar;
extern char huge *tioutray;
extern char huge *tioutway;

extern char huge *normal;
extern char huge *na;
extern char huge *com_prg_text;
extern char huge *blank;
//extern char showsign;
extern char huge *ctrlbreak_text;

extern char huge array_ranges[][11];
extern char huge array_access[][13];

struct FieldStruct huge array_range_struct[] =
		{
		{""   , 'N',0,10,0}
		}    ;

char huge months[4][80]={{"       JANUARY                FEBRUARY              MARCH           "},
								 {"        APRIL                   MAY                  JUNE           "},
								 {"        JULY                   AUGUST              SEPTEMBER        "},
								 {"       OCTOBER                NOVEMBER             DECEMBER         "}};

extern char huge point_cod[MAX_TBL_BANK][5];

extern unsigned char filter[8];

extern int analog_limits[6];

extern dig_range_form huge dig_range_array[];
extern an_range_form huge in_range_array[];
extern an_range_form huge out_range_array[];
extern an_range_form huge var_range_array[];
//extern range_form huge range_array[MAX_RANGE];
//extern char huge  des[MAX_DES];
//extern char huge mons[12];
extern char month_days[12];

Block::Block(GGrid *pthis, byte pt, byte p, int net, signed char ttype, byte pnum, int fields, char *p_line_buf)
{
			asm push es;
			pgrid = pthis;
			panel_type = pt;
			panel = p;
			network = net;
			type = ttype;
			point_number = pnum;
//			sub_panel = sp;
//			net_type = nt;
//			bank = b;
			fields_number = fields;
			if (type == INDIVIDUAL)
				current_point=pnum-1;
			else
				current_point=0;
			ptr_line_buf = p_line_buf;
			asm pop es;
}


int Block::checklocal(void)
{
//  if( (local_panel &&  type!=INDIVIDUAL) || (type==INDIVIDUAL && panel==Station_NUM))
	if( local_request(panel, network) )
	 return 1;
  else
    return 0;
}


//int Output_block::PutAlpha(FIELDHANDLE hfield, char *buf)
int Block::PutAlpha(FIELDHANDLE hfield, char *buf)
{
 int n;
 n=r.RecStruct(hfield)->l;
 if (strlen(buf) < n)
		n=strlen(buf);
// mmemcpy(((char *)&line_buf)+r.RecStruct(hfield)->position-1, buf, n);
 movedata(FP_SEG(buf), FP_OFF(buf), FP_SEG( ptr_line_buf+r.RecStruct(hfield)->position-1 ), FP_OFF( ptr_line_buf+r.RecStruct(hfield)->position-1 ), n);
// memcpy(ptr_line_buf+r.RecStruct(hfield)->position-1, buf, n);
}


//int Output_block::GetAlpha(FIELDHANDLE hfield,int bufsize, char *dest)
int Block::GetAlpha(FIELDHANDLE hfield,int bufsize, char *dest)
{
 int n;
 n=r.RecStruct(hfield)->l;
 if (bufsize < n)
		n=bufsize;
 movedata(FP_SEG(ptr_line_buf+r.RecStruct(hfield)->position-1), FP_OFF(ptr_line_buf+r.RecStruct(hfield)->position-1),
					FP_SEG( dest ), FP_OFF( dest ), n);
// memcpy(dest, ptr_line_buf+r.RecStruct(hfield)->position-1,n);
 dest[n]='\0';
}

//void Output_block::SetBank(byte b)
void Block::SetBank(byte b)
{
 bank = b;
}

//char *Output_block::GetFldName(FIELDHANDLE hfield)
char *Block::GetFldName(FIELDHANDLE hfield)
{
 return(r.RecStruct(hfield)->field_name);
}

//int Output_block::GetFldSize(FIELDHANDLE hfield)
int Block::GetFldSize(FIELDHANDLE hfield)
{
 return(r.RecStruct(hfield)->l);
}

//int Output_block::NRec(void)
int Block::NRec(void)
{
 return(h.HNRec());
}

//int Output_block::NFields(void)
int Block::NFields(void)
{
 return(fields_number);
}

//int Output_block::NextRec(void)
int Block::NextRec(void)
{
 current_point++;
}

//int Output_block::FirstRec(void)
int Block::FirstRec(void)
{
	current_point=0;
}

void Block::nr_point(char *buf)
{
//					 char xbuf[4];
//					 char *p;
					 int l=1;
					 if(type==INDIVIDUAL)
//							l = net_type;
							l = point_number;
/*
					 else
						 for(int i=0;i<bank;i++)
								l += tbl_bank[pgrid->point_type][i+1];
*/
//					 p = ralign(itoa(l+current_point,xbuf,10),pgrid->point_type==WR?2:3);
					 itoa(l+current_point,buf,10);
					 ralign(buf,pgrid->point_type==WR?2:3);
//					 movedata(FP_SEG(p), FP_OFF(p),
//										FP_SEG( buf ), FP_OFF( buf ), (pgrid->point_type==WR?2:3));
}
// field; dest-unde depun sirul citit;  length-lungimea
int Block::getalpha(FIELDHANDLE field, char *dest, int length)
{
 char buf[MAX_ALPHA+1];
 GetAlpha(field, MAX_ALPHA, buf);
 pgrid->GDGets(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
 PutAlpha(field, buf);
 char *p;
 p = lalign(buf,length);
 movedata(FP_SEG(p), FP_OFF(p),
					FP_SEG( dest ), FP_OFF( dest ), length);
// memcpy(dest,lalign(buf,length),length);
}

//  ppoint - point-ul  ; dest - unde depun pointul(2 bytes) citit la citire (read==1)
//                            - unde returnez label (read==0)
int Block::getpoint(FIELDHANDLE field, Point_T3000 point, char *dest, int read)
{
					 byte var_type, point_type;
					 int  num_point,num_net, num_panel;
					 char *p, buf[MAX_ALPHA+1];
					 if(read)
					 {
						GetAlpha(field, MAX_ALPHA, buf);
						pgrid->GDGets(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
						if( (p=ispoint(rtrim(buf),&num_point,&var_type, &point_type, &num_panel, &num_net, network, panel)) || !strlen(rtrim(buf)) )
						{
						if(strlen(rtrim(buf)))
						{
						 strcpy(buf,p);
						 point.panel = num_panel-1;point.number = num_point-1;point.point_type = point_type+1;
						}
						else
						 point.panel = point.number = point.point_type = 0;

						ralign(lalign(buf,L_AMON_INPUT),L_AMON_INPUT);
						PutAlpha(field, buf);
						movedata(FP_SEG(&point), FP_OFF(&point),
										FP_SEG( dest ), FP_OFF( dest ), sizeof(point));
						}
					 }
					 else
					 {
					  if (!pointtotext(buf,&point))
					  {
						p=ispoint(rtrim(buf),&num_point,&var_type, &point_type, &num_panel, &num_net, network, panel);
						strcpy(buf,p);
						ralign(lalign(buf,L_AMON_INPUT),L_AMON_INPUT);
					  }
					  else
					  {
						movedata(FP_SEG(snothing), FP_OFF(snothing),FP_SEG(buf), FP_OFF(buf), 8);
					  }
					  movedata(FP_SEG(buf), FP_OFF(buf),FP_SEG(dest), FP_OFF(dest), 8);
					 }
}

int Block::getpoint(FIELDHANDLE field, Point_Net point, char *dest, int read)
{
	byte var_type, point_type;
	int num_point,num_net, num_panel;
  char *p, buf[MAX_ALPHA+1];
					if(read)
					{
					 GetAlpha(field, MAX_ALPHA, buf);
					 pgrid->GDGets(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
					 if( (p=ispoint(rtrim(buf),&num_point,&var_type, &point_type, &num_panel, &num_net, network, panel)) || !strlen(rtrim(buf)) )
					 {
						if(strlen(rtrim(buf)))
						{
						 strcpy(buf,p);
						 point.panel = num_panel-1;point.number = num_point-1;point.point_type = point_type+1;
						 point.network = 0xFFFF;          //network;
						}
						else
						 point.panel = point.number = point.point_type = point.network = 0;

						ralign(lalign(buf,L_AMON_INPUT),L_AMON_INPUT);
						PutAlpha(field, buf);
						movedata(FP_SEG(&point), FP_OFF(&point),
									FP_SEG( dest ), FP_OFF( dest ), sizeof(point));
					 }
					}
					else
					{
					  if (!pointtotext(buf,&point))
					  {
						p=ispoint(rtrim(buf),&num_point,&var_type, &point_type, &num_panel, &num_net, network, panel);
						strcpy(buf,p);
						ralign(lalign(buf,L_AMON_INPUT),L_AMON_INPUT);
					  }
					  else
					  {
						movedata(FP_SEG(snothing), FP_OFF(snothing),FP_SEG(buf), FP_OFF(buf), 8);
					  }
					  movedata(FP_SEG(buf), FP_OFF(buf),FP_SEG(dest), FP_OFF(dest), 8);
					 }
}

//la read: field, pf, 0, 0, NULL, 1
// la get: all;
//int Block::readfloat(FIELDHANDLE field, float *pf,  int length, int dec, char *p, int read, float min, float max)
int Block::readfloat(FIELDHANDLE field, long *pf,  int length, int dec, char *p, int read, float min, float max)
{
 char buf[MAX_ALPHA+1];
 float value;
 if(read)
 {
	GetAlpha(field, MAX_ALPHA, buf);
	pgrid->GDGetn(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
	if(read==2)
	{
	 value = atof(buf);
	 if(value < min) value = min;
	 if(value > max) value = max;
	 ftoa(value, length, dec, buf);
	}
	PutAlpha(field, buf);
	*pf=(long)(atof(buf)*1000+0.1);
 }
 else
 {
//	value = (float)*pf / 1000;
//	ftoa(value, length, dec, p);
	longtoa(*pf, length, dec, p);
 }
}

int Block::readint(FIELDHANDLE field, int *pi,  int length, char *p, int read, int min, int max)
{
 char buf[MAX_ALPHA+1];
 int value;
 if(read)
 {
	GetAlpha(field, MAX_ALPHA, buf);
	pgrid->GDGetn(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
	if(read==2)
	{
	 value = atoi(buf);
	 if(value < min) value = min;
	 if(value > max) value = max;
	 ralign(itoa(value,buf,10),length);
	}
	PutAlpha(field, buf);
	*pi=atoi(buf);
 }
 else
 {
	char *p1;
	p1=ralign(itoa(*pi,buf,10),length);
	movedata(FP_SEG(p1), FP_OFF(p1),
					 FP_SEG(p), FP_OFF(p), length);
//	memcpy(p,ralign(itoa(*pi,buf,10),length),length);
 }
}
//int Output_block::GotoRec(RECORDNUMBER record_number)
int Block::GotoRec(RECORDNUMBER record_number)
{
 current_point = record_number-1;
}

int Block::readinterval(FIELDHANDLE field, char *buf, long *seconds , int *minutes, int *hours )
{
	memcpy(buf, intervaltotext( NULL, seconds?*seconds:0 , *minutes, *hours),seconds?8:5);
	if(!seconds)
			buf[5]=0;
	else
			buf[8]=0;
//	pgrid->GDGets(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
	if(seconds)
		pgrid->GDGetsablon(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White,"NN:NN:NN");
	else
		pgrid->GDGetsablon(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White,"NN:NN");

	texttointerval( buf,  (char *)seconds , (char *)minutes, (char *)hours);
	memcpy(buf,intervaltotext( NULL, seconds?*seconds:0, *minutes, *hours), seconds?8:5);
	if(!seconds)
			buf[5]=0;
	else
			buf[8]=0;
}




char *ralign(char *buf, int n)
{
 int l;
 l=strlen(buf);
 if (l<n)
		{
		 movmem(buf, buf+n-l, l+1);
		 memset(buf, ' ', n-l);
		}
 return buf;
}

char *lalign(char *buf, int n)
{
 if (strlen(buf)<n)
		{
		 memset(buf+strlen(buf),' ',n-strlen(buf));
		 buf[n]=0;
		}
 return buf;
}

int	automan(int l, char *buf)
{
	if (l==MAN)
	{
	 strcpy(buf,(char *)man);
	 l=MAN;
	}
	else
	{
	 strcpy(buf,(char *)autom);
	 l=AUTO;
	}
	return l;
}

int	onoff(int l, char *buf)
{
	if (l==ON)
	{
	 strcpy(buf,(char *)on);
	 l=ON;
	}
	else
	{
	 strcpy(buf,(char *)off);
	 l=OFF;
	}
	return l;
}

int	yesno(int l, char *buf)
{
	if (l==YES)
	{
	 strcpy(buf,(char *)Yes);
	 l=YES;
	}
	else
	{
	 strcpy(buf,(char *)No);
	 l=NO;
	}
	return l;
}

void upcunit(Units_element *punits)
{
 for(int i=0;i<MAX_UNITS;i++)
 {
	int x,y, z;
	z = custom_digital1 - DIG1;
	x =  min(5,strlen(punits[i].digital_units_off));
	memcpy(dig_range_array[z+i].range_text, ptr_panel->units[i].digital_units_off,x);
	punits[i].digital_units_off[x]='/';
	y =  min(5,strlen(punits[i].digital_units_on));
	memcpy(&punits[i].digital_units_off[x+1], punits[i].digital_units_on,y);
	punits[i].digital_units_off[x+1+y]=0;
 }
}
//**********************************
//    class Output_block
//**********************************

Output_block::Output_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				 :Block(pthis, pt, p, net, type, pnum, N_OUT, (char *)&line_buf)
	 {
		 unsigned char tbl_bank1[MAX_TBL_BANK];
		 asm push es;
		 int l1,npoint=0;
		 if(type==INDIVIDUAL)
		 {
				number_of_points=1;           //MAX_OUTPUT;
				npoint =  pnum-1;                // num_point
		 }
		 else
		 {
				if(maxtbl)
				{
				 number_of_points=maxtbl;           //MAX_OUTPUT;
         maxtbl = 0;
				}
				else
				 number_of_points=tbl_bank[OUT];           //MAX_OUTPUT;
		 }
		 set_semaphore_dos();
		 block=new Str_out_point[number_of_points];
		 clear_semaphore_dos();
//		 if((local_panel &&  type!=INDIVIDUAL) || (type==INDIVIDUAL && p==Station_NUM))
		 if( local_request(p, net) )
			memmove(block,&ptr_panel->outputs[npoint],number_of_points*sizeof(Str_out_point));
		 else
			memset(block,'\0',number_of_points*sizeof(Str_out_point));
		 r.RecStruct(N_OUT,out_struct);
		 h.HSet(N_OUT,r.RecStruct(1),number_of_points);
		asm pop es;
	 }

Output_block::~Output_block()
{
		 set_semaphore_dos();
		 if(block)
		 {
			 delete [] block;
		 }
		 clear_semaphore_dos();
}

int Output_block::Read(int field, char key)
{
 char buf[50],l;
 if(key==INSERT)
 {
 }
 else
 {
  switch (field) {
		case OUT_NUM:
		case OUT_UNITS:
						break;
		case OUT_FULL_LABEL:
					 getalpha(field, (block+current_point)->description, L_OUT_FULL_LABEL);
					 break;
		case OUT_LABEL:
					 getalpha(field, (block+current_point)->label, L_OUT_LABEL);
					 break;
		case OUT_AUTO_MAN:
					 (block+current_point)->auto_manual=automan(!(block+current_point)->auto_manual, buf);
					 PutAlpha(field, buf);
					 refresh_time = 0;
					 break;
		case OUT_VALUE:
//						float *pf;
						long *pf;
						char control1;
						if( (block+current_point)->auto_manual == AUTO ) break;

						int range;
						range = GetRange_Out((block+current_point)->range);

						pf = &(block+current_point)->value;
						control1=(block+current_point)->control;
//						if  ( range == 48 || range == 49 || range == 10 || range == 13 || range == 9 )
						if  ( range >= V0_10 && range <= I_0_20ma )
							{
							 GetAlpha(field, MAX_ALPHA, buf);
							 pgrid->GDGets(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
							 PutAlpha(field, buf);
							 *pf=(long)(atof(buf)*1000+0.1);
							 break;
							}
						else
							{
							 int n;
							 if( OFF_ON <= range && range <=custom_digital8 )
							 {
								control1 = !control1;
								range -= DIG1;
								memcpy(buf, dig_range_array[range].dunits[control1],L_OUT_VALUE);
								lalign(buf,L_OUT_VALUE);
								*pf=control1?1000L:0;
								PutAlpha(field, buf);
								(block+current_point)->control=control1;
							 }
							}
						 refresh_time = 0;
							break;
		case OUT_RANGE:
//					 float value;
					 char xbuf[4],dig_ana;
					 long value;
					 GWindow *D;
//					 set_semaphore_dos();
					 GWindow *D1;
					 D1 = new GWindow(1,1,80,25,NO_STACK,0);
//					 clear_semaphore_dos();
					 D1->GWSet("Select Range Number ",Lightgray,Darkgray);
					 D1->GShowWindow(0);

					 memcpy(array_struct, array_range_struct, sizeof(array_range_struct));
					 int i;
					 i=dialog_select( 3, (char *)array_ranges, 1, 32, 4, Cyan,Blue);  // 0=don't save
					 if(i>=0)
					 {
						if (i==0)
						{
//						 set_semaphore_dos();
						 D = new GWindow(2,12,78,19,NO_STACK,0);
//						 clear_semaphore_dos();
//						 D->GWSet("Analog Ranges",Lightgray,Darkgray);
						 D->GWSet("Analog Ranges",Cyan,Blue);
						 D->GShowWindow(0);
						 D->GWPuts(1,2,"1. 0.0 to 10.0  Volts       5. 0.0 to 100  %Close",Cyan,Black);
						 D->GWPuts(2,2,"2. 0.0 to 100   %Open       6. 0.0 to 20   ma",Cyan,Black);
						 D->GWPuts(3,2,"3. 0.0 to 20    psi         0. Unused ",Cyan,Black);
						 D->GWPuts(4,2,"4. 0.0 to 100   %",Cyan,Black);
						}
						if (i==1)
						{
 //						 set_semaphore_dos();
						 D = new GWindow(2,12,78,18,NO_STACK,0);
 //						 clear_semaphore_dos();
						 D->GWSet("Digital Ranges",Cyan,Blue);
						 D->GShowWindow(0);
						 D->GWPuts(1,2,"1/12 Off/On      2/13 Close/Open   3/14 Stop/Start  4/15 Dis/Enable",Cyan,Black);
						 D->GWPuts(2,2,"5/16 Norm/Alarm  6/17 Norm/High    7/18 Norm/Low    8/19 No/Yes",Cyan,Black);
						 D->GWPuts(3,2,"9/20 Cool/Heat   10/21 Un/Occupied  11/22 Low/High",Cyan,Black);
						}
						if (i==2)
						{
/*
						 Units_element	*punits;
						 set_semaphore_dos();
						 punits = new Units_element[MAX_UNITS];
						 clear_semaphore_dos();
						 memset(punits,0,sizeof(Units_element)*MAX_UNITS);
*/
//						 set_semaphore_dos();
						 D = new GWindow(2,11,78,18,NO_STACK,0);
//						 clear_semaphore_dos();
						 D->GWSet("Custom Digital Ranges",Cyan,Blue);
						 D->GShowWindow(0);
						 D->GWPuts(1,2,"23.          /                24.         /",Cyan,Black);
						 D->GWPuts(2,2,"25.          /                26.         /",Cyan,Black);
						 D->GWPuts(3,2,"27.          /                28.         /",Cyan,Black);
						 D->GWPuts(4,2,"29.          /                30.         /",Cyan,Black);

/*
						 if(!local_panel)
						 {
							if( net_call(UNIT+1, 0, (char *)punits, 0, panel, network)==SUCCESS)
							{

							  upcunit(punits);
							  D->GWPuts(1,10, punits->digital_units_off,Cyan,Black);
							  D->GWPuts(1,40, (punits+1)->digital_units_off,Cyan,Black);
								D->GWPuts(2,10, (punits+2)->digital_units_off,Cyan,Black);
							  D->GWPuts(2,40, (punits+3)->digital_units_off,Cyan,Black);
							  D->GWPuts(3,10, (punits+4)->digital_units_off,Cyan,Black);
								D->GWPuts(3,40, (punits+5)->digital_units_off,Cyan,Black);
							  D->GWPuts(4,10, (punits+6)->digital_units_off,Cyan,Black);
							  D->GWPuts(4,40, (punits+7)->digital_units_off,Cyan,Black);
							}
						 }
						 else
*/
						 {
						  D->GWPuts(1,10, dig_range_array[23].range_text,Cyan,Black);
						  D->GWPuts(1,40, dig_range_array[24].range_text,Cyan,Black);
						  D->GWPuts(2,10, dig_range_array[25].range_text,Cyan,Black);
						  D->GWPuts(2,40, dig_range_array[26].range_text,Cyan,Black);
						  D->GWPuts(3,10, dig_range_array[27].range_text,Cyan,Black);
							D->GWPuts(3,40, dig_range_array[28].range_text,Cyan,Black);
						  D->GWPuts(4,10, dig_range_array[29].range_text,Cyan,Black);
						  D->GWPuts(4,40, dig_range_array[30].range_text,Cyan,Black);
						 }
//						 if(punits) delete punits;
						}
						D1->GWPuts(20,27,"Enter range number : ",Lightgray,White);
						D1->GWPuts(20,49,"  ",Cyan,Black);
						D1->GWGoto(20,49);
					  wingets(xbuf, 22, 51, 2, Black, White);
//						mgets(xbuf,1, Black , White);
						D->GReleaseWindow();
//						set_semaphore_dos();
						delete D;
//						clear_semaphore_dos();
					 }
					 D1->GReleaseWindow();
					 delete D1;

					 range = 0;
					 range = atoi(xbuf);

					if( i==0 && ( range > 6 || range < 0 ) ) range = 0;
					if( i==1 && ( range > 22 || range < 1 ) ) range = 0;
					if( i==2 && ( range > 30 || range < 23 ) ) range = 0;
					if( i && range ) range += DIG1;
					if( 0 <= range && range <= I_0_20ma )
					{
					 value=0;
					 dig_ana=ANALOG;
					 control1=0;
					}
					else
					{
							range -= DIG1;
							value = (long)(dig_range_array[range].value);
							control1 = value % 2;
							value = control1?1000L:0;
							dig_ana=DIGITAL;
							range += DIG1;
					 }

							(block+current_point)->range=range;
							(block+current_point)->digital_analog=dig_ana;
							(block+current_point)->control=control1;
							(block+current_point)->value=value;
							(block+current_point)->m_del_low=0;
							(block+current_point)->s_del_high=0;
							if (dig_ana==ANALOG)
//								(block+current_point)->s_del_high=analog_limits[range-1];
								(block+current_point)->s_del_high=100;

						GetField(OUT_VALUE, ((char *)&line_buf)+r.RecStruct(OUT_VALUE)->position-1);
						GetField(OUT_UNITS, ((char *)&line_buf)+r.RecStruct(OUT_UNITS)->position-1);
						GetField(OUT_RANGE, ((char *)&line_buf)+r.RecStruct(OUT_RANGE)->position-1);
						GetField(OUT_LOW, ((char *)&line_buf)+r.RecStruct(OUT_LOW)->position-1);
						GetField(OUT_HIGH, ((char *)&line_buf)+r.RecStruct(OUT_HIGH)->position-1);
//						GetField(OUT_M_DEL, ((char *)&line_buf)+r.RecStruct(OUT_M_DEL)->position-1);
//						GetField(OUT_S_DEL, ((char *)&line_buf)+r.RecStruct(OUT_S_DEL)->position-1);
//						pgrid->GGPutRecord(pgrid->w_record, pgrid->t_fields[pgrid->w_lfield+pgrid->field-1-1],)
						pgrid->GGPutField(OUT_VALUE,Lightgray,Black);
						pgrid->GGPutField(OUT_UNITS,Lightgray,Black);
						pgrid->GGPutField(OUT_RANGE,Lightgray,Black);
						pgrid->GGPutField(OUT_LOW,Lightgray,Black);
						pgrid->GGPutField(OUT_HIGH,Lightgray,Black);
//						pgrid->GGPutField(OUT_M_DEL,Lightgray,Black);
//						pgrid->GGPutField(OUT_S_DEL,Lightgray,Black);

					 break;
		case OUT_LOW:
		case OUT_HIGH:
					 char n;
					 float value1;
					 dig_ana = (block+current_point)->digital_analog;
					 range = (block+current_point)->range;
					 if ((dig_ana==ANALOG) && (range==2 || range==4 || range==5))
							{
							 GetAlpha(field, MAX_ALPHA, buf);
							 pgrid->GDGetn(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
							 value1 = atof(buf);
							 if (value1<0) value1=0;
							 if (value1>10.0) value1=10.0;
							 ftoa(value1,L_OUT_LOW , 1, buf);
//								 sprintf(buf,"%4.1f",value);
							 PutAlpha(field, buf);
								 if (field==OUT_LOW)
									 (block+current_point)->m_del_low = (value1*10+0.1);
								 else
									 (block+current_point)->s_del_high = (value1*10+0.1);
							}
					 break;
/*
		case OUT_M_DEL:
		case OUT_S_DEL:
					 dig_ana = (block+current_point)->dig_ana;
					 if (dig_ana==ANA)
							{
							 GetAlpha(field, MAX_ALPHA, buf);
							 pgrid->GDGetn(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
							 l = atoi(buf);
							 PutAlpha(field, buf);
								 if (field==OUT_M_DEL)
									 (block+current_point)->m_del_low = l;
								 else
									 (block+current_point)->s_del_high = l;
							}
					 break;
		case OUT_SEC_LEVEL:
							 GetAlpha(field, MAX_ALPHA, buf);
							 pgrid->GDGetn(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
							 l = atoi(buf);
							 if (l>5) l=5;
							 itoa(l,buf,10);
							 PutAlpha(field, buf);
								(block+current_point)->access_level=l;
							 break;
*/
		case OUT_DECOM:
						l=(block+current_point)->decom;
						if (l==1)
							{
							 strcpy(buf,"-");
							 l=0;
							}
						else
							{
							 strcpy(buf,"Y");
							 l=1;
							}
					   PutAlpha(field, buf);
						(block+current_point)->decom=l;
						 break;
		}
	pgrid->GGPutField(field,Lightgray,Black);
	pgrid->modify = TRUE;
 }
}


int Output_block::GetRec(void)
{
	int i;
	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,'\0',sizeof(struct OUT_LineBuf));

	for(i=0; i<fields_number; i++)
		{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
		}
	return FX_SUCCESS;
}

int Output_block::GetField(int field, char *buf)
{
	int l;

	l=0;
	switch (field) {
		case OUT_NUM:
				 nr_point(buf);
				 break;
		case OUT_FULL_LABEL:
						memcpy(buf , lalign((block+current_point)->description,L_OUT_FULL_LABEL),L_OUT_FULL_LABEL);
						l=L_OUT_FULL_LABEL;
				 break;
		case OUT_AUTO_MAN:
						automan((block+current_point)->auto_manual, buf);
						l=L_OUT_AUTO_MAN;
				 break;
		case OUT_VALUE:
//						float *pf;
					 long *pf;
					 char control1;
					 int range;
					 range = GetRange_Out((block+current_point)->range);
					 if(range)
					 {
						pf = &(block+current_point)->value;
						control1=(block+current_point)->control;
						l=L_OUT_VALUE;
//						if  ( range == 48 || range == 49 || range == 10 || range == 13 || range == 9 )
						if( range >= V0_10 && range <= I_0_20ma )
						{
//							 ftoa((float)*pf/1000,L_OUT_VALUE , 2, buf);
							 longtoa(*pf,L_OUT_VALUE , 2, buf);
							 break;
						}
						if( OFF_ON <=  range && range <= custom_digital8 )
						{
								range -= DIG1;
								int n=dig_range_array[range].value % 2;
								memcpy(buf, dig_range_array[range].dunits[control1^n],L_OUT_VALUE);
/*								memcpy(buf, dig_range_array[range].dunits[control1],L_OUT_VALUE);*/
								lalign(buf,L_OUT_VALUE);
						}
					 }
					 else
					 	 longtoa( 0, L_OUT_VALUE , 2, buf );
					 break;
		case OUT_UNITS:
		case OUT_RANGE:
					int r;
					r = GetRange_Out((block+current_point)->range);
					if( field==OUT_UNITS )
					{
						if( r < DIG1 )
							memcpy(buf, lalign( out_range_array[r].aunits, L_OUT_UNITS), L_OUT_UNITS);
						else
							memcpy(buf, lalign( "     ", L_OUT_UNITS ), L_OUT_UNITS);
						l=L_OUT_UNITS;
					}
					if( field == OUT_RANGE )
					{
						if( r < DIG1 )    /* analog */
							memcpy(buf, lalign((out_range_array+r)->range_text,L_OUT_RANGE),L_OUT_RANGE);
						else             /* digital */
						{
								r -= DIG1;
								memcpy(buf, lalign(dig_range_array[r].range_text,L_OUT_RANGE),L_OUT_RANGE);
						}
						l=L_OUT_RANGE;
					}
				 break;
		case OUT_LOW:
					 char n;
					 l = (block+current_point)->digital_analog;
					 n = (block+current_point)->m_del_low;
					 if (l)
							 ftoa((float)(n)/10,L_OUT_LOW , 1, buf);
					 else
								 memcpy(buf ,nulbuf ,L_OUT_LOW);
					l=L_OUT_LOW;
					 break;
		case OUT_HIGH:
					 l = (block+current_point)->digital_analog;
					 n = (block+current_point)->s_del_high;
					 if (l)
							 ftoa((float)(n)/10,L_OUT_HIGH , 1, buf);
					 else
								 memcpy(buf ,nulbuf ,L_OUT_HIGH);
					 l=L_OUT_HIGH;
					 break;
/*
		case OUT_M_DEL:
					 l = (block+current_point)->dig_ana;
					 n = (block+current_point)->m_del_low;
					 if (l)
								 memcpy(buf ,nulbuf ,L_OUT_M_DEL);
					 else
								 memcpy(buf,ralign(itoa(n,xbuf,10),L_OUT_M_DEL),L_OUT_M_DEL);
					 l=L_OUT_M_DEL;
					 break;
		case OUT_S_DEL:
					 l = (block+current_point)->dig_ana;
					 n = (block+current_point)->s_del_high;
					 if (l)
								 memcpy(buf ,nulbuf ,L_OUT_M_DEL);
					 else
								 memcpy(buf,ralign(itoa(n,xbuf,10),L_OUT_S_DEL),L_OUT_S_DEL);
					l=L_OUT_S_DEL;
					 break;
		case OUT_SEC_LEVEL:
					 l = (block+current_point)->access_level;
					 memcpy(buf,ralign(itoa(l,xbuf,10),L_OUT_SEC_LEVEL),L_OUT_SEC_LEVEL);
					l=L_OUT_SEC_LEVEL;
					break;
*/
		case OUT_DECOM:
					 l = (block+current_point)->decom;
					 if (l)
								memcpy(buf,yes,L_OUT_DECOM);
					 else
								memcpy(buf,lin,L_OUT_DECOM);
					 l=L_OUT_DECOM;
					 break;
		case OUT_LABEL:
					 char *p=lalign((block+current_point)->label,L_OUT_LABEL);
					 memcpy(buf , p,L_OUT_LABEL);
					 l=L_OUT_LABEL;
					 break;
		}
 return l;
}

int GetRange_Out(int range)
{
					int r;
//					 range =  (block+current_point)->range;
					r =range;
/*
			if  ( 0 <=  range && range <= 7 ) { r = range +  DIG1; }
			if  ( 8 <=  range && range <= 15 ) { r = range +  DIG1; }
			if  ( 16 <=  range && range  <= 18 ) {r =  range +  DIG1; }
			if  ( 20 <=  range && range  <= 27 ) {r = range +  DIG1; }
			if  ( 36 <=  range && range  <= 38 ) {r =  range +  DIG1; }
*/
 return r;
}

int Error(int rc)
{
	return 0;
}


//**********************************
//    class Input_block
//**********************************

Input_block::Input_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				:Block(pthis, pt, p, net, type, pnum, N_IN, (char *)&line_buf)
{
			int npoint=0;
			if(type==INDIVIDUAL)
			 {
				number_of_points=1;           //MAX_OUTPUT;
				npoint =  pnum-1;                // num_point
			 }
			else
			{
				if(maxtbl)
				{
				 number_of_points=maxtbl;           //MAX_OUTPUT;
				 maxtbl = 0;
				}
				else
				 number_of_points=tbl_bank[IN];
      }
		 set_semaphore_dos();
			block=new Str_in_point[number_of_points];
		 clear_semaphore_dos();
//		 if((local_panel &&  type!=INDIVIDUAL) || (type==INDIVIDUAL && p==Station_NUM))
	   if( local_request(p, net) )
			memmove(block,&ptr_panel->inputs[npoint],number_of_points*sizeof(Str_in_point));
		 else
			memset(block,'\0',number_of_points*sizeof(Str_in_point));
		 r.RecStruct(N_IN,in_struct);
		 h.HSet(N_IN,r.RecStruct(1),number_of_points);
}

Input_block::~Input_block()
{
		 set_semaphore_dos();
		 if(block)
			 delete [] block;
		 clear_semaphore_dos();
}

int Input_block::Read(int field, char key)
{
 char buf[50],l;

 if(key==INSERT)
 {
 }
 else
 {
	switch (field) {
		case IN_NUM:
		case IN_UNITS:
						break;
		case IN_FULL_LABEL:
					 getalpha(field, (block+current_point)->description, L_IN_FULL_LABEL);
					 break;
		case IN_LABEL:
					 getalpha(field, (block+current_point)->label, L_IN_LABEL);
					 break;
		case IN_AUTO_MAN:
					 (block+current_point)->auto_manual=automan(!(block+current_point)->auto_manual, buf);
					 PutAlpha(field, buf);
					 refresh_time = 0;
					 break;
		case IN_VALUE:
//						float *pf;
						long *pf;
						char dig_ana;
						if( (block+current_point)->auto_manual == AUTO ) break;
						int range;
						range = GetRange_In((block+current_point)->range);
						pf = &(block+current_point)->value;
						dig_ana=(block+current_point)->digital_analog;
						if( dig_ana==ANALOG)
						{
							 GetAlpha(field, MAX_ALPHA, buf);
							 pgrid->GDGets(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
							 PutAlpha(field, buf);
							 *pf=(long)(atof(buf)*1000+0.1);
							 break;
						}
						else
						{
								(block+current_point)->control = !(block+current_point)->control;
								range -= DIG1;
								memcpy(buf, dig_range_array[range].dunits[(block+current_point)->control],L_IN_VALUE);
								lalign(buf,L_IN_VALUE);
								*pf=(block+current_point)->control?1000L:0;
								PutAlpha(field, buf);
						}
						refresh_time = 0;
						break;
		case IN_RANGE:
//					 float value;
					 char xbuf[4];
					 float value1;
					 long value;
					 GWindow *D;
//					 set_semaphore_dos();
					 GWindow *D1;
					 D1 = new GWindow(1,1,80,25,NO_STACK,0);
//					 clear_semaphore_dos();
					 D1->GWSet("Select Range Number ",Lightgray,Darkgray);
					 D1->GShowWindow(0);

					 memcpy(array_struct, array_range_struct, sizeof(array_range_struct));
					 int i;
					 i=dialog_select( 3, (char *)array_ranges, 1, 36, 4, Cyan,Blue);  // 0=don't save
					 if(i>=0)
					 {
						if (i==0)
						{
//						 set_semaphore_dos();
						 D = new GWindow(2,11,78,22,NO_STACK,0);
//						 clear_semaphore_dos();
						 D->GWSet("Analog Ranges",Cyan,Blue);
						 D->GShowWindow(0);
						 D->GWPuts(1,2,"1.   Y3K -40 to 150 Deg.C   10. A10K -60 to 200 Deg.F  19. Pulses/min",Cyan,Black);
						 D->GWPuts(2,2,"2.   Y3K -40 to 300 Deg.F   11. 0.0 to 5.0 Volts       20. Table 1 ",Cyan,Black);
						 D->GWPuts(3,2,"3.   10K -40 to 120 Deg.C   12. 0.0 to 100  Amps       21. Table 2 ",Cyan,Black);
						 D->GWPuts(4,2,"4.   10K -40 to 250 Deg.F   13. 0.0 to 20  ma          22. Table 3 ",Cyan,Black);
						 D->GWPuts(5,2,"5.   G3K -40 to 120 Deg.C   14. 0.0 to  20  psi        23. Table 4 ",Cyan,Black);
						 D->GWPuts(6,2,"6.   G3K -40 to 250 Deg.F   15. 0.0 to  2^22 counts    24. Table 5 ",Cyan,Black);
						 D->GWPuts(7,2,"7. KM10K -40 to 120 Deg.C   16. 0.0 to 3000 FPM         0. Unused  ",Cyan,Black);
						 D->GWPuts(8,2,"8. KM10K -40 to 250 Deg.F   17. 0 to 100  %(0-5V)                  ",Cyan,Black);
						 D->GWPuts(9,2,"9.  A10K -50 to 110 Deg.C   18. 0 to 100  %(4-20ma)                ",Cyan,Black);
						}
						if (i==1)
						{
//						 set_semaphore_dos();
						 D = new GWindow(2,12,78,18,NO_STACK,0);
//						 clear_semaphore_dos();
						 D->GWSet("Digital Ranges",Cyan,Blue);
						 D->GShowWindow(0);
						 D->GWPuts(1,2,"1/12 Off/On      2/13 Close/Open   3/14 Stop/Start  4/15 Dis/Enable",Cyan,Black);
						 D->GWPuts(2,2,"5/16 Norm/Alarm  6/17 Norm/High    7/18 Norm/Low    8/19 No/Yes",Cyan,Black);
						 D->GWPuts(3,2,"9/20 Cool/Heat   10/21 Un/Occupied  11/22 Low/High",Cyan,Black);
						}
						if (i==2)
						{
/*
						 Units_element	*punits;
						 set_semaphore_dos();
						 punits = new Units_element[MAX_UNITS];
						 clear_semaphore_dos();
						 memset(punits,0,sizeof(Units_element)*MAX_UNITS);
*/
//						 set_semaphore_dos();
						 D = new GWindow(2,11,78,18,NO_STACK,0);
//						 clear_semaphore_dos();
						 D->GWSet("Custom Digital Ranges",Cyan,Blue);
						 D->GShowWindow(0);
						 D->GWPuts(1,2,"23.          /                24.         /",Cyan,Black);
						 D->GWPuts(2,2,"25.          /                26.         /",Cyan,Black);
						 D->GWPuts(3,2,"27.          /                28.         /",Cyan,Black);
						 D->GWPuts(4,2,"29.          /                30.         /",Cyan,Black);

/*
						 if(!local_panel)
						 {
							if( net_call(UNIT+1, 0, (char *)punits, 0, panel, network)==SUCCESS)
							{

							  upcunit(punits);
							  D->GWPuts(1,10, punits->digital_units_off,Cyan,Black);
							  D->GWPuts(1,40, (punits+1)->digital_units_off,Cyan,Black);
							  D->GWPuts(2,10, (punits+2)->digital_units_off,Cyan,Black);
							  D->GWPuts(2,40, (punits+3)->digital_units_off,Cyan,Black);
							  D->GWPuts(3,10, (punits+4)->digital_units_off,Cyan,Black);
							  D->GWPuts(3,40, (punits+5)->digital_units_off,Cyan,Black);
							  D->GWPuts(4,10, (punits+6)->digital_units_off,Cyan,Black);
							  D->GWPuts(4,40, (punits+7)->digital_units_off,Cyan,Black);
							}
						 }
						 else
*/
						 {
						  D->GWPuts(1,10, dig_range_array[23].range_text,Cyan,Black);
						  D->GWPuts(1,40, dig_range_array[24].range_text,Cyan,Black);
						  D->GWPuts(2,10, dig_range_array[25].range_text,Cyan,Black);
						  D->GWPuts(2,40, dig_range_array[26].range_text,Cyan,Black);
						  D->GWPuts(3,10, dig_range_array[27].range_text,Cyan,Black);
						  D->GWPuts(3,40, dig_range_array[28].range_text,Cyan,Black);
						  D->GWPuts(4,10, dig_range_array[29].range_text,Cyan,Black);
						  D->GWPuts(4,40, dig_range_array[30].range_text,Cyan,Black);
                   }
//						 if(punits) delete punits;
						}
					 D1->GWPuts(22,27,"Enter range number : ",Lightgray,White);
					 D1->GWPuts(22,49,"  ",Cyan,Black);
					 D1->GWGoto(22,49);
					 wingets(xbuf, 24, 51, 2, Black, White);
//					 mgets(xbuf,1, Black , White);
					 D->GReleaseWindow();
//					 set_semaphore_dos();
					 delete D;
//					 clear_semaphore_dos();
					 }
					 D1->GReleaseWindow();
//					 set_semaphore_dos();
					 delete D1;
//					 clear_semaphore_dos();
//					 mtextbackground(Lightgray);

					value = 0;
					range=0;
					range =  atoi(xbuf);
//					if(!range) break;
					if( i==0 && ( range >= 25 || range < 1 ) ) range = 0;
					if( i==1 && ( range > 22 || range < 1 ) ) range = 0;
					if( i==2 && ( range > 30 || range < 23 ) ) range = 0;
					if( i && range ) range += DIG1;
					dig_ana=ANALOG;
					if( !range || (Y3K_40_150DegC <= range && range <= table5) )
					{
						dig_ana=ANALOG;
						if(control)
						 value = ptr_panel->convert_in_point( current_point, range );
						(block+current_point)->control=0;
					}
					else
					{
						 int r = range - DIG1;
						 dig_ana=DIGITAL;
						 if(control)
						 {
							 ptr_panel->inputs[current_point].value=ptr_panel->convert_in_point( current_point, range );
							 (block+current_point)->control = ptr_panel->inputs[current_point].control;
						 }
						 else
							 (block+current_point)->control = (long)(dig_range_array[r].value)%2;
							 value=(block+current_point)->control?1000L:0;
					}
							(block+current_point)->range=range;
							(block+current_point)->digital_analog=dig_ana;
							(block+current_point)->value=value;
							(block+current_point)->filter=6;
							(block+current_point)->calibration_sign=0;
							(block+current_point)->calibration=0;
							(block+current_point)->calibration_increment=0;
							if(range == N0_2_32counts || range == N0_3000FPM_0_5V || range == P0_255p_min)
								(block+current_point)->calibration_increment=1;

							if( Y3K_40_150DegC <= range && range <= A10K_60_200DegF && !(range%2) )
							 (block+current_point)->calibration_increment=1;

//							(block+current_point)->kreuter_10K_thermistor=0;
//							(block+current_point)->ticks=0;

						GetField(IN_VALUE, ((char *)&line_buf)+r.RecStruct(IN_VALUE)->position-1);
						GetField(IN_UNITS, ((char *)&line_buf)+r.RecStruct(IN_UNITS)->position-1);
						GetField(IN_RANGE, ((char *)&line_buf)+r.RecStruct(IN_RANGE)->position-1);
						GetField(IN_FILTER, ((char *)&line_buf)+r.RecStruct(IN_FILTER)->position-1);
//						pgrid->GGPutRecord(pgrid->w_record, pgrid->t_fields[pgrid->w_lfield+pgrid->field-1-1],)
						pgrid->GGPutField(IN_VALUE,Lightgray,Black);
						pgrid->GGPutField(IN_UNITS,Lightgray,Black);
						pgrid->GGPutField(IN_RANGE,Lightgray,Black);
						pgrid->GGPutField(IN_FILTER,Lightgray,Black);
					 break;

		case IN_CALIBR:
					 l = (block+current_point)->digital_analog;
					 if (l==DIGITAL)   break;
							GetAlpha(field, MAX_ALPHA, buf);
							pgrid->GDGets(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
							value1 = atof(buf);
							if((block+current_point)->calibration_increment)
							{
							 if( value1 < -255 ) value1 = -255;
							 if( value1 > 255 ) value1 = 255;
							}
							else
							{
							 if (value1<-25.5) value1=-25.5;
							 if (value1>25.5) value1=25.5;
							}
							if ( value1 < 0 )
							{
								(block+current_point)->calibration_sign = 1;
								value1 = -value1;
							}
							else
							{
								(block+current_point)->calibration_sign = 0;
							}

							if(!(block+current_point)->calibration_increment)
									(block+current_point)->calibration = (int)(value1*10+0.1);
							else
									(block+current_point)->calibration = (int)(value1);
							ftoa( value1, 4, 1, buf );
							PutAlpha(field, buf);
							break;
		case IN_FILTER:
						l=(block+current_point)->filter;
						l++;
						if (l==8) l=0;
						memcpy(buf,ralign(itoa(filter[l],buf,10),L_IN_FILTER),L_IN_FILTER);

						(block+current_point)->filter=l;
					 PutAlpha(field, buf);
					 break;
		case IN_DECOM:
						l=(block+current_point)->decom;
						if (l==1)
							{
							 strcpy(buf,"-");
							 l=0;
							}
						else
							{
							 strcpy(buf,"Y");
							 l=1;
							}
					 PutAlpha(field, buf);
					(block+current_point)->decom=l;
					 break;
		}
  pgrid->GGPutField(field,Lightgray,Black);
  pgrid->modify = TRUE;
 }
}


int Input_block::GetRec(void)
{
	int i;

	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,'\0',sizeof(struct IN_LineBuf));

	for(i=0; i<fields_number; i++)
	{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
	}
	return FX_SUCCESS;
}

int Input_block::GetField(int field, char *buf)
{
//	char xbuf[15];   // used for itoa fcn
	int l,n;

	l=0;
	switch (field) {
		case IN_NUM:
				 nr_point(buf);
				 break;
		case IN_FULL_LABEL:
						memcpy(buf , lalign((block+current_point)->description,L_IN_FULL_LABEL),L_IN_FULL_LABEL);
						l=L_IN_FULL_LABEL;
					 break;
		case IN_AUTO_MAN:
					 automan((block+current_point)->auto_manual, buf);
					 l=L_IN_AUTO_MAN;
				 break;
		case IN_VALUE:
						long *pf;
						char dig_ana;
						int range;
						range = GetRange_In((block+current_point)->range);
//						if( range )
						{
							pf = &(block+current_point)->value;
							dig_ana=(block+current_point)->digital_analog;
							if( dig_ana==ANALOG )
							{
//								 ftoa((float)(*pf)/1000.,L_IN_VALUE , 2, buf);
								 longtoa(*pf,L_IN_VALUE , 2, buf);
								 break;
							}
							else
							if( OFF_ON <= range && range <= custom_digital8 )
							{
								range -= DIG1;
								n=dig_range_array[range].value % 2;
								memcpy(buf, dig_range_array[range].dunits[(block+current_point)->control^n],L_IN_VALUE);
/*								memcpy(buf, dig_range_array[range].dunits[(block+current_point)->control],L_IN_VALUE);*/
								lalign(buf,L_IN_VALUE);
							}
						}
//				  else
//							 longtoa( 0, L_IN_VALUE , 2, buf );
						l = L_IN_VALUE;
						break;
		case IN_UNITS:
		case IN_RANGE:
			  n = GetRange_In((block+current_point)->range);
			  if( field==IN_UNITS )
			  {
				if( n < DIG1 )
				{
					memcpy(buf, in_range_array[n].aunits,L_IN_UNITS);
				}
				else
				{
					memcpy(buf, "     ", L_IN_UNITS);
				}
				l=L_IN_UNITS;
			  }
			  if( field==IN_RANGE )
				{
				if( n > DIG1 ) /*digital */
				{
					n -= DIG1;
					memcpy(buf, dig_range_array[n].range_text, L_IN_RANGE);
				}
				else           /*analog*/
					memcpy(buf, in_range_array[n].range_text, L_IN_RANGE);
				l=L_IN_RANGE;
			  }
			  lalign(buf,l);
			  break;
		case IN_CALIBR:
					 l = (block+current_point)->digital_analog;
					 n = (block+current_point)->calibration;
					 if (l==ANALOG)
					 {
							if( (block+current_point)->calibration_sign )
								n = -n;
							if((block+current_point)->calibration_increment)
							{
//									memcpy(buf,ralign(itoa(n,xbuf,10),L_IN_CALIBR),L_IN_CALIBR);
									itoa(n,buf,10);
									ralign(buf,L_IN_CALIBR);
							}
							else
									ftoa((float)(n)/10.,L_IN_CALIBR, 1, buf);
					 }
					 else
								 memcpy(buf ,nulbuf ,L_IN_CALIBR);
					 l=L_IN_CALIBR;
					 break;
		case IN_FILTER:
						l=(block+current_point)->filter;
						memcpy(buf,ralign(itoa(filter[l],buf,10),L_IN_FILTER),L_IN_FILTER);
						break;
		case IN_DECOM:
					 l = (block+current_point)->decom;
					 if (l)
								memcpy(buf,yes,L_IN_DECOM);
					 else
								memcpy(buf,lin,L_IN_DECOM);
					l=L_IN_DECOM;
					break;
		case IN_LABEL:
					char *p=lalign((block+current_point)->label,L_IN_LABEL);
					memcpy(buf , p,L_IN_LABEL);
					l=L_IN_LABEL;
				 break;
		}

 return l;
}

int GetRange_In(int range)
{
 int r;
 if( ( table5 <= range && range <= DIG1 ) || (	range > custom_digital8 ) )
			{ r = 0 ; }
 else
			{r = range;	}
 return r;
}

//**********************************
//    class Var_block
//**********************************

Var_block::Var_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
			 :Block(pthis, pt, p, net, type, pnum,  N_VAR, (char *)&line_buf)
{
			int npoint=0;
			if(type==INDIVIDUAL)
			{
				number_of_points=1;           //MAX_OUTPUT;
				npoint =  pnum-1;                // num_point
			}
			else
			{
				if(maxtbl)
				{
				 number_of_points=maxtbl;           //MAX_OUTPUT;
				 maxtbl = 0;
				}
				else
					number_of_points=tbl_bank[VAR];           //MAX_OUTPUT;
			}
			set_semaphore_dos();
			block=new Str_variable_point[number_of_points];
			clear_semaphore_dos();
//			if((local_panel &&  type!=INDIVIDUAL) || (type==INDIVIDUAL && p==Station_NUM))
			if( local_request(p, net) )
				memmove(block,&ptr_panel->vars[npoint],number_of_points*sizeof(Str_variable_point));
			else
				memset(block,'\0',number_of_points*sizeof(Str_variable_point));
			r.RecStruct(N_VAR,var_struct);
			h.HSet(N_VAR,r.RecStruct(1),number_of_points);
}

Var_block::~Var_block()
{
		 set_semaphore_dos();
		 if(block)
			 delete [] block;
		 clear_semaphore_dos();
}


int Var_block::Read(int field, char key)
{
 char buf[50],l;

 if(key==INSERT)
 {
 }
 else
 {
	switch (field) {
		case VAR_NUM:
						break;
		case VAR_FULL_LABEL:
					 getalpha(field, (block+current_point)->description, L_VAR_FULL_LABEL);
					 break;
		case VAR_LABEL:
					 getalpha(field, (block+current_point)->label, L_VAR_LABEL);
					 break;
		case VAR_AUTO_MAN:
					 (block+current_point)->auto_manual=automan(!(block+current_point)->auto_manual, buf);
					 PutAlpha(field, buf);
					 refresh_time = 0;
					 break;
		case VAR_VALUE:
						long *pf;
						int dig_ana;
						if( (block+current_point)->auto_manual == AUTO ) break;
						int range;
						range = GetRange_Var((block+current_point)->range);
						pf = &(block+current_point)->value;
						dig_ana=(block+current_point)->digital_analog;

						 if(dig_ana==ANALOG)
							{
							 GetAlpha(field, MAX_ALPHA, buf);
							 if(range == time_unit)
							 {
								 char sec, min, hour;
								 pgrid->GDGetsablon(ltrim(buf),pgrid->w_record,pgrid->t_fields[field-1]+GetFldSize(field)-8,8,Black,White,"NN:NN:NN");
								 texttointerval( buf, &sec , &min , &hour );
								 ralign(buf,L_VAR_VALUE);
									*pf=(long)(((long)hour*3600L+(long)min*60L+(long)sec)*1000L);
							 }
							 else
							 {
								pgrid->GDGets(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
								*pf=(long)(atof(buf)*1000+0.1);
							 }
							 PutAlpha(field, buf);
							 break;
							}
						 else
						 {
//							 char inv = 0;
//							 if( ON_OFF <= range && range <= HIGH_LOW ) inv++;
							 if( OFF_ON <= range && range <=custom_digital8 )
							 {
								char *p;
								(block+current_point)->control = !(block+current_point)->control;
								range -= DIG1;
//								p = dig_range_array[range].dunits[inv^(block+current_point)->control];
								p = dig_range_array[range].dunits[(block+current_point)->control];
								movedata(FP_SEG(p), FP_OFF(p),
												 FP_SEG(buf), FP_OFF(buf), L_VAR_VALUE);
								lalign(buf,L_VAR_VALUE);
								*pf=( (block+current_point)->control ) ? 1000L : 0;
								PutAlpha(field, buf);
							 }
						 }
						 refresh_time = 0;
						 break;
		case VAR_UNITS:
					 char xbuf[4];
					 long value;
					 GWindow *D;
					 set_semaphore_dos();
					 GWindow *D1 = new GWindow(1,1,80,25,NO_STACK,0);
					 clear_semaphore_dos();
					 D1->GWSet("Select Range Number ",Lightgray,Darkgray);
					 D1->GShowWindow(0);

					 movedata(FP_SEG(array_range_struct), FP_OFF(array_range_struct),
										FP_SEG(array_struct), FP_OFF(array_struct),  sizeof(array_range_struct));
//					 memcpy(array_struct, array_range_struct, sizeof(array_range_struct));
					 int i=dialog_select( 3, (char *)array_ranges, 1, 33, 4,Cyan,Blue);  // 0=don't save
					 if(i>=0)
					 {
						if (i==0)
						{
						 set_semaphore_dos();
						 D = new GWindow(2,11,78,22,NO_STACK,0);
						 clear_semaphore_dos();
						 D->GWSet("Analog Ranges",Cyan,Blue);
						 D->GShowWindow(0);
						 D->GWPuts(1,2,"1. Deg. Celsius     10. KWHours    19. Days   28. CFH     37. Custom3",Cyan,Black);
						 D->GWPuts(2,2,"2. Deg. Fahrenheit  11. Volts      20. Time   29. GPM     38. Custom4",Cyan,Black);
						 D->GWPuts(3,2,"3. Feet per Min.    12. KVolts     21. Ohms   30. GPH     39. Custom5" ,Cyan,Black);
						 D->GWPuts(4,2,"4. Pascals          13. Amperes    22. %      31. GAL     40. Custom6",Cyan,Black);
						 D->GWPuts(5,2,"5. KPascals         14. Milliamps  23. %RH    32. CF      41. Custom7",Cyan,Black);
						 D->GWPuts(6,2,"6. lbs/sqr.inch     15. CFM        24. p/min  33. BTU     42. Custom8",Cyan,Black);
						 D->GWPuts(7,2,"7. Inches of WC     16. Seconds    25. Counts 34. CMH      0. Unused",Cyan,Black);
						 D->GWPuts(8,2,"8. Watts            17. Minutes    26. %Open  35. Custom1 ",Cyan,Black);
						 D->GWPuts(9,2,"9. KWatts           18. Hours      27. %Close 36. Custom2 ",Cyan,Black);
						}
						if (i==1)
						{
//						 set_semaphore_dos();
						 D = new GWindow(2,12,78,18,NO_STACK,0);
//						 clear_semaphore_dos();
						 D->GWSet("Digital Ranges",Cyan,Blue);
						 D->GShowWindow(0);
						 D->GWPuts(1,2,"1/12 Off/On      2/13 Close/Open   3/14 Stop/Start  4/15 Dis/Enable",Cyan,Black);
						 D->GWPuts(2,2,"5/16 Norm/Alarm  6/17 Norm/High    7/18 Norm/Low    8/19 No/Yes",Cyan,Black);
						 D->GWPuts(3,2,"9/20 Cool/Heat   10/21 Un/Occupied  11/22 Low/High",Cyan,Black);
						}
						if (i==2)
						{
/*
						 Units_element	*punits;
						 set_semaphore_dos();
						 punits = new Units_element[MAX_UNITS];
						 clear_semaphore_dos();
						 memset(punits,0,sizeof(Units_element)*MAX_UNITS);
*/
//						 set_semaphore_dos();
						 D = new GWindow(2,11,78,18,NO_STACK,0);
//						 clear_semaphore_dos();
						 D->GWSet("Custom Digital Ranges",Cyan,Blue);
						 D->GShowWindow(0);
						 D->GWPuts(1,2,"23.          /                24.         /",Cyan,Black);
						 D->GWPuts(2,2,"25.          /                26.         /",Cyan,Black);
						 D->GWPuts(3,2,"27.          /                28.         /",Cyan,Black);
						 D->GWPuts(4,2,"29.          /                30.         /",Cyan,Black);

/*
						 if(!local_panel)
						 {
							if( net_call(UNIT+1, 0, (char *)punits, 0, panel, network)==SUCCESS)
							{

							  upcunit(punits);
							  D->GWPuts(1,10, punits->digital_units_off,Cyan,Black);
							  D->GWPuts(1,40, (punits+1)->digital_units_off,Cyan,Black);
							  D->GWPuts(2,10, (punits+2)->digital_units_off,Cyan,Black);
							  D->GWPuts(2,40, (punits+3)->digital_units_off,Cyan,Black);
							  D->GWPuts(3,10, (punits+4)->digital_units_off,Cyan,Black);
							  D->GWPuts(3,40, (punits+5)->digital_units_off,Cyan,Black);
							  D->GWPuts(4,10, (punits+6)->digital_units_off,Cyan,Black);
							  D->GWPuts(4,40, (punits+7)->digital_units_off,Cyan,Black);
							}
						 }
						 else
*/
						 {
						  D->GWPuts(1,10, dig_range_array[23].range_text,Cyan,Black);
						  D->GWPuts(1,40, dig_range_array[24].range_text,Cyan,Black);
						  D->GWPuts(2,10, dig_range_array[25].range_text,Cyan,Black);
						  D->GWPuts(2,40, dig_range_array[26].range_text,Cyan,Black);
						  D->GWPuts(3,10, dig_range_array[27].range_text,Cyan,Black);
						  D->GWPuts(3,40, dig_range_array[28].range_text,Cyan,Black);
						  D->GWPuts(4,10, dig_range_array[29].range_text,Cyan,Black);
						  D->GWPuts(4,40, dig_range_array[30].range_text,Cyan,Black);
                   }
//						 if(punits) delete punits;
						}
					 D1->GWPuts(22,27,"Enter Units number : ",Lightgray,White);
					 D1->GWPuts(22,49,"  ",Cyan,Black);
					 D1->GWGoto(22,49);
					 wingets(xbuf, 24, 51, 2, Black, White);
//					 mgets(xbuf,1, Black , White);
					 D->GReleaseWindow();
//					 set_semaphore_dos();
					 delete D;
//					 clear_semaphore_dos();
					 }
					 D1->GReleaseWindow();
//					 set_semaphore_dos();
					 delete D1;
//					 clear_semaphore_dos();

					 range =  atoi(xbuf);
//					 if(!range) break;
					if( i==0 && ( range > custom8 || range < 0 ) ) range = 0;
					if( i==1 && ( range > 22 || range < 1 ) ) range = 0;
					if( i==2 && ( range > 30 || range < 23 ) ) range = 0;
					if( i && range ) range += DIG1;
					if( 0 <= range && range <= custom8 )
					{
						value=0;
						dig_ana=ANALOG;
						(block+current_point)->control=0;
					}
					else
					{
						 int ran =  range - DIG1;
						 value = (block+current_point)->control ? 1000 : 0;
						 dig_ana=DIGITAL;
					}
/*
					{
						 int ran =  range - DIG1;
						 value = (long)(dig_range_array[ran].value);
						 if( ( OFF_ON <= range && range <=LOW_HIGH ) ||
								( custom_digital1 <= range && range <= custom_digital8 ) )
						 {
									(block+current_point)->control = 0;
						 }
						 else
						 {
									(block+current_point)->control = 1;
						 }
						 dig_ana=DIG;
					}
*/
					(block+current_point)->range=range;
					(block+current_point)->digital_analog=dig_ana;
					(block+current_point)->value=value;
					GetField(VAR_UNITS, ((char *)&line_buf)+r.RecStruct(VAR_UNITS)->position-1);
					pgrid->GGPutField(VAR_UNITS,Lightgray,Black);
					GetField(VAR_VALUE, ((char *)&line_buf)+r.RecStruct(VAR_VALUE)->position-1);
					pgrid->GGPutField(VAR_VALUE,Lightgray,Black);
					break;
		}
	pgrid->GGPutField(field,Lightgray,Black);
	pgrid->modify = TRUE;
 }
}

int Var_block::GetRec(void)
{
	int i;
	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,'\0',sizeof(struct VAR_LineBuf));

	for(i=0; i<fields_number; i++)
	{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
	}
	return FX_SUCCESS;
}

int Var_block::GetField(int field, char *buf)
{
	int l;

	l=0;
	switch (field) {
		case VAR_NUM:
				 nr_point(buf);
				 break;
		case VAR_FULL_LABEL:
						memcpy(buf , lalign((block+current_point)->description,L_VAR_FULL_LABEL),L_VAR_FULL_LABEL);
						l=L_VAR_FULL_LABEL;
				 break;
		case VAR_AUTO_MAN:
						automan((block+current_point)->auto_manual, buf);
						l=L_VAR_AUTO_MAN;
				 break;
		case VAR_VALUE:
//						float *pf;
						long *pf;
//						int range = GetRange();
						int range;
						range = (block+current_point)->range;
							pf = &(block+current_point)->value;
						l=L_VAR_VALUE;
						if( (block+current_point)->digital_analog==ANALOG )
//						if  ( range >= 1 && range <= 41)
						{
							 if(range == time_unit)
							 {
								intervaltotext( buf, *pf / 1000L , 0 , 0);
								ralign(buf,GetFldSize(field));
							 }
							 else
//								 ftoa( (float) *pf / 1000., L_VAR_VALUE, 2, buf);
								 longtoa( *pf, L_VAR_VALUE, 3, buf);
							 break;
						}
						else
						{
							char inv = 0;
							if( ON_OFF <= range && range <= HIGH_LOW ) inv++;
							if( OFF_ON <=  range && range <= custom_digital8 )
							{
								range -= DIG1;
								char *p;
								p=dig_range_array[range].dunits[inv^(block+current_point)->control];
//								p=dig_range_array[range].dunits[(block+current_point)->control];
								movedata(FP_SEG(p), FP_OFF(p),
												 FP_SEG(buf), FP_OFF(buf), L_VAR_VALUE);
								lalign(buf,L_VAR_VALUE);
							}
						}
					   break;
		case VAR_UNITS:
					 int r;
					 r = GetRange_Var((block+current_point)->range);
					 int dig_ana;
					 dig_ana = (block+current_point)->digital_analog;
					/* analog items get the auints */
					if( dig_ana == ANALOG )
					{
							movedata(FP_SEG(var_range_array[r].aunits), FP_OFF(var_range_array[r].aunits),
											 FP_SEG(buf), FP_OFF(buf), L_VAR_UNITS);
//							memcpy(buf, var_range_array[r].aunits,L_VAR_UNITS);
					}
					else
					{
							r -= DIG1;
							movedata(FP_SEG(dig_range_array[r].range_text), FP_OFF(dig_range_array[r].range_text),
											 FP_SEG(buf), FP_OFF(buf), L_VAR_UNITS);
//							memcpy(buf, dig_range_array[r].range_text,L_VAR_UNITS);
					}
					lalign(buf,L_VAR_UNITS);
					l=L_VAR_UNITS;
				 break;
		case VAR_LABEL:
						memcpy(buf , lalign((block+current_point)->label,L_VAR_LABEL),L_VAR_LABEL);
						l=L_VAR_LABEL;
				 break;
		}

 return l;
}

int GetRange_Var(int range)
{
					 int r;

	/* translate the range to the appropriate range array text */
		r = range;
//	if ( 0 <  range && range <= 24 )
//		 { r = range + 27 ; }
	/* custom digital ranges are translated to 16 thru 23 */
//	if  ( 25 <=  range && range <= 29 )
//		{ r = range - 5 ; }

#if 0	/* small unused block */
	if  ( 30 <=  variable[x].range && variable[x].range <= 31 )
		{ range = 0; }
#endif

	/* custom 6,7,8 */
/*	if  ( 32 <=  range && range <= 34 )
		{ r = range - 7; }
	if ( 35 <=  range && range <= 41 )
		{ r = range + 54 ; }*/
	/* digital items */
/*	if ( DIG1 <=  range && range <= DIG1+15 )
		{ r = range  ; }
	if  ( range >= 80 || range == 0  )
		{ r = 0  ; }
	*/
 return r;
}

//**********************************
//    class Con_block
//**********************************

Controller_block::Controller_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
					  :Block(pthis, pt, p, net, type, pnum,  N_CON, (char *)&line_buf)
{
			int npoint=0;
			if(type==INDIVIDUAL)
			{
				number_of_points=1;           //MAX_OUTPUT;
				npoint = pnum-1;                // num_point
			}
			else
			{
				if(maxtbl)
				{
				 number_of_points=maxtbl;           //MAX_OUTPUT;
				 maxtbl = 0;
				}
				else
					number_of_points=tbl_bank[CON];           //MAX_CONPUT;
			}
			set_semaphore_dos();
			block=new Str_controller_point[number_of_points];
			clear_semaphore_dos();
//			if((local_panel &&  type!=INDIVIDUAL) || (type==INDIVIDUAL && p==Station_NUM))
			if( local_request(p, net) )
				memmove(block,&ptr_panel->controllers[npoint],number_of_points*sizeof(Str_controller_point));
			else
			  memset(block,'\0',number_of_points*sizeof(Str_controller_point));
			r.RecStruct(N_CON,con_struct);
			h.HSet(N_CON,r.RecStruct(1),number_of_points);
}

Controller_block::~Controller_block()
{
		 set_semaphore_dos();
		 if(block)
			 delete [] block;
		 clear_semaphore_dos();
}


int Controller_block::Read(int field, char key)
{
 char buf[50],l, buf1[10];
 int i,r;

 if(key==INSERT)
 {
 }
 else
 {
	switch (field) {
		case CON_NUM:
		case CON_VALUE:
		case CON_INUNITS:
						break;
		case CON_INPUT:
					 getpoint(field, (block+current_point)->input, (char *)&(block+current_point)->input, 1);
//					 i=(block+current_point)->input;
					 if(local_panel)
					 {
						 if( (block+current_point)->input.point_type-1 == IN )
								r=ptr_panel->inputs[(block+current_point)->input.number].range;
						 if( (block+current_point)->input.point_type-1 == VAR )
								r=ptr_panel->vars[(block+current_point)->input.number].range;
						 get_point(*((Point *)&(block+current_point)->input), &(block+current_point)->input_value, NULL);
						 readfloat( CON_VALUE, &(block+current_point)->input_value, L_CON_VALUE, 1, buf1,0);
					 }
					 else
					 {
						 Str_in_point pinput;
						 net_call(20, ((block+current_point)->input.point_type<<8)+(block+current_point)->input.number, (char *)&pinput, 0, (block+current_point)->input.panel+1, network,NETCALL_RETRY);
						 longtoa(pinput.value, L_CON_VALUE, 1, buf1);
						 r=pinput.range;
					 }
					 PutAlpha(CON_VALUE, buf1);
					 (block+current_point)->units=r;
					 break;
		case CON_SETPOINT:
					 getpoint(field, (block+current_point)->setpoint, (char *)&(block+current_point)->setpoint, 1);
//					 i=(block+current_point)->setpoint;
					 if(local_panel)
					 {
						 if( (block+current_point)->setpoint.point_type-1 == IN )
								r=ptr_panel->inputs[(block+current_point)->setpoint.number].range;
						 if( (block+current_point)->setpoint.point_type-1 == VAR )
								r=ptr_panel->vars[(block+current_point)->setpoint.number].range;
						 get_point(*((Point *)&(block+current_point)->setpoint), &(block+current_point)->setpoint_value, NULL);
						 readfloat( CON_SETPOINTV, &(block+current_point)->setpoint_value, L_CON_SETPOINTV, 1, buf1,0);
					 }
					 else
					 {
						 Str_in_point pinput;
						 net_call(20, ((block+current_point)->setpoint.point_type<<8)+(block+current_point)->setpoint.number, (char *)&pinput, 0, (block+current_point)->setpoint.panel+1, network,NETCALL_RETRY);
						 longtoa(pinput.value, L_CON_SETPOINTV, 1, buf1);
						 r=pinput.range;
					 }
					 PutAlpha(CON_SETPOINTV, buf1);
//					 (block+current_point)->units=r;
					 break;
//		case CON_SETPOINT:
//					 getpoint(field, (block+current_point)->setpoint, (char *)&(block+current_point)->setpoint, 1);
//					 break;
/*
					 Point_main_sub point;
							 if (field==CON_INPUT)
									memcpy(&point,&(block+current_point)->input,2);
							 else
									memcpy(&point,&(block+current_point)->setpoint,2);

					 GetAlpha(field, MAX_ALPHA, buf);
					 pgrid->GDGets(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
					 look(buf,&point,panel_type,net_type,panel,sub_panel);
					 ralign(lalign(buf,L_CON_INPUT),L_CON_INPUT);
					 PutAlpha(field, buf);
					 if (field==CON_INPUT)
						 mmemcpy(&(block+current_point)->input,&point,2);
					 else
						 mmemcpy(&(block+current_point)->setpoint,&point,2);
*/
					 break;
		case CON_AUTO_MAN:
					 (block+current_point)->auto_manual=automan(!(block+current_point)->auto_manual, buf);
					 PutAlpha(field, buf);
					 break;
		case CON_OUTPUT:
						if( (block+current_point)->auto_manual == AUTO ) break;
						readfloat(field, &(block+current_point)->value, L_CON_OUTPUT-2, 1,NULL,1);
						GetAlpha(field, L_CON_OUTPUT-2, buf);
						strcat(buf, " %");
						PutAlpha(field,buf);
						break;
		case CON_SETPOINTV:
					  readfloat(field, &(block+current_point)->setpoint_value, L_CON_SETPOINTV, 1,NULL,1);
//					  i=(block+current_point)->setpoint;
					  r = (block+current_point)->setpoint.point_type-1;
					  if(local_panel)
					  {
						 if( r == IN )
							  ptr_panel->inputs[(block+current_point)->setpoint.number].value = (block+current_point)->setpoint_value;
						 if( r == VAR )
							  ptr_panel->vars[(block+current_point)->setpoint.number].value = (block+current_point)->setpoint_value;
					  }
					  else
					  {
//						 Str_in_point pinput;
//						 net_call(20+100, i, (char *)&i, 0, ((Point_main_sub *)&i)->main.panel+1);
					  }
					  break;
		case CON_ACTION:
							if ((block+current_point)->action)
							{
							 strcpy(buf,"+");
							 (block+current_point)->action = 0;
							}
							else
							{
							 strcpy(buf,"-");
							 (block+current_point)->action = 1;
							}

							if(local_panel)
							{
							 if(ptr_panel->controllers[current_point].auto_manual==AUTO)
							  if(!ptr_panel->controllers[current_point].input.zero())
							  {
								ptr_panel->controllers[current_point].action=(block+current_point)->action;
								ptr_panel->con_aux[current_point].error_area = 0;
//								ptr_panel->Controller(current_point);
								(block+current_point)->value=ptr_panel->controllers[current_point].value;
								GetField(CON_OUTPUT, buf);
							  }
							}
							PutAlpha(field, buf);
							break;
		case CON_PROP:
						 int pr;
						 pr = ((block+current_point)->prop_high<<8) + (block+current_point)->proportional;
						 readint(field, &pr,  L_CON_PROP, NULL, 2, 0, 4000);
						 (block+current_point)->prop_high = ((pr>>8)&0x0F);
						 (block+current_point)->proportional = pr&0x0FF;
						 break;
		case CON_RESET:
						 int v;
						 v=(int)(block+current_point)->reset;
						 readint(field, &v,  L_CON_RESET, NULL, 2, 0, 255);
						 (block+current_point)->reset = (char)v;
						 break;
		case CON_RATE:
//						 float f;
						 long f;
//						 f = (float)(block+current_point)->rate / 100;
						 f = (long)(block+current_point)->rate / 100;
						 readfloat(field, &f, L_CON_RATE, 2, NULL,2, 0, 2.00);
						 (block+current_point)->rate = (char)(f * 100 / 1000);
						 break;
		case CON_BIAS:
							v=(int)(block+current_point)->bias;
							readint(field, &v,  L_CON_BIAS, NULL, 2, 0, 100);
							(block+current_point)->bias = (char)v;
						 break;
		}
	pgrid->GGPutField(field,Lightgray,Black);
	pgrid->modify = TRUE;
 }
}


int Controller_block::GetRec(void)
{
	int i ;
	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,'\0',sizeof(struct CON_LineBuf));

	for(i=0; i<fields_number; i++)
	{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
	}
	return FX_SUCCESS;
}

int Controller_block::GetField(int field, char *buf)
{
	int l;

	l=0;
	switch (field) {
		case CON_NUM:
		case CON_NUM1:
				 nr_point(buf);
				 break;
		case CON_INPUT:
					 getpoint(field, (block+current_point)->input, buf, 0);
					 break;
		case CON_INUNITS:
		case CON_UNITS:
					 int r;
					 l = (block+current_point)->input.point_type+1;
					 r = GetRange_In((block+current_point)->units);
					 if( r < DIG1 )
					 {
						memcpy(buf, in_range_array[r].aunits,L_CON_INUNITS);
					 }
					 else
					 {
						memcpy(buf, "     ", L_CON_INUNITS);
					 }
					 lalign(buf, L_CON_INUNITS);
					 l=L_CON_INUNITS;
					break;
		case CON_SETPOINT:
					 getpoint(field, (block+current_point)->setpoint, buf, 0);
					 break;
		case CON_AUTO_MAN:
						automan((block+current_point)->auto_manual, buf);
						l=L_CON_AUTO_MAN;
				 break;
		case CON_OUTPUT:
						 readfloat(field, &(block+current_point)->value, L_CON_OUTPUT-2, 1, buf, 0);
						 GetAlpha(field, L_CON_OUTPUT-2, buf);
						 strcat(buf, " %");
						 PutAlpha(field,buf);
						 break;
		case CON_SETPOINTV:
//						char control;
//						int range = GetRange();
						 readfloat(field, &(block+current_point)->setpoint_value, L_CON_SETPOINTV, 1, buf, 0);
						 break;
		case CON_ACTION:
							if ((block+current_point)->action)
							{
							 strcpy(buf,"-");
							}
							else
							{
							 strcpy(buf,"+");
							}
						 break;
		case CON_PROP:
						 int pr;
						 pr = ((block+current_point)->prop_high<<8) + (block+current_point)->proportional;
						 readint(field, &pr,  L_CON_PROP, buf, 0);
						 break;
		case CON_RESET:
						 int v;
						 v=(int)(block+current_point)->reset;
						 readint(field, &v,  L_CON_RESET, buf, 0);
						 break;
		case CON_RATE:
//						 float f;
						 long f;
						 f = (long)(block+current_point)->rate / 100 * 1000L;
						 readfloat(field, &f, L_CON_RATE, 2, buf,0);
						 break;
		case CON_BIAS:
						 {
							int v;
							v=(int)(block+current_point)->bias;
							readint(field, &v,  L_CON_BIAS, buf, 0);
						 }
						 break;
		case CON_VALUE:
					{
					 readfloat(field, &(block+current_point)->input_value, L_CON_VALUE, 1, buf,0);
				 }
					break;
		}

 return l;
}

void alarm_routine(void)
{
				 char t[10];
				 GGrid p(mode_text?2:2,mode_text?3:30,mode_text?79:637,mode_text?3+16+2:425,GRID,NULL,ALARMM,STANDARD,Station_NUM,0,0);
				 p.GWSet(NULL,Lightgray,Darkgray);
				 if(!mode_text)
					 p.save=0;
				 nothing = 0;
				 p.GShowGrid();
				 while (!p.HandleEvent());
				 nothing = 1;
}

//**********************************
//    class Weekly_routine_block
//**********************************

Weekly_routine_block::Weekly_routine_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				 :Block(pthis, pt, p, net, type, pnum, N_WR, (char *)&line_buf)
{
			int npoint=0;
			if(type==INDIVIDUAL)
			{
				number_of_points=1;           //MAX_OUTPUT;
				npoint =  pnum-1;                // num_point
			}
			else
			{
				if(maxtbl)
				{
				 number_of_points=maxtbl;           //MAX_OUTPUT;
				 maxtbl = 0;
				}
				else
					number_of_points=tbl_bank[WR];           //MAX_OUTPUT;
			}
			set_semaphore_dos();
			block=new Str_weekly_routine_point[number_of_points];
			clear_semaphore_dos();
//			if((local_panel &&  type!=INDIVIDUAL) || (type==INDIVIDUAL && p==Station_NUM))
			if( local_request(p, net) )
				memmove(block,&ptr_panel->weekly_routines[npoint],number_of_points*sizeof(Str_weekly_routine_point));
			else
				memset(block,'\0',number_of_points*sizeof(Str_weekly_routine_point));
			r.RecStruct(N_WR,wr_struct);
			h.HSet(N_WR,r.RecStruct(1),number_of_points);
}

Weekly_routine_block::~Weekly_routine_block()
{
 set_semaphore_dos();
 delete [] block;
 clear_semaphore_dos();
}


void weekly_routine(int current_point,int panel,int network,int type)
{
				 char t[10];
//				 GGrid *p;
//				 set_semaphore_dos();
//				 p=new GGrid(9,9,73,9+8+2,GRID,NULL,WR_TIME,current_point+1,panel,sub_panel,net_type);
//				 clear_semaphore_dos();
				 GGrid *p=NULL;
				 p = new GGrid(mode_text?9:52,mode_text?9:100,mode_text?73:588,mode_text?9+8+2:333,GRID,NULL,WR_TIME,T3000,panel,network,type,current_point,SMALL_FONT,5,1);
				 if(!p->grid_error)
				 {
				  strcpy(t,"WR");
				  itoa(current_point, &t[2], 10);
				  p->GWSet(t,Lightgray,Darkgray);
				  if(!mode_text)
					 p->save=0;
				  nothing = 0;
				  p->GShowGrid();
					while (!p->HandleEvent());
					nothing = 1;
//				 set_semaphore_dos();
//				 delete p;
//				 clear_semaphore_dos();
						 }
				 if(p) delete p;
}

int Weekly_routine_block::Read(int field, char key)
{
 char buf[50],l;
	if(key==INSERT)
	{
//				 weekly_routine(current_point,pgrid->Gpanel,pgrid->Gnetwork,pgrid->Gtype,pgrid->Gpoint_num);
				 weekly_routine( (type==INDIVIDUAL)?point_number:current_point+1,pgrid->Gpanel,pgrid->Gnetwork,INDIVIDUAL);
//				 pgrid->modify = FALSE;
//				 refresh_table[pgrid->w_record-1] = 0;
	}
	else
	{
	 switch (field) {
		case WR_NUM:
		case WR_OR1VALUE:
		case WR_OR2VALUE:
						break;
		case WR_FULL_LABEL:
					 getalpha(field, (block+current_point)->description, L_WR_FULL_LABEL);
					 break;
		case WR_LABEL:
					 getalpha(field, (block+current_point)->label, L_WR_LABEL);
					 break;
		case WR_AUTO_MAN:
					 (block+current_point)->auto_manual=automan(!(block+current_point)->auto_manual, buf);
					 PutAlpha(field, buf);
					 refresh_time = 0;
					 break;
		case WR_VALUE:
					 if( (block+current_point)->auto_manual == MAN )
					 {
						(block+current_point)->value=onoff(!(block+current_point)->value, buf);
						PutAlpha(field, buf);
					 }
					 break;
		case WR_OVERRIDE1:
					 getpoint(field, (block+current_point)->override_1, (char *)&(block+current_point)->override_1, 1);
					 break;
		case WR_OVERRIDE2:
					 getpoint(field, (block+current_point)->override_2, (char *)&(block+current_point)->override_2, 1);

/*						Point_main_sub point;
							 if (field==WR_OVERRIDE1)
									memcpy(&point,&(block+current_point)->override_1,2);
							 else
									memcpy(&point,&(block+current_point)->override_2,2);
					 GetAlpha(field, MAX_ALPHA, buf);
					 pgrid->GDGets(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
					 look(buf,&point,panel_type,net_type,panel,sub_panel);
					 ralign(lalign(buf,L_WR_OVERRIDE1),L_WR_OVERRIDE1);
					 PutAlpha(field, buf);
					 if (field==WR_OVERRIDE1)
						 memcpy(&(block+current_point)->override_1,&point,2);
					 else
						 memcpy(&(block+current_point)->override_2,&point,2);
					 l=L_WR_OVERRIDE2;
*/
					 break;
			}
	  pgrid->GGPutField(field,Lightgray,Black);
	  pgrid->modify = TRUE;
	}
}


int Weekly_routine_block::GetRec(void)
{
	int i;
	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,'\0',sizeof(struct WR_LineBuf));

	for(i=0; i<fields_number; i++)
	{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
	}
	return FX_SUCCESS;
}

int Weekly_routine_block::GetField(int field, char *buf)
{
	int l;

	l=0;
	switch (field) {
		case WR_NUM:
				 nr_point(buf);
				 break;
		case WR_FULL_LABEL:
						memcpy(buf , lalign((block+current_point)->description,L_WR_FULL_LABEL),L_WR_FULL_LABEL);
						l=L_WR_FULL_LABEL;
				 break;
		case WR_AUTO_MAN:
					 automan((block+current_point)->auto_manual, buf);
					 l=L_WR_AUTO_MAN;
				 break;
		case WR_VALUE:
					 onoff((block+current_point)->value, buf);
					 break;
		case WR_OVERRIDE1:
					 getpoint(field, (block+current_point)->override_1, buf, 0);
					 l=L_WR_OVERRIDE1;
					 break;
		case WR_OVERRIDE2:
					 getpoint(field, (block+current_point)->override_2, buf, 0);
/*
					 Point_main_sub point;
							 if (field==WR_OVERRIDE1)
									memcpy(&point,&(block+current_point)->override_1,2);
							 else
									memcpy(&point,&(block+current_point)->override_2,2);

					 if (!pointtotext(buf,&point,panel_type))
//						 findlabel(panel_type, net_type, panel, point, buf);
					 ralign(lalign(buf,L_WR_OVERRIDE1),L_WR_OVERRIDE1);
*/
					 l=L_WR_OVERRIDE2;
					 break;
		case WR_OR1VALUE:
					 onoff((block+current_point)->override_1_value, buf);
					 break;
		case WR_OR2VALUE:
					 onoff((block+current_point)->override_2_value, buf);
					 break;
		case WR_LABEL:
						char *p=lalign((block+current_point)->label,L_WR_LABEL);
						memcpy(buf , p,L_WR_LABEL);
						l=L_WR_LABEL;
				 break;
		}

 return l;
}



//**********************************
//    class Weekly_routine_time_block
//**********************************

Weekly_routine_time_block::Weekly_routine_time_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				 :Block(pthis, pt, p, net, type, pnum, N_WR_TIME, (char *)&line_buf)
{
			routine_num=pnum;
			wr_day=(Wr_one_day *)&block[0][0];
			number_of_days=9;           //
			number_of_points=8;           //MAX_WRPUT;
//			if((local_panel &&  type!=INDIVIDUAL) || (type==INDIVIDUAL && p==Station_NUM))
			if( local_request(p, net) )
				memmove(block,&ptr_panel->wr_times[routine_num-1][0],9*sizeof(Wr_one_day));
			else
			  memset(block,'\0',9*sizeof(Wr_one_day));
			r.RecStruct(N_WR_TIME,wr_time_struct);
			h.HSet(N_WR_TIME,r.RecStruct(1),number_of_points);
}

Weekly_routine_time_block::~Weekly_routine_time_block()
{
}


int Weekly_routine_time_block::Read(int field, char key)
{
 char buf[50],l;
 if(key==INSERT)
 {
 }
 else
 {
	switch (field) {
		case WR_TIME0:
						break;
		case WR_TIME_MON:
		case WR_TIME_TUE:
		case WR_TIME_WED:
		case WR_TIME_THU:
		case WR_TIME_FRI:
		case WR_TIME_SAT:
		case WR_TIME_SUN:
		case WR_TIME_OR1:
		case WR_TIME_OR2:
//						char seconds ;
					{
					 modify_child=1;
					 int min, hour;
					 modify_monitor=1;
					 min = (int)block[field-2][2*current_point];
					 hour = (int)block[field-2][2*current_point+1];
					 readinterval(field, buf, NULL ,&min,&hour );
					 block[field-2][2*current_point]=min;
					 block[field-2][2*current_point+1]=hour;
					 PutAlpha(field, buf);
					}
//						memcpy(buf,intervaltotext( 0 , block[field-2][2*current_point],block[field-2][2*current_point+1] ),5);
//						buf[5]=0;
//						pgrid->GDGets(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
//						texttointerval( buf, &seconds , &block[field-2][2*current_point],&block[field-2][2*current_point+1] );
//						memcpy(buf,intervaltotext( 0 , block[field-2][2*current_point],block[field-2][2*current_point+1] ),5);
//						PutAlpha(field, buf);
						break;
			}
	pgrid->GGPutField(field,Lightgray,Black);
	pgrid->modify = TRUE;
 }
}


int Weekly_routine_time_block::GetRec(void)
{
	int i;
	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,'\0',sizeof(struct WR_TIME_LineBuf));

	for(i=0; i<fields_number; i++)
	{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
	}
	return FX_SUCCESS;
}

int Weekly_routine_time_block::GetField(int field, char *buf)
{
	int l;

	l=0;
	switch (field) {
		case WR_TIME0:
						if (current_point%2)
							 strcpy(buf,(char *)off);
						else
							 strcpy(buf,(char *)on);
						break;
		case WR_TIME_MON:
		case WR_TIME_TUE:
		case WR_TIME_WED:
		case WR_TIME_THU:
		case WR_TIME_FRI:
		case WR_TIME_SAT:
		case WR_TIME_SUN:
		case WR_TIME_OR1:
		case WR_TIME_OR2:
						if (block[field-2][2*current_point]+block[field-2][2*current_point+1])
								memcpy(buf,intervaltotext( NULL, 0 , block[field-2][2*current_point],block[field-2][2*current_point+1]),5);
						else
								memcpy(buf,nulbuf,5);
						break;
			}

 return l;
}


//**********************************
//    class Annual_routine_block
//**********************************

Annual_routine_block::Annual_routine_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				 :Block(pthis, pt, p, net, type, pnum, N_AR, (char *)&line_buf)
{
			int npoint=0;
			if(type==INDIVIDUAL)
			{
				number_of_points=1;           //MAX_OUTPUT;
				npoint = pnum-1;                // num_point
			}
			else
			{
				if(maxtbl)
				{
				 number_of_points=maxtbl;           //MAX_OUTPUT;
				 maxtbl = 0;
				}
				else
					number_of_points=tbl_bank[AR];
			}
			set_semaphore_dos();
			block=new Str_annual_routine_point[number_of_points];
			clear_semaphore_dos();
//			if((local_panel &&  type!=INDIVIDUAL) || (type==INDIVIDUAL && p==Station_NUM))
			if( checklocal() )
				memmove(block,&ptr_panel->annual_routines[npoint],number_of_points*sizeof(Str_annual_routine_point));
			else
				memset(block,'\0',number_of_points*sizeof(Str_annual_routine_point));
			r.RecStruct(N_AR,ar_struct);
			h.HSet(N_AR,r.RecStruct(1),number_of_points);
}

Annual_routine_block::~Annual_routine_block()
{
 set_semaphore_dos();
 delete [] block;
 clear_semaphore_dos();
}

void annual_routine(int current_point,int panel,int network,int type)
{
				 char t[10];
//				 GGrid *p;
//				 set_semaphore_dos();
//				 p=new GGrid(5,9,74,9+7+2,GRID,NULL,AR_Y,current_point+1,panel,sub_panel,net_type);
//				 clear_semaphore_dos();
				 GGrid *p=NULL;
				 p = new GGrid(mode_text?5:40,mode_text?9:100,mode_text?74:598,mode_text?9+7+2:318,GRID,NULL,AR_Y,T3000,panel,network,type,current_point,SMALL_FONT,5,1);
				 if(!p->grid_error)
				 {
					strcpy(t,"AR");
				  itoa(current_point, &t[2], 10);
				  p->GWSet(t,Lightgray,Darkgray);
				  if(!mode_text)
					 p->save=0;
				  nothing = 0;
				  p->GShowGrid();
//				 p->obj.ar_y->ShowDates(p->obj.ar_y->quarter);

				  mxyputs(p->GWRetLimits(0)+1,p->GWRetLimits(1)+1,&months[0][0],Lightgray,Black);
				  p->obj.ar_y->ShowDates(p->obj.ar_y->quarter);
//				 p->obj.ar_y->current_point=0;
				  while (!p->HandleEvent());
//				 set_semaphore_dos();
//				 delete p;
//				 clear_semaphore_dos();
				  nothing = 0;
//				 mtextbackground(Lightgray);
				 }
				 if(p) delete p;
}

int Annual_routine_block::Read(int field, char key)
{
 char buf[50],l;
	if(key==INSERT)
		{
//				 annual_routine(current_point,pgrid->Gpanel,pgrid->Gtype,pgrid->Gpoint_num);
				 annual_routine(current_point+1,pgrid->Gpanel,pgrid->Gnetwork,INDIVIDUAL);
//				 pgrid->modify = FALSE;
//				 refresh_table[pgrid->w_record-1] = 0;
		}
	else
	{
	 switch (field) {
		case AR_NUM:
						break;
		case AR_FULL_LABEL:
					 getalpha(field, (block+current_point)->description, L_AR_FULL_LABEL);
					 break;
		case AR_LABEL:
					 getalpha(field, (block+current_point)->label, L_AR_LABEL);
					 break;
		case AR_AUTO_MAN:
						(block+current_point)->auto_manual=automan(!(block+current_point)->auto_manual, buf);
					 PutAlpha(field, buf);
					 refresh_time = 0;
					 break;
		case AR_VALUE:
					 (block+current_point)->value=onoff(!(block+current_point)->value, buf);
					 PutAlpha(field, buf);
					 break;
			}
	 pgrid->GGPutField(field,Lightgray,Black);
	 pgrid->modify = TRUE;
  }
}


int Annual_routine_block::GetRec(void)
{
	int i;

	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,'\0',sizeof(struct AR_LineBuf));

	for(i=0; i<fields_number; i++)
	{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
	}
	return FX_SUCCESS;
}

int Annual_routine_block::GetField(int field, char *buf)
{
	int l;

	l=0;
	switch (field) {
		case AR_NUM:
				 nr_point(buf);
				 break;
		case AR_FULL_LABEL:
						memcpy(buf , lalign((block+current_point)->description,L_AR_FULL_LABEL),L_AR_FULL_LABEL);
						l=L_AR_FULL_LABEL;
					 break;
		case AR_AUTO_MAN:
						automan((block+current_point)->auto_manual, buf);
						l=L_AR_AUTO_MAN;
				 break;
		case AR_VALUE:
					 onoff((block+current_point)->value, buf);
					 break;
		case AR_LABEL:
					 char *p=lalign((block+current_point)->label,L_AR_LABEL);
					 memcpy(buf , p,L_AR_LABEL);
					 l=L_AR_LABEL;
					 break;
		}

 return l;
}


//**********************************
//    class Annual_routine_time_block
//**********************************

Annual_routine_time_block::Annual_routine_time_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				 :Block(pthis, pt, p, net, type, pnum, N_Y_AR, (char *)&line_buf)
{
			routine_num=pnum;
			block=block_year;
//			AR_day=(AR_one_day *)&block[0][0];
			quarter=0;           //
			number_of_points=7;           //MAX_ARPUT;
//			if((local_panel &&  type!=INDIVIDUAL) || (type==INDIVIDUAL && p==Station_NUM))
			if( checklocal() )
				memmove(block_year,&ptr_panel->ar_dates[routine_num-1][0],46);
			else
				memset(block_year,'\0',46);
			memset(year,'\0',6*7*3);
			r.RecStruct(N_Y_AR,ar_y_struct);
			h.HSet(N_Y_AR,r.RecStruct(1),number_of_points);
			struct tm time_check;
			int i;
/*  load the time_check structure with the data */
						 for(byte mon=0;mon<3;mon++)
							{
							 time_check.tm_year = ora_current.year;
							 time_check.tm_mon  = mon;
							 time_check.tm_mday = 1;
							 time_check.tm_hour = 0;
							 time_check.tm_min  = 0;
							 time_check.tm_sec  = 1;
							 time_check.tm_isdst = -1;
							 set_semaphore_dos();
							 if (mktime(&time_check) == -1)
									time_check.tm_wday = 7;
							 clear_semaphore_dos();
							 i=mon*6*7+time_check.tm_wday;

/*  call mktime to fill in the weekday field of the structure */

							for (byte day=1;day<=month_days[mon];day++)
								 year[i++]=day;
							}
}





Annual_routine_time_block::~Annual_routine_time_block()
{
}

int Annual_routine_time_block::ShowDates(byte quarter)
{
 char buf[5];          //,xbuf[6];
	for(current_point=1;current_point<7;current_point++)
	 {
	 GetRec();
	 for(int field=1;field<=N_Y_AR;field++)
		{
		switch (field) {
			case AR1_Y_SP:
			case AR2_Y_SP:
			case AR3_Y_SP:
								break;
			default:
							int i=field/8;
							if(year[(current_point/7)*126+(current_point%7-1)*7+i*42+field%8-1])
							{
//								memcpy(buf,ralign(itoa(year[(current_point/7)*126+(current_point%7-1)*7+i*42+field%8-1],xbuf,10),2),2) ;
								itoa(year[(current_point/7)*126+(current_point%7-1)*7+i*42+field%8-1],buf,10);
								ralign(buf,2);
								struct tm time_check;

/*  load the time_check structure with the data */
							 if(year[(current_point/7)*126+(current_point%7-1)*7+i*42+field%8-1]==29 && quarter*3+field/8 == 1) continue;
							 time_check.tm_year = ora_current.year;
							 time_check.tm_mon  = quarter*3+field/8;
							 time_check.tm_mday = year[(current_point/7)*126+(current_point%7-1)*7+i*42+field%8-1];
							 time_check.tm_hour = 0;
							 time_check.tm_min  = 0;
							 time_check.tm_sec  = 1;
							 time_check.tm_isdst = -1;
							 set_semaphore_dos();
							 if (mktime(&time_check) == -1)
									time_check.tm_wday = 7;
							 clear_semaphore_dos();
//							 if(time_check.tm_yday>58) time_check.tm_yday++;
							 int n=time_check.tm_yday/8;
							 char m = 1;
							 m <<= time_check.tm_yday%8;
							 if (block_year[n] & m)
									{
									 pgrid->w_record=current_point+1;
									 pgrid->GGPutField(field,Cyan,Black);
									}
							}
//							else
//								mmemcpy(buf,nulbuf,2);
					break;

		 }
	 }
	}
//mtextbackground(Lightgray);
pgrid->w_record=1;
}

int Annual_routine_time_block::Quarter(byte quarter)
{
 char buf[50],l,col,col1;  //xbuf[4];
 col=Black;
 col1=Lightgray;
					struct tm time_check;
					int i;
/*  load the time_check structure with the data */
					memset(year,'\0',6*7*3);
					for(byte mon=quarter*3;mon<(quarter+1)*3;mon++)
					{
							 time_check.tm_year = ora_current.year;
							 time_check.tm_mon  = mon;
							 time_check.tm_mday = 1;
							 time_check.tm_hour = 0;
							 time_check.tm_min  = 0;
							 time_check.tm_sec  = 1;
							 time_check.tm_isdst = -1;
							 set_semaphore_dos();
							 if (mktime(&time_check) == -1)
									time_check.tm_wday = 7;
							 clear_semaphore_dos();
							 i=(mon%3)*6*7+time_check.tm_wday;

/*  call mktime to fill in the weekday field of the structure */

							for (byte day=1;day<=month_days[mon];day++)
								 year[i++]=day;
					}
					pgrid->w_urecord = 1;
					pgrid->w_record = 1;
					pgrid->w_field = 1;
					pgrid->w_nfields = 0;
}

int Annual_routine_time_block::Read(int field, char key)
{
 char buf[50],l,col,col1;  //xbuf[4];
 col=Black;
 col1=Lightgray;
	if(key==118 || key==132 || key==81 || key==73)      //CTRL/PgDn
	{
				 if((key==118 || key==81) && quarter!=3)
						 quarter++;
				 if((key==132 || key==73) && quarter!=0)
						 quarter--;
						 struct tm time_check;
						 int i;
/*  load the time_check structure with the data */
						 memset(year,'\0',6*7*3);
						 for(byte mon=quarter*3;mon<(quarter+1)*3;mon++)
							{
							 time_check.tm_year = ora_current.year;
							 time_check.tm_mon  = mon;
							 time_check.tm_mday = 1;
							 time_check.tm_hour = 0;
							 time_check.tm_min  = 0;
							 time_check.tm_sec  = 1;
							 time_check.tm_isdst = -1;
							 set_semaphore_dos();
							 if (mktime(&time_check) == -1)
									time_check.tm_wday = 7;
							 clear_semaphore_dos();
							 i=(mon%3)*6*7+time_check.tm_wday;

/*  call mktime to fill in the weekday field of the structure */

							for (byte day=1;day<=month_days[mon];day++)
								 year[i++]=day;
							}
					pgrid->w_urecord = 1;
					pgrid->w_record = 1;
					pgrid->w_field = 1;
					pgrid->w_nfields = 0;
//					t_fields[w_field-1]=1;
					pgrid->GGDrawGrid(Black);
					pgrid->w_field = 1; pgrid->w_record = 1;
					pgrid->GGShowCur(Black);

//				 p->GShowGrid();
//				 gotoxy(pgrid->GWRetLimits(0)+1,pgrid->GWRetLimits(1)+1);
				 mxyputs(pgrid->GWRetLimits(0)+1,pgrid->GWRetLimits(1)+1,&months[quarter][0],Lightgray,Black);
//				 cputs(&months[quarter][0]);
				 ShowDates(quarter);
	}
	else
	{
	if (current_point!=0)
		switch (field) {
			case AR1_Y_SP:
			case AR2_Y_SP:
			case AR3_Y_SP:
								break;
			default:
							modify_child=1;
							int i=field/8;
							if(year[(current_point/7)*126+(current_point%7-1)*7+i*42+field%8-1])
							{
//							 memcpy(buf,ralign(itoa(year[(current_point/7)*126+(current_point%7-1)*7+i*42+field%8-1],xbuf,10),2),2) ;
							 itoa(year[(current_point/7)*126+(current_point%7-1)*7+i*42+field%8-1],buf,10);
							 ralign(buf,2);
							 struct tm time_check;

/*  load the time_check structure with the data */
							 if(year[(current_point/7)*126+(current_point%7-1)*7+i*42+field%8-1]==29 && quarter*3+field/8 == 1) break;
							 time_check.tm_year = ora_current.year;
							 time_check.tm_mon  = quarter*3+field/8;
							 time_check.tm_mday = year[(current_point/7)*126+(current_point%7-1)*7+i*42+field%8-1];
							 time_check.tm_hour = 0;
							 time_check.tm_min  = 0;
							 time_check.tm_sec  = 1;
							 time_check.tm_isdst = -1;
							 set_semaphore_dos();
							 if (mktime(&time_check) == -1)
									time_check.tm_wday = 7;
							 clear_semaphore_dos();
//							 if(time_check.tm_yday>58) time_check.tm_yday++;
							 int n=time_check.tm_yday/8;
							 char m = 1;
							 m <<= time_check.tm_yday%8;
							 if (!(block_year[n] & m))
									{
									 block_year[n] |= m;
//									mtextbackground(Cyan);
									 col=Cyan;
									 col1=col;
									}
							 else
								 {
									block_year[n] &= ~m;
								 }
							 pgrid->GGPutField(field,col1,Black);
										 pgrid->modify = TRUE;
//							 mtextbackground(Lightgray);
							}
//							else
//								mmemcpy(buf,nulbuf,2);

						break;
		}
	}
return col;
}


int Annual_routine_time_block::GetRec(void)
{
	int i;
	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,'\0',sizeof(struct AR_Y_LineBuf));

	for(i=0; i<fields_number; i++)
	{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
	}
	return FX_SUCCESS;
}

int Annual_routine_time_block::GetField(int field, char *buf)
{
	int l;

	l=0;
	if (current_point==0 || current_point==7 || current_point==14 || current_point==21)
		switch (field) {
			case AR1_Y_SUN:
			case AR2_Y_SUN:
			case AR3_Y_SUN:
							strcpy(buf,(char *)sun);
							break;
			case AR1_Y_MON:
			case AR2_Y_MON:
			case AR3_Y_MON:
							strcpy(buf,(char *)mon);
							break;
			case AR1_Y_TUE:
			case AR2_Y_TUE:
			case AR3_Y_TUE:
							strcpy(buf,(char *)tue);
							break;
			case AR1_Y_WED:
			case AR2_Y_WED:
			case AR3_Y_WED:
							strcpy(buf,(char *)wed);
							break;
			case AR1_Y_THU:
			case AR2_Y_THU:
			case AR3_Y_THU:
							strcpy(buf,(char *)thu);
							break;
			case AR1_Y_FRI:
			case AR2_Y_FRI:
			case AR3_Y_FRI:
							strcpy(buf,(char *)fri);
							break;
			case AR1_Y_SAT:
			case AR2_Y_SAT:
			case AR3_Y_SAT:
							strcpy(buf,(char *)sat);
							break;
			case AR1_Y_SP:
			case AR2_Y_SP:
			case AR3_Y_SP:
							memcpy(buf,nulbuf,1);
							break;
		 }
	else
	switch (field) {
		case AR1_Y_SP:
		case AR2_Y_SP:
		case AR3_Y_SP:
							memcpy(buf,nulbuf,1);
							break;
		default:
							int i=field/8;
							if(year[(current_point/7)*126+(current_point%7-1)*7+i*42+field%8-1])
							{
//								memcpy(buf,ralign(itoa(year[(current_point/7)*126+(current_point%7-1)*7+i*42+field%8-1],xbuf,10),2),2) ;
								itoa(year[(current_point/7)*126+(current_point%7-1)*7+i*42+field%8-1],buf,10);
								ralign(buf,2);
							}
							else
								memcpy(buf,nulbuf,2);

							break;
		}
 return l;
}



//**********************************
//    class Program_block
//**********************************

Program_block::Program_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				 :Block(pthis, pt, p, net, type, pnum, N_PRG, (char *)&line_buf)
{
		 int npoint=0;
		 if(type==INDIVIDUAL)
		 {
				number_of_points=1;           //MAX_OUTPUT;
				npoint = pnum-1;                // num_point
		 }
		 else
		 {
				if(maxtbl)
				{
				 number_of_points=maxtbl;           //MAX_OUTPUT;
				 maxtbl = 0;
				}
				else
					number_of_points=tbl_bank[PRG];
		 }
		 set_semaphore_dos();
		 block=new Str_program_point[number_of_points];
		 clear_semaphore_dos();
//		 if((local_panel && type!=INDIVIDUAL) || (type==INDIVIDUAL && p==Station_NUM))
		 if( checklocal() )
				memmove(block,&ptr_panel->programs[npoint],number_of_points*sizeof(Str_program_point));
		 else
				memset(block,'\0',number_of_points*sizeof(Str_program_point));
			r.RecStruct(N_PRG,prg_struct);
			h.HSet(N_PRG,r.RecStruct(1),number_of_points);
}

Program_block::~Program_block()
{
	set_semaphore_dos();
	delete [] block;
	clear_semaphore_dos();
}

int edit_program(Str_program_point *block, int current_point, int panel, int network)
{
	asm push es;
		 unsigned t[2];
		 DORU_SYSTEM=1;
		 set_semaphore_dos();
		 char *code = new char [PROGRAM_SIZE];
		 clear_semaphore_dos();


	 int ret=0;
	 if(!block->bytes)
	 {
		memset(code, 0, 20);
		code[2]=0xfe;
	 }
//	 if(local_panel && panel==Station_NUM)
	 if( local_request(panel, network) )
	 {
			movedata(FP_SEG(ptr_panel->program_codes[current_point]),FP_OFF(ptr_panel->program_codes[current_point]) ,FP_SEG(code),FP_OFF(code), block->bytes);
			t[0]=MAX_HEAP_BUF;
			t[1]=programs_size;
	 }
	 else
	 {
			 GWindow D(mode_text?20:200, mode_text?7:150, mode_text?60:500, mode_text?11:200, NO_STACK,0);
			 DisplayMessageT(20, 8, 60, 12,  ctrlbreak_text,"   Reading program...   ", NULL, Black, &D);
			 Delay(100);
			 NotResponse1=0;
			 ret=net_call(READPROGRAMCODE_T3000, current_point, code, 0, panel, network,NETCALL_SIGN, TIMEOUT_NETCALL, (char *)&t[0]);
			 NotResponse1=1;
			 D.GReleaseWindow();
	 }

	 if(!ret)
	 {
		 GEdit *e;
		 e=new GEdit(1,1,80,24,0, code, ptr_panel->code_length, block, current_point, panel, network);
		 e->GWSet("",Blue,Cyan);
		 e->GShowWindow(0);
		 e->pool_size = t[0];
		 e->total_programs_size = t[1];
		 e->GEditSet("",Blue,Blue);
		 while (!e->HandleEvent());
		 delete e;
	 }

	 set_semaphore_dos();
	 delete code;    // daca new 2000
	 clear_semaphore_dos();

	 if (ret)
	 {
		asm pop es;
		return 1;
	 }
	 asm pop es;
	 return 0;
}

int Program_block::Read(int field, char key)
{
 unsigned int i, prg_point;
 char buf[50],l;
 char *p;
 if(key==INSERT)
 {
		 int old_mode=MODE_TEXT;
		 if(!mode_text)
			{
			 old_mode=mode_text;
			 ptr_panel->go_text();
			}

		 edit_program(block+current_point, current_point, panel, network);
//		 modify_child=1;
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
	switch (field) {
//		case PRG_PANEL:
//		case PRG_PANEL_TYPE:
//		case PRG_SUB_PANEL:
//		case PRG_TYPE:
//		case PRG_NUM1:
		case PRG_NUM:
						break;
		case PRG_FULL_LABEL:
					 getalpha(field, (block+current_point)->description, L_PRG_FULL_LABEL);
					 break;
		case PRG_LABEL:
					 getalpha(field, (block+current_point)->label, L_PRG_LABEL);
					 break;
		case PRG_STATUS:
					 (block+current_point)->on_off=onoff(!(block+current_point)->on_off, buf);
					 PutAlpha(field, buf);
					 break;
		case PRG_AUTO_MAN:
						(block+current_point)->auto_manual=automan(!(block+current_point)->auto_manual, buf);
					 PutAlpha(field, buf);
					 break;
/*
		case PRG_TIMER:
						l=(block+current_point)->timer_disable;
						if (l==1)
							{
							 strcpy(buf,enabl);
							 l=0;
							}
						else
							{
							 strcpy(buf,disabl);
							 l=1;
							}
					 PutAlpha(field, buf);
						(block+current_point)->timer_disable=l;
							 break;
		case PRG_REPSEC:
		case PRG_REPMIN:
		case PRG_REMSEC:
		case PRG_REMMIN:
							 GetAlpha(field, MAX_ALPHA, buf);
							 pgrid->GDGets(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
							 l = atoi(buf);
							 PutAlpha(field, buf);
								 if (field==PRG_REPSEC)
									 (block+current_point)->repeat_seconds = l;
								 if (field==PRG_REPMIN)
									 (block+current_point)->repeat_minutes = l;
								 if (field==PRG_REMSEC)
									 (block+current_point)->remaining_seconds = l;
								 if (field==PRG_REMMIN)
									 (block+current_point)->remaining_minutes = l;
							 break;
*/
		case PRG_EXIT:
					 (block+current_point)->errcode=0;
					 memcpy(buf , (char *)normal, L_PRG_EXIT);
					 PutAlpha(field, buf);
					 break;

	 }
	 pgrid->GGPutField(field,Lightgray,Black);
	 pgrid->modify = TRUE;
  }
}


int Program_block::GetRec(void)
{
	int i;

	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,'\0',sizeof(struct PRG_LineBuf));

	for(i=0; i<fields_number; i++)
		{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
		}
	return FX_SUCCESS;
}

int Program_block::GetField(int field, char *buf)
{
	int l;

	l=0;
	switch (field) {
//		case PRG_NUM1:
		case PRG_NUM:
				 nr_point(buf);
				 break;
		case PRG_FULL_LABEL:
						memcpy(buf , lalign((block+current_point)->description,L_PRG_FULL_LABEL),L_PRG_FULL_LABEL);
						l=L_PRG_FULL_LABEL;
				 break;
		case PRG_STATUS:
					 if( !(block+current_point)->com_prg )
						 onoff((block+current_point)->on_off, buf);
					 else
					 {
	               strcpy(buf,(char *)com_prg_text);
					 }
					 break;
		case PRG_AUTO_MAN:
						automan((block+current_point)->auto_manual, buf);
						l=L_PRG_AUTO_MAN;
				 break;
/*
		case PRG_TIMER:
						l=(block+current_point)->timer_disable;
						if (l==1)
							 strcpy(buf,disabl);
						else
							 strcpy(buf,enabl);
						l=L_PRG_TIMER;
						 break;
		case PRG_REPSEC:
		case PRG_REPMIN:
		case PRG_REMSEC:
		case PRG_REMMIN:
							 GetAlpha(field, MAX_ALPHA, buf);
					 break;
*/
		case PRG_EXIT:
					 switch( (block+current_point)->errcode ){
					 case 0:
						 memcpy(buf , (char *)normal, L_PRG_EXIT);
						 break;
					 case 1:
						 memcpy(buf , (char *)tout, L_PRG_EXIT);
						 break;
					 case INDEX_OUT_OF_RANGE:
						 memcpy(buf , (char *)tioutrar, L_PRG_EXIT);
						 break;
					 case 3:
						 memcpy(buf , (char *)tioutwar, L_PRG_EXIT);
						 break;
					 case 4:
						 memcpy(buf , (char *)tioutray, L_PRG_EXIT);
						 break;
					 case 5:
						 memcpy(buf , (char *)tioutway, L_PRG_EXIT);
						 break;
					 }
					 l=L_PRG_EXIT;
					 break;
		case PRG_LABEL:
					 char *p;
					 p=lalign((block+current_point)->label,L_PRG_LABEL);
					 memcpy(buf , p,L_PRG_LABEL);
					 l=L_PRG_LABEL;
				 break;
		case PRG_SIZE:
					 readint(field, (int *)&((block+current_point)->bytes),  L_PRG_SIZE, buf, 0);
					 l=L_PRG_SIZE;
				 break;
		}

 return l;
}


//**********************************
//    class Analog_monitor_block
//**********************************

Monitor_block::Monitor_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				 :Block(pthis, pt, p, net, type, pnum, N_AMON, (char *)&line_buf)
	 {
		 int npoint=0;
		 if(type==INDIVIDUAL)
		 {
				number_of_points=1;           //MAX;
				npoint = pnum-1;                // num_point
		 }
		 else
		 {
				if(maxtbl)
				{
				 number_of_points=maxtbl;           //MAX_OUTPUT;
				 maxtbl = 0;
				}
				else
					number_of_points=tbl_bank[AMON];
		 }
		 set_semaphore_dos();
		 block=new Str_monitor_point[number_of_points];
		 clear_semaphore_dos();
//		 if((local_panel &&  type!=INDIVIDUAL) || (type==INDIVIDUAL && p==Station_NUM))
		 if( checklocal() )
			memmove(block,&ptr_panel->analog_mon[npoint],number_of_points*sizeof(Str_monitor_point));
	    else
			memset(block,'\0',number_of_points*sizeof(Str_monitor_point));
		 r.RecStruct(N_AMON,amon_struct);
		 h.HSet(N_AMON,r.RecStruct(1),number_of_points);

//	 initamoninputsscreen();
	 }

int initamoninputsscreen(void)
{
	 memset(amon_inputs,0,sizeof(amon_inputs));
//	 GGrid *pp;
//	 pp=new GGrid(58,3,67,3+16+2,GRID,NULL,AMON_INPUTS,1,1,0,0);
/*
	 GGrid pp(64,3,73,3+((panel_info1.panel_type == MINI_T3000)?8+2:16+2),GRID,NULL,AMON_INPUTS,1,1,0,0);
	 pp.save=0;
	 pp.GWSet(NULL,Lightgray,Darkgray);
	 pp.GShowGrid();
	 pp.GGHideCur(Black);
	 pp.GReleaseWindow();
*/
//	 delete pp;
}

Monitor_block::~Monitor_block()
{
	 set_semaphore_dos();
	 if(block) delete [] block;
	 clear_semaphore_dos();
}

char displayamonunit( signed char l, char *buf )
{
 if(l>2) l=0;
 if(l<0) l=2;
 if (l==0)
	 strcpy(buf,minut);
 if (l==1)
	 strcpy(buf,hours);
 if (l==2)
	 strcpy(buf,days);
 return l;
}

Monitor_block::compute_size(void)
{
					 char buf[20];
					 long sample,l1,interv;
					 if( !(block+current_point)->max_time_length )
					 {
						(block+current_point)->max_time_length = 1000;
						itoa(1000, buf, 10);
						PutAlpha( AMON_LENGTH, buf );
					 }
					 sample=psample(&interv, block+current_point);
					 l1 = (block+current_point)->anum_inputs * 4 * sample+sizeof(Header_amon)+4;
					 if( l1 > amon_file_length)
						{
						 l1 = (amon_file_length-sizeof(Header_amon)-4)/((block+current_point)->anum_inputs * 4L)*interv;
						 sample = l1;
						 while(1)
						 {
							switch ((block+current_point)->unit) {
							 case 0: l1 /= 60L;
											break;
							 case 1: l1 /= 3600L;
											break;
							 case 2: l1 /= 3600L*24L;
											break;
							}
							if( l1 ) break;
//							if( --((signed char)(block+current_point)->unit) < 0 )
							if( (block+current_point)->unit==0 )
							{
//							 (block+current_point)->unit=0;
							 l1 = 1;
							 break;
							}
							else
							 (block+current_point)->unit--;
							l1 = sample;
						 }
						 (block+current_point)->max_time_length = (unsigned char)l1;

//						 sample=psample(&interv, block+current_point);
//						 l1 = (block+current_point)->num_inputs * 4 * sample;

//					 l = (block+current_point)->data_length;
					 itoa(l1,buf,10);
					 ralign(buf,L_AMON_LENGTH);
					 PutAlpha(AMON_LENGTH, buf);

					 (block+current_point)->unit=displayamonunit( (block+current_point)->unit, buf );
					 PutAlpha(AMON_UNITS, buf);

					 sample=psample(&interv, block+current_point);
					 l1 = (block+current_point)->anum_inputs * 4 * sample+sizeof(Header_amon)+4;
					 ltoa(l1,buf,10);
					 ralign(buf,L_AMON_SIZE);
					 PutAlpha(AMON_SIZE, buf);
						}
}

int Monitor_block::Read(int field, char key)
{
 char buf[15], b[10], l;
 char *p;
 int i, j, k, k1, l1, l2, k2, x;
 char test;
 byte var_type,point_type;
 int onet,num_net,num_point,num_panel,r=SUCCESS;

 if(key=='\t')
 {
				pgrid->GGPutRecord(pgrid->w_urecord+pgrid->w_record-1,Lightgray,Blue);
				memcpy(amon_inputs,(block+current_point)->inputs,sizeof(amon_inputs));
				buf[0]=0;
				GGrid *p;
				 if(mode_text)
					 p=new GGrid(64,3,73,3+((panel_info1.panel_type == MINI_T3000)?8+2:16+2),GRID,NULL,AMON_INPUTS,T3000,panel,network,type,(block+current_point)->anum_inputs);
				 else
					 p=new GGrid(500,24,600,29+((panel_info1.panel_type == MINI_T3000)?200+20:360+20),GRID,NULL,AMON_INPUTS,T3000,panel,network,type,(block+current_point)->anum_inputs,SMALL_FONT,5,1);
				 p->GWSet(NULL,Lightgray,Lightgray);
				 p->GShowGrid();
				 while (!p->HandleEvent());
				 delete p;
				for(k=0;k<MAX_POINTS_IN_MONITOR;k++)
				 for(i=0;i<MAX_POINTS_IN_MONITOR;i++)
					if( amon_inputs[i].zero() )
					{
						for(j=i;j<MAX_POINTS_IN_MONITOR-1;j++)
							 amon_inputs[j]=amon_inputs[j+1];
						amon_inputs[MAX_POINTS_IN_MONITOR-1].setzero();
						break;
					}
				 for(i=0;i<MAX_POINTS_IN_MONITOR;i++)
					if( amon_inputs[i].zero() ) break;

				 l1 = i;   //num_inputs new
				 if( l1 > MAX_POINTS_IN_MONITOR)
				 {
					DisplayMessageT(15, 7, 65, 11, NULL, "It's not allowed more than 14 points", NULL, Blue, NULL, 3500);
				 }
				 else
				 {
					if( memcmp(amon_inputs,(block+current_point)->inputs,sizeof(amon_inputs) ) )
					{
					 for(i=0;i<(block+current_point)->num_inputs;i++)
					 {
						if( (block+current_point)->inputs[i].panel+1!=Station_NUM )
						 deleteremotepoint((block+current_point)->inputs[i],(block+current_point)->inputs[i].network);
					 }
					 (block+current_point)->ind_views=0;
					 memset((block+current_point)->views, 0, MAX_VIEWS*sizeof(Views));

					 l2 = (block+current_point)->anum_inputs; //anum_inputs old

// digital la coada
					 Point_Net amon_inputs1[MAX_POINTS_IN_MONITOR], amon_inputs2[MAX_POINTS_IN_MONITOR];
					 byte			 range1[MAX_POINTS_IN_MONITOR],range2[MAX_POINTS_IN_MONITOR];
					 memset(amon_inputs1, 0, sizeof(amon_inputs1) );
					 memset(amon_inputs2, 0, sizeof(amon_inputs2) );
					 memset(range1, 0, MAX_POINTS_IN_MONITOR );
					 memset(range2, 0, MAX_POINTS_IN_MONITOR );
					 Point_info point_info;
					 j = k = k1 = 0;
					 l = SUCCESS;
					 for(i=0;i<l1;i++)
					 {
						point_info.point = amon_inputs[i];

						pointtotext(buf,&point_info.point);
						if (ispoint(buf,&num_point,&var_type, &point_type, &num_panel, &num_net, network, panel, &k2))
						{
						 onet = network;
						 if( local_request(panel,network) )
						 {
							if ( !k2 )
							 if( rs485port!=-1 && ipxport!=-1 )
							 {
								num_net=(( class ConnectionData *)Routing_table[rs485port].ptr)->panel_info1.network;
								network = num_net;
							 }
						 }
/*
				 if( (test=checkpointpresence(num_point,point_type,num_panel,num_net,panel,network))==0 )
						DisplayMessage(20,7,60,11, NULL, panelmis, NULL, Black, NULL, 2500);
				 if(test)
						x = checkmaxpoints(num_point,point_type,num_panel,num_net);
				 else
						x = 128;
*/
//  replaced the above code with next line
						 test=1;
						 x = 256;
						 if(num_point <= x )
						 {
							if ( !k2 ) num_net = 0xFFFF;
							point_info.point.putpoint(num_point-1,point_type+1,num_panel-1,num_net);
//					if(get_point_info(&pgrp->point_info, NULL, NULL, NULL, NULL, 2, network)==SUCCESS )
							if(test)
							{
							 if( (l=get_point_info(&point_info, NULL, NULL, NULL, NULL, 2, num_net==0xFFFF?network:num_net))!= SUCCESS )
								if( (l=get_point_info(&point_info, NULL, NULL, NULL, NULL, 2, num_net==0xFFFF?network:num_net))!= SUCCESS )
								{
								 network=onet;
								 break;
								}
							}
							if( local_request(panel,network) )
							{
							 if( num_panel!=panel )
								updateremotepoint(point_info.point,num_net);
							}

							if( point_info.digital_analog==ANALOG )
							{
							 amon_inputs1[k] = amon_inputs[i];
							 range1[k]       = point_info.units;
							 k++;
							}
							else
							{
							 amon_inputs2[k1] = amon_inputs[i];
							 range2[k1]       = point_info.units;
							 k1++;
							}
						 }
						 else
						 {
							network=onet;
							break;
						 }
						 network=onet;
						}
					 }

					 l2 = k;
					 if (l==SUCCESS)
					 {
						if( k1 > 10)
						{
						 DisplayMessageT(15, 7, 65, 11, NULL, "It's not allowed more than 10 digital points", NULL, Blue, NULL, 3500);
						}
						else
						{
						 (block+current_point)->anum_inputs=l2;
						 (block+current_point)->num_inputs = l1;
						 memcpy((block+current_point)->inputs,amon_inputs1,sizeof(amon_inputs1));
						 memcpy(&(block+current_point)->inputs[l2],amon_inputs2,(MAX_POINTS_IN_MONITOR-l2)*sizeof(Point_Net) );
						 memcpy((block+current_point)->range,range1,MAX_POINTS_IN_MONITOR);
						 memcpy(&(block+current_point)->range[l2],range2,(MAX_POINTS_IN_MONITOR-l2));
						 compute_size();
						}
						pgrid->modify = TRUE;
					 }
					}
			   }
 }
 else
	 if(key==INSERT)
	 {
		amon_routine(current_point+1,panel,network,0,0,pgrid);
			pgrid->modify = TRUE;
	 }
	 else
	 {
		switch (field) {
		case AMON_NUM:
						break;
		case AMON_LABEL:     //modific numele fis
					 modify_monitor=2;
					 strcpy(buf,(block+current_point)->label);
					 getalpha(field, (block+current_point)->label, L_AMON_LABEL);
					 strcpy(b, (block+current_point)->label );
					 rtrim(b);
					 if( strchr(b,' ') )
					 {
						 strcpy((block+current_point)->label,buf);
						 PutAlpha(field, buf);
					 }
					 break;
		case AMON_STATUS:
					 modify_monitor=1;
					 (block+current_point)->status=onoff(!(block+current_point)->status, buf);
					 PutAlpha(field, buf);
					 break;
		case AMON_LENGTH:
					 long l1,interv;
					 int sample;
					 modify_monitor=1;
					 GetAlpha(field, MAX_ALPHA, buf);
					 pgrid->GDGets(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
					 l = atoi(buf);
					 if(!l)
					 {
						l=1000;
					  itoa(l, buf, 10);
						PutAlpha(field, buf);
					 }
					 (block+current_point)->max_time_length=(unsigned char)l;
					 compute_size();
					 break;
		case AMON_UNITS:
					 modify_monitor=1;
					 (block+current_point)->unit=displayamonunit( ((unsigned char)(block+current_point)->unit)-1, buf );
//					 PutAlpha(field, buf);

					 compute_size();
					 break;
		case AMON_INTERVAL:
					{
					 int min, hour;
					 long sec;
					 modify_monitor=1;
					 sec = (long)((block+current_point)->second_interval_time);
					 min = (int)((block+current_point)->minute_interval_time);
					 hour = (int)((block+current_point)->hour_interval_time);
					 readinterval(field, buf, &sec,&min,&hour);
					 if(!sec && !min && !hour)
					 {
						min = 15;
						memcpy(buf,intervaltotext( NULL, (block+current_point)->second_interval_time , (block+current_point)->minute_interval_time,
									 (block+current_point)->hour_interval_time ),8);
					 }
					 (block+current_point)->second_interval_time=(char)sec;
					 (block+current_point)->minute_interval_time=(char)min;
					 (block+current_point)->hour_interval_time=(char)hour;

					  PutAlpha(field, buf);
					  compute_size();
					}
					break;
		case AMON_SIZE:
					break;
	  }
	  pgrid->GGPutField(field,Lightgray,Black);
	  pgrid->modify = TRUE;
	 }
}


int Monitor_block::GetRec(void)
{
	int i;
	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,' ',sizeof(struct AMON_LineBuf));

	for(i=0; i<fields_number; i++)
	{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
	}

	memcpy(amon_inputs,(block+current_point)->inputs,sizeof(amon_inputs));
	if(!printamon)
	{
	 if(display_amons==1)
		display_amons=2;
	 if(display_amons==0 || display_amons==2)
	 {
		GGrid p(mode_text?64:500,mode_text?3:24,mode_text?73:600,mode_text?(3+((panel_info1.panel_type == MINI_T3000)?8+2:16+2)):(29+((panel_info1.panel_type == MINI_T3000)?200+20:360+20)),
					 GRID,NULL,AMON_INPUTS,current_point+1,panel,network,type,(block+current_point)->anum_inputs,SMALL_FONT,5,1);
		p.save=0;
		p.GWSet(NULL,Lightgray,Darkgray);
//	 nofond=1;
		nothing = 0;
		p.GShowGrid();
//	 nofond=0;
		p.GGHideCur(Black);
		p.GReleaseWindow();
		nothing = 1;
		if(display_amons==2)
		 display_amons=3;
	 }
  }
	return FX_SUCCESS;
}

int Monitor_block::GetField(int field, char *buf)
{
	int l;

	l=0;
	switch (field) {
		case AMON_NUM:
				 nr_point(buf);
				 break;
		case AMON_LABEL:
				 char *p;
				 p=lalign((block+current_point)->label,L_AMON_LABEL);
				 memcpy(buf , p,L_AMON_LABEL);
				 l=L_AMON_LABEL;
				 break;
		case AMON_STATUS:
				 onoff((block+current_point)->status, buf);
				 break;
		case AMON_INTERVAL:
						memcpy(buf,intervaltotext( NULL, (block+current_point)->second_interval_time , (block+current_point)->minute_interval_time,
									 (block+current_point)->hour_interval_time ),8);
						break;
		case AMON_LENGTH:
					 l = (block+current_point)->max_time_length;
					 itoa(l,buf,10);
					 ralign(buf,L_AMON_LENGTH);
					l=L_AMON_LENGTH;
					break;
		case AMON_UNITS:
					 l = (block+current_point)->unit;
					 if (l==0)
							 strcpy(buf,minut);
					 if (l==1)
							 strcpy(buf,hours);
					 if (l==2)
							 strcpy(buf,days);
					 break;
		case AMON_SIZE:
					 long sample,l1,interv;
					 sample=psample(&interv, block+current_point);
					 l1 = (block+current_point)->anum_inputs * 4 * sample+sizeof(Header_amon)+4;
					 if(l1==sizeof(Header_amon)+4) l1=0;
					 ltoa(l1,buf,10);
					 ralign(buf,L_AMON_SIZE);
					 l=L_AMON_SIZE;
					break;
		}

 return l;
}

//**********************************
//    class Analog_monitor_inputs
//**********************************

Amon_inputs_block::Amon_inputs_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				 :Block(pthis, pt, p, net, type, pnum, N_AMON_INPUT, (char *)&line_buf)
	 {
			int npoint=0;
			if(type==INDIVIDUAL)
			 {
				number_of_points=1;           //MAX;
				npoint =  pnum-1;                // num_point
			 }
			else
				number_of_points=16;           //MAX_;
		 set_semaphore_dos();
		 block=new Point_Net[number_of_points];
		 clear_semaphore_dos();
		 memset(block, 0, number_of_points*sizeof(Point_Net));
		 memmove(block,amon_inputs,sizeof(amon_inputs));
		 anum_inputs = pnum;
		 r.RecStruct(N_AMON_INPUT,amon_input_struct);
		 h.HSet(N_AMON_INPUT,r.RecStruct(1),number_of_points);
		 index_max_amon_input=0;
	 }

Amon_inputs_block::~Amon_inputs_block()
{
	set_semaphore_dos();
	delete [] block;
	clear_semaphore_dos();
}

int Amon_inputs_block::Read(int field, char key)
{
// unsigned ax,bx,es;
 char buf[50],l;
 char *p;
// unsigned bytes=0;
 if(key==INSERT)
 {
 }
 else
 {
//	if(current_point <= index_max_amon_input)
	switch (field) {
		case AMON_INPUT:
					 modify_monitor = 1;
					 getpoint(field, block[current_point],(char *)&block[current_point], 1);
					 break;
			}
	  pgrid->GGPutField(field,Lightgray,Black);
	  pgrid->modify = TRUE;
	}
 }


int Amon_inputs_block::GetRec(void)
{
	int i;

//	if (current_point > index_max_amon_input)
//		{
//		 memset(&line_buf,' ',sizeof(struct AMON_INPUT_LineBuf));
//		 return 0;
//		}

	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,' ',sizeof(struct AMON_INPUT_LineBuf));

	for(i=0; i<fields_number; i++)
	{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
	}
	return (FX_SUCCESS);
}

int Amon_inputs_block::GetField(int field, char *buf)
{
	int l;

	l=0;
	switch (field) {
		case AMON_INPUT:
					{
					 getpoint(field, block[current_point], buf, 0);
/*
					 Point_main_sub point;
					 int num_point,var_type, point_type, num_panel;
					 char *p;
					 memcpy(&point,(block+current_point),2);
					 if (!pointtotext(buf,&point,STANDARD))
					 {
						p=ispoint(rtrim(buf),&num_point,&var_type, &point_type, &num_panel);
						strcpy(buf,p);
						ralign(lalign(buf,L_AMON_INPUT),L_AMON_INPUT);
					 }
					 else
							 memcpy(buf,NOTHING,8);
*/
					 l=L_AMON_INPUT;
					}

					 break;
		}

 return l;
}

Password_block::Password_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				 :Block(pthis, pt, p, net, type, pnum, N_USER_NAME, (char *)&line_buf)
{
			number_of_points=tbl_bank[USER_NAME];           //MAX_GRPPUT;
			set_semaphore_dos();
//					block=new Password_point[number_of_points];
			block=new Password_struct;
			clear_semaphore_dos();
//			if((local_panel &&  type!=INDIVIDUAL) || (type==INDIVIDUAL && p==Station_NUM))
			if( checklocal() )
					memmove(block,&passwords,sizeof(Password_struct));
			else
					memset(block,'\0',sizeof(Password_struct));
			r.RecStruct(N_USER_NAME,user_name_struct);
			h.HSet(N_USER_NAME,r.RecStruct(1),number_of_points);
}

Password_block::~Password_block()
{
 set_semaphore_dos();
 delete block;
 clear_semaphore_dos();
}

useraccount()
{
 char apassword[9];
 memcpy(apassword,ast,strlen(upassword));
 apassword[strlen(upassword)]=0;
 if(!strlen(upassword))
 {
	memset(apassword,' ',8);
	apassword[8]=0;
 }
 itoa(Station_NUM,ddefault,10);

// ********  the old code  ********
// GWDialog *D = new GWDialog(mode_text?32:268,mode_text?7:110,mode_text?67:544,mode_text?19:360,NO_STACK,0);
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.036  ********
// ********       begin       ********
// ***********************************
 GWDialog *D = new GWDialog(41,"need_help",mode_text?32:268,mode_text?7:110,mode_text?67:544,mode_text?19:360,NO_STACK,0);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.036  ********
// ********        end        ********
// ***********************************
 D->enter = 1;

 D->GWSet("",Lightgray,Darkgray);

 D->GShowWindow(DIALOG);
// D->enter=1;

 D->GWPuts(2,2,"Name          :",Lightgray,Black);
 D->GWPuts(3,2,"Acces level   :",Lightgray,Black);
// D->GWPuts(3,2,"Rights_access :",Lightgray,Black);
 D->GWPuts(4,2,"Default panel :",Lightgray,Black);
 D->GWPuts(5,2,"Default screen:",Lightgray,Black);
 D->GWPuts(7,2,"Password      :",Lightgray,Black);
 D->GWPuts(8,12,"(Type Enter to change)",Lightgray,Black);
// file=new char[60];

// D.GDPuts(1,17, uname,15,Cyan,Black);
 D->GDPuts(3,18, array_access[acces],12,Cyan,Black);
// D.GDPuts(5,17, ddefault,2,Cyan,Black);
// D->GDPuts(3,18, blank,1,Cyan,Black);
 D->GDPuts(7,18, apassword,8,Cyan,Black);

 D->GDDef_object(NULL,18,2,15,Cyan,Black,uname,Blue,White);
// D.GDDef_object(pname,17,1,15,Cyan,Black);
// D->GDDef_object(NULL,18,3,2,Cyan,Black,acces,Blue,White);
 D->GDDef_object(paccess,18,3,12,Cyan,Black);
// D->GDDef_object(prights,18,4,1,Cyan,Black);
 D->GDDef_object(NULL,18,4,2,Cyan,Black,ddefault,Blue,White);
// D.GDDef_object(pdefault,17,5,2,Cyan,Black);
 D->GDDef_object(NULL,18,5,2,Cyan,Black,dgroup,Blue,White);
 D->GDDef_object(ppassword,18,7,8,Cyan,Black);

// mtextcolor(Black);

 D->index_cur = 0;
 while(!D->HandleEvent());
 delete D;
}

int Password_block::Read(int field, char key)
{
 char buf[50],l;
 set_semaphore_dos();
 screen_right_tmp = new char[sizeof( block->passwords[current_point].screen_right)];
 clear_semaphore_dos();
	if(key==INSERT)
		{
		 if (access_level == 0)
		 {
		  if( block->ind_passwords < number_of_points )
		  {
			current_point = block->ind_passwords;
			uname[0]=0;upassword[0]=0;
			dgroup[0]='0';dgroup[1]=0;
//			acces[0]='0';acces[1]=0;
			acces = 0;
			memcpy(screen_right_tmp, block->passwords[current_point].screen_right, sizeof(block->passwords[current_point].screen_right));
			rights_access_tmp = block->passwords[current_point].rights_access;
			useraccount();
			strcpy(block->passwords[current_point].name,uname);
			strcpy(block->passwords[current_point].password,upassword);
//			(block+current_point)->access_level=atoi(acces);
			block->passwords[current_point].access_level=acces;
			block->passwords[current_point].default_panel=atoi(ddefault);
			block->passwords[current_point].default_group=atoi(dgroup);
			memcpy(block->passwords[current_point].screen_right,  screen_right_tmp, sizeof(block->passwords[current_point].screen_right));
			block->passwords[current_point].rights_access=rights_access_tmp;

			pgrid->FGetRec(pgrid->fh,pgrid->obj);
			pgrid->w_record = current_point+1;
//		 pgrid->GWGoto(current_point,1);
			pgrid->GGPutField(field,Lightgray,Black);
			block->ind_passwords++;
			pgrid->modify=TRUE;
		  }
		 }
		}
	else
	if(key==DELETE)
		{
		 if (access_level == 0)
		 if(current_point < block->ind_passwords)
		 {
			if(ReadYesNo(36,10,58,14, Lightblue, Blue, White,
									 Cyan, Black, "Delete?(Y/N):  "))
			{
			 for(int i=current_point;i<block->ind_passwords-1;i++)
					block->passwords[i]=block->passwords[i+1];
			 block->ind_passwords--;
			 block->passwords[block->ind_passwords].name[0]=0;
//		 pgrid->w_field = w_lfield;
			 pgrid->w_nfields = 0;
//		 w_field = 1;
//		 t_fields[w_field-1]=1;
			 pgrid->GGDrawGrid(Black);
			 pgrid->w_record = 1;
//		 w_field = 1; w_record = 1;
//		 GGShowCur(Black);
			 pgrid->modify=TRUE;
			}
		 }
		}
	else
	{
	 switch (field) {
		case USERS_NAME:
		 if(current_point < block->ind_passwords)
		 {
			if(access_level == 0 || block->passwords[current_point].access_level == access_level)
			{
			 strcpy(uname,rtrim(block->passwords[current_point].name));
			 strcpy(upassword,rtrim(block->passwords[current_point].password));
//			 itoa((block+current_point)->access_level,acces,10);
			 acces=block->passwords[current_point].access_level;
			 itoa(block->passwords[current_point].default_panel,ddefault,10);
			 itoa(block->passwords[current_point].default_group,dgroup,10);
			 memcpy(screen_right_tmp, block->passwords[current_point].screen_right, sizeof(block->passwords[current_point].screen_right));
			 rights_access_tmp = block->passwords[current_point].rights_access;

			 useraccount();
			}
			if(access_level == 0)
			{
			 if(!strcmp(rtrim(block->passwords[current_point].name),user_name))
			 {
				if(local_panel)
				{
				 strcpy(user_name,uname);
				 strcpy(password,upassword);
				 textcolor(Blue);
            }
			 }
			 strcpy(block->passwords[current_point].name,uname);
			 strcpy(block->passwords[current_point].password,upassword);
//			 (block+current_point)->access_level=atoi(acces);
			 block->passwords[current_point].access_level=acces;
			 block->passwords[current_point].default_panel=atoi(ddefault);
			 block->passwords[current_point].default_group=atoi(dgroup);
			 memcpy(block->passwords[current_point].screen_right,  screen_right_tmp, sizeof(block->passwords[current_point].screen_right));
			 block->passwords[current_point].rights_access=rights_access_tmp;
			 pgrid->FGetRec(pgrid->fh,pgrid->obj);
			 pgrid->modify=TRUE;
			}
		 }
		 break;
	 }
	 set_semaphore_dos();
	 delete screen_right_tmp;
	 clear_semaphore_dos();
	 pgrid->GGPutField(field,Lightgray,Black);
	}
//	textcolor(Black);
}

/*
void pname(GWDialog *D)
{
 D->GDGets(uname,1,17,15,Blue,White);
}
void pdefault(GWDialog *D)
{
 D->GDGets(ddefault,5,17,2,Blue,White);
}
*/
void paccess(GWDialog *D)
{
 union key key;
 MouseStatus stat;
// while(1)
 {
//	if(bioskey_new(1))
	{
//		 key.i = bioskey_new(0);
//		 if (key.ch[1]==72){ D->last=72;break;}
//		 if (key.ch[1]==80){ D->last=80;break;}
//		 if(key.ch[0]==13)
		 {
			if(++acces > 2) acces=0;
			D->GWPuts(3,18,13,array_access[acces],FONDCOLOR,White);
		 }
	}
/*
	else
	{
	 mouse_status(stat);
	 if(stat.leftButton )
	 {
		D->last_mouse=1;
		break;
	 }
	}
*/
 }
}

void prights(GWDialog *D)
{
//	if( atoi(acces) > 1 )
	if( acces > 1 )
	{
	 arights_grid = 1;
//	GGrid *p;
//	p=new GGrid(20,6,60,6+14+2,GRID,NULL,AY,STANDARD,0,0,0);
	 GGrid p(25,4,50,4+14+2,GRID,NULL,AY,T3000,0,0,0);
	 p.GWSet("Access Rights",Lightgray,Darkgray);
	 p.GShowGrid();
	 while (!p.HandleEvent());
//	delete p;
	 arights_grid = 0;
	}
}


void ppassword(GWDialog *D)
{
 union key key;
 MouseStatus stat;
 char password1[9];
 char password2[9];
 memset(password1,0,9);
 memset(password2,0,9);
// chbkg(50,15, 8, Blue,White);
// mgotoxy(50,15);

// D->GWchbkg(18, 7, mode_text?8:64, Cyan, Black);
// D->GWGoto(18,7);
 while(1)
 {
//	if(bioskey_new(1))
	{
//		 key.i = bioskey_new(0);
//		 if (key.ch[1]==72){ D->last=72;break;}
//		 if (key.ch[1]==80){ D->last=80;break;}
//		 if(key.ch[0]==13)
		 {
			D->GWPuts(9,4,"Type new password  :",Lightgray,Black);
			D->GWchbkg(18, 7, mode_text?8:64, Cyan, Black, 127, mode_text ? 0 : textheight("H")+2);
//			D->GWchbkg(25, 9, mode_text?8:64, Blue, White);
//			chbkg(50,15, 8, Cyan, Black);
//			chbkg(57,17, 8, Blue, White);
//			mgotoxy(57,17);
//			mgets(password1,0,Blue,Black);
//			chbkg(57,17, 8, Cyan, Black);
			D->GWGoto(25,9);
//			D->GDGets(password1,9,25,8,Blue,Black);
			D->GWchbkg(25, 9, mode_text?8:64, Blue, Black, 127, mode_text ? 0 : textheight("H")+2);
			wingets(password1, D->GWy(9), D->GWx(25), 8, Blue,Black, 'S', "********",0);


			D->GWchbkg(25, 9, mode_text?8:64, Cyan, Black, 127, mode_text ? 0 : textheight("H")+2);

			D->GWPuts(10,4,"Retype new password:",Lightgray,Black);
//			D->GWchbkg(25, 10, mode_text?8:64, Cyan, Black);
			D->GWGoto(25,10);
//			D->GDGets(password2,10,25,8,Blue,Black);
			D->GWchbkg(25, 10, mode_text?8:64, Blue, Black, 127, mode_text ? 0 : textheight("H")+2);
			wingets(password2, D->GWy(10), D->GWx(25), 8, Blue,Black, 'S', "********",0);
			D->GWchbkg(25, 10, mode_text?8:64, Cyan, Black);
//			chbkg(57,18, 8, Blue, White);
//			mgotoxy(57,18);
//			mgets(password2,0,Blue,Black);
//			window(35,17,65,18);
//			mclrscr(35,17,65,18,Lightgray);
//			mtextbackground(Lightgray);
//			clrscr();

			if(!strcmp(rtrim(password1),rtrim(password2))) strcpy(upassword,password1);
			else
				D->GWPuts(11,8,"Password unchanged!",Lightgray,Black);

//			window(1,1,80,25);
//			chbkg(50,15, 8, Blue, White);
      hidecur();
			D->GWGoto(18,7);
//			D->GWchbkg(18, 7, mode_text?8:64, Cyan, Black);
			break;
		 }
	}
//	mouse_status(stat);
//	if(stat.leftButton )
//	 {
//		D->last_mouse=1;
//		break;
//	 }
 }
}


int Password_block::GetRec(void)
{
	int i;
	char buf[sizeof(struct USER_NAME_LineBuf)];
	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,'\0',sizeof(struct USER_NAME_LineBuf));

	for(i=0; i<fields_number; i++)
	{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
	}
	memcpy(buf,(char *)&line_buf,sizeof(struct USER_NAME_LineBuf));
	if(!memcmp(buf, lalign(user_name,15), strlen(user_name)) && !memcmp(password, passwords.passwords[current_point].password, strlen(password)))
	  pgrid->fground=Lightred;
	return (FX_SUCCESS);
}

int Password_block::GetField(int field, char *buf)
{
	int l;

	l=0;
	switch (field) {
		case USERS_NAME:
					memcpy(buf , lalign(block->passwords[current_point].name,L_USER_NAME),L_USER_NAME);
					break;
		}
 return l;
}


////////////////////////////////////
//
//      Array1_block
//
/////////////////////////////////


Array1_block::Array1_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				 :Block(pthis, pt, p, net, type, pnum, N_ARRAY1, (char *)&line_buf)
{
//					pgrid = pthis;
					number_of_points=max_entry;           //MAX_GRPPUT;
					set_semaphore_dos();
					block=new Array1_point[number_of_points];
					clear_semaphore_dos();
#ifdef NEW
//          memmove(block,array,number_of_points*sizeof(Array1_point));
					for(int i=0;i<number_of_points;i++)
					{
					 strcpy(block[i].name, array[i]);
					}
#else
//					mmemset(block,'\0',number_of_points*sizeof(Control_group_point));
#endif
			array_struct->l = point_number;
			r.RecStruct(N_ARRAY1,array_struct);
			h.HSet(N_ARRAY1,r.RecStruct(1),number_of_points);
}

Array1_block::~Array1_block()
{
 array_struct->l = 10;
 set_semaphore_dos();
 delete [] block;
 clear_semaphore_dos();
}

int Array1_block::Read(int field, char key)
{
 char buf[50],l;
 switch (field) {
		case ARRAY11:
					 GetAlpha(field, MAX_ALPHA, view_name);
					 view_name[point_number]=0;
					 break;
			}
}

int Array1_block::GetRec(void)
{
	int i;
	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,'\0',sizeof(struct ARRAY1_LineBuf));

	for(i=0; i<fields_number; i++)
	{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
	}
	return (FX_SUCCESS);
}

int Array1_block::GetField(int field, char *buf)
{
	int l;

	l=0;
	switch (field) {
		case ARRAY11:
					memcpy(buf , lalign((block+current_point)->name,point_number),point_number);
					break;
		}
 return l;
}


void ftoa(float f, int length, int ndec, char *buf)
{
 int i,n;
 char xxxtmp[20],*p,c;
 for(i=0;i<length-ndec;i++)
			buf[i]=' ';
 buf[length-ndec-1]='.';
 for(i=length-ndec;i<length;i++)
			buf[i]='0';
 if(f>1000000.00 || f<-1000000.00 || (f>-1.e-6 && f<1.e-6) )
	 gcvt(f, 5, xxxtmp);
 else
	 gcvt(f, length, xxxtmp);
 if ((p=strchr(xxxtmp, 'e'))!=NULL  ||  (p=strchr(xxxtmp, 'E'))!=NULL)
		strcpy(buf+length-strlen(xxxtmp),xxxtmp);
 else
 {
	c='.';
	if ((p=strchr(xxxtmp, c))!=NULL)
		{
		 memcpy(&buf[length-ndec],p+1,min(ndec,(int)strlen(p+1)));
		}
	else
		p=&xxxtmp[strlen(xxxtmp)];
	n=min(p-&xxxtmp[0],length-ndec-1);
	memcpy(&buf[length-ndec-1]-n,p-n,n);
 }
	buf[length]=0;
}

void longtoa(long f, int length, int ndec, char *buf)
{
	int n,i;
	char xxxtmp[20],*p,c, q[6];
	if(f>1000000000L || f<-1000000000L)
	{
	 ftoa((float)f/1000.,  length, ndec, buf);
	 return;
	}
	memset(buf, ' ', length-ndec-1);
	buf[length-ndec-1]='.';
	memset(&buf[length-ndec], '0', ndec);

	ltoa(f/1000, xxxtmp, 10);
	if( f<0 && f>-1000 )
	{
	 strcpy(xxxtmp,"-0");
	}
	n=strlen(xxxtmp);
	strcat(xxxtmp,".");
	p=&xxxtmp[n+1];
	f %= 1000;
	if(f<0) f = -f;
   q[0]=0;
	itoa(f, q, 10);
	if(f<100)
	{
	 memmove(&q[1], q, strlen(q)+1 );
	 q[0] = '0';
	}
	if(f<10)
	{
	 memmove(&q[1], q, strlen(q)+1 );
	 q[0] = '0';
	}
	memcpy(p, q, ndec);

//	if( *p=='-' )
//		memmove( p, p+1, 3);

	memcpy(&buf[length-ndec], p, min(ndec,(int)strlen(p)));
	n=min(n,length-ndec-1);
	memcpy(&buf[length-ndec-1]-n,p-n-1,n);
	buf[length]=0;
}

int pointtotext(char *buf,Point_T3000 *point)
{
 char x[4];
 byte num,panel,point_type;
 num=point->number;
 panel=point->panel;
 point_type=point->point_type;
 if (point_type==0)
 {
		buf[0]=0;
		return 1;
 }
 strcpy(buf,itoa(panel+1,x,10));
 if(panel+1<10 || num+1 < 100)
		 strcat(buf,lin);
 strcat(buf,ptr_panel->info[point_type-1].name);
 strcat(buf,itoa(num+1,x,10));
 return 0;
}

int pointtotext(char *buf,Point_Net *point)
{
 char x[6];
 byte num,panel,point_type;
 int net;
		 num=point->number;
		 panel=point->panel;
		 point_type=point->point_type;
		 net = point->network;
		 if (point_type==0)
		 {
				buf[0]=0;
				return 1;
		 }
		 if(net!=0xFFFF)
		 {
			strcpy(buf,itoa(net,x,10));
			strcat(buf,".");
		 }
		 else
		 {
			buf[0] = 0;
		 }
		 strcat(buf,itoa(panel+1,x,10));
		 if(panel+1<10 || num+1 < 100)
			 strcat(buf,lin);
		 strcat(buf,ptr_panel->info[point_type-1].name);
		 strcat(buf,itoa(num+1,x,10));
 return 0;
}


int look(char *buf,Point *point,byte panel_type,byte panel)
{
int t,i,j,k,l;
byte vpanel,vnum,vpoint_type;
char pc[9],pt[9],pn[9];

			 t=0;
			 l=0;
			 while(isdigit(buf[l]) && l<LABEL)
						 pc[l]=buf[l++];
			 pc[l]=0;
			 if (l==0)
				 vpanel=panel;
			 else
				 vpanel=atoi(pc);
//			 if ((panel_type!=SUB_MINI && (vpanel>=1 && vpanel<=32)) )
					 {
						if (buf[l]=='-') l++;
						j=0;
						while(!isdigit(buf[l]) && l<LABEL)
							pt[j++]=buf[l++];
						pt[j]=0;
						for(k=0;k<=AY;k++)
							if (!strcmp(pt,&point_cod[k][0]))
								break;
						if (k<=AY)
							{
							 vpoint_type=k;
							 strcpy(pn,&buf[l]);
							 vnum=atoi(pn);
									 {
//											 point->panel=vpanel-1;
											 point->point_type=vpoint_type+1;
											 point->number=vnum-1;
//										if(!findlabel(panel_type, net_type, panel, *point, buf))
											{
											 strcpy(buf,itoa(vpanel,pc,10));
											 if(vpanel<10 || vnum < 100)
												 strcat(buf,lin);
											 strcat(buf,pt);
											 strcat(buf,pn);
											 buf[8]=0;
											}
										t=1;
									 }
						 }
					}

/*
			if(!t)
				if (findpoint(panel_type, net_type, panel, *point, buf))
					t=1;
*/
			if (t==0)
					return 1;     //error
	return 0;
}

/*
int findlabel(int panel_type, Sub_a_b net_type, int panel,Point_main_sub point, char *buf)
{
 unsigned long n,l,lpanel,pos,pospanel,poscur,posrest,length,lposcur;
 int point_type,sub_panel,num,x,k;

	 if(panel_type!=SUB_MINI)
		 {
			panel=point.main.panel;
			point_type=point.main.point_type;
			num=point.main.number;
		 }
	 else
		 {
			sub_panel=point.sub.panel;
			point_type=point.sub.point_type;
			num=point.sub.number;
		 }

	 if (!panel || !num)
		 return 0;
	 pos = 4;
		for(int j=1; j<=panel; j++)
		 {
			 if ((j==panel) && (panel_type==STANDARD || panel_type==MINI_MAIN)) break;
			 mmemcpy(&l, &des[pos], 4);
			 pos += l+4;
			 if ((j==panel) && (panel_type==SUB_MINI) && (net_type==SUBA)) break;
			 mmemcpy(&l, &des[pos], 4);
			 pos += l+4;
			 if ((j==panel) && (panel_type==SUB_MINI) && (net_type==SUBB)) break;
			 mmemcpy(&l, &des[pos], 4);
			 pos += l+4;
		 }
//	 if (Gsub_panel == 0)
//		 {
			pospanel = pos;
			mmemcpy(&lpanel, &des[pos], 4);
			pos += 4;

			if (panel_type==SUB_MINI)
			{
			 k=1;
//			 lnet=lpanel;
			 while (lpanel > pos-pospanel-4)
				 {
					mmemcpy(&l, &des[pos], 4);
					if (k==sub_panel)
						break;
					pos += l+4;
					k++;
				 }
			 if (k==sub_panel)
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

			if (!lposcur)
					return 0;  //not found
			k=0;
			while (lposcur > pos-(poscur+2) && k< num)
					{
					 x=des[pos++];
					 pos += x;
					 x=des[pos++];
					 pos += x;
					 k++;
					}
			if (k!=num || x==0)
				 return 0;        // not found
			mstrcpy(buf,&des[pos-x]);
			return 1;
}
*/

/*
findpoint(int panel_type,Sub_a_b net_type, int panel, Point_main_sub point,char *buf)
{
return 0;  //error
}
*/

/*char *ltrim(char *text)
{
	int n,i;
	n=mstrlen(text);
	for (i=0;i<n;i++)
			if (text[i]!=' ')
					break;
	mstrcpy(text,text+i);
	return text;
}

*/

texttointerval( char *textbuffer,char *seconds , char *minutes , char *hours, char c )
{
	char *p1,*p2  ;
	char atoibuffer[10];       /* temporary sotrage for itoa */
		atoibuffer[0]=0;
		p2=textbuffer;
		p1=p2;
		if (!(p2=strchr(p2, c )))
			{
			strncat(atoibuffer,p1,strlen(p1));
			*minutes=atoi(atoibuffer);
			return 0;
			}
		strncat(atoibuffer,p1,p2-p1);
		*hours=atoi(atoibuffer);
		p2++;
		p1=p2;
		atoibuffer[0]=0;
		if (!(p2=strchr(p2, c )))
			{
			strncat(atoibuffer,p1,strlen(p1));
			*minutes=atoi(atoibuffer);
			return 0;
			}
		strncat(atoibuffer,p1,p2-p1);
		*minutes=atoi(atoibuffer);
		p2++;
		p1=p2;
		atoibuffer[0]=0;
		strncat(atoibuffer,p1,strlen(p1));
		if(seconds)
			*seconds=atoi(atoibuffer);
}
/*******************intervaltotext ********************/


char * intervaltotext( long seconds , int minutes , int hours, char *c )
{ /*  char * text;          /* return this string */
	char *separator = c ;
	char itoabuffer[12];       /* temporary sotrage for itoa */
	char textbuffer[12] ;
	textbuffer[0]=0;
	if(seconds<0)
	{
	 seconds=-seconds;
	 strcat(textbuffer, "-" ) ;        /* add the '-' */
	}
	if( hours < 10 ) {
			strcat(textbuffer, zero ) ;        /* add the leading zero 0#:##:## */
	}
	itoa(hours,itoabuffer,10) ;             /* put panel in ASCII onto buffer */
	strcat(textbuffer, itoabuffer ) ;        /* add the OUT text */
	strcat(textbuffer, separator ) ;        /* add the ":" separator*/
	if( minutes < 10 ) {
			strcat(textbuffer, zero ) ;        /* add the leading zero ##:0#:## */
	}
	itoa(minutes,itoabuffer,10) ;        /* add the OUT text */
	strcat(textbuffer, itoabuffer ) ;        /* add the OUT text */
	strcat(textbuffer, separator ) ;        /* add the ":" separator*/
	if( seconds < 10 ) {
			strcat(textbuffer, zero ) ;        /* add the leading zero ##:##:0# */
	}
	itoa(seconds,itoabuffer,10)  ;        /* add the OUT text */
	strcat(textbuffer, itoabuffer ) ;        /* add the OUT text */
	return( &textbuffer[0] ) ;

}
/*******************intervaltotext ********************/



//char huge *Heap_alloc(int bytes)
char *Heap_alloc(int bytes)
{
 if (bytes==0)
	 return NULL;
 ind_heap_buf += bytes;
 return (&heap_buf[ind_heap_buf - bytes]);
}

//int Heap_dealloc(char huge **old)
int Heap_dealloc(char **old)
{
// char huge *prog,*end;
 char *prog,*end;
 int bytes_old,n;
 if (*old)
 {
 memcpy(&bytes_old,*old,2);
 bytes_old += 5;
 memcpy(&n,*old+bytes_old,2);
 bytes_old += 2+n;
 memcpy(&n,*old+bytes_old,2);
 bytes_old += 2+n;
 memcpy(&n,*old+bytes_old,2);
 bytes_old += 2+n;

 set_semaphore(&t3000_flag);
 movedata(FP_SEG(*old+bytes_old),FP_OFF(*old+bytes_old) ,FP_SEG(*old),FP_OFF(*old), (&heap_buf[ind_heap_buf]-*old)-bytes_old);
	 for (int i=0;i<MAX_PRGS; i++)
		if (ptr_panel->program_codes[i] > *old)
			 ptr_panel->program_codes[i] -= bytes_old;
	 ind_heap_buf -= bytes_old;
 *old=NULL;
 clear_semaphore(&t3000_flag);
 }
}

//int Heap_move(char huge *old, char huge *newp, int ind)
int Heap_move(char *old, char *newp, int ind)
{
// char huge *prog,*end;
 char *prog,*end,*timetableold,*timetablenew, *p, *q, *s, r[100];
 int n,i,bytes_old,ntimeold,ntimenew;
// set_semaphore(&t3000_flag);
	ptr_panel->program_codes[ind] =  newp;
	if(old)
	{
	 memcpy(&bytes_old, old,2);
	 bytes_old += 5;
	 memcpy(&n,old+bytes_old,2);
	 bytes_old += 2+n;
	 memcpy(&n,old+bytes_old,2);
	 ntimeold = n;
	 timetableold = old + bytes_old + 2;
	 bytes_old += 2+n;

	 memcpy(&n,old+bytes_old,2);
	 bytes_old += 2+n;

	 prog=newp;
	 memcpy(&n,newp,2);
	 n += 5;
	 memcpy(&i,newp+n,2);
	 n += 2+i;
	 memcpy(&i,newp+n,2);
	 ntimenew = i;
	 timetablenew = newp + n + 2;
	 n += 2+i;
	 memcpy(&i,newp+n,2);
	 n += 2+i;
	 end=prog+n;

 p = timetableold + ntimeold;
 while( timetableold < p )
 {
	q = (char *)memchr(timetableold, 0xFF, ntimeold);
	if(q) q++;
	n = q - timetableold;
	memcpy(r, timetableold, n);
	r[n] = 0;
	s = timetablenew;
	while(s < timetablenew + ntimenew)
	{
	 if(!memcmp(s, r, n))
	 {
		memcpy( s + n , q, 5);
		break;
	 }
	 s = (char *)memchr(s, 0xFF, ntimenew);
	 if(s) s += 6;
	 else break;
	}
	timetableold = q + 5;
 }

/*
 while((long)FP_SEG(end)*16+(long)FP_OFF(end)>(long)FP_SEG(prog)*16+(long)FP_OFF(prog))   //1
 {
//	if((prog=(char huge *)memchr(prog,TIME_ON,((long)FP_SEG(end)*16+(long)FP_OFF(end)) - ((long)FP_SEG(prog)*16+(long)FP_OFF(prog))))!=NULL)
	if((prog=(char *)memchr(prog,TIME_ON,((long)FP_SEG(end)*16+(long)FP_OFF(end)) - ((long)FP_SEG(prog)*16+(long)FP_OFF(prog))))!=NULL)
		{
		 for(i=0;i<ind_line_array;i++)
			if (!memcmp(prog-2,&line_array[i][1],2))
				 {
					memcpy(prog+1,old+line_array[i][0],4);
					break;
				 }
		 prog++;
		continue;
		}
	 else
		 break;
 }
 prog=newp;
 while((long)FP_SEG(end)*16+(long)FP_OFF(end)>(long)FP_SEG(prog)*16+(long)FP_OFF(prog))   //1
 {
//	if((prog=(char huge *)memchr(prog,TIME_OFF,((long)FP_SEG(end)*16+(long)FP_OFF(end)) - ((long)FP_SEG(prog)*16+(long)FP_OFF(prog))))!=NULL)
	if((prog=(char *)memchr(prog,TIME_OFF,((long)FP_SEG(end)*16+(long)FP_OFF(end)) - ((long)FP_SEG(prog)*16+(long)FP_OFF(prog))))!=NULL)
		{
		 for(i=0;i<ind_line_array;i++)
			if (!memcmp(prog-2,&line_array[i][1],2))
				 {
					memcpy(prog+1,old+line_array[i][0],4);
					break;
				 }
		prog++;
		continue;
		}
	 else
		 break;
 }
*/
	 int j=(&heap_buf[ind_heap_buf]-old);
	 movedata(FP_SEG(old+bytes_old),FP_OFF(old+bytes_old) ,FP_SEG(old),FP_OFF(old), j-bytes_old);
	 for (int i=0;i<MAX_PRGS; i++)
		if (ptr_panel->program_codes[i] > old)
			 ptr_panel->program_codes[i] -= bytes_old;
	 ind_heap_buf -= bytes_old;
	}
// clear_semaphore(&t3000_flag);
}


int get_indiv_point(Point_Net point, char *buf)
{
 Delay(100);
 return (net_call(20, (point.point_type<<8)+point.number, buf, 0, point.panel+1, point.network,NETCALL_RETRY));
}

int get_point_info(Point_info *point_info, char **des, char **label, char **ontext, char **offtext, char pri, int network)
{
 char buf[160], buf1[17],*q;
 Point_Net p;
 int num_point,num_net,num_panel,r,t=0;
 byte point_type,var_type;
 union  {
		Str_out_point *p_out;
		Str_in_point *p_in;
		Str_variable_point *p_var;
		Str_controller_point *p_con;
		Str_weekly_routine_point *p_wr;
		Str_annual_routine_point *p_ar;
		Str_program_point *p_prg;
		Control_group_point *p_grp;
		Str_monitor_point *p_amon;
		Point_info *pinfo;
		} ptr;

 gdescriptor[0]=glabel[0]=0;
 memcpy(&p, &point_info->point, sizeof(Point_Net));
// p = &point_info->point;
 if (!p.point_type) return ERROR_COMM;

 point_type = p.point_type-1;
 num_point = p.number;

 r = ptr_panel->info[point_type].str_size;
 memset(buf, 0, r);

 if( (p.panel+1==Station_NUM && (local_panel || (!local_panel&&( (pri==1)||(pri==3&&(p.network==0xFFFF)) ))  ))
		|| local_request(p.panel+1) )//pri=0 remote priority
// if((local_panel && p->main.panel+1==Station_NUM) || (!local_panel &&  p->main.panel+1==Station_NUM && p->main.panel+1!=station_num))
 {
  switch (point_type) {
	 case OUT:
	 case IN:
	 case VAR:
	 case CON:
	 case WR:
	 case AR:
	 case PRG:
	 case AMON:
	 case GRP:
//					 if(p->main.panel+1==Station_NUM && local_panel)
					 if(num_point < ptr_panel->table_bank[point_type])
						 memcpy(buf, ptr_panel->info[point_type].address+num_point*r, r);
					 break;
	 }
	 t=1;
	 point_info->point_value=0;
	 point_info->auto_manual=0;
	 point_info->digital_analog=1;
	 point_info->security=0;
	 point_info->decomisioned=0;
	}
	else
	{
	 if(pri==2)
	 {
	  if( p.network == 0xFFFF ) p.network = network;
		if( get_indiv_point(p, buf) != SUCCESS )
			 return ERROR_COMM;
		t=1;
		point_info->point_value=0;
		point_info->auto_manual=0;
		point_info->digital_analog=1;
		point_info->security=0;
		point_info->decomisioned=0;
	 }
	 else
	 {
//	  if( p.network == 0xFFFF ) p.network = network;
		point_info->point_value=0;
		point_info->auto_manual=0;
		point_info->digital_analog=1;
		point_info->security=0;
		point_info->decomisioned=0;
		r=0;

		for(int i=0;i<MAXREMOTEPOINTS82;i++)
		{
//		if( !remote_points_list[i].info.point.zero() )
		if( remote_points_list[i].info.point.point_type )
		{
		 if( remote_points_list[i].info.point==p )
		 {
			memcpy(buf, &remote_points_list[i].info, sizeof(Point_info));

			ptr.pinfo = (Point_info *)buf;
			point_info->point_value=ptr.pinfo->point_value;
			point_info->auto_manual=ptr.pinfo->auto_manual;
			point_info->digital_analog=ptr.pinfo->digital_analog;
			point_info->security=ptr.pinfo->security;
			point_info->decomisioned=ptr.pinfo->decomisioned;
			r=ptr.pinfo->units;
			point_info->units=r;
			if(!point_info->digital_analog)
			{
				if(r < 0) r = 0;
				num_point=dig_range_array[r].value % 2;
				if(ontext)
				 *ontext= &(dig_range_array[r].dunits[!num_point][0]);
				if(offtext)
				 *offtext= &(dig_range_array[r].dunits[num_point][0]);
			}
			break;
		 }
		}
		}
		pointtotext(buf1,&p);
		r=0;
		q=ispoint(rtrim(buf1),&num_point,&var_type, &point_type, &num_panel, &num_net, networkaddress, Station_NUM, &r);
		strcpy(glabel,q);
		if(Des)
		{
		if(point_type!=CON && point_type!=TBL)
			q = Des->look_descriptor(num_panel,point_type,num_point);
		if(!q) q = glabel;
		strcpy(gdescriptor,q);
	  }
	 } //if pri==2
	}

 ptr.p_out = (Str_out_point *)buf;
 pointtotext(gpointname,&p);
 switch (point_type) {
	 case OUT:
					 {
//						Str_out_point *p_out=(Str_out_point *)buf;
					  if(t)
					  {
						point_info->point_value=ptr.p_out->value;
						point_info->auto_manual=ptr.p_out->auto_manual;
						point_info->digital_analog=ptr.p_out->digital_analog;
						point_info->security=ptr.p_out->access_level;
						point_info->decomisioned=ptr.p_out->decom;
						r = GetRange_Out(ptr.p_out->range);
						if(!ptr.p_out->digital_analog)
						{
							r -= DIG1;
							if(r < 0) r = 0;
							num_point=dig_range_array[r].value % 2;
							if(ontext)
								*ontext= &(dig_range_array[r].dunits[!num_point][0]);
//							 *ontext= &(dig_range_array[r].dunits[1][0]);
							if(offtext)
								 *offtext= &(dig_range_array[r].dunits[num_point][0]);
//							 *offtext= &(dig_range_array[r].dunits[0][0]);
						}
						point_info->units = r;
						strcpy(gdescriptor,ptr.p_out->description);
						strcpy(glabel,ptr.p_out->label);
						}
/*
						if( OFF_ON <=  r+DIG1 && r+DIG1 <= custom_digital8 )
						{
							num_point=dig_range_array[r].value % 2;
							if(ontext)
							 *ontext= &(dig_range_array[r].dunits[!num_point][0]);
							if(offtext)
							 *offtext= &(dig_range_array[r].dunits[num_point][0]);
						}
*/
					 }
					break;
	 case IN:
					 {
//						Str_in_point *p_in=(Str_in_point *)buf;
						if(t)
						{
						point_info->point_value   =ptr.p_in->value;
						point_info->auto_manual   =ptr.p_in->auto_manual;
						point_info->digital_analog=ptr.p_in->digital_analog;
						point_info->decomisioned  =ptr.p_in->decom;
						r = GetRange_In(ptr.p_in->range);
						if(!ptr.p_in->digital_analog)
						{
							r -= DIG1;
							if(r < 0) r = 0;
							num_point=dig_range_array[r].value % 2;
							if(ontext)
							 *ontext= &(dig_range_array[r].dunits[!num_point][0]);
//							 *ontext= &(dig_range_array[r].dunits[1][0]);
							if(offtext)
							 *offtext= &(dig_range_array[r].dunits[num_point][0]);
//							 *offtext= &(dig_range_array[r].dunits[0][0]);
						}
						point_info->units=r;
						strcpy(gdescriptor,ptr.p_in->description);
						strcpy(glabel,ptr.p_in->label);
						}
/*
						if( OFF_ON <=  r+DIG1 && r+DIG1 <= custom_digital8 )
						{
							num_point=dig_range_array[r].value % 2;
							if(ontext)
							 *ontext= &(dig_range_array[r].dunits[!num_point][0]);
							if(offtext)
							 *offtext= &(dig_range_array[r].dunits[num_point][0]);
						}
*/
						break;
					 }
	 case VAR:
					 {
//						Str_variable_point *p_var=(Str_variable_point *)buf;
						if(t)
						{
						point_info->point_value=ptr.p_var->value;
						point_info->auto_manual=ptr.p_var->auto_manual;
						point_info->digital_analog=ptr.p_var->digital_analog;
						r = GetRange_Var(ptr.p_var->range);
						if(!ptr.p_var->digital_analog)
						{
							r -= DIG1;
							if(r < 0) r = 0;
							num_point=dig_range_array[r].value % 2;
							if(ontext)
							 *ontext= &(dig_range_array[r].dunits[!num_point][0]);
//							 *ontext= &(dig_range_array[r].dunits[1][0]);
							if(offtext)
							 *offtext= &(dig_range_array[r].dunits[num_point][0]);
//							 *offtext= &(dig_range_array[r].dunits[0][0]);
						}
						point_info->units=r;
						strcpy(gdescriptor,ptr.p_var->description);
						strcpy(glabel,ptr.p_var->label);
					  }

/*
						if( OFF_ON <=  r+DIG1 && r+DIG1 <= custom_digital8 )
						{
							num_point=dig_range_array[r].value % 2;
							if(ontext)
							 *ontext= &(dig_range_array[r].dunits[!num_point][0]);
							if(offtext)
							 *offtext= &(dig_range_array[r].dunits[num_point][0]);
						}
*/
					 }
					break;

	 case CON:
					{
//						Str_controller_point *p_con=(Str_controller_point *)buf;
						if(t)
						{
						 point_info->point_value = ptr.p_con->value;
						 point_info->auto_manual = ptr.p_con->auto_manual;
						 point_info->digital_analog=1;
						 point_info->units=procent;
						}
					}
					break;
	 case WR:
					 {
//						Str_weekly_routine_point *p_wr=(Str_weekly_routine_point *)buf;
					  if(t)
					  {
						 point_info->point_value=ptr.p_wr->value;
						 point_info->auto_manual=ptr.p_wr->auto_manual;
						 point_info->digital_analog=0;
						 point_info->units=1;
						 strcpy(gdescriptor,ptr.p_wr->description);
						 strcpy(glabel,ptr.p_wr->label);
						}
						if(ontext)
							 *ontext= on;
						if(offtext)
							 *offtext= off;
						break;
					 }
					break;
	 case AR:
					 {
//						Str_annual_routine_point *p_ar=(Str_annual_routine_point *)buf;
						if(t)
						{
						 point_info->point_value=ptr.p_ar->value;
						 point_info->auto_manual=ptr.p_ar->auto_manual;
						 point_info->digital_analog=0;
						 point_info->units=1;
						 strcpy(gdescriptor,ptr.p_ar->description);
						 strcpy(glabel,ptr.p_ar->label);
						}
						if(ontext)
							 *ontext= on;
						if(offtext)
							 *offtext= off;
						break;
					 }
					break;
	 case PRG:
					 {
//						Str_program_point *p_prg=(Str_program_point *)buf;
						if(t)
						{
						 point_info->point_value=ptr.p_prg->on_off;
						 point_info->auto_manual=ptr.p_prg->auto_manual;
						 point_info->digital_analog=0;
						 point_info->units=1;
						 strcpy(gdescriptor,ptr.p_prg->description);
						 strcpy(glabel,ptr.p_prg->label);
						}
						if(ontext)
							 *ontext= on;
						if(offtext)
							 *offtext= off;
					 }
						break;
	 case AMON:
					 {
//						Str_analog_monitor_point *p_amon=(Str_analog_monitor_point *)buf;
						if(t)
						{
						 point_info->point_value=ptr.p_amon->status;
						 point_info->digital_analog=0;
						 point_info->units=1;
						 gdescriptor[0]=0;
						 strcpy(glabel,ptr.p_amon->label);
						}
						if(ontext)
							 *ontext= on;
						if(offtext)
							 *offtext= off;
					 }
					break;
	 case GRP:
					 {
//						Control_group_point *p_grp=(Control_group_point *)buf;
						if(t)
						{
						 point_info->digital_analog=0;
						 point_info->units=1;
						 strcpy(gdescriptor,ptr.p_grp->description);
						 strcpy(glabel,ptr.p_grp->label);
						}
					 }
						break;
	 }
//	set_semaphore_dos();
//	 delete buf;
//	 clear_semaphore_dos();
	 if(des)
		 *des = gdescriptor;
	 if(label)
		 *label = glabel;

//	read_point(1, value, num_point);
//	return num_point;
	return SUCCESS;
}

int get_point_info1(Point_info *point_info)
{
 char *pbuf;//,buf[160];
 Point_Net p;
 int num_point,r;
 byte point_type;
 union  {
		Str_out_point *p_out;
		Str_in_point *p_in;
		Str_variable_point *p_var;
		Str_controller_point *p_con;
		Str_weekly_routine_point *p_wr;
		Str_annual_routine_point *p_ar;
		Str_program_point *p_prg;
		Control_group_point *p_grp;
		Str_monitor_point *p_amon;
		Point_info *pinfo;
		} ptr;

 memcpy(&p, &point_info->point, sizeof(Point_Net));
 if (!p.point_type) return ERROR_COMM;

 point_type = p.point_type-1;
 num_point = p.number;

 r = ptr_panel->info[point_type].str_size;
// memset(buf, 0, r);

 if( p.panel+1==Station_NUM )
 {
	switch (point_type) {
	 case OUT:
	 case IN:
	 case VAR:
	 case CON:
	 case WR:
	 case AR:
	 case PRG:
	 case AMON:
	 case GRP:
				 if(num_point < ptr_panel->table_bank[point_type])
						 pbuf = ptr_panel->info[point_type].address+num_point*r;
//						 memcpy(buf, ptr_panel->info[point_type].address+num_point*r, r);
				 break;
	 default:
		return ERROR_COMM;
	}
//	t=1;
	point_info->point_value=0;
	point_info->auto_manual=0;
	point_info->digital_analog=1;
	point_info->security=0;
	point_info->decomisioned=0;
 }
 else
	return ERROR_COMM;
 ptr.p_out = (Str_out_point *)pbuf;
 switch (point_type) {
	 case OUT:
//						if(t)
					 {
						point_info->point_value=ptr.p_out->value;
						point_info->auto_manual=ptr.p_out->auto_manual;
						point_info->digital_analog=ptr.p_out->digital_analog;
						point_info->security=ptr.p_out->access_level;
						point_info->decomisioned=ptr.p_out->decom;
						r = GetRange_Out(ptr.p_out->range);
						if(!ptr.p_out->digital_analog)
						{
							r -= DIG1;
							if(r < 0) r = 0;
						}
						point_info->units = r;
					 }
					 break;
	 case IN:
//					  if(t)
					 {
						point_info->point_value   =ptr.p_in->value;
						point_info->auto_manual   =ptr.p_in->auto_manual;
						point_info->digital_analog=ptr.p_in->digital_analog;
						point_info->decomisioned  =ptr.p_in->decom;
						r = GetRange_In(ptr.p_in->range);
						if(!ptr.p_in->digital_analog)
						{
							r -= DIG1;
							if(r < 0) r = 0;
						}
						point_info->units=r;
					 }
					 break;
	 case VAR:
//					 if(t)
					 {
						point_info->point_value=ptr.p_var->value;
						point_info->auto_manual=ptr.p_var->auto_manual;
						point_info->digital_analog=ptr.p_var->digital_analog;
						r = GetRange_Var(ptr.p_var->range);
						if(!ptr.p_var->digital_analog)
						{
							r -= DIG1;
							if(r < 0) r = 0;
						}
						point_info->units=r;
					 }
					 break;
	 case CON:
//					 if(t)
					 {
						 point_info->point_value = ptr.p_con->value;
						 point_info->auto_manual = ptr.p_con->auto_manual;
						 point_info->digital_analog=1;
						 point_info->units=procent;
					 }
					break;
	 case WR:
//						if(t)
						{
						 point_info->point_value=ptr.p_wr->value;
						 point_info->auto_manual=ptr.p_wr->auto_manual;
						 point_info->digital_analog=0;
						 point_info->units=1;
						}
						break;
	 case AR:
//						if(t)
						{
						 point_info->point_value=ptr.p_ar->value;
						 point_info->auto_manual=ptr.p_ar->auto_manual;
						 point_info->digital_analog=0;
						 point_info->units=1;
						}
						break;
	 case PRG:
//						if(t)
						{
						 point_info->point_value=ptr.p_prg->on_off;
						 point_info->auto_manual=ptr.p_prg->auto_manual;
						 point_info->digital_analog=0;
						 point_info->units=1;
						}
						break;
	 case AMON:
//						if(t)
						{
						 point_info->point_value=ptr.p_amon->status;
						 point_info->digital_analog=0;
						 point_info->units=1;
						}
				   	break;
	 case GRP:
//						if(t)
						{
						 point_info->digital_analog=0;
						 point_info->units=1;
						}
						break;
	 }
	 return SUCCESS;
}

int put_indiv_point(Point_Net point, Point_info *point_info)
{
 Delay(100);
 uint i = sizeof(Point_info);
 net_call(25+100, (point.point_type<<8)+point.number, (char *)point_info, &i, point.panel+1, networkaddress,NETCALL_RETRY);
}

int	put_point_info(Point_info *point_info)
{
 Point_Net *p;
 Point *q;
 byte point_type,num_point;
 p=&point_info->point;
 q = (Point *)p;
 point_type = p->point_type-1;
 num_point = p->number;
// memcpy(&n,p,2);
 if((local_panel && p->panel+1==Station_NUM) || (!local_panel &&  p->panel+1==Station_NUM && p->panel+1!=station_num))
 {
	switch (point_type) {
	 case OUT:
					 ptr_panel->outputs[num_point].digital_analog=point_info->digital_analog;
					 ptr_panel->outputs[num_point].auto_manual   =point_info->auto_manual;

					 if(point_info->auto_manual == MAN)
#ifndef WORKSTATION
						 put_point(*q,point_info->point_value , OPERATOR, point_info->digital_analog);
#else
	;
#endif
					 ptr_panel->outputs[num_point].access_level=point_info->security;
					 ptr_panel->outputs[num_point].decom=point_info->decomisioned;
					break;
	 case IN:
					 ptr_panel->inputs[num_point].digital_analog=point_info->digital_analog;
					 ptr_panel->inputs[num_point].auto_manual=point_info->auto_manual;

					 if(point_info->auto_manual == MAN)
#ifndef WORKSTATION
						 put_point(*q,point_info->point_value , OPERATOR, point_info->digital_analog);
#else
	;
#endif
						break;
	 case VAR:
					 ptr_panel->vars[num_point].digital_analog=point_info->digital_analog;
					 ptr_panel->vars[num_point].auto_manual=point_info->auto_manual;

					 if(point_info->auto_manual == MAN)
#ifndef WORKSTATION
						 put_point(*q,point_info->point_value , OPERATOR, point_info->digital_analog);
#else
	;
#endif
					 break;
	 case CON:
					break;
	 case WR:
					 ptr_panel->weekly_routines[num_point].auto_manual=point_info->auto_manual;

					 if(point_info->auto_manual == MAN)
#ifndef WORKSTATION
						 put_point(*q,point_info->point_value, OPERATOR);
#else
	;
#endif
					break;
	 case AR:
					 ptr_panel->annual_routines[num_point].auto_manual=point_info->auto_manual;
					 if(point_info->auto_manual == MAN)
#ifndef WORKSTATION
						 put_point(*q,point_info->point_value,OPERATOR);
#else
	;
#endif
					break;
	 case PRG:
					 ptr_panel->programs[num_point].auto_manual=point_info->auto_manual;

					 if(point_info->auto_manual == MAN)
#ifndef WORKSTATION
						 put_point(*q,point_info->point_value, OPERATOR);
#else
	;
#endif
					break;
	 case AMON:
					 ptr_panel->analog_mon[num_point].status=point_info->auto_manual;

					 if(point_info->auto_manual == MAN)
#ifndef WORKSTATION
						 put_point(*q,point_info->point_value, OPERATOR);
#else
	;
#endif
					break;
	 }
	}
	else
	{
	 put_indiv_point(*p, point_info);
	}
}

int writepropertystate(Point_Net point, int state, int t=0)
{
 int r=SUCCESS;
 Point *q;
 q = (Point *)&point;
 if( t || local_request(point.panel+1) )
 {
	switch (point.point_type-1) {
		 case GRP:
			 ptr_panel->control_groups[point.number].state = state;
			 break;
	 }
 }
 else
 {
	r=writepropertyservice(point, property_state, state);
 }
 return r;
}

int writepropertystate(BACnetObjectIdentifier obj, long lvalue, int t=0)
{
 Point_Net point;
 point.number = obj.instance-1;
 point.point_type   = obj.object_type_low+(obj.object_type_hi<<2) - T3000_OBJECT_TYPE + 1;
 point.panel        = Station_NUM-1;
 point.network      = NetworkAddress;
 writepropertystate(point, lvalue, t);
}

int writepropertyvalue(Point_Net point, long point_value)
{
 Point *q;
 int r=SUCCESS;
 q = (Point *)&point;
 if( local_request(point.panel+1) )
 {
	switch (point.point_type-1) {
	 case OUT:
					 if(ptr_panel->outputs[point.number].auto_manual == MAN)
#ifndef WORKSTATION
						 put_point(*q, point_value , OPERATOR);
#else
	;
#endif
					 break;
	 case IN:
					 if(ptr_panel->inputs[point.number].auto_manual == MAN)
#ifndef WORKSTATION
						 put_point(*q, point_value , OPERATOR);
#else
	;
#endif
						break;
	 case VAR:
					 if(ptr_panel->vars[point.number].auto_manual == MAN)
#ifndef WORKSTATION
						 put_point(*q, point_value , OPERATOR);
#else
	;
#endif
					 break;
	 case CON:
					break;
	 case WR:
					 if(ptr_panel->weekly_routines[point.number].auto_manual == MAN)
#ifndef WORKSTATION
						 put_point(*q, point_value , OPERATOR);
#else
	;
#endif
					break;
	 case AR:
					 if(ptr_panel->annual_routines[point.number].auto_manual == MAN)
#ifndef WORKSTATION
						 put_point(*q, point_value , OPERATOR);
#else
	;
#endif
					break;
	 case PRG:
					break;
	 }
 }
 else
 {
	r=writepropertyservice(point, property_value, point_value);
 }
 return r;
}

int writepropertyvalue(BACnetObjectIdentifier obj, long lvalue)
{
 Point_Net point;
 point.number = obj.instance-1;
 point.point_type   = obj.object_type_low+(obj.object_type_hi<<2) - T3000_OBJECT_TYPE + 1;
 point.panel        = Station_NUM-1;
 point.network      = NetworkAddress;
 writepropertyvalue(point, lvalue);
}

int	writepropertyauto(Point_Net point, int auto_manual)
{
 int r=SUCCESS;
 Point *q;
 q = (Point *)&point;
 if( local_request(point.panel+1) )
 {
	switch (point.point_type-1) {
	 case OUT:
					 ptr_panel->outputs[point.number].auto_manual=auto_manual;
					break;
	 case IN:
					 ptr_panel->inputs[point.number].auto_manual=auto_manual;
						break;
	 case VAR:
					 ptr_panel->vars[point.number].auto_manual=auto_manual;
					 break;
	 case CON:
					break;
	 case WR:
					 ptr_panel->weekly_routines[point.number].auto_manual=auto_manual;
					break;
	 case AR:
					 ptr_panel->annual_routines[point.number].auto_manual=auto_manual;
           check_annual_routine_flag=1;
					break;
	 case PRG:
					break;
	 }
 }
 else
 {
	r=writepropertyservice(point, property_auto_manual, auto_manual);
 }
 return r;
}

int	writepropertyauto(BACnetObjectIdentifier obj, int auto_manual)
{
 Point_Net point;
 point.number = obj.instance-1;
 point.point_type   = obj.object_type_low+(obj.object_type_hi<<2) - T3000_OBJECT_TYPE + 1;
 point.panel        = Station_NUM-1;
 point.network      = NetworkAddress;
 writepropertyauto(point, auto_manual);
}

void save_screen(char **screen)
{
/*
 float big;

	if(mode_text)
		big = 80*25*2;
	else
		big= ((float)((unsigned long)(640)*(unsigned long)(480)*4))/8/DIVIMAGE;
//		big = imagesize(ltop.x,ltop.y,rbottom.x,rbottom.y);

 mfarmalloc((char far **)screen, (unsigned long)big	);
 if( *screen==NULL )
//	if( (under1=(char far *)farmalloc((unsigned long)big))==NULL )
	 {
//		DisplayError("ERROR IN MEM ALLOCATION");
		exit(0);
		}

 hide_pointer();    // hides the mouse cursor during reading
										// from the video memory
 if(mode_text)
		mgettext(1, 1, 80, 25,(void *)*screen);
 else
//		mgetimage(ltop.x, ltop.y, rbottom.x, rbottom.y, under1);
 mmgetimage(0, 0, 639, 479,(signed char **)screen);

 display_pointer(); //displays the mouse cursor after
										//the reading has been accomplished
*/
};

/**************************************/

void restore_screen(char *screen)
{
/*
	hide_pointer();
	if(mode_text)
		mputtext(1, 1, 80, 25,(void *)screen);
	else
	 mmputimage(0, 0, 639, 479, (signed char *)screen);
//		mputimage(ltop.x, ltop.y, (void *)under1, COPY_PUT);

	mfarfree( screen );

	display_pointer();
*/
};

char *ltrim(char *text)
{
	int n,i;
	n=strlen(text);
	for (i=0;i<n;i++)
			if (text[i]!=' ')
					break;
	strcpy(text,text+i);
	return text;
}

//int net_call(int command, int arg, char *ptr, int length ,int panel, int sign, char compress)
//{
//}
unsigned int countlength(int command, int arg)
{
 uint length;
 byte no_points;
 Bank_Type tbank;
 int str_new_size=0;
 char *ptr;
	no_points = 1;
	tbank = *( Bank_Type *)&arg;        //arg
	switch( command )            //command
	{
		case OUT+1:
		case IN+1:
		case VAR+1:
		case CON+1:
		case WR+1:
		case AR+1:
		case PRG+1:
		case GRP+1:
		case AMON+1:
		case AY+1:
		case UNIT+1:
		case ALARMM+1:
			ptr = (char *)&ptr_panel->info[command-1];
			str_new_size = ((Info_Table *)ptr)->str_size;
			if( tbank.bank_type )
			{
				no_points = tbank.no_points;
			}
			else
			{
				no_points = tbl_bank[command-1];
			}
			break;
		case USER_NAME+1:
//			 str_new_size = 16+9+1+4+1+1+(2*((tbl_bank[GRP]%8)?tbl_bank[GRP]/8+1:tbl_bank[GRP]/8))+
//								 (2*((tbl_bank[PRG]%8)?tbl_bank[PRG]/8+1:tbl_bank[PRG]/8));
			 str_new_size = sizeof( Password_point );
			 length = 2+(uint)(tbl_bank[USER_NAME]) * str_new_size;
			 return length;
			 break;
		case WR_TIME+1:
			str_new_size = 9*sizeof(Wr_one_day);
			break;
		case AR_Y+1:
			str_new_size = 46;
			break;
		case 20:
			Point *point;
			point = (Point *)&arg;
			no_points = 1;
			switch( point->point_type )
			{
				case OUT+1:
				case IN+1:
				case VAR+1:
				case CON+1:
				case WR+1:
				case AR+1:
				case PRG+1:
				case TBL+1:
				case AMON+1:
				case GRP+1:
				case AY+1:
				{
					ptr = (char *)&ptr_panel->info[point->point_type-1];
					str_new_size = ((Info_Table *)ptr)->str_size;
					break;
				}
				case DIGITAL_MONITOR:
					 break;
				default :
				{
						printf( "Wrong point type" );
						break;
				}
			}
			break;
		default:
			no_points = 0;
			break;
	}
	length = (uint)(no_points) * str_new_size;
	return length;
}

int buildsource(int others)
{
 int s;
 s = Station_NUM;
 if( (others&NETCALL_SOURCE255)==NETCALL_SOURCE255 )
	 s = 255;
 return s;
}

int net_call(int command, int arg,  char *data, uint *length , int dest,
				 int network, int others, int timeout,
				 char *returnargs, int *length_returnargs,
				 char *sendargs, int length_sendargs, char bytearg, int port)
{
 char dupl,id;
 char servicerequest[MAXAPDUSIZE];
 int  task,i,j,com, ctype, command_number, status, source, others1;
 uint length1, bank = arg, length2=0, lt, lt2;
 int service,event;
 BACnetPDU pdutype;
 unsigned long l;
 ROUTER_PARAMETERS r;

 others1 = others;
 if(command==COMMAND_50 && arg==ESTABLISH_CONNECTION_PORT)
 {
	 if( network==0xFFFF )
	 {
		com = dest;
		if( (network=checkport(com)) < 0 )
		 return ERROR_COMM;
	 }
	 if( (Routing_table[network].status&PTP_ACTIVE)==PTP_ACTIVE ) return SUCCESS;
	 r.termination_time_value = timeout;
	 remote_net = 0xFFFF;
	 router(N_UNITDATArequest, Establish_Connection_To_Network, &r, network);
	 l = timestart;
	 while( timestart < l+timeout )
	 {
		if( Routing_table[network].status==PTP_ACTIVE )
		{
			if( Routing_table[network].Port.network || remote_net != 0xFFFF )
			{
			 j=findroutingentry(0, ((class PTP *)Routing_table[network].ptr)->panel_info1.network, i, 0);  // find a duplicate
//			 if ( remote_net == comm_info[com].NetworkAddress )
			 if ( j!=-1 )
			 {
				 remote_net = 2;
				 while(1)
				 {
					if ( findroutingentry(0, remote_net, i, 0)==-1 ) break;
					remote_net++;
				 }
				 ((class PTP *)Routing_table[network].ptr)->panel_info1.network = remote_net;

/*
				for(i=0; i<MAX_Routing_table; i++)
				{
				 if( (i!=network) && (Routing_table[i].status&PORT_ACTIVE)==PORT_ACTIVE )
					if( Routing_table[i].Port.network==Routing_table[network].Port.network )
						Routing_table[i].reachabil_status = USER_UNREACHABIL;
				}
*/
				 router(N_UNITDATArequest, I_Am_Router_To_Network_Prop, NULL, ((class PTP *)Routing_table[network].ptr)->port_number);
//				return ERROR_NET;
			 }
//			 else
			 if( Routing_table[network].Port.network )
			 {
				 if( (others&NETCALL_NOTCHANGENETADR)!=NETCALL_NOTCHANGENETADR )
				 {
					networkaddress = Routing_table[network].Port.network;
					station_num = Routing_table[network].Port.address;
				 }
				 return SUCCESS;
			 }
			}
		}
		if( (others&NETCALL_NOTCTRLBREAK)!=NETCALL_NOTCTRLBREAK )
		if( bioskey_new(1) == CTRLBREAK )
		{
		 return ERROR_COMM;
		}
	 }
	 return ERROR_COMM;
 }

// if( (command==COMMAND_50 && (arg==STATION_LIST_COMMAND || arg==PANEL_INFO1_COMMAND)) || station_list[dest-1].state )
	if(tswitch==PROJ || tswitch==MISCELLANEOUS)	task = -1;
	else task = tswitch;
	pdutype = others&NETCALL_BACnetPduType;
  service = ConfirmedPrivateTransfer;
	status = RS232_ERROR;
	switch (pdutype) {
	 case BACnetConfirmedRequestPDU:
		event = CONF_SERVrequest;
		break;
	 case BACnetUnconfirmedRequestPDU:
		event = UNCONF_SERVrequest;
		break;
	 default:
		return ERROR_COMM;  //eroare
	}

	id = lastid++;
// flowcontrol = AEFLOWCONTROL;
	length1 = 0;

	if( service == ConfirmedPrivateTransfer )
	{
	 if(command > 100 && command < 200)
	 {
		ctype = WRITE;
		command_number = command-100;
	 }
	 else
	 {
		ctype = READ;
		command_number = command;
		if(length)
		 *length = 0;
	 }
	 if (ctype == WRITE)
	 {
		if(!length)
			length2 = countlength(command_number, arg);
//		else
//		  *length = countlength(command_number-1, arg);
	 }
	 if (ctype == READ)
	 if (length) *length = 0;
//	  time = (ctype==WRITE?10:16);
	 if(command_number == 22 ) timeout = 30;
	 if(command_number == 50 && (arg==40 || arg==41 || arg==42) ) timeout = 30;
//	 showsign = others&NETCALL_SIGN;
	 source = buildsource(others);
	 if( (others&NETCALL_RETRY)==NETCALL_RETRY )
		others1 = others & (~NETCALL_RETRY);
	 if(length)
		 lt = *length;
   lt2 = length2;
	 status=ClientTransactionStateMachine(event, ConfirmedPrivateTransfer,	AEFLOWCONTROL,
														network, dest, source,
														id, data, length?length:&length2,
														command, arg, VendorID, timeout,
														returnargs, length_returnargs,
														sendargs, length_sendargs, bytearg, task, port, others1);
//	 showsign=0;
	 if(!status)
		 return SUCCESS;
	 others1 = others;
	 if( (others&NETCALL_RETRY)==NETCALL_RETRY )
	 {
		if( (others&NETCALL_SIGN)==NETCALL_SIGN )
			data_const=data_length_const=0;
		if(length)
			*length = lt;
		length2 = lt2;
		status=ClientTransactionStateMachine(event, ConfirmedPrivateTransfer,	AEFLOWCONTROL,
														network, dest, source,
														id, data, length?length:&length2,
														command, arg, VendorID, timeout,
														returnargs, length_returnargs,
														sendargs, length_sendargs, bytearg, task, port, others);
	 }
	 if(status)
	 {
			if( (others&NETCALL_NOTTIMEOUT)!=NETCALL_NOTTIMEOUT )
				result_ser(status, 1);

			if(status == USER_ABORT)
			 return USER_ABORT;
			else
			 return ERROR_COMM;
	 }
	 return SUCCESS;
	}
}

int writepropertyservice(Point_Net point, T3000PropertyIdentifier property, long val)
{
	int r;
	uint l=0;
	char id, buf[100];
	BACnetObjectIdentifier obj;
	if( point.network == 0xFFFF ) point.network = networkaddress;
	id = lastid++;
	obj.proprietary = 1;
	obj.object_type_low = ((int)(T3000_OBJECT_TYPE + point.point_type - 1))&0x0003;
	obj.object_type_hi  = ((int)(T3000_OBJECT_TYPE + point.point_type - 1))>>2;
	obj.instance    = point.number+1;
	buf[0] = 0x0B;           //Context Tag 0(L=3)
	memcpy(&buf[1], &obj, 3);
	buf[4] = 0x1A;           //Context Tag 1(L=2)
	memcpy(&buf[5], &property, 2);
	buf[7] = 0x3E;           //Opening Tag 3
	l = 8;
	switch( property ){
	 case property_value:
			buf[l++] = 0x34;       //Application Tag 3(L=4)
			buf[l++] = (char)(val>>24);
			buf[l++] = (char)((val>>16)&0x0FF);
			buf[l++] = (char)((val>>8)&0x0FF);
			buf[l++] = (char)(val&0x0FF);
			break;
	 case property_auto_manual:
			buf[l++] = 0x31;       //Application Tag 3(L=1)
			buf[l++] = (char)val;
			break;
	 case property_state:
			buf[l++] = 0x31;       //Application Tag 3(L=1)
			buf[l++] = (char)val;
			break;
	}
	buf[l++] = 0x3F;           //Closing Tag 3
	r=ClientTransactionStateMachine(CONF_SERVrequest, WriteProperty,	AEFLOWCONTROL,
														point.network, point.panel+1, Station_NUM, id,
														buf, &l, 0, 0, VendorID);
	return r;
}


