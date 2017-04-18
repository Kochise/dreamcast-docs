/*
 * AUTOFIG.CPP
 * Cosmo Chapter 14
 *
 * "Figure" object for Cosmo's OLE Automation support, derived
 * from CAutoBase.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved.
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  INTERNET>kraigb@microsoft.com
 */


#include "cosmo.h"


/*
 * CAutoFigure::CAutoFigure
 * CAutoFigure::~CAutoFigure
 *
 * Constructor Parameters:
 *  pDoc            PCCosmoDoc to the dpcument object that we
 *                  use to implement much of this interface.
 */

CAutoFigure::CAutoFigure(PCCosmoDoc pDoc)
    : CAutoBase(pDoc, pDoc->m_hInst, IID_ICosmoFigure
    , DIID_DICosmoFigure, ObjectDestroyed)
    {
    return;
    }


/*
 * CAutoFigure::QueryInterface
 * CAutoFigure::AddRef
 * CAutoFigure::Release
 */

STDMETHODIMP CAutoFigure::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_ICosmoFigure==riid)
        *ppv=(IUnknown *)this;

    if (IID_IDispatch==riid || m_diid==riid)
        *ppv=m_pImpIDispatch;

    if (IID_IExternalConnection==riid)
        *ppv=m_pImpIExtConn;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }

STDMETHODIMP_(ULONG) CAutoFigure::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CAutoFigure::Release(void)
    {
    /*
     * Since this object might have come from a class factory,
     * we count it's existence (see NewFigure below) for
     * controlling shutdown of the application when we call
     * ObjectDestroyed.  Otherwise we always close the document.
     */
    if (0L!=--m_cRef)
        return m_cRef;

    put_Visible(FALSE);
    SendMessage(m_pDoc->Window(), WM_CLOSE, 0, 0L);

    if (NULL!=m_pfnDestroy)
        (*m_pfnDestroy)();

    return 0L;
    }


/*
 * CAutoFigure::VTableInterface
 *
 * Purpose:
 *  Returns the right vtable pointer to use when calling
 *  ITypeInfo::Invoke (see CImpIDispatch::Invoke in AUTOBASE.CPP).
 */
void *CAutoFigure::VTableInterface(void)
    {
    return (ICosmoFigure *)this;
    }



//All that follows is the ICosmoFigure implementation

/*
 * CAutoFigure::Application
 * CAutoFigure::Parent
 * Properties, read-only
 *
 * The application object (CAutoApp) in which we're contained,
 * which is stored in the frame object
 */

STDMETHODIMP_(IDispatch *) CAutoFigure::get_Application(void)
    {
    PCCosmoFrame    pFR;

    pFR=(PCCosmoFrame)m_pDoc->m_pFR;
    return pFR->AutoApp()->get_Application();
    }

STDMETHODIMP_(IDispatch *) CAutoFigure::get_Parent(void)
    {
    return get_Application();
    }


/*
 * CAutoFigure::FullName, Name, Path
 * Properties, read-only
 *
 * Retrieve the full pathname of the figure file (FullName),
 * just the file name (Name), or just the path (Path).
 *
 * Note that these functions are very similar to the same
 * ones in CAutoApp, and there is probably some code that could
 * be shared between them, but this sample won't bother with
 * such an optimization.
 */

STDMETHODIMP_(BSTR) CAutoFigure::get_FullName(void)
    {
    if ((TCHAR)0==m_pDoc->m_szFile[0])
        return NULL;

   #ifdef WIN32ANSI
    OLECHAR     szTemp[512];

    MultiByteToWideChar(CP_ACP, 0, m_pDoc->m_szFile, -1, szTemp, 512);
    return SysAllocString(szTemp);
   #else
    return SysAllocString(m_pDoc->m_szFile);
   #endif
    }

