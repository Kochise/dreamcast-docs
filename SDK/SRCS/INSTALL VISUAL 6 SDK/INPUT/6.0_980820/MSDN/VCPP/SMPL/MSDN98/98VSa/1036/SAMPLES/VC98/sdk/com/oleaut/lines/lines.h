#ifdef WIN32

#ifdef UNICODE
    #define FROM_OLE_STRING(str) str
    #define TO_OLE_STRING(str) str 
#else
    #define FROM_OLE_STRING(str) ConvertToAnsi(str)
    char* ConvertToAnsi(OLECHAR FAR* szW);  
    #define TO_OLE_STRING(str) ConvertToUnicode(str)
    OLECHAR* ConvertToUnicode(char FAR* szA);   
    // Maximum length of string that can be converted between Ansi & Unicode
    #define STRCONVERT_MAXLEN 300         
#endif

#else  // WIN16
  #define APIENTRY far pascal  
  #define TCHAR char
  #define TEXT(sz) sz 
  #define FROM_OLE_STRING(str) str  
  #define TO_OLE_STRING(str) str  
  #define LPTSTR LPSTR
  
  // Windows NT defines the following in windowsx.h
  #define GET_WM_COMMAND_ID(w,l) (w)
  #define GET_WM_COMMAND_CMD(w,l) HIWORD(l)
  #define GET_WM_COMMAND_HWND(w,l) LOWORD(l)
#endif

#include "tlb.h"
 
// Menu IDs
#define IDM_DRAWLINE  101
#define IDM_CLEAR     102
#define IDM_EXIT      103  

// Dialog ID
#define IDD_DRAWLINE  101
// Icon ID
#define IDI_ICON      102

// Dialog Control IDs
#define IDC_THICKNESS     101
#define IDC_CHOOSECOLOR   102
#define IDC_STARTPOINT_X  103
#define IDC_STARTPOINT_Y  104
#define IDC_ENDPOINT_X    105
#define IDC_ENDPOINT_Y    106 
#define IDC_STATIC         -1

// MAX len of string table entries
#define STR_LEN   200

// String table constants
#define IDS_Name                   1 
#define IDS_ErrorLoadingTypeLib    2
#define IDS_ProgID                 3 
#define IDS_Unexpected             1001
#define IDS_OutOfMemory            1002   
#define IDS_InvalidIndex           1003
#define IDS_CollectionFull         1004
#define IDS_LineFromOtherInstance  1005
#define IDS_CantAddEndPoints       1006  
#define IDS_PointFromOtherInstance 1007 
#define IDS_NoVisibleXCoordinate   1008
#define IDS_NoVisibleYCoordinate   1009  
#define IDS_NoStartPoint           1010
#define IDS_NoEndPoint             1011   

// SCODEs for the Lines Application. This is required for vtable-binding
// Automation objects want to return custom HRESULTs. All the OLE-defined 
// FACILITY_ITF codes have a code value which lies in the region 0x0000-0x01FFF.
// While it is legal for the definer to use any code, it is highly recommended
// that only code values in the range 0x0200-0xFFFF be used, as this will reduce the
// possiblity of accidental confusion with any OLE-defined errors.
#define LINES_E_FIRST MAKE_SCODE(SEVERITY_ERROR, FACILITY_ITF, 0x0200)  

#define LINES_E_UNEXPECTED              (LINES_E_FIRST + 0x0) 
// Unexpected error
#define LINES_E_OUTOFMEMORY             (LINES_E_FIRST + 0x1) 
// Out of memory
#define LINES_E_INVALIDINDEX            (LINES_E_FIRST + 0x2) 
// Invalid index to Points or Lines collections 
#define LINES_E_COLLECTIONFULL          (LINES_E_FIRST + 0x3) 
// Points or Lines collection is full
#define LINES_E_LINEFROMOTHERINSTANCE   (LINES_E_FIRST + 0x4)
// Line from another instance of this application cannot be added.
#define LINES_E_CANTADDENDPOINTS        (LINES_E_FIRST + 0x5)   
// End points of line cannot be added to collection. (Make sure line has two end points).
#define LINES_E_POINTFROMOTHERINSTANCE  (LINES_E_FIRST + 0x6)
// Point from another instance of this application cannot be added.
#define LINES_E_NOVISIBLEXCOORDINATE    (LINES_E_FIRST + 0x7)
// No visible X coordinate.
#define LINES_E_NOVISIBLEYCOORDINATE    (LINES_E_FIRST + 0x8)
// No visible Y coordinate.
#define LINES_E_NOSTARTPOINT            (LINES_E_FIRST + 0x9)
// Line does not have a start point.
#define LINES_E_NOENDPOINT              (LINES_E_FIRST + 0xA)
// Line does not have an end point.

