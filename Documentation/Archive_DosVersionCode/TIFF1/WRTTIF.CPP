//## begin module.includes preserve=yes
//--------------------------------------------------------//
//                                                        //
//   File:    WRTTIF.CPP                                  //
//                                                        //
//   Desc:    Code to output a TIFF file from a           //
//            a VGA Display or a Memory Bitmap            //
//                                                        //
//--------------------------------------------------------//

#include <windows.h>
#include "tif.hpp"
#include "tifcodec.hpp"
#include "display.hpp"
#include "imgstore.hpp"
//## end module.includes preserve=yes
//## begin module.epilog preserve=yes

extern char int_disk;
extern unsigned count_bytes;
extern char picture_bkgnd;
extern TIFFIMAGEDEF *idef;
extern void memsize(void);

//..................Tag set for color-mapped images

enum ColorMappedTagSet
{
   cmWidth,
   cmHeight,
   cmBitSamp,
   cmCompress,
   cmPhotoMet,
   cmStripOfs,
   cmStripHgt,
   cmXres,
   cmYres,
   cmResUnit,
   cmColorMap,
};

static IFDENTRY ColorMappedIFD[] =
{
   IFDENTRY( 256, tUShort,    1, 0L ),   // width
   IFDENTRY( 257, tUShort,    1, 0L ),   // height
   IFDENTRY( 258, tUShort,    1, 0L ),   // bits/samp
   IFDENTRY( 259, tUShort,    1, 0L ),   // compression
   IFDENTRY( 262, tUShort,    1, 0L ),   // photomet intrp
   IFDENTRY( 273, tULong,     1, 0L ),   // strip offsets
   IFDENTRY( 278, tUShort,    1, 0L ),   // rows/strip
   IFDENTRY( 282, tURational, 1, 0L ),   // x res
   IFDENTRY( 283, tURational, 1, 0L ),   // y res
   IFDENTRY( 296, tUShort,    1, 0L ),   // res unit
	 IFDENTRY( 320, tUShort,    1, 0L ),   // color map
};

int ColorMappedCnt( void )
{
	 return sizeof(ColorMappedIFD) / sizeof(IFDENTRY);
}

IFDENTRY * ColorMappedTags( void )
{
   IFDENTRY *cmt = new IFDENTRY [ ColorMappedCnt() ];
   if( cmt )
      for( int i=0; i<ColorMappedCnt(); i++ )
         cmt[i] = ColorMappedIFD[i];
   return cmt;
}

//..................Tag set for RGB images

enum RgbTagSet
{
   rgbWidth,
   rgbHeight,
   rgbBitSamp,
	 rgbCompress,
   rgbPhotoMet,
	 rgbStripOfs,
   rgbSampPix,
   rgbStripHgt,
	 rgbXres,
   rgbYres,
   rgbResUnit,
};

static IFDENTRY RgbIFD[] =
{
   IFDENTRY( 256, tUShort,    1, 0L ),   // width
   IFDENTRY( 257, tUShort,    1, 0L ),   // height
   IFDENTRY( 258, tUShort,    1, 0L ),   // bits/samp
   IFDENTRY( 259, tUShort,    1, 0L ),   // compression
   IFDENTRY( 262, tUShort,    1, 0L ),   // photomet intrp
   IFDENTRY( 273, tULong,     1, 0L ),   // strip offsets
   IFDENTRY( 277, tUShort,    1, 0L ),   // samps/pixel
	 IFDENTRY( 278, tUShort,    1, 0L ),   // rows/strip
   IFDENTRY( 282, tURational, 1, 0L ),   // x res
   IFDENTRY( 283, tURational, 1, 0L ),   // y res
	 IFDENTRY( 296, tUShort,    1, 0L ),   // res unit
   IFDENTRY( 320, tUShort,    1, 0L ),   // color map
};

int RgbCnt( void )
{
   return sizeof(RgbIFD) / sizeof(IFDENTRY);
}

