//////////////////////////////////////////////////////////
//                                                      //
//   Implements the mouse  functions offered by int33   //
//                                                      //
//////////////////////////////////////////////////////////

#ifndef _MOUSE.H
#define _MOUSE.H

#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <bios.h>

#define  uint    unsigned int

#define  BLEFT   0
#define  BRIGHT  1
#define  BCENTER 2
#define SHOWMOUSE 1
#define HIDEMOUSE 0

typedef struct
{
 int x;
 int y;
} Pointxy;

typedef struct MouseStatus        // describes the mouse status
{

 uint  leftButton;
 uint  rightButton;
 uint  centerButton;
 Pointxy where;

}MouseStatus;

typedef struct Pshape             // describes the pointer shape
{
 Pointxy hot_spot;
 uint  shape[32];

}Pshape;

void mouse_installed(void);       // checks if mouse installed
void display_pointer(void);       // shows the mouse pointer on the screen
void hide_pointer(void);          // hides the pointer
void mouse_status(MouseStatus& s);// gets the status of the buttons
																	// and the mouse position
int mouse_motion(int *x,int *y);

uint get_button_pressed(char which,
												MouseStatus& s); // returns the # of the  clicks
																				 // since the last call, as well
																				 // as the mouse status

uint get_button_released(char which,
												 MouseStatus& s);// returns the # of the  clicks
																				 // since the last call, as well
																				 // as the mouse status

void set_hor_range(uint xmin, uint xmax);// sets the horizontal range out
																				 // of which the mouse cursor will
																				 // not be able to move

void set_vert_range(uint xmin, uint xmax); // the same for vertical

void set_pointer_shape(Pshape& p); // loads the pointer shape from
																	 // a specified array

void set_speed(uint hor,uint vert);// sets the mouse speed (in mickeys per
																	 //    in each direction)

void set_mhandler(uint what, uint segm, uint offs); // installs a mouse
																										// handler

uint mouse_inside(uint ux,uint uy,
									uint dx,uint dy);// checks if the cursor is inside the
																	 // specified area

void set_exclusion_area(uint upx, uint upy,
												uint dnx, uint dny); // sets an area in which the
																						 // cursor is not visible
void move_mouse(int x,int y);

#endif