#ifndef OUTPUT_H
#define OUTPUT_H

#include "main.h" 


#define		SW_OFF 	 0//0
#define 	SW_HAND	 2//1
#define		SW_AUTO	 1//2




#if MINI 


#define	 MAX_OUTPUT_CHANNELS  	24   /* 12 analog output, 12 digtal output*/

/*#define 	PCA_8BIT_PWM_ON_MODULE_0 		1
#define 	PCA_8BIT_PWM_ON_MODULE_1		1
#define 	PCA_8BIT_PWM_ON_MODULE_2		1
#define 	PCA_8BIT_PWM_ON_MODULE_3		1
#define		PCA_MODULE0			0
#define		PCA_MODULE1			1
#define		PCA_MODULE2			2
#define		PCA_MODULE3			3*/



void cal_slop(void);
U16_T conver_ADC(U16_T adc);
U16_T Auto_Calibration_AO(U8_T channel,U16_T adc);
//U16_T Auto_Calibration_AO(U8_T *index);

void Initial_PWM(void);
//void Refresh_Output(void);
void Refresh_AnalogOutput(void);
void Refresh_DigtalOutput(void);
void vStartOutputTasks( unsigned char uxPriority);

#endif

#endif

