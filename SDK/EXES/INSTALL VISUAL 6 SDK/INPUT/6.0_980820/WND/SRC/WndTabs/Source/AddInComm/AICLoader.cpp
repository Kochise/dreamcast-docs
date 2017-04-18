/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

// AddInComm Loader, (AIC 1.4.0 - December 2000)
// =============================================

// ** PRE-COMPILE HEADERS **
// if you don't want the loader to automatically use your pre-compiler
// header, comment out the following two lines:
//#include "stdafx.h"
//#define AICL_PCH

// automatically link with version.lib
#pragma comment(lib, "version.lib")



// this file includes itself; the following is a helper directive
#ifndef __AICLOADER_INCLUDE_LIST
#define __AICLOADER_INCLUDE_LIST

#ifndef AICL_PCH
#define STRICT 
#define LEAN_AND_MEAN
#include <windows.h>
#endif  // AICL_PCH

#include <assert.h>
#include <stdio.h>

#include "AICLoader.h"
#include "AddInComm.h"

// "#include __FILE__" doesn't work with Win9x, so define our own const:
#define AICL_THIS_FILE "AICLoader.cpp"   

// library names: release/debug
const char *s_pszDLLNameR = "AIC.mod";
const char *s_pszDLLNameD = "AICD.mod";

// old library names: release/debug
const char *s_pszDLLNameOldR = "AIC.dll";
const char *s_pszDLLNameOldD = "AICD.dll";

const char **s_ppszDLLNameToUse = 
#ifdef _DEBUG
    &s_pszDLLNameD;
#else
    &s_pszDLLNameR;
#endif

#undef AICL_TRACE
#ifdef _DEBUG
#define AICL_TRACE OutputDebugString
#else
#define AICL_TRACE(x) ((void)0)
#endif

static HINSTANCE s_hInst = NULL;   // library instance handle

// define the function pointer variables
#undef FN_DEF
#undef FN_DEF_NONCRIT
#define FN_DEF(name,a,b)          static LPVOID s_pfn##name = NULL;
#define FN_DEF_NONCRIT(name,a,b)  FN_DEF(name,a,b)
#include AICL_THIS_FILE


// this auto destructing object will ensure that the library is freed when
// the DevStudio exits
static struct auto_destruct 
{ 
    ~auto_destruct() { aiclUnloadAICLibrary(); }
} autodestruct;


HINSTANCE aiclLoadLibByFileName(HINSTANCE hMyInst, const char *pszFileName)
{
    HINSTANCE hInst;
    char      path[1024], *p;
    
    hInst = ::LoadLibraryA(pszFileName);

    if (!hInst)
    {
        // try the module directory
        GetModuleFileName(hMyInst, path, sizeof(path));
        p = strrchr(path, '\\');
        assert(p);
        strcpy(++p, pszFileName);
        hInst = ::LoadLibrary(path);
    }

    if (!hInst)
    {
        // try add-in directory
        aiclGetDSAddInDir((LPSTR)path, sizeof(path));

        if (path[0])
        {
            strcat(path, pszFileName);
            hInst = ::LoadLibrary(path);
        }
    }

    return hInst;
}


bool aiclLoadAICLibrary(HINSTANCE hInst)
{
    // try extended path
    s_hInst = aiclLoadLibByFileName(hInst, *s_ppszDLLNameToUse);

    if (!s_hInst)
    {
        // try registry key
        HKEY hKey;
        char path[_MAX_PATH];
        DWORD dwtype, dwLen = sizeof(path);

        if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
            "Software\\WndTabs.com\\AddInComm", 0, KEY_READ, &hKey) == 
            ERROR_SUCCESS)
        {
            if (::RegQueryValueEx(hKey, "Path", 0, &dwtype, 
                (LPBYTE)path, &dwLen) == ERROR_SUCCESS)
            {
                strcat(path, "\\");
                strcat(path, *s_ppszDLLNameToUse);
                s_hInst = ::LoadLibrary(path);
            }
            
            ::RegCloseKey(hKey);
        }    
    }

    if (!s_hInst)
    {
        // attempt to load using old library name
        s_hInst = aiclLoadLibByFileName(hInst, 
            (s_ppszDLLNameToUse == &s_pszDLLNameR)?
                s_pszDLLNameOldR : s_pszDLLNameOldD);
    }
    
    if (s_hInst)
    {
#undef FN_DEF
#undef FN_DEF_NONCRIT
#define FN_DEF_NONCRIT(name,a,b) \
    s_pfn##name = (LPVOID)::GetProcAddress(s_hInst, #name);
#define FN_DEF(name,a,b)  \
    FN_DEF_NONCRIT(name,a,b); \
    if (!s_pfn##name) \
    { \
        AICL_TRACE("*** AICLoader: Couldn't load function " #name \
              " - aborting\n"); \
        goto bad; \
    }
#include AICL_THIS_FILE
    }

out:
    return (s_hInst != NULL);

bad:
    aiclUnloadAICLibrary();
    goto out;
}

void aiclUnloadAICLibrary()
{
    if (s_hInst)
    {
        ::FreeLibrary(s_hInst);
        s_hInst = NULL;
    }
}


void aiclUseDebugLibrary(BOOL bUse)
{
    s_ppszDLLNameToUse = bUse? &s_pszDLLNameD : &s_pszDLLNameR;
}

bool aiclIsAICLoaded()
{
    return (s_hInst != NULL);
}


// == Misc Functions == //

