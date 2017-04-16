// myserv.h

#ifndef _MYSERV_
#define _MYSERV_

class CMyStringItem : public CDDEStringItem
{
protected:
    virtual void OnPoke();
};

class CMyTopic : public CDDETopic
{
public:
    CMyTopic();
    virtual BOOL Exec(void* pData, DWORD dwSize);
};

class CMyServer : public CDDEServer
{
public:
    CMyServer();
    virtual ~CMyServer();
    virtual void Status(const char* pszFormat, ...);
    virtual BOOL OnCreate();

public:
    CMyTopic m_DataTopic;
    CMyStringItem m_StringItem1;
    CMyStringItem m_StringItem2;
};

#endif // _MYSERV_
