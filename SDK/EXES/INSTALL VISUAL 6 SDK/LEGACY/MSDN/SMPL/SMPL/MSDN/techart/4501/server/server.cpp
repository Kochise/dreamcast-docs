/*************************************************************************
**
**    VtblServer Application. Implements a custom interface (IVtblServer) 
**    which can be be marshaled by OLE Automation's marshaler.
**
**    server.cpp
**
**     Written by Microsoft Product Support Services, Windows Developer Support
**    (c) Copyright Microsoft Corp. 1995 All Rights Reserved
**
*************************************************************************/
#include <windows.h>
#include <stdio.h>
#include <initguid.h>
#include "server.h"      

// Globals  
CVtblServer * g_pVtblServer;

/*
 * Main
 *
 * Purpose:
 *  Main entry point of application.
 *  This function initializes the server and processes the message loop. 
 *
 */
int _cdecl main(int argc, char *argv[])
{
    MSG msg;
    DWORD dwRegisterCF;     

    Initialize();
    if (!ProcessCmdLine(argc, argv, &dwRegisterCF))
    {
        Uninitialize(dwRegisterCF);   
        return -1;
    }
        
   // Loop until WM_QUIT is posted by PostQuitMessage. OLE creates a hidden window
   // on this thread. Incoming OLE calls synchronize with this thread by posting
   // the hidden window a message. This message retrieval loop will dispatch these messages
   // to the OLE window.
    while (GetMessage(&msg, NULL, 0, 0))
    {
       TranslateMessage(&msg);
       DispatchMessage(&msg);
    }
   
    Uninitialize(dwRegisterCF);   
    return 0;
}

/*
 * Initialize
 *
 * Purpose:
 *  Intializes OLE and creates global VtblServer object
 *
 * Return Value:
 *  TRUE if initialization succeeded, FALSE otherwise.
 */
BOOL Initialize()
{  
    HRESULT hr; 
    TCHAR ach[STR_LEN];
    HINSTANCE hinst;
    
    // Intialize OLE
    hr = OleInitialize(NULL);
    if (FAILED(hr))
       return FALSE; 
    
    hinst = (HINSTANCE)GetModuleHandle(NULL);
    // Create an instance of the VtblServer object. Object is
    // created with refcount 0. 
    LoadString(hinst, IDS_Message, ach, sizeof(ach));
    hr = CVtblServer::Create(ach, &g_pVtblServer);       
    if (FAILED(hr))
        return FALSE;
    return TRUE;          
}

/*
 * ProcessCmdLine
 *
 * Purpose:
 *  Check command line arguments. 
 *  If /Embedding, the class factory of the object is registered.
 *  If /RegServer, the server registers in the registry.  
 *
 * Parameters:
 *  argc            Number of command line arguments
 *  argv            Command line passed to application
 *  pdwRegisterCF   Returns id returned after class factory registration. Can be used to 
 *                  revoke class factory registration. 
 *
 * Return Value:
 *    TRUE if class factory was registered, FALSE otherwise.
 *
 */
BOOL ProcessCmdLine(int argc, char *argv[], LPDWORD pdwRegisterCF)
{
    LPCLASSFACTORY pcf = NULL;
    HRESULT hr;
    BOOL bStartedByOle = FALSE;
   
    *pdwRegisterCF = 0;     

    // Parse each item, skip the command name
    for (int i = 1; i < argc; i++)
    {
        if (stricmp(argv[i], "-Embedding" ) == 0 || stricmp(argv[i], "/Embedding" ) == 0)
        {
            bStartedByOle = TRUE;
            break;
        }
        else if (stricmp(argv[i], "-RegServer") == 0 || stricmp(argv[i], "/RegServer") == 0)
        {
            if (RegisterServer(CLSID_VtblServer, TEXT("server.tlb")))
                printf("Server Registration Succeeded\n");
            else printf("Server Registration Failed\n"); 
            return FALSE;
        }
        else printf("Unknown Command Line Argument\n");
    }

    // Expose class factory for application object if the server was started by OLE
    if (bStartedByOle)
    {
        pcf = new CVtblServerCF;
        if (!pcf)
            goto error;  
        pcf->AddRef();           
        hr = CoRegisterClassObject(CLSID_VtblServer, pcf,
                                     CLSCTX_LOCAL_SERVER, REGCLS_SINGLEUSE,
                                     pdwRegisterCF);
        if (FAILED(hr))
            goto error;           
        pcf->Release();
    }     
    return TRUE;           
           
error:
    if (pcf)
        pcf->Release();
    return FALSE;
}

