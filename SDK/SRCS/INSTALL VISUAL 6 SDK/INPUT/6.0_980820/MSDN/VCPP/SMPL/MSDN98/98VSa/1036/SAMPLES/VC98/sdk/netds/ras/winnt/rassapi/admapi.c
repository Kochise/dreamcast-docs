/******************************************************************************
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1992-1997 Microsoft Corporation.
*       All rights reserved. 
*       This sample source code is only intended as a supplement to 
*       RasAdmin API usage and is meant to help user with
*       RasAdmin API Calling convention. Use this code at your own risk. 
*       Microsoft disclaims any implied warranty. This sample code can
*       be copied and distributed.
 
******************************************************************************/

/********************************************************************
*  admapit.c -- Sample program demonstrating the use of different
*                     RasAdmin API
*                                                                    
*  Comments:                                                 
*                   RasAdmin expects \\Servername  as it's arguments.
* RasAdminGetErrorString API returns error string. However 
* this API may return an Error 87 (Invalid Parameter) for the Non 
* RAS Error codes. This API is design for  only Ras related error codes. 
* For more Info. check the documentation. I am using this API to for all the 
* errors but I print the error codes before calling this API 
*****************************************************************************/
/***************************************************************************
*  Functions:
*      Init2(void);
*      Init1(void);
*      PrintGetStringError(DWORD dwResult);
*      ServerGetInfo(WCHAR *RasSrv);
*      PrintPriv(void);
*      UserPrivilege(void);
*      PrintClearStats(WCHAR * RasSrv, WCHAR *wszPortName);
*      RasAdminClearDisc(LPVOID param);
*****************************************************************************/


#define sleeptime 60000
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <lm.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <rassapi.h>

#include <memory.h>
WCHAR*
StrDupWFromA(
    CHAR* psz );


#define Number_Of_Flags 6
HANDLE LogFile = NULL;
HANDLE cLogFile = NULL;
HANDLE ErrLogFile = NULL;
VOID File_Print(RAS_PORT_1 *            pRasPort1,
    RAS_PORT_STATISTICS *   pRasStats,
    RAS_PARAMETERS *        pRasParams
);
VOID Debug_Print(RAS_PORT_1 *            pRasPort1,
    RAS_PORT_STATISTICS *   pRasStats,
    RAS_PARAMETERS *        pRasParams
);
VOID Init2(void);
VOID Init1(void);
VOID PrintGetStringError(DWORD dwResult);
INT ServerGetInfo(WCHAR *RasSrv);
VOID PrintPriv(void);
VOID UserPrivilege(void);
VOID PrintClearStats(WCHAR * RasSrv, WCHAR *wszPortName);
DWORD WINAPI RasAdminClearDisc(LPVOID param);

PRAS_PORT_1             pRasPort1;
PRAS_PORT_STATISTICS    pRasStats;
RAS_PARAMETERS *        pRasParams;
PRAS_SERVER_0           pRasServer0;
PRAS_PORT_0             pRasPort0;
RAS_PORT_1             RasPort1;
RAS_PORT_STATISTICS    RasStats;
RAS_SERVER_0           RasServer0;

BOOL First_Call = TRUE;
DWORD Status =0;
DWORD dwResult = 0;
DWORD dwBytesWritten=0;
CHAR szBuf[120];
BOOL ErrLogInValid = FALSE;
BOOL cErrLogInValid = FALSE;
BOOL LogInValid = TRUE;
WCHAR szUserAccountServer[UNLEN+1];
PRAS_USER_0 ppRasUser0;
RAS_USER_0 RasUser0;
WCHAR lpszServerName[50];
WCHAR RasSrv[64];
BOOL Quit=FALSE;
/*************************************************************************/
/***************** Start Main ********************************************/
/*************************************************************************/

WCHAR*
StrDupWFromA(
    CHAR* psz )

    /* Returns heap block containing a copy of 0-terminated string 'psz' or
    ** NULL on error or if 'psz' is NULL.  The output string is converted to
    ** UNICODE.  It is caller's responsibility to Free the returned string.
    */
{
    WCHAR* pszNew = NULL;

    if (psz)
    {
	DWORD cb;

	cb = MultiByteToWideChar( CP_ACP, 0, psz, -1, NULL, 0 );

	pszNew = malloc( cb * sizeof(TCHAR) );
	if (!pszNew)
	{
	    return NULL;
	}

	cb = MultiByteToWideChar( CP_ACP, 0, psz, -1, pszNew, cb );
	if (cb == 0)
	{
	    free( pszNew );
	    return NULL;
	}
    }

    return pszNew;
}




// Format and write debug information to OutputDebugString
ULONG
_cdecl
DbgPrint(
    PCH Format,
    ...
    )
{   
    CHAR szbuffer[255];
    WCHAR buffer[255];
    WCHAR *temp=NULL;
    LPINT lpResult=0;
    va_list marker;
    va_start (marker,Format);
    if (IsTextUnicode(Format, sizeof(Format),lpResult))
	{
	temp=StrDupWFromA(Format);
	     wvsprintfW (buffer,temp, marker);
	     OutputDebugString (buffer);
	      free(temp);
	}
    else
	{
	     wvsprintfA (szbuffer,Format, marker);
	     temp=StrDupWFromA(szbuffer);
	     OutputDebugString (temp);
	     free(temp);
	     }
    return TRUE;
}





