//## begin module.includes preserve=yes
//--------------------------------------------------------//
//                                                        //
//   File:    IMAGSTORE.CPP                               //
//                                                        //
//   Desc:    Memory management classes for storing and   //
//            manipulating bitmapped images.              //
//                                                        //
//--------------------------------------------------------//
#include <windows.h>
#include <graphics.h>
#include <conio.h>
#include <dos.h>

#include "imgstore.hpp"
#include "aio.h"
#include "baseclas.h"
#include "parser.h"
#include "mtkernel.h"
//## end module.includes preserve=yes
//## begin module.additionalDeclarations preserve=yes

#define OKAY 1
#define NOMEM 0
#define NOUSE 2

extern Panel *ptr_panel;
extern signed char point_des[AY+1];

//char buffer[4096];
char *pixunder1;
int ccc;
//................Conventional Memory

//## end module.additionalDeclarations
CnvImgStore::CnvImgStore( int nrows, int ncols, int nbits ) 
//## begin CnvImgStore::CnvImgStore%1980662044.initialization preserve=yes
:
						 ImgStore( nrows, ncols, nbits )
//## end CnvImgStore::CnvImgStore%1980662044.initialization
{

//## begin CnvImgStore::CnvImgStore%1980662044.body preserve=yes
/*
	 int nerrors = 1;
	 rowptrs = new unsigned char * [rowcnt];
	 if( rowptrs )
	 {
			nerrors--;
			for( int i=0; i<rowcnt; i++ )
			{
				 rowptrs[i] = new unsigned char [rowbytes];
				 if( rowptrs[i] )
						memset( rowptrs[i], 0, rowbytes );
				 else
						nerrors++;
			}
	 }
	 if( nerrors > 0 ) status = imgstoreNOMEM;
*/
 status = imgstoreOKAY;
//## end CnvImgStore::CnvImgStore%1980662044.body
}

CnvImgStore::~CnvImgStore( )
{
//## begin CnvImgStore::~CnvImgStore%2099760026.body preserve=yes
/*
	 if( rowptrs )
	 {
			for( int i=0; i<rowcnt; i++ )
			{
				 if( rowptrs[i] ) delete rowptrs[i];
			}
			delete rowptrs;
	 }
*/
//## end CnvImgStore::~CnvImgStore%2099760026.body
}

void CnvImgStore::put( unsigned char *data, int row )
{
//## begin CnvImgStore::put%790509207.body preserve=yes
/*
	 if( status == imgstoreOKAY )
			if( (row >= 0) && (row < rowcnt) )
				 memcpy( rowptrs[row], data, rowbytes );
*/
//## end CnvImgStore::put%790509207.body
}

unsigned char * CnvImgStore::get( int row )
{
//## begin CnvImgStore::get%1615204215.body preserve=yes
/*
	 if( status == imgstoreOKAY )
			if( (row >= 0) && (row < rowcnt) )
				 return rowptrs[row];
	 return 0;
*/
//## end CnvImgStore::get%1615204215.body
}

void CnvImgStore::cpy( unsigned char *dest, int row )
{
//## begin CnvImgStore::cpy%-1310083220.body preserve=yes
/*
	 if( status == imgstoreOKAY )
			if( (row >= 0) && (row < rowcnt) )
				 memcpy( dest, rowptrs[row], rowbytes );
*/
//## end CnvImgStore::cpy%-1310083220.body
}

void CnvImgStore::cpy( unsigned char *dest, int row,
											 int col, int cnt )
{
//## begin CnvImgStore::cpy%-1550615876.body preserve=yes
/*
	 if( status == imgstoreOKAY )
			if( (row >= 0) && (row < rowcnt) )
				 memcpy( dest, rowptrs[row]+col, cnt );
*/
//## end CnvImgStore::cpy%-1550615876.body
}
//## begin module.additionalDeclarations preserve=yes

//................EMS Memory

