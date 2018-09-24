#include <stdio.h>
#include <dos.h>
#include <mem.h>
#include <alloc.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <bios.h>
#include <graphics.h>
#include "aio.h"
#include "t3000def.h"
#include "mtkernel.h"
#include "gwin.h"
#include "vga12.h"
#include "rs232.h"
#include "serial.h"
#include "rs485.h"
#include "ptp.h"

char pixul;
struct input_buffer {
		unsigned time;
		union {
			int   i;
			char  key[2];
			} key;
		};

extern Str_grp_element	*group_element_temp;
extern int current_point_GRP;
extern uint update_length;
extern int panel_GRP;
extern int network_GRP;

extern long galarm_read_time;
extern Panel_info1 panel_info1;
extern int alarm_col;
extern int alarm_time;
extern char alarm_beep;
extern int local_panel;
extern char GAlarm, gAlarm, GAlarmold;
extern unsigned long timesec1970,timestart;
extern int  Station_NUM;
extern struct input_buffer input_buffer[10];//[MAX_INPUT_BUFFER];
extern int ind_input_buffer;

extern void chbkg(int lx, int ly, int width, int bkgnd, int frgnd, int unchangecol=127, int height = 0);
extern int net_call(int command, int arg,  char *data, uint *length , int dest,
				 int network, int others=0, int timeout=TIMEOUT_NETCALL,
				 char *returnargs=NULL, int *length_returnargs=NULL,
				 char *sendargs=NULL, int length_sendargs=0, char bytearg=0, int port=-1);
extern int generatealarm(char *mes, int prg, int panel, int type, char alarmatall,char indalarmpanel,char *alarmpanel,char printalarm);
extern void dalarmrestore(char *mes, int prg, int panel);
extern int print_alarm_word(void);
extern int alarm_savemessage(Alarm_point *ptr, int number_of_points, int f=0);
extern void updatet3000(int);
extern int read_descriptors(void);
extern void DisplayMessage(int lx, int ly, int rx, int ry, char *title, char *message, GWindow **Er1, int fcolor=Black, GWindow *Er2=NULL, long delay=0);
extern void set_PIC_mask(byte *PIC_mask);
extern void reset_PIC_mask(byte PIC_mask);
extern void save_config(int what);
extern void disconnect_serial(int d);
extern Panel *ptr_panel;
extern char main_screen;
extern int  station_num;
extern unsigned long timestart;
extern int disconnect_time;
extern int mode_text;
extern char simulate;
extern char ready_for_descriptors;
extern unsigned read_mon_flag;
extern char int_disk1;
extern unsigned  print_sem; // i/o semaphore
extern char loaddesstart;
extern Comm_Info *comm_info;
extern int Version;

extern char huge filetransfername[65];
extern char huge *disconnect_mes;
char saveloadfilename[13];
char dial_buffer[40];
char save_passwords, save_file, load_file, save_default, disconnect_modem, print_flag,save_alarm_flag;
char action, readmon_flag, savemon_flag, update_prg_flag, readfiles_flag;
char DIAL_action, DIAL_dial, DIAL_checkconnection, DIAL_updategrp;
char *ptr_filetransfer, filetransfer_flag, updatenet_flag;
uint filetransfer;
long length_filetransfer;
struct TSMTable *STSMtable_ptr, *STSMtable_ptr_readmon, *STSMtable_ptr_files;
int STSMtable_ptr_port, STSMtable_ptr_readmon_port, STSMtable_ptr_files_port;
signed char err_printer=-1;

char *updatebuffer;
char huge print_message_ptr[3072];
POOL print_message_pool(print_message_ptr, 3072);

char *printerrtext = "    ALARM! PRINTER ERROR!";

// type = 0 rename .prg as _rg
// type = 1 restore ._rg as .prg
void saveoldprg(char *fname,char type=0)
{
	char defaultname[65];
	if(type==2)
	{
	 strcpy(defaultname, ptr_panel->Program_Path);
	 if(strlen(defaultname)) strcat(defaultname,"\\");
	 strcat(defaultname, ptr_panel->Default_Program);
	}
	else
	 strcpy(defaultname, fname);
//	if( !strcmp(fname,defaultname) )
	if(strchr(defaultname,'.'))
	{
	 defaultname[strlen(defaultname)-1]='_';
	 set_semaphore_dos();
	 if(type)
	 {
		 remove(defaultname);
		 rename(fname, defaultname);
	 }
	 else
	 {
		 remove(fname);
		 rename(defaultname, fname);
	 }
	 clear_semaphore_dos();
	}
}

