// WOSA/XRT XRTFrame Sample Application Version 1.01
//
// Copyright (c) 1993-94 Microsoft Corporation, All Rights Reserved.
//
//      This is a part of the Microsoft Source Code Samples. 
//      This source code is only intended as a supplement to 
//      Microsoft Development Tools and/or WinHelp documentation.
//      See these sources for detailed information regarding the 
//      Microsoft samples programs.
//
// collist.cpp : implementation file
//
// CColumnListBox implementation  
//
// Revisions:
//  September 22, 1993   cek     First implementation.
//
#include "stdafx.h" 
//#include "util.h"
#include "resource.h"
#include "collist.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
#define HTCOLUMNHEADER  ((UINT)-3)

/////////////////////////////////////////////////////////////////////////////
// CColumnListBox
BEGIN_MESSAGE_MAP(CColumnListBox, CListBox)
    //{{AFX_MSG_MAP(CColumnListBox)
    ON_WM_NCCALCSIZE()
    ON_WM_NCHITTEST()
    ON_WM_NCLBUTTONDBLCLK()
    ON_WM_NCLBUTTONDOWN()
    ON_WM_NCPAINT()
    ON_WM_DRAWITEM()
    ON_WM_MEASUREITEM()
    ON_WM_SETCURSOR()
    ON_WM_CREATE()
    ON_WM_CANCELMODE()
    //}}AFX_MSG_MAP
    
    ON_MESSAGE( LB_SETTABSTOPS, OnSetTabStops ) 
    ON_MESSAGE( WM_SETFONT, OnSetFont )
    
    // Custom CCOlumnListBox messages
    ON_MESSAGE( CLB_GETTABSTOPS, OnGetTabStops )
    ON_MESSAGE( CLB_SETCOLUMNS, OnSetColumns ) 
    ON_MESSAGE( CLB_GETCOLUMNS, OnGetColumns ) 
    ON_MESSAGE( CLB_SETCOLUMNS_EX, OnSetColumnsEx ) 
    ON_MESSAGE( CLB_GETCOLUMNS_EX, OnGetColumnsEx ) 
    ON_MESSAGE( CLB_GETCLICKEDCOLUMN, OnGetClickedColumn )
    ON_MESSAGE( CLB_SETLIKEBUTTONSTYLE, OnSetLikeButtonStyle ) 

END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CColumnListBox, CListBox)
#define new DEBUG_NEW
#ifdef M_I86LM
#undef FAR
#define FAR
#endif 

#ifndef __UTIL_H__
int WINAPI
   GetTextMetricsCorrectly( HDC hDC, LPTEXTMETRIC lpTM ) ;
#endif

// ---- CColumnListBox Constructors and destructor
//
CColumnListBox::CColumnListBox()
{
    m_rgColInfo = NULL ;
    m_rgTabStops = NULL ;
    m_cTabsInHeaderString  = m_cColumns = 0 ;
    m_cyFont = m_cxAvgFont = 0 ;
    m_uiDepressed = (UINT)-1 ;
}

CColumnListBox::~CColumnListBox()
{
    if (m_rgColInfo != NULL)
    {
        delete m_rgColInfo ;
        m_rgColInfo = NULL ;
    }    
    
    if (m_rgTabStops != NULL)
        delete m_rgTabStops ;
}


int CColumnListBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    CDC*    pDC = GetDC() ;
    TEXTMETRIC tm ;
    m_cxAvgFont = GetTextMetricsCorrectly( pDC->m_hDC, &tm ) ;
    m_cyFont = tm.tmHeight ; //+ tm.tmInternalLeading ;
    ReleaseDC( pDC ) ;

    m_rgColInfo = new COLINFO ;        
    m_cColumns = 1 ;

    m_fLikeButtonStyle = (BOOL)(GetStyle() & CLBS_LIKEBUTTON) ;
    
    if (GetStyle() & LBS_USETABSTOPS)
        m_rgColInfo[0].uiWidth = MulDiv( 30, m_cxAvgFont, 4 ) ;
    else
        m_rgColInfo[0].uiWidth = m_cxAvgFont * 8  ;
    m_rgColInfo[0].uiIndent = 0 ;
    m_rgColInfo[0].uiFormatFlags = DT_LEFT ;

    if (CListBox::OnCreate(lpCreateStruct) == -1)
        return -1;
    return 0;
}

// ---- CColumnListBox Non-Client message handlers
//
// The column header (sometimes called a slider) is implemented by
// changing the size of the listbox's non-client area (OnNcCalcSize)
// and drawing the header in the non-client area using OnNcPaint.
//
void CColumnListBox::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp)
{   
    // Call default first
    CListBox::OnNcCalcSize(bCalcValidRects, lpncsp);

    if (!IsIconic())
    {
        lpncsp->rgrc[0].top += m_cyFont + 1 ;
    }                     
}

UINT CColumnListBox::OnNcHitTest(CPoint point)
{    
    UINT    uiRet ;

    // Let the default go first
    //
    uiRet = CListBox::OnNcHitTest(point);
    
    if (!IsIconic() && uiRet == HTNOWHERE)
    {
        CRect    rc ;
        GetHeaderRect( rc, TRUE ) ;
        
        if (rc.PtInRect( point ))
        {       
            UINT    nIndex ;
            int     x = rc.left ;
            int     test ;
            
            for (UINT i = 0 ; i < max(m_cColumns-1, m_cTabsInHeaderString) ; i++ ) 
            {
                nIndex = (i < (UINT)m_cColumns ? i : m_cColumns-1) ;
                test = x + (int)m_rgColInfo[nIndex].uiWidth ;
                if (point.x >= test - 1 && point.x <= test + 1 )
                    return HTGROWBOX ;
                x += m_rgColInfo[nIndex].uiWidth ;
            }

            return HTCOLUMNHEADER ;
        }
    }
    
    return uiRet ;
}

