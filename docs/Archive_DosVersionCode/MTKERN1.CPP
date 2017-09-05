#pragma inline
#include <windows.h>
#include <dos.h>
#include "t3000def.h"
#include "mtkernel.h"
#include "aio.h"
#include "baseclas.h"
//#include "vga12.h"
//#include "netbios.h"
#include "rs485.h"
#include "ptp.h"

void kill_task( int id );
void mono_task( void );
void resume_tasking( void );
void semblock( int id, unsigned *sem );
int  restart( unsigned *sem );
void check_sleepers( void );
void stop_tasking( void );
void msleep( int ticks );
void msleep( int id, int ticks );
void suspend( int id );
void resume( int id );
void resume_suspend( int, int );
void task_status( void );
//void free_all( void );
int all_dead( void );
int check_sleepers_all_dead(void);

extern void set_vid_mem( void );

extern void interrupt ( *oldhandler)(__CPPARGS);

void HookHandlers(void);
void UnhookHandlers(void);

/*
#ifdef NETWORK_COMM
extern unsigned int number_of_remote_points;
extern unsigned long program_interval;
extern int task_control(void);

char huge stack_NETWORK[stack_NETWORK_SIZE];
#endif
*/

#ifdef SERIAL_COMM
extern int int_occured;
#endif

extern int 	T_Inactivity;
extern int timepoints, timepoints_ipx;
extern long timesave;
//extern char virtual_not_run;
extern char	check_annual_routine_flag;
extern char	readclock_flag;

//extern PENDING_STATUS pr_call_state;

extern Panel *ptr_panel;
extern char disconnect_modem, action;
extern int ring_reset_time;
extern char ring_counts;
extern char control;
extern int refresh_time;
extern unsigned long grp_time;
extern unsigned long display_grp_time;
extern int alarm_time;
extern int worktime;
extern long refresh_graph_time;
extern char present_analog_monitor;
extern char *ontext;

extern char timeout, timeout_asyn;
extern int disconnect_time;

/* Timer interrupt task sheduller */
//extern unsigned char *ptr_dos_flag;

//extern int_regs *r;

extern int time_key;
extern char simulate;
extern int time_last_key;
//extern unsigned long timesec1970;  // sec la inceputul programului
extern unsigned long timestart;    // sec de la inceputul programului

extern char month_days[12];
extern unsigned long  ora_current_sec; // ora curenta exprimata in secunde
//struct  time  ora_current;      // ora curenta
extern Time_block ora_current;
extern int milisec;
extern long microsec;
//char dayofweek;
extern char onesec,onemin,tenmin,tensec;
extern int onesec_virtual;
//extern int pixvar;
extern int miliseclast;
//extern byte console_mode;

extern int indarray;
extern int int_dos;

extern unsigned real_ss;

extern task_struct tasks[NUM_TASKS];
extern unsigned  read_mon_flag; // i/o semaphore
extern unsigned  dos_flag; // i/o semaphore
extern unsigned  dos_host;
extern unsigned  screen; // i/o semaphore
//extern unsigned  memory; // i/o semaphore
extern unsigned  t3000_flag; // i/o semaphore

extern unsigned oldss, oldsp;
extern int tswitch;      		// task index

extern int setvectint8;
//extern int communication;
extern char timecount;
extern char run_board_flag;
extern int def_macro;

static char tasking = 1;           // tasking system enabled
static char single_task = 0;       // single task flag off
static unsigned pri,i,j;

#ifdef TEST
 char *num, *a = "0";
#endif

//#define byte	byte
//#define word  word

