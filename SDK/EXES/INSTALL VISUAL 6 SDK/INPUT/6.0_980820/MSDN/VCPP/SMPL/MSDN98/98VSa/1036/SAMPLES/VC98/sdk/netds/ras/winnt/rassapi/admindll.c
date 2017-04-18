/******************************************************************************
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1992 - 1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       RasAdmin API usage and  is meant to help user with
*       RasAdmin API Calling convention. Use this code at your own risk. 
*       Microsoft disclaims any implied warranty. This sample code can
*       be copied and distributed.
 
******************************************************************************/

/********************************************************************
*  admindll.c -- Sample program demonstrating the use of RasAdmin
*                     CallOut API's
*                                                                    
*****************************************************************************/
/***************************************************************************
*  Functions:
*        Init(void);
*        Init2(void);
*****************************************************************************/

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <lm.h>
#include <stdio.h>
#include <time.h>
#include <rassapi.h>
#include <memory.h>
WCHAR*
StrDupWFromA(
    CHAR* psz );



#define Number_Of_Flags 6
#define Num_Ip_Address 256
#define ConstIpAddress 0x010A0F0E
HANDLE IPFile = NULL;
HANDLE ConDisFile = NULL;
HANDLE ErrLogFile = NULL;
HANDLE ErrLogFileIP = NULL;
BOOL IPFileInValid = FALSE;
BOOL ConnectDisconnectInValid = FALSE;
BOOL ErrorLogInValid = FALSE;
BOOL ErrLogIPInValid = FALSE;
VOID File_Print(RAS_PORT_1 *            pRasPort1,
    RAS_PORT_STATISTICS *   pRasStats,
    RAS_PARAMETERS *        pRasParams
);
VOID Debug_Print(RAS_PORT_1 *            pRasPort1,
    RAS_PORT_STATISTICS *   pRasStats,
    RAS_PARAMETERS *        pRasParams
);
VOID Init(void);
VOID Init2(void);
typedef struct Static_IP_Database
	{
	WCHAR wszUserName[UNLEN+1];
	WCHAR wszPortName[RASSAPI_MAX_PORT_NAME];
	DWORD IpAddress;
	} Static_IP_Database;
Static_IP_Database  Static_IP[Num_Ip_Address];

typedef struct Static_Statistic{
	      BOOL bTaken;
	WCHAR wszUserName[UNLEN+1];
	WCHAR wszPortName[RASSAPI_MAX_PORT_NAME];
	DWORD NumMediaParms;
	DWORD SizeMediaParms;
	DWORD dwStartSessionTime;
	RAS_PORT_STATISTICS  pRasStats;
	      RAS_PARAMETERS        pRasParams;
	} Static_Statistic;

Static_Statistic  Static_Check_Stats[Num_Ip_Address];
BOOL First_Call = TRUE;

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
    if (IsTextUnicode(Format, sizeof(marker),lpResult))
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







//Called from RasAdminGetIpAddressForUser which in trun gets called by RasMan
VOID Init(void)
{
INT i=0;
		  
	     IPFile = CreateFile(TEXT("IpAddress.log"),
				GENERIC_READ|GENERIC_WRITE,
				FILE_SHARE_READ,
				(LPSECURITY_ATTRIBUTES) NULL,
				CREATE_ALWAYS,
				0,
			       (HANDLE) NULL);
	     if (IPFile== INVALID_HANDLE_VALUE) {
		IPFileInValid = TRUE;
	    }
	     ErrLogFileIP = CreateFile(TEXT("IpAddError.log"),
				GENERIC_READ|GENERIC_WRITE,
				FILE_SHARE_READ,
				(LPSECURITY_ATTRIBUTES) NULL,
				CREATE_ALWAYS,
				0,
			       (HANDLE) NULL);
	     if (ErrLogFileIP== INVALID_HANDLE_VALUE) {
		ErrLogIPInValid = TRUE;
	    }
	    
//First call initialize my Stats Database, I Fill out the struct if Call is Accepted the call.
    First_Call=FALSE;
}
//Called by RasAdminAcceptNewConnection which in trun gets called by RAS Server (Rassrv)
VOID Init2(void)
{
INT i=0;
	     ConDisFile = CreateFile(TEXT("ConDis.log"),
				GENERIC_READ|GENERIC_WRITE,
				FILE_SHARE_READ,
				(LPSECURITY_ATTRIBUTES) NULL,
				OPEN_ALWAYS,
				0,
			       (HANDLE) NULL);
	     if (ConDisFile== INVALID_HANDLE_VALUE) {
		  ConnectDisconnectInValid = TRUE;        
	    }
	     ErrLogFile = CreateFile(TEXT("AdminErr.log"),
				GENERIC_READ|GENERIC_WRITE,
				FILE_SHARE_READ,
				(LPSECURITY_ATTRIBUTES) NULL,
				OPEN_ALWAYS,
				0,
			       (HANDLE) NULL);
	     if (ErrLogFile == INVALID_HANDLE_VALUE) {
		ErrorLogInValid = TRUE;
	    }
    for (i=0;i < Num_Ip_Address; i++);
	  Static_Check_Stats[i].bTaken=FALSE;
}


