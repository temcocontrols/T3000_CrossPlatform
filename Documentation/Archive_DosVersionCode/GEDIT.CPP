#include <graphics.h>
#include <process.h>
#include <windows.h>
#include "t3000def.h"
#include "aio.h"
#include "mtkernel.h"
#include "parser.h"
#include "_msdos.h"
#include "gedit.h"
#include "t3000hlp.h"
//#include "rs485.h"

#define Srt '\`'
#define TAB 2
#define TABEDI 3
#define TABMES 4
#define ESC 27

extern void *newalloc(long size);
extern void newdelete(void *ptr);

extern char huge search_str[41];
extern char huge replace_str[41];
extern char huge deletebuf[MAX_KILL_BUF_SIZE];

extern int mode_text;
extern int networkaddress;
extern int  station_num;
extern char Station_NAME[NAME_SIZE];
extern int extended_memory;
extern XmsDes Des;
extern Panel *ptr_panel;
extern int fond_color;
extern int MAX_HEAP_BUF;
extern int renumvar;
extern char int_disk1;
extern char *prog ;
extern char token[80];
extern char tok,token_type;
extern int DORU_SYSTEM;

#ifdef NETWORK_COMM
extern NETBIOS_Presence	Netbios_state;
#endif
extern char huge *colon;

extern void clear_color(int lx, int length, int ly, int ry, char *lin_text, int bkgnd, int frgnd);
extern int sendtoprint(void);
extern int pointtotext(char *buf,Point_Net *point);
extern int print_basic(int l, byte *s);
extern char *lin_text;
extern char huge *lin_menu;
extern char huge *lin_hor;
extern char huge *lin_ver;
extern int dxscreen, dyscreen;
extern int xscreen, yscreen;
extern int get_token(void) ;
extern int comman_line(int lx, int ly, int rx, int ry, int fond_color, GEdit *edit=NULL);
extern int isdelim( char c) ;
extern int look_up_func( char *s );
extern char *ispoint(char *token,int *num_point,byte *var_type, byte *point_type, int *num_panel, int *num_net, int network=0, byte panel=0, int *netpresent=0);
extern int mgetch(int x, int y);
extern int mgetword(int x, int y, char *pword, int length = 80);
extern int ReadYesNo(int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							int bkgndrreadcolor, int readcolor, char *text, char yes='Y', char no='N', char s=0);
extern ReadWindow(int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							 int bkgndrreadcolor, int readcolor, char *text, char *buf, int width);
extern void DisplayError(int lx, int ly, int rx, int ry, char *message,int bkgnd, int frgnd, int tbkgnd, int fcolor=Black);
extern int icommand(char *buf, int from, byte panel, int network);
extern int ReadWindow2(int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							 int bkgndreadcolor, int readcolor, char *text1, char *text2,
							 char *buf1, char *buf2, int width);
extern int print_alarm_word(void);

extern char *rtrim(char *text);

void psearch(GWDialog *D);
void preplace(GWDialog *D);
int isdelimit(char c);
void infoheapprg(int x, int y);
void checkcolor(char *p,char *delim, int *statement, int *frgnd, int network, int panel);
char * intervaltotext(char *textbuf, long seconds , unsigned minutes , unsigned hours, char *c=":");
extern char huge *hhelpline;
extern char huge *loadtext;
extern char huge *savetext;
extern char huge *searchstr;
extern char huge *replstr;
char lastdelete,lastline,lastblock;
extern char _far tempbuf[65];
extern char huge *bas_text;
char sendedit;
char pword[40];
char prg_active ;

void *GEdit::operator new(size_t size)
{
 return (newalloc(size));
}
void GEdit::operator delete(void *ptr)
{
 newdelete(ptr);
}

//GEdit::GEdit(uint tx, uint ty, uint bx, uint by, uint stk, char huge *pcode, int length):GWindow(tx,ty,bx,by,stk,0)
GEdit::GEdit(int tx, int ty, int bx, int by, int stk, char *pcode, int length,
				 Str_program_point *pprg, int current_prg, int ppanel, int nnetwork)
				 :GWindow(tx,ty,bx,by,stk,0)
{
 prg_active++;
 grid=1;
 ptrprg = pprg;
 current_point_prg = current_prg;
 panel = ppanel;
 network = nnetwork;
 code = pcode;
 length_code = length;
 helpline = hhelpline;
 buf=editbuf;
 memset(editbuf,'\0',BUF_SIZE);
 memset(mesbuf,'\0',MES_SIZE);
 curloc = endloc = buf;
 ecurloc = eendloc = buf;
 beginblock = endblock = 0;
 beginline = endline = 0;
 mcurloc = mendloc = mesbuf;
 scrnx = scrny = 0;
 HIGH_MES=5;

/* asm {
		mov al,0edh
		out 64h,al
		mov cx,4000h
		}
delay:  asm  loop delay
//		for(int i=0;i<_CX;i++);
	asm {
		mov al,04h
		out 64h,al
	 }
//		outp(0x64,4);
//		outp(0x60,4);

 char *p=(char *)MK_FP(0,0x417);
 *p |= 0x40;
*/
 endloc=eendloc=desassembler_program();
 buf = editbuf;
 code = pcode;
 sendedit=0;
 lastdelete=lastline=lastblock=0;
 memset(search_str,' ',40);
 search_str[40]=0;
 memset(replace_str,' ',40);
 replace_str[40]=0;
 deleteline[0]=0;
};

void GEdit::GEditSet(char far *titl, uint clr, uint tclr)
{
 LINE_LEN = bx-tx;
 MAX_LINES = by-ty-HIGH_MES;
 KILL_BUF_SIZE= 4*LINE_LEN;
 mty=0;mby=HIGH_MES+1;
 editt = 1;
 message=0;
 scrnx = scrny = 0;
 display_scrn_file(editbuf);
 beginscreen = curloc;
	ed.top.x=tx;
	ed.top.y=ty;
	ed.bot.x=bx;
	ed.bot.y=by-HIGH_MES;

	mes.top.x=tx;
	mes.top.y=by-HIGH_MES+1;
	mes.bot.x=bx;
	mes.bot.y=by;

	hsave.top.x=tx+45;
	hsave.top.y=ltop.y+1;
	hsave.bot.x=tx+56;
	hsave.bot.y=ltop.y+1;

	hload.top.x=tx+31;
	hload.top.y=ltop.y+1;
	hload.bot.x=tx+42;
	hload.bot.y=ltop.y+1;

	hcompile.top.x=tx+1;
	hcompile.top.y=ltop.y+1;
	hcompile.bot.x=tx+7;
	hcompile.bot.y=ltop.y+1;

	hclear.top.x=tx+10;
	hclear.top.y=ltop.y+1;
	hclear.bot.x=tx+17;
	hclear.bot.y=ltop.y+1;

	hprint.top.x=tx+20;
	hprint.top.y=ltop.y+1;
	hprint.bot.x=tx+27;
	hprint.bot.y=ltop.y+1;

	ctrll.top.x=1;
	ctrll.top.y=25;
	ctrll.bot.x=6;
	ctrll.bot.y=25;

	ctrlu.top.x=8;
	ctrlu.top.y=25;
	ctrlu.bot.x=15;
	ctrlu.bot.y=25;

	ctrld.top.x=17;
	ctrld.top.y=25;
	ctrld.bot.x=28;
	ctrld.bot.y=25;

	ctrly.top.x=30;
	ctrly.top.y=25;
	ctrly.bot.x=40;
	ctrly.bot.y=25;

	ctrlo.top.x=42;
	ctrlo.top.y=25;
	ctrlo.bot.x=48;
	ctrlo.bot.y=25;

	ctrlc.top.x=50;
	ctrlc.top.y=25;
	ctrlc.bot.x=56;
	ctrlc.bot.y=25;

	ctrlf.top.x=58;
	ctrlf.top.y=25;
	ctrlf.bot.x=64;
	ctrlf.bot.y=25;

	ctrln.top.x=66;
	ctrln.top.y=25;
	ctrln.bot.x=72;
	ctrln.bot.y=25;

	ctrlr.top.x=74;
	ctrlr.top.y=25;
	ctrlr.bot.x=80;
	ctrlr.bot.y=25;

	showedit(beginscreen);
};


