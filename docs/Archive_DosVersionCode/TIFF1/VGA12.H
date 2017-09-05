//## begin module.includes preserve=yes
/*
 *   VGA12.H - VGA Mode 12h Functions
 */
#include <dos.h>
//## end module.includes preserve=yes
#ifndef _VGA12_H_
#define _VGA12_H_
//## begin module.epilog preserve=yes

#if defined( __cplusplus )
extern "C" {
#endif

void get_pixels_12( unsigned char *pixels, int npixels,
						  int x, int y, unsigned = __SegA000 );
void put_pixels_12( unsigned char *pixels, int npixels,
                    int x, int y, unsigned = __SegA000 );

#if defined( __cplusplus )
}
#endif

//## end module.epilog
#endif 
