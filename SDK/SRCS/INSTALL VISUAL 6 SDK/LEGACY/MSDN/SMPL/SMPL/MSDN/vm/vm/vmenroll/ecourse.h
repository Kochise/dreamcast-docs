// ECourse.h
//

#if !defined(ECourse_h)
#define ECourse_h

#include "stdafx.h"


class CString;
class ESection;
class CCourseSet;
class EAdministrator;
class EStudent;
class EProfessor;

//##ModelId=349062240217
class ECourse
{
public:
    //##ModelId=34909EAD007E
    CString m_CourseID;

    //##ModelId=34909EE203BA
    CString m_CourseTitle;

    //##ModelId=34909EFB0243
    int m_Hours;

    //##ModelId=3490AE4C0010
    CCourseSet* theCCourseSet;

    //##ModelId=3490624B020A
    EAdministrator* theschedules;

    //##ModelId=349062E401FF
    EStudent* theattends;

    //##ModelId=3490630E007A
    EProfessor* thelectures;

protected:

private:

};

#endif /* ECourse_h */
