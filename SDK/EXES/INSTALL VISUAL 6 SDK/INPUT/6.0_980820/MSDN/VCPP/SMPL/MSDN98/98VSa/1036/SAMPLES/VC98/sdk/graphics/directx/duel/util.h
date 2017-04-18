/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:	util.h
 *  Content:	miscellaneous utilities include file
 *
 *
 ***************************************************************************/

#include <windows.h>

#define GUIDSTR_MAX 38
#define GUID_STRING_SIZE 64

int		StringFromGUID(GUID *lpguid, LPWSTR lpsz);
BOOL	IsEqualGuid(GUID *lpguid1, LPGUID lpguid2);
int		GetDigit(LPSTR lpstr);
void	ConvertField(LPBYTE lpByte,LPSTR * ppStr,int iFieldSize,BOOL fRightToLeft);
HRESULT GUIDFromString(LPWSTR lpWStr, GUID * pGuid);
int		WideToAnsi(LPSTR lpStr,LPWSTR lpWStr,int cchStr);
int		AnsiToWide(LPWSTR lpWStr,LPSTR lpStr,int cchWStr);
int		randInt( int low, int high );
double	randDouble( double low, double high );

