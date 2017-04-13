/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.76 */
/* at Wed Sep 24 14:39:38 1997
 */
/* Compiler settings for .\stlcoll.idl:
	Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
	error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __stlcoll_h__
#define __stlcoll_h__

#ifdef __cplusplus
extern "C"{
#endif

/* Forward Declarations */

#ifndef __IStlMaps_FWD_DEFINED__
#define __IStlMaps_FWD_DEFINED__
typedef interface IStlMaps IStlMaps;
#endif  /* __IStlMaps_FWD_DEFINED__ */


#ifndef __IStlMapStringToMyObject_FWD_DEFINED__
#define __IStlMapStringToMyObject_FWD_DEFINED__
typedef interface IStlMapStringToMyObject IStlMapStringToMyObject;
#endif  /* __IStlMapStringToMyObject_FWD_DEFINED__ */


#ifndef __IStlMapDWordToMyStruct_FWD_DEFINED__
#define __IStlMapDWordToMyStruct_FWD_DEFINED__
typedef interface IStlMapDWordToMyStruct IStlMapDWordToMyStruct;
#endif  /* __IStlMapDWordToMyStruct_FWD_DEFINED__ */


#ifndef __IStlMapStringToString_FWD_DEFINED__
#define __IStlMapStringToString_FWD_DEFINED__
typedef interface IStlMapStringToString IStlMapStringToString;
#endif  /* __IStlMapStringToString_FWD_DEFINED__ */


#ifndef __IStlLists_FWD_DEFINED__
#define __IStlLists_FWD_DEFINED__
typedef interface IStlLists IStlLists;
#endif  /* __IStlLists_FWD_DEFINED__ */


#ifndef __IStlStringList_FWD_DEFINED__
#define __IStlStringList_FWD_DEFINED__
typedef interface IStlStringList IStlStringList;
#endif  /* __IStlStringList_FWD_DEFINED__ */


#ifndef __IStlMyStructList_FWD_DEFINED__
#define __IStlMyStructList_FWD_DEFINED__
typedef interface IStlMyStructList IStlMyStructList;
#endif  /* __IStlMyStructList_FWD_DEFINED__ */


#ifndef __IStlintList_FWD_DEFINED__
#define __IStlintList_FWD_DEFINED__
typedef interface IStlintList IStlintList;
#endif  /* __IStlintList_FWD_DEFINED__ */


#ifndef __IStlArrays_FWD_DEFINED__
#define __IStlArrays_FWD_DEFINED__
typedef interface IStlArrays IStlArrays;
#endif  /* __IStlArrays_FWD_DEFINED__ */


#ifndef __IStlDWordArray_FWD_DEFINED__
#define __IStlDWordArray_FWD_DEFINED__
typedef interface IStlDWordArray IStlDWordArray;
#endif  /* __IStlDWordArray_FWD_DEFINED__ */


#ifndef __IStlMyObjectArray_FWD_DEFINED__
#define __IStlMyObjectArray_FWD_DEFINED__
typedef interface IStlMyObjectArray IStlMyObjectArray;
#endif  /* __IStlMyObjectArray_FWD_DEFINED__ */


#ifndef __IStlPointArray_FWD_DEFINED__
#define __IStlPointArray_FWD_DEFINED__
typedef interface IStlPointArray IStlPointArray;
#endif  /* __IStlPointArray_FWD_DEFINED__ */


#ifndef __CStlMaps_FWD_DEFINED__
#define __CStlMaps_FWD_DEFINED__

#ifdef __cplusplus
typedef class CStlMaps CStlMaps;
#else
typedef struct CStlMaps CStlMaps;
#endif /* __cplusplus */

#endif  /* __CStlMaps_FWD_DEFINED__ */


#ifndef __CStlMapStringToMyObject_FWD_DEFINED__
#define __CStlMapStringToMyObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class CStlMapStringToMyObject CStlMapStringToMyObject;
#else
typedef struct CStlMapStringToMyObject CStlMapStringToMyObject;
#endif /* __cplusplus */

#endif  /* __CStlMapStringToMyObject_FWD_DEFINED__ */


#ifndef __CStlMapDWordToMyStruct_FWD_DEFINED__
#define __CStlMapDWordToMyStruct_FWD_DEFINED__

#ifdef __cplusplus
typedef class CStlMapDWordToMyStruct CStlMapDWordToMyStruct;
#else
typedef struct CStlMapDWordToMyStruct CStlMapDWordToMyStruct;
#endif /* __cplusplus */

#endif  /* __CStlMapDWordToMyStruct_FWD_DEFINED__ */


#ifndef __CStlMapStringToString_FWD_DEFINED__
#define __CStlMapStringToString_FWD_DEFINED__

#ifdef __cplusplus
typedef class CStlMapStringToString CStlMapStringToString;
#else
typedef struct CStlMapStringToString CStlMapStringToString;
#endif /* __cplusplus */

#endif  /* __CStlMapStringToString_FWD_DEFINED__ */


#ifndef __CStlLists_FWD_DEFINED__
#define __CStlLists_FWD_DEFINED__

#ifdef __cplusplus
typedef class CStlLists CStlLists;
#else
typedef struct CStlLists CStlLists;
#endif /* __cplusplus */

#endif  /* __CStlLists_FWD_DEFINED__ */


#ifndef __CStlArrays_FWD_DEFINED__
#define __CStlArrays_FWD_DEFINED__

#ifdef __cplusplus
typedef class CStlArrays CStlArrays;
#else
typedef struct CStlArrays CStlArrays;
#endif /* __cplusplus */

#endif  /* __CStlArrays_FWD_DEFINED__ */


#ifndef __CStlDWordArray_FWD_DEFINED__
#define __CStlDWordArray_FWD_DEFINED__

#ifdef __cplusplus
typedef class CStlDWordArray CStlDWordArray;
#else
typedef struct CStlDWordArray CStlDWordArray;
#endif /* __cplusplus */

#endif  /* __CStlDWordArray_FWD_DEFINED__ */


/* header files for imported files */
#include "idata.h"
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * );

#ifndef __IStlMaps_INTERFACE_DEFINED__
#define __IStlMaps_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IStlMaps
 * at Wed Sep 24 14:39:38 1997
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][uuid][object] */



EXTERN_C const IID IID_IStlMaps;

#if defined(__cplusplus) && !defined(CINTERFACE)

	interface DECLSPEC_UUID("7CE086C9-3E78-11D0-AE6B-00C04FD7D06E")
	IStlMaps : public IUnknown
	{
	public:
	};

#else   /* C style interface */

	typedef struct IStlMapsVtbl
	{
		BEGIN_INTERFACE

		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
			IStlMaps __RPC_FAR * This,
			/* [in] */ REFIID riid,
			/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
			IStlMaps __RPC_FAR * This);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
			IStlMaps __RPC_FAR * This);

		END_INTERFACE
	} IStlMapsVtbl;

	interface IStlMaps
	{
		CONST_VTBL struct IStlMapsVtbl __RPC_FAR *lpVtbl;
	};



#ifdef COBJMACROS


