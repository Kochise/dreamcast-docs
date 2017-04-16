// sec.cpp - implements the C++ class to encapsulate the security API

#include "stdafx.h"
#include <windows.h>
#include "sec.h"
#include "resource.h"

#include "secdialo.h"

#include "examstff.h"

#include "malloc.h"


// helper function

BOOL SetSpecificPrivilegeInAccessToken(LPCSTR lpPrivType,BOOL bEnabled)
{
  HANDLE           hProcess;
  HANDLE           hAccessToken;
  LUID             luidPrivilegeLUID;
  TOKEN_PRIVILEGES tpTokenPrivilege;
  BOOL bReturn = FALSE;

  hProcess = GetCurrentProcess();
  if (!hProcess)
  { 
    return(FALSE);
  }

  if (!OpenProcessToken(hProcess,
                        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
                        &hAccessToken))
  { 
    return(FALSE);
  }

   if (!LookupPrivilegeValue(NULL,
                            lpPrivType,
                            &luidPrivilegeLUID))
  { 
    goto ErrorExit;
  }

  
  tpTokenPrivilege.PrivilegeCount = 1;
  tpTokenPrivilege.Privileges[0].Luid = luidPrivilegeLUID;
  tpTokenPrivilege.Privileges[0].Attributes = bEnabled?SE_PRIVILEGE_ENABLED:0;
  SetLastError(ERROR_SUCCESS);
  bReturn = AdjustTokenPrivileges (hAccessToken,
                         FALSE,  // Do not disable all
                         &tpTokenPrivilege,
                         sizeof(TOKEN_PRIVILEGES),
                         NULL,   // Ignore previous info
                         NULL);  // Ignore previous info
  if (GetLastError()!=ERROR_SUCCESS) bReturn = FALSE;
  ErrorExit:
  CloseHandle(hAccessToken);
  return bReturn;
}


BOOL SetPrivilegeInAccessToken(BOOL bEnabled)
{
 return SetSpecificPrivilegeInAccessToken("SeSecurityPrivilege",bEnabled);
}


CSecureableObject::CSecureableObject(BOOL bProtected)
{
 DWORD dwDACLLength;
 PSID pcSid = NULL;
 ZeroOut();
 SID_IDENTIFIER_AUTHORITY siaWorld = SECURITY_WORLD_SID_AUTHORITY;
 int iTempSidLength;
 m_pSD = malloc(sizeof(SECURITY_DESCRIPTOR)); 
 if (!m_pSD) 
 {
  SetLastError(ERROR_NOT_ENOUGH_MEMORY);
  goto ErrorExit;
 };
 if (!InitializeSecurityDescriptor(m_pSD,SECURITY_DESCRIPTOR_REVISION))
  goto ErrorExit;
 iTempSidLength = GetSidLengthRequired(1); // this can not fail
 pcSid = (PSID)malloc(iTempSidLength); 
 if (!pcSid)
 {
  SetLastError(ERROR_NOT_ENOUGH_MEMORY);
  goto ErrorExit;
 };
 dwDACLLength = sizeof (ACL) +sizeof (ACCESS_ALLOWED_ACE) - sizeof (DWORD) + iTempSidLength;							
 m_pDACL = (PACL) malloc(dwDACLLength);      
 if (!m_pDACL)
 {
  SetLastError(ERROR_NOT_ENOUGH_MEMORY);
  goto ErrorExit;
 }; 
 if (!InitializeAcl(m_pDACL,dwDACLLength,ACL_REVISION) ||!InitializeSid(pcSid,&siaWorld,1))
  goto ErrorExit;
 *(GetSidSubAuthority(pcSid,0)) = SECURITY_WORLD_RID;
 if (bProtected)   // this works like a empty dacl - fully protected
 {
  if (!AddAccessAllowedAce(m_pDACL,ACL_REVISION,NULL,pcSid))  // RAc
   goto ErrorExit;
 }
 else                // this works like a NULL dacl - unprotected
 {
  if (!AddAccessAllowedAce(m_pDACL,ACL_REVISION,GENERIC_ALL|STANDARD_RIGHTS_ALL|SPECIFIC_RIGHTS_ALL,pcSid))
  goto ErrorExit;
 };
 if (!SetSecurityDescriptorDacl(m_pSD,TRUE,m_pDACL,FALSE)) goto ErrorExit;
// at this point we need to go through the same procedure w/ a SACL...
 if (pcSid) free (pcSid);
 pcSid = NULL;             // we reuse this data structure.
 iTempSidLength = GetSidLengthRequired(1); // this can not fail
 pcSid = (PSID)malloc(iTempSidLength); 
 if (!pcSid)
 {
  SetLastError(ERROR_NOT_ENOUGH_MEMORY);
  goto ErrorExit;
 };
 dwDACLLength = sizeof (ACL) +sizeof (SYSTEM_AUDIT_ACE) - sizeof (DWORD) + iTempSidLength;							
 m_pSACL = (PACL) malloc(dwDACLLength);      
 if (!m_pSACL)
 {
  SetLastError(ERROR_NOT_ENOUGH_MEMORY);
  goto ErrorExit;
 }; 
 if (!InitializeAcl(m_pSACL,dwDACLLength,ACL_REVISION) ||!InitializeSid(pcSid,&siaWorld,1))
  goto ErrorExit;
 *(GetSidSubAuthority(pcSid,0)) = SECURITY_WORLD_RID;
 if (!AddAuditAccessAce(m_pSACL,ACL_REVISION,GENERIC_ALL|STANDARD_RIGHTS_ALL|SPECIFIC_RIGHTS_ALL,pcSid,TRUE,TRUE)) goto ErrorExit;
 if (!SetSecurityDescriptorSacl(m_pSD,TRUE,m_pSACL,FALSE)) goto ErrorExit;

 SetLastError(ERROR_SUCCESS);
ErrorExit:
 m_iSecErrorCode = GetLastError(); 
 if (pcSid) free (pcSid);
};