/*
EmsImgStore::EmsImgStore( int nrows, int ncols, int nbits ) :
						 ImgStore( nrows, ncols, nbits )
{
	 if( EMS_installed() )
	 {
			// we use only 1 of the 4 physical pages
			// in the page frame buffer.  phypage
			// is set to desired page (0-3).
			phypage = 0;
			pgframe = EMS_pgframeaddr( phypage );

      // blklen is rowlen padded to multiple of 4.
		// blkcnt is number of padded rows that
      // fit in a 16K page.
      int n  = (rowbytes + 3) / 4;
      blklen = n * 4;
      blkcnt = 16384 / blklen;

      npages = (rowcnt + blkcnt - 1) / blkcnt;
      handle = EMS_alloc( npages );
		if( handle != -1 )
		{
         for( int i=0; i<npages; i++ )
				 {
            EMS_mappage( handle, i, phypage );
				memset( pgframe, 0, 16384 );
         }
      }
		else
				 status = imgstoreNOMEM;
   }
   else
		status = imgstoreNODRVR;
}

EmsImgStore::~EmsImgStore( )
{
   if( status == imgstoreOKAY )
      EMS_free( handle );
}

void EmsImgStore::put( unsigned char *data, int row )
{
	 if( status == imgstoreOKAY )
		if( (row >= 0) && (row < rowcnt) )
      {
         int page = row / blkcnt;
         EMS_mappage( handle, page, phypage );
			int ofs  = (row % blkcnt) * blklen;
				 memcpy( pgframe+ofs, data, rowbytes );
      }
}

unsigned char * EmsImgStore::get( int row )
{
	if( status == imgstoreOKAY )
      if( (row >= 0) && (row < rowcnt) )
      {
         int page = row / blkcnt;
         EMS_mappage( handle, page, phypage );
			int ofs  = (row % blkcnt) * blklen;
         return (unsigned char *) pgframe+ofs;
      }
	 return 0;
}

void EmsImgStore::cpy( unsigned char *dest, int row )
{
	if( status == imgstoreOKAY )
			if( (row >= 0) && (row < rowcnt) )
         memcpy( dest, get(row), rowbytes );
}

void EmsImgStore::cpy( unsigned char *dest, int row,
                       int col, int cnt )
{
   if( status == imgstoreOKAY )
      if( (row >= 0) && (row < rowcnt) )
         memcpy( dest, get(row)+col, cnt );
}
*/

//................XMS Memory

/*
XmsImgStore::XmsImgStore( int nrows, int ncols, int nbits ) :
             ImgStore( nrows, ncols, nbits )
{
	 if( XMS_installed() )
	{
		// blklen is rowlen padded to multiple of 4.
			int n  = (rowbytes + 3) / 4;
		blklen = n * 4;

		// allocate a cnv mem row buffer
		buffer = new char [blklen];
		if( buffer )
		{
			memset( buffer, 0, blklen );

			// total xms bytes required
			long nbytes = blklen; nbytes *= rowcnt;

			// convert to KB
			nbytes += 1023;
				 nbytes /= 1024;
			n = (int) nbytes;

				 // and attempt to allocate
				 handle = XMS_alloc( n );
				 if( handle != 0 )
				 {
						// set up move structs
						c2x.nbytes = blklen;
				c2x.srchandle = 0;
            c2x.srcoffset = (long) buffer;
            c2x.dsthandle = handle;
				c2x.dstoffset = 0;

            x2c.nbytes = blklen;
            x2c.srchandle = handle;
            x2c.srcoffset = 0;
				x2c.dsthandle = 0;
            x2c.dstoffset = (long) buffer;

						// zero the image
            for( int i=0; i<rowcnt; i++ )
				{
							 XMS_move( &c2x );
					c2x.dstoffset += blklen;
				}
				 }
         else
         {
				status = imgstoreNOMEM;
            delete buffer;
         }
		}
      else
         status = imgstoreNOMEM;
   }
	else
      status = imgstoreNODRVR;
}

XmsImgStore::~XmsImgStore( )
{
	if( status == imgstoreOKAY )
	 {
		delete buffer;
		XMS_free( handle );
	 }
}

void XmsImgStore::put( unsigned char *data, int row )
{
   if( status == imgstoreOKAY )
		if( (row >= 0) && (row < rowcnt) )
      {
         c2x.srcoffset = (long) data;
			c2x.dstoffset = long( blklen ) * row;
         XMS_move( &c2x );
      }
}

unsigned char * XmsImgStore::get( int row )
{
	if( status == imgstoreOKAY )
			if( (row >= 0) && (row < rowcnt) )
		{
			x2c.srcoffset = long( blklen ) * row;
			XMS_move( &x2c );
			return (unsigned char *) buffer;
      }
   return 0;
}

void XmsImgStore::cpy( unsigned char *dest, int row )
{
	if( status == imgstoreOKAY )
      if( (row >= 0) && (row < rowcnt) )
         memcpy( dest, get(row), rowbytes );
}

void XmsImgStore::cpy( unsigned char *dest, int row,
											 int col, int cnt )
{
	if( status == imgstoreOKAY )
			if( (row >= 0) && (row < rowcnt) )
			memcpy( dest, get(row)+col, cnt );
}
*/

