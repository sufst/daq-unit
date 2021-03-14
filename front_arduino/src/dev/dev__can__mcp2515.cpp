/*************************************************************************//**
* @file dev__can__mcp2515.cpp
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
  include files
----------------------------------------------------------------------------*/
#include <SPI.h>
#include <mcp2515.h>

#include "dev__can__mcp2515.h"
#include "../sys/sys__manager.h"

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
/*************************************************************************//**
* @brief Initialise the wheel speed sensor
* @param dev__wheel__speed__obj_t* obj Wheel speed device object
* @return None
* @note
*****************************************************************************/
void dev__can__mcp2515__init()
{
    mcp2515.reset();                  
    mcp2515.setBitrate(CAN_125KBPS);  
    mcp2515.setNormalMode();          // Send and recieve mode
}

/*************************************************************************//**
* @brief Communications service process loop
* @param None
* @return None
* @note
*****************************************************************************/
void dev__can__mcp2515_tx(sys__datastore_t dataStore, uint8_t canCommand)
{ 
  struct can_frame frameTx;
  frameTx.can_id  = SYS__MANAGER__CAN_ID;
  frameTx.can_dlc = 5;      // Send 8 bytes (max)

  switch(canCommand){
    case DEV__CAN__CMD_WHEEL_SPEED:
      frameTx.data[0] = DEV__CAN__CMD_WHEEL_SPEED;
      frameTx.data[1] = sys__datastore.wheelSpeed.data & 0xFF;
      frameTx.data[2] = (sys__datastore.wheelSpeed.data>>8) & 0xFF;
      frameTx.data[3] = (sys__datastore.wheelSpeed.data>>16) & 0xFF;
      frameTx.data[4] = (sys__datastore.wheelSpeed.data>>24) & 0xFF;
      break;
  }
  
  Serial.print("Send: ");
  for(int i=0; i<frameTx.can_dlc; i++){
    Serial.print(frameTx.data[i]);
    Serial.print(" ");
  }
  Serial.println();
  
  mcp2515.sendMessage(&frameTx);  

}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
