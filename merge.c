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
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "configuration.h"
#include "function.h"
#include "merge.h"

int globalflag = 0;

void advanced_search(char *);

	/* Take global-flag for advanced_search() */

	/* This function is used for merging already spliited-file, provided it satisfies all condition required. */

int merge_files (const char *filename) {


	FILE			*fp_split,
				*fp_merged,
				*fp_dim;

	size_t			len, bytes_read;
	
	uoff_t			merged_size,
				spliting_size,
				s_index;

	int			filenr,
				numofFiles,
				startnr,
				piececount;

	int 			j;

	char			*merged_filename,
				*spliting_filename,
				*original_filename,
				*missing_filename,
				*c_bytes,
				*spliting_sfilename;

	char 			ch1,
				ch2,
				checkname[30],
				response;

	char 			*dimfilename;

	struct stat		buf;

	unsigned long mainslicesize, lastslicesize;


	len = strlen(filename);
	if (len < 5 || filename[len - 4] != '.') {

		printf("\tProvided Filename is Invalid.\n"
			"\tFilename must end with extension .001\n\n");
		return 1;
	}

	/* startnr is integer-type which is essential for dealing with names of files that we are going to access or modify. */

	switch (filename[len - 1]) {

	case '1':
		startnr = 1;
		break;
	default:
		printf("\tProvided Filename is Invalid.\n"
			"\tFilename must end with extension .001\n\n");
		return 1;
	}

	original_filename = (char *)malloc((len - 4 + 1) * sizeof(char)); /* lenght - 4(for extension like .001) + Null Character */
	spliting_filename = (char *)malloc((len + 1) * sizeof(char));	  /* lenght + Null Character*/

	strncpy(original_filename, filename, len - 4);
	original_filename[len - 4] = '\0';

	/* Below function "strip_path()" is used so that if in commandline-argument, user enter address of file
	   such "/Home/Desktop/Akshay/Flash2.mp4" then, this function will check it and return exact filename.
	   In this case, It'll return "Flash2.mp4" only. */

	merged_filename = strip_path(original_filename);

	numofFiles = 0;
	merged_size = 0;

	/* missing_filename = NULL indicates that are all files which we need are present in current directory. */

	missing_filename = NULL;

	/* Below Code(loop) will check existance of Files present in current directory. It will check sequential-naming accordingly. */

	for (filenr = startnr; filenr < 1000; filenr++) {

		if (filenr < 10) {
			sprintf(spliting_filename, "%s.00%d", original_filename, filenr);
		}
		else if(filenr < 100) {
			sprintf(spliting_filename, "%s.0%d", original_filename, filenr);
		}
		else {
			sprintf(spliting_filename, "%s.%d", original_filename, filenr);
		}
		
		
		if (stat(spliting_filename, &buf) == -1) {

				if (filenr == startnr) {
					printf("\n\tTransEase 1.0\n");
					printf("\n\t\tCouldn't find `%s'\n", spliting_filename);
					if(globalflag == 0) 
						{
						printf("\n\t\t Would You Like to Do Advanced-Search ?\n");
						printf("\t\t Note: Advanced-Search will scan your current directory for missing-files \n");
						printf("\t\t       and Restore Files in original-state if present.\n");
						printf("\t\t Enter Y/N :");
						response = getchar();
						printf("\n");
							if(response == 'Y' || response == 'y') {
								printf("\n\t\tCurrent Directory is being Analysed ...\n");
								printf("\t\t(Note.- Processing all & Displaying only suspicious files.)\n\n");
								advanced_search(original_filename);
							} else {
								printf("\n");
								printf("\t\tOperation aborted Successfully. \n\n");
							}								
						}
					//return 1;
				}else {
					if (missing_filename == NULL)
						missing_filename = strdup(spliting_filename);
				}
			} else {
				
				if (!S_ISREG(buf.st_mode)) {
					printf("\n\tTransEase 1.0\n");
					printf("\n\t\tCouldn't find `%s'\n", spliting_filename);
					if(globalflag == 0) 
						{
						printf("\n\t\t Would You Like to Do Advanced-Search ?\n");
						printf("\t\t Note: Advanced-Search will scan your current directory for missing-files \n");
						printf("\t\t       and Restore Files in original-state if present.\n");
						printf("\t\t Enter Y/N :");
						response = getchar();
						printf("\n");
							if(response == 'Y' || response == 'y') {
								printf("\n\t\tCurrent Directory is being Analysed ...\n");
								printf("\t\t(Note.- Processing all & Displaying only suspicious files.)\n\n");
								advanced_search(original_filename);
							} else {
								printf("\n");
								printf("\t\tOperation aborted Successfully. \n\n");
							}								
						}
					//return 1;
				} else {
					
					if (missing_filename != NULL) {
					printf("\n\tTransEase 1.0\n");
						printf("\n\t\tMissing file `%s' !\n", missing_filename);
						if(globalflag == 0) 
						{
						printf("\n\t\t Would You Like to Do Advanced-Search ?\n");
						printf("\t\t Note: Advanced-Search will scan your current directory for missing-files \n");
						printf("\t\t       and Restore Files in original-state if present.\n");
						printf("\t\t Enter Y/N :");
						response = getchar();
						printf("\n");
							if(response == 'Y' || response == 'y') {
								printf("\n\t\tCurrent Directory is being Analysed ...\n");
								printf("\t\t(Note.- Processing all & Displaying only suspicious files.)\n\n");

								advanced_search(original_filename);
							} else {
								printf("\n");
								printf("\t\tOperation aborted Successfully. \n\n");
							}								
						}
						else 
						{
						printf("\n");
						printf("\t\t You are done with Advanced-Search. Files are still missing.\n\n");
						printf("\t\t Operation aborted Successfully. \n\n");
						return 1;
						}
					}
					merged_size = merged_size + buf.st_size;
					numofFiles++;
				}
			}
	}

	/* If all files are ready for Merging, then following code executes. */	

	printf("\n\tTransEase 1.0\n");
	printf("\n\tCreating merged file: %s\n\n",merged_filename);
	printf("\t\tComplete size:  %lu Bytes\n",(unsigned long)merged_size);
	printf("\t\tNumber of Files to be Merged (expected a/c files present in current directory): %d\n\n",numofFiles);

	if (stat(merged_filename, &buf) == 0) {

		printf("\n\tFile having same name of Output-File is already present : %s\n", merged_filename);
		printf("\tOperation Aborted Successfully. \n\n");
		return 1;
	}

	fp_merged = fopen(merged_filename, "w");

	if (fp_merged == NULL) {

		perror("cannot create output file");
		return 1;
	}

/**/	//sprintf(dim_filename,"%s.dim",original_filename);
	
	dimfilename = (char *)malloc(strlen(original_filename) + 1 + 4);

	sprintf(dimfilename,"%s.dim",original_filename);

/**/	fp_dim = fopen(dimfilename,"r");

	if(fp_dim == NULL) {
		perror("Unable to Locate .dim file");
		return 1;
	}

	fread(&piececount,sizeof(int),1,fp_dim);
	fread(checkname,sizeof(checkname),1,fp_dim);
	fread(&mainslicesize,sizeof(unsigned long),1,fp_dim);
	fread(&lastslicesize,sizeof(unsigned long),1,fp_dim);

	if(piececount == numofFiles && strcmp(checkname,original_filename) == 0)
		printf("\t\tSplitted-files count has been confirmed from Data-Identity-Module.\n\n");
	else {
		printf("\t\tAs per Data-Identity-Module, splitted-file's count doesn't match.\n");
		printf("\t\tCouldn't Proceed further.\n");
		printf("\t\tOperation Aborted Successfully.\n\n");
		return 1;	
		fclose(fp_dim);
		fclose(fp_merged);
	}
	fclose(fp_dim);

	c_bytes = (char *)malloc(READ_BUFSIZE * sizeof(char));

	for (filenr = startnr; filenr <= numofFiles + (startnr - 1); filenr++) {
		
		if (filenr < 10) {
			sprintf(spliting_filename, "%s.00%d", original_filename, filenr);
		} else if (filenr < 100) {
			sprintf(spliting_filename, "%s.0%d", original_filename, filenr);
		} else if (filenr < 1000){
			sprintf(spliting_filename, "%s.%d", original_filename, filenr);
		}
		
		spliting_sfilename = shorten_path(spliting_filename);
		
		printf("\t\tReading data from file for Merging :  %s", spliting_sfilename);

		if (stat(spliting_filename, &buf) == -1) {

			perror("Failed to stat this file");
			fclose(fp_merged);
			return 1;
		}

		spliting_size = buf.st_size;
		
		fp_split = fopen(spliting_filename, "r");
		fp_dim = fopen(dimfilename,"r");

		fseek(fp_dim, sizeof(int) + sizeof(checkname) + sizeof(unsigned long) + sizeof(unsigned long) + ((filenr - 1) * 10),SEEK_SET);

		j = 0;
		while(j < 10) {
			ch1 = fgetc(fp_split);
			ch2 = fgetc(fp_dim);
			if(ch1 != ch2) {
				printf("   Status: Match Not Found\n");
				printf("\n\t\tOperation Successfully Aborted\n\n.");
				return 0;
			}
			j++;
			if(j == 10) {
				printf("   Status: Match Found\n");
			}
		}
		
		fclose(fp_split);
		fclose(fp_dim);

		fp_split = fopen(spliting_filename, "r");

		/* Data-verification must be done here. */
		
		if (fp_split == NULL) {

			perror("Unable to Open Corresponding Input-File");
			fclose(fp_merged);
			return 1;
		}

		s_index = 0;

		while (s_index < spliting_size) { /* s_index = s_index + bytes_read */

			/* s_index maintains positon of bytes of Onput-File.*/	

			bytes_read = fread(c_bytes, 1, READ_BUFSIZE, fp_split);

			if (bytes_read != READ_BUFSIZE && !feof(fp_split)) {

				perror("Error encountered while reading Input-File");
				fclose(fp_split);
			}

			len = fwrite(c_bytes, 1, bytes_read, fp_merged);

			if (len != bytes_read) {

				perror("Error encountered while writing to Output-File");
				fclose(fp_split);
			}

			s_index = s_index + bytes_read;
		}

		fclose(fp_split);
		
		if (spliting_sfilename != spliting_filename)
			free (spliting_sfilename);
	
	}
	printf("\n\t\tAll files are Successfully merged in File : %s\n\n",merged_filename);
	fclose(fp_merged);
	return 0;
}

