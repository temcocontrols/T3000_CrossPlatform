//## begin module.includes preserve=yes
//--------------------------------------------------------//
//                                                        //
//   File:   INTENMAP.CPP                                 //
//                                                        //
//   Desc:   Intensity mapping functions.                 //
//                                                        //
//--------------------------------------------------------//
#include <math.h>

#include "intenmap.hpp"
//## end module.includes preserve=yes
//## begin module.epilog preserve=yes

//..................compute contrast intensity delta

int contrast_delta( int ival, int imax )
{
   // map 0..imax to -pi/2..+pi/2
   double m = double( imax );
   double x = double( ival ) - m/2.0;
   double theta = (x * 3.14159265) / m;

	 // convert back to 0..imax
#ifndef NOMATH
	 x = (sin(theta) + 1.0) * m/2.0;
	 int inew = int( x );
#else
	 int inew = 20;
#endif
	 return inew - ival;
}

//..................contrast-alter a byte intensity array

void contrast_alter( unsigned char *ivals,
                       int icnt, int isign )
{
   for( int i=0; i<icnt; i++ )
      ivals[i] += contrast_delta( ivals[i], 255 ) * isign;
}

//..................contrast-alter an int intensity array

void contrast_alter( int *ivals, int icnt, int isign )
{
   for( int i=0; i<icnt; i++ )
      ivals[i] += contrast_delta( ivals[i], 255 ) * isign;
}

//..................contrast-alter an rgb color array

void contrast_alter( rgb *iclrs, int icnt, int isign )
{
   for( int i=0; i<icnt; i++ )
   {
      iclrs[i].red += contrast_delta( iclrs[i].red, 255 )
                       * isign;
      iclrs[i].grn += contrast_delta( iclrs[i].grn, 255 )
                       * isign;
      iclrs[i].blu += contrast_delta( iclrs[i].blu, 255 )
                       * isign;
   }
}

//..................compute brightness intensity delta

int brightness_delta( int ival, int imax )
{
   // map 0..imax to 0..pi/2
   double m = double( imax );
   double x = double( ival );
   double theta = (x * 1.57079633) / m;

   // convert back to 0..imax
#ifndef NOMATH
	 x = sin(theta) * m;
	 int inew = int( x );
#else
	 int inew = 20;
#endif

   return inew - ival;
}

//..................brightness-alter a byte intensity array

void brightness_alter( unsigned char *ivals,
                       int icnt, int isign )
{
   for( int i=0; i<icnt; i++ )
      ivals[i] += brightness_delta( ivals[i], 255 ) * isign;
}

//..................brightness-alter an int intensity array

void brightness_alter( int *ivals, int icnt, int isign )
{
   for( int i=0; i<icnt; i++ )
      ivals[i] += brightness_delta( ivals[i], 255 ) * isign;
}

//..................brightness-alter an rgb color array

void brightness_alter( rgb *iclrs, int icnt, int isign )
{
   for( int i=0; i<icnt; i++ )
   {
      iclrs[i].red += brightness_delta( iclrs[i].red, 255 )
                       * isign;
      iclrs[i].grn += brightness_delta( iclrs[i].grn, 255 )
                       * isign;
      iclrs[i].blu += brightness_delta( iclrs[i].blu, 255 )
                       * isign;
   }
} 
//## end module.epilog
