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

#ifndef _AC_H_
#define _AC_H_

#define AC_AIN0_DDR DDRE
#define AC_AIN0_PORT PORTE
#define AC_AIN0_PIN PINE
#define AC_AIN0_PIO PE2

#define AC_AIN1_DDR DDRE
#define AC_AIN1_PORT PORTE
#define AC_AIN1_PIN PINE
#define AC_AIN1_PIO PE3

void ac_init(void);

#endif /* _AC_H_ */
