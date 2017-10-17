//## begin module.includes preserve=yes
//--------------------------------------------------------//
//                                                        //
//   File:    COLORMAP.CPP                                //
//                                                        //
//   Desc:    Palette modification and color mapping      //
//            functions.                                  //
//                                                        //
//--------------------------------------------------------//

#include "colormap.hpp"
//## end module.includes preserve=yes
//## begin module.epilog preserve=yes

extern "C"
{
   // see iscale.asm
   int iscale( int i, int m, int d );
   // see dist3.asm
   long dist3( int r1, int r2, int g1, int g2,
               int b1, int b2 );
}

//..................swap two palette entries

void xchg_rgb( rgb *pal, int m, int n )
{
   rgb tmp = pal[m];
   pal[m] = pal[n];
   pal[n] = tmp;
}

//..................determine closest rgb in a list

int closest_rgb( rgb x, rgb *pal, int npal )
{
   long dmin = dist3( x.red, pal[0].red,
                      x.grn, pal[0].grn,
                      x.blu, pal[0].blu );
   int closest = 0;

   for( int i=1; i<npal; i++ )
   {
      long d = dist3( x.red, pal[i].red,
                      x.grn, pal[i].grn,
                      x.blu, pal[i].blu );
      if( d < dmin )
      {
         dmin = d;
         closest = i;
      }
   }

   return closest;
}

//..................find rgb in mid..max maximal to 0..mid-1

int maximal_rgb( rgb *pal, int mid, int max )
{
   long n = 1L << 30;  // a large number
   long dmin = n;
   int  maximal = mid;
   for( int i=mid; i<max; i++ )
   {
      long dsum = 0;
      for( int j=0; j<mid; j++ )
      {
         long d = dist3( pal[i].red, pal[j].red,
                         pal[i].grn, pal[j].grn,
                         pal[i].blu, pal[j].blu );
         if( d == 0 )
         {
             dsum = n;
             break;
         }
         dsum += n / d;
      }
      if( dsum < dmin )
      {
         dmin = dsum;
         maximal = i;
      }
   }
   return maximal;
}

//..................compute maximally apart reduced palette

void reduce_palette( rgb *pal, int npal, int nsub )
{
   // find "blackest" entry as a starting point
   int  i = closest_rgb( rgb(0,0,0), pal, npal );

   // reorder palette so that first nsub entries
   // are maximally far apart
   int imin = 0;
   while( imin < nsub )
   {
      xchg_rgb( pal, i, imin++ );
      i = maximal_rgb( pal, imin, npal );
   }
}

//..................compute color map, optionally smooth

void color_map( rgb *img, int nimg, rgb *dev, int ndev,
                int *cmap, int smooth_wt )
{
   int  *ccnt = 0;
   long *rsum = 0,
        *gsum = 0,
        *bsum = 0;

   // smooth_wt > 0 enables averaging filter
   {
      ccnt = new int [ndev];
      rsum = new long [ndev*3];
      if( (ccnt == 0) || (rsum == 0) )
      {
         smooth_wt = 0;
         if( ccnt ) delete ccnt;
         if( rsum ) delete rsum;
      }
      else
      {
         gsum = rsum + ndev;
         bsum = gsum + ndev;
         // initialize weighted sums
         int n = smooth_wt - 1;
         for( int i=0; i<ndev; i++ )
         {
            rsum[i] = dev[i].red;  rsum[i] *= n;
            gsum[i] = dev[i].grn;  gsum[i] *= n;
            bsum[i] = dev[i].blu;  bsum[i] *= n;
            ccnt[i] = n;
         }
      }
   }

   // compute the color map
   for( int i=0; i<nimg; i++ )
   {
      int j = closest_rgb( img[i], dev, ndev );
      cmap[i] = j;
      if( smooth_wt > 0 )
      {
         ccnt[j] += 1;
         rsum[j] += img[i].red;
         gsum[j] += img[i].grn;
         bsum[j] += img[i].blu;
      }
   }

   // smooth the device palette
   if( smooth_wt > 0 )
   {
      for( i=0; i<ndev; i++ )
      {
         rsum[i] /= ccnt[i];
         dev[i].red = rsum[i];
         gsum[i] /= ccnt[i];
         dev[i].grn = gsum[i];
         bsum[i] /= ccnt[i];
         dev[i].blu = bsum[i];
      }
   }

   if( ccnt ) delete ccnt;
   if( rsum ) delete rsum;
} 
//## end module.epilog
