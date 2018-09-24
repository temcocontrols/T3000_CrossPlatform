//////////////////////////////////////////////////////////////
//                                                          //
// Implements the classes GWindow, GDWindow and GWControl   //
//                                                          //
//////////////////////////////////////////////////////////////

#ifndef _GWIN_H
#define _GWIN_H

#define TEXT_MODE_WINDOW    0
#define GRAPHIC_MODE_WINDOW 1

extern void *newalloc(long size);
extern void newdelete(void *ptr);
extern int Blue;
extern int White;                  

#include "gview.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <math.h>
#include <windows.h>
#include <graphics.h>

#define NOREAD   1
//#define READ     0
#define STACK    1
#define NO_STACK 0
#define DIALOG 0
#define WIN_ERROR 2
#define GRID 1
#define GRIDINS 3
extern int Black;

///////////////////////////
//                       //
//    Class GWindow      //
//                       //
///////////////////////////

class GWindow:public GView
{
 private:
	char  mode;            // TEXT_MODE_WINDOW    = text mode
												 // GRAPHIC_MODE_WINDOW = graphic mode
	int  error;

	int w_fonttype, old_fonttype;
	int w_charsize, old_charsize;
	int doubleprint;
 public:
		hot_box close_spot;  // defines the limits of the rectangle in which,
												 // if the left button is clicked, the window will
												 // close up
		int select;
		int title_status;
		int spot;
		BOOLEAN on_screen;   // says if the window is currently on screen
		char esc;
		char retnokey;       // return if no  key pressed
		char bkgcolour;         // colour of the window background

 protected:
	char *title;          // window title
	HANDLE title_handle;
	char	 title_bkgcolour,          // colour of the title background
				 border_bkgcolour,         // colour of the border background
				 border_frgcolour;         // colour of the border foreground

	unsigned char attribute;

	int tx,              //coordinates of the operational window
			ty,
			bx,
			by;

	uint nrows,          // # of rows that can be written in the window
			 ncols;          // # of columns....

	hot_box lscroll;
	hot_box rscroll;
	hot_box uscroll;
	hot_box dscroll;
	hot_box ziscroll;
	hot_box zoscroll;
	hot_box mscroll;


	int grid;
	uint NO_STK;         // the view is not monitored by Control class

 private:
	void GWInit(int lx, int ly, int rx, int ry, uint stk, int but, int fonttype=DEFAULT_FONT, int charsize=1, char doubleprint=0);																								// constructor

 public:
	GWindow(int lx, int ly, int rx, int ry, uint stk, int but, int fonttype=DEFAULT_FONT, int charsize=1, char doubleprint=0); // constructor
	GWindow(int lx, int ly, int rx, int ry, char far *ptitle,
					uint bkgclr, uint title_bkgclr, uint border_frgclr,
					uint stk, int but, int fonttype=DEFAULT_FONT, int charsize=1, char doubleprint=0);                     // constructor
	~GWindow();  // destructor

	void GWBorder(void);
	uint GWRetLimits(int); // returns the limits of the window (with 0,1,2,3
				// you get the limits of the entire window, namely
				// ltop.x, ltop.y, rbottom.x, rbottom.y, and with
				// 5,6,7,8  you get the limits of the operational
				// window, namely tx,ty,bx,by)

	void GWSet(char far *, uint bkgclr, uint title_bkgclr, uint border_frgclr = Black); // sets the window title, the colour
							// of the window and the background
							// colour for title

	void GShowWindow(int, int saveunder = 1);     // slaps the window on the screen
	void GReleaseWindow();  // wipes the window off the screen

	virtual void GWGoto(int, int); // goes to the specified row and column
	virtual int GWx(int);
	virtual int GWy(int);

	void GWPutch(int, int, char ); // puts  a character at the specified
					 // row and column

	void GWPuts(int, int, char *,int,int); // the same for a string
	void GWPuts(int, int, int, char *, int, int); // the same for a string
	uint GMaxCols(){ return ncols;};
	uint GMaxRows(){ return nrows;};
	void GWchbkg(int lx, int ly, int width, int bkgnd, int frgnd, int unchangecol=127, int height = 0);

