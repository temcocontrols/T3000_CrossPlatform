//## begin module.includes preserve=yes
//--------------------------------------------------------//
//                                                        //
//   File:    VTIF.CPP                                    //
//                                                        //
//   Desc:    Program to view or print a TIFF file.       //
//                                                        //
//--------------------------------------------------------//

#include <windows.h>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "conio.h"
#include "ctype.h"
#include "graphics.h"
#include "bios.h"
#include <alloc.h>
#include "fxengine.h"
#include "t3000def.h"
#include "mtkernel.h"

#include "tifcodec.hpp"
#include "imgviewr.hpp"
#include "baseclas.h"


//..................Printer types

#define  LJ  0x4C4A
#define  PJ  0x504A
#define  JX  0x4A58
#define  LQ  0x4C51
#define  PS  0x5053

//## end module.includes preserve=yes
union key {
		int i;
		char ch[2];
		
} ;
//## begin key.postscript preserve=yes

ImageViewer *iv;
long table_color[256];
char picture_bkgnd;
char picture_write=0;
extern long ind_pcx_buf;
extern int mode_text;
extern rgb init_pal[16];
extern char huge *pcx_buf ;
extern char mem ;
extern char int_disk;

extern int WriteTIF( VgaDisplay& vga, char *fn,
							int x1, int y1, int x2, int y2 );
extern void prectangle(int ltopx,int ltopy,int rbottomx,int rbottomy,int color);
extern void memsize(void);
extern int bioskey_new(int cmd);
extern void get16( rgb * pal, int nclrs );
extern void get16all( rgb * pal, int nclrs );

int on_screen=0;
char type_mem;
int NR=0;
unsigned char *scanln;
FILE *ftif;
TIFFIMAGEDEF *idef;
TiffDecoder *tifd;
//..................Program globals

int X1,Y1,X2,Y2;

char      fn[80];       // path to TIFF file

int       gmode;        // video display mode
int       pmode;        // printer ID
int       ropt;         // rendering flags
int       iopt;         // itensity mapping flags
char      c_icon;         // itensity mapping flags

ImgStore   *imgmap;     // image bitmap
rgb        *pal;        //   "
int         ncolors;    //   "

//..................Exit with a message

void exit_pgm( char *msg )
{
	 if(mode_text)
		 printf( "%s\n", msg );
	 exit( 0 );
}

//..................Program usage

//..................Process pgm argument list

void process_args( char *argv )
{
	 // establish default values
	 fn[0] = 0;
	 gmode = 0x12;
	 pmode = 0;
	 ropt  = 0;
	 iopt  = 0;

				 strcpy( fn, argv );
				 char *p = strchr( fn, '.' );
				 if( p == 0 )
						strcat( fn, ".tif" );
				 else if( *(p+1) == 0 )
						*p = 0;

	 // was a file name specified?
	 if( fn[0] == 0 )
	 {
			exit( 0 );
	 }
}

//..................Create an image storage buffer


ImgStore * istore( int h, int w, int d )
{
	 ImgStore *ist = 0;

	 // attempt to create in order of preference
	 type_mem='M';
	 ist = new CnvImgStore( h, w, d );
	 return ist;
}

/*
ImgStore * istore( int h, int w, int d )
{
	 ImgStore *ist = 0;

	 type_mem=0;
	 ist = new CnvImgStore( h, w, d );
	 return ist;
}
*/
//..................Load the TIFF file