void interrupt int8_task_switch( __CPPARGS )
{
	if(++timecount >= 8)
	{
		oldhandler();
		disable();
		register int i;
		timecount = 0;
		tasking = 0;
		for( i=MSTP_MASTER; i<MSTP_MASTER+RS485TASKS; i++ )
		{
		 if( tasks[i].status != DEAD )
		 {
			tasks[i].ps->InactivityTimer++;
			if( ++tasks[i].ps->SilenceTimer == (Tno_token-1) )
			{
				 tasks[i].status = READY;
				 tasking = 1;
			}
		 }
		}
	}
	else
	{
		disable();
		asm mov al, 20h
		asm out 20h, al
		asm jmp $+2
		asm nop
		register int i;

		for( i=NETWORK1; i<MSTP_MASTER+RS485TASKS; i++ )
		{
		 if( tasks[i].status != DEAD )
		 {
			if( tasks[i].ps )
			{
			 if( ++tasks[i].ps->SilenceTimer == (Tno_token-1) )
				 tasks[i].status = READY;
			 tasks[i].ps->InactivityTimer++;
			}
			if( tasks[i].status == SLEEPING )
			{
			 tasks[i].sleep--;
			 if( !tasks[i].sleep ) tasks[i].status = READY;
			}
		 }
		}
//		if (run_board_flag || int_occured || int_dos)
		if (run_board_flag || int_occured )
		{
		 enable();return;
		}

		tasks[tswitch].sp = _SP;	// save current task's stack
		tasks[tswitch].ss = _SS;
		if(tasks[tswitch].status == RUNNING )
		 tasks[tswitch].status = READY;
		for( i=NETWORK1; i<MSTP_MASTER+RS485TASKS; i++ )
		{
		 if( tasks[i].status == READY ) tswitch = i;
		}
		_SP = tasks[tswitch].sp;
		_SS = tasks[tswitch].ss;
		tasks[tswitch].status = RUNNING; // state is running
		enable();
		return;
	}

	if (setvectint8)
	{
	 enable();
	 return;
	};
//	oldhandler();

//	disable();

	if(!timecount)
	{
	 timeout++;
	 timeout_asyn++;
	 microsec +=  54925;
	 miliseclast += 55;
	 if( microsec >= 1000000)
	 {
		microsec -= 1000000;
		onesec++;
		onesec_virtual++;

		if(tensec++ == 10) tensec = 0;
		timestart++;
		ora_current_sec++;
		++ora_current.ti_sec;
		if( ora_current.ti_sec == 60 )
		{
		 onemin++;
		 if(tenmin++ == 10) tenmin = 0;
		 ora_current.ti_sec = 0;
		 ++ora_current.ti_min;
		 if(ora_current.ti_min == 60)
		 {
			ora_current.ti_min = 0;
			++ora_current.ti_hour;
			if( ora_current.ti_hour == 24 )
			{
			 ora_current.ti_hour=0;
			 ora_current_sec = 0;
			 if(++ora_current.dayofweek==7)
				 ora_current.dayofweek=0;
			 if( ++ora_current.dayofmonth==month_days[ora_current.month]+1 )
			 {
				 ora_current.dayofmonth=1;
				 if( ++ora_current.month == 12 )
						ora_current.month = 0;
			 }
			 if(++ora_current.dayofyear==366)
			 {
					ora_current.dayofyear=0;
					++ora_current.year;
					month_days[1]=28;
			 }
			 else
				if(ora_current.dayofyear==365)
				{
				 if( ora_current.year&0x03 )
				 {
					ora_current.dayofyear=0;
					++ora_current.year;
					month_days[1]=28;
				 }
				 else
					month_days[1]=29;
				}
			 check_annual_routine_flag=1;
//			 readclock_flag=1;
			}
		 }
	 }

	}

	if (int_occured)
	{
	 enable();
	 return;
	}

	register int i;

	if(timesave) timesave--;
	if(timepoints) timepoints--;
	if(timepoints_ipx) timepoints_ipx--;
	if(refresh_time) refresh_time--;
	if(grp_time) grp_time--;
	if(display_grp_time) display_grp_time--;
	if(alarm_time) alarm_time--;
	if(refresh_graph_time) refresh_graph_time--;
	if(disconnect_time>0) disconnect_time--;
	if(worktime>0) worktime--;

	for( i=0; i< NUM_TASKS; i++ )
	{
		if( tasks[i].delay_time >= 0 ) tasks[i].delay_time -= 55;
		if( i>=PTP_CONNECTION && i<PTP_CONNECTION+RS232TASKS )
		{
		 if( tasks[i].status != DEAD )
		 {
			if( tasks[i].ps->time_modem >= 0 ) tasks[i].ps->time_modem -= 55;
			if( tasks[i].ps->connection == PTP_CONNECTED )
			{
			tasks[i].ps->SilenceTimer++;
			if( ++tasks[i].ps->InactivityTimer < T_Inactivity )    //T_INACTIVITY
			{
			 if( ++tasks[i].ps->HeartbeatTimer >= T_HEARTBEAT )
			 {
//				if (!run_board_flag && !int_dos )
				if (!run_board_flag )
				{
				 if(tasks[i+PTP_transmission].status != BLOCKED &&  tasks[i+PTP_transmission].status != RUNNING )
				 {
					tasks[i+PTP_transmission].status = READY;
					tasking = 1;
				 }
				}
			 }
			}
			else
			{
//				if (!run_board_flag && !int_dos )
			 if (!run_board_flag)
			 {
				if( tasks[i].status != RUNNING )
				{
				 tasks[i].status = READY;
				 tasking = 1;
				}
			 }
			}
			}
		 }
		}
		if( tasks[i].status == SLEEPING )
		{
			tasks[i].sleep--;
			if( !tasks[i].sleep )
			{
			 tasks[i].status = READY;
			 tasking = 1;
			}
		}
	}
	if(present_analog_monitor && onesec)
	{
	 for(i=0;i<MAX_ANALM;i++)
		if(ptr_panel->analog_mon[i].num_inputs)
		{
			if(ptr_panel->monitor_work_data[i].next_sample_time)
				ptr_panel->monitor_work_data[i].next_sample_time--;
		}
		onesec = 0;
	}


	if(time_key) time_key--;
	if(def_macro)
	{
		 time_last_key++;
	}

 }  // end if(!timecount)

//	if (run_board_flag || int_dos )
	if (run_board_flag)
	{
	 enable();
	 return;
	}

//	(*old_int8)(); // call to original int8 routine

	if( single_task ) // if single task is on, then return
	{                 //without a task switch
	 enable();
	 return;
	}

	tasks[tswitch].ss = _SS;	// save current task's stack
	tasks[tswitch].sp = _SP;
	// if current task was running, then change its state to READY
	if(tasks[tswitch].status == RUNNING )
	{
		tasks[tswitch].status = READY;
	  tasking = 1;
	}
	if(!timecount)
	{
	 if( disconnect_time==605)
	 {
		disconnect_modem=1;
		action=1;
		tasks[MISCELLANEOUS].status = READY;
		tasking = 1;
	 }
// ->
// see if any sleepers need to wakwe up
//	check_sleepers();
// see if all tasks are dead; if so, stop tasking
//	i=all_dead();
// <-

/*	 i = check_sleepers_all_dead();
	 if( i )
		tasking = 0;
*/
	 if( !tasking) { // stop tasking
			disable();
			_SS = oldss;
			_SP = oldsp;
//			setvect( 8, old_int8 );
			UnhookHandlers();
//			free_all();
			enable();
			return;
	 }
	// find new task
	}
	tswitch++;
	if( tswitch == NUM_TASKS ) tswitch = 0;
	while( tasks[tswitch].status != READY )
	{
		 tswitch++;
		 if( tswitch == NUM_TASKS ) tswitch = 0;
	}

	pri = tasks[tswitch].pri;
	i=tswitch;
	j=tswitch+1;
	if (j ==  NUM_TASKS ) j = 0;
	while( j != i )
	{
	 if( tasks[j].status == READY && tasks[j].pri > pri  )
	 {
		tswitch = j;
		pri = tasks[tswitch].pri;
	 }
	 j++;
	 if( j == NUM_TASKS ) j = 0;
	}

	// switch task to a new task

	_SP = tasks[tswitch].sp;
	_SS = tasks[tswitch].ss;
	tasks[tswitch].status = RUNNING; // state is running
	enable();
};


