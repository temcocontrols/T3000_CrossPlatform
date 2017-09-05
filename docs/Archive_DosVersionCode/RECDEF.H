#ifndef _RECDEF_H
#define _RECDEF_H

#include "fxengine.h"

#define FULL_LABEL      20
#define LABEL            8
#define MAX_ANNUAL_ARRAY  50


#define OUT_NUM         1
#define OUT_FULL_LABEL  2
#define OUT_AUTO_MAN    3
#define OUT_VALUE       4
#define OUT_UNITS       5
#define OUT_RANGE       6
#define OUT_LOW         7
#define OUT_HIGH        8
//#define OUT_M_DEL       9
//#define OUT_S_DEL       10
//#define OUT_SEC_LEVEL   11
#define OUT_DECOM       9
#define OUT_LABEL       10
#define N_OUT           10         // NUMBER OF FIELDS

#define L_OUT_NUM         3
#define L_OUT_FULL_LABEL  FULL_LABEL
#define L_OUT_AUTO_MAN    4
#define L_OUT_VALUE       10
#define L_OUT_UNITS       5
#define L_OUT_RANGE       12
#define L_OUT_LOW         4
#define L_OUT_HIGH        4
#define L_OUT_M_DEL       4
#define L_OUT_S_DEL       4
#define L_OUT_SEC_LEVEL   4
#define L_OUT_DECOM       1
#define L_OUT_LABEL       LABEL

struct OUT_LineBuf {
		char num[L_OUT_NUM];           // 'N',17,3,0},
		char full_label[L_OUT_FULL_LABEL];   //  ",'C',20,20,0},
		char auto_man[L_OUT_AUTO_MAN];//",'C',53,4,0},
		char value[L_OUT_VALUE];//",'F',40,8,2},
		char units[L_OUT_UNITS];//" ,'C',48,5,0},
		char range[L_OUT_RANGE];//",'C',73,12,0},
		char low[L_OUT_LOW];//",'C',73,12,0},
		char high[L_OUT_HIGH];//",'C',73,12,0},
//		char m_del[L_OUT_M_DEL];//",'N',85,4,0},
//		char s_del[L_OUT_S_DEL];//",'N',89,4,0},
//		char sec_level[L_OUT_SEC_LEVEL];//",'N',61,4,0},
		char decom[L_OUT_DECOM];//",'N',69,4,0},
		char label[L_OUT_LABEL];//" ,'C',97,8,0},
	 };

#define IN_NUM         1
#define IN_FULL_LABEL  2
#define IN_AUTO_MAN    3
#define IN_VALUE       4
#define IN_UNITS       5
#define IN_RANGE       6
#define IN_CALIBR      7
#define IN_FILTER      8
#define IN_DECOM       9
#define IN_LABEL       10
#define N_IN           10         // NUMBER OF FIELDS

#define L_IN_NUM         3
#define L_IN_FULL_LABEL  FULL_LABEL
#define L_IN_AUTO_MAN    4
#define L_IN_VALUE       7
#define L_IN_UNITS       5
#define L_IN_RANGE       12
#define L_IN_CALIBR      5
#define L_IN_FILTER      3
#define L_IN_DECOM       1
#define L_IN_LABEL       LABEL

struct IN_LineBuf {
		char num[L_IN_NUM];
		char full_label[L_IN_FULL_LABEL];
		char auto_man[L_IN_AUTO_MAN];
		char value[L_IN_VALUE];
		char units[L_IN_UNITS];
		char range[L_IN_RANGE];
		char calibr[L_IN_CALIBR];
		char filter[L_IN_FILTER];
		char decom[L_IN_DECOM];
		char label[L_IN_LABEL];
	 };

#define VAR_NUM         1
#define VAR_FULL_LABEL  2
#define VAR_AUTO_MAN    3
#define VAR_VALUE       4
#define VAR_UNITS       5
#define VAR_LABEL       6
#define N_VAR           6         // NUMBER OF FIELDS

#define L_VAR_NUM         3
#define L_VAR_FULL_LABEL  FULL_LABEL
#define L_VAR_AUTO_MAN    4
#define L_VAR_VALUE       12
#define L_VAR_UNITS       10
#define L_VAR_LABEL       LABEL

