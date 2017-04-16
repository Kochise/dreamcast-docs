//***********************************************************************
//
//  EZPrintView.h
//
//***********************************************************************

class CPrintView : public CView
{
    DECLARE_DYNCREATE (CPrintView)

protected:
    virtual void OnDraw (CDC*);
    virtual BOOL OnPreparePrinting (CPrintInfo*);

    DECLARE_MESSAGE_MAP ()
};