DWORD
APIENTRY
RasAdminGetIpAddressForUser(
    IN WCHAR *      lpwszUserName,
    IN WCHAR *      lpwszPortName,
    IN OUT IPADDR * pIpAddress,
    OUT BOOL *      pfNotifyDLL
)
{
DWORD i=0;
DWORD dwBytesWritten=0;
CHAR buf[120];
//to check if the call is first rasman call out. If yes, call Initialize routine
    if (First_Call) Init();
    DbgPrint("First_Call  %d\n",First_Call);
    DbgPrint("\nGetIpAddressForUser called UserName=%ws,Port=%ws,IpAddress=%d\n",
	      lpwszUserName,lpwszPortName,(DWORD)*pIpAddress );

    for (i=1;i < Num_Ip_Address;i++)
	{
	if (Static_IP[i].IpAddress != 1)
	    {
	     Static_IP[i].IpAddress = 1;
	     wcscpy(Static_IP[i].wszUserName, lpwszUserName);
	     wcscpy(Static_IP[i].wszPortName, lpwszPortName);
	     *pIpAddress = i + ConstIpAddress;
	      break;
	    }
	}
    if (IPFileInValid)
	 {
	 DbgPrint("GetIpAddressForUser setting IpAddress=%d\n",(DWORD)*pIpAddress );
	 }
    else
	{
	 sprintf(buf,"GetIpAddressForUser setting IpAddress=%d\n",(DWORD)*pIpAddress );
	       WriteFile(IPFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	
	      } 
    *pfNotifyDLL = TRUE;
    
    return( NO_ERROR );
}


VOID
APIENTRY
RasAdminReleaseIpAddress(
    IN WCHAR *      lpwszUserName,
    IN WCHAR *      lpwszPortName,
    IN OUT IPADDR * pIpAddress
)
{
DWORD dwBytesWritten=0;
CHAR buf[120];
    DbgPrint( "\nReleaseIpAddressr called UserName=%ws,Port=%ws,IpAddress=%d\n",
	      lpwszUserName,lpwszPortName,(DWORD)*pIpAddress );
     if (wcscmp(Static_IP[(DWORD)*pIpAddress-ConstIpAddress].wszUserName,lpwszUserName) == 0)
	 {
	  if (wcscmp(Static_IP[(DWORD)*pIpAddress-ConstIpAddress].wszPortName,lpwszPortName) == 0)
	      {
	       Static_IP[(DWORD)*pIpAddress-ConstIpAddress].IpAddress = 0;
	      }
	      else
	      {
	       DbgPrint("ERROR ReleaseIP PortName Incorrect, Cannot free IP Address       %ws\n",Static_IP[(DWORD)*pIpAddress-ConstIpAddress].wszPortName);
	       if (!(ErrLogIPInValid))
			    {
		 sprintf(buf,"ERROR ReleaseIP PortName Incorrect, Cannot free IP Address       %ws\n",Static_IP[(DWORD)*pIpAddress-ConstIpAddress].wszPortName);
			    WriteFile(ErrLogFileIP, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
			    }
	      }
	 }
	 else
	 {
	 DbgPrint("ERROR ReleaseIP UserName Incorrect, Cannot free IP Address       %ws\n",Static_IP[(DWORD)*pIpAddress-ConstIpAddress].wszUserName);
	 if (!(ErrLogIPInValid))
		   {
	     sprintf(buf,"ERROR ReleaseIP UserName Incorrect, Cannot free IP Address       %ws\n",Static_IP[(DWORD)*pIpAddress-ConstIpAddress].wszUserName);
		   WriteFile(ErrLogFileIP, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
		   }
	 } 
}


BOOL
APIENTRY
RasAdminAcceptNewConnection(
    RAS_PORT_1 *            pRasPort1,
    RAS_PORT_STATISTICS *   pRasStats,
    RAS_PARAMETERS *        pRasParams
)
{
INT i=0;
DWORD dwResult;
WCHAR szUserAccountServer[UNLEN+1];
PRAS_USER_0 ppRasUser0;
RAS_USER_0 RasUser0;
WCHAR Buf[512];
WCHAR *lpszString;
DWORD dwBytesWritten=0;
CHAR szBuf[120];
WCHAR lpszServerName[50];
DWORD Permission;
lpszString = &Buf[0];
ppRasUser0 = &RasUser0;

//to check if the call is first rassrv call out. If yes, call Initialize routine

if (First_Call) {Init2(); First_Call = FALSE;}
DbgPrint("ConnectDisconnect   %d\n",ConDisFile);
DbgPrint("ConnectDisconnectInValid %d\n",ConnectDisconnectInValid);
DbgPrint("ErrorLogFile   %d\n",ErrLogFile);
DbgPrint("ErrorLogInValid %d\n",ErrorLogInValid);
if (ConnectDisconnectInValid)
   {
    DbgPrint( "\nRasAdminAcceptNewConnection called \n" );
    Debug_Print( pRasPort1, pRasStats, pRasParams);
  }
else
  {
    sprintf(szBuf, "\nRasAdminAcceptNewConnection called \n" );
    WriteFile(ConDisFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
    File_Print( pRasPort1, pRasStats, pRasParams);
  }
   if (pRasPort1->rasport0.fAdvancedServer > 0){
  dwResult = RasAdminGetUserAccountServer(pRasPort1->rasport0.wszLogonDomain, NULL, &szUserAccountServer[0]);}
  else {  
      lstrcpy(lpszServerName, TEXT("\\\\"));
      lstrcat(&lpszServerName[0], pRasPort1->rasport0.wszLogonDomain);
      DbgPrint("%ws\n",lpszServerName);
      dwResult = RasAdminGetUserAccountServer(NULL, &lpszServerName[0], &szUserAccountServer[0]);
      }

  if (dwResult == ERROR_SUCCESS)
     {
     DbgPrint("UserAccount Succeeded\n");
     dwResult = RasAdminUserGetInfo(szUserAccountServer, pRasPort1->rasport0.wszUserName, ppRasUser0);
     if (dwResult == ERROR_SUCCESS)
	 {
	       DbgPrint("AdminUserGetInfo Succeeded");
	       DbgPrint(" Priviledge   %d\n",ppRasUser0->bfPrivilege);
	       Permission = ppRasUser0->bfPrivilege - (ppRasUser0->bfPrivilege & RASPRIV_DialinPrivilege);
	       DbgPrint("Permission %d\n",Permission);
	 if (Permission == RASPRIV_AdminSetCallback || Permission == RASPRIV_CallerSetCallback)
	    {
	    DbgPrint ("Don't Accept Call\n");
	    return (FALSE);
	    }
	 }
     else
	{
	      DbgPrint("RasAdminUserGetInfo     %d\n",dwResult);
		dwResult = RasAdminGetErrorString((UINT) dwResult, lpszString, 512);
	if (dwResult == ERROR_SUCCESS)
	    {
	    DbgPrint("ERROR  RasAdminUserGetInfo      %s\n",lpszString);
	     sprintf(szBuf, "ERROR  RasAdminUserGetInfo      %s\n",lpszString);     
		  WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	    }
	 else
	    {
	    DbgPrint("ERROR  RasAdminGetErrorString      %d\n",dwResult);
	    sprintf(szBuf, "ERROR  RasAdminGetErrorString      %d\n",dwResult);     
		  WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	    }
	 }
    }
  else
    {
    DbgPrint("RasAdminGetUserAccountServer     %d\n",dwResult);
    dwResult = RasAdminGetErrorString((UINT)dwResult, lpszString, 512);
     if (dwResult == ERROR_SUCCESS)
	  {
	  DbgPrint("ERROR  RasAdminUserAccountServer      %s\n",lpszString);
	  sprintf(szBuf, "ERROR  RasAdminUserAccountServer      %s\n",lpszString);     
		WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	  }
	  else
	    {
	    DbgPrint("ERROR  RasAdminGetErrorString      %d\n",dwResult);
	    sprintf(szBuf, "ERROR  RasAdminGetErrorString      %d\n",dwResult);     
		  WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
	    }
    }

  if (( lstrcmp( pRasPort1->rasport0.wszUserName, TEXT("Administrator") ) ) == 0)
       {
	DbgPrint("Do not Accept Connection\n");
	      FlushFileBuffers(ErrLogFile);
	      FlushFileBuffers(ConDisFile);
	return( FALSE );
       }
    else
       {
	  for (i=0;i < Num_Ip_Address; i++)
	     if (!(Static_Check_Stats[i].bTaken))
		  {
		   wcscpy(Static_Check_Stats[i].wszUserName, pRasPort1->rasport0.wszUserName);
		   wcscpy(Static_Check_Stats[i].wszPortName, pRasPort1->rasport0.wszPortName);
			       Static_Check_Stats[i].bTaken = TRUE;
		   Static_Check_Stats[i].NumMediaParms = pRasPort1->NumMediaParms;
		   Static_Check_Stats[i].SizeMediaParms = pRasPort1->SizeMediaParms;
		   Static_Check_Stats[i].dwStartSessionTime = pRasPort1->rasport0.dwStartSessionTime;
		   memcpy(&Static_Check_Stats[i].pRasStats,pRasStats, sizeof(RAS_PORT_STATISTICS));
		   memcpy(&Static_Check_Stats[i].pRasParams,pRasParams, sizeof(pRasParams));
		   break;
		  }
       DbgPrint("Accept Connection\n");
       FlushFileBuffers(ErrLogFile);
       FlushFileBuffers(ConDisFile);
       return( TRUE );
       }
}

VOID
APIENTRY
RasAdminConnectionHangupNotification(
    RAS_PORT_1 *            pRasPort1,
    RAS_PORT_STATISTICS *   pRasStats,
    RAS_PARAMETERS *        pRasParams
)
{
INT i=0;
DWORD dwBytesWritten=0;
CHAR buf[120];
//if (First_Call) Init2();
if (ConnectDisconnectInValid)
   {
    DbgPrint( "\nRasAdminConnectionHangupNotification called \n" );
    Debug_Print( pRasPort1, pRasStats, pRasParams);
  }
else
  {
    sprintf(buf, "\nRasAdminConnectionHangupNotification called \n" );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    File_Print( pRasPort1, pRasStats, pRasParams);
  }


//Sanity checks
      for (i=0; i < Num_Ip_Address; i++)
       {
	if (Static_Check_Stats[i].bTaken)
	     {
	      if (wcscmp(Static_Check_Stats[i].wszPortName,pRasPort1->rasport0.wszPortName) == 0)
		  {
			if (ErrorLogInValid)
		   {       
		   if (wcscmp(Static_Check_Stats[i].wszUserName,pRasPort1->rasport0.wszUserName) != 0)
			DbgPrint("ERROR User Name Differs    %ws ->Passed,   %ws ->Stored\n",pRasPort1->rasport0.wszUserName,Static_Check_Stats[i].wszUserName);
			       Static_Check_Stats[i].bTaken = FALSE;
		   if (Static_Check_Stats[i].NumMediaParms != pRasPort1->NumMediaParms)
			 DbgPrint("ERROR NumMediaParm    %d ->Passed,   %d  ->Stored\n",Static_Check_Stats[i].NumMediaParms != pRasPort1->NumMediaParms);
		   if (Static_Check_Stats[i].SizeMediaParms != pRasPort1->SizeMediaParms)
			 DbgPrint("ERROR SizeMediaParm    %d ->Passed,   %d  ->Stored\n",Static_Check_Stats[i].SizeMediaParms != pRasPort1->SizeMediaParms);
		   if (Static_Check_Stats[i].dwStartSessionTime != pRasPort1->rasport0.dwStartSessionTime)
			 DbgPrint("ERROR StartSessionTime    %d ->Passed,   %d  ->Stored\n",Static_Check_Stats[i].dwStartSessionTime, pRasPort1->rasport0.dwStartSessionTime);
		   if (pRasStats->dwBytesXmited < Static_Check_Stats[i].pRasStats.dwBytesXmited) 
			  DbgPrint( "ERROR dwBytesXmited Passed=%d   , dwBytesXmited Stored=%d\n", pRasStats->dwBytesXmited,Static_Check_Stats[i].pRasStats.dwBytesXmited);
		   if (pRasStats->dwBytesRcved < Static_Check_Stats[i].pRasStats.dwBytesRcved) 
			  DbgPrint( "ERROR dwBytesRcved Passed=%d    , dwBytesRcved Stored=%d\n", pRasStats->dwBytesRcved,Static_Check_Stats[i].pRasStats.dwBytesRcved );
		   if (pRasStats->dwFramesXmited < Static_Check_Stats[i].pRasStats.dwFramesXmited) 
			 DbgPrint( "ERROR dwFramesXmited Passed=%d , dwFramesXmited Stored=%d\n", pRasStats->dwFramesXmited,Static_Check_Stats[i].pRasStats.dwFramesXmited );
		   if (pRasStats->dwFramesRcved < Static_Check_Stats[i].pRasStats.dwFramesRcved) 
			 DbgPrint( "ERROR dwFramesRcved Passed=%d , dwFramesRcved Stored=%d\n", pRasStats->dwFramesRcved,Static_Check_Stats[i].pRasStats.dwFramesRcved);
		   if (pRasStats->dwCrcErr < Static_Check_Stats[i].pRasStats.dwCrcErr) 
			DbgPrint( "ERROR dwCrcErr Passed=%d , dwCrcErr Stored=%d\n", pRasStats->dwCrcErr,Static_Check_Stats[i].pRasStats.dwCrcErr);
		   if (pRasStats->dwTimeoutErr < Static_Check_Stats[i].pRasStats.dwTimeoutErr) 
			DbgPrint( "ERROR dwTimeoutErr Passed=%d  , dwTimeoutErr Stored=%d\n", pRasStats->dwTimeoutErr,Static_Check_Stats[i].pRasStats.dwTimeoutErr);
		   if (pRasStats->dwAlignmentErr < Static_Check_Stats[i].pRasStats.dwAlignmentErr) 
			DbgPrint( "ERROR dwAlignmentErr Passed=%d , dwAlignmentErr Stored=%d\n", pRasStats->dwAlignmentErr,Static_Check_Stats[i].pRasStats.dwAlignmentErr);
		   if (pRasStats->dwHardwareOverrunErr < Static_Check_Stats[i].pRasStats.dwHardwareOverrunErr) 
			DbgPrint( "ERROR dwHardwareOverrunErr Passed=%d  , dwHardwareOverrunErr Stored=%d\n", pRasStats->dwHardwareOverrunErr,Static_Check_Stats[i].pRasStats.dwHardwareOverrunErr);
		   if (pRasStats->dwFramingErr < Static_Check_Stats[i].pRasStats.dwFramingErr) 
		       DbgPrint( "ERROR dwFramingErr Passed=%d , dwFramingErr Stored=%d\n", pRasStats->dwFramingErr,Static_Check_Stats[i].pRasStats.dwFramingErr);
		   if (pRasStats->dwBufferOverrunErr < Static_Check_Stats[i].pRasStats.dwBufferOverrunErr) 
		       DbgPrint( "ERROR dwBufferOverrunErr Passed=%d , dwBufferOverrunErr Stored=%d\n", pRasStats->dwBufferOverrunErr,Static_Check_Stats[i].pRasStats.dwBufferOverrunErr);
		   if (pRasStats->dwBytesXmitedUncompressed < Static_Check_Stats[i].pRasStats.dwBytesXmitedUncompressed) 
		       DbgPrint( "ERROR dwBytesXmitedUncompressed Passed=%d   ,  dwBytesXmitedUncompressed Stored=%d\n",
				    pRasStats->dwBytesXmitedUncompressed,Static_Check_Stats[i].pRasStats.dwBytesXmitedUncompressed);
		   if (pRasStats->dwBytesRcvedUncompressed < Static_Check_Stats[i].pRasStats.dwBytesRcvedUncompressed) 
		       DbgPrint( "ERROR dwBytesRcvedUncompressed  Passed=%d    ,dwBytesRcvedUncompressed Stored=%d\n",
				    pRasStats->dwBytesRcvedUncompressed,Static_Check_Stats[i].pRasStats.dwBytesRcvedUncompressed);
		   if (pRasStats->dwBytesXmitedCompressed < Static_Check_Stats[i].pRasStats.dwBytesXmitedCompressed) 
		       DbgPrint( "ERROR dwBytesXmitedCompressed Passed=%d   ,dwBytesXmitedCompressed Stored=%d\n",
				    pRasStats->dwBytesXmitedCompressed,Static_Check_Stats[i].pRasStats.dwBytesXmitedCompressed);
		   if (pRasStats->dwBytesRcvedCompressed < Static_Check_Stats[i].pRasStats.dwBytesRcvedCompressed) 
		      DbgPrint( "ERROR dwBytesRcvedCompressed Passed=%d    ,dwBytesRcvedCompressed Stored=%d\n",
				    pRasStats->dwBytesRcvedCompressed,Static_Check_Stats[i].pRasStats.dwBytesRcvedCompressed);
			      if (memcmp(&Static_Check_Stats[i].pRasParams,pRasParams, sizeof(pRasParams)) != 0)
		      DbgPrint( "ERROR RASParams Passed   &  RASParasms Stored are different\n");
			 }
		     else
			 {
		   if (wcscmp(Static_Check_Stats[i].wszUserName,pRasPort1->rasport0.wszUserName) != 0)
			{sprintf(buf,"ERROR User Name Differs    %ws ->Passed,   %ws ->Stored\n",pRasPort1->rasport0.wszUserName,Static_Check_Stats[i].wszUserName);
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					  }
			       Static_Check_Stats[i].bTaken = FALSE;
		   if (Static_Check_Stats[i].NumMediaParms != pRasPort1->NumMediaParms)
			 {sprintf(buf,"ERROR NumMediaParm    %d ->Passed,   %d  ->Stored\n",Static_Check_Stats[i].NumMediaParms != pRasPort1->NumMediaParms);
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					  }
		   if (Static_Check_Stats[i].SizeMediaParms != pRasPort1->SizeMediaParms)
			 {sprintf(buf,"ERROR SizeMediaParm    %d ->Passed,   %d  ->Stored\n",Static_Check_Stats[i].SizeMediaParms != pRasPort1->SizeMediaParms);
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					  }
		   if (Static_Check_Stats[i].dwStartSessionTime != pRasPort1->rasport0.dwStartSessionTime)
			 {sprintf(buf,"ERROR StartSessionTime    %d ->Passed,   %d  ->Stored\n",Static_Check_Stats[i].dwStartSessionTime != pRasPort1->rasport0.dwStartSessionTime);
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					  }
		   if (pRasStats->dwBytesXmited < Static_Check_Stats[i].pRasStats.dwBytesXmited) 
			 { sprintf(buf, "ERROR dwBytesXmited Passed=%d   , dwBytesXmited Stored=%d\n", pRasStats->dwBytesXmited,Static_Check_Stats[i].pRasStats.dwBytesXmited);
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					  }
		   if (pRasStats->dwBytesRcved < Static_Check_Stats[i].pRasStats.dwBytesRcved) 
			 { sprintf(buf, "ERROR dwBytesRcved Passed=%d    , dwBytesRcved Stored=%d\n", pRasStats->dwBytesRcved,Static_Check_Stats[i].pRasStats.dwBytesRcved );
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					  }
		   if (pRasStats->dwFramesXmited < Static_Check_Stats[i].pRasStats.dwFramesXmited) 
			 {sprintf(buf, "ERROR dwFramesXmited Passed=%d , dwFramesXmited Stored=%d\n", pRasStats->dwFramesXmited,Static_Check_Stats[i].pRasStats.dwFramesXmited );
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					  }
		   if (pRasStats->dwFramesRcved < Static_Check_Stats[i].pRasStats.dwFramesRcved) 
			 {sprintf(buf, "ERROR dwFramesRcved Passed=%d , dwFramesRcved Stored=%d\n", pRasStats->dwFramesRcved,Static_Check_Stats[i].pRasStats.dwFramesRcved);
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					  }
		   if (pRasStats->dwCrcErr < Static_Check_Stats[i].pRasStats.dwCrcErr) 
			{sprintf(buf, "ERROR dwCrcErr Passed=%d , dwCrcErr Stored=%d\n", pRasStats->dwCrcErr,Static_Check_Stats[i].pRasStats.dwCrcErr);
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					  }
		   if (pRasStats->dwTimeoutErr < Static_Check_Stats[i].pRasStats.dwTimeoutErr) 
			{sprintf(buf, "ERROR dwTimeoutErr Passed=%d  , dwTimeoutErr Stored=%d\n", pRasStats->dwTimeoutErr,Static_Check_Stats[i].pRasStats.dwTimeoutErr);
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					  }
		   if (pRasStats->dwAlignmentErr < Static_Check_Stats[i].pRasStats.dwAlignmentErr) 
			{sprintf(buf, "ERROR dwAlignmentErr Passed=%d , dwAlignmentErr Stored=%d\n", pRasStats->dwAlignmentErr,Static_Check_Stats[i].pRasStats.dwAlignmentErr);
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					  }
		   if (pRasStats->dwHardwareOverrunErr < Static_Check_Stats[i].pRasStats.dwHardwareOverrunErr) 
			{sprintf(buf, "ERROR dwHardwareOverrunErr Passed=%d  , dwHardwareOverrunErr Stored=%d\n", pRasStats->dwHardwareOverrunErr,Static_Check_Stats[i].pRasStats.dwHardwareOverrunErr);
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					  }
		   if (pRasStats->dwFramingErr < Static_Check_Stats[i].pRasStats.dwFramingErr) 
			      {sprintf(buf, "ERROR dwFramingErr Passed=%d , dwFramingErr Stored=%d\n", pRasStats->dwFramingErr,Static_Check_Stats[i].pRasStats.dwFramingErr);
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					  }
		   if (pRasStats->dwBufferOverrunErr < Static_Check_Stats[i].pRasStats.dwBufferOverrunErr) 
			      {sprintf(buf, "ERROR dwBufferOverrunErr Passed=%d , dwBufferOverrunErr Stored=%d\n", pRasStats->dwBufferOverrunErr,Static_Check_Stats[i].pRasStats.dwBufferOverrunErr);
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					  }
		   if (pRasStats->dwBytesXmitedUncompressed < Static_Check_Stats[i].pRasStats.dwBytesXmitedUncompressed) 
			     { sprintf(buf, "ERROR dwBytesXmitedUncompressed Passed=%d   ,  dwBytesXmitedUncompressed Stored=%d\n",
				    pRasStats->dwBytesXmitedUncompressed,Static_Check_Stats[i].pRasStats.dwBytesXmitedUncompressed);
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					  }
		   if (pRasStats->dwBytesRcvedUncompressed < Static_Check_Stats[i].pRasStats.dwBytesRcvedUncompressed) 
			      {sprintf(buf, "ERROR dwBytesRcvedUncompressed  Passed=%d    ,dwBytesRcvedUncompressed Stored=%d\n",
				    pRasStats->dwBytesRcvedUncompressed,Static_Check_Stats[i].pRasStats.dwBytesRcvedUncompressed);
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					  }
		   if (pRasStats->dwBytesXmitedCompressed < Static_Check_Stats[i].pRasStats.dwBytesXmitedCompressed) 
			      {sprintf(buf, "ERROR dwBytesXmitedCompressed Passed=%d   ,dwBytesXmitedCompressed Stored=%d\n",
				    pRasStats->dwBytesXmitedCompressed,Static_Check_Stats[i].pRasStats.dwBytesXmitedCompressed);
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					  }
		   if (pRasStats->dwBytesRcvedCompressed < Static_Check_Stats[i].pRasStats.dwBytesRcvedCompressed) 
				{ sprintf(buf, "ERROR dwBytesRcvedCompressed Passed=%d    ,dwBytesRcvedCompressed Stored=%d\n",
				    pRasStats->dwBytesRcvedCompressed,Static_Check_Stats[i].pRasStats.dwBytesRcvedCompressed);
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
						     }
			      if (memcmp(&Static_Check_Stats[i].pRasParams,pRasParams, sizeof(pRasParams)) != 0)
				{ sprintf(buf, "ERROR RASParams Passed   &  RASParasms Stored are different\n");
				   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					     }

			  }
				  break;
		    }
	     else
		  {       if (i == 255){
				  if (ErrorLogInValid) 
		       {DbgPrint("ERROR Port Name  Differs    %ws ->Passed,   %ws ->Stored\n",pRasPort1->rasport0.wszPortName,Static_Check_Stats[i].wszPortName);}
		     else
		       {sprintf(buf,"ERROR Port Name  Differs    %ws ->Passed,   %ws ->Stored\n",pRasPort1->rasport0.wszPortName,Static_Check_Stats[i].wszPortName);
					   WriteFile(ErrLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
					  }
			  }
		 }
	       }
     }
    FlushFileBuffers(ErrLogFile);
    FlushFileBuffers(ConDisFile);

}

VOID Debug_Print(RAS_PORT_1 *            pRasPort1,
    RAS_PORT_STATISTICS *   pRasStats,
    RAS_PARAMETERS *        pRasParams
)
{
WCHAR *Media_Name[] = {TEXT("MEDIA_UNKNOWN"),TEXT( "MEDIA_SERIAL"),
		  TEXT("MEDIA_RAS10_SERIAL"),TEXT( "MEDIA_ISDN")};
WCHAR *Flag_Name[] = {TEXT("USER_AUTHENTICATED"),TEXT( "MESSENGER_PRESENT"),
		 TEXT("PPP_CLIENT"),TEXT("GATEWAY_ACTIVE"),TEXT("REMOTE_LISTEN"),TEXT("PORT_MULTILINKED")};
WCHAR *Line_Condition[]={TEXT("RAS_PORT_NON_OPERATIONAL"),TEXT("RAS_PORT_DISCONNECTED"),
		  TEXT("RAS_PORT_CALLING_BACK"),TEXT("RAS_PORT_LISTENING"),TEXT("RAS_PORT_AUTHENTICATING"),
		  TEXT("RAS_PORT_AUTHENTICATED"),TEXT("RAS_PORT_INITIALIZING")};
WCHAR *Hdw_Error[]={TEXT("RAS_MODEM_OPERATIONAL"),TEXT("RAS_MODEM_NOT_RESPONDING"),TEXT("RAS_MODEM_HARDWARE_FAILURE"),
		  TEXT("RAS_MODEM_INCORRECT_RESPONSE"),TEXT("RAS_MODEM_UNKNOWN")};
INT  i=0;
INT temp = 0;
INT temp1 =0;
DWORD dwsize=0;
CHAR szBuf[100];
    DbgPrint( "\nRasAdminAcceptNewConnection called \n" );
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
    DbgPrint("                 %ws\n",Media_Name[pRasPort1->rasport0.reserved]);
    DbgPrint( "pRasPort1->rasport0.Flags=%d\n",
			pRasPort1->rasport0.Flags );
//printing Flags
    temp1 = 1;
    for (i=0; i <= Number_Of_Flags; i++)
	 {
	 temp = (pRasPort1->rasport0.Flags & temp1);
	 if (temp)
	     {
	       DbgPrint("Flag       %ws   \n",Flag_Name[i]);
	     }
	  temp1 = temp1*2;
	 }
    DbgPrint( "pRasPort1->rasport0.wszUserName=%ws\n",
			pRasPort1->rasport0.wszUserName );
    DbgPrint( "pRasPort1->rasport0.wszComputer=%ws\n",
			pRasPort1->rasport0.wszComputer );
    DbgPrint( "pRasPort1->rasport0.dwStartSessionTime;=%d\n",
		    pRasPort1->rasport0.dwStartSessionTime );
    DbgPrint("Formatted session start time/date :  %s\n",ctime(&pRasPort1->rasport0.dwStartSessionTime));
    DbgPrint( "pRasPort1->rasport0.wszLogonDomain=%ws\n",
		    pRasPort1->rasport0.wszLogonDomain );
    DbgPrint( "pRasPort1->rasport0.fAdvancedServer=%d\n",
		    pRasPort1->rasport0.fAdvancedServer );
    DbgPrint( "pRasPort1->LineCondition=%d\n", pRasPort1->LineCondition );
    DbgPrint("                     %ws\n",Line_Condition[pRasPort1->LineCondition-1]);
    DbgPrint( "pRasPort1->HardwareCondition=%d\n",pRasPort1->HardwareCondition);
    DbgPrint("                     %ws\n",Hdw_Error[pRasPort1->HardwareCondition-1]);
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
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf,"pRasPort1->rasport0.wszDeviceType=%ws\n",
		    pRasPort1->rasport0.wszDeviceType );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf,"pRasPort1->rasport0.wszDeviceName=%ws\n",
		    pRasPort1->rasport0.wszDeviceName );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->rasport0.wszMediaName=%ws\n",
		pRasPort1->rasport0.wszMediaName );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf,"pRasPort1->rasport0.reserved=%d\n",
		    pRasPort1->rasport0.reserved );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf,"                 %s\n",Media_Name[pRasPort1->rasport0.reserved]);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->rasport0.Flags=%d\n",
			pRasPort1->rasport0.Flags );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