struct VAR_LineBuf {
		char num[L_VAR_NUM];
		char full_label[L_VAR_FULL_LABEL];
		char auto_man[L_VAR_AUTO_MAN];
		char value[L_VAR_VALUE];
		char units[L_VAR_UNITS];
		char label[L_VAR_LABEL];
	 };

#define CON_NUM         1
#define CON_INPUT       2
#define CON_VALUE       3
#define CON_INUNITS     4
#define CON_AUTO_MAN    5
#define CON_OUTPUT      6
//#define CON_OUTUNITS    7
#define CON_SETPOINT    7
#define CON_SETPOINTV   8
#define CON_UNITS       9
#define CON_ACTION      10
#define CON_PROP        11
#define CON_RESET       12
#define CON_RATE        13
#define CON_BIAS        14
#define CON_NUM1        15
#define N_CON           15         // NUMBER OF FIELDS

#define L_CON_NUM         3
#define L_CON_INPUT       8
#define L_CON_VALUE       5
#define L_CON_INUNITS     5
#define L_CON_AUTO_MAN    4
#define L_CON_OUTPUT      7
//#define L_CON_OUTUNITS    1
#define L_CON_SETPOINT    8
#define L_CON_SETPOINTV   6
#define L_CON_UNITS       5
#define L_CON_AUTO_MAN    4
#define L_CON_ACTION      1
#define L_CON_PROP        4
#define L_CON_RESET       4
#define L_CON_RATE        4
#define L_CON_BIAS        4

struct CON_LineBuf {
		char num[L_CON_NUM];
		char input[L_CON_INPUT];
		char value[L_CON_VALUE];
		char inunits[L_CON_INUNITS];
		char auto_man[L_CON_AUTO_MAN];
		char output[L_CON_OUTPUT];
//		char outunits[L_CON_OUTUNITS];
		char setpoint[L_CON_SETPOINT];
		char setpointv[L_CON_SETPOINTV];
		char units[L_CON_UNITS];
		char action[L_CON_ACTION];
		char prop[L_CON_PROP];
		char reset[L_CON_RESET];
		char rate[L_CON_RATE];
		char bias[L_CON_BIAS];
		char num1[L_CON_NUM];
	 };

#define WR_NUM         1
#define WR_FULL_LABEL  2
#define WR_AUTO_MAN    3
#define WR_VALUE       4
#define WR_OVERRIDE1   5
#define WR_OR1VALUE    6
#define WR_OVERRIDE2   7
#define WR_OR2VALUE    8
#define WR_LABEL       9
#define N_WR           9         // NUMBER OF FIELDS

#define L_WR_NUM         2
#define L_WR_FULL_LABEL  FULL_LABEL
#define L_WR_AUTO_MAN    4
#define L_WR_VALUE       3
#define L_WR_OVERRIDE1   8
#define L_WR_OR1VALUE    3
#define L_WR_OVERRIDE2   8
#define L_WR_OR2VALUE    3
#define L_WR_LABEL       LABEL

struct WR_LineBuf {
		char num[L_WR_NUM];
		char full_label[L_WR_FULL_LABEL];
		char auto_man[L_WR_AUTO_MAN];
		char value[L_WR_VALUE];
		char override1[L_WR_OVERRIDE1];
		char or1value[L_WR_OR1VALUE];
		char override2[L_WR_OVERRIDE2];
		char or2value[L_WR_OR2VALUE];
		char label[L_WR_LABEL];
	 };

#define WR_TIME0          1
#define WR_TIME_MON       2
#define WR_TIME_TUE       3
#define WR_TIME_WED       4
#define WR_TIME_THU       5
#define WR_TIME_FRI       6
#define WR_TIME_SAT       7
#define WR_TIME_SUN       8
#define WR_TIME_OR1       9
#define WR_TIME_OR2       10
#define N_WR_TIME         10         // NUMBER OF FIELDS

struct WR_TIME_LineBuf {
		char onoff[3] ;
		char mon[5];
		char tue[5];
		char wed[5];
		char thu[5];
		char fri[5];
		char sat[5];
		char sun[5];
		char or1[5];
		char or2[5];
	 };

#define AR_NUM         1
#define AR_FULL_LABEL  2
#define AR_AUTO_MAN    3
#define AR_VALUE       4
#define AR_LABEL       5
#define N_AR           5         // NUMBER OF FIELDS

