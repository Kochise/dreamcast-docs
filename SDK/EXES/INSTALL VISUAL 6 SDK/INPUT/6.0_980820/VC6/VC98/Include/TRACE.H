/* trace.h */

/*
 * (C) Copyright Microsoft Corporation 1991-1993.
 * All Rights Reserved.
 */

#if (defined(WIN32_SUPPORT) || defined(MSWIN_SUPPORT))
 #ifndef DONT_INCLUDE_MEMORY_H
  #include <memory.h>
 #endif
#endif

#ifdef ASYNCTRACE
#include <dbgtrace.h>
#endif	

#ifdef WIN32_SUPPORT
#define sepudcpy(X,Y,Z) memcpy(X,Y,Z)
#endif

#ifdef DOS_SUPPORT
extern int _cdecl far com_sprintf( char far *, const char far *, ... );
#define SPRINTF(x)  com_sprintf x;
#else
 #if (defined(WIN32_SUPPORT) || defined(MSWIN_SUPPORT))
  /***************************************************************************/
  /* Temporary for Win32: in Win32 DLLs in PDK2, sprintf is not available:   */
  /* use wsprintf instead.                                                   */
  /***************************************************************************/
  #define SPRINTF(x)  wsprintf x;
 #else
  #define SPRINTF(x)  sprintf x;
 #endif
#endif

/*****************************************************************************/
/* Comm Server Critical Section macros.                                      */
/*****************************************************************************/
#ifdef WIN32_SUPPORT
 typedef struct cscritsec
 {
   BOOL             Inited;
   CRITICAL_SECTION CritSec;
 } CSCRITSEC;


 #define CSENTERCRITSEC(x) if (!((x)->Inited))                                \
                             {                                                \
                               InitializeCriticalSection(&((x)->CritSec));    \
                               (x)->Inited = TRUE;                            \
                             }                                                \
                           EnterCriticalSection(&((x)->CritSec))

 #define CSEXITCRITSEC(x)  LeaveCriticalSection(&((x)->CritSec))

 #define CSLEAVECRITSEC(x)  LeaveCriticalSection(&((x)->CritSec))
#endif

/*****************************************************************************/
/* Global flags and variables                                                */
/*****************************************************************************/
#ifdef MSWIN_SUPPORT
#define com_str com_logstr
#endif

#ifdef WIN32_SUPPORT
 extern CSCRITSEC crit_comlog;
 extern CSCRITSEC crit_dlbtrc;
 extern CSCRITSEC crit_dlblog;
 extern UCHAR com_str[256];
 extern UCHAR com_logstr[256];
#else
 #ifndef MSWIN_SUPPORT
  extern ULONG  pascal com_trcsem;
  extern ULONG  pascal com_logsem;
  extern ULONG  pascal dlb_logsem;
  extern ULONG  pascal dlb_trcsem;
  extern UCHAR  pascal com_str[256];
 #endif
#endif
#ifndef WIN32_SUPPORT
extern UCHAR pascal com_logstr[256];
#endif

/*****************************************************************************/
/* TRACEn macro definitions                                                  */
/*****************************************************************************/
#ifdef NOTRC
#define TRCLVL  20
#else
#   ifndef TRCLVL
#define TRCLVL  0
#   endif
#endif

