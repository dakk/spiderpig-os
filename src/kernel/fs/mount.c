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
 * \file fs/mount.c
 * \author Davide Gessa
 * \date 12-22-09
 */
#include <fs/fs.h>
#include <fs/mount.h>
#include <device.h>
#include <debug.h>


/**
 * Restituisce il mountpoint di un path
 * 
 * \param path il path del file
 * \param mp buffer per memorizzare il mountpoint
 * \return byte scritti
 * 
 * \note bisogna spezzettare il path!
 */
uint32_t fs_get_mount_point(char *path, char *mpstr)
{
	unsigned i;
	unsigned t = 0;
	
	for(i = 0; i < MP_MAX; i++)
	{
		if((strncmp(fs_mountpoints[i].path, path, strlen(fs_mountpoints[i].path)) == 0) && /*(strlen(mpstr) < fs_mountpoints[i].path) &&*/ (fs_mountpoints[i].used == 1))
		{
			strcpy(mpstr, fs_mountpoints[i].path);
			t = strlen(mpstr);
		}
	}	
	return t;
}



/**
 * Restituisce il filesystem dato il mountpoint
 */
uint32_t fs_get_mount_point_fs(char *path, char *mpstr)
{
	unsigned i;
	
	for(i = 0; i < MP_MAX; i++)
	{
		if(strcmp(fs_mountpoints[i].path, path) == 0)
		{
			strcpy(mpstr, fs_mountpoints[i].fs);
			return strlen(fs_mountpoints[i].fs);
		}
	}	
	
	return 0;
}


/**
 * Restituisce il mp numero x
 * 
 * \return stato operazione
 */
uint32_t fs_iget_mount_point(uint32_t x, mount_point_t **fs)
{
	*fs = NULL;
	
	if((x < MP_MAX) && (fs_mountpoints[x].root != NULL))
	{
		*fs = &fs_mountpoints[x];
		return 0;
	}

	return 1;	
}


/**
 * 
 */
mount_point_t *fs_get_mount_point_struct(char *path)
{
	uint32_t i;
	char mpname[128];
	
	fs_get_mount_point(path, mpname);
	
	for(i = 0; i < MP_MAX; i++)
	{
		if(strcmp(fs_mountpoints[i].path, mpname) == 0)
			return &fs_mountpoints[i];
	}
}


/**
 * Mount di un device
 * 
 * \param device path del device
 * \param path cartella in cui mountare il device
 * \param fs filesystem
 * \return stato dell'operazione
 * 
 * \note sostituire la seconda condizione del ifdev con un get_node
 */
uint32_t fs_mount(char *device, char *path, char *fs, uint32_t flags)
{
	DEBUGP("fs_mount()\n");
	
	driver_t *cf = driver_list;
	inode_t *node;
	
	// Controlla se e' gia' montato qualcosa in quel path
	unsigned i;
	
	for(i = 0; i < MP_MAX; i++)
	{
		if((strcmp(path, fs_mountpoints[i].path) == 0))// && (strlen(path) > 2) && (strlen(mp->path) > 2))
			return MOUNT_STATE_PM;
			
		//if(strcmp(device, mp->dev) == 0)
		//	return MOUNT_STATE_DM;
	}
	
	
	// Troviamo il fs
	while(cf != NULL)
	{
		if((strcmp(fs, cf->name) == 0) && (cf->type = DRV_TYPE_FS))
			break;
		cf = cf->next;
	}
	
	if(cf != NULL)
	{
		// Controlla se e' valido il device (nel caso serva)
		if((cf->fs).ifdev == 1 && (device[0] == '\0' || device[0] == '-'))
			return MOUNT_STATE_MD;

		// Prendiamo il nodo e verifichiamo se e' corretto
		fs_get_node(path, &node);
		if(node == NULL)
			return MOUNT_STATE_MP;
			
		// Richiamiamo la funzione di mount del fs	
		if((cf->fs).mount(0, 0, node) != MOUNT_STATE_OK)
			return MOUNT_STATE_FE;

		// Allochiamo il mp
		mount_point_t *mp = NULL;
		
		for(i = 0; i < MP_MAX; i++)
		{
			if(fs_mountpoints[i].used == 0)
			{
				mp = &fs_mountpoints[i];
				break;
			}
		}
		
		if(mp == NULL)
			return MOUNT_STATE_FE;

		mp->used = 1;
		mp->root = node;
		strcpy(mp->path, path);
		strcat(mp->path, "\0");
				
		strcpy(mp->dev, device);
		strcat(mp->dev, "\0");
		
		strcpy(mp->fs, fs);
		strcat(mp->fs, "\0");
		return MOUNT_STATE_OK;
	}
		
	return MOUNT_STATE_MF;
}



/**
 * Umount di un device
 * 
 * \param path path del device, o mountpoint
 * \return stato dell'operazione
 * 
 * \note da correggere: il clean svuota l'intero albero
 */
uint32_t fs_umount(char *path)
{
	DEBUGP("fs_umount()\n");
	
	/*
	driver_t *cf = driver_list;	
	mount_point_t *mp = fs_mountpoints;
	mount_point_t *prev = NULL;
	
	while(mp != NULL)
	{
		if(strcmp(mp->path, path) == 0 || strcmp(mp->dev, path) == 0)
		{
			// Toglie il mountpoint dalla lista
			if(prev == NULL)
				fs_mountpoints = mp->next;
			else
				prev->next = mp->next;
			
				
			// Elimina i nodi allocati per il filesystem montato
			//fs_tree_cleanup(mp->root->childs, 0);
			
			// Trova il filesystem tra i driver
			while(cf != NULL)
			{
				if((strcmp(mp->fs, cf->name) == 0) && (cf->type = DRV_TYPE_FS))
					break;
				cf = cf->next;
			}
			
			if(cf != NULL)
				if((cf->fs).umount(mp->root) != MOUNT_STATE_OK)
					return MOUNT_STATE_FE;
			else
				return MOUNT_STATE_MF;
				
			// Dealloca il mount point
			free(mp);
			
			return MOUNT_STATE_OK;
		}
		
		prev = mp;
		mp = mp->next;
	}*/
	
	return MOUNT_STATE_MP;
}