/* This is the manual task switcher which a program can call to force a task
switch. It does not decrement any sleeper's sleep counter because a clock tick
has not occured */
void interrupt task_switch( void )
//void task_switch( void )
{
  disable();

//	asm mov ax, DGROUP
//	asm mov ds,ax

	tasks[tswitch].ss = _SS;
	tasks[tswitch].sp = _SP;
	if( tasks[tswitch].status == RUNNING )
		tasks[tswitch].status = READY;

/*
//->
asm {
	 //
	 //
	 //		tasks[tswitch].ss = _SS;
	 //
	mov	bx,word ptr DGROUP:_tswitch
	imul	bx,bx,24
	mov	word ptr DGROUP:_tasks[bx+4],ss
	 //;
	 //;		tasks[tswitch].sp = _SP;
	 //;
	mov	word ptr DGROUP:_tasks[bx+2],sp
	 //;
	 //;		if( tasks[tswitch].status == RUNNING )
	 //;
	cmp	word ptr DGROUP:_tasks[bx],0
	jne	short @2@86
	 //;
	 //;			tasks[tswitch].status = READY;
	 //;
	mov	word ptr DGROUP:_tasks[bx],1
@2@86:
}
//<-
*/

	tasking=all_dead();
/*
	if (i)
		 tasking = 0;
*/
	if( !tasking )
	{
			disable();
			_SS = oldss;
			_SP = oldsp;
//			setvect( 8, old_int8 );
			UnhookHandlers();
//			free_all();
			enable();
			return;
	}
	// find new tasks
	tswitch++;
	if( tswitch==NUM_TASKS ) tswitch = 0;

	while( tasks[tswitch].status!=READY)
	{
		 tswitch++;
		 if( tswitch==NUM_TASKS ) tswitch = 0;
	}
	pri = tasks[tswitch].pri;

/*
//->
asm {
	 //		// find new tasks
	 //;		tswitch++;
	 //;
	inc	word ptr DGROUP:_tswitch
	 //;
	 //;		if( tswitch==NUM_TASKS ) tswitch = 0;
	 //;
	cmp	word ptr DGROUP:_tswitch,22
	jne	short @2@310
	jmp	short @2@282
@2@254:
	 //;
	 //;		while( tasks[tswitch].status!=READY)
	 //;		{
	 //;			 tswitch++;
	 //;
	inc	word ptr DGROUP:_tswitch
	 //;
	 //;			 if( tswitch==NUM_TASKS ) tswitch = 0;
	 //;
	cmp	word ptr DGROUP:_tswitch,22
	jne	short @2@310
@2@282:
	mov	word ptr DGROUP:_tswitch,0
@2@310:
	mov	bx,word ptr DGROUP:_tswitch
	imul	bx,bx,24
	cmp	word ptr DGROUP:_tasks[bx],1
	jne	short @2@254
	 //;
	 //;		}
	 //;
	 //;		pri = tasks[tswitch].pri;
	 //;
	mov	ax,word ptr DGROUP:_tasks[bx+12]
	mov	word ptr DGROUP:pri,ax
}
//<-
*/

	i=tswitch;
	j=tswitch+1;
	if (j ==  NUM_TASKS ) j = 0;
	while( j != i )
	{
	 if( tasks[j].status == READY && tasks[j].pri > pri  )
	 {
		tswitch = j;
		pri = tasks[tswitch].pri;
	 }
	 j++;
	 if( j == NUM_TASKS ) j = 0;
	}

	_SS = tasks[tswitch].ss;
	_SP = tasks[tswitch].sp;
	tasks[tswitch].status = RUNNING;

/*
//->
asm{
	 ;
	 ;		i=tswitch;
	 ;
	mov	ax,word ptr DGROUP:_tswitch
	mov	word ptr DGROUP:i,ax
	 ;
	 ;		j=tswitch+1;
	 ;
	inc	ax
	mov	word ptr DGROUP:j,ax
	 ;
	 ;		if (j ==  NUM_TASKS ) j = 0;
	 ;
	cmp	ax,22
	jne	short @2@534
	jmp	short @2@506
@2@394:
	 //;
	 //;		while( j != i )
	 //;		{
	 //;		 if( tasks[j].status == READY && tasks[j].pri > pri  )
	 //;
	mov	bx,word ptr DGROUP:j
	imul	bx,bx,24
	cmp	word ptr DGROUP:_tasks[bx],1
	jne	short @2@478
	mov	ax,word ptr DGROUP:_tasks[bx+12]
	cmp	ax,word ptr DGROUP:pri
	jbe	short @2@478
	 //;
	 //;		 {
	 //;			tswitch = j;
	 //;
	mov	ax,word ptr DGROUP:j
	mov	word ptr DGROUP:_tswitch,ax
	 //;
	 //;			pri = tasks[tswitch].pri;
	 //;
	mov	bx,ax
	imul	bx,bx,24
	mov	ax,word ptr DGROUP:_tasks[bx+12]
	mov	word ptr DGROUP:pri,ax
@2@478:
	 //;
	 //;		 }
	 //;		 j++;
	 //;
	inc	word ptr DGROUP:j
	 //;
	 //;		 if( j == NUM_TASKS ) j = 0;
	 //;
	cmp	word ptr DGROUP:j,22
	jne	short @2@534
@2@506:
	mov	word ptr DGROUP:j,0
@2@534:
	mov	ax,word ptr DGROUP:j
	cmp	ax,word ptr DGROUP:i
	jne	short @2@394
	 //;
	 //;		}
	 //;
	 //;		_SS = tasks[tswitch].ss;
	 //;
	mov	bx,word ptr DGROUP:_tswitch
	imul	bx,bx,24
	 //;
	 //;		_SP = tasks[tswitch].sp;
	 //;
	mov	ss,word ptr DGROUP:_tasks[bx+4]
	mov	sp,word ptr DGROUP:_tasks[bx+2]
	 //;
	 //;		tasks[tswitch].status = RUNNING;
	 //;
	mov	word ptr DGROUP:_tasks[bx],0
}
//<-
*/
	enable();
}
//#define byte	unsigned char
//#define word  unsigned int

