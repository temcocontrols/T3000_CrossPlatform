//## begin module.includes preserve=yes
//--------------------------------------------------------//
//                                                        //
//   File:   TIFCODEC.CPP                                 //
//                                                        //
//   Desc:   TIFF Encoder and Decoder classes for         //
//           Tagged Image File Format Revision 6.0        //
//                                                        //
//--------------------------------------------------------//

#include <windows.h>
#include "tifcodec.hpp"
#include "imgviewr.hpp"
//## end module.includes preserve=yes
//## begin module.additionalDeclarations preserve=yes

extern void mfarmalloc(char far **far_point, unsigned long nbytes, HANDLE& handle);
extern void mfarfree(HANDLE handle);

extern ImageViewer *iv;
extern long table_color[256];
char huge *pcx_buf ;
long ind_pcx_buf;
unsigned count_bytes;
char mem;

extern char int_disk;
extern char picture_bkgnd;
int l8;
extern void memsize(void);
//--------------------------------------------------------//
//         Group 3 Modified Huffman Compression           //
//--------------------------------------------------------//

//..................structure to hold code definitions

//## end module.additionalDeclarations
struct codedef
{
   short bitcode;   // encoded representation
   short codelen;   // length of bitcode in bits
	 short runlen;    // run length in pixels
};
//## begin codedef.postscript preserve=yes

// table entry count -- note that EOL codes are omitted

#define TBLSIZE 104

// code table for black runs, ordered by code length

static codedef black_bits;

// code table for black runs, ordered by run length

static codedef black_runs;
// code table for white runs, ordered by code length

static codedef white_bits;
// code table for white runs, ordered by run length

static codedef white_runs;

static int   codebyte, codemask;
static FILE* codefile;

int g3rdbit( void )
{
}

int g3rdcode( int pxval )
{
}

int ReadG3( FILE *fi, unsigned char *buf, int nbytes )
{
}

int g3wrtbitcode( int code, int len )
{
}

int g3wrtrun( int pxval, int cnt )
{
}

int WriteG3( FILE *fo, unsigned char *buf, int nbytes )
{
}

//--------------------------------------------------------//
//                   PackBits Compression                 //
//--------------------------------------------------------//

/*
int ReadPB( FILE *fi, unsigned char *buf, int nbytes )
{
	 int n = 0;            // number of bytes decoded

	 while( (n < nbytes) && (mem?1:!feof(fi)) )
	 {
			int ix = (mem?pcx_buf[ind_pcx_buf++]:fgetc( fi ));   // get index byte
			if( ix < 0 ) return xIOERROR;

			signed char cx = ix;
			if( cx == -128 ) cx=0;

			if( cx < 0 )  //.............run
			{
				 int i = 1 - cx;
				 char ch =  (mem?pcx_buf[ind_pcx_buf++]:fgetc( fi ));
				 while( i-- )
						if( n < nbytes )
							 (*buf)[n++] = ch;
			}
			else  //.....................seq
			{
				 int i = cx + 1;
				 while( i-- )
						if( n < nbytes )
							 (*buf)[n++] =  (mem?pcx_buf[ind_pcx_buf++]:fgetc( fi ));
			}
	 }
	 return feof(fi) ? xENDOFFILE : xOKAY;
}
*/

