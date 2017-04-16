//////////////////
// Typical document class, nothing special
//
class CMyDoc : public CDocument {
	DECLARE_DYNCREATE(CMyDoc)
public:
	virtual ~CMyDoc();
protected:
	CMyDoc();
	//{{AFX_MSG(CMyDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
