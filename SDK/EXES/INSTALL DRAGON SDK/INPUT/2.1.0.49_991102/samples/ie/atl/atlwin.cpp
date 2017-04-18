// This is a part of the Active Template Library.
// Copyright (C) 1996-1997 Microsoft Corporation
// All rights reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#ifndef __ATLWIN_H__
	#error atlwin.cpp requires atlwin.h to be included first
#endif

#ifndef ATL_NO_NAMESPACE
namespace ATL
{
#endif

/////////////////////////////////////////////////////////////////////////////
// CWndProcThunk

void CWndProcThunk::Init(WNDPROC proc, void* pThis)
{
#if defined(_M_PPC)
    thunk.lis_r12 = 0x3d800000 | HIWORD(proc);
    thunk.ori_r12 = 0x618C0000 | LOWORD(proc);
    thunk.lis_r3 = 0x3c600000 | HIWORD(pThis);
    thunk.mtctr_r12 = 0x7d8903a6;
    thunk.ori_r3 = 0x60630000 | LOWORD(pThis);
    thunk.bctr = 0x4e800420;
	// write block from data cache and
	//  flush from instruction cache
	FlushInstructionCache(GetCurrentProcess(), &thunk, sizeof(thunk));
#elif defined (_M_ALPHA)
	thunk.ldah_at = (0x279f0000 | HIWORD(proc)) + (LOWORD(proc)>>15);
	thunk.ldah_a0 = (0x261f0000 | HIWORD(pThis)) + (LOWORD(pThis)>>15);
	thunk.lda_at = 0x239c0000 | LOWORD(proc);
	thunk.lda_a0 = 0x22100000 | LOWORD(pThis);
	thunk.jmp = 0x6bfc0000;
	FlushInstructionCache(GetCurrentProcess(), &thunk, sizeof(thunk));
#elif defined (_M_IX86)
	thunk.m_mov = 0xb9;
	thunk.m_this = (DWORD)pThis;
	thunk.m_jmp = 0xe9;
#ifdef MapPtrToProcess
	thunk.m_relproc = (int)MapPtrToProcess(proc, GetCurrentProcess()) - (((int)MapPtrToProcess(this,GetCurrentProcess())) + sizeof(_WndProcThunk));
#else
	thunk.m_relproc = (int)proc - ((int)this+sizeof(_WndProcThunk));
#endif
#elif defined(SH3) || defined(SH4)
	thunk.m_mov_r0 = 0xd001;
	thunk.m_mov_r1 = 0xd402;
	thunk.m_jmp = 0x402b;
	thunk.m_nop = 0x0009;
	thunk.m_pFunc = (DWORD)proc;
	thunk.m_pThis = (DWORD)pThis;
	FlushInstructionCache(GetCurrentProcess(), &thunk, sizeof(thunk));
#elif defined (_MIPS_)
	thunk.m_pFuncHi = HIWORD(proc);
	thunk.m_lui_t0  = 0x3c08;
	thunk.m_pFuncLo = LOWORD(proc);
	thunk.m_ori_t0  = 0x3508;
	thunk.m_pThisHi = HIWORD(pThis);
	thunk.m_lui_a0  = 0x3c04;
	thunk.m_jr_t0   = 0x01000008;
	thunk.m_pThisLo = LOWORD(pThis);
	thunk.m_ori_a0  = 0x3484;
	FlushInstructionCache(GetCurrentProcess(), &thunk, sizeof(thunk));
#elif defined (_ARM_)
	thunk.m_mov_r0 = 0xE59F0000;
	thunk.m_mov_pc = 0xE59FF000;
	thunk.m_pThis = (DWORD)pThis;
	thunk.m_pFunc = (DWORD)proc;
#else
#error Only ARM, PPC, ALPHA, SH3, SH4, MIPS and X86 supported
#endif
}

/////////////////////////////////////////////////////////////////////////////
// CWindow

#ifndef UNDER_CE
HWND CWindow::GetDescendantWindow(int nID) const
{
	_ASSERTE(::IsWindow(m_hWnd));

	// GetDlgItem recursive (return first found)
	// breadth-first for 1 level, then depth-first for next level

	// use GetDlgItem since it is a fast USER function
	HWND hWndChild, hWndTmp;
	CWindow wnd;
	if((hWndChild = ::GetDlgItem(m_hWnd, nID)) != NULL)
	{
		if(::GetTopWindow(hWndChild) != NULL)
		{
			// children with the same ID as their parent have priority
			wnd.Attach(hWndChild);
			hWndTmp = wnd.GetDescendantWindow(nID);
			if(hWndTmp != NULL)
				return hWndTmp;
		}
		return hWndChild;
	}

	// walk each child
	for(hWndChild = ::GetTopWindow(m_hWnd); hWndChild != NULL;
		hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
	{
		wnd.Attach(hWndChild);
		hWndTmp = wnd.GetDescendantWindow(nID);
		if(hWndTmp != NULL)
			return hWndTmp;
	}

	return NULL;    // not found
}

void CWindow::SendMessageToDescendants(UINT message, WPARAM wParam/*= 0*/, LPARAM lParam/*= 0*/, BOOL bDeep/* = TRUE*/)
{
	CWindow wnd;
	for(HWND hWndChild = ::GetTopWindow(m_hWnd); hWndChild != NULL;
		hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
	{
		::SendMessage(hWndChild, message, wParam, lParam);

		if(bDeep && ::GetTopWindow(hWndChild) != NULL)
		{
			// send to child windows after parent
			wnd.Attach(hWndChild);
			wnd.SendMessageToDescendants(message, wParam, lParam, bDeep);
		}
	}
}
#endif //!UNDER_CE

BOOL CWindow::CenterWindow(HWND hWndCenter/* = NULL*/)
{
	_ASSERTE(::IsWindow(m_hWnd));

	// determine owner window to center against
	DWORD dwStyle = GetStyle();
	if(hWndCenter == NULL)
	{
		if(dwStyle & WS_CHILD)
			hWndCenter = ::GetParent(m_hWnd);
		else
			hWndCenter = ::GetWindow(m_hWnd, GW_OWNER);
	}

	// get coordinates of the window relative to its parent
	RECT rcDlg;
	::GetWindowRect(m_hWnd, &rcDlg);
	RECT rcArea;
	RECT rcCenter;
	HWND hWndParent;
	if(!(dwStyle & WS_CHILD))
	{
		// don't center against invisible or minimized windows
		if(hWndCenter != NULL)
		{
			DWORD dwStyle = ::GetWindowLong(hWndCenter, GWL_STYLE);
#ifdef UNDER_CE
			if(!(dwStyle & WS_VISIBLE))
#else
			if(!(dwStyle & WS_VISIBLE) || (dwStyle & WS_MINIMIZE))
#endif
				hWndCenter = NULL;
		}

#ifdef UNDER_CE
		rcArea.left = 0;
		rcArea.right = rcArea.left + GetSystemMetrics(SM_CXSCREEN);
		rcArea.top = 0;
		rcArea.bottom = rcArea.top + GetSystemMetrics(SM_CYSCREEN);
#else
		// center within screen coordinates
		::SystemParametersInfo(SPI_GETWORKAREA, NULL, &rcArea, NULL);
#endif

		if(hWndCenter == NULL)
			rcCenter = rcArea;
		else
			::GetWindowRect(hWndCenter, &rcCenter);
	}
	else
	{
		// center within parent client coordinates
		hWndParent = ::GetParent(m_hWnd);
		_ASSERTE(::IsWindow(hWndParent));

		::GetClientRect(hWndParent, &rcArea);
		_ASSERTE(::IsWindow(hWndCenter));
		::GetClientRect(hWndCenter, &rcCenter);
		::MapWindowPoints(hWndCenter, hWndParent, (POINT*)&rcCenter, 2);
	}

	int DlgWidth = rcDlg.right - rcDlg.left;
	int DlgHeight = rcDlg.bottom - rcDlg.top;

	// find dialog's upper left based on rcCenter
	int xLeft = (rcCenter.left + rcCenter.right) / 2 - DlgWidth / 2;
	int yTop = (rcCenter.top + rcCenter.bottom) / 2 - DlgHeight / 2;

	// if the dialog is outside the screen, move it inside
	if(xLeft < rcArea.left)
		xLeft = rcArea.left;
	else if(xLeft + DlgWidth > rcArea.right)
		xLeft = rcArea.right - DlgWidth;

	if(yTop < rcArea.top)
		yTop = rcArea.top;
	else if(yTop + DlgHeight > rcArea.bottom)
		yTop = rcArea.bottom - DlgHeight;

	// map screen coordinates to child coordinates
	return ::SetWindowPos(m_hWnd, NULL, xLeft, yTop, -1, -1,
		SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

BOOL CWindow::ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	_ASSERTE(::IsWindow(m_hWnd));

	DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
	DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
	if(dwStyle == dwNewStyle)
		return FALSE;

	::SetWindowLong(m_hWnd, GWL_STYLE, dwNewStyle);
	if(nFlags != 0)
	{
		::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
	}

	return TRUE;
}

BOOL CWindow::ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	_ASSERTE(::IsWindow(m_hWnd));

	DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
	if(dwStyle == dwNewStyle)
		return FALSE;

	::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwNewStyle);
	if(nFlags != 0)
	{
		::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
	}

	return TRUE;
}

BOOL CWindow::GetWindowText(BSTR& bstrText)
{
	USES_CONVERSION;
	_ASSERTE(::IsWindow(m_hWnd));

	int nLen = ::GetWindowTextLength(m_hWnd);
	if(nLen == 0)
		return FALSE;

	LPTSTR lpszText = (LPTSTR)_alloca((nLen+1)*sizeof(TCHAR));

	if(!::GetWindowText(m_hWnd, lpszText, nLen+1))
		return FALSE;

	bstrText = ::SysAllocString(T2OLE(lpszText));

	return (bstrText != NULL) ? TRUE : FALSE;
}

HWND CWindow::GetTopLevelParent() const
{
	_ASSERTE(::IsWindow(m_hWnd));

	HWND hWndParent = m_hWnd;
	HWND hWndTmp;
	while((hWndTmp = ::GetParent(hWndParent)) != NULL)
		hWndParent = hWndTmp;

	return hWndParent;
}

HWND CWindow::GetTopLevelWindow() const
{
	_ASSERTE(::IsWindow(m_hWnd));

	HWND hWndParent = m_hWnd;
	HWND hWndTmp = hWndParent;

	while(hWndTmp != NULL)
	{
		hWndTmp = (::GetWindowLong(hWndParent, GWL_STYLE) & WS_CHILD) ? ::GetParent(hWndParent) : ::GetWindow(hWndParent, GW_OWNER);
		hWndParent = hWndTmp;
	}

	return hWndParent;
}

/////////////////////////////////////////////////////////////////////////////
// CDynamicChain

CDynamicChain::~CDynamicChain()
{
	if(m_pChainEntry != NULL)
	{
		for(int i = 0; i < m_nEntries; i++)
		{
			if(m_pChainEntry[i] != NULL)
				delete m_pChainEntry[i];
		}

		delete [] m_pChainEntry;
	}
}

BOOL CDynamicChain::SetChainEntry(DWORD dwChainID, CMessageMap* pObject, DWORD dwMsgMapID /* = 0 */)
{
// first search for an existing entry

	for(int i = 0; i < m_nEntries; i++)
	{
		if(m_pChainEntry[i] != NULL && m_pChainEntry[i]->m_dwChainID == dwChainID)
		{
			m_pChainEntry[i]->m_pObject = pObject;
			m_pChainEntry[i]->m_dwMsgMapID = dwMsgMapID;
			return TRUE;
		}
	}

// create a new one

	ATL_CHAIN_ENTRY* pEntry = NULL;
	ATLTRY(pEntry = new ATL_CHAIN_ENTRY);

	if(pEntry == NULL)
		return FALSE;

// search for an empty one

	for(i = 0; i < m_nEntries; i++)
	{
		if(m_pChainEntry[i] == NULL)
		{
			m_pChainEntry[i] = pEntry;
			return TRUE;
		}
	}

// add a new one

	ATL_CHAIN_ENTRY** ppNew = NULL;
	ATLTRY(ppNew = new ATL_CHAIN_ENTRY*[m_nEntries + 1]);

	if(ppNew == NULL)
	{
		delete pEntry;
		return FALSE;
	}

	pEntry->m_dwChainID = dwChainID;
	pEntry->m_pObject = pObject;
	pEntry->m_dwMsgMapID = dwMsgMapID;

	if(m_pChainEntry != NULL)
	{
		memcpy(ppNew, m_pChainEntry, m_nEntries * sizeof(ATL_CHAIN_ENTRY*));
		delete [] m_pChainEntry;
	}

	m_pChainEntry = ppNew;

	m_pChainEntry[m_nEntries] = pEntry;

	m_nEntries++;

	return TRUE;
}

BOOL CDynamicChain::RemoveChainEntry(DWORD dwChainID)
{
	for(int i = 0; i < m_nEntries; i++)
	{
		if(m_pChainEntry[i] != NULL && m_pChainEntry[i]->m_dwChainID == dwChainID)
		{
			delete m_pChainEntry[i];
			m_pChainEntry[i] = NULL;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CDynamicChain::CallChain(DWORD dwChainID, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult)
{
	for(int i = 0; i < m_nEntries; i++)
	{
		if(m_pChainEntry[i] != NULL && m_pChainEntry[i]->m_dwChainID == dwChainID)
			return (m_pChainEntry[i]->m_pObject)->ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult, m_pChainEntry[i]->m_dwMsgMapID);
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CWndClassInfo

ATOM CWndClassInfo::Register(WNDPROC* pProc)
{
	if (m_atom == 0)
	{
		::EnterCriticalSection(&_Module.m_csWindowCreate);
		if(m_atom == 0)
		{
			HINSTANCE hInst = _Module.GetModuleInstance();
			if (m_lpszOrigName != NULL)
			{
				_ASSERTE(pProc != NULL);
				LPCTSTR lpsz = m_wc.lpszClassName;
				WNDPROC proc = m_wc.lpfnWndProc;

#ifdef UNDER_CE
				WNDCLASS wc;
				if(!::GetClassInfo(NULL, m_lpszOrigName, &wc))
				{
					::LeaveCriticalSection(&_Module.m_csWindowCreate);
					return 0;
				}
				memcpy(&m_wc, &wc, sizeof(WNDCLASS));
				pWndProc = m_wc.lpfnWndProc;
				m_wc.lpszClassName = lpsz;
				m_wc.lpfnWndProc = proc;
#else
				WNDCLASSEX wc;
				wc.cbSize = sizeof(WNDCLASSEX);
				if(!::GetClassInfoEx(NULL, m_lpszOrigName, &wc))
				{
					::LeaveCriticalSection(&_Module.m_csWindowCreate);
					return 0;
				}
				memcpy(&m_wc, &wc, sizeof(WNDCLASSEX));
				pWndProc = m_wc.lpfnWndProc;
				m_wc.lpszClassName = lpsz;
				m_wc.lpfnWndProc = proc;
#endif
			}
			else
			{
#ifdef UNDER_CE
				m_wc.hCursor = NULL;
#else
				m_wc.hCursor = ::LoadCursor(m_bSystemCursor ? NULL : hInst,
					m_lpszCursorID);
#endif
			}

			m_wc.hInstance = hInst;
			m_wc.style &= ~CS_GLOBALCLASS;	// we don't register global classes
			if (m_wc.lpszClassName == NULL)
			{
				wsprintf(m_szAutoName, _T("ATL:%8.8X"), (DWORD)&m_wc);
				m_wc.lpszClassName = m_szAutoName;
			}
#ifdef UNDER_CE
			WNDCLASS wcTemp;
			memcpy(&wcTemp, &m_wc, sizeof(WNDCLASS));
			m_atom = ::GetClassInfo(m_wc.hInstance, m_szAutoName, &wcTemp);
			if (m_atom == 0)
				m_atom = ::RegisterClass(&m_wc);
#else
			WNDCLASSEX wcTemp;
			memcpy(&wcTemp, &m_wc, sizeof(WNDCLASSEX));
			m_atom = ::GetClassInfoEx(m_wc.hInstance, m_szAutoName, &wcTemp);
			if (m_atom == 0)
				m_atom = ::RegisterClassEx(&m_wc);
#endif
		}
		::LeaveCriticalSection(&_Module.m_csWindowCreate);
	}

	if (m_lpszOrigName != NULL)
	{
		_ASSERTE(pProc != NULL);
		_ASSERTE(pWndProc != NULL);
		*pProc = pWndProc;
	}
	return m_atom;
}

/////////////////////////////////////////////////////////////////////////////
// CWindowImpl

LRESULT CALLBACK CWindowImplBase::StartWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CWindowImplBase* pT = (CWindowImplBase*)_Module.ExtractCreateWndData();
	_ASSERTE(pT != NULL);
	pT->m_hWnd = hWnd;
	pT->m_thunk.Init(WindowProc, pT);
	WNDPROC pProc = (WNDPROC)&(pT->m_thunk.thunk);
	::SetWindowLong(hWnd, GWL_WNDPROC, (LONG)pProc);
	// if somebody has subclassed us already we can't do anything,
	// so discard return value from SetWindowLong

    //RETAILMSG(1, (_T("Proc: %x\n"), pProc));
	return pProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK CWindowImplBase::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#ifdef _M_IX86
	__asm mov dword ptr[hWnd], ecx
#endif
	CWindowImplBase* pT = (CWindowImplBase*)hWnd;
	LRESULT lRes;
	BOOL bRet = pT->ProcessWindowMessage(pT->m_hWnd, uMsg, wParam, lParam, lRes, 0);
#ifdef UNDER_CE
	if(uMsg == WM_DESTROY)
#else
	if(uMsg == WM_NCDESTROY)
#endif
		pT->m_hWnd = NULL;
	if(bRet)
		return lRes;
	return pT->DefWindowProc(uMsg, wParam, lParam);
}

HWND CWindowImplBase::Create(HWND hWndParent, RECT& rcPos, LPCTSTR szWindowName,
		DWORD dwStyle, DWORD dwExStyle, UINT nID, ATOM atom)
{
	_ASSERTE(m_hWnd == NULL);

	if(atom == 0)
		return NULL;

	_Module.AddCreateWndData(&m_thunk.cd, this);

	if(nID == 0 && (dwStyle & WS_CHILD))
		nID = (UINT)this;

	HWND hWnd = ::CreateWindowEx(dwExStyle, (LPCTSTR)MAKELONG(atom, 0), szWindowName,
		dwStyle, rcPos.left, rcPos.top, rcPos.right - rcPos.left,
		rcPos.bottom - rcPos.top, hWndParent, (HMENU)nID,
		_Module.GetModuleInstance(), NULL);

	_ASSERTE(m_hWnd == hWnd);

	return hWnd;
}

BOOL CWindowImplBase::SubclassWindow(HWND hWnd)
{
	_ASSERTE(m_hWnd == NULL);
	_ASSERTE(::IsWindow(hWnd));
	m_thunk.Init(WindowProc, this);
	WNDPROC pProc = (WNDPROC)&(m_thunk.thunk);
	WNDPROC pfnWndProc = (WNDPROC)::SetWindowLong(hWnd, GWL_WNDPROC, (LONG)pProc);
	if(pfnWndProc == NULL)
		return FALSE;
	m_pfnSuperWindowProc = pfnWndProc;
	m_hWnd = hWnd;
	return TRUE;
}

HWND CWindowImplBase::UnsubclassWindow()
{
	_ASSERTE(m_hWnd != NULL);

	if(!::SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)m_pfnSuperWindowProc))
		return NULL;

	m_pfnSuperWindowProc = ::DefWindowProc;

	HWND hWnd = m_hWnd;
	m_hWnd = NULL;

	return hWnd;
}

#ifndef NO_DIALOGS
/////////////////////////////////////////////////////////////////////////////
// CDialogImplBase

LRESULT CALLBACK CDialogImplBase::StartDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CDialogImplBase* pT = (CDialogImplBase*)_Module.ExtractCreateWndData();
	_ASSERTE(pT != NULL);
	pT->m_hWnd = hWnd;
	pT->m_thunk.Init(DialogProc, pT);
	WNDPROC pProc = (WNDPROC)&(pT->m_thunk.thunk);
	WNDPROC pOldProc = (WNDPROC)::SetWindowLong(hWnd, DWL_DLGPROC, (LONG)pProc);
	// check if somebody has subclassed us already since we don't hold onto it
	ATLTRACE(_T("Subclassing through a hook discarded.\n"));
	return pProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK CDialogImplBase::DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#ifdef _M_IX86
	__asm mov dword ptr[hWnd], ecx
#endif
	CDialogImplBase* pT = (CDialogImplBase*)hWnd;
	LRESULT lRes;
	if(pT->ProcessWindowMessage(pT->m_hWnd, uMsg, wParam, lParam, lRes, 0))
	{
		switch (uMsg)
		{
		case WM_COMPAREITEM:
		case WM_VKEYTOITEM:
		case WM_CHARTOITEM:
		case WM_INITDIALOG:
		case WM_QUERYDRAGICON:
#ifndef GAL_VERSION
		case WM_CTLCOLORMSGBOX:
#endif // !GAL_VERSION
		case WM_CTLCOLOREDIT:
		case WM_CTLCOLORLISTBOX:
		case WM_CTLCOLORBTN:
		case WM_CTLCOLORDLG:
		case WM_CTLCOLORSCROLLBAR:
		case WM_CTLCOLORSTATIC:
			return lRes;
			break;
		}
		if (lRes != 0)
			::SetWindowLong(pT->m_hWnd, DWL_MSGRESULT, lRes);
		return TRUE;
	}
	return FALSE;
}

BOOL CDialogImplBase::EndDialog(int nRetCode)
{
	_ASSERTE(m_hWnd);
	return ::EndDialog(m_hWnd, nRetCode);
}
#endif // #ifndef NO_DIALOGS

/////////////////////////////////////////////////////////////////////////////
// CContainedWindow

LRESULT CALLBACK CContainedWindow::StartWindowProc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	CContainedWindow* pThis = (CContainedWindow*)_Module.ExtractCreateWndData();
	_ASSERTE(pThis != NULL);
	pThis->m_hWnd = hWnd;
	pThis->m_thunk.Init(pThis->WindowProc, pThis);
	WNDPROC pProc = (WNDPROC)&(pThis->m_thunk.thunk);
	WNDPROC pOldProc = (WNDPROC)::SetWindowLong(hWnd, GWL_WNDPROC, (LONG)pProc);
	// check if somebody has subclassed us already since we don't hold onto it
	ATLTRACE(_T("Subclassing through a hook discarded.\n"));
	return pProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK CContainedWindow::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam,
	LPARAM lParam)
{
#ifdef _M_IX86
	__asm mov dword ptr[hWnd], ecx
#endif
	CContainedWindow* pT = (CContainedWindow*)hWnd;
	_ASSERTE(pT->m_hWnd != NULL);
	_ASSERTE(pT->m_pObject != NULL);

	LRESULT lRes;
	BOOL bRet = pT->m_pObject->ProcessWindowMessage(pT->m_hWnd, uMsg, wParam, lParam, lRes, pT->m_dwMsgMapID);
#ifdef UNDER_CE
	if(uMsg == WM_DESTROY)
#else
	if(uMsg == WM_NCDESTROY)
#endif
		pT->m_hWnd = NULL;
	if(bRet)
		return lRes;
	return pT->DefWindowProc(uMsg, wParam, lParam);
}

ATOM CContainedWindow::RegisterWndSuperclass()
{
	ATOM atom = 0;
	LPTSTR szBuff = (LPTSTR)_alloca((lstrlen(m_lpszClassName) + 14) * sizeof(TCHAR));

#ifdef UNDER_CE
	WNDCLASS wc;

	if(::GetClassInfo(NULL, m_lpszClassName, &wc))
	{
#else
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	if(::GetClassInfoEx(NULL, m_lpszClassName, &wc))
	{
#endif

		m_pfnSuperWindowProc = wc.lpfnWndProc;

		wsprintf(szBuff, _T("ATL:%s"), m_lpszClassName);

#ifdef UNDER_CE
		WNDCLASS wc1;
		atom = (ATOM)::GetClassInfo(_Module.GetModuleInstance(), szBuff, &wc1);
#else
		WNDCLASSEX wc1;
		wc1.cbSize = sizeof(WNDCLASSEX);
		atom = (ATOM)::GetClassInfoEx(_Module.GetModuleInstance(), szBuff, &wc1);
#endif

		if(atom == 0)   // register class
		{
			wc.lpszClassName = szBuff;
			wc.lpfnWndProc = StartWindowProc;
			wc.hInstance = _Module.GetModuleInstance();
			wc.style &= ~CS_GLOBALCLASS;	// we don't register global classes

#ifdef UNDER_CE
			atom = ::RegisterClass(&wc);
#else
			atom = ::RegisterClassEx(&wc);
#endif
		}
	}

	return atom;
}

HWND CContainedWindow::Create(HWND hWndParent, RECT& rcPos,
	LPCTSTR szWindowName, DWORD dwStyle, DWORD dwExStyle, UINT nID)
{
	_ASSERTE(m_hWnd == NULL);

	ATOM atom = RegisterWndSuperclass();
	if(atom == 0)
		return NULL;

	_Module.AddCreateWndData(&m_thunk.cd, this);

	if(nID == 0 && (dwStyle & WS_CHILD))
		nID = (UINT)this;

	HWND hWnd = ::CreateWindowEx(dwExStyle, (LPCTSTR)MAKELONG(atom, 0), szWindowName,
							dwStyle,
							rcPos.left, rcPos.top,
							rcPos.right - rcPos.left,
							rcPos.bottom - rcPos.top,
							hWndParent, (HMENU)nID,
							_Module.GetModuleInstance(), this);

	_ASSERTE(m_hWnd == hWnd);
	return hWnd;
}

BOOL CContainedWindow::SubclassWindow(HWND hWnd)
{
	_ASSERTE(m_hWnd == NULL);
	_ASSERTE(::IsWindow(hWnd));

	m_thunk.Init(WindowProc, this);
	WNDPROC pProc = (WNDPROC)&m_thunk.thunk;
	WNDPROC pfnWndProc = (WNDPROC)::SetWindowLong(hWnd, GWL_WNDPROC, (LONG)pProc);
	if(pfnWndProc == NULL)
		return FALSE;
	m_pfnSuperWindowProc = pfnWndProc;
	m_hWnd = hWnd;
	return TRUE;
}

HWND CContainedWindow::UnsubclassWindow()
{
	_ASSERTE(m_hWnd != NULL);

	if(!::SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)m_pfnSuperWindowProc))
		return NULL;
	m_pfnSuperWindowProc = ::DefWindowProc;

	HWND hWnd = m_hWnd;
	m_hWnd = NULL;

	return hWnd;
}

#ifndef ATL_NO_NAMESPACE
}; //namespace ATL
#endif

///////////////////////////////////////////////////////////////////////////////
//All Global stuff goes below this line
///////////////////////////////////////////////////////////////////////////////
