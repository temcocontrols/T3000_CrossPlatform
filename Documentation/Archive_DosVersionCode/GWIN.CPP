// atof

#include "gwin.h"
#include <math.h>
#include <bios.h>
#include <dir.h>
#include <mem.h>
#include <graphics.h>
#include <fcntl.h>
#include <SYS\STAT.H>
#define LINE_SPACE (mode_text ? 0 : 4)
#include "_msdos.h"

#include "vga12.h"
#include "t3000def.h"
#include "mtkernel.h"
#include "T3000hlp.h"

#define PGDN 81
#define PGUP 73
#define RIGHT 77
#define LEFT 75
#define HOME 71
#define ENDKEY 79
#define UP 72
#define DOWN 80
#define INSERT  82
#define DELETE  83
#define ENTER  13

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

extern void memsize(void);
extern mmputimage(int ltopx, int ltopy, int rbottomx, int rbottomy, signed char *under1);
extern mmgetimage(int ltopx, int ltopy, int rbottomx, int rbottomy, signed char **under1);

extern int decode( unsigned char *line, int size, signed char *buf )   ;
extern int encode( unsigned char *line, int size , signed char *buf);

extern int worktime;
extern int mode_text;
extern int text;
extern int mode_text;
extern  int gtx,gty,gbx,gby;
extern Pshape ARROW;
void chbkg(int lx, int ly, int width, int bkgnd, int frgnd, int unchangecol=127, int height = 0);
extern void Bordergr(int ltopx, int ltopy, int rbottomx, int rbottomy, int colour, int bkgnd, int bcolour,int butcol, int how, int out);
extern void msettextstyle(int font, int dir, int chars);
extern int doubleclick(void);

extern  void print();


extern char huge *ok_button,*cancel_button;
extern char huge *lin_menu;
extern char huge *lin_menu_full;
extern char huge *lin_hor;
extern char huge *lin_ver;
extern int dxscreen, dyscreen;

extern int lat_char_n;
extern int lung_char_n;
extern int font_type,charsize;

extern char *lin_text;
extern char huge *lin_menu_full;
//extern int nofond;
extern int xsign,ysign;
extern long data_const, data_length_const;

GWControl Control;
int select_tmp;
char huge linebuf[730];

/********Functii auxiliare**************************/
extern char wingets(char far *ptr, int row, int col, int width,
				 int bkgnd, int frgnd, char which_type, char *sablon=NULL, char retnokey = 0);

void put_text(char *p, char x, char y, int bkgnd, int frgnd);

/********Constructor***************/

GWindow::GWindow(int lx, int ly, int rx, int ry, uint stk, int but, int ftype, int csize, char dprint)
                 :GView(lx,ly,rx,ry)
{
 GWInit(lx, ly, rx, ry, stk, but, ftype, csize, dprint);
};

/********Constructor***************/

GWindow::GWindow(int lx, int ly, int rx, int ry, char far *ptitle,
								 uint bkgclr, uint title_bkgclr, uint border_frgclr,
								 uint stk, int but, int ftype, int csize, char dprint)
								 :GView(lx,ly,rx,ry)
{
	GWInit(lx, ly, rx, ry, stk, but, ftype, csize, dprint);
	GWSet(ptitle, bkgclr, title_bkgclr, border_frgclr);
};

/*******************************/
// spot = 1  - buttons
// spot = 5  - without 3 lines on left side and botoom

void GWindow::GWInit(int lx, int ly, int rx, int ry, uint stk, int but, int ftype, int csize, char dprint)
{
 if(stk)
		NO_STK = 0;
 else
		NO_STK = 1;
 on_screen = 0;
 spot      = but;
 retnokey  = select = grid = esc = error = 0;
 title_handle = title_status = 0;
 handle    = 0;
 title     = NULL;
 mode      = TEXT_MODE_WINDOW;
 old_fonttype = font_type; old_charsize=charsize;
 w_fonttype=ftype; w_charsize=csize; doubleprint=dprint;
};

/***********************************/
GWindow::~GWindow()
{
 if(!mode_text)
 {
	font_type=old_fonttype; charsize=old_charsize;
	set_semaphore(&screen);
	settextstyle(font_type, HORIZ_DIR, charsize);
	lat_char_n = textwidth(" ");
	lung_char_n = textheight("H");
	clear_semaphore(&screen);
 }

//	GReleaseWindow();
}

/***********************************/

uint GWindow::GWRetLimits(int which_one)
{
 switch(which_one){

	case 0:return ltop.x;
	case 1:return ltop.y;
	case 2:return rbottom.x;
	case 3:return rbottom.y;
	case 4:return tx;
	case 5:return ty;
	case 6:return bx;
	case 7:return by;
			 }
 return 0;
};

/********Set title and colour******/

void GWindow::GWBorder(void)
{
	Bordergr(ltop.x, ltop.y, rbottom.x,rbottom.y, border_frgcolour, bkgcolour, White, Green, 0, 0);
	lin_menu[rbottom.x-ltop.x+1]=0;
	mxyputs(ltop.x,ltop.y,lin_menu,title_bkgcolour,bkgcolour);
	lin_menu[rbottom.x-ltop.x+1]=lin_menu[0];
	return;
}

void GWindow::GWSet(char far *ptitle, uint bkgclr, uint title_bkgclr, uint border_frgclr)
{
 uint lat,lung,dx,dy;
 int l;
 bkgcolour=bkgclr;
 title_bkgcolour=title_bkgclr;
 border_bkgcolour=title_bkgclr;
 border_frgcolour = border_frgclr;

 if(!mode_text)
	 msettextstyle(w_fonttype, HORIZ_DIR, w_charsize);
 if(ptitle)
 {
//	mfarmalloc((char far **)&title, (unsigned long)strlen(mes)+1, title_handle);
	mfarmalloc((char far **)&title, (unsigned long)(strlen(ptitle)+1));
	if(title==NULL)
	{
	 GWPuts(1,1,"FAIL IN FARMALLOC",Lightgray,Black);
//	 exit(0);
	}
	movedata( FP_SEG(ptitle), FP_OFF(ptitle),FP_SEG(title), FP_OFF(title), strlen(ptitle)+1);
 }
 else
	title=NULL;

 l=0;
 if(mode_text)
 {
  lat=1;
  lung=1;
  dx=dy=1;
  if(title)
	l=strlen(title)+1;
 }
 else
 {
  lat=lat_char_n;                  //textwidth(" ");
  lung=lung_char_n+LINE_SPACE;     //textheight("H")+LINE_SPACE;
  dx=dy=20;
  if(title)
	l = lat * strlen(title); //textwidth(title);
 }

 if(l>(rbottom.x-ltop.x-4*lat))
 {
//		mxyputs(10,10,"TITLE TOO LONG");
		title[(rbottom.x-ltop.x-4*lat)/lat]=0;
 }

 if(mode_text)
 {
		tx=ltop.x+1;
		if (grid)
			ty=ltop.y+2*lung;
		else
			ty=ltop.y+lung;
		bx=rbottom.x-dx;
		by=rbottom.y-dy;
		nrows=(by-ty+1)/lung;
		ncols=(bx-tx+1)/lat;
 }
 else
 {
		tx=ltop.x+3;
		if(spot==5)
			tx=ltop.x;

		if (grid)
//			ty=ltop.y+textheight("H")+12;    //16;
			ty=ltop.y+textheight("H")+8;    //16;
		else
			ty=ltop.y+textheight("H")+4;
		if(spot==GRID || spot==GRIDINS)
		{
			bx=rbottom.x-dx;
			by=rbottom.y-3-dy;
		}
		else
		{
			bx=rbottom.x;
			if(spot==5)
				by=rbottom.y;
			else
				by=rbottom.y-3;
		}

		nrows=(by-ty-2)/lung;
		ncols=(bx-tx-2)/lat;
 }



 if(mode_text)
 {
	close_spot.top.x=tx-1;        //tx
	close_spot.top.y=ltop.y;
	close_spot.bot.x=tx;          //tx+2
	close_spot.bot.y=ltop.y;

	lscroll.top.x=tx-1;           //tx
	lscroll.top.y=rbottom.y;
	lscroll.bot.x=tx;             //tx
	lscroll.bot.y=rbottom.y;

	rscroll.top.x=bx-1;             //bx
	rscroll.top.y=rbottom.y;
	rscroll.bot.x=bx;            //bx
	rscroll.bot.y=rbottom.y;

	uscroll.top.x=rbottom.x;
	uscroll.top.y=ty;
	uscroll.bot.x=rbottom.x;
	uscroll.bot.y=ty;

	dscroll.top.x=rbottom.x;
	dscroll.top.y=by;
	dscroll.bot.x=rbottom.x;
	dscroll.bot.y=by;

	ziscroll.top.x=bx+1;        //0
	ziscroll.top.y=ltop.y;
	ziscroll.bot.x=bx+1;       //0
	ziscroll.bot.y=ltop.y;

	zoscroll.top.x=bx*dx;       //-2
	zoscroll.top.y=ltop.y;
	zoscroll.bot.x=bx*dx;      //-2
	zoscroll.bot.y=ltop.y;

	mscroll.top.x=rbottom.x;
	mscroll.top.y=rbottom.y;
	mscroll.bot.x=rbottom.x;
	mscroll.bot.y=rbottom.y;
 }
 else
 {
	close_spot.top.x=tx;
	close_spot.top.y=ltop.y;
	close_spot.bot.x=tx+dx;
	close_spot.bot.y=ty;

	lscroll.top.x=tx;
	lscroll.top.y=by;
	lscroll.bot.x=tx+dx;
	lscroll.bot.y=rbottom.y-3;

	rscroll.top.x=bx-dx;
	rscroll.top.y=by;
	rscroll.bot.x=bx;
	rscroll.bot.y=rbottom.y-3;

	uscroll.top.x=bx;
	uscroll.top.y=ty;
	uscroll.bot.x=rbottom.x;
	uscroll.bot.y=ty+dy;

	dscroll.top.x=bx;
	dscroll.top.y=by-dy;
	dscroll.bot.x=rbottom.x;
	dscroll.bot.y=by;

	ziscroll.top.x=bx;
	ziscroll.top.y=ltop.y;
	ziscroll.bot.x=rbottom.x;
	ziscroll.bot.y=ty;

	zoscroll.top.x=bx-dx;
	zoscroll.top.y=ltop.y;
	zoscroll.bot.x=bx;
	zoscroll.bot.y=ty;


	mscroll.top.x=bx;
	mscroll.top.y=by;
	mscroll.bot.x=rbottom.x;
	mscroll.bot.y=rbottom.y;
 }
};


