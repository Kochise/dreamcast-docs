//=--------------------------------------------------------------------------=
// CDocObj.H
//=--------------------------------------------------------------------------=
// Copyright 1995 - 1997 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for the document object server class.
//
#ifndef __CDOCOBJ_H_
#define __CDOCOBJ_H_

#ifndef __MKTYPLIB__

#include <IPServer.H>
#include <internet.h>

//=--------------------------------------------------------------------------=
// DOCOBJECTINFO
//=--------------------------------------------------------------------------=
// for each DocObject you wish to expose to the programmer/user, you need to
// declare and define one of the following structures.  the first part should
// follow the rules of the CONTROLOBJECTINFO structure.  
// once this structre is declared/defined, an entry should be put in the
// global g_ObjectInfo table.
//
typedef struct {
    CONTROLOBJECTINFO ControlInfo;            // control, automation and creation information
	DWORD             dwMiscDocObj;	    // value of DocObject subkey
	BOOL              bPrint;		    // IPrint interface supported
	UINT		      nIDszExt;		    // resource ID of default file extension
	UINT              nIDszFileDescription; // resource ID of file description 
} DOCOBJECTINFO;

#ifndef INITOBJECTS

#define DEFINE_DOCOBJECT(name, clsid, progid, fn, ver, riid, pszh, piide, dwcf, dwap, w, szwc, cpp, rgppg, ccv, rgcv, dwmisc, bprint, nidext, niddesc) \
extern DOCOBJECTINFO name##DocObj \

#else
#define DEFINE_DOCOBJECT(name, clsid, progid, fn, ver, riid, pszh, piide, dwcf, dwap, w, szwc, cpp, rgppg, ccv, rgcv, dwmisc, bprint, nidext, niddesc) \
DOCOBJECTINFO name##DocObj = { { { {clsid, progid, fn}, ver, riid, pszh, NULL, 0}, piide, dwcf, dwap, TRUE, FALSE, w, szwc, FALSE, cpp, rgppg, ccv, rgcv, NULL }, dwmisc, bprint, nidext, niddesc }\


#endif // !INITOBJECTS

#define MISCFLAGSOFDOCOBJECT(index)         ((DOCOBJECTINFO *)(g_ObjectInfo[index].pInfo))->dwMiscDocObj
#define PRINTOFDOCOBJECT(index)             ((DOCOBJECTINFO *)(g_ObjectInfo[index].pInfo))->bPrint
#define DEFAULTEXTIDOFDOCOBJECT(index)      ((DOCOBJECTINFO *)(g_ObjectInfo[index].pInfo))->nIDszExt
#define FILEDESCRIPTIONIDOFDOCOBJECT(index) ((DOCOBJECTINFO *)(g_ObjectInfo[index].pInfo))->nIDszFileDescription


// this is the macros you should use to fill in the table.  Note that the name
// must be exactly the same as that used in the global structure you created
// for this object.
//
// if we were adding docobj support right into the framework, we would
// put this definition in localobj.h, and instead of using the OI_CONTROL
// type, we would define a new type (eg OI_DOCOBJ). 
//
#define DOCOBJECT(name)    { OI_CONTROL,      (void *)&(name##DocObj) }


//=--------------------------------------------------------------------------=
// CDocumentObject
//=--------------------------------------------------------------------------=
//
// if you don't want internet-aware support, change BASECLASS to COleControl
//
#define BASECLASS   CInternetControl

class CDocumentObject : public BASECLASS, public IOleDocument, public IOleDocumentView
{
public:
    // constructor and destructor
    //
    CDocumentObject(IUnknown* pUnkOuter, int iPrimaryDispatch, void* pMainInterface);
    virtual ~CDocumentObject();

    // IUnknown methods
    //
    DECLARE_STANDARD_UNKNOWN();

    // IOleObject method overrides for DocObject support
    STDMETHOD(SetClientSite)(IOleClientSite* pClientSite);
    STDMETHOD(DoVerb)(LONG iVerb, LPMSG lpmsg, IOleClientSite  *pActiveSite, LONG lindex,
                                     HWND hwndParent, LPCRECT lprcPosRect);
    STDMETHOD(SetExtent)(DWORD dwDrawAspect, SIZEL *psizel);
    STDMETHOD(Unadvise)(DWORD dwConnection);

    // IOleDocument -- required DocObject server interface
    //
    STDMETHOD(CreateView)(IOleInPlaceSite* pIPSite, IStream* pstm,
                          DWORD dwReserved, IOleDocumentView** ppView);
    STDMETHOD(GetDocMiscStatus)(DWORD* pdwStatus);
    STDMETHOD(EnumViews)(IEnumOleDocumentViews** ppEnum, IOleDocumentView** ppView);
    
    // IOleDocumentView -- required DocObject server interface
    //
    STDMETHOD(SetInPlaceSite)(IOleInPlaceSite* pIPSite);
    STDMETHOD(GetInPlaceSite)(IOleInPlaceSite** ppIPSite);
    STDMETHOD(GetDocument)(IUnknown** ppunk);
    STDMETHOD(SetRect)(LPRECT prcView);
    STDMETHOD(GetRect)(LPRECT prcView);
    STDMETHOD(SetRectComplex)(LPRECT prcView, LPRECT prcHScroll,
                              LPRECT prcVScroll, LPRECT prcSizeBox);
    STDMETHOD(Show)(BOOL fShow);
    STDMETHOD(UIActivate)(BOOL fUIActivate);
    STDMETHOD(Open)(void);
    STDMETHOD(CloseView)(ULONG ulReserved);
    STDMETHOD(SaveViewState)(LPSTREAM pstm);
    STDMETHOD(ApplyViewState)(LPSTREAM pstm);
    STDMETHOD(Clone)(IOleInPlaceSite* pIPSiteNew, IOleDocumentView** ppViewNew);

    // Override base class implementation...
    virtual HRESULT InternalQueryInterface(REFIID, void**);

protected:
    BOOL              m_fDocObj;
    IOleDocumentSite* m_pDocSite;
    IOleInPlaceSite*  m_pViewSite;

    // Functions to override to save/restore view state
    virtual HRESULT OnSaveViewState(IStream* pstm);
    virtual HRESULT OnApplyViewState(IStream* pstm);

    // Helper function for DocObject activation
    HRESULT ActivateAsDocObject(LONG lVerb);

};


//=--------------------------------------------------------------------------=
// helper functions
//=--------------------------------------------------------------------------=
//
BOOL RegisterDocObject(LPCSTR pszLibName, LPCSTR pszObjectName,
                       REFCLSID riidObject, DWORD dwMiscDocObj,
	                   BOOL bPrint, LPCSTR szExt, LPCSTR szDescription);

//=--------------------------------------------------------------------------=
// Debugging macros
//=--------------------------------------------------------------------------=
// handy-dandy TRACE macro is useful for figuring out how docobj containers
// are calling our interface methods 
//
#ifdef DEBUG
    #define TRACE(szMsg)    OutputDebugString(szMsg)
#else
    #define TRACE(szMsg)
#endif

#endif __MKTYPLIB__

#endif __CDOCOBJ_H_

