//////////////////
// Three views: one for each doc.
//
// CBaseView is never instantiated since CBaseDoc is an abstract class,
// but it's better to have a common base for the views as well as
// docs because there may be common functionality. Also, you may want to get
// the view associated with a CBaseDoc and treat it as a CBaseView.
//

class CBaseView : public CView {
   DECLARE_DYNAMIC(CBaseView)
protected:
   CBaseView() { }
   CBaseDoc* GetDocument() { return (CBaseDoc*)m_pDocument; }
public:
   virtual void OnDraw(CDC* pDC);
};

class CViewA : public CBaseView {
   DECLARE_DYNCREATE(CViewA)
protected:
   CViewA() { }
   CDocA* GetDocument() { return (CDocA*)m_pDocument; }
public:
   virtual void OnDraw(CDC* pDC);
};

class CViewB : public CBaseView {
   DECLARE_DYNCREATE(CViewB)
protected:
   CViewB() { }
   CDocB* GetDocument() { return (CDocB*)m_pDocument; }
public:
   virtual void OnDraw(CDC* pDC);
};
