///////////////////////////////////////////////////////////////////////
// This file declares the three views used in VIEW3. There's also a base 
// class for all the views, where common functionality is implemented.
// (E.g. The File Edit command.)

//////////////////
// Base View class
//
class CBaseView : public CView {
   DECLARE_DYNAMIC(CBaseView)
public:
   virtual ~CBaseView();
   CView3Doc*  GetDocument()     { return (CView3Doc*)m_pDocument; }
protected:
   CBaseView();
   //{{AFX_MSG(CBaseView)
   afx_msg void OnFileEdit();    // to edit the contents of the doc
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

////////////////
// Each view class overrides OnDraw to 
// display the document in a different way
//
class CView1 : public CBaseView {
public:
   DECLARE_DYNCREATE(CView1)
   virtual void OnDraw(CDC* pDC);
};

class CView2 : public CBaseView {
public:
   DECLARE_DYNCREATE(CView2)
   virtual void OnDraw(CDC* pDC);
};

class CView3 : public CBaseView {
public:
   DECLARE_DYNCREATE(CView3)
   virtual void OnDraw(CDC* pDC);
};
