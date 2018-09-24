//## begin module.cp preserve=yes
/*
 *   VGAPAL.H - Functions for VGA palette manipulation
 */

//## end module.cp
#ifndef _VGAPAL_H_
#define _VGAPAL_H_
//## begin module.epilog preserve=yes

#if defined( __cplusplus )
extern "C" {
#endif

int  get_vga_pal_reg( int reg_no );
void set_vga_pal_reg( int reg_no, int reg_val );
long get_vga_dac_reg( int reg_no );
void set_vga_dac_reg( int reg_no, int red, int grn, int blu );
void get_vga_dac_256( unsigned char *colors );
void set_vga_dac_256( unsigned char *colors );

#if defined( __cplusplus )
}
#endif

//## end module.epilog
#endif 
