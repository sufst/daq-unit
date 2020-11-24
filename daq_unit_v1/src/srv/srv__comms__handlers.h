/*************************************************************************//**
* @file srv__comms__can__handlers.h
* @brief Communication service layer message handlers
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

#ifndef CONTROLLER_V2_SRV__COMMS__HANDLERS_H
#define CONTROLLER_V2_SRV__COMMS__HANDLERS_H
/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
#include "Arduino.h"

#include "srv__comms.h"
/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/
extern void (*const srv__comms__handlers__from_cmd[])(void *data, uint8_t len);

extern void (*const srv__comms__handlers__from_can_0x2000_region[])(srv__comms__can_rx_message_t *msg);

extern void (*const srv__comms__handlers__from_can_0x487_region[])(srv__comms__can_rx_message_t *msg);
/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
void srv__comms__handler_config(void *data, uint8_t len);

void srv__comms__handler_tag_data(void *data, uint8_t len);
/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif //CONTROLLER_V2_SRV__COMMS__HANDLERS_H
/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
