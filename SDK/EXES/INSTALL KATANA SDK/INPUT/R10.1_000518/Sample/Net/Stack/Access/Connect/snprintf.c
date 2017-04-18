/*-
 * Copyright (c) 1990, 1993
 *      The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
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
 *      This product includes software developed by the University of
 *      California, Berkeley and its contributors.
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

/*
 * Local changes Copyright 1996,1997,1998,1999 PlanetWeb, Inc.
 *
 * $Header: h:/RCS/netsamp/snprintf.c 1.1 1999-03-15 14:40:47-0800 soohoo Exp $
 *
 * $Log: snprintf.c $
 * Revision 1.1  1999-03-15 14:40:47-0800  soohoo
 * Initial revision
 *
 *
 * Branched from v1.9
 *
 */

int shc_empty_c_file = 0;

/*
 * Actual printf innards.
 *
 * This code is large and complicated...
 */

/* Only used by PlanetWeb stack. */
#ifdef KGTRN_PLANET_WEB
#include <pwebinc.h>

#if __KATANA__ || __MMATICS__ || __TOSHIBA__
#define		__NO_QUAD_SUPPORT__		1
#else
#define		__NO_QUAD_SUPPORT__		0
#endif

#if __NO_QUAD_SUPPORT__
typedef unsigned long u_longest_t;
typedef long longest_t;
#else
typedef unsigned long long u_longest_t;
typedef long long longest_t;
#endif

#include <limits.h>

#if __NO_QUAD_SUPPORT__
#ifndef LONG_MAX
#define LONG_MAX 0x7FFFFFFFL
#endif
#define LONGEST_MAX LONG_MAX
#else
#ifndef LONG_LONG_MAX
#define LONG_LONG_MAX 9223372036854775807LL
#endif
#define LONGEST_MAX LONG_LONG_MAX
#endif

//#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>

static char *   __ultoa (u_long, char *, int, int, char *);
#if !__NO_QUAD_SUPPORT__
static char *   __uqtoa (u_longest_t, char *, int, int, char *);
#endif

//#define MIN(a,b) (((a)<(b))?(a):(b))

/*
 * Macros for converting digits to letters and vice versa
 */
#define to_digit(c)     ((c) - '0')
#define is_digit(c)     ((unsigned)to_digit(c) <= 9)
#define to_char(n)      ((n) + '0')

/*
 * Convert an unsigned long to ASCII for printf purposes, returning
 * a pointer to the first character of the string representation.
 * Octal numbers can be forced to have a leading zero; hex numbers
 * use the given digits.
 */
static char *
__ultoa(val, endp, base, octzero, xdigs)
        register u_long val;
        char *endp;
        int base, octzero;
        char *xdigs;
{
        register char *cp = endp;
        register long sval;

        /*
         * Handle the three cases separately, in the hope of getting
         * better/faster code.
         */
        switch (base) {
        case 10:
                if (val < 10) { /* many numbers are 1 digit */
                        *--cp = to_char(val);
                        return (cp);
                }
                /*
                 * On many machines, unsigned arithmetic is harder than
                 * signed arithmetic, so we do at most one unsigned mod and
                 * divide; this is sufficient to reduce the range of
                 * the incoming value to where signed arithmetic works.
                 */
                if (val > LONG_MAX) {
                        *--cp = to_char(val % 10);
                        sval = val / 10;
                } else
                        sval = val;
                do {
                        *--cp = to_char(sval % 10);
                        sval /= 10;
                } while (sval != 0);
                break;

        case 8:
                do {
                        *--cp = to_char(val & 7);
                        val >>= 3;
                } while (val);
                if (octzero && *cp != '0')
                        *--cp = '0';
                break;

        case 16:
        default:                        /* oops */
                do {
                        *--cp = xdigs[val & 15];
                        val >>= 4;
                } while (val);
                break;

        }
        return (cp);
}

