///////////////////////////////////////////////////////////
// Implements the member functions of the classes        //
//        GMenuBar and GPopUp                            //
///////////////////////////////////////////////////////////

#include <graphics.h>
#include "gmbar.h"
#include "keys.h"
#include "t3000def.h"
#include "mtkernel.h"
#include "T3000hlp.h"
#define LINE_SPACE (mode_text ? 0 : 4)

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
#define ESC  27
#define ALT   0x08
#define CTRL  0x04

#define F1KEY  59
#define F2KEY  60
#define F3KEY  61
#define F4KEY  62
#define F5KEY  63
#define F6KEY  64
#define F7KEY  65
#define F8KEY  66
#define F9KEY  67
#define F10KEY  68
#define F11KEY  69
#define F12KEY  70

//GPopUp PPtab[11];    // table for holding the initialized popups
extern int print_alarm_word(void);
extern void getkey(void);
extern int bioskey_new(int cmd);
extern void memsize(void);
void DisplayError(char * message);
extern void chbkg(int lx, int ly, int width, int bkgnd, int frgnd, int unchangecol=127, int height = 0);
extern void Bordergr(int ltopx, int ltopy, int rbottomx, int rbottomy, int colour, int bkgnd, int bcolour,int butcol, int how, int out);
extern void msettextstyle(int font, int dir, int chars);
extern int mode_text;
extern int maxx, maxy;
extern int dxscreen, dyscreen;
extern int Cyan;                   //3
extern int Lightblue;         //7
extern int Darkgray;         //7

char huge *lin_menu_full     ="€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€";
extern char *lin_text;
char huge *lin_menu = lin_text;
char huge *lin_hor      ="ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ";
char huge *lin_ver      ="≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥≥";

char huge *twospace="  ";

extern int lat_char_n, lung_char_n;
extern char array_access_level[70];
extern char access_level;
int m_move;
//                    A         P          S         I         L        'X'
char altkey[20][2]={{0x1E,27},{0x19,21},{0x1F,20},{0x17,22},{0x26,9},{0x2D,8},
										{0x18,23},{0x2F,24},{0x11,26},{0x2E,25},{0x15,28},{0x32,30},
										{0x14,31},{0x31,34}};
//										O          V         W      C
/************Constructor**************/

GMenuBar::GMenuBar(uint ltx,uint lty, uint rbx,uint rby,
				int cfond ,int cfrg, int chigh, int max, int type,
				char huge ***plist, int ffont, int cchar_size, char d_print)
				:GView(ltx,lty,rbx,rby)
{
 font = ffont;
 char_size = cchar_size;
 double_print=d_print;
 selectbkgcolour = Lightblue;
 fond=(int)cfond;
 frg=(int)cfrg;
 highlight=(int)chigh;
 type_menu = type;
 nrmax=max;
 list = plist;
 if (type_menu!=BARMENU)
	 pGPopUpTable = new GPopUp[nrmax];

 actnr=-1;
 for (int i=0;i<11;i++)
		hotletter[i]=0;
 munder=NULL;
 set_popup = 0;
 nrcur=0;
};

/*************************************************/

GMenuBar::~GMenuBar()
{
 if (type_menu!=BARMENU)
	 delete pGPopUpTable;
 if( munder ) mfarfree(munder_handle);
};

/************************************/

