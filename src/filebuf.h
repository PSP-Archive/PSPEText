/*
 *   PSPEText
 *
 *   Copyright (c) 2008-2009 Norman B. Lancaster
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FILEBUF_H_INCLUDED
#define FILEBUF_H_INCLUDED

#include <pspiofilemgr.h>

typedef struct
{
	const char *path;
	SceOff length;
	SceOff bufTop;
	SceOff bufLength;
	u8 *buf;
} FILEBUF;

int fbOpen(FILEBUF *fb, u8 *buf, SceOff bufLength);
int fbFromBuffer(FILEBUF *out, u8 *buf, SceOff bufLength, char *name);
void fbClose(FILEBUF *fb);
int fbReadByte(FILEBUF *fb, SceOff off);
int fbLoadBuffer(FILEBUF *fb);

#endif // FILEBUF_H_INCLUDED
