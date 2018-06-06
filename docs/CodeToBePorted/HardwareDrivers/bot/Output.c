#include "main.h"
#include "serial.h"



#if MINI
#if ARM
	// PB.7 -> AO_GP1_EN
	// PC.0 -> AO_GP2_EN
	// PA.13 -> AO_CHSEL0
	// PA.14 -> AO_CHSEL1
	// PB.6 -> AO_CHSEL2
/*   FOR BB's IO defination  */
#define AO_GP1_EN 	PBout(7)
#define AO_GP2_EN 	PCout(0)
#define AO_CHSEL0 	PAout(13)
#define AO_CHSEL1 	PAout(14)
#define AO_CHSEL2 	PBout(6)


/*   FOR LB's IO defination  */
// PB.0 -> AO1 TIM3_CH3
// PB.1 -> AO2 TIM3_CH4
// PB.6 -> AO3 TIM4_CH1
// PB.7 -> AO4 TIM4_CH2
// PA.4 -> AO_FB1 
// PC.0 -> AO_FB2 
// PC.3 -> AO_FB3 
// PC.5 -> AO_FB4 

#define LB_REALY1	PEout(2)
#define LB_REALY2	PEout(3)
#define LB_REALY3	PGout(7)
#define LB_REALY4	PGout(8)
#define LB_REALY5	PGout(9)
#define LB_REALY6	PGout(10)


/*   FOR TB's IO defination  */
// PB.6 -> AO1 TIM4_CH1
// PB.7 -> AO2 TIM4_CH2
// PB.8 -> AO3 TIM4_CH3
// PB.9 -> AO4 TIM4_CH4
// PC.0 -> AO_FB1 ADC123_IN10
// PC.1 -> AO_FB2 ADC123_IN11
// PC.2 -> AO_FB3 ADC123_IN12
// PC.3 -> AO_FB4 ADC123_IN13

#define TB_REALY1	PCout(6)
#define TB_REALY2	PCout(7)
#define TB_REALY3	PBout(8)
#define TB_REALY4	PBout(6)
#define TB_REALY5	PAout(0)
#define TB_REALY6	PAout(1)
#define TB_REALY7	PFout(7)
#define TB_REALY8	PCout(3)

void Choose_AO(u8 i)
{
	switch(i)
	{
		case 0:
			AO_GP1_EN = 1;AO_GP2_EN = 1;AO_CHSEL0 = 0;AO_CHSEL1 = 0;AO_CHSEL2 = 0;
			break;
		case 1:
			AO_GP1_EN = 1;AO_GP2_EN = 1;AO_CHSEL0 = 1;AO_CHSEL1 = 0;AO_CHSEL2 = 0;
			break;
		case 2:
			AO_GP1_EN = 1;AO_GP2_EN = 1;AO_CHSEL0 = 0;AO_CHSEL1 = 1;AO_CHSEL2 = 0;
			break;
		case 3:
			AO_GP1_EN = 1;AO_GP2_EN = 1;AO_CHSEL0 = 1;AO_CHSEL1 = 1;AO_CHSEL2 = 0;
			break;
		case 4:
			AO_GP1_EN = 1;AO_GP2_EN = 1;AO_CHSEL0 = 0;AO_CHSEL1 = 0;AO_CHSEL2 = 1;
			break;
		case 5:
			AO_GP1_EN = 1;AO_GP2_EN = 1;AO_CHSEL0 = 1;AO_CHSEL1 = 0;AO_CHSEL2 = 1;
			break;
		case 6:
			AO_GP1_EN = 1;AO_GP2_EN = 1;AO_CHSEL0 = 0;AO_CHSEL1 = 0;AO_CHSEL2 = 0;
			break;
		case 7:
			AO_GP1_EN = 1;AO_GP2_EN = 1;AO_CHSEL0 = 1;AO_CHSEL1 = 0;AO_CHSEL2 = 0;
			break;
		case 8:
			AO_GP1_EN = 1;AO_GP2_EN = 1;AO_CHSEL0 = 0;AO_CHSEL1 = 1;AO_CHSEL2 = 0;
			break;
		case 9:
			AO_GP1_EN = 1;AO_GP2_EN = 1;AO_CHSEL0 = 1;AO_CHSEL1 = 1;AO_CHSEL2 = 0;
			break;
		case 10:
			AO_GP1_EN = 1;AO_GP2_EN = 1;AO_CHSEL0 = 0;AO_CHSEL1 = 0;AO_CHSEL2 = 1;
			break;
		case 11:
			AO_GP1_EN = 1;AO_GP2_EN = 1;AO_CHSEL0 = 1;AO_CHSEL1 = 0;AO_CHSEL2 = 1;
			break;
		default:
			break;

	}
		
}
void Output_IO_Init(void);



