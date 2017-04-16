//
// PerfIds.c
//

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IPerfmonObject = {0x3DBD6FB0,0xFFA7,0x11d0,{0x9F,0x8C,0x40,0x00,0x04,0x49,0x13,0x41}};


const IID IID_IPerfmonCounter = {0x3DBD6FB1,0xFFA7,0x11d0,{0x9F,0x8C,0x40,0x00,0x04,0x49,0x13,0x41}};

#ifdef __cplusplus
}
#endif