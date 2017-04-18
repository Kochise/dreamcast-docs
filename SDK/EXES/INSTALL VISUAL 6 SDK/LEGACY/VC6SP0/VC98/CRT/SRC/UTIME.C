/***
*utime.c - set modification time for a file
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Sets the access/modification times for a file.
*
*******************************************************************************/

#ifdef _WIN32



#include <cruntime.h>
#include <sys/types.h>
#include <sys/utime.h>
#include <msdos.h>
#include <dostypes.h>
#include <time.h>
#include <fcntl.h>
#include <io.h>
#include <dos.h>
#include <oscalls.h>
#include <errno.h>
#include <stddef.h>
#include <internal.h>

#include <stdio.h>
#include <tchar.h>

/***
*int _utime(pathname, time) - set modification time for file
*
*Purpose:
*       Sets the modification time for the file specified by pathname.
*       Only the modification time from the _utimbuf structure is used
*       under MS-DOS.
*
*Entry:
*       struct _utimbuf *time - new modification date
*
*Exit:
*       returns 0 if successful
*       returns -1 and sets errno if fails
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _tutime (
        const _TSCHAR *fname,
        struct _utimbuf *times
        )
{
        int fh;
        int retval;

        /* open file, fname, since filedate system call needs a handle.  Note
         * _utime definition says you must have write permission for the file
         * to change its time, so open file for write only.  Also, must force
         * it to open in binary mode so we dont remove ^Z's from binary files.
         */


        if ((fh = _topen(fname, _O_RDWR | _O_BINARY)) < 0)
                return(-1);

        retval = _futime(fh, times);

        _close(fh);
        return(retval);
}

#ifndef _UNICODE

/***
*int _futime(fh, time) - set modification time for open file
*
*Purpose:
*       Sets the modification time for the open file specified by fh.
*       Only the modification time from the _utimbuf structure is used
*       under MS-DOS.
*
*Entry:
*       struct _utimbuf *time - new modification date
*
*Exit:
*       returns 0 if successful
*       returns -1 and sets errno if fails
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _futime (
        int fh,
        struct _utimbuf *times
        )
{
        REG1 struct tm *tmb;

        SYSTEMTIME SystemTime;
        FILETIME LocalFileTime;
        FILETIME LastWriteTime;
        FILETIME LastAccessTime;
        struct _utimbuf deftimes;

        if (times == NULL) {
                time(&deftimes.modtime);
                deftimes.actime = deftimes.modtime;
                times = &deftimes;
        }

        if ((tmb = localtime(&times->modtime)) == NULL) {
                errno = EINVAL;
                return(-1);
        }

        SystemTime.wYear   = (WORD)(tmb->tm_year + 1900);
        SystemTime.wMonth  = (WORD)(tmb->tm_mon + 1);
        SystemTime.wDay    = (WORD)(tmb->tm_mday);
        SystemTime.wHour   = (WORD)(tmb->tm_hour);
        SystemTime.wMinute = (WORD)(tmb->tm_min);
        SystemTime.wSecond = (WORD)(tmb->tm_sec);
        SystemTime.wMilliseconds = 0;

        if ( !SystemTimeToFileTime( &SystemTime, &LocalFileTime ) ||
             !LocalFileTimeToFileTime( &LocalFileTime, &LastWriteTime ) )
        {
                errno = EINVAL;
                return(-1);
        }

        if ((tmb = localtime(&times->actime)) == NULL) {
                errno = EINVAL;
                return(-1);
        }

        SystemTime.wYear   = (WORD)(tmb->tm_year + 1900);
        SystemTime.wMonth  = (WORD)(tmb->tm_mon + 1);
        SystemTime.wDay    = (WORD)(tmb->tm_mday);
        SystemTime.wHour   = (WORD)(tmb->tm_hour);
        SystemTime.wMinute = (WORD)(tmb->tm_min);
        SystemTime.wSecond = (WORD)(tmb->tm_sec);
        SystemTime.wMilliseconds = 0;

        if ( !SystemTimeToFileTime( &SystemTime, &LocalFileTime ) ||
             !LocalFileTimeToFileTime( &LocalFileTime, &LastAccessTime ) )
        {
                errno = EINVAL;
                return(-1);
        }

        /* set the date via the filedate system call and return. failing
         * this call implies the new file times are not supported by the
         * underlying file system.
         */

        if (!SetFileTime((HANDLE)_get_osfhandle(fh),
                                NULL,
                                &LastAccessTime,
                                &LastWriteTime
                               ))
        {
                errno = EINVAL;
                return(-1);
        }

        return(0);
}

