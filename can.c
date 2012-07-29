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

#include "can.h"

void can_init(void)
{
	can_clear_all_mob();
	CANGCON |= _BV(ENASTB); //enable CAN

}

void can_clear_all_mob(void)
{
	uint8_t mob_num;
	volatile uint8_t *i;

	for(mob_num=0;mob_num<MOB_NUM;mob_num++)
	{
		CANPAGE = (mob_num<<4);
		for (i=&CANSTMOB;i<&CANSTML;i++) *i=0x00;
	}
}

uint8_t can_get_mob_free(void)
{
	uint8_t mob_number, page_saved;

	page_saved = CANPAGE;
	for (mob_number = 0; mob_number < MOB_NUM; mob_number++)
	{
		CANPAGE = mob_number << 4;
		if ((CANCDMOB & 0xC0) == 0x00) //! Disable configuration
		{
			CANPAGE = page_saved;
			return (mob_number);
		}
	}
	CANPAGE = page_saved;
	return (NO_MOB);
}
