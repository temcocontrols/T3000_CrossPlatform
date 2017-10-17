//## begin module.includes preserve=yes
//--------------------------------------------------------//
//                                                        //
//   File:    TIFDEMO.CPP                                 //
//                                                        //
//   Desc:    Example code to write a TIFF file           //
//                                                        //
//--------------------------------------------------------//

#include "wrttif.cpp"
//## end module.includes preserve=yes
//## begin module.epilog preserve=yes

char *        palname    = "EL-GRECO.PAL";
char *        imgname    = "EL-GRECO.IMG";
int           imgwidth   = 354;
int           imgheight  = 446;
int           imgcolors  = 256;
rgb           imgpalette[256];
unsigned char scanline[354];
CnvImgStore img( 446, 354, 8 );

// read the test image's palette

void read_palette( void )
{
   FILE *f = fopen( palname, "rt" );
   for( int i=0; i<imgcolors; i++ )
   {
      int r, g, b;
      fscanf( f, "%d %d %d", &r, &g, &b );
      imgpalette[i] = rgb( r, g, b );
   }
   fclose( f );
}

// read the test image into memory

void read_image( void )
{
   FILE *f = fopen( imgname, "rb" );
   for( int i=0; i<imgheight; i++ )
   {
      fread( scanline, imgwidth, 1, f );
      img.put( scanline, i );
   }
   fclose( f );
}

// output a TIF file

int main( void )
{
   read_palette( );

   read_image( );

   WriteTIF( img, imgpalette, "TIFDEMO.TIF" );

   return 0;
} 
//## end module.epilog
