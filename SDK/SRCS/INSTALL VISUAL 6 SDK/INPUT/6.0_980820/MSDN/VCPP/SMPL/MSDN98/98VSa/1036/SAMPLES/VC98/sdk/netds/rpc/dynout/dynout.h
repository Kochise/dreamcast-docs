/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:06:59 1998
 */
/* Compiler settings for dynout.idl:
    Os (OptLev=s), W1, Zp1, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __dynout_h__
#define __dynout_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __MemStuff_INTERFACE_DEFINED__
#define __MemStuff_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: MemStuff
 * at Mon Mar 30 03:06:59 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [auto_handle][unique][version][uuid] */ 


short GrabChunk( 
    /* [out] */ long __RPC_FAR *lSize,
    /* [size_is][size_is][out] */ unsigned char __RPC_FAR *__RPC_FAR *ppData);



extern RPC_IF_HANDLE MemStuff_v1_0_c_ifspec;
extern RPC_IF_HANDLE MemStuff_v1_0_s_ifspec;
#endif /* __MemStuff_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