void CColumnListBox::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
    switch(nHitTest) 
    {
        case HTCOLUMNHEADER:
        {
            if (m_fLikeButtonStyle)
            {
                return ;
                CListBox::OnNcLButtonDblClk(nHitTest, point);
            }    
            
            // Figure out which column it was
            CRect    rc ;
            GetHeaderRect( rc, TRUE ) ;

            UINT    nIndex ;
            int     left = rc.left ;
            int     right = rc.right ;
            
            for (UINT nCol = 0 ; nCol < max(m_cColumns-1, m_cTabsInHeaderString) ; nCol++ ) 
            {
                nIndex = (nCol < (UINT)m_cColumns ? nCol : m_cColumns-1) ;
                right = left + (int)m_rgColInfo[nIndex].uiWidth ;
                if (point.x >= left && point.x <= right )
                {
                    rc.left = left ;
                    if (nCol != m_cTabsInHeaderString+1)
                        rc.right = right ;
                        
                    break ;
                }
                left += m_rgColInfo[nIndex].uiWidth ;
            }
            
            //TRACE("CLBN_DOUBLECLICKED %d\n\r", nCol ) ;
              
            m_LastClickedColumn = nCol ;
            #ifndef WIN32
            GetParent()->SendMessage( WM_COMMAND, (WPARAM)GetDlgCtrlID(), 
                        MAKELPARAM( GetSafeHwnd(), CLBN_DOUBLECLICKED ) ) ;
            #else
            GetParent()->SendMessage( WM_COMMAND, (WPARAM)MAKELPARAM(GetDlgCtrlID(), CLBN_DOUBLECLICKED ), 
                            (LPARAM)GetSafeHwnd() ) ;
            #endif
        }
        break ;

#if 0        
        // TODO:  Make this size the column to the left so that it is just wide enuf for
        // the widest element in the list.
        //
        case HTGROWBOX:
            SizeColumn( point ) ;
        break ;
#endif        
        default:
            CListBox::OnNcLButtonDblClk(nHitTest, point);
    }
}

void CColumnListBox::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
    switch(nHitTest) 
    {
        case HTCOLUMNHEADER:
        {
            // Figure out which column it was
            CRect    rc ;
            GetHeaderRect( rc, TRUE ) ;

            UINT    nIndex ;
            int     left = rc.left ;
            int     right = rc.right ;
            
            for (UINT nCol = 0 ; nCol <= max(m_cColumns-1, m_cTabsInHeaderString) ; nCol++ ) 
            {
                nIndex = (nCol < (UINT)m_cColumns ? nCol : m_cColumns-1) ;
                if (nCol == m_cTabsInHeaderString)
                    right = rc.right ;
                else
                    right = left + (int)m_rgColInfo[nIndex].uiWidth ;
                if (point.x >= left && point.x <= right )
                {
                    rc.left = left ;
                    rc.right = right ;
                    break ;
                }
                left += m_rgColInfo[nIndex].uiWidth ;
            }
            
            // Call DepressColumn()
            if (DepressColumn( nCol, &rc ))
            {
                //TRACE("CLBN_CLICKED %d\n\r", nCol ) ;
                m_LastClickedColumn = nCol ;
              
                #ifndef WIN32
                GetParent()->SendMessage( WM_COMMAND, (WPARAM)GetDlgCtrlID(), 
                            MAKELPARAM( GetSafeHwnd(), CLBN_CLICKED ) ) ;
                #else
                GetParent()->SendMessage( WM_COMMAND, (WPARAM)MAKELPARAM(GetDlgCtrlID(), CLBN_CLICKED ), 
                                (LPARAM)GetSafeHwnd() ) ;
                #endif
            }
        }
        break ;
        
        case HTGROWBOX:
            SizeColumn( point ) ;
        break ;
        
        default:
            CListBox::OnNcLButtonDown(nHitTest, point);
    }
    
}

void CColumnListBox::Paint( CDC* pDC ) 
{
    //RECT rc ;
    
    
}