#define IStlMaps_QueryInterface(This,riid,ppvObject)    \
	(This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStlMaps_AddRef(This)   \
	(This)->lpVtbl -> AddRef(This)

#define IStlMaps_Release(This)  \
	(This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif  /* C style interface */




#endif  /* __IStlMaps_INTERFACE_DEFINED__ */


#ifndef __IStlMapStringToMyObject_INTERFACE_DEFINED__
#define __IStlMapStringToMyObject_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IStlMapStringToMyObject
 * at Wed Sep 24 14:39:38 1997
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][uuid][object] */



EXTERN_C const IID IID_IStlMapStringToMyObject;

#if defined(__cplusplus) && !defined(CINTERFACE)

	interface DECLSPEC_UUID("7CE086CE-3E78-11D0-AE6B-00C04FD7D06E")
	IStlMapStringToMyObject : public IUnknown
	{
	public:
		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Map(
			/* [in] */ BSTR str,
			/* [retval][out] */ IMyStruct __RPC_FAR *__RPC_FAR *obj) = 0;

		virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Map(
			/* [in] */ BSTR str,
			/* [in] */ IMyStruct __RPC_FAR *obj) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE Lookup(
			/* [in] */ BSTR str,
			IMyStruct __RPC_FAR *__RPC_FAR *obj,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE First( void) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE Next(
			/* [out] */ BSTR __RPC_FAR *str,
			/* [out] */ IMyStruct __RPC_FAR *__RPC_FAR *obj,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b) = 0;

		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Remove(
			/* [retval][out] */ BSTR __RPC_FAR *str) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;

		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count(
			/* [retval][out] */ UINT __RPC_FAR *dw) = 0;

	};

#else   /* C style interface */

	typedef struct IStlMapStringToMyObjectVtbl
	{
		BEGIN_INTERFACE

		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
			IStlMapStringToMyObject __RPC_FAR * This,
			/* [in] */ REFIID riid,
			/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
			IStlMapStringToMyObject __RPC_FAR * This);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
			IStlMapStringToMyObject __RPC_FAR * This);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Map )(
			IStlMapStringToMyObject __RPC_FAR * This,
			/* [in] */ BSTR str,
			/* [retval][out] */ IMyStruct __RPC_FAR *__RPC_FAR *obj);

		/* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Map )(
			IStlMapStringToMyObject __RPC_FAR * This,
			/* [in] */ BSTR str,
			/* [in] */ IMyStruct __RPC_FAR *obj);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Lookup )(
			IStlMapStringToMyObject __RPC_FAR * This,
			/* [in] */ BSTR str,
			IMyStruct __RPC_FAR *__RPC_FAR *obj,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *First )(
			IStlMapStringToMyObject __RPC_FAR * This);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )(
			IStlMapStringToMyObject __RPC_FAR * This,
			/* [out] */ BSTR __RPC_FAR *str,
			/* [out] */ IMyStruct __RPC_FAR *__RPC_FAR *obj,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Remove )(
			IStlMapStringToMyObject __RPC_FAR * This,
			/* [retval][out] */ BSTR __RPC_FAR *str);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAll )(
			IStlMapStringToMyObject __RPC_FAR * This);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )(
			IStlMapStringToMyObject __RPC_FAR * This,
			/* [retval][out] */ UINT __RPC_FAR *dw);

		END_INTERFACE
	} IStlMapStringToMyObjectVtbl;

	interface IStlMapStringToMyObject
	{
		CONST_VTBL struct IStlMapStringToMyObjectVtbl __RPC_FAR *lpVtbl;
	};



#ifdef COBJMACROS


#define IStlMapStringToMyObject_QueryInterface(This,riid,ppvObject) \
	(This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStlMapStringToMyObject_AddRef(This)    \
	(This)->lpVtbl -> AddRef(This)

#define IStlMapStringToMyObject_Release(This)   \
	(This)->lpVtbl -> Release(This)


#define IStlMapStringToMyObject_get_Map(This,str,obj)   \
	(This)->lpVtbl -> get_Map(This,str,obj)

#define IStlMapStringToMyObject_put_Map(This,str,obj)   \
	(This)->lpVtbl -> put_Map(This,str,obj)

#define IStlMapStringToMyObject_Lookup(This,str,obj,b)  \
	(This)->lpVtbl -> Lookup(This,str,obj,b)

#define IStlMapStringToMyObject_First(This) \
	(This)->lpVtbl -> First(This)

#define IStlMapStringToMyObject_Next(This,str,obj,b)    \
	(This)->lpVtbl -> Next(This,str,obj,b)

#define IStlMapStringToMyObject_get_Remove(This,str)    \
	(This)->lpVtbl -> get_Remove(This,str)

#define IStlMapStringToMyObject_RemoveAll(This) \
	(This)->lpVtbl -> RemoveAll(This)

#define IStlMapStringToMyObject_get_Count(This,dw)  \
	(This)->lpVtbl -> get_Count(This,dw)

#endif /* COBJMACROS */


#endif  /* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlMapStringToMyObject_get_Map_Proxy(
	IStlMapStringToMyObject __RPC_FAR * This,
	/* [in] */ BSTR str,
	/* [retval][out] */ IMyStruct __RPC_FAR *__RPC_FAR *obj);


void __RPC_STUB IStlMapStringToMyObject_get_Map_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IStlMapStringToMyObject_put_Map_Proxy(
	IStlMapStringToMyObject __RPC_FAR * This,
	/* [in] */ BSTR str,
	/* [in] */ IMyStruct __RPC_FAR *obj);


void __RPC_STUB IStlMapStringToMyObject_put_Map_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlMapStringToMyObject_Lookup_Proxy(
	IStlMapStringToMyObject __RPC_FAR * This,
	/* [in] */ BSTR str,
	IMyStruct __RPC_FAR *__RPC_FAR *obj,
	/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);


void __RPC_STUB IStlMapStringToMyObject_Lookup_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlMapStringToMyObject_First_Proxy(
	IStlMapStringToMyObject __RPC_FAR * This);


void __RPC_STUB IStlMapStringToMyObject_First_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlMapStringToMyObject_Next_Proxy(
	IStlMapStringToMyObject __RPC_FAR * This,
	/* [out] */ BSTR __RPC_FAR *str,
	/* [out] */ IMyStruct __RPC_FAR *__RPC_FAR *obj,
	/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);


void __RPC_STUB IStlMapStringToMyObject_Next_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlMapStringToMyObject_get_Remove_Proxy(
	IStlMapStringToMyObject __RPC_FAR * This,
	/* [retval][out] */ BSTR __RPC_FAR *str);


void __RPC_STUB IStlMapStringToMyObject_get_Remove_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlMapStringToMyObject_RemoveAll_Proxy(
	IStlMapStringToMyObject __RPC_FAR * This);


void __RPC_STUB IStlMapStringToMyObject_RemoveAll_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlMapStringToMyObject_get_Count_Proxy(
	IStlMapStringToMyObject __RPC_FAR * This,
	/* [retval][out] */ UINT __RPC_FAR *dw);


void __RPC_STUB IStlMapStringToMyObject_get_Count_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);



#endif  /* __IStlMapStringToMyObject_INTERFACE_DEFINED__ */


#ifndef __IStlMapDWordToMyStruct_INTERFACE_DEFINED__
#define __IStlMapDWordToMyStruct_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IStlMapDWordToMyStruct
 * at Wed Sep 24 14:39:38 1997
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][uuid][object] */



EXTERN_C const IID IID_IStlMapDWordToMyStruct;

#if defined(__cplusplus) && !defined(CINTERFACE)

	interface DECLSPEC_UUID("7CE086D3-3E78-11D0-AE6B-00C04FD7D06E")
	IStlMapDWordToMyStruct : public IUnknown
	{
	public:
		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Map(
			/* [in] */ DWORD dw,
			/* [retval][out] */ IMyStruct __RPC_FAR *__RPC_FAR *str) = 0;

		virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Map(
			/* [in] */ DWORD dw,
			/* [in] */ IMyStruct __RPC_FAR *str) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE Lookup(
			/* [in] */ DWORD dw,
			/* [out] */ IMyStruct __RPC_FAR *__RPC_FAR *str,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE First( void) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE Next(
			/* [out] */ DWORD __RPC_FAR *dw,
			/* [out] */ IMyStruct __RPC_FAR *__RPC_FAR *str,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b) = 0;

		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Remove(
			/* [retval][out] */ DWORD __RPC_FAR *str) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;

		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count(
			/* [retval][out] */ UINT __RPC_FAR *dw) = 0;

	};

#else   /* C style interface */

	typedef struct IStlMapDWordToMyStructVtbl
	{
		BEGIN_INTERFACE

		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
			IStlMapDWordToMyStruct __RPC_FAR * This,
			/* [in] */ REFIID riid,
			/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
			IStlMapDWordToMyStruct __RPC_FAR * This);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
			IStlMapDWordToMyStruct __RPC_FAR * This);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Map )(
			IStlMapDWordToMyStruct __RPC_FAR * This,
			/* [in] */ DWORD dw,
			/* [retval][out] */ IMyStruct __RPC_FAR *__RPC_FAR *str);

		/* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Map )(
			IStlMapDWordToMyStruct __RPC_FAR * This,
			/* [in] */ DWORD dw,
			/* [in] */ IMyStruct __RPC_FAR *str);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Lookup )(
			IStlMapDWordToMyStruct __RPC_FAR * This,
			/* [in] */ DWORD dw,
			/* [out] */ IMyStruct __RPC_FAR *__RPC_FAR *str,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *First )(
			IStlMapDWordToMyStruct __RPC_FAR * This);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )(
			IStlMapDWordToMyStruct __RPC_FAR * This,
			/* [out] */ DWORD __RPC_FAR *dw,
			/* [out] */ IMyStruct __RPC_FAR *__RPC_FAR *str,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Remove )(
			IStlMapDWordToMyStruct __RPC_FAR * This,
			/* [retval][out] */ DWORD __RPC_FAR *str);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAll )(
			IStlMapDWordToMyStruct __RPC_FAR * This);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )(
			IStlMapDWordToMyStruct __RPC_FAR * This,
			/* [retval][out] */ UINT __RPC_FAR *dw);

		END_INTERFACE
	} IStlMapDWordToMyStructVtbl;

	interface IStlMapDWordToMyStruct
	{
		CONST_VTBL struct IStlMapDWordToMyStructVtbl __RPC_FAR *lpVtbl;
	};



