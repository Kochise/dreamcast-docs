/*
   Tiki

   font.cpp

   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/font.h"
#include "Tiki/file.h"
#include "Tiki/plxcompat.h"

#include <memory>
using std::auto_ptr;

using namespace Tiki::GL;
using namespace Tiki::GL::Plxcompat;

// This is mostly pulled from the Parallax font functions.

Font::Font(const string & fn) {
	memset(&m_fnt, 0, sizeof(m_fnt));
	memset(&m_cxt, 0, sizeof(m_cxt));
	if (fn.length() > 0) {
		if (!loadFromFile(fn)) {
			assert( false );
		}
	}
	resetContext();
}

Font::~Font() {
	destroy();
}

////////////////////////////////////////////////////////////////////////////////////////////

/*
  Implementation notes...

  TXF Header (thanks to PLIB and gentexfont)

  BYTES         WHAT
  -----------------------------
  4	 	0xff + 'txf'
  4		0x12345678 for endian testing
  4		format: 0 for bytes, 1 for bits
  4		texture width
  4		texture height
  4		maximum font ascent
  4		maximum font descent
  4		glyph count

  TXF Per-Glyph Data

  BYTES		WHAT
  -----------------------------
  2		character index
  1		width in pixels
  1		height in pixels
  1		x offset for left side of char
  1		y offset for bottom of char
  1		advance
  1		char for padding
  2		texture x for left of char
  2		texture y for bottom of char

  We'll mimic PLIB here as far as handling the fonts: each u/v coord
  is offset by half a pixel (which provides a bit of an anti-aliasing effect)
  and all character sizes are scaled to 1 pixel high using the maximum font
  ascent. We then multiply this by the point size to get the real quad
  size. Additionally, we add to the X coordinate of the top of the
  glyph to achieve an oblique effect (it's not a proper italic...)

*/

#if TIKI_PLAT==TIKI_WIN32
#pragma pack(push,1)
#endif
typedef struct {
	uint8	magic[4]		PACKED_STRUCT_MEMBER;
	uint32	endian			PACKED_STRUCT_MEMBER;
	uint32	format			PACKED_STRUCT_MEMBER;
	uint32	txr_width		PACKED_STRUCT_MEMBER;
	uint32	txr_height		PACKED_STRUCT_MEMBER;
	int32	max_ascent		PACKED_STRUCT_MEMBER;
	int32	max_descent		PACKED_STRUCT_MEMBER;
	uint32	glyph_cnt		PACKED_STRUCT_MEMBER;
} txfhdr_t;

typedef struct {
	int16	idx			PACKED_STRUCT_MEMBER;
	int8	w			PACKED_STRUCT_MEMBER;
	int8	h			PACKED_STRUCT_MEMBER;
	int8	x_offset		PACKED_STRUCT_MEMBER;
	int8	y_offset		PACKED_STRUCT_MEMBER;
	int8	advance			PACKED_STRUCT_MEMBER;
	char	padding			PACKED_STRUCT_MEMBER;
	uint16	x			PACKED_STRUCT_MEMBER;
	uint16	y			PACKED_STRUCT_MEMBER;
} txfglyph_t;
#if TIKI_PLAT==TIKI_WIN32
#pragma pack(pop)
#endif

// These functions are used if the host and font endianness
// do *not* match.
static uint32 swapu32(uint32 i) {
	return (((i >> 24) & 0xff) << 0) |
		(((i >> 16) & 0xff) << 8) |
		(((i >> 8) & 0xff) << 16) |
		(((i >> 0) & 0xff) << 24);
}

static int32 swapi32(int32 i) {
	uint32 iv = *((uint32 *)&i);
	iv = swapu32(iv);
	return *((int32 *)&iv);
}

static uint16 swapu16(uint16 i) {
	return (((i >> 8) & 0xff) << 0) |
		(((i >> 0) & 0xff) << 8);
}

static int16 swapi16(int16 i) {
	uint16 iv = *((uint16 *)&i);
	iv = swapu16(iv);
	return *((int16 *)&iv);
}

