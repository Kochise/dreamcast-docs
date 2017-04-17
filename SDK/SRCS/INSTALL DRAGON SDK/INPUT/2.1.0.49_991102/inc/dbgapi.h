/*++

Copyright (c) 1997-1998 Microsoft Corporation

Module Name: dbgapi.h

Purpose: Debug Message and Zone APIs.

--*/
#ifndef __DBGAPI_H__
#define __DBGAPI_H__

#ifdef __cplusplus
extern "C" {
#endif
    
void WINAPIV NKDbgPrintfW(LPWSTR lpszFmt, ...);
void WINAPI WriteDebugLED(WORD wIndex, DWORD dwPattern);

/*
@doc    EXTERNAL    KERNEL
@struct DBGPARAM | Debug zone information structure
@comm   The name of the module is used to look for zone initialization
        information in the host PC registry. Zone names are displayed by
        the control app (eg shell) which allows the user to dynamically
        set zones.
@xref   <f DEBUGREGISTER>
*/
typedef struct _DBGPARAM {
	WCHAR	lpszName[32];           // @field Name of module
	WCHAR   rglpszZones[16][32];    // @field names of zones for first 16 bits
	ULONG   ulZoneMask;             // @field Current zone Mask
} DBGPARAM, *LPDBGPARAM;

/*
@func   BOOL | DEBUGZONE | Associates a mask bit with a zone
@parm   int | bitnum | Bitnumber being defined
@rdesc  A boolean which is TRUE if bitnum in '1' else is FALSE
@ex     Example of use is |
        // associate bit 0 with an info zone
        #define ZONE_INFO   DEBUGZONE(0)
        // we can now use ZONE_INFO as a boolean for anything.
        // We'd typically use it in a DEBUGMSG ...
*/
#define DEBUGZONE(n)  (dpCurSettings.ulZoneMask&(0x00000001<<n))

#ifdef SHIP_BUILD

#define ERRORMSG(cond,printf_exp) ((void)0)
#define RETAILMSG(cond,printf_exp) ((void)0)
#define DEBUGMSG(cond,printf_exp) ((void)0)
#define DEBUGLED(cond,parms) ((void)0)
#define DBGCHK(module,exp) ((void)0)
#define DEBUGCHK(exp) ((void)0)
#define DEBUGREGISTER(hMod) ((void)0)

#else 

#ifdef DEBUG

/*
@func BOOL | DEBUGMSG | Output a debug message conditionally
@parm BOOL | cond | The condition under which the message is printed
@parm <null> | (printf_exp) | A printf style expression to be output. Must be enclosed
      in parentheses. Gets passed on to the <f NKDbgPrintf> function.
@ex   Example of use |
      DEBUGMSG(ZONE_INFO, (L"FOODLL: Entered func1. Param 1 = %d\r\n", par1));
@xref <f RETAILMSG> <tab> <f ERRORMSG> <tab> <f NKDbgPrintf>
*/
#define DEBUGMSG(cond,printf_exp)   \
   ((void)((cond)?(NKDbgPrintfW printf_exp),1:0))
#define DBGCHK(module,exp) \
   ((void)((exp)?1:(          \
       NKDbgPrintfW ( TEXT("%s: DEBUGCHK failed in file %s at line %d \r\n"), \
                 (LPWSTR)module, TEXT(__FILE__) ,__LINE__ ),    \
       DebugBreak(), \
	   0  \
   )))

/*
@func BOOL | DEBUGLED | Output a debug LED pattern conditionally
@parm BOOL | cond | The condition under which the message is printed
@parm <null> | (parms) | The parameters to be passed to the WriteDebugLED
      function.  Must me in parentheses.  First parameter is wIndex and second
      parameter is dwPattern.
@ex   Example of use |
      DEBUGLED(ZONE_INFO, (3, 0x2345);
@xref <f RETAILMSG> <tab> <f ERRORMSG> <tab> <f WriteDebugLED>
*/
#define DEBUGLED(cond,parms)   \
   ((void)((cond)?(WriteDebugLED parms),1:0))    


/*
@func BOOL | DEBUGCHK | Asserts an expression
@parm BOOL | exp | Expression to be asserted
@comm If the expression is false, this will cause a DebugBreak to be hit which
      will cause you to enter the debugger if you are running with one. It will
      also give you the line number and file name where the assert failed.
*/
#define DEBUGCHK(exp) DBGCHK(dpCurSettings.lpszName, exp)
extern  DBGPARAM    dpCurSettings;
/*
@func  BOOL | DEBUGREGISTER | Registers debug settings for a process / module
@parm  HINSTANCE | hInstance | If target is a module this is it's hInstance. If
       target is a process this should be NULL.
@comm  This simply calls through to <f RegisterDebugZones>. It assumes that
       there is a variable of name <b dpCurSettings> visible in the code.
*/
BOOL RegisterDbgZones(HMODULE hMod, LPDBGPARAM lpdbgparam);
#define DEBUGREGISTER(hMod)  RegisterDbgZones(hMod, &dpCurSettings)
#else

#define DEBUGMSG(cond,printf_exp) ((void)0)
#define DEBUGLED(cond,parms) ((void)0)
#define DBGCHK(module,exp) ((void)0)
#define DEBUGCHK(exp) ((void)0)
#define DEBUGREGISTER(hMod) ((void)0)

#endif

/*
@func BOOL | RETAILMSG | Output a message in retail builds
@parm BOOL | cond | The condition under which the message is printed
@parm <null> | (printf_exp) | A printf style expression to be output. Must be enclosed
      in parentheses. This is simply passed in to the <f NKDbgPrintf> function.
@comm This should be used in a very limited fashion since it can increase
      the size of your retail build.
@ex   Example of use |
      RETAILMSG(x==y, (L"FOODLL: Wierdness. x===y = %d\r\n", x));
@xref <f DEBUGMSG> <tab> <f ERRORMSG> <tab> <f NKDbgPrintf>
*/
#define RETAILMSG(cond,printf_exp)   \
   ((cond)?(NKDbgPrintfW printf_exp),1:0)

/*
@func BOOL | ERRORMSG | Output an error msg
@parm BOOL | cond | The condition under which the message is printed
@parm <null> | (printf_exp) | A printf style expression to be output. Must be enclosed
      in parentheses. This is passed in to the <f NKDbgPrintf> function.
@comm Very similar to <f RETAILMSG> except that this will prefix the message
      with a big bold ERROR and give the file name & line number of the error
      also.
@ex   Example of use |
      ERRORMSG(x==y, (L"FOODLL: Wierdness. x===y = %d\r\n", x));
@xref <f DEBUGMSG> <tab> <f RETAILMSG> <tab> <f NKDbgPrintf>
*/
#define ERRORMSG(cond,printf_exp)	 \
   ((cond)?(NKDbgPrintfW(TEXT("ERROR: %s line %d: "),TEXT(__FILE__),__LINE__), NKDbgPrintfW printf_exp),1:0)

#endif

/*
@func BOOL | RETAILLED | Output a LED code in retail builds
@parm BOOL | cond | The condition under which the message is printed
@parm <null> | (parms) | The parameters to be passed to the WriteDebugLED
      function.  Must me in parentheses.  First parameter is wIndex and second
      parameter is dwPattern.
@comm This should be used in a very limited fashion since it can increase
      the size of your retail build.
@ex   Example of use |
      RETAILLED(ZONE_INFO, (3, 0x2345);
@xref <f DEBUGMSG> <tab> <f ERRORMSG> <tab> <f WriteDebugLED>
*/
#define RETAILLED(cond,parms) \
   ((void)((cond)?(WriteDebugLED parms),1:0))    


// some alternate ways to get to these
#define ASSERTMSG(msg, exp) (DEBUGMSG(!exp,(msg)),DBGCHK(TEXT("Unknown"),exp))
#define ASSERT( exp )   DBGCHK(TEXT("Unknown"), exp)
#define ASSERT_IMPLIES( cond, exp ) ASSERT( !(cond) || (exp) )
#ifdef DEBUG
#define VERIFY(exp)  ASSERT(exp)
#else
#define VERIFY(exp)  ((void)(exp))
#endif

#ifdef __cplusplus
}
#endif
    
#endif

