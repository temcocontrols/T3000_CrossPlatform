#define NEW
extern void *newalloc(long size);
extern void newdelete(void *ptr);
#include <windows.h>
#include <math.h>
#include "recstruc.h"
#include "fxengine.h"
#include "t3000def.h"
#include <string.h>
#include "ggrid.h"
#include "gedit.h"
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include "_msdos.h"
#include "color.hpp"
#include "colormap.hpp"
#include "tifcodec.hpp"
#include "imgviewr.hpp"
#include "serial.h"
#include "t3000hlp.h"

#define min(a,b)    (((a) < (b)) ? (a) : (b))

#define REFRESH_TIME 200
#define DELETE_ELEMENT 0
#define ADD_ELEMENT    1
#define UPDATE_ELEMENT 2

#define ESC 27

#include "mtkernel.h"
#include "gmbar.h"
//#include "netbios.h"
#include "graph.h"
#include "rs485.h"
#include "router.h"

#define TEXT_FOND_COLOR White
enum  {  DISPLAY_LABEL = 0, DISPLAY_DES, DISPLAY_VALUE,  DISPLAY_ICON,
				 DISPLAY_ICON_LABEL, DISPLAY_ICON_DES, DISPLAY_ICON_VALUE };

extern icon *points_icon;

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
extern int Brown;
extern int Magenta;


extern Pshape ARROW;
extern Pshape CHECK;
extern Pshape CROSS;
extern Pshape GLOVE;

extern char remote_points_OUT;
extern char	 NotResponse1;
extern char maxtbl;
extern int ipxport, rs485port;
extern unsigned int MAX_HEAP_GRP;   //15000;
extern Panel_info1 Panel_Info1,panel_info1;
extern char interface_mode;
extern char _far tempbuf[65];
extern char remote_path[65];
extern char huge *ctrlbreak_text;
extern char huge *lin_hor;
extern int fground;
extern char GAlarm,gAlarm;
extern unsigned long timestart;
extern unsigned long timesec1970;

extern int mode_text;
extern char huge *message[];
extern rgb init_pal[16];
extern char int_disk;

extern Station_point station_list[32];
extern int ind_station;
extern char station_name[NAME_SIZE];
extern int  station_num;
extern int  Station_NUM;
extern int local_panel;

extern int refresh_time;
extern int refresh_time_init;
//extern unsigned long display_grp_time;

//extern OPERATOR_LIST operator_list;

extern Point_Net amon_inputs[MAX_POINTS_IN_MONITOR];
extern int current_mon;
extern Str_monitor_point *current_analog_mon;
extern Str_monitor_work_data *current_mon_workdata ;
extern ulong *pactivepanels;
extern Station_point *pstation_list_sel;

extern int fond_color;
extern int prg_active;
int FONDCOLOR=Lightgray;
int BOXCOLOR=Lightblue;
#define  BOXTITLE  Blue

extern char nothing;

extern int lat_char_n;
extern int lung_char_n;

extern Point_Net nested_grp[MAX_NEST_GRP];
extern int ind_nested_grp;
extern Point_Net current_opened_grp;
extern char control;
extern byte serial_access;

extern char gpointname[17];
extern int network_select, network_sel_tmp;
extern int panel_select, panel_sel_tmp;

enum {PROGR=0, OPERATOR=1 };

	union key {
		int i;
		char ch[2];
		} ;

#include <color.hpp>
extern int localnetwork(int net);
extern long aftolproc(char *avalue);
extern float atofproc(char *avalue);
extern unsigned int countlength(int command, int arg);
extern void alarm_routine(void);
extern int ReadWindow(int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							 int bkgndreadcolor, int readcolor, char *text, char *buf, int width, char *sablon=NULL);
extern int closest_rgb(rgb x, rgb *pal, int npal);
extern void get16( rgb * pal, int nclrs );
extern void set16( rgb * pal, int nclrs );
extern int setregister(int);
extern int setmousetext(void);
extern void set_vid_mem( void );
extern int writepropertystate(Point_Net point, int state, int t=0);
extern int writepropertyauto(Point_Net point, int auto_manual);
extern int writepropertyvalue(Point_Net point, long point_value);
extern void showpoints(int man, int Panel_type, int Panel, int Network, int arg=0, int maxtbl=0);
extern int checkpointpresence(int num_point,int point_type,int num_panel,int num_net, int panel, int network);
extern int checkmaxpoints(int num_point,int point_type,int num_panel,int num_net);

//class GMenuBar;
extern GMenuBar G;
extern char *lin_text;

extern int on_screen;
extern int picture_write;

extern  char huge *grp_message[];
extern  char huge *graphic_grp_message[];

extern char *heap_grp;
extern unsigned long ind_heap_grp;
extern unsigned high_mem_block;
extern Panel *ptr_panel;
extern byte cod_command[AY+1];

extern char huge *lin_menu;
extern int maxx, maxy;

extern XmsDes *Des;

extern dig_range_form huge dig_range_array[];
extern an_range_form huge in_range_array[];
extern an_range_form huge out_range_array[];
extern an_range_form huge var_range_array[];

extern int tif(char *argv,int x1, int x2, int y1,int y2);

extern int updateremotepoint(Point_Net point, int network);
extern void deleteremotepoint(Point_Net point, int network);
extern int bioskey_new(int cmd);
extern int icommand(char *buf, int from, byte panel, int network);
extern int net_call(int command, int arg,  char *data, uint *length , int dest,
				 int network, int others=0, int timeout=TIMEOUT_NETCALL,
				 char *returnargs=NULL, int *length_returnargs=NULL,
				 char *sendargs=NULL, int length_sendargs=0, char bytearg=0, int port=-1);
extern void Border(int ltopx, int ltopy, int rbottomx, int rbottomy, int colour,int bcolour);
extern char *ispoint(char *token,int *num_point,byte *var_type, byte *point_type, int *num_panel, int *num_net, int network=0, byte panel=0, int *netpresent=0);
extern char *islabel(char *token,int *num_point,int *var_type,int *point_type,int *num_panel);
//extern int put_point(int point, float value, int ana_dig, int prog_op);
extern void chbkg(int lx, int ly, int width, int bkgnd, int frgnd, int unchangecol=127, int height = 0);
extern char *ltrim(char *text);
extern void msettextstyle(int font, int dir, int chars);
extern char *rtrim(char *text);
extern int print_alarm_word(void);
extern int initamoninputsscreen(void);
extern int program_routine(int num_point,int point_type,int num_panel,int num_net);
extern void annual_routine(int current_point,int panel,int network,int type);
extern void weekly_routine(int current_point,int panel,int network,int type);
extern void mclrscr(char x1, char y1, char x2, char y2, char col);
extern void DisplayError(int lx, int ly, int rx, int ry, char *message,int bkgnd, int frgnd, int tbkgnd, int fcolor=Black);
extern void DisplayMessage(int lx, int ly, int rx, int ry, char *title, char *message, GWindow **Er1, int fcolor=Black, GWindow *Er2=NULL, long delay=0);
extern void DisplayMessageT(int lx, int ly, int rx, int ry, char *title, char *message, GWindow **Er1, int fcolor=Black, GWindow *Er2=NULL, long delay=0);
extern void DeleteMessage(GWindow *p);
extern int draw_icon(int x, int y, struct icon huge *ptr_icon, char copy = 0, rgb *current_pal=NULL, char save_under=1);
extern void getkey(void);
extern int check_access(int ptype, int num=-1, int mes=R_NA);
extern void clear_color(int lx, int length, int ly, int ry, char *lin_text, int bkgnd, int frgnd);
extern void changechar(int arg=0);
extern void restorechar(int arg=0);

extern unsigned char tbl_bank[MAX_TBL_BANK];

char huge *Heap_grp_alloc(int bytes);
int Heap_grp_resizedown(char huge **old, int width, int bytes);
int Heap_grp_resizeup(char huge **old, int bytes);
int Heap_grp_dealloc(char huge **old, int bytes_old);

void memsize(void);
int graphic_mode(Control_group_point *block, int current_point, int call_type, byte panel, int network, int display, Point_Net *retpoint);
int amon_routine(byte num_point,byte num_panel,int net, int call_type,int x,GGrid *pgrid);

void pvalue(GWDialog *D)    ;
void pcolor(GWDialog *D)    ;
void ponhigh(GWDialog *D)   ;
void pofflow(GWDialog *D)   ;
void pshowpoint(GWDialog *D) ;
void pauto(GWDialog *D)      ;
void ptextsize(GWDialog *D)  ;
void phighlimit(GWDialog *D) ;
void plowlimit(GWDialog *D) ;
void pdisplay(GWDialog *D) ;
void pinfofile(GWDialog *D);
void pload(GWDialog *D);
void piconname(GWDialog *D);

void update_value_grp_elem(Str_grp_element *group_element, int nr_elements, int pri=0);
uint cell(uint hx, uint hy, Str_grp_element *group_element, Str_grp_work_data *grp_workdata, byte panel, int network, int print, byte put = 1);
extern int	put_point_info(Point_info *point_info);
extern int	get_point_info(Point_info *point_info, char **des=NULL, char **label=NULL, char **ontext=NULL, char **offtext=NULL, char pri=0, int network = 0xFFFF);
extern char *lalign(char *buf, int n);
extern char *ralign(char *buf, int n);
extern void ftoa(float f, int length, int ndec, char *buf);
extern void longtoa(long f, int length, int ndec, char *buf);
extern int pointtotext(char *buf,Point_Net *point);
extern int pointtotext(char *buf,Point_T3000 *point);
extern int texttointerval( char *textbuffer,char *seconds , char *minutes , char *hours, char c=':' );
extern char * intervaltotext(char *textbuf, long seconds , unsigned minutes , unsigned hours, char *c=":");
extern int local_request(int panel, int network);
extern int ptpnetwork(int net);

extern int GetRange_Out(int range);
extern int GetRange_In(int range);
extern int GetRange_Var(int range);

extern int status_mouse;
extern char DIAL_action, DIAL_updategrp;

static int index_cur=0;
static int index_max_group_element=0;
static int index_max=0;
int xcur_grp,ycur_grp;

int exit_time_display;

HANDLE handle_group_element;
Str_grp_element	*group_element;
Str_grp_element	*group_element_temp;
Str_grp_work_data *grp_workdata;

char objectbuf[10];

char type_dis;
/* the ranges and units of the items used */
char *ontext, *offtext;
char test_tiff = 1;
char copy_icon;
char t_icon;
char display_mode;

Point_Net localopenscreen;
char screen_access;
int modify_grp;
char modify_grp_new;
char monitor_accessed;
rgb *grp_current_pal;

char text_size[4][7]={{"TINY"},{"SMALL"},{"MEDIUM"},{"LARGE"}};

char huge *load_text     ="LOAD";
//char huge *des_text     ="20 char";
//char huge *label_text     ="8 char";
char huge *value_text     ="VALUE     :";
//char huge *val_text     ="Value";

char huge *d_text[7]  = { "8 char  ", "20 char ", "Value   ", "Icon    ",
																"Icon/8ch", "Icon/20c", "Icon/Val" };

char huge *text_place[4]  = { "Bottom", "Top   ", "Left  ", "Right "};
char huge *type_icon[2]  = { "Custom  ", "Standard"};
char huge *color_text     ="Display color ";
char huge *onhigh_text    ="High color    ";
char huge *offlow_text    ="Low color     " ;
char huge *viz_inviz_text="VIZ/INVIZ";
char huge *viz_point_text="VIZ";
char huge *inviz_point_text="INVIZ";
char huge *text_text      ="TEXT SIZE :";
char huge *high_limit     ="HIGH LIMIT:";
char huge *low_limit      ="LOW LIMIT :";
char huge *display_text   ="DISPLAY   :";
char huge *info_file_text ="MEMO FILE :";
char huge *texts   ="Text   ";
char huge *graphic="Graphic";
char huge *blank=" ";
char huge *blank3="   ";
char huge *default_text_icon = "default";
char far  *panelmis=" Panel missing or out of service! ";
char far  *pointins=" Point instance out of range! ";
extern char huge *grp;
extern char huge *Main;
extern char huge *Mini;
extern char huge *Suba;
extern char huge *Subb;
extern char huge *man;
extern char huge *autom;
extern char huge *nulbuf;
extern char huge *yes;
extern char huge *Yes;
extern char huge *No;
extern char huge *lin;
extern char huge *on;
extern char huge *off;
extern char huge *colon;
extern char huge *zero;
extern char huge *enabl;
extern char huge *disabl;

extern char point_cod[MAX_TBL_BANK][5];

//extern char huge  des[MAX_DES];
extern char huge mons[12];

char heap_grp_flag1,heap_grp_flag2,error_communication;
int dontch;
char far Icon_name_table[MAX_ICON_NAME_TABLE][14];
char (*icon_name_table)[14];
int maxelem_grouppool;
int curelem_grouppool;
int current_point_GRP;
uint update_length;
int panel_GRP;
int network_GRP;

//**********************************
//    class Control_group_block
//**********************************

Control_group_block::Control_group_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
							:Block(pthis, pt, p, net, type, pnum, N_GRP, (char *)&line_buf)
	 {
			int npoint=0;
			if(type==INDIVIDUAL)
			 {
				number_of_points=1;           //MAX_OUTPUT;
				npoint =  pnum-1;                // num_point
			 }
			else
			{
				if(maxtbl)
				{
				 number_of_points=maxtbl;           //MAX_OUTPUT;
				 maxtbl = 0;
				}
				else
					number_of_points=tbl_bank[GRP];           //MAX_OUTPUT;
			}
		 set_semaphore_dos();
		 block=new Control_group_point[number_of_points];
		 clear_semaphore_dos();
//		 if((local_panel &&  sp!=INDIVIDUAL) || (sp==INDIVIDUAL && p==Station_NUM))
//		 if((local_panel &&  p==Station_NUM) || (!local_panel &&  p==Station_NUM && p!=station_num))
		 if(local_request(p,net))
				memmove(block,&ptr_panel->control_groups[npoint],number_of_points*sizeof(Control_group_point));
		 else
				memset(block,'\0',number_of_points*sizeof(Control_group_point));
			r.RecStruct(N_GRP,grp_struct);
			h.HSet(N_GRP,r.RecStruct(1),number_of_points);
	 }

Control_group_block::~Control_group_block()
{
// set_semaphore_dos();
 delete block;
// clear_semaphore_dos();
// xcur_grp=1;ycur_grp=23;
}

print_des(Str_grp_element *group_element, Str_grp_work_data *grp_workdata, byte panel, int network, char len = 0)
{
//					 HANDLE handle;
					 char buf1[17],buf[41],*des=NULL,*label=NULL,*ontext=NULL,*offtext=NULL;
					 byte var_type,point_type;
					 int num_net,color,num_point,num_panel,k;
					 Point_Net *p;
					 Point_info point_info;
					 point_info = group_element->point_info;
					 if(!refresh_time && (point_info.point.point_type-1 == GRP ))
//												point_info.point.point_type-1 == PRG ||
//												point_info.point.point_type-1 == AMON))
							 return 0;

					 if(group_element->graphic_x_coordinate+group_element->graphic_y_coordinate+
							 group_element->text_x_coordinate+group_element->text_y_coordinate==0) return 0;
					 memset(buf,0,41);
					 if(mode_text)
							buf[0]=' ';
					 if (point_info.description_label==DISPLAY_ICON_VALUE +1)
					 {
						 strcat(buf,point_cod[point_info.point.point_type-1]);
						 strcat(buf,"S");
					 }
					 else
					 {
//						 if((local_panel &&  panel==Station_NUM) || (!local_panel &&  panel==Station_NUM && panel!=station_num) )
						 if(group_element->point_absent)
							point_info.description_label=DISPLAY_LABEL;
						 if(local_request(panel,network))
						 {
							 if(!group_element->point_absent)
								 get_point_info(&group_element->point_info, &des, &label,&ontext,&offtext,0,network);
							 point_info = group_element->point_info;
						 }
						 else
						 {
							if( !point_info.digital_analog )
							{
							 if(!group_element->point_absent)
							 {
							  num_point=dig_range_array[point_info.units].value % 2;
							  ontext= &dig_range_array[point_info.units].dunits[!num_point][0];
							  offtext= &(dig_range_array[point_info.units].dunits[num_point][0]);
							 }
							}
							p = &point_info.point;
							pointtotext(buf1,p);
							k=0;
							label=ispoint(rtrim(buf1),&num_point,&var_type, &point_type, &num_panel, &num_net, network, panel, &k);
							if(Des)
							{
								if(point_type!=CON && point_type!=TBL)
									des = Des->look_descriptor(num_panel,point_type,num_point);
								if(!des) des = label;
							}
						 }
						 if(!mode_text)
							 moveto(group_element->graphic_x_coordinate,group_element->graphic_y_coordinate);

						 if(!group_element->display_point_name)
						 {
						  if (point_info.description_label==DISPLAY_DES || point_info.description_label==DISPLAY_ICON_DES)
						  {
							 if(!des) des = label;
							 {
								if(des)
								 strcat(buf,des);
							 }
							}
							else
							 if (point_info.description_label==DISPLAY_LABEL || point_info.description_label==DISPLAY_ICON_LABEL)
							 {
								if(label)
								 strcat(buf,label);
							 }

						  if(point_info.description_label!=DISPLAY_VALUE && point_info.description_label!=DISPLAY_ICON_VALUE	&& !strlen(rtrim(buf)))
							{
							 if(mode_text)
							 {
								buf[0]=' '; buf[1]=0;
							 }
							 strcat(buf, gpointname);
						  }
						}
						if(mode_text && buf[1])
							 lalign(buf,22);
						if(!mode_text && buf[0])
							 rtrim(buf);

						 color = group_element->normal_color;

						if(!group_element->point_absent)
						{
						 if(point_info.point.point_type-1 != GRP &&
								point_info.point.point_type-1 != PRG &&
								point_info.point.point_type-1 != AMON &&
								point_info.point.point_type-1 != AR &&
								point_info.point.point_type-1 != WR )
						 {
//								strcat(buf,blank);
								if(!mode_text && buf[0])
									strcat(buf,blank);

								if(point_info.digital_analog)
								{
										if(point_info.units == time_unit)
										{
											intervaltotext( &buf[strlen(buf)], point_info.point_value / 1000L , 0 , 0);
										}
										else
										{
											longtoa(point_info.point_value, 7, 2, &buf[strlen(buf)]);
											ltrim(&buf[strlen(buf)-6]);
											strcat(buf,blank);
											var_type = 0;
											if( point_info.point.point_type-1==IN )
											{
												var_type = 1;
												if( point_info.units >=0 && point_info.units <=24 )
													strcat(buf,in_range_array[point_info.units].aunits);
											}
											else
											 if( point_info.point.point_type-1==OUT )
											 {
												var_type = 1;
												if( point_info.units >=0 && point_info.units <=6 )
													strcat(buf,out_range_array[point_info.units].aunits);
											 }
											 else
											  if( point_info.point.point_type-1==VAR || point_info.point.point_type-1==CON )
											  {
												 var_type = 1;
												 if( point_info.units >=0 && point_info.units <=42 )
													 strcat(buf,var_range_array[point_info.units].aunits);
												}
											if(var_type)
											{
											  if(point_info.point_value>(long)(group_element->high_limit*1000l) ) color = group_element->on_high_color;
											  if(point_info.point_value<(long)(group_element->low_limit*1000l) ) color = group_element->off_low_color;
											}
										}
								}
								else
								{
										if(point_info.point_value)
										{
											 color = group_element->on_high_color;
											 if(ontext)
												strcat(buf,ontext);
//											  else
//												strcat(buf,label);
										}
										else
										{
											 color = group_element->off_low_color;
											 if(offtext)
												strcat(buf,offtext);
//											 else
//												strcat(buf,label);
										}
								}
						 }
						 else
						 {
								 if( point_info.point.point_type-1!=GRP )
								 {
										if(!mode_text && buf[0])
										 strcat(buf,blank);
										if(point_info.description_label < DISPLAY_ICON || point_info.description_label == DISPLAY_ICON_VALUE )
										{
										 if(point_info.point_value)
										 {
											 if(ontext)
												strcat(buf,ontext);
										 }
										 else
										 {
											 if(offtext)
												strcat(buf,offtext);
										 }
                    }
								 }
						 }
            }
						if(!mode_text)
									rtrim(buf);
						strcat(buf,blank);
						if(!group_element->point_absent)
						{
							if (point_info.auto_manual!=AUTO)
										strcpy(&buf[strlen(buf)],"M");
						}
						else
								strcpy(&buf[strlen(buf)],"Absent");

					 }
					 var_type = strlen(buf);
					 num_point = 0;
					 if(!len)
					 {
						hide_pointer();
						if(mode_text)
						{
						 lalign(buf, 40);
//						 hide_pointer();

						 mxyputs(group_element->text_x_coordinate,group_element->text_y_coordinate,buf,-1,color);
						}
						else
						{
						 if(grp_workdata->ptr_save_bkgnd)
						 {
/*
								if(mouse_inside(group_element->graphic_x_coordinate,
													 group_element->graphic_y_coordinate,
													 group_element->graphic_x_coordinate+group_element->nchar*lat_char_n,
													 group_element->graphic_y_coordinate+lung_char_n) )
										hide_pointer();
*/
								mputimage(group_element->graphic_x_coordinate,group_element->graphic_y_coordinate,grp_workdata->ptr_save_bkgnd, COPY_PUT);
								mfarfree(grp_workdata->ptr_save_bkgnd);
								grp_workdata->ptr_save_bkgnd = NULL;
						 }
						 if(refresh_time && point_info.description_label >= DISPLAY_ICON)
						 {
//							hide_pointer();
							if( !grp_workdata->icon )
							{
//							 if( group_element[index_cur].default_icon )
							 if( group_element->default_icon )
							 {
//								 if(!points_icon[group_element[index_cur].point_info.point.point_type-1].status)
								 if(!points_icon[group_element->point_info.point.point_type-1].status)
								 {
									 set_semaphore_dos();
//									 group_element[index_cur].icon = new Icon((icon *)&points_icon[group_element[index_cur].point_info.point_name.main.point_type-1],group_element[index_cur].bkgnd_icon);
									 grp_workdata->icon = new Icon((icon *)&points_icon[group_element->point_info.point.point_type-1],group_element->bkgnd_icon);
									 clear_semaphore_dos();
								 }
								 else num_point = 1;
							 }
							 else
							 {
								set_semaphore_dos();
//								icon *ic=new icon(group_element[index_cur].icon_name);
								icon *ic=new icon(icon_name_table[group_element->icon_name_index]);
								clear_semaphore_dos();
								if(!ic->status)
								{
								 set_semaphore_dos();
//								 group_element[index_cur].icon = new Icon((icon *)ic, group_element[index_cur].bkgnd_icon);
								 grp_workdata->icon = new Icon((icon *)ic, group_element->bkgnd_icon);
								 clear_semaphore_dos();
								}
								else
								{
								 set_semaphore_dos();
								 delete ic;
								 clear_semaphore_dos();
								 num_point = 1;
								}
							 }
							}
							if(!num_point)
							{
							 grp_workdata->icon->draw_icon(group_element->xicon, group_element->yicon, copy_icon, grp_current_pal);
							 int x1,x2,y1,y2;
							 x1 = group_element->xicon; x2 = x1 + grp_workdata->icon->ptr_icon->width;
							 y1 = group_element->yicon; y2 = y1 + grp_workdata->icon->ptr_icon->height;
							 switch(group_element->text_place){
								case 0: y1 = y2 + 4;
													 x1 = (x1+x2)/2 - ((strlen(buf)-1)/2)*8;
													 break;
								case 1: y1 -= 12;
													 x1 = (x1+x2)/2 - ((strlen(buf)-1)/2)*8;
													 break;
								case 2: y1 = y2 - 12;
													 x1 = x1 - (strlen(buf)+1)*8;
													 break;
								case 3: y1 = y2 - 12;
														x1 = x2 + 8;
													 break;
							 }
							 group_element->graphic_x_coordinate = x1;
							 group_element->graphic_y_coordinate = y1;
							 if( x1 < 0 ) group_element->graphic_x_coordinate = 0;
							}
							else
							{
							 group_element->icon_present = 0;
							 group_element->text_present = 1;
							 if(point_info.description_label == DISPLAY_ICON )
							 {
								 group_element->point_info.description_label = DISPLAY_LABEL;
							 }
							 if(point_info.description_label > DISPLAY_ICON )
							 {
								 group_element->point_info.description_label -= DISPLAY_ICON_LABEL;
							 }
							 point_info.description_label = group_element->point_info.description_label;
							}
						 }
						 if(point_info.description_label != DISPLAY_ICON)
						 {
/*
							if(mouse_inside(group_element->graphic_x_coordinate,
												 group_element->graphic_y_coordinate,
												 group_element->graphic_x_coordinate+group_element->nchar*lat_char_n,
												 group_element->graphic_y_coordinate+lung_char_n) )
										hide_pointer();
*/
							grp_workdata->nchar=strlen(buf);
							unsigned long big;
							big = mimagesize(group_element->graphic_x_coordinate,group_element->graphic_y_coordinate,min(group_element->graphic_x_coordinate+grp_workdata->nchar*lat_char_n,maxx),group_element->graphic_y_coordinate+lung_char_n);
							mfarmalloc((char far **)&grp_workdata->ptr_save_bkgnd, (unsigned long)big);
							set_semaphore(&screen);
							getimage(group_element->graphic_x_coordinate,group_element->graphic_y_coordinate,min(group_element->graphic_x_coordinate+grp_workdata->nchar*lat_char_n, maxx),group_element->graphic_y_coordinate+lung_char_n,(void *)grp_workdata->ptr_save_bkgnd);
							settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
							if(color == fond_color)
								setcolor(Red);
							else
								setcolor(color);
							outtextxy(group_element->graphic_x_coordinate,group_element->graphic_y_coordinate,buf);
							settextstyle(SMALL_FONT,0,5);
							clear_semaphore(&screen);
						 }
						 else
						 {
							var_type = 0;
						 }
						}
						display_pointer();
					 }
					 else
						 if(point_info.description_label == DISPLAY_ICON)
							var_type = 0;

					 return var_type;
}