void CColumnListBox::PaintNc( CDC *pDC, UINT uiUpdateColumn  ) 
{
    UINT    uiBonusWidth ;

    RECT rc ;
    uiBonusWidth = GetHeaderRect( &rc ) ;                 
                 
    CFont   *pFont = GetFont() ;
    CFont   *pOldFont ;
    pOldFont = pDC->SelectObject( pFont ) ;
    LPSTR   szText ;
    UINT    cch = GetWindowTextLength()+1;
        
    szText = new FAR char[cch+2] ;    
    GetWindowText( szText, cch ) ;
    if (*szText == '\0')
    {
        szText[0] = ' ' ;
        szText[1] = '\0' ;
    }

    LPSTR   p, sz ;
    UINT    nCol = 0 ;
    UINT    nIndex ;
    BOOL    fLast = FALSE ;
    RECT    rc2 ;

    pDC->SelectObject( GetStockObject( BLACK_PEN )) ;        
    pDC->MoveTo( rc.left, rc.bottom ) ;
    pDC->LineTo( rc.right, rc.bottom ) ;

    p = sz = szText ;
    rc2 = rc ;
    m_cTabsInHeaderString = 0 ;  // used to ease hit testing

    while (*p)
    {   
        cch = 0 ;
        while (*p && *p != '\t')
        {
            cch++ ;
            p++ ;
        }
                    
        if (*p == '\t')
        {
            m_cTabsInHeaderString++ ;
            *p = '\0' ;
            p++ ;
            if (*p == '\0')
            {
                // HACK: to account for a tab at the endo
                // of the line.
                *p = ' ' ;
                *(p+1) = '\0' ;
            }
        }
        else
            fLast = TRUE ;
                
        // sz is now an zero-terminated string that represents our current column
        // label
        //
        nIndex = (nCol < (UINT)m_cColumns ? nCol : m_cColumns-1) ;
        if (fLast == FALSE)
            rc2.right = rc2.left + m_rgColInfo[nIndex].uiWidth ; 
        else
            rc2.right = rc.right ;

        if (uiUpdateColumn == -1 || uiUpdateColumn == nCol)
        {                
            pDC->SetBkColor( GetSysColor( COLOR_BTNFACE ) ) ;                        
            if (m_uiDepressed == nCol)
            {
                rc2.top += 1 ;
                rc2.left += 1 ;
            }
            JustifiedTextOut( pDC, rc2.left + 2 + m_rgColInfo[nIndex].uiIndent, rc2.top, rc2, sz, cch, m_rgColInfo[nIndex].uiFormatFlags ) ;
            if (m_uiDepressed == nCol)
            {
                rc2.top -= 1 ;
                rc2.left -= 1 ;
            }
            DrawBtnFrame( pDC, &rc2, m_uiDepressed == nCol ) ;
        }
        nCol++ ;
        rc2.left = rc2.right ;
        sz = p ;
    }                        

    if (uiBonusWidth)
    {
        rc.left = rc.right ;
        rc.right += uiBonusWidth ;
        pDC->MoveTo( rc.left, rc.top ) ;
        pDC->LineTo( rc.left, rc.bottom ) ;
        pDC->SetBkColor( GetSysColor( COLOR_BTNFACE ) ) ;                        
        pDC->ExtTextOut( 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL ) ;
        DrawBtnFrame( pDC, &rc, FALSE ) ;
    }

    delete szText ;            
    pDC->SelectObject( pOldFont ) ;
}


void CColumnListBox::OnNcPaint( UINT uiUpdateColumn )
{   
    if (!IsIconic() && m_rgColInfo && m_cColumns)
    {
        // do our drawing
        CDC *pDC = GetWindowDC() ;

        PaintNc( pDC, uiUpdateColumn ) ;
        ReleaseDC( pDC ) ;
    }
    
    // call the default
    CListBox::OnNcPaint() ;
}

void CColumnListBox::OnNcPaint( )
{
    OnNcPaint( (UINT)-1 );
}


LRESULT CColumnListBox::OnSetTabStops( WPARAM wParam, LPARAM lParam )
{   
    UINT    nTabStops = (UINT)wParam  ;
    LPINT   lpnTabStops = (LPINT)lParam;
    
    if (m_rgColInfo != NULL)
    {
        delete m_rgColInfo ;
        m_rgColInfo = NULL ;
    }    

    CFont   *pFont = GetFont() ;
    CDC*    pDC = GetDC() ;
    CFont   *pOldFont ;
    
    if (pFont != NULL)
        pOldFont = pDC->SelectObject( pFont ) ;
    TEXTMETRIC tm ;
    m_cxAvgFont = GetTextMetricsCorrectly( pDC->m_hDC, &tm ) ;
    m_cyFont = tm.tmHeight ; //+ tm.tmInternalLeading ;
        
    if (pOldFont != NULL)
        pDC->SelectObject( pOldFont ) ;

    ReleaseDC( pDC ) ;

    if (nTabStops == 0)
    {
        m_rgColInfo = new COLINFO ;        
        m_cColumns = 1 ;

        if (GetStyle() & LBS_USETABSTOPS)
            m_rgColInfo[0].uiWidth = MulDiv( 30, m_cxAvgFont, 4 ) ;
        else
            m_rgColInfo[0].uiWidth = m_cxAvgFont * 8  ;
        m_rgColInfo[0].uiIndent = 0 ;
        m_rgColInfo[0].uiFormatFlags = DT_LEFT ;
    }
    else
    {
        m_rgColInfo = new COLINFO[nTabStops] ;        
        m_cColumns = nTabStops ;
            
        int prev = 0 ;
        for ( UINT i = 0 ; i < nTabStops ; i++ )
        {
            if (GetStyle() & LBS_USETABSTOPS)
            {
                m_rgColInfo[i].uiWidth = MulDiv( lpnTabStops[i] - prev, m_cxAvgFont, 4 )  ;
                prev = lpnTabStops[i] ;
            }
            else            
                m_rgColInfo[i].uiWidth = lpnTabStops[i]  ;
                
            m_rgColInfo[i].uiIndent = 0 ;
            m_rgColInfo[i].uiFormatFlags = DT_LEFT ;
        }    
    }

    if (GetStyle() & LBS_USETABSTOPS)    
        DefWindowProc( LB_SETTABSTOPS, wParam, lParam ) ;

    RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_UPDATENOW ) ;
    return (LRESULT)TRUE ;
}

