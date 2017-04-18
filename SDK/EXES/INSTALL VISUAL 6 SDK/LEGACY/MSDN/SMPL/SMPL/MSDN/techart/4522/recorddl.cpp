// recorddl.cpp : implementation file
//

#include "stdafx.h"
#include "animtest.h"
#include "recorddl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecordDlg dialog

CRecordDlg::CRecordDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CRecordDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CRecordDlg)
    m_strFormat = "";
    m_strSource = "";
    //}}AFX_DATA_INIT

    m_pWave = NULL;
    m_iNumDevs = 0;
    m_pDevCaps = NULL;
    m_NotifyObj.Attach(this);
    m_iMode = IDLE;
	m_pPal = NULL;	// 9/28/95 NigelT Added palette
}

CRecordDlg::~CRecordDlg()
{
    if (m_pDevCaps) delete m_pDevCaps;
}

void CRecordDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CRecordDlg)
    DDX_Control(pDX, IDC_SOURCE, m_cbSource);
    DDX_Control(pDX, IDC_FORMAT, m_cbFormat);
    DDX_Control(pDX, IDC_FRAME, m_wndFrame);
    DDX_Control(pDX, IDC_PLAY, m_btnPlay);
    DDX_Control(pDX, IDC_RECORD, m_btnRecord);
    DDX_Control(pDX, IDOK, m_btnOK);
    DDX_Control(pDX, IDC_STOP, m_btnStop);
    DDX_CBString(pDX, IDC_FORMAT, m_strFormat);
    DDX_CBString(pDX, IDC_SOURCE, m_strSource);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRecordDlg, CDialog)
    //{{AFX_MSG_MAP(CRecordDlg)
    ON_CBN_SELCHANGE(IDC_FORMAT, OnSelchangeFormat)
    ON_BN_CLICKED(IDC_PLAY, OnClickedPlay)
    ON_BN_CLICKED(IDC_RECORD, OnClickedRecord)
    ON_BN_CLICKED(IDC_STOP, OnClickedStop)
    ON_CBN_SELCHANGE(IDC_SOURCE, OnSelchangeSource)
    ON_WM_DRAWITEM()
    ON_WM_MEASUREITEM()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecordDlg message handlers

BOOL CRecordDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    // Wave must not be provided by caller
    ASSERT(m_pWave == NULL);
    CRect rcVU;
    m_wndFrame.GetWindowRect(&rcVU);
    ScreenToClient(&rcVU);
    m_VU.Create("VU",
                WS_CHILD | WS_VISIBLE,
                rcVU,
                this,
                1,
				m_pPal);	// 9/28/95 NigelT Added palette
    m_VU.SetValue(0, 0);

    // Fill the input device list box
    FillDeviceList();
    // Fill the device list
    FillFormatList();
    // Get the VU meter going
    SetMode(SAMPLING);
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRecordDlg::OnSelchangeFormat()
{
    OnClickedStop();
}

void CRecordDlg::OnClickedPlay()
{
    SetMode(PLAYING);
}

void CRecordDlg::OnClickedRecord()
{
    SetMode(RECORDING);
}

void CRecordDlg::OnClickedStop()
{
    SetMode(SAMPLING);
}

void CRecordDlg::OnSelchangeSource()
{
    OnClickedStop();
    FillFormatList();
}

void CRecordDlg::OnCancel()
{
    OnClickedStop();
    SetMode(IDLE);
    m_VU.DestroyWindow();
    if (m_pWave) {
        delete m_pWave;
        m_pWave = NULL;
    }
    CDialog::OnCancel();
}

void CRecordDlg::OnOK()
{
    OnClickedStop();
    SetMode(IDLE);
    m_VU.DestroyWindow();
    CDialog::OnOK();
}

void CRecordDlg::FillDeviceList()
{
    m_iNumDevs = waveInGetNumDevs();
    if (m_iNumDevs == 0) {
        AfxMessageBox("There are no suitable input devices");
        EndDialog(IDCANCEL);
        return;
    }
    // Allocate memory for the device list
    if (m_pDevCaps) delete m_pDevCaps;
    m_pDevCaps = new WAVEINCAPS[m_iNumDevs];
    m_cbSource.ResetContent();
    for (int i=0; i<m_iNumDevs; i++) {
        waveInGetDevCaps(i,
                         &m_pDevCaps[i],
                         sizeof(WAVEINCAPS));
        // save the device id in the manufacturer field
        m_pDevCaps[i].wMid = i;
        m_cbSource.AddString((LPCSTR)&m_pDevCaps[i]);
    }
    m_cbSource.SetCurSel(0);
}

void CRecordDlg::FillFormatList()
{
    m_cbFormat.ResetContent();
    int iSel = m_cbSource.GetCurSel();
    if(iSel == CB_ERR) return;
    WAVEINCAPS* pCaps = (WAVEINCAPS*) m_cbSource.GetItemData(iSel);
    ASSERT(pCaps);
    DWORD dwMask = 0x00000001;
    for (int i=0; i<12; i++) {
        if (pCaps->dwFormats & dwMask) {
            m_cbFormat.AddString((LPCSTR) dwMask);
        }
        dwMask = dwMask << 1;
    }
    m_cbFormat.SetCurSel(0);
}

void CRecordDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT pDI)
{
    char* pszText = NULL;
    switch (nIDCtl) {
    case IDC_SOURCE: {
        WAVEINCAPS* pCaps = (WAVEINCAPS*)(pDI->itemData);
        pszText = pCaps->szPname;
        } break;
    case IDC_FORMAT: {
        switch(pDI->itemData) {
        case WAVE_FORMAT_1M08:
            pszText = "11.025 kHz, 8 bit, mono";
            break;
        case WAVE_FORMAT_1S08:
            pszText = "11.025 kHz, 8 bit, stereo";
            break;
        case WAVE_FORMAT_1M16:
            pszText = "11.025 kHz, 16 bit, mono";
            break;
        case WAVE_FORMAT_1S16:
            pszText = "22.05 kHz, 16 bit, stereo";
            break;
        case WAVE_FORMAT_2M08:
            pszText = "22.05 kHz, 8 bit, mono";
            break;
        case WAVE_FORMAT_2S08:
            pszText = "22.05 kHz, 8 bit, stereo";
            break;
        case WAVE_FORMAT_2M16:
            pszText = "22.05 kHz, 16 bit, mono";
            break;
        case WAVE_FORMAT_2S16:
            pszText = "22.05 kHz, 16 bit, stereo";
            break;
        case WAVE_FORMAT_4M08:
            pszText = "44.1 kHz, 8 bit, mono";
            break;
        case WAVE_FORMAT_4S08:
            pszText = "44.1 kHz, 8 bit, stereo";
            break;
        case WAVE_FORMAT_4M16:
            pszText = "44.1 kHz, 16 bit, mono";
            break;
        case WAVE_FORMAT_4S16:
            pszText = "44.1 kHz, 16 bit, stereo";
            break;
        default:
            pszText = "Unknown";
            break;
        }

        } break;
    default:
        break;
    }
    if (!pszText) return;
    ::DrawText(pDI->hDC,
               pszText,
               -1,
               &(pDI->rcItem),
               DT_LEFT | DT_VCENTER);
    if (pDI->itemState & ODS_SELECTED) {
        ::InvertRect(pDI->hDC, &(pDI->rcItem));
    }
    if (pDI->itemState & ODS_FOCUS) {
        ::DrawFocusRect(pDI->hDC, &(pDI->rcItem));
    }
}

void CRecordDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
    CClientDC dc (this);
    TEXTMETRIC tm;
    dc.GetTextMetrics(&tm);
    lpMeasureItemStruct->itemHeight = tm.tmHeight;
}

void CRecordDlg::SetMode(MODE m)
{
    if (m == m_iMode) return; // no change

    // Stop whatever we are doing now
    TRACE("Stop wave");
    if (m_pWave) m_pWave->Stop();
    switch (m_iMode) {
    case SAMPLING:
    case RECORDING:
        TRACE("Reset input device");
        m_InDev.Reset();
        m_InDev.Close();
        break;
    case PLAYING:
        // nothing else to do
        break;
    }
    m_iMode = IDLE;

    // Start up in the new mode
    switch (m) {
    case SAMPLING:
    case RECORDING:
        TRACE("Start sampling or recording");
        {
        // get the selected input device
        int iSel = m_cbSource.GetCurSel();
        if(iSel == CB_ERR) return;
        WAVEINCAPS* pCaps = (WAVEINCAPS*) m_cbSource.GetItemData(iSel);
        ASSERT(pCaps);
        // get the device id we saved in the man. id slot
        UINT uiID = pCaps->wMid;
        // get the selected format
        iSel = m_cbFormat.GetCurSel();
        if(iSel == CB_ERR) return;
        DWORD dwFormat = m_cbFormat.GetItemData(iSel);
        ASSERT(dwFormat);
        // Open the device
        WAVEFORMATEX fmt;
        BuildFormat(fmt, dwFormat);
        if (!m_InDev.Open(uiID, &fmt)) return;
        if (m == SAMPLING) {
            m_SampleWave.DeleteAll();
            m_SampleWave.Create(&fmt);
            m_SampleWave.Record(&m_InDev,
                                1024,  
                                &m_NotifyObj);
        } else if (m == RECORDING) {
            if (!m_pWave) m_pWave = new CWave;
            ASSERT(m_pWave);
            m_pWave->Create(&fmt);
            m_pWave->Record(&m_InDev,
                            4096,  
                            &m_NotifyObj);
        }
        } break;

    case PLAYING:
        TRACE("Start playing");
        if (m_pWave) m_pWave->Play(NULL, &m_NotifyObj);
        break;
    }
    m_iMode = m;
    // set the button states
    if ((m_iMode == PLAYING) || (m_iMode == RECORDING)) {
        m_btnStop.EnableWindow(TRUE);
    } else {
        m_btnStop.EnableWindow(FALSE);
    }
    if (m_iMode == PLAYING) {
        m_btnPlay.EnableWindow(FALSE);
    } else {
        m_btnPlay.EnableWindow(TRUE);
    }
    if (m_iMode == RECORDING) {
        m_btnRecord.EnableWindow(FALSE);
    } else {
        m_btnRecord.EnableWindow(TRUE);
    }
}

