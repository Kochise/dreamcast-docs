// ddlisdoc.h : interface of the CDdlistDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CDdlistDoc : public CDocument
{
protected: // create from serialization only
    CDdlistDoc();
    DECLARE_DYNCREATE(CDdlistDoc)

// Attributes
public:

// Operations
public:

// Implementation
public:
    virtual ~CDdlistDoc();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
protected:
    virtual BOOL    OnNewDocument();

public:
    CStrList m_StrList; // List of strings

// Generated message map functions
protected:
    //{{AFX_MSG(CDdlistDoc)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