LRESULT CColumnListBox::OnGetTabStops( WPARAM w, LPARAM lParam ) 
{
    LPINT FAR * lplpInt = (LPINT FAR*)lParam ;
    
    if (m_rgTabStops != NULL)
        delete m_rgTabStops ;
        
    m_rgTabStops = new FAR int[m_cColumns] ;   // will be freed in destructor
    
    if (GetStyle() & LBS_USETABSTOPS)
    {
        int cur = 0 ;
        for (UINT i = 0 ; i < m_cColumns; i++)
        {
            cur += MulDiv( m_rgColInfo[i].uiWidth, 4, m_cxAvgFont ) ;
            m_rgTabStops[i] = cur ; 
        }
    }
    else
        for (UINT i = 0 ; i < m_cColumns; i++)
            m_rgTabStops[i] = m_rgColInfo[i].uiWidth ; 

    
    *lplpInt = m_rgTabStops ;            

    return (LRESULT)m_cColumns ;
}

LRESULT CColumnListBox::OnSetColumns( WPARAM nCols, LPARAM rgColWidth ) 
{    return OnSetTabStops( nCols, rgColWidth ) ;   }
LRESULT CColumnListBox::OnGetColumns( WPARAM w, LPARAM prgColWidth ) 
{    return OnGetTabStops( w, prgColWidth ) ;  }

LRESULT CColumnListBox::OnSetColumnsEx( WPARAM wParam, LPARAM lParam ) 
{
    UINT    nCols = (UINT)wParam  ;
    COLINFO FAR* rgColInfo = (COLINFO FAR*)lParam ;
    
    if (m_rgColInfo != NULL)
    {
        delete m_rgColInfo ;
        m_rgColInfo = NULL ;
    }    

    CFont   *pFont = GetFont() ;
    CFont   *pOldFont ;
    CDC*    pDC = GetDC() ;
    
    pOldFont = pDC->SelectObject( pFont ) ;
        
    TEXTMETRIC tm ;
    m_cxAvgFont = GetTextMetricsCorrectly( pDC->m_hDC, &tm ) ;
    m_cyFont = tm.tmHeight ; //+ tm.tmInternalLeading ;

    pDC->SelectObject( pOldFont ) ;

    ReleaseDC( pDC ) ;
    
    if (nCols == 0)
    {
        m_rgColInfo = new COLINFO ;        
        m_cColumns = 1 ;
        m_rgColInfo[0].uiWidth = m_cxAvgFont * 8  ;
        m_rgColInfo[0].uiIndent = 0 ;
        m_rgColInfo[0].uiFormatFlags = DT_LEFT ;
    }
    else
    {
        m_rgColInfo = new COLINFO[nCols] ;        
        m_cColumns = nCols ;
        #ifdef WIN32
        memcpy( m_rgColInfo, rgColInfo, nCols * sizeof(COLINFO) ) ;            
        #else
        _fmemcpy( m_rgColInfo, rgColInfo, nCols * sizeof(COLINFO) ) ;            
        #endif
    }

    RedrawWindow( NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_UPDATENOW ) ;
    return (LRESULT)TRUE ;
}

LRESULT CColumnListBox::OnGetColumnsEx( WPARAM w, LPARAM prgColInfo ) 
{
    *(LPCOLINFO FAR *)prgColInfo = m_rgColInfo ;
    return (LRESULT)m_cColumns ;
}

// handler for CLBM_GETCLICKEDCOLUMN
//
LRESULT CColumnListBox::OnGetClickedColumn( WPARAM, LPARAM ) 
{
    return (LRESULT) m_LastClickedColumn;
}

LRESULT CColumnListBox::OnSetLikeButtonStyle( WPARAM fSet, LPARAM )
{
    BOOL    f = m_fLikeButtonStyle ;
    m_fLikeButtonStyle = (BOOL)fSet ;
    return (LRESULT)f ;
}

// We need to intercept WM_SETFONT messages to the listbox
// so that we can re-calc ourselves to fit the new fonts.
//
LRESULT CColumnListBox::OnSetFont( WPARAM wParam, LPARAM lParam ) 
{
    BOOL    fRedraw = (BOOL)lParam ;

    LRESULT l = DefWindowProc( WM_SETFONT, wParam, lParam ) ;

    // Before recalcing m_cxAvgFont, restore uiWidth's to dlg units
    //
    if (m_rgColInfo && GetStyle() & LBS_USETABSTOPS)
    {
        int cur = 0 ;
        for (UINT i = 0 ; i < m_cColumns ; i++)
        {   
            cur += MulDiv( m_rgColInfo[i].uiWidth, 4, m_cxAvgFont )  ;
            m_rgColInfo[i].uiWidth = cur ;
        }
    }
    CFont   *pFont = GetFont() ;
    CDC*    pDC = GetDC() ;
    CFont*  pOldFont ;
    pOldFont = pDC->SelectObject( pFont ) ;
    TEXTMETRIC tm ;
    m_cxAvgFont = GetTextMetricsCorrectly( pDC->m_hDC, &tm ) ;
    m_cyFont = tm.tmHeight ; //+ tm.tmInternalLeading ;
        
    pDC->SelectObject( pOldFont ) ;
    ReleaseDC( pDC ) ;

    // Restore from dlg units
    if (m_rgColInfo && GetStyle() & LBS_USETABSTOPS)
    {
        int prev = 0 ;
        for (UINT i = 0 ; i < m_cColumns ; i++)
        {
            m_rgColInfo[i].uiWidth = MulDiv( m_rgColInfo[i].uiWidth - prev, m_cxAvgFont, 4 )  ;
            prev = m_rgColInfo[i].uiWidth ;
        }
    }
    if (GetStyle() & LBS_OWNERDRAWFIXED)    
        SendMessage( LB_SETITEMHEIGHT, (WPARAM)0, (LPARAM)tm.tmHeight) ;

    SetWindowPos( NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE );
    if (fRedraw)
        RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_UPDATENOW ) ;
              
    return l ;
}

