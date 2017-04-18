/*
 * TENANT.CPP
 * Patron Chapter 12
 *
 * Implementation of the CTentant class which holds information
 * for a single object on a page.  It maintains position, references
 * to data, and a storage.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * CTenant::CTenant
 * CTenant::~CTenant
 *
 * Constructor Parameters:
 *  dwID            DWORD identifier for this page.
 *  hWnd            HWND of the pages window.
 *  pPG             PCPages to the parent structure.
 */

CTenant::CTenant(DWORD dwID, HWND hWnd, PCPages pPG)
    {
    m_hWnd=hWnd;
    m_dwID=dwID;

    m_fInitialized=0;
    m_pIStorage=NULL;
    m_cOpens=0;

    m_pObj=NULL;
    m_pPG =pPG;
    m_clsID=CLSID_NULL;
    m_fSetExtent=FALSE;

    return;
    }


CTenant::~CTenant(void)
    {
    if (NULL!=m_pObj)
        {
        //We know we only hold one reference from Create or Load
        m_pObj->Release();
        m_pObj=NULL;
        }

    return;
    }



/*
 * CTenant::GetID
 *
 * Return Value:
 *  DWORD           dwID field in this tenant.
 */

DWORD CTenant::GetID(void)
    {
    return m_dwID;
    }



/*
 * CTenant::GetStorageName
 *
 * Parameters:
 *  pszName         LPOLESTR to a buffer in which to store the storage
 *                  name for this tenant.
 *
 * Return Value:
 *  UINT            Number of characters stored.
 */

UINT CTenant::GetStorageName(LPOLESTR pszName)
    {
   #ifdef WIN32ANSI
    char        szTemp[32];
    UINT        cch;

    cch=wsprintf(szTemp, "Tenant %lu", m_dwID);
    MultiByteToWideChar(CP_ACP, 0, szTemp, -1, pszName, 32);
    return cch;
   #else
    return wsprintf(pszName, TEXT("Tenant %lu"), m_dwID);
   #endif
    }





/*
 * CTenant::Create
 *
 * Purpose:
 *  Creates a new tenant of the given CLSID, which can be either a
 *  static bitmap or metafile now (Chapter 12) and which may
 *  eventually be any compound document object.
 *
 * Parameters:
 *  tType           TENANTTYPE to create, either a static metafile,
 *                  bitmap, or some kind of compound document object
 *                  This determines which OleCreate* call we use.
 *  pvType          LPVOID providing the relevant pointer from which
 *                  to create the tenant, depending on iType.
 *  pFE             LPFORMATETC specifying the type of renderings
 *                  to use.
 *  pptl            PPOINTL in which we store offset coordinates.
 *  pszl            LPSIZEL where this object should store its
 *                  lometric extents.
 *  pIStorage       LPSTORAGE of the page we live in.  We have to
 *                  create another storage in this for the tenant.
 *  ppo             PPATRONOBJECT containing placement data.
 *  dwData          DWORD with extra data, sensitive to iType.
 *
 * Return Value:
 *  UINT            A CREATE_* value depending on what we
 *                  actually do.
 */

