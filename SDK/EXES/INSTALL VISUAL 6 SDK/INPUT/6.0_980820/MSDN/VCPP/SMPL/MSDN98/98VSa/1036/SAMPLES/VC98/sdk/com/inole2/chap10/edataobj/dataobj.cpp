/*
 * DATAOBJ.CPP
 * Data Object Chapter 19
 *
 * Implementation of CDataObject and CImpIDataObject that work
 * in either an EXE or DLL.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "dataobj.h"

extern HINSTANCE   g_hInst;

DWORD              g_dwID=0;

//Names of data sizes
static TCHAR * rgszSize[3]={TEXT("Small"), TEXT("Medium")
    , TEXT("Large")};



/*
 * CDataObject::CDataObject
 * CDataObject::~CDataObject
 *
 * Parameters (Constructor):
 *  pUnkOuter       LPUNKNOWN of controlling unknown, if it exists.
 *  pfnDestroy      PFNDESTROYED to call when object is destroyed.
 *  iSize           UINT specifying the size of the data set to use.
 */

CDataObject::CDataObject(LPUNKNOWN pUnkOuter
    , PFNDESTROYED pfnDestroy, UINT iSize)
    {
    UINT        i;

    m_cRef=0;
    m_pUnkOuter=pUnkOuter;
    m_pfnDestroy=pfnDestroy;
    m_iSize=iSize;

    m_hWndAdvise=NULL;
    m_dwAdvFlags=ADVF_NODATA;

    //NULL any contained interfaces initially.
    m_pImpIDataObject=NULL;
    m_pIDataAdviseHolder=NULL;

    //Initilize the FORMATETCs arrays we use for EnumFormatEtc
    m_cfeGet=CFORMATETCGET;

    SETDefFormatEtc(m_rgfeGet[0], CF_METAFILEPICT, TYMED_MFPICT);
    SETDefFormatEtc(m_rgfeGet[1], CF_BITMAP, TYMED_GDI);
    SETDefFormatEtc(m_rgfeGet[2], CF_TEXT, TYMED_HGLOBAL);

    for (i=0; i < DOSIZE_CSIZES; i++)
        m_rghBmp[i]=NULL;

    return;
    }


CDataObject::~CDataObject(void)
    {
    UINT        i;

    for (i=0; i < DOSIZE_CSIZES; i++)
        {
        if (NULL!=m_rghBmp[i])
            DeleteObject(m_rghBmp[i]);
        }

    ReleaseInterface(m_pIDataAdviseHolder);
    DeleteInterfaceImp(m_pImpIDataObject);

    if (NULL!=m_hWndAdvise)
        DestroyWindow(m_hWndAdvise);

    return;
    }



/*
 * CDataObject::Init
 *
 * Purpose:
 *  Performs any intiailization of a CDataObject that's prone to
 *  failure that we also use internally before exposing the
 *  object outside.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful,
 *                  FALSE otherwise.
 */

