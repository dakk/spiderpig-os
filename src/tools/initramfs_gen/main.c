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
#include "initramfs.h"
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv)
{
	int inode_number = 1;
	unsigned last_data_offset;
	unsigned last_data_size;
	unsigned last_seek;
	char file_name[1024];
	int i;
	FILE *f;
	FILE *to_w;
	
	initramfs_node_t node;
	
	f = fopen(argv[1], "wb");
	
	if(f == NULL)
	{
		printf("cannot open %s\n", argv[1]);
		return 0;
	}
	
	// Posizione e dimensione di partenza
	last_data_offset = 0;
	last_data_size = (sizeof(initramfs_node_t) * (argc - 2));
	
	// Ciclo di inserimento
	for(i = 2; i < argc; i++)
	{
		node.identify = 0xABCDEF;
		node.n = i;

		// Puliamo il path
		char node_name[32];
		uint32_t p = 0;
		char *point = argv[i];
		while(*point != '\0')
		{
			if(*point == '/')
				p = 0;

			else
			{
				node_name[p] = *point;
				p++;		
			}
			
			point++;		
		}
		node_name[p] = '\0';

		// Impostiamo il nome del nodo =)
		strcpy(node.name, node_name);
		
		// Posizione corrente
		last_seek = ftell(f);
		
		// Carichiamo il file
		node.data = last_data_offset + last_data_size;
		last_data_size = 0;
		
		fseek(f, node.data, SEEK_SET);
		
		//strcpy(file_name, "files/");
		strcpy(file_name, argv[i]);
		 
		to_w = fopen(file_name, "rb");
		if(to_w == NULL)
			continue;
		char buf[10];
		unsigned size = 0;
		
		while(fread(buf, sizeof(char), 1, to_w) != 0)
		{
			fwrite(buf, sizeof(char), 1, f);
			size++;
		}
		
		node.size = size;
		last_data_size = size;
		last_data_offset = node.data;
		printf("%s size: %d  data: %d\n", node.name, node.size, node.data);
		
		// Torna indietro e scrive la struct
		fseek(f, last_seek, SEEK_SET);
		fwrite(&node, sizeof(initramfs_node_t), 1, f);
	}
	fclose(f);
	
	return 0;
}
