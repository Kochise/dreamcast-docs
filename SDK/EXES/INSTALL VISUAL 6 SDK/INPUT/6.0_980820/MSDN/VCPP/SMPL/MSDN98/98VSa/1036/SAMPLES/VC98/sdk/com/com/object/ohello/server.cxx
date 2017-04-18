/*+----------------------------------------------------------------------------

Microsoft Windows Sample Program
Copyright (C) 1994 - 1997 Microsoft Corporation.  All rights reserved.

FILE:       server.cxx

USAGE:      server /REGSERVER   - Installs registry entries for the server.
            server /UNREGSERVER - Removes registry entries for the server.
            server -Embedding   - Server was auto-started by OLE.

PURPOSE:    Example of an OLE local server using a custom interface.
            This program illustrates the correct reference counting and 
            shutdown behavior for a multiple-use local server.  
            
            The sample code is safe for multiple threads.  This is not
            really necessary, but it makes it easy to convert this program
            to a multi-threaded server for a future version of Windows.

            This sample also provides an example of how to use the 
            Win32 registry functions to install a local server and a 
            proxy DLL in the registry.


FUNCTIONS:  DecrementLockCount  - Decrement the server's lock count.
            IncrementLockCount  - Increment the server's lock count.
            main                - Main entry point.
            ObjectCreated       - Called when object is created.
            ObjectDestroyed     - Called when object is destroyed.
            RegisterLocalServer - Create a registry entry for a local server.
            RegisterProxyDll    - Create a registry entry for a proxy DLL.
            UnregisterLocalServer - Remove a registry entry for a local server.
            UnregisterProxyDll  - Remove a registry entry for a proxy DLL.

COMMENTS:   The server program must be installed before running the client.
            Run server.exe /REGSERVER to install the server program.

-----------------------------------------------------------------------------*/
#include <windows.h>
#include <stdio.h>
#include "ohello.h"

void    PrintErrorMessage(HRESULT hr);
HRESULT RegisterClassFactory();
HRESULT RevokeClassFactory();

//Prototypes for local functions
HRESULT RegisterLocalServer(REFCLSID rclsid);
HRESULT RegisterProxyDll(const char *pszProxyDll);
HRESULT UnregisterLocalServer(REFCLSID rclsid);
HRESULT UnregisterProxyDll(const char *pszProxyDll);

//CLSID for the server object
extern "C" const CLSID CLSID_OHello 
    = {0xf9246031,0x9f33,0x11cd,{0xb2,0x3f,0x00,0xaa,0x00,0x33,0x9c,0xce}};

long    g_LockCount   = 0;
long    g_ObjectCount = 0;

//+---------------------------------------------------------------------------
//
//  Function:   DecrementLockCount
//
//  Synopsis:   Decrements the lock count.  The lock count controls the 
//              registration of the class factory in the class table.
//              DecrementLockCount revokes the class factory when the 
//              lock count is zero.
//
//  Called By:  ~CHello, IClassFactory::LockServer(FALSE).
//
//  See Also:   ObjectCreated, ObjectDestroyed, IncrementLockCount.
//
//----------------------------------------------------------------------------
void DecrementLockCount()
{
    //Decrement the lock count.
    if(InterlockedDecrement(&g_LockCount) == 0)
    {
        //When the lock count is decremented to zero,
        //revoke the class factory.
        RevokeClassFactory();
    }
}

//+---------------------------------------------------------------------------
//
//  Function:   IncrementLockCount
//
//  Synopsis:   Increments the lock count.  The lock count controls the 
//              registration of the class factory in the class table.
//              If necessary, IncrementLockCount will reregister the class
//              factory in the class table.
//
//  Called By:  CHello, IClassFactory::LockServer(TRUE).
//
//  See Also:   DecrementLockCount, ObjectCreated, ObjectDestroyed.
//
//----------------------------------------------------------------------------
void IncrementLockCount()
{
    if(g_LockCount == 0)
    {
        //Increment the lock count.
        InterlockedIncrement(&g_LockCount);

        //Reregister the class factory if necessary.
        RegisterClassFactory();
    }
    else
    {
        //Increment the lock count.
        InterlockedIncrement(&g_LockCount);
    }
}


