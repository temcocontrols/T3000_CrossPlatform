#include "switch.h"
#include "delay.h"
#include "spi.h"

u8 Switch_Status[24];
extern u16 test[200];
extern u8 Mini_Type;


#define 	SW_OFF 		0
#define 	SW_AUTO 	1
#define 	SW_HAND 	2

// SW_IN PC0-PC7
// SW_HAND PC8
// SW_AUTO PC9
// SW_EN1 PC10
// SW_EN2 PC11
// SW_EN3 PC12

//
#ifdef BB
#define SW_IN  	GPIO_ReadInputData(GPIOC)  // read PC0-PC7
#define SET_SW_HAND() GPIO_SetBits(GPIOC,GPIO_Pin_8)
#define RST_SW_HAND() GPIO_ResetBits(GPIOC,GPIO_Pin_8)
#define SET_SW_AUTO() GPIO_SetBits(GPIOC,GPIO_Pin_9)
#define RST_SW_AUTO() GPIO_ResetBits(GPIOC,GPIO_Pin_9)
#endif

#ifdef TB
#define SW_IN  	GPIO_ReadInputData(GPIOB)  // read PC0-PC7
#define SET_SW_HAND() GPIO_SetBits(GPIOA,GPIO_Pin_11)
#define RST_SW_HAND() GPIO_ResetBits(GPIOA,GPIO_Pin_11)
#define SET_SW_AUTO() GPIO_SetBits(GPIOA,GPIO_Pin_12)
#define RST_SW_AUTO() GPIO_ResetBits(GPIOA,GPIO_Pin_12)
#endif

//#define SW_EN1() {GPIO_ResetBits(GPIOC,GPIO_Pin_10);GPIO_SetBits(GPIOC,GPIO_Pin_11);GPIO_SetBits(GPIOC,GPIO_Pin_12);}
//#define SW_EN2() {GPIO_ResetBits(GPIOC,GPIO_Pin_11);GPIO_SetBits(GPIOC,GPIO_Pin_10);GPIO_SetBits(GPIOC,GPIO_Pin_12);}
//#define SW_EN3() {GPIO_ResetBits(GPIOC,GPIO_Pin_12);GPIO_SetBits(GPIOC,GPIO_Pin_11);GPIO_SetBits(GPIOC,GPIO_Pin_10);}




void Switch_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
#ifdef BB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);


	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15 ;  // only for small panel
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC, GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12);
#endif

#ifdef TB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);   // DONT RESET ASIX

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

#endif
}

