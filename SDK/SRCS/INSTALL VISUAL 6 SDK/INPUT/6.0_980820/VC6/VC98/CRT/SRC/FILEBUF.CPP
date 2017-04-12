/***
*filebuf.cpp - core filebuf member functions
*
*       Copyright (c) 1991-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Contains the core member functions for filebuf class.
*
*******************************************************************************/

#include <cruntime.h>
#include <internal.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <crtdbg.h>
#include <sys\types.h>
#include <io.h>
#include <fstream.h>
#pragma hdrstop

#include <msdos.h>
#include <sys\stat.h>

const int filebuf::openprot     = 0644;

const int filebuf::sh_none      = 04000;        // deny rw
const int filebuf::sh_read      = 05000;        // deny wr
const int filebuf::sh_write     = 06000;        // deny rd

const int filebuf::binary       = O_BINARY;
const int filebuf::text         = O_TEXT;

/***
*filebuf::filebuf() - filebuf default constructor
*
*Purpose:
*       Default constructor.
*
*Entry:
*
*******************************************************************************/
        filebuf::filebuf()
: streambuf()
{
    x_fOpened = 0;
    x_fd = -1;
}


/***
*filebuf::filebuf(filedesc fd) - filebuf constructor
*
*Purpose:
*       Constructor.  Initialize filebuf and attach to file descriptor.
*
*Entry:
*       fd = file descriptor to attach to filebuf
*
*******************************************************************************/
        filebuf::filebuf(filedesc fd)
: streambuf()
{
    x_fOpened = 0;
    x_fd=fd;
}


/***
*filebuf::filebuf(filedesc fd, char* p, int len) - filebuf constructor
*
*Purpose:
*       Constructor.  Initialize filebuf and attach to file descriptor.
*
*Entry:
*       fd  = file descriptor to attach to filebuf
*       p   = user-supplied buffer
*       len = length of buffer
*
*******************************************************************************/
        filebuf::filebuf(filedesc fd, char* p, int len)
:    streambuf()
{
    filebuf::setbuf(p,len);
    x_fOpened = 0;
    x_fd=fd;
}


/***
*filebuf::~filebuf() - filebuf destructor
*
*Purpose:
*       Destructor.  Close attached file only if we opened it.
*
*Entry:
*       None.
*
*******************************************************************************/
        filebuf::~filebuf()
{
        lock();         // no need to unlock...
        if (x_fOpened)
            close();    // calls filebuf::sync()
        else
            filebuf::sync();
}


/***
*filebuf* filebuf::close() - close an attached file
*
*Purpose:
*       Close attached file.
*
*Entry:
*       None.
*Exit:
*       Returns NULL if error, otherwise returns "this" pointer.
*
*******************************************************************************/
filebuf* filebuf::close()
{
    int retval;
    if (x_fd==-1)
        return NULL;

    lock();
    retval = sync();

    if ((_close(x_fd)==-1) || (retval==EOF))
        {
        unlock();
        return NULL;
        }
    x_fd = -1;
    unlock();
    return this;
}

/***
*virtual int filebuf::overflow(int c) - overflow virtual function
*
*Purpose:
*       flush any characters in the reserve area and handle 'c'.
*
*Entry:
*       c = character to output (if not EOF)
*
*Exit:
*       Returns EOF if error, otherwise returns something else.
*
*Exceptions:
*       Returns EOF if error.
*
*******************************************************************************/
int filebuf::overflow(int c)
{
    if (allocate()==EOF)        // make sure there is a reserve area
        return EOF;
    if (filebuf::sync()==EOF) // sync before new buffer created below
        return EOF;

    if (!unbuffered())
        setp(base(),ebuf());

    if (c!=EOF)
        {
        if ((!unbuffered()) && (pptr() < epptr())) // guard against recursion
            sputc(c);
        else
            {
            if (_write(x_fd,&c,1)!=1)
                return(EOF);
            }
        }
    return(1);  // return something other than EOF if successful
}

