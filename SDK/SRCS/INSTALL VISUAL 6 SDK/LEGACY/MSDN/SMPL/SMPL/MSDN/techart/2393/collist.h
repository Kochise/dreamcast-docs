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
// collist.h : header file
//
// The CColumnListBox is inherited from CListBox and behaves exactly
// as a listbox does.  All standard listbox messages and CListBox
// member functions operate in the same manner.
//
// However, the nonclient area of the listbox is 'grown' at the
// top to accomodate a slider for column headings.  
// WM_SETTEXT (or SetWindowText()) is used to define the strings
// that are used in column headings.   Each heading is separated from
// the next by a TAB char.
//
// Unlike normal "SetTabStops" listboxes, CCOlumnListBox lets you
// specify the justification for each column:  Left, Right, or 
// Center.
//
// An end user can size columns by dragging on column separators.  The
// shift key works as a modifier, allowing only the column to the
// left of the separator to be sized.
//
// If the CLBS_LIKEBUTTON style is set, each column heading acts
// like a 'button' that can be depressed.  The parent window will
// be notified.  This is useful for implementing 'sort by
// this column' functionality, much like MS-Mail does.
//
// There are two ways to 'use' CColumnListBox in your code:
//
//  Method #1 - Default CListBox behavior      
//  - Create the listbox control with the LBS_USETABSTOPS style
//  - Use LB_SETTABSTOPS (::SetTabStops) in the normal manner.  All
//    tab stops are defined using Dialog Base Units.
//  - SetWindowText to define the column headings (use '\t' to 
//    identify each).
//  - Use LB_ADDSTRING (::AddString) as normal to add items to the
//    list.  Each column is separated by '\t' characters as normal.
//  - Use CLB_GETTABSTOPS (::GetTabStops) to get the widths after
//    the user has changed them (so you can restore state later).
//
//  Advantages:
//      If you have code that currently uses a LBS_USETABSTOPS 
//      listbox, you can simply replace the CListBox with 
//      CColumnListBox add a call to SetWindowText() and you 
//      have column headings.
//      
//  Method #2 - Enhanced Justification behavior
//  - Don't specify LBS_USETABSTOPS when you create the control.
//  - Do specify LBS_OWNERDRAWFIXED when you create the control.
//  - You DO NOT need to implement handlers for WM_DRAWITEM 
//    (OnDrawItem) and WM_MEASUREITEM (OnMeasureItem).  
//    However, if you do want to do ownerdraw, do not call the
//    default implementation for these two messages.
//  - Use either LB_SETTABSTOPS or CLB_SETCOLUMNS to define the
//    properites of each column.   All dimensions are specified 
//    in device units (NOT dlg base units).
//  - SetWindowText to define the column headings (use '\t' to 
//    identify each).
//  - Use LB_ADDSTRING (::AddString) as normal to add items to the
//    list.  Use \t to define columns.
//  - Use CLB_GETTABSTOPS or CLB_GETCOLUMNS.
//  
//  Advantages:
//      You can define the justification style for each column:
//          left, right, or center.
//          (note:  column headings are always left justified in
//            this implementation).
//      No fooling with dialog base units.
//      Easier to implement ownerdraw:  You don't have to fool with
//      dialog base units.
/////////////////////////////////////////////////////////////////////////

#ifndef _COLLIST_H_
#define _COLLIST_H_

// ---- Control messages (in addition to all LB_ messages)
// 
// CLB_GETTABSTOPS is the opposite of LB_SETTABSTOPS. 
//  wParam = (WPARAM) cTabs;             
//  lParam = (LPARAM) (int FAR*)rgTabs ; 
// lpTabs is only valid until you return from your window proc.
//
#define CLB_GETTABSTOPS         (WM_USER+50)  // last LB_ msg is WM_USER+37

// CLB_SETCOLUMNS
//  wParam = (WPARAM) cCols;             
//  lParam = (LPARAM) (UINT FAR*)rgColWidths; 
//
// Like LB_SETTABSTOPS but column widths are in device units.
//  
#define CLB_SETCOLUMNS          (WM_USER+51)
#define CLB_GETCOLUMNS          (WM_USER+52)

// CLB_SETCOLUMNS_EX
//  wParam = (WPARAM) cCols;             /* number of columns  */
//  lParam = (LPARAM) (COLINFO FAR*)rgColInfo; 
//
// Allows setting of 'indent' and format flags.   rgColInfo is
// a pointer to an array of COLINFO structures cCols big.
//  
#define CLB_SETCOLUMNS_EX       (WM_USER+53)
#define CLB_GETCOLUMNS_EX       (WM_USER+54)

// describes a column (used for CLB_?ETCOLUMNS_EX)
//
typedef struct FAR tagCOLINFO
{
    UINT        uiWidth ;
    UINT        uiIndent ;          // indent from left of column 
                                    // where text  starts.  
    UINT        uiFormatFlags ;     // [DT_LEFT | DT_RIGHT | DT_CENTER]
} COLINFO, FAR* LPCOLINFO ;
                                            
// CLB_GETCLICKEDCOLUMN                                            
//  return value is index of column that was last clicked or
//  double clicked on.
//
#define CLB_GETCLICKEDCOLUMN    (WM_USER+55)

