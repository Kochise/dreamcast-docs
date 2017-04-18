/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.01.75 */
/* at Wed Jan 07 23:33:43 1998
 */
/* Compiler settings for RegPCtrs.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
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

const IID IID_IRegisterPerfmonObject = {0x0166BEA2,0x87E2,0x11D1,{0x8D,0xB5,0x20,0x4C,0x4F,0x4F,0x50,0x20}};


const IID LIBID_REGPCTRSLib = {0x0166BE95,0x87E2,0x11D1,{0x8D,0xB5,0x20,0x4C,0x4F,0x4F,0x50,0x20}};


const CLSID CLSID_RegisterPerfmonObject = {0x8F2BBC80,0x1257,0x11D1,{0x9F,0x91,0x40,0x00,0x04,0x49,0x13,0x41}};


#ifdef __cplusplus
}
#endif

