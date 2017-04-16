/* sna_cnst.h */

/*****************************************************************************/
/* Constants for use by IHV's via sna_dlc.h or by internal builds via        */
/* direct #include                                                           */
/*****************************************************************************/

#ifndef SNA_CNSTH_INCLUDED
#define SNA_CNSTH_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/* Routine to get value of a configuration parameter                         */
/*****************************************************************************/
#ifdef WIN32_SUPPORT
  USHORT WINAPI SNAGetPerfValues(int * pPerfObject, int * pFirstCounter);
  USHORT WINAPI SNAGetPNodePerfVals(int * pPerfObject, int * pFirstCounter);
  #ifdef OLD_IHV_PROTOS
    USHORT WINAPI sepdgetcf(UCHAR *, VOID *, ULONG, UCHAR, ULONG *);
  #else
    USHORT WINAPI SNAGetConfigValue(UCHAR *, VOID *, ULONG, UCHAR, ULONG *);
  #endif

#else
  USHORT far sepdgetcf(UCHAR far *, VOID far *, ULONG, UCHAR, ULONG far *);
#endif

#define TYPELONG '\000'
#define TYPESTRING '\001'

#define ERBADCFG  1
#define ERNOTFND  2
#define ERTOOLONG 3
#define ERBADTYPE 4

/*****************************************************************************/
/* Structure of version information block                                    */
/*****************************************************************************/

struct cs_info {
  unsigned short    length;            /* length of this struct (bytes)      */
                                       /* (supplied parameter)               */
  unsigned char     major_ver;         /* CS major ver CS1.1->1, CS2.0->2    */
  unsigned char     minor_ver;         /* CS minor ver CS1.1->10 (dec)       */
  unsigned char     config_share[80];  /* name of share point of current     */
                                       /* config file = default location for */
                                       /* style file \\box\share\ (null      */
                                       /* terminated)                        */
  unsigned short    nos;               /* NOS that the LAN is running        */
#define Workstation 0
#define LANMan      1      /* Also LAN Server, unless we can differentiate   */
#define NetWare     2
} CS_INFO;

/*****************************************************************************/
/* Routine to get version information                                        */
/*****************************************************************************/
#ifdef WIN32_SUPPORT

  #ifdef OLD_IHV_PROTOS
    USHORT WINAPI sepdgetinfo(struct cs_info * );
  #else
    USHORT WINAPI SNAGetSystemInfo(struct cs_info * );
  #endif

#else
  USHORT far sepdgetinfo(struct cs_info far * );
#endif

/*****************************************************************************/
/* Routine to return the name of the SNALink                                 */
/*****************************************************************************/
#ifdef WIN32_SUPPORT

  #ifdef OLD_IHV_PROTOS
    VOID WINAPI sepdlknm(UCHAR *);
  #else
    VOID WINAPI SNAGetLinkName(UCHAR *);
  #endif

#else
  VOID far sepdlknm(UCHAR far *);
#endif

/*****************************************************************************/
/* Routine to send a message to the local node                               */
/*****************************************************************************/
#ifdef WIN32_SUPPORT

  #ifdef OLD_IHV_PROTOS
    extern VOID WINAPI sbpgsend(PTRBFHDR *);
  #else
    extern VOID WINAPI SNASendMessage(PTRBFHDR *);
  #endif

#else
  extern VOID     far  sbpgsend(PTRBFHDR *);
#endif

/*****************************************************************************/
/* Routine to send an NMVT Alert to NetView                                  */
/*****************************************************************************/
#ifdef WIN32_SUPPORT

  #ifdef OLD_IHV_PROTOS
    extern VOID WINAPI sbpgnmvt(PTRBFHDR, INTEGER);
  #else
    extern VOID WINAPI SNASendAlert(PTRBFHDR, INTEGER);
  #endif

#else
  extern VOID     far  sbpgnmvt(PTRBFHDR, INTEGER);
#endif

/*****************************************************************************/
/* Function prototypes for routines which must be supplied by IHV DLL        */
/*****************************************************************************/
#ifdef WIN32_SUPPORT

  #ifdef OLD_IHV_PROTOS
    VOID WINAPI slpginit(HANDLE);
    VOID WINAPI slpgdisp(PTRBFHDR, INTEGER, INTEGER);
    VOID WINAPI slpwrkmg();
  #else
    VOID WINAPI SNALinkInitialize(HANDLE);
    VOID WINAPI SNALinkDispatchProc(PTRBFHDR, INTEGER, INTEGER);
    VOID WINAPI SNALinkWorkProc();
  #endif

#else
  VOID     far  slpginit(HSEM);
  VOID     far  slpgdisp(PTRBFHDR, INTEGER, INTEGER);
  VOID     far  slpwrkmg();
#endif

/*****************************************************************************/
/* Constants used by slpgdisp                                                */
/*****************************************************************************/
#define SBTICK 253
#define SBLOST 254

#ifdef __cplusplus
}
#endif

#endif
