/* mw_util.c */

#include "mw_util.h"

int str_len(const char *s);
/*
 * mw_pr - printf a text line
 */

void mw_pr(const char *s)
{
	write ( 1, (char *)s, str_len( s ) );
}

/*
 * STR_LEN - return the length of a string
 */
int str_len(const char *s)
{
	const char *t;

	for (t = s; *t != '\0'; ++t)
		;
	return t - s;
}

int close()
{ return 0; }

int read()
{ return 0; }

int lseek()
{ return 0; }

int open()
{ return 0; }