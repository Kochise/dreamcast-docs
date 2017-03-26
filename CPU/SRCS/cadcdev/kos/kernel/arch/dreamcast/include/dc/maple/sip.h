/* KallistiOS ##version##

   dc/maple/sip.h
   Copyright (C) 2005 Lawrence Sebald

*/

#ifndef __DC_MAPLE_SIP_H
#define __DC_MAPLE_SIP_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <sys/types.h>

/* This driver controls the Sound Input Peripheral for the maple
   bus (the microphone). Many thanks go out to ZeZu for pointing
   me towards what some commands actually do.
*/

/* SIP Status structure */
typedef struct	sip_state {
	uint8           amp_gain;
	uint8           is_sampling;
	size_t          buf_len;
	off_t           buf_pos;
	uint8          *samples_buf;
} sip_state_t;

/* The maximum gain value to be passed to the function
   below. */
#define SIP_MAX_GAIN 0x1F

/* Set the amplifier's gain. This should only be called prior
   to sampling, to ensure that the sound returned is of the
   same volume. */
int sip_set_gain(maple_device_t *dev, uint8 g);

/* Start sampling. */
int sip_start_sampling(maple_device_t *dev);

/* Stop sampling. */
int sip_stop_sampling(maple_device_t *dev);

/* Get samples out of the buffer. This can ONLY be called after
   sampling has been stopped. Returns the size in bytes of the
   filled buffer. */
int sip_get_samples(maple_device_t *dev, uint8 *buf, size_t len);

/* Clear the internal sample buffer. */
int sip_clear_samples(maple_device_t *dev);

/* Init / Shutdown */
int sip_init();
void sip_shutdown();

__END_DECLS

#endif	/* __DC_MAPLE_SIP_H */

