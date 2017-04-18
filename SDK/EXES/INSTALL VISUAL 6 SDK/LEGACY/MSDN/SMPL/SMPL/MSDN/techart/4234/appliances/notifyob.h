// notifyob.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CNotifyListObject command target

class CNotifyListObject : public CCmdTarget
{
	DECLARE_DYNCREATE(CNotifyListObject)
protected:
	CNotifyListObject();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotifyListObject)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CNotifyListObject();

	// Generated message map functions
	//{{AFX_MSG(CNotifyListObject)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CNotifyListObject)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CNotifyListObject)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

    // Declare the interface map for this object
    DECLARE_INTERFACE_MAP()

    BEGIN_INTERFACE_PART(NotifySrc, INotifySrc)
        STDMETHOD(AddUser)(INotify* pNotify, LPVOID pUserInfo);
        STDMETHOD(RemoveUser)(INotify* pNotify);
        STDMETHOD(NotifyAll)();
    END_INTERFACE_PART(NotifySrc)

    CObList m_NotifyList;
};

// Notification info class
class CUserInfo
{
public:
    INotify* pNotify;
    LPVOID pUserInfo;
};

/////////////////////////////////////////////////////////////////////////////
