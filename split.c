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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>

#include "configuration.h"
#include "function.h"
#include "split.h"
#include "extra.h"

void make_enc(int, char *, uoff_t, uoff_t);
	
	/* This function creates unique file with extension .enc for given input.*/
	/* .enc file is used to check files before merging. */
	/* It's necessary because algorithm deals with names of files & data-verification is also important. */

int split_file (const char *filename, uoff_t passed_split_size) {

	/* This Function is used to Split Two Files of Desired Size */

	/* uoff_t is used because we need widest range integer */


		FILE		*original_fp,
				*spliting_fp;

		int		filenr,
				pieces;

		char		*c_byte,
				*spliting_filename,
				*original_filename,
				*spliting_sfilename;

		
		size_t		readBytes, allow_read,
				len;

		uoff_t		o_index, size_original,
				s_index, size_spliting,
				leftBytes, slicesize,
				lastsize, dummy_so, dummy_sp;

		struct stat	buf;	
		

		o_index = 0;
		s_index = 0;

		size_original = 0;
		size_spliting = 0;

		filenr = 1;
		
		/* Using standard stat structure defined in <sys/stat.h> 
		   This will be useful to get size of Input File. 

	           Alternate way to do this is :-
			
			size_t size;
			fseek(original_fp,0,2);
			size = ftell(fp);   
		 */
		
		if (stat(filename, &buf) == -1)
		{
			perror("cannot stat input file");
			return 1;
		}
		
		/* Checking whether given file is Regular file or not.*/

		if (!S_ISREG(buf.st_mode))
		{
			printf("%s is not a regular file\n", filename);
			return 1;
		}
	
		/* Actually Copying size of Input-File that we have taken into buf to argument "size_original"*/

		size_original = buf.st_size;
		
		if (passed_split_size >= size_original)
		{
			/* .... Don't let proceed further ..... */
			return 1;
		}

		original_fp = fopen(filename, "r");

		/* While dealing with Files, You must check whether fopen() is successful or not.  */
		
		if (original_fp == NULL)
		{
			perror("error opening input file");
			return -1;
		}


		size_spliting = passed_split_size;
		
		leftBytes = size_original;
		
		dummy_sp = passed_split_size;

		dummy_so = size_original; 
		/* We must know how many parts/sections are needed. */

		pieces = size_original / size_spliting;

		/* Extra part/section so that if we can write left-over Binary data.*/

		if ((size_original % size_spliting) > 0)
			pieces++;


		/* Below function "strip_path()" is used so that if in commandline-argument, user enter address of file
		   such "/Home/Desktop/Akshay/Flash2.mp4" then, this function will check it and return exact filename.
		   In this case, It'll return "Flash2.mp4" only. */

		original_filename = strip_path(filename);

		len = strlen(original_filename) + 5;	/* ".001" + null terminator */
		

		spliting_filename = (char *) malloc(len * sizeof(char));

		
		/* READ_BUFSIZE is macro defined in configuration.h */		

		c_byte = (char *) malloc(READ_BUFSIZE * sizeof(char));

		printf("\n\t TransEase 1.0\n");
		printf("\n\t Splitting %s into %d pieces.\n\n", original_filename, pieces);



		while (o_index < size_original)  /* o_index = o_index + readBytes */
		{

			/* o_index maintains positon of bytes of Input-File.*/			
			
			/* Code that will give sequential names to output-files. */			
						
			if (filenr < 10)
				sprintf(spliting_filename, "%s.00%d", original_filename, filenr);
			else if (filenr < 100)
				sprintf(spliting_filename, "%s.0%d", original_filename, filenr);
			else
				sprintf(spliting_filename, "%s.%d", original_filename, filenr);


			spliting_fp = fopen(spliting_filename, "w");


			if (spliting_fp == NULL)
			{
				perror("cannot create output file");
				fclose(original_fp);
				return 1;
			}


			/* This function return shortened-name of input-file.
			   It's used to just display short-names.
			   Suppose, Your Inputfile have name as "abcdefghijklmnopqrstuvwxyz.mp4"
			   Then, while performing operations. it will display output file name as "abcdef...xyz.mp4.coepX001"
			   Original output files will have original name. 
			   This means output file will have name "abcdefghijklmnopqrstuvwxyz.mp4.001"*/

			spliting_sfilename = shorten_path(spliting_filename);

			printf("\t\t %s\t\t\t %lu bytes\n", spliting_sfilename, size_spliting);

			readBytes = 0;

			allow_read = READ_BUFSIZE;
			
			s_index = 0;

			while (s_index < size_spliting)  /* s_index = s_index + readBytes */
			{
						
				/* s_index maintains positon of bytes of file that will be written as splitted file as output.*/				
			
				slicesize = size_spliting - s_index;			/* how much to read */
				
				if (slicesize < (uoff_t)allow_read)
					allow_read = (size_t)slicesize;

				/* This fread() performs integral role of Splitting Function.*/			
			
				readBytes = fread(c_byte, 1, allow_read, original_fp);	/* how much is read */
				

				if (readBytes != allow_read)
				{
					if (feof(original_fp))
						printf("unexpected EOF!...\n");
					perror("error while reading input file");
					fclose(spliting_fp);
				}

				/* This fwrite() performs integral role of Splitting Function.*/			

				len = fwrite(c_byte, 1, readBytes, spliting_fp);   /* how much is being written */

				if (len != readBytes)
				{
					perror("error while writing to output file");
					fclose(spliting_fp);
				}

				o_index = o_index + readBytes;
				s_index = s_index + readBytes;
			}

			leftBytes = leftBytes - size_spliting;

			/* Dealing with situation, when we have less data than splitting size */

			if (leftBytes < size_spliting) {
				size_spliting = leftBytes;
			}
			filenr++;			

			fclose(spliting_fp);

			/*  free() used memory after satisfing need for purpose ! */

			if (spliting_sfilename != spliting_filename)
				free (spliting_sfilename);
		}

		while(1) {
				dummy_so = dummy_so - dummy_sp;
				if(dummy_so < dummy_sp) {
					lastsize = dummy_so;
					break;
				}
			}
		printf("\n\n\t Spliting-Operation Completed ... \n\n");
		printf("\t Creating Data-Identity Module (.dim) File  ..... \n\n");
		make_enc(pieces, original_filename, passed_split_size, lastsize);
		printf("\t File created Successfully : %s.dim\n\n", original_filename);
		printf("\t Status : Success \n\n");
		free(c_byte);		
		fclose(original_fp);

		return 0;


}

