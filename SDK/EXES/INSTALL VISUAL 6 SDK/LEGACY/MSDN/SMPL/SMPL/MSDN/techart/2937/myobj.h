// myobj.h : interface of the CMyObject class
//
/////////////////////////////////////////////////////////////////////////////

class CMyObj : public CObject
{
public:
    DECLARE_SERIAL(CMyObj)
    CMyObj();
    ~CMyObj();
    virtual void Serialize(CArchive& ar); 

    const CString& GetText()
        {return m_strText;}
    void SetText(CString& str)
        {m_strText = str;}
    int DoEditDialog();

private:
    CString m_strText;
};

/////////////////////////////////////////////////////////////////////////////
