/*
 * FRAMER.CPP
 * Document Objects Framer
 *
 * Sample to demonstrate in-place activation of a DocObject--also
 * activates normal embeddings in separate windows.
 *
 * Copyright (c)1995-1997 Microsoft Corporation, All Rights Reserved
 */


#define INITGUID
#include "framer.h"


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
    PCFrame         pFR;    
    WPARAM          wRet;

    //Attempt to allocate and initialize the application
    pFR=new CFrame(hInst, hPrev, pszCmdLine, nCmdShow);

    if (NULL==pFR)
        return 0;
    
    //If we can initialize pFR, start chugging messages
    if (pFR->Init(CMENUS, CW_USEDEFAULT, CW_USEDEFAULT
        , CW_USEDEFAULT, CW_USEDEFAULT))
        wRet=pFR->MessageLoop();

    delete pFR;
    return wRet;
    }



/*
 * CFrame::CFrame
 * CFrame::~CFrame
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE from WinMain
 *  hInstPrev       HINSTANCE from WinMain
 *  pszCmdLine      LPSTR from WinMain
 *  nCmdShow        int from WinMain
 */

CFrame::CFrame(HINSTANCE hInst, HINSTANCE hInstPrev
    , LPSTR pszCmdLine, int nCmdShow)    
    {
    m_hInst=hInst;
    m_hWnd=NULL;
    m_hInstPrev=hInstPrev;
    m_nCmdShow=nCmdShow;

    m_phMenu=NULL;
    m_hAccel=NULL;
    m_hWndClient=NULL;

    m_fInitialized=FALSE;
    m_pIStorage=NULL;
    m_dwIDCounter=0;

    m_hMenuOrg=NULL;
    m_hMenuTop=NULL;
	m_hMenuHelp=NULL;
	m_fInObjectHelp=FALSE;
	m_fUsingOurHelp=FALSE;
		    
    m_fHaveObject=FALSE;
	m_hWndObj=NULL;

    m_pSite=NULL;
    m_fOurMenuShowing=TRUE;
    SetRect(&m_bwIP, 0, 0, 0, 0);
    m_fInContextHelp=FALSE;
    m_pIOleIPActiveObject=NULL;

    return;
    }



CFrame::~CFrame(void)
    {
    if (NULL!=m_hWndClient)
        DestroyWindow(m_hWndClient);
	
    //Frees the temp file.
    ReleaseInterface(m_pIStorage);
    
    //m_pSite cleaned up in Close

    //Accelerators freed automatically.

	//Destroy the special help menu
	if (NULL!=m_hMenuHelp)
		DestroyMenu(m_hMenuHelp);

    //Free the menu handle array
    if (NULL!=m_phMenu)
        delete []((UINT *)m_phMenu);

    if (m_fInitialized)
        OleUninitialize();

    return;
    }


/*
 * CFrame::Init
 *
 * Purpose:
 *  Initializer for a CFrame object containing anything prone to
 *  failure.
 *
 * Parameters:
 *  cMenus          UINT number of menus on the frame
 *  x, y, cx, cy    int location and size of frame window 
 *
 * Return Value:
 *  BOOL            TRUE if initialization succeeded, FALSE
 *                  otherwise. If FALSE is returned, the caller must
 *                  guarantee that the destructor is called promptly
 *                  to insure cleanup.
 */

