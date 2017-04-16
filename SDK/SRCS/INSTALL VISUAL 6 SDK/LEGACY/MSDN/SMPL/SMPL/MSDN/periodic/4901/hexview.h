//***********************************************************************
//
//  HexView.h
//
//***********************************************************************

class CHexView : public CScrollView
{
    DECLARE_DYNCREATE (CHexView)

private:
    CFont m_screenFont;
    CFont m_printerFont;

    UINT m_cyScreen;
    UINT m_cyPrinter;
    UINT m_cxOffset;
    UINT m_cxWidth;

    UINT m_nLinesTotal;
    UINT m_nLinesPerPage;

    CHexDoc* GetDocument () { return (CHexDoc*) m_pDocument; }
    void FormatLine (UINT, CString&);
    void PrintPageHeader (CDC*, UINT);
    void PrintPage (CDC*, UINT);

public:
    virtual void OnInitialUpdate ();

protected:
    virtual void OnDraw (CDC*);
    virtual BOOL OnPreparePrinting (CPrintInfo*);
    virtual void OnBeginPrinting (CDC*, CPrintInfo*);
    virtual void OnPrint (CDC*, CPrintInfo*);
    virtual void OnEndPrinting (CDC*, CPrintInfo*);

    afx_msg int OnCreate (LPCREATESTRUCT);
    DECLARE_MESSAGE_MAP ()
};
