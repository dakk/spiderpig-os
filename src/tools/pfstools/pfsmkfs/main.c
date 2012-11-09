/*
 * SpiderpigOS
 * Copyright (C) 2009 - 2010 Davide Gessa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * \file pfstools/pfsmkfs/main.c
 * \author Davide Gessa
 * \date 11-23-2009
 */
//#include <fs/pfs/pfs.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include "main.h"

/**
 * Formatta una partizione con filesystem pfs
 */
int main(int argc, char **argv)
{
	if(argc < 2)
	{
		usage();
		return 0;
	}
	
	FILE *dev;
	struct stat stat_s;
	char label[32];
	int i = 0;
	int dev_arg = 1;
	
	/*while(i < argc)
	{
		if(strcmp(argv[i], "-V") == 0)
		{
			i++;
			strcpy(label, argv[i]);
		}
		i++;
	}*/
	
	//dev_arg = i - 1;
	stat(argv[dev_arg], &stat_s);
	
	if(stat_s.st_ino == 0)
	{
		printf("mkfs.pfs: cannot stat device %s\n", argv[dev_arg]);
		return 0;
	}
	
	return 0;
}


/**
 * Messaggio di help
 */
void usage()
{
	printf("Usage: mkfs.pfs [-V volume-name] device\n");	
}