#ifdef COBJMACROS


#define IStlMapDWordToMyStruct_QueryInterface(This,riid,ppvObject)  \
	(This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStlMapDWordToMyStruct_AddRef(This) \
	(This)->lpVtbl -> AddRef(This)

#define IStlMapDWordToMyStruct_Release(This)    \
	(This)->lpVtbl -> Release(This)


#define IStlMapDWordToMyStruct_get_Map(This,dw,str) \
	(This)->lpVtbl -> get_Map(This,dw,str)

#define IStlMapDWordToMyStruct_put_Map(This,dw,str) \
	(This)->lpVtbl -> put_Map(This,dw,str)

#define IStlMapDWordToMyStruct_Lookup(This,dw,str,b)    \
	(This)->lpVtbl -> Lookup(This,dw,str,b)

#define IStlMapDWordToMyStruct_First(This)  \
	(This)->lpVtbl -> First(This)

#define IStlMapDWordToMyStruct_Next(This,dw,str,b)  \
	(This)->lpVtbl -> Next(This,dw,str,b)

#define IStlMapDWordToMyStruct_get_Remove(This,str) \
	(This)->lpVtbl -> get_Remove(This,str)

#define IStlMapDWordToMyStruct_RemoveAll(This)  \
	(This)->lpVtbl -> RemoveAll(This)

#define IStlMapDWordToMyStruct_get_Count(This,dw)   \
	(This)->lpVtbl -> get_Count(This,dw)

#endif /* COBJMACROS */


#endif  /* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlMapDWordToMyStruct_get_Map_Proxy(
	IStlMapDWordToMyStruct __RPC_FAR * This,
	/* [in] */ DWORD dw,
	/* [retval][out] */ IMyStruct __RPC_FAR *__RPC_FAR *str);


void __RPC_STUB IStlMapDWordToMyStruct_get_Map_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IStlMapDWordToMyStruct_put_Map_Proxy(
	IStlMapDWordToMyStruct __RPC_FAR * This,
	/* [in] */ DWORD dw,
	/* [in] */ IMyStruct __RPC_FAR *str);


void __RPC_STUB IStlMapDWordToMyStruct_put_Map_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlMapDWordToMyStruct_Lookup_Proxy(
	IStlMapDWordToMyStruct __RPC_FAR * This,
	/* [in] */ DWORD dw,
	/* [out] */ IMyStruct __RPC_FAR *__RPC_FAR *str,
	/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);


void __RPC_STUB IStlMapDWordToMyStruct_Lookup_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlMapDWordToMyStruct_First_Proxy(
	IStlMapDWordToMyStruct __RPC_FAR * This);


void __RPC_STUB IStlMapDWordToMyStruct_First_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlMapDWordToMyStruct_Next_Proxy(
	IStlMapDWordToMyStruct __RPC_FAR * This,
	/* [out] */ DWORD __RPC_FAR *dw,
	/* [out] */ IMyStruct __RPC_FAR *__RPC_FAR *str,
	/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);


void __RPC_STUB IStlMapDWordToMyStruct_Next_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlMapDWordToMyStruct_get_Remove_Proxy(
	IStlMapDWordToMyStruct __RPC_FAR * This,
	/* [retval][out] */ DWORD __RPC_FAR *str);


void __RPC_STUB IStlMapDWordToMyStruct_get_Remove_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlMapDWordToMyStruct_RemoveAll_Proxy(
	IStlMapDWordToMyStruct __RPC_FAR * This);


void __RPC_STUB IStlMapDWordToMyStruct_RemoveAll_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlMapDWordToMyStruct_get_Count_Proxy(
	IStlMapDWordToMyStruct __RPC_FAR * This,
	/* [retval][out] */ UINT __RPC_FAR *dw);


void __RPC_STUB IStlMapDWordToMyStruct_get_Count_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);



#endif  /* __IStlMapDWordToMyStruct_INTERFACE_DEFINED__ */


#ifndef __IStlMapStringToString_INTERFACE_DEFINED__
#define __IStlMapStringToString_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IStlMapStringToString
 * at Wed Sep 24 14:39:38 1997
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][uuid][object] */



EXTERN_C const IID IID_IStlMapStringToString;

#if defined(__cplusplus) && !defined(CINTERFACE)

	interface DECLSPEC_UUID("7CE086D8-3E78-11D0-AE6B-00C04FD7D06E")
	IStlMapStringToString : public IUnknown
	{
	public:
		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Map(
			/* [in] */ BSTR str1,
			/* [retval][out] */ BSTR __RPC_FAR *str2) = 0;

		virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Map(
			/* [in] */ BSTR str1,
			/* [in] */ BSTR str2) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE Lookup(
			/* [in] */ BSTR str1,
			/* [out] */ BSTR __RPC_FAR *str2,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE First( void) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE Next(
			/* [out] */ BSTR __RPC_FAR *str1,
			/* [out] */ BSTR __RPC_FAR *str2,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b) = 0;

		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Remove(
			/* [retval][out] */ BSTR __RPC_FAR *str) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;

		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count(
			/* [retval][out] */ UINT __RPC_FAR *dw) = 0;

	};

#else   /* C style interface */

	typedef struct IStlMapStringToStringVtbl
	{
		BEGIN_INTERFACE

		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
			IStlMapStringToString __RPC_FAR * This,
			/* [in] */ REFIID riid,
			/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
			IStlMapStringToString __RPC_FAR * This);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
			IStlMapStringToString __RPC_FAR * This);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Map )(
			IStlMapStringToString __RPC_FAR * This,
			/* [in] */ BSTR str1,
			/* [retval][out] */ BSTR __RPC_FAR *str2);

		/* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Map )(
			IStlMapStringToString __RPC_FAR * This,
			/* [in] */ BSTR str1,
			/* [in] */ BSTR str2);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Lookup )(
			IStlMapStringToString __RPC_FAR * This,
			/* [in] */ BSTR str1,
			/* [out] */ BSTR __RPC_FAR *str2,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *First )(
			IStlMapStringToString __RPC_FAR * This);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )(
			IStlMapStringToString __RPC_FAR * This,
			/* [out] */ BSTR __RPC_FAR *str1,
			/* [out] */ BSTR __RPC_FAR *str2,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Remove )(
			IStlMapStringToString __RPC_FAR * This,
			/* [retval][out] */ BSTR __RPC_FAR *str);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAll )(
			IStlMapStringToString __RPC_FAR * This);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )(
			IStlMapStringToString __RPC_FAR * This,
			/* [retval][out] */ UINT __RPC_FAR *dw);

		END_INTERFACE
	} IStlMapStringToStringVtbl;

	interface IStlMapStringToString
	{
		CONST_VTBL struct IStlMapStringToStringVtbl __RPC_FAR *lpVtbl;
	};



#ifdef COBJMACROS


#define IStlMapStringToString_QueryInterface(This,riid,ppvObject)   \
	(This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStlMapStringToString_AddRef(This)  \
	(This)->lpVtbl -> AddRef(This)

#define IStlMapStringToString_Release(This) \
	(This)->lpVtbl -> Release(This)


#define IStlMapStringToString_get_Map(This,str1,str2)   \
	(This)->lpVtbl -> get_Map(This,str1,str2)

#define IStlMapStringToString_put_Map(This,str1,str2)   \
	(This)->lpVtbl -> put_Map(This,str1,str2)

#define IStlMapStringToString_Lookup(This,str1,str2,b)  \
	(This)->lpVtbl -> Lookup(This,str1,str2,b)

#define IStlMapStringToString_First(This)   \
	(This)->lpVtbl -> First(This)

#define IStlMapStringToString_Next(This,str1,str2,b)    \
	(This)->lpVtbl -> Next(This,str1,str2,b)

#define IStlMapStringToString_get_Remove(This,str)  \
	(This)->lpVtbl -> get_Remove(This,str)

#define IStlMapStringToString_RemoveAll(This)   \
	(This)->lpVtbl -> RemoveAll(This)

#define IStlMapStringToString_get_Count(This,dw)    \
	(This)->lpVtbl -> get_Count(This,dw)

#endif /* COBJMACROS */


#endif  /* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlMapStringToString_get_Map_Proxy(
	IStlMapStringToString __RPC_FAR * This,
	/* [in] */ BSTR str1,
	/* [retval][out] */ BSTR __RPC_FAR *str2);