int dial_init(void)
{
	Serial *ser_m;
	int i, sleep_flag;
	while( 1 )
	{
	 sleep_flag=tasks[DIAL].sleep;
	 if(sleep_flag<0) sleep_flag=0;
	 while(DIAL_action)
	 {
		DIAL_action = 0;
		if (DIAL_dial)
		{
		 DIAL_dial = 0;
		 for(i=0; i<MAX_Routing_table; i++)
		 {
			if( (Routing_table[i].status&PTP_INSTALLED)==PTP_INSTALLED )
			 if(((class PTP *)Routing_table[i].ptr)->media == MODEM_LINK )
			 {
				break;
			 }
		 }
		 if(i<MAX_Routing_table)
		 {
			ser_m = (class PTP *)Routing_table[i].ptr;
			if( ser_m->modem_active )
			{
			 if(ser_m->activity != BUSY )
			 {
				ser_m->Set_mode( MASTER );
				Settings copy;
				ser_m->port->ReadSettings( copy );
				ser_m->port->Set( 300L );
				if( ( ser_m->modem_status = ser_m->modem_obj->Initialize() ) == MODEM_SUCCESS )
				{
//				 char *p = strchr(dial_buffer, '*');
//				 *p = 0;
//				 p++;
				 ser_m->modem_obj->Dial( dial_buffer, 1 );
//				 Delay(3000);
//			 int result = ser_m->port->Write( p, strlen(p), 100*strlen(p) );
//		   if( result == RS232_SUCCESS )
//				 {
//				 }
				 if( ( ser_m->modem_status = ser_m->modem_obj->Disconnect() ) != MODEM_SUCCESS )
				 {
				 }
				}
				ser_m->port->Set( copy.BaudRate );
			 }
			}
		 }
		 continue;
		} // end if DIAL_dial
	  if (DIAL_checkconnection)
	  {
		 if(!sleep_flag)
		 {
			for(i=0;i<MAX_COM;i++)
			 if(comm_info[i].activate)
			 {
				if ( net_call(50, ESTABLISH_CONNECTION_PORT, NULL, 0, i, 0xFFFF, NETCALL_NOTCTRLBREAK|NETCALL_NOTCHANGENETADR, 40) == SUCCESS )
				{
				}
			 }
			 sleep_flag=1200;  // 1 minute
		 }
		}  // end if DIAL_checkconnection
		if( DIAL_updategrp==1 )
		{
		 if(group_element_temp)
		 {
			update_length = 0;
			if( net_call(19, current_point_GRP, updatebuffer, &update_length, panel_GRP, network_GRP, NETCALL_CHECKDUPLICATE|NETCALL_NOTTIMEOUT,15)==SUCCESS )
			{
				if(group_element_temp&&(DIAL_updategrp==1))  // the buffer still exist?
				{
					memcpy(group_element_temp, updatebuffer, update_length);
					DIAL_updategrp=2;
        }
				else
				 DIAL_updategrp=0;
			}
			else
				DIAL_updategrp=3;
		 }
		 else
				DIAL_updategrp=0;
		 sleep_flag=1200;  // 1 minute
		}
	 }
	 if(sleep_flag)
	 {
		DIAL_action = 1;
		msleep(sleep_flag);
	 }
	 else
		suspend(DIAL);
	}
}

