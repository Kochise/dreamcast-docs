//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//|   Title:   INI.C
//|      This module contains the functions which work with SATOOL.INI.
//*---------------------------------------------------------------------------------
#include "ini.h"
#include "results.h"
#include <commdlg.h>


//*---------------------------------------------------------------------------------
//|   Global variables
//*---------------------------------------------------------------------------------
dCSEG(char) szLABINI[]                       = "ADMNDEMO.INI";
dCSEG(char) szSCREEN[]                       = "screen";
dCSEG(char) szMAX[]                          = "Maximized";
dCSEG(char) szCONNECTOPTIONS[]               = "Connect Options";
dCSEG(char) szMAXRESULTS[]                   = "Max Results Windows";
dCSEG(char) szFONT[]                         = "Font";
dCSEG(char) szFONTSIZE[]                     = "FontSize";
dCSEG(char) szFONTWEIGHT[]                   = "FontWeight";
dCSEG(char) szFONTNAME[]                     = "FontName";
dCSEG(char) szFONTRGB[]                      = "FontColor";
dCSEG(char) szSTRIKEOUT[]                    = "FontStrikeOut";
dCSEG(char) szUNDERLINE[]                    = "FontUnderline";
dCSEG(char) szFONTSTYLE[]                    = "FontStyle";
dCSEG(char) szPIPES[]                        = "Pipes";
dCSEG(char) szRegular[]                      = "Regular";
dCSEG(char) szArial[]                        = "Arial";
dCSEG(char) szMSSansSerif[]                  = "MS Sans Serif";
dCSEG(char) szINSTALL[]                      = "Installed";
dCSEG(char) szDROPPROC[]                     = "Drop Procedure (with semi-colon)";
dCSEG(char) szDROPTABLE[]                    = "Drop Table";
dCSEG(char) szSQLSECTION[]                   = "Sql";
dCSEG(char) szPARMSSECTION[]                 = "Parms";
dCSEG(char) szPARMOPTSECTION[]               = "ParmOpt";
dCSEG(char) szDELETESECTION[]                = "Delete";
dCSEG(char) szSQLDROPSTMT[]                  = "drop procedure ?";
dCSEG(char) szSQLDROPTABLESTMT[]             = "drop table ?";
dCSEG(char) szPARMVALUE[]                    = "value";
dCSEG(char) szPARM1[]                        = "1";
dCSEG(char) szPARM3[]                        = "3";


//*---------------------------------------------------------------------------------
//|   Local Functions
//*---------------------------------------------------------------------------------
LPSTR GetFontStyle(LPSTR szStyle, int cbStyle);
void SetDefaultFont(LOGFONT FAR * lf);
void SetDefaultRGB(COLORREF rgb);
void SetFontStyle(LPSTR szFontStyle);


//*---------------------------------------------------------------------------------
//| ResolveIniFile:
//|   Look for ADMNDEMO.INI, if not found, fill out the defaults.
//| Parms:
//|   Nothing
//| Returns:
//|   Nothing.
//*---------------------------------------------------------------------------------
VOID INTFUN ResolveIniFile()
{
   // Max status is written after every exit, so if this constant cannot
   // be found, there is no file to find.
   if(GetPrivateProfileInt(szSCREEN, szMAX, -1, szLABINI) == -1) {
      // No file, create one
      WritePrivateProfileString(szPIPES, szDROPPROC, szINSTALL, szLABINI);
      WritePrivateProfileString(szDROPPROC, szSQLSECTION, szSQLDROPSTMT, szLABINI);
      WritePrivateProfileString(szDROPPROC, szPARMSSECTION, szPARM3, szLABINI);
      WritePrivateProfileString(szDROPPROC, szPARMOPTSECTION, szPARMVALUE, szLABINI);
      WritePrivateProfileString(szDROPPROC, szDELETESECTION, szPARM1, szLABINI);

      WritePrivateProfileString(szPIPES, szDROPTABLE, szINSTALL, szLABINI);
      WritePrivateProfileString(szDROPTABLE, szSQLSECTION, szSQLDROPTABLESTMT, szLABINI);
      WritePrivateProfileString(szDROPTABLE, szPARMSSECTION, szPARM3, szLABINI);
      WritePrivateProfileString(szDROPTABLE, szPARMOPTSECTION, szPARMVALUE, szLABINI);
      WritePrivateProfileString(szDROPTABLE, szDELETESECTION, szPARM1, szLABINI);
   }
}


