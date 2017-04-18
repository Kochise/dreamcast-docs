/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 2.00.0102 */
/* at Mon Sep 25 11:13:21 1995
 */
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"

#ifndef __winds_h__
#define __winds_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __WINDSREM_INTERFACE_DEFINED__
#define __WINDSREM_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: WINDSREM
 * at Mon Sep 25 11:13:21 1995
 * using MIDL 2.00.0102
 ****************************************/
/* [implicit_handle][unique][version][uuid] */ 


            /* size is 4 */
long RemoteIsServerRunning( void);

            /* size is 4 */
long RemoteGetAllAccounts( 
    /* [out] */ long __RPC_FAR *pPipeNumber);

            /* size is 4 */
long RemoteFinishUpload( 
    /* [string][in] */ unsigned char __RPC_FAR *szCookie);

            /* size is 4 */
long RemoteGetContainerProps( 
    /* [in] */ unsigned long dwContainerID,
    /* [out] */ unsigned long __RPC_FAR *pdwContentCount);

            /* size is 4 */
long RemoteGetContainerRecipients( 
    /* [in] */ unsigned long dwFlags,
    /* [in] */ unsigned long dwContainerID,
    /* [out] */ long __RPC_FAR *pPipeNumber);

            /* size is 4 */
long RemoteGetPublicFoldersList( 
    /* [in] */ short nFlags,
    /* [out] */ long __RPC_FAR *pPipeNumber);

            /* size is 4 */
long RemoteGetPublicFolderMessages( 
    /* [in] */ short nFlags,
    /* [in] */ unsigned long dwFolderID,
    /* [out] */ long __RPC_FAR *pPipeNumber);

            /* size is 4 */
long RemoteChangePasswordA( 
    /* [in] */ unsigned char __RPC_FAR *szMailbox,
    /* [string][in] */ unsigned char __RPC_FAR *szOldPassword,
    /* [string][in] */ unsigned char __RPC_FAR *szNewPassword);

            /* size is 4 */
long RemoteLogonMailBoxA( 
    /* [string][in] */ unsigned char __RPC_FAR *szMailbox,
    /* [string][in] */ unsigned char __RPC_FAR *szPassword,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szFullName,
    /* [out] */ unsigned long __RPC_FAR *pdwMailboxID);

            /* size is 4 */
long RemoteLogonMailBoxAndSetNotifA( 
    /* [string][in] */ unsigned char __RPC_FAR *szMailbox,
    /* [string][in] */ unsigned char __RPC_FAR *szPassword,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szFullName,
    /* [out] */ unsigned long __RPC_FAR *pdwMailboxID,
    /* [string][in] */ unsigned char __RPC_FAR *szComputerName,
    /* [in] */ unsigned long ulNotifMask,
    /* [out] */ unsigned long __RPC_FAR *pulConnectionID);

            /* size is 4 */
long RemoteTerminateNotifA( 
    /* [string][in] */ unsigned char __RPC_FAR *szComputerName,
    /* [in] */ unsigned long ulConnectionID);

            /* size is 4 */
long RemoteValidateNotifA( 
    /* [string][in] */ unsigned char __RPC_FAR *szComputerName,
    /* [string][in] */ unsigned char __RPC_FAR *szMailboxName,
    /* [in] */ unsigned long ulNotifMask,
    /* [out] */ unsigned long __RPC_FAR *pulConnectionID);

            /* size is 4 */
long RemoteOpenMsgUploadPipeA( 
    /* [string][in] */ unsigned char __RPC_FAR *szSenderMailbox,
    /* [out] */ long __RPC_FAR *pPipeNumber,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szCookie);

            /* size is 4 */
long RemoteSendMsgToAccountA( 
    /* [string][in] */ unsigned char __RPC_FAR *szRecipAccount,
    /* [string][in] */ unsigned char __RPC_FAR *szHeaderInfo,
    /* [string][in] */ unsigned char __RPC_FAR *szCookie);

            /* size is 4 */
long RemoteOpenMsgDownloadPipeA( 
    /* [string][in] */ unsigned char __RPC_FAR *szMailbox,
    /* [out] */ unsigned long __RPC_FAR *pPipeNumber);

            /* size is 4 */
long RemoteOpenHeaderDownloadPipeA( 
    /* [string][in] */ unsigned char __RPC_FAR *szMailbox,
    /* [out] */ long __RPC_FAR *pPipeNumber);

            /* size is 4 */
long RemoteCheckNewMailA( 
    /* [string][in] */ unsigned char __RPC_FAR *szMailbox,
    /* [out] */ unsigned long __RPC_FAR *pulPending);

            /* size is 4 */
long RemoteOpenOneMsgDownloadPipeA( 
    /* [string][in] */ unsigned char __RPC_FAR *szMailbox,
    /* [out] */ long __RPC_FAR *pPipeNumber);

            /* size is 4 */