void load_tif( void )
{
	 // open file
	 set_semaphore_dos();
	 int_disk=1;
	 ftif = fopen( fn, "rb" );
	 int_disk=0;
	 if( ftif == 0 )
	 {
			clear_semaphore_dos();
			exit_pgm( "TIFF file not found" );
	 }

	 // read header
	 TIFFHEADER tif;
	 if( tif.get( ftif ) != 0 )
	 {
			clear_semaphore_dos();
			exit_pgm( "Error reading TIFF file header" );
	 }

	 // validate file
	 if( ! tif.isvalid() )
	 {
			clear_semaphore_dos();
			exit_pgm( "Specified file not a TIFF file" );
	  }

	 // create and read an image definition structure
	 int_disk=1;
	 fseek( ftif, tif.ifdofs, SEEK_SET );
	 int_disk=0;
	 idef = new TIFFIMAGEDEF;
	 int retv = idef->get( ftif );
	 clear_semaphore_dos();
	 if( retv == xUNSUPPORTED )
			exit_pgm( "TIFF file contains unsupported features" );
	 if( retv == xBADPARAM )
			exit_pgm( "TIFF file missing tag or has bad tag value" );
	 if( retv == xNOMEMORY )
			exit_pgm( "Out of memory reading TIFF file" );
	 if( retv != xOKAY )
			exit_pgm( "Error reading TIFF file IFD" );

	 // create palette
	 pal = 0;
	 ncolors = idef->ncolors;
	 if( ncolors > 0 )
	 {
			set_semaphore_dos();
			pal = new rgb [ncolors];
			clear_semaphore_dos();
			if( pal == 0 )
				 exit_pgm( "Insufficient memory to load image" );
			for( int i=0; i<ncolors; i++ )
			{
				pal[i] = idef->colors[i];
				pal[i] = init_pal[closest_rgb( pal[i], init_pal, 16)];
			}
	 }

	 // create bitmap
	 int pxbytes = (idef->depth <= 8) ? 1 : 3;
	 int rwbytes = pxbytes * idef->width;
	 int ncols   = idef->width;
	 int nrows   = idef->height;
	 if( X2 > ncols ) X2 = ncols;
	 //	 scanln = new unsigned char [rwbytes];

	 imgmap = istore( nrows, ncols, pxbytes*8 );
	 if( (imgmap == 0) )
	 {
			delete pal;
			delete imgmap;
			delete scanln;
			exit_pgm( "Insufficient memory to load image" );
	 }

//	 if( idef->depth >= 8 && (X1==0 && Y1==0 && X2==639 && Y2==479) && !type_mem) NR=15;
//	 else NR=0;
//	 if( idef->depth == 8 ) NR = 20;
//	 else NR = 1;
	 NR = 1;
	 set_semaphore_dos();
	 scanln = new unsigned char [rwbytes*(NR?NR:1)];
	 clear_semaphore_dos();

	 memset( scanln, 0, rwbytes );


	 // load bitmap
//	 printf( "Loading TIFF image from '%s'...", fn );
//	 tifd = new TiffDecoder;
//	 tifd->init( ftif, idef, &pcx_buf );
	 set_semaphore_dos();
	 tifd = new TiffDecoder( ftif, idef );
	 tifd->init();
	 clear_semaphore_dos();

	 picture_bkgnd = idef->picture_bkgnd ;

	 if(type_mem=='X')
	 {
	 VgaDisplay vga( gmode );
	 char *p;
	 p=scanln;
	 for( int i=0; i<nrows; i++ )
	 {
			p=scanln;
//			ReadPB( tifd->ftif, scanln, 640 );
			if( tifd->decode( scanln, ncols ) != xOKAY )
				 break;
			imgmap->put( scanln, i );
//				 p = imgmap->get( i ) ;
//				vga.putscanline( p, 640, 0, i );
	 }
	 tifd->term();
	 }

//	 printf( "done\n" );

	 delete scanln;

}




//..................Main

