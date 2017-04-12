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

// BCGUserTool.h: interface for the CBCGUserTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGUSERTOOL_H__80D80814_B943_11D3_A713_009027900694__INCLUDED_)
#define AFX_BCGUSERTOOL_H__80D80814_B943_11D3_A713_009027900694__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class BCGCONTROLBARDLLEXPORT CBCGUserTool : public CObject  
{
	friend class CBCGUserToolsManager;

	DECLARE_SERIAL(CBCGUserTool)

public:
// Construction
	CBCGUserTool();
	virtual ~CBCGUserTool();

// Overrides
	virtual void Serialize (CArchive& ar);
	virtual BOOL Invoke ();
	virtual HICON SetToolIcon ();

// Operations:
public:
	void DrawToolIcon (CDC* pDC, const CRect& rectImage);
	void SetCommand (LPCTSTR lpszCmd);

protected:
	virtual HICON LoadDefaultIcon ();
	virtual void DeleteIcon ();

// Attributes:
public:
	UINT GetCommandId () const
	{
		return m_uiCmdId;
	}

	const CString& GetCommand () const
	{
		return m_strCommand;
	}

	CString		m_strLabel;
	CString		m_strArguments;
	CString		m_strInitialDirectory;

protected:
	UINT		m_uiCmdId;
	CString		m_strCommand;
	HICON		m_hIcon;
};

#endif // !defined(AFX_BCGUSERTOOL_H__80D80814_B943_11D3_A713_009027900694__INCLUDED_)
