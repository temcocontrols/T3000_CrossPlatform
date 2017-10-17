// gcvt
#define  FXENGINE

#include <windows.h>
#include <dos.h>
#include <stdio.h>
#include <string.h>
#include <alloc.h>
#include <process.h>
#include <stdlib.h>

#include "fxengine.h"

extern void mfarfree(HANDLE handle);
extern void mfarmalloc(char far **far_point, unsigned long nbytes, HANDLE& handle);

int FXMoveEndFile(FILEHANDLE hfile);
int FXEof(FILEHANDLE hfile);

/**************  open file function  ************
		entry:  char *dbfFile = pointer to dbf name
			char *mode = open mode : READWRITE , APPEND
		exit:   open the file dbfFile and return file handle
*************************************************/

int FXOpen(char *dbfFile, FILEHANDLE *hfile, char *mode)
{
 int h;
 for(h=0; h < FXMAX_FILE; h++)
		{
		 if (!TblHandle[h])
				 break;
		}
 if (h>FXMAX_FILE)
		 return(FX_NO_HANDLE_AVAILABLE);
 if ((TblHandle[h] =  fopen(dbfFile, mode)) == NULL )
		{
//		printf(" FXENGINE Open function %s",sys_errlist[errno]);
		return(FX_OPEN_ERROR) ;
		};
 fread(&TblHeader[h], sizeof(TblHeader[0]), 1,TblHandle[h]);
 fseek(TblHandle[h], 32, SEEK_SET);
 mfarmalloc((char far **)&TblRecStruct[h] , sizeof(struct FieldStruct)*FXMAX_FIELDS, TblRecStruct_handle[h]);
 if (TblRecStruct[h] == NULL)
// if ((TblRecStruct[h] =  farmalloc(sizeof(struct FieldStruct)*FXMAX_FIELDS)) == NULL)
	{
	 printf("FXENGINE Not enough memory to allocate TblRecStruct\n");
	 exit(2);  /* terminate program if out of memory */
	}
 fread(xxxbuf, sizeof(xxxbuf), 1,TblHandle[h]);
 while (xxxbuf[0] != '\x0d')
	 {
	 TblNrFields[h]++;
	 memcpy(&TblRecStruct[h][TblNrFields[h]-1],xxxbuf,sizeof(TblRecStruct[0][0]));
	 fread(xxxbuf, sizeof(xxxbuf), 1,TblHandle[h]);
	 }
	mfarmalloc((char far **)&TblRecBuf[h], TblHeader[h].record_size , TblRecBuf_handle[h]);
	if (TblRecBuf[h] == NULL)
//	if ((TblRecBuf[h] =  farmalloc(TblHeader[h].record_size)) == NULL)
	{
	 printf("FXENGINE Not enough memory to allocate TblRecBuf\n");
	 exit(1);  /* terminate program if out of memory */
	}
 memset(TblRecBuf[h],'\x20',TblHeader[h].record_size);
 TblRecBuf[h][0]='\x20';
 *hfile = h+1;
 if (!strcmp(mode,READWRITE))
	 fseek(TblHandle[h], TblHeader[h].header_size, SEEK_SET);
 if (!strcmp(mode,APPEND))
         FXMoveEndFile(h+1);
 return(FX_SUCCESS);
}


/**************  file info function  ************
		entry:  hfile = file handle
		exit:   fill out FileInfo structure
*************************************************/

int FXFileInfo(FILEHANDLE hfile, struct FileInfo *fileinfo)
{
 memcpy(fileinfo, &TblHeader[hfile-1], sizeof(struct Header));
 fileinfo->fields_number=TblNrFields[hfile-1];
}

/**************  record structure function  ************
		entry:  hfile = file handle
		exit:   pointer to record structure
*************************************************/

int FXGetRecStruct(FILEHANDLE hfile, const struct FieldStruct **recstruct)
{
 *recstruct=TblRecStruct[hfile-1];
}

/**************  field info function  ************
		entry:  hfile = file handle
						hfield = field handle
		exit:   fill out FieldStruct structure
*************************************************/

int FXGetFieldInfo(FILEHANDLE hfile, FIELDHANDLE hfield,struct FieldStruct *fieldinfo)
{
 memcpy(fieldinfo, &TblRecStruct[hfile-1][hfield-1],sizeof(struct FieldStruct));
}

