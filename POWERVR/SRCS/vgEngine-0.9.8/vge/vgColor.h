//
// C++ Interface: vgColor
//
// Description: 
//
//
// Author: root <root@majo>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

class vgColor
{
	public:
		vgColor() : r(0), g(0), b(0), a(0) {}
		vgColor(unsigned char cr, unsigned char cg, unsigned char cb, unsigned char ca) : r(cr), g(cg), b(cb), a(ca) { }
		vgColor(const vgColor& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
		vgColor& operator=(const vgColor& c){ r = c.r; g = c.g; b = c.b; a = c.a;  return *this; }
		
		void set(unsigned char cr, unsigned char cg, unsigned char cb, unsigned char ca) { r=cr; g=cg; b=cb; a=ca; }
		
		unsigned char GetRed() const { return r; }
		unsigned char GetGreen() const { return g; }
		unsigned char GetBlue() const { return b; }
		unsigned char GetAlpha() const { return a; }

		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
};

