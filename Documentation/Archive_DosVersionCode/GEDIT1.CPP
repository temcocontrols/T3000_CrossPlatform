#include <graphics.h>
#include <process.h>
#include <windows.h>
#include "t3000def.h"
#include "aio.h"
#include "mtkernel.h"
#include "parser.h"
#include "_msdos.h"
#include "gedit.h"
#include "rs485.h"

#define Srt '\`'
#define TAB 2
#define TABEDI 3
#define TABMES 4
#define ESC 27

extern int fond_color;
extern int renumvar;
extern char *lin_text;

extern int comman_line(int lx, int ly, int rx, int ry, int fond_color, GEdit *edit=NULL);
extern int mgetword(int x, int y, char *pword, int length = 80);
extern int ReadYesNo(int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							int bkgndrreadcolor, int readcolor, char *text, char yes='Y', char no='N', char s=0);
extern ReadWindow(int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							 int bkgndrreadcolor, int readcolor, char *text, char *buf, int width);
extern int icommand(char *buf, int from, byte panel, int network);
extern int print_alarm_word(void);
extern int check_access(int ptype, int num=-1, int mes=R_NA);
extern  mmain ( GEdit *pedit);
extern void DisplayError(int lx, int ly, int rx, int ry, char *message,int bkgnd, int frgnd, int tbkgnd, int fcolor=Black);
extern int updateremotepoint(Point_Net point, int network);
extern char *Heap_alloc(int bytes);
extern int Heap_dealloc(char **old);
extern int Heap_move(char *old,  char *newp, int ind);
extern int net_call(int command, int arg,  char *data, uint *length , int dest,
				 int network, int others=0, int timeout=TIMEOUT_NETCALL,
				 char *returnargs=NULL, int *length_returnargs=NULL,
				 char *sendargs=NULL, int length_sendargs=0, char bytearg=0, int port=-1);
extern char * intervaltotext(char *textbuf, long seconds , unsigned minutes , unsigned hours, char *c=":");
extern int pointtotext(char *buf,Point_Net *point);
extern int pointtotext(char *buf,Point_T3000 *point);
extern char *ispoint(char *token,int *num_point,byte *var_type, byte *point_type, int *num_panel, int *num_net, int network=0, byte panel=0, int *netpresent=0);
extern void ftoa(float f, int length, int ndec, char *buf);
extern char *ltrim(char *text);
extern int local_request(int panel, int network);

extern unsigned int line_array[50][2];
extern int ind_line_array;
extern Panel_info1 panel_info1;
extern REMOTE_POINTS _far	remote_points_list[MAXREMOTEPOINTS82];
extern int  Station_NUM;
extern int local_panel;
extern char huge *lin_menu;
extern char sendedit;
extern char pword[40];
extern char prg_active ;
extern Panel *ptr_panel;
extern char tempbuf[65];
extern char huge *bas_text;
extern char int_disk1;
extern char lastdelete,lastline,lastblock;
extern int programs_size;
extern int ind_local_table;
extern int lline;

extern struct func_table {
 char func_name[15] ;
 char tok ;
} func_table[];

extern struct {
 char command[15] ;
 char tok ;
} table[];


int ind_remote_local_list;
struct remote_local_list  remote_local_list[MAXREMOTEPOINTS];
char stack[150];
char *index_stack;
char *pcode, *ptimebuf;
char *local;

char *desassembler_program( );
char *look_instr( char cod );
char *look_func( char cod );
int desvar(char *buf,char *pcode);
int	desexpr(char *buf, char *pcode);
void push(char *buf);
char *pop(void);
int update_prg(char *buf, int ind_prg, char *code, Str_program_point *ptrprg, int panel, GEdit *pe=NULL);    // buff=0 local, #0 dist
//int basicprogram(char *source, char *code, Str_program_point *prg, int currentprogram, int panel, int network);

