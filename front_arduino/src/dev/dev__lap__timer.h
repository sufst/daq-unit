/*************************************************************************//**
* @file dev__lap__timer.h
* @brief Laptimer device layer
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
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*****************************************************************************/
/*----------------------------------------------------------------------------
  @brief
----------------------------------------------------------------------------*/

#ifndef CONTROLLER_V2_DEV__LAP__TIMER_H
#define CONTROLLER_V2_DEV__LAP__TIMER_H
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

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef struct
{
    uint8_t intPin;
    uint8_t drivePin;

    void (*callback)(void);
} dev__lap__timer__obj_t;
/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
void dev__lap__timer__init(dev__lap__timer__obj_t *obj);

/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif //CONTROLLER_V2_DEV__LAP__TIMER_H

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
