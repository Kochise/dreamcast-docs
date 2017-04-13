/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 02:35:41 1998
 */
/* Compiler settings for browseh.odl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __tlb_h__
#define __tlb_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IArrayDesc_FWD_DEFINED__
#define __IArrayDesc_FWD_DEFINED__
typedef interface IArrayDesc IArrayDesc;
#endif 	/* __IArrayDesc_FWD_DEFINED__ */


#ifndef __ICollection_FWD_DEFINED__
#define __ICollection_FWD_DEFINED__
typedef interface ICollection ICollection;
#endif 	/* __ICollection_FWD_DEFINED__ */


#ifndef __ITypeLibrary_FWD_DEFINED__
#define __ITypeLibrary_FWD_DEFINED__
typedef interface ITypeLibrary ITypeLibrary;
#endif 	/* __ITypeLibrary_FWD_DEFINED__ */


#ifndef __ITypeInformation_FWD_DEFINED__
#define __ITypeInformation_FWD_DEFINED__
typedef interface ITypeInformation ITypeInformation;
#endif 	/* __ITypeInformation_FWD_DEFINED__ */


#ifndef __IBrowseHelper_FWD_DEFINED__
#define __IBrowseHelper_FWD_DEFINED__
typedef interface IBrowseHelper IBrowseHelper;
#endif 	/* __IBrowseHelper_FWD_DEFINED__ */


#ifndef __ITypeDesc_FWD_DEFINED__
#define __ITypeDesc_FWD_DEFINED__
typedef interface ITypeDesc ITypeDesc;
#endif 	/* __ITypeDesc_FWD_DEFINED__ */


#ifndef __IArrayBound_FWD_DEFINED__
#define __IArrayBound_FWD_DEFINED__
typedef interface IArrayBound IArrayBound;
#endif 	/* __IArrayBound_FWD_DEFINED__ */


#ifndef __IInterface_FWD_DEFINED__
#define __IInterface_FWD_DEFINED__
typedef interface IInterface IInterface;
#endif 	/* __IInterface_FWD_DEFINED__ */


#ifndef __IDispinterface_FWD_DEFINED__
#define __IDispinterface_FWD_DEFINED__
typedef interface IDispinterface IDispinterface;
#endif 	/* __IDispinterface_FWD_DEFINED__ */


#ifndef __IModule_FWD_DEFINED__
#define __IModule_FWD_DEFINED__
typedef interface IModule IModule;
#endif 	/* __IModule_FWD_DEFINED__ */


#ifndef __ICoClass_FWD_DEFINED__
#define __ICoClass_FWD_DEFINED__
typedef interface ICoClass ICoClass;
#endif 	/* __ICoClass_FWD_DEFINED__ */


#ifndef __IEnum_FWD_DEFINED__
#define __IEnum_FWD_DEFINED__
typedef interface IEnum IEnum;
#endif 	/* __IEnum_FWD_DEFINED__ */


#ifndef __IStruct_FWD_DEFINED__
#define __IStruct_FWD_DEFINED__
typedef interface IStruct IStruct;
#endif 	/* __IStruct_FWD_DEFINED__ */


#ifndef __IUnion_FWD_DEFINED__
#define __IUnion_FWD_DEFINED__
typedef interface IUnion IUnion;
#endif 	/* __IUnion_FWD_DEFINED__ */


#ifndef __IAlias_FWD_DEFINED__
#define __IAlias_FWD_DEFINED__
typedef interface IAlias IAlias;
#endif 	/* __IAlias_FWD_DEFINED__ */


#ifndef __IFunction_FWD_DEFINED__
#define __IFunction_FWD_DEFINED__
typedef interface IFunction IFunction;
#endif 	/* __IFunction_FWD_DEFINED__ */


#ifndef __IProperty_FWD_DEFINED__
#define __IProperty_FWD_DEFINED__
typedef interface IProperty IProperty;
#endif 	/* __IProperty_FWD_DEFINED__ */


#ifndef __IConstant_FWD_DEFINED__
#define __IConstant_FWD_DEFINED__
typedef interface IConstant IConstant;
#endif 	/* __IConstant_FWD_DEFINED__ */


#ifndef __IParameter_FWD_DEFINED__
#define __IParameter_FWD_DEFINED__
typedef interface IParameter IParameter;
#endif 	/* __IParameter_FWD_DEFINED__ */


#ifndef __BrowseHelper_FWD_DEFINED__
#define __BrowseHelper_FWD_DEFINED__

#ifdef __cplusplus
typedef class BrowseHelper BrowseHelper;
#else
typedef struct BrowseHelper BrowseHelper;
#endif /* __cplusplus */

#endif 	/* __BrowseHelper_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __BrowseHelper_LIBRARY_DEFINED__
#define __BrowseHelper_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: BrowseHelper
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [version][helpstring][uuid] */ 



typedef 
enum __MIDL___MIDL_itf_browseh_0000_0001
    {	TYPE_FUNCTION	= 0,
	TYPE_PROPERTY	= 1,
	TYPE_CONSTANT	= 2,
	TYPE_PARAMETER	= 3
    }	OBJTYPE;


