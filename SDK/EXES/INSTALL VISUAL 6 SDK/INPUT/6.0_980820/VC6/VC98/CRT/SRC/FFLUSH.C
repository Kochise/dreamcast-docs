/***
*fflush.c - flush a stream buffer
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines fflush() - flush the buffer on a stream
*               _flushall() - flush all stream buffers
*
*******************************************************************************/

#ifdef _WIN32


#include <cruntime.h>
#include <stdio.h>
#include <file2.h>
#include <io.h>
#include <mtdll.h>
#include <internal.h>


/* Values passed to flsall() to distinguish between _flushall() and
 * fflush(NULL) behavior
 */
#define FLUSHALL        1
#define FFLUSHNULL      0

/* Core routine for fflush(NULL) and flushall()
 */
static int __cdecl flsall(int);


/***
*int fflush(stream) - flush the buffer on a stream
*
*Purpose:
*       if file open for writing and buffered, flush the buffer. if problems
*       flushing the buffer, set the stream flag to error
*       Always flushes the stdio stream and forces a commit to disk if file
*       was opened in commit mode.
*
*Entry:
*       FILE *stream - stream to flush
*
*Exit:
*       returns 0 if flushed successfully, or no buffer to flush
*       returns EOF and sets file error flag if fails.
*       FILE struct entries affected: _ptr, _cnt, _flag.
*
*Exceptions:
*
*******************************************************************************/

#ifdef _MT

int __cdecl fflush (
        REG1 FILE *stream
        )
{
        int rc;

        /* if stream is NULL, flush all streams
         */
        if ( stream == NULL )
                return(flsall(FFLUSHNULL));

        _lock_str(stream);

        rc = _fflush_lk(stream);

        _unlock_str(stream);

        return(rc);
}


/***
*_fflush_lk() - Flush the buffer on a stream (stream is already locked)
*
*Purpose:
*       Core flush routine; assumes stream lock is held by caller.
*
*       [See fflush() above for more information.]
*
*Entry:
*       [See fflush()]
*Exit:
*       [See fflush()]
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _fflush_lk (
        REG1 FILE *str
        )
{

#else  /* _MT */

int __cdecl fflush (
        REG1 FILE *str
        )
{

        /* if stream is NULL, flush all streams */
        if ( str == NULL ) {
                return(flsall(FFLUSHNULL));
        }

#endif  /* _MT */

        if (_flush(str) != 0) {
                /* _flush failed, don't attempt to commit */
                return(EOF);
        }

        /* lowio commit to ensure data is written to disk */
        if (str->_flag & _IOCOMMIT) {
                return (_commit(_fileno(str)) ? EOF : 0);
        }
        return 0;
}


/***
*int _flush(stream) - flush the buffer on a single stream
*
*Purpose:
*       If file open for writing and buffered, flush the buffer.  If
*       problems flushing the buffer, set the stream flag to error.
*       Multi-thread version assumes stream lock is held by caller.
*
*Entry:
*       FILE* stream - stream to flush
*
*Exit:
*       Returns 0 if flushed successfully, or if no buffer to flush.,
*       Returns EOF and sets file error flag if fails.
*       File struct entries affected: _ptr, _cnt, _flag.
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _flush (
        FILE *str
        )
{
        REG1 FILE *stream;
        REG2 int rc = 0; /* assume good return */
        REG3 int nchar;

        /* Init pointer to stream */
        stream = str;


        if ((stream->_flag & (_IOREAD | _IOWRT)) == _IOWRT && bigbuf(stream)
                && (nchar = stream->_ptr - stream->_base) > 0)
        {
                if ( _write(_fileno(stream), stream->_base, nchar) == nchar ) {
                        /* if this is a read/write file, clear _IOWRT so that
                         * next operation can be a read
                         */
                        if ( _IORW & stream->_flag )
                                stream->_flag &= ~_IOWRT;
                }
                else {
                        stream->_flag |= _IOERR;
                        rc = EOF;
                }
        }

        stream->_ptr = stream->_base;
        stream->_cnt = 0;

        return(rc);
}


