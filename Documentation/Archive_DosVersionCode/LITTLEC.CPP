//#define MAIN
#define __LITTLEC
extern void *newalloc(long size);
extern void newdelete(void *ptr);
#include <graphics.h>
#include <setjmp.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <alloc.h>
#include <graphics.h>
#include <windows.h>
#include "t3000def.h"
#include "mtkernel.h"
#include "aio.h"
#include "gedit.h"
#include "parser.h"
//#include "rs485.h"

#define LONGTIMETEST -123456789L
#define MAX_GOTO 100

extern int mode_text;
extern int ipxport, rs485port;

extern Panel *ptr_panel;
extern void creategauge(GWindow **gauge, char *buf);
extern void deletegauge(GWindow **gauge);
extern void showgauge(GWindow *w, long coef, long ntot);
extern int local_request(int panel, int network);

extern int networkaddress;
extern int Station_NUM;
extern unsigned long t;
int DORU_SYSTEM=0;
extern GetPrgFileNames(void) ;    	/* get the prg names */

//void cod_putint(char *ptr, int j, int type);
int find_var_def(char *var_name);
char *ispoint(char *token,int *num_point,byte *var_type, byte *point_type, int *num_panel, int *num_net, int network=0, byte panel=0, int *netpresent=0);
extern char *ltrim(char *text);
extern char *rtrim(char *text);
void get_label(void);
char *islabel(char *token,int *num_point,byte *var_type,byte *point_type, int *num_panel );
void prescan2(void) ; // find the location of all functions and global
int prescan1(void) ; // find the location of all functions and global
int define_var(char *token, int t=FLOAT_TYPE,int l=0,int c=0, int lstr=LENGTHSTRING);
void assig_var(char *var_name, int value);
void write_cod(int type,int n_var,int v1, char *var1, float fvar1,
												int v2, char *var2, float fvar2,
												int v3, char *var3, float fvar3);
void get_comment(char *);
int pcodvar(int cod,int v,char *var,float fvar,char *op,int Byte);
char *look_label(int panel, int point_type, int num, int network);
void eval_exp(float *) ;
extern int checkpointpresence(int num_point,int point_type,int num_panel,int num_net, int panel, int network);
extern int checkmaxpoints(int num_point,int point_type,int num_panel,int num_net);
extern float atofproc(char *avalue);
extern void parse_atom( float  *value );
extern void parse_exp5( float *value );
extern void parse_exp4( float *value );
extern void parse_exp3( float *value );
extern void parse_exp2( float *value );
extern void parse_exp1( float *value );
extern void parse_exp( float *value );
int parse_then_else();
void parse2_then_else();
void write_cod_d(int type,int n_var, int v1, char *var1, float fvar1,
																	 int v2, char *var2, float fvar2,
																	 int v3, char *var3, float fvar3);
extern struct remote_local_list  remote_local_list[MAXREMOTEPOINTS];
extern int ind_remote_local_list;

extern XmsDes *Des;
extern int  station_num;
extern int local_panel;
extern unsigned char tbl_bank[MAX_TBL_BANK];

/* This array is used by eval_exp1() */
extern char relops[8]  ;
extern char logops[7]  ;
extern char huge *lin;

/* these were declared as external in the parser */
float ttime;
unsigned long ttimed;
char *prog ;
char *p_buf;
jmp_buf e_buf ;

FILE *fp;
char null_buf[10],cod_line[150],label[9];
//int n_local,n_global;
GWindow *gaugep;
long pos,vpos;
unsigned line_value;
long long_line_value;
int int_value,cur_scope,cur_index,len_cod_linie;
int ncod;
int error;
//int panel,panel_sub;
int n_var,n_var1,n_var2,for_count,then_else,ind_cod_line,next_then_else,next_else_else;
char eoi=NL;
char eol;
char argcall[40];

struct line_table_str {
	 unsigned go_to;
	 int go_to_pos;
	 int for_count;
	 int for_pos;
	 int next_pos;
	 unsigned line;
	 int pos;
	 };
struct line_table_str *line_table;
//int index_line_table;

struct buf_str *buf_v;      // buf[MAX_VAR_LINE];
struct buf_str huge buf2[7];

struct  dalarm {
			int line;
			int pos;
			} huge dalarm[25];
int  wait[15][2];
int index_wait=0;

struct  go_to_str {
			unsigned line;
			unsigned go_to;
			int pos;
         };

struct  go_to_str *go_to;

int index_go_to;
int index_dalarm;

int index_buf,index_op,type_eval;
int id;
float res;

unsigned *renum;
int ind_renum;
int renumvar;

struct variable_table *vars_table;
//struct variable_table vars_table[MAX_Var];

//int position_table[40][30];
//int index_position_table;

int index_vars_table;
int lline;

char outdir[65];
char indir[65];
char infile[65];

struct func_table {
 char func_name[15] ;
 char tok ;
} func_table[] = {
 "ABS",ABS,
 "AVG",AVG,
 "CONPROP", CONPROP,
 "CONRATE", CONRATE,
 "CONRESET", CONRESET,
 "CLEARPORT", CLEARPORT,
 "DOW",DOW,
 "DOM",DOM,
 "DOY",DOY,
 "MOY",MOY,
 "INPUT",INKEYD,
 "INT",INT,
 "INTERVAL",INTERVAL,
 "LN",LN,
 "LN-1",LN_1 ,
 "LN_1",LN_1 ,
 "MAX",MAX,
 "MIN",MIN,
 "OUTPUT",OUTPUTD,
 "POWER-LOSS",POWER_LOSS,
 "POWER_LOSS",POWER_LOSS,
 "SCANS",SCANS,
 "SQR",SQR,
 "STATUS",Status,
 "RUNTIME",RUNTIME,
 "TBL",Tbl,
 "TIME",TIME,
 "TIME_FORMAT",TIME_FORMAT,
 "TIME-ON",TIME_ON,
 "TIME_ON",TIME_ON,
 "TIME-OFF",TIME_OFF,
 "TIME_OFF",TIME_OFF,
 "WR-ON",WR_ON,
 "WR_ON",WR_ON,
 "WR-OFF",WR_OFF,
 "WR_OFF",WR_OFF,
 "SENSOR-ON",	SENSOR_ON,
 "SENSOR_ON",	SENSOR_ON,
 "SENSOR-OFF", SENSOR_OFF,
 "SENSOR_OFF", SENSOR_OFF,
 "UNACK",UNACK,
 "USER-A",USER_A,
 "USER_A",USER_A,
 "USER-B",USER_B,
 "USER_B",USER_B,
 "NOT", NOT,
 "SUNDAY", SUN,
 "MONDAY", MON,
 "TUESDAY", TUE,
 "WEDNESDAY", WED,
 "THURSDAY", THU,
 "FRIDAY", FRI,
 "SATURDAY", SAT,
 "JANUARY", JAN,
 "FEBRUARY", FEB,
 "MARCH", MAR,
 "APRIL", APR,
 "MAY", MAY,
 "JUNE", JUN,
 "JULY", JUL,
 "AUGUST", AUG,
 "SEPTEMBER", SEP,
 "OCTOBER", OCT,
 "NOVEMBER", NOV,
 "DECEMBER", DEC,
 "",ENDPRG
 };

struct commands {
 char command[15] ;
 char tok ;
} table[] = { /* Commands must be enetered lower case */
 "ALARM",   Alarm,
 "ALARM-AT",ALARM_AT,
 "ALARM_AT",ALARM_AT,
 "CALL",    CALLB,
 "CLEAR",   CLEARX,
 "CLOSE",   CLOSE,
 "DALARM",  DALARM,
 "DECLARE", DECLARE,
 "DISABLE",	DISABLEX,
 "ENABLE",  ENABLEX,
 "END",     ENDPRG,
 "FOR",     FOR,
 "TO",      TO,
 "STEP",    STEP,
 "GOSUB",	  GOSUB,
 "GOTO",    GOTO,
 "HANGUP",  HANGUP,
 "IF",      IF,
 "IF+",     IFP,
 "IF-",     IFM,
 "THEN",    THEN,
 "ELSE",    ELSE,
 "LET",	    LET,
 "MOD",     MOD,
 "NEXT",    NEXT,
 "ON",      ON,
 "ON-ALARM",    ON_ALARM,
 "ON_ALARM",    ON_ALARM,
 "ON-ERROR",    ON_ERROR,
 "ON_ERROR",    ON_ERROR,
 "OPEN",        OPEN,
 "PHONE",       PHONE,
 "PRINT",       PRINT,
 "PRINT-AT",    PRINT_AT,
 "PRINT_AT",    PRINT_AT,
 "REM",         REM,
 "REMOTE-GET",  REMOTE_GET,
 "REMOTE_GET",  REMOTE_GET,
 "REMOTE-SET",  REMOTE_SET,
 "REMOTE_SET",  REMOTE_SET,
 "RETURN",      RETURN,
 "RUN-MACRO",   RUN_MACRO,
 "RUN_MACRO",   RUN_MACRO,
 "SET-PRINTER", SET_PRINTER,
 "SET_PRINTER", SET_PRINTER,
 "START",       STARTPRG,
 "STOP",        STOP,
 "WAIT",        WAIT,
 "AND",         AND,
 "OR",          OR,
 "XOR",         XOR,
 "DIM",         DIM,
 "INTEGER",     INTEGER_TYPE,
 "STRING",      STRING_TYPE,
 "BYTE",        BYTE_TYPE, 
 "FLOAT",       FLOAT_TYPE,
 "LONG",        LONG_TYPE,
 "" ,           ENDPRG /* marks the end of the table */
 };
/* "if" , IF ,
 "else" , ELSE ,
 "for" , FOR ,
 "do" , DO,
 "while" , WHILE ,
 "char" , CHAR ,
 "int" , INT ,
 "return" , RETURN ,
 "REM" ,REM,
 "end" , END ,
 "" , END  marks the end of the table */


long coef;
char token[80]  ;
char token_type  ;
char tok ;

static char *time_table;
int ind_time_table;
char *local_table;
int ind_local_table;

char *code;
int ind_code;

int ret_value ; /* function return value */

extern void get_nl(void);
extern void putback(void) ;
extern void sntx_err(int err, int err_true = TRUE );
int load_program(char *p , char *fname) , find_var(char *s) ;
extern int get_token(void) ;

