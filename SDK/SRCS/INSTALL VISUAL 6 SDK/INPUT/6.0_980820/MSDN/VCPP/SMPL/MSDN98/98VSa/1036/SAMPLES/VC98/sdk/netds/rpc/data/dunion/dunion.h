/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:05:33 1998
 */
/* Compiler settings for dunion.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext, oldnames
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __dunion_h__
#define __dunion_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __dunion_INTERFACE_DEFINED__
#define __dunion_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: dunion
 * at Mon Mar 30 03:05:33 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [implicit_handle][unique][version][uuid] */ 


typedef /* [public][public][public][public][public][switch_type] */ union __MIDL_dunion_0001
    {
    /* [case()] */ short sVal;
    /* [case()] */ float fVal;
    /* [case()] */ unsigned char chVal;
    /* [default] */  /* Empty union arm */ 
    }	DISCRIM_UNION_PARAM_TYPE;

typedef DISCRIM_UNION_PARAM_TYPE DISCRIM_UNION_FIELD_TYPE;

typedef /* [public][public] */ struct  __MIDL_dunion_0002
    {
    short sDiscrim;
    /* [switch_is] */ DISCRIM_UNION_FIELD_TYPE u;
    }	DISCRIM_UNION_STRUCT_TYPE;

void UnionParamProc( 
    /* [switch_is][in] */ DISCRIM_UNION_PARAM_TYPE __RPC_FAR *UnionParam,
    /* [in] */ short sDiscrim);

void UnionStructProc( 
    /* [in] */ DISCRIM_UNION_STRUCT_TYPE __RPC_FAR *UnionStruct);

void Shutdown( void);


extern handle_t hDiscrim;


extern RPC_IF_HANDLE dunion_ClientIfHandle;
extern RPC_IF_HANDLE dunion_ServerIfHandle;
#endif /* __dunion_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