/***
*int _flushall() - flush all output buffers
*
*Purpose:
*       flushes all the output buffers to the file, clears all input buffers.
*
*Entry:
*       None.
*
*Exit:
*       returns number of open streams
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _flushall (
        void
        )
{
        return(flsall(FLUSHALL));
}


/***
*static int flsall(flushflag) - flush all output buffers
*
*Purpose:
*       Flushes all the output buffers to the file and, if FLUSHALL is passed,
*       clears all input buffers. Core routine for both fflush(NULL) and
*       flushall().
*
*       MTHREAD Note: All the locking/unlocking required for both fflush(NULL)
*       and flushall() is performed in this routine.
*
*Entry:
*       int flushflag - flag indicating the exact semantics, there are two
*                       legal values: FLUSHALL and FFLUSHNULL
*
*Exit:
*       if flushflag == FFLUSHNULL then flsbuf returns:
                0, if successful
*               EOF, if an error occurs while flushing one of the streams
*
*       if flushflag == FLUSHALL then flsbuf returns the number of streams
*       successfully flushed
*
*Exceptions:
*
*******************************************************************************/

static int __cdecl flsall (
        int flushflag
        )
{
        REG1 int i;
        int count = 0;
        int errcode = 0;

        _mlock(_IOB_SCAN_LOCK);

        for ( i = 0 ; i < _nstream ; i++ ) {

                if ( (__piob[i] != NULL) && (inuse((FILE *)__piob[i])) ) {

#ifdef _MT
                        /*
                         * lock the stream. this is not done until testing
                         * the stream is in use to avoid unnecessarily creating
                         * a lock for every stream. the price is having to
                         * retest the stream after the lock has been asserted.
                         */
                        _lock_str2(i, __piob[i]);

                        /*
                         * if the stream is STILL in use (it may have been
                         * closed before the lock was asserted), see about
                         * flushing it.
                         */
                        if ( inuse((FILE *)__piob[i]) ) {
#endif  /* _MT */

                        if ( flushflag == FLUSHALL ) {
                                /*
                                 * FLUSHALL functionality: fflush the read or
                                 * write stream and, if successful, update the
                                 * count of flushed streams
                                 */
                                if ( _fflush_lk(__piob[i]) != EOF )
                                        /* update count of successfully flushed
                                         * streams
                                         */
                                        count++;
                        }
                        else if ( (flushflag == FFLUSHNULL) &&
                                  (((FILE *)__piob[i])->_flag & _IOWRT) ) {
                                /*
                                 * FFLUSHNULL functionality: fflush the write
                                 * stream and kept track of the error, if one
                                 * occurs
                                 */
                                if ( _fflush_lk(__piob[i]) == EOF )
                                        errcode = EOF;
                        }

#ifdef _MT
                        }
                        _unlock_str2(i, __piob[i]);
#endif  /* _MT */
                }
        }

        _munlock(_IOB_SCAN_LOCK);

        if ( flushflag == FLUSHALL )
                return(count);
        else
                return(errcode);
}


#else  /* _WIN32 */

#if defined (_M_MPPC) || defined (_M_M68K)


#include <cruntime.h>
#include <stdio.h>
#include <file2.h>
#include <io.h>
#include <internal.h>

/* define the entry in pre-terminator table */

#pragma data_seg(".CRT$XPX")

static _PVFV __pendstdio = _endstdio;

#pragma data_seg()

#ifndef CRTDLL
/*
 * _cflush is a dummy variable used to pull in _endstdio() when any STDIO
 * routine is included in the user program.
 */
int _cflush = 1;
#endif  /* CRTDLL */


/* Values passed to flsall() to distinguish between _flushall() and
 * fflush(NULL) behavior
 */
#define FLUSHALL        1
#define FFLUSHNULL      0

/* Core routine for fflush(NULL) and flushall()
 */
static int __cdecl flsall(int);

/***
*int fflush(stream) - flush the buffer on a stream
*
*Purpose:
*       if file open for writing and buffered, flush the buffer. if problems
*       flushing the buffer, set the stream flag to error
*       Always flushes the stdio stream and forces a commit to disk if file
*       was opened in commit mode.
*
*Entry:
*       FILE *stream - stream to flush
*
*Exit:
*       returns 0 if flushed successfully, or no buffer to flush
*       returns EOF and sets file error flag if fails.
*       FILE struct entries affected: _ptr, _cnt, _flag.
*
*Exceptions:
*
*******************************************************************************/

int __cdecl fflush (
        REG1 FILE *str
        )
{

        /* if stream is NULL, flush all streams */
        if ( str == NULL ) {
                return(flsall(FFLUSHNULL));
        }

        if (_flush(str) != 0) {
                /* _flush failed, don't attempt to commit */
                return(EOF);
        }

        /* lowio commit to ensure data is written to disk */
        if (str->_flag & _IOCOMMIT) {
                return (_commit(_fileno(str)) ? EOF : 0);
        }
        return (0);
}


