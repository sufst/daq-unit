/*************************************************************************//**
* @file srv__daq.h
* @brief DAQ service layer
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

#ifndef CONTROLLER_V2_SRV__DAQ_H
#define CONTROLLER_V2_SRV__DAQ_H
/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
#include "Arduino.h"

#include <stdint.h> 

#include "../sys/sys__manager.h"
#include "../sys/sys__datastore.h"
/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef enum
{
    SRV__DAQ__ERROR_NONE,
    SRV__DAQ__ERROR
} srv__daq__state_t;

/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
#if SYS__MANAGER__DAMPER_POTS_ENABLED
void srv__daq__damper_pots_init(uint8_t *pins);
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__ACCELEROMETERS_ENABLED
void srv__daq__accelerometers_init(uint8_t *pins);
#endif // SYS__MANAGER__ACCELEROMETERS_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
void srv__daq__ride_height_init(uint8_t pin);
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

#if SYS__MANAGER__WHEEL_SPEEDS_ENABLED
void srv__daq__wheel_speeds_init(uint8_t *pins);
#endif // SYS__MANAGER__WHEEL_SPEEDS_ENABLED

#if SYS__MANAGER__FUEL_FLOW_ENABLED
void srv__daq__fuel_flow_init(uint8_t pin);
#endif // SYS__MANAGER__FUEL_FLOW_ENABLED

void srv__daq__process(sys__datastore_t dataStore);
/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif //CONTROLLER_V2_SRV__DAQ_H

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