//int main( int argc, char *argv[] )
int tif( char *argv,int x1,int y1,int x2,int y2)
{
	X1 = x1; X2 = x2 ; Y1 = y1 ; Y2 = y2;
	memset(table_color, 0, sizeof(table_color));

	 process_args(  argv );
	 load_tif( );

	 // print the image
	 if( pmode != 0 )
	 {
/*
			PrinterDriver *prt = printer( pmode );
			if( prt )
			{
				 printf( "Printing..." );
				 ImagePrinter ip( prt, imgmap, pal, ncolors,
													ropt, iopt, 100, 100 );
				 ip.print( 1 );
				 printf( "done\n" );
				 delete prt;
			}
			else
				 printf( "Printer instantiation failed\n" );
*/ ;
	 }

	 // display the image
	 else
	 {
			VgaDisplay vga( gmode );
			iv = new ImageViewer( &vga, imgmap, pal, ncolors,
											ropt, iopt );
//			setbkcolor(WHITE);
//			cleardevice();
//		 setfillstyle(SOLID_FILL,WHITE);
//		 bar(0,0,639,479);
/*	 asm {
		 mov ah,10h
		 mov al,0
		 mov bl,0
		 mov bh,255
		 int 10h
		 }
*/
			 if(picture_bkgnd>=0 && picture_bkgnd<=15 )
			 {
				 setfillstyle(SOLID_FILL,idef->picture_bkgnd);
				 if(!on_screen)
				 {
					bar(0,0,639,479);
					picture_write=0;
					on_screen = 1;
				 }
				 else
				 {
					bar(0,Y1,X2,Y2);
				 }
			 }

			pcx_buf = (char huge *)tifd->map;
			mem = tifd->mem;
			iv->view( );
			long l = table_color[0];
			int c=0;
			for(int i=1;i<256;i++)
			{
			 if( l < table_color[i] )
			 {
				l = table_color[i];
				c = i;
			 }
			}

			if(picture_bkgnd != c)
//			if(picture_write)
				 {
/*
					setcolor(LIGHTRED);
					outtextxy(24,32,"Select background color and press Enter :");
					int i;
					for(i=0;i<16;i++)
					{
					 setfillstyle(SOLID_FILL, i);
					 bar(80,60+i*16,120,60+(i+1)*16);
					}
					 setfillstyle(SOLID_FILL, 0);
					 bar(150,60,350,300);
					union key key;
					i=0;
					int q=0;
					while(!q)
					{
					 while(!bioskey_new(1));
					 key.i=bioskey_new(0);
					 if(key.ch[0]==0) key.ch[0]=key.ch[1];
					 switch (key.ch[0]) {
					 case 80:
								i++;
								if(i>15) i=0;
								break;
					 case 72:
								i--;
								if(i<0) i=15;
								break;
					 case 13:
								q=1;
								break;
					 }
					 setfillstyle(SOLID_FILL, i);
					 bar(150,60,350,300);
					 prectangle(150,60,350,300,RED);
					}
					idef->picture_bkgnd=i;
					picture_write=0;

*/
					idef->picture_bkgnd=c;
					setfillstyle(SOLID_FILL,idef->picture_bkgnd);
					bar(0,0,639,479);
					ind_pcx_buf=0;
		      mem = tifd->mem;
					iv->view( );

//					WriteTIF( vga, "test.tif", 0, 0,  639, 479 );
					WriteTIF( vga, fn, 0, 0,  639, 479 );
				 }
	 }

	 delete pal;
	 delete imgmap;

	 delete tifd;
	 delete idef;
//	 delete scanln;

	 if (iv)
	 {
		delete iv;
		iv = NULL;
	 }
	 set_semaphore_dos();
	 int_disk=1;
	 fclose(ftif);
	 int_disk=0;
	 clear_semaphore_dos();

//		setbkcolor(BLACK);

	 return 0;
}

//## end key.postscript
icon::icon(void)
{
//## begin icon::icon%-1275897386.body preserve=yes
  name[0]=0;
  width=height=0;
  status=1;
//## end icon::icon%-1275897386.body
}

//void load_icon( char *fn, TIFFIMAGEDEF *idef, TiffDecoder  *tifd, char **pcx_buf )
icon::icon( char *fn )
{
//## begin icon::icon%1300299164.body preserve=yes
 name[0]=0;
 width=height=0;
 status=1;
 load_icon(fn);
//## end icon::icon%1300299164.body
}

icon::~icon( void )
{
//## begin icon::~icon%1223842933.body preserve=yes
 idef.~TIFFIMAGEDEF( );
 tifd.~TiffDecoder( );
//## end icon::~icon%1223842933.body
}

