/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    StkList.hpp

Abstract:

    Class declarations for Stack and SmartArray Template classes

-------------------------------------------------------------------*/

template <class TYPE, int nSizeDelta> class CSmartArray {
private:
    int  m_nCurSize;
    TYPE *m_pData;

public:
    CSmartArray()
    {
        m_nCurSize = nSizeDelta;
        m_pData = (TYPE*)malloc(nSizeDelta*sizeof(TYPE));
#ifdef DEBUG
        if (m_pData == NULL)
            DebugBreak();
#endif
    };
    ~CSmartArray()
    {
        // TODO: freeing causes error
        // free(m_pData);
    };
    TYPE &operator[](int nIndex)
    {
        if (nIndex >= m_nCurSize)
        {
            // realloc the space
            m_nCurSize = nIndex + nSizeDelta;
            m_pData = (TYPE*)realloc(m_pData, m_nCurSize*sizeof(TYPE));
#ifdef DEBUG
            if (m_pData == NULL)
                DebugBreak();
#endif
        }
        return m_pData[nIndex];
    };
    TYPE *Data()
    {
        return m_pData;
    };
    void Remove(int nIndex)
    {
        memcpy(&m_pData[nIndex], &m_pData[nIndex+1], (m_nCurSize-nIndex-1)*sizeof(TYPE));
        m_nCurSize--;
    };
    
    // Warning: This function would be slow if used with large TYPE variables.
    int FindIndex(TYPE data)
    {
        int i;
        for (i = 0; i < m_nCurSize; i++)
            if (memcmp(&m_pData[i], &data, sizeof(TYPE)))
                return i;
        return -1;
    };
}; 

// Template Stack class
template <class TYPE> class CStack 
{
private:
    CSmartArray<TYPE, 1> m_array;
    int m_nTop;

public:
    CStack()
    {
        m_nTop = -1;
    };
    void Push(TYPE element)
    {
        m_nTop++;
        m_array[m_nTop] = element;
    };
    TYPE Pop()
    {
        if (m_nTop < 0)
            return (TYPE) 0;
        return m_array[m_nTop--];
    };
    TYPE GetTop()
    {
        if (m_nTop < 0)
            return (TYPE) 0;
        return m_array[m_nTop];
    };
};
