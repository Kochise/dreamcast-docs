/*
 * COCOSMO.CPP
 * Component Cosmo Chapter 10
 *
 * WinMain and CCosmoFrame implementations.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "cocosmo.h"


/*
 * WinMain
 *
 * Purpose:
 *  Main entry point of application.  Should register the app class
 *  if a previous instance has not done so and do any other one-time
 *  initializations.
 */

int PASCAL WinMain (HINSTANCE hInst, HINSTANCE hPrev
    , LPSTR pszCmdLine, int nCmdShow)
    {
    PCCosmoFrame    pFR;
    FRAMEINIT       fi;
    WPARAM          wRet;

    //Attempt to allocate and initialize the application
    pFR=new CCosmoFrame(hInst, hPrev, pszCmdLine, nCmdShow);

    if (NULL==pFR)
        return -1;

    fi.idsMin=IDS_FRAMEMIN;
    fi.idsMax=IDS_FRAMEMAX;
    fi.idsStatMin=IDS_STATMESSAGEMIN;
    fi.idsStatMax=IDS_STATMESSAGEMAX;
    fi.idStatMenuMin=ID_MENUFILE;
    fi.idStatMenuMax=ID_MENUHELP;
    fi.iPosWindowMenu=WINDOW_MENU;
    fi.cMenus=CMENUS;

    fi.x=CW_USEDEFAULT;
    fi.y=CW_USEDEFAULT;
    fi.cx=440;
    fi.cy=460;

    //If we can initialize pFR, start chugging messages
    if (pFR->Init(&fi))
        wRet=pFR->MessageLoop();

    delete pFR;
    return wRet;
    }




/*
 * CCosmoFrame::CCosmoFrame
 * CCosmoFrame::~CCosmoFrame
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE from WinMain
 *  hInstPrev       HINSTANCE from WinMain
 *  pszCmdLine      LPSTR from WinMain
 *  nCmdShow        int from WInMain
 */

CCosmoFrame::CCosmoFrame(HINSTANCE hInst, HINSTANCE hInstPrev
    , LPSTR pszCmdLine, int nCmdShow)
    : CFrame(hInst, hInstPrev, pszCmdLine, nCmdShow)
    {
    UINT        i;

    for (i=0; i<5; i++)
        m_hBmpLines[i]=NULL;

    m_uIDCurLine=0;
    m_fInitialized=FALSE;
    return;
    }


CCosmoFrame::~CCosmoFrame(void)
    {
    UINT        i;

    for (i=0; i<5; i++)
        {
        if (NULL!=m_hBmpLines[i])
            DeleteObject(m_hBmpLines[i]);
        }

    if (m_fInitialized)
        CoUninitialize();

    return;
    }




/*
 * CCosmoFrame::Init
 *
 * Purpose:
 *  Call CoInitialize then calling down into the base class
 *  initialization.
 *
 * Parameters:
 *  pFI             PFRAMEINIT containing initialization
 *                  parameters.
 *
 * Return Value:
 *  BOOL            TRUE if initialization succeeded,
 *                  FALSE otherwise.
 */

BOOL CCosmoFrame::Init(PFRAMEINIT pFI)
    {
    CHECKVER_COM;

    if (FAILED(CoInitialize(NULL)))
        return FALSE;

    m_fInitialized=TRUE;

    return CFrame::Init(pFI);
    }






/*
 * CCosmoFrame::CreateCClient
 *
 * Purpose:
 *  Constructs a new client specific to the application.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  PCClient        Pointer to the new client object.
 */

PCClient CCosmoFrame::CreateCClient(void)
    {
    return (PCClient)(new CCosmoClient(m_hInst, this));
    }






/*
 * CCosmoFrame::RegisterAllClasses
 *
 * Purpose:
 *  Registers all classes used in this application.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if registration succeeded, FALSE otherwise.
 */

BOOL CCosmoFrame::RegisterAllClasses(void)
    {
    WNDCLASS        wc;

    //First let the standard frame do its thing
    if (!CFrame::RegisterAllClasses())
        return FALSE;

    /*
     * We want a different background color for the document
     * because the Polyline we put in the document will paint
     * with COLOR_WINDOW which by default which is CLASSLIB's
     * default document color.
     */

    GetClassInfo(m_hInst, SZCLASSDOCUMENT, &wc);
    UnregisterClass(SZCLASSDOCUMENT, m_hInst);

    wc.hbrBackground=(HBRUSH)(COLOR_APPWORKSPACE+1);

    if (!RegisterClass(&wc))
        return FALSE;

    //No need to register the Polyline window now...

    return TRUE;
    }



