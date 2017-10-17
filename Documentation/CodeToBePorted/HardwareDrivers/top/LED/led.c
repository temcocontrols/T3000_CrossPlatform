#include "led.h"
#include "spi.h"

#define MAX_LEVEL 6

u8 LED_status[67];
u16 LED_Level[5][MAX_LEVEL];
u8 level;
void LED_Init(void)
{
	u8 i,j;
	GPIO_InitTypeDef GPIO_InitStructure;

#ifdef BB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure); 
	GPIO_SetBits(GPIOE, GPIO_InitStructure.GPIO_Pin);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_SetBits(GPIOF, GPIO_InitStructure.GPIO_Pin);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_SetBits(GPIOG, GPIO_InitStructure.GPIO_Pin);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD, GPIO_InitStructure.GPIO_Pin);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);	
	
	GPIO_SetBits(GPIOA, GPIO_Pin_15);   // DONT RESET ASIX
#endif

#ifdef TB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure); 
	GPIO_SetBits(GPIOE, GPIO_InitStructure.GPIO_Pin);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD, GPIO_InitStructure.GPIO_Pin);	

#endif

	for(j = 0;j < 67;j++) LED_status[j] = 0;
	for(i = 0;i < 5;i++)
		for(j = 0;j < MAX_LEVEL;j++)
			LED_Level[i][j] = 0;
	
}



void Count_LED_Buffer(void)
{
	u8 i,j;

	for(i = 0;i < MAX_LEVEL;i++)
	{		
		for(j = 0;j < 67;j++)
		{			
			if(LED_status[j] <= i)	 
			{
				LED_Level[j / 16][i] |= (0x01 << (j % 16));	  
			}
			else 
			{
				LED_Level[j / 16][i] &= ~(0x01 << (j % 16)); 
			}
		}
		 
	} 
}
extern u8 Mini_Type;
// 1ms 
void Refresh_LED(void)
{
#ifdef BB
	GPIO_Write(GPIOE,LED_Level[0][level]);
	GPIO_Write(GPIOF,LED_Level[1][level]);
	GPIO_Write(GPIOG,LED_Level[2][level]);
	GPIO_Write(GPIOD,LED_Level[3][level]);
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,LED_Level[4][level] & 0x01);	
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,LED_Level[4][level] & 0x02);	
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,LED_Level[4][level] & 0x04);	
#endif
	
#ifdef TB
	GPIO_Write(GPIOD,LED_Level[0][level]);
	LED_Level[1][level] &= 0xF3FF;
	LED_Level[1][level] |= 0xf000;
	GPIO_Write(GPIOE,LED_Level[1][level]);
#endif	
	if(level < 5)  // 6 level
	{  				
		level++;
	}
	else
		level = 0;

}