/*
void pbar(int tx, int ty, int bx, int by)
{
  int i;
  for( i=ty+(by-ty)/2; i >= ty; i=i-16 )
  {
	bar(tx, i, bx, i+(ty+(by-ty)/2-i)*2);
  }
  bar(tx, ty, bx, by);
}
*/

/**********************************/


void GWindow::GShowWindow(int vspot, int saveunder)
{
 uint big1;
 struct fillsettingstype fill;
 int pol[8],handle;
 uint dx,dy,lat;

 int sx,sy,jx,jy;

 spot = vspot;
 sx=(int)ltop.x;
 sy=(int)ltop.y;
 jx=(int)rbottom.x;
 jy=(int)rbottom.y;

 if(on_screen) return;

 on_screen=1;

 if(!NO_STK)
	Control.Push(this);


 if(mode_text)
 {
  if(saveunder)
	 SaveArea();
  hide_pointer();
// window
//  if(!nofond)
  GWBorder();

// close
  lat=1;
  dx=dy=1;
  if(title)
  {
	if(title_status)
	 mxyputs(bx-strlen(title)-((bx-tx)>60?10:5), ltop.y,title,title_bkgcolour,White);
	else
	 mxyputs((bx+tx+lat)/2-strlen(title)/2, ltop.y,title,title_bkgcolour,White);
  }

  if (spot && spot!=5 && spot!=WIN_ERROR)
  {
	 if(!text)
	 {
		char buf[81];
		memset(buf,209,rbottom.x-ltop.x+1);
		buf[rbottom.x-ltop.x+1]=0;
		mxyputs(ltop.x,rbottom.y,buf,bkgcolour,Black);

		dxscreen--;
		dyscreen++;
		memset(buf,208,rbottom.y-ltop.y+1);
		buf[rbottom.y-ltop.y+1]=0;
		mxyputs(rbottom.x,ltop.y,buf,bkgcolour,Black);
		if(spot == GRIDINS)
		 mxyputs(ltop.x,ltop.y,buf,bkgcolour,Black);
		dxscreen++;
		dyscreen--;
	 }
	 if(!text)
		 moutchar( tx-1,by+1, 200+26, Lightgray, Black );
	 moutchar( tx,by+1, text?'':200+27, Lightgray, Black );
	 if(!text)
		 moutchar( bx-1,by+1, 200+28, Lightgray, Black );
	 moutchar( bx,by+1, text?'':200+29, Lightgray, Black );
	 moutchar( bx+1,ty, text?'':200+24, Lightgray, Black );
	 moutchar( bx+1,by, text?'':200+25, Lightgray, Black );
	 moutchar( bx,ltop.y, '', title_bkgcolour, White );
	 moutchar( bx+1,ltop.y, '', title_bkgcolour, White );

/*
	moutchar( tx,by+1, '', Lightgray, Black );
	moutchar( bx,by+1, '', Lightgray, Black );
	moutchar( bx+1,ty, '', Lightgray, Black );
	moutchar( bx+1,by, '', Lightgray, Black );
	moutchar( bx-2,ltop.y, '', Lightgray, Black );
	moutchar( bx,ltop.y, '', Lightgray, Black );
*/
	}
	moutchar( tx-1,ltop.y, text?178:200+10, text?Black:Lightgray, text?Lightgray:Black );
	moutchar( tx,ltop.y, text?178:200+11, text?Black:Lightgray, text?Lightgray:Black );
 }
 else
 {

	flag=0;
	if(saveunder)
	  SaveArea();
	hide_pointer();
	set_semaphore(&screen);
	getfillsettings(&fill);
	big1=getcolor();
// window
	setcolor(Black);
	setlinestyle(SOLID_LINE,0xffff,1);
	setfillstyle(SOLID_FILL,bkgcolour);
	bar(tx,ty,bx,by);
	prectangle(tx,ty,bx,by,Black);
	clear_semaphore(&screen);

	pol[0]=tx;
	pol[1]=sy;
	pol[2]=sx;
	pol[3]=sy+3;
	pol[4]=sx;
	pol[5]=jy;
	pol[6]=tx;
	pol[7]=by;

//	setfillstyle(SOLID_FILL,bkgcolour-8);
	set_semaphore(&screen);
	setfillstyle(SOLID_FILL,Darkgray);
	if(spot!=5)
		fillpoly(4,pol);
	clear_semaphore(&screen);

	pol[0]=tx;
	pol[1]=by;
	pol[2]=bx;
	pol[3]=by;
	pol[4]=jx-3;
	pol[5]=jy;
	pol[6]=sx;
	pol[7]=jy;

	if(spot!=5)
	{
		set_semaphore(&screen);
		fillpoly(4,pol);
		clear_semaphore(&screen);
	}

// close
	set_semaphore(&screen);
	lat=textwidth("  ");
	dx=dy=20;
	setfillstyle(SOLID_FILL,Lightgray);
	bar(tx,sy,tx+dx,ty);
	prectangle(tx,sy,tx+dx,ty,Black);

	setfillstyle(SOLID_FILL,Black);
	bar((tx+dx/2)-2,
		 (sy+ty)/2-1,
		 (tx+dx/2)+2,
		 (sy+ty)/2+1);

	setfillstyle(SOLID_FILL,title_bkgcolour);
	bar(tx+dx,sy,jx,ty);
	prectangle(tx+dx,sy,jx,ty,Black);

	setcolor(White);
	if(title)
	 if(title_status)
		outtextxy(bx-(strlen(title)+10)*lat_char_n, ltop.y+5, title);
	 else
//	  outtextxy((bx+tx+lat)/2-textwidth(title)/2, ty-(grid?16:2+lung_char_n), title);
		outtextxy((bx+tx+lat)/2-textwidth(title)/2, ty-(grid?8:2+lung_char_n), title);

	setcolor(Black);
	setfillstyle(SOLID_FILL,Lightgray);
	if(spot!=5)
	{
	 bar(bx,ty,rbottom.x,rbottom.y-3);
	 prectangle(bx,ty,rbottom.x,rbottom.y-3,Black);
	 bar(tx,by,rbottom.x,rbottom.y-3);
	 prectangle(tx,by,rbottom.x,rbottom.y-3,Black);
	}

	if (spot==GRID || spot==GRIDINS)
	{
	 bar(bx-dx,ltop.y,rbottom.x,ty);
	 prectangle(bx-dx,ltop.y,rbottom.x,ty,Black);

	 prectangle(lscroll.top.x,lscroll.top.y,lscroll.bot.x,lscroll.bot.y,Black);
	 prectangle(rscroll.top.x,rscroll.top.y,rscroll.bot.x,rscroll.bot.y,Black);
	 prectangle(uscroll.top.x,uscroll.top.y,uscroll.bot.x,uscroll.bot.y,Black);
	 prectangle(dscroll.top.x,dscroll.top.y,dscroll.bot.x,dscroll.bot.y,Black);
	 prectangle(zoscroll.top.x,zoscroll.top.y,zoscroll.bot.x,zoscroll.bot.y,Black);
	 prectangle(ziscroll.top.x,ziscroll.top.y,ziscroll.bot.x,ziscroll.bot.y,Black);
	 setcolor(DARKGRAY);
	 pline(lscroll.top.x+1,lscroll.bot.y-1,lscroll.bot.x-1,lscroll.bot.y-1,Black);
	 pline(lscroll.bot.x-1,lscroll.top.y+1,lscroll.bot.x-1,lscroll.bot.y-1,Black);
	 pline(rscroll.top.x+1,rscroll.bot.y-1,rscroll.bot.x-1,rscroll.bot.y-1,Black);
	 pline(rscroll.bot.x-1,rscroll.top.y+1,rscroll.bot.x-1,rscroll.bot.y-1,Black);
	 pline(uscroll.top.x+1,uscroll.bot.y-1,uscroll.bot.x-1,uscroll.bot.y-1,Black);
	 pline(uscroll.bot.x-1,uscroll.top.y+1,uscroll.bot.x-1,uscroll.bot.y-1,Black);
	 pline(dscroll.top.x+1,dscroll.bot.y-1,dscroll.bot.x-1,dscroll.bot.y-1,Black);
	 pline(dscroll.bot.x-1,dscroll.top.y+1,dscroll.bot.x-1,dscroll.bot.y-1,Black);
	 pline(ziscroll.top.x+1,ziscroll.bot.y-1,ziscroll.bot.x-1,ziscroll.bot.y-1,Black);
	 pline(ziscroll.bot.x-1,ziscroll.top.y+1,ziscroll.bot.x-1,ziscroll.bot.y-1,Black);
	 pline(zoscroll.top.x+1,zoscroll.bot.y-1,zoscroll.bot.x-1,zoscroll.bot.y-1,Black);
	 pline(zoscroll.bot.x-1,zoscroll.top.y+1,zoscroll.bot.x-1,zoscroll.bot.y-1,Black);

	 setcolor(White);
	 pline(lscroll.top.x+1,lscroll.top.y+1,lscroll.bot.x-1,lscroll.top.y+1,White);
	 pline(lscroll.top.x+1,lscroll.top.y+1,lscroll.top.x+1,lscroll.bot.y-1,White);
	 pline(rscroll.top.x+1,rscroll.top.y+1,rscroll.bot.x-1,rscroll.top.y+1,White);
	 pline(rscroll.top.x+1,rscroll.top.y+1,rscroll.top.x+1,rscroll.bot.y-1,White);
	 pline(uscroll.top.x+1,uscroll.top.y+1,uscroll.bot.x-1,uscroll.top.y+1,White);
	 pline(uscroll.top.x+1,uscroll.top.y+1,uscroll.top.x+1,uscroll.bot.y-1,White);
	 pline(dscroll.top.x+1,dscroll.top.y+1,dscroll.bot.x-1,dscroll.top.y+1,White);
	 pline(dscroll.top.x+1,dscroll.top.y+1,dscroll.top.x+1,dscroll.bot.y-1,White);
	 pline(ziscroll.top.x+1,ziscroll.top.y+1,ziscroll.bot.x-1,ziscroll.top.y+1,White);
	 pline(ziscroll.top.x+1,ziscroll.top.y+1,ziscroll.top.x+1,ziscroll.bot.y-1,White);
	 pline(zoscroll.top.x+1,zoscroll.top.y+1,zoscroll.bot.x-1,zoscroll.top.y+1,White);
	 pline(zoscroll.top.x+1,zoscroll.top.y+1,zoscroll.top.x+1,zoscroll.bot.y-1,White);



	 setcolor(Black);
//	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	 setfillstyle(fill.pattern,fill.color);

	 outtextxy(tx+5,by+7,"");
	 outtextxy(bx-11,by+7,"");
	 outtextxy(bx+7,ty+7,"");
	 outtextxy(bx+7,by-13,"");
	 outtextxy(bx-13,ty-13,"");
	 outtextxy(bx+7,ty-13,"");

// setfillstyle(fill.pattern,fill.color);
	 setcolor(big1);
//	msettextstyle(font_type,HORIZ_DIR,charsize);
	}
	clear_semaphore(&screen);
//	msettextstyle(font_type,HORIZ_DIR,charsize);
 }
 display_pointer();

};