int miscellaneous_init( void )
{
 int n,sleep;
// Serial *sptr;
	ConnectionData *cdata;

 while(1)
 {
	 while(action)
	 {
		action = 0;
//		sleep  = 0;
		if (save_alarm_flag)
		{
		 alarm_savemessage( ptr_panel->alarms, MAX_ALARMS);
		 save_alarm_flag=0;
		 continue;
		}
		if(print_flag)
		{
		 char *ptr;
		 int j;
		 print_flag=0;
		 j=0;
		 if(sleep)
			 msleep(50);
		 sleep = 0;
		 while( (ptr = print_message_pool.next())!=NULL )
		 {
			if ( (n=biosprint(2, 0, 0))&0x10 )
			{
			while( !((n=biosprint(2, 0, 0))&0x80) )
			{
				if ( n&0x01 || n&0x20 || n&0x08 ) break;
			}
			if ( n&0x80 && n&0x10)
			{
			 while(*ptr)
			 {
				if( *ptr=='\\' )
				{
				 if( *(ptr+1)=='n' )
				 {
					*ptr=13;
					*(ptr+1)=10;
				 }
				 else
				 {
					if( *(ptr+1)=='f' )
					{
					 *ptr=' ';
					 *(ptr+1)=12;
					}
					else
					 ptr++;
				 }
				}
				biosprint(0, *ptr++, 0);
				while( !((n=biosprint(2, 0, 0))&0x80) )
				{
				 if ( n&0x01 || n&0x20 || n&0x08 ) break;
				}
				if ( !(n&0x80 && n&0x10) ) break;
			 }
			}
			}
			if ( n&0x80 && n&0x10)
			{
//			 if(err_printer>=0)
			 if(err_printer>0)
			 {
				dalarmrestore(printerrtext, 0, Station_NUM);
/*
				if( ptr_panel->alarms[err_printer].type == PRINTER_ALARM )
				{
				 ptr_panel->alarms[err_printer].restored = 1;
				 if(--ptr_panel->ind_alarms==0)
				 {
					GAlarm = 0;
					print_alarm_word();
				 }
				}
*/
			 }
			 err_printer=-1;
			 set_semaphore(&print_sem);
			 print_message_pool.release();
			 clear_semaphore(&print_sem);
			}
			else
			{
			 n=generatealarm(printerrtext, 0, Station_NUM, PRINTER_ALARM, 1, 0, NULL, 0);
			 if(n>0) err_printer = n;

/*
			 if(err_printer==-1)
			 {
				int k;
				for(k=0;k<MAX_ALARMS;k++)
				{
					if(!ptr_panel->alarms[k].alarm) break;
				}
				if(k>=MAX_ALARMS)
				{
				 for(k=0;k<MAX_ALARMS;k++)
				 {
					if(ptr_panel->alarms[k].restored) break;
				 }
				}
				if(k<MAX_ALARMS)
				{
					err_printer=k;
					ptr_panel->alarms[k].alarm = 1;
					ptr_panel->alarms[k].alarm_panel = Station_NUM;
					ptr_panel->alarms[k].alarm_time = timesec1970+timestart;
					ptr_panel->alarms[k].alarm_count = ALARM_MESSAGE_SIZE;
					ptr_panel->alarms[k].type = PRINTER_ALARM;
					strcpy(ptr_panel->alarms[k].alarm_message,"    ALARM! PRINTER ERROR!");
					ptr_panel->ind_alarms++;
					GAlarm = 1;
				}
			 }
*/
			}
			if(++j >= 25)
			{
				print_flag=1;
				action = 1;
				sleep = 1;
				break;
			}
		 }
//		 if ( n&0x80 && n&0x10 )
//			biosprint(0, '\f', 0);
		}
		if (save_passwords)
		{
		 save_passwords = 0;
		 save_config(CNF_PASS_INFO);
		 continue;
		}
		if (save_default)
		{
		 save_default = 0;
		 save_config(CNF_PATH_INFO);
		 continue;
		}
		if (save_file)
		{
		 save_file = 0;
		 saveoldprg(saveloadfilename,2);
		 ptr_panel->savefile(saveloadfilename, 1);
		 continue;
		}
		if (load_file)
		{
		 load_file = 0;
		 if(main_screen)
			 ptr_panel->loadprg(saveloadfilename);
		 continue;
		}
		if (updatenet_flag)
		{
		 updatet3000(updatenet_flag-1);
		 updatenet_flag=0;
		 continue;
		}
		if (filetransfer_flag==1)
		{
		 filetransfer_flag = 0;
		 FILE *h;
		 byte PIC_mask;
		 filetransfer = 0;
		 set_semaphore_dos();
		 int_disk1++;
		 if( (h=fopen(filetransfername,"wb+"))!=NULL )
		 {
		 int_disk1--;
			ptr_filetransfer=new char [MAX_FILE_TRANSFER_BUF];
			memset( ptr_filetransfer, 0, MAX_FILE_TRANSFER_BUF);
			clear_semaphore_dos();
			set_PIC_mask(&PIC_mask);
			unsigned long t;
			while(1)
			{
			 filetransfer = 1;
			 t=timestart;
			 while(filetransfer && timestart < t+105 );
			 if(filetransfer) break;
			 memcpy(&n, ptr_filetransfer, 2);
			 if(!n) break;
			 set_semaphore_dos();
			 int_disk1++;
			 fwrite(ptr_filetransfer+2, 1, n, h);
			 int_disk1--;
			 clear_semaphore_dos();
			}
			reset_PIC_mask(PIC_mask);
			set_semaphore_dos();
		 int_disk1++;
			fclose(h);
		 int_disk1--;
			delete ptr_filetransfer;
			ptr_filetransfer=NULL;
		 }
		 else
		 {
		  int_disk1--;
		 }
		 clear_semaphore_dos();
		 filetransfer=0;
		 continue;
		}
		if (filetransfer_flag==2)
		{
		 filetransfer_flag = 0;
		 FILE *h;
		 byte PIC_mask;
		 filetransfer = 0;
		 length_filetransfer = 0;
		 set_semaphore_dos();
		 int_disk1++;
		 if( (h=fopen(filetransfername,"rb+"))!=NULL )
		 {
			fseek(h, 0, SEEK_END);
			length_filetransfer = ftell(h);
			fseek(h, 0, SEEK_SET);
		 int_disk1--;
			ptr_filetransfer=new char [MAX_FILE_TRANSFER_BUF];
			memset( ptr_filetransfer, 0, MAX_FILE_TRANSFER_BUF);
			clear_semaphore_dos();
			unsigned long t,l=0;
			set_PIC_mask(&PIC_mask);
			while( l < length_filetransfer)
			{
			 set_semaphore_dos();
		 int_disk1++;
			 n=fread(ptr_filetransfer+2, 1, Version>=213?(MAX_FILE_TRANSFER_BUF-2):6000, h);
		 int_disk1--;
			 clear_semaphore_dos();
			 memcpy(ptr_filetransfer, &n, 2);
			 filetransfer = 1;
			 t=timestart;
			 while(filetransfer && timestart < t+105 );
			 if(filetransfer) break;
			 l += n;
			}
			reset_PIC_mask(PIC_mask);
			set_semaphore_dos();
			int_disk1++;
			fclose(h);
			int_disk1--;
			delete ptr_filetransfer;
			ptr_filetransfer=NULL;
		 }
		 else
		 {
			 int_disk1--;
		 }
		 clear_semaphore_dos();
		 filetransfer=0;
		 continue;
		}
		if (disconnect_modem)
		{
		 disconnect_modem = 0;
		 while( !bioskey_new(1) && disconnect_time > 0 && disconnect_time <= 605 )
		 {
			itoa(((unsigned)disconnect_time)*55/1000,&disconnect_mes[61],10);
			if(!disconnect_mes[63])
			  disconnect_mes[63]	=' ';
			else
			  disconnect_mes[62]	=' ';
			if(n==1300) n=2000;
			else n=1300;
			sound(n);
			DisplayMessage(mode_text?20:160, mode_text?7:150, mode_text?60:500, mode_text?12:220, NULL, disconnect_mes, NULL, White, NULL, 2000);
			nosound();
		 }
		 if(!disconnect_time)
		 {
			 disconnect_serial(1);
			 input_buffer[0].key.i=27;
			 input_buffer[1].key.i='$';
			 simulate=1;
			 ind_input_buffer=0;
		 }
		 else
			 bioskey_new(0);
		 continue;
		}
		if( ready_for_descriptors&0x01 )
		{
		 if(main_screen && loaddesstart)
		 {
			set_semaphore(&screen);
			clear_semaphore(&screen);
			read_descriptors();
			if(main_screen&0x02) main_screen=0;
		 }
		 else
		 {
			ready_for_descriptors |= 0x08;
		 }
		 if(ready_for_descriptors)
		 {
			ready_for_descriptors &= 0xfc;
			ready_for_descriptors |= 0x02;
		 }
		}
		if( readmon_flag )
		{
		  if(read_mon_flag)
		  {
			STSMtable_ptr_readmon->state=STSM_IDLE;
			STSMtable_ptr_readmon->timeout = 0;
			resume(SERVERTSM);
		  }
		  else
			{
/*
			if( (Routing_table[STSMtable_ptr_readmon_port].status&PTP_INSTALLED)==PTP_INSTALLED )
			 sptr = (class PTP *)Routing_table[STSMtable_ptr_readmon_port].ptr;
			else
			 sptr = (class MSTP *)Routing_table[STSMtable_ptr_readmon_port].ptr;
*/
			cdata = ( class ConnectionData *)Routing_table[STSMtable_ptr_readmon_port].ptr;
			execute_command( cdata->media, SEND, Routing_table[STSMtable_ptr_readmon_port].ptr, STSMtable_ptr_readmon->data, STSMtable_ptr_readmon);
			if(STSMtable_ptr_readmon->state >= 16)
			{
				STSMtable_ptr_readmon->state += 16;
				STSMtable_ptr_readmon->timeout = 0;
				resume(SERVERTSM);
			}
			}
			readmon_flag = 0;
		}
		if( savemon_flag )
		{
/*
			if( (Routing_table[STSMtable_ptr_port].status&PTP_INSTALLED)==PTP_INSTALLED )
			 sptr = (class PTP *)Routing_table[STSMtable_ptr_port].ptr;
			else
			 sptr = (class MSTP *)Routing_table[STSMtable_ptr_port].ptr;
*/
			cdata = ( class ConnectionData *)Routing_table[STSMtable_ptr_readmon_port].ptr;
			execute_command( cdata->media, SEND, Routing_table[STSMtable_ptr_port].ptr, STSMtable_ptr->data, STSMtable_ptr);
			if(STSMtable_ptr->state >= 0)
				STSMtable_ptr->timeout = 0;
			resume(SERVERTSM);
			savemon_flag = 0;
		}
		if( update_prg_flag )
		{
/*
			if( (Routing_table[STSMtable_ptr_port].status&PTP_INSTALLED)==PTP_INSTALLED )
			 sptr = (class PTP *)Routing_table[STSMtable_ptr_port].ptr;
			else
			 sptr = (class MSTP *)Routing_table[STSMtable_ptr_port].ptr;
*/
			cdata = ( class ConnectionData *)Routing_table[STSMtable_ptr_readmon_port].ptr;
			execute_command( cdata->media, SEND, Routing_table[STSMtable_ptr_port].ptr, STSMtable_ptr->data, STSMtable_ptr);
			if(STSMtable_ptr->state >= 0)
			  STSMtable_ptr->timeout = 0;
		  resume(SERVERTSM);
		  update_prg_flag = 0;
		}
		if( readfiles_flag )
		{
//		  rib[2] = STSMtable_ptr_files->command;
//		  memcpy(&rib[3], &STSMtable_ptr_files->arg, 2);
/*
			if( (Routing_table[STSMtable_ptr_files_port].status&PTP_INSTALLED)==PTP_INSTALLED )
			 sptr = ((class PTP *)Routing_table[STSMtable_ptr_files_port].ptr);
			else
			 sptr = (class MSTP *)Routing_table[STSMtable_ptr_files_port].ptr;
*/
			cdata = ( class ConnectionData *)Routing_table[STSMtable_ptr_readmon_port].ptr;
			execute_command( cdata->media, SEND, Routing_table[STSMtable_ptr_files_port].ptr, STSMtable_ptr_files->data, STSMtable_ptr_files);
			if(STSMtable_ptr_files->state >= 16)
			{
			  if( STSMtable_ptr_files->command == 50 && ( STSMtable_ptr_files->arg == 47 || STSMtable_ptr_files->arg == 48) )
				 ;
			  else
				  STSMtable_ptr_files->state += 16;
			  STSMtable_ptr_files->timeout = 0;
			  resume(SERVERTSM);
		  }
		  readfiles_flag = 0;
		}

	 }
	 suspend(MISCELLANEOUS);
 }
}