BOOL CFrame::Init(UINT cMenus, int x, int y, int cx, int cy)
    {
    HMENU               hMenu;
    UINT                uTemp;
    RECT                rc;

    //1.  Initialize OLE
    if (SUCCEEDED(OleInitialize(NULL)))
        m_fInitialized=TRUE;
    else
        return FALSE;


    //2.  Register window classes
    if (NULL==m_hInstPrev)
        {
        if (!RegisterAllClasses())
            return FALSE;
        }


    //3.  Create the main window and client-area window
    m_hWnd=CreateWindow(SZCLASSFRAME, TEXT("DocObject Framer")
        , WS_MINIMIZEBOX | WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN
        , x, y, cx, cy, NULL, NULL, m_hInst, this);
        
    if (NULL==m_hWnd)
        return FALSE;

    GetClientRect(m_hWnd, &rc);

    m_hWndClient=CreateWindow(SZCLASSCLIENT, SZCLASSCLIENT
        , WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE | WS_CLIPSIBLINGS
        , rc.left, rc.top, rc.right-rc.left
        , rc.bottom-rc.top, m_hWnd, NULL, m_hInst, this);

    if (NULL==m_hWndClient)
        return FALSE;

    //4. Allocate menu array for use with in-place menu merging.
    m_phMenu=new HMENU[cMenus];
    hMenu=GetMenu(m_hWnd);
    m_hMenuOrg=hMenu;

    for (uTemp=0; uTemp < cMenus; uTemp++)
        m_phMenu[uTemp]=GetSubMenu(hMenu, uTemp);

	//Also load the special help menu
	m_hMenuHelp=LoadMenu(m_hInst
		, MAKEINTRESOURCE(IDR_MENUHELP));

    //5.  Load accelerators
    m_hAccel=LoadAccelerators(m_hInst
        , MAKEINTRESOURCE(IDR_ACCELERATORS));

    if (NULL==m_hAccel)
        return FALSE;


    //6.  Make us all visible.
    ShowWindow(m_hWnd, m_nCmdShow);
    UpdateWindow(m_hWnd);


    /*
     * 7.  Create a temp file for all embedded files.  Note that in this
     *     sample we don't save any changes to DocObjects because we 
	 *     don't manage any storage directly.
	 */	  
    if (FAILED(StgCreateDocfile(NULL, STGM_TRANSACTED | STGM_READWRITE
        | STGM_SHARE_EXCLUSIVE | STGM_CREATE| STGM_DELETEONRELEASE
        , 0, &m_pIStorage)))
        return FALSE;

    return TRUE;
    }





/*
 * CFrame::RegisterAllClasses
 *
 * Purpose:
 *  Registers all classes used in this application.
 *
 * Return Value:
 *  BOOL            TRUE if registration succeeded, FALSE otherwise.
 */

BOOL CFrame::RegisterAllClasses(void)
    {
    WNDCLASS        wc;

    //Field that are the same for all windows.
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance     = m_hInst;
    wc.cbClsExtra    = 0;

    //Register the Frame window
    wc.lpfnWndProc   = FrameWndProc;
    wc.cbWndExtra    = CBFRAMEWNDEXTRA;
    wc.hIcon         = LoadIcon(m_hInst, TEXT("Icon"));
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU);
    wc.lpszClassName = SZCLASSFRAME;

    if (!RegisterClass(&wc))
        return FALSE;


    //Register the do-nothing Client window
    wc.lpfnWndProc   = ClientWndProc;
    wc.cbWndExtra    = CBCLIENTWNDEXTRA;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = SZCLASSCLIENT;

    if (!RegisterClass(&wc))
        return FALSE;

    return TRUE;
    }




/*
 * CFrame::OnCommand
 *
 * Purpose:
 *  WM_COMMAND handler for the frame window so derivations can
 *  process their messages and then pass the standard commands (like
 *  file open and save) on to the base class.
 *
 * Parameters:
 *  hWnd            HWND of the frame window.
 *  wParam          WPARAM of the message.
 *  lParam          LPARAM of the message.
 *
 * Return Value:
 *  LRESULT         Return value for the message.
 */

LRESULT CFrame::OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
    {
    TCHAR           szFile[MAX_PATH];
    BOOL            fOK;
    PCHourglass     pHour;
    WORD            wID=LOWORD(wParam);

    switch (wID)
        {
        case IDM_FILEOPEN:
            /*
             * This will be disabled if we already have an object.
             * User must File/Close first to get back here. 
             *
             * Otherwise open the File/Open dialog
             */
            szFile[0]=0;
            if (!OpenDialog(szFile, MAX_PATH))
                return 0L;
                
            pHour=new CHourglass;            
            fOK=CreateObject(szFile);
            delete pHour;
            return 0;


        case IDM_FILECLOSE:
            Close();
            break;


        case IDM_FILEEXIT:
            PostMessage(hWnd, WM_CLOSE, 0, 0L);            
            break;


        case IDM_HELPABOUT:
            DialogBox(m_hInst, MAKEINTRESOURCE(IDD_ABOUT)
                , m_hWnd, (DLGPROC)AboutProc);
            break;


        case IDM_ENTERCONTEXTHELP:
        case IDM_ESCAPECONTEXTHELP:
            //Notify the object on entry and exit.
            ContextSensitiveHelp(IDM_ENTERCONTEXTHELP==wID);
            break;


        default:
           return DefWindowProc(hWnd, WM_COMMAND, wParam, lParam);
               
        }

    return 0L;
    }