#define L_AR_NUM         3
#define L_AR_FULL_LABEL  FULL_LABEL
#define L_AR_AUTO_MAN    4
#define L_AR_VALUE       3
#define L_AR_LABEL       LABEL

struct AR_LineBuf {
		char num[L_AR_NUM];
		char full_label[L_AR_FULL_LABEL];
		char auto_man[L_AR_AUTO_MAN];
		char value[L_AR_VALUE];
		char label[L_AR_LABEL];
	 };

#define AR1_Y_SUN     1
#define AR1_Y_MON     2
#define AR1_Y_TUE     3
#define AR1_Y_WED     4
#define AR1_Y_THU     5
#define AR1_Y_FRI     6
#define AR1_Y_SAT     7
#define AR1_Y_SP      8
#define AR2_Y_SUN     9
#define AR2_Y_MON     10
#define AR2_Y_TUE     11
#define AR2_Y_WED     12
#define AR2_Y_THU     13
#define AR2_Y_FRI     14
#define AR2_Y_SAT     15
#define AR2_Y_SP      16
#define AR3_Y_SUN     17
#define AR3_Y_MON     18
#define AR3_Y_TUE     19
#define AR3_Y_WED     20
#define AR3_Y_THU     21
#define AR3_Y_FRI     22
#define AR3_Y_SAT     23
#define AR3_Y_SP      24

#define N_Y_AR       24         // NUMBER OF FIELDS

struct AR_Y_LineBuf {
		char sun1[2];
		char mon1[2];
		char tue1[2];
		char wed1[2];
		char thu1[2];
		char fri1[2];
		char sat1[2];
		char sp1[1];
		char sun2[2];
		char mon2[2];
		char tue2[2];
		char wed2[2];
		char thu2[2];
		char fri2[2];
		char sat2[2];
		char sp2[1];
		char sun3[2];
		char mon3[2];
		char tue3[2];
		char wed3[2];
		char thu3[2];
		char fri3[2];
		char sat3[2];
		char sp3[1];
	 };


#define PRG_NUM         1
#define PRG_FULL_LABEL  2
#define PRG_STATUS      3
#define PRG_AUTO_MAN    4
//#define PRG_TIMER       5
//#define PRG_REPMIN      6
//#define PRG_REPSEC      7
//#define PRG_REMMIN      8
//#define PRG_REMSEC      9
#define PRG_SIZE        5
#define PRG_EXIT        6
#define PRG_LABEL       7
//#define PRG_NUM1        13
#define N_PRG           7         // NUMBER OF FIELDS

#define L_PRG_NUM         3
#define L_PRG_FULL_LABEL  FULL_LABEL
#define L_PRG_STATUS      4
#define L_PRG_AUTO_MAN    4
#define L_PRG_TIMER       7
#define L_PRG_REPMIN      3
#define L_PRG_REPSEC      2
#define L_PRG_REMMIN      3
#define L_PRG_REMSEC      2
#define L_PRG_SIZE        4
#define L_PRG_EXIT        7
#define L_PRG_LABEL       LABEL

struct PRG_LineBuf {
		char num[L_PRG_NUM];
		char full_label[L_PRG_FULL_LABEL];
		char status[L_PRG_STATUS];
		char auto_man[L_PRG_AUTO_MAN];
//		char timer[L_PRG_TIMER];
//		char repmin[L_PRG_REPMIN];
//		char repsec[L_PRG_REPSEC];
//		char remmin[L_PRG_REMMIN];
//		char remsec[L_PRG_REMSEC];
		char size[L_PRG_SIZE];
		char exit[L_PRG_EXIT];
		char label[L_PRG_LABEL];
	 };

#define TBL_VALUE1      1
#define TBL_UNIT1       2
#define N_TBL           2         // NUMBER OF FIELDS

#define L_TBL_VALUE1      5
#define L_TBL_UNIT1       9


struct TBL_LineBuf {
		char value1[L_TBL_VALUE1];
		char unit1[L_TBL_UNIT1];
	 };

#define DMON_NUM         1
#define DMON_INPUT       2
#define DMON_ONTIME      3
#define DMON_STARTDATE   4
#define DMON_LENGTH      5
#define DMON_TOTAL       6
#define DMON_DAY         7
#define N_DMON           7         // NUMBER OF FIELDS

