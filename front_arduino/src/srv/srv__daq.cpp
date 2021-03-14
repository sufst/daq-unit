/*************************************************************************//**
* @file srv__daq.cpp
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
  include files
----------------------------------------------------------------------------*/
#include "srv__daq.h"

#include "../sys/sys__manager.h"
#include "../sys/sys__datastore.h"
/*
#if SYS__MANAGER__DAMPER_POTS_ENABLED
#include "../dev/dev__damper__pots.h"
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__ACCELEROMETER_ENABLED
#include "../dev/dev__accelerometer.h"
#endif // SYS__MANAGER__ACCELEROMETER_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
#include "../dev/dev__ride__height.h"
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED */

#if SYS__MANAGER__WHEEL_SPEED_ENABLED
#include "../dev/dev__wheel__speed.h"
#endif // SYS__MANAGER__WHEEL_SPEED_ENABLED

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/

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
/*#if SYS__MANAGER__DAMPER_POTS_ENABLED
static dev__damper__pots__obj_t dev__damper__pots__obj;
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__ACCELEROMETER_ENABLED
static dev__accelerometer__obj_t dev__accelerometer__obj;
#endif // SYS__MANAGER__ACCELEROMETER_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
static dev__ride__height__obj_t dev__ride__height__obj;
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED */

#if SYS__MANAGER__WHEEL_SPEED_ENABLED
static dev__wheel__speed__obj_t dev__wheel__speed__obj;
#endif // SYS__MANAGER__WHEEL_SPEED_ENABLED

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
#if SYS__MANAGER__WHEEL_SPEED_ENABLED
/*************************************************************************//**
* @brief Initialise wheel speed sensor
* @param uint8_t pins Wheel speed pin
* @return None
* @note
*****************************************************************************/
void srv__daq__wheel_speed_init(uint8_t pin)
{
    dev__wheel__speed__obj.pin = pin;
    dev__wheel__speed__init(&dev__wheel__speed__obj);
}
#endif // SYS__MANAGER__WHEEL_SPEED_ENABLED

/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/

/*************************************************************************//**
* @brief DAQ service process loop
* @param None
* @return None
* @note
*****************************************************************************/
void srv__daq__process(sys__datastore_t dataStore)
{ 
  // Read wheel speed
  dataStore.wheelSpeed.data = dev__wheel_speed__read_uv(&dev__wheel__speed__obj);

}

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/


