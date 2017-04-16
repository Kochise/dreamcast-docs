// VControlPpg.h : Declaration of the CVControlPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CVControlPropPage : See VControlPpg.cpp.cpp for implementation.

class CVControlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CVControlPropPage)
	DECLARE_OLECREATE_EX(CVControlPropPage)

// Constructor
public:
	CVControlPropPage();

// Dialog Data
	//{{AFX_DATA(CVControlPropPage)
	enum { IDD = IDD_PROPPAGE_VCONTROL };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CVControlPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
