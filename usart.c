/*
 * dcmctrlfw - DC Motor Control firmware
 * Copyright (C) 2012 Mirza Nakicevic <mirza@linux.org.ba>
 *
 * This file is part of dcmctrlfw.
 *
 * dcmctrlfw is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dcmctrlfw is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dcmctrlfw. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "usart.h"
#include "ata6824.h"

static int usart0_putchar(char c, FILE *stream);
static int usart0_getchar(FILE *stream);

static FILE usart0_stdio = FDEV_SETUP_STREAM(usart0_putchar, usart0_getchar, _FDEV_SETUP_RW);

void usart0_init(void)
{
	UBRR0H  = ((F_CPU / ( 16UL * USART0_BAUDRATE)) - 1)>>8;
	UBRR0L  = ( F_CPU / ( 16UL * USART0_BAUDRATE)) - 1;
	UCSR0B = _BV(TXEN0) | _BV(RXEN0);
	stdout = stdin = stderr = &usart0_stdio;
}

static int usart0_putchar(char c, FILE *stream)
{
	if (c == '\a')
	{
		puts("*ring*\n");
		return 0;
	}

	if (c == '\n') usart0_putchar('\r', stream);

	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;

	return 0;
}

static int usart0_getchar(FILE *stream)
{
	loop_until_bit_is_set(UCSR0A, RXC0);
	if ( bit_is_set(UCSR0A, FE0) )
		return _FDEV_EOF;
	if ( bit_is_set(UCSR0A, DOR0) )
		return _FDEV_ERR;
	return UDR0;
}
