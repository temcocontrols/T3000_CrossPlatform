#include "inputs.h"
#include "delay.h"
#include "spi.h"
#include "modbus.h"

uint16_t data_change = 0 ;
vu8 MAX_AI_CHANNEL;

vu16 AD_Value[32]; 
u8 range[32];
//vu16 input[MAX_AI_CHANNEL];
extern u16 test[200]; 
extern u8 Mini_Type;
 void pulse_set(uint8_t channel,uint8_t rise_or_fall);

 void range_set_func(u8 range) ;
 
#define ADC_DR_ADDRESS  0x4001244C  

void inputs_io_init(void)
{
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_0|ADC_Channel_1, 1, ADC_SampleTime_28Cycles5);
// IO Configure 
	
	GPIO_InitTypeDef GPIO_InitStructure;

#ifdef BB
///**************************PortB configure----ADC1*****************************************/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;  
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB, GPIO_InitStructure.GPIO_Pin);	

#endif


#ifdef TB
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;  
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC, GPIO_InitStructure.GPIO_Pin);	


#endif
	// initial high_speed_counter IO
//	pulse_set(0,FALL);
//	pulse_set(1,FALL);
//	pulse_set(2,FALL);
//	pulse_set(3,FALL);
//	pulse_set(4,FALL);
//	pulse_set(5,FALL);
	
	if(Mini_Type == BIG)	MAX_AI_CHANNEL = 32;
	else if(Mini_Type == SMALL)	MAX_AI_CHANNEL = 16;
	else	MAX_AI_CHANNEL = 11;
}


void inputs_adc_init(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	/* configuration ------------------------------------------------------*/  
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;

	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Cmd(ADC1, ENABLE); 
	/* Enable ADC1 reset calibaration register */   
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1)== SET)
	{
		;
	}	
	
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
}


void inputs_init(void) 
{
	u8 i;
	inputs_io_init();
	inputs_adc_init();
	//dma_adc_init();	
	for(i = 0;i < 32;i++)
		range[i] = 3;
	
}


void inpust_scan(void)
{
	u16   temp = 0 ;
	static u8 channel_count =0 ;
	//u16 pin_buf ;
#ifdef BB

if(Mini_Type == BIG)
{

	AD_Value[channel_count] = ADC_getChannal(ADC1,ADC_Channel_8);
	

	channel_count++;
	channel_count %= MAX_AI_CHANNEL;


	temp = GPIO_ReadOutputData(GPIOB);
	temp &= 0xffc1;
	temp |= (channel_count << 1);
	
	temp &= 0xff3f;
	temp |= (range[channel_count] << 6);
//	if((channel_count < 26) || (high_speed_flag[channel_count - 26] == 0))
	{
		GPIO_Write(GPIOB,temp);
	}
}
if(Mini_Type == SMALL)
{

	AD_Value[channel_count] = ADC_getChannal(ADC1,ADC_Channel_8);
	

	channel_count++;
	channel_count %= MAX_AI_CHANNEL;

	temp = GPIO_ReadOutputData(GPIOB);
	temp &= 0xffc1;
	temp |= (channel_count << 1);
	
	temp &= 0xff3f;
	temp |= (range[channel_count] << 6);
	//if((channel_count < 10) || (high_speed_flag[channel_count - 10] == 0))
	{
		GPIO_Write(GPIOB,temp | 0x20);
	}
}


#endif
	
#ifdef TB
	
	AD_Value[channel_count] = ADC_getChannal(ADC1,ADC_Channel_11);

  test[40 + channel_count] = AD_Value[channel_count];
	channel_count++;
	channel_count %= MAX_AI_CHANNEL;

	temp = GPIO_ReadOutputData(GPIOC);
	temp &= 0xC3FF;
	// adjust pin
	if(channel_count == 1)	temp |= (8 << 10);
	else if(channel_count == 2)	temp |= (4 << 10);
	else if(channel_count == 3)	temp |= (12 << 10);
	else if(channel_count == 4)	temp |= (2 << 10);
	else if(channel_count == 5)	temp |= (10 << 10);
	else if(channel_count == 7)	temp |= (15 << 10);
	else if(channel_count == 8)	temp |= (1 << 10);
	else if(channel_count == 10)	temp |= (5 << 10);
	else
		temp |= (channel_count << 10);

//	temp &= 0xfe7f;
//	temp |= (range[channel_count] << 7);

	GPIO_Write(GPIOC,temp | 0x200);

	range_set_func(range[channel_count]);
#endif
	
	
}


