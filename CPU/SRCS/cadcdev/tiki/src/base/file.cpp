/*
   Tiki

   file.cpp

   Copyright (C)2003,2004,2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/file.h"

#include <machine/endian.h>

File::File() {
	m_fd = NULL;
}

File::File(const string & fn, const char * access) {
	m_fd = NULL;
	open(fn, access);
}

File::~File() {
}

bool File::open(const string & fn, const char * access) {
	FILE *f = fopen(fn.c_str(), access);
	if (!f)
		return false;
	m_fd = new FileFD(f);
	return true;
}

bool File::isValid() const {
	return m_fd != NULL;
}

void File::close() {
	if (m_fd)
		m_fd = NULL;
}

int File::read(void * out, int size) {
	if (!isValid())
		return -1;

	return (int)fread(out, 1, size, m_fd->m_fd);
}

int File::write(const void * src, int size) {
	if (!isValid())
		return -1;

	return (int)fwrite(src, 1, size, m_fd->m_fd);
}

bool File::readle16(void * out, int cnt) {
#if BYTE_ORDER == BIG_ENDIAN
	for (int i=0; i<cnt; i++) {
		uint16 v;
		if (read(&v, 2) < 2)
			return false;
		v = ((v & 0xff00) >> 8)
			| ((v & 0x00ff) << 8);
		*((uint16 *)out) = v;
		out = ((uint16 *)out) + 1;
	}
	return true;
#else
	return read(out, 2 * cnt) == 2 * cnt;
#endif
}
	
bool File::readle32(void * out, int cnt) {
#if BYTE_ORDER == BIG_ENDIAN
	for (int i=0; i<cnt; i++) {
		uint32 v;
		if (read(&v, 4) < 2)
			return false;
		v = ((v & 0x000000ff) << 24) |
			((v & 0x0000ff00) << 8) |
			((v & 0x00ff0000) >> 8) |
			((v & 0xff000000) >> 24);
		*((uint32 *)out) = v;
		out = ((uint32 *)out) + 1;
	}
	return true;
#else
	return read(out, 4 * cnt) == 4 * cnt;
#endif
}

bool File::writele16(uint16 * in, int cnt) {
#if BYTE_ORDER == BIG_ENDIAN
	for (int i=0; i<cnt; i++) {
		uint16 v = *in;
		v = ((v & 0xff00) >> 8)
			| ((v & 0x00ff) << 8);

		if (write(&v, 2) < 2)
			return false;
		in = ((uint16 *)in) + 1;
	}
	return true;
#else
	return write(in, 2 * cnt) == 2 * cnt;
#endif
}

bool File::writele32(uint32 * in, int cnt) {
#if BYTE_ORDER == BIG_ENDIAN
	for (int i=0; i<cnt; i++) {
		uint16 v = *in;
		v = ((v & 0x000000ff) << 24) |
			((v & 0x0000ff00) << 8) |
			((v & 0x00ff0000) >> 8) |
			((v & 0xff000000) >> 24);
		
		if (write(&v, 4) < 4)
			return false;
		in = ((uint32 *)in) + 1;
	}
	return true;
#else
	return write(in, 4 * cnt) == 4 * cnt;
#endif
}

int File::seek(int where, int whence) {
	if (!isValid())
		return -1;

	return fseek(m_fd->m_fd, where, whence);
}

int File::tell() {
	if (!isValid())
		return -1;

	return ftell(m_fd->m_fd);
}

int File::total() {
	if (!isValid())
		return -1;

	int tmp = ftell(m_fd->m_fd);
	fseek(m_fd->m_fd, 0, SEEK_END);
	int rv = ftell(m_fd->m_fd);
	fseek(m_fd->m_fd, tmp, SEEK_SET);

	return rv;
}

FILE *	File::getFile() const {
	return m_fd->m_fd;
}
