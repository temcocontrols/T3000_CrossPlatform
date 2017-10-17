// ******************** START OF PCIRQ.CPP ********************
//
//
//
// This module contains the interrupt management code.
// ConnectToIRQ() is called to establish an interrupt handler
// function, DisconnectFromIRQ() is called to break the
// connection.  The funny parameter passed to all of the isr
// routines is there because of the way Zortech calls interrupt
// handlers.  There are several places in this module where you
// may see casts to type NEW_HANDLER that appear unnecessary.
// They are there strictly to mollify Turbo C++ 1.0.

#ifdef SERIAL_COMM

#include <dos.h>
#include "portable.h"
#include "pcirq.h"

#ifndef __ZTC__

struct INT_DATA {
    void *dummy;
};

#endif

typedef void ( INTERRUPT *OLD_HANDLER )( void );
typedef int ( INTERRUPT *NEW_HANDLER )( struct INT_DATA *pd );

// Prototypes for all the handlers defined here

int INTERRUPT isr2( struct INT_DATA *pd );
int INTERRUPT isr3( struct INT_DATA *pd );
int INTERRUPT isr4( struct INT_DATA *pd );
int INTERRUPT isr5( struct INT_DATA *pd );
int INTERRUPT isr7( struct INT_DATA *pd );
int INTERRUPT isr10( struct INT_DATA *pd );
int INTERRUPT isr11( struct INT_DATA *pd );
int INTERRUPT isr15( struct INT_DATA *pd );
int INTERRUPT int1b( struct INT_DATA *pd );
int INTERRUPT int23( struct INT_DATA *pd );

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
// instruction and then exiting.  The "return 1" is necessary for
// Zortech's interrupt handlers.  If a "return 0" is used, the
// handler will then chain to the old interrupt, which we don't
// want.

int INTERRUPT isr2( struct INT_DATA *pd )
{
    UNUSED( pd );
    irq_data[ 0 ].isr_routine( irq_data[ 0 ].isr_data );
    CLI();
    OUTPUT( 0x20, 0x20 );
    return 1;
}

int INTERRUPT isr3( struct INT_DATA *pd )
{
    UNUSED( pd );
    irq_data[ 1 ].isr_routine( irq_data[ 1 ].isr_data );
    CLI();
    OUTPUT( 0x20, 0x20 );
    return 1;
}

int INTERRUPT isr4( struct INT_DATA *pd )
{
    UNUSED( pd );
    irq_data[ 2 ].isr_routine( irq_data[ 2 ].isr_data );
    CLI();
    OUTPUT( 0x20, 0x20 );
    return 1;
}


int INTERRUPT isr5( struct INT_DATA *pd )
{
    UNUSED( pd );
    irq_data[ 3 ].isr_routine( irq_data[ 3 ].isr_data );
    CLI();
    OUTPUT( 0x20, 0x20 );
    return 1;
}

int INTERRUPT isr7( struct INT_DATA *pd )
{
    UNUSED( pd );
    irq_data[ 4 ].isr_routine( irq_data[ 4 ].isr_data );
    CLI();
    OUTPUT( 0x20, 0x20 );
    return 1;
}


// These routines have to send an EOI to the second 8250 PIC
// as well as the first.

int INTERRUPT isr10( struct INT_DATA *pd )
{
    UNUSED( pd );
    irq_data[ 5 ].isr_routine( irq_data[ 5 ].isr_data );
    CLI();
    OUTPUT( 0xa0, 0x20 );
    OUTPUT( 0x20, 0x20 );
    return 1;
}

int INTERRUPT isr11( struct INT_DATA *pd )
{
    UNUSED( pd );
    irq_data[ 6 ].isr_routine( irq_data[ 6 ].isr_data );
    CLI();
    OUTPUT( 0xa0, 0x20 );
    OUTPUT( 0x20, 0x20 );
    return 1;
}

int INTERRUPT isr15( struct INT_DATA *pd )
{
    UNUSED( pd );
    irq_data[ 7 ].isr_routine( irq_data[ 7 ].isr_data );
    CLI();
    OUTPUT( 0xa0, 0x20 );
    OUTPUT( 0x20, 0x20 );
    return 1;
}

