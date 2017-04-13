///////////////////////////////////////////////////////////////////////////////
//
//  FILE: textcopy.cpp
//              
//      Text and image copy application
//
//  FUNCTIONS:
//
//      main() - Main application
//
//  COMMENTS:
//
///////////////////////////////////////////////////////////////////////////////

#include <afx.h>                // MFC 
#include <iostream.h>           // iostream
#include <stdlib.h>             // C run-time

#if defined (_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define DBNTWIN32               // Win32 DB-Library for Windows NT
#include <sqlfront.h>           // DB-Library
#include <sqldb.h>              // DB-Library

extern "C"
{
    #include "getopt.h"         // GetOption
}

#include "textcopy.h"           // specific to this program

// GLOBAL VARIABLES
BOOL bDebug = FALSE;            // debug info
BYTE* aBuf;

///////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION: main()
//
//      Main application
//
//  PARAMETERS:
//
//      argc - count of command line arguments
//      argv - array of command line argument strings
//      envp - array of environment strings
//
//  RETURNS: 0
//
//  COMMENTS:
//
///////////////////////////////////////////////////////////////////////////////
 
int main (
    int argc,
    char** argv,
    char** envp)
{
    char chOpt;                 // gotten option character
    char* pszParam;             // gotten parameter
    int nChunkSize = 4096;          // chunk size
    CString strChunkSize = "4096";  // chunk size
    CString strColumnType;

    CString strServer,          // SQL Server
        strLogin,               // login
        strPassword,            // password
        strDatabase,            // database
        strTable,               // table
        strColumn,              // column
        strWhere,               // where clause
        strFile;                // file
    BOOL bServer = FALSE,       // flags for tracking options
        bLogin = FALSE,
        bPassword = FALSE,
        bDatabase = FALSE,
        bTable = FALSE,
        bColumn = FALSE,
        bWhere = FALSE,
        bFile = FALSE,
        bIn = FALSE,
        bOut = FALSE;

    // banner
    cout << "TEXTCOPY Version 1.0" << endl;

    // initialize DB-Library, get DB-Library version number
    CString strDblibVersion;
    strDblibVersion = dbinit();
    if (strDblibVersion.IsEmpty())
    {
        cout << err << "Could not initialize DB-Library" << endl;
        return (1);
    }
    cout << strDblibVersion << endl;
    
    // get command-line options and parameters
    while (TRUE)
    {
        // all the following command-line options are valid, they
        // are neither case sensitive nor white-space sensitive, and
        // both '/' and '-' are valid switch characters
        //
        //  OPTION  PARAMETER           DESCRIPTION
        //
        //  /S      [sqlserver]         SQL Server
        //  /U      [login]             Login
        //  /P      [password]          Password
        //  /D      [database]          Database
        //  /T      table               Table
        //  /C      column              Column
        //  /W      "where clause"      Where clause in double quotes
        //  /F      file                File
        //  /I                          Into SQL Server from file
        //  /O                          Out of SQL Server into file
        //  /K      chunksize           Chunk size in bytes
        //  /Z                          Debug information
        //  /?                          Usage information
        //
        // for example, all of the following are valid ways to specify
        // a connection to a SQL Server named 'gizmo'
        //
        //  /Sgizmo     /sgizmo     -Sgizmo     -sgizmo
        //  /S gizmo    /s gizmo    -S gizmo    -s gizmo

        chOpt = GetOption(argc, argv, "s:S:u:U:p:P:d:D:t:T:c:C:w:W:f:F:k:K:iIoOzZ?", &pszParam);
        if (chOpt > 1)
        {
            // chOpt is valid argument
            switch (chOpt)
            {
            case 's':   // SQL Server
            case 'S':
                bServer = TRUE;
                strServer = pszParam;
                break;
            case 'u':   // login
            case 'U':
                bLogin = TRUE;
                strLogin = pszParam;
                break;
            case 'p':   // password
            case 'P':
                bPassword = TRUE;
                strPassword = pszParam;
                break;
            case 'd':   // database
            case 'D':
                bDatabase = TRUE;
                strDatabase = pszParam;
                break;
            case 't':   // table
            case 'T':
                bTable = TRUE;
                strTable = pszParam;
                break;
            case 'c':   // column
            case 'C':
                bColumn = TRUE;
                strColumn = pszParam;
                break;
            case 'w':   // where clause
            case 'W':
                bWhere = TRUE;
                strWhere = pszParam;
                break;
            case 'f':   // file
            case 'F':
                bFile = TRUE;
                strFile = pszParam;
                break;
            case 'i':   // direction: into SQL Server from file
            case 'I':
                bIn = TRUE;
                break;
            case 'o':   // direction: out of SQL Server into file
            case 'O':
                bOut = TRUE;
                break;
            case 'k':   // chunk size in bytes
            case 'K':
                if (pszParam != NULL)
                {
                    nChunkSize = atoi (pszParam);
                    _itoa (nChunkSize, strChunkSize.GetBuffer(20), 10);
                    strChunkSize.ReleaseBuffer();
                    if (strChunkSize != pszParam)
                    {
                        cout << err << "Converted chunk size '" << pszParam << "' to " << nChunkSize << endl;
                        return (0);
                    }
                }
                break;
            case 'z':   // debug
            case 'Z':
                bDebug = TRUE;
                break;
            case '?':   // usage info
                DisplayUsage();
                return(0);
                break;
            }
        }
        if (chOpt == 0)
        {
            // end of argument list
            break;
        }
        if ((chOpt == 1) || (chOpt == -1))
        {
            // standalone param or error
            cout << err << "Argument '" << pszParam << "' not recognized" << endl;
            break;
        }
    }

    if ((chOpt == 1) || (chOpt == -1))
    {
        // exit on error
        return (1);
    }

    // prompt the user for any unspecified options
    if (!bServer)
    {
        cout << "Type the SQL Server to connect to: ";
        cinstr (strServer);
    }

    if (!bLogin)
    {
        cout << "Type your login: ";
        cinstr (strLogin);
    }

    if (!bPassword)
    {
        cout << "Type your password: ";
        cinstr (strPassword);
    }

    if (!bDatabase)
    {
        cout << "Type the database: ";
        cinstr (strDatabase);
    }

    if (!bTable)
    {
        cout << "Type the table: ";
        cinstr (strTable);
    }
    
    if (!bColumn)
    {
        cout << "Type the text or image column: ";
        cinstr (strColumn);
    }
    
    if (!bWhere)
    {
        cout << "Type the where clause: ";
        cinstr (strWhere);
    }
    
    if (!bFile)
    {
        cout << "Type the file: ";
        cinstr (strFile);
    }

    if (!bIn && !bOut)
    {
        while (TRUE)
        {
            CString strDirection;
            cout << "Type the direction ('I' for in, 'O' for out): ";
            cinstr (strDirection);
            if (strDirection.CompareNoCase("i") == 0)
            {
                bIn = TRUE;
                break;
            }
            else
            {
                if (strDirection.CompareNoCase("o") == 0)
                {
                    bOut = TRUE;
                    break;
                }
                else
                {
                    cout << err << "The value '" << strDirection << "' is invalid." << endl;
                }
            }
        }
    }

    // parameter validation
    if (strTable.IsEmpty())
    {
        cout << err << "You did not specify a table." << endl;
        return (1);
    }

    if (strColumn.IsEmpty())
    {
        cout << err << "You did not specify a column." << endl;
        return (1);
    }

    if (strWhere.IsEmpty())
    {
        cout << err << "You did not specify a where clause." << endl;
        return (1);
    }

    /*
    CString strLowerWhere = strWhere;
    strLowerWhere.MakeLower();
    if (strLowerWhere.Find ("where ") == -1)
    {
        cout << err << "Your where clause '" << strWhere << "' did not contain the keyword 'where'." << endl;
        return (1);
    }
    */

    if (strFile.IsEmpty())
    {
        cout << err << "You did not specify a file." << endl;
        return (1);
    }

    if (bIn && bOut)
    {
        cout << err << "You cannot specify both 'in' and 'out' directions." << endl;
        return (1);
    }

    if (nChunkSize < 1024)
    {
        cout << err << "Your specified chunk size of " << nChunkSize << " bytes is too small." << endl;
        return (1);
    }

    if (bDebug)
    {
        cout << dbg << "Final parameters:" << endl;
        cout << dbg << "  Server: " << strServer << endl;
        cout << dbg << "  Login: " << strLogin << endl;
        cout << dbg << "  Password: " << strPassword << endl;
        cout << dbg << "  Database: " << strDatabase << endl;
        cout << dbg << "  Table: " << strTable << endl;
        cout << dbg << "  Column: " << strColumn << endl;
        cout << dbg << "  Where clause: " << strWhere << endl;
        cout << dbg << "  File: " << strFile << endl;
        cout << dbg << "  Direction: ";
        if (bIn)
        {
            cout << "Into SQL Server from file." << endl;
        }
        if (bOut)
        {
            cout << "Out of SQL Server into file." << endl;
        }
        cout << dbg << "  Chunk size: " << nChunkSize << " bytes" << endl;
    }

    // install error and message handlers
    dberrhandle (ErrorHandler);
    dbmsghandle (MessageHandler);

    // set DB-Library options
    dbsettime(30);
    dbsetlogintime(10);

    // get login record
    PLOGINREC pLoginRec;
    pLoginRec = dblogin();
    if (pLoginRec == NULL)
    {
        cout << err << "Could not allocate a login record" << endl;
        return (1);
    }

    // fill the login record 
    DBSETLUSER (pLoginRec, strLogin);       // set the login
    DBSETLPWD (pLoginRec, strPassword);     // set the password
    DBSETLAPP (pLoginRec, "textcopy");      // set the app name
    DBSETLHOST (pLoginRec, "textcopy");     // set the host name

    // attempt to connect to SQL Server
    PDBPROCESS pDbproc;
    pDbproc = dbopen (pLoginRec, strServer);
    dbfreelogin (pLoginRec);
    if (pDbproc == NULL)
    {
        cout << err << "Could not connect to SQL Server '" << strServer << "'" << endl;
        return (1);
    }

    // re-used DB-Library return code
    RETCODE r;

    // set textlimit and textsize options for this connection
    if (bOut)
    {
        dbsetopt (pDbproc, DBTEXTLIMIT, strChunkSize);
        dbsetopt (pDbproc, DBTEXTSIZE, "2147483647");
    }

    if (bIn)
    {
        dbsetopt (pDbproc, DBTEXTSIZE, "1024");
    }

    // must send and execute batch to set options
    r = dbsqlexec (pDbproc);
    if (r == FAIL)
    {
        cout << err << "Query execution failed." << endl;
        Cleanup (pDbproc);
        return (1);
    }

    // get empty result set(s) from setting options
    while (TRUE)
    {
        r = dbresults (pDbproc);
        if (r == FAIL)
        {
            cout << err << "Query results failed." << endl;
            Cleanup (pDbproc);
            return (1);
        }
        if (r == NO_MORE_RESULTS)
            break; // while loop
    }

    // use specified database
    if (!strDatabase.IsEmpty())
    {
        r = dbuse (pDbproc, strDatabase);
        if (r == FAIL)
        {
            cout << err << "Could not use database '" << strDatabase << "'" << endl;
            Cleanup(pDbproc);
            return (1);
        }
    }

    // build query
    CString strQuery;

    strQuery = "select " + strColumn + " from " + strTable + " " + strWhere;
    D(cout << "Query: " << strQuery << endl);

    r = dbcmd (pDbproc, strQuery);

    // send and execute query 
    r = dbsqlexec (pDbproc);
    if (r == FAIL)
    {
        cout << err << "Query execution failed." << endl;
        Cleanup (pDbproc);
        return (1);
    }

    // get first result set
    r = dbresults (pDbproc);
    if (r != SUCCEED)
    {
        cout << err << "Query results failed." << endl;
        Cleanup (pDbproc);
        return (1);
    }

    // verify that only a single column was selected    
    if (dbnumcols (pDbproc) != 1)
    {
        cout << err << "More than one column specified." << endl;
        Cleanup (pDbproc);
        return (1);
    }

    // verify that the single column selected is either text or image
    int nColumnType;
    nColumnType = dbcoltype (pDbproc, 1);
    if ((nColumnType != SQLTEXT) && (nColumnType != SQLIMAGE))
    {
        cout << err << "Specified column is not a text or image column." << endl;
        Cleanup (pDbproc);
        return (1);
    }
    else
    {
        if (nColumnType == SQLTEXT)
        {
            strColumnType = "text";
        }
        if (nColumnType == SQLIMAGE)
        {
            strColumnType = "image";
        }
    }

    // buffer for data transfer between DB-Library and file
    aBuf = new BYTE[nChunkSize];
    if (aBuf == 0)
    {
        cout << err << "Unable to allocate transfer buffer of '" << nChunkSize << "' bytes." << endl;
        Cleanup (pDbproc);
        return (1);
    }

    // if the data is coming out of SQL Server and into a file, use dbreadtext
    // (instead of dbnextrow) to read the text or image data from the row
    // in chunks
    if (bOut)
    {
    try
    {
        // set up file 
        CFile file (strFile, CFile::modeCreate | CFile::modeWrite);
        D(cout << "File '" << strFile << "' opened for write" << endl);

        DBINT lWriteBytes;
        while (TRUE)
        {
            // read chunk of text or image data from SQL Server into aBuf
            lWriteBytes = dbreadtext (pDbproc, aBuf, nChunkSize);
            switch (lWriteBytes)
            {
            case 0:
                // end of text or image row
                //D(cout << "End of row" << endl);
                break;
            case -1:
                // dbreadtext failed
                cout << err << "Text or image data retrieval failed." << endl;
                Cleanup (pDbproc);
                return (1);
                break;
            case NO_MORE_ROWS:
                //D(cout << "No more rows" << endl);
                break;
            default:
                // dbreadtext has placed lBytes of text or image data
                // into aBuf, now write that chunk to the file
                file.Write (aBuf, lWriteBytes);
                D(cout << "Wrote " << lWriteBytes << " bytes to file" << endl);
                break;
            }
            if ((lWriteBytes == -1) || (lWriteBytes == NO_MORE_ROWS))
                break; // while loop
        }
        file.Close();
        D(cout << "File closed" << endl);
    }
    catch (CFileException* e)
    {
        //if (e->m_cause == CFileException::fileNotFound)
        cout << err << "Problem with file '" << strFile << "'." << endl;
        e->Delete();
        Cleanup (pDbproc);
        return (1);
    }

    }

    DBBINARY aTextPointer[DBTXPLEN], aTextTimestamp[DBTXTSLEN];
    DBBINARY *pTextPointer, *pTextTimestamp;
    
    // if the data is going into SQL Server from a file, copy the text
    // pointer and text timestamp values into private buffers
    if (bIn)
    {
        // get the single row
        STATUS s;
        s = dbnextrow (pDbproc);
        if (s != REG_ROW)
        {
            cout << err << "Row retrieval failed." << endl;
            Cleanup (pDbproc);
            return (1);
        }

        // get the pointers to the text pointer and text timestamp values
        pTextPointer = dbtxptr (pDbproc, 1);
        pTextTimestamp = dbtxtimestamp (pDbproc, 1);
        if ((pTextPointer == NULL) || (pTextTimestamp == NULL))
        {
            cout << err << "Text or image pointer and timestamp retrieval failed." << endl;
            Cleanup (pDbproc);
            return (1);
        }

        // copy the actual text pointer and text timestamp values into
        // private buffers
        memcpy (aTextPointer, pTextPointer, DBTXPLEN);
        memcpy (aTextTimestamp, pTextTimestamp, DBTXTSLEN);

        // we should only have received one row, so call dbnextrow
        // to get NO_MORE_ROWS
        s = dbnextrow (pDbproc);
        switch (s)
        {
        case NO_MORE_ROWS:
            // this is what we expect
            break;
        case REG_ROW:
            cout << err << "Where clause returned more than one row." << endl;
            Cleanup (pDbproc);
            return (1);
            break;
        default:
            cout << err << "Row retrieval failed." << endl;
            Cleanup (pDbproc);
            return (1);
            break;
        }
    }
    
    // get NO_MORE_RESULTS to clear out all results
    r = dbresults (pDbproc);
    if (r != NO_MORE_RESULTS)
    {
        cout << err << "Query results failed." << endl;
        Cleanup (pDbproc);
        return (1);
    }

    // if the data is going into SQL Server from a file, use dbwritetext
    // (with the private copies of the text or image pointer and timestamp
    // values) and dbmoretext to write the text or image data to
    // SQL Server in chunks
    if (bIn)
    {
    try
    {
        // set up file
        CFile file (strFile, CFile::modeRead);
        D(cout << "File '" << strFile << "' opened for read" << endl);
        D(cout << "File is " << file.GetLength() << " bytes long" << endl);

        // call dbwritetext will NULL text value to indicate that the text
        // values will be sent in chunks using dbmoretext
        r = dbwritetext (pDbproc, strTable + "." + strColumn,
            aTextPointer, DBTXPLEN, aTextTimestamp,
            TRUE, file.GetLength(), NULL);
        if (r == FAIL)
        {
            cout << err << "Text or image write failed." << endl;
            Cleanup (pDbproc);
            return (1);
        }
        
        // call dbsqlok and dbresults to prepare for calling dbmoretext
        r = dbsqlok (pDbproc);
        if (r == FAIL)
        {
            cout << err << "Text or image write failed." << endl;
            Cleanup (pDbproc);
            return (1);
        }
        r = dbresults (pDbproc);
        if (r == FAIL)
        {
            cout << err << "Query results failed." << endl;
            Cleanup (pDbproc);
            return (1);
        }

        // read each chunk from the file and write it to SQL Server
        UINT nReadBytes = nChunkSize;
        while (nReadBytes == UINT(nChunkSize))
        {
            // read chunk from file into aBuf
            nReadBytes = file.Read (aBuf, nChunkSize);
            D(cout << "Read "<< nReadBytes << " bytes from file" << endl);
            
            // write chunk of text or image data from aBuf to SQL Server
            r = dbmoretext (pDbproc, nReadBytes, aBuf);
            if (r == FAIL)
            {
                cout << err << "Text or image write failed." << endl;
                Cleanup (pDbproc);
                return (1);
            }
        }

        file.Close();
        D(cout << "File closed" << endl);

        // call dbsqlok and dbresults to signal end of calls to
        // dbmoretext and completion of text or image write
        r = dbsqlok (pDbproc);
        if (r == FAIL)
        {
            cout << err << "Text or image write failed." << endl;
            Cleanup (pDbproc);
            return (1);
        }
        r = dbresults (pDbproc);
        if (r == FAIL)
        {
            cout << err << "Query results failed." << endl;
            Cleanup (pDbproc);
            return (1);
        }
    }
    catch (CFileException* e)
    {
        //if (e->m_cause == CFileException::fileNotFound)
        cout << err << "Problem with file '" << strFile << "'." << endl;
        e->Delete();
        Cleanup (pDbproc);
        return (1);
    }

    }

    // display success message
    if (bIn)
    {
        cout << "Data copied into SQL Server " << strColumnType << " column from file '" << strFile << "'." << endl;
    }
    if (bOut)
    {
        cout << "Data copied out of SQL Server " << strColumnType << " column into file '" << strFile << "'." << endl;
    }

    // prepare DB-Library for exit
    Cleanup (pDbproc);

    return (0);
}