//FILE *pmes;
char *pmes;
GEdit *pedit;
mmain ( GEdit *ppedit)
{
	int n,i,j,k,m;
	char fname[65],*p;
	unsigned int Byte;
	int lx,ly,rx,ry;
	eoi=NL;
	eol=0;
	t=0;
//	n_local=n_global=0;
	ncod=error=n_var=n_var1=for_count=then_else=ind_cod_line=next_then_else=0;
	next_else_else=ret_value=index_vars_table=lline=index_buf=index_op=type_eval=0;
	index_wait=index_go_to=index_dalarm=ind_renum=0;
//	index_position_table=ind_renum=0;
	id=res=0;
	ind_code=0;


	set_semaphore_dos();

	//  local_table[4000] , time_table[300]
	local_table = new char[4000+300+sizeof(struct variable_table)*MAX_Var+
								  sizeof(struct line_table_str)*MAX_LINE+sizeof(struct buf_str)*MAX_VAR_LINE+
								  sizeof(go_to_str)*MAX_GOTO];
	time_table = local_table+4000;
	vars_table = (struct variable_table *)(time_table+300);
	line_table = (struct line_table_str *)(((char *)vars_table)+sizeof(struct variable_table)*MAX_Var);
	buf_v = (struct buf_str *)(((char *)line_table)+sizeof(struct line_table_str)*MAX_LINE);
	go_to = (struct go_to_str *)(((char *)buf_v)+sizeof(struct buf_str)*MAX_VAR_LINE);
	clear_semaphore_dos();
	memset(local_table, 0, 4000+300+sizeof(struct variable_table)*MAX_Var+
								  sizeof(struct line_table_str)*MAX_LINE+sizeof(struct buf_str)*MAX_VAR_LINE+
								  sizeof(go_to_str)*MAX_GOTO);
	if( !local_table )
		  return 2;

//	memset(go_to, 0, 20 * sizeof(struct  go_to));
//	memset(time_table, 0, 200);
//	memset(local_table,0,sizeof(local_table));
	ind_local_table = ind_time_table = 0;
	pedit=ppedit;
	code = pedit->code;
	pmes = pedit->mesbuf;
	p_buf = pedit->editbuf;
	*pmes = 0;

//	set_semaphore_dos();

//	 set the program pointer to the beginning of program buffer
	prog = p_buf;

	for_count = 0;
	if (renumvar)
	{
	 set_semaphore_dos();
	 renum=new unsigned [MAX_LINE];
	 clear_semaphore_dos();
	 if( renum==NULL )
	 {
	  if( local_table )
		{
			set_semaphore_dos();
			delete local_table;
			clear_semaphore_dos();
		}
		*pmes = 0;
		return 0;
	 }
	 get_token() ;
	 while( tok!=FINISHED)  {
		if(token_type==NL) 	get_token() ;
		if((token_type==NL) || (tok==FINISHED)) continue;
		renum[ind_renum++] = atoi(token);
		get_nl();
		get_token() ;
	 }
	}
	prog = p_buf;
	long length=1;
	while(  *prog != 0  )
	{
	 if (*prog++ == 13) length++;
	}
//	coef = (float)length / 20.;
	coef = (length*1000L/20000L)*1000L + ((length*1000L)%20000L)*1000L/20000L ;
	if (renumvar)
		creategauge(&gaugep,"Renum");
	else
		creategauge(&gaugep,"Parsing");

/*
	set_semaphore_dos();
	vars_table = new struct variable_table[MAX_Var];
	line_table = new struct line_table_str [MAX_LINE];
	buf_v      = new struct buf_str [MAX_VAR_LINE];
	memset(buf_v, 0, MAX_VAR_LINE * sizeof(struct buf_str));
	memset(line_table, 0, MAX_LINE * sizeof(struct line_table_str));
	clear_semaphore_dos();
*/
	memset(local_table, 0, 4000+300+sizeof(struct variable_table)*MAX_Var+
									sizeof(struct line_table_str)*MAX_LINE+sizeof(struct buf_str)*MAX_VAR_LINE+
									sizeof(go_to_str)*MAX_GOTO);

	prog = p_buf;
	prescan1() ; // find the location of all functions and global
	deletegauge(&gaugep);
	if (renumvar)
	{
		 set_semaphore_dos();
		 delete renum;
		 if( local_table )
			delete local_table;
		 clear_semaphore_dos();
		 *pmes = 0;
		 return 0;
	}
	for(i=0;i<lline;i++)
		 if(line_table[i].go_to!=0)
		 {
			 for(k=0;k<index_go_to;k++)
			 {
				for(j=0;j<lline;j++)
					 if(line_table[j].line==go_to[k].go_to)
							break;
				if (j==lline)
				{
						sntx_err(NOT_LINE) ;
						break;
				}
			 }
		 }

	if (error || for_count!=0)
	{
		 set_semaphore_dos();
		 if( local_table )
			delete local_table;
		 clear_semaphore_dos();
		 *pmes = 0;
		 return 2;
	}

	prog = p_buf;
	lline = 0;
	memcpy(code,null_buf,2);
	code += 2;
	for_count=0;
	index_go_to = 0;
	creategauge(&gaugep,"Generating code");
	prescan2() ; // find the location of all functions and global
	deletegauge(&gaugep);
//	cod_putint(pedit->code, ncod, pedit->ptrprg->type);
	memcpy(pedit->code,&ncod,2);
/*
	if (!DORU_SYSTEM)
	{
		memcpy(code,null_buf,4);
		code += 4;
	}
	if (!DORU_SYSTEM)
	{
	 if (index_wait)
	 {
			 Byte=ncod+2;
			 memcpy(code-2,&Byte,2);
	 }
	 for(j=index_wait-1;j>=0;j--)
	 {
	  Byte=code-pedit->code+2-2;

	  memcpy(pedit->code+wait[j][0],&Byte,2);
	  memcpy(code,null_buf,4);
	  code += 4;
	  Byte='\x1E';
	  memcpy(code,&Byte,1);
	  code += 1;
	  if(j)
	  {
		 memcpy(code,&wait[j-1][1],2);
		 code += 2;
	  }
	  else
	  {
		 memcpy(code,null_buf,2);
		 code += 2;
	  }
	 }

	 for(j=lline;j>0;j--)
	 {
	  for(k=0;k<index_dalarm;k++)
		if(dalarm[k].line==j)
			 break;
	  if (k!=index_dalarm)
	  {
			vpos = code-pedit->code-2;
			memcpy(pedit->code+dalarm[k].pos,&vpos,2);
			Byte='\x2C';
			memcpy(code,&Byte,1);
			code += 1;
			Byte=0;
			memcpy(code,&Byte,2);
			code += 2;
	  }
	  for(i=index_vars_table-1;i>=0;i--)
			if (vars_table[i].type==LOCAL_VAR)
						if (vars_table[i].scope[0].line==j)
						{
								vpos=code-pedit->code-2;
								for(m=0;m<vars_table[i].col_position_table;m++)
								{
										memcpy(pedit->code+position_table[vars_table[i].position][m],&vpos,2);
								}
								Byte='\x81'+vars_table[i].name[0]-'A'+1;
								memcpy(code,null_buf,2);
								code += 2;
								memcpy(code,&Byte,1);
								code += 1;
								memcpy(code,null_buf,2);
								code += 2;
						 }
	 }
	}
*/

//  go_to

		for(i=0;i<lline;i++)
		{
		 if(line_table[i].go_to!=0)
		 {
				for(k=0;k<index_go_to;k++)
				{
					for(j=0;j<lline;j++)
						if((go_to[k].line==i+1) && line_table[j].line==go_to[k].go_to)
							break;
					if (j!=lline)
					{
							Byte=line_table[j].pos-2+2;
//							cod_putint(pedit->code+go_to[k].pos, Byte, pedit->ptrprg->type);
							memcpy(pedit->code+go_to[k].pos,&Byte,2);
					}
				}
		 }
		 if(line_table[i].for_pos!=0)
		 {
				for(j=i+1;j<lline;j++)
					 if(line_table[j].for_count==line_table[i].for_count)
							break;
				if (j==lline-1)
					 Byte=ncod+2;
				else
					 Byte=line_table[j+1].pos-2+2;

//				cod_putint(pedit->code+line_table[i].for_pos, Byte, pedit->ptrprg->type);
				memcpy(pedit->code+line_table[i].for_pos,&Byte,2);
				if(!DORU_SYSTEM)
					Byte=line_table[i].pos-2+5;
				else
					Byte=line_table[i].pos ;
//				cod_putint(pedit->code+line_table[j].next_pos, Byte, pedit->ptrprg->type);
				memcpy(pedit->code+line_table[j].next_pos,&Byte,2);
		 }
		}

		if(DORU_SYSTEM)
			Byte=0xfe;
		else
			Byte=0xff;

		if( ncod+2+1 >= PROGRAM_SIZE )
		{
		 set_semaphore_dos();
		 if( local_table )
			delete local_table;
		 clear_semaphore_dos();
		 *pmes = 0;
		 return 3;
		}
		memcpy(code,&Byte,1);
		code += 1;
/*
		if (!DORU_SYSTEM)
		{
		 Byte=ncod+3;
		 memcpy(code-3,&Byte,2);
		}
*/
		if (DORU_SYSTEM)
		{
		 if( (ncod+2)+2+2+ind_local_table+2+ind_time_table >= PROGRAM_SIZE )
		 {
		  set_semaphore_dos();
			if( local_table )
			delete local_table;
			clear_semaphore_dos();
		  *pmes = 0;
			return 3;
		 }
		 Byte=0;
//		 cod_putint(code, Byte, pedit->ptrprg->type);
		 memcpy(code,&Byte,2);
		 code += 2;
		 Byte =  ind_local_table;
//		 cod_putint(code, Byte, pedit->ptrprg->type);
		 memcpy(code,&Byte,2);
		 code += 2;
		 memcpy(code, local_table, Byte);
		 code += Byte;
//		 cod_putint(code, ind_time_table, pedit->ptrprg->type);
		 memcpy(code,&ind_time_table,2);
		 memcpy(code+2,time_table,ind_time_table);
		}

	pedit->length_code=code-pedit->code;

	for(i=0;i<index_vars_table;i++)
	{
	 if(vars_table[i].panel!=pedit->panel && vars_table[i].type!=LOCAL_VAR)
	 {
		for(j=0;j<ind_remote_local_list;j++)
		{
			if(remote_local_list[j].point.network==vars_table[i].network &&
				remote_local_list[j].point.panel==vars_table[i].panel-1 &&
				remote_local_list[j].point.point_type==vars_table[i].point_type+1 &&
				remote_local_list[j].point.number==vars_table[i].num_point-1 &&
				remote_local_list[j].index<1000)
						{
						 remote_local_list[j].index += 1000;
						 break;
						}
		}
		if(j==ind_remote_local_list)
		{
			 remote_local_list[j].point.network=vars_table[i].network;
			 remote_local_list[j].point.panel=vars_table[i].panel-1;
			 remote_local_list[j].point.point_type=vars_table[i].point_type+1;
			 remote_local_list[j].point.number=vars_table[i].num_point-1;
			 remote_local_list[j].index=-1;
			 ind_remote_local_list++;
			 if( ind_remote_local_list >= MAXREMOTEPOINTS )
			 {
		    set_semaphore_dos();
				if( local_table )
				 delete local_table;
				clear_semaphore_dos();
				*pmes = 0;
				return 4;
			 }
		}
	 }
	}

/*
	memcpy(pmes,"Program compiled, 0 errors",26);
	pmes += 26;
	*pmes++ = 0x0d;
*/
	*pmes = 0;

	set_semaphore_dos();
	if( local_table )
			delete local_table;
	clear_semaphore_dos();
  *pmes = 0;
	return 0;
}	/* end of main */

void  get_comment(char *comment)
{
	int i=0;
	while( i++ < 79 && *prog!=13 && *prog)
	{
		*(comment++)=*(prog++);
	}
	while( *prog!=13 && *prog )
	{
		prog++;
	}
//	if (*prog)
//		prog=prog+2;
	*comment=0x0;
}

char *islabel(char *token,int *num_point,byte *var_type,byte *point_type, int *num_panel)
{
 char *p;
 int i,j;

 if(!local_panel)
 {
  p=0;
  if(Des)
  {
		p=Des->islabel(token,num_point,var_type,point_type,num_panel);
	}
	if( p )
		return(p);
 }

 for(i=OUT;i<=AY;i++)
//		for(j=0;j<ptr_panel->info[i].max_points;j++)
		for(j=0;j<ptr_panel->table_bank[i];j++)
				 {
					p = 0;
					if(i!=CON)
					{
					switch (i) {
						case OUT:
									p = ptr_panel->outputs[j].label;
									break;
						case IN:
									p = ptr_panel->inputs[j].label;
									break;
						case VAR:
									p = ptr_panel->vars[j].label;
									break;
						case CON:
//									p = ptr_panel->controllers[j].label;
									break;
						case WR:
									p = ptr_panel->weekly_routines[j].label;
									break;
						case AR:
									p = ptr_panel->annual_routines[j].label;
									break;
						case PRG:
									p = ptr_panel->programs[j].label;
									break;
						case GRP:
									p = ptr_panel->control_groups[j].label;
									break;
						case AMON:
									p = ptr_panel->analog_mon[j].label;
									break;
						case AY:
									p = ptr_panel->arrays[j].label;
									break;
						default:
									break;
						}
					 if(p)
					 if(!strcmp(rtrim(p),rtrim(token)))  // de verificat duplicate
						{
						 *var_type = LABEL_VAR;
						 itoa(Station_NUM,token,10);
						 strcat(token,lin);
						 strcat(token,ptr_panel->info[i].name);
						 itoa(j+1,&token[strlen(token)],10);
						 *num_point = j+1;
						 *point_type = i;
//						 *num_panel = ptr_panel->GlPanel;
						 *num_panel = Station_NUM;
						 return p;
						}
					}
				}
 p=0;
 if(local_panel)
 {
	if(Des)
	{
		p=Des->islabel(token,num_point,var_type,point_type,num_panel);
	}
 }
 return(p);
}

char *ispoint(char *token,int *num_point,byte *var_type, byte *point_type, int *num_panel, int *num_net, int network, byte panel, int *netpresent)
{
int i,j,k,l;
char pc[11],*p,*q,buf[21],*tok;
			 tok = token;
			 if(netpresent) *netpresent = 0;
			 *num_net = network;
			 if(strlen(token)==0) return 0;
			 if ((q=strchr(token,'.'))!=NULL)
			 {
						memcpy(pc,token,min( (int)(q-token),10));
						pc[min((int)(q-token),10)]=0;
						q++;
						*num_net = atoi(pc);
						token = q;
						if(netpresent)
							*netpresent = *num_net;
			 }
			 if ((q=strchr(token,'-'))!=NULL)
			 {
						memcpy(pc,token,min( (int)(q-token),10));
						pc[min((int)(q-token),10)]=0;
						q++;
						*num_panel = atoi(pc);
						if ( *num_panel>32 || *num_panel==0 )
										 q=token;
			 }
			 else
			 {
					for(l=0;l<3 && token[l]!=0;l++)
						if (token[l]<'0' || token[l]>'9')
								 break;
					q=token+l;
					memcpy(pc,token,l);
					pc[l]=0;
					*num_panel = atoi(pc);
					if (*num_panel==0)
					  *num_panel = panel;
					if ( *num_panel>32 && strlen(pc) )
										 return(islabel(token,num_point,var_type,point_type,num_panel));
			 }
			 if ((p=strpbrk(q, "123456789"))!=NULL)
			 {
				memcpy(pc,q,p-q);
				pc[p-q]=0;
				for(k=OUT;k<=AY;k++)
					if(k!=DMON)
					 if (!strcmp(pc,ptr_panel->info[k].name))
						 break;
				if (k<=AY)
					{
					if (p==NULL) {
												memcpy(pmes,"error line : ",13);
												pmes += 13;
												itoa(lline,pmes,10);
												pmes += strlen(pmes);
												*pmes++ = 0x0d;
//												fprintf(pmes,"error line %d\n",line);
												error=TRUE;return 0;
												}
					else  if ((strlen(p)==1) && (*p=='0'))
								{
									memcpy(pmes,"error line : ",13);
									pmes += 13;
									itoa(lline,pmes,10);
									pmes += strlen(pmes);
									*pmes++ = 0x0d;
//								fprintf(pmes,"error line %d\n",line);
									error=TRUE;return 0;
									}
								else {
											for(l=0;l<strlen(p);l++)
												 if (p[l]<'0' || p[l]>'9')
														 break;
											if (l<strlen(p))
												 return(islabel(token,num_point,var_type,point_type,num_panel));
											else
													 {
//														itoa(panel,buf,10);
                            buf[0] = 0;
														if(netpresent)
															if(*netpresent)
															{
																itoa(*num_net,buf,10);
     															strcat(buf,".");
															}
														itoa(*num_panel,&buf[strlen(buf)],10);
														*num_point=atoi(p);
														*point_type = k;
														if(*num_panel<10 || *num_point<100)
															strcat(buf,"-");
														strcat(buf,pc);
														strcat(buf,p);
														strcpy(tok,buf);
														if((p=look_label(*num_panel,k,*num_point,*num_net)) != NULL)
															 {
																*var_type = LABEL_VAR;
																return p;
															 }
														else
															 {
																*var_type = POINT_VAR;
																return tok;
															 }
													 }
										 }
					}
			 }
// return(islabel(token,num_point,var_type,point_type,&ptr_panel->GlPanel));
			 return(islabel(token,num_point,var_type,point_type,num_panel));
}



