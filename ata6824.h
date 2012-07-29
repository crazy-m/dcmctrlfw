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

#ifndef _ATA6824_H_
#define _ATA6824_H_

#define ATA6824_PWM_DDR  DDRB
#define ATA6824_PWM_PORT PORTB
#define ATA6824_PWM_PIN  PINB
#define ATA6824_PWM_PIO  PB5

#define ATA6824_DIR_DDR  DDRB
#define ATA6824_DIR_PORT PORTB
#define ATA6824_DIR_PIN  PINB
#define ATA6824_DIR_PIO  PB4

#define ATA6824_TRIG_DDR  DDRE
#define ATA6824_TRIG_PORT PORTE
#define ATA6824_TRIG_PIN  PINE
#define ATA6824_TRIG_PIO  PE4

#define ATA6824_DIAG1_DDR  DDRE
#define ATA6824_DIAG1_PORT PORTE
#define ATA6824_DIAG1_PIN  PINE
#define ATA6824_DIAG1_PIO  PE5

#define ATA6824_DIAG1_INT  INT5
#define ATA6824_DIAG1_ISC  ISC51
#define ATA6824_DIAG1_VECT INT5_vect

#define ATA6824_DIAG2_DDR  DDRE
#define ATA6824_DIAG2_PORT PORTE
#define ATA6824_DIAG2_PIN  PINE
#define ATA6824_DIAG2_PIO  PE6

#define ATA6824_DIAG2_INT  INT6
#define ATA6824_DIAG2_ISC  ISC61
#define ATA6824_DIAG2_VECT INT6_vect

#define ATA6824_DIAG3_DDR  DDRE
#define ATA6824_DIAG3_PORT PORTE
#define ATA6824_DIAG3_PIN  PINE
#define ATA6824_DIAG3_PIO  PE7

#define ATA6824_DIAG3_INT  INT7
#define ATA6824_DIAG3_ISC  ISC71
#define ATA6824_DIAG3_VECT INT7_vect

//#define ATA6824_PWM_FREQ 7820UL // TOP=1023
#define ATA6824_PWM_FREQ 20000UL
#define ATA6824_PWM_PRESCALE 1
#define ATA6824_PWM_TOP ( F_CPU/(2*ATA6824_PWM_PRESCALE*ATA6824_PWM_FREQ) )

#define FORWARD 0x00
#define REVERSE 0x01

/*
typedef enum
{
	FORWARD,
	REVERSE,
} ata6824_dir_t;
*/
typedef enum
{
	NO_FAILURE,
	WARNING,
	LATCHED_FAILURE
} ata6824_failure_t;

typedef struct
{
	ata6824_failure_t diag1;
	ata6824_failure_t diag2;
	ata6824_failure_t diag3;
} ata6824_diag_mgt_t;

void ata6824_init(void);
void ata6824_set_pwm(uint8_t pwm);
uint8_t ata6824_get_pwm(void);
void ata6824_set_dir(uint8_t dir);
uint8_t ata6824_get_dir(void);

#endif /* _ATA6824_H_ */
