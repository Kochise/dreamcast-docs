// unregdlg.cpp : implementation file
//

#include "stdafx.h"
#include "CtlReg.h"
#include "unregdlg.h"
#include <stdlib.h>  
#include <string.h>

#ifndef _WIN32
#include <shellapi.h>
#define MAX_PATH _MAX_PATH
#endif

#ifdef _WIN32	
	static char szToolboxBitmap[] = "ToolboxBitmap32" ;
	static char szInprocServer[] = "InprocServer32" ;
	#define LOADLIBRARY_SUCCEEDED(x) (x != 0)
#else	
	static char szToolboxBitmap[] = "ToolboxBitmap" ;
	static char szInprocServer[] = "InprocServer" ;
	#define LOADLIBRARY_SUCCEEDED(x) (x > HINSTANCE_ERROR)
#endif	


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

const int G_ICON_HEIGHT = 20 ;
const int G_ICON_WIDTH = 20 ;

class CRegEntry
{
	public:
		CRegEntry() ; 
		virtual ~CRegEntry() ;

		char* m_pName ;
		char* m_pPath ;
		char* m_pClsid ; // For cleanup
		char* m_pProgID ; // For cleanup
		char* m_pTypeLib ; // For cleanup
		HBITMAP m_hBitmap ;
		BOOL m_bInsertable ;
		BOOL m_bExists ;
		//Bitmap ;		
};

CRegEntry::CRegEntry()
: m_pName(NULL), m_pPath(NULL), m_hBitmap(NULL), 
  m_bInsertable(FALSE), m_bExists(TRUE), m_pClsid(NULL),m_pProgID(NULL) 
{
}

CRegEntry::~CRegEntry()
{
	if (m_pName) delete m_pName ;
	if (m_pPath) delete m_pPath ;
	if (m_pClsid) delete m_pClsid ;
	if (m_pProgID) delete m_pProgID ;
	if (m_hBitmap) ::DeleteObject(m_hBitmap) ;
}

/////////////////////////////////////////////////////////////////////////////
// CUnregisterDlg dialog


CUnregisterDlg::CUnregisterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUnregisterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUnregisterDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

    // Load the font we want to use
    m_font.CreateStockObject(ANSI_FIXED_FONT);
    // Get the metrics of the font
    CDC dc;
    dc.CreateCompatibleDC(NULL);
    CFont* pfntOld = (CFont*) dc.SelectObject(&m_font);
    TEXTMETRIC tm;
    dc.GetTextMetrics(&tm);
    dc.SelectObject(pfntOld);
    m_iFontHeight = tm.tmHeight;
    m_iFontWidth = tm.tmMaxCharWidth;
}


void CUnregisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUnregisterDlg)
	DDX_Control(pDX, IDC_LIST1, m_theListBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUnregisterDlg, CDialog)
	//{{AFX_MSG_MAP(CUnregisterDlg)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_WM_COMPAREITEM()
	ON_BN_CLICKED(IDD_CLEANUP, OnCleanup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CUnregisterDlg helper functions

BOOL CUnregisterDlg::GetControlNames()
{	
	DWORD dwIndex = 0 ;
	HKEY hKeyClsid ;
	HKEY hKeyX ;
	HKEY hKeyControl ;
	HKEY hKeyInsertable; 
	LONG lSize ;
	LONG regResult = ERROR_SUCCESS;
	char szClsidName[MAX_PATH+1] ;
	char szBuffer[MAX_PATH*2] ;
	

	//HKEY_CLASSES_ROOT
	//	CLSID
	//		{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}	
	//			Control
	//			Insertable
	//			ToolbarBitmap		
	regResult = ::RegOpenKey(HKEY_CLASSES_ROOT, "CLSID", &hKeyClsid);
	if (regResult != ERROR_SUCCESS) return FALSE ;

	BeginWaitCursor() ;

	// Enum all entries under CLSID
	while(::RegEnumKey(hKeyClsid, dwIndex++, szClsidName, MAX_PATH+1) == ERROR_SUCCESS)
	{
		// Open the CLSID key
		regResult = ::RegOpenKey(hKeyClsid,szClsidName,&hKeyX) ;
		if (regResult != ERROR_SUCCESS) continue;

		// Is this a Control?
		regResult = ::RegOpenKey(hKeyX, "Control", &hKeyControl) ;	
		if (regResult == ERROR_SUCCESS)
		{
			// Yes, we have a control 

			// Look for path of Inproc Server 
			lSize = sizeof(szBuffer) ;
			regResult = ::RegQueryValue(hKeyX, szInprocServer, szBuffer, &lSize) ;
			if (regResult != ERROR_SUCCESS)
			{// Didn't find it. It might be 16bit instead of 32bit or vice versa
			    continue ; 
			}
			
			// Store pathname
			CRegEntry* pEntry = new CRegEntry ;		
			pEntry->m_pPath = new char[lSize] ;
			memcpy(pEntry->m_pPath, szBuffer, (int)lSize) ;
			
			// Check to see .OCX file actually exits
			OFSTRUCT OpenBuff ;
			if (::OpenFile(pEntry->m_pPath, &OpenBuff, OF_EXIST) == HFILE_ERROR)
			{
				pEntry->m_bExists = FALSE ;

				// Store CLSID for Cleanup
				pEntry->m_pClsid = new char[strlen(szClsidName)] ;
				strcpy(pEntry->m_pClsid,szClsidName) ;

				// Get ProdID and store it for later Cleanup
				lSize = sizeof(szBuffer); 
				regResult = ::RegQueryValue(hKeyX, "ProgID", szBuffer, &lSize) ;
				if (regResult == ERROR_SUCCESS)
				{
					pEntry->m_pProgID = new char[lSize] ;
					memcpy(pEntry->m_pProgID, szBuffer, (int)lSize) ;
				}
				
				// Get TypeLib ID and store it for later Cleanup
				lSize = sizeof(szBuffer); 
				regResult = ::RegQueryValue(hKeyX, "TypeLib", szBuffer, &lSize) ;
				if (regResult == ERROR_SUCCESS)
				{
					pEntry->m_pTypeLib = new char[lSize] ;
					memcpy(pEntry->m_pTypeLib, szBuffer, (int)lSize) ;
				}
			}			
						
			// Get control name and put it into array
			lSize = sizeof(szBuffer); 
			regResult = ::RegQueryValue(hKeyClsid, szClsidName, szBuffer, &lSize) ;
			if (regResult != ERROR_SUCCESS) 
			{   
				delete pEntry ;
				continue ;
			}
			pEntry->m_pName = new char[lSize] ; 
			memcpy(pEntry->m_pName, szBuffer, (int)lSize) ;				
			
			// Is it Insertable
			regResult = RegOpenKey(hKeyX,"Insertable",&hKeyInsertable) ;	
			pEntry->m_bInsertable = (regResult == ERROR_SUCCESS) ;
			if (pEntry->m_bInsertable) RegCloseKey(hKeyInsertable) ;
				

			// Put Bitmap in array		
			lSize = sizeof(szBuffer) ; 
			//char* szStr = strPathAndResNum.GetBufferSetLength((int)lSize) ;
			regResult = ::RegQueryValue(hKeyX, szToolboxBitmap, szBuffer, &lSize) ;
	   		
			if (regResult == ERROR_SUCCESS)
			{
				CString strPathAndResNum(szBuffer, (int)lSize) ;			
				// Let's pretend we're using Basic
				int indexComma = strPathAndResNum.Find(',') ; 
				// WHAT ABOUT ERRORS?
				CString strPath = strPathAndResNum.Left(indexComma) ;
				CString strResNum = strPathAndResNum.Mid(indexComma+1) ;
				WORD wResNum = atoi(strResNum) ;

				char* szPath = strPath.GetBuffer(strPath.GetLength()) ;               
				HINSTANCE hInstCtl  = ::LoadLibrary(szPath) ;
				if (LOADLIBRARY_SUCCEEDED(hInstCtl))
				{
					// The OCX file might not actually exist.
					pEntry->m_hBitmap = ::LoadBitmap(hInstCtl, MAKEINTRESOURCE(wResNum)) ;
					::FreeLibrary(hInstCtl) ;
				}   
				strPath.ReleaseBuffer(-1) ;				
			}	  
			// Add entry to list
			m_PtrArray.Add(pEntry); 			
			
			// Cleanup	
			::RegCloseKey(hKeyControl) ;
		}
		::RegCloseKey(hKeyX) ; 
	}
	::RegCloseKey(hKeyClsid); 

	EndWaitCursor() ;
	return TRUE ;
}
//
// Wipe out lpszSubKey and below
//
BOOL CUnregisterDlg::WipeOut(HKEY hKey, LPCTSTR lpszSubKey)
{
	HKEY hSubKey ;
	char szSubSubName[MAX_PATH+1] ;

	LONG regResult = ::RegOpenKey(hKey, lpszSubKey, &hSubKey);
	if (regResult != ERROR_SUCCESS) return FALSE ;
		
	//DWORD dwIndex = 0 ;
	while(::RegEnumKey(hSubKey, 0/*dwIndex++*/, szSubSubName, sizeof(szSubSubName)) == ERROR_SUCCESS)
	{
		WipeOut(hSubKey, szSubSubName) ;
	}		

	::RegCloseKey(hSubKey) ;
	regResult = ::RegDeleteKey(hKey, lpszSubKey) ;
	TRACE("WipeOut: %s, %d\r\n", lpszSubKey, regResult) ;

	return (regResult == ERROR_SUCCESS) ;
}

//
//
//
void CUnregisterDlg::OnCleanup() 
{
	HKEY hKeyClsid ;
	HKEY hKeyX ;
	HKEY hKeyTypeLib;
	char szClsidName[MAX_PATH+1] ;
	char szBuffer[MAX_PATH*2] ;
	LONG lSize ;
	CPtrList PathList ;
	int iNonExisting = 0 ;

	// Open the "CLSID" key
	LONG regResult = ::RegOpenKey(HKEY_CLASSES_ROOT, "CLSID", &hKeyClsid);
	if (regResult != ERROR_SUCCESS) return ;

	BeginWaitCursor() ;

    regResult = ::RegOpenKey(HKEY_CLASSES_ROOT,"TypeLib", &hKeyTypeLib) ;
	if (regResult != ERROR_SUCCESS) hKeyTypeLib = NULL ;
	
	CRegEntry* pEntry ;
	int i = 0;
	while (i < m_PtrArray.GetSize() )
	{
    	pEntry = (CRegEntry*)m_PtrArray.GetAt( i++ );
		if (!pEntry->m_bExists)
		{
			// .OCX file does not exist.
			// Remove ProgID
			if (pEntry->m_pProgID) WipeOut(HKEY_CLASSES_ROOT, pEntry->m_pProgID) ;
			// Remove TypeLib
			if (pEntry->m_pTypeLib && hKeyTypeLib) WipeOut(hKeyTypeLib, pEntry->m_pTypeLib) ;
							 	
			// Remove current entry
			WipeOut(hKeyClsid, pEntry->m_pClsid ) ;

			// Put the .OCX path into the path list
			PathList.AddTail(pEntry->m_pPath); 
			iNonExisting++ ;
		}
	}
	::RegCloseKey(hKeyTypeLib) ;

	//
	// Look for anything under \CLSID that has the same InprocServer 
	//
	if (iNonExisting)
	{
		// Enum all entries under CLSID
		DWORD dwIndex = 0 ;
		while(::RegEnumKey(hKeyClsid, dwIndex++, szClsidName, sizeof(szClsidName)) == ERROR_SUCCESS)
		{
			// Open the CLSID key
			regResult = ::RegOpenKey(hKeyClsid,szClsidName,&hKeyX) ;
			if (regResult != ERROR_SUCCESS) continue;

			// Get the InprocServer path ;
			lSize = sizeof(szBuffer) ;
			regResult = ::RegQueryValue(hKeyX, szInprocServer, szBuffer, &lSize) ;
			::RegCloseKey(hKeyX) ;
			if (regResult == ERROR_SUCCESS)
			{
				// Yes, we have an InprocServer
				char* pPath ;
				POSITION pos = PathList.GetHeadPosition() ;
				while (pos != NULL)
				{
	    			pPath = (char*)PathList.GetNext( pos );
					if (0 == strcmp(pPath, szBuffer)) 
					{
						WipeOut(hKeyClsid,szClsidName) ;				
						dwIndex-- ;
						break;
					}								
				}
			}
		}
	}
	::RegCloseKey(hKeyClsid) ;

	EndWaitCursor() ;

	CDialog::OnCancel(); //FIX THIS!!!!
	CleanUp() ;				
}

//
//
//
void CUnregisterDlg::CleanUp()
{
	CRegEntry* ptr ;
	int i = 0;
	while (i < m_PtrArray.GetSize() )
	{
		ptr = (CRegEntry*)m_PtrArray.GetAt(i++);
    	delete ptr;
	}
	m_PtrArray.RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////
// CUnregisterDlg message handlers

BOOL CUnregisterDlg::OnInitDialog() 
{
	CRegEntry* ptr ;
	CDialog::OnInitDialog();
	
	GetControlNames() ;

	m_theListBox.ResetContent() ;
	int i = 0;
	while (i < m_PtrArray.GetSize() )
	{
    	ptr = (CRegEntry*)m_PtrArray.GetAt( i++ );
		// Put the pointer in since its ownerdraw.
		int result = m_theListBox.AddString((char*)ptr ) ; //ptr->m_pName) ;		
	}										
					
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUnregisterDlg::OnCancel() 
{
	CleanUp() ;
		
	CDialog::OnCancel();
}

void CUnregisterDlg::OnOK() 
{
	int index = m_theListBox.GetCurSel() ;
	if (index != LB_ERR)
	{
		CRegEntry* ptr = (CRegEntry*)m_theListBox.GetItemData(index) ; //m_PtrArray.GetAt(index);
		m_strThePath = ptr->m_pPath ;	
		CDialog::OnOK();
		CleanUp() ;				
	}
}

void CUnregisterDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT pDI ) 
{
	ASSERT(nIDCtl == IDC_LIST1) ;

    CRegEntry* pEntry;
    HFONT hfntOld;
    CRect rcText;
    switch (pDI->itemAction) {
    case ODA_DRAWENTIRE:
        // Draw the whole line of information
        // Get a pointer to the object
        pEntry = (CRegEntry*) pDI->itemData;
        ASSERT(pEntry);
        // Set up the font we want to use
        hfntOld = (HFONT) ::SelectObject(pDI->hDC, m_font.m_hObject);
        rcText = pDI->rcItem;
        // Erase the entire area
        ::ExtTextOut(pDI->hDC, 
                     rcText.left, rcText.top,
                     ETO_OPAQUE,
                     &rcText,
                     "", 0,
                     NULL);
	
        // Draw the bitmap in place		
        if (pEntry->m_hBitmap)
		{		
 			BITMAP bm;
    		::GetObject(pEntry->m_hBitmap,sizeof(bm), &bm);
    		int iWidth = bm.bmWidth;
    		int iHeight = bm.bmHeight;

   			 // Create a memory DC
    		HDC hdcMem = ::CreateCompatibleDC(pDI->hDC);
    		// Select the bitmap into the mem DC
    		HBITMAP hbmold = (HBITMAP)::SelectObject(hdcMem, pEntry->m_hBitmap);
    		// Blt the bits
    		::BitBlt(	pDI->hDC,
             			rcText.left+5, rcText.top,
             			iWidth, iHeight,
             			hdcMem,
             			0, 0,
             			SRCCOPY);
    		::SelectObject(hdcMem, hbmold);
    		::DeleteDC(hdcMem); 
		}

        // Move the text over to just beyond the bitmap
        rcText.left = pDI->rcItem.left + G_ICON_WIDTH + 5 + 2;
        ::DrawText(pDI->hDC,
                   pEntry->m_pName,
                   -1,
                   &rcText,
                   DT_LEFT | DT_VCENTER);

		// Is control insertable

		rcText.left += m_iFontWidth*30 ; // Move over 30 characters
		if (pEntry->m_bInsertable)
		{
			::DrawText(	pDI->hDC,
				  		"Insert",
						-1,	
						&rcText,
                    	DT_LEFT | DT_VCENTER);
		}

		rcText.left += m_iFontWidth*8 ; // Move over 8 characters
		if (pEntry->m_bExists)
		{
			::DrawText(	pDI->hDC,
				  		"Exist",
						-1,	
						&rcText,
                    	DT_LEFT | DT_VCENTER);
		}

        // Check if we need to show selection state
        if (pDI->itemState & ODS_SELECTED) {
            ::InvertRect(pDI->hDC, &(pDI->rcItem));
        }
        // Check if we need to show focus state
        if (pDI->itemState & ODS_FOCUS) {
            ::DrawFocusRect(pDI->hDC, &(pDI->rcItem));
        }
        ::SelectObject(pDI->hDC, hfntOld);
        break;

    case ODA_FOCUS:
        // Toggle the focus state
        ::DrawFocusRect(pDI->hDC, &(pDI->rcItem));
        break;

    case ODA_SELECT:
        // Toggle the selection state
        ::InvertRect(pDI->hDC, &(pDI->rcItem));
        break;
    default:
        break;
    }	
}

void CUnregisterDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	
	ASSERT(nIDCtl == IDC_LIST1) ;
	// Return the height of the font or the bitmap, 
    // whichever is greater
    lpMeasureItemStruct->itemHeight = max(m_iFontHeight,G_ICON_HEIGHT);	
}

int CUnregisterDlg::OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT pCI) 
{
	ASSERT(	nIDCtl == IDC_LIST1) ;
	
	CRegEntry* pEntry1 = (CRegEntry*)pCI->itemData1 ;
	CRegEntry* pEntry2 = (CRegEntry*)pCI->itemData2 ;

	return strcmp(pEntry1->m_pName, pEntry2->m_pName) ;	
}


