/***
*closeall.c - close all open files
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _fcloseall() - closes all open files except stdin, stdout
*       stdprn, stderr, and stdaux.
*
*******************************************************************************/

#include <cruntime.h>
#ifdef _WIN32
#include <windows.h>
#endif  /* _WIN32 */
#include <stdio.h>
#include <file2.h>
#include <internal.h>
#include <malloc.h>
#include <mtdll.h>
#include <dbgint.h>


/***
*int _fcloseall() - close all open streams
*
*Purpose:
*       Closes all streams currently open except for stdin/out/err/aux/prn.
*       tmpfile() files are among those closed.
*
*Entry:
*       None.
*
*Exit:
*       returns number of streams closed if OK
*       returns EOF if fails.
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _fcloseall (
        void
        )
{
        REG2 int count = 0;

#ifdef _WIN32

        REG1 i;

        _mlock(_IOB_SCAN_LOCK);

        for ( i = 3 ; i < _nstream ; i++ ) {

            if ( __piob[i] != NULL ) {
                /*
                 * if the stream is in use, close it
                 */
                if ( inuse( (FILE *)__piob[i] ) && (fclose( __piob[i] ) !=
                     EOF) )
                        count++;

                /*
                 * if stream is part of a _FILEX we allocated, free it.
                 */
                if ( i >= _IOB_ENTRIES ) {

#if defined (_MT)
                    DeleteCriticalSection( &(((_FILEX *)__piob[i])->lock) );
#endif  /* defined (_MT) */
                    _free_crt( __piob[i] );
                    __piob[i] = NULL;
                }
            }
        }

        _munlock(_IOB_SCAN_LOCK);

#else  /* _WIN32 */
#if defined (_M_MPPC) || defined (_M_M68K)

        REG1 FILE *stream = &_iob[3];

        for (; stream <= _lastiob; stream++)
                if (fclose(stream) != EOF)
                        count++;

#endif  /* defined (_M_MPPC) || defined (_M_M68K) */
#endif  /* _WIN32 */

        return(count);
}