// Number of SCODEs
#define SCODE_COUNT 11   

// Function prototypes
int APIENTRY WinMain (HINSTANCE, HINSTANCE, LPSTR, int);
BOOL InitApplication (HINSTANCE);
BOOL InitInstance (HINSTANCE);
BOOL ProcessCmdLine(LPSTR pCmdLine, LPDWORD pdwRegisterCF, LPDWORD pdwRegisterActiveObject, int nCmdShow);
void Uninitialize(DWORD dwRegisterCF, DWORD dwRegisterActiveObject);
HRESULT LoadTypeInfo(ITypeInfo FAR* FAR* pptinfo, REFCLSID clsid);
HRESULT RaiseException(int nID, REFGUID rguid);

#ifdef WIN16
extern "C" LRESULT __export CALLBACK MainWndProc (HWND, UINT, WPARAM, LPARAM); 
extern "C" BOOL __export CALLBACK DrawLineDialogFunc(HWND, UINT, WPARAM, LPARAM);                  
#else 
extern "C" LRESULT CALLBACK MainWndProc (HWND, UINT, WPARAM, LPARAM); 
extern "C" BOOL CALLBACK DrawLineDialogFunc(HWND, UINT, WPARAM, LPARAM); 
#endif   
 
// Class definitions
class CPane;  
class CLine;
class CPoint;
class CLines;
class CPoints;  

// ISupportErrorInfo interface implementation
interface CSupportErrorInfo : public ISupportErrorInfo 
{
public:
    // IUnknown methods 
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)(void);
    STDMETHOD_(ULONG, Release)(void); 
    
    // ISupportErrorInfo method
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);  
     
    CSupportErrorInfo(IUnknown FAR* punkObject, REFIID riid); 
private:
    LPUNKNOWN m_punkObject;  // IUnknown of Object that implements this interface 
    GUID m_iid;
};     

class FAR CApplicationCF : public IClassFactory
{
public:
    // IUnknown methods 
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)(void);
    STDMETHOD_(ULONG, Release)(void); 
    
    // IClassFactory methods
    STDMETHOD(CreateInstance)(IUnknown FAR* punkOuter, REFIID riid, 
                              void FAR* FAR* ppv);
    STDMETHOD(LockServer)(BOOL fLock);    
    
    CApplicationCF();
    
private:
    ULONG m_cRef;                   // Reference count
}; 

    
class FAR CApplication : public IApplication
{
public:
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();

    /* IDispatch methods */
    STDMETHOD(GetTypeInfoCount)(UINT FAR* pctinfo);
    STDMETHOD(GetTypeInfo)(       
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo);
    STDMETHOD(GetIDsOfNames)(       
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid);
    STDMETHOD(Invoke)(       
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr);

    /* IApplication automation exposed properties and methods */   
    STDMETHOD(get_Application)(IApplication FAR* FAR* ppApplication);
    STDMETHOD(get_FullName)(BSTR FAR* pbstr);
    STDMETHOD(get_Name)(BSTR FAR* pbstr);
    STDMETHOD(get_Parent)(IApplication FAR* FAR* ppApplication);
    STDMETHOD(put_Visible)(VARIANT_BOOL bVisible);
    STDMETHOD(get_Visible)(VARIANT_BOOL FAR* pbVisible);
    STDMETHOD(Quit)();
    STDMETHOD(get_Pane)(IPane FAR* FAR* ppPane);
    STDMETHOD(CreateLine)(ILine FAR* FAR* ppLine);
    STDMETHOD(CreatePoint)(IPoint FAR* FAR* ppPoint);
    