void GMenuBar::GShowMenuBar(char huge **message, int *onscreen)
{
 char *tilda,c;
 char hotchar[2];
 char huge **mes;
 char *aux;
 uint x,y,wide=0,i=0;

 mes =message;

 if (!under1)
 {
	 SaveArea();
 }

 if(mode_text)
 {
	hide_pointer();
	lin_menu[rbottom.x-ltop.x+1]=0;
	mxyputs(ltop.x,ltop.y,lin_menu,fond,fond);
	lin_menu[rbottom.x-ltop.x+1]=lin_menu[0];
	x = ltop.x; y = ltop.y;
// mgotoxy(ltop.x,ltop.y);
 }
 else
 {
	setfillstyle(SOLID_FILL,fond);

	hide_pointer();
// setcolor(fond);
	bar(ltop.x,ltop.y,rbottom.x,rbottom.y);
// setcolor( Black);
	prectangle(ltop.x,ltop.y,rbottom.x,rbottom.y, Black);
	pline(ltop.x+1,rbottom.y-1,rbottom.x-1,rbottom.y-1, Black);
	pline(rbottom.x-1,ltop.y+1,rbottom.x-1,rbottom.y-1, Black);
// setcolor( White);
	pline(ltop.x+1,ltop.y+1,rbottom.x-1,ltop.y+1, White);
	pline(ltop.x+1,ltop.y+1,ltop.x+1,rbottom.y-1, White);

// settextstyle(DEFAULT_FONT,HORIZ_DIR,1);

// setcolor( Black);
	moveto(ltop.x+2,ltop.y+6);
	x = ltop.x+2;
	if( font != DEFAULT_FONT )
	 y = ltop.y+5;
	else
	 y = ltop.y+8;
	msettextstyle(font, 0, char_size);
	text_height = textheight("H");
 }
// while((*mes!=NULL)&&(wide<getmaxx())&&(i<11))
 while((*mes!=NULL)&&(i<nrmax))
 {
	 if (mode_text)
	 {
		mxyputs(x,y,twospace,fond,frg);
		x += strlen(twospace);
		wide+=2;
	 }
	 else
	 {
		setcolor(frg);
		outtextxy(x,y,"  ");
		wide += strlen(twospace)*lat_char_n;
		x += strlen(twospace)*lat_char_n;
	 }

	 table[i].top.y=ltop.y;
	 if (mode_text)
	 {
		 table[i].top.x=ltop.x+wide;
		 table[i].bot.x=ltop.x+wide+strlen(*mes)-2;
	 }
	 else
	 {
			table[i].top.x=ltop.x+2+wide;
		 table[i].bot.x=ltop.x+2+wide+textwidth(*mes)-lat_char_n;
	 }
	 table[i].bot.y=rbottom.y;

	 hooks[i].x=table[i].top.x;
	 hooks[i].y=table[i].bot.y;

	 if (mode_text)
		 wide+=(strlen(*mes)-1);
	 else
		 wide+=(textwidth(*mes)-lat_char_n);

	 tilda=strchr(*mes,'~');
	 *tilda=0;

	 if(mode_text)
	 {
//		 mtextbackground(fond);
		 mxyputs(x,y,*mes,fond,frg);
		 x += strlen(*mes);
	 }
	 else
	 {
		 outtextxy(x,y,*mes);
		 if(double_print)
			 outtextxy(x+1,y,*mes);
		 x += strlen(*mes)*lat_char_n;
	 }

	 hotchar[0]=*(tilda+1);
	 hotletter[i]=hotchar[0];
	 hotchar[1]=0;
//	 setcolor(Lightgray);
	 if(mode_text)
	 {
		moutchar(x++,y,hotchar[0],fond,highlight);
		aux=tilda+2;
		mxyputs(x,y,aux,fond,frg);
		x += strlen(aux);
	 }
	 else
	 {
		setcolor(highlight);
		outtextxy(x,y,hotchar);
		if(double_print)
		 outtextxy(x+1,y,hotchar);
		x += strlen(hotchar)*lat_char_n;
		setcolor(frg);
		aux=tilda+2;
		outtextxy(x,y,aux);
		if(double_print)
		 outtextxy(x+1,y,aux);
		x += strlen(aux)*lat_char_n;
	}
	 *tilda='~';
	 mes++;
	 i++;
 }
// nrmax=i-1;
// if(mode_text)
//	chbkg(table[nrcur].top.x,table[nrcur].top.y + (mode_text ? 0 : 6), table[nrcur].bot.x-table[nrcur].top.x +1 , selectbkgcolour, -1, 127, textheight("H")+2);
 chbkg(table[nrcur].top.x,table[nrcur].top.y + (mode_text ? 0 : 6), table[nrcur].bot.x-table[nrcur].top.x +1 , selectbkgcolour, -1, 127, text_height+3);
//	 cursor(CYAN);

 if(!set_popup)
 {
	if (type_menu!=BARMENU)
	{
		for(int i=0;i<nrmax;i++)
		{
			pGPopUpTable[i].bar_menu=this;
			pGPopUpTable[i].SetPopUp(i,hooks[i].x, hooks[i].y, onscreen?onscreen[i]:0, font, char_size, double_print);
			pGPopUpTable[i].SetList(list[i]);
		}
	}
	set_popup=1;
 }
 display_pointer();

};

/*************************************************/

void GMenuBar::ReleaseMBar(void)
{
 RestoreArea();
 set_popup = 0;
/*
 if (type_menu!=BARMENU)
	 delete pGPopUpTable;
*/
 if( munder )
 {
	mfarfree(munder_handle);
	munder = NULL;
 }
};

void GMenuBar::HideMBar(void)
{
	int big;
	if(munder)
	{
	 mfarfree(munder_handle);
	}
	if(mode_text)
		big = (rbottom.x-ltop.x+1)*(rbottom.y-ltop.y+1)*2;
	else
	{
		big = mimagesize( ltop.x,ltop.y,rbottom.x,rbottom.y);
	}
	mfarmalloc(&munder, (unsigned long) big, munder_handle);
	if( munder==NULL )
	{
//		DisplayError("ERROR IN MEM ALLOCATION");
	}

	hide_pointer();    // hides the mouse cursor during reading
										// from the video memory
	if(mode_text)
	 mgettext(ltop.x, ltop.y, rbottom.x,rbottom.y,(void *)munder);
	else
	 mgetimage(ltop.x, ltop.y, rbottom.x,rbottom.y,(void *)munder);
  display_pointer(); //displays the mouse cursor after
};

void GMenuBar::DisplayMBar(void)
{
 hide_pointer();    // hides the mouse cursor during reading
										// from the video memory
 if(mode_text)
		mputtext(ltop.x,ltop.y, rbottom.x, rbottom.y,(void *)munder);
 else
		mputimage(ltop.x,ltop.y, (void *)munder,COPY_PUT);
 if( munder )
 {
	 mfarfree(munder_handle);
   munder=NULL;
 }
 display_pointer(); //displays the mouse cursor after
};

void GMenuBar::ShowunderMBar(void)
{
	hide_pointer();    // hides the mouse cursor during reading
	if(under1)
	 if(mode_text)
		mputtext(ltop.x,ltop.y, rbottom.x, rbottom.y,(void *)under1);
	 else
		mputimage(ltop.x, ltop.y, (void *)under1, COPY_PUT);
	display_pointer(); //displays the mouse cursor after
}