int ReadPB( FILE *fi, unsigned char *buf, int nbytes )
{
	 int n = 0;            // number of bytes decoded
	 int m=0;
	 while( (n < nbytes) && (mem?1:!feof(fi)) )
	 {
			int ix = (mem?*(pcx_buf+ind_pcx_buf++):fgetc( fi ));   // get index byte
//			int ix = (mem?*pcx_buf++:fgetc( fi ));   // get index byte
			if( ix < 0 ) return xIOERROR;

			signed char cx = ix;
			if( cx == -128 ) cx=0;

			if( cx < 0 )  //.............run
			{
				 int i = 1 - cx;
				 char ch =  (mem?*(pcx_buf+ind_pcx_buf++):fgetc( fi ));
//				 char ch =  (mem?*pcx_buf++:fgetc( fi ));
				 if( iv->imgcnt > iv->devcnt )
					 ch = iv->clrmap[ch];
				 table_color[ch] += i;
				 if ( l8 && ch==picture_bkgnd)
						 {
							*buf++ = cx;
//							*buf++ = cx;
							n += i;
						 }
				 else
				 while( i-- )
						if( n++ < nbytes )
						 {
							*buf++ = ch ;
//							*buf++ = ch >> 4;
//							*buf++ = ch & 0x0F;
						 }
			}
			else  //.....................seq
			{
				 int i = cx + 1;
				 while( i-- )
						if( n++ < nbytes )
							 {
								 *buf++ =  (mem?*(pcx_buf+ind_pcx_buf++):fgetc( fi ));
//								 *buf++ =  (mem?*pcx_buf++:fgetc( fi ));
								 table_color[ *(buf-1)]++;
								 if( iv->imgcnt > iv->devcnt )
									*(buf-1) = iv->clrmap[*(buf-1)];
//								*buf++ = ch >> 4;
//								*buf++ = ch & 0x0F;
							 }
			}
	 }
	 return ( mem ? xOKAY : (feof(fi) ? xENDOFFILE : xOKAY ) );
}



int WritePB( FILE *fo, unsigned char *buf, int nbytes )
{
	 int cnt = 0;  // bytes encoded

	 while( cnt < nbytes )
	 {
			int i = cnt;
			int j = i + 1;
			int jmax = i + 126;
			if( jmax >= nbytes ) jmax = nbytes-1;

			if( i == nbytes-1 )  //..............last byte alone
			{
				 fputc( 0, fo );
				 fputc( buf[i], fo );
				 cnt++;
				 count_bytes += 2;
			}
			else if( buf[i] == buf[j] )  //.......run
			 {
				 while( (j<jmax) && (buf[j]==buf[j+1]) )
						j++;
				 fputc( i-j, fo );
				 fputc( buf[i], fo );
				 cnt += j-i+1;
				 count_bytes += 2;
			 }
			 else  //.............................sequence
			 {
				 while( (j<jmax) && (buf[j]!=buf[j+1]) )
						j++;
				 fputc( j-i, fo );
				 fwrite( buf+i, j-i+1, 1, fo );
				 cnt += j-i+1;
				 count_bytes += 1 + j-i+1;
			 }
	 }
	 return xOKAY;
}

//--------------------------------------------------------//
//                      No Compression                    //
//--------------------------------------------------------//

int ReadNC( FILE *fi, unsigned char *buf, int nbytes )
{
	 fread( buf, nbytes, 1, fi );
	 return xOKAY;
}

int WriteNC( FILE *fo, unsigned char *buf, int nbytes )
{
	 fwrite( buf, nbytes, 1, fo );
	 return xOKAY;
}

//--------------------------------------------------------
//                  Class TiffDecoder
//--------------------------------------------------------

//## end codedef.postscript
TiffDecoder::TiffDecoder( FILE *fi, struct TIFFIMAGEDEF *tid )
{
//## begin TiffDecoder::TiffDecoder%271569448.body preserve=yes
  tiffdecoder( fi, tid );
//## end TiffDecoder::TiffDecoder%271569448.body
}

TiffDecoder::tiffdecoder( FILE *fi, struct TIFFIMAGEDEF *tid )
{
//## begin TiffDecoder::tiffdecoder%-990146821.body preserve=yes
	ibuf = NULL;
	map = NULL;
	if(tid)
	{
	 ftif = fi;
	 idef = tid;
	 rwbytes = (idef->depth * idef->width + 7) / 8;
	 ibuf = new unsigned char [rwbytes];
	 cond = ibuf ? xOKAY : xNOMEMORY;
	 switch( idef->cmptype )
	 {
			case cNone :
			case cUncompressed :
					 read = ReadNC;
					 break;
			case cCCITT1d :
					 read = ReadG3;
					 break;
			case cPackBits :
					 read = ReadPB;
					 break;
			default :
					 read = 0;
					 cond = xUNSUPPORTED;
					 break;
	 }
	}
//## end TiffDecoder::tiffdecoder%-990146821.body
}

