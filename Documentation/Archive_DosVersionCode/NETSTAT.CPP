#include <windows.h>
#include "graphics.h"
#include "recstruc.h"
#include "fxengine.h"
#include "t3000def.h"
#include "parser.h"
#include <string.h>
#include "ggrid.h"
#include "gedit.h"
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include "t3000hlp.h"

extern Panel *ptr_panel;
extern char _far netoperation[MAX_STATIONS];
extern byte serial_access;
extern Station_point station_list[MAX_STATIONS];
extern int refresh_time;

extern int local_request(int panel, int network);
extern char *lalign(char *buf, int n);
extern int	automan(int l, char *buf);
extern void longtoa(long f, int length, int ndec, char *buf);

Str_netstat_point *netstatbuf;
Str_netstatus_point *netstatusbuf;

/*
int netstat_show(void)
{
		RS232Error error;
		int l1, st, net;
		GGrid *wgrid;
		hide_pointer();

		set_semaphore_dos();
		netstatbuf=new Str_netstat_point[MAX_NETSTATS];
		clear_semaphore_dos();
		memset(netstatbuf,'\0',MAX_NETSTATS*sizeof(Str_netstat_point));

		wgrid=new GGrid(4,4,76,22,GRID,NULL,NETSTAT,ptr_panel->GlPanel_type,ptr_panel->GlPanel,ptr_panel->GlNetwork);
		wgrid->GWSet("Netstat Panels",Lightgray,Darkgray);
		wgrid->GShowGrid();
		while (!wgrid->HandleEvent())
		{
		}
		delete wgrid;
		set_semaphore_dos();
		delete netstatbuf;
		netstatbuf = NULL;
		clear_semaphore_dos();
		return 0;
}
*/

