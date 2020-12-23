/*************************************************************************//**
* @file sys__manager.cpp
* @brief System manager 
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
#include "sys__manager.h"
#include "../srv/srv__daq.h"

#include "sys__datastore.h"


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
sys__datastore_t sys__datastore;

/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/

/*************************************************************************//**
* @brief Initialises the system
* @param None
* @return None
* @note
*****************************************************************************/
void sys__manager__init()
{
#if SYS__MANAGER__DAMPER_POTS_ENABLED
    uint8_t dampersPins[SYS__MANAGER__DAMPER_POTS_ATTACHED_AMT] = {SYS__MANAGER__DAMPER_POT_1_PIN,
                                                                   SYS__MANAGER__DAMPER_POT_2_PIN,
                                                                   SYS__MANAGER__DAMPER_POT_3_PIN,
                                                                   SYS__MANAGER__DAMPER_POT_4_PIN};
    srv__daq__damper_pots_init(SYS__MANAGER__DAMPER_POTS_POLL_MS, dampersPins);
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__ACCELEROMETER_ENABLED
    srv__daq__accelerometer_init(SYS__MANAGER__ACCELEROMETER_X_PIN, 
                                 SYS__MANAGER__ACCELEROMETER_Y_PIN, 
                                 SYS__MANAGER__ACCELEROMETER_Z_PIN);
#endif // SYS__MANAGER__ACCELEROMETER_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
    srv__daq__ride_height_init(SYS__MANAGER__RIDE_HEIGHT_PIN);
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

#if SYS__MANAGER__WHEEL_SPEED_ENABLED
    srv__daq__wheel_speed_init(SYS__MANAGER__WHEEL_SPEED_PIN);
#endif // SYS__MANAGER__WHEEL_SPEED_ENABLED

    Serial.println("SYSTEM INIT FINISHED");
}

/*************************************************************************//**
* @brief services loops
* @param None
* @return None
* @note
*****************************************************************************/
void sys__manager__process()
{
    srv__daq__process(sys__datastore);
}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/
