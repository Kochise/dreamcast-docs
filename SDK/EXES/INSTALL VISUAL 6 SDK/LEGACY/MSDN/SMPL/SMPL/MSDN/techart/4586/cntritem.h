// cntritem.h : interface of the CXlAutoCntrItem class
//

#include "xlsheet.h"
#include "xlrange.h"

class CXlAutoDoc;
class CXlAutoView;

class CXlAutoCntrItem : public COleClientItem
{
	DECLARE_SERIAL(CXlAutoCntrItem)

// Constructors
public:
	CXlAutoCntrItem(CXlAutoDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CRect m_rect;

	LPDISPATCH GetIDispatch();
	void GetRange(Worksheet* pSheet, Range* pRange, const char *szCell1, const char *szCell2);
	void SetRowHeadings(Range* pRange, char** szRows, int nRows);
	void SetColHeadings(Range* pRange, char** szCols, int nCols);
	void SetData(Range* pRange, long lDataArray[], int nRow, int nCol);
	void SetYTDTotals(Worksheet* pSheet);
	
	CXlAutoDoc* GetDocument()
		{ return (CXlAutoDoc*)COleClientItem::GetDocument(); }
	CXlAutoView* GetActiveView()
		{ return (CXlAutoView*)COleClientItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXlAutoCntrItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CXlAutoCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

/////////////////////////////////////////////////////////////////////////////