void __RPC_STUB IStlMapStringToString_get_Map_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IStlMapStringToString_put_Map_Proxy(
	IStlMapStringToString __RPC_FAR * This,
	/* [in] */ BSTR str1,
	/* [in] */ BSTR str2);


void __RPC_STUB IStlMapStringToString_put_Map_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlMapStringToString_Lookup_Proxy(
	IStlMapStringToString __RPC_FAR * This,
	/* [in] */ BSTR str1,
	/* [out] */ BSTR __RPC_FAR *str2,
	/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);


void __RPC_STUB IStlMapStringToString_Lookup_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlMapStringToString_First_Proxy(
	IStlMapStringToString __RPC_FAR * This);


void __RPC_STUB IStlMapStringToString_First_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlMapStringToString_Next_Proxy(
	IStlMapStringToString __RPC_FAR * This,
	/* [out] */ BSTR __RPC_FAR *str1,
	/* [out] */ BSTR __RPC_FAR *str2,
	/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);


void __RPC_STUB IStlMapStringToString_Next_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlMapStringToString_get_Remove_Proxy(
	IStlMapStringToString __RPC_FAR * This,
	/* [retval][out] */ BSTR __RPC_FAR *str);


void __RPC_STUB IStlMapStringToString_get_Remove_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlMapStringToString_RemoveAll_Proxy(
	IStlMapStringToString __RPC_FAR * This);


void __RPC_STUB IStlMapStringToString_RemoveAll_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlMapStringToString_get_Count_Proxy(
	IStlMapStringToString __RPC_FAR * This,
	/* [retval][out] */ UINT __RPC_FAR *dw);


void __RPC_STUB IStlMapStringToString_get_Count_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);



#endif  /* __IStlMapStringToString_INTERFACE_DEFINED__ */


#ifndef __IStlLists_INTERFACE_DEFINED__
#define __IStlLists_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IStlLists
 * at Wed Sep 24 14:39:38 1997
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][uuid][object] */



EXTERN_C const IID IID_IStlLists;

#if defined(__cplusplus) && !defined(CINTERFACE)

	interface DECLSPEC_UUID("7CE086DD-3E78-11D0-AE6B-00C04FD7D06E")
	IStlLists : public IUnknown
	{
	public:
	};

#else   /* C style interface */

	typedef struct IStlListsVtbl
	{
		BEGIN_INTERFACE

		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
			IStlLists __RPC_FAR * This,
			/* [in] */ REFIID riid,
			/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
			IStlLists __RPC_FAR * This);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
			IStlLists __RPC_FAR * This);

		END_INTERFACE
	} IStlListsVtbl;

	interface IStlLists
	{
		CONST_VTBL struct IStlListsVtbl __RPC_FAR *lpVtbl;
	};



#ifdef COBJMACROS


#define IStlLists_QueryInterface(This,riid,ppvObject)   \
	(This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStlLists_AddRef(This)  \
	(This)->lpVtbl -> AddRef(This)

#define IStlLists_Release(This) \
	(This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif  /* C style interface */




#endif  /* __IStlLists_INTERFACE_DEFINED__ */


#ifndef __IStlStringList_INTERFACE_DEFINED__
#define __IStlStringList_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IStlStringList
 * at Wed Sep 24 14:39:38 1997
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][uuid][object] */



EXTERN_C const IID IID_IStlStringList;

#if defined(__cplusplus) && !defined(CINTERFACE)

	interface DECLSPEC_UUID("7CE086E2-3E78-11D0-AE6B-00C04FD7D06E")
	IStlStringList : public IUnknown
	{
	public:
		virtual /* [id] */ HRESULT STDMETHODCALLTYPE Find(
			/* [in] */ BSTR str,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b) = 0;

		virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_SetAt(
			/* [in] */ BSTR str) = 0;

		virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Add(
			/* [in] */ BSTR str) = 0;

		virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_InsertBefore(
			/* [in] */ BSTR str) = 0;

		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Remove(
			/* [retval][out] */ BSTR __RPC_FAR *str) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE First( void) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE Next(
			/* [out] */ BSTR __RPC_FAR *str,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b) = 0;

		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count(
			/* [retval][out] */ UINT __RPC_FAR *dw) = 0;

	};

#else   /* C style interface */

	typedef struct IStlStringListVtbl
	{
		BEGIN_INTERFACE

		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
			IStlStringList __RPC_FAR * This,
			/* [in] */ REFIID riid,
			/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
			IStlStringList __RPC_FAR * This);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
			IStlStringList __RPC_FAR * This);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Find )(
			IStlStringList __RPC_FAR * This,
			/* [in] */ BSTR str,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);

		/* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SetAt )(
			IStlStringList __RPC_FAR * This,
			/* [in] */ BSTR str);

		/* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Add )(
			IStlStringList __RPC_FAR * This,
			/* [in] */ BSTR str);

		/* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InsertBefore )(
			IStlStringList __RPC_FAR * This,
			/* [in] */ BSTR str);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Remove )(
			IStlStringList __RPC_FAR * This,
			/* [retval][out] */ BSTR __RPC_FAR *str);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAll )(
			IStlStringList __RPC_FAR * This);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *First )(
			IStlStringList __RPC_FAR * This);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )(
			IStlStringList __RPC_FAR * This,
			/* [out] */ BSTR __RPC_FAR *str,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )(
			IStlStringList __RPC_FAR * This,
			/* [retval][out] */ UINT __RPC_FAR *dw);

		END_INTERFACE
	} IStlStringListVtbl;

	interface IStlStringList
	{
		CONST_VTBL struct IStlStringListVtbl __RPC_FAR *lpVtbl;
	};



#ifdef COBJMACROS


#define IStlStringList_QueryInterface(This,riid,ppvObject)  \
	(This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStlStringList_AddRef(This) \
	(This)->lpVtbl -> AddRef(This)

#define IStlStringList_Release(This)    \
	(This)->lpVtbl -> Release(This)


#define IStlStringList_Find(This,str,b) \
	(This)->lpVtbl -> Find(This,str,b)

#define IStlStringList_put_SetAt(This,str)  \
	(This)->lpVtbl -> put_SetAt(This,str)

#define IStlStringList_put_Add(This,str)    \
	(This)->lpVtbl -> put_Add(This,str)

#define IStlStringList_put_InsertBefore(This,str)   \
	(This)->lpVtbl -> put_InsertBefore(This,str)

#define IStlStringList_get_Remove(This,str) \
	(This)->lpVtbl -> get_Remove(This,str)

#define IStlStringList_RemoveAll(This)  \
	(This)->lpVtbl -> RemoveAll(This)

#define IStlStringList_First(This)  \
	(This)->lpVtbl -> First(This)

#define IStlStringList_Next(This,str,b) \
	(This)->lpVtbl -> Next(This,str,b)

#define IStlStringList_get_Count(This,dw)   \
	(This)->lpVtbl -> get_Count(This,dw)

#endif /* COBJMACROS */


#endif  /* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IStlStringList_Find_Proxy(
	IStlStringList __RPC_FAR * This,
	/* [in] */ BSTR str,
	/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);


void __RPC_STUB IStlStringList_Find_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IStlStringList_put_SetAt_Proxy(
	IStlStringList __RPC_FAR * This,
	/* [in] */ BSTR str);


void __RPC_STUB IStlStringList_put_SetAt_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IStlStringList_put_Add_Proxy(
	IStlStringList __RPC_FAR * This,
	/* [in] */ BSTR str);


void __RPC_STUB IStlStringList_put_Add_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IStlStringList_put_InsertBefore_Proxy(
	IStlStringList __RPC_FAR * This,
	/* [in] */ BSTR str);


