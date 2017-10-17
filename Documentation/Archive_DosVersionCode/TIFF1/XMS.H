//## begin module.cp preserve=yes
/*
 *   XMS.H - XMS Memory Interface Functions
 */

//## end module.cp
#ifndef _XMS_H_
#define _XMS_H_
//## begin module.additionalDeclarations preserve=yes
#define byte unsigned char

/*
 * note - this struct is packing sensitive!
 */

//## end module.additionalDeclarations
struct XMSmovestruct
{
   unsigned long  nbytes;
   unsigned short srchandle;
   unsigned long  srcoffset;
	unsigned short dsthandle;
   unsigned long  dstoffset;
};
//## begin XMSmovestruct.postscript preserve=yes

#if defined( __cplusplus )
extern "C" {
#endif

int       XMS_installed( void );
unsigned  XMS_alloc( int nKBytes );
void      XMS_free( unsigned XMShand );
int       XMS_move( XMSmovestruct *ms );

#if defined( __cplusplus )
}
#endif


typedef struct {
			unsigned des_length[12];
			unsigned panel_length;
			} Des_index_table;

//## end XMSmovestruct.postscript
class XmsDes {
	public:
		int status;
		HANDLE handle;     // xms handle
    char *ptr;
		int netlength;
		char buffer[4096];
		Des_index_table  des_index_table[32];
//		XMSmovestruct c2x;   // for move to xms
//		XMSmovestruct x2c;   // for move to cnv
//		XMSmovestruct x2x;   // for move to xms

	XmsDes(int nbytes);
	char *get(byte panel, byte point_type);
	int put(byte panel, byte point_type, int newlength);
	char *islabel(char *token, int *num_point,byte *var_type, byte *point_type,int *num_panel);
	char *look_label(byte panel, byte point_type, byte num);
	char *look_descriptor(byte panel, byte point_type, byte num);
	~XmsDes();

	
};


class XmsMem {
 public:
	int status;
	int nitems;
	struct {
	unsigned long offset;
	unsigned long length;
	
} table[4];
	unsigned handle;     // xms handle
	XMSmovestruct c2x;   // for move to xms
	XMSmovestruct x2c;   // for move to cnv

  XmsMem();
  XmsMem::XmsMem( unsigned long nbytes );
  ~XmsMem( );
  void get( int item , char *buffer);
  void put( char *data , unsigned long l);
  void Save( int sx, int sy, int jx, int jy);
  void Restore(int ltopx, int ltopy, int rbottomx, int rbottomy);
  
};

#endif 
