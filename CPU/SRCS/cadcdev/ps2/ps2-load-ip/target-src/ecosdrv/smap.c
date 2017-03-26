/* ps2-load-ip

   smap.c

   Copyright (c)2001 Sony Computer Entertainment Inc.
   Copyright (c)2001 YAEGASHI Takeshi
   Copyright (2)2002 Dan Potter
   License: GPL

   $Id: smap.c,v 1.4 2002/11/03 06:57:13 bardtx Exp $
*/

/* Pulled from the eCos port */

// $Id: smap.c,v 1.4 2002/11/03 06:57:13 bardtx Exp $
// many routines are taken from drivers/ps2/smap.c of PS2 Linux kernel (GPL).

// Modified by Dan Potter for ps2-load-ip. Man, this driver is super
// turbo hacked at this point, but it should function enough for this
// particular purpose anyway. I've removed a lot of cruft from the
// old Linux driver.

#include "smap.h"
#include <stddef.h>
#include "stdio.h"
#include "irq.h"
#include "net.h"
#include "ps2loadip.h"
#include "fb_support.h"

/*  */
#define IRQ_SBUS_PCIC       41

/* This is a hack but it should do for now... */
void udelay(unsigned long usec) {
	int i;

	for (i=0; i<usec*100; i++)
		;
}

/* All of our printfs _must_ go to the GS console, because otherwise
   we'd be in a chicken-and-egg situation... */
#define printf(args...) gs_printf(LCD_SYSMSG_FG, ##args)

static struct smap_chan *smap_chan = NULL;
static struct smap_chan smap0;

static unsigned char smap_dtxbuf[SMAP_TXMAXSIZE+SMAP_TXMAXTAILPAD] __attribute__((__aligned__(16))); 
static unsigned char smap_drxbuf[SMAP_RXMAXSIZE+SMAP_RXMAXTAILPAD] __attribute__((__aligned__(16)));

/*--------------------------------------------------------------------------*/

static void smap_clear_all_interrupt(struct smap_chan *smap);
static void smap_interrupt_XXable(struct smap_chan *smap, int enable_flag);
static void smap_txrx_XXable(struct smap_chan *smap, int enable_flag);
static void smap_txbd_init(struct smap_chan *smap);
static void smap_rxbd_init(struct smap_chan *smap);
static int  smap_read_phy(struct smap_chan *smap, u_int32_t phyadr, u_int32_t regadr);
static int  smap_write_phy(struct smap_chan *smap, u_int32_t phyadr, u_int32_t regadr, u_int16_t data);
static int smap_fifo_reset(struct smap_chan *smap);
static void smap_reg_init(struct smap_chan *smap);
static int  smap_emac3_soft_reset(struct smap_chan *smap);
static void smap_emac3_set_defvalue(struct smap_chan *smap);
static void smap_emac3_init(struct smap_chan *smap, int reset_only);
static void smap_emac3_re_init(struct smap_chan *smap);
static int  smap_phy_init(struct smap_chan *smap, int reset_only);
static int  smap_phy_reset(struct smap_chan *smap);
static int  smap_auto_negotiation(struct smap_chan *smap, int enable_auto_nego);
static int  smap_confirm_auto_negotiation(struct smap_chan *smap);
static void smap_force_spd_100M(struct smap_chan *smap);
static void smap_force_spd_10M(struct smap_chan *smap);
static void smap_confirm_force_spd(uint32 arg);
static void smap_phy_set_dsp(struct smap_chan *smap);
static void smap_reset(struct smap_chan *smap, int reset_only);
static void smap_print_mac_address(struct smap_chan *smap);
static int  smap_get_node_addr(struct smap_chan *smap);
static void smap_base_init(struct smap_chan *smap);
static void smap_dump_packet(struct smap_chan *smap, u_int8_t *ptr, int length);
#if 0
static void smap_dump_txbd(struct smap_chan *smap);
static void smap_dump_rxbd(struct smap_chan *smap);
static void smap_dump_reg(struct smap_chan *smap);
static void smap_dump_emac3_reg(struct smap_chan *smap);
#endif

/*--------------------------------------------------------------------------*/

static void
smap_tx_intr(u_int16_t intstat)
{
	struct smap_chan *smap = &smap0;
	volatile struct smapbd *txbd;
	int txlen, error;
	u_int16_t txstat;

	txbd = &smap->txbd[smap->txbdi];
	txstat = txbd->ctrl_stat;

	while (((txstat & SMAP_BD_TX_READY) == 0) && (smap->txbdusedcnt > 0)) {
		if (smap->flags & SMAP_F_PRINT_PKT) {
			printf("eth: tx intr: process packet,"
				"[%d]=stat=0x%04x,len=%d,ptr=0x%04x\n",
					smap->txbdi,txstat,
					txbd->length,txbd->pointer);
		}
		/* txlen is multiple of 4 */
		if ((txbd->length%4) == 0)
			txlen = txbd->length;
		else
			txlen = txbd->length + (4 - (txbd->length%4));
		smap->txfreebufsize += txlen;

		error = 0;
		if (txstat & 0x7FFF) {
			if (txstat & SMAP_BD_TX_BADFCS) {
				error++;
				if (smap->flags & SMAP_F_PRINT_MSG) {
					printf("eth:tx intr: bad FCS\n");
				}
			}
			if (txstat & SMAP_BD_TX_BADPKT) {
				error++;
				if (smap->flags & SMAP_F_PRINT_MSG) {
					printf("eth:tx intr: bad previous packet\n");
				}
			}
			if (txstat & SMAP_BD_TX_LOSSCR) {
				error++;
				if (smap->flags & SMAP_F_PRINT_MSG) {
					printf("eth:tx intr: loss of carrier\n");
				}
			}
			if (txstat & SMAP_BD_TX_EDEFER) {
				error++;
				if (smap->flags & SMAP_F_PRINT_MSG) {
					printf("eth:tx intr: excessive deferral\n");
				}
			}
			if (txstat & SMAP_BD_TX_ECOLL) {
				error++;
				if (smap->flags & SMAP_F_PRINT_MSG) {
					printf("eth:tx intr: excessive collisions\n");
				}
			}
			if (txstat & SMAP_BD_TX_LCOLL) {
				error++;
				if (smap->flags & SMAP_F_PRINT_MSG) {
					printf("eth:tx intr: late collision\n");
				}
			}
#if 0
			if (txstat & SMAP_BD_TX_MCOLL) {
				smap->net_stats.collisions++;	/*XXX*/
			}
			if (txstat & SMAP_BD_TX_SCOLL) {
				smap->net_stats.collisions++;
			}
#endif
			if (txstat & SMAP_BD_TX_UNDERRUN) {
				error++;
				if (smap->flags & SMAP_F_PRINT_MSG) {
					printf("eth:tx intr: underrun\n");
				}
			}
			if (txstat & SMAP_BD_TX_SQE) {
				error++;
				if (smap->flags & SMAP_F_PRINT_MSG) {
					printf("eth:tx intr: sqe test failed\n");
				}
			}
			if ((error > 0) && (smap->flags & SMAP_F_PRINT_MSG)) {
				printf("eth:Tx intr: [%d]=stat(0x%04x, 0x%04x), len(%d, 0x%04x), ptr(0x%04x)\n", smap->txbdi,txstat,txbd->ctrl_stat,txbd->length,txbd->length,txbd->pointer);
			}
		}

#if 0
		if (error == 0) {
			smap->net_stats.tx_packets++;
			smap->net_stats.tx_bytes += txbd->length;
		} else {
			smap->net_stats.tx_errors++;
		}
#endif

		smap->txbdusedcnt--;

		/* clear txbd */
		txbd->length = 0;
		txbd->pointer = 0;
		txbd->ctrl_stat = 0;

#if 0
		/* for next packet */
		clear_bit(0, (void *)&net_dev->tbusy);
		mark_bh(NET_BH);
#endif

		/* renew buffer descriptor */
		SMAP_BD_NEXT(smap->txbdi);
		txbd = &smap->txbd[smap->txbdi];
		txstat = txbd->ctrl_stat;
	}

	return;
}

