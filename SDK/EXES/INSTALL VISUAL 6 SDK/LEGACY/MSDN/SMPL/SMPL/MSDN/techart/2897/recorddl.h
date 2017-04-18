// recorddl.h : header file
//

class CRecordDlg;
class CRecDlgNotifyObj : public CWaveNotifyObj
{
public:
    CRecDlgNotifyObj();
    ~CRecDlgNotifyObj();
    void Attach(CRecordDlg* pDlg)
        {m_pDlg = pDlg;}


    virtual void NewData(CWave *pWave,
                         CWaveBlock* pBlock);
    virtual void EndPlayback(CWave *pWave);
    CRecordDlg* m_pDlg;
};

/////////////////////////////////////////////////////////////////////////////
// CRecordDlg dialog

class CRecordDlg : public CDialog
{
// Construction
public:
    CRecordDlg(CWnd* pParent = NULL);   // standard constructor
    ~CRecordDlg();
    void NewData(CWave *pWave, CWaveBlock* pBlock);
    void EndPlayback(CWave *pWave);

// Dialog Data
    //{{AFX_DATA(CRecordDlg)
    enum { IDD = IDD_RECORDDLG };
    CComboBox   m_cbSource;
    CComboBox   m_cbFormat;
    CStatic m_wndFrame;
    CButton m_btnPause;
    CButton m_btnPlay;
    CButton m_btnRecord;
    CButton m_btnOK;
    CButton m_btnStop;
    CString m_strFormat;
    CString m_strSource;
    //}}AFX_DATA
public:
    CWave* m_pWave;

// Implementation
private:
    enum MODE {
        IDLE,
        SAMPLING,
        PLAYING,
        RECORDING
    };

    CVUMeter m_VU;          // VU Meter
    int m_iNumDevs;         // number of input devices
    WAVEINCAPS* m_pDevCaps; // ptr to caps list
    CWaveInDevice m_InDev;  // Wave input device
    CWave m_SampleWave;     // sample wave
    CRecDlgNotifyObj m_NotifyObj;
    int m_iMode;            // current mode

    void FillDeviceList();
    void FillFormatList();
    void SetMode(MODE m);
    void BuildFormat(PCMWAVEFORMAT& fmt, DWORD dwFormat);


protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(CRecordDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangeFormat();
    afx_msg void OnClickedPlay();
    afx_msg void OnClickedRecord();
    afx_msg void OnClickedStop();
    afx_msg void OnSelchangeSource();
    virtual void OnCancel();
    virtual void OnOK();
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

