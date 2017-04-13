/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:07:10 1998
 */
/* Compiler settings for auto.idl:
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

#ifndef __auto_h__
#define __auto_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __autoh_INTERFACE_DEFINED__
#define __autoh_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: autoh
 * at Mon Mar 30 03:07:10 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [auto_handle][unique][version][uuid] */ 


void GetTime( 
    /* [out] */ long __RPC_FAR *time);

void Shutdown( void);



extern RPC_IF_HANDLE autoh_ClientIfHandle;
extern RPC_IF_HANDLE autoh_ServerIfHandle;
#endif /* __autoh_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