IFDENTRY * RgbTags( void )
{
   IFDENTRY *rgbt = new IFDENTRY [ RgbCnt() ];
   if( rgbt )
      for( int i=0; i<RgbCnt(); i++ )
         rgbt[i] = RgbIFD[i];
   return rgbt;
}

//..................Write VGA screen to TIFF file 'fn'

int WriteTIF( VgaDisplay& vga, char *fn,
              int x1, int y1, int x2, int y2 )
{
	 // image metrics
   int nrows   = y2 - y1 + 1;
   int ncols   = x2 - x1 + 1;
	 int nbits   = 8;
	 int ncolors = vga.metric.ncolors;

	 // scan line buffer for encoder
	 unsigned char *scanln = new unsigned char [ncols];
   if( scanln == 0 ) return xNOMEMORY;

   // create and initialize a Tiff Image Definition
	 TIFFIMAGEDEF lidef;
	 lidef.imgtype = iColorMapped;
	 lidef.cmptype = cPackBits;
	 lidef.width = ncols;
	 lidef.height = nrows;
	 lidef.depth = nbits;
	 lidef.bitsamp = nbits;
	 lidef.nstrips = 1;
	 lidef.ncolors = ncolors;
	 lidef.colors = new rgb [ncolors];
	 if( lidef.colors == 0 ) return xNOMEMORY;
	 vga.getpalette( lidef.colors, lidef.ncolors );

	 // create a TIFF header
	 TIFFHEADER thdr;

	 // create and initialize the tag set
	 IFDENTRY *tags = ColorMappedTags();
	 if( tags == 0 ) return xNOMEMORY;
	 tags[cmWidth].valofs = lidef.width;
	 tags[cmHeight].valofs = lidef.height;
	 tags[cmBitSamp].valofs = lidef.bitsamp;
	 tags[cmCompress].valofs = lidef.cmptype;
	 tags[cmPhotoMet].valofs = lidef.imgtype;
	 tags[cmStripHgt].valofs = lidef.height;
	 tags[cmXres].valofs = lidef.xres;
	 tags[cmYres].valofs = lidef.yres;
	 tags[cmResUnit].valofs = lidef.resunit;
	 tags[cmColorMap].count = lidef.ncolors * 3;

	 // open and write the file
	 int_disk=1;
	 FILE *f = fopen( fn, "wb" );
	 int_disk=0;

	 // output a placeholder for the header
	 if( thdr.put( f ) ) return xIOERROR;

	 // output the color map
	 tags[cmColorMap].valofs = ftell( f );
	 unsigned short pri;
	 for( int i=0; i<lidef.ncolors; i++ )
	 {
			pri = lidef.colors[i].red;
			pri <<= 8;
			int_disk=1;
			fwrite( &pri, 2, 1, f );
			int_disk=0;
	 }
	 for( i=0; i<lidef.ncolors; i++ )
	 {
			pri = lidef.colors[i].grn;
			pri <<= 8;
			int_disk=1;
			fwrite( &pri, 2, 1, f );
			int_disk=0;
	 }
	 for( i=0; i<lidef.ncolors; i++ )
	{
			pri = lidef.colors[i].blu;
			pri <<= 8;
			int_disk=1;
			fwrite( &pri, 2, 1, f );
		   int_disk=0;
	}

	 // output the X/Y resolutions
	 long ltmp;
	 int_disk=1;
	 tags[cmXres].valofs = ftell( f );
	 ltmp = lidef.xres;
	 fwrite( &ltmp, 4, 1, f );
	 ltmp = 1L;
	 fwrite( &ltmp, 4, 1, f );
	 tags[cmYres].valofs = ftell( f );
	 ltmp = lidef.yres;
	 fwrite( &ltmp, 4, 1, f );
	 ltmp = 1L;
	 fwrite( &ltmp, 4, 1, f );

	 // output the encoded bitmap
	 tags[cmStripOfs].valofs = ftell( f );
    int_disk=0;
	 TiffEncoder enc( f, &lidef );
	 enc.init();
	 count_bytes = 0;

	 for( i=0; i<nrows; i++ )
	 {
			vga.getscanline( scanln, ncols, x1, y1+i );
			if( enc.encode( scanln, ncols ) != xOKAY )
			{
				 delete scanln;
				 int_disk=1;
				 fclose( f );
				 int_disk=0;
				 return enc.status();
			}
	 }
	 enc.term();

	 IFDENTRY tags1;
	 tags1.tag=279;
	 tags1.type=tULong;
	 tags1.count=1;
	 tags1.valofs=count_bytes;

////////
//	 IFDENTRY tags1;
	 tags1.tag=33432;
	 tags1.type=tAscii;
	 tags1.count=1;
	 tags1.valofs=idef->picture_bkgnd;

/////////

	 // output the IFD
	 int_disk=1;
	 thdr.ifdofs = ftell( f );
	 int_disk=0;
	 short ntags = ColorMappedCnt();
	 ntags++;
	 int_disk=1;
	 fwrite( &ntags, 2, 1, f );
	 int_disk=0;
	 for( i=0; i<ntags-1; i++ )
			tags[i].put( f );
	tags1.put( f );

	 ltmp = 0L;
	 int_disk=1;
	 fwrite( &ltmp, 4, 1, f );

	 // rewrite the updated header
	 fseek( f, 0L, SEEK_SET );
	 int_disk=0;
	 thdr.put( f );

	 // finished!
	if(tags) delete tags;
	 delete scanln;
	 int retv = ferror(f) ? xIOERROR : xOKAY;
	 int_disk=1;
	 fclose( f );
	 int_disk=0;
	 return retv;
}

