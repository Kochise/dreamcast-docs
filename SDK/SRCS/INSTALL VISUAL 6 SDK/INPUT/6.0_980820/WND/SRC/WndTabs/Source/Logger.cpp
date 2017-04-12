
#include "stdafx.h"
#include "Logger.h"

CLogger theLogger;
CLogger *g_pTheLogger = &theLogger;


CLogger::~CLogger()
{
    Output("End.\n");
}

void CLogger::SetFileName(LPCTSTR pszFileName)
{
    CSingleLock(&m_cs, TRUE);
    m_sFileName = pszFileName;
    if (GetTraceLevel()) OpenIt();
}

void CLogger::OpenIt()
{
    CFileException e;
    if (m_OutputFile.Open(m_sFileName, CFile::modeCreate | CFile::modeWrite |
        CFile::shareDenyWrite, &e) == 0)
    {
        m_OutputFile.m_hFile = NULL;
        m_iTraceLevel = 0;
    }
    else
    {
        OutputBasicInfo();
    }
}

void CLogger::SetTraceLevel(int iLevel) 
{ 
    CSingleLock(&m_cs, TRUE);
    m_iTraceLevel = iLevel; 
    if (m_sPrefix.IsEmpty())
    {
        m_sPrefix = CString('[') + AfxGetAppName() + CString("] ");
    }
    if (iLevel  &&  m_OutputFile.m_hFile == NULL  &&  !m_sFileName.IsEmpty())
    {
        OpenIt();
    }
}

void CLogger::Output(LPCTSTR fmt, ...)
{
    CSingleLock(&m_cs, TRUE);

    if (GetTraceLevel() == 0) return;
    ASSERT(m_OutputFile.m_hFile != NULL);

    char buf[2048];
    va_list args;
    va_start(args, fmt);
    _vsntprintf((char *)buf, sizeof(buf), fmt, args);
    va_end(args);
    OutputIt(buf);
}

void CLogger::OutputIt(LPCTSTR pszMsg)
{
    static bool bIsNewLine = true;    
    size_t pos = 0;
#ifdef _DEBUG
    char buf[1024];
#endif
    TRY
    {
        for (;;)
        {
            if (bIsNewLine)
            {
                m_OutputFile.Write((const void *)m_sIndent, 
                    m_sIndent.GetLength());
#ifdef DEBUG    
                OutputDebugString(m_sPrefix);
                OutputDebugString(m_sIndent);
#endif
                bIsNewLine = false;
            }
            
            pos = 0;
            for (;;)
            {
                if (pszMsg[pos] == '\0')
                {
                    break;                    
                }
                if (pszMsg[pos] == '\n')
                {
                    bIsNewLine = true;
                    pos++;
                    break;
                }
                ++pos;
            }
            
            m_OutputFile.Write((const void *)pszMsg, pos);
#ifdef _DEBUG
            strncpy(buf, pszMsg, pos);
            buf[pos] = '\0';
            OutputDebugString(buf);
#endif
            if (pszMsg[pos] == '\0')
                break;
            pszMsg += pos;
            ++pos;
        }
    }
    CATCH_ALL(e)
    {
    }
    END_CATCH_ALL
}

void CLogger::OutputBasicInfo()
{
    // OS Detection
    CString         CStr1, CStr2;
    OSVERSIONINFO   osvi;

    CStr1.Format("%s Log File\n%s\n\n", AfxGetAppName(), 
        CTime::GetCurrentTime().Format("%#c"));
    OutputIt(CStr1);

    osvi.dwOSVersionInfoSize = sizeof(osvi);
    GetVersionEx(&osvi);

    CStr1.Format("Running on Windows %s %d.%d %s\n", 
        (char *)((osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)? "NT" : "9x"),
        osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.szCSDVersion);
    OutputIt(CStr1);


    // Memory sizes
    MEMORYSTATUS ms;
    const int megabyte = 1024 * 1024;

	memset (&ms, sizeof (MEMORYSTATUS), 0);
	ms.dwLength = sizeof (MEMORYSTATUS);
	GlobalMemoryStatus (&ms);

    CStr1.Format(
        "Total RAM: %dMB, free: %dMB, virtual free: %dMB, load=%d%%\n",
        (ms.dwTotalPhys / megabyte),
        (ms.dwAvailPhys / megabyte),
        (ms.dwAvailVirtual / megabyte),
        ms.dwMemoryLoad);
    OutputIt(CStr1);

    // Screen Size
	HDC hDC = ::GetDC(NULL);
    CStr1.Format("Screen resolution: %dx%d@%dbpp\n",
        ::GetSystemMetrics(SM_CXSCREEN),
	    ::GetSystemMetrics(SM_CYSCREEN),
        ::GetDeviceCaps(hDC, BITSPIXEL));
	::ReleaseDC(NULL, hDC);
    OutputIt(CStr1);
}
    

void CLogger::UseExtrnLogger(CLogger *pExtrnLogger)
{
    g_pTheLogger = pExtrnLogger;
}

void CLogger::IncreaseIndent()
{
    CSingleLock(&m_cs, TRUE);
    ++m_iIndent;
    MakeIndentString();
}

void CLogger::DecreaseIndent()
{
    CSingleLock(&m_cs, TRUE);
    ASSERT(m_iIndent > 0);
    --m_iIndent;
    MakeIndentString();
}

void CLogger::MakeIndentString()
{
    m_sIndent.Empty();
    if (!m_iIndent) return;
    for (int i = m_iIndent; i; --i)
    {
        m_sIndent += '.';
    }
    m_sIndent += ' ';
}

void CFunctionLogger::OutputIn()
{
    CString sOut;
    sOut.Format("Enter %s(", m_pszFuncName);
    if (m_pszFmt)
    {
        char buf[2048];
        va_list args;
        va_start(args, (*m_pFirstParam));
        args -= _INTSIZEOF((*m_pFirstParam)); // x86 hack!
        _vsntprintf((char *)buf, sizeof(buf), m_pszFmt, args);
        va_end(args);
        sOut += buf;
    }
    sOut += ")\n";
    g_pTheLogger->Output(sOut);
    g_pTheLogger->IncreaseIndent();
}

void CFunctionLogger::OutputOut()
{
    CString sOut;
    g_pTheLogger->DecreaseIndent();
    sOut.Format("Exit %s()", m_pszFuncName);
    if (m_pszRetType)
    {
        CString cStr;
        sOut += " = ";
        cStr.Format(m_pszRetType, (char *)m_RetVal);
        sOut += cStr;
    }
    sOut += "\n";
    g_pTheLogger->Output(sOut);
}
