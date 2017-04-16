
// (C) Copyright 1996, Microsoft Corporation and it suppliers.

//----------------------------------------------------------------------------
// Public header for COM-marshaling facilities provided by MSJava.dll
//----------------------------------------------------------------------------

#ifndef _NATIVCOM_
#define _NATIVCOM_


#include <windows.h>
#include <native.h>


#ifdef __cplusplus
extern "C" {
#endif


//----------------------------------------------------------------------------
// COM data wrapper helpers...
//----------------------------------------------------------------------------
void* __cdecl jcdwNewData(Hjava_lang_Object * phJCDW, unsigned int numBytes);
void* __cdecl jcdwGetData(Hjava_lang_Object * phJCDW);
unsigned int __cdecl jcdwSizeOf(Hjava_lang_Object * phJCDW);
unsigned int __cdecl jcdwClassSizeOf(Hjava_lang_Object * phJavaClass);
unsigned int __cdecl jcdwOffsetOf(Hjava_lang_Object * phJCDW, const char *pFieldName);
unsigned int __cdecl jcdwClassOffsetOf(Hjava_lang_Object * phJCDWClass, const char *pFieldName);
Hjava_lang_Object * __cdecl convert_IUnknown_to_Java_Object(IUnknown *punk,
                                                            Hjava_lang_Object *phJavaClass,
                                                            int       fAssumeThreadSafe);
Hjava_lang_Object * __cdecl convert_IUnknown_to_Java_Object2(IUnknown    *punk,
                                                             ClassClass  *pClassClass,
                                                             int         fFreeThreaded);

IUnknown * __cdecl convert_Java_Object_to_IUnknown(Hjava_lang_Object *phJavaObject, const IID *pIID);


Hjava_lang_Object * __cdecl convert_ptr_to_jcdw(void              *pExtData,
                                                Hjava_lang_Object *phJavaClass
                                                );

int __cdecl jcdw_memory_freed_on_gc(Hjava_lang_Object *phJCDW);


int   __cdecl jcdwSetData(Hjava_lang_Object * phJCDW, LPVOID pv);
int   __cdecl jcdw_java_owned(Hjava_lang_Object *phJCDW);




//----------------------------------------------------------------------------
// Map HRESULT to ComException.
//----------------------------------------------------------------------------
void    __cdecl SignalErrorHResult(HRESULT theHRESULT);

//----------------------------------------------------------------------------
// Map Java exception to HRESULT.
//----------------------------------------------------------------------------
HRESULT __cdecl HResultFromException(OBJECT* exception_object);



typedef Hjava_lang_Object *JAVAARG;

//----------------------------------------------------------------------------
// Information structure for Java->COM Custom Method hook.
//----------------------------------------------------------------------------
typedef struct {
    DWORD                   cbSize;         // size of structure in bytes
    IUnknown               *punk;           // pointer to interface being invoked
    const volatile JAVAARG *pJavaArgs;      // pointer to Java argument stack
} J2CMethodHookInfo;

//----------------------------------------------------------------------------
// Information structure for COM->Java Custom Method hook.
//----------------------------------------------------------------------------
typedef struct {
    DWORD                      cbSize;         // size of structure in bytes
    struct methodblock        *javaMethod;     // java method to call
    LPVOID                     pComArgs;       // pointer to COM method argument stack
    const volatile JAVAARG    *ppThis;         // pointer to pointer to Java this

    // Store the COM result here.
    union {
        HRESULT                         resHR;
        DWORD                           resDWORD;
        double                          resDouble;
    };
} C2JMethodHookInfo;


    

#ifdef __cplusplus
}
#endif



#endif _NATIVCOM_



