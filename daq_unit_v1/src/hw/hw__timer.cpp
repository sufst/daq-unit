/*************************************************************************//**
* @file hw__timer.cpp
* @brief
* @note
* @author nrs1g15@soton.ac.uk
* @copyright    Copyright (C) 2019  SOUTHAMPTON UNIVERSITY FORMULA STUDENT TEAM

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>
*****************************************************************************/
/*----------------------------------------------------------------------------
  include files
----------------------------------------------------------------------------*/
#include "hw__timer.h"

#include<avr/io.h>
#include<avr/interrupt.h>
/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef struct
{
    hw__timer__handler handlers[HW__TIMER__SUPPORTED_TIMERS];
} hw__timer__obj_t;
/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  global variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/
static hw__timer__obj_t hw__timer__obj;

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Initialises the wanted hardware timer with default prescaler of 64
* @param hw__timer__timer_num_t timer Hardware timer to initialise
* @param uint16_t OCRnA Value of OCRnA to load as the overflow value
* @param hw__timer__handler handler Service layer callback function
* @return None
* @note
*****************************************************************************/
void hw__timer__init(hw__timer__timer_num_t timer, uint16_t OCRnA, hw__timer__handler handler)
{
    noInterrupts();

    switch (timer)
    {
        case HW__TIMER__TIMER_0:
            TCNT0 = 0x00;
            TCCR0A = 0x00;
            TCCR0B = 0x00;

            OCR0A = OCRnA;
            TCCR0B |= (1 << WGM02);
            TCCR0B |= (1 << CS00) | (1 << CS01);
            TIMSK0 |= (1 << OCIE0A);

            hw__timer__obj.handlers[HW__TIMER__TIMER_0] = handler;

            break;
        case HW__TIMER__TIMER_1:
            TCNT1 = 0x00;
            TCCR1A = 0x00;
            TCCR1B = 0x00;

            OCR1A = OCRnA;
            TCCR1B |= (1 << WGM12);
            TCCR1B |= (1 << CS10) | (1 << CS11);
            TIMSK1 |= (1 << OCIE1A);

            hw__timer__obj.handlers[HW__TIMER__TIMER_1] = handler;

            break;
        case HW__TIMER__TIMER_2:
            TCNT2 = 0x00;
            TCCR2A = 0x00;
            TCCR2B = 0x00;

            OCR2A = OCRnA;
            TCCR2B |= (1 << WGM22);
            TCCR2B |= (1 << CS20) | (1 << CS21);
            TIMSK2 |= (1 << OCIE2A);

            hw__timer__obj.handlers[HW__TIMER__TIMER_2] = handler;

            break;
#if defined(__AVR_ATmega2560__)
        case HW__TIMER__TIMER_3:
            TCNT3 = 0x00;
            TCCR3A = 0x00;
            TCCR3B = 0x00;

            OCR3A = OCRnA;
            TCCR3B |= (1 << WGM32);
            TCCR3B |= (1 << CS30) | (1 << CS31);
            TIMSK3 |= (1 << OCIE3A);

            hw__timer__obj.handlers[HW__TIMER__TIMER_3] = handler;

            break;
        case HW__TIMER__TIMER_4:
            TCNT4 = 0x00;
            TCCR4A = 0x00;
            TCCR4B = 0x00;

            OCR4A = OCRnA;
            TCCR4B |= (1 << WGM42);
            TCCR4B |= (1 << CS40) | (1 << CS41);
            TIMSK4 |= (1 << OCIE4A);

            hw__timer__obj.handlers[HW__TIMER__TIMER_4] = handler;

            break;
        case HW__TIMER__TIMER_5:
            TCNT5 = 0x00;
            TCCR5A = 0x00;
            TCCR5B = 0x00;

            OCR5A = OCRnA;
            TCCR5B |= (1 << WGM52);
            TCCR5B |= (1 << CS50) | (1 << CS51);
            TIMSK5 |= (1 << OCIE5A);

            hw__timer__obj.handlers[HW__TIMER__TIMER_5] = handler;

            break;
#endif // defined(__AVR_ATmega2560__)
    }

    interrupts();
}

/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Timer 1 overflow interrupt ISR
* @param None
* @return None
* @note
*****************************************************************************/
ISR (TIMER1_COMPA_vect)
{
    hw__timer__obj.handlers[HW__TIMER__TIMER_1]();
}

/*************************************************************************//**
* @brief Timer 2 overflow interrupt ISR
* @param None
* @return None
* @note
*****************************************************************************/
ISR (TIMER2_COMPA_vect)
{
    hw__timer__obj.handlers[HW__TIMER__TIMER_2]();
}

#if defined(__AVR_ATmega2560__)
/*************************************************************************//**
* @brief Timer 3 overflow interrupt ISR
* @param None
* @return None
* @note
*****************************************************************************/
ISR (TIMER3_COMPA_vect)
{
    hw__timer__obj.handlers[HW__TIMER__TIMER_3]();
}

/*************************************************************************//**
* @brief Timer 4 overflow interrupt ISR
* @param None
* @return None
* @note
*****************************************************************************/
ISR (TIMER4_COMPA_vect)
{
    hw__timer__obj.handlers[HW__TIMER__TIMER_4]();
}

/*************************************************************************//**
* @brief Timer 5 overflow interrupt ISR
* @param None
* @return None
* @note
*****************************************************************************/
ISR (TIMER5_COMPA_vect)
{
    hw__timer__obj.handlers[HW__TIMER__TIMER_5]();
}

#endif // defined(__AVR_ATmega2560__)
/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/

