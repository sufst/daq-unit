/*************************************************************************//**
* @file dev__yaw__sensor.cpp
* @brief Yaw sensor device layer
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
#include "dev__yaw__sensor.h"

/*----------------------------------------------------------------------------
  include files
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/
#define DEV__YAW__SENSOR__ADC_CONVERSION_UV 488

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/

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

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Initialise the yaw sensor input
* @param dev__yaw__sensor__obj_t *obj yaw sensor device object
* @return None
* @note
*****************************************************************************/
void dev__yaw__sensor__init(dev__yaw__sensor__obj_t *obj)
{
    pinMode(obj->pin, INPUT_PULLUP);
}

/*************************************************************************//**
* @brief Read the yaw sensor pin voltage in micro volts
* @param dev__yaw__sensor__obj_t *obj Yaw sensor device object
* @return None
* @note
*****************************************************************************/
uint32_t dev__yaw__sensor__read_pot_uv(dev__yaw__sensor__obj_t *obj)
{
    uint32_t adcRaw = analogRead(obj->pin);
    return (adcRaw * DEV__YAW__SENSOR__ADC_CONVERSION_UV);
}

/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
