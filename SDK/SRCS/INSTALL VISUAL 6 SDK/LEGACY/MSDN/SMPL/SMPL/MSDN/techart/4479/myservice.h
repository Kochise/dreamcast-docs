// myservice.h

#include "ntservice.h"

class CMyService : public CNTService
{
public:
	CMyService();
	virtual BOOL OnInit();
    virtual void Run();
    virtual BOOL OnUserControl(DWORD dwOpcode);

    void SaveStatus();

	// Control parameters
	int m_iStartParam;
	int m_iIncParam;

	// Current state
	int m_iState;
};
