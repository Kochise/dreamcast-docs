//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//|   Title:   INI.H
//|      This file contains the prototypes and defines for executing SQL
//|         statements and displaying their results.
//*---------------------------------------------------------------------------------
#ifndef ini_DEFS
#define ini_DEFS

#include <windows.h>
#include "standard.h"
#include "errcheck.h"


//*---------------------------------------------------------------------------------
//|   Global variables
//*---------------------------------------------------------------------------------
extern dCSEG(char) szLABINI[];
extern dCSEG(char) szSCREEN[];
extern dCSEG(char) szMAX[];
extern dCSEG(char) szCONNECTOPTIONS[];
extern dCSEG(char) szMAXRESULTS[];
extern dCSEG(char) szFONTSIZE[];
extern dCSEG(char) szMSSansSerif[];


//*---------------------------------------------------------------------------------
//|   Function prototypes
//*---------------------------------------------------------------------------------
VOID INTFUN ResolveIniFile();
LOGFONT FAR * GetDefaultFont(LOGFONT FAR * lf);
COLORREF GetDefaultRGB(void);
void GetPipeNames(LPSTR szPipes, int size);
void PromptForFontName(HWND hwndOwner);




#endif