// Init Functions
VOID Init1(void)
{
//Stores port  information in this file
LogInValid = FALSE;
	     LogFile = CreateFile(TEXT("Admin.log"),
				GENERIC_READ|GENERIC_WRITE,
				FILE_SHARE_READ,
				(LPSECURITY_ATTRIBUTES) NULL,
				CREATE_ALWAYS,
				0,
			       (HANDLE) NULL);
	     if (LogFile== INVALID_HANDLE_VALUE) {
		LogInValid = TRUE;
	    }

}
VOID Init2(void)
{
cErrLogInValid = FALSE;
ErrLogInValid = FALSE;
//Stores Statistics and port disconnect information in this file
	     cLogFile = CreateFile(TEXT("AdminStats.log"),
				GENERIC_READ|GENERIC_WRITE,
				FILE_SHARE_READ,
				(LPSECURITY_ATTRIBUTES) NULL,
				CREATE_ALWAYS,
				0,
			       (HANDLE) NULL);
	     if (cLogFile== INVALID_HANDLE_VALUE) {
		cErrLogInValid = TRUE;
	    }
//Stores Privlege changes information of a user in this file
	     ErrLogFile = CreateFile(TEXT("AdminUser.log"),
				GENERIC_READ|GENERIC_WRITE,
				FILE_SHARE_READ,
				(LPSECURITY_ATTRIBUTES) NULL,
				CREATE_ALWAYS,
				0,
			       (HANDLE) NULL);
	     if (ErrLogFile== INVALID_HANDLE_VALUE) {
		ErrLogInValid = TRUE;
	    }
	    
}

//Function to Print Error Strings

VOID PrintGetStringError(DWORD dwResult)
{
CHAR szBuf[120];
DWORD dwBytesWritten=0;

     DbgPrint("ERROR  RasAdminGetErrorString      %d\n",dwResult);
     sprintf(szBuf, "ERROR  RasAdminGetErrorString      %d\n",dwResult);     
     WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
}

// Function to get Server  Info.
INT ServerGetInfo(WCHAR *RasSrv)
{
DWORD Status;
DWORD dwResult;
CHAR szBuf[120];
DWORD dwBytesWritten=0;
WCHAR Buf[512];
WCHAR *lpszString;
lpszString=&Buf[0];

// Calling RasAdminServerGetInfo 
// Paramters:
// IN   WCHAR * lpszServerName              //name of the RAS Server
// OUT PRAS_SERVER_0 pRasServer0    // Pointer to server inf.


Status=RasAdminServerGetInfo(RasSrv, pRasServer0);
if (Status != ERROR_SUCCESS)
   {
	sprintf(szBuf, "ERROR RasAdminServerGetInfo   %d\n",Status);
	dwResult = RasAdminGetErrorString((UINT) Status, lpszString, 512);
	if (dwResult == ERROR_SUCCESS)
	    {
	    DbgPrint("ERROR  RasAdminServerGetInfo      %ws\n",lpszString);
	     sprintf(szBuf, "ERROR  RasAdminServerGetInfo      %ws\n",lpszString);     
		  WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	    }
	 else
	    PrintGetStringError(dwResult);
	      return(1);
   }
else
   {
    sprintf(szBuf, "TotalPorts =  %d   PortsInUse = %d   RasVersion = %d  \n",
       pRasServer0->TotalPorts, pRasServer0->PortsInUse, pRasServer0->RasVersion);     
    WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
   }
return(0);
}

// Function to print Privileges of a user
VOID PrintPriv(void)
{
DWORD Permission;
DWORD dwBytesWritten=0;
CHAR szBuf[120];

     sprintf(szBuf,"\n User Privileges\n");
     WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
     sprintf(szBuf,"Account Server Name= %ws     UserName= %ws\n",szUserAccountServer, pRasPort1->rasport0.wszUserName);
     WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
     sprintf(szBuf," Priviledge   %d\n",ppRasUser0->bfPrivilege);
     WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
     Permission = ppRasUser0->bfPrivilege - (ppRasUser0->bfPrivilege & RASPRIV_DialinPrivilege);
     sprintf(szBuf,"CallBack Permission %d\n",Permission);
     WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
}

//Function to get and change User Dialin Privileges. It goes through all the Dialin Privileges for a user.

