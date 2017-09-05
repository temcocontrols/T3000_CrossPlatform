#ifndef _RECSTRUCT_H
#define _RECSTRUCT_H
#ifdef GGRID

#include "recdef.h"


struct FieldStruct  huge out_struct[] =
		{
		{"NUM"   , 'N',0,L_OUT_NUM,0},
		{"FULL_LABEL",'C',0,L_OUT_FULL_LABEL,0},
		{"A/M",'C',0,L_OUT_AUTO_MAN,0},
		{ "VALUE",'F',0,L_OUT_VALUE,2},
		{ "UNITS" ,'C',0,L_OUT_UNITS,0},
		{ "RANGE",'C',0,L_OUT_RANGE,0},
		{ " 0% ",'N',0,L_OUT_LOW,0},
		{	" 100",'N',0,L_OUT_HIGH,0},
//		{ "M_DEL",'N',0,L_OUT_M_DEL,0},
//		{	"S_DEL",'N',0,L_OUT_S_DEL,0},
//		{ "S_LEVEL",'N',0,L_OUT_SEC_LEVEL,0},
		{ "D",'N',0,L_OUT_DECOM,0},
		{"LABEL" ,'C',0,L_OUT_LABEL,0},
		};

struct FieldStruct  huge in_struct[] =
		{
		{"NUM"   , 'N',0,L_IN_NUM,0},
		{"FULL_LABEL",'C',0,L_IN_FULL_LABEL,0},
		{"A/M",'C',0,L_IN_AUTO_MAN,0},
		{ "VALUE",'F',0,L_IN_VALUE,2},
		{ "UNITS" ,'C',0,L_IN_UNITS,0},
		{ "RANGE",'C',0,L_IN_RANGE,0},
		{" CAL",'N',0,L_IN_CALIBR,0},
		{"FIL",'N',0,L_IN_FILTER,0},
		{"D",'N',0,L_IN_DECOM,0},
		{"LABEL" ,'C',0,L_IN_LABEL,0}
		};

struct FieldStruct  huge var_struct[] =
		{
		{"NUM"   , 'N',0,L_VAR_NUM,0},
		{"FULL_LABEL",'C',0,L_VAR_FULL_LABEL,0},
		{"A/M",'C',0,L_VAR_AUTO_MAN,0},
		{ "VALUE",'F',0,L_VAR_VALUE,3},
		{ "UNITS" ,'C',0,L_VAR_UNITS,0},
		{"LABEL" ,'C',0,L_VAR_LABEL,0}
	} ;

struct FieldStruct  huge con_struct[] =
		{
		{"NUM"   , 'N',17,L_CON_NUM,0},
		{"INPUT",'C',20,L_CON_INPUT,0},
		{ "VALUE",'F',30,L_CON_VALUE,2},
		{ "UNITS" ,'C',56,L_CON_INUNITS,0},
		{"A/M",'C',61,L_CON_AUTO_MAN,0},
		{ "OUTPUT",'F',30,L_CON_OUTPUT,2},
//		{ " " ,'C',56,L_CON_OUTUNITS,0},
		{"SETPOINT",'C',38,L_CON_SETPOINT,0},
		{"SET_VALUE",'F',48,L_CON_SETPOINTV,2},
		{ "UNITS" ,'N',56,L_CON_UNITS,0},
		{"ACTION",'N',65,L_CON_ACTION,0},
		{ "PROP",'N',69,L_CON_PROP,0},
		{ "RESET",'N',73,L_CON_RESET,0},
		{ "RATE",'N',81,L_CON_RATE,0},
		{ "BIAS",'N',77,L_CON_BIAS,0},
		{"NUM"   , 'N',17,L_CON_NUM,0}
	}    ;

struct FieldStruct  huge wr_struct[] =
		{
		{"NO"   , 'N',0,L_WR_NUM,0},
		{"FULL_LABEL",'C',0,L_WR_FULL_LABEL,0},
		{"A/M",'C',0,L_WR_AUTO_MAN,0},
		{ "OUTPUT",'C',0,L_WR_VALUE,0},
		{ "HOLIDAY1" ,'C',0,L_WR_OVERRIDE1,0},
		{ "STATE1",'C',0,L_WR_OR1VALUE,0},
		{ "HOLIDAY2",'N',0,L_WR_OVERRIDE2,0},
		{ "STATE2",'C',0,L_WR_OR2VALUE,0},
		{"LABEL" ,'C',0,L_WR_LABEL,0}
		}    ;