    /* CApplication methods */
    STDMETHOD_(void, Draw)();
    STDMETHOD_(void, OnSize)(unsigned int nWidth, unsigned int nHeight);
    STDMETHOD_(void, ShowWindow)(int nCmdShow); 
    STDMETHOD_(void, CreateAndDrawLine)();
    STDMETHOD_(void, ClearPane)();  
    
    static HRESULT Create(HINSTANCE hwnd, CApplication FAR* FAR* ppApplication); // Creates and intializes Applicaton object 
    CApplication();
    ~CApplication();    
    
public:
    HWND m_hwnd;                   // Application window.     
    HINSTANCE m_hinst;             // Hinstance of application. 
    BSTR m_bstrName;               // Name of application.
    BSTR m_bstrProgID;             // ProgID of application. 
    BOOL m_bUserClosing;           // User is closing the application.
    
private:
    LPTYPEINFO m_ptinfo;           // Type information of IApplication interface.
    BSTR m_bstrFullName;           // Full name of application.
    BOOL m_bVisible;               // Is window visible?
    CPane FAR* m_pPane;            // Pointer to the Pane object.   
    ULONG m_cRef;                  // Reference count.   
    CSupportErrorInfo m_SupportErrorInfo; // ISupportErrorInfo interface implementation 
};

class FAR CPane : public IPane
{
public:
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();

    /* IDispatch methods */
    STDMETHOD(GetTypeInfoCount)(UINT FAR* pctinfo);
    STDMETHOD(GetTypeInfo)(       
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo);
    STDMETHOD(GetIDsOfNames)(       
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid);
    STDMETHOD(Invoke)(       
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr);

    /* IPane automation exposed properties & methods */    
    STDMETHOD(get_Lines)(ILines FAR* FAR* ppLines);
    STDMETHOD(get_Points)(IPoints FAR* FAR* ppPoints);
    STDMETHOD(get_MaxX)(int FAR* pnMaxX);
    STDMETHOD(get_MaxY)(int FAR* pnMaxY);
    STDMETHOD(Clear)();
    STDMETHOD(Refresh)();
    
    /* CPane methods */
    STDMETHOD_(void, Draw)(); 
    STDMETHOD_(void, OnSize)(unsigned int nWidth, unsigned int nHeight);    
    STDMETHOD_(HDC,  GetDC)();  
    STDMETHOD_(void, ReleaseDC)(HDC hdc);   
    STDMETHOD_(void, InvalidateRect)(LPRECT prc);
    STDMETHOD_(void, Update)(void);
    STDMETHOD_(BOOL, AddPoint)(CPoint FAR* pPoint);
    STDMETHOD_(void, RemovePoint)(CPoint FAR* pPoint);
    
    static HRESULT Create(HWND hwnd, CPane FAR* FAR* ppPane); // Creates and intializes Pane object 
    CPane();
    ~CPane();
    
private:
    LPTYPEINFO m_ptinfo;           // Type information of IPane interface.
    HWND m_hwnd;                   // Main window.
    CLines FAR *m_pLines;          // Lines collection.
    CPoints FAR* m_pPoints;        // Points collection.
    int m_nMaxX;                   // Maximum visible X coordinate in twips.
    int m_nMaxY;                   // Maximum visible Y coordinate in twips.
    int m_nWidth;                  // Width of pane in twips.
    int m_nHeight;                 // Height of pane in twips.  
    ULONG m_cRef;                  // Reference count.   
    CSupportErrorInfo m_SupportErrorInfo; // ISupportErrorInfo interface implementation 
};

class FAR CLine : public ILine
{
public:
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();

    /* IDispatch methods */
    STDMETHOD(GetTypeInfoCount)(UINT FAR* pctinfo);
    STDMETHOD(GetTypeInfo)(       
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo);
    STDMETHOD(GetIDsOfNames)(       
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid);
    STDMETHOD(Invoke)(       
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr);