void GEdit::showedit(char *curloc)
{
 on_screen = 0;
 GShowWindow(spot,0);
 hide_pointer();
 lin_menu[bx-tx+3]=0;
 mxyputs(tx-1,ltop.y+1,lin_menu,Lightgray,Lightgray);
 lin_menu[bx-tx+3]=lin_menu[0];

 mxyputs(tx, ltop.y+1," Send ", Lightgray, Black);
 mxyputs(tx+6,ltop.y+1,"F2  ", Lightgray, White);
 mxyputs(tx+10,ltop.y+1,"Clear ", Lightgray, Black);
 mxyputs(tx+16,ltop.y+1,"F3  ", Lightgray, White);
 mxyputs(tx+20,ltop.y+1,"Print ", Lightgray, Black);
 mxyputs(tx+26,ltop.y+1,"F4  ", Lightgray, White);

 mxyputs(tx+31,ltop.y+1,"Load File ", Lightgray, Black);
 mxyputs(tx+41,ltop.y+1,"F5  ", Lightgray, White);
 mxyputs(tx+45,ltop.y+1,"Save File ", Lightgray, Black);
 mxyputs(tx+55,ltop.y+1,"F6  ", Lightgray, White);

 mxyputs(tx+20,ltop.y,ptrprg->description, Cyan, Black);
 mxyputs(tx+45,ltop.y,ptrprg->label, Cyan, Black);

// textcolor(White);
// textbackground(colour);

 lin_hor[LINE_LEN+2]=0;
 mxyputs(tx-1,ty+mty+MAX_LINES+1,lin_hor,bkgcolour,White);
 lin_hor[LINE_LEN+2]=lin_hor[0];

/*
 egotoxy(0,0);
 lin_text[LINE_LEN]=0;
 for(int j=0;j<MAX_LINES;j++)
 {
	egotoxy(0,j);
	mputs(lin_text,colour,White);
 }
 lin_text[LINE_LEN]=lin_text[0];
*/
 egotoxy(0,0);
// mputch(' ');
 display_scrn(0,0,curloc);
 help();
 mgotoxy(30,17);
 egotoxy(scrnx,scrny);
 infoheapprg(tx,by-HIGH_MES);
display_pointer();
}

void GEdit::GWGoto(int row, int col)
{
 uint lat,lung;

 lat  = 1;
 lung = 1;

 if((row<=nrows)&&(col<=ncols))
		mgotoxy(tx+col*lat,ty+mty+row*lung);
};

void GEdit::goedit(void)
{
			mty=0; mby=HIGH_MES+1;
			MAX_LINES = by-ty-1-HIGH_MES+1;
			scrnx=escrnx;scrny=escrny;
			buf=editbuf;
			curloc = ecurloc;endloc = eendloc;
			egotoxy(scrnx,scrny);
			editt = 1;
			message=0;
}

void GEdit::gomessage(void)
{
			mty=by-ty-HIGH_MES+2 ;mby=0;
			MAX_LINES = HIGH_MES-2;
			egotoxy(0,0);
			message = 1;
			editt=0;
			escrnx=scrnx;escrny=scrny;
			scrnx=0;scrny=0;
			buf=mesbuf;
			ecurloc = curloc;eendloc = endloc;
			curloc = mcurloc; endloc = mendloc;
}

int GEdit::clearprg(void)
{
 int ret=0;
						 if(ReadYesNo(25, 7, 58, 11, Lightgray, Darkgray, White,
													Cyan, Black, "Clear program? (Y/N): "))
						 {
						 memset(editbuf,'\0',BUF_SIZE);
						 memset(mesbuf,'\0',MES_SIZE);
						 buf=editbuf;
						 curloc = endloc = buf;
						 ecurloc = eendloc = buf;
						 beginblock = endblock = 0;
						 beginline = endline = 0;
						 mcurloc = mendloc = mesbuf;
						 scrnx = scrny = 0;
						 ret=compile();
						 egotoxy(0,0);
						 display_scrn(0,0,curloc);
						 sendedit=0;
						 }
	return ret;
 }