VOID UserPrivilege(void)
{
DWORD dwResult;
CHAR szBuf[120];
DWORD dwBytesWritten=0;
WCHAR Buf[512];
WCHAR *lpszString;
static DWORD LoopPriv=0;
static BYTE Dialin=1;
lpszString=&Buf[0];

// API Called:     RasAdminGetUserAccountServer
// Parameters:
//  IN WCHAR * lpszDomainName
// IN WCHAR * lpszServerName
// OUT WCHAR * lpszUserAccountServer

   if (pRasPort1->rasport0.fAdvancedServer > 0)
     {
      dwResult = RasAdminGetUserAccountServer(pRasPort1->rasport0.wszLogonDomain, 
		 NULL, &szUserAccountServer[0]);
     }
  else 
      {  
      wcscpy(lpszServerName, RasSrv);
      dwResult = RasAdminGetUserAccountServer(NULL, &lpszServerName[0], &szUserAccountServer[0]);
      }

// API Called:     RasAdmimUserGetInfo
// Parameters:
//  IN WCHAR * lpszUserAccountServer
// IN WCHAR * lpszUserName
// OUT RAS_USER_0 * ppRasUser0

  if (dwResult == ERROR_SUCCESS)
     {
     dwResult = RasAdminUserGetInfo(szUserAccountServer, pRasPort1->rasport0.wszUserName, ppRasUser0);
     if (dwResult == ERROR_SUCCESS)
	 {
	  PrintPriv();
	 }
     else
	{
	sprintf(szBuf,"RasAdminUserGetInfo     %d\n",dwResult);
	WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	dwResult = RasAdminGetErrorString((UINT) dwResult, lpszString, 512);
	if (dwResult == ERROR_SUCCESS)
	    {
	    sprintf(szBuf, "ERROR  RasAdminUserGetInfo      %ws\n",lpszString);     
	    WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	    }
	else
	    PrintGetStringError(dwResult);
	}
      if (LoopPriv > 3) 
		{LoopPriv =0; Dialin = 1;}
      if (LoopPriv < 4)
	 {
	  if (LoopPriv == 3) wcscpy(ppRasUser0->szPhoneNumber, TEXT("99999999"));
	  if (LoopPriv == 0) {ppRasUser0->bfPrivilege =  Dialin;Dialin = Dialin * 2;LoopPriv++;}
	  else {ppRasUser0->bfPrivilege = (RASPRIV_DialinPrivilege | Dialin  );
		Dialin = Dialin * 2 ;
		LoopPriv++;}
	 }
// API Called:     RasAdmimUserSetInfo
// Parameters:
//  IN WCHAR * lpszUserAccountServer
// IN WCHAR * lpszUserName
// IN RAS_USER_0 * ppRasUser0
	  
     dwResult = RasAdminUserSetInfo(szUserAccountServer, pRasPort1->rasport0.wszUserName,ppRasUser0);
     if (dwResult != ERROR_SUCCESS)
	{
	sprintf(szBuf,"ERROR: RasAdminUserSetInfo     %d\n",dwResult);
	WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	dwResult = RasAdminGetErrorString((UINT) dwResult, lpszString, 512);
	if (dwResult == ERROR_SUCCESS)
	    {
	     sprintf(szBuf, "ERROR  RasAdminUserSetInfo      %ws\n",lpszString);     
	     WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	    }
	 else
	    PrintGetStringError(dwResult);
	 }
// API Called:     RasAdmimUserSetInfo
// Parameters:
//  IN WCHAR * lpszUserAccountServer
// IN WCHAR * lpszUserName
// IN RAS_USER_0 * ppRasUser0
     if (LoopPriv == 0) 
	     {
	      ppRasUser0->bfPrivilege = (ppRasUser0->bfPrivilege | RASPRIV_DialinPrivilege);
	      dwResult = RasAdminUserSetInfo(szUserAccountServer, pRasPort1->rasport0.wszUserName, ppRasUser0);
		if (dwResult == ERROR_SUCCESS)
		   {
		   PrintPriv();
		   }
		else
		   {
		   sprintf(szBuf,"RasAdminUserSetInfo     %d\n",dwResult);
		   WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
		   dwResult = RasAdminGetErrorString((UINT) dwResult, lpszString, 512);
		   if (dwResult == ERROR_SUCCESS)
		      {
		      sprintf(szBuf, "ERROR  RasAdminUserSetInfo      %ws\n",lpszString);     
		      WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
		      }
		   else
		      PrintGetStringError(dwResult);
		   }
	     }
// API Called:     RasAdmimUserGetInfo
// Parameters:
//  IN WCHAR * lpszUserAccountServer
// IN WCHAR * lpszUserName
// OUT RAS_USER_0 * ppRasUser0
	 dwResult = RasAdminUserGetInfo(szUserAccountServer, pRasPort1->rasport0.wszUserName, ppRasUser0);
	 if (dwResult != ERROR_SUCCESS)
	     {
	    sprintf(szBuf,"ERROR: RasAdminUserGetInfo     %d\n",dwResult);
	    WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	    dwResult = RasAdminGetErrorString((UINT) dwResult, lpszString, 512);
	    if (dwResult == ERROR_SUCCESS)
	       {
	       sprintf(szBuf, "ERROR  RasAdminUserGetInfo      %ws\n",lpszString);     
	       WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	       }
	    else
	      PrintGetStringError(dwResult);
	    }
     }
  else
    {
    DbgPrint("RasAdminGetUserAccountServer     %d\n",dwResult);
    dwResult = RasAdminGetErrorString((UINT)dwResult, lpszString, 512);
     if (dwResult == ERROR_SUCCESS)
	  {
	  sprintf(szBuf, "ERROR  RasAdminUserAccountServer      %ws\n",lpszString);     
	  WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	  }
      else
	 PrintGetStringError(dwResult);
    }


}

//To print port information, statistics and rasparams on debugger.

