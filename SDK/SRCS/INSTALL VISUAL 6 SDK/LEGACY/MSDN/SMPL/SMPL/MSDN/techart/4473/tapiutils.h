//
// TAPIUTILS.H
//
#include <tapi.h>


class CTapiConnection
{

 protected:
    // this area contains the protected members of the CTapiConnection class
    DWORD m_dwNumDevs;   // the number of line devices available
    DWORD m_dwDeviceID;  // the device ID
    DWORD m_dwRequestedID;
    LONG m_lAsyncReply;


    // BOOLEANS to handle reentrancy
    BOOL m_bShuttingDown;
    BOOL m_bStoppingCall;
    BOOL m_bInitializing;
    BOOL m_bReplyReceived;
    

    BOOL m_bTapiInUse;   // whether TAPI is in use or not
    BOOL m_bInitialized; // whether TAPI has been initialized

 public:
    // this area contains the public members of the CTapiConnection class
    HLINEAPP m_hLineApp; // the usage handle of this application for TAPI
    HCALL m_hCall;       // handle to the call
    HLINE m_hLine;       // handle to the open line
    DWORD m_dwAPIVersion;   // the API version
    char m_szPhoneNumber[64];  // the phone number to call

 protected:
    // Here is where I put the protected (internal) functions
    BOOL ShutdownTAPI();
    BOOL HandleLineErr(long lLineErr);
    LPLINEDEVCAPS GetDeviceLine(DWORD *dwAPIVersion, LPLINEDEVCAPS lpLineDevCaps);
    LPLINEDEVCAPS MylineGetDevCaps(LPLINEDEVCAPS lpLineDevCaps,
        DWORD dwDeviceID, DWORD dwAPIVersion);
    LPVOID CheckAndReAllocBuffer(LPVOID lpBuffer, size_t sizeBufferMinimum);
    LPLINEADDRESSCAPS MylineGetAddressCaps (LPLINEADDRESSCAPS lpLineAddressCaps,
        DWORD dwDeviceID, DWORD dwAddressID,DWORD dwAPIVersion, DWORD dwExtVersion);
    BOOL MakeTheCall(LPLINEDEVCAPS lpLineDevCaps,LPCSTR lpszAddress);
    LPLINECALLPARAMS CreateCallParams (LPLINECALLPARAMS lpCallParams, LPCSTR lpszDisplayableAddress);
    long WaitForReply (long lRequestID);
    void HandleLineCallState(DWORD dwDevice, DWORD dwMessage, DWORD dwCallbackInstance,
        DWORD dwParam1, DWORD dwParam2, DWORD dwParam3);


 private:
   // This section is for private functions

 public:
    // Public functions
    CTapiConnection();   
    ~CTapiConnection();
    BOOL Create(char *szPhoneNumber = NULL);
    BOOL DialCall(char *szPhoneNumber = NULL);
    BOOL HangupCall();
    static void CALLBACK lineCallbackFunc(
        DWORD dwDevice, DWORD dwMsg, DWORD dwCallbackInstance, 
        DWORD dwParam1, DWORD dwParam2, DWORD dwParam3);

};