static void
smap_rx_intr(u_int16_t intstat)
{
	struct smap_chan *smap = &smap0;
	volatile struct smapbd *rxbd;
	u_int16_t rxstat;
	int i, rxlen;
	u_int32_t *datap;
	int pkt_len = 0;
	int end, pkt_err;
	int rx_pkt_cnt = 0;

	rxbd = &smap->rxbd[smap->rxbdi];
	rxstat = rxbd->ctrl_stat;

	while ((rxstat & SMAP_BD_RX_EMPTY) == 0) {
		end = CLEAR;
		pkt_err = CLEAR;

		if (rxstat & 0x7FFF) {
			if (rxstat & SMAP_BD_RX_OVERRUN) {
				if (smap->flags & SMAP_F_PRINT_MSG) {
					printf("eth:rx intr: overrun\n");
				}
			}
			if (rxstat & SMAP_BD_RX_PFRM) {
				if (smap->flags & SMAP_F_PRINT_MSG) {
					printf("eth:rx intr: pause frame\n");
				}
			}
			if (rxstat & SMAP_BD_RX_BADFRM) {
				if (smap->flags & SMAP_F_PRINT_MSG) {
					printf("eth:rx intr: bad frame\n");
				}
			}
			if (rxstat & SMAP_BD_RX_RUNTFRM) {
				if (smap->flags & SMAP_F_PRINT_MSG) {
					printf("eth:rx intr: runt frame\n");
				}
			}
			if (rxstat & SMAP_BD_RX_SHORTEVNT) {
				if (smap->flags & SMAP_F_PRINT_MSG) {
					printf("eth:rx intr: short event\n");
				}
			}
			if (rxstat & SMAP_BD_RX_ALIGNERR) {
				if (smap->flags & SMAP_F_PRINT_MSG) {
					printf("eth:rx intr: align error\n");
				}
			}
			if (rxstat & SMAP_BD_RX_BADFCS) {
				if (smap->flags & SMAP_F_PRINT_MSG) {
					printf("eth:rx intr: bad FCS\n");
				}
			}
			if (rxstat & SMAP_BD_RX_FRMTOOLONG) {
				if (smap->flags & SMAP_F_PRINT_MSG) {
					printf("eth:rx intr: frame too long\n");
				}
			}
			if (rxstat & SMAP_BD_RX_OUTRANGE) {
				if (smap->flags & SMAP_F_PRINT_MSG) {
					printf("eth:rx intr: out range error\n");
				}
			}
			if (rxstat & SMAP_BD_RX_INRANGE) {
				if (smap->flags & SMAP_F_PRINT_MSG) {
					printf("eth:rx intr: in range error\n");
				}
			}
			if (smap->flags & SMAP_F_PRINT_MSG) {
				printf("eth:Rx intr: [%d]=stat(0x%04x, 0x%04x), len(%d, 0x%04x), ptr(0x%04x)\n", smap->rxbdi, rxstat,rxbd->ctrl_stat,rxbd->length,rxbd->length,rxbd->pointer);
			}
			pkt_err = SET;
			goto next;
		}

		pkt_len = rxbd->length;

		if ((pkt_len < SMAP_RXMINSIZE) || (pkt_len > SMAP_RXMAXSIZE)) {
			printf("eth:rx intr: packet length error (%d)\n",
						pkt_len);
			pkt_err = SET;
			goto next;
		}

		/* rxlen is multiple of 4 */
		if ((pkt_len%4) == 0)
			rxlen = pkt_len;
		else
			rxlen = pkt_len + (4 - (pkt_len%4));

		/* recv from FIFO to memory */
		smap->rxbrp = rxbd->pointer;
		SMAPREG16(smap,SMAP_RXFIFO_RD_PTR) = (smap->rxbrp & 0x3FFC);

		datap = (u_int32_t *)smap->rxbuf;
		for (i = 0; i < rxlen; i += 4) {	/* FIFO -> memory */
			*datap++ = SMAPREG32(smap,SMAP_RXFIFO_DATA);
		}

		if (smap->flags & SMAP_F_PRINT_PKT) {
			printf("eth: rx: fifo->mem done,"
				"[%d]=stat=0x%04x,len=%d,ptr=0x%04x\n",
					smap->rxbdi,rxstat,
					rxbd->length,rxbd->pointer);
			smap_dump_packet(smap, smap->rxbuf,
				(rxbd->length < 60) ? rxbd->length : 60);
		}

		// Hook into the dc-load-ip code
		process_pkt(smap->rxbuf, pkt_len);
next:
		SMAPREG8(smap,SMAP_RXFIFO_FRAME_DEC) = 1;
		rx_pkt_cnt++;

#if 0
		if (pkt_err == 0) {
			smap->net_stats.rx_packets++;
			smap->net_stats.rx_bytes += pkt_len;
		} else {
			smap->net_stats.rx_errors++;
		}
#endif

		/* clear rxbd */
		rxbd->length = 0;
		rxbd->pointer = 0;
		rxbd->ctrl_stat = SMAP_BD_RX_EMPTY;

		/* renew buffer descriptor */
		SMAP_BD_NEXT(smap->rxbdi);
		rxbd = &smap->rxbd[smap->rxbdi];
		rxstat = rxbd->ctrl_stat;

		if (end)
			break;
	}
	if ((smap->flags & SMAP_F_RXDNV_DISABLE) && (rx_pkt_cnt > 0)) {
		smap->flags &= ~SMAP_F_RXDNV_DISABLE;
		SMAPREG16(smap,SMAP_INTR_ENABLE) |= INTR_RXDNV;
	}

	return;
}

