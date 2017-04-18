/////////////////////////////////////////////////////////////
//
// SharedPoint.cpp - Copyright 1996, Don Box
//

#include <windows.h>
#include "sharedpoint.h"

STDMETHODIMP 
CoSharedPoint::Set(long x, long y)
{
    SharedThis pThis(this); // initialize locked pointer to shared state
    pThis->m_x = x;         // copy parameters to shared state
    pThis->m_y = y;
    return NOERROR;
}

STDMETHODIMP 
CoSharedPoint::Get(long FAR* px, long FAR* py)
{
    SharedThis pThis(this); // initialize locked pointer to shared state
    *px = pThis->m_x;       // copy parameters from shared state
    *py = pThis->m_y;
    return NOERROR;
}

STDMETHODIMP 
CoSharedPoint::SetText(LPCSTR lpsz)
{
    SharedThis pThis(this);
    if (strncpy(pThis->m_sz, lpsz, sizeof(pThis->m_sz)))
        return S_OK;
    else
        return E_INVALIDARG;
}

STDMETHODIMP 
CoSharedPoint::GetText(LPSTR lpsz, int cb)
{
    SharedThis pThis(this);
    if (strncpy(lpsz, pThis->m_sz, cb))
        return S_OK;
    else
        return E_INVALIDARG;
}

