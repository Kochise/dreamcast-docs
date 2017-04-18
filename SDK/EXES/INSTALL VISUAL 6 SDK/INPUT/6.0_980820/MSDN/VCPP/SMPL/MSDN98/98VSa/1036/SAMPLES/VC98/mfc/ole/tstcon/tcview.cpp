// CTestContainer98View.cpp : implementation of the CTestContainer98View class
//

#include "StdAfx.H"
#include "TestCon.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestContainer98View

IMPLEMENT_DYNCREATE( CTestContainer98View, CView )

BEGIN_MESSAGE_MAP( CTestContainer98View, CView )
   //{{AFX_MSG_MAP(CTestContainer98View)
   ON_WM_DESTROY()
   ON_WM_SETFOCUS()
   ON_WM_SIZE()
   ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
   ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONDBLCLK()
   ON_WM_SETCURSOR()
   ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
   ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR, OnUpdateEditClear)
   ON_WM_RBUTTONDOWN()
   ON_COMMAND(ID_OPTIONS_DESIGNMODE, OnOptionsDesignMode)
   ON_UPDATE_COMMAND_UI(ID_OPTIONS_DESIGNMODE, OnUpdateOptionsDesignMode)
   ON_WM_CREATE()
   ON_WM_LBUTTONUP()
   ON_WM_MOUSEMOVE()
   ON_WM_RBUTTONDBLCLK()
   ON_WM_RBUTTONUP()
   ON_WM_CAPTURECHANGED()
   ON_WM_KILLFOCUS()
   ON_WM_KEYDOWN()
   ON_WM_KEYUP()
   ON_WM_CHAR()
   ON_WM_CANCELMODE()
   ON_COMMAND(ID_CONTROL_SAVETOSTREAM, OnControlSaveToStream)
   ON_COMMAND(ID_EDIT_INSERTFROMSTREAM, OnEditInsertFromStream)
	ON_COMMAND(ID_CONTROL_SAVETOPROPERTYBAG, OnControlSaveToPropertyBag)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_SAVETOPROPERTYBAG, OnUpdateControlSaveToPropertyBag)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_SAVETOSTREAM, OnUpdateControlSaveToStream)
	ON_COMMAND(ID_CONTROL_INVOKEMETHODS, OnControlInvokeMethods)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_INVOKEMETHODS, OnUpdateControlInvokeMethods)
	ON_COMMAND(ID_CONTROL_LOGGING, OnControlLogging)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_LOGGING, OnUpdateControlLogging)
	ON_COMMAND(ID_CONTROL_ACTIVATE, OnControlActivate)
	ON_COMMAND(ID_CONTROL_DEACTIVATE, OnControlDeactivate)
	ON_COMMAND(ID_CONTROL_UIACTIVATE, OnControlUIActivate)
	ON_COMMAND(ID_CONTROL_UIDEACTIVATE, OnControlUIDeactivate)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_UIDEACTIVATE, OnUpdateControlUIDeactivate)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_UIACTIVATE, OnUpdateControlUIActivate)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_ACTIVATE, OnUpdateControlActivate)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_DEACTIVATE, OnUpdateControlDeactivate)
	ON_COMMAND(ID_EDIT_BRINGTOFRONT, OnEditBringToFront)
	ON_UPDATE_COMMAND_UI(ID_EDIT_BRINGTOFRONT, OnUpdateEditBringToFront)
	ON_COMMAND(ID_EDIT_SENDTOBACK, OnEditSendToBack)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SENDTOBACK, OnUpdateEditSendToBack)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_PROPERTIES, OnEditProperties)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PROPERTIES, OnUpdateEditProperties)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectAll)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_TOOLS_OLEVIEW, OnToolsOLEView)
	ON_COMMAND(ID_TOOLS_REGEDIT, OnToolsRegEdit)
	ON_COMMAND(ID_CONTROL_SAVETOSTORAGE, OnControlSaveToStorage)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_SAVETOSTORAGE, OnUpdateControlSaveToStorage)
	ON_COMMAND(ID_EDIT_INSERTCONTROLFROMSTORAGE, OnEditInsertControlFromStorage)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECTALL, OnUpdateEditSelectAll)
	ON_COMMAND(ID_CONTROL_DRAWMETAFILE, OnControlDrawMetaFile)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_DRAWMETAFILE, OnUpdateControlDrawMetaFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CLIPFORMAT CTestContainer98View::s_cfObjectDescriptor = NULL;

/////////////////////////////////////////////////////////////////////////////
// CTestContainer98View construction/destruction

CTestContainer98View::CTestContainer98View() :
   m_pSelection( NULL ),
//   m_tDoingDrag( FALSE ),
   m_pItemWithCapture( NULL ),
   m_pItemWithFocus( NULL ),
   m_pItemToDeactivateOnLeave( NULL ),
   m_pInactiveDropTarget( NULL ),
   m_pWindowlessDropTarget( NULL ),
   m_dwLastDropKeyState( 0 )
{
   if( s_cfObjectDescriptor == NULL )
   {
	  s_cfObjectDescriptor = CLIPFORMAT( ::RegisterClipboardFormat( _T(
		 "Object Descriptor" ) ) );
   }
}

CTestContainer98View::~CTestContainer98View()
{
}

BOOL CTestContainer98View::PreCreateWindow( CREATESTRUCT& cs )
{
   cs.style |= WS_CLIPCHILDREN;

   return( CView::PreCreateWindow( cs ) );
}

