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
#include <util/twi.h>

#include "i2c.h"

void i2c_init(void)
{
	i2c_setbitrate(I2C_BITRATE_kHz);
	TWCR |= _BV(TWEN);
}

void i2c_setbitrate(uint8_t bitrate_kHz)
{
	uint8_t bitrate_div;

	TWSR &= ~_BV(TWPS1) & ~_BV(TWPS0);
	bitrate_div = ((F_CPU/4000l)/bitrate_kHz);
	if(bitrate_div >= 16)
		bitrate_div = (bitrate_div-16)/2;
	TWBR = bitrate_div;
}

void i2c_sendstart(void)
{
	I2C_SDA_DDR |= _BV(I2C_SDA_PIN);
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTA);
}

void i2c_sendstop(void)
{
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);
}

void i2c_sendbyte(uint8_t byte)
{
	I2C_SDA_DDR |= _BV(I2C_SDA_PIN);
	TWDR = byte;
	TWCR = _BV(TWINT) | _BV(TWEN);
}