VOID Debug_Print(RAS_PORT_1 *            pRasPort1,
    RAS_PORT_STATISTICS *   pRasStats,
    RAS_PARAMETERS *        pRasParams
)
{
TCHAR *Media_Name[] = {TEXT("MEDIA_UNKNOWN"),TEXT( "MEDIA_SERIAL"),
		  TEXT("MEDIA_RAS10_SERIAL"),TEXT( "MEDIA_ISDN")};
TCHAR *Flag_Name[] = {TEXT("USER_AUTHENTICATED"),TEXT( "MESSENGER_PRESENT"),
		 TEXT("PPP_CLIENT"),TEXT("GATEWAY_ACTIVE"),TEXT("REMOTE_LISTEN"),TEXT("PORT_MULTILINKED")};
TCHAR *Line_Condition[]={TEXT("RAS_PORT_NON_OPERATIONAL"),TEXT("RAS_PORT_DISCONNECTED"),
		  TEXT("RAS_PORT_CALLING_BACK"),TEXT("RAS_PORT_LISTENING"),TEXT("RAS_PORT_AUTHENTICATING"),
		  TEXT("RAS_PORT_AUTHENTICATED"),TEXT("RAS_PORT_INITIALIZING")};
TCHAR *Hdw_Error[]={TEXT("RAS_MODEM_OPERATIONAL"),TEXT("RAS_MODEM_NOT_RESPONDING"),TEXT("RAS_MODEM_HARDWARE_FAILURE"),
		  TEXT("RAS_MODEM_INCORRECT_RESPONSE"),TEXT("RAS_MODEM_UNKNOWN")};
INT  i=0;
INT temp = 0;
INT temp1 =0;
DWORD dwsize=0;
CHAR szBuf[100];
DWORD dwBytesWritten=0;

    DbgPrint( "pRasPort1->rasport0.wszPortName=%ws\n",
		pRasPort1->rasport0.wszPortName );
    DbgPrint( "pRasPort1->rasport0.wszDeviceType=%ws\n",
		    pRasPort1->rasport0.wszDeviceType );
    DbgPrint( "pRasPort1->rasport0.wszDeviceName=%ws\n",
		    pRasPort1->rasport0.wszDeviceName );
    DbgPrint( "pRasPort1->rasport0.wszMediaName=%ws\n",
		pRasPort1->rasport0.wszMediaName );
    DbgPrint( "pRasPort1->rasport0.reserved=%d\n",
		    pRasPort1->rasport0.reserved );
    DbgPrint("                 %s\n",Media_Name[pRasPort1->rasport0.reserved]);
    DbgPrint( "pRasPort1->rasport0.Flags=%d\n",
			pRasPort1->rasport0.Flags );
//printing Flags
    temp1 = 1;
    for (i=0; i <= Number_Of_Flags; i++)
	 {
	 temp = (pRasPort1->rasport0.Flags & temp1);
	 if (temp)
	     {
	       DbgPrint("Flag       %s   \n",Flag_Name[i]);
	     }
	  temp1 = temp1*2;
	 }
    DbgPrint( "pRasPort1->rasport0.wszUserName=%ws\n",
			pRasPort1->rasport0.wszUserName );
    DbgPrint( "pRasPort1->rasport0.wszComputer=%ws\n",
			pRasPort1->rasport0.wszComputer );
    DbgPrint( "pRasPort1->rasport0.dwStartSessionTime;=%d\n",
		    pRasPort1->rasport0.dwStartSessionTime );
    sprintf(szBuf,"Formatted session start time/date :  %s\n",ctime(&pRasPort1->rasport0.dwStartSessionTime));
    DbgPrint("%s",szBuf);
    DbgPrint( "pRasPort1->rasport0.wszLogonDomain=%ws\n",
		    pRasPort1->rasport0.wszLogonDomain );
    DbgPrint( "pRasPort1->rasport0.fAdvancedServer=%d\n",
		    pRasPort1->rasport0.fAdvancedServer );
    DbgPrint( "pRasPort1->LineCondition=%d\n", pRasPort1->LineCondition );
    DbgPrint("                     %s\n",Line_Condition[pRasPort1->LineCondition-1]);
    DbgPrint( "pRasPort1->HardwareCondition=%d\n",pRasPort1->HardwareCondition);
    DbgPrint("                     %s\n",Hdw_Error[pRasPort1->HardwareCondition-1]);
    DbgPrint( "pRasPort1->LineSpeed=%d   bits/sec\n",pRasPort1->LineSpeed);
    DbgPrint( "pRasPort1->NumStatistics=%d\n",pRasPort1->NumStatistics);
    DbgPrint( "pRasPort1->NumMediaParms=%d\n",pRasPort1->NumMediaParms);
    DbgPrint( "pRasPort1->SizeMediaParms=%d\n",pRasPort1->SizeMediaParms);
    DbgPrint( "\npRasPort1->ProjResult.nbf.dwError=%d\n",
					pRasPort1->ProjResult.nbf.dwError );
    if (pRasPort1->ProjResult.nbf.dwError == NO_ERROR)
       {
	DbgPrint( "pRasPort1->ProjResult.nbf.dwNetBiosError=%d\n",
			    pRasPort1->ProjResult.nbf.dwNetBiosError );
	DbgPrint( "pRasPort1->ProjResult.nbf.szName=%s\n", 
				    pRasPort1->ProjResult.nbf.szName );
	DbgPrint( "pRasPort1->ProjResult.nbf.wszWksta=%ws\n",
				    pRasPort1->ProjResult.nbf.wszWksta );
      }
   DbgPrint( "pRasPort1->ProjResult.ip.dwError=%d\n", 
					pRasPort1->ProjResult.ip.dwError );
   if (pRasPort1->ProjResult.ip.dwError == NO_ERROR)
      { 
	DbgPrint( "pRasPort1->ProjResult.ip.wszAddress=%ws\n",
				pRasPort1->ProjResult.ip.wszAddress );
       }
    DbgPrint( "pRasPort1->ProjResult.ipx.dwError=%d\n",
				pRasPort1->ProjResult.ipx.dwError );
    if (pRasPort1->ProjResult.ipx.dwError == NO_ERROR)
      {
	     DbgPrint( "pRasPort1->ProjResult.ipx.wszAddress=%ws\n",
			pRasPort1->ProjResult.ipx.wszAddress );
      }
    DbgPrint( "pRasPort1->ProjResult.at.dwError=%d\n",
				pRasPort1->ProjResult.at.dwError );
    if (pRasPort1->ProjResult.at.dwError == NO_ERROR)
      {
	      DbgPrint( "pRasPort1->ProjResult.at.wszAddress=%ws\n",
			pRasPort1->ProjResult.at.wszAddress );
       }
    DbgPrint( "\ndwBytesXmited=%d\n", pRasStats->dwBytesXmited );
    DbgPrint( "dwBytesRcved=%d\n", pRasStats->dwBytesRcved );
    DbgPrint( "dwFramesXmited=%d\n", pRasStats->dwFramesXmited );
    DbgPrint( "dwFramesRcved=%d\n", pRasStats->dwFramesRcved);
    DbgPrint( "dwCrcErr=%d\n", pRasStats->dwCrcErr);
    DbgPrint( "dwTimeoutErr=%d\n", pRasStats->dwTimeoutErr);
    DbgPrint( "dwAlignmentErr=%d\n", pRasStats->dwAlignmentErr);
    DbgPrint( "dwHardwareOverrunErr=%d\n", pRasStats->dwHardwareOverrunErr);
    DbgPrint( "dwFramingErr=%d\n", pRasStats->dwFramingErr);
    DbgPrint( "dwBufferOverrunErr=%d\n", pRasStats->dwBufferOverrunErr);
    DbgPrint( "dwBytesXmitedUncompressed=%d\n", 
				    pRasStats->dwBytesXmitedUncompressed);
    DbgPrint( "dwBytesRcvedUncompressed=%d\n", 
				    pRasStats->dwBytesRcvedUncompressed);
    DbgPrint( "dwBytesXmitedCompressed=%d\n", 
				    pRasStats->dwBytesXmitedCompressed);
    DbgPrint( "dwBytesRcvedCompressed=%d\n", 
				    pRasStats->dwBytesRcvedCompressed);
    for (i=0; i<pRasPort1->NumMediaParms;i++)
      {
      DbgPrint( "pRasParams->P_Key= %s\n",pRasParams[i].P_Key);
      DbgPrint( "pRasParams->P_Type= %d\n",pRasParams[i].P_Type);
      if (pRasParams[i].P_Type == 1)
	  {
	  DbgPrint("pRasParams->P_Value.Length=%d\n",pRasParams[i].P_Value.String.Length);
	  sprintf(szBuf,"                                                                \n");
	  strncpy(szBuf, pRasParams[i].P_Value.String.Data, pRasParams[i].P_Value.String.Length);
	  DbgPrint("pRasParams->P_Value.Data= %s\n",szBuf);
	  }
      if (pRasParams[i].P_Type == 0)
	 {
	 DbgPrint("pRasParams->P_Value.Number=%d\n", pRasParams[i].P_Value.Number);
	 }
      DbgPrint( "pRasParams->P_Attributes= %d\n",pRasParams[i].P_Attributes);
      }
}


