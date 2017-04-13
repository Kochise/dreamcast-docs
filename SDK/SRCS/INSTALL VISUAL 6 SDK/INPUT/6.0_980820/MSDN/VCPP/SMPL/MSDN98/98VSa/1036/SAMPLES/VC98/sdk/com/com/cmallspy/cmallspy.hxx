//+---------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1993 - 1996.
//
//  File:       cmallspy.hxx
//
//  Contents:   CMallocSpy definitions
//
//----------------------------------------------------------------------




class CMallocSpy : public IMallocSpy
{
public:
    CMallocSpy(void);
    ~CMallocSpy(void);

    // IUnknown methods
    STDMETHOD(QueryInterface) (REFIID riid, LPVOID *ppUnk);
    STDMETHOD_(ULONG, AddRef) (void);
    STDMETHOD_(ULONG, Release) (void);


    // IMallocSpy methods
    STDMETHOD_(ULONG, PreAlloc) (ULONG cbRequest);
    STDMETHOD_(void *, PostAlloc) (void *pActual);

    STDMETHOD_(void *, PreFree) (void *pRequest, BOOL fSpyed);
    STDMETHOD_(void, PostFree) (BOOL fSpyed);

    STDMETHOD_(ULONG, PreRealloc) (void *pRequest, ULONG cbRequest,
                                   void **ppNewRequest, BOOL fSpyed);
    STDMETHOD_(void *, PostRealloc) (void *pActual, BOOL fSpyed);

    STDMETHOD_(void *, PreGetSize) (void *pRequest, BOOL fSpyed);
    STDMETHOD_(ULONG, PostGetSize) (ULONG cbActual, BOOL fSpyed);

    STDMETHOD_(void *, PreDidAlloc) (void *pRequest, BOOL fSpyed);
    STDMETHOD_(BOOL, PostDidAlloc) (void *pRequest, BOOL fSpyed, BOOL fActual);

    STDMETHOD_(void, PreHeapMinimize) (void);
    STDMETHOD_(void, PostHeapMinimize) (void);


private:
    ULONG    m_cRef;
    ULONG    m_cbRequest;

};
