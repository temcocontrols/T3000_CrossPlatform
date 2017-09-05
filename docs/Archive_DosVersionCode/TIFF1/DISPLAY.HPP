//--------------------------------------------------------//
//                                                        //
//   File:    DISPLAY.HPP                                 //
//                                                        //
//   Desc:    A video display class for handling the      //
//            display of bitmapped images on VGA          //
//            compatible hardware                         //
//                                                        //
//--------------------------------------------------------//

#ifndef _DISPLAY_HPP_
#define _DISPLAY_HPP_
//## begin module.includes preserve=yes
#include <dos.h>
#include "color.hpp"
#include "gffasm.h"
//## end module.includes preserve=yes
//## begin module.additionalDeclarations preserve=yes

//...............function pointer types

typedef void (*ScanLinePrim) ( unsigned char *,
										 int, int, int, unsigned );

typedef void (*PalettePrim) ( rgb *, int );

//...............a display mode metric structure

//## end module.additionalDeclarations
struct ModeMetric
{
	int mode;       // mode for this metric set
	int nrows;      // display height in pixels
	int ncolumns;   // display width in pixels
	int nbits;      // pixel size in bits
	int nplanes;    // number of bit planes
   int ncolors;    // max simultaneous colors
   ModeMetric( )
   {
//## begin ModeMetric::ModeMetric%812564819.body preserve=yes
      mode = nrows = ncolumns = 0;
      nbits = nplanes = ncolors = 0;
   
//## end ModeMetric::ModeMetric%812564819.body
}
   ModeMetric( int m, int nr, int nc,
                int nb, int np, int ns )
	{
//## begin ModeMetric::ModeMetric%749251428.body preserve=yes
      mode = m;  nrows = nr;  ncolumns = nc;
      nbits = nb;  nplanes = np;  ncolors = ns;
   
//## end ModeMetric::ModeMetric%749251428.body
}
  ~ModeMetric( )
   {
//## begin ModeMetric::~ModeMetric%1178615400.body preserve=yes
   
//## end ModeMetric::~ModeMetric%1178615400.body
}
};

//...............a display mode driver structure

struct ModeDriver
{
   int mode;              // mode for this driver
   ScanLinePrim putln;    // write a scan line
   ScanLinePrim getln;    // read a scan line
   PalettePrim  putpl;    // set a palette
   PalettePrim  getpl;    // read the palette
   ModeDriver( )
   {
//## begin ModeDriver::ModeDriver%589627954.body preserve=yes
      mode = 0;
      putln = getln = 0;
      putpl = getpl = 0;
   
//## end ModeDriver::ModeDriver%589627954.body
}
   ModeDriver( int m,
               ScanLinePrim pl, ScanLinePrim gl,
               PalettePrim pp, PalettePrim gp )
   {
//## begin ModeDriver::ModeDriver%530011129.body preserve=yes
      mode = m;
      putln = pl;  getln = gl;
		putpl = pp;  getpl = gp;
   
//## end ModeDriver::ModeDriver%530011129.body
}
  ~ModeDriver( )
   {
//## begin ModeDriver::~ModeDriver%2142028944.body preserve=yes
   
//## end ModeDriver::~ModeDriver%2142028944.body
}
};

//...............the display class

class VgaDisplay
{
   public:
      int gmode;           // current graphics mode
      int pmode;           // previous mode
      ModeMetric metric;   // current mode's metrics
      ModeDriver driver;   // current mode's driver

      VgaDisplay( int mode=0x12 );
     ~VgaDisplay( );
      void putscanline( unsigned char *pxls, int npxls,
								int x, int y )
		{
//## begin VgaDisplay::putscanline%1609489209.body preserve=yes
			(*driver.putln)( pxls, npxls, x, y, __SegA000 );
      
//## end VgaDisplay::putscanline%1609489209.body
}
      void getscanline( unsigned char *pxls, int npxls,
                        int x, int y )
      {
//## begin VgaDisplay::getscanline%1224984337.body preserve=yes
         (*driver.getln)( pxls, npxls, x, y, __SegA000 );
      
//## end VgaDisplay::getscanline%1224984337.body
}
      void putpalette( rgb * pal, int nc = 0 )
      {
//## begin VgaDisplay::putpalette%1653551930.body preserve=yes
         (*driver.putpl)( pal, nc );
      
//## end VgaDisplay::putpalette%1653551930.body
}
      void getpalette( rgb * pal, int nc = 0 )
      {
//## begin VgaDisplay::getpalette%-824861722.body preserve=yes
         (*driver.getpl)( pal, nc );
      
//## end VgaDisplay::getpalette%-824861722.body
}
};

#endif 
