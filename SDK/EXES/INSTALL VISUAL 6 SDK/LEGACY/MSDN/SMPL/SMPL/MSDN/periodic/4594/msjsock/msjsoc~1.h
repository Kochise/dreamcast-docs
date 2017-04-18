// MSJSockPpg.h : Declaration of the CMSJSockPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CMSJSockPropPage : See MSJSockPpg.cpp.cpp for implementation.

class CMSJSockPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMSJSockPropPage)
	DECLARE_OLECREATE_EX(CMSJSockPropPage)

// Constructor
public:
	CMSJSockPropPage();

// Dialog Data
	//{{AFX_DATA(CMSJSockPropPage)
	enum { IDD = IDD_PROPPAGE_MSJSOCK };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CMSJSockPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
