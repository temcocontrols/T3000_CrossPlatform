 #include <stdio.h>

 #define IMPOTENT					32767
 #define	MENU_MAIN    			0
 #define MENU_FILE			   100
 #define MENU_SETUP           200
 #define	MENU_HARDWARE        300
 #define BORDER_LETTER        "() \r\n\0" 


//  ********  the function  of T3000hlp.cpp  ********
 extern void T3000help(int Context_number);
 extern void Init_help(void);
 extern int Key_word_convert(char far *Key_word);

//  ********  the function from other file  ******** 
 extern char wingets_help(int Flag_help,char far *ptr, int row, int col, int width,
				 int bkgnd, int frgnd, char which_type='A', char *sablon=NULL, char retnokey = 0);
 extern int ReadWindow_help(int Flag_help,int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							 int bkgndreadcolor, int readcolor, char *text, char *buf, int width, char *sablon=NULL);
 extern int ReadYesNo_help(int Flag_help,int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							int bkgndrreadcolor, int readcolor, char *text, char yes='Y', char no='N', char s=0);
 extern int ReadYesNoButton_help(int Flag_help,int x1, int y1, int x2, int y2, int bkgnd, int tcolor, int frgnd,
							int bkgndrreadcolor, int readcolor, char *text, char *yes, char *no,
							char okchar='O', char cancelchar='C', char xok=3, char xcancel=1);
 extern void getpassword_help(int Flag_help,char *pass, char *text);