static void
smap_emac3_intr()
{
	struct smap_chan *smap = &smap0;
	u_int32_t stat, ena;

	stat = EMAC3REG_READ(smap, SMAP_EMAC3_INTR_STAT);
	ena = EMAC3REG_READ(smap, SMAP_EMAC3_INTR_ENABLE);

	/* clear emac3 interrupt */
	EMAC3REG_WRITE(smap, SMAP_EMAC3_INTR_STAT, stat);

	stat &= (ena|E3_DEAD_ALL);
	if (stat & E3_INTR_OVERRUN) {		/* this bit does NOT WORKED */
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: rx overrun\n");
		}
	}
	if (stat & E3_INTR_PF) {
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: rx pause frame\n");
		}
	}
	if (stat & E3_INTR_BAD_FRAME) {
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: rx bad frame\n");
		}
	}
	if (stat & E3_INTR_RUNT_FRAME) {
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: rx runt frame\n");
		}
	}
	if (stat & E3_INTR_SHORT_EVENT) {
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: rx short event\n");
		}
	}
	if (stat & E3_INTR_ALIGN_ERR) {
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: rx alignment error\n");
		}
	}
	if (stat & E3_INTR_BAD_FCS) {
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: rx bad FCS\n");
		}
	}
	if (stat & E3_INTR_TOO_LONG) {
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: rx frame too long\n");
		}
	}
	if (stat & E3_INTR_OUT_RANGE_ERR) {
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: rx out range error\n");
		}
	}
	if (stat & E3_INTR_IN_RANGE_ERR) {
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: rx in range error\n");
		}
	}

	if (stat & E3_INTR_DEAD_DEPEND) {
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: tx dead in dependent mode\n");
		}
	}
	if (stat & E3_INTR_DEAD_0) {
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: tx dead in channel 0\n");
		}
	}
	if (stat & E3_INTR_SQE_ERR_0) {
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: tx sqe test error in channel 0\n");
		}
	}
	if (stat & E3_INTR_TX_ERR_0) {
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: tx transmit error in channel 0\n");
		}
	}
	if (stat & E3_INTR_DEAD_1) {
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: tx dead in channel 1\n");
		}
	}
	if (stat & E3_INTR_SQE_ERR_1) {
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: tx sqe test error in channel 1\n");
		}
	}
	if (stat & E3_INTR_TX_ERR_1) {
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: tx transmit error in channel 1\n");
		}
	}
	if (stat & E3_INTR_MMAOP_SUCCESS) {
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: phy operation succeeded\n");
		}
	}
	if (stat & E3_INTR_MMAOP_FAIL) {
		if (smap->flags & SMAP_F_PRINT_MSG) {
			printf("eth:emac3 intr: phy operation failed\n");
		}
	}

	return;
}

void
smap_poll()
{
	struct smap_chan *smap = &smap0;
	uint32 flags;
	u_int16_t stat, ena;

	flags = irq_disable();

	stat = SMAPREG16(smap,SMAP_INTR_STAT) & INTR_BITMSK;
	ena =  SMAPREG16(smap,SMAP_INTR_ENABLE) & INTR_BITMSK;
	stat &= ena;
	if (stat == 0)
		goto end;

	if (stat & INTR_TXDNV) {
		/* disable TXDNV interrupt */
		SMAPREG16(smap,SMAP_INTR_ENABLE) &= ~INTR_TXDNV;
		smap->flags |= SMAP_F_TXDNV_DISABLE;
		/* clear interrupt */
		SMAPREG16(smap,SMAP_INTR_CLR) = INTR_TXDNV;

		printf("eth: intr: TX desc not valid\n");
		EMAC3REG_WRITE(smap, SMAP_EMAC3_INTR_STAT, E3_DEAD_ALL);
	}
	if (stat & INTR_RXDNV) {
		/* disable RXDNV interrupt */
		SMAPREG16(smap,SMAP_INTR_ENABLE) &= ~INTR_RXDNV;
		smap->flags |= SMAP_F_RXDNV_DISABLE;
		/* clear interrupt */
		SMAPREG16(smap,SMAP_INTR_CLR) = INTR_RXDNV;

		printf("eth: intr: RX desc not valid\n");
		(void)smap_rx_intr(stat & INTR_RXDNV);
	}
	if (stat & INTR_TXEND) {
		SMAPREG16(smap,SMAP_INTR_CLR) = INTR_TXEND;
		/* workaround for race condition of TxEND/RxEND */
		if (SMAPREG8(smap,SMAP_RXFIFO_FRAME_CNT) > 0) {
			stat |= INTR_RXEND;
		}
		(void)smap_tx_intr(stat & INTR_TXEND);
	}
	if (stat & INTR_RXEND) {
		SMAPREG16(smap,SMAP_INTR_CLR) = INTR_RXEND;
		(void)smap_rx_intr(stat & INTR_RXEND);
		/* workaround for race condition of TxEND/RxEND */
		if ((smap->txbdusedcnt > 0) &&
		    (smap->txbdusedcnt > SMAPREG8(smap,SMAP_TXFIFO_FRAME_CNT))
		   ) {
			(void)smap_tx_intr(INTR_TXEND);
		}
	}
	if (stat & INTR_EMAC3) {
		(void)smap_emac3_intr();
	}
end:
	irq_restore(flags);
	return;
}

/*--------------------------------------------------------------------------*/

static void
smap_clear_all_interrupt(struct smap_chan *smap)
{
	SMAPREG16(smap,SMAP_INTR_CLR) = INTR_CLR_ALL;

	EMAC3REG_WRITE(smap, SMAP_EMAC3_INTR_STAT, E3_INTR_ALL);

	return;
}

static void
smap_interrupt_XXable(struct smap_chan *smap, int enable_flag)
{
	if (enable_flag) {
		/* enable interrupt */
		SMAPREG16(smap,SMAP_INTR_ENABLE) |= INTR_ENA_ALL;
		EMAC3REG_WRITE(smap, SMAP_EMAC3_INTR_ENABLE, E3_INTR_ALL);
	} else {
		/* disable interrupt */
		SMAPREG16(smap,SMAP_INTR_ENABLE) &= ~INTR_ENA_ALL;
		EMAC3REG_WRITE(smap, SMAP_EMAC3_INTR_ENABLE, 0);
	}
	return;
}

static void
smap_txrx_XXable(struct smap_chan *smap, int enable_flag)
{
	int i;
	u_int32_t e3v;

	if (enable_flag) {
		/* enable tx/rx */
		EMAC3REG_WRITE(smap, SMAP_EMAC3_MODE0,
					E3_TXMAC_ENABLE|E3_RXMAC_ENABLE);
	} else {
		/* disable tx/rx */
		e3v = EMAC3REG_READ(smap, SMAP_EMAC3_MODE0);
		e3v &= ~(E3_TXMAC_ENABLE|E3_RXMAC_ENABLE);
		EMAC3REG_WRITE(smap, SMAP_EMAC3_MODE0, e3v);

		/* check EMAC3 idle status */
		for (i = SMAP_LOOP_COUNT; i; i--) {
			e3v = EMAC3REG_READ(smap, SMAP_EMAC3_MODE0);
			if ( (e3v & E3_RXMAC_IDLE) && (e3v & E3_TXMAC_IDLE) )
				break;
		}
		if (i == 0) {
			printf("eth: emac3 is still running(%x).\n",
					e3v);
		}
	}
	return;
}

static void
smap_txbd_init(struct smap_chan *smap)
{
	int i;
	volatile struct smapbd *bd = smap->txbd;

	smap->txfreebufsize = SMAP_TXBUFSIZE;
	smap->txbwp = SMAP_TXBUFBASE;
	smap->txbds = smap->txbdi = smap->txbdusedcnt = 0;
	for (i = 0; i < SMAP_BD_MAX_ENTRY; i++, bd++) {
		bd->ctrl_stat = 0;		/* clear ready bit */
		bd->reserved = 0;		/* must be zero */
		bd->length = 0;
		bd->pointer = 0;
	}
	return;
}

static void
smap_rxbd_init(struct smap_chan *smap)
{
	int i;
	volatile struct smapbd *bd = smap->rxbd;

	smap->rxbrp = SMAP_RXBUFBASE;
	smap->rxbdi = 0;
	for (i = 0; i < SMAP_BD_MAX_ENTRY; i++, bd++) {
		bd->ctrl_stat = SMAP_BD_RX_EMPTY;	/* set empty bit */
		bd->reserved = 0;			/* must be zero */
		bd->length = 0;
		bd->pointer = 0;
	}
	return;
}

