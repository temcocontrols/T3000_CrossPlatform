//**********************************************************************
//
//  Here is defined the class used for interfacing with the AIO board
//
//**********************************************************************

#include <graphics.h>
#include <windows.h>
#include "aio.h"
#include "gwin.h"
#include <stdio.h>
#include "mtkernel.h"
#include "rs485.h"

#define MAX_TRY 30000
#define SCAN_RATE 3

//#pragma inline

extern int get_point(Point point, long *value, char **p);

extern char control;
extern dig_range_form huge dig_range_array[];
extern char reset1;
extern char version_string[12];

extern Board_info	boards[MAX_BOARDS];
extern Str_tbl_point custom_tab[MAX_TABS];

unsigned char blocked,blocked1;
long const4095 = 4095L;
long const4096 = 4096L;
long const1000 = 1000L;
long const5000 = 5000L;
long const10000 = 10000L;
long const100000 = 100000L;
long const300000 = 300000L;
long const20000 = 20000L;

long tab_int[10] = { 2969, 5344, 2500, 4500, 2500, 4500,
											2500, 4500, 2500, 4500 };

long limit[10][2] = { {-40000, 150000}, {-40000, 302000}, {-40000, 120000},
											{-40000, 248000}, {-40000, 120000}, {-40000, 248000},
											{-40000, 120000}, {-40000, 248000},
											{-50000, 110000}, {-58000,230000} };

uint def_tab[5][65] = {
	 // 3k termistor YSI44005 -40 to 150 Deg.C or -40 to 302 Deg.F
	 {
		3723, 3652, 3571, 3480, 3378, 3266, 3143, 3011,
		2871, 2724, 2571, 2415, 2257, 2100, 1945, 1793,
		1648, 1509, 1378, 1254, 1139, 1033, 935, 845,
		763, 689, 622, 561, 506, 456, 412, 372,
		336, 304, 275, 249, 226, 205, 186, 169,
		154, 141, 128, 117, 107, 98, 90, 82,
		76, 70, 64, 59, 54, 50, 46, 43,
		40, 37, 34, 32, 29, 27, 26, 24, 22
	  },

	 // 10k termistor GREYSTONE -40 to 120 Deg.C or -40 to 248 Deg.F
	 {
		3928, 3903, 3875, 3845, 3810, 3772, 3729, 3683,
		3632, 3576, 3516, 3451, 3381, 3307, 3227, 3144,
		3056, 2965, 2869, 2772, 2671, 2569, 2464, 2360,
		2254, 2150, 2046, 1944, 1843, 1745, 1650, 1557,
		1468, 1382, 1300, 1222, 1147, 1076, 1009, 945,
		885, 829, 776, 726, 679, 636, 595, 556,
		521, 487, 456, 427, 400, 375, 351, 329,
		309, 290, 272, 255, 240, 225, 212, 199, 188
		},

	 // 3k termistor GREYSTONE -40 to 120 Deg.C or -40 to 248 Deg.F
	 {
		3724, 3665, 3598, 3525, 3444, 3356, 3260, 3157,
		3047, 2931, 2809, 2684, 2554, 2423, 2290, 2148,
		2026, 1897, 1770, 1648, 1530, 1418, 1311, 1211,
		1116, 1027, 945, 868, 797, 731, 670, 615,
		564, 517, 474, 435, 399, 369, 336, 309,
		284, 261, 240, 222, 204, 188, 174, 161,
		148, 137, 127, 118, 109, 101, 94, 87,
		81, 76, 71, 66, 61, 57, 54, 50, 47
	 },

	 // 10k termistor KM -40 to 120 Deg.C or -40 to 248 Deg.F
	 {
		3928, 3903, 3875, 3845, 3810, 3772, 3729, 3683,
		3632, 3576, 3516, 3451, 3381, 3307, 3227, 3144,
		3056, 2965, 2869, 2772, 2671, 2569, 2464, 2360,
		2254, 2150, 2046, 1944, 1843, 1745, 1650, 1557,
		1468, 1382, 1300, 1222, 1147, 1076, 1009, 945,
		885, 829, 776, 726, 679, 636, 595, 556,
		521, 487, 456, 427, 400, 375, 351, 329,
		309, 290, 272, 255, 240, 225, 212, 199, 188
	  },

	 // 3k termistor AK -40 to 150 Deg.C or -40 to 302 Deg.F
	 {
		3928, 3903, 3875, 3845, 3810, 3772, 3729, 3683,
		3632, 3576, 3516, 3451, 3381, 3307, 3227, 3144,
		3056, 2965, 2869, 2772, 2671, 2569, 2464, 2360,
		2254, 2150, 2046, 1944, 1843, 1745, 1650, 1557,
		1468, 1382, 1300, 1222, 1147, 1076, 1009, 945,
		885, 829, 776, 726, 679, 636, 595, 556,
		521, 487, 456, 427, 400, 375, 351, 329,
		309, 290, 272, 255, 240, 225, 212, 199, 188
	 }
 };

void init_boards_struct( void )
{
	int i, j;
	for( i=0; i<MAX_BOARDS; i++ )
	{
		boards[i].board_number = i;
		boards[i].in_mask = 0x0F;
		boards[i].out_mask = 0xF0;
		boards[i].no_ins = MAX_INS/2;
		boards[i].no_outs = MAX_OUTS/2;
		boards[i].watchdog_interval = 250;
		boards[i].watchdog_flag = 0;
		boards[i].sample_time = 200;
		boards[i].status = 0;
		boards[i].base_adr = 100+i*4;
		boards[i].base_adr = 256;
		boards[i].quartz_freq = 7372;
		boards[i].sample_time = 200;
	}
}

