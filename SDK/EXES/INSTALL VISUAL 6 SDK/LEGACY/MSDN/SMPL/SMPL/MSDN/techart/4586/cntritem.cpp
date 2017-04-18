/*****************************************************************************
  File: cntritem.cpp

  Purpose: Implementation of the CXlAutoCntrItem class

  Functions: CXlAutoCntrItem::CXlAutoCntrItem
			 BOOL CXlAutoCntrItem::OnChangeItemPosition
			 void CXlAutoCntrItem::OnGetItemPosition
			 void CXlAutoCntrItem::Serialize
			 LPDISPATCH CXlAutoCntrItem::GetIDispatch
			 void CXlAutoCntrItem::GetRange
			 void CXlAutoCntrItem::SetRowHeadings
			 void CXlAutoCntrItem::SetColHeadings
			 void CXlAutoCntrItem::SetData
			 void CXlAutoCntrItem::SetYTDTotals

  Development Team: Steve Roeder

  Written by Microsoft Product Support Services, Languages Developer Support
  Copyright (c) 1995 Microsoft Corporation. All rights reserved.
\****************************************************************************/

// cntritem.cpp : implementation of the CXlAutoCntrItem class
//

#include "stdafx.h"
#include "XlAuto.h"

#include "XlAutdoc.h"
#include "cntritem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXlAutoCntrItem implementation

IMPLEMENT_SERIAL(CXlAutoCntrItem, COleClientItem, 0)

// CXlAutoCntrItem::CXlAutoCntrItem
// Sets the m_rect member variable, which determines the container size
CXlAutoCntrItem::CXlAutoCntrItem(CXlAutoDoc* pContainer)
	: COleClientItem(pContainer)
{
	m_rect.SetRect(50, 30, 250, 230);	
}

CXlAutoCntrItem::~CXlAutoCntrItem()
{
	// TODO: add cleanup code here
	
}

void CXlAutoCntrItem::OnChange(OLE_NOTIFICATION nCode, DWORD dwParam)
{
	ASSERT_VALID(this);

	COleClientItem::OnChange(nCode, dwParam);

	// When an item is being edited (either in-place or fully open)
	//  it sends OnChange notifications for changes in the state of the
	//  item or visual appearance of its content.

	// TODO: invalidate the item by calling UpdateAllViews
	//  (with hints appropriate to your application)

	GetDocument()->UpdateAllViews(NULL);
		// for now just update ALL views/no hints
}

/************************************************************************
  Function:	CXlAutoCntrItem::OnChangeItemPosition

  Purpose: Called when the position of the in-place window

  Parameters: rectPos - updates CXlAutoCntrItem::m_rect

  Returns: TRUE

  Comments:	This is a modification of a standard AppWizard generated
           implementation of an OnChangeItemPosition with the 
           modifications described in Chapter 3 of the OLE 2 Tutorial in
           the OLE 2 Classes manual.

  History:

  Date     Comment                                           Initials
  ======== ================================================= ========
  04/15/95 Created                                             SJR
\***********************************************************************/
BOOL CXlAutoCntrItem::OnChangeItemPosition(const CRect& rectPos)
{
	ASSERT_VALID(this);

	// During in-place activation CXlAutoCntrItem::OnChangeItemPosition
	//  is called by the server to change the position of the in-place
	//  window.  Usually, this is a result of the data in the server
	//  document changing such that the extent has changed or as a result
	//  of in-place resizing.
	//
	// The default here is to call the base class, which will call
	//  COleClientItem::SetItemRects to move the item
	//  to the new position.

	if (!COleClientItem::OnChangeItemPosition(rectPos))
		return FALSE;

	GetDocument()->UpdateAllViews(NULL);
	m_rect = rectPos;

	// mark document as dirty
	GetDocument()->SetModifiedFlag();

	return TRUE;
}

// CXlAutoCntrItem::OnGetItemPosition
// Modified as described in OLE 2 Tutorial 
void CXlAutoCntrItem::OnGetItemPosition(CRect& rPosition)
{
	ASSERT_VALID(this);

	// During in-place activation, CXlAutoCntrItem::OnGetItemPosition
	//  will be called to determine the location of this item.  The default
	//  implementation created from AppWizard simply returns a hard-coded
	//  rectangle.  Usually, this rectangle would reflect the current
	//  position of the item relative to the view used for activation.
	//  You can obtain the view by calling CXlAutoCntrItem::GetActiveView.

	// return rect relative to client area of view
	rPosition = m_rect;
}

void CXlAutoCntrItem::OnDeactivateUI(BOOL bUndoable)
{
	COleClientItem::OnDeactivateUI(bUndoable);

	// Close an in-place active item whenever it removes the user
	//  interface.  The action here should match as closely as possible
	//  to the handling of the escape key in the view.

	Deactivate();   // nothing fancy here -- just deactivate the object
}