CSecureableObject::~CSecureableObject()
{
 FreeDataStructures();
};


BOOL CSecureableObject::AddRightsTo(PSTR pDomainName,PSTR pAccountName,DWORD dwAccessMask,BOOL bGranted)
{
 DWORD dwDACLLength;
 char *pcDomainName;
 BYTE *pcSid;
 BOOL bHasDacl,bHasDefaulted;
 PACL pCurrentAcl=NULL;
 PACL pNewACL=NULL;
 PSECURITY_DESCRIPTOR pNewSD=NULL;
 if (!GetSIDFromName(pDomainName,pAccountName,&pcSid,&pcDomainName)) 
 {
  SetLastError(m_iSecErrorCode);
  goto ErrorExit;
 };
 UINT dwNumberOfAces;
 DWORD dwAceSize;
 if (!GetTheDescriptor()) goto ErrorExit;  // this will implicitly set m_pSD
 if (!GetSecurityDescriptorDacl(m_pSD,&bHasDacl, (PACL *)&pCurrentAcl,&bHasDefaulted))
    goto ErrorExit;
 dwNumberOfAces = pCurrentAcl->AceCount;
 dwAceSize = pCurrentAcl->AclSize;
 DWORD dwCurrentSecurityDescriptorLength;
 dwDACLLength	= dwAceSize + sizeof (ACCESS_ALLOWED_ACE) - sizeof (DWORD) +
				  GetLengthSid(pcSid);		// we must assume here that the sid is valid...
 pNewACL = (PACL) malloc(dwDACLLength); 
 if (!pNewACL) 
 { 
  SetLastError(ERROR_NOT_ENOUGH_MEMORY);
  goto ErrorExit;
 };   
 dwCurrentSecurityDescriptorLength=GetSecurityDescriptorLength(m_pSD);  
 pNewSD = malloc(dwDACLLength+dwCurrentSecurityDescriptorLength);
 if (!pNewSD) 
 {
  SetLastError(ERROR_NOT_ENOUGH_MEMORY);
  free (pNewACL);
  goto ErrorExit;
 };
 if (!InitializeSecurityDescriptor(pNewSD,SECURITY_DESCRIPTOR_REVISION)) goto ErrorExit;
 if (!InitializeAcl(pNewACL,dwDACLLength,ACL_REVISION)) goto ErrorExit;
 UINT iLoop;
 void *pTempACL;

// beginning of specific code -- depending on whether we want to grant or deny
// access, we must either add an access allowed ace at the end, or tuck a denied ace up front...
 if (!bGranted)
  if (!AddAccessDeniedAce(pNewACL,ACL_REVISION,dwAccessMask,(PSID)pcSid)) goto ErrorExit;
  for (iLoop = 0; iLoop < dwNumberOfAces; iLoop++)
  {
   if (! GetAce(pCurrentAcl, iLoop, &pTempACL)) goto ErrorExit;
   if (!AddAce(pNewACL,ACL_REVISION,MAXDWORD,pTempACL,((PACE_HEADER)pTempACL)->AceSize)) goto ErrorExit;
  };
 if (bGranted)
  if (!AddAccessAllowedAce(pNewACL,ACL_REVISION,dwAccessMask,(PSID)pcSid)) goto ErrorExit;

// now we may nuke the old SD because we don't need it anymore.
// note that we keep it until we know that security was set correctly. This way,
//if anything fails, we'll still have the old one around...
 if (!IsValidAcl(pNewACL)) goto ErrorExit;
 if (!IsValidSecurityDescriptor(pNewSD))	goto ErrorExit;
 if (!SetSecurityDescriptorDacl(pNewSD,TRUE,pNewACL,FALSE)) goto ErrorExit;
// now copy all of the other relevant stuff to the new SD
 if (m_pOwner && 
     !SetSecurityDescriptorOwner(pNewSD,m_pOwner,FALSE)) goto ErrorExit;
 if (m_pSACL &&
     !SetSecurityDescriptorSacl(pNewSD,TRUE,m_pSACL,FALSE)) goto ErrorExit;
 if (m_pPrimaryGroup &&
     !SetSecurityDescriptorGroup(pNewSD,m_pPrimaryGroup,FALSE)) goto ErrorExit;
 free(pCurrentAcl);
 free(m_pSD); 
 m_pSD = pNewSD;
 free(m_pDACL);
 m_pDACL=pNewACL;
 if (!SetTheDescriptor()) goto ErrorExit;
// free (pACL);

 return TRUE;
 ErrorExit:
 m_iSecErrorCode = GetLastError();
 if (pNewACL) free (pNewACL);
 if (pNewSD) free (pNewSD);
 return FALSE;
};


