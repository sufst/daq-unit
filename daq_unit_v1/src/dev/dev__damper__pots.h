/*************************************************************************//**
* @file dev__damper__pots.h
* @brief Damper pots device layer
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

#ifndef CONTROLLER_V2_DEV__DAMPER__POTS_H
#define CONTROLLER_V2_DEV__DAMPER__POTS_H
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
} dev__damper__pots__obj_t;

/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/

void dev__damper__pots__init(dev__damper__pots__obj_t *obj);

/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Read the damper pot pin voltage in micro volts
* @param dev__damper__pots__obj_t *obj Damper pot device object
* @return None
* @note
*****************************************************************************/
inline uint32_t dev__damper__pots__read_pot_uv(dev__damper__pots__obj_t *obj)
{
    uint32_t adcRaw = analogRead(obj->pin);
    return (adcRaw * obj->conversionRate);
}
/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif //CONTROLLER_V2_DEV__DAMPER__POTS_H

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/