// GetHeaderRect is used throughout to get the bounding rectangle
// for the header within the non-client area.  If fScreen is TRUE
// the rect is in screen coords.
//
UINT CColumnListBox::GetHeaderRect( LPRECT lprc, BOOL fScreen ) 
{
    int cx=0, cy=0 ;
    DWORD   dwStyle = GetStyle() ;
 
    if (dwStyle & WS_THICKFRAME)
    {
        cx = GetSystemMetrics( SM_CXFRAME ) ;
        cy = GetSystemMetrics( SM_CYFRAME ) ;
    }
    else
        if (dwStyle & WS_BORDER )
        {
            cx = GetSystemMetrics( SM_CXBORDER ) ;
            cy = GetSystemMetrics( SM_CYBORDER ) ;
        }

    RECT rc ;
    GetWindowRect( &rc ) ;

    GetClientRect( lprc ) ;
    lprc->bottom = m_cyFont ;
    OffsetRect( lprc, cx, cy ) ;    // this gives us the header rect in window coords
    
    if (fScreen)
        OffsetRect( lprc, rc.left, rc.top ) ;
        
    // determine the width of the area to the right, if any
    //
    InflateRect( &rc, -cx, -cy ) ;  // rc is now the size of the client area + scrollbar
    return (UINT)max( 0, (rc.right - rc.left) - (lprc->right - lprc->left)) ;
        
}

// ---- CColumnListBox Painting code
//
//   These members do utility work for painting the non-client and
// listbox client.
//
void CColumnListBox::JustifiedTextOut( CDC *pDC, int x, int y, RECT &rc, LPSTR sz, int cch, UINT uiJust ) 
{
    if (cch == 0 && *sz)
        cch = lstrlen( sz ) ;

    switch(uiJust)
    {
        case DT_CENTER:
        {
            CSize size = pDC->GetTextExtent( sz, cch ) ;
            pDC->ExtTextOut( x + ((rc.right-rc.left - size.cx) / (int)2),
                              y, ETO_OPAQUE|ETO_CLIPPED, &rc, sz, cch, NULL ) ;
        }                                   
        break ;
                
        case DT_RIGHT:
        {
            CSize size = pDC->GetTextExtent( sz, cch ) ;
                    
            pDC->ExtTextOut( x + (rc.right-rc.left - size.cx)-3,
                             y, ETO_OPAQUE|ETO_CLIPPED, &rc, sz, cch, NULL ) ;
        }                                  
        break ;
                
        case DT_LEFT:
        default:
            pDC->ExtTextOut( x, y, ETO_OPAQUE|ETO_CLIPPED, &rc, sz, cch, NULL ) ;
        break ;
    }
}

void CColumnListBox::DrawBtnFrame( CDC* pDC, LPRECT lprc, BOOL fDepressed )
{
    RECT rc2 ;
    
    if (fDepressed == FALSE)    
    {
        pDC->SetBkColor( GetSysColor( COLOR_BTNHIGHLIGHT ) ) ;
        rc2 = *lprc ;
        rc2.bottom = rc2.top + 1;
        pDC->ExtTextOut(0,0,ETO_OPAQUE,&rc2, NULL,0,NULL) ;
        
        rc2.right = lprc->left + 1 ;
        rc2.bottom = lprc->bottom ;        
        pDC->ExtTextOut(0,0,ETO_OPAQUE,&rc2, NULL,0,NULL) ;
                      
        pDC->SetBkColor( GetSysColor( COLOR_BTNSHADOW ) ) ;
        rc2 = *lprc ;
        rc2.top = lprc->bottom-1 ;
        pDC->ExtTextOut(0,0,ETO_OPAQUE,&rc2, NULL,0,NULL) ;
        
        rc2.top = lprc->top ;
        rc2.left = lprc->right - 1 ;
        pDC->ExtTextOut(0,0,ETO_OPAQUE,&rc2, NULL,0,NULL) ;
    }
    else
    {
        pDC->SetBkColor( GetSysColor( COLOR_BTNSHADOW ) ) ;
        rc2 = *lprc ;
        rc2.bottom = rc2.top + 1;
        pDC->ExtTextOut(0,0,ETO_OPAQUE,&rc2, NULL,0,NULL) ;
        
        rc2.right = lprc->left + 1 ;
        rc2.bottom = lprc->bottom ;        
        pDC->ExtTextOut(0,0,ETO_OPAQUE,&rc2, NULL,0,NULL) ;
    }
}