/*
Netstat_block::Netstat_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				:Block(pthis, pt, p, net, type, pnum, N_NETSTAT, (char *)&line_buf)
{
			int npoint=0;
			if(type==INDIVIDUAL)
			 {
				number_of_points=1;
				npoint =  pnum-1;                // num_point
			 }
			else
			{
				number_of_points=MAX_NETSTATS;
			}
		 block=netstatbuf;
		 r.RecStruct(N_NETSTAT,netstat_struct);
		 h.HSet(N_NETSTAT,r.RecStruct(1),number_of_points);
}

Netstat_block::~Netstat_block()
{
}

int Netstat_block::Read(int field, char key)
{
 char buf[50],l;

 if(key==INSERT)
 {
 }
 else
 {
//
//	switch (field) {
//		case NETSTAT_NUM:
//					 break;
//		case NETSTAT_FULL_LABEL:
//					 getalpha(field, (block+current_point)->description, L_NETSTAT_FULL_LABEL);
//					 break;
//		case NETSTAT_AUTO_MAN:
//					 (block+current_point)->auto_manual=automan(!(block+current_point)->auto_manual, buf);
//					 PutAlpha(field, buf);
//					 refresh_time = 0;
//					 break;
//	}
//
 }
}

int Netstat_block::GetRec(void)
{
	int i;

	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,'\0',sizeof(struct NETSTAT_LineBuf));

	for(i=0; i<fields_number; i++)
	{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
	}
	return FX_SUCCESS;
}

int Netstat_block::GetField(int field, char *buf)
{
	int l,n;

	l=0;
	switch (field) {
		case NETSTAT_NUM:
				 nr_point(buf);
				 break;
		case NETSTAT_DESCRIPTION:
				 memcpy(buf , lalign((block+current_point)->description,L_NETSTAT_DESCRIPTION),L_NETSTAT_DESCRIPTION);
				 l=L_NETSTAT_DESCRIPTION;
				 break;
		case NETSTAT_ROOM_NUMBER:
				 memcpy(buf , lalign((block+current_point)->roomnumber,L_NETSTAT_ROOM_NUMBER),L_NETSTAT_ROOM_NUMBER);
				 l=L_NETSTAT_ROOM_NUMBER;
				 break;
		case NETSTAT_SENSORID:
				 readint(field, (int *)&((block+current_point)->sensorid),  L_NETSTAT_SENSORID, buf, 0);
				 break;
		case NETSTAT_SENSOR_ADD:
				 n = (block+current_point)->sensoradd;
				 readint(field, (int *)&n,  L_NETSTAT_SENSOR_ADD, buf, 0);
				 break;
		case NETSTAT_AUTO_MAN:
				 automan((block+current_point)->auto_manual, buf);
				 l=L_NETSTAT_AUTO_MAN;
				 break;
		case NETSTAT_ROOM_TEMP:
				 n = (block+current_point)->room_temp;
				 readint(field, (int *)&n,  L_NETSTAT_ROOM_TEMP, buf, 0);
				 break;
		case NETSTAT_SET_TEMP:
				 n = (block+current_point)->set_temp;
				 readint(field, (int *)&n,  L_NETSTAT_SET_TEMP, buf, 0);
				 break;
		case NETSTAT_ROOM_STATUS:
				 break;
		case NETSTAT_AUTO_TIME:
				 n = (block+current_point)->auto_time;
				 readint(field, (int *)&n,  L_NETSTAT_AUTO_TIME, buf, 0);
				 break;
		}
 return l;
}
*/
int netstat_show(void)
{
		RS232Error error;
		int i,ack[MAX_NETSTATS];
		int l1, st, net,status,success[MAX_NETSTATS];
		unsigned int leng;
		char *data;
		GGrid *wgrid;
		hide_pointer();

		set_semaphore_dos();
//		data=new char[100]; // MAX_NETSTATS * sizeof(Str_netstat_point)
		netstatbuf=new Str_netstat_point[1];
		//[MAX_NETSTATS];
		clear_semaphore_dos();
		memset(netstatbuf,'\0',sizeof(Str_netstat_point));
		//MAX_NETSTATS*sizeof(Str_netstat_point));
		memset(ack,0x00,sizeof(ack));


		leng=0;
		i=0;
// test data
//		for(i=0;i<MAX_NETSTATS;i++)
//		{
			memcpy(netstatbuf[i].description,"abcdefghijk",12);
			netstatbuf[i].sensorid=1;
			netstatbuf[i].sensoradd=1;
			netstatbuf[i].room_temp=19;
			netstatbuf[i].set_temp=21;
			netstatbuf[i].auto_manual=0;
			netstatbuf[i].version=1;
//		}

		leng=sizeof(netstatbuf);
//		for(i=0;i<MAX_NETSTAT_T3000;i++)
//		{

//ADI			if(net_call(WRITENETSTAT_T3000, 0, (char *)netstatbuf, &leng, 2,  3, NETCALL_SIGN, TIMEOUT_NETCALL)==SUCCESS)
				ack[i]=1;
//ADI			else
				ack[i]=0;
//		}

/*
		for(i=0; i<MAX_NETSTATS; i++)
		{
			status = net_call(READNETSTAT_T3000, 0, data, &leng, i,
							  1, NETCALL_SIGN, TIMEOUT_NETCALL);
			if(status!=SUCCESS)
				ack[i]=0;
			else if(status==SUCCESS)
				puttobuf(ptr_block,leng,netstatbuf);
		}
*/
		wgrid=new GGrid(4, 4, 76, 22, GRID, NULL,NETSTAT, ptr_panel->GlPanel_type,
						ptr_panel->GlPanel, ptr_panel->GlNetwork);
		wgrid->GWSet("Netstat Panels",Lightgray,Darkgray);
		wgrid->GShowGrid();
		while (!wgrid->HandleEvent())
		{
/*			if(wgrid->modify)
			{
				wgrid->GSend(1);
				wgrid->modify = 0;
			}
			else
				wgrid->GRead(SMALLBANK);
*/		}
	set_semaphore_dos();
		delete wgrid;
		delete netstatbuf;
		netstatbuf = NULL;
	clear_semaphore_dos();
	return 0;
}

Netstat_block::Netstat_block(GGrid *pthis, byte pt, byte p, int net,
							 signed char type, byte pnum)
				:Block(pthis, pt, p, net, type, pnum, N_NETSTAT, (char *)&line_buf)
{
		int npoint=0,i;

		if(type==INDIVIDUAL)
		{
			number_of_points=1;
			npoint =  pnum-1;                // num_point
		}
		else
		{
			number_of_points=MAX_NETSTATS;
		}
		set_semaphore_dos();
		block=new Str_netstat_point[number_of_points];
		clear_semaphore_dos();

		if( local_request(p, net) )
			memmove(block,&ptr_panel->netstats[npoint],number_of_points*sizeof(Str_netstat_point));
		else
			memset(block,'\0',number_of_points*sizeof(Str_netstat_point));

//		block=netstatbuf;
		r.RecStruct(N_NETSTAT,netstat_struct);
		h.HSet(N_NETSTAT,r.RecStruct(1),number_of_points);
}

