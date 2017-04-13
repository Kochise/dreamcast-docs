

// --------------------------------------------------------------------------
#define TraceTag     TRACEFUNC
#define TraceError(_sz,_x)   TRACEFUNC(NULL,"ERROR: %s %08x",_sz,_x)

#define DoTagsDialog()
#define TagRegister 0;
#define RestoreDefaultDebugState()

#define tagNull      __LINE__,NULL
#define tagUI        __LINE__,"ui"        
#define tagUIOther   __LINE__,"uiother"
#define tagMouse     __LINE__,"mouse"
#define tagEngine    __LINE__,"engine"
#define tagEngineMin __LINE__,"enginemin"
#define tagForm      __LINE__,"form"
#define tagFormFunc  __LINE__,"formfunc"
#define tagFuncTriv  __LINE__,"functriv"


#define AssertSz(_x,_sz) if (!(_x)) ASSERTFUNC(_sz,__LINE__,__FILE__,#_x);
#define Assert(_x) AssertSz(_x,"assertion")
#define ASSERTDATA
#define pdebug
#define stddbgmin NULL
#define stddbg    NULL

#define NYI(_x) AssertSz(0,_x)


// --------------------------------------------------------------------------
#ifdef DEBUG
void _cdecl TRACEFUNC(int line, char * tag, char * szFmt, ...)
#ifdef DEBUG_CODE
{
    va_list valMarker;
    static char rgch[1024];
    static char szTraceNumber[32];
    static char szLineNumber[32];
    int  x,q;

    if (tag && 1 != GetPrivateProfileInt("tag",tag, 1, "c:\\trace.out")) return;

    va_start(valMarker, szFmt);
    wvsprintf(rgch, szFmt, valMarker);
    lstrcat(rgch,"                                                                                                                                                      ");
    rgch[125] = '\0';
    wsprintf(rgch + 125,"<<< (%5d) ",line);
    if (tag) lstrcat(rgch,tag);
    else lstrcat(rgch,"NULL");
    va_end(valMarker);

    if (GetPrivateProfileInt ("trace", "trace", 0, "c:\\trace.out"))
    {
        // ----- how many traces have we output

        x = GetPrivateProfileInt ("trace", "last", 0, "c:\\trace.out");
        ++x;
        wsprintf(szTraceNumber,"%d",x);
        WritePrivateProfileString ("trace", "last", szTraceNumber, "c:\\trace.out");


        // ----- cat the file

        FILE *fp;
        fp = fopen("c:\\trace.out", "a");
        if (fp)
        {
            fprintf(fp,"%s",rgch);
            fclose(fp);
        }
        else MessageBeep(0);

        // ----- debug break

        if (q=GetPrivateProfileInt ("trace", "break", 0, "c:\\trace.out"))
        {
            if (q == x || -1 == q)
                MessageBox(NULL,rgch,"TRACE TAG",MB_OK);
        }

    }
}
#else
;
#endif

