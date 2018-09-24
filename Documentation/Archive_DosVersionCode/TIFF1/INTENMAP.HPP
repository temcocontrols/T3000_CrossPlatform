//--------------------------------------------------------//
//                                                        //
//   File:   INTENMAP.HPP                                 //
//                                                        //
//   Desc:   Intensity mapping functions.                 //
//                                                        //
//--------------------------------------------------------//

#ifndef _INTENMAP_HPP_
#define _INTENMAP_HPP_
//## begin module.includes preserve=yes

#include "color.hpp"
//## end module.includes preserve=yes
//## begin module.epilog preserve=yes

#define  iMORE   1
#define  iLESS  -1

int  contrast_delta( int ival, int imax );
void contrast_alter( unsigned char *ivals,
                     int icnt, int isign );
void contrast_alter( int *ivals, int icnt, int isign );
void contrast_alter( rgb *iclrs, int icnt, int isign );

int  brightness_delta( int ival, int imax );
void brightness_alter( unsigned char *ivals,
                     int icnt, int isign );
void brightness_alter( int *ivals, int icnt, int isign );
void brightness_alter( rgb *iclrs, int icnt, int isign );

//## end module.epilog
#endif 