#define L_DMON_PANEL       3
#define L_DMON_PANEL_TYPE  4
#define L_DMON_SUB_PANEL   3
#define L_DMON_TYPE        5
#define L_DMON_NUM         3
#define L_DMON_INPUT       10
#define L_DMON_ONTIME      8
#define L_DMON_STARTDATE   11
#define L_DMON_LENGTH      6
#define L_DMON_TOTAL       4
#define L_DMON_DAY         4

struct DMON_LineBuf {
		char num[L_DMON_NUM];
		char input[L_DMON_INPUT];
		char ontime[L_DMON_ONTIME];
		char startdate[L_DMON_STARTDATE];
		char length[L_DMON_LENGTH];
		char total[L_DMON_TOTAL];
		char day[L_DMON_DAY];
	 };

#define AMON_NUM         1
#define AMON_LABEL       2
#define AMON_INTERVAL    3
#define AMON_LENGTH      4
#define AMON_UNITS       5
#define AMON_SIZE        6
#define AMON_STATUS      7
#define N_AMON           7         // NUMBER OF FIELDS

#define L_AMON_NUM         3
#define L_AMON_LABEL       8
#define L_AMON_INPUT1      8
#define L_AMON_INPUT2      8
#define L_AMON_INPUT3      8
#define L_AMON_INPUT4      8
#define L_AMON_INPUT5      8
#define L_AMON_INPUT6      8
#define L_AMON_INTERVAL    8
#define L_AMON_LENGTH      3
#define L_AMON_UNITS       6
#define L_AMON_SIZE        7
#define L_AMON_STATUS      3

struct AMON_LineBuf {
		char num[L_AMON_NUM];
		char label[L_AMON_LABEL];
		char interval[L_AMON_INTERVAL];
		char length[L_AMON_LENGTH];
		char units[L_AMON_UNITS];
		char size[L_AMON_SIZE];
		char status[L_AMON_STATUS];
	 };

#define AMON_INPUT        1
#define N_AMON_INPUT           1         // NUMBER OF FIELDS

#define L_AMON_INPUT	  8

struct AMON_INPUT_LineBuf {
		char amon_input[L_AMON_INPUT ] ;
	 };


#define GRP_NUM         1
#define GRP_FULL_LABEL  2
#define GRP_LABEL       3
#define GRP_PICFILE     4
#define GRP_MODE        5
#define GRP_UPDATE      6
#define N_GRP           6         // NUMBER OF FIELDS

#define L_GRP_NUM         3
#define L_GRP_FULL_LABEL  FULL_LABEL
#define L_GRP_LABEL       LABEL
#define L_GRP_PICFILE     8
#define L_GRP_MODE        7
#define L_GRP_UPDATE      3

struct GRP_LineBuf {
		char num[L_GRP_NUM];
		char full_label[L_GRP_FULL_LABEL];
		char label[L_GRP_LABEL];
		char picfile[L_GRP_PICFILE];
		char mode[L_GRP_MODE];
		char update_time[L_GRP_UPDATE];
	 };

#define G_GRP_PANEL       1
#define G_GRP_TYPE        2
#define G_GRP_NUM         3
#define G_GRP_FULL_LABEL  4
#define G_GRP_LABEL       5
#define G_GRP_VIZIBIL     6
#define G_GRP_X           7
#define G_GRP_Y           8
#define G_GRP_SYMBOL      9
#define N_G_GRP           9         // NUMBER OF FIELDS

#define L_G_GRP_PANEL       3
#define L_G_GRP_TYPE        5
#define L_G_GRP_NUM         3
#define L_G_GRP_FULL_LABEL  FULL_LABEL
#define L_G_GRP_LABEL       LABEL
#define L_G_GRP_VIZIBIL     5
#define L_G_GRP_X           3
#define L_G_GRP_Y           3
#define L_G_GRP_SYMBOL      12

struct G_GRP_LineBuf {
		char panel[L_G_GRP_PANEL] ;
		char type[L_G_GRP_TYPE];
		char num[L_G_GRP_NUM];
		char full_label[L_G_GRP_FULL_LABEL];
		char label[L_G_GRP_LABEL];
		char vizibil[L_G_GRP_VIZIBIL];
		char x[L_G_GRP_X];
		char y[L_G_GRP_Y];
		char symbol[L_G_GRP_SYMBOL];
	 };


