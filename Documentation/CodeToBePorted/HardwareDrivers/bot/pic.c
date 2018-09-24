#include "main.h"




U16_T far AO_feedback[16];
U32_T far sum_feedback[16];

U8_T pic_cmd_index;// = GET_VERSION;
U8_T count_read_pic_Rev = 0;

U8_T get_verion;

#define MAX_READ_FEEDBACK 1
					  
extern UN_RELAY relay_value;




#define STACK_PIC 50

typedef struct
{
	U8_T cmd;
	U8_T value;
	U8_T flag;
	U8_T retry;
}STR_PIC_CMD;

typedef enum { WRITE_PIC_OK = 0,WAIT_PIC_FOR_WRITE};

STR_PIC_CMD far pic_wirte[STACK_PIC];




#define I2C_STOP_COND 0 // no used
U8_T tmpdata[50];

U8_T I2C_RdmRead(U8_T cmd,U8_T *ptPktTemp,U16_T readLen)
{
	u8 temp = 0;		
	u8 i;
	IIC_Start();  

	IIC_Send_Byte(0xc0);	//发送器件地址0Xc0,写数据 	   
	if(IIC_Wait_Ack())
	{
//		IIC_Stop(); 
//		return 0;
	}
	
  IIC_Send_Byte(cmd);		//发送低地址
	IIC_Wait_Ack1();

	IIC_Start();  	 	   
	IIC_Send_Byte(0xc1);				//进入接收模式	
	if(IIC_Wait_Ack())
	{		
//		IIC_Stop(); 
//		return 0;
	}
	
	
	for(i = 0;i < readLen - 1;i++)
	{
	  *ptPktTemp++ = IIC_Read_Byte(1);
	}
	
	*ptPktTemp++ = IIC_Read_Byte(0);
			 
	IIC_Stop();							//产生一个停止条件	    
	return TRUE;
}

U8_T I2C_ByteWrite(U16_T cmd, U16_T byteData)
{
	IIC_Start(); 
	IIC_Send_Byte(0xc0);	//发送器件地址0Xc0,写数据 	 


	IIC_Wait_Ack();	   
	IIC_Send_Byte(cmd);		//发送低地址
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(byteData);			//发送字节							   
	IIC_Wait_Ack();	  		    	   
	IIC_Stop();							//产生一个停止条件 

	delay_ms(3);
		
	return TRUE;
}


void push_cmd_to_picstack(uint8 cmd, uint8 value)
{
	U8_T i;
	for(i = 0;i < STACK_PIC;i++)
	{
		if(pic_wirte[i].flag == WRITE_PIC_OK) 	break;
	}
	if(i == STACK_PIC)		
	{  // stack full
	// tbd
		return;	
	}
	else
	{	
		pic_wirte[i].cmd = cmd;
		pic_wirte[i].value = value;
		pic_wirte[i].flag = WAIT_PIC_FOR_WRITE;
		pic_wirte[i].retry = 0;
	}
}




U8_T check_write_to_pic(void)
{	
	U8_T i;

	for(i = 0;i < STACK_PIC;i++)
	{
		if(pic_wirte[i].flag == WAIT_PIC_FOR_WRITE) //	get current index, 1 -- WAIT_PIC_FOR_WRITE, 0 -- WRITE_PIC_OK
		{
			if(pic_wirte[i].retry < 5)
			{
				pic_wirte[i].retry++;
				break;
			}
			else
			{  	// retry 10 time, give up
				pic_wirte[i].flag = WRITE_PIC_OK; 
			}
		}
	}
	if(i == STACK_PIC)		// no WAIT_PIC_FOR_WRITE
	{	
		return 0;	 // no cmd in pic stack
	}

	if(I2C_ByteWrite(pic_wirte[i].cmd, pic_wirte[i].value) == TRUE)
	{
		pic_wirte[i].flag = WRITE_PIC_OK; // without doing checksum
	}

	return 1;  // write pic cmd
}

void PIC_initial_data(void)
{
	pic_cmd_index = GET_VERSION;
	count_read_pic_Rev = 0;
	memset(pic_wirte,0,sizeof(STR_PIC_CMD) * STACK_PIC);
	get_verion = 0;
}