void GWindow::GWchbkg(int lx, int ly, int width, int bkgnd, int frgnd, int unchangecol, int height)
{
 chbkg( GWx(lx), GWy(ly), width, bkgnd, frgnd, unchangecol, height);
}


/****************************/

int GWindow::HandleEvent()
{
 uint dx;
 MouseStatus stat;
 union {
		int i;
		char ch[2];
		} key;


 if (bioskey_new(1) || esc )                //kbhit())
 {
	if(!esc )
		key.i = bioskey_new(0);
	if (key.ch[0] == 27 || spot==WIN_ERROR || esc )
		 {
			GReleaseWindow();
			return 1;
		 }
 }
 if(mouse_inside(close_spot.top.x,
		 close_spot.top.y,
		 close_spot.bot.x,
		 close_spot.bot.y))
		{
			mouse_status(stat);
			if(stat.leftButton)
			 {
				 while(!get_button_released(BLEFT,stat));
				 esc = 1;
				 return 0;
			 }
		}
 if(mouse_inside(lscroll.top.x,
		 lscroll.top.y,
		 lscroll.bot.x,
		 lscroll.bot.y))
		{
			mouse_status(stat);
			if(stat.leftButton)
			 {
//				outtextxy(100,100,"ллллллллллл");
				hide_pointer();
//				outtextxy(100,100,"left scroll");
				display_pointer();
				return 0;
			 }
		}
 if(mouse_inside(rscroll.top.x,
		 rscroll.top.y,
		 rscroll.bot.x,
		 rscroll.bot.y))
		{
			mouse_status(stat);
			if(stat.leftButton)
			 {
//				outtextxy(100,100,"ллллллллллл");
				hide_pointer();
//				outtextxy(100,100,"right scroll");
				display_pointer();
				return 0;
			 }
		}
 if(mouse_inside(uscroll.top.x,
		 uscroll.top.y,
		 uscroll.bot.x,
		 uscroll.bot.y))
		{
			mouse_status(stat);
			if(stat.leftButton)
			 {
//				outtextxy(100,100,"ллллллллллл");
				hide_pointer();
//				outtextxy(100,100,"up scroll");
				display_pointer();
				return 0;
			 }
		}
 if(mouse_inside(dscroll.top.x,
		 dscroll.top.y,
		 dscroll.bot.x,
		 dscroll.bot.y))
		{
			mouse_status(stat);
			if(stat.leftButton)
			 {
//				outtextxy(100,100,"ллллллллллл");
				hide_pointer();
//				outtextxy(100,100,"down scroll");
				display_pointer();
				return 0;
			 }
		}

 if(mode_text)
	dx=1;
 else
	dx=20;
 if(mouse_inside(tx+dx,
		 ltop.y,
		 bx,
		 ty))
		{
			get_button_released(BRIGHT,stat);
			get_button_released(BLEFT,stat);
			mouse_status(stat);
			if(stat.leftButton)
			 {
				int x,y,lx,ly,rx,ry;
				char *buf;
				HANDLE h;
				lx=ltop.x;ly=ltop.y;rx=rbottom.x;ry=rbottom.y;
				mfarmalloc((char far **)&buf, (unsigned long)( (rbottom.x-ltop.x+1)*(rbottom.y-ltop.y+1)*2), h);
				if(buf!=NULL)
				{
//				mouse_motion(&x,&y);
//				mouse_status(stat);
				int cx=stat.where.x;
				int cy=stat.where.y;
				while(!get_button_released(BLEFT,stat))
				{
				 mouse_status(stat);
				 x = stat.where.x-cx;
				 y = stat.where.y-cy;

				 if (x!=0 || y!=0)
				 {
					cx=stat.where.x;
					cy=stat.where.y;

					lx += x; ly += y ; rx += x ; ry += y;
					if (lx <= 0) {	rx = rx-lx+1;lx=1; }
					if (rx >= 80) {	lx = lx-(rx-80)-1;rx=80-1; }
					if (ly <= 0) {	ry = ry-ly+1;ly=1; }
					if (ry > 24) {	ly = ly-(ry-24)-1;ry=24-1; }
					if(mode_text)
					{
					 hide_pointer();
					 mgettext(ltop.x,ltop.y,rbottom.x,rbottom.y,buf);
					 RestoreArea();
					 ltop.x=lx;ltop.y=ly;rbottom.x=rx;rbottom.y=ry;
					 SaveArea();
					 hide_pointer();
					 mputtext(ltop.x,ltop.y,rbottom.x,rbottom.y, buf);
					 display_pointer();
					}
					else
					{
					 GReleaseWindow();
					 ltop.x=lx;ltop.y=ly;rbottom.x=rx;rbottom.y=ry;
					 GWSet(NULL,Lightgray,Darkgray);
					 GShowWindow(spot);
					}
				 }
				}
//				 set_pointer_shape(ARROW);
				 display_pointer();
				 mfarfree(h);
				 GReleaseWindow();
				 ltop.x=lx;ltop.y=ly;rbottom.x=rx;rbottom.y=ry;
				 GWSet(NULL,bkgcolour,title_bkgcolour);
				 GShowWindow(spot);
				}
				return 0;
				}
		}
 return 0;
}