STDMETHODIMP_(BSTR) CAutoFigure::get_Name(void)
    {
    BSTR        bstrFull=NULL;
    BSTR        bstrName=NULL;
    const int   cch=256;
    TCHAR       szName[256];

    //Get the full path
    bstrFull=get_FullName();

    if (NULL==bstrFull)
        return NULL;

    //Now retrieve just the filename
   #ifdef WIN32ANSI
    char        szTemp[cch];
    OLECHAR     szTempW[cch];

    WideCharToMultiByte(CP_ACP, 0, bstrFull, -1, szTemp
        , cch, NULL, NULL);
    if (0==GetFileTitle(szTemp, szName, cch))
        {
        MultiByteToWideChar(CP_ACP, 0, szName, -1, szTempW, cch);
        bstrName=SysAllocString(szTempW);
        }
   #else
    if (0==GetFileTitle(bstrFull, szName, cch))
        bstrName=SysAllocString(szName);
   #endif

    SysFreeString(bstrFull);
    return bstrName;
    }

STDMETHODIMP_(BSTR) CAutoFigure::get_Path(void)
    {
    BSTR        bstrFull=NULL;
    BSTR        bstrName=NULL;
    BSTR        bstrPath=NULL;

    bstrFull=get_FullName();

    if (NULL==bstrFull)
        return NULL;

    bstrName=get_Name();

    if (NULL!=bstrName)
        {
        LPOLESTR    psz;

        /*
         * Find the position of bstrName in bstrFull then copy
         * only charaters up to that point into bstrPath.
         */
       #ifdef WIN32ANSI
        psz=wcsstr(bstrFull, bstrName);
       #else
        psz=_tcsstr(bstrFull, bstrName);
       #endif

        //The -1 accounts for the \ before the filename
        bstrPath=SysAllocStringLen(bstrFull
            , ((psz-bstrFull)/sizeof(TCHAR))-1);
        SysFreeString(bstrName);
        }

    SysFreeString(bstrFull);
    return bstrPath;
    }


/*
 * CAutoFigure::Saved
 * Property, read-only
 *
 * TRUE if the document is clean, FALSE otherwise.
 */

STDMETHODIMP_(VARIANT_BOOL) CAutoFigure::get_Saved(void)
    {
    return !m_pDoc->FDirtyGet();
    }


/*
 * CAutoFigure::NumberOfPoints
 * Property, read-only
 *
 * Number of points in the current figure.
 */

STDMETHODIMP_(short)CAutoFigure::get_NumberOfPoints(void)
    {
    POLYLINEDATA    pl;

    m_pDoc->m_pPL->DataGet(&pl, VERSIONCURRENT);
    return pl.cPoints;
    }


/*
 * CAutoFigure::BackColor
 * CAutoFigure::LineColor
 * Properties, read-write
 *
 * Colors used in the figure.
 */

STDMETHODIMP_(long) CAutoFigure::get_BackColor(void)
    {
    return m_pDoc->ColorGet(POLYLINECOLOR_BACKGROUND);
    }

STDMETHODIMP_(void) CAutoFigure::put_BackColor(long clrBack)
    {
    m_pDoc->ColorSet(POLYLINECOLOR_BACKGROUND, clrBack);
    return;
    }

STDMETHODIMP_(long) CAutoFigure::get_LineColor(void)
    {
    return m_pDoc->ColorGet(POLYLINECOLOR_LINE);
    }

STDMETHODIMP_(void) CAutoFigure::put_LineColor(long clrLine)
    {
    m_pDoc->ColorSet(POLYLINECOLOR_LINE, clrLine);
    return;
    }


/*
 * CAutoFigure::LineStyle
 * Property, read-write
 *
 * Line style used to draw the figure
 */

STDMETHODIMP_(short)CAutoFigure::get_LineStyle(void)
    {
    return m_pDoc->LineStyleGet();
    }

STDMETHODIMP_(void) CAutoFigure::put_LineStyle(short iStyle)
    {
    m_pDoc->LineStyleSet(iStyle);
    return;
    }


