/*
 * IPERSTOR.CPP
 * Cosmo Handler Chapter 19
 *
 * Implementation of the IPersistStorage interface that we expose on
 * the Figure object.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "hcosmo.h"


/*
 * CImpIPersistStorage:CImpIPersistStorage
 * CImpIPersistStorage::~CImpIPersistStorage
 *
 * Constructor Parameters:
 *  pObj            PCFigure pointing to the object we live in.
 *  pUnkOuter       LPUNKNOWN of the controlling unknown.
 */

CImpIPersistStorage::CImpIPersistStorage(PCFigure pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    m_psState=PSSTATE_UNINIT;

    m_fConvert=FALSE;
    return;
    }


CImpIPersistStorage::~CImpIPersistStorage(void)
    {
    return;
    }




/*
 * CImpIPersistStorage::QueryInterface
 * CImpIPersistStorage::AddRef
 * CImpIPersistStorage::Release
 */

STDMETHODIMP CImpIPersistStorage::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIPersistStorage::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIPersistStorage::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }





/*
 * CImpIPersistStorage::GetClassID
 *
 * Purpose:
 *  Returns the CLSID of the object represented by this interface.
 */

STDMETHODIMP CImpIPersistStorage::GetClassID(LPCLSID pClsID)
    {
    if (PSSTATE_UNINIT==m_psState)
        return ResultFromScode(E_UNEXPECTED);

    *pClsID=m_pObj->m_clsID;
    return NOERROR;
    }




/*
 * CImpIPersistStorage::IsDirty
 *
 * Purpose:
 *  Tells the caller if we have made changes to this object since
 *  it was loaded or initialized new.
 */

STDMETHODIMP CImpIPersistStorage::IsDirty(void)
    {
    if (PSSTATE_UNINIT==m_psState)
        return ResultFromScode(E_UNEXPECTED);

    /*
     * Since we don't edit, we have no idea if this data is dirty.
     * Delegate to the default handler in case it wants to ask the
     * server.
     */
    return m_pObj->m_pDefIPersistStorage->IsDirty();
    }





/*
 * CImpIPersistStorage::InitNew
 *
 * Purpose:
 *  Provides the object with the IStorage they hold on to while
 *  they are running.  Since we don't create data in the handler,
 *  there it nothing to write here.  We only need to initialize
 *  out internal state.  This function is only be called once in
 *  the object's lifetime in lieu of Load.
 */

STDMETHODIMP CImpIPersistStorage::InitNew(LPSTORAGE pIStorage)
    {
    if (PSSTATE_UNINIT!=m_psState)
        return ResultFromScode(E_UNEXPECTED);

    if (NULL==pIStorage)
        return ResultFromScode(E_POINTER);

    //Good time to initilize our data
    m_pObj->m_pl.wVerMaj=VERSIONMAJOR;
    m_pObj->m_pl.wVerMin=VERSIONMINOR;
    m_pObj->m_pl.cPoints=0;
    m_pObj->m_pl.rgbBackground=GetSysColor(COLOR_WINDOW);
    m_pObj->m_pl.rgbLine=GetSysColor(COLOR_WINDOWTEXT);
    m_pObj->m_pl.iLineStyle=PS_SOLID;

    //Make sure these aren't filled with trash.
    memcpy(&m_pObj->m_plContent,   &m_pObj->m_pl, CBPOLYLINEDATA);
    memcpy(&m_pObj->m_plThumbnail, &m_pObj->m_pl, CBPOLYLINEDATA);

    m_pObj->m_pDefIPersistStorage->InitNew(pIStorage);

    /*
     * This is just for state validation in other calls.  As
     * a handler we never actually 'scribble.'
     */
    m_psState=PSSTATE_SCRIBBLE;
    return NOERROR;
    }





/*
 * CImpIPersistStorage::Load
 *
 * Purpose:
 *  Instructs the object to load itself from a previously saved
 *  IStorage that was handled by Save in another object lifetime.
 *  This function will only be called once in the object's lifetime
 *  in lieu of InitNew.
 */

STDMETHODIMP CImpIPersistStorage::Load(LPSTORAGE pIStorage)
    {
    POLYLINEDATA    pl;
    ULONG           cb;
    LPSTREAM        pIStream;
    HRESULT         hr;

    if (PSSTATE_UNINIT!=m_psState)
        return ResultFromScode(E_UNEXPECTED);

    if (NULL==pIStorage)
        return ResultFromScode(E_POINTER);

    //This tells us if we're coming from another class storage.
    m_fConvert=(NOERROR==GetConvertStg(pIStorage));

    //This is the type of storage we're really messing with in Treat As
    ReadClassStg(pIStorage, &m_pObj->m_clsID);

    //Open the CONTENTS stream
    hr=pIStorage->OpenStream(SZSTREAM, 0, STGM_DIRECT | STGM_READ
        | STGM_SHARE_EXCLUSIVE, 0, &pIStream);

    if (FAILED(hr))
        return ResultFromScode(STG_E_READFAULT);

    //Read all the data into the POLYLINEDATA structure.
    hr=pIStream->Read(&pl, CBPOLYLINEDATA, &cb);
    pIStream->Release();

    if (CBPOLYLINEDATA!=cb)
        return ResultFromScode(STG_E_READFAULT);

    //Copy into the actual object now.
    memcpy(&m_pObj->m_pl, &pl, CBPOLYLINEDATA);

    m_pObj->m_pDefIPersistStorage->Load(pIStorage);

    //As with InitNew, this is just for validating other calls
    m_psState=PSSTATE_SCRIBBLE;
    return NOERROR;
    }