void __RPC_STUB IStlStringList_put_InsertBefore_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlStringList_get_Remove_Proxy(
	IStlStringList __RPC_FAR * This,
	/* [retval][out] */ BSTR __RPC_FAR *str);


void __RPC_STUB IStlStringList_get_Remove_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlStringList_RemoveAll_Proxy(
	IStlStringList __RPC_FAR * This);


void __RPC_STUB IStlStringList_RemoveAll_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlStringList_First_Proxy(
	IStlStringList __RPC_FAR * This);


void __RPC_STUB IStlStringList_First_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlStringList_Next_Proxy(
	IStlStringList __RPC_FAR * This,
	/* [out] */ BSTR __RPC_FAR *str,
	/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);


void __RPC_STUB IStlStringList_Next_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlStringList_get_Count_Proxy(
	IStlStringList __RPC_FAR * This,
	/* [retval][out] */ UINT __RPC_FAR *dw);


void __RPC_STUB IStlStringList_get_Count_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);



#endif  /* __IStlStringList_INTERFACE_DEFINED__ */


#ifndef __IStlMyStructList_INTERFACE_DEFINED__
#define __IStlMyStructList_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IStlMyStructList
 * at Wed Sep 24 14:39:38 1997
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][uuid][object] */



EXTERN_C const IID IID_IStlMyStructList;

#if defined(__cplusplus) && !defined(CINTERFACE)

	interface DECLSPEC_UUID("7CE086E7-3E78-11D0-AE6B-00C04FD7D06E")
	IStlMyStructList : public IUnknown
	{
	public:
		virtual /* [id] */ HRESULT STDMETHODCALLTYPE Find(
			/* [in] */ IMyStruct __RPC_FAR *str,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b) = 0;

		virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_SetAt(
			/* [in] */ IMyStruct __RPC_FAR *str) = 0;

		virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Add(
			/* [in] */ IMyStruct __RPC_FAR *str) = 0;

		virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_InsertBefore(
			/* [in] */ IMyStruct __RPC_FAR *str) = 0;

		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Remove(
			/* [retval][out] */ IMyStruct __RPC_FAR *__RPC_FAR *str) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE First( void) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE Next(
			/* [out] */ IMyStruct __RPC_FAR *__RPC_FAR *str,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b) = 0;

		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count(
			/* [retval][out] */ UINT __RPC_FAR *dw) = 0;

	};

#else   /* C style interface */

	typedef struct IStlMyStructListVtbl
	{
		BEGIN_INTERFACE

		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
			IStlMyStructList __RPC_FAR * This,
			/* [in] */ REFIID riid,
			/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
			IStlMyStructList __RPC_FAR * This);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
			IStlMyStructList __RPC_FAR * This);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Find )(
			IStlMyStructList __RPC_FAR * This,
			/* [in] */ IMyStruct __RPC_FAR *str,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);

		/* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SetAt )(
			IStlMyStructList __RPC_FAR * This,
			/* [in] */ IMyStruct __RPC_FAR *str);

		/* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Add )(
			IStlMyStructList __RPC_FAR * This,
			/* [in] */ IMyStruct __RPC_FAR *str);

		/* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InsertBefore )(
			IStlMyStructList __RPC_FAR * This,
			/* [in] */ IMyStruct __RPC_FAR *str);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Remove )(
			IStlMyStructList __RPC_FAR * This,
			/* [retval][out] */ IMyStruct __RPC_FAR *__RPC_FAR *str);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAll )(
			IStlMyStructList __RPC_FAR * This);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *First )(
			IStlMyStructList __RPC_FAR * This);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )(
			IStlMyStructList __RPC_FAR * This,
			/* [out] */ IMyStruct __RPC_FAR *__RPC_FAR *str,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )(
			IStlMyStructList __RPC_FAR * This,
			/* [retval][out] */ UINT __RPC_FAR *dw);

		END_INTERFACE
	} IStlMyStructListVtbl;

	interface IStlMyStructList
	{
		CONST_VTBL struct IStlMyStructListVtbl __RPC_FAR *lpVtbl;
	};



#ifdef COBJMACROS


#define IStlMyStructList_QueryInterface(This,riid,ppvObject)    \
	(This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStlMyStructList_AddRef(This)   \
	(This)->lpVtbl -> AddRef(This)

#define IStlMyStructList_Release(This)  \
	(This)->lpVtbl -> Release(This)


#define IStlMyStructList_Find(This,str,b)   \
	(This)->lpVtbl -> Find(This,str,b)

#define IStlMyStructList_put_SetAt(This,str)    \
	(This)->lpVtbl -> put_SetAt(This,str)

#define IStlMyStructList_put_Add(This,str)  \
	(This)->lpVtbl -> put_Add(This,str)

#define IStlMyStructList_put_InsertBefore(This,str) \
	(This)->lpVtbl -> put_InsertBefore(This,str)

#define IStlMyStructList_get_Remove(This,str)   \
	(This)->lpVtbl -> get_Remove(This,str)

#define IStlMyStructList_RemoveAll(This)    \
	(This)->lpVtbl -> RemoveAll(This)

#define IStlMyStructList_First(This)    \
	(This)->lpVtbl -> First(This)

#define IStlMyStructList_Next(This,str,b)   \
	(This)->lpVtbl -> Next(This,str,b)

#define IStlMyStructList_get_Count(This,dw) \
	(This)->lpVtbl -> get_Count(This,dw)

#endif /* COBJMACROS */


#endif  /* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IStlMyStructList_Find_Proxy(
	IStlMyStructList __RPC_FAR * This,
	/* [in] */ IMyStruct __RPC_FAR *str,
	/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);


void __RPC_STUB IStlMyStructList_Find_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IStlMyStructList_put_SetAt_Proxy(
	IStlMyStructList __RPC_FAR * This,
	/* [in] */ IMyStruct __RPC_FAR *str);


void __RPC_STUB IStlMyStructList_put_SetAt_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IStlMyStructList_put_Add_Proxy(
	IStlMyStructList __RPC_FAR * This,
	/* [in] */ IMyStruct __RPC_FAR *str);


void __RPC_STUB IStlMyStructList_put_Add_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IStlMyStructList_put_InsertBefore_Proxy(
	IStlMyStructList __RPC_FAR * This,
	/* [in] */ IMyStruct __RPC_FAR *str);


void __RPC_STUB IStlMyStructList_put_InsertBefore_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlMyStructList_get_Remove_Proxy(
	IStlMyStructList __RPC_FAR * This,
	/* [retval][out] */ IMyStruct __RPC_FAR *__RPC_FAR *str);


void __RPC_STUB IStlMyStructList_get_Remove_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlMyStructList_RemoveAll_Proxy(
	IStlMyStructList __RPC_FAR * This);


void __RPC_STUB IStlMyStructList_RemoveAll_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlMyStructList_First_Proxy(
	IStlMyStructList __RPC_FAR * This);


void __RPC_STUB IStlMyStructList_First_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlMyStructList_Next_Proxy(
	IStlMyStructList __RPC_FAR * This,
	/* [out] */ IMyStruct __RPC_FAR *__RPC_FAR *str,
	/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);


void __RPC_STUB IStlMyStructList_Next_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlMyStructList_get_Count_Proxy(
	IStlMyStructList __RPC_FAR * This,
	/* [retval][out] */ UINT __RPC_FAR *dw);


void __RPC_STUB IStlMyStructList_get_Count_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);



#endif  /* __IStlMyStructList_INTERFACE_DEFINED__ */


#ifndef __IStlintList_INTERFACE_DEFINED__
#define __IStlintList_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IStlintList
 * at Wed Sep 24 14:39:38 1997
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][uuid][object] */



EXTERN_C const IID IID_IStlintList;

#if defined(__cplusplus) && !defined(CINTERFACE)

	interface DECLSPEC_UUID("7CE086EC-3E78-11D0-AE6B-00C04FD7D06E")
	IStlintList : public IUnknown
	{
	public:
		virtual /* [id] */ HRESULT STDMETHODCALLTYPE Find(
			/* [in] */ long n,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b) = 0;

		virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_SetAt(
			/* [in] */ long n) = 0;

		virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Add(
			/* [in] */ long n) = 0;

		virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_InsertBefore(
			/* [in] */ long n) = 0;

		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Remove(
			/* [retval][out] */ long __RPC_FAR *n) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE First( void) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE Next(
			/* [out] */ long __RPC_FAR *n,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b) = 0;

		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count(
			/* [retval][out] */ UINT __RPC_FAR *dw) = 0;

	};

