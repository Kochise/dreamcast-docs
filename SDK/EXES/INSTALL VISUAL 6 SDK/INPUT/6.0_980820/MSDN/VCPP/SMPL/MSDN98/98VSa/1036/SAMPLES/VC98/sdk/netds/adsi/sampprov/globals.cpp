/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    globals.cpp

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop

WCHAR * g_szProviderName = L"Sample";


KWDLIST KeywordList[MAX_KEYWORDS] =
{
    { TOKEN_USER, L"user"},
    { TOKEN_GROUP, L"group"},
    { TOKEN_OU, L"organizational unit"}
};

SYNTAXMAP g_aSampleDSSyntaxMap[] =
{
  /* 1 */
  { TEXT("String"),  TEXT("SampleDS Distinguished Name"),  VT_BSTR},

  /* 2 */
  { TEXT("Integer"),    TEXT("SampleDS Integer"),           VT_I4}

};

DWORD g_cSampleDSSyntaxMap = (sizeof(g_aSampleDSSyntaxMap)/sizeof(g_aSampleDSSyntaxMap[0]));


