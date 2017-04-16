// comclass. h -- definition for the base communication class

#define COMMUNICATION_MODE_ASYNCHRONOUS 0x0
#define COMMUNICATION_MODE_SYNCHRONOUS  0x1
#define COMMUNICATION_MODE_INBOUND 0x2
#define COMMUNICATION_MODE_OUTBOUND 0x4

class CClientCommunication: public CFile
{ 
 protected:
  int m_bIsCommunicationEstablished;
  CString cOtherMachineName;
  int m_iMode;
 public:
  CClientCommunication();
  ~CClientCommunication();
  virtual BOOL Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError = NULL)=0;
  virtual UINT Read(void FAR* lpBuf, UINT nCount)=0;
  virtual void Write(const void FAR* lpBuf, UINT nCount)=0;
  virtual void Close()=0;

// members related to the communication as such
  BOOL IsCommunicationOk();
  virtual BOOL ReConnect()=0;
};

class CServerCommunication: public virtual CClientCommunication
{ 
 public:
  virtual BOOL AwaitCommunicationAttempt();
  virtual BOOL CancelCommunicationAttempt();
  virtual CServerCommunication *Duplicate() =0;
};



