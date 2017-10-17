//## begin module.cp preserve=yes
/*
 *   ATI62.H - ATI Mode 62h Functions
 */

//## end module.cp
#ifndef _ATI62_H_
#define _ATI62_H_
//## begin module.epilog preserve=yes

#if defined( __cplusplus )
extern "C" {
#endif

void get_pixels_62( unsigned char *pixels, int npixels,
                    int x, int y );
void put_pixels_62( unsigned char *pixels, int npixels,
                    int x, int y );

#if defined( __cplusplus )
}
#endif

//## end module.epilog
#endif 
