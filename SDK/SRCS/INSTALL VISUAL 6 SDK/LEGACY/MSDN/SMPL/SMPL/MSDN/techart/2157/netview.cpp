// dldmfvw.cpp : implementation of the CNetView class
//

#include "stdafx.h"
#include "dldetect.h"
#include "tpprops.h"
#include "gridsize.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetView

IMPLEMENT_DYNCREATE(CNetView, CView)

BEGIN_MESSAGE_MAP(CNetView, CScrollView)
	//{{AFX_MSG_MAP(CNetView)
	ON_COMMAND(ID_NET_NEWTRANSITIONUNDERCURSOR, OnNetNewtransitionundercursor)
	ON_WM_CREATE()
	ON_COMMAND(ID_NET_NEWPLACEUNDERCURSOR, OnNetNewplaceundercursor)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	ON_COMMAND(ID_NET_DELETEMARKEDOBJECTDEL, OnNetDeletemarkedobjectdel)
	ON_COMMAND(ID_NET_SNAPNETTOGRID, OnNetSnapnettogrid)
	ON_COMMAND(ID_NET_SETGRIDSIZE, OnNetSetgridsize)
	ON_COMMAND(ID_NET_EDITPROPERTIESFORMARKEDOBJECTENTER, OnNetEditpropertiesformarkedobjectenter)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetView construction/destruction

CNetView::CNetView()
{
m_places = (place *)0;
m_transitions = (transition *)0;
m_iSnapSize = 10;
InitializeCriticalSection(&m_csDrawGuard);
	// TODO: add construction code here
}

CNetView::~CNetView()
{
DeleteCriticalSection(&m_csDrawGuard);
}

void CNetView::OnInitialUpdate()
{
SetScrollSizes(MM_TEXT,CSize(100,100));
}

int CNetView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
if (CView::OnCreate(lpCreateStruct) == -1)
return -1;

m_SizeNet.cx=0;
m_SizeNet.cy=0;
m_pDocument->SetModifiedFlag(FALSE);
m_pAttachedDocument = GetDocument();
m_tpActivated = (TP *)0;
GetDocument()->cnvAttachedView=this;
return 0;
}

void CNetView::OnDestroy()
{
	CView::OnDestroy();
	// TODO: Add your message handler code here
	   NukeNet();
}


/////////////////////////////////////////////////////////////////////////////
// CNetView drawing

void CNetView::OnPrepareDC(CDC *pDC, CPrintInfo *pInfo)
{
SetScrollSizes(MM_TEXT,m_SizeNet);

CScrollView::OnPrepareDC(pDC, pInfo);
}

void CNetView::OnDraw(CDC* dc)
{
	dc->SetBkMode(TRANSPARENT);
	EnterCriticalSection(&m_csDrawGuard);
				 if (m_places != (TP *)0)
				   m_places->DrawYourself(dc);
				 if (m_transitions != (TP *)0)
				   m_transitions->DrawYourself(dc);
	LeaveCriticalSection(&m_csDrawGuard);
}