UINT CTenant::Create(TENANTTYPE tType, LPVOID pvType
    , LPFORMATETC pFE, PPOINTL pptl, LPSIZEL pszl
    , LPSTORAGE pIStorage, PPATRONOBJECT ppo, DWORD dwData)
    {
    HRESULT         hr;
    LPUNKNOWN       pObj;
    LPVIEWOBJECT2   pIViewObject2;
    LPOLEOBJECT     pIOleObject;
    UINT            uRet=CREATE_GRAPHICONLY;

    if (NULL==pvType || NULL==pIStorage)
        return CREATE_FAILED;

    //Fail if this is called for an already living tenant.
    if (m_fInitialized)
        return CREATE_FAILED;

    m_fInitialized=TRUE;

    //Create a new storage for this tenant.
    if (!Open(pIStorage))
        return CREATE_FAILED;

    /*
     * Get the placement info if it's here.  We either have a non-
     * NULL PPATRONOBJECT in ppo or we have to use default
     * placement and retrieve the size from the object itself.
     */
    pszl->cx=0;
    pszl->cy=0;

    if (NULL!=ppo)
        {
        *pFE=ppo->fe;
        *pptl=ppo->ptl;
        *pszl=ppo->szl;     //Could be 0,0 , so we ask object

        uRet=CREATE_PLACEDOBJECT;
        }

    hr=ResultFromScode(E_FAIL);

    //Now create an object based specifically for the type.
    switch (tType)
        {
        case TENANTTYPE_NULL:
            break;

        case TENANTTYPE_STATIC:
            /*
             * We could use OleCreateStaticFromData here which does
             * pretty much what we're doing below.  However, it does
             * not allow us to control whether we paste a bitmap or
             * a metafile--it uses metafile first, bitmap second.
             * For this reason we'll use code developed in Chapter
             * 11's FreeLoader to affect the paste.
             */
            hr=CreateStatic((LPDATAOBJECT)pvType, pFE, &pObj);
            break;

        default:
            break;
        }

    //If creation didn't work, get rid of the element Open created.
    if (FAILED(hr))
        {
        Destroy(pIStorage);
        return CREATE_FAILED;
        }

    //Otherwise, store the object pointer and initialize the tenant
    m_pObj=pObj;
    m_fe=*pFE;
    m_fe.ptd=NULL;
    m_dwState=TENANTSTATE_DEFAULT;

    //If we also saw PatronObjects on the clipboard, we have size

    if (0==pszl->cx && 0==pszl->cy)
        {
        SIZEL   szl;

        //Try to get the real size of the object, default to 2"*2"
        SETSIZEL((*pszl), 2*LOMETRIC_PER_INCH, 2*LOMETRIC_PER_INCH);

        //Try IViewObject2 first, then IOleObject as a backup.
        hr=pObj->QueryInterface(IID_IViewObject2
            , (PPVOID)&pIViewObject2);

        if (SUCCEEDED(hr))
            {
            pIViewObject2->GetExtent(m_fe.dwAspect, -1, NULL, &szl);
            pIViewObject2->Release();
            }
        else
            {
            hr=pObj->QueryInterface(IID_IOleObject
                , (PPVOID)&pIOleObject);

            if (SUCCEEDED(hr))
                {
                pIOleObject->GetExtent(m_fe.dwAspect, &szl);
                pIOleObject->Release();
                }
            }

        if (SUCCEEDED(hr))
            {
            //Convert HIMETRIC to our LOMETRIC mapping
            SETSIZEL((*pszl), szl.cx/10, szl.cy/10);
            }
        }

    return uRet;
    }






/*
 * CTenant::Load
 *
 * Purpose:
 *  Recreates the object living in this tenant in place of calling
 *  FCreate.  This is used in loading as opposed to new creation.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE of the page we live in.
 *  pti             PTENTANTINFO containing persistent information.
 *                  The ID value in this structure is ignored.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CTenant::Load(LPSTORAGE pIStorage, PTENANTINFO pti)
    {
    HRESULT         hr;
    LPUNKNOWN       pObj;

    if (NULL==pIStorage || NULL==pti)
        return FALSE;

    //Fail if this is called for an already living tenant.
    if (m_fInitialized)
        return FALSE;

    m_fInitialized=TRUE;

    //Open the storage for this tenant.
    if (!Open(pIStorage))
        return FALSE;

    hr=OleLoad(m_pIStorage, IID_IUnknown, NULL, (PPVOID)&pObj);

    if (FAILED(hr))
        {
        Destroy(pIStorage);
        return FALSE;
        }

    //Otherwise, store the object pointer and initialize the tenant
    m_pObj=pObj;
    m_fe=pti->fe;
    m_fe.ptd=NULL;
    m_fSetExtent=pti->fSetExtent;
    m_dwState=TENANTSTATE_DEFAULT;

    RectSet(&pti->rcl, FALSE);
    return TRUE;
    }




/*
 * CTenant::GetInfo
 *
 * Purpose:
 *  Retrieved a TENANTINFO structure for this tenant.
 *
 * Parameters:
 *  pti             PTENANTINFO structure to fill
 *
 * Return Value:
 *  None
 */

void CTenant::GetInfo(PTENANTINFO pti)
    {
    if (NULL!=pti)
        {
        pti->dwID=m_dwID;
        pti->rcl=m_rcl;
        pti->fe=m_fe;
        pti->fSetExtent=m_fSetExtent;
        }

    return;
    }