void Aio::Config_dacqd_card( void )
{
	asm push es;
	Aio_Error result;
	Aux_board_info aux_data[4];
	Board_info	boards_old[MAX_BOARDS];
	byte flag, count, count_stat;
	unsigned int lj;
	blocked = 0;
	int i, j, control_old;

	control_old = control;
	reset1 = 0;
	control = 0;
	reset1 = 0;
	for( i=0; i<number_of_boards; i++ )
	{
		boards_old[i] = boards[i];
		boards[i].no_ins = 0;
		boards[i].no_outs = 0;
		aux_data[i].in_mask = boards[i].in_mask;
		aux_data[i].out_mask = boards[i].out_mask;
		aux_data[i].status = 0;
	}

 if(control_old)
 {
	count = 0;
	do
	{
		result = Aio_Control( RESET_CARD, NULL, 0 );
		delay(300);
		result = Aio_Control( VERSION, version_string, 0 );
	}
	while( ( result != AIO_OK ) && ( count++ < 5 ) );

	if( count > 5 )
	{
		 control_old=0;
		 for( i=0; i<number_of_boards; i++ )
		   boards[i] = boards_old[i];
		 asm pop es;
		 return;
	}

	for(lj=0; lj<50000; lj++ );
	count = 0;
	do
	{
		flag = 0;
		if( card_type > VER0_CARD )
		{
			if( ( result = Aio_Control( DESCRIPTION, NULL, 0 ) ) == AIO_OK )
			{
				for( i=0; i<number_of_boards; i++ )
				{
					boards[i].no_ins = 0;
					boards[i].no_outs = 0;
				}
				result = Aio_Control( GET_STATUS, NULL, 0 );
				for( i=0; i<number_of_boards; i++ )
				{
					for( lj=1; lj<256; lj<<=1 )
					{
						if( boards[i].in_mask & lj ) boards[i].no_ins += 16;
						if( boards[i].out_mask & lj ) boards[i].no_outs += 16;
					}
					if( ( aux_data[i].in_mask == boards[i].in_mask ) &&
						( aux_data[i].out_mask == boards[i].out_mask ) ) flag++;
				}
			}
		}
		else
		{
			for(lj=0; lj<50000; lj++ );
			result = Aio_Control( GET_STATUS, NULL, 0 );
			for( i=0; i<number_of_boards; i++ )
			{
				boards[i].no_ins = 0;
				boards[i].no_outs = 0;
				if( aux_data[i].status == boards[i].status ) flag++;
				aux_data[i].status = boards[i].status;
			}

			for( i=0; i<number_of_boards; i++ )
			{
				if( boards[i].status & 0x10 ) boards[i].no_ins += 16;
				if( boards[i].status & 0x20 ) boards[i].no_ins += 16;
				if( boards[i].status & 0x40 ) boards[i].no_outs += 16;
				if( boards[i].status & 0x80 ) boards[i].no_outs += 16;
			}

		}
	}
	while( ( count++ < 5 ) && ( flag != number_of_boards ) );
	if( count > 5 )
	{
		 control_old=0;
		 for( i=0; i<number_of_boards; i++ )
		   boards[i] = boards_old[i];
		 asm pop es;
		 return;
	}
	j = 0;
	lj = 0;
	for( i=0; i<number_of_boards; i++ )
	{
		j +=  boards[i].no_ins;
		lj = boards[i].no_outs;
	}

	if( !j && !lj )
	{
		boards[0].no_ins = 16;
		boards[0].no_outs = 16;
	}

	 for(lj=0; lj<50000; lj++ );
	 Aio_Control( GET_ALL, (byte*)in_data, 0 );
	 for(lj=0; lj<50000; lj++ );
	 Aio_Control( GET_ALL, (byte*)in_data, 0 );
	 for( i=0; i<MAX_INS; i++ ) in_aux[i].average = in_data[i];

	 //	for(lj=0; lj<50000; lj++ );
	Aio_Control( SET_RATE, NULL, 0 );
	for(lj=0; lj<50000; lj++ );
//	Aio_Control( POWER_TOGGLE, NULL, 0 );
 }
 blocked1=0;
 control = control_old;
 asm pop es;
}

/************************

void Aio::Aio_Control( Order comm, uint *data_buffer, byte p_number )
{
asm push es;
	uint latch, status, count, k, i, v_byte, s_time;
	uint id = p_number >> 5;
	latch = boards[id].base_adr;
	status = latch + 1;
	uint order;
	switch( comm )
	{
	 case SET_POINT:
		 order = ( p_number - id << 5 );
		 outportb( latch, order );
		 count = 0;
		 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
		 if( count >= MAX_TRY )
		 {
				blocked++;
				asm pop es;
				return;
		 }
		 v_byte =  0x00ff & ( *data_buffer >> 4 );
		 outportb( latch, v_byte );
		 count = 0;
		 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
		 if( count >= MAX_TRY )
		 {
				blocked++;
				asm pop es;
				return;
		 }
		 v_byte = (byte)( ( *data_buffer & 0x000f ) << 4 );
		 outportb( latch, v_byte );
		 count = 0;
		 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
		 if( count >= MAX_TRY )
		 {
				blocked++;
				asm pop es;
				return;
		 }
		 break;
	 case GET_POINT:
		 order = 0x20 + ( p_number - id << 5 );
		 outportb( latch,order );
		 count = 0;
		 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
		 if( count >= MAX_TRY )
		 {
				blocked++;
				asm pop es;
				return;
		 }
		 count = 0;
		 while( (inportb(status) & 2) != 2 && count < MAX_TRY ) count++;
		 if( count >= MAX_TRY )
		 {
				blocked++;
				asm pop es;
				return;
		 }
		 v_byte= 0x00ff & inportb(latch);
		 count = 0;
		 while( (inportb(status) & 2) != 2 && count < MAX_TRY ) count++;
		 if( count >= MAX_TRY )
		 {
				blocked++;
				asm pop es;
				return;
		 }
		 *data_buffer = inportb(latch);
		 *data_buffer = ( (*data_buffer) << 8 + v_byte );
		 while( ( inportb(status) & 2 ) == 2 ) v_byte=inportb(latch);
		 break;
	 case SET_ALL:
		 order = 0x40;
		 for( k=0; k<number_of_boards; k++ )
		 {
			 latch = boards[k].base_adr;
			 status = latch + 1;
			 outportb( latch, order);
			 count = 0;
			 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
			 if( count >= MAX_TRY )
			 {
					blocked++;
				asm pop es;
					return;
			 }
			 for(i=0;i<32;i++)
			 {
					v_byte = 0x00ff & ( data_buffer[i+k*32] >> 4 );
					outportb( latch, v_byte );
					count = 0;
					while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
					if( count >= MAX_TRY )
					{
						blocked++;
				asm pop es;
						return;
					}
					v_byte = ( ( data_buffer[i+k*32] & 0x000f ) << 4 );
					outportb( latch, v_byte );
					count = 0;
					while( (inportb(status) & 1 ) == 1 && count < MAX_TRY ) count++;
					if( count >= MAX_TRY )
					{
						blocked++;
				asm pop es;
						return;
					}
			 }
		 }
		 break;
	 case GET_ALL:
		order = 0x60;
		 for( k=0; k < number_of_boards; k++ )
		 {
			 latch = boards[k].base_adr;
			 status = latch + 1;
			 outportb( latch, order );
			 count = 0;
			 while( ( ( inportb(status) & 1 ) == 1 ) && count < MAX_TRY ) count++;
			 if( count >= MAX_TRY )
			 {
					blocked++;
				asm pop es;
					return;
			 }
			 for(i=0;i<32;i++)
			 {
				count = 0;
				while( ( ( inportb(status) & 2 ) != 2 ) && count < MAX_TRY ) count++;
				if( count >= MAX_TRY )
				{
					blocked++;
				asm pop es;
					return;
				}
				v_byte = inportb(latch);
				count = 0;
				while( ( ( inportb(status) & 2 ) != 2 ) && count < MAX_TRY ) count++;
				if( count >= MAX_TRY )
				{
					blocked++;
				asm pop es;
					return;
				}
				data_buffer[i+k*32] = inportb(latch);
//				data_buffer[i+k*32] = data_buffer[i+k*32] + ( v_byte * 256 );
				data_buffer[i+k*32] += ( v_byte * 256 );
//				data_buffer[i+k*32] /= 16;
				for( v_byte=0; v_byte<1000; v_byte++ );
			}
			while( (i=inportb(status) & 2) == 2 )
			{
					v_byte=inportb(latch);
					i=inportb(status);
			}
			for( i=0; i<10000; i++ );
//			while( ( inportb(status) & 2 ) == 2 ) v_byte=inportb(latch);
		 }
		 break;
	 case SET_RATE:
			order = 0x80;
			 for( k=0;k<number_of_boards;k++ )
			 {
				 latch = boards[k].base_adr;
				 status = latch + 1;
				 outportb( latch, order );
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						asm pop es;
						return;
				 }
				 s_time = (uint)( 65536 - ( boards[k].sample_time *
													boards[k].quartz_freq )/12000 );
				 v_byte = s_time >> 8;
				 outportb( latch, v_byte );
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
				asm pop es;
						return;
				 }
				 v_byte = s_time & 0x00ff;
				 outportb( latch, v_byte );
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
				asm pop es;
						return;
				 }
			}
		 break;
	 case WAVEFORM: break;
	 case GET_STATUS:
		order = 0xc0;
		 for( k=0; k<number_of_boards; k++ )
		 {
			 latch = boards[k].base_adr;
			 status = latch + 1;
			 outportb( latch, order );
			 count = 0;
			 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
			 if( count >= MAX_TRY )
			 {
					blocked++;
					asm pop es;
					return;
			 }
			 count = 0;
			 while( (inportb(status) & 2) != 2 && count < MAX_TRY ) count++;
			 if( count >= MAX_TRY )
			 {
					blocked++;
					asm pop es;
					return;
			 }
			 data_buffer[k] = (byte)inportb(latch);
		 }
		 while( ( inportb(status) & 2 ) == 2 ) v_byte=inportb(latch);
		 break;
	 case SPECIAL: break;
	 default:
		 mxyputs( 24, 24, "Command error in Aio_Control !" );
		 break;
	}
asm pop es;
}
*******************************/

