/*
 * Dreamroq by Mike Melanson
 * Updated by Josh Pearson to add audio support
 * 
 * This is the main playback engine.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dreamroqlib.h"

#define RoQ_INFO           0x1001
#define RoQ_QUAD_CODEBOOK  0x1002
#define RoQ_QUAD_VQ        0x1011
#define RoQ_SOUND_MONO     0x1020
#define RoQ_SOUND_STEREO   0x1021
#define RoQ_SIGNATURE      0x1084

#define CHUNK_HEADER_SIZE 8

#define LE_16(buf) (*buf | (*(buf+1) << 8))
#define LE_32(buf) (*buf | (*(buf+1) << 8) | (*(buf+2) << 16) | (*(buf+3) << 24))

#define MAX_BUF_SIZE (64 * 1024)

#define ROQ_CODEBOOK_SIZE 256

struct roq_audio
{
     int pcm_samples;
     int channels;
     int position;
     short snd_sqr_arr[260];
     unsigned char pcm_sample[MAX_BUF_SIZE];
}roq_audio;

typedef struct
{
    int width;
    int height;
    int mb_width;
    int mb_height;
    int mb_count;

    int current_frame;
    unsigned short *frame[2];
    int stride;
    int texture_height;

    unsigned short cb2x2[ROQ_CODEBOOK_SIZE][4];
    unsigned short cb4x4[ROQ_CODEBOOK_SIZE][16];
} roq_state;



static int roq_unpack_quad_codebook(unsigned char *buf, int size, int arg, 
    roq_state *state)
{
    int y[4];
    int yp, u, v;
    int r, g, b;
    int count2x2;
    int count4x4;
    int i, j;
    unsigned short *v2x2;
    unsigned short *v4x4;

    count2x2 = (arg >> 8) & 0xFF;
    count4x4 =  arg       & 0xFF;

    if (!count2x2)
        count2x2 = ROQ_CODEBOOK_SIZE;
    /* 0x00 means 256 4x4 vectors iff there is enough space in the chunk
     * after accounting for the 2x2 vectors */
    if (!count4x4 && count2x2 * 6 < size)
        count4x4 = ROQ_CODEBOOK_SIZE;

    /* size sanity check */
    if ((count2x2 * 6 + count4x4 * 4) != size)
    {
        return ROQ_BAD_CODEBOOK;
    }

    /* unpack the 2x2 vectors */
    for (i = 0; i < count2x2; i++)
    {
        /* unpack the YUV components from the bytestream */
        for (j = 0; j < 4; j++)
            y[j] = *buf++;
        u  = *buf++;
        v  = *buf++;

        /* convert to RGB565 */
        for (j = 0; j < 4; j++)
        {
            yp = (y[j] - 16) * 1.164;
            r = (yp + 1.596 * (v - 128)) / 8;
            g = (yp - 0.813 * (v - 128) - 0.391 * (u - 128)) / 4;
            b = (yp + 2.018 * (u - 128)) / 8;

            if (r < 0) r = 0;
            if (r > 31) r = 31;
            if (g < 0) g = 0;
            if (g > 63) g = 63;
            if (b < 0) b = 0;
            if (b > 31) b = 31;

            state->cb2x2[i][j] = (
                (r << 11) | 
                (g <<  5) |
                (b <<  0) );
        }
    }

    /* unpack the 4x4 vectors */
    for (i = 0; i < count4x4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            v2x2 = state->cb2x2[*buf++];
            v4x4 = state->cb4x4[i] + (j / 2) * 8 + (j % 2) * 2;
            v4x4[0] = v2x2[0];
            v4x4[1] = v2x2[1];
            v4x4[4] = v2x2[2];
            v4x4[5] = v2x2[3];
        }
    }

    return ROQ_SUCCESS;
}

#define GET_BYTE(x) \
    if (index >= size) { \
        status = ROQ_BAD_VQ_STREAM; \
        x = 0; \
    } else { \
        x = buf[index++]; \
    }

#define GET_MODE() \
    if (!mode_count) { \
        GET_BYTE(mode_lo); \
        GET_BYTE(mode_hi); \
        mode_set = (mode_hi << 8) | mode_lo; \
        mode_count = 16; \
    } \
    mode_count -= 2; \
    mode = (mode_set >> mode_count) & 0x03;