/*
 * CTenant::Open
 *
 * Purpose:
 *  Retrieves the IStorage associated with this tenant.  The
 *  IStorage is owned by the tenant and thus the tenant always
 *  holds a reference count.
 *
 *  If the storage is already open for this tenant, then this
 *  function will AddRef it; therefore the caller must always
 *  match an Open with a Close.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE above this tenant (which has its
 *                  own storage).
 *
 * Return Value:
 *  BOOL            TRUE if opening succeeds, FALSE otherwise.
 */

BOOL CTenant::Open(LPSTORAGE pIStorage)
    {
    HRESULT     hr=NOERROR;
    DWORD       dwMode=STGM_TRANSACTED | STGM_READWRITE
                    | STGM_SHARE_EXCLUSIVE;
    OLECHAR     szTemp[32];

    if (NULL==m_pIStorage)
        {
        if (NULL==pIStorage)
            return FALSE;

        /*
         * Attempt to open the storage under this ID.  If there is
         * none, then create it.  In either case we end up with an
         * IStorage that we either save in pPage or release.
         */

        GetStorageName(szTemp);
        hr=pIStorage->OpenStorage(szTemp, NULL, dwMode, NULL, 0
            , &m_pIStorage);

        if (FAILED(hr))
            {
            hr=pIStorage->CreateStorage(szTemp, dwMode, 0, 0
                , &m_pIStorage);
            }
        }
    else
        m_pIStorage->AddRef();

    if (FAILED(hr))
        return FALSE;

    m_cOpens++;
    return TRUE;
    }




/*
 * CTenant::Close
 *
 * Purpose:
 *  Possibly commits the storage, then releases it reversing the
 *  reference count from Open.  If the reference on the storage
 *  goes to zero, the storage is forgotten.  However, the object we
 *  contain is still held and as long as it's active the storage
 *  remains alive.
 *
 * Parameters:
 *  fCommit         BOOL indicating if we're to commit.
 *
 * Return Value:
 *  None
 */

void CTenant::Close(BOOL fCommit)
    {
    if (fCommit)
        Update();

    if (NULL!=m_pIStorage)
        {
        m_pIStorage->Release();

        /*
         * We can't use a zero reference count to know when to NULL
         * this since other things might have AddRef'd the storage.
         */
        if (0==--m_cOpens)
            m_pIStorage=NULL;
        }

    return;
    }




/*
 * CTenant::Update
 *
 * Purpose:
 *  Forces a common on the page if it's open.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the object is open, FALSE otherwise.
 */

BOOL CTenant::Update(void)
    {
    LPPERSISTSTORAGE    pIPS;

    if (NULL!=m_pIStorage)
        {
        /*
         * We need to OleSave again because we might have changed
         * the size or position of this tenant.  We also need to
         * save the rectangle on the page, since that's not known
         * to OLE.
         */
        m_pObj->QueryInterface(IID_IPersistStorage, (PPVOID)&pIPS);

        if (FAILED(OleSave(pIPS, m_pIStorage, TRUE)))
            {
            //This is essentially what OleSave does.
            WriteClassStg(m_pIStorage, m_clsID);
            pIPS->Save(m_pIStorage, TRUE);
            }

        pIPS->SaveCompleted(NULL);
        pIPS->Release();

        m_pIStorage->Commit(STGC_ONLYIFCURRENT);
        }

    return FALSE;
    }





/*
 * CTenant::Destroy
 *
 * Purpose:
 *  Removes this page from the given storage.  The caller should
 *  eventually delete this CTenant object to free the object herein.
 *  Nothing is committed when being destroyed.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE contianing this page on which to call
 *                  DestroyElement
 *
 * Return Value:
 *  None
 */

void CTenant::Destroy(LPSTORAGE pIStorage)
    {
    OLECHAR     szTemp[32];

    if (NULL!=pIStorage)
        {
        if (NULL!=m_pIStorage)
            {
            //Remove all reference/open counts on this storage.
            while (0!=m_cOpens)
                {
                m_pIStorage->Release();
                m_cOpens--;
                }
            }

        GetStorageName(szTemp);
        pIStorage->DestroyElement(szTemp);

        m_pIStorage=NULL;
        }

    //m_pObj is released in destructor.
    return;
    }




/*
 * CTenant::Select
 *
 * Purpose:
 *  Selects or deselects the tenant.
 *
 * Parameters:
 *  fSelect         BOOL indicating the new state of the tenant.
 *
 * Return Value:
 *  None
 */

