#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#ifdef _WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

/* 
compile with wiringPi, requires SPI activated:
gcc -Wall -o blink blink.cpp -lwiringPi

start with root privileges or it won't work.:
sudo ./blink

*/

enum COMMANDS 
{
  /*  send  */
  C_INITIAL = 0,  

  S_OUTPUT_LED = 0x10,  /* 0x10 + 24 bytes */
  S_INPUT_LED = 0x11,   /* 0x11 + 32 bytes */
  S_HI_SP_FLAG = 0x12,    /* 0x12 + 6 bytes  */ 
  S_COMM_LED  = 0x013,  /* 0x13 + 6 bytes  */
  S_ALL = 0x14,      //  64

  G_SWTICH_STATUS = 0x20, /* 0x20 + 24 bytes */
  G_INPUT_VALUE = 0x21, /* 0x21 + 64 bytes */
  G_TOP_CHIP_INFO = 0x23, /* 0x21 + 12 bytes */
  G_SPEED_COUNTER = 0x30,  // 112
  G_ALL = 0x24,

  C_MINITYPE = 0x80,
  C_ASIX_ISP = 0X81,
  C_END = 255

};


int main (void)
{
  printf ("Raspberry Pi SPI Test\n") ;

  /*wiringPiSetup () ;
  pinMode (LED, OUTPUT) ;*/
  int chan=1;
int speed=1000000;
//int LED = 1;
unsigned char buffer[25];
int result = 0;

if( wiringPiSPISetup (chan, speed)==-1)
{
printf("Could not initialise SPI\n");
}
else
{
	printf("SPI initilized!\n");
	
}

buffer[0]= 0;
buffer[1]= 1;
buffer[2] = 1;
buffer[3] = 1;

 result = wiringPiSPIDataRW(chan, buffer, 25);
 Sleep(10);

buffer[0]= 0x10;
buffer[1]= 1;
buffer[2] = 1;
buffer[3] = 1;

 result = wiringPiSPIDataRW(chan, buffer, 25);
 Sleep(5);


/*
  for (int i= 0;i<54;i++)
  {
  	LED = i;
  	pinMode(LED,OUTPUT);
    digitalWrite (LED, HIGH) ;  // On
    delay (500) ;               // mS
    digitalWrite (LED, LOW) ;   // Off
    delay (500) ;

  }

  */
  return 0 ;
}