// Return 1 if no task are ready to run; 0 if at least one task is READY.


int all_dead( void )
{
//	register int i;
	for( j=0; j<NUM_TASKS; j++ )
		if( tasks[j].status == READY || tasks[j].status == RUNNING ) return 1;
	return 0;
}

// Decrement the sleep count of any sleeping tasks.

/*
//extern int vrx;
void check_sleepers( void )
{
//	register int i;
	for( j=0; j<NUM_TASKS; j++ )
		{
		 if( tasks[j].status == SLEEPING )
			{
			 if( tasks[j].count )
			 {
				if( tasks[j].count() <= 0 )
				 {
					tasks[j].status = READY;
					tasks[j].sleep = 0;
//					vrx = 0;
				 }
				else
				{
				 tasks[j].sleep--;
				 if( !tasks[j].sleep ) tasks[j].status = READY;
				}
			 }
			 else
			 {
				tasks[j].sleep--;
				if( !tasks[j].sleep ) tasks[j].status = READY;
			 }
			}
		}
}
*/

int check_sleepers_all_dead(void)
{
	register int j, k;
	k = 1;
	for( j=0; j<NUM_TASKS; j++ )
	{
		 if( tasks[j].status == SLEEPING )
		 {
			tasks[j].sleep--;
			if( !tasks[j].sleep ) tasks[j].status = READY;
		 }
		 else
		 {
			if( k )
			if( tasks[j].status == READY || tasks[j].status == RUNNING ) k = 0;
		 }
	}
	return k;
}