Netstat_block::~Netstat_block()
{
  set_semaphore_dos();
  if(block)
  {
	 delete [] block;
  }
  clear_semaphore_dos();
}

int Netstat_block::Read(int field, char key)
{
 char buf[50],l,s[90];

 if(key==INSERT)
 {
 }
 else
 {

	switch (field) {
		case NETSTAT_NUM:
				break;

		case NETSTAT_DESCRIPTION:
				getalpha(field, (block+current_point)->description, L_NETSTAT_DESCRIPTION);
//				PutAlpha(field,buf);
				break;

		case NETSTAT_AUTO_MAN:
				(block+current_point)->auto_manual=automan(!(block+current_point)->auto_manual, buf);
				PutAlpha(field, buf);
				refresh_time = 0;
				break;

		case NETSTAT_VERSION:
				getalpha(field, s, L_NETSTAT_VERSION);
				(block+current_point)->version=atoi(s);
		//		PutAlpha(field,buf);
				break;

		case NETSTAT_SENSORID:
/**************************************
**********  Dina Long add ************
********     2.4.1998   *************
**********   code begin  *************
**************************************/
		//		itoa((block+current_point)->sensorid,s,10);
				getalpha(field, s, L_NETSTAT_SENSORID);
				(block+current_point)->sensorid=atoi(s);
		//		PutAlpha(field,buf);
/**************************************
**********  Dina Long add ************
********     2.4.1998   *************
**********   code end   *************
**************************************/
				break;

		case NETSTAT_SENSOR_ADD:
/**************************************
**********  Dina Long add ************
********     2.4.1998   *************
**********   code begin  *************
**************************************/
//				itoa((block+current_point)->sensoradd,s,10);
				getalpha(field, s, L_NETSTAT_SENSOR_ADD);
				(block+current_point)->sensoradd=atoi(s);
//				PutAlpha(field,buf);
/**************************************
**********  Dina Long add ************
********     2.4.1998   *************
**********   code end  **************
**************************************/
				break;

		case NETSTAT_ROOM_TEMP:
/**************************************
**********  Dina Long add ************
********     2.4.1998   *************
**********   code begin  *************
**************************************/
//				itoa((block+current_point)->room_temp,s,10);
				getalpha(field, s, L_NETSTAT_ROOM_TEMP);
				(block+current_point)->room_temp=atol(s);
//				PutAlpha(field,buf);
/**************************************
**********  Dina Long add ************
********     2.4.1998   *************
**********   code begin  *************
**************************************/
				break;

		case NETSTAT_SET_TEMP:
/**************************************
**********  Dina Long add ************
********     2.4.1998   *************
**********   code begin  *************
**************************************/
				getalpha(field, s, L_NETSTAT_SET_TEMP);
				(block+current_point)->set_temp=atol(s);
//				PutAlpha(field,buf);
/**************************************
**********  Dina Long add ************
********     2.4.1998   *************
**********   code end  *************
**************************************/
				break;
/*
		case NETSTAT_COV:
//				ftoa((block+current_point)->sensorid,s,10);
				getalpha(field,s, L_NETSTAT_SENSORID);
				PutAlpha(field,buf);
				break;

		case NETSTAT_ROOM_NUMBER:
				getalpha(field, (block+current_point)->roomnumber, L_NETSTAT_ROOM_NUMBER);
				PutAlpha(field,buf);
				break;

		case NETSTAT_OCCUPIED:
				itoa((block+current_point)->occupied,s,10);
				getalpha(field, s, L_NETSTAT_OCCUPIED);
				PutAlpha(field,buf);
				break;

		case NETSTAT_AUTO_TIME:
				itoa((block+current_point)->auto_time,s,10);
				getalpha(field, s, L_NETSTAT_AUTO_TIME);
				PutAlpha(field,buf);
				break;

		case NETSTAT_VALVE:
				itoa((block+current_point)->valve,s,10);
				getalpha(field, s, L_NETSTAT_VALVE);
				PutAlpha(field,buf);
				break;

		case NETSTAT_FANSPEED:
				itoa((block+current_point)->fanspeed,s,10);
				getalpha(field, s, L_NETSTAT_FANSPEED);
				PutAlpha(field,buf);
				break;

		case NETSTAT_STATUS:
				itoa((block+current_point)->status,s,10);
				getalpha(field, s, L_NETSTAT_STATUS);
				PutAlpha(field,buf);
				break;*/
	}
/**************************************
**********  Dina Long add ************
********     1.23.1998   *************
**********   code begin  *************
**************************************/
	pgrid->GGPutField(field,Lightgray,Black);
	pgrid->modify = TRUE;
/**************************************
**********  Dina Long add ************
********     1.23.1998   *************
**********   code end    *************
**************************************/
 }
}