//+---------------------------------------------------------------------------
//
//  Function:   main
//
//  Synopsis:   Main entry point for the server application.  This function 
//              initializes the server and processes the message loop.
//
//----------------------------------------------------------------------------
int _cdecl main(int argc, char *argv[])
{
    HRESULT hr = S_OK;
    int i;
    BOOL fRegisterServer = FALSE;
    BOOL fUnregisterServer = FALSE;
    BOOL fEmbedding = FALSE;
    BOOL fHelp = FALSE;
    MSG msg;

    // Parse each item, skip the command name
    for (i = 1; i < argc; i++)
    {
        if (stricmp( argv[i], "-Embedding" ) == 0)
        {
            //This server has been activated by OLE.
            fEmbedding = TRUE;
        }
        else if (stricmp( argv[i], "/REGSERVER" ) == 0)
        {
            fRegisterServer = TRUE;
        }
        else if (stricmp( argv[i], "/UNREGSERVER" ) == 0)
        {
            fUnregisterServer = TRUE;
        }
        else
        {
            fHelp = TRUE;
        }
    }

    if(fHelp == TRUE)
        {
        printf("USAGE: server /REGSERVER   - Installs server in the registry.\n");
        printf("       server /UNREGSERVER - Removes server from the registry.\n");
        printf("       server -Embedding   - Server was auto-started by OLE.\n");
        return 0;
    }
    else if(fUnregisterServer == TRUE)
    {
        hr = UnregisterLocalServer(CLSID_OHello);
        if(FAILED(hr))
        {
            printf("Failed to remove local server from the registry.\n");
            PrintErrorMessage(hr);
        }

        hr = UnregisterProxyDll("ohello.dll");
        if(FAILED(hr))
        {
            printf("Failed to remove proxy DLL from the registry.\n");
            PrintErrorMessage(hr);
        }
        return 0;
    }
    

    //Install the local server in the registry.
    hr = RegisterLocalServer(CLSID_OHello);
    if(FAILED(hr))
    {
        printf("Failed to install local server in the registry.\n");
        PrintErrorMessage(hr);
    }

    //Install the proxy DLL in the registry.
    hr = RegisterProxyDll("ohello.dll");
    if(FAILED(hr))
    {
        printf("Failed to install proxy DLL in the registry.\n");
        PrintErrorMessage(hr);
    }

    if(fRegisterServer == TRUE)
        return 0;

  
    //
    // Initialize OLE before calling any other OLE functions.
    //

    hr = CoInitialize(NULL);

    if(SUCCEEDED(hr))
    {   
        hr = RegisterClassFactory();

        if(SUCCEEDED(hr))
        {
            printf("Waiting for client to connect...\n");
            // Main message loop.  We will remain in the message loop 
            // until we get a WM_QUIT message.
    	    while (GetMessage(&msg, NULL, 0, 0))
    	    {
        	    TranslateMessage(&msg);
        	    DispatchMessage(&msg);
        	}

            //If the class factory is still registered in the 
            //class table, revoke it before we shut down.
            RevokeClassFactory();
	    }
        else
        {
            printf("Failed to register class factory.\n");
            PrintErrorMessage(hr);
        }
        CoUninitialize();
    }
    else
    {
        printf("CoInitialize failed.\n");
        PrintErrorMessage(hr);
    }

    return 0;
}


//+---------------------------------------------------------------------------
//
//  Function:   ObjectCreated
//
//  Synopsis:   Increments the object count controlling the main message loop
//              of the server process.  
//
//  Called By:  CHello, CHelloFactory.
//
//  See Also:   DecrementLockCount, IncrementLockCount, ObjectDestroyed.
//
//----------------------------------------------------------------------------
void ObjectCreated()
{
    InterlockedIncrement(&g_ObjectCount);
}


