//Ini Functions       
#include <windows.h>
#include <vbapi.h> //for hlstr etc
#include <stdio.h>	
#include <stdlib.h>  //for _ltoa()
#include <dos.h>
#include <bios.h>
#include <time.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <string.h>   // for strlen
#include <ctype.h>     // for toupper
#include "nativevb.h"   
#define WF_WINNT 0x4000      
char szBuffer[256];    // this is our work space for all functions
char szLong[33];    // For _ltoa
HLSTR __export _pascal vbGetKeyboardState()
{HLSTR hlstr=NULL;
	GetKeyboardState((LPBYTE) &szBuffer);
	hlstr = VBCreateTempHlstr(szBuffer, 256);
	  		if (HIWORD(hlstr) == -1)
				return NULL;	
	  return hlstr;
}
HLSTR __export _pascal vbInKey()
{HLSTR hlstr=NULL;  
 BYTE pbKeyState[256]; 
 int i,cbfound=0;
 GetKeyboardState((LPBYTE) &pbKeyState);
 for(i=0; i < 256; i++)
 	if (pbKeyState[i] >= 0x80)
 		szBuffer[cbfound++]=i;
	if(cbfound==0) return NULL;
		
	hlstr = VBCreateTempHlstr(szBuffer, cbfound);
	  		if (HIWORD(hlstr) == -1)
				return NULL;	
	  return hlstr;
}
     




HLSTR __export _pascal vbWinDir()
{int cb=GetWindowsDirectory(szBuffer,_MAX_PATH);
 HLSTR hlstr=NULL;
	hlstr = VBCreateTempHlstr(szBuffer, cb);
	  		if (HIWORD(hlstr) == -1)
				return NULL;	
	  return hlstr;
}          

HLSTR __export _pascal vbSysDir()
{int cb=GetSystemDirectory(szBuffer,_MAX_PATH);
	HLSTR hlstr=NULL;
	hlstr = VBCreateTempHlstr(szBuffer, cb);
	VALIDHLSTR(hlstr);	  		
	  		return hlstr;
}

HLSTR __export _pascal vbWinInfo(int infoindex)
{  
HLSTR hlstr=NULL;
int len;
DWORD dwFlags = GetWinFlags();
switch (infoindex)
{ case 0:
	len = sprintf(szBuffer, "%s",
    (dwFlags & WF_80x87) ? "80x87" : "No 80x87");
	break;
  case 1:
	len = sprintf(szBuffer, "%s",
	(dwFlags & WF_CPU086) ? "8086" :
	(dwFlags & WF_CPU186) ? "80186" :
    (dwFlags & WF_CPU286) ? "80286" :
    (dwFlags & WF_CPU386) ? "80386" :
    (dwFlags & WF_CPU486) ? "80486" : "unknown");
	break;
   case 2:
	len = sprintf(szBuffer, "%s", 
	(dwFlags & WF_WINNT)  ? "Win NT":
    (dwFlags & WF_ENHANCED) ? "enhanced" : "standard");
	break;
   case 3:  //Windows Emulation Libraries
	len = sprintf(szBuffer, "%s",
    (dwFlags & WF_WLO) ? "WLO" : "No WLO");
	break;
   case 4:            
	len = sprintf(szBuffer, "%d%%",GetFreeSystemResources(GFSR_SYSTEMRESOURCES));
	break;
   case 5:
	len = sprintf(szBuffer, "%d%%",GetFreeSystemResources(GFSR_GDIRESOURCES));
	break;
   case 6:
	len = sprintf(szBuffer, "%d%%",GetFreeSystemResources(GFSR_USERRESOURCES));
	break;
   case 7:
	len = sprintf(szBuffer, "%ud",GetFreeSpace(0));     //Unsigned Int
	break; 
	case 8://Windows version 
		dwFlags = GetVersion();
        len = sprintf(szBuffer, "%d.%d",
    		LOBYTE(LOWORD(dwFlags)),
    		HIBYTE(LOWORD(dwFlags)));
    	break;
	case 9: //MS-DOS version 
		dwFlags = GetVersion();
		len= sprintf(szBuffer, "%d.%d",
    		HIBYTE(HIWORD(dwFlags)),
    		LOBYTE(HIWORD(dwFlags)));
	    break;
	default:
	len=0;
 }        
 if (len > 0)                          
 {
 	hlstr=VBCreateTempHlstr(szBuffer,len);
 	VALIDHLSTR(hlstr);
 };
 return hlstr;
}  

HLSTR  __export _pascal vbGetTempDrive(LPSTR lpDrive)
{	char szMsg[3]=" :";
	HLSTR hlstr=NULL;
	szMsg[0] = GetTempDrive(0);
	hlstr=VBCreateTempHlstr(szMsg,2);//No need for \0 at end!
	VALIDHLSTR(hlstr);
	return hlstr;
};  

HLSTR  __export _pascal vbGetTempFileName()
{ HLSTR hlstr=NULL;
/* Create a temporary file. */
	GetTempFileName(NULL, "vb", NULL, szBuffer);
    hlstr=VBCreateTempHlstr(szBuffer,strlen(szBuffer));
    VALIDHLSTR(hlstr);
    return hlstr;

}  

