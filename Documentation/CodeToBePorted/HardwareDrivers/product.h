#ifndef PRODUCT_H
#define PRODUCT_H


#define SW_REV	4105


#define MINI 1
#define	CM5	0

#define MINI_CM5  0
#define MINI_BIG	 1
#define MINI_SMALL  2
#define MINI_TINY	 3
#define MINI_VAV	 4


#define STM_TINY_REV 7


//extern const unsigned int code SW_REV;


#define DEBUG_UART1 0

//#define CHAMBER

#if (DEBUG_UART1)

#include <stdio.h>

#define UART_SUB1 2


void uart_init_send_com(unsigned char port);
extern unsigned char far debug_str[200];
void uart_send_string(unsigned char *p, unsigned int length,unsigned char port);


#endif


#define BIG_MAX_AIS 32
#define BIG_MAX_DOS 12
#define BIG_MAX_AOS 12
#define BIG_MAX_AVS 50
#define BIG_MAX_DIS 0

#define SMALL_MAX_AIS 16
#define SMALL_MAX_DOS 6
#define SMALL_MAX_AOS 4
#define SMALL_MAX_AVS 50
#define SMALL_MAX_DIS 0

#define TINY_MAX_AIS 11
#define TINY_MAX_DOS 6
#define TINY_MAX_AOS 2
#define TINY_MAX_AVS 50
#define TINY_MAX_DIS 0

#define VAV_MAX_AIS 6
#define VAV_MAX_DOS 1
#define VAV_MAX_AOS 2
#define VAV_MAX_AVS 5
#define VAV_MAX_DIS 0

#define CM5_MAX_AIS 26
#define CM5_MAX_DOS 10
#define CM5_MAX_AOS 0
#define CM5_MAX_AVS 5
#define CM5_MAX_DIS 8


#if MINI


#define TIME_SYNC 1

#define MSTP 1

#define USB_HOST   0//1 
#define USB_DEVICE 1
#define WEBPAGE 0
#define DYNDNS	1//0
#define SNTP    1
#define T3_MAP  1
#define STORE_TO_SD  1

//#define ADJUST_AUTO  1
//#define ADJUST_STATIC 0

#define INCLUDE_DNS_CLIENT  0
#define INCLUDE_DHCP_CLIENT 1

#define PING  0


#endif

#if CM5


#define MSTP 0

#define TIME_SYNC 0

#define WEBPAGE 0//1
#define T3_MAP  0
#define USB_HOST 0 
#define USB_DEVICE 0
#define STORE_TO_SD  0

#define INCLUDE_DNS_CLIENT  0
#define INCLUDE_DHCP_CLIENT 1

#define PING  0

//#define NEWPIC	   0
//#define NEW_INPUT  1

#endif

#endif