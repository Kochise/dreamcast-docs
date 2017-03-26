/*
   Tiki

   texture.cpp

   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/texture.h"
#include "Tiki/image.h"
#include "Tiki/imgpng.h"
#include "Tiki/imgjpg.h"

using namespace Tiki::GL;

TIKI_OBJECT_NAME(Texture)
TIKI_OBJECT_BEGIN(Object, Texture)
TIKI_OBJECT_END(Texture)

Texture::Texture(const string & fn, bool use_alpha) {
	destroy(true);
	if (!loadFromFile(fn, use_alpha))
		assert( false );
}

Texture::Texture(int w, int h, Fmt fmt) {
	destroy(true);
	if (!createCanvas(w, h, fmt)) {
		Debug::printf("Texture::Texture: Can't allocate %dx%dcanvas texture\n", w, h);
		assert( false );
	}
}

Texture::Texture() {
	destroy(true);
}

Texture::~Texture() {
	destroy();
}

void Texture::destroy(bool initial) {
	uint8 * oldptr = m_ptr;
	if (!initial && m_ptr)
		delete[] m_ptr;
	m_ptr = NULL;
	m_w = m_h = 0;
	m_fmt = None;
	if (!initial && m_txrdata && m_txrdata != oldptr)
#if TIKI_PLAT != TIKI_DC
		delete[] m_txrdata;
#else
		//glDeleteTexture frees the PVR memory for us, how nice of it!
#endif
	m_txrdata = NULL;
#if TIKI_PLAT != TIKI_NDS
	if (!initial && m_gltxr)
		glDeleteTextures(1, &m_gltxr);
#endif
	m_gltxr = 0;
}

void Texture::convertToGl() {
	uint16 * src16 = (uint16 *)m_ptr;
	uint8 * dst = m_txrdata;

	if (m_fmt == RGBA8888)
		return;

	// The data needs to be converted from its source format to ARGB8888, and
	// it needs to be Y-inverted as well.
	// NOTE: The Y-inversion is only true so "proper" GL coordinates can be obtained.
	//  since PLX is built around 0,0 being the upper left, this actually doesn't have
	//  the desired effect.
	// for (int y=txr->h-1; y>=0; y--) {
	for (int y=0; y<m_h; y++) {
		for (int x=0; x<m_w; x++) {
			uint8 r, g, b, a;
			uint16 tmp;
			tmp = src16[y * m_w + x];
			switch(m_fmt) {
			case RGB888:
				r = m_ptr[(y*m_w+x)*3+0];
				g = m_ptr[(y*m_w+x)*3+1];
				b = m_ptr[(y*m_w+x)*3+2];
				a = 255;
				break;
			case RGB565:
				r = ((tmp >> 11) & 0x1f) << 3;
				g = ((tmp >> 5) & 0x3f) << 2;
				b = ((tmp >> 0) & 0x1f) << 3;
				a = 255;
				break;
			case ARGB4444:
				r = ((tmp >> 8) & 0x0f) << 4;
				g = ((tmp >> 4) & 0x0f) << 4;
				b = ((tmp >> 0) & 0x0f) << 4;
				a = ((tmp >> 12) & 0x0f) << 4;
				break;
			case ARGB1555:
				r = ((tmp >> 10) & 0x1f) << 3;
				g = ((tmp >> 5) & 0x1f) << 3;
				b = ((tmp >> 0) & 0x1f) << 3;
				a = ((tmp >> 15) & 1) ? 255 : 0;
				break;
			default:
				r = g = b = a = 255;
				break;
			}
			*dst++ = r;
			*dst++ = g;
			*dst++ = b;
			*dst++ = a;
		}
	}
}

#if TIKI_PLAT == TIKI_WIN32
#if !defined(__GNUC__)
// Win32 doesn't seem to have this... perhaps it's not really ANSI?
static int strcasecmp(const char * cs,const char * ct) {
	int c1, c2, res;

	while(1) {
		c1 = *cs++; c2 = *ct++;
		if (c1 >= 'A' && c1 <= 'Z') c1 += 'a' - 'A';
		if (c2 >= 'A' && c2 <= 'Z') c2 += 'a' - 'A';
		if ((res = c1 - c2) != 0 || (!*cs && !*ct))
			break;
	}

	return res;
}
#endif
#endif


bool Texture::loadFromFile(const string & fn, int use_alpha) {
	RefPtr<Image>	img;
	size_t		fnlen;

	/* What type of texture is it? */
	fnlen = fn.length();
	if (!strcasecmp(fn.c_str() + fnlen - 3, "png")) {
		/* Load the texture (or try) */
		if (!pngToImage(fn, img)) {
			Debug::printf("Texture::loadFromFile: can't load texture from file '%s'\n", fn.c_str());
			return false;
		}
	} else if (!strcasecmp(fn.c_str() + fnlen - 3, "jpg")) {
		/* Load the texture (or try) */
		if (!jpgToImage(fn, 1, img)) {
			Debug::printf("Texture::loadFromFile: can't load texture from file '%s'\n", fn.c_str());
			return false;
		}
	} else {
		Debug::printf("Texture::loadFromFile: unknown extension for file '%s'\n", fn.c_str());
		return false;
	}

	Debug::printf("Texture::loadFromFile: loading '%s' %s alpha\n",
		fn.c_str(), use_alpha ? "with" : "without");

	// If they don't want to use alpha explicitly, then ditch it first.
#if TIKI_PLAT == TIKI_DC
	if (use_alpha == 0) {
		img->convertTo(Image::RGB565);
	} else {
		img->convertTo(Image::ARGB4444);
	}
#else
	if (use_alpha == 0) {
		img->convertTo(Image::RGB888);
	}