void Output_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	

	if((Modbus.mini_type == MINI_BIG) || (Modbus.mini_type == MINI_BIG_ARM))
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;  //TIM3_CH3-4
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		// PB.7 -> AO_GP1_EN
		// PC.0 -> AO_GP2_EN
		// PA.13 -> AO_CHSEL0
		// PA.14 -> AO_CHSEL1
		// PB.6 -> AO_CHSEL2
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;			
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  						
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);										
		GPIO_ResetBits(GPIOB, GPIO_Pin_6 | GPIO_Pin_7);

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  						
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);										
		GPIO_ResetBits(GPIOC, GPIO_Pin_0);
		
		TIM_TimeBaseStructure.TIM_Period = 1000;
		TIM_TimeBaseStructure.TIM_Prescaler = 0;
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
		
		TIM_OC3Init(TIM3, &TIM_OCInitStructure);
		TIM_OC4Init(TIM3, &TIM_OCInitStructure);
		
		TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
		TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
		
		TIM_Cmd(TIM3, ENABLE);
	}
	else if((Modbus.mini_type == MINI_SMALL) || (Modbus.mini_type == MINI_SMALL_ARM))
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOG | RCC_APB2Periph_AFIO, ENABLE);
	//	GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;  //REALY 1 RELAY 2
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOE, &GPIO_InitStructure);
		GPIO_ResetBits(GPIOE, GPIO_Pin_2 | GPIO_Pin_3);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;  //REALY 3 RELAY 4 REALY 5 RELAY 6
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOG, &GPIO_InitStructure);
		GPIO_ResetBits(GPIOG, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;		// AO 1,2,3,4	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  						
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
		
	
		
		TIM_TimeBaseStructure.TIM_Period = 1000;
		TIM_TimeBaseStructure.TIM_Prescaler = 0;
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
		
		TIM_OC3Init(TIM3, &TIM_OCInitStructure);  // AO1
		TIM_OC4Init(TIM3, &TIM_OCInitStructure);  // AO2
		TIM_OC1Init(TIM3, &TIM_OCInitStructure);  // AO3
		TIM_OC2Init(TIM3, &TIM_OCInitStructure);  // AO4
		
		TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
		TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
		TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
		
		TIM_Cmd(TIM3, ENABLE);

// intial AO_FB


	}
	else if((Modbus.mini_type == MINI_NEW_TINY) || (Modbus.mini_type == MINI_TINY_ARM))
	{
		RCC_APB1PeriphClockCmd(/*RCC_APB1Periph_TIM2 |*/ RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM5, ENABLE);
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
//		GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_3;  //REALY 1 - RELAY 2 RELAY8
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC,&GPIO_InitStructure);
		GPIO_ResetBits(GPIOC, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_3);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8;  //REALY 3 - RELAY 4
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_InitStructure);
		GPIO_ResetBits(GPIOB, GPIO_Pin_6 | GPIO_Pin_8);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 /*| GPIO_Pin_2 | GPIO_Pin_3*/;  // REALY 5 - RELAY 6
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 /*| GPIO_Pin_2 | GPIO_Pin_3*/);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  // REALY 7 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOF, &GPIO_InitStructure);
		GPIO_ResetBits(GPIOF, GPIO_Pin_7);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7;		// AO 1,2 AO5,AO6
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  						
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);										

		GPIO_InitStructure.GPIO_Pin = /*GPIO_Pin_10 | GPIO_Pin_11 |*/ GPIO_Pin_0 | GPIO_Pin_1;		// AO 3,4
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  						
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);		
	
		TIM_TimeBaseStructure.TIM_Period = 1000;
		TIM_TimeBaseStructure.TIM_Prescaler = 0;
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
		
		TIM_OC3Init(TIM5, &TIM_OCInitStructure);  // AO1 PA2 	TIM5_CH3
		TIM_OC4Init(TIM5, &TIM_OCInitStructure);  // AO2 PA3 	TIM5_CH4
//		TIM_OC3Init(TIM2, &TIM_OCInitStructure);  // AO3 PB10 TIM2_CH3
//		TIM_OC4Init(TIM2, &TIM_OCInitStructure);  // AO4 PB11 TIM2_CH4
		TIM_OC3Init(TIM3, &TIM_OCInitStructure);  // AO3 PB0	TIM3_CH3 	
		TIM_OC4Init(TIM3, &TIM_OCInitStructure);  // AO4 PB1	TIM3_CH4	
		TIM_OC1Init(TIM3, &TIM_OCInitStructure);  // AO5 PA6 	TIM3_CH1
		TIM_OC2Init(TIM3, &TIM_OCInitStructure);  // AO6 PA7	TIM3_CH2
		
		TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);
		TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
//		TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
//		TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
		TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
		TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
		TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
		
