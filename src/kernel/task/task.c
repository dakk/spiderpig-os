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
 * \file task.c
 * \author Davide Gessa
 * \date 10-12-09
 *
 * \note aggiornare i ms di sleeping di ogni task
 */
#include <task/task.h>
#include <video.h>
#include <debug.h>
#include <task/term.h>
#include <fs/dir.h>
#include <fs/file.h>
#include <task/elf.h>
#include <config.h>



#ifdef TEST
/**
 * Visualizza la lista dei messaggi di un task
 * 
 * \param pid task da analizzare
 */
void show_task_message_list(pid_t pid)
{
	if(task_get_from_pid(pid) == NULL) return;
	
	message_t *msg = task_get_from_pid(pid)->msg_start;
	
	
	video_puts_colored(VIDEO_HI_BLUE_BLACK, "\t-> ");
	video_puts("Msg List of ");
	video_putint(pid);
	video_puts("\n");
		
	while(msg != NULL)
	{
		video_puts_colored(VIDEO_HI_BLUE_BLACK, "\t\t-> ");
		video_puts("Msg: ");
		video_puts(msg->data);
		video_puts("\n");
		
		msg = msg->next;
	}
}

/**
 * Task di prova 1
 */
int task1(int argc, char **argv)
{
	while(1) video_puts("1");
}


/**
 * Task di prova 2
 */
int task2(int argc, char **argv)
{
	while(1) video_puts("2");
}

#endif

/**
 * Metodo round robin
 */
void task_switch_round_robin()
{
	if(task_current != NULL)
	{			
		//video_puts("round: ");
		//video_putint(task_get_pid());
		
		// Salviamo i registri del task corrente

	   
	   task_current->state = TASK_STATE_RUNNABLE;
			
		// Cambiamo task
		do
		{
			task_current = task_current->next;
			
			if(task_current == NULL) 
				task_current = task_list;
		} while(task_current->state != TASK_STATE_RUNNABLE);
		
		task_current->state = TASK_STATE_RUNNING;
		
		// Ripristiniamo i registri del task corrente

			
	}
}


/**
 * Metodo priorita'
 */
void task_switch_priority()
{
}


/**
 * Switcha tra i processi in esecuzione
 * 
 * \param regs registri durante l'interrupt del pit
 */
void task_switch(regs_t *regs)
{	
	// Chiama la funzione selezionata come metodo di switching
	if(task_switch_f != NULL)
	{
		void (*switching)();
		switching = task_switch_f;
		switching();	
	}
}


/**
 * Inizializza il gestore dei task
 * 
 * \param st metodo di switching
 */
void task_init(uint8_t st)
{
	DEBUGP("task_init()\n");
		
	switch(st)
	{
		//case TASK_SWITCH_PRIORITY:
		//	task_switch_f = &task_switch_priority;
		//	break;
		case TASK_SWITCH_ROUND_ROBIN:
			task_switch_f = &task_switch_round_robin;
			break;
			
		default:
			video_puts("Panic!\n");
			while(1);
	}
	
	task_list = NULL;
	task_current = NULL;
	task_cur_pid = 0;
}


/**
 * Restituisce il pid del processo corrente
 * 
 * \return pid del processo corrente
 */
uint32_t task_get_pid(){ return task_current->pid; }



/**
 * Restituisce dato il pid, il puntatore al task
 * 
 * \param pid processo
 * \return struttura del processo
 */
task_t *task_get_from_pid(pid_t pid)
{
	task_t *t = task_list;
	
	while(t != NULL)
	{
		if(t->pid == pid) return t;
		t = t->next;
	}
	return (task_t *) NULL;
}


/**
 * Restituisce il nome del task
 * 
 * \param pid processo
 * \return nome del processo
 */
char *task_get_name(pid_t pid)
{
	task_t *t = task_get_from_pid(pid);
	
	if(t == NULL) return (char *) NULL;
	return t->name;
}


/**
 * Restituisce l'user id del processo
 * 
 * \param pid processo
 * \return uid del processo
 */
uid_t task_get_uid(pid_t pid)
{
	task_t *t = task_get_from_pid(pid);
	
	if(t == NULL) return -1;
	return t->pid;
}


