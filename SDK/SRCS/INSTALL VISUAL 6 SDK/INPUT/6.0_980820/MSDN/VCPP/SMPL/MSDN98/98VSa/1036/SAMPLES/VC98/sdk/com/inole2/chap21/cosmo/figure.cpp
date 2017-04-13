/*
 * FIGURE.CPP
 * Cosmo Chapter 21
 *
 * Implementation of the CFigure object for Cosmo.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "cosmo.h"


/*
 * CFigure::CFigure
 * CFigure::~CFigure
 *
 * Parameters (Constructor):
 *  pfnDestroy      PFNDESTROYED to call when object is destroyed.
 *  pDoc            PCCosmoDoc we're associated with.
 */

CFigure::CFigure(PFNDESTROYED pfnDestroy, PCCosmoDoc pDoc)
    {
    m_cRef=0;
    m_pfnDestroy=pfnDestroy;

    m_pFR=NULL;     //We get this later through FrameSet.
    m_pDoc=pDoc;
    m_pPL=pDoc->m_pPL;

    m_fEmbedded=FALSE;

    //NULL any contained interfaces initially.
    m_pImpIPersistStorage=NULL;
    m_pIStorage=NULL;
    m_pIStream=NULL;
    m_pImpIDataObject=NULL;
    m_pIDataAdviseHolder=NULL;
    m_pImpIOleObject=NULL;
    m_pIOleAdviseHolder=NULL;
    m_pIOleClientSite=NULL;

    m_clsID=CLSID_CosmoFigure;
    m_cf=pDoc->m_cf;

    //These are for IDataObject::QueryGetData
    m_cfeGet=CFORMATETCGET;

    SETDefFormatEtc(m_rgfeGet[0], pDoc->m_cf, TYMED_HGLOBAL);
    SETDefFormatEtc(m_rgfeGet[1], pDoc->m_cfEmbedSource
        , TYMED_ISTORAGE);
    SETDefFormatEtc(m_rgfeGet[2], pDoc->m_cfObjectDescriptor
        , TYMED_HGLOBAL);
    SETDefFormatEtc(m_rgfeGet[3], CF_METAFILEPICT, TYMED_MFPICT);
    SETDefFormatEtc(m_rgfeGet[4], CF_BITMAP, TYMED_GDI);

    m_pST=NULL;

    //CHAPTER21MOD
    m_pImpIPersistFile=NULL;

    //We live in the document's lifetime, so no need to AddRef here.
    m_pMoniker=m_pDoc->m_pMoniker;
    m_dwRegROT=0L;
    //End CHAPTER21MOD

    return;
    }


CFigure::~CFigure(void)
    {
    //CHAPTER21MOD
    //Make sure no one thinks we're still running
    INOLE_RevokeAsRunning(&m_dwRegROT);
    //End CHAPTER21MOD

    ReleaseInterface(m_pIOleClientSite);
    ReleaseInterface(m_pIDataAdviseHolder);
    ReleaseInterface(m_pIOleAdviseHolder);
    ReleaseInterface(m_pIStorage)
    ReleaseInterface(m_pIStream)

    //CHAPTER21MOD
    DeleteInterfaceImp(m_pImpIPersistFile);
    //End CHAPTER21MOD
    DeleteInterfaceImp(m_pImpIOleObject)
    DeleteInterfaceImp(m_pImpIDataObject)
    DeleteInterfaceImp(m_pImpIPersistStorage);

    //Free strings.
    if (NULL!=m_pST)
        delete m_pST;

    return;
    }





/*
 * CFigure::QueryInterface
 * CFigure::AddRef
 * CFigure::Release
 *
 * Purpose:
 *  IUnknown members for CFigure object.
 */

STDMETHODIMP CFigure::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid)
        *ppv=this;

    if (IID_IPersist==riid || IID_IPersistStorage==riid)
        *ppv=m_pImpIPersistStorage;

    if (IID_IDataObject==riid)
        *ppv=m_pImpIDataObject;

    if (IID_IOleObject==riid)
        *ppv=m_pImpIOleObject;

    //CHAPTER21MOD
    if (IID_IPersistFile==riid)
        *ppv=m_pImpIPersistFile;
    //End CHAPTER21MOD

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CFigure::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CFigure::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    if (NULL!=m_pfnDestroy)
        (*m_pfnDestroy)();

    //Document deletes us
    return 0;
    }






/*
 * CFigure::Init
 *
 * Purpose:
 *  Performs any initialization of a CFigure that's prone to failure
 *  that we also use internally before exposing the object outside.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful,
 *                  FALSE otherwise.
 */