/*
 * CCosmoFrame::PreShowInit
 *
 * Purpose:
 *  Called from Init before intially showing the window.  We do
 *  whatever else we want here, modifying nCmdShow as necessary
 *  which affects ShowWindow in Init.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if this initialization succeeded,
 *                  FALSE otherwise.
 */

BOOL CCosmoFrame::PreShowInit(void)
    {
    CreateLineMenu();
    CheckLineSelection(IDM_LINESOLID);
    return TRUE;
    }






/*
 * CCosmoFrame::CreateLineMenu
 *
 * Purpose:
 *  Initializes the bitmaps used to create the Line menu and
 *  replaces the text items defined in the application resources
 *  with these bitmaps.  Note that the contents of m_hBmpLines
 *  must be cleaned up when the application terminates.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CCosmoFrame::CreateLineMenu(void)
    {
    HMENU       hMenu;
    HDC         hDC, hMemDC;
    HPEN        hPen;
    HGDIOBJ     hObj;
    TEXTMETRIC  tm;
    UINT        i, cx, cy;


    hMenu=GetSubMenu(GetMenu(m_hWnd), 3);   //Line menu.
    hDC=GetDC(m_hWnd);

    //Create each line in a menu item 8 chars wide, one char high.
    GetTextMetrics(hDC, &tm);
    cx=tm.tmAveCharWidth*8;
    cy=tm.tmHeight;

    /*
     * Create a memory DC in which to draw lines, and bitmaps
     * for each line.
     */
    hMemDC=CreateCompatibleDC(hDC);
    ReleaseDC(m_hWnd, hDC);

    for (i=0; i<5; i++)
        {
        m_hBmpLines[i]=CreateCompatibleBitmap(hMemDC, cx, cy);
        SelectObject(hMemDC, m_hBmpLines[i]);

        PatBlt(hMemDC, 0, 0, cx, cy, WHITENESS);

        hPen=CreatePen(i, 1, 0L);       //i=line style like PS_SOLID
        hObj=SelectObject(hMemDC, hPen);

        MoveToEx(hMemDC, 0, cy/2, NULL);
        LineTo(hMemDC, cx, cy/2);

        ModifyMenu(hMenu, IDM_LINEMIN+i, MF_BYCOMMAND | MF_BITMAP
            , IDM_LINEMIN+i, (LPTSTR)(LONG)(UINT)m_hBmpLines[i]);

        SelectObject(hMemDC, hObj);
        DeleteObject(hPen);
        }

    CheckMenuItem(hMenu, IDM_LINESOLID, MF_CHECKED);
    DeleteDC(hMemDC);

    return;
    }




/*
 * CCosmoFrame::CreateToolbar
 *
 * Purpose:
 *  Procedure to create all the necessary toolbar buttons.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Number of tools added to the bar.
 */

UINT CCosmoFrame::CreateToolbar(void)
    {
    UINT            iLast;
    UINT            uState=GIZMO_NORMAL;
    UINT            utCmd =GIZMOTYPE_BUTTONCOMMAND;
    UINT            utEx  =GIZMOTYPE_BUTTONATTRIBUTEEX;

    //Insert the standard ones.
    iLast=CFrame::CreateToolbar();

    /*
     * Insert File Import in the 5th position and account for
     * it in iLast.
     */
    m_pTB->Add(utCmd, 4, IDM_FILEIMPORT, m_dxB, m_dyB
        , NULL, m_hBmp, 2, uState);
    iLast++;

    //Separator
    m_pTB->Add(GIZMOTYPE_SEPARATOR, iLast++, 0, 6, m_dyB
        , NULL, NULL, 0, uState);

    /*
     * For the Background bitmap, preserve our use of black
     * (part of the image)
     */
    m_pTB->Add(utCmd, iLast++, IDM_COLORBACKGROUND, m_dxB, m_dyB
        , NULL, m_hBmp, 3, GIZMO_NORMAL | PRESERVE_BLACK);

    m_pTB->Add(utCmd, iLast++, IDM_COLORLINE, m_dxB, m_dyB
        , NULL, m_hBmp, 4, uState);

    //Separator
    m_pTB->Add(GIZMOTYPE_SEPARATOR, iLast++, 0, 6, m_dyB
        , NULL, NULL, 0, uState);

    //Line styles.
    m_pTB->Add(utEx, iLast++, IDM_LINESOLID, m_dxB, m_dyB
        , NULL, m_hBmp, 5, uState);
    m_pTB->Add(utEx, iLast++, IDM_LINEDASH, m_dxB, m_dyB
        , NULL, m_hBmp, 6, uState);
    m_pTB->Add(utEx, iLast++, IDM_LINEDOT, m_dxB, m_dyB
        , NULL, m_hBmp, 7, uState);
    m_pTB->Add(utEx, iLast++, IDM_LINEDASHDOT, m_dxB, m_dyB
        , NULL, m_hBmp, 8, uState);
    m_pTB->Add(utEx, iLast++, IDM_LINEDASHDOTDOT, m_dxB, m_dyB
        , NULL, m_hBmp, 9, uState);

    return iLast;
    }








