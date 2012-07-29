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

#include <avr/io.h>

#include "led.h"

void led_init(void)
{
	LED1_DDR |= _BV(LED1_PIO);
	LED2_DDR |= _BV(LED2_PIO);

	LED1_PORT &= ~_BV(LED1_PIO);
	LED2_PORT &= ~_BV(LED2_PIO);
}

void led_on(uint8_t led)
{
	switch (led)
	{
		case LED1:
			LED1_PORT |= _BV(LED1_PIO);
			break;
		case LED2:
			LED2_PORT |= _BV(LED2_PIO);
			break;
	}
}

void led_off(uint8_t led)
{
	switch (led)
	{
		case LED1:
			LED1_PORT &= ~_BV(LED1_PIO);
			break;
		case LED2:
			LED2_PORT &= ~_BV(LED2_PIO);
			break;
	}
}

void led_toggle(uint8_t led)
{
	switch (led)
	{
		case LED1:
			LED1_PORT ^= _BV(LED1_PIO);
			break;
		case LED2:
			LED2_PORT ^= _BV(LED2_PIO);
			break;
	}
}
