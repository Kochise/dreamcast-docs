/* KallistiOS ##version##

   sip.c
   Copyright (C) 2005 Lawrence Sebald
*/

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <kos/genwait.h>
#include <dc/maple.h>
#include <dc/maple/sip.h>

static void sip_generic_cb(maple_frame_t *frame)	{
	/* Unlock the frame */
	maple_frame_unlock(frame);
	
	/* Wake up! */
	genwait_wake_all(frame);
}

int sip_set_gain(maple_device_t *dev, uint8 g)	{
	sip_state_t *sip;

	assert( dev != NULL );
	
	sip = (sip_state_t *)dev->status;

	/* Check the gain value for validity */
	if(g > 0x1F)
		return MAPLE_EINVALID;

	sip->amp_gain = g;

	return MAPLE_EOK;
}

int sip_start_sampling(maple_device_t *dev)	{
	sip_state_t *sip;
	uint32 *send_buf;
	
	assert( dev != NULL );
	
	sip = (sip_state_t *)dev->status;
	
	/* Make sure we aren't yet sampling */
	if(sip->is_sampling)
		return MAPLE_EFAIL;
	
	/* Lock the frame */
	if(maple_frame_lock(&dev->frame) < 0)
		return MAPLE_EAGAIN;
	
	/* Reset the frame */
	maple_frame_init(&dev->frame);
	send_buf = (uint32 *)dev->frame.recv_buf;
	send_buf[0] = MAPLE_FUNC_MICROPHONE;
	send_buf[1] = 0x02 | (0x80 << 8); /* Start sampling */
	dev->frame.cmd = MAPLE_COMMAND_MICCONTROL;
	dev->frame.dst_port = dev->port;
	dev->frame.dst_unit = dev->unit;
	dev->frame.length = 2;
	dev->frame.callback = sip_generic_cb;
	dev->frame.send_buf = send_buf;
	maple_queue_frame(&dev->frame);
	
	/* Wait for the SIP to accept it */
	if(genwait_wait(&dev->frame, "sip_start_sampling", 500, NULL) < 0) {
		if(dev->frame.state != MAPLE_FRAME_VACANT)	{
			/* Something went wrong.... */
			dev->frame.state = MAPLE_FRAME_VACANT;
			dbglog(DBG_ERROR, "sip_start_sampling: timeout to unit %c%c\n",
			       dev->port + 'A', dev->unit + '0');
			return MAPLE_ETIMEOUT;
		}
	}
	
	sip->is_sampling = 1;
	
	return MAPLE_EOK;
}

int sip_stop_sampling(maple_device_t *dev)	{
	sip_state_t *sip;
	uint32 *send_buf;

	assert( dev != NULL );

	sip = (sip_state_t *)dev->status;

	/* Make sure we actually are sampling */
	if(!sip->is_sampling)
		return MAPLE_EFAIL;

	/* Lock the frame */
	if(maple_frame_lock(&dev->frame) < 0)
		return MAPLE_EAGAIN;

	/* Reset the frame */
	maple_frame_init(&dev->frame);
	send_buf = (uint32 *)dev->frame.recv_buf;
	send_buf[0] = MAPLE_FUNC_MICROPHONE;
	send_buf[1] = 0x02; /* Stop sampling */
	dev->frame.cmd = MAPLE_COMMAND_MICCONTROL;
	dev->frame.dst_port = dev->port;
	dev->frame.dst_unit = dev->unit;
	dev->frame.length = 2;
	dev->frame.callback = sip_generic_cb;
	dev->frame.send_buf = send_buf;
	maple_queue_frame(&dev->frame);

	/* Wait for the SIP to accept it */
	if(genwait_wait(&dev->frame, "sip_stop_sampling", 500, NULL) < 0) {
		if(dev->frame.state != MAPLE_FRAME_VACANT)	{
			/* Something went wrong.... */
			dev->frame.state = MAPLE_FRAME_VACANT;
			dbglog(DBG_ERROR, "sip_stop_sampling: timeout to unit %c%c\n",
			       dev->port + 'A', dev->unit + '0');
			return MAPLE_ETIMEOUT;
		}
	}

	sip->is_sampling = 0;

	return MAPLE_EOK;
}