static void swap_header(txfhdr_t * hdr) {
	hdr->format = swapu32(hdr->format);
	hdr->txr_width = swapu32(hdr->txr_width);
	hdr->txr_height = swapu32(hdr->txr_height);
	hdr->max_ascent = swapi32(hdr->max_ascent);
	hdr->max_descent = swapi32(hdr->max_descent);
	hdr->glyph_cnt = swapu32(hdr->glyph_cnt);
}

static void swap_glyph(txfglyph_t * g) {
	g->idx = swapi16(g->idx);
	g->x = swapu16(g->x);
	g->y = swapu16(g->y);
}

bool Font::loadFromFile(const string & fn) {
	destroy();

	/* Open the input file */
	File f;
	if (!f.open(fn, "rb")) {
		Debug::printf("plx_font_load: couldn't open file '%s'\n", fn.c_str());
		return false;
	}

	/* Create a font struct */
	memset(&m_fnt, 0, sizeof(m_fnt));

	/* Load up the TXF header */
	txfhdr_t hdr;
	if (f.read(&hdr, sizeof(txfhdr_t)) != sizeof(txfhdr_t)) {
		Debug::printf("plx_font_load: truncated file '%s'\n", fn.c_str());
		return false;
	}

	if (hdr.magic[0] != 0xff || strncmp("txf", ((const char *)hdr.magic)+1, 3)) {
		Debug::printf("plx_font_load: invalid font file '%s'\n", fn.c_str());
		return false;
	}

	if (hdr.endian != 0x12345678) {
		swap_header(&hdr);
	}

	Debug::printf("plx_font_load:  loading font '%s'\n"
			  "  texture size: %ldx%ld\n"
			  "  max ascent:   %ld\n"
			  "  max descent:  %ld\n"
			  "  glyph count:  %ld\n",
		fn.c_str(), hdr.txr_width, hdr.txr_height,
		hdr.max_ascent, hdr.max_descent, hdr.glyph_cnt);

	/* Make sure we can allocate texture space for it */
	m_fnt.txr = new Texture;
	if (!m_fnt.txr->createCanvas(hdr.txr_width, hdr.txr_height, Texture::ARGB4444)) {
		Debug::printf("plx_font_load: can't allocate texture for '%s'\n", fn.c_str());
		return false;
	}

	/* Copy over some other misc housekeeping info */
	m_fnt.glyph_cnt = hdr.glyph_cnt;
	m_fnt.map_cnt = 256;	/* Just ASCII for now */

	/* Allocate structs for the various maps */
	m_fnt.map = new short[m_fnt.map_cnt];
	m_fnt.txr_ll = new Vector[m_fnt.glyph_cnt * 4];
	m_fnt.txr_ur = m_fnt.txr_ll + m_fnt.glyph_cnt * 1;
	m_fnt.vert_ll = m_fnt.txr_ll + m_fnt.glyph_cnt * 2;
	m_fnt.vert_ur = m_fnt.txr_ll + m_fnt.glyph_cnt * 3;

	/* Set all chars as not present */
	for (int i=0; i<m_fnt.map_cnt; i++)
		m_fnt.map[i] = -1;

	/* Some more helpful values... */
	float w = (float)hdr.txr_width;
	float h = (float)hdr.txr_height;
	float xstep = 0.0f, ystep = 0.0f;

	/* Use this instead to get a pseudo-antialiasing effect */
	/* xstep = 0.5f / w;
	ystep = 0.5f / h; */

	/* Ok, go through and load up each glyph */
	txfglyph_t g;
	for (int i=0; i<m_fnt.glyph_cnt; i++) {
		/* Load up the glyph info */
		if (f.read(&g, sizeof(txfglyph_t)) != sizeof(txfglyph_t)) {
			Debug::printf("plx_font_load: truncated file '%s'\n", fn.c_str());
			return false;
		}
		if (hdr.endian != 0x12345678)
			swap_glyph(&g);

		/* Is it above our limit? If so, ignore it */
		if (g.idx >= m_fnt.map_cnt)
			continue;

		/* Leave out the space glyph, if we have one */
		if (g.idx == ' ')
			continue;

		/* Pull in all the relevant parameters */
		m_fnt.map[g.idx] = i;
		m_fnt.txr_ll[i].x = g.x / w + xstep;
		m_fnt.txr_ll[i].y = g.y / h + ystep;
		m_fnt.txr_ur[i].x = (g.x + g.w) / w + xstep;
		m_fnt.txr_ur[i].y = (g.y + g.h) / h + ystep;
		m_fnt.vert_ll[i].x = (float)g.x_offset / hdr.max_ascent;
		m_fnt.vert_ll[i].y = (float)g.y_offset / hdr.max_ascent;
		m_fnt.vert_ur[i].x = ((float)g.x_offset + g.w) / hdr.max_ascent;
		m_fnt.vert_ur[i].y = ((float)g.y_offset + g.h) / hdr.max_ascent;

		/* dbglog(DBG_DEBUG, "  loaded glyph %d(%c): uv %.2f,%.2f - %.2f,%.2f, vert %.2f,%.2f - %.2f, %.2f\n",
			g.idx, (char)g.idx,
			(double)m_fnt.txr_ll[i].x, (double)m_fnt.txr_ll[i].y,
			(double)m_fnt.txr_ur[i].x, (double)m_fnt.txr_ur[i].y,
			(double)m_fnt.vert_ll[i].x, (double)m_fnt.vert_ll[i].y,
			(double)m_fnt.vert_ur[i].x, (double)m_fnt.vert_ur[i].y); */
	}

	void		* txrptr = m_fnt.txr->canvasLock();
	auto_ptr<uint8>	bmtmpfree;
	uint8		* bmtmp = NULL;
	int		bmsize;
	auto_ptr<uint16> txrtmpfree;
	uint16		* txrtmp = NULL;
	int		stride;

	/* What format are we using? */
	switch (hdr.format) {
	case 1:		/* TXF_FORMAT_BITMAP */
		/* Allocate temp texture space */
		bmsize = hdr.txr_width * hdr.txr_height / 8;
		bmtmp = new uint8[bmsize];
		bmtmpfree.reset(bmtmp);
		txrtmp = new uint16[hdr.txr_width * hdr.txr_height];
		txrtmpfree.reset(txrtmp);

		/* Load the bitmap and convert to a texture */
		if (f.read(bmtmp, bmsize) != bmsize) {
			Debug::printf("plx_font_load: truncated file '%s'\n", fn.c_str());
			return false;
		}

		stride = hdr.txr_width / 8;
		for (int y=0; y<(int)hdr.txr_height; y++) {
			for (int x=0; x<(int)hdr.txr_width; x++) {
				if (bmtmp[y * stride + x/8] & (1 << (x%8))) {
					txrtmp[y*hdr.txr_width+x] = 0xffff;
				} else {
					txrtmp[y*hdr.txr_width+x] = 0;
				}
			}
		}

		break;
	case 0:		/* TXF_FORMAT_BYTE */
		/* Allocate temp texture space */
		bmsize = hdr.txr_width * hdr.txr_height;
		txrtmp = new uint16[bmsize * 2];
		txrtmpfree.reset(txrtmp);

		/* Load the texture */
		if (f.read(txrtmp, bmsize) != bmsize) {
			Debug::printf("plx_font_load: truncated file '%s'\n", fn.c_str());
			return false;
		}

		/* Convert to ARGB4444 -- go backwards so we can do it in place */
		/* PLIB seems to duplicate the alpha value into luminance.  I think it
		 * looks nicer to hardcode luminance to 1.0; characters look more robust. */
		bmtmp = (uint8 *)txrtmp;
		for (int x=bmsize-1; x>=0; x--) {
			uint8 alpha = (bmtmp[x] & 0xF0) >> 4;
			/* uint8 lum   = alpha; */
			uint8 lum   = 0x0f;
			txrtmp[x] = (alpha << 12) | (lum << 8) | (lum << 4) | (lum << 0);
		}

		break;
	}

	/* dbglog(DBG_DEBUG, "plx_font_load: load done\n"); */

	/* Close the file */
	f.close();

	/* Now load the temp texture into our canvas texture and twiddle it */
	memcpy(txrptr, txrtmp, hdr.txr_width * hdr.txr_height * 2);
	m_fnt.txr->canvasUnlock();

	/* Yay! Everything's happy. Clean up and return the font. */
	return true;
}

