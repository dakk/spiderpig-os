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
 * \file kernel/include/bish.h
 * \author Davide Gessa
 * \date 10-22-09
 */
#ifndef BISH_H
#define BISH_H

#define BISH_CMD_NUM		48		///< Numero dei commandi
#define BISH_VAR_NUM		128		///< Numero possibile di variabili

/**
 * Struttura per l'implementazione commandi
 */
typedef struct
{
	int (*func)(int argc, char **argv);
	char name[32];
	char desc[512];
} bish_cmd_t;


/**
 * Struttura di una variabile
 */
typedef struct
{
	char name[32];
	char value[512];
} bish_var_t;


bish_var_t bish_var_list[BISH_VAR_NUM];


void bish();
int bish_help(int, char **);
int bish_true(int, char **);
int bish_false(int, char **);
int bish_set(int, char **);
int bish_unset(int, char **);
int bish_memstat(int, char **);
int bish_regdump(int, char **);
int bish_pslist(int, char **);
int bish_shutdown(int, char **);
int bish_devlist(int, char **);
int bish_driver(int, char **);
int bish_sysinfo(int, char **);
int bish_snake(int, char **);
int bish_tree(int, char **);
int bish_netconf(int, char **);
int bish_mount(int, char **);
int bish_rpncalc(int, char **);
int bish_cd(int, char **);
int bish_ls(int, char **);
int bish_mkdir(int, char **);
int bish_clear(int, char **);
int bish_read(int, char **);
int bish_rm(int, char **);
int bish_elf(int, char **);
int bish_route(int, char **);
int bish_write(int, char **);
int bish_modem(int, char **);
int bish_irc(int, char **);
int bish_link(int, char **);
int bish_unlink(int, char **);
int bish_memdump(int, char **);
int bish_cp(int, char **);
int bish_serial(int, char **);
int bish_parse_command(char *);
int bish_ping(int, char **);


#endif

