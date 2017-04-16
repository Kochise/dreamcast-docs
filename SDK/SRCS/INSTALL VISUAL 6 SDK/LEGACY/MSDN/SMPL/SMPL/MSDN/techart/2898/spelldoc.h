// spelldoc.h : interface of the CSpellerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#include "wordmap.h"

// Hints for OnUpdate
#define HINT_NEWWORD 1

class CSpellerDoc : public CDocument
{
protected: // create from serialization only
    CSpellerDoc();
    DECLARE_DYNCREATE(CSpellerDoc)

// Attributes
public:

// Operations
public:
    CString* GetNextWord();
    CString* GetCurrentWord()
        {return &m_strCurrentWord;}
    CWave* GetCurrentWave()
        {return m_pCurrentWave;}

// Implementation
public:
    virtual ~CSpellerDoc();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
protected:
    virtual BOOL    OnNewDocument();

private:
   CWordMap m_WordMap;
   POSITION m_posCurrent;
   CString m_strCurrentWord;
   CWave* m_pCurrentWave;

// Generated message map functions
protected:
    //{{AFX_MSG(CSpellerDoc)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
