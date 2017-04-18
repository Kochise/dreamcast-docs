/*
 * DOCUMENT.CPP
 * Patron Chapter 17
 *
 * Implementation of the CPatronDoc derivation of CDocument that
 * manages pages for us.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"
#include <memory.h>
#include <dlgs.h>       //Pring Dlg button IDs


/*
 * CPatronDoc::CPatronDoc
 * CPatronDoc::~CPatronDoc
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the application.
 *  pFR             PCFrame of the frame object.
 *  pAdv            PCDocumentAdviseSink to notify on events.
 */

CPatronDoc::CPatronDoc(HINSTANCE hInst, PCFrame pFR
    , PCDocumentAdviseSink pAdv)
    : CDocument(hInst, pFR, pAdv)
    {
    m_pPG=NULL;
    m_lVer=VERSIONCURRENT;
    m_pIStorage=NULL;
    m_fPrintSetup=TRUE;
    m_pDropTarget=NULL;

    //CHAPTER17MOD
    //These CFSTR_* values are standard (defined in INC\CLASSLIB.H)
    m_cfEmbeddedObject=RegisterClipboardFormat
        (CFSTR_EMBEDDEDOBJECT);
    m_cfObjectDescriptor=RegisterClipboardFormat
        (CFSTR_OBJECTDESCRIPTOR);
    //End CHAPTER17MOD

    return;
    }


CPatronDoc::~CPatronDoc(void)
    {
    if (NULL!=m_pPG)
        delete m_pPG;

    if (NULL!=m_pIStorage)
        m_pIStorage->Release();

    CoFreeUnusedLibraries();
    return;
    }





/*
 * CPatronDoc::Init
 *
 * Purpose:
 *  Initializes an already created document window.  The client
 *  actually creates the window for us, then passes that here for
 *  further initialization.
 *
 * Parameters:
 *  pDI             PDOCUMENTINIT containing initialization
 *                  parameters.
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 */

BOOL CPatronDoc::Init(PDOCUMENTINIT pDI)
    {
    //Change the stringtable range to our customization.
    pDI->idsMin=IDS_DOCUMENTMIN;
    pDI->idsMax=IDS_DOCUMENTMAX;

    //Do default initialization
    if (!CDocument::Init(pDI))
        return FALSE;

    //Pages are created when we get a Load later.
    return TRUE;
    }







/*
 * CPatronDoc::FMessageHook
 *
 * Purpose:
 *  Processes WM_SIZE for the document so we can resize the Pages
 *  window.
 *
 * Parameters:
 *  <WndProc Parameters>
 *  pLRes           LRESULT * in which to store the return
 *                  value for the message.
 *
 * Return Value:
 *  BOOL            TRUE to prevent further processing,
 *                  FALSE otherwise.
 */

BOOL CPatronDoc::FMessageHook(HWND hWnd, UINT iMsg, WPARAM wParam
    , LPARAM lParam, LRESULT *pLRes)
    {
    UINT        dx, dy;
    RECT        rc;

    *pLRes=0;

    //Eat to prevent flickering
    if (WM_ERASEBKGND==iMsg)
        return TRUE;

    if (WM_SIZE==iMsg && NULL!=m_pPG)
        {
        dx=LOWORD(lParam);
        dy=HIWORD(lParam);

        if (SIZE_MINIMIZED!=wParam)
            {
            //Resize Pages window to fit the new document size.
            GetClientRect(hWnd, &rc);
            m_pPG->RectSet(&rc, FALSE);
            }
        }

    if (WM_DESTROY==iMsg)
        {
        /*
         * We have to revoke the drop target here because the window
         * will be destroyed and the property forcefully removed
         * before we could do this in the destructor.
         */
        if (NULL!=m_pDropTarget)
            {
            RevokeDragDrop(m_hWnd);
            CoLockObjectExternal(m_pDropTarget, FALSE, TRUE);
            m_pDropTarget->Release();
            }

        return FALSE;
        }

    /*
     * We return FALSE even on WM_SIZE so we can let the default
     * procedure handle maximized MDI child windows appropriately.
     */
    return FALSE;
    }







