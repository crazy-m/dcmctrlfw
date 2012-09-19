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
#include <avr/eeprom.h>
#include <avr/fuse.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "ac.h"
#include "adc.h"
#include "ata6824.h"
#include "can.h"
#include "i2c.h"
#include "led.h"
#include "qe.h"
#include "usart.h"

FUSES =
	{
	.low  = (FUSE_CKOUT & FUSE_SUT1),
	.high = (FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_SPIEN & FUSE_JTAGEN & FUSE_OCDEN),
	.extended = (FUSE_BODLEVEL0),
	};

//uint8_t EEMEM fwVer = 1;

/* -U lfuse:w:0x9f:m -U hfuse:w:0x19:m -U efuse:w:0xfd:m */

static void io_init(void);

int main(void)
{
	volatile uint8_t  op1,op2,op3;

	io_init();
	ac_init();
	adc_init();
	ata6824_init();
	can_init();
	i2c_init();
	led_init();
	qe_init();
	usart0_init();

	sei(); // go live :-)

	for(;;)
	{
		scanf("%c%c%c",&op1,&op2,&op3);
		switch(op1)
		{
			case 's':
				switch (op2)
				{
					case 'd':
						if(op3==1 || op3=='1')
						{
							ata6824_set_dir(REVERSE);
						}else{
							ata6824_set_dir(FORWARD);
						}
						break;

					case 'p':
						ata6824_set_pwm( op3 );
						break;

				}
				break;

			case 'g':
				switch(op2)
				{
					case 'v':
						printf("v%ld,%.2f,%.2f\r\n", qe_position, adc_read_vbat(), adc_read_current());
						break;
					case 'p':
						printf("p%d\r\n", ata6824_get_pwm() );
						break;
					case 'd':
						if ( ata6824_get_dir()==FORWARD )
						{
							printf("d0\r\n");
						}else{
							printf("d1\r\n");
						}
						break;
				}
				break;
		}

	}
	return 0;
}

static void io_init(void)
{
	/* set all pins to inputs with P-UP, power save */
	DDRA = 0x00;
	DDRB = 0x00;
	DDRC = 0x00;
	DDRD = 0x00;
	DDRE = 0x00;
	DDRF = 0x00;
	DDRG = 0x00;

	PORTA = 0xff;
	PORTB = 0xff;
	PORTC = 0xff;
	PORTD = 0xff;
	PORTE = 0xff;
	PORTF = 0xff;
	PORTG = 0xff;
}

