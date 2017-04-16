// dldmfdoc.h : interface of the CPetriNetDoc class
//
/////////////////////////////////////////////////////////////////////////////

class matrix;
class CNetView;
class CMatrixView;

class CPetriNetDoc : public CDocument
{
private:

matrix *GrabFromFile(LPVOID lpFileView);
void DumpToFile(HANDLE hFile, matrix *mMatrix);

protected: // create from serialization only
	CPetriNetDoc();
	DECLARE_DYNCREATE(CPetriNetDoc)

// Attributes
public:



// Operations
public:

matrix *m_mCurrentMatrix;
CNetView *cnvAttachedView;
CMatrixView *cmvAttachedView;


// Implementation
public:
	virtual CString GrabNameFromNet(BOOL, int);
    void ReflectChanges(void);
    void ConvertMatrixToNet(LPVOID lpFileView,matrix *mMatrix);
	matrix *ConvertNetToMatrix();
	virtual ~CPetriNetDoc();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
    virtual void DeleteContents();
    virtual void UpdateAllViews(CView *pSender, LPARAM lHint=0, CObject* pHint=NULL);

#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:
	virtual	BOOL	OnSaveDocument(const char* pszPathName);
	virtual BOOL    OnOpenDocument(const char* pszPathName);
//	virtual BOOL    OnNewDocument(void);
// Generated message map functions
protected:
	//{{AFX_MSG(CPetriNetDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