#ifdef WIN32_SUPPORT                                                   /*NTRC*/

	#if  (!defined(ASYNCTRACE) || defined(NOTRC) )
		#if TRCLVL < 3                                                        /*NTRC*/
		#define TRACE2() TRACEX(2,(com_mod,  (const UCHAR *)                                /*NTRC*/
		#else                                                                 /*NTRC*/
		#define TRACE2() TRACEZ((                                            /*NTRC*/
		#endif                                                                /*NTRC*/
		#if TRCLVL < 5                                                        /*NTRC*/
		#define TRACE4() TRACEX(4,(com_mod,  (const UCHAR *)                                /*NTRC*/
		#else                                                                 /*NTRC*/
		#define TRACE4() TRACEZ((                                            /*NTRC*/
		#endif                                                                /*NTRC*/
		#if TRCLVL < 7                                                        /*NTRC*/
		#define TRACE6() TRACEX(6,(com_mod,   (const UCHAR *)                               /*NTRC*/
		#else                                                                 /*NTRC*/
		#define TRACE6() TRACEZ((                                            /*NTRC*/
		#endif                                                                /*NTRC*/
		#if TRCLVL < 9                                                        /*NTRC*/
		#define TRACE8() TRACEX(8,(com_mod,   (const UCHAR *)                               /*NTRC*/
		#else                                                                 /*NTRC*/
		#define TRACE8() TRACEZ((                                            /*NTRC*/
		#endif                                                                /*NTRC*/
		#if TRCLVL < 11                                                       /*NTRC*/
		#define TRACE10() TRACEX(10,(com_mod,   (const UCHAR *)                             /*NTRC*/
		#else                                                                 /*NTRC*/
		#define TRACE10() TRACEZ((                                           /*NTRC*/
		#endif                                                                /*NTRC*/
		#if TRCLVL < 13                                                       /*NTRC*/
		#define TRACE12() TRACEX(12,(com_mod,   (const UCHAR *)                             /*NTRC*/
		#else                                                                 /*NTRC*/
		#define TRACE12() TRACEZ((                                           /*NTRC*/
		#endif                                                                /*NTRC*/
		#if TRCLVL < 17                                                       /*NTRC*/
		#define TRACE16() TRACEX(16,(com_mod,  (const UCHAR *)                           /*NTRC*/
		#else                                                                 /*NTRC*/
		#define TRACE16() TRACEZ((                                           /*NTRC*/
		#endif                                                                /*NTRC*/

	#else
		#define TRACE2() DEBUGTRACEX(((long)NULL, (const char *)
		#define TRACE4() DEBUGTRACEX(((long)NULL, (const char *)
		
		#define TRACE6()  ERRORTRACEX(((long)NULL, (const char *)
		#define TRACE8()  ERRORTRACEX(((long)NULL, (const char *)
		#define TRACE10() ERRORTRACEX(((long)NULL, (const char *)
	
		#define TRACE12() FATALTRACEX(((long)NULL, (const char *)
		#define TRACE16() FATALTRACEX(((long)NULL, (const char *)

		#define DEBUGTRACEX(x)		DebugTrace x
		#define ERRORTRACEX(x)		ErrorTrace x
		#define FATALTRACEX(x)		FatalTrace x


		#define TRACET(y)                                                                                                                \
			        if (y >= ptrc->intlvl) { SYSTEMTIME st;                  \
								             GetSystemTime(&st);                              \
											 SPRINTF((Time_Msg,"Time %2.2hu:%2.2hu.%2.2hu",   \
											 st.wMinute,                              \
											 st.wSecond,                              \
											(st.wMilliseconds/10)));                 \
											 DebugTrace(NULL, Time_Msg);			\
										   }		
	
		#define COM_ENTRY(x) DWORD rc = 0;												\
			                 DWORD rc2 = 0;												\
							 TraceQuietEnter(x)
	#endif





#else                                                                  /*NTRC*/
 #if TRCLVL < 3
  #define TRACE2() TRACEX(2,(com_str,
 #else                                                                 /*NTRC*/
  #define TRACE2() TRACEZ((
 #endif
 #if TRCLVL < 5
  #define TRACE4() TRACEX(4,(com_str,
 #else
  #define TRACE4() TRACEZ((
 #endif
 #if TRCLVL < 7
  #define TRACE6() TRACEX(6,(com_str,
 #else
  #define TRACE6() TRACEZ((
 #endif
 #if TRCLVL < 9
  #define TRACE8() TRACEX(8,(com_str,
 #else
  #define TRACE8() TRACEZ((
 #endif
 #if TRCLVL < 11
  #define TRACE10() TRACEX(10,(com_str,
 #else
  #define TRACE10() TRACEZ((
 #endif
 #if TRCLVL < 13
  #define TRACE12() TRACEX(12,(com_str,
 #else
  #define TRACE12() TRACEZ((
 #endif
 #if TRCLVL < 17
  #define TRACE16() TRACEX(16,(com_str,
 #else
  #define TRACE16() TRACEZ((
 #endif
#endif                                                                 /*NTRC*/

#if TRCLVL < 20
 #ifdef DOS_SUPPORT
  #define TRACEX(w,x)                                                         \
                    if (ptrc && (w >= ptrc->intlvl)) {                        \
                      if (ptrc->nocat)                                        \
                        CMDSemRequest(&com_trcsem,10000);                     \
                      SPRINTF(x);                                             \
                      seputrc(w,com_mod);                                     \
                    }
 #else
  #ifdef MSWIN_SUPPORT
   #define TRACEX(w,x)                                                        \
                      if (ptrc && (w >= ptrc->intlvl)) {                      \
                        SPRINTF(x);                                           \
                        seputrc(w,com_mod,ptrc, com_str);                     \
                      }
  #else
   #ifdef WIN32_SUPPORT
	
    #define TRACEX(w,x) if (w >= ptrc->intlvl) InternalTrace x;        /*NTRC*/
   #else
     #define TRACEX(w,x)                                                       \
                    if (ptrc && (w >= ptrc->intlvl)) {                        \
                      DosSemRequest(&dlb_trcsem,10000L);                      \
                      SPRINTF(x);                                             \
                      seputrc_w(com_str,w,com_mod);                           \
                      DosSemClear(&dlb_trcsem);                               \
                    }
   #endif
  #endif
 #endif