	virtual int HandleEvent();      // handles the mouse events
	void *operator new(size_t size){return(newalloc((long)size));};
  void operator delete(void *ptr){newdelete(ptr);};

};


/////////////////////////////
//                         //
//     Class GWControl     //
//                         //
/////////////////////////////

class GWControl               // keeps track of six windows simultaneously
			      // present on the screen  by implementing
			      // a stack
{
 public:

  GWindow* objects[6];

  int level;

  GWControl(){ level=-1;};
	void *GWActWindow();
	void Push (GWindow *);
  void Pop  ();
  int GWHandleEvent();

};

//////////////////////////////
//                          //
//     Class GWDialog       //
//                          //
//////////////////////////////

class GWDialog:public GWindow
{
 public:
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.033  ********
// ********       begin       ********
// ***********************************
		int Flag_help;
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.033  ********
// ********        end        ********
// ***********************************

		struct objects {
			 void (*f)(GWDialog *);
			 char *ptr;
			 char *sablon;
			 hot_box box;
			 int xrel,yrel;
			 char bkgnd, frgnd;
			 char sbkgnd, sfrgnd;
			 char width;
			 } *objects[25];
//		HANDLE handle_obj[20];
		char nrobj,index_obj;
		char first,last,last_mouse,exitCR,enter;
		int index_cur;
		char updown;
		signed char ok,cancel,nrok,nrcancel;
      signed char ok_char, cancel_char, xok, xcancel;

 protected:

	 void GDGet  (char far * , int, int, int, int, int, int, char *sablon=NULL);

 public:

	GWDialog(int, int, int, int, int, int, int fonttype=DEFAULT_FONT, int charsize=1, char doubleprint=0);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.020  ********
// ********       begin       ********
// ***********************************
	GWDialog(int, char *,int, int, int, int, int, int, int fonttype=DEFAULT_FONT, int charsize=1, char doubleprint=0);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.020  ********
// ********        end        ********
// ***********************************
// GWDialog(uint, uint, uint, uint, uint, uint );
// void wingets(char far * , uint, uint, int, uint, uint, uint);
	void   GDPuts(int, int, char *, int, int, int); // the same as GWPuts, but with
																									// background and foreground colours
																									// for the writing

	void   GDGets(char far * ,int, int, int, int, int); // gets a string at a specified
																											// position, with the specified
																											// colours

	double GDGetd(int, int, int, int, int);  // the same as GDGets but returns a double

	void GDGetn (char far * ptr,
					int row,   int col, int width,
					int bkgnd, int frgnd);

	void GDGetsablon (char far * ptr,
					int row,   int col, int width,
					int bkgnd, int frgnd, char *sablon);

	virtual int HandleEvent();       // handles the mouse events
// void GDDef_object(void (*f)(GWDialog *), int, int, int, char, char);
// void GDDef_object(void (*f)(GWDialog *), int, int, int, char, char, char *ptr=NULL, char sbkgnd=0, char sfrgnd=15, char *sablon=NULL,
	void GDDef_object(void (*f)(GWDialog *), int, int, int, char, char, char *ptr=NULL, char sbkgnd=Blue, char sfrgnd=White, char *sablon=NULL,
						 signed char ok_cancel=-1, char ok_cancel_char=0, char xokcancel=0);
	int Select();
	~GWDialog();
// void *operator new(size_t size){return(newalloc((long)size));};
// void operator delete(void *ptr){newdelete(ptr);};
};

/*****************************************/

void DisplayError(char *);    // displays an error message into a window

void RadioButton(hot_box& ,
		 char  *,
		 uint, uint); // displays a radio button within the spe-
						// cified limits, with the specified cha-
						// racter and colors for background and shade

uint GetFile(char *title, char *defaultname, char *path, char *term, char *ptr,
			 int hx, int hy, uint noread,int bkgnd, int frgnd, int local=1);
			      // gets the name of a file selected from a
						// specified(noread=NOREAD) or specified
						// (noread=READ) directory. The window for
						// selection will have the left corner
						// specified by hx,hy.

#endif