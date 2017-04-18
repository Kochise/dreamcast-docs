/***
*_flsbuf.c - flush buffer and output character.
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _flsbuf() - flush a file buffer and output a character.
*       defines _flswbuf() - flush a file buffer and output a wide character.
*       If no buffer, make one.
*
*******************************************************************************/

#ifdef _WIN32


#include <cruntime.h>
#include <stdio.h>
#include <file2.h>
#include <io.h>
#include <dbgint.h>
#include <malloc.h>
#include <msdos.h>
#include <wchar.h>
#include <internal.h>
#ifdef _MT
#include <mtdll.h>
#endif  /* _MT */
#include <tchar.h>

#ifndef _UNICODE

/***
*int _flsbuf(ch, stream) - flush buffer and output character.
*
*Purpose:
*       flush a buffer if this stream has one. if not, try to get one. put the
*       next output char (ch) into the buffer (or output it immediately if this
*       stream can't have a buffer). called only from putc. intended for use
*       only within library.
*
*       [NOTE: Multi-thread - It is assumed that the caller has aquired
*       the stream lock.]
*
*Entry:
*       FILE *stream - stream to flish and write on
*       int ch - character to output.
*
*Exit:
*       returns -1 if FILE is actually a string, or if can't write ch to
*       unbuffered file, or if we flush a buffer but the number of chars
*       written doesn't agree with buffer size.  Otherwise returns ch.
*       all fields in FILE struct can be affected except _file.
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _flsbuf (
        int ch,
        FILE *str
        )

#else  /* _UNICODE */

/***
*int _flswbuf(ch, stream) - flush buffer and output wide character.
*
*Purpose:
*       flush a buffer if this stream has one. if not, try to get one. put the
*       next output wide char (ch) into the buffer (or output it immediately if this
*       stream can't have a buffer). called only from putwc. intended for use
*       only within library.
*
*       [NOTE: Multi-thread - It is assumed that the caller has aquired
*       the stream lock.]
*
*Entry:
*       FILE *stream - stream to flish and write on
*       int ch - wide character to output.
*
*Exit:
*       returns -1 if FILE is actually a string, or if can't write ch to
*       unbuffered file, or if we flush a buffer but the number of wide chars
*       written doesn't agree with buffer size.  Otherwise returns ch.
*       all fields in FILE struct can be affected except _file.
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _flswbuf (
        int ch,
        FILE *str
        )

#endif  /* _UNICODE */

{

        REG1 FILE *stream;
        REG2 int charcount;
        REG3 int written;
        int fh;

        _ASSERTE(str != NULL);

        /* Init file handle and pointers */
        stream = str;
        fh = _fileno(stream);

        if (!(stream->_flag & (_IOWRT|_IORW)) || (stream->_flag & _IOSTRG)) {
                stream->_flag |= _IOERR;
                return(_TEOF);
        }

        /* Check that _IOREAD is not set or, if it is, then so is _IOEOF. Note
           that _IOREAD and IOEOF both being set implies switching from read to
           write at end-of-file, which is allowed by ANSI. Note that resetting
           the _cnt and _ptr fields amounts to doing an fflush() on the stream
           in this case. Note also that the _cnt field has to be reset to 0 for
           the error path as well (i.e., _IOREAD set but _IOEOF not set) as
           well as the non-error path. */

        if (stream->_flag & _IOREAD) {
                stream->_cnt = 0;
                if (stream->_flag & _IOEOF) {
                        stream->_ptr = stream->_base;
                        stream->_flag &= ~_IOREAD;
                }
                else {
                        stream->_flag |= _IOERR;
                        return(_TEOF);
                }
        }

        stream->_flag |= _IOWRT;
        stream->_flag &= ~_IOEOF;
        written = charcount = stream->_cnt = 0;

        /* Get a buffer for this stream, if necessary. */
        if (!anybuf(stream)) {

                /* Do NOT get a buffer if (1) stream is stdout/stderr, and
                   (2) stream is NOT a tty.
                   [If stdout/stderr is a tty, we do NOT set up single char
                   buffering. This is so that later temporary buffering will
                   not be thwarted by the _IONBF bit being set (see
                   _stbuf/_ftbuf usage).]
                */
                if (!( ((stream==stdout) || (stream==stderr))
                && (_isatty(fh)) ))

                        _getbuf(stream);

        } /* end !anybuf() */

        /* If big buffer is assigned to stream... */
        if (bigbuf(stream)) {

                _ASSERTE(("inconsistent IOB fields", stream->_ptr - stream->_base >= 0));

                charcount = stream->_ptr - stream->_base;
                stream->_ptr = stream->_base + sizeof(TCHAR);
                stream->_cnt = stream->_bufsiz - sizeof(TCHAR);

                if (charcount > 0)
                        written = _write(fh, stream->_base, charcount);
                else
                        if (_osfile_safe(fh) & FAPPEND)
                                _lseek(fh,0L,SEEK_END);

#ifndef _UNICODE
                *stream->_base = (char)ch;
#else  /* _UNICODE */
                *(wchar_t *)(stream->_base) = (wchar_t)(ch & 0xffff);
#endif  /* _UNICODE */
        }

    /* Perform single character output (either _IONBF or no buffering) */
        else {
                charcount = sizeof(TCHAR);
#ifndef _UNICODE
                written = _write(fh, &ch, charcount);
#else  /* _UNICODE */
                {
                        char mbc[4];

                        *(wchar_t *)mbc = (wchar_t)(ch & 0xffff);
                        written = _write(fh, mbc, charcount);
                }
#endif  /* _UNICODE */
        }

        /* See if the _write() was successful. */
        if (written != charcount) {
                stream->_flag |= _IOERR;
                return(_TEOF);
        }

#ifndef _UNICODE
        return(ch & 0xff);
#else  /* _UNICODE */
        return(ch & 0xffff);
#endif  /* _UNICODE */

}


