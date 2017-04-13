
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1994-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

//---------------------------------------------------------------------------
//
// File: dropext.c
//
//  This file contains a sample source code of context menu extension handler.
//
//---------------------------------------------------------------------------

#include "priv.h"

//
// Initialize GUIDs (should be done only and at-least once per DLL/EXE)
//
#pragma data_seg(".text")
#define INITGUID
#include <initguid.h>
#include "dropext.h"
#pragma data_seg()

//
// Function prototypes
//
HRESULT CALLBACK DropExt_CreateInstance(LPUNKNOWN, REFIID, LPVOID FAR*);

//
// Global variables
//
UINT g_cRefThisDll = 0;		// Reference count of this DLL.
UINT g_cfNetResource = 0;	// Clipboard format

//---------------------------------------------------------------------------
// LibMain
//---------------------------------------------------------------------------
BOOL APIENTRY LibMain(HANDLE hDll, DWORD dwReason, LPVOID lpReserved)
{
    switch(dwReason)
    {
    case DLL_PROCESS_ATTACH:
    	break;
    case DLL_PROCESS_DETACH:
    	break;

    case DLL_THREAD_DETACH:
        break;

    case DLL_THREAD_ATTACH:
    default:
    	break;
    } // end switch()

    return TRUE;
}

//---------------------------------------------------------------------------
// DllCanUnloadNow
//---------------------------------------------------------------------------

STDAPI DllCanUnloadNow(void)
{
    return ResultFromScode((g_cRefThisDll==0) ? S_OK : S_FALSE);
}

//---------------------------------------------------------------------------
//
// DllGetClassObject
//
//  This is the entry of this DLL, which all the In-Proc server DLLs should
// export. See the description of "DllGetClassObject" of OLE 2.0 reference
// manual for detail.
//
//---------------------------------------------------------------------------

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID FAR* ppvOut)
{
    //
    //  This DLL has only one class (CLSID_SampleDropExt). If a DLL supports
    // multiple classes, it should have either multiple if-statements or
    // efficient table lookup code.
    //
    if (IsEqualIID(rclsid, &CLSID_SampleDropExt))
    {
	//
	//  We are supposed return the class object for this class. Instead
	// of fully implementing it in this DLL, we just call a helper
	// function in the shell DLL which creates a default class factory
	// object for us. When its CreateInstance member is called, it
	// will call back our create instance function (DropExt_CreateInstance).
	//
	return SHCreateDefClassObject(
		    riid,		    //
		    ppvOut,		    //
		    DropExt_CreateInstance, // callback function
		    &g_cRefThisDll,	    // reference count of this DLL
		    &IID_IShellExtInit	    // init interface
		    );
    }

    return ResultFromScode(E_FAIL);
}


//---------------------------------------------------------------------------
//
// CSampleDropExt class
//
// In C++:
//  class CSampleDropExt : protected IContextMenu, protected IShellExtInit
//  {
//  protected:
//      UINT         _cRef;
//      LPDATAOBJECT _pdtobj;
//	HKEY	     _hkeyProgID;
//  public:
//      CSampleDropExt() _cRef(1), _pdtobj(NULL), _hkeyProgID(NULL) {};
//      ...
//  };
//
//---------------------------------------------------------------------------
typedef struct _CSampleDropExt	// smx
{
    IContextMenu    _ctm;           // 1st base class
    IShellExtInit   _sxi;	    // 2nd base class
    UINT            _cRef;          // reference count
    LPDATAOBJECT    _pdtobj;	    // data object
    HKEY	    _hkeyProgID;    // reg. database key to ProgID
    char	    _szTargetFolder[MAX_PATH];
} CSampleDropExt, * PSAMPLEDROPEXT;

#define SMX_OFFSETOF(x)	        ((UINT)(&((PSAMPLEDROPEXT)0)->x))
#define PVOID2PSMX(pv,offset)   ((PSAMPLEDROPEXT)(((LPBYTE)pv)-offset))
#define PCTM2PSMX(pctm)	        PVOID2PSMX(pctm, SMX_OFFSETOF(_ctm))
#define PSXI2PSMX(psxi)	        PVOID2PSMX(psxi, SMX_OFFSETOF(_sxi))

//
// Vtable prototype
//
extern IContextMenuVtbl     c_SampleDropExt_CTMVtbl;
extern IShellExtInitVtbl    c_SampleDropExt_SXIVtbl;

//---------------------------------------------------------------------------
//
// DropExt_CreateInstance
//
//  This function is called back from within IClassFactory::CreateInstance()
// of the default class factory object, which is created by SHCreateClassObject.
//
//---------------------------------------------------------------------------

