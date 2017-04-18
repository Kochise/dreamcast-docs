/*
 *  Network Library
 *  Copyright (c) 1999 SEGA
 *
 *  Library : Network Utility Library
 *  File    : nt_utl.h
 *  Date    :
 *  Version : 3.00
 *
 *  For Network SDK
 *
 */

/*
 *  return value
 */
#define NTD_OK                  (  0)
#define NTD_ERR_NOTINIT         ( -1)
#define NTD_ERR_INVALIDPARAM    ( -2)
#define NTD_ERR_NOINFO          ( -3)
/*
 * bit definition for flag in NetworkInfo
 */
#define ISP_USE1        0x00000000  /* Use ISP 1 information */
#define ISP_USE2        0x00000001  /* Use ISP 2 information */
#define CHANGE_NUMBER   0x00000000  /* When the line is busy, change the number */
#define FIXED_NUMBER    0x00000002  /* The phone number is fixed. */
/* for modem setting */
#define DIAL_TONE       0x00000000  /* Tone dialing */
#define DIAL_PULSE      0x00000100  /* Pulse dialing */
#define PULSE_US_10     0x00000000  /* Pulse speed 10pps (US) */
#define PULSE_UK_10     0x00000200  /* Pulse speed 10pps (UK) */
#define PULSE_US_20     0x00000400  /* Pulse speed 20pps (US) */
#define PULSE_UK_20     0x00000600  /* Pulse speed 20pps (UK) */
#define SPEAKER_VOL_L0  0x00000000  /* Speaker volume is low */
#define SPEAKER_VOL_L1  0x00000800  /* Speaker volume is low */
#define SPEAKER_VOL_L2  0x00001000  /* Speaker volume is medium */
#define SPEAKER_VOL_L3  0x00001800  /* Speaker volume is high */
#define SPEAKER_CTL_M0  0x00000000  /* Speaker always OFF */
#define SPEAKER_CTL_M1  0x00002000  /* Speaker ON from start of dialing until receiving carrier */
#define SPEAKER_CTL_M2  0x00004000  /* Speaker always ON */
#define SPEAKER_CTL_M3  0x00006000  /* Speaker OFF from end of dialing until receiving carrier */
#define BLIND_ENABLE    0x00008000  /* Enable Blind call (default: disabled) */

/* flag for NetworkInfo2; The following flags are newly added */
#define USE_LAN     0x00000004  /* Use LAN information in lan_info */
#define VERSION_2   0x01000000  /* Version of NetworkInfo */

/* flag for NetworkAccessInfo */
#define USE_EXTRA_INFO      0x0001  /* Use NetworkAccessInfo2 additionally */

/* flag for NetworkAccessInfo2 */
#define NA2_USE_MAIL1      0x00000001
#define NA2_USE_MAIL2      0x00000002
#define NA2_USE_MAIL3      0x00000004
#define NA2_USE_MAIL4      0x00000008
#define NA2_PROXY_OFF      0x00000010
#define NA2_FIXED_ADDRESS  0x00000020

/* flag for TCPIPInfo */
#define TCP_USE_DNS        0x00000001
#define TCP_FIXED_ADDRESS  0x00000002
#define TCP_USE_PROXY      0x00000004
#define TCP_USE_SOCKS      0x00000008

/* magic for NetworkAccessInfo, NetworkAccessInfo2, TCPIPInfo
             and NetworkCommonInfo */
#define NETINFO_MAGIC      0x41474553  /* magic number ("SEGA") */

/*
 * Structures
 */
struct in_addr {
    union {
        struct { unsigned char s_b1, s_b2, s_b3, s_b4; } S_un_b;
        struct { unsigned short s_w1, s_w2; } S_un_w;
        unsigned long S_addr;
    } S_un;
#define s_addr  S_un.S_addr     /* should be used for all code */
#define s_host  S_un.S_un_b.s_b2    /* OBSOLETE: host on imp */
#define s_net   S_un.S_un_b.s_b1    /* OBSOLETE: network */
#define s_imp   S_un.S_un_w.s_w2    /* OBSOLETE: imp */
#define s_impno S_un.S_un_b.s_b4    /* OBSOLETE: imp # */
#define s_lh    S_un.S_un_b.s_b3    /* OBSOLETE: logical host */
};




