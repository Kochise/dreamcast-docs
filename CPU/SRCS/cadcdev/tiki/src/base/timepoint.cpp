/*
   Tiki

   timepoint.cpp

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/timepoint.h"
#include "Tiki/timeline.h"

using namespace Tiki;

TIKI_OBJECT_NAME(Timepoint)
TIKI_OBJECT_BEGIN(Object, Timepoint)
	TIKI_OBJECT_OUTLET("timepointReached:")
TIKI_OBJECT_END(Timepoint)

Timepoint::Timepoint() {
	m_parent = NULL;
	m_offset = 0;
}

Timepoint::Timepoint(uint64 offset) {
	m_parent = NULL;
	m_offset = offset;
}

Timepoint::~Timepoint() {
}

uint64 Timepoint::getOffset() const {
	return m_offset;
}

void Timepoint::setOffset(uint64 offset) {
	m_offset = offset;
	if (m_parent)
		m_parent->timepointReSort(this);
}

void Timepoint::bump(uint64 offset) {
	setOffset(m_offset + offset);
}

Timepoint * Timepoint::newFromBump(uint64 offset) {
	Timepoint * ntp = new Timepoint(m_offset + offset);
	return ntp;
}

bool Timepoint::trigger(Timeline * tm) {
	uint64 oldOffset = m_offset;

	emit("timepointReached:", tm);

	// If we were bumped forwards, then we need to trigger again.
	return oldOffset < m_offset;
}