/*
int elemindex(Str_grp_element *group_element, int index_obj)
{
	int i,k=0;
	i=0;
	for(i=0; i<index_obj; i++, group_element++)
	{
		if(group_element->nr_element)
		{
				k++;
		}
	}
	return k;
}
*/

int send_grp(int local, int index_obj, int current_grp, Str_grp_element *group_element, int curline=2, int curcol=1, int panel=0, int network=0, int nr_element=0)
{
 uint i;
 int r=0;
 MouseStatus stat;
 Str_grp_element *grp, *p, *q;
 grp = group_element;

 int change=1,nr_elem=0;

 for(i=0;i<index_obj;i++,grp++)
		if( grp->nr_element )
			 nr_elem++;

 if(local)
 {
	Control_group_elements *cgrp;
	if( !heap_grp_flag1 && !heap_grp_flag2 )
	{
	 heap_grp_flag1 = 1;
	 cgrp = &ptr_panel->control_group_elements[current_grp];
	 if(local==DELETE_ELEMENT+3)    //delete elem
	 {
		if( cgrp->nr_elements )
		{
		 grp = cgrp->ptrgrp;
		 for(i=0;i<cgrp->nr_elements;i++,grp++)
		 {
			if( grp->nr_element==nr_element ) break;
		 }
		 if( i<cgrp->nr_elements )
		 {
			if( grp->point_info.point.panel+1 != Station_NUM )
			 deleteremotepoint(grp->point_info.point,grp->point_info.point.network);
			cgrp->nr_elements--;
			Heap_grp_resizedown((char huge **)&grp, sizeof(Str_grp_element), (cgrp->nr_elements-i)*sizeof(Str_grp_element));
		 }
		}
		heap_grp_flag1 = 0;
		return r;
	 }
	 if(local==ADD_ELEMENT+3)    //add elem
	 {
		if( cgrp->nr_elements )
		{
		 grp = cgrp->ptrgrp;
		 grp += cgrp->nr_elements;
		 update_value_grp_elem(group_element,nr_elem);
		 if( Heap_grp_resizeup((char huge **)&grp, sizeof(Str_grp_element)) )
		 {
			movedata(FP_SEG(group_element),FP_OFF(group_element) ,FP_SEG(grp),FP_OFF(grp), sizeof(Str_grp_element));
			cgrp->nr_elements++;
			if( group_element->point_info.point.panel+1 != Station_NUM )
			 updateremotepoint(group_element->point_info.point, group_element->point_info.point.network);
		 }
		 else
			r=1;
		 heap_grp_flag1 = 0;
		 return r;
		}
		local=2;
	 }
	 if(local==UPDATE_ELEMENT+3)    //update elem
	 {
		grp = cgrp->ptrgrp;
		for(i=0;i<cgrp->nr_elements;i++,grp++)
		{
			if( grp->nr_element==nr_element ) break;
		}
		if( i<cgrp->nr_elements )
		{
		 update_value_grp_elem(group_element,nr_elem);
		 movedata(FP_SEG(group_element),FP_OFF(group_element) ,FP_SEG(grp),FP_OFF(grp), sizeof(Str_grp_element));
    }
		heap_grp_flag1 = 0;
		return r;
	 }

	 if(local==2)
	 {
		grp = cgrp->ptrgrp;
		for(i=0;i<cgrp->nr_elements;i++, grp++)
		 if( grp->point_info.point.panel+1 != Station_NUM )
			deleteremotepoint(grp->point_info.point,grp->point_info.point.network);
	 }
	 update_value_grp_elem(group_element,nr_elem);
	 Heap_grp_dealloc((char huge **)&cgrp->ptrgrp, cgrp->nr_elements*sizeof(Str_grp_element));
	 cgrp->nr_elements = nr_elem;
	 p = cgrp->ptrgrp = (Str_grp_element *) Heap_grp_alloc(nr_elem*sizeof(Str_grp_element));
	 grp = group_element;
	 for(i=0;i<index_obj;i++, grp++)
			if(grp->nr_element)
				{
				 movedata(FP_SEG(grp),FP_OFF(grp), FP_SEG(p),FP_OFF(p) ,sizeof(Str_grp_element));
				 p++;
				}
	 if(local==2)
	 {
		grp = cgrp->ptrgrp;
		for(i=0;i<cgrp->nr_elements;i++, grp++)
		 if( grp->point_info.point.panel+1 != Station_NUM )
			updateremotepoint(grp->point_info.point,grp->point_info.point.network);
	 }
	 heap_grp_flag1 = 0;
	}
	else
	 r=1;
 }
 else
 {
//	 int j=0;
		i=0;
	 if( group_element_temp )
	 {
		q = group_element_temp;
	 }
	 else
	 {
		set_semaphore_dos();
	  q = new Str_grp_element[nr_elem];
	  clear_semaphore_dos();
	 }
//	 p = grp = group_element;
	 grp = group_element;
	 p = q;
//	 while(i<nr_elem)
	 while(i<index_obj)
	 {
			if(grp->nr_element)
			{
			  *p++ = *grp;
			}
			i++;
			grp++;
/*
			if(grp->nr_element)
				{
				 if(i!=j)
					 *p=*grp;
				}
			else
				{
				 while(j<index_obj && !grp->nr_element)
							{j++;grp++;}
				 *p=*grp;
				}
			i++;j++;
			p++;grp++;
*/
	 }
//	 p->graphic_y_coordinate=ycur_grp;
//	 p->graphic_x_coordinate=xcur_grp;
//	 p->nr_element=0;
//	 if(modify_grp)
//		p->text_x_coordinate=1;
//	 else
//		p->text_x_coordinate=0;
	 Delay(200);
//	 i = ((modify_grp?nr_elem:0)+1)*sizeof(Str_grp_element);
	 i = nr_elem*sizeof(Str_grp_element);
//	 r=net_call(19+100, current_grp, modify_grp?(char *)q:(char *)p, &i ,panel, networkaddress);
	 r=net_call(19+100, current_grp, (char *)q, &i ,panel, network,NETCALL_RETRY);
	 if( r==RS232_SUCCESS)
	 {
		if( icon_name_table )
		{
		 i = sizeof(Icon_name_table);
		 r=net_call(COMMAND_50+100, ICON_NAME_TABLE_COMMAND, (char*)icon_name_table, &i, panel, network,NETCALL_RETRY);
		}
	 }
	 if( !group_element_temp )
	 {
	  set_semaphore_dos();
	  if(q)
		  delete q;
	  clear_semaphore_dos();
	 }
 }

 modify_grp = 0;
 return r;
}


void update_value_grp_elem(Str_grp_element *group_element, int nr_elements, int pri)
{
	Str_grp_element *pgrp;
	pgrp = group_element;
	for(int i=0;i<nr_elements; pgrp++, i++)
	{
		get_point_info(&pgrp->point_info, NULL, NULL, NULL, NULL, pri, pgrp->point_info.point.network);
	}
}

int get_color(Str_grp_element *group_element)
{
  int color;
  color = group_element->normal_color;
  if(group_element->point_info.digital_analog)
  {
	 if(group_element->point_info.units != time_unit)
	 {
		if(group_element->point_info.point.point_type-1==IN || group_element->point_info.point.point_type-1==OUT
			|| group_element->point_info.point.point_type-1==VAR)
		{
		  if(group_element->point_info.point_value>(long)(group_element->high_limit*1000)) color = group_element->on_high_color;
		  else
			 if(group_element->point_info.point_value<(long)(group_element->low_limit*1000)) color = group_element->off_low_color;
		}
	}
  }
  else
  {
	if(group_element->point_info.point_value)
	 color = group_element->on_high_color;
	else
	 color = group_element->off_low_color;
  }
  return color;
}

int setscreenstate(Point_Net current_opened_grp)
{
	int i;
	if( (panel_info1.panel_type == T3000 && panel_info1.version >= 221) ||
			 (panel_info1.panel_type == MINI_T3000 && panel_info1.version >= 111) )
	{
	 if( writepropertystate(current_opened_grp, 1)==SUCCESS)
		return 1;
  }
	return 0;
}

int clearscreenstate(Point_Net current_opened_grp)
{
	int i;
	if( writepropertystate(current_opened_grp, 0)==SUCCESS)
	 return 1;
	return 0;
}

