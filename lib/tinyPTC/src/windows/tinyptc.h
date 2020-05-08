//
// This file is part of tinyPTC, UA version 2019
// Based on TinyPTC-X11-0.7.3 and TinyPTC-Windows-0.8
// Copyright (C) 2002 by Glenn Fiedler (gaffer@gaffer.org)
// Copyright (C) 2002 by Alessandro Gatti (a.gatti@tiscali.it)
// Copyright (C) 2002 by Fred Howell (foohoo@shaw.ca)
// Copyright (C) 2019 by Francisco J. Gallego-Durán (@FranGallegoBR)
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//

//
// TinyPTC by Gaffer
// www.gaffer.org/tinyptc
//

#ifndef __TINYPTC_WINDOWS_H
#define __TINYPTC_WINDOWS_H

#include <stdint.h>

// integer types
typedef uint32_t int32;
typedef uint16_t short16;
typedef uint8_t char8;

// tinyptc api
typedef unsigned long KeySym;
extern int ptc_open(const char *title,int width,int height);
extern int ptc_update(void *buffer);
extern void ptc_set_on_keypress  ( void (*onkeypress)  (KeySym) );
extern void ptc_set_on_keyrelease( void (*onkeyrelease)(KeySym) );
extern void ptc_close();
inline int ptc_process_events(void) { return 0; }

// display target
#define __PTC_DDRAW__
//#define __PTC_GDI__
//#define __PTC_VFW__

// configuration
#define __PTC_WINDOWED__
#define __PTC_CENTER_WINDOW__
#define __PTC_RESIZE_WINDOW__
#define __PTC_SYSTEM_MENU__
#define __PTC_ICON__ "IDI_MAIN"
#define __PTC_ALLOW_CLOSE__
#define __PTC_CLOSE_ON_ESCAPE__
#define __PTC_DISABLE_SCREENSAVER__

// converter configuration
#define __PTC_CONVERTER_32_TO_32_RGB888
#define __PTC_CONVERTER_32_TO_32_BGR888
#define __PTC_CONVERTER_32_TO_24_RGB888
#define __PTC_CONVERTER_32_TO_24_BGR888
#define __PTC_CONVERTER_32_TO_16_RGB565
#define __PTC_CONVERTER_32_TO_16_BGR565
#define __PTC_CONVERTER_32_TO_16_RGB555
#define __PTC_CONVERTER_32_TO_16_BGR555

// endian configuration
#define __PTC_LITTLE_ENDIAN__

// linker configuration
//#define __PTC_WINMAIN_CRT__
#define __PTC_MAIN_CRT__


#endif