void make_enc(int pieces, char *original_filename, uoff_t passed_split_size, uoff_t lastsize) {

	int i, len, filenr, piececount;
	char *spliting_filename, *original, *chunk;
	char a[30];

	strcpy(a,original_filename); /* original filename */

	piececount = pieces; /* no.of files/pieces */

	unsigned long slicesize, lastslicesize;

	slicesize = passed_split_size;
	lastslicesize = lastsize;
 
	chunk = (char *)malloc(10);

	len = strlen(original_filename) + 5; /* .dim + NUL character. */
	
	spliting_filename = (char *) malloc(len * sizeof(char));
	original = (char *) malloc(len * sizeof(char));

	FILE *fp, *enc;
		
		sprintf(original,"%s.dim", original_filename);

		enc = fopen(original,"w");
		fwrite(&piececount,sizeof(int),1,enc); /*no.of pieces*/
		fclose(enc);
		enc = fopen(original,"a");
		fwrite(a,sizeof(a),1,enc); /*file-name*/
		fclose(enc);
		enc = fopen(original,"a");
		fwrite(&slicesize,sizeof(slicesize),1,enc); /* slice-size main */
		fclose(enc);
		enc = fopen(original,"a");
		fwrite(&lastslicesize,sizeof(lastslicesize),1,enc); /*last slice-size*/
		fclose(enc);

	filenr = 1;

	for(i = 0; i < pieces; i++) {
		if (filenr < 10)
			sprintf(spliting_filename, "%s.00%d", original_filename, filenr);
		else if (filenr < 100)
			sprintf(spliting_filename, "%s.0%d", original_filename, filenr);
		else
			sprintf(spliting_filename, "%s.%d", original_filename, filenr);
		filenr++;
		fp = fopen(spliting_filename,"r");
		enc = fopen(original,"a+");
		fread(chunk,10,1,fp);
		fwrite(chunk,10,1,enc);
		fclose(fp);
		fclose(enc);
	}
}





