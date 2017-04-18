//****************************** Function Header ******************************
//
// Function : Stats.c
//
// Description:
// 
// This module is used to decode the statistics messages and
// write the results out to the various script files.
// 
// These scrpits can then be run against the server to populate
// the statistics tables.
//
// Author PeterWil 1994, Microsoft Ltd.
//*****************************************************************************

#define DBNTWIN32

// Compiler and SQL header files
#include    <windows.h>
#include    <sqlfront.h>
#include    <sqldb.h>
#include    <srv.h>
#include    <stdio.h>
#include    <stdlib.h>

// Application specific header files
#include    "sqleye.h"
#include    "stats.h" 

// Constants
#define     MAXCHARLEN  255
#define     BUFSIZE     80

extern LOG Log;

// Forward declaration
void WriteStats(DBPROCESS * dbproc, char * FileName, char * Table, char * Output);

//****************************** Function Header ******************************
//
// Function : CatchStats
//
// Description: Trap the messages and record the stats
//
//*****************************************************************************
BOOL CatchStats(DBINT msgno, char * msgtext, DBPROCESS * dbproc, REMOTE_DBMS * remote)
{
    // We do our best to decide whether or not to pass messages back to the client
    //
    // We track whether we think they want them or not.
    // If we've asked for them and we think they haven't then we don't pass them back.
    //
    // But because they can ask for them in a variety of ways then we can't always
    // guarantee to get it right. 
    //
    // Therefore we always assume that IF WE DIDN'T ask for it then THEY DID and pass it through.
    // This can cause a slight glitch when we change the stats options. But it's the best we can
    // really do without implementing a major language parser.

    // If we're logging the statistics to file then we want to process these messages
    // look out for message 3612 Execution Time %d
    // look out for message 3613 Parse and Compile Time %d
    // look out for message 3614 Total writes for this command: %d
    // look out for message 3615 Table: %.*s  scan count %d,  logical reads: %d,  physical reads: %d
    switch (msgno)
    {
        case 3612:
            if ( Log.Statistics_Time )
            {
                ProcessExecStats(dbproc,msgtext);
                // If the client application doesn't want the message then ignore it
                if ( remote->bStatisticsTime == FALSE) return (FALSE);
            }
            break;
        case 3613:
            if ( Log.Statistics_Time ) 
            {
                ProcessPAndCStats(dbproc,msgtext);
                // If the client application doesn't want the message then ignore it
                if ( remote->bStatisticsTime == FALSE) return (FALSE);
            }
            break;
        case 3614:
            if ( Log.Statistics_IO )
            {
                ProcessWriteStats(dbproc,msgtext);
                // If the client application doesn't want the message then ignore it
                if ( remote->bStatisticsIO == FALSE) return (FALSE);
            }
            break;
        case 3615:
            if ( Log.Statistics_IO )
            {
                ProcessReadStats(dbproc,msgtext);
                // If the client application doesn't want the message then ignore it
                if ( remote->bStatisticsIO == FALSE) return (FALSE);
            }
            break;
        case 0:
        {        // Check for SQL Server cpu time:
            if ( Log.Statistics_Time )
            {
                if ( _strnicmp(msgtext,"SQL Server cpu time:",20) == 0)
                {
                    ProcessCPUStats(dbproc,msgtext);
                    // If the client application doesn't want the message then ignore it
                    if ( remote->bStatisticsTime == FALSE) return (FALSE);
                }
                if ( strcmp(msgtext," ") == 0 )
                {
                    // If the client application doesn't want the message then ignore it.
                    if (remote->bStatisticsTime == FALSE) return (FALSE);
                }
            }
            break;
        }
    }
    return (TRUE);
}