BOOL CDataObject::Init(void)
    {
    LPUNKNOWN       pIUnknown=this;
    UINT            i;
    TCHAR           szTemp[80];
    UINT            cy;

    if (NULL!=m_pUnkOuter)
        pIUnknown=m_pUnkOuter;

    //Allocate contained interfaces.
    m_pImpIDataObject=new CImpIDataObject(this, pIUnknown);

    if (NULL==m_pImpIDataObject)
        return FALSE;

    for (i=0; i < DOSIZE_CSIZES; i++)
        {
        m_rghBmp[i]=LoadBitmap(g_hInst, MAKEINTRESOURCE(i+IDB_MIN));

        if (NULL==m_rghBmp[i])
            return FALSE;
        }


    /*
     * Register the Advise window class first time through
     * (g_dwID==0)
     */

    if (0L==g_dwID)
        {
        WNDCLASS    wc;

        wc.style          = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc    = AdvisorWndProc;
        wc.cbClsExtra     = 0;
        wc.cbWndExtra     = sizeof(PCDataObject);
        wc.hInstance      = g_hInst;
        wc.hIcon          = LoadIcon(g_hInst
            , MAKEINTRESOURCE(IDR_ADVISORICON));
        wc.hCursor        = NULL;
        wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU);
        wc.lpszClassName  = TEXT("Advisor");

        if (!RegisterClass(&wc))
            return FALSE;
        }

    /*
     * Create an advise window with a unique caption:
     * "<size> <module> Advisor #xx" where <size> is Small,
     * Medium, or Large, <module> is EXE or DLL, and xx is
     * counted globally every time a CDataObject is created.
     */

    g_dwID++;
   #ifdef EXEDATAOBJECT
    wsprintf(szTemp, TEXT("%s EXE Advisor #%lu")
        , (LPTSTR)rgszSize[m_iSize], g_dwID);
   #else
    wsprintf(szTemp, TEXT("%s DLL Advisor #%lu")
        , (LPTSTR)rgszSize[m_iSize], g_dwID);
   #endif

    cy=(GetSystemMetrics(SM_CYBORDER)*2)+GetSystemMetrics(SM_CYMENU)
        + GetSystemMetrics(SM_CYCAPTION);

    m_hWndAdvise=CreateWindow(TEXT("Advisor"), szTemp
        , WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_BORDER
        | WS_VISIBLE, 400, 35+(g_dwID*(cy+30)), 200, cy
        , HWND_DESKTOP, NULL, g_hInst, this);

    if (NULL==m_hWndAdvise)
        return FALSE;

    return TRUE;
    }





/*
 * CDataObject::QueryInterface
 * CDataObject::AddRef
 * CDataObject::Release
 *
 * Purpose:
 *  IUnknown members for CDataObject object.
 */

STDMETHODIMP CDataObject::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid)
        *ppv=this;

    if (IID_IDataObject==riid)
        *ppv=m_pImpIDataObject;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CDataObject::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CDataObject::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    if (NULL!=m_pfnDestroy)
        (*m_pfnDestroy)();

    delete this;
    return 0;
    }





/*
 * AdvisorWndProc
 *
 * Purpose:
 *  Standard window class procedure.
 */

LRESULT APIENTRY AdvisorWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PCDataObject    pDO;
    DWORD           i;
    DWORD           iAdvise;
    DWORD           dwTime;
    DWORD           dwAvg;
    TCHAR           szTime[128];
    TCHAR           szTitle[80];
    HCURSOR         hCur, hCurT;

    pDO=(PCDataObject)GetWindowLong(hWnd, 0);

    switch (iMsg)
        {
        case WM_NCCREATE:
            pDO=(PCDataObject)(((LPCREATESTRUCT)lParam)
                ->lpCreateParams);
            SetWindowLong(hWnd, 0, (LONG)pDO);
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));

        case WM_CLOSE:
            //Forbid task manager from closing us.
            return 0L;

        case WM_COMMAND:
            if (NULL==pDO->m_pIDataAdviseHolder)
                break;

            //Send IAdviseSink::OnDataChange many times.
            i=(DWORD)(LOWORD(wParam)-IDM_ADVISEITERATIONSMIN+1);
            iAdvise=(i*i)*16;

            hCur=LoadCursor(NULL, MAKEINTRESOURCE(IDC_WAIT));
            hCurT=SetCursor(hCur);
            ShowCursor(TRUE);

            dwTime=GetTickCount();

            i=0;
            while (TRUE)
                {
               #ifdef EXEDATAOBJECT
               #ifndef WIN32
                MSG     msg;

                if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                    {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                    }
                else
               #endif
               #endif
                    {
                    pDO->m_pIDataAdviseHolder->SendOnDataChange
                        (pDO->m_pImpIDataObject, 0, ADVF_NODATA);

                    if (++i >= iAdvise)
                        break;
                    }
                }

            dwTime=GetTickCount()-dwTime;
            dwAvg=dwTime/iAdvise;

            SetCursor(hCurT);
            ShowCursor(FALSE);

            wsprintf(szTime
                , TEXT("Total=%lu ms\n\rAverage=%lu ms")
                , dwTime, dwAvg);

            GetWindowText(hWnd, szTitle, sizeof(szTitle));
            MessageBox(hWnd, szTime, szTitle, MB_OK);
            break;

        default:
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));
        }

    return 0L;
    }