/*
 * Uninitialize
 *
 *  Purpose:
 *   Revoke class factory and uninitialize OLE.
 *
 * Parameters:
 *  dwRegisterCF     ID returned after class factory registration. 
 *
 */
void Uninitialize(DWORD dwRegisterCF)
{
    if (dwRegisterCF != 0)
        CoRevokeClassObject(dwRegisterCF);
    OleUninitialize();
}


/*
 * CVtblServer::Create
 *
 * Purpose:
 *  Creates an instance of the VtblServer object and initializes it.
 *
 * Parameters:
 *  lpszMessage     Initial message. 
 *  ppVtblServer    Returns VtblServer automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CVtblServer::Create(LPTSTR lpszMessage, CVtblServer** ppVtblServer) 
{    
    HRESULT hr;
    CVtblServer *pVtblServer = NULL;   
     
    *ppVtblServer = NULL;
    
    // Create VtblServer object
    pVtblServer = new CVtblServer();
    if (pVtblServer == NULL)
        goto error;
    
    // Initialize ref count to 0 and get console handle to write out to. 
    pVtblServer->m_cRef = 0;
    pVtblServer->m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // Initialize VtblServer Message. 32 bit OLE uses Unicode strings.
    // Convert the string passed to SysAllocString to Unicode if required.
    pVtblServer->m_bstrMessage = SysAllocString(TO_OLE_STRING(lpszMessage));
    if (NULL == pVtblServer->m_bstrMessage)
    {
        hr = E_OUTOFMEMORY;    
        goto error;
    }
         
    *ppVtblServer = pVtblServer;
    return S_OK;
    
error:                        
    if (pVtblServer == NULL) return E_OUTOFMEMORY;                        
    if (pVtblServer->m_bstrMessage) SysFreeString(pVtblServer->m_bstrMessage);      
    
    // Set to NULL to prevent destructor from attempting to free again
    pVtblServer->m_bstrMessage = NULL;
    
    delete pVtblServer;
    return hr;
}

/*
 * CVtblServer::CVtblServer
 *
 * Purpose:
 *  Constructor for CVtblServer object. Initializes members to NULL.
 *
 */
CVtblServer::CVtblServer() 
{   
    extern ULONG g_cObj;
     
    m_bstrMessage = NULL;
}

/*
 * CVtblServer::~CVtblServer
 *
 * Purpose:
 *  Destructor for CVtblServer object. 
 *
 */
CVtblServer::~CVtblServer()
{ 
     extern ULONG g_cObj;
     
     if (m_bstrMessage) SysFreeString(m_bstrMessage);          
     PostQuitMessage(0);   // Post WM_QUIT. Terminate application when the object destructs.
}

/*
 * CVtblServer::QueryInterface, AddRef, Release
 *
 * Purpose:
 *  Implements IUnknown::QueryInterface, AddRef, Release
 *
 */
STDMETHODIMP
CVtblServer::QueryInterface(REFIID iid, void** ppv) 
{   
    *ppv = NULL;
    
    if (iid == IID_IUnknown || iid == IID_IVtblServer  ) 
        *ppv = this;   
    else return E_NOINTERFACE; 

    AddRef();
    return S_OK;    
}


STDMETHODIMP_(ULONG)
CVtblServer::AddRef(void)
{ 
    return ++m_cRef;
}

STDMETHODIMP_(ULONG)
CVtblServer::Release(void)
{
    if(--m_cRef == 0)
    {
        delete this;
        return 0;
    }
    return m_cRef;
}

/*
 * CVtblServer::put_Message
 *
 * Purpose:
 *  Stores message string received from caller
 *
 */    
STDMETHODIMP
CVtblServer::put_Message(BSTR bstrMessage)
{
    // Save a copy of the message because the caller will
    // free all parameters.
    SysReAllocString(&m_bstrMessage, bstrMessage);   
    return S_OK; 
}

/*
 * CVtblServer::get_Message
 *
 * Purpose:
 *  Returns copy of message string to the caller
 *
 */  
STDMETHODIMP
CVtblServer::get_Message(BSTR *pbstrMessage)
{   
    // Return a copy of the message. The caller will free
    // all parameters.
    *pbstrMessage = SysAllocString(m_bstrMessage);
    return (*pbstrMessage) ? S_OK: E_OUTOFMEMORY; 
}