/*
 * CFrame::OpenDialog
 *
 * Purpose:
 *  Invokes the COMMDLG.DLL GetOpenFileName dialog and retrieves
 *  a filename for saving or opening.
 *
 * Parameters:
 *  pszFile         LPTSTR buffer to receive the entered filename.
 *  cchFile         UINT length of pszFile 
 *
 * Return Value:
 *  BOOL            TRUE if the function retrieved a filename,
 *                  FALSE if the user pressed CANCEL.
 */

BOOL CFrame::OpenDialog(LPTSTR pszFile, UINT cchFile)
    {
    OPENFILENAME        ofn;
    static TCHAR        szFilter[80]=TEXT("All Files (*.*)\0*.*\0\0");
    BOOL                fRet;
   #ifdef DEBUG
    DWORD               dwErr;
   #endif

    if (NULL==pszFile)
        return FALSE;

    memset(&ofn, 0, sizeof(OPENFILENAME));
    ofn.lStructSize      =sizeof(OPENFILENAME);
    ofn.hwndOwner        =m_hWnd;

    ofn.lpstrFilter      =szFilter;
    ofn.nFilterIndex     =1L;

    ofn.lpstrTitle       =NULL;
    ofn.lpstrFile        =pszFile;
    ofn.nMaxFile         =cchFile;

    ofn.lpstrDefExt      =TEXT("*");
    ofn.Flags            =OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;

    fRet=GetOpenFileName(&ofn);
    
   #ifdef DEBUG
    dwErr=CommDlgExtendedError();
   #endif
    return fRet;
    }



/*
 * CFrame::CreateObject
 *
 * Purpose:
 *  Creates a site and has it create an object based on a filename.
 *
 * Parameters:
 *  pszFile         LPTSTR pointing to the filename from which to
 *                  create the object.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CFrame::CreateObject(LPTSTR pszFile)
    {    
    m_pSite=new CSite(++m_dwIDCounter, m_hWndClient, this);

    if (NULL==m_pSite)
        return FALSE;

    m_pSite->AddRef();  //So we can free with Release

    /*
     * Now tell the site to create an object in it using the filename
     * and the storage we opened.  The site will create a sub-storage
     * for the doc object's use.
     */
    if (!m_pSite->Create(pszFile, m_pIStorage))
        return FALSE;

    m_fHaveObject=TRUE;

    //We created the thing, now activate it with "Show"
    m_pSite->Activate(OLEIVERB_SHOW);

	//Force repaint to show "have object" message
	InvalidateRect(m_hWndClient, NULL, TRUE);
	UpdateWindow(m_hWndClient);
    return TRUE;        
    }



/*
 * CFrame::Close
 *
 * Purpose:
 *  Handles File/Close by freeing the object and resetting the
 *  application state.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CFrame::Close(void)
    {    
	RECT	rc;

    if (NULL!=m_pSite)
        {
		CSite *pSite=m_pSite;        //Prevents reentry
		m_pSite=NULL;

        pSite->Close(FALSE);         //Frees the object
        pSite->Destroy(m_pIStorage); //Cleans up the storage
        pSite->Release();            //Frees the site        
        }
    
	m_fHaveObject=FALSE;	
    SetRect(&m_bwIP, 0, 0, 0, 0);	

	GetClientRect(m_hWnd, &rc);	
	ResizeClientWindow(rc.left, rc.top, rc.right-rc.left
		, rc.bottom-rc.top);	

	//Force repaint to remove "have object" message
	InvalidateRect(m_hWndClient, NULL, TRUE);
	UpdateWindow(m_hWndClient);
    
    return;        
    }


/*
 * CFrame::ResizeClientWindow
 *
 * Purpose:
 *	Resizes the client-area window according to current toolbar sizes
 *  and the frame window size.
 *
 * Parameters:
 *	x,y,cx,cy		UINT origin and dimensions of the window
 *
 * Return Value:
 *	None
 */

void CFrame::ResizeClientWindow(UINT x, UINT y, UINT cx, UINT cy)
	{
	SetWindowPos(m_hWndClient, NULL, x, y, cx, cy    	
        , SWP_NOZORDER | SWP_NOACTIVATE);

    //Tell the site to tell the object.
	if (NULL!=m_pSite)
    	m_pSite->UpdateObjectRects();

	return;
	}


