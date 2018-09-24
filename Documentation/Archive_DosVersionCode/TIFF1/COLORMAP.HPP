//--------------------------------------------------------//
//                                                        //
//   File:    COLORMAP.HPP                                //
//                                                        //
//   Desc:    Palette modification and color mapping      //
//            functions.                                  //
//                                                        //
//--------------------------------------------------------//

#ifndef _COLORMAP_HPP_
#define _COLORMAP_HPP_
//## begin module.includes preserve=yes

#include "color.hpp"
//## end module.includes preserve=yes
//## begin module.epilog preserve=yes

void xchg_rgb( rgb *pal, int m, int n );

int  closest_rgb( rgb x, rgb *pal, int npal );

int  maximal_rgb( rgb *pal, int mid, int max );

void reduce_palette( rgb *pal, int npal, int nsub );

void color_map( rgb *img, int nimg, rgb *dev, int ndev,
                int *cmap, int smooth_wt );

//## end module.epilog
#endif 
