//+--------------------------------------------------------
// File:        App.cxx
//
// Classes:     CController
//
// Functions:   WinMain
//              WndProc
//              MakeWindowClass
//              AboutDlgProc
//				PropDlgProc
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------

#include <windows.h>
#include <windowsx.h>
#include "app.hxx"

// global for use by PropDlgProc
CCTypeSet * pCSet = NULL;


//+--------------------------------------------------------
// Class:       CController
//
// Purpose:     Controlling the application, UI handler
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------

void CController::Create(HWND hwnd, LONG lParam )
{
    HANDLE handle = ((LPCREATESTRUCT) lParam)->hInstance;
    _hInst = (HINSTANCE)handle;
    _funAbout = (DLGPROC) MakeProcInstance((FARPROC)AboutDlgProc, _hInst);
	_funProp = (DLGPROC) MakeProcInstance((FARPROC) PropDlgProc, _hInst );

    // Set up the Main View
    _pView = new CScrollableView(((LPCREATESTRUCT) lParam)->cx,
                                ((LPCREATESTRUCT) lParam)->cy);
    _pView->SetScale(100);

    SetScrollRange(hwnd, SB_VERT, 0, PAGEHEIGHT, FALSE);
    SetScrollRange(hwnd, SB_HORZ, 0, PAGEWIDTH, FALSE);

    SetScrollPos(hwnd, SB_HORZ, 0, TRUE );
    SetScrollPos(hwnd, SB_VERT, 0, TRUE );

    // Set up the Model
    _pModel= new CModel(_hInst, hwnd, HEXADECIMAL, USEDONLY);

    // Set up the initial state of the Menu
    Page(hwnd, IDM_FIRSTPAGE);

    // initially no pop-up character box
    _pBox = 0;
}

void CController::Destroy()
{

    FreeProcInstance((FARPROC)AboutDlgProc);

    delete _pView;
    delete _pModel;
    PostQuitMessage(0);
}

void CController::Size ( LONG lParam )
{
   _pView->SetSize ( LOWORD(lParam), HIWORD(lParam) );
}

// Message Box with text from resource file
void CController::AlertBox( HWND hwnd, UINT idsText, UINT fuStyle)
{
    TCHAR szText[100];
    TCHAR szCaption[100];

    LoadString(_hInst, idsText, (LPTSTR)szText, 100);
    LoadString(_hInst, IDS_MSGCAPTION, (LPTSTR)szCaption, 100);

    ::MessageBox (hwnd, (LPTSTR)szText, (LPTSTR)szCaption, fuStyle) ;
};

// Menu commands processing

void CController::Command ( HWND hwnd, WPARAM wID )
{
    switch ( wID )
    {
      // File Menu
      case IDM_PRINT:
           {
                CPrintRequest job(hwnd, 1, _pModel->GetMaxPage());

                if(!job.Cancelled() && !job.Error())
                {
                    CPrintCanvas canvas (job);
                    job.Print (_hInst, canvas, _pModel);
                    
                    if(job.Error())
                    {
                        AlertBox (hwnd, IDS_PRINTERR, MB_OK | MB_ICONEXCLAMATION) ;
                    }
                }
           }
           break;
      case IDM_EXIT:
           SendMessage ( hwnd, WM_CLOSE, 0L, 0L );
           break;

      // View Menu
      case IDM_NEXTPAGE:
           Page(hwnd, IDM_NEXTPAGE);
           break;
      case IDM_PREVPAGE:
           Page(hwnd, IDM_PREVPAGE);
           break;
      case IDM_NEXTSECTION:
           Page(hwnd, IDM_NEXTSECTION);
           break;
      case IDM_PREVSECTION:
           Page(hwnd, IDM_PREVSECTION);
           break;
      case IDM_ZOOMIN:
           {
               UINT iScale;
               _pView->GetScale(iScale);
               iScale -= (iScale > 50 ? 25 : 0);
               _pView->SetScale(iScale);
               _pView->Invalidate(hwnd);
           }
           break;
      case IDM_ZOOMOUT:
           {
               UINT iScale;
               _pView->GetScale(iScale);
               iScale += (iScale < 200 ? 25 : 0);
               _pView->SetScale(iScale);
               _pView->Invalidate(hwnd);
           }
           break;

      // Options Menu
      case IDM_FONT:
           _pModel->ChooseFont(hwnd);
           _pView->Invalidate(hwnd);
           break;
     case IDM_DECIMAL:
           {
               UINT fuFormat;
               _pModel->GetFormat(fuFormat);
               fuFormat ^= DECIMAL;
               CheckMenuItem (GetMenu(hwnd), IDM_DECIMAL, 
                        fuFormat & DECIMAL ? MF_CHECKED : MF_UNCHECKED ) ;
              _pModel->SetFormat(fuFormat);
           }
           _pView->Invalidate(hwnd);
           break;
      case IDM_ALLPAGES:
           {
               UINT fPageMode;
               _pModel->GetPageMode(fPageMode);
               fPageMode ^= ALLPAGES;
               CheckMenuItem (GetMenu(hwnd), IDM_ALLPAGES, 
                        fPageMode & ALLPAGES ? MF_CHECKED : MF_UNCHECKED ) ;
               _pModel->SetPageMode(fPageMode);
           }
           _pView->Invalidate(hwnd);
           break;

	  case IDM_SHOWPROP:
	  	   {	
		   		DialogBox( _hInst, TEXT("PROPERTIES"),hwnd, _funProp );	
		   		_pModel->SetCSet(pCSet);	
		   }
           _pView->Invalidate(hwnd);
		   break;

      // Help Menu
      case IDM_HELP:
           AlertBox ( hwnd, IDS_NOTIMPLEM, MB_ICONINFORMATION | MB_OK);
           break;
      case IDM_ABOUT:
           DialogBox ( _hInst, TEXT("AboutBox"), hwnd, _funAbout );
           break;
     }
}