//int Control_group_block::fnc_group(void)
int fnc_group(Control_group_point *block, GGrid *pgrid, byte current_point, int call_type, byte panel, int network, int display, Point_Net *retpoint)
{
asm push es;
 Str_grp_element *pgrp;
 Str_grp_work_data *pworkdata;
 Control_group_elements *cgrp;
 int nrow = 24, ncol = 2;
 int curline=2,curcol=1,menu=0;
 char *des,*label;
 int bkgnd=FONDCOLOR, frgnd=White;
 int index_obj = MAX_ELEM;
 int local_panel_old;
 int x,y,k;
 int r=0;
 uint i;
 char bitmap[100];
 Point_Net openscreen;
 int rtime;
 index_cur=0;
 error_communication=0;
 unsigned long lastreadopenscreen;
 lastreadopenscreen	= timestart+timesec1970;
//
 on_screen=0;
 picture_write=1;
 group_element_temp = NULL;
 openscreen=current_opened_grp;
 localopenscreen.setzero();

 if(!mode_text && call_type!=INDIVIDUAL && call_type!=1 && dontch==0)
 {
	 pgrid->RestoreArea();
 }
// pgrid->on_screen = 0;
// pgrid->GReleaseWindow();
// G.HideMBar();
//	G.ReleaseMBar();

 if ( block->mode==1)
 {
	 mfarmalloc((char far **)&group_element, (sizeof(Str_grp_element)*2*MAX_ELEM+sizeof(Str_grp_work_data)*MAX_ELEM), handle_group_element);
	 group_element_temp=(Str_grp_element *)(((char *)group_element) + sizeof(Str_grp_element)*(MAX_ELEM));
	 grp_workdata = (Str_grp_work_data *)(((char *)group_element) + sizeof(Str_grp_element)*2*(MAX_ELEM));
	 if(local_request(panel,network))
		icon_name_table = Icon_name_table;
	 else
	 {
		set_semaphore_dos();
		icon_name_table = (char (*)[14])new char [MAX_ICON_NAME_TABLE*14];
	  clear_semaphore_dos();
		memset(icon_name_table,'\0',sizeof(Icon_name_table));
	 }
	 exit_time_display=0;
	 if(!local_request(panel,network))
		if( net_call(COMMAND_50, ICON_NAME_TABLE_COMMAND, (char*)icon_name_table, 0, panel, network,NETCALL_RETRY) != RS232_SUCCESS )
		r=1;
	 if(!r)
		r=graphic_mode(block,current_point,call_type,panel,network,display,retpoint);

//	 delete (char *)(group_element);
	 if( DIAL_updategrp==1)
		 resume(DIAL);
	 while( DIAL_updategrp==1);
	 DIAL_updategrp=0;
	 mfarfree(handle_group_element);
	 group_element_temp = NULL;
	 if(!local_request(panel,network))
	 {
		if( icon_name_table )
		{
		 for(i=0;i<MAX_ICON_NAME_TABLE;i++)
		 {
			 if( icon_name_table[i][0] )
			 {
				 i = sizeof(Icon_name_table);
				 net_call(COMMAND_50+100, ICON_NAME_TABLE_COMMAND, (char*)icon_name_table, &i, panel, network,NETCALL_RETRY);
				 break;
			 }
		 }
		 set_semaphore_dos();
		 delete (char *)(icon_name_table);
		 clear_semaphore_dos();
		}
	 }
	 display_pointer();
	 icon_name_table=NULL;
	 if(exit_time_display)
	 {
		asm pop es;
		return 0;
	 }
	 asm pop es;
	 return r;
 }
 else
 {
	grp_workdata = NULL;
	mfarmalloc((char far **)&group_element, (sizeof(Str_grp_element)*2*MAX_ELEM), handle_group_element);
	group_element_temp = (Str_grp_element *)(((char *)group_element) + sizeof(Str_grp_element)*(MAX_ELEM));
	if(!mode_text )
	{
	 mode_text = MODE_TEXT;
	 lat_char_n = 1;
	 lung_char_n = 1;
	 hide_pointer();
	 cleardevice();
	 restorecrtmode();
	 changechar();
	 Green=LIGHTBLUE;                 //2
	 Green1=WHITE; 						 //5
	 Blue1=DARKGRAY;                 //6
	 Darkgray=BROWN;           //8
	 Lightblue=GREEN;         //9
	 White=MAGENTA;                 //15
	 fond_color=TEXT_FOND_COLOR;
	 setregister(1);

	 asm {
		mov ax,21h
		int 33h
	 }
	 setmousetext();
	 move_mouse(30,20);
	 display_pointer();
	}

	BOXCOLOR=Lightblue;
	int esc = 0;
	exit_time_display=0;
	GWindow *D=NULL;
	local_panel_old = local_panel;
	while(!esc)
	{
	 esc = 1;
	 GMenuBar *grp_menu;
	 clear_color(1, 80, 1, 25, lin_text, bkgnd, Black);
	 hide_pointer();
	 mxyputs(20, 1, block->description, bkgnd, Red);
	 mxyputs(42, 1, block->label, bkgnd, Red);
	 display_pointer();
	 if(!display)
	 {
		 grp_menu = new GMenuBar(1,1,80,1,White,Black,Red,3,BARMENU,NULL);
	 }
	 uint j;
	 union key key;
	 key.ch[0]='\t';
	 screen_access=check_access(GRP, current_point);
	 if(local_request(panel,network))
	 {
		cgrp = &ptr_panel->control_group_elements[current_point];
		update_value_grp_elem(cgrp->ptrgrp,cgrp->nr_elements);
//	xcur_grp = cgrp->xcur_grp;
//	ycur_grp = cgrp->ycur_grp;
//	if( xcur_grp>2 || xcur_grp<1) xcur_grp=1;
//	if( ycur_grp>25 || ycur_grp<2) ycur_grp=2;
		for(i=0; i<cgrp->nr_elements;i++)
		{
		 if(!cgrp->ptrgrp[i].text_y_coordinate)
		 {
			j=i;
			if(cgrp->ptrgrp[0].text_y_coordinate)
			{
			 pgrp = group_element;
			 for(j=0;j<index_obj;j++,pgrp++)
				if( !pgrp->nr_element )
					break;
			}
			pgrp = &group_element[j];
			memcpy(pgrp,cgrp->ptrgrp+i,sizeof(Str_grp_element));
			if( (j/24)%2 ) x = 41;
			else x = 1;
			y = (j%48)%24+2;
			pgrp->nr_element=j+1;
			pgrp->text_y_coordinate=y;
			pgrp->text_x_coordinate=x;
//		 pgrp->ptr_save_bkgnd=0;
			xcur_grp = 1; ycur_grp = 2;
			modify_grp = 1;
		 }
		 else
		 {
			pgrp=&group_element[cgrp->ptrgrp[i].nr_element-1];
			memcpy(pgrp,cgrp->ptrgrp+i,sizeof(Str_grp_element));
//		 pgrp->ptr_save_bkgnd=0;
		 }
		}
		index_max=index_max_group_element=cgrp->nr_elements;
	 }
	 else
	 {
		Str_grp_element *buf;
		if( DIAL_updategrp==1)
		 resume(DIAL);
	  while( DIAL_updategrp==1);

		buf = group_element_temp;
		DisplayMessage(20, 7, 60, 11, ctrlbreak_text, "   Reading data ... ",&D);
		Delay(200);
		j = 0;
		NotResponse1=0;
		int s=net_call(19, current_point, (char *)buf, &j, panel, network, NETCALL_SIGN);
		NotResponse1=1;
		if(D)
		{
		 DeleteMessage(D);
		 D=NULL;
		}
		if(s==SUCCESS)
		{
		 index_max=j/sizeof(Str_grp_element);
		 index_max_group_element=index_max;
		 for( i=0; i<index_max;i++)
		 {
			if(!buf[i].text_y_coordinate)
			{
			 j=i;
			 if(buf[0].text_y_coordinate)
			 {
				pgrp = group_element;
				for(j=0;j<index_obj;j++,pgrp++)
				 if( !pgrp->nr_element )
					break;
			 }
			 pgrp = &group_element[j];
			 *pgrp=buf[i];
			 if( (j/24)%2 ) x = 41;
			 else x = 1;
			 y = (j%48)%24+2;
			 pgrp->nr_element=j+1;
			 pgrp->text_y_coordinate=y;
			 pgrp->text_x_coordinate=x;
//		 pgrp->ptr_save_bkgnd=0;
			 modify_grp = 1;
			}
			else
			{
			 pgrp = &group_element[buf[i].nr_element-1];
			 *pgrp=buf[i];
//		 pgrp->ptr_save_bkgnd=0;
			}
		 }
		}
		else
		{
		 key.ch[0]=27;
		 error_communication=1;
		}
   }

	 MouseStatus stat;

// textcolor(Blue);
// movedata(FP_SEG(ptr_panel->control_group_elements[current_point].ptrgrp),FP_OFF(ptr_panel->control_group_elements[current_point].ptrgrp) ,FP_SEG(group_element),FP_OFF(group_element),ptr_panel->control_group_elements[current_point].nr_elements*sizeof(Str_grp_element));

	 if( xcur_grp>2 || xcur_grp<1) xcur_grp=1;
	 if( ycur_grp>25 || ycur_grp<2) ycur_grp=2;
	 if(ycur_grp == 1) ycur_grp = 2;

	 char cont;
	 int page = -1;
	 int first=1, last_mouse=0;
	 refresh_time = refresh_time_init;
	 setscreenstate(current_opened_grp);
   modify_grp_new=0;
 while (1)
 {
	if (bioskey_new(1) || first)
	{
	 if(!first)
	 {
		key.i = bioskey_new(0);
		if (key.ch[0]==0)  key.ch[0]=key.ch[1];
	 }
	 if (key.ch[0]==27)  //esc
	 {
		if( DIAL_updategrp==1)
		 resume(DIAL);
	  while( DIAL_updategrp==1);

		if(!display)
		{
		 delete grp_menu;
		}
		if(!error_communication)
		{
		 if(!display)
		 {
			if(modify_grp)
			{
			 if( local_request(panel,network) )
			 {
				if(local_panel_old == local_panel)
				 send_grp(1,index_obj, current_point, group_element, curline, curcol);
			 }
			 else
			 {
				if( DIAL_updategrp==1)
				 resume(DIAL);
				while( DIAL_updategrp==1);
				send_grp(0,index_obj, current_point, group_element, curline, curcol,panel,network);
			 }
			}
		 }
		}
		DIAL_updategrp=0;
		mfarfree(handle_group_element);
		group_element_temp = NULL;

		xcur_grp = curcol;
		ycur_grp = curline;
//   clearscreenstate(current_opened_grp);
		if(exit_time_display)
		{
		 asm pop es;
		 return 0;
		}
		asm pop es;
		return esc;
	 }

	 if(key.ch[0]==1)  //CTRL-A  alarm  screen
	 {
				 menu=0;
				 first=1;
				 key.ch[0]=27;  //esc
				 esc = ALARMS+1;
				 continue;
	 }
	if (key.ch[0]==INSERT || key.ch[0]==ENTER || key.ch[0]==50 || key.ch[0]==DELETE)
	{
	 if( DIAL_updategrp==1 )
		 resume(DIAL);

	 if(key.ch[0]==DELETE && !display) //Delete
	 {
		 if(screen_access==R_READ_WRITE)
		 {
//			int k,r=SUCCESS;
			r=SUCCESS;
			pgrp = &group_element[index_cur];
			if(pgrp->nr_element)
			{
			 if( local_request(panel,network) )
			 {
					 if( pgrp->point_info.point.panel+1 != panel )
						 deleteremotepoint(pgrp->point_info.point,pgrp->point_info.point.network);
					 modify_grp=1;
			 }
			 else
			 {
				if( (panel_info1.panel_type == T3000 && panel_info1.version >= 221) ||
					(panel_info1.panel_type == MINI_T3000 && panel_info1.version >= 111) )
				{
					 i = sizeof(Str_grp_element);
//					 k = elemindex(group_element, index_cur);
					 if( DIAL_updategrp==1)
						 resume(DIAL);
					 while( DIAL_updategrp==1);
					 r=net_call(READGROUPELEMENT_T3000+100, DELETE_ELEMENT+(current_point<<8), (char *)pgrp, &i, panel, network,
											NETCALL_RETRY,TIMEOUT_NETCALL,NULL,NULL,NULL,0,pgrp->nr_element);
					 modify_grp_new = 1;
				}
				else
					modify_grp=1;
			 }
			 if(r==SUCCESS)
			 {
				hide_pointer();
				chbkg(pgrp->text_x_coordinate, pgrp->text_y_coordinate, 40, Cyan, Cyan);
				display_pointer();
				index_max--;
				index_max_group_element = index_max;
				pgrp->nr_element = 0;
			 }
      }
		 }
		 else
			 DisplayMessage(20, 7, 60, 11, NULL, " Unauthorized access! ", NULL, Black, NULL, 1200);
	 }
	 if(key.ch[0]==50 && group_element[index_cur].nr_element && !display) //Alt-M move
	 {
		if(screen_access==R_READ_WRITE)
		{
		 int index_old = index_cur;
		 int index_last = index_cur;
		 int l, c;
		 r=SUCCESS;
		 l = curline;
		 c = curcol;
		 hide_pointer();
		 chbkg(group_element[index_cur].text_x_coordinate, group_element[index_cur].text_y_coordinate, 40, Lightred, -1);
		 mgettext(group_element[index_cur].text_x_coordinate, group_element[index_cur].text_y_coordinate, group_element[index_cur].text_x_coordinate+39, group_element[index_cur].text_y_coordinate,bitmap);
//		 group_element[index_old].nr_element = 0;
		 display_pointer();

		 while(1)
		 {
//		 while(!bioskey_new(1));
			if(bioskey_new(1))
			{
			 key.i = bioskey_new(0);
			 hide_pointer();
			 if(key.ch[0]==ENTER )
			 {
					key.ch[0]=0;
					pgrp=&group_element[index_cur];
					if(index_cur!=index_last)
					{
					 chbkg(pgrp->text_x_coordinate, pgrp->text_y_coordinate, 40, Lightgray, -1);
					 index_cur=index_last;
					 curline = l;
					 curcol  = c;
					}
					pgrp=&group_element[index_cur];
					if( !local_request(panel,network) )
					{
						if( (panel_info1.panel_type == T3000 && panel_info1.version >= 221) ||
							(panel_info1.panel_type == MINI_T3000 && panel_info1.version >= 111) )
						{
							 while( DIAL_updategrp==1);
							 i = sizeof(Str_grp_element);
							 r=net_call(READGROUPELEMENT_T3000+100, DELETE_ELEMENT+(current_point<<8), (char *)&group_element[index_old], &i, panel, network,
										NETCALL_RETRY|NETCALL_NOTTIMEOUT,TIMEOUT_NETCALL,NULL,NULL,NULL,0,group_element[index_old].nr_element);
						}
					}
					if(r==SUCCESS)
					{
					 *pgrp=group_element[index_old];
//					group_element[index_old].nr_element = 0;

					 group_element[index_old].nr_element = 0;
					 pgrp->nr_element=index_cur+1;
					 pgrp->text_y_coordinate=curline;
					 pgrp->text_x_coordinate=(curcol-1)*40+1;
					 pgrp->graphic_y_coordinate=curline*16;
					 pgrp->graphic_x_coordinate=((curcol-1)*40+1)*8;

					 chbkg(pgrp->text_x_coordinate, pgrp->text_y_coordinate, 40, BOXCOLOR, -1);
					 modify_grp=1;

					 if( !local_request(panel,network) )
					 {
						if( (panel_info1.panel_type == T3000 && panel_info1.version >= 221) ||
							(panel_info1.panel_type == MINI_T3000 && panel_info1.version >= 111) )
						{
							 while( DIAL_updategrp==1);
								i = sizeof(Str_grp_element);
								r=net_call(READGROUPELEMENT_T3000+100, ADD_ELEMENT+(current_point<<8), (char *)pgrp, &i, panel, network,
											NETCALL_RETRY,TIMEOUT_NETCALL,NULL,NULL,NULL,0,pgrp->nr_element);
							 if(r==SUCCESS)
							 {
								modify_grp=0;
								modify_grp_new = 1;
							 }
						}
					 }
					 if(r!=SUCCESS)
					 {
						modify_grp=0;
						modify_grp_new = 1;
						chbkg((c-1)*40+1,l, 40, bkgnd, bkgnd);
						chbkg((c-1)*40+1,l, 40, BOXCOLOR, -1);
						pgrp->nr_element=0;
					 }
					}
					else
					{
					 pgrp=&group_element[index_old];
					 chbkg((c-1)*40+1,l, 40, bkgnd, bkgnd);
//					 l = curline;
//					 c = curcol;
					 mputtext(pgrp->text_x_coordinate,pgrp->text_y_coordinate,pgrp->text_x_coordinate+39,pgrp->text_y_coordinate, bitmap);
					 chbkg(pgrp->text_x_coordinate, pgrp->text_y_coordinate, 40, BOXCOLOR, -1);
					 modify_grp=0;
					 modify_grp_new = 1;
					 index_cur = index_old;
           curline =  pgrp->text_y_coordinate;
					}
					break;
			 }
			 if (key.ch[0] == '\t') //tab
			 {
/*
				 if(index_last==index_cur)
					 chbkg((curcol-1)*40+1,curline, 40,  bkgnd, bkgnd);
				 else
					 chbkg((curcol-1)*40+1,curline, 40, bkgnd, get_color(group_element+index_cur) );
				 page++;
				 int m=index_obj/(2*nrow);
				 if (index_obj%(2*nrow)) m++;
				 if(page>=m) page=0;
				 index_cur=page*2*nrow;
				 curline=2;
				 curcol=1;
//					mtextbackground(FONDCOLOR);
//					window(1,2,80,25);
				 mclrscr(1,2,80,25,FONDCOLOR);
//					window(1,1,80,25);
				 refresh_time = 2000;
				 pgrp = &group_element[index_cur];
				 for(i=index_cur;i<index_cur+2*nrow && i<index_obj;pgrp++,i++)
				 {
					 if(pgrp->nr_element)
						{
//						 print_des(pgrp,grp_workdata+i,panel);
						 print_des(pgrp,NULL,panel,network);
						}
				 }
				 refresh_time = refresh_time_init;

				 if(group_element[index_cur].nr_element)
					chbkg((curcol-1)*40+1,curline, 40, BOXCOLOR, get_color(group_element+index_cur));
				 else
				 {
					index_last=index_cur;
					mputtext((curcol-1)*40+1,curline,(curcol-1)*40+1+39,curline, bitmap);
				 }
*/
			 }

			 if(key.ch[0]==0)
			 {
				key.ch[0]=key.ch[1];
				if (key.ch[0]==DOWN || key.ch[0]==UP || first )  //dn, up
				{
				 if(index_last==index_cur)
					chbkg((curcol-1)*40+1,curline, 40,  bkgnd, bkgnd);
				 else
					chbkg((curcol-1)*40+1,curline, 40, bkgnd, get_color(group_element+index_cur));

				 if (key.ch[0]==DOWN)
				 {
					index_cur++;
					curline++;
				 }
				 else
				 {
					index_cur--;
					curline--;
				 }
				 if (index_cur>=(page+1)*2*nrow || index_cur>=index_obj)
				 {
					index_cur--;
					curline--;
				 }
				 if (index_cur<page*2*nrow)
				 {
					index_cur++;
					curline++;
				 }
				 if ((index_cur==page*2*nrow+nrow) && key.ch[0]==DOWN)
				 {
					curline=2;
					curcol=2;
				 }
				 if ((index_cur==page*2*nrow+nrow-1) && key.ch[0]==UP)
				 {
					curline=25;
					curcol=1;
				 }

				 if(group_element[index_cur].nr_element)
				 {
					chbkg((curcol-1)*40+1,curline, 40, BOXCOLOR, get_color(group_element+index_cur));
					mputtext((c-1)*40+1,l,(c-1)*40+1+39,l, bitmap);
				 }
				 else
				 {
					index_last  = index_cur;
					chbkg((c-1)*40+1,l, 40, bkgnd, bkgnd);
					l = curline;
					c = curcol;
					mputtext((curcol-1)*40+1,curline,(curcol-1)*40+1+39,curline, bitmap);
				 }
				}
				if (key.ch[0] == RIGHT || key.ch[0] == LEFT) //right, left
				{
				 if(index_last==index_cur)
					 chbkg((curcol-1)*40+1,curline, 40,  bkgnd, bkgnd);
				 else
					 chbkg((curcol-1)*40+1,curline, 40, bkgnd, -1);
				 if (curcol == 1)
				 {
						 curcol = 2;
						 index_cur += nrow;
						 if(index_cur>=index_obj)
						 {
							 curcol=1;
							 index_cur -= nrow;
						 }
				 }
				 else
				 {
						 curcol = 1;
						 index_cur -= nrow;
				 }
				 if(group_element[index_cur].nr_element)
				 {
					chbkg((curcol-1)*40+1,curline, 40, BOXCOLOR, get_color(group_element+index_cur));
					mputtext((c-1)*40+1,l,(c-1)*40+1+39,l, bitmap);
				 }
				 else
				 {
					index_last=index_cur;
					chbkg((c-1)*40+1,l, 40, bkgnd, bkgnd);
					l = curline;
					c = curcol;
					mputtext((curcol-1)*40+1,curline,(curcol-1)*40+1+39,curline, bitmap);
				 }
				}
				display_pointer();
			 }
			}
			else
			{
//			 int x,y;
			 if (mouse_motion(&x,&y))
			 for(i=2;i<=24;i++)
			 {
				int c=1;
				if(mouse_inside(1,i,40,i) || mouse_inside(41,i,80,i))
				{
				 if(mouse_inside(41,i,80,i)) c=2;
				 hide_pointer();
				 if(index_last==index_cur)
					 chbkg((curcol-1)*40+1,curline, 40,  bkgnd, bkgnd);
				 else
					 chbkg((curcol-1)*40+1,curline, 40, bkgnd, -1);
				 curline = i;
				 curcol=c;
				 index_cur=page*2*nrow+(curcol-1)*nrow+curline-1-1;

				 if(group_element[index_cur].nr_element)
				 {
					chbkg((curcol-1)*40+1,curline, 40, BOXCOLOR, get_color(group_element+index_cur));
					mputtext((c-1)*40+1,l,(c-1)*40+1+39,l, bitmap);
				 }
				 else
				 {
					index_last=index_cur;
					chbkg((c-1)*40+1,l, 40, bkgnd, bkgnd);
					l = curline;
					c = curcol;
					mputtext((curcol-1)*40+1,curline,(curcol-1)*40+1+39,curline, bitmap);
				 }
				 display_pointer();
				 modify_grp=1;
//			move_mouse((curcol-1)*40+1,curline);
				}
			 }
			}
		 }
		}
		else
		 DisplayMessage(20,7,60,11, NULL, " Unauthorized access! ", NULL, Black, NULL, 1200);
	 }

	 pgrp = &group_element[index_cur];
//	 pworkdata = &grp_workdata[index_cur];
		if(pgrp->nr_element && key.ch[0]==ENTER && !display)//Enter
		{
		 if(!pgrp->point_absent)
		 {
			if(pgrp->point_info.point.point_type-1!=PRG &&
				 pgrp->point_info.point.point_type-1!=AMON &&
				 pgrp->point_info.point.point_type-1!=GRP &&
				 pgrp->point_info.point.point_type-1!=WR &&
				 pgrp->point_info.point.point_type-1!=CON &&
				 pgrp->point_info.point.point_type-1!=AR)
			 key.ch[0]=INSERT;
			else
			 if(retpoint)
			 {
				if( check_access(pgrp->point_info.point.point_type-1, pgrp->point_info.point.number)!=R_NA )
				{
				 menu=0;
				 first=1;
				 key.ch[0]=27;  //esc
				 *retpoint=pgrp->point_info.point;
				 if( pgrp->point_info.description_label == DISPLAY_ICON_VALUE + 1 )
					esc = pgrp->point_info.point.point_type+100;
				 else
					esc = pgrp->point_info.point.point_type;
//				xcur_grp=group_element[index_cur].text_x_coordinate;
//				ycur_grp=group_element[index_cur].text_y_coordinate;
				 continue;
				}
			 }
		 }
		}

	 if(key.ch[0]==INSERT && pgrp->nr_element)
	 {
//				cell((curcol-1)*40+1,curline,pgrp,pworkdata,panel,1);
			if(!pgrp->point_absent)
			{
				cell((curcol-1)*40+1,curline,pgrp,NULL,panel,network,1);
				if(modify_grp)
				 if( !local_request(panel,network) )
					if( (panel_info1.panel_type == T3000 && panel_info1.version >= 221) ||
							(panel_info1.panel_type == MINI_T3000 && panel_info1.version >= 111) )
					{
//						 int k;
						 i = sizeof(Str_grp_element);
//						 k = elemindex(group_element, index_cur);
						 if( DIAL_updategrp==1)
							resume(DIAL);
						 while( DIAL_updategrp==1);
						 net_call(READGROUPELEMENT_T3000+100, UPDATE_ELEMENT+(current_point<<8), (char *)pgrp, &i, panel, network,
											NETCALL_RETRY,TIMEOUT_NETCALL,NULL,NULL,NULL,0,pgrp->nr_element);
						 modify_grp=0;
						 modify_grp_new = 1;
					}
			}
	 }

	 if (key.ch[0]==INSERT && !pgrp->nr_element && !display)
	 {                            //nu exista elementul
		 if(screen_access==R_READ_WRITE)
		 {
			char test,ptr[17];
			byte var_type,point_type;
			int onet,num_net,num_point,num_panel; //,r=SUCCESS;

			GWindow w((curcol-1)*40+1,(curline>22)?22:curline,(curcol-1)*40+40,(curline>22?22:curline)+3,NO_STACK,0);
			w.GWSet(NULL,BOXCOLOR,BOXTITLE);
			w.GShowWindow(0);
			w.GWPuts(1,4,"Point : ",BOXCOLOR,Black);
			w.GWPuts(1,12,"                ",Cyan,Black);
			chbkg((curcol-1)*40+15,(curline>22?22:curline)+2, 15, Cyan, Black);
			w.GWGoto(1,13);
			mgets(ptr,1,Cyan,White);
			w.GReleaseWindow();

			if (ispoint(ptr,&num_point,&var_type, &point_type, &num_panel, &num_net, network, panel, &k))
			{
				 onet = network;

				 if( local_request(panel,network) )
				 {
//					if ( num_net==network )
					if ( !k )
					 if( rs485port!=-1 && ipxport!=-1 )
					 {
						 num_net=(( class ConnectionData *)Routing_table[rs485port].ptr)->panel_info1.network;
						 network = num_net;
					 }
				 }

/*
				 if( (test=checkpointpresence(num_point,point_type,num_panel,num_net,panel,network))==0 )
						DisplayMessage(20,7,60,11, NULL, panelmis, NULL, Black, NULL, 2500);
				 if(test)
						x = checkmaxpoints(num_point,point_type,num_panel,num_net);
				 else
						x = 128;
*/
//  replaced the above code with next line
         test=1;
				 x = 256;
				 if(num_point <= x )
				 {
//					if ( num_net==network && !k ) num_net = 0xFFFF;
					if ( !k ) num_net = 0xFFFF;
					pgrp->point_info.point.putpoint(num_point-1,point_type+1,num_panel-1,num_net);
//					if(get_point_info(&pgrp->point_info, NULL, NULL, NULL, NULL, 2, network)==SUCCESS )
					if(test)
					{
						if( DIAL_updategrp==1)
						  resume(DIAL);
						while( DIAL_updategrp==1);
						if( (r=get_point_info(&pgrp->point_info, NULL, NULL, NULL, NULL, 2, num_net==0xFFFF?network:num_net))==SUCCESS )
						  modify_grp_new = 1;
					}
          if(r==SUCCESS)
					{
					 pgrp->nr_element=index_cur+1;
//					 if( num_panel == panel && num_net==0xFFFF )
					 if( num_panel == panel )
						pgrp->where_point = LOCAL_POINT;
					 else
						pgrp->where_point = LOCAL_NETWORK_POINT;
					 pgrp->text_y_coordinate=curline;
					 pgrp->text_x_coordinate=(curcol-1)*40+1;
					 pgrp->graphic_y_coordinate=curline*16;
					 pgrp->graphic_x_coordinate=((curcol-1)*40+1)*8;
					 pgrp->show_point=1;
					 pgrp->point_info.description_label=1;
					 pgrp->text_present = 1;
					 if( local_request(panel,network) )
					 {
//						if( num_panel!=panel || num_net!=0xFFFF)
						if( num_panel!=panel )
							updateremotepoint(pgrp->point_info.point,num_net);
						modify_grp=1;
					 }
					 else
					 {
						if( (panel_info1.panel_type == T3000 && panel_info1.version >= 221) ||
								(panel_info1.panel_type == MINI_T3000 && panel_info1.version >= 111) )
						{
//             int k;
						 i = sizeof(Str_grp_element);
//						 k = elemindex(group_element, index_cur);
						 if( DIAL_updategrp==1)
							resume(DIAL);
						 while( DIAL_updategrp==1);
						 r=net_call(READGROUPELEMENT_T3000+100, ADD_ELEMENT+(current_point<<8), (char *)pgrp, &i, panel, network,
											NETCALL_RETRY,TIMEOUT_NETCALL,NULL,NULL,NULL,0,pgrp->nr_element);
						 modify_grp_new = 1;
						}
						else
						 modify_grp=1;
					 }
					 if (refresh_time < 15) refresh_time = 15;
//					print_des(pgrp,pworkdata,panel);
					 if(r==SUCCESS)
					 {
						 print_des(pgrp,NULL,panel,network);
					 }
					 refresh_time = refresh_time_init;
//					 modify_grp = 1;
					}
				 }
				 else
						DisplayMessage(20,7,60,11, NULL, pointins, NULL, Black, NULL, 2000);
				 network=onet;
			}
		 }
		 else
			 DisplayMessage(20,7,60,11, NULL, " Unauthorized access! ", NULL, Black, NULL, 1200);
		}
	}
	if (key.ch[0] == '\t') //tab
	{
					page++;
					int m=index_obj/(2*nrow);
					if (index_obj%(2*nrow)) m++;
					if(page>=m) page=0;
					{
					 index_cur=page*2*nrow;
					 curline=2;
					 curcol=1;
					}
					mclrscr(1,2,80,25,FONDCOLOR);
					first=1; last_mouse=0;
					refresh_time = 2000;
					pgrp = &group_element[index_cur];
					for(i=index_cur;i<index_cur+2*nrow && i<index_obj;pgrp++,i++)
					{
					if(pgrp->nr_element)
						{
//						 print_des(pgrp, grp_workdata+i, panel);
						 print_des(pgrp, NULL, panel, network);
						}
					}
					refresh_time = refresh_time_init;
					if(ycur_grp)
					{
					 index_cur=page*2*nrow+(xcur_grp-1)*nrow+ycur_grp-2;
					 curline=ycur_grp;
					 curcol=xcur_grp;
					 ycur_grp = 0;
					}
	}

	if (key.ch[0] == PGDN) //Pgdn
	{
	 esc = PGDN;
	 key.ch[0]=27;
	 first=1;
	 continue ;
	}
	if (key.ch[0] == PGUP) //PgUP
  {
	 esc = PGUP;
	 key.ch[0]=27;
	 first=1;
	 continue ;
	}
	if (key.ch[0]==DOWN || key.ch[0]==UP || first )  //dn, up
	{
	 first = 0;
	 last_mouse=0;
	 chbkg((curcol-1)*40+1,curline, 40, bkgnd, -1);
	 if (key.ch[0]==DOWN)
	 {
		 if(menu==1)
			menu=0;
		 else
			{
			 index_cur++;
			 curline++;
			}
	 }
	 else
		if(key.ch[0]==UP)
		{
			 index_cur--;
			 curline--;
		}
	 if (index_cur>=(page+1)*2*nrow || index_cur>=index_obj)
	 {
			 index_cur--;
			 curline--;
	 }
	 if (index_cur<page*2*nrow)
	 {
			 if(menu==0)
			 {
				index_cur++;
				curline++;
				menu=1;
			 }
	 }
	 if ((index_cur==page*2*nrow+nrow) && key.ch[0]==DOWN)
	 {
			 curline=2;
			 curcol=2;
	 }
	 if ((index_cur==page*2*nrow+nrow-1) && key.ch[0]==UP)
	 {
			 curline=25;
			 curcol=1;
	 }
	 if (!menu)
		 chbkg((curcol-1)*40+1,curline, 40, BOXCOLOR, get_color(group_element+index_cur));

	}
	if (key.ch[0] == RIGHT || key.ch[0] == LEFT) //right, left
	{
				 chbkg((curcol-1)*40+1,curline, 40, bkgnd, -1);
				 if (curcol == 1)
						{
						 curcol = 2;
						 index_cur += nrow;
						 if(index_cur>=index_obj)
							{
							 curcol=1;
							 index_cur -= nrow;
							}
						}
				 else
						{
						 curcol = 1;
						 index_cur -= nrow;
						}
				 chbkg((curcol-1)*40+1,curline, 40, BOXCOLOR, get_color(group_element+index_cur));
	}
	if (menu && !display)
	{
			int qt=0;
			grp_menu->GShowMenuBar(graphic_grp_message);
			hide_pointer();
			move_mouse(4,1);
			display_pointer();
			do {
			 int man=grp_menu->GReturn();
			 switch (man) {
/*
				 case 0:
					{
					 memset(group_element,'\0',sizeof(Str_grp_element)*(MAX_ELEM+1));
					 for(int i=0; i<ptr_panel->control_group_elements[current_point].nr_elements;i++)
						 memcpy(&group_element[ptr_panel->control_group_elements[current_point].ptrgrp[i].nr_element-1],ptr_panel->control_group_elements[current_point].ptrgrp+i,sizeof(Str_grp_element));
					 page = -1;
					 first=1; last_mouse=0;
					 key.ch[0]='\t';
					 menu=0;
					 qt=1;
					}
					 break;
				 case 1:
					 if(local_panel)
						 send_grp(1,index_obj, current_point, group_element, curline, curcol);
					 else
						 send_grp(0,index_obj, current_point, group_element, curline, curcol);

					 menu=0;
					 qt=1;
					 break;
*/
				 case 1:
					 itoa( refresh_time_init/18, bitmap, 10);
					 ReadWindow(25, 8, 50, 11, Lightgray, Darkgray, Black,
							 Cyan, White, "Refresh time : ", bitmap, 3);
					 refresh_time_init = atoi(bitmap)*18;
					 break;
				 case  2:
				 case -2:
					 menu=0;
					 first=1;
					 qt=1;
					 key.ch[0]=27;  //esc
					 break;
				 case DOWN:
					 qt=1;
					 first=1;
					 key.ch[0]=DOWN;
					 break;
				 case -3:
					 qt=1;
					 menu=0;
					 first=0;
					 display_pointer();
					 break;
				 case -4:
					 qt=1;
/*
						Panel_info1 panel_info;
						if(local_request(panel))
						{
						 if( GAlarm )
							 showpoints(M3+3, Panel_Info1.panel_type, panel, network);
						}
						else
						{
						 if( gAlarm )
							if( net_call(COMMAND_50, PANEL_INFO1_COMMAND, (char*)&panel_info, 0, panel, network) == RS232_SUCCESS )
							{
								showpoints(M3+3, panel_info.panel_type, panel, network);
							}
						}
*/
						break;
			 }
			} while(!qt );
			grp_menu->ReleaseMBar();
	}
	}

	mouse_status(stat);
	if(stat.rightButton)
	{
	 first = 1;
	 key.ch[0]=27;
	 continue;
	}
	if(mouse_inside(75, 1, 80, 1 ))
	 if(stat.leftButton)
	 {
		Panel_info1 panel_info;
		if(local_request(panel,network))
		{
		 if( GAlarm )
				 showpoints(M3+3, Panel_Info1.panel_type, panel, network);
		}
		else
		{
		 if( gAlarm )
		 {
				if( DIAL_updategrp==1)
					resume(DIAL);
				while(DIAL_updategrp==1);
				if( net_call(COMMAND_50, PANEL_INFO1_COMMAND, (char*)&panel_info, 0, panel, network) == RS232_SUCCESS )
				{
					showpoints(M3+3, panel_info.panel_type, panel, network);
				}
		 }
		}
	 }

//	int x,y;
	if (mouse_motion(&x,&y))
	if(mouse_inside(1, 1, 79, 1 ) &&  key.ch[0]!=27 && page!=-1 && !display)
	{
		 menu=1; first=1;
		 key.ch[0]=0;
	}
	else
	for(i=2;i<=24;i++)
	{
	 int c=1;
	 if(mouse_inside(1,i,40,i) || mouse_inside(41,i,80,i))
	 {
			if(mouse_inside(41,i,80,i)) c=2;
			hide_pointer();
			chbkg((curcol-1)*40+1,curline, 40, bkgnd, -1);
			curline = i;
			curcol=c;
			index_cur=page*2*nrow+(curcol-1)*nrow+curline-1-1;
			chbkg((curcol-1)*40+1,curline, 40, BOXCOLOR, get_color(group_element+index_cur));
			display_pointer();
//			move_mouse((curcol-1)*40+1,curline);
			break;
	 }
	}

	if(!refresh_time)
	{
	 cont = 1;
	 if(modify_grp)
	 {
		if(!display)
		{
		 if( local_request(panel,network) )
			error_communication = send_grp(1,index_obj, current_point, group_element, curline, curcol);
		 else
		 {
			if( DIAL_updategrp==1)
					resume(DIAL);
			while(DIAL_updategrp==1);
			error_communication = send_grp(0,index_obj, current_point, group_element, curline, curcol,panel,network);
      modify_grp_new=1;
		 }
		}
	 }
	 if( local_request(panel,network) )
	 {
		if(local_panel_old == local_panel)
		 update_value_grp_elem(ptr_panel->control_group_elements[current_point].ptrgrp,ptr_panel->control_group_elements[current_point].nr_elements);
	 }
	 else
	 {
		if( !DIAL_updategrp )
		{
			current_point_GRP = current_point;
			panel_GRP = panel;
			network_GRP = network;
			DIAL_updategrp=1;
			DIAL_action=1;
			resume(DIAL);
			cont = 0;
		}
		else
		{
		 if( DIAL_updategrp!=1 )
		 {
			if( DIAL_updategrp==2 ) //OK
			{
			 if( !modify_grp_new )
			 {
				Str_grp_element *buf;
				buf = group_element_temp;
				memset(group_element,0,MAX_ELEM*sizeof(Str_grp_element));
				index_max=update_length/sizeof(Str_grp_element);
				index_max_group_element=index_max;
				pgrp = buf;
				for(i=0; i<index_max;pgrp++,i++)
				{
				 group_element[pgrp->nr_element-1]=*pgrp;
				}
				cont = 1;
			 }
			 else
			 {
				modify_grp_new = 0;
			  cont = 0;
			 }
			}
			else                    //Error
			 cont = 2;
      DIAL_updategrp=0;
/*
			Str_grp_element *buf;
			buf = group_element_temp;
			Delay(100);
			i=0;
			if((error_communication=net_call(19, current_point, (char *)buf, &i, panel, network,NETCALL_NOTTIMEOUT))==SUCCESS)
			{
			 memset(group_element,0,MAX_ELEM*sizeof(Str_grp_element));
			 index_max=i/sizeof(Str_grp_element);
			 index_max_group_element=index_max;
			 pgrp = buf;
			 for(i=0; i<index_max;pgrp++,i++)
			 {
				group_element[pgrp->nr_element-1]=*pgrp;
			 }
			}
*/
		 }
		 else
			cont = 0;
		}
	 }
//   refresh_time = 2000;
	 if(cont==1)
	 {
		pgrp=&group_element[page*2*nrow];
		for(i=page*2*nrow;i<page*2*nrow+2*nrow && i<index_obj;pgrp++,i++)
		{
		 if(pgrp->nr_element)
		 {
			 print_des(pgrp,NULL,panel,network);
		 }
		}
	 }
	 if(cont)
	 {
		if( refresh_time_init )	refresh_time = refresh_time_init;
		else
		{
		 if(rtime==4)
			 rtime = 5;
		 else
			 rtime = 4;
		 refresh_time = rtime;
		}
	 }
	}
/////////
	if( !DIAL_updategrp )
	{
	 if( timestart+timesec1970 > lastreadopenscreen+15 )
	 {
		k=1;
		lastreadopenscreen = timestart+timesec1970;
		if( local_request(panel,network) )
		 openscreen = localopenscreen;
		else
		{
		 if( (panel_info1.panel_type == T3000 && panel_info1.version >= 221) ||
			 (panel_info1.panel_type == MINI_T3000 && panel_info1.version >= 111) )
		 {
			i = sizeof(Point_Net);
			if( net_call(COMMAND_50, OPENSCREEN_COMMAND, (char *)&openscreen, &i, panel, network, BACnetConfirmedRequestPDU|NETCALL_NOTTIMEOUT)!=SUCCESS )
			 k=0;
		 }
		}
		if( k && (openscreen.point_type &&	!(openscreen==current_opened_grp)) )
		if( retpoint )
		{
		 if( check_access(openscreen.point_type-1, openscreen.number)!=R_NA )
		 {
				 menu=0;
				 first=1;
				 key.ch[0]=27;  //esc
				 *retpoint=openscreen;
				 esc = openscreen.point_type;
				 continue;
		 }
		}
	 }
////////////
	 print_alarm_word();
	}
 }
}
asm pop es;
}
}

