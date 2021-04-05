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

#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#include <string.h>

#define LOGFILE "ms0:/debug.log"
#define TEXT_BUF_LENGTH		1024

// Debuging enabled
#ifdef DEBUG

	// PSPLink debugging enabled
	#ifdef PSPLINK_DEBUG
		#define debugPrintf(fmt, args...) {printf(fmt, args);}
	#else//PSPLINK_DEBUG
		void debugPrintf(const char *fmt, ...);
	#endif//PSPLINK_DEBUG
#else//DEBUG
	#define debugPrintf(fmt, args...) {}
#endif//DEBUG

#endif // DEBUG_H_INCLUDED
