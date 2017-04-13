/*************************************************************************
**
**  This is a part of the Microsoft Source Code Samples.
**
**  Copyright (C) 1992-1997 Microsoft Corporation. All rights reserved.
**
**  This source code is only intended as a supplement to Microsoft Development
**  Tools and/or WinHelp documentation.  See these sources for detailed
**  information regarding the Microsoft samples programs.
**
**  OLE Automation TypeLibrary Browse Helper Sample
**
**  main.cpp
**
**  new and delete operator redefinition to use memory manager of calling
**  task.
**  LibMain, WEP, DllGetClassObject, DllCanUnloadNow, DLL initialization.
**  Procedure to create standard dispatch implementation.
**
**  Written by Microsoft Product Support Services, Windows Developer Support
**
*************************************************************************/
#include <windows.h>
#include <windowsx.h>
#ifdef WIN16   
  #include <ole2.h>
  #include <compobj.h>    
  #include <dispatch.h> 
  #include <variant.h>
  #include <olenls.h>  
#endif 
#include <initguid.h>
#include "browseh.h"          

// Globals
HINSTANCE   g_hinst;                   // Instance of application
                                       //Count number of objects and number of locks.
ULONG       g_cObj=0;
ULONG       g_cLock=0;

// String resource buffers
TCHAR g_szServerName[STR_LEN];


/*
 * new
 *
 * Purpose:
 *   Since this is an InProcServer object, the memory allocator used by 
 *   the calling task must be used.
 *   This is done by redefining the global new operator and using new 
 *   for all memory allocations.
 */
void FAR* operator new(size_t size)
{
    IMalloc FAR* pMalloc;
    LPVOID lpv;

    if (CoGetMalloc(MEMCTX_TASK, &pMalloc) == NOERROR)
    {
        lpv = pMalloc->Alloc(size);
        pMalloc->Release();
        return lpv;
    }
    return NULL;
}

/*
 * delete
 *
 * Purpose:
 *   Use the memory manager of the calling task to free memory.
 */
void operator delete(void FAR* lpv)
{
    IMalloc FAR* pMalloc;

    if (lpv == NULL) return;

    if( CoGetMalloc(MEMCTX_TASK, &pMalloc) == NOERROR) 
    {
        if (pMalloc->DidAlloc(lpv))
            pMalloc->Free(lpv);
        pMalloc->Release();
    }
}


#ifdef WIN16
/*
 * LibMain
 *
 * Purpose:
 *  Called by Win16 on DLL load. Does any one-time initializations.
 *
 */
int PASCAL LibMain (HINSTANCE hinst, WORD wDataSeg, WORD cbHeapSize, LPSTR lpCmdLine)
{
   if (cbHeapSize != 0)
       UnlockData(0);
   
   g_hinst = hinst;    

   if (!InitDLL(hinst))
         return FALSE;

   return TRUE;
}

/*
 * WEP
 *
 * Purpose:
 *  Called by Windows on DLL unload. 
 *
 */
extern "C" void FAR PASCAL _WEP(int bSystemExit)
{
    return;
}

#else //Win 32

BOOL WINAPI DllMain (HINSTANCE hinst, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            if (!InitDLL(hinst))
                return FALSE;
            else return TRUE;

        default:
            return TRUE;
    }
}

#endif 

/*
 * DLLGetClassObject
 *
 * Purpose:
 *  OLE calls this funtion to obtain the class factory. Note that the class 
 *  factory is not registered by the inproc server. 
 *
 */
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid,
                                   LPVOID FAR *ppv)
{    
    LPCLASSFACTORY pcf;
    HRESULT hr;
    
    *ppv =  NULL;
    
    // Check if this CLSID is supported.
    if (rclsid != CLSID_BrowseHelper)
       return E_FAIL;
    
    // Create class factory and return it  
    pcf = new CBrowseHelperCF;  
    if (!pcf)
        return E_OUTOFMEMORY;  
    hr = pcf->QueryInterface(riid, ppv);
    if (FAILED(hr)) 
    {
        delete pcf;
        return hr;
    }          
    return NOERROR;
}

/*
 * DLLCanUnloadNow
 *
 * Purpose:
 *  DllCanUnloadNow is called by OLE to determine if the DLL can be unloded. 
 *
 */
STDAPI DllCanUnloadNow(void)
{  
    if (g_cObj==0L && g_cLock==0L)
        return S_OK;
    else return S_FALSE;
}     

/*
 * InitDLL
 *
 * Purpose:
 *  Load strings & Registers the window class
 *
 * Parameters:
 *  hinstance       hinstance of application
 *
 */
BOOL InitDLL (HINSTANCE hinst)
{  
   return LoadString(hinst, IDS_SERVERNAME, g_szServerName, sizeof(g_szServerName));
}

/*
 * Quick & Dirty ANSI/Unicode conversion routines. These routines use a static
 * buffer of fixed size to hold the converted string. Consequently these
 * routines are limited to strings of size STRCONVERT_MAXLEN. Also the same
 * buffer is reused when the routine is called a second time. So make sure
 * that the converted string is used before the conversion routine is called
 * again
 */
#ifdef WIN32

#ifndef UNICODE
char* ConvertToAnsi(OLECHAR FAR* szW)
{
  static char achA[STRCONVERT_MAXLEN]; 
  
  WideCharToMultiByte(CP_ACP, 0, szW, -1, achA, STRCONVERT_MAXLEN, NULL, NULL);  
  return achA; 
} 

OLECHAR* ConvertToUnicode(char FAR* szA)
{
  static OLECHAR achW[STRCONVERT_MAXLEN]; 

  MultiByteToWideChar(CP_ACP, 0, szA, -1, achW, STRCONVERT_MAXLEN);  
  return achW; 
}
#endif

#endif   
