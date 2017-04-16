// rectls.h : header file
//
// CrectList class
// This is a type safe version of CObList for CRect objects
// It is mostly a set of inline casts
//

#ifndef __RECTLS__
#define __RECTLS__

class CRectList : private CObList
{
public:
    CRectList();
    ~CRectList();
    void RemoveAll();
    CRect *GetNext(POSITION &pos)
        {return (CRect *) CObList::GetNext(pos);}
    POSITION GetHeadPosition() const
        {return CObList::GetHeadPosition();}
    void Add(CRect *pRect);
    void Merge();
};

#endif // __RECTLS__