/*
 * CImpIPersistStorage::Save
 *
 * Purpose:
 *  Saves the data for this object to an IStorage.
 */

STDMETHODIMP CImpIPersistStorage::Save(LPSTORAGE pIStorage
    , BOOL fSameAsLoad)
    {
    ULONG           cb;
    HRESULT         hr;
    LPSTREAM        pIStream;

    //Have to come here from scribble state.
    if (PSSTATE_SCRIBBLE!=m_psState)
        return ResultFromScode(E_UNEXPECTED);

    //Must have an IStorage if we're not in SameAsLoad
    if (NULL==pIStorage && !fSameAsLoad)
        return ResultFromScode(E_POINTER);

    /*
     * If the server is running, don't do the save ourselves since
     * we'd end up writing the storage twice with possible conflicts.
     */
    if (OleIsRunning(m_pObj->m_pDefIOleObject))
        {
        hr=m_pObj->m_pDefIPersistStorage->Save(pIStorage
            , fSameAsLoad);

        if (SUCCEEDED(hr))
            m_psState=PSSTATE_ZOMBIE;

        return hr;
        }

    /*
     * Since we don't have any data we modify in the handler,
     * we have nothing to do for same-as-load cases.  The only
     * case we have to handle is writing to a new storage.
     */
    if (!fSameAsLoad)
        {
        /*
         * This code facilitates making copies of an object into
         * a new storage during a container Save As.
         */

        hr=pIStorage->CreateStream(SZSTREAM, STGM_DIRECT | STGM_CREATE
            | STGM_WRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &pIStream);

        if (FAILED(hr))
            return hr;

        WriteClassStg(pIStorage, CLSID_CosmoFigure);
        WriteFmtUserTypeStg(pIStorage, m_pObj->m_cf
            , TEXT("Polyline Figure"));

        hr=pIStream->Write(&m_pObj->m_pl, CBPOLYLINEDATA, &cb);
        pIStream->Release();

        if (FAILED(hr) || CBPOLYLINEDATA!=cb)
            return ResultFromScode(STG_E_WRITEFAULT);
        }

    //Clear the convert bit if it was set
    if (m_fConvert)
        {
        WriteFmtUserTypeStg(pIStorage, m_pObj->m_cf
            , TEXT("Polyline Figure"));

        SetConvertStg(pIStorage, FALSE);
        m_fConvert=FALSE;
        }

    m_psState=PSSTATE_ZOMBIE;
    m_pObj->m_pDefIPersistStorage->Save(pIStorage, fSameAsLoad);
    return NOERROR;
    }




/*
 * CImpIPersistStorage::SaveCompleted
 * CImpIPersistStorage::HandsOffStorage
 *
 * Purpose:
 *  Pass throughs with typical management of our pointers.
 */

STDMETHODIMP CImpIPersistStorage::SaveCompleted(LPSTORAGE pIStorage)
    {
    //Must be called in no-scribble or hands-off state
    if (!(PSSTATE_ZOMBIE==m_psState || PSSTATE_HANDSOFF==m_psState))
        return ResultFromScode(E_UNEXPECTED);

    //If we're coming from Hands-Off, we'd better get a storage
    if (NULL==pIStorage && PSSTATE_HANDSOFF==m_psState)
        return ResultFromScode(E_UNEXPECTED);

    /*
     * Since this handler modifies nothing, it saves no pointers
     * which it would have to release here.  Nothing to do.
     */

    m_pObj->m_pDefIPersistStorage->SaveCompleted(pIStorage);
    m_psState=PSSTATE_SCRIBBLE;
    return NOERROR;
    }


STDMETHODIMP CImpIPersistStorage::HandsOffStorage(void)
    {
    if (PSSTATE_UNINIT==m_psState || PSSTATE_HANDSOFF==m_psState)
        return ResultFromScode(E_UNEXPECTED);

    /*
     * Since this handler modifies nothing, it saves no pointers
     * which it would have to release here.  Nothing to do.
     */

    m_pObj->m_pDefIPersistStorage->HandsOffStorage();
    m_psState=PSSTATE_HANDSOFF;
    return NOERROR;
    }
