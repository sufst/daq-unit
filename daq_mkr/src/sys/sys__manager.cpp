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
#include "../srv/srv__comms.h"
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
sys__ecu_datastore_t sys__ecu_datastore;

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
  /*
#if SYS__MANAGER__DAMPER_POTS_ENABLED
    uint8_t dampersPins[SYS__MANAGER__DAMPER_POTS_ATTACHED_AMT] = {SYS__MANAGER__DAMPER_POT_1_PIN,
                                                                   SYS__MANAGER__DAMPER_POT_2_PIN};
    srv__daq__damper_pots_init(dampersPins);
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__ACCELEROMETERS_ENABLED
    // 3 pins per accelerometer, x, y, z axis
    uint8_t accelerometerPins[SYS__MANAGER__ACCELEROMETERS_ATTACHED_AMT*SYS__MANAGER__ACCELEROMETER_ATTACHED_PINS] 
                                                                          = {SYS__MANAGER__ACCELEROMETER_X_1_PIN,
                                                                             SYS__MANAGER__ACCELEROMETER_Y_1_PIN,
                                                                             SYS__MANAGER__ACCELEROMETER_Z_1_PIN,
                                                                             SYS__MANAGER__ACCELEROMETER_X_2_PIN,
                                                                             SYS__MANAGER__ACCELEROMETER_Y_2_PIN,
                                                                             SYS__MANAGER__ACCELEROMETER_Z_2_PIN};
    srv__daq__accelerometers_init(accelerometerPins);
#endif // SYS__MANAGER__ACCELEROMETERS_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
    srv__daq__ride_height_init(SYS__MANAGER__RIDE_HEIGHT_PIN);
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

#if SYS__MANAGER__FUEL_FLOW_ENABLED
    srv__daq__fuel_flow_init(SYS__MANAGER__FUEL_FLOW_PIN);
#endif // SYS__MANAGER__FUEL_FLOW_ENABLED */

#if SYS__MANAGER__WHEEL_SPEEDS_ENABLED
    uint8_t wheelSpeedPins[SYS__MANAGER__WHEEL_SPEEDS_ATTACHED_AMT] = {SYS__MANAGER__WHEEL_SPEED_1_PIN,
                                                                       SYS__MANAGER__WHEEL_SPEED_2_PIN};
    srv__daq__wheel_speeds_init(wheelSpeedPins);
#endif // SYS__MANAGER__WHEEL_SPEED_ENABLED


#if SYS__MANAGER__CAN_BUS_ENABLED
    srv__comms__can_init();
#endif //SYS__MANAGER__CAN_BUS_ENABLED
 
    
}

/*************************************************************************//**
* @brief services loops
* @param None
* @return None
* @note
*****************************************************************************/
void sys__manager__process()
{
    //srv__daq__process(sys__datastore);
    srv__comms__process(sys__datastore);
}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/
