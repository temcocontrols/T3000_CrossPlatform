//////////////////////////////////////////////////////////////
//                                                          //
// Implements the classes GEdit                             //
//                                                          //
//////////////////////////////////////////////////////////////

#ifndef _GEDIT_H
#define _GEDIT_H

#include "gwin.h"
#include <dir.h>
#include <SYS\STAT.H>
#include <bios.h>


#define BUF_SIZE 4596
#define MES_SIZE 1024
#define MAX_KILL_BUF_SIZE 2048
#define MAX_LINE_SIZE 300

///////////////////////////
//                       //
//    Class GEdit        //
//                       //
///////////////////////////

class GEdit:public GWindow
{
public:
Str_program_point *ptrprg;
int current_point_prg;
byte panel;
int network;
int length_code;
//char huge *code;
char *code;
char *eendloc;
char editbuf[BUF_SIZE];
char mesbuf[MES_SIZE];
char deleteline[MAX_LINE_SIZE];
char *beginscreen;
char comment[100];
unsigned int pool_size;
unsigned int total_programs_size;

protected:

char *buf;
char *curloc, *endloc;
char *beginblock, *endblock;
char *beginline, *endline;
char *ecurloc;
char *mcurloc, *mendloc;
//char deletebuf[MAX_KILL_BUF_SIZE];
//char deleteline[MAX_LINE_SIZE];
int scrnx, scrny;
int escrnx, escrny;
int LINE_LEN;
int MAX_LINES,HIGH_MES;
int KILL_BUF_SIZE;
hot_box ed,mes,hsave,hload,hcompile,hclear,hprint;
hot_box ctrll,ctrlu,ctrld,ctrly,ctrlo,ctrlc,ctrlf,ctrln,ctrlr;
int mty,mby;
int message,editt;

 union k {
	 char ch[2];
	 unsigned i;
 } key;
 MouseStatus stat;
 char tab;

 char name[80];

char *helpline;

public:

//	GEdit( uint, uint, uint, uint, uint, char huge *, int);  // constructor (the same as GView)
	GEdit(int tx, int ty, int bx, int by, int stk, char *pcode, int length,
			Str_program_point *pprg, int current_prg, int panel, int network);
	virtual void GWGoto(int row, int col);
	virtual int HandleEvent();      // handles the mouse events
	void GEditSet(char far *, uint, uint); // sets the window title, the colour
	void showedit(char *curloc);
	save(char *fname);
	load(void);
	void help(void);
	void clrscr(int y);
	void printline(char *p);
	void pageup(void);
	void pagedown(void);
	void edit_clr_eol(int x, int y);
	void clrline(int y);
	void egotoxy(int x, int y);
	int edit(char *fname);
	void left(void);
	void right(void);
	void upline(void);
	void downline(void);
	void delete_char(void);
	void delete_line(void);
	void delete_block(void);
	void select_line(void);
	void unselect_line(void);
	void undo(void);
	void insertchar(char);
	void lookbegin(char *begin, char *end,char *buf);
	void escrollup(int topx, int topy, int endx, int endy);
	void scrolldn(int x,int y);
	void replace(void);
	void edit_gets(char *str);
	void search(void);
	int  next(void);
	void gotoline(void);
	void insertbuf(void);
	void display_scrn(int x, int y, char *p, char type=0);
	void home(void);
	void gotoend(void);
	void cursor_pos(void);
	void display_scrn_file(char *p);
	void checkline(void);
	void checkblock(char *p, int i);
	int  compile(void);
	int  clearprg(void);
	char *desassembler_program(void);
	int desvar(void);
	int desexpr(void);
	void goedit(void);
	void gomessage(void);
   void infoheapprg(int x, int y);
	void *operator new(size_t size);
	void operator delete(void *p);
};

#endif