static int
smap_read_phy(struct smap_chan *smap, u_int32_t phyadr, u_int32_t regadr)
{
	int i;
	u_int32_t e3v;

	/* check complete bit */
	for (i = SMAP_LOOP_COUNT; i; i--) {
		e3v = EMAC3REG_READ(smap, SMAP_EMAC3_STA_CTRL);
		if (e3v & E3_PHY_OP_COMP)
			break;
	}
	if (i == 0) {
		printf("eth: read phy: busy\n");
		return(-1);
	}

	/* write phy address and register address */
	EMAC3REG_WRITE(smap, SMAP_EMAC3_STA_CTRL,
			E3_PHY_READ |
			((phyadr&E3_PHY_ADDR_MSK)<<E3_PHY_ADDR_BITSFT) |
			(regadr&E3_PHY_REG_ADDR_MSK) );

	/* check complete bit */
	for (i = SMAP_LOOP_COUNT; i; i--) {
		e3v = EMAC3REG_READ(smap, SMAP_EMAC3_STA_CTRL);
		if (e3v & E3_PHY_OP_COMP)
			break;
	}
	if (i == 0) {
		printf("eth: read phy: write address busy, val = %x\n",
						e3v);
		return(-1);
	}

	/* workarrund: it may be needed to re-read to get correct phy data */
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_STA_CTRL);
	return(e3v >> E3_PHY_DATA_BITSFT);
}

static int
smap_write_phy(struct smap_chan *smap,
		u_int32_t phyadr, u_int32_t regadr, u_int16_t data)
{
	int i;
	u_int32_t e3v;

	/* check complete bit */
	for (i = SMAP_LOOP_COUNT; i; i--) {
		e3v = EMAC3REG_READ(smap, SMAP_EMAC3_STA_CTRL);
		if (e3v & E3_PHY_OP_COMP)
			break;
	}
	if (i == 0) {
		printf("eth: write phy: busy\n");
		return(-1);
	}

	/* write data, phy address and register address */
	e3v = ( ((data&E3_PHY_DATA_MSK)<<E3_PHY_DATA_BITSFT) |
			E3_PHY_WRITE |
			((phyadr&E3_PHY_ADDR_MSK)<<E3_PHY_ADDR_BITSFT) |
			(regadr&E3_PHY_REG_ADDR_MSK) );
	EMAC3REG_WRITE(smap, SMAP_EMAC3_STA_CTRL, e3v);

	/* check complete bit */
	for (i = SMAP_LOOP_COUNT; i; i--) {
		e3v = EMAC3REG_READ(smap, SMAP_EMAC3_STA_CTRL);
		if (e3v & E3_PHY_OP_COMP)
			break;
	}
	if (i == 0) {
		printf("eth: write phy: write data busy, val = %x\n",
						e3v);
		return(-1);
	}

	return(0);
}

static int
smap_fifo_reset(struct smap_chan *smap)
{
	int i, retval = 0;

	/* reset TX FIFO */
	SMAPREG8(smap,SMAP_TXFIFO_CTRL) = TXFIFO_RESET;
	/* reset RX FIFO */
	SMAPREG8(smap,SMAP_RXFIFO_CTRL) = RXFIFO_RESET;

	/* confirm reset done */
	for (i = SMAP_LOOP_COUNT; i; i--) {
		if (!(SMAPREG8(smap,SMAP_TXFIFO_CTRL) & TXFIFO_RESET))
			break;
	}
	if (i == 0) {
		printf("eth: Txfifo reset is in progress\n");
		retval |= 1;
	}

	for (i = SMAP_LOOP_COUNT; i; i--) {
		if (!(SMAPREG8(smap,SMAP_RXFIFO_CTRL) & RXFIFO_RESET))
			break;
	}
	if (i == 0) {
		printf("eth: Rxfifo reset is in progress\n");
		retval |= 2;
	}

	return(retval);
}

static void
smap_reg_init(struct smap_chan *smap)
{

	(void)smap_interrupt_XXable(smap, DISABLE);
	(void)smap_clear_all_interrupt(smap);

	/* BD mode */
	SMAPREG8(smap,SMAP_BD_MODE) = 0;	/* swap */

	/* reset TX/RX FIFO */
	(void)smap_fifo_reset(smap);

	return;
}

static int
smap_emac3_soft_reset(struct smap_chan *smap)
{
	int i;
	u_int32_t e3v;

	EMAC3REG_WRITE(smap, SMAP_EMAC3_MODE0, E3_SOFT_RESET);
	for (i = SMAP_LOOP_COUNT; i; i--) {
		e3v = EMAC3REG_READ(smap, SMAP_EMAC3_MODE0);
		if (!(e3v & E3_SOFT_RESET))
			break;
	}
	if (i == 0) {
		printf("eth: emac3 reset is in progress\n");
		return(-1);
	}
	return(0);
}

static void
smap_emac3_set_defvalue(struct smap_chan *smap)
{
	u_int32_t e3v;

	/* set HW address */
	e3v = ( (smap->hwaddr[0] << 8) | smap->hwaddr[1] );
	EMAC3REG_WRITE(smap, SMAP_EMAC3_ADDR_HI, e3v);
	e3v = ( (smap->hwaddr[2] << 24) | (smap->hwaddr[3] << 16) |
			(smap->hwaddr[4] << 8) | smap->hwaddr[5] );
	EMAC3REG_WRITE(smap, SMAP_EMAC3_ADDR_LO, e3v);

	/* Inter-frame GAP */
	EMAC3REG_WRITE(smap, SMAP_EMAC3_INTER_FRAME_GAP, 4);

	/* Rx mode */
	e3v = (E3_RX_STRIP_PAD|E3_RX_STRIP_FCS|
				E3_RX_INDIVID_ADDR|E3_RX_BCAST);
	EMAC3REG_WRITE(smap, SMAP_EMAC3_RxMODE, e3v);

	/* Tx fifo value for request priority */
	/* low = 7*8=56, urgent = 15*8=120 */
	e3v = ( (7<<E3_TX_LOW_REQ_BITSFT) | (15<<E3_TX_URG_REQ_BITSFT) );
	EMAC3REG_WRITE(smap, SMAP_EMAC3_TxMODE1, e3v);

	/* TX threshold, (12+1)*64=832 */
	e3v = ((12&E3_TX_THRESHLD_MSK)<<E3_TX_THRESHLD_BITSFT);
	EMAC3REG_WRITE(smap, SMAP_EMAC3_TX_THRESHOLD, e3v);

	/* Rx watermark, low = 16*8=128, hi = 128*8=1024 */
	e3v = ( ((16&E3_RX_LO_WATER_MSK)<<E3_RX_LO_WATER_BITSFT) |
			((128&E3_RX_HI_WATER_MSK)<<E3_RX_HI_WATER_BITSFT) );
	EMAC3REG_WRITE(smap, SMAP_EMAC3_RX_WATERMARK, e3v);

	return;
}

