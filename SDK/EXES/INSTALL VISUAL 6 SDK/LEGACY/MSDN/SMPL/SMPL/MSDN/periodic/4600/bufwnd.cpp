////////////////////////////////////////////////////////////////
// Trace buffer class for TRACEWND applet.
//
#include "stdafx.h"
#include "bufwnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CBufWnd, CEdit)
	//{{AFX_MSG_MAP(CBufWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, OnUpdateEditSelectAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CBufWnd::CBufWnd()
{
}

CBufWnd::~CBufWnd()
{
}

//////////////////
// Create a multiline edit control
//
BOOL CBufWnd::Create(CWnd* pParentWnd, UINT nID)
{
	CRect rect;
	return CEdit::Create(
		WS_VISIBLE | WS_CHILD | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE,
		rect, 
		pParentWnd, 
		nID);
}

//////////////////
// Window created: set font to 8pt Courier (monospace font).
//
int CBufWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Use 8pt Courier (monospace)
	LOGFONT logfont;
	memset(&logfont, 0, sizeof(logfont));

	HDC hdc = ::GetDC(NULL);
	ASSERT(hdc);

	// Windows voodoo, something to do with placating "twips", a 
	// mythical genie alleged to live in WYSIWYG software programs.
	//
	strcpy(logfont.lfFaceName, "Courier");
	logfont.lfHeight = -MulDiv(8, ::GetDeviceCaps(hdc, LOGPIXELSY), 72);
	logfont.lfWeight = FW_NORMAL;
	m_font.CreateFontIndirect(&logfont);
	::ReleaseDC(NULL, hdc);

	SetFont(&m_font);

	return 0;
}

/////////////////
// Helper returns TRUE of buffer is empty
//
BOOL CBufWnd::IsEmpty() 
{
	return GetLineCount() <= 1 && LineLength() == 0;
}

void CBufWnd::OnEditClearAll() 
{
	OnEditSelectAll();		// select all...
	Clear();						// ..then delete
}

void CBufWnd::OnUpdateEditClearAll(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!IsEmpty());	// enabled if not empty
}

void CBufWnd::OnEditCopy() 
{
	Copy();						// duh
}

void CBufWnd::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// Enabled if something selected
	int begin, end;
	GetSel(begin, end);
	pCmdUI->Enable(begin != end);
}

void CBufWnd::OnEditSelectAll() 
{
	SetSel(0, -1);		//  select whole buffer
}

void CBufWnd::OnUpdateEditSelectAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!IsEmpty());	// enabled if not empty
}
