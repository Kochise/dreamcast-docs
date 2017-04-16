// mciobj.cpp : implementation file
// @doc

#include "stdafx.h"
#include "animate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMCIObject

IMPLEMENT_SERIAL(CMCIObject, CObject, 0 /* schema number*/ )

CMCIObject::CMCIObject()
{
    m_OpenParams.dwCallback = 0;
    m_OpenParams.wDeviceID = 0;
    m_OpenParams.lpstrDeviceType = NULL;
    m_OpenParams.lpstrElementName = NULL;
    m_OpenParams.lpstrAlias = NULL;
}

CMCIObject::~CMCIObject()
{
    // make sure the object is not in use
    if (m_OpenParams.wDeviceID != 0) {
        Close();
    }
    ASSERT(m_OpenParams.wDeviceID == 0);
}


/////////////////////////////////////////////////////////////////////////////
// CMCIObject serialization

void CMCIObject::Serialize(CArchive& ar)
{
    ASSERT(0); // not supported
}

/////////////////////////////////////////////////////////////////////////////
// local functions

void CMCIObject::MCIError(DWORD dwErr)
{
    char buf[256];

    buf[0] = '\0';
    mciGetErrorString(dwErr, buf, sizeof(buf));
    if (!strlen(buf)) {
        strcpy(buf, "Unknown error");
    }
    TRACE(buf);
}

/////////////////////////////////////////////////////////////////////////////
// CMCIObject commands

/*
@mfunc BOOL | CMCIObject | OpenFile | Open a file as an MCI object.
@syntax BOOL OpenFile(const char* pszFileName);
@parm char* | pszFileName | The path of the file to open.
@rdesc The return value is TRUE if the file is opened, FALSE if an
error occurs.
@comm The time format is set to milliseconds by default. A cue command
is sent to the open device so that it will play without delay when requested
to do so.
@xref <c CMCIObject>
*/

BOOL CMCIObject::OpenFile(const char* pszFileName)
{
    DWORD dwResult;

    if (m_OpenParams.wDeviceID != 0) {
        Close();
    }
    ASSERT(m_OpenParams.wDeviceID == 0);
    m_OpenParams.lpstrDeviceType = NULL;
    m_OpenParams.lpstrElementName = pszFileName;
    dwResult = mciSendCommand(0,
                              MCI_OPEN,
                              MCI_WAIT | MCI_OPEN_ELEMENT,
                              (DWORD)(LPVOID)&m_OpenParams);
    if (dwResult != 0) {
        MCIError(dwResult);
        m_OpenParams.wDeviceID = 0;
        return FALSE;
    }

    // Set the time format to milliseconds
    MCI_SET_PARMS set;
    set.dwTimeFormat = MCI_FORMAT_MILLISECONDS;
    dwResult = mciSendCommand(m_OpenParams.wDeviceID,
                              MCI_SET,
                              MCI_WAIT | MCI_SET_TIME_FORMAT,
                              (DWORD)(LPVOID)&set);
    if (dwResult != 0) {
        MCIError(dwResult);
        m_OpenParams.wDeviceID = 0;
        return FALSE;
    }

    // Try to cue the file so it will play with no delay
    mciSendCommand(m_OpenParams.wDeviceID,
                   MCI_CUE,
                   MCI_WAIT,
                   (DWORD)(LPVOID)NULL);

    return TRUE;
}

/*
@mfunc BOOL | CMCIObject | OpenDevice | Open a device as an MCI object.
@syntax BOOL OpenDevice(const char* pszDevName);
@parm const char* | pszDevName | The name of the device to open.
@rdesc The return value is TRUE if the device is opened, FALSE if an
error occurs.
@comm The time format is set to milliseconds by default. The device name
is one of the set of MCI device names defined in the registry in 
HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\WindowsNT\\CurrentVersion\\MCI.
@xref <c CMCIObject>
*/