HLSTR  __export _pascal vbNextFreeDrive()
{int iDrive,len;  
 HLSTR hlstr=NULL;
 for (iDrive=3; iDrive < 27; iDrive++)
    if(GetDriveType(iDrive)==0) 
    	{
        len = sprintf(szBuffer, "%c", 'A'+iDrive);
        hlstr=VBCreateTempHlstr(szBuffer,len);     
    	return hlstr;
    	}
	return NULL;
}

HLSTR  __export _pascal vbFileInfo(LPSTR szFileName,int InfoItem)
{OFSTRUCT ofStruct;         
 struct _stat buf;
 int len=0;
 HLSTR hlstr;   
 if (InfoItem < 3)                                  
 	{
 	ofStruct.cBytes=sizeof(ofStruct);
 	if (-1 ==OpenFile(szFileName,&ofStruct, OF_EXIST))
		  		return NULL;       //Function failed
	}
 else
    if(0 != _stat( "stat.c", &buf ))
    		return NULL;//Function failed
 switch (InfoItem)
 {
  case 1:  //Location
	   len = sprintf(szBuffer, "%s", ofStruct.szPathName);		  		
		break;
  case 2:  //Fixed Drive?
	if (ofStruct.fFixedDisk)		  		
		len = sprintf(szBuffer, "%s","-1 Fixed Drive");		  		
	else
		len = sprintf(szBuffer, "%s","0 Not Fixed Drive");		  		
		break;
  case 3: //Size   
		len = sprintf(szBuffer, "%ld", buf.st_size);  	
		break;
  case 4: //Drive
		len = sprintf(szBuffer, "%c:", buf.st_dev + 'A' );
		break;
  case 5: //Datetime
        len = sprintf(szBuffer, "%s", ctime( &buf.st_atime ) );
/* STAT.C: This program uses the _stat function to
 * report information about the file named STAT.C.
 */

  case 6: //Attributes
      if (buf.st_mode)
      	return NULL;
  default:
    return NULL;
 };         
 if (len){
	 hlstr=VBCreateTempHlstr(szBuffer,len);      
 	 VALIDHLSTR(hlstr);
 	 };
 return hlstr;
}      
//============================================  
// Return information about a Drive
// A - Z are valid arguments.
//============================================
HLSTR  __export _pascal vbDriveInfo(LPSTR lpDrive, int item)
{int iDrive = toupper(*lpDrive) - 'A'; 
 HLSTR hlstr=NULL;
 int len;                       
 long DiskSpace=1;
 struct _diskfree_t drive;
 
 if((iDrive < 0) || (iDrive > 26))
    return NULL;                         
 switch (item)
 {                                                     
 case 0:
 	len = sprintf(szBuffer, "%s", lpDrive);
 	break;
 case 1: //Type
    switch (GetDriveType(iDrive)) {
        case DRIVE_REMOVABLE:
            len = sprintf(szBuffer, "%s", "removable");
            break;

        case DRIVE_FIXED:
            len = sprintf(szBuffer, "%s","fixed");

            break;

        case DRIVE_REMOTE:
            len = sprintf(szBuffer, "%s", "remote (network)");
            break;
        default:
            len = sprintf(szBuffer, "%s","undetermined");
            break;
	
    }                                         
    break;
    case 2: //Total Space
	    if( _dos_getdiskfree( iDrive + 1, &drive) )
        return NULL; //Error     
        DiskSpace=drive.total_clusters;
        DiskSpace=DiskSpace *(long) drive.bytes_per_sector ;
		DiskSpace=DiskSpace *(long) drive.sectors_per_cluster ;         
        len = sprintf(szBuffer, "%s bytes total",(LPSTR) _ltoa(DiskSpace,(LPSTR) &szLong,10));
        break;
	case 3: //Free Space
	if( _dos_getdiskfree( iDrive + 1, &drive ) )
          return NULL; //Error    
        DiskSpace=drive.avail_clusters;
        DiskSpace=DiskSpace *(long) drive.bytes_per_sector ;
		DiskSpace=DiskSpace *(long) drive.sectors_per_cluster ;         
        len = sprintf(szBuffer, "%s bytes free",(LPSTR) _ltoa(DiskSpace,(LPSTR)&szLong,10));
        break;
	case 4: //Bytes per Sector
	if( _dos_getdiskfree( iDrive + 1, &drive ) )
          return NULL; //Error    
        len = sprintf(szBuffer, "%u bytes per sector", drive.bytes_per_sector);
		break;
	case 5: //Sectors Per Cluster
		if( _dos_getdiskfree( iDrive + 1, &drive ) )
          return NULL; //Error    
        len = sprintf(szBuffer, "%u sector per cluster", drive.sectors_per_cluster );
		break;
    ;
    default:
     return NULL;

 };
    hlstr=VBCreateTempHlstr(szBuffer,len);      
    VALIDHLSTR(hlstr);
    return hlstr;
}
  
  


