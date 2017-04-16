
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1993 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

// These are the data structures used to change the data through the pointer.

//typedef struct CHAINLIST;

typedef struct CHAINLIST 
{ 
 int iInsecuredElement;
 int iSecuredElement;
} CHAINLIST;

typedef struct COMPLETECHAINLIST
{ 
 struct CHAINLIST cl;
 BOOL bValid;
} COMPLETECHAINLIST; 

class CMutex;
//class CSecuredMutex;
//class CSecuredNamedPipe;

class ChainedQueue
{ 
 private: 
  COMPLETECHAINLIST *cpBase;
  CMutex *m_hMutex;
 protected:
 public:
  int m_iErrorCode;
 public:
  ChainedQueue(void *pSharedMemory,int iLength,CMutex *hM);
  ChainedQueue(); // this is the "anonymous" constructor
  ~ChainedQueue();
  BOOL Retrieve(int iIndex,CHAINLIST *cpResult);
  BOOL Remove(int iIndex);
  BOOL Insert(int *iIndex,CHAINLIST *cpElement);
  int inline GetEntries() { return cpBase[0].cl.iInsecuredElement; };

};

#ifdef SERVER

class ServerChainedQueue : public ChainedQueue //, public CPrivateSecObject
{
 private:
 public:
  ServerChainedQueue(void *pSharedMemory,int iLength,CMutex *hM);
      
};

#endif