//*---------------------------------------------------------------------------------
//| GetDefaultFont:
//|   This function will retrieve all of the font information that is stored in
//|   the .INI file and places it in the LOGFONT structure passed in.
//|   NOTE:  User should clear the LOGFONT structure to 0 (eg: fmemset(&lf, 0,sizeof())
//|     before calling this function.  The font name buffer must point to a user's
//|     allocated buffer.
//| Parms:
//|   in       lf             LOGFONT structure
//| Returns:
//|   Pointer to the LOGFONT structure passed in or NULL on error.
//*---------------------------------------------------------------------------------
LOGFONT FAR * GetDefaultFont(LOGFONT FAR * lf)
{
   lf->lfHeight = GetPrivateProfileInt(szFONT, szFONTSIZE, -12, szLABINI);
   lf->lfWeight = GetPrivateProfileInt(szFONT, szFONTWEIGHT, FW_NORMAL, szLABINI);
   lf->lfStrikeOut = GetPrivateProfileInt(szFONT, szSTRIKEOUT, 0, szLABINI);
   lf->lfUnderline = GetPrivateProfileInt(szFONT, szUNDERLINE, 0, szLABINI);
   lf->lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;
   if(!GetPrivateProfileString(szFONT, szFONTNAME, NULL,
                               lf->lfFaceName, LF_FACESIZE, szLABINI))
      lstrcpy(lf->lfFaceName, (LPSTR)szArial);

   return lf;
}


//*---------------------------------------------------------------------------------
//| SetDefaultFont:
//|   This function uses the values in the LOGFONT structure passed in to write the
//|   default values to the .INI file.
//| Parms:
//|   in       lf             LOGFONT structure
//| Returns:
//|   Nothing
//*---------------------------------------------------------------------------------
void SetDefaultFont(LOGFONT FAR * lf)
{
   char  szTmp[20];
   char  szpd[] = "%d";

   wsprintf(szTmp, szpd, lf->lfHeight);
   WritePrivateProfileString(szFONT, szFONTSIZE, szTmp, szLABINI);

   wsprintf(szTmp, szpd, lf->lfWeight);
   WritePrivateProfileString(szFONT, szFONTWEIGHT, szTmp, szLABINI);

   wsprintf(szTmp, szpd, lf->lfStrikeOut);
   WritePrivateProfileString(szFONT, szSTRIKEOUT, szTmp, szLABINI);

   wsprintf(szTmp, szpd, lf->lfUnderline);
   WritePrivateProfileString(szFONT, szUNDERLINE, szTmp, szLABINI);

   WritePrivateProfileString(szFONT, szFONTNAME, lf->lfFaceName, szLABINI);
}



//*---------------------------------------------------------------------------------
//| GetDefaultRGB:
//|   This function will retrieve the default rgbvalue from the ini file.
//| Parms:
//|   Nothing.
//| Returns:
//|   A COLORREF value that can be used for color.
//*---------------------------------------------------------------------------------
COLORREF GetDefaultRGB(void)
{
   COLORREF dft;
   LPSTR    lpsz;
   char     szBuff[20];

   if(!GetPrivateProfileString(szSCREEN, szFONTRGB, NULL,
                               szBuff, sizeof(szBuff), szLABINI))
      dft = RGB(0,0,0);          // If not specified, use Black
   else
      dft = strtoul(szBuff, &lpsz, 10);

   return dft;
}


