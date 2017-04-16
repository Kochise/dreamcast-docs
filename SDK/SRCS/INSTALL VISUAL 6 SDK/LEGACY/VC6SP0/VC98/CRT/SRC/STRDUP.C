/***
*strdup.c - duplicate a string in malloc'd memory
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _strdup() - grab new memory, and duplicate the string into it.
*
*******************************************************************************/

#include <cruntime.h>
#include <malloc.h>
#include <string.h>

/***
*char *_strdup(string) - duplicate string into malloc'd memory
*
*Purpose:
*       Allocates enough storage via malloc() for a copy of the
*       string, copies the string into the new memory, and returns
*       a pointer to it.
*
*Entry:
*       char *string - string to copy into new memory
*
*Exit:
*       returns a pointer to the newly allocated storage with the
*       string in it.
*
*       returns NULL if enough memory could not be allocated, or
*       string was NULL.
*
*Uses:
*
*Exceptions:
*
*******************************************************************************/

char * __cdecl _strdup (
        const char * string
        )
{
        char *memory;

        if (!string)
                return(NULL);

        if (memory = malloc(strlen(string) + 1))
                return(strcpy(memory,string));

        return(NULL);
}
