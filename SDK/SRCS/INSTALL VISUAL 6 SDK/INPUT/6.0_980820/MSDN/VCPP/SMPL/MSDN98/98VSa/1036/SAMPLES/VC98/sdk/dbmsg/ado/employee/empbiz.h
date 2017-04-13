// EmpBiz.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEmpBiz dialog

class CEmpBiz 
{
// Construction
public:
	CEmpBiz();	// standard constructor
	~CEmpBiz();

// Attributes
public:
	ADORecordset*	m_piEmpRecordSet;
	BOOL			m_fConnected;
	BOOL			m_fRecordsetEmpty;

protected:
	ADOConnection*		m_piConnection;
	COleVariant			m_varLastGoodRecord;

// Operations
public:
	BOOL	ConnectToDatabase(); //Opens a database 
	long	GetEmployeeId(); 
	CString GetFirstName(); 
	CString GetLastName(); 
	CString GetHomePhone() ;
	CString GetTitle() ;
	void	AddRecord() ;
	void	DeleteRecord(); 
	BOOL	MoveNext() 	;
	BOOL	MovePrevious(); 	  
	BOOL	MoveFirst() ;
	BOOL	MoveLast(); 
	BOOL	FindForward(CString strCriteria) ;
	void	ClearFilter(); 
	BOOL	IsAddMode(); 
	void	UpdateEmpRec(CString &strFirstName, 
						CString &strHomePhone, CString &strLastName,
						CString &strTitle);
	void	CancelPendingAdd();
};

void PopupErrorMessage(HRESULT hr);

#define EMP_EMPLOYEE_ID		L"EmployeeID"
#define	EMP_LAST_NAME		L"LastName"
#define	EMP_FIRST_NAME		L"FirstName"
#define EMP_TITLE			L"Title"
#define EMP_HOME_PHONE		L"HomePhone"
