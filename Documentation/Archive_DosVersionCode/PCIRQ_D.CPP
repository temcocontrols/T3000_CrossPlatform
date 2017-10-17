// ******************** START OF PCIRQ.CPP ********************
//
// This module contains the interrupt management code.
// ConnectToIRQ() is called to establish an interrupt handler
// function, DisconnectFromIRQ() is called to break the
// connection.
//
//*************************************************************

#ifdef SERIAL_COMM

#include <dos.h>
//#include "portable.h"
#include <windows.h>
#include "t3000def.h"
#include "pcirq.h"
#pragma inline
//void interrupt ( *oldhandler)(__CPPARGS);

typedef void ( interrupt *OLD_HANDLER )( ... );

//typedef int ( interrupt *NEW_HANDLER )( struct INT_DATA *pd );
typedef int ( interrupt *NEW_HANDLER )( ... );

// Prototypes for all the handlers defined here

int interrupt isr2( void );
int interrupt isr3( void );
int interrupt isr4( void );
int interrupt isr5( void );
int interrupt isr7( void );
int interrupt isr10( void );
int interrupt isr11( void );
int interrupt isr15( void );
int interrupt int1b( void );
int interrupt int23( void );

// When any IRQs are hooked by one of our routines, the IRQ
// code disables control-break termination by taking over the two
// control-break vectors.  The saved control-break state is
// stored in the following three variables.

static OLD_HANDLER old_int1b;
static OLD_HANDLER old_int23;
static unsigned char old_dos_break_state;

// A count of the number of handlers currently in use.

static int count = 0;

// This structure keeps track of the state of each of the
// eight possible IRQ lines our program can take over.  This
// includes the address of the new handler, the old handler, and
// most importantly, the data pointer passed to the new handler
// when it is invoked.

struct {
	 irq_name irq;
	 void *isr_data;
	 void ( *isr_routine)( void *isr_data );
	 NEW_HANDLER handler;
	 OLD_HANDLER old_isr;
	 int old_pic_enable_bit;
} irq_data[] = { { IRQ2,  0, 0, (NEW_HANDLER) isr2,  0, 0 },
					  { IRQ3,  0, 0, (NEW_HANDLER) isr3,  0, 0 },
						{ IRQ4,  0, 0, (NEW_HANDLER) isr4,  0, 0 },
						{ IRQ5,  0, 0, (NEW_HANDLER) isr5,  0, 0 },
						{ IRQ7,  0, 0, (NEW_HANDLER) isr7,  0, 0 },
						{ IRQ10, 0, 0, (NEW_HANDLER) isr10, 0, 0 },
						{ IRQ11, 0, 0, (NEW_HANDLER) isr11, 0, 0 },
						{ IRQ15, 0, 0, (NEW_HANDLER) isr15, 0, 0 }
					};

// All of the new ISR handlers are called when the interrupt
// occurs.  All they do is call the hooked routine, passing it a
// pointer to the data block it asked for in the ConnectToIRQ()
// routine.  When this is done, they take care of issuing the EOI
// instruction and then exiting.  If a "return 0" is used, the
// handler will then chain to the old interrupt, which we don't
// want.

int interrupt isr2( void )
{
	 irq_data[ 0 ].isr_routine( irq_data[ 0 ].isr_data );
	 disable();
//	 outportb( 0x20, 0x20 );
		asm mov al, 20h
		asm out 20h, al
		asm jmp $+2
		asm nop
//	 return 1;
}

int interrupt isr3( void )
{
//	 UNUSED( pd );
	 irq_data[ 1 ].isr_routine( irq_data[ 1 ].isr_data );
	 disable();
		asm mov al, 20h
		asm out 20h, al
		asm jmp $+2
		asm nop
//	 outportb( 0x20, 0x20 );
//	 return 1;
}

int interrupt isr4( void )
{
//	 UNUSED( pd );
	 irq_data[ 2 ].isr_routine( irq_data[ 2 ].isr_data );
	 disable();
//	 outportb( 0x20, 0x20 );
		asm mov al, 20h
		asm out 20h, al
		asm jmp $+2
		asm nop
//	 return 1;
}

