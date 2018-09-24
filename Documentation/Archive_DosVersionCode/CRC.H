// ************************* START OF CRC.H *************************
//
//
//
// This header file contains the definitions for the two CRC classes,
// Crc16 and Crc32.
//
//*******************************************************************

#ifndef _CRC_DOT_H
#define _CRC_DOT_H

// The two CRC objects create 16 and 32 bit CRC values using the
// polynomials used by ZMODEM.  The calculations are table driven,
// with the table being initialized by the constructor at runtime.
// The constructor assigns an initial value to the crc, and then
// it is updated on a character by character basis.

class Crc32 {
	 private :
		  static unsigned long table[ 256 ];
		  static int initialized;
		  unsigned long crc;
	 public :
		  Crc32( unsigned long init_value );
		  void init( unsigned long init_value );
		  void update( int c );
		  unsigned long value( void ){ return crc; }
};

inline void Crc32::update( int c )
{
	 crc = table[ ( (int) crc ^ ( c & 0xff ) ) & 0xff ] ^
			 ( ( crc >> 8 ) & 0x00FFFFFFL );
}

inline void Crc32::init( unsigned long init_val )
{
	 crc = init_val;
}

class Crc16 {
	 private :
		  static unsigned short table[ 256 ];
		  static int initialized;
		  unsigned short crc;
	 public :
		  Crc16( unsigned short init_value );
		  void init( unsigned short init_value );
		  void update( int c );
		  unsigned short value( void ){ return crc; }
};

inline void Crc16::update( int c )
{
	 crc = (unsigned short)
				 ( table[ (( crc >> 8 ) & 0xff ) ] ^
					( crc << 8 ) ^ ( c & 0xff ) );
}

inline void Crc16::init( unsigned short init_val )
{
	 crc = init_val;
}

#endif // #ifndef _CRC_DOT_H

// *************************** END OF CRC.H ***************************

