// --convdllc.h----------------------------------------------------------------
//
// Conversion DLL cache object header file.
//
// Copyright (C) Microsoft Corp., 1986-1996.  All rights reserved.
//
// ----------------------------------------------------------------------------

#ifndef _CONVDLLC_H
#define _CONVDLLC_H

//$--CDllCache-----------------------------------------------------------------
//
// Object to maintain cache of most frequently used conversion
// DLLs
//
//-----------------------------------------------------------------------------

// Constants

// maximum number of cached DLLs maintained
const UINT nCachedDlls  =   1024;

class CDllCache
{
public:

    CDllCache();        // constructor
    ~CDllCache();       // destructor

    // Loads the DLL and saves in the cache
    HRESULT HrAdd(
        IN LPWSTR lpwszDllName);    // name of DLL to load and add

    // Finds handle of DLL in the cache
    HRESULT HrFind(
        IN LPWSTR lpwszDllName,     // name of DLL to find
        OUT HINSTANCE * phInst);    // pointer to DLL instance handle

private:

    // structure for cached DLL entries
    struct SDllCache
    {
        WCHAR lpwszName[MAX_PATH + 1];  // DLL name
        HINSTANCE   hInst;      // DLL instance handle
    };

    // array of pointers to cached DLLs
    SDllCache * m_rgSDllCache[nCachedDlls];

};

#endif  // _CONVDLLC_H