int GEdit::HandleEvent()
{
 if (bioskey_new(1))                //kbhit())
 {
		char c;
		if ((c=edit("x.bas"))==TAB)
		{
			 if (message) tab=TABEDI;
			 if (editt)    tab=TABMES;
		}
		else tab=0;
		if (c==ESC)
		{
			if(sendedit)
			{
						 if(ReadYesNo(25, 7, 58, 11, Lightgray, Darkgray, White,
							 Cyan, Black, "Send program? (Y/N): "))
						 {
							 compile();
						 }
			}
			GReleaseWindow();
//			mxyputs(1,25,lin_text,fond_color,Black);
//			mxyputs(1,25,lin_text,Black,Black);
			clear_color(1, 80, 25, 25, lin_text, fond_color, Black);
			prg_active--;
			return 1;
		}
 }
 print_alarm_word();

 mouse_status(stat);
 if( (stat.leftButton && mouse_inside(tx,
		 ty, bx, by-HIGH_MES) && message) || (tab==TABEDI))
	 {
		 if (editt==0)
			{
			 goedit();
			 tab=0;
			}
	 }
 if( (stat.leftButton && mouse_inside(mes.top.x,
		 mes.top.y, mes.bot.x, mes.bot.y)) || (tab==TABMES))
	 {
		if(!tab)
			 while(!get_button_released(BLEFT,stat));
		if (message==0)
			{
			 gomessage();
			 tab=0;
			}
		return 0;
	 }

 if(stat.leftButton && mouse_inside(ed.top.x,
		 ed.top.y,
		 ed.bot.x,
		 ed.bot.y) && editt)
	 {
		 while(!get_button_released(BLEFT,stat));
		 int x,y,xcur,ycur;
		 char *p;
		 xcur = stat.where.x - tx; ycur = stat.where.y-ty;
		 x = scrnx; y = scrny;
		 p =curloc;
		 while(y<MAX_LINES && *p) {
			if( x == xcur && y == ycur)
			{
			 curloc = p;
			 scrnx = xcur; scrny = ycur;
			 egotoxy(scrnx, scrny);
			 break;
			}
			switch (*p) {
			 case '\r':
				break;
			 case Srt:
			 case '\n':
				 y++;
				 x = 0;
				 break;
			 default:
				 x++;
			}
		 p++;
		 }
		 if (x!=xcur || y!=ycur)
		 {
			char *q;
			x = scrnx; y = scrny;
			q = curloc;
			p=q;
			while(y>=0 && p >= buf ) {
			if(*p=='\n') p--;
			while(*p!='\n'  && *p!=Srt && p>buf) p--;
			if(*p=='\n') {p++;}
			q = p-1;
			x=0;

			 while(*p!='\r' && *p!=Srt && p<=endloc)
			 {
				if( x == xcur && y == ycur)
				{
				 curloc = p;
				 scrnx = xcur; scrny = ycur;
				 egotoxy(scrnx, scrny);
				 break;
				}
				x++;
				p++;
			 }
			if( x == xcur && y == ycur) break;
			y--;
			p = q;
			}
		 }
		return 0;
		}

 if(stat.leftButton)
 {
 if(mouse_inside(hsave.top.x,
		 hsave.top.y,
		 hsave.bot.x,
		 hsave.bot.y))
		{
				 save("");
				 return 0;
		}

 if(mouse_inside(hload.top.x,
		 hload.top.y,
		 hload.bot.x,
		 hload.bot.y))
		{
				 load();
					return 0;
		}

 if(mouse_inside(hcompile.top.x,
		 hcompile.top.y,
		 hcompile.bot.x,
		 hcompile.bot.y))
		{
				if (editt==1)
				{
					if( compile()==ESC ) return ESC;
				}
				return 0;
		}

 if(mouse_inside(hclear.top.x,
		 hclear.top.y,
		 hclear.bot.x,
		 hclear.bot.y))
		{
						while(!get_button_released(BLEFT,stat));
						if (editt==1)
						{
						 clearprg();
						 return 0;
						}
		}
 if(mouse_inside(hprint.top.x,
		 hprint.top.y,
		 hprint.bot.x,
		 hprint.bot.y))
		{
				 while(!get_button_released(BLEFT,stat));
				 return 0;
		}

 if(mouse_inside(close_spot.top.x,
		 close_spot.top.y,
		 close_spot.bot.x,
		 close_spot.bot.y))
		{
			 while(!get_button_released(BLEFT,stat));
			if(sendedit)
			{
						 if(ReadYesNo(25, 7, 58, 11, Lightgray, Darkgray, White,
							 Cyan, Black, "Send program? (Y/N): "))
						 {
							 compile();
						 }
			}
			GReleaseWindow();
			mxyputs(1,25,lin_text,fond_color,Black);
			prg_active--;
			return 1;
		}

 if(mouse_inside(ctrll.top.x,
		 ctrll.top.y,
		 ctrll.bot.x,
		 ctrll.bot.y))
		{
					while(!get_button_released(BLEFT,stat));
					select_line();
					return 0;
		}
 if(mouse_inside(ctrlu.top.x,
		 ctrlu.top.y,
		 ctrlu.bot.x,
		 ctrlu.bot.y))
		{
				 while(!get_button_released(BLEFT,stat));
				 unselect_line();
				 return 0;
		}
 if(mouse_inside(ctrld.top.x,
		 ctrld.top.y,
		 ctrld.bot.x,
		 ctrld.bot.y))
		{
				 while(!get_button_released(BLEFT,stat));
				 delete_block();
				 return 0;
		}
 if(mouse_inside(ctrly.top.x,
		 ctrly.top.y,
		 ctrly.bot.x,
		 ctrly.bot.y))
		{
				 while(!get_button_released(BLEFT,stat));
				 delete_line();
				 return 0;
		}
 if(mouse_inside(ctrlo.top.x,
		 ctrlo.top.y,
		 ctrlo.bot.x,
		 ctrlo.bot.y))
		{
				 while(!get_button_released(BLEFT,stat));
				 undo();
				 return 0;
		}
 if(mouse_inside(ctrlc.top.x,
		 ctrlc.top.y,
		 ctrlc.bot.x,
		 ctrlc.bot.y))
		{
				 while(!get_button_released(BLEFT,stat));
				 insertbuf();
				 return 0;
		}
 if(mouse_inside(ctrlf.top.x,
		 ctrlf.top.y,
		 ctrlf.bot.x,
		 ctrlf.bot.y))
		{
				 while(!get_button_released(BLEFT,stat));
				 search();
				 return 0;
		}
 if(mouse_inside(ctrln.top.x,
		 ctrln.top.y,
		 ctrln.bot.x,
		 ctrln.bot.y))
		{
				 while(!get_button_released(BLEFT,stat));
				 next();
				 return 0;
		}
 if(mouse_inside(ctrlr.top.x,
		 ctrlr.top.y,
		 ctrlr.bot.x,
		 ctrlr.bot.y))
		{
				 while(!get_button_released(BLEFT,stat));
				 replace();
				 return 0;
		}

 }

 if(stat.rightButton)
 {
		 while(!get_button_released(BRIGHT,stat));
		 if(mgetword(stat.where.x, stat.where.y, pword, 40))
		 {
			icommand(pword, 0, panel, network);
			help();
		 }
 }

 return 0;
}

int GEdit::edit(char *fname)
{
 int oldcolor,ret=0;;
 oldcolor = bkgcolour;
 key.i = bioskey_new(0);
 if (!key.ch[0]) {
	 switch (key.ch[1]) {
// ***********************************
// ********      mao hui      ********
// ********  1997.8.5 NO.062  ********
// ********       begin       ********
// ***********************************
		case 	F1KEY:
				{
					char Key_word[20];
					char far *Pointer_letter;
					int Key_word_number;
					int Counter;
					Pointer_letter=curloc;
					if (_fstrchr(BORDER_LETTER,*Pointer_letter)!=NULL)
					{
						T3000help(500);
					}
					else
					{
						do
						{
							Pointer_letter--;
						}	while ((_fstrchr(BORDER_LETTER,*Pointer_letter))==NULL);
						Counter=0;
						do
						{
							Pointer_letter++;
							Key_word[Counter]=*Pointer_letter;
							Counter++;
						}	while ((_fstrchr(BORDER_LETTER,*Pointer_letter))==NULL);
						Counter--;
						Key_word[Counter]='\0';
                  Key_word_number=Key_word_convert(Key_word);
						T3000help(Key_word_number);
					}
				};
            break;
// ***********************************
// ********      mao hui      ********
// ********  1997.8.5 NO.062  ********
// ********        end        ********
// ***********************************
		case F7KEY:  //save
				 comman_line(2, 21, 79, 23, Blue, this);
				 break;
		case F6KEY:  //save
				 save("");
				 break;
		case F5KEY: //load
				 load();
				 break;
		case F4KEY: //load
				 if( strlen(editbuf) )
				 {
					byte var_type,point_type;
					int  num_point,num_net,num_panel;
					Point_Net p;
					char *ptr;
					set_semaphore_dos();
					ptr = new char[50];
					clear_semaphore_dos();
					p.putpoint(current_point_prg, PRG + 1, panel, network);
					pointtotext(ptr,&p);
					strcpy(ptr,ispoint(ptr,&num_point,&var_type, &point_type, &num_panel, &num_net));
					strcat(ptr,"\r\n----------\r\n");
					print_basic(strlen(ptr),ptr);
					print_basic(strlen(editbuf),editbuf);
					set_semaphore_dos();
					delete ptr;
					clear_semaphore_dos();
					sendtoprint();
				 }
				 break;
		case F3KEY:   //clear
				 if (editt==1)
				 {
					 clearprg();
				 }
				 break;
		case F2KEY:   //compile
				 if (editt==1)
				 {
					 ret = compile();
				 }
				 break;
		case HOME:  //home
				 home();
				 break;
		case ENDKEY:  //end
				 gotoend();
				 break;
		case LEFT:  //left
				 left();
				 break;
		case RIGHT:  //right
				 right();
				 break;
		case UP:  //up
				 upline();
				 break;
		case DOWN:  //down
				 downline();
				 break;
		case PGUP:  //page up
				 pageup();
				 break;
		case PGDN:  //page down
				 pagedown();
				 break;
		case DELETE:  //del
				 if(curloc<endloc)
				 {
					delete_char();
					sendedit=1;
				 }
				 break;
		case INSERT:  //
				 {
					int x,y;
					getxy(&x, &y);
					if(mgetword(x, y, pword, 40))
					{
					 icommand(pword, 0, panel, network);
					 help();
					}
				 }
				 break;
		}
		if (curloc < buf) {
				scrnx = scrny = 0;
				curloc = buf;
		}
		egotoxy(scrnx,scrny);
	 }
	 else {
		switch (key.ch[0]) {
			case '\r': //CR
						 if (endloc>=buf+BUF_SIZE-3) break;
						 memmove(curloc+2, curloc, endloc-curloc+1);
						 *curloc++ = key.ch[0];
						 *curloc++ = 0x0a;
						 checkblock(curloc, 2);
						 edit_clr_eol(scrnx,scrny);
						 scrnx = 0;
						 scrny++;
						 if(scrny==MAX_LINES) {
							 scrny=MAX_LINES-1;
							 escrollup(0,0,LINE_LEN,scrny);
						 }
						 else scrolldn(scrnx,scrny);

						 if( !scrnx && !scrny)
								beginscreen = curloc;
						 egotoxy(scrnx,scrny);
						 endloc += 2;
						 checkline();
						 printline(curloc);
						 sendedit=1;
						 break;
			case '\b': //BS
						 if(curloc==buf) break;
						 left();
						 delete_char();
						 sendedit=1;
						 break;
			case 4: //CTRL-D delete block
						 delete_block();
						 break;
//			case 22: //CTRL-V insert delete buffer
			case 3:    // ctrl/C
						 insertbuf();
						 break;
			case 6:   //search
						 search();
						 break;
			case 18:   //search
						 replace();
						 break;
			case 14:   //search
						 next();
						 break;
			case 7:   //search
						 gotoline();
						 break;
			case 5:   //search
						 if (editt==1)
						 {
							renumvar=1;
							ret = compile();
							renumvar=0;
						 }
						 break;
			case 12:   //CTRL-L
						 select_line();
						 break;
			case 21:   //CTRL-U
						 unselect_line();
						 break;
			case 15: // ^O
						 undo();
						 break;
			case 25: // ^Y
						delete_line();
						break;
			case 27: //ESC
			case 26: //CTRL-Z
						 return ESC;
			case 9:
							return TAB;
			default:
						 insertchar(key.ch[0]);
						 sendedit=1;
		 }
		 egotoxy(scrnx,scrny);
	 }
// } while(key.ch[0]!=26);  //CTRL-Z
	return ret;
}