BOOL CSecureableObject::RevokePreviouslyGrantedAccess(PSTR pAccountName,PSTR pDomainName)
{
 PACL pNewACL = NULL;
 PACL pCurrentAcl=NULL;
 DWORD dwDACLLength;
 char *pcDomainName;
 BYTE *pcSid;
 PSECURITY_DESCRIPTOR pNewSD = NULL;
 UINT iOffendingIndex;

 if (!GetSIDFromName(pDomainName,pAccountName,&pcSid,&pcDomainName)) 
 { 
  SetLastError(m_iSecErrorCode);
  goto ErrorExit;
 };
 
 BOOL bHasDacl;
 BOOL bHasDefaulted;
 UINT dwNumberOfAces;
 DWORD dwAceSize;
 if (!GetTheDescriptor()) goto ErrorExit;  // this will implicitly set m_pSD
 if (!GetSecurityDescriptorDacl(m_pSD,&bHasDacl, (PACL *)&pCurrentAcl,&bHasDefaulted))
    goto ErrorExit;
 dwNumberOfAces = pCurrentAcl->AceCount;
 dwAceSize = pCurrentAcl->AclSize;
 DWORD dwCurrentSecurityDescriptorLength;
 dwCurrentSecurityDescriptorLength=GetSecurityDescriptorLength(m_pSD);
// here we figure out if an ace with the requested sid is already in the acl...
 UINT iLoop;
 void *pTempACL;
 for (iLoop = 0; iLoop < dwNumberOfAces; iLoop++)
 {
  if (! GetAce(pCurrentAcl, iLoop, &pTempACL)) goto ErrorExit;
  if (EqualSid ((PSID) &(((PACCESS_ALLOWED_ACE)pTempACL)->SidStart),pcSid))
  break;
 };
 if (iLoop >= dwNumberOfAces) 
 { 
  SetLastError(ERROR_PRIVILEGE_NOT_HELD);
  goto ErrorExit;    // didn't find the sid...
 };
 iOffendingIndex = iLoop;
 dwDACLLength = dwAceSize - ((PACE_HEADER)pTempACL)->AceSize; 
 pNewACL = (PACL) malloc(dwDACLLength); 
 if (!pNewACL) 
 {
  SetLastError(ERROR_NOT_ENOUGH_MEMORY);
  goto ErrorExit;
 };
 pNewSD = malloc(dwDACLLength+dwCurrentSecurityDescriptorLength);
 if (!pNewSD) 
 {
  SetLastError(ERROR_NOT_ENOUGH_MEMORY);
  goto ErrorExit;
 };
 if (!InitializeSecurityDescriptor(pNewSD,SECURITY_DESCRIPTOR_REVISION)) goto ErrorExit;
 if (!InitializeAcl(pNewACL,dwDACLLength,ACL_REVISION)) goto ErrorExit;
// now we copy the old ace to the new one, of course leaving out the offending sid...
 for (iLoop = 0; iLoop < dwNumberOfAces; iLoop++)
 {
  if (iLoop == iOffendingIndex) continue;
  if (! GetAce(pCurrentAcl, iLoop, &pTempACL)) goto ErrorExit;
  if (!AddAce(pNewACL,ACL_REVISION,MAXDWORD,pTempACL,((PACE_HEADER)pTempACL)->AceSize))
   goto ErrorExit;
 };
 // now we may nuke the old ACL because we don't need it anymore...
 if (!IsValidAcl(pNewACL)) goto ErrorExit;
 if (!IsValidSecurityDescriptor(pNewSD))	goto ErrorExit;
 if (!SetSecurityDescriptorDacl(pNewSD,TRUE,pNewACL,FALSE)) goto ErrorExit;
// now copy all of the other relevant stuff to the new SD
 if (m_pOwner && 
     !SetSecurityDescriptorOwner(pNewSD,m_pOwner,FALSE)) goto ErrorExit;
 if (m_pSACL &&
     !SetSecurityDescriptorSacl(pNewSD,TRUE,m_pSACL,FALSE)) goto ErrorExit;
 if (m_pPrimaryGroup &&
     !SetSecurityDescriptorGroup(pNewSD,m_pPrimaryGroup,FALSE)) goto ErrorExit;
 free(pCurrentAcl);
 free(m_pSD); 
 m_pSD = pNewSD;
 free(m_pDACL);
 m_pDACL=pNewACL;
 if (!SetTheDescriptor()) goto ErrorExit;
// free (pACL);
 return TRUE;
 ErrorExit:
 m_iSecErrorCode = GetLastError();
 if (pNewACL) free (pNewACL);
 if (pNewSD) free (pNewSD);
 return FALSE;
};