BOOL CFigure::Init(void)
    {
    m_pST=new CStringTable(m_pDoc->m_hInst);

    if (NULL==m_pST)
        return FALSE;

    if (!m_pST->Init(IDS_FIGUREMIN, IDS_FIGUREMAX))
        return FALSE;

    //Allocate contained interfaces.
    m_pImpIPersistStorage=new CImpIPersistStorage(this, this);

    if (NULL==m_pImpIPersistStorage)
        return FALSE;

    m_pImpIDataObject=new CImpIDataObject(this, this);

    if (NULL==m_pImpIDataObject)
        return FALSE;

    m_pImpIOleObject=new CImpIOleObject(this, this);

    if (NULL==m_pImpIOleObject)
        return FALSE;

    //CHAPTER21MOD
    m_pImpIPersistFile=new CImpIPersistFile(this, this);

    if (NULL==m_pImpIPersistFile)
        return FALSE;
    //End CHAPTER21MOD

    return TRUE;
    }



/*
 * CFigure::FrameSet
 *
 * Purpose:
 *  Provides the compound document object with access to the frame
 *  of this application for UI purposes.
 *
 * Parameters:
 *  pFR             PCCosmoFrame of the frame window.
 *
 * Return Value:
 *  None
 */

void CFigure::FrameSet(PCCosmoFrame pFR)
    {
    m_pFR=pFR;
    return;
    }




/*
 * CFigure::FIsDirty
 *
 * Purpose:
 *  Checks if the document is dirty.  This can be called from
 *  IPersistStorage::IsDirty which doesn't have access to CCosmoDoc.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if dirty, FALSE if clean.
 */

BOOL CFigure::FIsDirty(void)
    {
    return m_pDoc->m_fDirty;
    }




/*
 * CFigure::FIsEmbedded
 *
 * Purpose:
 *  Answers if the object is embedded or not.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the object is embedded, FALSE otherwise.
 */

BOOL CFigure::FIsEmbedded(void)
    {
    return m_fEmbedded;
    }




/*
 * CFigure::SendAdvise
 *
 * Purpose:
 *  Calls the appropriate IOleClientSite or IAdviseSink member
 *  function for various events such as closure, saving, etc.
 *
 * Parameters:
 *  uCode           UINT OBJECTCODE_* identifying the notification.
 *
 * Return Value:
 *  None
 */

void CFigure::SendAdvise(UINT uCode)
    {
    switch (uCode)
        {
        case OBJECTCODE_SAVED:
            if (NULL!=m_pIOleAdviseHolder)
                m_pIOleAdviseHolder->SendOnSave();

			break;

        case OBJECTCODE_CLOSED:
            if (NULL!=m_pIOleAdviseHolder)
                m_pIOleAdviseHolder->SendOnClose();

			break;

        case OBJECTCODE_RENAMED:
            //CHAPTER21MOD
            m_pMoniker=m_pDoc->m_pMoniker;  //For IOleObject::GetMoniker
            m_dwRegROT=m_pDoc->m_dwRegROT;

            if (NULL!=m_pIOleAdviseHolder)
                m_pIOleAdviseHolder->SendOnRename(m_pMoniker);
            //End CHAPTER21MOD
            break;

        case OBJECTCODE_SAVEOBJECT:
            if (FIsDirty() && NULL!=m_pIOleClientSite)
                m_pIOleClientSite->SaveObject();

            break;

        case OBJECTCODE_DATACHANGED:
            //No flags are necessary here.
            if (NULL!=m_pIDataAdviseHolder)
                {
                m_pIDataAdviseHolder->SendOnDataChange
                    (m_pImpIDataObject, 0, 0);
                }

            //CHAPTER21MOD
            //Tell the running object table of the change
            if (0!=m_dwRegROT)
                INOLE_NoteChangeTime(m_dwRegROT, NULL, NULL);
            //End CHAPTER21MOD

            break;

        case OBJECTCODE_SHOWWINDOW:
            if (NULL!=m_pIOleClientSite)
                m_pIOleClientSite->OnShowWindow(TRUE);

            break;

        case OBJECTCODE_HIDEWINDOW:
            if (NULL!=m_pIOleClientSite)
                m_pIOleClientSite->OnShowWindow(FALSE);

            break;

        case OBJECTCODE_SHOWOBJECT:
            if (NULL!=m_pIOleClientSite)
                m_pIOleClientSite->ShowObject();

            break;
        }

    return;
    }