//+---------------------------------------------------------------------------
//
//  Function:   ObjectDestroyed
//
//  Synopsis:   Decrements the object count controlling the main message loop 
//              of the server process.  When the object count is decremented 
//              to zero, we post a WM_QUIT message.  The main message loop will
//              exit and terminate the server process.
//
//  Called By:  ~CHello, ~CHelloFactory.
//
//  See Also:   DecrementLockCount, IncrementLockCount, ObjectCreated.
//
//----------------------------------------------------------------------------
void ObjectDestroyed()
{
    if(InterlockedDecrement(&g_ObjectCount) == 0)
    {
        //When the last object is released, post a quit message.
        PostQuitMessage(0);
    }
}

  
//+---------------------------------------------------------------------------
//
//  Function:   RegisterLocalServer
//
//  Synopsis:   Creates a registry key for a local server.
//
//  Parameters: rclsid - Supplies the class ID of the local server.
//
//----------------------------------------------------------------------------
HRESULT RegisterLocalServer(REFCLSID rclsid)
{
    HRESULT hr;
    LONG error;
    HKEY hKeyCLSID;         // key for ...\Classes\CLSID
    HKEY hKeyClassID;
    HKEY hKey;              // current key
    DWORD dwDisposition;
    char szServer[MAX_PATH];
    char szClassID[39];
    unsigned long length;

    length = GetModuleFileNameA(0, szServer, sizeof(szServer));

    if(length == 0)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        return hr;
    }

    //create the CLSID key
    error = RegCreateKeyExA(
            HKEY_CLASSES_ROOT, 
            "CLSID",
            0, 
            "REG_SZ", 
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            0,
            &hKeyCLSID,
            &dwDisposition);

    if(!error)
    {
        //convert the class ID to a registry key name.
        sprintf(szClassID, "{%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
                rclsid.Data1, rclsid.Data2, rclsid.Data3,
                rclsid.Data4[0], rclsid.Data4[1],
                rclsid.Data4[2], rclsid.Data4[3],
                rclsid.Data4[4], rclsid.Data4[5],
                rclsid.Data4[6], rclsid.Data4[7]);
  
        //create key for the server class
        error = RegCreateKeyExA(hKeyCLSID, 
                                szClassID,
                                0, 
                                "REG_SZ", 
                                REG_OPTION_NON_VOLATILE,
                                KEY_ALL_ACCESS,
                                0,
                                &hKeyClassID,
                                &dwDisposition);

        if(!error)
        {
            //create LocalServer32 key.
            error = RegCreateKeyExA(hKeyClassID,           
                                    "LocalServer32",
                                    0, 
                                    "REG_SZ", 
                                    REG_OPTION_NON_VOLATILE,
                                    KEY_ALL_ACCESS,
                                    0,            
                                    &hKey,
                                    &dwDisposition);

            if(!error)
            {
                //Set the server name.
                error = RegSetValueExA(hKey, 
                                       "", 
                                       0, 
                                       REG_SZ, 
                                       (const unsigned char *)szServer,
                                       strlen(szServer) + 1);

                RegFlushKey(hKey);
                RegCloseKey(hKey);
            }
            RegCloseKey(hKeyClassID);
        }
        RegCloseKey(hKeyCLSID);
    }

    if(!error)
        hr = S_OK;
    else
        hr = HRESULT_FROM_WIN32(error);

    return hr;
}