//****************************** Function Header ******************************
//
// Function : SwitchStats
//
// Description: Determine what the state of the stats should be
//
//*****************************************************************************
// Switch the stats on or off as necessary
int SwitchStats(REMOTE_DBMS *rmt_dbms, DBPROCESS *rmtproc,char * query)
{
    int         status = SUCCEED;
    
    // Do we need to switch it on ?
    if ( ((rmt_dbms->bStatisticsTime    == TRUE) || (Log.Statistics_Time == TRUE)) &&
          (rmt_dbms->bStatisticsTime_On == FALSE) )
    {
     if ( (status = dbcmd(rmtproc,"set STATISTICS TIME on")) == SUCCEED)
        if ( (status = dbsqlexec(rmtproc)) == SUCCEED)
            if ( (status=dbcancel(rmtproc)) != SUCCEED)
                MessageBox(NULL,"Couldn't cancel results","Error setting STATISTICS TIME on",MB_OK | MB_ICONHAND);
            else
                rmt_dbms->bStatisticsTime_On = TRUE;
    }
    // Do We need to switch it off ?
    if ( status == SUCCEED &&
         ((rmt_dbms->bStatisticsTime    == FALSE) && (Log.Statistics_Time == FALSE)) &&
          (rmt_dbms->bStatisticsTime_On == TRUE) )
    {
     if ( (status = dbcmd(rmtproc,"set STATISTICS TIME off")) == SUCCEED)
        if ( (status = dbsqlexec(rmtproc)) == SUCCEED)
            if ( (status=dbcancel(rmtproc)) != SUCCEED)
                MessageBox(NULL,"Couldn't cancel results","Error setting STATISTICS TIME off",MB_OK | MB_ICONHAND);
            else
                rmt_dbms->bStatisticsTime_On = FALSE;
    }
    // Do we need to switch it on ?
    if ( status == SUCCEED &&
         ((rmt_dbms->bStatisticsIO    == TRUE) || (Log.Statistics_IO == TRUE)) &&
          (rmt_dbms->bStatisticsIO_On == FALSE) )
    {
     if ( (status = dbcmd(rmtproc,"set STATISTICS IO on")) == SUCCEED)
        if ( (status = dbsqlexec(rmtproc)) == SUCCEED)
            if ( (status=dbcancel(rmtproc)) != SUCCEED)
                MessageBox(NULL,"Couldn't cancel results","Error setting STATISTICS IO on",MB_OK | MB_ICONHAND);
            else
                rmt_dbms->bStatisticsIO_On = TRUE;
    }
    // Do We need to switch it off ?
    if ( status == SUCCEED &&
         ((rmt_dbms->bStatisticsIO    == FALSE) && (Log.Statistics_IO == FALSE)) &&
          (rmt_dbms->bStatisticsIO_On == TRUE) )
    {
     if ( (status = dbcmd(rmtproc,"set STATISTICS IO off")) == SUCCEED)
        if ( (status = dbsqlexec(rmtproc)) == SUCCEED)
            if ( (status=dbcancel(rmtproc)) != SUCCEED)
                MessageBox(NULL,"Couldn't cancel results","Error setting STATISTICS IO off",MB_OK | MB_ICONHAND);
            else
                rmt_dbms->bStatisticsIO_On = FALSE;
    }

    // The way we parse things is not very water tight (see below). We could 
    // do a lot better but this section is called every time we receive a  
    // language request so the overhead would be very large.
    // We have writen CatchStats so that if we don't catch the stats ourselves 
    // we are water tight.
    //
    // Therefore for applications that use a different syntax then don't use the
    // stats features or re-write this section.

    // Check if we need to change the STATISTICS IO flag for next time around
    // i.e. has the remote user requested to get this information !!
    // Crude parsing but we'll get by
    if ( _strnicmp(query,"set statistics io on",20) == 0)
    {
        rmt_dbms->bStatisticsIO = TRUE;
        rmt_dbms->bStatisticsIO_On = TRUE;
    }
    if ( _strnicmp(query,"set statistics io off",21) == 0)
    {
        rmt_dbms->bStatisticsIO = FALSE;
        rmt_dbms->bStatisticsIO_On = FALSE;
    }

    // Check if we need to change the STATISTICS TIME flag for next time around
    // i.e. has the remote user requested to get this information !!
    // Crude parsing but we'll get by
    if ( _strnicmp(query,"set statistics time on",22) == 0)
    {
        rmt_dbms->bStatisticsTime = TRUE;
        rmt_dbms->bStatisticsTime_On = TRUE;
    }
    if ( _strnicmp(query,"set statistics time off",23) == 0)
    {
        rmt_dbms->bStatisticsTime = FALSE;
        rmt_dbms->bStatisticsTime_On = FALSE;
    }

    return status;
}

//****************************** Function Header ******************************
//
// Description: Now process the messages
//
//*****************************************************************************

// process message 3615 Table: %.*s  scan count %d,  logical reads: %d,  physical reads: %d
void ProcessReadStats(DBPROCESS * dbproc, char * msgtext)
{
    int nScanCount, nLogicalReads,nPhysicalReads;
    char buffer[BUFSIZE],buffer2[BUFSIZE];

    // parse the message
    sscanf(msgtext,"Table: %s scan count %d,  logical reads: %d,  physical reads: %d",
        buffer,
        &nScanCount,
        &nLogicalReads,
        &nPhysicalReads);
    if ( (nScanCount != 0) || (nLogicalReads != 0) || (nPhysicalReads != 0) )
    {
        // Build the string
        sprintf(buffer2,"'%s',%d,%d,%d",
            buffer,
            nScanCount,
            nLogicalReads,
            nPhysicalReads);
        // Write it out
        WriteStats(dbproc,"sqlreads.sql","sqleye_read_stats",buffer2);
    }
}