char *look_label(int panel, int point_type, int num, int network)
{
 char *p=NULL;
// if(local_panel)
 if( local_request(panel, network) )
	 if(panel == Station_NUM)
			{
				switch (point_type) {
						case OUT:
									p = ptr_panel->outputs[num-1].label;
									break;
						case IN:
									p = ptr_panel->inputs[num-1].label;
									break;
						case VAR:
									p = ptr_panel->vars[num-1].label;
									break;
						case CON:
									return 0;
//									p = ptr_panel->controllers[num].label;
									break;
						case WR:
									p = ptr_panel->weekly_routines[num-1].label;
									break;
						case AR:
									p = ptr_panel->annual_routines[num-1].label;
									break;
						case PRG:
									p = ptr_panel->programs[num-1].label;
									break;
						case AMON:
									p = ptr_panel->analog_mon[num-1].label;
									break;
						case AY:
									p = ptr_panel->arrays[num-1].label;
									break;
						default:
									break;
						}
						if(p)
						{
						 p=rtrim(p);
						 if (strlen(p) == 0)
							return 0;
						 else
							return p;
						}
						else
							return 0;

			}
	p=0;
	if(point_type!=CON && point_type!=TBL)
	{
	 if(Des)
		p = Des->look_label(panel,point_type,num);
	}
	return p;
}

int find_var_def(char *var_name)
{
 int i,j,num_net,num_panel,num_point,k;
 byte point_type,var_type;
 var_type = 0;
 k = 0;
 ispoint(var_name,&num_point,&var_type, &point_type,&num_panel,&num_net,pedit->network,pedit->panel, &k);
 for (i=0; i<index_vars_table; i++)
		if(!strcmp(vars_table[i].name , var_name))
		{
			cur_index = i;
/*
			for(j=0;j<MAX_ATTRIB;j++)
				if (vars_table[i].scope[j].line == lline)
				{
					 cur_scope = j;
					 return 1;
				}
*/
		}
return 0;
}

/*
void cod_putlong(int Byte, long l, int type)
{
  int L, H;
  if( Panel_Info1.panel_type != T3000 )
  {
	 L = (int)( l&0x0000FFFF ) ;
	 H = (int)( l>>16 );
	 asm mov  ax,L
	 asm xchg ah,al
	 asm mov  L,ax
	 memcpy(&cod_line[Byte],&L,2);
	 asm mov  ax,H
	 asm xchg ah,al
	 asm mov  H,ax
	 memcpy(&cod_line[Byte+2],&H,2);
  }
  else
	 memcpy(&cod_line[Byte],&l,4);
}

void cod_putint(char *ptr, int j, int type)
{
	if( type != T3000 )
  {
	 asm push ax
	 asm mov  ax,j
	 asm xchg ah,al
	 asm mov  j,ax
	 asm pop  ax
  }
  memcpy(ptr, &j, 2);
}

void cod_putint(int Byte, int j, int type)
{
  if( type != T3000 )
  {
	 asm push ax
	 asm mov  ax,j
	 asm xchg ah,al
	 asm mov  j,ax
	 asm pop  ax
  }
  memcpy(&cod_line[Byte], &j, 2);
}
*/

int pcodvar(int cod,int v,char *var,float fvar,char *op,int Byte)
{
 long lvar;
 int i,ind;
// unsigned cod_var;
 Point_Net point;
		 ind = Byte;
		 if (v>0)
		 {
				find_var_def(var);
				if (vars_table[cur_index].type == LOCAL_VAR)
				{
					 if (DORU_SYSTEM)
					 {
//						 cod_line[Byte++]=0x81+vars_table[cur_index].name[0]-'A'+1;
//						 cod_line[Byte++]=LOCAL_VARIABLE;
						 cod_line[Byte++]=vars_table[cur_index].var_type;
						 int t=0,j,k=0;
						 i=0;
/*
						 switch(vars_table[cur_index].var_type){
									case FLOAT_TYPE:
									case LONG_TYPE:
										t = 4;
										break;
									case INTEGER_TYPE:
										t = 2;
										break;
									case BYTE_TYPE:
										t = 1;
										break;
						 }
*/
						 for(j=0;j<ind_local_table; )
						 {
							switch(local_table[j]){
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
									switch(local_table[j]){
									case FLOAT_TYPE_ARRAY:
									case LONG_TYPE_ARRAY:
										k = 4;
										break;
									case INTEGER_TYPE_ARRAY:
										k = 2;
										break;
									case BYTE_TYPE_ARRAY:
									case STRING_TYPE:
//									case STRING_TYPE_ARRAY:
										k = 1;
										break;
								 }
								 if( (*((int *)&local_table[j+1])) )
									 k = 4+(*((int *)&local_table[j+1])) * (*((int *)&local_table[j+3])) * k;
								 else
									 k = 4 + (*((int *)&local_table[j+3])) * k;
								}
								break;
							}
							t = j+1;
							j += 1 + k;
							if( !strcmp(&local_table[j], vars_table[cur_index].name) )
							{
								if( vars_table[cur_index].c)
								{
//								 t += 4 + ( ( ( (*((int *)&op[i]))-1 ) * (*((int *)&op[i+2])) ) + ((*((int *)&op[i+2]))-1) );
								 t += 4;
								}
								memcpy(&cod_line[Byte], &t, 2);
								Byte += 2;
								break;
							}
							j += 1+strlen(&local_table[j]);
						 }
						 if (j == ind_local_table)
						 {
							exit(1);
						 }
/*
						 for(j=0;j<ind_local_table; j++)
								 if(local_table[j]==cod_line[Byte-1])
								 {
									t = 1;
									break;
								 }
						 if (j == ind_local_table)
							 local_table[ind_local_table++]=cod_line[Byte-1];
//						 cod_putint(Byte, j, pedit->ptrprg->type);
						 memcpy(&cod_line[Byte], &j, 2);
						 Byte += 2;
*/
					 }
/*
					 else
					 {
					  if (cod==NAME)
						 cod_line[Byte++]=98+vars_table[cur_index].name[0]; // '\0x62'+var  -> '\xAn'
					  else
						 cod_line[Byte++]='\x81'+vars_table[cur_index].name[0]-'A'+1;
//					 position_table[vars_table[cur_index].position][vars_table[cur_index].col_position_table++] = (int)ftell(fp)+Byte;
					  position_table[vars_table[cur_index].position][vars_table[cur_index].col_position_table++] =  code-pedit->code	+Byte;
					  Byte += 2;
					 }
*/
				}
				else
					if ((vars_table[cur_index].type == POINT_VAR) || (vars_table[cur_index].type == LABEL_VAR))
					{
//						 if ((cod==NAME) && (!DORU_SYSTEM))
//							 cod_line[Byte++]='\xA2';
//						 else
//							 if(vars_table[cur_index].panel == ptr_panel->GlPanel)
					 if( vars_table[cur_index].panel == pedit->panel )
					 {
						cod_line[Byte++]=LOCAL_POINT_PRG;
						point.number     = vars_table[cur_index].num_point-1;
						point.point_type = vars_table[cur_index].point_type+1;
						memcpy(&cod_line[Byte],&point,sizeof(Point));
						Byte += sizeof(Point);
					 }
					 else
					 {
						cod_line[Byte++]=REMOTE_POINT_PRG;
						point.putpoint( vars_table[cur_index].num_point-1, vars_table[cur_index].point_type+1, vars_table[cur_index].panel-1, vars_table[cur_index].network);
						memcpy(&cod_line[Byte],&point,sizeof(Point_Net));
						Byte += sizeof(Point_Net);
					 }
					}
		 }
		 else
			if (v<0)
			 cod_line[Byte++]=var[0];
			else
			{
			 cod_line[Byte++]=0x9D;
			 lvar = (long)( fvar * 1000 + 0.1 );
//			 cod_putlong(Byte, lvar, pedit->ptrprg->type);
			 memcpy(&cod_line[Byte],&lvar,4);
			 Byte += 4;
			}
		i=0;
		if (op!=NULL)
			while(op[i] && i<MAX_OP)
			{
			  switch (op[i]){
				 case '+':	 cod_line[Byte++]=PLUS;break;
				 case '-':	 cod_line[Byte++]=MINUS;break;
				 case '*':	 cod_line[Byte++]=MUL;break;
				 case '/':	 cod_line[Byte++]=DIV;break;
				 case '%':	 cod_line[Byte++]=MOD;break;
				 case '^':	 cod_line[Byte++]=POW;break;
				 case LT:
				 case LE:
				 case GT:
				 case GE:
				 case NE:
				 case EQ:
				 case OR:
				 case XOR:
				 case AND:
				 case NOT:
				 case MINUSUNAR:
				 case ABS:
				 case INKEYD:
				 case OUTPUTD:
				 case INT:
				 case LN:
				 case LN_1:
				 case SQR:
				 case Status:
         case RUNTIME:
				 case CONPROP:
				 case CONRATE:
				 case CONRESET:
				 case Tbl:
				 case WR_ON:
				 case WR_OFF:
				 case SENSOR_ON:
				 case SENSOR_OFF:
				 case TIME_FORMAT:
				 case ASSIGNARRAY_1:
				 case ASSIGNARRAY_2:
							cod_line[Byte++]=op[i];break;
				 case ASSIGNARRAY:
						 memmove(&cod_line[Byte-2], &cod_line[Byte-3], 3);
						 cod_line[Byte-3]=op[i];
						 Byte++;
						 break;
				 case ASSIGNAR:
						 cod_line[Byte++]=0xFF;
						 break;
				 case TIME_ON:
				 case TIME_OFF:
							  {
								int j=0,t=0;
								char *p;
								while (j<ind_time_table)
								{
								 if(!memcmp(&time_table[j], &cod_line[ind], Byte-ind))
								 {
									t = 1;
									break;
								 }
								 if(( p = (char *)memchr(&time_table[j], 0xff, ind_time_table - j)) )
									 j += (p - &time_table[j])+1+5;
								 else
									break;
								}

								if (!t)
								{
									memcpy(&time_table[ind_time_table], &cod_line[ind], Byte-ind);
									ind_time_table += Byte-ind;
									time_table[ind_time_table++] = 0xff;
									ind_time_table++;
								}
								Byte = ind;
								cod_line[Byte++]=op[i++];
								if (!t)
								{
//									cod_putint(Byte, ind_time_table, pedit->ptrprg->type);
									memcpy(&cod_line[Byte], &ind_time_table, 2);
								}
								else
								 {
									 p = (char *)memchr(&time_table[j], 0xff, ind_time_table - j);
									 p++;
									 j = (p - &time_table[0])+1;
//									 cod_putint(Byte, j, pedit->ptrprg->type);
									 memcpy(&cod_line[Byte], &j, 2);
								 }

								Byte += 2;
								if (!t)
									ind_time_table += 4;
/*
								cod_line[Byte++]=op[i++];
								cod_line[Byte++]=op[i++];
								cod_line[Byte++]=op[i++];
								cod_line[Byte++]=op[i];
*/
								}
								break;
				 case INTERVAL:
								cod_line[Byte++]=op[i++];
								lvar = LONGTIMETEST;
//								cod_putlong(Byte, lvar, pedit->ptrprg->type);
								memcpy(&cod_line[Byte], &lvar, 4);
								Byte += 4;
								i += 3;
								break;
				 case AVG:
				 case MAX:
				 case MIN:
								cod_line[Byte++]=op[i++];
								cod_line[Byte++]=op[i];
								break;
			  }
			  i++;
			}
			return Byte;
}

int checklocalvar(char *tok)
{
 int i;
 for(i=0;i<index_vars_table;i++)
		 if (!strcmp(vars_table[i].name,tok))
				break;
 if(i>=index_vars_table) return 0;
 if(vars_table[i].type!=LOCAL_VAR) return 0;
// if( (l>=1 && l<=vars_table[i].l) && (c>=1 && c<=vars_table[i].c) )
// {
//	t=vars_table[i].var_type;
 return i+1;
// }
// return 0;
}

int isarray(char *tok)
{
  float value;
  int i;
  i=checklocalvar(tok);
  if( !i ) return 0;
  get_token();
  if (*token=='(')
  {
	  parse_exp(&res);
	  if(!res)
		 return 0;
	  get_token();
	  if (*token!=')')
	  {
		if( !vars_table[i-1].l ) return 0;
		if (*token!=',')
		 return 0;
		parse_exp(&res);
		if(!res)
		 return 0;
		get_token();
		if (*token!=')')
		 return 0;
	   return 1;
	  }
	  if( vars_table[i-1].l && vars_table[i-1].c ) return 0;
	  return 1;
  }
  else
  {
	return 2;
  }
}

int isarray(int &l, int &c)
{
  float value;
  l=0; c=0;
  get_token();
  if (*token=='(')
  {
	  get_token();
	  if ( token_type!=NUMBER )
		 return 0;
	  putback();
	  eval_exp(&value);
	  c=(int)value;
	  if ( c<= 0 )
		 return 0;
	  l=0;
	  get_token();
	  if (*token!=')')
	  {
		if (*token!=',')
		 return 0;
		get_token();
		if ( token_type!=NUMBER )
		 return 0;
		putback();
		eval_exp(&value);
		l=c;
		c=(int)value;
		if ( c<= 0 )
		 return 0;
		get_token();
		if (*token!=')')
		 return 0;
		return 1;
	  }
  }
  else
  {
	return 2;
  }
}