/*
 * CPatronDoc::Clear
 *
 * Purpose:
 *  Sets all contents in the document back to defaults with no
 *  filename.
 *
 * Paramters:
 *  None
 *
 * Return Value:
 *  None
 */

void CPatronDoc::Clear(void)
    {
    //Completely reset the pages
    if (NULL!=m_pPG)
        m_pPG->StorageSet(NULL, FALSE, FALSE);

    CDocument::Clear();
    m_lVer=VERSIONCURRENT;
    return;
    }




/*
 * CPatronDoc::FDirtyGet
 *
 * Purpose:
 *  Returns the current dirty status of the document.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the file is clean, FALSE otherwise.
 */

BOOL CPatronDoc::FDirtyGet()
    {
    BOOL    fPageDirty;

    fPageDirty=m_pPG->FIsDirty();
    return m_fDirty | fPageDirty;
    }





/*
 * CPatronDoc::Delete
 *
 * Purpose:
 *  Removed the current object from the document.
 *
 * Paramters:
 *  None
 *
 * Return Value:
 *  None
 */

void CPatronDoc::Delete(void)
    {
    if (NULL!=m_pPG)
        m_pPG->TenantDestroy();

    CoFreeUnusedLibraries();
    return;
    }





/*
 * CPatronDoc::FQueryObjectSelected
 *
 * Purpose:
 *  Returns whether or not there is an object selected in this
 *  document for Cut, Copy, Delete functions.
 *
 * Parameters:
 *  hMenu           HMENU of the Edit menu.
 *
 * Return Value:
 *  BOOL            TRUE if we have an object, FALSE otherwise.
 */

BOOL CPatronDoc::FQueryObjectSelected(HMENU hMenu)
    {
    return m_pPG->FQueryObjectSelected(hMenu);
    }





/*
 * CPatronDoc::Load
 *
 * Purpose:
 *  Loads a given document without any user interface overwriting
 *  the previous contents of the editor.
 *
 * Parameters:
 *  fChangeFile     BOOL indicating if we're to update the window
 *                  title and the filename from using this file.
 *  pszFile         LPTSTR to the filename to load.  Could be NULL
 *                  for an untitled document.
 *
 * Return Value:
 *  UINT            An error value from DOCERR_*
 */

UINT CPatronDoc::Load(BOOL fChangeFile, LPTSTR pszFile)
    {
    RECT        rc;
    LPSTORAGE   pIStorage;
    HRESULT     hr;
    CLSID       clsID;
    DWORD       dwMode=STGM_TRANSACTED | STGM_READWRITE
                    | STGM_SHARE_EXCLUSIVE;

    if (NULL==pszFile)
        {
        //Create a new temp file.
        hr=StgCreateDocfile(NULL, dwMode | STGM_CREATE
            | STGM_DELETEONRELEASE, 0, &pIStorage);

        //Mark this our class since we check with ReadClassStg.
        if (SUCCEEDED(hr))
            WriteClassStg(pIStorage, CLSID_PatronPages);
        }
    else
        {
        hr=StgOpenStorage(pszFile, NULL, dwMode, NULL, 0, &pIStorage);
        }

    if (FAILED(hr))
        return DOCERR_COULDNOTOPEN;

    //Check if this is our type of file and exit if not.
    hr=ReadClassStg(pIStorage, &clsID);

    if (FAILED(hr) || CLSID_PatronPages!=clsID)
        {
        pIStorage->Release();
        return DOCERR_READFAILURE;
        }

    //Attempt to create our contained Pages window.
    m_pPG=new CPages(m_hInst, m_cf);
    GetClientRect(m_hWnd, &rc);

    if (!m_pPG->Init(m_hWnd, &rc, WS_CHILD | WS_VISIBLE
        , ID_PAGES, NULL))
        {
        pIStorage->Release();
        return DOCERR_READFAILURE;
        }

    if (!m_pPG->StorageSet(pIStorage, FALSE, (NULL==pszFile)))
        {
        pIStorage->Release();
        return DOCERR_READFAILURE;
        }

    //Open the window up for drag-drop
    m_pDropTarget=new CDropTarget(this);

    if (NULL!=m_pDropTarget)
        {
        m_pDropTarget->AddRef();
        CoLockObjectExternal(m_pDropTarget, TRUE, FALSE);
        RegisterDragDrop(m_hWnd, m_pDropTarget);
        }

    m_pIStorage=pIStorage;
    Rename(pszFile);

    //Do initial setup if new file, otherwise Pages handles things.
    if (NULL==pszFile)
        {
        //Go initialize the Pages for the default printer.
        if (!PrinterSetup(NULL, TRUE))
            return DOCERR_COULDNOTOPEN;

        //Go create an initial page.
        m_pPG->PageInsert(0);
        }
    else
        {
        //Can't change an already saved configuration
        m_fPrintSetup=FALSE;
        }

    FDirtySet(FALSE);
    return DOCERR_NONE;
    }