// helper functions

BOOL CSecureableObject::GetSIDFromName(PSTR pDomainName,
                                       PSTR pAccountName,
                                       BYTE **pcSid,
                                       char **pcDomainName)
{ SID_NAME_USE su;
 DWORD dwSidLength=0;
 unsigned long iBufLen=0;

 /* we first must determine the SID that belongs to the user. This happens in
    two steps: First, determine how much space is needed for the SID and
	domain buffers. Then, call the function again with the previously allocated
	buffers. */
 if (!(LookupAccountName(pDomainName,pAccountName,*pcSid,&dwSidLength,*pcDomainName,
       &iBufLen,&su)))
 {
// this call will fail in any case, or we are in trouble.
  if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
// didn't find the name, or something else went wrong...
  {
   m_iSecErrorCode = GetLastError();
   return FALSE;
  }; 
  *pcSid=(BYTE *)malloc(dwSidLength);    
  if (!*pcSid) 
  {
   m_iSecErrorCode = ERROR_NOT_ENOUGH_MEMORY;
   return FALSE;
  };
  *pcDomainName=(char *)malloc(iBufLen); 
  if (!*pcDomainName) 
  {
   free (*pcSid);
   m_iSecErrorCode = ERROR_NOT_ENOUGH_MEMORY; 
   return FALSE;
  };
  if (!LookupAccountName(pDomainName,pAccountName,*pcSid,&dwSidLength,*pcDomainName,
        &iBufLen,&su))
  {
   free (*pcSid);
   free (*pcDomainName);
   m_iSecErrorCode = GetLastError();
   return FALSE;
  };
  if (!IsValidSid(*pcSid)) 
  {
   free (*pcSid);
   free (*pcDomainName);
   m_iSecErrorCode = GetLastError();
   return FALSE;
  };
 };
 return TRUE;
};

