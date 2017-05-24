#include "main.h"




U16_T far AO_feedback[16];
U8_T get_verion;
					  
extern UN_RELAY relay_value;

I2C_BUF  tmpdata;



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

	if(I2C_ByteWrite(0x60, pic_wirte[i].cmd, pic_wirte[i].value, I2C_STOP_COND) == TRUE)
	{
		pic_wirte[i].flag = WRITE_PIC_OK; // without doing checksum
	}
	else
	{
		I2C_Setup(I2C_ENB|I2C_STANDARD|I2C_MST_IE|I2C_7BIT|I2C_MASTER_MODE, 0xc7, 0x005A);
		return 0;
	}
	return 1;  // write pic cmd
}

void PIC_initial_data(void)
{
	memset(pic_wirte,0,sizeof(STR_PIC_CMD) * STACK_PIC);
}

void PIC_refresh(void)
{
	static U8_T pic_cmd_index = GET_VERSION;
//	relay_value.word = 0xaa;
//	if(check_write_to_pic() == 1) // write pic cmd
//	{
//		
//		return;
//	}
	check_write_to_pic();
	if(pic_cmd_index == GET_VERSION)
	{
		if(I2C_RdmRead(0x60, GET_VERSION, &tmpdata,1,I2C_STOP_COND) == TRUE)
		{
		Modbus.PicVer = tmpdata.I2cData[0];
		Setting_Info.reg.pro_info.frimware_pic = Modbus.PicVer;
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
				if(I2C_RdmRead(0x60, pic_cmd_index, &tmpdata,24,I2C_STOP_COND) == TRUE)
				{
					for(i = 0;i < 11;i++)
					{	
						input_raw[i] = Filter(i,(U16_T)(tmpdata.I2cData[i * 2] << 8) + tmpdata.I2cData[i * 2 + 1]);
					}
				}
			}
		}
#endif
//#if MINI 
//		if(I2C_RdmRead(0x60, pic_cmd_index, &tmpdata,24,I2C_STOP_COND) == TRUE)
//		{
//			for(i = 0;i < 12;i++)
//			{	
//				if((Modbus.mini_type == MINI_TINY) && (i < 11))  //  tiny has 11 inputs
//				{
//					input_raw[i] = Filter(i,(U16_T)(tmpdata.I2cData[i * 2] << 8) + tmpdata.I2cData[i * 2 + 1]);
//				}
//				else if(Modbus.mini_type == MINI_VAV && i < 6)
//				{
//					input_raw[i] = Filter(i,(U16_T)(tmpdata.I2cData[i * 2] << 8) + tmpdata.I2cData[i * 2 + 1]);	
//				}
//				else  // big and samll
//				{
//					if(Modbus.mini_type == MINI_SMALL)
//					{ // SMALL hardware maybe need fix a little bit					
//					 	if(i == 3)	AO_feedback[0] = (U16_T)(tmpdata.I2cData[i * 2] << 8) + tmpdata.I2cData[i * 2 + 1];
//						else if(i <= 2)	AO_feedback[i + 1] = (U16_T)(tmpdata.I2cData[i * 2] << 8) + tmpdata.I2cData[i * 2 + 1];
//						else AO_feedback[i] = 0;
//						
//					}
//					else
//					{
//						AO_feedback[i] = (U16_T)(tmpdata.I2cData[i * 2] << 8) + tmpdata.I2cData[i * 2 + 1];
//					}
//				}
//			}
//		}
//		else
//			I2C_Setup(I2C_ENB|I2C_STANDARD|I2C_MST_IE|I2C_7BIT|I2C_MASTER_MODE, 0xc7, 0x005A);
//#endif
			
#if CM5
		
		if(I2C_RdmRead(0x60, pic_cmd_index, &tmpdata,32,I2C_STOP_COND) == TRUE)
		{	
			for(i = 0;i < 16;i++)
			{
				AO_feedback[i] = (U16_T)(tmpdata.I2cData[i * 2] << 8) + tmpdata.I2cData[i * 2 + 1];
				
				if((inputs[i].digital_analog == 1)) // analog
					input_raw[i] = Filter(i,AO_feedback[i]);
				else
					input_raw[i] = AO_feedback[i];
			}
		}
//		else
//			I2C_Setup(I2C_ENB|I2C_STANDARD|I2C_MST_IE|I2C_7BIT|I2C_MASTER_MODE, i2cpreclk, 0x005A);
		
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


