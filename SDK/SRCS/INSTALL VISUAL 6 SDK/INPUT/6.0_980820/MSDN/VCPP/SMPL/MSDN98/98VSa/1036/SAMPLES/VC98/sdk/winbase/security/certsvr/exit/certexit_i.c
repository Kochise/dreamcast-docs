/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:25:12 1998
 */
/* Compiler settings for certexit.idl:
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

const IID IID_ICertExit = {0xe19ae1a0,0x7364,0x11d0,{0x88,0x16,0x00,0xa0,0xc9,0x03,0xb8,0x3c}};


const IID LIBID_CERTEXITLib = {0xe1f81810,0x7364,0x11d0,{0x88,0x16,0x00,0xa0,0xc9,0x03,0xb8,0x3c}};


const CLSID CLSID_CCertExit = {0xc9e6e410,0x7364,0x11d0,{0x88,0x16,0x00,0xa0,0xc9,0x03,0xb8,0x3c}};


#ifdef __cplusplus
}
#endif