int Netstat_block::GetRec(void)
{
	int i;

	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,'\0',sizeof(struct NETSTAT_LineBuf));

	for(i=0; i<fields_number; i++)
	{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);	}
	return FX_SUCCESS;
}

int Netstat_block::GetField(int field, char *buf)
{
	int l,n,i;
	long l1;
//	char *c;
	byte v;
//	c=new char[21];
//	memset(c,0x00,sizeof(c));

	l=0;
	switch (field) {
		case NETSTAT_NUM:
				 nr_point(buf);
				 break;

		case NETSTAT_DESCRIPTION:
				 memcpy(buf , lalign((block+current_point)->description,L_NETSTAT_DESCRIPTION),L_NETSTAT_DESCRIPTION);
				 l=L_NETSTAT_DESCRIPTION;
				 break;
/*		case NETSTAT_COV:
				 n= (block+current_point)->valve;
				 readfloat(field, long *pf,  int length, int dec, char *p, int read, float min, float max)
				 l=L_NETSTAT_VALVE;
				 break;

		case NETSTAT_ROOM_NUMBER:
				 memcpy(buf , lalign((block+current_point)->roomnumber,L_NETSTAT_ROOM_NUMBER),L_NETSTAT_ROOM_NUMBER);
				 l=L_NETSTAT_ROOM_NUMBER;
				 break;
*/
		case NETSTAT_VERSION:
/**************************************
**********  Dina Long add ************
********     2.3.1998   *************
**********   code end    *************
**************************************/
				i=(int)(block+current_point)->version;
				itoa(i,buf,10);
				lalign(buf,L_NETSTAT_VERSION);
/**************************************
**********  Dina Long add ************
********     2.3.1998    *************
**********   code end    *************
**************************************/
//				readint(field, (int *)&((block+current_point)->version), L_NETSTAT_VERSION, buf, 0);
//				l=L_NETSTAT_VERSION;
				break;
		case NETSTAT_SENSORID:
				i=(int)(block+current_point)->sensorid;
/**************************************
**********  Dina Long add ************
********     2.3.1998   *************
**********   code begin *************
**************************************/
				itoa(i,buf,10);
				lalign(buf,L_NETSTAT_SENSORID);
/**************************************
**********  Dina Long add ************
********     2.3.1998   *************
**********   code end    *************
**************************************/
//				readint(field, (int *)&((block+current_point)->sensorid),  L_NETSTAT_SENSORID, buf, 0);
//				l=L_NETSTAT_SENSORID;
				break;

		case NETSTAT_SENSOR_ADD:
				i=(int)(block+current_point)->sensoradd;
/**************************************
**********  Dina Long add ************
********     2.3.1998   *************
**********   code begin *************
**************************************/
				itoa(i,buf,10);
				lalign(buf,L_NETSTAT_SENSOR_ADD);
/**************************************
**********  Dina Long add ************
********     2.3.1998   *************
**********   code end    *************
**************************************/
//				n = (block+current_point)->sensoradd;
//				readint(field, (int *)&n,  L_NETSTAT_SENSOR_ADD, buf, 0);
//				l=L_NETSTAT_SENSOR_ADD;
				break;

		case NETSTAT_AUTO_MAN:
				 automan((block+current_point)->auto_manual, buf);
				 l=L_NETSTAT_AUTO_MAN;
				 break;

		case NETSTAT_ROOM_TEMP:
				l1=(block+current_point)->room_temp;
/**************************************
**********  Dina Long add ************
********     2.3.1998   *************
**********   code begin *************
**************************************/
				ltoa(l1,buf,10);
				lalign(buf,L_NETSTAT_ROOM_TEMP);
/**************************************
**********  Dina Long add ************
********     2.3.1998   *************
**********   code end    *************
**************************************/
//				 n = (block+current_point)->room_temp;
//				 readint(field, (int *)&n,  L_NETSTAT_ROOM_TEMP, buf, 0);
//				 l=L_NETSTAT_ROOM_TEMP;
				 break;

		case NETSTAT_SET_TEMP:
				l1=(block+current_point)->set_temp;
/**************************************
**********  Dina Long add ************
********     2.3.1998   *************
**********   code begin *************
**************************************/
				ltoa(l1,buf,10);
				lalign(buf,L_NETSTAT_SET_TEMP);
/**************************************
**********  Dina Long add ************
********     2.3.1998   *************
**********   code end    *************
**************************************/
//				 n = (block+current_point)->set_temp;
//				 readint(field, (int *)&n,  L_NETSTAT_SET_TEMP, buf, 0);
//				 l=L_NETSTAT_SET_TEMP;
				 break;
/*
		case NETSTAT_OCCUPIED:
				 n = (block+current_point)->occupied;
//				 if(n==1)c="Occupied";
//				 else c="Empty";
//				 readint(field, (int *)&n,  L_NETSTAT_SET_TEMP, buf, 0);
				 l=L_NETSTAT_SET_TEMP;
				 break;

		case NETSTAT_AUTO_TIME:
				 n = (block+current_point)->auto_time;
				 readint(field, (int *)&n,  L_NETSTAT_AUTO_TIME, buf, 0);
				 l=L_NETSTAT_AUTO_TIME;
				 break;

		case NETSTAT_VALVE:
				 n= (block+current_point)->valve;
//				 readfloat(field, );
				 l=L_NETSTAT_VALVE;
				 break;

		case NETSTAT_FANSPEED:
				 i=(block+current_point)->fanspeed;
				 switch(i){
					case 0:
						c="OFF";
						break;
					case 1:
						c="LOW";
						break;
					case 2:
						c="MED";
						break;
					case 3:
						c="HIGH";
						break;
				 }
				 l=L_NETSTAT_FANSPEED;
				 break;

		case NETSTAT_STATUS:
				 i=(block+current_point)->status;
				 if(i==0)c="Cool";
				 else c="Heat";
				 n=readint();
				 l=L_NETSTAT_STATUS;
				 break;*/
		}
//		delete c;
 return l;
}

