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

#ifndef PSPETEXT_H_INCLUDED
#define PSPETEXT_H_INCLUDED

#include "filebuf.h"

// Static memory buffers and thier dimensions. The FB* naming convention comes
// from when I shoved this into the first few lines of the frame buffer. I
// just don't feel like refactoring this.
#define	PET_FBPARM_LEN			256
extern char pFBParm[PET_FBPARM_LEN];

#define	PET_FBSCRATCH_LEN		256
extern char pFBScratch[PET_FBSCRATCH_LEN];

// This is NOT an array of pointers, but one big buffer.
#define	PET_FBLISTSTR_COUNT		33
#define	PET_FBLISTSTR_LEN		80
extern char pFBListStrings[PET_FBLISTSTR_COUNT*PET_FBLISTSTR_LEN];

#define	PET_FBFILEBUF_LEN		4096
extern u8 pFBFileBuf[PET_FBFILEBUF_LEN];

#define	PET_FPATH_LEN			256
extern char petFilePath[PET_FPATH_LEN];

// Globals
extern u32 petFGColor;
extern u32 petBGColor;
extern u32 petFGHLColor;
extern u32 petBGHLColor;
extern u32 petFGERColor;
extern u32 petBGERColor;

// Global functions
int errorPrint(const char *str);
int petMain();
int petCommonInputHandler(int isHelpScreen);
int petGetFileName();
int petBufferViewer(FILEBUF *p_fileBuf, SceOff *p_line, SceOff *p_offset, int isHelpScreen);
SceOff scanForPrevLine(FILEBUF *buf, SceOff start);
SceOff scanForNextLine(FILEBUF *buf, SceOff start);
int petListProc(const char *statusLine, int(*refreshList)(int));

#endif // PSPETEXT_H_INCLUDED
