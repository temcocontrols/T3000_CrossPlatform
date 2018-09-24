//## begin module.includes preserve=yes
//--------------------------------------------------------//
//                                                        //
//   File:   TIF.CPP                                      //
//                                                        //
//   Desc:   Structure and Class definitions for the      //
//           Tagged Image File Format Revision 6.0        //
//                                                        //
//--------------------------------------------------------//

#include <windows.h>
#include "tif.hpp"
//## end module.includes preserve=yes
//## begin module.additionalDeclarations preserve=yes

//..................various constant/name sets

extern char int_disk;

static int reverse_byte_order = 0;

int ReverseByteOrder( void ) { return reverse_byte_order; }

//..................various constant/name sets

//## end module.additionalDeclarations
static struct TAGNAMES
{
   unsigned short tag;
   char          *name;
}
TagNames[] =
{
	 { 254,    "NewSubfileType" },
   { 255,    "SubfileTye" },
   { 256,    "ImageWidth" },
   { 257,    "ImageHeight" },
   { 258,    "BitsPerSample" },
   { 259,    "Compression" },
   { 262,    "PhotometricInterpretation" },
   { 263,    "Thresholding" },
   { 264,    "CellWidth" },
   { 265,    "CellHeight" },
   { 266,    "FillOrder" },
   { 269,    "DocumentName" },
   { 270,    "ImageDescription" },
   { 271,    "Make" },
   { 272,    "Model" },
   { 273,    "StripOffsets" },
   { 274,    "Orientation" },
   { 277,    "SamplesPerPixel" },
	 { 278,    "RowsPerStrip" },
   { 279,    "StripByteCounts" },
	 { 280,    "MinSampleValue" },
   { 281,    "MaxSampleValue" },
   { 282,    "XResolution" },
   { 283,    "YResolution" },
   { 284,    "PlanarConfiguration" },
   { 285,    "PageName" },
   { 286,    "XPosition" },
   { 287,    "YPosition" },
   { 288,    "FreeOffsets" },
   { 289,    "FreeByteCounts" },
   { 290,    "GrayResponseUnit" },
   { 291,    "GrayResponseCurve" },
   { 292,    "Group3Options" },
   { 293,    "Group4Options" },
   { 296,    "ResolutionUnit" },
   { 297,    "PageNumber" },
   { 301,    "TransferFunction" },
   { 305,    "Software" },
	 { 306,    "DateTime" },
   { 315,    "Artist" },
	 { 316,    "HostComputer" },
   { 317,    "Predictor" },
   { 318,    "WhitePoint" },
   { 319,    "PrimaryChromaticities" },
   { 320,    "ColorMap" },
   { 321,    "HalftoneHints" },
   { 322,    "TileWidth" },
   { 323,    "TileHeight" },
   { 324,    "TileOffsets" },
   { 325,    "TileByteCounts" },
   { 332,    "InkSet" },
   { 333,    "InkNames" },
   { 334,    "NumberOfInks" },
   { 336,    "DotRange" },
   { 337,    "TargetPrinter" },
   { 338,    "ExtraSamples" },
   { 339,    "SampleFormat" },
   { 340,    "SMinSampleValue" },
	 { 341,    "SMaxSampleValue" },
   { 512,    "JPEGProc" },
	 { 513,    "JPEGInterchangeFormat" },
   { 514,    "JPEGInterchangeFormatLngth" },
   { 515,    "JPEGRestartInterval" },
   { 517,    "JPEGLosslessPredictors" },
   { 518,    "JPEGPointTransforms" },
   { 519,    "JPEGQTables" },
   { 520,    "JPEGDCTables" },
   { 521,    "JPEGACTables" },
   { 529,    "YCbCrCoefficients" },
   { 530,    "YCbCrSubSampling" },
   { 531,    "YCbCrPositioning" },
   { 532,    "ReferenceBlackWhite" },
   { 33432u, "Copyright" },
};
//## begin TAGNAMES.postscript preserve=yes
#define TAGCOUNT ( sizeof(TagNames) / sizeof(TAGNAMES) )