static void
smap_emac3_init(struct smap_chan *smap, int reset_only)
{
	u_int32_t e3v;

	/* reset emac3 */
	(void)smap_emac3_soft_reset(smap);

	/* EMAC3 operating MODE */
	e3v = (E3_FDX_ENABLE|E3_IGNORE_SQE|E3_MEDIA_100M|
			E3_RXFIFO_2K|E3_TXFIFO_1K|
			E3_TXREQ0_SINGLE|E3_TXREQ1_SINGLE);
	EMAC3REG_WRITE(smap, SMAP_EMAC3_MODE1, e3v);

	/* phy init */
	if (smap_phy_init(smap, reset_only) < 0) {
		printf("eth: phy init error\n");
		return;
	}
	if (reset_only)		/* this flag may be set when unloading */
		return;

	/* clear interrupt */
	(void)smap_clear_all_interrupt(smap);
	/* disable interrupt */
	(void)smap_interrupt_XXable(smap, DISABLE);

	/* permanently set to default value */
	(void)smap_emac3_set_defvalue(smap);

	return;
}

static void
smap_emac3_re_init(struct smap_chan *smap)
{
	(void)smap_emac3_soft_reset(smap);
	EMAC3REG_WRITE(smap, SMAP_EMAC3_MODE1, smap->txmode_val);
	(void)smap_emac3_set_defvalue(smap);
	return;
}

/* return value 0: success, <0: error */
static int
smap_phy_init(struct smap_chan *smap, int reset_only)
{
	int val;

	val = smap_phy_reset(smap);
	if (val < 0)
		return val;

	if (reset_only)		/* this flag may be set when unloading */
		return 0;

	/* after phy reset, auto-nego is performed automatically */
	val = smap_auto_negotiation(smap, DISABLE);
	if (val == 0) {
		/* wait 1 second ?? probably need not */
		smap->flags |= SMAP_F_LINKESTABLISH;
		(void)smap_phy_set_dsp(smap);
		return(0);	/* auto-negotiation is succeeded */
	}

	/* force 100Mbps(HDX) or 10Mbps(HDX) */
	(void)smap_force_spd_100M(smap);

	return(0);
}

static int
smap_phy_reset(struct smap_chan *smap)
{
	int i;
	u_int16_t phyval = 0;

	/* set reset bit */
	smap_write_phy(smap, DsPHYTER_ADDRESS, DsPHYTER_BMCR,
			PHY_BMCR_RST|PHY_BMCR_100M|PHY_BMCR_ANEN|PHY_BMCR_DUPM);

	udelay(300);				/* wait 300us */

	/* confirm reset done */
	for (i = SMAP_LOOP_COUNT; i; i--) {
		phyval = (u_int16_t)smap_read_phy(smap,
					DsPHYTER_ADDRESS, DsPHYTER_BMCR);
		if (!(phyval & PHY_BMCR_RST))
			break;
		udelay(300);
	}
	if (i == 0) {
		printf("eth: PHY reset not complete(BMCR=0x%x)\n",
					phyval);
		return(-1);
	}
	return(0);
}

static int
smap_auto_negotiation(struct smap_chan *smap, int enable_auto_nego)
{
	int i, val;

	if (enable_auto_nego) {
		/* set auto-negotiation */
		smap_write_phy(smap, DsPHYTER_ADDRESS, DsPHYTER_BMCR,
				PHY_BMCR_100M|PHY_BMCR_ANEN|PHY_BMCR_DUPM);
	}

	val = smap_confirm_auto_negotiation(smap);
	for (i = SMAP_AUTONEGO_RETRY; i; i--) {
		if (val < 0) {	/* timeout */
			/* restart auto-negotiation */
			smap_write_phy(smap, DsPHYTER_ADDRESS, DsPHYTER_BMCR,
					PHY_BMCR_100M|PHY_BMCR_ANEN|PHY_BMCR_DUPM|PHY_BMCR_RSAN);
			val = smap_confirm_auto_negotiation(smap);
		} else
			break;
	}
	if ((i == 0) || (val < 0))
		return(-1);	/* error */

	return(0);
}

static int
smap_confirm_auto_negotiation(struct smap_chan *smap)
{
	int i;
	u_int16_t phyval = 0;
	u_int32_t e3v;

	for (i = SMAP_AUTONEGO_TIMEOUT; i; i--) {
						/* auto nego timeout is 3s */
		phyval = (u_int16_t)smap_read_phy(smap,
					DsPHYTER_ADDRESS, DsPHYTER_BMSR);
		if (phyval & PHY_BMSR_ANCP)
			break;
		udelay(1000);		/* wait 1ms */
	}
	if (i == 0) {
		printf("eth: Auto-negotiation timeout, not complete(BMSR=%x)\n",
					phyval);
		return(-1);
	}

	/* confirm speed & duplex mode */
	for (i = SMAP_LOOP_COUNT; i; i--) {
		phyval = (u_int16_t)smap_read_phy(smap,
					DsPHYTER_ADDRESS, DsPHYTER_PHYSTS);
		if ((phyval & PHY_STS_ANCP) && (phyval & PHY_STS_LINK))
			break;
		udelay(1000);
	}
	if (i == 0) {	/* error */
		printf("eth: Auto-negotiation error?? (PHYSTS=%x)\n",
					phyval);
	} else {
		printf("eth: Auto-negotiation complete. %s %s duplex mode.\n",
				(phyval & PHY_STS_10M) ? "10Mbps" : "100Mbps",
				(phyval & PHY_STS_FDX) ? "Full" : "Half");
		e3v = EMAC3REG_READ(smap, SMAP_EMAC3_MODE1);
		if (phyval & PHY_STS_FDX) {
			/* Full duplex mode */
			e3v |= (E3_FDX_ENABLE|E3_FLOWCTRL_ENABLE|E3_ALLOW_PF);
		} else {
			/* Half duplex mode */
			e3v &= ~(E3_FDX_ENABLE|E3_FLOWCTRL_ENABLE|E3_ALLOW_PF);
			if (phyval & PHY_STS_10M)
				e3v &= ~E3_IGNORE_SQE;
		}
		e3v &= ~E3_MEDIA_MSK;
		if (phyval & PHY_STS_10M)
			e3v |= E3_MEDIA_10M;
		else
			e3v |= E3_MEDIA_100M;
		EMAC3REG_WRITE(smap, SMAP_EMAC3_MODE1, e3v);
	}

	return(0);
}

static void
smap_force_spd_100M(struct smap_chan *smap)
{
	int i;
	printf("eth: try 100Mbps Half duplex mode...\n");

	/* set 100Mbps, half duplex */
	smap_write_phy(smap, DsPHYTER_ADDRESS, DsPHYTER_BMCR, PHY_BMCR_100M);

	/* delay 2s */
	smap->flags |= SMAP_F_CHECK_FORCE100M;
	for (i = SMAP_FORCEMODE_WAIT; i; i--)
		udelay(1000);
	smap_confirm_force_spd((uint32)smap);

	return;
}

static void
smap_force_spd_10M(struct smap_chan *smap)
{
	int i;
	printf("eth: try 10Mbps Half duplex mode...\n");

	/* set 10Mbps, half duplex */
	smap_write_phy(smap, DsPHYTER_ADDRESS, DsPHYTER_BMCR, PHY_BMCR_10M);

	/* delay 2s */
	smap->flags |= SMAP_F_CHECK_FORCE10M;
	for (i = SMAP_FORCEMODE_WAIT; i; i--)
		udelay(1000);
	smap_confirm_force_spd((uint32)smap);

	return;
}