int checkonlyarray(char *tok)
{
 int i;
 for(i=0;i<index_vars_table;i++)
		 if (!strcmp(vars_table[i].name,tok))
				break;
 if(i>=index_vars_table) return 0;
 if(vars_table[i].type!=LOCAL_VAR) return 0;
 if( !vars_table[i].l && !vars_table[i].c ) return 0;
 return i+1;
}

int varoffsetlast(int cur)
{
  int j,k;
  for(j=0;j<ind_local_table; )
  {
	switch(local_table[j]){
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
				switch(local_table[j]){
					case FLOAT_TYPE_ARRAY:
					case LONG_TYPE_ARRAY:
						k = 4;
						break;
					case INTEGER_TYPE_ARRAY:
						k = 2;
						break;
					case BYTE_TYPE_ARRAY:
					case STRING_TYPE:
//					case STRING_TYPE_ARRAY:
						k = 1;
						break;
				 }
				 if( (*((int *)&local_table[j+1])) )
					 k = 4+(*((int *)&local_table[j+1])) * (*((int *)&local_table[j+3])) * k;
				 else
					 k = 4 + (*((int *)&local_table[j+3])) * k;
			}
			break;
	}
//	t = j+1;
	j += 1 + k;
	if( !strcmp(&local_table[j], vars_table[cur].name) )
	{
		return j;;
	}
	j += 1+strlen(&local_table[j]);
  }
  return 0;
}

int createlocaltable(int cur)
{
	 int t=0,j,k;
	 for(j=0;j<ind_local_table; )
	 {
		switch(local_table[j]){
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
					switch(local_table[j]){
						case FLOAT_TYPE_ARRAY:
						case LONG_TYPE_ARRAY:
								k = 4;
								break;
						case INTEGER_TYPE_ARRAY:
								k = 2;
								break;
						case BYTE_TYPE_ARRAY:
						case STRING_TYPE:
//						case STRING_TYPE_ARRAY:
								k = 1;
								break;
					 }
					 if( *((int *)&local_table[j+1]) )
						 k = 4+(*((int *)&local_table[j+1])) * (*((int *)&local_table[j+3])) * k;
					 else
						 k = 4+(*((int *)&local_table[j+3])) * k;
					}
					break;
		}
		j += 1 + k;
		if( !strcmp(&local_table[j], vars_table[cur].name) ) break;
		j += 1+strlen(&local_table[j]);
	}
	if (j == ind_local_table)
	{
//		local_table[j]=vars_table[cur].var_type;
//		j++;
		switch(vars_table[cur].var_type){
			case FLOAT_TYPE:
			case LONG_TYPE:
			case FLOAT_TYPE_ARRAY:
			case LONG_TYPE_ARRAY:
					k = 4;
					break;
			case INTEGER_TYPE:
			case INTEGER_TYPE_ARRAY:
					k = 2;
					break;
			case BYTE_TYPE:
			case STRING_TYPE:
			case BYTE_TYPE_ARRAY:
//			case STRING_TYPE_ARRAY:
					k = 1;
					break;
		}
		local_table[j++]=vars_table[cur].var_type;
		if( vars_table[cur].c)
		{
//		 local_table[j++]=vars_table[cur].var_type+FLOAT_TYPE_ARRAY-FLOAT_TYPE;
		 memcpy(&local_table[j],&vars_table[cur].l,2);
		 j += 2;
		 memcpy(&local_table[j],&vars_table[cur].c,2);
		 j += 2;
		 if( vars_table[cur].l )
			 k *= (vars_table[cur].l*vars_table[cur].c);
		 else
			 k *= vars_table[cur].c;

		}
//		else
//		{
//		 local_table[j++]=vars_table[cur].var_type;
//		}
		memset( &local_table[j], 0, k);
		j += k;
		strcpy(&local_table[j], vars_table[cur].name);
		ind_local_table = j + 1 + strlen(vars_table[cur].name);
	}
}

int define_var(char *tok, int t,int l,int c, int lstr)
{
 char *label,test;
 byte point_type,var_type;
 int i,k,num_net,num_point,num_panel;
 var_type = num_point = point_type = 0;
 k=0;
 label=ispoint(tok,&num_point,&var_type,&point_type,&num_panel,&num_net,pedit->network,pedit->panel,&k);
 if(!label)
 {             // local var
//  if ((strlen(token) == 1 ) && (token[0]>='A' && token[0]<='Z'))
//  {
	 var_type = LOCAL_VAR;
	 label = tok;
	 while( *label )
	 {
		if (strchr( " :!;,+-/<>'*^=()[]" , *label) )
		 {sntx_err(NOT_VAR); return 0;}
		*label++;
	 }
//  }
 }
/*
 if (var_type==POINT_VAR )
 {
	 if( (test=checkpointpresence(num_point,point_type,num_panel,num_net,pedit->panel,pedit->network))==0 )
		 ; // warning			DisplayMessage(20,7,60,11, NULL, " Panel absent! ", NULL, Black, NULL, 2500);
	 if(test)
			test = checkmaxpoints(num_point,point_type,num_panel,num_net);
	 else
			test = 128;
//	 if (num_point>tbl_bank[point_type])
	 if (num_point>test)
		{sntx_err(GREATER_THEN_MAX); return 0;}
 }
*/

 if (!var_type)
				{sntx_err(NOT_VAR); return 0;}

 for(i=0;i<index_vars_table;i++)
		 if (!strcmp(vars_table[i].name,tok))
				break;
 if ( i>= MAX_Var )
	{sntx_err(TOOMANYVARS); return 0;}

 cur_index=i;

 if(i>=index_vars_table)
 {
  strcpy(vars_table[i].name,tok) ;
/*
 for(j=0;j<MAX_ATTRIB;j++)
 {
		if (vars_table[i].scope[j].line==0)
		{

			 vars_table[i].scope[j].line = lline ;
			 break;
		}
 }
*/
  vars_table[i].type = var_type ;

/*
 if (var_type==LOCAL_VAR)
 {
			if (i>=index_vars_table)
			{
//				 vars_table[i].position = index_position_table++;
//				 n_local++;
			}
 }
*/

	if (var_type==POINT_VAR || var_type==LABEL_VAR)
	{
					vars_table[i].point_type=point_type;
					vars_table[i].num_point = num_point;
					vars_table[i].panel = num_panel;

					if( local_request(pedit->panel,pedit->network) )
					{
						if ( !k )
							if( rs485port!=-1 && ipxport!=-1 )
							{
								num_net=(( class ConnectionData *)Routing_table[rs485port].ptr)->panel_info1.network;
							}
					}
/*
					if( (test=checkpointpresence(num_point,point_type,num_panel,num_net,pedit->panel,pedit->network))==0 )
							sntx_err(WARN_PANEL_MISSING,FALSE);
					if(test)
						 test = checkmaxpoints(num_point,point_type,num_panel,num_net);
					else
						test = 128;
					if (num_point>test)
							sntx_err(WARN_POINT_MISSING,FALSE);
*/
					if ( !k ) num_net = 0xFFFF;
					vars_table[i].network = num_net;

/*
					if( num_net==pedit->network )
						vars_table[i].network = 0xFFFF;
					else
						vars_table[i].network = num_net;
*/
					if (var_type==LABEL_VAR)
					{
						strcpy(vars_table[i].label,label);
					}
	}
	if(var_type==LOCAL_VAR)
	{
	if( c && t!=STRING_TYPE)
	{
		vars_table[i].var_type = t+FLOAT_TYPE_ARRAY-FLOAT_TYPE;
	}
	else
	{
	 if( tok[strlen(tok)-1]=='%' ) t = INTEGER_TYPE;
	 if( tok[strlen(tok)-1]=='$' ) {t = STRING_TYPE; l=0; c=lstr;}
	 vars_table[i].var_type = t;
	}
	vars_table[i].l = l;
	vars_table[i].c = c;

	createlocaltable(i);
	}
//n_global++;
	if (i>=index_vars_table) index_vars_table++;
 }
return 1;
}

int parse_then_else()
{
char temp[32] ;
float value;
then_else = 1;
eoi=',';
t++;
get_token();
if (token_type==NUMBER)
	 {
		putback() ;
		eval_exp(&value) ;
		if(renumvar)
		{
		 for(int i=0;i<ind_renum;i++)
			 if(renum[i]==(unsigned)value) break;
		 itoa((i+1)*10,temp,10);
		 putback();
		 memmove(prog+strlen(temp), prog+strlen(token), strlen(prog));
		 memcpy(prog, temp, strlen(temp));
		 prog += strlen(temp);
		}
		if(index_go_to+1 < MAX_GOTO)
		{
		 line_table[lline-1].go_to=1;
		 go_to[index_go_to].line=lline;
		 go_to[index_go_to++].go_to=value;
		}
		get_token();
		t--;
		then_else=0;
		eoi=NL;
		return 0;
	 }
putback() ;
prescan1();
eoi=NL;
t--;
if (then_else==1)
	{
	 then_else = 0;
	 error = TRUE;
	 return 1;
	}
then_else = 0;
return 0;
}

