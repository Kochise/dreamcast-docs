/***
*fgetwc.c - get a wide character from a stream
*
*       Copyright (c) 1993-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines fgetwc() - read a wide character from a stream
*
*******************************************************************************/


#include <cruntime.h>
#include <stdio.h>
#include <stdlib.h>
#include <dbgint.h>
#include <file2.h>
#include <internal.h>
#include <mtdll.h>
#include <msdos.h>
#include <errno.h>
#include <wchar.h>
#include <tchar.h>
#include <setlocal.h>

#ifdef _MT

/***
*wint_t fgetwc(stream) - read a wide character from a stream
*
*Purpose:
*       reads a wide character from the given stream
*
*Entry:
*       FILE *stream - stream to read wide character from
*
*Exit:
*       returns the wide character read
*       returns WEOF if at end of file or error occurred
*
*Exceptions:
*
*******************************************************************************/

wint_t __cdecl fgetwc (
        REG1 FILE *stream
        )
{
        wint_t retval;

        _ASSERTE(stream != NULL);

        _lock_str(stream);
        retval = _getwc_lk(stream);
        _unlock_str(stream);

        return(retval);
}

/***
*_getwc_lk() -  getwc() core routine (locked version)
*
*Purpose:
*       Core getwc() routine; assumes stream is already locked.
*
*       [See getwc() above for more info.]
*
*Entry: [See getwc()]
*
*Exit:  [See getwc()]
*
*Exceptions:
*
*******************************************************************************/

wint_t __cdecl _getwc_lk (
        REG1 FILE *stream
        )
{

#else  /* _MT */

wint_t __cdecl fgetwc (
        REG1 FILE *stream
        )
{

#endif  /* _MT */

        if (!(stream->_flag & _IOSTRG) && (_osfile_safe(_fileno(stream)) &
              FTEXT))
        {
                int size = 1;
                int ch;
                char mbc[4];
                wchar_t wch;

                /* text (multi-byte) mode */
                if ((ch = _getc_lk(stream)) == EOF)
                        return WEOF;

                mbc[0] = (char)ch;

                if (isleadbyte((unsigned char)mbc[0]))
                {
                        if ((ch = _getc_lk(stream)) == EOF)
                        {
                                ungetc(mbc[0], stream);
                                return WEOF;
                        }
                        mbc[1] = (char)ch;
                        size = 2;
                }
                if (mbtowc(&wch, mbc, size) == -1)
                {
                        /*
                         * Conversion failed! Set errno and return
                         * failure.
                         */
                        errno = EILSEQ;
                        return WEOF;
                }
                return wch;
        }
        /* binary (Unicode) mode */
        if ((stream->_cnt -= sizeof(wchar_t)) >= 0)
                return *((wchar_t *)(stream->_ptr))++;
        else
                return (wint_t) _filwbuf(stream);
}

#undef getwc

wint_t __cdecl getwc (
        FILE *stream
        )
{
        return fgetwc(stream);
}


