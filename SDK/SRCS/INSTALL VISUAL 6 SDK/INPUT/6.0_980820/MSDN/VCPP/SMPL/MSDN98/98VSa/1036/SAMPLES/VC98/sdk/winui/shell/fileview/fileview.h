//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright  1994-1996  Microsoft Corporation.  All Rights Reserved.
//
//	PROGRAM: FILEVIEW.H	
//
//	PURPOSE:   File Viewer Component Object to work with Windows 95 Explorer.
//	  Definitions, classes, and prototypes for a FileViewer DLL.
//    Necessary modifications marked with MODIFY
//
//	PLATFORMS:	Windows 95
//
//	SPECIAL INSTRUCTIONS: N/A
//
#ifndef _FILEVIEW_H_
#define _FILEVIEW_H_


//Prevent windows.h from pulling in OLE 1
#define INC_OLE2

#include <windows.h>
#include <stdlib.h>
#include <ole2.h>
#include <commdlg.h>
#include <shlobj.h>


#include "dbgout.h"
#include "cstrtabl.h"
#include "cstathlp.h"

//Types needed for other include files.
#ifndef PPVOID
typedef LPVOID * PPVOID;
#endif


/*
 * Type and function for an object-destroyed callback.  An
 * Object will call ObjectDestoyed in FILEVIEW.CPP when it
 * deletes itself.  That way the server code, independent
 * of the object, can implement DllCanUnloadNow properly.
 */
typedef void (WINAPI *PFNDESTROYED)(void);
void WINAPI ObjectDestroyed(void);


//MODIFY:  Other viewer-specific headers
#include "fvtext.h"     //FileViewer specifics
#include "resource.h"   //Resource definitions



//FILEVIEW.CPP
HRESULT PASCAL DllGetClassObject(REFCLSID, REFIID, PPVOID);
STDAPI         DllCanUnloadNow(void);

//A class factory that creates CFileViewer objects
class CFVClassFactory : public IClassFactory
    {
    protected:
        ULONG           m_cRef;

    public:
        CFVClassFactory(void);
        ~CFVClassFactory(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP         CreateInstance(LPUNKNOWN, REFIID, PPVOID);
        STDMETHODIMP         LockServer(BOOL);
    };

typedef CFVClassFactory *PCFVClassFactory;

#endif //_FILEVIEW_H_
