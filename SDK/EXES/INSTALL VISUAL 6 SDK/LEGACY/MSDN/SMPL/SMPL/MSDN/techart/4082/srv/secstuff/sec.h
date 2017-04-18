
#define DBASE_WRITE 0x20L
#define DBASE_READ 0x40L

// this initializes the application for security manipulation


BOOL SetSpecificPrivilegeInAccessToken(LPCSTR lpPrivType,BOOL bEnabled);
BOOL SetPrivilegeInAccessToken(BOOL);


class CSecureableObject
{
 protected:
  PSECURITY_DESCRIPTOR m_pSD;
  PACL m_pDACL;
  PACL m_pSACL;
  PSID m_pOwner;
  PSID m_pPrimaryGroup;
 public:
  int m_iSecErrorCode;
 protected:
  virtual BOOL SetTheDescriptor()=0;
  virtual BOOL GetTheDescriptor()=0;
 private:
  BOOL GetSIDFromName(PSTR pDomainName,PSTR pAccountName,BYTE **pcSid,char **pcDomainName);
 protected:
  BOOL BuildSD(PSECURITY_DESCRIPTOR pSelfRelativeReturnSD);
  void inline FreeDataStructures()
  {
   if (m_pSD) free (m_pSD);
   if (m_pDACL) free(m_pDACL);
   if (m_pSACL) free(m_pSACL);
   if (m_pOwner) free(m_pOwner);
   if (m_pPrimaryGroup) free(m_pPrimaryGroup);
   ZeroOut();
  };
  void inline ZeroOut()
  { 
   m_pSD = NULL;
   m_pDACL = NULL;
   m_pSACL = NULL;
   m_pOwner = NULL;
   m_pPrimaryGroup = NULL;
  };
 public:
  CSecureableObject(BOOL bProtected);   
  ~CSecureableObject();
  BOOL AddRightsTo(PSTR pDomainName,PSTR pAccountName,DWORD dwAccessMask,BOOL bGranted);
  BOOL RevokePreviouslyGrantedAccess(PSTR pAccountName,PSTR pDomainName);
  BOOL AddSecurity(DWORD dwAccessMask, LPSTR lpTitleString);
};

class CKernelSecObject : public CSecureableObject
{
 public:
  CKernelSecObject();
  ~CKernelSecObject();
  virtual BOOL SetObjectSecurity(HANDLE hObject);
  virtual BOOL GetObjectSecurity(HANDLE hObject);
};

class CUserSecObject : public CSecureableObject
{
 public:
  CUserSecObject();
  ~CUserSecObject();
  virtual BOOL SetObjectSecurity(HANDLE hObject);
  virtual BOOL GetObjectSecurity(HANDLE hObject);

};

class CPrivateSecObject : public CSecureableObject
{
 private:
  HANDLE m_hAccessToken;
  GENERIC_MAPPING m_gmPrivateMapping;
  PSECURITY_DESCRIPTOR m_ObjectSD;
  DWORD m_dwUniqueHandleId;

 public:
  CPrivateSecObject();
  ~CPrivateSecObject();
  virtual BOOL SetObjectSecurity();
  virtual BOOL GetObjectSecurity();
  BOOL MatchAccessRequest(DWORD dwMask, HANDLE hThread);
  DWORD MapRequestedRights (DWORD dwArg);
};
