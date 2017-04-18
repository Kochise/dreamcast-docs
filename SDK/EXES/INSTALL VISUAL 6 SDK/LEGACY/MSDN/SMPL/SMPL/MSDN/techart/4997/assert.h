//
// assert.h
//

#ifndef _INC_ASSERT
#define _INC_ASSERT


// Prototypes
#ifdef __cplusplus
extern "C"
{
#endif
    void AssertFailedLine(LPCSTR lpszFilename, int nLine);
#ifdef __cplusplus
}
#endif


// Assert macros
#ifdef _DEBUG
#define ASSERT(f) if(!(f)) AssertFailedLine(__FILE__, __LINE__)
#else
#define ASSERT(f) 
#endif

#endif // _INC_ASSERT