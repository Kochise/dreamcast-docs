/***
*spawnv.c - spawn a child process
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _spawnv() - spawn a child process
*
*******************************************************************************/

#include <cruntime.h>
#include <stdlib.h>
#include <process.h>
#include <tchar.h>
#include <dbgint.h>

/***
*int _spawnv(modeflag, pathname, argv) - spawn a child process
*
*Purpose:
*       Spawns a child process.
*       formats the parameters and calls _spawnve to do the actual work.  The
*       NULL environment pointer indicates that the new process will inherit
*       the parents process's environment.  NOTE - at least one argument must
*       be present.  This argument is always, by convention, the name of the
*       file being spawned.
*
*Entry:
*       int modeflag   - mode to spawn (WAIT, NOWAIT, or OVERLAY)
*                        only WAIT and OVERLAY currently implemented
*       _TSCHAR *pathname - file to spawn
*       _TSCHAR **argv    - vector of arguments
*
*Exit:
*       returns exit code of child process
*       if fails, returns -1
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _tspawnv (
        int modeflag,
        const _TSCHAR *pathname,
        const _TSCHAR * const *argv
        )
{
        _ASSERTE(pathname != NULL);
        _ASSERTE(*pathname != _T('\0'));
        _ASSERTE(argv != NULL);
        _ASSERTE(*argv != NULL);
        _ASSERTE(**argv != _T('\0'));

        return(_tspawnve(modeflag,pathname,argv,NULL));
}