#else  /* _WIN32 */

#if defined (_M_MPPC) || defined (_M_M68K)


#include <cruntime.h>
#include <stdio.h>
#include <file2.h>
#include <io.h>
#include <dbgint.h>
#include <malloc.h>
#include <msdos.h>
#include <internal.h>

/***
*int _flsbuf(ch, stream) - flush buffer and output character.
*
*Purpose:
*       flush a buffer if this stream has one. if not, try to get one. put the
*       next output char (ch) into the buffer (or output it immediately if this
*       stream can't have a buffer). called only from putc. intended for use
*       only within library.
*
*Entry:
*       FILE *stream - stream to flish and write on
*       char ch - character to output.
*
*Exit:
*       returns -1 if FILE is actually a string, or if can't write ch to
*       unbuffered file, or if we flush a buffer but the number of chars
*       written doesn't agree with buffer size.  Otherwise returns ch.
*       all fields in FILE struct can be affected except _file.
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _flsbuf (
        int ch,
        FILE *str
        )
{
        REG1 FILE *stream;
        REG2 int charcount;
        REG3 int written;
        int fh;
        char chbuf;

        _ASSERTE(str != NULL);

        /* Init file handle and pointers */
        stream = str;
        fh = _fileno(stream);

        if (!(stream->_flag & (_IOWRT|_IORW)) || (stream->_flag & _IOSTRG)) {
                stream->_flag |= _IOERR;
                return(-1);
        }

        /* Check that _IOREAD is not set or, if it is, then so is _IOEOF. Note
           that _IOREAD and IOEOF both being set implies switching from read to
           write at end-of-file, which is allowed by ANSI. Note that resetting
           the _cnt and _ptr fields amounts to doing an fflush() on the stream
           in this case. Note also that the _cnt field has to be reset to 0 for
           the error path as well (i.e., _IOREAD set but _IOEOF not set) as
           well as the non-error path. */

        if (stream->_flag & _IOREAD) {
                stream->_cnt = 0;
                if (stream->_flag & _IOEOF) {
                        stream->_ptr = stream->_base;
                        stream->_flag &= ~_IOREAD;
                }
                else {
                        stream->_flag |= _IOERR;
                        return(-1);
                }
        }

        stream->_flag |= _IOWRT;
        stream->_flag &= ~_IOEOF;
        written = charcount = stream->_cnt = 0;

        /* Get a buffer for this stream, if necessary. */
        if (!anybuf(stream)) {

                /* Do NOT get a buffer if (1) stream is stdout/stderr, and
                   (2) stream is NOT a tty.
                   [If stdout/stderr is a tty, we do NOT set up single char
                   buffering. This is so that later temporary buffering will
                   not be thwarted by the _IONBF bit being set (see
                   _stbuf/_ftbuf usage).]
                */
                if (!( ((stream==stdout) || (stream==stderr))
                && (_isatty(fh)) ))

                        _getbuf(stream);

        } /* end !anybuf() */

        /* If big buffer is assigned to stream... */
        if (bigbuf(stream)) {

                _ASSERTE(("inconsistent IOB fields", stream->_ptr - stream->_base >= 0));

                charcount = stream->_ptr - stream->_base;
                stream->_ptr = stream->_base + 1;
                stream->_cnt = stream->_bufsiz - 1;

                if (charcount > 0)
                        written = _write(fh, stream->_base, charcount);
                else
                        if (_osfile[fh] & FAPPEND)
                                _lseek(fh,0L,SEEK_END);

                *stream->_base = (char)ch;
        }

        /* Perform single character output (either _IONBF or no buffering) */
        else {
                charcount = 1;
                chbuf = (char)ch;
                written = _write(fh, &chbuf, charcount);
        }

        /* See if the _write() was successful. */
        if (written != charcount) {
                stream->_flag |= _IOERR;
                return(-1);
        }

        return(ch & 0xff);
}


#endif  /* defined (_M_MPPC) || defined (_M_M68K) */

#endif  /* _WIN32 */