#else
 #define TRACEX(w,x)
#endif
#define TRACEZ(x)

#if TRCLVL < 20
 #ifdef DOS_SUPPORT
  #define COM_ENTRY(x) UCHAR com_mod[6];                                      \
                       sepudcpy(com_mod,x,6)
 #else
  #ifdef WIN32_SUPPORT
	#ifndef ASYNCTRACE
		#define COM_ENTRY(x) DWORD rc = 0;										\
		                     DWORD rc2 = 0;                                     \
	                         UCHAR com_mod[6];                                  \
		                     sepudcpy(com_mod,x,6)
	#else
		#define COM_ENTRY(x) DWORD rc = 0;                                      \
			                 DWORD rc2 = 0;										\
							 TraceQuietEnter(x)
	#endif
 
  #else
   #define COM_ENTRY(x) USHORT rc = 0;                                        \
                        UCHAR com_mod[6];                                     \
                        sepudcpy(com_mod,x,6)
  #endif
 #endif
#else
 #ifdef DOS_SUPPORT
  #define COM_ENTRY(x)
 #else
  #ifdef WIN32_SUPPORT
	#ifndef ASYNCTRACE
		#define COM_ENTRY(x) DWORD rc = 0; DWORD rc2=0
	#else
		#define COM_ENTRY(x) DWORD rc = 0;                                      \
			                 DWORD rc2 = 0;										\
							 TraceQuietEnter(x)
	#endif
  #else
   #define COM_ENTRY(x) USHORT rc = 0;
  #endif
 #endif
#endif

#define COM_QUIT goto com_exit
#define COM_EXIT com_exit:
#define COM_EXIT_RC com_exit: return(rc)

typedef struct trc {
  USHORT    flags;                   /*0140* Make trace flags 2 bytes        */
#define      DLCMSGS   0x0001        /* NODE TRACE CONTROL                   */
#define      PVIMSGS   0x0002
#define      FMIMSGS   0x0004
#define      OTHMSGS   0x0008
#define      NODEMSGS  0x000F        /* All node messages to be traced       */
#define      SNAMSGS   0x0010        /* User wants DLC as SNA msgs           */
#define      NOSNATRC  0x0020        /* SNA tracing not permitted            */

#define      CPICMSGS  0x0040        /* CPIC messages                        */
#define      LUAMSGS   0x0080        /* LUA/RUI trace control                */
#define      HLLMSGS   0x0100        /* API trace control                    */
#define      SRPIMSGS  0x0200
#define      CSVMSGS   0x0400
#define      APPCMSGS  0x0800
#define      APIMSGS   0x0FC0        /*LUA* 0x0F00 -> 0x0F80 due to LUA flag */
                                     /*CPIC*0x0f80 -> 0x0fc0 due to CPIC flag*/

#define      LINKMSGS  0x1000        /* Link trace control                   */
#define      NOTRACE   0x2000        /* API tracing not permitted            */

#define      ADSTOP    0x4000        /* Stop/Dump options                    */
#define      ADDUMP    0x8000
  UCHAR     audlvl;                  /* Logging level                        */
  USHORT    control;                 /* permission for user to control       */
  USHORT    intlvl;                  /* Internal trace level                 */
  USHORT    nocat;                   /* message concatenation flag           */
  USHORT    apiinit;                 /* api tracing initialised              */
  USHORT    asyinit;                 /* special asynch initialisation flag   */
  USHORT    errinit;
  USHORT    intinit;
  USHORT    snainit;
#if ( defined(WIN32_SUPPORT) || defined(MSWIN_SUPPORT) )
  HANDLE    apihand1;                /* handles for various trace files      */
  HANDLE    apihand2;
  HANDLE    audhand;
  HANDLE    errhand;
  HANDLE    inthand1;
  HANDLE    inthand2;
  HANDLE    snahand1;
  HANDLE    snahand2;
#else
  HFILE     apihand1;                /* handles for various trace files      */
  HFILE     apihand2;
  HFILE     audhand;
  HFILE     errhand;
  HFILE     inthand1;
  HFILE     inthand2;
  HFILE     snahand1;
  HFILE     snahand2;
#endif
} TRC;

