// CClient object implementation
#include "stdafx.h"

#include "dbcode.h"
#include "comclass.h"
#include "npipe.h"
#include "client.h"

#include "protocol.h"

int CClientObject::DispatchFn(STATE_ENUMERATOR se,LPOVERLAPPED lpo)
{
  switch (se)
  {
   case(Read_Command): 
    return (Read_Command_Fn(lpo));
   case(Wrote_Error_Code):
    return (Wrote_Error_Code_Fn(lpo)); 
   case(Wrote_Result):
    return (Wrote_Result_Fn(lpo)); 
   case(Read_First_Add_Val):
    return (Read_First_Add_Val_Fn(lpo)); 
   case(Read_Second_Add_Val):
    return (Read_Second_Add_Val_Fn(lpo)); 
   case(Read_Delete_Index):
    return (Read_Delete_Index_Fn(lpo)); 
   case(Read_Retrieve_Index):
    return (Read_Retrieve_Index_Fn(lpo)); 
   case(Wrote_First_Retrieve_Val):
    return (Wrote_First_Retrieve_Val_Fn(lpo)); 
   case(Wrote_Second_Retrieve_Val):
    return (Wrote_Second_Retrieve_Val_Fn(lpo)); 
   };
  return 0;
};

CClientObject::CClientObject(CServerNamedPipe *cp,ServerChainedQueue *cq) 
{
 m_cpPipe=cp;
 m_cq=cq;
};

CClientObject::~CClientObject()
{
 m_cpPipe->CloseInstance();

};

UINT CClientObject::Read(void FAR* lpBuf, UINT nCount)
{
 return m_cpPipe->Read(lpBuf,nCount);
};

void CClientObject::Write(const void FAR* lpBuf, UINT nCount)
{
 m_cpPipe->Write(lpBuf,nCount);
};

void CClientObject::Trigger()
{
 m_se=Read_Command;
 Read((void FAR *)&m_iStatusWord,sizeof(int));
};

// this set of functions
// implements the finite automaton
int WINAPI CClientObject::Read_Command_Fn(LPOVERLAPPED lpo)
{
  // obtain the overlapped result from the
  // pipe, then branch:
  switch (m_iStatusWord)
  {
   case CMD_EXIT:
    return CMD_CLIENT_TERMINATED;
   case CMD_ADDRECORD:
    m_se=Read_First_Add_Val;
    // now dispatch a read call to retrieve the first record
    Read((void FAR *)&m_clElement.iSecuredElement,sizeof(int));
    return CMD_CONTINUE;
   case CMD_DELETERECORD:
    m_se=Read_Delete_Index;
    // dispatch a read call to retrieve the delete index
    Read((void FAR *)&m_iIndex,sizeof(int));
    return CMD_CONTINUE;
   case CMD_RETRIEVERECORD:
    m_se=Read_Retrieve_Index;
    // dispatch a read call to retrieve the index
    Read((void FAR *)&m_iIndex,sizeof(int));
    return CMD_CONTINUE;
   case CMD_GETENTRIES:
    m_se=Wrote_Error_Code;
    // now call the database for the # of entries;
    // depending on the outcome, set m_iStatusWord to
    //CMD_SUCCESS or CMD_FAIL, and m_iSendValue to the
    // #of entries or the error code, respectively;
    // then dispatch a write call
    m_iSendValue=m_cq->GetEntries();
    m_iStatusWord=CMD_SUCCESS;
    Write((void FAR *)&m_iStatusWord,sizeof(int));
    return CMD_CONTINUE;
  };
  return CMD_ERROR;
};

int WINAPI CClientObject::Wrote_Error_Code_Fn(LPOVERLAPPED lpo)
{
  m_se=Wrote_Result;
  // m_iStatusWord and m_iSend have already been
  // assigned meaningful values, so simply
  // dispatch a write call to spew out the 2nd word
  Write((void FAR *)&m_iSendValue,sizeof(int));
  return CMD_CONTINUE;
 };

