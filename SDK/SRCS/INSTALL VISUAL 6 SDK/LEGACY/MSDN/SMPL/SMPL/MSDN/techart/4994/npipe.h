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
  HANDLE m_hReadEvent,m_hWriteEvent,m_hConnectEvent;
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

  UINT virtual Read(void FAR* lpBuf, UINT nCount);
  void virtual Write(const void FAR* lpBuf, UINT nCount);
  virtual void Close();

  BOOL ReConnect();
  inline int GetStatus() { return m_iStatusPending; };

};

class CServerNamedPipe : public CClientNamedPipe, public CServerCommunication
{
  private:
  UINT m_iFlagsOpened;
  BOOL m_bNotCancelled;
  int m_iInstances;
  OVERLAPPED m_ol1,m_ol2;
  unsigned long m_bytesSent1,m_bytesSent2;
  public:
  CServerNamedPipe();
  CServerNamedPipe(int iInstances);
  CServerNamedPipe(PSTR pIn, PSTR pOut, PSTR pBiDir);
  void CloseInstance(void);
  BOOL AwaitCommunicationAttempt();
  BOOL CancelCommunicationAttempt();
  virtual BOOL Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError = NULL);
  void Close(void);
  UINT virtual Read(void FAR* lpBuf, UINT nCount);
  void virtual Write(const void FAR* lpBuf, UINT nCount);
  virtual CServerCommunication *Duplicate();
};