static int roq_unpack_vq(unsigned char *buf, int size, unsigned int arg, 
    roq_state *state)
{
    int status = ROQ_SUCCESS;
    int mb_x, mb_y;
    int block;     /* 8x8 blocks */
    int subblock;  /* 4x4 blocks */
    int stride = state->stride;
    int i;

    /* frame and pixel management */
    unsigned short *this_frame;
    unsigned short *last_frame;

    int line_offset;
    int mb_offset;
    int block_offset;
    int subblock_offset;

    unsigned short *this_ptr;
    unsigned int *this_ptr32;
    unsigned short *last_ptr;
    /*unsigned int *last_ptr32;*/
    unsigned short *vector16;
    unsigned int *vector32;
    int stride32 = stride / 2;

    /* bytestream management */
    int index = 0;
    int mode_set = 0;
    int mode, mode_lo, mode_hi;
    int mode_count = 0;

    /* vectors */
    int mx, my;
    int motion_x, motion_y;
    unsigned char data_byte;

    mx = (arg >> 8) & 0xFF;
    my =  arg       & 0xFF;

    if (state->current_frame == 1)
    {
        state->current_frame = 0;
        this_frame = state->frame[0];
        last_frame = state->frame[1];
    }
    else
    {
        state->current_frame = 1;
        this_frame = state->frame[1];
        last_frame = state->frame[0];
    }

    for (mb_y = 0; mb_y < state->mb_height && status == ROQ_SUCCESS; mb_y++)
    {
        line_offset = mb_y * 16 * stride;
        for (mb_x = 0; mb_x < state->mb_width && status == ROQ_SUCCESS; mb_x++)
        {
            mb_offset = line_offset + mb_x * 16;
            for (block = 0; block < 4 && status == ROQ_SUCCESS; block++)
            {
                block_offset = mb_offset + (block / 2 * 8 * stride) + (block % 2 * 8);
                /* each 8x8 block gets a mode */
                GET_MODE();
                switch (mode)
                {
                case 0:  /* MOT: skip */
                    break;

                case 1:  /* FCC: motion compensation */
                    /* this needs to be done 16 bits at a time due to
                     * data alignment issues on the SH-4 */
                    GET_BYTE(data_byte);
                    motion_x = 8 - (data_byte >>  4) - mx;
                    motion_y = 8 - (data_byte & 0xF) - my;
                    last_ptr = last_frame + block_offset + 
                        (motion_y * stride) + motion_x;
                    this_ptr = this_frame + block_offset;
                    for (i = 0; i < 8; i++)
                    {
                        *this_ptr++ = *last_ptr++;
                        *this_ptr++ = *last_ptr++;
                        *this_ptr++ = *last_ptr++;
                        *this_ptr++ = *last_ptr++;
                        *this_ptr++ = *last_ptr++;
                        *this_ptr++ = *last_ptr++;
                        *this_ptr++ = *last_ptr++;
                        *this_ptr++ = *last_ptr++;

                        last_ptr += stride - 8;
                        this_ptr += stride - 8;
                    }
                    break;

                case 2:  /* SLD: upsample 4x4 vector */
                    GET_BYTE(data_byte);
                    vector16 = state->cb4x4[data_byte];
                    for (i = 0; i < 4*4; i++)
                    {
                        this_ptr = this_frame + block_offset +
                            (i / 4 * 2 * stride) + (i % 4 * 2);
                        this_ptr[0] = *vector16;
                        this_ptr[1] = *vector16;
                        this_ptr[stride+0] = *vector16;
                        this_ptr[stride+1] = *vector16;
						vector16++;
                    }
                    break;

                case 3:  /* CCC: subdivide into 4 subblocks */
                    for (subblock = 0; subblock < 4; subblock++)
                    {
                        subblock_offset = block_offset + (subblock / 2 * 4 * stride) + (subblock % 2 * 4);

                        GET_MODE();
                        switch (mode)
                        {
                        case 0:  /* MOT: skip */
						break;

                        case 1:  /* FCC: motion compensation */
                            GET_BYTE(data_byte);
                            motion_x = 8 - (data_byte >>  4) - mx;
                            motion_y = 8 - (data_byte & 0xF) - my;
                            last_ptr = last_frame + subblock_offset + 
                                (motion_y * stride) + motion_x;
                            this_ptr = this_frame + subblock_offset;
                            for (i = 0; i < 4; i++)
                            {
                                *this_ptr++ = *last_ptr++;
                                *this_ptr++ = *last_ptr++;
                                *this_ptr++ = *last_ptr++;
                                *this_ptr++ = *last_ptr++;

                                last_ptr += stride - 4;
                                this_ptr += stride - 4;
                            }
                            break;

                        case 2:  /* SLD: use 4x4 vector from codebook */
                            GET_BYTE(data_byte);
                            vector32 = (unsigned int*)state->cb4x4[data_byte];

                            this_ptr32 = (unsigned int*)this_frame;
                            this_ptr32 += subblock_offset / 2;
                            for (i = 0; i < 4; i++)
                            {
                                *this_ptr32++ = *vector32++;
                                *this_ptr32++ = *vector32++;


                                this_ptr32 += stride32 - 2;
                            }
                            break;

                        case 3:  /* CCC: subdivide into 4 subblocks */
                            GET_BYTE(data_byte);
                            vector16 = state->cb2x2[data_byte];
                            this_ptr = this_frame + subblock_offset;


                            this_ptr[0] = vector16[0];
                            this_ptr[1] = vector16[1];
                            this_ptr[stride+0] = vector16[2];
                            this_ptr[stride+1] = vector16[3];

                            GET_BYTE(data_byte);
                            vector16 = state->cb2x2[data_byte];


                            this_ptr[2] = vector16[0];
                            this_ptr[3] = vector16[1];
                            this_ptr[stride+2] = vector16[2];
                            this_ptr[stride+3] = vector16[3];

                            this_ptr += stride * 2;

                            GET_BYTE(data_byte);
                            vector16 = state->cb2x2[data_byte];


                            this_ptr[0] = vector16[0];
                            this_ptr[1] = vector16[1];
                            this_ptr[stride+0] = vector16[2];
                            this_ptr[stride+1] = vector16[3];

                            GET_BYTE(data_byte);
                            vector16 = state->cb2x2[data_byte];


                            this_ptr[2] = vector16[0];
                            this_ptr[3] = vector16[1];
                            this_ptr[stride+2] = vector16[2];
                            this_ptr[stride+3] = vector16[3];

                            break;
                        }
                    }
                    break;
                }
            }
        }
    }

    /* sanity check to see if the stream was fully consumed */
    if (status == ROQ_SUCCESS && index < size-2)
    {
        status = ROQ_BAD_VQ_STREAM;
    }

    return status;
}

