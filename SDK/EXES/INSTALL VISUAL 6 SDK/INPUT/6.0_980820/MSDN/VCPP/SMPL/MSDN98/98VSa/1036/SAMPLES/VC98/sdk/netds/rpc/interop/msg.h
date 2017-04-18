/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:07:53 1998
 */
/* Compiler settings for msg.idl:
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

#ifndef __msg_h__
#define __msg_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __interop_INTERFACE_DEFINED__
#define __interop_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: interop
 * at Mon Mar 30 03:07:53 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [implicit_handle][version][uuid] */ 


void ClientMessage( 
    /* [ref][string][in] */ unsigned char __RPC_FAR *pszMessage);

void ShutdownServer( void);


extern handle_t interop_binding_handle;


extern RPC_IF_HANDLE interop_v1_0_c_ifspec;
extern RPC_IF_HANDLE interop_v1_0_s_ifspec;
#endif /* __interop_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
