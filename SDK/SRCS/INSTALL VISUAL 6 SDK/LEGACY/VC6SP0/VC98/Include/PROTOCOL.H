#ifndef __brloader_protocol_h
#define __brloader_protocol_h

typedef BYTE ETHERNET_ADDRESS [6];

typedef struct ETHERNET_FRAME {
	ETHERNET_ADDRESS	Destination;
	ETHERNET_ADDRESS	Source;
	WORD				FrameType;			// in host-order
} ETHERNET_FRAME;

#define	ETHERNET_FRAME_TYPE_IP		0x0800

typedef struct IP_HEADER {
    BYTE    x;
    BYTE    tos;
    WORD    length;
    WORD    identifier;
#define IP_MF 0x2000
    WORD    fragment;
    BYTE    ttl;
    BYTE    protocol;
    WORD    cksum;
    DWORD   src;
    DWORD   dest;
} IP_HEADER;
typedef IP_HEADER * LPIPHEADER;

#define	IP_HEADER_MINIMUM_LEN	20

typedef struct UDP_HEADER {
	WORD	src_port;
	WORD	dest_port;
	WORD	length;			// including this header
	WORD	checksum;
} UDP_HEADER;

#define	UDP_HEADER_LEN			8

#endif // __brloader__protocol_h