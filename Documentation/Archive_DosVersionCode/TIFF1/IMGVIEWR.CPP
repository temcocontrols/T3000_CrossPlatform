//## begin module.includes preserve=yes
//--------------------------------------------------------//
//                                                        //
//   File:    IMGVIEWR.CPP                                //
//                                                        //
//   Desc:    Image viewer class                          //
//                                                        //
//--------------------------------------------------------//

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <dos.h>
#include <alloc.h>
#include <graphics.h>

#include "fxengine.h"
#include "t3000def.h"
#include "imgviewr.hpp"

#include "tifcodec.hpp"
#include "tif.hpp"
#include "mtkernel.h"
//## end module.includes preserve=yes
//## begin module.additionalDeclarations preserve=yes

extern int decode( unsigned char *line, int size, signed char *buf )   ;

extern unsigned char *scanln ;
extern FILE *ftif;
extern TIFFIMAGEDEF *idef;
extern TiffDecoder *tifd;
extern int X1,Y1,X2,Y2;
extern int NR;
char col_bkgnd=0x0F;
extern void memsize(void);
extern char type_mem;
extern char c_icon;
extern rgb *grp_current_pal;
//..................keyboard interface stuff

enum ViewerCommands
{
	 cmdError,
	 cmdEscape,
	 cmdEnter,
   cmdPanHalf,
	 cmdPanFull,
   cmdHome,
	 cmdEnd,
};

static int keys[] =
{
   0x1B, 0x0D,                  // esc, enter
   0x47, 0x4F,                  // home, end
   0x34, 0x4B, 0x36, 0x4D,      // left/right arrow
	 0x38, 0x48, 0x32, 0x50,      // up/down arrow
	 0x39, 0x49, 0x33, 0x51       // up/down page
};

static int keycmds[] =
{
   cmdEscape,  cmdEnter,
   cmdHome,    cmdEnd,
	 cmdPanHalf, cmdPanFull, cmdPanHalf, cmdPanFull,
   cmdPanHalf, cmdPanFull, cmdPanHalf, cmdPanFull,
	 cmdPanHalf, cmdPanFull, cmdPanHalf, cmdPanFull
};

static int keydxs[] =
{
	 0,  0,
   -1,  1,
   -1, -2,  1,  2,
    0,  0,  0,  0,
    0,  0,  0,  0
};

static int keydys[] =
{
    0,  0,
   -1,  1,
    0,  0,  0,  0,
   -1, -2,  1,  2,
   -1, -2,  1,  2
};

static int nkeys = sizeof(keys) / sizeof(int);

static int getkey( int& dx, int& dy )
{
   while( 1 )
   {
      int k = getch();
		if( k == 0 ) k = getch();

			for( int i=0; i<nkeys; i++ )
				 if( k == keys[i] )
         {
            dx = keydxs[i];
            dy = keydys[i];
            return keycmds[i];
         }
   }
}

//..................the viewer class

