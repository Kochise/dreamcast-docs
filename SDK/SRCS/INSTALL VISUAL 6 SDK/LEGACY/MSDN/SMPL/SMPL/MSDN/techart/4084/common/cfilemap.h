// CFileMapping.cpp -- implements a mutex as a shared, secureable object...


class CFileMapping
{
protected:
 HANDLE m_hMap;
 LPVOID m_lpMapping;

public:
 int m_iErrorCode;

public:			   
 CFileMapping();
 ~CFileMapping();
 BOOL Open(PSTR pName);
 LPVOID ObtainPointer();
 BOOL ReleasePointer();
 BOOL Close();
} ;

#ifdef SECURITY

class CSecuredFileMapping : public CKernelSecObject, public CFileMapping
{
public:
 CSecuredFileMapping(PSTR pName, DWORD dwSize);
private:
 BOOL SetTheDescriptor(void);
 BOOL GetTheDescriptor(void);
};

#endif