//Function to print Port Info, statistics and rasparam to a file
VOID File_Print(RAS_PORT_1 *            pRasPort1,
    RAS_PORT_STATISTICS *   pRasStats,
    RAS_PARAMETERS *        pRasParams
)
{
char *Media_Name[] = {"MEDIA_UNKNOWN", "MEDIA_SERIAL",
		  "MEDIA_RAS10_SERIAL", "MEDIA_ISDN"};
char *Flag_Name[] = {"USER_AUTHENTICATED", "MESSENGER_PRESENT",
		 "PPP_CLIENT","GATEWAY_ACTIVE","REMOTE_LISTEN","PORT_MULTILINKED"};
char *Line_Condition[]={"RAS_PORT_NON_OPERATIONAL","RAS_PORT_DISCONNECTED",
		  "RAS_PORT_CALLING_BACK","RAS_PORT_LISTENING","RAS_PORT_AUTHENTICATING",
		  "RAS_PORT_AUTHENTICATED","RAS_PORT_INITIALIZING"};
char *Hdw_Error[]={"RAS_MODEM_OPERATIONAL","RAS_MODEM_NOT_RESPONDING","RAS_MODEM_HARDWARE_FAILURE",
		  "RAS_MODEM_INCORRECT_RESPONSE","RAS_MODEM_UNKNOWN"};
INT  i=0;
INT temp = 0;
INT temp1 =0;
DWORD dwsize=0;
CHAR szBuf[50];
CHAR buf[120];
DWORD dwBytesWritten=0;
    sprintf(buf, "pRasPort1->rasport0.wszPortName=%ws\n",
		pRasPort1->rasport0.wszPortName );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf,"pRasPort1->rasport0.wszDeviceType=%ws\n",
		    pRasPort1->rasport0.wszDeviceType );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf,"pRasPort1->rasport0.wszDeviceName=%ws\n",
		    pRasPort1->rasport0.wszDeviceName );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->rasport0.wszMediaName=%ws\n",
		pRasPort1->rasport0.wszMediaName );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf,"pRasPort1->rasport0.reserved=%d\n",
		    pRasPort1->rasport0.reserved );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf,"                 %s\n",Media_Name[pRasPort1->rasport0.reserved]);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->rasport0.Flags=%d\n",
			pRasPort1->rasport0.Flags );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