TiffDecoder::~TiffDecoder( )
{
//## begin TiffDecoder::~TiffDecoder%1671696870.body preserve=yes
	 if(ibuf)
	 {
		delete ibuf;
		ibuf = NULL;
	 }	
	 if(map)
	 {
		if(map_handle)
		 mfarfree(map_handle);
		else
		 delete map;
      map_handle = 0;
		map = NULL;
	 }
//## end TiffDecoder::~TiffDecoder%1671696870.body
}

int TiffDecoder::status( void )
{
//## begin TiffDecoder::status%-650580993.body preserve=yes
	 if(!mem)
	 {
		if( feof(ftif) )   cond = xENDOFFILE;
		if( ferror(ftif) ) cond = xIOERROR;
	 }
	 return cond;
//## end TiffDecoder::status%-650580993.body
}

int TiffDecoder::init( FILE *fi, struct TIFFIMAGEDEF *tid )
{
//## begin TiffDecoder::init%1230188329.body preserve=yes
	 tiffdecoder( fi, tid );
	 init( );
//## end TiffDecoder::init%1230188329.body
}

int TiffDecoder::init( void )
{
//## begin TiffDecoder::init%-1577372432.body preserve=yes
	 char huge *p;
	 unsigned long count;
	 curline = curstrip = 0;
	 map = NULL;
	 ind_pcx_buf=0;
	 mem = 0;
//	fclose(ftif);
//	ftif = fopen("t.tif","rb+");

	 int_disk=1;
	 fseek(ftif,0,SEEK_END);
	 unsigned long l=ftell(ftif);
	 int_disk=0;
//	 fseek(ftif,0,SEEK_SET);
//	 fseek( ftif, idef->stripofs[curstrip], SEEK_SET );
	 if(l>64000)
		mfarmalloc((char far **)&map, l, map_handle);
	 else
	 {
	  map = new char [l];
	  map_handle = 0;
	 }
	 if( map!=NULL )
		{
//		 memset(map,0,l);
		 p = (char huge *)map;
		 for(int i=0; i< idef->nstrips; i++)
		 {
			int_disk=1;
			fseek( ftif, idef->stripofs[i], SEEK_SET );
			int_disk=0;
			if(idef->stripcnt)
				l = idef->stripcnt[i];
			while(l>0)
			{
			 if( l>0x8000 ) count=0x8000;
			 else count = l;
			 l-=count;
			 int_disk=1;
			 fread(p, count, 1, ftif);
			 int_disk=0;
			 p += count;
			}
//			fread(p, l, 1, ftif);
//			p += l;
		 }
//		 fread(pcx_buf, l, 1, ftif);
		 int_disk=1;
		 fseek( ftif, idef->stripofs[curstrip], SEEK_SET );
		 int_disk=0;
////	 fseek(ftif,0,SEEK_SET);
		 ind_pcx_buf = 0;
		 mem = 1;
		}

	 return status();
//## end TiffDecoder::init%-1577372432.body
}

int TiffDecoder::term( void )
{
//## begin TiffDecoder::term%-886934389.body preserve=yes
	return status();
//## end TiffDecoder::term%-886934389.body
}

void TiffDecoder::unpack( unsigned char *buf, int npxls )
{
//## begin TiffDecoder::unpack%1555815670.body preserve=yes
	 if( idef->depth >= 8 )
	 {
			int nbytes = (idef->depth + 7) / 8;
			nbytes *= npxls;
			for( int i=0; i<nbytes; i++ )
				 buf[i] = ibuf[i];
	 }
	 else
	 {
			int mask = (1 << idef->depth) - 1;
			int npix = 8 / idef->depth;
			int ntot = 0;
			int n    = 0;
			while( ntot < npxls )
			{
				 int x = reverse( ibuf[n++], idef->depth );
				 for( int i=0; i<npix; i++ )
				 {
						if( ntot < npxls )
							 buf[ntot++] = x & mask;
						x >>= idef->depth;
				 }
			}
	 }
//## end TiffDecoder::unpack%1555815670.body
}

