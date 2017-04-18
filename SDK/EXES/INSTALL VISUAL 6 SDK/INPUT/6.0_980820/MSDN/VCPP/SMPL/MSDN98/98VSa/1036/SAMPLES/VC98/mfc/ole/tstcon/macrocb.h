#if !defined(AFX_MACROCOMBOBOX_H__4E83BE2F_3F5E_11D1_8E47_00C04FB68D60__INCLUDED_)
#define AFX_MACROCOMBOBOX_H__4E83BE2F_3F5E_11D1_8E47_00C04FB68D60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MacroComboBox.H : header file
//

#define MCBN_RETURN WM_APP

/////////////////////////////////////////////////////////////////////////////
// CMacroComboBox window

class CMacroComboBox : public CComboBox
{
// Construction
public:
	CMacroComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMacroComboBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMacroComboBox();

protected:
   void AddMRUEntry( LPCTSTR pszMacroName );

	// Generated message map functions
protected:
	//{{AFX_MSG(CMacroComboBox)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MACROCOMBOBOX_H__4E83BE2F_3F5E_11D1_8E47_00C04FB68D60__INCLUDED_)
