//****************************** Function Header ******************************
//
// Module : Rowstuff
//
// Description: Assorted row routines
//
// Author PeterWil 1994, Microsoft Ltd.
//*****************************************************************************
#define DBNTWIN32

// standard compiler/sql server supplied header files
#include    <windows.h>
#include    <sqlfront.h>
#include    <sqldb.h>
#include    <stdio.h>
#include    <srv.h>
#include    <stdlib.h>

// Application specific header files
#include    "sqleye.h"
#include    "rowstuff.h"

extern BOOL bAutoScroll; 
extern LOG  Log;      

#define TIMESIZE 14  

#pragma check_stack( off )  // turn off stack checking

//****************************** Function Header ******************************
//
// Function : Get Time
//
// Description: Get time info if necessary
//
//*****************************************************************************
void GetMDITime(char szTheTime[TIMESIZE])
{
    SYSTEMTIME  stTime;

    // Do we need the timings ?
    if ( Log.MDI_Timing)
    {
        GetLocalTime(&stTime);
        sprintf(
            szTheTime,
            "%2u:%2u:%2u.%3u ",
            stTime.wHour,
            stTime.wMinute,
            stTime.wSecond,
            stTime.wMilliseconds
            );
    } else strcpy(szTheTime,"");
}


//****************************** Function Header ******************************
//
// Function : CheckBuffers
//
// Description: Check if the buffers need to be cleared and clear if necessary
//
//*****************************************************************************
BOOL CheckBuffers(PCLIENTINFO pInfo)
{
    if ( (pInfo->iCurrentRow >= (MAX_ROWS-1)) || (pInfo->bClearBuf == TRUE) )
        return ClearBuffers(pInfo);
    else
        return TRUE;
}

//****************************** Function Header ******************************
//
// Function : ClearBuffers
//
// Description: Clear the buffers 
//
//*****************************************************************************
BOOL ClearBuffers(PCLIENTINFO pInfo)
{
    int iCounter;

    pInfo->iCurrentRow = 0;
    pInfo->bClearBuf = FALSE;
    for (iCounter=0; iCounter < MAX_ROWS; iCounter++)
    {
        free(pInfo->pszRow[iCounter]);
        pInfo->pszRow[iCounter] = NULL;
        pInfo->color[iCounter] = 0;
    }
    InvalidateRect(pInfo->hwnd, NULL, TRUE);
    return TRUE;
}

//****************************** Function Header ******************************
//
// Function : AddRow
//
// Description: Adds a row to the display buffer
//
//*****************************************************************************
BOOL AddRow(HANDLE hInfo, char *szBuf, COLORREF color)
{
    PCLIENTINFO pInfo;
    CHAR        szTheTime[TIMESIZE];

    if (!hInfo) return FALSE;

    pInfo = LocalLock(hInfo);

    if (pInfo == NULL) return FALSE;

    CheckBuffers(pInfo);

    GetMDITime(szTheTime);

    if ((pInfo->pszRow[pInfo->iCurrentRow] = malloc(strlen(szTheTime)+strlen(szBuf)+1))!= NULL)
    {
        pInfo->color[pInfo->iCurrentRow] = color;
        sprintf(pInfo->pszRow[pInfo->iCurrentRow++],"%s%s",szTheTime,szBuf);

        pInfo->iMaxHorRow = max(pInfo->iMaxHorRow, (int)strlen(szBuf));
        pInfo->iMaxHScrollPos = max(0,pInfo->iMaxHorRow -pInfo->iDisplayedHRows);
        SetScrollRange(pInfo->hwnd, SB_HORZ, 0, pInfo->iMaxHScrollPos, TRUE);
    } else {
        // We couldn't allocate memory, WM_PAINT will pick this up and display 
        // the necessary message instead of the row
        pInfo->color[pInfo->iCurrentRow++] = colorRed;
    }

    // if it's in the display window (not minimised) then invalidate the rectangle
    if ( ( (pInfo->iCurrentRow < pInfo->iVScrollPos + pInfo->iDisplayedVRows) ) &&
         !IsIconic(pInfo->hwnd) ) InvalidateRect(pInfo->hwnd, NULL, FALSE);

    // set the vertical scroll stuff        
    pInfo->iMaxVScrollPos = max(0,pInfo->iCurrentRow - pInfo->iDisplayedVRows);
    SetScrollRange(pInfo->hwnd, SB_VERT, 0, pInfo->iMaxVScrollPos, TRUE);

    // Autoscroll if necessary
    if (bAutoScroll && (pInfo->iVScrollPos < pInfo->iMaxVScrollPos) )
    {
        PostMessage(pInfo->hwnd,WM_VSCROLL,SB_BOTTOM,0L);
    }

    LocalUnlock(hInfo);
    return TRUE;
}

