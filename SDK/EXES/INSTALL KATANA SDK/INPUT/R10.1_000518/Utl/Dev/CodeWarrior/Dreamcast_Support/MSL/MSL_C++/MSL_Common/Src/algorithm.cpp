/*  Metrowerks Standard Library  */

/*  $Date: 1999/01/23 00:26:06 $ 
 *  $Revision: 1.6 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */

/**
 **  Lib++  : The Modena C++ Standard Library,
 **           Version 2.4, October 1997
 **
 **  Copyright (c) 1995-1997 Modena Software Inc.
 **/

#include <mcompile.h>

#include <algorithm>    // hh 971220 fixed MOD_INCLUDE
#include <utility>      // hh 971220 fixed MOD_INCLUDE

MSIPL_STD_BEGIN

#define MSIPL_SEED_RANDOM 161803398

void __random_generator::seed (unsigned long j)
{
    unsigned long k = 1;
    table[54] = j;
    size_t i;
    for (i = 0; i < 55; i++)
    {
        size_t ii = 21 * i % 55;
        table[ii] = k;
        k = j - k;
        j = table[ii];
    }
    for (int loop = 0; loop < 4; loop++)
    {
        for (i = 0; i < 55; i++)
            table[i] = table[i] - table[ (1 + i + 30) % 55];
    }
    index1 = 0;
    index2 = 31;
}

__random_generator __msipl_rd (MSIPL_SEED_RANDOM);

MSIPL_STD_END

// hh 971220 fixed MOD_INCLUDE