void CTestContainer98View::ClearSelection()
{
   m_pSelection = NULL;
   m_lpSelectedItems.RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////
// CTestContainer98View drawing

void CTestContainer98View::OnDraw( CDC* pDC )
{
   POSITION posItem;
   CTestContainer98Doc* pDoc;
   CTestContainer98Item* pItem;

   pDoc = GetDocument();
   ASSERT_VALID( pDoc );

   if( pDoc->UseTwoPassDrawing() )
   {
	  // Draw the opaque parts of the controls from front to back.
	  TCTrace( TRACELEVEL_VERBOSE, "Starting drawing pass 1.\n" );
	  posItem = pDoc->GetStartPosition();
	  while( posItem != NULL )
	  {
		 pItem = (CTestContainer98Item*)pDoc->GetNextItem( posItem );

		 // Push the state of the DC onto the stack.  This is to save the
		 // current clip region for when we do the second pass.
		 pDC->SaveDC();

		 // The item will exclude any opaque areas from the clip region of the
		 // DC.
		 pItem->DrawFrontToBack( pDC, pItem->m_rect );

		 if( pDoc->UseSlowDrawing() )
		 {
			Sleep( 1000 );
		 }
	  }

	  // Draw the rest of each control from back to front, clipping out opaque
	  // regions of any controls in front.
	  TCTrace( TRACELEVEL_VERBOSE, "Starting drawing pass 2.\n" );
	  posItem = pDoc->GetTailPosition();
	  while( posItem != NULL )
	  {
		 pItem = (CTestContainer98Item*)pDoc->GetPrevItem( posItem );

		 // Draw the tracker for the item.
		 CRectTracker tracker;
		 SetupTracker( pItem, &tracker );
		 tracker.Draw( pDC );

		 // Pop the state of the DC off the stack.  This makes sure the
		 // clipping region excludes only the opaque regions of all the
		 // controls in front of this one.
		 pDC->RestoreDC( -1 );

		 pItem->DrawBackToFront( pDC, pItem->m_rect );

		 if( pDoc->UseSlowDrawing() )
		 {
			Sleep( 1000 );
		 }
	  }
   }
   else
   {
	  // Draw the OLE items from the list.
	  posItem = pDoc->GetTailPosition();
	  while( posItem != NULL )
	  {
		 pItem = (CTestContainer98Item*)pDoc->GetPrevItem( posItem );

		 // Draw the tracker for the item.
		 CRectTracker tracker;
		 SetupTracker( pItem, &tracker );
		 tracker.Draw( pDC );

		 // Draw the item.
		 pItem->Draw( pDC, pItem->m_rect );

		 if( pDoc->UseSlowDrawing() )
		 {
			Sleep( 1000 );
		 }
	  }
   }
}

void CTestContainer98View::OnInitialUpdate()
{
   CView::OnInitialUpdate();

   m_pSelection = NULL;
   m_lpSelectedItems.RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////
// CTestContainer98View printing

void CTestContainer98View::OnDestroy()
{
   // Deactivate the item on destruction; this is important
   // when a splitter view is being used.
   CView::OnDestroy();

   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem( this );
   if( (pActiveItem != NULL) && (pActiveItem->GetActiveView() == this) )
   {
	  pActiveItem->Deactivate();
	  ASSERT( GetDocument()->GetInPlaceActiveItem( this ) == NULL );
   }
}


/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CTestContainer98View::IsSelected( const CObject* pDocItem ) const
{
   // The implementation below is adequate if your selection consists of
   //  only CTestContainer98Item objects.  To handle different selection
   //  mechanisms, the implementation here should be replaced.

   // TODO: implement this function that tests for a selected OLE client item

   return( pDocItem == m_pSelection );
}

void CTestContainer98View::OnInsertObject()
{
   CTestContainer98Item* pItem;
   CTestContainer98Doc* pDoc;
   CInsertControlDlg dlg;
   int nResult;

   nResult = dlg.DoModal();
   if( nResult != IDOK )
   {
	  return;
   }

   BeginWaitCursor();

   pItem = NULL;
   try
   {
	  // Create new item connected to this document.
	  pDoc = GetDocument();

	  pItem = pDoc->AddControl( dlg.m_clsid, NULL );
	  ASSERT_VALID( pItem );

	  // As an arbitrary user interface design, this sets the selection to the
	  // last item inserted.

	  SetSelection( pItem );

	  pItem->InvalidateItem();
   }
   catch( COleException* pException )
   {
	  CString strErrorMessage;
	  _com_error error( pException->m_sc );

	  pException->Delete();

	  if( pItem != NULL )
	  {
		 ASSERT_VALID( pItem );
		 pItem->Delete();
	  }

	  AfxFormatString1( strErrorMessage, IDS_CREATEFAILED,
		 error.ErrorMessage() );

	  AfxMessageBox( strErrorMessage );
   }
   catch( CException* pException )
   {
	  pException->Delete();

	  if( pItem != NULL )
	  {
		 ASSERT_VALID( pItem );
		 pItem->Delete();
	  }

	  AfxMessageBox( IDP_FAILED_TO_CREATE );
   }

   EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CTestContainer98View::OnCancelEditCntr()
{
   // Close any in-place active item on this view.
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem( this );
   if( pActiveItem != NULL )
   {
	  pActiveItem->Close();
   }
   ASSERT( GetDocument()->GetInPlaceActiveItem( this ) == NULL );
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CTestContainer98View::OnSetFocus( CWnd* pOldWnd )
{
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem( this );
   if( (pActiveItem != NULL) && (pActiveItem->GetItemState() ==
	  COleClientItem::activeUIState) )
   {
	  // need to set focus to this item if it is in the same view
	  CWnd* pWnd = pActiveItem->GetInPlaceWindow();
	  if( pWnd != NULL )
	  {
		 pWnd->SetFocus();   // don't call the base class
		 return;
	  }
   }

   CView::OnSetFocus( pOldWnd );
}

void CTestContainer98View::OnSize( UINT nType, int cx, int cy )
{
   COleClientItem* pActiveItem;

   CView::OnSize( nType, cx, cy );

   pActiveItem = GetDocument()->GetInPlaceActiveItem( this );
   if( pActiveItem != NULL )
   {
	  pActiveItem->SetItemRects();
   }
}

/////////////////////////////////////////////////////////////////////////////
// CTestContainer98View diagnostics

#ifdef _DEBUG
void CTestContainer98View::AssertValid() const
{
   CView::AssertValid();
}

void CTestContainer98View::Dump( CDumpContext& dc ) const
{
   CView::Dump( dc );
}

// non-debug version is inline.
CTestContainer98Doc* CTestContainer98View::GetDocument()
{
   ASSERT( m_pDocument->IsKindOf( RUNTIME_CLASS( CTestContainer98Doc ) ) );
   return( (CTestContainer98Doc*)m_pDocument );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestContainer98View message handlers

// Method: HitTestItems
// Description: Determines the topmost item that contains the given point.
// Parameters:
//    point - (IN) The point to hit test.
//    pdwHitType - (OUT) Which part of the item was hit.  Possible values are:
//       HITTYPE_NONE - No item was hit.
//       HITTYPE_OBJECT - The item itself was hit.
//       HITTYPE_BORDER - The grab border of the item was hit.
// Return Value: Topmost item containing the point, or NULL if the point is not
//    inside any of the items.
CTestContainer98Item* CTestContainer98View::HitTestItems( CPoint point,
   DWORD* pdwHitType )
{
   CTestContainer98Doc* pDoc;
   CTestContainer98Item* pItem;
   POSITION posItem;
   CRect rectBorder;
   DWORD dwHitResult;

   pDoc = GetDocument();

   *pdwHitType = HITTYPE_NONE;  // Assume that we don't hit anything.

   // Traverse the list of controls from front to back.
   posItem = pDoc->GetStartPosition();
   while( posItem != NULL )
   {
	  pItem = (CTestContainer98Item*)pDoc->GetNextItem( posItem );
	  dwHitResult = pItem->HitTest( point );
	  if( dwHitResult == HITRESULT_HIT )
	  {
		 // We hit the control itself.
		 *pdwHitType = HITTYPE_OBJECT;
		 return( pItem );
	  }
	  else
	  {
		 // We missed the control, so check the grab border that we added to
		 // it.
		 rectBorder = pItem->m_rect;
		 rectBorder.InflateRect( MARGIN_PIXELS, MARGIN_PIXELS );
		 if( rectBorder.PtInRect( point ) && !pItem->m_rect.PtInRect( point ) )
		 {
			// The point is outside the item's bounding rectangle, but inside
			// the border rect.
			*pdwHitType = HITTYPE_BORDER;
			return( pItem );
		 }
	  }
   }

   return( NULL );
}

void CTestContainer98View::SetMultiSelect( CTestContainer98Item* pItem,
   BOOL tSelect )
{
   POSITION posItem;

   ASSERT( pItem != NULL );

   posItem = m_lpSelectedItems.Find( pItem );
   if( tSelect )
   {
	  if( posItem != NULL )
	  {
		 // Already selected
		 return;
	  }
	  else
	  {
		 m_lpSelectedItems.AddHead( pItem );
		 if( m_lpSelectedItems.GetCount() == 1 )
		 {
			ASSERT( m_pSelection == NULL );
			m_pSelection = pItem;
			m_pSelection->OnSelect();
		 }
		 else
		 {
			if( m_pSelection != NULL )
			{
			   OnUpdate( NULL, HINT_UPDATE_ITEM, m_pSelection );
			   m_pSelection->OnDeselect();
			   m_pSelection = NULL;
			}
		 }
		 OnUpdate( NULL, HINT_UPDATE_ITEM, pItem );
	  }
   }
   else
   {
	  if( posItem == NULL )
	  {
		 // Already not selected
		 return;
	  }
	  else
	  {
		 if( m_pSelection == pItem )
		 {
			ASSERT( m_lpSelectedItems.GetCount() == 1 );
			m_pSelection->OnDeselect();
			m_pSelection = NULL;
		 }
		 m_lpSelectedItems.RemoveAt( posItem );
		 if( m_lpSelectedItems.GetCount() == 1 )
		 {
			ASSERT( m_pSelection == NULL );
			m_pSelection = m_lpSelectedItems.GetHead();
			m_pSelection->OnSelect();
			OnUpdate( NULL, HINT_UPDATE_ITEM, m_pSelection );
		 }
		 OnUpdate( NULL, HINT_UPDATE_ITEM, pItem );
	  }
   }
}

void CTestContainer98View::ToggleMultiSelect( CTestContainer98Item* pItem )
{
   POSITION posItem;

   ASSERT( pItem != NULL );

   posItem = m_lpSelectedItems.Find( pItem );
   if( posItem == NULL )
   {
	  m_lpSelectedItems.AddHead( pItem );
	  if( m_lpSelectedItems.GetCount() == 1 )
	  {
		 ASSERT( m_pSelection == NULL );
		 m_pSelection = pItem;
		 m_pSelection->OnSelect();
	  }
	  else
	  {
		 if( m_pSelection != NULL )
		 {
			m_pSelection->OnDeselect();
			m_pSelection = NULL;
		 }
	  }
   }
   else
   {
	  if( m_pSelection == pItem )
	  {
		 ASSERT( m_lpSelectedItems.GetCount() == 1 );
		 m_pSelection->OnDeselect();
		 m_pSelection = NULL;
	  }
	  m_lpSelectedItems.RemoveAt( posItem );
	  if( m_lpSelectedItems.GetCount() == 1 )
	  {
		 ASSERT( m_pSelection == NULL );
		 m_pSelection = m_lpSelectedItems.GetHead();
		 m_pSelection->OnSelect();
	  }
   }
   OnUpdate( NULL, HINT_UPDATE_ITEM, pItem );
}

void CTestContainer98View::SetSelection( CTestContainer98Item* pItem )
{
   CTestContainer98Item* pSelectedItem;

   if( (pItem != NULL ) && (m_pSelection == pItem) )
   {
	  // No change in selection
	  return;
   }

   if( m_pSelection != NULL )
   {
	  m_pSelection->OnDeselect();
	  m_pSelection = NULL;
   }

   while( !m_lpSelectedItems.IsEmpty() )
   {
	  pSelectedItem = m_lpSelectedItems.RemoveHead();
	  if( pSelectedItem != pItem )
	  {
		 OnUpdate( NULL, HINT_UPDATE_ITEM, pSelectedItem );
	  }
   }

   if( pItem != NULL )
   {
	  m_lpSelectedItems.AddHead( pItem );
	  m_pSelection = pItem;
	  m_pSelection->OnSelect();
	  OnUpdate( NULL, HINT_UPDATE_ITEM, pItem );
   }
}

BOOL CTestContainer98View::HandleWindowlessKeyboardMessage()
{
   if( m_pItemWithFocus != NULL )
   {
	  if( m_pItemWithFocus->IsWindowless() )
	  {
		 m_pItemWithFocus->OnWindowMessage( GetCurrentMessage() );
		 return( TRUE );
	  }
   }

   return( FALSE );
}

BOOL CTestContainer98View::HandlePointerInactiveMove( CPoint point,
   DWORD dwKeyState )
{
   CTestContainer98Item* pItemHit;
   CRect rect;
   BOOL tHandled;
   DWORD dwPolicy;
   MSG msg;
   DWORD dwHitType;

   if( !GetDocument()->UseIPointerInactive() )
   {
	  return( FALSE );
   }

   tHandled = FALSE;

   pItemHit = HitTestItems( point, &dwHitType );
   if( (dwHitType != HITTYPE_OBJECT) || !pItemHit->SupportsIPointerInactive() )
   {
	  pItemHit = NULL;
   }

   if( m_pItemToDeactivateOnLeave != NULL )
   {
	  // We have an active object that wants to be deactivated as soon as the
	  // mouse leaves its extents.
	  if( m_pItemToDeactivateOnLeave != pItemHit )
	  {
		 TCTrace( TRACELEVEL_NORMAL,
			"Deactivating item because of POINTERINACTIVE_DEACTIVATEONLEAVE.\n" );
		 m_pItemToDeactivateOnLeave->Deactivate();
		 m_pItemToDeactivateOnLeave = NULL;
	  }
   }

   if( pItemHit != NULL )
   {
	  if( !pItemHit->IsInPlaceActive() )
	  {
		 // The mouse was over an inactive control that wants to receive mouse
		 // pointer messages, so send the message to that control first.
		 dwPolicy = pItemHit->OnPointerInactiveMove( point, dwKeyState );
		 if( dwPolicy&POINTERINACTIVE_ACTIVATEONENTRY )
		 {
			msg = *GetCurrentMessage();
			TCTrace( TRACELEVEL_NORMAL,
			   "Activating item because of POINTERINACTIVE_ACTIVATEONENTRY.\n" );
			pItemHit->Activate( OLEIVERB_SHOW, this, &msg );
			if( dwPolicy&POINTERINACTIVE_DEACTIVATEONLEAVE )
			{
			   // The control wants to be deactivated as soon as the mouse
			   // leaves its extents.
			   m_pItemToDeactivateOnLeave = pItemHit;
			}
		 }
		 tHandled = TRUE;
	  }
   }
   else
   {
	  tHandled = FALSE;
   }

   return( tHandled );
}

BOOL CTestContainer98View::HandlePointerInactiveSetCursor(
   DWORD dwMouseMessage )
{
   CTestContainer98Item* pItemHit;
   CRect rect;
   BOOL tHandled;
   DWORD dwPolicy;
   MSG msg;
   CPoint point;
   DWORD dwHitType;

   if( !GetDocument()->UseIPointerInactive() )
   {
	  return( FALSE );
   }

   point = m_ptLastMousePosition;
   pItemHit = HitTestItems( point, &dwHitType );
   if( (dwHitType != HITTYPE_OBJECT) || !pItemHit->SupportsIPointerInactive() )
   {
	  pItemHit = NULL;
   }

   if( m_pItemToDeactivateOnLeave != NULL )
   {
	  // If the pointer is still over the same control, then we really haven't
	  // left it.
	  if( m_pItemToDeactivateOnLeave != pItemHit )
	  {
		 TCTrace( TRACELEVEL_NORMAL,
			"Deactivating item because of POINTERINACTIVE_DEACTIVATEONLEAVE.\n" );
		 m_pItemToDeactivateOnLeave->Deactivate();
		 m_pItemToDeactivateOnLeave = NULL;
	  }
   }

   tHandled = FALSE;
   if( pItemHit != NULL )
   {
	  if( !pItemHit->IsInPlaceActive() )
	  {
		 // The mouse was over an inactive control that wants to receive mouse
		 // pointer messages, so send the message to that control first.
		 dwPolicy = pItemHit->OnPointerInactiveSetCursor( point,
			dwMouseMessage, &tHandled );
		 if( dwPolicy&POINTERINACTIVE_ACTIVATEONENTRY )
		 {
			msg = *GetCurrentMessage();
			TCTrace( TRACELEVEL_NORMAL,
			   "Activating item because of POINTERINACTIVE_ACTIVATEONENTRY.\n" );
			pItemHit->Activate( OLEIVERB_SHOW, this, &msg );
			if( dwPolicy&POINTERINACTIVE_DEACTIVATEONLEAVE )
			{
			   m_pItemToDeactivateOnLeave = pItemHit;
			}
			tHandled = TRUE;
		 }
	  }
   }

   return( tHandled );
}

BOOL CTestContainer98View::HandlePointerInactiveDragOver( CPoint point )
{
   CTestContainer98Item* pItemHit;
   DWORD dwHitType;
   DWORD dwPolicy;
   BOOL tHandled;

   if( !GetDocument()->UseIPointerInactive() )
   {
	  return( FALSE );
   }

   pItemHit = HitTestItems( point, &dwHitType );
   if( (dwHitType != HITTYPE_OBJECT) || !pItemHit->SupportsIPointerInactive() )
   {
	  pItemHit = NULL;
   }

   tHandled = FALSE;
   if( pItemHit != NULL )
   {
	  if( !pItemHit->IsInPlaceActive() )
	  {
		 dwPolicy = pItemHit->GetActivationPolicy();
		 if( dwPolicy&POINTERINACTIVE_ACTIVATEONDRAG )
		 {
			TCTrace( TRACELEVEL_NORMAL,
			   "Activating item because of POINTERINACTIVE_ACTIVATEONDRAG.\n" );
			pItemHit->Activate( OLEIVERB_SHOW, this );
		 }
	  }
   }

   return( tHandled );
}

BOOL CTestContainer98View::HandleWindowlessDragEnter(
   COleDataObject* pDataObject, DWORD dwKeyState, CPoint point,
   DWORD* pdwDropEffect )
{
   CTestContainer98Item* pItemHit;
   DWORD dwHitType;
   BOOL tHandled;

   ASSERT( m_pWindowlessDropTarget == NULL );

   pItemHit = HitTestItems( point, &dwHitType );
   if( (dwHitType != HITTYPE_OBJECT) || !pItemHit->IsWindowless() )
   {
	  pItemHit = NULL;
   }

   tHandled = FALSE;
   if( pItemHit != NULL )
   {
	  tHandled = pItemHit->OnWindowlessDragEnter( pDataObject, dwKeyState,
		 point, pdwDropEffect );
	  if( tHandled )
	  {
		 // Remember which item we're over.
		 m_pWindowlessDropTarget = pItemHit;
	  }
   }

   return( tHandled );
}

BOOL CTestContainer98View::HandleWindowlessDragOver(
   COleDataObject* pDataObject, DWORD dwKeyState, CPoint point,
   DWORD* pdwDropEffect )
{
   CTestContainer98Item* pItemHit;
   DWORD dwHitType;
   BOOL tHandled;

   pItemHit = HitTestItems( point, &dwHitType );
   if( (dwHitType != HITTYPE_OBJECT) || !pItemHit->IsWindowless() )
   {
	  pItemHit = NULL;
   }

   tHandled = FALSE;
   if( m_pWindowlessDropTarget != NULL )
   {
	  // The cursor was previously over a windowless control.
	  if( m_pWindowlessDropTarget != pItemHit )
	  {
		 // The cursor left that windowless control.
		 m_pWindowlessDropTarget->OnWindowlessDragLeave();
		 m_pWindowlessDropTarget = NULL;
	  }
   }

   if( pItemHit != NULL )
   {
	  // The cursor is now over a windowless control.
	  if( pItemHit != m_pWindowlessDropTarget )
	  {
		 // The cursor entered a new windowless control.
		 ASSERT( m_pWindowlessDropTarget == NULL );
		 tHandled = pItemHit->OnWindowlessDragEnter( pDataObject, dwKeyState,
			point, pdwDropEffect );
		 if( tHandled )
		 {
			m_pWindowlessDropTarget = pItemHit;
		 }
	  }
	  else
	  {
		 // The cursor is still over the same windowless control.
		 pItemHit->OnWindowlessDragOver( dwKeyState, point, pdwDropEffect );
		 tHandled = TRUE;
	  }
   }

   return( tHandled );
}

void CTestContainer98View::HandleWindowlessDragLeave()
{
   if( m_pWindowlessDropTarget != NULL )
   {
	  m_pWindowlessDropTarget->OnWindowlessDragLeave();
	  m_pWindowlessDropTarget = NULL;
   }
}

BOOL CTestContainer98View::HandleWindowlessDrop( COleDataObject* pDataObject,
   DWORD dwKeyState, CPoint point, DWORD* pdwEffect )
{
   if( m_pWindowlessDropTarget != NULL )
   {
	  m_pWindowlessDropTarget->OnWindowlessDrop( pDataObject, dwKeyState,
		 point, pdwEffect );
	  m_pWindowlessDropTarget = NULL;
	  return( TRUE );
   }
   else
   {
	  return( FALSE );
   }
}

BOOL CTestContainer98View::HandleWindowlessMouseMessage( CPoint point )
{
   CTestContainer98Item* pItemHit;
   DWORD dwHitType;
   BOOL tHandled;
   CRect rect;

   // First, see if a windowless control has mouse capture.
   if( m_pItemWithCapture != NULL )
   {
	  m_pItemWithCapture->OnWindowMessage( GetCurrentMessage() );
	  return( TRUE );
   }

   // Now, see if we hit a windowless control.
   pItemHit = HitTestItems( point, &dwHitType );
   if( (dwHitType != HITTYPE_OBJECT) || !pItemHit->IsWindowless() )
   {
	  pItemHit = NULL;
   }

   if( pItemHit != NULL )
   {
	  // The mouse was over a windowless control, so send the message to that
	  // control first.
	  tHandled = pItemHit->OnWindowMessage( GetCurrentMessage() );
	  if( !tHandled )
	  {
		 // The windowless control didn't do anything, but we don't want the
		 // container to do anything either.
		 {
			Default();
		 }
	  }
	  return( TRUE );
   }

   return( FALSE );
}

void CTestContainer98View::OnLButtonDown( UINT nFlags, CPoint point )
{
   BOOL tHandled;
   CTestContainer98Item* pItemHit;
   CTestContainer98Item* pItem;
   POSITION posItem;
   DWORD dwHitType;
   int eHitType;
   MSG msg;

   tHandled = HandleWindowlessMouseMessage( point );
   if( tHandled )
   {
	  return;
   }

   pItemHit = HitTestItems( point, &dwHitType );
   if( nFlags&MK_CONTROL )
   {
	  if( pItemHit != NULL )
	  {
		 ToggleMultiSelect( pItemHit );
	  }
   }
   else
   {
	  if( m_lpSelectedItems.Find( pItemHit ) == NULL )
	  {
		 SetSelection( pItemHit );
	  }
   }

   if( (pItemHit != NULL) && (dwHitType != HITTYPE_BORDER) )
   {
	  if( !pItemHit->IsInPlaceActive() )
	  {
		 msg = *GetCurrentMessage();
		 pItemHit->Activate( OLEIVERB_SHOW, this, &msg );
	  }
   }

   if( !m_lpSelectedItems.IsEmpty() )
   {
	  if( dwHitType == HITTYPE_BORDER )
	  {
		 CRectTracker tracker;
		 CPoint ptStart;
		 CSize sizeDisplacement;
		 CRect rectItem;

		 SetupSelectionTracker( &tracker );
		 ptStart = tracker.m_rect.TopLeft();
		 eHitType = tracker.HitTest( point );
		 if( eHitType == CRectTracker::hitMiddle )
		 {
			// Drag the selection
			if( tracker.Track( this, point ) )
			{
			   posItem = m_lpSelectedItems.GetHeadPosition();
			   while( posItem != NULL )
			   {
				  pItem = m_lpSelectedItems.GetNext( posItem );
				  pItem->InvalidateItem();
			   }

			   sizeDisplacement = tracker.m_rect.TopLeft()-ptStart;

			   posItem = m_lpSelectedItems.GetHeadPosition();
			   while( posItem != NULL )
			   {
				  pItem = m_lpSelectedItems.GetNext( posItem );
				  rectItem = pItem->m_rect;
				  rectItem.OffsetRect( sizeDisplacement );
				  pItem->Move( rectItem );
				  pItem->InvalidateItem();
			   }

			   GetDocument()->SetModifiedFlag();
			}
		 }
		 else
		 {
			if( (eHitType != CRectTracker::hitNothing) && (m_pSelection !=
			   NULL) )
			{
			   // Resize the item.
			   if( tracker.Track( this, point ) )
			   {
				  m_pSelection->InvalidateItem();
			   }

			   tracker.m_rect.DeflateRect( MARGIN_PIXELS, MARGIN_PIXELS );
			   m_pSelection->Move( tracker.m_rect );
			   m_pSelection->InvalidateItem();

			   GetDocument()->SetModifiedFlag();
			}
		 }
	  }
   }
   else
   {
	  CRectTracker tracker;
	  CRect rectIntersection;
	  CTestContainer98Doc* pDoc;

	  if( tracker.TrackRubberBand( this, point, TRUE ) )
	  {
		 tracker.m_rect.NormalizeRect();

		 pDoc = GetDocument();
		 posItem = pDoc->GetStartPosition();
		 while( posItem != NULL )
		 {
			pItem = STATIC_DOWNCAST( CTestContainer98Item, pDoc->GetNextItem(
			   posItem ) );
			if( rectIntersection.IntersectRect( tracker.m_rect,
			   pItem->m_rect ) )
			{
			   SetMultiSelect( pItem, TRUE );
			}
		 }
	  }
   }
}

void CTestContainer98View::SetupSelectionTracker( CRectTracker* pTracker )
{
   POSITION posItem;
   CTestContainer98Item* pItem;

   ASSERT( !m_lpSelectedItems.IsEmpty() );
   if( m_pSelection != NULL )
   {
	  // Only one item is selected, so use its tracker.
	  SetupTracker( m_pSelection, pTracker );
   }
   else
   {
	  pTracker->m_rect.SetRectEmpty();
	  posItem = m_lpSelectedItems.GetHeadPosition();
	  while( posItem != NULL )
	  {
		 pItem = m_lpSelectedItems.GetNext( posItem );
		 pTracker->m_rect.UnionRect( pTracker->m_rect, pItem->m_rect );
	  }
	  pTracker->m_rect.InflateRect( MARGIN_PIXELS, MARGIN_PIXELS );
	  pTracker->m_nHandleSize = MARGIN_PIXELS+1;
	  pTracker->m_sizeMin.cx = 8;
	  pTracker->m_sizeMin.cy = 8;
	  pTracker->m_nStyle = CRectTracker::solidLine;
   }
}

void CTestContainer98View::SetupTracker( CTestContainer98Item* pItem,
   CRectTracker* pTracker )
{
   pTracker->m_rect = pItem->m_rect;
   pTracker->m_rect.InflateRect( MARGIN_PIXELS, MARGIN_PIXELS );
   pTracker->m_nHandleSize = MARGIN_PIXELS+1;
   pTracker->m_sizeMin.cx = 8;
   pTracker->m_sizeMin.cy = 8;

   pTracker->m_nStyle = 0;

   if( m_lpSelectedItems.Find( pItem ) != NULL )
   {
	  pTracker->m_nStyle |= CRectTracker::resizeInside;
   }

   pTracker->m_nStyle |= CRectTracker::solidLine;

   if( (pItem->GetItemState() == COleClientItem::openState) ||
	  (pItem->GetItemState() == COleClientItem::activeUIState) )
   {
	  pTracker->m_nStyle |= CRectTracker::hatchInside;
   }
}

void CTestContainer98View::OnLButtonDblClk( UINT nFlags, CPoint point )
{
   LONG iVerb;
   BOOL tHandled;
   CTestContainer98Item* pItemHit;
   MSG msg;
   DWORD dwHitType;

   tHandled = HandleWindowlessMouseMessage( point );
   if( tHandled )
   {
	  return;
   }

   pItemHit = HitTestItems( point, &dwHitType );

   SetSelection( pItemHit );

   if( pItemHit != NULL )
   {
	  if( !GetDocument()->GetUserMode() && pItemHit->IsInsideOut() &&
		 !pItemHit->IsUIActive() )
	  {
		 // UIActivate the selected object.
		 msg = *GetCurrentMessage();
		 pItemHit->DoVerb( OLEIVERB_UIACTIVATE, this, &msg );
	  }
   }

   Invalidate();

   if( m_pSelection != NULL )
   {
	  if( GetKeyState( VK_CONTROL ) < 0 )
	  {
		 iVerb = OLEIVERB_OPEN;
	  }
	  else
	  {
		 iVerb = OLEIVERB_PRIMARY;
	  }

	  m_pSelection->DoVerb( iVerb, this );
   }

   CView::OnLButtonDblClk( nFlags, point );
}

HRESULT CTestContainer98View::OnWindowlessDefWindowMessage( UINT nMessage,
   WPARAM wParam, LPARAM lParam, LRESULT* plResult )
{
   const MSG* pMessage;

   (void)nMessage;
   (void)wParam;
   (void)lParam;

   pMessage = GetCurrentMessage();
   ASSERT( pMessage->message == nMessage );
   ASSERT( pMessage->wParam == wParam );
   ASSERT( pMessage->lParam == lParam );

   *plResult = Default();

   return( S_OK );
}

BOOL CTestContainer98View::OnSetCursor( CWnd* pWnd, UINT nHitTest,
   UINT message )
{
   CPoint pt;
   DWORD dwHitType;
   CRectTracker tracker;
   BOOL tHandled;
   CTestContainer98Item* pItemHit;

   // First, give the any inactive objects underneath the cursor a chance to
   // set the cursor and/or activate.
   tHandled = HandlePointerInactiveSetCursor( message );
   if( tHandled )
   {
	  return( TRUE );
   }

   // Now, see if a windowless control should be handling this message.
   tHandled = HandleWindowlessMouseMessage( m_ptLastMousePosition );
   if( tHandled )
   {
	  return( FALSE );
   }

   // None of the controls handled the message, so set the cursor ourselves.
   // The only interesting thing we do is let the tracker for the current
   // selection set the cursor to show resize/move arrows.
   if( pWnd == this )
   {
	  GetCursorPos( &pt );
	  ScreenToClient( &pt );
	  pItemHit = HitTestItems( pt, &dwHitType );
	  if( (pItemHit != NULL) && (dwHitType == HITTYPE_BORDER) &&
		 (m_lpSelectedItems.Find( pItemHit ) != NULL) )
	  {
		 SetupTracker( pItemHit, &tracker );
		 if( tracker.SetCursor( this, nHitTest ) )
		 {
			return( TRUE );
		 }
	  }
   }

   return( CView::OnSetCursor( pWnd, nHitTest, message ) );
}

void CTestContainer98View::OnEditClear()
{
   POSITION posItem;
   CTestContainer98Item* pItem;

   ASSERT( !m_lpSelectedItems.IsEmpty() );

   posItem = m_lpSelectedItems.GetHeadPosition();
   while( posItem != NULL )
   {
	  pItem = m_lpSelectedItems.GetNext( posItem );
	  pItem->Delete();
   }
   ClearSelection();
   GetDocument()->UpdateAllViews( NULL );
}

void CTestContainer98View::OnUpdateEditClear( CCmdUI* pCmdUI )
{
   pCmdUI->Enable( !m_lpSelectedItems.IsEmpty() );
}

void CTestContainer98View::OnUpdate( CView* pSender, LPARAM lHint,
   CObject* pHint )
{
   (void)pSender;

   switch( lHint )
   {
   case HINT_UPDATE_WINDOW:
	  Invalidate();
	  break;

   case HINT_UPDATE_ITEM:
	  {
		 CRectTracker tracker;
		 CRect rect;

		 SetupTracker( (CTestContainer98Item*)pHint, &tracker );
		 tracker.GetTrueRect( &rect );
		 InvalidateRect( rect );
	  }
	  break;
   }
}

void CTestContainer98View::OnRButtonDown( UINT nFlags, CPoint point )
{
   CTestContainer98Item* pItemHit;
   BOOL tHandled;
   DWORD dwHitType;
   MSG msg;

   tHandled = HandleWindowlessMouseMessage( point );
   if( tHandled )
   {
	  return;
   }

   pItemHit = HitTestItems( point, &dwHitType );

   if( !(nFlags&MK_CONTROL) )
   {
	  if( (pItemHit != NULL) && (m_lpSelectedItems.Find( pItemHit ) == NULL) )
	  {
		 SetSelection( pItemHit );
	  }
   }

   if( (pItemHit != NULL) && (dwHitType != HITTYPE_BORDER) )
   {
	  if( !pItemHit->IsInPlaceActive() )
	  {
		 msg = *GetCurrentMessage();
		 pItemHit->Activate( OLEIVERB_SHOW, this, &msg );
	  }
   }
}

BOOL CTestContainer98View::PreTranslateMessage( MSG* pMsg )
{
   CTestContainer98Item* pItem;
   CTestContainer98Doc* pDoc;
   MSG msg;
   IOleInPlaceActiveObjectPtr pInPlaceActiveObject;
   HRESULT hResult;
   POSITION posItem;
   CTestContainer98Item* pCurrentItem;

   pDoc = GetDocument();

   pCurrentItem = NULL;
   if( m_pItemWithFocus != NULL )
   {
	  pCurrentItem = m_pItemWithFocus;
   }
   else
   {
	  // Try the UI active control
	  posItem = pDoc->GetStartPosition();
	  while( (posItem != NULL) && (pCurrentItem == NULL) )
	  {
		 pItem = (CTestContainer98Item*)pDoc->GetNextItem( posItem );
		 if( pItem->IsUIActive() )
		 {
			pCurrentItem = pItem;
		 }
	  }
   }

   if( ((pMsg->message >= WM_KEYFIRST) && (pMsg->message <= WM_KEYLAST)) ||
	  ((pMsg->message >= WM_MOUSEFIRST) && (pMsg->message <= WM_MOUSELAST)) )
   {
	  // Give the item with focus first crack at keyboard and mouse messages
	  if( pCurrentItem != NULL )
	  {
		 pInPlaceActiveObject = pCurrentItem->m_lpObject;
		 if( pInPlaceActiveObject != NULL )
		 {
			hResult = pInPlaceActiveObject->TranslateAccelerator( pMsg );
			if( hResult == S_OK )
			{
			   return( TRUE );
			}
		 }
	  }
   }

   if( pMsg->message == WM_KEYDOWN )
   {
	  if( LOWORD( pMsg->wParam ) == VK_TAB )
	  {
		 pItem = pDoc->GetNextTabItem( pCurrentItem );
		 if( pItem != NULL )
		 {
			if( pItem->HasUIActiveState() )
			{
			   if( !pItem->IsUIActive() )
			   {
				  msg = *pMsg;
				  pItem->DoVerb( OLEIVERB_UIACTIVATE, this, &msg );
			   }
			}
			if( pItem->ActsLikeButton() )
			{
			   pItem->DisplayAsDefault( TRUE );
			}
		 }

		 return( TRUE );
	  }
   }
   else if( pMsg->message == WM_KEYUP )
   {
	  if( LOWORD( pMsg->wParam ) == VK_TAB )
	  {
		 return( TRUE );
	  }
   }

   return( CView::PreTranslateMessage( pMsg ) );
}

void CTestContainer98View::OnOptionsDesignMode()
{
   CTestContainer98Doc* pDoc;

   pDoc = GetDocument();
   pDoc->SetUserMode( !pDoc->GetUserMode() );
}

void CTestContainer98View::OnUpdateOptionsDesignMode( CCmdUI* pCmdUI )
{
   if( GetDocument()->GetUserMode() )
   {
	  pCmdUI->SetCheck( 0 );
   }
   else
   {
	  pCmdUI->SetCheck( 1 );
   }
}

BOOL CTestContainer98View::OnDrop( COleDataObject* pDataObject,
   DROPEFFECT dropEffect, CPoint point )
{
   DWORD dwDropEffect;
   BOOL tHandled;

   TRACE( "OnDrop()\n" );

   dwDropEffect = dropEffect;
   tHandled = HandleWindowlessDrop( pDataObject, m_dwLastDropKeyState, point,
	  &dwDropEffect );
   if( tHandled )
   {
	  return( CView::OnDrop( pDataObject, dropEffect, point ) );
   }

   return( CView::OnDrop( pDataObject, dropEffect, point ) );
}

CTestContainer98Item* CTestContainer98View::GetItemWithCapture() const
{
   return( m_pItemWithCapture );
}

CTestContainer98Item* CTestContainer98View::GetItemWithFocus() const
{
   return( m_pItemWithFocus );
}

HRESULT CTestContainer98View::OnWindowlessReleaseCapture(
   CTestContainer98Item* pItem )
{
   if( m_pItemWithCapture == pItem )
   {
	  m_pItemWithCapture = NULL;
	  ReleaseCapture();
   }

   return( S_OK );
}

HRESULT CTestContainer98View::OnWindowlessReleaseFocus()
{
   ASSERT( m_pItemWithFocus != NULL );

   m_pItemWithFocus = NULL;

   return( S_OK );
}

HRESULT CTestContainer98View::OnWindowlessSetCapture(
   CTestContainer98Item* pItem )
{
   ASSERT( pItem != NULL );
//   ASSERT( m_pItemWithCapture == NULL );

   SetCapture();
   m_pItemWithCapture = pItem;

   return( S_OK );
}

HRESULT CTestContainer98View::OnWindowlessSetFocus(
   CTestContainer98Item* pItem )
{
   ASSERT( pItem != NULL );

   TCTrace( TRACELEVEL_NORMAL, "Setting focus to windowless control.\n" );

   SetFocus();
   m_pItemWithFocus = pItem;

   return( S_OK );
}

DROPEFFECT CTestContainer98View::OnDragEnter( COleDataObject* pDataObject,
   DWORD dwKeyState, CPoint point )
{
   BOOL tHandled;
   DWORD dwDropEffect;

   TRACE( "OnDragEnter()\n" );

   HandlePointerInactiveDragOver( point );

   dwDropEffect = DROPEFFECT_COPY|DROPEFFECT_MOVE|DROPEFFECT_LINK;
   tHandled = HandleWindowlessDragEnter( pDataObject, dwKeyState, point,
	  &dwDropEffect );
   if( tHandled )
   {
	  return( dwDropEffect );
   }

	return( DROPEFFECT_NONE );
}

DROPEFFECT CTestContainer98View::OnDragOver( COleDataObject* pDataObject,
   DWORD dwKeyState, CPoint point )
{
   DWORD dwDropEffect;
   BOOL tHandled;

   m_dwLastDropKeyState = dwKeyState;

   HandlePointerInactiveDragOver( point );

   dwDropEffect = DROPEFFECT_COPY|DROPEFFECT_MOVE|DROPEFFECT_LINK;
   tHandled = HandleWindowlessDragOver( pDataObject, dwKeyState, point,
	  &dwDropEffect );
   if( tHandled )
   {
	  return( dwDropEffect );
   }

   return( DROPEFFECT_NONE );
}

int CTestContainer98View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if( CView::OnCreate( lpCreateStruct ) == -1 )
   {
	  return( -1 );
   }

   // Register drop target.
   m_dropTarget.Register( this );

   return( 0 );
}

void CTestContainer98View::OnLButtonUp( UINT nFlags, CPoint point )
{
   BOOL tHandled;

   tHandled = HandleWindowlessMouseMessage( point );
   if( tHandled )
   {
	  return;
   }

   CView::OnLButtonUp( nFlags, point );
}

void CTestContainer98View::OnMouseMove( UINT nFlags, CPoint point )
{
   BOOL tHandled;

   m_ptLastMousePosition = point;

   tHandled = HandlePointerInactiveMove( point, nFlags );
   if( tHandled )
   {
	  return;
   }

   tHandled = HandleWindowlessMouseMessage( point );
   if( tHandled )
   {
	  return;
   }

   CView::OnMouseMove( nFlags, point );
}

void CTestContainer98View::OnRButtonDblClk( UINT nFlags, CPoint point )
{
   BOOL tHandled;

   tHandled = HandleWindowlessMouseMessage( point );
   if( tHandled )
   {
	  return;
   }

   CView::OnRButtonDblClk( nFlags, point );
}

void CTestContainer98View::OnRButtonUp( UINT nFlags, CPoint point )
{
   BOOL tHandled;

   tHandled = HandleWindowlessMouseMessage( point );
   if( tHandled )
   {
	  return;
   }

   CView::OnRButtonUp( nFlags, point );
}

void CTestContainer98View::OnCaptureChanged( CWnd *pWnd )
{
   // We're losing the capture, so the windowless item that has the capture
   // loses it, too.
   m_pItemWithCapture = NULL;

	CView::OnCaptureChanged( pWnd );
}

void CTestContainer98View::OnFocus( CTestContainer98Item* pItem,
   BOOL tGotFocus )
{
   ASSERT( pItem != NULL );

   if( tGotFocus )
   {
	  m_pItemWithFocus = pItem;
   }
   else
   {
	  if( m_pItemWithFocus == pItem )
	  {
		 m_pItemWithFocus = NULL;
	  }
   }
}

void CTestContainer98View::OnKillFocus( CWnd* pNewWnd )
{
	CView ::OnKillFocus( pNewWnd );
}

void CTestContainer98View::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
   BOOL tHandled;

   tHandled = HandleWindowlessKeyboardMessage();
   if( tHandled )
   {
	  return;
   }

   CView::OnKeyDown( nChar, nRepCnt, nFlags );
}

void CTestContainer98View::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
   BOOL tHandled;

   tHandled = HandleWindowlessKeyboardMessage();
   if( tHandled )
   {
	  return;
   }

   CView::OnKeyUp( nChar, nRepCnt, nFlags );
}

void CTestContainer98View::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{
   BOOL tHandled;

   tHandled = HandleWindowlessKeyboardMessage();
   if( tHandled )
   {
	  return;
   }

   CView::OnChar( nChar, nRepCnt, nFlags );
}

void CTestContainer98View::OnCancelMode()
{
   BOOL tHandled;

   CView::OnCancelMode();

   tHandled = HandleWindowlessKeyboardMessage();
   if( tHandled )
   {
	  return;
   }
}

void CTestContainer98View::OnControlSaveToStream()
{
   int nResult;
   CFileDialog dlg( FALSE, _T( "TSM" ), NULL, OFN_HIDEREADONLY|
	  OFN_OVERWRITEPROMPT, _T( "Test Container Stream Files (*.TSM)|*.TSM||" ) );
   HRESULT hResult;
   IStreamPtr pStream;
   LARGE_INTEGER nDisplacement;
   ULARGE_INTEGER iSeekPtr;
   ULONG nBytesLeft;
   ULONG nBytesRead;
   BYTE abData[512];

   ASSERT( m_pSelection != NULL );

   nResult = dlg.DoModal();
   if( nResult != IDOK )
   {
	  return;
   }

   hResult = CreateStreamOnHGlobal( NULL, TRUE, &pStream );
   if( FAILED( hResult ) )
   {
	  TRACE( "CreateStreamOnHGlobal() failed.\n" );
	  return;
   }

   hResult = m_pSelection->SaveToStream( pStream );
   if( FAILED( hResult ) )
   {
	  CString strErrorMessage;
	  _com_error e( hResult );

	  strErrorMessage.LoadString( IDS_SAVETOSTREAMFAILED );
	  strErrorMessage += e.ErrorMessage();
	  AfxMessageBox( strErrorMessage );
	  return;
   }

   try
   {
	  CFile file( dlg.GetPathName(), CFile::modeCreate|CFile::modeWrite|
		 CFile::shareExclusive );

	  nDisplacement.QuadPart = 0;
	  pStream->Seek( nDisplacement, STREAM_SEEK_CUR, &iSeekPtr );
	  nBytesLeft = ULONG( iSeekPtr.QuadPart );
	  pStream->Seek( nDisplacement, STREAM_SEEK_SET, NULL );
	  while( nBytesLeft > 0 )
	  {
		 pStream->Read( abData, min( nBytesLeft, sizeof( abData ) ),
			&nBytesRead );
		 ASSERT( nBytesRead > 0 );
		 file.Write( abData, nBytesRead );
		 nBytesLeft -= nBytesRead;
	  }
   }
   catch( CFileException* pException )
   {
	  pException->Delete();

	  AfxMessageBox( IDS_ERRORWRITINGTOFILE );
   }
}

void CTestContainer98View::OnEditInsertFromStream()
{
   int nResult;
   HRESULT hResult;
   IStreamPtr pStream;
   LARGE_INTEGER nDisplacement;
   ULONG nBytesLeft;
   ULONG nBytesToRead;
   CTestContainer98Doc* pDoc;
   CTestContainer98Item* pItem;
   CLSID clsid;
   BYTE abData[512];
   CFileDialog dlg( TRUE, _T( "TSM" ), NULL, OFN_HIDEREADONLY|
	  OFN_OVERWRITEPROMPT, _T( "Test Container Stream Files (*.TSM)|*.TSM||" ) );

   nResult = dlg.DoModal();
   if( nResult != IDOK )
   {
	  return;
   }

   hResult = CreateStreamOnHGlobal( NULL, TRUE, &pStream );
   if( FAILED( hResult ) )
   {
	  TRACE( "CreateStreamOnHGlobal() failed.\n" );
	  return;
   }

   try
   {
	  CFile file( dlg.GetPathName(), CFile::modeRead|CFile::shareDenyWrite );

	  nBytesLeft = file.GetLength();
	  while( nBytesLeft > 0 )
	  {
		 nBytesToRead = min( nBytesLeft, sizeof( abData ) );
		 file.Read( abData, nBytesToRead );
		 pStream->Write( abData, nBytesToRead, NULL );
		 nBytesLeft -= nBytesToRead;
	  }
   }
   catch( CFileException* pException )
   {
	  pException->Delete();
	  AfxMessageBox( IDS_ERRORREADINGFROMFILE );
	  return;
   }

   nDisplacement.QuadPart = 0;
   pStream->Seek( nDisplacement, STREAM_SEEK_SET, NULL );

   BeginWaitCursor();

   pItem = NULL;
   try
   {
	  hResult = ReadClassStm( pStream, &clsid );
	  if( FAILED( hResult ) )
	  {
		 AfxThrowOleException( hResult );
	  }

	  pDoc = GetDocument();
	  pItem = pDoc->AddControl( clsid, NULL, IID_IStream, pStream );
   }
   catch( COleException* pException )
   {
	  CString strErrorMessage;
	  _com_error error( pException->m_sc );

	  pException->Delete();

	  if( pItem != NULL )
	  {
		 ASSERT_VALID( pItem );
		 pItem->Delete();
	  }

	  AfxFormatString1( strErrorMessage, IDS_CREATEFAILED,
		 error.ErrorMessage() );

	  AfxMessageBox( strErrorMessage );
   }
   catch( CException* pException )
   {
	  pException->Delete();

	  AfxMessageBox( IDP_FAILED_TO_CREATE );
   }

   EndWaitCursor();
}

void CTestContainer98View::OnDragLeave()
{
   TRACE( "OnDragLeave()\n" );

   HandleWindowlessDragLeave();

	CView::OnDragLeave();
}

void CTestContainer98View::OnControlSaveToPropertyBag()
{
   CPropertyBag* pPropertyBagObject;
   IPropertyBagPtr pPropertyBag;
   HRESULT hResult;

   pPropertyBagObject = new CPropertyBag;
   if( pPropertyBagObject == NULL )
   {
	  return;
   }

   hResult = pPropertyBagObject->QueryInterface( IID_IPropertyBag,
	  (void**)&pPropertyBag );
   ASSERT( SUCCEEDED( hResult ) );

   hResult = m_pSelection->SaveToPropertyBag( pPropertyBag );
   if( FAILED( hResult ) )
   {
	  CString strErrorMessage;
	  _com_error e( hResult );

	  strErrorMessage.LoadString( IDS_SAVETOPROPERTYBAGFAILED );
	  strErrorMessage += e.ErrorMessage();
	  AfxMessageBox( strErrorMessage );
	  return;
   }

   CPropertyBagDlg dlg( pPropertyBagObject );

   dlg.DoModal();
}

void CTestContainer98View::OnUpdateControlSaveToPropertyBag( CCmdUI* pCmdUI )
{
   pCmdUI->Enable( m_pSelection != NULL );
}

void CTestContainer98View::OnUpdateControlSaveToStream( CCmdUI* pCmdUI )
{
   pCmdUI->Enable( m_pSelection != NULL );
}

void CTestContainer98View::OnControlInvokeMethods()
{
   ASSERT( m_pSelection != NULL );

   m_pSelection->InvokeMethods();
}

void CTestContainer98View::OnUpdateControlInvokeMethods( CCmdUI* pCmdUI )
{
   pCmdUI->Enable( m_pSelection != NULL );
}

void CTestContainer98View::OnControlLogging()
{
   ASSERT( m_pSelection != NULL );

   m_pSelection->SetLoggingOptions();
}

void CTestContainer98View::OnUpdateControlLogging( CCmdUI* pCmdUI )
{
   pCmdUI->Enable( m_pSelection != NULL );
}

void CTestContainer98View::OnControlActivate()
{
   ASSERT( m_pSelection != NULL );

   m_pSelection->Activate( OLEIVERB_INPLACEACTIVATE, this );
}

void CTestContainer98View::OnControlDeactivate()
{
   ASSERT( m_pSelection != NULL );

   m_pSelection->Deactivate();
}

void CTestContainer98View::OnControlUIActivate()
{
   ASSERT( m_pSelection != NULL );

   m_pSelection->Activate( OLEIVERB_UIACTIVATE, this );
}

void CTestContainer98View::OnControlUIDeactivate()
{
   ASSERT( m_pSelection != NULL );

   m_pSelection->DeactivateUI();
}

void CTestContainer98View::OnUpdateControlUIDeactivate( CCmdUI* pCmdUI )
{
   pCmdUI->Enable( (m_pSelection != NULL)   && (m_pSelection->IsUIActive()) );
}

void CTestContainer98View::OnUpdateControlUIActivate( CCmdUI* pCmdUI )
{
   pCmdUI->Enable( (m_pSelection != NULL) && (!m_pSelection->IsUIActive()) );
}

void CTestContainer98View::OnUpdateControlActivate( CCmdUI* pCmdUI )
{
   pCmdUI->Enable( (m_pSelection != NULL) &&
	  (!m_pSelection->IsInPlaceActive()) );
}

void CTestContainer98View::OnUpdateControlDeactivate( CCmdUI* pCmdUI )
{
   pCmdUI->Enable( (m_pSelection != NULL) &&
	  (m_pSelection->IsInPlaceActive()) );
}

void CTestContainer98View::OnEditBringToFront()
{
   POSITION posItem;
   CTestContainer98Item* pItem;

   ASSERT( !m_lpSelectedItems.IsEmpty() );

   posItem = m_lpSelectedItems.GetHeadPosition();
   while( posItem != NULL )
   {
	  pItem = m_lpSelectedItems.GetNext( posItem );
	  GetDocument()->BringToFront( pItem );
   }

   Invalidate();
}

void CTestContainer98View::OnUpdateEditBringToFront( CCmdUI* pCmdUI )
{
   pCmdUI->Enable( !m_lpSelectedItems.IsEmpty() );
}

void CTestContainer98View::OnEditSendToBack()
{
   POSITION posItem;
   CTestContainer98Item* pItem;

   ASSERT( !m_lpSelectedItems.IsEmpty() );

   posItem = m_lpSelectedItems.GetHeadPosition();
   while( posItem != NULL )
   {
	  pItem = m_lpSelectedItems.GetNext( posItem );
	  GetDocument()->SendToBack( pItem );
   }

   Invalidate();
}

void CTestContainer98View::OnUpdateEditSendToBack( CCmdUI* pCmdUI )
{
   pCmdUI->Enable( !m_lpSelectedItems.IsEmpty() );
}

void CTestContainer98View::OnContextMenu( CWnd* pWnd, CPoint point )
{
   CTestContainer98Item* pItemHit;
   CPoint ptClient;
   CMenu menu;
   CMenu* pPopupMenu;
   DWORD dwHitType;

   if( pWnd->m_hWnd != m_hWnd )
   {
	  return;
   }

   GetParentFrame()->ActivateFrame();

   ptClient = point;
   ScreenToClient( &ptClient );

   pItemHit = HitTestItems( ptClient, &dwHitType );

   if( pItemHit == NULL )
   {
	  menu.LoadMenu( IDR_CONTAINER_CONTEXT );
	  pPopupMenu = menu.GetSubMenu( 0 );
	  pPopupMenu->TrackPopupMenu( TPM_LEFTALIGN|TPM_RIGHTBUTTON, point.x,
		 point.y, AfxGetMainWnd(), NULL );
	  menu.DestroyMenu();
   }
   else
   {
	  if( m_lpSelectedItems.Find( pItemHit ) != NULL )
	  {
		 // The item is selected.  Create a popup menu at the current mouse
		 // location, and fill it with the appropriate verbs for the object.
		 menu.LoadMenu( IDR_CONTROL_CONTEXT );
		 pPopupMenu = menu.GetSubMenu( 0 );
		 pPopupMenu->TrackPopupMenu( TPM_LEFTALIGN|TPM_RIGHTBUTTON, point.x,
			point.y, AfxGetMainWnd(), NULL );
		 menu.DestroyMenu();
	  }
   }
}

void CTestContainer98View::OnEditProperties()
{
   POSITION posItem;
   CTestContainer98Item* pItem;
   CArray< CLSID, CLSID& > aclsidCommonPages;
   CArray< CLSID, CLSID& > aclsidPages;
   BOOL tSuccess;
   int iPage;
   int iCommonPage;
   BOOL tFound;
   CLSID clsidPage;

   posItem = m_lpSelectedItems.GetHeadPosition();
   pItem = m_lpSelectedItems.GetNext( posItem );
   tSuccess = pItem->GetPropertyPageCLSIDs( aclsidCommonPages );
   if( !tSuccess )
   {
	  return;
   }
   while( posItem != NULL )
   {
	  pItem = m_lpSelectedItems.GetNext( posItem );
	  aclsidPages.RemoveAll();
	  tSuccess = pItem->GetPropertyPageCLSIDs( aclsidPages );
	  if( !tSuccess )
	  {
		 return;
	  }

	  for( iCommonPage = aclsidCommonPages.GetSize()-1; iCommonPage >= 0;
		 iCommonPage-- )
	  {
		 clsidPage = aclsidCommonPages[iCommonPage];
		 tFound = FALSE;
		 for( iPage = 0; iPage < aclsidPages.GetSize(); iPage++ )
		 {
			if( IsEqualCLSID( clsidPage, aclsidPages[iPage] ) )
			{
			   tFound = TRUE;
			}
		 }
		 if( !tFound )
		 {
			aclsidCommonPages.RemoveAt( iCommonPage );
		 }
	  }
   }

   if( m_lpSelectedItems.GetCount() > 1 )
   {
	  // Don't display the extended properties page if multiple items are
	  // selected.
	  for( iCommonPage = 0; iCommonPage < aclsidCommonPages.GetSize();
		 iCommonPage++ )
	  {
		 if( IsEqualCLSID( aclsidCommonPages[iCommonPage], __uuidof(
			TCExtPage ) ) )
		 {
			aclsidCommonPages.RemoveAt( iCommonPage );
		 }
	  }
   }

   if( aclsidCommonPages.GetSize() == 0 )
   {
	  AfxMessageBox( IDS_NOCOMMONPROPERTIES );
   }
   else
   {
	  USES_CONVERSION;
	  int iObject;
	  IUnknown** ppObjects;
	  CLSID* pclsidCommonPages;
	  CString strCaption;

	  ppObjects = (IUnknown**)_alloca( m_lpSelectedItems.GetCount()*sizeof(
		 IUnknown* ) );
	  iObject = 0;
	  posItem = m_lpSelectedItems.GetHeadPosition();
	  while( posItem != NULL )
	  {
		 pItem = m_lpSelectedItems.GetNext( posItem );
		 ppObjects[iObject] = pItem->m_lpObject;
		 iObject++;
	  }

	  pclsidCommonPages = (CLSID*)_alloca( aclsidCommonPages.GetSize()*sizeof(
		 CLSID ) );
	  for( iPage = 0; iPage < aclsidCommonPages.GetSize(); iPage++ )
	  {
		 pclsidCommonPages[iPage] = aclsidCommonPages[iPage];
	  }

	  if( m_lpSelectedItems.GetCount() > 1 )
	  {
		 strCaption.LoadString( IDS_MULTIPLESELECTION );
	  }
	  else
	  {
		 strCaption = m_pSelection->GetDisplayName();
	  }
	  OleCreatePropertyFrame( m_hWnd, 0, 0, T2COLE( strCaption ),
		 m_lpSelectedItems.GetCount(), ppObjects, aclsidCommonPages.GetSize(),
		 pclsidCommonPages, GetUserDefaultLCID(), 0, NULL );

	  //WINBUG: OleCreatePropertyFrame doesn't return focus to its parent when
	  // it closes
	  SetFocus();
   }
}

void CTestContainer98View::OnUpdateEditProperties( CCmdUI* pCmdUI )
{
   pCmdUI->Enable( !m_lpSelectedItems.IsEmpty() );
}

void CTestContainer98View::OnEditSelectAll()
{
   POSITION posItem;
   CTestContainer98Item* pItem;
   CTestContainer98Doc* pDoc;

   pDoc = GetDocument();
   posItem = pDoc->GetStartPosition();
   while( posItem != NULL )
   {
	  pItem = (CTestContainer98Item*)pDoc->GetNextItem( posItem );
	  SetMultiSelect( pItem, TRUE );
   }
}

void CTestContainer98View::OnEditCopy()
{
   IStoragePtr pStorage;
   HRESULT hResult;
   POSITION posItem;
   CTestContainer98Item* pItem;
   COleStreamFile file;
   ULONG iItem;
   CString strStorageName;
   BSTR bstrStorageName;
   IStoragePtr pSubStorage;
   COleDataSource* pDataSource;
   CLIPFORMAT cf;
   STGMEDIUM stgmedium;
   int nSelectedItems;

   ASSERT( m_lpSelectedItems.GetCount() > 0 );

   pDataSource = new COleDataSource;
   try
   {
	  hResult = StgCreateDocfile( NULL, STGM_CREATE|STGM_READWRITE|
		 STGM_DELETEONRELEASE|STGM_SHARE_EXCLUSIVE, 0, &pStorage );
	  if( FAILED( hResult ) )
	  {
		 AfxThrowOleException( hResult );
	  }

	  if( !file.CreateStream( pStorage, _T( "Contents" ), CFile::modeReadWrite|
		 CFile::shareExclusive|CFile::modeCreate ) )
	  {
		 AfxThrowOleException( E_FAIL );
	  }

	  CArchive ar( &file, CArchive::store );

	  nSelectedItems = m_lpSelectedItems.GetCount();
	  ar<<nSelectedItems;

	  posItem = m_lpSelectedItems.GetHeadPosition();
	  iItem = 0;
	  while( posItem != NULL )
	  {
		 pItem = m_lpSelectedItems.GetNext( posItem );
		 strStorageName.Format( "Control%d", iItem );
		 bstrStorageName = strStorageName.AllocSysString();

		 hResult = pStorage->CreateStorage( bstrStorageName, STGM_READWRITE|
			STGM_CREATE|STGM_SHARE_EXCLUSIVE, 0, 0, &pSubStorage );
		 SysFreeString( bstrStorageName );
		 if( FAILED( hResult ) )
		 {
			AfxThrowOleException( hResult );
		 }

		 pItem->CopyToClipboard( ar, pSubStorage );

		 pSubStorage.Release();
		 iItem++;
	  }

	  stgmedium.tymed = TYMED_ISTORAGE;
	  stgmedium.pstg = pStorage;
	  stgmedium.pstg->AddRef();
	  stgmedium.pUnkForRelease = NULL;

	  cf = CLIPFORMAT( ::RegisterClipboardFormat( _T( "TC98 Controls" ) ) );
	  pDataSource->CacheData( cf, &stgmedium );
   }
   catch( COleException* pException )
   {
	  CString strErrorMessage;
	  _com_error error( pException->m_sc );

	  pException->Delete();
	  delete pDataSource;

	  AfxFormatString1( strErrorMessage, IDS_COPYFAILED,
		 error.ErrorMessage() );
	  AfxMessageBox( strErrorMessage );
	  return;
   }

   file.Close();

   pDataSource->SetClipboard();
}

void CTestContainer98View::OnEditPaste()
{
   CTestContainer98Item* pItem;
   CTestContainer98Doc* pDoc;
   COleDataObject data;
   CLIPFORMAT cf;
   STGMEDIUM stgmedium;
   IStoragePtr pStorage;
   IStoragePtr pSubStorage;
   int iItem;
   int nItems;
   CString strItemName;
   BSTR bstrItemName;
   HRESULT hResult;
   COleStreamFile file;

   pDoc = GetDocument();

   if( !data.AttachClipboard() )
   {
	  return;
   }

   cf = CLIPFORMAT( ::RegisterClipboardFormat( _T( "TC98 Controls" ) ) );
   if( !data.GetData( cf, &stgmedium ) )
   {
	  return;
   }

   ASSERT( stgmedium.tymed == TYMED_ISTORAGE );

   pStorage = stgmedium.pstg;
   ReleaseStgMedium( &stgmedium );

   if( !file.OpenStream( pStorage, _T( "Contents" ), STGM_READ|
	  STGM_SHARE_EXCLUSIVE ) )
   {
	  return;
   }

   CArchive ar( &file, CArchive::load|CArchive::bNoFlushOnDelete );

   ClearSelection();

   ar>>nItems;

   for( iItem = 0; iItem < nItems; iItem++ )
   {
	  pItem = NULL;
	  try
	  {
		 strItemName.Format( "Control%d", iItem );
		 bstrItemName = strItemName.AllocSysString();
		 hResult = pStorage->OpenStorage( bstrItemName, NULL, STGM_READWRITE|
			STGM_SHARE_EXCLUSIVE, NULL, 0, &pSubStorage );
		 SysFreeString( bstrItemName );
		 if( FAILED( hResult ) )
		 {
			AfxThrowOleException( hResult );
		 }

		 pItem = new CTestContainer98Item( pDoc );
		 if( !pItem->CreateFromClipboard( ar, pSubStorage ) )
		 {
			AfxThrowOleException( E_FAIL );
		 }

		 pItem->UpdateLink();
		 pItem->InvalidateItem();

		 // Activate the item if it wants to be active all the time.
		 if( pItem->ShouldActivateWhenVisible() )
		 {
			if( pDoc->GetUserMode() && pItem->IsInvisibleAtRuntime() )
			{
			   pItem->DoVerb( OLEIVERB_HIDE, this );
			}
			else
			{
			   pItem->DoVerb( OLEIVERB_SHOW, this );
			}
		 }

		 SetMultiSelect( pItem, TRUE );

		 ASSERT_VALID( pItem );
	  }
	  catch( CException* pException )
	  {
		 pException->Delete();

		 delete pItem;
	  }
   }

   ar.Flush();
   file.Close();

   pDoc->SetModifiedFlag();

   Invalidate();
}

void CTestContainer98View::OnUpdateEditCopy( CCmdUI* pCmdUI )
{
   pCmdUI->Enable( m_lpSelectedItems.GetCount() > 0 );
}

void CTestContainer98View::OnUpdateEditPaste( CCmdUI* pCmdUI )
{
   pCmdUI->Enable( IsClipboardFormatAvailable( ::RegisterClipboardFormat( _T(
	  "TC98 Controls" ) ) ) );
}

void CTestContainer98View::OnEditCut()
{
   OnEditCopy();
   OnEditClear();
}

void CTestContainer98View::OnUpdateEditCut( CCmdUI* pCmdUI )
{
   pCmdUI->Enable( m_lpSelectedItems.GetCount() > 0 );
}

const LPCTSTR VS_SETUP_KEY = _T(
   "Software\\Microsoft\\VisualStudio\\6.0\\Setup" );
const LPCTSTR VS_COMMONDIR_VALUENAME = _T( "VsCommonDir" );

void CTestContainer98View::OnToolsOLEView()
{
   HKEY hKey;
   LONG nResult;
   DWORD dwType;
   CString strPath;
   LPTSTR pszPath;
   ULONG nDataLength;
   STARTUPINFO startup;
   PROCESS_INFORMATION process;
   BOOL tSuccess;

   nResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, VS_SETUP_KEY, 0, KEY_READ,
	  &hKey );
   if( nResult != ERROR_SUCCESS )
   {
	  return;
   }

   nResult = RegQueryValueEx( hKey, VS_COMMONDIR_VALUENAME, NULL, &dwType,
	  NULL, &nDataLength );
   if( (nResult == ERROR_SUCCESS) && (dwType == REG_SZ) )
   {
	  pszPath = strPath.GetBuffer( nDataLength/sizeof( TCHAR ) );
	  nResult = RegQueryValueEx( hKey, VS_COMMONDIR_VALUENAME, NULL, &dwType,
		 LPBYTE( pszPath ), &nDataLength );
	  strPath.ReleaseBuffer();
	  strPath += _T( "\\Tools\\OLEView.exe" );
	  if( (nResult == ERROR_SUCCESS) && (dwType == REG_SZ) )
	  {
		 memset( &startup, 0, sizeof( startup ) );
		 startup.cb = sizeof( startup );

		 memset( &process, 0, sizeof( process ) );

		 tSuccess = CreateProcess( strPath, NULL, NULL, NULL, FALSE, 0, NULL,
			NULL, &startup, &process );
		 if( tSuccess )
		 {
			// Close the handles that CreateProcess returned so we don't leak
			// kernel resources.
			ASSERT( process.hProcess != NULL );
			CloseHandle( process.hProcess );
			ASSERT( process.hThread != NULL );
			CloseHandle( process.hThread );
		 }
		 else
		 {
			AfxMessageBox( IDS_NOOLEVIEW );
		 }
	  }
   }

   RegCloseKey( hKey );
}

void CTestContainer98View::OnToolsRegEdit()
{
   STARTUPINFO startup;
   PROCESS_INFORMATION process;
   BOOL tSuccess;
   CString strPath;
   LPTSTR pszPath;

   pszPath = strPath.GetBuffer( MAX_PATH );
   GetWindowsDirectory( pszPath, MAX_PATH );
   strPath.ReleaseBuffer();

   memset( &startup, 0, sizeof( startup ) );
   startup.cb = sizeof( startup );

   memset( &process, 0, sizeof( process ) );

   tSuccess = CreateProcess( strPath+_T( "\\RegEdit.exe" ), NULL, NULL, NULL,
	  FALSE, 0, NULL, NULL, &startup, &process );
   if( tSuccess )
   {
	  // Close the handles that CreateProcess returned so we don't leak
	  // kernel resources.
	  ASSERT( process.hProcess != NULL );
	  CloseHandle( process.hProcess );
	  ASSERT( process.hThread != NULL );
	  CloseHandle( process.hThread );
   }
}

void CTestContainer98View::OnControlSaveToStorage()
{
   USES_CONVERSION;
   HKEY hKey;
   LONG nResult;
   DWORD dwType;
   CString strPath;
   LPTSTR pszPath;
   CString strCommandLine;
   LPTSTR pszCommandLine;
   ULONG nDataLength;
   STARTUPINFO startup;
   PROCESS_INFORMATION process;
   BOOL tSuccess;
   HRESULT hResult;
   IStoragePtr pStorage;
   CFileDialog dlg( FALSE, _T( "TSG" ), NULL, OFN_HIDEREADONLY|
	  OFN_OVERWRITEPROMPT, _T( "Test Container Storage Files (*.TSG)|*.TSG||" ) );

   ASSERT( m_pSelection != NULL );

   nResult = dlg.DoModal();
   if( nResult != IDOK )
   {
	  return;
   }

   hResult = StgCreateDocfile( T2COLE( dlg.GetPathName() ), STGM_READWRITE|
	  STGM_SHARE_EXCLUSIVE|STGM_CREATE, 0, &pStorage );
   if( FAILED( hResult ) )
   {
	  return;
   }

   hResult = m_pSelection->SaveToStorage( pStorage );
   if( FAILED( hResult ) )
   {
	  CString strErrorMessage;
	  _com_error e( hResult );

	  strErrorMessage.LoadString( IDS_SAVETOSTORAGEFAILED );
	  strErrorMessage += e.ErrorMessage();
	  AfxMessageBox( strErrorMessage );
	  return;
   }

   nResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, VS_SETUP_KEY, 0, KEY_READ,
	  &hKey );
   if( nResult != ERROR_SUCCESS )
   {
	  return;
   }

   pStorage.Release();

   nResult = RegQueryValueEx( hKey, VS_COMMONDIR_VALUENAME, NULL, &dwType,
	  NULL, &nDataLength );
   if( (nResult == ERROR_SUCCESS) && (dwType == REG_SZ) )
   {
	  pszPath = strPath.GetBuffer( nDataLength/sizeof( TCHAR ) );
	  nResult = RegQueryValueEx( hKey, VS_COMMONDIR_VALUENAME, NULL, &dwType,
		 LPBYTE( pszPath ), &nDataLength );
	  strPath.ReleaseBuffer();
	  strPath += _T( "\\Tools\\DFView.exe" );
	  if( (nResult == ERROR_SUCCESS) && (dwType == REG_SZ) )
	  {
		 memset( &startup, 0, sizeof( startup ) );
		 startup.cb = sizeof( startup );

		 memset( &process, 0, sizeof( process ) );

		 strCommandLine.Format( "\"%s\" %s", LPCTSTR( strPath ),
			dlg.GetPathName() );
		 pszCommandLine = strCommandLine.GetBuffer( 0 );
		 tSuccess = CreateProcess( strPath, pszCommandLine, NULL, NULL, FALSE,
			0, NULL, NULL, &startup, &process );
		 strCommandLine.ReleaseBuffer();
		 if( tSuccess )
		 {
			// Close the handles that CreateProcess returned so we don't leak
			// kernel resources.
			ASSERT( process.hProcess != NULL );
			CloseHandle( process.hProcess );
			ASSERT( process.hThread != NULL );
			CloseHandle( process.hThread );
		 }
		 else
		 {
			AfxMessageBox( IDS_NODFVIEW );
		 }
	  }
   }

   RegCloseKey( hKey );
}

