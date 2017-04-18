//////////////////
// Typical view class, nothing special
//
class CMyView : public CView {
	DECLARE_DYNCREATE(CMyView)
public:
	virtual ~CMyView();
	virtual void OnDraw(CDC* pDC);	
	CMyDoc* GetDocument() { return (CMyDoc*)m_pDocument; }
protected:
	CMyView();
	//{{AFX_MSG(CMyView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
