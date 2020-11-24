/*************************************************************************//**
* @file srv__software__timer.h
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
  To be modified, not specified yet //Piotr
----------------------------------------------------------------------------*/

#ifndef CONTROLLER_SRV__SOFTWARE__TIMER_H
#define CONTROLLER_SRV__SOFTWARE__TIMER_H
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
#define SRV__SOFTWARE__TIMER__MAX_SUPPORTED_CALLBACKS 10

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef void (*srv__software__timer__callback)(void);

typedef int8_t srv__software__timer__handle;
/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
void srv__software__timer__init();

srv__software__timer__handle
srv__software__timer__register(uint16_t intervalMs, srv__software__timer__callback handler);

void srv__software__timer__change_ms(srv__software__timer__handle timer, uint16_t newMs);

void srv__software__timer__process();
/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif //CONTROLLER_SRV__SOFTWARE__TIMER_H