int interrupt isr5( void )
{
//	 UNUSED( pd );
	 irq_data[ 3 ].isr_routine( irq_data[ 3 ].isr_data );
	 disable();
//	 outportb( 0x20, 0x20 );
		asm mov al, 20h
		asm out 20h, al
		asm jmp $+2
		asm nop
//	 return 1;
}

int interrupt isr7( void )
{
//    UNUSED( pd );
	 irq_data[ 4 ].isr_routine( irq_data[ 4 ].isr_data );
	 disable();
//	 outportb( 0x20, 0x20 );
		asm mov al, 20h
		asm out 20h, al
		asm jmp $+2
		asm nop
//	 return 1;
}


// These routines have to send an EOI to the second 8250 PIC
// as well as the first.

int interrupt isr10( void )
{
//	 UNUSED( pd );
	 irq_data[ 5 ].isr_routine( irq_data[ 5 ].isr_data );
	 disable();
//	 outportb( 0xa0, 0x20 );
		asm mov al, 20h
		asm out 0a0h, al
		asm jmp $+2
		asm nop
//	 outportb( 0x20, 0x20 );
		asm out 20h,al
		asm jmp $+2
		asm nop
//	 return 1;
}

int interrupt isr11( void )
{
//	 UNUSED( pd );
	 irq_data[ 6 ].isr_routine( irq_data[ 6 ].isr_data );
	 disable();
//	 outportb( 0xa0, 0x20 );
		asm mov al, 20h
		asm out 0a0h, al
		asm jmp $+2
		asm nop
//	 outportb( 0x20, 0x20 );
		asm out 20h,al
		asm jmp $+2
		asm nop
//	 return 1;
}

int interrupt isr15( void )
{
//	 UNUSED( pd );
	 irq_data[ 7 ].isr_routine( irq_data[ 7 ].isr_data );
	 disable();
//	 outportb( 0xa0, 0x20 );
		asm mov al, 20h
		asm out 0a0h, al
		asm jmp $+2
		asm nop
//	 outportb( 0x20, 0x20 );
		asm out 20h,al
		asm jmp $+2
		asm nop
//	 return 1;
}

// The two control-break vectors do nothing, so that Control-C
// and Contrl-Break both have no effect on our program.

int interrupt int1b( void )
{
//	 UNUSED( pd );
	 return 1;
}

int interrupt int23( void )
{
//	 UNUSED( pd );
	 return 1;
}


// This utility routine is only used internally to these
// routines.  It sets control of the given interrupt number to
// the handler specifified as a parameter.  It returns the
// address of the old handler to the caller, so it can be stored
// for later restoration.

OLD_HANDLER HookVector( int interrupt_number, NEW_HANDLER new_handler )
{
	 OLD_HANDLER old_handler = 0;

	old_handler = (void (interrupt *)( ... ))getvect( interrupt_number );
/*
	asm {
		mov ax, 0200h
		mov bx, interrupt_number
		int 31h
		mov old_handler+2, cx
		mov old_handler, dx
		}
*/
	setvect( interrupt_number, (void interrupt (*)( ... ))new_handler );
/*
	asm {
		mov ax, 0303h
		lds si, new_handler
		les di, call_back_buffer
		int 31h
		jc err
		mov ax, 0201h
		mov bx, interrupt_number
		int 31h
		}
*/
	return old_handler;
}

// When we are done with an IRQ, we restore the old handler
// here.

void UnHookVector( int interrupt_number, OLD_HANDLER old_handler )
{

	setvect( interrupt_number, (void interrupt (*)( ... ))old_handler );
/*
	asm {
		mov cx, old_handler+2
		mov dx, old_handler
		mov ax, 0201h
		mov bx, interrupt_number
		int 31h
		}
*/
}

