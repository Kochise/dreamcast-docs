// -----------------------------------------------------------------------------
// ExAdmin.H: Declaration of the classes necessary to create an Exchange 
//            Administration Extension DLL.
//              
// NOTE:      When we refer to "admin" we mean the Exchange Administration program.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _EXADMIN_H_
#define _EXADMIN_H_

// -----------------------------------------------------------------------------

#include <mapix.h>
#include "retcode.h"
#include "adminext.h"

// -----------------------------------------------------------------------------
// NOTE: Your resource file MUST define these two control ids with these exact 
//       numbers.  If you don't you will get a compile time error telling you 
//       that you are redefining a macro.  Just go into your resource.h file and
//       change those definitions to these values.
// -----------------------------------------------------------------------------

#define IDC_ADMINICON                   1000
#define IDC_TITLE                       1001

// -----------------------------------------------------------------------------
// The following macros and the SInitPropValue structure give the user the 
// ability to easily create a property value array.  This is intended to make
// it easier to use the CAdminDialog::HrSetExtProps() function.
//
// See usage example that follows.
// -----------------------------------------------------------------------------

#define MAKE_PROP_VALUE( cnt, ptr) ((LONGLONG) ((((LONGLONG) ((ULONG) (ptr))) << 32) + ((LONGLONG) ((ULONG) (cnt)))))
#define BINARY_PROP_VALUE( bin)  MAKE_PROP_VALUE( sizeof( bin), &bin)
#define MULTI_VALUE_PROP( array) MAKE_PROP_VALUE( ARRAY_CNT( array), array)

typedef struct
{
    ULONG    ulPropTag;
    ULONG    dwAlignPad;
    LONGLONG ll;    
} SInitPropValue, *LPSInitPropValue;

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Usage example:
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#ifdef  _USAGE_EXAMPLE_
#ifndef _USAGE_EXAMPLE_
    // Example of a binary structure that could be used by the property value array.
    typedef struct
    {
        CHAR    ch[20];
        LPSTR   lpsz;
        ULONG   ul;
        BOOL    flag;
    } ExampleStruct;

    // Example data that could go in the property value array.
    ExampleStruct BinData     = { "Binary Data", "A STRING", 3752789, TRUE};
    LONG          LongArray[] = { 92314535, 2231223, 111, 424242312};

    // The example property value array.
    static SInitPropValue ExtensionProps[] =
    {
        { PT_STRING8, 0, (ULONG)"Topic Folder"}, 
        { PT_LONG,    0, 0},      
        { PT_BOOLEAN, 0, FALSE},  
        { PT_BINARY,  0, BINARY_PROP_VALUE( BinData)},
        { PT_MV_LONG, 0, MULTI_VALUE_PROP( LongArray)},
    };
    
    // Somewhere in your OnInitDialog() function make the following call.
    hr = HrSetExtProps( ARRAY_CNT( ExtensionProps), ExtensionProps);
#endif
#endif

// -----------------------------------------------------------------------------
// This is called once per standard property sheet.  Not at all for our property
// sheets.  If you want to disable some or all of the standard property sheets 
// Then define this function in your code.  Your function will need to return 
// FALSE to disable a default property sheet.
// -----------------------------------------------------------------------------

BOOL PASCAL bShowPage( UINT iddAdminPage);

// -----------------------------------------------------------------------------
// This function is called once durring initialization.  Return -1 to cause the 
// first standard property sheet to be displayed.  Or return the index of one of 
// our property sheets to have it come up first.  The user can override this 
// function by simply defining their own function in their code.
// -----------------------------------------------------------------------------

INT PASCAL iStartPage( void);

// -----------------------------------------------------------------------------
// Class to initialize the DLL for both Windows and MFC.
// -----------------------------------------------------------------------------

class CInitDLL : public CWinApp
{
public:
    ~CInitDLL();
	virtual BOOL InitInstance(); // Initialization
	virtual int ExitInstance();  // Termination (WEP-like code)

	// Nothing special for the constructor.
	CInitDLL(LPCSTR pszAppName) : CWinApp(pszAppName) {}
};

// -----------------------------------------------------------------------------
// This dialog class allows easy subclassing of controls.
// -----------------------------------------------------------------------------

class CADialog : public CDialog
{
protected:    
    CADialog() : CDialog() {}   // Constructor.
    CADialog( LPCSTR lpszTemplateName, CWnd* pParentWnd = NULL) : CDialog( lpszTemplateName, pParentWnd) {}
    CADialog( UINT nIDTemplate, CWnd* pParentWnd = NULL) : CDialog( nIDTemplate, pParentWnd) {}

