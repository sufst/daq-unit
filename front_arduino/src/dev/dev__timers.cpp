/*************************************************************************//**
* @file dev__software__timer.cpp
* @brief Software timer device layer
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
#include "dev__timers.h"

#include "../hw/hw__timer.h"
/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef struct
{
    dev__software__timer__callback handler;
} dev__software__timer__obj_t;
/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
static void dev__software__timer__hw_timer_handler();
/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  global variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/
static dev__software__timer__obj_t dev__software__timer__obj;
/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Initialises hardware timer 1 at 1000hz for software timers
* @param None
* @return None
* @note All software timers have to be a multiple of 2ms intervals
*****************************************************************************/
void dev__software__timer__init()
{
    hw__timer__init(HW__TIMER__TIMER_1, DEV__SOFTWARE__TIMER__HW_1MS_OCRNA,
                                  dev__software__timer__hw_timer_handler);
}

/*************************************************************************//**
* @brief Register service layer interrupt handler
* @param dev__software__timer__callback handler Callback
* @return None
* @note
*****************************************************************************/
void dev__software__timer__register_handler(dev__software__timer__callback handler)
{
    dev__software__timer__obj.handler = handler;
}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Hardware layer interrupt handler function
* @param None
* @return None
* @note
*****************************************************************************/
static void dev__software__timer__hw_timer_handler()
{
    dev__software__timer__obj.handler();
}
/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/


