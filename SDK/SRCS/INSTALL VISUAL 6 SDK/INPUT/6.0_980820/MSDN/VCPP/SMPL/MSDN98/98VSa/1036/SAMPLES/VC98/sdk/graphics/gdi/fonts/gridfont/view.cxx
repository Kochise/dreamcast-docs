//--------------------------------------------------------------------
// File: View.Cxx
//
// Classes: 
//      CClientCanvas - Device context for client area
//      CPrintCanvas  - Device context for printing
//
//      CView          - Base class for Views 
//      CScrollaleView - Scrollable View
//      CFullPageView  - NonScrollable FullPage View
//
// History: 22-Jan-1993 Asmusf  Created
//
// Copyright (C) 1993-1997 Microsoft Corp. All Rights reserved
//
//--------------------------------------------------------------------
#include <windows.h>
#include <windowsx.h>
#include <commdlg.h>
#include "app.h"
#include "view.hxx"
#include "grid.hxx"

//+--------------------------------------------------------
// Class:       CView
//
// Purpose:     Standard fixed View for printing, or base class
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------
CView::CView(int cx, int cy)
{
        _iScale = 100;        // percentage magnification
        _ptOrg.x = 0;         // 0..(PAGEWIDTH - widht of window) 
        _ptOrg.y = 0;         // 0..(PAGEHEIGHT - height of window)
        _ptScroll.x = 0;      // 0..PAGEWIDTH
        _ptScroll.y = 0;      // 0..PAGEHEIGHT
        _size.cx = cx;        // width of window (dev. coord)
        _size.cy = cy;        // widht of window (dev. coord)
}

void CView::SetSize( int cx, int cy)
{
        _size.cx = cx;
        _size.cy = cy;
}

void CView::Invalidate(HWND hwnd, LPRECT lpRect)
{
        InvalidateRect(hwnd, lpRect, TRUE);             
}

BOOL CView::Paint(CCanvas& canvas, CModel * _pModel, RECT rc)
{
        // Scale using MapMode = logical TWIPS
        canvas.Scale(_iScale);
        
        // Client rect in logical coordinates
        _ptClient.x=_size.cx;
        _ptClient.y=_size.cy;
        canvas.DPtoLP(&_ptClient);

        // Adjust GDIwindow origin, set _ptOrg
        Scroll(canvas);

        // ClipRectangle in logical coordinates
        POINT pt;
        pt.x = rc.left; pt.y = rc.top;
        canvas.DPtoLP(&pt);
        rc.left = pt.x; rc.top = pt.y;

        pt.x = rc.right; pt.y = rc.bottom;
        canvas.DPtoLP(&pt);
        rc.right = pt.x; rc.bottom = pt.y;


        // Paint
        _pModel->Paint(canvas, rc);

        return TRUE;  // screen Paints don't fail
}

UINT CView::Hittest(CCanvas& canvas, POINT ptTest, CModel * _pModel)
{
        // Scale using MapMode = logical TWIPS
        canvas.Scale(_iScale);
        
        // Client rect in logical coordinates
        _ptClient.x=_size.cx;
        _ptClient.y=_size.cy;
        canvas.DPtoLP(&_ptClient);

        // Adjust GDIwindow origin, set _ptOrg
        Scroll(canvas);

        // Hittest

        canvas.DPtoLP(&ptTest);
        return _pModel->Hittest( ptTest);
}

void CView::Scroll(CCanvas &canvas)
{
        int dx=MulDiv(_ptClient.x,_ptScroll.x,PAGEWIDTH);
        int dy=MulDiv(_ptClient.y,_ptScroll.y,PAGEHEIGHT);

        // Adjust GDIwindow origin, set _ptOrg
        _ptOrg.x = _ptScroll.x-dx;
        _ptOrg.y = _ptScroll.y-dy;
        
        canvas.Scroll(_ptOrg.x, _ptOrg.y);
}