void GEdit::checkline(void)
{
 char *p,*q, *dis;
 p = q = curloc;
 if( *curloc==Srt ) q--;
 while(*q!='\n' && *q!=Srt && q>buf) q--;
 if(*q=='\n'|| *q==Srt ) q++;
 dis = q;
 while(*p != '\r' && *p != 0)
 {
  if(*p == Srt)
  {
	 memmove(p, p+1, endloc-p);
	 endloc -= 1;
	 checkblock(p, -1);
  }
  else p++;
 }
 if(p-q>LINE_LEN)
 {
 int i;
 i=0;
 p = q;
 while(p<=endloc && *p!='\r' && *p!=0) {
	 if(i<LINE_LEN)
	 {
		i++;
		p++;
	 }
	 else
	 {
		 if (endloc>=buf+BUF_SIZE-2) continue;
		 edit_clr_eol(i, scrny);
		 memmove(p+1, p, endloc-p+1);
		 *p = Srt;
		 p++;
		 endloc += 1;
		 if(curloc >= p-1)
		 {
		  q = p;
		  curloc += 1;
		  scrnx=0; scrny++;
		  while(q<=endloc && q<curloc)
		  {
			scrnx++;
			q++;
		  }
        dis = p;
		  clrscr(scrny);
		 }
		 checkblock(p, 1);
		 i=0;
	 }
  }
 }
 display_scrn(0, scrny, dis);
 egotoxy(scrnx,scrny);
}

void GEdit::insertchar(char ch)
{
	int oldcolor=bkgcolour;
						 if (endloc>=buf+BUF_SIZE-2) return;
/*						 if(scrnx==LINE_LEN)
						 {
							 int i=0;
							 if (endloc==buf+BUF_SIZE-5) break;
							 while(*curloc!=' ' && curloc>buf)
								 {
									curloc--;
									i++;
									moutchar(--scrnx+tx, scrny+ty+mty,' ',colour,White);
								 }
							 memmove(curloc+4, curloc, endloc-curloc+1);
							 *curloc = Srt; *(curloc+1) = *(curloc+2) = *(curloc+3) = ' ';
							 endloc += 4;

						 if(beginblock!=endblock)
							 {
								if(curloc <= beginblock)
								{
								 beginblock += 4;
								 endblock += 4;
								}
								else
								 if(curloc < endblock)
									 if(!lastblock)
										 endblock += 4;
							 }

							 curloc++;
							 scrnx = 0;
							 scrny++;
							 if(scrny==MAX_LINES) {
								 scrny=MAX_LINES-1;
								 escrollup(0,0,LINE_LEN,scrny);
							 }
							 else scrolldn(scrnx,scrny);
//							 endloc++;
							 egotoxy(scrnx,scrny);
							 printline(curloc);
							 scrnx = 3 + i;
							 curloc += i + 3;
						 }
*/
						 memmove(curloc+1, curloc, endloc-curloc+1);
						 *curloc = ch;
						 if( curloc >= beginblock && curloc < endblock && !lastblock)
							 bkgcolour = Cyan;
						 moutchar(scrnx+tx, scrny+ty+mty,*curloc,bkgcolour,White);
						 bkgcolour=oldcolor;
//						 mputch(*curloc);
						 scrnx++;
						 egotoxy(scrnx,scrny);
						 curloc++;
						 endloc++;
						 checkline();
						 printline(curloc);
						 checkblock(curloc, 1);
}

void GEdit::left(void)
{
 if(curloc==buf) return;
 scrnx--;
 if(scrnx < 0) {
	 scrnx = 0;
	 upline();

	 while( *curloc!='\r' && *curloc!=Srt && *curloc ) {
		 curloc++;
		 scrnx++;
	}
 }
 else
			{
			 if (*curloc=='\n')
					curloc--;
			 curloc--;
			}
}

void GEdit::right(void)
{
 if (curloc+1 > endloc) return;
 scrnx++;
 if (scrnx > LINE_LEN || *curloc == '\r' || *curloc==Srt) {
		scrnx = 0;
		scrny++;
		if (scrny==MAX_LINES) {
			scrny = MAX_LINES-1;
			downline();
			curloc--;
			while(*curloc!='\r' && *curloc!=Srt && curloc>buf ) curloc--;
			if(*curloc=='\r')
				curloc+=2;
			if(*curloc==Srt)
				curloc++;
			scrnx = 0;
		 }
		 else
			{
			 if (*curloc=='\r')
					curloc++;
			 curloc++;
			}
	}
	else curloc++;
}

void GEdit::upline(void)
{
 int i;
 char *p;
 if(curloc==buf) return;
 p=curloc;
 if(*p=='\r' || *p==Srt) p--;
 for(;*p!='\r'  && *p!=Srt && p>buf; p--);
 if(*p!='\r' && *p!=Srt) return;
 curloc =p;
 curloc--;
 i= scrnx;
 while(*curloc!='\r'  && *curloc!=Srt && curloc>buf) curloc--;
 scrny--; scrnx = 0;
 if (*curloc=='\r')
	 curloc+=2;
 if (*curloc==Srt)
	 curloc++;
 if(scrny<0) {
	 scrolldn(0,0);
	 scrny = 0;
	 egotoxy(0,0);
	 printline(curloc);
	 beginscreen = curloc;
 }
 while(i && *curloc!='\r' && *curloc!=Srt) {
	 curloc++;
	 scrnx++;
	 i--;
 }
}

void GEdit::downline(void)
{
 int i;
 char *p;

 i=scrnx;
 p=curloc;
 while(*p!='\r' && *p!=Srt && p<endloc) p++;
// while(*p!='\r' && p<endloc)
// {
//	if(*p == Srt) scrny++;
//	p++;
// }
 if(p==endloc) return;
 if (*p=='\r')
	 p++;
 p++;
 curloc=p;
 scrny++; scrnx=0;
 if(scrny==MAX_LINES) {
	 scrny = MAX_LINES-1;
	 escrollup(0,0,LINE_LEN, MAX_LINES);
	 egotoxy(scrnx,scrny);
	 printline(curloc);
	 while(*beginscreen!='\n' && *beginscreen!=Srt && beginscreen<endloc) beginscreen++;
	 if (*beginscreen=='\n' || *beginscreen==Srt) beginscreen++;
 }

 while(i && *curloc!='\r' && *curloc!=Srt && curloc<endloc) {
	 curloc++;
	 scrnx++;
	 i--;
 }
}