//		TIM_Cmd(TIM2, ENABLE);
		TIM_Cmd(TIM3, ENABLE);
		TIM_Cmd(TIM5, ENABLE);
	}

}

#endif

#define OutputSTACK_SIZE				( ( unsigned portSHORT ) 1024 )

U16_T far relay_value_auto;
UN_RELAY relay_value;

#define ADJUST_AUTO 1

U8_T far flag_output;
U16_T flag_output_changed;


U8_T  AnalogOutput_refresh_index = 0;

//--- variables define --------//

xTaskHandle xHandler_Output;
//extern U8_T data outputs[i].switch_status[24];  // read from top board

//extern U8_T OutputLed[24];

U8_T DigtalOutput_Channel = 0; // the current digtal output channel
U8_T AnalogOutput_Channel = 0; // the current analog output channel


U8_T tick; 
U8_T ccap_low;
extern U16_T test_adc;
extern U8_T test_adc_flag;



void Refresh_Output(void);
void Calucation_PWM_IO(U8_T refresh_index);

/*
 *--------------------------------------------------------------------------------
 * void Initial_PWM(void)
 * Purpose : initial PWM moduel
 * Params  : none
 * Returns : none
 * Note    : used after Intial_E2prom
 //CPS Description
//000 Reference timing tick = operating system clock divided by 25.
//001 Reference timing tick = operating system clock divided by 19.
//010 Reference timing tick = operating system clock divided by 8.
//011 Reference timing tick = operating system clock divided by 6.
//100 Reference timing tick = Timer 0 overflow rate.
//111 Reference timing tick = external clock at ECI pin (the max input

 *--------------------------------------------------------------------------------
 */
U8_T table_pwm[8];
U8_T slop[10];
//U16_T start_adc[11];
//U8_T const code table_pwm[6] = {0 , 4 , 2 ,6 , 1 , 5 /*, 3 , 7*/};
//U8_T slop[10] = {70,30,28,22,70,90,80,100,80,20};
//U16_T start_adc[10] = {0,70,100,128,160,230,420,600,700,880};



void cal_slop(void)
{
	U8_T i;
	for(i = 0;i < 10;i++)
	{
		slop[i] = Modbus.start_adc[i+1] - Modbus.start_adc[i];
	}
}

//U8_T const code slop[10] = {65,30,25,35,95,170,180,100,80,20};
//U16_T const code start_adc[10] = {0,65,95,120,155,250,420,600,700,880};
//U16_T const code start_adc[10] = {0,100,200,300,400,500,600,700,800,900};
/* add adjust output */
U16_T conver_ADC(U16_T adc)
{
	U8_T far seg;
	U16_T far real_adc = 0;

	if(adc <= 0)	return 0;
	if((adc >= 1000))  return 1000;

	
	seg = adc / 100;
	real_adc = Modbus.start_adc[seg] + (U16_T)(adc % 100) * slop[seg] / 100;
	
	if(real_adc > 1000) return 1000;
	else if(real_adc < 0) return 0;
	
	return real_adc;


}



U16_T far AO_auto[24];
U8_T far AO_auto_count[12];

void Read_feedback(void);

