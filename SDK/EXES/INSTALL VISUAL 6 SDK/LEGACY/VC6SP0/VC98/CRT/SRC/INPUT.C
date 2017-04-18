/***
*input.c - C formatted input, used by scanf, etc.
*
*       Copyright (c) 1987-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _input() to do formatted input; called from scanf(),
*       etc. functions.  This module defines _cscanf() instead when
*       CPRFLAG is defined.  The file cscanf.c defines that symbol
*       and then includes this file in order to implement _cscanf().
*
*******************************************************************************/

#ifdef _WIN32


#define ALLOW_RANGE /* allow "%[a-z]"-style scansets */


/* temporary work-around for compiler without 64-bit support */

#ifndef _INTEGRAL_MAX_BITS
#define _INTEGRAL_MAX_BITS  64
#endif  /* _INTEGRAL_MAX_BITS */


#include <cruntime.h>
#include <stdio.h>
#include <ctype.h>
#include <cvt.h>
#include <conio.h>
#include <stdarg.h>
#include <string.h>
#include <internal.h>
#include <fltintrn.h>
#include <mtdll.h>
#include <stdlib.h>
#include <nlsint.h>
#include <dbgint.h>

#ifdef _MBCS
#undef _MBCS
#endif  /* _MBCS */
#include <tchar.h>

#define HEXTODEC(chr)   _hextodec(chr)
#define LEFT_BRACKET    ('[' | ('a' - 'A')) /* 'lowercase' version */

#ifdef _UNICODE
static wchar_t __cdecl _hextodec(wchar_t);
#else  /* _UNICODE */
static int __cdecl _hextodec(int);
#endif  /* _UNICODE */

/*
 * Note: CPRFLAG and _UNICODE cases are currently mutually exclusive.
 */

#ifdef CPRFLAG

#define INC()           (++charcount, _inc())
#define UN_INC(chr)     (--charcount, _ungetch_lk(chr))
#define EAT_WHITE()     _whiteout(&charcount)

static int __cdecl _inc(void);
static int __cdecl _whiteout(int *);

#else  /* CPRFLAG */

#define INC()           (++charcount, _inc(stream))
#define UN_INC(chr)     (--charcount, _un_inc(chr, stream))
#define EAT_WHITE()     _whiteout(&charcount, stream)

#ifndef _UNICODE
static int __cdecl _inc(FILE *);
static void __cdecl _un_inc(int, FILE *);
static int __cdecl _whiteout(int *, FILE *);
#else  /* _UNICODE */
static wchar_t __cdecl _inc(FILE *);
static void __cdecl _un_inc(wchar_t, FILE *);
static wchar_t __cdecl _whiteout(int *, FILE *);
#endif  /* _UNICODE */

#endif  /* CPRFLAG */


#ifndef _UNICODE
#define _ISDIGIT(chr)   isdigit(chr)
#define _ISXDIGIT(chr)  isxdigit(chr)
#else  /* _UNICODE */
#define _ISDIGIT(chr)   ( !(chr & 0xff00) && isdigit( chr & 0x00ff ) )
#define _ISXDIGIT(chr)  ( !(chr & 0xff00) && isxdigit( chr & 0x00ff ) )
#endif  /* _UNICODE */


#ifdef _UNICODE
int __cdecl _winput(FILE *, const wchar_t *, va_list);
#endif  /* _UNICODE */

#ifdef CPRFLAG
static int __cdecl input(const unsigned char *, va_list);


/***
*int _cscanf(format, arglist) - read formatted input direct from console
*
*Purpose:
*   Reads formatted data like scanf, but uses console I/O functions.
*
*Entry:
*   char *format - format string to determine data formats
*   arglist - list of POINTERS to where to put data
*
*Exit:
*   returns number of successfully matched data items (from input)
*
*Exceptions:
*
*******************************************************************************/


int __cdecl _cscanf (
    const char *format,
    ...
    )
{
    va_list arglist;

    va_start(arglist, format);

    _ASSERTE(format != NULL);

    return input(format,arglist);   /* get the input */
}

#endif  /* CPRFLAG */


#define ASCII       32           /* # of bytes needed to hold 256 bits */

#define SCAN_SHORT     0         /* also for FLOAT */
#define SCAN_LONG      1         /* also for DOUBLE */
#define SCAN_L_DOUBLE  2         /* only for LONG DOUBLE */

#define SCAN_NEAR    0
#define SCAN_FAR     1


static _TCHAR sbrackset[] = _T(" \t-\r]"); /* use range-style list */


static _TCHAR cbrackset[] = _T("]");



/***
*int _input(stream, format, arglist), static int input(format, arglist)
*
*Purpose:
*   get input items (data items or literal matches) from the input stream
*   and assign them if appropriate to the items thru the arglist. this
*   function is intended for internal library use only, not for the user
*
*   The _input entry point is for the normal scanf() functions
*   The input entry point is used when compiling for _cscanf() [CPRFLAF
*   defined] and is a static function called only by _cscanf() -- reads from
*   console.
*
*Entry:
*   FILE *stream - file to read from
*   char *format - format string to determine the data to read
*   arglist - list of pointer to data items
*
*Exit:
*   returns number of items assigned and fills in data items
*   returns EOF if error or EOF found on stream before 1st data item matched
*
*Exceptions:
*
*******************************************************************************/

#ifdef CPRFLAG

static int __cdecl input (
    const unsigned char *format,
    va_list arglist
    )
#elif defined (_UNICODE)

int __cdecl _winput (
    FILE *stream,
    const wchar_t *format,
    va_list arglist
    )
#else  /* defined (_UNICODE) */

int __cdecl _input (
    FILE *stream,
    const unsigned char *format,
    va_list arglist
    )
#endif  /* defined (_UNICODE) */

