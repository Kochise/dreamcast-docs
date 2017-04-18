#include <stdafx.h>
#include <windows.h>
#include "examstff.h"


/****************************************************************************\
*  INCLUDES, DEFINES
\****************************************************************************/

#define Debugprintf(string) OutputDebugString(string)
#define Debugprintf1(string,v1) {char szBuf[255];sprintf(szBuf,string,v1);OutputDebugString(szBuf);};
#define Debugprintf2(string,v1,v2) {char szBuf[255];sprintf(szBuf,string,v1,v2);OutputDebugString(szBuf);};
#define Debugprintf3(string,v1,v2,v3) {char szBuf[255];sprintf(szBuf,string,v1,v2,v3);OutputDebugString(szBuf);};
#define Debugprintf4(string,v1,v2,v3,v4) {char szBuf[255];sprintf(szBuf,string,v1,v2,v3,v4);OutputDebugString(szBuf);};


#define PERR(api) Debugprintf4("\n%s: Error %d from %s on line %d",  \
    __FILE__, GetLastError(), api, __LINE__);
#define PMSG(msg) Debugprintf3("\n%s line %d: %s",  \
    __FILE__, __LINE__, msg);

/****************************************************************************\
* GLOBAL VARIABLES AND TYPEDEFS
\****************************************************************************/

PSID psidNullSid;
PSID psidWorldSid;
PSID psidLocalSid;
PSID psidCreatorOwnerSid;
PSID psidCreatorGroupSid;
PSID psidNtAuthoritySid;
PSID psidDialupSid;
PSID psidNetworkSid;
PSID psidBatchSid;
PSID psidInteractiveSid;
PSID psidLogonIdsSid; // But the X and Y values are bogus at first!!! (See below)
PSID psidServiceSid;
PSID psidLocalSystemSid;
PSID psidBuiltinDomainSid;


/****************************************************************************\
*
* FUNCTION: ExamineSD
*
\****************************************************************************/

BOOL ExamineSD    (PSECURITY_DESCRIPTOR psdSD)
//                   KINDS_OF_ACCESSMASKS_DECODED kamKindOfMask)
{

  PACL                        paclDACL;
  PACL                        paclSACL;
  BOOL                        bHasDACL        = FALSE;
  BOOL                        bHasSACL        = FALSE;
  BOOL                        bDaclDefaulted  = FALSE;
  BOOL                        bSaclDefaulted  = FALSE;
  BOOL                        bOwnerDefaulted = FALSE;
  BOOL                        bGroupDefaulted = FALSE;
  PSID                        psidOwner;
  PSID                        psidGroup;
  SECURITY_DESCRIPTOR_CONTROL sdcSDControl;
  DWORD                       dwSDRevision;
  DWORD                       dwSDLength;

  if (!IsValidSecurityDescriptor(psdSD))
  { PERR("IsValidSecurityDescriptor");
    return(FALSE);
  }

  dwSDLength = GetSecurityDescriptorLength(psdSD);

  if (!GetSecurityDescriptorDacl(psdSD,
                                 (LPBOOL)&bHasDACL,
                                 (PACL *)&paclDACL,
                                 (LPBOOL)&bDaclDefaulted))
  { PERR("GetSecurityDescriptorDacl");
    return(FALSE);
  }

  if (!GetSecurityDescriptorSacl(psdSD,
                                 (LPBOOL)&bHasSACL,
                                 (PACL *)&paclSACL,
                                 (LPBOOL)&bSaclDefaulted))
  { PERR("GetSecurityDescriptorSacl");
    return(FALSE);
  }

  if (!GetSecurityDescriptorOwner(psdSD,
                                  (PSID *)&psidOwner,
                                  (LPBOOL)&bOwnerDefaulted))
  { PERR("GetSecurityDescriptorOwner");
    return(FALSE);
  }

  if (!GetSecurityDescriptorGroup(psdSD,
                                  (PSID *)&psidGroup,
                                  (LPBOOL)&bGroupDefaulted))
  { PERR("GetSecurityDescriptorGroup");
    return(FALSE);
  }

  if (!GetSecurityDescriptorControl(psdSD,
                                    (PSECURITY_DESCRIPTOR_CONTROL)&sdcSDControl,
                                    (LPDWORD)&dwSDRevision))
  { PERR("GetSecurityDescriptorControl");
    return(FALSE);
  }

  Debugprintf2("\nSD is valid.  SD is %d bytes long.  SD revision is %d == ",dwSDLength,dwSDRevision);

  switch (dwSDRevision)
  {
    case      SECURITY_DESCRIPTOR_REVISION1 :
    { Debugprintf("SECURITY_DESCRIPTOR_REVISION1");
      break;
    }
    default :
    { Debugprintf("! SD Revision is an IMPOSSIBLE SD revision!!! Perhaps a new revision was added...");
      return(FALSE);
    }
  }

  if (SE_SELF_RELATIVE & sdcSDControl)
    Debugprintf("\nSD is in self-relative format (all SDs returned by the system are)");

  if (NULL == psidOwner)
  { Debugprintf("\nSD's Owner is NULL, so SE_OWNER_DEFAULTED is ignored");
  }
  else
  { Debugprintf("\nSD's Owner is Not NULL");
    if (bOwnerDefaulted )
    { Debugprintf("\nSD's Owner-Defaulted flag is TRUE");
    }
    else
    { Debugprintf("\nSD's Owner-Defaulted flag is FALSE");
    }
    if(!LookupSIDName(psidOwner,""))
    { PERR("LookupSIDName failed");
    }
  }

  /**************************************************************************\
  *
  * The other use for psidGroup is for Macintosh client support
  *
  \**************************************************************************/

  if (NULL == psidGroup)
  { Debugprintf("\nSD's Group is NULL, so SE_GROUP_DEFAULTED is ignored");
    Debugprintf("\nSD's Group being NULL is typical, GROUP in SD(s) is mainly for POSIX compliance");
  }
  else
  { if (bGroupDefaulted)
    { Debugprintf("\nSD's Group-Defaulted flag is TRUE");
    }
    else
    { Debugprintf("\nSD's Group-Defaulted flag is FALSE");
    }
    if(!LookupSIDName(psidGroup,""))
    { PERR("LookupSIDName failed");
    }
  }

  if   (SE_DACL_PRESENT & sdcSDControl)
  { Debugprintf("\nSD's DACL is Present");
    if (bDaclDefaulted)
    { Debugprintf("\nSD's DACL-Defaulted flag is TRUE");
    }
    else
    { Debugprintf("\nSD's DACL-Defaulted flag is FALSE");
    }

    if (NULL == paclDACL)
    { Debugprintf("\nSD has a NULL DACL explicitly specified      (allows all access to Everyone)");
      Debugprintf("\n    This does not apply to this SD, but for comparison,");
      Debugprintf("\n    a non-NULL DACL pointer to a 0-length ACL allows  no access to   anyone");
    }
    else if(!ExamineACL(paclDACL,""))//,kamKindOfMask))
    {  PERR("ExamineACL failed");
    }
  }
  else
  { Debugprintf("\nSD's DACL is Not Present, so SE_DACL_DEFAULTED is ignored");
    Debugprintf("\nSD has no DACL at all (allows all access to Everyone)");
  }

  if   (SE_SACL_PRESENT & sdcSDControl)
  { Debugprintf("\nSD's SACL is Present");
    if (bSaclDefaulted)
    { Debugprintf("\nSD's SACL-Defaulted flag is TRUE");
    }
    else
    { Debugprintf("\nSD's SACL-Defaulted flag is FALSE");
    }

    if (NULL == paclSACL)
    { Debugprintf("\nSD has a NULL SACL explicitly specified");
    }
    else if(!ExamineACL(paclSACL,""))//,kamKindOfMask))
    {  PERR("ExamineACL failed");
    }
  }
  else
  { Debugprintf("\nSD's SACL is Not Present, so SE_SACL_DEFAULTED is ignored");
    Debugprintf("\nSD has no SACL at all (or we did not request to see it)");
  }
 return TRUE;
}

