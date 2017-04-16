class CDAOEMPDoc : public COleDocument {
protected:
   CDAOEMPDoc();
   DECLARE_DYNCREATE(CDAOEMPDoc)

   CdbDBEngine    m_cDBEngine;
   CdbDatabase    m_cEmpDatabase;
   CdbBookmark    m_cLastGoodRecord;

public:
   CdbRecordset   m_cEmpRecordSet;
   BOOL           m_bConnected;
   BOOL ConnectToDatabase(); //Opens a database 

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CDAOEMPDoc)
   public:
   virtual BOOL OnNewDocument();
   //}}AFX_VIRTUAL

public:
   virtual ~CDAOEMPDoc();
   virtual void Serialize(CArchive& ar);   // overridden for document i/o
   BOOL OKToMove();

   void UpdateEmpRec(long m_nEmpNum, LPCTSTR lpszFirstName, 
         LPCTSTR lpszHomePhone, LPCTSTR lpszLastName, 
         LPCTSTR lpszNotes, DATE HireDate);

protected:
   //{{AFX_MSG(CDAOEMPDoc)
   afx_msg void OnEditNext();
   afx_msg void OnEditPrevious();
   afx_msg void OnEditAdd();
   afx_msg void OnEditDelete();
   afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
