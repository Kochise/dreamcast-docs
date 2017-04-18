/*************************************************************************
**
**  Automation Client for Excel
**
**  Copyright (C) 1992-1995 Microsoft Corporation. All rights reserved.
**
**  xlclient.cpp
**
**  Written by Microsoft Product Support Services, Windows Developer Support
**
*************************************************************************/

#include <windows.h>
#include <windowsx.h>
#ifdef WIN16   
  #include <ole2.h>
  #include <compobj.h>    
  #include <dispatch.h> 
  #include <variant.h>
  #include <olenls.h>
  #include <commdlg.h>  
#endif  
#include "resource.h"
#include "xlclient.h" 
#include "invhelp.h"         


int APIENTRY WinMain (HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef WIN16
   //  It is recommended that all 16 bit OLE applications set
   //  their message queue size to 96. This improves the capacity
   //  and performance of OLE's LRPC mechanism.
   int cMsg = 96;                  // Recommend msg queue size for OLE
   while (cMsg && !SetMessageQueue(cMsg))  // take largest size we can get.
       cMsg -= 8;
   if (!cMsg)
       return -1;       
#endif
   
   OleInitialize(NULL);
   DialogBox(hinst, MAKEINTRESOURCE(IDD_MAINDIALOG), NULL, (DLGPROC)MainDialogFunc); 
   OleUninitialize();
   
   return 0;
}


BOOL CALLBACK MainDialogFunc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{  
   switch (msg)
   {                        
      case WM_COMMAND:
         switch(GET_WM_COMMAND_ID(wParam,lParam))
         {   
             case IDC_EXIT:
             case IDCANCEL:                   
                 EndDialog(hwndDlg, IDOK);
                 return TRUE;
                 
             case IDC_CONTROL_EXCEL:   
                 ControlExcel();
                 return TRUE;                                                                                                                 
         }
         break;
   }
   return FALSE;
}  

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

/*
 * ControlExcel uses the helper functions CreateObject and Invoke in invhelp.cpp
 * to control Excel. nvoke uses late-binding. It is possible
 * to make Invoke more efficient by using id-binding, where the DISPID of the
 * property is obtained from Excel's type library, rather than by using
 * using IDispatch::GetIDsOfNames. invhelp.cpp and invhelp.h were obtained
 * from the BROWSE sample in the Win32 SDK.
 *
 */
