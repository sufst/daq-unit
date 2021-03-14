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
#include <math.h>

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
bool canIntrr = false;

union 
{
  float data;
  uint8_t dataBytes[4]; // Little Endian
}dev__can_data;

/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
void dev__can__mcp2515__irq_handler(){
    canIntrr = true;
}

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
    attachInterrupt(SYS__MANAGER__CAN_INT_PIN, dev__can__mcp2515__irq_handler, FALLING);
}

/*************************************************************************//**
* @brief Communications service process loop
* @param None
* @return None
* @note
*****************************************************************************/
void dev__can__mcp2515_rx(sys__datastore_t dataStore)
{ 

  if(canIntrr){
    canIntrr = false;

    can_frame frameRx;
    uint8_t irq = mcp2515.getInterrupts();
    unsigned char idRx;

    if (irq & MCP2515::CANINTF_RX0IF) {
      if (mcp2515.readMessage(MCP2515::RXB0, &frameRx) == MCP2515::ERROR_OK) {
        idRx = frameRx.can_id;
        uint8_t commandByteRx;

        commandByteRx = frameRx.data[0];
        for(int i=0; i<frameRx.can_dlc; i++)
          dev__can_data.dataBytes[i] = frameRx.data[i+1];  // First byte of data is command
          
        switch(commandByteRx){
          case DEV__CAN__CMD_WHEEL_SPEED:
            dataStore.wheelSpeeds[0].data = dev__can_data.data;
        }

        Serial.print("Recieved: ");
        Serial.print(idRx);
        Serial.print(" ");
        Serial.print(commandByteRx);
        Serial.print(" ");
        for(int i=0; i<frameRx.can_dlc; i++){
          Serial.print(dev__can_data.dataBytes[i]);
          Serial.print(" ");
        }
        Serial.println();
      }
      if (irq & MCP2515::CANINTF_RX1IF) {
        if (mcp2515.readMessage(MCP2515::RXB1, &frameRx) == MCP2515::ERROR_OK) {
          idRx = frameRx.can_id;
          uint8_t dataBytesRx[sizeof(float)];
          uint8_t commandByteRx;

          commandByteRx = frameRx.data[0];
          for(int i=0; i<frameRx.can_dlc; i++)
            dev__can_data.dataBytes[i] = frameRx.data[i+1];  // First byte of data is command
                
          switch(commandByteRx){
            case DEV__CAN__CMD_WHEEL_SPEED:
              dataStore.wheelSpeeds[0].data = dev__can_data.data;
          }

          Serial.print("Recieved: ");
          Serial.print(idRx);
          Serial.print(" ");
          Serial.print(commandByteRx);
          Serial.print(" ");
          for(int i=0; i<frameRx.can_dlc; i++){
            Serial.print(dev__can_data.dataBytes[i]);
            Serial.print(" ");
          }
          Serial.println();
        }
      }
    }
  }
}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
