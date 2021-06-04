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
      for (int i = 0; i < DEV__XBEE_FRAME_CORE_LENGTH; i++) {
        Serial.print(xbeePayload[i]);
        Serial.print(" ");
      }
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
      for (int i = 0; i < DEV__XBEE_FRAME_POWER_LENGTH; i++) {
        Serial.print(xbeePayload[i]);
        Serial.print(" ");
      }
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
      for (int i = 0; i < DEV__XBEE_FRAME_SUS_LENGTH; i++){
        Serial.print(xbeePayload[i]);
        Serial.print(" ");
      }         
      Serial.println();
      break;     
    } 
    

    case DEV__XBEE__CMD_MISC: {     
      xbeePayload[1] = DEV__XBEE__CMD_MISC;
      xbeePayload[2] = DEV__XBEE_MISC_BITFIELD >> 8;
      xbeePayload[3] = DEV__XBEE_MISC_BITFIELD & 0xFF;
      xbeePayload[4] = (sys__datastore.accelerometers.dataX_f >> 24) & 0xFF;
      xbeePayload[5] = (sys__datastore.accelerometers.dataX_f >> 16) & 0xFF;
      xbeePayload[6] = (sys__datastore.accelerometers.dataX_f >> 8) & 0xFF;    
      xbeePayload[7] = sys__datastore.accelerometers.dataX_f & 0xFF;
      xbeePayload[8] = (sys__datastore.accelerometers.dataY_f >> 24) & 0xFF;
      xbeePayload[9] = (sys__datastore.accelerometers.dataY_f >> 16) & 0xFF;
      xbeePayload[10] = (sys__datastore.accelerometers.dataY_f >> 8) & 0xFF;    
      xbeePayload[11] = sys__datastore.accelerometers.dataY_f & 0xFF;
      xbeePayload[12] = (sys__datastore.accelerometers.dataZ_f >> 24) & 0xFF;
      xbeePayload[13] = (sys__datastore.accelerometers.dataZ_f >> 16) & 0xFF;
      xbeePayload[14] = (sys__datastore.accelerometers.dataZ_f >> 8) & 0xFF;    
      xbeePayload[15] = sys__datastore.accelerometers.dataZ_f & 0xFF;
      xbeePayload[16] = (sys__datastore.accelerometers.dataX_r >> 24) & 0xFF;
      xbeePayload[17] = (sys__datastore.accelerometers.dataX_r >> 16) & 0xFF;
      xbeePayload[18] = (sys__datastore.accelerometers.dataX_r >> 8) & 0xFF;    
      xbeePayload[19] = sys__datastore.accelerometers.dataX_r & 0xFF;
      xbeePayload[20] = (sys__datastore.accelerometers.dataY_r >> 24) & 0xFF;
      xbeePayload[21] = (sys__datastore.accelerometers.dataY_r >> 16) & 0xFF;
      xbeePayload[22] = (sys__datastore.accelerometers.dataY_r >> 8) & 0xFF;    
      xbeePayload[23] = sys__datastore.accelerometers.dataY_r & 0xFF;
      xbeePayload[24] = (sys__datastore.accelerometers.dataZ_r >> 24) & 0xFF;
      xbeePayload[25] = (sys__datastore.accelerometers.dataZ_r >> 16) & 0xFF;
      xbeePayload[26] = (sys__datastore.accelerometers.dataZ_r >> 8) & 0xFF;    
      xbeePayload[27] = sys__datastore.accelerometers.dataZ_r & 0xFF;

      xbeePayload[28] = (sys__datastore.damperPots.data_fl >> 24) & 0xFF;
      xbeePayload[29] = (sys__datastore.damperPots.data_fl >> 16) & 0xFF;
      xbeePayload[30] = (sys__datastore.damperPots.data_fl >> 8) & 0xFF;    
      xbeePayload[31] = sys__datastore.damperPots.data_fl & 0xFF;
      xbeePayload[32] = (sys__datastore.damperPots.data_fr >> 24) & 0xFF;
      xbeePayload[33] = (sys__datastore.damperPots.data_fr >> 16) & 0xFF;
      xbeePayload[34] = (sys__datastore.damperPots.data_fr >> 8) & 0xFF;    
      xbeePayload[35] = sys__datastore.damperPots.data_fr & 0xFF;
      xbeePayload[36] = (sys__datastore.damperPots.data_rl >> 24) & 0xFF;
      xbeePayload[37] = (sys__datastore.damperPots.data_rl >> 16) & 0xFF;
      xbeePayload[38] = (sys__datastore.damperPots.data_rl >> 8) & 0xFF;    
      xbeePayload[39] = sys__datastore.damperPots.data_rl & 0xFF;
      xbeePayload[40] = (sys__datastore.damperPots.data_rr >> 24) & 0xFF;
      xbeePayload[41] = (sys__datastore.damperPots.data_rr >> 16) & 0xFF;
      xbeePayload[42] = (sys__datastore.damperPots.data_rr >> 8) & 0xFF;    
      xbeePayload[43] = sys__datastore.damperPots.data_rr & 0xFF;

      xbeePayload[44] = (sys__datastore.wheelSpeeds.data_fl >> 24) & 0xFF;
      xbeePayload[45] = (sys__datastore.wheelSpeeds.data_fl >> 16) & 0xFF;
      xbeePayload[46] = (sys__datastore.wheelSpeeds.data_fl >> 8) & 0xFF;    
      xbeePayload[47] = sys__datastore.wheelSpeeds.data_fl & 0xFF;
      xbeePayload[48] = (sys__datastore.wheelSpeeds.data_fr >> 24) & 0xFF;
      xbeePayload[49] = (sys__datastore.wheelSpeeds.data_fr >> 16) & 0xFF;
      xbeePayload[50] = (sys__datastore.wheelSpeeds.data_fr >> 8) & 0xFF;    
      xbeePayload[51] = sys__datastore.wheelSpeeds.data_fr & 0xFF;
      xbeePayload[52] = (sys__datastore.wheelSpeeds.data_rl >> 24) & 0xFF;
      xbeePayload[53] = (sys__datastore.wheelSpeeds.data_rl >> 16) & 0xFF;
      xbeePayload[54] = (sys__datastore.wheelSpeeds.data_rl >> 8) & 0xFF;    
      xbeePayload[55] = sys__datastore.wheelSpeeds.data_rl & 0xFF;
      xbeePayload[56] = (sys__datastore.wheelSpeeds.data_rr >> 24) & 0xFF;
      xbeePayload[57] = (sys__datastore.wheelSpeeds.data_rr >> 16) & 0xFF;
      xbeePayload[58] = (sys__datastore.wheelSpeeds.data_rr >> 8) & 0xFF;    
      xbeePayload[59] = sys__datastore.wheelSpeeds.data_rr & 0xFF;

      sys__datastore.accelerometers.hasReceivedXY_f = false;
      sys__datastore.accelerometers.hasReceivedZ_f = false;
      sys__datastore.accelerometers.hasReceived_r = false;
      sys__datastore.damperPots.hasReceived_f = false;
      sys__datastore.damperPots.hasReceived_r = false;
      sys__datastore.wheelSpeeds.hasReceived_f = false;
      sys__datastore.wheelSpeeds.hasReceived_r = false;

      for (int i = 0; i < DEV__XBEE_FRAME_MISC_LENGTH; i++) 
        Serial1.write(xbeePayload[i]);
      Serial.print("XBEE Transmitting Misc Frame: ");
      for (int i = 0; i < DEV__XBEE_FRAME_MISC_LENGTH; i++){
        Serial.print(xbeePayload[i]);
        Serial.print(" ");
      }         
      Serial.println();
      break;     
    }
  }
}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