/********  number of records function  **********
		entry    hfile = file handle
		 exit:   number of records from file
*************************************************/

int FXNRecs(FILEHANDLE hfile, RECORDNUMBER *nrecptr)
{
 return(*nrecptr = TblHeader[hfile-1].n_records);
}

/************  get record function  *************
		entry    hfile = file handle
*************************************************/

int FXGetRec(FILEHANDLE hfile)
{
 if (FXEof(hfile))
		return FX_EOF;
 fread(TblRecBuf[hfile-1],TblHeader[hfile-1].record_size,1,TblHandle[hfile-1]);
 return FX_SUCCESS;
}

/************   eof function  *************
		entry    hfile = file handle
*************************************************/
int FXEof(FILEHANDLE hfile)
{
if (ftell(TblHandle[hfile-1]) >= (TblHeader[hfile-1].header_size+TblHeader[hfile-1].n_records*TblHeader[hfile-1].record_size))
		return FX_EOF;
else
	 return FX_SUCCESS;
}

/********  number of records function  **********
		entry    hfile = file handle
		 exit:   copy of record buffer in call progam
*************************************************/

int FXGetCopy(FILEHANDLE hfile,char  *recptr)
{
 memcpy(recptr, TblRecBuf[hfile-1], TblHeader[hfile-1].record_size);
}

/*************  go to  function  ***************
		entry    hfile = file handle
		 exit:   positions the file pointer to record number nrec
*************************************************/

int FXGotoRec(FILEHANDLE hfile, RECORDNUMBER nrec)
{
 fseek(TblHandle[hfile-1], TblHeader[hfile-1].header_size+(nrec-1)*TblHeader[hfile-1].record_size, SEEK_SET);
}

/********  number of records function  **********
		entry    hfile = file handle
		 exit:   positions the file pointer to first record
*************************************************/

int FXFirstRec(FILEHANDLE hfile)
{
 fseek(TblHandle[hfile-1], TblHeader[hfile-1].header_size, SEEK_SET);
}

/********  number of records function  **********
		entry    hfile = file handle
		 exit:   positions the file pointer to last record
*************************************************/

int FXLastRec(FILEHANDLE hfile)
{
 fseek(TblHandle[hfile-1], TblHeader[hfile-1].header_size+(TblHeader[hfile-1].n_records-1)*TblHeader[hfile-1].record_size, SEEK_SET);
}

/********  number of records function  **********
		entry    hfile = file handle
		 exit:   positions the file pointer to end of file
*************************************************/

int FXMoveEndFile(FILEHANDLE hfile)
{
 fseek(TblHandle[hfile-1], TblHeader[hfile-1].header_size+TblHeader[hfile-1].n_records*TblHeader[hfile-1].record_size, SEEK_SET);
}

/***************  close function  **************
		entry    hfile = file handle
		 exit:   close the file
*************************************************/

int FXClose(FILEHANDLE hfile)
{
 fflush(TblHandle[hfile-1]);
 fseek(TblHandle[hfile-1],0,SEEK_SET);
 fwrite(&TblHeader[hfile-1], sizeof(TblHeader[0]), 1,TblHandle[hfile-1]);
 fseek(TblHandle[hfile-1],0,SEEK_END);
 fputc(0x1A,TblHandle[hfile-1]);
 fclose(TblHandle[hfile-1]);
 mfarfree(TblRecBuf_handle[hfile-1]);
 mfarfree(TblRecStruct_handle[hfile-1]);
 TblNrFields[hfile-1]=0;
 TblHandle[hfile-1]=0;
}

/***********  field type  function  ************
		entry    hfile = file handle
			 hfield = field handle
		 exit:   field name, type, and width
*************************************************/

/*
int FXFldType(FILEHANDLE hfile, FIELDHANDLE hfield, FIELDTYPE *fldtype)
{
 strcpy(fldtype, TblRecStruct[hfile-1][hfield-1].field_name) ;
 memcpy(fldtype+11, &TblRecStruct[hfile-1][hfield-1].field_type,1) ;
 memcpy(fldtype+12, &TblRecStruct[hfile-1][hfield-1].l,2);
}
*/

/***********  field name function  *************
		entry    hfile = file handle
			 hfield = field handle
		 exit:   field name
*************************************************/

