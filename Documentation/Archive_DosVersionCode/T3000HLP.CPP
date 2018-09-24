 #include <graphics.h>
 #include <stdio.h>
 #include <string.h>
 #include <dir.h>
 #include "gwin.h"

// ************************************
// ********  The key for need  ********
// ********        begin       ********
// ************************************

 #define PGDN 81
 #define PGUP 73
 #define RIGHT 77
 #define LEFT 75
 #define HOME 71
 #define ENDKEY 79
 #define UP 72
 #define DOWN 80
 #define INSERT  82
 #define DELETE  83
 #define ENTER  13
 #define ESC  27
 #define ALT   0x08
 #define CTRL  0x04

 #define F1KEY  59
 #define F2KEY  60
 #define F3KEY  61
 #define F4KEY  62
 #define F5KEY  63
 #define F6KEY  64
 #define F7KEY  65
 #define F8KEY  66
 #define F9KEY  67
 #define F10KEY  68
 #define F11KEY  69
 #define F12KEY  70

// ************************************
// ********  The key for need  ********
// ********         end        ********
// ************************************



// ************************************************
// ********  The function from other file  ********
// ********             begin              ********
// ************************************************

 extern int bioskey_new(int cmd);
 extern void movetoxy(int x, int y);

// ************************************************
// ********  The function from other file  ********
// ********              end               ********
// ************************************************




// ********************************************
// ********  The data from other file  ********
// ********           begin            ********
// ********************************************

 extern int Black;                 //0
 extern int Blue;                   //1
 extern int Green;                 //2
 extern int Cyan;                   //3
 extern int Darkgray;           //8
 extern int White;                 //15
 extern int Green1;   //13
 extern int Lightgray;         //7
 extern int Red;                     //4
 extern int Lightblue;         //9
 extern int Lightgreen;       //10
 extern int Lightcyan;         //11
 extern int Lightred;           //12
 extern int Yellow;               //14
 extern int Blue1;


 extern int mode_text;

// ********************************************
// ********  The data from other file  ********
// ********            end             ********
// ********************************************



// ****************************************
// ********    The private data    ********
// ********         begin          ********
// ****************************************

 #define CONTINUE_HELP  1
 #define EXIT_HELP      0

 #define FLAG_CONTEXT   35
 #define FLAG_TITLE     36

 #define WIN_LENGTH     50
 #define WIN_HIGH       14
 #define WORD_WIDE      9
 #define WORD_HIGH      18

 #define FLAG_PAGE_BREAK	"@"
 #define SPACE        		32          // " "
 #define FLAG_CHANGE_LINE	10
 #define FLAG_END_LINE		0
 #define TAB_KEY				9

 #define COLOR_LETTER_TEXT     	Lightblue
 #define COLOR_BACK_TEXT			White
 #define COLOR_LETTER_GRAPH      BLUE
 #define COLOR_BACK_GRAPH        White

 #define CLICK_FIRST       		1
 #define CLICK_CONTINUE    		0
 #define WAITE_OF_CLICK_FIRST		1000

 #define IMPOTENT               32767

 struct Text_line
 {
	char Text_string[WIN_LENGTH+1];
	Text_line far *Previous;
	Text_line far *Next;
	int 	Location;
 };

 struct MAP_array
 {
	int context_number;
	char context_string[21];
 };
 // ********  public var  ********
 struct MAP_array map_array[200];
 int max_map_array;       // the number of map_array;
 int max_text_chain;      // the number of Text_line;
 char directory_help[80];
// ****************************************
// ********    The private data    ********
// ********          end           ********
// ****************************************




// ****************************************
// ********  The private function  ********
// ********         begin          ********
// ****************************************

 GWindow				  		*T3000_help_initialize();
 void 						Search_context_string(FILE *Help_file,char far *Context_string);
 char far  					*Search_context_number(int Context_number);
 struct Text_line far 	*Build_text_chain(FILE *Help_file);
// void 						Handle_key_press(char Key_press);
 int  						Judge_page_break(char far *String);
 void 						Text_display(GWindow *T3000_help,struct Text_line far *Win_top_line);
 void 						Change_text_line_array(char far *String_array);
 void 						Handle_key_press(GWindow *T3000_help,struct Text_line far *First_line);
 char far *Get_words(FILE *Help_file,char String_array[WIN_LENGTH+2]);
 int							Key_word_convert(char far *Key_word);
