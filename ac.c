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
#include <avr/interrupt.h>

#include "ac.h"
#include "ata6824.h"
#include "led.h"

overcurrent_t overcurrent;

void ac_init(void)
{
	AC_AIN0_DDR &= ~_BV(AC_AIN0_PIO);
	AC_AIN1_DDR &= ~_BV(AC_AIN1_PIO);

	AC_AIN0_PORT &= ~_BV(AC_AIN0_PIO);
	AC_AIN1_PORT &= ~_BV(AC_AIN1_PIO);

	ACSR  = _BV(ACIE);
	DIDR1 = _BV(AIN1D) | _BV(AIN0D);
}

ISR(ANALOG_COMP_vect)
{
	if ( bit_is_set(ACSR, ACO) )
	{
		// normal
		TCCR1A |= _BV(COM1A1);
		overcurrent.status = 0;
		led_off(LED2);
	}
	else
	{
		// overcurrent
		//TCCR1A &= ~_BV(COM1A1);
		//ata6824_set_pwm(0);
		overcurrent.occured = 1;
		overcurrent.status = 1;
		led_on(LED2);
	}
}