bool aiclGetFileVersion(LPCTSTR pszPath, LPSTR out_pszVer)
{
    DWORD   DataLen, Zero;
    PVOID   pData, pValue;
    UINT    ValueLen;
    TCHAR   buf[50];
    DWORD   dwTranslation;

    // assume the worst
    out_pszVer[0] = '\0';
   
    if ((DataLen = GetFileVersionInfoSize((char *)pszPath, &Zero)) == 0)
    {
        return false;
    }

    pData = new char[DataLen];
    GetFileVersionInfo((char *)pszPath, NULL, DataLen, pData);

    VerQueryValue (pData, "\\VarFileInfo\\Translation", &pValue, &ValueLen);
    if (ValueLen >= 4)
    {
        dwTranslation = *(DWORD *)pValue;
        sprintf(buf, "\\StringFileInfo\\%04x%04x\\ProductVersion",
            LOWORD(dwTranslation), HIWORD(dwTranslation));

        VerQueryValue(pData, buf, &pValue, &ValueLen);

        memcpy(out_pszVer, pValue, ValueLen);
    }

    delete [] pData;

    return true;
}


bool aiclGetModuleVersion(LPCTSTR pszMod, LPSTR out_pszVer)
{
    char path[1024];
    HMODULE hModule;

    hModule = GetModuleHandle(pszMod);
    if (hModule)
    {
        GetModuleFileName(hModule, (LPSTR)path, sizeof(path));
        return aiclGetFileVersion(path, out_pszVer);
    }
    else
    {
        out_pszVer[0] = '\0';
    }

    return false;
}


bool aiclGetDSCurrentUserRegKey(LPSTR out_pszKeyName)
{
    char buf[1024];
    static const char *MSDEV_aliases[] = { 
        "MSDEV.EXE",   // Microsoft (R) Visual C++
//      "CEPB.EXE",    // Microsoft (R) Windows CE Platform Builder
        "EVC.EXE" };   // Microsoft (R) eMbedded Visual C++

    static const char *Reg_Keys[] = {
        "Software\\Microsoft\\DevStudio\\?.0",
//      ""   // the registry key for PB doesn't match the file ver!
        "Software\\Microsoft\\CEStudio\\?.0\\evc"
        };

    for (int i = 0; i < sizeof(MSDEV_aliases)/sizeof(MSDEV_aliases[0]); i++)
    {
        if (aiclGetModuleVersion(MSDEV_aliases[i], (LPSTR)buf))
        {
            strcpy(out_pszKeyName, Reg_Keys[i]);
            char *p = strchr(out_pszKeyName, '?');
            if (p) 
            {
                *p = buf[0];
                return true;
            }
            return false;
        }
    }
    
    out_pszKeyName[0] = '\0';
    return false;
}

void aiclGetDSAddInDir(LPSTR out_pszPath, DWORD cb)
{
    HKEY hKey;
    DWORD type;
    char *p = NULL;

    aiclGetDSCurrentUserRegKey(out_pszPath);
    strcat(out_pszPath, "\\Directories");

    if (::RegOpenKeyEx(HKEY_CURRENT_USER, out_pszPath, 0, KEY_READ, &hKey) ==
        ERROR_SUCCESS)
    {
        if (::RegQueryValueEx(hKey, "Install Dirs", 0, &type, 
            (LPBYTE)out_pszPath, &cb) == ERROR_SUCCESS)
        {
            p = strrchr(out_pszPath, '\\');
            if (p)
            {
                strcpy(p + 1, "AddIns\\");
            }
        }
        ::RegCloseKey(hKey);
    }

    if (!p)
    {
        out_pszPath[0] = '\0';
    }
}


// == Function Stubs == //

static __declspec(naked) retnull()
{
    _asm {
        xor eax, eax
        ret
    }
}

// create the function stubs
#undef FN_DEF
#undef FN_DEF_NONCRIT
#define FN_DEF(name, ret, params) \
    ret __declspec(naked) name params \
    { \
        if (s_hInst) \
            __asm { jmp s_pfn##name } \
        else \
            __asm { jmp retnull }; \
    }
#define FN_DEF_NONCRIT(name, ret, params) \
    ret __declspec(naked) name params \
    { \
        if (s_hInst && s_pfn##name) \
            __asm { jmp s_pfn##name } \
        else \
            __asm { jmp retnull }; \
    } 
#include AICL_THIS_FILE

#else  // __AICLOADER_INCLUDE_LIST

// function list
FN_DEF(AICRegisterAddIn, HADDIN, (LPCTSTR pName, int iVerMaj, int iVerMin, int iVerExtra, AddinCmdHandler_t *pCmdFn))
FN_DEF(AICUnregisterAddIn, bool, (HADDIN hAddIn));
FN_DEF(AICGetAddInCount, int, ());
FN_DEF(AICGetAddInList, void, (HADDIN addin_array[]));
FN_DEF(AICGetAddIn, HADDIN, (LPCTSTR pName));
FN_DEF(AICGetAddInName, LPCTSTR, (HADDIN hAddIn));
FN_DEF(AICGetAddInVersion, void, (HADDIN hAddIn, int& iVerMaj, int& iVerMin, int& iVerExtra));
FN_DEF(AICSendCommand, int, (HADDIN hAddIn, LPCTSTR pCommand));
FN_DEF(AICGetDllVersion, void, (int& iVerMaj, int& iVerMin, int& iVerExtra));

// non-critical functions: loading will not fail if these functions aren't
// found
FN_DEF_NONCRIT(AICGetAddInVersionString, LPCTSTR, (HADDIN HADDIN))
FN_DEF_NONCRIT(AICSetAddInVersionString, void, (HADDIN hAddIn, LPCTSTR pszVerStr))

#endif  // __AICLOADER_INCLUDE_LIST
