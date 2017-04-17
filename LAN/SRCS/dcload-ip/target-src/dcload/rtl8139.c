#include "packet.h"
#include "net.h"
#include "rtl8139.h"
#include "dcload.h"

static rtl_status_t rtl;

// Defined below
extern adapter_t adapter_bba;

/* 8, 16, and 32 bit access to the PCI I/O space (configured by GAPS) */
static vuc * const nic8 = REGC(0xa1001700);
static vus * const nic16 = REGS(0xa1001700);
static vul * const nic32 = REGL(0xa1001700);

/* 8, 16, and 32 bit access to the PCI MEMMAP space (configured by GAPS) */
static vuc * const mem8 = REGC(0xa1840000);
static vus * const mem16 = REGS(0xa1840000);
static vul * const mem32 = REGL(0xa1840000);

static int bb_detect()
{
    const char *str = (char*)REGC(0xa1001400);
    if (!memcmp(str, "GAPSPCI_BRIDGE_2", 16))
	return 0;
    else
	return -1;
}

static void rtl_init()
{
    unsigned int tmp;
    
    /* Soft-reset the chip */
    nic8[RT_CHIPCMD] = RT_CMD_RESET;
    
    /* Wait for it to come back */
    while (nic8[RT_CHIPCMD] & RT_CMD_RESET);
    
    /* Reset CONFIG1 */
    nic8[RT_CONFIG1] = 0;
    
    /* Enable auto-negotiation and restart that process */
    nic16[RT_MII_BMCR/2] = 0x9200;

    /* Do another reset */
    nic8[RT_CHIPCMD] = RT_CMD_RESET;
    
    /* Wait for it to come back */
    while (nic8[RT_CHIPCMD] & RT_CMD_RESET);

    /* Enable writing to the config registers */
    nic8[RT_CFG9346] = 0xc0;
    
    /* Read MAC address */
    tmp = nic32[RT_IDR0];
    rtl.mac[0] = tmp & 0xff;
    rtl.mac[1] = (tmp >> 8) & 0xff;
    rtl.mac[2] = (tmp >> 16) & 0xff;
    rtl.mac[3] = (tmp >> 24) & 0xff;
    tmp = nic32[RT_IDR0+1];
    rtl.mac[4] = tmp & 0xff;
    rtl.mac[5] = (tmp >> 8) & 0xff;
    memcpy(adapter_bba.mac, rtl.mac, 6);
    
    /* Enable receive and transmit functions */
    nic8[RT_CHIPCMD] = RT_CMD_RX_ENABLE | RT_CMD_TX_ENABLE;
    
    /* Set Rx FIFO threashold to 16 bytes, Rx size to 16k+16, 1024 byte DMA burst */
    nic32[RT_RXCONFIG/4] = 0x00000e00;

    /* Set Tx 1024 byte DMA burst */
    nic32[RT_TXCONFIG/4] = 00000600;
    
    /* Turn off lan-wake and set the driver-loaded bit */
    nic8[RT_CONFIG1] = (nic8[RT_CONFIG1] & ~0x30) | 0x20;
    
    /* Enable FIFO auto-clear */
    nic8[RT_CONFIG4] |= 0x80;
    
    /* Switch back to normal operation mode */
    nic8[RT_CFG9346] = 0;
    
    /* Setup Rx and Tx buffers */
    nic32[RT_RXBUF/4] = 0x01840000;
    nic32[RT_TXADDR0/4 + 0] = 0x01846000;
    nic32[RT_TXADDR0/4 + 1] = 0x01846800;
    nic32[RT_TXADDR0/4 + 2] = 0x01847000;
    nic32[RT_TXADDR0/4 + 3] = 0x01847800;
    
    /* Reset RXMISSED counter */
    nic32[RT_RXMISSED/4] = 0;
    
    /* Enable receiving broadcast and physical match packets */
    nic32[RT_RXCONFIG/4] |= 0x0000000a;
    
    /* Filter out all multicast packets */
    nic32[RT_MAR0/4 + 0] = 0;
    nic32[RT_MAR0/4 + 1] = 0;
    
    /* Disable all multi-interrupts */
    nic16[RT_MULTIINTR/2] = 0;
    
    /* clear all interrupts */
    nic16[RT_INTRSTATUS/2] = 0xffff;

    /* Enable RX/TX once more */
    nic8[RT_CHIPCMD] = RT_CMD_RX_ENABLE | RT_CMD_TX_ENABLE;
    
    /* Initialize status vars */
    rtl.cur_tx = 0;
    rtl.cur_rx = 0;
}

