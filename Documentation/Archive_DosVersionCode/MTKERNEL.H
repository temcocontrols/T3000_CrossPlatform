#ifndef _MTKERNEL_H

#define _MTKERNEL_H

#define COD386

#ifdef __cplusplus
	 #define __CPPARGS ...
#else
	 #define __CPPARGS
#endif

#define byte		unsigned char

#define PROGRAM_INTERVAL 10000L

#define RS232TASKS            4
#define PTP_reception         RS232TASKS
#define PTP_transmission      PTP_reception+RS232TASKS

#define RS485TASKS            1

typedef enum {
					PROJ             = 0,
					MISCELLANEOUS,
					DIAL,
					PTP_CONNECTION,
					PTP_RECEPTION    = PTP_CONNECTION+RS232TASKS,
					PTP_TRANSMISSION = PTP_RECEPTION+RS232TASKS,
					AMONITOR         = PTP_TRANSMISSION+RS232TASKS,
					ALARMTASK,
					NETTASK,
					VIRTUAL,
// NETWORK1 should be immediatly before MSTP_MASTER, because
// in int8_task_switch NETWORK1 has a TIMERESOLUTION time switch
					SERVERTSM,
					NETWORK1,
					MSTP_MASTER,
					LAST_TASK = MSTP_MASTER + RS485TASKS - 1
				 } task_id;

#define NUM_TASKS	LAST_TASK+1

typedef enum {RUNNING, READY, BLOCKED, SLEEPING, SUSPENDED, DEAD }task_state;

#define stack_VIRTUAL_SIZE 				  1024
#define stack_MONITOR_SIZE 				  2048
#define stack_NETWORK_SIZE 				  2048
//#define stack_SERIAL_SIZE  				1024
#define stack_PROJ_SIZE    				  3000
//#define stack_PROJ_SIZE    				3072
//#define stack_MODEM_SIZE   				1024
#define stack_DIAL_SIZE    				  1024
#define stack_MISCELLANEOUS_SIZE 	  1024
#define stack_ALARMTASK_SIZE    	  1024
#define stack_NETTASK_SIZE    		  1024
#define stack_MSTP_Master_node_SIZE 2048
//#define stack_rs485_receive_frame_SIZE  512
#define stack_ServerTSM_SIZE  			1024

#define stack_PTP_CONNECTION_SIZE   1024
#define stack_PTP_RECEPTION_SIZE    1536
#define stack_PTP_TRANSMISSION_SIZE  512
#define stack_PTP_SIZE (stack_PTP_CONNECTION_SIZE+stack_PTP_RECEPTION_SIZE+stack_PTP_TRANSMISSION_SIZE)


typedef struct {
	unsigned long edi, esi, ebp;
	unsigned long reserved1;
	unsigned long ebx, edx, ecx, eax;
	unsigned flags;
	unsigned es, ds;
	unsigned fs, gs;
	unsigned ip, cs;
	unsigned sp, ss;
	} real_mode_str;

/*
#ifdef COD286
typedef struct {
	unsigned bp;
	unsigned di;
	unsigned si;
	unsigned ds;
	unsigned es;
	unsigned dx;
	unsigned cx;
	unsigned bx;
	unsigned ax;
	unsigned ip;
	unsigned cs;
	unsigned flags;
	} int_regs;
#endif
*/


//#ifdef COD386
typedef struct {
//	unsigned long ebp;
//	unsigned long edi;
//	unsigned long esi;
//	unsigned long edx;
//	unsigned long ecx;
//	unsigned long ebx;
//	unsigned long eax;
	unsigned bp;
	unsigned long edi;
	unsigned long esi;
	unsigned ds;
	unsigned es;
	unsigned long edx;
	unsigned long ecx;
	unsigned long ebx;
	unsigned long eax;
	unsigned ip;
	unsigned cs;
	unsigned flags;
	} int_regs;

//#endif



typedef struct {
	task_state status;
	unsigned   sp;
	unsigned   ss;
	unsigned   *pending;
	int        sleep;
	unsigned   pri;
	long       delay_time;
	PORT_STATUS_variables *ps;
	} task_struct;

typedef int ( far *taskptr ) (void);


#ifdef MTKERNEL

void interrupt (*old_int8 )( __CPPARGS );

int make_task( taskptr task, char *stck, unsigned stck_size, unsigned id, void *ptr=NULL, int port=0 );
void interrupt multitask( void );
void init_tasks( void );
void kill_task( int id );
void interrupt int8_task_switch( __CPPARGS );
void interrupt task_switch( void );
void mono_task( void );
void set_semaphore_dos(void);
void clear_semaphore_dos(void);
void resume_tasking( void );
void semblock( int id, unsigned *sem );
void restart( unsigned *sem );
void check_sleepers( void );
void stop_tasking( void );
void msleep( int ticks );
void msleep( int id, int ticks );
void suspend( int id );
void resume( int id );
void resume_suspend( int, int );
void task_status( void );
void free_all( void );
int all_dead( void );