// When we have taken over an interrupt, we don't want
// keyboard breaks to cause us to exit without properly restoring
// vectors.  This routine takes over the DOS and BIOS
// control-break routines, and sets the DOS BREAK flag to 0.  The
// old state of all these variables is saved off so it can be
// restored when the last interrupt routine is restored.

void TrapKeyboardBreak( void )
{

	 old_int1b = HookVector( 0x1b, (NEW_HANDLER) int1b );
	 old_int23 = HookVector( 0x23, (NEW_HANDLER) int23 );
	asm {
		mov ax, 3300h
		int 21h
		mov old_dos_break_state, dl
		mov ax, 3301h
		mov dl, 0
		int 21h
		}
}

// When the last interrupt is restored, we can set the
// control-break vectors back where they belong, and restore the
// old setting of the DOS break flag.

void RestoreKeyboardBreak( void )
{
	 UnHookVector( 0x1b, old_int1b );
	 UnHookVector( 0x23, old_int23 );
	 asm {
		mov ax,3301h
		mov dl, old_dos_break_state
		int 21h
	 }
}

// When connecting to an IRQ, I pass it an irq number, plus a
// pointer to a function that will handle the interrupt.  The
// function gets passed a pointer to a data block of its choice,
// which will vary depending on what type of interrupt is being
// handled.

RS232Error ConnectToIrq( irq_name irq,
			 void *isr_data,
			 void ( *isr_routine )( void *isr_data ) )
{
	 int i;
	 int pic_mask;
	 int pic_address;
	 int interrupt_number;
	 int temp;

	 for ( i = 0 ; ; i++ ) {
	if ( irq_data[ i ].irq == irq )
		 break;
	if ( irq_data[ i ].irq == IRQ15 )
		 return RS232_ILLEGAL_IRQ;
	 }
	 if ( irq_data[ i ].isr_routine != 0 )
	return RS232_IRQ_IN_USE;
	 if ( count++ == 0 )
	TrapKeyboardBreak();
	 irq_data[ i ].isr_data = isr_data;
	 irq_data[ i ].isr_routine = isr_routine;

	 pic_mask = 1 << ( irq % 8 );
	 if ( irq < IRQ8 ) {
	pic_address = 0x20;
		  interrupt_number = irq + 8;
	 } else {
		  interrupt_number = irq + 104;
		  pic_address = 0xa0;
	 }
	 irq_data[ i ].old_isr = HookVector( interrupt_number,
													 irq_data[ i ].handler );

	 temp = inportb( pic_address + 1 );
	 irq_data[ i ].old_pic_enable_bit = temp & pic_mask;
	 outportb( pic_address + 1, temp & ~pic_mask );
	 return RS232_SUCCESS;
}

// This routine restores an old interrupt vector.

int DisconnectFromIRQ( irq_name irq )
{
	 int i;
	 int pic_mask;
	 int pic_address;
	 int interrupt_number;
	 int temp;

	 for ( i = 0 ; ; i++ ) {
		  if ( irq_data[ i ].irq == irq )
				break;
		  if ( irq_data[ i ].irq == IRQ15 )
				return 0;
	 }
	 if ( irq_data[ i ].isr_routine == 0 )
	return 0;

	 irq_data[ i ].isr_data = 0;
	 irq_data[ i ].isr_routine = 0;

	 pic_mask = 1 << ( irq % 8 );
	 if ( irq < IRQ8 ) {
		  pic_address = 0x20;
		  interrupt_number = irq + 8;
	 } else {
		  interrupt_number = irq + 104;
		  pic_address = 0xa0;
	 }

	 temp = inportb( pic_address + 1 );
	 temp &= ~pic_mask;
	 temp |= irq_data[ i ].old_pic_enable_bit;
	 outportb( pic_address + 1, temp );

	 UnHookVector( interrupt_number, irq_data[ i ].old_isr );

	 if ( --count == 0 )
	RestoreKeyboardBreak();
	 return 1;
}
// *********************** END OF PCIRQ.CPP ***********************

#endif