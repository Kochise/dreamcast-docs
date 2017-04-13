/*
 * LNKASSIS.H
 * Links Assistant Chapter 20
 *
 * Classes that implement the LinksAssistant object
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _LNKASSIS_H_
#define _LNKASSIS_H_

#define INC_OLEUI
#define CHAPTER20
#include <inole.h>

#define CCHPATHMAX  260


class CLinks : public IOleUILinkContainer
    {
    protected:
        ULONG           m_cRef;
        PFNDESTROYED    m_pfnDestroy;

    protected:
        //Internal functions for implementing IOleUILinkContainer
        BOOL ValidateLinkSource(LPTSTR, ULONG *, LPMONIKER *
            , LPCLSID);
        BOOL CreateNewSourceMoniker(LPTSTR, ULONG, LPMONIKER *);
        UINT CchFilePrefix(LPMONIKER);

    public:
        CLinks(PFNDESTROYED);
        ~CLinks(void);

        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        /*
         * The dwLink parameter to all of these functions is assumed
         * to be an IOleLink pointer for the object in question
         * (GetNextLink is not implelemented in us).  We can
         * QueryInterface IOleLink for anything else we need.
         */

        STDMETHODIMP_(DWORD) GetNextLink(DWORD);
        STDMETHODIMP         SetLinkUpdateOptions(DWORD, DWORD);
        STDMETHODIMP         GetLinkUpdateOptions(DWORD, LPDWORD);
        STDMETHODIMP         SetLinkSource(DWORD, LPTSTR, ULONG
                                 , ULONG *, BOOL);
        STDMETHODIMP         GetLinkSource(DWORD, LPTSTR *, ULONG *
                                 , LPTSTR *, LPTSTR *, BOOL *, BOOL *);
        STDMETHODIMP         OpenLinkSource(DWORD);
        STDMETHODIMP         UpdateLink(DWORD, BOOL, BOOL);
        STDMETHODIMP         CancelLink(DWORD);
    };

typedef CLinks *PCLinks;


#endif //_LNKASSIS_H_
