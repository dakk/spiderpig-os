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
 * \file lib/libc/dirent.c
 * \author Davide Gessa
 * \note Standard input output
 * \date 10-12-09
 */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <dirent.h>

DIR *opendir(const char *path)
{
	FILE *f = fopen(path, "r");
	
	if(f == NULL)
		return NULL;
	
	return fdopendir((int) f);	
}



DIR *fdopendir(int fd)
{
	return NULL;
}


int closedir(DIR *fd)
{
	return 0;
}


int readdir(unsigned int fd, struct dirent *d, unsigned int off)
{
	return 0;
}
