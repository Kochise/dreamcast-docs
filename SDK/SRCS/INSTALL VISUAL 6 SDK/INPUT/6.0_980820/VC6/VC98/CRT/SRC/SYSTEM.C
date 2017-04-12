/***
*system.c - pass a command line to the shell
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines system() - passes a command to the shell
*
*******************************************************************************/

#include <cruntime.h>
#include <process.h>
#include <io.h>
#include <stdlib.h>
#include <errno.h>
#include <tchar.h>
#include <dbgint.h>

/***
*int system(command) - send the command line to a shell
*
*Purpose:
*       Executes a shell and passes the command line to it.
*       If command is NULL, determine if a command processor exists.
*       The command processor is described by the environment variable
*       COMSPEC.  If that environment variable does not exist, try the
*       name "cmd.exe" for Windows NT and "command.com" for Windows '95.
*
*Entry:
*       char *command - command to pass to the shell (if NULL, just determine
*                       if command processor exists)
*
*Exit:
*       if command != NULL  returns status of the shell
*       if command == NULL  returns non-zero if CP exists, zero if CP doesn't exist
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _tsystem (
        const _TSCHAR *command
        )
{
        int catch;
        _TSCHAR *argv[4];

        argv[0] = _tgetenv(_T("COMSPEC"));

        /*
         * If command == NULL, return true IFF %COMSPEC%
         * is set AND the file it points to exists.
         */

        if (command == NULL) {
                return argv[0] == NULL ? 0 : (!_taccess(argv[0],0));
        }

        _ASSERTE(*command != _T('\0'));

        argv[1] = _T("/c");
        argv[2] = (_TSCHAR *) command;
        argv[3] = NULL;

        /* If there is a COMSPEC defined, try spawning the shell */

        if (argv[0])    /* Do not try to spawn the null string */
                if ((catch = _tspawnve(_P_WAIT,argv[0],argv,NULL)) != -1
                || (errno != ENOENT && errno != EACCES))
                        return(catch);

        /* No COMSPEC so set argv[0] to what COMSPEC should be. */
        argv[0] = ( _osver & 0x8000 ) ? _T("command.com") : _T("cmd.exe");

        /* Let the _spawnvpe routine do the path search and spawn. */

        return(_tspawnvpe(_P_WAIT,argv[0],argv,NULL));
}
