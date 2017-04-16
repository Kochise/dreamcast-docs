/***
*ungetc.c - unget a character from a stream
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines ungetc() - pushes a character back onto an input stream
*
*******************************************************************************/

#include <cruntime.h>
#include <stdio.h>
#include <file2.h>
#include <dbgint.h>
#include <internal.h>
#include <mtdll.h>

#ifdef _MT

/***
*int ungetc(ch, stream) - put a character back onto a stream
*
*Purpose:
*       Guaranteed one char pushback on a stream as long as open for reading.
*       More than one char pushback in a row is not guaranteed, and will fail
*       if it follows an ungetc which pushed the first char in buffer. Failure
*       causes return of EOF.
*
*Entry:
*       char ch - character to push back
*       FILE *stream - stream to push character onto
*
*Exit:
*       returns ch
*       returns EOF if tried to push EOF, stream not opened for reading or
*       or if we have already ungetc'd back to beginning of buffer.
*
*Exceptions:
*
*******************************************************************************/

int __cdecl ungetc (
        REG2 int ch,
        REG1 FILE *stream
        )
{
        int retval;

        _ASSERTE(stream != NULL);

        _lock_str(stream);

        retval = _ungetc_lk (ch, stream);

        _unlock_str(stream);

        return(retval);
}

/***
*_ungetc_lk() -  Ungetc() core routine (locked version)
*
*Purpose:
*       Core ungetc() routine; assumes stream is already locked.
*
*       [See ungetc() above for more info.]
*
*Entry: [See ungetc()]
*
*Exit:  [See ungetc()]
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _ungetc_lk (
        REG2 int ch,
        FILE *str
        )

{

#else  /* _MT */

int __cdecl ungetc (
        REG2 int ch,
        FILE *str
        )

{

#endif  /* _MT */

        REG1 FILE *stream;

        _ASSERTE(str != NULL);

        /* Init stream pointer and file descriptor */
        stream = str;

        /* Stream must be open for read and can NOT be currently in write mode.
           Also, ungetc() character cannot be EOF. */

        if (
              (ch == EOF) ||
              !(
                (stream->_flag & _IOREAD) ||
                ((stream->_flag & _IORW) && !(stream->_flag & _IOWRT))
               )
           )
                return(EOF);

        /* If stream is unbuffered, get one. */

        if (stream->_base == NULL)
                _getbuf(stream);

        /* now we know _base != NULL; since file must be buffered */

        if (stream->_ptr == stream->_base) {
                if (stream->_cnt)
                        /* my back is against the wall; i've already done
                         * ungetc, and there's no room for this one
                         */
                        return(EOF);

                stream->_ptr++;
        }

        if (stream->_flag & _IOSTRG) {
            /* If stream opened by sscanf do not modify buffer */
                if (*--stream->_ptr != (char)ch) {
                        ++stream->_ptr;
                        return(EOF);
                }
        } else
                *--stream->_ptr = (char)ch;

        stream->_cnt++;
        stream->_flag &= ~_IOEOF;
        stream->_flag |= _IOREAD;       /* may already be set */

        return(0xff & ch);
}
