/*************************************************************************//**
* @file dev__can__mcp2515.h
* @brief Device layer implementing the MCP2515 CAN Controller
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
#ifndef CONTROLLER_V2_DEV__CAN__MCP2515_H
#define CONTROLLER_V2_DEV__CAN__MCP2515_H

/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
#include "Arduino.h"
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
    DEV__CAN__CMD_DAMPER = 0x01,
    DEV__CAN__CMD_ACCELEROMETER_X,
    DEV__CAN__CMD_ACCELEROMETER_Y,
    DEV__CAN__CMD_ACCELEROMETER_Z,
    DEV__CAN__CMD_RIDE_HEIGHT,
    DEV__CAN__CMD_WHEEL_SPEED,
    DEV__CAN__CMD_TIME_STAMP
} dev__can__cmd_t;

/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/
extern dev__can__cmd_t dev__can_cmd;

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
void dev__can__mcp2515__init();
void dev__can__mcp2515_tx(sys__datastore_t dataStore, uint8_t canCommand);

/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif // CONTROLLER_V2_DEV__CAN__MCP2515_H

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/