/*************************************************/

void far GMenuBar::HandleEvent(void)

{
 MouseStatus stat;
 int show,last=0;
 show=nrcur;
 do{
		 mouse_status(stat);
		 if (!mouse_inside(ltop.x,ltop.y,rbottom.x,rbottom.y))
		 {
				actnr=-3;
				return;
		 }
		 if (mouse_inside(rbottom.x-40,ltop.y,rbottom.x,rbottom.y))
		 {
				if(stat.leftButton)
				{
				 actnr=-4;
				 return;
				}
		 }
/*		 if(stat.leftButton)
			{
			 for (uint i=0; i<nrmax; i++)
			 if (mouse_inside(this->table[i].top.x,this->table[i].top.y,
						this->table[i].bot.x,this->table[i].bot.y))
			{
			 this->actnr=i;
			 i=nrmax;
			 return;
			}
			}
*/
		 for (uint i=0; i<nrmax; i++)
			 if (mouse_inside(this->table[i].top.x,this->table[i].top.y,
							this->table[i].bot.x,this->table[i].bot.y))
		 {
				int x=0,y=0;
				if(stat.leftButton)
				{
				 this->actnr=i;
				 i=nrmax;
				 return;
				}
				if(show!=i && mouse_motion(&x,&y))
				 {
//					printf("x y show  i %d  %d  %d  %d\n",x,y,show,i );
					show=i;
					hide_pointer();
					chbkg(table[nrcur].top.x,table[nrcur].top.y + (mode_text ? 0 : 6), table[nrcur].bot.x-table[nrcur].top.x +1  , fond, -1, 127, text_height+3);
//				 cursor(fond);
					nrcur=i;
					chbkg(table[nrcur].top.x,table[nrcur].top.y + (mode_text ? 0 : 6), table[nrcur].bot.x-table[nrcur].top.x +1  , selectbkgcolour, -1, 127, text_height+3);
					display_pointer();
					break;
				 }
		 }

		 print_alarm_word();
		}while(!bioskey_new(1));  //kbhit());

};


/*******************************************/

int GMenuBar::GReturn(void)
{
	union {
		int i;
		char ch[2];
		} key;
 char what;
 int rtvar,i,j=0;

 while(1)
 {
  if ( (key.i=bioskey_new(1)) )                //kbhit())
  {
	 if(key.i==-1)
	 {
		key.i=bioskey_new(0);
		return -2;
	 }
	 key.i=bioskey_new(0);
//	what=mgetch();
	 what=key.ch[0];
	 i=0;
	 if(what==ESC)
		return -2;
	 if(what==32)       // blank
		return -32;
	 if(what==0 || what==ENTER)
	 {
		 hide_pointer();
		 if (what==ENTER)
			{
			 if (type_menu==BARMENU)
				 rtvar = nrcur;
			 else
				 rtvar=select(nrcur);
			 actnr=-1;
			 display_pointer();
			 return rtvar;
			}
		else
//		 what=mgetch();
		 what=key.ch[1];
		 if (what==F10KEY)
			return F10KEY;
		 if (what==0x70)
		 {
			what = bioskey_new(2);
			if(	what&ALT && what&CTRL )	return 0x70;
			return -1;
		 }
		 if (what==0x71)   // CTRL/ALT-F10
		 {
			what = bioskey_new(2);
			if(	what&ALT && what&CTRL )	return 0x71;
			return -1;
		 }
		 if (what==DOWN)
			return DOWN;
		 if (what==UP)
			return UP;
		 if (what==RIGHT)   //right
		 {
//			 if(mode_text)
				 chbkg(table[nrcur].top.x,table[nrcur].top.y + (mode_text ? 0 : 6), table[nrcur].bot.x-table[nrcur].top.x +1  , fond, -1, 127, text_height+3);
//				 cursor(fond);
			 nrcur++;
			 if(nrcur>=nrmax) nrcur=0;
//			 if(mode_text)
				 chbkg(table[nrcur].top.x,table[nrcur].top.y + (mode_text ? 0 : 6), table[nrcur].bot.x-table[nrcur].top.x +1  , selectbkgcolour, -1, 127, text_height+3);
//			 move_mouse(table[nrcur].top.x+1,table[nrcur].top.y + (mode_text ? 0 : 5));
		 }
		 if (what==LEFT)
		 {
//			 if(mode_text)
				 chbkg(table[nrcur].top.x,table[nrcur].top.y + (mode_text ? 0 : 6), table[nrcur].bot.x-table[nrcur].top.x +1  , fond, -1, 127, text_height+3);
//				 cursor(fond);
			 nrcur--;
			 if(nrcur<0) nrcur=nrmax-1;
//			 if(mode_text)
				 chbkg(table[nrcur].top.x,table[nrcur].top.y + (mode_text ? 0 : 6), table[nrcur].bot.x-table[nrcur].top.x +1  , selectbkgcolour, -1, 127, text_height+3);
//			 move_mouse(table[nrcur].top.x+1,table[nrcur].top.y + (mode_text ? 0 : 5));
		 }
		 for(i=0;i<20;i++)
			 if(altkey[i][0]==what)
						 {
							 actnr=-1;
							 display_pointer();
							 return altkey[i][1];
						 }

	 }
	 else    // if what = 0
	 {
		while(i<26)
		{
			if (key.ch[0]==GKeys[i]) break;
			else i++;
		}

		if (i==26)
		{
			display_pointer();
			return -1;
		}
		while((j<nrmax)&&(hotletter[j]!=0))
		{
		 if(((0x41+i)==hotletter[j])||
			((0x61+i)==hotletter[j]))
		 {
			hide_pointer();
			chbkg(table[nrcur].top.x,table[nrcur].top.y + (mode_text ? 0 : 6), table[nrcur].bot.x-table[nrcur].top.x +1  , fond, -1, 127, text_height+3);
			nrcur=j;
			chbkg(table[nrcur].top.x,table[nrcur].top.y + (mode_text ? 0 : 6), table[nrcur].bot.x-table[nrcur].top.x +1  , selectbkgcolour, -1, 127, text_height+3);
			display_pointer();
			if (type_menu==BARMENU)
				rtvar=j;
			else
				rtvar=select(j);
			actnr=-1;
			display_pointer();
			return rtvar;
		 }
		 else j++;
		}
	 }   //if
	}
	else
	{
	 this->HandleEvent();
	 if(actnr==-3)
	 {
		 actnr=-1;
		 return -3;
	 }
	 if(actnr==-4)
	 {
		 actnr=-1;
		 return -4;
	 }
	 if(actnr!=-1)
	 {
		 hide_pointer();
//		 if(mode_text)
		 chbkg(table[nrcur].top.x,table[nrcur].top.y + (mode_text ? 0 : 6), table[nrcur].bot.x-table[nrcur].top.x +1  , fond, -1, 127, text_height+3);
//			 cursor(fond);
		 nrcur=actnr;
//		 if(mode_text)
		 chbkg(table[nrcur].top.x,table[nrcur].top.y + (mode_text ? 0 : 6), table[nrcur].bot.x-table[nrcur].top.x +1  , selectbkgcolour, -1, 127, text_height+3);
//			 cursor(CYAN);
		 display_pointer();
		 if (type_menu==BARMENU)
			 rtvar = actnr;
		 else
			 rtvar=select(actnr);
		 nrcur=actnr;
		 actnr=-1;
		 return rtvar;
	 }
	}
 }
 return -1;
};

