/*
   Tiki

   font.h

   Copyright (C)2002 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_FONT_H
#define __TIKI_FONT_H

#include "refcnt.h"
#include "vector.h"
#include "color.h"
#include "texture.h"

namespace Tiki {
namespace GL {

class Font : public RefCnt {
public:
	Font(const string & fn = "");
	virtual ~Font();

	///////////////////////////////////////////////
	// Basic font functions

	bool	loadFromFile(const string & fn);
	void	destroy();

	void	setFilter(Texture::FilterType t);

	Color	getColor() const;
	void	setColor(const Color & c);

	float	getAlpha() const;
	void	setAlpha(float a);
	
	float	getSize() const;
	void	setSize(float size);
	
	float	getSlant() const;
	void	setSlant(float slant);

	void	draw(const Vector & pos, const string & text);

	void	drawBegin();
	void	drawEnd();
	Vector	drawCharGetPos();
	void	drawCharSetPos(const Vector & v);
	float	drawChar(int ch);
	
	void	getCharExtents(int c, float & l, float & u, float & r, float & d);
	void	getTextExtents(const string & text, float & l, float & u, float & r, float & d);
	void	getTextSize(const string & text, float & w, float & h);
	void	upperleftCoords(const string & text, Vector & p);
	void	centerCoords(const string & text, Vector & p);

	///////////////////////////////////////////////
	// More advanced stuff

	void	drawCentered(const Vector & v, const string & text);
	void	smearDraw(const Vector & v, const string & text);
	void	smearDrawCentered(const Vector & v, const string & text);

private:
	void	resetContext();

	// Old plx_font_t struct
	struct Fnt {
		RefPtr<Texture>	txr;		/**< Our font texture */
		int		glyph_cnt;	/**< The number of glyphs we have loaded */
		int		map_cnt;	/**< Size of our font map in entries */
		short		* map;		/**< Mapping from 16-bit character to glyph index */
		Vector		* txr_ll;	/**< Lower-left texture coordinates */
		Vector		* txr_ur;	/**< Upper-right texture coordinates */
		Vector		* vert_ll;	/**< Lower-left vertex coordinates */
		Vector		* vert_ur;	/**< Upper-right vertex coordinates */
	} m_fnt;
	
	// Old plx_fcxt_t struct
	struct FntCxt {
		float		slant;		/**< For oblique text output */
		float		size;		/**< Pixel size */
		float		gap;		/**< Extra pixels between each char */
		float		fixed_width;	/**< Width of each character in points in fixed mode */
		uint32		flags;		/**< Font attributes */
		Color		color;		/**< Color value */
		Vector		pos;		/**< Output position */
	} m_cxt;
	
	enum Flags {
		FcxtFixed = 0
	};
};

};
};

#endif	// __TIKI_FONT_H

