// comfns.cpp
//
// COM support functions

#include "stdafx.h"
#include "comfns.h"

STDAPI vbCoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter,
		    DWORD dwClsContext, REFIID riid, LPVOID FAR* ppv)
{
    // say what we're about to call
    dprintf2("CoCreateInstance()");
    
    // maybe print the arguments
    dprintf3("  CLSID %8.8lX-%4.4X-%4.4X-%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X",
             rclsid.Data1,
             rclsid.Data2,
             rclsid.Data3,
             rclsid.Data4[0], rclsid.Data4[1], rclsid.Data4[2], rclsid.Data4[3],
             rclsid.Data4[4], rclsid.Data4[5], rclsid.Data4[6], rclsid.Data4[7]);
    dprintf3("  pUnkOuter %8.8lXH", pUnkOuter);
    dprintf3("  dwClsContext %8.8lXH", dwClsContext);
    dprintf3("  IID %8.8lX-%4.4X-%4.4X-%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X",
             riid.Data1,
             riid.Data2,
             riid.Data3,
             riid.Data4[0], riid.Data4[1], riid.Data4[2], riid.Data4[3],
             riid.Data4[4], riid.Data4[5], riid.Data4[6], riid.Data4[7]);
    dprintf3("  ppv %8.8lXH", ppv);

    // Call the function
    HRESULT hr = CoCreateInstance(rclsid, pUnkOuter, dwClsContext, riid, ppv);
    
    // If it failed, print a message
    if (FAILED(hr)) {
        dprintf1("CoCreateInstance failed: %8.8lXH", hr);
    }

    // return the result
    return hr;
}

//////////////////////////////////////////////////////////////////////////
// Local COM support functions

// Provide QueryInterface for an IUnknown pointer
STDAPI comQueryInterface(IUnknown* punkObject, IID& riid, void** ppvObj)
{
    dprintf2("comQueryInterface()");
    *ppvObj = NULL;

    if (!punkObject || !ppvObj) {
        dprintf1("Invalid args");
        return E_INVALIDARG;
    }

    // show the args
    dprintf3("  punkObject %8.8lXH", punkObject);
    dprintf3("  IID %8.8lX-%4.4X-%4.4X-%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X",
             riid.Data1,
             riid.Data2,
             riid.Data3,
             riid.Data4[0], riid.Data4[1], riid.Data4[2], riid.Data4[3],
             riid.Data4[4], riid.Data4[5], riid.Data4[6], riid.Data4[7]);
    dprintf3("  ppvObj %8.8lXH", ppvObj);

    // Make the call
    HRESULT hr = punkObject->QueryInterface(riid, ppvObj);
    if (FAILED(hr)) {
        dprintf1("comQueryInterface failed: %8.8lXH", hr);
    }

    // return the result
    return hr;
}

// Support for AddRef and Release
STDAPI comAddRef(IUnknown* punkObject)
{
    dprintf2("comAddRef");

    if (!punkObject) {
        dprintf1("Invalid args");
        return E_INVALIDARG;
    }

    punkObject->AddRef();
    return NOERROR;
}

STDAPI comRelease(IUnknown* punkObject)
{
    dprintf2("comRelease");

    if (!punkObject) {
        dprintf1("Invalid args");
        return E_INVALIDARG;
    }

    punkObject->Release();
    return NOERROR;
}


// Provide a way to call a mmber through the object's vtable
// Note that we are forced to define a whole load of function types
// here with fixed argumnets to avoid using varargs which would cause
// the compiler to ignore the __stdcall modifier and use __cdecl instead

typedef HRESULT (__stdcall METHOD0)(IUnknown* pInterface);
typedef HRESULT (__stdcall METHOD1)(IUnknown* pInterface, DWORD dwArg1);
typedef HRESULT (__stdcall METHOD2)(IUnknown* pInterface, DWORD dwArg1, DWORD dwArg2);
typedef HRESULT (__stdcall METHOD3)(IUnknown* pInterface, DWORD dwArg1, DWORD dwArg2, DWORD dwArg3);
typedef METHOD0* PMETHOD;
typedef PMETHOD* PVTABLE;
typedef PVTABLE* POBJIFACE;