// ****************************************
// ********  The private function  ********
// ********          end           ********
// ****************************************

 void Init_help(void)
 {
	FILE *Help_file;
	char String_array[200];
	char far *String_temporary;
	int Counter_map_array;
	int Counter_letter;

	max_map_array=0;
	Counter_map_array=0;
	getcwd(directory_help,80);
	Help_file=fopen("T3000hlp.hlp","rt");
	if ((Help_file!=NULL)&&(!feof(Help_file)))
	{
		String_temporary=fgets(String_array,200,Help_file);
		while (!Judge_page_break(String_temporary))
		{
			if (strlen(String_temporary)<=2)
			{
				max_map_array=0;
				fclose(Help_file);
				return;
			}
			if (_fstrpbrk(" 1234567890",String_temporary)==NULL)
			{
				max_map_array=0;
				fclose(Help_file);
				return;
			}
			Counter_letter=0;
			while ((String_temporary[Counter_letter]!=SPACE)&&(String_temporary[Counter_letter]!=TAB_KEY))
			{
				map_array[Counter_map_array].context_string[Counter_letter]=String_temporary[Counter_letter];
				Counter_letter++;
			}
			map_array[Counter_map_array].context_string[Counter_letter]=FLAG_END_LINE;
			while ((String_temporary[Counter_letter]==SPACE)||(String_temporary[Counter_letter]==TAB_KEY))
			{
				Counter_letter++;
			}
			map_array[Counter_map_array].context_number=0;
			while ((String_temporary[Counter_letter]>=48)&&(String_temporary[Counter_letter]<=57)) //  "0"<  <"9"
			{
				map_array[Counter_map_array].context_number=map_array[Counter_map_array].context_number*10+((int)String_temporary[Counter_letter]-48);
				Counter_letter++;
			}
			Counter_map_array++;
			if (feof(Help_file))
			{
				max_map_array=0;
				fclose(Help_file);
				return;
			}
			else
			{
				String_temporary=fgets(String_array,200,Help_file);
			}
		}
		max_map_array=Counter_map_array;
	}
	fclose(Help_file);
 }

// ***************************************************
 void T3000help(int Context_number)
 {
	FILE *Help_file;                    // point to help file
	char far *Context_string;
	struct Text_line far *First_line, *p;
	char directory_current[80];
// ***********************************
// ********  Help Initialize  ********
// ********       begin       ********
// ***********************************
	if (Context_number==IMPOTENT)
	{
		return;
	}
	GWindow *T3000_help=T3000_help_initialize();
	getcwd(directory_current,80);
	chdir(directory_help);
	Help_file=fopen("T3000hlp.hlp","rt");
// ***********************************
// ********  Help Initialize  ********
// ********        end        ********
// ***********************************
	if (Help_file!=NULL)
	{
		if (max_map_array==0)
		{
			if (mode_text)
			{
				T3000_help->GWPuts(2,8,"            Sorry !",COLOR_LETTER_TEXT,COLOR_BACK_TEXT);
				T3000_help->GWPuts(4,5," The form of T3000hlp.hlp isn't correct !",COLOR_LETTER_TEXT,COLOR_BACK_TEXT);
			}
			else
			{
				T3000_help->GWPuts(2,8,"            Sorry !",COLOR_LETTER_GRAPH,COLOR_BACK_GRAPH);
				T3000_help->GWPuts(4,5," The form of T3000hlp.hlp isn't correct !",COLOR_LETTER_GRAPH,COLOR_BACK_GRAPH);
			}
			while(!(T3000_help->HandleEvent()));
		}
		else
		{
			Context_string=Search_context_number(Context_number);
			if (Context_string==NULL)
			{
				if (mode_text)
				{
					T3000_help->GWPuts(2,8,"            Sorry !",COLOR_LETTER_TEXT,COLOR_BACK_TEXT);
					T3000_help->GWPuts(4,5," The context_number isn't correct !",COLOR_LETTER_TEXT,COLOR_BACK_TEXT);
				}
				else
				{
					T3000_help->GWPuts(2,8,"            Sorry !",COLOR_LETTER_GRAPH,COLOR_BACK_GRAPH);
					T3000_help->GWPuts(4,5," The context_number isn't correct !",COLOR_LETTER_GRAPH,COLOR_BACK_GRAPH);
				}
				while(!(T3000_help->HandleEvent()));
			}
			else
			{
				Search_context_string(Help_file,Context_string);
				if (!feof(Help_file))
				{
					First_line=Build_text_chain(Help_file);
					Handle_key_press(T3000_help,First_line); // need use test_chain
// ***********************************
// ********      Adi          ********
// ********  Aug 13,1997      ********
// ********       begin       ********
// ***********************************
					while( First_line )
					{
						 p = First_line->Next;
						 delete First_line;
						 First_line = p;
					}
// ***********************************
// ********      Adi          ********
// ********   Aug 13,1997     ********
// ********       begin       ********
// ***********************************
				}
				else
				{
					if (mode_text)
					{
						T3000_help->GWPuts(2,8,"            Sorry !",COLOR_LETTER_TEXT,COLOR_BACK_TEXT);
						T3000_help->GWPuts(4,5," The context_string isn't correct !",COLOR_LETTER_TEXT,COLOR_BACK_TEXT);
					}
					else
					{
						T3000_help->GWPuts(2,8,"            Sorry !",COLOR_LETTER_GRAPH,COLOR_BACK_GRAPH);
						T3000_help->GWPuts(4,5," The context_string isn't correct !",COLOR_LETTER_GRAPH,COLOR_BACK_GRAPH);
					}
					while(!(T3000_help->HandleEvent()));
				}
			}
		}
		fclose(Help_file);
	}
	else
	{
		if (mode_text)
		{
			T3000_help->GWPuts(2,8,"            Sorry!",COLOR_LETTER_TEXT,COLOR_BACK_TEXT);
			T3000_help->GWPuts(4,8," The T3000.hlp file isn't exist!",COLOR_LETTER_TEXT,COLOR_BACK_TEXT);
		}
		else
		{
			T3000_help->GWPuts(2,8,"            Sorry!",COLOR_LETTER_GRAPH,COLOR_BACK_GRAPH);
			T3000_help->GWPuts(4,8," The T3000.hlp file isn't exist!",COLOR_LETTER_GRAPH,COLOR_BACK_GRAPH);
		}
		while(!(T3000_help->HandleEvent()));
	}
	T3000_help->GReleaseWindow();
	delete T3000_help;
	if (mode_text)
	{
		_setcursortype(_NORMALCURSOR);
	}
	chdir(directory_current);
 }

