#ifndef MAIN_H
#define MAIN_H



#include "product.h" 

#include 	"types.h"
#include 	"ax11000.h"
#include 	"uart.h"
#include	"stoe.h"
#include	"uip.h"
#include	"uip_arp.h"
#include	"adapter.h"
#include	"modbustcp.h"
#include 	"projdefs.h"
#include 	"portable.h"
#include 	"task.h"
#include	"queue.h"
#include	"semphr.h" 
#include 	"output.h"
#include 	"e2prom.h"
#include 	"clock.h"
#include 	"define.h"
#include    "hsuart.h"
#include	"spi.h"
#include	"spiapi.h"
#include 	"comm.h"
#include    "flash.h"
#include 	"delay.h"

#include 	"rs485.h"
//#include    "schedule.h"

#include 	"gconfig.h"
#include 	"gudpbc.h"
#include 	"sntpc.h"
#include 	"mstimer.h"
#include    "dma.h"


#include 	"lcd.h"
#include	"display.h"
#include	"key.h"
#include 	"commsub.h"
#include 	"scan.h"
#include 	"serial.h"
#include 	"input.h"
#include 	"pic.h"

//#include "ptp.h"


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <absacc.h>

#include "ch375usb.h"  
#include "usb.h" 
#include "bacnet.h"

#include "ud_str.h"
#include "user_data.h"
#include "dyndns.h"
#include "dyndns_app.h"

#include "timesync.h"
//#include "dnsc.h"
//#include "ping.h"




extern xQueueHandle xLCDQueue;

extern xTaskHandle xDisplayTask;		/* handle for display task */
extern xTaskHandle xDisplayCheckTask;  /* handle for check display status task */
extern xTaskHandle xHandler_Output;
extern xTaskHandle xKeyTask;
extern xTaskHandle far xHandleUSB;

extern xTaskHandle xSoftWatchTask;
extern xTaskHandle xHandleTcp;
extern xTaskHandle far xHandleSchedule;
extern xTaskHandle far xHandleBACnetComm;
extern xTaskHandle far xHandleBacnetControl;
extern xTaskHandle far xHandleMSTP;
extern xTaskHandle xHandleCommon;
extern xTaskHandle xHandler_SPI;
extern xTaskHandle xdata Handle_MainSerial;
extern xTaskHandle Handle_Scan, Handle_ParameterOperation;
extern xTaskHandle far xHandleMornitor_task;
extern xTaskHandle far xHandleLCD_task;
extern xTaskHandle far Handle_SampleDI;

extern U8_T flag_Updata_Clock;

#if STORE_TO_SD
extern xSemaphoreHandle sem_SPI;
#endif

extern bit flagLED_ether_tx;
extern bit flagLED_ether_rx;
extern bit flagLED_uart0_rx;
extern bit flagLED_uart0_tx;
extern bit flagLED_uart1_rx; 
extern bit flagLED_uart1_tx;
extern bit flagLED_uart2_rx;
extern bit flagLED_uart2_tx;
extern bit flagLED_usb_rx;
extern bit flagLED_usb_tx;


extern uint16_t pdu_len;  
extern BACNET_ADDRESS far src;

extern unsigned int far Test[50];

extern U16_T far AO_feedback[16];

typedef	struct
{
	U16_T count[15];
	U16_T old_count[15];
	U8_T  enable[15];
	U8_T  inactive_count[15];
}STR_Task_Test;



unsigned int Filter(unsigned char channel,unsigned int input);

extern STR_Task_Test xdata task_test;

void GSM_Test();

void vStartHandleMstpTasks( unsigned char uxPriority);	
void vStartSerialTasks( unsigned char uxPriority);
void initSerial(void);

void E2prom_Initial(void);
void watchdog(void);

bit read_PIC_AO( void);
void TCPIP_Task(void) reentrant ;


void set_default_parameters(void);

void control_logic(void); 
//void Updata_Clock(void);

extern char far time[20];

extern U8_T IDATA ExecuteRuntimeFlag;
extern U8_T flag_update;
extern U8_T far SD_exist;
#if STORE_TO_SD	
//U8_T exfuns_init(void);	
u8 SD_Initialize(void);
u8 Write_SD(U8_T file_no,U8_T index,U8_T ana_dig,U32_T star_pos);
u8 Read_SD(U8_T file_no,U8_T index,U8_T ana_dig,U32_T star_pos);
void check_SD_exist(void);

#endif


void SPI_Roution(void);
void Update_InputLed(void);
void refresh_led(void);
bit read_pic_version( void);
void pic_relay(unsigned int set_relay);