//+--------------------------------------------------------
// Class:       CScrollableView
//
// Purpose:     View for scrollable window
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------
void CScrollableView::SetHScrollPos(HWND hwnd, WPARAM wParam, LPARAM lParam, CModel * pModel)
{
    CScreenCanvas canvas(hwnd);
    int nScrollPos = GetScrollPos( hwnd, SB_HORZ );
    canvas.Scale(_iScale);


    SIZE size;
    pModel->GetLineSize(&size);

    // scroll position relative to page dimension
    switch (wParam)
    {
    case SB_LINEUP:
         nScrollPos -= 2 * size.cx;
         break;
    case SB_LINEDOWN:
         nScrollPos += 2 * size.cx;
         break;

    case SB_PAGEUP:
         nScrollPos -= _ptClient.x; // size of Window in log coord
         break;

    case SB_PAGEDOWN:
         nScrollPos += _ptClient.x;
         break;

    case SB_THUMBPOSITION:
         nScrollPos = LOWORD(lParam);
         break;

    default:
         break;
    }
                      
    nScrollPos = max( 0, min (nScrollPos, PAGEWIDTH));
    
    POINT pt;
    pt.x =  GetScrollPos( hwnd, SB_HORZ ) - nScrollPos;
    if( pt.x )
    {
        SetScrollPos(hwnd, SB_HORZ, nScrollPos, TRUE );

        pt.y = 0;
        canvas.LPtoDP(&pt);

        pt.x -= MulDiv( _ptClient.x, pt.x, PAGEWIDTH);
        ScrollWindow(hwnd, pt.x, pt.y, NULL, NULL );    
    }
    _ptScroll.x = nScrollPos;
}

void CScrollableView::SetVScrollPos(HWND hwnd, WPARAM wParam, LPARAM lParam, CModel * pModel)
{
    CScreenCanvas canvas(hwnd);
    int nScrollPos = GetScrollPos( hwnd, SB_VERT );
    canvas.Scale(_iScale);


    SIZE size;
    pModel->GetLineSize(&size);

    // scroll position relative to page dimension
    switch (wParam)
    {
    case SB_LINEUP:
         nScrollPos -= 2 * size.cy;
         break;
    case SB_LINEDOWN:
         nScrollPos += 2 * size.cy;
         break;

    case SB_PAGEUP:
         nScrollPos -= _ptClient.y; // size of Window in log coord
         break;

    case SB_PAGEDOWN:
         nScrollPos += _ptClient.y;
         break;

    case SB_THUMBPOSITION:
         nScrollPos = LOWORD(lParam);
         break;

    default:
         break;
    }
                      
    nScrollPos = max( 0, min (nScrollPos, PAGEHEIGHT));
    
    POINT pt;
    pt.y =  GetScrollPos( hwnd, SB_VERT ) - nScrollPos;
    if( pt.y )
    {
        SetScrollPos(hwnd, SB_VERT, nScrollPos, TRUE );

        pt.x = 0;
        canvas.LPtoDP(&pt);

        pt.y -= MulDiv( _ptClient.y, pt.y, PAGEHEIGHT);
        ScrollWindow(hwnd, pt.x, pt.y, NULL, NULL );    
    }
    _ptScroll.y = nScrollPos;
}

//+--------------------------------------------------------
// Class:       CPrintCanvas
//
// Purpose:     Device Context for Printing
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------

// fully inline //

//+--------------------------------------------------------
// Class:       CPrintRequest
//
// Purpose:     Print Job selection and parameters
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------
CPrintAux PrGlobal;     // global flags for printing control

CPrintRequest::CPrintRequest(HWND hwnd, UINT nMinPage, UINT nMaxPage ) :
        _hwnd(hwnd),
        _hdc(0),
        _hDevNames(0)
{
    PRINTDLG pd;

    pd.lStructSize= sizeof(PRINTDLG);
    pd.hwndOwner=NULL;
    pd.hDevMode=NULL;
    pd.hDevNames=NULL;
    pd.hDC;
    pd.nFromPage = 0xFFFF; // cause initial blank field
    pd.nToPage   = 0xFFFF; // in dialog
    pd.nMinPage=nMinPage;
    pd.nMaxPage=nMaxPage;
    pd.nCopies=1;
    pd.hInstance=NULL;
    pd.lCustData=0L;
    pd.lpfnPrintHook=NULL;
    pd.lpfnSetupHook=NULL;
    pd.lpPrintTemplateName=NULL;
    pd.lpSetupTemplateName=NULL;
    pd.hPrintTemplate=NULL;
    pd.hSetupTemplate=NULL;

    pd.Flags = PD_RETURNDEFAULT;
    
    if( PrintDlg(&pd) )
    {
        pd.Flags = PD_SELECTION | PD_HIDEPRINTTOFILE | PD_RETURNDC;
        if( PrintDlg( &pd ) )
        {
             if(pd.Flags & PD_PAGENUMS)
             {
                 _nFromPage = pd.nFromPage;
                 _nToPage = pd.nToPage;
             }
             else if (pd.Flags & PD_SELECTION )
             {
                 _nFromPage = _nToPage = 0xFFFF;
             }
             else   // all non empty pages
             {
                 _nFromPage = nMinPage;
                 _nToPage = nMaxPage;
             }
             _hdc = pd.hDC;
             _hDevNames = pd.hDevNames;

             if( pd.hDevMode )
             {
                GlobalFree (pd.hDevMode);
             }
             _status = PREQ_SUCCESS;
             return;
        }
        else
        {
            _status = PREQ_ERROR;
            return;
        }
    } 

    _status = PREQ_CANCEL;
}

