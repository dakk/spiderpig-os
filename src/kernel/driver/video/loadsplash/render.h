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
 * \file screenpig/render.h
 * \date 01-21-2010
 * \author Davide Gessa
 */
#ifndef LOADSPLASH_RENDER_H
#define LOADSPLASH_RENDER_H

#include <types.h>


uint32_t res_x;
uint32_t res_y;

/**
 * Struttura di un immagine esportata con gimp
 */
typedef struct
{
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 3:RGB, 4:RGBA */ 
  unsigned char	 *pixel_data; //[64 * 64 * 4 + 1];
} gimp_image;


uint32_t render_x0;
uint32_t render_x1;
uint32_t render_y0;
uint32_t render_y1;

char render_buffer[800*600*4];
char cursor[13*15*4];
char cursor_graphic;

void render_swap_buffer(char *, char *, uint32_t);
void render_draw_pixel(uint32_t, uint32_t, uint32_t);
uint32_t render_get_pixel(uint32_t, uint32_t);
void render_write_text(uint8_t, char *, uint32_t, uint32_t, uint32_t);
void render_write_letter(uint8_t, char, uint32_t, uint32_t, uint32_t);
void render_draw_rect(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
void render_draw_rect_fill(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
void render_draw_rect_fill_gradient(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
void render_draw_rect_bordered(uint32_t, uint32_t, uint32_t, uint32_t, uint8_t, uint32_t, uint32_t);
void render_draw_rect_bordered_gradient(uint32_t, uint32_t, uint32_t, uint32_t, uint8_t, uint32_t, uint32_t, uint32_t);
void render_draw_line(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
void render_bit_map(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t);
void render_gimp_image(gimp_image *, uint32_t, uint32_t);
void render_draw_cursor(uint32_t, uint32_t);
uint32_t load_raw_bitmap(char *, char *, uint32_t, uint32_t);

#endif
