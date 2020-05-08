//
// This file is part of tinyPTC, UA version 2019
// Based on TinyPTC-X11-0.7.3 XVideo with Shared Memory Extension target
// Copyright (C) 2002 by Fred Howell (foohoo@shaw.ca)
// Copyright (C) 2002 by Alessandro Gatti (a.gatti@tiscali.it)
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

#ifndef __PTC_XVSHM_H
#define __PTC_XVSHM_H

#include "tinyptc.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XShm.h>
#include <X11/extensions/Xvlib.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#ifdef __PTC_XVSHM__

#ifdef __TINYPTC_INCLUDED
#error You chose more than one target. Please make your mind and try again.
#endif /* __TINYPTC_INCLUDED */

#define __TINYPTC_INCLUDED
#define pragma target xvshm

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int ptc_open(const char *title, int width, int height);
int ptc_update(void *buffer);
void ptc_close(void);
int ptc_process_events(void);

#ifdef __PTC_MMX__
void convert_yv12_mmx(void *pin, void *py, void *pu, void *pv, int stride);
#else
void yuvbuf_init();
void convert_yv12_c(void *pin, unsigned char *py, unsigned char *pu,
                    unsigned char *pv, int stride);
#endif /* __PTC_MMX__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PTC_XVSHM__ */

#endif /* __PTC_XVSHM_H */

#ifdef __PTC_FROM_SOURCE

static Display *ptc_display;
static int ptc_screen, ptc_screen_width, ptc_screen_height, ptc_viewport_width,
    ptc_viewport_height, ptc_depth;
static Window ptc_root_window;
static Visual *ptc_visual;
static char *ptc_buffer = NULL;

static Window ptc_window;
static int ptc_x_position, ptc_y_position;
static XSetWindowAttributes ptc_window_attributes;
static GC ptc_window_gc;

static XShmSegmentInfo ptc_shm_segment;
static int ptc_xv_ok;
static XvImage *ptc_xvimage;
static XvPortID ptc_xv_port;

#endif /* __PTC_FROM_SOURCE */
