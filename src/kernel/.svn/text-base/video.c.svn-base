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
 * \file kernel/video.c
 * \author Davide Gessa
 * \date 10-12-09
 */
#include <video.h>
#include <klibc/stdio.h>

uint8_t video_x = 0;		///< Cursore x
uint8_t video_y = 0;		///< Cursore y


/**
 * Restituisce il valore di y
 */
uint8_t video_gety()
{
	return video_y;
}



/**
 * Restituisce il valore di x
 */
uint8_t video_getx()
{
	return video_x;
}


/**
 * Visualizza un carattere nello schermo
 * 
 * \param ch carattere da stampare
 */
void video_putchar(uint8_t ch)
{
	char *vidmem = (char *) VIDEO_MEM;
	unsigned int i = 0;
	int x;

	// Calcola la posizione nel buffer video
	i = (video_y * VIDEO_MAX_X * 2) + (video_x * 2);
	
	// Esaminiamo il carattere
	switch(ch)
	{
		// A capo
		case '\n':
			video_y++;
			video_x = 0;
			break;
			
		case '\b':
			if(video_x == 0)
			{
				video_x = VIDEO_MAX_X-1;
				video_y = video_gety()-1;
			}
			video_x--;
			vidmem[i-2] = ' ';
			vidmem[i-1] = video_std_color;
			break;
		
		// Tab
		case '\t':
			for(x = 0; x < VIDEO_TAB_DIM; x++)
				video_putchar(' ');
			break;

		// Carattere normale
		default:
			vidmem[i] = ch;
			i++;
			vidmem[i] = video_std_color;
			video_x++;
			break;
	}


	// Controlla se le posizioni x e y hanno superato i limiti
	if(video_y >= VIDEO_MAX_Y)
		video_scroll_dw();
		
	if(video_x >= VIDEO_MAX_X)
	{
		video_y++;
		video_x = 0;
	}
	
	video_move_cursor(video_x, video_y);
}


/**
 * Cancella il carattere precedente al corrente
 */
void video_backspace()
{
	char *vidmem = (char *) VIDEO_MEM;
	unsigned int i = 0;
	int x;

	// Calcola la posizione nel buffer video
	i = (video_y * VIDEO_MAX_X * 2) + (video_x * 2);
	
	if(video_x == 0)
		{
				video_x = VIDEO_MAX_X-1;
				video_y = video_gety()-1;
			}
			video_x--;
			vidmem[i-2] = ' ';
			vidmem[i-1] = video_std_color;	
}





/**
 * Fa lo scroll di una posizione nello schermo
 */
void video_scroll_dw()
{
	char *vidmem = (char *) VIDEO_MEM;
	
	unsigned int x;
	unsigned int y;
	unsigned int i;
	unsigned int j;
	
	
	for(x = 0; x < VIDEO_MAX_X; x++)
	{
		for(y = 0; y <= VIDEO_MAX_Y; y++)
		{
			i = (y * VIDEO_MAX_X * 2) + (x * 2);
			j = ((y+1) * VIDEO_MAX_X * 2) + (x * 2);
			vidmem[i] = vidmem[j];
			i++; j++;
			vidmem[i] = vidmem[j];
 		}
	}
	
	video_y--;		
}


/**
 * Visualizza un int nello schermo
 * 
 * \param num intero da visualizzare
 */
void video_putint(int num)
{
	video_puts(itoa(num));
}



/**
 * Mostra una stringa su schermo
 * 
 * \param str stringa da visualizzare
 */
void video_puts(uint8_t *str)
{
	while(*str != '\0')
	{
		video_putchar(*str);
		str++;
	}	
}



/**
 * Muove il printing nella data posizione
 * 
 * \param x posizione asse x
 * \param y posizione asse y
 */
void video_gotoxy(uint8_t x, uint8_t y)
{
	video_x = x;
	video_y = y;
	video_move_cursor(video_x, video_y);
}


/**
 * Muove il cursore nella data posizione
 * 
 * \author DreamOS
 * \param x posizione asse x
 * \param y posizione asse y
 */
void video_move_cursor(uint8_t x, uint8_t y)
{
	arch_video_move_cursor(x, y);
}


/**
 * Pulisce lo schermo
 */
void video_clear()
{
	unsigned char *vidmem = (unsigned char *) VIDEO_MEM;
	int i = 0;

	while(i < (VIDEO_MAX_X * VIDEO_MAX_Y * 2))
	{
		vidmem[i] = ' ';
		i++;
		vidmem[i] = video_std_color;
		i++;
	}
	video_gotoxy(0,0);
}



/**
 * Imposta il colore di default
 * 
 * \param cl colore da impostare
 */
void video_set_color(vcolor_t cl)
{
	video_std_color = cl;
}



/**
 * Visualizza una stringa con un determinato colore
 * 
 * \param cl colore da usare
 * \param str stringa da stampare
 */
void video_puts_colored(vcolor_t cl, uint8_t *str)
{
	uint8_t dc = video_std_color;
	video_set_color(cl);
	video_puts(str);
	video_set_color(dc);
}