/****************************************************************************\
*
* FUNCTION: ExamineACL
*
\****************************************************************************/

BOOL ExamineACL   (PACL paclACL,LPTSTR lpszOldIndent)
//                   KINDS_OF_ACCESSMASKS_DECODED kamKindOfMask)
{
  #define                          SZ_INDENT_BUF 80
  CHAR                ucIndentBuf[SZ_INDENT_BUF] = "";
  ACL_SIZE_INFORMATION                      asiAclSize;
  ACL_REVISION_INFORMATION                  ariAclRevision;
  DWORD                dwBufLength;
  DWORD                dwAcl_i;
  ACCESS_ALLOWED_ACE   *paaAllowedAce;

  strcpy(ucIndentBuf,lpszOldIndent);
  strcat(ucIndentBuf,"  ");

  if (!IsValidAcl(paclACL))
  { PERR("IsValidAcl");
    return(FALSE);
  }

  dwBufLength = sizeof(asiAclSize);

  if (!GetAclInformation(paclACL,
                         (LPVOID)&asiAclSize,
                         (DWORD)dwBufLength,
                         (ACL_INFORMATION_CLASS)AclSizeInformation))
  { PERR("GetAclInformation");
    return(FALSE);
  }

  dwBufLength = sizeof(ariAclRevision);

  if (!GetAclInformation(paclACL,
                         (LPVOID)&ariAclRevision,
                         (DWORD)dwBufLength,
                         (ACL_INFORMATION_CLASS)AclRevisionInformation))
  { PERR("GetAclInformation");
    return(FALSE);
  }

  Debugprintf4("\n%sACL has %d ACE(s), %d bytes used, %d bytes free",ucIndentBuf,
     asiAclSize.AceCount,
     asiAclSize.AclBytesInUse,
     asiAclSize.AclBytesFree);

  Debugprintf2("\n%sACL revision is %d == ",ucIndentBuf,ariAclRevision.AclRevision);

  switch (ariAclRevision.AclRevision)
  {
    case      ACL_REVISION1 :
    { Debugprintf("ACL_REVISION1");
      break;
    }
    case      ACL_REVISION2 :
    { Debugprintf("ACL_REVISION2");
      break;
    }
    default :
    { Debugprintf1("\n%sACL Revision is an IMPOSSIBLE ACL revision!!! Perhaps a new revision was added...",ucIndentBuf);
      return(FALSE);
    }
  }

  for (dwAcl_i = 0; dwAcl_i < asiAclSize.AceCount;  dwAcl_i++)
  {
    if (!GetAce(paclACL,
                dwAcl_i,
                (LPVOID *)&paaAllowedAce))
    { PERR("GetAce");
      return(FALSE);
    }

    Debugprintf3("\n%sACE %d size %d",ucIndentBuf,dwAcl_i,paaAllowedAce->Header.AceSize);

    { DWORD dwAceFlags = paaAllowedAce->Header.AceFlags;

      Debugprintf3("\n%sACE %d flags 0x%.2x",ucIndentBuf,dwAcl_i,dwAceFlags);

      if (dwAceFlags)
      {
        DWORD dwExtraBits;
        CHAR ucIndentBitsBuf[SZ_INDENT_BUF] = "";

        strcpy(ucIndentBitsBuf,ucIndentBuf);
        strcat(ucIndentBitsBuf,"            ");

        if ((dwAceFlags  & OBJECT_INHERIT_ACE        ) == OBJECT_INHERIT_ACE        )
        { Debugprintf1("\n%s0x01 OBJECT_INHERIT_ACE        ",ucIndentBitsBuf);
        }
        if ((dwAceFlags  & CONTAINER_INHERIT_ACE     ) == CONTAINER_INHERIT_ACE     )
        { Debugprintf1("\n%s0x02 CONTAINER_INHERIT_ACE     ",ucIndentBitsBuf);
        }
        if ((dwAceFlags  & NO_PROPAGATE_INHERIT_ACE  ) == NO_PROPAGATE_INHERIT_ACE  )
        { Debugprintf1("\n%s0x04 NO_PROPAGATE_INHERIT_ACE  ",ucIndentBitsBuf);
        }
        if ((dwAceFlags  & INHERIT_ONLY_ACE          ) == INHERIT_ONLY_ACE          )
        { Debugprintf1("\n%s0x08 INHERIT_ONLY_ACE          ",ucIndentBitsBuf);
        }
        if ((dwAceFlags  & VALID_INHERIT_FLAGS       ) == VALID_INHERIT_FLAGS       )
        { Debugprintf1("\n%s0x0F VALID_INHERIT_FLAGS       ",ucIndentBitsBuf);
        }
        if ((dwAceFlags  & SUCCESSFUL_ACCESS_ACE_FLAG) == SUCCESSFUL_ACCESS_ACE_FLAG)
        { Debugprintf1("\n%s0x40 SUCCESSFUL_ACCESS_ACE_FLAG",ucIndentBitsBuf);
        }
        if ((dwAceFlags  & FAILED_ACCESS_ACE_FLAG    ) == FAILED_ACCESS_ACE_FLAG    )
        { Debugprintf1("\n%s0x80 FAILED_ACCESS_ACE_FLAG    ",ucIndentBitsBuf);
        }

        dwExtraBits = dwAceFlags & ( ~( OBJECT_INHERIT_ACE
                                      | CONTAINER_INHERIT_ACE
                                      | NO_PROPAGATE_INHERIT_ACE
                                      | INHERIT_ONLY_ACE
                                      | VALID_INHERIT_FLAGS
                                      | SUCCESSFUL_ACCESS_ACE_FLAG
                                      | FAILED_ACCESS_ACE_FLAG) );
        if (dwExtraBits)
        { Debugprintf2("\n%sExtra AceFlag bits     == 0x%.8x <-This is a problem, should be all 0s",ucIndentBuf,dwExtraBits);
        }
      }
    }

    switch (paaAllowedAce->Header.AceType)
    {
      case                       ACCESS_ALLOWED_ACE_TYPE :
      { Debugprintf2("\n%sACE %d is an ACCESS_ALLOWED_ACE_TYPE",ucIndentBuf,dwAcl_i);
        break;
      }
      case                       ACCESS_DENIED_ACE_TYPE :
      { Debugprintf2("\n%sACE %d is an ACCESS_DENIED_ACE_TYPE",ucIndentBuf,dwAcl_i);
        break;
      }
      case                       SYSTEM_AUDIT_ACE_TYPE :
      { Debugprintf2("\n%sACE %d is a  SYSTEM_AUDIT_ACE_TYPE",ucIndentBuf,dwAcl_i);
        break;
      }
      case                       SYSTEM_ALARM_ACE_TYPE :
      { Debugprintf2("\n%sACE %d is a  SYSTEM_ALARM_ACE_TYPE",ucIndentBuf,dwAcl_i);
        break;
      }
      default :
      { Debugprintf2("\n%sACE %d is an IMPOSSIBLE ACE_TYPE!!! Run debugger, examine value!",ucIndentBuf,dwAcl_i);
        return(FALSE);
      }
    }

    Debugprintf3("\n%sACE %d mask               == 0x%.8x",ucIndentBuf,dwAcl_i,paaAllowedAce->Mask);

    ExamineMask(paaAllowedAce->Mask,ucIndentBuf);//,kamKindOfMask);

    if(!LookupSIDName((PSID)&(paaAllowedAce->SidStart),ucIndentBuf))
    { PERR("LookupSIDName failed");
    }
  }
 return TRUE;
}

