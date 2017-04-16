// ESection.h
//

#if !defined(ESection_h)
#define ESection_h

#include "stdafx.h"


class CString;
class CSectionSet;

//##ModelId=34909F5D0226
class ESection
{
public:
    //##ModelId=34909F7001BF
    CString m_CourseID;

    //##ModelId=34909F87033F
    CString m_SectionNo;

    //##ModelId=34909FB202A0
    CString m_InstructorID;

    //##ModelId=34909FDE0181
    CString m_Schedule;

    //##ModelId=3490A9AD02A4
    CString m_RoomNo;

    //##ModelId=3490A9C003D8
    int m_Capacity;

    //##ModelId=3490AB5D0223
    CSectionSet* theCSectionSet;

protected:

private:

};

#endif /* ESection_h */