int GMenuBar::select(int j)
{
 int rtvar;

 while(1)
 {
		pGPopUpTable[j].GShowPopUp();
		rtvar=pGPopUpTable[j].PSelected();
		pGPopUpTable[j].ReleasePopUp(rtvar - nrcur*10);
		actnr=nrcur;
//		if(mode_text)
		hide_pointer();
		chbkg(table[nrcur].top.x,table[nrcur].top.y + (mode_text ? 0 : 6), table[nrcur].bot.x-table[nrcur].top.x +1  , fond, -1, 127, text_height+3);

//			cursor(fond);
		if (rtvar>=200)    //right
		{
			 nrcur=rtvar-200;
		}
		else
		 if (rtvar==-3)    //right
		 {
			 nrcur++;
			 if(nrcur>=nrmax) nrcur=0;
		 }
		 else
			 if (rtvar==-2)    //left
			 {
					 nrcur--;
					 if(nrcur<0) nrcur=nrmax-1;
			 }
			 else
			 {
						 chbkg(table[nrcur].top.x,table[nrcur].top.y + (mode_text ? 0 : 6), table[nrcur].bot.x-table[nrcur].top.x +1  , selectbkgcolour, -1, 127, text_height+3);
						 break;
			 }
		 chbkg(table[nrcur].top.x,table[nrcur].top.y + (mode_text ? 0 : 6), table[nrcur].bot.x-table[nrcur].top.x +1  , selectbkgcolour, -1, 127, text_height+3);
		 j=nrcur;
     display_pointer();
		 print_alarm_word();
 }
display_pointer();
return rtvar;
}


/************************************************/

// class GPopUp//

/*************Constructor**************************/

GPopUp::GPopUp()
{
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.003  ********
// ********       begin       ********
// ***********************************
	Flag_help=MENU_MAIN;
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.003  ********
// ********        end        ********
// ***********************************
 nr=0;
 hook.x=1;
 hook.y=1;
 ltop.x=1;
 ltop.y=1;
 rbottom.x=1;
 rbottom.y=1;
 save = 1;
 pXms = NULL;
 style = 1;
 under1 = NULL;

 for (int i=0; i<10;i++)
		hotletter[i]=0;

};

