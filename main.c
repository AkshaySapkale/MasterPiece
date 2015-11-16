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
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "configuration.h"
#include "split.h"
#include "merge.h"

#include "extra.h"

static const char author[] = "Mr. Akshay Sapkale";

static void displayHelpOptions (const char *executable_name) {

	printf("\n\t College of Engineering, Pune\n\n");
	printf ("\t DSA Project - TransEase 1.0\n\n"
		"\t\t\t by %s\n"
		"\t\t\t MIS - 111408052\n\n", author);

	printf ("\t Usage: %s (Option for what to do) (Filename to perform) (Valid Splitting Size)\n\n\n", executable_name);

	printf ("\t Available options:\n\n"
		"\t\t  -j : join the files beginning with the given name\n"
		"\t\t  -s : split the given file. (default spliting-size is in bytes.) \n\n");

	printf ("\t Examples:\n\n"
		"\t \t%s -s FlashSeason1.iso 15M    (15 MB)\n"
		"\t \t%s -s FlashSeason1.iso 1500   (1500 Bytes by defualt)\n"
		"\t \t%s -j FlashSeason1.iso.001\n\n", executable_name, executable_name, executable_name);
}


int main (int argc, char **argv) {

	char			*filename,
				*usersize;
	int			ret;
	unsigned long int	size;
	size_t			len;


	if (argc < 3) {

		displayHelpOptions(argv[0]);
		exit (1);
	}

	if (!strcmp(argv[1], "-s")) {

		if (argc != 4)	{

			displayHelpOptions(argv[0]);
			exit (1);
		}

		if (argv[3][0] == '-') {
			printf("\n\tTransEase 1.0\n\n");
			printf("\t\tSplit size cannot be a negative number!\n\n");
			exit (1);
		}

		len = strlen(argv[3]);
		usersize = (char *)malloc((len + 1) * sizeof(char));
		strncpy(usersize, argv[3], len);
		
		if ((argv[3][len - 1] == 'M') || (argv[3][len - 1] == 'm')) {

			usersize[len - 1] = '\0';
			size = strtoul(usersize, NULL, 10);
			size *= 1024 * 1024;
		
		} else if ((argv[3][len - 1] == 'K') || (argv[3][len - 1] == 'k')) {

			usersize[len - 1] = '\0';
			size = strtoul(usersize, NULL, 10);
			size *= 1024;

		} else if ((argv[3][len - 1] == 'B' || argv[3][len - 1] == 'b')) {

			usersize[len - 1] = '\0';
			size = strtoul(usersize, NULL, 10);

		}else if (isdigit(argv[3][len - 1])) {

			size = strtoul(usersize, NULL, 10);

		} else {
			printf("\n\tTransEase 1.0\n\n");
			printf("\t\tPlease specify the size correctly!\n\n");
			displayHelpOptions(argv[0]);
			exit (1);
		}

		
		if (size == 0) {
			printf("\n\tTransEase 1.0\n\n");
			printf("\t\tInvalid split size (0) \n\n");
			exit (1);
		}

		if (size > MAX_SPLITSIZE) { /*MAX_SPLITSIZE is defined in configuration.h */
			printf("\n\tTransEase 1.0\n\n");
			printf("\t\tSplit size can be %lu bytes at maximum!\n\n", (uoff_t)MAX_SPLITSIZE);
			exit (1);
		}

		filename = strdup(argv[2]);

		ret = split_file(filename, size);

		exit (ret);
	
	} else if (!strcmp(argv[1], "-j")) {

		if (argc != 3) {
			displayHelpOptions(argv[0]);
			exit (1);
		}

		filename = strdup(argv[2]);
		ret = merge_files(filename);
		exit (ret);
	
	} else{
		printf("\n\tTransEase 1.0\n\n");
		printf("\t\tWhatch Wanna Do ?\n");
		displayHelpOptions(argv[0]);
		exit (1);

	}
	exit (0);
}


