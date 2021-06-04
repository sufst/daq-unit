/*************************************************************************//**
* @file sys__manager.h
* @brief Main system application
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
  @brief sys__manager.h holds all the common configurable compile options for the system
----------------------------------------------------------------------------*/
#ifndef SYS__MANAGER_H
#define SYS__MANAGER_H

/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
//#include "Arduino.h"

/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/
#define SYS__MANAGER__DAMPER_POTS_ENABLED 1
#define SYS__MANAGER__DAMPER_POTS_ATTACHED_AMT 2
#define SYS__MANAGER__DAMPER_POT_L_PIN 1
#define SYS__MANAGER__DAMPER_POT_R_PIN 2

#define SYS__MANAGER__ACCELEROMETER_ENABLED 1
#define SYS__MANAGER__ACCELEROMETER_ATTACHED_AMT 3
#define SYS__MANAGER__ACCELEROMETER_X_PIN 3
#define SYS__MANAGER__ACCELEROMETER_Y_PIN 4
#define SYS__MANAGER__ACCELEROMETER_Z_PIN 5

#define SYS__MANAGER__FUEL_FLOW_ENABLED 1
#define SYS__MANAGER__FUEL_FLOW_PIN 5

#define SYS__MANAGER__RIDE_HEIGHT_ENABLED 1
#define SYS__MANAGER__RIDE_HEIGHT_PIN 6

#define SYS__MANAGER__WHEEL_SPEEDS_ENABLED 1
#define SYS__MANAGER__WHEEL_SPEEDS_ATTACHED_AMT 2
#define SYS__MANAGER__WHEEL_SPEED_L_PIN 7
#define SYS__MANAGER__WHEEL_SPEED_R_PIN 8

#define SYS__MANAGER__DAQ_SAMPLE_PERIOD 500



#define SYS__MANAGER__CAN_BUS_ENABLED 1
#define SYS__MANAGER__CAN_ID 0
#define SYS__MANAGER__CAN_CS_PIN 3
#define SYS__MANAGER__CAN_INT_PIN 7
#define SYS__MANAGER__CAN_SPEED CAN_1000KBPS


#define SYS__MANAGER__XBEE_ENABLED 1

#define SYS__MANAGER__ECU_ENABLED 1

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
void sys__manager__init();

void sys__manager__process();
/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif //SYS__MANAGER_H
