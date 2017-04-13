/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:09:11 1998
 */
/* Compiler settings for strout.idl:
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

#ifndef __strout_h__
#define __strout_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __strout_sample_INTERFACE_DEFINED__
#define __strout_sample_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: strout_sample
 * at Mon Mar 30 03:09:11 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [implicit_handle][version][unique][uuid] */ 


typedef /* [unique][string] */ unsigned char __RPC_FAR *str;

void GetRemoteEnv( 
    /* [out][in] */ unsigned long __RPC_FAR *Lines,
    /* [size_is][size_is][out] */ str __RPC_FAR *__RPC_FAR *EnvBlock);

void ShutDown( void);


extern handle_t global_strout_sample_handle;


extern RPC_IF_HANDLE strout_sample_v1_0_c_ifspec;
extern RPC_IF_HANDLE strout_sample_v1_0_s_ifspec;
#endif /* __strout_sample_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
