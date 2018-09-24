// ************************* START OF CRC.CPP *************************
//
//
//
// This file contains the supporting code for the two CRC classes,
// Crc16 and Crc32.
//
//*********************************************************************

#ifdef SERIAL_COMM

#include "portable.h"
#include "crc.h"

unsigned long Crc32::table[ 256 ];
int Crc32::initialized = 0;

Crc32::Crc32( unsigned long init_value )
{
	 if ( !initialized )
	 {
		  int i;
		  int j;
		  unsigned long coeff;

			for ( i = 0; i < 256 ; i++ ) {
				coeff = i;
				for ( j = 0; j < 8; j++ ) {
					 if ( coeff & 1 )
							coeff = ( coeff >> 1 ) ^ 0xEDB88320L;
					 else
							coeff >>= 1;
				}
				table[ i ] = coeff;
			}
		  initialized = 1;
	 }
	 crc = init_value;
}

unsigned short Crc16::table[ 256 ];
int Crc16::initialized = 0;

Crc16::Crc16( unsigned short init_value )
{
	 if ( !initialized ) {
		  int i;
		  int j;
		  int k;
		  int crc;

			for ( i = 0 ; i < 256 ; i++ ) {
				k = i << 8;
				crc = 0;
				for ( j = 0 ; j < 8 ; j++ ) {
					 if ( ( crc ^ k ) & 0x8000 )
							crc = ( crc << 1 ) ^ 0x1021;
					 else
							crc <<= 1;
					 k <<= 1;
				}
				table[ i ] = (unsigned short) crc;
			}
			initialized = 1;
	 }
	 crc = init_value;
}

// *************************** END OF CRC.CPP ***************************

#endif