    // To make subclassing controls to CWnd derived objects easier.
    HRESULT HrSubclassWindow( 
        int   nID,  // Id of a control in this dialog.
        CWnd& Wnd); // Reference to MFC CWnd object to connect to Windows control.
};

// -----------------------------------------------------------------------------
// Derive your dialog class from this class to have it become an automatic
// property sheet of the Exchange Administration application.
//
// NOTE: In your derived dialog you MUST NOT release a MAPI interface in the 
//       destructor, this will cause a deadlock hang.  Use the OnDestroy() method
//       of the dialog to ULRELEASE() any MAPI Interface objects.
//
//       The problem is that the destructor does not get called until the DLL is
//       unloading.  This is a single threaded opperation in NT.  The ULRELEASE
//       process needs to run multi-threaded and waits INFINITELY for threads to
//       terminate.  The threads can't terminate until the DLL exits, and the DLL
//       can't exit until the threads terminate resulting in a deadlock.
// -----------------------------------------------------------------------------

class CAdminDialog : public CADialog
{
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// You may find the following information useful for creating your dialog.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
protected:
    // Protected constructor insures that you must derive a class from CAdminDialog
    // in order to use it.  You may NOT instantiate directly from this class.
    //
    // To override the show page function you must pass in the pfnShowPage parameter.
    // Your function will be called once for each default property sheet and will 
    // receive an id of the sheet.  Your function must return TRUE if you want it 
    // to show.
    CAdminDialog( 
        UINT iddDialog,     // The resource ID of your dialog.
        UINT idsName,       // The resource ID of the string containing the name
                            // used by admin for the tab of your property sheet.
        LPSTR lpszBlobName = NULL);// Name of extension data blob.

    ~CAdminDialog();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Functions to make displaying of message boxes easier. 
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // If the caller does not pass in the lpszCaption then use the title of the 
    // parent window for the default title of our message box.
    int MessageBox( LPCSTR lpszText, LPCSTR lpszCaption = NULL, UINT nType = MB_OK);
    int MessageBox2( int IDText, int IDCaption = NULL, UINT nType = MB_OK);
    CString m_sMsgBoxCaption;   // This will contain the title of the parent window.

    // Displays a message box with a resource string for invalid entries.  After
    // the user presses OK the appropriate control gets focus.
    void InvalidEntry( int nResourceStrID, CWnd& wndCtrl);

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Use this function to create child dialog box templates.  It will ensure that 
    // the correct language and fonts are used.  Then use the CDialog::InitModalIndirect()
    // function to create the dialog
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

public:
    const HGLOBAL LoadDialogTemplate( UINT iddDialog);

    static int LoadStringA(UINT wID, LPSTR szBuf,  int cchBuf);
	static int LoadStringW(UINT wID, LPWSTR wzBuf, int cchBuf);

    // Free the template loaded with the above function.
    void FreeDialogTemplate( HGLOBAL* lphDlgTemplate)  { m_pAdminFunctions->pfnFreeDialogResource( (LPBYTE*) lphDlgTemplate);}

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Override these virtual functions in your derived class if you want them to do
    // something.
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
protected:    
    // Called when a different property sheet has been selected or when either the
    // OK or APPLY NOW button is pressed.  This saves the data to a memory buffer 
    // inside of admin.  Even if the user just switches to a different property sheet
    // this needs to be done so that other property sheets can read any changes that 
    // may have been made to the data.
    // Return TRUE if data has been validated and saved.  Default return is TRUE.
    virtual BOOL bSaveData();
    
    // Called when either the OK or APPLY NOW button is pressed and after bSaveData().
    // Return TRUE if data has been committed.  This saves the extension data and returns
    // TRUE if it was successful.
    virtual BOOL bCommitData();
    
    // Called so that your property sheet can refresh with data that may have been changed
    // by another property sheet.  You say you don't have more than one property sheet that
    // modifies the same data fields.  Ahh, but the Exchange SDK provides a sample that 
    // lets an Administrator view and modify any Exchange SDK packed extension data array.
    virtual void Refresh();

    // Called to determine if you supply help.  Return TRUE if you do, defaults to FALSE.
    virtual BOOL bHasHelp();
    
    // Called to start help.  Default does nothing.
    virtual VOID DoHelp();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // Call this to inform admin that the data has changed.
    void DataHasChanged() { m_pAdminFunctions->pfnInfoHasChanged( GetSafeHwnd());}

