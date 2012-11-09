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
 * \file message.c
 * \author Davide Gessa
 * \date 10-12-09
 */
#include <task/message.h>
#include <task/task.h>
#include <video.h>
#include <debug.h>


/**
 * Cancella tutta la lista dei messaggi
 */
void message_clear()
{
	task_t *t = task_current;
	
	message_t *first;
	message_t *second = t->msg_start;
	
	while(second != NULL)
	{
		first = second->next;
		mm_kfree(second);
		t->msg_num--;
		second = first;
	}
	
	t->msg_end = t->msg_start = NULL;
	t->msg_num = 0;	
}


/**
 * Invia un msg ad un determinato pid
 * 
 * \param to processo di destinazione
 * \param buf messaggio da inviare
 * \param size dimensione del messaggio
 * \return stato dell'operazione
 */
uint32_t message_send(pid_t to, char *buf, uint32_t size)
{
	uint32_t x;
	task_t *t = task_get_from_pid(to);
	
	if(t == NULL) return MESSAGE_STATE_UNKN;
	if(t->msg_num > MESSAGE_MAX) return MESSAGE_STATE_FULL;
	if(size >= MESSAGE_BUFFER_MAX)	return MESSAGE_STATE_HEAVY;
			
	message_t *tm = (message_t *) mm_kalloc(sizeof(message_t));
	
	for(x = 0; x < size && x < MESSAGE_BUFFER_MAX; x++)
		tm->data[x] = buf[x];
	
	tm->pid = task_get_pid();
	tm->size = size;
	tm->next = NULL;
	
	if(t->msg_start == NULL || t->msg_end == NULL)
	{
		t->msg_start = tm;
		t->msg_end = tm;
	}
	else
	{
		t->msg_end->next = tm;
		t->msg_end = tm;
	}
	t->msg_num++;
	
	/*video_puts("Il task ");
	video_putint(task_get_pid());
	video_puts(" ha inviato il messaggio '");
	video_puts(buf);
	video_puts("' di dimensione ");
	video_putint(size);
	video_puts(" dal task ");
	video_putint(to);
	video_puts("\n");*/
	
	return MESSAGE_STATE_OK;
}



/**
 * Riceve il primo msg arrivato non letto
 * 
 * \param data memoria nel quale salvare il messaggio
 * \param pid variabile che verra' riempita col pid del mittente
 * \return dimensione del messaggio
 */
uint32_t message_recv(char *data, pid_t *pid)
{
	task_t *t = task_current;
	
	if(t == NULL) return 0;
	if(t->msg_num < 1) return 0;
	if(t->msg_start == NULL) return 0;
	
	strcpy(data, t->msg_start->data);
	uint32_t size = t->msg_start->size;
	*pid = t->msg_start->pid;
	
	
	/*video_puts("Il task ");
	video_putint(task_get_pid());
	video_puts(" ha ricevuto il messaggio '");
	video_puts(data);
	video_puts("' di dimensione ");
	video_putint(size);
	video_puts(" al task ");
	video_putint(*pid);
	video_puts("\n");*/
	
	
	message_t *msg = t->msg_start->next;
	mm_kfree(t->msg_start);
	t->msg_start = msg;
	if(t->msg_end == NULL) t->msg_end = t->msg_start;
	t->msg_num--;
	
	return size;	
}

