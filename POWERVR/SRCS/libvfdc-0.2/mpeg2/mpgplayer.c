/****************************************************************************/
/*!
\par Project:  Video For DreamCast
\file          mpgplayer.c
\author        La Cible (la.cible@free.fr)
*/
/****************************************************************************/
/**
 * mpeg2 player
 */
#include <kos.h>
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
//#include <signal.h>
#include <inttypes.h>
#include <vfdc.h>
#include "mpeg2.h"
#include "video_out.h"
#include "convert.h"
#include "libads/ads.h"


#define BUFFER_SIZE 4096
static uint8_t buffer[BUFFER_SIZE];
static FILE * in_file=NULL;
static int demux_track_ads = 255; // << this is ads sound stream data  
static int demux_track_video = 0xe0;
static int demux_pid = 0;
static int demux_pva = 0;
static mpeg2dec_t * mpeg2dec;
static vo_open_t * output_open = NULL;
static vo_instance_t * output;
static char stop=0;
static char es_stream=0;

static void decode_mpeg2 (uint8_t * current, uint8_t * end)
{
    const mpeg2_info_t * info;
    int state;
    vo_setup_result_t setup_result;

    mpeg2_buffer (mpeg2dec, current, end);

    info = mpeg2_info (mpeg2dec);
    while (1) {
	state = mpeg2_parse (mpeg2dec);
	switch (state) {
	case -1:
	    return;
	case STATE_SEQUENCE:
	    /* might set nb fbuf, convert format, stride */
	    /* might set fbufs */
	    if (output->setup (output, info->sequence->width,
			       info->sequence->height, &setup_result)) {
		fprintf (stderr, "display setup failed\n");
		exit (1);
	    }
	    if (setup_result.convert)
		mpeg2_convert (mpeg2dec, setup_result.convert, NULL);
	    if (output->set_fbuf) {
		uint8_t * buf[3];
		void * id;

		mpeg2_custom_fbuf (mpeg2dec, 1);
		output->set_fbuf (output, buf, &id);
		mpeg2_set_buf (mpeg2dec, buf, id);
		output->set_fbuf (output, buf, &id);
		mpeg2_set_buf (mpeg2dec, buf, id);
	    } else if (output->setup_fbuf) {
		uint8_t * buf[3];
		void * id;

		output->setup_fbuf (output, buf, &id);
		mpeg2_set_buf (mpeg2dec, buf, id);
		output->setup_fbuf (output, buf, &id);
		mpeg2_set_buf (mpeg2dec, buf, id);
		output->setup_fbuf (output, buf, &id);
		mpeg2_set_buf (mpeg2dec, buf, id);
	    }
	    break;
	case STATE_PICTURE:
	    /* might skip */
	    /* might set fbuf */
	    if (output->set_fbuf) {
		uint8_t * buf[3];
		void * id;

		output->set_fbuf (output, buf, &id);
		mpeg2_set_buf (mpeg2dec, buf, id);
	    }
	    if (output->start_fbuf)
		output->start_fbuf (output, info->current_fbuf->buf,
				    info->current_fbuf->id);
	    break;
	case STATE_PICTURE_2ND:
	    /* should not do anything */
	    break;
	case STATE_SLICE:
	case STATE_END:
	    /* draw current picture */
	    /* might free frame buffer */
	    if (info->display_fbuf) {
		output->draw (output, info->display_fbuf->buf,
			      info->display_fbuf->id);
		//print_fps (0);
	    }
	    if (output->discard && info->discard_fbuf)
		output->discard (output, info->discard_fbuf->buf,
				 info->discard_fbuf->id);
	    break;
	}
    }
}

static char audio_open = 0;


static void play_sound(uint8_t * current, int32_t lenght)
{
	static char firtscall = 1;
	
	uint8_t * pData=NULL;
	
	if(firtscall && lenght>=40)
	{
		firtscall = 0;
		audio_open= ADS_Open(current);
		
		pData = current+40;
		lenght -=40;
		
	}
	else
	{
		pData = current;
	}
	
	if(audio_open)
		ADS_Write(pData,lenght);	

}