void GEdit::checkblock(char *p, int i)
{
	 if(beginblock!=endblock)
	 {
		if(p <= beginblock)
		{
		 beginblock += i;
		 endblock += i;
		}
		else
		 if(p < endblock)
			 if(!lastblock)
				 endblock += i;
	 }
}

void GEdit::delete_char(void)
{
 int i=1;
 egotoxy(scrnx,scrny);
// if(*curloc==Srt) return;
 if(*curloc=='\r' || *curloc==Srt)
 {
	escrollup(0,scrny+1, LINE_LEN, MAX_LINES-1);
	if(*curloc==Srt)
		i=1;
	else
		i=2;
	memmove(curloc, curloc+i, endloc-curloc-(i-1));
	endloc -= i;
	checkblock(curloc, -i);
	checkline();
	display_scrn(scrnx, scrny, curloc);
 }
 else
 {
	memmove(curloc, curloc+1, endloc-curloc);
	endloc--;
	checkblock(curloc, -1);
	if( (*curloc=='\r' || !(*curloc)) && *(curloc-1)==Srt )
	{
	 escrollup(0,scrny+1, LINE_LEN, MAX_LINES-1);
	 memmove(curloc-1, curloc, endloc-curloc+1);
	 endloc -= 1;
	 if(*curloc=='\n')
		  curloc++;
	 checkline();
	 display_scrn(scrnx, scrny, curloc);
	}
	else
	 if( *curloc==Srt)
	 {
	  escrollup(0,scrny+1, LINE_LEN, MAX_LINES-1);
	  memmove(curloc, curloc+1, endloc-curloc);
	  endloc -= 1;
	  checkblock(curloc, -1);
	  checkline();
	  display_scrn(scrnx, scrny, curloc);
	 }
	checkline();
	printline(curloc);
//	 printf(" ");
 }
}


/*
void GEdit::delete_line(void)
{
 int i;
 char *p, *deletebufptr;
 if(*curloc=='\r' || *curloc==Srt) {
	if(*curloc=='\r') delete_char();
	delete_char();
	return;


 }

 edit_clr_eol(scrnx,scrny);
 p=curloc;
 i=0;
 deletebufptr = deletebuf;
 while(*p!='\r' && *p!=Srt &&p<endloc) {
	i++;
	*deletebufptr = *p;
	p++;
	if(deletebufptr<deletebuf+KILL_BUF_SIZE-2) deletebufptr++;
 }
 *deletebufptr = '\0';
 memmove(curloc, curloc+i, endloc-curloc);
 endloc -= i;

}
*/
void GEdit::undo(void)
{
						 if(lastdelete)
						 {
							if( lastdelete==1 )
							{
							 lookbegin(beginline,endline,deleteline);
							 lastline = 0;
							 lastdelete = lastblock;
							 if(endline < beginblock )
								{
								 endblock += endline-beginline;
								 beginblock += endline-beginline;
								}
							 else
								 if(beginline <= endblock)
										endblock += endline-beginline;

							 beginline = endline = 0;
							 scrnx = 0;
							 display_scrn(scrnx, scrny, curloc);
							}
							else
							if( lastdelete==2 )
							{
							 lookbegin(beginblock,endblock,deletebuf);
							 lastblock = 0;
							 lastdelete = lastline;
							 display_scrn(scrnx, scrny, curloc);
							}
						 sendedit=1;
						 }
}

void GEdit::delete_line(void)
{
						 char *q;
						 int i;
						 if(*curloc=='\n') curloc--;
						 while(*curloc!='\n' && curloc>buf)
						 {
							if(*curloc==Srt) scrny--;
							curloc--;
						 }
						 if(*curloc=='\n') curloc++;
						 q = curloc;
						 while(*q!='\n' && q<endloc) q++;
						 if(*q=='\n') { q++;}
						 endline=q;
						 beginline=curloc;
						 i = endline-beginline;
						 if( i < MAX_LINE_SIZE )
						 {
						  memmove(deleteline, beginline, i);
						  deleteline[i]=0;
						 }
						 else
						 {
						  memmove(deleteline, beginline, MAX_LINE_SIZE-3);
						  deleteline[MAX_LINE_SIZE-3] = 0x0d;
						  deleteline[MAX_LINE_SIZE-2] = 0x0a;
						  deleteline[MAX_LINE_SIZE-1] = 0;
						 }
						 memmove(beginline, endline, endloc-endline+1);
						 endloc -= i;
						 if(endline < beginblock )
						 {
							 endblock -= i;
							 beginblock -= i;
						 }
						 else
						 if(beginline >= beginblock && endline <= endblock)
							 endblock -= i;
						 lastdelete = 1;
						 lastline = 1;
						 scrnx = 0;
						 display_scrn(scrnx, scrny, curloc);
						 sendedit=1;
						 if( i >= MAX_LINE_SIZE )
						   endline=beginline+MAX_LINE_SIZE-1;

}

void GEdit::delete_block(void)
{
 int i;
 if (beginblock!=endblock && !lastblock)
 {
  i=endblock-beginblock;
  if( i < MAX_KILL_BUF_SIZE-1 )
  {
	if(curloc<beginblock)
	 while(curloc!=beginblock)
		{
		 right();
//		 egotoxy(scrnx,scrny);
		}

	if(curloc>beginblock)
	 while(curloc!=beginblock)
		 {
		 left();
//		 egotoxy(scrnx,scrny);
		}
	memmove(deletebuf, curloc, i);
	deletebuf[i] = 0;
	memmove(curloc, curloc+i, endloc-endblock+1);
	endloc -= i;
	lastblock = 2;
	lastdelete = 2;
	checkline();
	display_scrn(scrnx, scrny, curloc);
	sendedit=1;
  }
  else
  {
	DisplayError(25, 7, 55, 14, "Enough memory.Block to big!",Lightgray, Lightred, Red);
  }
 }
}

void GEdit::select_line(void)
{
 int i,j,oldcolor;
 char x,y,*p, *q;
 j=0;
 p=curloc;
// q=curloc;
 if(*p=='\n') p--;
// if(*curloc=='\r' || *curloc==Srt || curloc==endloc) {
//	return;
// }
 x=scrnx;y=scrny;
// while(*p!='\n'  && *p!=Srt && p>=buf) p--;
 while(*p!='\n'  &&  p>buf)
	{
	 if(*p == Srt) scrny--;
	 p--;
	}
 if(*p=='\n') {p++;}
 curloc = p;
 q = p;
// while(*q!='\n'  && *q!=Srt && q<endloc) q++;
 while(*q!='\n'  &&  q<=endloc)
 {
	q++;
 }
 if(*q == '\n') { q++;}

 if(lastblock)
 {
	beginblock=p;
	endblock=q;
 }
 else
 {
	if(p>endblock || q<beginblock) {beginblock=p;endblock=q;}
	if(p==endblock) {endblock=q;}
	if(q==beginblock) {beginblock=p;}
 }
// textbackground(CYAN);
 lastblock = 0;
 lastdelete = lastline;
 oldcolor = bkgcolour;
 bkgcolour = CYAN;
 scrnx=0;
 printline(p);
 bkgcolour = oldcolor;
// textbackground(colour);
 scrnx = 0;
 downline();
 egotoxy(scrnx,scrny);
}