    // Get the count of extension data properties.
    ULONG GetExtCount() { return( m_cExtProps);}

    // Set the extension data properties to an existing property value array.  This
    // can be used to create a blob for the first time.  To do this initialized the
    // lpExtProps array with just property types and no real data.  Then use the 
    // CAdminDialog::HrMod...() functions to set the values.
    HRESULT HrSetExtProps(
        ULONG        cExtProps,     // Count of extension data properties.
        LPSPropValue lpExtProps);   // Array of properties to set extension data to.
    
    // Overloaded function to convert our property initialization structure to
    // the real MAPI property structure.  (This is temporary until MAPI changes
    // their _UPV union definition.)
    HRESULT HrSetExtProps(
        ULONG        cExtProps,     // Count of extension data properties.
        LPSInitPropValue lpExtProps)// Array of properties to set extension data to.
    {
        return( HrSetExtProps( cExtProps, (LPSPropValue) lpExtProps));
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Functions to get extension data.
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Use this to get a binary extension data property.
    LPSBinary GetExtBinary(
        ULONG iProp);       // Index of property.

    // Use this to get a string extension data property.
    LPSTR GetExtString(
        ULONG iProp);       // Index of property.

    // Use this to get a long extension data property.
    LONG GetExtLong(
        ULONG iProp);       // Index of property.

    // Use this to get a double word extension data property.
    DWORD GetExtDWord(
        ULONG iProp)        // Index of property.
    {
        return( (DWORD) GetExtLong( iProp));
    }

    // Use this to get a boolean extension data property.
    BOOL GetExtBool(
        ULONG iProp);       // Index of property.

    // Use this to get a system time extension data property.
    FILETIME GetExtSysTime(
        ULONG iProp);       // Index of property.

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Functions to modify extension data.
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Use this to modify a binary extension data property.
    HRESULT HrModExtBinary(
        IN ULONG  iProp,    // Index of property
        IN ULONG  cb,       // Count of new data bytes.
        IN const LPBYTE lpNew);   // New data bytes.

    // Use this to modify a string extension data property.
    HRESULT HrModExtString(
        IN ULONG   iProp,     // Index of property
        IN LPCSTR lpszNew);   // New data bytes.

    // Use this to modify a long extension data property.
    HRESULT HrModExtLong(
        IN ULONG  iProp,    // Index of property
        IN LONG   lNew);    // New long data value.
    
    // Use this to modify a double word extension data property.
    HRESULT HrModExtDWord(
        IN ULONG  iProp,    // Index of property
        IN DWORD  dwNew)     // New long data value.
    {
        return( HrModExtLong( iProp, (LONG) dwNew));
    }
    
    // Use this to modify a boolean extension data property.
    HRESULT HrModExtBool(
        IN ULONG  iProp,    // Index of property
        IN BOOL   bNew);    // New boolean data value.

    // Use this to modify a SysTime extension data property.
    HRESULT HrModExtSysTime(
        IN ULONG    iProp,    // Index of property
        IN FILETIME ftNew);   // New boolean data value.

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Other miscellaneous functions that wrap administration functions.
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Add service to be tracked by Server Monitor.
    HRESULT HrAddService(
        IN LPSTR lpszServiceName);   // SHORT name of the service.

    // Remove service to be tracked by Server Monitor.
    HRESULT HrRemoveService( 
        IN LPSTR lpszServiceName);   // SHORT name of the service.

    // You MUST release the array with FreeNameList.
    BOOL GetNameList( 
        OUT int*     lpcNameList,     // Ptr to number of WIDE strings in the array.
        OUT LPWSTR** lppwszNameList); // Ptr to a ptr of WIDE string array.  

    BOOL SetNameList(
        IN int      cNameList,        // Number of WIDE strings in the array.
        IN LPWSTR*  lpwszNameList);   // Ptr to a WIDE string array.  

    // Free the name list that was received in a call to GetNameList.
    void CAdminDialog::FreeNameList(
        IN int      cNameList,        // Number of WIDE strings in the array.
        IN LPWSTR*  lpwszNameList)    // Ptr to a WIDE string array.  
    {
        m_pAdminFunctions->pfnFreeNameList( cNameList, lpwszNameList);
    }    

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Functions to get other miscellaneous data that admin gave us.
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	// Return the MAPI session interface pointer.
	IMAPISession* GetMAPISession() { return( m_pMAPISession);}

	// Return the MAPI address book interface pointer.
	IAddrBook* GetAddrBook() { return( m_pAddrBook);}

	// Return the MAPI address book container interface pointer.
	IABContainer* GetABContainer() { return( m_pABContainer);}

	// Return the name of computer on which the gateway runs, when applicable.
	LPWSTR GetComputerName() { return( m_pAdminObjectInfo->szComputerName);}
	
	// Return the distinguished name of the object administered.
	LPWSTR GetDN()           { return( m_pAdminObjectInfo->szDistinguishedName);}	
	
	// Return the distinguished name of the server running the home message database.
	LPWSTR GetDNHomeMDB()    { return( m_pAdminObjectInfo->szDNHomeMDB);}

	// Return the distinguished name of the server running the home message transport agent.
	LPWSTR GetDNHomeMTA()    { return( m_pAdminObjectInfo->szDNHomeMTA);}
	
	// Return the language id.
	static LANGID GetLanguageId()   { return( LANGIDFROMLCID(m_lcid));}
	static void   SetLcid(LCID lcid);

	// Return font in use by Admin.
	HFONT GetAdminFont()     { return( m_pAdminObjectInfo->hfontDialog);}

    // Return the object id.  Compare this against one or more of the #defined 
    // constants that can be found in "adminext.h"
    UINT GetObjectId()       { return( m_pAdminObjectInfo->uObjectID);}

    // Return a const ptr to the extension data properties.
    const LPSPropValue GetExtProps() { return( m_lpExtProps);}

    // Are we in read only mode?
    static BOOL bIsReadOnly(){ return( m_bReadOnly);}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Your dialog need not be concerned with these members.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
protected:
    // Load extension data into buffer contained in this object.  This is called
    // by the OnInitDialog() and OnChildActivate() functions of this class so 
    // you will probably not want to call this in your code.
    HRESULT HrLoadExtData();
    
    // Save extension data buffer that is contained in this object.  This is called
    // by the bCommitData function of this class so you will probably not want
    // to call this in your code.
    HRESULT HrSaveExtData();

public:
    static VOID ADMIN_Initialize( ADMIN_AdministratorConnections*, ADMIN_AdministratorFunction*);

private:
    UINT    m_iddDialog;    // The resource ID of your dialog.
    UINT    m_idsName;      // The resource ID of the string containing the name
                            // used by admin for the tab of your property sheet. 
    LPWSTR  m_lpwszBlobName;// Name of extension data blob (if there is one).
    
    ULONG        m_cExtData;   // Count of extension data blob.
    LPBYTE       m_lpbExtData; // Extension data blob.
    ULONG        m_cExtProps;  // Count of extension data properties. 
    LPSPropValue m_lpExtProps; // Ptr to extension data properties.
    
    static CPtrList          m_DlgList;      // List of dialog instances derived from this class.
    static IMAPISession*     m_pMAPISession; // The MAPI session handle opened by admin.
    static IAddrBook*        m_pAddrBook;    // The MAPI Address book opened by admin.
	static IABContainer*     m_pABContainer; // The MAPI Address Book Container opened by admin.
    static ADMIN_SheetInfo*  m_pSheetInfo;   // Dynamic information used by admin.
    static ADMIN_ObjectInfo* m_pAdminObjectInfo; // Admin server name and other useful DNs.
    static ADMIN_AdministratorFunction* m_pAdminFunctions;  // Admin functions available to you.
    static BOOL              m_bReadOnly;     // Open property sheets in read only mode.
	static LCID				 m_lcid;          // LCID to be used

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Finds the CAdminDialog derived object using a handle to the dialog's window.
    static CAdminDialog* FindDlg( HWND hDlg);
    
    // Helper functions to access protected and private data.
    static BOOL bInitSheet( ADMIN_ObjectInfo* poi, ULONG fFlags, ADMIN_SheetInfo** ppsi, UINT* pcsi, VOID** ppNotUsed);
    static void DeinitSheet( IN VOID* pNotUsed);
    
    // Called directly by the Exchange Administrator program.
    friend BOOL PASCAL bInstallExtension(ADMIN_ObjectInfo* poi);
    friend BOOL PASCAL bDeinstallExtension(ADMIN_ObjectInfo* poi);
    friend BOOL PASCAL bInitSheet( ADMIN_ObjectInfo* poi, ULONG fFlags, ADMIN_SheetInfo** ppsi, UINT* pcsi, VOID** ppNotUsed);
    friend BOOL PASCAL bShowPage( UINT iddAdminPage);
    friend INT  PASCAL iStartPage( void);
    friend BOOL PASCAL bSaveData(VOID*, HWND);
    friend BOOL PASCAL bCommitData(VOID*, HWND);
    friend VOID PASCAL DeinitSheet(VOID*);
    friend BOOL PASCAL bHasHelp(VOID*, HWND);
    friend VOID PASCAL DoHelp(VOID*, HWND);

// -----------------------------------------------------------------------------
// Check function stuff
// -----------------------------------------------------------------------------

__inline HRESULT CHK_HrExtData(
    ULONG iProp,            // Index of property.
    ULONG ulPropType)       // Property type expected.
{
    if( iProp >= m_cExtProps)
        RETURN( E_INVALIDARG);
    
    // Sanity check that should never fail.
    if( !TEST_READ_PTR( m_lpExtProps, sizeof( SPropValue) * m_cExtProps))
        RETURN( E_FAIL);

    // Make sure we have the property type we are expecting.
    if( PROP_TYPE( m_lpExtProps[ iProp].ulPropTag) != ulPropType)
        RETURN( E_FAIL);

    return( NOERROR);
}

// -----------------------------------------------------------------------------

__inline HRESULT CHK_HrModExtBin( 
    IN ULONG  iProp,    // Index of property
    IN ULONG  cb,       // Count of new data bytes.
    IN LPBYTE lpNew)    // New data bytes.
{
    HRESULT hr = CHK_HrExtData( iProp, PT_BINARY);
    if( FAILED( hr))
        return( hr);

    if( cb == 0)
        RETURN( E_INVALIDARG);

    if( !TEST_READ_PTR( lpNew, cb))
        RETURN( E_INVALIDARG);

    return( NOERROR);
}

// -----------------------------------------------------------------------------

__inline HRESULT CHK_HrModExtString(
    IN ULONG   iProp,   // Index of property
    IN LPCSTR lpszNew) // New data string.
{
    HRESULT hr = CHK_HrExtData( iProp, PT_STRING8);
    if( FAILED( hr))
        return( hr);

    if( !TEST_STRING_PTR( lpszNew))
        RETURN( E_INVALIDARG);

    return( NOERROR);
}

// -----------------------------------------------------------------------------

__inline HRESULT CHK_HrSetExtProps(
    ULONG        cExtProps,     // Count of extension data properties.
    LPSPropValue lpExtProps)    // Array of properties to set extension data to.
{
    if( cExtProps == 0)
        RETURN( E_INVALIDARG);

    if( !TEST_READ_PTR( lpExtProps, sizeof( SPropValue) * cExtProps))
        RETURN( E_INVALIDARG);

    if( m_lpwszBlobName == NULL)
        RETURN( E_FAIL);    // There must be a blob name to use this function.

    return( NOERROR);
}
 

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Class wizard stuff.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
public:
	//{{AFX_DATA(CAdminDialog)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdminDialog)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CAdminDialog)
	virtual BOOL OnInitDialog();
    afx_msg LONG OnChildActivate( UINT, LONG);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// -----------------------------------------------------------------------------
// Our dialog proc calls the MFC one.
// -----------------------------------------------------------------------------

LRESULT CALLBACK AdminDlgProc(HWND, UINT, WPARAM, LPARAM lParam);   // Ours
BOOL CALLBACK AfxDlgProc(HWND, UINT, WPARAM, LPARAM lParam);     // MFC

// -----------------------------------------------------------------------------
#ifdef _GLOBAL_OBJECTS_
#pragma message("Declaration of global objects for: " __FILE__)

// Instance of application initialization object.
CInitDLL InitDLL(_T("InitDLL.dll"));    

// Intialize static member data.
CPtrList                        CAdminDialog::m_DlgList(2);
ADMIN_SheetInfo*                CAdminDialog::m_pSheetInfo = NULL;
ADMIN_AdministratorFunction*    CAdminDialog::m_pAdminFunctions = NULL;  
ADMIN_ObjectInfo*               CAdminDialog::m_pAdminObjectInfo = NULL;
IMAPISession*                   CAdminDialog::m_pMAPISession = NULL;
IAddrBook*                      CAdminDialog::m_pAddrBook = NULL;
IABContainer*                   CAdminDialog::m_pABContainer = NULL;
BOOL                            CAdminDialog::m_bReadOnly = FALSE;
LCID                            CAdminDialog::m_lcid = MAKELCID( MAKELANGID( LANG_ENGLISH, SUBLANG_NEUTRAL),  SORT_DEFAULT);

#else  // ! _GLOBAL_OBJECTS_

extern CInitDLL InitDLL;

#endif //_GLOBAL_OBJECTS_
// -----------------------------------------------------------------------------

#endif  //_EXADMIN_H_
