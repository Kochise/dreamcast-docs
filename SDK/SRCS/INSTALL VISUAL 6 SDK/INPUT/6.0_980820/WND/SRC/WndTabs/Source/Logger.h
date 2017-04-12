
#ifndef __LOGGER_H
#define __LOGGER_H

#define FN_TRACE_LEVEL 3

#define WT_TRACE(level) \
    if (g_pTheLogger->GetTraceLevel() >= level) g_pTheLogger->Output
#define WT_L1_TRACE WT_TRACE(1)
#define WT_L2_TRACE WT_TRACE(2)
#define WT_L3_TRACE WT_TRACE(3)
#define WT_L4_TRACE WT_TRACE(4)

#ifdef _DEBUG
#define WT_ASSERT ASSERT
#else
#define WT_ASSERT(f) \
    if (g_pTheLogger->GetTraceLevel() > 0  &&  (!(f))) \
        g_pTheLogger->Output("Assertion failed @%s(%d), expr: %s", THIS_FILE, __LINE__, #f);
#endif

#define WT_FN_TRACE_PARAMS_INT(name, fmt, firstparam) \
    CFunctionLogger wt_fn_log(name, fmt, (int *)firstparam);
#define WT_FN_TRACE_PARAMS(name, fmt, firstparam) \
    WT_FN_TRACE_PARAMS_INT(name, fmt, (&firstparam));
#define WT_FN_TRACE(name)  WT_FN_TRACE_PARAMS_INT(name, NULL, NULL)

#define RETURN_TYPE(val, fmt) \
    { \
        if (g_pTheLogger->GetTraceLevel() >= FN_TRACE_LEVEL) \
        { \
            wt_fn_log.m_RetVal = (void *)(val); \
            wt_fn_log.m_pszRetType = (fmt); \
        } \
        return (val); \
    }     
#define RETURN_STR(str) RETURN_TYPE((str), "%s")
#define RETURN_INT(i)   RETURN_TYPE((i),   "%d")
#define RETURN_BOOL(i)  RETURN_INT((i))


class CLogger
{
public:
    CLogger() {}
    virtual ~CLogger();

    static void UseExtrnLogger(CLogger *pExtrnLogger);

    void SetTraceLevel(int iLevel);
    void SetFileName(LPCTSTR pszFileName);

    void Output(LPCTSTR fmt, ...);

    void IncreaseIndent();
    void DecreaseIndent();

    int GetTraceLevel() { return m_iTraceLevel; }
    
protected:
    CString          m_sFileName;
    CCriticalSection m_cs;
    CFile            m_OutputFile;
    int              m_iTraceLevel;
    CString          m_sPrefix;
    CString          m_sIndent;
    int              m_iIndent;

    void OutputIt(LPCTSTR pszMsg);
    void OpenIt();
    virtual void MakeIndentString();
    virtual void OutputBasicInfo();
};

extern CLogger *g_pTheLogger;

class CFunctionLogger
{
public:
    void    *m_RetVal;
    LPCTSTR m_pszRetType;

    CFunctionLogger(LPCTSTR pszFuncName, LPCTSTR pszFmt = NULL, 
        int *pFirstParam = NULL): m_pszFuncName(pszFuncName),
        m_pszFmt(pszFmt), m_pFirstParam(pFirstParam), m_pszRetType(NULL)
    {
        if (g_pTheLogger->GetTraceLevel() >= FN_TRACE_LEVEL) 
            OutputIn();
    }
    ~CFunctionLogger()                 
    {
        if (g_pTheLogger->GetTraceLevel() >= FN_TRACE_LEVEL) 
            OutputOut();
    }

    void OutputIn();
    void OutputOut();

protected:
    LPCTSTR m_pszFuncName;
    LPCTSTR m_pszFmt;
    int*  m_pFirstParam;
};

#endif  // __LOGGER_H