void CController::Page(HWND hwnd, WPARAM wParam)
{
    UINT iPage = _pModel->GetPage();
    switch (wParam)
    {
    case IDM_PREVPAGE: 
        _pModel->PrevPage();
        break;  
    case IDM_NEXTPAGE:
        _pModel->NextPage();
        break;  
    case IDM_NEXTSECTION:
        _pModel->NextSection();
        break;
    case IDM_PREVSECTION:
        _pModel->PrevSection();
        break;
    case IDM_FIRSTPAGE:
        _pModel->SetPage( 0 );
        break;  
    case IDM_LASTPAGE:
        _pModel->SetPage( _pModel->GetMaxPage() -1 );
        break;  
    }
    if (iPage != _pModel->GetPage())
    {   
        _pView->Invalidate(hwnd);
    }
    HMENU hmenu = GetMenu(hwnd);

    EnableMenuItem (hmenu, IDM_PREVPAGE, _pModel->CanPrevPage()  ?
                      MF_ENABLED : MF_DISABLED | MF_GRAYED ) ;
    EnableMenuItem (hmenu, IDM_NEXTPAGE, _pModel->CanNextPage() ?
                      MF_ENABLED : MF_DISABLED | MF_GRAYED ) ;
    EnableMenuItem (hmenu, IDM_NEXTSECTION, _pModel->CanNextSection() ?
                      MF_ENABLED : MF_DISABLED | MF_GRAYED ) ;
    EnableMenuItem (hmenu, IDM_PREVSECTION,_pModel->CanPrevSection() ?
                      MF_ENABLED : MF_DISABLED | MF_GRAYED ) ;
}

void CController::ButtonDown(HWND hwnd, LONG lParam )
{
    static RECT rc;
    SetCapture (hwnd);

	// second mouse click removes pop-up box
    if( _pBox )
    {
        delete _pBox;
        _pBox = 0;
		_pView->Invalidate(hwnd, &rc);
        return;
    }
    
	// locate character selected
    CScreenCanvas canvas(hwnd);
    
    POINT pt = {LOWORD(lParam), HIWORD(lParam)};

    UINT iChar = _pView->Hittest(canvas, pt, _pModel);
    
    if( iChar == 0xFFFF )
    {
        return;	  // no char selected
    }

	// create the pop-up box
    SIZE size = { 4*(INCH1-INCH8)/5, INCH1};
    CBoxFormat bxf(size);

    HFONT hfont = _pModel->GetFont();
    _pBox = new CBox(bxf, iChar, hfont); 


	// match current format
    UINT fuFormat;
	_pModel->GetFormat(fuFormat);
	_pBox->SetFormat(fuFormat & DECIMAL);


    canvas.DPtoLP(&pt);
    pt.x -= size.cx/2;
    pt.y -= size.cy/2;
#ifdef UNICODE
    pt.x -= size.cx; // accommodate wider popup
#endif

    GetClientRect(hwnd, &rc);

	// show it
    _pBox->Paint(canvas, pt, rc);

	//--- dead code....
    size = _pBox->GetSize();
    
	POINT ptSize;
	ptSize.x = size.cx;
	ptSize.y = size.cy;
	canvas.LPtoDP(&ptSize);
	pt.x+=ptSize.x;
	pt.y+=ptSize.y;
}

void CController::ButtonUp(HWND hwnd, LONG lParam )
{
    ReleaseCapture();
}

