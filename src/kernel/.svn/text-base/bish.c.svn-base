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
 * \file kernel/bish.c
 * \author Davide Gessa
 * \date 10-22-09
 * \note bish built in shell
 */
#include <bish.h>
#include <klibc/stdio.h>
#include <klibc/string.h>
#include <driver/input/keyboard.h>
#include <network/network.h>
#include <network/socket.h>
#include <network/route.h>
#include <network/net/icmp.h>
#include <task/task.h>
#include <driver/net/rs232.h>
#include <driver/net/modem.h>
#include <driver/bus/pci/pci.h>
#include <arch.h>
#include <main.h>
#include <driver.h>
#include <video.h>
#include <fs/fs.h>
#include <syscall.h>
#include <debug.h>
#include <task/elf.h>
#include <config.h>

/**
 * Lista commandi supportati
 */
bish_cmd_t bish_cmd_list[] = 
	{
		{ .func = &bish_help,		.name = "help\0",		.desc = "show commands help"},
		{ .func = &bish_true,		.name = "true\0",		.desc = "return true"},
		{ .func = &bish_false,		.name = "false\0",		.desc = "return false"},
		{ .func = &bish_set, 		.name = "set\0",		.desc = "variable ops"},
		{ .func = &bish_unset,		.name = "unset\0",		.desc = "unset a variable"},
		{ .func = &bish_memstat,	.name = "memstat\0",	.desc = "memory stat"},
		{ .func = &bish_pslist,		.name = "pslist\0",		.desc = "process list"},
		{ .func = &bish_regdump,	.name = "regdump\0",	.desc = "dump all registers"},
		{ .func = &bish_shutdown,	.name = "shutdown\0",	.desc = "shutdown the pc"},
		{ .func = &bish_sysinfo,	.name = "sysinfo\0",	.desc = "print system info"},
		{ .func = &bish_devlist,	.name = "devlist\0",	.desc = "device list"},
		{ .func = &bish_driver,		.name = "driver\0",		.desc = "driver tool"},
		//{ .func = &bish_snake,	.name = "snake\0",		.desc = "textual snake game"},
		{ .func = &bish_tree,		.name = "tree\0",		.desc = "list all directories"},
		{ .func = &bish_rpncalc,	.name = "rpncalc\0",	.desc = "rpn calculator"},
		{ .func = &bish_mount,		.name = "mount\0",		.desc = "mount program"},
		{ .func = &bish_cd,			.name = "cd\0",			.desc = "change directory"},
		{ .func = &bish_cp,			.name = "cp\0",			.desc = "copy file"},
		{ .func = &bish_ls,			.name = "ls\0",			.desc = "list directory"},
		{ .func = &bish_mkdir,		.name = "mkdir\0",		.desc = "make directory"},
		{ .func = &bish_clear,		.name = "clear\0",		.desc = "clear the shell"},
		{ .func = &bish_rm,			.name = "rm\0",			.desc = "remove a node"},
		{ .func = &bish_read,		.name = "read\0",		.desc = "display a text file"},
		{ .func = &bish_write,		.name = "write\0",		.desc = "write a text file"},
	
	#ifdef EELF
		{ .func = &bish_elf,		.name = "elf\0",		.desc = "elf utility"},
	#endif
	
		{ .func = &bish_link,		.name = "link\0",		.desc = "create a link"},
		{ .func = &bish_unlink,		.name = "unlink\0",		.desc = "remove a link"},
		{ .func = &bish_memdump,	.name = "memdump\0",	.desc = "memory dump"},

	// Serial
	#ifdef DRS232
		{ .func = &bish_serial,		.name = "serial",		.desc = "rs232 operations"},
	
		#ifdef DMODEM
			{ .func = &bish_modem,		.name = "modem\0",		.desc = "modem control"},
		#endif		
	#endif

	// Network programs
	#ifdef NETWORK
		{ .func = &bish_route,		.name = "route\0",		.desc = "routing table"},
		{ .func = &bish_netconf,	.name = "netconf\0",	.desc = "configure networks"},
		{ .func = &bish_irc,		.name = "irc\0",		.desc = "irc client"},
		{ .func = &bish_ping,		.name = "ping\0",		.desc = "ping"},
	#endif	
	
		{ .func = NULL,				.name = "\0",			.desc = "\0" }
	};
	

char *argv[32];

	
/**
 * Avvio della BuiltIn Shell
 */
void bish()
{
	DEBUGP("bish()\n");
	

	driver_initd("keyboard");	
		
	char while_c = 1;
	char buf[1024];
	int argc;
	int x;
	int state;
	
	for(x = 0; x < 32; x++)
		argv[x] = (char *) malloc(128);
	
	
	// Azzera tutte le variabili
	for(x = 0; x < BISH_VAR_NUM; x++)
	{
		strcpy(bish_var_list[x].name, "\0");
		strcpy(bish_var_list[x].value, "\0");
	}


	strcpy(bish_var_list[0].name, "CUR_DIR\0");
	strcpy(bish_var_list[0].value, "/\0");
	
	strcpy(bish_var_list[1].name, "PATH\0");
	strcpy(bish_var_list[1].value, "/bin\0");
	
	strcpy(bish_var_list[2].name, "EDITOR\0");
	strcpy(bish_var_list[2].value, "/bin/nano\0");
	
	printf("\n");
	
	// Mostra l'help iniziale
	#ifdef VERBOSE
	bish_help(0, 0);
	printf("\n");
	#endif
	
	// Mainloop della shell
	while(while_c)
	{
		printf("%s", bish_var_list[0].value);
		video_puts_colored(VIDEO_HI_BLUE_BLACK, "$ ");
		scanf("%s", buf);
		if(buf[0] == '\0') continue;
		strcpy(argv[0], "\0");
		
		state = bish_parse_command(buf);
		
		// Exit
		if(strcmp("exit\0", buf) == 0)
			while_c = 0;
		else if(state == -1) 
			printf(MSG_CMD_NOT_FOUND);
	}
}



