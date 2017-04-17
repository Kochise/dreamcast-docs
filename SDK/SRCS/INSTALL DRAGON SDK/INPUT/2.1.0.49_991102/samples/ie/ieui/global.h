/********************************************************************
 * Copyright (c) 1999 Microsoft Corporation
 *
 * global.h
 *
 * Description
 *   Global types and variables.
 ********************************************************************/

#ifndef __GLOBAL_H
#define __GLOBAL_H

/********************************************************************
 * Includes
 ********************************************************************/
#include <mshtmhst.h>   // SHOWNHTMLDIALOGFN

/********************************************************************
 * Typedefs for functions from dynamically loaded DLLs
 ********************************************************************/
typedef HRESULT STDAPICALLTYPE CREATEURLMONIKER(IMoniker *pmkContext, LPWSTR pszURL, IMoniker **ppMoniker);

/********************************************************************
 * Global Variables
 ********************************************************************/
extern HINSTANCE         g_hinst;               // Instance of DLL
extern CREATEURLMONIKER *g_pfnCreateUrlMoniker; // CreateUrlMoniker function
extern SHOWHTMLDIALOGFN *g_pfnShowHTMLDialog;   // ShowHTMLDialog function
extern ULONG             g_ulLocks;             // Number of server locks

#endif // __GLOBAL_H