int grp_proc(int current_point, byte panel, int network, int call_type, GGrid *pgrid = NULL)
{
 char buf[17],*p;
 uint i;
 int r,ctype, loc_panel;
 char point_type, var_type;
 int num_net, refresh_time_old,num_point,num_panel;
 Point_Net point;
 Control_group_point block1;
 int current_panel, current_net;
 int old_mode;

		old_mode	= mode_text;
		ctype = call_type;
		loc_panel = local_panel;
		num_panel = panel;
		num_point = current_point;
		current_point--;
		current_panel = panel;
		current_net   = network;
		while(1)
		{
//		 call_type=0;
		 test_tiff = 0;
		 while(1)
		 {
			point.setzero();
			r=0;
//			if( (!local_panel && num_panel==Station_NUM && num_panel!=station_num ) || (local_panel && num_panel==Station_NUM) )
//			if( local_request(num_panel) )
			if( current_panel==Station_NUM && localnetwork(current_net) )
			{
				memmove(&block1,&ptr_panel->control_groups[current_point],sizeof(Control_group_point));
				local_panel=1;
			}
			else
			{
				Delay(150);
				r=net_call(20, ((GRP+1)<<8)+ current_point, (char *)&block1, 0 ,current_panel, current_net,NETCALL_RETRY);
				if (r) r=1;
				local_panel=0;
			}
			xcur_grp = block1.xcur_grp;
			ycur_grp = block1.ycur_grp;

			current_opened_grp.putpoint(current_point, GRP+1, current_panel-1, current_net);
			if (!r)
			{
				refresh_time_old = refresh_time_init;
				refresh_time_init = block1.update_time*18;
//				openscreen=current_opened_grp;
				r=fnc_group(&block1,pgrid,current_point,call_type,current_panel,current_net,0,&point);
				if(block1.update_time != refresh_time_init/18)
				{
					block1.update_time = refresh_time_init/18;
					if(pgrid)
						pgrid->obj.grp->block[current_point].update_time = block1.update_time;
				}
				block1.xcur_grp=xcur_grp;
				block1.ycur_grp=ycur_grp;
				block1.state=0;
//				if( (!local_panel && num_panel==Station_NUM && num_panel!=station_num ) || (local_panel && num_panel==Station_NUM) )
				if( current_panel==Station_NUM && localnetwork(current_net) )
				{
					memmove(&ptr_panel->control_groups[current_point],&block1,sizeof(Control_group_point));
				}
				else
				{
					Delay(100);
					i = countlength(20, ((GRP+1)<<8)+ current_point );
					net_call(20+100, ((GRP+1)<<8)+ current_point, (char *)&block1, &i ,current_panel, current_net,BACnetUnconfirmedRequestPDU);   //NETCALL_RETRY
          delay(1000);
				}
				refresh_time_init = refresh_time_old;
			}
			local_panel=loc_panel;
			if (!dontch) dontch = 1;

			if(r==1)
			{
			 if(ind_nested_grp)
			 {
				ind_nested_grp--;
//				if(!ind_nested_grp) dontch=-1;
				pointtotext(buf,&nested_grp[ind_nested_grp]);
				p=ispoint(rtrim(buf),&num_point,&var_type, &point_type, &num_panel, &num_net, network);
				current_point = num_point-1;
				current_panel = num_panel;
				current_net   = num_net;
				continue;
			 }
			 if (prg_active) return ESC;
			 break;
			}
			if(r-1==ALARMS)
			{
			  alarm_routine();
			  continue;
			}
			if(r-1==PRG || r-1==AMON || r-1 == GRP || r-1 == WR || r-1 == AR || r-1 == CON )
			{
				pointtotext(buf,&point);
				p=ispoint(rtrim(buf),&num_point,&var_type, &point_type, &num_panel, &num_net, network);
			}
			if(r-1==PRG)
			{
			 program_routine(num_point, point_type, num_panel, num_net);
			 continue;
			}
			if(r-1==AMON)
			{
			 amon_routine(num_point,num_panel,num_net,INDIVIDUAL,0,NULL);
			 continue;
			}
			if(r-1==WR)
			{
			 weekly_routine(num_point,num_panel,num_net,INDIVIDUAL);
			 continue;
			}
			if(r-1==AR)
			{
			 annual_routine(num_point,num_panel,num_net,INDIVIDUAL);
			 continue;
			}
			if(r-1==CON)
			{
			 icommand(buf, 0, num_panel, num_net);
			 continue;
			}
			if(r-1==GRP)
			{
			 if(ind_nested_grp < MAX_NEST_GRP-1)
			 {
				nested_grp[ind_nested_grp++]=current_opened_grp;
				current_point = num_point-1;
				current_panel = num_panel;
				current_net   = num_net;
			 }
			 continue;
			}
			if(r > 100+OUT)
			{
			 int n=cod_command[r-101];
			 ptr_panel->Select(n);
			 continue;
			}
			call_type = 1;
			if(r==PGDN)
				if(++current_point>=16) current_point=0;  //MAX_GRPS
			if(r==PGUP)
				if(current_point--==0) current_point=15;     //(char)(MAX_GRPS-1);
		 }
		 if(r==1)
		 {
			if(old_mode == MODE_TEXT)
			{
				lat_char_n = 1;
				lung_char_n = 1;
				Green=LIGHTBLUE;                 //2
				Green1=WHITE; 						 //5
				Blue1=DARKGRAY;                 //6
				Darkgray=BROWN;           //8
				Lightblue=GREEN;         //9
				White=MAGENTA;                 //15
				fond_color=TEXT_FOND_COLOR;
				if(mode_text == MODE_GRAPHIC)
				{
				 mode_text = MODE_TEXT;
				 hide_pointer();
				 cleardevice();
				 restorecrtmode();
				 changechar();
				 setregister(1);
				 asm {
					mov ax,21h
					int 33h
				 }
				 setmousetext();
				}
				clear_color(1, 80, 1, 25, lin_text, fond_color, Black);

				move_mouse(30,20);
				display_pointer();
			}
			else
			{
			 hide_pointer();
			 if(mode_text)
			 {
				mode_text = MODE_GRAPHIC;
				restorechar();
				setgraphmode(getgraphmode());
			 }
			 msettextstyle(DEFAULT_FONT, 0, 1);
			 Green=GREEN;                 //2
			 White=WHITE; 						 //5
			 Darkgray=DARKGRAY;                 //6
			 Brown=BROWN;           //8
			 Lightblue=LIGHTBLUE;         //9
			 Magenta=MAGENTA;                 //15
			 fond_color = White;
			 setcolor(Darkgray);
			 setfillstyle(SOLID_FILL,fond_color);
			 bar(0,0,maxx,maxy);
			 prectangle(2,2,maxx-2,maxy-2,Black);
			 setcolor(White);
			 prectangle(1,1,maxx-1,maxy-1,White);
			 setcolor(Black);
			 mouse_installed();
			 asm {
					 mov ax,21h
					 int 33h
			 }
			 display_pointer();
			}

//			if(!display)
			{
//			 G.GShowMenuBar(message);


			 if(ctype!=INDIVIDUAL)
			 {
			 int old_rec=pgrid->w_record;
			 int old_field=pgrid->w_field;
//				pgrid->w_nfields = 0;
//				pgrid->w_field = 1;
				pgrid->t_fields[pgrid->w_lfield-1]=1;
//				pgrid->RestoreArea();
				pgrid->on_screen=0;
				if (mode_text)
					 pgrid->save=0;
				pgrid->GShowGrid();
				if (mode_text)
					 pgrid->save=1;
				pgrid->GGHideCur(Black);
				pgrid->w_record = old_rec;
				pgrid->w_field = old_field;
				pgrid->GGShowCur(Black);
				}
				else
				  G.GShowMenuBar(message);
			 }
			dontch = 0;
			break;
		 }
		}
      return 0;
}


int Control_group_block::Read(int field, char key)
{
 char buf[50],l;
// Point_Net openscreen;

	if(key==INSERT)
	{
	 if(check_access(GRP, current_point)!=R_NA)
	 {
//		openscreen.setzero();
		return(grp_proc(current_point+1, panel, network, 0, pgrid));
	 }
	}
	else
	{
	 switch (field) {
		case GRP_NUM:
						break;
		case GRP_FULL_LABEL:
					 getalpha(field, (block+current_point)->description, L_GRP_FULL_LABEL);
					 break;
		case GRP_LABEL:
					 getalpha(field, (block+current_point)->label, L_GRP_LABEL);
					 break;
		case GRP_PICFILE:
					 getalpha(field, (block+current_point)->picture_file, L_GRP_PICFILE);
					 break;
		case GRP_MODE:
						l=(block+current_point)->mode;
						if (l==1)
							 {
							 strcpy(buf,texts);
							 l=0;
							 }
						else
							{
							 strcpy(buf,graphic);
							 l=1;
							}
					 (block+current_point)->mode=l;
					 PutAlpha(field, buf);
					 break;
		case GRP_UPDATE:
					 int v;
					 v=(int)(block+current_point)->update_time;
					 readint(field, &v,  L_GRP_UPDATE, NULL, 2, 0, 255);
					 (block+current_point)->update_time = (byte)v;
					 break;
			}
	 pgrid->GGPutField(field,Lightgray,Black);
    pgrid->modify = TRUE;
	}
}


int Control_group_block::GetRec(void)
{
	int i;

	if (current_point+1 > number_of_points) return(FX_EOF);

	memset(&line_buf,'\0',sizeof(struct GRP_LineBuf));

	for(i=0; i<fields_number; i++)
		{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
		}
	return (FX_SUCCESS);
}

int Control_group_block::GetField(int field, char *buf)
{
	int l;

	l=0;
	switch (field) {
		case GRP_NUM:
				 nr_point(buf);
				 break;
		case GRP_FULL_LABEL:
						memcpy(buf , lalign((block+current_point)->description,L_GRP_FULL_LABEL),L_GRP_FULL_LABEL);
						l=L_GRP_FULL_LABEL;
				 break;
		case GRP_MODE:
						if ((block+current_point)->mode==0)
							 strcpy(buf,(char *)texts);
						else
							 strcpy(buf,(char *)graphic);
						l=L_GRP_MODE;
				 break;
		case GRP_LABEL:
						 char *p;
						 p=lalign((block+current_point)->label,L_GRP_LABEL);
						 memcpy(buf , p,L_GRP_LABEL);
						 l=L_GRP_LABEL;
				 break;
		case GRP_PICFILE:
						 p=lalign((block+current_point)->picture_file,L_GRP_PICFILE);
						 memcpy(buf , p,L_GRP_PICFILE);
						 l=L_GRP_PICFILE;
				 break;
		case GRP_UPDATE:
				int v;
				v=(int)(block+current_point)->update_time;
				readint(field, &v,  L_GRP_UPDATE, buf, 0);
				break;
		}

 return l;
}


char huge *Heap_grp_alloc(int bytes)
{
 if (bytes==0)
	 return NULL;
 if( ind_heap_grp+bytes >= MAX_HEAP_GRP )
	 return NULL;
 ind_heap_grp += bytes;
 return (&heap_grp[ind_heap_grp - bytes]);
}

int Heap_grp_dealloc(char huge **old, int bytes_old)
{
 if (*old)
 {
 char huge *p,*q;
 int l;
 p=*old+bytes_old;
 l=(&heap_grp[ind_heap_grp]-*old)-bytes_old;
 movedata(FP_SEG(p),FP_OFF(p) ,FP_SEG(*old),FP_OFF(*old), l);

 Control_group_elements *cgrp;
	 cgrp = ptr_panel->control_group_elements;
	 for (int i=0;i<MAX_GRPS; cgrp++, i++)
		if (cgrp->ptrgrp > *old)
			 cgrp->ptrgrp -= bytes_old/sizeof(Str_grp_element);
	 ind_heap_grp -= bytes_old;
 *old=NULL;
 }
}

int Heap_grp_resizedown(char huge **old, int width, int bytes)
{
 if (*old)
 {
	char huge *p,*q;
	int l;
	p=*old+width;
	movedata(FP_SEG(p),FP_OFF(p) ,FP_SEG(*old),FP_OFF(*old), bytes);

	Control_group_elements *cgrp;
	 cgrp = ptr_panel->control_group_elements;
	 for (int i=0;i<MAX_GRPS; cgrp++, i++)
		if (cgrp->ptrgrp > *old)
			 cgrp->ptrgrp -= width/sizeof(Str_grp_element);
	 ind_heap_grp -= width;
 }
}

int Heap_grp_resizeup(char huge **old, int bytes)
{
 if (bytes==0)
	 return 0;
 if( ind_heap_grp+bytes >= MAX_HEAP_GRP )
	 return 0;
 Control_group_elements *cgrp;
 cgrp = ptr_panel->control_group_elements;
 for (int i=0;i<MAX_GRPS; cgrp++, i++)
		if (cgrp->ptrgrp >= *old)
			 cgrp->ptrgrp += bytes/sizeof(Str_grp_element);
 ind_heap_grp += bytes;
 return 1;
}

uint cell(uint hx, uint hy, Str_grp_element *group_element, Str_grp_work_data *grp_workdata, byte panel, int network, int print, byte put)
{
 uint nrfiles, nrdirectories;
 byte p_type;
 int lat,lung,height;
 char avalue[17];
 avalue[0] = 0;
 if (group_element->point_info.description_label==7)
 {
	return  0;
 }

 if( DIAL_updategrp==1 )
		 resume(DIAL);

 p_type = group_element->point_info.point.point_type;
 if(p_type == PRG+1 || p_type == GRP+1 || p_type == AMON+1 || p_type == WR+1 || p_type == AR+1)
 {
	 type_dis = 0;
	 refresh_time = refresh_time_init;
 }
 else
	 type_dis = 1;

 hide_pointer();
 if(mode_text)
 {
	lat=1;
	lung=1;
 }
 else
 {
	lat=textwidth(" ");
	height=textheight("H");
	lung=height+2*LINE_SPACE;
	if(grp_workdata->ptr_save_bkgnd)
	{
	 if(put)
		 mputimage(group_element->graphic_x_coordinate,group_element->graphic_y_coordinate,grp_workdata->ptr_save_bkgnd, COPY_PUT);
//	 mfarfree((HANDLE)FP_SEG(group_element->ptr_save_bkgnd));
	 mfarfree(grp_workdata->ptr_save_bkgnd);
	 grp_workdata->ptr_save_bkgnd = NULL;
	}
	if(group_element->icon_present)
	{
	 if( grp_workdata->icon )
		 if( grp_workdata->icon->image_under )
		 {
			if(put)
			 mputimage(group_element->xicon, group_element->yicon, grp_workdata->icon->image_under, COPY_PUT);
//	   mfarfree((HANDLE)FP_SEG(group_element->icon->image_under));
			mfarfree(grp_workdata->icon->image_under);
			grp_workdata->icon->image_under = NULL;
		 }
	}
 }

 int num_net,last_cur,num_panel,num_point;
 int last_m=0;
 byte var_type,point_type;
// char point_name[12];
// pointtotext(point_name,&group_element->point_info.point_name,STANDARD);
 char *label; //=islabel(point_name,&num_point,&var_type,&point_type,&num_panel);
 char *des;
 des = NULL;
// if((local_panel &&  panel==Station_NUM) || (!local_panel &&  panel==Station_NUM && panel!=station_num) )
 if( local_request(panel,network) )
 {
	get_point_info(&group_element->point_info, &des, &label,&ontext,&offtext,0,network);
 }
 else
 {
	if( !group_element->point_info.digital_analog )
	{
	 num_point=dig_range_array[group_element->point_info.units].value % 2;
	 ontext= &dig_range_array[group_element->point_info.units].dunits[!num_point][0];
	 offtext= &(dig_range_array[group_element->point_info.units].dunits[num_point][0]);
	}
	pointtotext(avalue,&group_element->point_info.point);
	label=ispoint(rtrim(avalue),&num_point,&var_type, &point_type, &num_panel, &num_net, network, panel);
	if(Des)
	{
	 if(point_type!=CON && point_type!=TBL)
	 des = Des->look_descriptor(num_panel,point_type,num_point);
	}
 }
// get_point_info(&group_element->point_info, &des, &label,&ontext,&offtext);

 int lx,ly,rx,ry;
			if((hx+40*lat) < maxx+1)
			 {
				lx = hx;
				rx = hx+40*lat;
			 }
			else
			 {
				lx = maxx-40*lat;
				rx = maxx;
			 }
			if((hy+(type_dis?8:6)*(lung)) < (mode_text?25:maxy))
			 {
				ly = hy;
				ry = hy+(type_dis?8:6)*(lung);
			 }
			 else
			 {
				ly = (mode_text?25:maxy)-((type_dis?8:6)*(lung));
				ry = (mode_text?25:maxy);
			 }
			if(mode_text && rx==81)
				{rx=80; lx=40;}

 GWDialog D(lx,ly,rx,ry,NO_STACK,0,SMALL_FONT,5,1);

 D.GWSet(NULL,BOXCOLOR,BOXTITLE);

 D.save=2;
 D.GShowWindow(DIALOG);

 hide_pointer();
 if(mode_text)
 {
//	 moutchar(hx,hy+2,'У',BOXCOLOR,Black);

 lin_hor[39]=0;
 mxyputs(lx+1,ly+2,lin_hor,BOXCOLOR,Black);
 lin_hor[39]=lin_hor[0];

// moutchar(hx+39,hy+2,'Д',BOXCOLOR,Black);
 }
 else
 {
	setcolor(Lightcyan);
	moveto(lx + 6, ly + 3*lung_char_n);
	lineto(rx - 6, ly + 3*lung_char_n);
 }

 D.select=0;
 pointtotext(avalue,&group_element->point_info.point);
 D.GWPuts(0,1,avalue,BOXCOLOR,Black);
 D.GWPuts(0,10,label,BOXCOLOR,White);
 if(des)
	D.GWPuts(0,19, des,BOXCOLOR,White);

// if(mode_text)
//	mtextcolor(Black);

 D.GWPuts(2,1,value_text,BOXCOLOR,Black);
 if(group_element->point_info.digital_analog)
 {
		if(group_element->point_info.units == time_unit)
		 intervaltotext( avalue, group_element->point_info.point_value / 1000L , 0 , 0);
		else
		 longtoa(group_element->point_info.point_value, 6, 2, avalue);
 }
 else
 {
	 if(group_element->point_info.point_value)
	 {
		 if(ontext)
			 strcpy(avalue, ontext);
	 }
	 else
	 {
		 if(offtext)
			 strcpy(avalue, offtext);
	 }		 
 }
 D.GWPuts(2,13,strupr(avalue),BOXCOLOR,Black);
 if (group_element->point_info.auto_manual==AUTO)
		D.GWPuts(2,30,strupr(autom),BOXCOLOR,Black);
 else
		D.GWPuts(2,30,strupr(man),BOXCOLOR,Black);
 if(type_dis)
 {
	D.GWPuts(3,1,high_limit,BOXCOLOR,Black);
	D.GWPuts(4,1,low_limit,BOXCOLOR,Black);
	D.GWPuts(4,22,onhigh_text,BOXCOLOR,group_element->on_high_color);
	D.GWPuts(5,22,offlow_text,BOXCOLOR,group_element->off_low_color);

	ftoa(group_element->high_limit, 6, 2, avalue);
	D.GWPuts(3,13,avalue,BOXCOLOR,Black);
	ftoa(group_element->low_limit, 6, 2, avalue);
	D.GWPuts(4,13,avalue,BOXCOLOR,Black);
//	D.GWPuts(6,13,viz_point_text,BOXCOLOR,Black);
//  D.GWPuts(6,22,load_text,BOXCOLOR,Black);
 }
 D.GWPuts(type_dis?5:3,1,display_text,BOXCOLOR,Black);
 D.GWPuts(type_dis?3:3,22,color_text,BOXCOLOR,group_element->normal_color);

// D.GWPuts(6,1,info_file_text);
// D.GWPuts(6,1,viz_inviz_text,BOXCOLOR,Black);

//// D.GWPuts(2,1,color_text);
/// D.GWPuts(3,1,onhigh_text);
/// D.GWPuts(4,1,offlow_text);
/// D.GWPuts(5,1,show_point_text);
// if(mode_text)
//	 mtextcolor(Black);
/// D.GWPuts(2,18,text_text);

///					 pthis->GDGets(buf,pthis->w_record,pthis->t_fields[field-1],GetFldSize(field),Black,White);
///							 *pf=atof(buf);


//	if(mode_text)
//		mtextcolor(group_element->normal_color);
//	else
//		setcolor(group_element->normal_color);


//	for(int i=0;i<3;i++)
//	 mputch('л');
//	if(mode_text)
//		mtextcolor(group_element->on_high_color);
//	else
//		setcolor(group_element->on_high_color);

//	if(mode_text)
//		mtextcolor(group_element->off_low_color);
//	else
//		setcolor(group_element->off_low_color);


//	if ( group_element->show_point)
//		D.GWPuts(5,14,Yes);
//	D.GWPuts(2,29,&text_size[group_element->text_size][0]);
//	if (mode_text)
//		mtextcolor(Black);
//	else
//		setcolor(Black);

	D.GWPuts(type_dis?5:3,13,d_text[group_element->point_info.description_label],BOXCOLOR,Black);

// Border(hx+13,hy+2,hx+13,hy+9,Lightgray,Lightgray);
// Border(hx+17,hy+3,hx+17,hy+9,Cyan,Lightgray);

 if(type_dis)
 {
	D.GDDef_object(pvalue,13,2,15,BOXCOLOR,Black);
	D.GDDef_object(phighlimit,13,3,6,BOXCOLOR,Black);
	D.GDDef_object(plowlimit,13,4,6,BOXCOLOR,Black);
	D.GDDef_object(pdisplay,13,5,8,BOXCOLOR,Black);
//	D.GDDef_object(pinfofile,13,6,5,BOXCOLOR,Black);
	D.GDDef_object(pauto,30,2,4,BOXCOLOR,Black);
	D.GDDef_object(pcolor,22,3,14,BOXCOLOR,Black);
	D.GDDef_object(ponhigh,22,4,14,BOXCOLOR,Black);
	D.GDDef_object(pofflow,22,5,14,BOXCOLOR,Black);
//	D.GDDef_object(pload,22,6,4,BOXCOLOR,Black);
 }
 else
 {
	D.GDDef_object(pvalue,13,2,15,BOXCOLOR,Black);
	D.GDDef_object(pdisplay,13,3,8,BOXCOLOR,Black);
	D.GDDef_object(pauto,30,2,4,BOXCOLOR,Black);
	D.GDDef_object(pcolor,22,3,14,BOXCOLOR,Black);
 }
// D.GDDef_object(pshowpoint,14,5,3,Lightgray,Black);
// D.GDDef_object(ptextsize,29,2,6,Lightgray,Black);

 D.index_cur=0;

 MouseStatus stat;
	union key key;
key.i=0;
int cur=2;
D.updown=0;
hide_pointer();
chbkg(D.objects[D.index_cur]->box.top.x,D.objects[D.index_cur]->box.top.y, D.objects[D.index_cur]->width*lat, FONDCOLOR, Black, 127,height+2);
while (1)
{
 if (bioskey_new(1) || D.first)
 {
	if(!D.first)
		{
		key.i = bioskey_new(0);
// ********  the old code  ********
//		if (key.ch[0]==0)  key.ch[0]=key.ch[1];
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.037  ********
// ********       begin       ********
// ***********************************
		if (key.ch[0]==0)
		{
			key.ch[0]=key.ch[1];
			if (key.ch[0]==F1KEY)
			{
				T3000help(400);
			}
		}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.037  ********
// ********        end        ********
// ***********************************
		}
//	GGHideCur(Black);
	if (key.ch[0]==27)  //esc
	{
	 if(display_mode)
	 {
		piconname(&D);
	 }
	 D.GReleaseWindow();
//	 if(mode_text)
//		 mtextbackground(BOXCOLOR);
	 if ( refresh_time < 25 ) refresh_time = 25;
	 if(print)
		 print_des(group_element, grp_workdata, panel, network);
//-----------	 put_point_info(&group_element->point_info);
	 if ( refresh_time < 15 ) refresh_time = 15;
	 break;
	}


	if (key.ch[0]=='\t' )  //tab
	{
//	 key.ch[0]=0;
//	 if (!last_m)
//		 chbkg(D.objects[D.index_cur]->box.top.x,D.objects[D.index_cur]->box.top.y, D.objects[D.index_cur]->width, D.objects[D.index_cur]->bkgnd, D.objects[D.index_cur]->frgnd);

	 }
	chbkg(D.objects[D.index_cur]->box.top.x,D.objects[D.index_cur]->box.top.y, D.objects[D.index_cur]->width*lat, D.objects[D.index_cur]->bkgnd, -1, 127, height+2);
	D.last= key.ch[0];

	if (key.ch[0]==13)  //tab
	{
	 if( screen_access==R_READ_WRITE )
			 D.objects[D.index_cur]->f(&D);
	}
	if ( key.ch[0]==INSERT && ((type_dis  && D.index_cur==3)
			|| (!type_dis  && D.index_cur==1)) )
	{
	 if(screen_access==R_READ_WRITE)
	 {
		piconname(&D);
//		display_mode = 1;
		D.last == ENTER;
	 }
	}

//	if ( key.ch[0]==80 || key.ch[0]==72 || D.first )  //tab
//
//	 if (D.last_mouse == 0 )
//			 chbkg(D.objects[D.index_cur]->box.top.x,D.objects[D.index_cur]->box.top.y, D.objects[D.index_cur]->width, D.objects[D.index_cur]->bkgnd, D.objects[D.index_cur]->frgnd);
	 if ( D.last=='\t')
		 {
//			key.ch[0]='\t';
//			D.first = 1;
		 }
	 if (D.last == DOWN)  {D.updown=1;  D.first = 1;} //dn=1
	 if ( D.last == UP) {D.updown=2;D.first = 1;}   //up =2
	 if ( D.last == LEFT) {D.updown=3;D.first = 1;}   //RIGHT =3
	 if ( D.last == RIGHT) {D.updown=4;D.first = 1;}   //LEFT =4
	 if (D.last == 0) D.last_mouse = 1;
	 if (D.last == 27) D.esc = 1;
	 if (D.last == ENTER) D.updown = 0;

	 if( !D.last_mouse )
	 if(D.updown)
	 {
		if (D.updown ==1) D.index_cur++;
		else
		 if (D.updown ==2) D.index_cur--;
		 else
			 {
				D.index_cur += (type_dis?4:2);
				if ( D.index_cur>=D.index_obj )  D.index_cur -= (type_dis?8:4);
				if ( D.index_cur<0 )  D.index_cur += (type_dis?8:4);
			 }
		if(display_mode)
		{
		 piconname(&D);
		}
	 }
	 D.first = 0;
	 D.last_mouse=0;
	 if (D.index_cur>=D.index_obj)	D.index_cur--;
	 if (D.index_cur<0)		D.index_cur++;
	 chbkg(D.objects[D.index_cur]->box.top.x,D.objects[D.index_cur]->box.top.y, D.objects[D.index_cur]->width*lat, FONDCOLOR, -1, 127, height+2);


	 }
 }
/*
 if(mouse_inside(D.close_spot.top.x,
		 D.close_spot.top.y,
		 D.close_spot.bot.x,
		 D.close_spot.bot.y) || D.esc )
		{
			mouse_status(stat);
			if(stat.leftButton || D.esc || D.last_mouse)
			 {
			 D.GReleaseWindow();
			 break;
			 }
		}


// i=0;
 for(int i=0;i<D.index_obj;i++)
 {
 if(mouse_inside(D.objects[i]->box.top.x,
		 D.objects[i]->box.top.y,
		 D.objects[i]->box.bot.x,
		 D.objects[i]->box.bot.y))
		{
			mouse_status(stat);
			if(stat.leftButton || D.last_mouse)
			 {
			 D.first = 1;
			 D.last_mouse=1;
			 last_cur=D.index_cur;
			 D.index_cur = i;
			 chbkg(D.objects[last_cur]->box.top.x,D.objects[last_cur]->box.top.y, D.objects[last_cur]->width, D.objects[last_cur]->bkgnd, D.objects[D.index_cur]->frgnd);
			 if(cur==2)
				 i_files += i-last_cur;
			 if(cur==3)
				 {
					i_directories += i-last_cur;
					for(long j=0;j<100000;j++);
					mouse_status(stat);
					if(stat.leftButton)
						{
						 nldirectories(&D, dir, nname, &nrfiles, &nrdirectories,
													 &upfiles, &updir, &key);

////////////

////////////////////
	 D.first = 0;
	 D.last_mouse=0;
						}

				 }

			 break;
			 }
		}
 }

 if ( i < D.index_obj)  continue;



if(mouse_inside(hotuf.top.x,
		 hotuf.top.y,
		 hotuf.bot.x,
		 hotuf.bot.y) && cur==2)
		 {
			mouse_status(stat);
			if(stat.leftButton || D.last_mouse)
			 {
				 D.updown=0;D.first = 1;					//up
				 D.last_mouse=0;
			 }
		}

if(mouse_inside(hotud.top.x,
		 hotud.top.y,
		 hotud.bot.x,
		 hotud.bot.y) && cur==3)
		 {
			mouse_status(stat);
			if(stat.leftButton || D.last_mouse)
			 {
				 D.updown=0;D.first = 1;					//up
				 D.last_mouse=0;
			 }
		}
if(mouse_inside(hotdd.top.x,
		 hotdd.top.y,
		 hotdd.bot.x,
		 hotdd.bot.y) && cur==3)
		{
			mouse_status(stat);
			if(stat.leftButton || D.last_mouse)
			 {
				 D.updown=1;D.first = 1;					//up
				 D.last_mouse=0;
			 }
		}

if(mouse_inside(hotdf.top.x,
		 hotdf.top.y,
		 hotdf.bot.x,
		 hotdf.bot.y) && cur==2)
		{
			mouse_status(stat);
			if(stat.leftButton || D.last_mouse)
			 {
				 D.updown=1;D.first = 1;					//up
				 D.last_mouse=0;
			 }
		}



 if(mouse_inside(hotname.top.x,
		 hotname.top.y,
		 hotname.bot.x,
		 hotname.bot.y) )
		{
			mouse_status(stat);
			if(stat.leftButton || D.last_mouse)
			 {
				if (cur==2)
					 upfiles = i_files - D.index_cur;
				if (cur==3)
					 updir = i_directories - D.index_cur;
				D.last_mouse=0;
				key.ch[0]='\t';
				cur=4;
				chbkg(D.objects[D.index_cur]->box.top.x,D.objects[D.index_cur]->box.top.y, D.objects[D.index_cur]->width, D.objects[D.index_cur]->bkgnd, D.objects[D.index_cur]->frgnd);
				last_m=1;
				D.first = 1;
			 }
		}
 if(mouse_inside(hotfile.top.x,
		 hotfile.top.y,
		 hotfile.bot.x,
		 hotfile.bot.y) )
		{
			mouse_status(stat);
			if(stat.leftButton || D.last_mouse)
			 {
				if (cur==3)
					 updir = i_directories - D.index_cur;
				D.last_mouse=0;
				key.ch[0]='\t';
				cur=1;
				if (nrfiles)
				chbkg(D.objects[D.index_cur]->box.top.x,D.objects[D.index_cur]->box.top.y, D.objects[D.index_cur]->width, D.objects[D.index_cur]->bkgnd, D.objects[D.index_cur]->frgnd);
				last_m=1;
				D.first = 1;
			 }
		}
 if(mouse_inside(hotdir.top.x,
		 hotdir.top.y,
		 hotdir.bot.x,
		 hotdir.bot.y) )
		{
			mouse_status(stat);
			if(stat.leftButton || D.last_mouse)
			 {
				if (cur==2)
					 upfiles = i_files - D.index_cur;
				D.last_mouse=0;
				key.ch[0]='\t';
				cur=2;
				if (nrdirectories)
				chbkg(D.objects[D.index_cur]->box.top.x,D.objects[D.index_cur]->box.top.y, D.objects[D.index_cur]->width, D.objects[D.index_cur]->bkgnd, D.objects[D.index_cur]->frgnd);
				last_m=1;
				D.first = 1;
			 }
		}
 if(mouse_inside(hotdrive.top.x,
		 hotdrive.top.y,
		 hotdrive.bot.x,
		 hotdrive.bot.y) )
		{
			mouse_status(stat);
			if(stat.leftButton || D.last_mouse)
			 {
				if (cur==2)
					 upfiles = i_files - D.index_cur;
				if (cur==3)
					 updir = i_directories - D.index_cur;
				D.last_mouse=0;
				key.ch[0]='\t';
				cur=3;
				chbkg(D.objects[D.index_cur]->box.top.x,D.objects[D.index_cur]->box.top.y, D.objects[D.index_cur]->width, D.objects[D.index_cur]->bkgnd, D.objects[D.index_cur]->frgnd);
				last_m=1;
				D.first = 1;
			 }
		}


*/
};