void CTenant::Select(BOOL fSelect)
    {
    BOOL        fWasSelected;
    DWORD       dwState;
    RECT        rc;
    HDC         hDC;

    fWasSelected=(BOOL)(TENANTSTATE_SELECTED & m_dwState);

    //Nothing to do when there's no change.
    if (fWasSelected==fSelect)
        return;

    dwState=m_dwState & ~TENANTSTATE_SELECTED;
    m_dwState=dwState | ((fSelect) ? TENANTSTATE_SELECTED : 0);

    /*
     * Draw sizing handles to show the selection state.  We convert
     * things to MM_TEXT since that's what this function expects.
     */

    RECTFROMRECTL(rc, m_rcl);
    RectConvertMappings(&rc, NULL, TRUE);
    OffsetRect(&rc, -(int)m_pPG->m_xPos, -(int)m_pPG->m_yPos);

    hDC=GetDC(m_hWnd);

    UIDrawHandles(&rc, hDC, UI_HANDLES_INSIDE
        | UI_HANDLES_NOBORDER | UI_HANDLES_USEINVERSE
        , CXYHANDLE, !fWasSelected);

    ReleaseDC(m_hWnd, hDC);

    //Changing the selected object dirties the page
    if (fSelect)
        m_pPG->m_fDirty=TRUE;
    return;
    }







/*
 * CTenant::Activate
 *
 * Purpose:
 *  Activates a verb on the object living in the tenant.  Does
 *  nothing for static objects.
 *
 * Parameters:
 *  iVerb           LONG of the verb to execute.
 *
 * Return Value:
 *  BOOL            TRUE if the object changed due to this verb
 *                  execution.
 */

BOOL CTenant::Activate(LONG iVerb)
    {
    MessageBeep(0); //Nothing doing for now.
    return FALSE;
    }






/*
 * CTenant::Draw
 *
 * Purpose:
 *  Draws the tenant in its rectangle on the given hDC.  We assume
 *  the DC is already set up for the mapping mode in which our
 *  rectangle is expressed, since the Page we're in tells us both
 *  the rect and the hDC.
 *
 * Parameters:
 *  hDC             HDC in which to draw.  Could be a metafile,
 *                  memory DC, screen, or printer.
 *  ptd             DVTARGETDEVICE * describing the device.
 *  hIC             HDC holding an information context (printing).
 *  xOff, yOff      int offsets for the page in lometric
 *  fNoColor        BOOL indicating if we should do B & W
 *  fPrinter        BOOL indicating if we should render for a
 *                  printer.
 *
 * Return Value:
 *  None
 */

void CTenant::Draw(HDC hDC, DVTARGETDEVICE *ptd, HDC hIC
    , int xOff, int yOff, BOOL fNoColor, BOOL fPrinter)
    {
    HRESULT         hr;
    RECT            rc;
    RECTL           rcl;
    UINT            uMM;
    LPVIEWOBJECT2   pIViewObject2;

    hr=m_pObj->QueryInterface(IID_IViewObject2
        , (PPVOID)&pIViewObject2);

    if (FAILED(hr))
        return;

    RECTFROMRECTL(rc, m_rcl);
    OffsetRect(&rc, -xOff, -yOff);
    RECTLFROMRECT(rcl, rc);

    //We have to use Draw since we have a target device and IC.
    hr=pIViewObject2->Draw(m_fe.dwAspect, -1, NULL, ptd, hIC, hDC
        , &rcl, NULL, NULL, 0);
    pIViewObject2->Release();

    /*
     * If Draw failed, then perhaps it couldn't work for the device,
     * so try good old OleDraw as a last resort.  The code will
     * generally be OLE_E_BLANK.
     */
    if (FAILED(hr))
        OleDraw(m_pObj, m_fe.dwAspect, hDC, &rc);

    if (!fPrinter && TENANTSTATE_SELECTED & m_dwState)
        {
        /*
         * Draw sizing handles to show the selection state.  We
         * convert things to MM_TEXT since that's what this
         * function expects.
         */
        RectConvertMappings(&rc, NULL, TRUE);
        uMM=SetMapMode(hDC, MM_TEXT);

        UIDrawHandles(&rc, hDC, UI_HANDLES_INSIDE
            | UI_HANDLES_NOBORDER| UI_HANDLES_USEINVERSE
            , CXYHANDLE, TRUE);

        uMM=SetMapMode(hDC, uMM);
        }

    return;
    }





