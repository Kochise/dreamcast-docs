// callbppg.h : Declaration of the CCallBackPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CCallBackPropPage : See callbppg.cpp for implementation.

class CCallBackPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CCallBackPropPage)
	DECLARE_OLECREATE_EX(CCallBackPropPage)

// Constructor
public:
	CCallBackPropPage();

// Dialog Data
	//{{AFX_DATA(CCallBackPropPage)
	enum { IDD = IDD_PROPPAGE_CALLBACK };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CCallBackPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