// CLB_SETLIKEBUTTONSTYLE
//  Under Windows NT (as a WOW app), any styles not defined for 
//  a listbox are stripped off of the listbox if present when created.
//  this renders the CLBS_LIKEBUTTON style (defined below) ineffective.
//  This message can be used to set the style instead.
//
#define CLB_SETLIKEBUTTONSTYLE  (WM_USER+56)

// ---- Notification codes (WM_COMMAND) (in addition to all LBN_ codes)
//
// Indicates that a column header was clicked on.
//
#define CLBN_CLICKED        10              // last LBN_ code is 5

// Only valid if CLBS_LIKEBUTTON is set in the class style.
#define CLBN_DOUBLECLICKED  11

#define CLBN_COLUMNCHANGE   12

// ---- Class styles (in addition to all LBS_ styles)
// 
// If this bit is set, the column headers behave like buttons
// (that is, they depress visually and CLB_DOUBLECLICKED 
// notifcations are not sent).
//
//  NOTE: This does not work when running under WOW on Windows NT!
//   Use CLB_SETLIKEBUTTONSTYLE instead.
//
#define CLBS_LIKEBUTTON     0x2000L

// CColumnList class definition
//
class CColumnListBox : public CListBox
{
    DECLARE_DYNAMIC(CColumnListBox)
// Constructors
public:
    CColumnListBox();
    ~CColumnListBox();

// Attributes
public:
    BOOL SetColumns( UINT nCols, UINT FAR* rgColInfo ) ;
    UINT GetColumns( LPINT FAR* plpInt) ;

    BOOL SetColumnsEx( UINT nCols, COLINFO FAR* rgColInfo ) ;
    UINT GetColumnsEx( LPCOLINFO FAR* prgColInfo ) ;
    
    UINT GetClickedColumn() ;
    BOOL SetLikeButtonStyle( BOOL fSet ) ; 

    // If you want to rely on the default ownerdraw implemenation
    // in CColumnListBox, set the LBS_OWNERDRAWFIXED | LBS_HASSTRINGS
    // styles and call the following two members in your
    // OnDrawItem and OnMeasureItem functions, respectively.
    //
    void DrawItem(LPDRAWITEMSTRUCT);
    void MeasureItem(LPMEASUREITEMSTRUCT);
    
protected: 
    COLINFO FAR*    m_rgColInfo ;
    UINT            m_cColumns ;    // Number of elements in m_rgColInfo

    // Its possible that the header string (set with SetWindowText) has
    // more TABS in it than there are elements in m_rgColInfo.  To handle
    // this we keep a count.
    //
    UINT            m_cTabsInHeaderString ; 
    
    int FAR*        m_rgTabStops ;  // for use by CLBM_GETTABSTOPS (speed)
    
    UINT            m_cxAvgFont ;   // For speed we keep around the font
    UINT            m_cyFont ;      // dimensions.
    
    UINT            m_uiDepressed ; // State variable for button simulation

    UINT            m_LastClickedColumn ;  // used by CLBM_GETCLICKEDCOLUMN
    
    BOOL            m_fLikeButtonStyle ;
    
public:
    void ColumnTextOut( CDC* pDC, int nX, int nY, LPRECT lprc, CString& rStr );
    void Paint( CDC* pDC ) ;
    static void JustifiedTextOut( CDC *pDC, int x, int y, 
                           RECT &rc, LPSTR sz, 
                           int nChars = 0, UINT uiJust = DT_LEFT ) ;
    static void DrawBtnFrame( CDC* pDC, LPRECT lprc, BOOL fDepressed = FALSE ) ;
    
protected:
    UINT GetHeaderRect( LPRECT lprc, BOOL fScreen = FALSE ) ;
    BOOL DepressColumn( UINT nCol, LPRECT lprc );
    BOOL SizeColumn( CPoint& point );
    void OnNcPaint( UINT uiUpdateColumn ); // only uiUpdateColumn gets painted
    void PaintNc( CDC* pDC, UINT uiUpdateColumn  ) ;
    
protected:
    //{{AFX_MSG(CColumnListBox)
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
    afx_msg UINT OnNcHitTest(CPoint point);
    afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
    afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
    afx_msg void OnNcPaint();
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnCancelMode();
    //}}AFX_MSG

    afx_msg LRESULT OnSetTabStops( WPARAM nTabStops, LPARAM lpnTabStops ) ;
    afx_msg LRESULT OnSetFont( WPARAM wParam, LPARAM lParam ) ;

    // Custom CColumnListBox messages
    afx_msg LRESULT OnGetTabStops( WPARAM nTabStops, LPARAM lpnTabStops ) ;
    afx_msg LRESULT OnSetColumns( WPARAM nCols, LPARAM rgColWidth ) ;
    afx_msg LRESULT OnGetColumns( WPARAM nCols, LPARAM rgColWidth ) ;
    afx_msg LRESULT OnSetColumnsEx( WPARAM nCols, LPARAM rgColInfo ) ;
    afx_msg LRESULT OnGetColumnsEx( WPARAM nCols, LPARAM rgColInfo ) ;
    afx_msg LRESULT OnGetClickedColumn( WPARAM, LPARAM ) ;
    afx_msg LRESULT OnSetLikeButtonStyle( WPARAM fSet, LPARAM  ) ; 
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif

