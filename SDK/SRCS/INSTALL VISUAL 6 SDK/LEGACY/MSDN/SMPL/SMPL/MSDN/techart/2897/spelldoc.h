// spelldoc.h : interface of the CSpellDoc class
//
/////////////////////////////////////////////////////////////////////////////

#include "wordmap.h"

#define HINT_NEW_WORD        1   // obj is const char* word

class CSpellDoc : public CDocument
{
protected: // create from serialization only
    CSpellDoc();
    DECLARE_DYNCREATE(CSpellDoc)

// Attributes
public:

// Operations
public:
    BOOL AddWord(const char* pszWord, CWave* pWave);
    BOOL DeleteWord(const char* pszWord);
    void PlayWord(const char* pszWord);

// Implementation
public:
    virtual ~CSpellDoc();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
protected:
    virtual BOOL    OnNewDocument();

public:
   CWordMap m_WordMap;


// Generated message map functions
protected:
    //{{AFX_MSG(CSpellDoc)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
