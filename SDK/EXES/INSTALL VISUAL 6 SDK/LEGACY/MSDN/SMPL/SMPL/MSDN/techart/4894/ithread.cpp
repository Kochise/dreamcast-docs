#include "stdafx.h"
#include "IThread.h"


//
// Helper function
//
BOOL Succeeded(HANDLE h, LPCTSTR strFunctionName) ;

//
// Constructor
//
CInternetThread::CInternetThread()
   : m_hPostMsgWnd(NULL), 
      m_hSession(NULL), 
      m_buffer(NULL),
      m_dwAccessType(PRE_CONFIG_INTERNET_ACCESS)
{
}

//
// Closes the Internet session so InternetOpen will be called on next GetPage.
//
void CInternetThread::ResetSession()
{
   TRACE0("Resetting Session\r\n") ;
   if (m_hSession != NULL)
   {
      VERIFY(::InternetCloseHandle(m_hSession)) ;
      m_hSession = NULL ;
   }   
}

//
// 
//
CInternetThread::~CInternetThread()
{
   if (m_buffer) delete m_buffer ;
   ResetSession(); 
}

//
// 
//
BOOL CInternetThread::Init(HWND hPostMsgWnd)
{
   ASSERT(hPostMsgWnd) ;
   m_hPostMsgWnd = hPostMsgWnd ;

   return TRUE ;
}

//
// Returns an Index which represents the AccessType. Used by CAccessTypeDlg
//

int CInternetThread::GetAccessTypeIndex() 
{
   // This function is tied to the dialog box...
   int index = 0 ;
   switch (m_dwAccessType)
   {
   case PRE_CONFIG_INTERNET_ACCESS:
      index = 0 ;
      break ;
   case GATEWAY_INTERNET_ACCESS:
      index = 1 ;
      break ;
   case CERN_PROXY_INTERNET_ACCESS:
      index = 2 ;
      break ;
   case LOCAL_INTERNET_ACCESS:
      index = 3 ;
      break ;
   default:
      ASSERT(0) ;
   }
   return index ;
}

//
// Sets the Access Type using an Index returned from the CAccessTypeDlg
//
void CInternetThread::SetAccessTypeIndex(int index) 
{
   // This function is tied to the dialog box...
   switch(index)
   {
   case 0:
      m_dwAccessType = PRE_CONFIG_INTERNET_ACCESS ;
      break;
   case 1:
      m_dwAccessType = GATEWAY_INTERNET_ACCESS ;
      break;
   case 2:
      m_dwAccessType = CERN_PROXY_INTERNET_ACCESS ;
      break;
   case 3:
      m_dwAccessType = LOCAL_INTERNET_ACCESS ;
      break;
   default:
      ASSERT(0) ;
   }
   ResetSession() ;
}

//
// Varify that rAddress is partially valid. Start the worker thread to get a web page.
//
void CInternetThread::GetPage(CString& rAddress)
{
   ASSERT(!rAddress.IsEmpty()) ;
   //
   // Parse the http address for the server and file names
   //
   CString strTemp = rAddress.Mid(7) ; // Remove http://
   int i = strTemp.Find("/"); // Filename on address?
   if (i != -1)
   {
      m_strServer = strTemp.Left(i) ;
      m_strPath = strTemp.Mid(i) ;
      TRACE("Path = [%s]", (LPCTSTR)m_strPath) ; 
  }
   else
      m_strServer = strTemp ;

   TRACE("\t Server = [%s] \r\n", (LPCTSTR)m_strServer) ;   

   ASSERT(IsBufferEmpty()) ;
   //
   // Start a worker thread to get the web page.
   //
   AfxBeginThread(GetWebPageWorkerThread, this) ;
}

//
// This is the thread function. 
//
UINT CInternetThread::GetWebPageWorkerThread(LPVOID pvThread)
{
   TRACE0("GetWebPageWorkerThread\r\n") ;

   CInternetThread* pInternetThread = (CInternetThread*) pvThread ;
   if (pInternetThread == NULL 
       || pInternetThread->m_strServer.IsEmpty()
         || pInternetThread->m_hPostMsgWnd == NULL)
   {
      TRACE0("InternetThread isn't a valid\r\n") ;
      return THREAD_BAD ;
   }

   return pInternetThread->_GetPageWorker() ;
}

