/*
 * Jellyfish sync.
 * Copyright (C) 2014  Albert Farres
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

/*
 * Inputs:
 * - Signal  --> PB4
 *
 * Outputs:
 * - DO      --> SDI - Serial data in to external pot.
 * - SCK     --> CLK - Serial clock
 * - PB3     --> CS  - Chip Select for external pot.
 */

#if !defined( __AVR_ATtiny85__ )
#warning "This code is intended to be built for an attiny85"
#endif

//#include "config.h"

#define F_CPU 1000000UL

#include <avr/interrupt.h>

#include "scaler.h"

#define SIGNAL_PORT PINB
#define SIGNAL_PIN  PB4

#define DDR_SPI  DDRB
#define DD_DO    DDB1
#define DD_DI    DDB0
#define DD_SCK   DDB2
#define DD_POT   DDB3
#define PORT_SPI PORTB
#define P_POT    PB3

#define TIMER_SCALER 1

#define POT_BITRES 8
#define POT_NVAL   (1 << POT_BITRES)

#define WL_MIN  27000UL
#define WL_MAX 570000UL

volatile uint32_t elapsed;

unsigned char usi_spi_4x_send_recv( unsigned char data );
unsigned char usi_spi_2x_send_recv( unsigned char data );

static unsigned char shft8bit(unsigned char val)
{
	USIDR = val;
	USISR = _BV( USIOIF );
	do {
		USICR = _BV( USIWM0 )|_BV( USICS1 )|_BV( USICLK )|_BV( USITC );
	} while( (USISR & _BV( USIOIF )) == 0 );
	return USIDR;
}
#define SPI_MasterSendReceive  shft8bit

static void timers_init( void )
{
	TIMER_SET_SCALER( TCCR1, TIMER_SCALER, 1 );
	TIMSK |= _BV( TOIE1 );
}

ISR( TIMER1_OVF_vect )
{
	elapsed += 1UL<<8 ;
}

static void spi_pot_init( void )
{
	/* Set USI outputs */
	DDR_SPI  |= _BV( DD_SCK ) | _BV( DD_DO ) | _BV( DD_POT );
	PORT_SPI |= _BV( P_POT ); /* Drive CS high */
}

static inline void spi_pot_write( unsigned short value )
{
	/* Memory address bits */
	value &= ~_BV( 15 );
	value &= ~_BV( 14 );
	value &= ~_BV( 13 );
	value &= ~_BV( 12 );
	/* Command bits */
	value &= ~_BV( 11 );
	value &= ~_BV( 10 );

	PORT_SPI &= ~_BV( P_POT ); /* Drive SS low */
	SPI_MasterSendReceive( (unsigned char)(value >> 8) );
	SPI_MasterSendReceive( (unsigned char) value );
	PORT_SPI |= _BV( P_POT );  /* Drive SS high */
}

int main( void )
{
	unsigned short pot_value;
	uint32_t us;

	elapsed = 0;

	timers_init();
	spi_pot_init();

	sei(); /* Enable Global Interrupts */

	TCNT1 = 0; /* Reset timer */
	while( 1 )
	{
		while(   SIGNAL_PORT & _BV( SIGNAL_PIN )  ); /* loop until 0 */
		while( !(SIGNAL_PORT & _BV( SIGNAL_PIN )) ); /* loop until 1 */

		/* Compute elapased time in us */
		us = ((elapsed + TCNT1) * TIMER_SCALER) / (F_CPU/1000000UL);
		TCNT1 = 0;        /* Reset timer */
		elapsed = 0;

		if( us < WL_MIN )     us = WL_MIN;
		else if( us > WL_MAX) us = WL_MAX;

		pot_value = (us - WL_MIN) / ((WL_MAX+1 - WL_MIN) / POT_NVAL);

		spi_pot_write( pot_value );
	}
}