/*
 * CFrame::MessageLoop
 *
 * Purpose:
 *  Spins in a standard message loop (with accelerators) until
 *  WM_QUIT is found after which it returns.
 *
 * Return Value:
 *  WPARAM          Contents of msg.wParam from WM_QUIT.
 */

WPARAM CFrame::MessageLoop(void)
    {
    MSG     msg;

    while (GetMessage(&msg, NULL, 0,0 ))
        {
        //Always give the object first crack at translation.
        if (NULL!=m_pIOleIPActiveObject)
            {
            HRESULT     hr;

            hr=m_pIOleIPActiveObject->TranslateAccelerator(&msg);

            //If the object translated the accelerator, we're done
            if (NOERROR==hr)
                continue;
            }

        if (!::TranslateAccelerator(m_hWnd, m_hAccel, &msg))
            {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            }
        }

    return msg.wParam;
    }



/*
 * FrameWndProc
 *
 * Purpose:
 *  Frame window class procedure that allows a derivation of these
 *  classes to hook and process any messages desired.  Otherwise this
 *  handles standard commands as well as the status line and menus.
 */

LRESULT APIENTRY FrameWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PCFrame         pFR;
    RECT            rc;
    HMENU           hMenu;

    pFR=(PCFrame)GetWindowLong(hWnd, FRAMEWL_STRUCTURE);

    switch (iMsg)
        {
        case WM_NCCREATE:
            pFR=(PCFrame)((LPCREATESTRUCT)lParam)->lpCreateParams;

            SetWindowLong(hWnd, FRAMEWL_STRUCTURE, (LONG)pFR);
            return DefWindowProc(hWnd, iMsg, wParam, lParam);

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_CLOSE:                        
            pFR->Close();
            DestroyWindow(hWnd);
            break;

        case WM_ERASEBKGND:
            //Client area window always manages painting
            return FALSE;

        case WM_SIZE:
            //Tell the in-place object about the new frame size
            GetClientRect(hWnd, &rc);

            if (NULL!=pFR->m_pIOleIPActiveObject)
                pFR->m_pIOleIPActiveObject->ResizeBorder(&rc, pFR, TRUE);
					
            /*
             * Resize the client, which is done in all cases since this window
			 * is the parent of the DocObject, plus we need to tell the 
			 * DocObject of the new size through IOleDocumentView::SetRect.
			 */
            rc.left  +=pFR->m_bwIP.left;
            rc.right -=pFR->m_bwIP.right;
            rc.top   +=pFR->m_bwIP.top;
            rc.bottom-=pFR->m_bwIP.bottom;            

			pFR->ResizeClientWindow(rc.left, rc.top, rc.right-rc.left
				, rc.bottom-rc.top);
			
            break;


        case WM_SETFOCUS:
            if (NULL!=pFR->m_pIOleIPActiveObject)
                {
                HWND    hWndObj;

                pFR->m_pIOleIPActiveObject->GetWindow(&hWndObj);
                SetFocus(hWndObj);
                }

            return TRUE;


		case WM_INITMENU:
			pFR->m_fInObjectHelp=FALSE;
			break;


		case WM_MENUSELECT:
				{
 				UINT fuFlags=(UINT)HIWORD(wParam);
 				UINT uItem=(UINT)LOWORD(wParam);

				if (MF_POPUP & fuFlags)
					{
					/*
					 * If we're inside our m_hMenuHelp, and uItem is
					 * not zero (first item on the menu, which is ours),
					 * then we must be in an object-supplied menu.
					 *
					 * Therefore we set our flag and forward the message
					 * as well as others that occur later.  Otherwise we
					 * clear the flag so we get messages again.
					 */				
					if (NULL!=pFR->m_hMenuHelp
						&& (HMENU)lParam==pFR->m_hMenuHelp)					
						{
						pFR->m_fInObjectHelp=(0!=uItem);
				
						if (pFR->m_fInObjectHelp)
							SendMessage(pFR->m_hWndObj, iMsg, wParam, lParam);
						}				
					}
				else
					{
					//Forward the message on
					if (pFR->m_fInObjectHelp)
						{
						SendMessage(pFR->m_hWndObj, iMsg, wParam, lParam);
						break;
						}
					}		
				}
			break;

		case WM_INITMENUPOPUP:
			/*
			 * If we're in the object's Help menu, forward to
			 * the object received in IOleInPlaceFrame::SetActiveObject
			 */
			if (pFR->m_fInObjectHelp && NULL!=pFR->m_hWndObj) 
				SendMessage(pFR->m_hWndObj, iMsg, wParam, lParam);


			//Skip the system menu
            if (TRUE==(BOOL)HIWORD(lParam))
                break;

		    /*
             * If we have an object, enable Close, otherwise
             * enable Open.
             */
            hMenu=(HMENU)wParam;

            if (hMenu==pFR->m_phMenu[0])
                {
                UINT uTempE=MF_BYCOMMAND | MF_ENABLED;
                UINT uTempD=MF_BYCOMMAND | MF_DISABLED | MF_GRAYED;

                EnableMenuItem(hMenu, IDM_FILEOPEN
                    , pFR->m_fHaveObject ? uTempD : uTempE);
                EnableMenuItem(hMenu, IDM_FILECLOSE
                    , pFR->m_fHaveObject ? uTempE : uTempD);
                }
            
            break;

        case WM_COMMAND:
			if (pFR->m_fInObjectHelp)
				{
				SendMessage(pFR->m_hWndObj, iMsg, wParam, lParam);
				break;
				}
			else
            	return pFR->OnCommand(hWnd, wParam, lParam);

		case WM_ACTIVATEAPP:
			if (NULL!=pFR->m_pIOleIPActiveObject)
				{
				HRESULT hr;
				hr=pFR->m_pIOleIPActiveObject->OnFrameWindowActivate((BOOL)wParam);
				}
			break;

        default:
            return DefWindowProc(hWnd, iMsg, wParam, lParam);
        }

    return 0L;
    }



