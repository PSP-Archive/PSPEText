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

#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

// Input options
#define	PSP_REPEAT_DELAY	15
#define PSP_REPEAT_TICKS	3
#define PSP_MICRO_PER_FRAME	16667

// Input flags
#define PSP_INNONE			0x00000000
#define PSP_INASYNC			0x00000001

// Internal key enum
enum PSPKeyName {
	PSPKEY_SELECT = 0,
	PSPKEY_START,
	PSPKEY_UP,
	PSPKEY_RIGHT,
	PSPKEY_DOWN,
	PSPKEY_LEFT,
	PSPKEY_LTRIGGER,
	PSPKEY_RTRIGGER,
	PSPKEY_TRIANGLE,
	PSPKEY_CIRCLE,
	PSPKEY_CROSS,
	PSPKEY_SQUARE,
	PSPKEY_LAST
};

void inPumpInputEvents(int flags);
int inWasKeyPressed();


#endif // INPUT_H_INCLUDED