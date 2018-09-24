#include <mem.h>
#include "gview.h"
#include <graphics.h>
#include "t3000def.h"
#include "mtkernel.h"
#include "_msdos.h"

#define MODE_TEXT 1
#define MODE_GRAPHIC 0

#define OKAY 1
#define NOMEM 0

extern int mode_text;
extern int fond_color;
char graphsave=0;
char nothing = 1;
//////////////////////////////////////////////////
//                                              //
// Implements the member functions for GVIEW.H  //
//                                              //
//////////////////////////////////////////////////


/**************************************/

GView::GView(uint lx,uint ly, uint rx,uint ry)  //constructor
{
		ltop.x=lx; rbottom.x=rx;
		ltop.y=ly; rbottom.y=ry;
		save = 1; flag = 0;
		pXms = NULL;
		under1 = under2 = under3 = under4 = NULL;
		handle = 0;
};

/**************************************/

GView::~GView()
{
	asm push es;
	if(save)
	{
	 if(mode_text)
	 {
		if(under1)
		{
		 mfarfree (handle);
		}
	 }
	 else
	 {
		if(!flag)
		{
		 if(under1)
		 {
			mfarfree (handle);
		 }
		}
		else
		{
		 if (under1)
		 {
			mfarfree((HANDLE)FP_SEG(under1));
		 }
		 if (under2)
		 {
			mfarfree((HANDLE)FP_SEG(under2));
		 }
		 if (under3)
		 {
			mfarfree((HANDLE)FP_SEG(under3));
		 }
		 if (under4)
		 {
			mfarfree((HANDLE)FP_SEG(under4));
		 }
		}
	 }
	}
	asm pop es;
};

void GView::SaveArea(void)
{
 unsigned long big;
 HANDLE h;

 asm push es;
 if(save)
 {
	flag=0;
	hide_pointer();    // hides the mouse cursor during reading
	if(mode_text)
		big = (rbottom.x-ltop.x+1)*(rbottom.y-ltop.y+1)*2;
	else
	{
		big = mimagesize(ltop.x, ltop.y, rbottom.x, rbottom.y);
		if (big && big!=0xffff)
		{
			mfarmalloc((char far **)&under1, big , handle	);
			if( under1!=NULL )
			{
				mgetimage(ltop.x, ltop.y, rbottom.x, rbottom.y, under1);
				save=1;
				asm pop es;
				return;
		 }
		}
		else
		{
		 big = mimagesize(ltop.x, ltop.y, rbottom.x, ltop.y + (rbottom.y-ltop.y)/4);
		 mfarmalloc((char far **)&under1, big, h);
		 if (under1) mgetimage(ltop.x, ltop.y, rbottom.x, ltop.y + (rbottom.y-ltop.y)/4, under1);
		 big = mimagesize(ltop.x, ltop.y + (rbottom.y-ltop.y)/4, rbottom.x, ltop.y + (rbottom.y-ltop.y)/2);
		 mfarmalloc((char far **)&under2, (unsigned long)big, h);
		 if (under2) mgetimage(ltop.x, ltop.y + (rbottom.y-ltop.y)/4, rbottom.x, ltop.y + (rbottom.y-ltop.y)/2, under2);
		 big = mimagesize(ltop.x, ltop.y + (rbottom.y-ltop.y)/2, rbottom.x, ltop.y + 3*(rbottom.y-ltop.y)/4);
		 mfarmalloc((char far **)&under3, (unsigned long)big, h);
		 if (under3) mgetimage(ltop.x, ltop.y + (rbottom.y-ltop.y)/2, rbottom.x, ltop.y + 3*(rbottom.y-ltop.y)/4, under3);
		 big = mimagesize(ltop.x, ltop.y + 3*(rbottom.y-ltop.y)/4, rbottom.x, rbottom.y);
		 mfarmalloc((char far **)&under4, (unsigned long)big, h);
		 if (under4) mgetimage(ltop.x, ltop.y + 3*(rbottom.y-ltop.y)/4, rbottom.x, rbottom.y, under4);
		 flag=1;
		}

	}

	if(mode_text)
	{
		mfarmalloc((char far **)&under1, (unsigned long)big, handle	);
		if( under1!=NULL )
		{
			mgettext(ltop.x, ltop.y, rbottom.x, rbottom.y,(void *)under1);
		}
	}
	display_pointer(); //displays the mouse cursor after
										//the reading has been accomplished
 }

 asm pop es;
};

/**************************************/

void GView::RestoreArea(void)
{
	asm push es;
	hide_pointer();

	if(save)
	{
	 if(mode_text)
	 {
		if(under1)
		{
		 mputtext(ltop.x, ltop.y, rbottom.x, rbottom.y,(void *)under1);
		 mfarfree (handle);
		 handle = 0;
		 under1 = NULL;
		}
	 }
	 else
	 {
		if(!flag)
		{
		 if(under1)
		 {
			mputimage(ltop.x, ltop.y, (void *)under1, COPY_PUT);
			mfarfree (handle);
			handle = 0;
			under1 = NULL;
		 }
		}
		else
		{
		 if (under1)
		 {
			mputimage(ltop.x,ltop.y,(void *)under1, COPY_PUT);
			mfarfree((HANDLE)FP_SEG(under1));
			under1 = NULL;
		 }
		 if (under2)
		 {
			mputimage(ltop.x,(ltop.y+(rbottom.y-ltop.y)/4),under2,COPY_PUT);
			mfarfree((HANDLE)FP_SEG(under2));
			under2 = NULL;
		 }
		 if (under3)
		 {
			mputimage(ltop.x,(ltop.y+(rbottom.y-ltop.y)/2),under3,COPY_PUT);
			mfarfree((HANDLE)FP_SEG(under3));
			under3 = NULL;
		 }
		 if (under4)
		 {
			mputimage(ltop.x,ltop.y+3*(rbottom.y-ltop.y)/4,under4,COPY_PUT);
			mfarfree((HANDLE)FP_SEG(under4));
			under4 = NULL;
		 }
		}
	 }
	}
	else
	{
	 if(!mode_text)
		if(nothing)
		{
		 set_semaphore(&screen);
		 setfillstyle(SOLID_FILL, fond_color);
		 bar(ltop.x, ltop.y, rbottom.x, rbottom.y);
		 clear_semaphore(&screen);
		}
	}
	display_pointer();
	asm pop es;
};

