// cmutex.cpp -- implements a mutex as a shared, secureable object...


class CMutex
{
protected:
 HANDLE m_hMutex;

public: 
 int m_iErrorCode;

public:
 CMutex();
 BOOL Open(PSTR pName);
 ~CMutex();
 void Claim();
 BOOL Release();
 BOOL Close();
 void ErrorCheck(PSTR pMsg);
} ;

#ifdef SECURITY

class CSecuredMutex : public CKernelSecObject, public CMutex
{
public:
 CSecuredMutex(PSTR pName);
private:
 BOOL SetTheDescriptor(void);
 BOOL GetTheDescriptor(void);
};

#endif 