//
// This is where all of the actually Internet work is done.
//
UINT CInternetThread::_GetPageWorker()
{
    UINT uiResult = THREAD_BAD;

    if (m_hSession == NULL)
   {
      //
      // Initialize the Internet Functions.
      //
      TRACE("Starting Session (Access = %i) (Proxy = %s)\r\n",
            GetAccessTypeIndex(),
            (LPCTSTR)m_strProxyServer) ;
      m_hSession = ::InternetOpen("MSDN SurfBear",
                                  m_dwAccessType,
                                  m_strProxyServer,
                                  INTERNET_INVALID_PORT_NUMBER,
                                  0 ) ;

      if (!Succeeded(m_hSession, "InternetOpen"))
      {
         // Send message to UI that we finished.
         ::PostMessage(m_hPostMsgWnd,WM_READFILECOMPLETED, NULL, (LPARAM)THREAD_BAD) ;

         return THREAD_BAD;
      }
   }

   HINTERNET hConnect = ::InternetConnect(m_hSession,
                                          m_strServer,
                                          INTERNET_INVALID_PORT_NUMBER,
                                          "",
                                          "",
                                          INTERNET_SERVICE_HTTP,
                                          0,
                                          0) ;

                                          
   if (Succeeded(hConnect, "InternetConnect"))
   {

      HINTERNET hHttpFile = ::HttpOpenRequest(hConnect,
                                              "GET",
                                              m_strPath,
                                              HTTP_VERSION,
                                              NULL,
                                              0,
                                              INTERNET_FLAG_DONT_CACHE,
                                              0) ;

      if (Succeeded(hHttpFile, "HttpOpenRequest"))
      {
         
         BOOL bSendRequest = ::HttpSendRequest(hHttpFile, NULL, 0, 0, 0);
         
         if (Succeeded((HINTERNET)bSendRequest, "HttpSendRequest"))
         {
            // Get size of file.
            char bufQuery[32] ;
            DWORD dwFileSize ;
            DWORD dwLengthBufQuery = sizeof (bufQuery);
            BOOL bQuery = ::HttpQueryInfo(hHttpFile,
                           HTTP_QUERY_CONTENT_LENGTH, 
                           bufQuery, 
                           &dwLengthBufQuery,
                           NULL) ;
            if (Succeeded((HINTERNET)bQuery, "HttpQueryInfo"))
            {
               // The Query was successful, so allocate the memory.
               TRACE("HttpQueryInfo FileSize is %s.\r\n", bufQuery) ;
               dwFileSize = (DWORD)atol(bufQuery) ;
            }
            else
            {
               // The Query failed. Allocate some memory. Should allocate memory in blocks.
               TRACE("\tQueryInfo Failed. Just get 5k.\r\n") ;
               dwFileSize = 5*1024 ;
            }

            ASSERT(m_buffer == NULL); 
            m_buffer = new char[dwFileSize+1] ;
            DWORD dwBytesRead ;
            BOOL bRead = ::InternetReadFile(hHttpFile,	
                                            m_buffer,	
                                            dwFileSize+1, 	
                                            &dwBytesRead);	
            if (Succeeded((HINTERNET)bRead, "InternetReadFile"))
            {
               TRACE("\tBytes Read is %d\r\n", dwBytesRead) ;
               m_buffer[dwBytesRead] = 0 ;
               uiResult = THREAD_GOOD;
            } // InternetReadFile
         } // HttpSendRequest

         VERIFY(::InternetCloseHandle(hHttpFile)); 
      } // HttpOpenRequest

      VERIFY(::InternetCloseHandle(hConnect)) ;
   } // InternetConnect 

   ::PostMessage(m_hPostMsgWnd,WM_READFILECOMPLETED, NULL, (LPARAM)uiResult) ;

   return uiResult ;
}

//
//
//
BOOL Succeeded(HANDLE h, LPCTSTR strFunctionName)
{
   if (h == NULL)
   {
      DWORD dwError = GetLastError() ;
      TRACE("%s *** Error = %u***\r\n",strFunctionName, dwError) ;

      CString errString ;
      errString.Format("%s returns error %u", strFunctionName, dwError) ;
      AfxMessageBox(errString, MB_ICONEXCLAMATION | MB_OK) ;
      return FALSE;
   }
   else
   {
      TRACE("%s\r\n", strFunctionName) ;
      return TRUE ;
   }

}