/********************************************/

int GWindow::GWx(int col)
{
// uint lat,lung;
// if(mode_text)
//	 lat  = 1;
// else
//	 lat  = textwidth(" ");
 return(tx+col*lat_char_n);
};

/********************************************/

int GWindow::GWy(int row)
{
// uint lat,lung;

// if(mode_text)
//	 lung = 1;
// else
//	 lung = textheight("H")+LINE_SPACE;

	 if(mode_text)
			return(ty+row*lung_char_n);
	 else
			return(ty+3+row*(LINE_SPACE+(lung_char_n+LINE_SPACE)));
};

/********************************************/

void GWindow::GWGoto(int row, int col)
{
// uint lat,lung;

// if(mode_text)
// {
// lat  = 1;
// lung = 1;
// }
// else
// {
// lat  = textwidth(" ");
// lung = textheight("H")+LINE_SPACE;
// }
 if((row<=nrows)&&(col<=ncols))
	 if(mode_text)
			mgotoxy(tx+col*lat_char_n,ty+row*lung_char_n);
	 else
//		moveto(tx+COL_SPACE+col*lat,ty+3+row*(LINE_SPACE+lung));
			if(row)
				moveto(tx+col*lat_char_n,ty+3+row*(LINE_SPACE+(lung_char_n+LINE_SPACE)));
//				moveto(tx+col*lat_char_n,ty+3+row*((lung_char_n+LINE_SPACE)));
			else
				moveto(tx+col*lat_char_n,ty+3+row*(LINE_SPACE+(lung_char_n+LINE_SPACE)));

};

/********************************************/
void GWindow::GWPutch(int row, int col, char c)
{
 char ch[2];

 ch[0]=c;
 ch[1]=0;

 if((row<nrows)&&(col<ncols-1))
	{
	 hide_pointer();
	 GWGoto(row, col);
	 if(mode_text)
		 mputch(c);
	 else
		 outtext(ch);
	 display_pointer();
	}
};


/********************************************/
void GWindow::GWPuts(int row, int col, int width, char *st, int bkgnd, int frgnd)
{
// int i,lat,lung;
// char ch[2];
// ch[1]=0;

// this->GWGoto(row,col);
// hide_pointer();
 if(strlen(st)>(ncols-col+1))
	{
	}
 else
	 if(mode_text)
	 {
		 mxyputs(GWx(col),GWy(row),st,bkgnd,frgnd);
	 }
	 else
		{
		 setfillstyle(SOLID_FILL,bkgnd);
		 bar(tx+col*lat_char_n,ty + 3+row*(2*LINE_SPACE+lung_char_n), tx+col*lat_char_n+width*lat_char_n, ty + 3+row*(2*LINE_SPACE+lung_char_n)+lung_char_n+1);
//		 bar(tx+col*lat_char_n,ty+3+row*(LINE_SPACE+(lung_char_n+LINE_SPACE)), tx+col*lat_char_n+width*lat_char_n, ty+3+row*(LINE_SPACE+(lung_char_n+LINE_SPACE))+lung_char_n);
		 setcolor(frgnd);
		 outtextxy(GWx(col),GWy(row),st);
		 if(doubleprint)
			 outtextxy(GWx(col)+1,GWy(row),st);
//		 put_text(st, GWx(col)/8, GWy(row)/16, bkgnd, frgnd);
		}
// display_pointer();

};

/********************************************/
void GWindow::GWPuts(int row, int col, char * st,int bkgnd, int frgnd)
{
// int i;
 char ch[2];
 ch[1]=0;

// GWGoto(row,col);
 hidecur();
// hide_pointer();
 if(strlen(st)>(ncols-col+1))
	{
			ch[0]=st[ncols-col];
			st[ncols-col] = 0;
			if(mode_text)
				mxyputs(GWx(col),GWy(row),st,bkgnd,frgnd);
			else
			{
			 setcolor(frgnd);
			 outtextxy(GWx(col),GWy(row),st);
			}
			st[ncols-col]=ch[0];
			this->GWGoto(row+1,0);
			if(mode_text)
				mxyputs(GWx(col),GWy(row)+1,&st[ncols-col],bkgnd,frgnd);
			else
			{
			 setcolor(frgnd);
			 outtext(&st[ncols-col]);
			}
//				settextstyle(2, 0, 0);
	 }
	else
	 if(mode_text)
	 {
		 mxyputs(GWx(col),GWy(row),st,bkgnd,frgnd);
	 }
	 else
		{
		 set_semaphore(&screen);
		 setfillstyle(SOLID_FILL,bkgnd);
		 bar(tx+col*lat_char_n,ty+3+row*(2*LINE_SPACE+lung_char_n), tx+col*lat_char_n+strlen(st)*lat_char_n, ty + 3+row*(2*LINE_SPACE+lung_char_n)+lung_char_n+1);
//		 bar(tx+col*lat_char_n,ty+3+row*(LINE_SPACE+(lung_char_n+LINE_SPACE)), tx+col*lat_char_n+strlen(st)*lat_char_n, ty+3+row*(LINE_SPACE+(lung_char_n+LINE_SPACE))+lung_char_n);
		 setcolor(frgnd);
		 outtextxy(GWx(col),GWy(row),st);
		 if(doubleprint)
			 outtextxy(GWx(col)+1,GWy(row),st);
		 clear_semaphore(&screen);
//		 put_text(st, GWx(col)/8, GWy(row)/16, bkgnd, frgnd);
		}

// display_pointer();

};


