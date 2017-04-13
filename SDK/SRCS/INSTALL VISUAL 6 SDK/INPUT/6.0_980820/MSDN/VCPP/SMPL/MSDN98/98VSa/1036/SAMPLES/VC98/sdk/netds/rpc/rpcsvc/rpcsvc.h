/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:08:56 1998
 */
/* Compiler settings for rpcsvc.idl:
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

#ifndef __rpcsvc_h__
#define __rpcsvc_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __RpcServiceSample_INTERFACE_DEFINED__
#define __RpcServiceSample_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: RpcServiceSample
 * at Mon Mar 30 03:08:56 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [auto_handle][version][uuid] */ 


/* [fault_status][comm_status] */ error_status_t Ping( 
    /* [in] */ handle_t Binding);

/* [fault_status][comm_status] */ error_status_t CheckSecurity( 
    /* [in] */ handle_t Binding);

#define	BUFFER_SIZE	( 100 )

/* [fault_status][comm_status] */ error_status_t BufferIn1( 
    /* [in] */ handle_t Binding,
    /* [in][size_is][length_is] */ byte __RPC_FAR Buffer[  ],
    /* [in] */ unsigned long BufferLength,
    /* [in] */ unsigned long BufferSize);

/* [fault_status][comm_status] */ error_status_t BufferIn2( 
    /* [in] */ handle_t Binding,
    /* [in][length_is] */ byte __RPC_FAR Buffer[ 16384 ],
    /* [in] */ unsigned long BufferLength);

/* [fault_status][comm_status] */ error_status_t BufferIn3( 
    /* [in] */ handle_t Binding,
    /* [in][size_is] */ byte __RPC_FAR Buffer[  ],
    /* [in] */ unsigned long BufferLength);

/* [fault_status][comm_status] */ error_status_t BufferOut1( 
    /* [in] */ handle_t Binding,
    /* [length_is] */ byte __RPC_FAR Buffer[ 16384 ],
    /* [out] */ unsigned long __RPC_FAR *pBufferLength);

/* [fault_status][comm_status] */ error_status_t BufferOut2( 
    /* [in] */ handle_t Binding,
    /* [out][length_is][size_is] */ byte __RPC_FAR Buffer[  ],
    /* [in] */ unsigned long BufferSize,
    /* [out] */ unsigned long __RPC_FAR *pBufferLength);

typedef /* [public][public] */ struct  __MIDL_RpcServiceSample_0001
    {
    unsigned long BufferLength;
    /* [size_is][unique] */ byte __RPC_FAR *Buffer;
    }	BUFFER;

/* [fault_status][comm_status] */ error_status_t BufferOut3( 
    /* [in] */ handle_t Binding,
    /* [out] */ BUFFER __RPC_FAR *pBuffer);

/* [fault_status][comm_status] */ error_status_t BufferOut4( 
    /* [in] */ handle_t Binding,
    /* [size_is][out] */ byte __RPC_FAR Buffer[  ],
    /* [out][in] */ unsigned long __RPC_FAR *pBufferLength);

typedef /* [public][public][public] */ 
enum __MIDL_RpcServiceSample_0002
    {	A	= 1,
	B	= A + 1,
	C	= B + 1,
	D	= C + 1
    }	BAD_ENUM;

typedef /* [public][public][public][v1_enum] */ 
enum __MIDL_RpcServiceSample_0003
    {	E	= 5,
	F	= E + 1,
	G	= F + 1,
	H	= G + 1
    }	GOOD_ENUM;

struct  BAD1
    {
    long l;
    short s;
    };
struct  BAD2
    {
    BAD_ENUM e;
    long l;
    };
struct  GOOD
    {
    GOOD_ENUM e;
    long l;
    long l2;
    };
/* [fault_status][comm_status] */ error_status_t StructsIn1( 
    /* [in] */ handle_t Binding,
    /* [in] */ struct BAD1 __RPC_FAR array[ 50 ]);

/* [fault_status][comm_status] */ error_status_t StructsIn2( 
    /* [in] */ handle_t Binding,
    /* [in] */ struct BAD2 __RPC_FAR array[ 50 ]);

/* [fault_status][comm_status] */ error_status_t StructsIn3( 
    /* [in] */ handle_t Binding,
    /* [in] */ struct GOOD __RPC_FAR array[ 50 ]);

#define	LIST_SIZE	( 50 )

typedef struct  LIST
    {
    /* [unique] */ struct LIST __RPC_FAR *pNext;
    unsigned long data;
    }	LIST;

typedef /* [unique] */ LIST __RPC_FAR *PLIST;

/* [fault_status][comm_status] */ error_status_t ListIn( 
    /* [in] */ handle_t Binding,
    /* [in] */ PLIST pList);

/* [fault_status][comm_status] */ error_status_t ListOut1( 
    /* [in] */ handle_t Binding,
    /* [out] */ LIST __RPC_FAR *pListHead);

/* [enable_allocate][fault_status][comm_status] */ error_status_t ListOut2( 
    /* [in] */ handle_t Binding,
    /* [out] */ LIST __RPC_FAR *pListHead);

#define	UNION_ARRAY_LEN	( 50 )

typedef struct  BAD_UNION
    {
    unsigned long Tag;
    /* [switch_is] */ /* [switch_type] */ union 
        {
        /* [case()] */ unsigned long ulData;
        /* [case()] */ MIDL_uhyper uhData;
        /* [default] */  /* Empty union arm */ 
        }	u;
    }	BAD_UNION;

typedef struct  ONE
    {
    unsigned long DataLength;
    /* [size_is] */ unsigned long __RPC_FAR *Data;
    }	ARM_ONE;

typedef struct  TWO
    {
    unsigned long DataLength;
    /* [size_is] */ MIDL_uhyper __RPC_FAR *Data;
    }	ARM_TWO;

typedef /* [public][public] */ struct  __MIDL_RpcServiceSample_0005
    {
    unsigned long Tag;
    /* [switch_is] */ /* [switch_type] */ union 
        {
        /* [case()][unique] */ ARM_ONE __RPC_FAR *pOne;
        /* [case()][unique] */ ARM_TWO __RPC_FAR *pTwo;
        }	u;
    }	GOOD_UNION;

/* [fault_status][comm_status] */ error_status_t UnionCall1( 
    /* [in] */ handle_t Binding,
    /* [in] */ unsigned long Length,
    /* [size_is][in] */ BAD_UNION __RPC_FAR ArrayOfUnions[  ]);

/* [fault_status][comm_status] */ error_status_t UnionCall2( 
    /* [in] */ handle_t Binding,
    /* [in] */ GOOD_UNION __RPC_FAR *pUnionContainingArrays);



extern RPC_IF_HANDLE RpcServiceSample_v1_0_c_ifspec;
extern RPC_IF_HANDLE RpcServiceSample_v1_0_s_ifspec;
#endif /* __RpcServiceSample_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