// The ColumntTextOut function writes a character string at
// the specified location, using tabs to identify column breaks.  Each
// column is aligned according to the array of COLINFO
//
void CColumnListBox::ColumnTextOut( CDC* pDC, int nX, int nY, LPRECT lprc, CString& rStr )
{

    COLINFO         CI ;              // local copy for speed 
    RECT           rc ;              // current cell rect 
    UINT           nCol = 0 ;  // what column 
    LPSTR          lpNext ;          // next string (current is lpsz) 
    int            cch ;             // count of chars in current string 
    
    if (m_rgColInfo == NULL || m_cColumns < 1)
    {                                                                      
        int Tab ;  
        Tab = m_cxAvgFont * 8 ;
        pDC->ExtTextOut( 0, 0, ETO_OPAQUE, lprc, NULL, 0, NULL ) ;
        pDC->TabbedTextOut( nX+2, nY, rStr, rStr.GetLength(), 1, &Tab, nX ) ;
        return ;
    }

    rc = *lprc ;
    
    // For each sub string (bracketed by a tab)
    //
    LPSTR lpsz = lpNext = rStr.GetBuffer( rStr.GetLength() + 2 ) ;
    while (*lpNext)
    {
        for (cch = 0, lpNext = lpsz ;
             *lpNext != '\t' && *lpNext ;
             lpNext++, cch++)
            ;

        CI = m_rgColInfo[(nCol < m_cColumns) ? nCol : m_cColumns - 1] ;

        if (CI.uiWidth == (UINT)-1)
            CI.uiWidth = lprc->right - lprc->left ;  

        rc.right = nX + CI.uiWidth ;
         
        // special case right most column
        if (*lpNext == '\0')    
        {
            rc.right = lprc->right ;
            if (nCol == m_cTabsInHeaderString)
                CI.uiWidth = rc.right - rc.left ;
        }
    
        // If the width of the column is 0 do nothing
        //
        if (CI.uiWidth > 0)
        {
            switch(CI.uiFormatFlags)
            {
                case DT_CENTER:
                {
                    CSize size = pDC->GetTextExtent( lpsz, cch ) ;
                    pDC->ExtTextOut( 2 + nX + (((int)CI.uiWidth - size.cx) / (int)2),
                                      nY, ETO_OPAQUE | ETO_CLIPPED, &rc, lpsz, cch, NULL ) ;
                }                                   
                break ;
                
                case DT_RIGHT:
                {
                    CSize size = pDC->GetTextExtent( lpsz, cch ) ;
                    
                    pDC->ExtTextOut( nX + (CI.uiWidth - size.cx)-1,
                                     nY, ETO_OPAQUE | ETO_CLIPPED, &rc, lpsz, cch, NULL ) ;
                }                                  
                break ;
                
                case DT_LEFT:
                default:
                    pDC->ExtTextOut( 2+nX + CI.uiIndent, nY, ETO_OPAQUE, &rc, lpsz, cch, NULL ) ;
                break ;
            }
        }
        
        nX = rc.left = rc.right ;
        nCol++ ;
            
        lpsz = lpNext + 1 ;
    }

    rStr.ReleaseBuffer() ;
    
} // ColumnTextOut()  

// ---- Header manipulation helpers
//
// The following functions: OnSetCursor, DepressColumn, and SizeColumn
// are used for the UI of the header.
//
BOOL CColumnListBox::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    if (nHitTest == HTGROWBOX)
    {
        SetCursor( AfxGetApp()->LoadCursor( IDC_SIZEHORZ ) ) ;
        return FALSE ;
    }
    
    return CListBox::OnSetCursor(pWnd, nHitTest, message);
}

// This function is called when the user has pressed a column header
// (i.e. WM_NCLBUTTONDOWN).  We go into a Peekmessage() loop,
// waiting for the mouse to come back up.  This allows us to make the
// button change up/down state like a real button does.
//
// lprc points to the rectangle that describes the button the
// user has clicked on.
//
// When a button has been clicked on the parent is notified via a
// CLBN_CLICKED message (generated by the caller to this function
// ...this function returns TRUE if the button was 'clicked'
// FALSE otherwise.
//
BOOL CColumnListBox::DepressColumn(UINT nCol, LPRECT lprc )
{             
    MSG     msg ;
    RECT    rc ;    // need client coords for draw
    
    rc = *lprc ;
    OffsetRect( &rc, -lprc->left, -lprc->top ) ;
    
    if (m_fLikeButtonStyle)
    {
        m_uiDepressed = nCol ;
        OnNcPaint( nCol ) ;
    }

    SetCapture() ;
    
    while (TRUE)
    {
        if (PeekMessage((LPMSG)&msg, NULL, WM_MOUSEFIRST, WM_MOUSELAST, PM_REMOVE))
        {
            switch (msg.message)
            {
                case WM_LBUTTONUP:
                    if (m_fLikeButtonStyle)
                    {
                        m_uiDepressed = (UINT)-1 ;
                        OnNcPaint( nCol ) ;
                    }
                    ReleaseCapture();
                return PtInRect( lprc, msg.pt ) ;
                
                case WM_MOUSEMOVE:
                    if (m_fLikeButtonStyle)
                    {
                        if (PtInRect( lprc, msg.pt ))
                        {
                            if (m_uiDepressed != nCol)
                                m_uiDepressed = nCol ;
                        }
                        else
                        {
                            if (m_uiDepressed == nCol)
                                m_uiDepressed = (UINT)-1 ;
                        }
                        OnNcPaint( nCol ) ;
                    }
                break;
            }
        }
    }
    
} // DepressColumn()  

