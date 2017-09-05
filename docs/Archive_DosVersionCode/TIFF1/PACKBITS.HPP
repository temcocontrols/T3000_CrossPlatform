//--------------------------------------------------------//
//                                                        //
//   File:    PACKBITS.HPP                                //
//                                                        //
//   Desc:    Class definitions for PackBits              //
//            compressor and decompressor.                //
//                                                        //
//--------------------------------------------------------//

#ifndef _PACKBITS_HPP_
#define _PACKBITS_HPP_

#include "stdio.h"

#include "codec.hpp"

//..................PackBits encoder

class PackBitsEncoder : public Encoder
{
   protected:
      FILE *outfile;

   public:
      PackBitsEncoder( FILE *f_out ) : Encoder( tPACKBITS )
      {
         outfile = f_out;
      }
     ~PackBitsEncoder( )
      {
      }
      virtual int init( void );
      virtual int term( void );
      virtual int encode( unsigned char *line, int size );
      virtual int status( void );
};

//..................PackBits decoder

class PackBitsDecoder : public Decoder
{
   protected:
      FILE *infile;

   public:
      PackBitsDecoder( FILE *f_in ) : Decoder( tPACKBITS )
      {
         infile = f_in;
      }
     ~PackBitsDecoder( )
      {
      }
      virtual int init( void );
      virtual int term( void );
      virtual int decode( unsigned char *line, int size );
      virtual int status( void );
};

#endif
