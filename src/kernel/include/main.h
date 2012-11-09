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
 * \file kernel/include/main.h
 * \author Davide Gessa
 * \date 10-12-09
 */

#ifndef MAIN_H
#define MAIN_H

#include <multiboot.h>


#define NAME	"spiderpig"	///< Nome kernel
#define VER		"0.1.9"		///< Versione del kernel
#define REV		"r850"		///< Revisione del kernel


char *mod_addr;				///< Indirizzo modulo
multiboot_info_t *mboot;	///< Multi Boot header

int main(multiboot_info_t *);
void shutdown();
int kinit();

#endif