/**
 * Esegue un commando
 */
int bish_parse_command(char *buf)
{
	int state;
	int argc;
	int x;
	
	// Split degli argomenti
	argc = 0;
	x = 0;
	int buf_c = 0;

	while(buf[x] != '\0')
	{
		argv[argc][buf_c] = buf[x];
			
		x++;
		buf_c++;
			
		if((buf[x] == ' ') || (buf[x] == '\0'))
		{
			argv[argc][buf_c] = '\0';
			argc++;
			buf_c = 0;
			if(buf[x] == '\0') break;
			x++;
		}
	}
	
	state = -1;


	// Shell
	if(strcmp("sh", argv[0]) == 0)
	{
		file_t *t;//state = bish_cmd_list[x].func(argc, &argv[0]);

		char name[128];
		fs_get_full_path(bish_var_list[0].value, argv[1], name);
		
		t = fs_open(name, "r");
	
		if(t != NULL)
		{
			char bu[3024];
			int bu_p = 0;
			int max = fs_read(t, bu, 3024);
			//puts(bu);
			
			char line[512];
			int line_p = 0;
			
			while(bu_p < max)
			{
				line[line_p] = bu[bu_p];
				//putchar(line[line_p]);
					
				if((line[line_p] == '\n') || (line[line_p] == '\0'))
				{
					line[line_p] = '\0';
					line[line_p+1] = '\n';
					//puts(line);
					
					bish_parse_command(line);
					line_p = 0;
					
					if(bu[bu_p] == '\0')
						return 0;
						
					bu_p++;
					
					continue;
				}
				
				line_p++;
				bu_p++;
			}
					
	
			return 0;	
		}
		else
		{
			printf("cannot execute %s\n", argv[1]);
			return 1;
		}
	}


	for(x = 0; x < BISH_CMD_NUM; x++)
	{
		if(strcmp(bish_cmd_list[x].name, argv[0]) == 0)
		{
			state = bish_cmd_list[x].func(argc, &argv[0]);
			break;
		}
	}
		
		
	#ifdef EELF
		char name[128];
		fs_get_full_path(bish_var_list[0].value, argv[0], name);
		
		if(fs_open(name, "r") != NULL)
		{
			strcpy(argv[1], argv[0]);
			state = bish_elf(2, &argv[0]);			
		}
	#endif
		
	return state;	
}

/**
 * Memory dump
 */
int bish_memdump(int argc, char **argv)
{
	char *start;
	char *end;
	int i;
	
	if(argc == 2)
		start = (char *) atoi(argv[1]);
	else if(argc == 3)
	{
		start = (char *) atoi(argv[1]);
		end = (char *) atoi(argv[2]);
	}
	else
	{
		start = (char *) mod_addr;
		end = (char *) mod_addr+1200;
	}
	
	while(start < end)
	{
		printf("0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x   ", 	
			*start, *(start+1), *(start+2), *(start+3), *(start+4), *(start+5), *(start+6), *(start+7));
		
		for(i = 0; i < 8; i++)
		{
			if( (((*(start+i)) >= 'a') && ((*(start+i)) <= 'z')) ||
				(((*(start+i)) >= 'A') && ((*(start+i)) <= 'Z')) ||
				(((*(start+i)) >= '0') && ((*(start+i)) <= '9')))
					putchar(*(start+i));
			else
				putchar('.');
			putchar(' ');
		}	
		printf("\n");
		
		start += 16;
	}
	
	return 0;
}
	


#ifdef DRS232

#ifdef DMODEM
/**
 * Operazioni con il modem seriale
 */
int bish_modem(int argc, char **argv)
{	
	if((argc >= 3) && (strcmp(argv[1], "-d") == 0))
	{
		device_t *dev;
		
		switch(argv[1][0])
		{
			case '1':
				dev = &rs232_com1;
				break;
			case '2':
				dev = &rs232_com2;
				break;
			case '3':
				dev = &rs232_com3;
				break;
			case '4':
				dev = &rs232_com4;
				break;
			default:
				dev = &rs232_com1;
		}
		
		modem_disconnect(dev);
	}

	else if((argc >= 4) && (strcmp(argv[1], "-c") == 0))
	{
		driver_initd("rs232");
		driver_initd("modem");	
		
		device_t *dev;
		
		switch(argv[2][0])
		{
			case '1':
				dev = &rs232_com1;
				break;
			case '2':
				dev = &rs232_com2;
				break;
			case '3':
				dev = &rs232_com3;
				break;
			case '4':
				dev = &rs232_com4;
				break;
			default:
				dev = &rs232_com1;
		}
		modem_connect(dev, argv[3]);
	}

	else
	{
		printf("use: modem -c port number\n\tmodem -d port\n");
		return 0;
	}

	return 0;
}
		
#endif

/**
 * Operazioni con la porta seriale
 */
