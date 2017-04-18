/*
 * AUTOFIGS.CPP
 * Cosmo Chapter 14
 *
 * "Figures" collection object for Cosmo's OLE Automation support,
 * derived from CAutoBase.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved.
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  INTERNET>kraigb@microsoft.com
 */


#include "cosmo.h"


/*
 * CAutoFigures::CAutoFigures
 * CAutoFigures::~CAutoFigures
 *
 * Constructor Parameters:
 *  pCL             PCCosmoClient to the client object that we use
 *                  to implement much of this interface.
 */

CAutoFigures::CAutoFigures(PCCosmoClient pCL)
    : CAutoBase(pCL, pCL->m_hInst, IID_ICosmoFigures
    , DIID_DICosmoFigures, NULL)
    {
    return;
    }


CAutoFigures::~CAutoFigures(void)
    {
    return;
    }




/*
 * CAutoFigures::QueryInterface
 * CAutoFigures::AddRef
 * CAutoFigures::Release
 */

STDMETHODIMP CAutoFigures::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_ICosmoFigures==riid)
        *ppv=(IUnknown *)this;

    if (IID_IDispatch==riid || m_diid==riid)
        *ppv=m_pImpIDispatch;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }

STDMETHODIMP_(ULONG) CAutoFigures::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CAutoFigures::Release(void)
    {
    //CCosmoClient deletes this object during shutdown
    if (0==--m_cRef)
        {
        /*
         * Note:  This early release is to avoid a bug in
         * Beta Windows NT 3.51 at the time this code was
         * finalized.  Technically it should be fine to leave
         * the Release call in CImpIDispatch::~CImpIDispatch
         * (see autobase.cpp), but making the call here
         * avoids a crash on a null pointer.
         */
        ReleaseInterface(m_pImpIDispatch->m_pITypeInfo);
        }
    return m_cRef;
    }




/*
 * CAutoFigures::VTableInterface
 *
 * Purpose:
 *  Returns the right vtable pointer to use when calling
 *  ITypeInfo::Invoke (see CImpIDispatch::Invoke in AUTOBASE.CPP).
 */
void *CAutoFigures::VTableInterface(void)
    {
    return (ICosmoFigures *)this;
    }



//The ICosmoFigures implementation

/*
 * CAutoFigures::Application
 * CAutoFigures::Parent
 * Properties, read-only
 *
 * The application object (CAutoApp) in which we're contained,
 * which is stored in the frame object.  Basically we walk
 * up from the client to the frame to it's application object
 * to get the IDispatch we need.
 */

STDMETHODIMP_(IDispatch *) CAutoFigures::get_Application(void)
    {
    PCCosmoFrame    pFR;

    pFR=(PCCosmoFrame)m_pCL->Frame();
    return pFR->AutoApp()->get_Application();
    }

STDMETHODIMP_(IDispatch *) CAutoFigures::get_Parent(void)
    {
    return get_Application();
    }



/*
 * CAutoFigures::Count
 * Property, read-only
 *
 * The number of figures in this collection
 */

STDMETHODIMP_(long) CAutoFigures::get_Count(void)
    {
    //This is easy:  just the number of items in the listbox.
    return m_pCL->m_cDoc;
    }



/*
 * CAutoFigures::Item
 * Method
 *
 * This is essentially an array lookup operator for the collection.
 * Collection.Item by itself the same as the collection itself.
 * Otherwise you can refer to the item by index or by path, which
 * shows up in the VARIANT parameter.  We have to check the type
 * of the variant to see if it's VT_I4 (an index) or VT_BSTR (a
 * path) and do the right thing.
 */