void GEdit::infoheapprg(int x, int y)
{
 char bbuf[7];
					mxyputs(x+43,y+2,"Programs pool size:        bytes",Blue,Lightgray);
					mxyputs(x+64,y+2,ltoa(pool_size,bbuf,10),Blue,Lightgray);
					mxyputs(x+43,y+3,"Programs size     :        bytes",Blue,Lightgray);
					mxyputs(x+64,y+3,ltoa(total_programs_size,bbuf,10),Blue,Lightgray);
					mxyputs(x+43,y+4,"Free memory       :        bytes",Blue,Lightgray);
					mxyputs(x+64,y+4,ltoa(pool_size-total_programs_size,bbuf,10),Blue,Lightgray);
}
int GEdit::compile(void)
{
			 int i,j,ret=0;
			 if(check_access(PRG,current_point_prg,R_NA|1)==R_READ_WRITE)
			 {
				 memset(mesbuf,'\0',MES_SIZE);
				 i = renumvar;
//				 renumvar = 0;
				 if( (j=mmain(this))!=0 )
				 {
					if( j == 3 )
					{
						DisplayError(20, 7, 60, 14, "Error. Program to big!",Lightgray, Red, Red);
					}
					else
					 if( j == 4 )
					 {
						 DisplayError(20, 7, 60, 14, "Error. Too many remote points!",Lightgray, Red, Red);
					 }
					 else
						if (message==0)
						{
							mty=by-ty-HIGH_MES+2 ;mby=0;
							MAX_LINES = HIGH_MES-2;
							message = 1;
							editt=0;
							escrnx=scrnx;escrny=scrny;
							ecurloc = curloc;eendloc = endloc;
							curloc = mesbuf;
							endloc = mesbuf+strlen(mesbuf);
							scrnx=0;scrny=0;
							egotoxy(0,0);
							buf=&mesbuf[0];
				//			load("message.txt");
							display_scrn(0,0,curloc,1);
							goedit();
							tab=0;
							DisplayError(20, 7, 60, 14, "Errors, program NOT sent!",Lightgray, Red, Red);
						}
				}
				else
				{
				 if(i)
				 {
						renumvar = i;
						curloc = buf;
						endloc = curloc + strlen(buf);
						scrnx = scrny = 0;
						lastdelete = lastline = lastblock = 0;
						beginblock = endblock = 0;
						beginline = endline = 0;
						display_scrn(0,0,curloc);
						sendedit=1;
						return ret;
				 }
				 else
				 {
				 lin_menu[bx-tx+1]=0;
				 for(int j=by-HIGH_MES+2;j<=by;j++)
						mxyputs(tx,j,lin_menu,bkgcolour,bkgcolour);
				 lin_menu[bx-tx+1]=lin_menu[0];
				 if ( (ret=update_prg(NULL,current_point_prg, code, ptrprg, panel, this))==0)
					 DisplayError(19, 7, 60, 14, "Error, program NOT sent!",Lightgray, Red, Red); //Not enough memory
//					mxyputs(tx,by-HIGH_MES+2,"Not enough memory, program NOT sent",colour,White);
				 else
				 {
					 char bbuf[60];
					 if (message==0)
					 {
						 if( mesbuf[0] )
						 {
							mty=by-ty-HIGH_MES+2 ;mby=0;
							MAX_LINES = HIGH_MES-2;
							message = 1;
							editt=0;
							escrnx=scrnx;escrny=scrny;
							ecurloc = curloc;eendloc = endloc;
							curloc = mesbuf;
							endloc = mesbuf+strlen(mesbuf);
							scrnx=0;scrny=0;
							egotoxy(0,0);
							buf=&mesbuf[0];
							display_scrn(0,0,curloc,1);
							goedit();
							tab=0;
             }
					 }
					 strcpy(bbuf, "Program sent, 0 errors, ");
					 itoa(ptrprg->bytes,&bbuf[strlen(bbuf)],10);
					 strcat(bbuf, " bytes");
					 DisplayError(19, 7, 60, 14, bbuf,Lightgray, White, Darkgray);
                if( ret!=ESC ) ret = 0;
//					mxyputs(tx,by-HIGH_MES+2,"Program sent, 0 errors,      bytes",colour,White);
//					mxyputs(tx+24,by-HIGH_MES+2,itoa(ptrprg->bytes,bbuf,10),colour,White);
				 }
					infoheapprg(tx,by-HIGH_MES);
				 }
				}
				sendedit=0;
			}
 return ret;
}
/*
main(int argc, char *argv[])
{
 if(argc==2) edit(argv[1]);
 clrscr();
}

*/

