//## begin module.includes preserve=yes
//--------------------------------------------------------//
//                                                        //
//   File:    DITHER.CPP                                  //
//                                                        //
//   Desc:    Bilevel and Color Dithering Classes         //
//                                                        //
//--------------------------------------------------------//
#include <string.h>
#include "dither.hpp"
//## end module.includes preserve=yes
//## begin module.additionalDeclarations preserve=yes

extern "C"
{
   int iscale( int, int, int );
   long dist3( int, int, int, int, int, int );
}

//..................dither matrix

//## end module.additionalDeclarations
DitherMatrix::DitherMatrix( )
{
//## begin DitherMatrix::DitherMatrix%815763082.body preserve=yes
//## end DitherMatrix::DitherMatrix%815763082.body
}

DitherMatrix::DitherMatrix( int w, int h, unsigned char *ord )
{
//## begin DitherMatrix::DitherMatrix%-1539688180.body preserve=yes
//## end DitherMatrix::DitherMatrix%-1539688180.body
}

DitherMatrix::~DitherMatrix( )
{
//## begin DitherMatrix::~DitherMatrix%1367144101.body preserve=yes
//## end DitherMatrix::~DitherMatrix%1367144101.body
}

//..................ordered dither (bilevel)

OrderedDither::OrderedDither( ) 
//## begin OrderedDither::OrderedDither%131086968.initialization preserve=yes
: Dither( )
//## end OrderedDither::OrderedDither%131086968.initialization
{

//## begin OrderedDither::OrderedDither%131086968.body preserve=yes
//## end OrderedDither::OrderedDither%131086968.body
}

OrderedDither::OrderedDither( DitherMatrix& dm,
										int von, int voff ) 
//## begin OrderedDither::OrderedDither%1237747093.initialization preserve=yes
: Dither( )
//## end OrderedDither::OrderedDither%1237747093.initialization
{

//## begin OrderedDither::OrderedDither%1237747093.body preserve=yes
//## end OrderedDither::OrderedDither%1237747093.body
}

OrderedDither::~OrderedDither( )
{
//## begin OrderedDither::~OrderedDither%75301695.body preserve=yes
//## end OrderedDither::~OrderedDither%75301695.body
}

int OrderedDither::dotval( int p, int x, int y )
{
//## begin OrderedDither::dotval%-1572093567.body preserve=yes
//## end OrderedDither::dotval%-1572093567.body
}

void OrderedDither::dither( unsigned char *pxls, int npxls )
{
//## begin OrderedDither::dither%692738589.body preserve=yes
//## end OrderedDither::dither%692738589.body
}

//..................thresholded dither (bilevel)

ThresholdDither::ThresholdDither( ) 
//## begin ThresholdDither::ThresholdDither%-1238835807.initialization preserve=yes
: Dither( )
//## end ThresholdDither::ThresholdDither%-1238835807.initialization
{

//## begin ThresholdDither::ThresholdDither%-1238835807.body preserve=yes
//## end ThresholdDither::ThresholdDither%-1238835807.body
}

ThresholdDither::ThresholdDither( int t,
					 int von, int voff ) 
//## begin ThresholdDither::ThresholdDither%-2011749271.initialization preserve=yes
: Dither( )
//## end ThresholdDither::ThresholdDither%-2011749271.initialization
{

//## begin ThresholdDither::ThresholdDither%-2011749271.body preserve=yes
//## end ThresholdDither::ThresholdDither%-2011749271.body
}

ThresholdDither::~ThresholdDither( )
{
//## begin ThresholdDither::~ThresholdDither%-142597286.body preserve=yes
//## end ThresholdDither::~ThresholdDither%-142597286.body
}

void ThresholdDither::dither( unsigned char *pxls, int npxls )
{
//## begin ThresholdDither::dither%913182444.body preserve=yes
//## end ThresholdDither::dither%913182444.body
}

//..................diffusion dither (bilevel)

DiffusionDither::DiffusionDither( ) 
//## begin DiffusionDither::DiffusionDither%383200443.initialization preserve=yes
: Dither( )
//## end DiffusionDither::DiffusionDither%383200443.initialization
{

//## begin DiffusionDither::DiffusionDither%383200443.body preserve=yes
//## end DiffusionDither::DiffusionDither%383200443.body
}

DiffusionDither::DiffusionDither( int t, int maxwidth,
					 int von, int voff ) 
//## begin DiffusionDither::DiffusionDither%995343189.initialization preserve=yes
: Dither( )
//## end DiffusionDither::DiffusionDither%995343189.initialization
{

//## begin DiffusionDither::DiffusionDither%995343189.body preserve=yes
//## end DiffusionDither::DiffusionDither%995343189.body
}

