#ifndef COMM_H
#define COMM_H

#include "types.h"

/* communication task */
/*
	from master to slaver
	1. 	SEND output led status
	2.	SEND input type : 0-3.3v / therimsiter / 0 - 10v / 0-20ma
	3. 	GET	input value
    4. 	GET output switch status

*/
/* define command for communication with slaver */

 typedef struct
{
	U8_T type;		/* type for current command */
	U8_T len; 		/* data number for sending or receiving */
	U8_T buf[32];  /* buffer for sending or receiveing */
	U8_T index; 	/* index for current bytes of sending or receiving */
	U8_T flag;    	/* flag for whether finish the current sending or receiving */
}STR_CMD;



typedef  enum 
{
	/* 	send	*/
	C_INITIAL = 0,	

	S_OUTPUT_LED = 0x10, 	/* 0x10 + 24 bytes */
	S_INPUT_LED = 0x11, 	/* 0x11 + 32 bytes */
	S_HI_SP_FLAG = 0x12,  	/* 0x12 + 6 bytes  */	
	S_COMM_LED	= 0x13,	/* 0x13 + 2 bytes  */
	S_ALL = 0x14,	   // 58

	G_SWTICH_STATUS = 0x20,	/* 0x20 + 24 bytes */
	G_INPUT_VALUE = 0x21,	/* 0x21 + 64 bytes */
	G_SPEED_COUNTER = 0x22, /* 0x22 + 24 bytes */
	G_TOP_CHIP_INFO	= 0x23,
	G_ALL = 0x24,	//  88


	C_MINITYPE = 0x80,
	C_ASIX_ISP = 0X81,
	C_END = 255

};

/* command for communication , pls refer to detailed protocal */


void vStartCommToTopTasks( unsigned char uxPriority);
void Start_Comm_Top(void);
void Stop_Comm_Top(void);
void Update_Led(void);
void SPI_Roution(void);
void Rsest_Top(void);
void SPI_Get(U8_T cmd,U8_T len);
void Enter_Asix_ISP(void);


#endif