int TiffDecoder::decode( unsigned char *buf, int npxls )
{
//## begin TiffDecoder::decode%1228524690.body preserve=yes
	 if( status() == xOKAY )
	 {
			if(!mem)
			{
			 curline++;
			 if( curline > idef->striphgt )
			 {
				 curline = 1;
				 curstrip++;
				 int_disk=1;
				 fseek( ftif, idef->stripofs[curstrip], SEEK_SET );
				 int_disk=0;
			 }
			}
			if( idef->depth >= 8 )
			 {
				l8=1;
				cond = (*read)( ftif, buf, npxls );
			 }
			else
			 {
				l8=0;
				cond = (*read)( ftif, ibuf, rwbytes );
				unpack( buf, npxls );
			 }
//			cond = (*read)( ftif, buf, npxls );
	 }
	 return status();
//## end TiffDecoder::decode%1228524690.body
}


//--------------------------------------------------------//
//                  Class TiffEncoder                     //
//--------------------------------------------------------//

TiffEncoder::TiffEncoder( FILE *fo, struct TIFFIMAGEDEF *tid )
{
//## begin TiffEncoder::TiffEncoder%-1922602023.body preserve=yes
	 ftif = fo;
   idef = tid;
	 rwbytes = (idef->depth * idef->width + 7) / 8;
   ibuf = new unsigned char [rwbytes];
   cond = ibuf ? xOKAY : xNOMEMORY;
   switch( idef->cmptype )
   {
      case cNone :
      case cUncompressed :
					 write = WriteNC;
           break;
      case cCCITT1d :
           write = WriteG3;
           break;
			case cPackBits :
					 write = WritePB;
           break;
      default :
           write = 0;
           cond = xUNSUPPORTED;
					 break;
   }
//## end TiffEncoder::TiffEncoder%-1922602023.body
}

TiffEncoder::~TiffEncoder( )
{
//## begin TiffEncoder::~TiffEncoder%1916318678.body preserve=yes
   delete ibuf;
//## end TiffEncoder::~TiffEncoder%1916318678.body
}

int TiffEncoder::status( void )
{
//## begin TiffEncoder::status%404424875.body preserve=yes
   if( ferror(ftif) ) cond = xIOERROR;
   return cond;
//## end TiffEncoder::status%404424875.body
}

int TiffEncoder::init( void )
{
//## begin TiffEncoder::init%-928632824.body preserve=yes
   return status();
//## end TiffEncoder::init%-928632824.body
}

int TiffEncoder::term( void )
{
//## begin TiffEncoder::term%967874782.body preserve=yes
	 return status();
//## end TiffEncoder::term%967874782.body
}

void TiffEncoder::pack( unsigned char *buf, int npxls )
{
//## begin TiffEncoder::pack%1855881084.body preserve=yes
	 if( idef->depth >= 8 )
	 {
			int nbytes = (idef->depth + 7) / 8;
			nbytes *= npxls;
			for( int i=0; i<nbytes; i++ )
				 ibuf[i] = buf[i];
	 }
	 else
	 {
			int mask = (1 << idef->depth) - 1;
			int npix = 8 / idef->depth;
			int ntot = 0;
			int n    = 0;
			while( ntot < npxls )
			{
				 for( int i=0; i<npix; i++ )
         {
            ibuf[n] <<= idef->depth;
            ibuf[n] |= (ntot < npxls) ?
                       buf[ntot++] & mask : 0;
				 }
				 n++;
			}
	 }
//## end TiffEncoder::pack%1855881084.body
}

int TiffEncoder::encode( unsigned char *buf, int npxls )
{
//## begin TiffEncoder::encode%-2061504125.body preserve=yes
	 if( status() == xOKAY )
	 {
			pack( buf, npxls );
			cond = (*write)( ftif, ibuf, rwbytes );
//			cond = (*write)( ftif, buf, npxls );
	 }
	 return status();
//## end TiffEncoder::encode%-2061504125.body
}

 
