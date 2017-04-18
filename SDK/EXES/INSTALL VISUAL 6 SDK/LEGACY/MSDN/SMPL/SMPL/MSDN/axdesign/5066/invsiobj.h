//=--------------------------------------------------------------------------=
// InvisibleInstanceObj.H
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// the InvisibleInstance object.
//
//
#ifndef _INVISIBLEINSTANCE_H_

#include "AutoObj.H"
#include "InvsInstInterfaces.H"
#include "ctrlobj.h"

class CInvisibleInstance :	public IInvisibleInstance,
							public CAutomationObjectWEvents,
							public ISupportErrorInfo,
							public IOleObject,
							public IPersistStreamInit {	                   
                         // public IPersistStorage  {

  public:
    // IUnknown methods
    //
    DECLARE_STANDARD_UNKNOWN();

    // IDispatch methods
    //
    DECLARE_STANDARD_DISPATCH();

    //  ISupportErrorInfo methods
    //
    DECLARE_STANDARD_SUPPORTERRORINFO();

    CInvisibleInstance(IUnknown *);
    virtual ~CInvisibleInstance();

    // IPersist methods.  used by IPersistStream and IPersistStorage
    //
    STDMETHOD(GetClassID)(LPCLSID lpClassID);
                               
    // IPersistStreamInit methods
    //
    
    STDMETHOD(IsDirty)(void);
    STDMETHOD(Load)(LPSTREAM pStm);
    STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty);
    STDMETHOD(GetSizeMax)(ULARGE_INTEGER * pcbSize);
    STDMETHOD(InitNew)();

    // IPersistStorage
    //
    //STDMETHOD(InitNew)(IStorage  *pStg);
    //STDMETHOD(Load)(IStorage  *pStg);
    //STDMETHOD(Save)(IStorage  *pStgSave, BOOL fSameAsLoad);
    //STDMETHOD(SaveCompleted)(IStorage  *pStgNew);
    //STDMETHOD(HandsOffStorage)(void);
    //STDMETHOD(IsDirty)(void);

    // IInvisibleInstance methods
    //
    STDMETHOD(get_MyString)(BSTR * pbstrMyString);
    STDMETHOD(put_MyString)(BSTR bstrMyString);

	  // IOleObject methods
    //
    STDMETHOD(SetClientSite)(IOleClientSite  *pClientSite);
    STDMETHOD(GetClientSite)(IOleClientSite  * *ppClientSite);
    STDMETHOD(SetHostNames)(LPCOLESTR szContainerApp, LPCOLESTR szContainerObj);
    STDMETHOD(Close)(DWORD dwSaveOption);
    STDMETHOD(SetMoniker)(DWORD dwWhichMoniker, IMoniker  *pmk);
    STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker  * *ppmk);
    STDMETHOD(InitFromData)(IDataObject  *pDataObject, BOOL fCreation, DWORD dwReserved);
    STDMETHOD(GetClipboardData)(DWORD dwReserved, IDataObject  * *ppDataObject);
    STDMETHOD(DoVerb)(LONG iVerb, LPMSG lpmsg, IOleClientSite  *pActiveSite, LONG lindex,
                                     HWND hwndParent, LPCRECT lprcPosRect);
    STDMETHOD(EnumVerbs)(IEnumOLEVERB  * *ppEnumOleVerb);
    STDMETHOD(Update)(void);
    STDMETHOD(IsUpToDate)(void);
    STDMETHOD(GetUserClassID)(CLSID  *pClsid);
    STDMETHOD(GetUserType)(DWORD dwFormOfType, LPOLESTR  *pszUserType);
    STDMETHOD(SetExtent)(DWORD dwDrawAspect,SIZEL  *psizel);
    STDMETHOD(GetExtent)(DWORD dwDrawAspect, SIZEL  *psizel);
    STDMETHOD(Advise)(IAdviseSink  *pAdvSink, DWORD  *pdwConnection);
    STDMETHOD(Unadvise)(DWORD dwConnection);
    STDMETHOD(EnumAdvise)(IEnumSTATDATA  * *ppenumAdvise);
    STDMETHOD(GetMiscStatus)(DWORD dwAspect, DWORD  *pdwStatus);
    STDMETHOD(SetColorScheme)(LOGPALETTE  *pLogpal);


    // creation method
    //
    static IUnknown *Create(IUnknown *);

	//  for siting r.e.7/11
	IOleClientSite *m_pClientSite;

  protected:
    virtual HRESULT InternalQueryInterface(REFIID riid, void **ppvObjOut);

  private:
    // member variables that nobody else gets to look at.
    //
    BSTR m_bstrMyString;

};

// TODO: modify anything appropriate in this structure, such as the helpfile
//       name, the version number, etc.
//
DEFINE_AUTOMATIONOBJECTWEVENTS(InvisibleInstance,
    &CLSID_InvisibleInstance,
    "InvisibleInstance",
    CInvisibleInstance::Create,
    1,
    &IID_IInvisibleInstance,
	&DIID_DInvisibleDesignerEvents,
    "InvisibleInstance.Hlp");


#define _INVISIBLEINSTANCE_H_
#endif // _INVISIBLEINSTANCE_H_