{
#ifndef _UNICODE
    char table[ASCII];                  /* which chars allowed for %[], %s   */
    char floatstring[CVTBUFSIZE + 1];   /* ASCII buffer for floats           */
#else  /* _UNICODE */
    char table[256*ASCII];
    wchar_t floatstring[CVTBUFSIZE + 1];
#endif  /* _UNICODE */

    unsigned long number;               /* temp hold-value                   */
#if _INTEGRAL_MAX_BITS >= 64   
    unsigned __int64 num64;             /* temp for 64-bit integers          */
#endif  /* _INTEGRAL_MAX_BITS >= 64    */
    void *pointer;                      /* points to user data receptacle    */
    void *start;                        /* indicate non-empty string         */


#ifdef _UNICODE
    wchar_t *scanptr;           /* for building "table" data         */
REG2 wchar_t ch;
#else  /* _UNICODE */
    wchar_t wctemp;
    unsigned char *scanptr;             /* for building "table" data         */
REG2 int ch;
#endif  /* _UNICODE */
    int charcount;                      /* total number of chars read        */
REG1 int comchr;                        /* holds designator type             */
    int count;                          /* return value.  # of assignments   */

    int started;                        /* indicate good number              */
    int width;                          /* width of field                    */
    int widthset;                       /* user has specified width          */

/* Neither coerceshort nor farone are need for the 386 */


    char done_flag;                     /* general purpose loop monitor      */
    char longone;                       /* 0 = SHORT, 1 = LONG, 2 = L_DOUBLE */
#if _INTEGRAL_MAX_BITS >= 64   
    int integer64;                      /* 1 for 64-bit integer, 0 otherwise */
#endif  /* _INTEGRAL_MAX_BITS >= 64    */
    signed char widechar;               /* -1 = char, 0 = ????, 1 = wchar_t  */
    char reject;                        /* %[^ABC] instead of %[ABC]         */
    char negative;                      /* flag for '-' detected             */
    char suppress;                      /* don't assign anything             */
    char match;                         /* flag: !0 if any fields matched    */
    va_list arglistsave;                /* save arglist value                */

    char fl_wchar_arg;                  /* flags wide char/string argument   */
#ifdef _UNICODE
    wchar_t rngch;              /* used while scanning range         */
    wchar_t last;               /* also for %[a-z]                   */
    wchar_t prevchar;           /* for %[a-z]                        */
    wchar_t wdecimal;                   /* wide version of decimal point     */
    wchar_t *wptr;                      /* pointer traverses wide floatstring*/
#else  /* _UNICODE */
    unsigned char rngch;                /* used while scanning range         */
    unsigned char last;                 /* also for %[a-z]                   */
    unsigned char prevchar;             /* for %[a-z]                        */
#endif  /* _UNICODE */

    _ASSERTE(format != NULL);

#ifndef CPRFLAG
    _ASSERTE(stream != NULL);
#endif  /* CPRFLAG */

    /*
    count = # fields assigned
    charcount = # chars read
    match = flag indicating if any fields were matched

    [Note that we need both count and match.  For example, a field
    may match a format but have assignments suppressed.  In this case,
    match will get set, but 'count' will still equal 0.  We need to
    distinguish 'match vs no-match' when terminating due to EOF.]
    */

    count = charcount = match = 0;

    while (*format) {

        if (_istspace((_TUCHAR)*format)) {

            UN_INC(EAT_WHITE()); /* put first non-space char back */

            while ((_istspace)(*++format)); /* NULL */
            /* careful: isspace macro may evaluate argument more than once! */

        }

        if (_T('%') == *format) {

            number = 0;
            prevchar = 0;
            width = widthset = started = 0;
            fl_wchar_arg = done_flag = suppress = negative = reject = 0;
            widechar = 0;

            longone = 1;

            integer64 = 0;

            while (!done_flag) {

                comchr = *++format;
                if (_ISDIGIT((_TUCHAR)comchr)) {
                    ++widthset;
                    width = MUL10(width) + (comchr - _T('0'));
                } else
                    switch (comchr) {
                        case _T('F') :
                        case _T('N') :   /* no way to push NEAR in large model */
                            break;  /* NEAR is default in small model */
                        case _T('h') :
                            /* set longone to 0 */
                            --longone;
                            --widechar;         /* set widechar = -1 */
                            break;

#if _INTEGRAL_MAX_BITS >= 64   
                        case _T('I'):
                            if ( (*(format + 1) == _T('6')) &&
                                 (*(format + 2) == _T('4')) )
                            {
                                format += 2;
                                ++integer64;
                                num64 = 0;
                                break;
                            }
                            goto DEFAULT_LABEL;
#endif  /* _INTEGRAL_MAX_BITS >= 64    */

                        case _T('L') :
                        /*  ++longone;  */
                            ++longone;
                            break;

                        case _T('l') :
                            ++longone;
                                    /* NOBREAK */
                        case _T('w') :
                            ++widechar;         /* set widechar = 1 */
                            break;

                        case _T('*') :
                            ++suppress;
                            break;

                        default:
DEFAULT_LABEL:
                            ++done_flag;
                            break;
                    }
            }

            if (!suppress) {
                arglistsave = arglist;
                pointer = va_arg(arglist,void *);
            }

            done_flag = 0;

            if (!widechar) {    /* use case if not explicitly specified */
                if ((*format == _T('S')) || (*format == _T('C')))
#ifdef _UNICODE
                    --widechar;
                else
                    ++widechar;
#else  /* _UNICODE */
                    ++widechar;
                else
                    --widechar;
#endif  /* _UNICODE */
            }

            /* switch to lowercase to allow %E,%G, and to
               keep the switch table small */

            comchr = *format | (_T('a') - _T('A'));

            if (_T('n') != comchr)
                if (_T('c') != comchr && LEFT_BRACKET != comchr)
                    ch = EAT_WHITE();
                else
                    ch = INC();


            if (!widthset || width) {

                switch(comchr) {

                    case _T('c'):
                /*  case _T('C'):  */
                        if (!widthset) {
                            ++widthset;
                            ++width;
                        }
                        if (widechar>0)
                            fl_wchar_arg++;
                        scanptr = cbrackset;
                        --reject; /* set reject to 255 */
                        goto scanit2;

                    case _T('s'):
                /*  case _T('S'):  */
                        if (widechar>0)
                            fl_wchar_arg++;
                        scanptr = sbrackset;
                        --reject; /* set reject to 255 */
                        goto scanit2;

                    case LEFT_BRACKET :   /* scanset */
                        if (widechar>0)
                            fl_wchar_arg++;
                        scanptr = (_TCHAR *)(++format);

                        if (_T('^') == *scanptr) {
                            ++scanptr;
                            --reject; /* set reject to 255 */
                        }


scanit2:
#ifdef _UNICODE
                        memset(table, 0, ASCII*256);
#else  /* _UNICODE */
                        memset(table, 0, ASCII);
#endif  /* _UNICODE */


                        if (LEFT_BRACKET == comchr)
                            if (_T(']') == *scanptr) {
                                prevchar = _T(']');
                                ++scanptr;

                                table[ _T(']') >> 3] = 1 << (_T(']') & 7);

                            }

                        while (_T(']') != *scanptr) {

                            rngch = *scanptr++;

                            if (_T('-') != rngch ||
                                 !prevchar ||           /* first char */
                                 _T(']') == *scanptr) /* last char */

                                table[(prevchar = rngch) >> 3] |= 1 << (rngch & 7);

                            else {  /* handle a-z type set */

                                rngch = *scanptr++; /* get end of range */

                                if (prevchar < rngch)  /* %[a-z] */
                                    last = rngch;
                                else {              /* %[z-a] */
                                    last = prevchar;
                                    prevchar = rngch;
                                }
                                for (rngch = prevchar; rngch <= last; ++rngch)
                                    table[rngch >> 3] |= 1 << (rngch & 7);

                                prevchar = 0;

                            }
                        }


                        if (!*scanptr)
                            goto error_return;      /* trunc'd format string */

                        /* scanset completed.  Now read string */

                        if (LEFT_BRACKET == comchr)
                            format = scanptr;

                        start = pointer;

                        /*
                         * execute the format directive. that is, scan input
                         * characters until the directive is fulfilled, eof
                         * is reached, or a non-matching character is
                         * encountered.
                         *
                         * it is important not to get the next character
                         * unless that character needs to be tested! other-
                         * wise, reads from line-buffered devices (e.g.,
                         * scanf()) would require an extra, spurious, newline
                         * if the first newline completes the current format
                         * directive.
                         */
                        UN_INC(ch);

                        while ( !widthset || width-- ) {

                            ch = INC();
                            if (
#ifndef _UNICODE
#ifndef CPRFLAG
                              (EOF != ch) &&
#endif  /* CPRFLAG */
                              ((table[ch >> 3] ^ reject) & (1 << (ch & 7)))
#else  /* _UNICODE */
                              (WEOF != ch) &&
                         /*     ((ch>>3 >= ASCII) ? reject : */
                              ((table[ch >> 3] ^ reject) &
                                        (1 << (ch & 7)))         /* ) */
#endif  /* _UNICODE */
                            ) {
                                if (!suppress) {
#ifndef _UNICODE
                                    if (fl_wchar_arg) {
                                        char temp[2];
                                        temp[0] = (char) ch;
                                        if (isleadbyte(ch))
                                            temp[1] = (char) INC();
                                        mbtowc(&wctemp, temp, MB_CUR_MAX);
                                        *(wchar_t UNALIGNED *)pointer =
                                          wctemp;
                                        /* do nothing if mbtowc fails */
                                        pointer = (wchar_t *)pointer + 1;
                                    } else
#else  /* _UNICODE */
                                    if (fl_wchar_arg) {
                                        *(wchar_t UNALIGNED *)pointer = ch;
                                        pointer = (wchar_t *)pointer + 1;
                                    } else
#endif  /* _UNICODE */
                                    {
#ifndef _UNICODE
                                    *(char *)pointer = (char)ch;
                                    pointer = (char *)pointer + 1;
#else  /* _UNICODE */
                                    int temp;
                                    /* convert wide to multibyte */
                                    temp = wctomb((char *)pointer, ch);
                                    /* do nothing if wctomb fails */
                                    pointer = (char *)pointer + temp;
#endif  /* _UNICODE */
                                    }
                                } /* suppress */
                                else {
                                    /* just indicate a match */
                                    start = (_TCHAR *)start + 1;
                                }
                            }
                            else  {
                                UN_INC(ch);
                                break;
                            }
                        }

                        /* make sure something has been matched and, if
                           assignment is not suppressed, null-terminate
                           output string if comchr != c */

                        if (start != pointer) {
                            if (!suppress) {
                                ++count;
                                if ('c' != comchr) /* null-terminate strings */
                                    if (fl_wchar_arg)
                                        *(wchar_t UNALIGNED *)pointer = L'\0';
                                    else
                                    *(char *)pointer = '\0';
                            } else /*NULL*/;
                        }
                        else
                            goto error_return;

                        break;

                    case _T('i') :      /* could be d, o, or x */

                        comchr = _T('d'); /* use as default */

                    case _T('x'):

                        if (_T('-') == ch) {
                            ++negative;

                            goto x_incwidth;

                        } else if (_T('+') == ch) {
x_incwidth:
                            if (!--width && widthset)
                                ++done_flag;
                            else
                                ch = INC();
                        }

                        if (_T('0') == ch) {

                            if (_T('x') == (_TCHAR)(ch = INC()) || _T('X') == (_TCHAR)ch) {
                                ch = INC();
                                comchr = _T('x');
                            } else {
                                ++started;
                                if (_T('x') != comchr)
                                    comchr = _T('o');
                                else {
                                    /* scanning a hex number that starts */
                                    /* with a 0. push back the character */
                                    /* currently in ch and restore the 0 */
                                    UN_INC(ch);
                                    ch = _T('0');
                                }
                            }
                        }
                        goto getnum;

                        /* NOTREACHED */

                    case _T('p') :
                        /* force %hp to be treated as %p */
                        longone = 1;

                    case _T('o') :
                    case _T('u') :
                    case _T('d') :

                        if (_T('-') == ch) {
                            ++negative;

                            goto d_incwidth;

                        } else if (_T('+') == ch) {
d_incwidth:
                            if (!--width && widthset)
                                ++done_flag;
                            else
                                ch = INC();
                        }

getnum:
#if _INTEGRAL_MAX_BITS >= 64   
                        if ( integer64 ) {

                            while (!done_flag) {

                                if (_T('x') == comchr)

                                    if (_ISXDIGIT(ch)) {
                                        num64 <<= 4;
                                        ch = HEXTODEC(ch);
                                    }
                                    else
                                        ++done_flag;

                                else if (_ISDIGIT(ch))

                                    if (_T('o') == comchr)
                                        if (_T('8') > ch)
                                                num64 <<= 3;
                                        else {
                                                ++done_flag;
                                        }
                                    else /* _T('d') == comchr */
                                        num64 = MUL10(num64);

                                else
                                    ++done_flag;

                                if (!done_flag) {
                                    ++started;
                                    num64 += ch - _T('0');

                                    if (widthset && !--width)
                                        ++done_flag;
                                    else
                                        ch = INC();
                                } else
                                    UN_INC(ch);

                            } /* end of WHILE loop */

                            if (negative)
                                num64 = (unsigned __int64 )(-(__int64)num64);
                        }
                        else {
#endif  /* _INTEGRAL_MAX_BITS >= 64    */
                            while (!done_flag) {

                                if (_T('x') == comchr || _T('p') == comchr)

                                    if (_ISXDIGIT(ch)) {
                                        number = (number << 4);
                                        ch = HEXTODEC(ch);
                                    }
                                    else
                                        ++done_flag;

                                else if (_ISDIGIT(ch))

                                    if (_T('o') == comchr)
                                        if (_T('8') > ch)
                                            number = (number << 3);
                                        else {
                                            ++done_flag;
                                        }
                                    else /* _T('d') == comchr */
                                        number = MUL10(number);

                                else
                                    ++done_flag;

                                if (!done_flag) {
                                    ++started;
                                    number += ch - _T('0');

                                    if (widthset && !--width)
                                        ++done_flag;
                                    else
                                        ch = INC();
                                } else
                                    UN_INC(ch);

                            } /* end of WHILE loop */

                            if (negative)
                                number = (unsigned long)(-(long)number);
#if _INTEGRAL_MAX_BITS >= 64   
                        }
#endif  /* _INTEGRAL_MAX_BITS >= 64    */
                        if (_T('F')==comchr) /* expected ':' in long pointer */
                            started = 0;

                        if (started)
                            if (!suppress) {

                                ++count;
assign_num:
#if _INTEGRAL_MAX_BITS >= 64   
                                if ( integer64 )
                                    *(__int64 UNALIGNED *)pointer = (unsigned __int64)num64;
                                else
#endif  /* _INTEGRAL_MAX_BITS >= 64    */
                                if (longone)
                                    *(long UNALIGNED *)pointer = (unsigned long)number;
                                else
                                    *(short UNALIGNED *)pointer = (unsigned short)number;

                            } else /*NULL*/;
                        else
                            goto error_return;

                        break;

                    case _T('n') :      /* char count, don't inc return value */
                        number = charcount;
                        if(!suppress)
                            goto assign_num; /* found in number code above */
                        break;


                    case _T('e') :
                 /* case _T('E') : */
                    case _T('f') :
                    case _T('g') : /* scan a float */
                 /* case _T('G') : */

#ifndef _UNICODE
                        scanptr = floatstring;

                        if (_T('-') == ch) {
                            *scanptr++ = _T('-');
                            goto f_incwidth;

                        } else if (_T('+') == ch) {
f_incwidth:
                            --width;
                            ch = INC();
                        }

                        if (!widthset || width > CVTBUFSIZE)              /* must watch width */
                            width = CVTBUFSIZE;


                        /* now get integral part */

                        while (_ISDIGIT(ch) && width--) {
                            ++started;
                            *scanptr++ = (char)ch;
                            ch = INC();
                        }

                        /* now check for decimal */

                        if (*___decimal_point == (char)ch && width--) {
                            ch = INC();
                            *scanptr++ = *___decimal_point;

                            while (_ISDIGIT(ch) && width--) {
                                ++started;
                                *scanptr++ = (char)ch;
                                ch = INC();
                            }
                        }

                        /* now check for exponent */

                        if (started && (_T('e') == ch || _T('E') == ch) && width--) {
                            *scanptr++ = 'e';

                            if (_T('-') == (ch = INC())) {

                                *scanptr++ = '-';
                                goto f_incwidth2;

                            } else if (_T('+') == ch) {
f_incwidth2:
                                if (!width--)
                                    ++width;
                                else
                                    ch = INC();
                            }


                            while (_ISDIGIT(ch) && width--) {
                                ++started;
                                *scanptr++ = (char)ch;
                                ch = INC();
                            }

                        }

                        UN_INC(ch);

                        if (started)
                            if (!suppress) {
                                ++count;
                                *scanptr = '\0';
                                _fassign( longone-1, pointer , floatstring);
                            } else /*NULL */;
                        else
                            goto error_return;

#else  /* _UNICODE */
                        wptr = floatstring;

                        if (L'-' == ch) {
                            *wptr++ = L'-';
                            goto f_incwidthw;

                        } else if (L'+' == ch) {
f_incwidthw:
                            --width;
                            ch = INC();
                        }

                        if (!widthset || width > CVTBUFSIZE)
                            width = CVTBUFSIZE;


                        /* now get integral part */

                        while (_ISDIGIT(ch) && width--) {
                            ++started;
                            *wptr++ = ch;
                            ch = INC();
                        }

                        /* now check for decimal */

                        /* convert decimal point to wide-char */
                        /* assume result is single wide-char */
                        mbtowc (&wdecimal, ___decimal_point, MB_CUR_MAX);

                        if (wdecimal == ch && width--) {
                            ch = INC();
                            *wptr++ = wdecimal;

                            while (_ISDIGIT(ch) && width--) {
                                ++started;
                                *wptr++ = ch;
                                ch = INC();
                            }
                        }

                        /* now check for exponent */

                        if (started && (L'e' == ch || L'E' == ch) && width--) {
                            *wptr++ = L'e';

                            if (L'-' == (ch = INC())) {

                                *wptr++ = L'-';
                                goto f_incwidth2w;

                            } else if (L'+' == ch) {
f_incwidth2w:
                                if (!width--)
                                    ++width;
                                else
                                    ch = INC();
                            }


                            while (_ISDIGIT(ch) && width--) {
                                ++started;
                                *wptr++ = ch;
                                ch = INC();
                            }

                        }

                        UN_INC(ch);

                        if (started)
                            if (!suppress) {
                                ++count;
                                *wptr = '\0';
                                {
                                /* convert floatstring to char string */
                                /* and do the conversion */
                                size_t cfslength;
                                char *cfloatstring;
                                cfslength =(wptr-floatstring+1)*sizeof(wchar_t);
                                cfloatstring = (char *)_malloc_crt (cfslength);
                                wcstombs (cfloatstring, floatstring, cfslength);
                                _fassign( longone-1, pointer , cfloatstring);
                                _free_crt (cfloatstring);
                                }
                            } else /*NULL */;
                        else
                            goto error_return;

#endif  /* _UNICODE */
                        break;


                    default:    /* either found '%' or something else */

                        if ((int)*format != (int)ch) {
                            UN_INC(ch);
                            goto error_return;
                            }
                        else
                            match--; /* % found, compensate for inc below */

                        if (!suppress)
                            arglist = arglistsave;

                } /* SWITCH */

                match++;        /* matched a format field - set flag */

            } /* WHILE (width) */

            else {  /* zero-width field in format string */
                UN_INC(ch);  /* check for input error */
                goto error_return;
            }

            ++format;  /* skip to next char */

        } else  /*  ('%' != *format) */
            {

            if ((int)*format++ != (int)(ch = INC()))
                {
                UN_INC(ch);
                goto error_return;
                }
#ifndef _UNICODE
            if (isleadbyte(ch))
                {
                int ch2;
                if ((int)*format++ != (ch2=INC()))
                    {
                    UN_INC(ch2);
                    UN_INC(ch);
                    goto error_return;
                    }

                    --charcount; /* only count as one character read */
                }
#endif  /* _UNICODE */
            }

#ifndef CPRFLAG
        if ( (EOF == ch) && ((*format != '%') || (*(format + 1) != 'n')) )
            break;
#endif  /* CPRFLAG */

    }  /* WHILE (*format) */

error_return:

#ifndef CPRFLAG
    if (EOF == ch)
        /* If any fields were matched or assigned, return count */
        return ( (count || match) ? count : EOF);
    else
#endif  /* CPRFLAG */
        return count;

}

