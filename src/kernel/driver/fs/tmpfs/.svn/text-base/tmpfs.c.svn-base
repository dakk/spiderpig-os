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
 * \file kernel/driver/fs/tmpfs/tmpfs.c
 * \author Davide Gessa
 * \date 12/22/2009
 */
#include "tmpfs.h"
#include <driver.h>
#include <fs/fs.h>
#include <malloc.h>

driver_t driver_tmpfs =
{
	.name = "tmpfs\0",
	.author = "Davide Gessa\0",
	.probe = NULL,
	
	.type = DRV_TYPE_FS,
	.fs.ifdev = 0,
	
	.fs.mount = tmpfs_mount,
	.fs.umount = tmpfs_umount,
	
	.fs.mkdir = tmpfs_mkdir,
	.fs.readdir = tmpfs_readdir,
	
	.fs.read = tmpfs_read,
	.fs.write = tmpfs_write,
	.fs.open = tmpfs_open,
	.fs.close = tmpfs_close,
	
	.fs.get_node = tmpfs_get_node,
	.fs.delete_node = tmpfs_delete_node,
	.fs.create_node = NULL,
	
	.fs.write_stat = NULL,
	.fs.read_stat = NULL,
	
	.fs.link = tmpfs_link,
	.fs.unlink = tmpfs_unlink
};



/**
 * Ottiene un nodo
 */