u16 ADC_getChannal(ADC_TypeDef* ADCx, u8 channal)
{
	uint16_t tem = 0;
	ADC_ClearFlag(ADCx, ADC_FLAG_EOC);
	ADC_RegularChannelConfig(ADCx, channal, 1, ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);         
	while(ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == RESET);
	tem = ADC_GetConversionValue(ADCx);
	return tem;        
}

 
 void range_set_func(u8 range)
 {
	 if(range == V0_5)
	 {
			RANGE_SET0 = 1 ;
			RANGE_SET1 = 0 ;
	 }
	 else if (range == V0_10)
	 {
			RANGE_SET0 = 0 ;
			RANGE_SET1 = 1 ;
	 }
	 	 else if (range == I0_20ma)
	 {
			RANGE_SET0 = 0 ;
			RANGE_SET1 = 0 ;
	 }
	 else
	 {
			RANGE_SET0 = 1 ;
			RANGE_SET1 = 1 ;
	 }
 }
 

 /*
 LINE8------------>	HSP_INPUT1
 LINE9------------>	HSP_INPUT2
 LINE10------------>	HSP_INPUT3
 LINE11------------>	HSP_INPUT4
 LINE12------------>	HSP_INPUT5
 LINE13------------>	HSP_INPUT6
*/

 const struct
 {
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	uint8_t PortSource;
	uint8_t PinSource;
	uint8_t NVIC_IRQChannel;
	uint32_t Exit_line ; 
	 
 } _STR_PLUSE_SETTING_[6] = 
 {
#ifdef BB
	{GPIOB, GPIO_Pin_8, GPIO_PortSourceGPIOB, GPIO_PinSource8, EXTI9_5_IRQn, EXTI_Line8},
	{GPIOB, GPIO_Pin_9, GPIO_PortSourceGPIOB, GPIO_PinSource9, EXTI9_5_IRQn, EXTI_Line9},
	{GPIOB, GPIO_Pin_10, GPIO_PortSourceGPIOB, GPIO_PinSource10, EXTI15_10_IRQn, EXTI_Line10},
	{GPIOB, GPIO_Pin_11, GPIO_PortSourceGPIOB, GPIO_PinSource11, EXTI15_10_IRQn, EXTI_Line11},
	{GPIOB, GPIO_Pin_12, GPIO_PortSourceGPIOB, GPIO_PinSource12, EXTI15_10_IRQn, EXTI_Line12},
	{GPIOB, GPIO_Pin_13, GPIO_PortSourceGPIOB, GPIO_PinSource13, EXTI15_10_IRQn, EXTI_Line13},
#endif
	
#ifdef TB	
	{GPIOB, GPIO_Pin_10, GPIO_PortSourceGPIOB, GPIO_PinSource10, EXTI15_10_IRQn, EXTI_Line10},
	{GPIOB, GPIO_Pin_11, GPIO_PortSourceGPIOB, GPIO_PinSource11, EXTI15_10_IRQn, EXTI_Line11},
	{GPIOB, GPIO_Pin_12, GPIO_PortSourceGPIOB, GPIO_PinSource12, EXTI15_10_IRQn, EXTI_Line12},
	{GPIOB, GPIO_Pin_13, GPIO_PortSourceGPIOB, GPIO_PinSource13, EXTI15_10_IRQn, EXTI_Line13},
	{GPIOB, GPIO_Pin_14, GPIO_PortSourceGPIOB, GPIO_PinSource14, EXTI15_10_IRQn, EXTI_Line14},
	{GPIOB, GPIO_Pin_15, GPIO_PortSourceGPIOB, GPIO_PinSource15, EXTI15_10_IRQn, EXTI_Line15},
#endif	
 };
 
  void pulse_set(uint8_t channel,uint8_t rise_or_fall)
 {
	u8 port_source ;
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	GPIO_InitStructure.GPIO_Pin = _STR_PLUSE_SETTING_[channel].GPIO_Pin ;	
//	 if(rise_or_fall == RISE)
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
//	 else
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(_STR_PLUSE_SETTING_[channel].GPIOx, &GPIO_InitStructure);
	GPIO_SetBits(_STR_PLUSE_SETTING_[channel].GPIOx, _STR_PLUSE_SETTING_[channel].GPIO_Pin );
	
	 
	GPIO_EXTILineConfig(_STR_PLUSE_SETTING_[channel].PortSource, _STR_PLUSE_SETTING_[channel].PinSource ); 
	EXTI_InitStructure.EXTI_Line  = _STR_PLUSE_SETTING_[channel].Exit_line ; 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	if(rise_or_fall == RISE)
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	else
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	
	
	NVIC_InitStructure.NVIC_IRQChannel = _STR_PLUSE_SETTING_[channel].NVIC_IRQChannel ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
 
 }
 