//+---------------------------------------------------------------------------
//
//  Function:   RegisterProxyDll
//
//  Synopsis:   Creates registry entries for the interfaces contained in a 
//              proxy DLL.  
//
//  Parameters: pszProxyDll - Supplies the filename of the proxy DLL.
//
//  Notes:      RegisterProxyDll calls the DllRegisterServer function 
//              exported from the proxy DLL.
//
//----------------------------------------------------------------------------
HRESULT RegisterProxyDll(const char *pszProxyDll)
{
    HRESULT hr;
    HINSTANCE hProxyDll;
    HRESULT (STDAPICALLTYPE *pfnDllRegisterServer)();
 
    hProxyDll = LoadLibraryA(pszProxyDll);
    
    if(hProxyDll != 0)
    {
        pfnDllRegisterServer = (HRESULT (STDAPICALLTYPE *)())
            GetProcAddress(hProxyDll, "DllRegisterServer");
        
        if(pfnDllRegisterServer != 0)
            hr = (*pfnDllRegisterServer)();
        else
            hr = HRESULT_FROM_WIN32(GetLastError());

        FreeLibrary(hProxyDll);
    }
    else
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
    }

    return hr;
}



//+---------------------------------------------------------------------------
//
//  Function:   UnregisterLocalServer
//
//  Synopsis:   Removes the registry key for a local server.
//
//  Parameters: rclsid - Supplies the class ID of the local server.
//
//----------------------------------------------------------------------------
HRESULT UnregisterLocalServer(REFCLSID rclsid)
{
    HRESULT hr;
    HKEY hKeyCLSID;
    HKEY hKeyClassID;
    long error;
    char szClassID[39];

    //open the CLSID key
    error = RegOpenKeyExA(
        HKEY_CLASSES_ROOT, 
        "CLSID",
        0, 
        KEY_ALL_ACCESS,
        &hKeyCLSID);

    if(!error)
    { 
    //convert the class ID to a registry key name.
    sprintf(szClassID, "{%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
            rclsid.Data1, rclsid.Data2, rclsid.Data3,
            rclsid.Data4[0], rclsid.Data4[1],
            rclsid.Data4[2], rclsid.Data4[3],
            rclsid.Data4[4], rclsid.Data4[5],
            rclsid.Data4[6], rclsid.Data4[7]);

        //open registry key for class ID string
        error = RegOpenKeyExA(
            hKeyCLSID, 
            szClassID,
            0, 
            KEY_ALL_ACCESS,
            &hKeyClassID);

        if(!error)
        {
            //delete LocalServer32 key. 
            error = RegDeleteKeyA(hKeyClassID, "LocalServer32");
            RegCloseKey(hKeyClassID);          
        }

        error = RegDeleteKeyA(hKeyCLSID, szClassID);
        RegCloseKey(hKeyCLSID);
    }

    if(!error)
        hr = S_OK;
    else
        hr = HRESULT_FROM_WIN32(error);

    return hr;
}


//+---------------------------------------------------------------------------
//
//  Function:   UnregisterProxyDll
//
//  Synopsis:   Removes registry entries for the interfaces contained in a 
//              proxy DLL.  
//
//  Parameters: pszProxyDll - Supplies the filename of the proxy DLL.
//
//  Notes:      UnregisterProxyDll calls the DllUnregisterServer function 
//              exported from the proxy DLL.
//
//----------------------------------------------------------------------------
HRESULT UnregisterProxyDll(const char *pszProxyDll)
{
    HRESULT hr;
    HINSTANCE hProxyDll;
    HRESULT (STDAPICALLTYPE *pfnDllUnregisterServer)();
    
    hProxyDll = LoadLibraryA(pszProxyDll);
    
    if(hProxyDll != 0)
    {
        pfnDllUnregisterServer = (HRESULT (STDAPICALLTYPE *)())
            GetProcAddress(hProxyDll, "DllUnregisterServer");
        
        if(pfnDllUnregisterServer != 0)
            hr = (*pfnDllUnregisterServer)();
        else
            hr = HRESULT_FROM_WIN32(GetLastError());
    
        FreeLibrary(hProxyDll);
    }
    else
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
    }

    return hr;
}

