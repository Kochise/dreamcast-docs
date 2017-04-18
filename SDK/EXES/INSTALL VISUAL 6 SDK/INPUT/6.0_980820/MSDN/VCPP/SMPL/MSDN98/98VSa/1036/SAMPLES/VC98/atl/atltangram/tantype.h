/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.76 */
/* at Mon Dec 08 20:38:21 1997
 */
/* Compiler settings for D:\ATL25\samples\ATLTangram\tantype.idl:
	Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
	error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"

#ifndef __tantype_h__
#define __tantype_h__

#ifdef __cplusplus
extern "C"{
#endif

/* Forward Declarations */

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * );

/****************************************
 * Generated header for interface: __MIDL_itf_tantype_0000
 * at Mon Dec 08 20:38:21 1997
 * using MIDL 3.01.76
 ****************************************/
/* [local] */


typedef struct  tagTangramSize2d_
	{
	double cx;
	double cy;
	}   TangramSize2d;

typedef struct  tagTangramPoint2d_
	{
	double x;
	double y;
	}   TangramPoint2d;



extern RPC_IF_HANDLE __MIDL_itf_tantype_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_tantype_0000_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