/*
 * CPatronDoc::Save
 *
 * Purpose:
 *  Writes the file to a known filename, requiring that the user
 *  has previously used FileOpen or FileSaveAs in order to have
 *  a filename.
 *
 * Parameters:
 *  uType           UINT indicating the type of file the user
 *                  requested to save in the File Save As dialog.
 *  pszFile         LPTSTR under which to save.  If NULL, use the
 *                  current name.
 *
 * Return Value:
 *  UINT            An error value from DOCERR_*
 */

UINT CPatronDoc::Save(UINT uType, LPTSTR pszFile)
    {
    HRESULT     hr;
    LPSTORAGE   pIStorage;

    //Save or Save As with the same file is just a commit.
    if (NULL==pszFile
        || (NULL!=pszFile && 0==lstrcmpi(pszFile, m_szFile)))
        {
        WriteFmtUserTypeStg(m_pIStorage, m_cf
            , PSZ(IDS_CLIPBOARDFORMAT));

        //Insure pages are up to date.
        m_pPG->StorageUpdate(FALSE);

        //Commit everyting
        m_pIStorage->Commit(STGC_DEFAULT);

        FDirtySet(FALSE);
        return DOCERR_NONE;
        }

    /*
     * When we're given a name, open the storage, creating it new
     * if it does not exist or overwriting the old one.  Then CopyTo
     * from the current to the new, Commit the new, Release the old.
     */

    hr=StgCreateDocfile(pszFile, STGM_TRANSACTED | STGM_READWRITE
        | STGM_CREATE | STGM_SHARE_EXCLUSIVE, 0, &pIStorage);

    if (FAILED(hr))
        return DOCERR_COULDNOTOPEN;

    WriteClassStg(pIStorage, CLSID_PatronPages);
    WriteFmtUserTypeStg(pIStorage, m_cf, PSZ(IDS_CLIPBOARDFORMAT));

    //Insure all pages are up-to-date.
    m_pPG->StorageUpdate(TRUE);

    //This also copies the CLSID we stuff in here on file creation.
    hr=m_pIStorage->CopyTo(NULL, NULL, NULL, pIStorage);

    if (FAILED(hr))
        {
        SCODE       sc;

        pIStorage->Release();
        sc=GetScode(hr);

        /*
         * If we failed because of low memory, use IRootStorage
         * to switch into the new file.
         */
        if (E_OUTOFMEMORY==sc)
            {
            LPROOTSTORAGE        pIRoot;

            //Delete file we already created
            DeleteFile(pszFile);

            if (FAILED(m_pIStorage->QueryInterface
                (IID_IRootStorage, (PPVOID)&pIRoot)))
                return DOCERR_WRITEFAILURE;

           #ifdef WIN32ANSI
            OLECHAR     szTemp[MAX_PATH];

            MultiByteToWideChar(CP_ACP, 0, pszFile, -1, szTemp, MAX_PATH);
            hr=pIRoot->SwitchToFile(szTemp);
           #else
            hr=pIRoot->SwitchToFile(pszFile);
           #endif
            pIRoot->Release();

            if (FAILED(hr))
                return DOCERR_WRITEFAILURE;

            //If successful, the Commit below finishes the save.
            pIStorage=m_pIStorage;
            m_pIStorage->AddRef();    //Matches Release below
            }
        }

    pIStorage->Commit(STGC_DEFAULT);

    /*
     * Revert changes on the original storage.  If this was a temp
     * file, it's deleted since we used STGM_DELETEONRELEASE.
     */
    m_pIStorage->Release();

    //Make this new storage current
    m_pIStorage=pIStorage;
    m_pPG->StorageSet(pIStorage, TRUE, FALSE);

    FDirtySet(FALSE);
    Rename(pszFile);    //Update caption bar.

    return DOCERR_NONE;
    }








