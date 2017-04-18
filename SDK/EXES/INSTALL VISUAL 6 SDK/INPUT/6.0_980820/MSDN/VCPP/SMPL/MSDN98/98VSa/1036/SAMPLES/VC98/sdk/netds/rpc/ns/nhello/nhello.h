/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:08:16 1998
 */
/* Compiler settings for nhello.idl:
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

#ifndef __nhello_h__
#define __nhello_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __nhello_INTERFACE_DEFINED__
#define __nhello_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: nhello
 * at Mon Mar 30 03:08:16 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [auto_handle][unique][version][uuid] */ 


void HelloProc( 
    handle_t nBinding,
    /* [string][in] */ unsigned char __RPC_FAR *pszString);

void Shutdown( 
    handle_t nBinding);



extern RPC_IF_HANDLE nhello_v1_0_c_ifspec;
extern RPC_IF_HANDLE nhello_v1_0_s_ifspec;
#endif /* __nhello_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
