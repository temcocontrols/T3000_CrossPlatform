 /*================================================================================
 * Module Name : comm.c
 * Purpose     : communicate with the slaver (C8051F023) with SPI bus
 * Author      : Chelsea
 * Date        : 2010/02/03
 * Notes       : 
 * Revision	   : 
 *	rev1.0
 *   
 *================================================================================
 */


#include "e2prom.h"
#include "comm.h"
#include "projdefs.h"
#include "portable.h"
#include "errors.h"
#include "task.h"
#include "list.h"
#include "queue.h"
#include "spi.h"
#include "spiapi.h"
#include "stdio.h"
#include "define.h"
#include "main.h"


xTaskHandle xHandler_SPI;

#define SpiSTACK_SIZE		( ( unsigned portSHORT ) 256 )


U8_T	far flag_send_start_comm = 1;
U8_T	far flag_get_chip_info = 0;
U8_T data count_send_start_comm;
static U8_T far flag_lose_comm = 0;
static U8_T far count_lose_comm = 0;


U16_T far Test[50];
U8_T re_send_led_in = 0;
U8_T re_send_led_out = 0;

bit flagLED_ether_tx = 0;
bit flagLED_ether_rx = 0;
bit flagLED_uart0_rx = 0;
bit flagLED_uart0_tx = 0;
bit flagLED_uart1_rx = 0; 
bit flagLED_uart1_tx = 0;
bit flagLED_uart2_rx = 0;
bit flagLED_uart2_tx = 0;
bit flagLED_usb_rx = 0;
bit flagLED_usb_tx = 0;


U8_T uart0_heartbeat = 0;
U8_T uart1_heartbeat = 0;
U8_T uart2_heartbeat = 0;
U8_T etr_heartbeat = 0;
U8_T usb_heartbeat = 0;	

U8_T flag_led_out_changed = 0;	  
U8_T flag_led_in_changed = 0;
U8_T flag_led_comm_changed = 0;
U8_T flag_high_spd_changed = 0;
U8_T CommLed[2];
U8_T InputLed[32];  // high 4 bits - input type, low 4 bits - brightness
extern U8_T far input_type[32];
extern U8_T far input_type1[32];
U8_T OutputLed[24];
static U8_T OLD_COMM;
U8_T high_spd_flag[HI_COMMON_CHANNEL];
U8_T clear_high_spd[HI_COMMON_CHANNEL];
U16_T count_clear_hsp[HI_COMMON_CHANNEL] = {0,0,0,0,0,0};

U8_T xdata tmpbuf[150];

//U32_T far input_raw_temp[32];
//U8_T far raw_number[32];

U8_T far spi_index;



void Updata_Comm_Led(void);

#if MINI


#define TEMPER_0_C   191*4
#define TEMPER_10_C   167*4
#define TEMPER_20_C   141*4
#define TEMPER_30_C   115*4
#define TEMPER_40_C   92*4


void vStartCommToTopTasks( unsigned char uxPriority)
{
//	U8_T base_hsp;
	U8_T i;
	
	memset(InputLed,0x35,32);
	memset(OutputLed,5,24);		
	
	memset(tmpbuf,0,150);
	memset(CommLed,0,2);
	OLD_COMM = 0;
	flag_send_start_comm = 1;
	flag_get_chip_info = 0;
	count_send_start_comm = 0;
 	flag_lose_comm = 0;
	count_lose_comm = 0;
	re_send_led_in = 0;
	re_send_led_out = 0;

	flagLED_ether_tx = 0;
	flagLED_ether_rx = 0;
	flagLED_uart0_rx = 0;
	flagLED_uart0_tx = 0;
	flagLED_uart1_rx = 0; 
	flagLED_uart1_tx = 0;
	flagLED_uart2_rx = 0;
	flagLED_uart2_tx = 0;
	flagLED_usb_rx = 0;
	flagLED_usb_tx = 0;		
	
	flag_led_out_changed = 0;	  
	flag_led_in_changed = 0;
	flag_led_comm_changed = 0;
	flag_high_spd_changed = 0;

	
//	if(Modbus.mini_type == MINI_BIG)
//	{
//		base_hsp = 26;
//	}
//	else if(Modbus.mini_type == MINI_SMALL)
//	{
//		base_hsp = 10;
//	}
		
	for(i = 0;i < HI_COMMON_CHANNEL;i++)
	{
		if((inputs[i].range == HI_spd_count) || (inputs[i].range == N0_2_32counts))
		{
			high_spd_counter[i] = swap_double(inputs[i].value) / 1000;
			high_spd_counter_tempbuf[i] = 0;
		}
		count_clear_hsp[i] = 0;
		high_spd_en[i] = 0;
		high_spd_flag[i] = 0;
	}

	
//	memset(input_raw_temp,0,32*4);
//	memset(raw_number,0,32);

	if(Modbus.mini_type == MINI_TINY)
		OLD_COMM = 0;	
	else
		Start_Comm_Top();

	sTaskCreate( SPI_Roution, "SPITask", SpiSTACK_SIZE, NULL, uxPriority, &xHandler_SPI );
}

