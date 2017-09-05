// ********************** START OF PORTABLE.H **********************
//
//
//
// This header file contains the macro definitions needed to
// provide portability across various compilers.
//

#ifndef _PORTABLE_DOT_H
#define _PORTABLE_DOT_H

#if defined(__TURBOC__) && (__TURBOC__ < 0x400 )
#define COMPILER             "Borland C++ 2.0/Turbo C++ 1.0"
#define INPUT( port )        inportb( port )
#define OUTPUT( port, data ) (void) outportb( port, data )
#define CLI()                disable()
#define STI()                enable()
#define UNUSED( a )          if ( a != a ) a = 0
#define INTERRUPT            far interrupt
#define FAR                  far
#ifdef __cplusplus
// #include <iostream.h>
#endif  // #ifdef __cplusplus
#endif  // #ifdef __BORLANDC__

#if defined(__TURBOC__) && (__TURBOC__ >= 0x400 )
#define COMPILER             "Borland C++ 3.0/Turbo C++ 3.0"
#define INPUT( port )        inportb( port )
#define OUTPUT( port, data ) (void) outportb( port, data )
#define CLI()                disable()
#define STI()                enable()
#define UNUSED( a )          (void) a
#define INTERRUPT            _far _interrupt
#define DELETE_ARRAY
#define FAR                  _far
#ifdef __cplusplus
#include <iostream.h>
#endif  // #ifdef __cplusplus
#endif  // #ifdef __BORLANDC__

#if defined(__TSC__)
#define COMPILER             "Topspeed C++"
#define INPUT( port )        inp( port )
#define OUTPUT( port, data ) (void) outp( port, data )
#define CLI()                disable()
#define STI()                enable()
#define UNUSED( a )          if ( a != a ) a = 0
#define INTERRUPT            far interrupt
#define FAR                  far
#ifdef __cplusplus
#include <iostream.h>
#endif  // #ifdef __cplusplus
#endif  // #ifdef __TSC__

#ifdef __ZTC__
#if ( __ZTC__ < 0x300 )
#define COMPILER             "Zortech C++ 2.x"
#else
#define COMPILER             "Zortech C++ 3.x"
#endif
#define INPUT( port )        inp( port )
#define OUTPUT( port, data ) outp( port, data )
#define CLI()                int_off()
#define STI()                int_on()
#define UNUSED( a )
#define INTERRUPT            _cdecl
#define FAR                  _far
#ifdef __cplusplus
#if ( __ZTC__ < 0x300 )
#include <stream.hpp>
#else
#include <iostream.hpp>
#endif
#endif  // #ifdef __cplusplus
#include <int.h>
#endif  // #ifdef __ZTC__

#ifdef _MSC_VER
#define COMPILER             "Microsoft C/C++"
#define INPUT( port )        _inp( port )
#define OUTPUT( port, data ) (void) _outp( port, data )
#define CLI()                _disable()
#define STI()                _enable()
#define UNUSED( a )          (void) a
#define INTERRUPT            __far __interrupt
#define FAR                  __far
#define DELETE_ARRAY
#pragma check_stack( off )
#pragma warning( disable : 4505 )
#ifdef __cplusplus
#include <iostream.h>
#endif  // #ifdef __cplusplus
#include <conio.h>
#endif  // #ifdef _MSC_VER

#endif  // #ifndef _PORTABLE_DOT_H

// ************************ END OF PORTABLE.H ***********************

