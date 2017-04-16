// clipdoc.h : interface of the CClipDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CClipDoc : public CDocument
{
protected: // create from serialization only
    CClipDoc();
    DECLARE_DYNCREATE(CClipDoc)

// Attributes
public:

// Operations
public:
   CMyObList* GetObList()
    {return &m_MyObList;}
// Implementation
public:
    virtual ~CClipDoc();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
protected:
    virtual BOOL    OnNewDocument();

private:
    CMyObList m_MyObList;

// Generated message map functions
protected:
    //{{AFX_MSG(CClipDoc)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