void PIC_refresh(void)
{
	if((Modbus.mini_type == MINI_NEW_TINY) || (Modbus.mini_type == MINI_TINY_ARM))
		return;
	if((Modbus.mini_type == MINI_TINY) && (Modbus.hardRev >= STM_TINY_REV)) 
	{  // TINY with ARM TOP, do not have PIC
		flag_output = 0;
		return;
	}


	// 
	if((Modbus.mini_type == MINI_TINY) && (Modbus.hardRev >= STM_TINY_REV)) 
	{  // NEW ARM'S LB, do not have PIC
		return;
	}


	
	
	if(count_read_pic_Rev >= 10)
	{
		if(count_read_pic_Rev == 10)
		{
			count_read_pic_Rev = 100;
			generate_common_alarm(ALARM_LOST_PIC);
		}
		flag_output = 0;
		
		return;

	}

	check_write_to_pic();

	if(pic_cmd_index == GET_VERSION)
	{		
		count_read_pic_Rev++;


		if(I2C_RdmRead(GET_VERSION, tmpdata,1) == TRUE)
		{		
			
		Modbus.PicVer = tmpdata[0];		

		//Setting_Info.reg.pro_info.frimware_pic = Modbus.PicVer;
			if(Modbus.PicVer > 0)  // old code have trouble, maybe get 130
			{
				get_verion = 1;
			}
		// if get right pic ver, dont need to send this cmd again
		}
		else
		{
			//I2C_Setup(I2C_ENB|I2C_STANDARD|I2C_MST_IE|I2C_7BIT|I2C_MASTER_MODE, 0xc7, 0x005A);
		}
	}
	else if(pic_cmd_index == READ_AO_FEEDBACK)//	if(pic_cmd_index <= READ_AO12_FEEDBACK_H)	 // read cmd
	{
		U8_T i;
#if MINI
		if(Setting_Info.reg.pro_info.firmware_c8051 < 30) // old top board
		{
			if(Modbus.mini_type == MINI_TINY)  //  tiny has 11 inputs
			{	
				
				if(I2C_RdmRead(pic_cmd_index, tmpdata,24) == TRUE)
				{
					for(i = 0;i < 11;i++)
					{	
						input_raw[i] = Filter(i,(U16_T)(tmpdata[i * 2] << 8) + tmpdata[i * 2 + 1]);
					}
				}
			
			}
		}
#endif

			
	}

 
 	if(get_verion != 1)
	{
		pic_cmd_index = GET_VERSION;
	}
	else  
	{ 
		pic_cmd_index = READ_AO_FEEDBACK;
	}
}


void Read_feedback(void)
{
	U8_T i,j;
	for(j = 0;j < MAX_READ_FEEDBACK;)		

	if(I2C_RdmRead(READ_AO_FEEDBACK, tmpdata,24) == TRUE)
	{
		
		j++;
		for(i = 0;i < 12;i++)
		{
			if((Modbus.mini_type == MINI_TINY) && (i < 11))  //  tiny has 11 inputs
			{
				input_raw[i] = Filter(i,(U16_T)(tmpdata[i * 2] << 8) + tmpdata[i * 2 + 1]);
			}
			else if(Modbus.mini_type == MINI_VAV && i < 6)
			{
				input_raw[i] = Filter(i,(U16_T)(tmpdata[i * 2] << 8) + tmpdata[i * 2 + 1]);
				
			}
			else  // big and samll
			{		

				if((Modbus.mini_type == MINI_SMALL) || (Modbus.mini_type == MINI_SMALL_ARM))
				{ // SMALL hardware maybe need fix a little bit	
					if(i == 3)	sum_feedback[0] += (U16_T)(tmpdata[i * 2] << 8) + tmpdata[i * 2 + 1];
					else if(i <= 2)	sum_feedback[i + 1] += (U16_T)(tmpdata[i * 2] << 8) + tmpdata[i * 2 + 1];
					else AO_feedback[i] = 0;					
				}
				else
				{		
					sum_feedback[i] += (U16_T)(tmpdata[i * 2] << 8) + tmpdata[i * 2 + 1];			
					
				}
				
				if(j == MAX_READ_FEEDBACK)
				{		
						
					AO_feedback[i] = (float)sum_feedback[i] * 1000 / 1017 / j;		
					sum_feedback[i] = 0;
				}
				
			}
		}
		
	}	

}