/***
*int _flush(stream) - flush the buffer on a single stream
*
*Purpose:
*       If file open for writing and buffered, flush the buffer.  If
*       problems flushing the buffer, set the stream flag to error.
*       Multi-thread version assumes stream lock is held by caller.
*
*Entry:
*       FILE* stream - stream to flush
*
*Exit:
*       Returns 0 if flushed successfully, or if no buffer to flush.,
*       Returns EOF and sets file error flag if fails.
*       File struct entries affected: _ptr, _cnt, _flag.
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _flush (
        FILE *str
        )
{
        REG1 FILE *stream;
        REG2 int rc = 0; /* assume good return */
        REG3 int nchar;

        /* Init pointer to stream */
        stream = str;

        if ((stream->_flag & (_IOREAD | _IOWRT)) == _IOWRT && bigbuf(stream)
                && (nchar = stream->_ptr - stream->_base) > 0)
        {
                if ( _write(_fileno(stream), stream->_base, nchar) == nchar ) {
                        /* if this is a read/write file, clear _IOWRT so that
                         * next operation can be a read
                         */
                        if ( _IORW & stream->_flag )
                                stream->_flag &= ~_IOWRT;
                }
                else {
                        stream->_flag |= _IOERR;
                        rc = EOF;
                }
        }

        stream->_ptr = stream->_base;
        stream->_cnt = 0;

        return(rc);
}


/***
*int _flushall() - flush all output buffers
*
*Purpose:
*       flushes all the output buffers to the file, clears all input buffers.
*
*Entry:
*       None.
*
*Exit:
*       returns number of open streams
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _flushall (
        void
        )
{
        return(flsall(FLUSHALL));
}


/***
*static int flsall(flushflag) - flush all output buffers
*
*Purpose:
*       Flushes all the output buffers to the file and, if FLUSHALL is passed,
*       clears all input buffers. Core routine for both fflush(NULL) and
*       flushall().
*
*Entry:
*       int flushflag - flag indicating the exact semantics, there are two
*                       legal values: FLUSHALL and FFLUSHNULL
*
*Exit:
*       if flushflag == FFLUSHNULL then flsbuf returns:
*               0, if successful
*               EOF, if an error occurs while flushing one of the streams
*
*       if flushflag == FLUSHALL then flsbuf returns the number of streams
*       successfully flushed
*
*Exceptions:
*
*******************************************************************************/

static int __cdecl flsall (
        int flushflag
        )
{
        REG1 FILE *stream = _iob;
        REG2 int count = 0;
        int errcode = 0;

        for (; stream <= _lastiob; stream++) {

                if ( (flushflag == FLUSHALL) && inuse(stream) ) {
                        /* FLUSHALL functionality: fflush the read or write
                         * stream and, if successful, update the count of
                         * flushed streams
                         */
                        if ( fflush(stream) != EOF )
                                /* update count of successfully flushed
                                 * streams
                                 */
                                count++;
                }
                else if ( (flushflag == FFLUSHNULL) &&
                (stream->_flag & _IOWRT) ) {
                        /* FFLUSHNULL functionality: fflush the write stream
                         * and kept track of the error, if one occurs
                         */
                        if ( fflush(stream) == EOF )
                                errcode = EOF;
                }

        }

        if ( flushflag == FLUSHALL )
                return(count);
        else
                return(errcode);
}


/***
* _endstdio - Terminate the stdio system
*
*Purpose:
*       Terminate the stdio system
*
*       (1) Flush all streams.  (Do this even if we're going to
*       call fcloseall since that routine won't do anything to the
*       std streams.)
*
*       (2) If returning to caller, close all streams.  This is
*       not necessary if the exe is terminating because the OS will
*       close the files for us (much more efficiently, too).
*
*Entry: <void>
*
*Exit:  <void>
*
*Uses:
*
*Exceptions:
*
*******************************************************************************/

void _endstdio(void)

{

        /* flush all streams */
        _flushall();

        /* if in callable exit, close all streams */
        if (_exitflag)
                _fcloseall();

}


#endif  /* defined (_M_MPPC) || defined (_M_M68K) */

#endif  /* _WIN32 */