//int FXFldName(FILEHANDLE hfile, FIELDHANDLE hfield, char *fldname)
char *FXFldName(FILEHANDLE hfile, FIELDHANDLE hfield)
{
// strcpy(fldname,TblRecStruct[hfile-1][hfield-1].field_name);
 return(TblRecStruct[hfile-1][hfield-1].field_name);
}


/***********  fields number function  *************
		entry    hfile = file handle
		 exit		 fields_number
*************************************************/
int	FXNFields(FILEHANDLE hfile,int *fields_number)
{
 *fields_number = TblNrFields[hfile-1];
}


/***********  field size function  *************
		entry    hfile = file handle
			 hfield = field handle
		 exit:   field size
*************************************************/

int FXFldSize(FILEHANDLE hfile, FIELDHANDLE hfield)
{
// strcpy(fldname,TblRecStruct[hfile-1][hfield-1].field_name);
 return(TblRecStruct[hfile-1][hfield-1].l);
}

/***********  field handle function  ************
		entry    hfile = file handle
			 fldname = field name
		 exit:   field handle
*************************************************/

int FXFldHandle(FILEHANDLE hfile, FIELDHANDLE *hfield, char *fldname)
{
int h;
for(h=0; h<TblNrFields[hfile-1]; h++)
	if ( !strcmp(TblRecStruct[hfile-1][h].field_name,fldname))
				 break;
if (h==TblNrFields[hfile-1])
		return(FX_NO_FIELD);
*hfield=h+1;
return(FX_SUCCESS);
}


/***********  get alpha  function  ************
		entry    hfile = file handle
			 hfield = field handle
			 bufsize = number of characters
		 exit:   return a string of 'bufsize' characters
*************************************************/

int FXGetAlpha(FILEHANDLE hfile, FIELDHANDLE hfield, int bufsize, char *dest)
{
 if (bufsize <= TblRecStruct[hfile-1][hfield-1].l)
	 {
		memcpy(dest, &TblRecBuf[hfile-1][TblRecStruct[hfile-1][hfield-1].position],bufsize);
		dest[bufsize]='\0';
	 }
 else
	 {
		memcpy(dest, &TblRecBuf[hfile-1][TblRecStruct[hfile-1][hfield-1].position],TblRecStruct[hfile-1][hfield-1].l);
		dest[TblRecStruct[hfile-1][hfield-1].l]='\0';
	 }
}

/***********  get int  function  ************
		entry    hfile = file handle
			 hfield = field handle
		 exit:   return a int value from the field
*************************************************/

int FXGetInt(FILEHANDLE hfile, FIELDHANDLE hfield, int *intptr)
{
 char xxxtmp[20];
 memcpy(xxxtmp, &TblRecBuf[hfile-1][TblRecStruct[hfile-1][hfield-1].position],TblRecStruct[hfile-1][hfield-1].l);
 xxxtmp[TblRecStruct[hfile-1][hfield-1].l]='\0';
 *intptr=atoi(xxxtmp);
}


/***********  get long function  ************
		entry    hfile = file handle
			 hfield = field handle
		 exit:   return a long value from the field
*************************************************/

int FXGetLong(FILEHANDLE hfile, FIELDHANDLE hfield, long *longptr)
{
 char xxxtmp[20];
 memcpy(xxxtmp, &TblRecBuf[hfile-1][TblRecStruct[hfile-1][hfield-1].position],TblRecStruct[hfile-1][hfield-1].l);
 xxxtmp[TblRecStruct[hfile-1][hfield-1].l]='\0';
 *longptr=atol(xxxtmp);
}


/***********  get float function  ************
		entry    hfile = file handle
	     hfield = field handle
		 exit:   return a float value from the field
*************************************************/

int FXGetFloat(FILEHANDLE hfile, FIELDHANDLE hfield, float *floatptr)
{
 char xxxtmp[20];
 memcpy(xxxtmp, &TblRecBuf[hfile-1][TblRecStruct[hfile-1][hfield-1].position],TblRecStruct[hfile-1][hfield-1].l);
 xxxtmp[TblRecStruct[hfile-1][hfield-1].l]='\0';
#ifndef NOMATH
 *floatptr = (float) atof(xxxtmp);
#else
 *floatptr = 0;
#endif
}

