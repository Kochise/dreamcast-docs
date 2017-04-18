//////////////////
// Document class holds a string of text and what 
// kind of view last viewed the doc.
//
class CView3Doc : public CDocument {
   DECLARE_DYNCREATE(CView3Doc)
public:
   virtual  ~CView3Doc();
   void     SetText(const char* pszText);
   LPCSTR   GetText()      { return m_sText; }
   int      GetViewID()    { return m_nViewID; }
   virtual  void Serialize(CArchive& ar);
protected:
   CView3Doc();
   CString  m_sText;       // contents of doc
   int      m_nViewID;     // identifies view that last saved the doc
   //{{AFX_MSG(CView3Doc)
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

