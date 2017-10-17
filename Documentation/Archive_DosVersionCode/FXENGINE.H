#ifndef _FXENGINE_H
#define _FXENGINE_H

#include <alloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <mem.h>


#define FXMAX_FILE 3         /* maxim open files */
#define FXMAX_FIELDS 30      /* maxim fields     */

/*    error codes               */
#define FX_NO_HANDLE_AVAILABLE 10
#define FX_OPEN_ERROR 11
#define FX_ERROR 12
#define FX_NO_FIELD 13
#define FX_EOF 14
#define FX_SUCCESS 0
/*    error codes               */

/*    open modes                */
#define READWRITE "rb+"
#define APPEND "r+b"
/*    open modes                */

typedef int FILEHANDLE;             /*  file handle         */
typedef int FIELDHANDLE;            /*  field handle        */
typedef unsigned long RECORDNUMBER; /*  record number type  */

//typedef struct {
//	 char field_name[11];       /*  field name   */
//	 char field_type;                 /*  field type   */
//	 unsigned long position;        /*  first byte of field in record */
//	 unsigned char l;           /*  field width  */
//	 unsigned char d;           /*  decimal width */
//	} FIELDSTRUCT ;
struct Header {
			unsigned char id;                /*    FOXPRO    */
			struct data {
				char da_year;       /*    current year    */
				char da_mon;        /*    month (1 = Jan) */
				char da_day;        /*    day             */
				} d;
			unsigned long int n_records;  /* file records number */
			unsigned int header_size;     /* file header size    */
			unsigned int record_size;     /* file record size    */
			char unknown[20];
			};                            /*  file header structure  */

struct FileInfo  {
			 struct Header header;
			 unsigned int fields_number;
			 };

struct FieldStruct {
			char field_name[11];           /*  field name     */
			char field_type;               /*  field type     */
			unsigned long position;        /*  first byte of field in record */
			unsigned char l;               /*  field width    */
			unsigned char d;               /*  number of decimal */
			char unknown[14];
			};                            /*  file record structure  */

struct CreateStruct  {
				char filedbf[64];
				unsigned int n_fields;
				struct FieldStruct field_struct[25];
				};

class HHeader
{
	protected:
	 struct Header header;        /*  file header structure  */

	public:
		void HSet(int nfields,struct FieldStruct *recstruct, int nrecords);
		int HNRecords(void) {return header.n_records;};
		int HHeaderSize(void) {return header.header_size;};
		int HRecordSize(void) {return header.record_size;};
		int HNRec(void) {return header.n_records;};
};

class RecordStruct {
 protected:
		struct FieldStruct  *Recstruct;             //
		HANDLE Recstruct_handle;
 public:

	 RecordStruct(){};
	 void RecStruct(int nfields, struct FieldStruct huge *recstruct);
	 struct FieldStruct *RecStruct(int nfield)
							 {
							 return Recstruct+(nfield-1);
							 };
	 ~RecordStruct();
};

/* for next declarations : array index = handle number      */

#ifdef MAIN

FILE *TblHandle[FXMAX_FILE];        /*  handle table             */
																		 /*  pointer to stream        */
char * TblRecBuf[FXMAX_FILE];        /*  record buffer table      */
HANDLE TblRecBuf_handle[FXMAX_FILE];
																		 /*  pointer to record buffer */
int    TblNrFields[FXMAX_FILE];      /*  number fields table      */
																		 /*  file fields number       */
struct Header TblHeader[FXMAX_FILE];        /*  file header structure  */

struct FieldStruct *TblRecStruct[FXMAX_FILE]; //[FXMAX_FIELDS];  /*  file record structure  */
HANDLE TblRecStruct_handle[FXMAX_FILE];

char xxxbuf[32];    /*  work buffer ; DON'T CHANGE THE SIZE !!! */

