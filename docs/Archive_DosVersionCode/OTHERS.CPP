#include <windows.h>
#include <math.h>
#include <bios.h>
#include <dir.h>
#include <mem.h>
#include <string.h>
#include <graphics.h>
#include <fcntl.h>
#include <SYS\STAT.H>
#include <ctype.h>
#include "mouse.h"
#include "t3000hlp.h"

#define  BS      0x08
#define  DOUBLE  1

#include "t3000def.h"
#include "mtkernel.h"

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


extern unsigned long  microsec; //  microsecunde
extern int select_tmp;
extern int mode_text;
extern int lat_char_n;
extern int lung_char_n;
extern char *lin_text;
extern char keyboard_data;


// 'A' alfanumeric
// 'N' numeric
// 'S' sablon
extern int print_alarm_word(void);
extern int bioskey_new(int cmd);
int cur_count;

// 'S'  sablon
// 'A' ascii
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.021  ********
// ********       begin       ********
// ***********************************
char wingets_help(int Flag_help,char far *ptr, int row, int col, int width,
				 int bkgnd, int frgnd, char which_type, char *sablon, char retnokey )
{
 int n,i=0;
// *ptr=0;
	union {
		int i;
		char ch[2];
		} key;
 char c, c1, cur[2];
 int w,xg,yg,lung,first=0;
 int loccur,endcur;
 MouseStatus stat;

//		 lung=textheight("H")+LINE_SPACE;
 if(which_type=='S')
 {
	if(!strlen(ptr))
		memset(ptr,' ',strlen(sablon));
	for(i=0;i<strlen(sablon);i++)
		if(sablon[i]!='A' && sablon[i]!='N' && sablon[i]!='*')
			ptr[i]=sablon[i];
 }

		if(!row && !col)
		{
		 if(mode_text)
		 {
			xg=wherex();
			yg=wherey();
		 }
		 else
		 {
			xg=getx();
			yg=gety();
		 }
		}
		else
		{
		 xg = col;
		 yg = row;
		}

 if(!mode_text)
 {
		 set_semaphore(&screen);
		 setfillstyle(SOLID_FILL,bkgnd);
		 clear_semaphore(&screen);
 }
 if(which_type=='E')
 {
  if(!mode_text)
  {
	 set_semaphore(&screen);
	 bar(xg,yg,xg+width*lat_char_n-1,yg+textheight("H")+1);
	 moveto(xg, yg);
	 setcolor(frgnd);
	 outtext(ptr);
	 moveto(xg+loccur*lat_char_n, yg);
   clear_semaphore(&screen);
	}
  else
  {
	 mxyputs(xg,yg,ptr,bkgnd,frgnd);
	}
 }
 else
 if(!select_tmp)
 {
	 if(!mode_text)
	 {
		set_semaphore(&screen);
		bar(xg,yg,xg+width*lat_char_n-1,yg+textheight("H")+1);
		moveto(xg, yg);
		if(which_type!='S')
			setcolor(Lightred);
		outtext(ptr);
		clear_semaphore(&screen);
	 }
	 else
	 {
		if(which_type!='S')
		 mxyputs(xg,yg,ptr,Red,frgnd);
	 }
 }

 if(which_type!='S'&&which_type!='E')
 {
	 first=1;
 }
/*
 if(which_type!='S')
 {
	 first=1;
	 if(!mode_text)
	 {
			if(!select_tmp)
			{
					bar(xg,yg,xg+width*lat_char_n,yg+textheight("H")+2);
					moveto(xg, yg);
					setcolor(Lightred);
					outtext(ptr);
			}
	 }
	 else
	 {
			if(!select_tmp)
					mxyputs(xg,yg,ptr,Red,frgnd);
	 }
 }
*/

 if(mode_text)
	 movetoxy(xg, yg);
 else
 {
	 set_semaphore(&screen);
	 moveto(xg, yg);
	 clear_semaphore(&screen);
 }
 endcur=strlen(ptr);
 loccur=0;
 c = 0;
 if(mode_text)
 {
	;
// mtextcolor(frgnd);
// mtextbackground(bkgnd);
 }
 else
 {
	set_semaphore(&screen);
	setfillstyle(SOLID_FILL,bkgnd);
	cur[0]='_';
	cur[1]=0;
//  setcolor(White);
	if( !retnokey )
	{
		c1 = ptr[loccur];
		ptr[loccur] = 0;
		w=textwidth(ptr);
		pline(xg+w-1,yg,xg+w-1,yg+textheight("H"),Yellow);
		ptr[loccur] = c1;
	}
//  outtextxy(xg+loccur*lat_char_n, yg, cur);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	setcolor(frgnd);
	clear_semaphore(&screen);
 }
 while(1)
 {
	display_pointer();
	while(!bioskey_new(1))
	{
	 if(!mode_text)
	 {
		if( cur_count==(retnokey?2000:5000) )
		{
//		 setcolor(White);
			c1 = ptr[loccur];
			ptr[loccur] = 0;
	    set_semaphore(&screen);
			w=textwidth(ptr);
			pline(xg+w-1,yg,xg+w-1,yg+textheight("H"),Yellow);
	    clear_semaphore(&screen);
			ptr[loccur] = c1;
//		 outtextxy(xg+loccur*lat_char_n, yg, cur);
		}
		if( cur_count++>(retnokey?4000:10000) )
		{
//		  setfillstyle(SOLID_FILL,bkgnd);
			c1 = ptr[loccur];
			ptr[loccur] = 0;
			set_semaphore(&screen);
			w=textwidth(ptr);
			pline(xg+w-1,yg,xg+w-1,yg+textheight("H"),bkgnd);
	    clear_semaphore(&screen);
			ptr[loccur] = c1;
			cur_count=0;
		}
	 }
	 print_alarm_word();
	 mouse_status(stat);
	 if(stat.leftButton)
	 {
			while(!get_button_released(BLEFT,stat));
//			while(stat.leftButton) 	mouse_status(stat);
//			last = '\0';
			if(!mode_text)
			{
				c1 = ptr[loccur];
				ptr[loccur] = 0;
				set_semaphore(&screen);
				w=textwidth(ptr);
				pline(xg+w-1,yg,xg+w-1,yg+textheight("H"),bkgnd);
				clear_semaphore(&screen);
				ptr[loccur] = c1;
			}
			return 0;
	 }
	 if( retnokey )
	 {
		return 1;
	 }
	}
	key.i = bioskey_new(0);
//	c=mgetch();
// ****************************************************************
// ********                    mao hui                     ********
// ********  this is deffrent from old function wingets()  ********
// ********                     begin                      ********
// ****************************************************************
	if (Flag_help!=0)
	{
		if (key.ch[0]==0)
		{
			if (key.ch[1]==F1KEY)
			{
				T3000help(Flag_help);
			}
		}
	}
// ****************************************************************
// ********                    mao hui                     ********
// ********  this is deffrent from old function wingets()  ********
// ********                      end                       ********
// ****************************************************************
	c=key.ch[0];
	hide_pointer();
	retnokey=0;

	if( c==0x0d || c=='\t' || c==27)
		break;
	if(c==0)       // tasta speciala
	{
		 if(first)
		 {
			first=0;
			if(!mode_text)
			{
					set_semaphore(&screen);
					bar(xg,yg,xg+width*lat_char_n-1,yg+textheight("H")+1);
					moveto(xg, yg);
					setcolor(frgnd);
					outtext(ptr);
					moveto(xg+loccur*lat_char_n, yg);
					clear_semaphore(&screen);
			}
			else
			{
					mxyputs(xg,yg,ptr,bkgnd,frgnd);
			}
		 }
		 c=key.ch[1];
		 if(c==80 || c==72)     //down  and up
				break;
		 if(((c==75) || (c==77)) && (select_tmp||which_type=='E'))
				break;
		 if(c==75)     //left
		 {
				if(!mode_text)
				{
					c1 = ptr[loccur];
					ptr[loccur] = 0;
					set_semaphore(&screen);
					w=textwidth(ptr);
					pline(xg+w-1,yg,xg+w-1,yg+textheight("H"),Black);
					clear_semaphore(&screen);
					ptr[loccur] = c1;
				}
				loccur--;
				if (loccur<0) loccur=0;
				if(which_type=='S')
				 while(1)
				 {
					if(!loccur) break;
					if(sablon[loccur] != 'A' && sablon[loccur] != 'N')
					{
					 loccur--;
					 if (loccur<0) loccur=0;
					}
					else
					 break;
				 }
		 }
		 if(c==77)     //right
		 {
				if(!mode_text)
				{
				 c1 = ptr[loccur];
				 ptr[loccur] = 0;
				 set_semaphore(&screen);
				 w=textwidth(ptr);
				 pline(xg+w-1,yg,xg+w-1,yg+textheight("H"),Black);
	       clear_semaphore(&screen);
				 ptr[loccur] = c1;
				}
				loccur++;
				if (loccur>=endcur) loccur--;
				if(which_type=='S')
				 while(1)
				 {
					if(loccur==endcur) break;
					if(sablon[loccur] != 'A' && sablon[loccur] != 'N')
					{
					 loccur++;
					 if (loccur>=endcur) loccur--;
					}
					else
					 break;
				 }
		 }

		 if(c==83&&which_type!='E')       // del
		 {
			 keyboard_data=1;
			 if(which_type=='S')
			 {
				 if(sablon[loccur]=='N')
					 ptr[loccur] = '0';
				 else
						ptr[loccur] = ' ';
				 if(!mode_text)
				 {
					set_semaphore(&screen);
					bar(xg,yg,xg+width*lat_char_n-1,yg+textheight("H")+1);
//					bar(xg,yg,xg+width*lat_char_n-3,yg+textheight("H")+2);
					moveto(xg, yg);
					setcolor(frgnd);
					outtext(ptr);
					clear_semaphore(&screen);
				 }
				 else
				 {
					mxyputs(xg,yg,ptr,bkgnd,frgnd);
				 }
			 }
			 else
			 if (endcur!=loccur)
				{
				 movmem(ptr+loccur+1,ptr+loccur,endcur-loccur);
				 endcur--;
				 ptr[endcur]=0;
				 if(!mode_text)
				 {
					set_semaphore(&screen);
					bar(xg,yg,xg+width*lat_char_n-1,yg+textheight("H")+1);
//					bar(xg,yg,xg+width*lat_char_n-3,yg+textheight("H")+2);
					moveto(xg, yg);
					setcolor(frgnd);
					outtext(ptr);
					moveto(xg+loccur*lat_char_n, yg);
	        clear_semaphore(&screen);
				 }
				 else
				 {
					mxyputs(xg,yg,ptr,bkgnd,frgnd);
					moutchar(xg+endcur,yg,' ',bkgnd,frgnd);
				 }
				}
		 }
		 if(!mode_text)
		 {
				c1 = ptr[loccur];
				ptr[loccur] = 0;
				set_semaphore(&screen);
				moveto(xg+w,yg);
				clear_semaphore(&screen);
				ptr[loccur] = c1;
		 }
		 else
		 {
				movetoxy(xg+loccur*lat_char_n,yg);
		 }

//		 GWGoto(row,col+loccur);
		 continue;
	}
	if (c==BS&&which_type!='E')
	{
		 keyboard_data=1;
		 if(which_type!='S')
		 if (loccur!=0)
		 {
			 if(!mode_text)
			 {
				c1 = ptr[loccur];
				ptr[loccur] = 0;
				set_semaphore(&screen);
				w=textwidth(ptr);
				pline(xg+w-1,yg,xg+w-1,yg+textheight("H"),Black);
				clear_semaphore(&screen);
				ptr[loccur] = c1;
			 }
			 loccur--;
			 movmem(ptr+loccur+1,ptr+loccur,endcur-loccur);
			 endcur--;
			 ptr[endcur]=0;
			 if(!mode_text)
			 {
//				bar(xg,yg,xg+width*lat_char_n-3,yg+textheight("H")+2);
				set_semaphore(&screen);
				bar(xg,yg,xg+width*lat_char_n-1,yg+textheight("H")+1);
				moveto(xg, yg);
				setcolor(frgnd);
				outtext(ptr);
				clear_semaphore(&screen);
			 }
			 else
			 {
				mxyputs(xg,yg,ptr,bkgnd,frgnd);
				moutchar(xg+endcur,yg,' ',bkgnd,frgnd);
			 }
			 if(!mode_text)
			 {
					set_semaphore(&screen);
					moveto(xg+loccur*lat_char_n, yg);
					clear_semaphore(&screen);
			 }
			 else
					movetoxy(xg+loccur,yg);
//			 GWGoto(row,col+loccur);
		 }
		 continue;
	}

	if(!select_tmp&&which_type!='E')
	{
	keyboard_data=1;
	if(which_type==DOUBLE)
		if((!isdigit(c))&&(c!='.'))
		 {
//			 c=mgetch();
//				 key.i = bioskey(0);
//				 c=key.ch[0];
			 continue;
		 }


//	if(i<(ncols-col))
		{
		 if( (which_type=='N' && (isdigit(c) || c=='.')) || (which_type=='A')
				 || (which_type=='S' && (sablon[loccur]=='A' || sablon[loccur]=='*' || (sablon[loccur]=='N' && isdigit(c)))))
		 {
			if(first)
			{
			 first=0;
			 endcur=loccur=1;
			 if(mode_text && strlen(ptr))
			 {
				lin_text[strlen(ptr)] = 0;
				mxyputs(xg,yg,lin_text,bkgnd,frgnd);
				lin_text[strlen(ptr)] = lin_text[0];
			 }
			 ptr[0]=c;
			 ptr[1]=0;
			}
			else
			if(which_type!='S')
			{
			 if(endcur==width)
				 {
					endcur--;
					if(loccur==width) loccur--;
				 }
			 movmem(ptr+loccur,ptr+loccur+1,endcur-loccur);
			 endcur++;
			 ptr[loccur++]=c;
			 ptr[endcur]=0;
			}
			else
			{
			 ptr[loccur++]=c;
			 if (loccur>=endcur) loccur--;
			 while(1)
			 {
					if(loccur>=endcur-1) break;
					if(sablon[loccur] != 'A' && sablon[loccur] != 'N' && sablon[loccur] != '*')
					{
					 loccur++;
					 if (loccur>=endcur) loccur--;
					}
					else
					 break;
			 }
			}

//		 putch(c);
			if(!mode_text)
			{
//				bar(xg,yg,xg+width*lat_char_n-3,yg+textheight("H")+2);
				set_semaphore(&screen);
				bar(xg,yg,xg+width*lat_char_n-1,yg+textheight("H")+1);
				moveto(xg, yg);
				setcolor(frgnd);
				if(which_type=='S' && sablon[loccur] == '*' )
				{
					sablon[loccur]=0;
					outtext(sablon);
					sablon[loccur]='*';
				}
				else
				{
				 outtext(ptr);
				 moveto(xg, yg);
				 c1 = ptr[loccur];
				 ptr[loccur] = 0;
				 outtext(ptr);
				 ptr[loccur] = c1;
				}
				clear_semaphore(&screen);
			}
			else
			{
				if(which_type=='S' && sablon[loccur] == '*' )
				{
					sablon[loccur]=0;
					mxyputs(xg,yg,sablon,bkgnd,frgnd);
					sablon[loccur]='*';
				}
				else
					mxyputs(xg,yg,ptr,bkgnd,frgnd);
			}
			if(!mode_text)
			{
//				moveto(xg+loccur*lat_char_n, yg);
			}
			else
				movetoxy(xg+loccur,yg);
//		 GWPuts(row, col, ptr,bkgnd,frgnd);
//		 GWGoto(row,col+loccur);
			hide_pointer();
		 }
		}
//	if (i<width/lat-1)
//			i++;
	 }
 }//while
 if(!mode_text)
 {
	c1 = ptr[loccur];
	ptr[loccur] = 0;
	set_semaphore(&screen);
	w=textwidth(ptr);
	pline(xg+w-1,yg,xg+w-1,yg+textheight("H"),bkgnd);
	clear_semaphore(&screen);
	ptr[loccur] = c1;
 }
 return c;
// last = c;
}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.021  ********
// ********        end        ********
// ***********************************