void CTestContainer98View::OnUpdateControlSaveToStorage( CCmdUI* pCmdUI )
{
   pCmdUI->Enable( m_lpSelectedItems.GetCount() == 1 );
}

void CTestContainer98View::OnEditInsertControlFromStorage()
{
   USES_CONVERSION;
   CTestContainer98Item* pItem;
   CTestContainer98Doc* pDoc;
   int nResult;
   IStoragePtr pStorage;
   HRESULT hResult;
   CLSID clsid;
   CString strMessage;
   CFileDialog dlg( TRUE, _T( "TSG" ), NULL, OFN_HIDEREADONLY|
	  OFN_OVERWRITEPROMPT, _T( "Test Container Storage Files (*.TSG)|*.TSG||" ) );

   nResult = dlg.DoModal();
   if( nResult != IDOK )
   {
	  return;
   }

   hResult = StgOpenStorage( T2COLE( dlg.GetPathName() ), NULL, STGM_READ|
	  STGM_SHARE_DENY_WRITE, NULL, 0, &pStorage );
   if( FAILED( hResult ) )
   {
	  _com_error error( hResult );

	  AfxFormatString1( strMessage, IDS_OPENSTORAGEFAILED,
		 error.ErrorMessage() );
	  AfxMessageBox( strMessage );
	  return;
   }

   ReadClassStg( pStorage, &clsid );

   pDoc = GetDocument();

   pItem = NULL;
   try
   {
	  pItem = pDoc->AddControl( clsid, NULL, IID_IStorage, pStorage );
   }
   catch( COleException* pException )
   {
	  _com_error error( pException->m_sc );

	  pException->Delete();

	  AfxFormatString1( strMessage, IDS_LOADCONTROLFAILED,
		 error.ErrorMessage() );

	  AfxMessageBox( strMessage );
   }
   catch( CException* pException )
   {
	  _com_error error( E_FAIL );

	  pException->Delete();

	  AfxFormatString1( strMessage, IDS_LOADCONTROLFAILED,
		 error.ErrorMessage() );

	  AfxMessageBox( strMessage );
   }
}

void CTestContainer98View::OnUpdateEditSelectAll( CCmdUI* pCmdUI )
{
   CTestContainer98Doc* pDoc;

   pDoc = GetDocument();
   pCmdUI->Enable( pDoc->GetStartPosition() != NULL );
}

void CTestContainer98View::OnControlDrawMetaFile()
{
   IUnknownPtr pObject;
   CMetaFileWnd* pWnd;
   CString strWindowTitle;

   ASSERT( m_lpSelectedItems.GetCount() == 1 );
   ASSERT( m_pSelection != NULL );

   pObject = m_pSelection->m_lpObject;

   strWindowTitle.LoadString( IDS_METAFILEWINDOWTITLE );
	pWnd = new CMetaFileWnd;
   pWnd->Create( NULL, strWindowTitle );
   pWnd->SetObject( pObject );
   pWnd->ShowWindow( SW_SHOW );
}

void CTestContainer98View::OnUpdateControlDrawMetaFile( CCmdUI* pCmdUI )
{
   pCmdUI->Enable( m_lpSelectedItems.GetCount() == 1 );
}