struct FieldStruct  huge wr_time_struct[] =
		{
		{"   " , 'C',0 ,3,0},
		{" MON " , 'C', 0,5,0},
		{" TUE " , 'C', 0,5,0},
		{" WED "  , 'C', 12,5,0},
		{" THU "   , 'C',17,5,0},
		{" FRI ",'C',20,5,0},
		{" SAT ",'C',40,5,0},
		{" SUN ",'C',44,5,0},
		{"HOLIDAY1" ,'C',48,5,0},
		{"HOLIDAY2",'C',59,5,0}
		}    ;

struct FieldStruct  huge ar_struct[] =
		{
		{"NUM"   , 'N',17,3,0},
		{"FULL_LABEL",'C',20,20,0},
		{"A/M",'C',40,4,0},
		{ "VALUE",'C',44,3,0},
		{"LABEL" ,'C',47,8,0}
		}    ;

struct FieldStruct  huge ar_y_struct[] =
		{
		{"SU",'C',44,2,0},
		{"MO" , 'C', 0,2,0},
		{"TU" , 'C', 0,2,0},
		{"WE"  , 'C', 12,2,0},
		{"TH"   , 'C',17,2,0},
		{"FR",'C',20,2,0},
		{"SA",'C',40,2,0},
		{"  " , 'C',0 ,1,0},
		{"SU",'C',44,2,0},
		{"MO" , 'C', 0,2,0},
		{"TU" , 'C', 0,2,0},
		{"WE"  , 'C', 12,2,0},
		{"TH"   , 'C',17,2,0},
		{"FR",'C',20,2,0},
		{"SA",'C',40,2,0},
		{"  " , 'C',0 ,1,0},
		{"SU",'C',44,2,0},
		{"MO" , 'C', 0,2,0},
		{"TU" , 'C', 0,2,0},
		{"WE"  , 'C', 12,2,0},
		{"TH"   , 'C',17,2,0},
		{"FR",'C',20,2,0},
		{"SA",'C',40,2,0},
		{"  " , 'C',0 ,1,0}
		}    ;


struct FieldStruct  huge prg_struct[] =
		{
		{"NUM"   , 'N',17,3,0},
		{"FULL_LABEL",'C',20,20,0},
		{ "STATUS" ,'C',40,4,0},
		{"A/M",'C',44,4,0},
//		{ "TIMER",'C',48,L_PRG_TIMER,0},
//		{ "TIME_MIN",'C',48,L_PRG_REPMIN,0},
//		{ "TIME_SEC",'C',48,L_PRG_REPSEC,0},
//		{ "LEFT_MIN",'C',48,L_PRG_REMMIN,0},
//		{ "LEFT_SEC",'C',48,L_PRG_REMSEC,0},
		{ "SIZE",'N',68,4,0},
		{"RUN_STATUS",'C',72,L_PRG_EXIT,0},
		{"LABEL" ,'C',75,8,0}
		}    ;


/*
struct FieldStruct  dmon_struct[] =
		{
//		{"PANEL" , 'N',0 ,3,0},
//		{"PANEL_TYPE" , 'C', 0,4,0},
//		{"SUB_PANEL" , 'N', 0,3,0},
//		{"TYPE"  , 'C', 12,5,0},
		{"NUM"   , 'N',17,3,0},
		{ "INPUT",'C',20,10,0},
		{ "ON TIME",'C',20,8,0},
		{ "START DATE",'C',28,11,0},
		{ "LENGTH" ,'N',39,6,0},
		{   "TOTAL",'N',43,4,0},
		{     "DAY",'N',47,4,0}
	}    ;
*/

struct FieldStruct huge amon_struct[] =
		{
		{ "NUM"      ,'C',0,3,},
		{ "LABEL"    ,'C',0,8,},
		{ "INTERVAL" ,'C',0,8,},
		{ "LENGTH"   ,'N',0,3,},
		{ "UNITS"    ,'N',0,6,},
		{ "SIZE"     ,'N',0,7,},
		{ "STATUS"   ,'N',0,3,}
	}    ;

struct FieldStruct  huge amon_input_struct[] =
		{
		{"INPUT" , 'C',0 ,8,0}
		}    ;