void *newalloc(long size)
{
 set_semaphore_dos();
 void *ptr = new char[size];
 clear_semaphore_dos();
 return ptr;
}

void newdelete(void *ptr)
{
 set_semaphore_dos();
 delete (void *)ptr;
 clear_semaphore_dos();
}

/*
static void *operator new[](size_t size, int sem)
{
// HANDLE handle;
 void *rtn;
 set_semaphore_dos();
 if( (rtn=farmalloc(size))!=NULL )
	memset(rtn,0,size);
 clear_semaphore_dos();
// mfarmalloc( (char far **)&rtn, (unsigned long)size, handle);
 return rtn;
}

static void operator delete[](void *ptr)
{
 set_semaphore_dos();
 farfree(ptr);
 clear_semaphore_dos();
}
*/
void POOL::init_pool(char *p, int l)
{
 Header_pool *h;
 length = l;
 first = last = access = 0;
 buf=p;
 h = (Header_pool *)buf;
 h->status = 0;
 h->length=l-sizeof(Header_pool);
 h->next=0;
 h->last=0xFFFF;
}

POOL::POOL(char *p, int l)
{
 init_pool(p, l);
}

POOL::POOL(void)
{
}

char *POOL::put(char *p, int l)
{
 int i,j;
 Header_pool *h;
 h = (Header_pool *)(buf+last);
 if(h->status) return 0;
 if( h->length < l+sizeof(Header_pool) ) return 0;
 j = h->length;
 h->length = l;
 h->status = 1;
 i = last + sizeof(Header_pool) + l;
 if( i >= length )
 {
  h->next = i-length;
  memcpy( ((char *)h)+sizeof(Header_pool), p, length-(last + sizeof(Header_pool)) );
  memcpy( buf, p+length-(last + sizeof(Header_pool)), i-length );
 }
 else
 {
  h->next = i;
  memcpy( ((char *)h)+sizeof(Header_pool), p, l );
  if( i+sizeof(Header_pool) >= length )
  {
	h->length += length - i;
	l = h->length;
	h->next = 0;
  }
 }
 i = last;
 last = h->next;
 h = (Header_pool *)(buf+last);
 h->status = 0;
 h->length = j - l - sizeof(Header_pool);
 h->next   = 0;
 h->last   = i;
}

