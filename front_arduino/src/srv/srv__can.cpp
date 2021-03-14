/*************************************************************************//**
* @file srv__can.cpp
* @brief CAN communications service layer
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
#include "srv__can.h"

#include "../sys/sys__manager.h"
#include "../sys/sys__datastore.h"

#include <SPI.h>
#include <mcp2515.h>
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
MCP2515 mcp2515(SYS__MANAGER__CAN_CS_PIN);  

/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
#if SYS__MANAGER__CAN_BUS_ENABLED
/*************************************************************************//**
* @brief Initialise MCP2515 CAN
* @param uint8_t pinCS Pin number of connection to SPI CS of MCP2515
* @return None
* @note
*****************************************************************************/
void srv__comms__can_init(uint8_t pinCS)
{  
    mcp2515.reset();                  
    mcp2515.setBitrate(CAN_125KBPS);  
    mcp2515.setNormalMode();          // Send and recieve mode
}


/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/

/*************************************************************************//**
* @brief Communications service process loop
* @param sys__datastore_t dataStore
* @param uint8_t canID
* @return None
* @note
*****************************************************************************/
void srv__comms__process(sys__datastore_t dataStore)
{ 

  srv__comms__can_tx(dataStore, SRV__COMMS__CMD_WHEEL_SPEED);

}


/*************************************************************************//**
* @brief Communications service process loop
* @param None
* @return None
* @note
*****************************************************************************/
void srv__comms__can_tx(sys__datastore_t dataStore, uint8_t canCommand)
{ 
  struct can_frame msg;
  msg.can_id  = SYS__MANAGER__CAN_ID;
  msg.can_dlc = 5;      // Send 8 bytes (max)

  switch(canCommand){
    case SRV__COMMS__CMD_WHEEL_SPEED:
      msg.data[0] = SRV__COMMS__CMD_WHEEL_SPEED;
      msg.data[1] = sys__datastore.wheelSpeed.data & 0xFF;
      msg.data[2] = (sys__datastore.wheelSpeed.data>>8) & 0xFF;
      msg.data[3] = (sys__datastore.wheelSpeed.data>>16) & 0xFF;
      msg.data[4] = (sys__datastore.wheelSpeed.data>>24) & 0xFF;
      break;
  }

  mcp2515.sendMessage(&msg);  

}

#endif // SYS__MANAGER__CAN_BUS_ENABLED



