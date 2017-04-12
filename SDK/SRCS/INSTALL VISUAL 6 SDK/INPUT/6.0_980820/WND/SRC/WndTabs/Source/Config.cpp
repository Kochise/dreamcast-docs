/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// Config.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/* Registry section */
static LPCTSTR s_pszSection = "";


// define the variables:
#define CFG_VAR(name, type, var, defval) type var = defval;
#define CFG_STR(name, var, defval)       CString var = defval;
#include "config.h"


struct IntCfgVar
{
    LPCTSTR     cKeyName;
    int *       pVar;       
};

struct StrCfgVar
{
    LPCTSTR     cKeyName;
    CString *   pVar;       
};


// the variable <-> registry key translation lists
IntCfgVar IntCfgVars[] =
{
#undef CFG_VAR
#undef CFG_STR
#define CFG_VAR(name, type, var, defval) { #name, ((int *)&var) },
#define CFG_STR(name, var, defval) 
#include "config.h"
    { NULL, NULL }
};

StrCfgVar StrCfgVars[] =
{
#undef CFG_VAR
#undef CFG_STR
#define CFG_VAR(name, type, var, defval)
#define CFG_STR(name, var, defval)       { #name, &var },
#include "config.h"
    { NULL, NULL }
};


const unsigned cIntCfgVars = (sizeof(IntCfgVars)/sizeof(IntCfgVars[0]) - 1);
const unsigned cStrCfgVars = (sizeof(StrCfgVars)/sizeof(StrCfgVars[0]) - 1);


/////////////////////////////////////////////////////////////////////////////
// Configuration persistence

BOOL WriteCfgInt(LPCTSTR lpszEntry, int nValue)
{
    return AfxGetApp()->WriteProfileInt(s_pszSection, lpszEntry, nValue);
}

UINT GetCfgInt(LPCTSTR lpszEntry, int nDefault)
{
    return AfxGetApp()->GetProfileInt(s_pszSection, lpszEntry, nDefault);
}

BOOL WriteCfgString(LPCTSTR lpszEntry, LPCTSTR lpszValue)
{
    return AfxGetApp()->WriteProfileString(s_pszSection, lpszEntry, lpszValue);
}

CString GetCfgString(LPCTSTR lpszEntry, LPCTSTR lpszDefault)
{
    return AfxGetApp()->GetProfileString(s_pszSection, lpszEntry, lpszDefault);
}

#define GETINT(name, var) var = GetCfgInt(name, var);

void GetConfiguration()
{
    unsigned i;

    for (i = 0; i < cIntCfgVars; i++)
    {
        (*IntCfgVars[i].pVar) = 
            GetCfgInt(IntCfgVars[i].cKeyName, *IntCfgVars[i].pVar);
    }

    for (i = 0; i < cStrCfgVars; i++)
    {
        (*StrCfgVars[i].pVar) = 
            GetCfgString(StrCfgVars[i].cKeyName, *StrCfgVars[i].pVar);
    }
}

void WriteConfiguration()
{
    unsigned i;

    for (i = 0; i < cIntCfgVars; i++)
    {
        WriteCfgInt(IntCfgVars[i].cKeyName, *IntCfgVars[i].pVar);
    }

    for (i = 0; i < cStrCfgVars; i++)
    {
        WriteCfgString(StrCfgVars[i].cKeyName, *StrCfgVars[i].pVar);
    }
}

/////////////////////////////////////////////////////////////////////////////
// Registry Section Information

void CfgSetRegSection(LPCTSTR pszSection)
{
    s_pszSection = pszSection;
}

void CfgGetRegSection(LPCTSTR *ppszSection)
{
    *ppszSection = s_pszSection;
}