// **********************************************

 GWindow *T3000_help_initialize(void)
 {
	int Win_lx;
	int Win_rx;
	int Win_ty;      
	int Win_by;

	int Counter;

	if (mode_text)
	{
		Win_lx=(80-WIN_LENGTH)/2;
		Win_rx=Win_lx+WIN_LENGTH+1;
		Win_ty=(24-WIN_HIGH)/2;
		Win_by=Win_ty+WIN_HIGH+1;
	}
	else
	{
		Win_lx=(int)((640-WIN_LENGTH*WORD_WIDE)/2);
		Win_rx=(int)(Win_lx+WIN_LENGTH*WORD_WIDE);
		Win_ty=(int)((480-WIN_HIGH*WORD_HIGH)/2);
		Win_by=(int)(Win_ty+WIN_HIGH*WORD_HIGH);
	}
	GWindow *T3000_help= new GWindow(Win_lx,Win_ty,Win_rx,Win_by,NO_STACK,0);
	if (mode_text)
	{
		T3000_help->GWSet("T3000 Help",Lightblue,BLUE,BLUE);
	}
	else
	{
		T3000_help->GWSet("T3000 Help",BLUE,Lightblue,BLUE);
	}
	T3000_help->GShowWindow(WIN_ERROR);

	if (mode_text)
	{
		_setcursortype(_NOCURSOR);
		textcolor(BLUE);
		textbackground(COLOR_LETTER_TEXT);
		movetoxy(Win_rx,Win_ty+1);
		putch(30);   // up arrow
//		for(Counter=Win_ty+2;Counter<Win_by-1;Counter++)
//		{
//			movetoxy(Win_rx,Counter);
//			putch(Counter-Win_ty+17);
//		}
		movetoxy(Win_rx,Win_by-1);
		putch(31);   // down arrow;
	}
	else
	{
		setcolor(LIGHTGRAY);
		bar(Win_rx-WORD_WIDE-3,Win_ty+13,Win_rx-1,Win_by-4);
		setcolor(WHITE);
		line(Win_rx-6,Win_ty+15,Win_rx-WORD_WIDE-1,Win_ty+23);
		setcolor(BLACK);
		line(Win_rx-6,Win_ty+15,Win_rx-2,Win_ty+23);
		line(Win_rx-WORD_WIDE-1,Win_ty+23,Win_rx-2,Win_ty+23);

		setcolor(WHITE);
		line(Win_rx-6,Win_by-6,Win_rx-WORD_WIDE-1,Win_by-14);
		setcolor(BLACK);
		line(Win_rx-6,Win_by-6,Win_rx-2,Win_by-14);
		setcolor(WHITE);
		line(Win_rx-WORD_WIDE-1,Win_by-14,Win_rx-2,Win_by-14);

		setcolor(BLACK);
		line(Win_rx-7,Win_ty+29,Win_rx-7,Win_by-20);
		setcolor(WHITE);
		line(Win_rx-6,Win_ty+29,Win_rx-6,Win_by-20);
	}

	return T3000_help;
 }

