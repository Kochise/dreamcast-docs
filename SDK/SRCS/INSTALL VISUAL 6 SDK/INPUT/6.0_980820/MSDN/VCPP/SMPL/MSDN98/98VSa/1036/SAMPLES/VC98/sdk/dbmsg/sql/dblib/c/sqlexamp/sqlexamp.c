/* SQLEXAMP.C - Copyright (c) 1990 - 1995 by Craig Henry.  This program may
** be freely distributed and copied, without charge.  However, any attempt to
** charge for this program will be considered a copyright infringement and
** will be prosecuted to the fullest extent.
**
** This program provides a simple example of logging onto a SQL Server,
** sending down commands, retrieving metadata, and result rows.  Formatting
** and printing those results on the console.
**
*/

#if defined(DBNTWIN32)
#include <windows.h>
#endif

#include "stdio.h"		// include standard header
#include "sqlfront.h"		// include dblib macro/manifest defines
#include "sqldb.h"		// include dblib datatype, prottypes, etc
#include "string.h"		// include for string functions
#include "malloc.h"		// include for malloc and free


// prototypes for internal functions
extern int DetermineRowSize(DBPROCESS *,int);
extern RETCODE PrintHeaders(DBPROCESS *);
extern RETCODE PrintRow(DBPROCESS *);

/*
** DetermineRowSize(DBPROCESS *,int)
**
** This function returns either the size of all columns in the row, converted
** to character data (SQLCHAR) with one space between each column, or
** if col is non-zero, the length of the input column converted to string.
** It is used to build the header strings, and each row of data, and is
** called to allocate the memory needed for each row, and determine how
** much of that space is to be used for each column
*/
int DetermineRowSize(dbproc,col)
DBPROCESS *dbproc;		// The SQL Server connection structure
int col;			// column size to get, 0 for all
{
    int x,cols;			// counters
    int length=0;		// total length of column(row).
    int namelength;		// length of name of column
    int prlength;		// printable length
    char *name;			// pointer to column name
    if(!col)		        // get number of columns
       cols = dbnumcols(dbproc);
    // count from 1 to numcols if col is 0, else x will = col only
    for(x=((col) ? col : 1);x<=((col) ? col : cols);x++)
    {
        switch(dbcoltype(dbproc,x))	// get column type, determine SQLCHAR
        {				// converted length
		case SQLNUMERIC:
		case SQLDECIMAL:
			{
			DBCOL Col;
				dbcolinfo(dbproc,CI_REGULAR,x,0,&Col);
				prlength = Col.Precision + 2;
			}
			break;

	    case SQLBIT:		// The PR... values are found in the
	        prlength = PRBIT;	// SQLDB.H header file.
	        break;
	    case SQLINT1:
   	        prlength = PRINT1;
	        break;
	    case SQLINT2:
  	        prlength = PRINT2;
	        break;
	    case SQLINT4:
	        prlength = PRINT4;
	        break;
	    case SQLFLT8:
	        prlength = PRFLT8;
	        break;
	    case SQLDATETIME:
	        prlength = PRDATETIME;
	        break;
	    case SQLMONEY:
	        prlength = PRMONEY;
	        break;
            case SQLVARBINARY :		// VARBINARY IMAGE, and BINARY
            case SQLBINARY:		// convert to 2 times length
            case SQLIMAGE:
                prlength = dbcollen(dbproc,x)*2;
                break;
	    default :
	        prlength = dbcollen(dbproc,x);	 // other types are maximum of
	        break;				 // actual column length
        }
        name = (char *)dbcolname(dbproc,x);		 // names may be longer than
        namelength =  (name) ? strlen(name) : 0; // column so use name len if
        if(prlength<namelength)			 // longer of two.
           length+=namelength+1;		 // add one for space between
        else					 // columns
           length+=prlength+1;
    }
    return length;			// return the length of the
    					// field
}
/*
** RETCODE PrintHeaders(DBPROCESS *)
**
** This function builds the string that contains the names of each column,
** and a string containing '=' as a separator line.  It does this by finding
** the print size of each column, allocating a buffer to hold all column names
** plus one space between each column name, then copying that name into the
** appropriate location into the buffer.  Finally the two lines are
** printed.
*/
RETCODE PrintHeaders(dbproc)
DBPROCESS *dbproc;		// The SQL Server connection structure pointer
{
    int x,cols,size;		// counters
    char *header;		// pointer for separator buffer
    char *colnames;		// pointer for column name buffer
    char *colname;		// scratch pointers
    char *ptr,*hptr;
    size = DetermineRowSize(dbproc,0);	// get size of buffers
    ptr = colnames = malloc(size+1); 	// get name buffer
    hptr = header = malloc(size+1); 	// get separator buf
    memset (header,' ',size);		// set buffers to all spaces
    memset (colnames,' ',size);
    cols = dbnumcols(dbproc);	// get number of columns
    for(x=1;x<=cols;x++)	// loop on all columns
    {
        size = DetermineRowSize(dbproc,x); 	// get size of this column
        colname = (char *)dbcolname(dbproc,x);		// get column name
        strncpy(ptr,colname,strlen(colname));	// copy name
        memset(hptr,'=',size-1);			// set ='s in separator line
        hptr+=size;				// move to next position
        ptr+=size;				// move to next position
    }
    *ptr = '\0';			// null term both strings
    *hptr = '\0';
    printf("%s\n",colnames);		// print both strings
    printf("%s\n",header);
    free(colnames);			// free both buffers
    free(header);
    return SUCCEED;			// done
}
/*
** RETCODE PrintRow(DBPROCESS *)
**
** This function prints out one row.  dbnextrow() must be called to fetch the
** row to print.  This routine could be used to print the current row as
** many times as wanted, as the current row data is always available until
** dbnextrow() is called to fetch the next row.  This routine works like
** PrintHeaders above, but each column's data is obtained instead of a row
** name, and converted to a string.  It is then set into the buffer.
*/
RETCODE PrintRow(dbproc)
DBPROCESS *dbproc;		// SQL Server connection structure
{
    int x,cols,size,datasize,colwidth,coltype;	// counters
    char *datavals;		// data buffer pointer
    char *data;			// column data pointer
    char *ptr;			// scratch pointer
	 colwidth = DetermineRowSize(dbproc,0);
    ptr = datavals = malloc(colwidth+1); // get buffer
    cols = dbnumcols(dbproc);	// get number of columns
    for(x=1;x<=cols;x++)	// do all columns
    {
	 	  coltype = dbcoltype(dbproc,x);
        size = DetermineRowSize(dbproc,x); // determine size of this column
        memset(ptr,' ',size);		// set it to spaces
        data = (char *)dbdata(dbproc,x);	// get pointer to column's data
        if(data == (BYTE *)NULL)	// if NULL, use "NULL"
        {
            strncpy(ptr,"NULL",4);	// set NULL into buffer
            ptr += size;		// point past this column in output buf
        }
        else				// else have data, so convert to char
        {
            datasize = dbconvert(dbproc,coltype,data,dbdatlen(dbproc,x),
                SQLCHAR,ptr,(DBINT)size-1);
				if (datasize < size && (coltype == SQLNUMERIC || coltype == SQLDECIMAL || coltype == SQLINT1 ||
				    coltype == SQLINT2 || coltype == SQLINT4 || coltype == SQLFLT8 || coltype == SQLFLT4))
					{
					memmove(ptr+size-1-datasize,ptr,datasize);
					memset(ptr,' ',size-1-datasize);
					}
            ptr+=size;
        }
    }
    *ptr = '\0';			// null term string
    printf("%s\n",datavals);		// print row
    free(datavals);			// free buffer
    return SUCCEED;			// done
}

