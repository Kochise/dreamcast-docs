/***
*unlink.c - unlink a file
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines unlink() - unlink a file
*
*******************************************************************************/

#ifndef _MAC

#include <cruntime.h>
#include <oscalls.h>
#include <internal.h>
#include <io.h>
#include <tchar.h>

/***
*int _unlink(path) - unlink(delete) the given file
*
*Purpose:
*       This version deletes the given file because there is no
*       distinction between a linked file and non-linked file.
*
*       NOTE: remove() is an alternative entry point to the _unlink()
*       routine* interface is identical.
*
*Entry:
*       _TSCHAR *path - file to unlink/delete
*
*Exit:
*       returns 0 if successful
*       returns -1 and sets errno if unsuccessful
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _tremove (
        const _TSCHAR *path
        )
{
        ULONG dosretval;

        if (!DeleteFile((LPTSTR)path))
            dosretval = GetLastError();
        else
            dosretval = 0;

        if (dosretval) {
            /* error occured -- map error code and return */
            _dosmaperr(dosretval);
            return -1;
        }

        return 0;
}

int __cdecl _tunlink (
        const _TSCHAR *path
        )
{
        /* remove is synonym for unlink */
        return _tremove(path);
}

#else  /* _MAC */


#include <cruntime.h>
//#include <oscalls.h>
#include <internal.h>
#include <io.h>
#include <errno.h>
#include <stdlib.h>
#include <macos\files.h>
#include <macos\errors.h>
#include <string.h>

/***
*int _unlink(path) - unlink(delete) the given file
*
*Purpose:
*       This version deletes the given file but not a directory
*
*Entry:
*       char *path -    file to unlink/delete
*
*Exit:
*       returns 0 if successful
*       returns -1 and sets errno if unsuccessful
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _unlink (
        const char *path
        )
{
        ParamBlockRec parm;
        OSErr osErr;
        char stPath[256];

        if (!*path || strlen(path) > 255)
        {
            errno = ENOENT;
            return -1;
        }

        strcpy(stPath, path);
        _c2pstr(stPath);

        memset(&parm, '\0', sizeof(ParamBlockRec));
        parm.fileParam.ioNamePtr = stPath;

        /* parm.fileParam.ioVRefNum = 0; */
        /* parm.fileParam.ioFDirIndex = 0; */

        if (!(osErr = PBGetFInfoSync(&parm)))  /* Make sure it's not a dir */
        {
            memset(&parm, '\0', sizeof(ParamBlockRec));
            parm.ioParam.ioNamePtr = stPath;
            /* parm.ioParam.ioVRefNum = 0; */
            osErr = PBDeleteSync(&parm);
        }

        if (osErr)
        {
            /* error occured -- map error code and return */
            _dosmaperr(osErr);
            return -1;
        }

        return 0;
}

#endif  /* _MAC */
