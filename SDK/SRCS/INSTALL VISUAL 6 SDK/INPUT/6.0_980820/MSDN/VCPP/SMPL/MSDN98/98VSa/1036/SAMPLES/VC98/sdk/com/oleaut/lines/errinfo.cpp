/*************************************************************************
**
**  This is a part of the Microsoft Source Code Samples.
**
**  Copyright (C) 1992-1997 Microsoft Corporation. All rights reserved.
**
**  This source code is only intended as a supplement to Microsoft Development
**  Tools and/or WinHelp documentation.  See these sources for detailed
**  information regarding the Microsoft samples programs.
**
**  OLE Automation Lines Object.
**
**  errinfo.cpp
**
**  CSupportErrorInfo implementation
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
#endif      
#include "lines.h"  

CSupportErrorInfo::CSupportErrorInfo(IUnknown FAR* punkObject, REFIID riid)
{
    m_punkObject = punkObject; 
    m_iid = riid;
}         

STDMETHODIMP
CSupportErrorInfo::QueryInterface(REFIID iid, void FAR* FAR* ppv) 
{   
    return m_punkObject->QueryInterface(iid, ppv);    
}


STDMETHODIMP_(ULONG)
CSupportErrorInfo::AddRef(void)
{
    return m_punkObject->AddRef();
}

STDMETHODIMP_(ULONG)
CSupportErrorInfo::Release(void)
{
    return m_punkObject->Release();
} 

STDMETHODIMP
CSupportErrorInfo::InterfaceSupportsErrorInfo(REFIID riid)  
{
    return (riid == m_iid) ? NOERROR : S_FALSE;
}
