/***
*rotl.c - rotate an unsigned integer left
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _rotl() - performs a rotate left on an unsigned integer.
*
*******************************************************************************/


#include <cruntime.h>
#include <stdlib.h>
#include <limits.h>

#ifdef _MSC_VER
#pragma function(_lrotl,_rotl)
#endif  /* _MSC_VER */

#if UINT_MAX != 0xffffffff
#error This module assumes 32-bit integers
#endif  /* UINT_MAX != 0xffffffff */

#if UINT_MAX != ULONG_MAX
#error This module assumes sizeof(int) == sizeof(long)
#endif  /* UINT_MAX != ULONG_MAX */

/***
*unsigned _rotl(val, shift) - int rotate left
*
*Purpose:
*       Performs a rotate left on an unsigned integer.
*
*       [Note:  The _lrotl entry is based on the assumption
*       that sizeof(int) == sizeof(long).]
*Entry:
*       unsigned val:   value to rotate
*       int    shift:   number of bits to shift by
*
*Exit:
*       returns rotated value
*
*Exceptions:
*       None.
*
*******************************************************************************/

unsigned long __cdecl _lrotl (
        unsigned long val,
        int shift
        )
{
        return( (unsigned long) _rotl((unsigned) val, shift) );
}

unsigned __cdecl _rotl (
        unsigned val,
        int shift
        )
{
        register unsigned hibit;        /* non-zero means hi bit set */
        register unsigned num = val;    /* number to rotate */

        shift &= 0x1f;                  /* modulo 32 -- this will also make
                                           negative shifts work */

        while (shift--) {
                hibit = num & 0x80000000;  /* get high bit */
                num <<= 1;              /* shift left one bit */
                if (hibit)
                        num |= 1;       /* set lo bit if hi bit was set */
        }

        return num;
}

