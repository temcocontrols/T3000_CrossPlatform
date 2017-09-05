//## begin module.cp preserve=yes
/*
 *   REVWORD.H - Functions to reverse byte orders
 */

//## end module.cp
#ifndef _REVWORD_H_
#define _REVWORD_H_
//## begin module.epilog preserve=yes

#if defined( __cplusplus )
extern "C" {
#endif

unsigned short rev_word( unsigned short );
unsigned long rev_dword( unsigned long );

#if defined( __cplusplus )
}
#endif

//## end module.epilog
#endif 
