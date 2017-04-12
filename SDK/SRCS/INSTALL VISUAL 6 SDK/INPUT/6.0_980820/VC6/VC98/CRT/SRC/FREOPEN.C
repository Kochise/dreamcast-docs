/***
*freopen.c - close a stream and assign it to a new file
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines freopen() - close and reopen file, typically used to redirect
*       stdin/out/err/prn/aux.
*
*******************************************************************************/

#include <cruntime.h>
#include <stdio.h>
#include <file2.h>
#include <share.h>
#include <dbgint.h>
#include <internal.h>
#include <mtdll.h>
#include <tchar.h>

/***
*FILE *freopen(filename, mode, stream) - reopen stream as new file
*
*Purpose:
*       Closes the file associated with stream and assigns stream to a new
*       file with current mode.  Usually used to redirect a standard file
*       handle.
*
*Entry:
*       char *filename - new file to open
*       char *mode - new file mode, as in fopen()
*       FILE *stream - stream to close and reassign
*
*Exit:
*       returns stream if successful
*       return NULL if fails
*
*Exceptions:
*
*******************************************************************************/

FILE * __cdecl _tfreopen (
        const _TSCHAR *filename,
        const _TSCHAR *mode,
        FILE *str
        )
{
        REG1 FILE *stream;
        FILE *retval;

        _ASSERTE(filename != NULL);
        _ASSERTE(*filename != _T('\0'));
        _ASSERTE(mode != NULL);
        _ASSERTE(str != NULL);

        /* Init stream pointer */
        stream = str;

        _lock_str(stream);

        /* If the stream is in use, try to close it. Ignore possible
         * error (ANSI 4.9.5.4). */
        if ( inuse(stream) )
                _fclose_lk(stream);

        stream->_ptr = stream->_base = NULL;
        stream->_cnt = stream->_flag = 0;
#ifdef _UNICODE
        retval = _wopenfile(filename,mode,_SH_DENYNO,stream);
#else  /* _UNICODE */
        retval = _openfile(filename,mode,_SH_DENYNO,stream);
#endif  /* _UNICODE */

        _unlock_str(stream);
        return(retval);
}
