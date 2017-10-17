//## begin module.additionalDeclarations preserve=yes
//--------------------------------------------------------//
//                                                        //
//   File:    COLOR.CPP                                   //
//                                                        //
//   Desc:    Classes for implementation of various       //
//            color models and their conversion.          //
//                                                        //
//--------------------------------------------------------//

extern "C"
{
   // see iscale.asm
   int iscale( int i, int m, int d );
}

#include "color.hpp"

//..............the RGB class

//## end module.additionalDeclarations
rgb::rgb( cmy& x )
{
//## begin rgb::rgb%151052075.body preserve=yes
   red = 255 - x.cyn;
   grn = 255 - x.mag;
   blu = 255 - x.yel;
//## end rgb::rgb%151052075.body
}

rgb::rgb( cmyk& x )
{
//## begin rgb::rgb%1941945266.body preserve=yes
   int i = x.cyn + x.blk;
   red = (i > 255) ? 0 : 255 - i;
   i = x.mag + x.blk;
   grn = (i > 255) ? 0 : 255 - i;
   i = x.yel + x.blk;
   blu = (i > 255) ? 0 : 255 - i;
//## end rgb::rgb%1941945266.body
}

unsigned char rgb::graylevel( void )
{
//## begin rgb::graylevel%1896121609.body preserve=yes
	int gry = iscale( red, 299, 1000 );
	gry += iscale( grn, 587, 1000 );
	gry += iscale( blu, 114, 1000 );
	return (unsigned char) gry;
//## end rgb::graylevel%1896121609.body
}

void	rgb::setrgb( unsigned char r, unsigned char g, unsigned char b )
{
//## begin rgb::setrgb%-1500582230.body preserve=yes
	red = r;
	grn = g;
	blu = b;
//## end rgb::setrgb%-1500582230.body
}
//..............the CMY class

cmy::cmy( rgb& x )
{
//## begin cmy::cmy%451015561.body preserve=yes
   cyn = 255 - x.red;
   mag = 255 - x.grn;
   yel = 255 - x.blu;
//## end cmy::cmy%451015561.body
}

cmy::cmy( cmyk& x )
{
//## begin cmy::cmy%1067815685.body preserve=yes
   int i = x.cyn + x.blk;
   cyn = (i > 255) ? 255 : i;
   i = x.mag + x.blk;
   mag = (i > 255) ? 255 : i;
   i = x.yel + x.blk;
   yel = (i > 255) ? 255 : i;
//## end cmy::cmy%1067815685.body
}

unsigned char cmy::graylevel( void )
{
//## begin cmy::graylevel%-830184647.body preserve=yes
   int gry = iscale( 255-cyn, 299, 1000 );
   gry += iscale( 255-mag, 587, 1000 );
   gry += iscale( 255-yel, 114, 1000 );
   return (unsigned char) gry;
//## end cmy::graylevel%-830184647.body
}

//..............the CMYK class

cmyk::cmyk( rgb& x )
{
//## begin cmyk::cmyk%-2055123806.body preserve=yes
   cmy C( x );
   int k = C.cyn;
   if( C.mag < k ) k = C.mag;
   if( C.yel < k ) k = C.yel;
   cyn = C.cyn - k;
   mag = C.mag - k;
   yel = C.yel - k;
   blk = k;
//## end cmyk::cmyk%-2055123806.body
}

cmyk::cmyk( cmy& x )
{
//## begin cmyk::cmyk%665656618.body preserve=yes
   int k = x.cyn;
   if( x.mag < k ) k = x.mag;
   if( x.yel < k ) k = x.yel;
   cyn = x.cyn - k;
   mag = x.mag - k;
   yel = x.yel - k;
   blk = k;
//## end cmyk::cmyk%665656618.body
}

unsigned char cmyk::graylevel( void )
{
//## begin cmyk::graylevel%272547519.body preserve=yes
   cmy C( *this );
   return C.graylevel();
//## end cmyk::graylevel%272547519.body
}
 