int bish_serial(int argc, char **argv)
{	
	if((argc >= 3) && (strcmp(argv[1], "-t") == 0))
	{
		driver_initd("rs232");	
		
		char buf;
		uint32_t port;
		
		switch(argv[3][0])
		{
			case '1':
				port = COM1;
				break;
			case '2':
				port = COM2;
				break;
			case '3':
				port = COM3;
				break;
			case '4':
				port = COM4;
				break;
			default:
				port = COM1;
		}
		
		while(1)
		{
			buf = rs232_receive(port);
			if(buf != 0)
				putchar(buf);
			
			buf = getchar();
			if(buf != 0)
			{
				putchar(buf);
				rs232_send(port, buf);
			}
		}
	}
	else
	{
		printf("use: serial -t port\n\tserial -s tosend.txt port\n\tserial -r received.txt port\n");
		return 0;
	}

	return 0;
}


#endif





/**
 * Visualizza il contenuto della directory corrente
 * 
 * \note -R visualizza solo un livello
 */
int bish_ls(int argc, char **argv)
{
	struct dirent dir_tmp;


	// Ls di questa dir
	if(argc == 1)
	{
		uint32_t x = 0;
		uint32_t y = video_gety();
		dir_t *dir = fs_opendir(bish_var_list[0].value);
		
		if(dir == NULL)
			return 0;
			
		while(fs_readdir(dir, &dir_tmp) != 0)
		{
			printf(" ");
			video_puts_colored(VIDEO_HI_BLUE_BLACK, dir_tmp.name);

			//printf(" %s", dir_tmp.name);
			x = x + 25;
			if(x >= (VIDEO_MAX_X - 20))
			{
				printf("\n");
				x = 0;
				y = video_gety();
			}
			video_gotoxy(x, y);
		}
		if(x != 0) printf("\n");
		
		fs_closedir(dir);
		return 0;
	}
	
	// Help
	else if((argc == 2) && (strcmp(argv[1], "-h") == 0))
	{
		printf("use: ls -h\n\tls -R\n\tls -i\nls /dir\n\tls\n");
		//dir_t *a = fs_opendir("/bin");
		
	}
	
	// Ls di questa dir con inode numbers
	else if((argc == 2) && (strcmp(argv[1], "-i") == 0))
	{
		uint32_t x = 0;
		uint32_t y = video_gety();
		dir_t *dir = fs_opendir(bish_var_list[0].value);
		
		if(dir == NULL)
			return 0;
			
		while(fs_readdir(dir, &dir_tmp) != 0)
		{
			printf(" %d ", dir_tmp.inode);
			
			video_gotoxy(x + 4, y);
			
			video_puts_colored(VIDEO_HI_BLUE_BLACK, dir_tmp.name);

			//printf(" %s", dir_tmp.name);
			x = x + 25;
			if(x >= (VIDEO_MAX_X - 20))
			{
				printf("\n");
				x = 0;
				y = video_gety();
			}
			video_gotoxy(x, y);
		}
		if(x != 0) printf("\n");
		
		fs_closedir(dir);
		return 0;
	}

	// Tree listing
	else if((argc == 2) && (strcmp(argv[1], "-R") == 0))
	{
		char name[1024];
		strcpy(name, bish_var_list[0].value);
		
		dir_t *dir = fs_opendir(name);
		
		if(dir == NULL)
			return 0;
			
		while(fs_readdir(dir, &dir_tmp) != 0)
		{
			dir_t *dir2;

			printf(" %s\n", dir_tmp.name);
			strcpy(name, bish_var_list[0].value);
			strcat(name, dir_tmp.name);
			dir2 = fs_opendir(name);
			
			if(dir2 == NULL)
				continue;
			
			while(fs_readdir(dir2, &dir_tmp) != 0)
			{
				printf(" \t%s\n", dir_tmp.name);
			}
			fs_closedir(dir2);
			printf("\n");			
		}
		
		fs_closedir(dir);
		
	}
	
	// Ls di un altra dir
	else if(argc == 2)
	{
		char name[1024];
		fs_get_full_path(bish_var_list[0].value, argv[1], name);

		dir_t *dir = fs_opendir(name);
		
		if(dir == NULL)
		{
			printf("no such directory %s\n", name);
			return 0;
		}
		
		while(fs_readdir(dir, &dir_tmp) != 0)
		{
			printf(" %s\n", dir_tmp.name);
		}
		
		fs_closedir(dir);
		return 0;
	}

}



/**
 * Visualizza il contenuto di un file
 * 
 * \note inserire la possibilita di scegliere il byte di inizio e di fine
 */
int bish_read(int argc, char **argv)
{
	char buf[1024];
	
	if(argc < 2)
	{
		printf("use: read file.txt\n");
		return 0;
	}
	
	char name[128];
	fs_get_full_path(bish_var_list[0].value, argv[1], name);
	
	file_t *t = fs_open(name, "r");
	if(t != NULL)
	{
		while(fs_read(t, buf, 1024) != 0)
			printf("%s",buf);
		printf("\n");
	}
	else
		printf("cannot open %s\n", argv[1]);
	
	return 0;
}





/**
 * Copia un file in un altro
 */
int bish_cp(int argc, char **argv)
{
	char buf[1024];
	
	if(argc < 3)
	{
		printf("use: cp file_source.txt file_dest.txt\n");
		return 0;
	}
	
	char name1[128];
	char name2[128];
	
	fs_get_full_path(bish_var_list[0].value, argv[1], name1);
	fs_get_full_path(bish_var_list[0].value, argv[2], name2);


	file_t *s = fs_open(name1, "r");
	file_t *d = fs_open(name2, "w");
	
	if(s == NULL)
		printf("cannot open %s\n", argv[1]);
	else if(d == NULL)
		printf("cannot open %s\n", argv[2]);
	else
	{
		int i = 0;
		while(fs_read(s, buf, 16) != 0)
		{
			i++;
			fs_write(d, buf, 16);
			//printf("cp %d\n", i);
		}
		printf("writted %d bytes\n", i*16);
	}
		
	return 0;
}





