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

#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "basecon.h"
#include "debug.h"
#include "input.h"
#include "filebuf.h"
#include "pspetext.h"
#include "font.h"

SceOff scanForPrevLine(FILEBUF *buf, SceOff start)
{
	int thisChar;
	SceOff curOfs = start;

	// Go back to the previous \n
	while(1)
	{
		// No previous line
		if(curOfs < 0) return 0;
		thisChar = fbReadByte(buf, curOfs);
		if(thisChar == '\n') break;
		--curOfs;
	}

	// Scan back until we find the next \n
	--curOfs;
	while(1)
	{
		// We have hit the begining of the file
		if(curOfs < 0)
		{
			return 0;
		}
		thisChar = fbReadByte(buf, curOfs);
		// We have hit the preceeding \n, so report the start of the line as ofs+1
		if(thisChar == '\n')
		{
			// The exception is for a UNIX line ending file with blank lines.
			if(curOfs + 1 != start) return curOfs + 1;
		}
		--curOfs;
	}

	// Should never get here
	return -1;
}
SceOff scanForNextLine(FILEBUF *buf, SceOff start)
{
	int thisChar;
	SceOff curOfs = start;

	// Go forward to the next \n
	while(1)
	{
		thisChar = fbReadByte(buf, curOfs);

		// We have hit the next \n, so the address of the next line is ofs+1
		if(thisChar == '\n')
		{
			// But only if it is within a valid range
			if(curOfs + 1 < buf->length) return curOfs + 1;
			else return -1;
		}
		// This means we are past EoF
		else if(thisChar < 0) return -1;
		++curOfs;
	}

	// Should never get here
	return -1;
}
