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
 * \file fs/file.h
 * \author Davide Gessa
 * \date 24-01-10
 */
#ifndef FS_FILE_H
#define FS_FILE_H

#include <types.h>
#include <fs/fs.h>
#include <driver.h>


#define FS_SEEK_SET	0			///< Seek dall'inizio
#define FS_SEEK_CUR	1			///< Seek dalla posizione corrente
#define FS_SEEK_END	2			///< Seek dalla fine


/**
 * Struttura di un file aperto
 */
typedef struct file_p
{
	uint32_t id;				///< Id del file aperto
	uint64_t seek_p;			///< Posizione del puntatore
	uint64_t size;				///< Dimensione del file
	
	inode_t *node;				///< Nodo
	void *drv;					///< Driver
	
	struct file_p *next;		///< Prossimo file
} file_t; 



uint32_t files_open_n;			///< Numero corrente dei file aperti
file_t *file_list;				///< Lista file aperti



file_t *fs_open(char *, char *);
uint32_t fs_close(file_t *);
uint32_t fs_read(file_t *, char *, uint32_t);
uint32_t fs_write(file_t *, char *, uint32_t);
uint32_t fs_seek(file_t *, uint8_t, uint64_t);

uint32_t fs_link(char *, char *);
uint32_t fs_unlink(char *);


#endif