/**
 * Crea un link
 */
int bish_link(int argc, char **argv)
{
	if(argc < 3)
	{
		printf("use: link file link_file\n");
		return 0;
	}
	
	uint32_t e = fs_link(argv[1], argv[2]);
	
	switch(e)
	{
		case FS_ER_NT_PERM:
			printf("operation not permitted\n");
			break;
			
		case FS_ER_NT_FOUND:
			printf("file not found\n");
			break;
		
		
	}
	
	return 0;
}



/**
 * Elimina un link
 */
int bish_unlink(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("use: unlink link_file\n");
		return 0;
	}
	
	uint32_t e = fs_unlink(argv[1]);
	
	switch(e)
	{
		case FS_ER_NT_PERM:
			printf("operation not permitted\n");
			break;
			
		case FS_ER_NT_LINK:
			printf("%s is not a link\n", argv[1]);
			break;
			
		case FS_ER_NT_FOUND:
			printf("link not found\n");
			break;
		
	}
}


/**
 * Scrive il contenuto su un file
 */
int bish_write(int argc, char **argv)
{
	char buf[1024];
	
	if(argc < 2)
	{
		printf("use: write file.txt\n");
		return 0;
	}
	
	char name[128];
	if(argv[1][0] != '/')
	{
		strcpy(name, bish_var_list[0].value);
		if(name[strlen(name)-1] != '/')
			strcat(name, "/");
		strcat(name, argv[1]);
	}
	else strcpy(name, argv[1]);
	
	file_t *t = fs_open(name, "w");
	if(t != NULL)
	{
		printf("text: ");
		scanf("%s", buf);
		fs_write(t, buf, strlen(buf));
		fs_write(t, "\n", 1);
		fs_write(t, "\0", 1);
	}
	else
		printf("cannot open %s\n", argv[1]);
	
	return 0;
}


#ifdef EELF
/**
 * Elf utils
 */
int bish_elf(int argc, char **argv)
{
	char buf[102400];
	char *point = buf;
	
	if(argc < 2)
	{
		printf("use: elf elf_file\n");
		printf("use: elf -i elf_file\n");
		return 0;
	}
	
	if(argc == 2)
	{
		char name[128];
		fs_get_full_path(bish_var_list[0].value, argv[1], name);
	
		char *task_argv[] = { "test" };
		if(!task_exec(name, task_argv, 1, 0))
			printf("cannot exec %s\n", name);
	}
	else if((argc == 3) && (strcmp(argv[1], "-i") == 0))
	{
		char name[128];
		fs_get_full_path(bish_var_list[0].value, argv[2], name);

		file_t *t = fs_open(name, "r");
		if(t != NULL)
			while(fs_read(t, point, 1) != 0)
				point++;
		else
			printf("cannot open %s\n", argv[2]);
			
		if(!elf_check(buf))
		{
			printf("this file is not an elf file\n");
			return 0;
		}
		
		elf_header_t *header = (elf_header_t *) buf;
		
		printf("elf:\n\tident: ");
		putchar(*(header->ident+1));
		putchar(*(header->ident+2));
		putchar(*(header->ident+3));

		printf("\n\tnident: %d", *(header->ident+ELF_ID_NIDENT));

		printf("\n\tdata: ");
		switch(*(header->ident+ELF_ID_DATA))
		{
			case ELF_DATA_2LSB:
				printf("2lsb\n");
				break;
			case ELF_DATA_2MSB:
				printf("2msb\n");
				break;
			case ELF_DATA_NONE:
				printf("none\n");
				break;
			default:
				printf("0x%x (unrecognized)\n", *(header->ident+ELF_ID_DATA));
		};
		
		printf("\tclass: ");
		switch(*(header->ident+ELF_ID_CLASS))
		{
			case ELF_CLASS_NONE:
				printf("none\n");
				break;
			case ELF_CLASS_32:
				printf("32bit\n");
				break;
			case ELF_CLASS_64:
				printf("64bit\n");
				break;
			default:
				printf("0x%x (unrecognized)\n", *(header->ident+ELF_ID_CLASS));
		};

		
		printf("\ttype: ");
		switch(header->type)
		{
			case ELF_TYPE_NONE:
				printf("none\n");
				break;
			case ELF_TYPE_REL:
				printf("rel\n");
				break;
			case ELF_TYPE_EXEC:
				printf("exec\n");
				break;
			case ELF_TYPE_DYN:
				printf("dyn\n");
				break;
			case ELF_TYPE_CORE:
				printf("core\n");
				break;
			case ELF_TYPE_LOPROC:
				printf("loproc\n");
				break;
			case ELF_TYPE_HIPROC:
				printf("hiproc\n");
				break;
			default:
				printf("0x%x (unrecognized)\n", header->type);
		};

		printf("\tversion: ");
		switch(header->version)
		{
			case ELF_VER_CURRENT:
				printf("current version\n");
				break;
			case ELF_VER_NONE:
				printf("invalid version\n");
				break;
			default:
				printf("0x%x (unrecognized)\n", header->version);
		};

		printf("\tmachine: ");
		switch(header->machine)
		{
			case ELF_MAC_NONE:
				printf("none\n");
				break;
			case ELF_MAC_M32:
				printf("m32\n");
				break;
			case ELF_MAC_SPARC:
				printf("sparc\n");
				break;
			case ELF_MAC_386:
				printf("386\n");
				break;
			case ELF_MAC_68K:
				printf("68k\n");
				break;
			case ELF_MAC_88K:
				printf("88k\n");
				break;
			case ELF_MAC_860:
				printf("860\n");
				break;
			case ELF_MAC_MIPS:
				printf("mips\n");
				break;
			default:
				printf("0x%x (unrecognized)\n", header->version);
		};
	}
		
	return 0;
}
#endif