/**
 * Restituisce lo stato del processo
 * 
 * \param pid processo
 * \return stato del processo
 */
uint8_t task_get_state(pid_t pid)
{
	task_t *t = task_get_from_pid(pid);
	
	if(t == NULL) return -1;
	return t->state;
}


/**
 * Mette in pausa il processo
 * 
 * \param pid processo
 */
uint32_t task_pause(pid_t pid)
{
	task_t *t = task_get_from_pid(pid);
	
	if(t != NULL) t->state = TASK_STATE_PAUSE;	
}


/**
 * Ristabilisce il processo
 * 
 * \param pid processo
 */
uint32_t task_resume(pid_t pid)
{
	task_t *t = task_get_from_pid(pid);
	
	if(t != NULL) t->state = TASK_STATE_RUNNABLE;		
}



/**
 * Esegue un task
 * 
 * \param func funzione main del task
 * \param argv argomenti
 * \param argc numero argomenti
 * \return pid del task eseguito
 */
pid_t task_exec(char *path, char **argv, int argc, char **env)
{	
	task_t *taskn;
	void (*v)();	
	char *buf;
	uint32_t point;
	file_t *t;
	
	// Leggiamo l'intero file
	point = 0; 
	t = fs_open(path, "r");
	
	if(t != NULL)
	{
		// Troviamo la grandezza
		char ch[3];
		while(fs_read(t, ch, 1) != 0)
			point++;
			
		// Leggiamolo
		buf = (char *) malloc(point); 
		fs_seek(t, 0, 0);
		fs_read(t, buf, point);

	}
	else
		return 0;
	
	
	// Controlliamo se e' un file di qualche tipo binario supportato
	v = NULL;
	
	///savecr3			
	#ifdef EELF
		if(!elf_check(buf))
		{
			//printf("this file is not an elf file\n");
			return 0;
		}
			
		elf_header_t *header = (elf_header_t *) buf;
			
		v = (void *) ((uint32_t) buf + (uint32_t) header->phoff);
	#endif
	if(v == NULL)
		return 0;
		
	
	// Alloca il task
	taskn = task_create();
	taskn->uid = 1;
	strcpy(taskn->name, argv[0]);		

	// Avvia il task
	v();
	while(1);
	printf("end\n");
	///loadcr3
while(1);
	return taskn->pid;
}


/**
 * Uccide un processo
 * 
 * \param pid processo
 */
uint32_t task_kill(pid_t pid)
{

}


/**
 * Crea un task, lo mette in coda
 * 
 * \return task creato
 */
task_t *task_create()
{
	task_t *taskn;
	
	if(task_num >= TASK_MAX_NUM)
		return (task_t *) NULL;	
		
	// Disattiva gli interrupt, altrimenti potrebbe capitare un altro task switch
	// durante le operazioni di inizializzazione. (Non dovrebbero servire perche' le syscall
	// bloccano gia' gli interrupt, ma lo tengo per i test kernel level)
	// TODO sostituire con le funzioni globali per l'architettura generica 
	asm("cli");
	
	// Alloca il task
	taskn = (task_t *) mm_kalloc(sizeof(task_t)*10);
	if(taskn == NULL) return (task_t *) NULL;
	
	// Assegna il pid
	task_cur_pid++;
	taskn->pid = task_cur_pid;
	taskn->state = TASK_STATE_RUNNABLE;
	task_num++;

	// Azzeriamo il tempo d'attesa
	taskn->ms_sleep = 0;
	
	// Azzera la queue dei messaggi
	taskn->msg_end = taskn->msg_start = NULL;
	taskn->msg_num = 0;
	
	// Aggiunge all'inizio
	taskn->next = task_list;
	task_list = taskn;
	
	// Alloca un terminale
	taskn->term = term_new(TERM_STD_SIZE);
	
	// Se e' l'unico task, lo mette in esecuzione
	if(task_current == NULL) task_current = task_list;
	
	asm("sti");
	
	return (task_t *) taskn;
}


/**
 * Fa attendere al programma tot ms
 */
void task_sleep_ms(uint32_t tts)
{
	task_current->ms_sleep = tts;
}
