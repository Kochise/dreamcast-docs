/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.01.75 */
/* at Mon Jul 14 09:24:35 1997
 */
/* Compiler settings for FishTankLevelGetter.idl:
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

const IID IID_ILevelGetter = {0x7F0DFAA2,0xF56D,0x11D0,{0xA9,0x80,0x00,0x20,0x18,0x2A,0x70,0x50}};


const IID LIBID_FISHTANKLEVELGETTERLib = {0x7F0DFA91,0xF56D,0x11D0,{0xA9,0x80,0x00,0x20,0x18,0x2A,0x70,0x50}};


const CLSID CLSID_LevelGetter = {0x7F0DFAA3,0xF56D,0x11D0,{0xA9,0x80,0x00,0x20,0x18,0x2A,0x70,0x50}};


#ifdef __cplusplus
}
#endif

