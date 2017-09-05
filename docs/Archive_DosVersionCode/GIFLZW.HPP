//--------------------------------------------------------//
//                                                        //
//   File:    GIFLZW.HPP                                  //
//                                                        //
//   Desc:    Encoder and Decoder classes for GIF/LZW     //
//                                                        //
//--------------------------------------------------------//

#ifndef _GIFLZW_HPP_
#define _GIFLZW_HPP_

#include "stdio.h"
#include "string.h"

#include "codec.hpp"

//..................A Code File I/O Class

// This class encapsulates the I/O requirements of GIF/LZW
// compression.  These are (1) blocked reads and writes of
// up to 255 bytes at a time, and (2) reading and writing
// values with a variable number of bits.

class CodeFile
{
	public:
		int   cond;      // condition code;
		int   bytecnt;   // number of bytes in buffer

	protected:
//      FILE *filep;     // open stream pointer
		int   capacity;  // size of I/O buffer
		char *buffer;    // I/O buffer
		int   codesize;  // bits per code
		int   curbyte;   // current byte in buffer
		int   curbit;    // current bit of current byte
		int   byteind;   //

	public:
      CodeFile( int nbits, char *buf, int length_buf );
     ~CodeFile( );
      void clearbuf( void );
      int flushbuf( void );
      int loadbuf( void );
      int putcode( int code );
      int getcode( void );
      void dumpcode( int code );
      void setsize( int nbits )
         { codesize = nbits; }
      int getsize( void )
         { return codesize; }
};

//..................An Encoder String Table Class

// This implementation of the string table is for the
// encoder and uses a hashing function for searching
// and addition.  Performance is generally unacceptable
// if some form of hashing is not used.

class  LzwEncoderTable
{
   public:
      int  cond;          // condition code

   protected:
      int  capacity;      // table size
      int  next_code;     // next code value
      int  root_size;     // root size in bits
      int *code_value;    // code value array
      int *prefix_code;   // prefix code array
      int *append_char;   // char for this code

   public:
      LzwEncoderTable( int rootsize );
     ~LzwEncoderTable( );
      void cleartbl( void );
      int findstr( int pfx, int chr );
      int addstr( int pfx, int chr, int index );
};

//..................A GIF/LZW Encoder Class

class GifEncoder : public Encoder,
                   public CodeFile,
                   public LzwEncoderTable
{
   public:
      int cond;       // condition code;

   protected:
      int minbits;    // min # bits per code
      int curbits;    // current # bits per code
      int maxcode;    // max code value for cur # bits
      int clearcode;  // nroots
      int endcode;    // nroots+1;
      int string;     // current prefix
      int character;  // current character

   public:
      GifEncoder( int pixelsize, char *buf, int length_buf );
     ~GifEncoder( );
      virtual int init( void );
      virtual int term( void );
      virtual int encode( unsigned char *line, int size );
      virtual int status( void );
};

//..................A Byte Stack Class

// This class is used by the GIF/LZW decoder to output
// decoded strings.  Because of the design of the algorithm
// strings are decoded last char to first char, so a stack
// is used to reverse the character order for output.

class ByteStack
{
   public:
      int cond;        // condition code

   protected:
      int   capacity;  // size in bytes
      char *top;       // top of stack
      char *bot;       // bottom of stack
      char *sp;        // current stack pointer

   public:
      ByteStack( int size );
     ~ByteStack( );
      void push( int x );
      int pop( void );
      void purge( void );
      int empty( void )
         { return (sp == top) ? 1 : 0; }
};

//..................A Decoder String Table Class

// This implementation of the string table is for the
// decoder.  Entries are directly addressed with a
// code value, so searching requires no implementation.

class  LzwDecoderTable
{
   public:
      int cond;           // condition code;

   protected:
      int  capacity;      // table size
      int  next_code;     // next code value
      int  root_size;     // root size in bits
      int *prefix_code;   // prefix code array
      int *append_char;   // char for this code

   public:
      LzwDecoderTable( int rootsize );
     ~LzwDecoderTable( );
      void cleartbl( void );
      int addstr( int pfx, int chr );
      int findstr( int code )
      {
         return ((code >= 0) && (code < next_code)) ?
                1 : 0;
      }
};

//..................A GIF/LZW Decoder Class

class GifDecoder : public Decoder,
                   public CodeFile,
                   public ByteStack,
                   public LzwDecoderTable
{
   public:
      int cond;       // condition code;

   protected:
      int minbits;    // min # bits per code
      int curbits;    // current # bits per code
      int maxcode;    // max code value for cur # bits
      int clearcode;  // nroots
      int endcode;    // nroots+1;
      int oldcode;    // prev input code
      int newcode;    // cur input code
      int firstch;    // first char of decoded string

   public:
      GifDecoder( int pixelsize, char *buf, int length_buf );
     ~GifDecoder( );
      virtual int init( void );
      virtual int term( void );
      virtual int decode( unsigned char *line, int size );
      virtual int status( void );
      int pushstr( int code );
};

#endif
