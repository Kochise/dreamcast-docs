// ClientView.cpp : implementation of the CClientView class
//

#include "stdafx.h"
#include "SIClient.h"

#include "SIClientDoc.h"
#include "SIClientView.h"

#include "SimpleObject\GUIDS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientView

IMPLEMENT_DYNCREATE(CClientView, CView)

BEGIN_MESSAGE_MAP(CClientView, CView)
	//{{AFX_MSG_MAP(CClientView)
	ON_COMMAND(ID_OBJECT_CREATE, OnObjectCreate)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_CREATE, OnUpdateObjectCreate)
	ON_COMMAND(ID_OBJECT_INCREMENT, OnObjectIncrement)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_INCREMENT, OnUpdateObjectIncrement)
	ON_COMMAND(ID_OBJECT_RELEASE, OnObjectRelease)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_RELEASE, OnUpdateObjectRelease)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientView construction/destruction

CClientView::CClientView()
{
   //m_pISimple = NULL ; //SM - not needed with smart interface pointers
}

CClientView::~CClientView()
{
      //if (m_pISimple != NULL) m_pISimple->Release() ; //SM not needed

}

BOOL CClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CClientView drawing

void CClientView::OnDraw(CDC* pDC)
{
   CString aString ;
   //if (m_pISimple != NULL) //SM 
   if (m_SISimple != NULL)	//SM - operator!= must be overriden for this to work.
   {
      //int i = m_pISimple->GetCount() ;
	   int i = m_SISimple->GetCount() ;
      aString.Format("Count: %d", i) ;
   }
   else
   {
      aString = "Count: xxxx          " ;
   }

   pDC->TextOut(20,20, aString) ;
}

/////////////////////////////////////////////////////////////////////////////
// CClientView diagnostics

#ifdef _DEBUG
void CClientView::AssertValid() const
{
	CView::AssertValid();
}

void CClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClientDoc* CClientView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClientDoc)));
	return (CClientDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClientView message handlers

void CClientView::OnObjectCreate() 
{
  // IUnknown* pIUnknown = NULL ;
   CSmartInterface<IUnknown> SIUnknown ;

    HRESULT hr = ::CoCreateInstance(CLSID_SimpleObject,
                                    NULL, 
                                    CLSCTX_INPROC_SERVER,
                                    IID_IUnknown,
                                    (void**)&SIUnknown); //SM operator& must be defined
    if (FAILED(hr)) {
        TRACE("Failed to create object. SCODE: %8.8lXH (%lu)\n",
              GetScode(hr),
              GetScode(hr) & 0x0000FFFF);
        //pIUnknown = NULL; //SM - not needed
        return;
    }
    //ASSERT(pIUnknown);
	ASSERT(SIUnknown) ; // SM - Conversion operator needed.

    // Get a pointer to the ISimple interface
    //ASSERT(m_pISimple == NULL) ;
	ASSERT(m_SISimple == NULL) ;	//SM - operator== must be defined.

#ifdef _DEBUG
      // SMTest various equality operators
    ASSERT(!m_SISimple) ; //SM - check operator!.
#endif

    if (SIUnknown->QueryInterface(IID_ISimple, (void**)&m_SISimple) != S_OK) {
        TRACE("ISimple not supported");
        m_SISimple = NULL ; //SM - not needed but okay.
        return;
    }

	ASSERT(m_SISimple) ;
#ifdef _DEBUG
      // Test various equality operators
    ASSERT(m_SISimple != NULL) ; //SM - check operator!=
#endif

    m_SISimple->SetCount(10) ;

   Invalidate() ;
   UpdateWindow() ;
}

void CClientView::OnUpdateObjectCreate(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_SISimple == NULL) ;
}

void CClientView::OnObjectIncrement() 
{
   m_SISimple->Inc() ;

   /* Show how to use a CSmartInterface as a pointer
   typedef CSmartInterface<ISimple> CSmartISimple ;
   CSmartISimple* pSISimple = new CSmartISimple(m_pISimple) ;
   (*pSISimple)->Inc() ;
   delete pSISimple ;
   */

   Invalidate() ;
   UpdateWindow() ;
}

void CClientView::OnUpdateObjectIncrement(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_SISimple != NULL) ;
}

void CClientView::OnObjectRelease() 
{
   
   //m_pISimple->Release() ;
   m_SISimple = NULL ;	// SM - DON'T CALL RELEASE. This will result in
						// calling Release.
   
   Invalidate() ;
   UpdateWindow() ;
}

void CClientView::OnUpdateObjectRelease(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_SISimple != NULL) ;
}