/**
 * Crea una cartella nella directory indicata o corrente
 */
int bish_mkdir(int argc, char **argv)
{
	char name[512];

	fs_get_full_path(bish_var_list[0].value, argv[1], name);
	fs_makedir(name);
}



/**
 * Rimuove una cartella nella directory indicata
 */
int bish_rm(int argc, char **argv)
{
	char name[512];
	fs_get_full_path(bish_var_list[0].value, argv[1], name);
	fs_rm(name);
}





/**
 * Cancella lo schermo
 */
int bish_clear(int argc, char **argv)
{
	video_clear();
}




/**
 * Cambia directory
 */
int bish_cd(int argc, char **argv)
{
	if(argc < 2)
	{
		strcpy(bish_var_list[0].value, "/\0");
		return 0;
	}
	else if(strcmp(argv[1], "-h") == 0)
	{
		printf("use: cd /directory\n");
		return 0;
	}
	
	// Salviamo il vecchio path
	char old[1024];
	strcpy(old, bish_var_list[0].value);
	
	// Creiamo il nuovo
	if(strcmp(argv[1], "/\0") == 0)
		strcpy(bish_var_list[0].value, "/\0");
	else if(argv[1][0] == '/')
		strcpy(bish_var_list[0].value, argv[1]);
	else
	{
		strcpy(bish_var_list[0].value, old);
		if(old[strlen(old)-1] != '/')
			strcat(bish_var_list[0].value, "/");
		strcat(bish_var_list[0].value, argv[1]);
		strcat(bish_var_list[0].value, "/");
	}
	
	
	// Controllare se esiste il percorso
	inode_t *a;
	
	if((fs_get_node(bish_var_list[0].value, &a) == 0))
	{
		printf("path %s doesn't exist\n",bish_var_list[0].value); 
		strcpy(bish_var_list[0].value, old);
	}
	else if(   ((a->type != NODE_TYPE_DIR) && 
			    (a->type != NODE_TYPE_LINK)) ||
			   ((a->type == NODE_TYPE_LINK) && (a->link->type != NODE_TYPE_DIR)))
	{
		printf("path %s isn't a directory\n",bish_var_list[0].value); 
		strcpy(bish_var_list[0].value, old);
	}
	
	return 0;	
}


/**
 * Mostra un messaggio di help
 */
int bish_help(int argc, char **argv)
{
	if(argc == 0 || argc == 1)
	{
		printf(MSG_CMD_INTRO);
		printf(MSG_CMD_HELP);
	}
	
	if((argc == 2) && (strcmp(argv[1], "-l") == 0))
	{
		int x, i, t;
		
		i = 0;
		for(x = 0; x < BISH_CMD_NUM; x++)
		{
			if(bish_cmd_list[x].name[0] != '\0')
				printf("%s - %s\n", bish_cmd_list[x].name, bish_cmd_list[x].desc);
			else break;
			i++;
			if(i > 20)
			{
				i = 0;
				printf("press return...\n");
				scanf("%d", &t);
			}
		}			
	}
	else if(argc == 1)
	{
		int x;
		
		printf("\n");
		for(x = 0; x < BISH_CMD_NUM; x++)
		{
			if(bish_cmd_list[x].name[0] != '\0')
				printf("%s ", bish_cmd_list[x].name);
			else break;
		}	
		
		printf("\n");
		return 0;
	}
	
	else if(argc >= 2)
	{
		int x, y;
		
		for(x = 0; x < BISH_CMD_NUM; x++)
		{
			if(argv[1][0] == '%' && bish_cmd_list[x].name[0] != '\0') 
				printf("%s - %s\n", bish_cmd_list[x].name, bish_cmd_list[x].desc);
			else if(strcmp(argv[1], bish_cmd_list[x].name) == 0)
			{
				printf("%s - %s\n", argv[1], bish_cmd_list[x].desc);
				return 0;
			}
		}
		
		if(argv[1][0] == '%') 
			return 0;
			
		printf("command %s not found\n", argv[1]);
		return 1;
	}
	
	return 0;
}



/**
 * Lista processi
 */
int bish_pslist(int argc, char **argv)
{
	task_t *t = task_list;
	
	printf("pid       name\n");
	
	while(t != NULL)
	{
		printf("%d         %s\n", t->pid, t->name);
		t = t->next;
	}

	return 0;
}



/**
 * Vero
 */
int bish_true(int argc, char **argv)
{
	return 1;
}



/**
 * Falso
 */
int bish_false(int argc, char **argv)
{
	return 0;
}


/**
 * Memory Stat
 */
int bish_memstat(int argc, char **argv)
{
	printf("used: %dkb (%d%%)\n", mm_get_used_mem(), mm_get_used_mem() * 100 / mm_get_total_mem());
	printf("total: %dkb\n", mm_get_total_mem());
	return 0;
}



/**
 * Spegne il pc
 */
int bish_shutdown(int argc, char **argv)
{
	shutdown();
	return 0;
}


/**
 * Operazioni sulle variabili
 */