DEFINE_GUID(LIBID_BrowseHelper,0x19FEEEC0,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#ifndef __IArrayDesc_INTERFACE_DEFINED__
#define __IArrayDesc_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IArrayDesc
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_IArrayDesc,0x19FEEED2,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEED2-4104-101B-B826-00DD01103DE1")
    IArrayDesc : public CMyDispatch
    {
    public:
        virtual /* [helpstring][propget] */ ITypeDesc __RPC_FAR *STDMETHODCALLTYPE get_ElementType( void) = 0;
        
        virtual /* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE get_ArrayBounds( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IArrayDescVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IArrayDesc __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IArrayDesc __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IArrayDesc __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IArrayDesc __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IArrayDesc __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IArrayDesc __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IArrayDesc __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            IArrayDesc __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            IArrayDesc __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            IArrayDesc __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            IArrayDesc __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring][propget] */ ITypeDesc __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_ElementType )( 
            IArrayDesc __RPC_FAR * This);
        
        /* [helpstring][propget] */ ICollection __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_ArrayBounds )( 
            IArrayDesc __RPC_FAR * This);
        
        END_INTERFACE
    } IArrayDescVtbl;

    interface IArrayDesc
    {
        CONST_VTBL struct IArrayDescVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IArrayDesc_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define IArrayDesc_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define IArrayDesc_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define IArrayDesc_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define IArrayDesc_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define IArrayDesc_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define IArrayDesc_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define IArrayDesc__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define IArrayDesc__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define IArrayDesc__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define IArrayDesc__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define IArrayDesc_get_ElementType(This)	\
    (This)->lpVtbl -> get_ElementType(This)

#define IArrayDesc_get_ArrayBounds(This)	\
    (This)->lpVtbl -> get_ArrayBounds(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ ITypeDesc __RPC_FAR *STDMETHODCALLTYPE IArrayDesc_get_ElementType_Proxy( 
    IArrayDesc __RPC_FAR * This);


void __RPC_STUB IArrayDesc_get_ElementType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE IArrayDesc_get_ArrayBounds_Proxy( 
    IArrayDesc __RPC_FAR * This);


void __RPC_STUB IArrayDesc_get_ArrayBounds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IArrayDesc_INTERFACE_DEFINED__ */


#ifndef __ICollection_INTERFACE_DEFINED__
#define __ICollection_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICollection
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_ICollection,0x19FEEECC,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEECC-4104-101B-B826-00DD01103DE1")
    ICollection : public CMyDispatch
    {
    public:
        virtual /* [helpstring][propget] */ long STDMETHODCALLTYPE get_Count( void) = 0;
        
        virtual /* [helpstring][id][propget] */ IDispatch __RPC_FAR *STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index) = 0;
        
        virtual /* [id][restricted][propget] */ IUnknown __RPC_FAR *STDMETHODCALLTYPE get__NewEnum( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICollectionVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICollection __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICollection __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICollection __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICollection __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICollection __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICollection __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICollection __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            ICollection __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            ICollection __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            ICollection __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            ICollection __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring][propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICollection __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ IDispatch __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICollection __RPC_FAR * This,
            /* [in] */ long Index);
        
        /* [id][restricted][propget] */ IUnknown __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICollection __RPC_FAR * This);
        
        END_INTERFACE
    } ICollectionVtbl;

    interface ICollection
    {
        CONST_VTBL struct ICollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICollection_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define ICollection_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define ICollection_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define ICollection_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define ICollection_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define ICollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define ICollection_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define ICollection__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define ICollection__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define ICollection__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define ICollection__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define ICollection_get_Count(This)	\
    (This)->lpVtbl -> get_Count(This)

#define ICollection_get_Item(This,Index)	\
    (This)->lpVtbl -> get_Item(This,Index)

#define ICollection_get__NewEnum(This)	\
    (This)->lpVtbl -> get__NewEnum(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ long STDMETHODCALLTYPE ICollection_get_Count_Proxy( 
    ICollection __RPC_FAR * This);


void __RPC_STUB ICollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ IDispatch __RPC_FAR *STDMETHODCALLTYPE ICollection_get_Item_Proxy( 
    ICollection __RPC_FAR * This,
    /* [in] */ long Index);


void __RPC_STUB ICollection_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ IUnknown __RPC_FAR *STDMETHODCALLTYPE ICollection_get__NewEnum_Proxy( 
    ICollection __RPC_FAR * This);


void __RPC_STUB ICollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICollection_INTERFACE_DEFINED__ */


#ifndef __ITypeLibrary_INTERFACE_DEFINED__
#define __ITypeLibrary_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITypeLibrary
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_ITypeLibrary,0x19FEEEC3,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEEC3-4104-101B-B826-00DD01103DE1")
    ITypeLibrary : public CMyDispatch
    {
    public:
        virtual /* [helpstring][propget] */ BSTR STDMETHODCALLTYPE get_Name( void) = 0;
        
        virtual /* [helpstring][propget] */ BSTR STDMETHODCALLTYPE get_Documentation( void) = 0;
        
        virtual /* [helpstring][propget] */ long STDMETHODCALLTYPE get_HelpContext( void) = 0;
        
        virtual /* [helpstring][propget] */ BSTR STDMETHODCALLTYPE get_HelpFile( void) = 0;
        
        virtual /* [helpstring][propget] */ long STDMETHODCALLTYPE get_LocaleID( void) = 0;
        
        virtual /* [helpstring][propget] */ int STDMETHODCALLTYPE get_MajorVersion( void) = 0;
        
        virtual /* [helpstring][propget] */ int STDMETHODCALLTYPE get_MinorVersion( void) = 0;
        
        virtual /* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE get_TypeInfos( void) = 0;
        
        virtual /* [helpstring][propget] */ BSTR STDMETHODCALLTYPE get_GUIDAsString( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITypeLibraryVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITypeLibrary __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITypeLibrary __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITypeLibrary __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITypeLibrary __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITypeLibrary __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITypeLibrary __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITypeLibrary __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            ITypeLibrary __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            ITypeLibrary __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            ITypeLibrary __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            ITypeLibrary __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ITypeLibrary __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Documentation )( 
            ITypeLibrary __RPC_FAR * This);
        
        /* [helpstring][propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContext )( 
            ITypeLibrary __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            ITypeLibrary __RPC_FAR * This);
        
        /* [helpstring][propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_LocaleID )( 
            ITypeLibrary __RPC_FAR * This);
        
        /* [helpstring][propget] */ int ( STDMETHODCALLTYPE __RPC_FAR *get_MajorVersion )( 
            ITypeLibrary __RPC_FAR * This);
        
        /* [helpstring][propget] */ int ( STDMETHODCALLTYPE __RPC_FAR *get_MinorVersion )( 
            ITypeLibrary __RPC_FAR * This);
        
        /* [helpstring][propget] */ ICollection __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_TypeInfos )( 
            ITypeLibrary __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_GUIDAsString )( 
            ITypeLibrary __RPC_FAR * This);
        
        END_INTERFACE
    } ITypeLibraryVtbl;

    interface ITypeLibrary
    {
        CONST_VTBL struct ITypeLibraryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITypeLibrary_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define ITypeLibrary_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define ITypeLibrary_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define ITypeLibrary_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define ITypeLibrary_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define ITypeLibrary_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define ITypeLibrary_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define ITypeLibrary__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define ITypeLibrary__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define ITypeLibrary__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define ITypeLibrary__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define ITypeLibrary_get_Name(This)	\
    (This)->lpVtbl -> get_Name(This)

#define ITypeLibrary_get_Documentation(This)	\
    (This)->lpVtbl -> get_Documentation(This)

#define ITypeLibrary_get_HelpContext(This)	\
    (This)->lpVtbl -> get_HelpContext(This)

#define ITypeLibrary_get_HelpFile(This)	\
    (This)->lpVtbl -> get_HelpFile(This)

#define ITypeLibrary_get_LocaleID(This)	\
    (This)->lpVtbl -> get_LocaleID(This)

#define ITypeLibrary_get_MajorVersion(This)	\
    (This)->lpVtbl -> get_MajorVersion(This)

#define ITypeLibrary_get_MinorVersion(This)	\
    (This)->lpVtbl -> get_MinorVersion(This)

#define ITypeLibrary_get_TypeInfos(This)	\
    (This)->lpVtbl -> get_TypeInfos(This)

#define ITypeLibrary_get_GUIDAsString(This)	\
    (This)->lpVtbl -> get_GUIDAsString(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ BSTR STDMETHODCALLTYPE ITypeLibrary_get_Name_Proxy( 
    ITypeLibrary __RPC_FAR * This);


void __RPC_STUB ITypeLibrary_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ BSTR STDMETHODCALLTYPE ITypeLibrary_get_Documentation_Proxy( 
    ITypeLibrary __RPC_FAR * This);


void __RPC_STUB ITypeLibrary_get_Documentation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ long STDMETHODCALLTYPE ITypeLibrary_get_HelpContext_Proxy( 
    ITypeLibrary __RPC_FAR * This);


void __RPC_STUB ITypeLibrary_get_HelpContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ BSTR STDMETHODCALLTYPE ITypeLibrary_get_HelpFile_Proxy( 
    ITypeLibrary __RPC_FAR * This);


void __RPC_STUB ITypeLibrary_get_HelpFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ long STDMETHODCALLTYPE ITypeLibrary_get_LocaleID_Proxy( 
    ITypeLibrary __RPC_FAR * This);


void __RPC_STUB ITypeLibrary_get_LocaleID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ int STDMETHODCALLTYPE ITypeLibrary_get_MajorVersion_Proxy( 
    ITypeLibrary __RPC_FAR * This);


void __RPC_STUB ITypeLibrary_get_MajorVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ int STDMETHODCALLTYPE ITypeLibrary_get_MinorVersion_Proxy( 
    ITypeLibrary __RPC_FAR * This);


void __RPC_STUB ITypeLibrary_get_MinorVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE ITypeLibrary_get_TypeInfos_Proxy( 
    ITypeLibrary __RPC_FAR * This);


void __RPC_STUB ITypeLibrary_get_TypeInfos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ BSTR STDMETHODCALLTYPE ITypeLibrary_get_GUIDAsString_Proxy( 
    ITypeLibrary __RPC_FAR * This);


void __RPC_STUB ITypeLibrary_get_GUIDAsString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITypeLibrary_INTERFACE_DEFINED__ */


#ifndef __ITypeInformation_INTERFACE_DEFINED__
#define __ITypeInformation_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITypeInformation
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_ITypeInformation,0x19FEEEC4,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEEC4-4104-101B-B826-00DD01103DE1")
    ITypeInformation : public CMyDispatch
    {
    public:
        virtual /* [helpstring][propget] */ BSTR STDMETHODCALLTYPE get_Name( void) = 0;
        
        virtual /* [helpstring][propget] */ BSTR STDMETHODCALLTYPE get_Documentation( void) = 0;
        
        virtual /* [helpstring][propget] */ long STDMETHODCALLTYPE get_HelpContext( void) = 0;
        
        virtual /* [helpstring][propget] */ BSTR STDMETHODCALLTYPE get_HelpFile( void) = 0;
        
        virtual /* [helpstring][propget] */ TYPEKIND STDMETHODCALLTYPE get_TypeInfoKind( void) = 0;
        
        virtual /* [helpstring][propget] */ short STDMETHODCALLTYPE get_TypeFlags( void) = 0;
        
        virtual /* [helpstring][propget] */ BSTR STDMETHODCALLTYPE get_GUIDAsString( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE _InitTypeInfo( 
            /* [in] */ LPTYPEINFO ptinfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITypeInformationVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITypeInformation __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITypeInformation __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITypeInformation __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITypeInformation __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITypeInformation __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITypeInformation __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITypeInformation __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            ITypeInformation __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            ITypeInformation __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            ITypeInformation __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            ITypeInformation __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ITypeInformation __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Documentation )( 
            ITypeInformation __RPC_FAR * This);
        
        /* [helpstring][propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContext )( 
            ITypeInformation __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            ITypeInformation __RPC_FAR * This);
        
        /* [helpstring][propget] */ TYPEKIND ( STDMETHODCALLTYPE __RPC_FAR *get_TypeInfoKind )( 
            ITypeInformation __RPC_FAR * This);
        
        /* [helpstring][propget] */ short ( STDMETHODCALLTYPE __RPC_FAR *get_TypeFlags )( 
            ITypeInformation __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_GUIDAsString )( 
            ITypeInformation __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_InitTypeInfo )( 
            ITypeInformation __RPC_FAR * This,
            /* [in] */ LPTYPEINFO ptinfo);
        
        END_INTERFACE
    } ITypeInformationVtbl;

    interface ITypeInformation
    {
        CONST_VTBL struct ITypeInformationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITypeInformation_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define ITypeInformation_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define ITypeInformation_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define ITypeInformation_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define ITypeInformation_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define ITypeInformation_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define ITypeInformation_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define ITypeInformation__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define ITypeInformation__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define ITypeInformation__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define ITypeInformation__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define ITypeInformation_get_Name(This)	\
    (This)->lpVtbl -> get_Name(This)

#define ITypeInformation_get_Documentation(This)	\
    (This)->lpVtbl -> get_Documentation(This)

#define ITypeInformation_get_HelpContext(This)	\
    (This)->lpVtbl -> get_HelpContext(This)

#define ITypeInformation_get_HelpFile(This)	\
    (This)->lpVtbl -> get_HelpFile(This)

#define ITypeInformation_get_TypeInfoKind(This)	\
    (This)->lpVtbl -> get_TypeInfoKind(This)

#define ITypeInformation_get_TypeFlags(This)	\
    (This)->lpVtbl -> get_TypeFlags(This)

#define ITypeInformation_get_GUIDAsString(This)	\
    (This)->lpVtbl -> get_GUIDAsString(This)

#define ITypeInformation__InitTypeInfo(This,ptinfo)	\
    (This)->lpVtbl -> _InitTypeInfo(This,ptinfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ BSTR STDMETHODCALLTYPE ITypeInformation_get_Name_Proxy( 
    ITypeInformation __RPC_FAR * This);


void __RPC_STUB ITypeInformation_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ BSTR STDMETHODCALLTYPE ITypeInformation_get_Documentation_Proxy( 
    ITypeInformation __RPC_FAR * This);


void __RPC_STUB ITypeInformation_get_Documentation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ long STDMETHODCALLTYPE ITypeInformation_get_HelpContext_Proxy( 
    ITypeInformation __RPC_FAR * This);


void __RPC_STUB ITypeInformation_get_HelpContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ BSTR STDMETHODCALLTYPE ITypeInformation_get_HelpFile_Proxy( 
    ITypeInformation __RPC_FAR * This);


void __RPC_STUB ITypeInformation_get_HelpFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ TYPEKIND STDMETHODCALLTYPE ITypeInformation_get_TypeInfoKind_Proxy( 
    ITypeInformation __RPC_FAR * This);


void __RPC_STUB ITypeInformation_get_TypeInfoKind_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ short STDMETHODCALLTYPE ITypeInformation_get_TypeFlags_Proxy( 
    ITypeInformation __RPC_FAR * This);


void __RPC_STUB ITypeInformation_get_TypeFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ BSTR STDMETHODCALLTYPE ITypeInformation_get_GUIDAsString_Proxy( 
    ITypeInformation __RPC_FAR * This);


void __RPC_STUB ITypeInformation_get_GUIDAsString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITypeInformation__InitTypeInfo_Proxy( 
    ITypeInformation __RPC_FAR * This,
    /* [in] */ LPTYPEINFO ptinfo);


void __RPC_STUB ITypeInformation__InitTypeInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITypeInformation_INTERFACE_DEFINED__ */


#ifndef __IBrowseHelper_INTERFACE_DEFINED__
#define __IBrowseHelper_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IBrowseHelper
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_IBrowseHelper,0x19FEEEC2,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEEC2-4104-101B-B826-00DD01103DE1")
    IBrowseHelper : public CMyDispatch
    {
    public:
        virtual /* [helpstring] */ ITypeLibrary __RPC_FAR *STDMETHODCALLTYPE BrowseTypeLibrary( 
            /* [in] */ BSTR TypeLibraryPath) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBrowseHelperVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBrowseHelper __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBrowseHelper __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBrowseHelper __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IBrowseHelper __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IBrowseHelper __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IBrowseHelper __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IBrowseHelper __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            IBrowseHelper __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            IBrowseHelper __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            IBrowseHelper __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            IBrowseHelper __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring] */ ITypeLibrary __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *BrowseTypeLibrary )( 
            IBrowseHelper __RPC_FAR * This,
            /* [in] */ BSTR TypeLibraryPath);
        
        END_INTERFACE
    } IBrowseHelperVtbl;

    interface IBrowseHelper
    {
        CONST_VTBL struct IBrowseHelperVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBrowseHelper_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define IBrowseHelper_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define IBrowseHelper_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define IBrowseHelper_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define IBrowseHelper_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define IBrowseHelper_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define IBrowseHelper_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define IBrowseHelper__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define IBrowseHelper__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define IBrowseHelper__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define IBrowseHelper__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define IBrowseHelper_BrowseTypeLibrary(This,TypeLibraryPath)	\
    (This)->lpVtbl -> BrowseTypeLibrary(This,TypeLibraryPath)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ ITypeLibrary __RPC_FAR *STDMETHODCALLTYPE IBrowseHelper_BrowseTypeLibrary_Proxy( 
    IBrowseHelper __RPC_FAR * This,
    /* [in] */ BSTR TypeLibraryPath);


void __RPC_STUB IBrowseHelper_BrowseTypeLibrary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBrowseHelper_INTERFACE_DEFINED__ */


#ifndef __ITypeDesc_INTERFACE_DEFINED__
#define __ITypeDesc_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITypeDesc
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_ITypeDesc,0x19FEEED1,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEED1-4104-101B-B826-00DD01103DE1")
    ITypeDesc : public CMyDispatch
    {
    public:
        virtual /* [helpstring][propget] */ short STDMETHODCALLTYPE get_Type( void) = 0;
        
        virtual /* [helpstring][propget] */ ITypeInformation __RPC_FAR *STDMETHODCALLTYPE get_UserDefinedDesc( void) = 0;
        
        virtual /* [helpstring][propget] */ IArrayDesc __RPC_FAR *STDMETHODCALLTYPE get_ArrayDesc( void) = 0;
        
        virtual /* [helpstring][propget] */ ITypeDesc __RPC_FAR *STDMETHODCALLTYPE get_PointerDesc( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITypeDescVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITypeDesc __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITypeDesc __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITypeDesc __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITypeDesc __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITypeDesc __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITypeDesc __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITypeDesc __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            ITypeDesc __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            ITypeDesc __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            ITypeDesc __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            ITypeDesc __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring][propget] */ short ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            ITypeDesc __RPC_FAR * This);
        
        /* [helpstring][propget] */ ITypeInformation __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_UserDefinedDesc )( 
            ITypeDesc __RPC_FAR * This);
        
        /* [helpstring][propget] */ IArrayDesc __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_ArrayDesc )( 
            ITypeDesc __RPC_FAR * This);
        
        /* [helpstring][propget] */ ITypeDesc __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_PointerDesc )( 
            ITypeDesc __RPC_FAR * This);
        
        END_INTERFACE
    } ITypeDescVtbl;

    interface ITypeDesc
    {
        CONST_VTBL struct ITypeDescVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITypeDesc_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define ITypeDesc_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define ITypeDesc_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define ITypeDesc_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define ITypeDesc_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define ITypeDesc_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define ITypeDesc_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define ITypeDesc__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define ITypeDesc__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define ITypeDesc__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define ITypeDesc__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define ITypeDesc_get_Type(This)	\
    (This)->lpVtbl -> get_Type(This)

#define ITypeDesc_get_UserDefinedDesc(This)	\
    (This)->lpVtbl -> get_UserDefinedDesc(This)

#define ITypeDesc_get_ArrayDesc(This)	\
    (This)->lpVtbl -> get_ArrayDesc(This)

#define ITypeDesc_get_PointerDesc(This)	\
    (This)->lpVtbl -> get_PointerDesc(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ short STDMETHODCALLTYPE ITypeDesc_get_Type_Proxy( 
    ITypeDesc __RPC_FAR * This);


void __RPC_STUB ITypeDesc_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ ITypeInformation __RPC_FAR *STDMETHODCALLTYPE ITypeDesc_get_UserDefinedDesc_Proxy( 
    ITypeDesc __RPC_FAR * This);


void __RPC_STUB ITypeDesc_get_UserDefinedDesc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ IArrayDesc __RPC_FAR *STDMETHODCALLTYPE ITypeDesc_get_ArrayDesc_Proxy( 
    ITypeDesc __RPC_FAR * This);


void __RPC_STUB ITypeDesc_get_ArrayDesc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ ITypeDesc __RPC_FAR *STDMETHODCALLTYPE ITypeDesc_get_PointerDesc_Proxy( 
    ITypeDesc __RPC_FAR * This);


void __RPC_STUB ITypeDesc_get_PointerDesc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITypeDesc_INTERFACE_DEFINED__ */


#ifndef __IArrayBound_INTERFACE_DEFINED__
#define __IArrayBound_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IArrayBound
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_IArrayBound,0x19FEEED3,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEED3-4104-101B-B826-00DD01103DE1")
    IArrayBound : public CMyDispatch
    {
    public:
        virtual /* [helpstring][propget] */ long STDMETHODCALLTYPE get_ElementsCount( void) = 0;
        
        virtual /* [helpstring][propget] */ long STDMETHODCALLTYPE get_LowerBound( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IArrayBoundVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IArrayBound __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IArrayBound __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IArrayBound __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IArrayBound __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IArrayBound __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IArrayBound __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IArrayBound __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            IArrayBound __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            IArrayBound __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            IArrayBound __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            IArrayBound __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring][propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_ElementsCount )( 
            IArrayBound __RPC_FAR * This);
        
        /* [helpstring][propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_LowerBound )( 
            IArrayBound __RPC_FAR * This);
        
        END_INTERFACE
    } IArrayBoundVtbl;

    interface IArrayBound
    {
        CONST_VTBL struct IArrayBoundVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IArrayBound_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define IArrayBound_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define IArrayBound_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define IArrayBound_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define IArrayBound_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define IArrayBound_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define IArrayBound_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define IArrayBound__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define IArrayBound__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define IArrayBound__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define IArrayBound__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define IArrayBound_get_ElementsCount(This)	\
    (This)->lpVtbl -> get_ElementsCount(This)

#define IArrayBound_get_LowerBound(This)	\
    (This)->lpVtbl -> get_LowerBound(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ long STDMETHODCALLTYPE IArrayBound_get_ElementsCount_Proxy( 
    IArrayBound __RPC_FAR * This);


void __RPC_STUB IArrayBound_get_ElementsCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ long STDMETHODCALLTYPE IArrayBound_get_LowerBound_Proxy( 
    IArrayBound __RPC_FAR * This);


void __RPC_STUB IArrayBound_get_LowerBound_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IArrayBound_INTERFACE_DEFINED__ */


#ifndef __IInterface_INTERFACE_DEFINED__
#define __IInterface_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IInterface
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_IInterface,0x19FEEEC5,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEEC5-4104-101B-B826-00DD01103DE1")
    IInterface : public ITypeInformation
    {
    public:
        virtual /* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE get_Functions( void) = 0;
        
        virtual /* [helpstring][propget] */ IInterface __RPC_FAR *STDMETHODCALLTYPE get_BaseInterface( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInterface __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInterface __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInterface __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInterface __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInterface __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInterface __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInterface __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            IInterface __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            IInterface __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            IInterface __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            IInterface __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IInterface __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Documentation )( 
            IInterface __RPC_FAR * This);
        
        /* [helpstring][propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContext )( 
            IInterface __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            IInterface __RPC_FAR * This);
        
        /* [helpstring][propget] */ TYPEKIND ( STDMETHODCALLTYPE __RPC_FAR *get_TypeInfoKind )( 
            IInterface __RPC_FAR * This);
        
        /* [helpstring][propget] */ short ( STDMETHODCALLTYPE __RPC_FAR *get_TypeFlags )( 
            IInterface __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_GUIDAsString )( 
            IInterface __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_InitTypeInfo )( 
            IInterface __RPC_FAR * This,
            /* [in] */ LPTYPEINFO ptinfo);
        
        /* [helpstring][propget] */ ICollection __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_Functions )( 
            IInterface __RPC_FAR * This);
        
        /* [helpstring][propget] */ IInterface __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_BaseInterface )( 
            IInterface __RPC_FAR * This);
        
        END_INTERFACE
    } IInterfaceVtbl;

    interface IInterface
    {
        CONST_VTBL struct IInterfaceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInterface_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define IInterface_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define IInterface_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define IInterface_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define IInterface_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define IInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define IInterface_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define IInterface__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define IInterface__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define IInterface__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define IInterface__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define IInterface_get_Name(This)	\
    (This)->lpVtbl -> get_Name(This)

#define IInterface_get_Documentation(This)	\
    (This)->lpVtbl -> get_Documentation(This)

#define IInterface_get_HelpContext(This)	\
    (This)->lpVtbl -> get_HelpContext(This)

#define IInterface_get_HelpFile(This)	\
    (This)->lpVtbl -> get_HelpFile(This)

#define IInterface_get_TypeInfoKind(This)	\
    (This)->lpVtbl -> get_TypeInfoKind(This)

#define IInterface_get_TypeFlags(This)	\
    (This)->lpVtbl -> get_TypeFlags(This)

#define IInterface_get_GUIDAsString(This)	\
    (This)->lpVtbl -> get_GUIDAsString(This)

#define IInterface__InitTypeInfo(This,ptinfo)	\
    (This)->lpVtbl -> _InitTypeInfo(This,ptinfo)


#define IInterface_get_Functions(This)	\
    (This)->lpVtbl -> get_Functions(This)

#define IInterface_get_BaseInterface(This)	\
    (This)->lpVtbl -> get_BaseInterface(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE IInterface_get_Functions_Proxy( 
    IInterface __RPC_FAR * This);


void __RPC_STUB IInterface_get_Functions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ IInterface __RPC_FAR *STDMETHODCALLTYPE IInterface_get_BaseInterface_Proxy( 
    IInterface __RPC_FAR * This);


void __RPC_STUB IInterface_get_BaseInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInterface_INTERFACE_DEFINED__ */


#ifndef __IDispinterface_INTERFACE_DEFINED__
#define __IDispinterface_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDispinterface
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_IDispinterface,0x19FEEEC6,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEEC6-4104-101B-B826-00DD01103DE1")
    IDispinterface : public ITypeInformation
    {
    public:
        virtual /* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE get_Properties( void) = 0;
        
        virtual /* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE get_Methods( void) = 0;
        
        virtual /* [helpstring][propget] */ IInterface __RPC_FAR *STDMETHODCALLTYPE get_Interface( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDispinterfaceVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDispinterface __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDispinterface __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDispinterface __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDispinterface __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDispinterface __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDispinterface __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDispinterface __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            IDispinterface __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            IDispinterface __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            IDispinterface __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            IDispinterface __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IDispinterface __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Documentation )( 
            IDispinterface __RPC_FAR * This);
        
        /* [helpstring][propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContext )( 
            IDispinterface __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            IDispinterface __RPC_FAR * This);
        
        /* [helpstring][propget] */ TYPEKIND ( STDMETHODCALLTYPE __RPC_FAR *get_TypeInfoKind )( 
            IDispinterface __RPC_FAR * This);
        
        /* [helpstring][propget] */ short ( STDMETHODCALLTYPE __RPC_FAR *get_TypeFlags )( 
            IDispinterface __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_GUIDAsString )( 
            IDispinterface __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_InitTypeInfo )( 
            IDispinterface __RPC_FAR * This,
            /* [in] */ LPTYPEINFO ptinfo);
        
        /* [helpstring][propget] */ ICollection __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_Properties )( 
            IDispinterface __RPC_FAR * This);
        
        /* [helpstring][propget] */ ICollection __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_Methods )( 
            IDispinterface __RPC_FAR * This);
        
        /* [helpstring][propget] */ IInterface __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_Interface )( 
            IDispinterface __RPC_FAR * This);
        
        END_INTERFACE
    } IDispinterfaceVtbl;

    interface IDispinterface
    {
        CONST_VTBL struct IDispinterfaceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDispinterface_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define IDispinterface_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define IDispinterface_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define IDispinterface_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define IDispinterface_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define IDispinterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define IDispinterface_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define IDispinterface__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define IDispinterface__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define IDispinterface__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define IDispinterface__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define IDispinterface_get_Name(This)	\
    (This)->lpVtbl -> get_Name(This)

#define IDispinterface_get_Documentation(This)	\
    (This)->lpVtbl -> get_Documentation(This)

#define IDispinterface_get_HelpContext(This)	\
    (This)->lpVtbl -> get_HelpContext(This)

#define IDispinterface_get_HelpFile(This)	\
    (This)->lpVtbl -> get_HelpFile(This)

#define IDispinterface_get_TypeInfoKind(This)	\
    (This)->lpVtbl -> get_TypeInfoKind(This)

#define IDispinterface_get_TypeFlags(This)	\
    (This)->lpVtbl -> get_TypeFlags(This)

#define IDispinterface_get_GUIDAsString(This)	\
    (This)->lpVtbl -> get_GUIDAsString(This)

#define IDispinterface__InitTypeInfo(This,ptinfo)	\
    (This)->lpVtbl -> _InitTypeInfo(This,ptinfo)


#define IDispinterface_get_Properties(This)	\
    (This)->lpVtbl -> get_Properties(This)

#define IDispinterface_get_Methods(This)	\
    (This)->lpVtbl -> get_Methods(This)

#define IDispinterface_get_Interface(This)	\
    (This)->lpVtbl -> get_Interface(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE IDispinterface_get_Properties_Proxy( 
    IDispinterface __RPC_FAR * This);


void __RPC_STUB IDispinterface_get_Properties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE IDispinterface_get_Methods_Proxy( 
    IDispinterface __RPC_FAR * This);


void __RPC_STUB IDispinterface_get_Methods_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ IInterface __RPC_FAR *STDMETHODCALLTYPE IDispinterface_get_Interface_Proxy( 
    IDispinterface __RPC_FAR * This);


void __RPC_STUB IDispinterface_get_Interface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDispinterface_INTERFACE_DEFINED__ */


#ifndef __IModule_INTERFACE_DEFINED__
#define __IModule_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IModule
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_IModule,0x19FEEEC7,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEEC7-4104-101B-B826-00DD01103DE1")
    IModule : public ITypeInformation
    {
    public:
        virtual /* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE get_Functions( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IModuleVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IModule __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IModule __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IModule __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IModule __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IModule __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IModule __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IModule __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            IModule __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            IModule __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            IModule __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            IModule __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IModule __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Documentation )( 
            IModule __RPC_FAR * This);
        
        /* [helpstring][propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContext )( 
            IModule __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            IModule __RPC_FAR * This);
        
        /* [helpstring][propget] */ TYPEKIND ( STDMETHODCALLTYPE __RPC_FAR *get_TypeInfoKind )( 
            IModule __RPC_FAR * This);
        
        /* [helpstring][propget] */ short ( STDMETHODCALLTYPE __RPC_FAR *get_TypeFlags )( 
            IModule __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_GUIDAsString )( 
            IModule __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_InitTypeInfo )( 
            IModule __RPC_FAR * This,
            /* [in] */ LPTYPEINFO ptinfo);
        
        /* [helpstring][propget] */ ICollection __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_Functions )( 
            IModule __RPC_FAR * This);
        
        END_INTERFACE
    } IModuleVtbl;

    interface IModule
    {
        CONST_VTBL struct IModuleVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IModule_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define IModule_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define IModule_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define IModule_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define IModule_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define IModule_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define IModule_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define IModule__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define IModule__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define IModule__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define IModule__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define IModule_get_Name(This)	\
    (This)->lpVtbl -> get_Name(This)

#define IModule_get_Documentation(This)	\
    (This)->lpVtbl -> get_Documentation(This)

#define IModule_get_HelpContext(This)	\
    (This)->lpVtbl -> get_HelpContext(This)

#define IModule_get_HelpFile(This)	\
    (This)->lpVtbl -> get_HelpFile(This)

#define IModule_get_TypeInfoKind(This)	\
    (This)->lpVtbl -> get_TypeInfoKind(This)

#define IModule_get_TypeFlags(This)	\
    (This)->lpVtbl -> get_TypeFlags(This)

#define IModule_get_GUIDAsString(This)	\
    (This)->lpVtbl -> get_GUIDAsString(This)

#define IModule__InitTypeInfo(This,ptinfo)	\
    (This)->lpVtbl -> _InitTypeInfo(This,ptinfo)


#define IModule_get_Functions(This)	\
    (This)->lpVtbl -> get_Functions(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE IModule_get_Functions_Proxy( 
    IModule __RPC_FAR * This);


void __RPC_STUB IModule_get_Functions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IModule_INTERFACE_DEFINED__ */


#ifndef __ICoClass_INTERFACE_DEFINED__
#define __ICoClass_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICoClass
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_ICoClass,0x19FEEEC8,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEEC8-4104-101B-B826-00DD01103DE1")
    ICoClass : public ITypeInformation
    {
    public:
        virtual /* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE get_Interfaces( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICoClassVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICoClass __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICoClass __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICoClass __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICoClass __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICoClass __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICoClass __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICoClass __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            ICoClass __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            ICoClass __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            ICoClass __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            ICoClass __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ICoClass __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Documentation )( 
            ICoClass __RPC_FAR * This);
        
        /* [helpstring][propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContext )( 
            ICoClass __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            ICoClass __RPC_FAR * This);
        
        /* [helpstring][propget] */ TYPEKIND ( STDMETHODCALLTYPE __RPC_FAR *get_TypeInfoKind )( 
            ICoClass __RPC_FAR * This);
        
        /* [helpstring][propget] */ short ( STDMETHODCALLTYPE __RPC_FAR *get_TypeFlags )( 
            ICoClass __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_GUIDAsString )( 
            ICoClass __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_InitTypeInfo )( 
            ICoClass __RPC_FAR * This,
            /* [in] */ LPTYPEINFO ptinfo);
        
        /* [helpstring][propget] */ ICollection __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_Interfaces )( 
            ICoClass __RPC_FAR * This);
        
        END_INTERFACE
    } ICoClassVtbl;

    interface ICoClass
    {
        CONST_VTBL struct ICoClassVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICoClass_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define ICoClass_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define ICoClass_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define ICoClass_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define ICoClass_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define ICoClass_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define ICoClass_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define ICoClass__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define ICoClass__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define ICoClass__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define ICoClass__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define ICoClass_get_Name(This)	\
    (This)->lpVtbl -> get_Name(This)

#define ICoClass_get_Documentation(This)	\
    (This)->lpVtbl -> get_Documentation(This)

#define ICoClass_get_HelpContext(This)	\
    (This)->lpVtbl -> get_HelpContext(This)

#define ICoClass_get_HelpFile(This)	\
    (This)->lpVtbl -> get_HelpFile(This)

#define ICoClass_get_TypeInfoKind(This)	\
    (This)->lpVtbl -> get_TypeInfoKind(This)

#define ICoClass_get_TypeFlags(This)	\
    (This)->lpVtbl -> get_TypeFlags(This)

#define ICoClass_get_GUIDAsString(This)	\
    (This)->lpVtbl -> get_GUIDAsString(This)

#define ICoClass__InitTypeInfo(This,ptinfo)	\
    (This)->lpVtbl -> _InitTypeInfo(This,ptinfo)


#define ICoClass_get_Interfaces(This)	\
    (This)->lpVtbl -> get_Interfaces(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE ICoClass_get_Interfaces_Proxy( 
    ICoClass __RPC_FAR * This);


void __RPC_STUB ICoClass_get_Interfaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICoClass_INTERFACE_DEFINED__ */


#ifndef __IEnum_INTERFACE_DEFINED__
#define __IEnum_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnum
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_IEnum,0x19FEEECD,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEECD-4104-101B-B826-00DD01103DE1")
    IEnum : public ITypeInformation
    {
    public:
        virtual /* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE get_Elements( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnum __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnum __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnum __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IEnum __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IEnum __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IEnum __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IEnum __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            IEnum __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            IEnum __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            IEnum __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            IEnum __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IEnum __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Documentation )( 
            IEnum __RPC_FAR * This);
        
        /* [helpstring][propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContext )( 
            IEnum __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            IEnum __RPC_FAR * This);
        
        /* [helpstring][propget] */ TYPEKIND ( STDMETHODCALLTYPE __RPC_FAR *get_TypeInfoKind )( 
            IEnum __RPC_FAR * This);
        
        /* [helpstring][propget] */ short ( STDMETHODCALLTYPE __RPC_FAR *get_TypeFlags )( 
            IEnum __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_GUIDAsString )( 
            IEnum __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_InitTypeInfo )( 
            IEnum __RPC_FAR * This,
            /* [in] */ LPTYPEINFO ptinfo);
        
        /* [helpstring][propget] */ ICollection __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_Elements )( 
            IEnum __RPC_FAR * This);
        
        END_INTERFACE
    } IEnumVtbl;

    interface IEnum
    {
        CONST_VTBL struct IEnumVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnum_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define IEnum_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define IEnum_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define IEnum_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define IEnum_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define IEnum_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define IEnum_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define IEnum__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define IEnum__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define IEnum__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define IEnum__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define IEnum_get_Name(This)	\
    (This)->lpVtbl -> get_Name(This)

#define IEnum_get_Documentation(This)	\
    (This)->lpVtbl -> get_Documentation(This)

#define IEnum_get_HelpContext(This)	\
    (This)->lpVtbl -> get_HelpContext(This)

#define IEnum_get_HelpFile(This)	\
    (This)->lpVtbl -> get_HelpFile(This)

#define IEnum_get_TypeInfoKind(This)	\
    (This)->lpVtbl -> get_TypeInfoKind(This)

#define IEnum_get_TypeFlags(This)	\
    (This)->lpVtbl -> get_TypeFlags(This)

#define IEnum_get_GUIDAsString(This)	\
    (This)->lpVtbl -> get_GUIDAsString(This)

#define IEnum__InitTypeInfo(This,ptinfo)	\
    (This)->lpVtbl -> _InitTypeInfo(This,ptinfo)


#define IEnum_get_Elements(This)	\
    (This)->lpVtbl -> get_Elements(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE IEnum_get_Elements_Proxy( 
    IEnum __RPC_FAR * This);


void __RPC_STUB IEnum_get_Elements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnum_INTERFACE_DEFINED__ */


#ifndef __IStruct_INTERFACE_DEFINED__
#define __IStruct_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IStruct
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_IStruct,0x19FEEECE,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEECE-4104-101B-B826-00DD01103DE1")
    IStruct : public ITypeInformation
    {
    public:
        virtual /* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE get_Members( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStructVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStruct __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStruct __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStruct __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IStruct __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IStruct __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IStruct __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IStruct __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            IStruct __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            IStruct __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            IStruct __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            IStruct __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IStruct __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Documentation )( 
            IStruct __RPC_FAR * This);
        
        /* [helpstring][propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContext )( 
            IStruct __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            IStruct __RPC_FAR * This);
        
        /* [helpstring][propget] */ TYPEKIND ( STDMETHODCALLTYPE __RPC_FAR *get_TypeInfoKind )( 
            IStruct __RPC_FAR * This);
        
        /* [helpstring][propget] */ short ( STDMETHODCALLTYPE __RPC_FAR *get_TypeFlags )( 
            IStruct __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_GUIDAsString )( 
            IStruct __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_InitTypeInfo )( 
            IStruct __RPC_FAR * This,
            /* [in] */ LPTYPEINFO ptinfo);
        
        /* [helpstring][propget] */ ICollection __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_Members )( 
            IStruct __RPC_FAR * This);
        
        END_INTERFACE
    } IStructVtbl;

    interface IStruct
    {
        CONST_VTBL struct IStructVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStruct_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define IStruct_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define IStruct_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define IStruct_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define IStruct_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define IStruct_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define IStruct_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define IStruct__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define IStruct__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define IStruct__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define IStruct__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define IStruct_get_Name(This)	\
    (This)->lpVtbl -> get_Name(This)

#define IStruct_get_Documentation(This)	\
    (This)->lpVtbl -> get_Documentation(This)

#define IStruct_get_HelpContext(This)	\
    (This)->lpVtbl -> get_HelpContext(This)

#define IStruct_get_HelpFile(This)	\
    (This)->lpVtbl -> get_HelpFile(This)

#define IStruct_get_TypeInfoKind(This)	\
    (This)->lpVtbl -> get_TypeInfoKind(This)

#define IStruct_get_TypeFlags(This)	\
    (This)->lpVtbl -> get_TypeFlags(This)

#define IStruct_get_GUIDAsString(This)	\
    (This)->lpVtbl -> get_GUIDAsString(This)

#define IStruct__InitTypeInfo(This,ptinfo)	\
    (This)->lpVtbl -> _InitTypeInfo(This,ptinfo)


#define IStruct_get_Members(This)	\
    (This)->lpVtbl -> get_Members(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE IStruct_get_Members_Proxy( 
    IStruct __RPC_FAR * This);


void __RPC_STUB IStruct_get_Members_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStruct_INTERFACE_DEFINED__ */


#ifndef __IUnion_INTERFACE_DEFINED__
#define __IUnion_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IUnion
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_IUnion,0x19FEEECF,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEECF-4104-101B-B826-00DD01103DE1")
    IUnion : public ITypeInformation
    {
    public:
        virtual /* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE get_Members( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUnionVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUnion __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUnion __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUnion __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IUnion __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IUnion __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IUnion __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IUnion __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            IUnion __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            IUnion __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            IUnion __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            IUnion __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IUnion __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Documentation )( 
            IUnion __RPC_FAR * This);
        
        /* [helpstring][propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContext )( 
            IUnion __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            IUnion __RPC_FAR * This);
        
        /* [helpstring][propget] */ TYPEKIND ( STDMETHODCALLTYPE __RPC_FAR *get_TypeInfoKind )( 
            IUnion __RPC_FAR * This);
        
        /* [helpstring][propget] */ short ( STDMETHODCALLTYPE __RPC_FAR *get_TypeFlags )( 
            IUnion __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_GUIDAsString )( 
            IUnion __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_InitTypeInfo )( 
            IUnion __RPC_FAR * This,
            /* [in] */ LPTYPEINFO ptinfo);
        
        /* [helpstring][propget] */ ICollection __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_Members )( 
            IUnion __RPC_FAR * This);
        
        END_INTERFACE
    } IUnionVtbl;

    interface IUnion
    {
        CONST_VTBL struct IUnionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnion_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define IUnion_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define IUnion_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define IUnion_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define IUnion_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define IUnion_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define IUnion_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define IUnion__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define IUnion__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define IUnion__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define IUnion__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define IUnion_get_Name(This)	\
    (This)->lpVtbl -> get_Name(This)

#define IUnion_get_Documentation(This)	\
    (This)->lpVtbl -> get_Documentation(This)

#define IUnion_get_HelpContext(This)	\
    (This)->lpVtbl -> get_HelpContext(This)

#define IUnion_get_HelpFile(This)	\
    (This)->lpVtbl -> get_HelpFile(This)

#define IUnion_get_TypeInfoKind(This)	\
    (This)->lpVtbl -> get_TypeInfoKind(This)

#define IUnion_get_TypeFlags(This)	\
    (This)->lpVtbl -> get_TypeFlags(This)

#define IUnion_get_GUIDAsString(This)	\
    (This)->lpVtbl -> get_GUIDAsString(This)

#define IUnion__InitTypeInfo(This,ptinfo)	\
    (This)->lpVtbl -> _InitTypeInfo(This,ptinfo)


#define IUnion_get_Members(This)	\
    (This)->lpVtbl -> get_Members(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE IUnion_get_Members_Proxy( 
    IUnion __RPC_FAR * This);


void __RPC_STUB IUnion_get_Members_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUnion_INTERFACE_DEFINED__ */


#ifndef __IAlias_INTERFACE_DEFINED__
#define __IAlias_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAlias
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_IAlias,0x19FEEED0,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEED0-4104-101B-B826-00DD01103DE1")
    IAlias : public ITypeInformation
    {
    public:
        virtual /* [helpstring][propget] */ ITypeDesc __RPC_FAR *STDMETHODCALLTYPE get_BaseType( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAliasVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAlias __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAlias __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAlias __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAlias __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAlias __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAlias __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAlias __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            IAlias __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            IAlias __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            IAlias __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            IAlias __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IAlias __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Documentation )( 
            IAlias __RPC_FAR * This);
        
        /* [helpstring][propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContext )( 
            IAlias __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            IAlias __RPC_FAR * This);
        
        /* [helpstring][propget] */ TYPEKIND ( STDMETHODCALLTYPE __RPC_FAR *get_TypeInfoKind )( 
            IAlias __RPC_FAR * This);
        
        /* [helpstring][propget] */ short ( STDMETHODCALLTYPE __RPC_FAR *get_TypeFlags )( 
            IAlias __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_GUIDAsString )( 
            IAlias __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_InitTypeInfo )( 
            IAlias __RPC_FAR * This,
            /* [in] */ LPTYPEINFO ptinfo);
        
        /* [helpstring][propget] */ ITypeDesc __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_BaseType )( 
            IAlias __RPC_FAR * This);
        
        END_INTERFACE
    } IAliasVtbl;

    interface IAlias
    {
        CONST_VTBL struct IAliasVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAlias_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define IAlias_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define IAlias_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define IAlias_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define IAlias_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define IAlias_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define IAlias_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define IAlias__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define IAlias__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define IAlias__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define IAlias__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define IAlias_get_Name(This)	\
    (This)->lpVtbl -> get_Name(This)

#define IAlias_get_Documentation(This)	\
    (This)->lpVtbl -> get_Documentation(This)

#define IAlias_get_HelpContext(This)	\
    (This)->lpVtbl -> get_HelpContext(This)

#define IAlias_get_HelpFile(This)	\
    (This)->lpVtbl -> get_HelpFile(This)

#define IAlias_get_TypeInfoKind(This)	\
    (This)->lpVtbl -> get_TypeInfoKind(This)

#define IAlias_get_TypeFlags(This)	\
    (This)->lpVtbl -> get_TypeFlags(This)

#define IAlias_get_GUIDAsString(This)	\
    (This)->lpVtbl -> get_GUIDAsString(This)

#define IAlias__InitTypeInfo(This,ptinfo)	\
    (This)->lpVtbl -> _InitTypeInfo(This,ptinfo)


#define IAlias_get_BaseType(This)	\
    (This)->lpVtbl -> get_BaseType(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ ITypeDesc __RPC_FAR *STDMETHODCALLTYPE IAlias_get_BaseType_Proxy( 
    IAlias __RPC_FAR * This);


void __RPC_STUB IAlias_get_BaseType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAlias_INTERFACE_DEFINED__ */


#ifndef __IFunction_INTERFACE_DEFINED__
#define __IFunction_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IFunction
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_IFunction,0x19FEEEC9,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEEC9-4104-101B-B826-00DD01103DE1")
    IFunction : public CMyDispatch
    {
    public:
        virtual /* [helpstring][propget] */ BSTR STDMETHODCALLTYPE get_Name( void) = 0;
        
        virtual /* [helpstring][propget] */ BSTR STDMETHODCALLTYPE get_Documentation( void) = 0;
        
        virtual /* [helpstring][propget] */ long STDMETHODCALLTYPE get_HelpContext( void) = 0;
        
        virtual /* [helpstring][propget] */ BSTR STDMETHODCALLTYPE get_HelpFile( void) = 0;
        
        virtual /* [helpstring][propget] */ ITypeDesc __RPC_FAR *STDMETHODCALLTYPE get_ReturnType( void) = 0;
        
        virtual /* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE get_Parameters( void) = 0;
        
        virtual /* [helpstring][propget] */ MEMBERID STDMETHODCALLTYPE get_Memberid( void) = 0;
        
        virtual /* [helpstring][propget] */ CALLCONV STDMETHODCALLTYPE get_CallConvention( void) = 0;
        
        virtual /* [helpstring][propget] */ FUNCKIND STDMETHODCALLTYPE get_FuncKind( void) = 0;
        
        virtual /* [helpstring][propget] */ INVOKEKIND STDMETHODCALLTYPE get_InvocationKind( void) = 0;
        
        virtual /* [helpstring][propget] */ short STDMETHODCALLTYPE get_NumberOfOptionalParams( void) = 0;
        
        virtual /* [helpstring][propget] */ short STDMETHODCALLTYPE get_OffsetInVtbl( void) = 0;
        
        virtual /* [helpstring][propget] */ unsigned short STDMETHODCALLTYPE get_FuncFlags( void) = 0;
        
        virtual /* [helpstring][propget] */ OBJTYPE STDMETHODCALLTYPE get_Kind( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFunctionVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFunction __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFunction __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFunction __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IFunction __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IFunction __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IFunction __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IFunction __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            IFunction __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            IFunction __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            IFunction __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            IFunction __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IFunction __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Documentation )( 
            IFunction __RPC_FAR * This);
        
        /* [helpstring][propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContext )( 
            IFunction __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            IFunction __RPC_FAR * This);
        
        /* [helpstring][propget] */ ITypeDesc __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_ReturnType )( 
            IFunction __RPC_FAR * This);
        
        /* [helpstring][propget] */ ICollection __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_Parameters )( 
            IFunction __RPC_FAR * This);
        
        /* [helpstring][propget] */ MEMBERID ( STDMETHODCALLTYPE __RPC_FAR *get_Memberid )( 
            IFunction __RPC_FAR * This);
        
        /* [helpstring][propget] */ CALLCONV ( STDMETHODCALLTYPE __RPC_FAR *get_CallConvention )( 
            IFunction __RPC_FAR * This);
        
        /* [helpstring][propget] */ FUNCKIND ( STDMETHODCALLTYPE __RPC_FAR *get_FuncKind )( 
            IFunction __RPC_FAR * This);
        
        /* [helpstring][propget] */ INVOKEKIND ( STDMETHODCALLTYPE __RPC_FAR *get_InvocationKind )( 
            IFunction __RPC_FAR * This);
        
        /* [helpstring][propget] */ short ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfOptionalParams )( 
            IFunction __RPC_FAR * This);
        
        /* [helpstring][propget] */ short ( STDMETHODCALLTYPE __RPC_FAR *get_OffsetInVtbl )( 
            IFunction __RPC_FAR * This);
        
        /* [helpstring][propget] */ unsigned short ( STDMETHODCALLTYPE __RPC_FAR *get_FuncFlags )( 
            IFunction __RPC_FAR * This);
        
        /* [helpstring][propget] */ OBJTYPE ( STDMETHODCALLTYPE __RPC_FAR *get_Kind )( 
            IFunction __RPC_FAR * This);
        
        END_INTERFACE
    } IFunctionVtbl;

    interface IFunction
    {
        CONST_VTBL struct IFunctionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFunction_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define IFunction_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define IFunction_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define IFunction_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define IFunction_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define IFunction_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define IFunction_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define IFunction__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define IFunction__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define IFunction__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define IFunction__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define IFunction_get_Name(This)	\
    (This)->lpVtbl -> get_Name(This)

#define IFunction_get_Documentation(This)	\
    (This)->lpVtbl -> get_Documentation(This)

#define IFunction_get_HelpContext(This)	\
    (This)->lpVtbl -> get_HelpContext(This)

#define IFunction_get_HelpFile(This)	\
    (This)->lpVtbl -> get_HelpFile(This)

#define IFunction_get_ReturnType(This)	\
    (This)->lpVtbl -> get_ReturnType(This)

#define IFunction_get_Parameters(This)	\
    (This)->lpVtbl -> get_Parameters(This)

#define IFunction_get_Memberid(This)	\
    (This)->lpVtbl -> get_Memberid(This)

#define IFunction_get_CallConvention(This)	\
    (This)->lpVtbl -> get_CallConvention(This)

#define IFunction_get_FuncKind(This)	\
    (This)->lpVtbl -> get_FuncKind(This)

#define IFunction_get_InvocationKind(This)	\
    (This)->lpVtbl -> get_InvocationKind(This)

#define IFunction_get_NumberOfOptionalParams(This)	\
    (This)->lpVtbl -> get_NumberOfOptionalParams(This)

#define IFunction_get_OffsetInVtbl(This)	\
    (This)->lpVtbl -> get_OffsetInVtbl(This)

#define IFunction_get_FuncFlags(This)	\
    (This)->lpVtbl -> get_FuncFlags(This)

#define IFunction_get_Kind(This)	\
    (This)->lpVtbl -> get_Kind(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ BSTR STDMETHODCALLTYPE IFunction_get_Name_Proxy( 
    IFunction __RPC_FAR * This);


void __RPC_STUB IFunction_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ BSTR STDMETHODCALLTYPE IFunction_get_Documentation_Proxy( 
    IFunction __RPC_FAR * This);


void __RPC_STUB IFunction_get_Documentation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ long STDMETHODCALLTYPE IFunction_get_HelpContext_Proxy( 
    IFunction __RPC_FAR * This);


void __RPC_STUB IFunction_get_HelpContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ BSTR STDMETHODCALLTYPE IFunction_get_HelpFile_Proxy( 
    IFunction __RPC_FAR * This);


void __RPC_STUB IFunction_get_HelpFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ ITypeDesc __RPC_FAR *STDMETHODCALLTYPE IFunction_get_ReturnType_Proxy( 
    IFunction __RPC_FAR * This);


void __RPC_STUB IFunction_get_ReturnType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ ICollection __RPC_FAR *STDMETHODCALLTYPE IFunction_get_Parameters_Proxy( 
    IFunction __RPC_FAR * This);


void __RPC_STUB IFunction_get_Parameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ MEMBERID STDMETHODCALLTYPE IFunction_get_Memberid_Proxy( 
    IFunction __RPC_FAR * This);


void __RPC_STUB IFunction_get_Memberid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ CALLCONV STDMETHODCALLTYPE IFunction_get_CallConvention_Proxy( 
    IFunction __RPC_FAR * This);


void __RPC_STUB IFunction_get_CallConvention_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ FUNCKIND STDMETHODCALLTYPE IFunction_get_FuncKind_Proxy( 
    IFunction __RPC_FAR * This);


void __RPC_STUB IFunction_get_FuncKind_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ INVOKEKIND STDMETHODCALLTYPE IFunction_get_InvocationKind_Proxy( 
    IFunction __RPC_FAR * This);


void __RPC_STUB IFunction_get_InvocationKind_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ short STDMETHODCALLTYPE IFunction_get_NumberOfOptionalParams_Proxy( 
    IFunction __RPC_FAR * This);


void __RPC_STUB IFunction_get_NumberOfOptionalParams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ short STDMETHODCALLTYPE IFunction_get_OffsetInVtbl_Proxy( 
    IFunction __RPC_FAR * This);


void __RPC_STUB IFunction_get_OffsetInVtbl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ unsigned short STDMETHODCALLTYPE IFunction_get_FuncFlags_Proxy( 
    IFunction __RPC_FAR * This);


void __RPC_STUB IFunction_get_FuncFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ OBJTYPE STDMETHODCALLTYPE IFunction_get_Kind_Proxy( 
    IFunction __RPC_FAR * This);


void __RPC_STUB IFunction_get_Kind_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFunction_INTERFACE_DEFINED__ */


#ifndef __IProperty_INTERFACE_DEFINED__
#define __IProperty_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IProperty
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_IProperty,0x19FEEECA,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEECA-4104-101B-B826-00DD01103DE1")
    IProperty : public CMyDispatch
    {
    public:
        virtual /* [helpstring][propget] */ BSTR STDMETHODCALLTYPE get_Name( void) = 0;
        
        virtual /* [helpstring][propget] */ BSTR STDMETHODCALLTYPE get_Documentation( void) = 0;
        
        virtual /* [helpstring][propget] */ long STDMETHODCALLTYPE get_HelpContext( void) = 0;
        
        virtual /* [helpstring][propget] */ BSTR STDMETHODCALLTYPE get_HelpFile( void) = 0;
        
        virtual /* [helpstring][propget] */ ITypeDesc __RPC_FAR *STDMETHODCALLTYPE get_Type( void) = 0;
        
        virtual /* [helpstring][propget] */ MEMBERID STDMETHODCALLTYPE get_Memberid( void) = 0;
        
        virtual /* [helpstring][propget] */ OBJTYPE STDMETHODCALLTYPE get_Kind( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropertyVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IProperty __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IProperty __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IProperty __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IProperty __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IProperty __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IProperty __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IProperty __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            IProperty __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            IProperty __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            IProperty __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            IProperty __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IProperty __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Documentation )( 
            IProperty __RPC_FAR * This);
        
        /* [helpstring][propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContext )( 
            IProperty __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            IProperty __RPC_FAR * This);
        
        /* [helpstring][propget] */ ITypeDesc __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IProperty __RPC_FAR * This);
        
        /* [helpstring][propget] */ MEMBERID ( STDMETHODCALLTYPE __RPC_FAR *get_Memberid )( 
            IProperty __RPC_FAR * This);
        
        /* [helpstring][propget] */ OBJTYPE ( STDMETHODCALLTYPE __RPC_FAR *get_Kind )( 
            IProperty __RPC_FAR * This);
        
        END_INTERFACE
    } IPropertyVtbl;

    interface IProperty
    {
        CONST_VTBL struct IPropertyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProperty_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define IProperty_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define IProperty_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define IProperty_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define IProperty_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define IProperty_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define IProperty_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define IProperty__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define IProperty__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define IProperty__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define IProperty__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define IProperty_get_Name(This)	\
    (This)->lpVtbl -> get_Name(This)

#define IProperty_get_Documentation(This)	\
    (This)->lpVtbl -> get_Documentation(This)

#define IProperty_get_HelpContext(This)	\
    (This)->lpVtbl -> get_HelpContext(This)

#define IProperty_get_HelpFile(This)	\
    (This)->lpVtbl -> get_HelpFile(This)

#define IProperty_get_Type(This)	\
    (This)->lpVtbl -> get_Type(This)

#define IProperty_get_Memberid(This)	\
    (This)->lpVtbl -> get_Memberid(This)

#define IProperty_get_Kind(This)	\
    (This)->lpVtbl -> get_Kind(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ BSTR STDMETHODCALLTYPE IProperty_get_Name_Proxy( 
    IProperty __RPC_FAR * This);


void __RPC_STUB IProperty_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ BSTR STDMETHODCALLTYPE IProperty_get_Documentation_Proxy( 
    IProperty __RPC_FAR * This);


void __RPC_STUB IProperty_get_Documentation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ long STDMETHODCALLTYPE IProperty_get_HelpContext_Proxy( 
    IProperty __RPC_FAR * This);


void __RPC_STUB IProperty_get_HelpContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ BSTR STDMETHODCALLTYPE IProperty_get_HelpFile_Proxy( 
    IProperty __RPC_FAR * This);


void __RPC_STUB IProperty_get_HelpFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ ITypeDesc __RPC_FAR *STDMETHODCALLTYPE IProperty_get_Type_Proxy( 
    IProperty __RPC_FAR * This);


void __RPC_STUB IProperty_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ MEMBERID STDMETHODCALLTYPE IProperty_get_Memberid_Proxy( 
    IProperty __RPC_FAR * This);


void __RPC_STUB IProperty_get_Memberid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ OBJTYPE STDMETHODCALLTYPE IProperty_get_Kind_Proxy( 
    IProperty __RPC_FAR * This);


void __RPC_STUB IProperty_get_Kind_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IProperty_INTERFACE_DEFINED__ */


#ifndef __IConstant_INTERFACE_DEFINED__
#define __IConstant_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IConstant
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_IConstant,0x19FEEED4,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEED4-4104-101B-B826-00DD01103DE1")
    IConstant : public CMyDispatch
    {
    public:
        virtual /* [helpstring][propget] */ BSTR STDMETHODCALLTYPE get_Name( void) = 0;
        
        virtual /* [helpstring][propget] */ BSTR STDMETHODCALLTYPE get_Documentation( void) = 0;
        
        virtual /* [helpstring][propget] */ long STDMETHODCALLTYPE get_HelpContext( void) = 0;
        
        virtual /* [helpstring][propget] */ BSTR STDMETHODCALLTYPE get_HelpFile( void) = 0;
        
        virtual /* [helpstring][propget] */ ITypeDesc __RPC_FAR *STDMETHODCALLTYPE get_Type( void) = 0;
        
        virtual /* [helpstring][propget] */ VARIANT STDMETHODCALLTYPE get_Value( void) = 0;
        
        virtual /* [helpstring][propget] */ MEMBERID STDMETHODCALLTYPE get_Memberid( void) = 0;
        
        virtual /* [helpstring][propget] */ OBJTYPE STDMETHODCALLTYPE get_Kind( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConstantVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IConstant __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IConstant __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IConstant __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IConstant __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IConstant __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IConstant __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IConstant __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            IConstant __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            IConstant __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            IConstant __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            IConstant __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IConstant __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Documentation )( 
            IConstant __RPC_FAR * This);
        
        /* [helpstring][propget] */ long ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContext )( 
            IConstant __RPC_FAR * This);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            IConstant __RPC_FAR * This);
        
        /* [helpstring][propget] */ ITypeDesc __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IConstant __RPC_FAR * This);
        
        /* [helpstring][propget] */ VARIANT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            IConstant __RPC_FAR * This);
        
        /* [helpstring][propget] */ MEMBERID ( STDMETHODCALLTYPE __RPC_FAR *get_Memberid )( 
            IConstant __RPC_FAR * This);
        
        /* [helpstring][propget] */ OBJTYPE ( STDMETHODCALLTYPE __RPC_FAR *get_Kind )( 
            IConstant __RPC_FAR * This);
        
        END_INTERFACE
    } IConstantVtbl;

    interface IConstant
    {
        CONST_VTBL struct IConstantVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConstant_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define IConstant_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define IConstant_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define IConstant_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define IConstant_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define IConstant_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define IConstant_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define IConstant__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define IConstant__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define IConstant__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define IConstant__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define IConstant_get_Name(This)	\
    (This)->lpVtbl -> get_Name(This)

#define IConstant_get_Documentation(This)	\
    (This)->lpVtbl -> get_Documentation(This)

#define IConstant_get_HelpContext(This)	\
    (This)->lpVtbl -> get_HelpContext(This)

#define IConstant_get_HelpFile(This)	\
    (This)->lpVtbl -> get_HelpFile(This)

#define IConstant_get_Type(This)	\
    (This)->lpVtbl -> get_Type(This)

#define IConstant_get_Value(This)	\
    (This)->lpVtbl -> get_Value(This)

#define IConstant_get_Memberid(This)	\
    (This)->lpVtbl -> get_Memberid(This)

#define IConstant_get_Kind(This)	\
    (This)->lpVtbl -> get_Kind(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ BSTR STDMETHODCALLTYPE IConstant_get_Name_Proxy( 
    IConstant __RPC_FAR * This);


void __RPC_STUB IConstant_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ BSTR STDMETHODCALLTYPE IConstant_get_Documentation_Proxy( 
    IConstant __RPC_FAR * This);


void __RPC_STUB IConstant_get_Documentation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ long STDMETHODCALLTYPE IConstant_get_HelpContext_Proxy( 
    IConstant __RPC_FAR * This);


void __RPC_STUB IConstant_get_HelpContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ BSTR STDMETHODCALLTYPE IConstant_get_HelpFile_Proxy( 
    IConstant __RPC_FAR * This);


void __RPC_STUB IConstant_get_HelpFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ ITypeDesc __RPC_FAR *STDMETHODCALLTYPE IConstant_get_Type_Proxy( 
    IConstant __RPC_FAR * This);


void __RPC_STUB IConstant_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ VARIANT STDMETHODCALLTYPE IConstant_get_Value_Proxy( 
    IConstant __RPC_FAR * This);


void __RPC_STUB IConstant_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ MEMBERID STDMETHODCALLTYPE IConstant_get_Memberid_Proxy( 
    IConstant __RPC_FAR * This);


void __RPC_STUB IConstant_get_Memberid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ OBJTYPE STDMETHODCALLTYPE IConstant_get_Kind_Proxy( 
    IConstant __RPC_FAR * This);


void __RPC_STUB IConstant_get_Kind_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IConstant_INTERFACE_DEFINED__ */


#ifndef __IParameter_INTERFACE_DEFINED__
#define __IParameter_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IParameter
 * at Mon Mar 30 02:35:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_IParameter,0x19FEEECB,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19FEEECB-4104-101B-B826-00DD01103DE1")
    IParameter : public CMyDispatch
    {
    public:
        virtual /* [helpstring][propget] */ BSTR STDMETHODCALLTYPE get_Name( void) = 0;
        
        virtual /* [helpstring][propget] */ ITypeDesc __RPC_FAR *STDMETHODCALLTYPE get_Type( void) = 0;
        
        virtual /* [helpstring][propget] */ int STDMETHODCALLTYPE get_IDLFlags( void) = 0;
        
        virtual /* [helpstring][propget] */ OBJTYPE STDMETHODCALLTYPE get_Kind( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IParameterVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IParameter __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *ppvObj,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IParameter __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IParameter __RPC_FAR * This,
            /* [retval][out] */ unsigned long __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IParameter __RPC_FAR * This,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *pctinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IParameter __RPC_FAR * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void __RPC_FAR *__RPC_FAR *pptinfo,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IParameter __RPC_FAR * This,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ signed char __RPC_FAR *__RPC_FAR *rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long __RPC_FAR *rgdispid,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IParameter __RPC_FAR * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ GUID __RPC_FAR *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [out][idldescattr] */ VARIANT __RPC_FAR *pvarResult,
            /* [out][idldescattr] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT __RPC_FAR *puArgErr,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_CMyDispatchDestructor )( 
            IParameter __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_LoadTypeInfo )( 
            IParameter __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_RaiseException )( 
            IParameter __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_GetInterfaceID )( 
            IParameter __RPC_FAR * This,
            /* [retval][out] */ void __RPC_FAR *retval);
        
        /* [helpstring][propget] */ BSTR ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IParameter __RPC_FAR * This);
        
        /* [helpstring][propget] */ ITypeDesc __RPC_FAR *( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IParameter __RPC_FAR * This);
        
        /* [helpstring][propget] */ int ( STDMETHODCALLTYPE __RPC_FAR *get_IDLFlags )( 
            IParameter __RPC_FAR * This);
        
        /* [helpstring][propget] */ OBJTYPE ( STDMETHODCALLTYPE __RPC_FAR *get_Kind )( 
            IParameter __RPC_FAR * This);
        
        END_INTERFACE
    } IParameterVtbl;

    interface IParameter
    {
        CONST_VTBL struct IParameterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IParameter_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define IParameter_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define IParameter_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define IParameter_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define IParameter_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define IParameter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define IParameter_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define IParameter__CMyDispatchDestructor(This,retval)	\
    (This)->lpVtbl -> _CMyDispatchDestructor(This,retval)

#define IParameter__LoadTypeInfo(This,retval)	\
    (This)->lpVtbl -> _LoadTypeInfo(This,retval)

#define IParameter__RaiseException(This,retval)	\
    (This)->lpVtbl -> _RaiseException(This,retval)

#define IParameter__GetInterfaceID(This,retval)	\
    (This)->lpVtbl -> _GetInterfaceID(This,retval)


#define IParameter_get_Name(This)	\
    (This)->lpVtbl -> get_Name(This)

#define IParameter_get_Type(This)	\
    (This)->lpVtbl -> get_Type(This)

#define IParameter_get_IDLFlags(This)	\
    (This)->lpVtbl -> get_IDLFlags(This)

#define IParameter_get_Kind(This)	\
    (This)->lpVtbl -> get_Kind(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ BSTR STDMETHODCALLTYPE IParameter_get_Name_Proxy( 
    IParameter __RPC_FAR * This);


void __RPC_STUB IParameter_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ ITypeDesc __RPC_FAR *STDMETHODCALLTYPE IParameter_get_Type_Proxy( 
    IParameter __RPC_FAR * This);


void __RPC_STUB IParameter_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ int STDMETHODCALLTYPE IParameter_get_IDLFlags_Proxy( 
    IParameter __RPC_FAR * This);


void __RPC_STUB IParameter_get_IDLFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ OBJTYPE STDMETHODCALLTYPE IParameter_get_Kind_Proxy( 
    IParameter __RPC_FAR * This);


void __RPC_STUB IParameter_get_Kind_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IParameter_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_BrowseHelper,0x19FEEEC1,0x4104,0x101B,0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1);

#ifdef __cplusplus

class DECLSPEC_UUID("19FEEEC1-4104-101B-B826-00DD01103DE1")
BrowseHelper;
#endif
#endif /* __BrowseHelper_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