void Check_Pulse_Counter(void)
{
  char loop;
	
	for(loop = 0;loop < HI_COMMON_CHANNEL;loop++)
	{
		if(high_spd_flag[loop] == 1) // start
		{
			if((input_raw_back[loop] != input_raw[loop]) && (input_raw[loop] > 800) 
				&& (input_raw_back[loop] < 200))
			{
				high_spd_counter_tempbuf[loop]++;
			}
			input_raw_back[loop] = input_raw[loop];
		}
		if(high_spd_flag[loop] == 2) // clear
		{
			high_spd_counter_tempbuf[loop] = 0;
		}
	}

	
	for(loop = 0;loop < HI_COMMON_CHANNEL;loop++)
	{ 
	// high_spd_flag 0: disable high speed counter  1:  start count 2: clear counter
		if(clear_high_spd[loop] == 1)
		{
			high_spd_flag[loop] = 2;  // clear
			count_clear_hsp[loop]++;
			if(count_clear_hsp[loop] > 20)
			{
				count_clear_hsp[loop] = 0;
				clear_high_spd[loop] = 0;
			}
		}
		else
		{			
			if((inputs[loop].range == HI_spd_count) || (inputs[loop].range == N0_2_32counts))
			{
				//high_spd_flag[HI_COMMON_CHANNEL - loop - 1] = high_spd_en[HI_COMMON_CHANNEL - loop - 1] + 1;
				high_spd_flag[loop] = 1; // start
			}
			else
			{
				high_spd_flag[loop] = 0; // stop
			}
		}
	}
}