#ifndef WIN32_SUPPORT
extern TRC FAR * pascal ptrc;
#else
extern TRC FAR * ptrc;
#endif


/*****************************************************************************/
/* COM_LOGn macro definitions                                                */
/*****************************************************************************/
#define COM_LOG6(x)  COM_LOG(6,x,(com_logstr,
#define COM_LOG8(x)  COM_LOG(8,x,(com_logstr,
#define COM_LOG10(x) COM_LOG(10,x,(com_logstr,
#define COM_LOG12(x) COM_LOG(12,x,(com_logstr,
#define COM_LOG16(x) COM_LOG(16,x,(com_logstr,

#define COM_MSG6(x)  COM_MSG(6,x)
#define COM_MSG8(x)  COM_MSG(8,x)
#define COM_MSG10(x) COM_MSG(10,x)
#define COM_MSG12(x) COM_MSG(12,x)
#define COM_MSG16(x) COM_MSG(16,x)

#define COM_ERR6(x)  COM_LOG(6,x,(com_logstr,"%d",ret))
#define COM_ERR8(x)  COM_LOG(8,x,(com_logstr,"%d",ret))
#define COM_ERR10(x) COM_LOG(10,x,(com_logstr,"%d",ret))
#define COM_ERR12(x) COM_LOG(12,x,(com_logstr,"%d",ret))
#define COM_ERR16(x) COM_LOG(16,x,(com_logstr,"%d",ret))

#ifdef DOS_SUPPORT
 #define COM_LOG(v,w,x)                                                       \
                    if (v >= ptrc->audlvl) {                                  \
                      CMDSemRequest(&com_logsem,10000);                       \
                      SPRINTF(x);                                             \
                      sepulog(v,w);                                           \
                    }
#else
 #ifdef MSWIN_SUPPORT
  #define COM_LOG(v,w,x)                                                      \
                        if (v >= ptrc->audlvl) {                              \
                          SPRINTF(x);                                         \
                          sepulog(v,w,ptrc, com_logstr);                      \
                        }
 #else
  #ifndef WIN32_SUPPORT
   #define COM_LOG(v,w,x)                                                     \
                       if (v >= ptrc->audlvl) {                               \
                         DosSemRequest(&dlb_logsem,10000L);                   \
                         SPRINTF(x);                                          \
                         sepulog_w(com_logstr,v,w);                           \
                         DosSemClear(&dlb_logsem);                            \
                       }
  #else
   #define COM_LOG(v,w,x)                                                     \
                       if (v >= ptrc->audlvl) {                               \
                         CSENTERCRITSEC(&crit_dlblog);                        \
                         SPRINTF(x);                                          \
                         sepulog_w(com_logstr,v,w);                           \
                         CSEXITCRITSEC(&crit_dlblog);                         \
                       }
  #endif
 #endif
 #ifdef WIN32_SUPPORT
  #define COM_MSG(v,w)                                                        \
                      if (v >= ptrc->audlvl) {                                \
                        CSENTERCRITSEC(&crit_dlblog);                         \
                        sepulog_w(com_logstr,v,w);                            \
                        CSEXITCRITSEC(&crit_dlblog);                          \
                      }
 #else
  #define COM_MSG(v,w)                                                        \
                      if (v >= ptrc->audlvl) {                                \
                        DosSemRequest(&dlb_logsem,10000L);                    \
                        sepulog_w(com_logstr,v,w);                            \
                        DosSemClear(&dlb_logsem);                             \
                      }
 #endif
/* Parameters are message #, target m/c                                      */
 #define COM_ALERT(x,y) COM_ALERTX(x,y,(com_logstr,
 #ifdef WIN32_SUPPORT
  #define COM_ALERTX(x,y,z)                                                   \
                      {                                                       \
                        CSENTERCRITSEC(&crit_comlog);                         \
                        SPRINTF(z);                                           \
                        sepualrt(x,y,com_logstr,&crit_comlog);                \
                      }
 #else
  #define COM_ALERTX(x,y,z)                                                   \
                      {                                                       \
                        DosSemRequest(&com_logsem,10000L);                    \
                        SPRINTF(z);                                           \
                        sepualrt(x,y,com_logstr,&com_logsem);                 \
                      }
 #endif
#endif
#define COM_ERROR(x) COM_LOG(16,x,(com_logstr,"%d",rc));                      \
                     rc = x

#define COM_TRC_SNA(x)