/*
 * ClientWndProc
 *
 * Purpose:
 *  Client window class procedure that's only used to paint a
 *  message when we have a non-DocObject open.  Otherwise this
 *  is completely hidden.
 */

LRESULT APIENTRY ClientWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PCFrame         pFR;
	PAINTSTRUCT		ps;

    pFR=(PCFrame)GetWindowLong(hWnd, CLIENTWL_STRUCTURE);

    switch (iMsg)
        {
        case WM_NCCREATE:
            pFR=(PCFrame)((LPCREATESTRUCT)lParam)->lpCreateParams;

            SetWindowLong(hWnd, CLIENTWL_STRUCTURE, (LONG)pFR);
            return DefWindowProc(hWnd, iMsg, wParam, lParam);

        case WM_PAINT:
			BeginPaint(hWnd, &ps);

			if (pFR->m_fHaveObject)
				{
				static TCHAR szMsg[]={TEXT("A non-DocObject is open or loaded. Use File/Close to destroy it.")};

				SetBkColor(ps.hdc, GetSysColor(COLOR_WINDOW));
				TextOut(ps.hdc, 0, 0, szMsg, lstrlen(szMsg));
				}

			EndPaint(hWnd, &ps);
            break;

        default:
            return DefWindowProc(hWnd, iMsg, wParam, lParam);
        }

    return 0L;
    }





/*
 * AboutProc
 *
 * Purpose:
 *  Dialog procedure for the omnipresent About box.
 *
 * Parameters:
 *  The standard.
 *
 * Return Value:
 *  The value to be returned through the DialogBox call that
 *  created the dialog.
 *
 */

BOOL APIENTRY AboutProc(HWND hDlg, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    switch (iMsg)
        {
        case WM_INITDIALOG:
            return TRUE;

        case WM_COMMAND:
            switch (LOWORD(wParam))
                {
                case IDOK:
                    EndDialog(hDlg, TRUE);
                }
            break;
        }
    return FALSE;
    }









/*
 * IUnknown implementation
 */


/*
 * CFrame::QueryInterface
 * CFrame::AddRef
 * CFrame::Release
 */

STDMETHODIMP CFrame::QueryInterface(REFIID riid, void **ppv)
    {
    /*
     * We only know IOleInPlaceFrame and its base interfaces as well
     * as a bogus IOleCommandTarget to make PowerPoint happy.
	 */
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IOleInPlaceUIWindow==riid
        || IID_IOleWindow==riid || IID_IOleInPlaceFrame==riid)
        *ppv=(IOleInPlaceFrame *)this;

	if (IID_IOleCommandTarget==riid)
        *ppv=(IOleCommandTarget *)this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return E_NOINTERFACE;
    }


STDMETHODIMP_(ULONG) CFrame::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CFrame::Release(void)
    {
    //Nothing special happening here--frame's life if user-controlled.
    return --m_cRef;
    }


