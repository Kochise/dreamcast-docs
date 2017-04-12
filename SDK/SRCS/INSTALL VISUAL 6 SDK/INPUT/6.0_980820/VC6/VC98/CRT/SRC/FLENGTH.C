/***
*flength.c - find length of a file
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _filelength() - find the length of a file
*
*******************************************************************************/

#ifndef _MAC


#include <cruntime.h>
#include <stdio.h>
#include <errno.h>
#include <io.h>
#include <internal.h>
#include <msdos.h>
#include <mtdll.h>
#include <stddef.h>
#include <stdlib.h>

/***
*long _filelength(filedes) - find length of a file
*
*Purpose:
*       Returns the length in bytes of the specified file.
*
*Entry:
*       int filedes - handle referring to file to find length of
*
*Exit:
*       returns length of file in bytes
*       returns -1L if fails
*
*Exceptions:
*
*******************************************************************************/

long __cdecl _filelength (
        int filedes
        )
{
        long length;
        long here;

        if ( ((unsigned)filedes >= (unsigned)_nhandle) ||
             !(_osfile(filedes) & FOPEN) )
        {
                errno = EBADF;
                _doserrno = 0L;         /* not an OS error */
                return(-1L);
        }

        _lock_fh(filedes);

        /* Seek to end to get length of file. */
        if ( (here = _lseek_lk(filedes, 0L, SEEK_CUR)) == -1L )
                length = -1L;   /* return error */
        else {
                length = _lseek_lk(filedes, 0L, SEEK_END);
                if ( here != length )
                        _lseek_lk(filedes, here, SEEK_SET);
        }

        _unlock_fh(filedes);

        return(length);
}


#else  /* _MAC */


#include <cruntime.h>
#include <stdio.h>
#include <errno.h>
#include <io.h>
#include <internal.h>
#include <memory.h>
#include <msdos.h>
#include <stddef.h>
#include <stdlib.h>
#include <macos\files.h>
#include <macos\errors.h>

/***
*long _filelength(fh) - find length of a file
*
*Purpose:
*       Returns the length in bytes of the specified file.
*
*Entry:
*       int fh - handle referring to file to find length of
*
*Exit:
*       returns length of file in bytes
*       returns -1L if fails
*
*Exceptions:
*
*******************************************************************************/

long __cdecl _filelength (
        int fh
        )
{
        ParamBlockRec parm;
        OSErr osErr;

        /* validate handle */
        if ( (unsigned)fh >= (unsigned)_nfile ||
             !(_osfile[fh] & FOPEN) ||
             _osfile[fh] & FDEV )
        {
                /* out of range -- return error */
                errno = EBADF;
                _macerrno = 0;
                return -1;
        }

        memset(&parm, 0, sizeof(ParamBlockRec));
        parm.ioParam.ioRefNum = _osfhnd[fh];
        osErr = PBGetEOFSync(&parm);
        if (osErr)
        {
                _dosmaperr(osErr);
                return -1;
        }
        return (long)parm.ioParam.ioMisc;
}


#endif  /* _MAC */
