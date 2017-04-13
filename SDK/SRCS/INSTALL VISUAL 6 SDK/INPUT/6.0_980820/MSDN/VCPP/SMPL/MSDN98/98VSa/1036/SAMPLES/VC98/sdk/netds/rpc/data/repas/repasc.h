/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:05:50 1998
 */
/* Compiler settings for repas.idl, repasc.acf:
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

#ifndef __repasc_h__
#define __repasc_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __repas_INTERFACE_DEFINED__
#define __repas_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: repas
 * at Mon Mar 30 03:05:50 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [implicit_handle][unique][version][uuid] */ 


#define	STRING_SIZE	( 100 )

typedef unsigned char __RPC_FAR CHAR_STRING[ 100 ];

typedef /* [represent_as] */ wchar_t __RPC_FAR WCHAR_STRING[ 100 ];

void ModifyMyWString( 
    /* [out][in] */ CHAR_STRING __RPC_FAR *pStr);

void ModifyMyString( 
    /* [out][in] */ CHAR_STRING __RPC_FAR *pStr);

void Shutdown( void);


extern handle_t hrepas;


extern RPC_IF_HANDLE repas_ClientIfHandle;
extern RPC_IF_HANDLE repas_ServerIfHandle;
#endif /* __repas_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */


void __RPC_USER WCHAR_STRING_from_local( CHAR_STRING __RPC_FAR *, WCHAR_STRING __RPC_FAR * __RPC_FAR * );
void __RPC_USER WCHAR_STRING_to_local( WCHAR_STRING __RPC_FAR *, CHAR_STRING __RPC_FAR * );
 void __RPC_USER WCHAR_STRING_free_inst( WCHAR_STRING __RPC_FAR * );
void __RPC_USER WCHAR_STRING_free_local( CHAR_STRING __RPC_FAR * );

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