int update_prg(char *buf, int ind_prg, char *code, Str_program_point *ptrprg, int panel, GEdit *pe)    // 0 local, #0 dist
{
 uint i;
 int ret=1, j, i_del_remote_list=0, program_size;
 unsigned int bytes, l;	// size in byte s of program)
 if (!buf)
 {
//					if(local_panel && panel==Station_NUM)
					if(local_request(panel, pe->network))
					{
					 for(i=0;i<ind_remote_local_list;)
						if(remote_local_list[i].index<999 && remote_local_list[i].index>=0)
						{
						 int k;
						 k = remote_local_list[i].index;
						 if( !(--remote_points_list[k].count) )
						 {
							 memset(&remote_points_list[k],0,sizeof(REMOTE_POINTS));
//							 remote_points_list[k].info.point.setzero();
//							 want_points_list[k].point.setzero();
						 }
						 memmove(&remote_local_list[i],&remote_local_list[i+1],(ind_remote_local_list-i-1)*sizeof(struct remote_local_list));
						 ind_remote_local_list--;
						}
						else
						{
						if (remote_local_list[i].index < 0)
						 {
									j=updateremotepoint(remote_local_list[i].point,remote_local_list[i].point.network);
									remote_local_list[i].index = j;
									i++;
						 }
						 else
						 {
							remote_local_list[i].index -= 1000;
							i++;
						 }
					  }
					}
					else
					{
					 for(i=0;i<ind_remote_local_list;i++)
					  if(remote_local_list[i].index<999 && remote_local_list[i].index>=0)
						 i_del_remote_list++;
					}
					int oldsize = ptrprg->bytes;
					memcpy(&bytes,code,2);
//					adjustint((int *)&bytes, ptrprg->type);
					bytes += 3+2;
					l = *((int *)(code+bytes)); // local table
//					adjustint((int *)&l, ptrprg->type);
					bytes += l+2;
					l = *((int *)(code+bytes)); // time-on,off
//					adjustint((int *)&l, ptrprg->type);
					bytes += l+2;

					if( bytes + 2 + (ind_remote_local_list)*sizeof(struct remote_local_list) >= PROGRAM_SIZE )
					{
						DisplayError(20, 7, 60, 14, "Error. Program to big!",Lightgray, Lightred, Red);
					  return 0;
					}
					l = ind_remote_local_list;
//					cod_putint((char *)&l, l, ptrprg->type);
					memcpy(code+bytes, &l, 2);
					memcpy(code+bytes+2, remote_local_list, (ind_remote_local_list)*sizeof(struct remote_local_list));
					bytes += 2 + (ind_remote_local_list)*sizeof(struct remote_local_list);
					if( (pe->total_programs_size+(bytes<=11?0:bytes)-(panel_info1.panel_type==T3000?0:oldsize)) > pe->pool_size)
					{
						 DisplayError(20, 7, 60, 14, "Program NOT sent. Enough memory!",Lightgray, Lightred, Red);
						 return 0;
					}
//					if(local_panel && panel==Station_NUM)
					if(local_request(panel, pe->network))
					{
						if(bytes <= 11) bytes = 0;
						programs_size += bytes - oldsize;
						ptr_panel->programs[ind_prg].bytes = bytes;
						memcpy(&(ptrprg->bytes),&bytes,2);
						pe->total_programs_size = programs_size;
					}
//					if(local_panel && panel==Station_NUM)
					if(local_request(panel, pe->network))
					{
						char *p;
						if(ptrprg->bytes)
						{
						 set_semaphore(&t3000_flag);
						 p=Heap_alloc(ptrprg->bytes);
						 movedata(FP_SEG(code),FP_OFF(code),FP_SEG(p),FP_OFF(p) , ptrprg->bytes);
//						 Heap_move((char huge *)ptr_panel->program_codes[current_point_prg], (char huge *)p, current_point_prg);
						 Heap_move(ptr_panel->program_codes[ind_prg], p, ind_prg);
						 clear_semaphore(&t3000_flag);
						}
						else
						 Heap_dealloc((char **)&ptr_panel->program_codes[ind_prg]);
					}
					else
					{
//						Delay(100);
						i = bytes;
						if( net_call(16+100,ind_prg,code,&i,panel, networkaddress, NETCALL_NOTTIMEOUT)!=SUCCESS )
						{
							if( ind_remote_local_list ) return ESC;
							ret=0;
						}
						else
						{
							bytes -= i_del_remote_list*sizeof(struct remote_local_list);
							if(bytes <= 11) bytes = 0;
							memcpy(&(ptrprg->bytes),&bytes,2);
							pe->total_programs_size += bytes - oldsize;
							if( ind_remote_local_list ) return ESC;
						}
					}
#ifdef NETWORK_COMM
						if( Netbios_state == NB_INSTALLED )
							resume(NETWORK);
#endif
	}
	else
	{
#ifndef WORKSTATION
	struct remote_local_list *r;
	int ind_r;
	programs_size -= ptr_panel->programs[ind_prg].bytes;
	memcpy(&bytes,buf,2);
	bytes += 2+3;

	bytes += *((int *)(buf+bytes))+2; //local table
	bytes += *((int *)(buf+bytes))+2;  //time on-off

	memcpy(&ind_r, buf+bytes, 2);
	r = (struct remote_local_list *)(buf+bytes+2);
//#ifdef NETWORK_COMM
	for(i=0;i<ind_r;)
	 if(r[i].index<999 && r[i].index>=0)
	 {
			int k;
			k = r[i].index;
//			number_of_remote_points--;
			if( !(--remote_points_list[k].count) )
			{
			 memset(&remote_points_list[k],0,sizeof(REMOTE_POINTS));
//			 remote_points_list[k].info.point.setzero();
//			 want_points_list[k].point.setzero();
//			 want_points_list[k].destination = 255;
			}
			memmove(&r[i],&r[i+1],(ind_r-i-1)*sizeof(struct remote_local_list));
			ind_r--;
			memcpy(buf+bytes, &ind_r, 2);  // update ind_r
	 }
	 else
	 {
			if (r[i].index < 0)
			{
						j=updateremotepoint(r[i].point,r[i].point.network);
						r[i].index = j;
						i++;
			}
			else
			{
				r[i].index -= 1000;
				i++;
			}
	 }
//#endif
//	char huge *p;
	char *p;
	bytes += 2 + ind_r * sizeof(struct remote_local_list);
	if(bytes<=11) bytes=0;
	programs_size += bytes;
	if(bytes)
	{
	 set_semaphore(&t3000_flag);
	 p=Heap_alloc(bytes);
	 movedata(FP_SEG(buf),FP_OFF(buf),FP_SEG(p),FP_OFF(p) , bytes);
//	 Heap_move((char huge *)ptr_panel->program_codes[ind_prg], (char huge *)p, ind_prg);
	 Heap_move(ptr_panel->program_codes[ind_prg], p, ind_prg);
	 clear_semaphore(&t3000_flag);
	}
	else
	 Heap_dealloc((char **)&ptr_panel->program_codes[ind_prg]);
	ptr_panel->programs[ind_prg].bytes = bytes;
#endif
	;
	}
return ret;
}