HRESULT CALLBACK DropExt_CreateInstance(LPUNKNOWN punkOuter,
				        REFIID riid, LPVOID FAR* ppvOut)
{
    HRESULT hres;
    PSAMPLEDROPEXT psmx;

    //
    // Shell extentions typically does not support aggregation.
    //
    if (punkOuter) {
	return ResultFromScode(CLASS_E_NOAGGREGATION);
    }

    //
    // in C++:
    //  psmx = new CSampleDropExt();
    //
    psmx = LocalAlloc(LPTR, sizeof(CSampleDropExt));
    if (!psmx) {
	return ResultFromScode(E_OUTOFMEMORY);
    }
    psmx->_ctm.lpVtbl = &c_SampleDropExt_CTMVtbl;
    psmx->_sxi.lpVtbl = &c_SampleDropExt_SXIVtbl;
    psmx->_cRef = 1;
    psmx->_pdtobj = NULL;
    psmx->_hkeyProgID = NULL;
    g_cRefThisDll++;

    //
    // in C++:
    //  hres = psmx->QueryInterface(riid, ppvOut);
    //  psmx->Release();
    //
    // Note that the Release member will free the object, if QueryInterface
    // failed.
    //
    hres = c_SampleDropExt_CTMVtbl.QueryInterface(&psmx->_ctm, riid, ppvOut);
    c_SampleDropExt_CTMVtbl.Release(&psmx->_ctm);

    return hres;	// S_OK or E_NOINTERFACE
}


//---------------------------------------------------------------------------
// CSampleDropExt::Initialize (IShellExtInit override)
//---------------------------------------------------------------------------
STDMETHODIMP DropExt_Initialize(LPSHELLEXTINIT psxi,
		LPCITEMIDLIST pidlFolder,
		LPDATAOBJECT pdtobj,
		HKEY hkeyProgID)
{
    PSAMPLEDROPEXT this = PSXI2PSMX(psxi);

    // Initialize can be called more than once.
    if (this->_pdtobj) {
	this->_pdtobj->lpVtbl->Release(this->_pdtobj);
    }

    if (this->_hkeyProgID) {
	RegCloseKey(this->_hkeyProgID);
    }

    // Duplicate the pdtobj pointer
    if (pdtobj) {
	this->_pdtobj = pdtobj;
	pdtobj->lpVtbl->AddRef(pdtobj);
    }

    // Duplicate the handle
    if (hkeyProgID) {
	RegOpenKeyEx(hkeyProgID, NULL, 0L, MAXIMUM_ALLOWED, &this->_hkeyProgID);
    }

    // Get the path to the drop target folder
    if (pidlFolder) {
	SHGetPathFromIDList(pidlFolder, this->_szTargetFolder);
    }

    return NOERROR;
}

STDMETHODIMP DropExt_QueryContextMenu(LPCONTEXTMENU pctm,
                                               HMENU hmenu,
                                               UINT indexMenu,
                                               UINT idCmdFirst,
                                               UINT idCmdLast,
					       UINT uFlags)
{
    UINT idCmd = idCmdFirst;
    InsertMenu(hmenu, indexMenu++, MF_STRING|MF_BYPOSITION, idCmd++, "Check H&DROP (dropext)");
    InsertMenu(hmenu, indexMenu++, MF_STRING|MF_BYPOSITION, idCmd++, "Check H&NRES (dropext)");
    return ResultFromScode(MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_NULL, (USHORT)2));
}

//
// Converts an offset to a string to a string pointer.
//
LPCSTR _Offset2Ptr(LPSTR pszBase, UINT offset, UINT * pcb)
{
    LPSTR pszRet;
    if (offset==0) {
	pszRet = NULL;
	*pcb = 0;
    } else {
	pszRet = pszBase + offset;
	*pcb = lstrlen(pszRet) + 1;
    }
    return pszRet;
}

//
// This is a helper routine which extracts a specified NETRESOURCE from hnres.
//
UINT DropExt_GetNetResource(HGLOBAL hnres, UINT iItem, LPNETRESOURCE pnresOut, UINT cbMax)
{
    LPNRESARRAY panr = GlobalLock(hnres);
    UINT iRet = 0;	// assume error
    if (hnres)
    {
	if (iItem==(UINT)-1)
	{
	    iRet = panr->cItems;
	}
	else if (iItem < panr->cItems)
	{
	    UINT cbProvider, cbRemoteName;
	    LPCSTR pszProvider = _Offset2Ptr((LPSTR)panr, (UINT)panr->nr[iItem].lpProvider, &cbProvider);
	    LPCSTR pszRemoteName = _Offset2Ptr((LPSTR)panr, (UINT)panr->nr[iItem].lpRemoteName, &cbRemoteName);
	    iRet = sizeof(NETRESOURCE) + cbProvider + cbRemoteName;
	    if (iRet <= cbMax)
	    {
		LPSTR psz = (LPSTR)(pnresOut+1);
		*pnresOut = panr->nr[iItem];
		if (pnresOut->lpProvider) {
		    pnresOut->lpProvider = psz;
		    lstrcpy(psz, pszProvider);
		    psz += cbProvider;
		}
		if (pnresOut->lpRemoteName) {
		    pnresOut->lpRemoteName = psz;
		    lstrcpy(psz, pszRemoteName);
		}
	    }
	}
	GlobalUnlock(hnres);
    }
    return iRet;
}

