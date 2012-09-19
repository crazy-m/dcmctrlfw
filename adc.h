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

#ifndef _ADC_H_
#define _ADC_H_

#define ADC0_DDR  DDRF
#define ADC0_PORT PORTF
#define ADC0_PIN  PINF
#define ADC0_PIO  PF0

#define ADC1_DDR  DDRF
#define ADC1_PORT PORTF
#define ADC1_PIN  PINF
#define ADC1_PIO  PF1

#define ADC2_DDR  DDRF
#define ADC2_PORT PORTF
#define ADC2_PIN  PINF
#define ADC2_PIO  PF2

#define ADC_CH_NO 2

extern volatile uint16_t adc_channel[ADC_CH_NO];

void adc_init(void);
float adc_read_vbat(void);
float adc_read_current(void);

#endif /* _ADC_H_ */
