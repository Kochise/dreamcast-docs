/*      
   Tsunami for KallistiOS ##version##
        
   texture.cpp

   (c)2002 Dan Potter
*/

#include <tsu/texture.h>

CVSID("$Id: texture.cpp,v 1.3 2003/04/24 02:57:20 bardtx Exp $");

Texture::Texture(const char *fn, bool use_alpha, bool yflip) {
	m_txr = NULL;
	if (!loadFromFile(fn, use_alpha, yflip))
		assert( false );
}

Texture::Texture(int w, int h, int fmt) {
	m_txr = plx_txr_canvas(w, h, fmt);
	if (m_txr == NULL) {
		dbglog(DBG_WARNING, "Texture::loadFromFile: Can't allocate %dx%dcanvas texture\n", w, h);
		assert( false );
	}
}

Texture::Texture() {
	m_txr = NULL;
}

Texture::~Texture() {
	if (m_txr != NULL)
		plx_txr_destroy(m_txr);
}

void Texture::setFilter(FilterType filter) {
	plx_txr_setfilter(m_txr, filter);
}

void Texture::setUVClamp(UVMode umode, UVMode vmode) {
	plx_txr_setuvclamp(m_txr, umode, vmode);
}

// Submit one of the poly headers
void Texture::sendHdr(int list) {
	plx_txr_send_hdr(m_txr, list, 0);
}

bool Texture::loadFromFile(const char *fn, bool use_alpha, bool flip) {
	m_txr = plx_txr_load(fn, use_alpha, flip ? PVR_TXRLOAD_INVERT_Y : 0);
	if (m_txr == NULL) {
		dbglog(DBG_WARNING, "Texture::loadFromFile: Can't load '%s'\n", fn);
		return false;
	} else
		return true;
}