int prescan1 (void)
{
	char *p;
	char temp[32] ;
	float value;
	int i,l,c,t; /* when this is zero, we are outside all functions */

	p = prog ;


	get_token() ;
	while( tok!=FINISHED)  {
		if (token_type == FINISHED)
				break;
		if (token_type == NL)
			 if ((then_else!=0) && eol==NL )
				 return 1;
			 else
			 {
			  while(token_type==NL) get_token();
			 }
		if (tok==FINISHED) return 1;

		if (!then_else)
		{
		if( token_type != NUMBER )
				{
				get_nl();
				sntx_err(NOT_LINE);
				get_token() ;
				continue;
				}
//		putback() ; /* restore input stream for further processing
//									 by eval_exp() */
//		eval_exp(&value) ; /* process the expression */
		line_value=atoi(token);       //(int)value;
		line_table[lline].line=(int)line_value;
		lline++;
		if( lline >= MAX_LINE )
			{sntx_err(TOOMANYLINES); break;}
		long_line_value=atol(token);       //(int)value;
		if(long_line_value > 64000)
			{sntx_err(TOOBIG);}
		showgauge(gaugep, coef, lline);
		if(renumvar)
		{
		 itoa(lline*10,temp,10);
		 putback();
		 memmove(prog+strlen(temp), prog+strlen(token), strlen(prog));
		 memcpy(prog, temp, strlen(temp));
		 prog += strlen(temp);
		}
		get_token() ;
		}
		else
		 then_else++;

		switch ( token_type ) {
		case IDENTIFIER:
						if( *prog == '(' )
						{
						  if( !checklocalvar(token) )
							{sntx_err(SYNTAX);get_nl();break;}
						}
						else
						 if (!define_var(token))
							{get_nl();break;}
						get_token();
						if (*token=='[')
						{
						 type_eval=0;
						 parse_exp(&res);
						 get_token();
						 if (*token!=']')
							{sntx_err(SYNTAX);get_nl();break;}
						 get_token();
						}
						else
						{
						 if (*token=='(')
						 {
						  type_eval=0;
						  parse_exp(&res);
						  if(!res)
								{sntx_err(SYNTAX);get_nl();break;}
						  get_token();
						  if ( *token!=')')
							 if (*token!=',')
								{sntx_err(SYNTAX);get_nl();break;}
						  if (*token==',')
						  {
							type_eval=0;
							parse_exp(&res);
							if(!res)
								{sntx_err(SYNTAX);get_nl();break;}
							get_token();
							if (*token!=')')
								{sntx_err(SYNTAX);get_nl();break;}
						  }
						  get_token();
						 }
						}
						if (*token!=EQ)
							{sntx_err(SYNTAX);get_nl();break;}
						type_eval=0;
						parse_exp(&res);
//						if (!res)
//							{sntx_err(SYNTAX);break;}
						break;

		case KEYWORD:
			 switch(tok) {
					case DIM:
						get_token();
						t = FLOAT_TYPE;
					case INTEGER_TYPE:
					case STRING_TYPE:
					case BYTE_TYPE:
					case FLOAT_TYPE:
					case LONG_TYPE:
						l=0;c=0;
						if ( ( token_type==KEYWORD && (tok==INTEGER_TYPE || tok==STRING_TYPE ||
							  tok==BYTE_TYPE || tok==FLOAT_TYPE || tok==LONG_TYPE) )
							  || token_type==IDENTIFIER)
						{
						 if ( token_type!=IDENTIFIER )
						 {
							 t=tok;
							 get_token();
							 if ( token_type!=IDENTIFIER )
								{sntx_err(SYNTAX);get_nl();break;};
						 }
						 else
						 {
							if( token[strlen(token)-1]=='%' ) t = INTEGER_TYPE;
							if( token[strlen(token)-1]=='$' ) t = STRING_TYPE;
						 }
						 strcpy(temp, token);
						 if(t!=STRING_TYPE)
						 {
						  if(!isarray(l,c))
								{sntx_err(SYNTAX);get_nl();break;};
						 }
						 else
						 {
						  i = isarray(l,c);
						  if( i==1 || i==0 )
								{sntx_err(SYNTAX);get_nl();break;}
						  else
						  { l=0; c=128; }
						 }

						 if (!define_var(temp,t,l,c))    // define array
							{get_nl();break;}
						}
						else
							 {sntx_err(SYNTAX);get_nl();break;};
						break;
					case PHONE:
					case REM:
						while( (*prog!=13) && *prog)
							++prog ;
						break;
					case PRINT:
						get_token();
						if (*token==';')
							 {sntx_err(SYNTAX);get_nl();break;};

						while (token_type!=NL && tok!=FINISHED && token_type!=KEYWORD )
						{
						if (token_type!=STRING)
							 if (strcmp(strupr(token),"DATE"))
								 if (strcmp(strupr(token),"PTIME"))
									 if (strcmp(strupr(token),"USER_A"))
										 if (strcmp(strupr(token),"USER_B"))
											 if (strcmp(strupr(token),"BEEP"))
													if(!define_var(token))
														 {get_nl();get_token();break;};

						get_token();
						if (*token!=';' && token_type!=NL && then_else==0 )
							 {sntx_err(SYNTAX);get_nl();get_token();break;};
						if (*token!=';' && token_type!=NL && token_type!=',' && token_type!=KEYWORD && then_else!=0 )
							 {sntx_err(SYNTAX);get_nl();get_token();break;};
						if (*token==';')
							get_token();
						}

						if ( token_type!=KEYWORD )
							if (eol==NL ) {--prog;--prog;}
							else --prog;
						else
							putback();
						break;
					case ENDPRG:
//						get_token();
//						if (token_type!=NL && tok!=FINISHED)
//									{sntx_err(SYNTAX);get_nl();break;};
						break;
					case HANGUP:
					case CLEARX:
					case RETURN:
						get_token();
						if (token_type!=NL && tok!=FINISHED)
									{sntx_err(SYNTAX);get_nl();break;};
						break;
					case SET_PRINTER:
						get_token();
						if (*token != 'A' && *token != 'B' && *token != '0'
								&& *token != 'a' && *token != 'b' )
											{sntx_err(SYNTAX);get_nl();break;};
						break;
					case RUN_MACRO:
						get_token();
						if ((token_type == NUMBER) && tok!=FINISHED)
									 {
									 putback();
									 eval_exp(&value);
									 if ((int)value<1 || (int)value>16)
											{sntx_err(SYNTAX);get_nl();break;};
									 }
						else
											{sntx_err(SYNTAX);get_nl();break;};
						break;
					case STARTPRG:
					case STOP:
					case OPEN:
					case CLOSE:
					case DISABLEX:
					case ENABLEX:
						get_token();
						if ((token_type == IDENTIFIER) && tok!=FINISHED)
									{
									 if(!define_var(token))
											{get_nl();break;}
									}
						else
									{sntx_err(SYNTAX);get_nl();break;};
						break;
					case ON:
						type_eval=0;
						parse_exp(&res);
						if (!res)
								break;
						get_token();
						if((token_type==NL) || tok==FINISHED)	{sntx_err(SYNTAX);break;}
						if((tok!=GOTO) && tok!=GOSUB)	{sntx_err(SYNTAX);get_nl();break;}
						get_token();
						if((token_type==NL) || tok==FINISHED)	{sntx_err(SYNTAX);break;}
						while ((token_type != NL) && tok!=FINISHED) {
							if(token_type!=NUMBER) {sntx_err(SYNTAX);get_nl();break;} ;
							if(renumvar)
									{
									 for(int i=0;i<ind_renum;i++)
										 if(renum[i]==(unsigned)atoi(token)) break;
									 itoa((i+1)*10,temp,10);
									 putback();
									 memmove(prog+strlen(temp), prog+strlen(token), strlen(prog));
									 memcpy(prog, temp, strlen(temp));
									 prog += strlen(temp);
									}
							get_token();
							if (token_type == NL || tok==FINISHED) break;
							if(*token!=',') {sntx_err(SYNTAX);get_nl();break;};
							get_token();
						}
						break;
					case ON_ALARM:
					case ON_ERROR:
					case GOSUB:
					case GOTO:
						get_token();
						if(token_type==NL) {sntx_err(NOT_LINE);break;}
						if(token_type!=NUMBER) {sntx_err(NOT_LINE),get_nl();break;}
						else {
									putback() ;
									eval_exp(&value) ;
									if(renumvar)
									{
									 for(i=0;i<ind_renum;i++)
										 if(renum[i]==(unsigned)value) break;
									 itoa((i+1)*10,temp,10);
									 putback();
									 memmove(prog+strlen(temp), prog+strlen(token), strlen(prog));
									 memcpy(prog, temp, strlen(temp));
									 prog += strlen(temp);
									}
									if(index_go_to+1 < MAX_GOTO)
									{
									 line_table[lline-1].go_to=1;
									 go_to[index_go_to].line=lline;
									 go_to[index_go_to++].go_to=value;
									}
									else
									  {sntx_err(TOOMANYGOTO),get_nl();break;}
								 }
						break;
					case Alarm:
						type_eval=0;
						parse_exp(&res);
						if (!res)
								break;
						get_token();
						if (*token!=',')
							{sntx_err(SYNTAX);get_nl();break;}
						parse_exp(&res);
						if (!res)
								break;
						get_token();
						if (*token!=',')
							{sntx_err(SYNTAX);get_nl();break;}
						get_nl();
						break;
					case PRINT_AT:
					case ALARM_AT:
						get_token();
						if(((token_type!=NUMBER) && (token_type!=IDENTIFIER)) || tok==FINISHED)
											 {sntx_err(SYNTAX);get_nl(); break;}
						if((token_type==IDENTIFIER) && (strcmp(strupr(token),"ALL")))
											 {sntx_err(SYNTAX);get_nl();break;} ;
						if(token_type==NUMBER)
						{
							get_token();
							if (token_type!=NL)
								 if(token_type!=NUMBER){sntx_err(SYNTAX);get_nl();break;}
								 else
								 {
									 get_token();
									 if (token_type!=NL)
									 {
										 if(token_type!=NUMBER){sntx_err(SYNTAX);get_nl();break;};
									 }
								 }
						}
						break;
					case CALLB:
						get_token();
						if ((token_type == IDENTIFIER) && tok!=FINISHED)
								 {
								 if(!define_var(token))
										{get_nl();break;}
								 if (vars_table[cur_index].point_type!=PRG)
											 {sntx_err(SYNTAX);get_nl();break;} ;
								 }
						else
											 {sntx_err(SYNTAX);get_nl();break;} ;
						get_token();
						if((token_type==NL) || (tok==FINISHED)) break;
						if( *token != EQ )  {sntx_err(SYNTAX);get_nl();break;} ;
							res=0;
							while ((token_type != NL) && tok!=FINISHED)
										 {
											parse_exp(&res);
											if (!res)
													break;
											get_token();
											if((token_type==NL) || (tok==FINISHED)) continue;
											if(*token!=',') {sntx_err(SYNTAX);get_nl();break;} ;
										 }
						break;
					case DALARM:
						type_eval=0;
						parse_exp(&res);
						if (!res)
							break;
						get_token();
						if((token_type==NL) || (tok==FINISHED)) {sntx_err(SYNTAX);break;}
						if( *token != ',' )  {sntx_err(SYNTAX);get_nl();break;} ;
						get_token();
						if((token_type==NL) || (tok==FINISHED)) {sntx_err(SYNTAX);break;}
						if( token_type!=NUMBER ) {sntx_err(SYNTAX);get_nl();break;} ;
						get_token();
						if((token_type==NL) || (tok==FINISHED)) {sntx_err(SYNTAX);break;}
						if( *token != ',' )	 {sntx_err(SYNTAX);get_nl();break;} ;
						get_nl();
						break;
					case DECLARE:
						if (lline != 1) {
//									 fprintf(pmes,"error line : %d  DECLARE must be first line\n",(int)line_value);
										memcpy(pmes,"error line : ",13);
										pmes += 13;
										itoa((int)line_value,pmes,10);
										pmes += strlen(pmes);
										memcpy(pmes," DECLARE must be first line",27);
										pmes += 27;
										*pmes++ = 0x0d;
									 break;} ;

						get_token();
						while ((token_type != NL) && tok!=FINISHED)
									 {
											if(token_type!=IDENTIFIER)
													 {sntx_err(SYNTAX);get_nl();break;} ;
											if(!define_var(token))
														{get_nl();break;}
											get_token();
									 }
						break;
					case REMOTE_SET:
					case REMOTE_GET:
						get_token();
						if (tok==FINISHED || token_type==NL)  {sntx_err(SYNTAX);break;}
						if ((token_type != IDENTIFIER)) {sntx_err(SYNTAX);get_nl();break;} ;
						if(!define_var(token))
							{get_nl();break;}
						get_token();
						if (*token!=EQ)	{sntx_err(SYNTAX);get_nl();break;}
						get_token();
						if ((token_type != IDENTIFIER) || tok==FINISHED || token_type==NL)
									 {sntx_err(SYNTAX);get_nl();break;} ;
						if(!define_var(token))
							{get_nl();break;}
						break;

					case FOR:
						get_token();
						if ((token_type != IDENTIFIER) || tok==FINISHED || token_type==NL)
									 {sntx_err(SYNTAX);get_nl();break;} ;
						if(!define_var(token))
									 {get_nl();break;} ;
						if (vars_table[cur_index].type!=LOCAL_VAR)
						{
												memcpy(pmes,"not a local variable in line ",31);
												pmes += 31;
												itoa((int)line_value,pmes,10);
												pmes += strlen(pmes);
												*pmes++ = 0x0d;
//											 fprintf(pmes,"not a local variable in line %d \n",line_value);
												get_nl();break;
						}
						get_token();
						if (*token!=EQ)
							{sntx_err(SYNTAX);get_nl();break;}
						type_eval=0;
						parse_exp(&res);
						if (!res)
							break;
						get_token();
						if (tok!=TO)
							{sntx_err(SYNTAX);get_nl();break;}
						type_eval=0;
						parse_exp(&res);
						if (!res)
							break;
						get_token();
						if (tok==STEP)
						 {
							type_eval=0;
							parse_exp(&res);
							if (!res)
								break;
							get_token();
						 }
						if (token_type!=NL)
										{sntx_err(SYNTAX);get_nl();break;}
						for_count++;
						if (prescan1()!=NEXT)
							 {
								memcpy(pmes,"missing NEXT ",13);
								pmes += 13;
								*pmes++ = 0x0d;
//							 fprintf(pmes," missing NEXT  \n");
							 break;
							 }
						if( error) 	break;
						get_token();
						if ((token_type != IDENTIFIER) || tok==FINISHED || token_type == NL)
								{sntx_err(SYNTAX);get_nl();break;}
						if(!define_var(token))
									 {get_nl();break;}
						break;
					case NEXT:
						if (for_count--<0)
								 {
									error = TRUE;
									memcpy(pmes,"missing FOR ",12);
									pmes += 12;
									*pmes++ = 0x0d;
//									fprintf(pmes," missing FOR \n");
								 }
						return NEXT;
					case ELSE:
						return 1;
					case IF:
					case IFP:
					case IFM:
/*
						if (*prog=='+')
						{
						prog++;
						}
						if (*prog=='-')
						{
						prog++;
						}
*/
						type_eval=0;
						parse_exp(&res);
						if (!res)
							break;
						get_token();
						if (tok!=THEN)
							{sntx_err(SYNTAX);get_nl();break;}
						if (parse_then_else())
								{sntx_err(SYNTAX);get_nl();break;}
						if (tok==ELSE)
							if (parse_then_else())
								{sntx_err(SYNTAX);get_nl();break;}
						break;
					case WAIT:
						get_token();
						if(token_type==NL || tok==FINISHED) {sntx_err(SYNTAX); break;}
						if(token_type == TTIME)
							 {
								get_token();
								if(token_type!=NL && tok!=FINISHED) {sntx_err(SYNTAX);get_nl(); break;}
								break;
							 }
						putback();
						type_eval=0;
						parse_exp(&res);
						break;
				 }
             break;
			 default:
					{sntx_err(SYNTAX);get_nl();break;}
		}
//	if(token_type!=NL)
		get_token();
	}
}

void parse2_then_else()
{
float value;
then_else=1;
eoi=',';
t++;
get_token();
if (token_type==NUMBER)
	 {
		putback() ;
		eval_exp(&value) ;
		line_table[lline-1].go_to=1;
		go_to[index_go_to].line=lline;
		go_to[index_go_to++].go_to=value;
		write_cod(GOTOIF,1,0,"",value,0,"",0,0,"",0);
		get_token();
		t--;
		then_else=0;
		eoi=NL;
		return;
	 }
putback() ;
prescan2();
t--;
then_else=0;
eoi=NL;
}

