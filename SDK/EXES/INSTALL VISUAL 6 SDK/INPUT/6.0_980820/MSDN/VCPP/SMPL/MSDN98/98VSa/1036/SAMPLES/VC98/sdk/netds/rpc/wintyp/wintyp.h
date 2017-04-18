/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:09:21 1998
 */
/* Compiler settings for wintyp.idl:
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

#ifndef __wintyp_h__
#define __wintyp_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

/* header files for imported files */
#include "wtypes.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __wintyp_sample_INTERFACE_DEFINED__
#define __wintyp_sample_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: wintyp_sample
 * at Mon Mar 30 03:09:21 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [implicit_handle][version][unique][uuid] */ 


BOOL ChangeBitmapRemote( 
    /* [in] */ unsigned short action,
    /* [out][in] */ HBITMAP __RPC_FAR *bitmap);

void ShutDown( void);


extern handle_t global_wintyp_sample_handle;


extern RPC_IF_HANDLE wintyp_sample_v1_0_c_ifspec;
extern RPC_IF_HANDLE wintyp_sample_v1_0_s_ifspec;
#endif /* __wintyp_sample_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  HBITMAP_UserSize(     unsigned long __RPC_FAR *, unsigned long            , HBITMAP __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  HBITMAP_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, HBITMAP __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  HBITMAP_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, HBITMAP __RPC_FAR * ); 
void                      __RPC_USER  HBITMAP_UserFree(     unsigned long __RPC_FAR *, HBITMAP __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