//****************************** Function Header ******************************
//
// Function : AddHeader
//
// Description: Adds a query header to the display buffer
//
//*****************************************************************************
BOOL AddHeader(HANDLE hInfo, DBPROCESS *dbproc, COLORREF color)
{
    PCLIENTINFO pInfo;
    CHAR  szTheTime[TIMESIZE];

    if (!hInfo) return FALSE;

    pInfo = LocalLock(hInfo);

    if (pInfo == NULL) return FALSE;

    CheckBuffers(pInfo);

    // Get the time
    GetMDITime(szTheTime);

    if (ConstructHeader(dbproc, &pInfo->pszRow[pInfo->iCurrentRow],szTheTime)==FAIL)
    {
        // WM_PAINT will pick this up
        pInfo->pszRow[pInfo->iCurrentRow] = NULL;
    }

    pInfo->iMaxHorRow = max(pInfo->iMaxHorRow,
                            (int)strlen(pInfo->pszRow[pInfo->iCurrentRow]));

    pInfo->color[pInfo->iCurrentRow++] = color;

    // if it's in the display window (not minimised) then invalidate the rectangle
    if ( ( (pInfo->iCurrentRow < pInfo->iVScrollPos + pInfo->iDisplayedVRows) ) &&
         !IsIconic(pInfo->hwnd) ) InvalidateRect(pInfo->hwnd, NULL, FALSE);

    // Set the vertical scroll stuff    
    pInfo->iMaxVScrollPos = max(0,pInfo->iCurrentRow - pInfo->iDisplayedVRows);
    SetScrollRange(pInfo->hwnd, SB_VERT, 0, pInfo->iMaxVScrollPos, TRUE);

    // Autoscroll if necessary
    if (bAutoScroll && (pInfo->iVScrollPos < pInfo->iMaxVScrollPos) )
        PostMessage(pInfo->hwnd,WM_VSCROLL,SB_BOTTOM,0L);
    
    LocalUnlock(hInfo);
    return TRUE;
}

//****************************** Function Header ******************************
//
// Function : AddResultRow
//
// Description: Adds a query result row to the display buffer
//
//*****************************************************************************
BOOL AddResultRow(HANDLE hInfo, DBPROCESS *dbproc, COLORREF color)
{
    PCLIENTINFO pInfo;
    CHAR  szTheTime[TIMESIZE];

    if (!hInfo) return FALSE;

    pInfo = LocalLock(hInfo);

    if (pInfo == NULL) return FALSE;

    CheckBuffers(pInfo);

    // Get the time
    GetMDITime(szTheTime);

    if (ConstructRow(dbproc, &pInfo->pszRow[pInfo->iCurrentRow],szTheTime) == FAIL)
    {
        // WM_PAINT will pick this up
        pInfo->pszRow[pInfo->iCurrentRow] = NULL;
    }

    pInfo->iMaxHorRow = max(pInfo->iMaxHorRow,
                            (int)strlen(pInfo->pszRow[pInfo->iCurrentRow]));
    
    pInfo->color[pInfo->iCurrentRow++] = color;

    // set the vertical scroll stuff
    pInfo->iMaxVScrollPos = max(0,pInfo->iCurrentRow - pInfo->iDisplayedVRows);
    SetScrollRange(pInfo->hwnd, SB_VERT, 0, pInfo->iMaxVScrollPos, TRUE);

    // set the horizontal scroll stuff
    pInfo->iMaxHScrollPos = max(0,pInfo->iMaxHorRow -pInfo->iDisplayedHRows);
    SetScrollRange(pInfo->hwnd, SB_HORZ, 0, pInfo->iMaxHScrollPos, TRUE);

    // if it's in the display window (not minimised) then invalidate the rectangle
    if ( ( (pInfo->iCurrentRow < pInfo->iVScrollPos + pInfo->iDisplayedVRows) ) &&
         !IsIconic(pInfo->hwnd) ) InvalidateRect(pInfo->hwnd, NULL, FALSE);

    // Autoscroll if necessary
    if (bAutoScroll && (pInfo->iVScrollPos < pInfo->iMaxVScrollPos) )
        PostMessage(pInfo->hwnd,WM_VSCROLL,SB_BOTTOM,0L);

    LocalUnlock(hInfo);

    return 1;
}

