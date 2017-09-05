//////////////////////////////////////////////////////////////
//                                                          //
// Implements the classes GWindow, GDWindow and GWControl   //
//                                                          //
//////////////////////////////////////////////////////////////

#ifndef _GGRID_H
#define _GGRID_H

#include "gwin.h"
#include "fxengine.h"
#include "t3000def.h"
#include "aio.h"

#define SENDBANK    0
#define SENDPOINTS  1
#define FULLBANK    0
#define SMALLBANK   1

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

class Output_block;
class Input_block;
class Var_block;
class Controller_block;
class Weekly_routine_block;
class Weekly_routine_time_block;
class Annual_routine_block;
class Annual_routine_time_block;
class Control_group_block;
class Monitor_block;
class Amon_inputs_block;
class Password_block;
class Station_block;
class Array1_block;
class Alarm_block;
class Alarm_set_block;
class Units_block;
class Tbl_block;
class Array_block;
class Ayvalue_block;
class Connect_com_block;
class Net_block;
class Netstat_block;
class Netstatus_block;

///////////////////////////
//                       //
//    Class GGrid        //
//                       //
///////////////////////////

class GGrid:public GWDialog
{
 public:
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.013  ********
// ********       begin       ********
// ***********************************
	int Flag_help;
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.013  ********
// ********        end        ********
// ***********************************

// ***********************************
// *********  William  ***************
// *********  begin    ***************
// ***********************************
	FILE *pf;
	int field_wide[20];
	int line_count; // count data line
// ***********************************
// *********  William  ***************
// *********   end    ***************
// ***********************************
	int w_field, w_lfield, w_record, w_urecord,w_nfields;
	int modify, grid_error;
	FILEHANDLE fh;
	char *ptr_block;
	char refresh_table[24];
//	Sub_a_b Gnet_type;
	signed char Gtype;
	byte point_type, Gpoint_num;
	byte Gpanel;
	byte Glocal;
	int  Gnetwork;
	int  fground;
 protected:
	int  w_rfield;
	int w_nrecords, w_drecord;
	int w_nlfield;

	Pointxy inltop,inrbottom;


	char header_bkgcolour;     // colour of the background for field name
	char filename[65];
	const struct FieldStruct *recstruct;
	RECORDNUMBER NRec;
	int fields_number;
//	struct FileInfo fileinfo;
	int Gpanel_type;              //STANDARD, ....
	byte bank, max_bank;
	int max_points_bank ;
	int index_max_bank;
	byte descriptor;
 public:
	union  pointer_point_obj  {
		Output_block *out;
		Input_block *in;
		Var_block *var;
		Controller_block *con;
		Weekly_routine_block *wr;
		Weekly_routine_time_block *wr_time;
		Annual_routine_block *ar;
		Annual_routine_time_block *ar_y;
		Program_block *prg;
		Control_group_block *grp;
		Control_graphic_group_block *ggrp;
		Monitor_block *amon;
		Amon_inputs_block *amon_input;
		Password_block *user_name;
		Station_block *st;
		Array1_block *array;
		Alarm_block *alarmm;
		Alarm_set_block *alarms;
		Units_block *units;
		Tbl_block *tbl;
		Array_block *ay;
		Ayvalue_block *ayvalue;
		Dial_list_block *sl;
		Connect_com_block *ccom;
		Net_block *net;
		Netstat_block *netstat;
    Netstatus_block *ns;
	} obj;
	int t_fields[50];

 private:
	void GGInit( int lx, int ly, int rx, int ry, int stk, char *fname,
					byte Point_type, byte Panel_type, byte Panel, int Network,
					signed char Type=0, byte Point_num=0);

