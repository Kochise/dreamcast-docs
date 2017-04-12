/***
*toupper.c - convert character to uppercase
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Defines function versions of _toupper() and toupper().
*
*******************************************************************************/


#include <cruntime.h>
#include <ctype.h>
#include <stddef.h>

#ifndef _MAC
#include <locale.h>
#include <setlocal.h>
#include <mtdll.h>
#include <awint.h>
#endif  /* _MAC */

/* remove macro definitions of _toupper() and toupper()
 */
#undef  _toupper
#undef  toupper

/* define function-like macro equivalent to _toupper()
 */
#define mkupper(c)  ( (c)-'a'+'A' )

/***
*int _toupper(c) - convert character to uppercase
*
*Purpose:
*       _toupper() is simply a function version of the macro of the same name.
*
*Entry:
*       c - int value of character to be converted
*
*Exit:
*       returns int value of uppercase representation of c
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _toupper (
        int c
        )
{
        return(mkupper(c));
}


/***
*int toupper(c) - convert character to uppercase
*
*Purpose:
*       toupper() is simply a function version of the macro of the same name.
*
*Entry:
*       c - int value of character to be converted
*
*Exit:
*       if c is a lower case letter, returns int value of uppercase
*       representation of c. otherwise, it returns c.
*
*Exceptions:
*
*******************************************************************************/


int __cdecl toupper (
    int c
    )
{
#if !defined (_MAC)

#ifdef _MT

        int local_lock_flag;

        if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE)
        {
            if ( (c >= 'a') && (c <= 'z') )
                c = c - ('a' - 'A');
            return c;
        }

        _lock_locale( local_lock_flag )

        c = _toupper_lk(c);

        _unlock_locale( local_lock_flag )

        return c;
}


/***
*int _toupper_lk(c) - convert character to uppercase
*
*Purpose:
*       Multi-thread function! Non-locking version of toupper.
*
*Entry:
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/


int __cdecl _toupper_lk (
        int c
        )
{

#endif  /* _MT */

        int size;
        unsigned char inbuffer[3];
        unsigned char outbuffer[3];

        if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE)
        {
            if ( (c >= 'a') && (c <= 'z') )
                c = c - ('a' - 'A');
            return c;
        }

        /* if checking case of c does not require API call, do it */
        if (c < 256) {
            if (!islower(c))
            {
                return c;
            }
        }

        /* convert int c to multibyte string */
        if (isleadbyte(c >> 8 & 0xff)) {
            inbuffer[0] = (c >> 8 & 0xff); /* put lead-byte at start of str */
            inbuffer[1] = (unsigned char)c;
            inbuffer[2] = 0;
            size = 2;
        } else {
            inbuffer[0] = (unsigned char)c;
            inbuffer[1] = 0;
            size = 1;
        }

        /* convert wide char to lowercase */
        if ( 0 == (size = __crtLCMapStringA( __lc_handle[LC_CTYPE],
                                             LCMAP_UPPERCASE,
                                             inbuffer,
                                             size,
                                             outbuffer,
                                             3,
                                             0,
                                             TRUE)) )
        {
            return c;
        }

        /* construct integer return value */
        if (size == 1)
            return ((int)outbuffer[0]);
        else
            return ((int)outbuffer[0] | ((int)outbuffer[1] << 8));

#else  /* !defined (_MAC) */

        return(islower(c) ? mkupper(c) : c);

#endif  /* !defined (_MAC) */
}