/* Free all stack space. This function should not be called by the user's
 program */

/*
void free_all( void )
{
//	register int i;
	for( j=0; j<NUM_TASKS; j++ )
		{
		 if( tasks[j].stck)
			{
//			 free( tasks[j].stck );
			 tasks[j].stck = NULL;
			}
		}
}
*/


// Start up the multitasking kernel.
void interrupt multitask( void )
//void multitask( void )
{
	disable();
// Switch in the timer based schedular
//	old_int8 = getvect( 8 );
//	setvect( 8, int8_task_switch );
	HookHandlers();

/* Save the program's stack pointer and segment so that when
  tasking ends, execution can continue where it left off in the
	program. */
	oldss = _SS;
	oldsp = _SP;
// set stack to first task's stack
	_SP = tasks[tswitch].sp;
	_SS = tasks[tswitch].ss;
	enable();
}

// Kill a task. ( i.e., make it's state DEAD. )
void kill_task( int id )
{
	disable();
	tasks[id].status = DEAD;
	enable();
	task_switch();
}

// Initialize the task control structures
void init_tasks( void )
{

	for( i=0; i<NUM_TASKS; i++ )
	{
//	 tasks[i].status = SUSPENDED;
	 tasks[i].status = DEAD;
	 tasks[i].pending = NULL;
	 tasks[i].sleep = 0;
	 tasks[i].pri = i;
	}
	 tasks[PROJ].status = DEAD;

	 set_vid_mem();
}

