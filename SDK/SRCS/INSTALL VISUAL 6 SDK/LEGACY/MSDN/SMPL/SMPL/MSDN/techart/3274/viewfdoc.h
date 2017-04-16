// viewfdoc.h : interface of the CViewfileDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CViewfileDoc : public CDocument
{
protected: // create from serialization only
	CViewfileDoc();
	DECLARE_DYNCREATE(CViewfileDoc)

// Attributes
private:
 CString *m_csFileName;
 HANDLE m_hFile;
 HANDLE m_hFileMapping;
 BYTE *m_lpImage;
 int m_iCurrentPointer, m_iFileSize;
 CView *m_AssociatedView;
 CFrameWnd *m_PriorityFrame;
public:
 char szStatusMessage[300];

// Operations
public:

// helper functions

BYTE *AdjustPointerRelative(int iOffset);
BYTE *AdjustPointerAbsolute(int iPosition);
BOOL RetrieveBytesAtCurrentPosition(BYTE *lpTarget, int iLength);
BOOL RetrieveBytesAtAbsolutePosition(BYTE *lpPosition, BYTE *lpTarget, int iLength);
inline int GetCurrentPosition() { return m_iCurrentPointer; };
void ActivateTheRightFrame();
int inline ImageFileLength() {return m_iFileSize;};


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewfileDoc)
	public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszFileName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CViewfileDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CViewfileDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