char *POOL::next(void)
{
 if( ((Header_pool *)(buf+first))->status )
	return ( buf+first+sizeof(Header_pool) );
 else
	return 0;
}

void POOL::release(void)
{
 Header_pool *h;
 int i;
 h = (Header_pool *)(buf+last);
 if(h->status)
 {
  h->next = first;
  i = last;
  first = ((Header_pool *)(buf+first))->next;
  last = h->next;
  h = (Header_pool *)(buf+last);
  h->status=0;
  h->next = 0;
  h->last = i;
 }
 else
 {
  h->length += ((Header_pool *)(buf+first))->length + sizeof(Header_pool);
  first = ((Header_pool *)(buf+first))->next;
 }
}

unsigned POOL::alloc(int l)
{
 unsigned i,j,offset,next;
 Header_pool *h;
 if (access) return 0;
 h = (Header_pool *)buf;
 offset = 0;
 while(1)
 {
	if( h->status || (!h->status && h->length < l+sizeof(Header_pool)+1) )
	{
	  if(h->next)
	  {
		 offset = h->next;
		 h = (Header_pool *)(buf+(h->next));
	  }
	  else
	  {
		 offset = 0;
		 break;
	  }	 
	}
	else
	{
//	  p = (char *)h;
	  next = h->next;
	  j = h->length;
	  h->length = l;
	  h->status = 1;
	  i = offset + sizeof(Header_pool) + l;
	  h->next = i;
	  h = (Header_pool *)(buf+i);
	  h->status = 0;
	  h->length = j - l - sizeof(Header_pool);
	  h->next   = next;
	  h->last   = offset;
	  if(h->next)
	  {
		h = (Header_pool *)(buf+next);
		h->last   = i;
	  }
	  offset += sizeof(Header_pool);
	  break;
	}
 }
 return offset;
}

