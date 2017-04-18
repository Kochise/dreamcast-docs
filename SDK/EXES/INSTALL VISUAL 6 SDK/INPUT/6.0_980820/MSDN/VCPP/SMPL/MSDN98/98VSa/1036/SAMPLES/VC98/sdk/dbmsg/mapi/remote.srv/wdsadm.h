/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 2.00.0102 */
/* at Wed Sep 27 11:30:53 1995
 */
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"

#ifndef __wdsadm_h__
#define __wdsadm_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __WINDSADM_INTERFACE_DEFINED__
#define __WINDSADM_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: WINDSADM
 * at Wed Sep 27 11:30:53 1995
 * using MIDL 2.00.0102
 ****************************************/
/* [implicit_handle][unique][version][uuid] */ 


            /* size is 396 */
typedef struct  _ADM_MAILBOX_INFO_A
    {
    unsigned char szMailboxName[ 17 ];
    unsigned char szFullName[ 33 ];
    unsigned char szJobTitle[ 33 ];
    unsigned char szOffice[ 33 ];
    unsigned char szPhone[ 13 ];
    unsigned char szAltPhone[ 13 ];
    unsigned char szFax[ 13 ];
    unsigned char szPassword[ 17 ];
    unsigned char szCompany[ 33 ];
    unsigned char szDepartment[ 33 ];
    unsigned char szComments[ 80 ];
    unsigned char szManagerName[ 33 ];
    unsigned char szManagerAlias[ 33 ];
    unsigned long dwManagerID;
    unsigned long dwObjID;
    unsigned long dwFlags;
    }   ADM_MAILBOX_INFO_A;

            /* size is 64 */
typedef struct  _DLM_INFO_A
    {
    unsigned char szMemberName[ 36 ];
    unsigned char szMemberAlias[ 20 ];
    unsigned long dwMemberID;
    unsigned long dwMemberType;
    }   DLM_INFO_A;

            /* size is 68 */
typedef struct  _DLM_LIST_A
    {
    DLM_INFO_A Info;
    struct _DLM_LIST_A __RPC_FAR *pNext;
    }   DLM_LIST_A;

            /* size is 4 */
typedef struct  _DLM_ARRAY_A
    {
    unsigned long dwCount;
    /* [size_is] */ DLM_INFO_A pMembers[ 1 ];
    }   DLM_ARRAY_A;

            /* size is 68 */
typedef /* [transmit] */ DLM_LIST_A DLM_XMIT_LIST_A;

            /* size is 780 */
typedef struct  _ADM_MAILBOX_INFO_W
    {
    wchar_t szMailboxName[ 17 ];
    wchar_t szFullName[ 33 ];
    wchar_t szJobTitle[ 33 ];
    wchar_t szOffice[ 33 ];
    wchar_t szPhone[ 13 ];
    wchar_t szAltPhone[ 13 ];
    wchar_t szFax[ 13 ];
    wchar_t szPassword[ 17 ];
    wchar_t szCompany[ 33 ];
    wchar_t szDepartment[ 33 ];
    wchar_t szComments[ 80 ];
    wchar_t szManagerName[ 33 ];
    wchar_t szManagerAlias[ 33 ];
    unsigned long dwManagerID;
    unsigned long dwObjID;
    unsigned long dwFlags;
    }   ADM_MAILBOX_INFO_W;

            /* size is 120 */
typedef struct  _DLM_INFO_W
    {
    wchar_t szMemberName[ 36 ];
    wchar_t szMemberAlias[ 20 ];
    unsigned long dwMemberID;
    unsigned long dwMemberType;
    }   DLM_INFO_W;

            /* size is 124 */
typedef struct  _DLM_LIST_W
    {
    DLM_INFO_W Info;
    struct _DLM_LIST_W __RPC_FAR *pNext;
    }   DLM_LIST_W;

            /* size is 4 */
typedef struct  _DLM_ARRAY_W
    {
    unsigned long dwCount;
    /* [size_is] */ DLM_INFO_W pMembers[ 1 ];
    }   DLM_ARRAY_W;

            /* size is 124 */
typedef /* [transmit] */ DLM_LIST_W DLM_XMIT_LIST_W;

            /* size is 4 */
