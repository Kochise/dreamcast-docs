/***
*mkdir.c - make directory
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Defines function _mkdir() - make a directory
*
*******************************************************************************/

#ifndef _MAC

#include <cruntime.h>
#include <oscalls.h>
#include <internal.h>
#include <direct.h>
#include <tchar.h>

/***
*int _mkdir(path) - make a directory
*
*Purpose:
*       creates a new directory with the specified name
*
*Entry:
*       _TSCHAR *path - name of new directory
*
*Exit:
*       returns 0 if successful
*       returns -1 and sets errno if unsuccessful
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _tmkdir (
        const _TSCHAR *path
        )
{
        ULONG dosretval;

        /* ask OS to create directory */

        if (!CreateDirectory((LPTSTR)path, (LPSECURITY_ATTRIBUTES)NULL))
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

#else  /* _MAC */

#include <cruntime.h>
#include <internal.h>
#include <direct.h>
#include <string.h>
#include <errno.h>
#include <macos\osutils.h>
#include <macos\files.h>
#include <macos\errors.h>

/***
*int _mkdir(path) - make a directory
*
*Purpose:
*       creates a new directory with the specified name
*
*Entry:
*       char *path - name of new directory
*
*Exit:
*       returns 0 if successful
*       returns -1 and sets errno if unsuccessful
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _mkdir (
        const char *path
        )
{
        /* ask OS to create directory */
        HParamBlockRec hparamBlock;
        char st[256];
        OSErr osErr;

        if (!*path)
        {
            errno = ENOENT;
            return -1;
        }
        strcpy(st, path);
        hparamBlock.fileParam.ioNamePtr = _c2pstr(st);
        hparamBlock.fileParam.ioVRefNum = 0;
        hparamBlock.fileParam.ioDirID = 0;
        osErr = PBDirCreateSync(&hparamBlock);
        if (osErr) {
            /* error occured -- map error code and return */
            _dosmaperr(osErr);
            return -1;
        }

        return 0;
}

#endif  /* _MAC */
