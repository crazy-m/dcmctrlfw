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

#include "qe.h"
#include "led.h"

int16_t qe_position=0;
uint16_t qe_cycles=0;

void qe_init(void)
{
	QE_CH_A_DDR &= ~_BV(QE_CH_A_PIO);
	QE_CH_B_DDR &= ~_BV(QE_CH_B_PIO);
	QE_CH_I_DDR &= ~_BV(QE_CH_I_PIO);

	QE_CH_A_PORT &= ~_BV(QE_CH_A_PIO);
	QE_CH_B_PORT &= ~_BV(QE_CH_B_PIO);
	QE_CH_I_PORT &= ~_BV(QE_CH_I_PIO);

	EICRA = _BV(QE_CH_A_ISC) | _BV(QE_CH_I_ISC);
	EIMSK = _BV(QE_CH_A_INT) | _BV(QE_CH_I_INT);
}

/* QE Ch. A */
ISR(QE_CH_A_VECT)
{
	if ( (QE_CH_A_PIN & _BV(QE_CH_A_PIO))==(QE_CH_B_PIN & _BV(QE_CH_B_PIO)) )
	{
		qe_position++;
	}else{
		qe_position--;
	}
	/*
	if ( bit_is_set(QE_CH_A_PORT, QE_CH_A_PIN) )
	{
		if ( bit_is_clear(QE_CH_A_PORT, QE_CH_B_PIN) )
		{
			qe_position++;
		}else{
			qe_position--;
		}
	}else{
		if ( bit_is_set(QE_CH_A_PORT, QE_CH_B_PIN) )
		{
			qe_position++;
		}else{
			qe_position--;
		}
	}
	*/
}

/* QE Ch. I */
ISR(QE_CH_I_VECT)
{
	qe_cycles++;
}
