/*************************************************************************

SQLTESTC - SQL Data Server sample program for console-based Windows NT.
		 
Copyright (c), 1995 by Microsoft Corp.

*************************************************************************/

#define	DBNTWIN32		// must identify operating system environment
#include "windows.h"

#include <sqlfront.h>
#include <sqldb.h>	   // DB-LIB header file (should always be included)
#include <stdio.h>


main ()
{
	PDBPROCESS dbproc;  // allocate	a DB-LIB process structure
	PLOGINREC  login;   // allocate	a DB-LIB login structure

	// Variables used to store the returning data
	char       au_lname[41];
	char       au_fname[20];
	char       id[12];
	char       phone[13];
	char       address[41];
	char       city[21];
	char       state[3];
	char       zip[6];
	char       getname[41];
	char       Servername[25];
	RETCODE    result_code;

	// Forward declarations of the error handler and message handler.
    int err_handler(PDBPROCESS, int, int, int, char*, char*);
    int msg_handler(PDBPROCESS, DBINT, int, int, char*);

	if (dbinit() == (char *)NULL)
	{
		printf("Communications layer not loaded\n");
		return(1);
	}
	
	// Install the user-supplied error-handling	and message-handling
	// routines. They are defined at the bottom	of this	source file.
	
	dberrhandle((DBERRHANDLE_PROC)err_handler);
	dbmsghandle((DBMSGHANDLE_PROC)msg_handler);

	// Get server's computer name
	Servername[0] = '\0';
	printf ("\nEnter Name of SQL Server: ");
	gets (Servername);

	login = dblogin();                     // get login record from DB-LIB
	DBSETLUSER (login, (char *)"sa");      // set the username
	DBSETLAPP (login, (char *)"sqltestp"); // set the application name
	DBSETLPWD (login, (char *)"");         // set the SQL Server password
	DBSETLVERSION(login,DBVER60);

	// Now attempt to create and initialize a DBPROCESS structure
	if ((dbproc	= dbopen (login, Servername)) == NULL)
	{
		printf ("dbopen failed\n");
		return (1); // exit program
	}

	dbuse (dbproc, "pubs"); // use the "pubs" database

	while (TRUE)
	{
		printf ("\nEnter author's last name to retrieve (return to exit): ");
		gets (getname);

		if (getname[0] == '\0') // if only a return was entered
			break;

		// construct command buffer to be sent to the SQL server
		dbcmd (dbproc, (char *)"select au_id, au_lname, au_fname, phone,");
		dbcmd (dbproc, (char *)" address, city, state, zip");
		dbcmd (dbproc, (char *)" from authors");
		dbcmd (dbproc,	(char *)" where au_lname = '");
		dbcmd (dbproc, (char *)getname);
		dbcmd (dbproc, (char *)"'");

		dbsqlexec (dbproc); // send command buffer to SQL server

		// now check the results from the SQL server
		while ((result_code = dbresults(dbproc)) != NO_MORE_RESULTS)
		{
			if (result_code == SUCCEED)
			{
				dbbind (dbproc,	1, NTBSTRINGBIND, (DBINT) 0, (char *)id);
				dbbind (dbproc,	2, NTBSTRINGBIND, (DBINT) 0, (char *)au_lname);
				dbbind (dbproc,	3, NTBSTRINGBIND, (DBINT) 0, (char *)au_fname);
				dbbind (dbproc,	4, NTBSTRINGBIND, (DBINT) 0, (char *)phone);
				dbbind (dbproc,	5, NTBSTRINGBIND, (DBINT) 0, (char *)address);
				dbbind (dbproc,	6, NTBSTRINGBIND, (DBINT) 0, (char *)city);
				dbbind (dbproc,	7, NTBSTRINGBIND, (DBINT) 0, (char *)state);
				dbbind (dbproc,	8, NTBSTRINGBIND, (DBINT) 0, (char *)zip);

				// now process the rows
				while (dbnextrow(dbproc) != NO_MORE_ROWS)
				{
					printf ("Author ID:  %s\n",	id);
					printf ("Last Name:  %s\n",	au_lname);
					printf ("First Name: %s\n",	au_fname);
					printf ("Address:    %s\n",	address);
					printf ("City:       %s\n",	city);
					printf ("State:      %s\n",	state);
					printf ("Zip Code:   %s\n",	zip);
					printf ("Telephone:  %s\n",	phone);
					printf ("\n");
				}
			}
			else
			{
				printf ("Results Failed\n");
				break;
			}
		}
	} // while (TRUE)

	// Close the connection and exit
	dbexit();
}

int err_handler(PDBPROCESS dbproc, int severity, int dberr, int oserr, char * dberrstr, char * oserrstr)
{
	if (dberrstr != NULL)
		printf("DB-LIBRARY error:\n\t%s\n", dberrstr);

	if (oserr != DBNOERR)
		printf("Operating-system error:\n\t%s\n", oserrstr);

	if ((dbproc == NULL) ||	(DBDEAD(dbproc)))
		return(INT_EXIT);
	else
		return(INT_CANCEL);
}

int msg_handler(PDBPROCESS dbproc, DBINT msgno, int msgstate, int severity, char * msgtext)
{
	printf("SQL Server message %ld, state %d, severity %d:\n\t%s\n",
			msgno, msgstate, severity, msgtext);
	return(0);
}