static void
smap_confirm_force_spd(uint32 arg)
{
	struct smap_chan *smap = (struct smap_chan *)arg;
	int i;
	u_int16_t phyval = 0;
	u_int32_t e3v;

	/* confirm link status, wait 1s is needed */
	for (i = SMAP_FORCEMODE_TIMEOUT; i; i--) {
		phyval = (u_int16_t)smap_read_phy(smap,
					DsPHYTER_ADDRESS, DsPHYTER_BMSR);
		if (phyval & PHY_BMSR_LINK)
			break;
		udelay(1000);
	}
	if (i) {
validlink:
		e3v = EMAC3REG_READ(smap, SMAP_EMAC3_MODE1);
		e3v &= ~(E3_FDX_ENABLE|E3_FLOWCTRL_ENABLE|E3_ALLOW_PF|E3_MEDIA_MSK);
		if (smap->flags & SMAP_F_CHECK_FORCE100M) {
			printf("eth: 100Mbps Half duplex mode\n");
			e3v |= E3_MEDIA_100M;
		} else if (smap->flags & SMAP_F_CHECK_FORCE10M) {
			printf("eth: 10Mbps Half duplex mode\n");
			e3v &= ~E3_IGNORE_SQE;
			e3v |= E3_MEDIA_10M;
		}
		EMAC3REG_WRITE(smap, SMAP_EMAC3_MODE1, e3v);
		smap->flags &= ~(SMAP_F_CHECK_FORCE100M|SMAP_F_CHECK_FORCE10M);
		smap->flags |= SMAP_F_LINKESTABLISH;
		(void)smap_phy_set_dsp(smap);
		return;			/* success */
	}

	if (smap->flags & SMAP_F_CHECK_FORCE100M) {
		smap->flags &= ~SMAP_F_CHECK_FORCE100M;
		(void)smap_force_spd_10M(smap);
	} else if (smap->flags & SMAP_F_CHECK_FORCE10M) {
		smap->flags &= ~SMAP_F_CHECK_FORCE10M;
		phyval = (u_int16_t)smap_read_phy(smap,
				DsPHYTER_ADDRESS, DsPHYTER_PHYSTS);
		if (phyval & PHY_STS_LINK) {
			/* valid link */
			smap->flags |= SMAP_F_CHECK_FORCE10M;
			goto validlink;
		} else {
			printf("eth: fail force speed mode."
				" link not valid.  phystat=0x%04x\n",
						phyval);
		}
	}
	return;
}

static void
smap_phy_set_dsp(struct smap_chan *smap)
{
	u_int16_t id1, id2, phyval;

	if (!(smap->flags & SMAP_F_LINKESTABLISH))  /* link not established */
		return;

	/* this value is used in emac3 re-init without phy init */
	smap->txmode_val = EMAC3REG_READ(smap, SMAP_EMAC3_MODE1);

	id1 = (u_int16_t)smap_read_phy(smap, DsPHYTER_ADDRESS,DsPHYTER_PHYIDR1);
	id2 = (u_int16_t)smap_read_phy(smap, DsPHYTER_ADDRESS,DsPHYTER_PHYIDR2);

	if (!((id1 == PHY_IDR1_VAL) && ((id2&PHY_IDR2_MSK) == PHY_IDR2_VAL))) {
		smap->flags |= SMAP_F_LINKVALID;
		return;
	}

	if (smap->flags & SMAP_F_LINKVALID)
		return;

	smap_write_phy(smap, DsPHYTER_ADDRESS, 0x13, 0x0001);
	smap_write_phy(smap, DsPHYTER_ADDRESS, 0x19, 0x1898);
	smap_write_phy(smap, DsPHYTER_ADDRESS, 0x1f, 0x0000);
	smap_write_phy(smap, DsPHYTER_ADDRESS, 0x1d, 0x5040);
	smap_write_phy(smap, DsPHYTER_ADDRESS, 0x1e, 0x008c);
	smap_write_phy(smap, DsPHYTER_ADDRESS, 0x13, 0x0000);
	phyval = (u_int16_t)smap_read_phy(smap, DsPHYTER_ADDRESS,
							DsPHYTER_PHYSTS);
	if ( (phyval & (PHY_STS_DUPS|PHY_STS_SPDS|PHY_STS_LINK)) ==
				(PHY_STS_HDX|PHY_STS_10M|PHY_STS_LINK) ) {
		smap_write_phy(smap, DsPHYTER_ADDRESS, 0x1a, 0x0104);
	}

	smap->flags |= SMAP_F_LINKVALID;
	return;
}

static void
smap_reset(struct smap_chan *smap, int reset_only)
{
	smap_reg_init(smap);
	smap_emac3_init(smap, reset_only);

	return;
}

/*--------------------------------------------------------------------------*/

/* 1 clock with putting data */
static inline void
smap_eeprom_clock_dataout(struct smap_chan *smap, int val)
{
	SMAP_PP_SET_D(smap, val);

	SMAP_PP_CLK_OUT(smap, 0);
	udelay(1);	/* tDIS */

	SMAP_PP_CLK_OUT(smap, 1);
	udelay(1);	/* tSKH, tDIH */

	SMAP_PP_CLK_OUT(smap, 0);
	udelay(1);	/* tSKL */
}

/* 1 clock with getting data */
static inline int
smap_eeprom_clock_datain(struct smap_chan *smap)
{
	int r;

	SMAP_PP_SET_D(smap, 0);
	SMAP_PP_CLK_OUT(smap, 0);
	udelay(1);	/* tSKL */

	SMAP_PP_CLK_OUT(smap, 1);
	udelay(1);	/* tSKH, tPD0,1 */
	r = SMAP_PP_GET_Q(smap);

	SMAP_PP_CLK_OUT(smap, 0);
	udelay(1);	/* tSKL */

	return(r);
}

/* put address(6bit) */
static void
smap_eeprom_put_addr(struct smap_chan *smap, u_int8_t addr)
{
	int i;

	addr &= 0x3f;
	for (i = 0; i < 6; i++) {
		smap_eeprom_clock_dataout(smap, (addr & 0x20)?1:0);
		addr <<= 1;
	}
}

/* get data(16bit) */
static u_int16_t
smap_eeprom_get_data(struct smap_chan *smap)
{
	int i;
	u_int16_t data = 0;

	for (i = 0; i < 16; i++) {
		data <<= 1;
		data |= smap_eeprom_clock_datain(smap);
	}

	return(data);
}

/* instruction start(rise S, put start bit, op code) */
static void
smap_eeprom_start_op(struct smap_chan *smap, int op)
{
	/* set port direction */    
	SMAPREG8(smap, SMAP_PIOPORT_DIR) = (PP_SCLK | PP_CSEL | PP_DIN);

	/* rise chip select */
	SMAP_PP_SET_S(smap, 0);
	SMAP_PP_SET_D(smap, 0);
	SMAP_PP_CLK_OUT(smap, 0);
	udelay(1);	/* tSKS */

	SMAP_PP_SET_S(smap, 1);
	SMAP_PP_SET_D(smap, 0);
	SMAP_PP_CLK_OUT(smap, 0);
	udelay(1);	/* tCSS */

	/* put start bit */
	smap_eeprom_clock_dataout(smap, 1);

	/* put op code */
	smap_eeprom_clock_dataout(smap, (op >> 1) & 1);
	smap_eeprom_clock_dataout(smap, op & 1);
}