/*
extern  int FXOpen(char *file_name, FILEHANDLE *filehandle , char *mode);
extern  int FXCreate(char *file_name, int nfields, struct FieldStruct *recstruct, FILEHANDLE *filehandle);
extern  int FXFileInfo(FILEHANDLE filehandle, struct FileInfo *fileinfo);
extern  int FXGetRecStruct(FILEHANDLE filehandle, const struct FieldStruct **recstruct);
extern  int FXGetFieldInfo(FILEHANDLE filehandle, FIELDHANDLE fieldhandle,struct FieldStruct *fieldinfo);
extern  int FXNRecs(FILEHANDLE filehandle, RECORDNUMBER *record_numbers);
extern  int FXClose(FILEHANDLE filehandle);
extern  int FXGetRec(FILEHANDLE filehandle);
extern  int FXGetCopy(FILEHANDLE filehandle,char *record_buffer);
extern  int FXGotoRec(FILEHANDLE filehandle,RECORDNUMBER record_number);
extern  int FXFirstRec(FILEHANDLE filehandle);
extern  int FXLastRec(FILEHANDLE filehandle);
extern  int FXMoveEndFile(FILEHANDLE filehandle);
//extern int FXFldType(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, char *fldtype);
//extern "C" int FXFldName(FILEHANDLE, FIELDHANDLE fieldhandle, char *fldname);
extern  int FXNFields(FILEHANDLE hfile,int *fields_number);
extern  int FXFldSize(FILEHANDLE, FIELDHANDLE fieldhandle);
extern  char *FXFldName(FILEHANDLE, FIELDHANDLE fieldhandle);
extern  int FXFldHandle(FILEHANDLE, FIELDHANDLE *fieldhandle, char *fldname);
extern  int FXGetAlpha(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, int bufsize, char *dest);
extern  int FXGetInt(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, int *intptr);
extern  int FXGetLong(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, long *longptr);
extern  int FXGetFloat(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, float *floatptr);
extern  int FXGetDouble(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, double *doubleptr);
extern  int FXPutRec(FILEHANDLE filehandle);
extern  int FXPutCopy(FILEHANDLE filehandle, char *record_buffer);
extern  int FXPutAlpha(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, char *src);
extern  int FXPutInt(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, int value);
extern  int FXPutLong(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, long value);
extern  int FXPutDouble(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, double value);
*/
#endif
#ifdef FXENGINE

extern FILE * TblHandle[FXMAX_FILE];      /*  handle table             */
																					/*  pointer to stream        */
extern char * TblRecBuf[FXMAX_FILE];      /*  record buffer table      */
extern HANDLE TblRecBuf_handle[FXMAX_FILE];
																					/*  pointer to record buffer */
extern int    TblNrFields[FXMAX_FILE];    /*  number fields table      */
																					/*  file fields number       */
extern struct Header TblHeader[FXMAX_FILE];

extern struct FieldStruct *TblRecStruct[FXMAX_FILE]; //[FXMAX_FIELDS];
extern HANDLE TblRecStruct_handle[FXMAX_FILE];

extern char xxxbuf[32];    /*  work buffer  */

#else
extern  int FXOpen(char *file_name, FILEHANDLE *filehandle , char *mode);
extern  int FXCreate(char *file_name, int nfields, struct FieldStruct *recstruct, FILEHANDLE *filehandle);
extern  int FXFileInfo(FILEHANDLE filehandle, struct FileInfo *fileinfo);
extern  int FXGetRecStruct(FILEHANDLE filehandle, const struct FieldStruct **recstruct);
extern  int FXGetFieldInfo(FILEHANDLE filehandle, FIELDHANDLE fieldhandle,struct FieldStruct *fieldinfo);
extern  int FXNRecs(FILEHANDLE filehandle, RECORDNUMBER *record_numbers);
extern  int FXClose(FILEHANDLE filehandle);
extern  int FXGetRec(FILEHANDLE filehandle);
extern  int FXGetCopy(FILEHANDLE filehandle,char *record_buffer);
extern  int FXGotoRec(FILEHANDLE filehandle,RECORDNUMBER record_number);
extern  int FXFirstRec(FILEHANDLE filehandle);
extern  int FXLastRec(FILEHANDLE filehandle);
extern  int FXMoveEndFile(FILEHANDLE filehandle);
/*extern int FXFldType(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, char *fldtype);*/
//extern "C" int FXFldName(FILEHANDLE, FIELDHANDLE fieldhandle, char *fldname);
extern  int FXNFields(FILEHANDLE hfile,int *fields_number);
extern  int FXFldSize(FILEHANDLE, FIELDHANDLE fieldhandle);
extern  char *FXFldName(FILEHANDLE, FIELDHANDLE fieldhandle);
extern  int FXFldHandle(FILEHANDLE, FIELDHANDLE *fieldhandle, char *fldname);
extern  int FXGetAlpha(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, int bufsize, char *dest);
extern  int FXGetInt(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, int *intptr);
extern  int FXGetLong(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, long *longptr);
extern  int FXGetFloat(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, float *floatptr);
extern  int FXGetDouble(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, double *doubleptr);

extern  int FXPutRec(FILEHANDLE filehandle);
extern  int FXPutCopy(FILEHANDLE filehandle, char *record_buffer);
extern  int FXPutAlpha(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, char *src);
extern  int FXPutInt(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, int value);
extern  int FXPutLong(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, long value);
extern  int FXPutDouble(FILEHANDLE filehandle, FIELDHANDLE fieldhandle, double value);
#endif
#endif
/*      functions prototypes              */