void advanced_search(char *original_filename) {
	globalflag = 1;
	system("ls -l | awk '{print $9}'>master.txt");
	FILE *fp, *enc, *target;
	fp = fopen("master.txt","r");
	struct stat file;

	char *king;
	char a[30];
	
	char *oriname, *dimname;

	char ch1, ch2;

	int j, noofpieces, i, foundcounter;

	oriname = (char *)malloc(strlen(original_filename) + 1 + 4);
	dimname = (char *)malloc(strlen(original_filename) + 1 + 4);

	sprintf(dimname,"%s.dim",original_filename);

	unsigned long mainsize, lastwalisize;	

	enc = fopen(dimname,"r");
	if(enc == NULL) {
		perror("\t\t.dim file must be present for Advanced-Searching ");
		printf("\n\t\t Aborting Operation Successfully.\n\n");
		exit(0); /*Fault :p*/
	}
	fread(&noofpieces,sizeof(int),1,enc);
	fseek(enc,30,SEEK_CUR);
	fread(&mainsize,sizeof(unsigned long),1,enc);
	//printf("\n--%lu--\n",mainsize);
	fread(&lastwalisize,sizeof(unsigned long),1,enc);
	//printf("\n--%lu--\n",lastwalisize);
	fclose(enc);
	fgets(a,sizeof(a),fp);

	foundcounter = 0;

	while(fgets(a,sizeof(a),fp)) {

		a[strlen(a)-1] = '\0';

		king = (char *)malloc(strlen(a) + 1);
		strcpy(king,a);

		if (stat(king, &file) == -1)	{
				perror("cannot stat input file");
				continue;
		}
		if (!S_ISREG(file.st_mode)) {
				printf("\t\t%s is not a regular file\n",king);
				continue;
		}		
		
		if(mainsize == (unsigned long)(file.st_size) || lastwalisize ==(unsigned long)(file.st_size) ) {

			printf("\t\tAnalysing File : %s\n",a);
			//printf("%d\n\n",noofpieces);
		
			i = 0;
			xyz:while(i < noofpieces) {

				enc = fopen(dimname,"r");

				fseek(enc, sizeof(int) + sizeof(a) + sizeof(unsigned long) + sizeof(unsigned long) + (i) * 10 ,SEEK_SET);

				target = fopen(king,"r");
			
				j = 0;
				while(j < 10) {
					ch1 = fgetc(enc);
					ch2 = fgetc(target);
					if(ch1 != ch2) {
						//printf("Analysis Done. Not Found. Taking Next-File.\n");
						fclose(enc);
						fclose(target);
						i++;
						goto xyz;
					}
					j++;
					if(j == 10) {
			
						if (i < 10) {
							sprintf(oriname,"%s.00%d",original_filename,i + 1);
						} else if (i < 100) {
							sprintf(oriname,"%s.0%d",original_filename,i + 1);
						} else if (i < 1000){
							sprintf(oriname,"%s.%d",original_filename,i + 1);
						}
						printf("\t\t\tYou should rename file %s as '%s' \n\n",a,oriname);
						foundcounter++;
						i++;
					}
				}
				fclose(enc);
			}
		}
	}
	if(foundcounter == noofpieces) {
		printf("\n\t ---------------------------------------------------------------- \n");
		printf("\n\t\t(-- Note: You may ignore files those don't need renaming. --)\n\n");
		printf("\n\t\t\t--- All File are Present For further Operation. --- \n\n");
		printf("\t\t--- Follow Above Instructions. ---\n");
		printf("\t\t--- Aborting Operation Successfully. ---\n\n");
		printf("\n\t ---------------------------------------------------------------- \n\n");
		exit(0);
	} else {
		printf("\n\t ---------------------------------------------------------------- \n");
		printf("\n\t\tSome-Files are absent For further Operation.\n");
		printf("\t\tSorry sir, You need all files for Merging-Operation.\n");
		printf("\t\tAborting Operation Successfully.\n\n");
		printf("\n\t ---------------------------------------------------------------- \n\n");
		exit(0);
	}
}