/* chip select low */
static void
smap_eeprom_cs_low(struct smap_chan *smap)
{
	SMAP_PP_SET_S(smap, 0);
	SMAP_PP_SET_D(smap, 0);
	SMAP_PP_CLK_OUT(smap, 0);
	udelay(2);	/* tSLSH */
}

/*
 *   EEPROM instruction
 */
/* read instruction */
static void
smap_eeprom_exec_read(struct smap_chan *smap,
					u_int8_t addr, u_int16_t *datap, int n)
{
	int i;

	smap_eeprom_start_op(smap, PP_OP_READ);
	smap_eeprom_put_addr(smap, addr);
	for (i = 0; i < n; i++) {
		*datap++ = smap_eeprom_get_data(smap);
	}
	smap_eeprom_cs_low(smap);
}

/*
 *   read EEPROM
 */
static void
smap_eeprom_read(struct smap_chan *smap, u_int8_t addr, u_int16_t *datap, int n)
{
	uint32 flags;

	flags = irq_disable();
	smap_eeprom_exec_read(smap, addr, datap, n);
	irq_restore(flags);
}

static void
smap_print_mac_address(struct smap_chan *smap)
{
	int i, j;

	// printf("%s: MAC address ");
	printf("SMAP Ethernet Detected, MAC ");
	for (i = 0; i < 6; i++) {
		j = smap->hwaddr[i];
		printf("%02x", j);
		if (i != 5)
			printf(":");
	}
	printf("\n");
	return;
}

uint8 * smap_get_mac() {
	return smap0.hwaddr;
}

static int
smap_get_node_addr(struct smap_chan *smap)
{
	int i;
	u_int16_t *macp, cksum, sum = 0;

	macp = (u_int16_t *)smap->hwaddr;
	smap_eeprom_read(smap, 0x0, macp, 3);
	smap_eeprom_read(smap, 0x3, &cksum, 1);

	for (i = 0; i < 3; i++) {
		sum += *macp++;
	}
	if (sum != cksum) {
		printf("eth: MAC address read error\n");
		printf("checksum %04x is read from EEPROM, "
			"and %04x is calculated by mac address read now.\n",
							cksum, sum);
		smap_print_mac_address(smap);
		memset(smap->hwaddr, 0, 6);
		return(-1);
	}
	smap_print_mac_address(smap);
#if 0
	if (!smap->sc) {
		printf("eth: net_dev is error(null).\n");
		memset(smap->hwaddr, 0, 6);
		return(-1);
	}
	memcpy(smap->sc->dev_addr, smap->hwaddr, 6);
#endif
	return(0);
}

static void
smap_base_init(struct smap_chan *smap)
{
	/* we can access register&BD after this routine returned. */

	smap->base = (volatile u_int8_t *)SMAP_BASE;
	smap->txbd = (volatile struct smapbd *)(smap->base + SMAP_BD_BASE_TX);
	smap->rxbd = (volatile struct smapbd *)(smap->base + SMAP_BD_BASE_RX);

	smap->txfreebufsize = SMAP_TXBUFSIZE;
	smap->txbwp = SMAP_TXBUFBASE;
	smap->txbds = smap->txbdi = smap->txbdusedcnt = 0;

	smap->rxbrp = SMAP_RXBUFBASE;
	smap->rxbdi = 0;

	return;
}

/*--------------------------------------------------------------------------*/

static void
smap_dump_packet(struct smap_chan *smap, u_int8_t *ptr, int length)
{
	int i;

	printf("eth: dump packet(dump len = %d):\n", length);
	for (i = 0; i < length; i++) {
		printf("%02x", *(ptr + i));
		if ((i%20)==19)
			printf("\n");
		else if ((i%4)==3)
			printf(" ");
	}
	printf("\n");
	return;
}

#if 0	/* DEBUG stuff */
static void
smap_dump_txbd(struct smap_chan *smap)
{
	int i;
	volatile struct smapbd *bd = smap->txbd;

	printf("Tx Buffer Descriptor\n");
	for (i = 0; i < SMAP_BD_MAX_ENTRY; i++, bd++) {
		printf("%02d: stat(0x%04x),rsv(0x%04x),len(%d,0x%04x),ptr(0x%04x), ",
					i, bd->ctrl_stat, bd->reserved,
					bd->length, bd->length, bd->pointer);
		if ((i%2)==1)
			printf("\n");
	}
	printf("tx buf w_ptr(0x%04x), free buf size(%d), bd used cnt(%d)\n",
		smap->txbwp, smap->txfreebufsize, smap->txbdusedcnt);
	printf("txbds(%d), txbdi(%d)\n", smap->txbds, smap->txbdi);
}

static void
smap_dump_rxbd(struct smap_chan *smap)
{
	int i;
	volatile struct smapbd *bd = smap->rxbd;

	printf("Rx Buffer Descriptor\n");
	for (i = 0; i < SMAP_BD_MAX_ENTRY; i++, bd++) {
		printf("%02d: stat(0x%04x),rsv(0x%04x),len(%d,0x%04x),ptr(0x%04x), ",
					i, bd->ctrl_stat, bd->reserved,
					bd->length, bd->length, bd->pointer);
		if ((i%2)==1)
			printf("\n");
	}
	printf("rx buf r_ptr(0x%04x), rxbdi(%d)\n", smap->rxbrp, smap->rxbdi);
}

static void
smap_dump_reg(struct smap_chan *smap)
{
	printf("PlayStation 2 SMAP register\n");
	printf("BD MODE(0x%02x), INTR STAT(0x%04x), ENA(0x%04x)\n",
		SMAPREG8(smap,SMAP_BD_MODE),
		SMAPREG16(smap,SMAP_INTR_STAT),
		SMAPREG16(smap,SMAP_INTR_ENABLE));
	printf("TX:CTRL(0x%02x), PTR(0x%04x), FRM CNT(0x%02x)\n",
		SMAPREG8(smap,SMAP_TXFIFO_CTRL),
		SMAPREG16(smap,SMAP_TXFIFO_WR_PTR),
		SMAPREG8(smap,SMAP_TXFIFO_FRAME_CNT));
	printf("RX:CTRL(0x%02x), PTR(0x%04x), FRM CNT(0x%02x)\n",
		SMAPREG8(smap,SMAP_RXFIFO_CTRL),
		SMAPREG16(smap,SMAP_RXFIFO_RD_PTR),
		SMAPREG8(smap,SMAP_RXFIFO_FRAME_CNT));
}

