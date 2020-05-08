//
// This file is part of tinyPTC, UA version 2019
// Based on TinyPTC-X11-0.7.3 X Shared Memory Extension target
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

/* #includes */

#include "tinyptc.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XShm.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#ifdef __PTC_XSHM__

#define __PTC_FROM_SOURCE

#include "xshm.h"

/* Open the screen */

int ptc_open(const char *title, int width, int height) {
  /* Open a display on the current root window */
  ptc_display = XOpenDisplay(NULL);
  if (ptc_display == NULL) {
    return PTC_FAILURE;
  }

  /* Get the default screen associated with the previously opened display */
  ptc_screen = DefaultScreen(ptc_display);
  /* Get the default visual */
  ptc_visual = DefaultVisual(ptc_display, ptc_screen);
  /* Get screen bitdepth */
  ptc_depth = DefaultDepth(ptc_display, ptc_screen);
  /* Get a pointer to the supported pixmap formats */
  ptc_pixmap_formats =
      XListPixmapFormats(ptc_display, &ptc_pixmap_format_count);
  /* Check if there's one that's suitable */
  for (ptc_pixmap_counter = 0; ptc_pixmap_counter < ptc_pixmap_format_count;
       ptc_pixmap_counter++) {
    if (ptc_depth == ptc_pixmap_formats[ptc_pixmap_counter].depth) {
      /* Set the right value */
      ptc_converter_depth =
          ptc_pixmap_formats[ptc_pixmap_counter].bits_per_pixel;
    }
  }
  XFree(ptc_pixmap_formats);
#ifdef __PTC_ENABLE_CONVERSIONS__
  /* Check if a converter is avaliable */
  ptc_convert =
      ptc_request_converter(ptc_converter_depth, ptc_visual->red_mask,
                            ptc_visual->green_mask, ptc_visual->blue_mask);
  if (!ptc_convert) {
    /* Close the display */
    XCloseDisplay(ptc_display);
    return 0;
  }
  /* Get the actual bytes-per-pixel value */
  switch (ptc_converter_depth) {
  case 8:
    ptc_output_pitch = 1;
    break;
  case 15:
    ptc_output_pitch = 2;
    break;
  case 16:
    ptc_output_pitch = 2;
    break;
  case 24:
    ptc_output_pitch = 3;
    break;
  case 32:
    ptc_output_pitch = 4;
    break;
  }
  /* Allocate the temporary buffer */
  ptc_buffer = (char *)malloc(width * height * ptc_output_pitch);
  if (ptc_buffer == NULL) {
    XCloseDisplay(ptc_display);
    return PTC_FAILURE;
  }
#else
  /* It runs only on a 32bpp display if no conversions were activated */
  if (ptc_converter_depth != 32) {
    XCloseDisplay(ptc_display);
    return PTC_FAILURE;
  }
#endif /* __PTC_ENABLE_CONVERSIONS__ */
  /* Check for XShm extension */
  if (!XShmQueryExtension(ptc_display)) {
    XCloseDisplay(ptc_display);
    return PTC_FAILURE;
  }
  /* Get screen dimensions */
  ptc_screen_width = DisplayWidth(ptc_display, ptc_screen);
  ptc_screen_height = DisplayHeight(ptc_display, ptc_screen);
  /* Get the default root window */
  ptc_root_window = DefaultRootWindow(ptc_display);
  /* Initialize window's attribute structure */
  ptc_window_attributes.border_pixel = BlackPixel(ptc_display, ptc_screen);
  ptc_window_attributes.background_pixel = BlackPixel(ptc_display, ptc_screen);
  ptc_window_attributes.backing_store = NotUseful;
#ifdef __PTC_CENTER_WINDOW__
  /* Center the window on the screen */
  ptc_x_position = (ptc_screen_width - width) / 2;
  ptc_y_position = (ptc_screen_height - height) / 2;
#else
  /* Dock the window on the top-left corner */
  ptc_x_position = 0;
  ptc_y_position = 0;
#endif /* __PTC_CENTER_WINDOW__ */
  /* Create the window */
  ptc_window = XCreateWindow(
      ptc_display, ptc_root_window, ptc_x_position, ptc_y_position, width,
      height, 0, ptc_depth, InputOutput, ptc_visual,
      CWBackPixel | CWBorderPixel | CWBackingStore, &ptc_window_attributes);
  /* Set the window's name */
  XStoreName(ptc_display, ptc_window, title);
  /* Tell the server to report only keypress-related events */
  XSelectInput(ptc_display, ptc_window, KeyPressMask | KeyReleaseMask);
  /* Initialize window's sizehint definition structure */
  ptc_window_sizehints.flags = PPosition | PMinSize | PMaxSize;
  ptc_window_sizehints.x = 0;
  ptc_window_sizehints.y = 0;
  ptc_window_sizehints.min_width = width;
  ptc_window_sizehints.max_width = width;
  ptc_window_sizehints.min_height = height;
  ptc_window_sizehints.max_height = height;
  /* Set the window's sizehint */
  XSetWMNormalHints(ptc_display, ptc_window, &ptc_window_sizehints);
  /* Clear the window */
  XClearWindow(ptc_display, ptc_window);
  /* Put the window on top of the others */
  XMapRaised(ptc_display, ptc_window);
  /* Clear event queue */
  XFlush(ptc_display);
  /* Get the default graphic context */
  ptc_window_gc = DefaultGC(ptc_display, ptc_screen);
  /* Create an XShmImage */
  ptc_ximage = XShmCreateImage(ptc_display, ptc_visual, ptc_depth, ZPixmap, 0,
                               &ptc_shm_segment, width, height);
  /* Get a shared segment */
  ptc_shm_segment.shmid =
      shmget(IPC_PRIVATE, ptc_ximage->bytes_per_line * ptc_ximage->height,
             IPC_CREAT | 0777);
  /* Initialize XShmImage data buffer pointer */
  ptc_ximage->data = (char *)shmat(ptc_shm_segment.shmid, 0, 0);
  /* Save buffer address */
  ptc_shm_segment.shmaddr = ptc_ximage->data;
  /* Put the segment in read/write */
  ptc_shm_segment.readOnly = False;
  /* Attach the segment to the display */
  if (!XShmAttach(ptc_display, &ptc_shm_segment)) {
    /* Destroy the image */
    XDestroyImage(ptc_ximage);
    /* Detach the buffer from the segment */
    shmdt(ptc_shm_segment.shmaddr);
    /* Remove the segment */
    shmctl(ptc_shm_segment.shmid, IPC_RMID, 0);
    /* Destroy the window */
    XDestroyWindow(ptc_display, ptc_window);
    /* Close the display */
    XCloseDisplay(ptc_display);
    return PTC_FAILURE;
  }
  /* Save windowsize values */
  ptc_viewport_width = width;
  ptc_viewport_height = height;
  return PTC_SUCCESS;
}

