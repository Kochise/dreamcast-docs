//+-------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1993-1997.
//
//  File:        aclapi.h
//
//  Contents:    public header file for acl and trusted server access control
//               APIs
//
//--------------------------------------------------------------------
#ifndef __ACCESS_CONTROL_API__
#define __ACCESS_CONTROL_API__


#ifdef __cplusplus
extern "C" {
#endif

#include <windows.h>
#include <accctrl.h>

DWORD
WINAPI
SetEntriesInAclA( IN  ULONG               cCountOfExplicitEntries,
                  IN  PEXPLICIT_ACCESS_A  pListOfExplicitEntries,
                  IN  PACL                OldAcl,
                  OUT PACL              * NewAcl);
DWORD
WINAPI
SetEntriesInAclW( IN  ULONG               cCountOfExplicitEntries,
                  IN  PEXPLICIT_ACCESS_W  pListOfExplicitEntries,
                  IN  PACL                OldAcl,
                  OUT PACL              * NewAcl);
#ifdef UNICODE
#define SetEntriesInAcl  SetEntriesInAclW
#else
#define SetEntriesInAcl  SetEntriesInAclA
#endif // !UNICODE


DWORD
WINAPI
GetExplicitEntriesFromAclA( IN  PACL                  pacl,
                            OUT PULONG                pcCountOfExplicitEntries,
                            OUT PEXPLICIT_ACCESS_A  * pListOfExplicitEntries);
DWORD
WINAPI
GetExplicitEntriesFromAclW( IN  PACL                  pacl,
                            OUT PULONG                pcCountOfExplicitEntries,
                            OUT PEXPLICIT_ACCESS_W  * pListOfExplicitEntries);
#ifdef UNICODE
#define GetExplicitEntriesFromAcl  GetExplicitEntriesFromAclW
#else
#define GetExplicitEntriesFromAcl  GetExplicitEntriesFromAclA
#endif // !UNICODE


DWORD
WINAPI
GetEffectiveRightsFromAclA( IN  PACL          pacl,
                            IN  PTRUSTEE_A    pTrustee,
                            OUT PACCESS_MASK  pAccessRights);
DWORD
WINAPI
GetEffectiveRightsFromAclW( IN  PACL          pacl,
                            IN  PTRUSTEE_W    pTrustee,
                            OUT PACCESS_MASK  pAccessRights);
#ifdef UNICODE
#define GetEffectiveRightsFromAcl  GetEffectiveRightsFromAclW
#else
#define GetEffectiveRightsFromAcl  GetEffectiveRightsFromAclA
#endif // !UNICODE


DWORD
WINAPI
GetAuditedPermissionsFromAclA( IN  PACL          pacl,
                               IN  PTRUSTEE_A    pTrustee,
                               OUT PACCESS_MASK  pSuccessfulAuditedRights,
                               OUT PACCESS_MASK  pFailedAuditRights);
DWORD
WINAPI
GetAuditedPermissionsFromAclW( IN  PACL          pacl,
                               IN  PTRUSTEE_W    pTrustee,
                               OUT PACCESS_MASK  pSuccessfulAuditedRights,
                               OUT PACCESS_MASK  pFailedAuditRights);
#ifdef UNICODE
#define GetAuditedPermissionsFromAcl  GetAuditedPermissionsFromAclW
#else
#define GetAuditedPermissionsFromAcl  GetAuditedPermissionsFromAclA
#endif // !UNICODE



DWORD
WINAPI
GetNamedSecurityInfoA( IN  LPSTR                pObjectName,
                       IN  SE_OBJECT_TYPE         ObjectType,
                       IN  SECURITY_INFORMATION   SecurityInfo,
                       OUT PSID                 * ppsidOowner,
                       OUT PSID                 * ppsidGroup,
                       OUT PACL                 * ppDacl,
                       OUT PACL                 * ppSacl,
                       OUT PSECURITY_DESCRIPTOR * ppSecurityDescriptor);
DWORD
WINAPI
GetNamedSecurityInfoW( IN  LPWSTR                pObjectName,
                       IN  SE_OBJECT_TYPE         ObjectType,
                       IN  SECURITY_INFORMATION   SecurityInfo,
                       OUT PSID                 * ppsidOowner,
                       OUT PSID                 * ppsidGroup,
                       OUT PACL                 * ppDacl,
                       OUT PACL                 * ppSacl,
                       OUT PSECURITY_DESCRIPTOR * ppSecurityDescriptor);
#ifdef UNICODE
#define GetNamedSecurityInfo  GetNamedSecurityInfoW
#else
#define GetNamedSecurityInfo  GetNamedSecurityInfoA
#endif // !UNICODE


DWORD
WINAPI
GetSecurityInfo( IN  HANDLE                 handle,
                 IN  SE_OBJECT_TYPE         ObjectType,
                 IN  SECURITY_INFORMATION   SecurityInfo,
                 OUT PSID                 * ppsidOowner,
                 OUT PSID                 * ppsidGroup,
                 OUT PACL                 * ppDacl,
                 OUT PACL                 * ppSacl,
                 OUT PSECURITY_DESCRIPTOR * ppSecurityDescriptor);


DWORD
WINAPI
SetNamedSecurityInfoA( IN LPSTR               pObjectName,
                       IN SE_OBJECT_TYPE        ObjectType,
                       IN SECURITY_INFORMATION  SecurityInfo,
                       IN PSID                  psidOowner,
                       IN PSID                  psidGroup,
                       IN PACL                  pDacl,
                       IN PACL                  pSacl);
DWORD
WINAPI
SetNamedSecurityInfoW( IN LPWSTR               pObjectName,
                       IN SE_OBJECT_TYPE        ObjectType,
                       IN SECURITY_INFORMATION  SecurityInfo,
                       IN PSID                  psidOowner,
                       IN PSID                  psidGroup,
                       IN PACL                  pDacl,
                       IN PACL                  pSacl);
#ifdef UNICODE
#define SetNamedSecurityInfo  SetNamedSecurityInfoW
#else
#define SetNamedSecurityInfo  SetNamedSecurityInfoA
#endif // !UNICODE


DWORD
WINAPI
SetSecurityInfo( IN HANDLE                handle,
                 IN SE_OBJECT_TYPE        ObjectType,
                 IN SECURITY_INFORMATION  SecurityInfo,
                 IN PSID                  psidOowner,
                 IN PSID                  psidGroup,
                 IN PACL                  pDacl,
                 IN PACL                  pSacl);


//----------------------------------------------------------------------------
// The following API are provided for trusted servers to use to
// implement access control on their own objects.
//----------------------------------------------------------------------------

DWORD
WINAPI
BuildSecurityDescriptorA( IN  PTRUSTEE_A              pOwner,
                          IN  PTRUSTEE_A              pGroup,
                          IN  ULONG                   cCountOfAccessEntries,
                          IN  PEXPLICIT_ACCESS_A      pListOfAccessEntries,
                          IN  ULONG                   cCountOfAuditEntries,
                          IN  PEXPLICIT_ACCESS_A      pListOfAuditEntries,
                          IN  PSECURITY_DESCRIPTOR    pOldSD,
                          OUT PULONG                  pSizeNewSD,
                          OUT PSECURITY_DESCRIPTOR  * pNewSD);
DWORD
WINAPI
BuildSecurityDescriptorW( IN  PTRUSTEE_W              pOwner,
                          IN  PTRUSTEE_W              pGroup,
                          IN  ULONG                   cCountOfAccessEntries,
                          IN  PEXPLICIT_ACCESS_W      pListOfAccessEntries,
                          IN  ULONG                   cCountOfAuditEntries,
                          IN  PEXPLICIT_ACCESS_W      pListOfAuditEntries,
                          IN  PSECURITY_DESCRIPTOR    pOldSD,
                          OUT PULONG                  pSizeNewSD,
                          OUT PSECURITY_DESCRIPTOR  * pNewSD);
#ifdef UNICODE
#define BuildSecurityDescriptor  BuildSecurityDescriptorW
#else
#define BuildSecurityDescriptor  BuildSecurityDescriptorA
#endif // !UNICODE


DWORD
WINAPI
LookupSecurityDescriptorPartsA( OUT PTRUSTEE_A         * pOwner,
                                OUT PTRUSTEE_A         * pGroup,
                                OUT PULONG               cCountOfAccessEntries,
                                OUT PEXPLICIT_ACCESS_A * pListOfAccessEntries,
                                OUT PULONG               cCountOfAuditEntries,
                                OUT PEXPLICIT_ACCESS_A * pListOfAuditEntries,
                                IN  PSECURITY_DESCRIPTOR pSD);
DWORD
WINAPI
LookupSecurityDescriptorPartsW( OUT PTRUSTEE_W         * pOwner,
                                OUT PTRUSTEE_W         * pGroup,
                                OUT PULONG               cCountOfAccessEntries,
                                OUT PEXPLICIT_ACCESS_W * pListOfAccessEntries,
                                OUT PULONG               cCountOfAuditEntries,
                                OUT PEXPLICIT_ACCESS_W * pListOfAuditEntries,
                                IN  PSECURITY_DESCRIPTOR pSD);
#ifdef UNICODE
#define LookupSecurityDescriptorParts  LookupSecurityDescriptorPartsW
#else
#define LookupSecurityDescriptorParts  LookupSecurityDescriptorPartsA
#endif // !UNICODE


//----------------------------------------------------------------------------
// The following helper API are provided for building
// access control structures.
//----------------------------------------------------------------------------

VOID
WINAPI
BuildExplicitAccessWithNameA( IN OUT PEXPLICIT_ACCESS_A  pExplicitAccess,
                              IN     LPSTR             pTrusteeName,
                              IN     DWORD               AccessPermissions,
                              IN     ACCESS_MODE         AccessMode,
                              IN     DWORD               Inheritance);
VOID
WINAPI
BuildExplicitAccessWithNameW( IN OUT PEXPLICIT_ACCESS_W  pExplicitAccess,
                              IN     LPWSTR             pTrusteeName,
                              IN     DWORD               AccessPermissions,
                              IN     ACCESS_MODE         AccessMode,
                              IN     DWORD               Inheritance);
#ifdef UNICODE
#define BuildExplicitAccessWithName  BuildExplicitAccessWithNameW
#else
#define BuildExplicitAccessWithName  BuildExplicitAccessWithNameA
#endif // !UNICODE


VOID
WINAPI
BuildImpersonateExplicitAccessWithNameA(
    IN OUT PEXPLICIT_ACCESS_A  pExplicitAccess,
    IN     LPSTR             pTrusteeName,
    IN     PTRUSTEE_A          pTrustee,
    IN     DWORD               AccessPermissions,
    IN     ACCESS_MODE         AccessMode,
    IN     DWORD               Inheritance);
VOID
WINAPI
BuildImpersonateExplicitAccessWithNameW(
    IN OUT PEXPLICIT_ACCESS_W  pExplicitAccess,
    IN     LPWSTR             pTrusteeName,
    IN     PTRUSTEE_W          pTrustee,
    IN     DWORD               AccessPermissions,
    IN     ACCESS_MODE         AccessMode,
    IN     DWORD               Inheritance);
#ifdef UNICODE
#define BuildImpersonateExplicitAccessWithName  BuildImpersonateExplicitAccessWithNameW
#else
#define BuildImpersonateExplicitAccessWithName  BuildImpersonateExplicitAccessWithNameA
#endif // !UNICODE


VOID
WINAPI
BuildTrusteeWithNameA( IN OUT PTRUSTEE_A  pTrustee,
                       IN     LPSTR     pName);
VOID
WINAPI
BuildTrusteeWithNameW( IN OUT PTRUSTEE_W  pTrustee,
                       IN     LPWSTR     pName);
#ifdef UNICODE
#define BuildTrusteeWithName  BuildTrusteeWithNameW
#else
#define BuildTrusteeWithName  BuildTrusteeWithNameA
#endif // !UNICODE


VOID
WINAPI
BuildImpersonateTrusteeA( IN OUT PTRUSTEE_A  pTrustee,
                          IN     PTRUSTEE_A  pImpersonateTrustee);
VOID
WINAPI
BuildImpersonateTrusteeW( IN OUT PTRUSTEE_W  pTrustee,
                          IN     PTRUSTEE_W  pImpersonateTrustee);
#ifdef UNICODE
#define BuildImpersonateTrustee  BuildImpersonateTrusteeW
#else
#define BuildImpersonateTrustee  BuildImpersonateTrusteeA
#endif // !UNICODE


VOID
WINAPI
BuildTrusteeWithSidA( IN OUT PTRUSTEE_A  pTrustee,
                      IN     PSID        pSid);
VOID
WINAPI
BuildTrusteeWithSidW( IN OUT PTRUSTEE_W  pTrustee,
                      IN     PSID        pSid);
#ifdef UNICODE
#define BuildTrusteeWithSid  BuildTrusteeWithSidW
#else
#define BuildTrusteeWithSid  BuildTrusteeWithSidA
#endif // !UNICODE


LPSTR
WINAPI
GetTrusteeNameA( IN PTRUSTEE_A  pTrustee);
LPWSTR
WINAPI
GetTrusteeNameW( IN PTRUSTEE_W  pTrustee);
#ifdef UNICODE
#define GetTrusteeName  GetTrusteeNameW
#else
#define GetTrusteeName  GetTrusteeNameA
#endif // !UNICODE


TRUSTEE_TYPE
WINAPI
GetTrusteeTypeA( IN PTRUSTEE_A  pTrustee);
TRUSTEE_TYPE
WINAPI
GetTrusteeTypeW( IN PTRUSTEE_W  pTrustee);
#ifdef UNICODE
#define GetTrusteeType  GetTrusteeTypeW
#else
#define GetTrusteeType  GetTrusteeTypeA
#endif // !UNICODE


TRUSTEE_FORM
WINAPI
GetTrusteeFormA( IN PTRUSTEE_A  pTrustee);
TRUSTEE_FORM
WINAPI
GetTrusteeFormW( IN PTRUSTEE_W  pTrustee);
#ifdef UNICODE
#define GetTrusteeForm  GetTrusteeFormW
#else
#define GetTrusteeForm  GetTrusteeFormA
#endif // !UNICODE



MULTIPLE_TRUSTEE_OPERATION
WINAPI
GetMultipleTrusteeOperationA( IN PTRUSTEE_A  pTrustee);
MULTIPLE_TRUSTEE_OPERATION
WINAPI
GetMultipleTrusteeOperationW( IN PTRUSTEE_W  pTrustee);
#ifdef UNICODE
#define GetMultipleTrusteeOperation  GetMultipleTrusteeOperationW
#else
#define GetMultipleTrusteeOperation  GetMultipleTrusteeOperationA
#endif // !UNICODE



PTRUSTEE_A
WINAPI
GetMultipleTrusteeA( IN PTRUSTEE_A  pTrustee);
PTRUSTEE_W
WINAPI
GetMultipleTrusteeW( IN PTRUSTEE_W  pTrustee);
#ifdef UNICODE
#define GetMultipleTrustee  GetMultipleTrusteeW
#else
#define GetMultipleTrustee  GetMultipleTrusteeA
#endif // !UNICODE


#if(_WIN32_WINNT >= 0x0500)
//----------------------------------------------------------------------------
//
//                                  NT5 APIs
//
//----------------------------------------------------------------------------

DWORD
WINAPI
GetNamedSecurityInfoExA(IN   LPCSTR                lpObject,
                        IN   SE_OBJECT_TYPE          ObjectType,
                        IN   SECURITY_INFORMATION    SecurityInfo,
                        IN   LPCSTR                lpProvider,
                        IN   LPCSTR                lpProperty,
                        OUT  PACTRL_ACCESSA         *ppAccessList,
                        OUT  PACTRL_AUDITA          *ppAuditList,
                        OUT  LPSTR                *lppOwner,
                        OUT  LPSTR                *lppGroup);
DWORD
WINAPI
GetNamedSecurityInfoExW(IN   LPCWSTR                lpObject,
                        IN   SE_OBJECT_TYPE          ObjectType,
                        IN   SECURITY_INFORMATION    SecurityInfo,
                        IN   LPCWSTR                lpProvider,
                        IN   LPCWSTR                lpProperty,
                        OUT  PACTRL_ACCESSW         *ppAccessList,
                        OUT  PACTRL_AUDITW          *ppAuditList,
                        OUT  LPWSTR                *lppOwner,
                        OUT  LPWSTR                *lppGroup);
#ifdef UNICODE
#define GetNamedSecurityInfoEx  GetNamedSecurityInfoExW
#else
#define GetNamedSecurityInfoEx  GetNamedSecurityInfoExA
#endif // !UNICODE


DWORD
WINAPI
SetNamedSecurityInfoExA(IN    LPCSTR               lpObject,
                        IN    SE_OBJECT_TYPE         ObjectType,
                        IN    SECURITY_INFORMATION   SecurityInfo,
                        IN    LPCSTR               lpProvider,
                        IN    PACTRL_ACCESSA         pAccessList,
                        IN    PACTRL_AUDITA          pAuditList,
                        IN    LPSTR                lpOwner,
                        IN    LPSTR                lpGroup,
                        IN    PACTRL_OVERLAPPED      pOverlapped);
DWORD
WINAPI
SetNamedSecurityInfoExW(IN    LPCWSTR               lpObject,
                        IN    SE_OBJECT_TYPE         ObjectType,
                        IN    SECURITY_INFORMATION   SecurityInfo,
                        IN    LPCWSTR               lpProvider,
                        IN    PACTRL_ACCESSW         pAccessList,
                        IN    PACTRL_AUDITW          pAuditList,
                        IN    LPWSTR                lpOwner,
                        IN    LPWSTR                lpGroup,
                        IN    PACTRL_OVERLAPPED      pOverlapped);
#ifdef UNICODE
#define SetNamedSecurityInfoEx  SetNamedSecurityInfoExW
#else
#define SetNamedSecurityInfoEx  SetNamedSecurityInfoExA
#endif // !UNICODE


DWORD
WINAPI
GetSecurityInfoExA(IN    HANDLE                  hObject,
                   IN    SE_OBJECT_TYPE          ObjectType,
                   IN    SECURITY_INFORMATION    SecurityInfo,
                   IN    LPCSTR                lpProvider,
                   IN    LPCSTR                lpProperty,
                   OUT   PACTRL_ACCESSA         *ppAccessList,
                   OUT   PACTRL_AUDITA          *ppAuditList,
                   OUT   LPSTR                *lppOwner,
                   OUT   LPSTR                *lppGroup);
DWORD
WINAPI
GetSecurityInfoExW(IN    HANDLE                  hObject,
                   IN    SE_OBJECT_TYPE          ObjectType,
                   IN    SECURITY_INFORMATION    SecurityInfo,
                   IN    LPCWSTR                lpProvider,
                   IN    LPCWSTR                lpProperty,
                   OUT   PACTRL_ACCESSW         *ppAccessList,
                   OUT   PACTRL_AUDITW          *ppAuditList,
                   OUT   LPWSTR                *lppOwner,
                   OUT   LPWSTR                *lppGroup);
#ifdef UNICODE
#define GetSecurityInfoEx  GetSecurityInfoExW
#else
#define GetSecurityInfoEx  GetSecurityInfoExA
#endif // !UNICODE



DWORD
WINAPI
SetSecurityInfoExA(IN    HANDLE                 hObject,
                   IN    SE_OBJECT_TYPE         ObjectType,
                   IN    SECURITY_INFORMATION   SecurityInfo,
                   IN    LPCSTR               lpProvider,
                   IN    PACTRL_ACCESSA         pAccessList,
                   IN    PACTRL_AUDITA          pAuditList,
                   IN    LPSTR                lpOwner,
                   IN    LPSTR                lpGroup,
                   OUT   PACTRL_OVERLAPPED      pOverlapped);
DWORD
WINAPI
SetSecurityInfoExW(IN    HANDLE                 hObject,
                   IN    SE_OBJECT_TYPE         ObjectType,
                   IN    SECURITY_INFORMATION   SecurityInfo,
                   IN    LPCWSTR               lpProvider,
                   IN    PACTRL_ACCESSW         pAccessList,
                   IN    PACTRL_AUDITW          pAuditList,
                   IN    LPWSTR                lpOwner,
                   IN    LPWSTR                lpGroup,
                   OUT   PACTRL_OVERLAPPED      pOverlapped);
#ifdef UNICODE
#define SetSecurityInfoEx  SetSecurityInfoExW
#else
#define SetSecurityInfoEx  SetSecurityInfoExA
#endif // !UNICODE


DWORD
WINAPI
ConvertAccessToSecurityDescriptorA(IN  PACTRL_ACCESSA        pAccessList,
                                   IN  PACTRL_AUDITA         pAuditList,
                                   IN  LPCSTR              lpOwner,
                                   IN  LPCSTR              lpGroup,
                                   OUT PSECURITY_DESCRIPTOR *ppSecDescriptor);
DWORD
WINAPI
ConvertAccessToSecurityDescriptorW(IN  PACTRL_ACCESSW        pAccessList,
                                   IN  PACTRL_AUDITW         pAuditList,
                                   IN  LPCWSTR              lpOwner,
                                   IN  LPCWSTR              lpGroup,
                                   OUT PSECURITY_DESCRIPTOR *ppSecDescriptor);
#ifdef UNICODE
#define ConvertAccessToSecurityDescriptor  ConvertAccessToSecurityDescriptorW
#else
#define ConvertAccessToSecurityDescriptor  ConvertAccessToSecurityDescriptorA
#endif // !UNICODE


DWORD
WINAPI
ConvertSecurityDescriptorToAccessA(IN  HANDLE               hObject,
                                   IN  SE_OBJECT_TYPE       ObjectType,
                                   IN  PSECURITY_DESCRIPTOR pSecDescriptor,
                                   OUT PACTRL_ACCESSA      *ppAccessList,
                                   OUT PACTRL_AUDITA       *ppAuditList,
                                   OUT LPSTR             *lppOwner,
                                   OUT LPSTR             *lppGroup);
DWORD
WINAPI
ConvertSecurityDescriptorToAccessW(IN  HANDLE               hObject,
                                   IN  SE_OBJECT_TYPE       ObjectType,
                                   IN  PSECURITY_DESCRIPTOR pSecDescriptor,
                                   OUT PACTRL_ACCESSW      *ppAccessList,
                                   OUT PACTRL_AUDITW       *ppAuditList,
                                   OUT LPWSTR             *lppOwner,
                                   OUT LPWSTR             *lppGroup);
#ifdef UNICODE
#define ConvertSecurityDescriptorToAccess  ConvertSecurityDescriptorToAccessW
#else
#define ConvertSecurityDescriptorToAccess  ConvertSecurityDescriptorToAccessA
#endif // !UNICODE


DWORD
WINAPI
ConvertSecurityDescriptorToAccessNamedA(IN  LPCSTR             lpObject,
                                        IN  SE_OBJECT_TYPE       ObjectType,
                                        IN  PSECURITY_DESCRIPTOR pSecDescriptor,
                                        OUT PACTRL_ACCESSA      *ppAccessList,
                                        OUT PACTRL_AUDITA       *ppAuditList,
                                        OUT LPSTR             *lppOwner,
                                        OUT LPSTR             *lppGroup);
DWORD
WINAPI
ConvertSecurityDescriptorToAccessNamedW(IN  LPCWSTR             lpObject,
                                        IN  SE_OBJECT_TYPE       ObjectType,
                                        IN  PSECURITY_DESCRIPTOR pSecDescriptor,
                                        OUT PACTRL_ACCESSW      *ppAccessList,
                                        OUT PACTRL_AUDITW       *ppAuditList,
                                        OUT LPWSTR             *lppOwner,
                                        OUT LPWSTR             *lppGroup);
#ifdef UNICODE
#define ConvertSecurityDescriptorToAccessNamed  ConvertSecurityDescriptorToAccessNamedW
#else
#define ConvertSecurityDescriptorToAccessNamed  ConvertSecurityDescriptorToAccessNamedA
#endif // !UNICODE




DWORD
WINAPI
SetEntriesInAccessListA(IN  ULONG                cEntries,
                        IN  PACTRL_ACCESS_ENTRYA pAccessEntryList,
                        IN  ACCESS_MODE          AccessMode,
                        IN  LPCSTR             lpProperty,
                        IN  PACTRL_ACCESSA       pOldList,
                        OUT PACTRL_ACCESSA      *ppNewList);
DWORD
WINAPI
SetEntriesInAccessListW(IN  ULONG                cEntries,
                        IN  PACTRL_ACCESS_ENTRYW pAccessEntryList,
                        IN  ACCESS_MODE          AccessMode,
                        IN  LPCWSTR             lpProperty,
                        IN  PACTRL_ACCESSW       pOldList,
                        OUT PACTRL_ACCESSW      *ppNewList);
#ifdef UNICODE
#define SetEntriesInAccessList  SetEntriesInAccessListW
#else
#define SetEntriesInAccessList  SetEntriesInAccessListA
#endif // !UNICODE



DWORD
WINAPI
SetEntriesInAuditListA(IN  ULONG                 cEntries,
                       IN  PACTRL_ACCESS_ENTRYA  pAccessEntryList,
                       IN  ACCESS_MODE           AccessMode,
                       IN  LPCSTR              lpProperty,
                       IN  PACTRL_AUDITA         pOldList,
                       OUT PACTRL_AUDITA        *ppNewList);
DWORD
WINAPI
SetEntriesInAuditListW(IN  ULONG                 cEntries,
                       IN  PACTRL_ACCESS_ENTRYW  pAccessEntryList,
                       IN  ACCESS_MODE           AccessMode,
                       IN  LPCWSTR              lpProperty,
                       IN  PACTRL_AUDITW         pOldList,
                       OUT PACTRL_AUDITW        *ppNewList);
#ifdef UNICODE
#define SetEntriesInAuditList  SetEntriesInAuditListW
#else
#define SetEntriesInAuditList  SetEntriesInAuditListA
#endif // !UNICODE

DWORD
WINAPI
TrusteeAccessToObjectA(IN        LPCSTR           lpObject,
                       IN        SE_OBJECT_TYPE     ObjectType,
                       IN        LPCSTR           lpProvider,
                       IN        PTRUSTEE_A         pTrustee,
                       IN        ULONG              cEntries,
                       IN OUT    PTRUSTEE_ACCESSA   pTrusteeAccess);
DWORD
WINAPI
TrusteeAccessToObjectW(IN        LPCWSTR           lpObject,
                       IN        SE_OBJECT_TYPE     ObjectType,
                       IN        LPCWSTR           lpProvider,
                       IN        PTRUSTEE_W         pTrustee,
                       IN        ULONG              cEntries,
                       IN OUT    PTRUSTEE_ACCESSW   pTrusteeAccess);
#ifdef UNICODE
#define TrusteeAccessToObject  TrusteeAccessToObjectW
#else
#define TrusteeAccessToObject  TrusteeAccessToObjectA
#endif // !UNICODE



DWORD
WINAPI
GetOverlappedAccessResults( IN  PACTRL_OVERLAPPED   pOverlapped,
                            IN  BOOL                fWaitForCompletion,
                            OUT PDWORD              pResult,
                            OUT PULONG              pcItemsProcessed OPTIONAL);



DWORD
WINAPI
CancelOverlappedAccess(IN       PACTRL_OVERLAPPED   pOverlapped);


DWORD
WINAPI
GetAccessPermissionsForObjectA(IN   LPCSTR             lpObject,
                               IN   SE_OBJECT_TYPE       ObjectType,
                               IN   LPCSTR             lpObjType,
                               IN   LPCSTR             lpProvider,
                               OUT  PULONG               pcEntries,
                               OUT  PACTRL_ACCESS_INFOA *ppAccessInfoList,
                               OUT  PULONG               pcRights,
                               OUT  PACTRL_CONTROL_INFOA *ppRightsList,
                               OUT  PULONG               pfAccessFlags);
DWORD
WINAPI
GetAccessPermissionsForObjectW(IN   LPCWSTR             lpObject,
                               IN   SE_OBJECT_TYPE       ObjectType,
                               IN   LPCWSTR             lpObjType,
                               IN   LPCWSTR             lpProvider,
                               OUT  PULONG               pcEntries,
                               OUT  PACTRL_ACCESS_INFOW *ppAccessInfoList,
                               OUT  PULONG               pcRights,
                               OUT  PACTRL_CONTROL_INFOW *ppRightsList,
                               OUT  PULONG               pfAccessFlags);
#ifdef UNICODE
#define GetAccessPermissionsForObject  GetAccessPermissionsForObjectW
#else
#define GetAccessPermissionsForObject  GetAccessPermissionsForObjectA
#endif // !UNICODE

//
// Temporary requirement for the technology preview, no longer required
//
#define AccProvInit(err)
#endif /* _WIN32_WINNT >=  0x0500 */


#ifdef __cplusplus
}
#endif


#endif // __ACCESS_CONTROL_API__