///////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION: Cleanup()
//
//      Prepare DB-Library for exit
//
//  PARAMETERS:
//
//      pDbproc - pointer to DBPROCESS connection
//
//  RETURNS: 0
//
//  COMMENTS:
//
///////////////////////////////////////////////////////////////////////////////

int Cleanup (PDBPROCESS pDbproc)
{
    delete [] aBuf;
    dbcancel (pDbproc);
    dbclose (pDbproc);
    return (0);
}

///////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION: ErrorHandler()
//
//      Called when a DB-Library error occurs
//
//  PARAMETERS:
//
//      pDbproc - pointer to DBPROCESS connection
//      nDblibSeverity - DB-Library error severity
//      nDblibErrorNo - DB-Library error number
//      nOSErrorNo - operating system error number
//      lpstrDblibError - DB-Library error string
//      lpstrOSError - operating system error string
//
//  RETURNS: One of three DB-Library return continuation codes:
//
//      INT_CANCEL
//      INT_CONTINUE
//      INT_EXIT
//
//  COMMENTS:
//
///////////////////////////////////////////////////////////////////////////////

extern "C" int ErrorHandler (
    PDBPROCESS pDbproc,
    INT nSeverity,
    INT nDBLibError,
    INT nOSError,
    LPCSTR pszDBLibError,
    LPCSTR pszOSError)
{
    // display DB-Library error information
    cout << "DB-Library Error " << nDBLibError << ": " << pszDBLibError << endl;

    if ((pDbproc == NULL) || (DBDEAD(pDbproc)))
    {
        return(INT_EXIT);
    }
    else
    {
        if (nOSError != DBNOERR)
        {
            // this DB-Library error was caused by an operating system
            // error, so display OS error information
            cout << "Operating System Error " << nOSError << ": " << pszOSError << endl;
        }

        return(INT_CANCEL);
    }
}