/*********************************************/

void GWindow::GReleaseWindow(void)
{
	hide_pointer();
	if (title)
	{
//	 mfarfree(title_handle);
	 mfarfree(title);
	 title = NULL;
	}
	if(mode_text)
	{
	 if(!flag)
		RestoreArea();
	}
	else
	{
	 RestoreArea();
	}
	on_screen=0;

	if(!NO_STK)
	 Control.Pop();

	hidecur();
	display_pointer();
};


/////////////////////////////
//                         //
//     Class GWControl     //
//                         //
/////////////////////////////


/********************************************/

int GWControl::GWHandleEvent()
{
 int j=0;

 do{
	 if (bioskey_new(1))                //kbhit())
		 {
			if(mouse_inside(Control.objects[level]->GWRetLimits(0),
					Control.objects[level]->GWRetLimits(1),
					Control.objects[level]->GWRetLimits(2),
					Control.objects[level]->GWRetLimits(3)))
							j = Control.objects[level]->HandleEvent();
		 }
	 else
							j = Control.objects[level]->HandleEvent();

	 }while(level>=0);

 return j;

};

/********************************************/
void *GWControl::GWActWindow()
{
 int j=0;

 for(j=0; j<=level ;j++)
 {
			if(mouse_inside(Control.objects[j]->GWRetLimits(0),
					Control.objects[j]->GWRetLimits(1),
					Control.objects[j]->GWRetLimits(2),
					Control.objects[j]->GWRetLimits(3)))
							return Control.objects[j];
 }
 return 0;

};
/*****************************************/

void GWControl::Push(GWindow * ptr)
{
 this->level++;
 this->objects[level]=ptr;
};

/******************************************/

void GWControl::Pop()
{
 (this->level)--;
};

/*****************************************/

///////////////////////////////
//                           //
//        GWDialog           //
//                           //
///////////////////////////////

GWDialog::GWDialog(int tx, int ty, int bx, int by, int stk, int but, int ftype, int csize, char dprint)
									 :GWindow(tx,ty,bx,by,stk,but,ftype,csize,dprint)
{
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.015  ********
// ********       begin       ********
// ***********************************
 Flag_help=IMPOTENT;
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.015  ********
// ********        end        ********
// ***********************************
index_cur=-1;
index_obj=0;
updown=first = 1;
nrobj=last_mouse=esc=exitCR=enter=ok=cancel=0;
nrok=nrcancel=-1;
ok_char='O';
cancel_char='C';
xok=3; xcancel=1;
}

// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.016  ********
// ********       begin       ********
// ***********************************
GWDialog::GWDialog(int flag_help,char *need_help,int tx, int ty, int bx, int by, int stk, int but, int ftype, int csize, char dprint)
									 :GWindow(tx,ty,bx,by,stk,but,ftype,csize,dprint)
{
Flag_help=flag_help;
index_cur=-1;
index_obj=0;
updown=first = 1;
nrobj=last_mouse=esc=exitCR=enter=ok=cancel=0;
nrok=nrcancel=-1;
ok_char='O';
cancel_char='C';
xok=3; xcancel=1;
}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.016  ********
// ********        end        ********
// ***********************************

/*GWDialog::GWDialog(uint tx, uint ty, uint bx, uint by, uint stk, uint Nrobj):
		GWindow(tx,ty,bx,by,stk)
{
index_cur=-1;
index_obj=0;
updown=first = 1;
last_mouse=esc=0;
nrobj=(char)Nrobj;

if ((objects=(struct objects *)farmalloc(nrobj*sizeof(struct objects)))==NULL)
	 {
	 printf("Error allocation GWDialog for objects");
	 exit(1);
	 }
};
*/
GWDialog::~GWDialog()
{
 if (index_obj)
	 for(int i=0;i<index_obj;i++)
//			 mfarfree( handle_obj[i]);
	 {
		 if( objects[i] )
			 mfarfree( objects[i] );
	 }
}

void GWDialog::GDDef_object(void (*f)(GWDialog *), int lx, int ly, int width, char bkgnd, char frgnd, char *ptr, char sbkgnd, char sfrgnd, char *sablon,
									 signed char ok_cancel, char ok_cancel_char, char xokcancel)
{
 int lat,lung;
 if(mode_text)
 {
// lat=lung=1;
 }
 else
 {
//	settextstyle(2, 0, 0);
// lat=textwidth(" ");
// lung=textheight("H")+LINE_SPACE;
 }

//mfarmalloc((char far **)&objects[index_obj], (unsigned long)sizeof(struct objects), handle_obj[index_obj]);
 mfarmalloc((char far **)&objects[index_obj], (unsigned long)sizeof(struct objects));
 if (objects[index_obj]==NULL)
//if ((objects[index_obj]=(struct objects *)farmalloc(sizeof(struct objects)))==NULL)
 {
	 printf("Error allocation GWDialog for objects");
	 exit(1);
 }

 objects[index_obj]->f=f;
 objects[index_obj]->ptr=ptr;
 objects[index_obj]->sablon=sablon;
 objects[index_obj]->xrel = lx;
 objects[index_obj]->yrel = ly;
 objects[index_obj]->box.top.x=tx+lx*lat_char_n;
// objects[index_obj]->box.top.y=ty+(mode_text?0:3+2)+ly*(lung_char_n+LINE_SPACE+LINE_SPACE);
 objects[index_obj]->box.top.y=ty+(mode_text?0:3)+ly*(lung_char_n+LINE_SPACE+LINE_SPACE);
// objects[index_obj]->box.bot.x=tx+(lx+width-1)*lat_char_n;
 objects[index_obj]->box.bot.x=tx+(lx+width-(mode_text?1:0))*lat_char_n;
// objects[index_obj]->box.bot.y=ty+(mode_text?0:3+2)+ly*(lung_char_n+LINE_SPACE+LINE_SPACE)+(mode_text?0:lung_char_n+LINE_SPACE-LINE_SPACE);
 objects[index_obj]->box.bot.y=ty+(mode_text?0:3+2)+ly*(lung_char_n+LINE_SPACE+LINE_SPACE)+(mode_text?0:lung_char_n+LINE_SPACE-LINE_SPACE);
 objects[index_obj]->width=width;
 objects[index_obj]->bkgnd=bkgnd;
 objects[index_obj]->frgnd=frgnd;
 objects[index_obj]->sbkgnd=sbkgnd;
 objects[index_obj]->sfrgnd=sfrgnd;
 index_cur=index_obj++;

 if(!f && ptr)
 {
	hide_pointer();
	if(!ok_cancel)
	{
	 nrok=index_cur;
	 ok_char = ok_cancel_char;
	 xok = xokcancel;
	}
	if(ok_cancel==1)
	{
	 nrcancel=index_cur;
	 cancel_char = ok_cancel_char;
	 xcancel = xokcancel;
	}
	if(mode_text)
	{
	 lin_text[width]=0;
	 mxyputs(objects[index_cur]->box.top.x,objects[index_cur]->box.top.y,lin_text,bkgnd,frgnd);
	 lin_text[width]=lin_text[0];
	 mxyputs(objects[index_cur]->box.top.x,objects[index_cur]->box.top.y,ptr,bkgnd,frgnd);
	 if(!ok_cancel || ok_cancel==1)
		 if(mode_text)
			moutchar(objects[index_cur]->box.top.x+xokcancel,objects[index_cur]->box.top.y,ok_cancel_char,bkgnd,White); //Lightred
	}
	else
	{
//	 setfillstyle(SOLID_FILL, bkgnd);
//	 bar(objects[index_cur]->box.top.x,objects[index_cur]->box.top.y,objects[index_obj]->box.bot.x,objects[index_obj]->box.bot.y);
//	 moveto(objects[index_cur]->box.top.x,objects[index_cur]->box.top.y);
	 GWPuts(ly, lx, width, ptr, bkgnd, frgnd);
//	 setcolor(frgnd);
//	 outtextxy(objects[index_cur]->box.top.x,objects[index_cur]->box.top.y,ptr);
	}
	display_pointer();
 }
}