/* _hextodec() returns a value of 0-15 and expects a char 0-9, a-f, A-F */
/* _inc() is the one place where we put the actual getc code. */
/* _whiteout() returns the first non-blank character, as defined by isspace() */

#ifndef _UNICODE
static int __cdecl _hextodec (
    int chr
    )
{
    return _ISDIGIT(chr) ? chr : (chr & ~(_T('a') - _T('A'))) - _T('A') + 10 + _T('0');
}
#else  /* _UNICODE */
static _TCHAR __cdecl _hextodec (
    _TCHAR chr
    )
{
    if (_ISDIGIT(chr))
        return chr;
    if (_istlower(chr))
        return (_TCHAR)(chr - _T('a') + 10 + _T('0'));
    else
        return (_TCHAR)(chr - _T('A') + 10 + _T('0'));
}
#endif  /* _UNICODE */


#ifdef CPRFLAG

static int __cdecl _inc (
    void
    )
{
    return(_getche_lk());
}

static int __cdecl _whiteout (
    REG1 int *counter
    )
{
    REG2 int ch;

    while((_istspace)(ch = (++*counter, _inc())));
    return ch;
}

#elif defined (_UNICODE)

/*
 * Manipulate wide-chars in a file.
 * A wide-char is hard-coded to be two chars for efficiency.
 */

