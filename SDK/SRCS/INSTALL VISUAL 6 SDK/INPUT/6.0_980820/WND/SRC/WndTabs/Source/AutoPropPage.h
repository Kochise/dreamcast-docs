/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// AutoPropPage.h : header file
//

#if !defined(AFX_AUTOPROPPAGE_H__725700F0_B71A_11D3_BA84_0000861DFCE7__INCLUDED_)
#define AFX_AUTOPROPPAGE_H__725700F0_B71A_11D3_BA84_0000861DFCE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HHSupp.h"

// Jerzy Kaczorowski <kaczoroj@hotmail.com> - template for vars and strs
// Usage:
//
// varpair vars[] = 
// {
//     { &m_var_name, &cfg_var_name },
//     .....
// };
// InitAutoVars(countof(vars), vars);
// 
// and / or
//
// strpair strs[] = 
// {
//     { &m_var_name, &cfg_var_name },
//     .....
// };
// InitAutoStrs(countof(strs), strs);


template<class T>
class TPair
{
public:
	TPair()
	{
		m_pVars = NULL;
		m_cVars = 0;
	}

	~TPair()
	{
		if( m_pVars )
		{
			delete[] m_pVars;
			delete[] m_pOrigVals;
			delete[] m_pPrevVals;
		}
	}
	
	typedef struct { T* pMemberVar; T* pConfigVar; } pair;
	
	// Operations
public:
	void InitAutoVars(int argc, pair *argv)
	{
		m_cVars     = argc;
		m_pVars     = new pair[argc];
		m_pOrigVals = new T[argc];
		m_pPrevVals = new T[argc];
		
		for (int i = 0; i < argc; i++) 
		{
			m_pVars[i]     = argv[i];
			m_pOrigVals[i] = *(m_pVars[i].pMemberVar) = *m_pVars[i].pConfigVar;
		}
	}
	
	bool Changed(T& member)
	{
		int i = FindMemberIndex(member);
		return (*(m_pVars[i].pMemberVar) != m_pPrevVals[i]);
	}

	bool ChangedAny()
	{
		int i;
		
		for (i = 0; i < m_cVars; i++)
		{
			if (*(m_pVars[i].pMemberVar) != m_pPrevVals[i])
				return true;
		}
		
		return false;
	}

	T OrigVal(T& member)
	{
		return m_pOrigVals[FindMemberIndex(member)];
	}

	T PrevVal(T& member)
	{
		return m_pPrevVals[FindMemberIndex(member)];
	}

	void OnCancel()
	{
		if (m_pVars)
		{
			for (int i = 0; i < m_cVars; i++)
				*(m_pVars[i].pMemberVar) = m_pOrigVals[i];
		}
	}

	void OnApply()
	{
		if (m_pVars)
		{
			for (int i = 0; i < m_cVars; i++)
			{
				m_pPrevVals[i] = *(m_pVars[i].pConfigVar);
				*(m_pVars[i].pConfigVar) = *(m_pVars[i].pMemberVar);
			}
		}
	}

	// Implementation
protected:
	int FindMemberIndex(T& member)
	{
		int i;
		
		for (i = 0; i < m_cVars  &&  ((m_pVars[i].pMemberVar) != &member); i++);
		
		ASSERT(i < m_cVars);  // assure legal variable was passed;
		
		return i;
	}

	int		m_cVars;
	pair*	m_pVars;
	T*		m_pOrigVals;
	T*		m_pPrevVals;
};

// define the type for the int and CString types
typedef TPair<int>::pair varpair;
typedef TPair<CString>::pair strpair;

//template for vars and strs end

/////////////////////////////////////////////////////////////////////////////
// CAutoPropPage dialog

class CAutoPropPage : public CHHPropPage
{
    DECLARE_DYNCREATE(CAutoPropPage);

    CAutoPropPage() : CHHPropPage() {}

// Construction
public:
    CAutoPropPage(UINT nIDTemplate, bool bAllowImplicit = true, 
        int iHelpID = -1, UINT nIDCaption = 0) : 
        CHHPropPage(nIDTemplate, bAllowImplicit, iHelpID, 
            nIDCaption) {}

    CAutoPropPage(LPCTSTR lpszTemplateName, bool bAllowImplicit = true, 
        int iHelpID = -1, UINT nIDCaption = 0) : 
        CHHPropPage(lpszTemplateName, bAllowImplicit, iHelpID, 
            nIDCaption) {}

    ~CAutoPropPage();

	TPair<int> m_varpair;
	TPair<CString> m_strpair;

// Operations
public:
	void InitAutoVars(int argc, varpair *argv);
	void InitAutoStrs(int argc, strpair *argv);

    bool Changed(int& member);
    bool Changed(CString& member);
    bool ChangedAny();
    int OrigVal(int& member);
    CString OrigVal(CString& member);
    int PrevVal(int& member);
    CString PrevVal(CString& member);
// Dialog Data
    //{{AFX_DATA(CAutoPropPage)
    //}}AFX_DATA

// Overrides
    // ClassWizard generate virtual function overrides
    virtual void OnCancel();
    virtual BOOL OnApply();
    //{{AFX_VIRTUAL(CAutoPropPage)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CAutoPropPage)
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOPROPPAGE_H__725700F0_B71A_11D3_BA84_0000861DFCE7__INCLUDED_)