new_elem(int curcol,int curline,int index_cur, byte panel, int network, int current_grp)
{
//	char *des,*label;
	uint i,j,k;
	int r=1;       //1 - success
	int lat=textwidth(" ");
	int lung=textheight("H");
	Str_grp_element *pgrp;

			char ptr[17],test;
			int num_net, lx,ly,rx,ry,num_point,num_panel;
			byte var_type,point_type;

			num_point = 0;
			if((curcol+40*lat) < maxx+1)
			{
				lx = curcol;
				rx = curcol+40*lat;
			}
			else
			{
				lx = maxx-40*lat;
				rx = maxx;
			}
			if((curline+12+lung+2*LINE_SPACE+3+2) < maxy)
			{
				ly = curline;
				ry = curline+12+lung+2*LINE_SPACE+3+2+4;
			}
			else
			 {
				ly = maxy-(12+lung+2*LINE_SPACE+3+2-4);
				ry = maxy;
			 }
			GWDialog w(lx,ly,rx,ry,NO_STACK,0,SMALL_FONT,5,1);
			w.GWSet(NULL,BOXCOLOR,BOXCOLOR);
			w.GShowWindow(DIALOG);
			w.GWPuts(0,4,"Point :                 ",BOXCOLOR,Black);
//      w.GWGoto(0,12);

//			chbkg((curcol-1)*40+1,curline, 40, Cyan, Black);
//			mgotoxy((curcol-1)*40+5,curline);
//			mtextcolor(Red);
//			mcputs("Point : ");
			setcolor(BOXCOLOR);
			bar(w.GWRetLimits(4)+12*lat,w.GWRetLimits(5)+3,w.GWRetLimits(4)+(12+16)*lat, w.GWRetLimits(5)+3+lung+4);
			w.GWGoto(0,12);
			ptr[0]=0;
			w.GDGets(ptr,0,12,16,FONDCOLOR,White);
			w.GReleaseWindow();

/*
			for(i=0; i<=AY;i++)
			{
				 char pbuf[7];
				 strcpy(pbuf,point_cod[i]);
				 strcat(pbuf,"S");
				 if(!strcmp(pbuf,ptr))
					 break;
			}
*/
			pgrp = &group_element[index_cur];
//			if (i<= AY || ispoint(ptr,&num_point,&var_type, &point_type, &num_panel, &num_net, network, panel))
			if (ispoint(ptr,&num_point,&var_type, &point_type, &num_panel, &num_net, network, panel,(int *)&k))
			{
//				 onet = network;

				 if( local_request(panel,network) )
				 {
//					if ( num_net==network )
					if ( !k )
					 if( rs485port!=-1 && ipxport!=-1 )
					 {
						 num_net=(( class ConnectionData *)Routing_table[rs485port].ptr)->panel_info1.network;
						 network = num_net;
					 }
				 }

/*
				 if( (test=checkpointpresence(num_point,point_type,num_panel,num_net,panel,network))==0 )
						DisplayMessage(160, 150, 500, 210, NULL, panelmis, NULL, Black, NULL, 2500);
				 if(test)
						j = checkmaxpoints(num_point,point_type,num_panel,num_net);
				 else
						j = 128;
*/
//  replaced the above code with next line
         test=1;
				 j = 256;
				 if(num_point <= j )
				 {
//					pgrp->nr_element=1;
//					group_element[index_cur].nr_element=index_cur+1;
//					if ( num_net==network && !k ) num_net = 0xFFFF;
					if ( !k ) num_net = 0xFFFF;
					for(j=1;j<=index_max;j++)
					{
					 for(k=0;k<index_max;k++)
					 {
						if( j==group_element[k].nr_element ) break;
					 }
					 if( k>=index_max ) break;
					}
//					pgrp->nr_element=1;
					pgrp->nr_element=j;
					pgrp->normal_color=Lightgreen;
					pgrp->text_y_coordinate=0;          //curline/lung;
					pgrp->text_x_coordinate=0;          //curcol/lat;
					pgrp->graphic_y_coordinate=curline;
					pgrp->graphic_x_coordinate=curcol;
					pgrp->show_point=1;
					pgrp->display_point_name=0;
					pgrp->text_present = 1;
					pgrp->icon_present = 0;
//					if(i>AY)
					
					 pgrp->point_info.point.putpoint(num_point-1,point_type+1,num_panel-1,num_net);
//					 if (get_point_info(&pgrp->point_info, NULL, NULL, NULL, NULL, 2, network)!=SUCCESS )
//								return 0;
           r=1;
					 if(test)
					 {
						while( DIAL_updategrp==1);
						if( (r=get_point_info(&pgrp->point_info, NULL, NULL, NULL, NULL, 2, num_net==0xFFFF?network:num_net))==SUCCESS )
							modify_grp_new=1;
					 }
					 if(r==SUCCESS)
           {
						pgrp->point_info.description_label=DISPLAY_DES;
						if( num_panel == panel )
						 pgrp->where_point = LOCAL_POINT;
						else
						 pgrp->where_point = LOCAL_NETWORK_POINT;
//					 get_point_info(&pgrp->point_info, &des, &label);
						if( point_type==OUT || point_type==IN || point_type==VAR )
						{
						 pgrp->point_info.description_label=DISPLAY_VALUE;
//						 pgrp->point_info.digital_analog = 0;
						}
						if( point_type==AMON )
						 pgrp->point_info.description_label=DISPLAY_LABEL;
						if( local_request(panel,network) )
						{
						 if( num_panel!=panel )
							updateremotepoint(pgrp->point_info.point,num_net);
						 modify_grp=1;
						}

/*
					else
					{
					 pgrp->point_info.point.putpoint(0,i+1,station_num-1,num_net);
					 pgrp->point_info.description_label=DISPLAY_ICON_VALUE+1;
					}
*/
					 if( !local_request(panel,network) )
					 {
						if( (panel_info1.panel_type == T3000 && panel_info1.version >= 221) ||
								(panel_info1.panel_type == MINI_T3000 && panel_info1.version >= 111) )
						{
						 while( DIAL_updategrp==1);
						 i = sizeof(Str_grp_element);
						 r=net_call(READGROUPELEMENT_T3000+100, ADD_ELEMENT+(current_grp<<8), (char *)pgrp, &i, panel, network,
											NETCALL_RETRY,TIMEOUT_NETCALL,NULL,NULL,NULL,0,pgrp->nr_element);
						 modify_grp_new=1;
						}
						else
						 modify_grp=1;
					 }
          }
					if(r==SUCCESS)
					{
//					chbkg((curcol-1)*40+1,curline, 40, Lightcyan, frgnd);
					 moveto(curcol,curline);
//					setcolor(group_element[index_cur].normal_color);
					 setcolor(White);
					 return 1;
					}
					else
					 return 0;
				 }
				 else
						DisplayMessage(160, 150, 500, 210, NULL, pointins, NULL, Black, NULL, 2000);
			}
 return 0;  //error
}

void pvalue(GWDialog *D)
{
 char avalue[16],*buf, *ptr;
 Str_grp_element *pgrp;
 pgrp = &group_element[index_cur];
// float f;
 if(check_access(pgrp->point_info.point.point_type-1,pgrp->point_info.point.number,R_NA|1)==R_READ_WRITE)
 {
	if (pgrp->point_info.auto_manual==MAN)
	{
	 if(pgrp->point_info.digital_analog)
	 {
		if(pgrp->point_info.units == time_unit)
		{
		 intervaltotext( avalue, pgrp->point_info.point_value / 1000L , 0 , 0);
		 char sec, min, hour;
		 D->GDGetsablon(avalue,2,13,8,FONDCOLOR,White,"NN:NN:NN");
		 texttointerval( avalue, &sec , &min , &hour );
		 pgrp->point_info.point_value=(long)(((long)hour*3600L+(long)min*60L+(long)sec)*1000L);
		}
		else
		{
//	 f = group_element[index_cur].point_info.point_value/1000.;
		 longtoa(pgrp->point_info.point_value, 6, 2, avalue);
		 D->GDGets(avalue,2,13,6,FONDCOLOR,White);
#ifndef NOMATH
		 pgrp->point_info.point_value=atof(avalue)*1000.;
#else
		 pgrp->point_info.point_value=aftolproc(avalue);
/*
		 ptr = strrchr(avalue,'.');
		 if(ptr)
		 {
			 *ptr=0;
			 pgrp->point_info.point_value=atoi(avalue)*1000L;
			 pgrp->point_info.point_value+=atoi(ptr+1);
		 }
		 else
			pgrp->point_info.point_value=atoi(avalue)*1000L;
*/
#endif
		}
	 }
	 else
	 {
		 pgrp->point_info.point_value = pgrp->point_info.point_value?0:1000L;
		 if(pgrp->point_info.point_value)
			buf = ontext;
		 else
			buf = offtext;
		 D->GWPuts(2,13,6,strupr(buf),FONDCOLOR,White);
	 }
	 if( (panel_info1.panel_type == T3000 && panel_info1.version >= 221) ||
			 (panel_info1.panel_type == MINI_T3000 && panel_info1.version >= 111) )
	 {
		 if( DIAL_updategrp==1)
		 	 resume(DIAL);
		 while( DIAL_updategrp==1);
		 writepropertyvalue(pgrp->point_info.point, pgrp->point_info.point_value);
	 }
	 else
     put_point_info(&pgrp->point_info);

// chbkg(D->objects[D->index_cur]->box.top.x,D->objects[D->index_cur]->box.top.y, 6*lat_char_n, D->objects[D->index_cur]->bkgnd, D->objects[D->index_cur]->frgnd,127,lung_char_n+2);
	 modify_grp = 1;
	}
 }
}

void pcolor(GWDialog *D)
{
 Str_grp_element *pgrp;
 pgrp = &group_element[index_cur];
 pgrp->normal_color++;
 if(!mode_text)
	setcolor(pgrp->normal_color);
 D->GWPuts(type_dis?3:3,22,12,color_text,FONDCOLOR,pgrp->normal_color);
// chbkg(D->objects[D->index_cur]->box.top.x,D->objects[D->index_cur]->box.top.y, 6*lat_char_n, D->objects[D->index_cur]->bkgnd, D->objects[D->index_cur]->frgnd,127,lung_char_n+2);
 modify_grp = 1;
}

void ponhigh(GWDialog *D)
{
 Str_grp_element *pgrp;
 pgrp = &group_element[index_cur];
 pgrp->on_high_color++;
 if(!mode_text)
	setcolor(pgrp->on_high_color);
 D->GWPuts(4,22,12,onhigh_text,FONDCOLOR,pgrp->on_high_color);
 modify_grp = 1;
}
void pofflow(GWDialog *D)
{
 Str_grp_element *pgrp;
 pgrp = &group_element[index_cur];
 pgrp->off_low_color++;
 if(!mode_text)
		setcolor(pgrp->off_low_color);
 D->GWPuts(5,22,12,offlow_text,FONDCOLOR,pgrp->off_low_color);
 modify_grp = 1;
}

void pshowpoint(GWDialog *D)
{
 D->GDGets(objectbuf,5,13,3,Cyan,White);
 modify_grp = 1;
}

void pauto(GWDialog *D)
{
 Str_grp_element *pgrp;
 pgrp = &group_element[index_cur];

 if(check_access(pgrp->point_info.point.point_type-1,pgrp->point_info.point.number,R_NA|1)==R_READ_WRITE)
 {
	if(pgrp->point_info.auto_manual == 0 )
			pgrp->point_info.auto_manual++;
	else
			pgrp->point_info.auto_manual--;
	if (pgrp->point_info.auto_manual==AUTO)
		D->GWPuts(2,30,4,strupr(autom),FONDCOLOR,White);
	else
		D->GWPuts(2,30,4,strupr(man),FONDCOLOR,White);

	if( (panel_info1.panel_type == T3000 && panel_info1.version >= 221) ||
			 (panel_info1.panel_type == MINI_T3000 && panel_info1.version >= 111) )
	{
		if( DIAL_updategrp==1)
		 resume(DIAL);
		while( DIAL_updategrp==1);
		writepropertyauto(pgrp->point_info.point, pgrp->point_info.auto_manual);
	}
	else
		put_point_info(&pgrp->point_info);
//	chbkg(D->objects[D->index_cur]->box.top.x,D->objects[D->index_cur]->box.top.y, D->objects[D->index_cur]->width*lat_char_n, D->objects[D->index_cur]->bkgnd, D->objects[D->index_cur]->frgnd,127,lung_char_n+2);
	modify_grp = 1;
 }
}
void ptextsize(GWDialog *D)
{
 D->GDGets(objectbuf,2,29,6,Cyan,White);
}
void phighlimit(GWDialog *D)
{
 char avalue[16],*ptr;
 ftoa(group_element[index_cur].high_limit, 6, 2, avalue);
 D->GDGets(avalue,3,13,6,FONDCOLOR,White);
#ifndef NOMATH
 group_element[index_cur].high_limit=atof(avalue)*1000.;
#else
 group_element[index_cur].high_limit=aftolproc(avalue);
/*
		 ptr = strrchr(avalue,'.');
		 if(ptr)
		 {
			 *ptr=0;
			 group_element[index_cur].high_limit=atoi(avalue)*1000L;
			 group_element[index_cur].high_limit+=atoi(ptr+1);
		 }
		 else
			group_element[index_cur].high_limit=atoi(avalue)*1000L;
*/
#endif
// chbkg(D->objects[D->index_cur]->box.top.x,D->objects[D->index_cur]->box.top.y, D->objects[D->index_cur]->width*lat_char_n, D->objects[D->index_cur]->bkgnd, D->objects[D->index_cur]->frgnd,127,lung_char_n+2);
 modify_grp = 1;
}
void plowlimit(GWDialog *D)
{
 char avalue[16],*ptr;
 ftoa(group_element[index_cur].low_limit, 6, 2, avalue);
 D->GDGets(avalue,4,13,6,FONDCOLOR,White);
#ifndef NOMATH
 group_element[index_cur].low_limit=atof(avalue)*1000.;
#else
 group_element[index_cur].low_limit=aftolproc(avalue);
/*
		 ptr = strrchr(avalue,'.');
		 if(ptr)
		 {
			 *ptr=0;
			 group_element[index_cur].low_limit=atoi(avalue)*1000L;
			 group_element[index_cur].low_limit+=atoi(ptr+1);
		 }
		 else
			group_element[index_cur].low_limit=atoi(avalue)*1000L;
*/
#endif

// chbkg(D->objects[D->index_cur]->box.top.x,D->objects[D->index_cur]->box.top.y, D->objects[D->index_cur]->width*lat_char_n, D->objects[D->index_cur]->bkgnd, D->objects[D->index_cur]->frgnd,127,lung_char_n+2);
 modify_grp = 1;
}

void ptexticon(GWDialog *D)
{
 Str_grp_element *pgrp;
 pgrp = &group_element[index_cur];
 pgrp->text_place++;
 if(pgrp->text_place == 4 )
		pgrp->text_place = 0;
	D->GWPuts(1,13,6,text_place[pgrp->text_place],FONDCOLOR,White);
//	chbkg(D->objects[D->index_cur]->box.top.x,D->objects[D->index_cur]->box.top.y, D->objects[D->index_cur]->width*lat, D->objects[D->index_cur]->bkgnd, D->objects[D->index_cur]->frgnd);
}
void ptypeicon(GWDialog *D)
{
 Str_grp_element *pgrp;
 pgrp = &group_element[index_cur];
 pgrp->type_icon++;
 if(pgrp->type_icon == 2 )
		pgrp->type_icon = 0;
 D->GWPuts(2,13,8,type_icon[pgrp->type_icon],FONDCOLOR,White);
//	chbkg(D->objects[D->index_cur]->box.top.x,D->objects[D->index_cur]->box.top.y, D->objects[D->index_cur]->width*lat, D->objects[D->index_cur]->bkgnd, D->objects[D->index_cur]->frgnd);
 if(pgrp->type_icon)
	 t_icon = 1;
}

