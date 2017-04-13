/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CDispMgr.c

Abstract:

    Dispatch Manager implementation

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop

DISPID
CDispatchMgr::getDISPID(DISPID InputDispId)
{
    return(InputDispId & 0x0000FFFF);
}

DISPID
CDispatchMgr::getTypeinfoID(DISPID InputDispId)
{
    return((InputDispId & 0x7fff0000) >> 16);
}

void *
CDispatchMgr::getInterfacePtr(DISPID TypeinfoID
                                  )
{
    PTYPEINFOENTRY pTypeInfoEntry = NULL;
    pTypeInfoEntry = _pTypeInfoEntry;
    while (pTypeInfoEntry) {
        if (pTypeInfoEntry->TypeInfoId == TypeinfoID) {
            return(pTypeInfoEntry->pInterfacePointer);
        }
        pTypeInfoEntry = pTypeInfoEntry->pNext;
    }
    return(NULL);
}

PTYPEINFOENTRY
CDispatchMgr::FindTypeInfoEntry(LONG TypeInfoId)
{
    PTYPEINFOENTRY pTypeInfoEntry;

    pTypeInfoEntry = _pTypeInfoEntry;
    while (pTypeInfoEntry) {
        if (pTypeInfoEntry->TypeInfoId == TypeInfoId) {
            return(pTypeInfoEntry);
        }
        pTypeInfoEntry = pTypeInfoEntry->pNext;
    }
    return(NULL);
}



HRESULT
CDispatchMgr::AddTypeInfo(void FAR *ptypeinfo,
                               void * pIntfptr)
{
    PTYPEINFOENTRY pTypeInfoEntry = NULL;
    HRESULT hr;

    if (pTypeInfoEntry =FindTypeInfo(ptypeinfo)) {
        return(E_FAIL);
    }
    pTypeInfoEntry = (PTYPEINFOENTRY)LocalAlloc(LPTR,sizeof(TYPEINFOENTRY));
    if (!pTypeInfoEntry) {
        hr = E_OUTOFMEMORY;
        BAIL_IF_ERROR(hr);
    }

    pTypeInfoEntry->ptypeinfo = ptypeinfo;
    pTypeInfoEntry->TypeInfoId = gentypeinfoid();
    pTypeInfoEntry->pInterfacePointer = pIntfptr;

    pTypeInfoEntry->pNext = _pTypeInfoEntry;
    _pTypeInfoEntry = pTypeInfoEntry;

    RRETURN(S_OK);

cleanup:
    RRETURN(hr);
}

STDMETHODIMP
CDispatchMgr::GetTypeInfoCount(unsigned int FAR* pctinfo)
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CDispatchMgr::GetTypeInfo(unsigned int itinfo, LCID lcid,
        ITypeInfo FAR* FAR* pptinfo)
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CDispatchMgr::GetIDsOfNames(REFIID iid, LPWSTR FAR* rgszNames,
        unsigned int cNames, LCID lcid, DISPID FAR* rgdispid)
{
    PTYPEINFOENTRY pTypeInfo = NULL;
    HRESULT hr;

    pTypeInfo = _pTypeInfoEntry;
    while (pTypeInfo) {
        hr = DispGetIDsOfNames(((ITypeInfo *)pTypeInfo->ptypeinfo),
                                rgszNames,
                                cNames,
                                rgdispid
                                );
        if (SUCCEEDED(hr)) {
            generate_newids(pTypeInfo->TypeInfoId,
                            rgdispid,
                            cNames
                            );
            RRETURN(hr);
        }
        pTypeInfo = pTypeInfo->pNext;
    }
    RRETURN(E_FAIL);
}

STDMETHODIMP
CDispatchMgr::Invoke(DISPID dispidMember, REFIID iid, LCID lcid,
        unsigned short wFlags, DISPPARAMS FAR* pdispparams,
        VARIANT FAR* pvarResult, EXCEPINFO FAR* pexcepinfo,
        unsigned int FAR* puArgErr)
{
        RRETURN(TypeInfoInvoke(dispidMember,
                               iid,
                               lcid,
                               wFlags,
                               pdispparams,
                               pvarResult,
                               pexcepinfo,
                               puArgErr
                               ));
}

void
CDispatchMgr::generate_newids(LONG TypeInfoId,
        DISPID FAR* rgdispid, unsigned int cNames)
{
    unsigned int i = 0;
    for (i = 0; i < cNames; i++ ) {
        rgdispid[i] = (DISPID)(((unsigned int)TypeInfoId << 16) | rgdispid[i]);
    }
}