// The two control-break vectors do nothing, so that Control-C
// and Contrl-Break both have no effect on our program.

int INTERRUPT int1b( struct INT_DATA *pd )
{
    UNUSED( pd );
    return 1;
}

int INTERRUPT int23( struct INT_DATA *pd )
{
    UNUSED( pd );
    return 1;
}


// This utility routine is only used internally to these
// routines.  It sets control of the given interrupt number to
// the handler specifified as a parameter.  It returns the
// address of the old handler to the caller, so it can be stored
// for later restoration.  Note that Zortech stores the old
// handler internally, so we just return a 0.

OLD_HANDLER HookVector( int interrupt_number, NEW_HANDLER new_handler )
{
#ifdef __ZTC__
    int_intercept( interrupt_number, new_handler, 0 );
    return 0;
#else  // #ifdef __ZTC__
    union REGS r;
    struct SREGS s = { 0, 0, 0, 0 };
    OLD_HANDLER old_handler = 0;

    r.h.al = (unsigned char) interrupt_number;
    r.h.ah = 0x35;
    int86x( 0x21, &r, &r, &s );
    *( (unsigned FAR *) old_handler + 1 ) = s.es;
    *( (unsigned FAR *) old_handler ) = r.x.bx;
    s.ds = FP_SEG( new_handler );
    r.x.dx = FP_OFF( new_handler );
    r.h.al = (unsigned char) interrupt_number;
    r.h.ah = 0x25;
    int86x( 0x21, &r, &r, &s );
    return old_handler;
#endif // #ifdef __ZTC__ ... #else
}

// When we are done with an IRQ, we restore the old handler
// here.  Note once again that Zortech does this internally, so
// we don't have to.

void UnHookVector( int interrupt_number, OLD_HANDLER old_handler )
{
#ifdef __ZTC__
   int_restore( interrupt_number );
#else // #ifdef __ZTC__
    union REGS r;
    struct SREGS s = { 0, 0, 0, 0 };

    s.ds = FP_SEG( old_handler );
    r.x.dx = FP_OFF( old_handler );
    r.h.al = (unsigned char) interrupt_number;
    r.h.ah = 0x25;
    int86x( 0x21, &r, &r, &s );
#endif // #ifdef __ZTC__ ... #else
}

// When we have taken over an interrupt, we don't want
// keyboard breaks to cause us to exit without properly restoring
// vectors.  This routine takes over the DOS and BIOS
// control-break routines, and sets the DOS BREAK flag to 0.  The
// old state of all these variables is saved off so it can be
// restored when the last interrupt routine is restored.

void TrapKeyboardBreak( void )
{
    union REGS r;

    old_int1b = HookVector( 0x1b, (NEW_HANDLER) int1b );
    old_int23 = HookVector( 0x23, (NEW_HANDLER) int23 );
    r.h.ah = 0x33;
    r.h.al = 0;
    int86( 0x21, &r, &r );
    old_dos_break_state = r.h.dl;
    r.h.ah = 0x33;
    r.h.al = 1;
    r.h.dl = 0;
    int86( 0x21, &r, &r );
}

// When the last interrupt is restored, we can set the
// control-break vectors back where they belong, and restore the
// old setting of the DOS break flag.

void RestoreKeyboardBreak( void )
{
    union REGS r;

    UnHookVector( 0x1b, old_int1b );
    UnHookVector( 0x23, old_int23 );
    r.h.ah = 0x33;
    r.h.al = 1;
    r.h.dl = old_dos_break_state;
    int86( 0x21, &r, &r );
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

    temp = INPUT( pic_address + 1 );
    irq_data[ i ].old_pic_enable_bit = temp & pic_mask;
    OUTPUT( pic_address + 1, temp & ~pic_mask );
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

    temp = INPUT( pic_address + 1 );
    temp &= ~pic_mask;
    temp |= irq_data[ i ].old_pic_enable_bit;
    OUTPUT( pic_address + 1, temp );

    UnHookVector( interrupt_number, irq_data[ i ].old_isr );

    if ( --count == 0 )
	RestoreKeyboardBreak();
    return 1;
}
// *********************** END OF PCIRQ.CPP ***********************

#endif