// Stop tasking
void stop_tasking( void )
{
	 tasking = 0;
	 task_switch();
	 enable();
}

// Execute only one task
void mono_task( void )
{
	 disable();
	single_task = 1;
	 enable();
}

/* Resume multitasking all tasks. ( Use to restart tasking after a call
	 to mono_task(). */
void resume_tasking( void )
{
	 single_task = 0;
}

// Stop execution of a task for a specified number of clock cycles.
void msleep( int ticks )
{
	disable();
	tasks[tswitch].sleep = ticks;
	if(ticks)
	 tasks[tswitch].status = SLEEPING;
	else
	 tasks[tswitch].status = READY;
//   enable();
	 task_switch();
	 enable();
}

void msleep( int id, int ticks )
{
	if(tasks[id].status==SUSPENDED || tasks[id].status==SLEEPING)
	{
	 disable();
	 tasks[id].sleep = ticks;
	 tasks[id].status = SLEEPING;
	 enable();
	}
}

// Suspend a task until resumed by another task
void suspend( int id )
{
	 if( id < 0 || id > NUM_TASKS ) return;
//	 disable();      //**************************
//		asm {
//			mov ax, 0900h
//			int 31h
//		}
	 disable();
	 tasks[id].status = SUSPENDED;
	 if(id==tswitch)
		 task_switch();
	 enable();       //*****************************
}

// Restart a previously suspended task.
void resume( int id )
{
//disable();              //***********************
//asm {
//	mov ax, 0900h
//	int 31h
// }
	 if( (id < 0 || id > NUM_TASKS) || (tasks[id].status == DEAD)
				|| (tasks[id].status == BLOCKED) )
	 {
//		asm {
//			mov ax, 0901h
//			int 31h
//		}
//		enable();           //*************************
		return;
	 }
//	 tasks[id].sleep = 0;
	 tasks[id].status = READY;
//asm {
//	mov ax, 0901h
//	int 31h
// }
// enable();               //******************************
}

void resume_suspend( int id_res, int id_susp )
{
	resume( id_res );
	suspend( id_susp );
}