#if !__NO_QUAD_SUPPORT__
/* Identical to __ultoa, but for quads. */
static char *
__uqtoa(val, endp, base, octzero, xdigs)
        register u_longest_t val;
        char *endp;
        int base, octzero;
        char *xdigs;
{
        register char *cp = endp;
        register longest_t sval;

        /* quick test for small values; __ultoa is typically much faster */
        /* (perhaps instead we should run until small, then call __ultoa?) */
        if (val <= ULONG_MAX)
                return (__ultoa((u_long)val, endp, base, octzero, xdigs));
        switch (base) {
        case 10:
                if (val < 10) {
                        *--cp = to_char(val % 10);
                        return (cp);
                }
                if (val > LONGEST_MAX) {
                        *--cp = to_char(val % 10);
                        sval = val / 10;
                } else
                        sval = val;
                do {
                        *--cp = to_char(sval % 10);
                        sval /= 10;
                } while (sval != 0);
                break;

        case 8:
                do {
                        *--cp = to_char(val & 7);
                        val >>= 3;
                } while (val);
                if (octzero && *cp != '0')
                        *--cp = '0';
                break;

        case 16:
        default:
                do {
                        *--cp = xdigs[val & 15];
                        val >>= 4;
                } while (val);
                break;

        }
        return (cp);
}
#endif

#define BUF             68

/*
 * Flags used during conversion.
 */
#define ALT             0x001           /* alternate form */
#define HEXPREFIX       0x002           /* add 0x or 0X prefix */
#define LADJUST         0x004           /* left adjustment */
#define LONGDBL         0x008           /* long double; unimplemented */
#define LONGINT         0x010           /* long integer */
#define QUADINT         0x020           /* quad integer */
#define SHORTINT        0x040           /* short integer */
#define ZEROPAD         0x080           /* zero (as opposed to blank) pad */
#define FPT             0x100           /* Floating point number */
int
vPWprintf(fp, maxlen, fmt0, ap)
        char *fp; 				/* output buffer */
		size_t maxlen;			/* output buffer size */
        const char *fmt0;
        va_list ap;
{
	struct vars {
        /*register*/ char *xfmt;     /* format string */
        /*register*/ int xch;        /* character from fmt */
//        /*register*/ int n;         /* handy integer (short term usage) */
        /*register*/ char *xcp;      /* handy char pointer (short term usage) */
        /*register*/ int xflags;     /* flags as above */
        int xret;                /* return value accumulator */
        int xwidth;              /* width from format (%8d), or 0 */
        int xprec;               /* precision from format (%.3d), or -1 */
        int xsign;              /* sign prefix (' ', '+', '-', or \0) */
        u_long  xulval /*= 0*/;      /* integer arguments %[diouxX] */
        u_longest_t xuqval /*= 0*/;     /* %q integers */
        int xbase;               /* base for [diouxX] conversion */
        int xdprec;              /* a copy of prec if [diouxX], 0 otherwise */
        int xrealsz;             /* field size expanded by dprec, sign, etc */
        int xsize;               /* size of converted field or string */
        char *xxdigs /*= NULL*/;     /* digits for [xX] conversion */
	} v;
	    struct vars *pV = &v;
#define fmt (pV->xfmt)
#define ch (pV->xch)
#define cp (pV->xcp)
#define flags (pV->xflags)
#define ret (pV->xret)
#define width (pV->xwidth)
#define prec (pV->xprec)
#define sign (pV->xsign)
#define ulval (pV->xulval)
#define uqval (pV->xuqval)
#define base (pV->xbase)
#define dprec (pV->xdprec)
#define realsz (pV->xrealsz)
#define size (pV->xsize)
#define xdigs (pV->xxdigs)
		int n;
        char buf[BUF];          /* space for %c, %[diouxX], %[eEfgG] */
        char ox[2];             /* space for 0x hex-prefix */

        /*
         * Choose PADSIZE to trade efficiency vs. size.  If larger printf
         * fields occur frequently, increase PADSIZE and make the initialisers
         * below longer.
         */
#define PADSIZE 16              /* pad chunk size */
        static const char blanks[PADSIZE] =
         {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
        static const char zeroes[PADSIZE] =
         {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};

        /*
         * BEWARE, these `goto error' on error, and PAD uses `n'.
         */
#define PRINT(ptr, len) { \
		size_t writesize; \
		writesize = MIN((len), maxlen); \
		memcpy(fp, (ptr), writesize); \
		fp += writesize; \
		maxlen -= writesize; \
}
#define PAD(howmany, with) { \
		int n; \
        if ((n = (howmany)) > 0) { \
                while (n > PADSIZE) { \
                        PRINT(with, PADSIZE); \
                        n -= PADSIZE; \
                } \
                PRINT(with, n); \
        } \
}

        /*
         * To extend shorts properly, we need both signed and unsigned
         * argument extraction methods.
         */
