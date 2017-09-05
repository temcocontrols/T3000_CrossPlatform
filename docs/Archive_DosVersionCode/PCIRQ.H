// ********************** START OF PCIRQ.H **********************
//
//
//
// This header file has the prototypes and definitions used with the
// IRQ manager routines.  The three public functions have their
// prototypes here.  All the code for the IRQ manager is found in
// PCIRQ.CPP.

#ifndef _PCIRQ_DOT_H
#define _PCIRQ_DOT_H

#include "rs232.h"

RS232Error ConnectToIrq( irq_name irq,
								 void *isr_data_block,
								 void ( *isr_routine )( void *isr_data_block ) );
int DisconnectFromIRQ( irq_name irq );

#endif // #ifndef _PCIRQ_DOT_H

// ************************ END OF PCIRQ.H ***********************

