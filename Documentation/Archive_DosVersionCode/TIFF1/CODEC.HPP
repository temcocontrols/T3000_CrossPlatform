//--------------------------------------------------------//
//                                                        //
//   File:    CODEC.HPP                                   //
//                                                        //
//   Desc:    Base class definitions for data             //
//            compressors and decompressors.              //
//                                                        //
//--------------------------------------------------------//

#ifndef _CODEC_HPP_
#define _CODEC_HPP_
//## begin module.includes preserve=yes
#include "tif.hpp"
//## end module.includes preserve=yes
//## begin module.additionalDeclarations preserve=yes

//.................codec types

enum tCodecTypes
{
   tNONE,
   tRLE,
   tPACKBITS,
   tHUFFMAN,
   tGROUP3,
   tLZW,
   tGIFLZW
};

//.................status codes

enum xStatusCodes
{
   xOKAY        = 0x00,
   xENDOFIMAGE  = 0x01,
   xENDOFFILE   = 0x02,
   xIOERROR     = 0x04,
   xNOMEMORY    = 0x08,
   xOUTOFSYNC   = 0x10,
   xOVERFLOW    = 0x20,
   xBADPARAM    = 0x40,
   xUNSUPPORTED = 0x80
};

//.................the encoder (compressor) base class

//## end module.additionalDeclarations
class Encoder
{
   public:
      int type;      // encoder identifier

      Encoder( int encoder_type = tNONE )
      {
//## begin Encoder::Encoder%814661500.body preserve=yes
 type = encoder_type; 
//## end Encoder::Encoder%814661500.body
}
      virtual ~Encoder( )
      {
//## begin Encoder::~Encoder%1709745592.body preserve=yes
 
//## end Encoder::~Encoder%1709745592.body
}
      virtual int encode( unsigned char *buf,
                          int nbytes ) = 0;
      virtual int init( void ) = 0;
      virtual int term( void ) = 0;
      virtual int status( void ) = 0;
};

//.................the decoder (decompressor) base class

class Decoder
{
   public:
      int   type;      // decoder type

      Decoder( int decoder_type = tNONE )
      {
//## begin Decoder::Decoder%-1727449003.body preserve=yes
 type = decoder_type; 
//## end Decoder::Decoder%-1727449003.body
}
      virtual ~Decoder( )
      {
//## begin Decoder::~Decoder%-1396007415.body preserve=yes
 
//## end Decoder::~Decoder%-1396007415.body
}
      virtual int decode( unsigned char *buf,
                          int nbytes ) = 0;
      virtual int init( void ) = 0;
			virtual int term( void ) = 0;
			virtual int status( void ) = 0;
};

#endif 