int GWDialog::Select()
{
 int i;
 select=1;
 while(!(i=HandleEvent()));
 select=0;
 return i-1;
};

/***********************************/

int GWDialog::HandleEvent()
{
	union {
		int i;
		char ch[2];
		} key;
 int lat,lung;
 MouseStatus stat;
 if(mode_text)
	 lat=lung=1;
 else
	{
	 lat=textwidth(" ");
	 lung=textheight("H")+2*LINE_SPACE;
	}
 key.i = -1;
 while(1)
 {
 if (bioskey_new(1) || first)
 {
	if(!first)
	{
		key.i = bioskey_new(0);
// ********  the old code  ********
//		if (key.ch[0]==0)  key.ch[0]=key.ch[1];
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.017  ********
// ********       begin       ********
// ***********************************
		if (key.ch[0]==0)
		{
			key.ch[0]=key.ch[1];
			if (key.ch[0]==F1KEY)
			{
				T3000help(Flag_help);
			}
		}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.017  ********
// ********        end        ********
// ***********************************
	}
	else
	{
		 if(enter==2)
		 {
         enter = 1;
			if(objects[index_cur]->f)
				key.ch[0]=13;
		 }
	}

//	GGHideCur(Black);
	if (esc || key.ch[0]==27 || ok || cancel)  //esc
	{
	 GReleaseWindow();
	 return 1;
	}
// CHANGE FEB 97
	if(!index_obj)
		first = 0;
	else
	if ( (key.ch[0]==13 && enter) || key.ch[0]=='\t' || key.ch[0]==DOWN || key.ch[0]==UP ||
			key.ch[0]==LEFT || key.ch[0]==RIGHT || key.ch[0]==ok_char || key.ch[0]==cancel_char || first )  //tab
	{
	 first = 0;
	 last_mouse=0;
	 if(key.ch[0]!=13)
	 {
		if(enter)
		{
		 updown = 2;
		 if (key.ch[0]==DOWN || key.ch[0]==RIGHT) updown=1;
		 if (key.ch[0]== UP || key.ch[0]==LEFT) updown=0;
		 last = 13;
		}
		hide_pointer();
		chbkg(objects[index_cur]->box.top.x,objects[index_cur]->box.top.y, objects[index_cur]->width*lat, objects[index_cur]->bkgnd, objects[index_cur]->frgnd,127,mode_text ? 0 : textheight("H")+2);  //Lightred
		if( index_cur==nrok || index_cur==nrcancel)
		 if(mode_text)
			moutchar(objects[index_cur]->box.top.x+(index_cur==nrok?xok:xcancel),objects[index_cur]->box.top.y,(index_cur==nrok?ok_char:cancel_char),objects[index_cur]->bkgnd,White); //Lightred
		if (updown==1)
		 index_cur++;
		if (updown==0)
		 index_cur--;
		if (index_cur>=index_obj) index_cur=0;
		if (index_cur<0) index_cur=index_obj-1;
		if (key.ch[0]==ok_char && nrok>=0) index_cur=nrok;
		if (key.ch[0]==cancel_char && nrcancel>=0) index_cur=nrcancel;
		chbkg(objects[index_cur]->box.top.x,objects[index_cur]->box.top.y, objects[index_cur]->width*lat, objects[index_cur]->bkgnd, White,127,mode_text ? 0 : textheight("H")+2);  //Lightred
		if( index_cur==nrok || index_cur==nrcancel)
		 if(mode_text)
			moutchar(objects[index_cur]->box.top.x+(index_cur==nrok?xok:xcancel),objects[index_cur]->box.top.y,(index_cur==nrok?ok_char:cancel_char),objects[index_cur]->bkgnd,Lightred);
		display_pointer();
	 }

	 if(key.ch[0]==13||key.ch[0]==ok_char||key.ch[0]==cancel_char)
	 {
		if(index_cur==nrok) {ok=1;first=1;continue;}
		if(index_cur==nrcancel) {cancel=1;first=1;continue;}
	 }
	 if(!enter || (key.ch[0]==13 && enter) )
	 {
		if(index_cur!=nrok && index_cur!=nrcancel)
		{
			if(objects[index_cur]->f)
				 objects[index_cur]->f(this);
			else
			{
			 if(objects[index_cur]->sablon)
				 GDGetsablon(objects[index_cur]->ptr, objects[index_cur]->yrel, objects[index_cur]->xrel, objects[index_cur]->width,objects[index_cur]->sbkgnd,objects[index_cur]->sfrgnd,objects[index_cur]->sablon);
			 else
				 GDGets(objects[index_cur]->ptr, objects[index_cur]->yrel, objects[index_cur]->xrel, objects[index_cur]->width,objects[index_cur]->sbkgnd,objects[index_cur]->sfrgnd);
			}
		}
//		else
//		 GDGet(objects[index_cur]->ptr, objects[index_cur]->yrel, objects[index_cur]->xrel, objects[index_cur]->width,objects[index_cur]->sbkgnd,objects[index_cur]->sfrgnd,'E');

		if(enter)
		 last = 13;
	 }
//  feb 97
	 else
	 {
		chbkg(objects[index_cur]->box.top.x,objects[index_cur]->box.top.y, objects[index_cur]->width*lat, objects[index_cur]->sbkgnd,objects[index_cur]->sfrgnd,127,mode_text ? 0 : textheight("H")+2);  //Lightred
	 }

	 if (last == '\t' || last == DOWN || last == RIGHT) {updown=1;first = 1;}
	 if (last == UP || last == LEFT) {updown=0;first = 1;}   //up
	 if (last == 0) last_mouse = 1;
	 if (last == 27) esc = 1;
	 if (last==13 && (select || (exitCR && index_cur == index_obj-1)))
	 {
			 GReleaseWindow();
			 return index_cur+1+1;
	 }
	 else
	 {
			if(!enter)
				if (last==13) {updown=1;first = 1;}
			hide_pointer();
// feb 97
//			chbkg(objects[index_cur]->box.top.x,objects[index_cur]->box.top.y, objects[index_cur]->width*lat, objects[index_cur]->bkgnd, White); //Lightred
			chbkg(objects[index_cur]->box.top.x,objects[index_cur]->box.top.y, objects[index_cur]->width*lat, objects[index_cur]->sbkgnd, objects[index_cur]->sfrgnd,127,mode_text ? 0 : textheight("H")+2); //Lightred
			if( index_cur==nrok || index_cur==nrcancel)
			 if(mode_text)
			   moutchar(objects[index_cur]->box.top.x+(index_cur==nrok?xok:xcancel),objects[index_cur]->box.top.y,(index_cur==nrok?ok_char:cancel_char),objects[index_cur]->bkgnd,Lightred);
			display_pointer();
	 }

	 if (last == 77 && select)
	 {
/*
				 chbkg(objects[index_cur]->box.top.x,objects[index_cur]->box.top.y, objects[index_cur]->width*lat, objects[index_cur]->bkgnd, objects[index_cur]->frgnd);
				 index_cur += 15;
				 if (index_cur>=index_obj) index_cur=index_obj-1;
				 updown = 1;
				 first = 1;
*/
	 }
	 if (last == 75 && select)
	 {
/*
				 chbkg(objects[index_cur]->box.top.x,objects[index_cur]->box.top.y, objects[index_cur]->width*lat, objects[index_cur]->bkgnd, objects[index_cur]->frgnd);
				 index_cur -= 15;
				 if (index_cur<0) index_cur=0;
				 updown = 0;
				 first = 1;
*/
	 }
	}
 }
 mouse_status(stat);
 if(stat.leftButton  || esc)
 {
  if(mouse_inside(close_spot.top.x,
		 close_spot.top.y,
		 close_spot.bot.x,
		 close_spot.bot.y) || esc )
		{
			mouse_status(stat);
			if(stat.leftButton || esc || last_mouse)
			 {
			  if(stat.leftButton)
				 while(!get_button_released(BLEFT,stat));
			  GReleaseWindow();
				return 1;
			 }
		}
 }
// i=0;
 if(stat.leftButton || last_mouse)
 {
  for(int i=0;i<index_obj;i++)
  {
	if(mouse_inside(objects[i]->box.top.x,
		 objects[i]->box.top.y,
//		 objects[i]->box.bot.x+objects[i]->width-1,
		 objects[i]->box.bot.x,
		 objects[i]->box.bot.y))
	{
			mouse_status(stat);
			if(stat.leftButton || last_mouse)
			 {
			  if(stat.leftButton)
				 while(!get_button_released(BLEFT,stat));
			  first = 1;
			  chbkg(objects[index_cur]->box.top.x,objects[index_cur]->box.top.y, objects[index_cur]->width*lat, objects[index_cur]->bkgnd, objects[index_cur]->frgnd,127,mode_text ? 0 : textheight("H")+2); //Lightred
			  if( index_cur==nrok || index_cur==nrcancel)
				 if(mode_text)
					moutchar(objects[index_cur]->box.top.x+(index_cur==nrok?xok:xcancel),objects[index_cur]->box.top.y,(index_cur==nrok?ok_char:cancel_char),objects[index_cur]->bkgnd,White);
			  if(index_cur==i)
			  {
				if(index_cur==nrok) ok=1;
				if(index_cur==nrcancel) cancel=1;
				key.ch[0]=13;
			  }
			  else
			  {
				index_cur = i-1;
				key.ch[0] = DOWN;
			  }
			  if (index_cur>=index_obj) index_cur=0;
			  if (index_cur<0) index_cur=index_obj-1;
			  break;
			 }
	}
  }
  last_mouse = 0;
  if(stat.leftButton)
	 while(!get_button_released(BLEFT,stat));
 }
 if(first) continue;
 return 0;
}
}