typedef struct _NetworkAccessInfo {
    Uint32          magic;      /* magic number, should be 0x41474553("SEGA") */
    Uint8           loginId[28];
    Uint8           loginPasswd[16];
    Uint8           accessPointNumber[3][40];
    struct in_addr  dnsServerAddress1;
    struct in_addr  dnsServerAddress2;
    Uint8           mailAddress[48];
    Uint8           mailServer[32];
    Uint8           popServer[32];
    Uint8           popId[16];
    Uint8           popPasswd[16];
    Uint8           proxyServer[32];
    Uint16          proxyPortNum;
#ifdef OLD_NETWORKACCESSINFO
    Uint16          reserve;    /* should be 0x0000 */
#else
    Uint16          flag;
#endif
} NetworkAccessInfo;

typedef struct _MailAccount {
    Uint8           mailAddress[48];
    Uint8           mailServer[32];
    Uint8           popServer[32];
    Uint8           popId[16];
    Uint8           popPasswd[16];
} MailAccount;

typedef struct _NetworkAccessInfo2 {

    Uint32          magic;
    Uint32          flag;
    struct in_addr  ipAddr;
    Uint8           parentalPasswd[12];
    MailAccount     mailAccount[4];

} NetworkAccessInfo2;

typedef struct _TCPIPInfo {
    Uint32          magic;
    Uint32          flag;
    struct in_addr  ipAddr;
    struct in_addr  subnetMask;
    struct in_addr  broadcast;
    struct in_addr  dnsServerAddress1;
    struct in_addr  dnsServerAddress2;
    struct in_addr  gateway1;
    struct in_addr  gateway2;
    Uint8           host[32];
    Uint8           domain[64];
    Uint8           mailAddress[140];
    Uint8           mailServer[64];
    Uint8           popServer[64];
    Uint8           popId[32];
    Uint8           popPasswd[32];
    Uint8           proxyServer[64];
    Uint16          proxyPortNum;
    Uint8           socksServer[64];
    Uint16          socksPortNum;
    Uint32          reserved;
} TCPIPInfo;

typedef struct _NetworkCommonInfo {
    Uint32          magic;
    Uint32          flag;       /* should be 0x00000000 */
    Uint8           url[52];
} NetworkCommonInfo;

typedef struct _NetworkInfo {
    Uint32          flag;
    NetworkAccessInfo    isp_info1;
    NetworkAccessInfo    isp_info2;
    Uint32          reserve;
} NetworkInfo;

typedef struct _NetworkInfo2 {
    Uint32              flag;       /* Highest Byte means version of this structure */
    NetworkAccessInfo   isp_info1;
    NetworkAccessInfo   isp_info2;
    Uint32              reserve;
    NetworkAccessInfo2  ext_info1;
    NetworkAccessInfo2  ext_info2;
    TCPIPInfo           lan_info;
    NetworkCommonInfo   comm_info;
} NetworkInfo2;

/*
 * prototypes
 */

