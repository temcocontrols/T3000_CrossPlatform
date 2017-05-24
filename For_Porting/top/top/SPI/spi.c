#include "spi.h"
#include <string.h>
#include "inputs.h"



#define HW_REV 24 

#define SW_REV 31  // ARM board, start from 30, less than 30 is C8051 board

typedef  enum 
{
	/* 	send	*/
	C_INITIAL = 0,	

	S_OUTPUT_LED = 0x10, 	/* 0x10 + 24 bytes */
	S_INPUT_LED = 0x11, 	/* 0x11 + 32 bytes */
	S_HI_SP_FLAG = 0x12,  	/* 0x12 + 6 bytes  */	
	S_COMM_LED	= 0x013,	/* 0x13 + 6 bytes  */
	S_ALL = 0x14,		   //  64

	G_SWTICH_STATUS = 0x20,	/* 0x20 + 24 bytes */
	G_INPUT_VALUE = 0x21,	/* 0x21 + 64 bytes */
	G_TOP_CHIP_INFO	= 0x23, /* 0x21 + 12 bytes */
	G_SPEED_COUNTER = 0x30,	 // 112
	G_ALL = 0x24,

	C_MINITYPE = 0x80,
	C_ASIX_ISP = 0X81,
	C_END = 255

};




u8 command;
u8 state;
u8 array_index;
u32 comm_heartbeat = 0;
u8  flag_Comm = 0;
u16 count_comm;
u8 flag_ISP; // 0 - intial 1 - isp 2 - normal
u8 Mini_Type;
//u8 flag_Start;


u8 high_speed_flag[HI_COMMON_CHANNEL];  // 0 - clear  1 - start  2 - stop
UN_HIGH_COUNT high_speed_counter[HI_COMMON_CHANNEL];

extern u16 test[200];
extern u8 Switch_Status[24];
extern vu16 AD_Value[32];
u8  RX_SPI_BUF[56];
extern u8 range[32];
extern u8 LED_status[67];
extern u16 relay_value;

//**** SPI1 ****************
void SPI1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);	//PORTA和SPI1时钟使能 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;			//PA5-SCK, PA6-MISO, PA7-MOSI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  							//PA5/6/7复用推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);										//初始化GPIOA
//	GPIO_SetBits(GPIOA, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);  				//PA5/6/7上拉

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;			//设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;								//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;							//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;									//串行同步时钟的空闲状态为高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;								//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;									//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;							//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;									//CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure);											//根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  //使用中断进行接收，因此设置NVIC的优先机组，1表示1bit抢占优先级
 
  NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
    
	/* Enable SPI1 RXNE interrupt */    
	SPI_I2S_ITConfig(SPI1,SPI_I2S_IT_RXNE,ENABLE); 

  //Enable SPI1 
  SPI_Cmd(SPI1, ENABLE); //????SPI,?????????????
 
	flag_ISP = 0;
//	flag_Start = 0;

	memset(high_speed_flag,0,HI_COMMON_CHANNEL);
	memset(high_speed_counter,0,sizeof(UN_HIGH_COUNT)*HI_COMMON_CHANNEL);
	
}

//SPI1速度设置函数
//SPI_BaudRatePrescaler_2   2分频   
//SPI_BaudRatePrescaler_8   8分频   
//SPI_BaudRatePrescaler_16  16分频  
//SPI_BaudRatePrescaler_256 256分频 
//void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
//{
//	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));		//限制范围
//	SPI1->CR1 &= 0XFFC7; 
//	SPI1->CR1 |= SPI_BaudRatePrescaler;									//设置SPI1速度  
//	SPI_Cmd(SPI1, ENABLE);												//SPI1设备使能	  
//}

//SPI1 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI1_ReadWriteByte(u8 TxData)
{		
	u16 retry = 0;
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
	{
		retry++;
		if(retry > 0xffff) return 0;
	};
	SPI_I2S_SendData(SPI1, TxData);
	
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
	{
		retry++;
		if(retry > 0xffff) return 0;
	};
	return SPI_I2S_ReceiveData(SPI1);
}


u8 spi_rx[100];
void SPI1_IRQHandler(void) 
{ 
    // 接收数据
		u8 i;

	comm_heartbeat = 0;
	flag_Comm = 1;
	count_comm = 0;
	 test[12]++;
   if(state == 0)
   {	test[13]++;	  	
		  
	    command = SPI_I2S_ReceiveData(SPI1);			
			if(command == 0x55)
			{
				test[14]++;
				flag_ISP = 1;	
			}
			else
			{
				test[15]++;
				test[16] = command;
				flag_ISP = 2;
			}
		 
			if(command == G_TOP_CHIP_INFO)	 	state = 1;	  
			else if(command == C_MINITYPE)		state = 1;
			else if(command == S_ALL)					state = 1;
			else if(command == G_ALL)					state = 1;
			
			array_index = 0;
	 }
	 else if(state == 1)
	 {
#ifdef BB
	 	if(command == G_ALL)
		{
			if(array_index < 112)   // 88 + 24
			{
				if(Mini_Type == BIG || Mini_Type == SMALL)
				{	
					if(array_index < 24)   // switch
					{
						SPI1_ReadWriteByte(Switch_Status[array_index]);						
					}
					else if(array_index < 88)   // input value
					{	
						if((array_index - 24) % 2 == 0)
								SPI1_ReadWriteByte((u8)(AD_Value[(array_index - 24) / 2] >> 10));
						else 
							SPI1_ReadWriteByte((u8)(AD_Value[(array_index - 24) / 2] >> 2));

					}
					else // high_speed_counter
					{
						SPI1_ReadWriteByte(high_speed_counter[(array_index - 88) / 4].byte[(array_index - 88) % 4]);
					}
				}
				else   // if dont get mini type, return 0X55
					SPI1_ReadWriteByte(0x55);
			}
			else if(array_index == 112)
			   	SPI1_ReadWriteByte(0x55);
			else if(array_index == 113)
			   	SPI1_ReadWriteByte(0xaa);
			
			if(array_index >= 113) 
			{	
				array_index = 0; 
				state = 0;
				command = 0;
			}
			else 
			{
				array_index++;
				state = 1;
			}
		}
		if(command == S_ALL)  /* input led status */	
		{
			spi_rx[array_index]	= SPI_I2S_ReceiveData(SPI1);
			if(array_index >= 65) 	
			{
				array_index = 0; 
				state = 0;
				command = 0;  
				if(spi_rx[64] == 0x55 && spi_rx[65] == 0xaa)  // crc ok
				{
					//memcpy(&comm_led[0],&spi_rx[0],2);
					// LED status of COMM					
					if(Mini_Type == BIG)
					{
					for(i = 0;i < 8;i++)
						LED_status[56 + i] = (spi_rx[0] & (0x01 << i)) ? 5 : 0;
					for(i = 0;i < 3;i++)
						LED_status[64 + i] = (spi_rx[1] & (0x01 << i)) ? 5 : 0;
			// 2 + 24 + 32 + 6  = 64
			// 2  - communication led
			// 24 - led of outputs status 
			// 32 - inputs status, types and led
			// -> first 4 bit for inputs type, last 4 bits for input led status,added in new hardware with INPUT moudle
			// 6  - flag of high speed inputs
						
						memcpy(&RX_SPI_BUF[0],&spi_rx[26],32);
						memcpy(&RX_SPI_BUF[32],&spi_rx[2],24);
						for(i = 0;i < 32;i++)
						{
							range[i] = (RX_SPI_BUF[i] >> 4) & 0x0f;
						}
						for(i = 0;i < 56;i++)
						{
							LED_status[i] = RX_SPI_BUF[i] & 0x0f;
						}
						for(i = 0;i < HI_COMMON_CHANNEL;i++)  // HI_COMMON_CHANNEL 6
						{	
							if(spi_rx[58 + i]  != high_speed_flag[i])
							{
								high_speed_flag[i] = spi_rx[58 + i];
								if(high_speed_flag[i] == 1)  // start counter
								{
									if(range[26 + i] == Thermistor) // thermsitor  
									{
										pulse_set(i,RISE);									
									}
									else if(range[26 + i] == V0_5)// 0-5v, 
									{
										pulse_set(i,FALL);
									}
								}
								if(high_speed_flag[i] == 2)	
									high_speed_counter[i].longbyte = 0;
							}
						}
						
					}
					else if(Mini_Type == SMALL)
					{
						LED_status[11] = (spi_rx[0] & (0x01 << 0)) ? 5 : 0;
						LED_status[12] = (spi_rx[0] & (0x01 << 1)) ? 5 : 0;
						
						LED_status[13] = (spi_rx[0] & (0x01 << 2)) ? 5 : 0;
						LED_status[14] = (spi_rx[0] & (0x01 << 3)) ? 5 : 0;
						
						LED_status[32] = (spi_rx[0] & (0x01 << 4)) ? 5 : 0;
						LED_status[33] = (spi_rx[0] & (0x01 << 5)) ? 5 : 0;
						
						LED_status[36] = (spi_rx[0] & (0x01 << 6)) ? 5 : 0;
						LED_status[37] = (spi_rx[0] & (0x01 << 7)) ? 5 : 0;
						
						LED_status[34] = (spi_rx[1] & (0x01 << 0)) ? 5 : 0;
						LED_status[35] = (spi_rx[1] & (0x01 << 1)) ? 5 : 0;						
						
			// 2 + 10 + 16 + 6  = 64
			// 2  - communication led
			// 10 - led of outputs status 
			// 16 - inputs status, types and led
//						-> first 4 bit for inputs type, last 4 bits for input led status,added in new hardware with INPUT moudle
			// 6  - flag of high speed inputs
						memcpy(&RX_SPI_BUF[0],&spi_rx[2],10);
						memcpy(&RX_SPI_BUF[10],&spi_rx[26],16); 
						for(i = 0;i < 16;i++)
							range[i] = ((RX_SPI_BUF[10 + i] >> 4) & 0x0f);
							
						for(i = 0;i < 10;i++)
						{
							LED_status[1 + i] = RX_SPI_BUF[i] & 0x0f;
						}
						for(i = 0;i < 16;i++)
						{
							LED_status[16 + i] = RX_SPI_BUF[10 + i] & 0x0f;
						}
						
						for(i = 0;i < HI_COMMON_CHANNEL;i++)  // HI_COMMON_CHANNEL 6
						{	
							if(spi_rx[58 + i]  != high_speed_flag[i])
							{
								high_speed_flag[i] = spi_rx[58 + i];
								if(high_speed_flag[i] == 1)  // start counter
								{
									if(range[10 + i] == Thermistor) // thermsitor  
									{
										pulse_set(i,RISE);									
									}
									else if(range[10 + i] == V0_5)// 0-5v, 
									{
										pulse_set(i,FALL);
									}
								}
								if(high_speed_flag[i] == 2)	high_speed_counter[i].longbyte = 0;
							}
						}
					}
					
					
				
				} 
			}
			else 
			{
				array_index++;
				state = 1;
			}
		}
		if(command == G_TOP_CHIP_INFO)  /*send input value */	
		{		
			if(Mini_Type == 0)	   // do not get mini type
			{
				if(array_index < 12)
				{
				   	SPI1_ReadWriteByte(0x55);
				}
			}
			else
			{
				if(array_index < 12)
				{		
					if(array_index == 1)
					  SPI1_ReadWriteByte(HW_REV);
					else if(array_index == 3)
					  SPI1_ReadWriteByte(SW_REV);
					else 
						SPI1_ReadWriteByte(0);
				}
			}
			
			if(array_index == 12)
				SPI1_ReadWriteByte(0x55);		
			if(array_index == 13)
				SPI1_ReadWriteByte(0xaa);

			if(array_index >= 13) 
			{	
				array_index = 0; 
				state = 0;
				command = 0;
			}
			else 
			{  				 
				array_index++;
				state = 1;
			}					 
		}		
#endif
		
		
#ifdef TB
	 	if(command == G_ALL)
		{
//			flag_Start = 1;
			if(array_index < 54)   // 8 + 22 + 24
			{
				if(array_index < 8)   // switch
				{
					SPI1_ReadWriteByte(Switch_Status[array_index]);
				}
				else if(array_index < 30)   // input value
				{	 
					if((array_index - 8) % 2 == 0)
						SPI1_ReadWriteByte((u8)(AD_Value[(array_index - 8) / 2] >> 10));
					else 
						SPI1_ReadWriteByte((u8)(AD_Value[(array_index - 8) / 2] >> 2));		
				}
				else if(array_index < 54) // high_speed_counter
				{
					SPI1_ReadWriteByte(high_speed_counter[(array_index - 30) / 4].byte[(array_index - 30) % 4]);
				}
			}
			else if(array_index == 54)
			   	SPI1_ReadWriteByte(0x55);
			else if(array_index == 55)
			   	SPI1_ReadWriteByte(0xaa);
			
			if(array_index >= 55) 
			{		
				test[12]++;
				array_index = 0; 
				state = 0;
				command = 0;
			}
			else 
			{
				array_index++;
				state = 1;
			}
		}
		if(command == S_ALL)  /* input led status */	
		{		
			spi_rx[array_index]	= SPI_I2S_ReceiveData(SPI1);
			if(array_index >= 34) 	
			{
				array_index = 0; 
				state = 0;
				command = 0;  
				if(spi_rx[33] == 0x55 && spi_rx[34] == 0xaa)  // crc ok
				{
					LED_status[8] = spi_rx[21]; //  main 485
					LED_status[9] = spi_rx[22];
					
					LED_status[10] = spi_rx[23]; // ethernet
					LED_status[11] = spi_rx[24];
					
					LED_status[24] = spi_rx[19];  //  sub 485
					LED_status[25] = spi_rx[20];

					for(i = 0;i < 8;i++)  // output status
					{
						LED_status[i] = spi_rx[i] & 0x0f;
					}
					// input led status ,high 4 bits is range
					for(i = 0;i < 11;i++)  
					{
						LED_status[13 + i] = spi_rx[8 + i] & 0x0f;
						range[i] = ((spi_rx[8 + i] >> 4) & 0x0f);	
					}	
					
					for(i = 0;i < HI_COMMON_CHANNEL;i++)  // HI_COMMON_CHANNEL 6
						{	
							
							if(spi_rx[25 + i]  != high_speed_flag[i])
							{
								high_speed_flag[i] = spi_rx[25 + i];
								if(high_speed_flag[i] == 1)  // start counter
								{
									if(range[5 + i] == Thermistor) // thermsitor  
									{
										pulse_set(i,RISE);									
									}
									else if(range[5 + i] == V0_5)// 0-5v, 
									{
										pulse_set(i,FALL);
									}
								}
								if(high_speed_flag[i] == 2)
										high_speed_counter[i].longbyte = 0;
								
								test[20 + i] = high_speed_flag[i];
							}
						}
											
				}
//				memcpy(&high_speed_flag[0],&spi_rx[25],6);
//				for(i = 0;i < 6;i++)  // tiny have 6 hsp
//					if(high_speed_flag[i] == 2)	high_speed_counter[i].longbyte = 0;
				
				

					
				
				
				
				relay_value = (spi_rx[32] * 256 + spi_rx[31]) & 0x3f;
			}
			else 
			{
				array_index++;
				state = 1;
			}
		}		
		if(command == G_TOP_CHIP_INFO)  /*send input value */	
		{		
			if(Mini_Type == 0)	   // do not get mini type
			{
				if(array_index < 12)
				{
				   	SPI1_ReadWriteByte(0x55);
				}
			}
			else
			{
				test[18]++;
				if(array_index < 12)
				{		
					if(array_index == 0)
						SPI1_ReadWriteByte(HW_REV);
					else if(array_index == 1)
					  SPI1_ReadWriteByte(SW_REV);
					else 
						SPI1_ReadWriteByte(0);
				}
			}
			
			if(array_index == 12)
				SPI1_ReadWriteByte(0x55);		
			if(array_index == 13)
				SPI1_ReadWriteByte(0xaa);

			if(array_index >= 13) 
			{	
				array_index = 0; 
				state = 0;
				command = 0;
			}
			else 
			{  				 
				array_index++;
				state = 1;
			}					 
		}		
#endif
		

		if(command == C_MINITYPE)	   // MINI TYPE
		{	
			test[11]++;
//			Mini_Type = SPI_I2S_ReceiveData(SPI1);
//			if(Mini_Type == BIG)
//				MAX_AI_CHANNEL = 32;
//			else
//			{
//				MAX_AI_CHANNEL = 16;
//				GPIO_ResetBits(GPIOC, GPIO_Pin_10 | GPIO_Pin_11);
//			}
//			flag_Start = 1;
			state = 0;
		}
		
	 }  
	
} 

