/*
 * IMSGFILT.H
 *
 * Definitions of a template IMessageFilter object.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IMSGFILT_H_
#define _IMSGFILT_H_

#include <inole.h>

class CMessageFilter;
typedef class CMessageFilter *PCMessageFilter;

class CMessageFilter : public IMessageFilter
    {
    protected:
        ULONG           m_cRef;      //Object reference count

    public:
        CMessageFilter(void);
        ~CMessageFilter(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP_(DWORD) HandleInComingCall(DWORD, HTASK
            , DWORD, LPINTERFACEINFO);
        STDMETHODIMP_(DWORD) RetryRejectedCall(HTASK, DWORD, DWORD);
        STDMETHODIMP_(DWORD) MessagePending(HTASK, DWORD, DWORD);
    };


#endif //_IMSGFILT_H_