void CController::KeyDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
    switch( wParam )
    {
    case VK_PRIOR:
         Page(hwnd, IDM_PREVPAGE);
         break;
    case VK_NEXT:
         Page(hwnd, IDM_NEXTPAGE);
         break;
    case VK_HOME:
         Page(hwnd, IDM_FIRSTPAGE);
         break;
    case VK_END:
         Page(hwnd, IDM_LASTPAGE);
         break;
    case VK_UP:
         _pView->SetVScrollPos(hwnd, SB_LINEUP, lParam, _pModel);       
         break;
    case VK_DOWN:
         _pView->SetVScrollPos(hwnd, SB_LINEDOWN, lParam, _pModel);     
         break;
    case VK_LEFT:
         _pView->SetHScrollPos(hwnd, SB_LINEUP, lParam, _pModel);       
         break;
    case VK_RIGHT:
         _pView->SetHScrollPos(hwnd, SB_LINEDOWN, lParam, _pModel);     
         break;
    }
}

void CController::KeyUp(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
}

void CController::HScroll(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	if (_pBox)
	{
		// Remove box by simulating second mouse click
		ButtonDown(hwnd, 0); 
		UpdateWindow(hwnd);
	}
    _pView->SetHScrollPos(hwnd, wParam, lParam, _pModel);       
}

void CController::VScroll(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	if (_pBox)
	{
		// Remove box by simulating second mouse click
		ButtonDown(hwnd, 0); 
		UpdateWindow(hwnd);
	}
    _pView->SetVScrollPos(hwnd, wParam, lParam, _pModel);       
}

// Main application

// WinMain - Main window funtion
//
int WINAPI WinMain
   ( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdParam, int cmdShow )
{
    TCHAR  szAppName [] = TEXT("Grid") ;
    TCHAR  szCaption [] = TEXT("Character Grid") ;

    // Create Window Class
 
    if ( hPrevInst == 0 )
    {
        MakeWindowClass ( WndProc, szAppName, hInst );
    }

    // Create Window
    
    CWindow win ( szCaption, szAppName, hInst );
    
    win.Show ( cmdShow );
    
    MSG  msg;
    
    while ( GetMessage (&msg, NULL, 0, 0 ) )
    {
        TranslateMessage ( &msg );
        DispatchMessage ( &msg );
    }
    
    return msg.wParam;
}

// Make Window Class
//
void MakeWindowClass ( WNDPROC WndProc, LPTSTR szAppName, HINSTANCE hInst )
{
    WNDCLASS cl;
   
    cl.style = CS_HREDRAW | CS_VREDRAW;
    cl.lpfnWndProc = WndProc;
    cl.cbClsExtra = 0;
    cl.cbWndExtra = 0;
    cl.hInstance = hInst;
    cl.hIcon = LoadIcon ( hInst, szAppName );
    cl.hCursor = LoadCursor ( NULL, IDC_ARROW );
    cl.hbrBackground = GetStockBrush ( WHITE_BRUSH );
    cl.lpszMenuName = szAppName;
    cl.lpszClassName = szAppName;
   
    RegisterClass (&cl);
}

// Window Proc
//

LRESULT CALLBACK WndProc ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    static CController ctrl;

    switch (message)
    {
        case WM_CREATE:
            ctrl.Create(hwnd, lParam);
            return 0;
        case WM_SIZE:
            ctrl.Size(lParam);
            return 0;
        case WM_PAINT:
            ctrl.Paint(hwnd);
            return 0;
        case WM_COMMAND:
            ctrl.Command(hwnd, wParam);
            return 0;
        case WM_LBUTTONUP:
            ctrl.ButtonUp(hwnd, lParam);
            return 0;
        case WM_LBUTTONDOWN:
            ctrl.ButtonDown(hwnd, lParam);
            return 0;
        case WM_KEYUP:
            ctrl.KeyUp(hwnd, wParam, lParam);
            return 0;
        case WM_KEYDOWN:
            ctrl.KeyDown(hwnd, wParam, lParam);
            return 0;
        case WM_VSCROLL:
            ctrl.VScroll(hwnd, wParam, lParam );
            return 0;
        case WM_HSCROLL:
            ctrl.HScroll(hwnd, wParam, lParam );
            return 0;
        case WM_DESTROY:
            ctrl.Destroy();
            return 0;

    }
    return DefWindowProc (hwnd, message, wParam, lParam );
}

// "About" dialog box procedure
// Process messages from dialog box
//

BOOL CALLBACK AboutDlgProc
   ( HWND hwnd, UINT message, WPARAM wParam, LONG lParam )
{

    switch(message)
    {
       case WM_INITDIALOG:
            return TRUE;
       case WM_COMMAND:
            switch (wParam) //Command ID
            {
               case IDOK:
               case IDCANCEL:
                    EndDialog(hwnd, 0);
                    return TRUE;
            }
            break;
    }
    return FALSE;
}

extern CPrintAux PrGlobal;

//======== PrintDlgProc ===========================================