//****************************** Function Header ******************************
//
// Function : ConstructHeader
//
// Description: Builds result header
//
//*****************************************************************************
RETCODE ConstructHeader(DBPROCESS *dbproc, LPSTR *pszHeader,char * szTheTime)
{
    int   iCols,iSize, iTabs;
    LPSTR pszColName;
    LPSTR pszPtr;
    DBINT i;

    // Get number of columns so we now how much memory to allow for tabs
    iTabs = dbnumcols(dbproc);

    // Get row size and allocate memory for buffer
    iSize = strlen(szTheTime)+ DetermineRowSize(dbproc,0);

    if (*pszHeader != NULL)
        free(*pszHeader);

    *pszHeader = malloc ((DWORD) (iSize + iTabs + 1));
    if(*pszHeader != NULL)
        pszPtr = *pszHeader;
    else
    {
        ERRBOX("ConstructHeader: malloc failed");
        return(FAIL);
    }

    // Initialize buffer to spaces
    memset (pszPtr,' ',iSize);
    // Place the time in the buffer and move the pointer forward
    strcpy (pszPtr,szTheTime);
    pszPtr += strlen(szTheTime);

    // Get number of columns
    iCols = dbnumcols(dbproc);

    // Loop on all columns, retrieving column size and name, and adding
    // to buffer, spaced with tabs (\t)
    for(i=1; i <= iCols; i++)
    {
        iSize = DetermineRowSize(dbproc,i);
        pszColName = dbcolname(dbproc,i);
        strncpy(pszPtr,pszColName,strlen(pszColName));
        pszPtr+= iSize;
        strncpy(pszPtr, (LPSTR) "\t",1);
        pszPtr += 1;
    }

    // Finished: null terminate buffer and return SUCCEED
    *pszPtr = '\0';

    return(SUCCEED);
}


//****************************** Function Header ******************************
//
// Function : ConstructRow
//
// Description: Builds row for query result set
//
//*****************************************************************************
RETCODE ConstructRow(DBPROCESS *dbproc, LPSTR *pszDataVals, char * szTheTime)
{
    int   i, iCols, iSize, iDatasize, iTabs;
    LPSTR pszData;
    LPSTR pszPtr;

    // Get number of columns so we now how much memory to alloc for tabs
    iTabs = dbnumcols(dbproc);

    // Get row size and allocate memory for buffer
    iSize = strlen(szTheTime)+ DetermineRowSize(dbproc,0);

    if (*pszDataVals != NULL)
        free(*pszDataVals);
    *pszDataVals = malloc((DWORD) (iSize + iTabs + 1));
    if(*pszDataVals != NULL)
        pszPtr = *pszDataVals;
    else
    {
        ERRBOX("ConstructRow: malloc failed");
        return(FAIL);
    }

    // Place the time in the buffer and move the pointer forward
    strcpy (pszPtr,szTheTime);
    pszPtr += strlen(szTheTime);

    // Get number of columns
    iCols = dbnumcols(dbproc);

    // Loop through all columns, initialize to spaces and then
    // retrieve values
    for(i=1;i<=iCols;i++)
    {
        iSize = DetermineRowSize(dbproc,i);
        memset(pszPtr,' ',iSize);
        pszData = dbdata(dbproc,i);
        if(pszData == (BYTE *)NULL) // if NULL, use "NULL"
        {
            strncpy(pszPtr,(LPSTR) "NULL",4);
            pszPtr += iSize;
            strncpy(pszPtr, (LPSTR) "\t",1);
            pszPtr += 1;
        }
        else    // else we have data, so convert to char
        {
            iDatasize = dbconvert(dbproc,
                dbcoltype(dbproc,i),
                pszData,
                dbdatlen(dbproc,i),
                SQLCHAR,
                pszPtr,
                (DBINT)iSize-1);
            pszPtr += iSize;
            strncpy(pszPtr, (LPSTR) "\t",1);
            pszPtr += 1;
        }
    }

    // Finished: null terminate buffer and return SUCCEED
    *pszPtr = '\0';
    return(SUCCEED);
}