long RemoteAdmIsServerRunning( void);

            /* size is 4 */
long RemoteAdmDeleteObject( 
    /* [in] */ unsigned long dwObjID);

            /* size is 4 */
long RemoteAdmGetServerMailboxes( 
    /* [out] */ long __RPC_FAR *pPipeNumber);

            /* size is 4 */
long RemoteAdmGetServerDistLists( 
    /* [out] */ long __RPC_FAR *pPipeNumber);

            /* size is 4 */
long RemoteAdmEmptyMailbox( 
    /* [in] */ unsigned long dwMailboxID);

            /* size is 4 */
long RemoteAdmGetGALDirectory( 
    /* [in] */ unsigned long dwFlags,
    /* [out] */ long __RPC_FAR *pPipeNumber);

            /* size is 4 */
long RemoteAdmTerminateNotifA( 
    /* [string][in] */ unsigned char __RPC_FAR *szComputerName,
    /* [in] */ unsigned long ulConnectionID);

            /* size is 4 */
long RemoteAdmValidateNotifA( 
    /* [string][in] */ unsigned char __RPC_FAR *szComputerName,
    /* [in] */ unsigned long ulNotifMask,
    /* [out] */ unsigned long __RPC_FAR *pulConnectionID);

            /* size is 4 */
long RemoteAdmCreateMailboxA( 
    /* [in] */ ADM_MAILBOX_INFO_A __RPC_FAR *pMailboxInfo);

            /* size is 4 */
long RemoteAdmGetMailboxPropsA( 
    /* [in] */ unsigned long dwObjID,
    /* [out] */ unsigned long __RPC_FAR *pdwObjType,
    /* [out] */ ADM_MAILBOX_INFO_A __RPC_FAR *pMailboxInfo);

            /* size is 4 */
long RemoteAdmSetMailboxPropsA( 
    /* [in] */ ADM_MAILBOX_INFO_A __RPC_FAR *pMailboxInfo);

            /* size is 4 */
long RemoteAdmCreateDistListA( 
    /* [string][in] */ unsigned char __RPC_FAR *szDLAlias,
    /* [string][in] */ unsigned char __RPC_FAR *szDLFullName,
    /* [in] */ unsigned long dwFlags,
    /* [string][in] */ unsigned char __RPC_FAR *szOwnerAlias,
    /* [string][in] */ unsigned char __RPC_FAR *szOwnerName,
    /* [in] */ unsigned long dwOwnerID,
    /* [in] */ DLM_XMIT_LIST_A __RPC_FAR *pMembers);

            /* size is 4 */
long RemoteAdmGetDLPropsA( 
    /* [in] */ unsigned long dwObjID,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szDLAlias,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szDLFullName,
    /* [out] */ unsigned long __RPC_FAR *pdwFlags,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szOwnerAlias,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szOwnerName,
    /* [out] */ unsigned long __RPC_FAR *pdwOwnerID,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szComments,
    /* [out][in] */ DLM_XMIT_LIST_A __RPC_FAR *pMembers);

            /* size is 4 */
long RemoteAdmSetDLPropsA( 
    /* [in] */ unsigned long dwObjID,
    /* [string][in] */ unsigned char __RPC_FAR *szDLAlias,
    /* [string][in] */ unsigned char __RPC_FAR *szDLFullName,
    /* [in] */ unsigned long dwFlags,
    /* [string][in] */ unsigned char __RPC_FAR *szOwnerAlias,
    /* [string][in] */ unsigned char __RPC_FAR *szOwnerName,
    /* [in] */ unsigned long dwOwnerID,
    /* [string][in] */ unsigned char __RPC_FAR *szComments,
    /* [out][in] */ DLM_XMIT_LIST_A __RPC_FAR *pMembers);

            /* size is 4 */
long RemoteAdmTerminateNotifW( 
    /* [string][in] */ wchar_t __RPC_FAR *szComputerName,
    /* [in] */ unsigned long ulConnectionID);

            /* size is 4 */
long RemoteAdmValidateNotifW( 
    /* [string][in] */ wchar_t __RPC_FAR *szComputerName,
    /* [in] */ unsigned long ulNotifMask,
    /* [out] */ unsigned long __RPC_FAR *pulConnectionID);

            /* size is 4 */