//................Disk Memory

//## end module.additionalDeclarations
DskImgStore::DskImgStore( int nrows, int ncols, int nbits ) 
//## begin DskImgStore::DskImgStore%-381271234.initialization preserve=yes
:
				 ImgStore( nrows, ncols, nbits )
//## end DskImgStore::DskImgStore%-381271234.initialization
{

//## begin DskImgStore::DskImgStore%-381271234.body preserve=yes
/*
	// blklen is rowlen padded to multiple of 4.
	int n  = (rowbytes + 3) / 4;
	 blklen = n * 4;

	 // allocate a cnv mem row buffer
	 buffer = new char [blklen];
	 if( buffer )
	 {
			memset( buffer, 0, blklen );

		// initialize the disk file
			fstor = fopen( "IMGSTORE.MEM", "w+b" );
		if( fstor )
		{
			for( int i=0; i<nrows; i++ )
				 {
						fwrite( buffer, blklen, 1, fstor );
						if( ferror(fstor) )
						{
							 fclose( fstor );
					delete buffer;
							 status = imgstoreNODISK;
							 break;
						}
				 }
			}
			else
			{
				 delete buffer;
				 status = imgstoreNODISK;
		}
	 }
	else
		status = imgstoreNOMEM;
*/
//## end DskImgStore::DskImgStore%-381271234.body
}

DskImgStore::~DskImgStore( )
{
//## begin DskImgStore::~DskImgStore%-313281947.body preserve=yes
/*
	 if( status == imgstoreOKAY )
	{
		delete buffer;
			fclose( fstor );
	 }
*/
//## end DskImgStore::~DskImgStore%-313281947.body
}

void DskImgStore::put( unsigned char *data, int row )
{
//## begin DskImgStore::put%33367919.body preserve=yes
/*
	 if( status == imgstoreOKAY )
			if( (row >= 0) && (row < rowcnt) )
			{
			long offset = blklen;
				 offset *= row;
			fseek( fstor, offset, SEEK_SET );
			fwrite( (char *) data, blklen, 1, fstor );
		}
*/
//## end DskImgStore::put%33367919.body
}

unsigned char * DskImgStore::get( int row )
{
//## begin DskImgStore::get%1114832322.body preserve=yes
/*
	 if( status == imgstoreOKAY )
		if( (row >= 0) && (row < rowcnt) )
			{
				 long offset = blklen;
				 offset *= row;
				 fseek( fstor, offset, SEEK_SET );
				 fread( buffer, blklen, 1, fstor );
				 return (unsigned char *) buffer;
			}
	 return 0;
*/
//## end DskImgStore::get%1114832322.body
}

void DskImgStore::cpy( unsigned char *dest, int row )
{
//## begin DskImgStore::cpy%-1918260764.body preserve=yes
/*
	 if( status == imgstoreOKAY )
			if( (row >= 0) && (row < rowcnt) )
				 memcpy( dest, get(row), rowbytes );
*/
//## end DskImgStore::cpy%-1918260764.body
}

void DskImgStore::cpy( unsigned char *dest, int row,
											 int col, int cnt )
{
//## begin DskImgStore::cpy%1103766757.body preserve=yes
/*
	 if( status == imgstoreOKAY )
			if( (row >= 0) && (row < rowcnt) )
				 memcpy( dest, get(row)+col, cnt );
*/
//## end DskImgStore::cpy%1103766757.body
}





//................XMS Memory

//#include "xms.h"

