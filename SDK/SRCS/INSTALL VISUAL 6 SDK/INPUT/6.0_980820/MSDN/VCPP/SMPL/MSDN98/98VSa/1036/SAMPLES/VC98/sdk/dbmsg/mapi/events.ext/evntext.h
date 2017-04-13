///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      EVNTEXT.H
//
//  Description
//      Interface Methods are declared in this file for evntext.cpp
//
//  Author
//      Gary Peluso
//
//  Revision: 1.00
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1992-1995 Microsoft Corporation. All rights reserved.
//
#ifndef __EVNTEXT_H__
#define __EVNTEXT_H__

#include <WINDOWS.H> 
#include <COMMCTRL.H>
#include <MAPIX.H>
#include <MAPIUTIL.H>
#include <MAPIFORM.H>
#include <EXCHEXT.H>

#include "RESOURCE.H"


///////////////////////////////////////////////////////////////////////////////
//    Prototypes
//

extern "C"
{
 LPEXCHEXT CALLBACK ExchEntryPoint(void);
}

void ErrorMessageBox(HWND hWnd, HRESULT hr, 
        LPSTR szFunction, LPSTR szMessage);
HRESULT CalcULONGCheckSum(LPMESSAGE pMessage, ULONG *pulCheckSum);
BOOL CALLBACK SignatureOptionsDlgProc(HWND hDlg, UINT uMsg, 
        WPARAM wParam, LPARAM lParam);

///////////////////////////////////////////////////////////////////////////////
//    Global Data Declarations
//
extern BOOL bSignatureOn;   // defined in EVNTEXT.CPP



///////////////////////////////////////////////////////////////////////////////
//    forward declarations
//
class MyExchExt;
class MyExchExtPropertySheets;
class MyExchExtMessageEvents;

class MyExchExt : public IExchExt
{
 
 public:
    MyExchExt(); 
    STDMETHODIMP QueryInterface
                    (REFIID                     riid,
                     LPVOID *                   ppvObj);
    inline STDMETHODIMP_(ULONG) AddRef
                    () { ++m_cRef; return m_cRef; };
    STDMETHODIMP_(ULONG) Release(); 
    STDMETHODIMP Install (LPEXCHEXTCALLBACK pmecb, 
                        ULONG mecontext, ULONG ulFlags);
    
 private:
    ULONG m_cRef;
    UINT  m_context;
    MyExchExtPropertySheets * m_pExchExtPropertySheets;
    MyExchExtMessageEvents * m_pExchExtMessageEvents;

};

class MyExchExtPropertySheets : public IExchExtPropertySheets
{
 public:
    MyExchExtPropertySheets (LPUNKNOWN pParentInterface) { 
    m_pExchExt = pParentInterface;
    m_cRef = 0; 
    };

    
    STDMETHODIMP QueryInterface
                    (REFIID                     riid,
                     LPVOID *                   ppvObj);
    inline STDMETHODIMP_(ULONG) AddRef
                    () { ++m_cRef; return m_cRef; };
    inline STDMETHODIMP_(ULONG) Release
                    () { ULONG ulCount = --m_cRef;
                         if (!ulCount) { delete this; }
                         return ulCount;};

    STDMETHODIMP_ (ULONG) GetMaxPageCount(ULONG ulFlags);          
    STDMETHODIMP  GetPages(LPEXCHEXTCALLBACK peecb,
                          ULONG ulFlags, LPPROPSHEETPAGE ppsp, ULONG FAR * pcpsp);          
    STDMETHODIMP_ (VOID) FreePages(LPPROPSHEETPAGE ppsp, ULONG ulFlags, 
                                         ULONG cpsp);          

 private:
    ULONG m_cRef;
    LPUNKNOWN m_pExchExt;
};

class MyExchExtMessageEvents : public IExchExtMessageEvents
{
 public:
    MyExchExtMessageEvents (LPUNKNOWN pParentInterface) { 
    m_pExchExt = pParentInterface;
    m_cRef = 0; 
    m_bInSubmitState = FALSE;
    };

    STDMETHODIMP QueryInterface
                    (REFIID                     riid,
                     LPVOID *                   ppvObj);
    inline STDMETHODIMP_(ULONG) AddRef
                    () { ++m_cRef; return m_cRef; };
    inline STDMETHODIMP_(ULONG) Release
                    () { ULONG ulCount = --m_cRef;
                         if (!ulCount) { delete this; }
                         return ulCount;};

    STDMETHODIMP OnRead(LPEXCHEXTCALLBACK lpeecb);
    STDMETHODIMP OnReadComplete(LPEXCHEXTCALLBACK lpeecb, ULONG ulFlags);
    STDMETHODIMP OnWrite(LPEXCHEXTCALLBACK lpeecb);
    STDMETHODIMP OnWriteComplete(LPEXCHEXTCALLBACK lpeecb, ULONG ulFlags);
    STDMETHODIMP OnCheckNames(LPEXCHEXTCALLBACK lpeecb);
    STDMETHODIMP OnCheckNamesComplete(LPEXCHEXTCALLBACK lpeecb, ULONG ulFlags);
    STDMETHODIMP OnSubmit(LPEXCHEXTCALLBACK lpeecb);
    STDMETHODIMP_ (VOID)OnSubmitComplete(LPEXCHEXTCALLBACK lpeecb, ULONG ulFlags);


 private:
    ULONG   m_cRef;
    HRESULT m_hrOnReadComplete;
    BOOL    m_bInSubmitState;
    LPUNKNOWN m_pExchExt;

};


#endif // __EVNTEXT_H__
