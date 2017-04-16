//#include "comclass.h"
//#include <winsock.h>

#define STATUS_NOT_CONNECTED 0
#define STATUS_CONNECTION_PENDING 1
#define STATUS_CONNECTED 2


#include "cncb.h"


class CClientNetBIOS: public virtual CClientCommunication
{
 protected: 
  CNCB m_thisNCB;
  UCHAR m_lsn;
  char m_pszPaddedFileName[MAXMACHINENAME];
  int m_iStatusPending;

 public:
  int m_iErrorCode;

 public:
  CClientNetBIOS();
  ~CClientNetBIOS();
  virtual BOOL Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError = NULL);

  UINT Read(void FAR* lpBuf, UINT nCount);
  void Write(const void FAR* lpBuf, UINT nCount);
  void Close();

  BOOL ReConnect();
  inline int GetStatus() { return m_iStatusPending; };

};

class CServerNetBIOS : public CClientNetBIOS, public CServerCommunication
{
 public:
 void CloseInstance(void);
 CServerNetBIOS();
 BOOL AwaitCommunicationAttempt();
 BOOL CancelCommunicationAttempt();
 virtual CServerCommunication *Duplicate();

 };

#ifdef SECURITY

class CSecuredNetBIOS : public CServerNetBIOS, public CKernelSecObject
{
private:
  BOOL SetTheDescriptor() { return TRUE;};
  BOOL GetTheDescriptor() { return TRUE;};

public:
  BOOL ImpersonateClient(BOOL) {return TRUE;};
  BOOL Open(const char* pszFileName, UINT nOpenFlags,CFileException* pError=0);

};

#endif
