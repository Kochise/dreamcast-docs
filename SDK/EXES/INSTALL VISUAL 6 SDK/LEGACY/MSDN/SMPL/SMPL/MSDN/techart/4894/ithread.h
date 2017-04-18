#ifndef __InternetThread_h__
#define __InternetThread_h__
#include <wininet.h>

//   Return values for GetWebPageWorkerThread
const UINT THREAD_GOOD = 0 ;
const UINT THREAD_BAD = 1 ;

//
// Message to post when thread is done.
//
#define WM_READFILECOMPLETED (WM_USER + 100)

//
//  CInternetThread Class...manages worker thread which reads from Internet.
//
class CInternetThread
{
public:
   // Construction
   CInternetThread() ;
   ~CInternetThread() ;

   // Initialization
   BOOL Init(HWND hPostMsgWnd) ;

   // Re-initialized Internet functions. Used after changing access type.
   void ResetSession() ;

   // Manage Buffer where HTML text is placed.
   void EmptyBuffer()
      { delete m_buffer ; m_buffer = NULL ; }
   BOOL IsBufferEmpty() 
      { return m_buffer == NULL;}
   char* GetBuffer()
      { return m_buffer ;}

   // Access Type 
   int GetAccessTypeIndex() ;
   void SetAccessTypeIndex(int index) ;

   // Proxy Server name.
   CString& GetProxyServer() 
      {return m_strProxyServer; }
   void SetProxyServer(CString& strProxyServer) 
      { m_strProxyServer = strProxyServer; ResetSession() ;}

   // Go get the requested Internet page.
   void GetPage(CString& rAddress) ;

private:
   // Worker thread calls _GetPageWorker.
   static UINT GetWebPageWorkerThread(LPVOID pvThread) ;

   // This is where the actually work is done.
   UINT _GetPageWorker() ;

   CString m_strServer ;
   CString m_strPath ;
   CString m_strProxyServer ;
   DWORD m_dwAccessType ;
   char* m_buffer ;

   HINTERNET m_hSession ;
   HWND m_hPostMsgWnd ;
};

//
// Working Thread which does all the actually internet work.
//
UINT GetWebPageWorkerThread(LPVOID pvThreadData);

#endif 
