#ifndef PIC_H
#define PIC_H
 
#include "main.h"



#define 	C_VER_CHECKSUM  0x69
#define READING_THRESHOLD	150

// PIC commands protocol
#define PIC16_PULSE    	 		0xB1
#define PIC16_VERSION			0xB2

#define MAX_FILTER 12

//    define command 
#define READ_VERSION    0xb2
enum
{
	GET_VERSION = 0,
	READ_AO_FEEDBACK,

	SET_RELAY_LOW,
	SET_RELAY_HI,

	SET_WATCHDOG_TIMER,
	
	SET_INPUT1_TYPE = 11,
  SET_INPUT12_TYPE = SET_INPUT1_TYPE + 11
	
};
//   end define


void vStartPicTasks( unsigned char uxPriority);
void Initial_Range(void);
bit write_pic_watchdog(S8_T time);
void push_cmd_to_picstack(uint8 cmd, uint8 value);
void PIC_refresh(void);
void PIC_initial_data(void);

#endif
