/*
 * CPatronDoc::Clip
 *
 * Purpose:
 *  Places a private format, a metafile, and a bitmap of the display
 *  on the clipboard, optionally implementing Cut by deleting the
 *  data in the current window after rendering.
 *
 * Parameters:
 *  hWndFrame       HWND of the main window.
 *  fCut            BOOL indicating cut (TRUE) or copy (FALSE).
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPatronDoc::Clip(HWND hWndFrame, BOOL fCut)
    {
    if (NULL==m_pPG)
        return FALSE;

    return m_pPG->TenantClip(fCut);
    }





/*
 * CPatronDoc::Paste
 *
 * Purpose:
 *  Retrieves the private data format from the clipboard and sets it
 *  to the current figure in the editor window.
 *
 *  Note that if this function is called, then the clipboard format
 *  is available because the Paste menu item is only enabled if the
 *  format is present.
 *
 * Parameters:
 *  hWndFrame       HWND of the main window.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPatronDoc::Paste(HWND hWndFrame)
    {
    LPDATAOBJECT    pIDataObject;
    BOOL            fRet=FALSE;
    FORMATETC       fe;
    TENANTTYPE      tType;

    if (NULL==m_pPG)
        return FALSE;

    if (FAILED(OleGetClipboard(&pIDataObject)))
        return FALSE;

    //Go get type and format we *can* paste, then actually paste it.
    if (FQueryPasteFromData(pIDataObject, &fe, &tType))
        {
        //CHAPTER17MOD
        fRet=PasteFromData(pIDataObject, &fe, tType, NULL
            , 0L, TRUE);
        //End CHAPTER17MOD
        }

    pIDataObject->Release();
    return fRet;
    }




/*
 * CPatronDoc::FQueryPaste
 *
 * Purpose:
 *  Determines if we can paste data from the clipboard.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if data is available, FALSE otherwise.
 */

BOOL CPatronDoc::FQueryPaste(void)
    {
    LPDATAOBJECT    pIDataObject;
    BOOL            fRet;

    if (FAILED(OleGetClipboard(&pIDataObject)))
        return FALSE;

    fRet=FQueryPasteFromData(pIDataObject, NULL, NULL);
    pIDataObject->Release();
    return fRet;
    }