//****************************** Function Header ******************************
//
// Function : DetermineRowSize
//
// Description: Calculates length of row / column
//
//*****************************************************************************
int DetermineRowSize(DBPROCESS *dbproc,int iCol)
{
    int     iCols, i;
    int     iLength=0;
    int     iNamelength;
    int     iPrLength;
    LPSTR   pszName;

    // If iCol == 0 then we want the length of the whole row not just a particular column
    // Get number of columns
    if(!iCol) iCols =  dbnumcols(dbproc);

    // count from 1 to numcols if col is 0, else i will equal col only
    // Remember if iCol == 0 then we want the length of the whole row not just a particular column
    for(i =  ((iCol) ? iCol : 1);
        i <= ((iCol) ? iCol : iCols);
        i++)
    {
        // get column type & determine SQLCHAR converted iLength
        iPrLength = GetConvertedLength(dbcoltype(dbproc,i),(int) dbcollen(dbproc,i),dbproc);

        // names may be longer than column so use name len if longer of two
        pszName = dbcolname(dbproc,i);
        iNamelength =  (pszName) ? strlen(pszName) : 0;

        // add one for space between columns
        if(iPrLength<iNamelength)
            // We'll allow at least 4 in case we have to store the value NULL 
            // plus a space
           iLength += max(4,iNamelength) + 1;
        else
            // We'll allow at least 4 in case we have to store the value NULL 
            // plus a space
           iLength += max(4,iPrLength) + 1;
    }

    // Return the length of the field
    return iLength;
}

//****************************** Function Header ******************************
//
// Function : GetConvertedLength
//
// Description: Calculates length of data when converted to SQLCHAR
//
//*****************************************************************************
int GetConvertedLength(int SQLType, int Length, DBPROCESS * dbproc)
{
    DBCHAR * pszMsg;
    int  iPrLength = 0;

    // (Values below are found in SQLFRONT.H header file)
    switch(SQLType)
    {
    case SQLBIT:
        iPrLength = PRBIT;
        break;
    case SQLINT1:
        iPrLength = PRINT1;
        break;
    case SQLINT2:
        iPrLength = PRINT2;
        break;
    case SQLINT4:
    case SQLINTN:
        iPrLength = PRINT4;
        break;
    case SQLFLT4:
    case SQLFLT8:
    case SQLFLTN:
        iPrLength = PRFLT8;
        break;
    case SQLDATETIM4:
    case SQLDATETIME:
    case SQLDATETIMN:
        iPrLength = PRDATETIME;
        break;
    case SQLMONEY4:
    case SQLMONEY:
    case SQLMONEYN:
        iPrLength = PRMONEY;
        break;
    // VARBINARY IMAGE, and BINARY ...convert to 2 times iLength
    case SQLVARBINARY :
    case SQLBINARY:
    case SQLIMAGE:
        iPrLength = Length * 2;
        break;
    case SQLTEXT :
    case SQLCHAR :
    case SQLVARCHAR :
        iPrLength = Length;
        break;
        // other types are maximum of actual column iLength
    default :
        // If we get to here then this is a SQL data type that we
        // don't know about (probably introduced by a later version
        // of SQL Server.
        // We'll just have to allow lots of memory for it and hope for the best
        iPrLength = Length * 10;
        // Better log an error  
        pszMsg = (char *)malloc(strlen("Unknown SQL Data Type . Assuming a size of collen * 10.") + 11);
        sprintf(pszMsg,"Unknown SQL Data Type %d. Assuming a size of collen * 10.",SQLType);
        srv_log(SRV_GETSERVER((SRV_PROC *)dbgetuserdata(dbproc)), Log.FILE_Timing, pszMsg, SRV_NULLTERM);
        free(pszMsg);
        break;
    }
    return iPrLength;
}

#pragma check_stack()   // set stack checking to its default setting