STDMETHODIMP_(IDispatch *) CAutoFigures::Item(VARIANT index)
    {
    IDispatch  *pIDispatch=NULL;
    PCCosmoDoc  pDoc;
    const int   cch=512;
    TCHAR       szPath[cch];
    UINT        i;
    HWND        hList=m_pCL->m_hListDocs;

    /*
     * Each case in this switch gets at a different pointer
     * and stores it in pIDispatch for return.
     */
    switch (index.vt)
        {
        case VT_ERROR:
            /*
             * No parameters, get the "Figures" collection
             * IDispatch, which we can easily retrieve with
             * our own QueryInterface.
             */
            QueryInterface(IID_IDispatch, (PPVOID)&pIDispatch);
            break;

        case VT_I4:
            if (LB_ERR!=SendMessage(hList, LB_GETTEXT
                , (int)index.lVal, (LONG)&pDoc))
                {
                //Sets pIDispatch to NULL on failure.
                pDoc->AutoFigure()->QueryInterface(IID_IDispatch
                    , (PPVOID)&pIDispatch);
                }

            break;

        case VT_BSTR:
            /*
             * First we'll iterate over the pages and check
             * for full path matches.  If that doesn't yield
             * anything, then we'll see if index.bstrVal is
             * just a filename inside one of the paths.
             */
            for (i=0; i < m_pCL->m_cDoc; i++)
                {
                if (LB_ERR!=SendMessage(hList, LB_GETTEXT
                    , i, (LONG)&pDoc))
                    {
                    pDoc->FilenameGet(szPath, cch);

                   #ifdef WIN32ANSI
                    char    szTemp[512];

                    WideCharToMultiByte(CP_ACP, 0, index.bstrVal, -1
                        , szTemp, 512, NULL, NULL);

                    if (0==lstrcmpi(szPath, szTemp))
                   #else
                    if (0==lstrcmpi(szPath, index.bstrVal))
                   #endif
                        {
                        //Found it...
                        pDoc->AutoFigure()->QueryInterface
                            (IID_IDispatch, (PPVOID)&pIDispatch);
                        }
                    }
                }

            //Stop now if we found anything.
            if (NULL!=pIDispatch)
                break;

            //Now look for portions of the path
            for (i=0; i < m_pCL->m_cDoc; i++)
                {
                if (LB_ERR!=SendMessage(hList, LB_GETTEXT
                    , i, (LONG)&pDoc))
                    {
                    LPTSTR  psz;

                    pDoc->FilenameGet(szPath, cch);

                   #ifdef WIN32ANSI
                    char    szTemp[512];

                    WideCharToMultiByte(CP_ACP, 0, index.bstrVal, -1
                        , szTemp, 512, NULL, NULL);
                    psz=_tcsstr(szPath, szTemp);
                   #else
                    psz=_tcsstr(szPath, index.bstrVal);
                   #endif

                    if (NULL!=psz)
                        {
                        //Found it...
                        pDoc->AutoFigure()->QueryInterface
                            (IID_IDispatch, (PPVOID)&pIDispatch);
                        }
                    }
                }


            break;

        default:
            return NULL;
        }

    return pIDispatch;
    }



/*
 * CAutoFigures::Add
 * CAutoFigures::Open
 * Methods
 *
 * Creates a new figure window with an empty figure (Add) or one
 * with the contents of a file (Open), and adds it to the collection.
 */

STDMETHODIMP_(IDispatch *) CAutoFigures::Add(void)
    {
    return NewFigure(NULL);
    }

STDMETHODIMP_(IDispatch *) CAutoFigures::Open(BSTR bstrPath)
    {
   #ifdef WIN32ANSI
    char        szTemp[512];

    WideCharToMultiByte(CP_ACP, 0, bstrPath, -1, szTemp
        , 512, NULL, NULL);
    return NewFigure(szTemp);
   #else
    return NewFigure(bstrPath);
   #endif
    }



/*
 * CAutoFigures:NewFigure
 *
 * Purpose:
 *  Internal helper function to centralize figure creation for
 *  Add and Open.
 *
 * Parameters:
 *  pszPath         LPTSTR to a file to open if this is an open.
 *                  Should be NULL for Add.
 *
 * Return Value:
 *  IDispatch *     Return value for Add and Open
 */