//## end TAGNAMES.postscript
static struct COMPRESSIONNAMES
{
	 unsigned short type;
   char          *name;
}
CompressionNames[] =
{
   { 1,      "Uncompressed" },
   { 2,      "CCITT1D" },
   { 3,      "Group3Fax" },
   { 4,      "Group4Fax" },
   { 5,      "LZW" },
   { 6,      "JPEG" },
   { 32773u, "PackBits" },
};
//## begin COMPRESSIONNAMES.postscript preserve=yes
#define COMPCOUNT ( sizeof(CompressionNames) /\
                    sizeof(COMPRESSIONNAMES) )

//## end COMPRESSIONNAMES.postscript
static struct PHOTOMETRICNAMES
{
   unsigned short type;
   char          *name;
}
PhotometricNames[] =
{
   { 0, "WhiteIsZero" },
   { 1, "BlackIsZero" },
   { 2, "RGB" },
   { 3, "RGB Palette" },
   { 4, "Transparency Mask" },
   { 5, "CMYK" },
   { 6, "YCbCr" },
   { 8, "CIELab" },
};
//## begin PHOTOMETRICNAMES.postscript preserve=yes
#define PHOTOCOUNT ( sizeof(PhotometricNames) /\
                     sizeof(PHOTOMETRICNAMES) )

//## end PHOTOMETRICNAMES.postscript
static struct DATATYPENAMES
{
   unsigned short type;
   int            size;
   char          *name;
}
DataTypeNames[] =
{
   {  0,  0,  "Unspecified" },
   {  1,  1,  "8-bit unsigned" },
   {  2,  1,  "ASCIIZ string" },
   {  3,  2,  "16-bit unsigned" },
   {  4,  4,  "32-bit unsigned" },
   {  5,  8,  "32-bit unsigned rational" },
   {  6,  1,  "8-bit signed" },
   {  7,  1,  "8-bit undefined" },
   {  8,  2,  "16-bit signed" },
   {  9,  4,  "32-bit signed" },
   { 10,  8,  "32-bit signed rational" },
   { 11,  4,  "4-byte IEEE floating point" },
   { 12,  8,  "8-byte IEEE floating point" },
};
//## begin DATATYPENAMES.postscript preserve=yes
#define DATACOUNT ( sizeof(DataTypeNames) /\
                    sizeof(DATATYPENAMES) )

//## end DATATYPENAMES.postscript
static struct RESOLUTIONNAMES
{
	 unsigned short type;
   char          *name;
}
ResolutionNames[] =
{
   { 1, "Undefined" },
   { 2, "Inches" },
   { 3, "Centimeters" },
};
//## begin RESOLUTIONNAMES.postscript preserve=yes
#define RESCOUNT ( sizeof(ResolutionNames) /\
                   sizeof(RESOLUTIONNAMES) )

//## end RESOLUTIONNAMES.postscript
static struct PLANARNAMES
{
   unsigned short type;
   char          *name;
}
PlanarNames[] =
{
   { 1, "Chunky" },
	 { 2, "Planar" },
};
//## begin PLANARNAMES.postscript preserve=yes
#define PLANARCOUNT ( sizeof(PlanarNames) /\
                     sizeof(PLANARNAMES) )

static char *Unknown = "Unknown";

char *TiffTagName( int tag )
{
   for( int i=0; i<TAGCOUNT; i++ )
      if( TagNames[i].tag == tag )
         return TagNames[i].name;
   return Unknown;
}

char *TiffDataTypeName( int type )
{
   for( int i=0; i<DATACOUNT; i++ )
			if( DataTypeNames[i].type == type )
         return DataTypeNames[i].name;
	 return Unknown;
}

int TiffDataTypeSize( int type )
{
   for( int i=0; i<DATACOUNT; i++ )
      if( DataTypeNames[i].type == type )
         return DataTypeNames[i].size;
   return 0;
}

char *TiffCompressionName( int type )
{
   for( int i=0; i<COMPCOUNT; i++ )
      if( CompressionNames[i].type == type )
         return CompressionNames[i].name;
   return Unknown;
}

char *TiffPhotometricName( int type )
{
	 for( int i=0; i<PHOTOCOUNT; i++ )
			if( PhotometricNames[i].type == type )
				 return PhotometricNames[i].name;
	 return Unknown;
}