static int bb_init() 
{
    vuc * const g28 = REGC(0xa1000000);
    vus * const g216 = REGS(0xa1000000);
    vul * const g232 = REGL(0xa1000000);
    
    int i;
    unsigned int tmp;
        
    /* Initialize the "GAPS" PCI glue controller.
       It ain't pretty but it works. */
    g232[0x1418/4] = 0x5a14a501;		/* M */
    i = 10000;
    while (!(g232[0x1418/4] & 1) && i > 0)
	i--;
    if (!(g232[0x1418/4] & 1)) {
	return -1;
    }
    g232[0x1420/4] = 0x01000000;
    g232[0x1424/4] = 0x01000000;
    g232[0x1428/4] = 0x01840000;		/* DMA Base */
    g232[0x142c/4] = 0x01840000 + 32*1024;	/* DMA End */
    g232[0x1414/4] = 0x00000001;
    g232[0x1434/4] = 0x00000001;
    
    /* Configure PCI bridge (very very hacky). If we wanted to be proper,
       we ought to implement a full PCI subsystem. In this case that is
       ridiculous for accessing a single card that will probably never
       change. Considering that the DC is now out of production officially,
       there is a VERY good chance it will never change. */
    g216[0x1606/2] = 0xf900;
    g232[0x1630/4] = 0x00000000;
    g28[0x163c] = 0x00;
    g28[0x160d] = 0xf0;
    (void)g216[0x04/2];
    g216[0x1604/2] = 0x0006;
    g232[0x1614/4] = 0x01000000;
    (void)g28[0x1650];

    rtl_init();

    return 0;
}

static void bb_stop(void)
{
    nic32[RT_RXCONFIG/4] &= 0xfffffff5;
}

static void bb_start(void)
{
    nic32[RT_RXCONFIG/4] |= 0x0000000a;
}

static vuc * const txdesc[4] = { REGC(0xa1846000),
				 REGC(0xa1846800),
				 REGC(0xa1847000),
				 REGC(0xa1847800) };

static int bb_tx(unsigned char * pkt, int len)
{
  while (!(nic32[RT_TXSTATUS0/4 + rtl.cur_tx] & 0x2000))
    if (nic32[RT_TXSTATUS0/4 + rtl.cur_tx] & 0x40000000)
      nic32[RT_TXSTATUS0/4 + rtl.cur_tx] |= 1;

    memcpy(txdesc[rtl.cur_tx], pkt, len);
    if (len < 60) /* 8139 doesn't auto-pad */
	len = 60;
    nic32[RT_TXSTATUS0/4 + rtl.cur_tx] = len;
    rtl.cur_tx = (rtl.cur_tx + 1) % 4;
}

static void pktcpy(unsigned char *dest, unsigned char *src, int n)
{
    if (n > 1514)
	return;

    if ((unsigned int)(src + n) < (unsigned int)(0xa1840000 + 16384))
	memcpy(dest, src, n);
    else {
	memcpy(dest, src, (0xa1840000 + 16384) - (unsigned int)src);
	memcpy(dest + ((0xa1840000 + 16384) - (unsigned int)src), (unsigned char *)0xa1840000, (unsigned int)(src + n) - (0xa1840000 + 16384)); 
    }
}