/***********  get double function  ************
		entry    hfile = file handle
			 hfield = field handle
		 exit:   return a double value from the field
*************************************************/

int FXGetDouble(FILEHANDLE hfile, FIELDHANDLE hfield, double *doubleptr)
{
 char xxxtmp[20];
 memcpy(xxxtmp, &TblRecBuf[hfile-1][TblRecStruct[hfile-1][hfield-1].position],TblRecStruct[hfile-1][hfield-1].l);
 xxxtmp[TblRecStruct[hfile-1][hfield-1].l]='\0';
#ifndef NOMATH
 *doubleptr = atof(xxxtmp);
#else
 *doubleptr = 0;
#endif
}

int FXCreate(char *dbffile, int nfields, struct FieldStruct *recstruct, FILEHANDLE *hfile)
{
 struct date d;
 int h, i,e,n;
 for(h=0; h < FXMAX_FILE; h++)
		{
		 if (!TblHandle[h])
				 break;
		}
 if (h>FXMAX_FILE)
		 return(FX_NO_HANDLE_AVAILABLE);
 if ((TblHandle[h] =  fopen(dbffile, "wb+")) == NULL )
		{
//		printf(" FXENGINE Open function %s",sys_errlist[errno]);
		return(FX_OPEN_ERROR) ;
		};
 TblNrFields[h] = nfields;

	mfarmalloc((char far **)&TblRecStruct[h], sizeof(struct FieldStruct)*FXMAX_FIELDS, TblRecStruct_handle[h] );
	if (TblRecStruct[h] == NULL)
//	if ((TblRecStruct[h] =  farmalloc(sizeof(struct FieldStruct)*FXMAX_FIELDS)) == NULL)
	{
	 printf("FXENGINE Not enough memory to allocate TblRecStruct\n");
   exit(2);  /* terminate program if out of memory */
  }

 memcpy(TblRecStruct[h], recstruct, nfields*32);

 getdate(&d);
 TblHeader[h].id = 0x03;
 TblHeader[h].d.da_year = d.da_year % 100;
 TblHeader[h].d.da_mon = d.da_day ;
 TblHeader[h].d.da_day = d.da_mon ;

 TblHeader[h].n_records = 0 ;

 TblHeader[h].header_size = 32 + nfields*32 + 1 ;

 TblHeader[h].record_size = 0 ;

 n=1;
 for(i=0; i<nfields ; i++)
	 {
		TblHeader[h].record_size += TblRecStruct[h][i].l ;
		TblRecStruct[h][i].position = n;
		n += TblRecStruct[h][i].l;
	 };
 (TblHeader[h].record_size)++;

 fwrite(&TblHeader[h], sizeof(TblHeader[0]), 1,TblHandle[h]);
 for(i=0; i<nfields ; i++)
		 n=fwrite(&TblRecStruct[h][i], sizeof(struct FieldStruct), 1,TblHandle[h]);

 fputc(0x0d,TblHandle[h]);
 fputc(0x1A,TblHandle[h]);
 mfarmalloc((char far **)&TblRecBuf[h], TblHeader[h].record_size, TblRecBuf_handle[h]);
 if (TblRecBuf[h] == NULL)
// if ((TblRecBuf[h] =  farmalloc(TblHeader[h].record_size)) == NULL)
	{
	 printf("Not enough memory to allocate buffer\n");
	 exit(1);  /* terminate program if out of memory */
	}
 memset(TblRecBuf[h],'\x20',TblHeader[h].record_size);
 TblRecBuf[h][0]='\x20';
 *hfile = h+1;
 return(FX_SUCCESS);
}

int FXPutRec(FILEHANDLE hfile)
{
 fwrite(TblRecBuf[hfile-1],TblHeader[hfile-1].record_size,1,TblHandle[hfile-1]);
 (TblHeader[hfile-1].n_records)++;
 memset(TblRecBuf[hfile-1],'\x20',TblHeader[hfile-1].record_size);
 TblRecBuf[hfile-1][0]='\x20';
}

int FXPutCopy(FILEHANDLE hfile, char *recptr)
{
 memcpy(TblRecBuf[hfile-1], recptr, TblHeader[hfile-1].record_size);
}

