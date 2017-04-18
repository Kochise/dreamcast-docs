/***
*write.c - write to a file handle
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _write() - write to a file handle
*
*******************************************************************************/

#ifndef _MAC


#include <cruntime.h>
#include <oscalls.h>
#include <io.h>
#include <errno.h>
#include <msdos.h>
#include <mtdll.h>
#include <stdlib.h>
#include <string.h>
#include <internal.h>

#define BUF_SIZE    1025    /* size of LF translation buffer */

#define LF '\n'      /* line feed */
#define CR '\r'      /* carriage return */
#define CTRLZ 26     /* ctrl-z */

/***
*int _write(fh, buf, cnt) - write bytes to a file handle
*
*Purpose:
*       Writes count bytes from the buffer to the handle specified.
*       If the file was opened in text mode, each LF is translated to
*       CR-LF.  This does not affect the return value.  In text
*       mode ^Z indicates end of file.
*
*       Multi-thread notes:
*       (1) _write() - Locks/unlocks file handle
*           _write_lk() - Does NOT lock/unlock file handle
*
*Entry:
*       int fh - file handle to write to
*       char *buf - buffer to write from
*       unsigned int cnt - number of bytes to write
*
*Exit:
*       returns number of bytes actually written.
*       This may be less than cnt, for example, if out of disk space.
*       returns -1 (and set errno) if fails.
*
*Exceptions:
*
*******************************************************************************/

#ifdef _MT

/* define normal version that locks/unlocks, validates fh */
int __cdecl _write (
        int fh,
        const void *buf,
        unsigned cnt
        )
{
        int r;                          /* return value */

        /* validate handle */
        if ( ((unsigned)fh >= (unsigned)_nhandle) ||
             !(_osfile(fh) & FOPEN) )
        {
                /* out of range -- return error */
                errno = EBADF;
                _doserrno = 0;  /* not o.s. error */
                return -1;
        }

        _lock_fh(fh);                   /* lock file */
        r = _write_lk(fh, buf, cnt);    /* write bytes */
        _unlock_fh(fh);                 /* unlock file */

        return r;
}

