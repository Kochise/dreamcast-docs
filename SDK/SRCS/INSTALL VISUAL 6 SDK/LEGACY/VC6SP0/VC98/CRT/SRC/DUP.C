/***
*dup.c - duplicate file handles
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _dup() - duplicate file handles
*
*******************************************************************************/

#ifndef _MAC


#include <cruntime.h>
#include <oscalls.h>
#include <errno.h>
#include <mtdll.h>
#include <io.h>
#include <msdos.h>
#include <internal.h>
#include <stdlib.h>

/***
*int _dup(fh) - duplicate a file handle
*
*Purpose:
*       Assigns another file handle to the file associated with the
*       handle fh.  The next available file handle is assigned.
*
*       Multi-thread: Be sure not to hold two file handle locks
*       at the same time!
*
*Entry:
*       int fh - file handle to duplicate
*
*Exit:
*       returns new file handle if successful
*       returns -1 (and sets errno) if fails
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _dup (
        int fh
        )
{
        ULONG dosretval;                /* o.s. return value */
        int newfh;                      /* variable for new file handle */
        char fileinfo;                  /* _osfile info for file */
        long new_osfhandle;

        /* validate file handle */
        if ( ((unsigned)fh >= (unsigned)_nhandle) ||
             !(_osfile(fh) & FOPEN) )
        {
                errno = EBADF;
                _doserrno = 0;  /* no o.s. error */
                return -1;
        }

        _lock_fh(fh);                   /* lock file handle */
        fileinfo = _osfile(fh);         /* get file info for file */

        /* create duplicate handle */

        if ( (newfh = _alloc_osfhnd()) == -1 )
        {
                errno = EMFILE;         /* too many files error */
                _doserrno = 0L;         /* not an OS error */
                _unlock_fh(fh);
                return -1;              /* return error to caller */
        }

        /*
         * duplicate the file handle
         */
        if ( !(DuplicateHandle(GetCurrentProcess(),
                               (HANDLE)_get_osfhandle(fh),
                               GetCurrentProcess(),
                               (PHANDLE)&new_osfhandle,
                               0L,
                               TRUE,
                               DUPLICATE_SAME_ACCESS)) )
        {
                dosretval = GetLastError();
        }
        else {
                _set_osfhnd(newfh, new_osfhandle);
                dosretval = 0;
        }

        _unlock_fh(newfh);

        _unlock_fh(fh);                 /* unlock file handle */

        if (dosretval) {
                /* o.s. error -- map and return */
                _dosmaperr(dosretval);
                return -1;
        }

        /*
         * copy the _osfile value, with the FNOINHERIT bit cleared
         */
        _osfile(newfh) = fileinfo & ~FNOINHERIT;

        return newfh;
}


#else  /* _MAC */


#include <cruntime.h>
#include <errno.h>
#include <io.h>
#include <internal.h>
#include <stdlib.h>
#include <msdos.h>

/***
*int _dup(fh) - duplicate a file handle
*
*Purpose:
*       Assigns another file handle to the file associated with the
*       handle fh.  The next available file handle is assigned.
*
*Entry:
*       int fh - file handle to duplicate
*
*Exit:
*       returns new file handle if successful
*       returns -1 (and sets errno) if fails
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _dup (
        int fh
        )
{

        int fhNew;

        /* get a file handle*/
        for (fhNew=0; fhNew <_nfile; fhNew++)
        {
                if (!(_osfile[fhNew] & FOPEN))
                {
                        break;
                }
        }
        if (fhNew >= _nfile)
        {
                errno = EMFILE;
                _macerrno = 0;
                return -1;
        }

        return __dupx(fh, fhNew);
}


#endif  /* _MAC */