uint32_t tmpfs_get_node(inode_t *root, uint32_t i, inode_t **child)
{
	inode_t *tmp = root->childs;
	
	while(tmp != NULL)
	{
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
 * Legge il contenuto della dir
 */
uint32_t tmpfs_readdir(inode_t *root, uint32_t n, struct dirent *d)
{
	inode_t *childs;
	unsigned i;
	
	childs = root->childs;
	i = 0;
	
	while(childs != NULL && i <= n)
	{
		if(i == n)
		{
			//printf("%s %n\n", childs->name, childs->inode_n);
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
 * Umonta il tmpfs
 */
uint32_t tmpfs_umount(inode_t *root)
{
	return MOUNT_STATE_OK;
}



/**
 * Monta il tmpfs
 */
uint32_t tmpfs_mount(char *dev, uint32_t flags, inode_t *root)
{
	return MOUNT_STATE_OK;
}



/**
 * Crea un nodo dir
 */
uint32_t tmpfs_mkdir(inode_t *root, char *name)
{
	if(root->type != NODE_TYPE_DIR)
		return 0;
		
	inode_t *node = fs_create_node(name, root, NODE_TYPE_DIR, 0);
		
	return node->inode_n;
}





/**
 * Elimina un nodo
 * 
 * \note dobbiamo fare in modo che deallochi i file
 */
uint32_t tmpfs_delete_node(inode_t *root, char *name)
{
	//if(root->type != NODE_TYPE_DIR)
	//	return 0;
		
	inode_t *c;
	inode_t *p;
	uint32_t in;
	
	p = NULL;
	c = root->childs;

	while(c != NULL)
	{
		if(strcmp(c->name, name) == 0)
		{
			if(p != NULL)
				p->next = c->next;
			else
				root->childs = root->childs->next;
				
			in = c->inode_n;
			free(c);
			return in;
		}
		p = c;
		c = c->next;
	}
	
	return 0;
}



/**
 * Apre un file
 */
uint32_t tmpfs_open(inode_t *node, char *flags)
{
	int i = 0;
	struct dirent dir;
	
	if(node->fs_node == NULL)
	{
		(node->fs_node) = (void *) malloc(sizeof(tmpfs_node_t));
		((tmpfs_node_t *) (node->fs_node))->size = 0;
		((tmpfs_node_t *) (node->fs_node))->data = NULL;
		//((tmpfs_node_t *) (node->fs_node))->data = (tmpfs_data_node_t *) malloc(sizeof(tmpfs_data_node_t));
		//strcpy((((tmpfs_node_t *) (node->fs_node))->data)->data, "ciaooo\n");
		//printf("%s\n",(((tmpfs_node_t *) (node->fs_node))->data)->data);
		//((tmpfs_node_t *) (node->fs_node))->size = 7;
		
		return 1;		
	}
	return 1;
}





/**
 * Legge da file
 */
uint32_t tmpfs_read(inode_t *node, char *buf, uint32_t size, uint64_t offset)
{
	uint32_t i;
	uint32_t j;
	uint32_t r;
	tmpfs_node_t *tmpnode;
	tmpfs_data_node_t *tmpdata;
	
	// Numero del nodo della lista
	j = offset / TMPFS_DATA_SIZE;
	
	// Ci posizioniamo al nodo stabilito
	tmpnode = (tmpfs_node_t *) (node->fs_node); 

	// Controlli necessari
	if(tmpnode == NULL || tmpnode->size < offset)
		return 0;

	tmpdata = tmpnode->data;
	//printf("%s", tmpdata->data);
	
	for(i = 0; i < j; i++)
		tmpdata = tmpdata->next;

		
	// Il byte di inizio lettura
	j = offset % TMPFS_DATA_SIZE;
			
	// Possiamo leggere
	r = 0;
	
	for(i = 0; i < size; i++)
	{
		if((j > TMPFS_DATA_SIZE))
		{
			tmpdata = tmpdata->next;
			j = 0;
			if(tmpdata == NULL)
			{
				buf[i] = '\0';
				return r;
			}
		}
		
		buf[i] = tmpdata->data[j];
		
		r++;
		j++;
		
		if(r == size)
		{
			buf[i+1] = '\0';
			return size;
		}
	}
}



/**
 * Scrive su file
 */
uint32_t tmpfs_write(inode_t *node, char *buf, uint32_t size, uint64_t offset)
{
	uint32_t i;
	uint32_t j;
	uint32_t r;
	tmpfs_node_t *tmpnode;
	tmpfs_data_node_t *tmpdata;
	
	// Numero del nodo della lista
	j = offset / TMPFS_DATA_SIZE;
	
	// Ci posizioniamo al nodo stabilito
	tmpnode = (tmpfs_node_t *) (node->fs_node); 

	// Controlli necessari
	if(tmpnode == NULL || tmpnode->size < offset)
		return 0;

	tmpdata = tmpnode->data;
	
	for(i = 0; i < j; i++)
	{
		if(tmpdata == NULL)
		{
			tmpdata = (tmpfs_data_node_t *) malloc(sizeof(tmpfs_data_node_t));
			//printf("allocated new \n");
		}
		tmpdata = tmpdata->next;
	}
		
	// Il byte di inizio lettura
	j = offset % TMPFS_DATA_SIZE;

	//printf("%d\n", j);
	// Possiamo scrivere
	r = 0;
	
	for(i = 0; i < size; i++)
	{
		if((j > TMPFS_DATA_SIZE))
		{
			tmpdata = tmpdata->next;
			j = 0;
			if(tmpdata == NULL)
				return r;
		}
		tmpdata->data[j] = buf[i];
		//putchar(tmpdata->data[j]);

		tmpnode->size++;
		r++;
		j++;
		
		if(r == size)
			return size;
	}	
	return 0;
}


/**
 * Chiude  un file aperto
 */
uint32_t tmpfs_close(inode_t *n)
{
	if(n->fs_node != NULL)
		free(n->fs_node);

	return 1;
}



/**
 * Crea un link
 */
uint32_t tmpfs_link(inode_t *root, char *name, inode_t *dest, char *link_name)
{
	if(root == NULL || root->type != NODE_TYPE_DIR)
		return 0;
		
	inode_t *c;
	inode_t *p;
	uint32_t in;
	
	c = root->childs;

	while(c != NULL)
	{
		//printf("%s\n", c->name);
		if(strcmp(c->name, name) == 0)
		{
			in = c->inode_n;
			break;
		}
		c = c->next;
	}
	
	if(c == NULL)
		return 0;


	if(dest->type != NODE_TYPE_DIR)
		return 0;
		
	inode_t *node = fs_create_node(link_name, dest, NODE_TYPE_LINK, 0);
	node->link = c;
	//printf("src: %s\tdest: %s\n", (node->link)->name, node->name);
	return node->inode_n;	
}


/**
 * Elimina un link
 */
uint32_t tmpfs_unlink(inode_t *root, char *name)
{
	return tmpfs_delete_node(root, name);
	
	/*
	if(root->type != NODE_TYPE_DIR)
		return 0;
		
	inode_t *c;
	inode_t *p;
	uint32_t in;
	
	p = NULL;
	c = root->childs;

	while(c != NULL)
	{
		if(strcmp(c->name, name) == 0)
		{
			if(p != NULL)
				p->next = c->next;
			else
				root->childs = root->childs->next;
				
			in = c->inode_n;
			// Da sostituire con delete_inode
			free(c);
			return in;
		}
		p = c;
		c = c->next;
	}
	*/
	return 0;	
}
