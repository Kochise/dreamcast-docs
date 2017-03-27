/*
 * Dreamroq by Mike Melanson
 *
 * This is the header file to be included in the programs wishing to
 * use the Dreamroq playback engine.
 */

#ifndef NEWROQ_H
#define NEWROQ_H

#define ROQ_SUCCESS           0
#define ROQ_FILE_OPEN_FAILURE 1
#define ROQ_FILE_READ_FAILURE 2
#define ROQ_CHUNK_TOO_LARGE   3
#define ROQ_BAD_CODEBOOK      4
#define ROQ_INVALID_PIC_SIZE  5
#define ROQ_NO_MEMORY         6
#define ROQ_BAD_VQ_STREAM     7
#define ROQ_INVALID_DIMENSION 8
#define ROQ_RENDER_PROBLEM    9
#define ROQ_CLIENT_PROBLEM    10

/* The library calls this function when it has a frame ready for display. */
typedef int (*render_callback)(unsigned short *buf, int width, int height,
    int stride, int texture_height);

/* The library calls this function when it has pcm samples ready for output. */
typedef int (*audio_callback)(unsigned char *buf, int samples, int channels);

/* The library calls this function to ask whether it should quit playback.
 * Return non-zero if it's time to quite. */
typedef int (*quit_callback)();

int dreamroq_play(char *filename, int loop, render_callback render_cb,
                  audio_callback audio_cb, quit_callback quit_cb);

#endif  /* NEWROQ_H */