#else   /* C style interface */

	typedef struct IStlintListVtbl
	{
		BEGIN_INTERFACE

		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
			IStlintList __RPC_FAR * This,
			/* [in] */ REFIID riid,
			/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
			IStlintList __RPC_FAR * This);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
			IStlintList __RPC_FAR * This);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Find )(
			IStlintList __RPC_FAR * This,
			/* [in] */ long n,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);

		/* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SetAt )(
			IStlintList __RPC_FAR * This,
			/* [in] */ long n);

		/* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Add )(
			IStlintList __RPC_FAR * This,
			/* [in] */ long n);

		/* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InsertBefore )(
			IStlintList __RPC_FAR * This,
			/* [in] */ long n);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Remove )(
			IStlintList __RPC_FAR * This,
			/* [retval][out] */ long __RPC_FAR *n);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAll )(
			IStlintList __RPC_FAR * This);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *First )(
			IStlintList __RPC_FAR * This);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )(
			IStlintList __RPC_FAR * This,
			/* [out] */ long __RPC_FAR *n,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )(
			IStlintList __RPC_FAR * This,
			/* [retval][out] */ UINT __RPC_FAR *dw);

		END_INTERFACE
	} IStlintListVtbl;

	interface IStlintList
	{
		CONST_VTBL struct IStlintListVtbl __RPC_FAR *lpVtbl;
	};



#ifdef COBJMACROS


#define IStlintList_QueryInterface(This,riid,ppvObject) \
	(This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStlintList_AddRef(This)    \
	(This)->lpVtbl -> AddRef(This)

#define IStlintList_Release(This)   \
	(This)->lpVtbl -> Release(This)


#define IStlintList_Find(This,n,b)  \
	(This)->lpVtbl -> Find(This,n,b)

#define IStlintList_put_SetAt(This,n)   \
	(This)->lpVtbl -> put_SetAt(This,n)

#define IStlintList_put_Add(This,n) \
	(This)->lpVtbl -> put_Add(This,n)

#define IStlintList_put_InsertBefore(This,n)    \
	(This)->lpVtbl -> put_InsertBefore(This,n)

#define IStlintList_get_Remove(This,n)  \
	(This)->lpVtbl -> get_Remove(This,n)

#define IStlintList_RemoveAll(This) \
	(This)->lpVtbl -> RemoveAll(This)

#define IStlintList_First(This) \
	(This)->lpVtbl -> First(This)

#define IStlintList_Next(This,n,b)  \
	(This)->lpVtbl -> Next(This,n,b)

#define IStlintList_get_Count(This,dw)  \
	(This)->lpVtbl -> get_Count(This,dw)

#endif /* COBJMACROS */


#endif  /* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IStlintList_Find_Proxy(
	IStlintList __RPC_FAR * This,
	/* [in] */ long n,
	/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);


void __RPC_STUB IStlintList_Find_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IStlintList_put_SetAt_Proxy(
	IStlintList __RPC_FAR * This,
	/* [in] */ long n);


void __RPC_STUB IStlintList_put_SetAt_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IStlintList_put_Add_Proxy(
	IStlintList __RPC_FAR * This,
	/* [in] */ long n);


void __RPC_STUB IStlintList_put_Add_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IStlintList_put_InsertBefore_Proxy(
	IStlintList __RPC_FAR * This,
	/* [in] */ long n);


void __RPC_STUB IStlintList_put_InsertBefore_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlintList_get_Remove_Proxy(
	IStlintList __RPC_FAR * This,
	/* [retval][out] */ long __RPC_FAR *n);


void __RPC_STUB IStlintList_get_Remove_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlintList_RemoveAll_Proxy(
	IStlintList __RPC_FAR * This);


void __RPC_STUB IStlintList_RemoveAll_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlintList_First_Proxy(
	IStlintList __RPC_FAR * This);


void __RPC_STUB IStlintList_First_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlintList_Next_Proxy(
	IStlintList __RPC_FAR * This,
	/* [out] */ long __RPC_FAR *n,
	/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);


void __RPC_STUB IStlintList_Next_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlintList_get_Count_Proxy(
	IStlintList __RPC_FAR * This,
	/* [retval][out] */ UINT __RPC_FAR *dw);


void __RPC_STUB IStlintList_get_Count_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);



#endif  /* __IStlintList_INTERFACE_DEFINED__ */


#ifndef __IStlArrays_INTERFACE_DEFINED__
#define __IStlArrays_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IStlArrays
 * at Wed Sep 24 14:39:38 1997
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][uuid][object] */



EXTERN_C const IID IID_IStlArrays;

#if defined(__cplusplus) && !defined(CINTERFACE)

	interface DECLSPEC_UUID("7CE086F1-3E78-11D0-AE6B-00C04FD7D06E")
	IStlArrays : public IUnknown
	{
	public:
	};

#else   /* C style interface */

	typedef struct IStlArraysVtbl
	{
		BEGIN_INTERFACE

		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
			IStlArrays __RPC_FAR * This,
			/* [in] */ REFIID riid,
			/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
			IStlArrays __RPC_FAR * This);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
			IStlArrays __RPC_FAR * This);

		END_INTERFACE
	} IStlArraysVtbl;

	interface IStlArrays
	{
		CONST_VTBL struct IStlArraysVtbl __RPC_FAR *lpVtbl;
	};



#ifdef COBJMACROS


#define IStlArrays_QueryInterface(This,riid,ppvObject)  \
	(This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStlArrays_AddRef(This) \
	(This)->lpVtbl -> AddRef(This)

#define IStlArrays_Release(This)    \
	(This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif  /* C style interface */




#endif  /* __IStlArrays_INTERFACE_DEFINED__ */


#ifndef __IStlDWordArray_INTERFACE_DEFINED__
#define __IStlDWordArray_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IStlDWordArray
 * at Wed Sep 24 14:39:38 1997
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][uuid][object] */



EXTERN_C const IID IID_IStlDWordArray;

#if defined(__cplusplus) && !defined(CINTERFACE)

	interface DECLSPEC_UUID("7CE086F6-3E78-11D0-AE6B-00C04FD7D06E")
	IStlDWordArray : public IUnknown
	{
	public:
		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Array(
			/* [in] */ long idx,
			/* [retval][out] */ DWORD __RPC_FAR *dw) = 0;

		virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Array(
			/* [in] */ long idx,
			/* [in] */ DWORD dw) = 0;

		virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Add(
			/* [in] */ DWORD dw) = 0;

		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Remove(
			/* [in] */ long idx,
			/* [retval][out] */ DWORD __RPC_FAR *dw) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE First( void) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE Next(
			/* [out] */ DWORD __RPC_FAR *pt,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b) = 0;

		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count(
			/* [retval][out] */ UINT __RPC_FAR *dw) = 0;

	};

#else   /* C style interface */

	typedef struct IStlDWordArrayVtbl
	{
		BEGIN_INTERFACE

		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
			IStlDWordArray __RPC_FAR * This,
			/* [in] */ REFIID riid,
			/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
			IStlDWordArray __RPC_FAR * This);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
			IStlDWordArray __RPC_FAR * This);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Array )(
			IStlDWordArray __RPC_FAR * This,
			/* [in] */ long idx,
			/* [retval][out] */ DWORD __RPC_FAR *dw);

		/* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Array )(
			IStlDWordArray __RPC_FAR * This,
			/* [in] */ long idx,
			/* [in] */ DWORD dw);

		/* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Add )(
			IStlDWordArray __RPC_FAR * This,
			/* [in] */ DWORD dw);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Remove )(
			IStlDWordArray __RPC_FAR * This,
			/* [in] */ long idx,
			/* [retval][out] */ DWORD __RPC_FAR *dw);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAll )(
			IStlDWordArray __RPC_FAR * This);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *First )(
			IStlDWordArray __RPC_FAR * This);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )(
			IStlDWordArray __RPC_FAR * This,
			/* [out] */ DWORD __RPC_FAR *pt,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )(
			IStlDWordArray __RPC_FAR * This,
			/* [retval][out] */ UINT __RPC_FAR *dw);

		END_INTERFACE
	} IStlDWordArrayVtbl;

	interface IStlDWordArray
	{
		CONST_VTBL struct IStlDWordArrayVtbl __RPC_FAR *lpVtbl;
	};



