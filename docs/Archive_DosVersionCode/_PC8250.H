// ********************** START OF _PC8250.H **********************
//
//
//
// This header file provides prototypes for functions that are shared
// between the PC8250 class and the PC8250 ISR routines.  This header
// file is only for use by the PC8250 class, not the end user of the
// class.
//

#ifndef __PC8250_DOT_H
#define __PC8250_DOT_H

void jump_start( struct isr_data_block *data );
void isr_8250( struct isr_data_block * data );

#endif // #ifndef __PC8250_DOT_H

// ************************ END OF _PC8250.H ***********************

