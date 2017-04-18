#ifndef _NETINFO_H_
#define _NETINFO_H_

#include <winsock.h>

/*----------------------------------------------------------------------------*/
/* constants for fmMng functions                                              */
/*----------------------------------------------------------------------------*/
#define NETWORK_INFO_START      192
#define PACKET_NUMBER           12
#define NETWORK_INFO_END        (NETWORK_INFO_START + PACKET_NUMBER - 1)
/*----------------------------------------------------------------------------*/
/* bit definition for flag in NetworkInfo                                     */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* Structures                                                                 */
/*----------------------------------------------------------------------------*/
#ifndef _WINSOCKAPI_
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
#endif

typedef struct _NetworkAccessInfo {
    unsigned long   magic;      /* magic number, should be 0x41474553("SEGA") */
    char            loginId[28];
    char            loginPasswd[16];
    char            accessPointNumber[3][40];
    struct in_addr  dnsServerAddress1;
    struct in_addr  dnsServerAddress2;
    char            mailAddress[48];
    char            mailServer[32];
    char            popServer[32];
    char            popId[16];
    char            popPasswd[16];
    char            proxyServer[32];
    unsigned short  proxyPortNum;
    unsigned short  reserve;    /* should be 0x0000 */
} NetworkAccessInfo;

typedef struct _NetworkInfo {
    unsigned long   flag;
    NetworkAccessInfo    isp_info1;
    NetworkAccessInfo    isp_info2;
    unsigned long   reserve;
} NetworkInfo;

#endif
