#include <accctrl.h>

#ifndef __IAccessControl_INTERFACE_DEFINED__
#define __IAccessControl_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: __MIDL__intf_0077
 * at Tue Oct 29 15:38:21 1996
 * using MIDL 3.00.44
 ****************************************/
/* [local] */


typedef /* [allocate] */ PACTRL_ACCESSW PACTRL_ACCESSW_ALLOCATE_ALL_NODES;

typedef /* [allocate] */ PACTRL_AUDITW PACTRL_AUDITW_ALLOCATE_ALL_NODES;





/****************************************
 * Generated header for interface: IAccessControl
 * at Tue Oct 29 15:38:21 1996
 * using MIDL 3.00.44
 ****************************************/
/* [unique][uuid][object] */



EXTERN_C const IID IID_IAccessControl;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface IAccessControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GrantAccessRights(
            /* [in] */ PACTRL_ACCESSW pAccessList) = 0;

        virtual HRESULT STDMETHODCALLTYPE SetAccessRights(
            /* [in] */ PACTRL_ACCESSW pAccessList) = 0;

        virtual HRESULT STDMETHODCALLTYPE SetOwner(
            /* [in] */ PTRUSTEEW pOwner,
            /* [in] */ PTRUSTEEW pGroup) = 0;

        virtual HRESULT STDMETHODCALLTYPE RevokeAccessRights(
            /* [in] */ LPWSTR lpProperty,
            /* [in] */ ULONG cTrustees,
            /* [size_is][in] */ TRUSTEEW __RPC_FAR prgTrustees[  ]) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetAllAccessRights(
            /* [in] */ LPWSTR lpProperty,
            /* [out] */ PACTRL_ACCESSW_ALLOCATE_ALL_NODES __RPC_FAR *ppAccessList,
            /* [out] */ PTRUSTEEW __RPC_FAR *ppOwner,
            /* [out] */ PTRUSTEEW __RPC_FAR *ppGroup) = 0;

        virtual HRESULT STDMETHODCALLTYPE IsAccessAllowed(
            /* [in] */ PTRUSTEEW pTrustee,
            /* [in] */ LPWSTR lpProperty,
            /* [in] */ ACCESS_RIGHTS AccessRights,
            /* [out] */ BOOL __RPC_FAR *pfAccessAllowed) = 0;

    };

#else   /* C style interface */

    typedef struct IAccessControlVtbl
    {
        BEGIN_INTERFACE

        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
            IAccessControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
            IAccessControl __RPC_FAR * This);

        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
            IAccessControl __RPC_FAR * This);

        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GrantAccessRights )(
            IAccessControl __RPC_FAR * This,
            /* [in] */ PACTRL_ACCESSW pAccessList);

        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAccessRights )(
            IAccessControl __RPC_FAR * This,
            /* [in] */ PACTRL_ACCESSW pAccessList);

        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOwner )(
            IAccessControl __RPC_FAR * This,
            /* [in] */ PTRUSTEEW pOwner,
            /* [in] */ PTRUSTEEW pGroup);

        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RevokeAccessRights )(
            IAccessControl __RPC_FAR * This,
            /* [in] */ LPWSTR lpProperty,
            /* [in] */ ULONG cTrustees,
            /* [size_is][in] */ TRUSTEEW __RPC_FAR prgTrustees[  ]);

        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAllAccessRights )(
            IAccessControl __RPC_FAR * This,
            /* [in] */ LPWSTR lpProperty,
            /* [out] */ PACTRL_ACCESSW_ALLOCATE_ALL_NODES __RPC_FAR *ppAccessList,
            /* [out] */ PTRUSTEEW __RPC_FAR *ppOwner,
            /* [out] */ PTRUSTEEW __RPC_FAR *ppGroup);

        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsAccessAllowed )(
            IAccessControl __RPC_FAR * This,
            /* [in] */ PTRUSTEEW pTrustee,
            /* [in] */ LPWSTR lpProperty,
            /* [in] */ ACCESS_RIGHTS AccessRights,
            /* [out] */ BOOL __RPC_FAR *pfAccessAllowed);

        END_INTERFACE
    } IAccessControlVtbl;

    interface IAccessControl
    {
        CONST_VTBL struct IAccessControlVtbl __RPC_FAR *lpVtbl;
    };