/****************************************************************************\
*
* FUNCTION: ExamineMask
*
\****************************************************************************/

VOID ExamineMask  (ACCESS_MASK amMask,        LPTSTR lpszOldIndent)
//                   KINDS_OF_ACCESSMASKS_DECODED kamKindOfMask)
{
  #define STANDARD_RIGHTS_ALL_THE_BITS 0x00FF0000L
  #define GENERIC_RIGHTS_ALL_THE_BITS  0xF0000000L
  CHAR ucIndentBuf[SZ_INDENT_BUF]     = "";
  CHAR ucIndentBitsBuf[SZ_INDENT_BUF] = "";
  DWORD dwGenericBits;
  DWORD dwStandardBits;
  DWORD dwSpecificBits;
  DWORD dwAccessSystemSecurityBit;
  DWORD dwExtraBits;

  strcpy(ucIndentBuf,    lpszOldIndent);
  strcat(ucIndentBuf,    "  ");
  strcpy(ucIndentBitsBuf,lpszOldIndent);
  strcat(ucIndentBitsBuf,"                            ");

  dwStandardBits            = (amMask & STANDARD_RIGHTS_ALL_THE_BITS);
  dwSpecificBits            = (amMask & SPECIFIC_RIGHTS_ALL         );
  dwAccessSystemSecurityBit = (amMask & ACCESS_SYSTEM_SECURITY      );
  dwGenericBits             = (amMask & GENERIC_RIGHTS_ALL_THE_BITS );

  /**************************************************************************\
  *
  * Print then decode the standard rights bits
  *
  \**************************************************************************/

  Debugprintf2("\n%sStandard Rights        == 0x%.8x",ucIndentBuf,dwStandardBits);

  if (dwStandardBits)
  {
    if ((dwStandardBits    & DELETE                  ) == DELETE                  )
    { Debugprintf1("\n%s0x00010000 DELETE                  ",ucIndentBitsBuf);
    }
    if ((dwStandardBits    & READ_CONTROL            ) == READ_CONTROL            )
    { Debugprintf1("\n%s0x00020000 READ_CONTROL            ",ucIndentBitsBuf);
    }
    if ((dwStandardBits    & STANDARD_RIGHTS_READ    ) == STANDARD_RIGHTS_READ    )
    { Debugprintf1("\n%s0x00020000 STANDARD_RIGHTS_READ    ",ucIndentBitsBuf);
    }
    if ((dwStandardBits    & STANDARD_RIGHTS_WRITE   ) == STANDARD_RIGHTS_WRITE   )
    { Debugprintf1("\n%s0x00020000 STANDARD_RIGHTS_WRITE   ",ucIndentBitsBuf);
    }
    if ((dwStandardBits    & STANDARD_RIGHTS_EXECUTE ) == STANDARD_RIGHTS_EXECUTE )
    { Debugprintf1("\n%s0x00020000 STANDARD_RIGHTS_EXECUTE ",ucIndentBitsBuf);
    }
    if ((dwStandardBits    & WRITE_DAC               ) == WRITE_DAC               )
    { Debugprintf1("\n%s0x00040000 WRITE_DAC               ",ucIndentBitsBuf);
    }
    if ((dwStandardBits    & WRITE_OWNER             ) == WRITE_OWNER             )
    { Debugprintf1("\n%s0x00080000 WRITE_OWNER             ",ucIndentBitsBuf);
    }
    if ((dwStandardBits    & SYNCHRONIZE             ) == SYNCHRONIZE             )
    { Debugprintf1("\n%s0x00100000 SYNCHRONIZE             ",ucIndentBitsBuf);
    }
    if ((dwStandardBits    & STANDARD_RIGHTS_REQUIRED) == STANDARD_RIGHTS_REQUIRED)
    { Debugprintf1("\n%s0x000F0000 STANDARD_RIGHTS_REQUIRED",ucIndentBitsBuf);
    }
    if ((dwStandardBits    & STANDARD_RIGHTS_ALL     ) == STANDARD_RIGHTS_ALL     )
    { Debugprintf1("\n%s0x001F0000 STANDARD_RIGHTS_ALL     ",ucIndentBitsBuf);
    }

    dwExtraBits = dwStandardBits & ( ~( DELETE
                                      | READ_CONTROL
                                      | STANDARD_RIGHTS_READ
                                      | STANDARD_RIGHTS_WRITE
                                      | STANDARD_RIGHTS_EXECUTE
                                      | WRITE_DAC
                                      | WRITE_OWNER
                                      | SYNCHRONIZE
                                      | STANDARD_RIGHTS_REQUIRED
                                      | STANDARD_RIGHTS_ALL) );
    if (dwExtraBits)
    { Debugprintf2("\n%sExtra standard bits    == 0x%.8x <-This is a problem, should be all 0s",ucIndentBuf,dwExtraBits);
    }
  }
  
  Debugprintf2("\n%sSpecific Rights        == 0x%.8x",ucIndentBuf,dwSpecificBits);
  
  /**************************************************************************\
  *
  * Print then decode the ACCESS_SYSTEM_SECURITY bit
  *
  \**************************************************************************/

  Debugprintf2("\n%sAccess System Security == 0x%.8x",ucIndentBuf,dwAccessSystemSecurityBit);

  /**************************************************************************\
  *
  * Print then decode the generic rights bits, which will rarely be on
  *
  * Generic bits are nearly always mapped by Windows NT before it tries to do
  *   anything with them.  You can ignore the fact that generic bits are
  *   special in any way, although it helps to keep track of what the mappings
  *   are so that you don't have any surprises
  *
  * The only time the generic bits are not mapped immediately is if they are
  *   placed in an inheritable ACE in an ACL, or in an ACL that will be
  *   assigned by default (such as the default DACL in an access token).  In
  *   that case they're mapped when the child object is created (or when the
  *   default DACL is used at object creation time)
  *
  \**************************************************************************/

  Debugprintf2("\n%sGeneric  Rights        == 0x%.8x",ucIndentBuf,dwGenericBits);

  if (dwGenericBits)
  {
    if ((dwGenericBits     & GENERIC_READ   ) == GENERIC_READ   )
    { Debugprintf1("\n%s0x80000000 GENERIC_READ   ",ucIndentBitsBuf);
    }
    if ((dwGenericBits     & GENERIC_WRITE  ) == GENERIC_WRITE  )
    { Debugprintf1("\n%s0x40000000 GENERIC_WRITE  ",ucIndentBitsBuf);
    }
    if ((dwGenericBits     & GENERIC_EXECUTE) == GENERIC_EXECUTE)
    { Debugprintf1("\n%s0x20000000 GENERIC_EXECUTE",ucIndentBitsBuf);
    }
    if ((dwGenericBits     & GENERIC_ALL    ) == GENERIC_ALL    )
    { Debugprintf1("\n%s0x10000000 GENERIC_ALL    ",ucIndentBitsBuf);
    }

    dwExtraBits = dwGenericBits & ( ~( GENERIC_READ
                                     | GENERIC_WRITE
                                     | GENERIC_EXECUTE
                                     | GENERIC_ALL) );
    if (dwExtraBits)
    { Debugprintf2("\n%sExtra generic bits     == 0x%.8x <-This is a problem, should be all 0s",ucIndentBuf,dwExtraBits);
    }
  }
}