#ifdef BB
void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & (1 << 8))	//是8线的中断
	{      
		EXTI->PR  = (1 << 8);	//清除LINE8上的中断标志位
		
		if(high_speed_flag[0] == 1)
		{
			high_speed_counter[0].longbyte++;
			test[30]++;
		}
//		data_change |= (1<<0) ;
	}
	if(EXTI->PR & (1 << 9))	//是9线的中断
	{      
		EXTI->PR  = (1 << 9);	//清除LINE9上的中断标志位
		if(high_speed_flag[1] == 1)
		{
			high_speed_counter[1].longbyte++;	test[31]++;
		}
//		data_change |= (1<<1) ;
	}
}
#endif

void EXTI15_10_IRQHandler(void)
{
#ifdef BB
	if(EXTI->PR & (1 << 10))	//是10线的中断
	{      
		EXTI->PR  = (1 << 10);	//清除LINE10上的中断标志位
		if(high_speed_flag[2] == 1)
		{
			high_speed_counter[2].longbyte++;	test[32]++;

		}
//		data_change |= (1<<2) ;
	}
	if(EXTI->PR & (1 << 11))	//是11线的中断
	{      
		EXTI->PR  = (1 << 11);	//清除LINE11上的中断标志位
		if(high_speed_flag[3] == 1)
		{
			high_speed_counter[3].longbyte++; test[33]++;
		}
//		data_change |= (1<<3) ;
	}
	if(EXTI->PR & (1 << 12))	//是12线的中断
	{      
		EXTI->PR  = (1 << 12);	//清除LINE12上的中断标志位
		if(high_speed_flag[4] == 1)
		{
			high_speed_counter[4].longbyte++; test[34]++;
		}
//		data_change |= (1<<4) ;
	}
	if(EXTI->PR & (1 << 13))	//是13线的中断
	{      
		EXTI->PR  = (1 << 13);	//清除LINE13上的中断标志位
		if(high_speed_flag[5] == 1)
		{
			high_speed_counter[5].longbyte++; test[35]++;
		}
//		data_change |= (1<<5) ;
	}
#endif
	
#ifdef TB
	if(EXTI->PR & (1 << 10))	//是10线的中断
	{      
		EXTI->PR  = (1 << 10);	//清除LINE10上的中断标志位
		if(high_speed_flag[0] == 1)
			high_speed_counter[0].longbyte++;
		test[30]++;
	}
	if(EXTI->PR & (1 << 11))	//是11线的中断
	{      
		EXTI->PR  = (1 << 11);	//清除LINE11上的中断标志位
		if(high_speed_flag[1] == 1)
			high_speed_counter[1].longbyte++;
		test[31]++;
	}
	if(EXTI->PR & (1 << 12))	//是12线的中断
	{      
		EXTI->PR  = (1 << 12);	//清除LINE12上的中断标志位
		if(high_speed_flag[2] == 1)
			high_speed_counter[2].longbyte++;
		test[32]++;
	}
	if(EXTI->PR & (1 << 13))	//是13线的中断
	{      
		EXTI->PR  = (1 << 13);	//清除LINE13上的中断标志位
		if(high_speed_flag[3] == 1)
			high_speed_counter[3].longbyte++;
		test[33]++;
	}
	if(EXTI->PR & (1 << 14))	//是14线的中断
	{      
		EXTI->PR  = (1 << 14);	//清除LINE14上的中断标志位
		if(high_speed_flag[4] == 1)
			high_speed_counter[4].longbyte++;
		test[34]++;
	}
	if(EXTI->PR & (1 << 15))	//是15线的中断
	{      
		EXTI->PR  = (1 << 15);	//清除LINE15上的中断标志位
		if(high_speed_flag[5] == 1)
			high_speed_counter[5].longbyte++;
		test[35]++;
	}
#endif
}


 
 