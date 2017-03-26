/*
 * Plays J.S.Bach's BWV784 (Invention 13)
 *
 * Rather poorly...
 *
 * Code by marcus
 * MIDI data from http://www.midiworld.com/
 */


#include "aica.h"

/* Number of samples in the waveform */
#define WAVE_LEN 16

/* A MIDI note event (sort of) */
struct note {
  unsigned short time;
  signed char note, velocity;
};


#define MUSIC invention13
#include "bwv784.h"


static void __gccmain() { }

/* Multiply note frequencies with waveform length to get replay freq */
#define HZ(n) ((int)((n)*WAVE_LEN))


/* Which channel is playing each note */
signed char note_to_channel[128];

/* Which note is each channel playing */
signed char channel_to_note[64];


/* MIDI note frequency table */
const int note_to_hz[128] = {
  HZ(8.1757989156), HZ(8.6619572180), HZ(9.1770239974), HZ(9.7227182413),
  HZ(10.3008611535), HZ(10.9133822323), HZ(11.5623257097), HZ(12.2498573744),
  HZ(12.9782717994), HZ(13.7500000000), HZ(14.5676175474), HZ(15.4338531643),
  HZ(16.3515978313), HZ(17.3239144361), HZ(18.3540479948), HZ(19.4454364826),
  HZ(20.6017223071), HZ(21.8267644646), HZ(23.1246514195), HZ(24.4997147489),
  HZ(25.9565435987), HZ(27.5000000000), HZ(29.1352350949), HZ(30.8677063285),
  HZ(32.7031956626), HZ(34.6478288721), HZ(36.7080959897), HZ(38.8908729653),
  HZ(41.2034446141), HZ(43.6535289291), HZ(46.2493028390), HZ(48.9994294977),
  HZ(51.9130871975), HZ(55.0000000000), HZ(58.2704701898), HZ(61.7354126570),
  HZ(65.4063913251), HZ(69.2956577442), HZ(73.4161919794), HZ(77.7817459305),
  HZ(82.4068892282), HZ(87.3070578583), HZ(92.4986056779), HZ(97.9988589954),
  HZ(103.8261743950), HZ(110.0000000000), HZ(116.5409403795), HZ(123.4708253140),
  HZ(130.8127826503), HZ(138.5913154884), HZ(146.8323839587), HZ(155.5634918610),
  HZ(164.8137784564), HZ(174.6141157165), HZ(184.9972113558), HZ(195.9977179909),
  HZ(207.6523487900), HZ(220.0000000000), HZ(233.0818807590), HZ(246.9416506281),
  HZ(261.6255653006), HZ(277.1826309769), HZ(293.6647679174), HZ(311.1269837221),
  HZ(329.6275569129), HZ(349.2282314330), HZ(369.9944227116), HZ(391.9954359817),
  HZ(415.3046975799), HZ(440.0000000000), HZ(466.1637615181), HZ(493.8833012561),
  HZ(523.2511306012), HZ(554.3652619537), HZ(587.3295358348), HZ(622.2539674442),
  HZ(659.2551138257), HZ(698.4564628660), HZ(739.9888454233), HZ(783.9908719635),
  HZ(830.6093951599), HZ(880.0000000000), HZ(932.3275230362), HZ(987.7666025122),
  HZ(1046.5022612024), HZ(1108.7305239075), HZ(1174.6590716696), HZ(1244.5079348883),
  HZ(1318.5102276515), HZ(1396.9129257320), HZ(1479.9776908465), HZ(1567.9817439270),
  HZ(1661.2187903198), HZ(1760.0000000000), HZ(1864.6550460724), HZ(1975.5332050245),
  HZ(2093.0045224048), HZ(2217.4610478150), HZ(2349.3181433393), HZ(2489.0158697766),
  HZ(2637.0204553030), HZ(2793.8258514640), HZ(2959.9553816931), HZ(3135.9634878540),
  HZ(3322.4375806396), HZ(3520.0000000000), HZ(3729.3100921447), HZ(3951.0664100490),
  HZ(4186.0090448096), HZ(4434.9220956300), HZ(4698.6362866785), HZ(4978.0317395533),
  HZ(5274.0409106059), HZ(5587.6517029281), HZ(5919.9107633862), HZ(6271.9269757080),
  HZ(6644.8751612791), HZ(7040.0000000000), HZ(7458.6201842894), HZ(7902.1328200980),
  HZ(8372.0180896192), HZ(8869.8441912599), HZ(9397.2725733570), HZ(9956.0634791066),
  HZ(10548.0818212118), HZ(11175.3034058561), HZ(11839.8215267723), HZ(12543.8539514160),
};


/* The program is short enough to place the waveform here.
   This is after the stack anyway (see base.s).            */
signed char *waveform = (void*)0x10000;

/* Start playing a note */
void note_on(int n, int v)
{
  int c;

  if(note_to_channel[n]>=0)
    return;

  for(c=0; c<64; c++)
    if(channel_to_note[c]<0)
      break;
  if(c>=64)
    return;

  play_sound(c, waveform, MODE_8BIT, WAVE_LEN, note_to_hz[n],
	     VOL_MAX, PAN_CENTER);
  note_to_channel[n] = c;
  channel_to_note[c] = n;
}

/* Stop playing a note */
void note_off(int n)
{
  int c;
  if((c=note_to_channel[n])<0)
    return;
  stop_sound(c);
  note_to_channel[n] = -1;
  channel_to_note[c] = -1;
}


int main()
{
  int i;
  extern volatile unsigned int timer;

  /* Initialize sound hardware */
  aica_reset();

  /* Generate a nice(?) sawtooth waveform */
  for(i=0; i<WAVE_LEN; i++)
    waveform[i] = 256*i/WAVE_LEN-128;
  waveform[WAVE_LEN] = waveform[0];

  /* Initialize tables */
  for(i=0; i<128; i++)
    note_to_channel[i] = -1;
  for(i=0; i<64; i++)
    channel_to_note[i] = -1;

  /* Reset the interrupt driven timer */
  timer = 0;

  for(i = 0; i<sizeof(MUSIC)/sizeof(MUSIC[0]); i++) {
    struct note n = MUSIC[i];
    int t = n.time * 3;

    /* Wait for the events designated time */
    while(timer < t);

    /* Execute event */
    if(n.note<0)
      note_off(-n.note);
    else
      note_on(n.note, n.velocity);
  }

  /* Make sure all notes are released, just in case */
  for(i=0; i<128; i++)
    note_off(i);

}