#ifdef COBJMACROS


#define IStlDWordArray_QueryInterface(This,riid,ppvObject)  \
	(This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStlDWordArray_AddRef(This) \
	(This)->lpVtbl -> AddRef(This)

#define IStlDWordArray_Release(This)    \
	(This)->lpVtbl -> Release(This)


#define IStlDWordArray_get_Array(This,idx,dw)   \
	(This)->lpVtbl -> get_Array(This,idx,dw)

#define IStlDWordArray_put_Array(This,idx,dw)   \
	(This)->lpVtbl -> put_Array(This,idx,dw)

#define IStlDWordArray_put_Add(This,dw) \
	(This)->lpVtbl -> put_Add(This,dw)

#define IStlDWordArray_get_Remove(This,idx,dw)  \
	(This)->lpVtbl -> get_Remove(This,idx,dw)

#define IStlDWordArray_RemoveAll(This)  \
	(This)->lpVtbl -> RemoveAll(This)

#define IStlDWordArray_First(This)  \
	(This)->lpVtbl -> First(This)

#define IStlDWordArray_Next(This,pt,b)  \
	(This)->lpVtbl -> Next(This,pt,b)

#define IStlDWordArray_get_Count(This,dw)   \
	(This)->lpVtbl -> get_Count(This,dw)

#endif /* COBJMACROS */


#endif  /* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlDWordArray_get_Array_Proxy(
	IStlDWordArray __RPC_FAR * This,
	/* [in] */ long idx,
	/* [retval][out] */ DWORD __RPC_FAR *dw);


void __RPC_STUB IStlDWordArray_get_Array_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IStlDWordArray_put_Array_Proxy(
	IStlDWordArray __RPC_FAR * This,
	/* [in] */ long idx,
	/* [in] */ DWORD dw);


void __RPC_STUB IStlDWordArray_put_Array_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IStlDWordArray_put_Add_Proxy(
	IStlDWordArray __RPC_FAR * This,
	/* [in] */ DWORD dw);


void __RPC_STUB IStlDWordArray_put_Add_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlDWordArray_get_Remove_Proxy(
	IStlDWordArray __RPC_FAR * This,
	/* [in] */ long idx,
	/* [retval][out] */ DWORD __RPC_FAR *dw);


void __RPC_STUB IStlDWordArray_get_Remove_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlDWordArray_RemoveAll_Proxy(
	IStlDWordArray __RPC_FAR * This);


void __RPC_STUB IStlDWordArray_RemoveAll_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlDWordArray_First_Proxy(
	IStlDWordArray __RPC_FAR * This);


void __RPC_STUB IStlDWordArray_First_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlDWordArray_Next_Proxy(
	IStlDWordArray __RPC_FAR * This,
	/* [out] */ DWORD __RPC_FAR *pt,
	/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);


void __RPC_STUB IStlDWordArray_Next_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlDWordArray_get_Count_Proxy(
	IStlDWordArray __RPC_FAR * This,
	/* [retval][out] */ UINT __RPC_FAR *dw);


void __RPC_STUB IStlDWordArray_get_Count_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);



#endif  /* __IStlDWordArray_INTERFACE_DEFINED__ */


#ifndef __IStlMyObjectArray_INTERFACE_DEFINED__
#define __IStlMyObjectArray_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IStlMyObjectArray
 * at Wed Sep 24 14:39:38 1997
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][uuid][object] */



EXTERN_C const IID IID_IStlMyObjectArray;

#if defined(__cplusplus) && !defined(CINTERFACE)

	interface DECLSPEC_UUID("7CE086FB-3E78-11D0-AE6B-00C04FD7D06E")
	IStlMyObjectArray : public IUnknown
	{
	public:
		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Array(
			/* [in] */ long idx,
			/* [retval][out] */ IMyStruct __RPC_FAR *__RPC_FAR *str) = 0;

		virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Array(
			/* [in] */ long idx,
			/* [in] */ IMyStruct __RPC_FAR *str) = 0;

		virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Add(
			/* [in] */ IMyStruct __RPC_FAR *str) = 0;

		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Remove(
			/* [in] */ long idx,
			/* [retval][out] */ IMyStruct __RPC_FAR *__RPC_FAR *str) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE First( void) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE Next(
			/* [out] */ IMyStruct __RPC_FAR *__RPC_FAR *pt,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b) = 0;

		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count(
			/* [retval][out] */ UINT __RPC_FAR *dw) = 0;

	};

#else   /* C style interface */

	typedef struct IStlMyObjectArrayVtbl
	{
		BEGIN_INTERFACE

		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
			IStlMyObjectArray __RPC_FAR * This,
			/* [in] */ REFIID riid,
			/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
			IStlMyObjectArray __RPC_FAR * This);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
			IStlMyObjectArray __RPC_FAR * This);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Array )(
			IStlMyObjectArray __RPC_FAR * This,
			/* [in] */ long idx,
			/* [retval][out] */ IMyStruct __RPC_FAR *__RPC_FAR *str);

		/* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Array )(
			IStlMyObjectArray __RPC_FAR * This,
			/* [in] */ long idx,
			/* [in] */ IMyStruct __RPC_FAR *str);

		/* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Add )(
			IStlMyObjectArray __RPC_FAR * This,
			/* [in] */ IMyStruct __RPC_FAR *str);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Remove )(
			IStlMyObjectArray __RPC_FAR * This,
			/* [in] */ long idx,
			/* [retval][out] */ IMyStruct __RPC_FAR *__RPC_FAR *str);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAll )(
			IStlMyObjectArray __RPC_FAR * This);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *First )(
			IStlMyObjectArray __RPC_FAR * This);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )(
			IStlMyObjectArray __RPC_FAR * This,
			/* [out] */ IMyStruct __RPC_FAR *__RPC_FAR *pt,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )(
			IStlMyObjectArray __RPC_FAR * This,
			/* [retval][out] */ UINT __RPC_FAR *dw);

		END_INTERFACE
	} IStlMyObjectArrayVtbl;

	interface IStlMyObjectArray
	{
		CONST_VTBL struct IStlMyObjectArrayVtbl __RPC_FAR *lpVtbl;
	};



#ifdef COBJMACROS


#define IStlMyObjectArray_QueryInterface(This,riid,ppvObject)   \
	(This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStlMyObjectArray_AddRef(This)  \
	(This)->lpVtbl -> AddRef(This)

#define IStlMyObjectArray_Release(This) \
	(This)->lpVtbl -> Release(This)


#define IStlMyObjectArray_get_Array(This,idx,str)   \
	(This)->lpVtbl -> get_Array(This,idx,str)

#define IStlMyObjectArray_put_Array(This,idx,str)   \
	(This)->lpVtbl -> put_Array(This,idx,str)

#define IStlMyObjectArray_put_Add(This,str) \
	(This)->lpVtbl -> put_Add(This,str)

#define IStlMyObjectArray_get_Remove(This,idx,str)  \
	(This)->lpVtbl -> get_Remove(This,idx,str)

#define IStlMyObjectArray_RemoveAll(This)   \
	(This)->lpVtbl -> RemoveAll(This)

#define IStlMyObjectArray_First(This)   \
	(This)->lpVtbl -> First(This)

#define IStlMyObjectArray_Next(This,pt,b)   \
	(This)->lpVtbl -> Next(This,pt,b)

#define IStlMyObjectArray_get_Count(This,dw)    \
	(This)->lpVtbl -> get_Count(This,dw)

#endif /* COBJMACROS */


#endif  /* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlMyObjectArray_get_Array_Proxy(
	IStlMyObjectArray __RPC_FAR * This,
	/* [in] */ long idx,
	/* [retval][out] */ IMyStruct __RPC_FAR *__RPC_FAR *str);


void __RPC_STUB IStlMyObjectArray_get_Array_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IStlMyObjectArray_put_Array_Proxy(
	IStlMyObjectArray __RPC_FAR * This,
	/* [in] */ long idx,
	/* [in] */ IMyStruct __RPC_FAR *str);


void __RPC_STUB IStlMyObjectArray_put_Array_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IStlMyObjectArray_put_Add_Proxy(
	IStlMyObjectArray __RPC_FAR * This,
	/* [in] */ IMyStruct __RPC_FAR *str);


void __RPC_STUB IStlMyObjectArray_put_Add_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlMyObjectArray_get_Remove_Proxy(
	IStlMyObjectArray __RPC_FAR * This,
	/* [in] */ long idx,
	/* [retval][out] */ IMyStruct __RPC_FAR *__RPC_FAR *str);


