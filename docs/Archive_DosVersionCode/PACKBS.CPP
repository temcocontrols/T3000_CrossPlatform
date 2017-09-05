//--------------------------------------------------------//
//                                                        //
//   File:    PACKBITS.CPP                                //
//                                                        //
//   Desc:    Encode and Decode functions for the         //
//            PackBits compression algorithm              //
//                                                        //
//--------------------------------------------------------//
int i,j,k;
static signed char *p;
static int n = 0;            // number of bytes decoded
static int cnt;  // bytes encoded
static int jmax ;
static int ix;   // get index byte
static signed char cx ;
static signed char ch;

int encode( unsigned char *line, int size , signed char *buf)
{
	 cnt = 0;  // bytes encoded
	 p = buf;
	 while( cnt < size )
	 {
			i = cnt;
			j = i + 1;
			jmax = i + 126;
			if( jmax >= size ) jmax = size-1;

			if( i == size-1 )  //................last byte alone
			{
				 *buf++ = 0;
				 *buf++ = line[i];
				 cnt++;
			}
			else if( line[i] == line[j] )  //....run
			{
				 while( (j<jmax) && (line[j]==line[j+1]) )
						j++;
				 *buf++ = i-j;
				 *buf++ = line[i];
				 cnt += j-i+1;
			}
			else  //.............................sequence
			{
				 while( (j<jmax) && (line[j]!=line[j+1]) )
						j++;
				 *buf++ = j-i;
				 for(k=0;k<j-i+1;k++)
					 *buf++ = line[i+k];
				 cnt += j-i+1;
			}
	 }

	 return buf-p;
}

//..................class PackBitsDecoder
int decode( unsigned char *line, int size,signed char *buf )
{
	 n = 0;            // number of bytes decoded
	 p=buf;

	 while( n < size )
	 {
			ix = *buf++;   // get index byte

			cx = ix;
			if( cx == -128 ) { cx=0; }

			if( cx < 0 )  //.............run
			{
				 i = 1 - cx;
				 ch = *buf++;
				 while( i-- )
				 {
						// test for buffer overflow
						if( n == size ) return -1;
						line[n++] = ch;
				 }
			}
			else  //.....................seq
			{
				 i = cx + 1;
				 while( i-- )
				 {
						// test for buffer overflow
						if( n == size ) return -1;
						line[n++] = *buf++;
				 }
			}
	 }

	 return buf-p;
}