///////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION: MessageHandler()
//
//      Called when a SQL Server message is received
//
//  PARAMETERS:
//
//      pDbproc - pointer to DBPROCESS connection
//      lMessage - SQL Server message number
//      nState - SQL Server message state
//      nSeverity - SQL Server message severity
//      pszMessage - SQL Server message string
//      pszServer - the SQL Server that sent this message
//      pszProcedure - the stored procedure (if any) where the message
//                     occurred
//      usLine - the line number (if any) of the batch or stored procedure
//            	 where the message occurred
//
//  RETURNS: 0
//
//  COMMENTS:
//
///////////////////////////////////////////////////////////////////////////////

extern "C" int MessageHandler (
    PDBPROCESS pDbproc,
    DBINT lMessage,
    INT nState,
    INT nSeverity,
    LPCSTR pszMessage,
    LPCSTR pszServer,
    LPCSTR pszProcedure,
    DBUSMALLINT usLine)
{
    // only display certain SQL Serve messages when debug info enabled
    switch (lMessage)
    {
    case 5701:
        if (!bDebug)
        {
            return (0);
        }
        break;
    }

    // display SQL Server message information
    cout << "SQL Server";

    if (pszServer != NULL)
    {
        if (*pszServer != '\0')
        {
            cout << " '" << pszServer << "'";
        }
    }

    cout << " Message " << lMessage << ": " << pszMessage;

    if (usLine != 0)
    {
        cout << " (Concerning line " << usLine;
        if (pszProcedure != NULL)
        {
            cout << " of stored procedure '" << pszProcedure << "'";
        }
        cout << ")";
    }

    cout << endl;

    return(0);
}