#define STATUS_PANEL       1
#define STATUS_PANEL_TYPE  2
#define STATUS_SUB_PANEL   3
#define STATUS_TYPE        4
#define STATUS_NUM         5
#define STATUS_NAME        6
#define STATUS_NET         7
#define STATUS_PROGRAM     8
#define STATUS_VERSION     9
#define STATUS_SCANS       10
#define STATUS_NETIN       11
#define STATUS_NETOUT      12
#define STATUS_MEMORY      13
#define N_STATUS           13         // NUMBER OF FIELDS

#define L_STATUS_PANEL       3
#define L_STATUS_PANEL_TYPE  4
#define L_STATUS_SUB_PANEL   3
#define L_STATUS_TYPE        5
#define L_STATUS_NUM         3
#define L_STATUS_NAME        20
#define L_STATUS_NET         3
#define L_STATUS_PROGRAM     3
#define L_STATUS_VERSION     4
#define L_STATUS_SCANS       4
#define L_STATUS_NETIN       4
#define L_STATUS_NETOUT      4
#define L_STATUS_MEMORY      4

struct STATUS_LineBuf {
		char panel[L_STATUS_PANEL] ;
		char panel_type[L_STATUS_PANEL_TYPE];
		char sub_panel[L_STATUS_SUB_PANEL];
		char type[L_STATUS_TYPE];
		char num[L_STATUS_NUM];
		char name[L_STATUS_NAME];
		char net[L_STATUS_NET];
		char program[L_STATUS_PROGRAM];
		char version[L_STATUS_VERSION];
		char scans[L_STATUS_SCANS];
		char netin[L_STATUS_NETIN];
		char netout[L_STATUS_NETOUT];
		char memory[L_STATUS_MEMORY];
	 };

#define PASS_PANEL       1
#define PASS_PANEL_TYPE  2
#define PASS_SUB_PANEL   3
#define PASS_TYPE        4
#define PASS_NUM         5
#define PASS_NAME        6
#define PASS_CODE        7
#define PASS_GROUP       8
#define PASS_LEVEL       9
#define PASS_MENU        10
#define N_PASS           10         // NUMBER OF FIELDS

#define L_PASS_PANEL       3
#define L_PASS_PANEL_TYPE  4
#define L_PASS_SUB_PANEL   3
#define L_PASS_TYPE        5
#define L_PASS_NUM         3
#define L_PASS_NAME        8
#define L_PASS_CODE        6
#define L_PASS_GROUP       4
#define L_PASS_LEVEL       4
#define L_PASS_MENU        4

struct PASS_LineBuf {
		char panel[L_PASS_PANEL] ;
		char panel_type[L_PASS_PANEL_TYPE];
		char sub_panel[L_PASS_SUB_PANEL];
		char type[L_PASS_TYPE];
		char num[L_PASS_NUM];
		char name[L_PASS_NAME];
		char code[L_PASS_CODE];
		char group[L_PASS_GROUP];
		char level[L_PASS_LEVEL];
		char menu[L_PASS_MENU];
	 };


#define USERS_NAME        1
#define N_USER_NAME           1         // NUMBER OF FIELDS

#define L_USER_NAME	  15

struct USER_NAME_LineBuf {
		char user_name[L_USER_NAME] ;
	 };

#define ST_COD         1
#define ST_NAME        2
#define ST_STATUS      3
#define ST_VERSION     4
#define N_ST    4         // NUMBER OF FIELDS

#define L_ST_COD	     3
#define L_ST_NAME	    16
#define L_ST_STATUS	  3
#define L_ST_VERSION	  4

struct ST_LineBuf {
		char st_cod[L_ST_COD] ;
		char st_name[L_ST_NAME] ;
		char st_status[L_ST_STATUS] ;
		char st_version[L_ST_VERSION] ;
	 };

#define CST_NUM_NAME        1
#define N_CST    1         // NUMBER OF FIELDS

#define L_CST_NUM_NAME	  25

struct CST_LineBuf {
		char st_cod[L_ST_COD+1] ;
		char st_name[L_ST_NAME+1] ;
		char st_status[L_ST_STATUS] ;
	 };