void prescan2(void)
{
	int v1,v2,v3 ;
	float value,fvar1,fvar2,fvar3;
	int i,command ;
	char *p;
	char temp[31],temp1[11];
	char block = 0 ;
	char var1[12],var2[12],var3[12];
	int nrlin[10];
	p = prog ;

	get_token() ;
	while( tok!=FINISHED)  {
//	for(i=0;i<100;i++)
//				cod_line[i]=0;
		if (token_type == FINISHED)
				break;
		if (token_type == NL)
			 if ((then_else!=0) && eol==NL )
				 return;
			 else
			 {
			  while(token_type==NL) get_token();
			 }
		if (tok==FINISHED) return;

		if (!then_else)
		{
		if( token_type != NUMBER )
				{
				get_nl();
				memcpy(pmes,"error: missing line number",27);
				pmes += 27;
				*pmes++ = 0x0d;
//				fprintf(pmes,"error: missing line number\n");
				get_token() ;
				continue;
				}
//		putback() ; /* restore input stream for further processing
//									 by eval_exp() */
//		eval_exp(&value) ; /* process the expression */
//		line_value=(int)value;
		line_value=atoi(token);       //(int)value;
		line_table[lline].line=(int)line_value;
//		line_table[line].pos=(int)ftell(fp);
		line_table[lline].pos=code-pedit->code;
		lline++;
		showgauge(gaugep, coef, lline);

		get_token() ;
		}
		else
		 then_else++;

		switch (token_type) {

		case IDENTIFIER:
						v2=v3=0;
						strcpy(temp,token);
 /*
						putback();
						index_buf=0;
						index_op=0;
						n_var=0;
						type_eval=1;
						for(i=0;i<MAX_VAR_LINE;i++)
						{
							 buf[i].v=0;
							 buf[i].var[0]=0;
						}
						parse_exp((float *)buf);
						for(i=0;i<5;i++)
						{
							 buf2[i] = buf[i];
						}
						n_var2 = n_var;
*/

						get_token() ;    //  override '='
						if( *token=='[' )
							command = ASSIGNAR;
						else
						{
						 if( *token=='(' )
							command = ASSIGNARRAY_2;
						 else
							command = ASSIGN;
						}
						if (*token=='[' || *token=='(')
						{
						  if (*token=='(')
						  {
							i=checklocalvar(temp);
							if( !vars_table[i-1].l )    // one index
							{
								command = ASSIGNARRAY_1;
/*
								for(i=0;i<7;i++)
								{
								  memset(&buf2[i],0,sizeof(buf2[i]));
								}
								buf2[0].fvar = 1;
								strcpy(buf2[0].var,"");
								index_buf++;
								v2 = 1;
*/
							}
						  }
							index_buf=0;
							index_op=0;
							n_var=0;
							type_eval=1;
							memset(buf_v, 0, MAX_VAR_LINE * sizeof(struct buf_str));
							parse_exp((float *)buf_v);
							for(i=v2;i<7;i++)
							{
							 buf2[i] = buf_v[i-v2];
							}
//							v2 = n_var;
//							v3=0;
//							v3 = n_var;
							v2 = n_var;

							get_token();  //']' or ',' or ')'
							if (*token==',')
							{
//							 v2 = v3;
//							 v3 = 0;
							 index_buf=0;
							 index_op=0;
							 n_var=0;
							 type_eval=1;
							 memset(buf_v, 0, MAX_VAR_LINE * sizeof(struct buf_str));
							 parse_exp((float *)buf_v);
							 for(i=v2;i<7;i++)
							 {
							  buf2[i] = buf_v[i-v2];
							 }
							 v3 = n_var;
							 get_token();  //')'
							}
							get_token();  //'='
						}

										index_buf=0;
										index_op=0;
										n_var=0;
										type_eval=1;
										memset(buf_v, 0, MAX_VAR_LINE * sizeof(struct buf_str));
										parse_exp((float *)buf_v);
/*					get_token() ;
					putback() ;
					eval_exp1(&value);
					assig_var(temp,value);
					write_cod(ATTRIB,0,0,"",0,0,"",0,0,"",0);
*/
//						write_cod(ASSIGN,n_var,1,temp,0,1,(char *)buf,0,n_var2,(char *)buf2,0);
						write_cod(command,n_var,1,temp,0,v2,(char *)buf_v,0,v3,(char *)buf2,0);
						break;
		case KEYWORD:
					switch (tok) {

						case DIM:
						case INTEGER_TYPE:
						case BYTE_TYPE:
						case STRING_TYPE:
						case LONG_TYPE:
						case FLOAT_TYPE:
						case REM:
						case PHONE:
										prog++;
										get_comment(pedit->comment);
										write_cod(tok,0,0,"",0,0,"",0,0,"",0);
										break;
						case PRINT:
									  n_var=0;
									  i=0;
									  get_token();
									  if (token_type==NL)
									  {
												buf_v[i++].v=NL;
												n_var++;
									  }
									  v1=0;
									  while (token_type!=NL && tok!=FINISHED && token_type!=KEYWORD)
									  {
										if (token_type==STRING)
										{
													buf_v[i].v=STRING;
													strcpy(&pedit->comment[v1],token);
													v1 += strlen(token)+1;
										}
										else
										{
										 if (!strcmp(strupr(token),"DATE"))
													buf_v[i].v=DATE;
										 else if (!strcmp(strupr(token),"PTIME"))
														buf_v[i].v=PTIME;
												 else	if (!strcmp(strupr(token),"USER_A"))
																buf_v[i].v=USER_A;
															else if (!strcmp(strupr(token),"USER_B"))
																		 buf_v[i].v=USER_B;
																	 else	if (!strcmp(strupr(token),"BEEP"))
																						buf_v[i].v=BEEP;
																				else if (token_type==IDENTIFIER)
																								 {
																								buf_v[i].v=IDENTIFIER;
																									strcpy(buf_v[i].var,token);
																								 }
										}
										n_var++;
										i++;
										get_token();
										if (*token==';')
										 {
											get_token();
											if (token_type==NL)
												break;
											if (token_type==KEYWORD)
												putback();
										 }

										if (token_type==NL)
												{
												buf_v[i++].v=NL;
												n_var++;
												if (eol==NL) {--prog;--prog;}
												else --prog;
												}
									}
										write_cod(PRINT,n_var,0,"",0,1,(char *)buf_v,0,0,(char *)"",0);
										break;
						case CLEARX:
						case ENDPRG:
						case RETURN:
						case HANGUP:
										write_cod(tok,0,0,"",0,0,"",0,0,"",0);
										break;
					case ELSE:
										return;
						case SET_PRINTER:
						case STARTPRG:
						case STOP:
						case OPEN:
						case CLOSE:
						case DISABLEX:
						case ENABLEX:
										id = tok;
										get_token() ;
										write_cod(id,1,1,token,0,0,"",0,0,"",0);
										break;
						case RUN_MACRO:
										eval_exp(&value);
										write_cod(RUN_MACRO,0,0,"",value,0,"",0,0,"",0);
										break;
						case ON:
									 index_buf=0;
									 index_op=0;
									 n_var=0;
									 type_eval=1;
									 memset(buf_v, 0, MAX_VAR_LINE * sizeof(struct buf_str));
									 i=0;
									 parse_exp((float *)buf_v);
									 get_token();
									 if (tok == GOTO) fvar1 = GOTO;
									 else fvar1=GOSUB;
									 i=0;
									 while ((token_type != NL) && tok!=FINISHED) {
											eval_exp(&value);
											nrlin[i++]=(int)value;
											get_token();
										}
										write_cod(ON,n_var,i,(char *)nrlin,fvar1,1,(char*)buf_v,0,0,"",0);

										break;
						case GOTO:
						case ON_ERROR:
						case ON_ALARM:
						case GOSUB:
										id = tok;
										eval_exp(&value) ;
										line_table[lline-1].go_to=1;
										go_to[index_go_to].line=lline;
										go_to[index_go_to++].go_to=value;
										write_cod(id,1,0,"",value,0,"",0,0,"",0);
										break;
						case Alarm:
										char c;
										index_buf=0;
										index_op=0;
										n_var=0;
										n_var1=0;
										type_eval=1;
										memset(buf_v, 0, MAX_VAR_LINE * sizeof(struct buf_str));

									if ((p=(char *)strchr(prog,'<'))!=NULL)
										c=LT;
									else
										if ((p=(char *)strchr(prog,'>'))!=NULL)
											c=GT;
									*p=',';


										parse_exp((float *)buf_v);
										n_var1=n_var;
										get_token();
										parse_exp((float *)buf_v);
										n_var2=n_var;
										get_token();
										parse_exp((float *)&buf_v[index_buf]);
										get_token();
//  treb rez probl spatiului
										prog++;
//
										get_comment(pedit->comment);
										write_cod(Alarm,n_var,c,"",0,1,(char*)buf_v,0,0,"",0);


/*

										get_token();
										v1=v2=v3=1;
										if(token_type==NUMBER)
												 {
													putback();
													eval_exp(&fvar1) ;
													v1=0;
													*var1=0;
												 }
										else
												 strcpy(var1,token);
										get_token();
										get_token();
										if(token_type==NUMBER)
												 {
													putback();
													eval_exp(&fvar2) ;
													v2=0;
													*var2=0;
												 }
										else
													strcpy(var2,token);
										get_token();
										get_token();
										if(token_type==NUMBER)
												 {
													putback();
													eval_exp(&fvar3) ;
													v3=0;
													*var3=0;
												 }
										else
													strcpy(var3,token);
										get_token();
										prog++;
										get_comment(comment);
										if (DORU_SYSTEM)
											write_cod_d(Alarm,3,v1,var1,fvar1,v2,var2,fvar2,v3,var3,fvar3);
										else
											write_cod(Alarm,3,v1,var1,fvar1,v2,var2,fvar2,v3,var3,fvar3);
*/
										break;

						case PRINT_AT:
						case ALARM_AT:
										id = tok;
										get_token();
										if(token_type==IDENTIFIER)
												write_cod(PRINT_ALARM_AT_ALL,0,0,"",0,0,"",0,0,"",0);
										n_var=0;
										if(token_type==NUMBER)
										{
//											putback();
//											eval_exp(&fvar1) ;
#ifndef NOMATH
											fvar1=atof(token);
#else
											fvar1=atofproc(token);
#endif
											v1=0;
											*var1=0;
											n_var++;
											get_token();
											if (token_type!=NL)
												{
//												 putback();
//												 eval_exp(&fvar2) ;
#ifndef NOMATH
												 fvar2=atof(token);
#else
												 fvar2=atofproc(token);
#endif
												 v2=0;
												 *var2=0;
												 n_var++;
												 get_token();
												 if (token_type!=NL)
														{
//														 putback();
//														 eval_exp(&fvar3) ;
#ifndef NOMATH
														 fvar3=atof(token);
#else
														 fvar3=atofproc(token);
#endif
														 v3=0;
														 *var3=0;
														 n_var++;
														}
												}
										write_cod(PRINT_ALARM_AT,n_var,v1,var1,fvar1,v2,var2,fvar2,v3,var3,fvar3);
									 }
									 break;
						 case CALLB:
									 get_token();
									 strcpy(var1,token);
									 index_buf=0;
									 index_op=0;
									 n_var=0;
									 type_eval=1;
									 memset(buf_v, 0, MAX_VAR_LINE * sizeof(struct buf_str));
									 i=0;
									 get_token();
									 while ((token_type != NL) && tok!=FINISHED)
										 {
											parse_exp((float *)&buf_v[index_buf]);
											argcall[i++]=n_var;
											get_token();
										 }
									 argcall[i]=0;
									 write_cod(CALLB,n_var,1,var1,0,i,(char*)buf_v,0,0,"",0);
									 break;
						 case DALARM:
									index_buf=0;
									index_op=0;
									n_var=0;
									type_eval=1;
									memset(buf_v, 0, MAX_VAR_LINE * sizeof(struct buf_str));
									parse_exp((float *)buf_v);
									get_token();
									eval_exp(&fvar1) ;
									get_token();
									prog++;
									get_comment(pedit->comment);
									write_cod(DALARM,n_var,0,"",fvar1,1,(char*)buf_v,0,0,"",0);
									break;
							case DECLARE:
									n_var=0;
									i=0;
									get_token();
									while ((token_type != NL) && tok!=FINISHED)
									 {
											buf_v[i].v=1;
											strcpy(buf_v[i].var,token);
											i++;
											n_var++;
											get_token();
									 }
									 write_cod(DECLARE,n_var,0,"",0,1,(char*)buf_v,0,0,"",0);
									 break;
							case REMOTE_SET:
							case REMOTE_GET:
									id = tok;
									get_token();
									v1=1;
									strcpy(var1,token);
									get_token();
									get_token();
									v2=1;
									strcpy(var2,token);
									write_cod(id,0,1,var1,0,1,var2,0,0,"",0);
									break;
							case FOR:
										for_count++;
										n_var=0;
										get_token();
										v1=1;
										strcpy(var1,token);
										index_buf=0;
										index_op=0;
										n_var=0;
										type_eval=1;
										memset(buf_v, 0, MAX_VAR_LINE * sizeof(struct buf_str));
										i=0;
										get_token();
										parse_exp((float *)buf_v);
										argcall[i++]=n_var;
										get_token();
										parse_exp((float *)&buf_v[index_buf]);
										argcall[i++]=n_var;
										get_token();
										if (tok == STEP)
											{
											 parse_exp((float *)&buf_v[index_buf]);
											 argcall[i++]=n_var;
											}
										else
											 {
												buf_v[index_buf].v=0;
												buf_v[index_buf++].fvar=1;
												n_var++;
												argcall[i++]=n_var;
											 }
									 argcall[i]=0;
										write_cod(FOR,n_var,1,var1,0,i,(char*)buf_v,0,0,"",0);
										break;
								case NEXT:
										get_token() ;
										write_cod(NEXT,0,0,"",0,0,"",0,0,"",0);
										for_count--;
										break;
					case IF:
					case IFP:
					case IFM:
						fvar1 = 0;
						if (tok==IFP)
						{
						fvar1 = 1;
						}
						if (tok==IFM)
						{
						fvar1 = 2;
						}

									index_buf=0;
									index_op=0;
									n_var=0;
									ind_cod_line=0;
									type_eval=1;
									memset(buf_v, 0, MAX_VAR_LINE * sizeof(struct buf_str));
									parse_exp((float *)buf_v);
									write_cod(IF,n_var,0,"",fvar1,1,(char*)buf_v,0,0,"",0);
									get_token();
									parse2_then_else();

						if (tok==ELSE)
						{
							cod_line[ind_cod_line++]=0x10;
							if(DORU_SYSTEM)
								cod_line[ind_cod_line++]=0xFF;
							next_else_else = ind_cod_line;
							ind_cod_line += 2;
							i=ncod+ind_cod_line+2;
//							cod_putint(next_then_else, i, pedit->ptrprg->type);
							memcpy(&cod_line[next_then_else],&i,2);
							parse2_then_else();
							i=ncod+ind_cod_line+2;
//							cod_putint(next_else_else, i, pedit->ptrprg->type);
							memcpy(&cod_line[next_else_else],&i,2);
						}
						else
						{
							i=ncod+ind_cod_line+2;
//							cod_putint(next_then_else, i, pedit->ptrprg->type);
							memcpy(&cod_line[next_then_else],&i,2);
							if (token_type==NL)
							  if (eol==NL) {--prog;--prog;}
							  else --prog;
						}

					if( ncod + ind_cod_line + 2 < PROGRAM_SIZE )
					{
					 ncod = ncod + ind_cod_line ;
					 memcpy(code,cod_line,ind_cod_line);
					 code += ind_cod_line;
					}
					else
					  ncod = PROGRAM_SIZE ;
					break;

					case WAIT:
									get_token();
									if(token_type == TTIME)
									 {
											write_cod(WAIT,0,1,"",ttime,0,"",0,0,"",0);
											break;
									 }
									putback();
									index_buf=0;
									index_op=0;
									n_var=0;
									type_eval=1;
									memset(buf_v, 0, MAX_VAR_LINE * sizeof(struct buf_str));
									parse_exp((float *)buf_v);
									write_cod(WAIT,n_var,0,"",0,1,(char*)buf_v,0,0,"",0);

						break;
				 }
			}
		get_token() ;
	}
} /* end of function interp_block */

