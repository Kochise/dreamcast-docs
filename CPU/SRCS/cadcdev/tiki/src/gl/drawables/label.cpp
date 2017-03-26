/*
   Tiki

   label.cpp

   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"

#include "Tiki/drawables/label.h"
#include "Tiki/plxcompat.h"

using namespace Tiki::GL;
using namespace Tiki::GL::Plxcompat;

Label::Label(Font * fh, const string & text, float size, bool centered, bool smear) {
	m_fh = fh;
	m_text = text;
	m_size = size;
	m_centered = centered;
	m_smear = smear;
	
}
Label::~Label() {
}

void Label::setText(const string & text) {
	m_text = text;
}
const string & Label::getText() {
	return m_text;
}

void Label::setFont(Font * f) {
	m_fh = f;
}

void Label::draw(ObjType list) {
	if (list != Trans)
		return;

	const Vector & p = getPosition();
	Color t = getColor();

	m_fh->setSize(m_size);
	m_fh->setColor(t);
	if (m_centered) {
		if (m_smear)
			m_fh->smearDrawCentered(p, m_text);
		else
			m_fh->drawCentered(p, m_text);
	} else {
		if (m_smear)
			m_fh->smearDraw(p, m_text);
		else
			m_fh->draw(p, m_text);
	}
}