/*
void adjustint(int *i, int type)
{
	if( type != T3000 )
  {
	 _AX = *i;
	 asm xchg ah,al
	 *i = _AX;
  }
}

void adjustlong(unsigned long *l, int type)
{
  unsigned L, H;
	if( type != T3000 )
  {
	 L = (unsigned)( (*l)&0x0000FFFF ) ;
	 H = (unsigned)( (*l)>>16 );
	 asm mov  ax,L
	 asm xchg ah,al
	 asm mov  L,ax
	 asm mov  ax,H
	 asm xchg ah,al
	 asm mov  H,ax
	 *l = L + (H<<16);
  }
}
*/

char *GEdit::desassembler_program()
{
 char cod,xtemp[15];
 int point,type_var,ind,i;
 int id,len,nitem,lvar;
 long lval;

 index_stack = stack;
 int n;
 buf[0]=0;
 int bytes;
 pcode=code+2;
 memcpy(&bytes,code,2);
// adjustint(&bytes, ptrprg->type);
 bytes += 2+3;
 code += bytes;
 memcpy(&ind_local_table,code,2);    //local var
 local = code+2;
// adjustint(&bytes, ptrprg->type);
 code += ind_local_table + 2;
 ptimebuf = code + 2;      //timer
 memcpy(&bytes,code,2);
// adjustint(&bytes, ptrprg->type);
 code += bytes + 2;

 memcpy(&ind_remote_local_list,code,2);
// adjustint(&ind_remote_local_list, ptrprg->type);
 memcpy(remote_local_list,code+2,ind_remote_local_list*sizeof(struct remote_local_list));

 code = pcode;
 int then_else = 0;
 while(*code!=0xFE)
 {
	 if(!then_else)
	 {
		 if (*code!=0x01)
		 {
			printf("ERROR!!!!Desassambler!!!!!!!!!!!!!\n");
//			exit(1);
		 }
		memcpy(&lline,++code,2);
//		adjustint(&lline, ptrprg->type);
		itoa(lline, buf,10);
		code += 2;
		buf += strlen(buf);
		*buf++=' ';
	 }
	 else
		 if (*code==0x01)
				{
				 then_else = 0;
				 buf -= 3;
				 *buf++=0x0d;
				 *buf++=0x0a;
				 continue;
				}
//				 return;          // return when else is finished



	if (*code == ELSE) buf -= 2;
	if (*code != ASSIGN && *code != ASSIGNAR || *code != ASSIGNARRAY_1 || *code != ASSIGNARRAY_2)
	{
			strcpy(buf,look_instr(*code));
			buf += strlen(buf);
			*buf++=' ';
	}

	switch (*code++) {
			case ASSIGNARRAY_1:
			case ASSIGNARRAY_2:
			case ASSIGNAR:
			case ASSIGN:
									i = *(code-1);
									n=desvar();
									buf += strlen(buf);
/*
									if(i == ASSIGNAR)
									{
									 *buf++ = '[';
									 desexpr();
									 buf += strlen(buf);
									 *buf++ = ']';
									}
									else
*/
									{
									 if(i == ASSIGNARRAY_1 || i == ASSIGNARRAY_2)
									 {
									  *buf++ = '(';
									  desexpr();
									  if(n>1)
									  {
										buf += strlen(buf);
										strcpy(buf," , ");
										buf += strlen(buf);
									   desexpr();
									  }
//									  desexpr();
									  buf += strlen(buf);
									  *buf++ = ')';
									 }
									}
									*buf++=' ';
									*buf++='=';
									*buf++=' ';
									desexpr();
									buf += strlen(buf);
									break;

			case STARTPRG:
			case OPEN:
			case ENABLEX:
			case STOP:
			case CLOSE:
			case DISABLEX:
//									desexpr();
									desvar();
									buf += strlen(buf);
									break;
			case PHONE:
			case REM:
			case DIM:
			case INTEGER_TYPE:
			case BYTE_TYPE:
			case STRING_TYPE:
			case LONG_TYPE:
			case FLOAT_TYPE:
									len = *code++;
									memcpy(buf,code,len);
									buf += len;
									code += len;
									break;
			case PRINT:
								  {
									nitem = *code++;
									i=0;
									for(int j=0;j<nitem;j++)
									 {
										switch (*code++) {
											case DATE:
																strcpy(buf,"DATE;");
																buf += 5;
																break;
											case PTIME:
																strcpy(buf,"TIME;");
																buf += 5;
																break;
											case BEEP:
																strcpy(buf,"BEEP;");
																buf += 5;
																break;
											case USER_A:
																strcpy(buf,"USER_A;");
																buf += strlen("USER_A;");
																break;
											case USER_B:
																strcpy(buf,"USER_B;");
																buf += strlen("USER_B;");
																break;
											case STRING:
																len = *code++;
																if (*code=='\r')
																{
																 buf--;
																}
																else
																{
																	*buf++='"';
																	memcpy(buf,code,len);
																	buf += len;
																	*buf++='"';
																	*buf++=';';
																}
																code += len;
																break;

											default:
																code--;
																desexpr();
																buf += strlen(buf);
																*buf++=';';
																break;
									 }
									}
								  }
								  break;
			case CLEARX:              // clear all local variables to zero
			case ENDPRG:
			case RETURN:
			case HANGUP:
									break;
			case SET_PRINTER:
									*buf++ = *code;
									code++;
									break;
			case RUN_MACRO:
									itoa(*code,buf,10);
									buf += strlen(buf);
									code++;
									break;
			case ON:
									desexpr();
									buf += strlen(buf);
									*buf++ = ' ';
//									if (*code++==0x0c)   //gosub
									if (*code++==GOSUB)   //gosub
									{
											strcat(buf,"GOSUB");
											buf += 5;
									}
									else
									{
											strcat(buf,"GOTO");
											buf += 4;
									}
									*buf++ = ' ';
									nitem = *code++;
									for(i=0; i<nitem;i++)
										{
										 memcpy(&n,code,2);
//										 adjustint(&n, ptrprg->type);
//									 itoa(*((int *)&pcode[n-2+1]),buf,10);
										 itoa(*((int *)&pcode[n+1]),buf,10);
										 buf += strlen(buf);
										 *buf++ = ',';
										 code += 2;
										}
									buf--;
									break;
			case GOSUB:
			case ON_ALARM:
			case ON_ERROR:
			case GOTO:
			case GOTOIF:
									 cod = *(code-1);
									 memcpy(&n,code,2);
//									 adjustint(&n, ptrprg->type);
									 itoa(*((int *)&pcode[n-2+1]),buf,10);
									 buf += strlen(buf);
									 code += 2;
									 if(cod == GOTOIF)
											code++;    //FF
									break;
			case Alarm:
/*									if ( ind_line_array && line_array[ind_line_array-1][0]!=line)
										 {
											line_array[ind_line_array][0] = line;
											line_array[ind_line_array++][1] = code-pcode+2;
										 }
*/
									char c,*p;
									if ((p=(char *)memchr(code,LT,30))!=NULL)
										c=LT;
									else
										if ((p=(char *)memchr(code,GT,30))!=NULL)
											c=GT;
									*p='\xFF';
									desexpr();
									buf += strlen(buf);
									if (c==LT)
										strcpy(buf," < ");
									else
										strcpy(buf," > ");
									buf += strlen(buf);
									desexpr();
									buf += strlen(buf);
									strcpy(buf," , ");
									buf += strlen(buf);
									desexpr();
									buf += strlen(buf);
									strcpy(buf," , ");
									buf += strlen(buf);
									len = *code++;
									memcpy(buf,code,len);
									buf += len;
									code += len;
									code++;
									*p=c;
									break;
			case DALARM:
	/*								if ( ind_line_array && line_array[ind_line_array-1][0]!=line)
										 {
											line_array[ind_line_array][0] = line;
											line_array[ind_line_array++][1] = code-pcode+2;
										 }
	*/
									desexpr();
									buf += strlen(buf);
									strcpy(buf," , ");
									buf += strlen(buf);
									memcpy(&lval,code,4);
//									adjustlong((unsigned long *)&lval, ptrprg->type);
									code += 4;
/*									desexpr();
									buf += strlen(buf);
*/
									itoa(lval/1000,buf,10);
									buf += strlen(buf);
									strcpy(buf," , ");
									buf += strlen(buf);
									len = *code++;
									memcpy(buf,code,len);
									buf += len;
									code += len;
									code += 4;
									break;
			case ALARM_AT:
			case PRINT_AT:
									if (*code=='\xFF')
										 {
											strcpy(buf,"ALL");
											buf += 3;
											code++;
										 }
									else {
												i=1;
												while(*code && i++<=3)
													{
													 itoa(*code,buf,10);
													 buf += strlen(buf);
													 *buf++=' ';
													 code++;
													}
												if(*code==0) code++;
											 }
									break;
			case CALLB:
									strcpy(buf,"PRG");
									buf += strlen("PRG");
									itoa((*code++)+1,buf,10);
									buf += strlen(buf);
									strcpy(buf," = ");
									buf += strlen(buf);
									nitem = *code++;
									for(i=0;i<nitem;i++)
									 {
										desexpr();
										buf += strlen(buf);
										if (i!=nitem-1)
											{
											 strcpy(buf," , ");
											 buf += strlen(buf);
											}
									 }
									break;
			case DECLARE:
									nitem = *code++;
									for(i=0; i<nitem; i++)
									 {
										desvar();
										buf += strlen(buf);
										*buf++=' ';
									 }
									break;
			case REMOTE_GET:
			case REMOTE_SET:
										desvar();
										buf += strlen(buf);
										*buf++='=';
										desvar();
										buf += strlen(buf);
									break;
			case FOR:
										desvar();
										buf += strlen(buf);
										strcpy(buf," = ");
										buf += strlen(buf);
										desexpr();
										buf += strlen(buf);
										strcpy(buf," TO ");
										buf += 4;
										desexpr();
										buf += strlen(buf);
										strcpy(buf," STEP ");
										buf += 6;
										desexpr();
										buf += strlen(buf);
										code += 2;
									break;
			case NEXT:
									p=code;
									memcpy(&n,code,2);
//									adjustint(&n, ptrprg->type);
									code=pcode+n-2+4;
									desvar();
									buf += strlen(buf);
									code = p + 2;;
									break;
			case IF:
			case IFP:
			case IFM:
									cod = *(code-1);
									then_else = 0;
									desexpr();
									if( cod == IFP || cod == IFM)
											code++;
									buf += strlen(buf);
									strcpy(buf," THEN ");
									buf += strlen(" THEN ");
									code += 2;

									then_else = 1;
									continue;

			case ELSE:
									code += 3;
									continue;
			case WAIT:
/*									if ( ind_line_array && line_array[ind_line_array-1][0]!=line)
										 {
											line_array[ind_line_array][0] = line;
											line_array[ind_line_array++][1] = code-pcode+2;
										 }
*/
									if (*code==0xA1)
										 {
											unsigned long k;
											memcpy(&k,++code,4);
//									      adjustlong(&k, ptrprg->type);
											intervaltotext(buf, k , 0 , 0 );
											buf += strlen(buf);
											code += 4;
											}
									else
										 {
											desexpr();
											buf += strlen(buf);
										 }
									code += 4;
									break;
	 }
	if(then_else)
		 {
			 strcpy(buf," , ");
			 buf += strlen(buf);
		 }
	else
		 {
			*buf++=0x0d;
			*buf++=0x0a;
		 }
	}
if (then_else)
	 {
		buf -= 3;
		*buf++=0x0d;
		*buf++=0x0a;
	 }

*buf=0;

//mxyputs(1,1,editbuf);
//mgets(buf+1,1, Black, White);

return buf;
}

