 /*================================================================================
 * Module Name : comm.c
 * Purpose     : communicate with the slave CPU (STM32) with SPI bus
 * Author      : Chelsea
 * Date        : 2010/02/03
 * Notes       : 
 * Revision	   : 
 *	rev1.0
 *   
 *================================================================================
 */
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <string.h>

//#include "e2prom.h"
#include "comm.h"
//#include "define.h"

#include "main.h"
char buf[10];
char buf2[10];
struct spi_ioc_transfer xfer[2];
int fd;
xTaskHandle xHandler_SPI;

#define SpiSTACK_SIZE		( ( unsigned portSHORT ) 256 )

#define MAX_LOSE_TOP 30

/**************************************************************************/
//3 commands between BOT and TOP
//G_TOP_CHIP_INFO  -- return information of TOP. Hardware rev and firmware rev and so on. It is not important.
//G_ALL -- return switch status (24 * 1 bytes)and input value( 32 * 2 bytes) and high speed counter( 6 * 4bytes)
//S_ALL -- send LED status to TOP. Communication LED( 2 bytes) + output led( 24 * 1byte) + input led( 32 * 1) + flag of high speed counter( 6 * 1)
/***************************************************************************/


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
U8_T far InputLed[32];  // high 4 bits - input type, low 4 bits - brightness
extern U8_T far input_type[32];
extern U8_T far input_type1[32];
U8_T OutputLed[24];
static U8_T OLD_COMM;
U8_T far high_spd_flag[HI_COMMON_CHANNEL];
U8_T far clear_high_spd[HI_COMMON_CHANNEL];
U16_T far count_clear_hsp[HI_COMMON_CHANNEL] = {0,0,0,0,0,0};

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

int spi_init(char filename[40]) {
	static int file;
	__u8 mode = 0, lsb, bits = 8;
	__u32 speed = 500000;

	if ((file = open(filename, O_RDWR)) < 0) {
		perror("Failed to open the bus.");
		exit(1);
	}

	if (ioctl(file, SPI_IOC_WR_MODE, &mode) < 0) {
		perror("can't set spi mode");
		return 1;
	}

	if (ioctl(file, SPI_IOC_WR_BITS_PER_WORD, &bits) < 0) {
		perror("SPI bits_per_word");
		return 1;
	}

	if (ioctl(file, SPI_IOC_WR_MAX_SPEED_HZ, &speed)<0) {
		perror("can't set max speed hz");
		return 1;
	}

	printf("%s: spi mode %d, %d bits %sper word, %d Hz max\n", filename,
			mode, bits, lsb ? "(lsb first) " : "", speed);

	return file;
}

/*void SPI_ByteWrite(char data)	commented as this idea will not work.
{
	int status;
	status = ioctl(fd, SPI_IOC_MESSAGE(1), data);
	if (status < 0) {
		perror("SPI_IOC_MESSAGE");
		return;
	}
}*/	
 