void piconname(GWDialog *D)
{
	int error=0, i;
	Str_grp_element *pgrp;
	Str_grp_work_data *pworkdata;
	if(mode_text) return;
	pgrp = &group_element[index_cur];
	pworkdata = &grp_workdata[index_cur];
	pgrp->text_present = 1;
	if(pgrp->point_info.description_label >= DISPLAY_ICON )
	{
				int lx,ly,rx,ry;
				t_icon = 0;
				if( pgrp->point_info.point.point_type-1 != AMON &&
						pgrp->point_info.point.point_type-1 != PRG &&
						pgrp->point_info.point.point_type-1 != WR )
				{
				 strcpy(tempbuf, &icon_name_table[pgrp->icon_name_index][0]);
				 lx = D->objects[D->index_cur]->box.top.x + 16;
				 ly = D->objects[D->index_cur]->box.top.y+16;
				 if( lx+216 < maxx+1)
				 {
					rx = lx+216;
				 }
				 else
				 {
					lx = maxx-216;
					rx = maxx;
				 }
				 if( ly+80 < maxy )
				 {
					ry = ly+80;
				 }
				 else
				 {
					ly = maxy-80;
					ry = maxy;
				 }
//				 set_semaphore_dos();
				 GWDialog *D1;
				 D1 = new GWDialog(lx,ly,rx,ry,NO_STACK,0,SMALL_FONT,5,1);
//				 clear_semaphore_dos();
//				 D->exitCR = 1;
				 D1->GWSet(NULL,BOXCOLOR,BOXTITLE);
				 D1->GShowWindow(DIALOG);
				 D1->enter = 1;

				 D1->GWPuts(0,1," Icon name : ",BOXCOLOR,Black);
				 D1->GWPuts(1,1," Text place: ",BOXCOLOR,Black);
				 D1->GWPuts(2,1," Icon type : ",BOXCOLOR,Black);

				 D1->GWPuts(1,13,text_place[pgrp->text_place],BOXCOLOR,Black);
				 D1->GWPuts(2,13,type_icon[pgrp->type_icon],BOXCOLOR,Black);
//				 D1->GDDef_object(NULL,13,0,12,BOXCOLOR,Black,icon_name_table[pgrp->icon_name_index],Blue,White);
				 D1->GDDef_object(NULL,13,0,12,BOXCOLOR,Black,tempbuf,Blue,White);
				 D1->GDDef_object(ptexticon,13,1,6,BOXCOLOR,Black);
				 D1->GDDef_object(ptypeicon,13,2,8,BOXCOLOR,Black);
				 D1->index_cur=0;
				 while(!(D1->HandleEvent()));
//				 set_semaphore_dos();
				 delete D1;
//				 clear_semaphore_dos();
				 if(!pgrp->icon_present || strcmp(tempbuf,icon_name_table[pgrp->icon_name_index]))
				 {
					 if(pgrp->icon_present)
					 {
						set_semaphore_dos();
//						if(strlen(buf))
//						if(icon_name_table[pgrp->icon_name_index])
						{
						 if(pworkdata->icon)
						 {
							delete pworkdata->icon->ptr_icon;
							delete pworkdata->icon;
							pworkdata->icon = NULL;
						 }
						}
//						else
//						{
//						 delete pworkdata->icon;
//						}
						clear_semaphore_dos();
						pworkdata->icon = NULL;
					 }
//				 if(strlen(ltrim(icon_name_table[pgrp->icon_name_index])))
				 if(strlen(ltrim(tempbuf)))
				 {
					 set_semaphore_dos();
//					 icon *ic=new icon(icon_name_table[pgrp->icon_name_index]);
					 icon *ic=new icon(tempbuf);
					 clear_semaphore_dos();
					 if(!ic->status)
					 {
						set_semaphore_dos();
						pworkdata->icon = new Icon((icon *)ic, -9);
						clear_semaphore_dos();
						if(pgrp->type_icon) t_icon = 1;
						pgrp->default_icon = 0;
						for(i=0;i<MAX_ICON_NAME_TABLE;i++)
						{
						  if( !strcmp(rtrim(tempbuf),rtrim(icon_name_table[i])) ) break;
						}
						if(i>=MAX_ICON_NAME_TABLE)
						{
						 for(i=0;i<MAX_ICON_NAME_TABLE;i++)
						 {
							if(!strlen(rtrim(icon_name_table[i]))) break;
						 }
						 if(i>=MAX_ICON_NAME_TABLE)
						 {
							set_semaphore_dos();
						  delete ic;
						  delete pworkdata->icon;
						  clear_semaphore_dos();
                    pworkdata->icon = NULL;
						  error = 1;
						 }
						}
						if(!error)
						{
						 strcpy(icon_name_table[i], tempbuf);
						 pgrp->icon_name_index = i;
						}
					 }
					 else
					 {
						set_semaphore_dos();
						delete ic;
						clear_semaphore_dos();
						error = 1;
					 }
				 }
/*
				 else
				 {
					if(!points_icon[pgrp->point_info.point.point_type-1].status)
					{
					 set_semaphore_dos();
					 pworkdata->icon = new Icon((icon *)&points_icon[pgrp->point_info.point.point_type-1], -9);
					 clear_semaphore_dos();
					 pgrp->default_icon = 1;
					}
					else
						error = 1;
				 }
*/
				 if( !pgrp->icon_present )
				 {
					pgrp->xicon = pgrp->graphic_x_coordinate;
					pgrp->yicon = pgrp->graphic_y_coordinate;
				 }
				 pgrp->icon_present = 1;

				 }
				}
				else
				{
				 tempbuf[0]=0;
				 if(pgrp->icon_present)
				 {
						set_semaphore_dos();
						delete pworkdata->icon;
									clear_semaphore_dos();
						pworkdata->icon = NULL;
				 }
				 if(!points_icon[pgrp->point_info.point.point_type-1].status)
				 {
					 set_semaphore_dos();
					 pworkdata->icon = new Icon((icon *)&points_icon[pgrp->point_info.point.point_type-1], -9);
					 clear_semaphore_dos();
					 pgrp->default_icon = 1;
				 }
				 else
					 error = 1;
				 if( !pgrp->icon_present )
				 {
					pgrp->xicon = pgrp->graphic_x_coordinate;
					pgrp->yicon = pgrp->graphic_y_coordinate;
				 }
				 pgrp->icon_present = 1;
				}


				if(pgrp->point_info.description_label == DISPLAY_ICON )
						pgrp->text_present = 0;
				if (!error)
				{
				 if( !pgrp->type_icon )
				 {
					 if(pworkdata->icon)
					 {
					  pworkdata->icon->bkgnd_color = -9;
								}
					 pgrp->bkgnd_icon = -9;
				 }
				 if(t_icon)
				 {
//					set_semaphore_dos();
					GWindow *D1;
					D1 = new GWindow(maxx/2 - 12*8 - 8,(maxy - pworkdata->icon->ptr_icon->height)/2-60,maxx/2 + 12*8 + 16,(maxy + pworkdata->icon->ptr_icon->height)/2+18,NO_STACK,0);
//					clear_semaphore_dos();
//				 D->exitCR = 1;
					D1->GWSet(NULL,BOXCOLOR,BOXTITLE);
					D1->GShowWindow(WIN_ERROR);
					D1->GWPuts(0,2," CLICK THE MOUSE ON THE ",BOXCOLOR,Black);
					D1->GWPuts(1,2,"   BACKGROUND COLOR     ",BOXCOLOR,Black);

					pworkdata->icon->bkgnd_color = -9;
					pworkdata->icon->draw_icon( (maxx - pworkdata->icon->ptr_icon->width)/2, (maxy - pworkdata->icon->ptr_icon->height)/2, 0, NULL, 0);

					MouseStatus stat;
					mouse_status(stat);
					while(!stat.leftButton) mouse_status(stat);
					while(!get_button_released(BLEFT,stat));
					hide_pointer();
					asm {
					 mov ah,0dh
					 mov bh,0
					 mov dx,WORD PTR stat.where.y
					 mov cx,WORD PTR stat.where.x
					 int 10h
					}
					t_icon = _AL;
					display_pointer();
					pgrp->bkgnd_icon = t_icon;
					pworkdata->icon->bkgnd_color = t_icon;

					D1->GReleaseWindow();
//					set_semaphore_dos();
					delete D1;
//					clear_semaphore_dos();
				 }
				}
				else
				{
				 pgrp->icon_present = 0;
				 pgrp->text_present = 1;
				 if(pgrp->point_info.description_label == DISPLAY_ICON )
					 pgrp->point_info.description_label = DISPLAY_LABEL;
				 if(pgrp->point_info.description_label > DISPLAY_ICON )
					 pgrp->point_info.description_label -= DISPLAY_ICON_LABEL;
				}
	}
	else
	{
	 if( pgrp->icon_present && pworkdata->icon )
	 {
		if( pworkdata->icon->image_under )
		{
			mputimage(pgrp->xicon, pgrp->yicon, pworkdata->icon->image_under, COPY_PUT);
//		 mfarfree((HANDLE)FP_SEG(group_element[index_cur].icon->image_under));
			mfarfree(pworkdata->icon->image_under);
			pworkdata->icon->image_under = NULL;
		}
		set_semaphore_dos();
		if(!pgrp->default_icon)
		{
			if( pworkdata->icon->ptr_icon )
			 delete pworkdata->icon->ptr_icon;
		}
		delete pworkdata->icon;
		clear_semaphore_dos();
		pworkdata->icon = NULL;
		pgrp->icon_present = 0;
	 }
	}
 display_mode = 0;
}

void pdisplay(GWDialog *D)
{
		group_element[index_cur].point_info.description_label++;
		if(group_element[index_cur].point_info.description_label == 7 )
			group_element[index_cur].point_info.description_label = 0;

/*
	switch (group_element[index_cur].point_info.description_label) {
		case 1:
				D->GWPuts(type_dis?5:2,13,6,des_text,BOXCOLOR,White);
				break;
		case 0:
				D->GWPuts(type_dis?5:2,13,6,label_text,BOXCOLOR,White);
				break;
		case 2:
				D->GWPuts(type_dis?5:2,13,6,val_text,BOXCOLOR,White);
				break;
		}
*/
	D->GWPuts(type_dis?5:3,13,8,d_text[group_element[index_cur].point_info.description_label],BOXCOLOR,White);
/*
	group_element[index_cur].text_present = 1;
	if(group_element[index_cur].point_info.description_label >= DISPLAY_ICON )
	{
				 char buf[13];
				 strcpy(buf,group_element[index_cur].icon_name);
				 set_semaphore_dos();
				 GWDialog *D1;
				 D1 = new GWDialog(D->objects[D->index_cur]->box.top.x + 16,D->objects[D->index_cur]->box.top.y+16,D->objects[D->index_cur]->box.top.x+16+200,D->objects[D->index_cur]->box.top.y+16+72,NO_STACK,0);
				 clear_semaphore_dos();
//				 D->exitCR = 1;
				 D1->GWSet(NULL,BOXCOLOR,BOXTITLE);
				 D1->GShowWindow(DIALOG);

				 D1->GWPuts(0,2," Name : ",BOXCOLOR,Black);
				 D1->GWPuts(1,2," Text : ",BOXCOLOR,Black);

				 D1->GDDef_object(NULL,9,0,12,Cyan,Black,group_element[index_cur].icon_name,Blue,White);
				 D1->GDDef_object(ptexticon,9,1,6,Cyan,Black);
				 while(!(D1->HandleEvent()));
				 set_semaphore_dos();
				 delete D1;
				 clear_semaphore_dos();

				 if(!group_element[index_cur].icon_present || strcmp(buf,group_element[index_cur].icon_name))
				 {
					 if(group_element[index_cur].icon_present)
					 {
						if(strlen(buf))
						{
						 delete group_element[index_cur].icon->ptr_icon;
						 delete group_element[index_cur].icon;
						}
						else
						{
						 delete group_element[index_cur].icon;
						}
					 }
//				 group_element[index_cur].icon_present = 1;
				 if(strlen(ltrim(group_element[index_cur].icon_name)))
				 {
				 }
				 else
				 {
					group_element[index_cur].icon = new Icon((icon *)&points_icon[group_element[index_cur].point_info.point_name.main.point_type-1]);
					if( !group_element[index_cur].icon_present )
					{
					 group_element[index_cur].xicon = group_element[index_cur].graphic_x_coordinate;
					 group_element[index_cur].yicon = group_element[index_cur].graphic_y_coordinate;
					}
					group_element[index_cur].default_icon = 1;
				 }
				 group_element[index_cur].icon_present = 1;

				 if(group_element[index_cur].point_info.description_label == DISPLAY_ICON )
						group_element[index_cur].text_present = 0;
				 }
	}
	else
	{
	 if( group_element[index_cur].icon_present )
	 {
		if( group_element[index_cur].icon->image_under )
		{
		 mputimage(group_element[index_cur].xicon, group_element[index_cur].yicon, group_element[index_cur].icon->image_under);
		 mfarfree((HANDLE)FP_SEG(group_element[index_cur].icon->image_under));
		 group_element[index_cur].icon->image_under = 0;
		}
		group_element[index_cur].icon_present = 0;
	 }
	}
*/
// chbkg(D->objects[D->index_cur]->box.top.x,D->objects[D->index_cur]->box.top.y, D->objects[D->index_cur]->width*lat_char_n, D->objects[D->index_cur]->bkgnd, D->objects[D->index_cur]->frgnd,127,lung_char_n+2);
 modify_grp = 1;
 display_mode = 1;
}

void pinfofile(GWDialog *D)
{
 char buf[5];
 if(group_element[index_cur].display_point_name == 0 )
				 {
					group_element[index_cur].display_point_name=1;
					D->GWPuts(6,13,5,inviz_point_text,FONDCOLOR,White);
				 }
 else
				 {
					group_element[index_cur].display_point_name=0;
					D->GWPuts(6,13,5,viz_point_text,FONDCOLOR,White);
				 }
 chbkg(D->objects[D->index_cur]->box.top.x,D->objects[D->index_cur]->box.top.y, D->objects[D->index_cur]->width*lat_char_n, D->objects[D->index_cur]->bkgnd, D->objects[D->index_cur]->frgnd,127,lung_char_n+2);
 modify_grp = 1;
}

void pload(GWDialog *D)
{
/*
// D->select=1;
// D->GDGets(load_text,6,22,4,Blue,Black);
// if(D->last==13)
// {
// }
// D->select=0;
// if (D->last==80 || D->last==72 || D->last==75 || D->last==77)
		 chbkg(D->objects[D->index_cur]->box.top.x,D->objects[D->index_cur]->box.top.y, D->objects[D->index_cur]->width*lat, D->objects[D->index_cur]->bkgnd, D->objects[D->index_cur]->frgnd);
*/
}
//double GWDialog::GDGetd ( uint row,   uint col, int width,
//				uint bkgnd, uint frgnd)

void delete_elem(byte i, byte panel, int network, int current_grp, byte put = 1)
{
		uint j;
		int r=SUCCESS;
//			int l = print_des(&group_element[i]);
		if(screen_access==R_READ_WRITE)
		{
		 Str_grp_element *pgrp;
		 Str_grp_work_data *pworkdata;
		 pgrp = &group_element[i];
		 pworkdata = &grp_workdata[i];
		 hide_pointer();
		 if( local_request(panel,network) )
		 {
				if( pgrp->point_info.point.panel+1 != panel )
				 deleteremotepoint(pgrp->point_info.point,pgrp->point_info.point.network);
				modify_grp=1;
		 }
		 else
		 {
			 if( (panel_info1.panel_type == T3000 && panel_info1.version >= 221) ||
					(panel_info1.panel_type == MINI_T3000 && panel_info1.version >= 111) )
			 {
					 while( DIAL_updategrp==1);
					 j = sizeof(Str_grp_element);
					 r=net_call(READGROUPELEMENT_T3000+100, DELETE_ELEMENT+(current_grp<<8), (char *)pgrp, &j, panel, network,
											NETCALL_RETRY,TIMEOUT_NETCALL,NULL,NULL,NULL,0,pgrp->nr_element);
					 modify_grp_new=1;
			 }
			 else
				modify_grp=1;
		 }
		 if(r==SUCCESS)
		 {
			if(pworkdata->ptr_save_bkgnd)
			{
			 if(put)
				 mputimage(pgrp->graphic_x_coordinate,pgrp->graphic_y_coordinate,pworkdata->ptr_save_bkgnd, COPY_PUT);
//			 mfarfree( (HANDLE)FP_SEG(group_element[i].ptr_save_bkgnd));
			 mfarfree(pworkdata->ptr_save_bkgnd);
			 pworkdata->ptr_save_bkgnd=NULL;
			}
			if( pgrp->icon_present && pworkdata->icon )
			{
			 if( pworkdata->icon->image_under )
				 if(put)
					 mputimage(pgrp->xicon, pgrp->yicon, pworkdata->icon->image_under, COPY_PUT);
			 set_semaphore_dos();
			 if( !pgrp->default_icon )
				if( pworkdata->icon->ptr_icon )
					delete pworkdata->icon->ptr_icon;
			 delete pworkdata->icon;
			 clear_semaphore_dos();
			 pworkdata->icon = NULL;
			}
			display_pointer();
//			pgrp = &group_element[index_cur];
//			pworkdata = &grp_workdata[index_cur];
			for(j=i;j<index_max-1;pgrp++,pworkdata++,j++)
			{
				*pgrp = *(pgrp+1);
				*pworkdata = *(pworkdata+1);
			}
			index_max--;
			index_max_group_element = index_max;
			memset(pgrp, 0, sizeof(Str_grp_element));
			memset(pworkdata, 0, sizeof(Str_grp_work_data));
//			modify_grp=1;
		 }
		}
		else
		{
		 DisplayMessage(160, 150, 500, 210, NULL, " Unauthorized access! ", NULL, Black, NULL, 1200);
		}
}