void CNetView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
InvalidateRect(NULL,TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// CNetView diagnostics

#ifdef _DEBUG
void CNetView::AssertValid() const
{
	CView::AssertValid();
}

void CNetView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPetriNetDoc* CNetView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPetriNetDoc)));
	return (CPetriNetDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNetView message handlers


void CNetView::OnNetNewtransitionundercursor()
{
POINT ptCursor;
transition *t;
GetCursorPos(&ptCursor);
ScreenToClient(&ptCursor);
ConvertScreenToLog(&ptCursor);
t = new transition(ptCursor.x,ptCursor.y);
if (m_transitions == (TP *)0)
m_transitions = t;
else
m_transitions->AppendAtEnd(t);
m_pAttachedDocument->SetModifiedFlag(TRUE);
RecalcScrollDimensions(ptCursor.x,ptCursor.y,TRUE);
InvalidateRect(t->GetRect(GetScrollPosition()),FALSE);

}

void CNetView::OnNetNewplaceundercursor()

{
POINT ptCursor;
place *p;
GetCursorPos(&ptCursor);
ScreenToClient(&ptCursor);
ConvertScreenToLog(&ptCursor);
p = new	place(ptCursor.x,ptCursor.y);
if (m_places == (TP *)0)
m_places = p;
else
m_places->AppendAtEnd(p);
m_pAttachedDocument->SetModifiedFlag(TRUE);
RecalcScrollDimensions(ptCursor.x,ptCursor.y,TRUE);
InvalidateRect(p->GetRect(GetScrollPosition()),FALSE);
}




void CNetView::OnLButtonDown(UINT nFlags, CPoint point)
{
KillTimer(1); //to cancel all pending requests...
			   //First of all, figure out if there is something under the cursor.
TP *tp=(TP *)0;
point=ConvertScreenToLog(point);
if (m_places) tp=m_places->Hittest(point.x,point.y);
if (tp == (TP *)0 && m_transitions)
	tp =m_transitions->Hittest(point.x,point.y);
// If there is an activated object, then the user tried to draw a
// connection from the activated to the current element, so
// connect them. If there was no previously activated
// element, then just activate this sucker.
if (m_tpActivated)
{ if (tp)
  { if (tp == m_tpActivated)
       { m_tpActivated->Alert(FALSE);
	     InvalidateRect(m_tpActivated->GetRect(GetScrollPosition()),FALSE);
	     m_tpActivated = (TP *)0;
		 return;
	   };
    if (tp->iType&m_tpActivated->iType&(TRANSITION_TYPE|PLACE_TYPE))
	 {
	  MessageBeep(-1);
	  return;
	 }
	else
	 {
	  if (!(m_tpActivated->Connect(tp)))
	    MessageBeep(-1);
	  else
	   {m_tpActivated->Alert(FALSE);
// out of pure convenience for the user, we expect that he/she wants to
// keep making connections out of this new element, so we activate the
// current one. But to avoid confusion since the user might not have
// wanted this, we set a one-shot timer after which the activation is
// cancelled.
       m_tpActivated=tp;
       m_tpActivated->Alert(TRUE);
	   m_pAttachedDocument->SetModifiedFlag(TRUE);
       SetTimer(1,2000,NULL);
	   };
	 };
  }
// tpActivated is set, but the drop target was no
// valid object. Thus we assume that the user has
// changed his mind and does not want to do anything
// with the object.
  else {m_tpActivated->Alert(FALSE);
        InvalidateRect(m_tpActivated->GetRect(GetScrollPosition()),FALSE);
        m_tpActivated=(TP *)0;
        return;
       };

}
// eventually, tpActivated was not set to begin with,
// so we just set it to the newly activated element...
else
if (tp)
{
  m_tpActivated=tp;
  m_tpActivated->Alert(TRUE);
  InvalidateRect(m_tpActivated->GetRect(GetScrollPosition()),FALSE);
  return;
};
InvalidateRect(NULL,FALSE);

}

void CNetView::OnTimer(UINT nIDEvent)
{
KillTimer(1);
if (m_tpActivated)
 {  m_tpActivated->Alert(FALSE);
    InvalidateRect(m_tpActivated->GetRect(GetScrollPosition()),FALSE);
    m_tpActivated=(TP *)0;
 };

}

void CNetView::OnLButtonUp(UINT nFlags, CPoint point)
{
// we only do something if  there is an activated object and
// we are currently not on that same object... this indicates
// a move...
point=ConvertScreenToLog(point);
if (!m_tpActivated) return;
{
 TP *tp=(TP *)0;
 if (m_places) tp=m_places->Hittest(point.x,point.y);
 if (tp == (TP *)NULL && m_transitions)
  tp =m_transitions->Hittest(point.x,point.y);
  if (tp==(TP *)0 || tp == m_tpActivated)
  {if (m_tpActivated->Reposition(point.x,point.y))
   {RecalcScrollDimensions(point.x,point.y,TRUE);
    m_tpActivated->Alert(FALSE);
    InvalidateRect(NULL,TRUE);
    m_tpActivated=(TP *)0;
   };
  };
};

}

void CNetView::OnLButtonDblClk(UINT nFlags, CPoint point)
{ OnNetEditpropertiesformarkedobjectenter();
}

// Helper functions

void CNetView::RecalcScrollDimensions(int NewX, int NewY, BOOL bDirection)
{
if (bDirection)
{
m_SizeNet.cx=max(m_SizeNet.cx,NewX+PLACEXEXTENSION);
m_SizeNet.cy=max(m_SizeNet.cy,NewY+PLACEYEXTENSION);
}
else
{ // first check if the object we removed is somewhere on the border.
  // if not, do nothing; otherwise, we must traverse all objects to see
  // which one is the next coordinate-wise...
  if ((NewX+PLACEXEXTENSION < m_SizeNet.cx) && (NewY+PLACEYEXTENSION < m_SizeNet.cy)) return;
  TP *tpNext = m_places;
  m_SizeNet.cx=m_SizeNet.cy=0;
  while (tpNext != (TP *)0)
   {RecalcScrollDimensions(tpNext->iX,tpNext->iY,TRUE);
    tpNext=tpNext->Succ();
   };
  tpNext = m_transitions;
  while (tpNext != (TP *)0)
   {RecalcScrollDimensions(tpNext->iX,tpNext->iY,TRUE);
    tpNext=tpNext->Succ();
   }; 
};
   
}


void CNetView::ConvertScreenToLog(POINT *pt)
{CPoint result=GetScrollPosition();
 pt->x+=result.x;
 pt->y+=result.y;
}

CPoint CNetView::ConvertScreenToLog(CPoint pt)
{ CPoint result(pt);
  result.Offset(GetScrollPosition());
  return result;
}




void CNetView::DeleteLinks(TPLIST *tpList)
{ if (tpList != (TPLIST *)0)
     DeleteLinks(tpList->Succ());
  else return;
     delete (tpList);
} 

void CNetView::DeleteChain(TP *objects, BOOL bType)
{ if (objects != (TP *)0)
     DeleteChain(objects->Succ(),bType);
  else return;
   if (bType)
	 {DeleteLinks(((transition *)objects)->GetConnections(FALSE));
	  DeleteLinks(((transition *)objects)->GetConnections(TRUE));
	 };
     delete (objects);
}

void CNetView::NukeNet()
{
DeleteChain(m_places,FALSE);
DeleteChain(m_transitions,TRUE);
m_places = (place *)0;
m_transitions = (transition *)0;
}


#define DUMPIT WriteFile(hFile,lpMem,strlen(lpMem),&iWritten,NULL)

void CNetView::DumpCoordinateData(HANDLE hFile)
{ char lpMem[40];
  unsigned long iWritten;
  TP *tpTemp;
// first dump all of the places' data
 tpTemp=m_places;
 while (tpTemp!=(TP *)0)
  {LPSTR lpBuf=tpTemp->szName.GetBuffer(20);
   if (tpTemp->szName.IsEmpty()) lpBuf="no";
   wsprintf(lpMem,"%d %s %d %d\n",tpTemp->iOrdinal,lpBuf,tpTemp->iX,tpTemp->iY);
   tpTemp->szName.ReleaseBuffer();
   DUMPIT;
   tpTemp=tpTemp->Succ();
  };
 tpTemp=m_transitions;
 while (tpTemp!=(TP *)0)
  {LPSTR lpBuf=tpTemp->szName.GetBuffer(20);
   if (tpTemp->szName.IsEmpty()) lpBuf="no";
   wsprintf(lpMem,"%d %s %d %d\n",tpTemp->iOrdinal,lpBuf,tpTemp->iX,tpTemp->iY);
   DUMPIT;
   tpTemp->szName.ReleaseBuffer();
   tpTemp=tpTemp->Succ();
  };

}

void CNetView::Cleanup(transition *tp)
{
EnterCriticalSection(&m_csDrawGuard);
 DeleteLinks(tp->GetConnections(FALSE));
 DeleteLinks(tp->GetConnections(TRUE));
LeaveCriticalSection(&m_csDrawGuard);
 GetDocument()->SetModifiedFlag(TRUE);
 InvalidateRect(NULL,TRUE);

}

void CNetView::TraverseTransitions(place *pl)
{transition *tpt=m_transitions;
 while (tpt!=(transition *)0)
	    {tpt->DisConnect(pl);
		 tpt=tpt->Succ();
        };
 GetDocument()->SetModifiedFlag(TRUE);
 InvalidateRect(NULL,TRUE);

};

void CNetView::FinishPlace(place *pVictim)
{
 TraverseTransitions(pVictim);
 m_tpActivated=(TP *)0;
 RecalcScrollDimensions(pVictim->iX,pVictim->iY,FALSE);
 delete (pVictim);
};

void CNetView::FinishTransition(transition *tVictim)
{
 Cleanup((transition *)m_tpActivated);
 m_tpActivated=(TP *)0;
 RecalcScrollDimensions(tVictim->iX,tVictim->iY,FALSE);
 delete (tVictim);
};

void CNetView::OnNetDeletemarkedobjectdel()
{ 
	if (!m_tpActivated) 
	 {MessageBeep(-1);
	  return;
	 };
// the activated object can be either a place or a transition -- we don't
// know offhand; if it's a place, we must scan the list of transitions to
// see whether the transition is connected to that place and first remove
// all those connections before removing the object itself; otherwise all
// we need to do is remove the transition.
place *pVictim;
if (m_places==m_tpActivated)
{pVictim=m_places;
 m_places=pVictim->Succ();
 FinishPlace(pVictim);
 return;
};

place *tpp=m_places;
while (tpp!=(place *)0 && tpp->Succ()!=(place *)0)
{  if (tpp->Succ()==m_tpActivated) 
// we found the object... now let's go to work...
      {pVictim=tpp->Succ();
	   tpp->AppendUpFront(pVictim->Succ());
	   FinishPlace(pVictim);
       return;
	  };

tpp=tpp->Succ();	
}; // while (tpp!=(TP *)0)

transition *tVictim;

if (m_transitions==m_tpActivated)
{tVictim=m_transitions;
 m_transitions=tVictim->Succ();
 FinishTransition(tVictim);
 return;
};

transition *tpt=m_transitions;
while (tpt!=(transition *)0 && tpt->Succ()!=(transition *)0)
{  if (tpt->Succ()==m_tpActivated)
   {
    tVictim=tpt->Succ();
    tpt->AppendUpFront(tVictim->Succ());
	FinishTransition(tVictim);
    return;
   };
  tpt=tpt->Succ();
} // while (tpt!=(transition *)0)

}

CString CNetView::GrabNameFromNet(BOOL bType, int iIndex)
{ 
// bType==FALSE implies transition, TRUE place
TP *tpRoot;
if (bType) tpRoot = m_places; else tpRoot = m_transitions;
while (tpRoot != (TP *)0)
{ if (tpRoot->iOrdinal == iIndex)
     return tpRoot->szName;
  tpRoot = tpRoot->Succ();
};
return "";
}

void CNetView::OnNetSnapnettogrid()
{
 if (m_places!= (TP *)0)
  m_places->SnapToGrid(m_iSnapSize);
 if (m_transitions!= (TP *)0)
  m_transitions->SnapToGrid(m_iSnapSize);
 m_pDocument->SetModifiedFlag(TRUE);
 InvalidateRect(NULL,TRUE);
	
}

void CNetView::OnNetSetgridsize()
{ gridsize gds(NULL);
  gds.m_GridSize=m_iSnapSize;
  gds.DoModal();
  m_iSnapSize=gds.m_GridSize;
	
}

void CNetView::OnNetEditpropertiesformarkedobjectenter()
{
CTPProps cdProps(NULL);
if (m_tpActivated!=(TP *)0)
{ BOOL bInvalidate = FALSE;
  cdProps.m_iType=m_tpActivated->iType;
  cdProps.m_Name=m_tpActivated->szName;
  if (m_tpActivated->iType&PLACE_TYPE)cdProps.m_Marked=((place *)m_tpActivated)->GetMark();
  cdProps.DoModal();
  m_tpActivated->Alert(FALSE);
  m_tpActivated->iType = cdProps.m_iType;
  if (cdProps.m_Name != m_tpActivated->szName)
    bInvalidate = TRUE;
  m_tpActivated->Name(cdProps.m_Name);
  if (m_tpActivated->iType&PLACE_TYPE)
    ((place *)m_tpActivated)->Mark(cdProps.m_Marked);
  m_tpActivated=(TP *)0;
  KillTimer(1);
  GetDocument()->SetModifiedFlag(TRUE);
  InvalidateRect(NULL,bInvalidate);
};
	
}