void __RPC_STUB IStlMyObjectArray_get_Remove_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlMyObjectArray_RemoveAll_Proxy(
	IStlMyObjectArray __RPC_FAR * This);


void __RPC_STUB IStlMyObjectArray_RemoveAll_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlMyObjectArray_First_Proxy(
	IStlMyObjectArray __RPC_FAR * This);


void __RPC_STUB IStlMyObjectArray_First_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlMyObjectArray_Next_Proxy(
	IStlMyObjectArray __RPC_FAR * This,
	/* [out] */ IMyStruct __RPC_FAR *__RPC_FAR *pt,
	/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);


void __RPC_STUB IStlMyObjectArray_Next_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlMyObjectArray_get_Count_Proxy(
	IStlMyObjectArray __RPC_FAR * This,
	/* [retval][out] */ UINT __RPC_FAR *dw);


void __RPC_STUB IStlMyObjectArray_get_Count_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);



#endif  /* __IStlMyObjectArray_INTERFACE_DEFINED__ */


#ifndef __IStlPointArray_INTERFACE_DEFINED__
#define __IStlPointArray_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IStlPointArray
 * at Wed Sep 24 14:39:38 1997
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][uuid][object] */



EXTERN_C const IID IID_IStlPointArray;

#if defined(__cplusplus) && !defined(CINTERFACE)

	interface DECLSPEC_UUID("7CE08700-3E78-11D0-AE6B-00C04FD7D06E")
	IStlPointArray : public IUnknown
	{
	public:
		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Array(
			/* [in] */ long idx,
			/* [retval][out] */ POINT __RPC_FAR *pt) = 0;

		virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Array(
			/* [in] */ long idx,
			/* [in] */ POINT pt) = 0;

		virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Add(
			/* [in] */ POINT pt) = 0;

		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Remove(
			/* [in] */ long idx,
			/* [retval][out] */ POINT __RPC_FAR *pt) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE First( void) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE Next(
			/* [out] */ POINT __RPC_FAR *pt,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b) = 0;

		virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count(
			/* [retval][out] */ UINT __RPC_FAR *dw) = 0;

	};

#else   /* C style interface */

	typedef struct IStlPointArrayVtbl
	{
		BEGIN_INTERFACE

		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
			IStlPointArray __RPC_FAR * This,
			/* [in] */ REFIID riid,
			/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
			IStlPointArray __RPC_FAR * This);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
			IStlPointArray __RPC_FAR * This);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Array )(
			IStlPointArray __RPC_FAR * This,
			/* [in] */ long idx,
			/* [retval][out] */ POINT __RPC_FAR *pt);

		/* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Array )(
			IStlPointArray __RPC_FAR * This,
			/* [in] */ long idx,
			/* [in] */ POINT pt);

		/* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Add )(
			IStlPointArray __RPC_FAR * This,
			/* [in] */ POINT pt);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Remove )(
			IStlPointArray __RPC_FAR * This,
			/* [in] */ long idx,
			/* [retval][out] */ POINT __RPC_FAR *pt);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAll )(
			IStlPointArray __RPC_FAR * This);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *First )(
			IStlPointArray __RPC_FAR * This);

		/* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )(
			IStlPointArray __RPC_FAR * This,
			/* [out] */ POINT __RPC_FAR *pt,
			/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);

		/* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )(
			IStlPointArray __RPC_FAR * This,
			/* [retval][out] */ UINT __RPC_FAR *dw);

		END_INTERFACE
	} IStlPointArrayVtbl;

	interface IStlPointArray
	{
		CONST_VTBL struct IStlPointArrayVtbl __RPC_FAR *lpVtbl;
	};



#ifdef COBJMACROS


#define IStlPointArray_QueryInterface(This,riid,ppvObject)  \
	(This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStlPointArray_AddRef(This) \
	(This)->lpVtbl -> AddRef(This)

#define IStlPointArray_Release(This)    \
	(This)->lpVtbl -> Release(This)


#define IStlPointArray_get_Array(This,idx,pt)   \
	(This)->lpVtbl -> get_Array(This,idx,pt)

#define IStlPointArray_put_Array(This,idx,pt)   \
	(This)->lpVtbl -> put_Array(This,idx,pt)

#define IStlPointArray_put_Add(This,pt) \
	(This)->lpVtbl -> put_Add(This,pt)

#define IStlPointArray_get_Remove(This,idx,pt)  \
	(This)->lpVtbl -> get_Remove(This,idx,pt)

#define IStlPointArray_RemoveAll(This)  \
	(This)->lpVtbl -> RemoveAll(This)

#define IStlPointArray_First(This)  \
	(This)->lpVtbl -> First(This)

#define IStlPointArray_Next(This,pt,b)  \
	(This)->lpVtbl -> Next(This,pt,b)

#define IStlPointArray_get_Count(This,dw)   \
	(This)->lpVtbl -> get_Count(This,dw)

#endif /* COBJMACROS */


#endif  /* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlPointArray_get_Array_Proxy(
	IStlPointArray __RPC_FAR * This,
	/* [in] */ long idx,
	/* [retval][out] */ POINT __RPC_FAR *pt);


void __RPC_STUB IStlPointArray_get_Array_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IStlPointArray_put_Array_Proxy(
	IStlPointArray __RPC_FAR * This,
	/* [in] */ long idx,
	/* [in] */ POINT pt);


void __RPC_STUB IStlPointArray_put_Array_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IStlPointArray_put_Add_Proxy(
	IStlPointArray __RPC_FAR * This,
	/* [in] */ POINT pt);


void __RPC_STUB IStlPointArray_put_Add_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlPointArray_get_Remove_Proxy(
	IStlPointArray __RPC_FAR * This,
	/* [in] */ long idx,
	/* [retval][out] */ POINT __RPC_FAR *pt);


void __RPC_STUB IStlPointArray_get_Remove_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlPointArray_RemoveAll_Proxy(
	IStlPointArray __RPC_FAR * This);


void __RPC_STUB IStlPointArray_RemoveAll_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlPointArray_First_Proxy(
	IStlPointArray __RPC_FAR * This);


void __RPC_STUB IStlPointArray_First_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStlPointArray_Next_Proxy(
	IStlPointArray __RPC_FAR * This,
	/* [out] */ POINT __RPC_FAR *pt,
	/* [retval][out] */ VARIANT_BOOL __RPC_FAR *b);


void __RPC_STUB IStlPointArray_Next_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStlPointArray_get_Count_Proxy(
	IStlPointArray __RPC_FAR * This,
	/* [retval][out] */ UINT __RPC_FAR *dw);


void __RPC_STUB IStlPointArray_get_Count_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);



#endif  /* __IStlPointArray_INTERFACE_DEFINED__ */



#ifndef __STLCOLLLib_LIBRARY_DEFINED__
#define __STLCOLLLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: STLCOLLLib
 * at Wed Sep 24 14:39:38 1997
 * using MIDL 3.01.76
 ****************************************/
/* [helpstring][version][uuid] */



EXTERN_C const IID LIBID_STLCOLLLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CStlMaps;

class DECLSPEC_UUID("7CE086CD-3E78-11D0-AE6B-00C04FD7D06E")
CStlMaps;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CStlMapStringToMyObject;

class DECLSPEC_UUID("7CE086CF-3E78-11D0-AE6B-00C04FD7D06E")
CStlMapStringToMyObject;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CStlMapDWordToMyStruct;

class DECLSPEC_UUID("7CE086D0-3E78-11D0-AE6B-00C04FD7D06E")
CStlMapDWordToMyStruct;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CStlMapStringToString;

class DECLSPEC_UUID("7CE086D1-3E78-11D0-AE6B-00C04FD7D06E")
CStlMapStringToString;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CStlLists;

class DECLSPEC_UUID("7CE086D2-3E78-11D0-AE6B-00C04FD7D06E")
CStlLists;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CStlArrays;

class DECLSPEC_UUID("7CE086D7-3E78-11D0-AE6B-00C04FD7D06E")
CStlArrays;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CStlDWordArray;

class DECLSPEC_UUID("7CE086D9-3E78-11D0-AE6B-00C04FD7D06E")
CStlDWordArray;
#endif
#endif /* __STLCOLLLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * );
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * );
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * );
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * );

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
