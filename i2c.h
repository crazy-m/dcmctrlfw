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

#ifndef _I2C_H_
#define _I2C_H_


#define I2C_BITRATE_kHz 100


#define I2C_SDA_DDR  DDRD
#define I2C_SDA_PORT PORTD
#define I2C_SDA_PIN  PD1

void i2c_init(void);
void i2c_setbitrate(uint8_t bitrate_kHz);
void i2c_sendstart(void);
void i2c_sendstop(void);
void i2c_sendbyte(uint8_t byte);

#endif /* _I2C_H_ */