struct FieldStruct  huge grp_struct[] =
		{
		{"NUM"   , 'N',0,3,0},
		{"FULL_LABEL",'C',0,L_GRP_FULL_LABEL,0},
		{"LABEL" ,'C',0,L_GRP_LABEL,0},
		{"PIC FILE" ,'C',0,L_GRP_PICFILE,0},
		{"MODE" ,'C',0,L_GRP_MODE,0},
		{"REFRESH" ,'C',0,L_GRP_UPDATE,0}
	};

struct FieldStruct  huge g_grp_struct[] =
		{
		{"PANEL" , 'N',0 ,3,0},
		{"TYPE"  , 'C', 0,5,0},
		{"NUM"   , 'N',0,3,0},
		{"FULL_LABEL",'C',0,L_G_GRP_FULL_LABEL,0},
		{"LABEL" ,'C',0,L_G_GRP_LABEL,0},
		{"VIZ/INV" ,'C',0,L_G_GRP_VIZIBIL,0},
		{" X " ,'C',0,L_G_GRP_X,0},
		{" Y " ,'C',0,L_G_GRP_Y,0},
		{"ICON_NAME",'C',0,L_G_GRP_SYMBOL,0}
	}    ;

struct FieldStruct  status_struct[] =
		{
		{"PANEL" , 'N',0 ,3,0},
		{"PANEL_TYPE" , 'C', 0,4,0},
		{"SUB_PANEL" , 'N', 0,3,0},
		{"TYPE"  , 'C', 12,5,0},
		{"NUM"   , 'N',17,3,0},
		{"NAME",'C',20,20,0},
		{ "NET",'C',40,3,0},
		{ "PROGRAM" ,'C',43,3,0},
		{ "VERSION" ,'N',46,4,0},
		{"SCANS",'N',50,4,0},
		{ "NET IN",'N',54,4,0},
		{ "NET OUT" ,'N',58,4,0},
		{	"MEMORY",'N',62,4,0 }
	}    ;
/*
struct FieldStruct  pass_struct[] =
		{
		{"PANEL" , 'N',0 ,3,0},
		{"PANEL_TYPE" , 'C', 0,4,0},
		{"SUB_PANEL" , 'N', 0,3,0},
		{"TYPE"  , 'C', 12,5,0},
		{"NUM"   , 'N',17,3,0},
		{"NAME",'C',20,8,0},
		{ "CODE",'C',28,6,0},
		{ "GROUP" ,'N',34,4,0},
		{"LEVEL",'N',40,4,0},
		{ "MENU",'N',44,4,0}
	}    ;
*/

struct FieldStruct  huge user_name_struct[] =
		{
		{"USER NAME" , 'C',0 ,15,0}
		}    ;

struct FieldStruct  huge st_struct[] =
		{
		{"NUM" , 'C',0 ,3,0},
		{"PANEL NAME" , 'C',0 ,16,0},
		{"STATE" , 'C',0 ,3,0},
		{"VERSION" , 'C',0 ,4,0},
		}    ;
struct FieldStruct  huge cst_struct[] =
		{
		{"PANEL " , 'C',0 ,24,0}
		}    ;

struct FieldStruct huge alarmm_struct[] =
		{
		{"#" , 'N',0 ,L_ALARMM_NR,0},
		{"PAN" , 'C', 0,3,0},
		{"MESSAGE" , 'C', 0,L_ALARMM_MESSAGE,0},
		{"TIME"  , 'C', 0,L_ALARMM_TIME,0},
		{"ACK"   , 'C',0,L_ALARMM_ACK,0},
		{"RES"   , 'C',0,L_ALARMM_RES,0},
		{"DEL"   , 'C',0,L_ALARMM_DEL,0}
	}    ;

struct FieldStruct huge alarms_struct[] =
		{
		{"POINT" , 'C', 0,L_ALARMS_POINT,0},
		{"GATE" , 'N',0 ,L_ALARMS_GATE,0},
		{"COND" , 'C', 0,L_ALARMS_COND,0},
		{"VERYLOW"  , 'C', 0,L_ALARMS_WAYLOW,0},
		{"LOW"   , 'C',0,L_ALARMS_LOW,0},
		{"NORMAL"   , 'C',0,L_ALARMS_NORM,0},
		{"HI"   , 'C',0,L_ALARMS_HI,0},
		{"VERYHI" , 'C',0,L_ALARMS_WAYHI,0},
		{"TIME" , 'C',0,L_ALARMS_TIME,0}
	}    ;

