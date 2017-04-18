/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:08:24 1998
 */
/* Compiler settings for picklp.idl:
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
#include "midles.h"

#ifndef __picklp_h__
#define __picklp_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __proc_pickle_INTERFACE_DEFINED__
#define __proc_pickle_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: proc_pickle
 * at Mon Mar 30 03:08:24 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [implicit_handle][unique][version][uuid] */ 


#define	ARR_SIZE	( 4 )

#define	BUFSIZE	( 1024 )

typedef struct  _OBJECT1
    {
    long al[ 4 ];
    short s;
    }	OBJECT1;

typedef struct  _OBJECT2
    {
    short sSize;
    /* [size_is] */ short as[ 1 ];
    }	OBJECT2;

/* [decode][encode] */ void ProcPickle( 
    /* [string][out][in] */ unsigned char __RPC_FAR *pTextId,
    /* [out][in] */ OBJECT1 __RPC_FAR *pObject1,
    /* [out][in] */ OBJECT2 __RPC_FAR *pObject2);


extern handle_t ImplicitPicHandle;


extern RPC_IF_HANDLE proc_pickle_ClientIfHandle;
extern RPC_IF_HANDLE proc_pickle_ServerIfHandle;
#endif /* __proc_pickle_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