/*
 * CPatronDoc::PasteSpecial
 *
 * Purpose:
 *  Retrieves a specific data format from the clipboard and sends
 *  it to the editor window appropriately.
 *
 *  Note that if this function is called, then the appropriate
 *  format is available because the Paste menu item is only
 *  enabled if the format is present.
 *
 * Parameters:
 *  hWndFrame       HWND of the main window
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPatronDoc::PasteSpecial(HWND hWndFrame)
    {
    OLEUIPASTESPECIAL   ps;
    //CHAPTER17MOD
    OLEUIPASTEENTRY     rgPaste[5];
    DWORD               dwData=0;
    //End CHAPTER17MOD
    UINT                uTemp;
    BOOL                fRet=FALSE;

    if (NULL==m_pPG)
        return FALSE;

    memset(&ps, 0, sizeof(ps));

    if (FAILED(OleGetClipboard(&ps.lpSrcDataObj)))
        return FALSE;

    ps.cbStruct=sizeof(ps);
    ps.hWndOwner=hWndFrame;

    ps.dwFlags=PSF_SELECTPASTE;

    ps.arrPasteEntries=rgPaste;

    //CHAPTER17MOD
    ps.cPasteEntries=5;

    //Set up Paste Special descriptor arrays.
    SETDefFormatEtc(rgPaste[0].fmtetc, m_cf, TYMED_HGLOBAL);
    rgPaste[0].lpstrFormatName=PSZ(IDS_CLIPBOARDFORMAT);
    rgPaste[0].lpstrResultText=PSZ(IDS_PASTEASPATRON);
    rgPaste[0].dwFlags=OLEUIPASTE_PASTEONLY;

    //Embedded objects can be iconic displays if the user wants.
    SETDefFormatEtc(rgPaste[1].fmtetc, m_cfEmbeddedObject
        , TYMED_ISTORAGE);
    rgPaste[1].lpstrFormatName=PSZ(IDS_PASTEOBJECT);
    rgPaste[1].lpstrResultText=PSZ(IDS_PASTEASOBJECT);

    /*
     * CAUTION:  Use OLEUI_PASTE with embedded objects or else
     * this item will not show up in the dialog.  I learned this the
     * hard way (that is, after about 6 hours of pulling hair!).
     */
    rgPaste[1].dwFlags=OLEUIPASTE_PASTE | OLEUIPASTE_ENABLEICON;


    SETDefFormatEtc(rgPaste[2].fmtetc,CF_METAFILEPICT,TYMED_MFPICT);
    rgPaste[2].lpstrFormatName=PSZ(IDS_PASTEMETAFILE);
    rgPaste[2].lpstrResultText=PSZ(IDS_PASTEASMETAFILE);
    rgPaste[2].dwFlags=OLEUIPASTE_PASTEONLY;

    SETDefFormatEtc(rgPaste[3].fmtetc, CF_DIB, TYMED_HGLOBAL);
    rgPaste[3].lpstrFormatName=PSZ(IDS_PASTEDIB);
    rgPaste[3].lpstrResultText=PSZ(IDS_PASTEASDIB);
    rgPaste[3].dwFlags=OLEUIPASTE_PASTEONLY;

    SETDefFormatEtc(rgPaste[4].fmtetc, CF_BITMAP, TYMED_GDI);
    rgPaste[4].lpstrFormatName=PSZ(IDS_PASTEBITMAP);
    rgPaste[4].lpstrResultText=PSZ(IDS_PASTEASBITMAP);
    rgPaste[4].dwFlags=OLEUIPASTE_PASTEONLY;

    uTemp=OleUIPasteSpecial(&ps);

    if (OLEUI_OK==uTemp)
        {
        UINT        i=ps.nSelectedIndex;
        TENANTTYPE  tType;

        if (1==ps.nSelectedIndex)
            tType=TENANTTYPE_EMBEDDEDOBJECTFROMDATA;
        else
            tType=TENANTTYPE_STATIC;

        //Handle iconic aspects...
        if ((1==i) && (PSF_CHECKDISPLAYASICON & ps.dwFlags)
            && NULL!=ps.hMetaPict)
            {
            rgPaste[i].fmtetc.dwAspect=DVASPECT_ICON;
            dwData=(DWORD)(UINT)ps.hMetaPict;
            }

        fRet=PasteFromData(ps.lpSrcDataObj, &rgPaste[i].fmtetc
            , tType, NULL, dwData, FALSE);

        //Always free this regardless of what we do with it.
        INOLE_MetafilePictIconFree(ps.hMetaPict);
        }
    //End CHAPTER17MOD

    ps.lpSrcDataObj->Release();
    return fRet;
    }




