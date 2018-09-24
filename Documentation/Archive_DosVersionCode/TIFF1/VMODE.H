//## begin module.cp preserve=yes
/*
 *   VMODE.H - Video mode functions
 */

//## end module.cp
#ifndef _VMODE_H_
#define _VMODE_H_
//## begin module.epilog preserve=yes

#if defined( __cplusplus )
extern "C" {
#endif

int  getvideomode( void );
void setvideomode( int mode );

#if defined( __cplusplus )
}
#endif

//## end module.epilog
#endif 