int dreamroq_play(char *filename, int loop, render_callback render_cb,
                  audio_callback audio_cb, quit_callback quit_cb)
{
    FILE *f;
    size_t file_ret;
    int framerate;
    int chunk_id;
    unsigned int chunk_size;
    unsigned int chunk_arg;
    roq_state state;
    int status;
    int initialized = 0;
    unsigned char read_buffer[MAX_BUF_SIZE];
    int i, snd_left, snd_right;

    f = fopen(filename, "rb");
    if (!f)
        return ROQ_FILE_OPEN_FAILURE;

    file_ret = fread(read_buffer, CHUNK_HEADER_SIZE, 1, f);
    if (file_ret != 1)
    {
        fclose(f);
        printf("\nROQ_FILE_READ_FAILURE\n\n");
        return ROQ_FILE_READ_FAILURE;
        
    }
    chunk_id   = LE_16(&read_buffer[0]);
    chunk_size = LE_32(&read_buffer[2]);
    if (chunk_id != RoQ_SIGNATURE || chunk_size != 0xFFFFFFFF)
    {
        fclose(f);
        return ROQ_FILE_READ_FAILURE;
    }
    framerate = LE_16(&read_buffer[6]);
    printf("RoQ file plays at %d frames/sec\n", framerate);
	
    /* Initialize Audio SQRT Look-Up Table */
    for(i = 0; i < 128; i++)
    {
        roq_audio.snd_sqr_arr[i] = i * i;
        roq_audio.snd_sqr_arr[i + 128] = -(roq_audio.snd_sqr_arr[i]);
    }

    status = ROQ_SUCCESS;
    while (!feof(f) && status == ROQ_SUCCESS)
    {
        /* if client program defined a quit callback, check if it's time
         * to quit */
        if (quit_cb && quit_cb())
            break;

        file_ret = fread(read_buffer, CHUNK_HEADER_SIZE, 1, f);
        #ifdef FPSGRAPH
                printf("r\n");
        #endif
        if (file_ret != 1)
        {
            /* if the read failed but the file is not EOF, there is a deeper
             * problem; don't entertain the idea of looping */
            if (!feof(f))
                break;
            else if (loop)
            {
                /* it shouldn't be necessary to close and re-open the file
                 * here; however, this works around a bug in KOS 1.2.0 in
                 * which seeking back doesn't clear the EOF flag */
                //fclose(f);
                //f = fopen(filename, "rb");
                if (!f)
                    status = ROQ_FILE_OPEN_FAILURE;
                else
                {
                    /* skip the signature header */
                    fseek(f, 8, SEEK_SET);
                    continue;
                }
            }
            else
                break;
        }

        chunk_id   = LE_16(&read_buffer[0]);
        chunk_size = LE_32(&read_buffer[2]);
        chunk_arg  = LE_16(&read_buffer[6]);

        if (chunk_size > MAX_BUF_SIZE)
        {
            fclose(f);
            return ROQ_CHUNK_TOO_LARGE;
        }
	
        file_ret = fread(read_buffer, chunk_size, 1, f);
        if (file_ret != 1)
        {
            status = ROQ_FILE_READ_FAILURE;
            break;
        }
            
        switch(chunk_id)
        {
        case RoQ_INFO:
            if (initialized)
                continue;

            state.width = LE_16(&read_buffer[0]);
            state.height = LE_16(&read_buffer[2]);
            /* width and height each need to be divisible by 16 */
            if ((state.width & 0xF) || (state.height & 0xF))
            {
                status = ROQ_INVALID_PIC_SIZE;
                break;
            }
            state.mb_width = state.width / 16;
            state.mb_height = state.height / 16;
            state.mb_count = state.mb_width * state.mb_height;
            if (state.width < 8 || state.width > 1024)
                status = ROQ_INVALID_DIMENSION;
            else
            {
                state.stride = 8;
                while (state.stride < state.width)
                    state.stride <<= 1;
            }
            if (state.height < 8 || state.height > 1024)
                status = ROQ_INVALID_DIMENSION;
            else
            {
                state.texture_height = 8;
                while (state.texture_height < state.height)
                    state.texture_height <<= 1;
            }
            
            printf("  RoQ_INFO: dimensions = %dx%d, %dx%d; %d mbs, texture = %dx%d\n", 
                state.width, state.height, state.mb_width, state.mb_height,
                state.mb_count, state.stride, state.texture_height);
            
            state.frame[0] = (unsigned short*)memalign(32,state.texture_height * state.stride * sizeof(unsigned short));
            state.frame[1] = (unsigned short*)memalign(32,state.texture_height * state.stride * sizeof(unsigned short));
            state.current_frame = 0;
            if (!state.frame[0] || !state.frame[1])
            {
                free (state.frame[0]);
                free (state.frame[1]);
                status = ROQ_NO_MEMORY;
                break;
            }
            memset(state.frame[0], 0, state.texture_height * state.stride * sizeof(unsigned short));
            memset(state.frame[1], 0, state.texture_height * state.stride * sizeof(unsigned short));

            /* set this flag so that this code is not executed again when
             * looping */
            initialized = 1;
            break;

        case RoQ_QUAD_CODEBOOK:
            status = roq_unpack_quad_codebook(read_buffer, chunk_size, 
                chunk_arg, &state);
            break;

        case RoQ_QUAD_VQ:
            status = roq_unpack_vq(read_buffer, chunk_size, 
                chunk_arg, &state);
            if (render_cb)
                status = render_cb(state.frame[state.current_frame], 
                    state.width, state.height, state.stride, state.texture_height);
            break;

        case RoQ_SOUND_MONO:
            roq_audio.channels = 1;
            roq_audio.pcm_samples = chunk_size*2;
		    snd_left = chunk_arg;
		    for(i = 0; i < chunk_size; i++)
			{
			    snd_left += roq_audio.snd_sqr_arr[read_buffer[i]];
			    roq_audio.pcm_sample[i * 2] = snd_left & 0xff;
			    roq_audio.pcm_sample[i * 2 + 1] = (snd_left & 0xff00) >> 8;
			}
            if (audio_cb)
                status = audio_cb( roq_audio.pcm_sample, roq_audio.pcm_samples,
                                   roq_audio.channels ); 
            break;

        case RoQ_SOUND_STEREO:
            roq_audio.channels = 2;
            roq_audio.pcm_samples = chunk_size*2;
		    snd_left = (chunk_arg & 0xFF00);
		    snd_right = (chunk_arg & 0xFF) << 8;
		    for(i = 0; i < chunk_size; i += 2)
			{
			    snd_left  += roq_audio.snd_sqr_arr[read_buffer[i]];
			    snd_right += roq_audio.snd_sqr_arr[read_buffer[i+1]];
			    roq_audio.pcm_sample[i * 2] = snd_left & 0xff;
			    roq_audio.pcm_sample[i * 2 + 1] = (snd_left & 0xff00) >> 8;
			    roq_audio.pcm_sample[i * 2 + 2] =  snd_right & 0xff;
			    roq_audio.pcm_sample[i * 2 + 3] = (snd_right & 0xff00) >> 8;
			}
            if (audio_cb)
                status = audio_cb( roq_audio.pcm_sample, roq_audio.pcm_samples,
                                   roq_audio.channels );
            break;

        default:
            break;
        }
    }

    free(state.frame[0]);
    free(state.frame[1]);
    fclose(f);

    return status;
}

