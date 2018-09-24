//## begin module.epilog preserve=yes
//--------------------------------------------------------//
//                                                        //
//   File:    REVBYTE.HPP                                 //
//                                                        //
//   Desc:    Function to reverse a bit pattern.          //
//                                                        //
//--------------------------------------------------------//

extern unsigned char _reversed_bytes_1[],
                     _reversed_bytes_2[],
                     _reversed_bytes_4[];

inline int reverse( int i, int nbits )
{
   if( nbits == 1 ) return _reversed_bytes_1[i&255];
   if( nbits == 2 ) return _reversed_bytes_2[i&255];
   if( nbits == 4 ) return _reversed_bytes_4[i&255];
   return i;
} 
//## end module.epilog