/*
 * CPatronDoc::FQueryPasteFromData
 * (Protected)
 *
 * Purpose:
 *  Determines if we can paste data from a data object.
 *
 * Parameters:
 *  pIDataObject    LPDATAOBJECT from which we might want to paste.
 *  pFE             LPFORMATETC in which to return the first format
 *                  we can use.  Ignored if NULL.
 *  ptType          PTENANTTYPE in which to store the type of
 *                  object we can paste.  Ignored if NULL.
 *
 * Return Value:
 *  BOOL            TRUE if data is available, FALSE otherwise.
 */

BOOL CPatronDoc::FQueryPasteFromData(LPDATAOBJECT pIDataObject
    , LPFORMATETC pFE, PTENANTTYPE ptType)
    {
    FORMATETC       fe;
    //CHAPTER17MOD
    HRESULT         hr, hr2;
    //End CHAPTER17MOD

    if (NULL!=(LPVOID)ptType)
        *ptType=TENANTTYPE_STATIC;

    //Any of our specific data here?
    SETDefFormatEtc(fe, m_cf, TYMED_HGLOBAL);
    hr=pIDataObject->QueryGetData(&fe);

    //CHAPTER17MOD
    //If embedded object data is available, set the appropriate type
    hr2=OleQueryCreateFromData(pIDataObject);

    if (NOERROR==hr2)
        {
        if (NULL!=pFE)
            {
            /*
             * Default to content.  Paste will use
             * CFSTR_OBJECTDESCRIPTOR to figure the actual aspect.
             */
            SETDefFormatEtc(*pFE, m_cfEmbeddedObject
                , TYMED_ISTORAGE);
            }

        if (NULL!=(LPVOID)ptType)
            *ptType=TENANTTYPE_EMBEDDEDOBJECTFROMDATA;

        /*
         * Return now if PatronObject wasn't available, otherwise
         * break out so that pFE gets PatronObject format.
         */
        if (NOERROR!=hr)
            return TRUE;
        }


    if (NOERROR!=hr && NOERROR!=hr2)
    //End CHAPTER17MOD
        {
        //Try metafile, DIB, then bitmap, setting fe each time
        SETDefFormatEtc(fe, CF_METAFILEPICT, TYMED_MFPICT);
        hr=pIDataObject->QueryGetData(&fe);

        if (NOERROR!=hr)
            {
            SETDefFormatEtc(fe, CF_DIB, TYMED_HGLOBAL);
            hr=pIDataObject->QueryGetData(&fe);

            if (NOERROR!=hr)
                {
                SETDefFormatEtc(fe, CF_BITMAP, TYMED_GDI);
                hr=pIDataObject->QueryGetData(&fe);
                }
            }
        }

    if (NOERROR==hr && NULL!=pFE)
        *pFE=fe;

    return (NOERROR==hr);
    }





