// osdibvw.h : header file
//

#ifndef __OSDIBVW__
#define __OSDIBVW__

#include "dib.h"
#include "dibpal.h"
#include "animdoc.h"

/////////////////////////////////////////////////////////////////////////////
// COffScreenDIBView view

class COffScreenDIBView : public CScrollView
{
    DECLARE_DYNCREATE(COffScreenDIBView)
protected:
    COffScreenDIBView();            // protected constructor used by dynamic creation

public:
    CAnimDoc* GetDocument();

// Implementation
protected:
    CDIB *m_pDIB;                       // ptr to off screen DIB
    LPBITMAPINFO m_pOneToOneClrTab;     // ptr to 1:1 color table
    CDIBPal *m_pPal;                    // ptr to Palette

    virtual ~COffScreenDIBView();
    virtual void OnDraw(CDC* pDC);      // overridden to draw this view
    virtual void OnInitialUpdate();         // first time after construct
    BOOL CreateFromDIB(CDIB *pDIB);         // create a new buffer
    void Draw(CDC *pDC = NULL, 
              LPRECT pRect = NULL);      // draw os buffer to screen
    BOOL MapDIBColors(CDIB *pdib);

private:
    BOOL CreateTables(CDIB *pDIB);      // create a new table set

protected:
    // Generated message map functions
    //{{AFX_MSG(COffScreenDIBView)
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
    afx_msg BOOL OnQueryNewPalette();
    afx_msg void OnOptionsPalclr();
    afx_msg void OnUpdateOptionsPalclr(CCmdUI* pCmdUI);
    afx_msg void OnOptionsPalind();
    afx_msg void OnUpdateOptionsPalind(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // __OSDIBVW__
