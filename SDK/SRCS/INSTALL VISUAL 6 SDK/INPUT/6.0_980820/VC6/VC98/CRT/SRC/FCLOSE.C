/***
*fclose.c - close a file
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines fclose() - close an open file
*
*******************************************************************************/

#include <cruntime.h>
#include <stdio.h>
#include <file2.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include <internal.h>
#include <mtdll.h>
#include <dbgint.h>

#if defined (_M_MPPC) || defined (_M_M68K)
#include <macos\osutils.h>
#include <macos\files.h>
#include <macos\errors.h>
#include <macos\gestalte.h>
#include <macos\traps.h>
#include <macos\toolutil.h>
#include <macos\folders.h>
#endif  /* defined (_M_MPPC) || defined (_M_M68K) */


/***
*int fclose(stream) - close a stream
*
*Purpose:
*       Flushes and closes a stream and frees any buffer associated
*       with that stream, unless it was set with setbuf.
*
*Entry:
*       FILE *stream - stream to close
*
*Exit:
*       returns 0 if OK, EOF if fails (can't _flush, not a FILE, not open, etc.)
*       closes the file -- affecting FILE structure
*
*Exceptions:
*
*******************************************************************************/

#ifdef _MT

int __cdecl fclose (
        FILE *stream
        )
{
        int result = EOF;

        _ASSERTE(stream != NULL);

        /* If stream is a string, simply clear flag and return EOF */
        if (stream->_flag & _IOSTRG)
                stream->_flag = 0;  /* IS THIS REALLY NEEDED ??? */

        /* Stream is a real file. */
        else {
                _lock_str(stream);
                result = _fclose_lk(stream);
                _unlock_str(stream);
        }

        return(result);
}

/***
*int _fclose_lk() - close a stream (lock already held)
*
*Purpose:
*       Core fclose() routine; assumes caller has stream lock held.
*
*       [See fclose() above for more information.]
*
*Entry:
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _fclose_lk (
        FILE *str
        )
{
        REG1 FILE *stream;
        REG2 int result = EOF;

        /* Init near stream pointer */
        stream = str;

#else  /* _MT */

int __cdecl fclose (
        FILE *str
        )
{
        REG1 FILE *stream;
        REG2 int result = EOF;

        /* Init near stream pointer */
        stream = str;

        if (stream->_flag & _IOSTRG) {
                stream->_flag = 0;
                return(EOF);
        }

#endif  /* _MT */

        _ASSERTE(str != NULL);

        if (inuse(stream)) {

                /* Stream is in use:
                       (1) flush stream
                       (2) free the buffer
                       (3) close the file
                       (4) delete the file if temporary
                */

                result = _flush(stream);
                _freebuf(stream);

                if (_close(_fileno(stream)) < 0)
                        result = EOF;

                else if ( stream->_tmpfname != NULL ) {
                        /*
                         * temporary file (i.e., one created by tmpfile()
                         * call). delete, if necessary (don't have to on
                         * Windows NT because it was done by the system when
                         * the handle was closed). also, free up the heap
                         * block holding the pathname.
                         */

#if defined (_M_MPPC) || defined (_M_M68K)
                        if ( _unlink(stream->_tmpfname) )
                                result = EOF;
#endif  /* defined (_M_MPPC) || defined (_M_M68K) */
                        _free_crt(stream->_tmpfname);
                stream->_tmpfname = NULL;
                }

        }

        stream->_flag = 0;
        return(result);
}