/*
 * CPatronDoc::PasteFromData
 * (Protected)
 *
 * Purpose:
 *  Retrieves the private data format from a data object and sets
 *  it to the current figure in the editor window.
 *
 * Parameters:
 *  pIDataObject    LPDATAOBJECT from which to paste.
 *  pFE             LPFORMATETC to use in the paste. Cannot be NULL.
 *  tType           TENANTTYPE to paste.
 *  ppo             PPATRONOBJECT containing placement data.
 *  dwData          DWORD extra data sensitive to tType
 *  fUseObjDesc     BOOL indicating to use CFSTR_OBJECTDESCRIPTOR
 *                  format for determining the aspect of the object
 *                  if the format is available.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

//CHAPTER17MOD
BOOL CPatronDoc::PasteFromData(LPDATAOBJECT pIDataObject
    , LPFORMATETC pFE, TENANTTYPE tType, PPATRONOBJECT ppo
    , DWORD dwData, BOOL fUseObjDesc)
//End CHAPTER17MOD
    {
    BOOL                fRet;
    HRESULT             hr;
    PATRONOBJECT        po;
    STGMEDIUM           stm;
    //CHAPTER17MOD
    LPOBJECTDESCRIPTOR  pOD;
    FORMATETC           fe;
    BOOL                fRelease=FALSE;
    //End CHAPTER17MOD

    if (NULL==pFE)
        return FALSE;

    //If not given any placement data, see if we can retrieve it
    if (pFE->cfFormat==m_cf && NULL==ppo)
        {
        hr=pIDataObject->GetData(pFE, &stm);

        if (SUCCEEDED(hr))
            {
            ppo=(PPATRONOBJECT)GlobalLock(stm.hGlobal);

            po=*ppo;
            ppo=&po;

            //CHAPTER17MOD
            //If there's an object here, make sure type is right.
            if (ppo->fe.cfFormat==m_cfEmbeddedObject)
                tType=TENANTTYPE_EMBEDDEDOBJECTFROMDATA;
            //End CHAPTER17MOD

            GlobalUnlock(stm.hGlobal);
            ReleaseStgMedium(&stm);
            }
        }

    //CHAPTER17MOD
    /*
     * If we're told to look at CFSTR_OBJECTDESCRIPTOR, then try to get
     * the data and copy the aspect out of it.  We're not interested
     * in any other part of it, however.
     */
    if (fUseObjDesc)
        {
        SETDefFormatEtc(fe, m_cfObjectDescriptor, TYMED_HGLOBAL);

        if (SUCCEEDED(pIDataObject->GetData(&fe, &stm)))
            {
            pOD=(LPOBJECTDESCRIPTOR)GlobalLock(stm.hGlobal);
            pFE->dwAspect=pOD->dwDrawAspect;

            if (NULL!=ppo)
                ppo->fe.dwAspect=pFE->dwAspect;

            GlobalUnlock(stm.hGlobal);
            ReleaseStgMedium(&stm);

            /*
             * Furthermore, if pFE->dwAspect is DVASPECT_ICON, get
             * the metafile which will always be the icon
             * representation.
             */
            SETFormatEtc(fe, CF_METAFILEPICT, DVASPECT_ICON, NULL
                , TYMED_MFPICT, -1);

            if (SUCCEEDED(pIDataObject->GetData(&fe, &stm)))
                {
                dwData=(DWORD)(UINT)stm.hGlobal;
                fRelease=TRUE;
                }
            }
        }
    //End CHAPTER17MOD

    fRet=m_pPG->TenantCreate(tType, pIDataObject, pFE, ppo, dwData);

    //CHAPTER17MOD
    //Release the stm from the last GetData
    if (fRelease)
        ReleaseStgMedium(&stm);
    //End CHAPTER17MOD

    if (fRet)
        {
        //Disable Printer Setup once we've created a tenant.
        m_fPrintSetup=FALSE;
        FDirtySet(TRUE);
        }

    return fRet;
    }






/*
 * CPatronDoc::NewPage
 *
 * Purpose:
 *  Creates a new page in the document's pages control after the
 *  current page.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Index of the new page.
 */

UINT CPatronDoc::NewPage(void)
    {
    FDirtySet(TRUE);
    return m_pPG->PageInsert(0);
    }







/*
 * CPatronDoc::DeletePage
 *
 * Purpose:
 *  Deletes the current page from the document.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Index of the now current page.
 */

UINT CPatronDoc::DeletePage(void)
    {
    FDirtySet(TRUE);
    return m_pPG->PageDelete(0);
    }







/*
 * CPatronDoc::NextPage
 *
 * Purpose:
 *  Shows the next page in the pages window.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Index of the new page.
 */

UINT CPatronDoc::NextPage(void)
    {
    UINT        iPage;

    iPage=m_pPG->CurPageGet();
    return m_pPG->CurPageSet(++iPage);
    }







/*
 * CPatronDoc::PreviousPage
 *
 * Purpose:
 *  Shows the previous page in the pages window.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Index of the new page.
 */

UINT CPatronDoc::PreviousPage(void)
    {
    UINT        iPage;

    //If iPage is zero, then we wrap around to the end.
    iPage=m_pPG->CurPageGet();
    return m_pPG->CurPageSet(--iPage);
    }






/*
 * CPatronDoc::FirstPage
 *
 * Purpose:
 *  Shows the first page page in the pages window.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Index of the new page.
 */