    /* ILine automation exposed properties & methods */   
    STDMETHOD(get_Color)(long FAR* plColorref);
    STDMETHOD(put_Color)(long lColorref);
    STDMETHOD(get_EndPoint)(IPoint FAR* FAR* ppPoint);
    STDMETHOD(putref_EndPoint)(IPoint FAR* pPoint);
    STDMETHOD(get_StartPoint)(IPoint FAR* FAR* ppPoint);
    STDMETHOD(putref_StartPoint)(IPoint FAR* pPoint);
    STDMETHOD(get_Thickness)(int FAR* pnThickness);
    STDMETHOD(put_Thickness)(int nThickness);
    
    /* CLine methods */
    STDMETHOD_(void, Draw)(HDC hdc);     
    STDMETHOD_(void, GetInvalidateRect)(LPRECT prc);
    STDMETHOD_(BOOL, AddEndPointsToPane)(CPane FAR* pPane);
    STDMETHOD_(void, RemoveEndPointsFromPane)(CPane FAR* pPane);  
    
    static HRESULT Create(CLine FAR* FAR* ppLine); // Creates and intializes Line object 
    CLine();
    ~CLine();
    
private:
    LPTYPEINFO m_ptinfo;           // Type information of ILine interface.
    COLORREF m_colorref;           // RGB color of line.
    CPoint FAR* m_pPointStart;     // Start point of line.
    CPoint FAR* m_pPointEnd;       // End point of line.
    int m_nThickness;              // Line thickness in twips. 
    ULONG m_cRef;                  // Reference count.
    CSupportErrorInfo m_SupportErrorInfo; // ISupportErrorInfo interface implementation 
};

class FAR CPoint : public IPoint
{
public:
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();

    /* IDispatch methods */
    STDMETHOD(GetTypeInfoCount)(UINT FAR* pctinfo);
    STDMETHOD(GetTypeInfo)(       
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo);
    STDMETHOD(GetIDsOfNames)(       
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid);
    STDMETHOD(Invoke)(       
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr);

    /* IPoint automation exposed properties & methods */    
    STDMETHOD(get_x)(int FAR* pnX);
    STDMETHOD(put_x)(int nX);
    STDMETHOD(get_y)(int FAR* pnY);
    STDMETHOD(put_y)(int nY);
    
    /* CPoint methods */
    STDMETHOD_(ULONG, InternalAddRef)();
    STDMETHOD_(ULONG, InternalRelease)();
    STDMETHOD_(int, get_x)();      
    STDMETHOD_(int, get_y)(); 
    
    static HRESULT Create(CPoint FAR* FAR* ppPoint); // Creates and intializes Point object 
    CPoint();
    ~CPoint();
    
private:
    LPTYPEINFO m_ptinfo;           // Type information of IPoint interface.
    int m_nX;                      // X coordinate of point in twips.
    int m_nY;                      // Y coordinate of point in twips.
    ULONG m_cInternalRef;          // Reference count for the use of the Points collection only.
    ULONG m_cRef;                  // Reference count.  
    CSupportErrorInfo m_SupportErrorInfo; // ISupportErrorInfo interface implementation 
};

class FAR CLines : public ILines
{
public:
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();

    /* IDispatch methods */
    STDMETHOD(GetTypeInfoCount)(UINT FAR* pctinfo);
    STDMETHOD(GetTypeInfo)(       
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo);
    STDMETHOD(GetIDsOfNames)(       
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid);
    STDMETHOD(Invoke)(       
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr);

    /* ILines automation exposed properties & methods */ 
    STDMETHOD(Add)(ILine FAR* pLine);
    STDMETHOD(get_Count)(long FAR* lCount);
    STDMETHOD(get_Item)(long lIndex, ILine FAR* FAR* ppLine);
    STDMETHOD(get__NewEnum)(IUnknown FAR* FAR* ppunkEnum);
    STDMETHOD(Remove)(long lIndex);
    
    /* CLines methods */
    STDMETHOD_(void, Draw)(HDC hdc);
    STDMETHOD_(void, Clear)();   
    
