/***
*clearerr.c - clear error and eof flags
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines clearerr() - clear error and eof flags from a stream
*
*******************************************************************************/

#include <cruntime.h>
#include <stdio.h>
#include <dbgint.h>
#include <file2.h>
#include <mtdll.h>
#include <internal.h>
#include <msdos.h>

/***
*void clearerr(stream) - clear error and eof flags on a stream
*
*Purpose:
*       Resets the error and eof indicators for a stream to 0
*
*Entry:
*       FILE *stream - stream to set indicators on
*
*Exit:
*       No return value.
*       changes the _flag field of the FILE struct.
*
*Exceptions:
*
*******************************************************************************/

void __cdecl clearerr (
        FILE *stream
        )
{
        _ASSERTE(stream != NULL);

        _lock_str(stream);

        /* Clear stdio level flags */
        stream->_flag &= ~(_IOERR|_IOEOF);

        /* Clear lowio level flags */

#ifdef _WIN32

        _osfile_safe(_fileno(stream)) &= ~(FEOFLAG);

#else  /* _WIN32 */
        _osfile[_fileno(stream)] &= ~(FEOFLAG);
#endif  /* _WIN32 */

        _unlock_str(stream);
}
