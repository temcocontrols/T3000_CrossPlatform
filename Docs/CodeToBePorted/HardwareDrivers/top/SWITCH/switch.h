#ifndef __SWITCH_H
#define __SWITCH_H
 
#include "bitmap.h"

extern u8 Switch_Status[24];

void Switch_Init(void);
void Check_Switch_Status(u8 group);


#endif