U16_T Auto_Calibration_AO(U8_T channel,U16_T adc)
{	
//	U8_T step = 0;
	U8_T base;
	U8_T error;	
	

	if(AO_auto_count[channel] == 0) // first time, use static, calibrate AO on next time
	{
		AO_auto_count[channel]++;
		return adc;
	}
	
	if(flag_output_changed & (0x01 << channel))
	{
		if(Modbus.mini_type != MINI_TINY)
		{
			Read_feedback();
		}
		// if tiny ,get feedback from SPI
		// FOR big & small, get feedback from PIC
	}
	else
	{
		return adc;
	}

	AO_auto_count[channel]++;
	
	if((Modbus.mini_type == MINI_BIG) || (Modbus.mini_type == MINI_BIG_ARM))	
	{
		base = 12;
	}
	else if((Modbus.mini_type == MINI_SMALL) || (Modbus.mini_type == MINI_SMALL_ARM))
	{
		base = 6;
	}
	else if(Modbus.mini_type == MINI_TINY)
	{
		base = 4;
	}
	else
		return 0;

	if(adc <= 0)	adc = 0;
	if((adc > 1000))  adc = 1000;

	if(output_raw[base + channel] >= 990)
	{
		if(AO_feedback[channel] > 980)
		{
			flag_output_changed &= ~(0x01 << channel);			
		}
		AO_auto_count[channel] = 0;
		return 1000;
	}
	else if(output_raw[base + channel] <= 10)
	{
		if(AO_feedback[channel] < 10)
		{
			flag_output_changed &= ~(0x01 << channel);			
		}
		AO_auto_count[channel] = 0;
		return 0;
	}
	else
	{
		if((AO_feedback[channel] > output_raw[base + channel] - 5)  && (AO_feedback[channel] < output_raw[base + channel] + 5))
		{	// error is 20, in this range, dont adjust
			if(output_raw[base + channel] % 100 == 0)  // 1v 2v ... 10v
			{

				E2prom_Write_Byte(EEP_OUT_1V + (output_raw[base + channel] / 100 - 1) * 2,adc / 256);
				E2prom_Write_Byte(EEP_OUT_1V + (output_raw[base + channel] / 100 - 1) * 2 + 1,adc % 256);
				Modbus.start_adc[output_raw[base + channel] / 100] = adc;
			}
			AO_auto_count[channel] = 0;
			flag_output_changed &= ~(0x01 << channel);
			if(AO_feedback[channel] > output_raw[base + channel])
				return adc - 3;
			else 
				return adc + 3;
		}
		else
		{				
			if(AO_feedback[channel] > output_raw[base + channel])	  // larger then aim value, decrease adc
			{	
				error = AO_feedback[channel] - output_raw[base + channel];
				if(adc > error)
					return (adc - error / 2);
				else
					return adc;
			}
			else 		// less then aim value, increase adc
			{
				error =  output_raw[base + channel] - AO_feedback[channel];
				if(adc < 1000 - error)
					return (adc + error / 2);
				else
					return adc;
			}
		}
	}
}


 
void Initial_PWM(void)
{
	U8_T loop;


	Output_IO_Init();
	flag_output = 0;
	

	DigtalOutput_Channel = 0; // the current digtal output channel
	AnalogOutput_Channel = 0;


	test_adc = 0;
	test_adc_flag = 0;
	


	flag_output_changed = 0;

	memset(AO_feedback,0,32);
	memset(AO_auto,0,48);
	memset(AO_auto_count,0,12);

	for(loop = 0;loop < 24;loop++)		
		outputs[loop].switch_status = SW_AUTO;

}



 
void Calucation_PWM_IO(U8_T refresh_index)
{
	U32_T duty_Cycle1,duty_Cycle2;
	U32_T temp1,temp2;
//	U8_T loop;
	U32_T far adc1;
	U32_T far adc2; /* adc1 is for the first 4051, adc2 is for the second 4051 */


	if((Modbus.mini_type == MINI_BIG) || (Modbus.mini_type == MINI_BIG_ARM))
		Choose_AO(refresh_index);


	/* Analog OUTPUT1 - OUPUT6*/
	if((Modbus.mini_type == MINI_BIG) || (Modbus.mini_type == MINI_BIG_ARM))
	{
		if(outputs[refresh_index + 12].switch_status == SW_AUTO)
		{
			if(outputs[refresh_index + 12].digital_analog == 0) // digital
			{
				if(output_raw[refresh_index + 12] >= 512)
					adc1 = Modbus.start_adc[10];//1000;
				else
					adc1 = 0;
			}
			else // analog
				adc1 = output_raw[refresh_index + 12];
		}
		else if(outputs[refresh_index + 12].switch_status == SW_OFF)
			adc1 = 0;
		else if(outputs[refresh_index + 12].switch_status == SW_HAND)
			adc1 = Modbus.start_adc[10];//1000;
			
			/* Analog OUTPUT7 - OUPUT12*/
		if(outputs[refresh_index + 18].switch_status == SW_AUTO)		
		{
			if(outputs[refresh_index + 18].digital_analog == 0) // digital
			{
				if(output_raw[refresh_index + 18] >= 512)
					adc2 = Modbus.start_adc[10];//1000;
				else
					adc2 = 0;
			}
			else // analog
				adc2 = output_raw[refresh_index + 18];
		}
		else if(outputs[refresh_index + 18].switch_status == SW_OFF)
			adc2 = 0;
		else if(outputs[refresh_index + 18].switch_status == SW_HAND)
			adc2 = Modbus.start_adc[10];//1000;
		// if output is used for a digtal output, do not use feedback to adjust
		if(flag_output == ADJUST_AUTO && outputs[refresh_index + 12].switch_status == SW_AUTO && outputs[refresh_index + 12].digital_analog == 1)
		{
			adc1 = Auto_Calibration_AO(refresh_index,AO_auto[refresh_index + 12]);
			AO_auto[refresh_index + 12] = adc1;
		}
		else
			adc1 = AO_auto[refresh_index + 12];//conver_ADC(adc1);
		
		if(flag_output == ADJUST_AUTO && outputs[refresh_index + 18].switch_status == SW_AUTO && outputs[refresh_index + 18].digital_analog == 1)
		{ 
			adc2 = Auto_Calibration_AO(refresh_index + 6,AO_auto[refresh_index + 18]);
			AO_auto[refresh_index + 18] = adc2;
		}
		else
			adc2 = AO_auto[refresh_index + 18];// conver_ADC(adc2);		


		if(refresh_index == 0) 
		{
			if(test_adc_flag == 1)	adc1 = test_adc;
			test_adc = adc1;
		}
		
		if(outputs[refresh_index + 12].range == 0)
			adc1 = 0;
			
		if(outputs[refresh_index + 18].range == 0)
			adc2 = 0;
		
		duty_Cycle1 = adc1;
		if(duty_Cycle1 > Modbus.start_adc[10]) duty_Cycle1 = Modbus.start_adc[10];//1000;

	
		duty_Cycle2 = adc2;
		if(duty_Cycle2 > Modbus.start_adc[10]) duty_Cycle2 = Modbus.start_adc[10];//1000;
		
	
		TIM_SetCompare3(TIM3, duty_Cycle1);
		TIM_SetCompare4(TIM3, duty_Cycle2);
	}
	else if((Modbus.mini_type == MINI_SMALL) || (Modbus.mini_type == MINI_SMALL_ARM))
	{	/* Analog OUTPUT1 - OUPUT4*/			

		if(outputs[refresh_index + 6].switch_status == SW_AUTO)
		{
			if(outputs[refresh_index + 6].digital_analog == 0) // digital
			{
				if(output_raw[refresh_index + 6] >= 512)
					adc1 = Modbus.start_adc[10];//1000;
				else
					adc1 = 0;
			}
			else // analog
				adc1 = output_raw[refresh_index + 6];
		}
		else if(outputs[refresh_index + 6].switch_status == SW_OFF)
			adc1 = 0;
		else if(outputs[refresh_index + 6].switch_status == SW_HAND)
			adc1 = Modbus.start_adc[10];//1000;
		
// if output is used for a digtal output, do not use feedback to adjust
		if(flag_output == ADJUST_AUTO && outputs[refresh_index + 6].switch_status == SW_AUTO && outputs[refresh_index + 6].digital_analog == 1)
		{
			adc1 = Auto_Calibration_AO(refresh_index,AO_auto[refresh_index + 6]);
			AO_auto[refresh_index + 6] = adc1;
		}
		else
			adc1 = conver_ADC(adc1);

		if(refresh_index == 0) 
		{
			if(test_adc_flag == 1)	adc1 = test_adc;
			test_adc = adc1;
		}
		
		if(outputs[refresh_index + 6].range == 0)		
			adc1 = 0;

		duty_Cycle1 = adc1;
		if(duty_Cycle1 > Modbus.start_adc[10]) duty_Cycle1 = Modbus.start_adc[10];//1000;
		temp1 = (U32_T)255 * (1000 - duty_Cycle1) / 1000;
		temp1 = temp1 * 256 + ccap_low;	


		if(refresh_index == 0)
			TIM_SetCompare3(TIM3, duty_Cycle1);	
		else if(refresh_index == 1)
			TIM_SetCompare4(TIM3, duty_Cycle1);
		else if(refresh_index == 2)
			TIM_SetCompare1(TIM3, duty_Cycle1);
		else if(refresh_index == 3)
			TIM_SetCompare2(TIM3, duty_Cycle1);
	}

	else if((Modbus.mini_type == MINI_NEW_TINY) || (Modbus.mini_type == MINI_TINY_ARM))
	{
	if(outputs[refresh_index + 8].switch_status == SW_AUTO)
		{
			if(outputs[refresh_index + 8].digital_analog == 0) // digital
			{
				if(output_raw[refresh_index + 8] >= 512)
					adc1 = Modbus.start_adc[10];
				else
					adc1 = 0;
			}
			else // analog
				adc1 = output_raw[refresh_index + 8];
		}
		else if(outputs[refresh_index + 8].switch_status == SW_OFF)
			adc1 = 0;
		else if(outputs[refresh_index + 8].switch_status == SW_HAND)
			adc1 = Modbus.start_adc[10];//1000;

// if output is used for a digtal output, do not use feedback to adjust
		if(flag_output == ADJUST_AUTO && outputs[refresh_index + 8].switch_status == SW_AUTO && outputs[refresh_index + 8].digital_analog == 1)
		{
			
	   adc1 = Auto_Calibration_AO(refresh_index,AO_auto[refresh_index + 8]);
	   AO_auto[refresh_index + 8] = adc1;
		}
		else
			adc1 = conver_ADC(adc1);

		
		if(refresh_index == 0) 
		{
			if(test_adc_flag == 1)	
				adc1 = test_adc;
			test_adc = adc1;
		}

		duty_Cycle1 = adc1;
		if(duty_Cycle1 > Modbus.start_adc[10]) duty_Cycle1 = Modbus.start_adc[10];
		temp1 = (U32_T)255 * (1000 - duty_Cycle1) / 1000;
		temp1 = temp1 * 256 + ccap_low;		
		
		if(refresh_index == 0)
			TIM_SetCompare3(TIM5, duty_Cycle1);	
		else if(refresh_index == 1)
			TIM_SetCompare4(TIM5, duty_Cycle1);
//		else if(refresh_index == 2)
//			TIM_SetCompare3(TIM2, duty_Cycle1);	
//		else if(refresh_index == 3)
//			TIM_SetCompare4(TIM2, duty_Cycle1);
		else if(refresh_index == 2)
			TIM_SetCompare3(TIM3, duty_Cycle1);
		else if(refresh_index == 3)
			TIM_SetCompare4(TIM3, duty_Cycle1);
		else if(refresh_index == 4)
			TIM_SetCompare1(TIM3, duty_Cycle1);	
		else if(refresh_index == 5)
			TIM_SetCompare2(TIM3, duty_Cycle1);
	}


}

