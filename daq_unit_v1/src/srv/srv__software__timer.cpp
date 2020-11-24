/*************************************************************************//**
* @file srv__software__timer.cpp
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
#include "srv__software__timer.h"

#include "../dev/dev__timers.h"
/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef struct
{
    srv__software__timer__callback handler;
    uint16_t devClocksRequired;
    uint16_t devClocksSeen;
} srv__software__timer__handler_obj_t;

typedef struct
{
    srv__software__timer__handler_obj_t handlers[SRV__SOFTWARE__TIMER__MAX_SUPPORTED_CALLBACKS];
    uint8_t handlersCnt;
    srv__software__timer__callback readyHandlers[SRV__SOFTWARE__TIMER__MAX_SUPPORTED_CALLBACKS];
    uint8_t readyHandlersCnt;
} srv__software__timer__obj_t;

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
static void srv__software__timers__dev_handler();

/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  global variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/
static srv__software__timer__obj_t srv__software__timer__obj;

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Initialises the timer device layer assumed to be running at 1000hz
* @param None
* @return None
* @note All software timers have to be a multiple of 1ms intervals
*****************************************************************************/
void srv__software__timer__init()
{
    dev__software__timer__register_handler(srv__software__timers__dev_handler);
    dev__software__timer__init();
}

/*************************************************************************//**
* @brief Register a timer callback that gets called at a wanted multiple of 1ms
* @param uint16_t intervalMs Callback interval
* @param srv__software__timer__callback handler Callback function
* @return srv__software__timer__handle Handle for the assigned timer
* @note
*****************************************************************************/
srv__software__timer__handle srv__software__timer__register(uint16_t intervalMs, srv__software__timer__callback handler)
{
    for (uint8_t i = 0; i < SRV__SOFTWARE__TIMER__MAX_SUPPORTED_CALLBACKS; i++)
    {
        if (srv__software__timer__obj.handlers[i].handler == NULL)
        {
            srv__software__timer__obj.handlers[i].handler = handler;
            srv__software__timer__obj.handlers[i].devClocksRequired = intervalMs;

            srv__software__timer__obj.handlersCnt++;

            return i;
        }
    }

    return -1;
}

/*************************************************************************//**
* @brief Change the interval ms of a premade timer
* @param srv__software__timer__handle timer Timer handle
* @param uint16_t newMs New timer interval ms
* @return None
* @note
*****************************************************************************/
void srv__software__timer__change_ms(srv__software__timer__handle timer, uint16_t newMs)
{
    srv__software__timer__handler_obj_t *timerHandler = &srv__software__timer__obj.handlers[timer];

    timerHandler->devClocksRequired = newMs;
    timerHandler->devClocksSeen = 0;
}

/*************************************************************************//**
* @brief Timer service layer calls ready callback functions
* @param None
* @return None
* @note
*****************************************************************************/
void srv__software__timer__process()
{
    while (srv__software__timer__obj.readyHandlersCnt > 0)
    {
        srv__software__timer__obj.readyHandlers[--srv__software__timer__obj.readyHandlersCnt]();
    }
}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Handler for timer device layer timer interrupts
* @param None
* @return None
* @note
*****************************************************************************/
static void srv__software__timers__dev_handler()
{
    for (uint8_t i = 0; i < srv__software__timer__obj.handlersCnt; i++)
    {
        srv__software__timer__handler_obj_t *handler = (srv__software__timer__handler_obj_t *)
                &(srv__software__timer__obj.handlers[i]);

        if (++handler->devClocksSeen == handler->devClocksRequired)
        {
            handler->devClocksSeen = 0;

            srv__software__timer__obj.readyHandlers[srv__software__timer__obj.readyHandlersCnt] = handler->handler;
            srv__software__timer__obj.readyHandlersCnt++;
        }
    }
}

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