/*
 * IOleInPlaceFrame implementation
 */


/*
 * CFrame::GetWindow
 *
 * Purpose:
 *  Retrieves the handle of the window associated with the object
 *  on which this interface is implemented.
 *
 * Parameters:
 *  phWnd           HWND * in which to store the window handle.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, E_FAIL if there is no
 *                  window.
 */

STDMETHODIMP CFrame::GetWindow(HWND *phWnd)
    {
    *phWnd=m_hWnd;
    return NOERROR;
    }




/*
 * CFrame::ContextSensitiveHelp
 *
 * Purpose:
 *  Instructs the object on which this interface is implemented to
 *  enter or leave a context-sensitive help mode.
 *
 * Parameters:
 *  fEnterMode      BOOL TRUE to enter the mode, FALSE otherwise.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CFrame::ContextSensitiveHelp(BOOL fEnterMode)
    {
    /*
     * Don't bother if there is no active object since we don't do
     * context help on our own.
     */
    if (NULL==m_pIOleIPActiveObject)
        return NOERROR;

    //If the state changes, notify the active object.
    if (m_fInContextHelp!=fEnterMode)
        {
        m_fInContextHelp=fEnterMode;
        m_pIOleIPActiveObject->ContextSensitiveHelp(fEnterMode);
        }

    return NOERROR;
    }




/*
 * CFrame::GetBorder
 *
 * Purpose:
 *  Returns the rectangle in which the container is willing to
 *  negotiate about an object's adornments.
 *
 * Parameters:
 *  prcBorder       LPRECT in which to store the rectangle.
 *
 * Return Value:
 *  HRESULT         NOERROR if all is well, INPLACE_E_NOTOOLSPACE
 *                  if there is no negotiable space.
 */

STDMETHODIMP CFrame::GetBorder(LPRECT prcBorder)
    {
    if (NULL==prcBorder)
        return E_INVALIDARG;

    //We return all the client area space
    GetClientRect(m_hWnd, prcBorder);
    return NOERROR;
    }




/*
 * CFrame::RequestBorderSpace
 *
 * Purpose:
 *  Asks the container if it can surrender the amount of space
 *  in pBW that the object would like for it's adornments.  The
 *  container does nothing but validate the spaces on this call.
 *
 * Parameters:
 *  pBW             LPCBORDERWIDTHS containing the requested space.
 *                  The values are the amount of space requested
 *                  from each side of the relevant window.
 *
 * Return Value:
 *  HRESULT         NOERROR if we can give up space,
 *                  INPLACE_E_NOTOOLSPACE otherwise.
 */

STDMETHODIMP CFrame::RequestBorderSpace(LPCBORDERWIDTHS pBW)
    {
    //Framer has no border space restrictions
    return NOERROR;
    }




/*
 * CFrame::SetBorderSpace
 *
 * Purpose:
 *  Called when the object now officially requests that the
 *  container surrender border space it previously allowed
 *  in RequestBorderSpace.  The container should resize windows
 *  appropriately to surrender this space.
 *
 * Parameters:
 *  pBW             LPCBORDERWIDTHS containing the amount of space
 *                  from each side of the relevant window that the
 *                  object is now reserving.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CFrame::SetBorderSpace(LPCBORDERWIDTHS pBW)
    {
    RECT            rc;

    /*
     * Since we have no tools, we can accept anything the object sends
     * and must therefore adjust the client-area window accordingly.
     */

    /*
     * If pBW is NULL, the object is not interested in tools, so we
     * don't have to do anything.  In either case we need to save
     * the toolspace allocations in order to resize the client window
     * correctly.
     */
    if (NULL==pBW)
        {
        if (!m_fOurMenuShowing)
            SetMenu(NULL, NULL, NULL);

        SetRect(&m_bwIP, 0, 0, 0, 0);
        GetClientRect( m_hWnd, &rc );
        }
    else
        {
        GetClientRect(m_hWnd, &rc);
        rc.left  +=pBW->left;
        rc.right -=pBW->right;
        rc.top   +=pBW->top;
        rc.bottom-=pBW->bottom;

        m_bwIP=*pBW;
        }

	ResizeClientWindow(rc.left, rc.top, rc.right-rc.left
		, rc.bottom-rc.top);
	
    return NOERROR;
    }




