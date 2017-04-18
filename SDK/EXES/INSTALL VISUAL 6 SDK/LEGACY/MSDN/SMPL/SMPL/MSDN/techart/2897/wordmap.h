// spritlst.h : header file
//
// CSpriteList class
//

class CWordMap : private CMapStringToOb
{
    DECLARE_SERIAL(CWordMap)
public:
    CWordMap();
    ~CWordMap();
    virtual void Serialize(CArchive& ar);
    BOOL Add(const char* pszWord, CWave* pWave);
    BOOL Remove(const char *pszWord);
    CWave* Find(const char* pszWord);
    POSITION GetStartPosition();
    void GetNextAssoc(POSITION& rPos, CString& rKey,CWave*& rWave); 
    void DeleteAll();
};