void GEdit::lookbegin(char *begin, char *end,char *pbuf)
{
 int i;
 char *p;
 p=curloc;
 if (begin!=end)
 {
	i=end-begin;
	if(curloc<begin)
	 while(curloc!=begin)
		{
		 right();
//		 egotoxy(scrnx,scrny);
		}

	if(curloc>begin)
	 while(curloc!=begin)
		 {
		 left();
//		 egotoxy(scrnx,scrny);
		}
	if (endloc+i<buf+BUF_SIZE-1)
	{
	 memmove( curloc+i, curloc, endloc-curloc+1);
	 memmove( curloc, pbuf, i);
	 endloc += i;
	}
 }
}

void GEdit::unselect_line(void)
{
 int i;
 char *p;
 p=curloc;
 if (beginblock!=endblock)
 {
 i=endblock-beginblock;
 if(curloc<beginblock)
	 while(curloc!=beginblock)
		{
		 right();
		 egotoxy(scrnx,scrny);
		}

 if(curloc>beginblock)
	 while(curloc!=beginblock)
		 {
		 left();
		 egotoxy(scrnx,scrny);
		}

 endblock=beginblock;
 display_scrn(scrnx, scrny, curloc);
 }
}

void GEdit::insertbuf(void)
{
/*char *p;
p=beginbuf;
while(p<endblock) {
 memmove(curloc+1, curloc, endloc-curloc+1);
 *curloc = *p;
 if(scrnx<LINE_LEN) {
	 putch(*curloc);
	 scrnx++;
 }
 curloc++;
 endloc++;
 p++;
}
printline(curloc);
*/
 if( curloc>beginblock && curloc<endblock && !lastblock)
		return;
 int i=endblock-beginblock;
 if (i)
  if( endloc+i<buf+BUF_SIZE-1 )
  {
	memmove(curloc+i, curloc, endloc-curloc+1);
	if(curloc<=beginblock)
	 {
		beginblock += i;
		endblock += i;
	 }
	if(lastblock)
		memmove(curloc, deletebuf, i);
	else
		memmove(curloc, beginblock, i);
	endloc += i;
	display_scrn(scrnx, scrny, curloc);
	sendedit=1;
  }
  else
	DisplayError(25, 7, 55, 14, "Enough memory.Program to big!",Lightgray, Lightred, Red);
}

void GEdit::search(void)
{
 int i,x,y;
 getxy(&x, &y);
 search_str[0]=0;
 mgetword(x, y, search_str, 41);
 GWDialog *D = new GWDialog(8,8,74,11,NO_STACK,0);
 D->exitCR = 1;
 D->GWSet("",Lightgray,Darkgray);
 D->GShowWindow(DIALOG);
 D->GWPuts(1,2,searchstr,Lightgray,Black);
 D->GDDef_object(NULL,19,1,40,Cyan,Black, search_str, Cyan, White);
 while(!(i=D->HandleEvent()));
 delete D;
 egotoxy(scrnx,scrny);

 if(i==1 || !strlen(rtrim(search_str))) return;
 next();
}

void GEdit::gotoline(void)
{
clrline(MAX_LINES+2);
egotoxy(0,MAX_LINES+2);
mputs("line number: ");
egotoxy(16,MAX_LINES+2);
edit_gets(search_str);
clrline(MAX_LINES+2);
if(!search_str[0]) return;
next();
}

int GEdit::next(void)
{
char *p;
int len,i;
if(!strlen(rtrim(search_str))) return 0;
p=curloc+1;
len=strlen(search_str);

while(p<endloc && strncmp(search_str, p, len)) p++;
if(p>=endloc) return 0;

i=0;
while(p>buf && *p!='\n' && *p!=Srt) {
 p--;
 i++;
}
if(*p=='\n' || *p==Srt)
{
 p++;
 i--;
}

curloc = p+i;
scrnx=i;
scrny=0;

clrscr(0);
display_scrn(0,0,p);
egotoxy(scrnx,scrny);
return 1;
//help();
}

void GEdit::edit_gets(char *str)
{
 mgets(str,1,bkgcolour,White);
}

void GEdit::replace(void)
{
 int i,x,y;
/*
 GWDialog *D = new GWDialog(8,8,74,12,NO_STACK,0);
 D->exitCR = 1;
 D->GWSet("",Lightgray,Darkgray);
 D->GShowWindow(DIALOG);
 getxy(&x, &y);
 D->GWPuts(1,2,searchstr,Lightgray,Black);
 D->GWPuts(2,2,replstr,Lightgray,Black);
 search_str[0]=0;
 mgetword(x, y, search_str);
 D->GDDef_object(NULL,19,1,40,Cyan,Black, search_str, Cyan, White);
 D->GDDef_object(NULL,19,2,40,Cyan,Black, replace_str, Cyan, White);
 while(!(i=D->HandleEvent()));
 delete D;
*/
 getxy(&x, &y);
 search_str[0]=0;
 mgetword(x, y, search_str, 41);
 i=ReadWindow2(8, 8, 74, 12, Lightgray, Darkgray, Black,
							 Cyan, Black, searchstr, replstr,
							 search_str, replace_str, 40);

 egotoxy(scrnx,scrny);
 if(i==1 || !strlen(rtrim(search_str)) || !strlen(rtrim(replace_str)) ) return;

 while(next())
 {
	i=0;
	while(search_str[i++]) delete_char();
	i=0;
	while(replace_str[i]) insertchar(replace_str[i++]);
 }
 sendedit=1;
}

void GEdit::scrolldn(int x,int y)
{
// union REGS r;

  asm {
  push ax
  push bx
  push cx
  push dx
  }
 _CH = y+ty+mty-1;
 _CL = x+tx-1;
 asm push cx
 _DH = by-mby-1;
 _DL = bx-1;
 asm push dx
 _BH = bkgcolour*16;
 asm {
  pop dx
  pop cx
 }
 asm {
  mov ah,7
  mov al,1
  int 10h
 }
  asm {
  pop dx
  pop cx
  pop bx
  pop ax
  }
/*
 r.h.ah = 7;
 r.h.al = 1;
 r.h.ch = y+ty+mty-1;
 r.h.cl = x+tx-1;
 r.h.dh = by-mby-1;
 r.h.dl = bx-1;
 r.h.bh = colour*16;
 int86(0x10, &r, &r);
*/
}

void GEdit::escrollup(int topx, int topy, int endx, int endy)
{
// union REGS r;

  asm {
  push ax
  push bx
  push cx
  push dx
  }
 _CH = topy+ty+mty-1;;
 _CL = topx+tx-1;
 asm push cx
 _DH = endy+ty+mty-1;
 _DL = endx+tx-1;
 asm push dx
 _BH = bkgcolour*16+Lightgray;
 asm {
  pop dx
  pop cx
 }
 asm {
  mov ah,6
  mov al,1
  int 10h
 }
  asm {
  pop dx
  pop cx
  pop bx
  pop ax
  }
/*
 r.h.ah = 6;
 r.h.al = 1;
 r.h.ch = topy+ty+mty-1;
 r.h.cl = topx+tx-1;
 r.h.dh = endy+ty+mty-1;
 r.h.dl = endx+tx-1;
 r.h.bh = colour*16+Lightgray;
 int86(0x10, &r, &r);
*/
}

void GEdit::printline(char *p)
{
 char delim=2;
 int  statement=0;
 int i,y,frgnd=White;
 i=scrnx;
 int oldcolor = bkgcolour;
 if( p >= beginblock && p < endblock && !lastblock)
	 bkgcolour = Cyan;
 if(scrnx)
 {
	if(mode_text)
	{
	 asm {
		mov ah,08
		mov bh,0
		int 10h
	 }
	 frgnd=_AH&0x0F;
	 delim=1;
	}
 }
 while(*p!='\r'  && *p!=Srt && *p && i<LINE_LEN) {
//	 mputch(*p);
//				 mgotoxy(tx,y+ty+mty);
	 checkcolor(p,&delim,&statement,&frgnd,network,panel);
	 moutchar(i+tx , scrny+ty+mty , *p, bkgcolour, frgnd);
	 p++;
	 i++;
 }
 y=scrny+1;
 while( *p++==Srt && y<MAX_LINES )
 {
	 if(*(p-1)==Srt) i=0;
	 while(*p!='\r'  && *p!=Srt && *p && i<LINE_LEN)
	 {
		 checkcolor(p,&delim,&statement,&frgnd,network,panel);
		 moutchar(i+tx , y+ty+mty , *p, bkgcolour, frgnd);
		 p++;
		 i++;
	 }
	 y++;
 }
 y--;
 if(i<LINE_LEN)
	{
	 if((char)mgetch(i+tx , y+ty+mty)!=' ')
		 moutchar(i+tx , y+ty+mty , ' ', bkgcolour, frgnd);
	}
 bkgcolour = oldcolor;
}