long RemoteGetRecipientPropsA( 
    /* [in] */ unsigned long dwObjID,
    /* [out] */ unsigned long __RPC_FAR *pdwUserType,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szMailboxName,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szFullName,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szJobTitle,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szOffice,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szPhone,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szAltPhone,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szFax,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szComments,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szCompany,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szDepartment,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szManagerName,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szManagerAlias,
    /* [out] */ unsigned long __RPC_FAR *pdwManagerID);

            /* size is 4 */
long RemoteGetDistListPropsA( 
    /* [in] */ unsigned long dwObjID,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szDLAlias,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szDLFullName,
    /* [out] */ unsigned long __RPC_FAR *pdwContentCount,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szOwnerAlias,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szOwnerName,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szComments);

            /* size is 4 */
long RemoteChangePasswordW( 
    /* [in] */ wchar_t __RPC_FAR *szMailbox,
    /* [string][in] */ wchar_t __RPC_FAR *szOldPassword,
    /* [string][in] */ wchar_t __RPC_FAR *szNewPassword);

            /* size is 4 */
long RemoteLogonMailBoxW( 
    /* [string][in] */ wchar_t __RPC_FAR *szMailbox,
    /* [string][in] */ wchar_t __RPC_FAR *szPassword,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szFullName,
    /* [out] */ unsigned long __RPC_FAR *pdwMailboxID);

            /* size is 4 */
long RemoteLogonMailBoxAndSetNotifW( 
    /* [string][in] */ wchar_t __RPC_FAR *szMailbox,
    /* [string][in] */ wchar_t __RPC_FAR *szPassword,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szFullName,
    /* [out] */ unsigned long __RPC_FAR *pdwMailboxID,
    /* [string][in] */ wchar_t __RPC_FAR *szComputerName,
    /* [in] */ unsigned long ulNotifMask,
    /* [out] */ unsigned long __RPC_FAR *pulConnectionID);

            /* size is 4 */
long RemoteTerminateNotifW( 
    /* [string][in] */ wchar_t __RPC_FAR *szComputerName,
    /* [in] */ unsigned long ulConnectionID);

            /* size is 4 */
long RemoteValidateNotifW( 
    /* [string][in] */ wchar_t __RPC_FAR *szComputerName,
    /* [string][in] */ wchar_t __RPC_FAR *szMailboxName,
    /* [in] */ unsigned long ulNotifMask,
    /* [out] */ unsigned long __RPC_FAR *pulConnectionID);

            /* size is 4 */
long RemoteOpenMsgUploadPipeW( 
    /* [string][in] */ wchar_t __RPC_FAR *szSenderMailbox,
    /* [out] */ long __RPC_FAR *pPipeNumber,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szCookie);

            /* size is 4 */
long RemoteSendMsgToAccountW( 
    /* [string][in] */ wchar_t __RPC_FAR *szRecipAccount,
    /* [string][in] */ wchar_t __RPC_FAR *szHeaderInfo,
    /* [string][in] */ wchar_t __RPC_FAR *szCookie);

            /* size is 4 */
long RemoteOpenMsgDownloadPipeW( 
    /* [string][in] */ wchar_t __RPC_FAR *szMailbox,
    /* [out] */ unsigned long __RPC_FAR *pPipeNumber);

            /* size is 4 */
long RemoteOpenHeaderDownloadPipeW( 
    /* [string][in] */ wchar_t __RPC_FAR *szMailbox,
    /* [out] */ long __RPC_FAR *pPipeNumber);

            /* size is 4 */
long RemoteCheckNewMailW( 
    /* [string][in] */ wchar_t __RPC_FAR *szMailbox,
    /* [out] */ unsigned long __RPC_FAR *pulPending);

            /* size is 4 */
long RemoteOpenOneMsgDownloadPipeW( 
    /* [string][in] */ wchar_t __RPC_FAR *szMailbox,
    /* [out] */ long __RPC_FAR *pPipeNumber);

            /* size is 4 */
long RemoteGetRecipientPropsW( 
    /* [in] */ unsigned long dwObjID,
    /* [out] */ unsigned long __RPC_FAR *pdwUserType,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szMailboxName,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szFullName,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szJobTitle,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szOffice,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szPhone,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szAltPhone,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szFax,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szComments,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szCompany,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szDepartment,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szManagerName,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szManagerAlias,
    /* [out] */ unsigned long __RPC_FAR *pdwManagerID);

            /* size is 4 */
long RemoteGetDistListPropsW( 
    /* [in] */ unsigned long dwObjID,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szDLAlias,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szDLFullName,
    /* [out] */ unsigned long __RPC_FAR *pdwContentCount,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szOwnerAlias,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szOwnerName,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szComments);


extern handle_t hWINDSREM;


extern RPC_IF_HANDLE WINDSREM_v1_6_c_ifspec;
extern RPC_IF_HANDLE WINDSREM_v1_6_s_ifspec;
#endif /* __WINDSREM_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