struct FieldStruct  sys_struct[] =
		{
		{"PANEL" , 'N',0 ,3,0},
		{"PANEL_TYPE" , 'C', 0,4,0},
		{"SUB_PANEL" , 'N', 0,3,0},
		{"TYPE"  , 'C', 12,5,0},
		{"NUM"   , 'N',17,3,0},
		{"SYS_NAME",'C',20,20,0}
	}    ;


struct FieldStruct huge units_struct[] =
		{
		{"NUM"   , 'N',0,L_UNITS_NUM,0},
		{"DIG OFF",'C',0,L_UNITS_DIGOFF,0},
		{"DIG ON",'C',0,L_UNITS_DIGON,0},
		{"DIRECT_INV",'C',0,L_UNITS_NORMAL,0}
	}    ;

struct FieldStruct huge ay_struct[] =
		{
		{"NUM"   , 'N',0,L_AY_NUM,0},
		{"LABEL",'C',0,L_AY_LABEL,0},
		{"LENGTH",'C',0,L_AAY_LENGTH,0}
	}    ;

struct FieldStruct huge arights_struct[] =
		{
		{"NUM"   , 'N',0,L_AY_NUM,0},
		{"NAME",'C',0,L_AY_LABEL,0},
		{"ACCESS",'C',0,L_AAY_LENGTH,0}
	}    ;

struct FieldStruct huge ayvalue_struct[] =
		{
		{"NUM"   , 'N',0,L_AYVALUE_NUM,0},
		{"VALUE",'C',0,L_AYVALUE_VALUE,2}
	}    ;
/*
struct FieldStruct huge mon_struct[] =
		{
//		{"PANEL" , 'N',0 ,3,0},
//		{"PANEL_TYPE" , 'C', 0,4,0},
//		{"SUB_PANEL" , 'N', 0,3,0},
//		{"TYPE"  , 'C', 0,5,0},
		{"NUM"   , 'N',0,3,0},
		{"ANA_DIG"   , 'C',0,7,0},
		{"BYTES" , 'N',0 ,1,0},
		{"LENGTH" , 'N', 0,3,0},
		{"INPUTS" , 'N', 0,1,0},
		{"SIZE" , 'N', 0,7,0},
		{"NUMBER"  , 'N', 0,2,0}
		}    ;
*/

struct FieldStruct huge tbl_struct[] =
		{
		{"VALUE"  , 'N',0,5,2},
		{"     "  , 'N',0,9,2},
//		{"VALUE2"  , 'N',0,5,2},
//		{"     " , 'N',0 ,5,2},
//		{"VALUE3"  , 'N',0,5,2},
//		{"     " , 'N',0 ,5,2},
//		{"VALUE4"  , 'N',0,5,2},
//		{"     " , 'N',0 ,5,2},
//		{"VALUE5"  , 'N',0,5,2},
//		{"     " , 'N',0 ,5,2}
		}   ;

struct FieldStruct huge array_struct[] =
		{
		{"          "   , 'N',0,10,0}
		}    ;

struct FieldStruct  huge dial_struct[] =
		{
		{"SYS_NAME" , 'C',0 , L_DIAL_SYSTEM_NAME, 0 },
		{"PHONE_NO" , 'C', 0 , L_DIAL_PHONE_NUMBER, 0 },
		{"DIRECTORY" , 'C', 0, L_DIAL_DES_FILE, 0 },
		{"MENU_FILE" , 'C', 0, L_DIAL_MENU_FILE, 0 },
		{"BAUD_RATE" , 'N',0,L_DIAL_BAUD_RATE, 0 }
//		{"LINK_NO",'C',0,L_DIAL_LINK_NUMBER, 0 }
		};

struct FieldStruct  huge com_struct[] =
		{
		{"CONNECTION" , 'C',0,L_COM_CONNECT,0},
		{"PORT",'C',0,L_COM_PORT,0},
		{"STATE",'C',0,L_COM_STATE,0}
		};

