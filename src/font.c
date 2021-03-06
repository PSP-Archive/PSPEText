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
#include "font.h"

u8 font6x8_bits[] = {
   0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xac, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x34, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xac, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x34, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xb6, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x04, 0x84, 0x50, 0x3c, 0x07, 0x20, 0x08, 0x02, 0x00, 0x00, 0x80, 0xf8,
   0x0c, 0xc6, 0x51, 0xaa, 0x08, 0x70, 0x1c, 0x82, 0x20, 0x00, 0x85, 0xf8,
   0x1c, 0xe7, 0x53, 0x2a, 0x03, 0xf8, 0x3e, 0x82, 0x31, 0x00, 0xc5, 0x71,
   0xbc, 0x87, 0x50, 0x2c, 0x05, 0x20, 0x08, 0xe2, 0xfb, 0x82, 0xcf, 0x71,
   0x1c, 0xe7, 0x53, 0x28, 0x06, 0xf8, 0x88, 0x8f, 0x31, 0x02, 0xe5, 0x23,
   0x0c, 0xc6, 0x01, 0xa8, 0xe8, 0x71, 0x08, 0x87, 0x20, 0x02, 0xe5, 0x23,
   0x04, 0x84, 0x50, 0x28, 0xe7, 0x21, 0x08, 0x02, 0x00, 0x3e, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x62, 0x03, 0x84, 0x49, 0x30, 0x08, 0x01, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x67, 0x53, 0x9c, 0xa9, 0x30, 0x04, 0x42, 0x21, 0x00, 0x00, 0x80,
   0x00, 0x27, 0xf9, 0x02, 0xa4, 0x10, 0x04, 0xc2, 0x21, 0x00, 0x00, 0x40,
   0x00, 0x02, 0x50, 0x0c, 0x42, 0x00, 0x04, 0xe2, 0xfb, 0x80, 0x0f, 0x20,
   0x00, 0x02, 0x50, 0x10, 0xa1, 0x02, 0x04, 0xc2, 0x21, 0x00, 0x00, 0x10,
   0x00, 0x00, 0xf8, 0x8e, 0x2c, 0x01, 0x04, 0x42, 0x21, 0x0c, 0xc0, 0x08,
   0x00, 0x02, 0x50, 0x88, 0xcc, 0x02, 0x08, 0x01, 0x00, 0x0c, 0xc0, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00,
   0x1c, 0xc2, 0x71, 0x90, 0x8f, 0xf9, 0x1c, 0x07, 0x00, 0x10, 0x40, 0x70,
   0x22, 0x23, 0x8a, 0x98, 0x40, 0x80, 0xa2, 0x08, 0x00, 0x08, 0x80, 0x88,
   0x32, 0x02, 0x82, 0x94, 0x20, 0x40, 0xa2, 0xc8, 0x30, 0x84, 0x0f, 0x81,
   0x2a, 0x82, 0x71, 0x92, 0xe7, 0x21, 0x1c, 0xcf, 0x30, 0x02, 0x00, 0x62,
   0x26, 0x42, 0x80, 0x3e, 0x28, 0x12, 0x22, 0x08, 0x00, 0x04, 0x00, 0x21,
   0x22, 0x22, 0x88, 0x90, 0x28, 0x12, 0x22, 0xc4, 0x30, 0x88, 0x8f, 0x00,
   0x1c, 0xe7, 0x73, 0x10, 0xc7, 0x11, 0x1c, 0xc3, 0x30, 0x10, 0x40, 0x20,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
   0x1c, 0xe7, 0x71, 0x9e, 0xef, 0x73, 0x22, 0x07, 0x8a, 0x82, 0x28, 0x72,
   0xa2, 0x28, 0x8a, 0xa2, 0x20, 0x88, 0x22, 0x02, 0x4a, 0x82, 0x6d, 0x8a,
   0xba, 0x28, 0x0a, 0xa2, 0x20, 0x08, 0x22, 0x02, 0x2a, 0x82, 0xaa, 0x8a,
   0xaa, 0xe8, 0x09, 0xa2, 0xe7, 0xe9, 0x3e, 0x02, 0x1a, 0x82, 0x28, 0x8b,
   0xba, 0x2f, 0x0a, 0xa2, 0x20, 0x88, 0x22, 0x22, 0x2a, 0x82, 0x28, 0x8a,
   0x82, 0x28, 0x8a, 0xa2, 0x20, 0x88, 0x22, 0x22, 0x4a, 0x82, 0x28, 0x8a,
   0x9c, 0xe8, 0x71, 0x9e, 0x2f, 0xf0, 0x22, 0xc7, 0x89, 0xbe, 0x28, 0x72,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x1e, 0xe7, 0x71, 0xbe, 0x28, 0x8a, 0xa2, 0xe8, 0x71, 0x00, 0x87, 0x00,
   0xa2, 0x28, 0x8a, 0x88, 0x28, 0x8a, 0xa2, 0x08, 0x11, 0x02, 0x44, 0x01,
   0xa2, 0x28, 0x0a, 0x88, 0x28, 0xaa, 0x94, 0x88, 0x10, 0x04, 0x24, 0x02,
   0x9e, 0xe8, 0x71, 0x88, 0x28, 0xaa, 0x08, 0x45, 0x10, 0x08, 0x04, 0x00,
   0x82, 0x2a, 0x81, 0x88, 0x28, 0xaa, 0x14, 0x22, 0x10, 0x10, 0x04, 0x00,
   0x82, 0x24, 0x8a, 0x88, 0x48, 0xa9, 0x22, 0x22, 0x10, 0x20, 0x04, 0x00,
   0x02, 0x2b, 0x72, 0x08, 0x87, 0x50, 0x22, 0xe2, 0x71, 0x00, 0x07, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc,
   0x0c, 0x20, 0x00, 0x20, 0x80, 0x01, 0x02, 0x02, 0x09, 0x08, 0x00, 0x00,
   0x0c, 0x20, 0x00, 0x20, 0x40, 0x00, 0x02, 0x00, 0x08, 0x08, 0x00, 0x00,
   0x08, 0xe7, 0x71, 0x3c, 0x47, 0xf0, 0x0e, 0x82, 0x49, 0x88, 0xe5, 0x70,
   0x00, 0x28, 0x8a, 0xa2, 0xe8, 0x89, 0x12, 0x02, 0x29, 0x88, 0x2a, 0x89,
   0x00, 0x2f, 0x0a, 0xa2, 0x47, 0x88, 0x12, 0x02, 0x19, 0x88, 0x2a, 0x89,
   0x80, 0x28, 0x8a, 0xa2, 0x40, 0xf0, 0x12, 0x02, 0x29, 0x88, 0x28, 0x89,
   0x00, 0xef, 0x71, 0x3c, 0x47, 0x80, 0x12, 0x26, 0x49, 0x98, 0x28, 0x71,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x08, 0x43, 0x21,
   0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0xa4, 0x70,
   0x1e, 0xaf, 0x71, 0x9e, 0x24, 0x8a, 0x92, 0xe4, 0x11, 0x08, 0x04, 0xd8,
   0xa2, 0x48, 0x0a, 0x84, 0x24, 0x8a, 0x92, 0x04, 0x19, 0x00, 0x0c, 0x88,
   0xa2, 0x48, 0x70, 0x84, 0x24, 0xaa, 0x8c, 0xc4, 0x10, 0x08, 0x04, 0x88,
   0xa2, 0x48, 0x80, 0x94, 0x46, 0xf9, 0x12, 0x27, 0x10, 0x08, 0x04, 0xf8,
   0x1e, 0xef, 0x70, 0x08, 0x85, 0x50, 0x12, 0xe2, 0x61, 0x08, 0x03, 0x00,
   0x02, 0x08, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00,
   0x9c, 0x04, 0x73, 0x14, 0xc3, 0x01, 0x1c, 0xc5, 0x50, 0x08, 0x41, 0x71,
   0x22, 0x00, 0x00, 0x00, 0x40, 0x71, 0x00, 0x00, 0x00, 0x14, 0x00, 0x50,
   0x82, 0xc4, 0x71, 0x1c, 0xc7, 0x89, 0x1c, 0xc7, 0x21, 0x00, 0x82, 0x70,
   0x82, 0x24, 0x82, 0x20, 0x08, 0x0a, 0xa2, 0x28, 0x22, 0x08, 0x42, 0xd9,
   0xa2, 0xe4, 0xf1, 0x3c, 0xcf, 0x8b, 0x9e, 0xe7, 0x21, 0x08, 0x22, 0x8a,
   0x9c, 0x26, 0x88, 0xa2, 0x28, 0x72, 0x82, 0x20, 0x20, 0x08, 0xe2, 0xfb,
   0x08, 0xc5, 0xf1, 0x3c, 0xcf, 0x23, 0x1c, 0xc7, 0x61, 0x18, 0x26, 0x8a,
   0x0c, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x30, 0xc0, 0x73, 0x94, 0xc1, 0x19, 0x94, 0x44, 0x01, 0x98, 0x68, 0x40,
   0x00, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x20, 0x24, 0xa5, 0xa0,
   0xbe, 0xa7, 0x30, 0x0c, 0x23, 0x49, 0x92, 0x24, 0x71, 0x04, 0xa2, 0x20,
   0x02, 0xea, 0x4b, 0x92, 0x24, 0x49, 0x92, 0x24, 0x09, 0x9e, 0x6f, 0x71,
   0x9e, 0xaf, 0x48, 0x92, 0x24, 0x49, 0x92, 0x24, 0x09, 0x04, 0xa2, 0x23,
   0x82, 0xa2, 0x48, 0x92, 0xa4, 0x69, 0x9c, 0x24, 0x71, 0xa4, 0x2f, 0x21,
   0x3e, 0xaf, 0x33, 0x0c, 0x43, 0x51, 0x08, 0xc3, 0x20, 0x3a, 0x22, 0x29,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x10,
   0x18, 0x86, 0x61, 0x14, 0xc5, 0x31, 0x08, 0x00, 0x08, 0x02, 0x02, 0x00,
   0x00, 0x00, 0x00, 0x8a, 0x02, 0x4a, 0x00, 0x00, 0x48, 0x12, 0x00, 0x00,
   0x1c, 0xc2, 0x48, 0x00, 0xc0, 0x4b, 0x88, 0xff, 0x2b, 0x0a, 0x42, 0x4a,
   0x20, 0x22, 0x49, 0x8e, 0x24, 0x4a, 0x8c, 0x00, 0x72, 0x34, 0x22, 0x91,
   0x3c, 0x22, 0x49, 0x92, 0xc5, 0x33, 0x82, 0x00, 0x8a, 0x2a, 0x47, 0x4a,
   0x22, 0x22, 0x69, 0x92, 0x06, 0x00, 0xa2, 0x00, 0x40, 0x38, 0x07, 0x00,
   0x3c, 0xc6, 0x50, 0x92, 0xc4, 0x7b, 0x1c, 0x00, 0xe0, 0x20, 0x02, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xaa, 0x5a, 0x21, 0x08, 0xa2, 0x00, 0x80, 0xa2, 0x00, 0x8a, 0x82, 0x00,
   0x40, 0xf5, 0x23, 0xc8, 0xa3, 0x00, 0xcf, 0xa2, 0x3c, 0x8b, 0xf2, 0x00,
   0x95, 0xaa, 0x22, 0x08, 0xa2, 0x00, 0x08, 0xa2, 0x20, 0x88, 0x82, 0x00,
   0x40, 0xf5, 0x23, 0xcf, 0xb3, 0x3c, 0xcf, 0xa2, 0x2c, 0xcf, 0xf3, 0x3c,
   0xaa, 0x5a, 0x21, 0x08, 0xa2, 0x28, 0x88, 0xa2, 0x28, 0x00, 0x00, 0x20,
   0x40, 0xf5, 0x23, 0x08, 0xa2, 0x28, 0x88, 0xa2, 0x28, 0x00, 0x00, 0x20,
   0x95, 0xaa, 0x22, 0x08, 0xa2, 0x28, 0x88, 0xa2, 0x28, 0x00, 0x00, 0x20,
   0x40, 0xf5, 0x23, 0x08, 0xa2, 0x28, 0x88, 0xa2, 0x28, 0x00, 0x00, 0x20,
   0x08, 0x02, 0x20, 0x00, 0x82, 0x28, 0x0a, 0xa0, 0x00, 0x0a, 0xa0, 0x20,
   0x08, 0x02, 0x20, 0x00, 0x82, 0x2b, 0xba, 0xbf, 0xff, 0xfa, 0xbf, 0xff,
   0x08, 0x02, 0x20, 0x00, 0x82, 0x28, 0x82, 0x00, 0x00, 0x02, 0x00, 0x00,
   0xf8, 0xff, 0xe3, 0xff, 0x8f, 0xeb, 0xbe, 0xfe, 0xef, 0xfa, 0xbf, 0xff,
   0x00, 0x80, 0x20, 0x00, 0x82, 0x28, 0x80, 0x02, 0x28, 0x0a, 0xa0, 0x00,
   0x00, 0x80, 0x20, 0x00, 0x82, 0x28, 0x80, 0x02, 0x28, 0x0a, 0xa0, 0x00,
   0x00, 0x80, 0x20, 0x00, 0x82, 0x28, 0x80, 0x02, 0x28, 0x0a, 0xa0, 0x00,
   0x00, 0x80, 0x20, 0x00, 0x82, 0x28, 0x80, 0x02, 0x28, 0x0a, 0xa0, 0x00,
   0x0a, 0x00, 0x28, 0x08, 0x00, 0x28, 0x08, 0x02, 0xfc, 0xc0, 0x81, 0xff,
   0xca, 0x0f, 0x28, 0x38, 0x0e, 0x28, 0x3f, 0x02, 0xfc, 0xc0, 0x81, 0xff,
   0x0a, 0x00, 0x28, 0x08, 0x02, 0x28, 0x00, 0x02, 0xfc, 0xc0, 0x81, 0xff,
   0xff, 0xff, 0xfb, 0x38, 0xee, 0xef, 0xff, 0x83, 0xff, 0xc0, 0x81, 0xff,
   0x00, 0xa2, 0x00, 0x00, 0xa2, 0x28, 0x08, 0x80, 0xfc, 0xff, 0x81, 0x03,
   0x00, 0xa2, 0x00, 0x00, 0xa2, 0x28, 0x08, 0x80, 0xfc, 0xff, 0x81, 0x03,
   0x00, 0xa2, 0x00, 0x00, 0xa2, 0x28, 0x08, 0x80, 0xfc, 0xff, 0x81, 0x03,
   0x00, 0xa2, 0x00, 0x00, 0xa2, 0x28, 0x08, 0x80, 0xfc, 0xff, 0x81, 0x03,
   0x00, 0xe0, 0x01, 0x1e, 0x00, 0x00, 0x1c, 0x03, 0x30, 0x00, 0x00, 0x00,
   0x80, 0x23, 0xf9, 0x12, 0x00, 0x00, 0x88, 0xc4, 0x09, 0x00, 0xc2, 0x31,
   0xac, 0x24, 0x50, 0x04, 0x2f, 0x51, 0x9c, 0x24, 0x12, 0x14, 0x27, 0x48,
   0x92, 0x23, 0x50, 0x88, 0x24, 0x29, 0xa2, 0x27, 0x22, 0xaa, 0xea, 0x49,
   0x92, 0x24, 0x50, 0x84, 0x24, 0x21, 0x9c, 0x44, 0x71, 0xaa, 0x2a, 0x48,
   0xac, 0x24, 0x50, 0x12, 0xe3, 0x20, 0x88, 0x44, 0x49, 0x14, 0xc7, 0x49,
   0x80, 0x23, 0x50, 0x1e, 0x20, 0x20, 0x1c, 0x63, 0x33, 0x00, 0x02, 0x00,
   0x80, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x20, 0x40, 0x00, 0x02, 0x00, 0x0c, 0x00, 0x00, 0x8a, 0x01, 0x00,
   0x1e, 0xc2, 0x30, 0x10, 0x82, 0x50, 0x12, 0x00, 0xe0, 0x14, 0x02, 0x00,
   0x00, 0x07, 0x09, 0x28, 0x02, 0x28, 0x12, 0x00, 0x20, 0x14, 0xe1, 0x01,
   0x1e, 0xc2, 0x30, 0x08, 0xe2, 0x03, 0x0c, 0x43, 0x20, 0x94, 0xe3, 0x01,
   0x00, 0x20, 0x40, 0x08, 0x02, 0x50, 0x00, 0x03, 0x28, 0x00, 0xe0, 0x01,
   0x1e, 0x07, 0x00, 0x88, 0x82, 0x28, 0x00, 0x00, 0x28, 0x00, 0xe0, 0x01,
   0x00, 0xe0, 0x79, 0x08, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

FONTSPEC fonts[FONT_NUM] = {
	{  6,  8, 12, 80, 34, 0, 0, font6x8_bits		}
};