 public:
	GGrid( int lx, int ly, int rx, int ry, int stk, char *fname,
				 byte Point_type, byte Panel_type, byte Panel, int Network,
				 signed char Type=0, byte Point_num=0, int font_type=DEFAULT_FONT, int charsize=1, char doubleprint=0);		// constructor
	GGrid( int lx, int ly, int rx, int ry, char far *ptitle,
				 uint bkgclr, uint title_bkgclr, uint border_frgclr, int stk, char *fname,
				 byte Point_type, byte Panel_type, byte Panel, int Network,
				 signed char Type=0, byte Point_num=0, int font_type=DEFAULT_FONT, int charsize=1, char doubleprint=0);		// constructor
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.014  ********
// ********       begin       ********
// ***********************************
	GGrid( int flag_help,char *need_help,int lx, int ly, int rx, int ry, int stk, char *fname,
				 byte Point_type, byte Panel_type, byte Panel, int Network,
				 signed char Type=0, byte Point_num=0, int font_type=DEFAULT_FONT, int charsize=1, char doubleprint=0);		// constructor
	GGrid( int flag_help,char *need_help,int lx, int ly, int rx, int ry, char far *ptitle,
				 uint bkgclr, uint title_bkgclr, uint border_frgclr, int stk, char *fname,
				 byte Point_type, byte Panel_type, byte Panel, int Network,
				 signed char Type=0, byte Point_num=0, int font_type=DEFAULT_FONT, int charsize=1, char doubleprint=0);		// constructor
// ***********************************
// ********      mao hui      ********
// ********  1997.8.3 NO.014  ********
// ********        end        ********
// ***********************************
	void GShowGrid(void);     // slaps the window on the screen
	void GGPutRecord(int,int,int);
	void GGPutFieldName(int);
	virtual void GWGoto(int row, int col);
	virtual int GWx(int);
	virtual int GWy(int);
	void GGPuts(int);
	void GGDrawGrid(int);
	void GGReDrawGrid();
	void GGLeftGrid();
	void GGLeftRightGrid(int);
	void GGPutField(int field, int, int);
	void GGPutCol(int,int);
	void GGUpDownGrid(int);
	void GGZoomInGrid(void);
	void GGZoomOutGrid(void);
	void GGSizeGrid(void);
	void GGMoveGrid(int);
	void GTestMove(int where,int *plx,int *ply,int *prx,int *pry);
	void Graphic_GTestMove(int where,int *plx,int *ply,int *prx,int *pry);
	void GGShowCur(int);
	void GGHideCur(int);
	void count_fields(void);
	int FGetRec(FILEHANDLE fh, pointer_point_obj  obj);
	int FGotoRec(FILEHANDLE fh, pointer_point_obj  obj,RECORDNUMBER record_number);
	int FClose(FILEHANDLE fh, pointer_point_obj  obj);
	int FGetAlpha(FILEHANDLE fh,pointer_point_obj obj,FIELDHANDLE hfield,int bufsize,char *dest);
	int FPutAlpha(FILEHANDLE fh,pointer_point_obj obj,FIELDHANDLE hfield,char *buf);
	char *FFldName(FILEHANDLE hfile,pointer_point_obj  obj, FIELDHANDLE hfield);
	int FFldSize(FILEHANDLE hfile,pointer_point_obj  obj, FIELDHANDLE hfield);
	int FNextRec(FILEHANDLE hfile,pointer_point_obj  obj);
	int send(void);
	int readdes(void);
	void create_obj(void);
	void change_bank(int how);
	virtual int HandleEvent(void);      // handles the mouse events
	int GSend(int type = SENDBANK);
//	void GReadNet(int);
	void GRead(int type = FULLBANK);
	~GGrid( );  // destructor
	void *operator new(size_t size);
	void operator delete(void *p);
// ***********************************
// *********  William  ***************
// *********  begin    ***************
// ***********************************
	int  GPrintRecord(int);
	int  GPrintGrid(int);
	void time_date(char *);
	void PrintBasicCode(int,char *);
	int  GPrint_ar_y(int);
// ***********************************
// *********  William  ***************
// *********   end    ***************
// ***********************************
};

#endif