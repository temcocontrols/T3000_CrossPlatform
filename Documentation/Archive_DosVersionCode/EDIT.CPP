#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <bios.h>
#include <conio.h>
#include "gwin.h"


#define BUF_SIZE 10000
#define MAX_KILL_BUF_SIZE 320

extern GWindow e;
char buf[BUF_SIZE];
char *curloc, *endloc;
char killbuf[MAX_KILL_BUF_SIZE];
int scrnx, scrny;
int LINE_LEN;
int MAX_LINES;
int KILL_BUF_SIZE;

char *helpline =
			"F1: save  F2: load  F3: find  F4: replace  ^K: delete line  ^Y: paste ^Z: quit";

save(char *fname);
load(char *fname);
void help(void);
void clrscr(void);
void printline(char *p);
void pageup(void);
void pagedown(void);
void edit_clr_eol(int x, int y);
void clrline(int y);
void egotoxy(int x, int y);
void edit(char *fname);
void left(void);
void right(void);
void upline(void);
void downline(void);
void delete_char(void);
void kill_line(void);
void escrollup(int topx, int topy, int endx, int endy);
void scrolldn(int x,int y);
void replace(void);
void edit_gets(char *str);
void search(void);
void yank(void);
void display_scrn(int x, int y, char *p);
void home(void);
void gotoend(void);


void edit(char *fname)
{
 union k {
	 char ch[2];
	 unsigned i;
 } key;
 char name[80];
 LINE_LEN = e.GWRetLimits(6)-e.GWRetLimits(4);
 MAX_LINES = e.GWRetLimits(7)-e.GWRetLimits(5)-1;

 KILL_BUF_SIZE= 4*LINE_LEN;

 if (!load(fname)) curloc = endloc = buf;
 strcpy(name,fname);

 textcolor(WHITE);
 textbackground(BLUE); clrscr();
 scrnx = scrny = 0;
 display_scrn(0,0,curloc);
 help();
 egotoxy(0,0);

 do {
 key.i = bioskey(0);
 if (!key.ch[0]) {
	 switch (key.ch[1]) {
		case 59:  //save
				 save(name);
				 break;
		case 60: //load
				 clrline(MAX_LINES);
				 egotoxy(0,MAX_LINES+1);
				 printf("File name: ");
				 edit_gets(name);
				 if (*name) load(name);
				 clrscr();
				 help();
				 display_scrn(0,0,curloc);
				 scrnx = scrny = 0;
				 break;
		case 61:   //search
				 search();
				 break;
		case 62:  //replace
				 replace();
				 break;
		case 71:  //home
				 home();
				 break;
		case 79:  //end
				 gotoend();
				 break;
		case 75:  //left
				 left();
				 break;
		case 77:  //right
				 right();
				 break;
		case 72:  //up
				 upline();
				 break;
		case 80:  //down
				 downline();
				 break;
		case 73:  //page up
				 pageup();
				 break;
		case 81:  //page down
				 pagedown();
				 break;
		case 83:  //del
				 if(curloc<endloc) delete_char();
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
						 if (endloc==buf+BUF_SIZE-2) break;
						 memmove(curloc+1, curloc, endloc-curloc+1);
						 *curloc = key.ch[0];
						 curloc++;
						 edit_clr_eol(scrnx,scrny);
						 scrnx = 0;
						 scrny++;
						 if(scrny==MAX_LINES) {
							 scrny=MAX_LINES-1;
							 escrollup(0,0,LINE_LEN,scrny);
						 }
						 else scrolldn(scrnx,scrny);

						 egotoxy(scrnx,scrny);
						 printline(curloc);
						 endloc++;
						 break;
			case '\b': //BS
						 if(curloc==buf) break;
						 left();
						 delete_char();
						 break;
			case '11': //CTRL-K kill line
						 kill_line();
						 break;
			case '25': //CTRL-Y yank kill buffer
						 yank();
						 break;
			default:
						 if (endloc==buf+BUF_SIZE-2) break;
						 if(scrnx==LINE_LEN) break;
						 memmove(curloc+1, curloc, endloc-curloc+1);
						 *curloc = key.ch[0];
						 putch(*curloc);
						 scrnx++;
						 egotoxy(scrnx,scrny);
						 printline(curloc+1);
						 curloc++;
						 endloc++;
		 }
		 egotoxy(scrnx,scrny);
	 }
 } while(key.ch[0]!=26);  //CTRL-Z
}

void left(void)
{
 if(curloc==buf) return;
 scrnx--;
 if(scrnx < 0) {
	 scrnx = 0;
	 upline();

	 while(*curloc!='\r') {
		 curloc++;
		 scrnx++;
	}
 }
 else curloc--;
}

