#ifndef __DEVICE_H              // guard against multiple inclusion
#define __DEVICE_H

/********************************************************************
 * device.h
 *
 * Description
 *    CVMUSelection
 *    VMIMIME.DLL callback functions
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include <mapledev.h>           // maple (controller) functions
#include <perstore.h>           // VMU device functions
#include "window.h"             // base class CWindow
#include "critsect.h"           // CCriticalSection


/********************************************************************
 * Defines
 ********************************************************************/
#define NUM_DEVICES             8
#define DEVICE_SELECT_ABORT     0xff000000
#define DEVICE_SELECT_CANCEL    0x00ff0000

/********************************************************************
 * class CVMUSelecton
 *
 * Description
 *    Class for VMU device selection functionality for the VMIMIME.DLL
 *    callback function for the HTML control.
 ********************************************************************/
class CVMUSelection : public CWindow
{
    public:
        // Constructor/Destructor
        CVMUSelection(HANDLE hEvent, DWORD *pdwResults);
        virtual ~CVMUSelection(void);

        // Public functions
        HRESULT Start(void);
        HRESULT Stop(void);

        // CWindow overrides
        virtual HRESULT Draw(LPDIRECTDRAWSURFACE pDDS);
        virtual HRESULT Draw(HDC hdc);
        virtual HRESULT Joystick(DWORD dwButtons, DWORD dwButtonsHeld, WORD x, WORD y);

    private:
        // Internal class
        class CVMUDeviceData    // data for one VMU device
        {
            public:
                // Constructor/Destructor
                CVMUDeviceData(void);
                virtual ~CVMUDeviceData(void);

            public:
                IFlashDevice *  _pDevice;       // device interface pointer
                DWORD           _dwTotalBlocks; // number of total blocks free
                DWORD           _dwFreeBlocks;  // number of free blocks
                BOOL            _bFound;        // flag for device is in controller
        };

        // Internal functions
        void         SetData(BYTE nDevice, DWORD dwTotalBlocks, DWORD dwFreeBlocks);
        BYTE         FindAvailableDevices(void);
        BYTE         FindAvailableControllers(void);
        BOOL         EnumMapleDevicesCallback3(LPCMAPLEDEVICEINSTANCE pMDI);
        DWORD        ThreadProc(void);

        // Internal static functions
        static BOOL  EnumMapleDevicesCallback1(LPCMAPLEDEVICEINSTANCE pMDI, LPVOID pvData);
        static BOOL  EnumMapleDevicesCallback2(LPCMAPLEDEVICEINSTANCE pMDI, LPVOID pvData);
        static BOOL  EnumMapleDevicesCallback3(LPCMAPLEDEVICEINSTANCE pMDI, LPVOID pvData);
        static DWORD ThreadProc(LPVOID pvData);

    private:
        HANDLE              _hEventAbort;               // event from VMIMIME.DLL, set if aborted
        HANDLE              _hEventDone;                // event for blocking until selection is done
        BOOL                _bRunning;                  // in process of getting user's selection
        BYTE                _nSelected;                 // current VMU device selected
        HFONT               _hFont;                     // font in which to display prompt
        DWORD               _idThread;                  // ID of thread gathering device data
        TCHAR               _szPrompt[64];              // text of prompt for screen
        CVMUDeviceData      _aData[NUM_DEVICES];        // data for all VMU devices
        CCriticalSection    _cs;                        // critical section for thread control
        LPDIRECTDRAWSURFACE _pBitmap;                   // bitmap surface of device icons
        DWORD               _dwTotalBlocks;             // total blocks in current VMU device
        DWORD               _dwFreeBlocks;              // free blocks in current VMU device
        BYTE                _nDevices;                  // bit field of available VMU devices
        DWORD *             _pdwResults;                // pointer to port/device results
};

/********************************************************************
 * VMIMIME.DLL callback functions
 ********************************************************************/
HRESULT WINAPI GetVMUDevice(DWORD dwType, HANDLE hEventAbort, BYTE *pnPort, BYTE *pnDevice);
HRESULT WINAPI ShowVMUMessage(HRESULT hr, BOOL bLeave);

#endif // __DEVICE_H