/*
 * CTenant::Repaint
 * CTenant::Invalidate
 *
 * Purpose:
 *  Repaints the tenant where it lies or invalidates its area
 *  for later repainting.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CTenant::Repaint(void)
    {
    RECT        rc;
    HDC         hDC;

    hDC=GetDC(m_hWnd);
    SetRect(&rc, m_pPG->m_xPos, m_pPG->m_yPos, 0, 0);
    RectConvertMappings(&rc, NULL, FALSE);

    SetMapMode(hDC, MM_LOMETRIC);
    Draw(hDC, NULL, NULL, rc.left, rc.top, FALSE, FALSE);

    ReleaseDC(m_hWnd, hDC);
    return;
    }


void CTenant::Invalidate(void)
    {
    RECTL       rcl;
    RECT        rc;

    RectGet(&rcl, TRUE);
    RECTFROMRECTL(rc, rcl);

    OffsetRect(&rc, -(int)m_pPG->m_xPos, -(int)m_pPG->m_yPos);
    InvalidateRect(m_hWnd, &rc, FALSE);

    return;
    }






/*
 * CTenant::ObjectGet
 *
 * Purpose:
 *  Retrieves the LPUNKNOWN of the object in use by this tenant
 *
 * Parameters:
 *  ppUnk           LPUNKNOWN * in which to return the object
 *                  pointer.
 *
 * Return Value:
 *  None
 */

void CTenant::ObjectGet(LPUNKNOWN *ppUnk)
    {
    if (NULL!=ppUnk)
        {
        *ppUnk=m_pObj;
        m_pObj->AddRef();
        }

    return;
    }





/*
 * CTenant::FormatEtcGet
 *
 * Purpose:
 *  Retrieves the FORMATETC in use by this tenant
 *
 * Parameters:
 *  pFE             LPFORMATETC in which to store the information.
 *  fPresentation   BOOL indicating if we want the real format or
 *                  that of the presentation.
 *
 * Return Value:
 *  None
 */

void CTenant::FormatEtcGet(LPFORMATETC pFE, BOOL fPresentation)
    {
    if (NULL!=pFE)
        *pFE=m_fe;

    return;
    }





/*
 * CTenant::SizeGet
 * CTenant::SizeSet
 * CTenant::RectGet
 * CTenant::RectSet
 *
 * Purpose:
 *  Returns or sets the size/position of the object contained here.
 *
 * Parameters:
 *  pszl/prcl       LPSIZEL (Size) or LPRECTL (Rect) with the
 *                  extents of interest.  In Get situations,
 *                  this will receive the extents; in Set it
 *                  contains the extents.
 *  fDevice         BOOL indicating that pszl/prcl is expressed
 *                  in device units.  Otherwise it's LOMETRIC.
 *
 * Return Value:
 *  None
 */

void CTenant::SizeGet(LPSIZEL pszl, BOOL fDevice)
    {
    if (!fDevice)
        {
        pszl->cx=m_rcl.right-m_rcl.left;
        pszl->cy=m_rcl.bottom-m_rcl.top;
        }
    else
        {
        RECT        rc;

        SetRect(&rc, (int)(m_rcl.right-m_rcl.left)
            , (int)(m_rcl.bottom-m_rcl.top), 0, 0);

        RectConvertMappings(&rc, NULL, TRUE);

        pszl->cx=(long)rc.left;
        pszl->cy=(long)rc.top;
        }

    return;
    }


void CTenant::SizeSet(LPSIZEL pszl, BOOL fDevice)
    {
    SIZEL           szl;

    if (!fDevice)
        {
        szl=*pszl;
        m_rcl.right =pszl->cx+m_rcl.left;
        m_rcl.bottom=pszl->cy+m_rcl.top;
        }
    else
        {
        RECT        rc;

        SetRect(&rc, (int)pszl->cx, (int)pszl->cy, 0, 0);
        RectConvertMappings(&rc, NULL, FALSE);

        m_rcl.right =(long)rc.left+m_rcl.left;
        m_rcl.bottom=(long)rc.top+m_rcl.top;

        SETSIZEL(szl, (long)rc.left, (long)rc.top);
        }


    //Tell OLE that this object was resized.
    if (NULL!=m_pObj)
        {
        HRESULT     hr;
        LPOLEOBJECT pIOleObject;

        hr=m_pObj->QueryInterface(IID_IOleObject
            , (PPVOID)&pIOleObject);

        if (SUCCEEDED(hr))
            {
            //Convert our LOMETRIC into HIMETRIC by *=10
            szl.cx*=10;
            szl.cy*=-10;    //Our size is stored negative.

            pIOleObject->SetExtent(m_fe.dwAspect, &szl);
            pIOleObject->Release();
            }
        }

    return;
    }