int WINAPI CClientObject::Wrote_Result_Fn(LPOVERLAPPED lpo)
{
  m_se=Read_Command;
  // dispatch a read to fetch the next command
  Read((void FAR *)&m_iStatusWord,sizeof(int));
  return CMD_CONTINUE;
};

int WINAPI CClientObject::Read_First_Add_Val_Fn(LPOVERLAPPED lpo)
{
  m_se=Read_Second_Add_Val;
  // store the first value into the record to insert
  // and dispatch a read call for the second value
  Read((void FAR *)&m_clElement.iInsecuredElement,sizeof(int));
  return CMD_CONTINUE;
};

int WINAPI CClientObject::Read_Second_Add_Val_Fn(LPOVERLAPPED lpo)
{
  m_se=Wrote_Error_Code;
  if (!m_cq->Insert(&m_iIndex,&m_clElement))
  {
   m_iStatusWord=CMD_FAILURE;
   m_iSendValue=m_cq->m_iErrorCode;
  }
  else
  {
   m_iStatusWord=CMD_SUCCESS;
   m_iSendValue=m_iIndex;
  };
  // we have both values. Call the chainlist object
  // to try the add; set status and error code to
  // the appropriate values, and proceed. 
  Write((void FAR *)&m_iStatusWord,sizeof(int));
  return CMD_CONTINUE;
};

int WINAPI CClientObject::Read_Delete_Index_Fn(LPOVERLAPPED lpo)
{
  m_se=Wrote_Error_Code;
  // Call the chainlist object to try to delete the
  // record; set status and error code to the appropriate
  // values, and then proceed.
  if (!m_cq->Remove(m_iIndex))
  {
   m_iStatusWord = CMD_FAILURE;
   m_iSendValue = m_cq->m_iErrorCode;
  }
  else
  {
   m_iStatusWord = CMD_SUCCESS;
   m_iSendValue = 0;
  };
  Write((void FAR *)&m_iStatusWord,sizeof(int));
  return CMD_CONTINUE;
};

int WINAPI CClientObject::Read_Retrieve_Index_Fn(LPOVERLAPPED lpo)
{
  // this is the only case that can get us to
  // two different states, so wait with the next
  // state until we figured out what's going on...
  // call the chainlist object to try to retrive
  // the record. 
  if (m_cq->Retrieve(m_iIndex,&m_clElement))
  { 
   m_se=Wrote_First_Retrieve_Val;
   m_iStatusWord=CMD_SUCCESS;
   m_iSendValue=m_clElement.iInsecuredElement;
  // set status to CMD_SUCCESS; dispatch a Write call
  // dispatch another CMD_SUCCESS, and set a variable
  // to the first record. Set the error code to the 
  // second one.
  }
  else
  {
   m_se=Wrote_Error_Code;
   m_iStatusWord=CMD_FAILURE;
   m_iSendValue=m_cq->m_iErrorCode;
   // dispatch a write call to output the status value
   // CMD_FAIL, set m_iErrorCode to the error return
   // from the retrieve operation
  };
  Write((void FAR *)&m_iStatusWord,sizeof(int));
  return CMD_CONTINUE; 
};

int WINAPI CClientObject::Wrote_First_Retrieve_Val_Fn(LPOVERLAPPED lpo)
{
  m_se=Wrote_Second_Retrieve_Val;
  // simply dispatch a write to output the first
  // record	(CMD_SUCCESS).
  Write((void FAR *)&m_iSendValue,sizeof(int));
  return CMD_CONTINUE;
};

int WINAPI CClientObject::Wrote_Second_Retrieve_Val_Fn(LPOVERLAPPED lpo)
{
  m_se=Wrote_Error_Code;
  m_iSendValue=m_clElement.iSecuredElement;
  Write((void FAR *)&m_iStatusWord,sizeof(int));

  // output	the second value.
  return CMD_CONTINUE;
};