// **********************************************
 char far *Search_context_number(int Context_number)
 {
	int Counter;

	for (Counter=0;Counter<max_map_array;Counter++)
	{
		if (map_array[Counter].context_number==Context_number)
		{
			break;
		}
	}
	if (Counter==max_map_array)
	{
		return NULL;
	}
	else
	{
		return map_array[Counter].context_string;
	}
 }


// **********************************************

 void Search_context_string(FILE *Help_file,char far *Context_string)
 {
	char Letter;
	char String_array[40];
	char far *String_temporary;
	int  Length_context_string;
	long offset;

	do
	{
		do
		{
			do
			{
				if (feof(Help_file))
				{
					break;
				}
				Letter=fgetc(Help_file);
			}	while (!(feof(Help_file)||(Letter==FLAG_CONTEXT)));
			if (feof(Help_file))
			{
				break;
			}
			Length_context_string=strlen(Context_string);
			String_temporary=fgets(String_array,Length_context_string+1,Help_file);
			Letter=fgetc(Help_file);
			if (Letter!=FLAG_TITLE)
			{
				offset=strlen(String_temporary)+1;
				offset=0-offset;
				fseek(Help_file,offset,1);
			}
		}  while (Letter!=FLAG_TITLE);
		if (feof(Help_file))
		{
			break;
		}
		if (abs(strcmp(Context_string,String_temporary)))
		{
			offset=strlen(String_temporary)+1;
			offset=0-offset;
			fseek(Help_file,offset,1);
		}
	}  while (abs(strcmp(Context_string,String_temporary)));
 }

// **********************************************

 struct Text_line far *Build_text_chain(FILE *Help_file)
 {
	char far *String_temporary;
	char String_array[WIN_LENGTH+2];
	struct Text_line far *First_line;
	struct Text_line far *Win_old_line;
	struct Text_line far *Win_current_line;
	struct Text_line far *Win_new_line;
	int Counter;

	First_line=NULL;
	Win_old_line=NULL;
	Win_current_line=NULL;
	Win_new_line=NULL;
	Counter=0;

	if (!feof(Help_file))
	{
		String_temporary=Get_words(Help_file,String_array);
		First_line=new (Text_line);
		Win_current_line=First_line;
		while (!(Judge_page_break(String_temporary)||feof(Help_file)))
		{
			Win_new_line=new (Text_line);
			strcpy(Win_current_line->Text_string,String_temporary);
			Win_current_line->Location=Counter;
			Change_text_line_array(Win_current_line->Text_string);
			Win_current_line->Previous=Win_old_line;
			Win_current_line->Next=Win_new_line;
			Win_old_line=Win_current_line;
			Win_current_line=Win_new_line;
			String_temporary=Get_words(Help_file,String_array);
			Counter++;
		}
		max_text_chain=Counter;
		Win_old_line->Next=NULL;
		delete Win_new_line;
	}
	return First_line;
 }
// **********************************************
 int Judge_page_break(char far *String)
 {
	char *String_page_break;
	int Flag_equ;
	int Length_string;
	int i;

	Flag_equ=1;
	String_page_break=FLAG_PAGE_BREAK;
	Length_string=strlen(String_page_break);
	if ((String==NULL)||(Length_string==0))
	{
		Flag_equ=0;
	}
	else
	{
		i=0;
		while ((i<Length_string)&&(Flag_equ==1))
		{
			if (String[i]!=String_page_break[i])
			{
				Flag_equ=0;
			}
			i++;
		}
	}
	return Flag_equ;
 }

// **********************************************
 void Text_display(GWindow *T3000_help,struct Text_line far *Win_top_line)
 {
	struct Text_line far *Win_current_line;
	int Counter_line;
	int Counter_letter;
	char String_space[WIN_LENGTH+1];
	for (Counter_letter=0;Counter_letter<WIN_LENGTH;Counter_letter++)
	{
		String_space[Counter_letter]=SPACE;
	}
	String_space[WIN_LENGTH]=FLAG_END_LINE;

	Counter_line=0;
	Win_current_line=Win_top_line;
	while (Counter_line<WIN_HIGH)
	{
		if (Win_current_line!=NULL)
		{
			if (mode_text)
			{
				if (Win_current_line->Previous==NULL)
				{
					T3000_help->GWPuts(Counter_line,0,Win_current_line->Text_string,COLOR_LETTER_TEXT,YELLOW);
				}
				else
				{
					T3000_help->GWPuts(Counter_line,0,Win_current_line->Text_string,COLOR_LETTER_TEXT,COLOR_BACK_TEXT);
				}
			}
			else
			{
				if (Win_current_line->Previous==NULL)
				{
					T3000_help->GWPuts(Counter_line,1,Win_current_line->Text_string,COLOR_LETTER_GRAPH,YELLOW);
				}
				else
				{
					T3000_help->GWPuts(Counter_line,1,Win_current_line->Text_string,COLOR_LETTER_GRAPH,COLOR_BACK_GRAPH);
				}
			}
			Win_current_line=Win_current_line->Next;
		}
		else
		{
			if (mode_text)
			{
				T3000_help->GWPuts(Counter_line,0,String_space,COLOR_LETTER_TEXT,COLOR_BACK_TEXT);
			}
			else
			{
				T3000_help->GWPuts(Counter_line,1,String_space,COLOR_LETTER_GRAPH,COLOR_BACK_GRAPH);
			}
		}
		Counter_line++;
	}
 }