#ifdef __cplusplus /* Support for C++ */
extern "C" {
#endif /* __cplusplus */

void   ntUtlSetBrowserData(Sint16 page);
void   ntUtlSetGameData(Sint16 data);
Sint16 ntUtlGetGameData(void);

Sint32 ntInfInit(void *pNetInfo, void *pWork);
Sint32 ntInfExit(void);
Sint32 ntInfIsNetworkInfo(void);
Sint32 ntInfGetNetworkInfo(NetworkInfo **ppNetInfo);
Sint32 ntInfGetNetworkAccessInfo(Sint32 isp, NetworkAccessInfo **ppNetAccInfo);
Sint32 ntInfGetFlag(Uint32 *fFlag);
Sint32 ntInfGetLoginId(Sint32 isp, Uint8 *pLoginId);
Sint32 ntInfGetLoginPasswd(Sint32 isp, Uint8 *pLoginPasswd);
Sint32 ntInfGetAccessPointNumber(Sint32 isp, Uint8 *pAccessPointNumber);
Sint32 ntInfGetDnsServerAddress(Sint32 isp, struct in_addr *pDns1, struct in_addr *pDns2);
Sint32 ntInfGetMailAddress(Sint32 isp, Uint8 *pMailAddress);
Sint32 ntInfGetMailServer(Sint32 isp, Uint8 *pMailServer);
Sint32 ntInfGetPopServer(Sint32 isp, Uint8 *pPopServer);
Sint32 ntInfGetPopId(Sint32 isp, Uint8 *pPopId);
Sint32 ntInfGetPopPasswd(Sint32 isp, Uint8 *pPopPasswd);
Sint32 ntInfGetProxyServer(Sint32 isp, Uint8 *pProxyServer);
Sint32 ntInfGetProxyPortNum(Sint32 isp, Uint16 *pPort);

/* ext */
Sint32 ntInfInit2(void *pNetInfo, void *pWork);
Sint32 ntInfGetNetworkInfo2(NetworkInfo2 **ppNetInfo);
Sint32 ntInfGetMailAddress2(Sint32 isp, Sint32 account, Uint8 *pMailAddress, Sint32 size);
Sint32 ntInfGetMailServer2(Sint32 isp, Sint32 account, Uint8 *pMailServer, Sint32 size);
Sint32 ntInfGetPopServer2(Sint32 isp, Sint32 account, Uint8 *pPopServer, Sint32 size);
Sint32 ntInfGetPopId2(Sint32 isp, Sint32 account, Uint8 *pPopId, Sint32 size);
Sint32 ntInfGetPopPasswd2(Sint32 isp, Sint32 account, Uint8 *pPopPasswd, Sint32 size);
Sint32 ntInfGetProxyServer2(Sint32 isp, Uint8 *pProxyServer, Sint32 size);

Sint32 ntInfGetNetworkAccessInfoFlag(Sint32 isp, Uint16 *pFlag);
Sint32 ntInfGetNetworkAccessInfo2(Sint32 isp, NetworkAccessInfo2 **ppNetAccInfo2);
Sint32 ntInfGetTCPIPInfo(TCPIPInfo **ppTCPIPInfo);
Sint32 ntInfGetNetworkAccessInfo2Flag(Sint32 isp, Uint32 *pFlag);
Sint32 ntInfGetIPAddr(Sint32 isp, struct in_addr *IPAddr);
Sint32 ntInfGetParentalPasswd(Uint32 isp, Uint8 *pPasswd);
Sint32 ntInfGetMailAccount(Uint32 isp, Uint32 account, MailAccount **ppMailAcct);
Sint32 ntInfGetTCPIPInfoFlag(Uint32 *pFlag);
Sint32 ntInfGetSubnetMask(struct in_addr *pSubnetMask);
Sint32 ntInfGetBroadcast(struct in_addr *pBroadcast);
Sint32 ntInfGetGateway(struct in_addr *pGw1, struct in_addr *pGw2);
Sint32 ntInfGetHost(Uint8 *pHost);
Sint32 ntInfGetDomain(Uint8 *pDomain);
Sint32 ntInfGetSocksServer(Uint8 *pSocksServer);
Sint32 ntInfGetSocksPortNum(Uint16 *pSocksPortNum);

Sint32 ntInfGetISP(Sint32 *isp);
Sint32 ntInfGetURL(Uint8 *pURL);

#ifdef __cplusplus
} /* End of extern "C" { */
#endif /* __cplusplus */