char wingets(char far *ptr, int row, int col, int width,
				 int bkgnd, int frgnd, char which_type='A', char *sablon=NULL, char retnokey = 0)
{
 wingets_help(0,ptr,row,col,width,bkgnd,frgnd,which_type,sablon,retnokey );
/*
 int n,i=0;
// *ptr=0;
	union {
		int i;
		char ch[2];
		} key;
 char c, c1, cur[2];
 int w,xg,yg,lung,first=0;
 int loccur,endcur;
 MouseStatus stat;

//		 lung=textheight("H")+LINE_SPACE;
 if(which_type=='S')
 {
	if(!strlen(ptr))
		memset(ptr,' ',strlen(sablon));
	for(i=0;i<strlen(sablon);i++)
		if(sablon[i]!='A' && sablon[i]!='N' && sablon[i]!='*')
			ptr[i]=sablon[i];
 }

		if(!row && !col)
		{
		 if(mode_text)
		 {
			xg=wherex();
			yg=wherey();
		 }
		 else
		 {
			xg=getx();
			yg=gety();
		 }
		}
		else
		{
		 xg = col;
		 yg = row;
		}

 if(!mode_text)
 {
		 set_semaphore(&screen);
		 setfillstyle(SOLID_FILL,bkgnd);
		 clear_semaphore(&screen);
 }
 if(which_type=='E')
 {
	if(!mode_text)
	{
	 set_semaphore(&screen);
	 bar(xg,yg,xg+width*lat_char_n-1,yg+textheight("H")+1);
	 moveto(xg, yg);
	 setcolor(frgnd);
	 outtext(ptr);
	 moveto(xg+loccur*lat_char_n, yg);
	 clear_semaphore(&screen);
	}
	else
	{
	 mxyputs(xg,yg,ptr,bkgnd,frgnd);
	}
 }
 else
 if(!select_tmp)
 {
	 if(!mode_text)
	 {
		set_semaphore(&screen);
		bar(xg,yg,xg+width*lat_char_n-1,yg+textheight("H")+1);
		moveto(xg, yg);
		if(which_type!='S')
			setcolor(Lightred);
		outtext(ptr);
		clear_semaphore(&screen);
	 }
	 else
	 {
		if(which_type!='S')
		 mxyputs(xg,yg,ptr,Red,frgnd);
	 }
 }

 if(which_type!='S'&&which_type!='E')
 {
	 first=1;
 }

 if(mode_text)
	 movetoxy(xg, yg);
 else
 {
	 set_semaphore(&screen);
	 moveto(xg, yg);
	 clear_semaphore(&screen);
 }
 endcur=strlen(ptr);
 loccur=0;
 c = 0;
 if(mode_text)
 {
	;
// mtextcolor(frgnd);
// mtextbackground(bkgnd);
 }
 else
 {
	set_semaphore(&screen);
	setfillstyle(SOLID_FILL,bkgnd);
	cur[0]='_';
	cur[1]=0;
//  setcolor(White);
	if( !retnokey )
	{
		c1 = ptr[loccur];
		ptr[loccur] = 0;
		w=textwidth(ptr);
		pline(xg+w-1,yg,xg+w-1,yg+textheight("H"),Yellow);
		ptr[loccur] = c1;
	}
//  outtextxy(xg+loccur*lat_char_n, yg, cur);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	setcolor(frgnd);
	clear_semaphore(&screen);
 }
 while(1)
 {
	display_pointer();
	while(!bioskey_new(1))
	{
	 if(!mode_text)
	 {
		if( cur_count==(retnokey?2000:5000) )
		{
//		 setcolor(White);
			c1 = ptr[loccur];
			ptr[loccur] = 0;
	    set_semaphore(&screen);
			w=textwidth(ptr);
			pline(xg+w-1,yg,xg+w-1,yg+textheight("H"),Yellow);
	    clear_semaphore(&screen);
			ptr[loccur] = c1;
//		 outtextxy(xg+loccur*lat_char_n, yg, cur);
		}
		if( cur_count++>(retnokey?4000:10000) )
		{
//		  setfillstyle(SOLID_FILL,bkgnd);
			c1 = ptr[loccur];
			ptr[loccur] = 0;
			set_semaphore(&screen);
			w=textwidth(ptr);
			pline(xg+w-1,yg,xg+w-1,yg+textheight("H"),bkgnd);
	    clear_semaphore(&screen);
			ptr[loccur] = c1;
			cur_count=0;
		}
	 }
	 print_alarm_word();
	 mouse_status(stat);
	 if(stat.leftButton)
	 {
			while(!get_button_released(BLEFT,stat));
//			while(stat.leftButton) 	mouse_status(stat);
//			last = '\0';
			if(!mode_text)
			{
				c1 = ptr[loccur];
				ptr[loccur] = 0;
				set_semaphore(&screen);
				w=textwidth(ptr);
				pline(xg+w-1,yg,xg+w-1,yg+textheight("H"),bkgnd);
				clear_semaphore(&screen);
				ptr[loccur] = c1;
			}
			return 0;
	 }
	 if( retnokey )
	 {
		return 1;
	 }
	}
	key.i = bioskey_new(0);
//	c=mgetch();
	c=key.ch[0];
	hide_pointer();
	retnokey=0;

	if( c==0x0d || c=='\t' || c==27)
		break;
	if(c==0)       // tasta speciala
	{
		 if(first)
		 {
			first=0;
			if(!mode_text)
			{
					set_semaphore(&screen);
					bar(xg,yg,xg+width*lat_char_n-1,yg+textheight("H")+1);
					moveto(xg, yg);
					setcolor(frgnd);
					outtext(ptr);
					moveto(xg+loccur*lat_char_n, yg);
					clear_semaphore(&screen);
			}
			else
			{
					mxyputs(xg,yg,ptr,bkgnd,frgnd);
			}
		 }
		 c=key.ch[1];
		 if(c==80 || c==72)     //down  and up
				break;
		 if(((c==75) || (c==77)) && (select_tmp||which_type=='E'))
				break;
		 if(c==75)     //left
		 {
				if(!mode_text)
				{
					c1 = ptr[loccur];
					ptr[loccur] = 0;
					set_semaphore(&screen);
					w=textwidth(ptr);
					pline(xg+w-1,yg,xg+w-1,yg+textheight("H"),Black);
					clear_semaphore(&screen);
					ptr[loccur] = c1;
				}
				loccur--;
				if (loccur<0) loccur=0;
				if(which_type=='S')
				 while(1)
				 {
					if(!loccur) break;
					if(sablon[loccur] != 'A' && sablon[loccur] != 'N')
					{
					 loccur--;
					 if (loccur<0) loccur=0;
					}
					else
					 break;
				 }
		 }
		 if(c==77)     //right
		 {
				if(!mode_text)
				{
				 c1 = ptr[loccur];
				 ptr[loccur] = 0;
				 set_semaphore(&screen);
				 w=textwidth(ptr);
				 pline(xg+w-1,yg,xg+w-1,yg+textheight("H"),Black);
	       clear_semaphore(&screen);
				 ptr[loccur] = c1;
				}
				loccur++;
				if (loccur>=endcur) loccur--;
				if(which_type=='S')
				 while(1)
				 {
					if(loccur==endcur) break;
					if(sablon[loccur] != 'A' && sablon[loccur] != 'N')
					{
					 loccur++;
					 if (loccur>=endcur) loccur--;
					}
					else
					 break;
				 }
		 }

		 if(c==83&&which_type!='E')       // del
		 {
			 keyboard_data=1;
			 if(which_type=='S')
			 {
				 if(sablon[loccur]=='N')
					 ptr[loccur] = '0';
				 else
						ptr[loccur] = ' ';
				 if(!mode_text)
				 {
					set_semaphore(&screen);
					bar(xg,yg,xg+width*lat_char_n-1,yg+textheight("H")+1);
//					bar(xg,yg,xg+width*lat_char_n-3,yg+textheight("H")+2);
					moveto(xg, yg);
					setcolor(frgnd);
					outtext(ptr);
					clear_semaphore(&screen);
				 }
				 else
				 {
					mxyputs(xg,yg,ptr,bkgnd,frgnd);
				 }
			 }
			 else
			 if (endcur!=loccur)
				{
				 movmem(ptr+loccur+1,ptr+loccur,endcur-loccur);
				 endcur--;
				 ptr[endcur]=0;
				 if(!mode_text)
				 {
					set_semaphore(&screen);
					bar(xg,yg,xg+width*lat_char_n-1,yg+textheight("H")+1);
//					bar(xg,yg,xg+width*lat_char_n-3,yg+textheight("H")+2);
					moveto(xg, yg);
					setcolor(frgnd);
					outtext(ptr);
					moveto(xg+loccur*lat_char_n, yg);
	        clear_semaphore(&screen);
				 }
				 else
				 {
					mxyputs(xg,yg,ptr,bkgnd,frgnd);
					moutchar(xg+endcur,yg,' ',bkgnd,frgnd);
				 }
				}
		 }
		 if(!mode_text)
		 {
				c1 = ptr[loccur];
				ptr[loccur] = 0;
				set_semaphore(&screen);
				moveto(xg+w,yg);
				clear_semaphore(&screen);
				ptr[loccur] = c1;
		 }
		 else
		 {
				movetoxy(xg+loccur*lat_char_n,yg);
		 }

//		 GWGoto(row,col+loccur);
		 continue;
	}
	if (c==BS&&which_type!='E')
	{
		 keyboard_data=1;
		 if(which_type!='S')
		 if (loccur!=0)
		 {
			 if(!mode_text)
			 {
				c1 = ptr[loccur];
				ptr[loccur] = 0;
				set_semaphore(&screen);
				w=textwidth(ptr);
				pline(xg+w-1,yg,xg+w-1,yg+textheight("H"),Black);
				clear_semaphore(&screen);
				ptr[loccur] = c1;
			 }
			 loccur--;
			 movmem(ptr+loccur+1,ptr+loccur,endcur-loccur);
			 endcur--;
			 ptr[endcur]=0;
			 if(!mode_text)
			 {
//				bar(xg,yg,xg+width*lat_char_n-3,yg+textheight("H")+2);
				set_semaphore(&screen);
				bar(xg,yg,xg+width*lat_char_n-1,yg+textheight("H")+1);
				moveto(xg, yg);
				setcolor(frgnd);
				outtext(ptr);
				clear_semaphore(&screen);
			 }
			 else
			 {
				mxyputs(xg,yg,ptr,bkgnd,frgnd);
				moutchar(xg+endcur,yg,' ',bkgnd,frgnd);
			 }
			 if(!mode_text)
			 {
					set_semaphore(&screen);
					moveto(xg+loccur*lat_char_n, yg);
					clear_semaphore(&screen);
			 }
			 else
					movetoxy(xg+loccur,yg);
//			 GWGoto(row,col+loccur);
		 }
		 continue;
	}

	if(!select_tmp&&which_type!='E')
	{
	keyboard_data=1;
	if(which_type==DOUBLE)
		if((!isdigit(c))&&(c!='.'))
		 {
//			 c=mgetch();
//				 key.i = bioskey(0);
//				 c=key.ch[0];
			 continue;
		 }


//	if(i<(ncols-col))
		{
		 if( (which_type=='N' && (isdigit(c) || c=='.')) || (which_type=='A')
				 || (which_type=='S' && (sablon[loccur]=='A' || sablon[loccur]=='*' || (sablon[loccur]=='N' && isdigit(c)))))
		 {
			if(first)
			{
			 first=0;
			 endcur=loccur=1;
			 if(mode_text && strlen(ptr))
			 {
				lin_text[strlen(ptr)] = 0;
				mxyputs(xg,yg,lin_text,bkgnd,frgnd);
				lin_text[strlen(ptr)] = lin_text[0];
			 }
			 ptr[0]=c;
			 ptr[1]=0;
			}
			else
			if(which_type!='S')
			{
			 if(endcur==width)
				 {
					endcur--;
					if(loccur==width) loccur--;
				 }
			 movmem(ptr+loccur,ptr+loccur+1,endcur-loccur);
			 endcur++;
			 ptr[loccur++]=c;
			 ptr[endcur]=0;
			}
			else
			{
			 ptr[loccur++]=c;
			 if (loccur>=endcur) loccur--;
			 while(1)
			 {
					if(loccur>=endcur-1) break;
					if(sablon[loccur] != 'A' && sablon[loccur] != 'N' && sablon[loccur] != '*')
					{
					 loccur++;
					 if (loccur>=endcur) loccur--;
					}
					else
					 break;
			 }
			}

//		 putch(c);
			if(!mode_text)
			{
//				bar(xg,yg,xg+width*lat_char_n-3,yg+textheight("H")+2);
				set_semaphore(&screen);
				bar(xg,yg,xg+width*lat_char_n-1,yg+textheight("H")+1);
				moveto(xg, yg);
				setcolor(frgnd);
				if(which_type=='S' && sablon[loccur] == '*' )
				{
					sablon[loccur]=0;
					outtext(sablon);
					sablon[loccur]='*';
				}
				else
				{
				 outtext(ptr);
				 moveto(xg, yg);
				 c1 = ptr[loccur];
				 ptr[loccur] = 0;
				 outtext(ptr);
				 ptr[loccur] = c1;
				}
				clear_semaphore(&screen);
			}
			else
			{
				if(which_type=='S' && sablon[loccur] == '*' )
				{
					sablon[loccur]=0;
					mxyputs(xg,yg,sablon,bkgnd,frgnd);
					sablon[loccur]='*';
				}
				else
					mxyputs(xg,yg,ptr,bkgnd,frgnd);
			}
			if(!mode_text)
			{
//				moveto(xg+loccur*lat_char_n, yg);
			}
			else
				movetoxy(xg+loccur,yg);
//		 GWPuts(row, col, ptr,bkgnd,frgnd);
//		 GWGoto(row,col+loccur);
			hide_pointer();
		 }
		}
//	if (i<width/lat-1)
//			i++;
	 }
 }//while
 if(!mode_text)
 {
	c1 = ptr[loccur];
	ptr[loccur] = 0;
	set_semaphore(&screen);
	w=textwidth(ptr);
	pline(xg+w-1,yg,xg+w-1,yg+textheight("H"),bkgnd);
	clear_semaphore(&screen);
	ptr[loccur] = c1;
 }
 return c;
// last = c;
*/
}

int doubleclick(void)
{
  MouseStatus stat;
  char doublec = 0;
//  while(!get_button_released(BLEFT,stat));
  long l = microsec;
  long l1 ;
	while(1)
  {
	 l1 = microsec;
	 if(l1-l >= 0)
	 {
		 if(l1-l > 60000L)
			 break;
	 }
	 else
	 {
		 if(l-l1 < 60000L)
			 break;
	 }
	 mouse_status(stat);
	 if(stat.leftButton)
	 {
		doublec = 1;
		while(!get_button_released(BLEFT,stat));
		break;
	 }
  }
  return doublec;
}