void CTenant::RectGet(LPRECTL prcl, BOOL fDevice)
    {
    if (!fDevice)
        *prcl=m_rcl;
    else
        {
        RECT        rc;

        RECTFROMRECTL(rc, m_rcl);
        RectConvertMappings(&rc, NULL, TRUE);
        RECTLFROMRECT(*prcl, rc);
        }

    return;
    }


void CTenant::RectSet(LPRECTL prcl, BOOL fDevice)
    {
    SIZEL   szl;
    LONG    cx, cy;

    cx=m_rcl.right-m_rcl.left;
    cy=m_rcl.bottom-m_rcl.top;

    if (!fDevice)
        m_rcl=*prcl;
    else
        {
        RECT        rc;

        RECTFROMRECTL(rc, *prcl);
        RectConvertMappings(&rc, NULL, FALSE);
        RECTLFROMRECT(m_rcl, rc);
        }

    //Tell ourselves that the size changed, if it did.
    if ((m_rcl.right-m_rcl.left)!=cx || (m_rcl.bottom-m_rcl.top)!=cy)
        {
        SETSIZEL(szl, m_rcl.right-m_rcl.left, m_rcl.bottom-m_rcl.top);
        SizeSet(&szl, FALSE);
        }

    return;
    }







/*
 * CTenant::CreateStatic
 * (Protected)
 *
 * Purpose:
 *  Creates a new static bitmap or metafile object for this tenant
 *  using a freeloading method allowing us to specify exactly which
 *  type of data we want to paste since OleCreateStaticFromData
 *  doesn't.
 *
 * Parameters:
 *  pIDataObject    LPDATAOBJECT from which to paste.
 *  pFE             LPFORMATETC describing the format to paste.
 *  ppObj           LPUNKNOWN * into which we store the
 *                  object pointer.
 *
 * Return Value:
 *  HRESULT         NOERROR on success, error code otherwise.
 */

HRESULT CTenant::CreateStatic(LPDATAOBJECT pIDataObject
    , LPFORMATETC pFE, LPUNKNOWN *ppObj)
    {
    HRESULT             hr;
    STGMEDIUM           stm;
    LPUNKNOWN           pIUnknown;
    LPOLECACHE          pIOleCache;
    LPPERSISTSTORAGE    pIPersistStorage;
    CLSID               clsID;

    *ppObj=NULL;

    //Try to get the data desired as specified in pFE->cfFormat
    hr=pIDataObject->GetData(pFE, &stm);

    if (FAILED(hr))
        return hr;

    //Create the object to handle this data.
    if (CF_METAFILEPICT==pFE->cfFormat)
        clsID=CLSID_Picture_Metafile;
    else
        clsID=CLSID_Picture_Dib;

    hr=CreateDataCache(NULL, clsID, IID_IUnknown
        , (PPVOID)&pIUnknown);

    if (FAILED(hr))
        {
        ReleaseStgMedium(&stm);
        return hr;
        }

    m_clsID=clsID;

    //Stuff the data into the object
    pIUnknown->QueryInterface(IID_IPersistStorage
        , (PPVOID)&pIPersistStorage);
    pIPersistStorage->InitNew(m_pIStorage);

    //Now that we have the cache object, shove the data into it.
    pIUnknown->QueryInterface(IID_IOleCache, (PPVOID)&pIOleCache);
    pIOleCache->Cache(pFE, ADVF_PRIMEFIRST, NULL);

    hr=pIOleCache->SetData(pFE, &stm, TRUE);
    pIOleCache->Release();

    //Insure there is a persistent copy on the disk
    WriteClassStg(m_pIStorage, m_clsID);
    pIPersistStorage->Save(m_pIStorage, TRUE);
    pIPersistStorage->SaveCompleted(NULL);
    pIPersistStorage->Release();

    //The cache owns this now.
    ReleaseStgMedium(&stm);

    if (FAILED(hr))
        pIUnknown->Release();
    else
        *ppObj=pIUnknown;

    return hr;
    }