void ASSERTFUNC(char *sz,int line,char *file,char* string)
#ifdef DEBUG_CODE
{
    static char rgch[1024];
    TraceTag(tagNull,"\n\nASSERTION FAILURE !!!");
    MessageBeep(0);
    wsprintf(rgch,"%s(%d) (%s)\n%s",file,line,string,sz);
    TraceTag(tagNull,rgch);
    MessageBox(NULL,rgch,"assertion failure",MB_TASKMODAL|MB_ABORTRETRYIGNORE);
}
#else
;
#endif
#ifndef IID_IPersistMessage
#ifdef _WIN32
#include <objbase.h>
#else
#include <compobj.h>
#endif
#include <mapiform.h>
#else
#pragma message("here we are now .. REFCLSID")
#endif
char *DumpCLSID(REFCLSID riid)
#ifdef DEBUG_CODE
    {
    static char ach[44];
    static char szName[256];

    szName[0] = '\0';

#ifdef _WIN32
    if      (IsEqualIID(riid, IID_IUnknown            )) lstrcpy(szName,"IID_IUnknown           ");
    else if (IsEqualIID(riid, IID_IClassFactory       )) lstrcpy(szName,"IID_IClassFactory      ");
    else if (IsEqualIID(riid, IID_IMalloc             )) lstrcpy(szName,"IID_IMalloc            ");
    else if (IsEqualIID(riid, IID_IMarshal            )) lstrcpy(szName,"IID_IMarshal           ");
    else if (IsEqualIID(riid, IID_IRpcChannel         )) lstrcpy(szName,"IID_IRpcChannel        ");
    else if (IsEqualIID(riid, IID_IRpcStub            )) lstrcpy(szName,"IID_IRpcStub           ");
    else if (IsEqualIID(riid, IID_IStubManager        )) lstrcpy(szName,"IID_IStubManager       ");
    else if (IsEqualIID(riid, IID_IRpcProxy           )) lstrcpy(szName,"IID_IRpcProxy          ");
    else if (IsEqualIID(riid, IID_IProxyManager       )) lstrcpy(szName,"IID_IProxyManager      ");
    else if (IsEqualIID(riid, IID_IPSFactory          )) lstrcpy(szName,"IID_IPSFactory         ");
    else if (IsEqualIID(riid, IID_ILockBytes          )) lstrcpy(szName,"IID_ILockBytes         ");
    else if (IsEqualIID(riid, IID_IStorage            )) lstrcpy(szName,"IID_IStorage           ");
    else if (IsEqualIID(riid, IID_IStream             )) lstrcpy(szName,"IID_IStream            ");
    else if (IsEqualIID(riid, IID_IEnumSTATSTG        )) lstrcpy(szName,"IID_IEnumSTATSTG       ");
    else if (IsEqualIID(riid, IID_IBindCtx            )) lstrcpy(szName,"IID_IBindCtx           ");
    else if (IsEqualIID(riid, IID_IMoniker            )) lstrcpy(szName,"IID_IMoniker           ");
    else if (IsEqualIID(riid, IID_IRunningObjectTable )) lstrcpy(szName,"IID_IRunningObjectTable");
    else if (IsEqualIID(riid, IID_IInternalMoniker    )) lstrcpy(szName,"IID_IInternalMoniker   ");
    else if (IsEqualIID(riid, IID_IRootStorage        )) lstrcpy(szName,"IID_IRootStorage       ");
    else if (IsEqualIID(riid, IID_IMessageFilter      )) lstrcpy(szName,"IID_IMessageFilter     ");
    else if (IsEqualIID(riid, CLSID_StdMarshal        )) lstrcpy(szName,"CLSID_StdMarshal       ");
    else if (IsEqualIID(riid, IID_IStdMarshalInfo     )) lstrcpy(szName,"IID_IStdMarshalInfo    ");
    else if (IsEqualIID(riid, IID_IExternalConnection )) lstrcpy(szName,"IID_IExternalConnection");
    else if (IsEqualIID(riid, IID_IPersistMessage     )) lstrcpy(szName,"IID_IPersistMessage    ");
    else if (IsEqualIID(riid, IID_IMAPIMessageSite    )) lstrcpy(szName,"IID_IMAPIMessageSite   ");
    else if (IsEqualIID(riid, IID_IMAPISession        )) lstrcpy(szName,"IID_IMAPISession       ");
    else if (IsEqualIID(riid, IID_IMAPIViewContext    )) lstrcpy(szName,"IID_IMAPIViewContext   ");
    else if (IsEqualIID(riid, IID_IMAPIViewAdviseSink )) lstrcpy(szName,"IID_IMAPIViewAdviseSink");
    else if (IsEqualIID(riid, IID_IMAPIFormAdviseSink )) lstrcpy(szName,"IID_IMAPIFormAdviseSink");
    else if (IsEqualIID(riid, IID_IMAPIFormInfo       )) lstrcpy(szName,"IID_IMAPIFormInfo      ");
    else if (IsEqualIID(riid, IID_IMAPIFormMgr        )) lstrcpy(szName,"IID_IMAPIFormMgr       ");
    else if (IsEqualIID(riid, IID_IMAPIFormContainer  )) lstrcpy(szName,"IID_IMAPIFormContainer ");
    else if (IsEqualIID(riid, IID_IMAPIForm           )) lstrcpy(szName,"IID_IMAPIForm          ");
    else                                                 lstrcpy(szName,"                       ");
#endif


    wsprintf(ach, "{%8.8lX-%4.4X-%4.4X-%2.2X%2.2X-%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X} %s",
        riid.Data1,
        (int)riid.Data2,
        (int)riid.Data3,
        (int)riid.Data4[0],
        (int)riid.Data4[1],
        (int)riid.Data4[2],
        (int)riid.Data4[3],
        (int)riid.Data4[4],
        (int)riid.Data4[5],
        (int)riid.Data4[6],
        (int)riid.Data4[7],
        szName);
    return ach;
    }
#else
;
#endif
#else
#define TRACEFUNC   ;/##/
//#define TRACEFUNC   
#define ASSERTFUNC(_1,_2,_3,_4)
#define DumpCLSID(_x) 0
#endif