GPopUp::GPopUp(int lx, int ly, char **mess, int onscr, int st, int ffont, int cchar_size, char d_print)
{
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.004  ********
// ********       begin       ********
// ***********************************
 Flag_help=MENU_MAIN;
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.004  ********
// ********        end        ********
// ***********************************
 font = ffont;
 char_size = cchar_size;
 double_print = d_print;
 nr=0;
 hook.x=1;
 hook.y=1;
 ltop.x=1;
 ltop.y=1;
 rbottom.x=1;
 rbottom.y=1;
 save = 1;
 pXms = NULL;
 style = 1;
 under1 = NULL;

 for (int i=0; i<10;i++)
		hotletter[i]=0;

 SetPopUp(0, lx, ly, onscr, ffont, cchar_size, d_print);
 SetList((char huge **)mess);
 bar_menu = NULL;
 style = st;
 selectbkgcolour=Lightblue;
}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.005  ********
// ********       begin       ********
// ***********************************
GPopUp::GPopUp(int flag_help,char *need_help,int lx, int ly, char **mess, int onscr, int st, int ffont, int cchar_size, char d_print)
{
 Flag_help=flag_help;
 font = ffont;
 char_size = cchar_size;
 double_print = d_print;
 nr=0;
 hook.x=1;
 hook.y=1;
 ltop.x=1;
 ltop.y=1;
 rbottom.x=1;
 rbottom.y=1;
 save = 1;
 pXms = NULL;
 style = 1;
 under1 = NULL;

 for (int i=0; i<10;i++)
		hotletter[i]=0;

 SetPopUp(0, lx, ly, onscr, ffont, cchar_size, d_print);
 SetList((char huge **)mess);
 bar_menu = NULL;
 style = st;
 selectbkgcolour=Lightblue;
}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.005  ********
// ********        end        ********
// ***********************************

/**************************************/

void GPopUp::SetPopUp(uint which, uint hx, uint hy, int onscr,
							 int ffont, int cchar_size, char d_print)
{
 font = ffont;
 char_size = cchar_size;
 double_print = d_print;
 onscreen = onscr;
 nr=which;
 hook.x=hx;
 hook.y=hy;
 memset(table,0,10*sizeof(hot_box));
 selectbkgcolour=Lightblue;
};

/*************************************/

void GPopUp::SetList(char huge **mess)
{
 uint max=0,i=0;
 char huge **ptr;

 list=mess;
 ptr=mess;

 while(*ptr!=NULL)
 {
	if (max<(mode_text? strlen(*ptr) : textwidth(*ptr)))
			max = (mode_text ? strlen(*ptr) : textwidth(*ptr));
	ptr++;
	i++;
 }

 if(mode_text)
 {
//	ltop.y=3;
	ltop.y= hook.y+1;
	rbottom.y=ltop.y+1+i*1;
 }
 else
 {
 ltop.y=hook.y+4;
 rbottom.y=ltop.y+2*6+i*(textheight("H")+LINE_SPACE)+LINE_SPACE;
 }

 if(mode_text)
 {
	 if(hook.x+max+4 <= 80)
	 {
		ltop.x=hook.x;
		rbottom.x=ltop.x+max+2;
	 }
	 else
	 {
		ltop.x=80-(max+4)+1;
		rbottom.x=79;
	 }
 }
 else
 {
	 if(hook.x+max+2*6+20 < maxx-2)
	 {
		ltop.x=hook.x;
		rbottom.x=ltop.x+max+2*6+20;
	 }
	 else
	 {
		ltop.x=636-(max+2*6+20);
		rbottom.x=maxx-2;
	 }
 }
/*
 if(hook.x<(80/2))
	{
	 ltop.x=hook.x;
	 rbottom.x=ltop.x+max;
	}
 else
	{
	 rbottom.x=hook.x;
	 ltop.x=rbottom.x-max;
	}
*/

};

/************************************/

void GPopUp::GBorder(void)
{
 lin_hor[rbottom.x-ltop.x+1]=0;
 mxyputs(ltop.x,ltop.y,lin_hor,Lightgray,Black);
 mxyputs(ltop.x,rbottom.y,lin_hor,Lightgray,Black);
 lin_hor[rbottom.x-ltop.x+1]='ƒ';

 dxscreen--;
 dyscreen++;
 lin_ver[rbottom.y-ltop.y+1]=0;
 mxyputs(ltop.x,ltop.y,lin_ver,Lightgray,Black);
 mxyputs(rbottom.x,ltop.y,lin_ver,Lightgray,Black);
 lin_ver[rbottom.y-ltop.y+1]='≥';
 dxscreen++;
 dyscreen--;

	moutchar(ltop.x,ltop.y,'⁄',Lightgray,Black);
	moutchar(ltop.x,rbottom.y,'¿',Lightgray,Black);
	moutchar(rbottom.x,ltop.y,'ø',Lightgray,Black);
	moutchar(rbottom.x,rbottom.y,'Ÿ',Lightgray,Black);

	return;
}