char *TiffResolutionName( int type )
{
	 for( int i=0; i<RESCOUNT; i++ )
			if( ResolutionNames[i].type == type )
				 return ResolutionNames[i].name;
	 return Unknown;
}

char *TiffPlanarName( int type )
{
	 for( int i=0; i<PLANARCOUNT; i++ )
			if( PlanarNames[i].type == type )
				 return PlanarNames[i].name;
	 return Unknown;
}

//..................struct TIFFHEADER

//## end PLANARNAMES.postscript
void TIFFHEADER::list( void )
{
//## begin TIFFHEADER::list%-2036292456.body preserve=yes
//## end TIFFHEADER::list%-2036292456.body
}

int TIFFHEADER::get( FILE *f )
{
//## begin TIFFHEADER::get%75271793.body preserve=yes
	 int_disk=1;
	 if( fread(&order,sizeof(TIFFHEADER),1,f) != 1 )
	 {
		int_disk=0;
		return -1;
	 }
	 int_disk=0;
	 reverse_byte_order = (order == NativeORDER) ? 0 : 1;
	 if( reverse_byte_order )
	 {
			iden   = rev_word( iden );
			ifdofs = rev_dword( ifdofs );
	 }
	 return 0;
//## end TIFFHEADER::get%75271793.body
}

int TIFFHEADER::put( FILE *f )
{
//## begin TIFFHEADER::put%-797499562.body preserve=yes
	 reverse_byte_order = (order == NativeORDER) ? 0 : 1;
	 // reverse for writing
	 if( reverse_byte_order )
	 {
			iden   = rev_word( iden );
			ifdofs = rev_dword( ifdofs );
	 }
	 int_disk=1;
	 int retv = (fwrite(&order,sizeof(TIFFHEADER),1,f) == 1) ?
							0 : -1;
	 int_disk=0;
	 // restore original order
	 if( reverse_byte_order )
	 {
			iden   = rev_word( iden );
			ifdofs = rev_dword( ifdofs );
	 }
	 return retv;
//## end TIFFHEADER::put%-797499562.body
}

int TIFFHEADER::isvalid( void )
{
//## begin TIFFHEADER::isvalid%-897336725.body preserve=yes
	 if( iden != TIFFIDEN )
			return 0;
	 if( (order != IntelORDER) && (order != MotorORDER) )
			return 0;
	 return 1;
//## end TIFFHEADER::isvalid%-897336725.body
}

//..................struct IFDENTRY

void IFDENTRY::list( void )
{
//## begin IFDENTRY::list%-2078474478.body preserve=yes
//## end IFDENTRY::list%-2078474478.body
}

int IFDENTRY::get( FILE *f )
{
//## begin IFDENTRY::get%-341403856.body preserve=yes
	int_disk=1;
	if( fread(&tag,sizeof(IFDENTRY),1,f) != 1 )
	{
		int_disk=0;
		return -1;
	}
	int_disk=0;
	if( reverse_byte_order )
   {
      tag    = rev_word( tag );
      type   = rev_word( type );
      count  = rev_dword( count );
      valofs = rev_dword( valofs );
   }
   return 0;
//## end IFDENTRY::get%-341403856.body
}

int IFDENTRY::put( FILE *f )
{
//## begin IFDENTRY::put%868799417.body preserve=yes
   // reverse for writing
   if( reverse_byte_order )
   {
      tag    = rev_word( tag );
      type   = rev_word( type );
      count  = rev_dword( count );
      valofs = rev_dword( valofs );
   }
	int_disk=1;
	int retv = (fwrite(&tag,sizeof(IFDENTRY),1,f) == 1) ?
				  0 : -1;
	int_disk=0;
	// restore original order
   if( reverse_byte_order )
   {
      tag    = rev_word( tag );
      type   = rev_word( type );
      count  = rev_dword( count );
      valofs = rev_dword( valofs );
   }
	 return retv;
//## end IFDENTRY::put%868799417.body
}

//..................struct TIFFIMAGEDEF

