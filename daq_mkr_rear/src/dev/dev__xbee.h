/*************************************************************************//**
* @file dev__xbee.h
* @brief Device layer implementing the XBEE radio
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
#ifndef CONTROLLER_V2_DEV__XBEE_H
#define CONTROLLER_V2_DEV__XBEE_H

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
#define DEV__XBEE_START_BYTE 0x01

#define DEV__XBEE_CORE_BITFIELD 8
#define DEV__XBEE_AERO_BITFIELD 7
#define DEV__XBEE_DIAG_BITFIELD 5
#define DEV__XBEE_POWER_BITFIELD 8
#define DEV__XBEE_SUS_BITFIELD 8
#define DEV__XBEE_MISC_BITFIELD 8

#define DEV__XBEE_FRAME_CORE_LENGTH 22
#define DEV__XBEE_FRAME_AERO_LENGTH 18
#define DEV__XBEE_FRAME_DIAG_LENGTH 8
#define DEV__XBEE_FRAME_POWER_LENGTH 14
#define DEV__XBEE_FRAME_SUS_LENGTH 12
#define DEV__XBEE_FRAME_MISC_LENGTH 60


/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef enum
{
    DEV__XBEE__CMD_CORE = 0x01,
    DEV__XBEE__CMD_AERO,
    DEV__XBEE__CMD_DIAGNOSTIC,
    DEV__XBEE__CMD_POWER,
    DEV__XBEE__CMD_SUSPENSION,
    DEV__XBEE__CMD_MISC
} dev__ecu__cmd_t;

typedef enum
{
    DEV__XBEE__CMD_DAMPER = 0x01,
    DEV__XBEE__CMD_WHEEL_SPEED,
    DEV__XBEE__CMD_RIDE_HEIGHT
} dev__daq__cmd_t;



/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/
extern dev__ecu__cmd_t dev__xbee_ecu_cmd;
extern dev__daq__cmd_t dev__xbee_daq_cmd;


/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
void dev__xbee_tx(int xbee_cmd);



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