void right(void)
{
 if (curloc+1 > endloc) return;
 scrnx++;
 if (scrnx > LINE_LEN || *curloc == '\r') {
		scrnx = 0;
		scrny++;
		if (scrny==MAX_LINES) {
			scrny = MAX_LINES-1;
			downline();
			curloc--;
			while(*curloc!='\r') curloc--;
			curloc++;
			scrnx = 0;
		 }
		 else curloc++;
	}
	else curloc++;
}

void upline(void)
{
 int i;
 char *p;
 if(curloc==buf) return;
 p=curloc;
 if(*p=='\r') p--;
 for(;*p!='\r' && p>buf; p--);
 if(*p!='\r') return;
 curloc =p;
 curloc--;
 i= scrnx;
 while(*curloc!='\r' && curloc>=buf) curloc--;
 scrny--; scrnx = 0;
 curloc++;
 if(scrny<0) {
	 scrolldn(0,0);
	 scrny = 0;
	 egotoxy(0,0);
	 printline(curloc);
 }
 while(i && *curloc!='\r') {
	 curloc++;
	 scrnx++;
	 i--;
 }
}

void downline(void)
{
 int i;
 char *p;

 i=scrnx;
 p=curloc;
 while(*p!='\r' && p<endloc) p++;
 if(p==endloc) return;
 p++;
 curloc=p;
 scrny++; scrnx=0;
 if(scrny==MAX_LINES) {
	 scrny = MAX_LINES-1;
	 escrollup(0,0,LINE_LEN, MAX_LINES);
	 egotoxy(scrnx,scrny);
	 printline(curloc);
 }

 while(i && *curloc!='\r' && curloc<endloc) {
	 curloc++;
	 scrnx++;
	 i--;
 }
}

void delete_char(void)
{
 egotoxy(scrnx,scrny);
 if(*curloc=='\r') {
	escrollup(0,scrny+1, LINE_LEN, MAX_LINES-1);
	memmove(curloc, curloc+1, endloc-curloc);
	endloc--;
	display_scrn(scrnx, scrny, curloc);
	help();
 }
 else {
	memmove(curloc, curloc+1, endloc-curloc);
	endloc--;
	printline(curloc); printf(" ");
 }
}

void kill_line(void)
{
 int i;
 char *p, *killbufptr;
 if(*curloc=='\r') {
	delete_char();
	return;
 }

 edit_clr_eol(scrnx,scrny);
 p=curloc;
 i=0;
 killbufptr = killbuf;
 while(*p!='\r' &&p<endloc) {
	i++;
	*killbufptr = *p;
	p++;
	if(killbufptr<killbuf+KILL_BUF_SIZE-2) killbufptr++;
 }
 *killbufptr = '\0';
 memmove(curloc, curloc+i, endloc-curloc);
 endloc -= i;
}

void yank(void)
{
}

void search(void)
{
}

void edit_gets(char *str)
{
 char *p;
 p=str;
 for(;;) {
 *str=getch();
 if(*str=='\r') {
	*str = '\0';
	return;
 }
 if(*str=='\b') {
	if(str>p) {
	 str--;
	 putch('\b');
	 putch(' ');
	 putch('\b');
	}
 }
 else {
	 putch(*str);
	 str++;
	}
 }
}

void replace(void)
{
}

