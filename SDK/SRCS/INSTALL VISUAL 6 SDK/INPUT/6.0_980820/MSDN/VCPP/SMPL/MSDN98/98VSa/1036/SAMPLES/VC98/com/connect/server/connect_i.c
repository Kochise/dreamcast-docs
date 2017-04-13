/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.03.0110 */
/* at Wed Feb 11 11:48:29 1998
 */
/* Compiler settings for Connect.idl:
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

const IID IID_IRandom = {0xCCE84211,0xDB31,0x11CF,{0x9D,0x75,0x00,0xA0,0xC9,0x03,0x91,0xD3}};


const IID IID_IRandomEvent = {0xCCE84212,0xDB31,0x11CF,{0x9D,0x75,0x00,0xA0,0xC9,0x03,0x91,0xD3}};


const IID LIBID_CONNECTLib = {0xCCE8420F,0xDB31,0x11CF,{0x9D,0x75,0x00,0xA0,0xC9,0x03,0x91,0xD3}};


const CLSID CLSID_CoRandom = {0xCCE84215,0xDB31,0x11CF,{0x9D,0x75,0x00,0xA0,0xC9,0x03,0x91,0xD3}};


#ifdef __cplusplus
}
#endif

