/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:06:20 1998
 */
/* Compiler settings for replay.idl:
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

#ifndef __replay_h__
#define __replay_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __dict_INTERFACE_DEFINED__
#define __dict_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: dict
 * at Mon Mar 30 03:06:20 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [implicit_handle][unique][version][uuid] */ 


typedef struct  _Record
    {
    short key;
    /* [string] */ unsigned char __RPC_FAR *name;
    }	Record;

typedef Record __RPC_FAR *PRecord;

typedef struct  _RecordTreeNode
    {
    struct _RecordTreeNode __RPC_FAR *left;
    struct _RecordTreeNode __RPC_FAR *right;
    Record __RPC_FAR *item;
    }	RecordTreeNode;

typedef struct  _DictState
    {
    short ref_count;
    Record __RPC_FAR *curr_record;
    }	DictState;

typedef struct  _RDict
    {
    RecordTreeNode __RPC_FAR *root;
    long size;
    DictState __RPC_FAR *state;
    }	RDict;

typedef /* [context_handle] */ void __RPC_FAR *VDict;

typedef /* [public][public][public][public][public][public][public][public][public][public][public][public][public][public] */ 
enum __MIDL_dict_0001
    {	DICT_SUCCESS	= 0,
	DICT_ITEM_ALREADY_PRESENT	= DICT_SUCCESS + 1,
	DICT_ITEM_NOT_FOUND	= DICT_ITEM_ALREADY_PRESENT + 1,
	DICT_FIRST_ITEM	= DICT_ITEM_NOT_FOUND + 1,
	DICT_LAST_ITEM	= DICT_FIRST_ITEM + 1,
	DICT_EMPTY_DICTIONARY	= DICT_LAST_ITEM + 1,
	DICT_NULL_ITEM	= DICT_EMPTY_DICTIONARY + 1
    }	VDict_Status;

VDict_Status VDict_New( 
    /* [in] */ short shared_dict,
    /* [out] */ VDict __RPC_FAR *v_dict);

VDict_Status VDict_Find( 
    /* [in] */ VDict v_dict,
    /* [out][in] */ Record __RPC_FAR *__RPC_FAR *item);

VDict_Status VDict_Next( 
    /* [in] */ VDict v_dict,
    /* [out][in] */ Record __RPC_FAR *__RPC_FAR *item);

VDict_Status VDict_Prev( 
    /* [in] */ VDict v_dict,
    /* [out][in] */ Record __RPC_FAR *__RPC_FAR *item);

VDict_Status VDict_Curr_Next( 
    /* [in] */ VDict v_dict,
    /* [out] */ Record __RPC_FAR *__RPC_FAR *item);

VDict_Status VDict_Curr_Prev( 
    /* [in] */ VDict v_dict,
    /* [out] */ Record __RPC_FAR *__RPC_FAR *item);

VDict_Status VDict_Insert( 
    /* [in] */ VDict v_dict,
    /* [in] */ Record __RPC_FAR *item);

VDict_Status VDict_Delete( 
    /* [in] */ VDict v_dict,
    /* [out][in] */ Record __RPC_FAR *__RPC_FAR *item);

VDict_Status VDict_Get_Dict( 
    /* [in] */ VDict v_dict,
    /* [out] */ RDict __RPC_FAR *__RPC_FAR *r_dict);

VDict_Status VDict_Curr_Item( 
    /* [in] */ VDict v_dict,
    /* [out] */ Record __RPC_FAR *__RPC_FAR *item);

VDict_Status VDict_Curr_Delete( 
    /* [in] */ VDict v_dict,
    /* [out] */ Record __RPC_FAR *__RPC_FAR *item);

VDict_Status VDict_X_Dict( 
    /* [in] */ VDict v_dict);

VDict_Status VDict_I_Dict( 
    /* [in] */ VDict v_dict,
    /* [in] */ short size);


extern handle_t dict_IfHandle;


extern RPC_IF_HANDLE dict_ClientIfHandle;
extern RPC_IF_HANDLE dict_ServerIfHandle;
#endif /* __dict_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

void __RPC_USER VDict_rundown( VDict );

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
