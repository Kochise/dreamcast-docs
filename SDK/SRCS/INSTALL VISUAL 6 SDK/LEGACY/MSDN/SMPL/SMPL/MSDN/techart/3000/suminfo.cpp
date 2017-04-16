//This was modified from the following sample code for vbDLL functions
/*************************************************************************
**
**    OLE 2.0 Property Set Utilities
**
**    testsumi.cpp
**
**   
**    (c) Copyright Microsoft Corp. 1990 - 1992 All Rights Reserved
**
*************************************************************************/

#include <windows.h>
#include <ole2.h>
#include <storage.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <suminfo.h> 
#include <vbapi.h>
#include "nativevb.h"

int len;
#define BUFFERLEN 4096
char szBuffer[BUFFERLEN];
/****************************************************************************
**
** TestReadDocFile()
**
** reads summary info property set from "\\test.dfl" DocFile.  
**
*****************************************************************************/
extern "C" HLSTR _pascal __export vbHasSummaryInfo(LPSTR szFile)
{   
    HRESULT hrErr;
    char name1[50]=PropStreamName;
    BOOL bReturn=-1;
    LONG lRevNum = 0;               
    HLSTR hlstr=NULL;        
    if (FAILED(CoInitialize(NULL))){
     CoUninitialize();    
     MessageBox(NULL,"CoInitialize Failed.\n", (LPSTR)szFile,MB_ICONSTOP);
     return NULL;
     }                                  
    hrErr = StgIsStorageFile(szFile);
	if (FAILED(hrErr)){           
		switch ((DWORD)hrErr)
		{
		case S_FALSE:                                                                         
			len = sprintf(szBuffer, "%s","Not Storage File");
			break;
		case STG_E_FILENOTFOUND:                                                                         
			len = sprintf(szBuffer, "%s","File not found");
			break;
		 case STG_E_ACCESSDENIED:                                                                         
			len = sprintf(szBuffer, "%s","Access to file denied.");
			break;			
		case STG_E_INVALIDNAME:                                                                         
			len = sprintf(szBuffer, "%s","Invalid Name.");
			break;						
		case STG_E_INVALIDPOINTER:                                                                         
			len = sprintf(szBuffer, "%s","Invalid Pointer.");
			break;						
		case STG_E_INVALIDFLAG:                                                                         
			len = sprintf(szBuffer, "%s","Invalid Flag.");
			break;						
		case STG_E_FILEALREADYEXISTS:                                                                         
			len = sprintf(szBuffer, "%s","File already Exists.");
			break;			
		 case STG_E_INSUFFICIENTMEMORY:                                                                         
			len = sprintf(szBuffer, "%s","Insufficient Memory");
			break;			
		case STG_E_TOOMANYOPENFILES:                                                                         
			len = sprintf(szBuffer, "%s","Too many open files");
			break;			
		case STG_E_OLDDLL:                                                                         
			len = sprintf(szBuffer, "%s","Storage DLL is too old -- update");
			break;			
		case STG_E_OLDFORMAT:                                                                         
			len = sprintf(szBuffer, "%s","File is in Beta 1 Format -- update");
			break;			
         default:
     		len = sprintf(szBuffer, "Unknown Error: %l",hrErr);
     	}
     	bReturn=FALSE;
     };                                                        
    len = sprintf(szBuffer, "-1 Has Version Information ");
    CoUninitialize();                                      
    hlstr=VBCreateTempHlstr(szBuffer,len);
    VALIDHLSTR(hlstr);
	return hlstr;
}
extern "C" HLSTR _pascal __export vbSummaryInfo(LPSTR szFile, int item)
{
    LPSTORAGE lpRootStg;
    LPSTREAM lpStream;
    HRESULT hrErr;
    char name1[50]=PropStreamName;
    LPSUMINFO lpSumInf;
    LPSTR lpsz;
    int yr,mn,dy;
    DWORD sc;    
    LONG lRevNum = 0;               
    HLSTR hlstr=NULL;
    if (FAILED(CoInitialize(NULL))) return NULL;
    
    lpSumInf = OleStdInitSummaryInfo(0);
    hrErr = StgOpenStorage(
            szFile, 
            NULL, 
            STGM_READWRITE | STGM_DIRECT| STGM_SHARE_EXCLUSIVE, 
            NULL, 
            0, 
            &lpRootStg);

    if (FAILED(hrErr))
    {                               
        MessageBox(NULL,"Could not open storage file.\n", (LPSTR)szFile,MB_ICONSTOP);
        OleStdFreeSummaryInfo(&lpSumInf);
        CoUninitialize();
        return NULL;
    };
    hrErr = lpRootStg->OpenStream(
            name1, 
            NULL, 
            STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 
            0, 
            &lpStream);

    if (FAILED(hrErr)) {                 
    	OleStdFreeSummaryInfo(&lpSumInf);                                            
    	 MessageBox(NULL,"Could not open Stream.\n", (LPSTR)szFile,MB_ICONSTOP);
    	CoUninitialize();
    	return NULL;
    }
    OleStdReadSummaryInfo(lpStream, lpSumInf);
	switch (item)
	{
	case 1:
  		lpsz = OleStdGetStringProperty(lpSumInf, PID_TITLE);
    	if (lpsz) {
        	hlstr=VBCreateTempHlstr(lpsz,_fstrlen((LPSTR)lpsz));
        	VALIDHLSTR(hlstr);
    	}
    	break;
    case 2:
  	lpsz = OleStdGetStringProperty(lpSumInf, PID_SUBJECT);
    if (lpsz) {
        	hlstr=VBCreateTempHlstr(lpsz,_fstrlen((LPSTR)lpsz));
        	VALIDHLSTR(hlstr);
    	}
    	break;
    case 3:
  	
  	lpsz = OleStdGetStringProperty(lpSumInf, PID_AUTHOR);
    if (lpsz) {
        	hlstr=VBCreateTempHlstr(lpsz,_fstrlen((LPSTR)lpsz));
        	VALIDHLSTR(hlstr);
    	}
    	break;
    case 4:
  	
  	lpsz = OleStdGetStringProperty(lpSumInf, PID_KEYWORDS);
    	if (lpsz) {
        	hlstr=VBCreateTempHlstr(lpsz,_fstrlen((LPSTR)lpsz));
        	VALIDHLSTR(hlstr);
    	}
    	break;
    case 5:
 	lpsz = OleStdGetStringProperty(lpSumInf, PID_COMMENTS);
    	if (lpsz) {
        	hlstr=VBCreateTempHlstr(lpsz,_fstrlen((LPSTR)lpsz));
        	VALIDHLSTR(hlstr);
    	}
    	break;
     case 6:
  		lpsz = OleStdGetStringProperty(lpSumInf, PID_TEMPLATE);
    	if (lpsz) {
        	hlstr=VBCreateTempHlstr(lpsz,_fstrlen((LPSTR)lpsz));
        	VALIDHLSTR(hlstr);
    	}
    	break;
    case 7:
	lpsz = OleStdGetStringProperty(lpSumInf, PID_LASTAUTHOR);
    	if (lpsz) {
        	hlstr=VBCreateTempHlstr(lpsz,_fstrlen((LPSTR)lpsz));
        	VALIDHLSTR(hlstr);
    	}
    	break;
    case 8:
  	lpsz = OleStdGetStringProperty(lpSumInf, PID_REVNUMBER);
    	if (lpsz) {
        	hlstr=VBCreateTempHlstr(lpsz,_fstrlen((LPSTR)lpsz));
        	VALIDHLSTR(hlstr);
    	}
    	break;
    case 9:
		OleStdGetDateProperty(lpSumInf,PID_EDITTIME,&yr,&mn,&dy,&sc);
		len = sprintf(szBuffer, "%ul seconds",sc);
        hlstr=VBCreateTempHlstr(szBuffer,len);
        VALIDHLSTR(hlstr);                      
        break;
    case 10:
		OleStdGetDateProperty(lpSumInf,PID_LASTPRINTED,&yr,&mn,&dy,&sc);
		len = sprintf(szBuffer, "%d\\%d\\%d",mn,dy,yr);
        hlstr=VBCreateTempHlstr(szBuffer,len);
        VALIDHLSTR(hlstr);                      
        break; 
    case 11:
		OleStdGetDateProperty(lpSumInf,PID_CREATE_DTM_RO,&yr,&mn,&dy,&sc);
		len = sprintf(szBuffer, "%d\\%d\\%d",mn,dy,yr);
        hlstr=VBCreateTempHlstr(szBuffer,len);
        VALIDHLSTR(hlstr);                      
        break; 
    case 12:
		OleStdGetDateProperty(lpSumInf,PID_LASTSAVE_DTM,&yr,&mn,&dy,&sc);
		len = sprintf(szBuffer, "%d\\%d\\%d",mn,dy,yr);
        hlstr=VBCreateTempHlstr(szBuffer,len);
        VALIDHLSTR(hlstr);                      
        break;  
    case 13://Pages        
    case 14://words
    case 15://characters
    {DWORD nPages,nWords, nCharacters;
  		OleStdGetDocProperty(lpSumInf, (DWORD FAR *)&nPages,(DWORD FAR *)&nWords, (DWORD FAR *)&nCharacters);
    	  	switch (item)
  		{
  		case 13:
  			len = sprintf(szBuffer, "%d Pages",nPages);
  			break;
  		case 14:
  			len = sprintf(szBuffer, "%d Words",nWords);
  			break; 
  		case 15:
  			len = sprintf(szBuffer, "%d Characters","nCharacters");
  			break;        
	    };       
	    }
    	hlstr=VBCreateTempHlstr(szBuffer,len);
        VALIDHLSTR(hlstr);    
    	break;
    case 17:
  		lpsz = OleStdGetStringProperty(lpSumInf, PID_APPNAME);
    	if (lpsz) {
        	hlstr=VBCreateTempHlstr(lpsz,_fstrlen((LPSTR)lpsz));
        	VALIDHLSTR(hlstr);
    	}     
    	break;
	case 18:
  		switch (OleStdGetSecurityProperty(lpSumInf))
  		{
  		case 0:
  			len = sprintf(szBuffer, "%s","no security");
  			break;
  		case 1:
  			len = sprintf(szBuffer, "%s","password required");
  			break;
  		case 2:
  			len = sprintf(szBuffer, "%s","read-only is recommended");
  			break;
  		case 4:
  			len = sprintf(szBuffer, "%s","read-only is required");
  			break;
  		case 8:
  			len = sprintf(szBuffer, "%s","locked for annotations");
  			break;                                              
  		default:                                                   
  			len = sprintf(szBuffer, "%s","unknown");
    	
        }     
        hlstr=VBCreateTempHlstr(szBuffer,len);
        VALIDHLSTR(hlstr);
    	break;   
    
    default:   //Return EVERYTHING in tab delimited string
    //--------------------------------------------------------------
    	lpsz = OleStdGetStringProperty(lpSumInf, PID_TITLE);
    	len = sprintf(szBuffer, "%s\t",lpsz);    	          
			MessageBox(NULL,szBuffer,lpsz,0);
	  	lpsz = OleStdGetStringProperty(lpSumInf, PID_SUBJECT);
    	len += sprintf(szBuffer+len, "%s\t",lpsz);    	
    		MessageBox(NULL,szBuffer,lpsz,0);
    	lpsz = OleStdGetStringProperty(lpSumInf, PID_AUTHOR);
    	len += sprintf(szBuffer+len, "%s\t",lpsz);    	
    		MessageBox(NULL,szBuffer,lpsz,0);
    	lpsz = OleStdGetStringProperty(lpSumInf, PID_KEYWORDS);
    	len += sprintf(szBuffer+len, "%s\t",lpsz);    	
    		MessageBox(NULL,szBuffer,lpsz,0);
	 	lpsz = OleStdGetStringProperty(lpSumInf, PID_COMMENTS);
    	len += sprintf(szBuffer+len, "%s\t",lpsz);    	        
    		MessageBox(NULL,szBuffer,lpsz,0);
  		lpsz = OleStdGetStringProperty(lpSumInf, PID_TEMPLATE); 
  		len += sprintf(szBuffer+len, "%s\t",lpsz);    	        
  			MessageBox(NULL,szBuffer,lpsz,0);
		lpsz = OleStdGetStringProperty(lpSumInf, PID_LASTAUTHOR);
    	len += sprintf(szBuffer+len, "%s\t",lpsz);    	        
    		MessageBox(NULL,szBuffer,lpsz,0);
  		lpsz = OleStdGetStringProperty(lpSumInf, PID_REVNUMBER);
    	len += sprintf(szBuffer+len, "%s\t",lpsz);    	        
    		MessageBox(NULL,szBuffer,lpsz,0);    		  			

    	OleStdGetDateProperty(lpSumInf,PID_EDITTIME,&yr,&mn,&dy,&sc);
		len += sprintf(szBuffer+len, "%ul seconds\t",sc);
		    		MessageBox(NULL,szBuffer,lpsz,0);
        OleStdGetDateProperty(lpSumInf,PID_LASTPRINTED,&yr,&mn,&dy,&sc);
		len += sprintf(szBuffer+len, "%d\\%d\\%d\t",mn,dy,yr);
		    		MessageBox(NULL,szBuffer,lpsz,0);
        OleStdGetDateProperty(lpSumInf,PID_CREATE_DTM_RO,&yr,&mn,&dy,&sc);
		len += sprintf(szBuffer+len, "%d\\%d\\%d\t",mn,dy,yr);
		    		MessageBox(NULL,szBuffer,lpsz,0);
		OleStdGetDateProperty(lpSumInf,PID_LASTSAVE_DTM,&yr,&mn,&dy,&sc);
		len += sprintf(szBuffer+len, "%d\\%d\\%d\t",mn,dy,yr);
		    		MessageBox(NULL,szBuffer,lpsz,0);
        {DWORD nPages,nWords, nCharacters;
  		OleStdGetDocProperty(lpSumInf, (DWORD FAR *)&nPages,(DWORD FAR *)&nWords, (DWORD FAR *)&nCharacters);
    	len += sprintf(szBuffer+len, "%d Pages\t",nPages);
		len += sprintf(szBuffer+len, "%d Words\t",nWords);
  		len += sprintf(szBuffer+len, "%d Characters\t","nCharacters");
  		}	                                          
  		    		
  		lpsz = OleStdGetStringProperty(lpSumInf, PID_APPNAME);
    	len += sprintf(szBuffer+len, "%s\t",lpsz);    	
    	    		MessageBox(NULL,szBuffer,lpsz,0);
		switch (OleStdGetSecurityProperty(lpSumInf))
  		{
  		case 0:
  			len += sprintf(szBuffer+len, "%s","no security");
  			break;
  		case 1:
  			len += sprintf(szBuffer+len, "%s","password required");
  			break;
  		case 2:
  			len += sprintf(szBuffer+len, "%s","read-only is recommended");
  			break;
  		case 4:
  			len += sprintf(szBuffer+len, "%s","read-only is required");
  			break;
  		case 8:
  			len += sprintf(szBuffer+len, "%s","locked for annotations");
  			break;                                              
  		default:                                                   
  			len += sprintf(szBuffer+len, "%s","unknown");
    	
        }                                            
            		MessageBox(NULL,szBuffer,lpsz,0);
        hlstr=VBCreateTempHlstr(szBuffer,len);
        VALIDHLSTR(hlstr);
    }            
    OleStdFreeSummaryInfo(&lpSumInf);
    lpStream->Release();

    // And release the new stream since we are finished with it
    lpRootStg->Release();      
    CoUninitialize();
    return hlstr;
}                     