/*****************************************************************************/
/* Add a new macro to allow components which don't log though the DMOD (eg   */
/* Print Server) to decide whether or not a message should be logged.        */
/*****************************************************************************/
#define COM_LOG_CHECK(v,x)                                                  \
                    if (v >= ptrc->audlvl)                                  \
                    {                                                       \
                      x = TRUE;                                             \
                    }                                                       \
                    else                                                    \
                    {                                                       \
                      x = FALSE;                                            \
                    }                                                       \

/*****************************************************************************/
/* Trace macros for LUA/RUI/SLI tracing.                                     */
/*****************************************************************************/
#define INIT            0     /* Initial function for link services     */
#define REQUEST         1
#define RESPONSE        2
#define POST            3

#if (defined(DOS_SUPPORT) || defined(MSWIN_SUPPORT))
extern VOID FAR pascal seputrlu(USHORT, UCHAR FAR *, TRC FAR *);

#define COM_TRC_LUA(x,y)                                                \
                    if (ptrc && (ptrc->flags & LUAMSGS)) {              \
                      seputrlu(x,y,ptrc);                               \
                    }
#else
 #ifdef WIN32_SUPPORT
   extern VOID WINAPI seputrlu(USHORT, UCHAR *);
 #else
   extern VOID FAR PASCAL seputrlu(USHORT, UCHAR FAR *);
 #endif

#define COM_TRC_LUA(x,y)                                                \
                    if (ptrc->flags & LUAMSGS) {                        \
                      seputrlu(x,y);                                    \
                    }


#endif

/*****************************************************************************/
/* Defines for IHV tracing macros                                            */
/*****************************************************************************/
#ifdef WIN32_SUPPORT
extern VOID WINAPI seputrhv(UCHAR *);
extern VOID WINAPI sepdtrci(TRC **);

#define COM_TRC_IHV(x)                                                  \
                    if (ptrc->flags & LINKMSGS) {                       \
                      seputrhv(x);                                      \
                    }
#ifdef ASYNCTRACE
	#define INITIALIZE_TRACING InitAsyncTraceEx(" ")
#else
	#define INITIALIZE_TRACING sepdtrci(&ptrc)
#endif

#endif

/*****************************************************************************/
/* Defines for Log messages                                                  */
/*****************************************************************************/
#define LOG_ALERT_REJ   392                     /* alert was rejected        */
#define LOG_SESS_START  442                     /* user logged on            */
#define LOG_SESS_END    443                     /* user logged off           */
#define LOG_SESS_FAIL   444                     /* session lost              */
#define LOG_EMUL_START  445                     /* emulation started         */
#define LOG_EMUL_END    446                     /* emulation ended           */

/*****************************************************************************/
/* Function prototypes                                                       */
/*****************************************************************************/
#ifdef MSWIN_SUPPORT
extern VOID pascal FAR seputrc(USHORT, UCHAR FAR *, TRC far *, UCHAR FAR *);
extern VOID pascal FAR sepulog(USHORT, USHORT, TRC far *, UCHAR FAR *);

#define sepudcpy(x,y,z) _fmemcpy(x,y,z)

#else
 #ifdef WIN32_SUPPORT
  extern VOID  WINAPI seputrc(USHORT, UCHAR FAR *);
  extern VOID  WINAPI seputrc_w(UCHAR FAR *, USHORT, UCHAR FAR *);
  extern VOID  WINAPI sepulog(USHORT, USHORT);
  extern VOID  WINAPI sepulog_w(UCHAR FAR *,USHORT, USHORT);
  /***************************************************************************/
  /* New internal trace function                                        *NTRC*/
  /***************************************************************************/
  extern VOID InternalTrace( UCHAR * ModName, const UCHAR * FormatText, ...);
 #else
  extern USHORT APIENTRY sepudcpy(UCHAR FAR *, UCHAR FAR *, unsigned short);
  extern VOID   APIENTRY seputrc(USHORT, UCHAR FAR *);
  extern VOID   APIENTRY seputrc_w(UCHAR FAR *, USHORT, UCHAR FAR *);
  extern VOID   APIENTRY sepulog(USHORT, USHORT);
  extern VOID   APIENTRY sepulog_w(UCHAR FAR *,USHORT, USHORT);
 #endif
#endif
#ifdef WIN32_SUPPORT
extern VOID  WINAPI sepualrt(USHORT, UCHAR *, UCHAR *, CSCRITSEC *);
#else
#ifdef MSWIN_SUPPORT
extern VOID pascal FAR sepualrt(USHORT, UCHAR FAR *, UCHAR FAR *, ULONG FAR *);
#else
extern VOID APIENTRY sepualrt(USHORT, UCHAR FAR *, UCHAR FAR *, ULONG FAR *);
#endif
#endif
/* End of file trace.h */