#define SARG() \
        (flags&LONGINT ? va_arg(ap, long) : \
            flags&SHORTINT ? (long)(short)va_arg(ap, int) : \
            (long)va_arg(ap, int))
#define UARG() \
        (flags&LONGINT ? va_arg(ap, u_long) : \
            flags&SHORTINT ? (u_long)(u_short)va_arg(ap, int) : \
            (u_long)va_arg(ap, u_int))

		memset(pV, 0, sizeof(v));

        fmt = (char *)fmt0;
        ret = 0;

        /*
         * Scan the format for conversions (`%' character).
         */
        for (;;) {
                for (cp = fmt; (ch = *fmt) != '\0' && ch != '%'; fmt++)
                        /* void */;
                if ((n = fmt - cp) != 0) {
                        PRINT(cp, n);
                        ret += n;
                }
                if (ch == '\0')
                        goto done;
                fmt++;          /* skip over '%' */

                flags = 0;
                dprec = 0;
                width = 0;
                prec = -1;
                sign = '\0';

rflag:          ch = *fmt++;
reswitch:       switch (ch) {
                case ' ':
                        /*
                         * ``If the space and + flags both appear, the space
                         * flag will be ignored.''
                         *      -- ANSI X3J11
                         */
                        if (!sign)
                                sign = ' ';
                        goto rflag;
                case '#':
                        flags |= ALT;
                        goto rflag;
                case '*':
                        /*
                         * ``A negative field width argument is taken as a
                         * - flag followed by a positive field width.''
                         *      -- ANSI X3J11
                         * They don't exclude field widths read from args.
                         */
                        if ((width = va_arg(ap, int)) >= 0)
                                goto rflag;
                        width = -width;
                        /* FALLTHROUGH */
                case '-':
                        flags |= LADJUST;
                        goto rflag;
                case '+':
                        sign = '+';
                        goto rflag;
                case '.':
                        if ((ch = *fmt++) == '*') {
                                n = va_arg(ap, int);
                                prec = n < 0 ? -1 : n;
                                goto rflag;
                        }
                        n = 0;
                        while (is_digit(ch)) {
                                n = 10 * n + to_digit(ch);
                                ch = *fmt++;
                        }
                        prec = n < 0 ? -1 : n;
                        goto reswitch;
                case '0':
                        /*
                         * ``Note that 0 is taken as a flag, not as the
                         * beginning of a field width.''
                         *      -- ANSI X3J11
                         */
                        flags |= ZEROPAD;
                        goto rflag;
                case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9':
                        n = 0;
                        do {
                                n = 10 * n + to_digit(ch);
                                ch = *fmt++;
                        } while (is_digit(ch));
                        width = n;
                        goto reswitch;
                case 'h':
                        flags |= SHORTINT;
                        goto rflag;
                case 'l':
                        flags |= LONGINT;
                        goto rflag;
#if !__NO_QUAD_SUPPORT__
                case 'q':
                        flags |= QUADINT;
                        goto rflag;
#endif
                case 'c':
                        *(cp = buf) = va_arg(ap, int);
                        size = 1;
                        sign = '\0';
                        break;
                case 'D':
                        flags |= LONGINT;
                        /*FALLTHROUGH*/
                case 'd':
                case 'i':
#if !__NO_QUAD_SUPPORT__
                        if (flags & QUADINT) {
                                uqval = va_arg(ap, longest_t);
                                if ((longest_t)uqval < 0) {
                                        uqval = -uqval;
                                        sign = '-';
                                }
                        } else {
#endif
                                ulval = SARG();
                                if ((long)ulval < 0) {
                                        ulval = -ulval;
                                        sign = '-';
                                }
#if !__NO_QUAD_SUPPORT__
                        }
#endif
                        base = 10;
                        goto number;
                case 'n':
#if !__NO_QUAD_SUPPORT__
                        if (flags & QUADINT)
                                *va_arg(ap, longest_t *) = ret;
                        else
#endif
						if (flags & LONGINT)
                                *va_arg(ap, long *) = ret;
                        else if (flags & SHORTINT)
                                *va_arg(ap, short *) = ret;
                        else
                                *va_arg(ap, int *) = ret;
                        continue;       /* no output */
                case 'O':
                        flags |= LONGINT;
                        /*FALLTHROUGH*/
                case 'o':
#if !__NO_QUAD_SUPPORT__
                        if (flags & QUADINT)
                                uqval = va_arg(ap, u_longest_t);
                        else
#endif
                                ulval = UARG();
                        base = 8;
                        goto nosign;
                case 'p':
                        /*
                         * ``The argument shall be a pointer to void.  The
                         * value of the pointer is converted to a sequence
                         * of printable characters, in an implementation-
                         * defined manner.''
                         *      -- ANSI X3J11
                         */
                        ulval = (u_long)va_arg(ap, void *);
                        base = 16;
                        xdigs = "0123456789abcdef";
                        flags = (flags & ~QUADINT) | HEXPREFIX;
                        ch = 'x';
                        goto nosign;
                case 's':
                        if ((cp = va_arg(ap, char *)) == NULL)
                                cp = "(null)";
                        if (prec >= 0) {
                                /*
                                 * can't use strlen; can only look for the
                                 * NUL in the first `prec' characters, and
                                 * strlen() will go further.
                                 */
                                char *p = memchr(cp, 0, (size_t)prec);

                                if (p != NULL) {
                                        size = p - cp;
                                        if (size > prec)
                                                size = prec;
                                } else
                                        size = prec;
                        } else
                                size = strlen(cp);
                        sign = '\0';
                        break;
                case 'U':
                        flags |= LONGINT;
                        /*FALLTHROUGH*/
                case 'u':
#if !__NO_QUAD_SUPPORT__
                        if (flags & QUADINT)
                                uqval = va_arg(ap, u_longest_t);
                        else
#endif
                                ulval = UARG();
                        base = 10;
                        goto nosign;
                case 'X':
                        xdigs = "0123456789ABCDEF";
                        goto hex;
                case 'x':
                        xdigs = "0123456789abcdef";
hex:
#if !__NO_QUAD_SUPPORT__
						if (flags & QUADINT)
                                uqval = va_arg(ap, u_longest_t);
                        else
#endif
                                ulval = UARG();
                        base = 16;
                        /* leading 0x/X only if non-zero */
                        if (flags & ALT &&
                            (flags & QUADINT ? uqval != 0 : ulval != 0))
                                flags |= HEXPREFIX;

                        /* unsigned conversions */
nosign:                 sign = '\0';
                        /*
                         * ``... diouXx conversions ... if a precision is
                         * specified, the 0 flag will be ignored.''
                         *      -- ANSI X3J11
                         */
number:                 if ((dprec = prec) >= 0)
                                flags &= ~ZEROPAD;

                        /*
                         * ``The result of converting a zero value with an
                         * explicit precision of zero is no characters.''
                         *      -- ANSI X3J11
                         */
                        cp = buf + BUF;
#if !__NO_QUAD_SUPPORT__
                        if (flags & QUADINT) {
                                if (uqval != 0 || prec != 0)
                                        cp = __uqtoa(uqval, cp, base,
                                            flags & ALT, xdigs);
                        } else {
#endif
                                if (ulval != 0 || prec != 0)
                                        cp = __ultoa(ulval, cp, base,
                                            flags & ALT, xdigs);
#if !__NO_QUAD_SUPPORT__
                        }
#endif
                        size = buf + BUF - cp;
                        break;
                default:        /* "%?" prints ?, unless ? is NUL */
                        if (ch == '\0')
                                goto done;
                        /* pretend it was %c with argument ch */
                        cp = buf;
                        *cp = ch;
                        size = 1;
                        sign = '\0';
                        break;
                }

                /*
                 * All reasonable formats wind up here.  At this point, `cp'
                 * points to a string which (if not flags&LADJUST) should be
                 * padded out to `width' places.  If flags&ZEROPAD, it should
                 * first be prefixed by any sign or other prefix; otherwise,
                 * it should be blank padded before the prefix is emitted.
                 * After any left-hand padding and prefixing, emit zeroes
                 * required by a decimal [diouxX] precision, then print the
                 * string proper, then emit zeroes required by any leftover
                 * floating precision; finally, if LADJUST, pad with blanks.
                 *
                 * Compute actual size, so we know how much to pad.
                 * size excludes decimal prec; realsz includes it.
                 */
                realsz = dprec > size ? dprec : size;
                if (sign)
                        realsz++;
                else if (flags & HEXPREFIX)
                        realsz += 2;

                /* right-adjusting blank padding */
                if ((flags & (LADJUST|ZEROPAD)) == 0)
                        PAD(width - realsz, blanks);

                /* prefix */
                if (sign) {
						ox[0] = sign;
                        PRINT(ox, 1);
                } else if (flags & HEXPREFIX) {
                        ox[0] = '0';
                        ox[1] = ch;
                        PRINT(ox, 2);
                }

                /* right-adjusting zero padding */
                if ((flags & (LADJUST|ZEROPAD)) == ZEROPAD)
                        PAD(width - realsz, zeroes);

                /* leading zeroes from decimal precision */
                PAD(dprec - size, zeroes);

                /* the string or number proper */
                PRINT(cp, size);
                /* left-adjusting padding (always blank) */
                if (flags & LADJUST)
                        PAD(width - realsz, blanks);

                /* finally, adjust ret */
                ret += width > realsz ? width : realsz;
        }
done:
        return (v.xret);				/* Can't be pv->, because of  */
										/* an aliasing optimization   */
										/* error.  (Stack space was   */
										/* released before the return */
										/* code was read.)            */
}

#if !__VSURF__ && !__MMATICS__ && !__TOSHIBA__
int sprintf(char *buffer, const char *format, ...)
{
	va_list args;
	int retval;

	va_start(args, format);

	retval = vPWprintf(buffer, ULONG_MAX, format, args);

	va_end(args);
	buffer[retval] = '\0';

	return retval;
}
#endif

int snprintf(char *buffer, size_t max, const char *format, ...)
{
	va_list args;
	int retval;
	int idx;

	va_start(args, format);

	retval = vPWprintf(buffer, max - 1, format, args);

	va_end(args);

	if (retval < max) idx = retval; else idx = max - 1;
	buffer[idx] = '\0';

	return retval;
}

#if __SATURN__ || (!__MMATICS__ && !__TOSHIBA__)
/* Turn off printf, since it doesn't do anything on the saturn
 * anyway...
 * MediaMatics has its own printf.
 */
int printf(const char *format, ...)
{
	return 0;
}
#endif

#endif /* KGTRN_PLANET_WEB */