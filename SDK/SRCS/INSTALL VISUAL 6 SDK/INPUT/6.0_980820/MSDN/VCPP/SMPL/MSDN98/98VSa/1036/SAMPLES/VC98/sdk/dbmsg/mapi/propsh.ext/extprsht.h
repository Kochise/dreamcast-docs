///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      EXTPRSHT.H
//
//  Description
//      Interface Methods are declared in this file for extprsht.cpp
//
//  Author
//      Gary Peluso
//
//  Revision: 1.00
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1992-1995 Microsoft Corporation. All rights reserved.
//
#ifndef __EXTPRSHT_H__
#define __EXTPRSHT_H__

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

extern "C" LPEXCHEXT CALLBACK ExchEntryPoint(void);

BOOL CALLBACK SummaryPageDlgProc(HWND hDlg, UINT uMsg, 
        WPARAM wParam, LPARAM lParam);
void ErrorMessageBox(HWND hWnd, HRESULT hr, 
        LPSTR szFunction, LPSTR szMessage);
BOOL GetNamedIDs(LPMESSAGE pMessage);
BOOL GetSummarySheetInfo(LPMESSAGE pMessage);
BOOL ValidDocObject(LPMAPIPROP pObject);
LPSTR GetFileTimeString(FILETIME * pft);

///////////////////////////////////////////////////////////////////////////////
//    Office document summary sheet information data
//

extern LPSPropValue pSummaryProps;
extern LPSTR szDocComments;
extern LPSTR szDocApplication;
extern LPSTR szDocTitle;
extern LPSTR szDocSubject;
extern LPSTR szDocAuthor;
extern SLPSTRArray mvszKeywords;
extern LPSTR szDocKeywords;   
extern LPSTR szDocLastSaved;
extern LPSTR szDocEditTime;
extern LPSTR szDocCategory;
extern LPSTR szDocCompany;


///////////////////////////////////////////////////////////////////////////////
//   Other global data

extern BOOL bBusy;

///////////////////////////////////////////////////////////////////////////////
//    forward declarations
//
class MyExchExt;
class MyExchExtPropertySheets;

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

#endif // __EXTPRSHT_H__
