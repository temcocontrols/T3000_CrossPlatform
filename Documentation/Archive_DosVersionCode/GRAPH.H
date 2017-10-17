//////////////////////////////////////////////////////////////
//                                                          //
// Implements the classes GGraph   //
//                                                          //
//////////////////////////////////////////////////////////////

#ifndef _GGRAPH_H
#define _GGRAPH_H

#include "gwin.h"
#include "t3000def.h"
#include "aio.h"

//#define NOREAD   1
//#define READ     0
#define STACK    1
#define NO_STACK 0
#define ANYWHERE 10
#define SIZE 15
#define MAX_FIELDS 50
#define HIGH_FIELD_TITLE 20
#define COL_SPACE  3
#define LINE_SPACE (mode_text ? 0 : 4)
#define TOP_SPACE 5
#define SPACE_CHAR 1

#define  MAXSAMPLEUPDATE 35
#define  MAX_SAMPLE      200 //300
#define  MAX_INP 14
#define  MAX_SAMPLE_MEM  50 //100
#define MAX_MEM_DIG_BUF  10004    //6004;
#define MAX_HEADERS_AMON 16
#define MAX_HEADERS_DMON 17

#define ANALOGDATA     1
#define DIGITALDATA    2
#define DIGITALBUFSIZE 3
#define ANALOGBUFSIZE  4

///////////////////////////
//                       //
//    Class GGraph        //
//                       //
///////////////////////////

class GGraph:public GWDialog
{
 public:
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.053  ********
// ********       begin       ********
// ***********************************
	int Flag_help;
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.053  ********
// ********        end        ********
// ***********************************
	hot_box big_viewport;
	hot_box big;
	hot_box viewports[10];
	hot_box Zoomout;
	hot_box Zoomoutint;
	hot_box Up;
	hot_box Down;
	hot_box Zoomin;
	hot_box Left;
	hot_box Right;
	hot_box Label[16];
	hot_box View;
	hot_box Save;
	hot_box Delete;
	hot_box Reset;
	hot_box Exit;
	hot_box Timerange;
	char color[16];
	char viewport;
	char nviewports;
	int  onoff;
	unsigned int *ptablex[14];
	unsigned int *ptabley[14];
	int ind_ptable[14];
	char *ulinex,*uliney;
  int  linex, liney;

	int nsample_unit, npix_unit;
	double npix_sample;
	State status;
	int panel, network;
	char local;

 public:
	GGraph( int lx, int ly, int rx, int ry, int stk, int ppanel, int network, int local);  // constructor (the same as GView)
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.054  ********
// ********       begin       ********
// ***********************************
	GGraph( int flag_help,char *need_help,int lx, int ly, int rx, int ry, int stk, int ppanel, int network, int local);  // constructor (the same as GView)
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.054  ********
// ********        end        ********
// ***********************************
	void GShowGraph(int vspot);
	int drawgrid(int sample, long interv, long time_first_sample);
	int draw(int ind);
	int drawver();
//	int minmax(int where, int ind,float *min, float *max);
	int upgroup(int type,int ind);  //type=1 add; =0 del
	int drawpoint(int ind);
	int drawall();
//	virtual void GWGoto(uint row, uint col);
//	virtual int GWx(int);
//	virtual int GWy(int);
//	void GGPuts(uint);
//	void GGDrawGrid(int);
//	void GGLeftGrid();
//	void GGZoomInGrid(void);
//	void GGZoomOutGrid(void);
	virtual int HandleEvent();      // handles the mouse events
	~GGraph();  // destructor
//	void *operator new(size_t size){return(newalloc((long)size));};
//  void operator delete(void *ptr){newdelete(ptr);};
};

#endif