void Check_Switch_Status(u8 group)
{
	u8 temp1;  	// get the value of 3 groups when HAND = 1 AND AUTO = 0  	
	u8 temp2;	// get the value of 3 groups when HAND = 0 AND AUTO = 1  
	u8 sw_1,sw_2;
	
	u8 result1;  	  	
	u8 result2;
	u8 loop;
	u8 base;

#ifdef BB 
	if(Mini_Type == BIG)
	{
		if(group == 0)
		{
	//		SW_EN1();
			GPIO_ResetBits(GPIOC,GPIO_Pin_10);GPIO_SetBits(GPIOC,GPIO_Pin_11);GPIO_SetBits(GPIOC,GPIO_Pin_12);
			base = 0;
		}
		else if(group == 1)
		{
	//		SW_EN2();
			GPIO_ResetBits(GPIOC,GPIO_Pin_11);GPIO_SetBits(GPIOC,GPIO_Pin_10);GPIO_SetBits(GPIOC,GPIO_Pin_12);
			base = 8;
		}
		else if(group == 2)
		{
	//		SW_EN3();
			GPIO_ResetBits(GPIOC,GPIO_Pin_12);GPIO_SetBits(GPIOC,GPIO_Pin_11);GPIO_SetBits(GPIOC,GPIO_Pin_10);
			base = 16;
		}
		
		SET_SW_HAND();
		RST_SW_AUTO();	
		temp1 = SW_IN;

		RST_SW_HAND();
		SET_SW_AUTO();
		temp2 = SW_IN;
		
		/* compare temp1 and temp2, get the status */
		for(loop = 0;loop < 8;loop++)
		{
			result1 = (temp1 & (0x01 << loop));
			result2 = (temp2 & (0x01 << loop));
			if(result1 == result2)  Switch_Status[base + loop] = SW_OFF;
			else if(result1 == (0x01 << loop)) /* from 1 to 0 */
			{
				Switch_Status[base + loop] = SW_HAND;
			}
			else  /* from 0 to 1 */
			{
				Switch_Status[base + loop] = SW_AUTO;		 
			}
//			test[20 + base + loop] = Switch_Status[base + loop];
		}
	}
	else if(Mini_Type == SMALL)
	{
		SET_SW_HAND();
		RST_SW_AUTO();	
		temp1 = SW_IN;
		sw_1 = GPIO_ReadInputData(GPIOB) >> 14;
		
		RST_SW_HAND();
		SET_SW_AUTO();
		temp2 = SW_IN;
		sw_2 = GPIO_ReadInputData(GPIOB) >> 14;
				
		/* compare temp1 and temp2, get the status */
		for(loop = 0;loop < 8;loop++)
		{
			result1 = (temp1 & (0x01 << loop));
			result2 = (temp2 & (0x01 << loop));
			if(result1 == result2)  Switch_Status[loop] = SW_OFF;
			else if(result1 == (0x01 << loop)) /* from 1 to 0 */
			{
				Switch_Status[loop] = SW_HAND;
			}
			else  /* from 0 to 1 */
			{
				Switch_Status[loop] = SW_AUTO;		 
			}
//			test[20 + loop] = Switch_Status[loop];
		}
		for(loop = 0;loop < 2;loop++)
		{
			result1 = (sw_1 & (0x01 << loop));
			result2 = (sw_2 & (0x01 << loop));
			if(result1 == result2)  Switch_Status[8 + loop] = SW_OFF;
			else if(result1 == (0x01 << loop)) /* from 1 to 0 */
			{
				Switch_Status[8 + loop] = SW_HAND;
			}
			else  /* from 0 to 1 */
			{
				Switch_Status[8 + loop] = SW_AUTO;		 
			}
//		test[20 + 8 + loop] = Switch_Status[8 + loop];
		}
	}
#endif
	
	
#ifdef TB
	if(Mini_Type == TINY)
	{
		SET_SW_HAND();
		RST_SW_AUTO();	
		temp1 = SW_IN >> 1;
		sw_1 = SW_IN >> 2;
		
		RST_SW_HAND();
		SET_SW_AUTO();
		temp2 = SW_IN >>1;;
		sw_2 = SW_IN >> 2;
		
		result1 = (temp1 & (0x01 << 0));
		result2 = (temp2 & (0x01 << 0));
		if(result1 == result2)  Switch_Status[7] = SW_OFF;			
		else if(result1 == (0x01 << 0)) /* from 1 to 0 */
		{
			Switch_Status[7] = SW_HAND;
		}
		else  /* from 0 to 1 */
		{
			Switch_Status[7] = SW_AUTO;		 
		}
		/* compare temp1 and temp2, get the status */
//		test[20 + 0] = Switch_Status[0];
		for(loop = 1;loop < 8;loop++)
		{
			result1 = (sw_1 & (0x01 << loop));
			result2 = (sw_2 & (0x01 << loop));
			if(result1 == result2)  Switch_Status[7 - loop] = SW_OFF;
			else if(result1 == (0x01 << loop)) /* from 1 to 0 */
			{
				Switch_Status[7 - loop] = SW_HAND;
			}
			else  /* from 0 to 1 */
			{
				Switch_Status[7 - loop] = SW_AUTO;		 
			}
//			test[20 + loop] = Switch_Status[loop];
		}
	}
#endif
}

