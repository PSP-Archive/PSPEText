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

FILEBUF mainFileBuf;
FILEBUF helpScreenBuffer;
int isMainFileLoaded = 0;
SceOff mainOffset = 0;
SceOff mainLine = 0;
char pFBParm[PET_FBPARM_LEN];
char pFBScratch[PET_FBSCRATCH_LEN];
char pFBListStrings[PET_FBLISTSTR_COUNT*PET_FBLISTSTR_LEN];
u8 pFBFileBuf[PET_FBFILEBUF_LEN];
char petFilePath[PET_FPATH_LEN] = "\0";

u32 petFGColor = PET_DEFAULT_FG;
u32 petBGColor = PET_DEFAULT_BG;
u32 petFGHLColor = PET_DEFAULT_FGHL;
u32 petBGHLColor = PET_DEFAULT_BGHL;
u32 petFGERColor = PET_DEFAULT_FGER;
u32 petBGERColor = PET_DEFAULT_BGER;


// Help screen text
char helpScreenText[] = "\
********************* Common Controls *********************\n\
[DPAD Up]    Move one line up\n\
[DPAD Down]  Move one line down\n\
[DPAD Left]  Move one page up\n\
[DPAD Right] Move one page down\n\
[Select]     Display this help file\n\
[Start]      Exit\n\
******************* File View Controls ********************\n\
[Triangle]   Open a new file\n\
****************** File Select Controls *******************\n\
[Triangle]   Got to parent directory\n\
[Cross]      Select file or directory\n\
***********************************************************\n";

int errorPrint(const char *str)
{
	bcSetPos(0, 0);
	bcSetFG(petFGERColor);
	bcSetBG(petBGERColor);
	bcPrintString(str, BC_PRINT_NONE);
	bcClearToEndOfLine();
	sceKernelDelayThread(1000000);
	bcSetPos(0, 0);
	bcSetFG(petFGColor);
	bcSetBG(petBGColor);
	bcClearToEndOfLine();
	sceKernelDelayThread(250000);
	return 1;
}
int displayBufferFrom(FILEBUF *buf, SceOff start)
{
	int i;
	int outLine = 1;
	int thisChar;
	int sHeight = bcGetHeight();
	//int sWidth = bcGetWidth();
	SceOff curOff = start;

	bcSetFG(petFGColor);
	bcSetBG(petBGColor);
	bcSetPos(0, outLine);
	while(1)
	{
		thisChar = fbReadByte(buf, curOff);
		// Past the end of the file or some other such badness
		if(thisChar < 0)
		{
			bcClearToEndOfLine();
			for(i = outLine; i < sHeight; ++ i)
			{
				bcSetPos(0, i);
				bcClearToEndOfLine();
			}
			break;
		}
		++curOff;

		// If this is a newline, do it
		if(thisChar == '\n')
		{
			//bcPrintChar('\001', BC_PRINT_NOSCROLL);
			bcClearToEndOfLine();

			++outLine;
			// Past the end of the display
			if(outLine >= sHeight) break;

			bcSetPos(0, outLine);
		}
		// If this is part of a Windows newline, ignore it
		else if(thisChar == '\r')
		{
			continue;
		}
		// Tab
		else if(thisChar == '\t')
		{
			for(i = 0; i < 4; ++i)
			{
				bcPrintChar(' ', BC_PRINT_NOSCROLL);
			}
		}
		// Otherwise just render the character
		else
		{
			bcPrintChar(thisChar, BC_PRINT_NOSCROLL);
		}
	}

	return 0;
}
void updateStatusBars(FILEBUF *p_fileBuf, SceOff *p_line, SceOff *p_offset)
{
	bcSetFG(petFGHLColor);
	bcSetBG(petBGHLColor);
	bcSetPos(0, 0);
	sprintf(pFBParm, "%8d | %-69s", (int)*p_line, p_fileBuf->path);
	bcPrintString(pFBParm, BC_PRINT_NOSCROLL);
	bcClearToEndOfLine();
	bcSetFG(petFGColor);
	bcSetBG(petBGColor);
}
/* Handle common input events.
 * returns 0 if the callee should continue input processing.
 * returns -1 if the callee should pump input events again.
 * returns -2 if the callee should exit.
 * returns > 0 on error.
 */
