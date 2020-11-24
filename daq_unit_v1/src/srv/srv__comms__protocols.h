/*************************************************************************//**
* @file srv__comms__protocols.h
* @brief Communication service layer message protocols
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

#ifndef CONTROLLER_V2_SRV__COMMS__PROTOCOLS_H
#define CONTROLLER_V2_SRV__COMMS__PROTOCOLS_H
/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
#include "Arduino.h"

#include "../sys/sys__manager.h"
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
    SRV__COMMS__PROTOCOLS__CMD_CONFIG = 0x01,
    SRV__COMMS__PROTOCOLS__CMD_TAG_DATA,
    SRV__COMMS__PROTOCOLS__CMD_STATUS
} srv__comms__protocols__cmd_t;

/*
 * SRV__COMMS__PROTOCOLS__CMD_TAG_DATA has the following format:
 *
 * [ cmd: Tag Data ] [ 1-byte TAG ] [ n-bytes data ] ...
 *
 * In a single message of 32 bytes, an arbitrary amount of sensors data can be sent.
 *
 */

/*
 * SRV__COMMS__PROTOCOLS__CMD_CONFIG has the following format:
 *
 * [ cmd: Config ] [ len n] .. [ 1-byte Tag to config ] [ 1-byte Sub config] [ n-bytes Config data] ...
 *
 * In a single message of 32 bytes, an arbitrary amount of tags can be configured.
 *
 */

/*
 * SRV__COMMS__PROTOCOLS__CMD_STATUS has the following format:
 *
 * [ cmd: Status ] [ 1-byte Status Tag] [ 1-byte Data ] ...
 *
 * In a single message of 32 bytes, an arbitrary amount status bytes can be sent.
 *
 */

/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif //CONTROLLER_V2_SRV__COMMS__PROTOCOLS_H

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
