#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x.h"

#define BIG 1
#define SMALL 2
#define TINY 3

#define BB    // BIG OR SMALL 
//#define TB    // TINY

#ifdef BB

#define PANEL_TYPE  SMALL

#endif

 void pulse_set(uint8_t channel,uint8_t rise_or_fall);
#define RISE 0
#define FALL 1

typedef union
{
	u8 byte[4];
	u32 longbyte;

}UN_HIGH_COUNT;

#define HI_COMMON_CHANNEL  6

extern u8 high_speed_flag[HI_COMMON_CHANNEL];
extern UN_HIGH_COUNT high_speed_counter[HI_COMMON_CHANNEL]; 

void SPI1_Init(void);							//初始化SPI1口
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler);	//设置SPI1速度   
u8 SPI1_ReadWriteByte(u8 TxData);				//SPI1总线读写一个字节

#endif
