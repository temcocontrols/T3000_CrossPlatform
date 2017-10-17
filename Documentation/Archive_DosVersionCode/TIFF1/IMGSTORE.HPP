//--------------------------------------------------------//
//                                                        //
//   File:    IMAGSTORE.HPP                               //
//                                                        //
//   Desc:    Memory management classes for storing and   //
//            manipulating bitmapped images.              //
//                                                        //
//--------------------------------------------------------//

#ifndef _IMGSTORE_HPP_
#define _IMGSTORE_HPP_
//## begin module.includes preserve=yes

#include "stdio.h"
#include "string.h"
#include "ems.h"
#include "xms.h"
//## end module.includes preserve=yes
//## begin module.additionalDeclarations preserve=yes

//...............status codes

enum ImgStoreStatus
{
   imgstoreOKAY,
   imgstoreNOMEM,
   imgstoreNODRVR,
   imgstoreNODISK
};

//...............the base class

//## end module.additionalDeclarations
class ImgStore
{
   public:
      int status;     // okay or failed
      int flags;      // for the app's use
      int colcnt;     // pixels per row

	 protected:
			int rowcnt;     // row count
			int pxlbits;    // bits per pixel
      int rowbytes;   // bytes per row

   public:
      ImgStore( int nrows, int ncols, int nbits )
      {
//## begin ImgStore::ImgStore%-905158516.body preserve=yes
         status = imgstoreOKAY;
				 flags = 0;
         rowcnt = nrows;
         colcnt = ncols;
         pxlbits = nbits;
         rowbytes = ((nbits * ncols) + 7) / 8;
      
//## end ImgStore::ImgStore%-905158516.body
}
      virtual ~ImgStore( )
      {
//## begin ImgStore::~ImgStore%-233967509.body preserve=yes
      
//## end ImgStore::~ImgStore%-233967509.body
}
			virtual void put( unsigned char *data, int row ) = 0;
			virtual unsigned char *get( int row ) = 0;
			virtual void cpy( unsigned char *dest, int row ) = 0;
			virtual void cpy( unsigned char *dest, int row,
												int col, int cnt ) = 0;
			int width( void )     {
//## begin ImgStore::width%-1414858009.body preserve=yes
 return colcnt; 
//## end ImgStore::width%-1414858009.body
}
			int height( void )    {
//## begin ImgStore::height%2109134724.body preserve=yes
 return rowcnt; 
//## end ImgStore::height%2109134724.body
}
			int depth( void )     {
//## begin ImgStore::depth%1693861135.body preserve=yes
 return pxlbits; 
//## end ImgStore::depth%1693861135.body
}
			int scanbytes( void ) {
//## begin ImgStore::scanbytes%29100977.body preserve=yes
 return rowbytes; 
//## end ImgStore::scanbytes%29100977.body
}
};

//...............conventional memory

class CnvImgStore : public ImgStore
{
	 protected:
			unsigned char **rowptrs;

	 public:
			CnvImgStore( int nrows, int ncols, int nbits );
			virtual ~CnvImgStore( );
			virtual void put( unsigned char *data, int row );
			virtual unsigned char *get( int row );
			virtual void cpy( unsigned char *dest, int row );
			virtual void cpy( unsigned char *dest, int row,
												int col, int cnt );
};

//...............EMS memory

class EmsImgStore : public ImgStore
{
	 protected:
			int handle;     // EMS handle
			int npages;     // number of alloc'd pages
			int phypage;    // physical page used
			int blkcnt;     // rows per 16K page
			int blklen;     // padded row length
			char *pgframe;  // pointer to physical page

	 public:
			EmsImgStore( int nrows, int ncols, int nbits );
			virtual ~EmsImgStore( );
			virtual void put( unsigned char *data, int row );
			virtual unsigned char *get( int row );
			virtual void cpy( unsigned char *dest, int row );
			virtual void cpy( unsigned char *dest, int row,
												int col, int cnt );
};

//...............XMS memory

class XmsImgStore : public ImgStore
{
	 protected:
      unsigned handle;     // xms handle
      int blklen;          // padded row length
      char *buffer;        // cnv mem buffer
      XMSmovestruct c2x;   // for move to xms
      XMSmovestruct x2c;   // for move to cnv

   public:
      XmsImgStore( int nrows, int ncols, int nbits );
      virtual ~XmsImgStore( );
      virtual void put( unsigned char *data, int row );
      virtual unsigned char *get( int row );
      virtual void cpy( unsigned char *dest, int row );
      virtual void cpy( unsigned char *dest, int row,
                        int col, int cnt );
};

//...............Disk memory

class DskImgStore : public ImgStore
{
   protected:
      FILE *fstor;      // file pointer
      int blklen;       // padded row length
      char *buffer;     // cnv mem buffer

   public:
      DskImgStore( int nrows, int ncols, int nbits );
      virtual ~DskImgStore( );
      virtual void put( unsigned char *data, int row );
      virtual unsigned char *get( int row );
      virtual void cpy( unsigned char *dest, int row );
      virtual void cpy( unsigned char *dest, int row,
                        int col, int cnt );
};

#endif 
