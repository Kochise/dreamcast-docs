// 16bitvw.cpp : implementation of the C16bitView class
//


#include "stdafx.h"
#include "16bit.h"

#include "linkstr.h"
#include "16bitdoc.h"
#include "16bitvw.h"

extern "C" {
#include "receiver.h"

//#define Not_VxD
  
//typedef unsigned long ULONG;
  
//#include "vmm.h"


}

#define HVM DWORD
#define PTCB DWORD

#include "helper.h"

#define VXDLDR_INIT_DEVICE 1
#define VXDLDR_DEVICE_ID 0x27
#define VXDLDR_LoadDevice 1
#define VXDLDR_UnloadDevice 2

char VxDName[_MAX_PATH];
char DLLName[_MAX_PATH];
char VxDModName[]="CALLBACK";
long cbaddress;

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C16bitView

IMPLEMENT_DYNCREATE(C16bitView, CScrollView)

BEGIN_MESSAGE_MAP(C16bitView, CScrollView)
	//{{AFX_MSG_MAP(C16bitView)
	ON_MESSAGE(ID_CUSTOM,OnReceiveRegisterNotify)
	ON_COMMAND(ID_VXD_LOADDIAGNOSTICVXD, OnVxdLoaddiagnosticvxd)
	ON_WM_CREATE()
	ON_COMMAND(ID_VXD_UNLOADDIAGNOSTICVXD, OnVxdUnloaddiagnosticvxd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C16bitView construction/destruction

C16bitView::C16bitView()
{
}

C16bitView::~C16bitView()
{
}

/////////////////////////////////////////////////////////////////////////////
// C16bitView drawing

/*void C16bitView::OnDraw(CDC* pDC)
{
	C16bitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}
*/ 
/////////////////////////////////////////////////////////////////////////////
// C16bitView diagnostics

#ifdef _DEBUG
void C16bitView::AssertValid() const
{
	CView::AssertValid();
}

void C16bitView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C16bitDoc* C16bitView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C16bitDoc)));
	return (C16bitDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C16bitView message handlers

void C16bitView::OnVxdLoaddiagnosticvxd()
{ int iResult;
// first retrieve the name of the VxD from win.ini...
 if (::GetProfileString("callback","VxDLocation","",VxDName,_MAX_PATH) == 0)
  { AfxMessageBox("You need to add the entry VxDLocation=<VxD path> to the [callback] section in win.ini");
    return;
  }; 
 _asm mov ax,VXDLDR_LoadDevice;
 _asm mov dx, offset VxDName;
 _asm call dword ptr [cbaddress];
 _asm jnc GoAhead2;
 _asm mov [iResult],ax;
static char szBuf[30];
sprintf(szBuf,"Error loading VxD: %d",iResult);
 AfxMessageBox(szBuf);
 GoAhead2:
 if (::GetProfileString("callback","DLLLocation","",DLLName,_MAX_PATH) == 0)
  { AfxMessageBox("You need to add the entry DLLLocation=<DLL path> to the [callback] section in win.ini");
    return;
  }; 
 _asm mov ax, offset DLLName;
 _asm mov dx,ds;
 _asm int 60h;
}

int C16bitView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{   lpStrings = (linkstr *)0;
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_Sizes.cx=10;
	m_Sizes.cy=10;     // arbitrary value...
	
	// TODO: Add your specialized creation code here
 _asm xor di,di;
 _asm mov es,di;
 _asm mov ax, 1684h;
 _asm mov bx,VXDLDR_DEVICE_ID;
 _asm int 2fh;
 _asm mov ax,es;
 _asm or ax,di;
 _asm jnz GoAhead;
 AfxMessageBox("Could not find device loader entry point...");
 return(-1);
 GoAhead:
 _asm mov word ptr [cbaddress],di;
 _asm mov word ptr [cbaddress+2],es;

 char szBuf[20];

 wsprintf(szBuf,"callback: %lx",cbaddress);
 GetDocument()->SetTitle(szBuf);	
  Register(m_hWnd);	

	return 0;
}

void C16bitView::OnVxdUnloaddiagnosticvxd()
{
	// TODO: Add your command handler code here
int iResult;
 _asm mov ax,VXDLDR_UnloadDevice;
 _asm mov dx, offset VxDModName;
 _asm mov bx,-1;
 _asm call dword ptr [cbaddress];
 _asm jnc GoAhead3;
 _asm mov [iResult],ax;
static char szBuf[30];
sprintf(szBuf,"Error unloading VxD: %d",iResult);
 AfxMessageBox(szBuf);
 GoAhead3:
 _asm nop;	
}

LONG C16bitView::OnReceiveRegisterNotify(UINT wParam, LONG lParam)
{ MessageBeep(-1);
  CONTBLOCK FAR *cb=(CONTBLOCK FAR *)lParam;
  char szBuf[50];
  switch (cb->dwFlags)
  { case CREATE_THREAD:
    wsprintf(szBuf,"Created thread %8lx for VM %8lx",cb->ThreadHandle,cb->VMHandle);
    break;
    case CREATE_VM:
    wsprintf(szBuf,"Created VM %8lx, initial thread: %8lx",cb->VMHandle,cb->ThreadHandle);
    break;
    case DESTROY_THREAD:
    wsprintf(szBuf,"destroyed thread %8lx",cb->ThreadHandle);
    break;
    case TERMINATE_THREAD:
    wsprintf(szBuf,"terminated thread %8lx",cb->ThreadHandle);
    break;
    case DESTROY_VM:
    wsprintf(szBuf,"destroyed VM %8lx",cb->VMHandle);
    break;
    default:
    wsprintf(szBuf,"illegal code provided...");
  };

  if (lpStrings == (linkstr *)0) lpStrings = new linkstr(szBuf);
  else
  lpStrings->Append(new linkstr(szBuf));
  InvalidateRect(NULL,FALSE);   
  return (LONG)0x234;
}

void C16bitView::OnDraw (CDC *pDC)
{
linkstr *lpCurrent= lpStrings;
CSize iPos(0,0);
CSize iScrollPos(0,0);
int iCurrentPos=0;
while (lpCurrent != (linkstr *)0)
{ CString csNext=*(lpCurrent->GetData());
  iPos=pDC->GetTextExtent(csNext,csNext.GetLength());
  pDC->TextOut(0,iScrollPos.cy,csNext);
  iScrollPos.cy+=iPos.cy;
  iScrollPos.cx=max(iScrollPos.cx,iPos.cx);
  lpCurrent=lpCurrent->Succ();
};
m_Sizes.cx=max(m_Sizes.cx,iScrollPos.cx);
m_Sizes.cy=max(m_Sizes.cy,iScrollPos.cy);
}

void C16bitView::OnPrepareDC(CDC *pDC, CPrintInfo *pInfo)
{
SetScrollSizes(MM_TEXT,m_Sizes);

CScrollView::OnPrepareDC(pDC, pInfo);
}