signed int RangeConverter(unsigned char function, signed int para,unsigned char i,unsigned int cal);
void responseCmd(U8_T type,U8_T* pData,MODBUSTCP_SERVER_CONN * pHttpConn);  


void Set_transaction_ID(U8_T *str, U16_T id, U16_T num);
extern U16_T transaction_id;
extern U16_T transaction_num;
extern U8_T	TcpSocket_ME;


#define SERIAL  0
#define TCP		1
#define USB		2
#define GSM		3

//#if defined(VAV)



//#define  LCD_CLK  	   P1_3
//#define  LCD_DATA 	   P1_2
//#define  LCD_CS 		P2_0
//#define  LCD_A0 		P1_1
//#define  LCD_RESET 		P1_6
//#define  BACKLIT		P1_7 


//#endif

	
#if MINI



// for rev2
//#define UART0_TXEN_VAV	P1_5 
//#define UART2_TXEN_VAV	P1_4
//#define LED_AO_1   P2_2		// for VAV
//#define LED_AO_2   P2_3		// for VAV
//#define LED_BEAT	 P2_7		// for VAV
//#define AI_TEMP		 P2_4 	// for VAV
//#define AI_0_10V	 P2_5  	// for VAV
//#define AI_0_20MA	 P2_6		// for VAV
//#define DO1        P1_0		// for VAV

// for VAV rev3, remap IO
#define UART0_TXEN_VAV	P1_1 
#define UART2_TXEN_VAV	P1_0
#define LED_AO_1   P3_0		// for VAV
#define LED_AO_2   P3_1		// for VAV
#define LED_BEAT	 P2_7		// for VAV
#define AI_TEMP		 P2_4 	// for VAV
#define AI_0_10V	 P2_5  	// for VAV
#define AI_0_20MA	 P2_6		// for VAV
#define DO1        P3_2   // P1_0		// for VAV

#define  LCD_CLK  	   P1_3
#define  LCD_DATA 	   P1_2
#define  LCD_CS 		P1_4
#define  LCD_A0 		P1_5
#define  LCD_RESET 		P1_6
#define  BACKLIT		P1_7 

#define  RESET_8051	 	P2_3

#define	 KEYPAD			P3
#define  KEY_PRO 	    P3_4
#define  KEY_SEL 	    P3_5
#define  KEY_DOWN 		P3_6
#define  KEY_UP 		P3_7



#define MINI_PIC_REV 0x01  // pic882

#define  CHSEL3 P3_3

 
#define UART0_TXEN	P2_2 //P1_1


#define UART2_TXEN_BIG 	P2_0 //P2_2 
#define UART2_TXEN_TINY	P2_0 //P2_2 



#define UART1_VECTOR  6 // UART1
#define UART0_VECTOR  4 // UART0

#endif


#if CM5

#define CM5_PIC_REV 0x01  // pic688
#define CM5_HW  		8


#define  BACKLIT		   P2_4
#define  LCD_SCL  	   P3_3
#define  LCD_SDA 	     P2_3
#define  LCD_CS 			 P2_5
#define  LCD_RES 			 P2_7
#define  LCD_RS 		 P2_6

#define	 KEYPAD			 P1
#define  KEY_PRO 	   P1_0
#define  KEY_SEL 	   P1_1
#define  KEY_DOWN 	 P1_2
#define  KEY_UP 		 P1_3

#define  DI1_LATCH 	  P3_0
//#define  DI2_LATCH 	  P1_3
#define  KEY_LATCH    P2_2
#define  UART0_TXEN 	  P3_2
#define  UART2_TXEN 	  P3_1

#define DI1		P1
//#define DI2		P1

//#endif



#define AI_CHANNEL 10
#define DI1_CHANNEL	8
#define DI2_CHANNEL 8
#define DO_CHANNEL 10
#define CHS_DI1	0		
#define CHS_DI2 1


#endif




extern U8_T far ChangeFlash;
extern U8_T far WriteFlash;
extern U8_T UpIndex;
extern U8_T flag_retransmit;
//void responseCmd(U8_T type,U8_T* pData,MODBUSTCP_SERVER_CONN * pHttpConn); 
extern xSemaphoreHandle xSemaphore_tcp_send;
extern U32_T ether_rx_packet;	 
extern U32_T ether_tx_packet;
extern U8_T flag_reset_default;
extern U8_T flag_resume_scan;
extern U8_T resume_scan_count;
extern U8_T flag_reboot;
extern U8_T get_verion;

extern u8 far udp_scan_count;
extern u8 far flag_udp_scan;



void Check_whether_reiniTCP(void);
#endif



