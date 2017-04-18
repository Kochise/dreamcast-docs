// splsno.h : header file
//
// CSpriteListNotifyObj class
//
// This is a class derived from CSpriteNotifyObj which is used in 
// CSpriteList to handle notification calls from CSprite objects.
//

#ifndef __SPLSNO__
#define __SPLSNO__

#include "spriteno.h"
class CSpriteList;

class CSpriteListNotifyObj : public CSpriteNotifyObj
{
public:
    CSpriteListNotifyObj();
    ~CSpriteListNotifyObj();
    void SetList(CSpriteList *pList)
        {m_pList = pList;}
    void Change(CSprite *pSprite,
                CHANGETYPE change,
                LPVOID p1 = NULL,
                LPVOID p2 = NULL);
    void AttachDoc(CDocument *pDoc)
        {m_pDoc = pDoc;}

protected:
    CSpriteList *m_pList;
    CDocument *m_pDoc;
};

#endif // __SPLSNO__