void CRecordDlg::NewData(CWave *pWave, CWaveBlock* pBlock)
{
    ASSERT(pWave);
    // Update the VU meter from the samples
    ASSERT(pBlock);

    // get the format of the data
    WAVEFORMATEX* pwf = pWave->GetFormat();
    ASSERT(pwf->wFormatTag == WAVE_FORMAT_PCM);
    int iCount = pBlock->GetNumSamples();
    if (pwf->wBitsPerSample == 8) {
        BYTE* pData = (BYTE*)pBlock->GetSamples();
        BYTE bMax = 0;
        while (iCount--) {
            if (*pData > bMax) bMax = *pData;
            pData++;
        }
        if (bMax < 128) {
            bMax = 0;
        } else {
            bMax -= 128;
        }
        m_VU.SetValue(bMax << 8, bMax << 8);
    } else {
        // assume 16 bit samples
        ASSERT(sizeof(short int) == 2);
        short int* pData = (short int*) pBlock->GetSamples();
        int iMax = 0;
        while (iCount--) {
            if (*pData > iMax) iMax = *pData;
            pData++;
        }
        m_VU.SetValue(iMax, iMax);
    }

    // If we are just sampling, nuke the wave blocks
    if (m_iMode != RECORDING) {
        pWave->GetBlockList()->FreeAll();
    }
}

void CRecordDlg::EndPlayback(CWave *pWave)
{
    TRACE("End of playback");
    ASSERT(pWave);
    SetMode(SAMPLING);
}

void CRecordDlg::BuildFormat(WAVEFORMATEX& fmt, DWORD dwFormat)
{
    ASSERT(dwFormat);
    fmt.wFormatTag = WAVE_FORMAT_PCM;
    switch (dwFormat) {
    case WAVE_FORMAT_1M08:
        fmt.nChannels = 1;
        fmt.nSamplesPerSec = 11025;
        fmt.wBitsPerSample = 8;
        break;
    case WAVE_FORMAT_1M16:
        fmt.nChannels = 1;
        fmt.nSamplesPerSec = 11025;
        fmt.wBitsPerSample = 16;
        break;
    case WAVE_FORMAT_1S08:
        fmt.nChannels = 2;
        fmt.nSamplesPerSec = 11025;
        fmt.wBitsPerSample = 8;
        break;
    case WAVE_FORMAT_1S16:
        fmt.nChannels = 2;
        fmt.nSamplesPerSec = 11025;
        fmt.wBitsPerSample = 16;
        break;
    case WAVE_FORMAT_2M08:
        fmt.nChannels = 1;
        fmt.nSamplesPerSec = 22050;
        fmt.wBitsPerSample = 8;
        break;
    case WAVE_FORMAT_2M16:
        fmt.nChannels = 1;
        fmt.nSamplesPerSec = 22050;
        fmt.wBitsPerSample = 16;
        break;
    case WAVE_FORMAT_2S08:
        fmt.nChannels = 2;
        fmt.nSamplesPerSec = 22050;
        fmt.wBitsPerSample = 8;
        break;
    case WAVE_FORMAT_2S16:
        fmt.nChannels = 2;
        fmt.nSamplesPerSec = 22050;
        fmt.wBitsPerSample = 16;
        break;
    case WAVE_FORMAT_4M08:
        fmt.nChannels = 1;
        fmt.nSamplesPerSec = 44100;
        fmt.wBitsPerSample = 8;
        break;
    case WAVE_FORMAT_4M16:
        fmt.nChannels = 1;
        fmt.nSamplesPerSec = 44100;
        fmt.wBitsPerSample = 16;
        break;
    case WAVE_FORMAT_4S08:
        fmt.nChannels = 2;
        fmt.nSamplesPerSec = 44100;
        fmt.wBitsPerSample = 8;
        break;
    case WAVE_FORMAT_4S16:
        fmt.nChannels = 2;
        fmt.nSamplesPerSec = 44100;
        fmt.wBitsPerSample = 16;
        break;

    default:
        ASSERT(0);
        return;
    }
    fmt.nAvgBytesPerSec = fmt.nSamplesPerSec;
    fmt.nBlockAlign = fmt.wBitsPerSample / 8;
}

///////////////////////////////////////////////////////////////
// CRecDlgNotifyObj

CRecDlgNotifyObj::CRecDlgNotifyObj()
{
    m_pDlg = NULL;
}

CRecDlgNotifyObj::~CRecDlgNotifyObj()
{
}

void CRecDlgNotifyObj::NewData(CWave *pWave,
                         CWaveBlock* pBlock)
{
    ASSERT(m_pDlg);
    m_pDlg->NewData(pWave, pBlock);
}

void CRecDlgNotifyObj::EndPlayback(CWave *pWave)
{
    ASSERT(m_pDlg);
    m_pDlg->EndPlayback(pWave);
}
