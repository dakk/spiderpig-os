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
 * \file kernel/klibc/string.c
 * \author Davide Gessa
 * \note Operazioni su stringhe
 * \date 10-12-09
 */
#include <klibc/string.h>


/**
 * Copia tutta la stringa dopo gli n bit, in un altra
 */
void strncpy2(char *str1, char *str2, size_t n)
{
	int i = 0;
	
	str2 = str2 + n;
	
	strcpy(str1, str2);
}

/**
 * Lunghezza di una stringa
 * 
 * \param str stringa da analizzare
 * \return lunghezza stringa
 */
size_t strlen(const char *str)
{
	size_t x = 0;

	while(*str++ != '\0') x++;
		
	return x;
}


/**
 * Copia una stringa in un altra
 */
void strcpy(char *str1, char *str2)
{
	while(*str2 != '\0')
	{
		*str1 = *str2;
		str1++; str2++;
	}
	*str1 = '\0';
}

/**
 * Unisce due stringhe
 */
void strcat(char *str1, char *str2)
{
	while(*str1 != '\0') str1++;
	
	while(*str2 != '\0')
	{
		*str1 = *str2;
		str1++;
		str2++;
	}
	*str1 = '\0';
}


/**
 * Confronta la stringa 1 con la stringa 2
 */
int strcmp(const char *s1, const char *s2)
{	
	while(1)
	{
		if(*s1 != *s2) return 1;
		else if(*s1 == '\0' && *s2 == '\0') return 0;
		s1++; 
		s2++;
	}
}



/**
 * Riempie un area di memoria di lunghezza len con il dato data
 */
void *memset(void *s, int c, size_t n)
{
	char *a = s;
	size_t i;
	
	for (i = 0; i < n; i++, a++)
		*a = c;
	
	return s;
}



/**
 * Compara i primi n bit di una stringa con l'altra
 */
int strncmp(const char *s1, const char *s2, size_t dim)
{
	int a = 0;
	
	while(a < dim)
	{
		if(*s1 != *s2) return 1;
		else if(*s1 == '\0' && *s2 == '\0') return 0;
		s1++; 
		s2++;
		a++;
	}	
	return 0;
}




/**
 * Copia un area di memoria a nell'area b
 */
void *memcpy(char *a , const char *b, size_t dim)
{
	uint32_t x = 0;
	
	while(x < dim)
	{
		*a = *b;
		a++; 
		b++;
		x++;
	}
	return (void *) a;
}


/**
 * Muove un area di memoria a nell'area b
 */
void *memmove(void *a, void *b, size_t dim)
{
	
}


/**
 * Confronto tra due aree di memoria
 */
int memcmp(const void *a, const void *b, size_t dim)
{
	
}
