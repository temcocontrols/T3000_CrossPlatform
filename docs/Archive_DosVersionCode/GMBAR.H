///////////////////////////////////////////////////////
//                                                   //
// Implements the classes GMenuBar and GPopUP        //
//                                                   //
///////////////////////////////////////////////////////

#ifndef _GMBAR.H
#define _GMBAR.H

extern void *newalloc(long size);
extern void newdelete(void *ptr);
#include "gview.h"
#include <string.h>
#include <stdio.h>
#include <windows.h>

#define BARMENU 1
#define POPUPMENU 0

#define M0 0
#define M1 10
#define M2 20
#define M3 30
#define M4 40
#define M5 50
#define M6 60

class GPopUp;

/************************************/

class GMenuBar:public GView
{
 public:
	int nrcur, nrmax;
	hot_box table[11];   // table that holds the limits of the
											 // "hot" rectangles in which mouse
											 // events are effective
	GPopUp *pGPopUpTable;
	int highlight;
	int selectbkgcolour;
	int font, char_size;
 private:
	int fond, type_menu;
	int frg;
	char huge ***list;

	uint gt;

	char far *munder;
	HANDLE munder_handle;
	char hotletter[11];  // holds the letters which can be com-
											 // bined with the Alt key in order to
											 // get a selection

  int actnr;           // holds the # of action to be performed
  char set_popup;
  char double_print;
  char text_height;

 public:

	Pointxy hooks[11];     // holds the coordinates of the points
								  // from which the popups are "hooked"
	GMenuBar(uint ltx,uint lty, uint rbx,uint rby, int cfond ,int cfrg, int chigh,
				int max, int type, char huge ***plist, int ffont=DEFAULT_FONT,
				int cchar_size=1, char double_print=0);
																						 // constructor
	~GMenuBar(); 															       // destructor

	void HideMBar(void);
	void DisplayMBar(void);
	void ShowunderMBar(void);
	void GShowMenuBar(char huge **list, int *onscreen=NULL); // slaps the menu bar on the screen

	void ReleaseMBar(void);     // wipes the menu bar off the screen

	void far HandleEvent(void); // handles the mouse events

	int GReturn(void);          // returns the nr. of the action selected
										//from the popup
															// nr.act=(7*nr.popup+index) where nr.popup
										// is the offset of the popup's name from
															// the beginning of the menubar list and
															// index is the offset of the action's name
															// from the beginning of the popup list
	void cursor(char bkg);
	int select(int);
	void *operator new(size_t size){return(newalloc((long)size));};
	void operator delete(void *ptr){newdelete(ptr);};
};

/*************************************/

class GPopUp:public GView
{
 public:
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.001  ********
// ********       begin       ********
// ***********************************
	int Flag_help;
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.001  ********
// ********        end        ********
// ***********************************
	GMenuBar *bar_menu;
 private:
	int nrcur, nrmax, onscreen, style;

	uint nr;
	Pointxy hook;                 // the point from which the popup
															// will hang
	char huge **list;

	hot_box table[10];           // table that holds the limits of the
															// "hot" rectangles in which mouse
															// events are effective

	char hotletter[10];          // the same as for menubar
	int font, char_size;
	char double_print;
	char text_height;
	int selectbkgcolour;

 public:

	GPopUp(int lx, int ly, char **mess, int onscr = 0, int style = 1,
				 int font=DEFAULT_FONT, int char_size=1, char double_print=0);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.002  ********
// ********       begin       ********
// ***********************************
	GPopUp(int flag_help,char *need_help,int lx, int ly, char **mess, int onscr = 0, int style = 1,
				 int font=DEFAULT_FONT, int char_size=1, char double_print=0);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.002  ********
// ********        end        ********
// ***********************************
	GPopUp(void);                   // constructor
// sets the number of the popup, and the (X,Y) coordinates of the hook point
	void SetPopUp(uint which,uint hx,uint hy, int onscreen = 0,
						int font=DEFAULT_FONT, int char_size=1, char double_print=0);

	void SetList(char huge **);          // takes a list of strings and
																	// calculates the limits of the
																	// area wherein the popup can fit

	void GShowPopUp(void);              // slaps the popup on the screen
	void GBorder(void);

	void ReleasePopUp(int);       // wipes the popup off the screen

	int  GReturn(void);              // waits for an action to be selected
	int  PSelected();              // waits for an action to be selected
																 // (either by an Alt-key combination
																 // or by a mouse left button click).
																 // If no action from this popup is
																 // desired, a click of the right button
																 // will restore the situation existing
																 // before the popup was called
	void cursor(char bkg);
	void *operator new(size_t size){return(newalloc((long)size));};
  void operator delete(void *ptr){newdelete(ptr);};
};

#endif