/* Update the screen */

int ptc_update(void *buffer) {
  char *ptc_buffer;

  ptc_buffer = (char *)buffer;
  /* Copy buffer data into the XShmImage */
#ifdef __PTC_ENABLE_CONVERSIONS__
  ptc_source_index = 0;
  ptc_destination_index = 0;
  /* Convert the image line by line */
  for (ptc_blitcounter = 0; ptc_blitcounter < ptc_viewport_height;
       ptc_blitcounter++) {
    /* Conversion */
    ptc_convert(ptc_buffer + ptc_source_index,
                (ptc_ximage->data) + ptc_destination_index, ptc_viewport_width);
    /* Pointers update */
    ptc_source_index += ptc_viewport_width * sizeof(int);
    ptc_destination_index += ptc_viewport_width * ptc_output_pitch;
  }
#else
  /* Blit the image */
  memcpy(ptc_ximage->data, buffer,
         ptc_viewport_width * ptc_viewport_height * sizeof(int));
#endif /* __PTC_ENABLE_CONVERSIONS__ */
  /* Synchronize the event queue */
  XSync(ptc_display, 0);
  /* Put the buffer on the window */
  XShmPutImage(ptc_display, ptc_window, ptc_window_gc, ptc_ximage, 0, 0, 0, 0,
               ptc_viewport_width, ptc_viewport_height, False);
  /* Process incoming events */
//  if (ptc_process_events()) {
//#ifdef __PTC_CLEANUP_CALLBACK__
//    ptc_cleanup_callback();
//#endif /* __PTC_CLEANUP_CALLBACK__ */
//    ptc_close();
//    exit(0);
//  }
  return PTC_SUCCESS;
}

/* Process events */

int ptc_process_events(void) {
  XEvent ptc_xevent;
  KeySym ptc_keysym;

  /* Check if there are events waiting in the display's queue */
  if (XPending(ptc_display)) {
    /* Get the next event in queue */
    XNextEvent(ptc_display, &ptc_xevent);
    /* Check if it's a keypress event */
    if (ptc_xevent.type == KeyPress) {
      /* Get the keysym */
      ptc_keysym = XLookupKeysym(&ptc_xevent.xkey, 0);
      /* Check if the key pressed was a function one */
      if ((ptc_keysym >> 8) == __PTC_FUNCTION_KEY__) {
        /* Check if it was the escape key */
        if ((ptc_keysym & 0xFF) == __PTC_ESCAPE_KEY__) {
          return PTC_SUCCESS;
        }
      }
    }
  }
  return PTC_FAILURE;
}

/* Close the screen */

void ptc_close(void) {
  /* Detach the segment from the display */
  XShmDetach(ptc_display, &ptc_shm_segment);
  /* Destroy the XShmImage */
  XDestroyImage(ptc_ximage);
  /* Detach the buffer from the segment */
  shmdt(ptc_shm_segment.shmaddr);
  /* Remove the segment */
  shmctl(ptc_shm_segment.shmid, IPC_RMID, 0);
  /* Close the window */
  XDestroyWindow(ptc_display, ptc_window);
  /* Close the display */
  XCloseDisplay(ptc_display);
  /* Deallocate the buffer */
  if (ptc_buffer) {
    free(ptc_buffer);
  }
}

#endif /* __PTC_XSHM__ */