#define ALARMM_NR	         1
#define ALARMM_PANEL       2
#define ALARMM_MESSAGE     3
#define ALARMM_TIME        4
#define ALARMM_ACK         5
#define ALARMM_RES         6
#define ALARMM_DEL         7
#define N_ALARMM					 7         // NUMBER OF FIELDS

#define L_ALARMM_NR        3
#define L_ALARMM_PANEL     3
#define L_ALARMM_MESSAGE   ALARM_MESSAGE_SIZE
#define L_ALARMM_TIME      26
#define L_ALARMM_ACK       5
#define L_ALARMM_RES       3
#define L_ALARMM_DEL       3

struct ALARMM_LineBuf {
		char nr[L_ALARMM_NR] ;
		char panel[L_ALARMM_PANEL];
		char message[L_ALARMM_MESSAGE];
		char time[L_ALARMM_TIME];
		char ack[L_ALARMM_ACK];
		char res[L_ALARMM_RES];
		char del[L_ALARMM_DEL];
	 };

#define ALARMS_POINT     1
#define ALARMS_GATE	     2
#define ALARMS_COND      3
#define ALARMS_WAYLOW    4
#define ALARMS_LOW       5
#define ALARMS_NORM      6
#define ALARMS_HI        7
#define ALARMS_WAYHI     8
#define ALARMS_TIME      9
#define N_ALARMS				 9         // NUMBER OF FIELDS

#define L_ALARMS_GATE	     8
#define L_ALARMS_COND      4
#define L_ALARMS_POINT     8
#define L_ALARMS_WAYLOW    6
#define L_ALARMS_LOW       6
#define L_ALARMS_NORM      6
#define L_ALARMS_HI        6
#define L_ALARMS_WAYHI     6
#define L_ALARMS_TIME      6

struct ALARMS_LineBuf {
		char point[L_ALARMS_POINT];
		char gate[L_ALARMS_GATE] ;
		char cond[L_ALARMS_COND];
		char waylow[L_ALARMS_WAYLOW];
		char low[L_ALARMS_LOW];
		char norm[L_ALARMS_NORM];
		char hi[L_ALARMS_HI];
		char wayhi[L_ALARMS_WAYHI];
		char time[L_ALARMS_TIME];
	 };

/*
#define ALARMST_POINT	         1
#define ALARMST_VERYLOW       2
#define ALARMST_LOW     3
#define ALARMST_HI        4
#define ALARMST_VERYHI         5
#define ALARMST_RES         6
#define ALARMST_DEL         7
#define N_ALARMM					 7         // NUMBER OF FIELDS

#define L_ALARMM_NR        2
#define L_ALARMM_PANEL     3
#define L_ALARMM_MESSAGE   69
#define L_ALARMM_TIME      26
#define L_ALARMM_ACK       5
#define L_ALARMM_RES       3
#define L_ALARMM_DEL       3

struct ALARMM_LineBuf {
		char nr[L_ALARMM_NR] ;
		char panel[L_ALARMM_PANEL];
		char message[L_ALARMM_MESSAGE];
		char time[L_ALARMM_TIME];
		char ack[L_ALARMM_ACK];
		char res[L_ALARMM_RES];
		char del[L_ALARMM_DEL];
	 };
*/

#define SYS_PANEL       1
#define SYS_PANEL_TYPE  2
#define SYS_SUB_PANEL   3
#define SYS_TYPE        4
#define SYS_NUM         5
#define SYS_SYS_NAME    6
#define N_SYS           6         // NUMBER OF FIELDS


#define L_SYS_PANEL       3
#define L_SYS_PANEL_TYPE  4
#define L_SYS_SUB_PANEL   3
#define L_SYS_TYPE        5
#define L_SYS_NUM         3
#define L_SYS_SYS_NAME    20

struct SYS_LineBuf {
		char panel[L_SYS_PANEL] ;
		char panel_type[L_SYS_PANEL_TYPE];
		char sub_panel[L_SYS_SUB_PANEL];
		char type[L_SYS_TYPE];
		char num[L_SYS_NUM];
		char name[L_SYS_SYS_NAME];
	 };

#define UNITS_NUM         1
#define UNITS_DIGOFF      2
#define UNITS_DIGON       3
#define UNITS_NORMAL      4
#define N_UNITS           4         // NUMBER OF FIELDS

#define L_UNITS_NUM         3
#define L_UNITS_NORMAL			6
#define L_UNITS_DIGON       11
#define L_UNITS_DIGOFF      11