struct FieldStruct huge net_struct[] =
		{
		{"NET NO" , 'C',0,L_NET_NO,0},
		{"NET_NAME",'C',0,L_NET_NAME,0},
		{"CONNECTION",'C',0,L_NET_CON,0}
		};

struct FieldStruct  huge netstatus_struct[] =
		{
		{"NUM"  ,'N',0,L_NS_NUM,0},
		{"NAME" ,'C',0,L_NS_NAME,0},
		{"TYPE" ,'C',0,L_NS_TYPE,0},
		{"VERSION",'N',0,L_NS_VER,2},
		{"PROGRAM",'C',0,L_NS_PRG,0},
		{"UPDATE/PRG",'C',0,L_NS_UPDATE,0},
		{"NOTE",'C',0,L_NS_NOTE,0}
		};

//**************************************
//**********  William add  *************
//********     11.19.1997  *************
//**********   code begin  *************
//**************************************
/*
struct FieldStruct  huge netstat_struct[] =
	{
		{"NUM"   , 'N',0,L_NETSTAT_NUM,0},
		{"DESCRIP",'C',0,FULL_LABEL,0,},
		{"ROOM_NUM",'C',0,L_NETSTAT_ROOM_NUMBER,0},
		{"SENSORID",'N',0,L_NETSTAT_SENSORID,0},
		{"SENSOR_ADD",'N',0,L_NETSTAT_SENSOR_ADD,0},
		{"A/M",'C',0,L_IN_AUTO_MAN,0},
		{"ROOM_TEMP",'N',0,L_NETSTAT_ROOM_TEMP,0},
		{"SET_TEMP",'N',0,L_NETSTAT_SET_TEMP,0},
		{"STATUS",'C',0,L_NETSTAT_ROOM_STATUS,0},
		{"AUTO_TIME",'C',0,L_NETSTAT_AUTO_TIME,0}
	};
*/
// for test
struct FieldStruct  huge netstat_struct[] =
	{
		{"NUM"   , 'N',0,L_NETSTAT_NUM,0},
		{"FULL_LABEL",'C',0,FULL_LABEL,0,},
		{"VERSION",'C',0,L_NETSTAT_VERSION,0},
		{"SEN_ID",'N',0,L_NETSTAT_SENSORID,0},
		{"SEN_ADD",'N',0,L_NETSTAT_SENSOR_ADD,0},
		{"A/M",'C',0,L_NETSTAT_AUTO_MAN,0},
		{"ROOM_TEMP",'N',0,L_NETSTAT_ROOM_TEMP,0},
		{"SET_TEMP",'N',0,L_NETSTAT_SET_TEMP,0},
	};

//**************************************
//**********  William add  *************
//********     11.19.1997  *************
//**********    code end   *************
//**************************************

#else
	extern struct FieldStruct huge out_struct[];
	extern struct FieldStruct huge in_struct[];
	extern struct FieldStruct huge var_struct[];
	extern struct FieldStruct huge con_struct[];
	extern struct FieldStruct huge wr_struct[];
	extern struct FieldStruct huge wr_time_struct[];
	extern struct FieldStruct huge ar_struct[];
	extern struct FieldStruct huge ar_y_struct[];
	extern struct FieldStruct huge prg_struct[];
	extern struct FieldStruct huge grp_struct[];
	extern struct FieldStruct huge g_grp_struct[];
	extern struct FieldStruct huge user_name_struct[];
	extern struct FieldStruct huge st_struct[];
	extern struct FieldStruct huge cst_struct[];
	extern struct FieldStruct huge amon_struct[];
	extern struct FieldStruct huge amon_input_struct[];
	extern struct FieldStruct huge mon_struct[];
	extern struct FieldStruct huge array_struct[];
	extern struct FieldStruct huge alarmm_struct[];
	extern struct FieldStruct huge alarms_struct[];
	extern struct FieldStruct huge units_struct[];
	extern struct FieldStruct huge tbl_struct[];
	extern struct FieldStruct huge ay_struct[];
	extern struct FieldStruct huge arights_struct[];
	extern struct FieldStruct huge ayvalue_struct[];
	extern struct FieldStruct huge dial_struct[];
	extern struct FieldStruct huge com_struct[];
	extern struct FieldStruct huge net_struct[];
  extern struct FieldStruct huge netstatus_struct[]; 
	extern struct FieldStruct huge netstat_struct[];

#endif

#endif