void mputnum( int num );
void mputs( char *s );
char mgetche( void );
void moutchar( int x, int y, char ch );
void moutchar( int x, int y, char ch, int bkgnd, int frgnd );
void mxyputs( int x, int y, char *str );
void mxyputs( int x, int y, char *str, int bkgnd, int frgnd );
void getxy(int *x, int *y);
void set_vid_mem( void );
int video_mode( void );
void mbar(int ltopx,int ltopy,int rbottomx, int rbottomy, int fond);
void restore_upper_memory_link(void);
void set_upper_memory_link(void);
void mputchar( char ch, int bkgnd, int frgnd );

#else

#include	<time.h>

extern int make_task( taskptr task, char *stck, unsigned stck_size, unsigned id, void *ptr=NULL, int port=0 );
extern int bioskey_new(int cmd);
extern	task_struct tasks[NUM_TASKS];
extern void mfarfree(HANDLE handle);
extern void mfarfree(void *far_point);
extern void mfarmalloc(char far **far_point, unsigned long nbytes, HANDLE& handle);
extern void mfarmalloc(char far **far_point, unsigned long nbytes);
extern void mcprintf( char *s, char *p );
extern void mputtext(int left, int top, int right, int bottom, void *source);
extern void mgettext(int left, int top, int right, int bottom, void *dest);
extern void mputimage(int ltopx, int ltopy, void *under1, int Copy_put);
extern void mgetimage(int ltopx, int ltopy, int rbottomx, int rbottomy, void *under1);
extern void mgetimage_10(int ltopx, int ltopy, int rbottomx, int rbottomy, char *p);
extern void mputimage_10(int ltopx, int ltopy, int rbottomx, int rbottomy, char *p);
extern unsigned mimagesize(int ltopx, int ltopy, int rbottomx, int rbottomy);
extern void mcputs( char *s );
extern void mputch( int c );
extern int mgets(char *str,int viz);
extern int mgets(char *str,int viz,int bkgnd, int frgnd);
extern int mmovetext(int left, int top, int right,	int bottom, int destleft, int desttop);
extern void mclrscr(void);
extern void mclrscr(char x1, char y1, char x2, char y2, char col);
extern char *mstrcpy(char *dest, const char *src);
extern void *mmemcpy(void *dest, const void *src, size_t n);
extern char mgetch( void );
extern void mtextbackground(int newcolor);
extern void mtextcolor(int newcolor);
extern void mgotoxy(int x, int y);
extern size_t mstrlen( const char *s);
extern void  mmovmem(void *src, void *dest, unsigned length);
extern void  *mmemset(void *s, int c, size_t n);
extern void mxyputs( int x, int y, char *str );
extern void moutchar( int x, int y, char ch, int bkgnd, int frgnd );
extern void mputchar( char ch, int bkgnd, int frgnd );
extern void mxyputs( int x, int y, char *str, int bkgnd, int frgnd );
extern void mputs( char *str);
extern void mputs( char *str, int bkgnd, int frgnd );
extern char *mstrcat(char *dest, const char *src);
extern char *mctime(const time_t *time);
extern time_t mtime(time_t *timer);
extern void movetoxy(int x, int y);
extern void getxy(int *x, int *y);
extern void prectangle(int ltopx,int ltopy,int rbottomx,int rbottomy,int color);
extern void pline(int x1,int y1,int x2,int y2,int color);
extern void mbar(int ltopx,int ltopy,int rbottomx, int rbottomy, int fond);
extern void hidecur(void);

extern void msleep( int ticks );
extern void msleep( int id, int ticks );
extern void suspend(int);
extern void resume(int);
extern void resume_suspend( int, int );
extern void blocked_suspended( int id );
extern void blocked_resume( int id );
extern void kill_task( int id );
extern void interrupt task_switch( void );
extern void set_semaphore(unsigned *);
extern void clear_semaphore(unsigned *);
extern void set_semaphore_dos(void);
extern void clear_semaphore_dos(void);
extern void restore_upper_memory_link(void);
extern void set_upper_memory_link(void);

extern unsigned  t3000_flag; // i/o semaphore
extern unsigned  screen; // i/o semaphore
//extern unsigned  serial_wait[2]; // i/o semaphore
extern int local_request(int);

#define DIVIMAGE 2

#endif

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

#endif	// _MTKERNEL_H
