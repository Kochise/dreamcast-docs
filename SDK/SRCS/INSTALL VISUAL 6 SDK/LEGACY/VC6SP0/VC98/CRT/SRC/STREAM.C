/***
*stream.c - find a stream not in use
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _getstream() - find a stream not in use
*
*******************************************************************************/

#include <cruntime.h>
#ifdef _WIN32
#include <windows.h>
#endif  /* _WIN32 */
#include <malloc.h>
#include <stdio.h>
#include <file2.h>
#include <internal.h>
#include <mtdll.h>
#include <dbgint.h>

/***
*FILE *_getstream() - find a stream not in use
*
*Purpose:
*       Find a stream not in use and make it available to caller. Intended
*       for use inside library only
*
*Entry:
*       None. Scans __piob[]
*
*Exit:
*       Returns a pointer to a free stream, or NULL if all are in use.  A
*       stream becomes allocated if the caller decided to use it by setting
*       any r, w, r/w mode.
*
*       [Multi-thread note: If a free stream is found, it is returned in a
*       LOCKED state.  It is the caller's responsibility to unlock the stream.]
*
*Exceptions:
*
*******************************************************************************/

FILE * __cdecl _getstream (
        void
        )
{
        REG2 FILE *retval = NULL;

#ifdef _WIN32

        REG1 int i;

        /* Get the iob[] scan lock */
        _mlock(_IOB_SCAN_LOCK);

        /*
         * Loop through the __piob table looking for a free stream, or the
         * first NULL entry.
         */
        for ( i = 0 ; i < _nstream ; i++ ) {

            if ( __piob[i] != NULL ) {
                /*
                 * if the stream is not inuse, return it.
                 */
                if ( !inuse( (FILE *)__piob[i] ) ) {
#ifdef _MT
                    _lock_str2(i, __piob[i]);

                    if ( inuse( (FILE *)__piob[i] ) ) {
                        _unlock_str2(i, __piob[i]);
                        continue;
                    }
#endif  /* _MT */
                    retval = (FILE *)__piob[i];
                    break;
                }
            }
            else {
                /*
                 * allocate a new _FILEX, set _piob[i] to it and return a
                 * pointer to it.
                 */
                if ( (__piob[i] = _malloc_crt( sizeof(_FILEX) )) != NULL ) {

#if defined (_MT)
                    InitializeCriticalSection( &(((_FILEX *)__piob[i])->lock) );
                    EnterCriticalSection( &(((_FILEX *)__piob[i])->lock) );
#endif  /* defined (_MT) */
                    retval = (FILE *)__piob[i];
                }

                break;
            }
        }

        /*
         * Initialize the return stream.
         */
        if ( retval != NULL ) {
            retval->_flag = retval->_cnt = 0;
            retval->_tmpfname = retval->_ptr = retval->_base = NULL;
            retval->_file = -1;
        }

        _munlock(_IOB_SCAN_LOCK);

#else  /* _WIN32 */
#if defined (_M_MPPC) || defined (_M_M68K)

        REG1 FILE *stream = _iob;

        /* Loop through the _iob table looking for a free stream.*/
        for (; stream <= _lastiob; stream++) {

                if ( !inuse(stream) ) {
                        stream->_flag = stream->_cnt = 0;
                        stream->_tmpfname = stream->_ptr = stream->_base = NULL;
                        stream->_file = -1;
                        retval = stream;
                        break;
                }
        }

#endif  /* defined (_M_MPPC) || defined (_M_M68K) */
#endif  /* _WIN32 */

        return(retval);
}
