/***
*rmdir.c - remove directory
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _rmdir() - remove a directory
*
*******************************************************************************/

#ifndef _MAC

#include <cruntime.h>
#include <oscalls.h>
#include <internal.h>
#include <direct.h>
#include <tchar.h>

/***
*int _rmdir(path) - remove a directory
*
*Purpose:
*       deletes the directory speicifed by path.  The directory must
*       be empty, and it must not be the current working directory or
*       the root directory.
*
*Entry:
*       _TSCHAR *path - directory to remove
*
*Exit:
*       returns 0 if successful
*       returns -1 and sets errno if unsuccessful
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _trmdir (
        const _TSCHAR *path
        )
{
        ULONG dosretval;

        /* ask OS to remove directory */

        if (!RemoveDirectory((LPTSTR)path))
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

#include <macos\types.h>

/***
*int _rmdir(path) - remove a directory
*
*Purpose:
*       deletes the directory speicifed by path.  The directory must
*       be empty, and it must not be the current working directory or
*       the root directory.
*
*Entry:
*       char *path -    directory to remove
*
*Exit:
*       returns 0 if successful
*       returns -1 and sets errno if unsuccessful
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _rmdir (
        const char *path
        )
{
        ParamBlockRec parm;
        HParamBlockRec hparm;

        OSErr osErr;
        char stPath[256];

        if (!*path || strlen(path) > 255)
        {
            errno = ENOENT;
            return -1;
        }

        strcpy(stPath, path);
        _c2pstr(stPath);

        memset(&hparm, '\0', sizeof(HParamBlockRec));
        hparm.fileParam.ioNamePtr = stPath;

        /* hparm.fileParam.ioVRefNum = 0; */
        /* hparm.fileParam.ioFDirIndex = 0; */

        if ((osErr = PBHGetFInfoSync(&hparm)) == fnfErr)
        {
            memset(&parm, '\0', sizeof(ParamBlockRec));
            parm.fileParam.ioNamePtr = stPath;
            /* parm.fileParam.ioVRefNum = 0; */
            osErr = PBDeleteSync(&parm);
        }
        else if (!osErr)
        {
            osErr = fnfErr;  /* Can't rmdir a file */
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
