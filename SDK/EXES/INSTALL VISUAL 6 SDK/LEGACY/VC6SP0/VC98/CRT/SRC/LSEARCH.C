/***
*lsearch.c - linear search of an array
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       contains the _lsearch() function - linear search of an array
*
*******************************************************************************/

#include <cruntime.h>
#include <stddef.h>
#include <search.h>
#include <memory.h>

/***
*char *_lsearch(key, base, num, width, compare) - do a linear search
*
*Purpose:
*       Performs a linear search on the array, looking for the value key
*       in an array of num elements of width bytes in size.  Returns
*       a pointer to the array value if found; otherwise adds the
*       key to the end of the list.
*
*Entry:
*       char *key - key to search for
*       char *base - base of array to search
*       unsigned *num - number of elements in array
*       int width - number of bytes in each array element
*       int (*compare)() - pointer to function that compares two
*               array values, returning 0 if they are equal and non-0
*               if they are different. Two pointers to array elements
*               are passed to this function.
*
*Exit:
*       if key found:
*               returns pointer to array element
*       if key not found:
*               adds the key to the end of the list, and increments
*               *num.
*               returns pointer to new element.
*
*Exceptions:
*
*******************************************************************************/

void * __cdecl _lsearch (
        REG2 const void *key,
        REG1 void *base,
        REG3 unsigned int *num,
        unsigned int width,
        int (__cdecl *compare)(const void *, const void *)
        )
{
        unsigned int place = 0;
        while (place < *num )
                if (!(*compare)(key,base))
                        return(base);
                else
                {
                        base = (char *)base + width;
                        place++;
                }
        (void) memcpy( base, key, width );
        (*num)++;
        return( base );
}
