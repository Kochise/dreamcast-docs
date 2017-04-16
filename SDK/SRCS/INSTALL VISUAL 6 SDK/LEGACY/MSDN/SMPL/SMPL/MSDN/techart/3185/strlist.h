// strlist.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStrList document

class CStrList : public CPtrList
{
    DECLARE_SERIAL(CStrList)
public:
    CStrList(); 
    virtual ~CStrList();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
    void DeleteAll();
    CString* RemoveHead() {return (CString*) CPtrList::RemoveHead();}
    CString* GetNext(POSITION& pos) {return (CString*) CPtrList::GetNext(pos);}
};

