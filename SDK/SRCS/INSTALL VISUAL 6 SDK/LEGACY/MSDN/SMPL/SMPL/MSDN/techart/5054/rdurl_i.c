/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.01.75 */
/* at Thu Apr 03 15:34:20 1997
 */
/* Compiler settings for rdurl.idl:
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

const IID IID_IUrlReader = {0x511A6700,0x9EEE,0x11D0,{0xBD,0x88,0x00,0xA0,0xC9,0x0F,0x28,0x2F}};


const IID IID_IUrlReaderEvents = {0x723B5B11,0x9EEF,0x11d0,{0xBD,0x88,0x00,0xA0,0xC9,0x0F,0x28,0x2F}};


const IID LIBID_READURLLib = {0x511A66F3,0x9EEE,0x11D0,{0xBD,0x88,0x00,0xA0,0xC9,0x0F,0x28,0x2F}};


const IID DIID_DIUrlReaderEvents = {0x723B5B10,0x9EEF,0x11d0,{0xBD,0x88,0x00,0xA0,0xC9,0x0F,0x28,0x2F}};


const CLSID CLSID_UrlReader = {0x511A6703,0x9EEE,0x11D0,{0xBD,0x88,0x00,0xA0,0xC9,0x0F,0x28,0x2F}};


#ifdef __cplusplus
}
#endif