int sip_get_samples(maple_device_t *dev, uint8 *buf, size_t len)	{
	sip_state_t *sip;
	size_t sz;

	sip = (sip_state_t *)dev->status;

	if(sip->is_sampling)
		return MAPLE_EFAIL;

	sz = sip->buf_pos > len ? len : sip->buf_pos;

	memcpy(buf, sip->samples_buf, sz);

	if(sz == sip->buf_pos)	{
		sip->buf_pos = 0;
	}
	else	{
		memcpy(sip->samples_buf + sz, sip->samples_buf, sip->buf_pos - sz);
		sip->buf_pos -= sz;
	}

	return sz;
}

int sip_clear_samples(maple_device_t *dev)	{
	sip_state_t *sip;

	sip = (sip_state_t *)dev->status;

	if(sip->is_sampling)
		return MAPLE_EFAIL;

	sip->buf_pos = 0;

	return MAPLE_EOK;
}

static void sip_reply(maple_frame_t *frm)	{
	maple_response_t *resp;
	uint32 *respbuf;
	size_t sz, i;
	sip_state_t *sip;
	
	/* Unlock the frame now (it's ok, we're in an IRQ) */
	maple_frame_unlock(frm);
	
	/* Make sure we got a valid response */
	resp = (maple_response_t *)frm->recv_buf;
	
	if (resp->response != MAPLE_RESPONSE_DATATRF)
		return;
	respbuf = (uint32 *)resp->data;
	if (respbuf[0] != MAPLE_FUNC_MICROPHONE)
		return;
	
	if(frm->dev)	{
		sip = (sip_state_t *)frm->dev->status;
		frm->dev->status_valid = 1;

		if(sip->is_sampling)	{
			sz = resp->data_len * 4 - 8;

			/* Make sure we don't overflow the buffer */
			if(sz + sip->buf_pos <= sip->buf_len)	{
				for(i = 0; i < sz; i++)	{
					sip->samples_buf[i + sip->buf_pos] = resp->data[i + 8];
				}
				sip->buf_pos += sz;
			}
		}
	}
}


static int sip_poll(maple_device_t *dev)	{
	sip_state_t *sip;
	uint32 *send_buf;

	/* Test to make sure that the particular mic is enabled */
	sip = (sip_state_t *)dev->status;

	/* Lock the frame, or die trying */
	if(maple_frame_lock(&dev->frame) < 0)
		return 0;

	maple_frame_init(&dev->frame);
	send_buf = (uint32 *)dev->frame.recv_buf;
	send_buf[0] = MAPLE_FUNC_MICROPHONE;
	send_buf[1] = 0x01 | (sip->amp_gain << 8); /* Get samples/status */
	dev->frame.cmd = MAPLE_COMMAND_MICCONTROL;
	dev->frame.dst_port = dev->port;
	dev->frame.dst_unit = dev->unit;
	dev->frame.length = 2;
	dev->frame.callback = sip_reply;
	dev->frame.send_buf = send_buf;
	maple_queue_frame(&dev->frame);

	return 0;
}

static void sip_periodic(maple_driver_t *drv) {
	maple_driver_foreach(drv, sip_poll);
}

static int sip_attach(maple_driver_t *drv, maple_device_t *dev) {
	sip_state_t *sip;

	/* Allocate the sample buffer for 10 seconds worth of samples */
	sip = (sip_state_t *)dev->status;
	sip->is_sampling = 0;
	sip->amp_gain = 0;
	sip->buf_pos = 0;
	sip->samples_buf = (uint8 *)malloc(11025 * 2 * 10);

	if(sip->samples_buf == NULL)	{
		dev->status_valid = 0;
		sip->buf_len = 0;
		return -1;
	}
	else	{
		dev->status_valid = 1;
		sip->buf_len = 11025 * 2 * 10;
		return 0;
	}
}

static void sip_detach(maple_driver_t *drv, maple_device_t *dev) {
	sip_state_t *sip;

	sip = (sip_state_t *)dev->status;
	free(sip->samples_buf);
}

/* Device Driver Struct */
static maple_driver_t sip_drv = {
	functions:	MAPLE_FUNC_MICROPHONE,
	name:		"Sound Input Peripheral",
	periodic:	sip_periodic,
	attach:		sip_attach,
	detach:		sip_detach
};

/* Add the SIP to the driver chain */
int sip_init() {
	return maple_driver_reg(&sip_drv);
}

void sip_shutdown() {
	maple_driver_unreg(&sip_drv);
}