/***
*virtual int filebuf::underflow() - underflow virtual function
*
*Purpose:
*       return next character in get area, or get more characters from source.
*
*Entry:
*       None.
*
*Exit:
*       Returns current character in file.  Does not advance get pointer.
*
*Exceptions:
*       Returns EOF if error.
*
*******************************************************************************/
int filebuf::underflow()
{
    int count;
    unsigned char tbuf;

    if (in_avail())
        return (int)(unsigned char) *gptr();

    if (allocate()==EOF)        // make sure there is a reserve area
        return EOF;
    if (filebuf::sync()==EOF)
        return EOF;

    if (unbuffered())
        {
        if (_read(x_fd,(void *)&tbuf,1)<=0)
            return EOF;
        return (int)tbuf;
        }

    if ((count=_read(x_fd,(void *)base(),blen())) <= 0)
        return EOF;     // reached EOF
    setg(base(),base(),base()+count);
    return (int)(unsigned char) *gptr();
}


/***
*virtual streampos filebuf::seekoff() - seekoff virtual function
*
*Purpose:
*       Seeks to given absolute or relative file offset.
*
*Entry:
*       off = offset to seek to relative to beginning, end or current
*               position in the file.
*       dir = one of ios::beg, ios::cur, or ios::end
*
*Exit:
*       Returns current file position after seek.
*
*Exceptions:
*       Returns EOF if error.
*
*******************************************************************************/
streampos filebuf::seekoff(streamoff off, ios::seek_dir dir, int)
{

    int fdir;
    long retpos;
    switch (dir) {
        case ios::beg :
            fdir = SEEK_SET;
            break;
        case ios::cur :
            fdir = SEEK_CUR;
            break;
        case ios::end :
            fdir = SEEK_END;
            break;
        default:
        // error
            return(EOF);
        }

    if (filebuf::sync()==EOF)
        return EOF;
    if ((retpos=_lseek(x_fd, off, fdir))==-1L)
        return (EOF);
    return((streampos)retpos);
}

/***
*virtual int filebuf::sync() - synchronize buffers with external file postion.
*
*Purpose:
*       Synchronizes buffer with external file, by flushing any output and/or
*       discarding any unread input data.  Discards any get or put area(s).
*
*Entry:
*       None.
*
*Exit:
*       Returns EOF if error, else 0.
*
*Exceptions:
*       Returns EOF if error.
*
*******************************************************************************/
int filebuf::sync()
{
        long count, nout;
        char * p;
        if (x_fd==-1)
            return(EOF);

        if (!unbuffered())
        {
            if ((count=out_waiting())!=0)
            {
                if ((nout =_write(x_fd,(void *) pbase(),(unsigned int)count)) != count)
                {
                    if (nout > 0) {
                        // should set _pptr -= nout
                        pbump(-(int)nout);
                        memmove(pbase(), pbase()+nout, (int)(count-nout));
                    }
                    return(EOF);
                }
            }
            setp(0,0); // empty put area

            if ((count=in_avail()) > 0)
            {
                // can't use seekoff here!!
#ifdef _WIN32
                if (_osfile(x_fd) & FTEXT)
#else  /* _WIN32 */
                if (_osfile[x_fd] & FTEXT)
#endif  /* _WIN32 */
                {
                    // If text mode, need to account for CR/LF etc.
                    for (p = gptr(); p < egptr(); p++)
                        if (*p == '\n')
                            count++;

                    // account for EOF if read, not counted by _read
#ifdef _WIN32
                    if ((_osfile(x_fd) & FEOFLAG))
#else  /* _WIN32 */
                    if ((_osfile[x_fd] & FEOFLAG))
#endif  /* _WIN32 */
                        count++;

                }
                if (_lseek(x_fd, -count, SEEK_CUR)==-1L)
                {
//                  unlock();
                    return (EOF);
                }
            }
            setg(0,0,0); // empty get area
        }
//      unlock();
        return(0);
}

/***
*virtual streambuf* filebuf::setbuf(char* ptr, int len) - set reserve area.
*
*Purpose:
*       Synchronizes buffer with external file, by flushing any output and/or
*       discarding any unread input data.  Discards any get or put area(s).
*
*Entry:
*       ptr = requested reserve area.  If NULL, request is for unbuffered.
*       len = size of reserve area.  If <= 0, request is for unbuffered.
*
*Exit:
*       Returns this pointer if request is honored, else NULL.
*
*Exceptions:
*       Returns NULL if request is not honored.
*
*******************************************************************************/
streambuf * filebuf::setbuf(char * ptr, int len)
{
    if (is_open() && (ebuf()))
        return NULL;
    if ((!ptr) || (len <= 0))
        unbuffered(1);
    else
        {
        lock();
        setb(ptr, ptr+len, 0);
        unlock();
        }
    return this;
}
