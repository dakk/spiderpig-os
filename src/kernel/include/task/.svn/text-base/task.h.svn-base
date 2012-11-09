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
 * \file task.h
 * \author Davide Gessa
 * \date 10-12-09
 */
#ifndef TASK_H
#define TASK_H

#define TASK_SWITCH_ROUND_ROBIN		1	///< Flag per lo switch RoundRobin
#define TASK_SWITCH_PRIORITY		2	///< Flag per lo switch a priorita'

#define TASK_STATE_RUNNABLE			0	///< Flag task runnable
#define TASK_STATE_RUNNING			1	///< Flag task running
#define TASK_STATE_PAUSE			2	///< Flag task in pausa
#define TASK_STATE_DEFUNCT			3	///< Flag task defunto

#define TASK_PRIORITY_HG			10	///< Priorita' High
#define TASK_PRIORITY_MD			5	///< Priorita' Middle
#define TASK_PRIORITY_LW			1 	///< Priorita' Low

#define TASK_MAX_NAME				16	///< Dimensione max nome
#define TASK_MAX_NUM				999	///< Massimo num di task

#include <types.h>
#include <task/message.h>
#include <task/term.h>


/**
 * Struttura di un task
 */
typedef struct task_p
{
	char name[TASK_MAX_NAME];			///< Nome del processo
	uint8_t state;						///< Stato del processo
	uint8_t priority;					///< Priorita' del processo
	
	// Registri
	
	
	// Informazioni come la memoria usata dal programma
	//...


	uint32_t ms_sleep;					///< Ms to sleep
   
	// Informazioni per la lista dei messaggi
	uint32_t msg_num;					///< Numero messaggi
	message_t *msg_start;				///< Messaggio inizio
	message_t *msg_end;					///< Messaggio fine
	
	term_t *term;						///< Terminale
	pid_t pid;							///< Id del processo
	uid_t uid;							///< Owner del processo
	
	struct task_p *next;				///< Puntatore al prossimo processo
} task_t;



// Lista circolare di processi
task_t *task_list;
task_t *task_current;
uint32_t task_cur_pid;

// Numero di processi attivi
uint32_t task_num;

uint32_t task_get_pid();
//pid_t task_fork();

task_t *task_get_from_pid(pid_t);

// Funzioni sul processo generico
uint8_t task_get_state(pid_t);
uid_t task_get_uid(pid_t);
char *task_get_name(pid_t);
uint32_t task_kill(pid_t);
uint32_t task_pause(pid_t);
uint32_t task_resume(pid_t);
void task_kill_all();
void task_sleep_ms(uint32_t);
void task_switch_round_robin();
void task_switch_priority();
void task_init(uint8_t);
void (*task_switch_f);
void task_switch(regs_t *);
pid_t task_exec(char *path, char **, int, char **env);
task_t *task_create();


void show_task_message_list(pid_t);
int task1(int, char **);
int task2(int, char **);


#endif
