/*************************************************************************//**
* @file srv__can.h
* @brief Communications service layer
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

#ifndef CONTROLLER_V2_SRV__COMMS_H
#define CONTROLLER_V2_SRV__COMMS_H
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
    SRV__COMMS__CMD_DAMPER_1 = 0x01,
    SRV__COMMS__CMD_DAMPER_2,
    SRV__COMMS__CMD_ACCELEROMETER_X_1,
    SRV__COMMS__CMD_ACCELEROMETER_Y_1,
    SRV__COMMS__CMD_ACCELEROMETER_Z_1,
    SRV__COMMS__CMD_ACCELEROMETER_X_2,
    SRV__COMMS__CMD_ACCELEROMETER_Y_2,
    SRV__COMMS__CMD_ACCELEROMETER_Z_2,
    SRV__COMMS__CMD_RIDE_HEIGHT,
    SRV__COMMS__CMD_WHEEL_SPEED_1,
    SRV__COMMS__CMD_WHEEL_SPEED_2,
    SRV__COMMS__CMD_FUEL_FLOW,
    SRV__COMMS__CMD_TIME_STAMP
} srv__comms__cmd_t;

/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/
extern srv__comms__cmd_t srv__comms_cmd;
/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
#if SYS__MANAGER__CAN_BUS_ENABLED
void srv__comms__can_init(uint8_t pinCS);
void rxCanHandler();
#endif // SYS__MANAGER__CAN_BUS_ENABLED


void srv__comms__process(sys__datastore_t dataStore);
void srv__comms__can_tx(sys__datastore_t dataStore, uint8_t canCommand);
/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif //CONTROLLER_V2_SRV__COMMS_H

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