/*
// flag : 1 -- t3000 to point , 0 -- point to t3000
void Netstat_block::Convert(void)
{

} */

void LoadNetstatDataFromFile(void)
{
	FILE *f;
	char *buf;
	long length;
	int i, k, m, version, num, number;
	uint n, j, l;

	set_semaphore_dos();
	buf=new char[1000];
	clear_semaphore_dos();

	if ((f=fopen("netstat.dat","rb+"))==NULL)
	{
		clear_semaphore_dos();
//		DisplayMessageT(20, 7, 60, 11, NULL, " File not loaded! ",NULL, Black, NULL, 1000);
//		onemin = 1;
		resume(VIRTUAL);
	}
	else
	{
		m = 1;
		fread( buf, 26, 1, f); //time and date
		fread( &version, 2, 1, f); // version of netstat
		fread( buf, 22, 1, f); // reserved bytes
		fread( &number, 2, 1, f); // number of netstats
		fread( &num, 2, 1, f); // size of netstat_point
	}
}

void SaveNetstatDataToFile(void)
{

}



int netstatus_show(void)
{
	RS232Error error;
	int l1,i;
	GGrid *wgrid;
	Station_point *st_list;
	hide_pointer();

	asm push es;
	set_semaphore_dos();
	netstatusbuf=new Str_netstatus_point[MAX_STATIONS];
	clear_semaphore_dos();
	memset(netstatusbuf,'\0',MAX_STATIONS*sizeof(Str_netstatus_point));

	st_list = station_list;
	if( !serial_access )
	{
	 for(l1=0; l1<MAX_Routing_table ; l1++)
	 {
		if( (Routing_table[l1].status&IPX_ACTIVE)==IPX_ACTIVE ||
				(Routing_table[l1].status&TCPIP_ACTIVE)==TCPIP_ACTIVE ||
				(Routing_table[l1].status&RS485_ACTIVE)==RS485_ACTIVE )
		 {
			if( Routing_table[l1].Port.network == networkaddress )
			{
			 st_list = ((class ConnectionData *)Routing_table[l1].ptr)->station_list;
			 break;
			}
		 }
	 }
	}
		for(i=0;i<MAX_STATIONS;i++)
		{
		 if(st_list[i].state)
		 {
			memcpy(netstatusbuf[i].name, st_list[i].name, 16);
			if(st_list[i].panel_type==T3000)
			 strcpy(netstatusbuf[i].type, "T3000");
			else
			 strcpy(netstatusbuf[i].type, "Mini");
			longtoa(st_list[i].version*10l, 5 , 2, netstatusbuf[i].version);
//			ftoa(((float)st_list[i].version)/100., 5, 2, netstatusbuf[i].version);

			if(netoperation[i]==0)
			 strcpy(netstatusbuf[i].update, "No");
			if(netoperation[i]==0x01)
			 strcpy(netstatusbuf[i].update, "Yes, Not Loaded");
			if(netoperation[i]==0x03)
			 strcpy(netstatusbuf[i].update, "Yes, Loaded");
			if(netoperation[i]==0x04)
			 strcpy(netstatusbuf[i].update, "Saved");
		 }
		}
		wgrid=new GGrid(4,4,76,22,GRID,NULL,NETSTATUS,ptr_panel->GlPanel_type,ptr_panel->GlPanel,ptr_panel->GlNetwork);
		wgrid->GWSet("Network status",Lightgray,Darkgray);
		wgrid->GShowGrid();
		while (!wgrid->HandleEvent());
		delete wgrid;
		set_semaphore_dos();
		delete netstatusbuf;
		netstatusbuf = NULL;
		clear_semaphore_dos();
	  asm pop es;
		return 0;
}