BOOL CSecureableObject::AddSecurity(DWORD dwAccessMask,LPSTR lpTitleString)
{
 CSecDialog csD;
 csD.m_Title = lpTitleString;
 if (csD.DoModal() == IDCANCEL)
 { 
  m_iSecErrorCode = ERROR_REQUEST_ABORTED;
  return FALSE;
 };
 switch (csD.m_iButtonPushed)
 { 
  case IDC_RADIO2:  // denied
  if(!AddRightsTo((char *)(const char *)csD.m_DomainName,
                              (char *)(const char *)csD.m_UserName,
                              dwAccessMask,
                              FALSE))
  return FALSE;
  break;
  case IDC_RADIO1: // granted
  if(!AddRightsTo((char *)(const char *)csD.m_DomainName,
                               (char *)(const char *)csD.m_UserName,
                               dwAccessMask,
                               TRUE))
  return FALSE;
  break;
  case IDC_RADIO3: //revoked
  if (!RevokePreviouslyGrantedAccess((char *)(const char *)csD.m_UserName,
                                                (char *)(const char *)csD.m_DomainName))
  return FALSE;
 };
 return TRUE;
};

BOOL CSecureableObject::BuildSD(PSECURITY_DESCRIPTOR pSelfRelativeReturnSD)
{
 DWORD iSDSize,iDACLSize,iSACLSize,iOwnerSize,iGroupSize;
 iSDSize=0;
 iDACLSize=0;
 iSACLSize=0;
 iOwnerSize=0;
 iGroupSize=0;
 if (!MakeAbsoluteSD(pSelfRelativeReturnSD,
                       m_pSD,&iSDSize,
					   m_pDACL,&iDACLSize,
					   m_pSACL,&iSACLSize,
					   m_pOwner,&iOwnerSize,
					   m_pPrimaryGroup,&iGroupSize)
	   && GetLastError() == ERROR_INSUFFICIENT_BUFFER)
 {	 // this is tedious: Allocate all the data structures and try again...
  if (iSDSize)
  { 
   m_pSD = malloc(iSDSize);
   if (!m_pSD) 
   {
    SetLastError(ERROR_NOT_ENOUGH_MEMORY);
    goto ErrorExit;
   };
  };
  if (iDACLSize)
  {
   m_pDACL = (PACL)malloc(iDACLSize);
   if (!m_pDACL) 
   {
    SetLastError(ERROR_NOT_ENOUGH_MEMORY);
    goto ErrorExit;
   };
  };
  if (iSACLSize)
  {
   m_pSACL = (PACL)malloc(iSACLSize);
   if (!m_pSACL) 
   {
    SetLastError(ERROR_NOT_ENOUGH_MEMORY);
    goto ErrorExit;
   };
  };
  if (iOwnerSize)
  {
   m_pOwner = malloc(iOwnerSize);
   if (!m_pOwner) 
   {
    SetLastError(ERROR_NOT_ENOUGH_MEMORY);
    goto ErrorExit;
   };
  };
  if (iGroupSize)
  {
   m_pPrimaryGroup = malloc(iGroupSize);
   if (!m_pPrimaryGroup) 
   {
    SetLastError(ERROR_NOT_ENOUGH_MEMORY);
    goto ErrorExit;
   };
  }; // end of allocation stuff
  if (!MakeAbsoluteSD(pSelfRelativeReturnSD,
                       m_pSD,&iSDSize,
					   m_pDACL,&iDACLSize,
					   m_pSACL,&iSACLSize,
					   m_pOwner,&iOwnerSize,
					   m_pPrimaryGroup,&iGroupSize))
  goto ErrorExit;
   // by now we should have a good SD in m_pSD...
  return TRUE;
  }
  else goto ErrorExit; 
ErrorExit:
 FreeDataStructures();
 return FALSE;
};