void put_line_num( int line_value )
{
  cod_line[0]=0x01;
  memcpy(&cod_line[1],&line_value,2) ;
  ind_cod_line = 3;
}

void write_cod(int type,int n_var, int v1, char *var1, float fvar1,
																	 int v2, char *var2, float fvar2,
																	 int v3, char *var3, float fvar3)
{
char *p;
int *buf1;
struct buf_str *buf,*buf2;
int int_var1,n,i,j;
long lval;
switch (type) {
case ASSIGN:
case ASSIGNAR:
case ASSIGNARRAY_1:
case ASSIGNARRAY_2:
		 buf=(struct buf_str*)var2;
		 buf2=(struct buf_str*)var3;
		 if (!then_else)
		 {
			put_line_num( line_value );
		 }
		 if (DORU_SYSTEM)
		 {
			 cod_line[ind_cod_line++]=type;
/*
			 if(v3)
				cod_line[ind_cod_line++]=ASSIGNAR;
			 else
				cod_line[ind_cod_line++]=ASSIGN;
*/
			 ind_cod_line=pcodvar(0,v1,var1,fvar1,NULL,ind_cod_line);
			 if(v2)
			 {
				for(i=0;i<v2;i++)
				{
				 ind_cod_line=pcodvar(0,buf2[i].v,buf2[i].var,buf2[i].fvar,buf2[i].op,ind_cod_line);
				}
				cod_line[ind_cod_line++]=0xFF;
				if(v3)
				{
				 for(i=v2;i<v2+v3;i++)
				 {
				  ind_cod_line=pcodvar(0,buf2[i].v,buf2[i].var,buf2[i].fvar,buf2[i].op,ind_cod_line);
				 }
				 cod_line[ind_cod_line++]=0xFF;
				}
//				cod_line[ind_cod_line++]=0xFF;
			 }

/*
			for(i=0;i<v3;i++)
			{
				 ind_cod_line=pcodvar(0,buf2[i].v,buf2[i].var,buf2[i].fvar,buf2[i].op,ind_cod_line);
			}
*/
		 }
		 for(i=0;i<n_var;i++)
		 {
				 ind_cod_line=pcodvar(0,buf[i].v,buf[i].var,buf[i].fvar,buf[i].op,ind_cod_line);
		 }
/*
		 if (!DORU_SYSTEM)
			 cod_line[ind_cod_line++]='\x09';
*/
		 if (then_else)
			 {
				cod_line[ind_cod_line++]=0xFF;
				return;
			 }
		 len_cod_linie = ind_cod_line ;
		 break;
 case DIM:
 case INTEGER_TYPE:
 case BYTE_TYPE:
 case STRING_TYPE:
 case LONG_TYPE:
 case FLOAT_TYPE:
 case PHONE:
 case REM:
		 if (!then_else)
		 {
			put_line_num( line_value );
		 }
		 cod_line[ind_cod_line++]=type;
		 cod_line[ind_cod_line++]=strlen(pedit->comment);
		 strcpy(&cod_line[ind_cod_line],pedit->comment);
		 ind_cod_line += strlen(pedit->comment);
		 if (then_else)
				 return;
		 len_cod_linie = ind_cod_line ;
		 break;
 case PRINT:
		 buf=(struct buf_str*)var2;
		 if (!then_else)
		 {
			put_line_num( line_value );
		 }
		 cod_line[ind_cod_line++]=PRINT;
		 cod_line[ind_cod_line++]=(char)n_var;
		 j=0;
		 for(i=0;i<n_var;i++)
		 switch (buf[i].v) {
		 case STRING:
				 cod_line[ind_cod_line++]=STRING;
				 n = strlen(&pedit->comment[j]);
				 cod_line[ind_cod_line++]=n;
				 strcpy(&cod_line[ind_cod_line],&pedit->comment[j]);
				 ind_cod_line += n;
				 j += n+1;
//				 strcpy(&cod_line[ind_cod_line],buf[i].var);
//				 ind_cod_line +=  strlen(buf[i].var)+1;
				 break;
		 case DATE:
				 cod_line[ind_cod_line++]=DATE;
				 break;
		 case PTIME:
				 cod_line[ind_cod_line++]=PTIME;
				 break;
		 case USER_A:
				 cod_line[ind_cod_line++]=USER_A;
				 break;
		 case USER_B:
				 cod_line[ind_cod_line++]=USER_B;
				 break;
		 case BEEP:
				 cod_line[ind_cod_line++]=BEEP;
				 break;
		 case IDENTIFIER:
				 ind_cod_line=pcodvar(0,buf[i].v,buf[i].var,buf[i].fvar,NULL,ind_cod_line);
				 break;
		 case NL:
				 cod_line[ind_cod_line++]=STRING;
				 cod_line[ind_cod_line++]=2;
				 cod_line[ind_cod_line++]=0x0D;
				 cod_line[ind_cod_line++]=0x0A;
//				 cod_line[ind_cod_line++]='\x00';
				 break;
		 }
		 if (then_else)
			{
			 cod_line[ind_cod_line++]=0xFF;
			 return;
			}
		 len_cod_linie = ind_cod_line;
		 break;
 case CLEARX:
 case ENDPRG:
 case RETURN:
 case HANGUP:
		 if (!then_else)
		 {
				put_line_num( line_value );
		 }
		 cod_line[ind_cod_line++]=type;
		 if (then_else)
			{
			 cod_line[ind_cod_line++]=0xFF;
			 return;
			}
		 len_cod_linie = ind_cod_line;
		 break;
 case OPEN:
 case CLOSE:
 case DISABLEX:
 case ENABLEX:
 case STARTPRG:
 case STOP:
		 if (!then_else)
		 {
			 put_line_num( line_value );
		 }
		 cod_line[ind_cod_line++]=type;
		 ind_cod_line=pcodvar(0,v1,var1,fvar1,NULL,ind_cod_line);
		 if (then_else)
			{
//			 cod_line[ind_cod_line++]='\xFF';
			 return;
			}
		 len_cod_linie = ind_cod_line;
		 break;
 case RUN_MACRO:
		 if (!then_else)
		 {
			 put_line_num( line_value );
		 }
		 cod_line[ind_cod_line++]=0x23;
		 cod_line[ind_cod_line++]=(char)fvar1;
		 if (then_else)
				 return;
		 len_cod_linie = ind_cod_line;
		 break;
 case SET_PRINTER:
		 if (!then_else)
		 {
			 put_line_num( line_value );
		 }
		 cod_line[ind_cod_line++]=0x28;
		 cod_line[ind_cod_line++]=*var1;
		 if (then_else)
				 return;
		 len_cod_linie = ind_cod_line;
		 break;
 case ON:
		 buf=(struct buf_str*)var2;
		 buf1 = (int *)var1;
		 if (!then_else)
		 {
			 put_line_num( line_value );
		 }
		 if (DORU_SYSTEM)
			 cod_line[ind_cod_line++]=ON;
		 for(i=0;i<n_var;i++)
		 {
				 ind_cod_line=pcodvar(0,buf[i].v,buf[i].var,buf[i].fvar,buf[i].op,ind_cod_line);
		 }
		 if (DORU_SYSTEM)
				 cod_line[ind_cod_line++]=0xFF;
		 if (fvar1==GOTO)
//			cod_line[ind_cod_line++]=0x16;
			cod_line[ind_cod_line++]=GOTO;
		 else
//			cod_line[ind_cod_line++]=0x0C;
			cod_line[ind_cod_line++]=GOSUB;
		 cod_line[ind_cod_line++]=v1;
		 line_table[lline-1].go_to=1;
		 for(i=0;i<v1;i++)
			{
			go_to[index_go_to].line=lline;
			go_to[index_go_to].go_to=buf1[i];
//			go_to[index_go_to++].pos = (int)ftell(fp)+ind_cod_line;
			go_to[index_go_to++].pos = code-pedit->code+ind_cod_line;
			ind_cod_line += 2;
			}
		 if (then_else)
				 return;
		 len_cod_linie = ind_cod_line ;
		 break;
 case ON_ALARM:
		 if (then_else)
		 {
		 cod_line[ind_cod_line++]=0x2B;
//		 line_table[line-1].go_to_pos=1;
		 go_to[index_go_to-1].line=lline;
//		 go_to[index_go_to-1].pos = (int)ftell(fp)+ind_cod_line;
		 go_to[index_go_to-1].pos = code-pedit->code+ind_cod_line;
		 ind_cod_line += 2;
		 return;
		 }
		 put_line_num( line_value );
		 cod_line[ind_cod_line++]=0x2B;
//		 line_table[line-1].go_to_pos=1;
		 go_to[index_go_to-1].line=lline;
//		 go_to[index_go_to-1].pos = (int)ftell(fp)+4;
		 go_to[index_go_to-1].pos = code-pedit->code+4;
		 cod_line[ind_cod_line++]=0;
		 cod_line[ind_cod_line++]=0;
		 len_cod_linie = ind_cod_line;
		 break;
 case ON_ERROR:
		 if (then_else)
		 {
		 cod_line[ind_cod_line++]=0x27;
//		 line_table[line-1].go_to_pos=1;
		 go_to[index_go_to-1].line=lline;
//		 go_to[index_go_to-1].pos = (int)ftell(fp)+ind_cod_line;
		 go_to[index_go_to-1].pos = code-pedit->code+ind_cod_line;
		 ind_cod_line += 2;
		 return;
		 }
		 put_line_num( line_value );
		 cod_line[ind_cod_line++]=0x27;
//		 line_table[line-1].go_to_pos=1;
		 go_to[index_go_to-1].line=lline;
//		 go_to[index_go_to-1].pos = (int)ftell(fp)+4;
		 go_to[index_go_to-1].pos = code-pedit->code+4;
		 cod_line[ind_cod_line++]=0;
		 cod_line[ind_cod_line++]=0;
		 len_cod_linie = ind_cod_line;
		 break;
 case GOTO:
		 if (then_else)
		 {
		 cod_line[ind_cod_line++]=GOTO;
//		 line_table[line-1].go_to_pos=1;
		 go_to[index_go_to-1].line=lline;
//		 go_to[index_go_to-1].pos = (int)ftell(fp)+ind_cod_line;
		 go_to[index_go_to-1].pos = code-pedit->code+ind_cod_line;
		 ind_cod_line += 2;
		 return;
		 }
		 put_line_num( line_value );
		 cod_line[ind_cod_line++]=GOTO;
//		 line_table[line-1].go_to_pos=1;
		 go_to[index_go_to-1].line=lline;
//		 go_to[index_go_to-1].pos = (int)ftell(fp)+4;
		 go_to[index_go_to-1].pos = code-pedit->code+4;
		 cod_line[ind_cod_line++]=0;
		 cod_line[ind_cod_line++]=0;
		 len_cod_linie = ind_cod_line;
		 break;
 case GOTOIF:
		 if (then_else)
		 {
		 cod_line[ind_cod_line++]=0x2A;
//		 line_table[line-1].go_to_pos=(int)ftell(fp)+ind_cod_line;
		 go_to[index_go_to-1].line=lline;
//		 go_to[index_go_to-1].pos = (int)ftell(fp)+ind_cod_line;
		 go_to[index_go_to-1].pos = code-pedit->code+ind_cod_line;
		 ind_cod_line += 2;
		 cod_line[ind_cod_line++]=0xFF;
		 return;
		 }
		 break;
 case GOSUB:
		 if (then_else)
		 {
		 cod_line[ind_cod_line++]=GOSUB;
 //		 line_table[line-1].go_to_pos=(int)ftell(fp)+ind_cod_line;
		 go_to[index_go_to-1].line=lline;
//		 go_to[index_go_to-1].pos = (int)ftell(fp)+ind_cod_line;
		 go_to[index_go_to-1].pos = code-pedit->code+ind_cod_line;
		 ind_cod_line += 2;
		 return;
		 }
		 put_line_num( line_value );
		 cod_line[ind_cod_line++]=GOSUB;
//		 line_table[line-1].go_to_pos=1;
		 go_to[index_go_to-1].line=lline;
//		 go_to[index_go_to-1].pos = (int)ftell(fp)+4;
		 go_to[index_go_to-1].pos = code-pedit->code+4;
		 cod_line[ind_cod_line++]=0;
		 cod_line[ind_cod_line++]=0;
		 len_cod_linie = ind_cod_line;
		 break;
 case Alarm:
		 buf=(struct buf_str*)var2;
		 if (!then_else)
		 {
			 put_line_num( line_value );
		 }
		 if (DORU_SYSTEM)
			 cod_line[ind_cod_line++]=0x41;
		 for(i=0;i<n_var1;i++)
		 {
				 ind_cod_line=pcodvar(0,buf[i].v,buf[i].var,buf[i].fvar,buf[i].op,ind_cod_line);
		 }
		 if (DORU_SYSTEM)
			 cod_line[ind_cod_line++]=(char)v1;
		 for(i=n_var1;i<n_var2;i++)
				{
				 ind_cod_line=pcodvar(0,buf[i].v,buf[i].var,buf[i].fvar,buf[i].op,ind_cod_line);
				}
		 if (DORU_SYSTEM)
			 cod_line[ind_cod_line++]=0xFF;
		 for(i=n_var2;i<n_var;i++)
		 {
				 ind_cod_line=pcodvar(0,buf[i].v,buf[i].var,buf[i].fvar,buf[i].op,ind_cod_line);
		 }

		 if (DORU_SYSTEM)
		 {
			 cod_line[ind_cod_line++]=0xFF;
		 }
/*
		 else
		 {
			cod_line[ind_cod_line++]='\x19';
			cod_line[ind_cod_line++]='\x00';
			cod_line[ind_cod_line++]='\x01';
		 }
*/
		 cod_line[ind_cod_line++]=strlen(pedit->comment);
		 strcpy(&cod_line[ind_cod_line],pedit->comment);
		 ind_cod_line += strlen(pedit->comment);
		 if (DORU_SYSTEM)
		 {
			 cod_line[ind_cod_line++] = 0;
		 }
		 if (then_else)
				 return;
		 len_cod_linie = ind_cod_line;
		 break;
 case PRINT_ALARM_AT_ALL:
		 if (!then_else)
		 {
			 put_line_num( line_value );
		 }
		 if (id == ALARM_AT)
			 cod_line[ind_cod_line++]=0x21;
		 else
			 cod_line[ind_cod_line++]=0x1B;

		 cod_line[ind_cod_line++]=0xFF;
		 if (then_else)
				 return;
		 len_cod_linie = ind_cod_line;
		 break;
 case PRINT_ALARM_AT:
		 if (!then_else)
		 {
			 put_line_num( line_value );
		 }
		 if (id == ALARM_AT)
			 cod_line[ind_cod_line++]=0x21;
		 else
			 cod_line[ind_cod_line++]=0x1B;
		 cod_line[ind_cod_line++]=(int)fvar1;
		 if (n_var>=2)
			 cod_line[ind_cod_line++]=(int)fvar2;
		 if (n_var==3)
			 cod_line[ind_cod_line++]=(int)fvar3;
		 cod_line[ind_cod_line++]=0;
		 if(n_var==3)
			 ind_cod_line = 7;
		 if (then_else)
				 return;
		 len_cod_linie = ind_cod_line;
		 break;
 case CALLB:
		 buf=(struct buf_str*)var2;
		 if (!then_else)
		 {
			 put_line_num( line_value );
		 }
		 if (DORU_SYSTEM)
		 {
			 cod_line[ind_cod_line++]=0x2F;
			 find_var_def(var1);
			 cod_line[ind_cod_line++]=(char)(vars_table[cur_index].num_point-1);
			 cod_line[ind_cod_line++]=v2;
		 }
		 j=0;
		 for(i=0;i<n_var;i++)
		 {
				 ind_cod_line=pcodvar(NAME,buf[i].v,buf[i].var,buf[i].fvar,buf[i].op,ind_cod_line);
				 if(DORU_SYSTEM)
					 if (argcall[j]==i+1)
							{
							 j++;
							 cod_line[ind_cod_line++]=0xFF;
							}
//				 n = n + 3 + (buf[i].v^'\x01')*2;
		 }

/*
		 if (!DORU_SYSTEM)
		 {
			 cod_line[ind_cod_line++]='\x2F';
			 find_var_def(var1);
			 cod_line[ind_cod_line++]=(char)(vars_table[cur_index].num_point-1);
			 cod_line[ind_cod_line++]=v2;
		 }
*/
		 if (then_else)
				 return;
		 len_cod_linie = ind_cod_line;
		 break;
 case DALARM:
		 buf=(struct buf_str*)var2;
		 if (!then_else)
		 {
			 put_line_num( line_value );
		 }
		 if (DORU_SYSTEM)
			 cod_line[ind_cod_line++]=0x43;
		 for(i=0;i<n_var;i++)
		 {
				 ind_cod_line=pcodvar(0,buf[i].v,buf[i].var,buf[i].fvar,buf[i].op,ind_cod_line);
		 }
		 if (DORU_SYSTEM)
			cod_line[ind_cod_line++]=0xFF;
/*
		 else
		 {
			cod_line[ind_cod_line++]='\x2C';
			cod_line[ind_cod_line++]='\x0';
		 }
*/
		 lval = (long) (fvar1*1000);
//		 cod_putlong(ind_cod_line, lval, pedit->ptrprg->type);
		 memcpy(&cod_line[ind_cod_line],&lval,4);
		 ind_cod_line += 4;
		 dalarm[index_dalarm].line=lline;

/*
		 if (!DORU_SYSTEM)
		 {
			 dalarm[index_dalarm++].pos = code-pedit->code+ind_cod_line;
			 ind_cod_line += 2;
		 }
*/
		 cod_line[ind_cod_line++]=strlen(pedit->comment);
		 strcpy(&cod_line[ind_cod_line],pedit->comment);
		 ind_cod_line += strlen(pedit->comment);

		 if (DORU_SYSTEM)
		 {
//			 cod_putlong(ind_cod_line, lval, pedit->ptrprg->type);
			 memcpy(&cod_line[ind_cod_line],&lval,4);
			 ind_cod_line += 4;
		 }

		 if (then_else)
				 return;
		 len_cod_linie = ind_cod_line;
		 break;
 case DECLARE:
		 buf=(struct buf_str*)var2;
		 if (!then_else)
		 {
			 put_line_num( line_value );
		 }
		 cod_line[ind_cod_line++]=0x30;
		 cod_line[ind_cod_line++]=(char)n_var;

		 for(i=0;i<n_var;i++)
				{
				 ind_cod_line=pcodvar(0,buf[i].v,buf[i].var,buf[i].fvar,NULL,ind_cod_line);
				}
		 if (then_else)
				 return;
		 len_cod_linie = ind_cod_line;
		 break;
 case REMOTE_GET:
 case REMOTE_SET:
		 if (!then_else)
		 {
			 put_line_num( line_value );
		 }
		 if (type == REMOTE_SET)
				cod_line[ind_cod_line++]=0x22;
		 else
				cod_line[ind_cod_line++]=0x24;
		 if (type == REMOTE_SET)
				 ind_cod_line=pcodvar(0,v1,var1,fvar1,NULL,ind_cod_line);
		 else
				 ind_cod_line=pcodvar(NAME,v1,var1,fvar1,NULL,ind_cod_line);

		 ind_cod_line=pcodvar(0,v2,var2,fvar2,NULL,ind_cod_line);
		 if (then_else)
				 return;
		 len_cod_linie = ind_cod_line;
		 break;
 case FOR:
		 buf=(struct buf_str*)var2;
		 if (!then_else)
		 {
			 put_line_num( line_value );
		 }
		 if (DORU_SYSTEM)
			 cod_line[ind_cod_line++]=FOR;
		 ind_cod_line=pcodvar(NAME,v1,var1,fvar1,NULL,ind_cod_line);
		 j=0;
		 for(i=0;i<n_var;i++)
				{
				 ind_cod_line=pcodvar(0,buf[i].v,buf[i].var,buf[i].fvar,buf[i].op,ind_cod_line);
				 if(DORU_SYSTEM)
					 if (argcall[j]==i+1)
							{
							 j++;
							 cod_line[ind_cod_line++]=0xFF;
							}
//				 n = n + 3 + (buf[i].v^'\x01')*2;
				}
/*
		 if (!DORU_SYSTEM)
			 cod_line[ind_cod_line++]='\x0B';
*/
		 line_table[lline-1].for_count=for_count;
		 line_table[lline-1].for_pos=code-pedit->code+ind_cod_line;
		 ind_cod_line += 2;
		 if (then_else)
				 return;
		 len_cod_linie = ind_cod_line ;
		 break;
 case NEXT:
		 buf=(struct buf_str*)var2;
		 if (!then_else)
		 {
			 put_line_num( line_value );
		 }
		 cod_line[ind_cod_line++]=NEXT;
		 line_table[lline-1].for_count=for_count;
//		 line_table[line-1].next_pos=(int)ftell(fp)+4;
		 line_table[lline-1].next_pos=code-pedit->code+ind_cod_line;
		 ind_cod_line += 2;
		 if (then_else)
				 return;
		 len_cod_linie = ind_cod_line ;
		 break;
 case IF:
		 buf=(struct buf_str*)var2;
		 if (!then_else)
		 {
			 put_line_num( line_value );
		 }
		 if (DORU_SYSTEM)
		 {
			 if (fvar1==0)
				 cod_line[ind_cod_line++]=0x0E;
			 if (fvar1==1)
				 cod_line[ind_cod_line++]=0x11;
			 if (fvar1==2)
				 cod_line[ind_cod_line++]=0x12;
		 }
		 for(i=0;i<n_var;i++)
		 {
				 ind_cod_line=pcodvar(0,buf[i].v,buf[i].var,buf[i].fvar,buf[i].op,ind_cod_line);
		 }
		 if (DORU_SYSTEM)
				 cod_line[ind_cod_line++]=0xFF;

		 if (fvar1==0)
		 {
/*
			if (!DORU_SYSTEM)
				 cod_line[ind_cod_line++]='\x0E';
*/
			next_then_else = ind_cod_line;
			cod_line[ind_cod_line++]=0;
			cod_line[ind_cod_line++]=0;
			return;
		 }
		 if (fvar1==1)
		 {
			if (DORU_SYSTEM)
				cod_line[ind_cod_line++]=0;   //    ifP
/*
			else
				cod_line[ind_cod_line++]='\x11';
*/
			next_then_else = ind_cod_line;
			cod_line[ind_cod_line++]=0;
			cod_line[ind_cod_line++]=0;
/*
			if (!DORU_SYSTEM)
			{
				cod_line[ind_cod_line++]='\x01';
				cod_line[ind_cod_line++]='\x0';
			}
*/
			return;
		 }
		 if (fvar1==2)
		 {
			if (DORU_SYSTEM)
					cod_line[ind_cod_line++]=0;   //    ifm
/*
			else
					cod_line[ind_cod_line++]='\x12';
*/
			next_then_else = ind_cod_line;
			cod_line[ind_cod_line++]=0;
			cod_line[ind_cod_line++]=0;
/*
			if (!DORU_SYSTEM)
			{
				cod_line[ind_cod_line++]='\x0';
				cod_line[ind_cod_line++]='\x01';
			}
*/
			return;
			}

 case WAIT:
		 buf=(struct buf_str*)var2;
		 if (!then_else)
		 {
			 put_line_num( line_value );
		 }
		 if (DORU_SYSTEM)
			 cod_line[ind_cod_line++]=0x1E;
		 if(v1)
		 {
				cod_line[ind_cod_line++]=0xA1;
				if (DORU_SYSTEM)
				{
//					cod_putlong(ind_cod_line, ttimed, pedit->ptrprg->type);
					memcpy(&cod_line[ind_cod_line], &ttimed, 4);
				}
/*
				else
					memcpy(&cod_line[ind_cod_line], &fvar1, 4);
*/
				ind_cod_line += 4;
		 }
		 else
		 {
			for(i=0;i<n_var;i++)
			{
				 ind_cod_line=pcodvar(0,buf[i].v,buf[i].var,buf[i].fvar,buf[i].op,ind_cod_line);
			}
			if (DORU_SYSTEM)
			  cod_line[ind_cod_line++]=0xFF;
		 }
		 if (DORU_SYSTEM)
		 {
			 cod_line[ind_cod_line++]=0;
			 cod_line[ind_cod_line++]=0;
			 cod_line[ind_cod_line++]=0;
			 cod_line[ind_cod_line++]=0;
		 }

/*
		 if (!DORU_SYSTEM)
		 {
			cod_line[ind_cod_line++]='\x1E';
			wait[index_wait][0] = code-pedit->code+ind_cod_line;
			ind_cod_line += 2;
			wait[index_wait++][1]=code-pedit->code+ind_cod_line+2-2;
		 }
*/
		 if (then_else)
		 {
			 cod_line[ind_cod_line++]=0xFF;
			 return;
		 }
		 len_cod_linie = ind_cod_line ;
		 break;
 }
 if( ncod + len_cod_linie + 2 < PROGRAM_SIZE )
 {
  ncod = ncod + len_cod_linie ;
  memcpy(code,cod_line,len_cod_linie);
  code += len_cod_linie;
 }
 else
  ncod = PROGRAM_SIZE;
}

void eval_exp(float *value)
{
 char *p,*q;
 signed char semn;
 get_token();
// get_token();
 if((p=strchr(token,'e'))==0)
	 p=strchr(token,'E');
 if(p)
 {
	*p = 0;
#ifndef NOMATH
	*value = (float)atof(token) ;
#else
	*value = atofproc(token) ;
#endif
	semn = 1;
	p++;
 if((q=strchr(p,'-'))!=0)
	{
	 semn=-1;
	 q++;
	}
 else
 if((q=strchr(p,'+'))!=0)
	 q++;
 if(!q)
	q=p;
#ifndef NOMATH
 *value *= (float)pow(10,semn*atof(q));
#else
 *value *= (float)pow(10,semn*atofproc(q));
#endif
 }
 else
 {
#ifndef NOMATH
		*value = (float)atof(token) ;
#else
		*value = (float)atofproc(token) ;
#endif
 }

 /*
 get_token() ;
 if (token_type==NL)
		if (eol==NL) {--prog;--prog;}
		else --prog;
 else
 putback();
*/
 return ;
}

