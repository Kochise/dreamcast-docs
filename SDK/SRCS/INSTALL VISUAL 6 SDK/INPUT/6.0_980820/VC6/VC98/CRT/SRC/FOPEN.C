/***
*fopen.c - open a file
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines fopen() and _fsopen() - open a file as a stream and open a file
*       with a specified sharing mode as a stream
*
*******************************************************************************/

#include <cruntime.h>
#include <stdio.h>
#include <share.h>
#include <dbgint.h>
#include <internal.h>
#include <mtdll.h>
#include <file2.h>
#include <tchar.h>

/***
*FILE *_fsopen(file, mode, shflag) - open a file
*
*Purpose:
*       Opens the file specified as a stream.  mode determines file mode:
*       "r": read       "w": write      "a": append
*       "r+": read/write                "w+": open empty for read/write
*       "a+": read/append
*       Append "t" or "b" for text and binary mode. shflag determines the
*       sharing mode. Values are the same as for sopen().
*
*Entry:
*       char *file - file name to open
*       char *mode - mode of file access
*
*Exit:
*       returns pointer to stream
*       returns NULL if fails
*
*Exceptions:
*
*******************************************************************************/

FILE * __cdecl _tfsopen (
        const _TSCHAR *file,
        const _TSCHAR *mode
        ,int shflag
        )
{
        REG1 FILE *stream;
        REG2 FILE *retval;

        _ASSERTE(file != NULL);
        _ASSERTE(*file != _T('\0'));
        _ASSERTE(mode != NULL);
        _ASSERTE(*mode != _T('\0'));

        /* Get a free stream */
        /* [NOTE: _getstream() returns a locked stream.] */

        if ((stream = _getstream()) == NULL)
                return(NULL);

        /* open the stream */
#ifdef _UNICODE
        retval = _wopenfile(file,mode,shflag,stream);
#else  /* _UNICODE */
        retval = _openfile(file,mode,shflag,stream);
#endif  /* _UNICODE */

        /* unlock stream and return. */
        _unlock_str(stream);
        return(retval);
}


/***
*FILE *fopen(file, mode) - open a file
*
*Purpose:
*       Opens the file specified as a stream.  mode determines file mode:
*       "r": read       "w": write      "a": append
*       "r+": read/write                "w+": open empty for read/write
*       "a+": read/append
*       Append "t" or "b" for text and binary mode
*
*Entry:
*       char *file - file name to open
*       char *mode - mode of file access
*
*Exit:
*       returns pointer to stream
*       returns NULL if fails
*
*Exceptions:
*
*******************************************************************************/

FILE * __cdecl _tfopen (
        const _TSCHAR *file,
        const _TSCHAR *mode
        )
{
        return( _tfsopen(file, mode, _SH_DENYNO) );
}
