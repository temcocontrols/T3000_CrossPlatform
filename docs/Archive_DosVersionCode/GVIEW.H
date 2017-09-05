//////////////////////////////////////////
//                                      //
// Implements the base class GView      //
//                                      //
//////////////////////////////////////////


#ifndef _GVIEW_H
#define _GVIEW_H
#define LAT 8-8

#include <windows.h>
#include "mouse.h"
#include <alloc.h>
#include <conio.h>
#include "xms.h"
//#include <graphics.h>

typedef unsigned char BOOLEAN;

typedef struct hot_box
{

 Pointxy top;
 Pointxy bot;

} hot_box;


///////////////////////////////////////////////
//                                           //
// Base class for describing a certain view  //
//                                           //
///////////////////////////////////////////////

class GView
{
 public:
	Pointxy ltop;             //view limits
	Pointxy rbottom;

	int save;
 protected:

	HANDLE handle;
	char far *under1,
			 far *under2,
			 far *under3,
			 far *under4;       //saved area underneath

	uint flag;              //tells if the area saved has
													//been split into four
	XmsMem   *pXms;

 public:
	GView(){};																//constructor
	GView(uint lx,uint ly, uint rx,uint ry);  //constructor
	~GView();																  //destructor
	void SaveArea(void);    //saves area (used only for
													//small areas
	void RestoreArea(void); //restores the area previously
													//saved
};


#endif