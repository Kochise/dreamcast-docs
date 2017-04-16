// mypanel.h

#include "ctrlpan.h"

#define MYSERVICENAME "NT Service Demonstration"

class CMyPanel : public CControlPanel
{
public:
    virtual LONG OnInquire(UINT uAppNum, NEWCPLINFO* pInfo); 
    virtual LONG OnDblclk(HWND hwndCPl, UINT uAppNum, LONG lData);
};

