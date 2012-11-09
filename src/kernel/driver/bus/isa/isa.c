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

 * \file kernel/driver/isa/isa.c
 * \author Davide Gessa
 * \date 10-25-09
 */
#include "isa.h"
#include <arch.h>
#include <klibc/ctype.h>
#include <klibc/string.h>
#include <debug.h>
#include <driver.h>


driver_t driver_isa = 
{
	.name = "isa\0",
	.author = "Davide Gessa\0",
	
	.probe = isa_probe
};




/**
 * Probe isa
 */
uint32_t isa_probe()
{
	return 0;
}



