//#include "comclass.h"

#define STATUS_NOT_CONNECTED 0
#define STATUS_CONNECTION_PENDING 1
#define STATUS_CONNECTED 2

#define DEFAULTINPIPENAME "defpipei"
#define DEFAULTOUTPIPENAME "defpipeo"
#define DEFAULTBIPIPENAME "defpipeb"

class CClientNamedPipe: public virtual CClientCommunication
{
 protected: 
  HANDLE m_hEvent;
  BOOL m_bWeAreServer,m_bInterrupted;
  char m_szPipeName[256];
  char m_szPipeEndNameIn[10];
  char m_szPipeEndNameOut[10];
  char m_szPipeEndNameBoth[10];
  int m_iStatusPending;
  DWORD m_dwState;

 public:
  int m_iErrorCode;
 public:
  CClientNamedPipe();
  CClientNamedPipe(PSTR pIn, PSTR pOut, PSTR pBiDir);
  ~CClientNamedPipe();
  virtual BOOL Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError = NULL);

  UINT Read(void FAR* lpBuf, UINT nCount);
  void Write(const void FAR* lpBuf, UINT nCount);
  virtual void Close();

  BOOL ReConnect();
  inline int GetStatus() { return m_iStatusPending; };

};

class CServerNamedPipe : public CClientNamedPipe, public CServerCommunication
{
  private:
  UINT m_iFlagsOpened;
  BOOL m_bNotCancelled;
  public:
  CServerNamedPipe();
  CServerNamedPipe(PSTR pIn, PSTR pOut, PSTR pBiDir);
  void CloseInstance(void);
  BOOL AwaitCommunicationAttempt();
  BOOL CancelCommunicationAttempt();
  virtual BOOL Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError = NULL);
  void Close(void);
  virtual CServerCommunication *Duplicate();

};

#ifdef SECURITY

class CSecuredNamedPipe : public CServerNamedPipe, public CKernelSecObject
{
private:
  BOOL SetTheDescriptor();
  BOOL GetTheDescriptor();
public:
  BOOL ImpersonateClient(BOOL);
  BOOL Open(const char* pszFileName, UINT nOpenFlags,CFileException* pError=0);

};

#endif