void scrolldn(int x,int y)
{
// union REGS r;

 asm {
  push ax
  push bx
  push cx
  push dx
 }
 _CH = y+e.GWRetLimits(5)-1;
 asm push ch
 _CL = x+e.GWRetLimits(4)-1;
 asm push cl
 _DH = e.GWRetLimits(7)-2;
 asm push dh
 _DL = e.GWRetLimits(6)-2;
 asm {
  pop dh
  pop cl
  pop ch
 }
 asm {
  mov ah,7
  mov al,1
  mov bh,BLUE*16+LIGHTGRAY
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
 r.h.ch = y+e.GWRetLimits(5)-1;
 r.h.cl = x+e.GWRetLimits(4)-1;
 r.h.dh = e.GWRetLimits(7)-2;
 r.h.dl = e.GWRetLimits(6)-2;
 r.h.bh = BLUE*16+LIGHTGRAY;
 int86(0x10, &r, &r);
*/
}

void escrollup(int topx, int topy, int endx, int endy)
{
// union REGS r;

  asm {
  push ax
  push bx
  push cx
  push dx
  }
 _CH = topy+e.GWRetLimits(5)-1;
 asm push ch
 _CL = topx+e.GWRetLimits(4)-1;
 asm push cl
 _DH = endy+e.GWRetLimits(5)-1;
 asm push dh
 _DL = endx+e.GWRetLimits(4)-1;
 asm {
  pop dh
  pop cl
  pop ch
 }
 asm {
  mov ah,6
  mov al,1
  mov bh,BLUE*16+LIGHTGRAY
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
 r.h.ch = topy+e.GWRetLimits(5)-1;
 r.h.cl = topx+e.GWRetLimits(4)-1;
 r.h.dh = endy+e.GWRetLimits(5)-1;
 r.h.dl = endx+e.GWRetLimits(4)-1;
 r.h.bh = BLUE*16+LIGHTGRAY;
 int86(0x10, &r, &r);
*/
}

void printline(char *p)
{
 int i;
 i=scrnx;
 while(*p!='\r' && *p && i<LINE_LEN) {
	 putch(*p);
	 p++;
	 i++;
 }
}

void help(void)
{
// window(1,1,80,25);
 textbackground(LIGHTGRAY);
 gotoxy(1,25);
 cprintf(helpline);
// window(e.GWRetLimits(4),e.GWRetLimits(5),e.GWRetLimits(6),e.GWRetLimits(7));
 textbackground(BLUE);

}

void display_scrn(int x, int y, char *p)
{
 int i;
 egotoxy(x,y);
 i=0;
 while(y<MAX_LINES && *p) {
	 switch (*p) {
		 case '\r':
				 cprintf("\n");
				 y++;
				 gotoxy(e.GWRetLimits(4),y+e.GWRetLimits(5));
				 i=0;
				 break;
		 default:
				 if(i<LINE_LEN) putch(*p);
				 i++;
		 }
		 p++;
 }
}

void home(void)
{
 clrscr();
 curloc = buf;
 scrnx = scrny = 0;
 display_scrn(0,0,curloc);
 help();
}

void gotoend(void)
{
 clrscr();
 curloc=endloc;
 pageup();
}

load(char *fname)
{
 FILE *fp;
 char ch, *p;
 if((fp=fopen(fname,"rb"))==NULL)
	return 0 ;
 p=buf;
 while(!feof(fp) && p!=buf+BUF_SIZE-2) {
	 ch = getc(fp);
	 if(ch!='\n' && ch!=EOF) {
		*p=ch;
		p++;
	 }
 }
 *p=0;
 fclose(fp);
 curloc = buf;
 endloc=p;
 return 1;
}

save(char *fname)
{
 FILE *fp;
 char name[80], *p;
 egotoxy(0,MAX_LINES);
 if(!*fname) {
	cprintf("File name [Save]: ");
	gets(name);
 }
 else strcpy(name, fname);

 if((fp=fopen(fname,"wb"))==NULL)
	return 0 ;
 p=buf;
 while(p!=endloc) {
	 if(*p!='\r')
		 putc(*p,fp);
	 else {
		putc('\r', fp);
		putc('\n', fp);
	}
	p++;
 }
 fclose(fp);
 display_scrn(0,0,curloc);
 return 1;
}

void cursor_pos(void)
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

void egotoxy(int x, int y)
{
/* union REGS i;
 i.h.dh = y +  e.GWRetLimits(5);
 i.h.dl = x +  e.GWRetLimits(4);
 i.h.ah = 2;
 i.h.bh = 0;
 int86(16,&i,&i);
*/
 gotoxy(x+e.GWRetLimits(4),y+e.GWRetLimits(5));
}

void clrline(int y)
{
 int i;
 egotoxy(0,y);
 for(i=0;i<LINE_LEN;i++) putch(' ');
}

void edit_clr_eol(int x, int y)
{
 char *p;
 p=curloc;
 egotoxy(x,y);
 for(;x<LINE_LEN && *p!='\r' && *p; x++, p++) {
	 printf(" ");
 }
}

void clrscr(void)
{
// union REGS r;

  asm {
  push ax
  push bx
  push cx
  push dx
  }
 _CH = e.GWRetLimits(5)-1;
 asm push ch
 _CL =  e.GWRetLimits(4)-1;
 asm push cl
 _DH = e.GWRetLimits(7)-1;
 asm push dh
 _DL = e.GWRetLimits(6)-1;
 asm {
  pop dh
  pop cl
  pop ch
 }
 asm {
  mov ah,6
  mov al,0
  mov bh,BLUE*16+LIGHTGRAY
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
 r.h.ch = e.GWRetLimits(5)-1;
 r.h.cl = e.GWRetLimits(4)-1;
 r.h.dh = e.GWRetLimits(7)-1;
 r.h.dl = e.GWRetLimits(6)-1;
 r.h.bh = BLUE*16+LIGHTGRAY;
 int86(0x10, &r, &r);
*/
}

void pagedown(void)
{
 int i;
 clrscr();
 