static void
smap_dump_emac3_reg(struct smap_chan *smap)
{
	u_int32_t e3v;

	printf("EMAC3 register\n");
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_MODE0);
	printf("mode0(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_MODE1);
	printf("mode1(0x%08x)\n", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_TxMODE0);
	printf("TXmode0(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_TxMODE1);
	printf("TXmode1(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_RxMODE);
	printf("RXmode(0x%08x)\n", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_INTR_STAT);
	printf("INTR stat(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_INTR_ENABLE);
	printf("INTR enable(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_ADDR_HI);
	printf("addr HI(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_ADDR_LO);
	printf("LO(0x%08x)\n", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_VLAN_TPID);
	printf("vlan TPID(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_VLAN_TCI);
	printf("vlan TCI(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_PAUSE_TIMER);
	printf("pause(0x%08x)\n", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_INDIVID_HASH1);
	printf("Indivi 1(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_INDIVID_HASH2);
	printf("2(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_INDIVID_HASH3);
	printf("3(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_INDIVID_HASH4);
	printf("4(0x%08x)\n", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_GROUP_HASH1);
	printf("Group 1(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_GROUP_HASH2);
	printf("2(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_GROUP_HASH3);
	printf("3(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_GROUP_HASH4);
	printf("4(0x%08x)\n", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_LAST_SA_HI);
	printf("LAST SA HI(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_LAST_SA_LO);
	printf("LO(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_INTER_FRAME_GAP);
	printf("IFG(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_STA_CTRL);
	printf("STA ctrl(0x%08x)\n", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_TX_THRESHOLD);
	printf("TX threshold(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_RX_WATERMARK);
	printf("RX watermark(0x%08x)\n", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_TX_OCTETS);
	printf("TX octets(0x%08x), ", e3v);
	e3v = EMAC3REG_READ(smap, SMAP_EMAC3_RX_OCTETS);
	printf("RX octets(0x%08x)\n", e3v);
}

#endif	/* 0 */

bool smap_init()
{
	struct smap_chan *smap = &smap0;
	int ps2_hdd_ether_present;
	int r;

	ps2_hdd_ether_present = *(int *)0x81fff000;
	if (ps2_hdd_ether_present != 0x0100) {
		printf("PlayStation 2 HDD/Ethernet device NOT present.\n");
		return false;
	}

	memset(smap, 0, sizeof(struct smap_chan));

	/* alloc tx/rx buffer(16B align) */
	smap->txbuf = smap->dtxbuf = smap_dtxbuf;
	smap->rxbuf = smap->drxbuf = smap_drxbuf;

	// debugging
	// smap->flags = SMAP_F_PRINT_MSG | SMAP_F_PRINT_PKT;

	smap_base_init(smap);
	r = smap_get_node_addr(smap);
	if (r < 0)
		goto error;

	smap_reset(smap, RESET_INIT);
	smap_txrx_XXable(smap, DISABLE);
	smap_txbd_init(smap);
	smap_rxbd_init(smap);

	smap->irq = IRQ_SBUS_PCIC;
	smap_chan = smap;

	if (smap->flags & SMAP_F_PRINT_MSG) {
		printf("eth: PlayStation 2 SMAP open\n");
	}

	if (!(smap->flags & SMAP_F_LINKVALID)) {
		printf("eth: Waiting for link to stabilize...\n");
		while (!(smap->flags & SMAP_F_LINKVALID)) {
			smap_poll();
		}
	}
	(void)smap_fifo_reset(smap);
	(void)smap_emac3_re_init(smap);
	(void)smap_txbd_init(smap);
	(void)smap_rxbd_init(smap);

	return false;

 error:
	smap_chan = NULL;
	return false;
}

void smap_start()
{
	struct smap_chan *smap = &smap0;

	if (smap->flags & SMAP_F_OPENED)
		return;

	(void)smap_clear_all_interrupt(smap);
	(void)smap_interrupt_XXable(smap, ENABLE);

	(void)smap_txrx_XXable(smap, ENABLE);

	smap->flags |= SMAP_F_OPENED;
}


void smap_stop()
{
	(void)smap_txrx_XXable(&smap0, DISABLE);
	(void)smap_interrupt_XXable(&smap0, DISABLE);
	(void)smap_clear_all_interrupt(&smap0);

	smap0.flags &= ~SMAP_F_OPENED;
}


int smap_can_send()
{
	struct smap_chan *smap = &smap0;
	return smap->txfreebufsize;
}


void smap_send(const uint8 * packet, int total_len)
{
	struct smap_chan *smap = &smap0;
//	int retval = 0;
	int i, txlen;
	u_int32_t txmode0;
	u_int32_t *datap;
	volatile struct smapbd *txbd = &smap->txbd[smap->txbds];
	uint32 flags;

	flags = irq_disable();

	// Wait to make sure we have enough room
	while (smap_can_send() < total_len)
		smap_poll();

	if (total_len > SMAP_TXMAXSIZE) {
		printf("eth: xmit: length error(%d)\n", total_len);
		goto end;
	}
	if (smap->txbdusedcnt >= (SMAP_BD_MAX_ENTRY-1)) {
		printf("eth: xmit: txbd is full\n");
		goto end;
	}
	if (txbd->ctrl_stat & SMAP_BD_TX_READY) {
		printf("eth: xmit: all txbd is used\n");
		goto end;
	}

	/* check datalen and free buffer space */
	/* txlen is multiple of 4 */
	if ((total_len%4) == 0)
		txlen = total_len;
	else
		txlen = total_len + (4 - (total_len%4));
	if (txlen > smap->txfreebufsize) {
		printf("eth: xmit: no space, txlen(%d), free space(%d)\n",
				txlen,smap->txfreebufsize);
		goto end;
	}

	txmode0 = EMAC3REG_READ(smap, SMAP_EMAC3_TxMODE0);
	if (txmode0 & E3_TX_GNP_0) {
		goto end;
	}

	/* clear padding bytes */
	*(int *)&smap->txbuf[total_len & ~3] = 0;
	memcpy(smap->txbuf, packet, total_len);
	/* {
		char *p = smap->txbuf;
		struct eth_drv_sg *last_sg = sg_list + sg_len;
		while (sg_list < last_sg) {
			memcpy(p, (void *)sg_list->buf, sg_list->len);
			p += sg_list->len;
			sg_list++;
		}
	} */

	/* send from memory to FIFO */
	SMAPREG16(smap,SMAP_TXFIFO_WR_PTR) = (smap->txbwp & 0x0FFC);

	datap = (u_int32_t *)smap->txbuf;
	for (i = 0; i < txlen; i += 4) {	/* memory -> FIFO */
		SMAPREG32(smap,SMAP_TXFIFO_DATA) = *datap++;
	}
	if (smap->flags & SMAP_F_PRINT_PKT) {
		printf("eth: xmit: mem->fifo done, len=%d,%d,ptr=0x%04x\n",
				total_len,txlen,smap->txbwp);
		smap_dump_packet(smap, smap->txbuf,
					(total_len < 60) ? total_len : 60);
	}

	smap->txfreebufsize -= txlen;

	/* send from FIFO to ethernet */
	txbd->length = total_len;
	txbd->pointer = smap->txbwp;

	SMAPREG8(smap,SMAP_TXFIFO_FRAME_INC) = 1;

	txbd->ctrl_stat =
		(SMAP_BD_TX_READY|SMAP_BD_TX_GENFCS|SMAP_BD_TX_GENPAD);
	smap->txbdusedcnt++;

	EMAC3REG_WRITE(smap, SMAP_EMAC3_TxMODE0, E3_TX_GNP_0);
						/* FIFO->ethernet */

	if (smap->flags & SMAP_F_TXDNV_DISABLE) {
		smap->flags &= ~SMAP_F_TXDNV_DISABLE;
		SMAPREG16(smap,SMAP_INTR_ENABLE) |= INTR_TXDNV;
	}

	/* renew write pointer & buffer descriptor */
	smap->txbwp = SMAP_TXBUFBASE +
				((smap->txbwp + txlen)%SMAP_TXBUFBASE);
	SMAP_BD_NEXT(smap->txbds);

	/* Tell the upper layer */
	// sc->funs->eth_drv->tx_done(sc, key, 1);

end:
	irq_restore(flags);
}

void smap_loop() {
	uint32 old = irq_disable();
	while (!escape_loop)
		smap_poll();
	escape_loop = 0;
	irq_restore(old);
}