CPrintRequest:: ~CPrintRequest()
{
    if( _hDevNames )
    {
        GlobalFree( _hDevNames );
    }
    
    if( _hdc )
    {
        DeleteDC(_hdc );
    }
}

UINT CPrintRequest::Print(HINSTANCE hInst, CCanvas &canvas, CModel *pModel)
{
     // needs to become app & font name....
     static TCHAR szMessage [] = TEXT("Grid: Printing") ;

     TCHAR szCaption[30];
     
     BOOL       fError = PREQ_SUCCESS ;
     ABORTPROC  lpfnAbortProc;
     DLGPROC    lpfnPrintDlgProc ;
     short      cxPage, cyPage ;

     cxPage = GetDeviceCaps (canvas, HORZRES) ;
     cyPage = GetDeviceCaps (canvas, VERTRES) ;

     // disable user input to main window
     EnableWindow (_hwnd, FALSE) ;

     lpfnPrintDlgProc = (DLGPROC) MakeProcInstance ((FARPROC) PrintDlgProc, hInst) ;
     
     LoadString(hInst, IDS_MSGCAPTION, szCaption, 30);
     PrGlobal._bUserAbort = FALSE ;
     PrGlobal._hDlgPrint = 
                CreateDialogParam (hInst, TEXT("PrintDlgBox"), _hwnd, 
                                lpfnPrintDlgProc, (LONG)(LPSTR) szCaption) ;

     lpfnAbortProc = (ABORTPROC) MakeProcInstance ((FARPROC) AbortProc, hInst) ;

     SetAbortProc(canvas, lpfnAbortProc);

     DOCINFO docinfo;
     docinfo.cbSize = sizeof(DOCINFO);
     docinfo.lpszDocName = szMessage;
     docinfo.lpszOutput = NULL;

     if (Escape (canvas, STARTDOC, sizeof szMessage - 1, (LPCSTR)szMessage, NULL) > 0)
     //if (StartDoc(canvas, &docinfo) > 0)
     {
          UINT fuFormat;
          pModel->GetFormat(fuFormat);
          pModel->SetFormat(fuFormat | PAGEPRINT|PAGEELEMS);
          UINT iSavePage = pModel->GetPage();
          

          // create printer view to 
          CView  View(cxPage, cyPage);


          if( _nToPage == 0xFFFF || _nFromPage == 0xFFFF )
          {     
                _nToPage =   pModel->GetPage()+1;
                _nFromPage = pModel->GetPage()+1;
          }

          for( ; _nFromPage <= _nToPage && ! fError; _nFromPage++ )
          {
             if (pModel->IsModelPageUsed(_nFromPage-1))
                {
                if( StartPage(canvas) < 0 )
                    {
                    fError = PREQ_ERRSTARTPAGE ;
                    break;
                    }    
                pModel->SetPage(_nFromPage-1);  // <- pages are 0 based in Model
                RECT rc;
                rc.left = rc.top = 0;
                rc.right= cxPage;
                rc.bottom = cyPage;
                View.Paint (canvas, pModel, rc) ;
                
                if ( EndPage(canvas) < 0)
                    {
                    fError = PREQ_ERRENDPAGE ;
                    }
				}
          }
          if( !fError )
          {
               EndDoc(canvas);
          }
          // restore screen format
          pModel->SetPage(iSavePage);
          pModel->SetFormat(fuFormat);
     }
     else
     {
          fError = PREQ_ERRSTARTDOC ;
     }

     if (!PrGlobal._bUserAbort)
     {
          EnableWindow (_hwnd, TRUE) ;
          DestroyWindow (PrGlobal._hDlgPrint) ;
     }

     FreeProcInstance ((FARPROC)lpfnPrintDlgProc) ;
     FreeProcInstance ((FARPROC)lpfnAbortProc) ;

     if( PrGlobal._bUserAbort )
     {
        fError |= PREQ_USERABORT;
     }

     return fError ;
}