// CXlAutoCntrItem::Serialize
// Modified as described in OLE 2 Tutorial
void CXlAutoCntrItem::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	// Call base class first to read in COleClientItem data.
	// Since this sets up the m_pDocument pointer returned from
	//  CXlAutoCntrItem::GetDocument, it is a good idea to call
	//  the base class Serialize first.
	COleClientItem::Serialize(ar);

	// now store/retrieve data specific to CXlAutoCntrItem
	if (ar.IsStoring())
	{
		ar << m_rect;
	}
	else
	{
		ar >> m_rect;
	}
}

/************************************************************************
  Function:	CXlAutoCntrItem::GetIDispatch

  Purpose: Retrieve the IDispatch interface for CXlAutoCntrItem

  Parameters: none

  Returns: LPDISPATCH

  Comments: Code taken from Technical Note 39: MFC/OLE Automation
            Implementation

  History:

  Date     Comment                                           Initials
  ======== ================================================= ========
  04/15/95 Created                                             SJR
\***********************************************************************/
LPDISPATCH CXlAutoCntrItem::GetIDispatch()
{
    ASSERT_VALID(this);
    ASSERT(m_lpObject != NULL);

    LPUNKNOWN lpUnk = m_lpObject;

    Run();    // must be running

    LPOLELINK lpOleLink = NULL;
    if (m_lpObject->QueryInterface(IID_IOleLink, 
        (LPVOID FAR*)&lpOleLink) == NOERROR)
    {
        ASSERT(lpOleLink != NULL);
        lpUnk = NULL;
        if (lpOleLink->GetBoundSource(&lpUnk) != NOERROR)
        {
            TRACE0("Warning: Link is not connected!\n");
            lpOleLink->Release();

            return NULL;
        }
        ASSERT(lpUnk != NULL);
    }

    LPDISPATCH lpDispatch = NULL;
    if (lpUnk->QueryInterface(IID_IDispatch, (void **)&lpDispatch) 
        != NOERROR)
    {
        TRACE0("Warning: does not support IDispatch!\n");
        return NULL;
    }

    ASSERT(lpDispatch != NULL);
    return lpDispatch;
}

/************************************************************************
  Function: CXlAutoCntrItem::GetRange

  Purpose: Gets an Excel Range object given an Excel worksheet object and
           the start and end cells

  Parameters: pSheet - pointer to the Excel worksheet object
              pRange - pointer to where the Excel Range object will be 
			           returned
			  szCell1 - string containing the beginning cell of the range
			  szCell2 - string containing the ending cell of the range

  Returns: void

  Comments:

  History:

  Date     Comment                                           Initials
  ======== ================================================= ========
  04/15/95 Created                                             SJR
\***********************************************************************/
void CXlAutoCntrItem::GetRange(Worksheet* pSheet, Range* pRange, const char *szCell1, const char *szCell2)
{
VARIANT str1, str2;
VARIANT disp;

	VariantInit(&disp);

	V_VT(&str1)=VT_BSTR;
	V_VT(&str2)=VT_BSTR;
	V_VT(&disp) = VT_DISPATCH;

	V_BSTR(&str1) = SysAllocString(szCell1);
	V_BSTR(&str2) = SysAllocString(szCell2);

	TRY 
	{
		disp = pSheet->Range(str1, str2);
	}  
	CATCH(COleDispatchException, e)
	{  
		AfxMessageBox(e->m_strDescription, MB_OK);  
	}
	END_CATCH

	SysFreeString(V_BSTR(&str1));
	SysFreeString(V_BSTR(&str2));

	pRange->AttachDispatch(disp.pdispVal);
	pRange->Select();
}

/************************************************************************
  Function: CXlAutoCntrItem::SetRowHeadings

  Purpose: Set the row headings in the Excel worksheet

  Parameters: pRange - pointer to the range object where the information
			           will be placed
			  szRows - array of strings to be placed in worksheet
              nRows - number of elements in the szRows array

  Returns: void

  Comments:

  History:

  Date     Comment                                           Initials
  ======== ================================================= ========
  04/13/95 Created                                             SJR
\***********************************************************************/
void CXlAutoCntrItem::SetRowHeadings(Range* pRange, char** szRows, int nRows)
{
VARIANT va4;
long ix[2];
SAFEARRAY FAR *psa;
SAFEARRAYBOUND sa[2];

	sa[0].lLbound = 0;
	sa[0].cElements = nRows;
	sa[1].lLbound = 0;
	sa[1].cElements = 1;

	if ((psa = SafeArrayCreate(VT_BSTR, 2, sa)) == NULL)
		AfxMessageBox("The safe Array allocation failed\n");
     
	ix[1] = 0;
	BSTR str;
	for (int i = 0 ; i < nRows ; i++)
	{   
		ix[0] = i;
		str = SysAllocString(szRows[i]);
		SafeArrayPutElement(psa, ix, str);
		SysFreeString(str);
	}
    
	VariantInit(&va4);
	V_VT(&va4) = VT_ARRAY | VT_BSTR;
	V_ARRAY(&va4) = psa;
     
	TRY
	{
		pRange->SetFormula(va4);
	}
	CATCH(COleDispatchException,e)
	{
		AfxMessageBox(e->m_strDescription, MB_OK);
	}
	END_CATCH 

	SafeArrayDestroy(psa);
}