void GEdit::help(void)
{
// window(1,1,80,25);
// char hline[] = " CTRL/L        CTRL/U         	CTRL/D        CTRL/V      CTRL/F      ESC        ";
// textbackground(Lightgray);
//"^L seL ^U Unsel ^D Del block ^Y Del line ^O undO ^C Copy ^F Find ^N Next ^G Goto";
 mxyputs(1,25,helpline,Lightgray,White);
 mxyputs(1,25,"^L",Lightgray,Black);
 mxyputs(8,25,"^U",Lightgray,Black);
 mxyputs(17,25,"^D",Lightgray,Black);
 mxyputs(30,25,"^Y",Lightgray,Black);
 mxyputs(42,25,"^O",Lightgray,Black);
 mxyputs(50,25,"^C",Lightgray,Black);
 mxyputs(58,25,"^F",Lightgray,Black);
 mxyputs(66,25,"^N",Lightgray,Black);
 mxyputs(74,25,"^R",Lightgray,Black);
// textcolor(White);
// window(e.GWRetLimits(4),e.GWRetLimits(5),e.GWRetLimits(6),e.GWRetLimits(7));
// textbackground(colour);

}

void GEdit::display_scrn_file(char *p)
{
 int i;
 i=0;
 while(p<=endloc && *p) {
	 switch (*p) {
		 case '\r': break;
		 case Srt:
		 case '\n':
				 i=0;
				 break;
		 default:
				 if(i<LINE_LEN)
					 {
						i++;
					 }
				 else
					{
/*
					 if (endloc==buf+BUF_SIZE-5) continue;
					 while(*p!=' ' && p>buf)
							p--;
					 memmove(p+4, p, endloc-p+1);
					 *p = Srt; *(p+1) = *(p+2) = *(p+3) = ' ';
					 endloc += 4;
					 continue;
*/
					 if (endloc+1>=buf+BUF_SIZE-2) break;
					 memmove(p+1, p, endloc-p+1);
					 *p = Srt;
					 endloc += 1;
					 continue;
					}
		 }
		 p++;
 }
}

void checkcolor(char *p,char *delim, int *statement, int *frgnd, int network, int panel)
{
 char *label;
 byte point_type,var_type;
 int num_point,num_panel,num_net,i,x1,y1;

	 if(*delim==2)
	 {
		prog = p;
		get_token();
		*delim=1;
		if(token_type==IDENTIFIER)
		{
		 if( !look_up_func(token) )
		 {
			label=ispoint(token,&num_point,&var_type,&point_type,&num_panel,&num_net,network,panel);
			if(!label)
			{             // local var
			 *frgnd=Yellow;
			}
		 }
		}
		else
		{
		 if(token_type==KEYWORD)
		 {
			 switch(tok) {
				 case REM:
					 *delim=3;
					 break;
				 case DALARM:
					 *statement = DALARM;
					 break;
			 }
		 }
		}
	 }
	 if( isdelim(*p) )
	 {
		 if( *statement == DALARM )
		 {
			 if ( *p == ',' )
			 {
				 *delim=3;
			 }
		 }
		 if( *delim!=3 )
		 {
			*delim=2;
		 }
		 *frgnd=White;
	 }
}

void GEdit::display_scrn(int x, int y, char *p, char type)
{
 char isdel=1,delim=2;
 int statement=0;
 int i,x1,y1;
 int frgnd=White, oldcolor = bkgcolour;
// j=y;
 x1=x; y1=y;
 if(!x)
	clrscr(y);
// while(j<MAX_LINES) edit_clr_eol(0,j++);
 egotoxy(x,y);
 i=x;
 if(x)
 {
	if(mode_text)
	{
	 asm {
		mov ah,08
		mov bh,0
		int 10h
	 }
	 frgnd=_AH&0x0F;
	 delim=1;
	}
 }
 if( p+1 >= beginblock && p+1 < endblock && !lastblock)
	 bkgcolour = Cyan;
 while(y<MAX_LINES && *p) {
	 if(!type)
	 {
		 if( isdelim(*p) )
		 {
			isdel=1;
		 }
		 if( isdel<=2 )
			 checkcolor(p,&delim,&statement,&frgnd,network,panel);
		 if( isdel>=1 ) isdel++;
	 }
	 switch (*p) {
		 case '\r':
				bkgcolour = oldcolor;
				delim=2;
				frgnd=White;
				statement=0;
				isdel=1;
				break;
		 case Srt:
		 case '\n':
//		  cprintf("\n");
				 edit_clr_eol(i,y);
				 y++;
				 mgotoxy(tx,y+ty+mty);
				 i=0;
				 if( p+1 >= beginblock && p+1 < endblock && !lastblock)
					 bkgcolour = Cyan;
				 delim=2;
				 frgnd=White;
				 statement=0;
				 isdel=1;
				 break;
		 default:
				 if(i<LINE_LEN)
					 {
						moutchar(i+tx, y+ty+mty, *p, bkgcolour, frgnd);
						i++;
					 }
/*
				 else
					{
					 if (endloc==buf+BUF_SIZE-2) continue;
					 while(*p!=' ' && p>buf)
						 {
							p--;
							moutchar(--i+tx, y+ty+mty,' ',colour,White);
						 }
					 memmove(p+1, p, endloc-p+1);
					 *p = Srt;
					 endloc++;
					 continue;
					}
*/
		 }
		 p++;
 }
 bkgcolour = oldcolor;
 egotoxy(x1,y1);
}

void GEdit::home(void)
{
/*
 clrscr(0);
 curloc = buf;
 scrnx = scrny = 0;
 display_scrn(0,0,curloc);
// help();
*/
 char *p;
 p=curloc;
 if(*p=='\n' || *p==Srt) p--;
 while(*p!='\n'  && *p!=Srt && p>buf) p--;
 if(*p=='\n' || *p==Srt) {p++;}
 curloc = p;
 scrnx=0;
 egotoxy(scrnx,scrny);
}

void GEdit::gotoend(void)
{
 char *q;
 q=curloc;
 while(*q!='\r'  && *q!=Srt && q<=endloc)
 {
	q++;
	scrnx++;
 }
 egotoxy(scrnx,scrny);
 curloc=q;
/*
 clrscr(0);
 curloc=endloc;
 pageup();
*/
}

void GEdit::cursor_pos(void)
{
// union REGS i,o;
  asm {
  push ax
  push bx
  }
 asm {
  mov bh,0
  mov ah,3
  int 16h
 }
	asm {
  pop bx
  pop ax
  }
/*
 i.h.bh = 0;
 i.h.ah = 3;
 int86(16,&i,&o);
*/
}

void GEdit::egotoxy(int x, int y)
{
/* union REGS i;
 i.h.dh = y +  e.GWRetLimits(5);
 i.h.dl = x +  e.GWRetLimits(4);
 i.h.ah = 2;
 i.h.bh = 0;
 int86(16,&i,&i);
*/
 mgotoxy(x+tx,y+ty+mty);
}

void GEdit::clrline(int y)
{
 int i;
 egotoxy(0,y);
 for(i=0;i<LINE_LEN;i++)
	 moutchar(tx+i, y+ty+mty,' ',bkgcolour,White);
//   mputch(' ');
}