int petCommonInputHandler(int isHelpScreen)
{
	// Global change mode
	if(inIsKeyDown(PSPKEY_SQUARE))
	{
		return -1;
	}
	// Display help screen
	if(inWasKeyPressed(PSPKEY_SELECT) &&
		isHelpScreen == 0)
	{
		fbFromBuffer(&helpScreenBuffer, (u8*)helpScreenText,
			strlen(helpScreenText), "Help Screen");
		petBufferViewer(&helpScreenBuffer, NULL, NULL, 1);
		return -1;
	}
	// Exit when start is pressed
	if(inWasKeyPressed(PSPKEY_START))
	{
		return -2;
	}
	return 0;
}
int petBufferViewer(FILEBUF *p_fileBuf, SceOff *p_line, SceOff *p_offset, int isHelpScreen)
{
	int i, sHeight, returnCode = 0;
	SceOff offTemp;

	SceOff line, offset;
	if(p_line == NULL || p_offset == NULL)
	{
		line = 0;
		offset = 0;
	}
	else
	{
		line = *p_line;
		offset = *p_offset;
	}

	// Update the status bars
	updateStatusBars(p_fileBuf, &line, &offset);
	displayBufferFrom(p_fileBuf, offset);
	while(1)
	{
		inPumpInputEvents(PSP_INNONE);
		// Common events
		int ret = petCommonInputHandler(isHelpScreen);
		if(ret == -1)
		{
			displayBufferFrom(p_fileBuf, offset);
			updateStatusBars(p_fileBuf, &line, &offset);
			continue;
		}
		if(ret == -2 || ret > 0) break;
		// Line up
		if(inWasKeyPressed(PSPKEY_UP) &&
			line > 0)
		{
			--line;
			offset = scanForPrevLine(p_fileBuf, offset);
			displayBufferFrom(p_fileBuf, offset);
			updateStatusBars(p_fileBuf, &line, &offset);
		}
		// Line down
		if(inWasKeyPressed(PSPKEY_DOWN))
		{
			offTemp = scanForNextLine(p_fileBuf, offset);
			if(offTemp >= 0)
			{
				++line;
				offset = offTemp;
				displayBufferFrom(p_fileBuf, offset);
				updateStatusBars(p_fileBuf, &line, &offset);
			}
		}
		// Page up
		if(inWasKeyPressed(PSPKEY_LEFT))
		{
			sHeight = bcGetHeight();
			for(i = (sHeight - 5); i > 0 && line > 0; --i)
			{
				--line;
				offset = scanForPrevLine(p_fileBuf, offset);
			}
			displayBufferFrom(p_fileBuf, offset);
			updateStatusBars(p_fileBuf, &line, &offset);
		}
		// Page down
		if(inWasKeyPressed(PSPKEY_RIGHT))
		{
			sHeight = bcGetHeight();
			for(i = 0; i < (sHeight - 5); ++i)
			{
				offTemp = scanForNextLine(p_fileBuf, offset);
				if(offTemp >= 0)
				{
					++line;
					offset = offTemp;
				}
				else break;
			}
			displayBufferFrom(p_fileBuf, offset);
			updateStatusBars(p_fileBuf, &line, &offset);
		}
		// New file request, bubble this up
		if(inWasKeyPressed(PSPKEY_TRIANGLE))
		{
			returnCode = -1;
			break;
		}
	}
	if(p_line != NULL && p_offset != NULL)
	{
		*p_line = line;
		*p_offset = offset;
	}
	sceKernelDelayThread(250000);
	return returnCode;
}

void petOpenMainFile()
{
	// If the user did not cancel the UI, open the file
	if(!petGetFileName())
	{
		// Copy the file path into the statis RAM space
		strncpy(petFilePath, pFBScratch, PET_FPATH_LEN);
		petFilePath[PET_FPATH_LEN - 1] = 0;
		mainFileBuf.path = petFilePath;
		//errorPrint(mainFileBuf.path);
		if(fbOpen(&mainFileBuf, pFBFileBuf, PET_FBFILEBUF_LEN))
		{
			errorPrint("Unable to load file!");
			return;
		}
		mainOffset = 0;
		mainLine = 0;
		isMainFileLoaded = 1;
	}
}

int petMain()
{
	int returnCode = 0;

	// Init the console and set up our special pointers
	bcInit(0);

	// Splash screen with 2 second delay to let folks get off the trigger keys
	bcSetPos(31, 15);
	bcPrintString("PSPEText by QBRADQ", 0);
	bcSetPos(29, 17);
	bcPrintString("Press [select] for Help", 0);
	sceKernelDelayThread(2000000);

	// If there is no file open
	if(!isMainFileLoaded)
	{
		petOpenMainFile();
	}

	// If we have a file open, run the main interface
	if(isMainFileLoaded)
	{
		// Force the file to reload it's buffer
		mainFileBuf.buf = pFBFileBuf;
		fbLoadBuffer(&mainFileBuf);
		while(1)
		{
			returnCode = petBufferViewer(&mainFileBuf, &mainLine, &mainOffset, 0);
			if(returnCode == -1)
			{
				petOpenMainFile();
				continue;
			}
			break;
		}
	}

	// Exit splash screen with .5 second delay to let folks get off the
	// start button.
	bcClear();
	bcSetPos(36, 15);
	bcPrintString("Bye Bye", 0);
	sceKernelDelayThread(500000);
	bcKill();
	return 0;
}