void ControlExcel()
{   
	// The Excel Automation documentation is shipped with Excel in vba_xl.hlp.

	VARIANT v, vRet;
    LPDISPATCH pdispApplication = NULL; 
	LPDISPATCH pdispWorkbooks = NULL; 
	LPDISPATCH pdispWorkbook = NULL; 
	LPDISPATCH pdispWorksheet = NULL;
	LPDISPATCH pdispRange = NULL; 
	LPDISPATCH pdispCharts = NULL; 
	LPDISPATCH pdispChart = NULL; 
    HRESULT hr;  

    // Set application = CreateObject("Excel.Application")
    hr = CreateObject(OLESTR("Excel.Application"), &pdispApplication);   
    if (FAILED(hr))  
    {
        MessageBox(NULL, TEXT("Failed to create Excel"), TEXT("Error"), MB_ICONEXCLAMATION|MB_OK);
        return; //Fail
    }

    // Note that all parameters and return types
	// of Excel automation methods and types are of type VARIANT. V_VT, V_BOOL
	// etc. are helper macros defined in oleauto.h (varian.h in 16 bit) that allow 
	// easy initialization of and retrieval of values from a VARIANT. The actual 
	// types that need to be filled into and retrieved from a VARIANT 
	// are not explicilty stated in vba_xl.hlp. However the tyes can be 
	// easily guessed. For example an integer can be passed as VT_I2 or VT_I4, 
	// a string as VT_BSTR and an object as VT_DISPATCH.

	// application.Visible = True.
    V_VT(&v) = VT_BOOL;
    V_BOOL(&v) = TRUE;
    hr = Invoke(pdispApplication, DISPATCH_PROPERTYPUT, NULL, NULL, NULL,
		         OLESTR("Visible"), TEXT("v"), v);
	if (FAILED(hr))
		goto error;

    // The helper function Invoke doesn't support named arguments, so all arguments
	// are passed by position. Note that the IDispatch of the Workbooks object
	// must obtained before its Add method can be called.

    // Set workbook = application.Workbooks.Add(template:=xlWorkSheet)
	hr = Invoke(pdispApplication, DISPATCH_METHOD, &vRet, NULL, NULL,
		         OLESTR("WorkBooks"), NULL);
	if (FAILED(hr))
		goto error;
    pdispWorkbooks = V_DISPATCH(&vRet);
    V_VT(&v) = VT_I2;
    V_I2(&v) = xlWorkSheet;
	hr = Invoke (pdispWorkbooks, DISPATCH_METHOD, &vRet, NULL, NULL,
		         OLESTR("Add"), TEXT("v"), v);
    if (FAILED(hr))
		goto error;
    pdispWorkbook = V_DISPATCH(&vRet);

    // Set worksheet = workbook.Worksheets(1)
    V_VT(&v) = VT_I2;
    V_I2(&v) = 1;
	hr = Invoke(pdispWorkbook, DISPATCH_METHOD, &vRet, NULL, NULL,
		         OLESTR("Worksheets"), TEXT("v"), v);
    if (FAILED(hr))
		goto error;
    pdispWorksheet = V_DISPATCH(&vRet); 
	
	// worksheet.Range("A1:D1").Value = Array("North", "South", "East", "West")
    V_VT(&v) = VT_BSTR;
    V_BSTR(&v) = SysAllocString(OLESTR("A1:D1"));
	hr = Invoke(pdispWorksheet, DISPATCH_METHOD, &vRet, NULL, NULL,
		         OLESTR("Range"), TEXT("v"), v);
    VariantClear(&v);
    if (FAILED(hr))
		goto error;
    pdispRange = V_DISPATCH(&vRet);
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
	hr = Invoke(pdispRange, DISPATCH_PROPERTYPUT, NULL, NULL, NULL,
		         OLESTR("Value"), TEXT("v"), v);
	// The caller is responsible for freeing parameters and return values.
	// VariantClear will appropriately free the contents of the VARIANT.
    VariantClear(&v);
	if (FAILED(hr))
		goto error;

	// worksheet.Range("A2").Value = 5.2
    V_VT(&v) = VT_BSTR;
    V_BSTR(&v) = SysAllocString(OLESTR("A2"));
	hr = Invoke(pdispWorksheet, DISPATCH_METHOD, &vRet, NULL, NULL,
		         OLESTR("Range"), TEXT("v"), v);
    VariantClear(&v); 
    if (FAILED(hr))
		goto error;
	pdispRange->Release();  // Release the previous range object
    pdispRange = V_DISPATCH(&vRet);
    V_VT(&v) = VT_R8;
    V_R8(&v) = 5.2;
    hr = Invoke(pdispRange, DISPATCH_PROPERTYPUT, NULL, NULL, NULL,
		         OLESTR("Value"), TEXT("v"), v);
	if (FAILED(hr))
		goto error;

    // worksheet.Range("B2").Value = 10
    V_VT(&v) = VT_BSTR;
    V_BSTR(&v) = SysAllocString(OLESTR("B2"));
    hr = Invoke(pdispWorksheet, DISPATCH_METHOD, &vRet, NULL, NULL,
		         OLESTR("Range"), TEXT("v"), v);
    VariantClear(&v); 
    if (FAILED(hr))
		goto error;
	pdispRange->Release(); // Release the previous range object
    pdispRange = V_DISPATCH(&vRet);
    V_VT(&v) = VT_I2;
    V_I2(&v) = 10;
    hr = Invoke(pdispRange, DISPATCH_PROPERTYPUT, NULL, NULL, NULL,
		         OLESTR("Value"), TEXT("v"), v);
    if (FAILED(hr))
		goto error;

    // worksheet.Range("C2").Value = 8
    V_VT(&v) = VT_BSTR;
    V_BSTR(&v) = SysAllocString(OLESTR("C2"));
    hr = Invoke(pdispWorksheet, DISPATCH_METHOD, &vRet, NULL, NULL,
		         OLESTR("Range"), TEXT("v"), v);
    VariantClear(&v); 
    if (FAILED(hr))
		goto error;
	pdispRange->Release(); // Release the previous range object
    pdispRange = V_DISPATCH(&vRet);
    V_VT(&v) = VT_I2;
    V_I2(&v) = 8;
    hr = Invoke(pdispRange, DISPATCH_PROPERTYPUT, NULL, NULL, NULL,
		         OLESTR("Value"), TEXT("v"), v);
	if (FAILED(hr))
		goto error;

	// worksheet.Range("D2").Value = 20
	V_VT(&v) = VT_BSTR;
    V_BSTR(&v) = SysAllocString(OLESTR("D2"));
    hr = Invoke(pdispWorksheet, DISPATCH_METHOD, &vRet, NULL, NULL,
		         OLESTR("Range"), TEXT("v"), v);
    VariantClear(&v); 
    if (FAILED(hr))
		goto error;
	pdispRange->Release(); // Release the previous range object
    pdispRange = V_DISPATCH(&vRet);
    V_VT(&v) = VT_I2;
    V_I2(&v) = 20;
    hr = Invoke(pdispRange, DISPATCH_PROPERTYPUT, NULL, NULL, NULL,
		         OLESTR("Value"), TEXT("v"), v);
	if (FAILED(hr))
		goto error;

    // Set range = worksheet.Range("A1:D2")
	V_VT(&v) = VT_BSTR;
    V_BSTR(&v) = SysAllocString(OLESTR("A1:D2"));
    hr = Invoke(pdispWorksheet, DISPATCH_METHOD, &vRet, NULL, NULL,
		         OLESTR("Range"), TEXT("v"), v);
    VariantClear(&v);
    if (FAILED(hr))
		goto error;
	pdispRange->Release(); // Release the previous range object
    pdispRange = V_DISPATCH(&vRet);

    // Set chart = workbook.Charts.Add
	hr = Invoke(pdispWorkbook, DISPATCH_METHOD, &vRet, NULL, NULL,
		         OLESTR("Charts"), NULL);
    if (FAILED(hr))
		goto error;
    pdispCharts = V_DISPATCH(&vRet);
	hr = Invoke(pdispCharts, DISPATCH_METHOD, &vRet, NULL, NULL,
		         OLESTR("Add"), NULL);
    if (FAILED(hr))
		goto error;
    pdispChart = V_DISPATCH(&vRet);

	//chart.ChartWizard Source:=range, gallery:=xl3DPie, 
    //     Format:=7, plotBy:=xlRows, categoryLabels:=1, 
    //     seriesLabels:=0, hasLegend:=2, Title:="Sales Percentages"

    VARIANT v2, v3, v4, v5, v6, v7, v8;
    V_VT(&v) = VT_DISPATCH;                 // Source
    V_DISPATCH(&v) = pdispRange;
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

	hr = Invoke(pdispChart, DISPATCH_METHOD, NULL, NULL, NULL,
		         OLESTR("ChartWizard"), TEXT("vvvvvvvv"), v, v2, v3, v4, v5, v6, v7, v8);
	// VARIANTs that contain numbers/booleans need not be cleared because
	// they do not take up resources. v8 contains a string and must be freed.
	// v contains an IDispatch* and must be freed. 
    VariantClear(&v8);
	if (FAILED(hr))
		goto error;

	// workbook.Saved = True
    V_VT(&v) = VT_BOOL;
    V_BOOL(&v) = TRUE;
	hr = Invoke(pdispWorkbook, DISPATCH_PROPERTYPUT, NULL, NULL, NULL,
		         OLESTR("Saved"), TEXT("v"), v);
	if (FAILED(hr))
		goto error;

	pdispApplication->Release();
	pdispWorkbooks->Release();
	pdispWorkbook->Release();
	pdispWorksheet->Release();
    pdispRange->Release();
	pdispCharts->Release();
	pdispChart->Release();
	return; // Success

error:     
    if (pdispApplication) pdispApplication->Release();  
    if (pdispWorkbooks) pdispWorkbooks->Release();  
    if (pdispWorkbook) pdispWorkbook->Release(); 
	if (pdispWorksheet) pdispWorksheet->Release();  
    if (pdispRange) pdispRange->Release();  
    if (pdispCharts) pdispCharts->Release();
	if (pdispChart) pdispChart->Release(); 
    MessageBox(NULL, TEXT("Failed to control Excel"), TEXT("Error"), MB_ICONEXCLAMATION|MB_OK);
    return; // Fail
}

// The following ANSI/Unicode convertors are not used in this sample.
// because the sample only uses string constants.
#ifdef WIN32

#ifndef UNICODE
char* ConvertToAnsi(OLECHAR FAR* szW)
{
  static char achA[STRCONVERT_MAXLEN]; 
  
  WideCharToMultiByte(CP_ACP, 0, szW, -1, achA, STRCONVERT_MAXLEN, NULL, NULL);  
  return achA; 
} 

OLECHAR* ConvertToUnicode(char FAR* szA)
{
  static OLECHAR achW[STRCONVERT_MAXLEN]; 

  MultiByteToWideChar(CP_ACP, 0, szA, -1, achW, STRCONVERT_MAXLEN);  
  return achW; 
}
#endif

#endif     