XmsDes::XmsDes( int nbytes)
{
//## begin XmsDes::XmsDes%994936178.body preserve=yes
				 memset( buffer, 0, 4096 );
				 ptr = (char *)GlobalLock( handle = GlobalAlloc(GMEM_MOVEABLE,nbytes));
				 if( handle != 0 )
				 {
					status = OKAY;
					netlength = 0;
					memset(des_index_table,0,32*sizeof(Des_index_table));
					memset(ptr,0,nbytes);
				 }
				 else
					status = NOMEM;
//## end XmsDes::XmsDes%994936178.body
}

XmsDes::~XmsDes( )
{
//## begin XmsDes::~XmsDes%-1245726728.body preserve=yes
	if( status == OKAY )
	 {
		GlobalUnlock( handle);
      GlobalFree( handle );
//		mfarfree( handle );
	 }
//## end XmsDes::~XmsDes%-1245726728.body
}

int XmsDes::put( byte panel, byte point_type, int newlength )
{
//## begin XmsDes::put%-517218461.body preserve=yes
	long srcoffset, dstoffset, nbytes;
	if( status == OKAY )
		{
				int point_length = des_index_table[panel-1].des_length[point_type];
				int panel_length = des_index_table[panel-1].panel_length;

//      only for extended memory EMM
//				if(newlength%2)
//					buffer[newlength++] = 0;

				srcoffset = 0;
				for(int i=0; i<panel-1; i++)
					srcoffset += des_index_table[i].panel_length;
				for(i=0; i<=point_type; i++)
					srcoffset += des_index_table[panel-1].des_length[i];

				dstoffset = srcoffset + newlength-point_length;
				nbytes = netlength-srcoffset;

				memmove(ptr+dstoffset, ptr+srcoffset, nbytes);

				nbytes = newlength;
				dstoffset = srcoffset - des_index_table[panel-1].des_length[point_type];
				memmove(ptr+dstoffset, buffer, nbytes);

				des_index_table[panel-1].panel_length += newlength-point_length;
				des_index_table[panel-1].des_length[point_type] = newlength;
				netlength += newlength-point_length;

		}
//## end XmsDes::put%-517218461.body
}

char *XmsDes::get( byte panel, byte point_type )
{
//## begin XmsDes::get%-1834460603.body preserve=yes
	long srcoffset, dstoffset;
	unsigned nbytes;
	if( status == OKAY )
		{
				nbytes = des_index_table[panel-1].des_length[point_type];
				if( nbytes )
				{
				 srcoffset = 0;
				 for(int i=0; i<panel-1; i++)
					srcoffset += des_index_table[i].panel_length;
				 for(i=0; i<point_type; i++)
					srcoffset += des_index_table[panel-1].des_length[i];

				 memmove(buffer, ptr+srcoffset, nbytes);
				 return (char *)buffer;
				}
		}
	return 0;
//## end XmsDes::get%-1834460603.body
}

char *XmsDes::look_label(byte panel, byte point_type, byte num)
{
//## begin XmsDes::look_label%-131949839.body preserve=yes
 int n;
 int i;
 if( status == OKAY )
 {
  if(get(panel, point_type)!=NULL)
  {
	n=0;
	i=0;
	for(int k=0;k<num-1;k++)
	{
	  if(point_type!=AMON && point_type!=AY)
	  {
//	 n=buffer[i++];       //descriptor
//	 i += n;
		while(buffer[i++]);
//	 if(buffer[i-1])	i++;
	  }
	  while(buffer[i++]);
//	 if(buffer[i-1])	i++;
	}
	if(point_type!=AMON && point_type!=AY)
	{
//	 n=buffer[i++];
//	 i += n;
	 while(buffer[i++]);      //descriptor
//	 if(buffer[i-1])	i++;
	}
//	n=buffer[i++];
//	if(n)
	if(buffer[i])
	 return &buffer[i];
	else
	 return 0;
/* for(int i=0;i<32;i++)
 {
	for(j=0;j<DAY;j++)
	{
	 get(i+1, j);
	 for(k=0;k<des_index_table[i].des_length[j]
*/
  }
 }
 return 0;
//## end XmsDes::look_label%-131949839.body
}