//printing Flags
    temp1 = 1;
    for (i=0; i <= Number_Of_Flags; i++)
	 {
	 temp = (pRasPort1->rasport0.Flags & temp1);
	 if (temp)
	     {
	       sprintf(buf,"Flag       %s   \n",Flag_Name[i]);
		     WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	     }
	  temp1 = temp1*2;
	 }
    sprintf(buf, "pRasPort1->rasport0.wszUserName=%ws\n",
			pRasPort1->rasport0.wszUserName );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->rasport0.wszComputer=%ws\n",
			pRasPort1->rasport0.wszComputer );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->rasport0.dwStartSessionTime;=%d\n",
		    pRasPort1->rasport0.dwStartSessionTime );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf,"Formatted session start time/date :  %s\n",ctime(&pRasPort1->rasport0.dwStartSessionTime));
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->rasport0.wszLogonDomain=%ws\n",
		    pRasPort1->rasport0.wszLogonDomain );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->rasport0.fAdvancedServer=%d\n",
		    pRasPort1->rasport0.fAdvancedServer );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->LineCondition=%d\n", pRasPort1->LineCondition );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf,"                     %s\n",Line_Condition[pRasPort1->LineCondition-1]);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->HardwareCondition=%d\n",pRasPort1->HardwareCondition);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf,"                     %s\n",Hdw_Error[pRasPort1->HardwareCondition-1]);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->LineSpeed=%d   bits/sec\n",pRasPort1->LineSpeed);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->NumStatistics=%d\n",pRasPort1->NumStatistics);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->NumMediaParms=%d\n",pRasPort1->NumMediaParms);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "pRasPort1->SizeMediaParms=%d\n",pRasPort1->SizeMediaParms);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "\npRasPort1->ProjResult.nbf.dwError=%d\n",
					pRasPort1->ProjResult.nbf.dwError );
    if (pRasPort1->ProjResult.nbf.dwError == NO_ERROR)
       {
	sprintf(buf, "pRasPort1->ProjResult.nbf.dwNetBiosError=%d\n",
			    pRasPort1->ProjResult.nbf.dwNetBiosError );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	sprintf(buf, "pRasPort1->ProjResult.nbf.szName=%s\n", 
				    pRasPort1->ProjResult.nbf.szName );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	sprintf(buf, "pRasPort1->ProjResult.nbf.wszWksta=%ws\n",
				    pRasPort1->ProjResult.nbf.wszWksta );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
      }
   sprintf(buf, "pRasPort1->ProjResult.ip.dwError=%d\n", 
					pRasPort1->ProjResult.ip.dwError );
   WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   if (pRasPort1->ProjResult.ip.dwError == NO_ERROR)
      { 
	sprintf(buf, "pRasPort1->ProjResult.ip.wszAddress=%ws\n",
				pRasPort1->ProjResult.ip.wszAddress );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
       }
    sprintf(buf, "pRasPort1->ProjResult.ipx.dwError=%d\n",
				pRasPort1->ProjResult.ipx.dwError );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    if (pRasPort1->ProjResult.ipx.dwError == NO_ERROR)
      {
	     sprintf(buf, "pRasPort1->ProjResult.ipx.wszAddress=%ws\n",
			pRasPort1->ProjResult.ipx.wszAddress );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
      }
    sprintf(buf, "pRasPort1->ProjResult.at.dwError=%d\n",
				pRasPort1->ProjResult.at.dwError );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    if (pRasPort1->ProjResult.at.dwError == NO_ERROR)
      {
	      sprintf(buf, "pRasPort1->ProjResult.at.wszAddress=%ws\n",
			pRasPort1->ProjResult.at.wszAddress );
       }
    sprintf(buf, "\ndwBytesXmited=%d\n", pRasStats->dwBytesXmited );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwBytesRcved=%d\n", pRasStats->dwBytesRcved );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwFramesXmited=%d\n", pRasStats->dwFramesXmited );
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwFramesRcved=%d\n", pRasStats->dwFramesRcved);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwCrcErr=%d\n", pRasStats->dwCrcErr);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwTimeoutErr=%d\n", pRasStats->dwTimeoutErr);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwAlignmentErr=%d\n", pRasStats->dwAlignmentErr);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwHardwareOverrunErr=%d\n", pRasStats->dwHardwareOverrunErr);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwFramingErr=%d\n", pRasStats->dwFramingErr);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwBufferOverrunErr=%d\n", pRasStats->dwBufferOverrunErr);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwBytesXmitedUncompressed=%d\n", 
				    pRasStats->dwBytesXmitedUncompressed);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwBytesRcvedUncompressed=%d\n", 
				    pRasStats->dwBytesRcvedUncompressed);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwBytesXmitedCompressed=%d\n", 
				    pRasStats->dwBytesXmitedCompressed);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    sprintf(buf, "dwBytesRcvedCompressed=%d\n", 
				    pRasStats->dwBytesRcvedCompressed);
    WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
    for (i=0; i<pRasPort1->NumMediaParms;i++)
      {
      sprintf(buf, "pRasParams->P_Key= %s\n",pRasParams[i].P_Key);
      WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
      sprintf(buf, "pRasParams->P_Type= %d\n",pRasParams[i].P_Type);
      WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
      if (pRasParams[i].P_Type == 1)
	  {
	  sprintf(buf,"pRasParams->P_Value.Length=%d\n",pRasParams[i].P_Value.String.Length);
		WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	  sprintf(szBuf,"                                                                \n");
	  strncpy(szBuf, pRasParams[i].P_Value.String.Data, pRasParams[i].P_Value.String.Length);
	  sprintf(buf,"pRasParams->P_Value.Data= %s\n",szBuf);
	       WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	  }
      if (pRasParams[i].P_Type == 0)
	 {
	 sprintf(buf,"pRasParams->P_Value.Number=%d\n", pRasParams[i].P_Value.Number);
	      WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
	 }
      sprintf(buf, "pRasParams->P_Attributes= %d\n",pRasParams[i].P_Attributes);
      WriteFile(ConDisFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
      }
}