TIFFIMAGEDEF::TIFFIMAGEDEF( )
{
//## begin TIFFIMAGEDEF::TIFFIMAGEDEF%-1627091089.body preserve=yes
	 imgtype   = 0;     // white is zero
	 cmptype   = 1;     // uncompressed
	 width     = 0;
	 height    = 0;
	 depth     = 1;     // bilevel
	 bitsamp   = 1;
	 samppix   = 1;
	 planar    = 1;     // chunky
	 orient    = 1;     // upper left org
   hmirror   = 0;
   vmirror   = 0;
	 rotate    = 0;
   resunit   = 2;     // inches
   xres      = 100;   // typical screen dpi
   yres      = 100;
   nstrips   = 0;
   striphgt  = 0;
   ncolors   = 0;
   colors    = 0;
	 stripofs  = 0;
	 stripcnt  = 0;
	 picture_bkgnd = -1;
//## end TIFFIMAGEDEF::TIFFIMAGEDEF%-1627091089.body
}

TIFFIMAGEDEF::~TIFFIMAGEDEF( )
{
//## begin TIFFIMAGEDEF::~TIFFIMAGEDEF%1676708589.body preserve=yes
	 if(colors)
	 {
		delete colors;
		colors = NULL;
	 }
	 if(stripofs)
	 {
		delete stripofs;
		stripofs = NULL;
	 }
	 if(stripcnt)
	 {
		delete stripcnt;
		stripcnt = NULL;
	 }	
//## end TIFFIMAGEDEF::~TIFFIMAGEDEF%1676708589.body
}

// file should be positioned at start of IFD