BOOL CMCIObject::OpenDevice(const char* pszDevName)
{
    DWORD dwResult;

    if (m_OpenParams.wDeviceID != 0) {
        Close();
    }
    ASSERT(m_OpenParams.wDeviceID == 0);
    m_OpenParams.lpstrDeviceType = pszDevName;
    dwResult = mciSendCommand(0,
                              MCI_OPEN,
                              MCI_WAIT | MCI_OPEN_SHAREABLE | MCI_OPEN_TYPE,
                              (DWORD)(LPVOID)&m_OpenParams);
    if (dwResult != 0) {
        MCIError(dwResult);
        m_OpenParams.wDeviceID = 0;
        return FALSE;
    }

    // Set the time format to milliseconds
    MCI_SET_PARMS set;
    set.dwTimeFormat = MCI_FORMAT_MILLISECONDS;
    dwResult = mciSendCommand(m_OpenParams.wDeviceID,
                              MCI_SET,
                              MCI_WAIT | MCI_SET_TIME_FORMAT,
                              (DWORD)(LPVOID)&set);
    if (dwResult != 0) {
        MCIError(dwResult);
        m_OpenParams.wDeviceID = 0;
        return FALSE;
    }
    return TRUE;
}

/*
@mfunc void | CMCIObject | Close | Close the MCI object.
@syntax void Close();
@rdesc There is no return value.
@comm This function closes any open device or file.
@xref <c CMCIObject>
*/

void CMCIObject::Close()
{
    MCI_GENERIC_PARMS gp;
    DWORD dwResult;

    if (m_OpenParams.wDeviceID == 0) return; // already closed
    Stop(); // just in case
    dwResult = mciSendCommand(m_OpenParams.wDeviceID,
                              MCI_CLOSE,
                              MCI_WAIT,
                              (DWORD)(LPVOID)&gp);
    if (dwResult != 0) {
        MCIError(dwResult);
    }
    m_OpenParams.wDeviceID = 0;
}

/*
@mfunc void | CMCIObject | Play | Start playing.
@syntax void Play();
@rdesc There is no return value.
@comm This function starts playback of an open device or file.
Playback always begins from the start of the medium.
@xref <c CMCIObject> <mf CMCIObject::Stop>
*/

void CMCIObject::Play()
{
    MCI_PLAY_PARMS play;
    DWORD dwResult;

    if (m_OpenParams.wDeviceID == 0) return; // not open

    mciSendCommand(m_OpenParams.wDeviceID,
                   MCI_SEEK,
                   MCI_WAIT | MCI_SEEK_TO_START,
                   0);
    dwResult = mciSendCommand(m_OpenParams.wDeviceID,
                              MCI_PLAY,
                              NULL,
                              (DWORD)(LPVOID)&play);
    if (dwResult != 0) {
        MCIError(dwResult);
    }
}

/*
@mfunc void | CMCIObject | Stop | Stop the current action.
@syntax void Stop();
@rdesc There is no return value.
@comm This function stops playback of an open device or file.
@xref <c CMCIObject> <mf CMCIObject::Play>
*/

void CMCIObject::Stop()
{
    DWORD dwResult;

    if (m_OpenParams.wDeviceID == 0) return; // not open

    dwResult = mciSendCommand(m_OpenParams.wDeviceID,
                              MCI_STOP,
                              MCI_WAIT,
                              (DWORD)(LPVOID)NULL);
    if (dwResult != 0) {
        MCIError(dwResult);
    }
}

/*
@mfunc DWORD | CMCIObject | GetPosition | Get the current position.
@syntax DWORD GetPosition();
@rdesc The return value is the current position in milliseconds
from the start of the medium.
@xref <c CMCIObject>
*/

DWORD CMCIObject::GetPosition()
{
    if (m_OpenParams.wDeviceID == 0) return 0; // not open

    MCI_STATUS_PARMS status;
    status.dwItem = MCI_STATUS_POSITION;
    if (mciSendCommand(m_OpenParams.wDeviceID,
                       MCI_STATUS,
                       MCI_WAIT | MCI_STATUS_ITEM,
                       (DWORD)(LPVOID)&status) != 0) {
        return 0; // some error
    }
    return status.dwReturn;
}
