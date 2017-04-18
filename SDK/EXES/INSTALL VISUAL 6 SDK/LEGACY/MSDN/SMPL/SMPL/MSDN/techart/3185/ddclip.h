///////////////////////////////////////////////////////////
// ddclip.h

#ifndef __DDCLIP__
#define __DDCLIP__

// Message values
extern UINT ddcMsgQueryDrop;
extern UINT ddcMsgDoDrop;
extern UINT ddcMsgBeginDragDrop;

// Global functions
HGLOBAL CreateClipboardData(CObject* pObject);
BOOL SetClipboardObject(UINT uiFmt, CObject* pObject);
BOOL GetClipboardObject(CWnd* pWnd, UINT uiFmt, CObject* pObject);
void BeginDragDrop(CWnd* pSourceWnd, UINT uiFmt, CObject* pObject);
BOOL GetDropData(CObject* pObject);

// Window object used during drag and drop to receive
// mouse messages

class CDdcWnd : public CWnd
{
public:
    CDdcWnd::CDdcWnd(CWnd* pSourceWnd, UINT uiFmt);

private:
    HWND m_hwndSource;
    UINT m_uiFmt;
    HWND m_hwndOldCapture;
    HWND m_hwndUnder;
    HCURSOR m_hcurOld;
    HCURSOR m_hcurNoDrop; // IDC_DDCNODROP
    HCURSOR m_hcurDropOK; // IDC_DDCDROPOK

protected:
    //{{AFX_MSG(CDdcWnd)
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
#endif // __DDCLIP__

