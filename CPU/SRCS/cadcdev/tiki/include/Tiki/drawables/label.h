/*
   Tiki

   label.h

   Copyright (C)2002 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_DRW_LABEL_H
#define __TIKI_DRW_LABEL_H

#include "Tiki/drawable.h"
#include "Tiki/font.h"

namespace Tiki {
namespace GL {

class Label : public Drawable {
public:
	Label(Font * fh, const string & text, float size, bool centered, bool smear);
	virtual ~Label();

	void setText(const string & text);
	const string & getText();
	void setFont(Font * f);

	virtual void draw(ObjType t);

private:
	RefPtr<Font>	m_fh;
	string		m_text;
	float		m_size;
	bool		m_centered;
	bool		m_smear;
};

};
};

#endif	// __TIKI_DRW_LABEL_H

