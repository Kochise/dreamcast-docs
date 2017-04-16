/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.03.0110 */
/* at Tue Nov 25 10:32:54 1997
 */
/* Compiler settings for sspsidl.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
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

const IID IID_IByteBuffer = {0xE126F8FE,0xA7AF,0x11D0,{0xB8,0x8A,0x00,0xC0,0x4F,0xD4,0x24,0xB9}};


const IID IID_ISCardTypeConv = {0x53B6AA63,0x3F56,0x11D0,{0x91,0x6B,0x00,0xAA,0x00,0xC1,0x80,0x68}};


const IID IID_ISCardCmd = {0xD5778AE3,0x43DE,0x11D0,{0x91,0x71,0x00,0xAA,0x00,0xC1,0x80,0x68}};


#ifdef __cplusplus
}
#endif