#endif  /* _UNICODE */



#else  /* _WIN32 */

#if defined (_M_MPPC) || defined (_M_M68K)


#include <cruntime.h>
#include <internal.h>
#include <sys/types.h>
#include <sys/utime.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <macos\osutils.h>
#include <macos\files.h>
#include <macos\errors.h>

/***
*int _utime(pathname, time) - set modification time for file
*
*Purpose:
*       Sets the modification time for the file specified by pathname.
*       Only the modification time from the _utimbuf structure is used
*       under MS-DOS.
*
*Entry:
*       struct _utimbuf *time - new modification date
*
*Exit:
*       returns 0 if successful
*       returns -1 and sets errno if fails
*
*Exceptions:
*
*******************************************************************************/
void __Ansi2MacTime(struct tm *tmb, DateTimeRec * pdt);

int __cdecl _utime (
        const char *fname,
        struct _utimbuf *times
        )
{
        CInfoPBRec cinfoPB;
        time_t timeval;
        OSErr osErr;
        struct tm *tmb;
        unsigned long lTime;
        DateTimeRec dt;
        char szBuf[256];

        strcpy(szBuf, fname);
        cinfoPB.dirInfo.ioVRefNum = 0;
        cinfoPB.dirInfo.ioDrDirID = 0;
        cinfoPB.dirInfo.ioFDirIndex = 0;
        cinfoPB.dirInfo.ioNamePtr = _c2pstr(szBuf);
        osErr = PBGetCatInfoSync(&cinfoPB);
        switch (osErr)
                {
                case noErr:
                        break;
                case fnfErr:
                case extFSErr:
                case bdNamErr:
                case ioErr:
                case nsvErr:
                case paramErr:
                        errno = ENOENT;
                        return -1;
                default:
                        return -1;
                 }

        //file locked or dir
        if (cinfoPB.dirInfo.ioFlAttrib & 0x1 ||
                cinfoPB.dirInfo.ioFlAttrib & 0x10)
                {
                /* no write permission on file, return error */
                errno = EACCES;
                return -1;
                }

        if (times == NULL)
                {
                GetDateTime(&lTime);
                timeval = (time_t)lTime;
                }
        else
                {
                timeval = times->modtime;
                if ((tmb = localtime(&timeval)) == NULL)
                        {
                        errno = EINVAL;
                        return -1;
                        }
                //convert ANSI date/time to Mac date/time
                __Ansi2MacTime(tmb, &dt);
                Date2Secs(&dt, &timeval);
                }

   cinfoPB.dirInfo.ioVRefNum = 0;
   cinfoPB.dirInfo.ioDrDirID = 0;
   cinfoPB.dirInfo.ioFDirIndex = 0;
   cinfoPB.dirInfo.ioNamePtr = szBuf;
   cinfoPB.dirInfo.ioDrMdDat = timeval;

   osErr = PBSetCatInfoSync(&cinfoPB);
        switch (osErr)
                {
                case noErr:
                   errno = 0;
                   break;
                case extFSErr:
                case bdNamErr:
                case fnfErr:
                case ioErr:
                case nsvErr:
                    errno = ENOENT;
                    return -1;
                case fLckdErr:
                case vLckdErr:
                case wPrErr:
                    errno = EACCES;
                    return -1;
                default:
                    return -1;
                }

        return 0;
}

/***
*void __Ansi2MacTime(struct tm *, DateTimeRec *) - internal
*
*
*Purpose:
*  convert ansi time to Mac time
*
*Entry:
*       struct tm *tmb - ansi time
*  DateTimeRec - Mac time
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

void __Ansi2MacTime(struct tm *tmb, DateTimeRec * pdt)
{
      pdt->second =  tmb->tm_sec;
      pdt->minute =  tmb->tm_min;
      pdt->hour = tmb->tm_hour;
      pdt->day = tmb->tm_mday;
      pdt->month = tmb->tm_mon + 1;
      pdt->year = tmb->tm_year + 1900;
      pdt->dayOfWeek = tmb->tm_wday + 1;
      return;
}


#endif  /* defined (_M_MPPC) || defined (_M_M68K) */

#endif  /* _WIN32 */