/*--------------------------------------------------------------------------------
 * void vStartSPITasks( unsigned char uxPriority)
 * Purpose : start SPI_task and create Queue management for Cmd 
 * Params  : uxPriority - priority for spi_task
 * Returns : none
 * Note    :
 *--------------------------------------------------------------------------------
 */
void vStartOutputTasks( unsigned char uxPriority)
{
	Initial_PWM();

	sTaskCreate( Refresh_Output, "OutputTask1", OutputSTACK_SIZE, NULL, uxPriority, &xHandler_Output );

	relay_value.word = 0;
}


//#ifdef VAV
// level range is 0 - 100
void SET_VAV(U8_T level)
{
	uart_init_send_com(1);
	uart_send_byte(0xff,1);
	uart_send_byte(0x00,1);
	uart_send_byte(level,1);
	uart_send_byte((U8_T)(0xff + 0x00 + level),1);
}

void READ_VAV(U8_T *level)
{
	U8_T length;
	uart_init_send_com(1);
	uart_send_byte(0xff,1);
	uart_send_byte(0x01,1);
	uart_send_byte(0x00,1);
	uart_send_byte((U8_T)(0xff + 0x01 + 0),1);
	set_subnet_parameters(RECEIVE,4,1);
	if(length = wait_subnet_response(500,1))
	{
		if(subnet_response_buf[0] == 0xff && subnet_response_buf[1] == 0x01 &&  
			subnet_response_buf[3] == (U8_T)(subnet_response_buf[0] + subnet_response_buf[1] + subnet_response_buf[2]))
		{
			*level = subnet_response_buf[2];
		}
	}
	else
	{
		
	}
		
}

