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
 * \file kernel/log.c
 * \author Davide Gessa
 * \date 18-02-10
 */
#include <log.h>
#include <config.h>
#include <types.h>
#include <fs/fs.h>
#include <fs/file.h>
#include <fs/dir.h>

file_t *log_file = NULL;

/**
 * Il logging e' attivo?
 */
uint32_t log_stat()
{
	if(log_file != NULL)
		return 1;
	else
		return 0;
}

/**
 * Inizializza il sistema di log
 */
void log_init()
{
	fs_makedir("/log");
	log_file = fs_open(LOG_PATH, "w");
	log_write("log started\n");
}


/**
 * Scrive nel file di log
 */
uint32_t log_write(char *buf)
{
	if(log_file != NULL)
		return fs_write(log_file, buf, strlen(buf));
	return 0;
}