/****************************************************************************\
*
* FUNCTION: LookupSIDName
*
\****************************************************************************/

BOOL LookupSIDName(PSID psidSID, LPTSTR lpszOldIndent)
{
  CHAR        ucIndentBuf    [SZ_INDENT_BUF]    = "";
  #define                      SZ_ACCT_NAME_BUF  60
  CHAR        ucNameBuf      [SZ_ACCT_NAME_BUF] = "";
  DWORD        dwNameLength  = SZ_ACCT_NAME_BUF;
  #define                      SZ_DMN_NAME_BUF   60
  CHAR        ucDomainNmBuf  [SZ_DMN_NAME_BUF]  = "";
  DWORD        dwDNameLength = SZ_DMN_NAME_BUF;
  #define                      SZ_SID_STRING_BUF 150
  CHAR        ucSIDStringBuf [SZ_SID_STRING_BUF] = "";
  SID_NAME_USE peAcctNameUse = SidTypeInvalid;
  DWORD        dwLookupStatus;
  BOOL         bGotBadLookupThatIsNotLocalLogonSID;

  strcpy(ucIndentBuf,lpszOldIndent);
  strcat(ucIndentBuf,"  ");

  if (!IsValidSid(psidSID))
  { PERR("IsValidSid");
    return(FALSE);
  }

  if (!SIDStringName(psidSID,ucSIDStringBuf))
  { PERR("SIDStringName");
    return(FALSE);
  }

  if (!LookupAccountSid(
         (LPTSTR)"",         // Look on local machine
         psidSID,
         (LPTSTR)&ucNameBuf,
         (LPDWORD)&dwNameLength,
         (LPTSTR)&ucDomainNmBuf,
         (LPDWORD)&dwDNameLength,
         (PSID_NAME_USE)&peAcctNameUse))
  {
    dwLookupStatus = GetLastError();

    /************************************************************************\
    *
    * Got a bad Lookup, so check is SID the Local Logon SID?
    *
    * The problem is that LookupAccountSid api will find all the well-known
    *   SIDs except the Local Logon SID.  The last two sub-authorities are
    *   always different, so to check to see if the SID we're looking at is
    *   the Local Logon SID, we take the psidLogonIdsSid variable we built at
    *   initialization time, and blast into it's last two sub-authorities the
    *   last two sub-authorities that we have.  Then compare for EqualSid
    *
    \************************************************************************/

    // Must have same number of sub authorities

    bGotBadLookupThatIsNotLocalLogonSID = FALSE;  // Assume the best :)

    if ( ( *(GetSidSubAuthorityCount(psidLogonIdsSid))) !=
         ( *(GetSidSubAuthorityCount(psidSID        )))    )
    { // Not same number of sub-authorities, so can't be a match
      bGotBadLookupThatIsNotLocalLogonSID = TRUE;
    }
    else
    {
      // Force the last two sub-authorities to match
      *(GetSidSubAuthority( psidLogonIdsSid, 1 )) =
      *(GetSidSubAuthority( psidSID        , 1 ));
      *(GetSidSubAuthority( psidLogonIdsSid, 2 )) =
      *(GetSidSubAuthority( psidSID        , 2 ));

      /**********************************************************************\
      *
      * EqualPrefixSid could be used instead if we want to blast in all but
      *   the last sub-authority.  For demonstration purposes, as long as we
      *   did one of the two previous assignment statements, we may as well to
      *   the other and use EqualSID
      *
      \**********************************************************************/

      if (EqualSid(psidSID,psidLogonIdsSid))
      { Debugprintf2("\n%sSID is the Local Logon SID   %s",ucIndentBuf,ucSIDStringBuf);
      }
      else
      { bGotBadLookupThatIsNotLocalLogonSID = TRUE;
      }
    }
    if (bGotBadLookupThatIsNotLocalLogonSID)
    {
      /**********************************************************************\
      *
      * ERROR_NONE_MAPPED means account unknown.  RegEdt32.exe will show
      *   1332-error-type accounts as Account Unknown, so we will also
      *
      \**********************************************************************/

      if (ERROR_NONE_MAPPED == dwLookupStatus)
      { Debugprintf4("\n%sSID domain == %s, Name == %s    (Account Unknown)  %s",ucIndentBuf,ucDomainNmBuf,ucNameBuf,ucSIDStringBuf);
      }
      else
      { SetLastError(dwLookupStatus);
        PERR("LookupAccountSid");
        return(FALSE);
      }
    }
  }
  else
  { // Got good Lookup, so SID Is NOT the Local Logon SID
    Debugprintf4("\n%sSID domain == %s, Name == %s   %s",ucIndentBuf,ucDomainNmBuf,ucNameBuf,ucSIDStringBuf);

    /************************************************************************\
    *
    * For demonstration purposes see which well-known SID it might be
    * For demonstration purposes do a silly search demonstrating
    *   no two well-known SIDs are equal
    *
    \************************************************************************/

    if (EqualSid(psidSID,psidNullSid))
    { Debugprintf1("\n%sSID is the Null SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidWorldSid))
    { Debugprintf1("\n%sSID is the World SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidLocalSid))
    { Debugprintf1("\n%sSID is the Local SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidCreatorOwnerSid))
    { Debugprintf1("\n%sSID is the CreatorOwner SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidCreatorGroupSid))
    { Debugprintf1("\n%sSID is the CreatorGroup SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidNtAuthoritySid))
    { Debugprintf1("\n%sSID is the NtAuthority SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidDialupSid))
    { Debugprintf1("\n%sSID is the DialUp SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidNetworkSid))
    { Debugprintf1("\n%sSID is the Network SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidBatchSid))
    { Debugprintf1("\n%sSID is the Batch SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidInteractiveSid))
    { Debugprintf1("\n%sSID is the Interactive SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidServiceSid))
    { Debugprintf1("\n%sSID is the Service SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidLocalSystemSid))
    { Debugprintf1("\n%sSID is the LocalSystem SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidBuiltinDomainSid))
    { Debugprintf1("\n%sSID is the Builtin Domain SID",ucIndentBuf);
    }
  }

  switch (peAcctNameUse)
  { case                      SidTypeUser           :
      Debugprintf1("\n%sSID type is SidTypeUser"          ,ucIndentBuf);
      break;
    case                      SidTypeGroup          :
      Debugprintf1("\n%sSID type is SidTypeGroup"         ,ucIndentBuf);
      break;
    case                      SidTypeDomain         :
      Debugprintf1("\n%sSID type is SidTypeDomain"        ,ucIndentBuf);
      break;
    case                      SidTypeAlias          :
      Debugprintf1("\n%sSID type is SidTypeAlias"         ,ucIndentBuf);
      break;
    case                      SidTypeWellKnownGroup :
      Debugprintf1("\n%sSID type is SidTypeWellKnownGroup",ucIndentBuf);
      break;
    case                      SidTypeDeletedAccount :
      Debugprintf1("\n%sSID type is SidTypeDeletedAccount",ucIndentBuf);
      break;
    case                      SidTypeInvalid        :
      Debugprintf1("\n%sSID type is SidTypeInvalid"       ,ucIndentBuf);
      break;
    case                      SidTypeUnknown        :
      Debugprintf1("\n%sSID type is SidTypeUnknown"       ,ucIndentBuf);
      break;
    default                   :
      Debugprintf1("\n%sSID type is IMPOSSIBLE!!!!  Run debugger, see value!",ucIndentBuf);
      break;
  }
 return TRUE;
}

/****************************************************************************\
*
* FUNCTION: SIDStringName
*
\****************************************************************************/

BOOL SIDStringName(PSID psidSID, LPTSTR lpszSIDStringName)
{
  /**************************************************************************\
  *
  * Unfortunately there is no api to return the SID Revision, and the number
  *   of bytes in the Identifier Authority must be expressed as a define
  *   (since the == operator won't operate on structures so mempcy has to be
  *   used for the identifier authority compares)
  *
  \**************************************************************************/

  DWORD dwNumSubAuthorities;
  DWORD dwLen;
  DWORD dwSubAuthorityI;
  #define BytesInIdentifierAuthority  6
  SID_IDENTIFIER_AUTHORITY siaSidAuthority;
  SID_IDENTIFIER_AUTHORITY siaNullSidAuthority    = SECURITY_NULL_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY siaWorldSidAuthority   = SECURITY_WORLD_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY siaLocalSidAuthority   = SECURITY_LOCAL_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY siaCreatorSidAuthority = SECURITY_CREATOR_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY siaNtAuthority         = SECURITY_NT_AUTHORITY;

  dwLen = sprintf(lpszSIDStringName,"S-%d-",SID_REVISION);

  if (SID_REVISION != ((PISID)psidSID)->Revision)
  { dwLen += sprintf(lpszSIDStringName+dwLen,"bad_revision==%d",((PISID)psidSID)->Revision);
  }

  siaSidAuthority = *(GetSidIdentifierAuthority(psidSID));

  if      (0==memcmp(&siaSidAuthority,&siaNullSidAuthority   ,BytesInIdentifierAuthority))
  { dwLen += sprintf(lpszSIDStringName+dwLen,"0");
  }
  else if (0==memcmp(&siaSidAuthority,&siaWorldSidAuthority  ,BytesInIdentifierAuthority))
  { dwLen += sprintf(lpszSIDStringName+dwLen,"1");
  }
  else if (0==memcmp(&siaSidAuthority,&siaLocalSidAuthority  ,BytesInIdentifierAuthority))
  { dwLen += sprintf(lpszSIDStringName+dwLen,"2");
  }
  else if (0==memcmp(&siaSidAuthority,&siaCreatorSidAuthority,BytesInIdentifierAuthority))
  { dwLen += sprintf(lpszSIDStringName+dwLen,"3");
  }
  else if (0==memcmp(&siaSidAuthority,&siaNtAuthority        ,BytesInIdentifierAuthority))
  { dwLen += sprintf(lpszSIDStringName+dwLen,"5");
  }
  else
  { dwLen += sprintf(lpszSIDStringName+dwLen,"UnknownAuthority!");
  }

  dwNumSubAuthorities = (DWORD)( *(GetSidSubAuthorityCount(psidSID)) );

  for (dwSubAuthorityI=0; dwSubAuthorityI<dwNumSubAuthorities; dwSubAuthorityI++)
  { dwLen += sprintf(lpszSIDStringName+dwLen,"-%d",*(GetSidSubAuthority(psidSID,dwSubAuthorityI)));
  }

  return(TRUE);
}

/****************************************************************************\
*
* FUNCTION: ExamineAccessToken
*
\****************************************************************************/

VOID ExamineAccessToken(HANDLE hAccessToken)
{ TOKEN_INFORMATION_CLASS ticInfoClass;
  #define                               SZ_TOK_INFO_BUF  2000
  CHAR                   ucTokInfoBuf [SZ_TOK_INFO_BUF] = "";
  DWORD                   dwTokInfoBufSz;
  PTOKEN_USER             ptuTokenUser         = (PTOKEN_USER         )&ucTokInfoBuf;
  PTOKEN_GROUPS           ptgTokenGroups       = (PTOKEN_GROUPS       )&ucTokInfoBuf;
  PTOKEN_PRIVILEGES       ptpTokenPrivileges   = (PTOKEN_PRIVILEGES   )&ucTokInfoBuf;
  PTOKEN_OWNER            ptoTokenOwner        = (PTOKEN_OWNER        )&ucTokInfoBuf;
  PTOKEN_PRIMARY_GROUP    ptgTokenPrimaryGroup = (PTOKEN_PRIMARY_GROUP)&ucTokInfoBuf;
  PTOKEN_DEFAULT_DACL     ptdTokenDefaultDacl  = (PTOKEN_DEFAULT_DACL )&ucTokInfoBuf;
  PTOKEN_SOURCE           ptsTokenSource       = (PTOKEN_SOURCE       )&ucTokInfoBuf;
  PTOKEN_TYPE             pttTokenType         = (PTOKEN_TYPE         )&ucTokInfoBuf;
  PSECURITY_IMPERSONATION_LEVEL psilSecurityImpersonationLevel = (PSECURITY_IMPERSONATION_LEVEL)&ucTokInfoBuf;
  PTOKEN_STATISTICS       ptsTokenStatistics   = (PTOKEN_STATISTICS   )&ucTokInfoBuf;
  DWORD                   dwGroupI;
  DWORD                   dwPrivilegeI;
  #define                               SZ_PRIV_INFO_BUF  250
  CHAR                   ucPrivInfoBuf[SZ_PRIV_INFO_BUF] = "";
  DWORD                   dwPrivInfoBufSz;
  DWORD                   dwExtraBits;
  CHAR                   ucIndentBitsBuf[SZ_INDENT_BUF]  = "";

  strcpy(ucIndentBitsBuf,"");
  strcat(ucIndentBitsBuf,"                                  ");


  if    (TRUE)//!I_DO_NOT_WANT_THIS_CODE_TO_CLUTTER_THIS_PROGRAM_S_OUTPUT)
  {
    ticInfoClass   = TokenUser;
    dwTokInfoBufSz = SZ_TOK_INFO_BUF;

    if (!GetTokenInformation(hAccessToken,
                             ticInfoClass,
                             ucTokInfoBuf,
                             (DWORD)SZ_TOK_INFO_BUF,
                             &dwTokInfoBufSz))
    { PERR("GetTokenInformation");
      return;
    }

    Debugprintf("\nToken's User SID");
    Debugprintf("\n    (this is a SID that is used to compare to SIDs in DACL(s) and SACL(s)");

    if(!LookupSIDName( (*ptuTokenUser).User.Sid,""))
    { PERR("LookupSIDName failed");
    }

    Debugprintf1("\nToken's User SID Attributes == 0x%.8x",(*ptuTokenUser).User.Attributes);
    Debugprintf("\n    These should always be 0 - see \\mstools\\h\\winnt.h right after");
    Debugprintf("\n      the defines such as SE_GROUP_LOGON_ID - there are no user");
    Debugprintf("\n      attributes yet defined");



    ticInfoClass   = TokenGroups;
    dwTokInfoBufSz = SZ_TOK_INFO_BUF;

    if (!GetTokenInformation(hAccessToken,
                             ticInfoClass,
                             ucTokInfoBuf,
                             (DWORD)SZ_TOK_INFO_BUF,
                             &dwTokInfoBufSz))
    { PERR("GetTokenInformation");
      return;
    }

    Debugprintf1("\nToken groups (%d)",(*ptgTokenGroups).GroupCount);
    Debugprintf("\n    (these SID(s) also are used to compare to SIDs in DACL(s) and SACL(s)");

    for (dwGroupI=0; dwGroupI<(*ptgTokenGroups).GroupCount; dwGroupI++)
    {
      DWORD dwAttributeBits = (*ptgTokenGroups).Groups[dwGroupI].Attributes;
      Debugprintf1("\n  Token group (%d)",dwGroupI);

      if(!LookupSIDName( (*ptgTokenGroups).Groups[dwGroupI].Sid,"  "))
      { PERR("LookupSIDName failed");
      }
      Debugprintf2("\n  Token's group (%d) attributes == 0x%.8x",dwGroupI,dwAttributeBits);

      if (dwAttributeBits)
      {
        if ((dwAttributeBits   & SE_GROUP_MANDATORY         ) == SE_GROUP_MANDATORY         )
        { Debugprintf1("\n%s0x00000001 SE_GROUP_MANDATORY         ",ucIndentBitsBuf);
        }
        if ((dwAttributeBits   & SE_GROUP_ENABLED_BY_DEFAULT) == SE_GROUP_ENABLED_BY_DEFAULT)
        { Debugprintf1("\n%s0x00000002 SE_GROUP_ENABLED_BY_DEFAULT",ucIndentBitsBuf);
        }
        if ((dwAttributeBits   & SE_GROUP_ENABLED           ) == SE_GROUP_ENABLED           )
        { Debugprintf1("\n%s0x00000004 SE_GROUP_ENABLED           ",ucIndentBitsBuf);
        }
        if ((dwAttributeBits   & SE_GROUP_OWNER             ) == SE_GROUP_OWNER             )
        { Debugprintf1("\n%s0x00000008 SE_GROUP_OWNER             ",ucIndentBitsBuf);
        }
        if ((dwAttributeBits   & SE_GROUP_LOGON_ID          ) == SE_GROUP_LOGON_ID          )
        { Debugprintf1("\n%s0xC0000000 SE_GROUP_LOGON_ID          ",ucIndentBitsBuf);
        }

        dwExtraBits = dwAttributeBits & ( ~( SE_GROUP_MANDATORY
                                           | SE_GROUP_ENABLED_BY_DEFAULT
                                           | SE_GROUP_ENABLED
                                           | SE_GROUP_OWNER
                                           | SE_GROUP_LOGON_ID) );
        if (0 != dwExtraBits)
        { Debugprintf1("\n          Extra attribute bits == 0x%.8x <-This is a problem, should be all 0s",dwExtraBits);
        }
      }
    }



    ticInfoClass   = TokenPrivileges;
    dwTokInfoBufSz = SZ_TOK_INFO_BUF;

    if (!GetTokenInformation(hAccessToken,
                             ticInfoClass,
                             ucTokInfoBuf,
                             (DWORD)SZ_TOK_INFO_BUF,
                             &dwTokInfoBufSz))
    { PERR("GetTokenInformation");
      return;
    }

    Debugprintf1("\nToken privileges (%d)",(*ptpTokenPrivileges).PrivilegeCount);
    Debugprintf("\n  NOTE: Most token privileges are not enabled by default.");
    Debugprintf("\n    For example the privilege to reboot or logoff is not.");
    Debugprintf("\n    0x00000000 for attributes implies the privilege is not enabled.");
    Debugprintf("\n    Use care when enabling privileges.  Enable only those needed,");
    Debugprintf("\n      and leave them enabled only for as long as they are needed.");

    for (dwPrivilegeI=0; dwPrivilegeI<(*ptpTokenPrivileges).PrivilegeCount; dwPrivilegeI++)
    {
      LUID  luidTokenLuid   = (*ptpTokenPrivileges).Privileges[dwPrivilegeI].Luid;
      DWORD dwAttributeBits = (*ptpTokenPrivileges).Privileges[dwPrivilegeI].Attributes;

      dwPrivInfoBufSz = SZ_PRIV_INFO_BUF;

      if (!LookupPrivilegeName(NULL,
                               (PLUID)&luidTokenLuid,
                               (LPTSTR)ucPrivInfoBuf,
                               (LPDWORD)&dwPrivInfoBufSz))
      { PERR("LookUpPrivilegeName");
        return;
      }

      Debugprintf2("\n  Token's privilege (%.2d) name       == %s",dwPrivilegeI,ucPrivInfoBuf);

      Debugprintf2("\n  Token's privilege (%.2d) attributes == 0x%.8x",dwPrivilegeI,dwAttributeBits);

      if (dwAttributeBits)
      {
        if ((dwAttributeBits   & SE_PRIVILEGE_ENABLED_BY_DEFAULT) == SE_PRIVILEGE_ENABLED_BY_DEFAULT)
        { Debugprintf1("\n%s     0x00000001 SE_PRIVILEGE_ENABLED_BY_DEFAULT",ucIndentBitsBuf);
        }
        if ((dwAttributeBits   & SE_PRIVILEGE_ENABLED           ) == SE_PRIVILEGE_ENABLED           )
        { Debugprintf1("\n%s     0x00000002 SE_PRIVILEGE_ENABLED           ",ucIndentBitsBuf);
        }
        if ((dwAttributeBits   & SE_PRIVILEGE_USED_FOR_ACCESS   ) == SE_PRIVILEGE_USED_FOR_ACCESS   )
        { Debugprintf1("\n%s     0x80000000 SE_PRIVILEGE_USED_FOR_ACCESS   ",ucIndentBitsBuf);
        }

        dwExtraBits = dwAttributeBits & ( ~( SE_PRIVILEGE_ENABLED_BY_DEFAULT
                                           | SE_PRIVILEGE_ENABLED
                                           | SE_PRIVILEGE_USED_FOR_ACCESS ) );
        if (0 != dwExtraBits)
        { Debugprintf1("\n               Extra attribute bits == 0x%.8x <-This is a problem, should be all 0s",dwExtraBits);
        }
      }
    }



    ticInfoClass   = TokenOwner;
    dwTokInfoBufSz = SZ_TOK_INFO_BUF;

    if (!GetTokenInformation(hAccessToken,
                             ticInfoClass,
                             ucTokInfoBuf,
                             (DWORD)SZ_TOK_INFO_BUF,
                             &dwTokInfoBufSz))
    { PERR("GetTokenInformation");
      return;
    }

    Debugprintf("\nToken's default-owner-SID for created objects");
    Debugprintf("\n    (this is NOT a SID that is used to compare to SIDs in DACL(s) and SACL(s)");

    if(!LookupSIDName((*ptoTokenOwner).Owner,""))
    { PERR("LookupSIDName failed");
    }



    ticInfoClass   = TokenPrimaryGroup;
    dwTokInfoBufSz = SZ_TOK_INFO_BUF;

    if (!GetTokenInformation(hAccessToken,
                             ticInfoClass,
                             ucTokInfoBuf,
                             (DWORD)SZ_TOK_INFO_BUF,
                             &dwTokInfoBufSz))
    { PERR("GetTokenInformation");
      return;
    }

    Debugprintf("\nToken's Primary Group SID");
    Debugprintf("\n    (Current uses are Posix and Macintosh client support)");

    if(!LookupSIDName((*ptgTokenPrimaryGroup).PrimaryGroup,""))
    { PERR("LookupSIDName failed");
    }



    ticInfoClass   = TokenDefaultDacl;
    dwTokInfoBufSz = SZ_TOK_INFO_BUF;

    if (!GetTokenInformation(hAccessToken,
                             ticInfoClass,
                             ucTokInfoBuf,
                             (DWORD)SZ_TOK_INFO_BUF,
                             &dwTokInfoBufSz))
    { PERR("GetTokenInformation");
      return;
    }

    if (NULL         == (*ptdTokenDefaultDacl).DefaultDacl)
    { Debugprintf("\nToken has a NULL Default DACL explicitly specified (allows all access to");
      Debugprintf("\n    Everyone, only on objects that are created where the object's Dacl is");
      Debugprintf("\n    assigned by default from this default Dacl in this access token)");
    }
    else
    { Debugprintf("\nToken's default-DACL for created objects");
      if(!ExamineACL((*ptdTokenDefaultDacl).DefaultDacl,""))
      { PERR("ExamineACL failed");
      }
    }



    ticInfoClass   = TokenSource;
    dwTokInfoBufSz = SZ_TOK_INFO_BUF;

    if (!GetTokenInformation(hAccessToken,
                             ticInfoClass,
                             ucTokInfoBuf,
                             (DWORD)SZ_TOK_INFO_BUF,
                             &dwTokInfoBufSz))
    { PERR("GetTokenInformation");
      return;
    }

    Debugprintf("\nToken's Source");
    Debugprintf1("\n  Source Name        == %.8s",(*ptsTokenSource).SourceName);
    Debugprintf2("\n  Source Identifier  == 0x%.8x%.8x",
       (*ptsTokenSource).SourceIdentifier.HighPart,
       (*ptsTokenSource).SourceIdentifier.LowPart);



    ticInfoClass   = TokenType;
    dwTokInfoBufSz = SZ_TOK_INFO_BUF;

    if (!GetTokenInformation(hAccessToken,
                             ticInfoClass,
                             ucTokInfoBuf,
                             (DWORD)SZ_TOK_INFO_BUF,
                             &dwTokInfoBufSz))
    { PERR("GetTokenInformation");
      return;
    }

    switch (*pttTokenType)
    { case  TokenPrimary       :
        Debugprintf("\nToken's Type is TokenPrimary");
        break;
      case  TokenImpersonation :
        Debugprintf("\nToken's Type is TokenImpersonation");
        Debugprintf("\n    Hence the token's TokenImpersonationLevel can be examined");

        ticInfoClass   = TokenImpersonationLevel;
        dwTokInfoBufSz = SZ_TOK_INFO_BUF;

        if (!GetTokenInformation(hAccessToken,
                                 ticInfoClass,
                                 ucTokInfoBuf,
                                 (DWORD)SZ_TOK_INFO_BUF,
                                 &dwTokInfoBufSz))
        { PERR("GetTokenInformation");
          return;
        }

        switch (*psilSecurityImpersonationLevel)
        { case                     SecurityAnonymous      :
            Debugprintf("\n  Token is a SecurityAnonymous impersonation token");
            break;
          case                     SecurityIdentification :
            Debugprintf("\n  Token is a SecurityIdentification impersonation token");
            break;
          case                     SecurityImpersonation  :
            Debugprintf("\n  Token is a SecurityImpersonation impersonation token");
            break;
          case                     SecurityDelegation     :
            Debugprintf("\n  Token is a SecurityDelegation impersonation token");
            break;
          default                   :
            Debugprintf1("\n  Token is an ILLEGAL KIND OF impersonation token!!! == 0x%.8x",*psilSecurityImpersonationLevel);
            break;
        };

	  break;
      default                  :
        Debugprintf1("\nToken's Type is ILLEGAL!!! == 0x%.8x",*pttTokenType);
        break;
    }



    ticInfoClass   = TokenStatistics;
    dwTokInfoBufSz = SZ_TOK_INFO_BUF;

    if (!GetTokenInformation(hAccessToken,
                             ticInfoClass,
                             ucTokInfoBuf,
                             (DWORD)SZ_TOK_INFO_BUF,
                             &dwTokInfoBufSz))
    { PERR("GetTokenInformation");
      return;
    }

    Debugprintf("\nToken's Statistics");
    Debugprintf2("\n  TokenId            == 0x%.8x%.8x",
      (*ptsTokenStatistics).TokenId.HighPart,
      (*ptsTokenStatistics).TokenId.LowPart);
    Debugprintf2("\n  AuthenticationId   == 0x%.8x%.8x",
      (*ptsTokenStatistics).AuthenticationId.HighPart,
      (*ptsTokenStatistics).AuthenticationId.LowPart);
    Debugprintf("\n  ExpirationTime     == (not supported in this release of Windows NT)");
    Debugprintf("\n  TokenType          == See token type above");
    Debugprintf("\n  ImpersonationLevel == See impersonation level above (only if TokenType is not TokenPrimary)");
    Debugprintf1("\n  DynamicCharged     == %ld",(*ptsTokenStatistics).DynamicCharged    );
    Debugprintf1("\n  DynamicAvailable   == %ld",(*ptsTokenStatistics).DynamicAvailable  );
    Debugprintf1("\n  GroupCount         == %d",(*ptsTokenStatistics).GroupCount        );
    Debugprintf1("\n  PrivilegeCount     == %d",(*ptsTokenStatistics).PrivilegeCount    );
    Debugprintf2("\n  ModifiedId         == 0x%.8x%.8x",
      (*ptsTokenStatistics).ModifiedId.HighPart,
      (*ptsTokenStatistics).ModifiedId.LowPart);



    Debugprintf("\n\n");

  }
}



/****************************************************************************\
*
* FUNCTION: InitializeWellKnownSIDs
*
\****************************************************************************/

VOID InitializeWellKnownSIDs(VOID)
{
  DWORD dwSidWith0SubAuthorities;
  DWORD dwSidWith1SubAuthority;
  DWORD dwSidWith2SubAuthorities;
  DWORD dwSidWith3SubAuthorities;
  DWORD dwSidWith4SubAuthorities;

  SID_IDENTIFIER_AUTHORITY siaNullSidAuthority    = SECURITY_NULL_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY siaWorldSidAuthority   = SECURITY_WORLD_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY siaLocalSidAuthority   = SECURITY_LOCAL_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY siaCreatorSidAuthority = SECURITY_CREATOR_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY siaNtAuthority         = SECURITY_NT_AUTHORITY;

  //  These SID sizes need to be allocated

  dwSidWith0SubAuthorities = GetSidLengthRequired( 0 );
  dwSidWith1SubAuthority   = GetSidLengthRequired( 1 );
  dwSidWith2SubAuthorities = GetSidLengthRequired( 2 );
  dwSidWith3SubAuthorities = GetSidLengthRequired( 3 );
  dwSidWith4SubAuthorities = GetSidLengthRequired( 4 );

  //  Allocate and initialize the universal SIDs

  psidNullSid         = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidWorldSid        = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidLocalSid        = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidCreatorOwnerSid = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidCreatorGroupSid = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);

  InitializeSid( psidNullSid,         &siaNullSidAuthority,    1 );
  InitializeSid( psidWorldSid,        &siaWorldSidAuthority,   1 );
  InitializeSid( psidLocalSid,        &siaLocalSidAuthority,   1 );
  InitializeSid( psidCreatorOwnerSid, &siaCreatorSidAuthority, 1 );
  InitializeSid( psidCreatorGroupSid, &siaCreatorSidAuthority, 1 );

  *(GetSidSubAuthority( psidNullSid,         0 )) = SECURITY_NULL_RID;
  *(GetSidSubAuthority( psidWorldSid,        0 )) = SECURITY_WORLD_RID;
  *(GetSidSubAuthority( psidLocalSid,        0 )) = SECURITY_LOCAL_RID;
  *(GetSidSubAuthority( psidCreatorOwnerSid, 0 )) = SECURITY_CREATOR_OWNER_RID;
  *(GetSidSubAuthority( psidCreatorGroupSid, 0 )) = SECURITY_CREATOR_GROUP_RID;

  // Allocate and initialize the NT defined SIDs

  psidNtAuthoritySid   = (PSID)LocalAlloc(LPTR,dwSidWith0SubAuthorities);
  psidDialupSid        = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidNetworkSid       = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidBatchSid         = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidInteractiveSid   = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidLogonIdsSid      = (PSID)LocalAlloc(LPTR,dwSidWith3SubAuthorities);
  psidServiceSid       = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidLocalSystemSid   = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidBuiltinDomainSid = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);

  InitializeSid( psidNtAuthoritySid,   &siaNtAuthority, 0 );
  InitializeSid( psidDialupSid,        &siaNtAuthority, 1 );
  InitializeSid( psidNetworkSid,       &siaNtAuthority, 1 );
  InitializeSid( psidBatchSid,         &siaNtAuthority, 1 );
  InitializeSid( psidInteractiveSid,   &siaNtAuthority, 1 );
  InitializeSid( psidLogonIdsSid,      &siaNtAuthority, 3 );
  InitializeSid( psidServiceSid,       &siaNtAuthority, 1 );
  InitializeSid( psidLocalSystemSid,   &siaNtAuthority, 1 );
  InitializeSid( psidBuiltinDomainSid, &siaNtAuthority, 1 );

  *(GetSidSubAuthority( psidDialupSid,        0 )) = SECURITY_DIALUP_RID;
  *(GetSidSubAuthority( psidNetworkSid,       0 )) = SECURITY_NETWORK_RID;
  *(GetSidSubAuthority( psidBatchSid,         0 )) = SECURITY_BATCH_RID;
  *(GetSidSubAuthority( psidInteractiveSid,   0 )) = SECURITY_INTERACTIVE_RID;
  *(GetSidSubAuthority( psidLogonIdsSid,      0 )) = SECURITY_LOGON_IDS_RID;
  *(GetSidSubAuthority( psidLogonIdsSid,      1 )) = 0; // Bogus!
  *(GetSidSubAuthority( psidLogonIdsSid,      2 )) = 0; // Also bogus!
  *(GetSidSubAuthority( psidServiceSid,       0 )) = SECURITY_SERVICE_RID;
  *(GetSidSubAuthority( psidLocalSystemSid,   0 )) = SECURITY_LOCAL_SYSTEM_RID;
  *(GetSidSubAuthority( psidBuiltinDomainSid, 0 )) = SECURITY_BUILTIN_DOMAIN_RID;
}