void GPopUp::GShowPopUp()
{
 int x=0,y;
 char access;
 float f;
 char *tilda;
 char hotchar[2];
 hotchar[1]=0;
 char huge **mes;
 uint wide=0,length=1,i=0;
 if(!mode_text)
	 length=3;
 char *aux;

 mes =list;

 if(ltop.x>1)
	{x=1;ltop.x--;}
 rbottom.x++;
 SaveArea();
 if(x) ltop.x++;
 rbottom.x--;

 hide_pointer();

 if (mode_text)
	{
//	 mgettext(ltop.x,ltop.y,rbottom.x,rbottom.y,(void *)under1);
//	 mtextcolor(Lightgray);

/*
	 lin_menu[rbottom.x-ltop.x+1]=0;
	 for(int j=ltop.y;j<=rbottom.y;j++)
		{
		mxyputs(ltop.x,j,lin_menu,Lightgray,Black);
		}
	 lin_menu[rbottom.x-ltop.x+1]=lin_menu[0];

	 GBorder();
*/
	Bordergr(ltop.x, ltop.y, rbottom.x, rbottom.y, Black, Lightgray, White, White, style, 0);

//	 mgotoxy(ltop.x+1,ltop.y+1);

	 wide=strlen(*mes)+1;
	}
 else
	{
////	mmgetimage(ltop.x,ltop.y,rbottom.x,rbottom.y,(signed char **)&under1);

 setfillstyle(SOLID_FILL, Lightgray);

// setcolor(Black);
// setlinestyle(SOLID_LINE,0xffff,1);
 bar(ltop.x,ltop.y,rbottom.x,rbottom.y);
 prectangle(ltop.x,ltop.y,rbottom.x,rbottom.y, Black);
// prectangle(ltop.x+4,ltop.y+4,rbottom.x-4,rbottom.y-4, Black);
 prectangle(ltop.x+1,ltop.y+1,rbottom.x-1,rbottom.y-1, Darkgray);
 prectangle(ltop.x+2,ltop.y+2,rbottom.x-2,rbottom.y-2, Darkgray);
 prectangle(ltop.x+1,ltop.y+1,rbottom.x-1,ltop.y+1, White);
 prectangle(ltop.x+2,ltop.y+2,rbottom.x-2,ltop.y+2, White);
 prectangle(ltop.x+1,ltop.y+1,ltop.x+1,rbottom.y-1, White);
 prectangle(ltop.x+2,ltop.y+2,ltop.x+2,rbottom.y-2, White);


 // pline(ltop.x+1,rbottom.y-1,rbottom.x-1,rbottom.y-1, Black);
// pline(rbottom.x-1,ltop.y+1,rbottom.x-1,rbottom.y-1, Black);

// pline(ltop.x+1,ltop.y+1,rbottom.x-1,ltop.y+1, White);
// pline(ltop.x+1,rbottom.y-1,ltop.x+1,ltop.y+1, White);
// pline(ltop.x,ltop.y,rbottom.x,ltop.y, White);

// settextstyle(DEFAULT_FONT,HORIZ_DIR,1);

  moveto(ltop.x,ltop.y+3);
  wide=textwidth(*mes)+16;
  length = 6;

  msettextstyle(font , 0, char_size);
  text_height = textheight("H");
 }

 while((*mes!=NULL)&&(wide<(rbottom.x-ltop.x))&&
			 (length<(rbottom.y-ltop.y))&&(i<10))
	{
	 access = array_access_level[nr*10+i] & (1<<access_level);

	 table[i].top.x=ltop.x+1;
	 table[i].top.y=ltop.y+length+LINE_SPACE;
	 table[i].bot.x=rbottom.x-1;
	 if(mode_text)
		 table[i].bot.y=ltop.y+length;
	 else
		 table[i].bot.y=table[i].top.y+textheight(*mes);


	 if(mode_text)
	 {
//		mgotoxy(table[i].top.x+1,table[i].bot.y);

		x = table[i].top.x+1; y = table[i].bot.y;
		length+=1;

		tilda=strchr(*mes,'~');
		*tilda=0;
		if(access)
			mxyputs(x,y, *mes, Lightgray, Black );
		else
			mxyputs(x,y, *mes, Lightgray, Darkgray );

		x += strlen(*mes);
		*tilda='~';

		hotchar[0]=*(tilda+1);

		hotletter[i]=hotchar[0];

		moutchar(x,y, hotchar[0], Lightgray, White );
		aux=tilda+2;
		if(access)
			mxyputs( x+1, y, aux, Lightgray, Black );
		else
			mxyputs( x+1, y, aux, Lightgray, Darkgray );
		mes++;

		wide=strlen(*mes)+1;
	 }
	 else
	 {
//	 circle(ltop.x+12,table[i].top.y+(table[i].bot.y-table[i].top.y)/2,4);

	 x = table[i].top.x+20;
	 if( font != DEFAULT_FONT )
		 y = table[i].bot.y-lung_char_n-3;
	 else
		 y = table[i].bot.y-lung_char_n;
	 moveto(table[i].top.x+20,table[i].bot.y-lung_char_n);

	 length += lung_char_n+LINE_SPACE;

	 tilda=strchr(*mes,'~');
	 *tilda=0;
	 outtextxy(x,y,*mes);
	 if(double_print)
		outtextxy(x+1,y,*mes);
	 x += strlen(*mes)*lat_char_n;
	 *tilda='~';

	 hotchar[0]=*(tilda+1);
	 hotletter[i]=hotchar[0];

	 setcolor(bar_menu?bar_menu->highlight:White);
	 outtextxy(x,y,hotchar);
	 if(double_print)
		outtextxy(x+1,y,hotchar);
	 x += strlen(hotchar)*lat_char_n;
	 setcolor(Black);
	 aux=tilda+2;
	 outtextxy(x,y,aux);
	 if(double_print)
		outtextxy(x+1,y,aux);
	 x += strlen(aux)*lat_char_n;
	 mes++;

	 if(*mes)
		 wide=textwidth(*mes)+16;
	 }
	 i++;
	}
 nrcur = 0;
 nrmax = i-1;
// if(mode_text)
	 chbkg(table[nrcur].top.x+(mode_text?0:7),table[nrcur].top.y-(mode_text?0:2), table[nrcur].bot.x-table[nrcur].top.x +1+(mode_text?0:-14)	, bar_menu?bar_menu->selectbkgcolour:selectbkgcolour, -1, 127, text_height+2);
//	 cursor(CYAN);

 display_pointer();
};

