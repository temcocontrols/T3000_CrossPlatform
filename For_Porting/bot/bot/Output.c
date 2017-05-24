#include "main.h"
#include "serial.h"




#if MINI 

#include "pca.h"
#include "pca_cfg.h"


#define OutputSTACK_SIZE				( ( unsigned portSHORT ) 512 )

U16_T far relay_value_auto;
UN_RELAY relay_value;

U8_T far flag_output;

extern void DELAY_Us(U16_T loop);
extern U32_T Sysclk; 
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

	if(adc <= 0)	return 5;
	if((adc >= 1000))  return 1000;

	
	seg = adc / 100;
	real_adc = Modbus.start_adc[seg] + (U16_T)(adc % 100) * slop[seg] / 100;
	
//	if(real_adc > 1000) return 1000;
//	else if(real_adc < 0) return 0;
	
	return real_adc;


}


 
void Initial_PWM(void)
{
	U8_T loop;
	U8_T sysclk = 0;
	U32_T Sysclk; 
	sysclk = AX11000_GetSysClk();
	switch (sysclk)
	{
		case SYS_CLK_100M :
			Sysclk = 100000000;
			break;
		case SYS_CLK_50M :
			Sysclk = 50000000;
			break;
		case SYS_CLK_25M :
			Sysclk = 25000000;
			break;
	}
	for(loop = 0;loop < 24;loop++)		outputs[loop].switch_status = SW_OFF;

#if MINI
	CHSEL3 = 1;
#endif	  
	PCA_ModeSetup(0x07,0x40);   //  mode 011, con 0x40  ,so  tick is 6
	tick = 6;
	Sysclk = Sysclk / 6;
	ccap_low = 0xff;
	
#if MINI
	P3 &= 0xf0;	
	P3 |= 0x07; // dont select any channel 
#endif


	DigtalOutput_Channel = 0; // the current digtal output channel
	AnalogOutput_Channel = 0;
	table_pwm[0] = 0;
	table_pwm[1] = 4;
	table_pwm[2] = 2;
	table_pwm[3] = 6;
	table_pwm[4] = 1;
	table_pwm[5] = 5;
	table_pwm[6] = 3;
	table_pwm[7] = 7;

	test_adc = 0;
	test_adc_flag = 0;
	
	
	


	memset(AO_feedback,0,32);
//	memset(AO_auto,0,48);


}



 
void Calucation_PWM_IO(U8_T refresh_index)
{
	U32_T duty_Cycle1,duty_Cycle2;
	U32_T temp1,temp2;
//	U8_T loop;
	U32_T far adc1;
	U32_T far adc2; /* adc1 is for the first 4051, adc2 is for the second 4051 */

	/* CHSEL0 - CHSEL3: P3_0 ~ P3_3*/
//	refresh_index = 0;	

	if(Modbus.mini_type == MINI_TINY)
	{
		P3 &= 0xf0;	
		P3 |= table_pwm[refresh_index + 4] & 0x0f;
	}
	else if(Modbus.mini_type != MINI_VAV)
	{
		P3 &= 0xf0;	
		P3 |= table_pwm[refresh_index] & 0x0f;
	}
	/* must refresh all channel of the second 4051, the following is the refresh sequence
		C  		B  		A		first_4051			second_4051
		0 		0		0 		analogout1			analogout7
		0		0		1		analogout2			analogout8
		0		1		0		analogout3			analogout9
		0		1		1		analogout4			analogout10
		1		0		0		analogout5			analogout11
		1		0		1		analogout6			analogout12
		1		1		0			-					 -
		1		1		1			-					 -
	*/

	/* Analog OUTPUT1 - OUPUT6*/
	if(Modbus.mini_type == MINI_BIG)
	{
		if(outputs[refresh_index + 12].switch_status == SW_AUTO)
		{
			if(outputs[refresh_index + 12].digital_analog == 0) // digital
			{
				if(output_raw[refresh_index + 12] >= 512)
					adc1 = 1000;
				else
					adc1 = 0;
			}
			else // analog
				adc1 = output_raw[refresh_index + 12];
		}
		else if(outputs[refresh_index + 12].switch_status == SW_OFF)
			adc1 = 0;
		else if(outputs[refresh_index + 12].switch_status == SW_HAND)
			adc1 = 1000;
			
		
			/* Analog OUTPUT7 - OUPUT12*/
		if(outputs[refresh_index + 18].switch_status == SW_AUTO)		
		{
			if(outputs[refresh_index + 18].digital_analog == 0) // digital
			{
				if(output_raw[refresh_index + 18] >= 512)
					adc2 = 1000;
				else
					adc2 = 0;
			}
			else // analog
				adc2 = output_raw[refresh_index + 18];
		}
		else if(outputs[refresh_index + 18].switch_status == SW_OFF)
			adc2 = 0;
		else if(outputs[refresh_index + 18].switch_status == SW_HAND)
			adc2 = 1000;

//		if(flag_output == ADJUST_AUTO && outputs[refresh_index + 12].switch_status == SW_AUTO)
//		{
//	   adc1 = Auto_Calibration_AO(refresh_index,AO_auto[refresh_index + 12]);
//	   AO_auto[refresh_index + 12] = adc1;
//		}
//		else
			adc1 = conver_ADC(adc1);
		
//		if(flag_output == ADJUST_AUTO && outputs[refresh_index + 18].switch_status == SW_AUTO)
//		{
//	   adc2 = Auto_Calibration_AO(refresh_index + 6,AO_auto[refresh_index + 18]);
//	   AO_auto[refresh_index + 18] = adc2;
//		}
//		else
			adc2 = conver_ADC(adc2);
		


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
		temp1 = (U32_T)255 * (1000 - duty_Cycle1) / 1000;
		temp1 = temp1 * 256 + ccap_low;
	
		duty_Cycle2 = adc2;
		temp2 = (U32_T)255 * (1000 - duty_Cycle2) / 1000;
		temp2 = temp2 * 256 + ccap_low;
		


		PCA_ModuleSetup(PCA_MODULE1,PCA_8BIT_PWM,PCA_CCF_ENB,(U16_T)temp1);	
		PCA_ModuleSetup(PCA_MODULE2,PCA_8BIT_PWM,PCA_CCF_ENB,(U16_T)temp2);	
	}
	else if(Modbus.mini_type == MINI_SMALL)
	{	/* Analog OUTPUT1 - OUPUT4*/
		if(outputs[refresh_index + 6].switch_status == SW_AUTO)
		{
			if(outputs[refresh_index + 6].digital_analog == 0) // digital
			{
				if(output_raw[refresh_index + 6] >= 512)
					adc1 = 1000;
				else
					adc1 = 0;
			}
			else // analog
				adc1 = output_raw[refresh_index + 6];
		}
		else if(outputs[refresh_index + 6].switch_status == SW_OFF)
			adc1 = 0;
		else if(outputs[refresh_index + 6].switch_status == SW_HAND)
			adc1 = 1000;


//		if(flag_output == ADJUST_AUTO && outputs[refresh_index + 6].switch_status == SW_AUTO)
//		{
//	   adc1 = Auto_Calibration_AO(refresh_index,AO_auto[refresh_index + 6]);
//	   AO_auto[refresh_index + 6] = adc1;
//		}
//		else
			adc1 = conver_ADC(adc1);

		if(refresh_index == 0) 
		{
			if(test_adc_flag == 1)	adc1 = test_adc;
			test_adc = adc1;
		}
		
		if(outputs[refresh_index + 6].range == 0)		
			adc1 = 0;
		
		duty_Cycle1 = adc1;
		temp1 = (U32_T)255 * (1000 - duty_Cycle1) / 1000;
		temp1 = temp1 * 256 + ccap_low;		
		

		PCA_ModuleSetup(PCA_MODULE1,PCA_8BIT_PWM,PCA_CCF_ENB,(U16_T)temp1);	
		
			
	}
	else if(Modbus.mini_type == MINI_TINY)
	{	/* Analog OUTPUT1 - OUPUT4*/
		if(outputs[refresh_index + 4].switch_status == SW_AUTO)
		{
			if(outputs[refresh_index + 4].digital_analog == 0) // digital
			{
				if(output_raw[refresh_index + 4] >= 512)
					adc1 = 1000;
				else
					adc1 = 0;
			}
			else // analog
				adc1 = output_raw[refresh_index + 4];
		}
		else if(outputs[refresh_index + 4].switch_status == SW_OFF)
			adc1 = 0;
		else if(outputs[refresh_index + 4].switch_status == SW_HAND)
			adc1 = 1000;


//		if(flag_output == ADJUST_AUTO && outputs[refresh_index + 4].switch_status == SW_AUTO)
//		{
//	   adc1 = Auto_Calibration_AO(refresh_index,AO_auto[refresh_index + 6]);
//	   AO_auto[refresh_index + 6] = adc1;
//		}
//		else
			adc1 = conver_ADC(adc1);


		if(refresh_index == 0) 
		{
			if(test_adc_flag == 1)	adc1 = test_adc;
			test_adc = adc1;
		}

		duty_Cycle1 = adc1;
		temp1 = (U32_T)255 * (1000 - duty_Cycle1) / 1000;
		temp1 = temp1 * 256 + ccap_low;		
		
		
		if(outputs[refresh_index + 4].digital_analog == 1)			
			PCA_ModuleSetup(PCA_MODULE1,PCA_8BIT_PWM,PCA_CCF_ENB,(U16_T)temp1);	
	}
	else if(Modbus.mini_type == MINI_VAV)
	{
		adc1 = output_raw[0];
		adc2 = output_raw[1];
		
		duty_Cycle1 = adc1;
		temp1 = (U32_T)255 * (1000 - duty_Cycle1) / 1000;
		temp1 = temp1 * 256 + ccap_low;

		duty_Cycle2 = adc2;
		temp2 = (U32_T)255 * (1000 - duty_Cycle2) / 1000;
		temp2 = temp2 * 256 + ccap_low;

			
		PCA_ModuleSetup(PCA_MODULE2,PCA_8BIT_PWM,PCA_CCF_ENB,(U16_T)temp1);	
		PCA_ModuleSetup(PCA_MODULE3,PCA_8BIT_PWM,PCA_CCF_ENB,(U16_T)temp2);		
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
	U16_T temp1;
	U16_T far pwm_count[12];
	
	task_test.enable[5] = 1;
	for(i = 0;i < 12;i++)
		pwm_count[i] = 0;
	for (;;)
	{
		vTaskDelay( 50 / portTICK_RATE_MS);		
		task_test.count[5]++;
		if(Modbus.mini_type == MINI_BIG)
		{		
		//	U8_T temp2;
			temp1 = relay_value_auto;
			
			for(i = 0;i < 12;i++)
			{	
				if(outputs[i].switch_status == SW_AUTO )
				{
					if(outputs[i].digital_analog == 0)  // digital
					{
						if(output_raw[i] >= 512)						
								temp1 |= (0x01 << i);
						else
							temp1 &= ~(BIT0 << i); 
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
							temp1 |= (0x01 << i);
						}
						else 
						{
							temp1 &= ~(BIT0 << i); 
						}
					}
				}
				else if (outputs[i].switch_status == SW_OFF )			temp1 &= ~(BIT0 << i); 		
				else if (outputs[i].switch_status == SW_HAND )	temp1 |= (BIT0 << i);
										
			}
			
			if(temp1 != relay_value.word)
			{
				relay_value.word  = temp1;
				push_cmd_to_picstack(SET_RELAY_LOW,relay_value.byte[1]); 
				push_cmd_to_picstack(SET_RELAY_HI,relay_value.byte[0]);
				
			}

			if(flag_output == 1)
				Calucation_PWM_IO(0);	
			else
				Calucation_PWM_IO(AnalogOutput_refresh_index);	

			if(AnalogOutput_refresh_index < 5)	  
				AnalogOutput_refresh_index++;
			else 	
				AnalogOutput_refresh_index = 0;	
					
			
		} 
		else if(Modbus.mini_type == MINI_SMALL)
		{
			for(i = 0;i < 6;i++)
			{	
				if(outputs[i].switch_status == SW_AUTO)
				{
					if(outputs[i].digital_analog == 0)  // digital
					{
						if(output_raw[i] >= 512)						
								temp1 |= (0x01 << i);
						else
							temp1 &= ~(BIT0 << i);
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
							temp1 |= (0x01 << i);
						}
						else 
						{
							temp1 &= ~(BIT0 << i); 
						}
					}					
				}
				else if (outputs[i].switch_status == SW_OFF )			
					temp1 &= ~(BIT0 << i); 		
				else if (outputs[i].switch_status == SW_HAND )	
					temp1 |= (BIT0 << i);
			}

					
			if(temp1 != relay_value.word)
			{
				relay_value.word = temp1;
				push_cmd_to_picstack(SET_RELAY_LOW,relay_value.byte[1]); 
			}
			
			Calucation_PWM_IO(AnalogOutput_refresh_index);	
	
			if(AnalogOutput_refresh_index < 3)	  
				AnalogOutput_refresh_index++;
			else 	
				AnalogOutput_refresh_index = 0;			

		}
		else if(Modbus.mini_type == MINI_TINY)
		{
			for(i = 0;i < 6;i++)
			{	
				// check range of OUT5 & OUT6, they are abled to config to AO or DO
				if( ((i == 4) || (i == 5)) && (outputs[i].digital_analog == 1)) //  analog
				{
					temp1 &= ~(BIT0 << i); 		
				}
				else
				{
					if(outputs[i].switch_status == SW_AUTO)
					{						
						if(outputs[i].digital_analog == 0)  // digital
						{
							if(output_raw[i] >= 512)						
									temp1 |= (0x01 << i);
							else
								temp1 &= ~(BIT0 << i);
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
								temp1 |= (0x01 << i);
							}
							else 
							{
								temp1 &= ~(BIT0 << i); 
							}
						}
					}
					else if (outputs[i].switch_status == SW_OFF )			
						temp1 &= ~(BIT0 << i); 		
					else if (outputs[i].switch_status == SW_HAND )	
						temp1 |= (BIT0 << i);
				}
			}		
			
			if(temp1 != relay_value.word)
			{
				relay_value.word = temp1;
				push_cmd_to_picstack(SET_RELAY_LOW,relay_value.byte[1]); 
			}
			
			Calucation_PWM_IO(AnalogOutput_refresh_index);	
							
			if(AnalogOutput_refresh_index < 3)	  
				AnalogOutput_refresh_index++;
			else 	
				AnalogOutput_refresh_index = 0;	
			
		}
		else if(Modbus.mini_type == MINI_VAV)
		{
			outputs[0].switch_status = SW_AUTO;
			outputs[1].switch_status = SW_AUTO;
			outputs[2].switch_status = SW_AUTO;
			outputs[3].switch_status = SW_AUTO;
			
			if(output_raw[0] > 512)  DO1 = 1;
			else DO1 = 0;
			
			Calucation_PWM_IO(AnalogOutput_refresh_index);
			
			// control AO3 by uart1
			
			SET_VAV(Test[48]);
		}
		
	}
} 

#endif