int bish_set(int argc, char **argv)
{
	// Se non diamo argomenti visualizza tutte le variabili
	if(argc == 1)
	{
		int x;
		for(x = 0; x < BISH_VAR_NUM; x++)
		{
			if(strcmp(bish_var_list[x].name, "\0") != 0)
				printf("%s=%s\n", bish_var_list[x].name, bish_var_list[x].value);
		}
	}
	
	
	return 0;
}


/**
 * Visualizza tutti i registri
 */
int bish_regdump(int argc, char **argv)
{
	#ifdef X86
		regs_t r = cpu_reg_dump();
		if(strcmp(ARCH, "x86\0") == 0)
		{
			printf("eax: 0x%x", r.eax);
			video_gotoxy(16, video_gety());
			printf("ebx: 0x%x", r.ebx);
			video_gotoxy(32, video_gety());
			printf("ecx: 0x%x", r.ecx);
			video_gotoxy(48, video_gety());
			printf("edx: 0x%x\n", r.edx);
			printf("edi: 0x%x", r.edi);
			video_gotoxy(16, video_gety());
			printf("esi: 0x%x", r.esi);
			video_gotoxy(32, video_gety());
			printf("ebp: 0x%x", r.ebp);
			video_gotoxy(48, video_gety());
			printf("esp: 0x%x\n", r.esp);
			printf("ds: 0x%x", r.ds);
			video_gotoxy(16, video_gety());
			printf("es: 0x%x", r.es);
			video_gotoxy(32, video_gety());
			printf("fs: 0x%x", r.fs);
			video_gotoxy(48, video_gety());
			printf("gs: 0x%x\n", r.gs);
			printf("eip: 0x%x", r.eip);
			video_gotoxy(16, video_gety());
			printf("cs: 0x%x", r.cs);
			video_gotoxy(32, video_gety());
			printf("eflags: 0x%x", r.eflags);
			video_gotoxy(48, video_gety());
			printf("uesp: 0x%x\n", r.user_esp);
			//video_gotoxy(, video_gety());
			printf("uss: 0x%x\n", r.user_ss);
		}
	#endif
}


/**
 * Cancella una variabile
 */
int bish_unset(int argc, char **argv)
{
	if(argc == 2)
	{
		int x;
		for(x = 0; x < BISH_VAR_NUM; x++)
		{
			if(strcmp(bish_var_list[x].name, argv[1]) == 0)
			{
				strcpy(bish_var_list[x].name, "\0");
				strcpy(bish_var_list[x].value, "\0");
				
				return 0;
			}
		}
		
		printf("variable %s not found\n", argv[1]);
		return 1;
	}
	return 0;
}




/**
 * Visualizza le info del system
 */
int bish_sysinfo(int argc, char **argv)
{
	sysinfo_t k;
	syscall_info_get(&k);
	printf("%s %s %s (%s %s) %s (%s)\n", k.name, k.ver, k.rev, k.date, k.time, k.vend, k.arch);
	
	return 0;
}




/**
 * Visualizza le info del system
 */
int bish_devlist(int argc, char **argv)
{
	int i = 0;
	device_t *dev = device_list;
	
	//if(dev == NULL) device_update();
	//dev = device_list;
	
	while(dev != NULL)
	{
		if(device_iget(i, &dev) == 0)
		{
			//if(strcmp(dev->class, "\0") != 0)
			if(dev->bus_type == DEVICE_BUS_TYPE_PCI)
				printf("0%x:0%x.%x - %s (%s)\n", ((pci_device_t *) (dev->pci_dev))->bus, 
										((pci_device_t *) (dev->pci_dev))->device, 
										((pci_device_t *) (dev->pci_dev))->function, 
										dev->class, dev->class_desc);
		}
		i++;		
	}
	
	return 0;
}





/**
 * Visualizza tutti i file del fs
 */
int bish_tree(int argc, char **argv)
{
	fs_show_tree(fs_root, 0);
	
	return 0;
}




/**
 * Visualizza le info del system
 */
int bish_driver(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("use:\n\tdriver -l\n");
		printf("\tdriver -i drivername\n");
		printf("\tdriver -f drivername\n");
		printf("\tdriver -h drivername\n");
		return 0;
	}
	
	if(strcmp(argv[1], "-i") == 0)
	{
		driver_initd(argv[2]);
	}
	else if(strcmp(argv[1], "-f") == 0)
	{
		driver_freed(argv[2]);
	}
	else if(strcmp(argv[1], "-l") == 0)
	{
		driver_t *d = driver_list;

		while(d != NULL)
		{
			if(d->type == DRV_TYPE_FS)
			{
				d = d->next;
				continue;
			}
			if(d->loaded == 1) printf("[*] %s (%s)\n", d->name, d->desc);
			else printf("[ ] %s (%s)\n", d->name, d->desc);
			d = d->next;
		}
	}
	else if(strcmp(argv[1], "-h") == 0)
	{
		driver_t *d = driver_get(argv[2]);
		
		if(d != NULL)
		{			
			printf("%s (%s) made by '%s' (type: ", d->name, d->desc, d->author);
			
			switch(d->type)
			{
				case DRV_TYPE_SYSTEM:
					printf("system");
					break;
					
				case DRV_TYPE_BLOCK:
					printf("block device");
					break;
					
				case DRV_TYPE_CHAR:
					printf("char device");
					break;
					
				case DRV_TYPE_CRYPTO:
					printf("crypto");
					break;
					
				case DRV_TYPE_FS:
					printf("filesystem");
					break;
					
				case DRV_TYPE_NET:
					printf("network");
					break;
					
				case DRV_TYPE_VIDEO:
					printf("video");
					break;					
			}
			
			printf(", loaded: %d)\n", d->loaded);
		}
		else 
			printf("driver %s not found\n", argv[1]);
	}
	
	return 0;
}