Netstatus_block::Netstatus_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
				:Block(pthis, pt, p, net, type, pnum, N_NS, (char *)&line_buf)
{
			int npoint=0;
			if(type==INDIVIDUAL)
			 {
				number_of_points=1;
				npoint =  pnum-1;                // num_point
			 }
			else
			{
				number_of_points=MAX_STATIONS;
			}
			block=netstatusbuf;
			r.RecStruct(N_NS,netstatus_struct);
			h.HSet(N_NS,r.RecStruct(1),number_of_points);
}

Netstatus_block::~Netstatus_block()
{
}

int Netstatus_block::Read(int field, char key)
{
 if(key==INSERT)
 {
 }
 else
 {
 }
}

int Netstatus_block::GetRec(void)
{
	int i;

	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,'\0',sizeof(struct NS_LineBuf));

	for(i=0; i<fields_number; i++)
	{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
	}
	return FX_SUCCESS;
}

int Netstatus_block::GetField(int field, char *buf)
{
	int l,n;

	l=0;
	switch (field) {
		case NS_NUM:
				 nr_point(buf);
				 break;
		case NS_NAME:
				 memcpy(buf , (block+current_point)->name,L_NS_NAME);
				 lalign(buf,L_NS_NAME);
				 l=L_NS_NAME;
				 break;
		case NS_TYPE:
				 memcpy(buf , (block+current_point)->type,L_NS_TYPE);
				 lalign(buf,L_NS_TYPE);
				 l=L_NS_TYPE;
				 break;
		case NS_VER:
				 memcpy(buf , (block+current_point)->version, L_NS_VER);
				 lalign(buf,L_NS_VER);
				 break;
		case NS_PRG:
				 memcpy(buf , (block+current_point)->prg, L_NS_PRG);
				 lalign(buf,L_NS_PRG);
				 break;
		case NS_UPDATE:
				 memcpy(buf , (block+current_point)->update,L_NS_UPDATE);
				 lalign(buf,L_NS_UPDATE);
				 break;
		case NS_NOTE:
				 break;
		}
 return l;
}