struct UNITS_LineBuf {
		char num[L_UNITS_NUM];
		char digoff[L_UNITS_DIGOFF];
		char digon[L_UNITS_DIGON];
		char normal[L_UNITS_NORMAL];
	 };

#define MONITOR_NUM         1
#define MONITOR_ANA_DIG     2
#define MONITOR_BYTES       3
#define MONITOR_LENGTH      4
#define MONITOR_INPUTS      5
#define MONITOR_NUMBER      6
#define N_MONITOR           6         // NUMBER OF FIELDS

#define L_MONITOR_NUM         3
#define L_MONITOR_ANA_DIG     7
#define L_MONITOR_BYTES       1
#define L_MONITOR_LENGTH      3
#define L_MONITOR_INPUTS      1
#define L_MONITOR_NUMBER      2

struct MON_LineBuf {
		char num[L_MONITOR_NUM];
		char anadig[L_MONITOR_ANA_DIG];
		char bytes[L_MONITOR_BYTES];
		char length[L_MONITOR_LENGTH];
		char inputs[L_MONITOR_INPUTS];
		char number[L_MONITOR_NUMBER];
	 };

#define ARRAY11         1
#define N_ARRAY1       1         // NUMBER OF FIELDS

#define L_ARRAY1       41

struct ARRAY1_LineBuf {
		char array[L_ARRAY1];
	 };

#define AY_NUM         1
#define AY_LABEL       2
#define AY_LENGTH      3
#define N_AY          3         // NUMBER OF FIELDS

#define L_AY_NUM         3
#define L_AY_LABEL       LABEL
#define L_AY_LENGTH      3

#define L_AAY_LENGTH     5

struct AY_LineBuf {
		char num[L_AY_NUM];           // 'N',17,3,0},
		char label[L_AY_LABEL];//" ,'C',97,8,0},
		char length[L_AAY_LENGTH];           // 'N',17,3,0},
	 };

#define AYVALUE_NUM    1
#define AYVALUE_VALUE  2
#define N_AYVALUE      2

#define L_AYVALUE_NUM    3
#define L_AYVALUE_VALUE  11

struct AYvalue_LineBuf {
		char num[L_AYVALUE_NUM];           // 'N',17,3,0},
		char value[L_AYVALUE_VALUE];           // 'N',17,3,0},
	 };

#define DIAL_SYSTEM_NAME			1
#define DIAL_PHONE_NUMBER			2
#define DIAL_DESCRIPTOR_FILE	   3  
#define DIAL_MENU_FILE				4
#define DIAL_BAUD_RATE				5
//#define DIAL_LINK_NUMBER			6
#define N_DIAL           			5         // NUMBER OF FIELDS

#define L_DIAL_SYSTEM_NAME		20
#define L_DIAL_PHONE_NUMBER		30
#define L_DIAL_DES_FILE				15
#define L_DIAL_MENU_FILE			15
#define L_DIAL_BAUD_RATE			10
#define L_DIAL_LINK_NUMBER		15


struct DIAL_LineBuf {
		char system_name[L_DIAL_SYSTEM_NAME];   	//
		char phone_number[L_DIAL_PHONE_NUMBER];    	//
		char des_file[L_DIAL_DES_FILE];	     	//
		char menu_file[L_DIAL_MENU_FILE];          	//
		char baud_rate[L_DIAL_BAUD_RATE];           	//
//		char link_number[L_DIAL_LINK_NUMBER];   	//
	 };

#define COM_CONNECT    1
#define COM_PORT       2
#define COM_STATE      3
#define N_COM          3         // NUMBER OF FIELDS

#define L_COM_CONNECT  15
#define L_COM_PORT     4
#define L_COM_STATE    20

struct COM_LineBuf {
		char com_connect[L_COM_CONNECT];
		char com_port[L_COM_PORT];
		char com_state[L_COM_STATE];
	 };

#define NET_NO        1
#define NET_NAME      2
#define NET_CON       3
#define N_NET         3         // NUMBER OF FIELDS

#define L_NET_NO      5
#define L_NET_NAME   16
#define L_NET_CON    15

struct NET_LineBuf {
		char net_no[L_NET_NO];
		char net_name[L_NET_NAME];
		char net_con[L_NET_CON];
	 };



