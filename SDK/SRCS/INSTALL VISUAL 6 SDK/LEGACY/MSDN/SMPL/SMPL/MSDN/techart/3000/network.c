// This code is hacked from WFW SDK  Net.C
#include <windows.h>               
#include <vbapi.h>
#include <string.h>
#include <stdio.h>
#include <WFWNET.H>        // Windows for Workgroups Header
#include <LAN.H>           // Windows for Workgroups Network (NET) Header
#include <WINNET.H>        // Windows Network (WNET) Header
#include "nativevb.h"

#define INCL_NETWKSTA
#define INCL_NETERRORS
#include <WFWNET.H>        // Windows for Workgroups Header
#include <LAN.H>           // Windows for Workgroups Network (NET) Header
#include <WINNET.H>        // Windows Network (WNET) Header

#define BUFFER_LENGTH 256
char szBuffer[BUFFER_LENGTH];            // output buffer
int len;
HLSTR __export _pascal vbWorkStationInfo(int InfoIndex)
{   HLSTR hlstr;					//VB String
	HANDLE hwki0;                             // handle
   	struct wksta_info_0 *pwki0;               // pointer to wksta_info_0 structure
   
    int err, cb;
   
   char szServer[BUFFER_LENGTH];             // server buffer
   
szServer[0] = '\0';                            // init the server buffer
err = NetWkstaGetInfo(NULL, 0, NULL, 0, &cb); 
if (err != NERR_BufTooSmall)
    // error, no information available

hwki0 = LocalAlloc(LHND, cb);
pwki0 = (struct wksta_info_0 *)LocalLock(hwki0);
    // error, can't retrieve information           
         hwki0 = LocalAlloc(LHND, cb);                        
            pwki0 = (struct wksta_info_0 *)LocalLock(hwki0);
              
            err = NetWkstaGetInfo(szServer, 0, (char far *)pwki0, cb, &cb);

            if (err != NERR_Success)
               {
                  wsprintf(szBuffer,"* Could not get info on workstation %s",(LPSTR)szServer);
                  hlstr = VBCreateTempHlstr(szBuffer, strlen(szBuffer));
	  				if (HIWORD(hlstr) == -1)
						hlstr=NULL;	
	  				
               }
            else
               {
                switch(InfoIndex)
                {   
                 case 0://Path to Net Dir = 
                  // **********************************************************************
                  // function was successful....so let's output some of the information
                  // **********************************************************************
                  wsprintf(szBuffer,"%s",(LPSTR)pwki0->wki0_root);
                	break;
				 case 1://Computer Name = 				                  
                  wsprintf(szBuffer,"%s",(LPSTR)pwki0->wki0_computername);
                  break;
				 case 2://Username =                   
                  wsprintf(szBuffer,"%s",(LPSTR)pwki0->wki0_username);
                  break;
				 case 3://Workgroup =                   
                  wsprintf(szBuffer,"%s",(LPSTR)pwki0->wki0_langroup);
                  break;
                 case 4://Version =                   
                  	wsprintf(szBuffer,"%d.%d",pwki0->wki0_ver_major,pwki0->wki0_ver_major);                 
                  break;
                 case 5://MaxTimeInactiveConnection                   
                  	wsprintf(szBuffer,"%d",pwki0->wki0_keepconn);                 
                  break; 
                  case 6://MaxTimeInactiveSearch                   
                  	wsprintf(szBuffer,"%d",pwki0->wki0_keepsearch);                 
                  break; 
                  case 7://WorkStation Name                  
                  	wsprintf(szBuffer,"%s",(LPSTR)szServer);
                  	break;
                 default:
					wsprintf(szBuffer,"%s",(LPSTR)pwki0->wki0_username);
                 }        
               
             hlstr = VBCreateTempHlstr(szBuffer, strlen(szBuffer));
	  				if (HIWORD(hlstr) == -1)
						hlstr= NULL;	
	  		}		
            LocalUnlock(hwki0);                       // memory operations
            LocalFree(hwki0);
return hlstr;    
 }                                                     
typedef struct  _NETRESOURCE {
    DWORD    dwScope;
    DWORD    dwType;
    DWORD    dwDisplayType;
    DWORD    dwUsage;
    LPSTR    lpLocalName;
    LPSTR    lpResourceName;
    LPSTR    lpComment ;
    LPSTR    lpProvider;
}NETRESOURCE, *LPNETRESOURCE;
DWORD WNetAddConnection2 (
     LPNETRESOURCE lpNetResource,
     LPSTR        lpPassword,
     LPSTR        lpUserName,
     DWORD          dwFlags
    ); 