//## end module.additionalDeclarations
ImageViewer::ImageViewer( VgaDisplay *vga, ImgStore *map,
                          rgb *clrs, int nclrs,
                          int ropt, int iopt )
{
//## begin ImageViewer::ImageViewer%-161842093.body preserve=yes
   disp    = vga;
   image   = map;
   dit     = 0;
   imgpal  = 0;
	 imgcnt  = 0;
	 devpal  = 0;
   devcnt  = 0;
   clrmap  = 0;
   rendopt = ropt;
   intnopt = iopt;
   status  = 0;
   panning = 0;

   // scan line buffer
	 scanwid = disp->metric.ncolumns;
   scanhgt = disp->metric.nrows;
   set_semaphore_dos();
//	 scanbuf = new unsigned char [scanwid];
	 scanbuf = new unsigned char [image->colcnt];
	 clear_semaphore_dos();
	 if( scanbuf == 0 )
   {
      status = 1;
      return;
   }

   // allocate and initialize palettes
	 // if image is palette based
	 int i;
   if( nclrs > 0 )
   {
	 set_semaphore_dos();
			imgpal = new rgb [nclrs];
	 clear_semaphore_dos();
			if( imgpal == 0 )
			{
				 status = 1;
				 return;
			}
	 set_semaphore_dos();
			devpal = new rgb [nclrs];
	 clear_semaphore_dos();
			if( devpal == 0 )
			{
				 status = 1;
				 return;
			}
	 set_semaphore_dos();
			clrmap = new int [nclrs];
	 clear_semaphore_dos();
			if( clrmap == 0 )
			{
				 status = 1;
				 return;
			}
			imgcnt = nclrs;
			for( i=0; i<imgcnt; i++ )
			{
				 imgpal[i] = clrs[i];
				 clrmap[i] = i;
			}

			// apply any requested palette modifications
			alter_palette( imgpal, imgcnt );

			// initialize device palette to image palette
			devcnt = imgcnt;
			for( i=0; i<imgcnt; i++ )
				 devpal[i] = imgpal[i];
	 }

	 // nclrs == 0 implies a 24-bit color image,
	 // which has no palette
	 else
	 {
			devcnt = ColorDiffusionSize(disp->metric.ncolors);
			devpal = new rgb [devcnt];
			if( devpal == 0 )
			{
				 status = 1;
				 return;
			}
			imgpal = new rgb [scanwid];
			if( imgpal == 0 )
			{
				 status = 1;
				 return;
			}
	 }

	 // if the image must be approximated...
	 if( (disp->metric.ncolors < imgcnt) || (imgcnt == 0) )
	 {
			if( (ropt & renderDITHER) || (imgcnt == 0) )
			{
				 dit = new ColorDiffusionDither( scanwid,
											imgpal, imgcnt,
											ColorDiffusionPalette(),
											ColorDiffusionSize(disp->metric.ncolors) );
				 if( dit == 0 )
         {
				status = 1;
				return;
				 }
			devcnt = ColorDiffusionSize(disp->metric.ncolors);
			for( i=0; i<devcnt; i++ )
            devpal[i] = ColorDiffusionPalette()[i];
      }
      else
      {
         devcnt = disp->metric.ncolors;
         reduce_palette( devpal, imgcnt, devcnt );
         color_map( imgpal, imgcnt, devpal, devcnt,
										clrmap, 2 );
			}
	}

	 // set the device palette
  if(!c_icon)
  {
	 disp->putpalette( devpal, devcnt );
	 if(grp_current_pal)
	 {
	  for( i=0; i<devcnt; i++ )
		 grp_current_pal[i]=devpal[i];
	 }
  }

   // panning necessary?
	 if( (image->width() > scanwid) ||
       (image->height() > scanhgt) )
			panning = 1;
//## end ImageViewer::ImageViewer%-161842093.body
}

ImageViewer::~ImageViewer( )
{
//## begin ImageViewer::~ImageViewer%1468058285.body preserve=yes
	 set_semaphore_dos();
	 if( scanbuf ) delete [] scanbuf;
	 if( imgpal )  delete [] imgpal;
	 if( devpal )  delete [] devpal;
	 if( clrmap )  delete [] clrmap;
	 if( dit )     delete    dit;
	 clear_semaphore_dos();
//## end ImageViewer::~ImageViewer%1468058285.body
}

void ImageViewer::alter_palette( rgb *pal, int npal )
{
//## begin ImageViewer::alter_palette%1874659203.body preserve=yes
	 // apply any intensity mapping
	 if( intnopt & intensICNT )
			contrast_alter( pal, npal, iMORE );
   if( intnopt & intensDCNT )
      contrast_alter( pal, npal, iLESS );
   if( intnopt & intensIBRI )
			brightness_alter( pal, npal, iMORE );
	 if( intnopt & intensDBRI )
      brightness_alter( pal, npal, iLESS );

   // force grayscale?
   if( (rendopt & renderGRAY) || (disp->metric.ncolors == 2) )
	 {
			for( int i=0; i<npal; i++ )
			{
				 int g = pal[i].graylevel();
				 pal[i] = rgb( g, g, g );
			}
	 }
//## end ImageViewer::alter_palette%1874659203.body
}