/**
 * Snake
 */
int bish_snake(int argc, char **argv)
{
	uint32_t dir = 4;		// Direzione corrente del verme
	uint32_t points = 1;	// Punti totalizzati
	uint32_t sleep = 1000000;		// Tempo di attesa per il rendering
	uint32_t over = 0;		// Game over
	uint32_t level = 4;		// Livello raggiunto
	char grid[VIDEO_MAX_Y][VIDEO_MAX_X];		// Griglia  di gioco
	char d;
	int i,j;
	uint32_t ax = 16;
	uint32_t ay = 17;
	uint8_t worm[100][2];
	
	worm[0][0] = 10;
	worm[0][1] = 10;
	worm[1][0] = 9;
	worm[1][1] = 10;
	worm[2][0] = 8;
	worm[2][1] = 10;
	
	
	for(i = 1; i < VIDEO_MAX_Y-1; i++)
	{
		for(j = 1; j < VIDEO_MAX_X-1; j++)
		{
			grid[i][j] = 0;
		}
	}
	grid[ax][ay] = 3;		
	
	while(!over)
	{
		video_clear();
		printf("Points: %d\t\tLevel: %d\t\tDirection: %d\t\tNext: (%d/%d)\n", points-1, level, dir, ax, ay);

		// Collisione
		if(worm[0][0] == 0 || worm[0][0] == VIDEO_MAX_Y || worm[0][1] == 0 || worm[0][1] == VIDEO_MAX_X)
			over = 1;
		
		if(grid[worm[0][0]][worm[0][1]] == 3)
		{
			points++;
			ax = arch_get_tick();
			ay = arch_get_tick();
			grid[ax][ay] = 3;
		}			
		
		for(i = 1; i < VIDEO_MAX_Y-1; i++)
		{
			printf(" |");
			for(j = 1; j < VIDEO_MAX_X-3; j++)
			{
				switch(grid[i][j])
				{
					case 3:
						printf("o");
						break;
					case 0:
						printf(" ");
						break;
				}
			}
			printf("|\n");
		}
		
		
		// Visualizza il verme
		video_gotoxy(worm[0][0],worm[0][1]);
		switch(dir)
		{
			case 4:
				printf(">");
				break;
			case 3:
				printf("<");
				break;
			case 1:
				printf("^");
				break;
			case 2:
				printf("v");
				break;
		}
		for(i = 1; i < level; i++)
		{
			video_gotoxy(worm[i][0],worm[i][1]);
			printf("0");
		}
		
		//while(1);
						


		// Aggiorna il verme
		for(i = level; i > 1; i--)
		{
			worm[i][0] = worm[i-1][0];
			worm[i][1] = worm[i-1][1];
		}
		
		switch(dir)
		{
			case 1:
				worm[0][1]--;
				break;
			case 2:
				worm[0][1]++;
				break;
			case 3:
				worm[0][0]--;
				break;
			case 4:
				worm[0][0]++;
				break;
		};

		
		// Input utente
		d = getch();
		switch(d)
		{
			case 'w':
				dir = 1;
				break;
			case 's':
				dir = 2;
				break;
			case 'a':
				dir = 3;
				break;
			case 'd':
				dir = 4;
				break;
			default:
				break;
		};
		
		for(i = 0; i < sleep; i++) arch_sleep(1);
	}
	
	video_clear();
	printf("Game over! You reached %d points.\n", points - 1);
	return 0;
}






#ifdef NETWORK


/**
 * Irc client
 */
int bish_irc(int argc, char **argv)
{
	if(argc < 3)
	{
		printf("use:\n\tirc server port nick\n");
		return 0;
	}
	
	// Indirizzo del server e del client
	//struct sockaddr_in server_addr; 
	//struct sockaddr_in client_addr;
	int error;
	int sd;
	char buf[1024];

	// Inizializza porta e indirizzo del server
	//server_addr.sin_family = AF_INET;
	//server_addr.sin_port = htons((u_short) atoi(argv[2]));
	//server_addr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)gethostbyname(argv[1])->h_addr)); 

	// Inizializza il socket tcp
	//sd = socket(AF_INET,SOCK_STREAM,0);

	// Connette al server	
	//error = connect(sd,(struct sockaddr*) &server_addr, sizeof(server_addr)); 
	if(error)
	{
		printf("cannot connect.\n");
		return 0;
	}
	
	// Invia il nick
	strcpy(buf, "nick ");
	strcat(buf, argv[3]);
	strcat(buf, "\n");
	//send(sd, buf, strlen(buf), 0);

	// Identifica l'user
	strcpy(buf, "user ");
	strcat(buf, argv[3]);
	strcat(buf, " 127.0.0.1 ");
	strcat(buf, argv[3]);
	strcat(buf, "@localhost ");
	strcat(buf, argv[3]);
	strcat(buf, "\n");
	//send(sd, buf, strlen(buf), 0);

	
	while(1)
	{
		//recv(sd, &buf, 1024, 0);
		printf("%s\n", buf);
		scanf("%s", buf);
		
		if(strcmp(buf, "/exit") == 0)
		{
			return 0;
		}
		strcat(buf, "\n");
		//send(sd, buf, strlen(buf), 0);
	}	
		
	return 0;
}




/**
 * Ping
 */
