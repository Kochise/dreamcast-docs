/* Sample formats */
#define MODE_16BIT 0
#define MODE_8BIT  1
#define MODE_ADPCM 3

/* Volume 0 is max, higher is lower */
#define VOL_MAX    0x00
#define VOL_MIN    0xff

/* Pan is 5 bit sign-value (it seems) */
#define PAN_LEFT   0x1f
#define PAN_RIGHT  0x0f
#define PAN_CENTER 0x00

/* Prototypes */
extern void aica_reset(void);
extern void play_sound(int channel, void *data, int mode, int nsamp, int freq,
		       int vol, int pan);
extern void stop_sound(int channel);
