/* KallistiOS ##version##

   ctype.h
   (c)2000-2001 Jordan DeLong and Dan Potter

   $Id: ctype.h,v 1.1 2002/02/09 06:15:42 bardtx Exp $
*/

#ifndef __CTYPE_H
#define __CTYPE_H

#include <sys/cdefs.h>

__BEGIN_DECLS

/* Unix specification requires the definition of these as functions too */
int isalpha(int);
int isupper(int);
int islower(int);
int isdigit(int);
int isxdigit(int);
int isspace(int);
int ispunct(int);
int isalnum(int);
int isblank(int);
int isprint(int);
int isgraph(int);
int iscntrl(int);
int isascii(int);
int toascii(int);
int tolower(int);
int toupper(int);

#define _U	0x01	/* upper */
#define _L	0x02	/* lower */
#define _N	0x04	/* number */
#define _S	0x08	/* space */
#define _P	0x10	/* punct */
#define _C	0x20	/* control */
#define _X	0x40	/* hex number */
#define _B	0x80	/* blank */

extern const char _ctype_[];

#define isalpha(c) (_ctype_[(unsigned)(c)] & (_U|_L))
#define isupper(c) (_ctype_[(unsigned)(c)] & _U)
#define islower(c) (_ctype_[(unsigned)(c)] & _L)
#define isdigit(c) (_ctype_[(unsigned)(c)] & _N)
#define isxdigit(c) (_ctype_[(unsigned)(c)] & (_X|_N))
#define isspace(c) (_ctype_[(unsigned)(c)] & _S)
#define ispunct(c) (_ctype_[(unsigned)(c)] & _P)
#define isalnum(c) (_ctype_[(unsigned)(c)] & (_U|_L|_N))
#define isblank(c) (_ctype_[(unsigned)(c)] & _B)
#define isprint(c) (_ctype_[(unsigned)(c)] & (_P|_U|_L|_N|_B))
#define isgraph(c) (_ctype_[(unsigned)(c)] & (_P|_U|_L|_N))
#define iscntrl(c) (_ctype_[(unsigned)(c)] & _C)
#define isascii(c) (((c) & ~0x7F) == 0)
#define toascii(c) ((c) & 0x7f)
#define tolower(c) (isupper(c) ? ((c) + ('a' - 'A')) : (c))
#define toupper(c) (islower(c) ? ((c) - ('a' - 'A')) : (c))
#define _tolower(c) ((c) + ('a' - 'A'))
#define _toupper(c) ((c) - ('a' - 'A'))

__END_DECLS

#endif