/*
 * CVtblServer::DisplayMessage
 *
 * Purpose:
 *  Displays current message the specified number of times
 *  at the specified coordinate.
 *
 * Parameters:
 *  psaCoordinate SAFEARRAY(unsigned char) that contains the serialized 
 *                COORD structure which specifies the coordinate at which
 *                the message is to be displayed.
 *  nTimes        Number of times the message is to be displayed.
 *
 */  
STDMETHODIMP
CVtblServer::DisplayMessage(SAFEARRAY *psaCoordinate, short nTimes)
{  
    COORD  coord;
        HRESULT hr;
    
    // Validate dimensions of array 
    if (SafeArrayGetDim(psaCoordinate) != 1)
        return E_INVALIDARG;

    // Get COORD structure from array    
    unsigned char *pc;   
    hr = SafeArrayAccessData(psaCoordinate, (void **)&pc);
    if (FAILED(hr))
        return VTBLSERVER_E_UNEXPECTED;  
    memcpy(&coord, pc, sizeof(COORD));
    SafeArrayUnaccessData(psaCoordinate);

    // Position the console cursor
    SetConsoleCursorPosition(m_hStdOut, coord);

    // Display the message nTimes times. m_bstrMessage is 
    // Unicode, so convert to ANSI if this app is ANSI.
    TCHAR *psz = FROM_OLE_STRING(m_bstrMessage);
    DWORD cCharsWritten;
    for (short n = nTimes; n; n--)
    {
        // Display message
        WriteConsole(m_hStdOut, (void *)psz, lstrlen(psz), &cCharsWritten, NULL);
        // Update console cursor for the next line
        coord.Y += 1;
        SetConsoleCursorPosition(m_hStdOut, coord);
    }     
    return S_OK;
}

/*
 *  Class Factory implementation
 */

CVtblServerCF::CVtblServerCF(void)
{    
    m_cRef = 0; 
}

/*
 * CVtblServerCF::QueryInterface, AddRef, Release
 *
 * Purpose:
 *  Implements IUnknown::QueryInterface, AddRef, Release
 *
 */
STDMETHODIMP
CVtblServerCF::QueryInterface(REFIID iid, void ** ppv) 
{   
    *ppv = NULL;
    
    if (iid == IID_IUnknown || iid == IID_IClassFactory)
        *ppv = this;
    else 
        return E_NOINTERFACE; 

    AddRef();
    return S_OK;    
}


STDMETHODIMP_(ULONG)
CVtblServerCF::AddRef(void)
{ 
    return ++m_cRef;
}


STDMETHODIMP_(ULONG)
CVtblServerCF::Release(void)
{   
    if(--m_cRef == 0)
    {
        delete this;
        return 0;
    }
    return m_cRef;
}

/*
 * CVtblServerCF::CreateInstance, LockServer
 *
 * Purpose:
 *  Implements IClassFactory::CreateInstance, LockServer
 *
 */
STDMETHODIMP
CVtblServerCF::CreateInstance(IUnknown * punkOuter,
                         REFIID riid,
                         void ** ppv)
{
     HRESULT hr;
    
    *ppv = NULL;
    
    // This implementation does'nt allow aggregation
    if (punkOuter)
        return CLASS_E_NOAGGREGATION;
    
    // This is REGCLS_SINGLEUSE class factory, so IClassFactory::CreateInstance will be
    // called atmost once. The global application object which has already been created 
    // is returned. A REGCLS_MULTIPLEUSE class factory's CreateInstance would be 
    // called multiple times and could create a new object each time. 
    hr = g_pVtblServer->QueryInterface(riid, ppv);
    if (FAILED(hr))
    { 
        delete g_pVtblServer;
        return hr;
    }
    return S_OK;
}

STDMETHODIMP
CVtblServerCF::LockServer(BOOL fLock)
{    
    CoLockObjectExternal(g_pVtblServer, fLock, TRUE); 
    return S_OK;       
}


 // Quick & Dirty ANSI/Unicode conversion helper functions. Cannot
 // convert strings longer that STRCONVERT_MAXLEN. Also note that
 // the converted string is placed in a static array, which is reused
 // the next time the function is called. So use the converted string
 // before converting another string.
