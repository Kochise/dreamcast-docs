//***************************************************************************
//
//  Life.h
//
//***************************************************************************

class CLifeApp : public CWinApp
{
public:
    virtual BOOL InitInstance ();

protected:
    afx_msg void OnAppAbout ();
    DECLARE_MESSAGE_MAP ()
};