// **********************************************
 void Change_text_line_array(char far *String_array)
 {
	int Counter_letter;
	int Length_string;

	Length_string=strlen(String_array);
	String_array[WIN_LENGTH]=String_array[Length_string];
	if (String_array[Length_string-1]==FLAG_CHANGE_LINE)
	{
		String_array[Length_string-1]=SPACE;
	}
	for (Counter_letter=Length_string;Counter_letter<(WIN_LENGTH);Counter_letter++)
	{
		String_array[Counter_letter]=SPACE;
	}

 }

// **********************************************
 void Handle_key_press(GWindow *T3000_help,struct Text_line far *First_line)
 {
	struct Text_line far *Win_current_line;
	struct Text_line far *Win_top_line;

	int  Flag_continue_or_exit;         // Decide exit help or no
	int  Counter_line;
	union
	{
		int i;
		char ch[2];
	} 	Key;

	char Letter;
	char Key_press;                     // The key from keybord

	MouseStatus stat;
	int Win_lx;
	int Win_rx;
	int Win_ty;
	int Win_by;
	hot_box Up_arrow;
	hot_box Down_arrow;
	hot_box Up_ground;
	hot_box Down_ground;

	struct
	{
		int x;
		int y;
		int x1;
		int y1;
	} Block;
	int Flag_click;
	if (mode_text)
	{
		Win_lx=(80-WIN_LENGTH)/2;
		Win_rx=Win_lx+WIN_LENGTH+1;
		Win_ty=(24-WIN_HIGH)/2;
		Win_by=Win_ty+WIN_HIGH+1;
		Up_arrow.top.x=Win_rx;
		Up_arrow.top.y=Win_ty+1;
		Up_arrow.bot.x=Win_rx;
		Up_arrow.bot.y=Win_ty+1;
		Down_arrow.top.x=Win_rx;
		Down_arrow.top.y=Win_by-1;
		Down_arrow.bot.x=Win_rx;
		Down_arrow.bot.y=Win_by-1;
		Block.x=Win_rx;
		Block.y=Win_ty+2;
		Up_ground.top.x=Win_rx;
		Up_ground.top.y=Win_ty+2;
		Up_ground.bot.x=Win_rx;
		Up_ground.bot.y=Win_ty+1;
		Down_ground.top.x=Win_rx;
		Down_ground.top.y=Win_ty+3;
		Down_ground.bot.x=Win_rx;
		Down_ground.bot.y=Win_by-2;
	}
	else
	{
		Win_lx=(int)((640-WIN_LENGTH*WORD_WIDE)/2);
		Win_rx=(int)(Win_lx+WIN_LENGTH*WORD_WIDE);
		Win_ty=(int)((480-WIN_HIGH*WORD_HIGH)/2);
		Win_by=(int)(Win_ty+WIN_HIGH*WORD_HIGH);
		Up_arrow.top.x=Win_rx-WORD_WIDE-3;
		Up_arrow.top.y=Win_ty+13;
		Up_arrow.bot.x=Win_rx;
		Up_arrow.bot.y=Win_ty+25;
		Down_arrow.top.x=Win_rx-WORD_WIDE-3;
		Down_arrow.top.y=Win_by-16;
		Down_arrow.bot.x=Win_rx;
		Down_arrow.bot.y=Win_by-4;
		Block.x=Win_rx-WORD_WIDE-2;
		Block.y=Win_ty+29;
		Block.x1=Win_rx-1;
		Block.y1=Win_ty+34;
		Up_ground.top.x=Win_rx-WORD_WIDE-3;
		Up_ground.top.y=Win_ty+29;
		Up_ground.bot.x=Win_rx;
		Up_ground.bot.y=Block.y-1;
		Down_ground.top.x=Win_rx-WORD_WIDE-3;
		Down_ground.top.y=Block.y1+1;
		Down_ground.bot.x=Win_rx;
		Down_ground.bot.y=Win_by-20;
	}
	if (First_line!=NULL)
	{
		Win_top_line=First_line;
		Win_current_line=First_line;

		hide_pointer();
		Text_display(T3000_help,Win_current_line);
		display_pointer();
		if (mode_text)
		{
			movetoxy(Block.x,Block.y);
			putch(15);   // up arrow
		}
		else
		{
			setfillstyle(1,LIGHTGRAY);
			bar(Block.x,Block.y,Block.x1,Block.y1);
			setcolor(WHITE);
			line(Block.x,Block.y,Block.x1,Block.y);
			line(Block.x,Block.y,Block.x,Block.y1);
			setcolor(BLACK);
			line(Block.x1,Block.y1,Block.x1,Block.y);
			line(Block.x1,Block.y1,Block.x,Block.y1);
		}
		Flag_continue_or_exit=CONTINUE_HELP;
		while(Flag_continue_or_exit)
		{
			if ( (Key.i=bioskey_new(1)) )                //kbhit())
			{
				Key.i=bioskey_new(0);
				Key_press=Key.ch[0];
				if(Key_press==ESC)
				{
					Flag_continue_or_exit=EXIT_HELP;
				}
				if(Key_press==0)
				{
					Key_press=Key.ch[1];
					hide_pointer();
					switch (Key_press)
					{
						case UP:
						{
							if (Win_top_line!=First_line)
							{
								Win_top_line=Win_top_line->Previous;
								Win_current_line=Win_top_line;
								Text_display(T3000_help,Win_current_line);
							}
						};break;
						case DOWN:
						{
							if (Win_top_line->Next!=NULL)
							{
								Win_top_line=Win_top_line->Next;
								Win_current_line=Win_top_line;
								Text_display(T3000_help,Win_current_line);
							}
						};break;
						case PGUP:
						{
							Counter_line=0;
							Win_current_line=Win_top_line;
							while ((Counter_line<WIN_HIGH)&&(Win_current_line!=First_line))
							{
								Win_current_line=Win_current_line->Previous;
								Counter_line++;
							}
							Win_top_line=Win_current_line;
							Text_display(T3000_help,Win_current_line);
						};break;
						case PGDN:
						{
							Counter_line=0;
							Win_current_line=Win_top_line;
							while ((Counter_line<WIN_HIGH)&&(Win_current_line->Next!=NULL))
							{
								Win_current_line=Win_current_line->Next;
								Counter_line++;
							}
							Win_top_line=Win_current_line;
							Text_display(T3000_help,Win_current_line);
						};break;
						default:
						{
						};break;
					}
					if (mode_text)
					{
						movetoxy(Block.x,Block.y);
						putch(179);
						Block.y=Win_ty+2+(int)((Win_top_line->Location*(WIN_HIGH-2))/max_text_chain);
						movetoxy(Block.x,Block.y);
						putch(15);
					}
					else
					{
						setfillstyle(1,LIGHTGRAY);
						bar(Block.x,Block.y,Block.x1,Block.y1);
						setcolor(BLACK);
						line(Win_rx-7,Block.y,Win_rx-7,Block.y1);
						setcolor(WHITE);
						line(Win_rx-6,Block.y,Win_rx-6,Block.y1);
						Block.y=(Win_ty+29)+(int)(((Win_by-25)-(Win_ty+29))*Win_top_line->Location/max_text_chain);
						Block.y1=Block.y+5;

						setfillstyle(1,LIGHTGRAY);
						bar(Block.x,Block.y,Block.x1,Block.y1);
						setcolor(WHITE);
						line(Block.x,Block.y,Block.x1,Block.y);
						line(Block.x,Block.y,Block.x,Block.y1);
						setcolor(BLACK);
						line(Block.x1,Block.y1,Block.x1,Block.y);
						line(Block.x1,Block.y1,Block.x,Block.y1);
					}
					display_pointer();
				}
			}
			if(mouse_inside(T3000_help->close_spot.top.x,T3000_help->close_spot.top.y,
								 T3000_help->close_spot.bot.x,T3000_help->close_spot.bot.y))
			{
				mouse_status(stat);
				if(stat.leftButton)
				{
					while(!get_button_released(BLEFT,stat));
					Flag_continue_or_exit=EXIT_HELP;
				}
			}
			if(mouse_inside(Up_arrow.top.x,Up_arrow.top.y,
								 Up_arrow.bot.x,Up_arrow.bot.y))
			{
				mouse_status(stat);
				if(stat.leftButton)
				{
					Flag_click=CLICK_FIRST;
					while(!get_button_released(BLEFT,stat))
					{
						hide_pointer();
						if (Win_top_line!=First_line)
						{
							Win_top_line=Win_top_line->Previous;
							Win_current_line=Win_top_line;
							Text_display(T3000_help,Win_current_line);
						}
						if (mode_text)
						{
							movetoxy(Block.x,Block.y);
							putch(179);
							Block.y=Win_ty+2+(int)((Win_top_line->Location*(WIN_HIGH-2))/max_text_chain);
							movetoxy(Block.x,Block.y);
							putch(15);
						}
						else
						{
							setfillstyle(1,LIGHTGRAY);
							bar(Block.x,Block.y,Block.x1,Block.y1);
							setcolor(BLACK);
							line(Win_rx-7,Block.y,Win_rx-7,Block.y1);
							setcolor(WHITE);
							line(Win_rx-6,Block.y,Win_rx-6,Block.y1);
							Block.y=(Win_ty+29)+(int)(((Win_by-25)-(Win_ty+29))*Win_top_line->Location/max_text_chain);
							Block.y1=Block.y+5;

							setfillstyle(1,LIGHTGRAY);
							bar(Block.x,Block.y,Block.x1,Block.y1);
							setcolor(WHITE);
							line(Block.x,Block.y,Block.x1,Block.y);
							line(Block.x,Block.y,Block.x,Block.y1);
							setcolor(BLACK);
							line(Block.x1,Block.y1,Block.x1,Block.y);
							line(Block.x1,Block.y1,Block.x,Block.y1);
						}
						display_pointer();
						if (Flag_click==CLICK_FIRST)
						{
							delay(WAITE_OF_CLICK_FIRST);
							Flag_click=CLICK_CONTINUE;
						}
						else
						{
							delay(200);
						}
					}
				}
			}
			if(mouse_inside(Down_arrow.top.x,Down_arrow.top.y,
								 Down_arrow.bot.x,Down_arrow.bot.y))
			{
				mouse_status(stat);
				if(stat.leftButton)
				{
					Flag_click=CLICK_FIRST;
					while(!get_button_released(BLEFT,stat))
					{
						hide_pointer();
						if (Win_top_line->Next!=NULL)
						{
							Win_top_line=Win_top_line->Next;
							Win_current_line=Win_top_line;
							Text_display(T3000_help,Win_current_line);
						}
						if (mode_text)
						{
							movetoxy(Block.x,Block.y);
							putch(179);
							Block.y=Win_ty+2+(int)((Win_top_line->Location*(WIN_HIGH-2))/max_text_chain);
							movetoxy(Block.x,Block.y);
							putch(15);
						}
						else
						{
							setfillstyle(1,LIGHTGRAY);
							bar(Block.x,Block.y,Block.x1,Block.y1);
							setcolor(BLACK);
							line(Win_rx-7,Block.y,Win_rx-7,Block.y1);
							setcolor(WHITE);
							line(Win_rx-6,Block.y,Win_rx-6,Block.y1);
							Block.y=(Win_ty+29)+(int)(((Win_by-25)-(Win_ty+29))*Win_top_line->Location/max_text_chain);
							Block.y1=Block.y+5;

							setfillstyle(1,LIGHTGRAY);
							bar(Block.x,Block.y,Block.x1,Block.y1);
							setcolor(WHITE);
							line(Block.x,Block.y,Block.x1,Block.y);
							line(Block.x,Block.y,Block.x,Block.y1);
							setcolor(BLACK);
							line(Block.x1,Block.y1,Block.x1,Block.y);
							line(Block.x1,Block.y1,Block.x,Block.y1);
						}
						display_pointer();
						if (Flag_click==CLICK_FIRST)
						{
							delay(WAITE_OF_CLICK_FIRST);
							Flag_click=CLICK_CONTINUE;
						}
						else
						{
							delay(200);
						}
					}
				}
			}
			if(mouse_inside(Up_ground.top.x,Up_ground.top.y,
								 Up_ground.bot.x,Up_ground.bot.y))
			{
				mouse_status(stat);
				if(stat.leftButton)
				{
					while(!get_button_released(BLEFT,stat));
					Counter_line=0;
					Win_current_line=Win_top_line;
					while ((Counter_line<WIN_HIGH)&&(Win_current_line!=First_line))
					{
						Win_current_line=Win_current_line->Previous;
						Counter_line++;
					}
					Win_top_line=Win_current_line;
					hide_pointer();
					Text_display(T3000_help,Win_current_line);
					if (mode_text)
					{
						movetoxy(Block.x,Block.y);
						putch(179);
						Block.y=Win_ty+2+(int)((Win_top_line->Location*(WIN_HIGH-2))/max_text_chain);
						movetoxy(Block.x,Block.y);
						putch(15);
					}
					else
					{
						setfillstyle(1,LIGHTGRAY);
						bar(Block.x,Block.y,Block.x1,Block.y1);
						setcolor(BLACK);
						line(Win_rx-7,Block.y,Win_rx-7,Block.y1);
						setcolor(WHITE);
						line(Win_rx-6,Block.y,Win_rx-6,Block.y1);
						Block.y=(Win_ty+29)+(int)(((Win_by-25)-(Win_ty+29))*Win_top_line->Location/max_text_chain);
						Block.y1=Block.y+5;

						setfillstyle(1,LIGHTGRAY);
						bar(Block.x,Block.y,Block.x1,Block.y1);
						setcolor(WHITE);
						line(Block.x,Block.y,Block.x1,Block.y);
						line(Block.x,Block.y,Block.x,Block.y1);
						setcolor(BLACK);
						line(Block.x1,Block.y1,Block.x1,Block.y);
						line(Block.x1,Block.y1,Block.x,Block.y1);
					}
					display_pointer();
				}
			}
			if(mouse_inside(Down_ground.top.x,Down_ground.top.y,
								 Down_ground.bot.x,Down_ground.bot.y))
			{
				mouse_status(stat);
				if(stat.leftButton)
				{
					while(!get_button_released(BLEFT,stat));
					Counter_line=0;
					Win_current_line=Win_top_line;
					while ((Counter_line<WIN_HIGH)&&(Win_current_line->Next!=NULL))
					{
						Win_current_line=Win_current_line->Next;
						Counter_line++;
					}
					Win_top_line=Win_current_line;
					hide_pointer();
					Text_display(T3000_help,Win_current_line);
					if (mode_text)
					{
						movetoxy(Block.x,Block.y);
						putch(179);
						Block.y=Win_ty+2+(int)((Win_top_line->Location*(WIN_HIGH-2))/max_text_chain);
						movetoxy(Block.x,Block.y);
						putch(15);
					}
					else
					{
						setfillstyle(1,LIGHTGRAY);
						bar(Block.x,Block.y,Block.x1,Block.y1);
						setcolor(BLACK);
						line(Win_rx-7,Block.y,Win_rx-7,Block.y1);
						setcolor(WHITE);
						line(Win_rx-6,Block.y,Win_rx-6,Block.y1);
						Block.y=(Win_ty+29)+(int)(((Win_by-25)-(Win_ty+29))*Win_top_line->Location/max_text_chain);
						Block.y1=Block.y+5;

						setfillstyle(1,LIGHTGRAY);
						bar(Block.x,Block.y,Block.x1,Block.y1);
						setcolor(WHITE);
						line(Block.x,Block.y,Block.x1,Block.y);
						line(Block.x,Block.y,Block.x,Block.y1);
						setcolor(BLACK);
						line(Block.x1,Block.y1,Block.x1,Block.y);
						line(Block.x1,Block.y1,Block.x,Block.y1);
					}
					display_pointer();
				}
			}
			Up_ground.bot.y=Block.y-1;
			if (mode_text)
			{
				Down_ground.top.y=Block.y+1;
			}
			else
			{
				Down_ground.top.y=Block.y1+1;
			}
		}
	}
 }

