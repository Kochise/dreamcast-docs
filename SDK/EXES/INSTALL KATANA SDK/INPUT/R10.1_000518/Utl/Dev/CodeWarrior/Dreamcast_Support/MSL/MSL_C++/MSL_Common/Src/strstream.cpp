/*  Metrowerks Standard Library  */

/*  $Date: 1999/01/23 00:26:07 $ 
 *  $Revision: 1.5 $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */

/************************************************************************/
/*	Project...:	Standard C++ Library									*/
/*	Name......:	strstream.cpp											*/
/*	Purpose...:	<strstream> support										*/
/************************************************************************/

#include <strstream>

#ifndef _MSL_NO_CPP_NAMESPACE
	namespace std {
#endif

// strstreambuf

strstreambuf::~strstreambuf()
{
	if (strmode_ & allocated != 0 && strmode_ & frozen == 0)
	{
		if (pfree_ != 0)
			pfree_(eback());
		else
			delete [] eback();
	}
}

void
strstreambuf::freeze(bool freezefl)
{
	if (strmode_ & dynamic != 0)
	{
		if (freezefl)
			strmode_ |= frozen;
		else
			strmode_ &= (strstate)~frozen;
	}
}

strstreambuf::int_type
strstreambuf::overflow (int_type c)
{
	if (c == EOF)
		return 0;
	if (pptr() < epptr())
	{
		*pptr() = (char)c;
		pbump(1);
		return c;
	}
	if (strmode_ & dynamic == 0 || strmode_ & frozen != 0)
		return EOF;
	streamsize getlen = egptr() - eback();
	streamsize getpos = gptr() - eback();
	streamsize putlen = epptr() - pbase();
	streamsize putpos = pptr() - pbase();
	streamsize oldsize = getlen + putlen;
	streamsize newsize;
	if (oldsize < alsize_)
		newsize = alsize_;
	else
		newsize = 2 * oldsize;
	char* newbuffer = 0;
	if (palloc_ != 0)
		newbuffer = (char*)palloc_((size_t)newsize);
	else
		newbuffer = new(nothrow) char [newsize];
	if (newbuffer == 0)
		return EOF;
	if (oldsize != 0)
	{
		char* p = newbuffer;
		char* g = eback();
		for (streamsize i = 0; i < oldsize; ++i)
			*p++ = *g++;
		if (pfree_ != 0)
			pfree_(eback());
		else
			delete [] eback();
	}
	setg(newbuffer, newbuffer + getpos, newbuffer + getlen);
	newbuffer += getlen;
	newsize -= getlen;
	setp(newbuffer, newbuffer + newsize);  // hh 980910
	pbump(putpos);
	*pptr() = (char)c;
	pbump(1);
	return c;
}

strstreambuf::int_type
strstreambuf::pbackfail(int_type c)
{
	if (gptr() <= eback())
		return EOF;
	gbump(-1);
	if (c == EOF)
		return 0;
	if ((char)c == *gptr())
		return c;
	if (strmode_ & constant == 0)
	{
		*gptr() = (char)c;
		return c;
	}
	gbump(1);
	return EOF;
}

strstreambuf::int_type
strstreambuf::underflow()
{
	if (gptr() < egptr())
		return (unsigned char)*gptr();
	if (egptr() < pptr())
	{
		setg(eback(), gptr(), pptr());
		setp(pptr(), epptr());
		return (unsigned char)*gptr();
	}
	return EOF;
}

strstreambuf::pos_type
strstreambuf::seekoff(off_type off, ios_base::seekdir way, ios_base::openmode which)
{
	off_type newoff = -1;
	if (which & ios_base::in)
	{
		switch (way)
		{
		case ios_base::beg:
			newoff = 0;
			break;
		case ios_base::cur:
			newoff = gptr() - eback();
			break;
		case ios_base::end:
			newoff = egptr() - eback();
			break;
		default:
			return pos_type(-1);
		}
		newoff += off;
		if (newoff < 0 || newoff > egptr() - eback())
			return pos_type(-1);
		setg(eback(), eback()+newoff, egptr());
	}
	if (which & ios_base::out)
	{
		switch (way)
		{
		case ios_base::beg:
			newoff = 0;
			break;
		case ios_base::cur:
			newoff = pptr() - pbase();
			break;
		case ios_base::end:
			newoff = epptr() - pbase();
			break;
		default:
			return pos_type(-1);
		}
		newoff += off;
		if (newoff < 0 || newoff > epptr() - pbase())
			return pos_type(-1);
		setp(pbase(), epptr());
		pbump(newoff);
	}
	return pos_type(newoff);
}

strstreambuf::pos_type
strstreambuf::seekpos(pos_type sp, ios_base::openmode which)
{
	off_type newoff = -1;
	if (which & ios_base::in)
	{
		newoff = sp;  // hh 980909
		if (newoff < 0 || newoff > egptr() - eback())
			return pos_type(-1);
		setg(eback(), eback()+newoff, egptr());
	}
	if (which & ios_base::out)
	{
		newoff = sp;  // hh 980909
		if (newoff < 0 || newoff > epptr() - pbase())
			return pos_type(-1);
		setp(pbase(), epptr());
		pbump(newoff);
	}
	return pos_type(newoff);
}

streambuf*
strstreambuf::setbuf(char*, streamsize)
{
	return 0;
}

void
strstreambuf::init(char* gnext_arg, streamsize n, char* pbeg_arg)
{
	streamsize N = n;
	if (N == 0)
		N = (streamsize)strlen(gnext_arg);
	else if (N < 0)
		N = INT_MAX;
	if (pbeg_arg == 0)
		setg(gnext_arg, gnext_arg, gnext_arg + N);
	else
	{
		setg(gnext_arg, gnext_arg, pbeg_arg);
		setp(pbeg_arg, pbeg_arg + N);
	}
}

// istrstream

// ostrstream

#ifndef _MSL_NO_CPP_NAMESPACE
	}
#endif

// hh 980910 Fixed bug in strstreambuf::overflow, pend was being incorrectly set
// hh 990120 changed name of MSIPL flags
