#include <mem.h>
#include <windows.h>
#include <graphics.h>
#include "mouse.h"
#include "t3000def.h"
#include "mtkernel.h"
#define LAT 8
#define LUNG 8

extern int lat_char_n;
extern int lung_char_n;
extern int Green,Red;

int mode_text=MODE_TEXT;
int mode_graph=0;
char text;
char visible=0;
int mouse_inst;
int xcur_mouse;
int ycur_mouse;
extern char huge ptr_mouse[512];
//HANDLE ptr_mouse_handle;
int status_mouse;

/**************************/

void mouse_installed(void)
{
 uint  inst;
 uint buttons;

 asm{
	 xor 	ax,ax
	 int 	33h
	 mov 	inst,ax
	 mov	buttons,bx
	};

 if(inst==0)
	{
//	 printf("\nMouse driver not installed");
//	 getch();
//	 exit(0);
	}
// asm {
//	 mov ax,000ah
//	 mov bx,0
//	 mov cx,0ffffh
//	 mov dx,7700h
//	 int 33h
// }
 if(inst==0xffff)
	{
	 mouse_inst=1;
	 if (buttons!=3)
	 {
//	   printf("\nDoesn't support this many buttons");
//		 getch();
//		 exit(0);
		}
	 else
	 {
//		printf("\nMouse installed, press any key to proceed\n");
//		getch();
		return;
	 }
	}
};

/**************************/

void display_pointer(void)
{
 asm push es;
 if (mouse_inst)
 {
	if(!visible)
	{
		set_semaphore(&screen);
		asm{
			push  ax
			push  ds
			mov 	ax,1
			int	33h
			pop   ds
			pop   ax
		};
		visible=1;
		clear_semaphore(&screen);
	}//if
 }
 else
 {
//	int big;
	if(status_mouse == SHOWMOUSE)
	{
/*
	 if(!ptr_mouse)
	 {
//		mputimage(xcur_mouse, ycur_mouse, ptr_mouse, COPY_PUT);
//		mfarfree(ptr_mouse_handle);
//		ptr_mouse = NULL;
//	 }
*/
	 if(!visible)
	 {
/*
		if(ptr_mouse)
		{
		mputimage(xcur_mouse, ycur_mouse, ptr_mouse, COPY_PUT);
		mfarfree(ptr_mouse);
		ptr_mouse = NULL;
		}
		big=mimagesize(xcur_mouse, ycur_mouse, xcur_mouse + lat_char_n, ycur_mouse + lung_char_n);
		mfarmalloc((char far **)&ptr_mouse, (unsigned long)big );
		set_semaphore(&screen);
		getimage(xcur_mouse, ycur_mouse, xcur_mouse + lat_char_n, ycur_mouse + lung_char_n, ptr_mouse);
		setcolor(Green);
		outtextxy(xcur_mouse, ycur_mouse, "+");
		clear_semaphore(&screen);
//	 }
*/
		set_semaphore(&screen);
		getimage(xcur_mouse, ycur_mouse, xcur_mouse + lat_char_n, ycur_mouse + lung_char_n, ptr_mouse);
		setcolor(Green);
		outtextxy(xcur_mouse, ycur_mouse, "+");
		clear_semaphore(&screen);
		visible=1;
	 }
	}
 }
 asm pop es;
};

/***************************/

void hide_pointer(void)
{
 asm push es;
 if (mouse_inst)
 {
  if(visible)
  {
	set_semaphore(&screen);
	asm{
	 push  ax
	 push  ds
	 mov	 ax,2
	 int	 33h
	 pop   ds
	 pop   ax
	};
	clear_semaphore(&screen);
	visible=0;
	}
 }
 else
 {
	if(status_mouse == SHOWMOUSE)
	{
	 if(visible)
	 {
/*
		if(ptr_mouse)
		{
		 mputimage(xcur_mouse, ycur_mouse, ptr_mouse, COPY_PUT);
		 mfarfree(ptr_mouse);
		 ptr_mouse = NULL;
		}
*/
		mputimage(xcur_mouse, ycur_mouse, ptr_mouse, COPY_PUT);
	 }
	 visible=0;
	}
 }
 asm pop es;
};

