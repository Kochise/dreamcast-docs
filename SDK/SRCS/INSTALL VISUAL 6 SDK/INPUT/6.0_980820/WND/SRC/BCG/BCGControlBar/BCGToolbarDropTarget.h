//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This source code is a part of BCGControlBar library.
// You may use, compile or redistribute it as part of your application 
// for free. You cannot redistribute it as a part of a software development 
// library without the agreement of the author. If the sources are 
// distributed along with the application, you should leave the original 
// copyright notes in the source code without any changes.
// This code can be used WITHOUT ANY WARRANTIES on your own risk.
// 
// For the latest updates to this library, check my site:
// http://welcome.to/bcgsoft
// 
// Stas Levin <bcgsoft@yahoo.com>
//*******************************************************************************

#if !defined(AFX_BCGTOOLBARDROPTARGET_H__E0D2D9D6_C494_11D1_A646_00A0C93A70EC__INCLUDED_)
#define AFX_BCGTOOLBARDROPTARGET_H__E0D2D9D6_C494_11D1_A646_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BCGToolbarDropTarget.h : header file
//

#ifndef BCG_NO_CUSTOMIZATION

#ifndef __AFXOLE_H__
#include <afxole.h>
#endif

class CBCGToolBar;

/////////////////////////////////////////////////////////////////////////////
// CBCGToolbarDropTarget command target

class CBCGToolbarDropTarget : public COleDropTarget
{
public:
	CBCGToolbarDropTarget();
	virtual ~CBCGToolbarDropTarget();

// Attributes
public:
protected:
	CBCGToolBar*	m_pOwner;

// Operations
public:
	BOOL Register (CBCGToolBar *pOwner);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGToolbarDropTarget)
	public:
	virtual DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave(CWnd* pWnd);
	virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDropEx(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, DROPEFFECT dropList, CPoint point);
	//}}AFX_VIRTUAL

// Implementation

	// Generated message map functions
	//{{AFX_MSG(CBCGToolbarDropTarget)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // BCG_NO_CUSTOMIZATION

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGTOOLBARDROPTARGET_H__E0D2D9D6_C494_11D1_A646_00A0C93A70EC__INCLUDED_)