void blocked( int id )
{
	 if( id < 0 || id > NUM_TASKS ) return;
	 tasks[id].sleep = 0;
	 tasks[id].status = BLOCKED;
}

void blocked_suspended( int id )
{
	 if( id < 0 || id > NUM_TASKS ) return;
	 tasks[id].status = SUSPENDED;
}

void blocked_resume( int id )
{
	 if( id < 0 || id > NUM_TASKS ) return;
	 tasks[id].status = READY;
}

// Wait for a semaphore
void set_semaphore( unsigned *sem )
{
	disable();
	while( *sem )
	{
//			semblock( tswitch, sem );
			tasks[tswitch].status  = BLOCKED;
			tasks[tswitch].pending = sem;
			task_switch();
			disable(); // task switch will enable interrupts, so they need
								 //			 to be turned off again
	}
	*sem = 1;
	enable();
}

void set_semaphore_dos(void)
{
	 disable();
/*
	asm {
				push es
				mov ah,34h
				int 21h
				mov ax,es:[bx]
			 }
				ptr_dos_flag=(char *)MK_FP(_ES,_BX);
	asm		pop es
*/
//	 while(*ptr_dos_flag)
	 while(dos_flag && dos_host != tswitch)
	 {
//			semblock( tswitch, &io_out );
			tasks[tswitch].status  = BLOCKED;
			tasks[tswitch].pending = &dos_flag;
			task_switch();
			disable(); // task switch will enable interrupts, so they need
								 //   to be turned off again
	 }
	 dos_flag = 1;
	 dos_host = tswitch;
	 enable();
}

// Release a semaphore
void clear_semaphore_dos(void)
{
	disable();
	tasks[tswitch].pending = NULL;
	dos_flag = 0;
	if( restart( &dos_flag ) )
		task_switch();
	enable();
}

// Release a semaphore
void clear_semaphore( unsigned *sem )
{
	disable();
	tasks[tswitch].pending = NULL;
	*sem = 0;
	if( restart( sem ) )
		task_switch();
	enable();
}

/* Set task to BLOCKED. This is an internal function not to be called
	 by user's program. */
void semblock( int id, unsigned *sem )
{
		 tasks[id].status = BLOCKED;
		 tasks[id].pending = sem;
}

/* Restart a task that is waiting for the specified semaphore. This is
	 an internal function not to be called by user's program */
int restart( unsigned *sem )
{
	register int j;
	task_struct *ts;
	ts = &tasks[NUM_TASKS-1];
	for( j=NUM_TASKS-1; j>=0; j--, ts-- )
	  if( ts->pending == sem )
	  {
		 ts->pending = NULL;
		 if( ts->status == BLOCKED )
		 {
			if(!ts->sleep)
				ts->status = READY;
			else
				ts->status = SLEEPING;
		 }
		 return 1;
	  }
	return 0;
}

/* Display the state of all tasks. This function must NOT be called while
	 multitasking is in effect. */
void task_status( void )
{
/*
	 register int i;
	 if( tasking ) return; // cannot be used while multitasking
	 printf( "\n" );
	 for( i=0; i<NUM_TASKS; i++ )
	{
	 printf( "Task %d: ", i);
	 switch( tasks[i].status )
		{
		 case READY: printf( "READY\n" ); break;
		 case RUNNING: printf( "RUNNING\n" ); break;
		 case BLOCKED: printf( "BLOCKED\n" ); break;
		 case SUSPENDED: printf( "SUSPENDED\n" ); break;
		 case SLEEPING: printf( "SLEEPING\n" ); break;
		 case DEAD: printf( "DEAD\n" ); break;
		}
	}
*/
}

void HookHandlers(void)
{
	oldhandler = getvect(8);
	setvectint8 = 1;
	setvect(8, (void interrupt (*)( ... ))int8_task_switch);
}

void UnhookHandlers(void)
{
	//  set new vectors
	setvect(8, (void interrupt (*)( ... ))oldhandler);
}


