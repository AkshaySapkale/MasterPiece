/*****************************************************************************
 * Copyright (C) Akshay R. Sapkale arsapkale7@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
#include <sys/types.h>
#include <stdio.h>

#include <sys/stat.h>
#include <limits.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "configuration.h"
#include "function.h"

#include "extra.h"

/* Below function "strip_path()" is used so that if in commandline-argument, user enter address of file
   such "/Home/Desktop/Akshay/Flash2.mp4" then, this function will check it and return exact filename.
   In this case, It'll return "Flash2.mp4" only. */


char *strip_path (const char *cfilename) {

	size_t			lpos,
				i, n, len;
	char			*filename;


	lpos = 0;
	len = strlen(cfilename);
	for (i = 0; i < len; i++)
		if (cfilename[i] == '/')
			lpos = i;

	if (lpos != 0)
		lpos++;

	n = 0;

	filename = (char *)malloc((len + 2) * sizeof(char));

	for (i = lpos; i < len; i++){
		filename[n] = cfilename[i];
		n++;
	}

	filename[n] = '\0';

	return filename;
}

/* This function return shortened-name of input-file.
   It's used to just display short-names.
   Original output files will have original name. */

char *shorten_path (const char *cfilename) {

	char		*filename;
	size_t		i, n, len;

	len = strlen(cfilename);
	if (len < 30)
		return (char *)cfilename;

	filename = (char *)malloc((30 + 1) * sizeof(char));

	n = 0;

	for (i = 0; i < 10; i++){
		filename[n] = cfilename[i];
		n++;
	}

	for (i = 0; i < 3; i++) {
		filename[n] = '.';
		n++;
	}

	for (i = len - 17; i < len; i++) {
		filename[n] = cfilename[i];
		n++;
	}

	filename[30] = '\0';

	return filename;
}