char *XmsDes::islabel(char *token,int *num_point,byte *var_type,byte *point_type,int *num_panel)
{
//## begin XmsDes::islabel%1020230252.body preserve=yes
 int n,l,m;
 if( status == OKAY )
  for(int i=0;i<32;i++)
	for(int j=0;j<=AY;j++)
	{
//	 int m=point_des[j];
//	 if(m>=0)
	 m=j;
	 {
		get(i+1, m);
		n=0;
		l=0;
		for(int k=0;k<des_index_table[i].des_length[m];)
		{
			l++;
			if(m!=AMON && m!=AY)
			{
//				n=buffer[k++];  // descriptor
//				k += n;
					while(buffer[k++]);
//					if(buffer[k-1])	k++;
			}
//			n=buffer[k++];
//			if(n)
			if(buffer[k])
			{
				if(!strcmp(token,&buffer[k]))
				 {
					char point[21],x[5];
					*num_point=l;
					*point_type=j;
					*num_panel=i+1;
					 *var_type = LABEL_VAR;
					 itoa(*num_panel,point,10);
					 strcat(point,"-");
					 strcat(point,ptr_panel->info[j].name);
					 strcat(point,itoa(l,x,10));
					 strcpy(token,point);
					 return(&buffer[k]);
				 }
			}
			while(buffer[k++]);    //step over label
		}
	 }
	}
 return 0;
//## end XmsDes::islabel%1020230252.body
}

char *XmsDes::look_descriptor(byte panel, byte point_type, byte num)
{
//## begin XmsDes::look_descriptor%-1523684497.body preserve=yes
 int n;
 int i;
 if( status == OKAY )
 {
  if(get(panel, point_type)!=NULL)
  {
	n=0;
	i=0;
	for(int k=0;k<num-1;k++)
	{
	  if(point_type!=AMON && point_type!=AY)
	  {
		while(buffer[i++]);
	  }
	  while(buffer[i++]);
	}
//	if(point_type!=DAMON && point_type!=DAY)
//	{
//	 while(buffer[i++]);      //descriptor
//	}
	if(buffer[i])
	 return &buffer[i];
	else
	 return 0;
  }
 }
 return 0;
//## end XmsDes::look_descriptor%-1523684497.body
}
//## begin module.epilog preserve=yes


/*
void XmsDes::cpy( unsigned char *dest, int row )
{
	if( status == imgstoreOKAY )
		if( (row >= 0) && (row < rowcnt) )
			memcpy( dest, get(row), rowbytes );
}

void XmsImgStore::cpy( unsigned char *dest, int row,
											 int col, int cnt )
{
	if( status == imgstoreOKAY )
			if( (row >= 0) && (row < rowcnt) )
			memcpy( dest, get(row)+col, cnt );
}

*/

//................XMS Memory