// derived classes...

CKernelSecObject::CKernelSecObject() : CSecureableObject(TRUE)
{
};
 
CKernelSecObject::~CKernelSecObject()
{
};
 
BOOL CKernelSecObject::SetObjectSecurity(HANDLE hObject)
{
 BOOL bErrorCode=TRUE;
 if (!SetKernelObjectSecurity(hObject,DACL_SECURITY_INFORMATION|SACL_SECURITY_INFORMATION,m_pSD))
 { 
  m_iSecErrorCode = GetLastError();
  bErrorCode = FALSE;
 };

 FreeDataStructures();

 return bErrorCode;
};

BOOL CKernelSecObject::GetObjectSecurity(HANDLE hObject)
{
 PSECURITY_DESCRIPTOR pSelfRelativeReturnSD=NULL;
 DWORD iSDSize=0;
 if (!GetKernelObjectSecurity(hObject,DACL_SECURITY_INFORMATION|SACL_SECURITY_INFORMATION,pSelfRelativeReturnSD,iSDSize,&iSDSize) &&
      GetLastError() == ERROR_INSUFFICIENT_BUFFER)
 {
  pSelfRelativeReturnSD = malloc(iSDSize);
  if (!pSelfRelativeReturnSD)
  {
   SetLastError(ERROR_NOT_ENOUGH_MEMORY);
   goto ErrorExit;
  };
  if (!GetKernelObjectSecurity(hObject,DACL_SECURITY_INFORMATION|SACL_SECURITY_INFORMATION,pSelfRelativeReturnSD,iSDSize,&iSDSize))
   goto ErrorExit;
  if (!BuildSD(pSelfRelativeReturnSD)) goto ErrorExit;
  free (pSelfRelativeReturnSD);
  return TRUE;
 };
ErrorExit:
 if (pSelfRelativeReturnSD) free (pSelfRelativeReturnSD);
 return FALSE;
};

CUserSecObject::CUserSecObject() : CSecureableObject(TRUE)
{
};
 
CUserSecObject::~CUserSecObject()
{
};

BOOL CUserSecObject::SetObjectSecurity(HANDLE hObject)
{ 
 SECURITY_INFORMATION si = DACL_SECURITY_INFORMATION|SACL_SECURITY_INFORMATION;
 BOOL bErrorCode = TRUE;
 if (!SetUserObjectSecurity(hObject,&si,m_pSD))
 { 
  m_iSecErrorCode = GetLastError();
  bErrorCode = FALSE;
 };
 FreeDataStructures();
 return bErrorCode;
};

BOOL CUserSecObject::GetObjectSecurity(HANDLE hObject)
{
 PSECURITY_DESCRIPTOR pSelfRelativeReturnSD=NULL;
 DWORD iSDSize=0;
 SECURITY_INFORMATION si=DACL_SECURITY_INFORMATION|SACL_SECURITY_INFORMATION;
 if (!GetUserObjectSecurity(hObject,&si,pSelfRelativeReturnSD,iSDSize,&iSDSize) &&
      GetLastError() == ERROR_INSUFFICIENT_BUFFER)
 {
  pSelfRelativeReturnSD = malloc(iSDSize);
  if (!pSelfRelativeReturnSD)
  {
   SetLastError(ERROR_NOT_ENOUGH_MEMORY);
   goto ErrorExit;
  };
  if (!GetUserObjectSecurity(hObject,&si,pSelfRelativeReturnSD,iSDSize,&iSDSize))
   goto ErrorExit;
  if (!BuildSD(pSelfRelativeReturnSD)) goto ErrorExit;
  free (pSelfRelativeReturnSD);
  return TRUE;
 };
ErrorExit:
 if (pSelfRelativeReturnSD) free (pSelfRelativeReturnSD);
 return FALSE;
};



