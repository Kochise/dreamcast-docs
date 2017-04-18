class CompoundSynch
{
public:
virtual BOOL Initialize(int) = 0;
virtual void Cleanup() = 0;
virtual void Claim(int i) = 0;
virtual void Release(int i) = 0;
};

class CUnsafe : public CompoundSynch
{
public:
BOOL Initialize(int);
void Cleanup();
void Claim(int i);
void Release(int i);
};

class CMutex : public CompoundSynch
{ private:
  HANDLE hMutex;
  public:
  BOOL Initialize(int);
  void Cleanup();
  void Claim(int i);
  void Release(int i);

};

class CCritSect : public CompoundSynch
{ private:
  int iGroupNo;
  HANDLE hMutex;
  CRITICAL_SECTION *csShields;
  long *pCounters;
  public:
  BOOL Initialize(int);
  void Cleanup();
  void Claim(int i);
  void Release(int i);
};

class CEvents : public CompoundSynch
{ private:
  int iGroupNo;
  HANDLE hMutex;
  HANDLE *hEvents;
  long *pCounters;
  public:
  BOOL Initialize(int);
  void Cleanup();
  void Claim(int i);
  void Release(int i);
};

class CSemaphor : public CompoundSynch
{ private:
  int iGroupNo;
  HANDLE hMutex;
  HANDLE *hEvents;
  HANDLE *hSemaphores;
  long *pCounters;
  public:
  BOOL Initialize(int);
  void Cleanup();
  void Claim(int i);
  void Release(int i);
};

typedef HANDLE *PHANDLE;


class CWFMO : public CompoundSynch
{ private:
  int iGroupNo;
  HANDLE hMutex;
  HANDLE *hEvents;
  long *pCounters;
  PHANDLE *pHandleArrays;
  public:
  BOOL Initialize(int);
  void Cleanup();
  void Claim(int i);
  void Release(int i);
};

class CRWLock : public CompoundSynch
{ private:
  HANDLE hMutex;
  HANDLE hWriterMutex;
  HANDLE hReaderEvent;
  long iCounter;
  public:
  BOOL Initialize(int);
  void Cleanup();
  void Claim(int i);
  void Release(int i);
};

class CCCR : public CompoundSynch
{ private:
  int iGroupNo;
  HANDLE *hEvents;
  CRITICAL_SECTION csAtomizer;
  long *pCounters;
  HANDLE hAlwaysTrue;
  public:
  BOOL Initialize(int);
  void Cleanup();
  void Claim(int i);
  void Release(int i);
};


