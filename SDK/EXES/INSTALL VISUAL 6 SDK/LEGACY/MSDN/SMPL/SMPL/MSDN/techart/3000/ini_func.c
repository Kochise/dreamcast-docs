//Ini Functions       
#include <windows.h>
#include <vbapi.h>
#include "nativevb.h"

#define MAXINISTRING 4096 //Largest String that can be returned
#define EmptyString  "\0"
char iniBuffer[MAXINISTRING];   
HLSTR hlstr;         
// The following functions deals with Win.Ini

// Return the value on an Entry
HLSTR __export  _pascal vbGetWinIni(LPSTR Section, LPSTR Entry)
{int cb;
      if((Section==NULL) || (Entry==NULL))
        {
      	MessageBox(NULL,"Section or Entry is NULL -- wrong function called.","GetWinIni()",MB_ICONSTOP);
      	return NULL;
      	}
      cb=GetProfileString(Section,Entry,EmptyString,iniBuffer,MAXINISTRING);
      if (cb < 1) 
      	return NULL ;              
      if (cb ==MAXINISTRING)    
      		MessageBox(NULL,"Value may be truncated.","GetWinIni()",MB_ICONEXCLAMATION);
      hlstr = VBCreateTempHlstr(iniBuffer, cb);
	  VALIDHLSTR(hlstr);
	  return hlstr;
}   

// return all the entries in a Section
HLSTR __export  _pascal vbGetWinIniSection(LPSTR Section)
{int cb, i;
      if((Section==NULL))
        {
      	MessageBox(NULL,"Section is NULL -- wrong function called.","GetWinIniSection()",MB_ICONSTOP);
      	return NULL;
      	}
      cb=GetProfileString(Section,NULL,EmptyString,iniBuffer,MAXINISTRING);
      if (cb < 1) 
      	return NULL ;
      for(i=0;i < cb;i++)
      	if(iniBuffer[i]=='\0') 
      		iniBuffer[i]='\t';
      hlstr = VBCreateTempHlstr(iniBuffer, cb);
	  VALIDHLSTR(hlstr);
	  return hlstr;
}

// Set the value of an Entry in a section
void __export  _pascal PutWinIni(LPSTR Section, LPSTR Entry, LPSTR IniValue)
{   
	 if((Section==NULL) || (Entry==NULL) || (IniValue==NULL))
        {
      	MessageBox(NULL,"Section or Entry or IniValue is NULL -- wrong function called.","PutWinIni()",MB_ICONSTOP);
      	return ;
      	}
	if (0==WriteProfileString(Section,Entry,IniValue))  
		MessageBox(NULL,"Function failed.","PutWinIni()",MB_ICONSTOP);
}

// Delete one entry in a section
void __export  _pascal DelWinIni(LPSTR Section, LPSTR Entry)
{   
	 if((Section==NULL) || (Entry==NULL))
        {
      	MessageBox(NULL,"Section or Entry is NULL -- wrong function called.","DelWinIni()",MB_ICONSTOP);
      	return ;
      	}
	if (0==WriteProfileString(Section,Entry,NULL))  
		MessageBox(NULL,"Function failed.","PutWinIni()",MB_ICONSTOP);
}

// Remove all entries in a section
void __export  _pascal DelWinIniSection(LPSTR Section)
{   
	 if(Section==NULL) 
        {
      	MessageBox(NULL,"Section is NULL -- wrong function called.","DelWinIniSection()",MB_ICONSTOP);
      	return;
      	}
	if (0==WriteProfileString(Section,NULL,NULL))  
		MessageBox(NULL,"Function failed.","DelWinIniSection()",MB_ICONSTOP);
}    

// Flush the windows cache.
void __export  _pascal FlushWinIni()
{   
	WriteProfileString(NULL,NULL,NULL);  
	
}
// ============================================================
//  The following functions deals with private ini files
// ============================================================

HLSTR __export  _pascal vbGetIni(LPSTR Section, LPSTR Entry, LPSTR FileName)
{int cb;
      if((Section==NULL) || (Entry==NULL))
        {
      	MessageBox(NULL,"Section or Entry is NULL -- wrong function called.","GetWinIni()",MB_ICONSTOP);
      	return NULL;
      	}
      cb=GetPrivateProfileString(Section,Entry,EmptyString,iniBuffer,MAXINISTRING,FileName);
      if (cb < 1) 
      	return NULL ;              
      if (cb ==MAXINISTRING)    
      		MessageBox(NULL,"Value may be truncated.","vbGetIni()",MB_ICONEXCLAMATION);
      hlstr = VBCreateTempHlstr(iniBuffer, cb);
	  if (HIWORD(hlstr) == -1)                 
     { MessageBox(NULL,"VBCreateTempHlstr failed -- Contact Support." , "CRITICAL ERROR",MB_ICONSTOP);
			return NULL;}
	  return hlstr;
}   


HLSTR __export  _pascal vbGetIniSection(LPSTR Section, LPSTR FileName)
{int cb, i;             
      if((Section==NULL))
        {
      	MessageBox(NULL,"Section is NULL -- wrong function called.","GetWinIniSection()",MB_ICONSTOP);
      	return NULL;
      	}
      cb=GetPrivateProfileString(Section,NULL,NULL,iniBuffer,MAXINISTRING,FileName);
      if (cb < 1) 
      	return NULL ;
      for(i=0;i < cb;i++)
      	if(iniBuffer[i]=='\0') 
      		iniBuffer[i]='\t';
      hlstr = VBCreateTempHlstr(iniBuffer, cb);
	  VALIDHLSTR(hlstr);
      return hlstr;
}


void __export  _pascal PutIni(LPSTR Section, LPSTR Entry, LPSTR IniValue, LPSTR FileName)
{   
	 if((Section==NULL) || (Entry==NULL) || (IniValue==NULL))
        {
      	MessageBox(NULL,"Section or Entry or IniValue is NULL -- wrong function called.","PutIni()",MB_ICONSTOP);
      	return ;
      	}
	if (0==WritePrivateProfileString(Section,Entry,IniValue, FileName))  
		MessageBox(NULL,"Function failed.","PutIni()",MB_ICONSTOP);
}

// Delete one entry in a section
void __export  _pascal DelIni(LPSTR Section, LPSTR Entry, LPSTR FileName)
{   
	 if((Section==NULL) || (Entry==NULL))
        {
      	MessageBox(NULL,"Section or Entry is NULL -- wrong function called.","DelIni()",MB_ICONSTOP);
      	return ;
      	}
	if (0==WritePrivateProfileString(Section,Entry,NULL,FileName))  
		MessageBox(NULL,"Function failed.","PutIni()",MB_ICONSTOP);
}

// Remove all entries in a section
void __export  _pascal DelIniSection(LPSTR Section, LPSTR FileName)
{   
	 if(Section==NULL) 
        {
      	MessageBox(NULL,"Section is NULL -- wrong function called.","DelIniSection()",MB_ICONSTOP);
      	return;
      	}
	if (0==WritePrivateProfileString(Section,NULL,NULL, FileName))  
		MessageBox(NULL,"Function failed.","DelIniSection()",MB_ICONSTOP);
}    

// Flush the windows cache.
void __export  _pascal FlushIni(LPSTR FileName)
{   
	WritePrivateProfileString(NULL,NULL,NULL,FileName);
	
}