CPrivateSecObject::CPrivateSecObject() : CSecureableObject(TRUE)   
{
 HANDLE hProcess;
 hProcess = GetCurrentProcess();
 if(!OpenProcessToken(hProcess,TOKEN_ALL_ACCESS,&m_hAccessToken))
  m_iSecErrorCode =GetLastError();  
 SetPrivilegeInAccessToken(TRUE);
 m_gmPrivateMapping.GenericRead = DBASE_READ;
 m_gmPrivateMapping.GenericWrite = DBASE_WRITE;
 m_gmPrivateMapping.GenericExecute = STANDARD_RIGHTS_EXECUTE;
 m_gmPrivateMapping.GenericAll = DBASE_READ|DBASE_WRITE;
 if (!CreatePrivateObjectSecurity(NULL,m_pSD,&m_ObjectSD,FALSE,m_hAccessToken,&m_gmPrivateMapping)) 
  m_iSecErrorCode = GetLastError();
 SetPrivilegeInAccessToken(FALSE);
 m_dwUniqueHandleId = (DWORD)this;

};
 
CPrivateSecObject::~CPrivateSecObject()
{
 CloseHandle(m_hAccessToken);
 DestroyPrivateObjectSecurity(&m_ObjectSD);
};

BOOL CPrivateSecObject::SetObjectSecurity()
{
 BOOL bErrorCode = TRUE;
 if (!SetPrivateObjectSecurity(DACL_SECURITY_INFORMATION|SACL_SECURITY_INFORMATION,
       m_pSD,&m_ObjectSD,&m_gmPrivateMapping,m_hAccessToken))
 { 
  m_iSecErrorCode = GetLastError();
  bErrorCode = FALSE;
 };
 FreeDataStructures();
 return bErrorCode;
};

BOOL CPrivateSecObject::GetObjectSecurity()
{
 PSECURITY_DESCRIPTOR pSelfRelativeReturnSD=NULL;
 DWORD iSDSize=0;
 if (!GetPrivateObjectSecurity(m_ObjectSD,DACL_SECURITY_INFORMATION|SACL_SECURITY_INFORMATION,pSelfRelativeReturnSD,iSDSize,&iSDSize) &&
      GetLastError() == ERROR_INSUFFICIENT_BUFFER)
 {
  pSelfRelativeReturnSD = malloc(iSDSize);
  if (!pSelfRelativeReturnSD)
  {
   SetLastError(ERROR_NOT_ENOUGH_MEMORY);
   goto ErrorExit;
  };
  if (!GetPrivateObjectSecurity(m_ObjectSD,DACL_SECURITY_INFORMATION|SACL_SECURITY_INFORMATION,pSelfRelativeReturnSD,iSDSize,&iSDSize))
   goto ErrorExit;
  if (!BuildSD(pSelfRelativeReturnSD)) goto ErrorExit;
  free (pSelfRelativeReturnSD);
  return TRUE;
 };
ErrorExit:
 if (pSelfRelativeReturnSD) free (pSelfRelativeReturnSD);
 return FALSE;
};

BOOL CPrivateSecObject::MatchAccessRequest(DWORD dwMask, HANDLE hThread)
{
 BOOL bReturn;
 DWORD dwStatus;
 BOOL bAuditGenerated;
 if(!AccessCheckAndAuditAlarm("DBServer",(LPVOID)m_dwUniqueHandleId,"Database Object","TestBase",
                              m_ObjectSD,dwMask,&m_gmPrivateMapping,TRUE,
							  &dwStatus,&bReturn,&bAuditGenerated))
{
  m_iSecErrorCode = GetLastError();
  return FALSE;
 };
 if (!ObjectCloseAuditAlarm("DBServer",(LPVOID)m_dwUniqueHandleId,bAuditGenerated))
 {
  m_iSecErrorCode = GetLastError();
  return FALSE;
 };
 m_iSecErrorCode = ERROR_SUCCESS;
 m_dwUniqueHandleId++;
 return bReturn;
};

DWORD CPrivateSecObject::MapRequestedRights (DWORD dwArg)
{
 MapGenericMask(&dwArg,&m_gmPrivateMapping);
 return dwArg;
};

