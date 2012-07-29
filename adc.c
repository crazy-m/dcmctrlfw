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

#include "adc.h"

static uint16_t adc_read_ch(uint8_t channel);

void adc_init(void)
{
	ADMUX  = _BV(REFS0); // AVCC with external capacitor on AREF pin
	ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0); // prescaler 128
	ADCSRB = 0x00;
	DIDR0 = _BV(ADC2D) | _BV(ADC1D) | _BV(ADC0D);

	ADC0_DDR &= ~_BV(ADC0_PIO);
	ADC1_DDR &= ~_BV(ADC1_PIO);
	//ADC2_DDR &= ~_BV(ADC2_PIO);

	ADC0_PORT &= ~_BV(ADC0_PIO);
	ADC1_PORT &= ~_BV(ADC1_PIO);
	//ADC2_PORT &= ~_BV(ADC2_PIO);

}

float adc_read_vbat(void)
{
	return ( (float)(adc_read_ch(0))*(24.0/1024.0)+0.9 ); //+0.9 error correction
}

float adc_read_current(void)
{
	return ( (float)(adc_read_ch(1))*(30.24/1024.0)+0.0642 ); //+0.0642 error correction
}

static uint16_t adc_read_ch(uint8_t channel)
{
	ADMUX  &= 0xe0;
	ADMUX  |= (channel&0x07);
	ADCSRA |= _BV(ADSC);
	loop_until_bit_is_set(ADCSRA, ADIF);
	return ADC;
}
