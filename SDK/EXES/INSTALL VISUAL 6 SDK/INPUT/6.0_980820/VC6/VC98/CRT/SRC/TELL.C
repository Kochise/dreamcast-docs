/***
*tell.c - find file position
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       contains _tell() - find file position
*
*******************************************************************************/

#ifndef _MAC


#include <cruntime.h>
#include <io.h>

/***
*long _tell(filedes) - find file position
*
*Purpose:
*       Gets the current position of the file pointer (no adjustment
*       for buffering).
*
*Entry:
*       int filedes - file handle of file
*
*Exit:
*       returns file position or -1L (sets errno) if bad file descriptor or
*       pipe
*
*Exceptions:
*
*******************************************************************************/

long __cdecl _tell (
        int filedes
        )
{
        return(_lseek(filedes,0L,1));
}


#else  /* _MAC */


#include <cruntime.h>
#include <stdio.h>
#include <errno.h>
#include <io.h>
#include <internal.h>
#include <stddef.h>
#include <stdlib.h>
#include <memory.h>
#include <msdos.h>
#include <macos\files.h>
#include <macos\errors.h>

/***
*long _tell(fh) - find file position
*
*Purpose:
*       Gets the current position of the file pointer (no adjustment
*       for buffering).
*
*Entry:
*       int fh - file handle of file
*
*Exit:
*       returns file position or -1L (sets errno) if bad file descriptor or
*       pipe
*
*Exceptions:
*
*******************************************************************************/

long __cdecl _tell (
        int fh
        )
{
        ParamBlockRec parm;
        OSErr osErr;

        /* validate handle */
        if ( ((unsigned)fh >= (unsigned)_nfile) ||
             !(_osfile[fh] & FOPEN) ||
             (_osfile[fh] & FDEV) )
        {
                /* out of range -- return error */
                errno = EBADF;
                _macerrno = 0;
                return -1;
        }

        memset(&parm, 0, sizeof(ParamBlockRec));
        parm.ioParam.ioRefNum = _osfhnd[fh];
        osErr = PBGetFPosSync(&parm);
        switch (osErr)
        {
                case noErr:
                        return parm.ioParam.ioPosOffset;

                default:
                        errno = EIO;
                        return -1;
        }
}


#endif  /* _MAC */