static wchar_t __cdecl _inc (
    REG1 FILE *fileptr
    )
{
    return(_getwc_lk(fileptr));
}

static void __cdecl _un_inc (
    wchar_t chr,
    FILE *fileptr
    )
{
    if (WEOF != chr)
        _ungetwc_lk(chr, fileptr);
}

static wchar_t __cdecl _whiteout (
    REG1 int *counter,
    REG3 FILE *fileptr
    )
{
    REG2 wchar_t ch;

    while((iswspace)(ch = (++*counter, _inc(fileptr))));
    return ch;
}

#else  /* defined (_UNICODE) */

static int __cdecl _inc (
    REG1 FILE *fileptr
    )
{
    return(_getc_lk(fileptr));
}

static void __cdecl _un_inc (
    int chr,
    FILE *fileptr
    )
{
    if (EOF != chr)
        _ungetc_lk(chr, fileptr);
}

static int __cdecl _whiteout (
    REG1 int *counter,
    REG3 FILE *fileptr
    )
{
    REG2 int ch;

    while((_istspace)(ch = (++*counter, _inc(fileptr))));
    return ch;
}

#endif  /* defined (_UNICODE) */


#else  /* _WIN32 */

#if defined (_M_MPPC) || defined (_M_M68K)


#define ALLOW_RANGE /* allow "%[a-z]"-style scansets */