IDispatch * CAutoFigures::NewFigure(LPTSTR pszPath)
    {
    PCCosmoDoc  pDoc;
    IDispatch  *pIDispatch=NULL;
    HRESULT     hr;

    //Try creating a hidden document, which creates the object.
    pDoc=(PCCosmoDoc)m_pCL->NewDocument(FALSE);

    if (NULL==pDoc)
        return NULL;

    hr=ResultFromScode(E_FAIL);

    //Try to load the file and get the IDispatch for the document
    if (DOCERR_NONE==pDoc->Load(TRUE, pszPath))
        {
        hr=pDoc->AutoFigure()->QueryInterface(IID_IDispatch
            , (PPVOID)&pIDispatch);
        }

    if (FAILED(hr))
        m_pCL->CloseDocument(pDoc);
    else
        g_cObj++;

    return pIDispatch;
    }





/*
 * CAutoFigures::Close
 * Method
 *
 * Closes all figure windows in the collection
 */

STDMETHODIMP_(void) CAutoFigures::Close(void)
    {
    m_pCL->QueryCloseAllDocuments(TRUE, FALSE);
    return;
    }





/*
 * CAutoFigures::_NewEnum
 * Method
 *
 * Creates and returns an enumerator of the current list of
 * figures in this collection.
 */

STDMETHODIMP_(IUnknown *) CAutoFigures::_NewEnum(void)
    {
    PCEnumFigures   pNew=NULL;
    BOOL            fRet=TRUE;

    pNew=new CEnumFigures(m_pCL->Instance());

    if (NULL!=pNew)
        {
        if (!pNew->Init(m_pCL->m_hListDocs, FALSE))
            {
            delete pNew;
            pNew=NULL;
            }
        else
            pNew->AddRef();
        }

    return (IUnknown *)pNew;
    }




//CEnumFigures implementation of IEnumVARIANT


/*
 * CEnumFigures::CEnumFigures
 * CEnumFigures::~CEnumFigures
 *
 * Parameters (Constructor):
 *  hInst           HINSTANCE of the application.
 */

CEnumFigures::CEnumFigures(HINSTANCE hInst)
    {
    m_cRef=0;
    m_hList=NULL;
    m_hInst=hInst;
    m_iCur=0;
    m_cItems=0;
    return;
    }


CEnumFigures::~CEnumFigures(void)
    {
    if (NULL!=m_hList)
        DestroyWindow(m_hList);

    return;
    }



/*
 * CEnumFigures::Init
 *
 * Purpose:
 *  Initializes the enumeration with any operations that might fail.
 *
 * Parameters:
 *  hListPDoc       HWND of the listbox containing the current
 *                  set of document pointers.
 *  fClone          BOOL indicating if this is a clone creation
 *                  in which case hListPDoc already has what we want
 *                  and we can just copy it directly.
 *
 * Return Value:
 *  BOOL            TRUE if initialization succeeded,
 *                  FALSE otherwise.
 */
BOOL CEnumFigures::Init(HWND hListPDoc, BOOL fClone)
    {
    UINT        i;
    UINT        cDoc;
    PCDocument  pDoc;

    //Create our own list
    m_hList=CreateWindow(TEXT("listbox"), TEXT("EnumList")
        , WS_POPUP | LBS_OWNERDRAWFIXED, 0, 0, 100, 100
        , HWND_DESKTOP, NULL, m_hInst, NULL);

    if (NULL==m_hList)
        return FALSE;

    /*
     * An enumeration should not be attached to any sort of
     * dynamic list, so we have to initialize our own list here.
     * Furthermore, the hList we get here has document object
     * pointers which could possibly become invalid and we have
     * no way of knowing it.  So we take each pointer and copy
     * the window handle of that document into our own list.  If
     * the window is destroyed, then we have a way of checking
     * that condition and failing to return a valid pointer
     * in other partsof this enumerator.
     */

    cDoc=(UINT)SendMessage(hListPDoc, LB_GETCOUNT, 0, 0L);

    for (i=0; i < cDoc; i++)
        {
        if (LB_ERR!=SendMessage(hListPDoc, LB_GETTEXT, i
            , (LONG)&pDoc))
            {
            HWND    hWndDoc;

            //When cloning we have the window handle already.
            if (fClone)
                hWndDoc=(HWND)(UINT)(LONG)pDoc;
            else
                hWndDoc=pDoc->Window();

            if (LB_ERR!=SendMessage(m_hList, LB_ADDSTRING, 0
                , (LONG)(UINT)hWndDoc))
                m_cItems++;
            }
        }

    return TRUE;
    }