STDMETHODIMP
CDispatchMgr::TypeInfoInvoke(DISPID dispidMember, REFIID iid, LCID lcid,
        unsigned short wFlags, DISPPARAMS FAR* pdispparams,
        VARIANT FAR* pvarResult, EXCEPINFO FAR* pexcepinfo,
        unsigned int FAR* puArgErr)
{

    void * pInterfacePtr = NULL;
    DISPID dispid;
    DISPID typeinfoid;
    ITypeInfo *pTypeInfo;
    HRESULT hr = S_OK;

    if (dispidMember <= 0) {
        dispid = dispidMember;
        switch (dispid) {
        case -4:
            if (_pDispidNewEnum) {
                pTypeInfo = (ITypeInfo *)_pDispidNewEnum->ptypeinfo;
                pInterfacePtr = _pDispidNewEnum->pInterfacePointer;
                break;

            }else {
                hr = DISP_E_BADINDEX;
                BAIL_IF_ERROR(hr);

            }
            break;

        default:
             hr = DISP_E_BADINDEX;
             BAIL_IF_ERROR(hr);

        }

    }else {
        typeinfoid = getTypeinfoID(dispidMember);
        dispid = getDISPID(dispidMember);
        pInterfacePtr = getInterfacePtr(typeinfoid);
        hr = getTypeInfo(typeinfoid, &pTypeInfo);
        BAIL_IF_ERROR(hr);
    }

    hr = DispInvoke(pInterfacePtr,
                pTypeInfo,
                dispid,
                wFlags,
                pdispparams,
                pvarResult,
                pexcepinfo,
                puArgErr
                );
    return hr;

cleanup:

    RRETURN(hr);
}


HRESULT
CDispatchMgr::getTypeInfo(DISPID typeinfoid, ITypeInfo FAR * FAR * ppTypeInfo)
{
    PTYPEINFOENTRY pTypeInfoEntry;
    pTypeInfoEntry = _pTypeInfoEntry;
    while (pTypeInfoEntry) {
        if (pTypeInfoEntry->TypeInfoId == typeinfoid) {
            *ppTypeInfo = (ITypeInfo FAR *)pTypeInfoEntry->ptypeinfo;
            RRETURN(S_OK);
        }
        pTypeInfoEntry = pTypeInfoEntry->pNext;
    }
    RRETURN(E_FAIL);
}

CDispatchMgr::CDispatchMgr()
{
    _pTypeInfoEntry = NULL;
    _pDispidNewEnum = NULL;
    _dwTypeInfoId = 0;
}

CDispatchMgr::~CDispatchMgr()
{
    PTYPEINFOENTRY pTypeInfoEntry = NULL;
    PTYPEINFOENTRY pTemp = NULL;
    ITypeInfo *pTypeInfo = NULL;

    pTypeInfoEntry = _pTypeInfoEntry;

    while (pTypeInfoEntry) {

        pTemp = pTypeInfoEntry;

        pTypeInfo = (ITypeInfo *)pTypeInfoEntry->ptypeinfo;
        pTypeInfo->Release();

        pTypeInfoEntry = pTemp->pNext;

        LocalFree(pTemp);
    }
}

HRESULT
CDispatchMgr::MarkAsNewEnum(void *pTypeInfo)
{
    PTYPEINFOENTRY pTypeInfoEntry;

    if (!pTypeInfo) {
        RRETURN(E_FAIL);
    }
    if (!(pTypeInfoEntry = FindTypeInfo(pTypeInfo))) {
        RRETURN(E_FAIL);
    }
    _pDispidNewEnum = pTypeInfoEntry;
    RRETURN(S_OK);
}



PTYPEINFOENTRY
CDispatchMgr::FindTypeInfo(void *pTypeInfo)
{
    PTYPEINFOENTRY pTypeInfoEntry;

    pTypeInfoEntry = _pTypeInfoEntry;
    while (pTypeInfoEntry) {
        if (pTypeInfoEntry->ptypeinfo == pTypeInfo) {
            return(pTypeInfoEntry);
        }
        pTypeInfoEntry = pTypeInfoEntry->pNext;
    }
    return(NULL);
}

LONG
CDispatchMgr::gentypeinfoid()
{
    return (_dwTypeInfoId++);
}
