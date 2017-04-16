#include <windows.h>
#include <ver.h>                      // version info header
#include <stdlib.h>                   // for _MAX_PATH
#include <vbapi.h>			// for HLSTR etc.
#include  <string.h>			// for strlen
#include "nativevb.h"
     
int __export _pascal vbCountNulls(HLSTR hlstr)
{USHORT i=0, cb=VBGetHlstrLen(hlstr);  //obtain length of string
 int cnt=0;   //set count to zero
 LPSTR lpStr=VBDerefHlstr(hlstr);
 while(i++ < cb)  //are we at the end of the string?
    if(*lpStr++=='\0') cnt++;  //if a chr$(0) increment counter
 return cnt;
}
//------------------------------------------------------------
// Alltrim: Moves all control characters and spaces from both ends of a C string
//------------------------------------------------------------
HLSTR __export _pascal vbAllTrim(LPSTR buffer)
{LPSTR lpStart=buffer,lpEnd;                         
 USHORT cb=0;         
 HLSTR hlstr;   
	while((unsigned char)*lpStart < 33)
		lpStart++; //Skip all characters that is a space or below
	lpEnd=lpStart;
	while(*lpEnd++ != 0); //Move to end of string
	lpEnd--; //Back track to first good character but don't overshot
	while((lpEnd > lpStart)  //Don't go before start
		 && ((unsigned char)*lpEnd < 33)) 
		 	lpEnd--;
	cb=1+(USHORT)( lpEnd-lpStart); //bytes
	if (cb< 1) return NULL;
	hlstr=VBCreateTempHlstr(lpStart,cb);
	VALIDHLSTR(hlstr);
	return hlstr;
}
                                                              
                                                             
//------------------------------------------------------------
// ChangeChar: Changes all of one character to another
//------------------------------------------------------------
HLSTR __export _pascal vbChangeChar(LPSTR buffer, LPSTR lpFrom, LPSTR lpTo)
{	//create a VB string and copy   
	LPSTR lpStart;
	short cbBuffer= strlen(buffer) ;
	short I=0;
	HLSTR hlstr=VBCreateTempHlstr(buffer,cbBuffer);
	lpStart=VBDerefHlstr(hlstr);
	
	VALIDHLSTR(hlstr);  //make sure of success
 while(I < cbBuffer) //are we at the end of the string?
 	{
 	if(*lpStart==*lpFrom) //if this character is to be changed then 
 		*lpStart=*lpTo;    // change it
  		lpStart++;           // move to next character
		I++;
 	}
	
	return hlstr;
}