/*
 * CEnumFigures::QueryInterface
 * CEnumFigures::AddRef
 * CEnumFigures::Release
 */

STDMETHODIMP CEnumFigures::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IEnumVARIANT==riid)
        *ppv=this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CEnumFigures::AddRef(void)
    {
    ++m_cRef;
    return m_cRef;
    }

STDMETHODIMP_(ULONG) CEnumFigures::Release(void)
    {
    ULONG       cRefT;

    cRefT=--m_cRef;

    if (0L==m_cRef)
        delete this;

    return cRefT;
    }


/*
 * CEnumFigures::Next
 * CEnumFigures::Skip
 * CEnumFigures::Reset
 * CEnumFigures::Clone
 *
 * Standard enumerator members for IEnumVARIANT
 */

STDMETHODIMP CEnumFigures::Next(ULONG cVar, VARIANT *pVar
    , ULONG *pulVar)
    {
    ULONG       cReturn=0L;
    PCCosmoDoc  pDoc;
    HRESULT     hr;
    void       *pv;
    LONG        l;

    if (NULL==pulVar)
        {
        if (1L!=cVar)
            return ResultFromScode(E_POINTER);
        }
    else
        *pulVar=0L;

    if (NULL==pVar || m_iCur >= m_cItems)
        return ResultFromScode(S_FALSE);

    while (m_iCur < m_cItems && cVar > 0)
        {
        if (LB_ERR==SendMessage(m_hList, LB_GETTEXT, (UINT)m_iCur++
            , (LONG)&l))
            continue;

        /*
         * Try getting the document pointer.  If this fails
         * then the window is invalid (document is destroyed)
         * so remove it from the list for future enumerations.
         */
        pDoc=(PCCosmoDoc)SendMessage((HWND)(UINT)l
            , DOCM_PDOCUMENT, 0, 0L);

        if (NULL==pDoc)
            {
            SendMessage(m_hList, LB_DELETESTRING, (UINT)--m_iCur, 0L);
            continue;
            }

        hr=pDoc->AutoFigure()->QueryInterface(IID_IDispatch, &pv);

        if (SUCCEEDED(hr))
            {
            *pVar->ppdispVal=(IDispatch *)pv;
            pVar++;
            cReturn++;
            cVar--;
            }
        }


    if (NULL!=pulVar)
        *pulVar=cReturn;

    return NOERROR;
    }


STDMETHODIMP CEnumFigures::Skip(ULONG cSkip)
    {
    if ((m_iCur+cSkip) >= m_cItems)
        return ResultFromScode(S_FALSE);

    m_iCur+=cSkip;
    return NOERROR;
    }


STDMETHODIMP CEnumFigures::Reset(void)
    {
    m_iCur=0;
    return NOERROR;
    }


STDMETHODIMP CEnumFigures::Clone(LPENUMVARIANT *ppEnum)
    {
    PCEnumFigures   pNew;

    *ppEnum=NULL;

    pNew=new CEnumFigures(m_hInst);

    if (NULL!=pNew)
        {
        if (!pNew->Init(m_hList, TRUE))
            {
            delete pNew;
            pNew=NULL;
            }
        else
            pNew->AddRef();
        }

    *ppEnum=(IEnumVARIANT *)pNew;
    return (NULL!=pNew) ? NOERROR : ResultFromScode(E_OUTOFMEMORY);
    }