/***********************************/

void GWDialog::GDPuts(int row, int col,
					char * mes, int width,
					int bkgnd, int frgnd)
{
 uint colour,length,i;

 hide_pointer();
 GWGoto(row,col);
 if(mode_text)
 {
 length=strlen(mes);
// mtextbackground(bkgnd);
// mtextcolor(frgnd);
 chbkg(tx+col,ty+row, width, bkgnd, bkgnd);
 GWPuts(row,col,mes,bkgnd,frgnd);
 }
 else
 {
 struct fillsettingstype fill;

 getfillsettings(&fill);
 colour=getcolor();
 length=textwidth(mes);

 setfillstyle(SOLID_FILL,bkgnd);

/*
 if(strlen(mes)<=(ncols-col))
//	 bar(getx()-2,gety()-2,getx()+width+2,gety()+textheight("H")+2);
	 bar(getx(),gety(),getx()+width,gety()+textheight("H"));

 else
 {
	bar(getx(),gety()-2,bx-2,gety()+textheight("H")+2);
	i=2+(strlen(mes)-ncols+col)/ncols;
	bar(tx+2,gety()+textheight("H")+2,bx-2,
			gety()+(textheight("H")+2)*i);
	}
*/
 setcolor(frgnd);
 GWPuts(row,col,mes,bkgnd,frgnd);
 setfillstyle(fill.pattern, fill.color);
 setcolor(colour);
 }

 display_pointer();

};


/*****************************************/

void GWDialog::GDGet (char far * ptr,
					int row,   int col, int width,
					int bkgnd, int frgnd,
					int which_type, char *sablon)

{
 struct fillsettingstype fill;
 uint colour,length,i;
// int lat;
// int lung;
 char space[50]="                                                  ";
 hide_pointer();
// if(!mode_text)
//	{
//	 lat=textwidth(" ");
//	 lung=textheight("H");
//	}
 GWGoto(row,col);

 if(mode_text)
 {
	chbkg(objects[index_cur]->box.top.x,objects[index_cur]->box.top.y, width, bkgnd, bkgnd);
	GWPuts(row,col,ptr,bkgnd,frgnd);
	GWGoto(row,col);
	select_tmp = select;
// ********  the old code  ********
//	last=wingets(ptr, GWy(row), GWx(col), width, bkgnd, frgnd, which_type,sablon, retnokey);
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.018  ********
// ********       begin       ********
// ***********************************
	last=wingets_help(Flag_help,ptr, GWy(row), GWx(col), width, bkgnd, frgnd, which_type,sablon, retnokey);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.018  ********
// ********        end        ********
// ***********************************
	select_tmp = 0;
//// chbkg(objects[index_cur]->box.top.x,objects[index_cur]->box.top.y, width, Lightgray, Black);

 }
 else
 {
	setfillstyle(SOLID_FILL,bkgnd);
	setcolor(frgnd);
// ptr[0]=0;
	select_tmp = select;
// ********  the old code  ********
//	last=wingets(ptr, GWy(row), GWx(col), width, bkgnd, frgnd, which_type,sablon,retnokey);
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.019  ********
// ********       begin       ********
// ***********************************
	last=wingets_help(Flag_help,ptr, GWy(row), GWx(col), width, bkgnd, frgnd, which_type,sablon,retnokey);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.019  ********
// ********        end        ********
// ***********************************
select_tmp = 0;
// chbkg(tx+col*lat_char_n,ty + (row ? 3+row*(2*LINE_SPACE+lung_char_n)+2+2:3+2), width*lat_char_n, Lightgray, Black);
 }
 display_pointer();


};

void chbkg(int lx, int ly, int width, int bkgnd, int frgnd, int unchangecol, int height)
{
 char buf[200];
 char c,col,b,f;
 int i,j;
 if(mode_text)
 {
	mgettext(lx,ly, lx + width - 1, ly, buf);
	for(i=0;i<width;i++)
	 {
		col=buf[2*i+1] & '\x0F';
		if(col==buf[2*i+1]/16)	buf[2*i+1]=bkgnd*16+bkgnd;
		else
			{
			 if (frgnd==-1 || col==unchangecol)
				  buf[2*i+1] = bkgnd*16 + col;
			 else
				  buf[2*i+1] = bkgnd*16 + frgnd;
		 }
	 }
 mputtext(lx,ly, lx + width - 1, ly, buf);
 }
 else
 {
// set_semaphore(&screen);
	 b=bkgnd;
	 f=frgnd;
//	 char line[730];
	 asm {
				mov ah,0dh
				mov bh,0
				mov dx,ly
				mov cx,lx
				int 10h
		  }
	 col=_AL;
//	 for(i=ly-2; i<=ly+(height?height:textheight("H"));i++)
	 for(i=ly; i<ly+(height?height:textheight("H"));i++)
	 {
/*		for(j=lx; j<=lx+width;j++)
		{
			asm {
				mov ah,0dh
				mov bh,0
				mov dx,i
				mov cx,j
				int 10h
				cmp al,col
				jz c1
				mov al,f
				jmp c2
				}
c1:
asm     mov al,b
c2:
asm 		mov ah,0ch
asm				int 10h
*/
			 get_pixels_12( (char *)linebuf , width, lx, i);
			 for(j=0;j<width;j++)
				if(linebuf[j]==col) linebuf[j]=bkgnd;
				else
					 if(frgnd!=-1) linebuf[j]=frgnd;
			 put_pixels_12( (char *)linebuf ,width, lx, i);
	 }
//	clear_semaphore(&screen);
 }
}

