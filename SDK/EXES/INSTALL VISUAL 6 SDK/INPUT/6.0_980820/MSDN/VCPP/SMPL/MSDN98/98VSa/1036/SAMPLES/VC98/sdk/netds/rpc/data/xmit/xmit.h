/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:06:10 1998
 */
/* Compiler settings for xmit.idl:
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

#ifndef __xmit_h__
#define __xmit_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __xmit_INTERFACE_DEFINED__
#define __xmit_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: xmit
 * at Mon Mar 30 03:06:10 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [implicit_handle][unique][version][uuid] */ 


typedef struct  _DOUBLE_LINK_LIST
    {
    short sNumber;
    struct _DOUBLE_LINK_LIST __RPC_FAR *pNext;
    struct _DOUBLE_LINK_LIST __RPC_FAR *pPrevious;
    }	DOUBLE_LINK_LIST;

typedef struct  _DOUBLE_XMIT_TYPE
    {
    short sSize;
    /* [size_is] */ short asNumber[ 1 ];
    }	DOUBLE_XMIT_TYPE;

typedef /* [transmit_as] */ DOUBLE_LINK_LIST DOUBLE_LINK_TYPE;

void ModifyListProc( 
    /* [out][in] */ DOUBLE_LINK_TYPE __RPC_FAR *pHead);

void Shutdown( void);


extern handle_t hXmit;


extern RPC_IF_HANDLE xmit_ClientIfHandle;
extern RPC_IF_HANDLE xmit_ServerIfHandle;
#endif /* __xmit_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */


void __RPC_USER DOUBLE_LINK_TYPE_to_xmit( DOUBLE_LINK_TYPE __RPC_FAR *, DOUBLE_XMIT_TYPE  __RPC_FAR * __RPC_FAR * );
void __RPC_USER DOUBLE_LINK_TYPE_from_xmit( DOUBLE_XMIT_TYPE  __RPC_FAR *, DOUBLE_LINK_TYPE __RPC_FAR * );
void __RPC_USER DOUBLE_LINK_TYPE_free_inst( DOUBLE_LINK_TYPE __RPC_FAR * );
void __RPC_USER DOUBLE_LINK_TYPE_free_xmit( DOUBLE_XMIT_TYPE  __RPC_FAR * );

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
