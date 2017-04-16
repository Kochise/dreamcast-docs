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
//	Implementation of CCustomListBox and CInsertDialog class used
//	to insert controls to be tested.  .

#include "stdafx.h"
#include "vcontain.h"
#include "insertd.h"
#include "olestd.h"
#include <winreg.h>


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define INPROCSERVER	_T("InprocServer32")
#define LOCALSERVER		_T("LocalServer32")

#ifndef OLEUI_CCHKEYMAX
#define OLEUI_CCHKEYMAX 		(256)
#endif

#ifndef OLEUI_CCHKEYMAX_SIZE
#define OLEUI_CCHKEYMAX_SIZE	(OLEUI_CCHKEYMAX*sizeof(TCHAR))
#endif

BOOL CCustomListBox::AddControlsToList()
{
	ASSERT( this != NULL );

    DWORD       dw;
    UINT        cStrings=0;
	int			cch;
    HKEY        hKey;
    LONG        lRet;
    LPTSTR      pszClass;
    LPTSTR      pszClsid;
	LPTSTR		pszKey;
	HKEY		hKeyTemp;
	TCHAR		szID[50];

    pszClass=(LPTSTR)OleStdMalloc(OLEUI_CCHKEYMAX_SIZE*3);
    if (NULL==pszClass)
	{
        return FALSE;
	}

    pszClsid=pszClass+OLEUI_CCHKEYMAX;
	pszKey=pszClsid+OLEUI_CCHKEYMAX;

    //Open up the root key.
    lRet=RegOpenKey(HKEY_CLASSES_ROOT, NULL, &hKey);

    if ((LONG)ERROR_SUCCESS!=lRet)
    {
        OleStdFree((LPVOID)pszClsid);
        return FALSE;
    }

    //Clean out the existing strings.
	ResetContent();

    while (TRUE)
    {
        lRet=RegEnumKey(hKey, cStrings++, pszClass, OLEUI_CCHKEYMAX_SIZE);

        if ((LONG)ERROR_SUCCESS!=lRet)
		{
            break;
		}

        // Get full user type name
        dw=OLEUI_CCHKEYMAX_SIZE;
        lRet=RegQueryValue(hKey, pszClass, pszKey, (LONG*)&dw);

		// Get class ID
        lstrcat(pszClass, TEXT("\\CLSID"));
        dw=50 * sizeof(TCHAR);
        lRet = RegQueryValue(hKey, pszClass, szID, (LONG*)&dw);

        if ((LONG)ERROR_SUCCESS!=lRet)
		{
            continue;   // CLSID subkey not found
		}

        lstrcpy(pszClsid, TEXT("CLSID\\"));
        lstrcat(pszClsid, szID);
		lstrcat(pszClsid, TEXT("\\"));
		cch = lstrlen(pszClsid);
		lstrcpy(pszClsid+cch, TEXT("Control"));

		hKeyTemp = NULL;
        lRet=RegOpenKey(hKey, pszClsid, &hKeyTemp);
		if (hKeyTemp != NULL)
		{
			RegCloseKey(hKeyTemp);
		}

        if ((LONG)ERROR_SUCCESS!=lRet)
            continue;   // Control NOT found--skip this class

		// Look for InprocServer[32] or LocalServer[32] key
		lstrcpy(pszClsid+cch, INPROCSERVER);

		hKeyTemp = NULL;
        lRet=RegOpenKey(hKey, pszClsid, &hKeyTemp);
		if (hKeyTemp != NULL)
		{
			RegCloseKey(hKeyTemp);
		}

        if ((LONG)ERROR_SUCCESS!=lRet)	// InprocServer[32] not found
		{
			lstrcpy(pszClsid+cch, LOCALSERVER);

			hKeyTemp = NULL;
    	    lRet=RegOpenKey(hKey, pszClsid, &hKeyTemp);
			if (hKeyTemp != NULL)
			{
				RegCloseKey(hKeyTemp);
			}

	        if ((LONG)ERROR_SUCCESS!=lRet)	// LocalServer[32] not found
			{
				continue;
			}
		}

        //We got through all the conditions, add the string.
        lstrcat(pszKey, TEXT("\t"));

        // only add to listbox if not a duplicate
        if (LB_ERR==FindString(-1, pszKey)) 
        {
            lstrcat(pszKey, szID);
            AddString(pszKey);
        }
    }

    //Select the first item by default
    SetCurSel(0);
    RegCloseKey(hKey);
    OleStdFree((LPVOID)pszClass);
	return TRUE;
}

IMPLEMENT_DYNAMIC(CInsertDialog,COleInsertDialog);

/////////////////////////////////////////////////////////////////////////////
// CInsertDialog dialog


CInsertDialog::CInsertDialog(CWnd* pParent /*=NULL*/)
    : COleInsertDialog(IOF_SELECTCREATENEW | IOF_DISABLELINK | 
        IOF_DISABLEDISPLAYASICON, pParent)
{
    //{{AFX_DATA_INIT(CInsertDialog)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

int CInsertDialog::DoModal()
{
  	ASSERT( this != NULL );
	
	m_io.hInstance = AfxGetResourceHandle();
    m_io.lpszTemplate = _T("CUSTOMINSERTOBJECTDIALOG");
    return (COleInsertDialog::DoModal());
}

void CInsertDialog::DoDataExchange(CDataExchange* pDX)
{
    COleInsertDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CInsertDialog)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInsertDialog, COleInsertDialog)
    //{{AFX_MSG_MAP(CInsertDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CInsertDialog::OnInitDialog()
{
   	ASSERT( this != NULL );

	BOOL bOleDlgRet = COleInsertDialog::OnInitDialog();
    m_custlboxOleClasses.SubclassDlgItem(IDC_OLEINSERT_CLASSLIST, this);
    m_custlboxOleClasses.AddControlsToList();
    (GetDlgItem(IDC_OLEINSERT_CLASSLIST))->SetFocus();
    return (FALSE);
}

