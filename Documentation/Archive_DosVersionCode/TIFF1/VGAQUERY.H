//## begin module.cp preserve=yes
/*
 *   VGAQUERY.H - Functions for VGA adapter/mode detection
 */

//## end module.cp
#ifndef _VGAQUERY_H_
#define _VGAQUERY_H_
//## begin module.epilog preserve=yes

#if defined( __cplusplus )
extern "C" {
#endif

int test_mode( int mode );
int is_vga( void );
int is_ati( void );
int is_tseng( void );

#if defined( __cplusplus )
}
#endif

//## end module.epilog
#endif 
