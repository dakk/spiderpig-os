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
 * \file term.c
 * \author Davide Gessa
 * \date 10-12-09
 */
#include <task/term.h>
#include <types.h>
#include <video.h>
#include <fs/devfs.h>

/**
 * Alloca un terminale
 * 
 * \param size dimensione del terminale
 * \return struttura terminale
 */
term_t *term_new(size_t size)
{
	term_t *t = (term_t *) mm_kalloc(sizeof(term_t));
	t->data = (char *) mm_kalloc(sizeof(char) * size);
	t->input = (char *) mm_kalloc(sizeof(char) * size);

	strcpy(t->data, "\0");
	t->cursor_pos = 0;
	t->color = VIDEO_HI_WHITE_BLACK;
	
	devfs_find_freen("tty", t->dfile);
	devfs_reg_device(0,0, t->dfile);
}


/**
 * Dealloca un terminale
 * 
 * \param t terminale da deallocare
 */
void term_delete(term_t *t)
{
	devfs_unreg_device(t->dfile);
	
	mm_kfree(t->data);
	mm_kfree(t);
}


/**
 * Imposta un titolo
 * 
 * \param t terminale
 * \param title titolo da impostare al terminale
 */
void term_set_title(term_t *t, char *title)
{
	strcpy(t->name, title);
}
