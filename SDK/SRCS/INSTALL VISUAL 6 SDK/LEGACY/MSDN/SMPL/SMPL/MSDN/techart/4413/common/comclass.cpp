// comclass. cpp -- implementation of the base communication class

#include "stdafx.h"
#include "comclass.h"

CClientCommunication::CClientCommunication()
{
 m_bIsCommunicationEstablished = FALSE;
};

CClientCommunication::~CClientCommunication()
{
};

BOOL CClientCommunication::IsCommunicationOk()
{ 
 return m_bIsCommunicationEstablished;
};

BOOL CServerCommunication::AwaitCommunicationAttempt()
{
 return FALSE;
};

BOOL CServerCommunication::CancelCommunicationAttempt()
{
 return FALSE;
};