void GEdit::edit_clr_eol(int x, int y)
{
 char *p;
// p=curloc;
 egotoxy(x,y);
 for(;x<=LINE_LEN; x++) {
	 moutchar(x+tx, y+ty+mty,' ',bkgcolour,White);
//	 printf(" ");
 }
}

void GEdit::clrscr(int y)
{
// union REGS r;

  asm {
  push ax
  push bx
  push cx
  push dx
  }
 _CH = ty+mty-1+y;
 _CL = tx-1;
 asm push cx
 _DH = by-mby-1;
 _DL = bx-1;
 asm push dx
 _BH = bkgcolour*16;
 asm {
  pop dx
  pop cx
 }
 asm {
  mov ah,6
  mov al,0
  int 10h
 }
  asm {
  pop dx
  pop cx
  pop bx
  pop ax
  }

/*
 r.h.ah = 6;
 r.h.al = 0;
 r.h.ch = ty+mty-1+y;
 r.h.cl = tx-1;
 r.h.dh = by-mby-1;
 r.h.dl = bx-1;
 r.h.bh = colour*16;
 int86(0x10, &r, &r);
*/
}

void GEdit::pagedown(void)
{
 int i;
 clrscr(0);
 for(i=0;i<MAX_LINES && curloc<endloc;) {
//	 if(*curloc=='\r' || *curloc==Srt) i++;
	 if(*curloc=='\r' || *curloc==Srt) i++;
	 curloc++;
	 if(*curloc=='\n') curloc++;
 }
// help();
 scrnx= scrny = 0;
 beginscreen = curloc;
 if( curloc >= endloc )
  upline();
 display_scrn(0,0,curloc);
}

void GEdit::pageup(void)
{
 int i;
 clrscr(0);
 if((*curloc=='\r' || *curloc==Srt) && curloc > buf) curloc--;
 for(i=0;i<MAX_LINES+1 && curloc>buf;) {
//	 if(*curloc=='\r' || *curloc==Srt) i++;
	 if(*curloc=='\n' || *curloc==Srt) i++;
	 curloc--;
	 if(*curloc=='\r') curloc--;
 }
 if(i==MAX_LINES+1) curloc += 3;
// help();
 scrnx = scrny =0;
 beginscreen = curloc;
 display_scrn(0,0,curloc);
}

GEdit::load(void)
{
 FILE *fp;
 char ch, *p;
 name[0]=0;
 strcpy(tempbuf,bas_text);
 GetFile("Load file",NULL,ptr_panel->Basic_Path, tempbuf,name,13,5,1,Lightgray,Darkgray);
 if (*name)
 {
	buf = editbuf;

	set_semaphore_dos();
	int_disk1++;
	if((fp=fopen(name,"rb"))==NULL)
	{
		int_disk1--;
		clear_semaphore_dos();
		return 0 ;
	}
	else
	{
		int_disk1--;
	}
	p=buf;
	while(p<buf+BUF_SIZE-2) {
	 int_disk1++;
	 ch = getc(fp);
	 int_disk1--;
	 if(!ch) break;
	 if(feof(fp)) break;
	 if(ch!=EOF) {
		*p=ch;
		p++;
	 }
	}
	*p=0;
	int_disk1++;
	fclose(fp);
	int_disk1--;
	clear_semaphore_dos();
	curloc = buf;
	endloc=p;
	display_scrn_file(editbuf);
	clrscr(0);
	lastdelete = lastline = lastblock = 0;
	beginblock = endblock = 0;
	beginline = endline = 0;
	display_scrn(0,0,curloc);
	scrnx = scrny = 0;
	egotoxy(0,0);
	return 1;
 }
 return 0;
}

GEdit::save(char *fname)
{
 FILE *fp;
 char *p;
 fname[0]=0;
 strcpy(tempbuf,bas_text);
 GetFile("Save file",NULL,ptr_panel->Basic_Path, tempbuf,fname,13,5,1,Lightgray,Darkgray);
 set_semaphore_dos();
 int_disk1++;
 if((fp=fopen(fname,"wb"))==NULL)
 {
	 int_disk1--;
		clear_semaphore_dos();
	 return 0 ;
 }
 else
	 int_disk1--;
	p=buf;
	while(p!=endloc) {
		 if(*p!=Srt)
		 {
			 int_disk1++;
			 putc(*p,fp);
			 int_disk1--;
		 }
		 else
			{
			 while(*(++p)==' ');
			 if(*(--p)==Srt) p++;
			 p--;
			}
	 p++;
	}
	int_disk1++;
	fclose(fp);
	int_disk1--;
	clear_semaphore_dos();
	egotoxy(scrnx,scrny);
	return 1;
}

char * intervaltotext(char *textbuf, long seconds , unsigned minutes , unsigned hours, char *c)
{
	char buf[12], *textbuffer;
	char *separator = c ;
	textbuffer = buf;
	if( seconds < 0 )
	{
		seconds = -seconds;
		strcpy(textbuffer++, "-" ) ;        /* add the '-' */
	}
	if(*c!='-')
	{
	 hours += seconds/3600;
	 minutes += (unsigned)(seconds%3600)/60;
	 seconds = (unsigned)(seconds%3600)%60;
	}
	if( hours < 10 ) {
			strcpy(textbuffer++, "0" ) ;        /* add the leading zero 0#:##:## */
	}
	itoa(hours,textbuffer,10) ;
	textbuffer += strlen(textbuffer);
	strcpy(textbuffer++, separator ) ;        /* add the ":" separator*/

	if( minutes < 10 ) {
			strcpy(textbuffer++, "0" ) ;        /* add the leading zero ##:0#:## */
	}
	itoa(minutes,textbuffer,10) ;
	textbuffer += strlen(textbuffer);
	strcpy(textbuffer++, separator ) ;        /* add the ":" separator*/
	if( seconds < 10 ) {
			strcpy(textbuffer++, "0" ) ;        /* add the leading zero ##:##:0# */
	}
	itoa(seconds,textbuffer,10)  ;

	if(textbuf) strcpy(textbuf, buf);
	return( buf ) ;
}
/*******************intervaltotext ********************/

void psearch(GWDialog *D)
{
 D->GDGets(search_str,1,19,40,Cyan,White);
}

void preplace(GWDialog *D)
{
 D->GDGets(replace_str,2,19,40,Cyan,White);
 D->exitCR = 1;
}

int basicprogram(char *source, char *code, Str_program_point *prg, int currentprogram, int panel, int network)
{
	 asm push es;
	 int l=0;
	 DORU_SYSTEM=1;
	 if (!source) return -1;
	 if (!prg->bytes)
	 {
		*source=0;
		return 0;
	 }
	 GEdit *e;
	 e=new GEdit(1,1,80,24,0, code, ptr_panel->code_length, prg, currentprogram-1, panel, network);
	 e->GWSet("",Blue,Cyan);
	 e->GShowWindow(0);
	 e->GEditSet("",Blue,Blue);
	 l=0;
	 while(e->editbuf[l++]);
	 memcpy(source, e->editbuf, l);
	 source[l] = 0;
	 delete e;

	 asm pop es;
	 return l;
}

int basicprogram1(char *source, char *code, Str_program_point *prg, int currentprogram, int panel, int network)
{
	 asm push es;
	 int l=0;
//	 DORU_SYSTEM=1;
	 if (!source) return -1;
	 if (!prg->bytes)
	 {
		*source=0;
		return 0;
	 }
	 GEdit *e;
	 e=new GEdit(1,1,80,24,0, code, ptr_panel->code_length, prg, currentprogram-1, panel, network);
	 l=0;
	 while(e->editbuf[l++]);
	 memcpy(source, e->editbuf, l);
	 source[l] = 0;
	 delete e;

	 asm pop es;
	 return l;
}

