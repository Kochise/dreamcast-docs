// animtdoc.h : interface of the CAnimTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CAnimTestView;

class CAnimTestDoc : public CDocument
{
protected: // create from serialization only
    CAnimTestDoc();
    DECLARE_DYNCREATE(CAnimTestDoc)

// Attributes
public:
    CDIB m_dibBkgnd;
    CDIBPal* m_pPal;
    CAnimTestView* GetView();

// Operations
public:
    BOOL Restart(int w, int h);

// Implementation
public:
    virtual ~CAnimTestDoc();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
protected:
    virtual BOOL    OnNewDocument();


// Generated message map functions
protected:
    //{{AFX_MSG(CAnimTestDoc)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