/*
 * CCosmoFrame::OnCommand
 *
 * Purpose:
 *  WM_COMMAND handler for the Cosmo frame window that just
 *  processes the line menu and the color menu leaving the
 *  CFrame to do everything else.
 *
 * Parameters:
 *  hWnd            HWND of the frame window.
 *  wParam          WPARAM of the message.
 *  lParam          LPARAM of the message.
 *
 * Return Value:
 *  LRESULT         Return value for the message.
 */

LRESULT CCosmoFrame::OnCommand(HWND hWnd, WPARAM wParam
    , LPARAM lParam)
    {
    PCCosmoDoc      pDoc;
    TCHAR           szFile[CCHPATHMAX];
    BOOL            fOK;
    UINT            i, uTemp;
    COLORREF        rgColors[16];
    CHOOSECOLOR     cc;

    COMMANDPARAMS(wID, wCode, hWndMsg);

    /*
     * Don't bother with anything during first initialization,
     * skipping many toolbar notifications.
     */
    if (m_fInit)
        return 0L;

    pDoc=(PCCosmoDoc)m_pCL->ActiveDocument();

    /*
     * Check for the line style commands which are
     * IDM_LINEMIN+<style>.  We handle this by changing the menu
     * and toolbar, then we pass it to the document for real
     * processing.
     */
    if (NULL!=pDoc && IDM_LINEMIN <= wID && IDM_LINEMAX >=wID)
        {
        CheckLineSelection(wID);
        pDoc->LineStyleSet(wID-IDM_LINEMIN);
        return 0L;
        }

    switch (wID)
        {
        case IDM_FILEIMPORT:
            szFile[0]=0;
            fOK=SaveOpenDialog(szFile, CCHPATHMAX, IDS_FILEIMPORT
                , TRUE, &i);

            if (fOK)
                {
                uTemp=pDoc->Load(FALSE, szFile);
                pDoc->ErrorMessage(uTemp);
                }

            return (LRESULT)fOK;


        case IDM_COLORBACKGROUND:
        case IDM_COLORLINE:
            //Invoke the color chooser for either color
            uTemp=(IDM_COLORBACKGROUND==wID)
                ? DOCCOLOR_BACKGROUND : DOCCOLOR_LINE;

            for (i=0; i<16; i++)
                rgColors[i]=RGB(0, 0, i*16);

            memset(&cc, 0, sizeof(CHOOSECOLOR));
            cc.lStructSize=sizeof(CHOOSECOLOR);
            cc.lpCustColors=rgColors;
            cc.hwndOwner=hWnd;
            cc.Flags=CC_RGBINIT;
            cc.rgbResult=pDoc->ColorGet(uTemp);

            if (ChooseColor(&cc))
                pDoc->ColorSet(uTemp, cc.rgbResult);

            break;


        default:
           CFrame::OnCommand(hWnd, wParam, lParam);
        }

    return 0L;
    }






/*
 * CCosmoFrame::OnDocumentDataChange
 *
 * Purpose:
 *  Update the Line menu and toolbar if the style in the data
 *  changes.
 *
 * Parameters:
 *  pDoc            PCDocument notifying the sink.
 *
 * Return Value:
 *  None
 */

void CCosmoFrame::OnDocumentDataChange(PCDocument pDoc)
    {
    CheckLineSelection(IDM_LINEMIN
        +((PCCosmoDoc)pDoc)->LineStyleGet());
    return;
    }