/*
**
** The below main is a mini isql interpreter and as such is only
** used for demonstration purposes.  Command line args include the Server
** name as arg 1, User ID as arg 2, assumes the password is null.
** This routine requests opens the connection after obtaining the login record
** and filling it with the necessary info.  Once the connection is established
** it accpets command input, set's it into the dbproc.  On "go" it executes
** the command against the server, processes each results set and then returns
** to accepting command input.  If "quit" or "exit" is input the program
** is terminated.  This interpreter will not process COMPUTE statements,
** and will not work with commands that return text/image data.
*/
int main(argc, argv)
int argc;
char *argv[];
{
    LOGINREC *login;		// login rec pointer
    DBPROCESS *dbproc;		// SQL Server connection structure pointer

    char cmd[150];		// command buffer
    char server[30];		// server name buffer
    int x=1;			// command line counter
    STATUS retc;		// return code
    const char * sqlversion;		// pointer for version string
    int err_handler(DBPROCESS*, int, int, int, char*, char*);
    int msg_handler(DBPROCESS*, DBINT, int, int, char*);

    *server = '\0';		// null start these two buffers
    *cmd = '\0';

    if(argc == 1)		// if no server name, request it
    {
	printf("Enter Server Name: ");
	gets(server);
    }
    else			// else it was input as first arg
       strcpy(server,argv[1]);
    if(argc < 2)		// if no login id, request it
    {
       printf("Enter User Name: ");
       gets(cmd);
    }
    else			// otherwise it was input as second arg.
       strcpy(cmd,argv[2]);

    // check to see if communications layer was loaded (DOS ONLY)
    if((sqlversion = dbinit()) == (BYTE *)NULL)
    {
       // DOS TSR (DBNMPIPE.EXE) is not loaded, don't bother going any farther
       printf("Error in DB-Library initialization, exiting\n");
       return 1;
    }
    else
       printf("DB-Library version: %s\n",sqlversion); // print dblib version

    dbsettime(30);		// set timeouts to 30 seconds
    
    // set error/msg handlers for this program
    dbmsghandle((DBMSGHANDLE_PROC)msg_handler);
    dberrhandle((DBERRHANDLE_PROC)err_handler);
    
    login = dblogin();		// get a login rec

    DBSETLUSER(login,cmd);		// set login id
    DBSETLHOST(login,"SQL EXAMPLE");	// set host name for sp_who
    DBSETLVERSION(login, DBVER60);

    // open connection to requested server.  Pass null server name for local
    // connection, if name not entered.
    if((dbproc = dbopen(login,(*server) ? server : (char *)NULL)) == (DBPROCESS *)NULL)
    {
        // no one answered, so couldn't connect or error occurred
	printf("Login failed\n");
	return 1;
    }
    else
    {
        // loop on command input until quit or exit appears in first 4 bytes.
	while((strnicmp(cmd,"quit",4) != 0) && (strnicmp(cmd,"exit",4)!=0))
	{
	   printf("%d> ",x++);		// print command prompt
	   gets(cmd);			// get command
	   if(strnicmp(cmd,"go",2) == 0)	// is it go
	   {
	      if(dbsqlexec(dbproc) == FAIL)	// execute command
              {
                 // problem occurred, just try another command
                 printf("Error in executing command batch!\n");
                 x = 1;
                 continue;
              }
              // command executed correctly, get results information
	      while((retc = dbresults(dbproc)) != NO_MORE_RESULTS)
	      {
		 if (retc == FAIL)	// if error get out of loop
		     break;
		 // headers and data could be printed here with only two
                 // function calls, dbprhead(dbproc), and dbprrow(dbproc),
                 // which would output the headers, and all the data to
                 // standard output.  However, that isn't very informative
                 // toward understanding how this data is obtained and
                 // processed, so I do it the hard way, one column at a time.

                 PrintHeaders(dbproc);		// print header data

                 // loop on each row, until all read
                 while((retc= dbnextrow(dbproc))!=NO_MORE_ROWS)
                 {
                    if(retc == FAIL)		// if fail, then clear
                    {				// connection completely, just
                       dbcancel(dbproc);	// in case.
                       break;
                    }
                    else
                        PrintRow(dbproc);	// else print the current row
                 }
		 if(DBCOUNT(dbproc) == 1L)	// print the row count
		      printf("(1 row effected)\n");
		  else
		      printf("(%ld rows effected)\n",DBCOUNT(dbproc));

	      } // end while(dbresults())

              x = 1;			// reset command line counter
	   }
	   else
	   {
	      strcat(cmd," ");		// go not detected, so put space
	      dbcmd(dbproc,cmd);	// between each command and set in
	   }				// dbproc.

        } // end while()

        dbclose(dbproc);		// quit/exit input, close connection

        // print adios and exit.
        printf("SQL Server Connection to %s closed, bye bye.\n",server);
	return 0;
     }
}
/*
** msg_handler(char *buffer, long len);
**
** This routine is a local isql message handler call back function that
** is invoked whenever the SQL Server is sending a message back to
** the program.
**
*/
int msg_handler(dbproc, Msg, State, Severity, Message)
DBPROCESS *dbproc;		// SQL Server connection structure
DBINT Msg;			// SQL Server message number
int State;			// State of the message
int Severity;			// Severity of the message
char *Message;			// The message itself (read only)
{
    printf("Message No.: %ld, Msg. State: %d, Msg. Severity: %d\n",
	Msg,State,Severity);
    if(Message != NULL)
       printf("%s\n",Message);
    return (0);
}

/*
** err_handler(char *buffer, long len);
**
** This routine is a local error handler called by dblib if an internal
** error occurs, also to notify when a server message has been sent, which is
** obtained through the above message handler.
**
*/
int err_handler(dbproc, Severity,dberr, oserr, errstr, oserrstr)
DBPROCESS *dbproc;		// SQL Server connection structure
int Severity;			// Severity of Dblib error
int dberr;			// dblib error, all dblib errors start at 10000
int oserr;			// OS error from, C runtime
char *errstr;			// dblib error string
char *oserrstr;			// OS error string (if any)
{

    printf("DB-LIBRARY Error - Severity: %d, Error No: %d, OS Error No: %d\n",
       Severity, dberr, oserr);
    if(errstr != NULL)
       printf("%s\n",errstr);
    if(oserrstr != NULL)
       printf("%s\n",oserrstr);
    return INT_CANCEL;
}

/*****************************************************************************/
/*======================== E N D - O F - F I L E ============================*/
/*****************************************************************************/