//printing Flags
    temp1 = 1;
    for (i=0; i <= Number_Of_Flags; i++)
	 {
	 temp = (pRasPort1->rasport0.Flags & temp1);
	 if (temp)
	     {
	       sprintf(buf,"Flag       %s   \n",Flag_Name[i]);
		     WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	     }
	  temp1 = temp1*2;
	 }
    sprintf(buf, "pRasPort1->rasport0.wszUserName=%ws\n",
			pRasPort1->rasport0.wszUserName );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->rasport0.wszComputer=%ws\n",
			pRasPort1->rasport0.wszComputer );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->rasport0.dwStartSessionTime;=%d\n",
		    pRasPort1->rasport0.dwStartSessionTime );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf,"Formatted session start time/date :  %s\n",ctime(&pRasPort1->rasport0.dwStartSessionTime));
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->rasport0.wszLogonDomain=%ws\n",
		    pRasPort1->rasport0.wszLogonDomain );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->rasport0.fAdvancedServer=%d\n",
		    pRasPort1->rasport0.fAdvancedServer );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->LineCondition=%d\n", pRasPort1->LineCondition );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf,"                     %s\n",Line_Condition[pRasPort1->LineCondition-1]);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->HardwareCondition=%d\n",pRasPort1->HardwareCondition);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf,"                     %s\n",Hdw_Error[pRasPort1->HardwareCondition-1]);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->LineSpeed=%d   bits/sec\n",pRasPort1->LineSpeed);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->NumStatistics=%d\n",pRasPort1->NumStatistics);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->NumMediaParms=%d\n",pRasPort1->NumMediaParms);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->SizeMediaParms=%d\n",pRasPort1->SizeMediaParms);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "\npRasPort1->ProjResult.nbf.dwError=%d\n",
					pRasPort1->ProjResult.nbf.dwError );
    if (pRasPort1->ProjResult.nbf.dwError == NO_ERROR)
       {
	sprintf(buf, "pRasPort1->ProjResult.nbf.dwNetBiosError=%d\n",
			    pRasPort1->ProjResult.nbf.dwNetBiosError );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	sprintf(buf, "pRasPort1->ProjResult.nbf.szName=%s\n", 
				    pRasPort1->ProjResult.nbf.szName );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	sprintf(buf, "pRasPort1->ProjResult.nbf.wszWksta=%ws\n",
				    pRasPort1->ProjResult.nbf.wszWksta );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
      }
   sprintf(buf, "pRasPort1->ProjResult.ip.dwError=%d\n", 
					pRasPort1->ProjResult.ip.dwError );
   WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   if (pRasPort1->ProjResult.ip.dwError == NO_ERROR)
      { 
	sprintf(buf, "pRasPort1->ProjResult.ip.wszAddress=%ws\n",
				pRasPort1->ProjResult.ip.wszAddress );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
       }
    sprintf(buf, "pRasPort1->ProjResult.ipx.dwError=%d\n",
				pRasPort1->ProjResult.ipx.dwError );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    if (pRasPort1->ProjResult.ipx.dwError == NO_ERROR)
      {
	     sprintf(buf, "pRasPort1->ProjResult.ipx.wszAddress=%ws\n",
			pRasPort1->ProjResult.ipx.wszAddress );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
      }
    sprintf(buf, "pRasPort1->ProjResult.at.dwError=%d\n",
				pRasPort1->ProjResult.at.dwError );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    if (pRasPort1->ProjResult.at.dwError == NO_ERROR)
      {
	      sprintf(buf, "pRasPort1->ProjResult.at.wszAddress=%ws\n",
			pRasPort1->ProjResult.at.wszAddress );
       }
    sprintf(buf, "\ndwBytesXmited=%d\n", pRasStats->dwBytesXmited );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwBytesRcved=%d\n", pRasStats->dwBytesRcved );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwFramesXmited=%d\n", pRasStats->dwFramesXmited );
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwFramesRcved=%d\n", pRasStats->dwFramesRcved);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwCrcErr=%d\n", pRasStats->dwCrcErr);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwTimeoutErr=%d\n", pRasStats->dwTimeoutErr);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwAlignmentErr=%d\n", pRasStats->dwAlignmentErr);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwHardwareOverrunErr=%d\n", pRasStats->dwHardwareOverrunErr);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwFramingErr=%d\n", pRasStats->dwFramingErr);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwBufferOverrunErr=%d\n", pRasStats->dwBufferOverrunErr);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwBytesXmitedUncompressed=%d\n", 
				    pRasStats->dwBytesXmitedUncompressed);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwBytesRcvedUncompressed=%d\n", 
				    pRasStats->dwBytesRcvedUncompressed);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwBytesXmitedCompressed=%d\n", 
				    pRasStats->dwBytesXmitedCompressed);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwBytesRcvedCompressed=%d\n", 
				    pRasStats->dwBytesRcvedCompressed);
    WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    for (i=0; i<pRasPort1->NumMediaParms;i++)
      {
      sprintf(buf, "pRasParams->P_Key= %s\n",pRasParams[i].P_Key);
      WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
      sprintf(buf, "pRasParams->P_Type= %d\n",pRasParams[i].P_Type);
      WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
      if (pRasParams[i].P_Type == 1)
	  {
	  sprintf(buf,"pRasParams->P_Value.Length=%d\n",pRasParams[i].P_Value.String.Length);
		WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	  sprintf(szBuf,"                                                                \n");
	  strncpy(szBuf, pRasParams[i].P_Value.String.Data, pRasParams[i].P_Value.String.Length);
	  sprintf(buf,"pRasParams->P_Value.Data= %s\n",szBuf);
	       WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	  }
      if (pRasParams[i].P_Type == 0)
	 {
	 sprintf(buf,"pRasParams->P_Value.Number=%d\n", pRasParams[i].P_Value.Number);
	      WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	 }
      sprintf(buf, "pRasParams->P_Attributes= %d\n",pRasParams[i].P_Attributes);
      WriteFile(LogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
      }
}

//Function to  clear port statistics.

