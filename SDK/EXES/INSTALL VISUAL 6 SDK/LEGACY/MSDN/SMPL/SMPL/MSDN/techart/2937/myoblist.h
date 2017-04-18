// myoblist.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyObList object

class CMyObList : public CObList
{
    DECLARE_SERIAL(CMyObList)
public:
    CMyObList(); 
    ~CMyObList();
    void DeleteAll();
    CMyObj* RemoveHead()
        {return (CMyObj*) CObList::RemoveHead();}
    CMyObj* GetNext(POSITION& rPos)
        {return (CMyObj*) CObList::GetNext(rPos);}
    void Append(CMyObj* pMyObj);
    BOOL Remove(CMyObj* pMyObj);                       
    virtual void Serialize(CArchive& ar); 
};