#define RESOURCETYPE_ANY        0x00000000    
#define WF_WINNT 0x4000                                        
#define CONNECT_UPDATE_PROFILE     0x00000001
 HLSTR __export _pascal vbAddConnection(LPSTR Drive, LPSTR UNC, LPSTR Password)  
 {UINT ret=0;
  HLSTR hlstr=NULL;                  
  NETRESOURCE myNetResource;
  LPNETRESOURCE lpNetResource=&myNetResource;  
  DWORD dwFlags = GetWinFlags();  
  if (dwFlags & WF_WINNT)  
  { //32 BIT VERSION                             
	lpNetResource->lpResourceName=UNC;
	lpNetResource->lpLocalName=Drive;                                
	lpNetResource->lpProvider=NULL;
	lpNetResource->dwType=RESOURCETYPE_ANY;
//  	dwFlags=WNetAddConnection2(lpNetResource,Password,NULL,CONNECT_UPDATE_PROFILE);
  }
  else
  	//16 bit vERSION  
	  ret=WNetAddConnection(UNC,Password,Drive);

  switch (ret)
  {
   case WN_ACCESS_DENIED:  
   		len = sprintf(szBuffer, "Access Denied to %s",UNC);
   		break;
   case WN_ALREADY_CONNECTED:
   		len = sprintf(szBuffer, "Already connected on %s",Drive);
   		break;
   case WN_BAD_LOCALNAME:
   		len = sprintf(szBuffer, "Bad Local Name [%s], should by like [X:]",Drive);
   		break;
   case WN_BAD_PASSWORD:
   		len = sprintf(szBuffer, "Bad Password on %s, PW=%s",UNC,Password);
   		break; 
   case WN_BAD_POINTER:
   		len = sprintf(szBuffer, "Bad Pointer Passed -- Must be ByVal in Declare");
   		break; 
   case WN_NET_ERROR:
   		len = sprintf(szBuffer, "Network Error");
   		break; 
   case WN_NOT_SUPPORTED:
		len = sprintf(szBuffer, "Not supported by this Network");
   		break; 
   case WN_OUT_OF_MEMORY:
   		len = sprintf(szBuffer, "Out of Memory -- shut down applications and try again");
   		break; 
   case WN_SUCCESS:                                                                   
   		len = sprintf(szBuffer, "-1 Drive %s is connected to %s", Drive, UNC);
   		break; 
   default:
   		len = sprintf(szBuffer, "Unknown error: Drive %s is not connected to %s", Drive, UNC);
   }
          hlstr=VBCreateTempHlstr(szBuffer,len);
    	VALIDHLSTR(hlstr);
		return hlstr;
 }
BOOL __export _pascal RemoveConnection(LPSTR Drive) 
{UINT ret=WNetCancelConnection(Drive,FALSE);
	if(ret==WN_SUCCESS) return TRUE;
	if(ret==WN_NOT_CONNECTED) return TRUE;
	if(ret==WN_OPEN_FILES)
		if (IDYES==MessageBox(NULL,"You have open files on this connection. Data may be lost. Do you still want to disconnect?","WARNING",MB_YESNO))
			if (WN_SUCCESS==WNetCancelConnection(Drive,TRUE)) return TRUE;
	return FALSE;
} 
HLSTR __export _pascal vbGetConnection(LPSTR Drive)   
{HLSTR hlstr=NULL;
 UINT cbBuffer=BUFFER_LENGTH;
 UINT ret=WNetGetConnection((LPSTR)Drive,(LPSTR) &szBuffer,(UINT FAR *) &cbBuffer);
 if (ret==WN_SUCCESS)                             
 {
        hlstr=VBCreateTempHlstr(szBuffer,cbBuffer);
    	VALIDHLSTR(hlstr);
    	return hlstr;
  }

switch (ret) //Failed!
  {
   case WN_BAD_VALUE:  
   		len = sprintf(szBuffer, "-1 Not a Valid Local Device %s",Drive);
   		break;
   case WN_MORE_DATA:
   		len = sprintf(szBuffer, "-1 DLL did not supply enough memory -- Report to Developer (MSDN@Microsoft.com)");
   		break;
   case WN_BAD_LOCALNAME:
   		len = sprintf(szBuffer, "-1 Bad Local Name %s",Drive);
   		break;
   case WN_BAD_POINTER:
   		len = sprintf(szBuffer, "-1 Bad Pointer Passed -- Must be ByVal in Declare");
   		break; 
   case WN_NET_ERROR:
   		len = sprintf(szBuffer, "-1 Network Error");
   		break; 
   case WN_NOT_SUPPORTED:
		len = sprintf(szBuffer, "-1 Not supported by this Network");
   		break;                      
   case WN_OUT_OF_MEMORY:
   		len = sprintf(szBuffer, "-1 Out of Memory -- shut down applications and try again");
   		break;   
   default:
   		len = sprintf(szBuffer, "-1 Unknown error[%d]: Drive %s is not connected",ret, Drive);
   }                 
   hlstr=VBCreateTempHlstr(szBuffer,len);
   VALIDHLSTR(hlstr);
   return hlstr;
}
int __export _pascal NetDriveDialog()   
{
	if (WN_SUCCESS == WNetConnectionDialog(GetFocus(),WNTYPE_DRIVE))
		return -1;
return 0;
}

int __export _pascal NetPrinterDialog()   
{
    if (WN_SUCCESS == WNetConnectionDialog(GetFocus(),WNTYPE_PRINTER))
    	return -1;
return 0;
}