// **********************************************
 char far *Get_words(FILE *Help_file,char String_array[WIN_LENGTH+2])
 {
	long offset;
	int Counter_letter;

	if (feof(Help_file))
	{
		return NULL;
	}
	fgets(String_array,WIN_LENGTH+2,Help_file);
	if (_fstrchr(String_array,FLAG_CHANGE_LINE)==NULL)     // no "\n"
	{
		if (String_array[WIN_LENGTH]!=SPACE)
		{
			for (Counter_letter=WIN_LENGTH;Counter_letter>=0;Counter_letter--)
			{
				if (String_array[Counter_letter]==SPACE)
				{
					break;
				}
			}
			if (Counter_letter>=0)
			{
				String_array[Counter_letter]=FLAG_END_LINE;
				offset=Counter_letter-WIN_LENGTH;
				fseek(Help_file,offset,1);
			}
			else
			{
				fseek(Help_file,-1,1);
			}
		}
		else
		{
			String_array[WIN_LENGTH]=FLAG_END_LINE;
		}
	}
	else
	{
			String_array[WIN_LENGTH]=FLAG_END_LINE;
	}
	return String_array;
 }
// **********************************************
 int Key_word_convert(char far *Key_word)
 {
	int Counter;
	Counter=0;
	if (Key_word==NULL)
	{
		return IMPOTENT;
	}
	else
	{
		while ((Counter<max_map_array)&&(map_array[Counter].context_number>1000)&&(map_array[Counter].context_number<2000))
		{
			if (!strcmp(map_array[Counter].context_string,Key_word))
			{
				return map_array[Counter].context_number;
			}
         Counter++;
		}
		return IMPOTENT;
	}
 }