#define DEMUX_PAYLOAD_START 1
static int demux (uint8_t * buf, uint8_t * end, int flags)
{
    static int mpeg1_skip_table[16] = {
	0, 0, 4, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    /*
     * the demuxer keeps some state between calls:
     * if "state" = DEMUX_HEADER, then "head_buf" contains the first
     *     "bytes" bytes from some header.
     * if "state" == DEMUX_DATA, then we need to copy "bytes" bytes
     *     of ES data before the next header.
     * if "state" == DEMUX_SKIP, then we need to skip "bytes" bytes
     *     of data before the next header.
     *
     * NEEDBYTES makes sure we have the requested number of bytes for a
     * header. If we dont, it copies what we have into head_buf and returns,
     * so that when we come back with more data we finish decoding this header.
     *
     * DONEBYTES updates "buf" to point after the header we just parsed.
     */

#define DEMUX_HEADER 0
#define DEMUX_VIDEO_DATA 1
#define DEMUX_SKIP 2
#define DEMUX_AUDIO_ADSDATA 3
	
    static int state = DEMUX_SKIP;
    static int state_bytes = 0;
    static uint8_t head_buf[264];
    uint8_t * header;
    int bytes;
    int len;

	

#define NEEDBYTES(x)						\
    do {							\
	int missing;						\
								\
	missing = (x) - bytes;					\
	if (missing > 0) {					\
	    if (header == head_buf) {				\
		if (missing <= end - buf) {			\
		    memcpy (header + bytes, buf, missing);	\
		    buf += missing;				\
		    bytes = (x);				\
		} else {					\
		    memcpy (header + bytes, buf, end - buf);	\
		    state_bytes = bytes + end - buf;		\
		    return 0;					\
		}						\
	    } else {						\
		memcpy (head_buf, header, bytes);		\
		state = DEMUX_HEADER;				\
		state_bytes = bytes;				\
		return 0;					\
	    }							\
	}							\
    } while (0)

#define DONEBYTES(x)		\
    do {			\
	if (header != head_buf)	\
	    buf = header + (x);	\
    } while (0)

    if (flags & DEMUX_PAYLOAD_START)
	goto payload_start;
    switch (state) {
    case DEMUX_HEADER:
	if (state_bytes > 0) {
	    header = head_buf;
	    bytes = state_bytes;
	    goto continue_header;
	}
	break;
    case DEMUX_VIDEO_DATA:
	if (demux_pid || (state_bytes > end - buf)) {
	    decode_mpeg2 (buf, end);
	    state_bytes -= end - buf;
	    return 0;
	}
	decode_mpeg2 (buf, buf + state_bytes);
	buf += state_bytes;
	break;
	case DEMUX_AUDIO_ADSDATA: 
	if (demux_pid || (state_bytes > end - buf)) {
		play_sound (buf, end - buf);
		state_bytes -= end - buf;
		return 0;
	}
	play_sound (buf, state_bytes);
	buf += state_bytes;
	break;
    case DEMUX_SKIP:
	if (demux_pid || (state_bytes > end - buf)) {
	    state_bytes -= end - buf;
	    return 0;
	}
	buf += state_bytes;
	break;
    }

    while (1) {
	if (demux_pid) {
	    state = DEMUX_SKIP;
	    return 0;
	}
    payload_start:
	header = buf;
	bytes = end - buf;
    continue_header:
	NEEDBYTES (4);
	if (header[0] || header[1] || (header[2] != 1)) {
	    if (demux_pid) {
		state = DEMUX_SKIP;
		return 0;
	    } else if (header != head_buf) {
		buf++;
		goto payload_start;
	    } else {
		header[0] = header[1];
		header[1] = header[2];
		header[2] = header[3];
		bytes = 3;
		goto continue_header;
	    }
	}
	if (demux_pid) {
	    if ((header[3] >= 0xe0) && (header[3] <= 0xef))
		goto pes;
	    fprintf (stderr, "bad stream id %x\n", header[3]);
	    exit (1);
	}
	switch (header[3]) {
	case 0xb9:	/* program end code */
	    /* DONEBYTES (4); */
	    /* break;         */
	    return 1;
	case 0xba:	/* pack header */
	    NEEDBYTES (12);
	    if ((header[4] & 0xc0) == 0x40) {	/* mpeg2 */
		NEEDBYTES (14);
		len = 14 + (header[13] & 7);
		NEEDBYTES (len);
		DONEBYTES (len);
		/* header points to the mpeg2 pack header */
	    } else if ((header[4] & 0xf0) == 0x20) {	/* mpeg1 */
		DONEBYTES (12);
		/* header points to the mpeg1 pack header */
	    } else {
		fprintf (stderr, "weird pack header\n");
		exit (1);
	    }
	    break;


	case 0xbb: //?????? 
		NEEDBYTES (6);
		DONEBYTES (6);
		bytes = (header[4] << 8) + header[5];
		if (bytes > end - buf) {
			state = DEMUX_SKIP;
			state_bytes = bytes - (end - buf);
			return 0;
		}
		buf += bytes;
		break;

	case 0xbd: //ADS sound DATA 
		NEEDBYTES (7);
		if ((header[6] & 0xc0) == 0x80) {	/* mpeg2 */
			NEEDBYTES (9);
			len = 10 + header[8];
			NEEDBYTES (len);
			/* header points to the mpeg2 pes header */
		} else {	/* mpeg1 */
			len = 7;
			while ((header-1)[len] == 0xff) {
				len++;
				NEEDBYTES (len);
				if (len == 23) {
					fprintf (stderr, "too much stuffing\n");
					break;
				}
			}
			if (((header-1)[len] & 0xc0) == 0x40) {
				len += 2;
				NEEDBYTES (len);
			}
			len += mpeg1_skip_table[(header - 1)[len] >> 4] + 1;
			NEEDBYTES (len);
			/* header points to the mpeg1 pes header */
		}
		if ((!demux_pid) && ((header-1)[len] != demux_track_ads)) {
			DONEBYTES (len);
			bytes = 6 + (header[4] << 8) + header[5] - len;
			if (bytes <= 0)
				continue;
			if (bytes > end - buf) {
				state = DEMUX_SKIP;
				state_bytes = bytes - (end - buf);
				return 0;
			}
			buf += bytes;
		}
		len += 3;
		NEEDBYTES (len);
		DONEBYTES (len);
		bytes = 6 + (header[4] << 8) + header[5] - len;
		if (demux_pid || (bytes > end - buf)) {
			play_sound( buf, end - buf);
			state = DEMUX_AUDIO_ADSDATA;
			state_bytes = bytes - (end - buf);
			return 0;
		} else if (bytes <= 0)
			continue;
		play_sound (buf, bytes);
		buf += bytes;
		break;
		
		

	default:
	    if (header[3] == demux_track_video) {
	    pes:
		NEEDBYTES (7);
		if ((header[6] & 0xc0) == 0x80) {	/* mpeg2 */
		    NEEDBYTES (9);
		    len = 9 + header[8];
		    NEEDBYTES (len);
		    /* header points to the mpeg2 pes header */
		    if (header[7] & 0x80) {
			uint32_t pts;

			pts = (((buf[9] >> 1) << 30) |
			       (buf[10] << 22) | ((buf[11] >> 1) << 15) |
			       (buf[12] << 7) | (buf[13] >> 1));
			mpeg2_pts (mpeg2dec, pts);
		    }
		} else {	/* mpeg1 */
		    int len_skip;
		    uint8_t * ptsbuf;

		    len = 7;
		    while (header[len - 1] == 0xff) {
			len++;
			NEEDBYTES (len);
			if (len > 23) {
			    fprintf (stderr, "too much stuffing\n");
			    break;
			}
		    }
		    if ((header[len - 1] & 0xc0) == 0x40) {
			len += 2;
			NEEDBYTES (len);
		    }
		    len_skip = len;
		    len += mpeg1_skip_table[header[len - 1] >> 4];
		    NEEDBYTES (len);
		    /* header points to the mpeg1 pes header */
		    ptsbuf = header + len_skip;
		    if (ptsbuf[-1] & 0x20) {
			uint32_t pts;

			pts = (((ptsbuf[-1] >> 1) << 30) |
			       (ptsbuf[0] << 22) | ((ptsbuf[1] >> 1) << 15) |
			       (ptsbuf[2] << 7) | (ptsbuf[3] >> 1));
			mpeg2_pts (mpeg2dec, pts);
		    }
		}
		DONEBYTES (len);
		bytes = 6 + (header[4] << 8) + header[5] - len;
		if (demux_pid || (bytes > end - buf)) {
		    decode_mpeg2 (buf, end);
		    state = DEMUX_VIDEO_DATA;
		    state_bytes = bytes - (end - buf);
		    return 0;
		} else if (bytes > 0) {
		    decode_mpeg2 (buf, buf + bytes);
		    buf += bytes;
		}
	    } else if (header[3] < 0xb9) {
		es_stream = 1;
		fseek(in_file,0,SEEK_SET);
		return 1;
	    } else {
		NEEDBYTES (6);
		DONEBYTES (6);
		bytes = (header[4] << 8) + header[5];
		if (bytes > end - buf) {
		    state = DEMUX_SKIP;
		    state_bytes = bytes - (end - buf);
		    return 0;
		}
		buf += bytes;
	    }
	}
    }
}

static void ps_loop (int (*callback)())
{
    uint8_t * end;
	uint32_t byteread;
	
    do {
	
		if (callback) 
		{
			int ret = (*callback)();
			if (ret != VF4DC_OK)
			{	
				stop=1;
				break;
			}
			
		}
		
		
	byteread = fread (buffer, 1, BUFFER_SIZE, in_file);
	if(byteread==0)
		break;

	end = buffer + byteread;
	if (demux(buffer, end, 0))
	    break;	/* hit program_end_code */
	
    } while (end == buffer + BUFFER_SIZE && !es_stream);
}

static void es_loop (int (*callback)())
{
    uint8_t * end;
	
    do {

		if (callback) 
		{
			int ret = (*callback)();
			if (ret != VF4DC_OK)
			{	
				stop=1;
				break;
			}
			
		}

		end = buffer + fread (buffer, 1, BUFFER_SIZE, in_file);
		decode_mpeg2 (buffer, end);
    } while (end == buffer + BUFFER_SIZE);
}

int play_mpeg(char *filename,int _mode, int (*callback)(),unsigned int _flag)
{
    vo_driver_t * drivers;
	output = NULL;
	stop=0;
	in_file = fopen (filename, "rb");
	if (in_file == NULL) {
		printf ( "Can not open mpeg file\n");
		return VF4DC_NOT_OPEN;
    }
	es_stream=0;
    drivers = vo_drivers ();
	output_open = drivers[_flag].open;
	output = output_open ();
	mpeg2dec = mpeg2_init ();
    if (output == NULL) {
	printf ("Can not open output\n");
	return VF4DC_ERROR;
    }

	if(es_stream)
	es_loop (callback);
    else
    {
	   ps_loop(callback);
	   if(es_stream)
		   es_loop (callback);
    }

    while(_mode!=0)
    {
	   if(es_stream)
		   es_loop (callback);
	   else
		   ps_loop(callback);
	   if(stop)
		   break;
	   fseek(in_file,0,SEEK_SET);
	   if(_mode>0)
		   _mode--;
	}
	fclose(in_file);
    mpeg2_close (mpeg2dec);
    if (output->close)
		output->close (output);

	if(audio_open)
		ADS_Close();

    return 0;
}
