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
 * \file driver.h
 * \author Davide Gessa
 * \date 10-12-09
 */
#ifndef DRIVER_H
#define DRIVER_H

#include <types.h>
#include <config.h>
#include <device.h>
#include <fs/fs.h>

#define MDRV_OK		0x1
#define MDRV_ER		0x2
#define MDRV_WR		0x3
#define MDRV_IN		0x4

#define DRV_NF_ER	1
#define DRV_AL_LD	2
#define DRV_NF_IN	3
#define DRV_NF_FR	4
#define DRV_NT_IN	5
#define DRV_OK		0
#define DRV_ER		10

#define DRV_TYPE_SYSTEM	1
#define DRV_TYPE_BLOCK	2
#define DRV_TYPE_CHAR	3
#define DRV_TYPE_CRYPTO	4
#define DRV_TYPE_FS		5
#define DRV_TYPE_NET	6
#define DRV_TYPE_VIDEO	7



/**
 * Driver fs
 */
typedef struct 
{
	// Superblock
	uint32_t (*mount)(char *, uint32_t, inode_t *);				///< Callback di mount
	uint32_t (*umount)(inode_t *);								///< Callback di umount	
	
	// Directory
	uint32_t (*mkdir)(inode_t *, char *);						///< Crea directory
	uint32_t (*readdir)(inode_t *, uint32_t, struct dirent *);	///< Legge il contenuto di una directory
	
	// Nodi
	uint32_t (*get_node)(inode_t *, uint32_t, inode_t **);		///< Ottiene un nodo dato padre e inoden
	uint32_t (*delete_node)(inode_t *, char *);		///< Elimina un nodo dato padre e nome
	uint32_t (*create_node)(inode_t *, char *, uint32_t);		///< Crea un nodo dato padre, nome e tipo
	
	// Stat
	uint32_t (*write_stat)(inode_t *, struct stat *, uint32_t);	///< Scrive le stat ad un file
	uint32_t (*read_stat)(inode_t *, struct stat *);			///< Legge le stat da un file
	
	// File
	uint32_t (*open)(inode_t *, char *);						///< Apre un file
	uint32_t (*close)(inode_t *);								///< Chiude un file
	uint32_t (*read)(inode_t *, char *, uint32_t, uint64_t);	///< Legge da un file
	uint32_t (*write)(inode_t *, char *, uint32_t, uint64_t);	///< Scrive su un file
	
	// Link
	uint32_t (*link)(inode_t *, char *, inode_t *, char *);		///< Crea un link
	uint32_t (*unlink)(inode_t *, char *);						///< Elimina un link
	
	uint8_t ifdev;		///< Il filesystem necessita di un device?
} driver_fs_t;



/**
 * Driver video
 */
typedef struct 
{
	char *buffer;												///< Ram buffer
	void (*put_pixel)(uint32_t, uint32_t, uint32_t);			///< Disegna un pixel
	uint32_t (*get_pixel)(uint32_t, uint32_t);					///< Preleva un pixel
	uint32_t (*set_mode)(uint32_t, uint32_t, uint32_t);	///< Imposta la risoluzione
} driver_video_t;


/**
 * Struttura di un driver generico
 */
typedef struct driver_p
{
	char name[32];								///< Nome del driver
	char desc[128];								///< Descrizione del driver
	char author[128];							///< Autore del driver
	
	uint8_t type;								///< Tipo di driver


	// Tipi di driver
	driver_fs_t fs;								///< Driver FS
	driver_video_t video;						///< Driver Video
	
	
	// Comune a tutti i driver
	uint8_t loaded;								///< Indica se e' stato caricato
	uint32_t (*init)();							///< Inizializza il driver
	uint32_t (*free)();							///< Libera il driver
	uint32_t (*probe)(device_t *);				///< Controlla se adatto
	uint32_t (*read)(device_t *, char *, uint32_t, uint64_t);	///< Legge da un dev
	uint32_t (*write)(device_t *, char *, uint32_t, uint64_t);	///< Scrive su un dev
	uint32_t (*ioctl)(device_t *, uint32_t, uint32_t, uint32_t);
	
	struct driver_p *next;						///< Puntatore al driver successivo
} driver_t;


driver_t *driver_list;							///< Lista dei driver



void driver_init();
uint32_t driver_add(driver_t *);
uint32_t driver_del(char *);
uint32_t driver_iget(uint32_t, driver_t **);
driver_t *driver_get(char *);
uint8_t driver_freed(char *);
uint8_t driver_initd(char *);
uint32_t driver_ioctl(char *, device_t *, uint32_t, uint32_t, uint32_t);
void driver_puts(driver_t *, uint32_t, char *);

#endif
