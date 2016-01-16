/*
 * xdgatool - get and set XDGA screen modes
 * Copyright (C) 2016  Christian Garbs <mitch@cgarbs.de>
 * licensed under GNU GPL v3 (or later)
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xxf86dga.h>

/* get X connection */
Display*
getXConnection(void)
{
	Display *dpy;
	if (!(dpy = XOpenDisplay(0)))
	{
		fprintf(stderr, "can't open X display\n");
		exit(1);
	}
	return dpy;
}

/* print available modes */
void
printDGAModes(void)
{
	Display *dpy = getXConnection();

	int modes;
	XDGAMode *dgamodes = XDGAQueryModes(dpy, 0, &modes);
	if (dgamodes)
	{
		XDGAMode *mode = dgamodes;
		for (int i = 0; i < modes; i++, mode++)
		{
			printf("mode %2d size (%5d,%5d) depth %2d bpp %2d viewport (%5d,%5d) name (%s)\n",
			       mode->num,
			       mode->imageWidth,
			       mode->imageHeight,
			       mode->depth,
			       mode->bitsPerPixel,
			       mode->viewportWidth,
			       mode->viewportHeight,
			       mode->name
				);
			       
		}
	}
	XFree(dgamodes);
}

/* set a mode */
void
setDGAMode(int mode)
{
	Display *dpy = getXConnection();

	XDGADevice *device = XDGASetMode(dpy, 0, mode);
	XFree(device);
}

/* print help text and exit */
void
showHelp(void)
{
	printf("usage:\n"
	       "  xdgatool              - list all available XDGA modes\n"
	       "  xdgatool <modenum>    - activate XDGA mode <modenum>\n"
		);
	exit(2);
}

/* main program */
int
main(int argc, char**argv)
{
	if (argc > 2)
	{
		showHelp();
	}
	else if (argc == 2)
	{
		char *endptr;
		intmax_t modenum = strtoimax(argv[1], &endptr, 10);
		if (*argv[1] != '\0' && *endptr == '\0' && modenum >= 0)
		{
			setDGAMode(modenum);
		}
		else
		{
			showHelp();
		}
	}
	else
	{
		printDGAModes();
	}

	return 0;
}