/*
 * CFrame::SetActiveObject
 *
 * Purpose:
 *  Provides the container with the object's IOleInPlaceActiveObject
 *  pointer
 *
 * Parameters:
 *  pIIPActiveObj   LPOLEINPLACEACTIVEOBJECT of interest.
 *  pszObj          LPCOLESTR naming the object.  Not used.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CFrame::SetActiveObject
    (LPOLEINPLACEACTIVEOBJECT pIIPActiveObj, LPCOLESTR pszObj)
    {
    if (NULL!=m_pIOleIPActiveObject)
        m_pIOleIPActiveObject->Release();

    //NULLs m_pIOleIPActiveObject if pIIPActiveObj is NULL
    m_pIOleIPActiveObject=pIIPActiveObj;

    if (NULL!=m_pIOleIPActiveObject)
        m_pIOleIPActiveObject->AddRef();

	m_pIOleIPActiveObject->GetWindow(&m_hWndObj);
    return NOERROR;
    }




/*
 * CFrame::InsertMenus
 *
 * Purpose:
 *  Instructs the container to place its in-place menu items where
 *  necessary in the given menu and to fill in elements 0, 2, and 4
 *  of the OLEMENUGROUPWIDTHS array to indicate how many top-level
 *  items are in each group.
 *
 * Parameters:
 *  hMenu           HMENU in which to add popups.
 *  pMGW            LPOLEMENUGROUPWIDTHS in which to store the
 *                  width of each container menu group.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CFrame::InsertMenus(HMENU hMenu
    , LPOLEMENUGROUPWIDTHS pMGW)
    {    
	//Copy our File menu into the shared menu.    
    InsertMenu(hMenu, 0, MF_BYPOSITION | MF_POPUP, (UINT)m_phMenu[0]
        , TEXT("&File"));

    pMGW->width[0]=1;
    pMGW->width[2]=0;
    pMGW->width[4]=0;

	/*
	 * Add the special help menu which is the first item in
	 * the m_hMenuHelp popup that's sitting around.
	 */
	InsertMenu(hMenu, 1, MF_BYPOSITION | MF_POPUP
	    , (UINT)m_hMenuHelp, TEXT("&Help"));

	//Tell the object we added our Help menu
	pMGW->width[5]=1;    
    return NOERROR;
    }




/*
 * CFrame::SetMenu
 *
 * Purpose:
 *  Instructs the container to replace whatever menu it's currently
 *  using with the given menu and to call OleSetMenuDescritor so OLE
 *  knows to whom to dispatch messages.
 *
 * Parameters:
 *  hMenu           HMENU to show.
 *  hOLEMenu        HOLEMENU to the menu descriptor.
 *  hWndObj         HWND of the active object to which messages are
 *                  dispatched.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CFrame::SetMenu(HMENU hMenu, HOLEMENU hOLEMenu
    , HWND hWndObj)
    {
    HRESULT         hr;

    /*
     * Our responsibilities here are to put the menu on the frame
     * window and call OleSetMenuDescriptor.
     */

    if (NULL==hMenu)
        {
        //Prevent redundant calls, or debug warnings on startup.
        if (NULL==m_hMenuTop)
            return NOERROR;

        hMenu=m_hMenuTop;
        m_hMenuTop=NULL;
        m_fOurMenuShowing=TRUE;
        }
    else
        {
        m_hMenuTop=m_hMenuOrg;
        m_fOurMenuShowing=FALSE;

		/*
		 * Check if our Help menu has anything added to it.  If so, then
		 * remember to forward menu messages.  If not, remove the Help
		 * menu altogether (destroying it after removing our normal Help
		 * popup, as we also do in RemoveMenus.
		 */
		if (CHELPITEMS!=GetMenuItemCount(m_hMenuHelp))
			m_fUsingOurHelp=TRUE;
		else
			{			
			UINT	i, cItems;
				
			cItems=GetMenuItemCount(hMenu);			

			//Find m_hMenuHelp in the menu and remove it.
			for (i=0; i < cItems; i++)
				{
				if (GetSubMenu(hMenu, i)==m_hMenuHelp)
					{
					RemoveMenu(hMenu, i, MF_BYPOSITION);
					break;
					}
				}							
			}			
        }

    if (NULL!=hMenu)
        ::SetMenu(m_hWnd, hMenu);

    DrawMenuBar(m_hWnd);

    hr=OleSetMenuDescriptor(hOLEMenu, m_hWnd, hWndObj, NULL, NULL);
    return hr;
    }