int bish_ping(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("use: ping ip\n");
		return 0;
	}
	
	uint32_t wc;
	
	for(wc = 0; wc < 5; wc++)
	{
		// Crea pacchetto
		packet_t *p = packet_create(NULL, sizeof(icmp_header_t));
		
		// Crea socket raw
		//int sd = socket(SOCK_DOMAIN_AF_INET, SOCK_TYPE_SOCK_RAW, 0);
		
		// Invia pacchetto tramite protocollo ip
		//ip_send_frame(0, p, 0, 0);
		
		// Attendi risposta
		
	}
	
	return 0;
}


/**
 * Route config
 */
int bish_route(int argc, char **argv)
{
	// List all routes
	if(argc == 1)
	{
		route_entry_t *route;
		unsigned i = 0;

		printf("Kernel IP routing table\n");
		printf("Destination     Gateway         Genmask         Interface\n");

		while(route_iget(i, &route))
		{
			char adr[20];
			printf("%s", network_addrtoa(route->dest, adr));
			video_gotoxy(16, video_gety());
			printf("%s", network_addrtoa(route->gw, adr));
			video_gotoxy(32, video_gety());
			printf("%s", network_addrtoa(route->genmask, adr));
			video_gotoxy(48, video_gety());
			printf("%s", (route->iface)->name);
			i++;
			printf("\n");
		}		
	}	
}

/**
 * Network config
 */
int bish_netconf(int argc, char **argv)
{
	network_iface_t *nt;
	uint32_t i = 0;
	
	while(network_iface_iget(i, &nt) != 1)
	{
		if(nt->if_up == 1)
		{
			char adr[15];
			printf("%s ", nt->name);
			
			/*if(!nt->if_up)
				printf("(up) ");
			else
				printf("(down) ");
			*/
			video_gotoxy(13, video_gety());
			printf("link type: ");
			switch(nt->type)
			{
				case NET_LINK_TYPE_ETH:
					printf("ethernet\n");
					break;
				case NET_LINK_TYPE_PPP:
					printf("point to point\n");
					break;
				case NET_LINK_TYPE_LO:
					printf("loopback\n");
					break;
				case NET_LINK_TYPE_PPPOA:
					printf("point to point over atm\n");
					break;
				case NET_LINK_TYPE_PPPOE:
					printf("point to point over ethernet\n");
					break;
			};

			video_gotoxy(13, video_gety());				
			printf("addr: %s", network_addrtoa(nt->addr, adr));
			video_gotoxy(39, video_gety());		
			printf("mask: %s\n", network_addrtoa(nt->mask, adr));
			video_gotoxy(13, video_gety());
			printf("tx bytes: %d", nt->tx_bytes);
			video_gotoxy(39, video_gety());		
			printf("rx bytes: %d\n", nt->rx_bytes);
			video_gotoxy(13, video_gety());
			printf("broadcast: %s\n\n", network_addrtoa(nt->bcast, adr));
		}
		i++;
	}
}

#endif






/**
 * Mount
 */
int bish_mount(int argc, char **argv)
{
	if(argc < 2)
	{
		help:
			printf("use:\n\tmount -m filesystem /dev/hd0 /mnt/dreamos\n");
			printf("\tmount -u /dev/hd0   or   mount -u /mnt/dreamos\n");
			printf("\tmount -l\n");
			return 0;
	}
	//printf("%s\n%s\n%s\n%s\n", argv[0], argv[1], argv[2], argv[3]);
	
	if(strcmp(argv[1], "-l") == 0)
	{
		mount_point_t *mp;
		uint32_t i = 0;
		
		//printf("mounted fs\n");
		while(fs_iget_mount_point(i, &mp) != 1)
		{
			if(mp->root->name[0] != '\0')
				printf("%s",mp->path);
			else
				printf("/");
			video_gotoxy(34, video_gety());
			printf("%s\n",mp->fs);
			i++;
		}	
	}
	
	else if(strcmp(argv[1], "-u") == 0)
	{
		switch(fs_umount(argv[2]))
		{
			case MOUNT_STATE_MP:
				printf("missing path %s\n", argv[2]);
				break;
		};
	}
	
	else if(strcmp(argv[1], "-m") == 0)
	{
		switch(fs_mount(argv[3], argv[4], argv[2], 0))
		{
			case MOUNT_STATE_MD:
				printf("missing device %s\n", argv[3]);
				break;
				
			case MOUNT_STATE_MF:
				printf("missing filesystem %s\n", argv[2]);
				break;
				
			case MOUNT_STATE_MP:
				printf("missing path %s\n", argv[4]);
				break;
				
			case MOUNT_STATE_PM:
				printf("path %s already mounted\n", argv[4]);
				break;
				
			case MOUNT_STATE_DM:
				printf("device %s already mounted\n", argv[3]);
				break;
		}
	}
	else
		goto help;
}




/**
 * RPN Calc
 */
int bish_rpncalc(int argc, char **argv)
{
	int i;
	int value = atoi(argv[1]);
	int n = 0;
	
	for(i = 2; i < argc; i++)
	{
		if(n == 1)
		{
			n = 0;
			switch(argv[i][0])
			{
				case '-':
					//printf("%d - %d\n", value, atoi(argv[i-1]));
					value = value - atoi(argv[i-1]);
					break;
					
				case '+':
					//printf("%d + %d\n", value, atoi(argv[i-1]));
					value = value + atoi(argv[i-1]);
					break;
					
				case '/':
					//printf("%d / %d\n", value, atoi(argv[i-1]));
					value = value / atoi(argv[i-1]);
					break;
					
				case '*':
					//printf("%d * %d\n", value, atoi(argv[i-1]));
					value = value * atoi(argv[i-1]);
					break;
			}
		}
		else
			n++;
	}
	
	printf("%d\n", value);
}
