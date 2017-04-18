/***
*tolower.c - convert character to lower case
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Defines function versions of _tolower() and tolower().
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

/* remove macro defintions of _tolower() and tolower()
 */
#undef  _tolower
#undef  tolower

/* define function-like macro equivalent to _tolower()
 */
#define mklower(c)  ( (c)-'A'+'a' )

/***
*int _tolower(c) - convert character to lower case
*
*Purpose:
*       _tolower() is simply a function version of the macro of the same name.
*
*Entry:
*       c - int value of character to be converted
*
*Exit:
*       returns int value of lower case representation of c
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _tolower (
        int c
        )
{
        return(mklower(c));
}

/***
*int tolower(c) - convert character to lower case
*
*Purpose:
*       tolower() is simply a function version of the macro of the same name.
*
*Entry:
*       c - int value of character to be converted
*
*Exit:
*       if c is an upper case letter, returns int value of lower case
*       representation of c. otherwise, it returns c.
*
*Exceptions:
*
*******************************************************************************/


int __cdecl tolower (
        int c
        )
{
#if !defined (_MAC)

#ifdef _MT
        int local_lock_flag;

        if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE)
        {
            if ( (c >= 'A') && (c <= 'Z') )
                c = c + ('a' - 'A');
            return c;
        }

        _lock_locale( local_lock_flag )

        c = _tolower_lk(c);

        _unlock_locale( local_lock_flag )

        return c;

}

/***
*int _tolower_lk(c) - convert character to lower case
*
*Purpose:
*       Multi-thread function only! Non-locking version of tolower.
*
*Entry:
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _tolower_lk (
        int c
        )
{

#endif  /* _MT */

        int size;
        unsigned char inbuffer[3];
        unsigned char outbuffer[3];

        if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE)
        {
            if ( (c >= 'A') && (c <= 'Z') )
                c = c + ('a' - 'A');
            return c;
        }

        /* if checking case of c does not require API call, do it */
        if (c < 256)
        {
            if (!isupper(c))
            {
                return c;
            }
        }

        /* convert int c to multibyte string */
        if (isleadbyte(c >> 8 & 0xff))
        {
            inbuffer[0] = (c >> 8 & 0xff); /* put lead-byte at start of str */
            inbuffer[1] = (unsigned char)c;
            inbuffer[2] = 0;
            size = 2;
        } else {
            inbuffer[0] = (unsigned char)c;
            inbuffer[1] = 0;
            size = 1;
        }

        /* convert to lowercase */
        if ( 0 == (size = __crtLCMapStringA( __lc_handle[LC_CTYPE],
                                             LCMAP_LOWERCASE,
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

        return(isupper(c) ? mklower(c) : c);

#endif  /* !defined (_MAC) */
}
