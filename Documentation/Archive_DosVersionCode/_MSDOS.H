// ********************** START OF _MSDOS.H **********************
//
//
// This file contains header files used to call MS-DOS
// specific support routines.  The only one defined at this
// time is the Bus() function, which determines whether an ISA or
// Microchannel bus is in use on the target machine.


#ifndef __MSDOS_DOT_H
#define __MSDOS_DOT_H
/*
enum BusType { ISA_BUS, MCA_BUS };
BusType Bus( void );*/
void Delay( unsigned long );


#endif  // #ifndef __MSDOS_DOT_H

// ********************** END OF _MSDOS.H **********************