// Handle the sizing of columns
//
// Caveat:  Use this, and you loose the ability to have one integer define the width
// of trailing columns.   This routine will allocate a complete m_rgColInfo array
// regardless of what is already available.
//
BOOL CColumnListBox::SizeColumn( CPoint& point )
{             
    BOOL    fDepressed = TRUE ;
    MSG     msg ;
    UINT    i ;
    CRect    rc ;

    GetHeaderRect( rc, TRUE ) ;

    COLINFO FAR* rgtemp = new FAR COLINFO[m_cTabsInHeaderString+1] ;
    
    for ( i = 0 ; i < m_cTabsInHeaderString+1 ; i++ )
    {
        rgtemp[i] = m_rgColInfo[i < m_cColumns ? i : m_cColumns-1] ;
    }
    
    delete m_rgColInfo ;
    m_rgColInfo = rgtemp ;
    m_cColumns = m_cTabsInHeaderString+1 ;
    
    UINT    nSep = (UINT)-1 ;

    // xMin is the left bound.   If we are moving the leftmost separator then
    // xMin == left bound of header.
    //
    int     xMin = rc.left ;
    
    // xMax is the right bound.  If we are moving the rightmost separator then
    // xMax == right bound of header.  Otherwise it is xMin + uiWidth.
    int xMax = rc.right ;
    
    // xOld is the x coord of the separator we're sliding
    //
    int     xOld = 0 ;
    
    int     x, xTemp ;
    
    for (i = 0, x = rc.left ; i < m_cColumns-1 ; i++ ) 
    {
        xTemp = x + (int)m_rgColInfo[i].uiWidth ;
        if (point.x >= xTemp - 1 && point.x <= xTemp + 1 )
        {
            nSep = i ;   
            xOld = xTemp ;
            xMin = x ;
            
            if (i == m_cColumns-2)
                xMax = rc.right ;
            else
                xMax = xOld + m_rgColInfo[i+1].uiWidth ;
        }
        x += m_rgColInfo[i].uiWidth ;
    }       

    if (GetKeyState( VK_SHIFT ) >> (sizeof(int)-1) == 0)
    {
        // If shift is not down min max are defined by the client area
        //
//        xMin = rc.left ;
        xMax = rc.right ;
    }

    
    // Restrict movement a bit
    xMin++ ;
    xMax-- ;
    
    if (nSep == (UINT)-1)
    {
        MessageBeep(0) ;
        return FALSE ;
    }
    
    // With no modifier key down, moving one separator sizes all of the
    // columns to the right proportionally.   In other words, moving the sep to the
    // right makes all columns to the right smaller and moving the sep to
    // the left makes all columns to the right bigger.
    //
    // SHIFT down while moving means that just the columns to the left and
    // right of the sep change size.  All other columns remain unchanged.
    //

    SetCapture() ;
    
    CDC*    pDC = GetDC() ;
    RECT    rcClient ;
    GetClientRect( &rcClient ) ;
    pDC->PatBlt( xOld - rc.left, rcClient.top, 
                 1, rcClient.bottom - rcClient.top, 
                 PATINVERT ) ;

    // xNew is the x coord where the mousemove put us
    int xNew = xOld ;
    int nDelta ;
        
    while (TRUE)
    {
        if (PeekMessage((LPMSG)&msg, NULL, WM_MOUSEFIRST, WM_MOUSELAST, PM_REMOVE))
        {
            switch (msg.message)
            {
                case WM_CANCELMODE:
                case WM_LBUTTONUP:
                    pDC->PatBlt( xOld - rc.left, rcClient.top, 
                                 1, rcClient.bottom - rcClient.top, 
                                 PATINVERT ) ;
                    if (pDC)
                        ReleaseDC( pDC ) ;
                        
                    ReleaseCapture();     
                    if (GetStyle() & LBS_USETABSTOPS)
                    {
                        int far* lpn = new FAR int[m_cColumns] ;
                        int n = 0 ;
                        for (UINT i = 0 ; i < m_cColumns ; i++)
                        {
                            n += MulDiv( m_rgColInfo[i].uiWidth, 4, m_cxAvgFont ) ;
                            lpn[i] = n ;
                        }
                        CListBox::SetTabStops( m_cColumns, lpn ) ;
                        delete lpn ;
                    }
                    InvalidateRect( NULL, FALSE ) ;
                    #ifndef WIN32
                    GetParent()->SendMessage( WM_COMMAND, (WPARAM)GetDlgCtrlID(), 
                                MAKELPARAM( GetSafeHwnd(), CLBN_COLUMNCHANGE ) ) ;
                    #else
                    GetParent()->SendMessage( WM_COMMAND, (WPARAM)MAKELPARAM(GetDlgCtrlID(), CLBN_COLUMNCHANGE ), 
                                    (LPARAM)GetSafeHwnd() ) ;
                    #endif                    
                return TRUE ;
                
                case WM_MOUSEMOVE:
                    pDC->PatBlt( xOld - rc.left, rcClient.top, 
                                 1, rcClient.bottom - rcClient.top, 
                                 PATINVERT ) ;
                    xNew = LOWORD( msg.lParam ) + rc.left ; // convert to screen coords

                    // don't let xNew go past bounds
                    //
                    if (xNew < xMin)
                        xNew = xMin ;
                    if (xNew > xMax)
                        xNew = xMax ;
                    nDelta = xNew - xOld ;
                    m_rgColInfo[nSep].uiWidth += nDelta ;
                    if (GetKeyState( VK_SHIFT ) >> (sizeof(int)-1))
                        m_rgColInfo[nSep+1].uiWidth -= nDelta ;
                    xOld = xNew ;
                    OnNcPaint() ;
                    pDC->PatBlt( xOld - rc.left, rcClient.top, 
                                 1, rcClient.bottom - rcClient.top, 
                                 PATINVERT ) ;
                break;
            }
        }
    }
    
} // SizeColumn()  

void CColumnListBox::OnCancelMode()
{
    CListBox::OnCancelMode();
}

