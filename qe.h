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

#ifndef _QE_H_
#define _QE_H_

#define QE_CH_A_DDR DDRD
#define QE_CH_A_PORT PORTD
#define QE_CH_A_PIN PIND
#define QE_CH_A_PIO PD2

#define QE_CH_A_INT INT2
#define QE_CH_A_ISC ISC21
#define QE_CH_A_VECT INT2_vect

#define QE_CH_B_DDR DDRD
#define QE_CH_B_PORT PORTD
#define QE_CH_B_PIN PIND
#define QE_CH_B_PIO PD4

#define QE_CH_I_DDR DDRD
#define QE_CH_I_PORT PORTD
#define QE_CH_I_PIN PIND
#define QE_CH_I_PIO PD3

#define QE_CH_I_INT INT3
#define QE_CH_I_ISC ISC31
#define QE_CH_I_VECT INT3_vect

void qe_init(void);

#endif /* _QE_H_ */
