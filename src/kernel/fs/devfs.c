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
 * \file kernel/fs/devfs/devfs.c
 * \author Davide Gessa
 * \date 12/08/2009
 */
#include <driver.h>
#include <types.h>
#include <fs/fs.h>
#include <fs/devfs.h>
#include <debug.h>
#include <config.h>

driver_t driver_devfs =
{
	.name = "devfs\0",
	.type = DRV_TYPE_FS,
	
	.fs.ifdev = 0,
	.fs.mount = devfs_mount,
	.fs.umount = devfs_umount,
	.fs.readdir = devfs_readdir,
	.fs.open = devfs_open,
	.fs.read = devfs_read,
	.fs.write = devfs_write,
	.fs.close = devfs_close,
	
	.fs.get_node = devfs_get_node,
	.fs.delete_node = NULL,
	.fs.create_node = NULL,
	
	.fs.write_stat = NULL,
	.fs.read_stat = NULL
};




/**
 * Legge il contenuto della dir
 */
uint32_t devfs_readdir(inode_t *root, uint32_t n, struct dirent *d)
{
	inode_t *childs = devfs_root->childs;
	unsigned i = 0;
	
	while(childs != NULL && i <= n)
	{
		if(i == n)
		{
			strcpy(d->name, childs->name);
			d->inode = childs->inode_n;
			return 1;
		}
		i++;
		childs = childs->next;
	}
	return 0;
}


/**
 * Umonta il devfs
 */
uint32_t devfs_umount(inode_t *root)
{
	//root->childs = NULL;
	//devfs_root = NULL;
	//devfs_childs = NULL;
	return MOUNT_STATE_OK;
}



/**
 * Monta il devfs
 */
uint32_t devfs_mount(char *dev, uint32_t flags, inode_t *root)
{
	root->childs = devfs_childs;
	//devfs_root = root;
	//devfs_childs = NULL;
	return MOUNT_STATE_OK;
}



/**
 * Registra un device nel devfs
 * 
 * \param dev device
 * \param drv driver
 * \param name nome file
 * \return numero nodo
 */
uint32_t devfs_reg_device(device_t *dev, driver_t *drv, char *name)
{
	DEBUGP("devfs_reg_device()\n");
	
	if(name == NULL)
		return 0;
		
	
	// Crea il nodo
	inode_t *devv = fs_create_node(name, devfs_root, NODE_TYPE_FILE, 0);
	//printf("%s\n", devv->name);
	
	
	(devv->fs_node) = (void *) malloc(sizeof(devfs_node_t));
	((devfs_node_t *) (devv->fs_node))->driver = drv;
	((devfs_node_t *) (devv->fs_node))->device = dev;
			
	return 0;
}


/**
 * Sregistra un device
 */
uint32_t devfs_unreg_device(char *name)
{
	DEBUGP("devfs_unreg_device()\n");
	
	inode_t *node = devfs_root->childs;
	inode_t *prev = NULL;
	
	while(prev != NULL)
	{
		if(strcmp(node->name, name) == 0)
		{
			if(prev == NULL)
				devfs_root->childs = node->next;
			else
				prev->next = node->next;
			
			free(node);
			return 0;
		}
		prev = node;
		node = node->next;
	}
	
}


/**
 * Trova un nome libero per un dev
 */
uint32_t devfs_find_freen(char *name, char *res)
{
	inode_t *next;
	
	if(strcmp(name, "\0") != 0)
	{
		char a[32];
		char b[8];
		int i = 0;
		int over = 1;
		strcpy(res, "\0");
		
		while(over)
		{
			tent:
			next = devfs_root->childs;
			strcpy(a, name);
			strcpy(b, itoa(i));//48+i;
			strcat(b, "\0");//b[1]='\0';
			strcat(a, b);

			while(next != NULL)
			{
				if(strcmp(a, next->name) == 0)
				{
					i++;
					goto tent;
				}
				next = next->next;
			}
			over = 0;
			strcpy(res, a);
			strcat(res, "\0");
		}
		if(res[0] != '\0')
			return strlen(res);
			
	}
	return 0;	
}



/**
 * Ottiene un nodo
 */
uint32_t devfs_get_node(inode_t *root, uint32_t i, inode_t **child)
{
	inode_t *tmp = devfs_root->childs;
	
	while(tmp != NULL)
	{
		//printf("%s\n", tmp->name);
		if(tmp->inode_n == i)
		{
			*child = tmp;
			//printf("get_node_ found\n");
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}




/**
 * Apre un file
 */
uint32_t devfs_open(inode_t *node, char *flags)
{
	int i = 0;
	struct dirent dir;
	
	if(node->fs_node == NULL)
		return 0;
	
	return 1;
}



/**
 * Legge da file
 */
uint32_t devfs_read(inode_t *node, char *buf, uint32_t size, uint64_t offset)
{
	if(	(node->fs_node != NULL) && 
		(((devfs_node_t *) (node->fs_node))->driver != NULL) &&
		(((devfs_node_t *) (node->fs_node))->device != NULL) &&
		((((devfs_node_t *) (node->fs_node))->driver)->read != NULL))
	{
		return (((devfs_node_t *) (node->fs_node))->driver)->read(((devfs_node_t *) (node->fs_node))->device, buf, size, offset);
	}
	return 0;
}



/**
 * Scrive su file
 */
uint32_t devfs_write(inode_t *node, char *buf, uint32_t size, uint64_t offset)
{
	if(	(node->fs_node != NULL) && 
		(((devfs_node_t *) (node->fs_node))->driver != NULL) &&
		(((devfs_node_t *) (node->fs_node))->device != NULL) &&
		((((devfs_node_t *) (node->fs_node))->driver)->write != NULL))
	{
		return (((devfs_node_t *) (node->fs_node))->driver)->write(((devfs_node_t *) (node->fs_node))->device, buf, size, offset);
	}
	return 0;
}



/**
 * Chiude un file aperto
 */
uint32_t devfs_close(inode_t *node)
{
	return 0;
}
