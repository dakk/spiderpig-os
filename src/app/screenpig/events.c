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
 * \file screenpig/events.c
 * \date 01-30-2010
 * \author Davide Gessa
 */
#include "include/events.h"
#include "include/render.h"
#include <types.h>
#include <stdlib.h>




/**
 * Step event
 */
void events_step()
{
	int32_t b = mouse_get_x();
	int32_t a = mouse_get_y();
	
	cur_x = cur_x + b / 50;
	cur_y = cur_y + a / 50;
}