//..................Write an image to TIFF file 'fn'

int WriteTIF( ImgStore& img, rgb *pal, char *fn )
{
	 // image metrics
	 int nrows   = img.height();
	 int ncols   = img.width();
	 int nbits   = (img.depth() == 24) ? 24 : 8;
	 int ncolors = 2;
	 if( img.depth() == 24 ) ncolors = 0;
	 else if( img.depth() > 1 ) ncolors = 256;

	 // create and initialize a Tiff Image Definition
	 TIFFIMAGEDEF lidef;
	 lidef.imgtype = (nbits==24) ? iRGB : iColorMapped;
	 lidef.cmptype = (nbits==24) ? cUncompressed : cPackBits;
	 lidef.width = ncols;
	 lidef.height = nrows;
	 lidef.depth = nbits;
	 lidef.bitsamp = 8;
	 lidef.samppix = nbits / 8;
	 lidef.nstrips = 1;
	 lidef.ncolors = ncolors;
	 if( ncolors > 0 )
   {
			lidef.colors = new rgb [ncolors];
			if( lidef.colors == 0 ) return xNOMEMORY;
			for( int i=0; i<ncolors; i++ )
				 lidef.colors[i] = pal[i];
	 }

	 // create a TIFF header
	 TIFFHEADER thdr;

	 // create and initialize the tag set
	 IFDENTRY *tags;
	 if( lidef.ncolors > 0 )
	 {
			tags = ColorMappedTags();
			if( tags == 0 ) return xNOMEMORY;
			tags[cmWidth].valofs = lidef.width;
			tags[cmHeight].valofs = lidef.height;
			tags[cmBitSamp].valofs = lidef.bitsamp;
			tags[cmCompress].valofs = lidef.cmptype;
			tags[cmPhotoMet].valofs = lidef.imgtype;
			tags[cmStripHgt].valofs = lidef.height;
			tags[cmXres].valofs = lidef.xres;
			tags[cmYres].valofs = lidef.yres;
			tags[cmResUnit].valofs = lidef.resunit;
			tags[cmColorMap].count = lidef.ncolors * 3;
   }
   else
   {
      tags = RgbTags();
			if( tags == 0 ) return xNOMEMORY;
			tags[rgbWidth].valofs = lidef.width;
			tags[rgbHeight].valofs = lidef.height;
			tags[rgbBitSamp].valofs = lidef.bitsamp;
			tags[rgbCompress].valofs = lidef.cmptype;
			tags[rgbPhotoMet].valofs = lidef.imgtype;
			tags[rgbSampPix].valofs = lidef.samppix;
			tags[rgbStripHgt].valofs = lidef.height;
			tags[rgbXres].valofs = lidef.xres;
			tags[rgbYres].valofs = lidef.yres;
			tags[rgbResUnit].valofs = lidef.resunit;
   }

   // open and write the file
	 int_disk=1;
	 FILE *f = fopen( fn, "wb" );
	 int_disk=0;

   // output a placeholder for the header
   if( thdr.put( f ) ) return xIOERROR;

   // output the color map if present
	 if( lidef.ncolors > 0 )
	 {
      tags[cmColorMap].valofs = ftell( f );
      unsigned short pri;
			for( int i=0; i<lidef.ncolors; i++ )
			{
				 pri = lidef.colors[i].red;
				 pri <<= 8;
				 int_disk=1;
				 fwrite( &pri, 2, 1, f );
				 int_disk=0;
			}
			for( i=0; i<lidef.ncolors; i++ )
		{
				 pri = lidef.colors[i].grn;
				 pri <<= 8;
				 int_disk=1;
				 fwrite( &pri, 2, 1, f );
				 int_disk=0;
		}
			for( i=0; i<lidef.ncolors; i++ )
      {
				 pri = lidef.colors[i].blu;
				 pri <<= 8;
				 int_disk=1;
				 fwrite( &pri, 2, 1, f );
				 int_disk=0;
			}
	}

   // output the X/Y resolutions
	long ltmp;
	int ir = (lidef.ncolors > 0) ? cmXres : rgbXres;
	tags[ir].valofs = ftell( f );
	ltmp = lidef.xres;
	int_disk=1;
	fwrite( &ltmp, 4, 1, f );
	ltmp = 1L;
	fwrite( &ltmp, 4, 1, f );
	ir = (lidef.ncolors > 0) ? cmYres : rgbYres;
	tags[ir].valofs = ftell( f );
	ltmp = lidef.yres;
	fwrite( &ltmp, 4, 1, f );
	ltmp = 1L;
	fwrite( &ltmp, 4, 1, f );

	 // output the encoded bitmap
	 ir = (lidef.ncolors > 0) ? cmStripOfs : rgbStripOfs;
	 tags[ir].valofs = ftell( f );
	 int_disk=0;
	 TiffEncoder enc( f, &lidef );
	 enc.init();
	 for( int i=0; i<nrows; i++ )
	 {
			unsigned char *p = img.get( i );
			if( enc.encode( p, ncols ) != xOKAY )
			{
				 int_disk=1;
				 fclose( f );
				 int_disk=0;
				 return enc.status();
			}
	 }
	 enc.term();


	 // output the IFD
	 int_disk=1;
	 thdr.ifdofs = ftell( f );
	 short ntags = (ncolors > 0) ?  ColorMappedCnt() : RgbCnt();
	 fwrite( &ntags, 2, 1, f );
	 int_disk=0;
	 for( i=0; i<ntags; i++ )
			tags[i].put( f );
	 ltmp = 0L;
	 int_disk=1;
	 fwrite( &ltmp, 4, 1, f );

	 // rewrite the updated header
	 fseek( f, 0L, SEEK_SET );
	 int_disk=0;
	 thdr.put( f );

	 // finished!
	 int retv = ferror(f) ? xIOERROR : xOKAY;
	 int_disk=1;
	 fclose( f );
	 int_disk=0;
	 return retv;
} 
//## end module.epilog