void icon::load_icon( char *fn )
{
//## begin icon::load_icon%999573351.body preserve=yes
	 // open file
	 status = 0;
	 strcpy(name, fn);
	 set_semaphore_dos();
	 int_disk=1;
	 ftif = fopen( fn, "rb" );
	 int_disk=0;
	 clear_semaphore_dos();
	 if( ftif == 0 )
	 {
		 status = 1;
		 return;
	 }
	 // read header
	 TIFFHEADER tif;
	 if( tif.get( ftif ) != 0 )
			exit_pgm( "Error reading TIFF file header" );

	 // validate file
	 if( ! tif.isvalid() )
			exit_pgm( "Specified file not a TIFF file" );

	 // create and read an image definition structure
	 set_semaphore_dos();
	 int_disk=1;
	 fseek( ftif, tif.ifdofs, SEEK_SET );
	 int_disk=0;
	 clear_semaphore_dos();
//	 idef = new TIFFIMAGEDEF;
	 int retv = idef.get( ftif );
	 if( retv == xUNSUPPORTED )
			exit_pgm( "TIFF file contains unsupported features" );
	 if( retv == xBADPARAM )
			exit_pgm( "TIFF file missing tag or has bad tag value" );
	 if( retv == xNOMEMORY )
			exit_pgm( "Out of memory reading TIFF file" );
	 if( retv != xOKAY )
			exit_pgm( "Error reading TIFF file IFD" );

	 // create palette
//
//	 pal = 0;
//	 ncolors = idef->ncolors;
	 width  =  idef.width;
	 height =  idef.height;
//	 if( ptr_icon->idef.ncolors > 0 )
//	 {
//			pal = new rgb [ncolors];
//			if( pal == 0 )
//				 exit_pgm( "Insufficient memory to load image" );
//			for( int i=0; i<ptr_icon->idef.ncolors; i++ )
//			{
//				ptr_icon->pal[i] = ptr_icon->idef.colors[i];
//				pal[i] = init_pal[closest_rgb( pal[i], init_pal, 16)];
//			}
//	 }

	 // create bitmap
//	 int pxbytes = (ptr_icon->idef->depth <= 8) ? 1 : 3;
//	 int rwbytes = pxbytes * ptr_icon->idef->width;
//	 int ncols   = ptr_icon->idef->width;
//	 int nrows   = ptr_icon->idef->height;

	 //	 scanln = new unsigned char [rwbytes];

//	 imgmap = istore( nrows, ncols, pxbytes*8 );
//	 if( (imgmap == 0) )
//	 {
//			delete pal;
//			delete imgmap;
//			delete scanln;
//			exit_pgm( "Insufficient memory to load image" );
//	 }
//	 NR = 1;

//	 scanln = new unsigned char [rwbytes];

//	 memset( scanln, 0, rwbytes );


	 // load bitmap
//	 printf( "Loading TIFF image from '%s'...", fn );
//	 tifd = new TiffDecoder( ftif, idef );
//	 tifd->init();
//	 tifd = new TiffDecoder;
	 tifd.init( ftif, &idef );

//	 picture_bkgnd = idef->picture_bkgnd ;

//	 delete scanln;
	 {
		set_semaphore_dos();
		int_disk=1;
		fclose(ftif);
		int_disk=0;
	   clear_semaphore_dos();
		ftif = 0;
	 }
//## end icon::load_icon%999573351.body
}

Icon::Icon(class icon *p, int bkgnd )
{
//## begin Icon::Icon%-985510057.body preserve=yes
 ptr_icon = p;
 image_under = NULL;
 bkgnd_color = bkgnd;
//## end Icon::Icon%-985510057.body
}

Icon::~Icon( void )
{
//## begin Icon::~Icon%-250691795.body preserve=yes
	if( image_under )
//		mfarfree( (HANDLE)FP_SEG(image_under));
	{
		mfarfree( image_under );
	}
//## end Icon::~Icon%-250691795.body
}

