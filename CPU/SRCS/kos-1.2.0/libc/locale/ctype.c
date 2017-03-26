/* Derived from Berkeley's ctype. Original license follows: */
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 * This product includes software developed by the University of
 * California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <ctype.h>

#undef isalpha
#undef isupper
#undef islower
#undef isdigit
#undef isxdigit
#undef isspace
#undef ispunct
#undef isalnum
#undef isblank
#undef isprint
#undef isgraph
#undef iscntrl
#undef isascii
#undef toascii
#undef tolower
#undef toupper

/* hardcoded POSIX locale... */
const char _ctype_[256] = {
	_C,	_C,	_C,	_C,	_C,	_C,	_C,	_C,	/* 00-07 */
	_C,	_C|_S,	_C|_S,	_C|_S,	_C|_S,	_C|_S,	_C,	_C,	/* 08-0f */
	_C,	_C,	_C,	_C,	_C,	_C,	_C,	_C,	/* 10-17 */
	_C,	_C,	_C,	_C,	_C,	_C,	_C,	_C,	/* 18-1f */
	_S|_B,	_P,	_P,	_P,	_P,	_P,	_P,	_P,	/* 20-27 */
	_P,	_P,	_P,	_P,	_P,	_P,	_P,	_P,	/* 28-2f */
	_N,	_N,	_N,	_N,	_N,	_N,	_N,	_N,	/* 30-37 */
	_N,	_N,	_P,	_P,	_P,	_P,	_P,	_P,	/* 38-3f */
	_P,	_U|_X,	_U|_X,	_U|_X,	_U|_X,	_U|_X,	_U|_X,	_U,	/* 40-47 */
	_U,	_U,	_U,	_U,	_U,	_U,	_U,	_U,	/* 48-4f */
	_U,	_U,	_U,	_U,	_U,	_U,	_U,	_U,	/* 50-57 */
	_U,	_U,	_U,	_P,	_P,	_P,	_P,	_P,	/* 58-5f */
	_P,	_L|_X,	_L|_X,	_L|_X,	_L|_X,	_L|_X,	_L|_X,	_L,	/* 60-67 */
	_L,	_L,	_L,	_L,	_L,	_L,	_L,	_L,	/* 68-6f */
	_L,	_L,	_L,	_L,	_L,	_L,	_L,	_L,	/* 70-77 */
	_L,	_L,	_L,	_P,	_P,	_P,	_P,	_C	/* 78-7f */
									/* 80-ff */
};

int isalpha(int c)
{
	return (_ctype_[c] & (_U|_L));
}

int isupper(int c)
{
	return (_ctype_[c] & _U);
}

int islower(int c)
{
	return (_ctype_[c] & _L);
}

int isdigit(int c)
{
	return (_ctype_[c] & _N);
}

int isxdigit(int c)
{
	return (_ctype_[c] & (_X|_N));
}

int isspace(int c)
{
	return (_ctype_[c] & _S);
}

int ispunct(int c)
{
	return (_ctype_[c] & _P);
}

int isalnum(int c)
{
	return (_ctype_[c] & (_U|_L|_N));
}

int isblank(int c)
{
	return (_ctype_[c] & _B);
}

int isprint(int c)
{
	return (_ctype_[c] & (_P|_U|_L|_N|_B));
}

int isgraph(int c)
{
	return (_ctype_[c] & (_P|_U|_L|_N));
}

int iscntrl(int c)
{
	return (_ctype_[c] & _C);
}

int isascii(int c)
{
	return ((c & ~0x7F) == 0);
}

int toascii(int c)
{
	return (c & 0x7f);
}

int tolower(int c)
{
	return (isupper(c) ? (c + ('a' - 'A')) : c);
}

int toupper(int c)
{
	return (islower(c) ? (c - ('a' - 'A')) : c);
}