/**************************/

void mouse_status(MouseStatus& s)
{
 uint rtrn,x,y;

 if (mouse_inst)
 {
	asm{
	 mov	ax,3
	 int	33h
	 mov	rtrn,bx
	 and    cx,3ffh
	 mov	x,cx
	 and    dx,3ffh
	 mov	y,dx
	};

	s.leftButton   =(rtrn&1);
	s.rightButton  =(rtrn&2);
	s.centerButton =(rtrn&4);
 }
 else
 {
	x=xcur_mouse;
	y=ycur_mouse;
	s.leftButton   =0;
	s.rightButton  =0;
	s.centerButton =0;
 }

 if (mode_text)
 {
	s.where.x=x/LAT+1;
	s.where.y=y/LUNG+1;
 }
 else
 {
	s.where.x=x;
	s.where.y=y;
 }
 return;
};

/**************************/

uint get_button_pressed(char which, MouseStatus& s)
{
 uint retvar,ceix,deix;

 if (mouse_inst)
 {
	asm{
		 mov	ax,5
		 mov        bl,which
		 mov	bh,0
		 int	33h
		 mov	ceix,cx
		 mov	deix,dx
		 mov	cl,which
		 shr	ax,cl
		 mov	retvar,bx
		 };

	s.leftButton  =_AX;
	s.rightButton =_AX;
	s.centerButton=_AX;
 }
 else
 {
	ceix=xcur_mouse;
	deix=ycur_mouse;
	s.leftButton   =0;
	s.rightButton  =0;
	s.centerButton =0;
	retvar=0;
 }

 if (mode_text)
 {
	s.where.x=ceix/LAT+1;
	s.where.y=deix/LUNG+1;
 }
 else
 {
	s.where.x=ceix;
	s.where.y=deix;
 }
 return (retvar);
};

/**************************/

uint get_button_released(char which, MouseStatus& s)
{
 uint retvar,ceix,deix;

 if (mouse_inst)
 {
	asm{
		 mov	ax,6
		 mov        bl,which
		 mov        bh,0
		 int	33h
		 mov	ceix,cx
		 mov	deix,dx
		 mov	cl,which
		 shr	ax,cl
		 mov	retvar,bx
		 };

	s.leftButton  =_AX;
	s.rightButton =_AX;
	s.centerButton=_AX;
 }
 else
 {
	ceix=xcur_mouse;
	deix=ycur_mouse;
	s.leftButton   =0;
	s.rightButton  =0;
	s.centerButton =0;
	retvar=1;
 }

if (mode_text)
{
 s.where.x=ceix/LAT+1;
 s.where.y=deix/LUNG+1;
}
else
{
 s.where.x=ceix;
 s.where.y=deix;
}
 return (retvar);
};


/**************************/
int mouse_motion(int *x,int *y)
{
 int mx,my;
// asm {
//		mov ax,1bh
//		int 33h
//		}
// mx=_BX;
// my=_CX;
 if (mouse_inst)
 {
	asm{
		 mov	ax,0Bh
		 int	33h
		 };

	*x =(int)_CX;
	*y =(int)_DX;

/*	asm{
		 mov	ax,1Bh
		 int	33h
		 };
 *x /= (int)_BX;
 *y /= (int)_CX;
*/
	if (mode_text)
	{
	 *x /= LAT;
	 *y /= LUNG;
	}//	gotoxy(2,2);
 }
 else
 {
	*x = 0;
	*y = 0;
 }
 return (*x || *y);
}

/**************************/

void set_hor_range(uint xmin, uint xmax)
{
	int xxmin,xxmax;
	xxmin=(xmin-1)*LAT;
	xxmax=(xmax-1)*LAT;
asm 			 mov	ax,7
if (mode_text)
{
asm			 mov 	cx,xxmin
asm			 mov	dx,xxmax
}
else
{
asm			 mov 	cx,xmin
asm			 mov	dx,xmax
}
asm			 int	33h
 return;
};

