// commcdoc.h : interface of the CCommchatDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CWriterView;
class CReaderView;
class CChatProtocol;

class CCommchatDoc : public CDocument
{
friend class CReaderView;
friend class CWriterView;

protected: // create from serialization only
	CCommchatDoc();
	DECLARE_DYNCREATE(CCommchatDoc)

// Attributes
private:

// Operations
public:
    BOOL m_bAreWeServer;
	CChatProtocol *cpProtocol;

// Implementation
public:
    CWriterView *m_WriterView;
	CReaderView *m_ReaderView;

	BOOL SetReaderCommunicationObject(CChatProtocol *,BOOL);

	virtual ~CCommchatDoc();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:


	virtual	BOOL	OnNewDocument();
    virtual BOOL    OnOpenDocument(const char* pszPathName);

// Generated message map functions
protected:
	//{{AFX_MSG(CCommchatDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
