//## begin module.includes preserve=yes
//--------------------------------------------------------//
//                                                        //
//   File:    DISPLAY.CPP                                 //
//                                                        //
//   Desc:    A video display class for handling the      //
//            display of bitmapped images on VGA          //
//            compatible hardware                         //
//                                                        //
//--------------------------------------------------------//
#include <windows.h>

#include "display.hpp"
//## end module.includes preserve=yes
//## begin module.additionalDeclarations preserve=yes

#define NMODES ( sizeof(supported_modes) / \
                 sizeof(ModeMetric) )

//...............a mode metrics table

static ModeMetric supported_modes[] =
{
	ModeMetric( 0x12, 480, 640, 1, 4, 16 ),
	 ModeMetric( 0x13, 200, 320, 8, 1, 256 ),
   ModeMetric( 0x2e, 480, 640, 8, 1, 256 ),
   ModeMetric( 0x62, 480, 640, 8, 1, 256 )
};

static ModeMetric null_metric;

//...............select a metric from a mode

static ModeMetric& get_metric( int mode )
{
	for( int i=0; i<NMODES; i++ )
		if( mode == supported_modes[i].mode )
			return supported_modes[i];
	return null_metric;
}

//...............palette setting, 16 and 256 colors

void set16( rgb * pal, int nclrs )
{
	 int r;
	 int nc = (nclrs==0) ? 16 : nclrs;
	 for( int i=0; i<nc; i++ )
	 {
			rgb c = pal[i] >> 2;
//			r = get_vga_pal_reg( i );
disable();
			_BL = i;     // register number
			asm {
			  mov  ax, 1007h
			  int  10h
			}
			r = _BH;
//			set_vga_dac_reg( r, c.red, c.grn, c.blu );
			_BX = r;          //register number
			_DH = c.red;       // red component
			_CH = c.grn;       // red component
			_CL = c.blu;       // red component
			asm {
			  mov  ax, 1010h
			  int  10h
			}
enable();
	 }
}

static void set256( rgb * pal, int nclrs )
{

	 int nc = (nclrs==0) ? 256 : nclrs;
	 if( nc == 256 )
	 {
			unsigned char *buf = new unsigned char [768];
			if( buf == 0 ) return;
			int n = 0;
			for( int m=0; m<256; m++ )
			{
				 buf[n++] = pal[m].red >> 2;
				 buf[n++] = pal[m].grn >> 2;
				 buf[n++] = pal[m].blu >> 2;
			}
			set_vga_dac_256( buf );
			delete buf;
	 }
	 else for( int i=0; i<nc; i++ )
	 {
			rgb c = pal[i] >> 2;
			set_vga_dac_reg( i, c.red, c.grn, c.blu );
	 }
 ;
}


void get_vga_pal_regs(char *palregs)
{
	asm push es
	asm push dx
	_ES = FP_SEG(palregs);
	_DX = FP_OFF(palregs);
	asm{
		 mov  ax, 1009h
		 int  10h
  }
	asm pop dx
	asm pop es
}


//...............palette reading, 16 and 256 colors

void get16( rgb *pal, int nclrs )
{
	 int nc = (nclrs==0) ? 16 : nclrs;
	 asm push bx
	 asm push cx
	 for( int i=0; i<nc; i++, pal++ )
	 {
/*			int  r;
			long c;
			r = get_vga_pal_reg( i );
			c = get_vga_dac_reg( r );
			int blu = int( c & 0x3F );
			c >>= 8;
			int grn = int( c & 0x3F );
			c >>= 8;
			int red = int( c & 0x3F );
			pal[i] = rgb( red, grn, blu ) << 2;
*/
			_BL = i;     // register number
			asm {
			  mov  ax, 1007h
			  int  10h
			}
//			r = _BH;

			_BL = _BH;     // register number
			_BH = 0;
			asm {
			  mov  ax, 1015h
			  int  10h
			}
//			c = DH:CX
//			pal[i] = rgb( red, grn, blu ) << 2;
			pal->setrgb( (_DH & 0x3F)<<2, (_CH & 0x3F)<<2, (_CL & 0x3F)<<2 );
	 }
	 asm pop cx
	 asm pop bx
}

static void get256( rgb * pal, int nclrs )
{

	 int nc = (nclrs==0) ? 256 : nclrs;
	 if( nc == 256 )
	 {
			unsigned char *buf = new unsigned char [768];
			if( buf == 0 ) return;
			get_vga_dac_256( buf );
			int n = 0;
			for( int m=0; m<256; m++ )
			{
				 pal[m].red = buf[n++] << 2;
				 pal[m].grn = buf[n++] << 2;
				 pal[m].blu = buf[n++] << 2;
			}
			delete buf;
	 }
	 else for( int i=0; i<nc; i++ )
	 {
			long c = get_vga_dac_reg( i );
			int blu = int( c & 0x3F );
			c >>= 8;
			int grn = int( c & 0x3F );
			c >>= 8;
			int red = int( c & 0x3F );
			pal[i] = rgb( red, grn, blu ) << 2;
	 }
 ;
}

void get16all( rgb * pal, int nclrs )
{
	 int nc = (nclrs==0) ? 16 : nclrs;
	 if(nc==16)
	 {
		char palregs[17];
		get_vga_pal_regs( palregs );
		for( int i=0; i<nc; i++ )
		{
			int  r = palregs[ i ];
			long c = get_vga_dac_reg( r );
			int blu = int( c & 0x3F );
			c >>= 8;
			int grn = int( c & 0x3F );
			c >>= 8;
			int red = int( c & 0x3F );
			pal[i] = rgb( red, grn, blu ) << 2;
		}
	 }
	 else
	 {
		get16( pal, nclrs );
	 }
}

//...............a mode driver table

static ModeDriver drivers[] =
{
	 ModeDriver( 0x12, put_pixels_12, get_pixels_12,
							 set16, get16 ),
//	 ModeDriver( 0x13, put_pixels_13, get_pixels_13,
//							 set256, get256 ),
//	 ModeDriver( 0x2e, put_pixels_2e, get_pixels_2e,
//							 set256, get256 ),
//	 ModeDriver( 0x62, put_pixels_62, get_pixels_62,
//							 set256, get256 )
};

static ModeDriver null_driver;

//...............select a driver from a mode

static ModeDriver& get_driver( int mode )
{
	 for( int i=0; i<NMODES; i++ )
			if( mode == drivers[i].mode )
				 return drivers[i];
	 return null_driver;
}

//...............the display class

//## end module.additionalDeclarations
VgaDisplay::VgaDisplay( int mode ) 
//## begin VgaDisplay::VgaDisplay%-1553217937.initialization preserve=yes
:
						metric( ), driver( )
//## end VgaDisplay::VgaDisplay%-1553217937.initialization
{

//## begin VgaDisplay::VgaDisplay%-1553217937.body preserve=yes
	 pmode = getvideomode();
	 metric = get_metric( mode );
	 driver = get_driver( mode );
	 gmode = metric.mode;
//	 if( gmode )
//			setvideomode( gmode );
//## end VgaDisplay::VgaDisplay%-1553217937.body
}

VgaDisplay::~VgaDisplay( )
{
//## begin VgaDisplay::~VgaDisplay%-449401809.body preserve=yes
//	 if( getvideomode() != pmode )
//			setvideomode( pmode );
//## end VgaDisplay::~VgaDisplay%-449401809.body
}
 