#ifndef UNICODE
char* ConvertToAnsi(OLECHAR * szW)
{
    static char achA[STRCONVERT_MAXLEN]; 
  
    WideCharToMultiByte(CP_ACP, 0, szW, -1, achA, STRCONVERT_MAXLEN, NULL, NULL);  
    return achA; 
} 

OLECHAR* ConvertToUnicode(char * szA)
{
    static OLECHAR achW[STRCONVERT_MAXLEN]; 

    MultiByteToWideChar(CP_ACP, 0, szA, -1, achW, STRCONVERT_MAXLEN);  
    return achW; 
}
#endif

/*
 * RegisterServer
 *
 * Purpose:
 *  Registers the following entries in the registry with the full paths of
 *  server.exe and server.tlb.

; Server registration
HKEY_CLASSES_ROOT\CLSID\{2ED17401-F80F-11ce-8161-00AA0060D733}
HKEY_CLASSES_ROOT\CLSID\{2ED17401-F80F-11ce-8161-00AA0060D733}\LocalServer32 = server.exe

; Type library registration information  
HKEY_CLASSES_ROOT\TypeLib\{2ED17400-F80F-11ce-8161-00AA0060D733}
HKEY_CLASSES_ROOT\TypeLib\{2ED17400-F80F-11ce-8161-00AA0060D733}\1.0 = VtblServer 1.0 Type Library
HKEY_CLASSES_ROOT\TypeLib\{2ED17400-F80F-11ce-8161-00AA0060D733}\1.0\0\win32 = server.tlb 

; Interface registration.
HKEY_CLASSES_ROOT\Interface\{2ED17402-F80F-11ce-8161-00AA0060D733} = IVtblServer
HKEY_CLASSES_ROOT\Interface\{2ED17402-F80F-11ce-8161-00AA0060D733}\TypeLib = {2ED17400-F80F-11ce-8161-00AA0060D733}
HKEY_CLASSES_ROOT\Interface\{2ED17402-F80F-11ce-8161-00AA0060D733}\ProxyStubClsid = {00020424-0000-0000-C000-000000000046}
HKEY_CLASSES_ROOT\Interface\{2ED17402-F80F-11ce-8161-00AA0060D733}\ProxyStubClsid32 = {00020424-0000-0000-C000-000000000046}

 *
 * Parameters:
 *  clsid          CLSID of server.
 *  pszTypeLibrary Name of TypeLibrary file.
 *
 */
BOOL RegisterServer(REFCLSID clsid, LPTSTR pszTypeLibrary)
{
    TCHAR szPathName[_MAX_PATH];
    OLECHAR szClassID[GUID_CCH];
    HKEY hkeyClassID;

    StringFromGUID2(clsid, szClassID, GUID_CCH);
    // Get the full path of server.exe
    GetModuleFileName((HINSTANCE)GetModuleHandle(NULL), szPathName, _MAX_PATH);

    // Register the path of the server
    TCHAR szKey[_MAX_PATH];
    wsprintf(szKey, TEXT("CLSID\\%s"), FROM_OLE_STRING(szClassID));
    if (RegCreateKey(HKEY_CLASSES_ROOT, szKey, &hkeyClassID) != ERROR_SUCCESS)
        return FALSE;
    if (RegSetValue(hkeyClassID, TEXT("LocalServer32"), REG_SZ, szPathName, _MAX_PATH)
            != ERROR_SUCCESS)
        return FALSE;

    // Find last backslash in path of the server
    LPTSTR lpsz = _tcsrchr(szPathName, TEXT('\\'));
    // Replace characters after the last backslash with the name of the type library.
    // This will result in szPathName containing the full path of the type library.
    // If backslash was not found, append the name of the type library.
    if (lpsz != NULL)
        lpsz++;
    else lpsz = szPathName + _tcsclen(szPathName);
    while(*lpsz++ = *pszTypeLibrary++) 
        ;
        
    // Load and register type library and the custom interface declared in the type library.
    LPTYPELIB ptlib;
    HRESULT hr = LoadTypeLib(TO_OLE_STRING(szPathName), &ptlib);
    if (FAILED(hr))
        return FALSE;
    // RegisterTypeLib will register the type library and all the interfaces that it
    // contains.
    hr = RegisterTypeLib(ptlib, TO_OLE_STRING(szPathName), NULL);
    ptlib->Release();
    if (FAILED(hr))
        return FALSE;
    return TRUE;
}


   
    
    




