/***
*execv.c - execute a file
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _execv() - execute a file
*
*******************************************************************************/

#include <cruntime.h>
#include <stdlib.h>
#include <process.h>
#include <tchar.h>
#include <dbgint.h>

/***
*int _execv(filename, argvector) - execute a file
*
*Purpose:
*       Executes a file with given arguments.  Passes arguments to _execve and
*       uses pointer to the default environment.
*
*Entry:
*       _TSCHAR *filename        - file to execute
*       _TSCHAR **argvector - vector of arguments.
*
*Exit:
*       destroys calling process (hopefully)
*       if fails, returns -1
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _texecv (
        const _TSCHAR *filename,
        const _TSCHAR * const *argvector
        )
{
        _ASSERTE(filename != NULL);
        _ASSERTE(*filename != _T('\0'));
        _ASSERTE(argvector != NULL);
        _ASSERTE(*argvector != NULL);
        _ASSERTE(**argvector != _T('\0'));

        return(_texecve(filename,argvector,NULL));
}
