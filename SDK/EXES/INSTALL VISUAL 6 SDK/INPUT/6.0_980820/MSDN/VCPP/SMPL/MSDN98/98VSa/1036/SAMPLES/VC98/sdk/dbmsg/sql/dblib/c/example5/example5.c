/*	example5.c */
/*
** This example illustrates dbconvert.	It converts a
** number of constants to strings, a number of strings
** to numerical or binary quantities, and a number of
** numerical quantities to other numerical types.
**
*/

#if defined(DBNTWIN32)
#include <windows.h>
#endif

#include <stdio.h>
#include <sqlfront.h>
#include <sqldb.h>

#define ARRAY_LEN	20

/* Forward declarations of the error handler and message handler.
*/
int err_handler(DBPROCESS*, int, int, int, char*, char*);
int msg_handler(DBPROCESS*, DBINT, int, int, char*);

main(argc, argv)
int	argc;
char	*argv[];
{
	/* These variables hold the results of data conversions. */
	static DBBINARY	my_binary_array[ARRAY_LEN]
	= {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0};
	DBFLT8	my_flt8;
	DBINT	my_int4;
	DBMONEY	my_money;
	DBCHAR	my_string[ARRAY_LEN];

        dbinit();		/* initialize dblib */

	/* Install the user-supplied error-handling and message-handling
	* functions. They are defined at the bottom of this source file.
	*/
	dbmsghandle((DBMSGHANDLE_PROC)msg_handler);
	dberrhandle((DBERRHANDLE_PROC)err_handler);

	/* Convert numerical and binary constants to strings. */

	dbconvert
	((DBPROCESS *)NULL, SQLBINARY, my_binary_array, (DBINT)8,
            SQLCHAR, my_string,(DBINT)-1);
	printf("Binary constant 0x123456789abcdef0 converted to string");
	printf("\"%s\".\n\n", my_string);

	my_flt8 = 55.555;
	dbconvert
	((DBPROCESS *)NULL, SQLFLT8, (BYTE *) &my_flt8,
            (DBINT)-1, SQLCHAR, my_string, (DBINT)-1);
	printf
	("Floating-pt constant 55.555 converted to string \"%s\".\n\n",
	my_string);

	/* Convert string constants to numerical and binary quantities. */

	dbconvert
	((DBPROCESS *)NULL, SQLCHAR, "123", (DBINT)-1, SQLINT4, (BYTE *)
		&my_int4, (DBINT)-1);
	printf
	("String constant \"123\" converted to 4-byte integer %ld.\n\n",
	my_int4);

	dbconvert
	((DBPROCESS *)NULL,
	SQLCHAR, "0xfedc", (DBINT)-1, SQLBINARY, my_binary_array,
            (DBINT)ARRAY_LEN);
	printf("String constant \"0xfedc\" converted to binary sequence ");
	printf("%hx.\n\n", *((DBSMALLINT *)my_binary_array));

	dbconvert
	((DBPROCESS *)NULL, SQLCHAR, "123.456", (DBINT)-1, SQLFLT8,
	   (BYTE *) &my_flt8, (DBINT)-1);
	printf("String constant \"123.456\" converted to ");
	printf("floating-pt number %f.\n\n", my_flt8);

	/* Convert numerical types to other numerical types. */

	my_flt8 = 98.76;
	dbconvert
	   ((DBPROCESS *)NULL, SQLFLT8, (BYTE *) &my_flt8, (DBINT)-1, SQLMONEY,
		(BYTE *) &my_money, (DBINT)-1);
	dbconvert
	   ((DBPROCESS *)NULL, SQLMONEY, (BYTE *) &my_money, (DBINT)-1, SQLCHAR,
	       my_string, (DBINT)-1);
	printf
	("floating-pt number %f converted to money value %s.\n\n",
	my_flt8, my_string);

	dbconvert
	   ((DBPROCESS *)NULL, SQLMONEY, (BYTE *) &my_money, (DBINT)-1, SQLFLT8,
	       (BYTE *) &my_flt8, (DBINT)-1);
	printf
	("money value %s converted to floating-pt value %f.\n\n",
	my_string, my_flt8);

	return(STDEXIT);
}

int err_handler(dbproc, severity, dberr, oserr, dberrstr, oserrstr)
DBPROCESS	*dbproc;
int	severity;
int	dberr;
int	oserr;
char	*dberrstr;
char	*oserrstr;
{
    printf("DB-LIBRARY error:\n\t%s\n", dberrstr);

	if (oserr != DBNOERR)
		printf("Operating-system error:\n\t%s\n", oserrstr);

	if ((dbproc == NULL) || (DBDEAD(dbproc)))
		return(INT_EXIT);

	return(INT_CANCEL);
}

int msg_handler(dbproc, msgno, msgstate, severity, msgtext)
DBPROCESS	*dbproc;
DBINT	msgno;
int	msgstate;
int	severity;
char	*msgtext;
{
	printf
	("SQL Server message %ld, state %d, severity %d:\n\t%s\n",
	msgno, msgstate, severity, msgtext);
	return(0);
}