/*
 * CCosmoFrame::OnDocumentActivate
 *
 * Purpose:
 *  Informs us that document activation changed, so update the UI
 *  for that new document.
 *
 * Parameters:
 *  pDoc            PCDocument notifying the sink.
 *
 * Return Value:
 *  None
 */

void CCosmoFrame::OnDocumentActivate(PCDocument pDoc)
    {
    CheckLineSelection(IDM_LINEMIN
        +((PCCosmoDoc)pDoc)->LineStyleGet());
    return;
    }







/*
 * CCosmoFrame::UpdateMenus
 *
 * Purpose:
 *  Handles the WM_INITMENU message for the frame window.  Depending
 *  on the existence of an active window, menu items are selectively
 *  enabled and disabled.
 *
 * Parameters:
 *  hMenu           HMENU of the menu to intialize
 *  iMenu           UINT position of the menu.
 *
 * Return Value:
 *  None
 */

void CCosmoFrame::UpdateMenus(HMENU hMenu, UINT iMenu)
    {
    PCDocument  pDoc;
    BOOL        fOK=FALSE;
    BOOL        fCallDefault=TRUE;
    UINT        i;
    UINT        uTemp;
    UINT        uTempE;
    UINT        uTempD;

    pDoc=m_pCL->ActiveDocument();

    uTempE=MF_ENABLED | MF_BYCOMMAND;
    uTempD=MF_DISABLED | MF_GRAYED | MF_BYCOMMAND;
    uTemp=((NULL!=pDoc) ? uTempE : uTempD);

    //File menu:  If there is document window, disable Import.
    if (m_phMenu[0]==hMenu)
        EnableMenuItem(hMenu, IDM_FILEIMPORT, uTemp);

    //Color menu:  no document, no commands
    if (m_phMenu[2]==hMenu)
        {
        EnableMenuItem(hMenu, IDM_COLORBACKGROUND, uTemp);
        EnableMenuItem(hMenu, IDM_COLORLINE,       uTemp);
        fCallDefault=FALSE;
        }

    //Line menu:  no document, no commands
    if (m_phMenu[3]==hMenu)
        {
        for (i=IDM_LINEMIN; i<=IDM_LINEMAX; i++)
            EnableMenuItem(hMenu, i, uTemp);

        fCallDefault=FALSE;
        }

    if (fCallDefault)
        CFrame::UpdateMenus(hMenu, iMenu);

    return;
    }






/*
 * CCosmoFrame::UpdateToolbar
 *
 * Purpose:
 *  Enables and disables tools depending on whether we have
 *  a document or not.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CCosmoFrame::UpdateToolbar(void)
    {
    BOOL        fLast;
    UINT        i;

    //Save the last enabled state before CFrame changes it
    fLast=m_fLastEnable;

    //Let the default hack on its tools
    CFrame::UpdateToolbar();

    /*
     * If CFrame::UpdateToolbar changed anything, then we need
     * to change as well--if nothing changes, nothing to do.
     */
    if (fLast!=m_fLastEnable)
        {
        m_pTB->Enable(IDM_FILEIMPORT, m_fLastEnable);

        m_pTB->Enable(IDM_COLORBACKGROUND, m_fLastEnable);
        m_pTB->Enable(IDM_COLORLINE,       m_fLastEnable);

        for (i=IDM_LINEMIN; i <= IDM_LINEMAX; i++)
            m_pTB->Enable(i, m_fLastEnable);
        }

    return;
    }






/*
 * CCosmoFrame::CheckLineSelection
 *
 * Purpose:
 *  Maintains the bitmap menu and the tools for the line selection.
 *  Both are mutially exclusive option lists where a selection in
 *  one has to affect the other.
 *
 * Parameters:
 *  uID             UINT ID of the item to be selected
 *
 * Return Value:
 *  None
 */

void CCosmoFrame::CheckLineSelection(UINT uID)
    {
    UINT        i;
    HMENU       hMenu;

    //Update menus and tools if the selection changed.
    if (uID!=m_uIDCurLine)
        {
        m_uIDCurLine=uID;
        hMenu=GetMenu(m_hWnd);

        //Uncheck all lines initially.
        for (i=IDM_LINEMIN; i<=IDM_LINEMAX; i++)
            CheckMenuItem(hMenu, i, MF_UNCHECKED | MF_BYCOMMAND);

        CheckMenuItem(hMenu, uID, MF_CHECKED | MF_BYCOMMAND);
        m_pTB->Check(uID, TRUE);
        }

    return;
    }