void ImageViewer::go_home( ImCoord& ic )
{
//## begin ImageViewer::go_home%1317746057.body preserve=yes
/*
	 if( image->width() > scanwid )
	 {
			ic.xo = 0;
			ic.x1 = 0;
			ic.x2 = scanwid - 1;
	 }
	 else
	 {
			ic.xo = (scanwid - image->width()) / 2;
			ic.x1 = 0;
			ic.x2 = image->width() - 1;
	 }

	 if( image->height() > scanhgt )
	 {
			ic.yo = 0;
			ic.y1 = 0;
			ic.y2 = scanhgt - 1;
	 }
	 else
	 {
			ic.yo = (scanhgt - image->height()) / 2;
			ic.y1 = 0;
			ic.y2 = image->height() - 1;
	 }
*/
			ic.xo = X1;
			ic.x1 = X1;
			ic.x2 = X2;

			ic.yo = Y1;
			ic.y1 = Y1;
			ic.y2 = ((Y2-Y1)<image->height()?Y2:Y1+image->height()-1);

//## end ImageViewer::go_home%1317746057.body
}


void ImageViewer::erase( void )
{
//## begin ImageViewer::erase%-690424664.body preserve=yes
	 memset( scanbuf, 0, scanwid );
	 for( int i=0; i<scanhgt; i++ )
			disp->putscanline( scanbuf, scanwid, 0, i );
//## end ImageViewer::erase%-690424664.body
}

void ImageViewer::draw( ImCoord& ic )
{
//## begin ImageViewer::draw%-383739442.body preserve=yes
	 int            n = ic.x2 - ic.x1 + 1;
	 int            y = ic.yo;
	 unsigned char *p = scanbuf;

	 int ncols   = idef->width;

//   FILE *fo=fopen("t.tif","wb+");
	 for( int i=(type_mem?ic.y1:0); i<=ic.y2; i += (NR?NR:1)	)
	 {
			if( dit )
			{
				 if( imgcnt > 0 )
				 {
//						image->cpy( scanbuf, i, ic.x1, n );
//						dit->dither( scanbuf, n );
				 ;
				 }
				 else // 24-bit image
				 {
						unsigned char *s;
						tifd->decode( scanln, ncols ) ;
						scanln += X1*3;
//						s = image->get( i ) + ic.x1*3;
						for( int j=0; j<n; j++ )
							 imgpal[j] = rgb( *s++, *s++, *s++ );
						alter_palette( imgpal, n );
						ColorDiffusionDither *d =
						(ColorDiffusionDither *) dit;
						d->rgbdither( scanbuf, imgpal, n );
				 }
			}
			else if( imgcnt > devcnt )
			{
//				 image->cpy( scanbuf, i, ic.x1, n );
				 if ( tifd->decode( scanbuf, (NR?NR:1)*ncols ) != xOKAY )
						return;
//				 for( int j=0; j<n; j++ )
//						scanbuf[j] = clrmap[scanbuf[j]];
			}
			else
			{
			 if(type_mem=='X')
				 {
				 p = image->get( i ) ;
				 }
			 else
			 {
				if ( tifd->decode( scanbuf, (NR?NR:1)*ncols ) != xOKAY )
					return;
			 }
//				 p = image->get( i ) + ic.x1;
			}
			if(type_mem=='X')
				disp->putscanline( p, n, ic.xo, y++ );
			else
			if(i>=Y1 && i<=Y2)
				disp->putscanline( scanbuf, (NR?NR:1)*(X2-X1+1), ic.xo, i );
	 }
	 if(type_mem!='X')
		 tifd->term();
//	 fclose(fo);
//## end ImageViewer::draw%-383739442.body
}




int ImageViewer::view( void )
{
//## begin ImageViewer::view%-1954462676.body preserve=yes
	 if( status != 0 ) return status;

	 ImCoord ic;      // image/screen coords
	 int     dx, dy;  // panning deltas

//   erase();
	 go_home( ic );
	 draw( ic );
	 return status;
//## end ImageViewer::view%-1954462676.body
}
 
