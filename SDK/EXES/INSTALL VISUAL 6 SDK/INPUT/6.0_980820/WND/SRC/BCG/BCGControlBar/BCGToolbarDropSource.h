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

#if !defined(AFX_BCGTOOLBARDROPSOURCE_H__8ED1EE63_C585_11D1_B110_86F6097DAC36__INCLUDED_)
#define AFX_BCGTOOLBARDROPSOURCE_H__8ED1EE63_C585_11D1_B110_86F6097DAC36__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BCGToolbarDropSource.h : header file
//

#ifndef BCG_NO_CUSTOMIZATION

#ifndef __AFXOLE_H__
#include <afxole.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGToolbarDropSource command target

class CBCGToolbarDropSource : public COleDropSource
{
public:
	CBCGToolbarDropSource();
	virtual ~CBCGToolbarDropSource();

// Attributes
public:
	BOOL	m_bDeleteOnDrop;
	BOOL	m_bEscapePressed;
	BOOL	m_bDragStarted;
	HCURSOR	m_hcurDelete;
	HCURSOR	m_hcurMove;
	HCURSOR	m_hcurCopy;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGToolbarDropSource)
	public:
	virtual SCODE GiveFeedback(DROPEFFECT dropEffect);
	virtual SCODE QueryContinueDrag(BOOL bEscapePressed, DWORD dwKeyState);
	virtual BOOL OnBeginDrag(CWnd* pWnd);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBCGToolbarDropSource)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // BCG_NO_CUSTOMIZATION

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGTOOLBARDROPSOURCE_H__8ED1EE63_C585_11D1_B110_86F6097DAC36__INCLUDED_)