void GWDialog::GDGetsablon (char far * ptr,
					int row,   int col, int width,
					int bkgnd, int frgnd, char *sablon)
{
 GDGet(ptr, row, col, width, bkgnd, frgnd, 'S', sablon);
};

/***********************************/

void GWDialog::GDGets (char far * ptr,
					int row,   int col, int width,
					int bkgnd, int frgnd)
{
 GDGet(ptr, row, col, width, bkgnd, frgnd, 'A');
}

/***********************************/

/***********************************/

void GWDialog::GDGetn (char far * ptr,
					int row,   int col, int width,
					int bkgnd, int frgnd)
{
 GDGet(ptr, row, col, width, bkgnd, frgnd, 'N');
};

double GWDialog::GDGetd ( int row,   int col, int width,
				int bkgnd, int frgnd)
{
 char ptr[15];
 GDGet(ptr, row, col, width, bkgnd, frgnd, 'N');
 return atof(ptr);
};

/************************************/

//////////////////////////////////////////
//                                      //
//  Functia afisare mesaje de eroare    //
//                                      //
//////////////////////////////////////////

void DisplayError(int lx, int ly, int rx, int ry, char *message,int bkgnd, int frgnd, int tbkgnd, int fcolor=Black)
{
 int ftype,csize;
/*
 ftype=font_type;csize=charsize;
 if(!mode_text)
 {
	if( font_type!=DEFAULT_FONT )
		msettextstyle(DEFAULT_FONT, HORIZ_DIR,1);
 }
*/
 GWindow *Er = new GWindow(lx,ly,rx,ry,NO_STACK,0);
 Er->GWSet(NULL,bkgnd,tbkgnd,fcolor);
 Er->GShowWindow(WIN_ERROR);
 Er->GWPuts(2,(Er->GMaxCols()-strlen(message))/2, message, Lightgray,frgnd);
 while(!Er->HandleEvent());
 delete Er;
/*
 if(!mode_text)
	 if( ftype!=DEFAULT_FONT )
		msettextstyle(ftype, HORIZ_DIR, csize);
*/
}

void DisplayError(char * message)
{
 int ftype,csize;
/*
 ftype=font_type;csize=charsize;
 if(!mode_text)
 {
	if( font_type!=DEFAULT_FONT )
		msettextstyle(DEFAULT_FONT, HORIZ_DIR,1);
 }
*/
 GWDialog Er(150,100,450,180,NO_STACK,0);
 Er.GWSet("ERROR!",Lightgreen,Green);

 Er.GShowWindow(0);

 uint tx,ty,bx,by;

 if(strlen(message)>Er.GMaxCols())

	Er.GDPuts(2,0,message,100,Yellow,Black);

 else

	Er.GDPuts(2,(Er.GMaxCols()-strlen(message))/2,message, 100,Yellow,Black);

 while(!Er.HandleEvent());
/*
 if(!mode_text)
	 if( ftype!=DEFAULT_FONT )
		msettextstyle(ftype, HORIZ_DIR, csize);
*/
}

GWDialog *DisplayMessage(int lx, int ly, int rx, int ry, char *message, GWDialog **Er, int fcolor=Black)
{
 int ftype,csize;
/*
 ftype=font_type;csize=charsize;
 if(!mode_text)
 {
	if( font_type!=DEFAULT_FONT )
		msettextstyle(DEFAULT_FONT, HORIZ_DIR,1);
 }
*/
 *Er = new GWDialog(lx,ly,rx,ry,NO_STACK,0);
 (*Er)->GWSet(NULL,Lightblue,Blue,fcolor);

 (*Er)->GShowWindow(WIN_ERROR);

 if(strlen(message)>(*Er)->GMaxCols())

	(*Er)->GDPuts(2,0,message,100,Blue,White);

 else

//	(*Er)->GDPuts((mode_text?0:1),((*Er)->GMaxCols()-strlen(message))/2,message, strlen(message),Lightblue,Black);
	(*Er)->GDPuts((mode_text?0:1),0,message, strlen(message),Lightblue,Black);
/*
 if(!mode_text)
	 if( ftype!=DEFAULT_FONT )
		msettextstyle(ftype, HORIZ_DIR, csize);
*/
}

void DeleteMessage(GWDialog *p)
{
 p->GReleaseWindow();
// set_semaphore_dos();
 delete p;
// clear_semaphore_dos();
}

void DisplayMessage(int lx, int ly, int rx, int ry, char *title, char *message, GWindow **Er1, int fcolor=Black, GWindow *Er2=NULL, long delay=0)
{
 GWindow *Er;
// int ftype,csize;
// ftype=font_type;csize=charsize;

 int x;
/*
 if(!mode_text)
 {
//	 gettextsettings(&textinfo);
	if( font_type!=DEFAULT_FONT )
		msettextstyle(DEFAULT_FONT, HORIZ_DIR,1);
 }
*/
 if(Er1)
 {
//	set_semaphore_dos();
	*Er1 = new GWindow(lx,ly,rx,ry,NO_STACK,0);
//	clear_semaphore_dos();
	Er = *Er1;
 }
 else
	if(Er2)
	{
	 Er = Er2;
	}
	else
	{
	 Er = new GWindow(lx,ly,rx,ry,NO_STACK,0);
	 if(!delay) delay = 200;
	}

 (Er)->GWSet(title,Lightblue,Blue,fcolor);

 (Er)->GShowWindow(WIN_ERROR);

 x = ((Er)->GMaxCols()-strlen(message))/2;
 if(!delay)
 {
	ysign = (Er)->GWRetLimits(5)+(mode_text?1:20);
  xsign = x;
 }
 if(strlen(message)>(Er)->GMaxCols())

	(Er)->GWPuts(1, 1, message, Lightblue,fcolor);

 else

//	(*Er)->GDPuts((mode_text?0:1),((*Er)->GMaxCols()-strlen(message))/2,message, strlen(message),Lightblue,Black);
	(Er)->GWPuts(1, x, message, Lightblue,Black);

 if(!delay)
 {
	if(!mode_text) xsign <<= 3;
	xsign += (Er)->GWRetLimits(4)+(strlen(message)-3)*(mode_text?1:8);
	data_const=data_length_const=0;
 }

/*
 if(!mode_text)
	 if( ftype!=DEFAULT_FONT )
		msettextstyle(ftype, HORIZ_DIR, csize);
*/

 if(delay>0)
 {
	if(!title)
	{
	 Delay(delay);
   worktime=0;
	}
	else
	{
	 worktime = delay/55;
  }
	while(!Er->HandleEvent() && worktime);
	Er->GReleaseWindow();
	delete Er;
	if(Er1)
		*Er1 = NULL;
 }
 if(delay<0)
 {
	while(!Er->HandleEvent());
	Er->GReleaseWindow();
	delete Er;
	if(Er1)
		*Er1 = NULL;
 }
}

void DisplayMessageT(int lx, int ly, int rx, int ry, char *title, char *message, GWindow **Er1, int fcolor=Black, GWindow *Er2=NULL, long delay=0)
{
 if(!mode_text)
 {
	lx *= 8;
	rx *= 8;
	ry = ly*19 + (ry-ly)*10 + 20;
	ly *= 19;
 }
 DisplayMessage(lx,ly,rx,ry,title,message,Er1,fcolor,Er2,delay);
}
void DeleteMessage(GWindow *p)
{
 if(p)
 {
	p->GReleaseWindow();
	delete p;
 }
}

void put_text(char *p, char x, char y, int bkgnd, int frgnd)
{
	_BL = (bkgnd << 4) + frgnd;
	_CX = strlen(p);
	_DH = y;
	_DL = x;
	_ES = FP_SEG(p);
	_BP = FP_OFF(p);
	asm{
	 mov ah,13h
	 mov bh,0
	 mov al,1
	 int 10h
	 }
}

int height_char_size(void)
{
	return (textheight("H"));
}

int width_char_size(void)
{
	return (textwidth(" "));
}