//int Control_group_block::graphic_mode(void)
int graphic_mode(Control_group_point *block, int current_point, int call_type, byte panel, int network, int display, Point_Net *retpoint)
{
// struct palettetype Ppal;
 MouseStatus stat;
 Str_grp_work_data *pworkdata;
 uint i;
 int local_panel_old;
 int curline=2,curcol=1,menu=0;
 int x,y;
 char *des,*label;
 char filename[65];
// rgb pal[16],pal1[16];
 rgb pal1[16];
 Point_Net openscreen;
 unsigned long lastreadopenscreen;
 int rtime;
 lastreadopenscreen	= timestart+timesec1970;
 openscreen=current_opened_grp;
 localopenscreen.setzero();

 grp_current_pal=(rgb *)pal1;
 BOXCOLOR=Cyan;
 int bkgnd=FONDCOLOR, frgnd=White;
 int index_obj = MAX_ELEM;
 index_max_group_element=0;
 index_cur=0;
 hot_box hotgroup={3,1,96,15};
 hot_box hotload={112,1,145,15};
 hot_box hotsend={161,1,195,15};
 hot_box hotedit={211,1,245,15};
 hot_box hotexit={260,1,292,15};

	 filename[0] = 0;
//	 if( local_panel )
//	 if( local_request(panel,network) )
	 if( ptpnetwork(network) )
	  strcpy(filename, remote_path);
	 else
		strcpy(filename, ptr_panel->Graphics_Path);

	 if(strlen(filename)) strcat(filename, "\\");
	 strcat(filename,block->picture_file);
	 strcat(rtrim(filename),".tif");

 hide_pointer();

//
// int old_mode;
// if(dontch==-1)
// {
//	 old_mode=MODE_TEXT;
//	 dontch = 0;
// }
// else
//	if(dontch)
//		old_mode=MODE_TEXT;
//	else
//		old_mode=MODE_GRAPHIC;
//
 if(mode_text )
 {
	mode_text = MODE_GRAPHIC;
	hide_pointer();
	restorechar();
	setgraphmode(getgraphmode());
	Green=GREEN;                 //2
	White=WHITE; 						 //5
	Darkgray=DARKGRAY;                 //6
	Brown=BROWN;           //8
	Lightblue=LIGHTBLUE;         //9
	Magenta=MAGENTA;                 //15
//				 setpalette(BROWN,BROWN);
//				 setpalette(GREEN,GREEN);
//				 setpalette(MAGENTA,MAGENTA);
//				 setpalette(DARKGRAY,DARKGRAY);
//				 setpalette(WHITE,WHITE);
//				 setpalette(LIGHTBLUE,LIGHTBLUE);

// setpalette(Green,88);
// setpalette(White,255);
// setpalette(Magenta,99);
// setpalette(Brown,8);
asm {
	 mov ax,21h
	 int 33h
	 }
 display_pointer();
// mouse_installed();
 }
 int esc = 0;
 char cont;
 GWindow *D=NULL;
 msettextstyle(DEFAULT_FONT, 0, 1);
 modify_grp_new=0;
while(!esc)
{
// int exit=0;
 hide_pointer();
 setbkcolor(Black);
 fond_color=Black;
 cleardevice();
 int nclrs;
// struct palettetype ppal;
// getpalette(&ppal);
// get16( pal, 0 );
 if(strlen(rtrim(block->picture_file)))
 {
	struct ffblk block;
	set_semaphore_dos();
	int_disk=1;
	int done=findfirst(filename, &block,FA_ARCH);
	int_disk=0;
	clear_semaphore_dos();
	if(!done)
		tif(filename,0,0,maxx,maxy);
	else
	{
		if(!test_tiff)
		{
			test_tiff = 1;
			DisplayMessage(190, 170, 490, 230, NULL, " Picture file not found! ",NULL,Black,NULL,1300);
//			DisplayError(190, 170, 490, 230, "     Picture file not found! ", Lightblue, White, Blue);
		}
		grp_current_pal=init_pal;
	}
 }
 else
	grp_current_pal=init_pal;
	BOXCOLOR=closest_rgb( init_pal[BOXCOLOR], grp_current_pal, 16);
/*
	draw_icon(100, 100, &points_icon[AMON], pal1, 1);
	for(int i=0; i< 40; i++)
	{
	 Delay(500);
	 draw_icon(100+i*2, 100+i*2, &points_icon[AMON], pal1, 1);
	}
	if( points_icon[AMON].image_under )
	{
	 delete points_icon[AMON].image_under ;
	 points_icon[AMON].image_under = NULL;
	}
*/
//	setallpalette(&ppal);
//	set16( pal, 0 );
// setcolor(Red);
// outtextxy(200, 4, block->description);
// outtextxy(370, 4, block->label);

 union key key;
 GMenuBar *grp_menu;
 if(!display)
 {
	grp_menu = new GMenuBar(0,0,maxx,19,Lightgray,Black,White,3,BARMENU,NULL);
 }
// set_pointer_shape(ARROW);
 key.ch[0]='\t';
 screen_access = check_access(GRP, current_point);
 display_pointer();
 Str_grp_element *pgrp;
 Control_group_elements *cgrp;
// if((local_panel && call_type!=INDIVIDUAL) || (call_type==INDIVIDUAL && panel==Station_NUM ))
// if((local_panel &&  panel==Station_NUM) || (!local_panel &&  panel==Station_NUM && panel!=station_num))
 if( local_request(panel,network) )
 {
	cgrp = &ptr_panel->control_group_elements[current_point];
//	xcur_grp = cgrp->xcur_grp;
//	ycur_grp = cgrp->ycur_grp;

	pgrp = group_element;
	for(i=0; i<cgrp->nr_elements;i++, pgrp++)
	 {
		memcpy(pgrp,cgrp->ptrgrp+i,sizeof(Str_grp_element));
//		pgrp->ptr_save_bkgnd=NULL;
//		pgrp->icon = NULL;
	 }
	index_max=index_max_group_element=cgrp->nr_elements;
 }
 else
 {
	 if( DIAL_updategrp==1)
			 resume(DIAL);
	 while(DIAL_updategrp==1);
	 DisplayMessage(160, 150, 500, 210, ctrlbreak_text,"   Reading data ... ",&D);
	 Delay(100);
		i=0;
	 NotResponse1=0;
	 int s=net_call(19, current_point, (char *)group_element, &i, panel, network, NETCALL_SIGN);
	 NotResponse1=1;
	 if(D){ DeleteMessage(D);  D=NULL;}
	 if(s==SUCCESS)
	 {
		index_max=i/sizeof(Str_grp_element);
/*
		if( --index_max < 0 )
		{
		 index_max=0;
		 ycur_grp=xcur_grp=24;
		}
		else
		{
		 ycur_grp=group_element[index_max].graphic_y_coordinate;
		 xcur_grp=group_element[index_max].graphic_x_coordinate;
		}
*/
		index_max_group_element=index_max;
/*
		pgrp = group_element;
		for(int i=0; i<index_max; pgrp++, i++)
		{
			pgrp->ptr_save_bkgnd=0;
			pgrp->icon = NULL;
		}
		memset(pgrp,0,sizeof(Str_grp_element));
*/
//		refresh_time_init = 200;
//	 resume(NETWORK);
	 }
	 else
	 {
		key.ch[0]=27;
		error_communication=1;
	 }
	}
 if (ycur_grp < 20 ) ycur_grp = 23;
 status_mouse = SHOWMOUSE;
 move_mouse(xcur_grp,ycur_grp);

 msettextstyle(SMALL_FONT, 0, 5);
//	setusercharsize(4,3,4,3);
//	int lat=textwidth(" ");
//	int lung=textheight("H");


 int page = -1;
 int first=1, last_mouse=0;
 refresh_time = refresh_time_init;
 local_panel_old = local_panel;
 setscreenstate(current_opened_grp);
 while (1)
 {
	if (bioskey_new(1) || first)
	{
	 if(!first)
	 {
		key.i = bioskey_new(0);
// ********  the old code  ********
//		if (key.ch[0]==0)  key.ch[0]=key.ch[1];
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.038  ********
// ********       begin       ********
// ***********************************
		if (key.ch[0]==0)
		{
			key.ch[0]=key.ch[1];
			if (key.ch[0]==F1KEY)

			{
						T3000help(400);
			}
		}
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.038  ********
// ********        end        ********
// ***********************************
	 }
//	GGHideCur(Black);
	 if (key.ch[0]==27)  //esc
	 {
//	 if(!exit)
		 {
			esc = 1;
		 }
//	    refresh_time_init = 150;
		 break ;
	 }
	 if (key.ch[0]==68)  //f10
	 {
		memsize();
	 }
	 if(key.ch[0]==1)  //CTRL-A  alarm  screen
	 {
				 menu=0;
				 first=1;
				 key.ch[0]=27;  //esc
				 esc = ALARMS+1;
				 break;
	 }
	 if (key.ch[0]==INSERT || key.ch[0]==ENTER || key.ch[0]==50 || key.ch[0]==DELETE)
	 {
		if( DIAL_updategrp==1 )
		 resume(DIAL);

		mouse_status(stat);
		curcol = stat.where.x;
		curline = stat.where.y;
		pgrp = group_element;
		pworkdata = grp_workdata;
		for(i=0;i<index_max; pgrp++,pworkdata++,i++)
		{
		 if( pgrp->text_present && (stat.where.x >= pgrp->graphic_x_coordinate && stat.where.x <= pgrp->graphic_x_coordinate+print_des(pgrp,pworkdata,panel,network,1)*8 &&
					stat.where.y >= pgrp->graphic_y_coordinate && stat.where.y <= pgrp->graphic_y_coordinate+lat_char_n) )      // lung_char_n  am fixat la 8
					 break;
//			 (pgrp->icon_present && (stat.where.x >= pgrp->xicon && stat.where.x <= pgrp->xicon+pworkdata->icon->ptr_icon->width &&
//				stat.where.y >= pgrp->yicon && stat.where.y <= pgrp->yicon+pworkdata->icon->ptr_icon->height)) )
		 if( pworkdata->icon )
			 if ( pworkdata->icon->ptr_icon )
			 {
				if ( stat.where.x >= pgrp->xicon && stat.where.x <= pgrp->xicon+pworkdata->icon->ptr_icon->width &&
						 stat.where.y >= pgrp->yicon && stat.where.y <= pgrp->yicon+pworkdata->icon->ptr_icon->height )
					break;
			 }
		}
		index_cur=i;
		if(index_cur!=index_max && key.ch[0]==DELETE && !display) //Delete
		{
		 delete_elem(i, panel, network, current_point);
		}
		pgrp = &group_element[index_cur];
		pworkdata = &grp_workdata[index_cur];
		if(index_cur!=index_max && key.ch[0]==50 && !display) //Alt-M move
		{
//		char bitmap[800];
//		int l = print_des(&group_element[i]);
//		hide_pointer();
//		int n = imagesize(group_element[i].graphic_x_coordinate,group_element[i].graphic_y_coordinate, group_element[i].graphic_x_coordinate+l*textwidth(" "),group_element[i].graphic_y_coordinate+8);
//		mgetimage(group_element[i].graphic_x_coordinate,group_element[i].graphic_y_coordinate, group_element[i].graphic_x_coordinate+l*textwidth(" "),group_element[i].graphic_y_coordinate+8,bitmap);
//		mputimage(group_element[i].graphic_x_coordinate,group_element[i].graphic_y_coordinate, bitmap,XOR_PUT);
//		print_des(&group_element[i]);
//		hide_pointer();
//		mgetimage(group_element[i].graphic_x_coordinate,group_element[i].graphic_y_coordinate, group_element[i].graphic_x_coordinate+l*textwidth(" "),group_element[i].graphic_y_coordinate+8,bitmap);
//		display_pointer();
		if(screen_access==R_READ_WRITE)
		{
		 int l = print_des(pgrp,pworkdata,panel,network);
		 copy_icon = 1;
		 while(1)
		 {
//		 while(!bioskey_new(1));
			if(bioskey_new(1))
			{
			 key.i = bioskey_new(0);
			 if(key.ch[0]==ENTER)
			 {
				copy_icon = 0;
				modify_grp=1;
				if( !local_request(panel,network) )
				 if( (panel_info1.panel_type == T3000 && panel_info1.version >= 221) ||
						(panel_info1.panel_type == MINI_T3000 && panel_info1.version >= 111) )
					{
//						 int k;
						 i = sizeof(Str_grp_element);
//						 k = elemindex(group_element, index_cur);
						 while( DIAL_updategrp==1);
						 net_call(READGROUPELEMENT_T3000+100, UPDATE_ELEMENT+(current_point<<8), (char *)pgrp, &i, panel, network,
											NETCALL_RETRY,TIMEOUT_NETCALL,NULL,NULL,NULL,0,pgrp->nr_element);
						 modify_grp=0;
						 modify_grp_new = 1;
					}
				break;
			 }
			 if(key.ch[0]==0)
			 {
				hide_pointer();
				if( pworkdata->ptr_save_bkgnd )
				{
				 mputimage(pgrp->graphic_x_coordinate,pgrp->graphic_y_coordinate,pworkdata->ptr_save_bkgnd, COPY_PUT);
//			mfarfree( (HANDLE)FP_SEG(group_element[i].ptr_save_bkgnd) );
				 mfarfree(pworkdata->ptr_save_bkgnd);
				 pworkdata->ptr_save_bkgnd=NULL;
				}

				i=2;
				if( bioskey_new(2)&0x02 ) i=8;
				switch (key.ch[1]) {
				case DOWN:
				 if(pgrp->icon_present)
				 {
					 if (pgrp->yicon+pworkdata->icon->ptr_icon->height < maxy - i) pgrp->yicon += i;
					 break;
				 }
				 if(pgrp->text_present && pgrp->graphic_y_coordinate+i < maxy - 10) pgrp->graphic_y_coordinate += i;
				 break;
				case UP:
				 if(pgrp->icon_present)
				 {
					 if ( ((int)pgrp->yicon)-i > 20) pgrp->yicon -= i;
					 break;
				 }
				 if( ((int)pgrp->graphic_y_coordinate)-i > 20)  pgrp->graphic_y_coordinate -= i;
				 break;
				case LEFT:
				 if(pgrp->icon_present)
				 {
					if(((int)pgrp->xicon)-i > 0)  pgrp->xicon -= i;
					break;
				 }
				 if( ((int)pgrp->graphic_x_coordinate)-i > 0)  pgrp->graphic_x_coordinate -= i;
				 break;
				case RIGHT:
				 if(pgrp->icon_present)
				 {
					if(pgrp->xicon+pworkdata->icon->ptr_icon->width+i < maxx+1) pgrp->xicon += i;
					break;
				 }
				 if(pgrp->graphic_x_coordinate+i+l*8 < maxx+1) pgrp->graphic_x_coordinate += i;
				 break;
				}
				if(pgrp->icon_present)
				 move_mouse(pgrp->xicon,pgrp->yicon);
				else
				 move_mouse(pgrp->graphic_x_coordinate,pgrp->graphic_y_coordinate);
				if (refresh_time < 15) refresh_time = 15;
				print_des(pgrp,pworkdata,panel,network);
//		 display_pointer();
			 }
			}
			else
			{
			 mouse_status(stat);
			 if(stat.leftButton)
			 {
				while(!get_button_released(BLEFT,stat));
				copy_icon = 0;
				modify_grp=1;
				break;
			 }
//		 int x,y;
			 if (mouse_motion(&x,&y))
			 {
				hide_pointer();
//			mmputimage(group_element[i].graphic_x_coordinate,group_element[i].graphic_y_coordinate,group_element[i].graphic_x_coordinate+group_element[i].nchar*lat_char_n,group_element[i].graphic_y_coordinate+8,group_element[i].ptr_save_bkgnd);
//			set_semaphore_dos();
//			mfarfree( group_element[i].ptr_save_bkgnd);
//			clear_semaphore_dos();
				if( pworkdata->ptr_save_bkgnd )
				{
				 mputimage(pgrp->graphic_x_coordinate,pgrp->graphic_y_coordinate,pworkdata->ptr_save_bkgnd, COPY_PUT);
//			mfarfree( (HANDLE)FP_SEG(group_element[i].ptr_save_bkgnd));
				 mfarfree( pworkdata->ptr_save_bkgnd );
				 pworkdata->ptr_save_bkgnd=NULL;
				}
//	  	 mputimage(group_element[i].graphic_x_coordinate,group_element[i].graphic_y_coordinate, bitmap,XOR_PUT);
				if(	stat.where.x < 0) stat.where.x=0;
				if(pgrp->icon_present)
				{
				 if(stat.where.x+pworkdata->icon->ptr_icon->width >= maxx) stat.where.x = maxx-pworkdata->icon->ptr_icon->width-1;
				}
				else
				{
				 if( stat.where.x+l*8 >= maxx) stat.where.x = maxx-l*8;
				}
				pgrp->graphic_x_coordinate=stat.where.x;
				pgrp->xicon=stat.where.x;
				if(	stat.where.y < 22) stat.where.y=22;
				if(pgrp->icon_present)
				{
				 if(stat.where.y+pworkdata->icon->ptr_icon->height + 16 >= maxy) stat.where.y = maxy-pworkdata->icon->ptr_icon->height-16;
				}
				else
				{
				 if( stat.where.y+8 >= maxy) stat.where.y = maxy-8;
				}
				pgrp->graphic_y_coordinate=stat.where.y;
				pgrp->yicon=stat.where.y;
				if (refresh_time < 15) refresh_time = 15;
				print_des(pgrp,pworkdata,panel,network);
//			 mputimage(group_element[i].graphic_x_coordinate,group_element[i].graphic_y_coordinate, bitmap,XOR_PUT);
//			 display_pointer();
			 }
			}
		 }
//	 hide_pointer();
//	 mputimage(group_element[i].graphic_x_coordinate,group_element[i].graphic_y_coordinate, bitmap,XOR_PUT);
//	 print_des(&group_element[i]);
//	 move_mouse(group_element[i].graphic_x_coordinate,group_element[i].graphic_y_coordinate);
//	 display_pointer();
		 if (refresh_time < 15) refresh_time = 15;
		 print_des(pgrp,pworkdata,panel,network);
		 index_cur=index_max;
		}
		else
		 DisplayMessage(160, 150, 500, 210, NULL, " Unauthorized access! ", NULL, Black, NULL, 1200);
	 }

			if(index_cur!=index_max && key.ch[0]==ENTER && !display)
			{
			 first = 0;
			 if(!pgrp->point_absent)
			 {
				if(pgrp->point_info.point.point_type-1!=PRG &&
				 pgrp->point_info.point.point_type-1!=AMON &&
				 pgrp->point_info.point.point_type-1!=GRP &&
				 pgrp->point_info.point.point_type-1!=WR &&
				 pgrp->point_info.point.point_type-1!=AR &&
				 pgrp->point_info.point.point_type-1!=CON &&
				 pgrp->point_info.description_label != DISPLAY_ICON_VALUE+1 )
				 key.ch[0]=INSERT;
				else
				if(retpoint)
				{
				if( check_access(pgrp->point_info.point.point_type-1, pgrp->point_info.point.number)!=R_NA )
				{
				 menu=0;
				 first=1;
				 key.ch[0]=27;  //esc
				 *retpoint=pgrp->point_info.point;
				 if( pgrp->point_info.description_label ==DISPLAY_ICON_VALUE+1 )
					esc = pgrp->point_info.point.point_type+100;
				 else
					esc = pgrp->point_info.point.point_type;
//				xcur_grp=group_element[index_cur].graphic_x_coordinate;
//				ycur_grp=group_element[index_cur].graphic_y_coordinate;
//
//				if(esc-1!=PRG)
//					dontch = 1;
//				else
//					dontch = 0;
//
				 break;
				}
			 }
				 }
		 }

	 if(index_cur!=index_max && key.ch[0]==INSERT)
	 {
//			if(index_cur!=index_max)
			 if(!pgrp->point_absent)
			 {
				cell(curcol,curline,pgrp,pworkdata,panel,network,1);
				if(modify_grp)
				 if( !local_request(panel,network) )
					if( (panel_info1.panel_type == T3000 && panel_info1.version >= 221) ||
							(panel_info1.panel_type == MINI_T3000 && panel_info1.version >= 111) )
					{
						 while( DIAL_updategrp==1);
						 i = sizeof(Str_grp_element);
						 net_call(READGROUPELEMENT_T3000+100, UPDATE_ELEMENT+(current_point<<8), (char *)pgrp, &i, panel, network,
											NETCALL_RETRY,TIMEOUT_NETCALL,NULL,NULL,NULL,0,pgrp->nr_element);
						 modify_grp=0;
						 modify_grp_new=1;
					}
			 }
	 }

	 if(index_cur==index_max && key.ch[0]==INSERT && !display)
	 {
			if(screen_access==R_READ_WRITE)
			{
//					index_max++;  				 //nu exista elementul
//					index_max_group_element = index_max;
					if(index_max < MAX_ELEM)
					{
					 if( new_elem(curcol,curline,index_max,panel,network,current_point))
					 {
						index_max++;  				 //nu exista elementul
						index_max_group_element = index_max;
						hide_pointer();
						if (refresh_time < 15) refresh_time = 15;
						print_des(&group_element[index_cur],grp_workdata+index_cur,panel,network);
//					 modify_grp = 1;
						display_pointer();
					 }
					 else
					 {
						memset(&group_element[index_cur], 0, sizeof(Str_grp_element));
						memset(&grp_workdata[index_cur], 0, sizeof(Str_grp_work_data));
					 }
					}
					else
					{
					 DisplayMessage(160, 150, 500, 210, NULL, " To many elements! ", NULL, Black, NULL, 1500);
					}
			}
			else
			 DisplayMessage(160, 150, 500, 210, NULL, " Unauthorized access! ", NULL, Black, NULL, 1200);
	 }
//	 else
//	 if(index_cur!=index_max && key.ch[0]==13)

	}
	if (key.ch[0] == '\t') //tab
	{
					page++;
					index_cur=0;
					curline=2;
					curcol=1;
					first=0; last_mouse=0;
					refresh_time = 2000;
					pgrp = &group_element[index_cur];
					for(i=index_cur;i<index_obj;pgrp++,i++)
					{
					 if(pgrp->nr_element)
					 {
						 print_des(pgrp,grp_workdata+i,panel,network);
					 }
					}
					refresh_time = refresh_time_init;
	}
// exit = 0;
 if (key.ch[0] == PGDN	&& key.ch[1] == PGDN) //Pgdn
 {
	 esc = PGDN;
	 break ;
 }
 if (key.ch[0] == PGUP && key.ch[1] == PGUP) //PgUP
 {
	 esc = PGUP;
	 break ;
 }

 if (key.ch[0]==DOWN || key.ch[0]==UP || key.ch[0] == RIGHT || key.ch[0] == LEFT )  //dn, up
 {
//	 int x,y;
	 mouse_status(stat);
	 x=stat.where.x;
	 y=stat.where.y;
	 i=2;
	 if( bioskey_new(2)&0x02 ) i=8;
	 if (key.ch[0]==DOWN)  //dn
			 y += i;
	 if (key.ch[0]==UP)  //up
			 y -= i;
	 if (key.ch[0]==RIGHT)  //right
			 x += i;
	 if (key.ch[0]==LEFT)  //left
			 x -= i;
	 if (x<0) x=0;
	 if (x>maxx) x=maxx;
	 if (y<0) y=0;
	 if (y>maxy) y=maxy;

	 if(menu==1 && key.ch[0]==DOWN)
	 {
			menu=0;
			y = 20;
			key.ch[0]=0;
			first = 0;
	 }
	 else
		 if(menu==0 && y < 19 && !display)
		 {
			menu=1;
			y = 17;
		 }
	 move_mouse(x,y);
 }

 if (menu && !display)
			{
			int qt=0;
		msettextstyle(DEFAULT_FONT, 0, 1);
		grp_menu->GShowMenuBar(graphic_grp_message);
		msettextstyle(SMALL_FONT, 0, 5);
			do {

/*
			 if(!refresh_time)
				{
				 if(modify_grp)
				 {
					if(!display)
					{
//					 if(local_panel)
//					 if((local_panel &&  panel==Station_NUM) || (!local_panel &&  panel==Station_NUM && panel!=station_num))
					 if( local_request(panel,network) )
						error_communication=send_grp(1,index_obj, current_point, group_element, curline, curcol);
					 else
					 {
						error_communication=send_grp(0,index_obj, current_point, group_element, curline, curcol,panel,network);
					 }
					}
				 }
//				if(local_panel)
//				if((local_panel &&  panel==Station_NUM) || (!local_panel &&  panel==Station_NUM && panel!=station_num))
				if( local_request(panel,network) )
				{
				 if(local_panel_old == local_panel)
					update_value_grp_elem(ptr_panel->control_group_elements[current_point].ptrgrp,ptr_panel->control_group_elements[current_point].nr_elements);
				}
				else
				{
				 Str_grp_element *buf;
				 buf = group_element_temp;
				 Delay(100);
				 i=0;
				 if((error_communication=net_call(19, current_point, (char *)buf, &i, panel, network))==SUCCESS)
				 {
					index_max=i/sizeof(Str_grp_element);
//					if( --index_max < 0 ) index_max=0;
					index_max_group_element=index_max;
//				 memset(&group_element[index_max],0,sizeof(Str_grp_element));
					for(i=0; i<index_max;i++)
					{
//					 group_element[i].point_info=buf[i].point_info;
					 group_element[i]=buf[i];
					}
				 }
				}

//					for(int i=index_cur;i<index_obj;i++)
					pgrp = group_element;
					for(i=0;i<index_obj;pgrp++, i++)
					{
					 if(pgrp->nr_element)
						{
						 print_des(pgrp,grp_workdata+i,panel,network);
						}
					}
				 refresh_time = refresh_time_init;
				}
*/
			 msettextstyle(DEFAULT_FONT, 0, 1);
			 int man=grp_menu->GReturn();
			 msettextstyle(SMALL_FONT, 0, 5);
			 switch (man) {

				 case 0:

				 {
//				 set_semaphore_dos();
				 GGrid *w = new GGrid(6,22,6+70*8,450,0,NULL,GRAPHIC_GRP,ptr_panel->GlPanel_type,ptr_panel->GlPanel,ptr_panel->GlNetwork);
//				 clear_semaphore_dos();
				 w->GWSet("Group Elements",Lightgray,Darkgray);
				 w->save = 0;   //NO_SAVE
//				 w->save = 2;   //NO_SAVE
				 w->GShowGrid();
				 nothing = 0;
				 while (!w->HandleEvent());
				 nothing = 1;
//				 set_semaphore_dos();
				 delete w;
//				 clear_semaphore_dos();
				 }
				 hide_pointer();
//				 get16( pal, 0 );

				 if(strlen(rtrim(block->picture_file)))
				 {
					struct ffblk block;
					set_semaphore_dos();
					int_disk=1;
					int done=findfirst(filename,&block,FA_ARCH);
					int_disk=0;
					clear_semaphore_dos();
					if(!done)
						tif(filename,0,0,maxx,maxy);
					else
					{
						cleardevice();
						grp_current_pal=init_pal;
					}
				 }
				 else
				 {
						cleardevice();
						grp_current_pal=init_pal;
				 }

//				 get16(pal1,0);
				 BOXCOLOR=closest_rgb( init_pal[BOXCOLOR], grp_current_pal, 16);
//				 set16( pal, 0 );
				 display_pointer();
				 page = -1;
				 first = 1;
				 key.ch[0]='\t';
				 menu=0;
				 qt=1;
				 msettextstyle(SMALL_FONT, 0, 5);
				 break;
/*
				 case 1:
					{
					 memset(group_element,'\0',sizeof(Str_grp_element)*(MAX_ELEM+1));
					 for(int i=0; i<ptr_panel->control_group_elements[current_point].nr_elements;i++)
						 memcpy(&group_element[ptr_panel->control_group_elements[current_point].ptrgrp[i].nr_element-1],ptr_panel->control_group_elements[current_point].ptrgrp+i,sizeof(Str_grp_element));
					 page = -1;
					 first=1; last_mouse=0;
					 key.ch[0]='\t';
					 menu=0;
					 qt=1;
					}
					 break;
				 case 2:
					 if(local_panel)
						 send_grp(1,index_obj, current_point, group_element, curline, curcol);
					 else
						 send_grp(0,index_obj, current_point, group_element, curline, curcol);
					 menu=0;
					 qt=1;
					 break;
*/
				 case 1:
					 char b[6];
					 itoa( refresh_time_init/18, b, 10);
					 ReadWindow(200, 150, 400, 220, Lightgray, Darkgray, Blue,
							 Cyan, White, "Refresh time : ", b, 3);
					 refresh_time_init = atoi(b)*18;
					 break;
				 case  2:
				 case -2:
					 menu=0;
					 first=1;
					 qt=1;
					 key.ch[0]=27;  //esc
					 break;
				 case DOWN:
					 qt=1;
					 key.ch[0]=DOWN;
					 display_pointer();
					 break;
				 case -3:
					 qt=1;
					 menu=0;
					 first=0;
					 display_pointer();
					 break;
				 case -4:
					 qt=1;
					 break;
			 }
			} while(!qt);
grp_menu->ReleaseMBar();

			}
}
 if(mouse_inside(0, 0, maxx, 19 ) &&  key.ch[0]!=27 && page!=-1 && !display)
 {
		 menu=1; first=1;
		 if(key.ch[0]!=DOWN) key.ch[0]=0;
 }

mouse_status(stat);
if(stat.rightButton)
{
//	 if(!exit)
		 {
			while(!get_button_released(BRIGHT,stat));
			esc = 1;
		 }
	 break ;
}
if(mouse_inside(500, 1, 639, 16 ))
	 if(stat.leftButton)
	 {
		Panel_info1 panel_info;
		if(local_request(panel,network))
		{
		 if( GAlarm )
				 showpoints(M3+3, Panel_Info1.panel_type, panel, network);
		}
		else
		{
		 if( gAlarm )
				if( net_call(COMMAND_50, PANEL_INFO1_COMMAND, (char*)&panel_info, 0, panel, network) == RS232_SUCCESS )
				{
					showpoints(M3+3, panel_info.panel_type, panel, network);
				}
		}
	 }

if(stat.leftButton)
{
 while(!get_button_released(BLEFT,stat));
 pgrp = group_element;
 pworkdata = grp_workdata;
 for(i=0;i<index_max_group_element;pgrp++,pworkdata++,i++)
 {
	int l = print_des(pgrp,pworkdata,panel,network,1);
	if( (pgrp->text_present && (stat.where.x >= pgrp->graphic_x_coordinate && stat.where.x <= pgrp->graphic_x_coordinate+l*8 &&
			 stat.where.y >= pgrp->graphic_y_coordinate && stat.where.y <= pgrp->graphic_y_coordinate+lat_char_n)) ||       // lung_char_n  am fixat la 8
			 (pgrp->icon_present && (stat.where.x >= pgrp->xicon && stat.where.x <= pgrp->xicon+pworkdata->icon->ptr_icon->width &&
				stat.where.y >= pgrp->yicon && stat.where.y <= pgrp->yicon+pworkdata->icon->ptr_icon->height)) )
	if( (pgrp->text_present && mouse_inside(pgrp->graphic_x_coordinate,pgrp->graphic_y_coordinate,
								 pgrp->graphic_x_coordinate+l*textwidth(" "),pgrp->graphic_y_coordinate+8)) ||
		 (pgrp->icon_present && mouse_inside(pgrp->xicon,pgrp->yicon,
								 pgrp->xicon+pworkdata->icon->ptr_icon->width,pgrp->yicon+pworkdata->icon->ptr_icon->height)) )
	{
	 first=1;
	 key.ch[0] = ENTER;
	 break;
	}
 }
}

	if(!refresh_time)
	{
			 cont = 1;
			 if(modify_grp)
			 {
					if(!display)
					{
					 if( local_request(panel,network) )
						error_communication=send_grp(1,index_obj, current_point, group_element, curline, curcol);
					 else
					 {
						if( DIAL_updategrp==1)
						 resume(DIAL);
						while(DIAL_updategrp==1);
						error_communication=send_grp(0,index_obj, current_point, group_element, curline, curcol,panel,network);
						modify_grp_new=1;
					 }
					}
			 }
			 if( local_request(panel,network) )
			 {
				 if(local_panel_old == local_panel)
					update_value_grp_elem(ptr_panel->control_group_elements[current_point].ptrgrp,ptr_panel->control_group_elements[current_point].nr_elements);
			 }
			 else
			 {
				if( !DIAL_updategrp )
				{
					current_point_GRP = current_point;
					panel_GRP = panel;
					network_GRP = network;
					DIAL_updategrp=1;
					DIAL_action=1;
					resume(DIAL);
					cont = 0;
				}
				else
				{
				 if( DIAL_updategrp!=1 )
				 {
					if( DIAL_updategrp==2 ) //OK
					{
					 if( !modify_grp_new )
					 {
						Str_grp_element *buf;
						buf = group_element_temp;
//						memset(group_element,0,MAX_ELEM*sizeof(Str_grp_element));
						index_max=update_length/sizeof(Str_grp_element);
						index_max_group_element=index_max;
//						pgrp = group_element;
						for(i=0; i<index_max;i++)
						{
						 group_element[i]=buf[i];
						}
						cont = 1;
					 }
					 else
					 {
						modify_grp_new = 0;
						cont = 0;
					 }
					}
					else                    //Error
					 cont = 2;
					DIAL_updategrp=0;
				 }
				 else
					cont = 0;
				}
			 }

/*
				{
				 Str_grp_element *buf;
				 buf = group_element_temp;
				 Delay(100);
				 i=0;
				 if((error_communication=net_call(READGROUPELEMENTS_T3000, current_point, (char *)buf, &i, panel, network,NETCALL_NOTTIMEOUT))==SUCCESS)
				 {
					index_max=i/sizeof(Str_grp_element);
					index_max_group_element=index_max;
					pgrp = group_element;
					for(i=0; i<index_max;pgrp++,i++)
					{
					 group_element[i]=buf[i];
					}
				 }
				}
*/
			 if(cont==1)
			 {
				pgrp = group_element;
				for(i=0;i<index_obj;pgrp++,i++)
				{
					if(pgrp->nr_element)
					{
						 print_des(pgrp,grp_workdata+i,panel,network);
					}
				}
			 }
			 if(cont)
			 {
				if( refresh_time_init )	refresh_time = refresh_time_init;
				else
				{
				 if(rtime==4)
					 rtime = 5;
				 else
					 rtime = 4;
				 refresh_time = rtime;
				}
			 }
	}
	if( !DIAL_updategrp )
	{
	 if( timestart+timesec1970 > lastreadopenscreen+15 )
	 {
				 x=1;
				 lastreadopenscreen = timestart+timesec1970;

				 if( local_request(panel,network) )
					openscreen = localopenscreen;
				 else
				 {
					if( (panel_info1.panel_type == T3000 && panel_info1.version >= 221) ||
					 (panel_info1.panel_type == MINI_T3000 && panel_info1.version >= 111) )
					{
					 i = sizeof(Point_Net);
					 if(net_call(COMMAND_50, OPENSCREEN_COMMAND, (char *)&openscreen, &i, panel, network, BACnetConfirmedRequestPDU|NETCALL_NOTTIMEOUT)!=SUCCESS)
						x=0;
					}
				 }
				 if( x && (openscreen.point_type &&	!(openscreen==current_opened_grp)) )
					if( retpoint )
					{
					 if( check_access(openscreen.point_type-1, openscreen.number)!=R_NA )
					 {
						 menu=0;
						 first=1;
						 key.ch[0]=27;  //esc
						 *retpoint=openscreen;
						 esc = openscreen.point_type;
						 break;
					 }
					}
		}
		print_alarm_word();
   }
	}

if( DIAL_updategrp==1)
		 resume(DIAL);
if(!display)
{
	 delete grp_menu;

	if(!error_communication)
//	 if(local_panel)
//	 if((local_panel &&  panel==Station_NUM) || (!local_panel &&  panel==Station_NUM && panel!=station_num))
	 if(modify_grp)
	 {
		if( local_request(panel,network) )
		{
		 if(local_panel_old == local_panel)
			send_grp(1,index_obj, current_point, group_element, curline, curcol);
		}
		else
		{
		 while(DIAL_updategrp==1);
		 send_grp(0,index_obj, current_point, group_element, curline, curcol,panel,network);
		}
	 }

}
if(!error_communication)
{
 pgrp = group_element;
 pworkdata = grp_workdata;
 for(i=0;i<index_obj;pgrp++,pworkdata++,i++)
 {
	if(pworkdata->ptr_save_bkgnd)
	{
//		mfarfree( (HANDLE)FP_SEG(group_element[i].ptr_save_bkgnd));
		mfarfree( pworkdata->ptr_save_bkgnd );
		pworkdata->ptr_save_bkgnd = NULL;
	}
	if( pgrp->icon_present && pworkdata->icon )
	{
		if( !pgrp->default_icon )
			if( pworkdata->icon->ptr_icon )
				delete pworkdata->icon->ptr_icon;
		delete pworkdata->icon;
		pworkdata->icon = NULL;
//		if( ((struct icon huge *)group_element[i].icon)->image_under )
//		{
//			mfarfree( (HANDLE)FP_SEG(((struct icon huge *)group_element[i].icon)->image_under));
//			((struct icon huge *)group_element[i].icon)->image_under = NULL;
//		}
	}
 }
}
} //while esc
mouse_status(stat);
xcur_grp = stat.where.x;
ycur_grp = stat.where.y;
if( !interface_mode )
	set16( init_pal, 0 );
msettextstyle(DEFAULT_FONT, HORIZ_DIR,1);
hide_pointer();
//setbkcolor(Black);
//fond_color=Black;
status_mouse = HIDEMOUSE;
//setfillstyle(SOLID_FILL,Black);
//bar(0,0,639,479);

//cleardevice();
//clearscreenstate(current_opened_grp);
grp_current_pal=NULL;
display_pointer();

//
//if(esc==1 && !prg_active)
//if(!display && !ind_nested_grp)
//{
// G.GShowMenuBar(message);
//G.save=0;
//G.GShowMenuBar(message);
//G.save=1;
//}
///
return esc;
//closegraph();
}