DiffusionDither::~DiffusionDither( )
{
//## begin DiffusionDither::~DiffusionDither%603199063.body preserve=yes
//## end DiffusionDither::~DiffusionDither%603199063.body
}

void DiffusionDither::dither( unsigned char *pxls, int npxls )
{
//## begin DiffusionDither::dither%1043585794.body preserve=yes
//## end DiffusionDither::dither%1043585794.body
}

void DiffusionDither::reset( void )
{
//## begin DiffusionDither::reset%-486397091.body preserve=yes
//## end DiffusionDither::reset%-486397091.body
}
//## begin module.additionalDeclarations preserve=yes

//..................palette for color threshold dither

static rgb threshold_pal[1];

rgb * ColorThresholdPalette( void )
{
}

int ColorThresholdSize( void )
{
}

//..................thresholded dither (color)

//## end module.additionalDeclarations
ColorThresholdDither::ColorThresholdDither( ) 
//## begin ColorThresholdDither::ColorThresholdDither%-461930367.initialization preserve=yes
: Dither( )
//## end ColorThresholdDither::ColorThresholdDither%-461930367.initialization
{

//## begin ColorThresholdDither::ColorThresholdDither%-461930367.body preserve=yes
//## end ColorThresholdDither::ColorThresholdDither%-461930367.body
}

ColorThresholdDither::ColorThresholdDither( int t, rgb *img,
											 int nimg ) 
//## begin ColorThresholdDither::ColorThresholdDither%1094567445.initialization preserve=yes
: Dither( )
//## end ColorThresholdDither::ColorThresholdDither%1094567445.initialization
{

//## begin ColorThresholdDither::ColorThresholdDither%1094567445.body preserve=yes
//## end ColorThresholdDither::ColorThresholdDither%1094567445.body
}

ColorThresholdDither::~ColorThresholdDither( )
{
//## begin ColorThresholdDither::~ColorThresholdDither%167679910.body preserve=yes
//## end ColorThresholdDither::~ColorThresholdDither%167679910.body
}

void ColorThresholdDither::dither( unsigned char *pxls,
																	 int npxls )
{
//## begin ColorThresholdDither::dither%442596373.body preserve=yes
//## end ColorThresholdDither::dither%442596373.body
}
//## begin module.additionalDeclarations preserve=yes

//..................palette for color diffusion dither

static rgb diffusion_pal[1];

rgb * ColorDiffusionPalette( void )
{
}

int ColorDiffusionSize( int maxcolors )
{
}

//..................error diffusion dither (color)

//## end module.additionalDeclarations
ColorDiffusionDither::ColorDiffusionDither( ) 
//## begin ColorDiffusionDither::ColorDiffusionDither%1035135743.initialization preserve=yes
: Dither( )
//## end ColorDiffusionDither::ColorDiffusionDither%1035135743.initialization
{

//## begin ColorDiffusionDither::ColorDiffusionDither%1035135743.body preserve=yes
//## end ColorDiffusionDither::ColorDiffusionDither%1035135743.body
}

ColorDiffusionDither::ColorDiffusionDither( int maxw,
										 rgb *img, int nimg,
								rgb *dev, int ndev ) 
//## begin ColorDiffusionDither::ColorDiffusionDither%-1599378173.initialization preserve=yes
: Dither( )
//## end ColorDiffusionDither::ColorDiffusionDither%-1599378173.initialization
{

//## begin ColorDiffusionDither::ColorDiffusionDither%-1599378173.body preserve=yes
//## end ColorDiffusionDither::ColorDiffusionDither%-1599378173.body
}

ColorDiffusionDither::~ColorDiffusionDither( )
{
//## begin ColorDiffusionDither::~ColorDiffusionDither%2068478439.body preserve=yes
//## end ColorDiffusionDither::~ColorDiffusionDither%2068478439.body
}

int ColorDiffusionDither::bestdevclr( int r, int g, int b )
{
//## begin ColorDiffusionDither::bestdevclr%-557065888.body preserve=yes
//## end ColorDiffusionDither::bestdevclr%-557065888.body
}

void ColorDiffusionDither::reset( void )
{
//## begin ColorDiffusionDither::reset%-354496491.body preserve=yes
//## end ColorDiffusionDither::reset%-354496491.body
}

void ColorDiffusionDither::dither( unsigned char *pxls,
																	int npxls )
{
//## begin ColorDiffusionDither::dither%1025493798.body preserve=yes
//## end ColorDiffusionDither::dither%1025493798.body
}

void ColorDiffusionDither::rgbdither( unsigned char *pxls,
																			rgb *clrs, int npxls )
{
//## begin ColorDiffusionDither::rgbdither%1389812455.body preserve=yes
//## end ColorDiffusionDither::rgbdither%1389812455.body
}
 
