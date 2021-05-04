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
//#include <mcp2515.h>
#include <mcp2515_can.h>

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
//MCP2515 mcp2515(SYS__MANAGER__CAN_CS_PIN);  
mcp2515_can CAN(SYS__MANAGER__CAN_CS_PIN);

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
    while (CAN_OK != CAN.begin(CAN_1000KBPS)) {             // init can bus : baudrate = 500k
        Serial.println("CAN BUS Shield init fail, try again");
        delay(100);
    }
}

/*************************************************************************//**
* @brief Communications service process loop
* @param None
* @return None
* @note
*****************************************************************************/
void dev__can__mcp2515_tx(sys__ecu_datastore_t dataStore, int ecuCanId)
{ 
  unsigned long frameId;
  uint8_t frameLen = 8;
  uint8_t frameData[8];
  
  
  switch(ecuCanId){
    case DEV__CAN__CMD_2000:
      frameId = DEV__CAN__CMD_2000;
      frameData[0] = dataStore.x2000_data.rpm & 0xFF;
      frameData[1] = (dataStore.x2000_data.rpm>>8) & 0xFF;
      frameData[2] = dataStore.x2000_data.tps & 0xFF;
      frameData[3] = (dataStore.x2000_data.tps>>8) & 0xFF;
      frameData[4] = dataStore.x2000_data.waterTemp & 0xFF;
      frameData[5] = (dataStore.x2000_data.waterTemp>>8) & 0xFF;
      frameData[6] = dataStore.x2000_data.airTemp & 0xFF;
      frameData[7] = (dataStore.x2000_data.airTemp>>8) & 0xFF;
      CAN.sendMsgBuf(DEV__CAN__CMD_2000, 0, frameLen, frameData);
      break;
    case DEV__CAN__CMD_2001:
      frameId = DEV__CAN__CMD_2001;
      frameData[0] = dataStore.x2001_data.maniPress & 0xFF;
      frameData[1] = (dataStore.x2001_data.maniPress>>8) & 0xFF;
      frameData[2] = dataStore.x2001_data.lambda & 0xFF;
      frameData[3] = (dataStore.x2001_data.lambda>>8) & 0xFF;
      frameData[4] = dataStore.x2001_data.speed & 0xFF;
      frameData[5] = (dataStore.x2001_data.speed>>8) & 0xFF;
      frameData[6] = dataStore.x2001_data.oilPress & 0xFF;
      frameData[7] = (dataStore.x2001_data.oilPress>>8) & 0xFF;
      CAN.sendMsgBuf(DEV__CAN__CMD_2001, 0, frameLen, frameData);
      break;
    case DEV__CAN__CMD_2002:
      frameId = DEV__CAN__CMD_2002;
      frameData[0] = dataStore.x2002_data.fuelPress & 0xFF;
      frameData[1] = (dataStore.x2002_data.fuelPress >>8) & 0xFF;
      frameData[2] = dataStore.x2002_data.oilTemp & 0xFF;
      frameData[3] = (dataStore.x2002_data.oilTemp>>8) & 0xFF;
      frameData[4] = dataStore.x2002_data.battery & 0xFF;
      frameData[5] = (dataStore.x2002_data.battery >>8) & 0xFF;
      frameData[6] = dataStore.x2002_data.fuelCon & 0xFF;
      frameData[7] = (dataStore.x2002_data.fuelCon >>8) & 0xFF;
      CAN.sendMsgBuf(DEV__CAN__CMD_2002, 0, frameLen, frameData);
      break;
    case DEV__CAN__CMD_2003:
      frameId = DEV__CAN__CMD_2003;
      frameData[0] = dataStore.x2003_data.gear & 0xFF;
      frameData[1] = (dataStore.x2003_data.gear >>8) & 0xFF;
      frameData[2] = dataStore.x2003_data.advance & 0xFF;
      frameData[3] = (dataStore.x2003_data.advance >>8) & 0xFF;
      frameData[4] = dataStore.x2003_data.injTime & 0xFF;
      frameData[5] = (dataStore.x2003_data.injTime>>8) & 0xFF;
      frameData[6] = dataStore.x2003_data.fuelCon & 0xFF;
      frameData[7] = (dataStore.x2003_data.fuelCon>>8) & 0xFF;
      CAN.sendMsgBuf(DEV__CAN__CMD_2003, 0, frameLen, frameData);
      break;
    case DEV__CAN__CMD_2004:
      frameId = DEV__CAN__CMD_2004;
      frameData[0] = dataStore.x2004_data.ana1 & 0xFF;
      frameData[1] = (dataStore.x2004_data.ana1>>8) & 0xFF;
      frameData[2] = dataStore.x2004_data.ana2 & 0xFF;
      frameData[3] = (dataStore.x2004_data.ana2>>8) & 0xFF;
      frameData[4] = dataStore.x2004_data.ana3 & 0xFF;
      frameData[5] = (dataStore.x2004_data.ana3>>8) & 0xFF;
      frameData[6] = dataStore.x2004_data.camAdv & 0xFF;
      frameData[7] = (dataStore.x2004_data.camAdv>>8) & 0xFF;
      CAN.sendMsgBuf(DEV__CAN__CMD_2004, 0, frameLen, frameData);
      break;
    case DEV__CAN__CMD_2005:
      frameId = DEV__CAN__CMD_2005;
      frameData[0] = dataStore.x2005_data.camTar & 0xFF;
      frameData[1] = (dataStore.x2005_data.camTar>>8) & 0xFF;
      frameData[2] = dataStore.x2005_data.camPwm & 0xFF;
      frameData[3] = (dataStore.x2005_data.camPwm>>8) & 0xFF;
      frameData[4] = dataStore.x2005_data.crankErr & 0xFF;
      frameData[5] = (dataStore.x2005_data.crankErr>>8) & 0xFF;
      frameData[6] = dataStore.x2005_data.camErr & 0xFF;
      frameData[7] = (dataStore.x2005_data.camErr>>8) & 0xFF;
      CAN.sendMsgBuf(DEV__CAN__CMD_2005, 0, frameLen, frameData);
      break;
    case DEV__CAN__CMD_2006:
      frameId = DEV__CAN__CMD_2006;
      frameData[0] = dataStore.x2006_data.camAdv2 & 0xFF;
      frameData[1] = (dataStore.x2006_data.camAdv2>>8) & 0xFF;
      frameData[2] = dataStore.x2006_data.camTar2 & 0xFF;
      frameData[3] = (dataStore.x2006_data.camTar2 >>8) & 0xFF;
      frameData[4] = dataStore.x2006_data.camPwm2 & 0xFF;
      frameData[5] = (dataStore.x2006_data.camPwm2>>8) & 0xFF;
      frameData[6] = dataStore.x2006_data.external5v & 0xFF;
      frameData[7] = (dataStore.x2006_data.external5v >>8) & 0xFF;
      CAN.sendMsgBuf(DEV__CAN__CMD_2006, 0, frameLen, frameData);
      break;
    case DEV__CAN__CMD_2007:
      frameId = DEV__CAN__CMD_2007;
      frameData[0] = dataStore.x2007_data.injDutyCycle & 0xFF;
      frameData[1] = (dataStore.x2007_data.injDutyCycle>>8) & 0xFF;
      frameData[2] = dataStore.x2007_data.lambdaPid & 0xFF;
      frameData[3] = (dataStore.x2007_data.lambdaPid>>8) & 0xFF;
      frameData[4] = dataStore.x2007_data.lambdaPidAsj & 0xFF;
      frameData[5] = (dataStore.x2007_data.lambdaPidAsj>>8) & 0xFF;
      frameLen = 6;
      CAN.sendMsgBuf(DEV__CAN__CMD_2007, 0, frameLen, frameData);
      break;
  }

  
  Serial.print("Sending - ID:");
  Serial.print(frameId);
  Serial.print(" Data: ");
  for(int i=0; i<frameLen; i++){
    Serial.print(frameData[i]);
    Serial.print(" ");
  }
  Serial.println();
  

}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
