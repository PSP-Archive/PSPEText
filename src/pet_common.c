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
#include "pspetext.h"
#include "basecon.h"
#include "input.h"


void petDisplayList(int hlit, int count)
{
	int sHeight, outLine, entry;
	sHeight = bcGetHeight();

	bcSetBG(petBGColor);
	// Display directory contents
	for(outLine = 1; outLine < sHeight; ++outLine)
	{
		bcSetPos(0, outLine);
		entry = (outLine - 1);
		if(entry >= count)
		{
			bcSetFG(petFGColor);
			bcSetBG(petBGColor);
			bcClearToEndOfLine();
			continue;
		}
		if(hlit == entry)
		{
			bcSetFG(petFGHLColor);
			bcSetBG(petBGHLColor);
			bcPrintString("\020", BC_PRINT_NONE);
		}
		else
		{
			bcSetFG(petFGColor);
			bcSetBG(petBGColor);
			bcPrintString(" ", BC_PRINT_NONE);
		}
		bcPrintString(&pFBListStrings[entry * PET_FBLISTSTR_LEN],
			BC_PRINT_NOSCROLL);
		bcClearToEndOfLine();
	}
	return;
}
/* List display proc, reads all list items from the specail pFBListStrings
 * pointer. The refreshList function should take one parameter, the new top
 * list index, and return the number of list items that are now valid.
 */
int petListProc(const char *statusLine, int(*refreshList)(int))
{
	// Init list UI
	int sel = 0;
	int top = 0;
	int onScreenCount = 0;

	// Print status line
	bcSetFG(petFGHLColor);
	bcSetBG(petBGHLColor);
	bcSetPos(0, 0);
	bcPrintString(statusLine, BC_PRINT_NOSCROLL);
	bcClearToEndOfLine();

	// Get the inital list
	onScreenCount = refreshList(top);
	if(onScreenCount <= 0) return -126;
	petDisplayList(sel - top, onScreenCount);

	// Input loop
	while(1)
	{
		inPumpInputEvents(PSP_INNONE);
		// Common events
		int ret = petCommonInputHandler(0);
		if(ret == -1)
		{
			petDisplayList(sel - top, onScreenCount);
			continue;
		}
		if(ret == -2 || ret > 0) return -2;
		// Line down
		if(inWasKeyPressed(PSPKEY_DOWN))
		{
			// Down in middle of list
			if(sel - top < onScreenCount - 1)
			{
				++sel;
				petDisplayList(sel - top, onScreenCount);
			}
			// Down at bottom of list when there is more list left
			else if(sel - top == onScreenCount - 1 &&
				onScreenCount == PET_FBLISTSTR_COUNT)
			{
				top = sel;
				onScreenCount = refreshList(top);
				if(onScreenCount <= 0) return -126;
				petDisplayList(sel - top, onScreenCount);
			}
		}
		// Line up
		if(inWasKeyPressed(PSPKEY_UP))
		{
			// Up in middle of list
			if(sel - top > 0)
			{
				--sel;
				petDisplayList(sel - top, onScreenCount);
			}
			// Up at tome of list when there is more list left
			else if(sel == top && top > 0)
			{
				top = top - (PET_FBLISTSTR_COUNT - 1);
				if(top < 0) top = 0;
				onScreenCount = refreshList(top);
				if(onScreenCount <= 0) return -126;
				petDisplayList(sel - top, onScreenCount);
			}
		}
		// Page down
		if(inWasKeyPressed(PSPKEY_RIGHT))
		{
			// Not and end of list
			if(onScreenCount == PET_FBLISTSTR_COUNT)
			{
				top += PET_FBLISTSTR_COUNT - 1;
				sel = top;
				onScreenCount = refreshList(top);
				if(onScreenCount <= 0) return -126;
				petDisplayList(sel - top, onScreenCount);
			}
			// At end of list
			else
			{
				sel = top + onScreenCount - 1;
				petDisplayList(sel - top, onScreenCount);
			}
		}
		// Page up
		if(inWasKeyPressed(PSPKEY_LEFT))
		{
			// Not and top of list
			if(top != 0)
			{
				top -= PET_FBLISTSTR_COUNT - 1;
				if(top < 0) top = 0;
				sel = top;
				onScreenCount = refreshList(top);
				if(onScreenCount <= 0) return -126;
				petDisplayList(sel - top, onScreenCount);
			}
			// At top of list
			else
			{
				sel = top;
				petDisplayList(sel - top, onScreenCount);
			}
		}
		// Item selected
		if(inWasKeyPressed(PSPKEY_CROSS))
		{
			return sel;
		}
		// Exit with triangle
		if(inWasKeyPressed(PSPKEY_TRIANGLE))
		{
			return -1;
		}
		// Exit with circle
		if(inWasKeyPressed(PSPKEY_CIRCLE))
		{
			return -2;
		}

		// Rerender display
		petDisplayList(sel - top, onScreenCount);
	}

	// Should never execute
	return -126;
}
