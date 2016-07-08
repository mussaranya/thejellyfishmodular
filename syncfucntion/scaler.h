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

#ifndef _SCALER_H
#define _SCALER_H

#ifndef F_CPU
#error "F_CPU not defined"
#endif

#define TIMER_OCR_VALUE( _scaler_, _freq_ )  \
    (F_CPU / (_scaler_ * _freq_))

#define TIMER_SET_OCR_VALUE( _ocr_, _scaler_, _freq_ )  \
  do{ \
    _ocr_ = TIMER_OCR_VALUE( _scaler_, _freq_ ); \
  } while( 0 )

#define TIMER_SET_SCALER_0( _tccr_, _n_ )  \
  do{ \
        _tccr_ &= ~_BV( CS##_n_##2 ) & ~_BV( CS##_n_##1 ) & ~_BV( CS##_n_##0 ); \
  } while( 0 )
#define TIMER_SET_SCALER_1( _tccr_, _n_ )  \
  do{ \
        _tccr_ &= ~_BV( CS##_n_##2 ) & ~_BV( CS##_n_##1 ); \
        _tccr_ |=                                            _BV( CS##_n_##0 ); \
  } while( 0 )
#define TIMER_SET_SCALER_8( _tccr_, _n_ )  \
  do{ \
        _tccr_ &= ~_BV( CS##_n_##2 )                      & ~_BV( CS##_n_##0 ); \
        _tccr_ |=                       _BV( CS##_n_##1 ); \
  } while( 0 )
#define TIMER_SET_SCALER_64( _tccr_, _n_ )  \
  do{ \
        _tccr_ &= ~_BV( CS##_n_##2 ); \
        _tccr_ |=                       _BV( CS##_n_##1 ) |  _BV( CS##_n_##0 ); \
  } while( 0 )
#define TIMER_SET_SCALER_256( _tccr_, _n_ )  \
  do{ \
        _tccr_ &=                                           ~_BV( CS##_n_##0 ); \
        _tccr_ |=  _BV( CS##_n_##2 ) |  _BV( CS##_n_##1 ); \
  } while( 0 )
#define TIMER_SET_SCALER_1024( _tccr_, _n_ )  \
  do{ \
        _tccr_ &=                      ~_BV( CS##_n_##1 ); \
        _tccr_ |=  _BV( CS##_n_##2 )                      |  _BV( CS##_n_##0 ); \
  } while( 0 )

#define PASTER(x,y) x ## _ ## y
#define EVALUATOR(x,y)  PASTER(x,y)
#define TIMER_SET_SCALER(_tccr_, SCALER, _n_) EVALUATOR(TIMER_SET_SCALER, SCALER)( _tccr_, _n_)

#endif /* _SCALER_H */

