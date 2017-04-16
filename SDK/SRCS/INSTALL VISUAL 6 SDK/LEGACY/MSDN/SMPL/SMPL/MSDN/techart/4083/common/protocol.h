// comclass. h -- definition for the base communication class


#define CMD_EXIT 0
#define CMD_ADDRECORD 1
#define CMD_DELETERECORD 2
#define CMD_RETRIEVERECORD 4
#define CMD_FAILURE 8
#define CMD_SUCCESS 16
#define CMD_GETENTRIES 32


class CClientCommunication;
struct CHAINLIST;

class 
CProtocol: public CFile
{
 protected:
  int m_bIsCommunicationEstablished;
 public:
  int m_iErrorCode;
 public:
  CProtocol();
  ~CProtocol();
  virtual BOOL Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError = NULL)=0;
  virtual UINT Read(void FAR* lpBuf, UINT nCount)=0;
  virtual void Write(const void FAR* lpBuf, UINT nCount)=0;
  virtual void Close()=0;
 };


class CDatabaseProtocol	: public CProtocol
{
 private:
  CClientCommunication *m_cBothways;
 public:
  CDatabaseProtocol(CClientCommunication *);
  BOOL Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError = NULL);

  UINT Read(void FAR* lpBuf, UINT nCount);
  void Write(const void FAR* lpBuf, UINT nCount);
  void Close();
};

class CClientDatabaseProtocol : public CDatabaseProtocol
{

 public:
  CClientDatabaseProtocol(CClientCommunication *);
  BOOL AddData(int *iIndex,CHAINLIST *clElement);
  BOOL RemoveData(int iIndex);
  BOOL RetrieveData(int iIndex, CHAINLIST *cpResult);
  BOOL GetEntries(int *);
  BOOL Terminate();

};

#ifdef SERVER

class CServerDatabaseProtocol	: public CDatabaseProtocol
{ public:
  CServerDatabaseProtocol(CServerCommunication *);
  BOOL AcceptCommand(int *iCommand, CHAINLIST *cpElement, int *iIndex);
  BOOL ProcessCommand(CHAINLIST *cpElement, int *iIndex);
  BOOL Fail(int iErrorCode);
  BOOL Acknowledge(int iIndex);
};


#endif
