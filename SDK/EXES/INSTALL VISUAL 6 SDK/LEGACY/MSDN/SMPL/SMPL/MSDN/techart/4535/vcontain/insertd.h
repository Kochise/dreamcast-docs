//OLE Control Container Verification Application, Version 1.00
//
//Copyright (c) 1995-6 Microsoft Corp, All Rights Reserved
//
//	This is a part of the Microsoft Source Code Samples.
//	This source code is only intended as a supplement to
//	the Microsoft Development Tools and/or WinHelp implementation.
//	See these sources for detailed information regarding the
//	Microsoft sample programs.
//
//Revisions:
//	November 30, 1995	mtm		First Implementation
//
//Purpose:
//	Header file for INSERTD.CPP

#ifndef insertd_h_
#define insertd_h_

#include "afxodlgs.h"

/////////////////////////////////////////////////////////////////////////////
// CInsertDialog dialog

class CCustomListBox : public CListBox
{
public:
    CCustomListBox () {m_wndprocOleClasses = NULL;}
    virtual WNDPROC * GetSuperWndProcAddr () {return (&m_wndprocOleClasses);}
	BOOL AddControlsToList();
protected:
    WNDPROC m_wndprocOleClasses;
    CListBox m_lboxHidden;
};



class CInsertDialog : public COleInsertDialog
{
    DECLARE_DYNAMIC(CInsertDialog)
// Construction
public:
    CInsertDialog(CWnd* pParent = NULL);    // standard constructor

// Operations
    virtual int DoModal();
    virtual BOOL OnInitDialog();
		    
// Dialog Data
    //{{AFX_DATA(CInsertDialog)
    enum { IDD = IDD_INSERT };
    //}}AFX_DATA

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    
protected:
    CCustomListBox m_custlboxOleClasses;

    // Generated message map functions
    //{{AFX_MSG(CInsertDialog)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif
