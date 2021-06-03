/*************************************************************************//**
* @file dev__xbee.cpp
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
  include files
----------------------------------------------------------------------------*/
#include "dev__xbee.h"
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


/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/




/*************************************************************************//**
* @brief Communications service process loop
* @param None
* @return None
* @note
*****************************************************************************/
void dev__xbee_tx(int xbee_cmd)
{   
  uint8_t xbeePayload[DEV__XBEE_FRAME_CORE_LENGTH];
  xbeePayload[0] = DEV__XBEE_START_BYTE;
  
  switch(xbee_cmd){
    case DEV__XBEE__CMD_CORE: {     
      xbeePayload[1] = DEV__XBEE__CMD_CORE;
      xbeePayload[2] = DEV__XBEE_CORE_BITFIELD >> 8;
      xbeePayload[3] = DEV__XBEE_CORE_BITFIELD & 0xFF;
      xbeePayload[4] = sys__datastore.x2000_data.rpm >> 8;
      xbeePayload[5] = sys__datastore.x2000_data.rpm & 0xFF;
      xbeePayload[6] = sys__datastore.x2000_data.waterTemp >> 8;
      xbeePayload[7] = sys__datastore.x2000_data.waterTemp & 0xFF;
      xbeePayload[8] = sys__datastore.x2000_data.tps >> 8;
      xbeePayload[9] = sys__datastore.x2000_data.tps & 0xFF;
      xbeePayload[10] = sys__datastore.x2002_data.battery >> 8;
      xbeePayload[11] = sys__datastore.x2002_data.battery & 0xFF;
      xbeePayload[12] = sys__datastore.x2006_data.external5v >> 8;
      xbeePayload[13] = sys__datastore.x2006_data.external5v & 0xFF;
      xbeePayload[14] = (sys__datastore.fuelFlow.data >> 24) & 0xFF;
      xbeePayload[15] = (sys__datastore.fuelFlow.data >> 16) & 0xFF;
      xbeePayload[16] = (sys__datastore.fuelFlow.data >> 8) & 0xFF;    
      xbeePayload[17] = sys__datastore.fuelFlow.data & 0xFF;
      xbeePayload[18] = sys__datastore.x2001_data.lambda >> 8; 
      xbeePayload[19] = sys__datastore.x2001_data.lambda & 0xFF;
      xbeePayload[20] = sys__datastore.x2001_data.speed >> 8; 
      xbeePayload[21] = sys__datastore.x2001_data.speed & 0xFF;

      sys__datastore.x2000_data.hasReceived = false;
      sys__datastore.x2001_data.hasReceived = false;
      sys__datastore.x2002_data.hasReceived = false;
      sys__datastore.fuelFlow.hasReceived = false;

      for (int i = 0; i < DEV__XBEE_FRAME_CORE_LENGTH; i++) 
        Serial1.write(xbeePayload[i]);
      Serial.print("XBEE Transmitting Core Frame: ");
      for (int i = 0; i < DEV__XBEE_FRAME_CORE_LENGTH; i++) 
        Serial.print(xbeePayload[i]);
      Serial.println();
      break;     
    }  

    case DEV__XBEE__CMD_AERO:{
      /*
        TODO - EVO SCANNER?
      */
     break;
    }

    case DEV__XBEE__CMD_DIAGNOSTIC:{
      /*
        TODO - STATUS?
      */
      break;
    }

    case DEV__XBEE__CMD_POWER: {     
      xbeePayload[1] = DEV__XBEE__CMD_POWER;
      xbeePayload[2] = DEV__XBEE_POWER_BITFIELD >> 8;
      xbeePayload[3] = DEV__XBEE_POWER_BITFIELD & 0xFF;
      xbeePayload[4] = sys__datastore.x2003_data.injTime >> 8;
      xbeePayload[5] = sys__datastore.x2003_data.injTime & 0xFF;
      xbeePayload[6] = sys__datastore.x2007_data.injDutyCycle >> 8;
      xbeePayload[7] = sys__datastore.x2007_data.injDutyCycle & 0xFF;
      xbeePayload[8] = sys__datastore.x2007_data.lambdaPidAdj >> 8;
      xbeePayload[9] = sys__datastore.x2007_data.lambdaPidAdj& 0xFF;
      xbeePayload[10] = sys__datastore.x2007_data.lambdaPid >> 8;
      xbeePayload[11] = sys__datastore.x2007_data.lambdaPid  & 0xFF;
      xbeePayload[12] = sys__datastore.x2003_data.advance >> 8;
      xbeePayload[13] = sys__datastore.x2003_data.advance & 0xFF;

      sys__datastore.x2003_data.hasReceived = false;
      sys__datastore.x2007_data.hasReceived = false;

      for (int i = 0; i < DEV__XBEE_FRAME_POWER_LENGTH; i++) 
        Serial1.write(xbeePayload[i]);
      Serial.print("XBEE Transmitting Power Frame: ");
      for (int i = 0; i < DEV__XBEE_FRAME_POWER_LENGTH; i++) 
        Serial.print(xbeePayload[i]);
      Serial.println();
      break;     
    }


    case DEV__XBEE__CMD_SUSPENSION: {     
      xbeePayload[1] = DEV__XBEE__CMD_POWER;
      xbeePayload[2] = DEV__XBEE_POWER_BITFIELD >> 8;
      xbeePayload[3] = DEV__XBEE_POWER_BITFIELD & 0xFF;
      xbeePayload[4] = (sys__datastore.rideHeight.data_f >> 24) & 0xFF;
      xbeePayload[5] = (sys__datastore.rideHeight.data_f >> 16) & 0xFF;
      xbeePayload[6] = (sys__datastore.rideHeight.data_f >> 8) & 0xFF;    
      xbeePayload[7] = sys__datastore.rideHeight.data_f & 0xFF;
      xbeePayload[8] = (sys__datastore.rideHeight.data_r >> 24) & 0xFF;
      xbeePayload[9] = (sys__datastore.rideHeight.data_r >> 16) & 0xFF;
      xbeePayload[10] = (sys__datastore.rideHeight.data_r >> 8) & 0xFF;    
      xbeePayload[11] = sys__datastore.rideHeight.data_r & 0xFF;

      sys__datastore.rideHeight.hasReceived_f = false;
      sys__datastore.rideHeight.hasReceived_r = false;

      for (int i = 0; i < DEV__XBEE_FRAME_SUS_LENGTH; i++) 
        Serial1.write(xbeePayload[i]);
      Serial.print("XBEE Transmitting Suspension Frame: ");
      for (int i = 0; i < DEV__XBEE_FRAME_SUS_LENGTH; i++) 
        Serial.print(xbeePayload[i]);
      Serial.println();
      break;     
    } 
    
  }

  
  /*
  
    SEND DATA TO XBEE  

  */
}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