#define NS_NUM         1
#define NS_NAME        2
#define NS_TYPE        3
#define NS_VER         4
#define NS_PRG         5
#define NS_UPDATE      6
#define NS_NOTE        7
#define N_NS           7         // NUMBER OF FIELDS

#define L_NS_NUM         3
#define L_NS_NAME       16
#define L_NS_TYPE        5
#define L_NS_VER         5
#define L_NS_PRG         8
#define L_NS_UPDATE     15
#define L_NS_NOTE        8

struct NS_LineBuf {
		char num[L_NS_NUM];
		char name[L_NS_NAME];
		char type[L_NS_TYPE];
		char version[L_NS_VER];
		char prg[L_NS_PRG];
		char update[L_NS_UPDATE];
		char note[L_NS_NOTE];
	 };

/**************************************
**********  William add  *************
********     11.19.1997  *************
**********   code begin  *************
**************************************/
/*
#define NETSTAT_NUM         1
#define NETSTAT_DESCRIPTION 2
#define NETSTAT_ROOM_NUMBER 3
#define NETSTAT_SENSORID    4
#define NETSTAT_SENSOR_ADD  5
#define NETSTAT_AUTO_MAN    6
#define NETSTAT_ROOM_TEMP	  7
#define NETSTAT_SET_TEMP	  8
#define NETSTAT_ROOM_STATUS 9
#define NETSTAT_AUTO_TIME	 10
#define N_NETSTAT          10// NUMBER OF FIELDS

#define L_NETSTAT_NUM         3
#define L_NETSTAT_DESCRIPTION FULL_LABEL
#define L_NETSTAT_ROOM_NUMBER 4
#define L_NETSTAT_SENSORID    6
#define L_NETSTAT_SENSOR_ADD  3
#define L_NETSTAT_AUTO_MAN    4
#define L_NETSTAT_ROOM_TEMP	  4
#define L_NETSTAT_SET_TEMP	  4
#define L_NETSTAT_ROOM_STATUS 8
#define L_NETSTAT_AUTO_TIME	  5 // hour:minute

struct NETSTAT_LineBuf {
		char num[L_NETSTAT_NUM];
		char description[FULL_LABEL];
		char room_number[L_NETSTAT_ROOM_NUMBER];
		char sensorid[L_NETSTAT_SENSORID];
		char sensor_add[L_NETSTAT_SENSOR_ADD];
		char auto_man[L_NETSTAT_AUTO_MAN];
		char room_temp[L_NETSTAT_ROOM_TEMP];
		char set_temp[L_NETSTAT_SET_TEMP];
		char room_status[L_NETSTAT_ROOM_STATUS];
		char auto_time[L_NETSTAT_AUTO_TIME];
};
*/

// for test
#define NETSTAT_NUM         	1
#define NETSTAT_DESCRIPTION 	2
#define NETSTAT_VERSION       3
#define NETSTAT_SENSORID		  4
#define NETSTAT_SENSOR_ADD  	5
#define NETSTAT_AUTO_MAN    	6
#define NETSTAT_ROOM_TEMP	 	  7
#define NETSTAT_SET_TEMP	 	  8
#define N_NETSTAT           	8	// NUMBER OF FIELDS

#define L_NETSTAT_NUM         	3
#define L_NETSTAT_DESCRIPTION 	FULL_LABEL
#define L_NETSTAT_VERSION       7
#define L_NETSTAT_SENSORID    	6
#define L_NETSTAT_SENSOR_ADD  	7
#define L_NETSTAT_AUTO_MAN    	4
#define L_NETSTAT_ROOM_TEMP	 	  9
#define L_NETSTAT_SET_TEMP	 	  8

struct NETSTAT_LineBuf {
		char num[L_NETSTAT_NUM];
		char description[FULL_LABEL];
		char version[L_NETSTAT_VERSION];
		char sensorid[L_NETSTAT_SENSORID];
		char sensor_add[L_NETSTAT_SENSOR_ADD];
		char auto_man[L_NETSTAT_AUTO_MAN];
		char room_temp[L_NETSTAT_ROOM_TEMP];
		char set_temp[L_NETSTAT_SET_TEMP];
};

/**************************************
**********  William add  *************
********     11.19.1997  *************
**********    code end   *************
**************************************/

#endif