/*********************************************/

void GPopUp::ReleasePopUp(int rtvar)
 {
	int x=0;
	if( (rtvar>=0 && rtvar<10) && (onscreen & (1<<rtvar)) ) return;

	if(ltop.x>1)
	 {x=1;ltop.x--;}
	rbottom.x++;
	RestoreArea();
	if(x) ltop.x++;
	rbottom.x--;
/*
	hide_pointer();
	if(mode_text)
		mputtext(ltop.x,ltop.y,rbottom.x,rbottom.y,(void *)under1);
	else
	 mmputimage(ltop.x, ltop.y, rbottom.x, rbottom.y, (signed char *)under1);

	mfarfree(under1);
	display_pointer();
*/
 };

/*********************************************/
int GPopUp::GReturn(void)
{
		GShowPopUp();
		int rtvar;
		while ( (rtvar=PSelected())==-2 || rtvar==-3);
		ReleasePopUp(rtvar);
		return rtvar;
}
/*********************************************/
int GPopUp::PSelected(void)
{
// struct fillsettingstype fill;
// set_pointer_shape(GLOVE);
	union {
		int i;
		char ch[2];
		} key;
 int x,y;
 char access;
 display_pointer();

 int i,j=0,show;

 show=0;
 MouseStatus stat;
 char what;

 do
 {
	get_button_released(BRIGHT,stat);
	get_button_released(BLEFT,stat);

	if (!bioskey_new(1))                //kbhit())
	{
			mouse_status(stat);
			if (mouse_inside(ltop.x,ltop.y,rbottom.x,rbottom.y))
			{
			 for (uint i=0; i<10; i++)
				if (mouse_inside(table[i].top.x,table[i].top.y,
							table[i].bot.x,table[i].bot.y))
			 {
				if(stat.leftButton)
				{
				 get_button_released(BLEFT,stat);
				 while(!get_button_released(BLEFT,stat));
				 display_pointer();
				 if((array_access_level[nr*10+i] & (1<<access_level)))
					 return (nr*10+i);
				 else
					 return -1;
				}
				if(show!=i)
				{
					show=i;
					hide_pointer();
					chbkg(table[nrcur].top.x+(mode_text?0:7),table[nrcur].top.y-(mode_text?0:2), table[nrcur].bot.x-table[nrcur].top.x +1+(mode_text?0:-14)	, Lightgray, -1, 127, text_height+2);
//				 cursor(fond);
					nrcur=i;
					chbkg(table[nrcur].top.x+(mode_text?0:7),table[nrcur].top.y-(mode_text?0:2), table[nrcur].bot.x-table[nrcur].top.x +1+(mode_text?0:-14)	, bar_menu?bar_menu->selectbkgcolour:selectbkgcolour, -1, 127, text_height+2);
					display_pointer();
					break;
				}
			 }
			}
			else
			 if(bar_menu)
			 if ( mouse_inside(bar_menu->ltop.x,bar_menu->ltop.y,bar_menu->rbottom.x,bar_menu->rbottom.y) &&
					!mouse_inside(bar_menu->table[bar_menu->nrcur].top.x,bar_menu->table[bar_menu->nrcur].top.y,bar_menu->table[bar_menu->nrcur].bot.x,bar_menu->table[bar_menu->nrcur].bot.y) && mouse_motion(&x,&y))
				 for (uint i=0; i<bar_menu->nrmax; i++)
					 if (mouse_inside(bar_menu->table[i].top.x,bar_menu->table[i].top.y,
								bar_menu->table[i].bot.x,bar_menu->table[i].bot.y))
					{
						display_pointer();
						return 200+i;
					}

			if(stat.rightButton)
			{
				while(!get_button_released(BRIGHT,stat));
//	 set_pointer_shape(ARROW);
				display_pointer();
// ********  the old code  *******
// 			return -1;
// *******************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.006  ********
// ********       begin       ********
// ***********************************
				switch (Flag_help)
				{
					case	MENU_MAIN:
							{
								T3000help(nr*10+nrcur);
							};
							break;
					case	MENU_FILE:
							{
								T3000help(MENU_FILE+nrcur);
							};
							break;
					case	MENU_SETUP:
							{
								T3000help(MENU_SETUP+nrcur);
							};
							break;
					case	MENU_HARDWARE:
							{
								T3000help(MENU_HARDWARE+nrcur);
							};
							break;
				}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.006  ********
// ********        end        ********
// ***********************************

	    }//if

		 print_alarm_word();
	}
	else
	{
	 hide_pointer();
//	 what=mgetch();
	 key.i=bioskey_new(0);
	 what = key.ch[0];
	 if(what==ESC)
		 {
//			set_pointer_shape(ARROW);
			display_pointer();
			return -1;
		 }
	 if(what==32)       // blank
		return -32;

		i=0;
		if(what==0 || what==ENTER )
		{
		 if (what==ENTER)
			{
			 display_pointer();
			 if((array_access_level[nr*10+nrcur] & (1<<access_level)))
				 return (nr*10+nrcur);
			 else
				 return -1;
			}
		 else
//		 what=mgetch();
		 what = key.ch[1];
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.007  ********
// ********       begin       ********
// ***********************************
		 if (what==F1KEY)
			{
				switch (Flag_help)
				{
					case	MENU_MAIN:
							{
								T3000help(nr*10+nrcur);
							};
							break;
					case	MENU_FILE:
							{
								T3000help(MENU_FILE+nrcur);
							};
							break;
					case	MENU_SETUP:
							{
								T3000help(MENU_SETUP+nrcur);
							};
							break;
					case	MENU_HARDWARE:
							{
								T3000help(MENU_HARDWARE+nrcur);
							};
							break;
				}
			}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.007  ********
// ********        end        ********
// ***********************************
		 if (what==RIGHT)    //right || what==75)
		 {
			display_pointer();
			return -3;
		 }
		 if (what==LEFT)    //left
		 {
			display_pointer();
			return -2;
		 }
//		 {
		 if (what==DOWN)
		 {
			 hide_pointer();
//			 if(mode_text)
				 chbkg(table[nrcur].top.x+(mode_text?0:7),table[nrcur].top.y-(mode_text?0:2), table[nrcur].bot.x-table[nrcur].top.x +1+(mode_text?0:-14)	, Lightgray, -1, 127, text_height+2);
//				 cursor(Lightgray);
			 nrcur++;
			 if(nrcur>nrmax) nrcur=0;
//			 if(mode_text)
				 chbkg(table[nrcur].top.x+(mode_text?0:7),table[nrcur].top.y-(mode_text?0:2), table[nrcur].bot.x-table[nrcur].top.x +1+(mode_text?0:-14)	, bar_menu?bar_menu->selectbkgcolour:selectbkgcolour, -1, 127, text_height+2);
//				 cursor(CYAN);
			 display_pointer();
			 continue;
		 }
		 if (what==UP)
		 {
			 hide_pointer();
//			 if(mode_text)
				 chbkg(table[nrcur].top.x+(mode_text?0:7),table[nrcur].top.y-(mode_text?0:2), table[nrcur].bot.x-table[nrcur].top.x +1+(mode_text?0:-14)	, Lightgray, -1, 127, text_height+2);
//				 cursor(Lightgray);
			 nrcur--;
			 if(nrcur<0) nrcur=nrmax;
//			 if(mode_text)
				 chbkg(table[nrcur].top.x+(mode_text?0:7),table[nrcur].top.y-(mode_text?0:2), table[nrcur].bot.x-table[nrcur].top.x +1+(mode_text?0:-14)	, bar_menu?bar_menu->selectbkgcolour:selectbkgcolour, -1, 127, text_height+2);
//				 cursor(CYAN);
			 display_pointer();
			 continue;
		 }

		 for(i=0;i<20;i++)
			 if(altkey[i][0]==what)
						 {
							 display_pointer();
							 if((array_access_level[altkey[i][1]] & (1<<access_level)))
								 return altkey[i][1];
							 else
								 return -1;
						 }
		 }
		 else       // if what = 0
		 {
			while(i<26)
			{
			 if (what==GKeys[i]) break;
			 else i++;
			}
			if (i==26) continue;

		 j=0;

		 while((j<10)&&(hotletter[j]!=0))
			{
			 if(((0x41+i)==hotletter[j])||
		((0x61+i)==hotletter[j]))
		{
///		 set_pointer_shape(ARROW);
		 display_pointer();
		 if((array_access_level[nr*10+j] & (1<<access_level)))
			 return (nr*10+j);
		 else
			 return -1;
		}

			 else j++;
			}//while
		}//if

	 display_pointer();
	 }//else

 }while(1);
};