//**********************************
//    class Control_graphic_group_block
//**********************************

Control_graphic_group_block::Control_graphic_group_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
							:Block(pthis, pt, p, net, type, pnum, N_G_GRP, (char *)&line_buf)
	 {
					pgrid = pthis;
					number_of_points=MAX_ELEM;           //MAX_GRPPUT;
					block=group_element;
					r.RecStruct(N_G_GRP,g_grp_struct);
			      h.HSet(N_G_GRP,r.RecStruct(1),number_of_points);
	 }

Control_graphic_group_block::~Control_graphic_group_block()
{
}



int Control_graphic_group_block::Read(int field, char key)
{
 char buf[50];
 int l;
	if(key==DELETE)
		{
			index_cur = current_point;
			delete_elem(current_point, panel, network, point_number, 0);
			pgrid->GGReDrawGrid();
		}
	else
	{
	if( current_point<=index_max_group_element)
	{
	switch (field) {
		case G_GRP_PANEL:
		case G_GRP_TYPE:
		case G_GRP_NUM:
		case G_GRP_SYMBOL:
		case G_GRP_FULL_LABEL:
		case G_GRP_LABEL:
					 index_cur = current_point;
					 if(current_point==index_max_group_element)
							{
							 char *des,*label;
							 if(new_elem(150,100,current_point,panel,network,point_number))
							 {
							  index_max_group_element++;
							  index_max++;
							  setcolor(Black);
							  pgrid->GGPutRecord(pgrid->w_urecord+pgrid->w_record-1,Lightgray,Black);
							 }
							}
					 else
					 {
						 cell(300,20,&group_element[current_point],grp_workdata+current_point,panel,network,0,0);
						 modify_grp=1;
					 }
					 break;
		case G_GRP_VIZIBIL:
						l=(block+current_point)->show_point;
						if (l==1)
							 {
							 strcpy(buf,inviz_point_text);
							 l=0;
							 }
						else
							{
							 strcpy(buf,viz_point_text);
							 l=1;
							}
					 (block+current_point)->show_point=l;
					 PutAlpha(field, buf);
					 break;
		case G_GRP_X:
		case G_GRP_Y:
/*
						 GetAlpha(field, MAX_ALPHA, buf);
						 pthis->GDGets(buf,pthis->w_record,pthis->t_fields[field-1],GetFldSize(field),Black,White);
						 l = atoi(buf);
						 if(field==G_GRP_X)
							{
							 if (l<0 || l>maxx) break;
							 PutAlpha(field, buf);
							 (block+current_point)->graphic_x_coordinate=l;
							}
							else
							{
							 if (l<0 || l>maxy) break;
							 PutAlpha(field, buf);
							 (block+current_point)->graphic_y_coordinate=l;
							}
*/
						 break;
			}
 pgrid->GGPutField(field,Lightgray,Black);
	 }
	}
}

int Control_graphic_group_block::GetRec(void)
{
	int i;
//	if (current_point+1 > number_of_points) return(FX_EOF);
	if (current_point+1 > index_max_group_element)
	{
		 memset(&line_buf,' ',sizeof(struct G_GRP_LineBuf));
		 return 0;
	}
	memset(&line_buf,'\0',sizeof(struct G_GRP_LineBuf));

	for(i=0; i<fields_number; i++)
	{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
	}
	return (FX_SUCCESS);
}

int Control_graphic_group_block::GetField(int field, char *buf)
{
	Point_Net *p;
	int l;

	l=0;
	switch (field) {
		case G_GRP_PANEL:
//					 memcpy(buf,ralign(itoa( ((block+current_point)->point_info.point.panel)+1,xbuf,10),L_G_GRP_PANEL),L_G_GRP_PANEL) ;
					 itoa( ((block+current_point)->point_info.point.panel)+1,buf,10);
					 ralign(buf,L_G_GRP_PANEL);
					 break;
		case G_GRP_TYPE:
		case G_GRP_NUM:
					{
					 byte point_type,point_num;
					 p=&(block+current_point)->point_info.point;
					 point_type = p->point_type-1;
					 point_num = p->number+1;
					 if(field== G_GRP_TYPE)
					 {
						 strcpy(buf, point_cod[point_type]);
						 lalign(buf,L_G_GRP_TYPE);
					 }
					 else
					 {
//						 memcpy(buf,ralign(itoa(point_num ,xbuf,10),3),3);
						 itoa(point_num ,buf,10);
						 ralign(buf,3);
					 }
					}
					break;
		case G_GRP_FULL_LABEL:
						char *des,*label;
						get_point_info(&(block+current_point)->point_info, &des, &label, NULL, NULL, 0, network);
						strcpy(buf, des);
						lalign(buf,L_G_GRP_FULL_LABEL);
						l=L_G_GRP_FULL_LABEL;
				 break;
		case G_GRP_VIZIBIL:
						if ((block+current_point)->show_point==0)
							 strcpy(buf,(char *)inviz_point_text);
						else
							 strcpy(buf,(char *)viz_point_text);
				 break;
		case G_GRP_LABEL:
						get_point_info(&(block+current_point)->point_info, &des, &label, NULL, NULL, 0, network);
						strcpy(buf, label);
						lalign(buf,L_G_GRP_LABEL);
						l=L_G_GRP_LABEL;
				 break;

		case G_GRP_X:
					 l = (block+current_point)->graphic_x_coordinate;
//					 memcpy(buf,ralign(itoa(l,xbuf,10),L_G_GRP_X),L_G_GRP_X);
					 itoa(l,buf,10);
					 ralign(buf,L_G_GRP_X);
				 break;
		case G_GRP_Y:
					 l = (block+current_point)->graphic_y_coordinate;
//					 memcpy(buf,ralign(itoa(l,xbuf,10),L_G_GRP_Y),L_G_GRP_Y);
					 itoa(l,buf,10);
					 ralign(buf,L_G_GRP_Y);
					 break;
		case G_GRP_SYMBOL:
					 if ( (block+current_point)->icon_present )
					 {
						 if ( (block+current_point)->default_icon )
							 strcpy(buf, default_text_icon);
						 else
							 strcpy(buf, icon_name_table[(block+current_point)->icon_name_index] );
						 lalign(buf,L_G_GRP_SYMBOL);
					 }
					 break;
		}

 return l;
}
void memsize(void)
{
 GWindow *D=NULL;
/*
						set_semaphore_dos();
						asm {
								 mov ah,48h
								 mov bx,0ffffh
								 int 21h
								 }
						unsigned long nr =(unsigned long)_BX*16L;
						clear_semaphore_dos();
*/
						set_semaphore_dos();
						unsigned long core= (unsigned long) coreleft();
						clear_semaphore_dos();

						 char xbuf[60];
						 strcpy(xbuf,"the top of the heap is bytes ");
						 ltoa(core,&xbuf[strlen(xbuf)],10);
						 if(mode_text)
						 {
							DisplayMessageT(17, 10, 63, 14, NULL, xbuf,&D);
//			Delay(3200);
//			if(D) DeleteMessage(D);
/*
							xbuf[0]=0;
							if( Routing_table[0].ptr )
							{
								itoa( ((Header_pool *)(	((Serial *)Routing_table[0].ptr)->ser_pool.buf ))->length
									,xbuf,10);
							}
						 strcat(xbuf,"  ");
							if( Routing_table[1].ptr )
							{
								itoa( ((Header_pool *)(	((Serial *)Routing_table[1].ptr)->ser_pool.buf ))->length
									,&xbuf[strlen(xbuf)],10);
							}
						 strcat(xbuf,"  ");
						 for(int i=0; i<MAXServerTSMTable; i++)
						 {
							itoa( ServerTSMTable.table[i].state, &xbuf[strlen(xbuf)], 10);
						 }
						 DisplayMessage(17, 10, 63, 14, NULL, xbuf,&D);
*/
//			Delay(3200);


//						 mxyputs(3,2,"the top of the heap is bytes ");
//						 mxyputs(35,2,ltoa(core,xbuf,10));
//						 mxyputs(3,3,"     Large mem: ");
//						 mxyputs(20,3,ltoa(nr,xbuf,10));
							Delay(1000);
							if(D) DeleteMessage(D);
              D = NULL;
							strcpy(xbuf,"Remote points OUT: ");
							itoa(remote_points_OUT,&xbuf[strlen(xbuf)],10);
							DisplayMessageT(17, 10, 63, 14, NULL, xbuf,&D);
						 }
						 else
						 {
//						 setcolor(Darkgray);
//						 outtextxy(3,30,"ллллллллллллллллллллллллллллллллллллллллллллл");
//						 outtextxy(3,50,"ллллллллллллллллллллллллллллллллллллллллллллл");
						 setcolor(White);
//						 outtextxy(3,30,ltoa(core,xbuf,10));
//						 outtextxy(3,50,ltoa(nr,xbuf,10));
							DisplayMessage(170, 170, 500, 230, NULL, xbuf,&D);
						 }
			Delay(1000);
			if(D) DeleteMessage(D);

//  while(!bioskey_new(1));
//  int i=bioskey_new(0);
}


Station_block::Station_block(GGrid *pthis, byte pt, byte p, int net, signed char type, byte pnum)
							:Block(pthis, pt, p, net, type, pnum, (type==STATION?N_ST:N_CST), (char *)&line_buf)
	 {
			stype=type;
			pgrid = pthis;
			number_of_points=32;           //MAX_GRPPUT;
			set_semaphore_dos();
			block=new Station_point[number_of_points];
			clear_semaphore_dos();
			if(pstation_list_sel)
				memmove(block,pstation_list_sel,number_of_points*sizeof(Station_point));
			else
				memset(block,'\0',number_of_points*sizeof(Station_point));

			for(int i=0; i<32; i++)
			{
			  if(	(*pactivepanels)&(1L<<i) )
				  (block+i)->state = 1;
			}
/*
#ifdef NEW
					memmove(block,station_list,number_of_points*sizeof(Station_point));
#endif
*/
			if(stype==STATION)
				r.RecStruct(N_ST,st_struct);
			else
				r.RecStruct(N_CST,cst_struct);

			h.HSet((stype==STATION?N_ST:N_CST),r.RecStruct(1),number_of_points);
	 }

Station_block::~Station_block()
{
	set_semaphore_dos();
	if(block)
	{
	 delete block;
  }
  clear_semaphore_dos();
}

int Station_block::Read(int field, char key)
{
 char buf[50],d[2];
 int l;
	if(key==DELETE && stype==STATION)
		{
		 {
			GWindow w(26,10,48,14,0,0);
			w.GWSet("",Lightblue,Blue);
			w.GShowWindow(0);
			w.GWPuts(1,3,"Delete?(Y/N): ",Lightblue,White);
			w.GWPuts(1,17," ",Lightgray,Black);
			w.GWGoto(1,17);
//		 mtextcolor(White);
			mgets(d,1,Black,White);
			w.GReleaseWindow();
		 }

		 if(d[0]=='Y')
		 {
			(block+current_point)->name[0]=0;
			pgrid->FGetRec(pgrid->fh,pgrid->obj);
			pgrid->w_record = current_point+1;
//		 pgrid->GWGoto(current_point,1);
			pgrid->GGPutField(field,Lightgray,Black);

//			for(int j=current_point;j<ind_station-1;j++)
//				station_list[j] = station_list[j+1];
//			if(ind_station) ind_station--;
//			pgrid->GGReDrawGrid();
		 }
		}
	else
	{
	if(stype==CSTATION)
	{
//	 if((block+current_point)->state || (!control && !(block+current_point)->state) )
	 if((block+current_point)->state)
	 {
/*
		if(local_panel)
		if( !(block+ocurrent_point)->state )
		{
		  (block+current_point)->state=0;
			Station_NUM = ocurrent_point+1;
		  (block+ocurrent_point)->state=1;
		}
*/
		if(panel_sel_tmp)
		{
		 l=current_point;
		 current_point = panel_sel_tmp-1;
//		 pgrid->w_record = panel_sel_tmp;
		 pgrid->FGetRec(pgrid->fh,pgrid->obj);
		 pgrid->GWGoto(pgrid->w_record,1);
		 pgrid->GGPutField(field,Lightgray,Black);
		 current_point = l;
		}

//		 current_point = ocurrent_point;
		panel_sel_tmp = current_point+1;
//		station_num = current_point+1;
//		ptr_panel->GlPanel=station_num;
//		memcpy(station_name,lalign((block+current_point)->name,L_ST_NAME),L_ST_NAME);
//		memcpy(station_name_select,lalign((block+current_point)->name,L_ST_NAME),L_ST_NAME);
//		pgrid->w_record = station_num;
//		pgrid->w_record = panel_sel_tmp;
		pgrid->FGetRec(pgrid->fh,pgrid->obj);
//	 textcolor(Lightred);
		pgrid->GWGoto(pgrid->w_record,1);
		pgrid->GGPutField(field,Lightgray,Lightred);

//		if(station_num==Station_NUM) local_panel=1;
//		else local_panel=0;
	 }
	}
	else
	{
	switch (field) {
		case ST_NAME:
					 GetAlpha(field, MAX_ALPHA, buf);
					 pgrid->GDGets(buf,pgrid->w_record,pgrid->t_fields[field-1],GetFldSize(field),Black,White);
					 PutAlpha(field, buf);
					 memcpy((block+current_point)->name,lalign(buf,L_ST_NAME),L_ST_NAME);
					 break;
		case ST_COD:
//					 GetAlpha(field, MAX_ALPHA, buf);
//					 pthis->GDGets(buf,pthis->w_record,pthis->t_fields[field-1],GetFldSize(field),Black,White);
//					 l = atoi(buf);
//					 PutAlpha(field, buf);
//					 (block+current_point)->cod=l;
					 break;
			}
		pgrid->GGPutField(field,Lightgray,Black);
	 }
	}
}

int Station_block::GetRec(void)
{
	int i;
	if (current_point+1 > number_of_points) return(FX_EOF);

	if(stype==STATION)
		memset(&line_buf,'\0',sizeof(struct ST_LineBuf));
	else
		memset(&line_buf,'\0',sizeof(struct CST_LineBuf));

	for(i=0; i<fields_number; i++)
		{
		GetField(i+1, ((char *)&line_buf)+r.RecStruct(i+1)->position-1);
		}
//	 if(!memcmp((char *)&line_buf.st_name[stype==STATION?0:1], station_name, strlen(station_name)))
	 if( panel_sel_tmp && (panel_sel_tmp-1==current_point) )
		 pgrid->fground=Lightred;
	return (FX_SUCCESS);
}

int Station_block::GetField(int field, char *buf)
{
	int l;

	l=0;
	if(stype==CSTATION)
	{
		 l=1;
/*
		 for(int i=0;i<bank;i++)
				l += tbl_bank[PRG][i+1];
*/
//		 memcpy(buf,ralign(itoa(l+current_point,buf,10),3),3);
		 itoa(l+current_point,buf,10);
		 ralign(buf,3);
		 buf[3]=' ';
		 memcpy(&buf[4] , lalign((block+current_point)->name,L_ST_NAME),L_ST_NAME);
		 buf[20]=' ';
		 if((block+current_point)->state)
			 memcpy(&buf[21] , on, L_ST_STATUS);
		 else
			 memcpy(&buf[21] , off, L_ST_STATUS);
	}
	else
	switch (field) {
		case ST_NAME:
						memcpy(buf , lalign((block+current_point)->name,L_ST_NAME),L_ST_NAME);
						l=L_ST_NAME;
					 break;
		case ST_COD:
					{
					 l=1;
/*
					 for(int i=0;i<bank;i++)
							l += tbl_bank[PRG][i+1];
*/
					 memcpy(buf,ralign(itoa(l+current_point,buf,10),3),3);
					}
				 break;
//					 memcpy(buf,ralign(itoa((block+current_point)->cod,buf,10),L_ST_COD),L_ST_COD) ;
		case ST_STATUS:
				 if((block+current_point)->state)
					 memcpy(buf , on, L_ST_STATUS);
				 else
					 memcpy(buf , off, L_ST_STATUS);
				 break;
		case ST_VERSION:
//					 itoa((block+current_point)->version/100, buf, 10);
//					 strcat(buf, ".");
//					 itoa((block+current_point)->version%100, &buf[strlen(buf)], 10);
//					 l=L_ST_VERSION;
					 break;
		}
 return l;
}



int	repeat_grp(void)
{
 int exit=0,t=0;
 while(!bioskey_new(1))
 {
	char i = 0;
	while(1)
	 if (ptr_panel->control_group_elements[i].nr_elements)
	 {
//			display_grp_time=200;
			int r=fnc_group(&ptr_panel->control_groups[i],NULL,i,INDIVIDUAL,Station_NUM,NetworkAddress,1,NULL);
			if(r==1)
				{
				 exit = 1;
				 break;
				}
			if(r==PGDN)
				if(++i>=MAX_GRPS) i=0;
			if(r==PGUP)
				if(i--==0) i=(char)(MAX_GRPS-1);
			if(r==0)
				if(++i>=MAX_GRPS) i=0;
	 }
	 else
		if(++i>=MAX_GRPS)
		{
		 if(!t)
		 {
			 exit = 1;
			 break;
		 }
		 i=0;
		}

	 if(exit) break;
 }
}


int amon_routine(byte num_point,byte num_panel,int network,int call_type,int x,GGrid *pgrid)
{
 int s=0, local=0;
 Str_monitor_point buf;
 if(!mode_text && call_type!=INDIVIDUAL)
	 pgrid->RestoreArea();

 num_point--;
 int old_mode=MODE_GRAPHIC;
 if(mode_text)
 {
	old_mode=MODE_TEXT;
	mode_text = MODE_GRAPHIC;
	hide_pointer();
  restorechar();
	setgraphmode(getgraphmode());
	Green=GREEN;                 //2
	White=WHITE; 						 //5
	Darkgray=DARKGRAY;                 //6
	Brown=BROWN;           //8
	Lightblue=LIGHTBLUE;         //9
	Magenta=MAGENTA;                 //15
	fond_color=Black;
	asm {
	 mov ax,21h
	 int 33h
	 }
	display_pointer();
	move_mouse(1,23);
 }
				 hide_pointer();
				 msettextstyle(DEFAULT_FONT, HORIZ_DIR,1);
				 prectangle(2,2,maxx-2,maxy-2, Lightred);
				 prectangle(1,1,maxx-1,maxy-1, Lightred);
				 setcolor(Black);
				 display_pointer();
				 mode_text = MODE_GRAPHIC;

					if( local_request(num_panel,network) )
					{
							 memmove(amon_inputs, ptr_panel->analog_mon[num_point].inputs, sizeof(amon_inputs));
							 current_analog_mon = &ptr_panel->analog_mon[num_point];
							 current_mon_workdata = &ptr_panel->monitor_work_data[num_point];
							 local = 1;
					}
					else
					{
					 if(call_type!=INDIVIDUAL)
					 {
							 memmove(amon_inputs, pgrid->obj.amon->block[num_point].inputs, sizeof(amon_inputs));
							 current_analog_mon = &pgrid->obj.amon->block[num_point];
//							 s=net_call(20, ((num_panel-1)<<11)+ ((AMON+1)<<7)+ num_point, (char *)current_analog_mon, 0, num_panel, networkaddress);
//							 current_mon_workdata = &ptr_panel->monitor_work_data[num_point];
					 }
					 else
					 {
						 current_analog_mon = &buf;
						 Delay(100);
						 s=net_call(20, ((AMON+1)<<8)+ num_point, (char *)current_analog_mon, 0, num_panel, network,NETCALL_RETRY);
						 if(!s) memmove(amon_inputs, current_analog_mon->inputs, sizeof(amon_inputs));
					 }
					}
				if(!s && current_analog_mon->num_inputs)
				{
				 int x=0;
				 if(monitor_accessed) x=1;
				 else monitor_accessed++;
				 current_mon=num_point+1;

// ********  the old code  ********
				 GGraph *wgraph=new GGraph(3,3,maxx-3,maxy-3,0,num_panel,network,local);
// ********************************

// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.039  ********
// ********       begin       ********
// ***********************************
//				 GGraph *wgraph=new GGraph(401,"need help",3,3,maxx-3,maxy-3,0,num_panel,network,local);
// ***********************************
// ********      mao hui      ********
// ********  1997.8.4 NO.039  ********
// ********        end        ********
// ***********************************

				 wgraph->spot=5;
				 wgraph->save=0;
				 wgraph->GWSet(NULL,Lightgray,Lightgray);
				 wgraph->GShowGraph(5);
				 while (!wgraph->HandleEvent())
				 {
					print_alarm_word();
				 }
//				 set_semaphore_dos();
				 delete wgraph;
//				 clear_semaphore_dos();
				 if(pgrid)
				 {
					Str_monitor_point *p;
					p=&pgrid->obj.amon->block[num_point];
					p->ind_views=current_analog_mon->ind_views;
					memcpy(p->views, current_analog_mon->views, MAX_VIEWS*sizeof(Views));
				 }
				 if(!x) monitor_accessed--;
				}
current_mon=0;
// set_semaphore(&screen);
msettextstyle(DEFAULT_FONT, HORIZ_DIR,1);
hide_pointer();
setbkcolor(Black);
fond_color=Black;
cleardevice();
// clear_semaphore(&screen);
if(old_mode==MODE_TEXT)
{
mode_text = MODE_TEXT;
lat_char_n = 1;
lung_char_n = 1;
hide_pointer();
set_semaphore_dos();
restorecrtmode();
changechar();
clear_semaphore_dos();
clrscr();
set_vid_mem();

Green=LIGHTBLUE;                 //2
White=MAGENTA;                 //15
Darkgray=BROWN;           //8
Lightblue=GREEN;         //9

fond_color=TEXT_FOND_COLOR;
setregister(1);
asm {
	 mov ax,21h
	 int 33h
	 }
	setmousetext();
	move_mouse(40,19);
	display_pointer();
//mouse_installed();
}
else
{
hide_pointer();
				 fond_color = Black;
/*
				 setcolor(Darkgray);
				 setfillstyle(SOLID_FILL,fond_color);
				 bar(0,0,maxx,maxy);
				 prectangle(2,2,maxx-2,maxy-2,Darkgray);
				 setcolor(White);
				 prectangle(1,1,maxx-1,maxy-1,White);
*/
				 setcolor(Black);

	display_pointer();
}

			 if(call_type!=INDIVIDUAL)
			 {
			 if(mode_text)
				clear_color(1, 80, 1, 25, lin_text, fond_color, Black);
/*
				for( int y=1;y<=25;y++)
				{
					mxyputs(1,y,lin_text,fond_color,Black);
				}
*/
			 int old_rec=pgrid->w_record;
			 int old_field=pgrid->w_field;
//				pgrid->w_nfields = 0;
//				pgrid->w_field = 1;
				pgrid->t_fields[pgrid->w_lfield-1]=1;
//				pgrid->RestoreArea();
				pgrid->on_screen=0;
				if (mode_text)
					 pgrid->save=0;
				pgrid->GShowGrid();
				if (mode_text)
					 pgrid->save=1;
				pgrid->GGHideCur(Black);
				pgrid->w_record = old_rec;
				pgrid->w_field = old_field;
				pgrid->GGShowCur(Black);
				initamoninputsscreen();
				}

//G.save=0;
//G.GShowMenuBar(message);
//G.save=1;

}
