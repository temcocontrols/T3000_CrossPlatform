//--------------------------------------------------------//
//                                                        //
//   File:    DITHER.HPP                                  //
//                                                        //
//   Desc:    Bilevel and Color Dithering Classes         //
//                                                        //
//--------------------------------------------------------//

#ifndef _DITHER_HPP_
#define _DITHER_HPP_
//## begin module.includes preserve=yes

#include "color.hpp"
#include "colormap.hpp"

//..................dither matrix

//## end module.includes preserve=yes
struct DitherMatrix
{
   unsigned char width;
   unsigned char height;
   unsigned char *order;

   DitherMatrix( );
   DitherMatrix( int w, int h, unsigned char *ord );
  ~DitherMatrix( );
};
//## begin DitherMatrix.postscript preserve=yes

//..................basic dither types

enum DitherTypes
{
   ditNone,
   ditOrdered,
   ditThresholded,
   ditErrDiffused,
   ditClrThresholded,
   ditClrErrDiffused
};

//..................dither base class

//## end DitherMatrix.postscript
class Dither
{
   public:
      int type;

   public:
      Dither( ) {
//## begin Dither::Dither%364337808.body preserve=yes
 type = ditNone; 
//## end Dither::Dither%364337808.body
}
     ~Dither( ) {
//## begin Dither::~Dither%1474790123.body preserve=yes
 
//## end Dither::~Dither%1474790123.body
}
      virtual void dither( unsigned char *px, int npx ) = 0;
};

//..................ordered dither (bilevel)

class OrderedDither : public Dither
{
   protected :
      int cellw;
      int cellh;
      int ncells;
      int rowbytes;
      int on_value;
      int off_value;
      int rowcnt;
      unsigned char **cells;

   public:
      OrderedDither( );
      OrderedDither( DitherMatrix& dm,
                     int von=1, int voff=0 );
     ~OrderedDither( );
      int dotval( int p, int x, int y );
      virtual void dither( unsigned char *pxls, int npxls );
};

//..................thresholded dither (bilevel)

class ThresholdDither : public Dither
{
   protected:
      int threshold;
      int on_value;
      int off_value;

   public:
      ThresholdDither( );
      ThresholdDither( int t, int von=1, int voff=0 );
     ~ThresholdDither( );
      virtual void dither( unsigned char *pxls, int npxls );
};

//..................error diffusion dither (bilevel)

class DiffusionDither : public Dither
{
   protected:
      int threshold;
      int ewidth;
      int on_value;
      int off_value;
      int *err1;
      int *err2;

   public:
      DiffusionDither( );
      DiffusionDither( int t, int maxwidth,
                       int von=1, int voff=0 );
     ~DiffusionDither( );
      virtual void dither( unsigned char *pxls, int npxls );
      void reset( void );
};
//## begin DiffusionDither.postscript preserve=yes

//..................thresholded dither (color)

rgb * ColorThresholdPalette( void );
int   ColorThresholdSize( void );

//## end DiffusionDither.postscript
class ColorThresholdDither : public Dither
{
   protected:
      int  threshold;       // normally 127
      int  nimgcolors;      // number of image colors
      rgb *imgcolors;       // image colors

   public:
      ColorThresholdDither( );
      ColorThresholdDither( int t, rgb *img, int nimg );
     ~ColorThresholdDither( );
      virtual void dither( unsigned char *pxls, int npxls );
};
//## begin ColorThresholdDither.postscript preserve=yes

//..................error diffusion dither (color)

rgb * ColorDiffusionPalette( void );
int   ColorDiffusionSize( int maxcolors=16 );

//## end ColorThresholdDither.postscript
class ColorDiffusionDither : public Dither
{
   protected:
      int  ndevcolors;      // number of device colors
      rgb *devcolors;       // device colors
      int  nimgcolors;      // number of image colors
      rgb *imgcolors;       // image colors
      int *rerr1, *rerr2;   // red error accumulators
      int *gerr1, *gerr2;   // green error accumulators
      int *berr1, *berr2;   // blue error accumulators
      int  ewidth;          // error array sizes

   private:
      int  bestdevclr( int r, int g, int b );

   public:
      ColorDiffusionDither( );
      ColorDiffusionDither( int maxw, rgb *img, int nimg,
                            rgb *dev, int ndev );
     ~ColorDiffusionDither( );
      virtual void dither( unsigned char *pxls, int npxls );
      void rgbdither( unsigned char *pxls, rgb *clrs,
                                int npxls );
      void reset( void );
};

#endif 