int Icon::draw_icon(int X, int Y, char copy, rgb *current_pal, char save_under)
{
//## begin Icon::draw_icon%-1153671223.body preserve=yes
 HANDLE handle;
 char *p;
 int	big;
 int cp = 0;
 if(copy)
 {
	copy = 0;
	big = imagesize(x, y, x+ptr_icon->width, y+ptr_icon->height);
	if (big && big!=0xffff)
	{
	 mfarmalloc((char far **)&p, (unsigned long)big , handle	);
	 if( p!=NULL )
	 {
		mgetimage(x, y, x+ptr_icon->width-1, y+ptr_icon->height-1, p);
		copy = 1;
	 }
	}
 }
 if(!copy)
 {
	mem = ptr_icon->tifd.mem;
	if(!current_pal)
	{
	 cp = 1;
	 set_semaphore_dos();
	 current_pal = new rgb [16];
	 clear_semaphore_dos();
	 get16(current_pal,0);
	}
	if(!ptr_icon->tifd.mem)
	{
	 set_semaphore_dos();
	 int_disk=1;
	 ftif = fopen( ptr_icon->name, "rb" );
	 int_disk=0;
	 ptr_icon->tifd.curline = ptr_icon->tifd.curstrip = 0;
	 int_disk=1;
	 fseek( ftif, ptr_icon->idef.stripofs[0], SEEK_SET );
	 int_disk=0;
	clear_semaphore_dos();
	 ptr_icon->tifd.cond = xOKAY;
	}
 }
 c_icon = 1;
 if( image_under )
 {
//	mputimage_10(ptr_icon->x, ptr_icon->y, ptr_icon->x+ptr_icon->width, ptr_icon->y+ptr_icon->height, ptr_icon->image_under);
	mputimage(x, y, image_under, COPY_PUT);
//	mfarfree((HANDLE)FP_SEG(image_under));
	mfarfree(image_under);
	image_under = 0;
 }
 if(save_under)
 {
	HANDLE handle;
	int	big = imagesize(X, Y, X+ptr_icon->width, Y+ptr_icon->height);
//	int	big = ptr_icon->width * ptr_icon->height + 1;
	if (big && big!=0xffff)
	{
//	 mfarmalloc((char far **)&image_under, (unsigned long)big , handle	);
	 mfarmalloc((char far **)&image_under, (unsigned long)big);
	 if( image_under!=NULL )
	 {
//		mgetimage_10(x, y, x+ptr_icon->width, y+ptr_icon->height, ptr_icon->image_under);
		mgetimage(X, Y, X+ptr_icon->width, Y+ptr_icon->height, image_under);
	 }
	}
 }
 x = X;
 y = Y;
 if(!copy)
 {
	VgaDisplay vga( 0x12 );
	int pxbytes = (ptr_icon->idef.depth <= 8) ? 1 : 3;
	int rwbytes = pxbytes * ptr_icon->idef.width;
	int ncols   = ptr_icon->idef.width;
	int nrows   = ptr_icon->idef.height;
	imgmap = istore( nrows, ncols, pxbytes*8 );
	X1 = x; Y1 = y;
	X2 = x + ptr_icon->width - 1; Y2 = y + ptr_icon->height - 1;
	for( int i=0; i<ptr_icon->idef.ncolors; i++ )
	{
	 ptr_icon->pal[i] = current_pal[closest_rgb( ptr_icon->idef.colors[i], current_pal, 16)];
	}
	set_semaphore_dos();
	iv = new ImageViewer( &vga, imgmap, ptr_icon->pal, 16,	0, 0 );
	clear_semaphore_dos();
	for( i=0; i<ptr_icon->idef.ncolors; i++ )
	{
	 ptr_icon->pal[i] = iv->devpal[i];
	}

	pcx_buf = ptr_icon->tifd.map;
	ind_pcx_buf = 0;
	tifd = &ptr_icon->tifd;
	idef = &ptr_icon->idef;
	picture_bkgnd = bkgnd_color;
//	picture_bkgnd = closest_rgb( current_pal[bkgnd_color], ptr_icon->idef.colors, 16);
	iv->view( );
	set_semaphore_dos();
	delete imgmap;
	if (iv)
	{
	 delete iv;
	 iv = NULL;
	}
	if(!ptr_icon->tifd.mem)
	{
	 int_disk=1;
	 fclose(ftif);
	 int_disk=0;
	 ftif = 0;
	}
	if(cp)
		delete [] current_pal;
	clear_semaphore_dos();
 }
 else
 {
	mputimage(X, Y, p, COPY_PUT);
	mfarfree((HANDLE)FP_SEG(p));
 }
 c_icon = 0;
/*
 if(cp)
 {
	set_semaphore_dos();
	delete [] current_pal;
	clear_semaphore_dos();
 }
*/
//## end Icon::draw_icon%-1153671223.body
}
 