void POOL::free(int offset)
{
 Header_pool *h,*h1;
 if(offset==0xFFFF) return;
 access = 1;
 offset -= sizeof(Header_pool);
 h = (Header_pool *)(buf+offset);
 h->status = 0;
/*
 h = (Header_pool *)buf;
 while(h->next)
 {
  h = (Header_pool *)(buf+(h->next));
 }
 while(h->last!=0xFFFF)
 {
  if( !h->status )
  {
	h1 = (Header_pool *)(buf+(h->last));
	if( !(h1->status ) )
	{
	 h1->length += h->length + sizeof(Header_pool);
	 h1->next = h->next;
	 if(h->next)
	 {
	  h1 = (Header_pool *)(buf+(h->next));
	  h1->last = h->last;
	 }
	}
  }
  h = (Header_pool *)(buf+(h->last));
 }
*/

 if(h->next)
 {
  h1 = (Header_pool *)(buf+(h->next));
  if( !(h1->status ) )
  {
	h->length += h1->length + sizeof(Header_pool);
	h->next = h1->next;
	if(h->next)
	{
	 h1 = (Header_pool *)(buf+(h->next));
	 h1->last = offset;
	}
  }
 }
 if(h->last!=0xFFFF)
 {
  h1 = (Header_pool *)(buf+(h->last));
  if( !(h1->status ) )
  {
	h1->length += h->length + sizeof(Header_pool);
	h1->next = h->next;
	if(h->next)
	{
	 h1 = (Header_pool *)(buf+(h->next));
	 h1->last = h->last;
	}
  }
 }

 access = 0;
}