void Font::destroy() {
	m_fnt.txr = NULL;
	delete[] m_fnt.txr;
	delete[] m_fnt.txr_ll;
	m_fnt.txr_ur = m_fnt.vert_ll = m_fnt.vert_ur = NULL;

	resetContext();
}

void Font::resetContext() {
	memset(&m_cxt, 0, sizeof(m_cxt));
	m_cxt.size = 24.0f;
	m_cxt.gap = 0.1f;
	m_cxt.fixed_width = 1.0f;
	m_cxt.color = Color(1,1,1,1);
}

////////////////////////////////////////////////////////////////////////////////////////////

void Font::setFilter(Texture::FilterType type) {
	m_fnt.txr->setFilter(type);
}

Color Font::getColor() const {
	return m_cxt.color;
}

void Font::setColor(const Color & col) {
	m_cxt.color = col;
}

float Font::getAlpha() const {
	return m_cxt.color.a;
}

void Font::setAlpha(float a) {
	m_cxt.color.a = a;
}

float Font::getSize() const {
	return m_cxt.size;
}

void Font::setSize(float size) {
	m_cxt.size = size;
}

float Font::getSlant() const {
	return m_cxt.slant;
}

void Font::setSlant(float slant) {
	m_cxt.slant = slant;
}

void Font::draw(const Vector & pos, const string & text) {
	m_cxt.pos = pos;
	drawBegin();

	const char * str = text.c_str();
	float origx = m_cxt.pos.x;

	while (*str != 0) {
		if (*str == '\n') {
			/* Handle newlines somewhat */
			m_cxt.pos.x = origx;
			m_cxt.pos.y += m_cxt.size;
			str++;
		} else
			drawChar(*str++);
	}

	drawEnd();
}

