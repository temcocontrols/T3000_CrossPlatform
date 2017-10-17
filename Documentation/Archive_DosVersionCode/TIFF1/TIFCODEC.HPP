//--------------------------------------------------------//
//                                                        //
//   File:   TIFCODEC.HPP                                 //
//                                                        //
//   Desc:   TIFF Encoder and Decoder classes for         //
//           Tagged Image File Format Revision 6.0        //
//                                                        //
//--------------------------------------------------------//

#ifndef _TIFCODEC_HPP_
#define _TIFCODEC_HPP_
//## begin module.includes preserve=yes

#include "tif.hpp"
#include "revbyte.hpp"
//## end module.includes preserve=yes
//## begin module.additionalDeclarations preserve=yes

//..................Scan Line I/O Functions

typedef int (*SCANIO)( FILE *, unsigned char *, int );

int ReadG3( FILE *fi, unsigned char *buf, int nbytes );
int ReadPB( FILE *fi, unsigned char *buf, int nbytes );
int ReadNC( FILE *fi, unsigned char *buf, int nbytes );

int WriteG3( FILE *fo, unsigned char *buf, int nbytes );
int WritePB( FILE *fo, unsigned char *buf, int nbytes );
int WriteNC( FILE *fo, unsigned char *buf, int nbytes );

//..................Class TiffDecoder

//## end module.additionalDeclarations
class TiffDecoder : public Decoder
{
	 public:
			FILE           *ftif;
			int             cond;
			char            mem;
			int             curline;
			int             curstrip;
			char            *map;
         HANDLE          map_handle ;

	 protected:
			SCANIO          read;
			struct TIFFIMAGEDEF   *idef;
			unsigned char  *ibuf;
			unsigned short  rwbytes;
//			int ind_pcx_buf;

	 private:
			void unpack( unsigned char *buf, int npxls );

	 public:
			TiffDecoder( FILE *fi=NULL, struct TIFFIMAGEDEF *tid=NULL );
			tiffdecoder( FILE *fi=NULL, struct TIFFIMAGEDEF *tid=NULL );
//			TiffDecoder( void ){};
			virtual ~TiffDecoder();
//			virtual int init( void );
			virtual int init( void );
			virtual int init(  FILE *fi, struct TIFFIMAGEDEF *tid );
			virtual int term( void );
			virtual int decode( unsigned char *buf, int npxls);
			virtual int status( void );
};

//..................Class TiffEncoder

class TiffEncoder : public Encoder
{
	 protected:
			FILE           *ftif;
			SCANIO          write;
			struct TIFFIMAGEDEF   *idef;
      unsigned char  *ibuf;
      unsigned short  rwbytes;
      int             cond;

   private:
      void pack( unsigned char *buf, int npxls );

   public:
      TiffEncoder( FILE *fo, struct TIFFIMAGEDEF *tid );
      virtual ~TiffEncoder( );
      virtual int init( void );
      virtual int term( void );
      virtual int encode( unsigned char *buf, int npxls );
      virtual int status( void );
};

#endif 
