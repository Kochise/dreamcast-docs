#ifndef __brloader_packet_h
#define __brloader_packet_h

#include <assert.h>

#define	PACKET_ADDRESS_MAX	16

struct PACKET_BUFFER;

typedef void (*PACKET_COMPLETION_FUNC) (struct PACKET_BUFFER *, DWORD);

#define	PACKET_COMPLETE_SUCCESS		0x0000
#define	PACKET_COMPLETE_FAILURE		0x0001		// unspecified error
#define	PACKET_COMPLETE_OVERFLOW	0x0002
#define	PACKET_COMPLETE_NO_ROUTE	0x0003

typedef struct PACKET_BUFFER {
	LPBYTE	Data;		// storage for packet data
	DWORD	Start;		// where the data begins
	DWORD	End;		// where the data ends
	DWORD	Max;		// the physical length of Data
	DWORD	Context;

	// I hate to put this here, but I hate to put it elsewhere even more.
	WORD	Protocol;
	WORD	AddressLength;
	BYTE	Address		[PACKET_ADDRESS_MAX];
	PACKET_COMPLETION_FUNC	CompletionFunc;
} PACKET_BUFFER;

// this is the protocol argument for msbdnOutputSendPacket
#define	PACKET_BUFFER_PROTOCOL_IP			0x0000
#define	PACKET_BUFFER_PROTOCOL_VBI_RAW		0x0001
#define	PACKET_BUFFER_PROTOCOL_DSS_ARP		0x0002
#define	PACKET_BUFFER_PROTOCOL_DSS_RAW		0x0003
#define	PACKET_BUFFER_PROTOCOL_DSS_MPT		0x0004

// PACKET_BUFFER_PROTOCOL_IP
// packet body is a full IP packet, including header and body
// IP address should be extracted from the message body
// address field is not used

// PACKET_BUFFER_PROTOCOL_DSS_RAW
// the address field is not used
// the packet length must be 130 bytes.
// the packet is a standard DSS frame: 3 bytes of header
// and 127 bytes of payload

// PACKET_BUFFER_PROTOCOL_DSS_MPT
// the address field may or may not be specified
// the address field is the sub-SCID ID
// if the address is not specified, the output driver should build the
// sub-SCID like an Ethernet MAC address.  this only works for multicast packets,
// which have a fixed, deterministic IP address to MAC address mapping.
// if the address field exists (length is not zero), then the
// address length must be 6 and the address must contain an MPT sub-SCID ID.

static __inline void PacketBufferComplete (PACKET_BUFFER * packet, DWORD status) {
	assert (packet);
	if (packet -> CompletionFunc)
		(*packet -> CompletionFunc) (packet, status);
}

#endif // __brloader_packet_h