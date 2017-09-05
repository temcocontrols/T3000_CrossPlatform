//--------------------------------------------------------//
//                                                        //
//   File:   TIF.HPP                                      //
//                                                        //
//   Desc:   Structure and Class definitions for the      //
//           Tagged Image File Format Revision 6.0        //
//                                                        //
//--------------------------------------------------------//

#ifndef _TIF_HPP_
#define _TIF_HPP_
//## begin module.includes preserve=yes

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"

#include "gffasm.h"
#include "codec.hpp"
#include "color.hpp"
//## end module.includes preserve=yes
//## begin module.additionalDeclarations preserve=yes

//..................various constants

#define  IntelORDER   0x4949
#define  MotorORDER   0x4D4D
#define  TIFFIDEN     42

// define for system being used
#define  NativeORDER  IntelORDER

enum TiffDataTypes
{
    tNone,          // unspecified
    tUByte,         // 8-bit unsigned
    tAscii,         // Null terminated string
    tUShort,        // 16-bit unsigned
    tULong,         // 32-bit unsigned
    tURational,     // 32-bit unsigned x 2
    tSByte,         // 8-bit signed
    tByte,          // 8-bit undefined
    tSShort,        // 16-bit signed
    tSLong,         // 32-bit signed
    tSRational,     // 32-bit signed x 2
    tFloat,         // 4-byte IEEE
    tDouble         // 8-byte IEEE
};

enum TiffCompressionTypes
{
   cNone,
   cUncompressed,
   cCCITT1d,
   cGroup3Fax,
   cGroup4Fax,
   cLZW,
   cJPEG,
   cPackBits = 32773u
};

enum TiffImageTypes
{
   iBlackOnWhite,
   iWhiteOnBlack,
   iRGB,
   iColorMapped,
   iTransparency,
   iCMYK,
   iYCbCr,
   iCIELab
};

//..................nonmember functions

char *TiffTagName( int tag );
char *TiffDataTypeName( int type );
int   TiffDataTypeSize( int type );
char *TiffCompressionName( int type );
char *TiffPhotometricName( int type );
char *TiffResolutionName( int type );
char *TiffPlanarName( int type );
int   ReverseByteOrder( void );

//..................struct TIFFHEADER

//## end module.additionalDeclarations
struct TIFFHEADER
{
   unsigned short order;   // byte order Intel or Motorola
   unsigned short iden;    // magic number identifier (42)
   unsigned long  ifdofs;  // offset to first IFD

   TIFFHEADER( )
   {
//## begin TIFFHEADER::TIFFHEADER%-357400941.body preserve=yes
      order  = IntelORDER;
      iden   = TIFFIDEN;
      ifdofs = 0;
   
//## end TIFFHEADER::TIFFHEADER%-357400941.body
}
   TIFFHEADER( unsigned short ord, unsigned long iofs )
   {
//## begin TIFFHEADER::TIFFHEADER%667581897.body preserve=yes
      order  = ord;
      iden   = TIFFIDEN;
      ifdofs = iofs;
   
//## end TIFFHEADER::TIFFHEADER%667581897.body
}
  ~TIFFHEADER( )
   {
//## begin TIFFHEADER::~TIFFHEADER%1517182398.body preserve=yes
   
//## end TIFFHEADER::~TIFFHEADER%1517182398.body
}
   void list( void );
   int  get( FILE *f );
   int  put( FILE *f );
   int  isvalid( void );
};

//..................struct IFD

struct IFDENTRY
{
   unsigned short tag;     // tag identifier
   unsigned short type;    // data type
   unsigned long  count;   // number of type values
   unsigned long  valofs;  // offset to value

   IFDENTRY( )
   {
//## begin IFDENTRY::IFDENTRY%-254598593.body preserve=yes
      tag = type = 0;
      count = valofs = 0;
   
//## end IFDENTRY::IFDENTRY%-254598593.body
}
   IFDENTRY( unsigned short t, unsigned short typ,
             unsigned long cnt, unsigned long vofs )
   {
//## begin IFDENTRY::IFDENTRY%191564838.body preserve=yes
      tag    = t;
      type   = typ;
      count  = cnt;
      valofs = vofs;
   
//## end IFDENTRY::IFDENTRY%191564838.body
}
  ~IFDENTRY( )
   {
//## begin IFDENTRY::~IFDENTRY%1661377472.body preserve=yes
   
//## end IFDENTRY::~IFDENTRY%1661377472.body
}

   void list( void );
   int  get( FILE *f );
   int  put( FILE *f );

   // some convenient type conversions
   int cnt( void ) {
//## begin IFDENTRY::cnt%-901887548.body preserve=yes
 return int(count); 
//## end IFDENTRY::cnt%-901887548.body
}
   int val( void ) {
//## begin IFDENTRY::val%-76881931.body preserve=yes
 return int(valofs); 
//## end IFDENTRY::val%-76881931.body
}
   unsigned int ucnt( void ) {
//## begin IFDENTRY::ucnt%-318207313.body preserve=yes
 return (unsigned int) count; 
//## end IFDENTRY::ucnt%-318207313.body
}
   unsigned int uval( void ) {
//## begin IFDENTRY::uval%-508821644.body preserve=yes
 return (unsigned int) valofs; 
//## end IFDENTRY::uval%-508821644.body
}
};

//..................struct TIFFIMAGEDEF

struct TIFFIMAGEDEF
{
   unsigned short imgtype;     // image type              *
   unsigned short cmptype;     // compression type        *
   unsigned short width;       // width in pixels         *
   unsigned short height;      // height in pixels        *
   unsigned short depth;       // depth in bits
   unsigned short bitsamp;     // bits per sample         *
   unsigned short samppix;     // samples per pixel       *
   unsigned short planar;      // planar configuration    *
   unsigned short orient;      // orientation             *
   unsigned short hmirror;     // horz mirrored
   unsigned short vmirror;     // vert mirrored
   unsigned short rotate;      // rotated (landscape)
   unsigned short resunit;     // resolution units        *
   unsigned short xres;        // x resolution            *
   unsigned short yres;        // y resolution            *
   unsigned short nstrips;     // strips in image
   unsigned short striphgt;    // strip hgt in rows       *
   unsigned short ncolors;     // color count in pal
   rgb         *  colors;      // color map               *
   long        *  stripofs;    // array of strip offsets  *
   long        *  stripcnt;    // array of strip offsets  *
	 long           picture_bkgnd;

   TIFFIMAGEDEF( );
  ~TIFFIMAGEDEF( );
   void list( void );
   int  get( FILE *f );
};

#endif 
