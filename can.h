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

#ifndef _CAN_H_
#define _CAN_H_

#define CAN_DDR		DDRD
#define CAN_PORT	PORTD
#define CAN_PIN		PIND
#define CAN_PIO_TX	PD5
#define CAN_PIO_RX	PD6

#if F_CPU == 16000000UL
	#define CAN_BAUDRATE_100()			{CANBT1=0x12;CANBT2=0x0c;CANBT3=0x37;}
	#define CAN_BAUDRATE_125()			{CANBT1=0x0e;CANBT2=0x0c;CANBT3=0x37;}
	#define CAN_BAUDRATE_200()			{CANBT1=0x08;CANBT2=0x0c;CANBT3=0x37;}
	#define CAN_BAUDRATE_250()			{CANBT1=0x06;CANBT2=0x0c;CANBT3=0x37;}
	#define CAN_BAUDRATE_500()			{CANBT1=0x02;CANBT2=0x0c;CANBT3=0x37;}
	#define CAN_BAUDRATE_1000()			{CANBT1=0x00;CANBT2=0x0c;CANBT3=0x37;}
	#define CAN_BAUDRATE_AUTO()			{CANBT1=0x00;CANBT2=0x00;CANBT3=0x00;}
#endif

#define can_baudrate()					CAN_BAUDRATE_1000()

#define CAN_MOB_NUM						15
#define can_get_dlc()					((CANCDMOB &  CAN_DLC_MSK) >> DLC0)

#define CAN_NO_MOB						0xff
#define CAN_STATUS_CLEARED				0x00
#define CAN_MOB_NOT_COMPLETED			0x00
#define CAN_MOB_TX_COMPLETED			_BV(TXOK)
#define CAN_MOB_RX_COMPLETED			_BV(RXOK)
#define CAN_MOB_RX_COMPLETED_DLCW		( _BV(RXOK) | _BV(DLCW) )
#define CAN_MOB_PENDING					( _BV(RXOK) | _BV(TXOK) )
#define CAN_MOB_DISABLE					0xff
#define CAN_MOB_ERR_MSK					(_BV(BERR)| \
										_BV(SERR) | \
										_BV(CERR) | \
										_BV(FERR) | \
										_BV(AERR))

#define CAN_DLC_MSK						(_BV(DLC3)| \
										_BV(DLC2) | \
										_BV(DLC1) | \
										_BV(DLC0))

#define CONMOB_MSK						( _BV(CONMOB1) | _BV(CONMOB0) )

#define can_reset()						( CANGCON  =  _BV(SWRES) )
#define can_enable()					( CANGCON |=  _BV(ENASTB))
#define can_disable()					( CANGCON &= ~_BV(ENASTB))

#define can_conf_bt()					{ \
										CANBT1=0x00; \
										CANBT2=0x04; \
										CANBT3=0x13; \
										} //1 Mb/s, 8x Tscl, sampling at 75%



#define can_clear_mob()					{ \
										uint8_t volatile *__i_; \
										for (__i_=&CANSTMOB; __i_<&CANSTML; __i_++) *__i_=0x00; \
										}

#define can_get_std_id(identifier)  { *((U8 *)(&(identifier))+1) =  CANIDT1>>5              ; \
                                      *((U8 *)(&(identifier))  ) = (CANIDT2>>5)+(CANIDT1<<3); }
    // ----------
                //!< EXT ID TAG Reading
#define can_get_ext_id(identifier)  { *((U8 *)(&(identifier))+3) =  CANIDT1>>3              ; \
                                      *((U8 *)(&(identifier))+2) = (CANIDT2>>3)+(CANIDT1<<5); \
                                      *((U8 *)(&(identifier))+1) = (CANIDT3>>3)+(CANIDT2<<5); \
                                      *((U8 *)(&(identifier))  ) = (CANIDT4>>3)+(CANIDT3<<5); }

#define CAN_SET_STD_ID_10_4(identifier)  (((*((U8 *)(&(identifier))+1))<<5)+((* (U8 *)(&(identifier)))>>3))
#define CAN_SET_STD_ID_3_0( identifier)  (( * (U8 *)(&(identifier))   )<<5)
    // ----------
                //!< STD ID TAG writing
#define can_set_std_id(identifier)  { CANIDT1   = CAN_SET_STD_ID_10_4(identifier); \
                                      CANIDT2   = CAN_SET_STD_ID_3_0( identifier); \
                                      CANCDMOB &= (~(1<<IDE))                    ; }

typedef enum {
	CMD_NONE,
	CMD_TX,
	CMD_TX_DATA,
	CMD_TX_REMOTE,
	CMD_RX,
	CMD_RX_DATA,
	CMD_RX_REMOTE,
	CMD_RX_MASKED,
	CMD_RX_DATA_MASKED,
	CMD_RX_REMOTE_MASKED,
	CMD_REPLY,
	CMD_REPLY_MASKED,
	CMD_ABORT
} can_cmd_t;

typedef union{
	uint32_t ext;
	uint16_t std;
	uint8_t tab[4];
} can_id_t;

typedef struct{
	uint8_t rtr;
	uint8_t ide;
} can_ctrl_t;

typedef struct{
	uint8_t    handle;
	can_cmd_t  cmd;
	can_id_t   id;
	uint8_t    dlc;
	uint8_t*   pt_data;
	uint8_t    status;
	can_ctrl_t ctrl;
} st_cmd_t;

void can_init(void);

#endif /* _CAN_H_ */