void Font::drawBegin() {
	assert( m_fnt.txr );
	m_fnt.txr->select();
}

void Font::drawEnd() {
}

Vector Font::drawCharGetPos() {
	return m_cxt.pos;
}

void Font::drawCharSetPos(const Vector & v) {
	m_cxt.pos = v;
}

float Font::drawChar(int ch) {
	plx_vertex_t	vert;

	/* Do we have the character in question? */
	if (ch >= m_fnt.map_cnt)
		ch = 32;
	if (m_fnt.map[ch] == -1)
		ch = 32;
	if (ch == 32) {
		m_cxt.pos.x += m_cxt.gap + m_cxt.size / 2.0f;
		return m_cxt.gap + m_cxt.size / 2.0f;
	}

	int i = m_fnt.map[ch];
	assert( i < m_fnt.glyph_cnt );
	if (i >= m_fnt.glyph_cnt)
		return 0.0f;

	// XXX use a display list
	/* Submit the vertices */
	plx_vert_ifn(&vert, PLX_VERT,
		m_cxt.pos.x + m_fnt.vert_ll[i].x * m_cxt.size,
		m_cxt.pos.y - m_fnt.vert_ll[i].y * m_cxt.size,
		m_cxt.pos.z,
		m_cxt.color, m_fnt.txr_ll[i].x, m_fnt.txr_ll[i].y);
	plx_prim(&vert, sizeof(vert));

	vert.x += m_cxt.slant;
	vert.y = m_cxt.pos.y - m_fnt.vert_ur[i].y * m_cxt.size;
	vert.v = m_fnt.txr_ur[i].y;
	plx_prim(&vert, sizeof(vert));

	vert.x = m_cxt.pos.x + m_fnt.vert_ur[i].x * m_cxt.size;
	vert.y = m_cxt.pos.y - m_fnt.vert_ll[i].y * m_cxt.size;
	vert.u = m_fnt.txr_ur[i].x;
	vert.v = m_fnt.txr_ll[i].y;
	plx_prim(&vert, sizeof(vert));

	vert.flags = PLX_VERT_EOS;
	vert.x += m_cxt.slant;
	vert.y = m_cxt.pos.y - m_fnt.vert_ur[i].y * m_cxt.size;
	vert.v = m_fnt.txr_ur[i].y;
	plx_prim(&vert, sizeof(vert));

	/* Advance the cursor position */
	float adv;
	if (m_cxt.flags & FcxtFixed)
		adv = (m_cxt.gap + m_cxt.fixed_width) * m_cxt.size;
	else
		adv = (m_cxt.gap + m_fnt.vert_ur[i].x) * m_cxt.size;
	m_cxt.pos.x += adv;
	return adv;
}