//#endif

void Refresh_Output(void)
{
	portTickType xDelayPeriod = ( portTickType ) 50 / portTICK_RATE_MS;
	U8_T i = 0;			
	UN_RELAY temp1;
	U16_T far pwm_count[12];
	U8_T DO_change_count;
	U8_T flag_DO_changed;
	task_test.enable[5] = 1;
	DO_change_count = 0;
	for(i = 0;i < 12;i++)
		pwm_count[i] = 0;
	for (;;)
	{
		vTaskDelay( 50 / portTICK_RATE_MS);	
		task_test.count[5]++;
		if((Modbus.mini_type == MINI_BIG) || (Modbus.mini_type == MINI_BIG_ARM))
		{		
		//	U8_T temp2;
			temp1.word = relay_value_auto;
			
			for(i = 0;i < 12;i++)
			{					
				if(outputs[i].switch_status == SW_AUTO )
				{
					if(outputs[i].digital_analog == 0)  // digital
					{
						if(output_raw[i] >= 512)						
							temp1.word |= (0x01 << i);
						else
							temp1.word &= ~(BIT0 << i); 
					}
					else  // analog  , PWM mode
					{
						if(pwm_count[i] < (U32_T)outputs[i].pwm_period * 20)
						{
							pwm_count[i]++;
						}
						else
							pwm_count[i] = 0;
						
						if(pwm_count[i] < (U32_T)outputs[i].pwm_period * 20 * output_raw[i] / 1023)
						{
							temp1.word |= (0x01 << i);
						}
						else 
						{
							temp1.word &= ~(BIT0 << i); 
						}
					}
				}
				else if (outputs[i].switch_status == SW_OFF )			
					temp1.word &= ~(BIT0 << i); 		
				else if (outputs[i].switch_status == SW_HAND )	  
					temp1.word |= (BIT0 << i);
										
			}
			

			
			if(temp1.byte[0] != relay_value.byte[0])
			{
				flag_DO_changed = 1;
				DO_change_count = 0;
				relay_value.byte[0]  = temp1.byte[0];	
				push_cmd_to_picstack(SET_RELAY_LOW,relay_value.byte[0]); 
		
			}
			
			if(temp1.byte[1] != relay_value.byte[1])
			{
				flag_DO_changed = 1;
				DO_change_count = 0;
				relay_value.byte[1]  = temp1.byte[1];	
				push_cmd_to_picstack(SET_RELAY_HI,relay_value.byte[1]);
				
			}

			if(flag_DO_changed) 
			{
				DO_change_count++;
				if(DO_change_count > 200)  // keep stable for 500ms second,send command to pic again
				{
					flag_DO_changed = 0;
					DO_change_count = 0;

				push_cmd_to_picstack(SET_RELAY_LOW,relay_value.byte[0]); 
				push_cmd_to_picstack(SET_RELAY_HI,relay_value.byte[1]);
				
				}
				
			}
			
// check 12 AO, whether analog output is changed
			for(i = 0;i < 12;i++)
			{
				if(output_raw[i + 12] != output_raw_back[i + 12])
				{				
					output_raw_back[i + 12] = output_raw[i + 12];
					AO_auto[i + 12] = conver_ADC(output_raw[i + 12]);
					flag_output_changed |= (0x01 << i);
					AO_auto_count[i] = 0;
				}

				if(AO_auto_count[i] > 20)
					// generate alarm
				{
					AO_auto_count[i] = 0;
					flag_output = 0;
				// generate a alarm
					generate_common_alarm(ALARM_AO_FB);
				}
			}			

			
			Calucation_PWM_IO(AnalogOutput_refresh_index);
				
			if(AnalogOutput_refresh_index < 5)	  
				AnalogOutput_refresh_index++;
			else 	
				AnalogOutput_refresh_index = 0;	
					
			
		} 
		else if((Modbus.mini_type == MINI_SMALL) || (Modbus.mini_type == MINI_SMALL_ARM))
		{			
			for(i = 0;i < 6;i++)
			{	
				if(outputs[i].switch_status == SW_AUTO)
				{
					if(outputs[i].digital_analog == 0)  // digital
					{
						if(output_raw[i] >= 512)						
								temp1.word |= (0x01 << i);
						else
							temp1.word &= ~(BIT0 << i);
					}	
					else  // analog  , PWM mode
					{
						if(pwm_count[i] < (U32_T)outputs[i].pwm_period * 20)
						{
							pwm_count[i]++;
						}
						else
							pwm_count[i] = 0;
						
						if(pwm_count[i] < (U32_T)outputs[i].pwm_period * 20 * output_raw[i] / 1023)
						{
							temp1.word |= (0x01 << i);
						}
						else 
						{
							temp1.word &= ~(BIT0 << i); 
						}
					}					
				}
				else if (outputs[i].switch_status == SW_OFF )			
					temp1.word &= ~(BIT0 << i); 		
				else if (outputs[i].switch_status == SW_HAND )	
					temp1.word |= (BIT0 << i);
			}

			// check 4 AO, whether analog output is changed
			for(i = 0;i < 4;i++)
			{
				if(output_raw[i + 6] != output_raw_back[i + 6])
				{				
					output_raw_back[i + 6] = output_raw[i + 6];
					AO_auto[i + 6] = conver_ADC(output_raw[i + 6]);
					flag_output_changed |= (0x01 << i);
					AO_auto_count[i] = 0;
				}

				if(AO_auto_count[i] > 20)
					// generate alarm
				{
					AO_auto_count[i] = 0;
					flag_output = 0;
	// generate a alarm
					generate_common_alarm(ALARM_AO_FB);
				}
			}	
			if(temp1.word != relay_value.word)
			{
				flag_DO_changed = 1;
				DO_change_count = 0;
				
				relay_value.word = temp1.word;

				if(relay_value.byte[0] & 0x01) 					LB_REALY1 = 1;				else					LB_REALY1 = 0;
				if(relay_value.byte[0] & 0x02) 					LB_REALY2 = 1;				else					LB_REALY2 = 0;
				if(relay_value.byte[0] & 0x04) 					LB_REALY3 = 1;				else					LB_REALY3 = 0;
				if(relay_value.byte[0] & 0x08) 					LB_REALY4 = 1;				else					LB_REALY4 = 0;
				if(relay_value.byte[0] & 0x10) 					LB_REALY5 = 1;				else					LB_REALY5 = 0;
				if(relay_value.byte[0] & 0x20) 					LB_REALY6 = 1;				else					LB_REALY6 = 0;				
	
			}
			
			if(flag_DO_changed) 
			{
				DO_change_count++;
				if(DO_change_count > 200)  // keep stable for 500ms second,send command to pic again
				{
					flag_DO_changed = 0;
					DO_change_count = 0;
				
				if(relay_value.byte[0] & 0x01) 					LB_REALY1 = 1;				else					LB_REALY1 = 0;
				if(relay_value.byte[0] & 0x02) 					LB_REALY2 = 1;				else					LB_REALY2 = 0;
				if(relay_value.byte[0] & 0x04) 					LB_REALY3 = 1;				else					LB_REALY3 = 0;
				if(relay_value.byte[0] & 0x08) 					LB_REALY4 = 1;				else					LB_REALY4 = 0;
				if(relay_value.byte[0] & 0x10) 					LB_REALY5 = 1;				else					LB_REALY5 = 0;
				if(relay_value.byte[0] & 0x20) 					LB_REALY6 = 1;				else					LB_REALY6 = 0;				
	
				}
			}

			Calucation_PWM_IO(AnalogOutput_refresh_index);	
	
			if(AnalogOutput_refresh_index < 3)	  
				AnalogOutput_refresh_index++;
			else 	
				AnalogOutput_refresh_index = 0;			

		}			


		else if((Modbus.mini_type == MINI_NEW_TINY) || (Modbus.mini_type == MINI_TINY_ARM))
		{
			
			for(i = 0;i < 8;i++)
			{	
				// check range of OUT7 & OUT8, they are abled to config to AO or DO
//				if( ((i == 6) || (i == 7)) && (outputs[i].digital_analog == 1)) //  analog
//				{
//					temp1.word &= ~(BIT0 << i); 		
//				}
//				else
//				{
					if(outputs[i].switch_status == SW_AUTO)
					{						
						if(outputs[i].digital_analog == 0)  // digital
						{
							if(output_raw[i] >= 512)						
									temp1.word |= (0x01 << i);
							else
								temp1.word &= ~(BIT0 << i);
						}	
						else  // analog  , PWM mode
						{
							if(pwm_count[i] < (U32_T)outputs[i].pwm_period * 20)
							{
								pwm_count[i]++;
							}
							else
								pwm_count[i] = 0;
							
							if(pwm_count[i] < (U32_T)outputs[i].pwm_period * 20 * output_raw[i] / 1023)
							{
								temp1.word |= (0x01 << i);
							}
							else 
							{
								temp1.word &= ~(BIT0 << i); 
							}
						}
					}
					else if (outputs[i].switch_status == SW_OFF )			
						temp1.word &= ~(BIT0 << i); 		
					else if (outputs[i].switch_status == SW_HAND )	
						temp1.word |= (BIT0 << i);
				}

			
			
			if(temp1.word != relay_value.word)
			{
				flag_DO_changed = 1;
				DO_change_count = 0;
				
				relay_value.word = temp1.word;
				if(relay_value.byte[0] & 0x01) 					TB_REALY1 = 1;				else					TB_REALY1 = 0;
				if(relay_value.byte[0] & 0x02) 					TB_REALY2 = 1;				else					TB_REALY2 = 0;
				if(relay_value.byte[0] & 0x04) 					TB_REALY3 = 1;				else					TB_REALY3 = 0;
				if(relay_value.byte[0] & 0x08) 					TB_REALY4 = 1;				else					TB_REALY4 = 0;
				if(relay_value.byte[0] & 0x10) 					TB_REALY5 = 1;				else					TB_REALY5 = 0;
				if(relay_value.byte[0] & 0x20) 					TB_REALY6 = 1;				else					TB_REALY6 = 0;
				if(relay_value.byte[0] & 0x40) 					TB_REALY7 = 1;				else					TB_REALY7 = 0;
				if(relay_value.byte[0] & 0x80) 					TB_REALY8 = 1;				else					TB_REALY8 = 0;
			}			
		
			if(flag_DO_changed) 
			{
				DO_change_count++;
				if(DO_change_count > 200)  // keep stable for 500ms second,send command to pic again
				{
					flag_DO_changed = 0;
					DO_change_count = 0;
				
					if(relay_value.byte[0] & 0x01) 					TB_REALY1 = 1;				else					TB_REALY1 = 0;
					if(relay_value.byte[0] & 0x02) 					TB_REALY2 = 1;				else					TB_REALY2 = 0;
					if(relay_value.byte[0] & 0x04) 					TB_REALY3 = 1;				else					TB_REALY3 = 0;
					if(relay_value.byte[0] & 0x08) 					TB_REALY4 = 1;				else					TB_REALY4 = 0;
					if(relay_value.byte[0] & 0x10) 					TB_REALY5 = 1;				else					TB_REALY5 = 0;
					if(relay_value.byte[0] & 0x20) 					TB_REALY6 = 1;				else					TB_REALY6 = 0;
					if(relay_value.byte[0] & 0x40) 					TB_REALY7 = 1;				else					TB_REALY7 = 0;
					if(relay_value.byte[0] & 0x80) 					TB_REALY8 = 1;				else					TB_REALY8 = 0;	
				}
			}
			Calucation_PWM_IO(AnalogOutput_refresh_index);	
							
			if(AnalogOutput_refresh_index < 6)	  
				AnalogOutput_refresh_index++;
			else 	
				AnalogOutput_refresh_index = 0;	
			
		}			
	}
} 

#endif