// ---- CColumnListBox owner draw handlers.
//
// CColumnListBoxes can be created in one of two ways:
// 1) using LBS_USETABSTOPS
// 2) using LBS_OWNERDRAWFIXED
// 
// If #1 then the ownerdraw functions below are never
// called.  If #2 then they are (from the client code).
//
void CColumnListBox::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDIS)
{
    if (lpDIS->itemID == LB_ERR)
        return ;

    CDC             dc ;             
    COLORREF        rgbBack ;
    RECT            rcFocus ;
    BOOL            fSelected ;
    int             x, y /*, cy*/ ;

    CString         szItem ;

    dc.Attach( lpDIS->hDC ) ;
    
    rcFocus = lpDIS->rcItem ;    

    GetText( lpDIS->itemID, szItem ) ;
    
    if (fSelected = (lpDIS->itemState & ODS_SELECTED) ? TRUE : FALSE)
    {
        dc.SetTextColor( GetSysColor( COLOR_HIGHLIGHTTEXT ) ) ;
        dc.SetBkColor( rgbBack = GetSysColor( COLOR_HIGHLIGHT ) ) ;
    }
    else
    {
        dc.SetTextColor( GetSysColor( COLOR_WINDOWTEXT ) ) ;
        dc.SetBkColor( rgbBack = GetSysColor( COLOR_WINDOW ) ) ;
    }
    
    // if we are loosing focus, remove the focus rect before
    // drawing.
    //
    
    if ((lpDIS->itemAction) & (ODA_FOCUS))
        if (!((lpDIS->itemState) & (ODS_FOCUS)))
            dc.DrawFocusRect( &rcFocus ) ;
    
    y = lpDIS->rcItem.top ;
    x = lpDIS->rcItem.left ;
        
//    cy = (rcFocus.bottom - rcFocus.top - m_cyFont) / 2 ;

    // draw
    ColumnTextOut( &dc, x, y /*+ cy*/, &lpDIS->rcItem, szItem ) ;

    // if we are gaining focus draw the focus rect after drawing
    // the text.
    if ((lpDIS->itemAction) & (ODA_FOCUS))
        if ((lpDIS->itemState) & (ODS_FOCUS))
             dc.DrawFocusRect( &rcFocus ) ;
    
    
    if (fSelected)
    {
        dc.SetTextColor( GetSysColor( COLOR_WINDOWTEXT ) ) ;
        dc.SetBkColor( GetSysColor( COLOR_WINDOW ) ) ;
    }

    dc.Detach() ;
}

void CColumnListBox::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
    lpMeasureItemStruct->itemHeight = m_cyFont ;
}

void CColumnListBox::DrawItem(LPDRAWITEMSTRUCT lp )
{ 
    OnDrawItem( GetDlgCtrlID(), lp ) ;
}
    
void CColumnListBox::MeasureItem(LPMEASUREITEMSTRUCT lp)
{ 
    OnMeasureItem( GetDlgCtrlID(), lp ) ;
}

// ---- Public access functions
BOOL CColumnListBox::SetColumns( UINT nCols, UINT FAR* rgColInfo ) 
{
    return (BOOL)OnSetColumns( (WPARAM)nCols, (LPARAM)rgColInfo ) ;
}

UINT CColumnListBox::GetColumns( LPINT FAR* plpInt ) 
{
    return (BOOL)OnGetColumns( (WPARAM)NULL, (LPARAM)plpInt ) ;
}

BOOL CColumnListBox::SetColumnsEx( UINT nCols, COLINFO FAR* rgColInfo )
{
    return (BOOL)OnSetColumnsEx( (WPARAM)nCols, (LPARAM)rgColInfo ) ;
}

UINT CColumnListBox::GetColumnsEx( LPCOLINFO FAR* prgColInfo )
{
    return (UINT)OnGetColumnsEx( (WPARAM)NULL, (LPARAM)prgColInfo ) ;
}

UINT CColumnListBox::GetClickedColumn() 
{
    return (UINT)OnGetClickedColumn( (WPARAM)NULL, (LPARAM)NULL ) ;
}

BOOL CColumnListBox::SetLikeButtonStyle( BOOL fSet ) 
{
    return (BOOL)OnSetLikeButtonStyle( (WPARAM)fSet, (LPARAM)NULL ) ;
}

#ifndef __UTIL_H__
/****************************************************************
 *  int WINAPI
 *    GetTextMetricsCorrectly( HDC hDC, LPTEXTMETRIC lpTextMetrics )
 *
 *  Description: 
 *    
 *    This function gets the textmetrics of the font currently
 *    selected into the hDC.  It returns the average char width as
 *    the return value.
 *
 *    This function computes the average character width correctly
 *    by using GetTextExtent() on the string "abc...xzyABC...XYZ"
 *    which works out much better for proportional fonts.
 *
 *    Note that this function returns the same TEXTMETRIC
 *    values that GetTextMetrics() does, it simply has a different
 *    return value.
 *
 *  Comments:
 *
 ****************************************************************/
int WINAPI
   GetTextMetricsCorrectly( HDC hDC, LPTEXTMETRIC lpTM )
{
   int    nAveWidth ;
   char   rgchAlphabet[52] ;
   int  i ;
   SIZE size ;

   // Get the TM of the current font.  Note that GetTextMetrics
   // gets the incorrect AveCharWidth value for proportional fonts.
   // This is the whole poshort in this exercise.
   //
   if (lpTM)
    GetTextMetrics(hDC, lpTM);

   // If it's not a variable pitch font GetTextMetrics was correct
   // so just return.
   //
   if (lpTM && !(lpTM->tmPitchAndFamily & FIXED_PITCH))  
      return lpTM->tmAveCharWidth ;
   else
   {
      for ( i = 0 ; i <= 25 ; i++)
         rgchAlphabet[i] = (char)(i+(int)'a') ;

      for ( i = 0 ; i<=25 ; i++)
         rgchAlphabet[i+25] = (char)(i+(int)'A') ;

      GetTextExtentPoint( hDC, (LPSTR)rgchAlphabet, 52, &size ) ;
      nAveWidth = size.cx / 26 ;
      nAveWidth = (nAveWidth + 1) / 2 ;
   }

   // Return the calculated average char width
   //
   return nAveWidth ;

} /* GetTextMetricsCorrectly()  */
#endif