VOID PrintClearStats(WCHAR * RasSrv, WCHAR *wszPortName)
{
RAS_PORT_1             RasPort1;
RAS_PORT_STATISTICS    RasStats;
RAS_PORT_STATISTICS    NewRasStats;
RAS_PARAMETERS *        pRasParams=NULL;
DWORD dwBytesWritten=0;
CHAR szBuf[120];
CHAR buf[120];
WCHAR Buf[512];
WCHAR *lpszString;
lpszString=&Buf[0];

// API Called:     RasAdmimPortGetInfo
// Parameters:
//  IN WCHAR * lpszUserAccountServer
// IN WCHAR * lpszPortName
// OUT RAS_PORT_1 * pRasPort1
// OUT RAS_PORT_STATISTICS * pRasPortStatistics
// OUT RAS_PARAMETERS ** ppRasParams

// ppRasParams should be freed by calling RasAdminFreeBuffer

Status = RasAdminPortGetInfo ( RasSrv, wszPortName, &RasPort1, &RasStats, &pRasParams); 
     if (Status != ERROR_SUCCESS)       
	  {
	  sprintf(szBuf, "ERROR RasAdminGetInfo   %d\n",Status);
	  WriteFile(cLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	  dwResult = RasAdminGetErrorString((UINT) Status, lpszString, 512);
	 if (dwResult == ERROR_SUCCESS)
	     {
	     DbgPrint("ERROR  RasAdminPortGetInfo      %ws\n",lpszString);
	     sprintf(szBuf, "ERROR  RasAdminPortGetInfo      %ws\n",lpszString);     
	     WriteFile(cLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	     }
	 else
	     PrintGetStringError(dwResult);
	}
     else
	{

// API Called:     RasAdmimPortClearStatistics
// Parameters:
//  IN WCHAR * lpszServerName
// IN WCHAR * lpszPortName

	Status = RasAdminPortClearStatistics(RasSrv, wszPortName);
	if (Status != ERROR_SUCCESS)    
	  {
	  sprintf(szBuf, "ERROR RasAdminPortClearStatistics   %d\n",Status);
	  WriteFile(cLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	  dwResult = RasAdminGetErrorString((UINT) Status, lpszString, 512);
	 if (dwResult == ERROR_SUCCESS)
	     {
	     DbgPrint("ERROR  RasAdminPortClearStatistics      %ws\n",lpszString);
	     sprintf(szBuf, "ERROR  RasAdminPortClearStatistics      %ws\n",lpszString);     
	     WriteFile(cLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	     }
	 else
	     PrintGetStringError(dwResult);
	  }
       else
	  {
	  if (pRasParams != NULL)
		RasAdminFreeBuffer(pRasParams);

	  Status = RasAdminPortGetInfo ( RasSrv, wszPortName, &RasPort1, &NewRasStats,&pRasParams); 
	  sprintf(buf,"Port name is   %ws\n",wszPortName);
	  printf("%s",buf);
	  WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	  sprintf(buf, "\ndwBytesXmited=%d                    new= %d\n", RasStats.dwBytesXmited,NewRasStats.dwBytesXmited );
	  printf("%s",buf);
	  WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	  sprintf(buf, "dwBytesRcved=%d                       new= %d\n", RasStats.dwBytesRcved,NewRasStats.dwBytesRcved );
	  printf("%s",buf);
	  WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	  sprintf(buf, "dwFramesXmited=%d                   new= %d\n", RasStats.dwFramesXmited, NewRasStats.dwFramesXmited );
	  printf("%s",buf);
	  WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	  sprintf(buf, "dwFramesRcved=%d                    new= %d\n", RasStats.dwFramesRcved, NewRasStats.dwFramesRcved);
	  printf("%s",buf);
	  WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	  sprintf(buf, "dwCrcErr=%d                              new= %d\n", RasStats.dwCrcErr, NewRasStats.dwCrcErr);
	  printf("%s",buf);
	  WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	  sprintf(buf, "dwTimeoutErr=%d                       new= %d\n", RasStats.dwTimeoutErr, NewRasStats.dwTimeoutErr);
	  printf("%s",buf);
	  WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	  sprintf(buf, "dwAlignmentErr=%d                  new= %d\n", RasStats.dwAlignmentErr, NewRasStats.dwAlignmentErr);
	  printf("%s",buf);
	  WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	  sprintf(buf, "dwHardwareOverrunErr=%d        new= %d\n", RasStats.dwHardwareOverrunErr, NewRasStats.dwHardwareOverrunErr);
	  printf("%s",buf);
	  WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	  sprintf(buf, "dwFramingErr=%d                     new= %d\n", RasStats.dwFramingErr, NewRasStats.dwFramingErr);
	  printf("%s",buf);
	  WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	  sprintf(buf, "dwBufferOverrunErr=%d             new= %d\n", RasStats.dwBufferOverrunErr, NewRasStats.dwBufferOverrunErr);
	  printf("%s",buf);
	  WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	  sprintf(buf, "dwBytesXmitedUncompressed=%d   new= %d\n", 
				    RasStats.dwBytesXmitedUncompressed, NewRasStats.dwBytesXmitedUncompressed);
	  printf("%s",buf);
	  WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	  sprintf(buf, "dwBytesRcvedUncompressed=%d   new= %d\n", 
				    RasStats.dwBytesRcvedUncompressed, NewRasStats.dwBytesRcvedUncompressed);
	  printf("%s",buf);
	  WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	  sprintf(buf, "dwBytesXmitedCompressed=%d     new= %d\n", 
				    RasStats.dwBytesXmitedCompressed, NewRasStats.dwBytesXmitedCompressed);
	  printf("%s",buf);
	  WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	  sprintf(buf, "dwBytesRcvedCompressed=%d      new= %d\n", 
				    RasStats.dwBytesRcvedCompressed, NewRasStats.dwBytesRcvedCompressed);
	  printf("%s",buf);
	  WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	}
     if (pRasParams != NULL)
		RasAdminFreeBuffer(pRasParams);
   }
}

//Function to reset Port statistic

DWORD WINAPI RasAdminClearDisc(LPVOID param)
{
CHAR option= ' ';
WORD i=0;
DWORD Status=0;
WORD Entries=0;
DWORD PortOption = 0;
RAS_PORT_0 *            pRasPort0=NULL;
DWORD dwBytesWritten=0;
CHAR szBuf[120];
WCHAR Buf[512];
WCHAR *lpszString;
INT k=0;
lpszString=&Buf[0];
while (!Quit)
  {
    Status = RasAdminPortEnum( RasSrv, &pRasPort0, &Entries);
    if (Status != ERROR_SUCCESS)
	{
	sprintf(szBuf, "ERROR RasAdminPortEnum   %d\n",Status);
	dwResult = RasAdminGetErrorString((UINT) Status, lpszString, 512);
	if (dwResult == ERROR_SUCCESS)
	    {
	    sprintf(szBuf,"ERROR  RasAdminPortEnum      %ws\n",lpszString);
	    WriteFile(cLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	    sprintf(szBuf, "ERROR  RasAdminPortEnum      %ws\n",lpszString);     
	    WriteFile(cLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	    }
	 else
	    PrintGetStringError(dwResult);
	}
    else
	{
// Print the configured ports on the screen and ask user to choose the port to reset the statistic or disconnect.
// Right now, it lists all the ports  and lets the user pick up the port. A good idea is to let user only delete
// connected ports.
	printf("Select to C - Clear Statistic, D - Disconnect Port Q - Quit\n");
	do
		     {option=_getch();
		       option =toupper(option);
		      printf("%c\n",option);}   while (((option) != 'C') && ((option) != 'D') && ((option) != 'Q'));
	if (option == 'Q')
	   {
		  Quit = TRUE;
	     }              
	if (option == 'C')
	   {
// Print all the ports and then let user  choose the port to clear statistics
	 i = 0;         
	 while (i < Entries)
	      {
	      while ((i < Entries) && (k <=5))
		  {
//Better to check if the port is connected here
		  printf(" %d=%ws",i,pRasPort0[i].wszPortName);
		  i++;
		  k++;
		  }
	      printf("\n");
	      k=1;
	      }
	  printf("Enter your option 0 - %d  ",Entries-1);
	  while ((scanf("%i",&PortOption) < 0) && (scanf("%i",&PortOption)> Entries-1))
	       {};

	  PrintClearStats(RasSrv, pRasPort0[PortOption].wszPortName);          
	  }
	if (option == 'D')
	   {
// Print all the ports and then let user  choose the port to clear statistics
	 i = 0;         
	 while (i < Entries)
	      {
	      while ((i < Entries) && (k <=5))
		  {
//better to check if the port is connected here
		  printf(" %d=%ws",i,pRasPort0[i].wszPortName);
		  i++;
		  k++;
		  }
	      printf("\n");
	      k=1;
	      }
	  printf("Enter your option 0 - %d ",Entries-1);
	  while ((scanf("%i",&PortOption) < 0) && (scanf("%i",&PortOption) > Entries-1))
	       {};

// API Called:     RasAdmimPortDisconnect
// Parameters:
//  IN WCHAR * lpszServerName
// IN WCHAR * lpszPortName

	  Status = RasAdminPortDisconnect(RasSrv, pRasPort0[PortOption].wszPortName);
    if (Status != ERROR_SUCCESS)
	{
	sprintf(szBuf, "ERROR RasAdminPortDisconnect   %d\n",Status);
	dwResult = RasAdminGetErrorString((UINT) Status, lpszString, 512);
	if (dwResult == ERROR_SUCCESS)
	    {
	    sprintf(szBuf,"ERROR  RasAdminPortDisconnect      %ws\n",lpszString);
	    WriteFile(cLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	    sprintf(szBuf, "ERROR  RasAdminPortDisconnect      %ws\n",lpszString);     
	    WriteFile(cLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	    }
	 else
	    PrintGetStringError(dwResult);
	}
    else
	{
	printf("Port Disconnected successfully\n");
	}
     }
   }
 if (pRasPort0 != NULL)
     RasAdminFreeBuffer(pRasPort0);
  }
return(0);
}

void _cdecl main(int argc, char **argv)
{
INT LoopPriv=0;
INT Error = 0;
CHAR szBuf[120];
DWORD dwBytesWritten=0;
DWORD Dialin = 1;
WCHAR Buf[512];
WCHAR *lpszString;
WORD Entries;
WORD i=0;
DWORD id=0;
HANDLE ConnectDiscThread;
lpszString=&Buf[0];
pRasPort1 = &RasPort1;
pRasStats = &RasStats;
pRasServer0 = &RasServer0;
ppRasUser0 = &RasUser0;
if (argc > 1)
    {
    mbstowcs(RasSrv, argv[1], 32) ;
    }
else
    {
    printf ("to start type Admapit \\\\RasServerName\n");
    exit(0);
    }
Init1();
Init2();
Error=ServerGetInfo(RasSrv);
if (Error)
    {
    printf ("Ras Server is not started on the system");
    exit(0);
    }
    ConnectDiscThread = CreateThread (NULL,
					 0,
			&RasAdminClearDisc,
			       (LPVOID) id,
					 0,
				       &id);

while (!Quit)
  {
// API Called:     RasAdmimPortEnum
// Parameters:
//  IN WCHAR * lpszServerName
// OUT PRAS_PORT_0 *  ppRasPort0
// OUT WORD *  pcEntriesRead

// Free up ppRasPort0 by calling RasAdminFreeBuffer API

    Status = RasAdminPortEnum( RasSrv, &pRasPort0, &Entries);
    if (Status != ERROR_SUCCESS)
	{
	sprintf(szBuf, "ERROR RasAdminPortEnum   %d\n",Status);
	      WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	dwResult = RasAdminGetErrorString((UINT) Status, lpszString, 512);
	if (dwResult == ERROR_SUCCESS)
	    {
	    sprintf(szBuf,"ERROR  RasAdminPortEnum      %ws\n",lpszString);
	    WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	    sprintf(szBuf, "ERROR  RasAdminPortEnum      %ws\n",lpszString);     
	    WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	    }
	 else
	    PrintGetStringError(dwResult);
	}
    else
	{
//A good idea is to check for port Authentication before making this call
	for (i=0; i<Entries; i++)
	     {
// API Called:     RasAdmimPortGetInfo
// Parameters:
//  IN WCHAR * lpszUserAccountServer
// IN WCHAR * lpszPortName
// OUT RAS_PORT_1 * pRasPort1
// OUT RAS_PORT_STATISTICS * pRasPortStatistics
// OUT RAS_PARAMETERS ** ppRasParams

// ppRasParams should be freed by calling RasAdminFreeBuffer

	     Status = RasAdminPortGetInfo ( RasSrv, pRasPort0[i].wszPortName, pRasPort1, pRasStats, &pRasParams); 
	     if (Status != ERROR_SUCCESS)       
		{
		 sprintf(szBuf, "ERROR RasAdminGetInfo   %d\n",Status);
		 WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
		 dwResult = RasAdminGetErrorString((UINT) Status, lpszString, 512);
		 if (dwResult == ERROR_SUCCESS)
		     {
		     DbgPrint("ERROR  RasAdminPortGetInfo      %ws\n",lpszString);
		     sprintf(szBuf, "ERROR  RasAdminPortGetInfo      %ws\n",lpszString);     
		     WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
		     }
		 else
		    PrintGetStringError(dwResult);
		}
	     else
		{
		 File_Print(pRasPort1, pRasStats, pRasParams);
			     Debug_Print(pRasPort1, pRasStats, pRasParams);
		}
//Call user privilege API only if the user is connected, or you provide the user name. If you pass NULL for all the paramters to user priv API's then the API
// will hit an Assert
		   if ( pRasPort1->LineCondition == RAS_PORT_AUTHENTICATED)
			     UserPrivilege();
	     if (pRasParams != NULL) {
		    RasAdminFreeBuffer(pRasParams);
		    }
	     }//End Loop
	} 
     CloseHandle(LogFile);
     if (pRasPort0 != NULL)
		RasAdminFreeBuffer(pRasPort0);
     Sleep(sleeptime);
     Init1();
     ServerGetInfo(RasSrv);
  } 

	  WaitForSingleObject(ConnectDiscThread,INFINITE);
CloseHandle(LogFile);
CloseHandle(cLogFile);
CloseHandle(ErrLogFile);

  

} // Main End