    static HRESULT Create(ULONG lMaxSize, long lLBound, CPane FAR* pPane, CLines FAR* FAR* ppLines); // Creates and intializes Lines object 
    CLines();
    ~CLines();
    
private:
    LPTYPEINFO m_ptinfo;           // Type information of ILines interface.
    SAFEARRAY FAR *m_psa;          // Safe array that holds Lines collection items.
    ULONG m_cElements;             // Number of items in Lines collection.
    ULONG m_cMax;                  // Maximum number of items Lines collection can hold.
    long m_lLBound;                // Lower bound of index of Lines collection.
    CPane FAR* m_pPane;            // Pointer to the Pane object that contains this Lines collection.  
    ULONG m_cRef;                  // Reference count.     
    CSupportErrorInfo m_SupportErrorInfo; // ISupportErrorInfo interface implementation 
};

class FAR CPoints : public IPoints
{
public:
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();

    /* IDispatch methods */
    STDMETHOD(GetTypeInfoCount)(UINT FAR* pctinfo);
    STDMETHOD(GetTypeInfo)(       
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo);
    STDMETHOD(GetIDsOfNames)(       
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid);
    STDMETHOD(Invoke)(       
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr);

    /* IPoints automation exposed properties & methods */    
    STDMETHOD(get_Count)(long FAR* plCount);
    STDMETHOD(get_Item)(long lIndex, IPoint FAR* FAR* ppPoint);
    STDMETHOD(get__NewEnum)(IUnknown FAR* FAR* ppunkEnum);
    
    /* CPoints methods */
    STDMETHOD_(BOOL, Add)(CPoint FAR* pPointNew);
    STDMETHOD_(BOOL, Remove)(CPoint FAR* pPointRemove);
    STDMETHOD_(void, Clear)();   
    STDMETHOD_(void, GetMaxXMaxY)(int FAR* pnX, int FAR* pnY, LPRECT prc);  
    
    static HRESULT Create(ULONG lMaxSize, long lLBound, CPane FAR* pPane, CPoints FAR* FAR* ppPoints); // Creates and intializes Points object 
    CPoints();
    ~CPoints();
    
private:
    LPTYPEINFO m_ptinfo;           // Type information of IPoints interface.
    SAFEARRAY FAR *m_psa;          // Safe array that holds Points collection items.
    ULONG m_cElements;             // Number of items in Points collection.
    ULONG m_cMax;                  // Maximum number of items Points collection can hold.
    long m_lLBound;                // Lower bound of index of Points collection.     
    CPane FAR* m_pPane;            // Pointer to the Pane object that contains this Points collection.  
    ULONG m_cRef;                  // Reference count.
    CSupportErrorInfo m_SupportErrorInfo; // ISupportErrorInfo interface implementation 
};

class FAR CEnumVariant : public IEnumVARIANT
{
public:
    // IUnknown methods 
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();

    // IEnumVARIANT methods 
    STDMETHOD(Next)(ULONG cElements, VARIANT FAR* pvar, ULONG FAR* pcElementFetched);
    STDMETHOD(Skip)(ULONG cElements);
    STDMETHOD(Reset)();
    STDMETHOD(Clone)(IEnumVARIANT FAR* FAR* ppenum);
    
    static HRESULT Create(SAFEARRAY FAR*, ULONG, CEnumVariant FAR* FAR*); // Creates and intializes Enumerator
    CEnumVariant();
    ~CEnumVariant();
    
private:
    ULONG m_cRef;           // Reference count                                 
    ULONG m_cElements;      // Number of elements in enumerator. 
    long m_lLBound;         // Lower bound of index.
    long m_lCurrent;        // Current index.
    SAFEARRAY FAR* m_psa;   // Safe array that holds elements.
}; 
 
// Structure filled by dialog from user input to create a line.
typedef struct _lineinfo
{
    COLORREF colorref;    // RGB color of line.
    POINT ptStart;        // Start point of line.   
    POINT ptEnd;          // End point of line.
    int nThickness;       // Thickness of line.
} LINEINFO, FAR* LPLINEINFO;
 
extern CApplication FAR* g_pApplication;
