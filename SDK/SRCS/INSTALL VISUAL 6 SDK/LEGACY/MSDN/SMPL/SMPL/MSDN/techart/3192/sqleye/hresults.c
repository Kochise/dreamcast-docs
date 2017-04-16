//****************************** Function Header ******************************
//
// Function : HandleResults
//
// Description: Pass back results to client and log in MDI client
//      windows and/or log file
//
// Author PeterWil 1994, Microsoft Ltd.
//*****************************************************************************
#define DBNTWIN32

// standard compiler/sql server supplied header files
#include    <windows.h>
#include    <sqlfront.h>
#include    <sqldb.h>
#include    <srv.h>
#include    <stdio.h>
#include    <stdlib.h>

// Application specific header files
#include    "sqleye.h"
#include    "hresults.h"
#include    "rowstuff.h"
#include    "sqlcbs.h"

#define     ROWSZ   25

extern LOG Log;

int dbcolntype(DBPROCESS *, int);

#pragma check_stack( off )  // turn off stack checking

int HandleResults(DBPROCESS  *rmtproc, SRV_PROC  *srvproc)
{
    int         cols;
    int         iColumnCounter, iDataCounter, iOldIconType;
    DBINT       rows = 0L;
    BOOL        results_sent = FALSE;
    BOOL        gotcompute = FALSE;
    int         (*paramarray)[MAXPARAMS];
    RETCODE     returnvalue;
    REMOTE_DBMS *remote;
    char        szRows[ROWSZ+1];

    paramarray = (int (*)[MAXPARAMS])&(((REMOTE_DBMS *)srv_getuserdata(srvproc))->retparams);
    remote  = (REMOTE_DBMS *)srv_getuserdata(srvproc);
                                                         
    // store the old icon, then use the out icon
    if (Log.MDI) iOldIconType = ChangeIcon(remote->hMDI,   IDM_OUT_ICON);

    // Process the results from the remote DBMS.
    // Since a command may consist of multiple commands or a single
    // command that has multiple sets of results, we'll loop through
    // each results set.
    while (TRUE)
    {
        returnvalue = dbresults(rmtproc);
        if (returnvalue == NO_MORE_RESULTS)
            break;

        // Check to see if the client has sent an attention event.  If
        // so, simply discard data from remote server
        if (SRV_GOT_ATTENTION(srvproc))
        {
            dbcancel(rmtproc);
            continue;
        }

        // If this is the second time through the loop,
        // send a completion message to the client
        // for the previous results sent.
        if (results_sent == TRUE)
        {
            // If there are some COMPUTE rows, send a message
            // to the client that Data Services Library doesn't yet handle them.
            if (gotcompute == TRUE)
            {
                gotcompute = FALSE;
                srv_sendmsg(srvproc,
                    SRV_MSG_ERROR,
                    (DBINT)COMPUTE_ROW,
                    (DBTINYINT)0,
                    (DBTINYINT)0,
                    NULL,
                    0,
                    0,
                    "Data Services library can't handle COMPUTE rows.",
                    SRV_NULLTERM);
            }
            // If the previous batch was one that may
            // have returned rows, set the DONE status
            // accordingly.
            if (rows > 0)
            {
                srv_senddone(srvproc, SRV_DONE_MORE | SRV_DONE_COUNT,
                    (DBUSMALLINT)0, rows);
            } else
                srv_senddone(srvproc, SRV_DONE_MORE, (DBUSMALLINT)0,
                    (DBINT)0);
        }

        // How many data columns are in the row?
        // Non-"select" statements will have 0 columns.
        cols = dbnumcols(rmtproc);
    
        // Build the row description for the client return.
        for (iColumnCounter = 1; iColumnCounter <= cols; iColumnCounter++)
        {
            // Call "srv_describe()" for each column in the row.
            srv_describe(srvproc,
                iColumnCounter,
                dbcolname(rmtproc, iColumnCounter),
                SRV_NULLTERM,
                (DBINT)dbcolntype(rmtproc, iColumnCounter),
                dbcollen(rmtproc, iColumnCounter),
                (DBINT)dbcolntype(rmtproc, iColumnCounter),
                dbcollen(rmtproc, iColumnCounter),
                (BYTE *)NULL);
        }

        if (Log.MDI_Result)
        {
            AddRow(remote->hMDI, " ", colorBlack);
            AddRow(remote->hMDI, "Result Set: ", colorBlue);
            AddHeader(remote->hMDI, rmtproc, colorRed);
        }

        if (Log.FILE_Result)
        {
            char *pszHeader=NULL,*pszAll=NULL;
            //Make the header
            ConstructHeader(rmtproc, &pszHeader, "");
            // Allocate space for the whole lot
            pszAll = malloc( strlen(pszHeader) + 31 );
            // Make the whole lot
            sprintf(pszAll,
                "ResultHdr: Client Id: %s - %s",
                srv_pfield(srvproc, SRV_SPID, (int *)NULL),
                pszHeader);
            // Write it to disk
            srv_log(SRV_GETSERVER(srvproc), Log.FILE_Timing, pszAll, SRV_NULLTERM);
            // free the memory
            free(pszHeader);
            free(pszAll);
        }

        // Send each row from the remote DBMS to the client.
        rows = 0;
        while (TRUE)
        {
            returnvalue = dbnextrow(rmtproc);
            if (returnvalue == NO_MORE_ROWS)
                break;
            // Check to see if the client has issued an attention event.
            // If so, discard data from the remote server.
            if (SRV_GOT_ATTENTION(srvproc))
            {
                dbcancel(rmtproc);
                continue;
            }

            // If it's not a regular row, it's a COMPUTE row.
            // This SQL extension is particular to Sybase
            // TRANSACT-SQL and is not yet supported.
            if (DBROWTYPE(rmtproc) != REG_ROW)
            {
                gotcompute = TRUE;
                continue;
            }  else
                gotcompute = FALSE;
            // Move the rows from the remote server to the client.
            for (iColumnCounter = 1; iColumnCounter <= cols; iColumnCounter++)
            {
                srv_setcollen(srvproc, iColumnCounter, dbdatlen(rmtproc, iColumnCounter));
                srv_setcoldata(srvproc, iColumnCounter, dbdata(rmtproc, iColumnCounter));
            }

            // Display results on the screen
            if (Log.MDI_Result)
            {
                AddResultRow(remote->hMDI, rmtproc, colorBlack);
            } 

            // Log the results to file
            if (Log.FILE_Result)
            {
                char *pszRow=NULL,*pszAll=NULL;
                //Make the row
                ConstructRow(rmtproc, &pszRow, "");
                // Allocate space for the whole lot
                pszAll = malloc( strlen(pszRow) + 31 );
                // Make the whole lot
                sprintf(
                    pszAll,
                    "Results  : Client Id: %s - %s",
                    srv_pfield(srvproc, SRV_SPID, (int *)NULL),
                    pszRow );
                // Write it to disk
                srv_log(SRV_GETSERVER(srvproc), Log.FILE_Timing, pszAll, SRV_NULLTERM);
                // free the memory
                free(pszRow);
                free(pszAll);
            }
            // Send result row to client and increment counter
            if (srv_sendrow(srvproc) == SUCCEED)
                rows++;
        }

        // Check to see if any parameter were returned from
        // the remote DBMS.  If so, pass them through to the
        // client.
        for (iDataCounter = 1; iDataCounter <= dbnumrets(rmtproc); iDataCounter++)
        {
            // If the return parameters are a result of
            // an rpc, we used srv_paramset() to set the return
            // value.  If the return parameters are not the
            // result of an rpc, we use srv_returnval().
            if (srv_rpcname(srvproc, NULL) != NULL) {
                // The current rpc may have three parameters, but
                // only the first and third are return parameters.
                // This means that dbnumrets() returns two parameters,
                // not three.  The first call to dbretdata() refers to
                // the rpc's first parameter, and the second call to
                // dbretdata() refers to the rpc's third parameter.
                // To handle this, we map each return parameter to
                // its original parameter so we can later reset the
                // return value of the correct return parameters in
                // HandleResults().
                srv_paramset(srvproc, (*paramarray)[iDataCounter], dbretdata(rmtproc, iDataCounter),
                dbretlen(rmtproc, iDataCounter));
            } else {
                srv_returnval(srvproc,
                    dbretname(rmtproc, iDataCounter),
                    SRV_NULLTERM,
                    SRV_PARAMRETURN,
                    dbrettype(rmtproc, iDataCounter),
                    dbretlen(rmtproc, iDataCounter),
                    dbretlen(rmtproc, iDataCounter),
                    dbretdata(rmtproc, iDataCounter));
            }
        }
        // Check to see if we got a return status code from the
        // remote DBMS.  Pass it through to the client.
        if (dbhasretstat(rmtproc))
            srv_sendstatus(srvproc, dbretstatus(rmtproc));

        // If the command was one where count is meaningful,
        // DBCOUNT() will be >=0, set rows accordingly.
        if (dbnumcols(rmtproc) > 0)
            rows = DBCOUNT(rmtproc) < 0L ? 0L : rows;
        else
            rows = DBCOUNT(rmtproc);

        // Set flag so that we will send a completion
        // message for the current set of results.
        results_sent = TRUE;

         // Display the number of rows sent
        sprintf(szRows,"%i rows returned",rows);
        if (Log.MDI_RowCount) AddRow(remote->hMDI  , szRows ,colorGreen);
        if (Log.FILE_RowCount)
        {   
            char szLogRows[ROWSZ+31+1];
            // Make the whole lot
            sprintf(szLogRows,
                "Rowcount : Client Id: %s - %s",
                srv_pfield(srvproc, SRV_SPID, (int *)NULL),
                szRows);
            // Write it to disk
            srv_log(SRV_GETSERVER(srvproc), Log.FILE_Timing, szLogRows, SRV_NULLTERM);
        }
    }
    
    // If there are some COMPUTE rows, send a message
    // to the client that Open Services Library doesn't handle them yet.
    if (gotcompute == TRUE)
    {
        gotcompute = FALSE;
        srv_sendmsg(srvproc,
            SRV_MSG_ERROR,
            (DBINT)COMPUTE_ROW,
            (DBTINYINT)0,
            (DBTINYINT)0,
            NULL,
            0,
            0,
            "Data Services Library can't yet handle COMPUTE rows.",
            SRV_NULLTERM);
    }

    // Send the final done packet for the execution of the command batch.
    // If the previous batch was one that may
    // have returned rows, set the DONE status
    // accordingly.
    if (rows > 0)
    {
        srv_senddone(srvproc,
            SRV_DONE_COUNT | SRV_DONE_FINAL,
            (DBUSMALLINT)0,
            rows);
    } else {
        srv_senddone(srvproc,
            SRV_DONE_FINAL,
            (DBUSMALLINT)0,
            (DBINT)0);
    }

    // reset the icon
    if (Log.MDI)     ChangeIcon(remote->hMDI,   iOldIconType);

    return(SUCCEED);
}

#pragma check_stack()   // set stack checking to its default setting