void Font::getCharExtents(int ch, float & outleft, float & outup, float & outright, float & outdown) {
	if (ch >= m_fnt.map_cnt)
		ch = ' ';
	if (m_fnt.map[ch] == -1)
		ch = ' ';
	if (ch == ' ') {
		outleft = 0;
		outup = 0;
		outright = m_cxt.gap + m_cxt.size / 2.0f;
		outdown = 0;
		return;
	}

	int g = m_fnt.map[ch];
	assert( 0 <= g && g < m_fnt.glyph_cnt );
	if (g < 0 || g >= m_fnt.glyph_cnt)
		return;

	outleft = m_fnt.vert_ll[g].x * m_cxt.size;
	outup = m_fnt.vert_ur[g].y * m_cxt.size;
	if (m_cxt.flags & FcxtFixed)
		outright = (m_cxt.gap + m_cxt.fixed_width) * m_cxt.size;
	else
		outright = (m_cxt.gap + m_fnt.vert_ur[g].x) * m_cxt.size;
	outdown = m_fnt.vert_ll[g].y * -m_cxt.size;
}

void Font::getTextExtents(const string & text, float & l, float & u, float & r, float & d) {
	const char * str = text.c_str();
	int len = (int)text.length();
	l = u = r = d = 0.0f;

	for (int i=0; i<len; i++) {
		/* Find the glyph (if any) */
		int ch = str[i];
		if (ch < 0 || ch >= m_fnt.map_cnt)
			ch = ' ';
		if (m_fnt.map[ch] == -1)
			ch = ' ';
		if (ch == ' ') {
			r += m_cxt.gap + m_cxt.size / 2.0f;
			continue;
		}

		int g = m_fnt.map[ch];
		assert( 0 <= g && g < m_fnt.glyph_cnt );
		if (g < 0 || g >= m_fnt.glyph_cnt)
			continue;

		/* If this is the first char, do the left */
		if (i == 0) {
			l = m_fnt.vert_ll[g].x * m_cxt.size;
		}

		/* Handle the others */
		if (m_cxt.flags & FcxtFixed)
			r += (m_cxt.gap + m_cxt.fixed_width) * m_cxt.size;
		else
			r += (m_cxt.gap + m_fnt.vert_ur[g].x) * m_cxt.size;

		if (m_fnt.vert_ur[g].y * m_cxt.size > u)
			u = m_fnt.vert_ur[g].y * m_cxt.size;
		if (m_fnt.vert_ll[g].y * -m_cxt.size > d)
			d = m_fnt.vert_ll[g].y * -m_cxt.size;
	}
}

void Font::getTextSize(const string & text, float & w, float & h) {
	float left, right, bot, top;
	getTextExtents(text, left, top, right, bot);

	w = left+right;
	h = top+bot;
}

void Font::upperleftCoords(const string & text, Vector & p) {
	float left, right, bot, top;
	getTextExtents(text, left, top, right, bot);

	p.y += top;
}

void Font::centerCoords(const string & text, Vector & p) {
	float left, right, bot, top;
	getTextExtents(text, left, top, right, bot);

	p.x += -(left+right)/2;
	p.y += (bot+top)/2;
}

void Font::drawCentered(const Vector & v, const string & text) {
	Vector vp(v);
	centerCoords(text, vp);
	draw(vp, text);
}

void Font::smearDraw(const Vector & v, const string & text) {
	// Draw a nifty subtitle border
	// Guess all that time I spent on BakaSub wasn't wasted after all ^_-
	Color oc = m_cxt.color;
	setColor(Color(m_cxt.color.a, 0.0f, 0.0f, 0.0f));
	
	draw(v + Vector( 1, 0, -3.5), text);
	draw(v + Vector( 1, 1, -3.0), text);
	draw(v + Vector( 0, 1, -2.5), text);
	draw(v + Vector(-1, 1, -2.0), text);
	draw(v + Vector(-1, 0, -1.5), text);
	draw(v + Vector(-1,-1, -1.0), text);
	draw(v + Vector( 0, 0, -0.5), text);
		
	// Draw the text itself
	setColor(oc);
	draw(v, text);
}

void Font::smearDrawCentered(const Vector & v, const string & text) {
	Vector vp(v);
	centerCoords(text, vp);
	smearDraw(vp, text);
}

