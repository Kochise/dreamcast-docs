//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//*---------------------------------------------------------------------------------
#include "errcheck.h"
#include "standard.h"
#include "strings.h"


//*---------------------------------------------------------------------------------
//|   Global variables
//*---------------------------------------------------------------------------------
char        szErrOut[100];

dCSEG(char) szErrTitle[]                  =  "Error!";
dCSEG(char) szError[]                     =  "Error: %s,  File: %s, Line: %d";
dCSEG(char) szOutOfMemory[]               =  "Memory levels are very low.  Please exit other applications and try your request again.";
dCSEG(char) szInvalidParms[]              =  "Invalid parameters";
dCSEG(char) szRegisterClassFailed[]       =  "Register class failed";


//*------------------------------------------------------------------------
//| GetSQLState:
//|     Parameters:
//|         handletype     - Type of handle (env, conn, stmt, descr)
//|         handle         - Handle used in last ODBC call
//|         psMsgNum       - Pointer to variable storing message number
//|         szState        - Return sqlstate
//|         szNative       - Native return code (driver specific)
//|         szMessage      - Return message
//*------------------------------------------------------------------------
LPSTR GetSQLState(SWORD handletype, SQLHANDLE handle, SWORD *psMsgNum,
                  LPSTR szState, SDWORD FAR * pfNative, LPSTR szMessage)
{
   RETCODE  rc;
   SWORD    cb;

   rc = SQLGetDiagRec(handletype, handle, (*psMsgNum)++,
                      szState, pfNative,
                      szMessage, RTN_MSG_SIZE, &cb);
   if(rc == SQL_NO_DATA || rc == SQL_ERROR)
      return NULL;
   else
      return szState;
}



//*------------------------------------------------------------------------
//| DoPostError:
//|   This function will post an error message to standard output, whereever
//|      that should be.
//| Parms:
//|   in       szErr                Error message
//|   in       szFile               File name
//|   in       cbLine               Line number
//| Returns:
//|   Nothing.
//*---------------------------------------------------------------------------------
void DoPostError(LPSTR szErr, LPSTR szFile, int cbLine)
{
   wsprintf(szErrOut, szError, (LPSTR)szErr, szFile, cbLine);
   MessageBox(NULL, szErrOut, szErrTitle, MB_OK);
}



//*------------------------------------------------------------------------
//| PrintErrors:
//|     Print out all relevant errors.
//|         ci          -  Pointer to client information
//|         handletype  -  Which handle has relevant error information
//*------------------------------------------------------------------------
void PrintErrors(CHILDINFO FAR * ci, SWORD handletype)
{
   SQLHANDLE handle;

   switch (handletype) {
     case SQL_HANDLE_ENV:
      handle = (SQLHANDLE) ci->henv;
      break;

     case SQL_HANDLE_DBC:
      handle = (SQLHANDLE) ci->hdbc;
      break;

     case SQL_HANDLE_STMT:
      handle = (SQLHANDLE) ci->hstmt;
      break;
   }

   DisplayErrors(ci->hwndOut, (LPSTR)szErrTitle, SQL_HANDLE_ENV, ci->henv);
   if(!ci->hwndOut)
      PrintErrorsHwnd(ci->hwndOut, handletype, handle);
}


//*------------------------------------------------------------------------
//| PrintErrorsHwnd:
//|   Does the actual work.  Needed as separate function for those
//|   function which are not woking directly with a ci struct.
//| Parms:
//|   hwnd        Output window
//|   henv        Environment handle
//|   hdbc        Connection handle
//|   hstmt       Statement handle
//*------------------------------------------------------------------------
void PrintErrorsHwnd(HWND hwnd, SWORD handletype, SQLHANDLE handle)
{
   SWORD    sMsgNum = 0;
   char     szState[7]="";
   char     szMessage[RTN_MSG_SIZE];
   SDWORD   pfNative=0;

   while(GetSQLState(handletype, handle, &sMsgNum,
                     szState, &pfNative, szMessage) != NULL)
      szWrite(hwnd,
              GetidsString(idsErrorString, szErrOut, sizeof(szErrOut)),
              (LPSTR)szState,
              (LPSTR)szMessage);
}


//*------------------------------------------------------------------------
//| DisplayErrors:
//|   This will take all of the errors from the ODBC handles and display
//|   them using message box.  This is usually done when there is no
//|   output window to write them to.
//| Parms:
//|   hwnd        Window handle to own the message box
//|   title       The title for the message box
//|   henv        Environment handle to look on
//|   hdbc        Connection handle to look at
//|   hstmt       Statement handle to look at
//| Returns:
//|   Nothing
//*------------------------------------------------------------------------
void DisplayErrors(HWND hwnd, LPSTR title, SWORD handletype, SQLHANDLE handle)
{
   SWORD    sMsgNum = 0;
   char     szState[7]="";
   char     szMessage[RTN_MSG_SIZE];
   SDWORD   pfNative=0;

   while(GetSQLState(handletype, handle, &sMsgNum,
                     szState, &pfNative, szMessage) != NULL)
	{
    if(  szMessageBox((hwnd) ? hwnd : GetActiveWindow(),
                   MB_ICONEXCLAMATION,
                   title,
                   GetidsString(idsMsgErrorString, szErrOut, sizeof(szErrOut)),
                   (LPSTR)szState,
                   (LPSTR)szMessage) )
						 break;
	}
}