/*
void GPopUp::cursor( char bkg)
{
 char buf[60];
 char i,j;
 char col;
			j=1;
			if (bkg==CYAN) j=-1;
			mgettext(this->table[nrcur].top.x,this->table[this->nrcur].top.y,this->table[this->nrcur].bot.x,this->table[this->nrcur].bot.y,buf);

			 for(i=0;i<30;i++)
				{
				 col=buf[2*i+1] & '\x0F';
				 if(col==buf[2*i+1]/16) buf[2*i+1]=bkg*16+bkg;
				 else {
							 buf[2*i+1]=bkg*16+((col+j)&'\x0F');
							}
				}
			 mputtext(table[nrcur].top.x,table[nrcur].top.y,table[nrcur].bot.x,table[nrcur].bot.y,(void *)buf);
}
*/
/*
void GMenuBar::cursor( char bkg)
{
 char buf[60];
 char i,j;
 char col;
			j=1;
			if (bkg==CYAN) j=-1;
			mgettext(this->table[this->nrcur].top.x,this->table[this->nrcur].top.y,this->table[this->nrcur].bot.x,this->table[this->nrcur].bot.y,buf);

			 for(i=0;i<30;i++)
				{
				 col=buf[2*i+1] & '\x0F';
				 if(col==buf[2*i+1]/16) buf[2*i+1]=bkg*16+bkg;
				 else {
							 buf[2*i+1]=bkg*16+((col+j)&'\x0F');
							}
				}
			 mputtext(table[nrcur].top.x,table[nrcur].top.y,table[nrcur].bot.x,table[nrcur].bot.y,(void *)buf);
}
*/