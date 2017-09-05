//## begin module.cp preserve=yes
/*
 *   VGA13.H - VGA Mode 13h Functions
 */

//## end module.cp
#ifndef _VGA13_H_
#define _VGA13_H_
//## begin module.epilog preserve=yes

#if defined( __cplusplus )
extern "C" {
#endif

void get_pixels_13( unsigned char *pixels, int npixels,
                    int x, int y );
void put_pixels_13( unsigned char *pixels, int npixels,
                    int x, int y );

#if defined( __cplusplus )
}
#endif

//## end module.epilog
#endif 