//*---------------------------------------------------------------------------------
//| SetDefaultRGB:
//|   This function will set the default RGB value which will be used for
//|   color.
//| Parms:
//|   in       rgb                  The rgb value to use
//| Returns:
//|   Nothing
//*---------------------------------------------------------------------------------
void SetDefaultRGB(COLORREF rgb)
{
   char     szBuff[20];

   wsprintf(szBuff, "%lu", rgb);
   WritePrivateProfileString(szSCREEN, szFONTRGB,
                             szBuff, szLABINI);
}


//*---------------------------------------------------------------------------------
//| GetFontStyle:
//|   This function will copy the default font style to the user's buffer.
//| Parms:
//|   in       szStyle                 Pointer to output for font sytle
//|   in       cbStyle                 Maximum size of buffer
//| Returns:
//|   Style to use, NULL otherwise
//*---------------------------------------------------------------------------------
LPSTR GetFontStyle(LPSTR szStyle, int cbStyle)
{
   if(!GetPrivateProfileString(szSCREEN, szFONTSTYLE, NULL,
                               szStyle, cbStyle, szLABINI))
      lstrcpy(szStyle, (LPSTR)szRegular);
   return szStyle;
}


//*---------------------------------------------------------------------------------
//| SetFontStyle:
//|   This function will set the default font style.
//| Parms:
//|   in       szFontStyle          The new font style
//| Returns:
//|   Nothing
//*---------------------------------------------------------------------------------
void SetFontStyle(LPSTR szFontStyle)
{
   WritePrivateProfileString(szSCREEN, szFONTSTYLE,
                             szFontStyle, szLABINI);
}


//*---------------------------------------------------------------------------------
//| GetPipeNames:
//|   This function will get as many pipes as will fit into the user's
//|   buffer.  The list is simply retrieve via GetPrivateProfileString
//|   and therefore each pipe name will be null terminated with 2 nulls
//|   at the end of the entire list.
//| Parms:
//|   in       szPipes                 Pointer to string to hold names
//|   in       size                    Maximum size of pipe string
//| Returns:
//|   Nothing
//*---------------------------------------------------------------------------------
void GetPipeNames(LPSTR szPipes, int size)
{
   if(!GetPrivateProfileString(szPIPES, NULL, NULL, szPipes, size,
                               szLABINI))
      *szPipes = '\0';
}


//*---------------------------------------------------------------------------------
//| PromptForFontName:
//|   This function will prompt the user for a font style and name.
//| Parms:
//|   in       szPipes                 Pointer to string to hold names
//|   in       size                    Maximum size of pipe string
//| Returns:
//|   Nothing
//*---------------------------------------------------------------------------------
void PromptForFontName(HWND hwndOwner)
{
   CHOOSEFONT     cf;
   LOGFONT        lf;
   HWND           fHwnd=GetFocus();
   char           lpszStyle[LF_FACESIZE];

   memset(&lf, 0, sizeof(LOGFONT));
   memset(&cf, 0, sizeof(CHOOSEFONT));
   cf.lpLogFont = (LOGFONT FAR *)&lf;
   cf.lpszStyle = (LPSTR)lpszStyle;
   GetDefaultFont(&lf);

   cf.lStructSize = sizeof(CHOOSEFONT);
   cf.hwndOwner = hwndOwner;
   cf.Flags = CF_SCREENFONTS | CF_EFFECTS | CF_INITTOLOGFONTSTRUCT;
   cf.rgbColors = GetDefaultRGB();
   cf.nFontType = SCREEN_FONTTYPE;
   GetFontStyle(cf.lpszStyle, LF_FACESIZE);

   if(ChooseFont(&cf)) {
      SetDefaultFont(&lf);
      SetDefaultRGB(cf.rgbColors);
      SetFontStyle(cf.lpszStyle);
   }

   if(fHwnd)
      SetFocus(fHwnd);
}
