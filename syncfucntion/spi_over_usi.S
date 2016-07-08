;
; Jellyfish sync.
; Copyright (C) 2014  Albert Farres
;
; This program is free software; you can redistribute it and/or
; modify it under the terms of the GNU General Public License
; as published by the Free Software Foundation; either version 2
; of the License.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program; if not, write to the Free Software
; Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include <avr/io.h>

	.section .text

        .global usi_spi_4x_send_recv
usi_spi_4x_send_recv:
	out  _SFR_IO_ADDR( USIDR ), r24 ; unsigned char parameter
	ldi  r18, _BV( USIOIF )
	out  _SFR_IO_ADDR( USISR ), r18
	ldi  r19, _BV( USIWM0 ) | _BV( USICS1 )| _BV( USICLK )| _BV( USITC )
usi_spi_4x_send_recv_loop:
	out  _SFR_IO_ADDR( USICR ), r19
	in   r18, _SFR_IO_ADDR( USISR )
	sbrs r18, USIOIF
	rjmp usi_spi_4x_send_recv_loop
	in   r24, _SFR_IO_ADDR( USIDR )
	ret 

        .global usi_spi_2x_send_recv
usi_spi_2x_send_recv:
	out  _SFR_IO_ADDR( USIDR ), r24 ; unsigned char parameter
	ldi  r18,_BV( USIWM0 ) | _BV( USICS1 ) | _BV( USICS0 ) | _BV( USITC )
	ldi  r19,_BV( USIWM0 ) | _BV( USICS1 ) | _BV( USICS0 ) | _BV( USITC )| _BV( USICLK )
	out  _SFR_IO_ADDR( USICR ), r18 ; MSB
	out  _SFR_IO_ADDR( USICR ), r19
	out  _SFR_IO_ADDR( USICR ), r18
	out  _SFR_IO_ADDR( USICR ), r19
	out  _SFR_IO_ADDR( USICR ), r18
	out  _SFR_IO_ADDR( USICR ), r19
	out  _SFR_IO_ADDR( USICR ), r18
	out  _SFR_IO_ADDR( USICR ), r19
	out  _SFR_IO_ADDR( USICR ), r18
	out  _SFR_IO_ADDR( USICR ), r19
	out  _SFR_IO_ADDR( USICR ), r18
	out  _SFR_IO_ADDR( USICR ), r19
	out  _SFR_IO_ADDR( USICR ), r18
	out  _SFR_IO_ADDR( USICR ), r19
	out  _SFR_IO_ADDR( USICR ), r18 ; LSB
	out  _SFR_IO_ADDR( USICR ), r19
	in   r24, _SFR_IO_ADDR( USIDR )
	ret

	.end

