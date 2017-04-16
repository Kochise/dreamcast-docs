// comclass. h -- definition for the base communication class

#define CHATTYPE 0
#define TRANSFERTYPE 1

class CServerCommunication;
class CClientCommunication;

class CProtocol: public CFile
{
  protected:
   CClientCommunication *m_cInBound;
   CClientCommunication *m_cOutBound;

  int m_bIsCommunicationEstablished;
  public:
  CProtocol();
  ~CProtocol();
  virtual BOOL Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError = NULL)=0;
  virtual UINT Read(void FAR* lpBuf, UINT nCount)=0;
  virtual void Write(const void FAR* lpBuf, UINT nCount)=0;
  virtual void Close()=0;

  BOOL CheckOnResponse(void);
  void Acknowledge();
  void Reject();


// members related to the communication as such
};


class CChatProtocol: public CProtocol
{private: 
// helper functions

 public:
  CChatProtocol();
  ~CChatProtocol();
  BOOL Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError = NULL);

  UINT Read(void FAR* lpBuf, UINT nCount);
  void Write(const void FAR* lpBuf, UINT nCount);
  void Close();
};

class CServerChatProtocol: public CChatProtocol
{
 public:
  CServerChatProtocol(CServerCommunication *cInBound, CServerCommunication *cOutBound);
  BOOL InitiateConversationAsServer(CString **csArg);
};

class CClientChatProtocol: public CChatProtocol
{
 public:
  CClientChatProtocol(CClientCommunication *cInBound, CClientCommunication *cOutBound);
  BOOL InitiateConversationAsClient(const char *szMachineName, int iMachineName);
};


class CFileTransferProtocol: public CProtocol
{protected: 
 DWORD dwFileLength;
 BOOL m_bWeAreServer;
 CFile *cfFile;
 public:
  CFileTransferProtocol();
  ~CFileTransferProtocol();
  BOOL Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError = NULL);

  UINT Read(void FAR* lpBuf, UINT nCount);
  UINT ReadHelper(void FAR* lpBuf, UINT nCount);
  void Write(const void FAR* lpBuf, UINT nCount);
  void WriteHelper(const void FAR* lpBuf, UINT nCount);

  void Close();
  DWORD GetLength();
  void SetLength(DWORD dwNewLen);

  BOOL LastMinuteCheckReceiver(BOOL);
  BOOL LastMinuteCheckSender(BOOL);

};

class CServerFileTransferProtocol: public CFileTransferProtocol
{
 public:
  CServerFileTransferProtocol(CServerCommunication *cInBound, CServerCommunication *cOutBound);
};

class CClientFileTransferProtocol: public CFileTransferProtocol
{
 public:
  CClientFileTransferProtocol(CClientCommunication *cInBound, CClientCommunication *cOutBound);
};

class CSelectorProtocol: public CProtocol
{ public:
  CSelectorProtocol();

  int GetCommunicationType(void);
  void SetCommunicationType(int);

// dummies to avoid error 2259
  BOOL Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError = NULL);
  UINT Read(void FAR* lpBuf, UINT nCount);
  void Write(const void FAR* lpBuf, UINT nCount);
  void Close();

};

class CServerSelectorProtocol: public CSelectorProtocol
{ 
  public:
  CServerSelectorProtocol(CServerCommunication *cInBound, CServerCommunication *cOutBound);
};

class CClientSelectorProtocol: public CSelectorProtocol
{ 
  public:
  CClientSelectorProtocol(CClientCommunication *cInBound, CClientCommunication *cOutBound);
};
