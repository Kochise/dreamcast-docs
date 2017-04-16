//#include "comclass.h"
#include <winsock.h>

#define STATUS_NOT_CONNECTED 0
#define STATUS_CONNECTION_PENDING 1
#define STATUS_CONNECTED 2


class CClientSocket: public virtual CClientCommunication
{protected: SOCKET m_theSocket;
            SOCKET m_CommSocket;
//            BOOL m_bWeAreServer;
            PHOSTENT m_phe;
            PSERVENT m_pse;
		    SOCKADDR m_sa;
		    BOOL m_bWeAreDuplicated;
//		  SOCKADDR_IN m_saThem;
  int m_iStatusPending;


 public:
  int m_iErrorCode;
 public:
  CClientSocket();
  ~CClientSocket();
  BOOL Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError = NULL);

  UINT Read(void FAR* lpBuf, UINT nCount);
  void Write(const void FAR* lpBuf, UINT nCount);
  void Close();
  inline int GetStatus() { return m_iStatusPending; };
  BOOL ReConnect();
};

class CServerSocket : public CClientSocket, public CServerCommunication
{
 public:
 CServerSocket();
 void CloseInstance(void) {};
 BOOL Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError = NULL);
 
 BOOL AwaitCommunicationAttempt();
 BOOL CancelCommunicationAttempt();
 CServerCommunication *Duplicate();
};

#ifdef SECURITY

class CSecuredSocket : public CServerSocket, public CKernelSecObject
{
private:
  BOOL SetTheDescriptor() { return TRUE;};
  BOOL GetTheDescriptor() { return TRUE;};

public:
  BOOL ImpersonateClient(BOOL) {return TRUE;};
  BOOL Open(const char* pszFileName, UINT nOpenFlags,CFileException* pError=0);

};

#endif