static int bb_rx() 
{
    int avail;
    int processed;
    unsigned int      rx_status;
    int rx_size, pkt_size, ring_offset;
    int i;
    unsigned char       *pkt;

    processed = 0;

    /* While we have frames left to process... */	
    while (!(nic8[RT_CHIPCMD] & 1)) {
	/* Get frame size and status */
	ring_offset = rtl.cur_rx % 16384;
	rx_status = mem32[0x0000/4 + ring_offset/4];
	rx_size = (rx_status >> 16) & 0xffff;
	pkt_size = rx_size - 4;

	/* apparently this means the rtl8139 is still copying */
	if (rx_size == 0xfff0) {
	    break;
	}

	if ((rx_status & 1) && (pkt_size <= 1514)) {
	    pkt = (unsigned char*)(mem8 + 0x0000 + ring_offset + 4);
	    pktcpy(current_pkt, pkt, pkt_size);
	    process_pkt(current_pkt, pkt_size);
	}

	rtl.cur_rx = (rtl.cur_rx + rx_size + 4 + 3) & ~3;
	nic16[RT_RXBUFTAIL/2] = rtl.cur_rx - 16;

	// Ack it
	i = nic16[RT_INTRSTATUS/2];
	if (i & RT_INT_RX_ACK)
	    nic16[RT_INTRSTATUS/2] = RT_INT_RX_ACK;

	processed++;
    }
    return processed;
}

extern void uint_to_string(unsigned int foo, unsigned char *bar);

static void bb_loop() 
{
    unsigned int intr;
    int i;
    char value[256];

    intr = 0;

    while(!escape_loop) {

	/* Check interrupt status */
	if (nic16[RT_INTRSTATUS/2] != intr) {
	    intr = nic16[RT_INTRSTATUS/2];
	    nic16[RT_INTRSTATUS/2] = intr & ~RT_INT_RX_ACK;
	}

	/* Did we receive some data? */
	if (intr & RT_INT_RX_ACK) {
	    i = bb_rx();
	}

	/* link change */
	if (intr & RT_INT_RXFIFO_UNDERRUN) {

	    if (booted && !running) {
	        disp_status("link change...");
	    }

	    nic16[RT_MII_BMCR/2] = 0x9200;

	    /* wait for valid link */
	    while (!(nic16[RT_MII_BMSR/2] & 0x20));

	    /* wait for the additional link change interrupt that is coming */
	    while (!(nic16[RT_INTRSTATUS/2] & RT_INT_RXFIFO_UNDERRUN));
	    nic16[RT_INTRSTATUS/2] = RT_INT_RXFIFO_UNDERRUN;

	    if (booted && !running) {
	        disp_status("idle...");
	    }

	}
	    
	/* Rx FIFO overflow */
	if (intr & RT_INT_RXFIFO_OVERFLOW) {
	    /* must clear Rx Buffer Overflow too for some reason */
	    nic16[RT_INTRSTATUS/2] = RT_INT_RXBUF_OVERFLOW;
	}

	/* Rx Buffer overflow */
	if (intr & RT_INT_RXBUF_OVERFLOW) {
            rtl.cur_rx = nic16[RT_RXBUFHEAD];
            nic16[RT_RXBUFTAIL]=  rtl.cur_rx - 16;
	    
            rtl.cur_rx = 0;
            nic8[RT_CHIPCMD] = RT_CMD_TX_ENABLE;
	    
            nic32[RT_RXCONFIG/4] = 0x00000e0a;
	    
            while ( !(nic8[RT_CHIPCMD] & RT_CMD_RX_ENABLE))
                nic8[RT_CHIPCMD] = RT_CMD_TX_ENABLE | RT_CMD_RX_ENABLE;
            
            nic32[RT_RXCONFIG/4] = 0x00000e0a;

	    nic16[RT_INTRSTATUS/2] = 0xffff;
	}
    }
    escape_loop = 0;
}

// Pull together all the goodies
adapter_t adapter_bba = {
	"Broadband Adapter (HIT-0400)",
	{ 0 },		// Mac address
	bb_detect,
	bb_init,
	bb_start,
	bb_stop,
	bb_loop,
	bb_tx
};
