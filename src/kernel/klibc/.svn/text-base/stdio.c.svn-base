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
 * \file kernel/klibc/stdio.c
 * \author Davide Gessa
 * \note Standard input output
 * \date 10-12-09
 */
#include <klibc/stdio.h>
#include <klibc/stdarg.h>
#include <klibc/string.h>
#include <video.h>
#include <config.h>

/**
 *  Scrive un carattere sullo schermo
 */ 
void putchar(char ch)
{
	video_putchar(ch);
}


/**
 *  Scrive una stringa su schermo
 */
void puts(char *str)
{
	while(*str != '\0')
	{
		putchar(*str);
		str++;
	}
}



/**
 *  Converte un int in un char*
 */
char *itoa(int num)
{
	static char buff[10];
	char *str = buff + 9;
	int j = num;
	*str-- = 0;

	// Divide per 10 e mette il resto nella stringa, finche' non finisce il numero
	do 
		*str-- = num % 10 + '0';  
	while ((num = num / 10));

	// Se il numero e' negativo, mette il -
	if(j < 0)
		*str-- = '-';

	// Restituisce il puntatore
	return ++str;
}




/**
 *  Converte un int in un hex char*
 */
char *itox(int num)
{
	static char buff[10];
	char *str = buff + 9;
	int j = num;
	*str-- = 0;


	// Divide per 16 e mette il resto nella stringa, finche' non finisce il numero
	do 
	{
		unsigned n = num % 16;
		char x;
		
		if(n <= 9) 
			x = n + '0';
		else
			x = (n - 9) + 'A' - 1;
		*str-- = x;  
	}
	while ((num = num / 16));


	// Restituisce il puntatore
	return ++str;
}



/**
 *  Converte una stringa in un int
 */
int atoi(const char *str)
{
	int num = 0;
	int pot = 1;

	str += strlen(str)-1;

	while(*str != '\0')
	{
		num += ((int)(*str)-48) * pot;
		pot *= 10;
		str--;		
	}

	return num;
}


/**
 *  Printf
 */
int printf(const char *format, ...)
{
	int len = 0;
	char output[255];
	char *current = &output[0];
	va_list ap;

	va_start(ap, format);

	while(*format != '\0')
	{
		if(*format == '%')
		{
			format++;

			switch (*format)
			{
				// Stampa stringa
				case 's':
					current = va_arg(ap, char *);
					puts(current);
					break;
					
				// Stampa carattere
				case 'c':
					current = va_arg(ap, char *);
					putchar(current[0]);
					break;

				// Stampa hex
				case 'x':
					puts(itox(va_arg(ap, int)));
					break;
					
				// Per stampare decimali
				case 'd':
					puts(itoa(va_arg(ap, int)));
					break;


				// Per stampare il carattere % si scrive "%%"
				case '%':
					putchar('%');
					break;
			}
		}
		else
			putchar(*format);

		format++;
		len++;
	}
	return len;
}



/**
 *  Legge varie variabili
 */
int scanf(const char *format, ...)
{
	int len = 0;
	char buffer[255];
	char *current = &buffer[0];
	int *num;
	va_list ap;

	va_start(ap, format);

	while(*format != '\0')
	{
		if(*format == '%')
		{
			format++;

			switch (*format)
			{
				// Legge stringa stringa
				case 's':
					current = va_arg(ap, char *);
					gets(current);
					break;

				// Legge carattere
				case 'c':
					current = va_arg(ap, char *);
					break;

				// Legge decimale
				case 'd':
					num = va_arg(ap, int *);
					gets(buffer);
					*num = atoi(buffer);
					break;
			}
		}

		format++;
		len++;
	}
	return len;
}




/**
 *  Legge e restituisce un carattere
 */
int getchar()
{
	char c; 
	
	while((c = getch()) == 0);
	
	//video_putchar(c);
	
	return c;
}


/**
 * Legge un carattere istantaneo
 */
int getch()
{	
	#ifdef DKEYBOARD
		return keyboard_getchar();
	#endif
	return 0;
}



/**
 *  Legge una stringa
 */
char *gets(char *string)
{
	int count = 0;
	while(1)
	{
		*string = (char) getchar(); 

		if(*string == '\n') break;
		else if(*string == '\b')
		{
			if(count > 0)
			{
				string--;
				count--;
				video_backspace();
			}
		}
		else
		{
			putchar(*string);
			string++;
			count++;
		}
	}
	putchar('\n');
	*string = '\0';
	return string;
}

