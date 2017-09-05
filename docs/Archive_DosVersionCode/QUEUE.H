// ********************** START OF QUEUE.H **********************
//
//
//
// This header file contains the definitions needed to use the
// Queue class.  This class is used for both the input and
// output queues used by class PC8250.  Most of the functions
// in this class are defined as inline, as speed is essential
// in the interrupt service routine.  Those that aren't can
// be found in QUEUE.CPP
//

#ifndef _QUEUE_DOT_H
#define _QUEUE_DOT_H

const unsigned int QueueSize = 1024;
const unsigned int HighWaterMark = ( QueueSize * 3 ) / 4;
const unsigned int LowWaterMark = QueueSize / 4;

class Queue
{
	 private :
		  volatile unsigned int head_index;
		  volatile unsigned int tail_index;
		  volatile unsigned char buffer[ QueueSize ];
	 public :
		  Queue( void );
		  int Insert( unsigned char c );
		  int Remove( void );
		  int Peek( unsigned char *buffer, int count );
		  int InUseCount( void );
		  int FreeCount( void );
		  int Head( void ) { return head_index; }
		  int Tail( void ) { return tail_index; }
		  void Clear( void );
};

inline Queue::Queue( void )
{
    head_index = 0;
    tail_index = 0;
}

inline int Queue::Insert( unsigned char c )
{
    unsigned int temp_head = head_index;

	 buffer[ temp_head++ ] = c;
    if ( temp_head >= QueueSize )
        temp_head = 0;
    if ( temp_head == tail_index )
		 return 0;
	 head_index = temp_head;
	 return 1;
}

inline int Queue::Remove( void )
{
		unsigned char cc;
		if ( head_index == tail_index )
				return( -1 );
		cc = buffer[ tail_index++ ];
		if ( tail_index >= QueueSize )
				tail_index = 0;
		return cc;
}

inline int Queue::InUseCount( void )
{
    if ( head_index >= tail_index )
		{
			return head_index - tail_index;
		}
		else
		{
			return head_index + QueueSize - tail_index;
		}	
}

inline int Queue::FreeCount( void )
{
    return QueueSize - 1 - InUseCount();
}

inline void Queue::Clear( void )
{
    tail_index = head_index;
}

#endif  // #ifndef _QUEUE_DOT_H

// ************************ END OF QUEUE.H ***********************