#ifdef COBJMACROS


#define IAccessControl_QueryInterface(This,riid,ppvObject)      \
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAccessControl_AddRef(This)     \
    (This)->lpVtbl -> AddRef(This)

#define IAccessControl_Release(This)    \
    (This)->lpVtbl -> Release(This)


#define IAccessControl_GrantAccessRights(This,pAccessList)      \
    (This)->lpVtbl -> GrantAccessRights(This,pAccessList)

#define IAccessControl_SetAccessRights(This,pAccessList)        \
    (This)->lpVtbl -> SetAccessRights(This,pAccessList)

#define IAccessControl_SetOwner(This,pOwner,pGroup)     \
    (This)->lpVtbl -> SetOwner(This,pOwner,pGroup)

#define IAccessControl_RevokeAccessRights(This,lpProperty,cTrustees,prgTrustees)        \
    (This)->lpVtbl -> RevokeAccessRights(This,lpProperty,cTrustees,prgTrustees)

#define IAccessControl_GetAllAccessRights(This,lpProperty,ppAccessList,ppOwner,ppGroup) \
    (This)->lpVtbl -> GetAllAccessRights(This,lpProperty,ppAccessList,ppOwner,ppGroup)

#define IAccessControl_IsAccessAllowed(This,pTrustee,lpProperty,AccessRights,pfAccessAllowed)   \
    (This)->lpVtbl -> IsAccessAllowed(This,pTrustee,lpProperty,AccessRights,pfAccessAllowed)

#endif /* COBJMACROS */


#endif  /* C style interface */



HRESULT STDMETHODCALLTYPE IAccessControl_GrantAccessRights_Proxy(
    IAccessControl __RPC_FAR * This,
    /* [in] */ PACTRL_ACCESSW pAccessList);


void __RPC_STUB IAccessControl_GrantAccessRights_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAccessControl_SetAccessRights_Proxy(
    IAccessControl __RPC_FAR * This,
    /* [in] */ PACTRL_ACCESSW pAccessList);


void __RPC_STUB IAccessControl_SetAccessRights_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAccessControl_SetOwner_Proxy(
    IAccessControl __RPC_FAR * This,
    /* [in] */ PTRUSTEEW pOwner,
    /* [in] */ PTRUSTEEW pGroup);


void __RPC_STUB IAccessControl_SetOwner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAccessControl_RevokeAccessRights_Proxy(
    IAccessControl __RPC_FAR * This,
    /* [in] */ LPWSTR lpProperty,
    /* [in] */ ULONG cTrustees,
    /* [size_is][in] */ TRUSTEEW __RPC_FAR prgTrustees[  ]);


void __RPC_STUB IAccessControl_RevokeAccessRights_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAccessControl_GetAllAccessRights_Proxy(
    IAccessControl __RPC_FAR * This,
    /* [in] */ LPWSTR lpProperty,
    /* [out] */ PACTRL_ACCESSW_ALLOCATE_ALL_NODES __RPC_FAR *ppAccessList,
    /* [out] */ PTRUSTEEW __RPC_FAR *ppOwner,
    /* [out] */ PTRUSTEEW __RPC_FAR *ppGroup);


void __RPC_STUB IAccessControl_GetAllAccessRights_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAccessControl_IsAccessAllowed_Proxy(
    IAccessControl __RPC_FAR * This,
    /* [in] */ PTRUSTEEW pTrustee,
    /* [in] */ LPWSTR lpProperty,
    /* [in] */ ACCESS_RIGHTS AccessRights,
    /* [out] */ BOOL __RPC_FAR *pfAccessAllowed);


void __RPC_STUB IAccessControl_IsAccessAllowed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif  /* __IAccessControl_INTERFACE_DEFINED__ */

