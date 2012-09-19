#include <avr/io.h>
#include <avr/interrupt.h>

#include "ata6824.h"
#include "led.h"
#include "qe.h"
#include "timer.h"

static uint16_t timer_index=0;
static uint16_t trigger_index=0;

void timer_init(void)
{

	TCCR0A = _BV(WGM01) | _BV(CS02) | _BV(CS00); // CTC,F_CPU/1024
	TIMSK0 = _BV(OCIE0A);
	OCR0A = 0; // 1*64us=64us

}

ISR(TIMER0_COMP_vect)
{
	if(++trigger_index>181)
	{
		//180*64us=11.52ms
		trigger_index=0;
		ATA6824_TRIG_PORT ^= _BV(ATA6824_TRIG_PIO);
	}
	if(++timer_index>15626)
	{
		//15625*64us=1s
		timer_index=0;
		qe_speed = qe_cycles;
		qe_cycles=0;
	}
}