/*
 * CFrame::RemoveMenus
 *
 * Purpose:
 *  Asks the container to remove any menus it put into hMenu in
 *  InsertMenus.
 *
 * Parameters:
 *  hMenu           HMENU from which to remove the container's
 *                  items.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CFrame::RemoveMenus(HMENU hMenu)
    {
    int         cItems, i, j;
    HMENU       hMenuT;

	/*
     * To be defensive, loop through this menu removing anything
     * we recognize (that is, anything in m_phMenu) just in case
     * the server didn't clean it up right.  At least we can
     * give ourselves the prophylactic benefit.
     */

    if (NULL==hMenu)
        return NOERROR;

    cItems=GetMenuItemCount(hMenu);

    /*
     * Walk backwards down the menu.  For each popup, see if it
     * matches any other popup we know about, and if so, remove
     * it from the shared menu.
     */
    for (i=cItems; i >=0; i--)
        {
        hMenuT=GetSubMenu(hMenu, i);

        for (j=0; j <= CMENUS; j++)
            {
			//Remove any owned popup, or our special help menu
            if (hMenuT==m_phMenu[j]
                || (hMenuT==m_hMenuHelp && m_hMenuHelp!=NULL))
                RemoveMenu(hMenu, i, MF_BYPOSITION);
            }
        }
	
	m_fUsingOurHelp=FALSE;

    //The menu should now be empty.
    return NOERROR;
    }




/*
 * CFrame::SetStatusText
 *
 * Purpose:
 *  Asks the container to place some text in a status line, if one
 *  exists.  If the container does not have a status line it
 *  should return E_FAIL here in which case the object could
 *  display its own.
 *
 * Parameters:
 *  pszText         LPCOLESTR to display.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, S_TRUNCATED if not all
 *                  of the text could be displayed, or E_FAIL if
 *                  the container has no status line.
 */

STDMETHODIMP CFrame::SetStatusText(LPCOLESTR pszText)
    {
    //We have no status line...
    return E_NOTIMPL;
    }



/*
 * CFrame::EnableModeless
 *
 * Purpose:
 *  Instructs the container to show or hide any modeless popup
 *  windows that it may be using.
 *
 * Parameters:
 *  fEnable         BOOL indicating to enable/show the windows
 *                  (TRUE) or to hide them (FALSE).
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CFrame::EnableModeless(BOOL fEnable)
    {
    return NOERROR;
    }




/*
 * CFrame::TranslateAccelerator
 *
 * Purpose:
 *  When dealing with an in-place object from an EXE server, this
 *  is called to give the container a chance to process accelerators
 *  after the server has looked at the message.
 *
 * Parameters:
 *  pMSG            LPMSG for the container to examine.
 *  wID             WORD the identifier in the container's
 *                  accelerator table (from IOleInPlaceSite
 *                  ::GetWindowContext) for this message (OLE does
 *                  some translation before calling).
 *
 * Return Value:
 *  HRESULT         NOERROR if the keystroke was used,
 *                  S_FALSE otherwise.
 */

STDMETHODIMP CFrame::TranslateAccelerator(LPMSG pMSG, WORD wID)
    {
    /*
     * wID already has anything translated from m_hAccel for us,
     * so we can just check for the commands we want and process
     * them instead of calling TranslateAccelerator which would be
     * redundant and which also has a possibility of dispatching to
     * the wrong window.
     */
    if (IDM_ENTERCONTEXTHELP==wID || IDM_ESCAPECONTEXTHELP==wID)
        {
        //wID properly expands to 32-bits
        OnCommand(m_hWnd, (WPARAM)wID, 0L);
        return NOERROR;
        }

    return S_FALSE;
    }


/*
 * IOleCommandTarget methods, provided to make PowerPoint happy
 * with this frame.
 */

STDMETHODIMP CFrame::QueryStatus(const GUID *pguidCmdGroup, ULONG cCmds
    , OLECMD *prgCmds, OLECMDTEXT *pCmdText)
	{
	return OLECMDERR_E_UNKNOWNGROUP;
	}
        
STDMETHODIMP CFrame::Exec(const GUID *pguidCmdGroup, DWORD nCmdID
    , DWORD nCmdexecopt, VARIANTARG *pvaIn, VARIANTARG *pvaOut)
	{
	return OLECMDERR_E_UNKNOWNGROUP;
	}
    
