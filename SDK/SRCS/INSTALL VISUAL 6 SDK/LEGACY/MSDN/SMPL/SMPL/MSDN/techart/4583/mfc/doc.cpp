// doc.cpp : implementation of the CXlclientDoc class
//

#include "stdafx.h"
#include "xlclient.h"

#include "doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXlclientDoc

IMPLEMENT_DYNCREATE(CXlclientDoc, CDocument)

BEGIN_MESSAGE_MAP(CXlclientDoc, CDocument)
	//{{AFX_MSG_MAP(CXlclientDoc)
	ON_COMMAND(ID_CONTROLEXCEL, OnControlExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CXlclientDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CXlclientDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IXlclie to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {0E570F71-3B2D-11CF-8506-00AA00C006CF}
static const IID IID_IXlclie =
{ 0xe570f71, 0x3b2d, 0x11cf, { 0x85, 0x6, 0x0, 0xaa, 0x0, 0xc0, 0x6, 0xcf } };

BEGIN_INTERFACE_MAP(CXlclientDoc, CDocument)
	INTERFACE_PART(CXlclientDoc, IID_IXlclie, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXlclientDoc construction/destruction

CXlclientDoc::CXlclientDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CXlclientDoc::~CXlclientDoc()
{
	AfxOleUnlockApp();
}

BOOL CXlclientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CXlclientDoc serialization

void CXlclientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CXlclientDoc diagnostics

#ifdef _DEBUG
void CXlclientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXlclientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXlclientDoc commands

#include "xl5en32.h"

// The values of Excel constants like xlWorkSheet, xl3DPie, xlRows etc. 
// can be obtained from the following knowledge base article:
// Excel AppNote: Built-in Constants in VB, Applications Edition
// Q112671
// The constant value can also be obtained from Excel’s type library 
// by using  a type library browser like ole2vw32.exe (in the 
// compiler’s \bin directory). Open Excel's type library (for 
// example, xl5en32.olb for the U.S version of Excel 95) using the 
// File/ViewTypeLibrary menu of ole2vw32.exe. Drop the typeinfos 
// combobox and select 'constants'. The Excel constants will be 
// displayed in the Variables/DataMembers list box. 
#define xlWorkSheet -4167
#define xl3DPie -4102
#define xlRows 1

void CXlclientDoc::OnControlExcel() 
{
	// The Excel Automation documentation is shipped with Excel in vba_xl.hlp.


	// The IDispatch* attached to the following COleDispatchDriver derived
	// classes will be released by the destructor when these variables go
	// out of scope
    Application application;
    Workbooks workbooks;
    Workbook workbook;
    Worksheet worksheet;
    Range range;
    Charts charts;
    Chart chart;

    VARIANT v, vRet, vNotPassed;
    VariantInit(&v);
    VariantInit(&vRet);
	// Optional parameters which are not passed 
	// can be passed a VARIANT containing VT_ERROR/DISP_E_PARAMNOTFOUND.
    V_VT(&vNotPassed) = VT_ERROR;
    V_ERROR(&vNotPassed) = DISP_E_PARAMNOTFOUND;

	// Set application = CreateObject("Excel.Application")
    if (FALSE == application.CreateDispatch("Excel.Application"))
    {
        AfxMessageBox(IDS_CANNOT_CREATE_EXCEL);
        return;      // fail
    }
	
	// Note that all parameters and return types
	// of Excel automation methods and types are of type VARIANT. V_VT, V_BOOL
	// etc. are helper macros defined in oleauto.h that allow easy initialization
	// of and retrieval of values from a VARIANT. The actual types that need to be 
	// filled into and retrieved from a VARIANT are not explicilty stated in 
	// vba_xl.hlp. However the tyes can be easily guessed. For example an integer 
	// can be passed as VT_I2 or VT_I4, a string as VT_BSTR and an object as 
	// VT_DISPATCH.

    // application.Visible = True.
    V_VT(&v) = VT_BOOL;
    V_BOOL(&v) = TRUE;
    application.SetVisible(v);

	// COleDispatchDriver doesn't support named arguments, so all arguments
	// are passed by position. Note that the IDispatch of the Workbooks object
	// must obtained before its Add method can be called.

	// The Workbooks method of the Application object can be called using two
	// different syntaxes, as described in the Excel Automation documentation in
	// vba_xl.hlp. Syntax 1 takes one parameter and Syntax 2 takes none. However
	// ClassWizard will generate only one proxy method for this method and others
	// like it. The solution is to modify the .h and .cpp file generated by 
	// ClassWizard and to add a second method that corresponds to the other syntax.
	// For example in this case a new Workbooks2 method that has the same DISPID as
	// Worbbooks but with no parameters is added. Note that this problem cannot be
	// resolved by passing VT_ERROR/DISP_E_PAMNOTFOUND. All methods marked as two
	// syntaxes must be handled in this manner.

    // Set workbook = application.Workbooks.Add(template:=xlWorkSheet)
    vRet = application.Workbooks2();
    ASSERT(V_VT(&vRet) == VT_DISPATCH);
    workbooks.AttachDispatch(V_DISPATCH(&vRet));
    V_VT(&v) = VT_I2;
    V_I2(&v) = xlWorkSheet;
    vRet = workbooks.Add(v);
    ASSERT(V_VT(&vRet) == VT_DISPATCH);
    workbook.AttachDispatch(V_DISPATCH(&vRet));

	// Set worksheet = workbook.Worksheets(1)
    V_VT(&v) = VT_I2;
    V_I2(&v) = 1;
    vRet = workbook.Worksheets(v);
    ASSERT(V_VT(&vRet) == VT_DISPATCH);
    worksheet.AttachDispatch(V_DISPATCH(&vRet));

	// worksheet.Range("A1:D1").Value = Array("North", "South", "East", "West")
    V_VT(&v) = VT_BSTR;
    V_BSTR(&v) = SysAllocString(OLESTR("A1:D1"));
	// Range is a method with two syntaxes. Add Range1 to xl5en32.h/.cpp as 
	// described above in the comments for Workbooks2.
    vRet = worksheet.Range1(v);
    VariantClear(&v);
    ASSERT(V_VT(&vRet) == VT_DISPATCH);
    range.AttachDispatch(V_DISPATCH(&vRet));
    // Create the array of values to be assigned to the range. 
    SAFEARRAY FAR* psa;
    SAFEARRAYBOUND sabound[1];
    long n;
    sabound[0].cElements = 4;
    sabound[0].lLbound = 0;
    psa = SafeArrayCreate(VT_BSTR, 1, sabound);
    n = 0;
    SafeArrayPutElement(psa, &n, SysAllocString(OLESTR("North")));
    n++;
    SafeArrayPutElement(psa, &n, SysAllocString(OLESTR("South")));
    n++;
    SafeArrayPutElement(psa, &n, SysAllocString(OLESTR("East")));
    n++;
    SafeArrayPutElement(psa, &n, SysAllocString(OLESTR("West")));
    V_VT(&v) = VT_ARRAY|VT_BSTR;
    V_ARRAY(&v) = psa;
    range.SetValue(v);
	// The caller is responsible for freeing parameters and return values.
	// VariantClear will appropriately free the contents of the VARIANT.
    VariantClear(&v);

	// worksheet.Range("A2").Value = 5.2
    V_VT(&v) = VT_BSTR;
    V_BSTR(&v) = SysAllocString(OLESTR("A2"));
    vRet = worksheet.Range1(v);
    VariantClear(&v); 
    ASSERT(V_VT(&vRet) == VT_DISPATCH);
    range.AttachDispatch(V_DISPATCH(&vRet));
    V_VT(&v) = VT_R8;
    V_R8(&v) = 5.2;
    range.SetValue(v);

	// worksheet.Range("B2").Value = 10
    V_VT(&v) = VT_BSTR;
    V_BSTR(&v) = SysAllocString(OLESTR("B2"));
    vRet = worksheet.Range1(v);
    VariantClear(&v);
    ASSERT(V_VT(&vRet) == VT_DISPATCH);
    range.AttachDispatch(V_DISPATCH(&vRet));
    V_VT(&v) = VT_I2;
    V_I2(&v) = 10;
    range.SetValue(v);

	// worksheet.Range("C2").Value = 8
    V_VT(&v) = VT_BSTR;
    V_BSTR(&v) = SysAllocString(OLESTR("C2"));
    vRet = worksheet.Range1(v);
    VariantClear(&v);
    ASSERT(V_VT(&vRet) == VT_DISPATCH);
    range.AttachDispatch(V_DISPATCH(&vRet));
    V_VT(&v) = VT_I2;
    V_I2(&v) = 8;
    range.SetValue(v);

	// worksheet.Range("D2").Value = 20
    V_VT(&v) = VT_BSTR;
    V_BSTR(&v) = SysAllocString(OLESTR("D2"));
    vRet = worksheet.Range1(v);
    VariantClear(&v);
    ASSERT(V_VT(&vRet) == VT_DISPATCH);
    range.AttachDispatch(V_DISPATCH(&vRet));
    V_VT(&v) = VT_I2;
    V_I2(&v) = 20;
    range.SetValue(v);

	// Set range = worksheet.Range("A1:D2")
    V_VT(&v) = VT_BSTR;
    V_BSTR(&v) = SysAllocString(OLESTR("A1:D2"));
    vRet = worksheet.Range1(v);
    VariantClear(&v);
    ASSERT(V_VT(&vRet) == VT_DISPATCH);
    range.AttachDispatch(V_DISPATCH(&vRet));
    
	// Charts is a method with two syntaxes. Add Chart2 to xl5en32.h/.cpp as 
	// described above in the comments for Workbooks2.

    // Set chart = workbook.Charts.Add
    vRet = workbook.Charts2();
    ASSERT(V_VT(&vRet) == VT_DISPATCH);
    charts.AttachDispatch(V_DISPATCH(&vRet));
    vRet = charts.Add(vNotPassed, vNotPassed, vNotPassed);
    ASSERT(V_VT(&vRet) == VT_DISPATCH);
    chart.AttachDispatch(V_DISPATCH(&vRet));

	//chart.ChartWizard Source:=range, gallery:=xl3DPie, 
    //     Format:=7, plotBy:=xlRows, categoryLabels:=1, 
    //     seriesLabels:=0, hasLegend:=2, Title:="Sales Percentages"

    VARIANT v2, v3, v4, v5, v6, v7, v8;
    V_VT(&v) = VT_DISPATCH;                 // Source
    V_DISPATCH(&v) = range.m_lpDispatch;
    V_VT(&v2) = VT_I2;                      // Gallery
    V_I2(&v2) = xl3DPie;
    V_VT(&v3) = VT_I2;                      // Format
    V_I2(&v3) = 7;
    V_VT(&v4) = VT_I2;                      // PlotBy
    V_I2(&v4) = xlRows;
    V_VT(&v5) = VT_I2;                      // CategoryLabels
    V_I2(&v5) = 1;
    V_VT(&v6) = VT_I2;                      // SeriesLabels
    V_I2(&v6) = 0;
    V_VT(&v7) = VT_I2;                      // hasLegend
    V_I2(&v7) = 2;
    V_VT(&v8) = VT_BSTR;                    // Title
    V_BSTR(&v8) = SysAllocString(OLESTR("Sales Percentages"));
    chart.ChartWizard(v, v2, v3, v4, v5, v6, v7, v8,
                vNotPassed, vNotPassed, vNotPassed);
	// VARIANTs that contain numbers/booleans need not be cleared because
	// they do not take up resources. v8 contains a string and must be freed.
	// v contains an IDispatch* and must be freed. However the range variable
	// to which this IDispatch* is attached will automatically free it when
	// it goes out of scope.
    VariantClear(&v8);
  
	// workbook.Saved = True
    V_VT(&v) = VT_BOOL;
    V_BOOL(&v) = TRUE;
    workbook.SetSaved(v);
    return;
}