/* Following is the new Aio_Control function for the T3000 systems */

Aio_Error Aio::Aio_Control( Order comm, byte *data_buffer, byte p_number )
{
	uint latch, status, count, k, i, j, s_time;
	uint index, v_byte;
	byte no_points;
	uint order, *data_pointer;
	Aio_Error result = AIO_OK;
	int xxx,yyy;

	data_pointer = (uint*) data_buffer;

	switch( comm )
	{
	 case SET_POINT:
		 index = 0;
		 while( p_number > boards[index].no_outs )
		 {
			p_number -= boards[index].no_outs;
			index++;
		 }
		 latch = boards[index].base_adr;
		 status = latch + 1;
		 count = 0;
		 while( ( inportb(status) & 2 ) == 2 && count++ < 5 ) v_byte=inportb(latch);
		 if( card_type == VER0_CARD )
			 order = p_number;
		 else
			 order = SET_POINT;
		 outportb( latch, order );
		 for(xxx=0; xxx<10; xxx++) yyy++;
		 count = 0;
		 while( ( inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
		 if( count >= MAX_TRY )
		 {
				blocked++;
				return AIO_BLOCKED;
		 }
		 if( card_type != VER0_CARD )
		 {
			 outportb( latch, p_number );
			 for(xxx=0; xxx<10; xxx++) yyy++;
			 count = 0;
			 while( ( inportb(status) & 1 ) == 1 && count < MAX_TRY ) count++;
			 if( count >= MAX_TRY )
			 {
					blocked++;
					return AIO_BLOCKED;
			 }
		 }
		 if( card_type < VER2_CARD )
			 v_byte =  0x00ff & ( data_pointer[0] >> 4 );
		 else
			 v_byte =  0x00ff & ( data_pointer[0] >> 8 );
		 outportb( latch, v_byte );
		 for(xxx=0; xxx<10; xxx++) yyy++;
		 count = 0;
		 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
		 if( count >= MAX_TRY )
		 {
				blocked++;
				return AIO_BLOCKED;
		 }
		 if( card_type < VER2_CARD )
			 v_byte = (byte)( ( data_pointer[0] & 0x000f ) << 4 );
		 else
			 v_byte = (byte)( data_pointer[0] & 0x00ff ) ;
		 outportb( latch, v_byte );
		 for(xxx=0; xxx<10; xxx++) yyy++;
		 count = 0;
		 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
		 if( count >= MAX_TRY )
		 {
				blocked++;
				return AIO_BLOCKED;
		 }
		 break;
	 case GET_POINT:
		 index = 0;
		 while( p_number > boards[index].no_ins )
		 {
			p_number -= boards[index].no_ins;
			index++;
		 }
		 if( card_type == VER0_CARD )
			order = 0x20 + p_number;
		 else
			 order = GET_POINT;
		 latch = boards[index].base_adr;
		 status = latch + 1;
		 count = 0;
		 while( ( inportb(status) & 2 ) == 2 && count++ < 5 ) v_byte=inportb(latch);
		 outportb( latch,order );
		 for(xxx=0; xxx<10; xxx++) yyy++;
		 count = 0;
		 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
		 if( count >= MAX_TRY )
		 {
				blocked++;
				return AIO_BLOCKED;
		 }
		 if( card_type != VER0_CARD )
		 {
			 order = p_number;
			 outportb( latch, order );
			 for(xxx=0; xxx<10; xxx++) yyy++;
			 count = 0;
			 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
			 if( count >= MAX_TRY )
			 {
					blocked++;
					return AIO_BLOCKED;
			 }
		 }
		 count = 0;
		 while( (inportb(status) & 2) != 2 && count < MAX_TRY ) count++;
		 if( count >= MAX_TRY )
		 {
				blocked++;
				return AIO_BLOCKED;
		 }
		 v_byte= 0x00ff & inportb(latch);
		 count = 0;
		 while( (inportb(status) & 2) != 2 && count < MAX_TRY ) count++;
		 if( count >= MAX_TRY )
		 {
				blocked++;
				return AIO_BLOCKED;
		 }
		 data_pointer[0] = inportb(latch);
		 data_pointer[0] = ( data_pointer[0] + ( v_byte << 8 ) );
		 while( ( inportb(status) & 2 ) == 2 ) v_byte=inportb(latch);
		 break;
	 case SET_ALL:
		 for( k=0; k<number_of_boards; k++ )
		 {
			 if( card_type == VER0_CARD )
			 {
				order = 0x40;
				no_points = 32;
			 }
			 else
			 {
				order = SET_ALL;
				no_points = boards[k].no_outs;
			 }
			 latch = boards[k].base_adr;
			 status = latch + 1;
			 count = 0;
			 while( ( inportb(status) & 2 ) == 2 && count++ < 5 ) v_byte=inportb(latch);
			 outportb( latch, order);
  		 for(xxx=0; xxx<10; xxx++) yyy++;
			 count = 0;
			 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
			 if( count >= MAX_TRY )
			 {
					blocked++;
					return AIO_BLOCKED;
			 }
			 for( i=0; i<no_points; i++ )
			 {
						/* Write the m.s.byte */
					if( card_type < VER2_CARD )
						v_byte = 0x00ff & ( data_pointer[i+k*no_points] >> 4 );
					else
						v_byte =  0x00ff & ( data_pointer[i+k*no_points] >> 8 );
					outportb( latch, (byte)v_byte );
					for(xxx=0; xxx<10; xxx++) yyy++;
					count = 0;
					while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
					if( count >= MAX_TRY )
					{
						blocked++;
						return AIO_BLOCKED;
					}
						/* Write the l.s.byte */
					if( card_type < VER2_CARD )
						 v_byte = (byte)( ( data_pointer[i+k*no_points] & 0x000f ) << 4 );
					else
						 v_byte = (byte)( data_pointer[i+k*no_points] & 0x00ff ) ;
					outportb( latch, (byte)v_byte );
      	  for(xxx=0; xxx<10; xxx++) yyy++;
					count = 0;
					while( (inportb(status) & 1 ) == 1 && count < MAX_TRY ) count++;
					if( count >= MAX_TRY )
					{
						blocked++;
						return AIO_BLOCKED;
					}
			 }
		 }
		 break;
	 case GET_ALL:
		 for( k=0; k<number_of_boards; k++ )
		 {
			 if( card_type == VER0_CARD )
			 {
				order = 0x60;
				no_points = 32;
			 }
			 else
			 {
				order = GET_ALL;
				no_points = boards[k].no_ins;
			 }
			 latch = boards[k].base_adr;
			 status = latch + 1;
			 count = 0;
			 while( ( inportb(status) & 2 ) == 2 && count++ < 5 )
				 v_byte=inportb(latch);
			 outportb( latch, order );
			 for(xxx=0; xxx<10; xxx++) yyy++;
			 count = 0;
			 while( ( ( inportb(status) & 1 ) == 1 ) && count < MAX_TRY ) count++;
			 if( count >= MAX_TRY )
			 {
					blocked++;
					return AIO_BLOCKED;
			 }
			 for(i=0;i<no_points;i++)
			 {
				count = 0;
				while( ( ( inportb(status) & 2 ) != 2 ) && count < MAX_TRY ) count++;
				if( count >= MAX_TRY )
				{
					blocked++;
					return AIO_BLOCKED;
				}
				v_byte = inportb(latch);
				count = 0;
				while( ( ( inportb(status) & 2 ) != 2 ) && count < MAX_TRY ) count++;
				if( count >= MAX_TRY )
				{
					blocked++;
					return AIO_BLOCKED;
				}
				data_pointer[i+k*no_points] = inportb(latch);
				data_pointer[i+k*no_points] = data_pointer[i+k*no_points] + ( v_byte << 8);
//				data_buffer[i+k*32] /= 16;
				for( v_byte=0; v_byte<1000; v_byte++ );
			}
			while( (i=inportb(status) & 2) == 2 )
			{
					v_byte=inportb(latch);
					i=inportb(status);
			}
//			for( i=0; i<10000; i++ );
//			while( ( inportb(status) & 2 ) == 2 ) v_byte=inportb(latch);
		 }
		 break;
	 case SET_RATE:
		 if( card_type == VER0_CARD )
		 {
			 order = 0x80;
		 }
		 else
			 order = SET_RATE;
			 for( k=0; k<number_of_boards; k++ )
			 {
				 latch = boards[k].base_adr;
				 status = latch + 1;
				 count = 0;
				 while( ( inportb(status) & 2 ) == 2 && count++ < 5 ) v_byte=inportb(latch);
				 outportb( latch, order );
				 for(xxx=0; xxx<10; xxx++) yyy++;
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
				 s_time = (uint)( 65536L - ( (long)boards[k].sample_time *
													boards[k].quartz_freq / 12000L ) );
				 v_byte = s_time >> 8;
				 outportb( latch, v_byte );
				 for(xxx=0; xxx<10; xxx++) yyy++;
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
				 v_byte = s_time & 0x00ff;
				 outportb( latch, v_byte );
				 for(xxx=0; xxx<10; xxx++) yyy++;
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
			}
		 break;
	 case DESCRIPTION:
		 if( card_type > VER0_CARD )
		 {
			 order = DESCRIPTION;
			 for( k=0;k<number_of_boards;k++ )
			 {
				 latch = boards[k].base_adr;
				 status = latch + 1;
				 count = 0;
				 while( ( inportb(status) & 2 ) == 2 && count++ < 5 ) v_byte=inportb(latch);
				 outportb( latch, order );
    		 for(xxx=0; xxx<10; xxx++) yyy++;
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
				 outportb( latch, boards[k].in_mask );
				 for(xxx=0; xxx<10; xxx++) yyy++;
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
				 outportb( latch, boards[k].out_mask );
				 for(xxx=0; xxx<10; xxx++) yyy++;
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
			}
		 }
		 else
			 result = FUNCTION_NOT_AVAILABLE;
		 break;
	 case GET_STATUS:
		 if( card_type == VER0_CARD )
		 {
			order = 0xC0;
		 }
		 else
		 {
			order = GET_STATUS;
		 }
		 for( k=0; k<number_of_boards; k++ )
		 {
			 latch = boards[k].base_adr;
			 status = latch + 1;
			 count = 0;
			 while( ( inportb(status) & 2 ) == 2 && count++ < 5 ) v_byte=inportb(latch);
			 outportb( latch, order );
   		 for(xxx=0; xxx<10; xxx++) yyy++;
			 count = 0;
			 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
			 if( count >= MAX_TRY )
			 {
					blocked++;
					return AIO_BLOCKED;
			 }
			 count = 0;
			 while( (inportb(status) & 2) != 2 && count < MAX_TRY ) count++;
			 if( count >= MAX_TRY )
			 {
					blocked++;
					return AIO_BLOCKED;
			 }
			 boards[k].status = (byte)inportb(latch);

			 if( card_type == VER1_CARD )
			 {
				 count = 0;
				 while( (inportb(status) & 2 ) != 2 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
				 boards[k].in_mask = (byte)inportb(latch);
				 count = 0;
				 while( (inportb(status) & 2 ) != 2 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
				 boards[k].out_mask = (byte)inportb(latch);
			 }

//			 while( ( inportb(status) & 2 ) == 2 ) v_byte=inportb(latch);
		 }
		 break;
	 case TEST_INTERFACE:
		 if( card_type == VER0_CARD )
			 order = SPECIAL;
		 else
			 order = TEST_INTERFACE;
			 for( k=0;k<number_of_boards;k++ )
			 {
				 latch = boards[k].base_adr;
				 status = latch + 1;
				 count = 0;
				 while( ( inportb(status) & 2 ) == 2 && count++ < 5 ) v_byte=inportb(latch);
				 outportb( latch, order );
    		 for(xxx=0; xxx<10; xxx++) yyy++;
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
				 if( card_type == VER0_CARD )
				 {
					 order = TEST_INTERFACE;
					 outportb( latch, order );
      		 for(xxx=0; xxx<10; xxx++) yyy++;
					 count = 0;
					 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
					 if( count >= MAX_TRY )
					 {
							blocked++;
							return AIO_BLOCKED;
					 }
				 }
				 for( v_byte=0; v_byte<256; v_byte++ )
				 {
					 outportb( latch, v_byte );
      		 for(xxx=0; xxx<10; xxx++) yyy++;
					 count = 0;
					 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
					 if( count >= MAX_TRY )
					 {
							blocked++;
							return AIO_BLOCKED;
					 }
					 count = 0;
					 while( (inportb(status) & 2) != 2 && count < MAX_TRY ) count++;
					 if( count >= MAX_TRY )
					 {
							blocked++;
							return AIO_BLOCKED;
					 }
					 if( v_byte != inportb(latch) ) return AIO_ERROR;
				 }
			 }
			 break;
	 case RESET_PC:
		 if( card_type == VER0_CARD )
			 order = SPECIAL;
		 else
			 order = RESET_PC;
			 for( k=0;k<number_of_boards;k++ )
			 {
				 latch = boards[k].base_adr;
				 status = latch + 1;
				 count = 0;
				 while( ( inportb(status) & 2 ) == 2 && count++ < 5 ) v_byte=inportb(latch);
				 outportb( latch, order );
     		 for(xxx=0; xxx<10; xxx++) yyy++;
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
				 if( card_type == VER0_CARD )
				 {
					 order = RESET_PC;
					 outportb( latch, order );
					 for(xxx=0; xxx<10; xxx++) yyy++;
					 count = 0;
					 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
					 if( count >= MAX_TRY )
					 {
							blocked++;
							return AIO_BLOCKED;
					 }
				 }
			 }
			 break;
	 case RESET_CARD:
//		 if( card_type == VER1_CARD )
		 {
			 for( k=0;k<number_of_boards;k++ )
			 {
				 latch = boards[k].base_adr+2;
				 status = boards[k].base_adr+1;
				 if( inportb(status) & 0x04 )
				 {
					 v_byte = inportb( latch );	/*Turn ON reset signal*/
					 if( !( inportb(status) & 0x04 ) )
					 count = 0;
					 while( count < MAX_TRY ) count++;
					 v_byte = inportb( latch );  	/*Turn OFF reset signal*/
				 }
				 else
					 v_byte = inportb( latch );  	/*Turn OFF reset signal*/
				 if( inportb(status) & 0x04 )
					result = AIO_OK;
				 else
					result = AIO_ERROR;
			 }
		 }
//		 else
//			result = FUNCTION_NOT_AVAILABLE;
		 break;
	 case WATCHDOG_ON:
		 if( card_type == VER0_CARD )
			 order = SPECIAL;
		 else
			 order = WATCHDOG_ON;
			 for( k=0;k<number_of_boards;k++ )
			 {
				 latch = boards[k].base_adr;
				 status = latch + 1;
				 count = 0;
				 while( ( inportb(status) & 2 ) == 2 && count++ < 5 ) v_byte=inportb(latch);
				 outportb( latch, order );
    		 for(xxx=0; xxx<10; xxx++) yyy++;
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
				 if( card_type == VER0_CARD )
				 {
					 order = WATCHDOG_ON;
					 outportb( latch, order );
      		 for(xxx=0; xxx<10; xxx++) yyy++;
					 count = 0;
					 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
					 if( count >= MAX_TRY )
					 {
							blocked++;
							return AIO_BLOCKED;
					 }
				 }
			 }
			 break;
	 case WATCHDOG_OFF:
		 if( card_type == VER0_CARD )
			 order = SPECIAL;
		 else
			 order = WATCHDOG_OFF;
			 for( k=0;k<number_of_boards;k++ )
			 {
				 latch = boards[k].base_adr;
				 status = latch + 1;
				 count = 0;
				 while( ( inportb(status) & 2 ) == 2 && count++ < 5 ) v_byte=inportb(latch);
				 outportb( latch, order );
    		 for(xxx=0; xxx<10; xxx++) yyy++;
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
				 if( card_type == VER0_CARD )
				 {
					 order = WATCHDOG_OFF;
					 outportb( latch, order );
       		 for(xxx=0; xxx<10; xxx++) yyy++;
					 count = 0;
					 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
					 if( count >= MAX_TRY )
					 {
							blocked++;
							return AIO_BLOCKED;
					 }
				 }
			 }
			 break;
	 case SET_WATCHDOG:
		 if( card_type == VER1_CARD )
			 order = SET_WATCHDOG;
		 else
			order = SPECIAL;
			 for( k=0; k<number_of_boards; k++ )
			 {
				 latch = boards[k].base_adr;
				 status = latch + 1;
				 count = 0;
				 while( ( inportb(status) & 2 ) == 2 && count++ < 5 ) v_byte=inportb(latch);
				 outportb( latch, order );
    		 for(xxx=0; xxx<10; xxx++) yyy++;
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
				 if( card_type == VER0_CARD )
				 {
					 order = SET_WATCHDOG;
					 outportb( latch, order );
      		 for(xxx=0; xxx<10; xxx++) yyy++;
					 count = 0;
					 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
					 if( count >= MAX_TRY )
					 {
							blocked++;
							return AIO_BLOCKED;
					 }
				 }

				 s_time = (uint)( (long)boards[k].watchdog_interval *
													boards[k].quartz_freq/12 * 10000L / 65536L);
				 v_byte = s_time >> 8;
				 outportb( latch, v_byte );
				 for(xxx=0; xxx<10; xxx++) yyy++;
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
				 v_byte = s_time & 0x00ff;
				 outportb( latch, v_byte );
    		 for(xxx=0; xxx<10; xxx++) yyy++;
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
			}
		 break;
	 case GET_ALL_POINTS:
		 if( card_type > VER0_CARD )
		 {
			 order = GET_ALL_POINTS;
			 for( k=0; k < number_of_boards; k++ )
			 {
				 latch = boards[k].base_adr;
				 status = latch + 1;
				 count = 0;
				 while( ( inportb(status) & 2 ) == 2 && count++ < 5 ) v_byte=inportb(latch);
				 outportb( latch, order );
    		 for(xxx=0; xxx<10; xxx++) yyy++;
				 count = 0;
				 while( ( ( inportb(status) & 1 ) == 1 ) && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
				 no_points = 128;
				 for(i=0;i<no_points;i++)
				 {
					count = 0;
					while( ( ( inportb(status) & 2 ) != 2 ) && count < MAX_TRY ) count++;
					if( count >= MAX_TRY )
					{
						blocked++;
						return AIO_BLOCKED;
					}
					v_byte = inportb(latch);
					count = 0;
					while( ( ( inportb(status) & 2 ) != 2 ) && count < MAX_TRY ) count++;
					if( count >= MAX_TRY )
					{
						blocked++;
						return AIO_BLOCKED;
					}
					data_pointer[i+k*no_points] = inportb(latch);
					data_pointer[i+k*no_points] = data_pointer[i+k*no_points] + ( v_byte << 8);
					for( v_byte=0; v_byte<1000; v_byte++ );
				}
				while( (i=inportb(status) & 2) == 2 )
				{
						v_byte=inportb(latch);
						i=inportb(status);
				}
//				for( i=0; i<10000; i++ );
			 }
		 }
		 else
			result = FUNCTION_NOT_AVAILABLE;
		 break;
	 case POWER_TOGGLE:
		 if( card_type > VER0_CARD )
		 {
			 order = POWER_TOGGLE;
			 for( k=0;k<number_of_boards;k++ )
			 {
				 latch = boards[k].base_adr;
				 status = latch + 1;
				 count = 0;
				 while( ( inportb(status) & 2 ) == 2 && count++ < 5 ) v_byte=inportb(latch);
				 outportb( latch, order );
    		 for(xxx=0; xxx<10; xxx++) yyy++;
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
				 if( inportb(status) & 0x08 )
					result = AIO_OK;
				 else
					result = AIO_ERROR;
			 }
		 }
		 else
			result = FUNCTION_NOT_AVAILABLE;
		 break;
	 case VERSION:
			 order = VERSION;
			 for( k=0;k<number_of_boards;k++ )
			 {
				 latch = boards[k].base_adr;
				 status = latch + 1;
				 count = 0;
				 j = inportb(status);
				 while( ( j & 2 ) == 2 && count++ < 5 )
				 {
					v_byte=inportb(latch);
					j = inportb(status);
				 }
				 if( count>=5 )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
				 outportb( latch, order );
				 for(xxx=0; xxx<10; xxx++) yyy++;
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
				 for( k=0; k<12; k++ )
				 {
					 count = 0;
					 while( (inportb(status) & 2) != 2 && count < MAX_TRY ) count++;
					 if( count >= MAX_TRY )
					 {
							blocked++;
							return AIO_BLOCKED;
					 }
					 data_buffer[k] = inportb(latch);
					 if( data_buffer[0] == 'O' ) card_type = VER0_CARD;
					 else
						if( data_buffer[0] == 'N' ) card_type = VER1_CARD;
						else
							if( data_buffer[0] == 'T' ) card_type = VER2_CARD;
				 }
			 }
			 break;
	 case GET_NO_POINTS:
		 if( card_type > VER0_CARD )
		 {
			 order = GET_NO_POINTS;
			 for( k=0;k<number_of_boards;k++ )
			 {
				 latch = boards[k].base_adr;
				 status = latch + 1;
				 count = 0;
				 while( ( inportb(status) & 2 ) == 2 && count++ < 5 ) v_byte=inportb(latch);
				 outportb( latch, order );
    		 for(xxx=0; xxx<10; xxx++) yyy++;
				 count = 0;
				 while( (inportb(status) & 1) == 1 && count < MAX_TRY ) count++;
				 if( count >= MAX_TRY )
				 {
						blocked++;
						return AIO_BLOCKED;
				 }
				 for( k=0; k<18; k++ )
				 {
					 count = 0;
					 while( (inportb(status) & 2) != 2 && count < MAX_TRY ) count++;
					 if( count >= MAX_TRY )
					 {
							blocked++;
							return AIO_BLOCKED;
					 }
					 data_buffer[k] = inportb(latch);
				 }
			 }
		 }
		 else
			result = FUNCTION_NOT_AVAILABLE;
		 break;
	 default:
		 mputs(  "Command error in Aio_Control !" );
		 break;
	}
	return result;
}


/*
void Aio::Controller( byte p_number )
{
	long op, oi, od, ob, err, out_sum, sample_time;
	uint prop, time;
	Str_controller_point *con;
	con = &controllers[p_number];
	prop = con->prop_high * 256 + con->proportional;
	if( SCAN_RATE ) sample_time = 1000 / SCAN_RATE;
	if( con->repeats_per_min ) { if( sample_time ) time = 1 / sample_time; }
	else { if( con->reset ) time = 60 / con->reset; }
	if( prop )
		op = con->action * 100 / prop * ( con->input_value - con->setpoint_value );
	err = con->input_value - con->setpoint_value;
	if( err )
		oi += con->action * con->reset * time / 60 * err;
	if( time )
		od = con->action * sample_time * ( err - con_aux[p_number].old_err ) / time;
	out_sum = op + od + ob;
	if( out_sum > 100 ) out_sum = 100;
	if( out_sum < 0 ) out_sum = 0;
	if( con->reset )
	{
		 out_sum += con_aux[p_number].oi;
		 if( out_sum > 100 )
		 {
				con_aux[p_number].oi -= ( out_sum - 100 );
				out_sum = 100;
		 }
		 if( out_sum < 0 ) { con_aux[p_number].oi -= out_sum; out_sum = 0; }
	}
	else con_aux[p_number].oi = 0;
	con->value = out_sum;
	con_aux[p_number].old_err = err;
}
*/

void Aio::Controller( byte p_number )
{
	long op, oi, od, err, erp, out_sum, sample_time;
//  err = percent of error = ( input_value - setpoint_value ) * 100 /
//																			proportional_band
	uint prop;
	long l,l1;
	Str_controller_point *con;
	con = &controllers[p_number];
	get_point(*((Point *)&con->input), &con->input_value, NULL);
	get_point(*((Point *)&con->setpoint), &con->setpoint_value, NULL);
	od = oi = op = 0;
	prop = con->prop_high * 256 + con->proportional;
//	if( SCAN_RATE ) sample_time = 1000 / SCAN_RATE;
	sample_time = 10L;       // seconds
//	if( con->repeats_per_min ) { if( sample_time ) time = 1 / sample_time; }
//	else { if( con->reset ) time = 60 / con->reset; }
	err = con->input_value - con->setpoint_value;
	erp = 0L;
// proportional term
	if( prop )
		erp = 100L * err / prop;
	if( erp > 100000L ) erp = 100000L;
	if( !con->action )
		op = erp; /*  + */
	else
		op = -erp; /*  - */
// integral term
	l =( con_aux[p_number].old_err + err ) * sample_time / 2;
	l1 = con_aux[p_number].error_area + l;
	if( con_aux[p_number].error_area >= 0 )
	{
	 if(l1 > 8388607L)
		l1 = 8388607L;
	}
	else
	{
	 if( l1 < -8388607L)
		l1 = -8388607L;
	}
	con_aux[p_number].error_area = l1;

	if( con->reset )
	{
		if( !con->action )
			oi = con->reset*con_aux[p_number].error_area;
		else
			oi -= con->reset*con_aux[p_number].error_area;
		if( con->repeats_per_min )
			oi /= 60L;
		else
			oi /= 3600L;
	}
// differential term
	if( con->rate )
	{
		if( !con->action )
			od = con->rate * ( erp - con_aux[p_number].old_err
												* 100 / prop ) / sample_time / 60L;
		else
			od = -con->rate * ( erp - con_aux[p_number].old_err
												* 100 / prop ) / sample_time / 60L;
	}
	out_sum = op + con->bias + od;
//	out_sum /= 1000L;
	if( out_sum > 100000L ) out_sum = 100000L;
	if( out_sum < 0 ) out_sum = 0;
	if( con->reset )
	{
//		 out_sum += con_aux[p_number].oi;
		 out_sum += oi;
		 if( out_sum > 100000L )
		 {
//				con_aux[p_number].oi -= ( out_sum - 100 );
				out_sum = 100000L;
		 }
		 if( out_sum < 0 )
		 {
//			con_aux[p_number].oi -= out_sum;
			out_sum = 0;
		 }
	}
//	else con_aux[p_number].oi = 0;
	con->value = out_sum;
	con_aux[p_number].old_err = err;
}


/*
void Aio::Controller( byte p_number )
{
	long op, oi, od, ob, err, out_sum, sample_time;
	uint prop, time;
	Str_controller_point *con;
	con = &controllers[p_number];
	prop = con->prop_high * 256 + con->proportional;
	if( SCAN_RATE ) sample_time = 1000. / SCAN_RATE;
	if( con->repeats_per_min ) { if( sample_time ) time = 1 / sample_time; }
	else { if( con->reset ) time = 60. / con->reset; }
	if( prop )
		op = con->action * 100. / prop * ( con->input_value - con->setpoint_value );
	err = con->input_value - con->setpoint_value;
	if( err )
		oi += con->action * con->reset * time / 60. * err;
	if( time )
		od = con->action * sample_time * ( err - con_aux[p_number].old_err ) / time;
	out_sum = op + od + ob;
	if( out_sum > 100 ) out_sum = 100;
	if( out_sum < 0 ) out_sum = 0;
	if( con->reset )
	{
		 out_sum += con_aux[p_number].oi;
		 if( out_sum > 100 )
		 {
				con_aux[p_number].oi -= ( out_sum - 100 );
				out_sum = 100;
		 }
		 if( out_sum < 0 ) { con_aux[p_number].oi -= out_sum; out_sum = 0; }
	}
	else con_aux[p_number].oi = 0;
	con->value = out_sum;
	con_aux[p_number].old_err = err;
}
*/

long Aio::test_match( Analog_input_range_equate range, uint raw )
{
	char buffi[30];
	long index;
	long val;
	range--;
	int ran_in = range;
	range /= 2;
	if( raw <= def_tab[range][64] ) return limit[ran_in][1];
	if( raw >= def_tab[range][0] ) return limit[ran_in][0];
	int delta = 32;
	byte end = 0;
	index = 32;
	while( !end )
	{
		if( ( raw >= def_tab[range][index] ) && ( raw <= def_tab[range][index-1] ) )
		{
/*			if( range == V0_5 )
			{
				sprintf( buffi, "index=%4d raw=%4x", index, raw );
				mxyputs( 50, 23, buffi );
			}
*/			index--;
			if( def_tab[range][index] - def_tab[range][index+1] )
				val = limit[ran_in][0] + tab_int[ran_in] *
					( index*100  + (long)(def_tab[range][index] - raw ) * 100 /
					(long)(def_tab[range][index] - def_tab[range][index+1])) / 100;
			return val;
		}
		else
		{
			if( !delta ) end = 1;
			delta /= 2;
			if( raw < def_tab[range][index] ) index += delta;
			else index -= delta;
			if( index <= 0 ) return limit[range][0];
			if( index >= 64 ) return limit[range][1];
		}
	}
//	k = raw & 0x03f;
/*
	float val = def_tab[range][index] + k *
		( def_tab[range][index+1] - def_tab[range][index] );
	return val;		*/
}


long Aio::test_match_custom( Analog_input_range_equate  range, long raw )   // custom tables
{
	int index = 1;
	long val, diff;
	Tbl_point *table_point;
	range -= table1;
	do
	{
		 table_point = &custom_tab[range].table[index];
		 if( ( raw == table_point->value ) )
		 {
				return table_point->unit;
		 }
		 if( ( raw < table_point->value ) &&
				( raw > (table_point-1)->value ) )
			{ index--; break; }
		 else
			index++;
	}
	while( index <= 14 ); /*15*/
	table_point = &custom_tab[range].table[index];
	index = (table_point+1)->value - table_point->value;
//	if( (table_point+1)->value - table_point->value )
	if( index )
	{
/*		val = ( raw - table_point->value ) * 1000 /
			( (table_point+1)->value - table_point->value );*/
		val = ( raw - table_point->value );
		val *= 1000;
		val /= index;
	}
	diff = (table_point+1)->unit - table_point->unit;
//	if( (table_point+1)->unit - table_point->unit )
	if( diff )
	{
/*		val = table_point->unit + val *
			( (table_point+1)->unit - table_point->unit );*/
		val *= diff;
		val /= 1000;
		val += table_point->unit;
	}

	return val;
}

uint Aio::filter( uint sample, byte point )
{
	int num = inputs[point].filter ;
//	num =  (num + 6 ) & 0x0007;
//	num = 1 >> num;
	if( num != in_aux[point].filter_last )
	{
		in_aux[point].filter_sum = in_aux[point].average;
		in_aux[point].filter_sum <<= num;
		in_aux[point].filter_last = num;
	}
/*	if( inputs[point].range == R10K_40_120DegC )
	{
		char bufff[30];
		sprintf( bufff, "sum=%8lu ,num=%d", in_aux[point].filter_sum, num );
		mxyputs( 40, 22, bufff );
	}
*/
	if( num != 1 )
	{
		in_aux[point].filter_sum += (int)(sample - in_aux[point].average );
		in_aux[point].average = (int)
								( (in_aux[point].filter_sum >> num ) & 0x00000fff );
	}
	else in_aux[point].average = sample;
	return in_aux[point].average;
}

long Aio::calibration( byte point )
{
	int i;
	if(inputs[point].calibration_increment)
		if( !inputs[point].calibration_sign )
			i = 1000L;
		else
			i = -1000L;
	else
		if( !inputs[point].calibration_sign )
			i = 100L;
		else
			i = -100L;
	return ( (long)i * (long)inputs[point].calibration );
}

void Aio::convert_in()
{
 int ip;
 byte range;

	for( ip=0; ip<table_bank[IN]; ip++ )
  {
	 range = inputs[ip].range;
		if( !inputs[ip].auto_manual )
		{
			if( range == not_used_input ) inputs[ip].value = 0;
				else
					inputs[ip].value = convert_in_point( ip, range );
		}
	}
}


long Aio::convert_in_point( byte point, byte range )
{
		byte r;
		long val, sample;
		Str_in_point *ins;
		In_aux *inx;
		val = 0;
		r = range - DIG1;
		sample = in_data[point];
		ins = &inputs[point];
		inx = &in_aux[point];
		if( !ins->digital_analog )
		{
			if( range >= ON_OFF  && range <= HIGH_LOW )
				ins->control = ( sample > 2048 ) ? 0 : 1;
			else
				ins->control = ( sample < 2048 ) ? 0 : 1;
			if( range >= custom_digital1 && range <= custom_digital8 )
				ins->control = ( sample < 2048 ) ? 0 : 1;
			val =	ins->control?1000L:0;
		}
		else
		{
			 if( ( range != P0_255p_min ) && ( range != N0_2_32counts ) )
			 {
				if( inx->last - sample > 400 )
				{
					if( !ins->sen_on )
					{
						ins->sen_on = 1;
						inx->ticks = 0;
					}
					else
					{
						if( inx->ticks < 20 )
								inx->ticks++;
					}
				}
				else
				{
					ins->sen_on = 0;
//					ins->pulse_counter = 0;
				}
				if( sample - inx->last > 400 )
				{
					if( !ins->sen_off )
					{
						ins->sen_off = 1;
						inx->ticks = 0;
					}
					else
					{
						 if( inx->ticks < 20 )
									inx->ticks++;
					}
				}
				else
				{
					ins->sen_off = 0;
//					ins->pulse_counter = 0;
				}
			 }
			 else
			 {
					ins->sen_on = 0;
					ins->sen_off = 0;
					val = ins->value;
			 }

			 if( !( ins->sen_off || ins->sen_on ) || ( inx->ticks >= 20 ) )
			 {
				if( ( range != P0_255p_min ) && ( range != N0_2_32counts )
														&& ( range < DIG1 ) )
//				if( ins->filter != 2 )
					sample = filter( sample, point );
				ins->decom = ( ins->sen_off || ins->sen_on ) ? 1 : 0;
				switch( range )
				{
					case Y3K_40_150DegC:
					case Y3K_40_300DegF:
					case R3K_40_150DegC:
					case R3K_40_300DegF:
					case R10K_40_120DegC:
					case R10K_40_250DegF:
					case KM10K_40_120DegC:
					case KM10K_40_250DegF:
					case A10K_50_110DegC:
					case A10K_60_200DegF:
						val = test_match( range, sample );
						break;
					case V0_5:
						val =  sample * const5000 / const4096;
//    	      val =  val * 100L;
//					val /= ;
						break;
					case I0_100Amps:
						val = const100000 * sample / const4096;
						break;
					case I0_20ma:
						val = const20000 * sample / const4096;
						break;
					case I0_20psi:
						val = const20000 * sample / const4096;
						break;
					case N0_2_32counts:
						if( (inx->last < 250) && ( (sample - inx->last) > 400) )
						{
							val += 1000L;
						}
						break;
					case P0_255p_min:
						if( (inx->last < 250) && ( (sample - inx->last) > 400) )
								inx->ticks++;
						 break;
					case N0_3000FPM_0_5V:
						val = const300000 * sample / const4096 * 10;  // avoid overflow
						break;
/*	 	 case N0_3000FPM_1_5V:
		 {
			val = 3000. * ( sample - 819 ) / 819;
			break;
		 }*/
					case P0_100_0_5V:
						val = const100000 * sample / const4096;
						break;
					case P0_100_4_20ma:
						val = ( sample - 819 ) * const100000 / 819;
						break;
/*
					case P0_255p_min:
						val = inx->ticks;
						if( ( sample - inx->last ) > 3276 ) val++;
						inx->ticks++;
						if( time )
							if( inx->ticks >= 60000 / time )
							{
								ins->value = val;
								inx->ticks = 0;
							}
						break;
*/
					case table1:
					case table2:
					case table3:
					case table4:
					case table5:
						val = test_match_custom( range, sample );
						break;
					default:
//	 			printf( " Unappropiate range !!! \n" ); break;
						val = 0;
				}
				val += calibration( point );
				inx->last = sample;
			}
			else val = ins->value;
		}
	 return  val;
}

void Aio::convert_out()
{
	byte point, range, reverse;
	uint val;
	long value, delta;
	Str_out_point *outs;
	outs = outputs;

	for( point=0; point < table_bank[OUT]; point++, outs++ )
	{
		range = outs->range;
		if( range== UNUSED ) outs->value = 0;
		else
		{
			if( !outs->digital_analog )
			{
				if( range >= OFF_ON && range <= LOW_HIGH )
					if( outs->control ) val = 4095;
					else val = 0;
				if( range >= ON_OFF && range <= HIGH_LOW )
					if( outs->control ) val = 0;
					else val = 4095;
				if( range >= custom_digital1 && range <= custom_digital8 )
					if( outs->control ) val = 4095;
					else val = 0;
/*
				if( range >= OFF_ON && range <= HIGH_LOW )
					if( outs->control ) val = 4095;
					else val = 0;
				if( range >= ON_OFF && range <= HIGH_LOW )
					if( outs->control ) val = 0;
					else val = 4095;
				if( range >= custom_digital1 && range <= custom_digital8 )
					if( outs->control ) val = 4095;
					else val = 0;
*/
			}
			else
			{
				/*	char buff[20];
				range = outs->range;
				sprintf( buff, "range = %d", range );
				mxyputs( 23, 10, buff );*/
				switch( range )
				{
					case V0_10:
						val = (uint)( outs->value * const4095 / const10000 );
						break;
					case P0_100_Open:
					case P0_100:
						reverse = 0;
/*
						if( outs->m_del_low < outs->s_del_high )
							delta = outs->s_del_high - outs->m_del_low;
						else
						{
							 delta = outs->m_del_low - outs->s_del_high;
							 reverse++;
						}
*/
						delta = outs->s_del_high - outs->m_del_low;
//    	      delta *= 100;
/*
						if( reverse )
							value = const100000*(long)outs->s_del_high + delta * (long)outs->value;
						else value = const100000*(long)outs->m_del_low + delta * (long)outs->value;
*/
						value = const100000*(long)outs->m_del_low + delta * (long)outs->value;
						value /= 100;
						/*  	        asm {
									mov eax, DWORD PTR value
									mov ebx, eax
									shl eax, 12
									sub eax, ebx
									mov DWORD PTR value, eax
						}
*/
						val = (uint)( value * const4095 / const100000 );
//						value /= ;
//    	      val = (uint) value;
						break;
//					case I_0_20psi:
					case I_0_20ma:
						val = (uint)( outs->value * const4095 / const20000 );
					default:
						val = 0;
						//	printf("Range error !!! " ); break;
				}
			}
			out_data[point] = val;
		}
	}
}