/*
 * CAutoFigure::Left, Top, Width, Height
 * Properties, read-write
 *
 * Horizontal (Left) and vertical (Top) positions of the frame
 * window from the left and top edges of the application client
 * area; horizontal (Width) and vertical (Height) dimensions of
 * document window.  All of these functions call our private member
 * MoveSize, a helper function.
 */

STDMETHODIMP_(long) CAutoFigure::get_Left(void)
    {
    return MoveSize(MOVESIZEACTION_GETLEFT, 0, 0, 0, 0);
    }

STDMETHODIMP_(void) CAutoFigure::put_Left(long x)
    {
    MoveSize(MOVESIZEACTION_LEFT, x, 0, 0, 0);
    return;
    }

STDMETHODIMP_(long) CAutoFigure::get_Top(void)
    {
    return MoveSize(MOVESIZEACTION_GETTOP, 0, 0, 0, 0);
    }

STDMETHODIMP_(void) CAutoFigure::put_Top(long y)
    {
    MoveSize(MOVESIZEACTION_TOP, 0, y, 0, 0);
    return;
    }

STDMETHODIMP_(long) CAutoFigure::get_Width(void)
    {
    return MoveSize(MOVESIZEACTION_GETWIDTH, 0, 0, 0, 0);
    }

STDMETHODIMP_(void) CAutoFigure::put_Width(long cx)
    {
    MoveSize(MOVESIZEACTION_WIDTH, 0, 0, cx, 0);
    return;
    }

STDMETHODIMP_(long) CAutoFigure::get_Height(void)
    {
    return MoveSize(MOVESIZEACTION_GETHEIGHT, 0, 0, 0, 0);
    }

STDMETHODIMP_(void) CAutoFigure::put_Height(long cy)
    {
    MoveSize(MOVESIZEACTION_HEIGHT, 0, 0, 0, cy);
    return;
    }



/*
 * CAutoFigure::Visible
 * Properties, read-write
 *
 * Controls visibility of the figure window (which is hidden by
 * default when created through automation).
 */

STDMETHODIMP_(VARIANT_BOOL)  CAutoFigure::get_Visible(void)
    {
    return (VARIANT_BOOL)IsWindowVisible(m_pDoc->Window());
    }

STDMETHODIMP_(void) CAutoFigure::put_Visible(VARIANT_BOOL fShow)
    {
    ShowWindow(m_pDoc->Window(), fShow ? SW_SHOW : SW_HIDE);
    return;
    }


/*
 * CAutoFigure::Activate
 * Method
 *
 * Activate this window, that is, bring it to the foreground
 */

STDMETHODIMP_(void) CAutoFigure::Activate(void)
    {
    HWND        hWndDoc;

    hWndDoc=m_pDoc->Window();
    SendMessage(GetParent(hWndDoc), WM_MDIACTIVATE
        , (WPARAM)hWndDoc, 0L);
    return;
    }



/*
 * CAutoFigure::Close
 * Method
 *
 * Closes this document.
 *
 * Parameters (optional)
 *  fSaveChanges        BOOL that indicates if we're to save
 *                      changes or not.  If not, then we just nuke
 *                      the figure.
 *  bstrPath            BSTR with the filename into which to save
 *                      the figure if fSaveChanges is TRUE.  Note that
 *                      this overrides any other pathname we are
 *                      already using.
 */

STDMETHODIMP_(void) CAutoFigure::Close(VARIANT varSave
    , VARIANT varPath)
    {
    //If we got varSave and it's TRUE, then save
    if (VT_ERROR!=varSave.vt && varSave.boolVal)
        {
        /*
         * If we got a filename, call SaveAs.  Otherwise
         * call Save.  If we don't have a filename for
         * Save, then Save just fails and we don't have
         * to care.
         */
        if (VT_ERROR!=varPath.vt)
            SaveAs(varPath.bstrVal);
        else
            Save();
        }

    //Hiding the document first suppresses any UI on closure.
    put_Visible(FALSE);
    SendMessage(m_pDoc->Window(), WM_CLOSE, 0, 0L);
    return;
    }



