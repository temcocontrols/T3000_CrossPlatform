//--------------------------------------------------------//
//                                                        //
//   File:    IMGVIEWR.HPP                                //
//                                                        //
//   Desc:    Image viewer class                          //
//                                                        //
//--------------------------------------------------------//

#ifndef _IMGVIEWR_HPP_
#define _IMGVIEWR_HPP_
//## begin module.includes preserve=yes

#include "color.hpp"
#include "colormap.hpp"
#include "intenmap.hpp"
#include "dither.hpp"
#include "display.hpp"
#include "imgstore.hpp"

#ifndef _IMAGE_OPTIONS_
#define _IMAGE_OPTIONS_

//..................option values

#define  renderNONE    0x0000   // none specified
#define  renderMAP     0x0001   // palette mapping
#define  renderDITHER  0x0002   // dithering
#define  renderGRAY    0x0004   // force gray scale

#define  intensNONE    0x0000   // as-is
#define  intensICNT    0x0001   // increased contrast
#define  intensDCNT    0x0002   // decreased contrast
#define  intensIBRI    0x0004   // increased brightness
#define  intensDBRI    0x0008   // decreased brightness

#endif

//..................an image coordinate structure

//## end module.includes preserve=yes
struct ImCoord
{
   int xo;   // screen origin
   int yo;
   int x1;   // image upper left
   int y1;
	 int x2;   // image lower right
	 int y2;
};

//..................the image viewer class

class ImageViewer
{
	 public:
			int            imgcnt;
			int            devcnt;
			int           *clrmap;
			// image and display palettes
			rgb           *imgpal;
			rgb           *devpal;

	 protected :
			// various stuff
			VgaDisplay    *disp;
			ImgStore      *image;
			Dither        *dit;
			// display stuff
      int            scanwid;
      int            scanhgt;
      unsigned char *scanbuf;
      // options and flags
      int            rendopt;
      int            intnopt;
      int            status;
      int            panning;

   private:
      void mv_horz( ImCoord& ic, int dx );
      void mv_vert( ImCoord& ic, int dy );
      void go_home( ImCoord& ic );
      void go_end( ImCoord& ic );
      void alter_palette( rgb *pal, int npal );
      void erase( void );
      void draw( ImCoord& ic );

   public :
      ImageViewer( VgaDisplay *vga, ImgStore *map,
                   rgb *clrs, int nclrs,
                   int ropt, int iopt );
     ~ImageViewer( );
      int view( void );
};

#endif 
