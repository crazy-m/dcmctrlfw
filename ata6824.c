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

#include <math.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "ata6824.h"

ata6824_diag_mgt_t ata6824_diag_mgt;

void ata6824_init(void)
{
	ATA6824_PWM_DDR  |= _BV(ATA6824_PWM_PIO);
	ATA6824_DIR_DDR  |= _BV(ATA6824_DIR_PIO);
	ATA6824_TRIG_DDR |= _BV(ATA6824_TRIG_PIO);

	ATA6824_PWM_PORT  &= ~_BV(ATA6824_PWM_PIO);
	ATA6824_DIR_PORT  &= ~_BV(ATA6824_DIR_PIO);
	ATA6824_TRIG_PORT |=  _BV(ATA6824_TRIG_PIO);

	EICRB |= _BV(ATA6824_DIAG1_ISC);
	EICRB |= _BV(ATA6824_DIAG2_ISC);
	EICRB |= _BV(ATA6824_DIAG3_ISC);

	EIMSK |= _BV(ATA6824_DIAG1_INT);
	EIMSK |= _BV(ATA6824_DIAG2_INT);
	EIMSK |= _BV(ATA6824_DIAG3_INT);

	TCCR0A = _BV(WGM01) | _BV(CS02) | _BV(CS00); // CTC,F_CPU/1024
	TIMSK0 = _BV(OCIE0A);
	OCR0A = 180; // 180*64us=11.52ms

	TCCR1A = _BV(COM1A1);
	TCCR1B = _BV(WGM13) | _BV(CS10);
	ICR1  = ATA6824_PWM_TOP;
	OCR1A = 0;
}

void ata6824_set_pwm(uint8_t duty)
{
	OCR1A = (uint16_t)( (float)(duty)*ATA6824_PWM_TOP/100.0 );
}

uint8_t ata6824_get_pwm(void)
{
	return (uint8_t)( ceil(((float)(OCR1A)/ATA6824_PWM_TOP) *100.0) );
}

void ata6824_set_dir(uint8_t dir)
{
	switch(dir)
	{
		case FORWARD:
			ATA6824_DIR_PORT &= ~_BV(ATA6824_DIR_PIO);
			break;
		case REVERSE:
			ATA6824_DIR_PORT |= _BV(ATA6824_DIR_PIO);
			break;
		default:
			ata6824_set_pwm(0);
	}
}

uint8_t ata6824_get_dir(void)
{
	return bit_is_set(ATA6824_DIR_PORT, ATA6824_DIR_PIO);
}

/* DIAG1 */
ISR(ATA6824_DIAG1_VECT)
{
	/* DIAG1 */
}

/* DIAG2 */
ISR(ATA6824_DIAG2_VECT)
{
	/* DIAG2 */
}

/* DIAG3 */
ISR(ATA6824_DIAG3_VECT)
{
	/* DIAG3 */
}

ISR(TIMER0_COMP_vect)
{
	ATA6824_TRIG_PORT ^= _BV(ATA6824_TRIG_PIO);
}

