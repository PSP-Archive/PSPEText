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

#include <pspiofilemgr.h>

SceIoDirent dirEnt;

int petDirContents(int top)
{
	int i, dret, retVal;
	SceUID dirFD;
	char *outStr;

	// Open the directory
	dirFD = sceIoDopen(pFBScratch);
	if(dirFD < 0) return errorPrint("Unable to open directory");

	// Seek to the top
	for(i = 0; i < top; ++i)
	{
		dret = sceIoDread(dirFD, &dirEnt);
		// Out of files, bail
		if(dret <= 0)
		{
			sceIoDclose(dirFD);
			return 0;
		}
	}

	// Start loading file names unitl we're at the limit'
	retVal = PET_FBLISTSTR_COUNT;
	for(i = 0; i < PET_FBLISTSTR_COUNT; ++i)
	{
		// Break on out-of-files
		dret = sceIoDread(dirFD, &dirEnt);
		if(dret <= 0)
		{
			retVal = i;
			break;
		}

		// Copy over the file name
		outStr = &pFBListStrings[i * PET_FBLISTSTR_LEN];
		strncpy(outStr, dirEnt.d_name, PET_FBLISTSTR_LEN);
		outStr[PET_FBLISTSTR_LEN - 1] = 0;
		// And flag it a directory if it is
		if(dirEnt.d_stat.st_attr & 0x00000010)
		{
			size_t len = strlen(outStr);
			if(len < PET_FBLISTSTR_LEN - 1)
			{
				outStr[len] = '/';
				outStr[len + 1] = 0;
			}
			else
			{
				outStr[PET_FBLISTSTR_LEN - 1] = '/';
			}
		}
	}

	sceIoDclose(dirFD);
	return retVal;
}
int petDirGetNode(int node, unsigned int *attr)
{
	int i, dret;
	SceUID dirFD;

	// Open the directory
	dirFD = sceIoDopen(pFBScratch);
	if(dirFD < 0) return errorPrint("Unable to open directory");

	// Seek to the node
	for(i = 0; i <= node; ++i)
	{
		dret = sceIoDread(dirFD, &dirEnt);
		// Out of files, bail
		if(dret <= 0)
		{
			sceIoDclose(dirFD);
			return 0;
		}
	}

	// Now the file in question is in dret, so copy the name into pFBParam
	// and record the attributes.
	strncpy(pFBParm, dirEnt.d_name, PET_FBPARM_LEN);
	pFBParm[PET_FBPARM_LEN - 1] = 0;
	*attr = dirEnt.d_stat.st_attr;
	sceIoDclose(dirFD);
	return 0;
}
/* Uses the list UI to get a file name, which is stored into pFBScratch. If
 * the return code is non-zero the action was canceled or errored.
 */
int petGetFileName()
{
	char *tChar;
	unsigned int attr;
	int ret;

	// Init directory
	memcpy(pFBScratch, petFilePath, PET_FPATH_LEN);
	// No directory set yet
	if(pFBScratch[0] == 0)
	{
		strncpy(pFBScratch, PET_DEFAULT_DIR, PET_FBSCRATCH_LEN);
		pFBScratch[PET_FBSCRATCH_LEN - 1] = 0;
	}
	// We have a file path, not a directory
	else if(pFBScratch[strlen(pFBScratch) - 1] != '/')
	{
		// Truncate to the directory
		tChar = rindex(pFBScratch, '/');
		if(tChar != NULL)
		{
			++tChar;
			*tChar = 0;
		}
	}

	// Init screen
	bcClear();

	while(1)
	{
		ret = petListProc(pFBScratch, &petDirContents);
		// Selected something
		if(ret >= 0)
		{
			petDirGetNode(ret, &attr);
			//errorPrint(pFBParm);

			// User selected a directory
			if(attr & 0x00000010)
			{
				// The "this directory" entry
				if(strcmp(pFBParm, ".") == 0)
				{
					// DO NOTHING, it's not needed
				}
				// The "parent directory" entry
				else if(strcmp(pFBParm, "..") == 0)
				{
					// Strip the trailing slash from the current path
					pFBScratch[strlen(pFBScratch)-1] = 0;
					// Find the preceeding slash
					tChar = rindex(pFBScratch, '/');
					// And truncate the string at that point
					if(tChar != NULL)
					{
						++tChar;
						*tChar = 0;
					}
					// This should not happen
					else return errorPrint("rindex() failed during parent directory traversal");
				}
				// Just a regular directory
				else
				{
					strncat(pFBScratch, pFBParm, PET_FBPARM_LEN);
					strncat(pFBScratch, "/", PET_FBPARM_LEN);
					if(strlen(pFBScratch) >= PET_FBPARM_LEN - 1)
						return errorPrint("Path overflow");
				}
			}
			// User selected a file
			else
			{
				//errorPrint("Regular file!");
				//errorPrint(pFBScratch);
				//errorPrint(pFBParm);
				strncat(pFBScratch, pFBParm, PET_FBPARM_LEN);
				//errorPrint(pFBScratch);
				break;
			}
		}
		// User exited with triangle, back up one directory
		else if(ret == -1)
		{
			// Strip the trailing slash from the current path
			pFBScratch[strlen(pFBScratch)-1] = 0;
			// Find the preceeding slash
			tChar = rindex(pFBScratch, '/');
			// And truncate the string at that point
			if(tChar != NULL)
			{
				++tChar;
				*tChar = 0;
			}
			// This means we are already at the root, so just slap the trailing slash back on there.
			else
			{
				strcat(pFBScratch, "/");
			}
		}
		// User exited with circle, cancel
		else if(ret == -2)
		{
			return -1;
		}
	}
	return 0;
}