BOOL CALLBACK PrintDlgProc
   ( HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch (message)
    {
        case WM_INITDIALOG:
             SetWindowText (hwndDlg, (TCHAR *)lParam) ;
             EnableMenuItem (GetSystemMenu (hwndDlg, FALSE), SC_CLOSE, MF_GRAYED) ;
             return TRUE ;

        case WM_COMMAND:
             PrGlobal._bUserAbort = TRUE ;
             EnableWindow (GetParent (hwndDlg), TRUE) ;
             DestroyWindow (hwndDlg) ;
             PrGlobal._hDlgPrint = 0 ;
             return TRUE ;
    }
    return FALSE ;
}

//======== AbortProc ===========================================

BOOL CALLBACK AbortProc(HDC hdcPrn, short nCode)
{
    MSG   msg ;

    while (!PrGlobal._bUserAbort && PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (!PrGlobal._hDlgPrint 
                || 
            !IsDialogMessage (PrGlobal._hDlgPrint, &msg))
        {
            TranslateMessage (&msg) ;
            DispatchMessage (&msg) ;
        }
    }
    return !PrGlobal._bUserAbort ;
}


//======== PropDlgProc ===========================================
struct t_Ctype
{
	WORD 	fVal[3];
	LPTSTR	pszName;
} vCtype [] =  {
				 0x0001,0,0, TEXT("UPPER "),  // A
				 0x0002,0,0, TEXT("LOWER "),  //a
				 0x0004,0,0, TEXT("DIGIT "),  //1
				 0x0008,0,0, TEXT("SPACE "),  //_
				 0x0010,0,0, TEXT("PUNCT "),  //!
				 0x0020,0,0, TEXT("CNTRL "),
				 0x0040,0,0, TEXT("BLANK "),
				 0x0080,0,0, TEXT("XDIGIT "),	//x
				 0x0100,0,0, TEXT("ALPHA "),  //alpha
		
				 0, 0x0001,0, TEXT("LEFTTORIGHT "), //>
				 0, 0x0002,0, TEXT("RIGHTTOLEFT "), //<
				 0, 0x0003,0, TEXT("EUROPENUMBER "),
				 0, 0x0004,0, TEXT("EUROPESEPARATOR "),
				 0, 0x0005,0, TEXT("EUROPETERMINATOR "),
				 0, 0x0006,0, TEXT("ARABICNUMBER "),
				 0, 0x0007,0, TEXT("COMMONSEPARATOR "),
				 0, 0x0008,0, TEXT("BLOCKSEPARATOR "),
				 0, 0x0009,0, TEXT("SEGMENTSEPARATOR "),
				 0, 0x000a,0, TEXT("WHITESPACE "),  // _
				 0, 0x000b,0, TEXT("OTHERNEUTRAL "),  //<>

				 0,0,0x0001, TEXT("NONSPACING "),
				 0,0,0x0002, TEXT("DIACRITIC "),  //  "
				 0,0,0x0004, TEXT("VOWELMARK "),
				 0,0,0x0008, TEXT("SYMBOL "),  //	  =
				 0,0,0x0010, TEXT("KATAKANA "),  //	  katakana a
				 0,0,0x0020, TEXT("HIRAGANA "),  //	  hiragana a
				 0,0,0x0040, TEXT("HALFWIDTH "),  //  han
				 0,0,0x0080, TEXT("FULLWIDTH "),  //  zen
				 0,0,0x0100, TEXT("IDEOGRAPH "),  //  kan
				 0,0,0x0200, TEXT("KASHIDA "),
				 0,0,0x0400, TEXT("LEXICAL "),
				 0,0,0x8000, TEXT("C3ALPHA ")	//  alpha
};


BOOL CALLBACK PropDlgProc
   ( HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	int i;
    switch (message)
    {
       case WM_INITDIALOG:
	   		for( i=0; i<sizeof vCtype/sizeof t_Ctype; i++)
			{
	   			SendDlgItemMessage(hwndDlg, IDC_PROPLIST, LB_ADDSTRING, i, (LPARAM) vCtype[i].pszName);
			}
            return TRUE;
       case WM_COMMAND:
            switch (wParam) //Command ID
            {
               case IDOK:
			   		if( pCSet )
			   		{
						delete pCSet;
					}
	   				i = SendDlgItemMessage(hwndDlg, IDC_PROPLIST, LB_GETCARETINDEX, 0, 0);
			   		pCSet = new CCTypeSet(vCtype[i].fVal[0],vCtype[i].fVal[1], vCtype[i].fVal[2]);
                    EndDialog(hwndDlg, 0);
					return TRUE;
               case IDCANCEL:
			   		if( pCSet )
					{
						delete pCSet;
					}
                    EndDialog(hwndDlg, 0);
                    return TRUE;
            }
            break;
    }
    return FALSE ;
}