/* now define version that doesn't lock/unlock, validate fh */
int __cdecl _write_lk (
        int fh,
        const void *buf,
        unsigned cnt
        )
{
        int lfcount;            /* count of line feeds */
        int charcount;          /* count of chars written so far */
        int written;            /* count of chars written on this write */
        ULONG dosretval;        /* o.s. return value */
        char ch;                /* current character */
        char *p, *q;            /* pointers into buf and lfbuf resp. */
        char lfbuf[BUF_SIZE];   /* lf translation buffer */

#else  /* _MT */

/* now define normal version */
int __cdecl _write (
        int fh,
        const void *buf,
        unsigned cnt
        )
{
        int lfcount;            /* count of line feeds */
        int charcount;          /* count of chars written so far */
        int written;            /* count of chars written on this write */
        ULONG dosretval;        /* o.s. return value */
        char ch;                /* current character */
        char *p, *q;            /* pointers into buf and lfbuf resp. */
        char lfbuf[BUF_SIZE];   /* lf translation buffer */

        /* validate handle */
        if ( ((unsigned)fh >= (unsigned)_nhandle) ||
             !(_osfile(fh) & FOPEN) )
        {
                /* out of range -- return error */
                errno = EBADF;
                _doserrno = 0;  /* not o.s. error */
                return -1;
        }

#endif  /* _MT */

        lfcount = charcount = 0;        /* nothing written yet */

        if (cnt == 0)
                return 0;               /* nothing to do */


        if (_osfile(fh) & FAPPEND) {
                /* appending - seek to end of file; ignore error, because maybe
                   file doesn't allow seeking */
                (void)_lseek_lk(fh, 0, FILE_END);
        }

        /* check for text mode with LF's in the buffer */

        if ( _osfile(fh) & FTEXT ) {
                /* text mode, translate LF's to CR/LF's on output */

                p = (char *)buf;        /* start at beginning of buffer */
                dosretval = 0;          /* no OS error yet */

                while ( (unsigned)(p - (char *)buf) < cnt ) {
                        q = lfbuf;      /* start at beginning of lfbuf */

                        /* fill the lf buf, except maybe last char */
                        while ( q - lfbuf < BUF_SIZE - 1 &&
                            (unsigned)(p - (char *)buf) < cnt ) {
                                ch = *p++;
                                if ( ch == LF ) {
                                        ++lfcount;
                                        *q++ = CR;
                                }
                                *q++ = ch;
                        }

                        /* write the lf buf and update total */
                        if ( WriteFile( (HANDLE)_osfhnd(fh),
                                        lfbuf,
                                        q - lfbuf,
                                        (LPDWORD)&written,
                                        NULL) )
                        {
                                charcount += written;
                                if (written < q - lfbuf)
                                        break;
                        }
                        else {
                                dosretval = GetLastError();
                                break;
                        }
                }
        }
        else {
                /* binary mode, no translation */
                if ( WriteFile( (HANDLE)_osfhnd(fh),
                                (LPVOID)buf,
                                cnt,
                               (LPDWORD)&written,
                                NULL) )
                {
                        dosretval = 0;
                        charcount = written;
                }
                else
                        dosretval = GetLastError();
        }

        if (charcount == 0) {
                /* If nothing was written, first check if an o.s. error,
                   otherwise we return -1 and set errno to ENOSPC,
                   unless a device and first char was CTRL-Z */
                if (dosretval != 0) {
                        /* o.s. error happened, map error */
                        if (dosretval == ERROR_ACCESS_DENIED) {
                            /* wrong read/write mode should return EBADF, not
                               EACCES */
                                errno = EBADF;
                                _doserrno = dosretval;
                        }
                        else
                                _dosmaperr(dosretval);
                        return -1;
                }
                else if ((_osfile(fh) & FDEV) && *(char *)buf == CTRLZ)
                        return 0;
                else {
                        errno = ENOSPC;
                        _doserrno = 0;  /* no o.s. error */
                        return -1;
                }
        }
        else
                /* return adjusted bytes written */
                return charcount - lfcount;
}


#else  /* _MAC */


#include <cruntime.h>
#include <errno.h>
#include <msdos.h>
#include <stdlib.h>
#include <internal.h>
#include <macos\files.h>
#include <macos\errors.h>
#include <mpw.h>

/***
*int _write(fh, buf, cnt) - write bytes to a file handle
*
*Purpose:
*       Writes count bytes from the buffer to the handle specified.
*
*Entry:
*       int fh - file handle to write to
*       char *buf - buffer to write from
*       unsigned int cnt - number of bytes to write
*
*Exit:
*       returns number of bytes actually written.
*       This may be less than cnt, for example, if out of disk space.
*       returns -1 (and set errno) if fails.
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _write (
        int fh,
        const void *buf,
        unsigned cnt
        )
{
        OSErr osErr;
        int cbReturn;

        /* validate handle */
        if ( ((unsigned)fh >= (unsigned)_nfile) || !(_osfile[fh] & FOPEN) ||
             (_osfile[fh] & FRDONLY) )
        {
                /* out of range -- return error */
                errno = EBADF;
                _macerrno = 0;
                return -1;
        }
        if (_osfile[fh] & FDEV)
        {
                MPWFILE *pparm;

                 /* MPW console */

                pparm =  (MPWFILE *)_osfhnd[fh];
                pparm->count = cnt;
                (const void *)(pparm->pBuff) = buf;
                osErr = (*((pparm->pDevice)->write))(pparm);
                if (osErr)
                {
                        osErr = pparm->err;
                }
                else
                {
                        cbReturn = cnt - pparm->count;
                }
        }
        else
        {
                ParamBlockRec parm;

                /* File */

                parm.ioParam.ioRefNum = _osfhnd[fh];
                (const void *)parm.ioParam.ioBuffer = buf;
                parm.ioParam.ioReqCount = cnt;
                parm.ioParam.ioPosOffset = 0;
                if ( _osfile[fh] & FAPPEND)
                {
                        parm.ioParam.ioPosMode = fsFromLEOF;
                }
                else
                {
                        parm.ioParam.ioPosMode = fsAtMark;
                }
                osErr = PBWriteSync(&parm);
                cbReturn = parm.ioParam.ioActCount;
        }

        if (!osErr)
        {
                return cbReturn;
        }
        else
        {
                _dosmaperr(osErr);
                return -1;
        }

}


#endif  /* _MAC */
