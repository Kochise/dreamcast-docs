////////////////////////////////////////////////////////////////
// Definition for CDynViewDocTemplate, a document template class that
// implements "dynamic views", i.e., the ability to change the view
// class dynamically, while the app is running. See DynTempl.cpp.
// CDynViewDocTemplate is designed to work in a MDI app.
//
// Copyright 1996 Microsoft Systems Journal. If this code works, 
// it was written by Paul DiLascia. If not, I don't know who wrote it.

////////////////
// This structure associates a view class with 
// a display name and index (position in table).
//
struct DYNAMICVIEWINFO {
   CRuntimeClass* rtc;     // MFC runtime class
   LPCSTR         name;    // display name of view
};

//////////////////
// CDynViewDocTemplate manages multiple views of the same doc. 
// It handles the "View As" commands, and restoring of initial 
// view when a document is loaded.
//
class CDynViewDocTemplate : public CMultiDocTemplate {
public:
   CDynViewDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
      CRuntimeClass* pFrameClass, 
      const DYNAMICVIEWINFO* pViewInfo);
   virtual ~CDynViewDocTemplate();

   virtual void InitialUpdateFrame(CFrameWnd* pFrame, CDocument* pDoc,
      BOOL bMakeVisible = TRUE);

   int GetViewID(CDocument *pDoc);  // <== NOTE: You must implement this!
   int GetViewID(CView* pView);
   const DYNAMICVIEWINFO* GetViewInfo(CView* pView);

protected:
   DECLARE_DYNAMIC(CDynViewDocTemplate)
   const DYNAMICVIEWINFO*  m_pViewInfo;
   UINT                    m_nViewClasses;

   // Helper fn to change the view
   CView* ReplaceView(CFrameWnd* pFrame, int iNewView, BOOL bMakeVis=TRUE);

   //{{AFX_MSG(CDynViewDocTemplate)
   afx_msg BOOL OnViewAs(UINT nCmdID);
   afx_msg void OnUpdateViewAs(CCmdUI* pCmdUI);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
