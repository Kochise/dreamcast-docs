// myconv.h

class CDDECliDlg;

class CMyConv : public CDDEConv
{
    DECLARE_DYNCREATE(CMyConv);
public:
    CMyConv();
    CMyConv(CDDEServer* pServer, CDDECliDlg* pDlg);
    virtual BOOL AdviseData(UINT wFmt, const char* pszTopic, const char* pszItem,
                            void* pData, DWORD dwSize);

    CDDECliDlg* m_pDlg;

};