/*
 * CAutoFigure::RevertToSaved
 * Method
 *
 * Reloads the contents of the document from the saved state.
 */

STDMETHODIMP_(void) CAutoFigure::RevertToSaved(void)
    {
    //Can't do this if we don't have a file
    if ((TCHAR)0==m_pDoc->m_szFile[0])
        return;

    /*
     * Since we "open" a document by loading it and closing
     * it, then we can just "re-open" it with Load again.
     */
    m_pDoc->Load(FALSE, m_pDoc->m_szFile);

    /*
     * Load set the document as dirt when loading from a file
     * in this manner (the behavior of Import).  But this actually
     * makes the file clean, so we change the dirty flag here.
     */
    m_pDoc->FDirtySet(FALSE);
    return;
    }



/*
 * CAutoFigure::Save
 * Method
 *
 * Saves the document to a known file if one exists.
 */

STDMETHODIMP_(void) CAutoFigure::Save(void)
    {
    if ((TCHAR)0==m_pDoc->m_szFile[0])
        return;

    m_pDoc->Save(0, (LPTSTR)NULL);
    return;
    }



/*
 * CAutoFigure::SaveAs
 * Method
 *
 * Saves the current figure to a new file.
 */

STDMETHODIMP_(void) CAutoFigure::SaveAs(BSTR bstrPath)
    {
    if (NULL==bstrPath)
        return;

    //This also renames the document
   #ifdef WIN32ANSI
    char        szTemp[512];

    WideCharToMultiByte(CP_ACP, 0, bstrPath, -1, szTemp
        , 512, NULL, NULL);
    m_pDoc->Save(0, szTemp);
   #else
    m_pDoc->Save(0, bstrPath);
   #endif
    return;
    }



/*
 * CAutoFigure::Import
 * Method
 *
 * Initializes the figure from the contents of a file
 */

STDMETHODIMP_(void) CAutoFigure::Import(BSTR bstrImportPath)
    {
    if (NULL==bstrImportPath)
        return;

    /*
     * Like we have for RevertToSaved, we can just "open"
     * this file and the new information becomes current.
     */
   #ifdef WIN32ANSI
    char        szTemp[512];

    WideCharToMultiByte(CP_ACP, 0, bstrImportPath, -1
        , szTemp, 512, NULL, NULL);
    m_pDoc->Load(FALSE, szTemp);
   #else
    m_pDoc->Load(FALSE, bstrImportPath);
   #endif
    return;
    }



/*
 * CAutoFigure::Copy
 * CAutoFigure::Cut
 * CAutoFigure::Paste
 * Methods
 *
 * Perform clipboard operations
 */

STDMETHODIMP_(void) CAutoFigure::Copy(void)
    {
    m_pDoc->Clip(m_pDoc->m_pFR->Window(), FALSE);
    return;
    }

STDMETHODIMP_(void) CAutoFigure::Cut(void)
    {
    m_pDoc->Clip(m_pDoc->m_pFR->Window(), TRUE);
    return;
    }

STDMETHODIMP_(void) CAutoFigure::Paste(void)
    {
    if (m_pDoc->FQueryPaste())
        m_pDoc->Paste(m_pDoc->m_pFR->Window());

    return;
    }




/*
 * CAutoFigure::AddPoint
 * Method
 *
 * Adds a new point, expressed on a 0-32767 scale, to the figure.
 */

