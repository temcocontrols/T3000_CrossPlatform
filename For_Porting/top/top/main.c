#include <string.h>
#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "spi.h"
#include "dma.h"
#include "timerx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "modbus.h"
#include "inputs.h"
#include "switch.h"
#include "output.h"

static void vLED0Task( void *pvParameters );
void vCOMMTask(void *pvParameters );
void vINPUTSTask( void *pvParameters );

#define MAX_DEAD_TIMER 120

extern u32 	comm_heartbeat;
extern u8 flag_ISP;
extern u8 LED_status[67];
//extern u8 flag_Start;
extern u8  flag_Comm;
extern u16 count_comm;
extern u8 Mini_Type;

extern u16 test[200];

u8 flag_led;

static void debug_config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
}


int main(void)
{
//	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x8000);
	debug_config();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
#ifdef TB
	Mini_Type = TINY;
	Output_Init();
#endif
	
	
#ifdef BB
	Mini_Type = PANEL_TYPE;
#endif
	
 	delay_init(72);
	LED_Init();	
	Switch_Init();
	uart1_init(19200);
	SPI1_Init();
	TIM6_Int_Init(5, 7199); // 500 us	
//	GPIO_Write(GPIOE,0x55);
//	Mini_Type = SMALL;	
	xTaskCreate( vLED0Task, ( signed portCHAR * ) "LED0", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 3, NULL );
 	xTaskCreate( vCOMMTask, ( signed portCHAR * ) "COMM", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL );
	xTaskCreate( vINPUTSTask, ( signed portCHAR * ) "INPUT", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 4, NULL );
	/* Start the scheduler. */
	vTaskStartScheduler();
}

void vLED0Task( void *pvParameters )
{
	static u16 line = 4;
	static u8 group = 0;
	Count_LED_Buffer();
	if(Mini_Type == SMALL)	
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_10 | GPIO_Pin_11);
	}
	if(Mini_Type == TINY)	
	{
		GPIO_ResetBits(GPIOE, GPIO_Pin_10 | GPIO_Pin_11);		
	}

	for( ;; )
	{
		if(group < 2) group ++;
		else 
			group = 0;
#ifdef TB
		Refresh_Relay();
#endif	
		
		Check_Switch_Status(group);
		delay_ms(50) ;
		Count_LED_Buffer();
		flag_led = 1;
		line++;
		line %= 5;
		test[1]++;
		
		if(comm_heartbeat > MAX_DEAD_TIMER * 2000)	  
		{		
#ifdef BB
			GPIO_ResetBits(GPIOA, GPIO_Pin_15);   // RESET ASIX
			delay_ms(10) ;
			GPIO_SetBits(GPIOA, GPIO_Pin_15);   // RESET ASIX
#endif
			
#ifdef TB
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);   // RESET ASIX
			delay_ms(10) ;
			GPIO_SetBits(GPIOB, GPIO_Pin_0);   // RESET ASIX
#endif
			comm_heartbeat = 0;
			
		}
	}
}

void vCOMMTask(void *pvParameters )
{	
	modbus_init();
	for( ;; )
	{
		if (dealwithTag)
		{  
		 dealwithTag--;
		  if(dealwithTag == 1)//&& !Serial_Master )	
			dealwithData();
		}
		if(serial_receive_timeout_count>0)  
		{
				serial_receive_timeout_count -- ; 
				if(serial_receive_timeout_count == 0)
				{
					serial_restart();
				}
		}
		delay_ms(5) ;
	}
	
}


void vINPUTSTask( void *pvParameters )
{
	u8 i ;
	for(i=0; i < MAX_AI_CHANNEL; i++)
	{
		AD_Value[i] = 9 ;	
	}
	
	inputs_init();
	for( ;; )
	{
		inpust_scan();
		delay_ms(20);
	}	
}

