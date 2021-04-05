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

#ifndef BASECON_H_INCLUDED
#define BASECON_H_INCLUDED

#define BASECON_DEBUG

#include <psptypes.h>

// Print String flags
#define BC_PRINT_NONE		0x00000000
#define BC_PRINT_NOSCROLL	0x00000001

int bcInit(int font);
void bcKill();
int bcGetWidth();
int bcGetHeight();
void bcSetPos(int x, int y);
void bcPrintChar(int c, int flags);
void bcPrintString(const char *str, int flags);
void bcClear();
void bcRenderChar(int x, int y, int c);
void bcSetFG(u32 c);
void bcSetBG(u32 c);
void bcClearToEndOfLine();

#endif // BASECON_H_INCLUDED