void main(void)		//ronak - replaced the below function with the main function. this will be used for spi initialisation and other function.
//void vStartCommToTopTasks( unsigned char uxPriority)
{
//	U8_T base_hsp;
	U8_T i;

	//int fd;
	char *check, *send_buf;
	int i;
	
	fd = spi_init("/dev/spidev0.1");
	//	SPI1_Init(0);
	
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

	memset(high_spd_counter,0,4*HI_COMMON_CHANNEL);
	memset(high_spd_counter_tempbuf,0,4*HI_COMMON_CHANNEL);
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

//U32_T far back_pulse_count[HI_COMMON_CHANNEL];
//void store_pulse_count(void)
//{
//	U8_T loop;
//	for(loop = 0;loop < HI_COMMON_CHANNEL;loop++)
//	{
//		if(back_pulse_count[loop] != high_spd_counter[loop] + high_spd_counter_tempbuf[loop])
//		{			
//			back_pulse_count[loop] = high_spd_counter[loop] + high_spd_counter_tempbuf[loop];
//			// store it to E2porm
//			inputs[loop].value = swap_double(back_pulse_count[loop] * 1000);
//		}
//	}
//}



void Check_Pulse_Counter(void)
{
  char loop;
	
	for(loop = 0;loop < HI_COMMON_CHANNEL;loop++)
	{
		if(high_spd_flag[loop] == 1) // start
		{
			if((input_raw_back[loop] != input_raw[loop]) && (input_raw[loop] > 800) 
				&& (input_raw_back[loop] < 200))  // from low to high
			{
				high_spd_counter_tempbuf[loop]++;
			}

		}
		if(high_spd_flag[loop] == 2) // clear
		{
			high_spd_counter_tempbuf[loop] = 0;
//			inputs[loop].value = 0;
		}
		input_raw_back[loop] = input_raw[loop];
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

	
	
	if((Modbus.mini_type == MINI_BIG) || (Modbus.mini_type == MINI_BIG_ARM))
	{
		max_in = 32;
		max_out = 24;
		max_digout = 12;
	}
	else if((Modbus.mini_type == MINI_SMALL) || (Modbus.mini_type == MINI_SMALL_ARM))
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
	else  if((Modbus.mini_type == MINI_NEW_TINY) || (Modbus.mini_type == MINI_TINY_ARM))
	{
		max_in = 8;
		max_out = 14;
		max_digout = 8;	
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
	//					InputLed[loop] |= 0x30;   // input type is 3
						
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
						if(input_raw[loop]  >= 512)
							InputLed[loop] = 0;
						else
							InputLed[loop] = 5;
					}
					else
					{
						if(input_raw[loop]  < 512)
							InputLed[loop] = 0;
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
						if(inputs[loop].range == V0_5 || inputs[loop].range == P0_100_0_5V)	
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
	
	temp1 = 0;
	temp2 = 0;
	pre_status1 = CommLed[0];
	pre_status2 = CommLed[1];
	if((Modbus.mini_type == MINI_BIG) || (Modbus.mini_type == MINI_BIG_ARM))
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
		
		
		
//		if(Modbus.com_config[1] != MODBUS_MASTER)
//		{
//			if(flagLED_usb_rx)		{	temp1 |= 0x40;	 	flagLED_usb_rx = 0;}
//			if(flagLED_usb_tx)		{	temp1 |= 0x80;		flagLED_usb_tx = 0;} 
//		}
		
		if(Modbus.com_config[1] == MODBUS_MASTER)
		{
			if(flagLED_uart1_rx)	{	temp1 |= 0x80;	 flagLED_uart1_rx = 0;}
			if(flagLED_uart1_tx)	{	temp1 |= 0x40;	 flagLED_uart1_tx = 0;}
		}
		else
		{
			if(flagLED_uart1_rx)	{	temp2 |= 0x02;	 	flagLED_uart1_rx = 0;}
			if(flagLED_uart1_tx)	{	temp2 |= 0x01;		flagLED_uart1_tx = 0;} 
		}
	}
	else  if((Modbus.mini_type == MINI_SMALL) || (Modbus.mini_type == MINI_SMALL_ARM))
	{				
		if(flagLED_uart2_rx)	{ temp1 |= 0x02;	 	flagLED_uart2_rx = 0; }
		if(flagLED_uart2_tx)	{	temp1 |= 0x01;		flagLED_uart2_tx = 0; }	

		if(flagLED_ether_rx)	{	temp1 |= 0x08;		flagLED_ether_rx = 0; }			
		if(flagLED_ether_tx)	{	temp1 |= 0x04;		flagLED_ether_tx = 0;}		
		
		if(flagLED_uart0_rx)	{ temp1 |= 0x20;		flagLED_uart0_rx = 0;}
		if(flagLED_uart0_tx)	{	temp1 |= 0x10;		flagLED_uart0_tx = 0;}
//		if(flagLED_usb_rx)		{	temp1 |= 0x40;	 	flagLED_usb_rx = 0;}
//		if(flagLED_usb_tx)		{	temp1 |= 0x80;		flagLED_usb_tx = 0;} 
		
//		if(flagLED_uart1_tx)	{	temp2 |= 0x01;		flagLED_uart1_tx = 0;} 
//		if(flagLED_uart1_rx)	{	temp2 |= 0x02;	 	flagLED_uart1_rx = 0;}

		if(flagLED_uart1_tx)	{	temp1 |= 0x40;		flagLED_uart1_tx = 0;} 
		if(flagLED_uart1_rx)	{	temp1 |= 0x80;	 	flagLED_uart1_rx = 0;}
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
	else  if((Modbus.mini_type == MINI_NEW_TINY) || (Modbus.mini_type == MINI_TINY_ARM))
	{
		// TBD: 
//		if(flagLED_uart2_rx)	{ temp1 |= 0x10;	 	flagLED_uart2_rx = 0;}
//		if(flagLED_uart2_tx)	{	temp1 |= 0x20;		flagLED_uart2_tx = 0;}	
//		if(flagLED_ether_rx)	{	temp1 |= 0x04;		flagLED_ether_rx = 0;}
//		if(flagLED_ether_tx)	{	temp1 |= 0x08;		flagLED_ether_tx = 0;}
//		if(flagLED_uart0_rx)	{ temp1 |= 0x01;		flagLED_uart0_rx = 0;}
//		if(flagLED_uart0_tx)	{	temp1 |= 0x02;		flagLED_uart0_tx = 0;}
	}
	CommLed[0] = temp1;
	if(pre_status1 != CommLed[0])
		flag_led_comm_changed = 1;

	CommLed[1] = temp2;
	if(pre_status2 != CommLed[1])
		flag_led_comm_changed = 1;

}


void SPI_Send(int cmd, char *data, int data_length)
{
	int status;
	data_length += 2;
	
	printf("At line number %d\n",__LINE__);

	char * buf = malloc(data_length * sizeof(char));

	printf("At line number %d\n",__LINE__);

	memset(buf, 0, data_length + 3);

	buf[0] = cmd;
	memcpy(&buf[1], data, data_length - 2);
//	strncpy(buf + 1, data, data_length);
	buf[data_length - 1] = 0x55;
	buf[data_length - 2] = 0xAA;
	xfer[0].tx_buf = (unsigned long) buf;
	xfer[0].len = data_length; /* Length of  command to write*/
	status = ioctl(file, SPI_IOC_MESSAGE(1), xfer);
	if (status < 0) {
		perror("SPI_IOC_MESSAGE");
		return;
	}
}

/*void SPI_Send(U8_T cmd,U8_T* buf,U8_T len)
{	 
	U8_T i;


	if((Modbus.mini_type == MINI_SMALL) || (Modbus.mini_type == MINI_SMALL_ARM))
	{
		if(cSemaphoreTake(sem_SPI, 5) == pdFALSE)
			return ;
	}
  SPI_ByteWrite(cmd);
	
	for(i = 0; i < len; i++) 
	{		
		SPI_ByteWrite(buf[i]);
	}
	
	// add crc
	SPI_ByteWrite(0x55);
	SPI_ByteWrite(0xaa);


	if((Modbus.mini_type == MINI_SMALL) || (Modbus.mini_type == MINI_SMALL_ARM))
		cSemaphoreGive(sem_SPI);
} */

char * spi_read(int cmd, int nbytes)
{
	bit error = 1;
	U8_T count_error = 0;
	U8_T crc[2];
	int status;
	int i;

	char *buf2 = malloc(nbytes * sizeof(char));

	memset(buf, 0, sizeof buf);
	memset(buf2, 0, sizeof buf2);

	buf[0] = cmd;
	buf[1] = 0xff;
	xfer[0].tx_buf = (unsigned long) buf;
	xfer[0].len = 2; /* Length of  command to write*/
	xfer[1].rx_buf = (unsigned long) buf2;
	xfer[1].len = nbytes; /* Length of Data to read */
	status = ioctl(file, SPI_IOC_MESSAGE(2), xfer);
	if (status < 0){				//does it work if device is not connected. or return with 0xff?
		perror("SPI_IOC_MESSAGE");
		return NULL;
	}

	for (i = 0; i < nbytes; i++){
		//printf("check[%d] = %d\n", i, buf2[i]); commented as in final code we dont want print.
		
		if(tmpbuf[i] != 0xff)  
			error = 0;
	}
	
	crc[0] = tmpbuf[i - 1];
	crc[1] = tmpbuf[i - 2];


	if((Modbus.mini_type == MINI_TINY) && (Modbus.hardRev < STM_TINY_REV))
	{
		if((crc[0]!= 0x55) ||(crc[1] != 0xd5))	 {error = 1; } 	
	}
	else
	{
		if((crc[0]!= 0xaa) ||(crc[1] != 0x55))	 {error = 1; }
	}



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
		if(cmd == G_SWTICH_STATUS)
		{				
		  for(i = 0;i < len;i++)
			{// ONLY FOR OLD BOARD
				outputs[i].switch_status = SW_AUTO;//tmpbuf[i];
			}
		}
		else if(cmd == G_INPUT_VALUE)
		{
		  for(i = 0;i < len / 2;i++)
			{				   
				input_raw[i] = (U16_T)(tmpbuf[i * 2 + 1] + tmpbuf[i * 2] * 256); //Filter(i,(U16_T)(tmpbuf[i * 2 + 1] + tmpbuf[i * 2] * 256));
				// add filter 
				//input_raw[i] = filter_input_raw(i,(U16_T)(tmpbuf[i * 2 + 1] + tmpbuf[i * 2] * 256));
			}
		} 
		else if(cmd == G_TOP_CHIP_INFO)
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
				for(i = 0;i < 8;i++)
				{
					outputs[i].switch_status = tmpbuf[i];
				}
			
				if(Setting_Info.reg.pro_info.firmware_c8051 >= 30) // ARM board
				{
					for(i = 0;i < 22 / 2;i++)
					{		
						//input_raw[i] = Filter(i,(U16_T)(tmpbuf[i * 2 + 1 + 8] + tmpbuf[i * 2 + 8] * 256));
						input_raw[i] = (U16_T)(tmpbuf[i * 2 + 1 + 8] + tmpbuf[i * 2 + 8] * 256);
					}
					for(i = 0;i < 24 / 4;i++)
					{		
						char start;
//						if(Modbus.mini_type == MINI_BIG)	start = 26;
//						else if(Modbus.mini_type == MINI_SMALL) start = 10;		
//						else 
//							if(Modbus.mini_type == MINI_TINY) 
						start = 5;		
						high_spd_counter_tempbuf[start + i] = swap_double( tmpbuf[i * 4 + 33] | (U16_T)tmpbuf[i * 4 + 32] << 8 | (U32_T)tmpbuf[i * 4 + 31] << 16 |  (U32_T)tmpbuf[i * 4 + 30] << 24);
						
					}	
				
				}
			}
			else  // big and small panel
			{
				for(i = 0;i < 24;i++)
				{
					outputs[i].switch_status = tmpbuf[i];		
				}
				if((Modbus.mini_type == MINI_BIG) || (Modbus.mini_type == MINI_BIG_ARM))
					for(i = 0;i < 64 / 2;i++)	  // 88 == 24+64
					{						
						input_raw[i] = (U16_T)(tmpbuf[i * 2 + 1 + 24] + tmpbuf[i * 2 + 24] * 256);		
					}
				if((Modbus.mini_type == MINI_SMALL) || (Modbus.mini_type == MINI_SMALL_ARM))
					for(i = 0;i < 32 / 2;i++)	  // 88 == 24+64
					{						
						input_raw[i] = (U16_T)(tmpbuf[i * 2 + 1 + 24] + tmpbuf[i * 2 + 24] * 256);		
					}
				if(Setting_Info.reg.pro_info.firmware_c8051 >= 30) // ARM board
				{
					for(i = 0;i < 24 / 4;i++)
					{		
						char start;
						if((Modbus.mini_type == MINI_BIG) || (Modbus.mini_type == MINI_BIG_ARM))	start = 26;
						else if((Modbus.mini_type == MINI_SMALL) || (Modbus.mini_type == MINI_SMALL_ARM)) start = 10;		
						//else if(Modbus.mini_type == MINI_TINY) start = 5;	
						//if(inputs[start + i].range == HI_spd_count)
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



	//if((Modbus.mini_type == MINI_SMALL) || (Modbus.mini_type == MINI_SMALL_ARM))
	//	cSemaphoreGive(sem_SPI);

}

/*void SPI_Get(U8_T cmd,U8_T len)
{
	U8_T i;
	U8_T rec_len = 0;
	bit error = 1;
	U8_T count_error = 0;
	U8_T crc[2];



	if((Modbus.mini_type == MINI_SMALL) || (Modbus.mini_type == MINI_SMALL_ARM))
	{
		if(cSemaphoreTake(sem_SPI, 5) == pdFALSE)
			return ;
	}
	SPI_ByteWrite(cmd);		
	
	SPI_ByteWrite(0xff);
	
	if((Modbus.mini_type == MINI_TINY) && (Modbus.hardRev < STM_TINY_REV))
	{
		rec_len = len + 3;
	}
	else
		rec_len = len + 2;
	
	for(i = 0; i < rec_len; i++) 
	{	

		tmpbuf[i] = SPI1_ReadWriteByte(0xff);
		
		if(tmpbuf[i] != 0xff)  
			error = 0;
	}	

//	SPI1_CS_SET();
	
	crc[0] = tmpbuf[i - 1];
	crc[1] = tmpbuf[i - 2];


	if((Modbus.mini_type == MINI_TINY) && (Modbus.hardRev < STM_TINY_REV))
	{
		if((crc[0]!= 0x55) ||(crc[1] != 0xd5))	 {error = 1; } 	
	}
	else
	{
		if((crc[0]!= 0xaa) ||(crc[1] != 0x55))	 {error = 1; }
	}



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
		if(cmd == G_SWTICH_STATUS)
		{				
		  for(i = 0;i < len;i++)
			{// ONLY FOR OLD BOARD
				outputs[i].switch_status = SW_AUTO;//tmpbuf[i];
			}
		}
		else if(cmd == G_INPUT_VALUE)
		{
		  for(i = 0;i < len / 2;i++)
			{				   
				input_raw[i] = (U16_T)(tmpbuf[i * 2 + 1] + tmpbuf[i * 2] * 256); //Filter(i,(U16_T)(tmpbuf[i * 2 + 1] + tmpbuf[i * 2] * 256));
				// add filter 
				//input_raw[i] = filter_input_raw(i,(U16_T)(tmpbuf[i * 2 + 1] + tmpbuf[i * 2] * 256));
			}
		} 
		else if(cmd == G_TOP_CHIP_INFO)
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
				for(i = 0;i < 8;i++)
				{
					outputs[i].switch_status = tmpbuf[i];
				}
			
				if(Setting_Info.reg.pro_info.firmware_c8051 >= 30) // ARM board
				{
					for(i = 0;i < 22 / 2;i++)
					{		
						//input_raw[i] = Filter(i,(U16_T)(tmpbuf[i * 2 + 1 + 8] + tmpbuf[i * 2 + 8] * 256));
						input_raw[i] = (U16_T)(tmpbuf[i * 2 + 1 + 8] + tmpbuf[i * 2 + 8] * 256);
					}
					for(i = 0;i < 24 / 4;i++)
					{		
						char start;
//						if(Modbus.mini_type == MINI_BIG)	start = 26;
//						else if(Modbus.mini_type == MINI_SMALL) start = 10;		
//						else 
//							if(Modbus.mini_type == MINI_TINY) 
						start = 5;		
						high_spd_counter_tempbuf[start + i] = swap_double( tmpbuf[i * 4 + 33] | (U16_T)tmpbuf[i * 4 + 32] << 8 | (U32_T)tmpbuf[i * 4 + 31] << 16 |  (U32_T)tmpbuf[i * 4 + 30] << 24);
						
					}	
				
				}
			}
			else  // big and small panel
			{
				for(i = 0;i < 24;i++)
				{
					outputs[i].switch_status = tmpbuf[i];		
				}
				if((Modbus.mini_type == MINI_BIG) || (Modbus.mini_type == MINI_BIG_ARM))
					for(i = 0;i < 64 / 2;i++)	  // 88 == 24+64
					{						
						input_raw[i] = (U16_T)(tmpbuf[i * 2 + 1 + 24] + tmpbuf[i * 2 + 24] * 256);		
					}
				if((Modbus.mini_type == MINI_SMALL) || (Modbus.mini_type == MINI_SMALL_ARM))
					for(i = 0;i < 32 / 2;i++)	  // 88 == 24+64
					{						
						input_raw[i] = (U16_T)(tmpbuf[i * 2 + 1 + 24] + tmpbuf[i * 2 + 24] * 256);		
					}
				if(Setting_Info.reg.pro_info.firmware_c8051 >= 30) // ARM board
				{
					for(i = 0;i < 24 / 4;i++)
					{		
						char start;
						if((Modbus.mini_type == MINI_BIG) || (Modbus.mini_type == MINI_BIG_ARM))	start = 26;
						else if((Modbus.mini_type == MINI_SMALL) || (Modbus.mini_type == MINI_SMALL_ARM)) start = 10;		
						//else if(Modbus.mini_type == MINI_TINY) start = 5;	
						//if(inputs[start + i].range == HI_spd_count)
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



	if((Modbus.mini_type == MINI_SMALL) || (Modbus.mini_type == MINI_SMALL_ARM))
		cSemaphoreGive(sem_SPI);


}
*/
#if MINI

void Check_whether_lose_comm(void)
{	

	Test[2] = count_lose_comm;
	if(flag_lose_comm)	
	{		
		if(count_lose_comm > MAX_LOSE_TOP)
		{	
	// generate a alarm
			generate_common_alarm(ALARM_LOST_TOP);
			
			if((Modbus.mini_type == MINI_BIG) && (Modbus.hardRev <= 22))
			{
				RESET_8051 = 0;  // RESET c8051f023 
				DELAY_Ms(100);
				RESET_8051 = 1; 	
				flag_send_start_comm = 1;
				count_send_start_comm = 0;
			}
			if((Modbus.mini_type == MINI_SMALL) && (Modbus.hardRev <= 6))
			{
#if ASIX
				RESET_8051 = 0;  // RESET c8051f023 
				DELAY_Ms(100);
				RESET_8051 = 1; 	
				flag_send_start_comm = 1;
				count_send_start_comm = 0;
#endif
			}
			else if(Modbus.mini_type == MINI_TINY)
			{
				if(Modbus.hardRev >= STM_TINY_REV)
				{					
					RESET_8051 = 0;  // RESET stm32
					DELAY_Ms(100);
					RESET_8051 = 1; 
					Test[3]++;
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
	char i;
//	portTickType xDelayPeriod = ( portTickType ) 25 / portTICK_RATE_MS;
	U8_T far send_all[100];
	task_test.enable[8] = 1;
	spi_index = 0;
	
	for (;;)
	{
		task_test.count[8]++;
		Check_Pulse_Counter();
		Update_Led();
		
#if 1//ASIX
		Check_whether_lose_comm();
#endif
	
	  if(Modbus.mini_type == MINI_TINY)
		{			
		/*	if(Setting_Info.reg.pro_info.firmware_c8051 >= 30) 		commented as delay function not needed. if needed then need to implement seperately.
				vTaskDelay(75 / portTICK_RATE_MS);
			else
				vTaskDelay(175 / portTICK_RATE_MS);
		*/	
			
			if(flag_get_chip_info == 0) // get information first
			{	
				SPI_Get(G_TOP_CHIP_INFO,12);
			}
			else
			{
				if(spi_index == 0)
				{	
					spi_index = 1;
					//memcpy(send_all,CommLed,2);	
					memcpy(&send_all[0],OutputLed,8);
					
					if(Setting_Info.reg.pro_info.firmware_c8051 >= 30)  // ARM board
					{
						memcpy(&send_all[8],InputLed,11);	
					}
					else
					{
						send_all[8] = InputLed[0] & 0x0f;
						send_all[9] = InputLed[1] & 0x0f;
						send_all[10] = InputLed[2] & 0x0f;
						send_all[11] = InputLed[3] & 0x0f;
						send_all[12] = InputLed[4] & 0x0f;
						send_all[13] = InputLed[5] & 0x0f;
						send_all[14] = InputLed[6] & 0x0f;
						send_all[15] = InputLed[7] & 0x0f;
						send_all[16] = InputLed[8] & 0x0f;
						send_all[17] = InputLed[9] & 0x0f;
						send_all[18] = InputLed[10] & 0x0f;
					}
					
					send_all[23] = (CommLed[0] & 0x04) ? 5 : 0;
					send_all[24] = (CommLed[0] & 0x08) ? 5 : 0;
					send_all[19] = (CommLed[0] & 0x01) ? 5 : 0;
					send_all[20] = (CommLed[0] & 0x02) ? 5 : 0;
					send_all[21] = (CommLed[0] & 0x10) ? 5 : 0;
					send_all[22] = (CommLed[0] & 0x20) ? 5 : 0;
					
					
					if(Setting_Info.reg.pro_info.firmware_c8051 >= 30) // ARM board
					{// new hardware have high speed counter
						char i;
						
						memcpy(&send_all[25],&high_spd_flag[5],6);  // tiny have 6 HSP ,start pos is 5
#if ASIX							
						send_all[31] = relay_value.byte[1];   // new tiny control relays by ARM chip
						
						send_all[32] = relay_value.byte[0];
#endif
						SPI_Send(S_ALL,send_all,33);
					}
					else  // old version, do not have high speed counter					
						SPI_Send(S_ALL,send_all,25);
				}			
				else if(spi_index == 1)
				{	
					if(Setting_Info.reg.pro_info.firmware_c8051 >= 33) // ARM board  8 switch_status + 11 (* 2) input_value + 6 (* 4) highspeedcouner + 4 (*2) AO feedback
					{
						SPI_Get(G_ALL,62); 
					}
					else if(Setting_Info.reg.pro_info.firmware_c8051 >= 30) // ARM board  8 switch_status + 11 (* 2) input_value + 6 (* 4) highspeedcouner
					{
						SPI_Get(G_ALL,54);
					}
					else // old top board   8 switch_status  + 8 feedback
					{
						SPI_Get(G_ALL,16);
					}
					spi_index = 0;
				}
			}			
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
				
				if(OLD_COMM == 1)
				{
					if(flag_get_chip_info == 0)
					{
						SPI_Get(G_TOP_CHIP_INFO,12);
					}
					else if(flag_led_out_changed)	
					{
						if(re_send_led_out < 10)
						{	
							SPI_Send(S_OUTPUT_LED,OutputLed,24);
							re_send_led_out++;
						}
						else
						{
							re_send_led_out = 0;
							flag_led_out_changed = 0;
						}
					}
					else if(flag_led_in_changed)	
					{	
						if(re_send_led_in < 10)
						{	
							SPI_Send(S_INPUT_LED,InputLed,32);
							re_send_led_in++;
						}
						else
						{
							re_send_led_in = 0;
							flag_led_in_changed = 0;
						}
					}
					else 
					{	
						if(spi_index == 0 || spi_index == 2 || spi_index == 4 || spi_index == 6)	 
							//SPI_Get(G_TOP_CHIP_INFO,12);//
							SPI_Send(S_COMM_LED,CommLed,2);
						else if(spi_index == 1)	 SPI_Send(S_OUTPUT_LED,OutputLed,24);
						else if(spi_index == 3)	 {
							
							SPI_Send(S_INPUT_LED,InputLed,32);
						}
						else 
						if(spi_index == 5)	 
						{			
							SPI_Get(G_SWTICH_STATUS,24);
						}
						else if(spi_index == 7)	 
						{	
							SPI_Get(G_INPUT_VALUE,64);				
						}
			//			else if((index == 6) && high_spd_status != 0)	 
			//				;//SPI_Get(G_SPEED_COUNTER,high_spd_counter,24);
			//	
						if(spi_index < 7)	
							spi_index++;
						else 
							spi_index = 0; 
					
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

							if(Setting_Info.reg.pro_info.firmware_c8051 <= 13)  // old top board
							{
								char i;
								for(i = 0;i < 32;i++)
									InputLed[i] &= 0x0f;
							}

							memcpy(&send_all[26],InputLed,32);

							
							if(Setting_Info.reg.pro_info.firmware_c8051 >= 10)  // C8051, new protocal
							{	
								if((Modbus.mini_type == MINI_BIG) || (Modbus.mini_type == MINI_BIG_ARM))
									memcpy(&send_all[58],&high_spd_flag[26],6);	 // HI_COMMON_CHANNEL 6
								else if((Modbus.mini_type == MINI_SMALL) || (Modbus.mini_type == MINI_SMALL_ARM))
									memcpy(&send_all[58],&high_spd_flag[10],6);	 // HI_COMMON_CHANNEL 6
								SPI_Send(S_ALL,send_all,64);	
							}
							else if(Setting_Info.reg.pro_info.firmware_c8051 == 9)  // C8051, old protocal
							{
								SPI_Send(S_ALL,send_all,58);
							}
							
							spi_index = 1;
							if(flag_led_comm_changed)
								flag_led_comm_changed = 0;
						}
						else 
						{	
							
							if(Setting_Info.reg.pro_info.firmware_c8051 >= 10)
							{	

								SPI_Get(G_ALL,112);  // 88 + 24
								
							}
							else if(Setting_Info.reg.pro_info.firmware_c8051 == 9)
							{
								SPI_Get(G_ALL,88);						
							}
							spi_index = 0;
						}
					}
	
				}
	
			}

		}
	}
}




void Start_Comm_Top(void)
{
	SPI_ByteWrite(C_MINITYPE);
	SPI_ByteWrite(Modbus.mini_type);
} 




#endif


