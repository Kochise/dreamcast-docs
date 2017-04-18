// myclient.h

class CMyClient : public CDDEServer
{
    DECLARE_DYNCREATE(CMyClient);
public:
    virtual void Status(const char* pszFormat, ...);
};
