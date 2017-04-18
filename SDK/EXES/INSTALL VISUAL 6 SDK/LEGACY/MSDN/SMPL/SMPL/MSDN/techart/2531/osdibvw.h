// osdibvw.h : header file
//

#ifndef __OSDIBVW__
#define __OSDIBVW__

#include "dib.h"
#include "dibpal.h"
#include "animdoc.h"

// define the CreateDIBSection function (Build 550 version)
typedef HBITMAP (APIENTRY CDSPROC)
                (HDC hDC, 
                 BITMAPINFO *pbmi,
                 UINT iUsage, 
                 VOID ** ppvBits,
                 HANDLE hSection,
                 DWORD dwOffset);

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
    CDIBPal *m_pPal;                    // ptr to Palette

    virtual ~COffScreenDIBView();
    virtual void OnDraw(CDC* pDC);      // overridden to draw this view
    virtual void OnInitialUpdate();         // first time after construct
    BOOL CreateFromDIB(CDIB *pDIB);         // create a new buffer
    void Draw(CDC *pDC = NULL, 
              RECT *pRect = NULL);      // draw os buffer to screen
    BOOL MapDIBColors(CDIB *pdib);

private:
    BITMAPINFO *m_pOneToOneClrTab;     // ptr to 1:1 color table
    BOOL m_bUseCreateDIBSection;        // flag
    CDSPROC *m_pCDSProc;                // ptr to CreateDIBSection
    HBITMAP m_hbmSection;               // bm from section
    
protected:
    // Generated message map functions
    //{{AFX_MSG(COffScreenDIBView)
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
    afx_msg BOOL OnQueryNewPalette();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // __OSDIBVW__