HRESULT DropExt_CheckForHDROP(PSAMPLEDROPEXT this, HWND hwnd)
{
    FORMATETC fmte = {
        	CF_HDROP,
        	(DVTARGETDEVICE FAR *)NULL,
        	DVASPECT_CONTENT,
        	-1,
        	TYMED_HGLOBAL };
    STGMEDIUM medium;
    HRESULT hres = this->_pdtobj->lpVtbl->GetData(this->_pdtobj, &fmte, &medium);

    if (SUCCEEDED(hres))
    {
	HDROP hdrop = medium.hGlobal;
	UINT cFiles = DragQueryFile(hdrop, (UINT)-1, NULL, 0);
	char szFile[MAX_PATH];
	char szBuf[MAX_PATH*2+64];

	DragQueryFile(hdrop, 0, szFile, sizeof(szFile));
	wsprintf(szBuf,
		 "The drop target is %s.\n"
	 	 "%d files/directories in HDROP\n"
		 "The path to the first object is\n"
   		 "\t%s.",
		 this->_szTargetFolder,
		 cFiles,
		 szFile);

	MessageBox(hwnd, szBuf, "DropExt", MB_OK);

	//
	// HACK: We are supposed to call ReleaseStgMedium. This is a temporary
	//  hack until OLE 2.01 for Windows 95 is released.
	//
	if (medium.pUnkForRelease)
	{
	    medium.pUnkForRelease->lpVtbl->Release(medium.pUnkForRelease);
	}
	else
	{
	    GlobalFree(medium.hGlobal);
	}
    }
    else
    {
	MessageBox(hwnd, "No file system object in the selection", "DropExt", MB_OK);
    }

    return hres;
}

HRESULT DropExt_CheckForHNRES(PSAMPLEDROPEXT this, HWND hwnd)
{
    FORMATETC fmte = {
        	g_cfNetResource ? g_cfNetResource
		    : (g_cfNetResource=RegisterClipboardFormat("Net Resource")),
        	(DVTARGETDEVICE FAR *)NULL,
        	DVASPECT_CONTENT,
        	-1,
        	TYMED_HGLOBAL };
    STGMEDIUM medium;
    HRESULT hres = this->_pdtobj->lpVtbl->GetData(this->_pdtobj, &fmte, &medium);
    if (SUCCEEDED(hres))
    {
	HGLOBAL hnres = medium.hGlobal;
	LPNETRESOURCE pnr = (LPNETRESOURCE)LocalAlloc(LPTR, 1024);

	if (pnr)
	{
	    char szBuf[512];
	    UINT cItems = DropExt_GetNetResource(hnres, (UINT)-1, NULL, 0);

	    // Get the NETRESOURCE of the first item
	    DropExt_GetNetResource(hnres, 0, pnr, 1024);

	    wsprintf(szBuf,
		     "%d network resource objects in HNRES\n"
		     "The attributes of the first object are\n"
		     "\tProvider      = %s\n"
		     "\tRemoteName    = %s\n"
		     "\tdwDisplayType = %x\n"
		     "\tdwType        = %x\n"
		     "\tdwUsage       = %x\n",
		     cItems,
		     pnr->lpProvider,
		     pnr->lpRemoteName ? pnr->lpRemoteName : "N/A",
		     pnr->dwDisplayType,
		     pnr->dwType,
		     pnr->dwUsage);

	    MessageBox(hwnd, szBuf, "DropExt", MB_OK);

	    LocalFree(pnr);
	}
	else
	{
	    hres = ResultFromScode(E_OUTOFMEMORY);
	}

	//
	// HACK: We are supposed to call ReleaseStgMedium. This is a temporary
	//  hack until OLE 2.01 for Windows 95 is released.
	//
	if (medium.pUnkForRelease)
	{
	    medium.pUnkForRelease->lpVtbl->Release(medium.pUnkForRelease);
	}
	else
	{
	    GlobalFree(medium.hGlobal);
	}
    }
    else
    {
	MessageBox(hwnd, "No network objects in the selection", "DropExt", MB_OK);
    }
    return hres;
}