#endif

	/* Setup the struct */
	glGenTextures(1, &m_gltxr);
	if (img->fmt == Image::RGBA8888) {
		m_txrdata = m_ptr = img->data;
		img->data = NULL;
	} else {
		m_ptr = new uint8[img->byteCount];
		memcpy(m_ptr, img->data, img->byteCount);
	}

	m_w = img->w;
	m_h = img->h;
	m_fmt = (Fmt)(img->fmt);
	switch(img->fmt) {
	case Image::RGB565:
	case Image::RGB888:
#if TIKI_PLAT != TIKI_NDS // NDS doesnt support Alpha?
	case Image::RGBA8888:
	case Image::ARGB4444:
	case Image::ARGB1555:
#endif
		break;
	default:
		/* shrug */
		Debug::printf("Texture::loadFromFile: unknown format '%d'\n", img->fmt);
		m_fmt = RGB565;
		break;
	}

	/* Load it up and twiddle it */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_gltxr);

#if TIKI_PLAT != TIKI_DC && TIKI_PLAT != TIKI_NDS
	/* We'll write the converted data into this buffer */
	if (!m_txrdata)
		m_txrdata = new uint8[img->w * img->h * 4];

	convertToGl();
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_w, m_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_txrdata);

	GLenum err = glGetError();
#elif TIKI_PLAT == TIKI_DC
	m_txrdata = (uint8 *)pvr_mem_malloc(img->w * img->h * 2);
	pvr_txr_load_ex(m_ptr, m_txrdata, img->w, img->h, PVR_TXRLOAD_16BPP);

	if(use_alpha) {
		glKosTex2D(GL_ARGB4444_TWID, m_w, m_h, m_txrdata);
	} else {
		glKosTex2D(GL_RGB565_TWID, m_w, m_h, m_txrdata);
	}
	glTexEnvi(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATEALPHA);
#elif TIKI_PLAT == TIKI_NDS
	glTexImage2D(0, 0, GL_RGB, m_w, m_h, 0, TEXGEN_TEXCOORD, m_ptr);
#endif

	return true;
}

bool Texture::createCanvas(int w, int h, Fmt fmt) {
	glGenTextures(1, &m_gltxr);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_gltxr);

#if TIKI_PLAT != TIKI_DC && TIKI_PLAT != TIKI_NDS
	//KGL/NDS do support these
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
#elif TIKI_PLAT == TIKI_DC
	glTexEnvi(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATEALPHA);
#elif TIKI_PLAT == TIKI_NDS
#endif

	m_w = w;
	m_h = h;
	m_fmt = fmt;
	switch (m_fmt) {
	case RGB565:
	case ARGB1555:
	case ARGB4444:
		m_ptr = new uint8[m_w * m_h * 2];
		break;
	case RGB888:
		m_ptr = new uint8[m_w * m_h * 3];
		break;
	case RGBA8888:
	case ARGB8888:
		m_ptr = new uint8[m_w * m_h * 4];
		break;
	default:
		return false;
	}

	// We'll write the converted data into this buffer
	if (m_fmt == RGBA8888)
		m_txrdata = m_ptr;
	else
		m_txrdata = new uint8[m_w * m_h * 4];

	return true;
}

void Texture::select() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_gltxr);
}

void Texture::deselect() {
	glDisable(GL_TEXTURE_2D);
}


void Texture::setFilter(FilterType filter) {
#if TIKI_PLAT != TIKI_DC && TIKI_PLAT != TIKI_NDS
	select();
	GLuint glfilt = GL_LINEAR;
	switch (filter) {
	case FilterNone:
		glfilt = GL_NEAREST;
	case FilterBilinear:
	case FilterTrilinear1:
		glfilt = GL_LINEAR;
		break;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glfilt);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glfilt);
#endif
}

void Texture::setUVClamp(UVMode umode, UVMode vmode) {
#if TIKI_PLAT != TIKI_NDS
	GLenum gumode, gvmode;

	gumode = umode == UVClamp ? GL_CLAMP : GL_REPEAT;
	gvmode = vmode == UVClamp ? GL_CLAMP : GL_REPEAT;

	select();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gumode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gvmode);

	// This provides the expected behavior on newer OpenGL impls...
#if TIKI_PLAT != TIKI_DC
// for whatever reason the Windows 2003 R2 PSDK is only
// OpenGL 1.1 which doesnt have GL_CLAMP_TO_EDGE
#if !defined(GL_VERSION_1_1)
	if (gumode == GL_CLAMP)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	if (gvmode == GL_CLAMP)
		glTexParameteri(GL_EXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#endif // GL_VERSION_1_1
#endif // TIKI_DC
#endif // TIKI_NDS
}

void * Texture::canvasLock() {
	return getPtr();
}

void Texture::canvasUnlock() {
	convertToGl();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_gltxr);
#if TIKI_PLAT != TIKI_DC && TIKI_PLAT != TIKI_NDS
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_w, m_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_txrdata);
#else
	switch (m_fmt) {
#if TIKI_PLAT != TIKI_NDS
		case ARGB1555:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_ARGB1555, m_w, m_h, 0, GL_ARGB1555, GL_UNSIGNED_BYTE, m_ptr);
			break;
		case ARGB4444:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_ARGB4444, m_w, m_h, 0, GL_ARGB4444, GL_UNSIGNED_BYTE, m_ptr);
			break;
#endif
		case RGB565:
#if TIKI_PLAT != TIKI_NDS
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB565, m_w, m_h, 0, GL_RGB565, GL_UNSIGNED_BYTE, m_ptr);
#else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_w, m_h, 0, TEXGEN_TEXCOORD, m_ptr);
#endif
			break;
		default:
			Debug::printf("Texture::canvasUnlock: Unsupported texture format\n");
			assert( false );
			break;
	}
#endif
}