/* temporary work-around for compiler without 64-bit support */

#ifndef _INTEGRAL_MAX_BITS
#define _INTEGRAL_MAX_BITS  64
#endif  /* _INTEGRAL_MAX_BITS */

#include <cruntime.h>
#include <stdio.h>
#include <dbgint.h>
#include <ctype.h>
#include <cvt.h>
#include <conio.h>
#include <stdarg.h>
#include <string.h>
#include <internal.h>
#include <fltintrn.h>
#include <mtdll.h>
#include <stdlib.h>
#include <nlsint.h>
#include <tchar.h>

#define HEXTODEC(chr)   _hextodec(chr)
#define LEFT_BRACKET    ('[' | ('a' - 'A')) /* 'lowercase' version */

#ifdef _UNICODE
static wchar_t __cdecl _hextodec(wchar_t);
#else  /* _UNICODE */
static int __cdecl _hextodec(int);
#endif  /* _UNICODE */

/*
 * Note: CPRFLAG and _UNICODE cases are currently mutually exclusive.
 */

#ifdef CPRFLAG

#define INC()           (++charcount, _inc())
#define UN_INC(chr)     (--charcount, _ungetch_lk(chr))
#define EAT_WHITE()     _whiteout(&charcount)

static int __cdecl _inc(void);
static int __cdecl _whiteout(int *);

#else  /* CPRFLAG */

#define INC()           (++charcount, _inc(stream))
#define UN_INC(chr)     (--charcount, _un_inc(chr, stream))
#define EAT_WHITE()     _whiteout(&charcount, stream)

#ifndef _UNICODE
static int __cdecl _inc(FILE *);
static void __cdecl _un_inc(int, FILE *);
static int __cdecl _whiteout(int *, FILE *);
#else  /* _UNICODE */
static wchar_t __cdecl _inc(FILE *);
static void __cdecl _un_inc(wchar_t, FILE *);
static wchar_t __cdecl _whiteout(int *, FILE *);
#endif  /* _UNICODE */

#endif  /* CPRFLAG */


#ifdef _UNICODE
static int __cdecl _winput(FILE *, const unsigned char *, va_list);
#endif  /* _UNICODE */

#ifdef CPRFLAG
static int __cdecl input(const unsigned char *, va_list);


/***
*int _cscanf(format, arglist) - read formatted input direct from console
*
*Purpose:
*   Reads formatted data like scanf, but uses console I/O functions.
*
*Entry:
*   char *format - format string to determine data formats
*   arglist - list of POINTERS to where to put data
*
*Exit:
*   returns number of successfully matched data items (from input)
*
*Exceptions:
*
*******************************************************************************/


int __cdecl _cscanf (
    const char *format,
    ...
    )
{
    va_list arglist;

    va_start(arglist, format);

    _ASSERTE(format != NULL);

    return input(format,arglist);   /* get the input */
}

#endif  /* CPRFLAG */


#define ASCII       32           /* # of bytes needed to hold 256 bits */

#define SCAN_SHORT     0         /* also for FLOAT */
#define SCAN_LONG      1         /* also for DOUBLE */
#define SCAN_L_DOUBLE  2         /* only for LONG DOUBLE */

#define SCAN_NEAR    0
#define SCAN_FAR     1


static char sbrackset[] = " \t-\n]"; /* use range-style list, cl68 swaps \n to \r*/


static char cbrackset[] = "]";



/***
*int _input(stream, format, arglist), static int input(format, arglist)
*
*Purpose:
*   get input items (data items or literal matches) from the input stream
*   and assign them if appropriate to the items thru the arglist. this
*   function is intended for internal library use only, not for the user
*
*   The _input entry point is for the normal scanf() functions
*   The input entry point is used when compiling for _cscanf() [CPRFLAF
*   defined] and is a static function called only by _cscanf() -- reads from
*   console.
*
*Entry:
*   FILE *stream - file to read from
*   char *format - format string to determine the data to read
*   arglist - list of pointer to data items
*
*Exit:
*   returns number of items assigned and fills in data items
*   returns EOF if error or EOF found on stream before 1st data item matched
*
*Exceptions:
*
*******************************************************************************/

#ifdef CPRFLAG

static int __cdecl input (
    const unsigned char *format,
    va_list arglist
    )
#elif defined (_UNICODE)

static int __cdecl _winput (
    FILE *stream,
    const unsigned char *format,
    va_list arglist
    )
#else  /* defined (_UNICODE) */

int __cdecl _input (
    FILE *stream,
    const unsigned char *format,
    va_list arglist
    )
#endif  /* defined (_UNICODE) */