/**************************/

void set_vert_range(uint xmin, uint xmax)
{
	int xxmin,xxmax;
	xxmin=(xmin-1)*LUNG;
	xxmax=(xmax-1)*LUNG;
asm			 mov	ax,7
if (mode_text)
{
asm			 mov 	cx,xxmin
asm			 mov	dx,xxmax
}
else
{
asm			 mov 	cx,xmin
asm			 mov	dx,xmax
}
asm			 int	33h
 return;
};


/**************************/

void set_pointer_shape(Pshape& p)
{
 if (mouse_inst)
 {

	uint hsx=p.hot_spot.x;
	uint hsy=p.hot_spot.y;

 _ES=FP_SEG(p.shape);
 _DX=FP_OFF(p.shape);

 asm{
			mov	ax,9
			mov	bx,hsx
			mov	cx,hsy
			int	33h
		};
 }
 return;

};

/************************/

void set_speed(uint hor,uint vert)
{
	asm{
			mov	ax,0fh
			mov	cx,hor
			mov	dx,vert
			int	33h
		 };

	return;
};

/*************************/

void set_mhandler(uint what, uint segm, uint offs)
{
 asm{
			push	es
			mov       ax,segm
			mov       es,ax
			mov       cx,what
			mov       dx,offs
			mov	ax,0ch
			int	33h
			pop	es
		};

};


/***************************************/

uint mouse_inside(uint ux,uint uy,uint dx,uint dy)
{
 MouseStatus s;

 if (mouse_inst)
 {
 mouse_status(s);

 if((s.where.x<ux)||(s.where.x>dx)||
		(s.where.y<uy)||(s.where.y>dy))
			return 0;
 else
	 return 1;
 }
 else
		return 0;
};

/*****************************************/

void set_exclusion_area(uint upx, uint upy, uint dnx, uint dny)
{
 int uupx,uupy,ddnx,ddny;
 uupx=(upx-1)*LAT;
 uupy=(upy-1)*LUNG;
 ddnx=(dnx-1)*LAT;
 ddny=(dny-1)*LUNG;
asm			mov	ax,0010h
if (mode_text)
{
asm {
			mov	cx,uupx
			mov	dx,uupy
			mov	si,ddnx
			mov	di,ddny
		}
}
else
{
asm {
			mov	cx,upx
			mov	dx,upy
			mov	si,dnx
			mov	di,dny
		}
}
asm			int	33h
};

/*********************************/
void move_mouse(int x,int y)
{
 if (mode_text)
 {
	 x =(x-1)*LAT;
	 y =(y-1)*LUNG;
 }
 if (mouse_inst)
 {
	asm {
		mov ax,04h
		mov cx,x
		mov dx,y
		int 33h
		}
 }
 else
 {
	if(status_mouse == SHOWMOUSE)
	{
/*
	 int big;
	 if(ptr_mouse)
	 {
		mputimage(xcur_mouse, ycur_mouse, ptr_mouse, COPY_PUT);
		mfarfree(ptr_mouse);
		ptr_mouse = NULL;
	 }
	 big=mimagesize(x, y, x + lat_char_n, y + lung_char_n);
	 mfarmalloc((char far **)&ptr_mouse, (unsigned long)big);
	 set_semaphore(&screen);
	 getimage(x, y, x + lat_char_n, y + lung_char_n, ptr_mouse);
	 setcolor(Red);
	 outtextxy(x, y, "+");
	 clear_semaphore(&screen);
*/
	 if(visible)
		 mputimage(xcur_mouse, ycur_mouse, ptr_mouse, COPY_PUT);
	 set_semaphore(&screen);
	 getimage(x, y, x + lat_char_n, y + lung_char_n, ptr_mouse);
	 setcolor(Red);
	 outtextxy(x, y, "+");
	 clear_semaphore(&screen);
   visible = 1;
	}
	xcur_mouse = x;
	ycur_mouse = y;
 }
 return;
}