int FXPutAlpha(FILEHANDLE hfile, FIELDHANDLE hfield,  char *src)
{
 int bufsize;
 bufsize=strlen(src);
 memset(&TblRecBuf[hfile-1][TblRecStruct[hfile-1][hfield-1].position], '\x20',TblRecStruct[hfile-1][hfield-1].l);
 if ( bufsize <= TblRecStruct[hfile-1][hfield-1].l )
	 {
		memcpy(&TblRecBuf[hfile-1][TblRecStruct[hfile-1][hfield-1].position], src, bufsize);
	 }
 else
	 {
		memcpy(&TblRecBuf[hfile-1][TblRecStruct[hfile-1][hfield-1].position], src, TblRecStruct[hfile-1][hfield-1].l);
	 }
}

int FXPutInt(FILEHANDLE hfile, FIELDHANDLE hfield, int value)
{
 int n;
 char xxxtmp[20];
 memset(&TblRecBuf[hfile-1][TblRecStruct[hfile-1][hfield-1].position],'\x20',TblRecStruct[hfile-1][hfield-1].l);
 itoa(value, xxxtmp, 10);
 n=strlen(xxxtmp);
 if (n <= TblRecStruct[hfile-1][hfield-1].l)
		memcpy(&TblRecBuf[hfile-1][TblRecStruct[hfile-1][hfield-1].position+TblRecStruct[hfile-1][hfield-1].l-n],xxxtmp,n);
 else
		memcpy(&TblRecBuf[hfile-1][TblRecStruct[hfile-1][hfield-1].position],xxxtmp,TblRecStruct[hfile-1][hfield-1].l);
}

int FXPutLong(FILEHANDLE hfile, FIELDHANDLE hfield, long value)
{
 int n;
 char xxxtmp[20];
 memset(&TblRecBuf[hfile-1][TblRecStruct[hfile-1][hfield-1].position],'\x20',TblRecStruct[hfile-1][hfield-1].l);
 ltoa(value, xxxtmp, 10);
 n=strlen(xxxtmp);
 if (n <= TblRecStruct[hfile-1][hfield-1].l)
		memcpy(&TblRecBuf[hfile-1][TblRecStruct[hfile-1][hfield-1].position+TblRecStruct[hfile-1][hfield-1].l-n],xxxtmp,n);
 else
		memcpy(&TblRecBuf[hfile-1][TblRecStruct[hfile-1][hfield-1].position],xxxtmp,TblRecStruct[hfile-1][hfield-1].l);
}

int FXPutDouble(FILEHANDLE hfile, FIELDHANDLE hfield, double value)
{
 int n,n1;
 char xxxtmp[20],*p,c;
 memset(&TblRecBuf[hfile-1][TblRecStruct[hfile-1][hfield-1].position],'\x20',TblRecStruct[hfile-1][hfield-1].l);
#ifndef NOMATH
 gcvt(value, TblRecStruct[hfile-1][hfield-1].l-1, xxxtmp);
 c='e';
 if (strchr(xxxtmp,c)!=NULL)
		gcvt(0, TblRecStruct[hfile-1][hfield-1].l-1, xxxtmp);
 if (strlen(xxxtmp)<= TblRecStruct[hfile-1][hfield-1].l)
	{
	n=TblRecStruct[hfile-1][hfield-1].l;
	c='.';
	if ((p=strchr(xxxtmp, c))!=NULL)
	 if (strlen(p+1)>TblRecStruct[hfile-1][hfield-1].d)
			 p[TblRecStruct[hfile-1][hfield-1].d+1]='\0';
	n1=strlen(xxxtmp);
	for(c=n1; c>=0 ; c--)
			xxxtmp[n--]=xxxtmp[c];
	for(c=0;c<TblRecStruct[hfile-1][hfield-1].l-n1; c++)
			xxxtmp[c]='\x20';
	}
#else
	memset(xxxtmp,' ',TblRecStruct[hfile-1][hfield-1].l);
#endif

// if (n <= TblRecStruct[hfile-1][hfield-1].l)
//		memcpy(&TblRecBuf[hfile-1][TblRecStruct[hfile-1][hfield-1].position+TblRecStruct[hfile-1][hfield-1].l-n],xxxtmp,n);
//	else
	memcpy(&TblRecBuf[hfile-1][TblRecStruct[hfile-1][hfield-1].position],xxxtmp,TblRecStruct[hfile-1][hfield-1].l);
}

