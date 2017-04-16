/***
*putch.c - contains the _putch() routine
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved
*
*Purpose:
*       The routine "_putch()" writes a single character to the console.
*
*       NOTE: In real-mode MS-DOS the character is actually written to standard
*       output, and is therefore redirected when standard output is redirected.
*       However, under Win32 console mode, the character is ALWAYS written
*       to the console, even when standard output has been redirected.
*
*******************************************************************************/

#include <cruntime.h>
#include <oscalls.h>
#include <conio.h>
#include <internal.h>
#include <mtdll.h>
#include <stdio.h>

/*
 * declaration for console handle
 */
extern int _confh;

/***
*int _putch(c) - write a character to the console
*
*Purpose:
*       Calls WriteConsole to output the character
*       Note: in Win32 console mode always writes to console even
*       when stdout redirected
*
*Entry:
*       c - Character to be output
*
*Exit:
*       If an error is returned from WriteConsole
*           Then returns EOF
*       Otherwise
*           returns character that was output
*
*Exceptions:
*
*******************************************************************************/

#ifdef _MT
/* normal version lock and unlock the console, and then call the _lk version
   which directly accesses the console without locking. */

int __cdecl _putch (
        int c
        )
{
        int ch;

        _mlock(_CONIO_LOCK);            /* secure the console lock */
        ch = _putch_lk(c);              /* output the character */
        _munlock(_CONIO_LOCK);          /* release the console lock */

        return ch;
}
#endif  /* _MT */

/* define version which accesses the console directly - normal version in
   non-_MT situations, special _lk version in _MT */

#ifdef _MT
int __cdecl _putch_lk (
#else  /* _MT */
int __cdecl _putch (
#endif  /* _MT */
        int c
        )
{
        /* can't use ch directly unless sure we have a big-endian machine */
        unsigned char ch = (unsigned char)c;
        ULONG num_written;

        /*
         * _confh, the handle to the console output, is created the
         * first time that either _putch() or _cputs() is called.
         */

        if (_confh == -2)
            __initconout();

        /* write character to console file handle */

        if ( (_confh == -1) || !WriteConsole( (HANDLE)_confh,
                                              (LPVOID)&ch,
                                              1,
                                              &num_written,
                                              NULL )
           )
                /* return error indicator */
                return EOF;

        return ch;
}
