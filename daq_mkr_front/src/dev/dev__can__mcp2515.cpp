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
#include <mcp_can.h>
#include <SPI.h>

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
//sys__datastore_t dev__datastore_2;
MCP_CAN CAN0(3);                               // Set CS to pin 3  

union 
{
  uint32_t data;
  uint8_t dataBytes[4]; // Little Endian
}dev__can_data;

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
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  while(CAN0.begin(MCP_ANY, SYS__MANAGER__CAN_SPEED, MCP_16MHZ) != CAN_OK)
    Serial.println("Error Initializing MCP2515...");
  
  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.                         

  Serial.print("CAN INIT");
}


/*************************************************************************//**
* @brief CAN tranmission
* @param None
* @return None
* @note
*****************************************************************************/
void dev__can__mcp2515_tx(int can_cmd, sys__datastore_t *dataStore)
{   
  long unsigned int can_id;
  unsigned char len = 8;
  unsigned char txBuf[8];
  uint32_t temp;

  can_id = can_cmd;

  Serial.print("Transmit - ID:");
  Serial.print(can_id);
  
  switch(can_cmd){
    case DEV__CAN__CMD_DAMPER:{  
      dev__can_data.data =  dataStore->damperPots[1].data;
      for(int i=0; i<sizeof(uint32_t); i++)
        txBuf[i] = dev__can_data.dataBytes[i];

      dev__can_data.data = dataStore->damperPots[1].data;
      for(int i=0; i<sizeof(uint32_t); i++)
        txBuf[i+sizeof(uint32_t)] = dev__can_data.dataBytes[i];
               
      Serial.print("\tDamper 1:");
      Serial.print(dataStore->damperPots[0].data);
      Serial.print("\tDamper 2:");
      Serial.println(dataStore->damperPots[1].data);
      break; 
    }      
    case DEV__CAN__CMD_WHEEL_SPEED:{  
      dev__can_data.data = dataStore->wheelSpeeds[0].data;
      for(int i=0; i<sizeof(uint32_t); i++)
        txBuf[i] = dev__can_data.dataBytes[i];
      
      dev__can_data.data = dataStore->wheelSpeeds[1].data;
      for(int i=0; i<sizeof(uint32_t); i++)
        txBuf[i+sizeof(uint32_t)] = dev__can_data.dataBytes[i];
               
      Serial.print("\tLeft Wheel Speed:");
      Serial.print(dataStore->wheelSpeeds[0].data);
      Serial.print("\tRight Wheel Speed:");
      Serial.println(dataStore->wheelSpeeds[1].data);
      break; 
    } 
    case DEV__CAN__CMD_RIDE_HEIGHT:{  
      dev__can_data.data = dataStore->rideHeight.data;
      for(int i=0; i<sizeof(uint32_t); i++)
        txBuf[i] = dev__can_data.dataBytes[i];
            
      Serial.print("\t Ride Height:");
      Serial.println(dataStore->rideHeight.data);
      break; 
    } 

    CAN0.sendMsgBuf(can_id, 0, len, txBuf);

  }

}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
