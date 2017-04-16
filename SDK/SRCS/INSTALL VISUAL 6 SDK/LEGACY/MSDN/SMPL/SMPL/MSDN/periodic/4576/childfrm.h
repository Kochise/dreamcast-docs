/////////////////
// MDI child frame overrides OnUpdateFrameTitle to 
// show which view is displayed.
//
class CChildFrame : public CMDIChildWnd {
   DECLARE_DYNCREATE(CChildFrame)
public:
   CChildFrame();
   virtual ~CChildFrame();
   virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
protected:
   //{{AFX_MSG(CChildFrame)
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
