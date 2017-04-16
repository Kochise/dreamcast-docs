// DocList.h : header file
//

#define IDC_DOCLIST		0x1000

/////////////////////////////////////////////////////////////////////////////
// CDocList window

class CDocList : public CListBox
{
// Construction
public:
	CDocList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocList)
	public:
	virtual int CharToItem(UINT nKey, UINT nIndex);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDocList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDocList)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