/************************************************************************
  Function: CXlAutoCntrItem::SetColHeadings

  Purpose: Set the column headings in the Excel worksheet

  Parameters: pRange - pointer to the range object where the information
			           will be placed
			  szCols - array of strings to be placed in worksheet
              nCols - number of elements in the szRows array

  Returns: void

  Comments:

  History:

  Date     Comment                                           Initials
  ======== ================================================= ========
  04/13/95 Created                                             SJR
\***********************************************************************/
void CXlAutoCntrItem::SetColHeadings(Range* pRange, char** szCols, int nCols)
{
VARIANT va4;
long ix[2];
SAFEARRAY FAR *psa;
SAFEARRAYBOUND sa[1];

	sa[0].lLbound = 0;
	sa[0].cElements = nCols;

	if ((psa = SafeArrayCreate(VT_BSTR, 1, sa)) == NULL)
		AfxMessageBox("The safe Array allocation failed\n");
     
	BSTR str;
	for (int i = 0; i < nCols; i++)
	{   
		ix[0] = i;
		str = SysAllocString(szCols[i]);
		SafeArrayPutElement(psa, ix, str);
		SysFreeString(str);
	}
    
	VariantInit(&va4);
	V_VT(&va4) = VT_ARRAY | VT_BSTR;
	V_ARRAY(&va4) = psa;
     
	TRY
	{
		pRange->SetFormula(va4);
	}
	CATCH(COleDispatchException,e)
	{
		AfxMessageBox(e->m_strDescription, MB_OK);
	}
	END_CATCH 

	SafeArrayDestroy(psa);
}

/************************************************************************
  Function: CXlAutoCntrItem::SetData

  Purpose: Add some random data to the Excel worksheet

  Parameters: pRange - pointer to the range object where the information
			           will be placed
              lDataArray - two dimensional array of data
			  nRow - number of rows in lDataArray
			  nCol - number of cols in lDataArray

  Returns: void

  Comments:

  History:

  Date     Comment                                           Initials
  ======== ================================================= ========
  04/13/95 Created                                             SJR
\***********************************************************************/
void CXlAutoCntrItem::SetData(Range* pRange, long lDataArray[], int nRow, int nCol)
{
VARIANT va4;
long ix[2];
SAFEARRAY FAR *psa;
SAFEARRAYBOUND sa[2];

	sa[0].lLbound = 0;
	sa[0].cElements = nRow;
	sa[1].lLbound = 0;
	sa[1].cElements = nCol;

	if ((psa = SafeArrayCreate(VT_I2, 2, sa)) == NULL)
		AfxMessageBox("The safe Array allocation failed\n");

	for (int i = 0; i < nCol; i++)
		for (int j = 0; j < nRow; j++)
		{
			ix[1] = i;
			ix[0] = j; 
			SafeArrayPutElement(psa, ix, &(lDataArray[j * nCol + i]));
		}

	VariantInit(&va4);
	V_VT(&va4) = VT_ARRAY | VT_I2;
	V_ARRAY(&va4) = psa;
     
	TRY
	{
		pRange->SetFormula(va4);
	}
	CATCH(COleDispatchException,e)
	{
		AfxMessageBox(e->m_strDescription, MB_OK);
	}
	END_CATCH 

	SafeArrayDestroy(psa);
}

/************************************************************************
  Function: CXlAutoCntrItem::SetYTDTotals

  Purpose: Calculate totals for each column in the Excel worksheet

  Parameters: pSheet - pointer to the Excel worksheet object

  Returns:

  Comments:

  History:

  Date     Comment                                           Initials
  ======== ================================================= ========
  04/13/95 Created                                             SJR
\***********************************************************************/
void CXlAutoCntrItem::SetYTDTotals(Worksheet* pSheet)
{
	Range range;
	GetRange(pSheet, &range, "B9", "E9");

VARIANT va4;
long ix[1];
SAFEARRAY FAR *psa;
SAFEARRAYBOUND sa[1];

	sa[0].lLbound = 0;
	sa[0].cElements = 4;

	if ((psa = SafeArrayCreate(VT_BSTR, 1, sa)) == NULL)
		AfxMessageBox("The safe Array allocation failed\n");
     
	BSTR str;
	for (int i = 0 ; i < 4 ; i++)
	{
		ix[0] = i;
		str = SysAllocString("=SUM(B3:B7)");
		SafeArrayPutElement(psa, ix, str);
		SysFreeString(str);
	}

	VariantInit(&va4);
	V_VT(&va4) = VT_ARRAY | VT_BSTR;
	V_ARRAY(&va4) = psa;
     
	TRY
	{
		range.SetFormula(va4);
	}
	CATCH(COleDispatchException,e)
	{
		AfxMessageBox(e->m_strDescription, MB_OK);
	}
	END_CATCH 

	SafeArrayDestroy(psa);
}

/////////////////////////////////////////////////////////////////////////////
// CXlAutoCntrItem diagnostics

#ifdef _DEBUG
void CXlAutoCntrItem::AssertValid() const
{
	COleClientItem::AssertValid();
}

void CXlAutoCntrItem::Dump(CDumpContext& dc) const
{
	COleClientItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
