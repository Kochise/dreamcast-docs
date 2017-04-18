//****************************** Function Header ******************************
//
// Function : RPCExecute
//
// Description: Send RPC to SQL Server
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
#include    "rpcexec.h"
#include    "hresults.h"
#include    "rowstuff.h"
#include    "sqlcbs.h"

extern LOG Log;

#pragma check_stack( off )  // turn off stack checking

int RPCExecute(SRV_PROC  *srvproc)
{
    DBPROCESS  *rmtproc;
    REMOTE_DBMS  *rmt_dbms;
    int iParamCount;
    int len = 0,symbol_len=0;
    int params;
    int retparam;
    int  (*paramarray)[MAXPARAMS];
    int iOldIconType;
    int status = SUCCEED;
    char *pszScreen;
    char *pszValue;
    char *pszSymbol;
    RETCODE ret;
    DBINT param1 = 1;
    DBCHAR * paramname;
    char *plog_buffer;
    // file handle for building the scripts
    FILE *fOutput = NULL;

    // Get the remote dbms pointer we saved in the srvproc via
    // srv_setuserdata.
    rmt_dbms = (REMOTE_DBMS *)srv_getuserdata(srvproc);

    // Set up the icon for RPC
    if (Log.MDI) iOldIconType = ChangeIcon(rmt_dbms->hMDI  , IDM_RPC_ICON);

    // get the dbproc and the number of parameters
    rmtproc = ((REMOTE_DBMS *)srv_getuserdata(srvproc))->dbproc;
    paramarray = (int (*)[MAXPARAMS])&(((REMOTE_DBMS *)srv_getuserdata(srvproc))->retparams);

    // Get the RPC name and initialize the RPC to the remote DBMS.
    dbrpcinit(rmtproc, srv_rpcname(srvproc, (int *)NULL),
        (DBUSMALLINT)srv_rpcoptions(srvproc));

    // display it on the screen
    if (Log.MDI_Query || Log.FILE_Query)
    {
        pszScreen = (char *)malloc(
            strlen("dbrpcinit(RPCName=, Options=)") +
            strlen(srv_rpcname(srvproc, (int *)NULL)) + 11);
        sprintf(pszScreen,"dbrpcinit(RPCName=%s, Options=%d)",
            srv_rpcname(srvproc, (int *)NULL),
            (int)srv_rpcoptions(srvproc) );

        if (Log.MDI_Query)
            {
            AddRow(rmt_dbms->hMDI," ",colorBlue);
            AddRow(rmt_dbms->hMDI,"RPC",colorBlue);
            AddRow(rmt_dbms->hMDI,pszScreen,colorBlack);
            }

        // Update the log if necessary
        if (Log.FILE_Query)
        {
            plog_buffer = (char *) malloc(
                strlen("==>   RPC: Client Id:  - ") +
                strlen(srv_pfield(srvproc, SRV_SPID, (int *)NULL)) +
                strlen(pszScreen) + 1);
            sprintf(
                plog_buffer,
                "==>   RPC: Client Id: %s - %s",
                srv_pfield(srvproc, SRV_SPID, (int *)NULL),
                pszScreen );
            srv_log(SRV_GETSERVER(srvproc), Log.FILE_Timing, plog_buffer, SRV_NULLTERM);
            free(plog_buffer);
        }
        free(pszScreen);
    }
    // Build the scripts
    if (Log.Build_Scripts)
    {
        char szFileName[15];
        char * pszMsg;

        sprintf(szFileName,"%s.sql",srv_pfield(srvproc,SRV_SPID,NULL));
        if (fOutput = fopen(szFileName,"a"))
        {
            fprintf(fOutput,"execute %s ",srv_rpcname(srvproc, (int *)NULL));
        } else {
            pszMsg = (char *)malloc(
                strlen("Unable to open file ") +
                strlen(szFileName) + 1);
            sprintf(pszMsg,"Unable to open file %s",szFileName);
            srv_log(SRV_GETSERVER((SRV_PROC *)dbgetuserdata(rmtproc)), Log.FILE_Timing, pszMsg, SRV_NULLTERM);
            free(pszMsg);
        }

    }

    // Set up any RPC parameters.
    params = srv_rpcparams(srvproc);
    retparam = 1;


    for (iParamCount = 1; iParamCount <= params; iParamCount++)
    {
        paramname = srv_paramname(srvproc, iParamCount, &len);

        // screen and log display
        if (Log.MDI_Query || Log.FILE_Query || fOutput )
        {              
            // Find the value
            if (srv_paramlen(srvproc, iParamCount) == 0)
            {
                pszValue = (char *)malloc(strlen("NULL")+1);
                strcpy(pszValue,"NULL");
            } else {
                pszValue = (char *)malloc(GetConvertedLength(
                        srv_paramtype(srvproc, iParamCount),
                        srv_paramlen(srvproc, iParamCount),
                        rmtproc ) + 1 );
                srv_convert(
                    srvproc,
                    srv_paramtype(srvproc, iParamCount),
                    srv_paramdata(srvproc, iParamCount),
                    srv_paramlen(srvproc, iParamCount),
                    SQLCHAR,
                    pszValue,
                    -1);
            }

            // if we're building a script
            if (fOutput)
            {
                if (iParamCount > 1)
                    fprintf(fOutput,",");
                if (len > 0)
                    fprintf(fOutput,"%s=",paramname);
                if (srv_paramlen(srvproc,iParamCount) == 0)
                    fprintf(fOutput,"NULL");
                else
                    fprintf(fOutput,"\"%s\"",pszValue);
            }

            // Build the string

            // First get the symbol and massage it
            pszSymbol = srv_symbol(SRV_DATATYPE,srv_paramtype(srvproc, iParamCount),&symbol_len);
            // This function actually tends to return a string terminated
            // with \r\n, rather than just null term.
            if  (*(pszSymbol+symbol_len-2) == '\r') *(pszSymbol+symbol_len-2) = '\0';
            if  (*(pszSymbol+symbol_len-1) == '\n') *(pszSymbol+symbol_len-1) = '\0';

            pszScreen = (char *)malloc(
                strlen("dbrpcparam Paramname=, status=, type=, maxlen=, datalen=, value=") +
                strlen(srv_paramname(srvproc, iParamCount, (int *)NULL)) +
                strlen(pszSymbol) +
                strlen(pszValue) + 31);
            sprintf(pszScreen,
                "dbrpcparam Paramname=%s, status=%d, type=%s, maxlen=%d, datalen=%d, value=%s",
                srv_paramname(srvproc, iParamCount, (int *)NULL) ,
                srv_paramstatus(srvproc, iParamCount),
                pszSymbol,
                srv_parammaxlen(srvproc, iParamCount),
                srv_paramlen(srvproc, iParamCount), 
                pszValue );
            // Now finished with pszValue
            free(pszValue);
            // We also need to manualy free the memory that srv_symbol allocates
            LocalFree(pszSymbol);

            // screen
            if (Log.MDI_Query)
            {
                AddRow(rmt_dbms->hMDI,pszScreen,colorBlack);
            }

            // log file
            if (Log.FILE_Query)
            {
                plog_buffer = (char *)malloc(
                    strlen("RPC Param: Client Id: %s - %s") +
                    strlen(srv_pfield(srvproc, SRV_SPID, (int *)NULL)) +
                    strlen(pszScreen) + 1) ;
                sprintf(
                    plog_buffer,
                    "RPC Param: Client Id: %s - %s",
                    srv_pfield(srvproc, SRV_SPID, (int *)NULL),
                    pszScreen );
                srv_log(SRV_GETSERVER(srvproc), Log.FILE_Timing, plog_buffer, SRV_NULLTERM);
                free(plog_buffer);
            }
            free(pszScreen);
        }


        // Send the parameter to SQL Server
        // Earlier on we used srv_paramname to get the name of the parameter.
        // If no name is specified then it returns a pointer to a NULL string.
        // If there is no parameter name then dbrpcparam requires a NULL pointer
        // NOT a pointer to a NULL string. Therefore if name of  length 0 then 
        // we make it a NULL pointer.
        if (len == 0) paramname = NULL;
        ret = dbrpcparam(
            rmtproc,
            paramname,
            (BYTE)srv_paramstatus(srvproc, iParamCount),
            srv_paramtype(srvproc, iParamCount),
            srv_parammaxlen(srvproc, iParamCount),
            srv_paramlen(srvproc, iParamCount),
            srv_paramdata(srvproc, iParamCount));
        
        // The current rpc may have three parameters, but only the
        // first and third are return parameters.  This means that
        // dbnumrets() returns two parameters, not three.  The first
        // call to dbretdata() referes to the rpc's first parameter,
        // and the second call to dbretdata() refers to the rpc's
        // third parameter.  To handle this, we map each return
        // parameter to its original parameter so we can later
        // reset the return value of the correct return parameters
        // in "HandleResults()".
        if ((BYTE)srv_paramstatus(srvproc, iParamCount) & SRV_PARAMRETURN)
        {
            (*paramarray)[retparam] = iParamCount;
            retparam++;

            // if we're building a script
            if (fOutput) fprintf(fOutput," output");
        }
    }

    // close the script file (can't use the global flag as it may have changed)
    if (fOutput)
    {
        fprintf(fOutput,"\ngo\n");
        fclose(fOutput);
    }

    // Send the RPC to the remote DBMS.
    status = dbrpcsend(rmtproc);

    if (status == SUCCEED)
    {
        // use the waiting icon
        if (Log.MDI) ChangeIcon(rmt_dbms->hMDI  , IDM_ACTIVE_ICON);
        status = dbsqlok(rmtproc);
    }

    // if the user hasn't issued a dbcancel and the call succeded
    if (!SRV_GOT_ATTENTION(srvproc) && (status == SUCCEED))
    {
        // Now get the remote DBMS results and pass them back to
        // Open Server client.
        HandleResults(rmtproc, srvproc);
    } else {
        if (DBDEAD(rmtproc))
        {
            // Let them know it failed
            // they're one loop behind 
            srv_sendmsg(
                srvproc,
                SRV_MSG_ERROR,
                (DBINT)10025,
                (DBTINYINT)9,
                (DBTINYINT)0,
                NULL,
                0,
                0,
                "Possible network error: Write to SQL Server failed.",
                SRV_NULLTERM);
            // try this
            dbclose(rmtproc);
            rmt_dbms->dbproc = NULL;
            srv_senddone(srvproc, SRV_DONE_ERROR, (DBUSMALLINT)0, (DBINT)0);
            srv_event(srvproc, SRV_DISCONNECT, NULL);
            return(SRV_DISCONNECT);
        } else {
            dbcancel(rmtproc);
            srv_senddone(srvproc, SRV_DONE_FINAL, (DBUSMALLINT)0, (DBINT)0);
        }
    }
    // use the original icon
    if (Log.MDI)     ChangeIcon(rmt_dbms->hMDI  , iOldIconType);

    return(SRV_CONTINUE);
}                              

#pragma check_stack()   // set stack checking to its default setting

