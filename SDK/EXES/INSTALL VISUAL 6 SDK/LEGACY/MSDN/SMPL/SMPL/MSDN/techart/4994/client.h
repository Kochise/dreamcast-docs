// CClient object prototype

#define NUMBER_OF_STATES 9  // this is always the same as
                            // elements in the STATE_ENUMERATOR type

class ServerChainedQueue;

typedef enum
{
 Read_Command,
 Wrote_Error_Code,
 Wrote_Result,
 Read_First_Add_Val,
 Read_Second_Add_Val,
 Read_Delete_Index,
 Read_Retrieve_Index,
 Wrote_First_Retrieve_Val,
 Wrote_Second_Retrieve_Val
} STATE_ENUMERATOR;

class CClientObject
{
 private:
 CServerNamedPipe *m_cpPipe;
 ServerChainedQueue *m_cq;
 int m_iStatusWord;
 int m_iSendValue;
 char TransmissionBuffer[255];
 CHAINLIST m_clElement;
 HANDLE m_hLocalPort;
 int m_iIndex;
 public:
 friend class CServerDatabaseProtocol;
 STATE_ENUMERATOR m_se;
 int DispatchFn(STATE_ENUMERATOR se,LPOVERLAPPED lpo);

 CClientObject(CServerNamedPipe *cp,ServerChainedQueue *cq); 
 ~CClientObject();
 UINT virtual Read(void FAR* lpBuf, UINT nCount);
 void virtual Write(const void FAR* lpBuf, UINT nCount);
 void Trigger();
// this set of functions
// implements the finite automaton
 int WINAPI Read_Command_Fn(LPOVERLAPPED lpo);
 int WINAPI Wrote_Error_Code_Fn(LPOVERLAPPED lpo);
 int WINAPI Wrote_Result_Fn(LPOVERLAPPED lpo);
 int WINAPI Read_First_Add_Val_Fn(LPOVERLAPPED lpo);
 int WINAPI Read_Second_Add_Val_Fn(LPOVERLAPPED lpo);
 int WINAPI Read_Delete_Index_Fn(LPOVERLAPPED lpo);
 int WINAPI Read_Retrieve_Index_Fn(LPOVERLAPPED lpo);
 int WINAPI Wrote_First_Retrieve_Val_Fn(LPOVERLAPPED lpo);
 int WINAPI Wrote_Second_Retrieve_Val_Fn(LPOVERLAPPED lpo);
};