UINT CPatronDoc::FirstPage(void)
    {
    return m_pPG->CurPageSet(0);
    }






/*
 * CPatronDoc::LastPage
 *
 * Purpose:
 *  Shows the last page in the pages window.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Index of the last page.
 */

UINT CPatronDoc::LastPage(void)
    {
    return m_pPG->CurPageSet(NOVALUE);
    }






//CHAPTER17MOD

/*
 * CPatronDoc::Rename
 *
 * Purpose:
 *  Overrides the normal rename to include notification of tenants
 *  in this document of the new name.  This is so embedded objects
 *  are told the correct name through IOleObject::SetHostNames.
 *
 * Parameters:
 *  pszFile         LPTSTR to the new filename.
 *
 * Return Value:
 *  None
 */

void CPatronDoc::Rename(LPTSTR pszFile)
    {
    //We don't need to change the base class, just augment...
    CDocument::Rename(pszFile);
    m_pPG->NotifyTenantsOfRename(pszFile, NULL);
    return;
    }





/*
 * CPatronDoc::InsertObject
 *
 * Purpose:
 *  Retrieves a CLSID or a filename from the Insert Object dialog
 *  box and creates an object using those identifiers.
 *
 * Parameters:
 *  hWndFrame       HWND of the main window
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPatronDoc::InsertObject(HWND hWndFrame)
    {
    OLEUIINSERTOBJECT   io;
    DWORD               dwData=0;
    TCHAR               szFile[CCHPATHMAX];
    UINT                uTemp;
    BOOL                fRet=FALSE;

    if (NULL==m_pPG)
        return FALSE;

    memset(&io, 0, sizeof(io));

    io.cbStruct=sizeof(io);
    io.hWndOwner=hWndFrame;

    szFile[0]=0;
    io.lpszFile=szFile;
    io.cchFile=CCHPATHMAX;

    io.dwFlags=IOF_SELECTCREATENEW | IOF_DISABLELINK;

    uTemp=OleUIInsertObject(&io);

    if (OLEUI_OK==uTemp)
        {
        TENANTTYPE      tType;
        LPVOID          pv;
        FORMATETC       fe;

        SETDefFormatEtc(fe, 0, TYMED_NULL);

        if (io.dwFlags & IOF_SELECTCREATENEW)
            {
            tType=TENANTTYPE_EMBEDDEDOBJECT;
            pv=&io.clsid;
            }
        else
            {
            tType=TENANTTYPE_EMBEDDEDFILE;
            pv=szFile;
            }

        if ((io.dwFlags & IOF_CHECKDISPLAYASICON)
            && NULL!=io.hMetaPict)
            {
            fe.dwAspect=DVASPECT_ICON;
            dwData=(DWORD)(UINT)io.hMetaPict;
            }

        fRet=m_pPG->TenantCreate(tType, pv, &fe, NULL, dwData);

        //Free this regardless of what we do with it.
        INOLE_MetafilePictIconFree(io.hMetaPict);

        if (fRet)
            {
            //Disable Printer Setup once we've created a tenant.
            m_fPrintSetup=FALSE;
            FDirtySet(TRUE);
            }
        }

    return fRet;
    }




/*
 * CPatronDoc::ActivateObject
 *
 * Purpose:
 *  Executes a verb on the currently selected object.
 *
 * Parameters:
 *  iVerb           LONG of the selected verb.
 *
 * Return Value:
 *  None
 */

void CPatronDoc::ActivateObject(LONG iVerb)
    {
    m_pPG->ActivateObject(iVerb);
    return;
    }


/*
 * CPatronDoc::ConvertObject
 *
 * Purpose:
 *  Invokes the Convert dialog on the current object.  Here it's
 *  just a pass-through to the pages.
 *
 * Parameters:
 *  hWndFrame       HWND of the frame window.
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful, FALSE otherwise.
 */

BOOL CPatronDoc::ConvertObject(HWND hWndFrame)
    {
    return m_pPG->ConvertObject(hWndFrame);
    }

//End CHAPTER17MOD
