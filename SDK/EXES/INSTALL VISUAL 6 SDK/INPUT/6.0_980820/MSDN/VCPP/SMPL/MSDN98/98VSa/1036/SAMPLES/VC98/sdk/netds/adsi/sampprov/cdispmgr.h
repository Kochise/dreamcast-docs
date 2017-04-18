/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CDispMgr.h

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _CDISPMGR_H_
#define _CDISPMGR_H_

typedef struct _typeinfoentry
{
    LONG TypeInfoId;
    void FAR *ptypeinfo;
    void * pInterfacePointer;
    struct _typeinfoentry *pNext;
} TYPEINFOENTRY, *PTYPEINFOENTRY;

class CDispatchMgr;

class CDispatchMgr
{
public:

    DECLARE_IDispatch_METHODS

    CDispatchMgr::CDispatchMgr();

    CDispatchMgr::~CDispatchMgr();

    DISPID
    CDispatchMgr::getDISPID(DISPID InputDispId);

    DISPID
    CDispatchMgr::getTypeinfoID(DISPID InputDispId);

    void *
    CDispatchMgr::getInterfacePtr(DISPID TypeinfoID
                                      );
     void
     CDispatchMgr::generate_newids(LONG TypeInfoId,
             DISPID FAR* rgdispid, unsigned int cNames);

    PTYPEINFOENTRY
    CDispatchMgr::FindTypeInfoEntry(LONG TypeInfoId);

    HRESULT
    CDispatchMgr::AddTypeInfo(void FAR *ptypeinfo, void * pIntfptr);


    STDMETHODIMP
    CDispatchMgr::TypeInfoInvoke(DISPID dispidMember, REFIID iid, LCID lcid,
            unsigned short wFlags, DISPPARAMS FAR* pdispparams,
            VARIANT FAR* pvarResult, EXCEPINFO FAR* pexcepinfo,
            unsigned int FAR* puArgErr);

   HRESULT
   CDispatchMgr::getTypeInfo(DISPID typeinfoid, ITypeInfo FAR * FAR * ppTypeInfo) ;

   HRESULT
   CDispatchMgr::MarkAsNewEnum(void *pTypeInfo);

   PTYPEINFOENTRY
   CDispatchMgr::FindTypeInfo(void *pTypeInfo);

   LONG
   CDispatchMgr::gentypeinfoid();

protected:

    LONG        _dwTypeInfoId;
    PTYPEINFOENTRY _pTypeInfoEntry;
    PTYPEINFOENTRY _pDispidNewEnum;
};

#define BAIL_IF_ERROR(hr) \
        if (FAILED(hr)) {       \
                goto cleanup;   \
        }
#endif