/*
XmsMem::XmsMem(  )
{
	 if( XMS_installed() )
		{
		  memset(table,0,4*8);
		  status = NOUSE;
		  nitems = 0;
		 }
		else
		{
			status = NOMEM;
		}
}
XmsMem::XmsMem( unsigned long nbytes )
{
	 if( XMS_installed() )
	{
			// total xms bytes required
			// convert to KB
			nbytes += 1023;
			nbytes /= 1024;
			int n = (int) nbytes;

				 // and attempt to allocate
//				 handle = XMS_alloc( n );
				 if( handle != 0 )
				 {
				  memset(table,0,4*8);
				  status = OKAY;
				  nitems = 0;
				 }
				else
				{
					status = NOMEM;
				}
		}
		else
			status = NOMEM;
}

XmsMem::~XmsMem( )
{
	if( status == OKAY )
	 {
//	  ;
		XMS_free( handle );
	 }
}

void XmsMem::put( char *data , unsigned long l)
{
				c2x.nbytes = l;
				c2x.srchandle = 0;
//				c2x.srcoffset = (long)(((long)FP_SEG(data))*16+(long)FP_OFF(data));
				c2x.srcoffset = (long)data;
				c2x.dsthandle = handle;
				c2x.dstoffset = 0;
				if(nitems)
					c2x.dstoffset = table[nitems-1].offset+table[nitems-1].length;
			table[nitems].length = l;
			table[nitems].offset = c2x.dstoffset;
			nitems++;
         disable();
			XMS_move( &c2x );
			enable();

}

void XmsMem::get( int item , char *buffer)
{
	if( item < nitems )
		{
			x2c.nbytes = table[item].length;
			x2c.srchandle = handle;
			x2c.srcoffset = table[item].offset;
			x2c.dsthandle = 0;
			x2c.dstoffset = (long)buffer;
			disable();
			XMS_move( &x2c );
				 enable();
		}
}

void XmsMem::Save( int sx, int sy, int jx, int jy)
{
			int v;
			unsigned long big= ((unsigned long)(jx-sx)*(unsigned long)(jy-sy)*4+7)/8;
			unsigned long big1=big;
			big1 += 1023;
			big1 /= 1024;
			int n = (int) big1;
			if(n<26)
				v = 1;
			else
				v = 4;

			handle = XMS_alloc( n+4 );

			if(handle)
			{
			 status = OKAY;
			if(v==1)
			{
//			pixunder1=(char far *)farmalloc((unsigned long)big);
//			if(pixunder1==NULL) exit(0);
			mgetimage(sx, sy, jx, jy,pixunder1);
			put(pixunder1,big);
//			farfree(pixunder1);
			}
			else
			{
			int big1 = imagesize(sx, sy, jx, sy+(jy-sy)/4);
//			pixunder1=(char far *)farmalloc((unsigned long)big1);
			mgetimage(sx, sy, jx, sy+(jy-sy)/4,pixunder1);
			put(pixunder1,big1);
//			mfarfree(pixunder1);
			big1 = imagesize(sx, sy+(jy-sy)/4, jx, sy+(jy-sy)/2);
//			pixunder1=(char far *)farmalloc((unsigned long)big1);
			mgetimage(sx, sy+(jy-sy)/4,  jx,   sy+(jy-sy)/2,pixunder1);
			put(pixunder1,big1);
//			mfarfree(pixunder1);
			big1 = imagesize(sx, sy+(jy-sy)/2,jx, sy+3*(jy-sy)/4);
//			pixunder1=(char far *)farmalloc((unsigned long)big1);
			mgetimage(sx, sy+(jy-sy)/2, jx,  sy+3*(jy-sy)/4,pixunder1);
			put(pixunder1,big1);
//			mfarfree(pixunder1);
			big1 = imagesize(sx, sy+3*(jy-sy)/4, jx,jy);
//			pixunder1=(char far *)farmalloc((unsigned long)big1);
			mgetimage(sx,	 sy+3*(jy-sy)/4, 	 jx,  	 jy,pixunder1);
			put(pixunder1,big1);
//			farfree(pixunder1);
			}
			}
			else
			{
			 status=NOMEM;
			}
}

void XmsMem::Restore(int ltopx, int ltopy, int rbottomx, int rbottomy)
{
//			pixunder1=(char far *)farmalloc((unsigned long)table[0].length+1000);
			get( 0 , pixunder1);
			mputimage(ltopx,ltopy,pixunder1,COPY_PUT);
//			mfarfree(pixunder1);
			if(nitems!=1)
			{
//			pixunder1=(char far *)farmalloc((unsigned long)table[1].length);
			get( 1 , pixunder1);
			mputimage((int)ltopx,(int)(ltopy+(rbottomy-ltopy)/4),pixunder1,COPY_PUT);
//			mfarfree(pixunder1);
//			pixunder1=(char far *)farmalloc((unsigned long)table[2].length);
			get( 2 , pixunder1);
			mputimage((int)ltopx,(int)(ltopy+(rbottomy-ltopy)/2),pixunder1,COPY_PUT);
//			mfarfree(pixunder1);
//			pixunder1=(char far *)farmalloc((unsigned long)table[3].length);
			get( 3 , pixunder1);
			mputimage((int)ltopx,(int)ltopy+3*(rbottomy-ltopy)/4,pixunder1,COPY_PUT);
//			mfarfree(pixunder1);
			}
//			mfarfree(pixunder1);

	if( status == OKAY )
	 {
//		XMS_free( handle );
		nitems = 0;
//		status = NOUSE;
		memset(table,0,4*8);
	 }

}
*/
//## end module.epilog