int print_alarm_word()
{
	if( (local_panel && GAlarm) || (!local_panel && gAlarm) )
	{
	 GAlarmold = 1;
	 if(!alarm_time)
	 {
/*
		++alarm_beep;
		if(alarm_beep > 40)
		{
			 alarm_beep=0;
			 sound(4000);
			 delay(80);
			 nosound();
		}
		if(alarm_beep == 20)
		{
			 sound(200);
			 delay(50);
			 nosound();
		}
*/
		if(mode_text)
		{
		 if(alarm_col==Red)
		 {
			mxyputs(76,1,"ALARM",Black, Red);   //Red+8
			alarm_col=Black;
		 }
		 else
		 {
			mxyputs(76,1,"ALARM", Lightred, Black);
			alarm_col=Red;
		 }
		}
		else
		{
		 if(alarm_col==Lightred)
		 {
	//  set_semaphore(&screen);
			chbkg((76-1)*8, 0, 40, Red, Red);
			chbkg((76-1)*8, 8, 40, Red, Red);
			setcolor(Lightred);
			outtextxy((76-1)*8,4,"ALARM");
			alarm_col=Red;
	//  clear_semaphore(&screen);
		 }
		 else
		 {
	// set_semaphore(&screen);
			chbkg((76-1)*8, 0, 40, White, White);
			chbkg((76-1)*8, 8, 40, White, White);
			setcolor(Red);
			outtextxy((76-1)*8,4,"ALARM");
			alarm_col=Lightred;
	// clear_semaphore(&screen);
		 }

//		 setcolor(Lightred);
//		 outtextxy((76-1)*8,0,"ALARM");
		}
		alarm_time = 18 * 2;
	 }
	}
	else
	{
		if(GAlarmold)
		{
		 GAlarmold = 0;
		 if(mode_text)
		 {
			mxyputs(76,1,"ALARM",Lightgray, Lightgray);
		 }
		 else
		 {
			hide_pointer();
			chbkg((76-1)*8, 0, 40, Lightgray, Lightgray);
			chbkg((76-1)*8, 8, 40, Lightgray, Lightgray);
			display_pointer();
		 }
	 }
	}
	if( !local_panel )
	{
	 if( (panel_info1.panel_type == T3000 && panel_info1.version >= 216) ||	(panel_info1.panel_type == MINI_T3000 && panel_info1.version >= 107) )
	 {
		if( galarm_read_time < timestart+timesec1970 )
		{
		 if( !DIAL_updategrp )
			net_call(COMMAND_50, ALARM_NOTIFY_COMMAND, &gAlarm, 0, station_num, networkaddress,BACnetConfirmedRequestPDU|NETCALL_NOTTIMEOUT|NETCALL_CHECKDUPLICATE);
		 galarm_read_time = timestart+timesec1970+90;
		}
	 }
	}
}