STDMETHODIMP_(VARIANT_BOOL) CAutoFigure::AddPoint(short x, short y)
    {
    RECT        rc;
    POINTS      pt;
    HWND        hWndPL;

    /*
     * This is the only semi-tricky method to implement here because
     * normally this processing is done inside the Polyline's
     * WM_LBUTTONDOWN.  In order to get the same behavior, we'll
     * just send the same message to it.  However, we have to
     * convert from a 0-32767 range to a window coordinate range
     * which is nicely handled by CPolyline::PointScale (the only
     * small modification to CPolyline I had to make was to make
     * PointScale public instead of private).
     *
     * This is a non-invasive way to add Automation support.
     * The invasive way would require a change to the CPolyline
     * class and it's window procedure so both this function
     * and the WM_LBUTTONDOWN handling called the same function
     * with 0-32767 scaled points.
     */

    //See if we can add any more
    if (CPOLYLINEPOINTS==get_NumberOfPoints())
        return FALSE;

    hWndPL=m_pDoc->m_pPL->Window();
    GetClientRect(hWndPL, &rc);
    SETPOINT(pt, x, y);
    m_pDoc->m_pPL->PointScale(&rc, &pt, TRUE);
    SendMessage(hWndPL, WM_LBUTTONDOWN, 0, MAKELPARAM(pt.x, pt.y));
    return TRUE;
    }



/*
 * CAutoFigure::RemovePoint
 * Method
 *
 * Removes the last point added to a figure
 */

STDMETHODIMP_(void) CAutoFigure::RemovePoint(void)
    {
    m_pDoc->Undo();
    return;
    }




/*
 * CAutoFigure::MoveSize
 *
 * Purpose:
 *  Helper function for the Left, Top, Width, and Height properties
 *  that centralizes calls to GetWindowRect and SetWindowPos,
 *  reducing overall code somewhat.
 *
 * Parameters:
 *  iAction         MOVESIZEACTION enum value to indicate what
 *                  type of moving/sizing to perform
 *  x, y            long position coordinates;  x is only meaningful
 *                  with MOVESIZEACTION_LEFT, y only with _TOP
 *  cx, cy          long extents;  cx is only meaningful
 *                  with MOVESIZEACTION_WIDTH, cy only with _HEIGHT
 *
 * Return Value:
 *  long            The current x, y, cx, or cy value depending on
 *                  iAction being _GETLEFT, _GETTOP, _GETWIDTH, or
 *                  _GETHEIGHT.
 */

long CAutoFigure::MoveSize(MOVESIZEACTION iAction, long x, long y
    , long cx, long cy)
    {
    RECT        rc;
    POINT       pt1, pt2;
    long        x1, y1, cx1, cy1;
    UINT        uFlags;

    GetWindowRect(m_pDoc->Window(), &rc);
    SETPOINT(pt1, rc.left, rc.top);
    ScreenToClient(GetParent(m_pDoc->Window()), &pt1);
    SETPOINT(pt2, rc.right, rc.bottom);
    ScreenToClient(GetParent(m_pDoc->Window()), &pt2);

    //By default we'll do nothing
    x1=pt1.x;
    y1=pt1.y;
    cx1=pt2.x-pt1.x;
    cy1=pt2.y-pt1.y;
    uFlags=0L;

    switch (iAction)
        {
        /*
         * Each individual property modifies the appropriate
         * variable x1, y1, cx1, cy1, as well as uFlags to set
         * up SetWindowPos call.
         */
        case MOVESIZEACTION_LEFT:
            x1=x;
            uFlags=SWP_NOSIZE;
            break;

        case MOVESIZEACTION_TOP:
            y1=y;
            uFlags=SWP_NOSIZE;
            break;

        case MOVESIZEACTION_WIDTH:
            cx1=cx;
            uFlags=SWP_NOMOVE;
            break;

        case MOVESIZEACTION_HEIGHT:
            cy1=cy;
            uFlags=SWP_NOMOVE;
            break;


        case MOVESIZEACTION_GETLEFT:
            return x1;

        case MOVESIZEACTION_GETTOP:
            return y1;

        case MOVESIZEACTION_GETWIDTH:
            return cx1;

        case MOVESIZEACTION_GETHEIGHT:
            return cy1;

        default:
            return 0;
        }

    //We only get here on propety changes
    SetWindowPos(m_pDoc->Window(), NULL
        , (int)x1, (int)y1, (int)cx1, (int)cy1
        , SWP_NOZORDER | SWP_NOACTIVATE | uFlags);

    //Irrelevant for property changes.
    return 0;
    }