// update led and input_type
void Update_Led(void)
{
	U8_T loop;
	
//	U8_T index,shift;
//	U32_T tempvalue;
	static U16_T pre_in[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	U8_T error_in; // error of input raw value	
	U8_T pre_status;
	U8_T max_in,max_out,max_digout;
	/*    check input led status */	

	
	
	if(Modbus.mini_type == MINI_BIG)
	{
		max_in = 32;
		max_out = 24;
		max_digout = 12;
	}
	else if(Modbus.mini_type == MINI_SMALL)
	{
		max_in = 16;
		max_out = 10;
		max_digout = 6;
	}
	else  if(Modbus.mini_type == MINI_TINY)
	{
		max_in = 11;
		max_out = 8;
		max_digout = 2;	
	}

	

	for(loop = 0;loop < max_in;loop++)
	{	
		pre_status = InputLed[loop];
	   
		if(input_raw[loop] > pre_in[loop])
			error_in = input_raw[loop] - pre_in[loop];
		else
			error_in = pre_in[loop] - input_raw[loop];					
		
		
		if(inputs[loop].range == not_used_input)
			InputLed[loop] = 0;	
		else
		{
			if(inputs[loop].auto_manual == 0)
			{
				if(inputs[loop].digital_analog == 1) // analog 
				{
					if(inputs[loop].range <= A10K_60_200DegF)	  // temperature
					{	//  10k termistor GREYSTONE
						if(input_raw[loop]  > TEMPER_0_C) 	InputLed[loop] = 0;	   // 0 degree
						else  if(input_raw[loop]  > TEMPER_10_C) 	InputLed[loop] = 1;	// 10 degree
						else  if(input_raw[loop]  > TEMPER_20_C) 	InputLed[loop] = 2;	// 20 degree
						else  if(input_raw[loop]  > TEMPER_30_C) 	InputLed[loop] = 3;	// 30 degree
						else  if(input_raw[loop]  > TEMPER_40_C) 	InputLed[loop] = 4;	// 40 degree
						else
							InputLed[loop] = 5;	   // > 50 degree

						//InputLed high 4 bits - input type,
						InputLed[loop] |= 0x30;   // input type is 3
						
					}						
					else 	  // voltage or current
					{
						if(input_raw[loop]  < 50) 	InputLed[loop] = 0;
						else  if(input_raw[loop]  < 200) 	InputLed[loop] = 1;
						else  if(input_raw[loop]  < 400) 	InputLed[loop] = 2;
						else  if(input_raw[loop]  < 600) 	InputLed[loop] = 3;
						else  if(input_raw[loop]  < 800) 	InputLed[loop] = 4;
						else
							InputLed[loop] = 5;
	

					}
				}
				else if(inputs[loop].digital_analog == 0) // digtial
				{
					if( inputs[loop].range >= ON_OFF  && inputs[loop].range <= HIGH_LOW )  // control 0=OFF 1=ON
					{
						if(input_raw[loop]  >= 512)InputLed[loop] = 0;
						else
							InputLed[loop] = 5;
					}
					else
					{
						if(input_raw[loop]  < 512)InputLed[loop] = 0;
						else
							InputLed[loop] = 5;				
					}
				}
			}
			else // manual
			{
				if(inputs[loop].digital_analog == 0) // digtial
				{
					if( inputs[loop].range >= ON_OFF  && inputs[loop].range <= HIGH_LOW )  // control 0=OFF 1=ON
					{
						if(inputs[loop].control == 1) InputLed[loop] = 0;	
						else
							InputLed[loop] = 5;	
					}
					else
					{
						if(inputs[loop].control == 1) InputLed[loop] = 5;	
						else
							InputLed[loop] = 0;				
					}
					if( inputs[loop].range >= custom_digital1 && inputs[loop].range <= custom_digital8 )
					{
						if(inputs[loop].control == 1) InputLed[loop] = 5;	
						else
							InputLed[loop] = 0;	
					}
						
				}
				else   // analog
				{
					U32_T tempvalue;
					tempvalue = swap_double(inputs[loop].value) / 1000;
					if(inputs[loop].range <= A10K_60_200DegF)	  // temperature
					{	//  10k termistor GREYSTONE
						if(tempvalue <= 0) 	InputLed[loop] = 0;	   // 0 degree
						else  if(tempvalue < 10) 	InputLed[loop] = 1;	// 10 degree
						else  if(tempvalue < 20) 	InputLed[loop] = 2;	// 20 degree
						else  if(tempvalue < 30) 	InputLed[loop] = 3;	// 30 degree
						else  if(tempvalue < 40) 	InputLed[loop] = 4;	// 40 degree
						else
							InputLed[loop] = 5;	   // > 50 degree						
					}		
					else 	  // voltage or current
					{						
						//InputLed high 4 bits - input type,
						if(inputs[loop].range == V0_5)	
						{						
							if(tempvalue <= 0) 	InputLed[loop] = 0;	   // 0 degree
							else  if(tempvalue <= 1) 	InputLed[loop] = 1;	// 10 degree
							else  if(tempvalue <= 2) 	InputLed[loop] = 2;	// 20 degree
							else  if(tempvalue <= 3) 	InputLed[loop] = 3;	// 30 degree
							else  if(tempvalue <= 4) 	InputLed[loop] = 4;	// 40 degree
							else
								InputLed[loop] = 5;	   // > 50 degree	
						}
						if(inputs[loop].range == I0_20ma)	
						{
							if(tempvalue <= 4) 	InputLed[loop] = 0;	   // 0 degree
							else  if(tempvalue <= 7) 	InputLed[loop] = 1;	// 10 degree
							else  if(tempvalue <= 10) 	InputLed[loop] = 2;	// 20 degree
							else  if(tempvalue <= 14) 	InputLed[loop] = 3;	// 30 degree
							else  if(tempvalue <= 18) 	InputLed[loop] = 4;	// 40 degree
							else
								InputLed[loop] = 5;	   // > 50 degree	
						}
						if(inputs[loop].range == V0_10_IN)	
						{
							if(tempvalue <= 0) 	InputLed[loop] = 0;	   // 0 degree
							else  if(tempvalue <= 2) 	InputLed[loop] = 1;	// 10 degree
							else  if(tempvalue <= 4) 	InputLed[loop] = 2;	// 20 degree
							else  if(tempvalue <= 6) 	InputLed[loop] = 3;	// 30 degree
							else  if(tempvalue <= 8) 	InputLed[loop] = 4;	// 40 degree
							else
								InputLed[loop] = 5;	   // > 50 degree	
						}

					}
				}
			}
		}	
		if(pre_status != InputLed[loop] && error_in > 50)
		{  //  error is larger than 20, led of input is changed
			flag_led_in_changed = 1;   
			re_send_led_in = 0;
		}
		pre_in[loop] = input_raw[loop];

		//Test[42] = Setting_Info.reg.pro_info.firmware_c8051;
		//if(Setting_Info.reg.pro_info.firmware_c8051 >= 14)
		{
			InputLed[loop] &= 0x0f;		
			if(input_type[loop] >= 1)
				InputLed[loop] |= ((input_type[loop] - 1) << 4);			
			else
				InputLed[loop] |= (input_type[loop] << 4);
		}
	} 
	
	
	/*    check output led status */	
	for(loop = 0;loop < max_out;loop++)
	{	
//		OutputLed[loop] = loop / 4;
		pre_status = OutputLed[loop];
		
		if(outputs[loop].switch_status == SW_AUTO)
		{
			if(outputs[loop].range == 0)
			{
				OutputLed[loop] = 0;
			}
			else
			{
				if(loop < max_digout)	  // digital
				{
					if(output_raw[loop] < 512 ) 	OutputLed[loop] = 0;
					else
						OutputLed[loop] = 5;
				}
				else
				{
					if(output_raw[loop] >= 0 && output_raw[loop] < 50 )	   			
						OutputLed[loop] = 0;
					else if(output_raw[loop] >= 50 && output_raw[loop] < 200 )		
						OutputLed[loop] = 1;
					else if(output_raw[loop] >= 200 && output_raw[loop] < 400 )		
						OutputLed[loop] = 2;
					else if(output_raw[loop] >= 400 && output_raw[loop] < 600 )		
						OutputLed[loop] = 3;
					else if(output_raw[loop] >= 600 && output_raw[loop] < 800 )		
						OutputLed[loop] = 4;
					else if(output_raw[loop] >= 800 && output_raw[loop] < 1023 )		
						OutputLed[loop] = 5;
				}
			}
		}
		else if(outputs[loop].switch_status == SW_OFF)			 OutputLed[loop] = 0;
		else if(outputs[loop].switch_status == SW_HAND)		 OutputLed[loop] = 5;

		if(pre_status != OutputLed[loop])
		{
			flag_led_out_changed = 1;  
			re_send_led_out = 0;
		}
	}

	/*    check communication led status */

	Updata_Comm_Led();
}


void Updata_Comm_Led(void)
{
	U8_T temp1 = 0;
	U8_T temp2 = 0;
	U8_T pre_status1 = CommLed[0];
	U8_T pre_status2 = CommLed[1];
//	U8_T i;

	

	if(Modbus.mini_type == MINI_BIG)
	{
		if(Modbus.hardRev >= 21)  // swap UART0 and UART1 
		{
		if(flagLED_uart2_rx)	{ temp1 |= 0x02;	 	flagLED_uart2_rx = 0;}
		if(flagLED_uart2_tx)	{	temp1 |= 0x01;		flagLED_uart2_tx = 0;}	
		if(flagLED_uart0_rx)	{	temp1 |= 0x08;		flagLED_uart0_rx = 0;}
		if(flagLED_uart0_tx)	{	temp1 |= 0x04;		flagLED_uart0_tx = 0;}	
		}
		else
		{
		if(flagLED_uart0_rx)	{ temp1 |= 0x02;	 	flagLED_uart0_rx = 0;}
		if(flagLED_uart0_tx)	{	temp1 |= 0x01;		flagLED_uart0_tx = 0;}	
		if(flagLED_uart2_rx)	{	temp1 |= 0x08;		flagLED_uart2_rx = 0;}
		if(flagLED_uart2_tx)	{	temp1 |= 0x04;		flagLED_uart2_tx = 0;}
		}
		
		if(flagLED_ether_rx)	{ temp1 |= 0x20;		flagLED_ether_rx = 0;}
		if(flagLED_ether_tx)	{	temp1 |= 0x10;		flagLED_ether_tx = 0;}
		
		
		
		if(Modbus.com_config[1] != MASTER_MODBUS)
		{
			if(flagLED_usb_rx)		{	temp1 |= 0x40;	 	flagLED_usb_rx = 0;}
			if(flagLED_usb_tx)		{	temp1 |= 0x80;		flagLED_usb_tx = 0;} 
		}
		
		if(Modbus.com_config[1] == MASTER_MODBUS)
		{
			if(flagLED_uart1_rx)	{	temp1 |= 0x40;	 flagLED_uart1_rx = 0;}
			if(flagLED_uart1_tx)	{	temp1 |= 0x80;	flagLED_uart1_tx = 0;}
		}
		else
		{
			if(flagLED_uart1_rx)	{	temp2 |= 0x01;	 	flagLED_uart1_rx = 0;}
			if(flagLED_uart1_tx)	{	temp2 |= 0x02;		flagLED_uart1_tx = 0;} 
		}
	}
	else  if(Modbus.mini_type == MINI_SMALL)
	{
		if(flagLED_uart2_rx)	{ temp1 |= 0x02;	 	flagLED_uart2_rx = 0;}
		if(flagLED_uart2_tx)	{	temp1 |= 0x01;		flagLED_uart2_tx = 0;}	
		if(flagLED_ether_rx)	{	temp1 |= 0x08;		flagLED_ether_rx = 0;}
		if(flagLED_ether_tx)	{	temp1 |= 0x04;		flagLED_ether_tx = 0;}
		if(flagLED_uart0_rx)	{ temp1 |= 0x20;		flagLED_uart0_rx = 0;}
		if(flagLED_uart0_tx)	{	temp1 |= 0x10;		flagLED_uart0_tx = 0;}
		if(flagLED_usb_rx)		{	temp1 |= 0x40;	 	flagLED_usb_rx = 0;}
		if(flagLED_usb_tx)		{	temp1 |= 0x80;		flagLED_usb_tx = 0;} 
		
		if(flagLED_uart1_tx)	{	temp2 |= 0x01;		flagLED_uart1_tx = 0;} 
		if(flagLED_uart1_rx)	{	temp2 |= 0x02;	 	flagLED_uart1_rx = 0;}

	}
	else  if(Modbus.mini_type == MINI_TINY)
	{
		// TBD: 
		if(flagLED_uart2_rx)	{ temp1 |= 0x10;	 	flagLED_uart2_rx = 0;}
		if(flagLED_uart2_tx)	{	temp1 |= 0x20;		flagLED_uart2_tx = 0;}	
		if(flagLED_ether_rx)	{	temp1 |= 0x04;		flagLED_ether_rx = 0;}
		if(flagLED_ether_tx)	{	temp1 |= 0x08;		flagLED_ether_tx = 0;}
		if(flagLED_uart0_rx)	{ temp1 |= 0x01;		flagLED_uart0_rx = 0;}
		if(flagLED_uart0_tx)	{	temp1 |= 0x02;		flagLED_uart0_tx = 0;}
	}

	CommLed[0] = temp1;
	if(pre_status1 != CommLed[0])
		flag_led_comm_changed = 1;

	CommLed[1] = temp2;
	if(pre_status2 != CommLed[1])
		flag_led_comm_changed = 1;

}

void SPI_Send(U8_T cmd,U8_T* buf,U8_T len)
{	 
	U8_T i;
#if STORE_TO_SD
	if(cSemaphoreTake(sem_SPI, 0) == pdFALSE)
		return ;
#endif	
  SPI_ByteWrite(cmd);
	
	for(i = 0; i < len; i++) 
	{		
		SPI_ByteWrite(buf[i]);
	}
	
	// add crc
	SPI_ByteWrite(0x55);
	SPI_ByteWrite(0xaa);
#if STORE_TO_SD
	cSemaphoreGive(sem_SPI);
#endif
}



void SPI_Get(U8_T cmd,U8_T len)
{
	U8_T i;
	U8_T rec_len = 0;
	bit error = 1;
	U8_T count_error = 0;
	U8_T crc[2];

	SPI_ByteWrite(cmd);		
	SPI_ByteWrite(0xff);


	rec_len = len + 2;
	
	for(i = 0; i < rec_len; i++) 
	{	
		SPI_ByteWrite(0xff);		
		SPI_GetData(&tmpbuf[i]);
		if(tmpbuf[i] != 0xff)  
			error = 0;
	}	

//	SPI1_CS_SET();
	
	crc[0] = tmpbuf[i - 1];
	crc[1] = tmpbuf[i - 2];



	// CRC 0xaa55
	if((crc[0]!= 0xaa) ||(crc[1] != 0x55))	 {error = 1; }


	if((tmpbuf[0] == 0x55) && (tmpbuf[1] == 0x55) && (tmpbuf[2] == 0x55) && (tmpbuf[3] == 0x55) && (tmpbuf[4] == 0x55))
	{	// top board dont not get mini type
		Start_Comm_Top();
		error = 1;
	}
	
	if(!error) // no error
	{
		Test[1]++;
		flag_lose_comm = 0;
		count_lose_comm = 0;
		count_error = 0;
		if(cmd == G_TOP_CHIP_INFO)
		{
			if(Modbus.mini_type == MINI_TINY)
			{
				for(i = 0;i < 4;i++)
				{
					chip_info[i] = tmpbuf[i];
					Setting_Info.reg.pro_info.firmware_c8051 = chip_info[1];  
					Setting_Info.reg.pro_info.frimware_sm5964 = chip_info[2];
				}	
				flag_get_chip_info = 1;
				OLD_COMM = 0;
				
			}
			else
			{
				for(i = 0;i < len / 2;i++)
				{
					chip_info[i] = (U16_T)(tmpbuf[i * 2 + 1] + tmpbuf[i * 2] * 256);
					Setting_Info.reg.pro_info.firmware_c8051 = chip_info[1];
					Setting_Info.reg.pro_info.frimware_sm5964 = chip_info[2];
					flag_get_chip_info = 1;

					if(Setting_Info.reg.pro_info.firmware_c8051 >= 9)  // new comm
					{					
						OLD_COMM = 0;
					}
					else
					{	
						OLD_COMM = 1; 
					}
				}
			}
		}
		else if(cmd == G_ALL)
		{
			if(Modbus.mini_type == MINI_TINY)  // tiny
			{
				// ...
			}
			else  // big and small panel
			{
				for(i = 0;i < 24;i++)
				{
					outputs[i].switch_status = tmpbuf[i];					
				}
				for(i = 0;i < 64 / 2;i++)	  // 88 == 24+64
				{	
					input_raw[i] = (U16_T)(tmpbuf[i * 2 + 1 + 24] + tmpbuf[i * 2 + 24] * 256);
					//input_raw[i] = filter_input_raw(i,(U16_T)(tmpbuf[i * 2 + 1] + tmpbuf[i * 2] * 256));
				}
				
				if(Setting_Info.reg.pro_info.firmware_c8051 >= 30) // ARM board
				{
					for(i = 0;i < 24 / 4;i++)
					{		
						char start;
						if(Modbus.mini_type == MINI_BIG)	start = 26;
						else if(Modbus.mini_type == MINI_SMALL) start = 10;		
						//else if(Modbus.mini_type == MINI_TINY) start = 5;								
						high_spd_counter_tempbuf[start + i] = swap_double( tmpbuf[i * 4 + 91] | (U16_T)tmpbuf[i * 4 + 90] << 8 | (U32_T)tmpbuf[i * 4 + 89] << 16 |  (U32_T)tmpbuf[i * 4 + 88] << 24);
					
					}
				}
			}
		}
	}
	else
	{
		Test[0]++;
		flag_lose_comm = 1;
		count_lose_comm++;
	}

}

#if MINI
void Check_whether_lose_comm(void)
{	
	Test[2] = count_lose_comm;
	if(flag_lose_comm)	
	{
		if(count_lose_comm > 20)
		{	
			if(((Modbus.mini_type == MINI_BIG) && (Modbus.hardRev <= 22))
				|| ((Modbus.mini_type == MINI_SMALL) && (Modbus.hardRev <= 6)))
			{
				RESET_8051 = 0;  // RESET c8051f023 
				DELAY_Ms(100);
				RESET_8051 = 1; 	
				flag_send_start_comm = 1;
				count_send_start_comm = 0;
			}
			else if(Modbus.mini_type == MINI_TINY)
			{
				if(Modbus.hardRev >= STM_TINY_REV)
				{
					RESET_8051 = 0;  // RESET stm32
					DELAY_Ms(100);
					RESET_8051 = 1; 	
				}
				else
				{  // old version, top board is sm5r16
				
				RESET_8051 = 1;  // RESET sm5r16 
				DELAY_Ms(100);
				RESET_8051 = 0;
				}
			}
			count_lose_comm = 0;
			flag_lose_comm = 0;

		}
	}
}
#endif	


void SPI_Roution(void)
{
	portTickType xDelayPeriod = ( portTickType ) 25 / portTICK_RATE_MS;
	U8_T far send_all[100];
	task_test.enable[8] = 1;
	spi_index = 0;
	for (;;)
	{
		vTaskDelay(xDelayPeriod);
		task_test.count[8]++;
		Check_Pulse_Counter();
		Update_Led();
		Check_whether_lose_comm();


	  if(Modbus.mini_type == MINI_TINY)
		{
			
			//...
		}
		else
		{		
			vTaskDelay(75 / portTICK_RATE_MS);
			
			
			if(flag_send_start_comm)
			{
				if(count_send_start_comm < 30)
				{	
					count_send_start_comm++; 	
				}
				else
				{	
					
					Start_Comm_Top();
					flag_send_start_comm = 0; 
				}
			}
			else
			{	
				
					
					if(flag_get_chip_info == 0)
					{	
						SPI_Get(G_TOP_CHIP_INFO,12);
					}
					else 
					{	
						if(spi_index == 0)
						{
							memcpy(send_all,CommLed,2);
							memcpy(&send_all[2],OutputLed,24);
							memcpy(&send_all[26],InputLed,32);
							if(Setting_Info.reg.pro_info.firmware_c8051 >= 10)  // C8051, new protocal
							{	
								if(Modbus.mini_type == MINI_BIG)
									memcpy(&send_all[58],&high_spd_flag[26],6);	 // HI_COMMON_CHANNEL 6
								else if(Modbus.mini_type == MINI_SMALL)
									memcpy(&send_all[58],&high_spd_flag[10],6);	 // HI_COMMON_CHANNEL 6
								SPI_Send(S_ALL,send_all,64);								
							}
							
							spi_index = 1;
							if(flag_led_comm_changed)
								flag_led_comm_changed = 0;
						}
						else 
						{	
							
							
								SPI_Get(G_ALL,112);  // 88 + 24
							
							spi_index = 0;
						}
					}
	
				
	
			}
		// for test
		}
	}
}




void Start_Comm_Top(void)
{
	SPI_ByteWrite(C_MINITYPE);
	SPI_ByteWrite(Modbus.mini_type);
} 




#endif