STDMETHODIMP DropExt_InvokeCommand(LPCONTEXTMENU pctm,
				   LPCMINVOKECOMMANDINFO lpici)
{
    PSAMPLEDROPEXT this = PCTM2PSMX(pctm);
    HRESULT hres = ResultFromScode(E_INVALIDARG);	// assume error
    //
    // No need to support string based command.
    //
    if (!HIWORD(lpici->lpVerb))
    {
	UINT idCmd = LOWORD(lpici->lpVerb);

	switch(idCmd)
	{
	case 0:
	    hres = DropExt_CheckForHDROP(this, lpici->hwnd);
	    break;

	case 1:
	    hres = DropExt_CheckForHNRES(this, lpici->hwnd);
	    break;
	}
    }
    return hres;
}

STDMETHODIMP DropExt_GetCommandString(
                                        LPCONTEXTMENU pctm,
                                        UINT        idCmd,
                                        UINT        wReserved,
                                        UINT FAR *  pwReserved,
                                        LPSTR       pszName,
                                        UINT        cchMax)
{
    return NOERROR;
}

//---------------------------------------------------------------------------
// CSampleDropExt::AddRef (IContextMenu override)
//---------------------------------------------------------------------------

STDMETHODIMP_(UINT) DropExt_CTM_AddRef(LPCONTEXTMENU pctm)
{
    PSAMPLEDROPEXT this = PCTM2PSMX(pctm);
    return ++this->_cRef;
}


//---------------------------------------------------------------------------
// CSampleDropExt::AddRef (IShellExtInit override)
//---------------------------------------------------------------------------

STDMETHODIMP_(UINT) DropExt_SXI_AddRef(LPSHELLEXTINIT psxi)
{
    PSAMPLEDROPEXT this = PSXI2PSMX(psxi);
    return ++this->_cRef;
}

//---------------------------------------------------------------------------
// CSampleDropExt::Release (IContextMenu override)
//---------------------------------------------------------------------------

STDMETHODIMP_(UINT) DropExt_CTM_Release(LPCONTEXTMENU pctm)
{
    PSAMPLEDROPEXT this = PCTM2PSMX(pctm);
    if (--this->_cRef) {
	return this->_cRef;
    }

    if (this->_pdtobj) {
	this->_pdtobj->lpVtbl->Release(this->_pdtobj);
    }

    if (this->_hkeyProgID) {
	RegCloseKey(this->_hkeyProgID);
    }

    LocalFree((HLOCAL)this);
    g_cRefThisDll--;

    return 0;
}

//---------------------------------------------------------------------------
// CSampleDropExt::Release (IShellExtInit thunk)
//---------------------------------------------------------------------------

STDMETHODIMP_(UINT) DropExt_SXI_Release(LPSHELLEXTINIT psxi)
{
    PSAMPLEDROPEXT this = PSXI2PSMX(psxi);
    return DropExt_CTM_Release(&this->_ctm);
}

//---------------------------------------------------------------------------
// CSampleDropExt::QueryInterface (IContextMenu override)
//---------------------------------------------------------------------------

STDMETHODIMP DropExt_CTM_QueryInterface(LPCONTEXTMENU pctm, REFIID riid, LPVOID FAR* ppvOut)
{
    PSAMPLEDROPEXT this = PCTM2PSMX(pctm);
    if (IsEqualIID(riid, &IID_IContextMenu) || IsEqualIID(riid, &IID_IUnknown))
    {
        (LPCONTEXTMENU)*ppvOut=pctm;
        this->_cRef++;
        return NOERROR;
    }
    if (IsEqualIID(riid, &IID_IShellExtInit))
    {
        (LPSHELLEXTINIT)*ppvOut=&this->_sxi;
        this->_cRef++;
        return NOERROR;
    }
    return ResultFromScode(E_NOINTERFACE);
}

//---------------------------------------------------------------------------
// CSampleDropExt::QueryInterface (IShellExtInit thunk)
//---------------------------------------------------------------------------

STDMETHODIMP DropExt_SXI_QueryInterface(LPSHELLEXTINIT psxi, REFIID riid, LPVOID FAR* ppv)
{
    PSAMPLEDROPEXT this = PSXI2PSMX(psxi);
    return DropExt_CTM_QueryInterface(&this->_ctm, riid, ppv);
}


//---------------------------------------------------------------------------
// CSampleDropExt class : Vtables
//---------------------------------------------------------------------------

#pragma data_seg(".text")
IContextMenuVtbl c_SampleDropExt_CTMVtbl = {
    DropExt_CTM_QueryInterface,
    DropExt_CTM_AddRef,
    DropExt_CTM_Release,
    DropExt_QueryContextMenu,
    DropExt_InvokeCommand,
    DropExt_GetCommandString,
};

IShellExtInitVtbl c_SampleDropExt_SXIVtbl = {
    DropExt_SXI_QueryInterface,
    DropExt_SXI_AddRef,
    DropExt_SXI_Release,
    DropExt_Initialize
};
#pragma data_seg()
