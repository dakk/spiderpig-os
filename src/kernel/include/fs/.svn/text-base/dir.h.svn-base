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
 * \file fs/dir.h
 * \author Davide Gessa
 * \date 24-01-10
 */
#ifndef FS_DIR_H
#define FS_DIR_H

#include <types.h>
#include <fs/fs.h>
#include <driver.h>

/**
 * Struttura di un file aperto
 */
typedef struct dir_p
{
	file_t *f;				///< Puntatore al file
	char *d_name;			///< Nome directory
	uint32_t cur_i;			///< Puntatore all'elemento corrente
	
	////////// Provvisorio
	char path[512];			///< Path della directory (provvisorio)
} dir_t; 


uint32_t fs_readdir2(char *, uint32_t , struct dirent *);
dir_t *fs_opendir(char *);
uint32_t fs_closedir(dir_t *);
uint32_t fs_rewinddir(dir_t *);
uint32_t fs_readdir(dir_t *, struct dirent *);

uint32_t fs_makedir(char *);

#endif
