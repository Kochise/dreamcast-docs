// MSJDragPpg.h : Declaration of the CMSJDragPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CMSJDragPropPage : See MSJDragPpg.cpp.cpp for implementation.

class CMSJDragPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMSJDragPropPage)
	DECLARE_OLECREATE_EX(CMSJDragPropPage)

// Constructor
public:
	CMSJDragPropPage();

// Dialog Data
	//{{AFX_DATA(CMSJDragPropPage)
	enum { IDD = IDD_PROPPAGE_MSJDRAG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CMSJDragPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