// process message 3614 Total writes for this command: %d
void ProcessWriteStats(DBPROCESS * dbproc, char * msgtext)
{
    int nWrites;
    char buffer2[BUFSIZE];

    // parse the message
    sscanf(msgtext,"Total writes for this command: %d",&nWrites);
    if ( nWrites != 0 )
    {
        // Build the string
        sprintf(buffer2,"%d",nWrites);
        // Write it out
        WriteStats(dbproc,"sqlwrite.sql","sqleye_write_stats",buffer2);
    }
}

// process message 3612 Execution Time %d    
void ProcessExecStats(DBPROCESS * dbproc, char * msgtext)
{
    int nExecTime;
    char buffer2[BUFSIZE];

    // parse the message
    sscanf(msgtext,"Execution Time %d",&nExecTime);
    if ( nExecTime != 0 )
    {
        // Build the string
        sprintf(buffer2,"%d",nExecTime);
        // Write it out
        WriteStats(dbproc,"sqlexect.sql","sqleye_exec_stats",buffer2);
    }
}

// process message 3613 Parse and Compile Time %d
void ProcessPAndCStats(DBPROCESS * dbproc, char * msgtext)
{
    int nPAndCTime;
    char buffer2[BUFSIZE];

    // parse the message
    sscanf(msgtext,"Parse and Compile Time %d",&nPAndCTime);
    if ( nPAndCTime != 0 )
    {
        // Build the string
        sprintf(buffer2,"%d",nPAndCTime);
        // Write it out
        WriteStats(dbproc,"sqlpandc.sql","sqleye_pandc_stats",buffer2);
    }
}

// process either of
// SQL Server cpu time: %d ms.  SQL Server elapsed time: %d ms.
// SQL Server cpu time: %d ms.
void ProcessCPUStats(DBPROCESS * dbproc, char * msgtext)
{
    int nCPUTime=0,nElapsedTime=0;
    char buffer2[BUFSIZE];

    // parse the message
    if (sscanf(msgtext,"SQL Server cpu time: %d ms.  SQL Server elapsed time: %d ms.",&nCPUTime,&nElapsedTime) < 2)
        nElapsedTime = 0;
    if ( (nCPUTime != 0) || (nElapsedTime != 0) )
    {
        // Build the string
        sprintf(buffer2,"%d,%d",nCPUTime,nElapsedTime);
        // Write it out
        WriteStats(dbproc,"sqlcpu.sql","sqleye_cpu_stats",buffer2);
    }
}

// Write out the information to file
void WriteStats(DBPROCESS * dbproc, char * pszFileName, char * pszTable, char * pszOutput)
{
    FILE        *fOutput;
    SRV_PROC    *srvproc;
    char        QueryStart[MAXCHARLEN+1];
    int         nCounter;
    char        *pszMsg;

    // Find out who they are
    srvproc = (SRV_PROC *)dbgetuserdata(dbproc);

    // Get the first part of the query
    strncpy(QueryStart,srv_langptr(srvproc),MAXCHARLEN);
    QueryStart[MAXCHARLEN] = '\0';
    // make sure there are no ' in the string
    for ( nCounter=0; nCounter<MAXCHARLEN; nCounter++)
        if ( QueryStart[nCounter] == '\'' ) QueryStart[nCounter] = '"';

    // Open the file to append
    if (fOutput = fopen(pszFileName,"a"))
    {
       fprintf(fOutput,
          "insert %s values ('%s','%s','%s',%s,'%s')\ngo\n",
          pszTable,
          srv_pfield(srvproc,SRV_APPLNAME,NULL),
          srv_pfield(srvproc,SRV_USER,NULL),
          srv_pfield(srvproc,SRV_HOST,NULL),
          pszOutput,
          QueryStart);
       fclose(fOutput);
    } else {
        pszMsg = (char *)malloc(
            strlen("Unable to open file ") +
            strlen(pszFileName) + 1);
        sprintf(pszMsg,"Unable to open file %s",pszFileName);
        srv_log(SRV_GETSERVER((SRV_PROC *)dbgetuserdata(dbproc)), Log.FILE_Timing, pszMsg, SRV_NULLTERM);
        free(pszMsg);
    }
}
