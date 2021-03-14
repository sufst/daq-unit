/*************************************************************************//**
* @file dev__wheel__speed.h
* @brief device layer for analgog read of wheel speed
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
#ifndef CONTROLLER_V2_DEV__WHEEL__SPEED_H
#define CONTROLLER_V2_DEV__WHEEL__SPEED_H

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
    uint8_t pin;
    uint32_t conversionRate;
} dev__wheel__speed__obj_t;
/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
void dev__wheel__speed__init(dev__wheel__speed__obj_t* obj);

/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Read the wheel speed pin voltage in micro volts
* @param dev__wheel__speed__obj_t *obj Wheel speed device object
* @return uint32_t Voltage in uV
* @note
*****************************************************************************/
inline uint32_t dev__wheel_speed__read_uv(dev__wheel__speed__obj_t *obj)
{
  //uint32_t adcRaw = analogRead(obj->pin);
  static uint32_t var = 0;
  //return (adcRaw * obj->conversionRate);
  return var++;
}

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif // CONTROLLER_V2_DEV__WHEEL__SPEED_H

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
