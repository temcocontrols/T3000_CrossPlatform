// ******************** START OF QUEUE.CPP ********************
//
//
//
// Most of the queue class functions are defined in QUEUE.H as
// inline for speed.  This routine probably won't generate inline
// code with most compilers, and it is not used in the ISR, so
// speed is not as critical.  Thus, it gets defined normally.

#ifdef SERIAL_COMM


#include "portable.h"
#include "queue.h"

int Queue::Peek( unsigned char *buf, int count )
{
		unsigned int index = tail_index;
		int total = 0;

    while ( total < count && index != head_index ) {
				 *buf++ = buffer[ index++ ];
         if ( index >= QueueSize )
             index = 0;
         total++;
    }
    return total;
}
// *********************** END OF QUEUE.CPP ***********************

#endif