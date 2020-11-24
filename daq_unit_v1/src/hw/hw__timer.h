/*************************************************************************//**
* @file hw__timer.h
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
  @brief
  To do: check hardware support //Piotr
----------------------------------------------------------------------------*/

#ifndef CONTROLLER_HW__TIMER_H
#define CONTROLLER_HW__TIMER_H
/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
#include "Arduino.h"
/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/
#if defined(__AVR_ATmega2560__)
#define HW__TIMER__SUPPORTED_TIMERS 6
#else
#define HW__TIMER__SUPPORTED_TIMERS 3
#endif

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef enum
{
    HW__TIMER__TIMER_0 = 0x00,
    HW__TIMER__TIMER_1,
    HW__TIMER__TIMER_2,
    HW__TIMER__TIMER_3,
    HW__TIMER__TIMER_4,
    HW__TIMER__TIMER_5
} hw__timer__timer_num_t;

typedef void (*hw__timer__handler)(void);
/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
void hw__timer__init(hw__timer__timer_num_t timer, uint16_t OCRnA, hw__timer__handler handler);

void hw__timer__register_handler(hw__timer__timer_num_t timer, hw__timer__handler handler);
/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/


#endif //CONTROLLER_HW__TIMER_H