int TIFFIMAGEDEF::get( FILE *f )
{
//## begin TIFFIMAGEDEF::get%685677899.body preserve=yes
	 // read IFD entry count
	 unsigned short n;
	 int_disk=1;
	 if( fread( &n, 2, 1, f ) != 1 )
	 {
	  int_disk=0;
	  return xIOERROR;
	 }
	 int_disk=0;
	 if( reverse_byte_order ) n = rev_word( n );

	 // read each entry
	 long curofs, ltmp, ratnl[2];
	 unsigned short stmp;
	 int j;
	 for( int i=0; i<n; i++ )
	 {
			IFDENTRY x;
			if( x.get( f ) ) return xIOERROR;
			curofs = ftell( f );

			switch( x.tag )
			{
				 case 256 : // ImageWidth
							width = x.uval();
							break;
				 case 257 : // ImageHeight
							height = x.uval();
							break;
				 case 258 : // BitsPerSample
							bitsamp = x.uval();
							break;
				 case 259 : // Compression
							cmptype = x.uval();
							break;
				 case 262 : // PhotometricInterpretation
							imgtype = x.uval();
							break;
				 case 273 : // StripOffsets
							nstrips = x.ucnt();
							stripofs = new long [nstrips];
							if( stripofs == 0 ) return xNOMEMORY;
							// where are the offsets?
							int_disk=1;
							if( x.count * TiffDataTypeSize(x.type) <= 4L )
								 fseek( f, -4L, SEEK_CUR );
							else
								 fseek( f, x.valofs, SEEK_SET );
							int_disk=0;
							for( j=0; j<nstrips; j++ )
							{
								 if( (x.type == tULong) || (x.type == tSLong) )
								 {
										int_disk=1;
										fread( &ltmp, 4, 1, f );
										int_disk=0;
										stripofs[j] = ltmp;
								 }
								 else
								 {
										int_disk=1;
										fread( &stmp, 2, 1, f );
										int_disk=0;
										stripofs[j] = stmp;
								 }
							}
							// restore file position
							int_disk=1;
							fseek( f, curofs, SEEK_SET );
							int_disk=0;
							break;
				 case 274 : // Orientation
							orient = x.uval();
							break;
				 case 277 : // SamplesPerPixel
							samppix = x.uval();
							break;
				 case 278 : // RowsPerStrip
							striphgt = x.uval();
							break;
				 case 279 : // strip counts
							stripcnt = new long [nstrips];
							if( stripcnt == 0 ) return xNOMEMORY;
							// where are the offsets?
							int_disk=1;
							if( x.count * TiffDataTypeSize(x.type) <= 4L )
								 fseek( f, -4L, SEEK_CUR );
							else
								 fseek( f, x.valofs, SEEK_SET );
							int_disk=0;
							for( j=0; j<nstrips; j++ )
							{
								 if( (x.type == tULong) || (x.type == tSLong) )
								 {
										int_disk=1;
										fread( &ltmp, 4, 1, f );
										int_disk=0;
										stripcnt[j] = ltmp;
								 }
								 else
								 {
										int_disk=1;
										fread( &stmp, 2, 1, f );
										int_disk=0;
										stripcnt[j] = stmp;
								 }
							}
							// restore file position
							int_disk=1;
							fseek( f, curofs, SEEK_SET );
							int_disk=0;
							break;
				 case 282 : // X Resolution
							int_disk=1;
							fseek( f, x.valofs, SEEK_SET );
							fread( ratnl, 4, 2, f );
							int_disk=0;
							ltmp = ratnl[0] / ratnl[1];
							xres = (unsigned short) ltmp;
							// restore file position
							int_disk=1;
							fseek( f, curofs, SEEK_SET );
							int_disk=0;
							break;
				 case 283 : // Y Resolution
							int_disk=1;
							fseek( f, x.valofs, SEEK_SET );
							fread( ratnl, 4, 2, f );
							int_disk=0;
						   ltmp = ratnl[0] / ratnl[1];
							yres = (unsigned short) ltmp;
						  // restore file position
							int_disk=1;
							fseek( f, curofs, SEEK_SET );
							int_disk=0;
				  break;
         case 284 : // PlanarConfiguration
              planar = x.uval();
              break;
         case 296 : // ResolutionUnit
              resunit = x.uval();
              break;
         case 320 : // ColorMap
              ncolors = x.ucnt() / 3;
              colors = new rgb [ncolors];
              if( colors == 0 ) return xNOMEMORY;
				  int_disk=1;
				  fseek( f, x.valofs, SEEK_SET );
				  int_disk=0;
				  for( j=0; j<ncolors; j++ )
				  {
							 int_disk=1;
							 fread( &stmp, 2, 1, f );
							 int_disk=0;
							 stmp >>= 8;
							 colors[j].red = (unsigned char) stmp;
				  }
              for( j=0; j<ncolors; j++ )
              {
					  int_disk=1;
					  fread( &stmp, 2, 1, f );
					  int_disk=0;
					  stmp >>= 8;
                 colors[j].grn = (unsigned char) stmp;
              }
              for( j=0; j<ncolors; j++ )
              {
					  int_disk=1;
					  fread( &stmp, 2, 1, f );
					  int_disk=0;
					  stmp >>= 8;
                 colors[j].blu = (unsigned char) stmp;
              }
              // restore file position
					  int_disk=1;
					  fseek( f, curofs, SEEK_SET );
					  int_disk=0;
					  break;
				 case 33432 : // ResolutionUnit
							picture_bkgnd = x.valofs;
							break;
			}
	 }

	 // fill in missing values and check...

	 depth = samppix * bitsamp;

	 if( striphgt == 0 )
			striphgt = height;

	 switch( orient )
	 {
			case 2 :
					 hmirror = 1;
           break;
      case 3 :
           hmirror = 1;
           vmirror = 1;
           break;
      case 4 :
					 vmirror = 1;
					 break;
   }

   if( imgtype > 3 )
      return xUNSUPPORTED;

   if( planar == 2 )
      return xUNSUPPORTED;

   rgb Black( 0, 0, 0 );
   rgb White( 255, 255, 255 );

	 if( ncolors == 0 )
      switch( imgtype )
      {
         case 0 : // 0=white
              ncolors = 2;
              colors = new rgb [ncolors];
              if( colors == 0 ) return xNOMEMORY;
              colors[0] = White;
							colors[1] = Black;
              break;
         case 1 : // 0=black
              ncolors = 2;
              colors = new rgb [ncolors];
              if( colors == 0 ) return xNOMEMORY;
              colors[0] = Black;
              colors[1] = White;
              break;
         case 3 : // Color-mapped
              // missing palette
							return xBADPARAM;
			}

	 return xOKAY;
//## end TIFFIMAGEDEF::get%685677899.body
}

void TIFFIMAGEDEF::list( void )
{
//## begin TIFFIMAGEDEF::list%-203504671.body preserve=yes
//## end TIFFIMAGEDEF::list%-203504671.body
}
 