long RemoteAdmCreateMailboxW( 
    /* [in] */ ADM_MAILBOX_INFO_W __RPC_FAR *pMailboxInfo);

            /* size is 4 */
long RemoteAdmGetMailboxPropsW( 
    /* [in] */ unsigned long dwObjID,
    /* [out] */ unsigned long __RPC_FAR *pdwObjType,
    /* [out] */ ADM_MAILBOX_INFO_W __RPC_FAR *pMailboxInfo);

            /* size is 4 */
long RemoteAdmSetMailboxPropsW( 
    /* [in] */ ADM_MAILBOX_INFO_W __RPC_FAR *pMailboxInfo);

            /* size is 4 */
long RemoteAdmCreateDistListW( 
    /* [string][in] */ wchar_t __RPC_FAR *szDLAlias,
    /* [string][in] */ wchar_t __RPC_FAR *szDLFullName,
    /* [in] */ unsigned long dwFlags,
    /* [string][in] */ wchar_t __RPC_FAR *szOwnerAlias,
    /* [string][in] */ wchar_t __RPC_FAR *szOwnerName,
    /* [in] */ unsigned long dwOwnerID,
    /* [in] */ DLM_XMIT_LIST_W __RPC_FAR *pMembers);

            /* size is 4 */
long RemoteAdmGetDLPropsW( 
    /* [in] */ unsigned long dwObjID,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szDLAlias,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szDLFullName,
    /* [out] */ unsigned long __RPC_FAR *pdwFlags,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szOwnerAlias,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szOwnerName,
    /* [out] */ unsigned long __RPC_FAR *pdwOwnerID,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szComments,
    /* [out][in] */ DLM_XMIT_LIST_W __RPC_FAR *pMembers);

            /* size is 4 */
long RemoteAdmSetDLPropsW( 
    /* [in] */ unsigned long dwObjID,
    /* [string][in] */ wchar_t __RPC_FAR *szDLAlias,
    /* [string][in] */ wchar_t __RPC_FAR *szDLFullName,
    /* [in] */ unsigned long dwFlags,
    /* [string][in] */ wchar_t __RPC_FAR *szOwnerAlias,
    /* [string][in] */ wchar_t __RPC_FAR *szOwnerName,
    /* [in] */ unsigned long dwOwnerID,
    /* [string][in] */ wchar_t __RPC_FAR *szComments,
    /* [out][in] */ DLM_XMIT_LIST_W __RPC_FAR *pMembers);


extern handle_t hWINDSADM;


extern RPC_IF_HANDLE WINDSADM_v1_0_c_ifspec;
extern RPC_IF_HANDLE WINDSADM_v1_0_s_ifspec;
#endif /* __WINDSADM_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */


void __RPC_USER DLM_XMIT_LIST_A_to_xmit( DLM_XMIT_LIST_A __RPC_FAR *, DLM_ARRAY_A  __RPC_FAR * __RPC_FAR * );
void __RPC_USER DLM_XMIT_LIST_A_from_xmit( DLM_ARRAY_A  __RPC_FAR *, DLM_XMIT_LIST_A __RPC_FAR * );
void __RPC_USER DLM_XMIT_LIST_A_free_inst( DLM_XMIT_LIST_A __RPC_FAR * );
void __RPC_USER DLM_XMIT_LIST_A_free_xmit( DLM_ARRAY_A  __RPC_FAR * );

void __RPC_USER DLM_XMIT_LIST_W_to_xmit( DLM_XMIT_LIST_W __RPC_FAR *, DLM_ARRAY_W  __RPC_FAR * __RPC_FAR * );
void __RPC_USER DLM_XMIT_LIST_W_from_xmit( DLM_ARRAY_W  __RPC_FAR *, DLM_XMIT_LIST_W __RPC_FAR * );
void __RPC_USER DLM_XMIT_LIST_W_free_inst( DLM_XMIT_LIST_W __RPC_FAR * );
void __RPC_USER DLM_XMIT_LIST_W_free_xmit( DLM_ARRAY_W  __RPC_FAR * );

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
