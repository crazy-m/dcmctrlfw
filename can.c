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

static void can_mob_clear_all(void);
static uint8_t can_mob_get_free(void);
static uint8_t can_mob_get_status(void);
static void can_mob_get_data(uint8_t* p_can_message_data);
static uint8_t can_baudrate_fixed(void);

void can_init(void)
{
	CAN_DDR |= _BV(CAN_PIO_TX);
	CAN_DDR &= ~_BV(CAN_PIO_RX);

	CAN_PORT &= ~_BV(CAN_PIO_TX) & ~_BV(CAN_PIO_RX);

	can_baudrate_fixed();
	can_mob_clear_all();
	can_enable();

}

static void can_mob_clear_all(void)
{
	uint8_t mob_num;

	for(mob_num = 0; mob_num < CAN_MOB_NUM; mob_num++)
	{
		CANPAGE  = (mob_num<<4);
		// can_clear_mob
		CANSTMOB = 0x00;
		CANCDMOB = 0x00;
		CANIDT4  = 0X00;
		CANIDT3  = 0x00;
		CANIDT2  = 0x00;
		CANIDT1  = 0x00;
		CANIDM4  = 0x00;
		CANIDM3  = 0x00;
		CANIDM2  = 0x00;
		CANIDM1  = 0x00;
	}

}

static uint8_t can_mob_get_free(void)
{
	uint8_t mob_num, page_saved;

	page_saved = CANPAGE;
	for (mob_num = 0; mob_num < CAN_MOB_NUM; mob_num++)
	{
		CANPAGE = mob_num << 4;
		if ((CANCDMOB & 0xc0) == 0x00) //! Disable configuration
		{
			CANPAGE = page_saved;
			return (mob_num);
		}
	}
	CANPAGE = page_saved;
	return (CAN_NO_MOB);
}

static uint8_t can_mob_get_status(void)
{
	uint8_t mob_status;

	if ((CANCDMOB & 0xc0) == 0x00) return CAN_MOB_DISABLE;

	mob_status = CANSTMOB & ( _BV(DLCW) | _BV(TXOK) | _BV(RXOK) );

	if ((mob_status==CAN_MOB_RX_COMPLETED)  || \
		(mob_status==CAN_MOB_TX_COMPLETED)  || \
		(mob_status==CAN_MOB_RX_COMPLETED_DLCW)) return mob_status;

	mob_status = CANSTMOB & CAN_MOB_ERR_MSK;

	if (mob_status != 0) return mob_status;

	return CAN_MOB_NOT_COMPLETED;
}

static void can_mob_get_data(uint8_t* p_can_message_data)
{
	uint8_t data_index;

	for (data_index = 0; data_index < (can_get_dlc()); data_index++)
	{
		*(p_can_message_data + data_index) = CANMSG;
	}
}

static uint8_t can_baudrate_fixed(void)
{
	CANGCON  =  _BV(SWRES); //can_reset();
	can_baudrate();
	return 1;
}