STDAPI comCallStdMember0(IUnknown* pInterface, DWORD dwIndex)
{
    dprintf2("comCallMember0");

    if (!pInterface) {
        dprintf1("Invalid args");
        return E_INVALIDARG;
    }

    dprintf3("  pInterface %8.8lHX", pInterface);
    dprintf3("  dwIndex %8.8lXH", dwIndex);

    POBJIFACE pObjIface = (POBJIFACE)pInterface;
    PVTABLE pVtable = *pObjIface;
    METHOD0* pMethod = (METHOD0*)pVtable[dwIndex];
    HRESULT hr = pMethod(pInterface);
    if (FAILED(hr)) {
        dprintf1("comCallStdMember0 failed: %8.8lXH", hr);
    }
    return hr;
}

STDAPI comCallStdMember1(IUnknown* pInterface, DWORD dwIndex, DWORD dwArg1)
{
    dprintf2("comCallStdMember1");

    if (!pInterface) {
        dprintf1("Invalid args");
        return E_INVALIDARG;
    }

    dprintf3("  pInterface %8.8lHX", pInterface);
    dprintf3("  dwIndex %8.8lXH", dwIndex);
    dprintf3("  dwArg1 %8.8lXH", dwArg1);

    POBJIFACE pObjIface = (POBJIFACE)pInterface;
    PVTABLE pVtable = *pObjIface;
    METHOD1* pMethod = (METHOD1*)pVtable[dwIndex];
    HRESULT hr = pMethod(pInterface, dwArg1);
    if (FAILED(hr)) {
        dprintf1("comCallStdMember1 failed: %8.8lXH", hr);
    }
    return hr;
}

STDAPI comCallStdMember2(IUnknown* pInterface, DWORD dwIndex, DWORD dwArg1,
                         DWORD dwArg2)
{
    dprintf2("comCallStdMember2");

    if (!pInterface) {
        dprintf1("Invalid args");
        return E_INVALIDARG;
    }

    dprintf3("  pInterface %8.8lHX", pInterface);
    dprintf3("  dwIndex %8.8lXH", dwIndex);
    dprintf3("  dwArg1 %8.8lXH", dwArg1);
    dprintf3("  dwArg2 %8.8lXH", dwArg2);

    POBJIFACE pObjIface = (POBJIFACE)pInterface;
    PVTABLE pVtable = *pObjIface;
    METHOD2* pMethod = (METHOD2*)pVtable[dwIndex];
    HRESULT hr = pMethod(pInterface, dwArg1, dwArg2);
    if (FAILED(hr)) {
        dprintf1("comCallStdMember2 failed: %8.8lXH", hr);
    }
    return hr;
}

STDAPI comCallStdMember3(IUnknown* pInterface, DWORD dwIndex, DWORD dwArg1,
                         DWORD dwArg2, DWORD dwArg3)
{
    dprintf2("comCallStdMember3");

    if (!pInterface) {
        dprintf1("Invalid args");
        return E_INVALIDARG;
    }

    dprintf3("  pInterface %8.8lXH", pInterface);
    dprintf3("  dwIndex %8.8lXH", dwIndex);
    dprintf3("  dwArg1 %8.8lXH", dwArg1);
    dprintf3("  dwArg2 %8.8lXH", dwArg2);
    dprintf3("  dwArg3 %8.8lXH", dwArg3);

    POBJIFACE pObjIface = (POBJIFACE)pInterface;
    PVTABLE pVtable = *pObjIface;
    METHOD3* pMethod = (METHOD3*)pVtable[dwIndex];
    HRESULT hr = pMethod(pInterface, dwArg1, dwArg2, dwArg3);
    if (FAILED(hr)) {
        dprintf1("comCallStdMember3 failed: %8.8lXH", hr);
    }
    return hr;
}
