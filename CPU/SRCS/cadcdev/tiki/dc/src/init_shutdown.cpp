/*
   Tiki

   init_shutdown.cpp

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"

#include "Tiki/tiki.h"
#include "Tiki/sound.h"
#include "Tiki/stream.h"
#include "Tiki/plxcompat.h"
#include "Tiki/hid.h"

static pvr_init_params_t params = {
	/* Enable opaque and translucent polygons with size 32 */
	{ PVR_BINSIZE_32, PVR_BINSIZE_0, PVR_BINSIZE_32, PVR_BINSIZE_0, PVR_BINSIZE_0 },

	/* Vertex buffer size 512K */
	512*1024
};

namespace Tiki {

bool init(int argc, char **argv) {
	if (pvr_init(&params) < 0)
		return false;
	glKosInit();
	
	snd_stream_init();
	GL::Plxcompat::plx_mat3d_init(640, 480);
	Hid::init();

	return true;
}

void shutdown() {
	pvr_stats_t	stats;

	pvr_get_stats(&stats);
	dbglog(DBG_DEBUG, "PVR Stats: %ld vblanks, frame rate ~%f fps, max vertex used %d bytes\n",
		stats.vbl_count, (double)stats.frame_rate, stats.vtx_buffer_used_max);	
	Hid::shutdown();
	glKosShutdown();
}

void setName(const char *windowName, const char *iconName) {
}

namespace GL {
void showCursor(bool visible) {
}

}

}