int isdelimit(char c)
{
 if (strchr( "\x1\xFF\xFE" , c) )
			return 1;
	else
			return 0;
}

int GEdit::desvar(void)
{
 char *b,q[17], *p, *r;
 Point_T3000 point;
 byte point_type,var_type;
 int num_point,num_panel,num_net,k;
 p=buf;
 if (*code == ASSIGNARRAY )
 {
	code++;
 }
 if (*code >= 0x82 && *code <= 0x9B)
 {
	long n;
  n = *((int *)(code+1));
  int t=0,j,k,l,c,m,lc,cc;

  l = c = 0;
  for(j=0;j<ind_local_table; )
  {
	  switch(local[j]){
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
					switch(local[j]){
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
					 memcpy(&l, &local[j+1], 2);
					 memcpy(&c, &local[j+3], 2);
					 if(l)
						k *= l*c;
					 else
					  k *= c;
					 j += 4;
					}
					break;
		}
		m = j + 1;
		j += 1 + k;

		if( n < j )
		{
		 strcpy(p, &local[j]);
		 p += strlen(p);
/*
		 if(l && c)
		 {
		  lc = (n-m)/c + 1;
		  cc = (n-m)%c + 1;
		  *p++ = '(';
		  if(l==1)
		  {
			itoa(cc,p,10);
			p += strlen(p);
		  }
		  else
		  {
			itoa(lc,p,10);
			p += strlen(p);
			*p++ = ',';
			itoa(cc,p,10);
			p += strlen(p);
		  }
		  *p++ = ')';
		 }
*/
		 break;
		}
		j += 1+strlen(&local[j]);
	}
  code += 3;
  return l+1;
 }
 else
	if (*code == (byte)LOCAL_POINT_PRG)
	{
				*((Point *)&point) = *((Point *)++code);
				point.panel = panel-1;
				pointtotext(q, &point);
				code += sizeof(Point);
				k=0;
				strcpy(buf,ispoint(q,&num_point,&var_type, &point_type, &num_panel, &num_net, network, panel, &k));
				if( (point.point_type-1) == AY )
				{
				  b = buf;
				  strcat(buf, "[");
				  buf += strlen(buf);
				  desexpr();
				  strcat(buf, "]");
				  buf = b;
				}
  }
  else
	 if (*code == (byte)REMOTE_POINT_PRG)
	 {
				++code;
				b = code;
				pointtotext(q,(Point_Net *)code);
				code += sizeof(Point_Net);
				k=0;
				strcpy(buf,ispoint(q,&num_point,&var_type, &point_type, &num_panel, &num_net, network, panel, &k));
				if( (((Point_Net *)b)->point_type-1) == AY )
				{
					b = buf;
				  strcat(buf, "[");
				  buf += strlen(buf);
				  desexpr();
				  strcat(buf, "]");
				  buf = b;
				}
	 }
	 else
		 if (*code == CONST_VALUE_PRG)
		 {
						float f;
						long l;
						memcpy(&l,++code,4);
//						adjustlong((unsigned long *)&l, ptrprg->type);
						f = (float)l / 1000.;
						code += 4;
						if( *code == TIME_FORMAT)
						{
						 code++;
						 intervaltotext(buf, (long)f, 0, 0);
						}
						else
						if((long)f==f && (f<1000000 && f>-1000000 ))
						 {
							ltoa((long)f,buf,10);
						 }
						else
						 {
							ftoa(f, 15, 2, buf);
							ltrim(buf);
						 }
		 }
		 else
			return 0;
 return 1;
}

