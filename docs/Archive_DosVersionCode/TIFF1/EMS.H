//## begin module.cp preserve=yes
/*
 *   EMS.H - EMS Memory Interface Functions
 */

//## end module.cp
#ifndef _EMS_H_
#define _EMS_H_
//## begin module.epilog preserve=yes

#if defined( __cplusplus )
extern "C" {
#endif

int    EMS_installed( void );
char * EMS_pgframeaddr( int physical_pg );
int    EMS_alloc( int npages );
void   EMS_free( int EMShandle );
int    EMS_mappage( int hand, int lpage, int ppage );

#if defined( __cplusplus )
}
#endif

//## end module.epilog
#endif 