///////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION: DisplayUsage()
//
//      Display usage information
//
//  PARAMETERS:
//
//  RETURNS: 0
//
//  COMMENTS:
//
///////////////////////////////////////////////////////////////////////////////

int DisplayUsage (void)
{
    cout << endl;
    cout << "Copies a single text or image value into or out of SQL Server. The value" << endl;
    cout << "is a specified text or image 'column' of a single row (specified by the" << endl;
    cout << "\"where clause\") of the specified 'table'." << endl;
    cout << endl;
    cout << "If the direction is IN (/I) then the data from the specified 'file' is" << endl;
    cout << "copied into SQL Server, replacing the existing text or image value. If the" << endl;
    cout << "direction is OUT (/O) then the text or image value is copied from" << endl;
    cout << "SQL Server into the specified 'file', replacing any existing file." << endl;
    cout << endl;
    cout << "TEXTCOPY [/S [sqlserver]] [/U [login]] [/P [password]]" << endl;
    cout << "  [/D [database]] [/T table] [/C column] [/W\"where clause\"]" << endl;
    cout << "  [/F file] [{/I | /O}] [/K chunksize] [/Z] [/?]" << endl;
    cout << endl;
    cout << "  /S sqlserver       The SQL Server to connect to. If 'sqlserver' is not" << endl;
    cout << "                     specified, the local SQL Server is used." << endl;
    cout << "  /U login           The login to connect with. If 'login' is not specified," << endl;
    cout << "                     a trusted connection will be used." << endl;
    cout << "  /P password        The password for 'login'. If 'password' is not" << endl;
    cout << "                     specified, a NULL password will be used." << endl;
    cout << "  /D database        The database that contains the table with the text or" << endl;
    cout << "                     image data. If 'database' is not specified, the default" << endl;
    cout << "                     database of 'login' is used." << endl;
    cout << "  /T table           The table that contains the text or image value." << endl;
    cout << "  /C column          The text or image column of 'table'." << endl;
    cout << "  /W \"where clause\"  A complete where clause (including the WHERE keyword)" << endl;
    cout << "                     that specifies a single row of 'table'." << endl;
    cout << "  /F file            The file name." << endl;
    cout << "  /I                 Copy text or image value into SQL Server from 'file'." << endl;
    cout << "  /O                 Copy text or image value out of SQL Server into 'file'." << endl;
    cout << "  /K chunksize       Size of the data transfer buffer in bytes. Minimum" << endl;
    cout << "                     value is 1024 bytes, default value is 4096 bytes." << endl;
    cout << "  /Z                 Display debug information while running." << endl;
    cout << "  /?                 Display this usage information and exit." << endl;
    cout << endl;
    cout << "You will be prompted for any required options you did not specify." << endl;

    return (0);
}