int	GEdit::desexpr(void)
{
 char *op1,*op2,*op;
 char oper[10],last_oper,par,opar;
 int point,i;
 char n;
 char stack_par[30];
 char ind_par;
// index_stack = stack;
 set_semaphore_dos();
 op1 = new char [200];
 op2 = new char [200];
 op = new char [200];
 clear_semaphore_dos();

 ind_par=0;
 desvar();
 push(buf);
 stack_par[ind_par++]=0;
 last_oper=0;
 while( !isdelimit(*code))         // && code < )
 {
	switch (*code++) {
		case PLUS:
							 strcpy(oper," + ");
							 par=1;
							 break;
		case MINUS:
							 strcpy(oper," - ");
							 par=1;
							 break;
		case POW:
							 strcpy(oper," ^ ");
							 par=0;
							 break;
		case MUL:
							 strcpy(oper," * ");
							 par=0;
							 break;
		case DIV:
							 strcpy(oper," / ");
							 par=0;
							 break;
		case MOD:
							 strcpy(oper," % ");
							 par=0;
							 break;
		case XOR:
							 strcpy(oper," XOR ");
							 par=0;
							 break;
		case OR:
							 strcpy(oper," OR ");
							 par=0;
							 break;
		case AND:
							 strcpy(oper," AND ");
							 par=0;
							 break;
		case MINUSUNAR:
		case NOT:
							 par=0;
							 if(*(code-1)==NOT)
								{
								 strcpy(op1," NOT ");
								 strcpy(op2,pop());
								 if( strchr(op2,' ') )
								 {
									strcat(op1,"( ");
									strcat(op1,op2);
									strcat(op1," )");
								 }
								 else
									strcat(op1,op2);
								}
							 else
								{
								 strcpy(op1," -");
								 strcat(op1,pop());
								}
							 ind_par--;
							 push(op1);
							 stack_par[ind_par++]=0;
							 break;
		case GT:
							 strcpy(oper," > ");
							 par=0;
							 break;
		case GE:
							 strcpy(oper," >= ");
							 par=0;
							 break;
		case LT:
							 strcpy(oper," < ");
							 par=0;
							 break;
		case LE:
							 strcpy(oper," <= ");
							 par=0;
							 break;
		case EQ:
							 strcpy(oper," = ");
							 par=0;
							 break;
		case NE:
							 strcpy(oper," <> ");
							 par=0;
							 break;
				 case ABS:
				 case SENSOR_ON:
				 case SENSOR_OFF:
				 case INT:
				 case INTERVAL:
				 case LN:
				 case LN_1:
				 case SQR:
				 case Status:
				 case RUNTIME:
							 par=0;
								strcpy(op1,look_func(*(code-1)));
								strcat(op1,"( ");
								strcat(op1,pop());
								ind_par--;
								strcat(op1," )");
								push(op1);
								stack_par[ind_par++]=0;
								if (*(code-1) == INTERVAL || *(code-1) == TIME_ON || *(code-1) == TIME_OFF )
									 {
										if (*(code-1) == TIME_ON || *(code-1) == TIME_OFF )
//											if ( ind_line_array && line_array[ind_line_array-1][0]!=line)
											 {
												line_array[ind_line_array][0] = (unsigned int)((long)FP_SEG(code)*16+(long)FP_OFF(code)-(long)(FP_SEG(pcode)*16+(long)FP_OFF(pcode)) + 2);
												memcpy(&line_array[ind_line_array++][1],code-3,2);
											 }
										code += 4;
									 }
								break;
				 case TIME_ON:
				 case TIME_OFF:
							 char *oldcode, *oldbuf;
							 par=0;
							 strcpy(op1,look_func(*(code-1)));
							 strcat(op1,"( ");
							 oldcode = code;
							 oldbuf = buf;
							 code = ptimebuf+ *((int *)code);
							 code -= 3;
							 while( *code != 0xff && code >= ptimebuf)
								 code--;
							 if (code < ptimebuf) code = ptimebuf;
							 else code += 6;
							 buf = op2;
							 desexpr();
							 buf = oldbuf;
							 code = oldcode;
							 strcat(op1,op2);
							 strcat(op1," )");
							 push(op1);
							 stack_par[ind_par++]=0;
							 if (*(code-1) == INTERVAL || *(code-1) == TIME_ON || *(code-1) == TIME_OFF )
									 {
										if (*(code-1) == TIME_ON || *(code-1) == TIME_OFF )
//											if ( ind_line_array && line_array[ind_line_array-1][0]!=line)
											 {
												line_array[ind_line_array][0] = (unsigned int)((long)FP_SEG(code)*16+(long)FP_OFF(code)-(long)(FP_SEG(pcode)*16+(long)FP_OFF(pcode)) + 2);
												memcpy(&line_array[ind_line_array++][1],code-3,2);
											 }
										code += 2;
									 }
								break;
				 case AVG:
				 case MAX:
				 case MIN:
				 case INKEYD:
				 case	OUTPUTD:
				 case CONPROP:
				 case CONRATE:
				 case CONRESET:
				 case Tbl:
				 case WR_ON:
				 case WR_OFF:
				         {
								par=0;
								if (*(code-1)==AVG || *(code-1)==MIN || *(code-1)==MAX )
								{
										 i = *(code-1);
										 n = *code++;
								}
								else
								{
										 i = *(code-1);
										 n = 2;
								}
								strcpy(op1,look_func(i));
								strcat(op1,"( ");
								op2[0]=0;
								if( *(code-1)==INKEYD )
								{
								  strcpy(op,pop());
								}
								for(int i=0;i<n;i++)
								 {
									strcpy(op,op2);
									strcpy(op2,pop());
									ind_par--;
									strcat(op2," , ");
									strcat(op2,op);
									if (i==n-1)
										{
										 strcpy(&op2[strlen(op2)-2],")");
										}
									}
								 strcat(op1,op2);
								 push(op1);
								 stack_par[ind_par++]=0;
								}
								break;
				case SUN:
				case MON:
				case TUE:
				case WED:
				case THU:
				case FRI:
				case SAT:
				case JAN:
				case FEB:
				case MAR:
				case APR:
				case MAY:
				case JUN:
				case JUL:
				case AUG:
				case SEP:
				case OCT:
				case NOV:
				case DEC:
				case DOM:
				case DOW:
				case DOY:
				case MOY:
				case POWER_LOSS:
				case SCANS:
				case TIME:
				case USER_A:
				case USER_B:
				case UNACK:
						 par=0;
						strcpy(op1,look_func(*(code-1)));
						push(op1);
						stack_par[ind_par++]=0;
						break;
				case ASSIGNARRAY:
						desexpr();
						buf += strlen(buf);
                  break;
				case ASSIGNARRAY_1:
				case ASSIGNARRAY_2:
						i=desvar();
						strcpy(op1,buf);
						strcat(op1,"( ");
						if(i>1)
						{
						 strcpy(op2,pop());
						 strcat(op1,pop());
						 strcat(op1," , ");
						 strcat(op1,op2);
						}
						else
						{
						 strcat(op1,pop());
//						 strcat(op2,pop());
						}
						strcat(op1," )");
						push(op1);
						break;
		default:
							par=0;
							code--;
							if(!desvar())
								{
								 strcpy(buf,pop());
								 return 1;
								}
							push(buf);
							stack_par[ind_par++]=0;
							last_oper=0;
							continue;
	}
	switch (*(code-1)) {
		case PLUS:
		case MINUS:
		case MUL:
		case DIV:
		case MOD:
		case OR:
		case AND:
		case GT:
		case GE:
		case LT:
		case LE:
		case EQ:
		case NE:
/*						 if (last_oper)
							{
							 strcpy(op,pop());
							 int i=0;
							 int test=0;
							 while( op[i++] )
										if(isdelim(op[i-1]) && op[i-1]!=' ')
											 {
											 test=1; break;
											 }
							 if (test==1)
								 {
									 strcpy(op2,"(");
									 mstrcat(op2,op);
									 mstrcat(op2,")");
								 }
							 else
									 strcpy(op2,op);

							 strcpy(op,pop());
							 i=0;
							 test=0;
							 while( op[i++] )
										if(isdelim(op[i-1]) && op[i-1]!=' ')
											 {
												test=1; break;
											 }
							 if (test==1)
								 {
									 strcpy(op1,"(");
									 mstrcat(op1,op);
									 mstrcat(op1,")");
								 }
							 else
									 strcpy(op1,op);

							 mstrcat(op1,oper);
							 mstrcat(op1,op2);
							 push(op1);
							 stack_par[ind_par++]=par;

							}
*/
/*						 if (last_oper)
							{

							 strcpy(op2,pop());
							 opar=stack_par[--ind_par];
							 strcpy(op1,pop());
							 if(!opar) opar=stack_par[--ind_par];
							 else --ind_par;
							 mstrcat(op1,oper);
							 mstrcat(op1,op2);

							 if (*(code-1)==MUL || *(code-1)==DIV)
									if(opar)
										{
										 strcpy(op,"(");
										 mstrcat(op,op1);
										 mstrcat(op,")");
										 strcpy(op1,op);
										}

							 push(op1);
							 stack_par[ind_par++]=par;
							}
						 else
*/
							{
							 opar=stack_par[--ind_par];
							 if ((*(code-1)==MUL || *(code-1)==DIV || *(code-1)==MOD || *(code-1)==MINUS) && opar)
								 {
									 strcpy(op2,"(");
									 strcat(op2,pop());
									 strcat(op2,")");
								 }
							 else
									 strcpy(op2,pop());
							 opar=stack_par[--ind_par];
							 if ((*(code-1)==MUL || *(code-1)==DIV || *(code-1)==MOD) && opar)
								 {
									 strcpy(op1,"(");
									 strcat(op1,pop());
									 strcat(op1,")");
								 }
							 else
									 strcpy(op1,pop());

							 strcat(op1,oper);
							 strcat(op1,op2);

							 push(op1);
							 stack_par[ind_par++]=par;
							 last_oper=1;
							}
							 break;
		default: break;
		}

 }
 if (*code==0xFF) code++;
 strcpy(buf,pop());
 set_semaphore_dos();
 delete op1;
 delete op2;
 delete op;
 clear_semaphore_dos();
// return pop();
}

void push(char *buf)
{
 memcpy(index_stack,buf,strlen(buf)+1);
 index_stack += strlen(buf)+1;
}

char *pop(void)
{
--index_stack;
--index_stack;
 while (*index_stack && index_stack >= stack) index_stack--;
 index_stack++;
 return(index_stack);
}

char *look_instr( char cod )
{ int i ;
 /* convert to lower case */
	 /* see if token is in table */
	 for( i = 0 ; *table[i].command ; i++ )
		if (table[i].tok==cod ) return table[i].command;
	 return "" ; /* unkown command */
}

char *look_func( char cod )
{ int i ;
 /* convert to lower case */
	 /* see if token is in table */
	 for( i = 0 ; *func_table[i].func_name ; i++ )
		if (func_table[i].tok==cod ) return func_table[i].func_name;
	 return "" ; /* unkown command */
}