{
    char table[ASCII];                  /* which chars allowed for %[], %s   */
#ifndef _UNICODE
    char floatstring[CVTBUFSIZE + 1];   /* ASCII buffer for floats           */
#else  /* _UNICODE */
    wchar_t floatstring[CVTBUFSIZE + 1];
#endif  /* _UNICODE */

    unsigned long number;               /* temp hold-value                   */
    unsigned __int64 num64;             /* temp for 64-bit integers          */
    void *pointer;                      /* points to user data receptacle    */
    void *start;                        /* indicate non-empty string         */

    unsigned char *scanptr;             /* for building "table" data         */

#ifdef _UNICODE
REG2 wchar_t ch;
#else  /* _UNICODE */
REG2 int ch;
#endif  /* _UNICODE */
    int charcount;                      /* total number of chars read        */
REG1 int comchr;                        /* holds designator type             */
    int count;                          /* return value.  # of assignments   */

    int started;                        /* indicate good number              */
    int width;                          /* width of field                    */
    int widthset;                       /* user has specified width          */

/* Neither coerceshort nor farone are need for the 386 */

    unsigned char rngch;                /* used while scanning range         */

    char done_flag;                     /* general purpose loop monitor      */
    unsigned char last;                 /* also for %[a-z]                   */
    char longone;                       /* 0 = SHORT, 1 = LONG, 2 = L_DOUBLE */
    int integer64;                      /* 1 for 64-bit integer, 0 otherwise */
    char negative;                      /* flag for '-' detected             */
    unsigned char prevchar;             /* for %[a-z]                        */
    char reject;                        /* %[^ABC] instead of %[ABC]         */
    char suppress;                      /* don't assign anything             */
    char match;                         /* flag: !0 if any fields matched    */
    va_list arglistsave;                /* save arglist value                */

    char fl_wchar_arg;                  /* flags wide char/string argument   */
#ifdef _UNICODE
    wchar_t wdecimal;                   /* wide version of decimal point     */
    wchar_t *wptr;                      /* pointer traverses wide floatstring*/
#endif  /* _UNICODE */

    int _tflag = 0;

    _ASSERTE(format != NULL);

#ifndef CPRFLAG
    _ASSERTE(stream != NULL);
#endif  /* CPRFLAG */

    /*
    count = # fields assigned
    charcount = # chars read
    match = flag indicating if any fields were matched

    [Note that we need both count and match.  For example, a field
    may match a format but have assignments suppressed.  In this case,
    match will get set, but 'count' will still equal 0.  We need to
    distinguish 'match vs no-match' when terminating due to EOF.]
    */

    count = charcount = match = 0;

    while (*format) {

        if (isspace((int)*format)) {

            UN_INC(EAT_WHITE()); /* put first non-space char back */

            while ((isspace)(*++format)); /* NULL */
            /* careful: isspace macro may evaluate argument more than once! */

        }

        if ('%' == *format) {

            number = width = widthset = started = done_flag =

            /* ints are the same size as longs and all pointers are 'near' for
               the 386 */

            suppress = negative = reject = prevchar = 0;
            longone = 1;

            integer64 = 0;

            fl_wchar_arg = 0;

            while (!done_flag) {

                comchr = *++format;
                if (isdigit(comchr)) {
                    ++widthset;
                    width = MUL10(width) + (comchr - '0');
                } else
                    switch (comchr) {
                        case 'F':
                        case 'N':   /* no way to push NEAR in large model */
                            break;  /* NEAR is default in small model */
                        case 'h':
                            /* set longone to 0 */
                            --longone;
                            break;

            case _T('I'):
                if ( (*(format + 1) == _T('6')) &&
                     (*(format + 2) == _T('4')) )
                {
                    format += 2;
                    ++integer64;
                    num64 = 0;
                    break;
                }
                goto DEFAULT_LABEL;

            case 'L':
                            ++longone;
                                    /* NOBREAK */
                        case 'l':
                            ++longone;
                            break;
                        case '*':
                            ++suppress;
                            break;

                        default:
DEFAULT_LABEL:
                            ++done_flag;
                            break;
                    }
            }

            if (!suppress) {
                arglistsave = arglist;
                pointer = va_arg(arglist,void *);
            }

            done_flag = 0;

            /* switch to lowercase to allow %E,%G, and to
               keep the switch table small */

            comchr = *format | ('a' - 'A');

            /*
             *  Generic string handling support:  %tc, %ts accept
             *  either chars or wide-chars depending on _tflag.
             *  _tflag == 1 means wide-chars.
             */
            if (comchr == 't') {
                if (_tflag == 1)
                    comchr = 'w';
                else
                    comchr = *(++format);
            }

            if ('n' != comchr)
                if ('w' == comchr) {
                    fl_wchar_arg = 1;
                    comchr = *++format;
                    if (comchr == 'c')
                        ch = INC();
                    else if (comchr == 's')
                        ch = EAT_WHITE();
                    else
                        goto error_return; /* not 'wc' or 'ws' */
                } else
                if ('c' != comchr && LEFT_BRACKET != comchr)
                    ch = EAT_WHITE();
                else
                    ch = INC();

            if (!widthset || width) {

                switch(comchr) {

                    case 'c':
                        if (!widthset) {
                            ++widthset;
                            ++width;
                        }
                        scanptr = cbrackset;
                        --reject; /* set reject to 255 */
                        goto scanit2;

                    case 's':
                        scanptr = sbrackset;
                        --reject; /* set reject to 255 */
                        goto scanit2;

                    case LEFT_BRACKET :   /* scanset */
                        scanptr = (char *)(++format);

                        if ('^' == *scanptr) {
                            ++scanptr;
                            --reject; /* set reject to 255 */
                        }


scanit2:
                        memset(table, 0, ASCII);


                        if (LEFT_BRACKET == comchr)
                            if (']' == *scanptr) {
                                prevchar = ']';
                                ++scanptr;

                                table[ ']' >> 3] = 1 << (']' & 7);

                            }

                        while (']' != *scanptr) {

                            rngch = *scanptr++;

                            if ('-' != rngch ||
                                 !prevchar ||           /* first char */
                                 ']' == *scanptr) /* last char */

                                table[(prevchar = rngch) >> 3] |= 1 << (rngch & 7);

                            else {  /* handle a-z type set */

                                rngch = *scanptr++; /* get end of range */

                                if (prevchar < rngch)  /* %[a-z] */
                                    last = rngch;
                                else {              /* %[z-a] */
                                    last = prevchar;
                                    prevchar = rngch;
                                }
                                for (rngch = prevchar; rngch <= last; ++rngch)
                                    table[rngch >> 3] |= 1 << (rngch & 7);

                                prevchar = 0;

                            }
                        }


                        if (!*scanptr)
                            goto error_return;      /* trunc'd format string */

                        /* scanset completed.  Now read string */

                        if (LEFT_BRACKET == comchr)
                            format = scanptr;

                        start = pointer;

                        /*
                         * execute the format directive. that is, scan input
                         * characters until the directive is fulfilled, eof
                         * is reached, or a non-matching character is
                         * encountered.
                         *
                         * it is important not to get the next character
                         * unless that character needs to be tested! other-
                         * wise, reads from line-buffered devices (e.g.,
                         * scanf()) would require an extra, spurious, newline
                         * if the first newline completes the current format
                         * directive.
                         */
                        UN_INC(ch);

                        while ( !widthset || width-- ) {

                            ch = INC();
                            if (
#ifndef _UNICODE
#ifndef CPRFLAG
                              (EOF != ch) &&
#endif  /* CPRFLAG */
                              ((table[ch >> 3] ^ reject) & (1 << (ch & 7)))
#else  /* _UNICODE */
                              (WEOF != ch) &&
                              ((ch>>3 >= ASCII) ? reject :
                              ((table[ch >> 3] ^ reject) &
                                        (1 << (ch & 7))))
#endif  /* _UNICODE */
                            ) {
                                if (!suppress) {
#ifndef _UNICODE
                                    if (fl_wchar_arg) {
                                        char temp[2];
                                        temp[0] = (char) ch;
                                        if (isleadbyte(ch))
                                            temp[1] = (char) INC();
                                        mbtowc((wchar_t *)pointer, temp,
                                            MB_CUR_MAX);
                                        /* do nothing if mbtowc fails */
                                        pointer = (wchar_t *)pointer + 1;
                                    } else
#else  /* _UNICODE */
                                    if (fl_wchar_arg) {
                                        *(wchar_t *)pointer = ch;
                                        pointer = (wchar_t *)pointer + 1;
                                    } else
#endif  /* _UNICODE */
                                    {
#ifndef _UNICODE
                                    *(char *)pointer = (char)ch;
                                    pointer = (char *)pointer + 1;
#else  /* _UNICODE */
                                    int temp;
                                    /* convert wide to multibyte */
                                    temp = wctomb((char *)pointer, ch);
                                    /* do nothing if wctomb fails */
                                    pointer = (char *)pointer + temp;
#endif  /* _UNICODE */
                                    }
                                } /* suppress */
                                else {
                                    /* just indicate a match */
                                    start = (char *)start + 1;
                                }
                            }
                            else  {
                                UN_INC(ch);
                                break;
                            }
                        }

                        /* make sure something has been matched and, if
                           assignment is not suppressed, null-terminate
                           output string if comchr != c */

                        if (start != pointer) {
                            if (!suppress) {
                                ++count;
                                if ('c' != comchr) /* null-terminate strings */
                                    if (fl_wchar_arg)
                                        *(wchar_t *)pointer = L'\0';
                                    else
                                    *(char *)pointer = '\0';
                            } else /*NULL*/;
                        }
                        else
                            goto error_return;

                        break;

                    case 'i':   /* could be d, o, or x */

                        comchr = 'd'; /* use as default */

                    case 'x':

                        if (_T('-') == ch) {
                            ++negative;

                            goto x_incwidth;

                        } else if (_T('+') == ch) {
x_incwidth:
                            if (!--width && widthset)
                                ++done_flag;
                            else
                                ch = INC();
                        }

                        if (_T('0') == ch) {

#ifdef _UNICODE
                            if (L'x' == (ch = INC()) || L'X' == ch) {
#else  /* _UNICODE */
                            if ('x' == ((char)(ch = INC())) || 'X' == (char)ch){
#endif  /* _UNICODE */
                                ch = INC();
                                comchr = 'x';
                            } else {
                                ++started;
                                if ('x' != comchr)
                                    comchr = 'o';
                                else {
                                    /* scanning a hex number that starts */
                                    /* with a 0. push back the character */
                                    /* currently in ch and restore the 0 */
                                    UN_INC(ch);
                                    ch = _T('0');
                                }
                            }
                        }
                        goto getnum;

                        /* NOTREACHED */

                    case 'p':
                        /* force %hp to be treated as %p */
                        longone = 1;

                    case 'o':
                    case 'u':
                    case 'd':

                        if (_T('-') == ch) {
                            ++negative;

                            goto d_incwidth;

                        } else if (_T('+') == ch) {
d_incwidth:
                            if (!--width && widthset)
                                ++done_flag;
                            else
                                ch = INC();
                        }

getnum:
                        if ( integer64 ) {

                            while (!done_flag) {

                                if (_T('x') == comchr)

#ifdef _UNICODE
                                    if (iswxdigit(ch)) {
#else  /* _UNICODE */
                                    if (isxdigit(ch)) {
#endif  /* _UNICODE */
                                        num64 = (num64 << 4);
                                            ch = HEXTODEC(ch);
                                    }
                                    else
                                        ++done_flag;

#ifdef _UNICODE
                                else if (iswdigit(ch))
#else  /* _UNICODE */
                                else if (isdigit(ch))
#endif  /* _UNICODE */

                                    if (_T('o') == comchr)
                                        if (_T('8') > ch)
                                            num64 = (num64 << 3);
                                        else {
                                            ++done_flag;
                                        }
                                    else /* _T('d') == comchr */
                                            num64 = MUL10(num64);

                                else
                                    ++done_flag;

                                if (!done_flag) {
                                    ++started;
                                    num64 += ch - _T('0');

                                    if (widthset && !--width)
                                            ++done_flag;
                                    else
                                            ch = INC();
                                } else
                                    UN_INC(ch);

                            } /* end of WHILE loop */

                            if (negative)
                                    num64 = (unsigned __int64 )(-(__int64)num64);
                        }
                        else {

                            while (!done_flag) {

                                if ('x' == comchr || 'p' == comchr)

#ifdef _UNICODE
                                    if (iswxdigit(ch)) {
#else  /* _UNICODE */
                                    if (isxdigit(ch)) {
#endif  /* _UNICODE */
                                        number = (number << 4);
                                        ch = HEXTODEC(ch);
                                    }
                                    else
                                        ++done_flag;

#ifdef _UNICODE
                                else if (iswdigit(ch))
#else  /* _UNICODE */
                                else if (isdigit(ch))
#endif  /* _UNICODE */

                                    if ('o' == comchr)
                                        if (_T('8') > ch)
                                            number = (number << 3);
                                        else {
                                            ++done_flag;
                                        }
                                    else /* 'd' == comchr */
                                        number = MUL10(number);

                                else
                                    ++done_flag;

                                if (!done_flag) {
                                    ++started;
                                    number += ch - _T('0');

                                    if (widthset && !--width)
                                        ++done_flag;
                                    else
                                        ch = INC();
                                } else
                                     UN_INC(ch);

                            } /* end of WHILE loop */

                            if (negative)
                                number = (unsigned long)-(long)number;
                        }

                        if ('F' == comchr)  /* expected a ':' in long pointer */
                            started = 0;

                        if (started)
                            if (!suppress) {

                                ++count;
assign_num:
                                if ( integer64 )
                                    *(__int64 UNALIGNED *)pointer = (unsigned __int64)num64;
                                else if (longone)
                                    *(long *)pointer = (unsigned long)number;
                                else
                                    *(short *)pointer = (unsigned short)number;

                            } else /*NULL*/;
                        else
                            goto error_return;

                        break;

                    case 'n':   /* char count, don't inc return value */
                        number = charcount;
                        goto assign_num; /* found in number code above */


                    case 'e':
                    case 'f':
                    case 'g': /* scan a float */

#ifndef _UNICODE
                        scanptr = floatstring;

                        if ('-' == ch) {
                            *scanptr++ = '-';
                            goto f_incwidth;

                        } else if ('+' == ch) {
f_incwidth:
                            --width;
                            ch = INC();
                        }

                        if (!widthset || width > CVTBUFSIZE)              /* must watch width */
                            width = CVTBUFSIZE;


                        /* now get integral part */

                        while (isdigit(ch) && width--) {
                            ++started;
                            *scanptr++ = (char)ch;
                            ch = INC();
                        }

                        /* now check for decimal */

                        if (*___decimal_point == (char)ch && width--) {
                            ch = INC();
                            *scanptr++ = *___decimal_point;

                            while (isdigit(ch) && width--) {
                                ++started;
                                *scanptr++ = (char)ch;
                                ch = INC();
                            }
                        }

                        /* now check for exponent */

                        if (started && ('e' == (char)ch || 'E' == (char)ch) && width--) {
                            *scanptr++ = 'e';

                            if ('-' == (ch = INC())) {

                                *scanptr++ = '-';
                                goto f_incwidth2;

                            } else if ('+' == ch) {
f_incwidth2:
                                if (!width--)
                                    ++width;
                                else
                                    ch = INC();
                            }


                            while (isdigit(ch) && width--) {
                                ++started;
                                *scanptr++ = (char)ch;
                                ch = INC();
                            }

                        }

                        UN_INC(ch);

                        if (started)
                            if (!suppress) {
                                ++count;
                                *scanptr = '\0';
                                _fassign( longone-1, pointer , floatstring);
                            } else /*NULL */;
                        else
                            goto error_return;

#else  /* _UNICODE */
                        wptr = floatstring;

                        if (L'-' == ch) {
                            *wptr++ = L'-';
                            goto f_incwidthw;

                        } else if (L'+' == ch) {
f_incwidthw:
                            --width;
                            ch = INC();
                        }

                        if (!widthset || width > CVTBUFSIZE)
                            width = CVTBUFSIZE;


                        /* now get integral part */

                        while (iswdigit(ch) && width--) {
                            ++started;
                            *wptr++ = ch;
                            ch = INC();
                        }

                        /* now check for decimal */

                        /* convert decimal point to wide-char */
                        /* assume result is single wide-char */
                        mbtowc (&wdecimal, ___decimal_point, MB_CUR_MAX);

                        if (wdecimal == ch && width--) {
                            ch = INC();
                            *wptr++ = wdecimal;

                            while (iswdigit(ch) && width--) {
                                ++started;
                                *wptr++ = ch;
                                ch = INC();
                            }
                        }

                        /* now check for exponent */

                        if (started && (L'e' == ch || L'E' == ch) && width--) {
                            *wptr++ = L'e';

                            if (L'-' == (ch = INC())) {

                                *wptr++ = L'-';
                                goto f_incwidth2w;

                            } else if (L'+' == ch) {
f_incwidth2w:
                                if (!width--)
                                    ++width;
                                else
                                    ch = INC();
                            }


                            while (iswdigit(ch) && width--) {
                                ++started;
                                *wptr++ = ch;
                                ch = INC();
                            }

                        }

                        UN_INC(ch);

                        if (started)
                            if (!suppress) {
                                ++count;
                                *wptr = '\0';
                                {
                                /* convert floatstring to char string */
                                /* and do the conversion */
                                size_t cfslength;
                                char *cfloatstring;
                                cfslength =(wptr-floatstring+1)*sizeof(wchar_t);
                                cfloatstring = (char *)malloc (cfslength);
                                wcstombs (cfloatstring, floatstring, cfslength);
                                _fassign( longone-1, pointer , cfloatstring);
                                free (cfloatstring);
                                }
                            } else /*NULL */;
                        else
                            goto error_return;

#endif  /* _UNICODE */
                        break;


                    default:    /* either found '%' or something else */

                        if ((int)*format != (int)ch) {
                            UN_INC(ch);
                            goto error_return;
                            }
                        else
                            match--; /* % found, compensate for inc below */

                        if (!suppress)
                            arglist = arglistsave;

                } /* SWITCH */

                match++;        /* matched a format field - set flag */

            } /* WHILE (width) */

            else {  /* zero-width field in format string */
                UN_INC(ch);  /* check for input error */
                goto error_return;
            }

            ++format;  /* skip to next char */

        } else  /*  ('%' != *format) */
            {

            if ((int)*format++ != (int)(ch = INC()))
                {
                UN_INC(ch);
                goto error_return;
                }
#ifndef _UNICODE
            if (isleadbyte(ch))
                {
                int ch2;
                if ((int)*format++ != (ch2=INC()))
                    {
                    UN_INC(ch2);
                    UN_INC(ch);
                    goto error_return;
                    }

                    --charcount; /* only count as one character read */
                }
#endif  /* _UNICODE */
            }

#ifndef CPRFLAG
        if ( (EOF == ch) && ((*format != '%') || (*(format + 1) != 'n')) )
            break;
#endif  /* CPRFLAG */

    }  /* WHILE (*format) */

error_return:

#ifndef CPRFLAG
    if (EOF == ch)
        /* If any fields were matched or assigned, return count */
        return ( (count || match) ? count : EOF);
    else
#endif  /* CPRFLAG */
        return count;

}

/* _hextodec() returns a value of 0-15 and expects a char 0-9, a-f, A-F */
/* _inc() is the one place where we put the actual getc code. */
/* _whiteout() returns the first non-blank character, as defined by isspace() */

#ifndef _UNICODE
static int __cdecl _hextodec (
    int chr
    )
{
    return isdigit(chr) ? chr : (chr & ~('a' - 'A')) - 'A' + 10 + '0';
}
#else  /* _UNICODE */
static wchar_t __cdecl _hextodec (
    wchar_t chr
    )
{
    if (iswdigit(chr))
        return chr;
    if (iswlower(chr))
        return (wchar_t)(chr - L'a' + 10 + L'0');
    else
        return (wchar_t)(chr - L'A' + 10 + L'0');
}
#endif  /* _UNICODE */


#ifdef CPRFLAG

static int __cdecl _inc (
    void
    )
{
    return(_getche_lk());
}

static int __cdecl _whiteout (
    REG1 int *counter
    )
{
    REG2 int ch;

    while((isspace)(ch = (++*counter, _inc())));
    return ch;
}

#elif defined (_UNICODE)

/*
 * Manipulate wide-chars in a file.
 * A wide-char is hard-coded to be two chars for efficiency.
 */

static wchar_t __cdecl _inc (
    REG1 FILE *fileptr
    )
{
    wchar_t c1, c2;

    c1 = (wchar_t)_getc_lk(fileptr);
    c2 = (wchar_t)_getc_lk(fileptr);
    return (wchar_t)((feof(fileptr) || ferror(fileptr)) ? WEOF : c2<<8 | c1);
}

static void __cdecl _un_inc (
    wchar_t chr,
    FILE *fileptr
    )
{
    if (WEOF != chr) {
        _ungetc_lk((int)(chr >> 8), fileptr);
        _ungetc_lk((int)(chr & 0xff), fileptr);
    }
}

static wchar_t __cdecl _whiteout (
    REG1 int *counter,
    REG3 FILE *fileptr
    )
{
    REG2 wchar_t ch;

    while((iswspace)(ch = (++*counter, _inc(fileptr))));
    return ch;
}

#else  /* defined (_UNICODE) */

static int __cdecl _inc (
    REG1 FILE *fileptr
    )
{
    return(_getc_lk(fileptr));
}

static void __cdecl _un_inc (
    int chr,
    FILE *fileptr
    )
{
    if (EOF != chr)
        _ungetc_lk(chr, fileptr);
}

static int __cdecl _whiteout (
    REG1 int *counter,
    REG3 FILE *fileptr
    )
{
    REG2 int ch;

    while((isspace)(ch = (++*counter, _inc(fileptr))));
    return ch;
}

#endif  /* defined (_UNICODE) */


#endif  /* defined (_M_MPPC) || defined (_M_M68K) */

#endif  /* _WIN32 */
