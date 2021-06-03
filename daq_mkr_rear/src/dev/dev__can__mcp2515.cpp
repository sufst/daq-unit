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
MCP_CAN CAN0(3);                               // Set CS to pin 10  

union 
{
  int16_t data;
  uint8_t dataBytes[2]; // Little Endian
}dev__can_data_16;

union 
{
  uint32_t data;
  uint8_t dataBytes[4]; // Little Endian
}dev__can_data_32;

/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
void dev__can__mcp2515__irq_handler(){
    dev__can__mcp2515_rx();
}

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

  pinMode(SYS__MANAGER__CAN_INT_PIN, INPUT);                            
  attachInterrupt(digitalPinToInterrupt(SYS__MANAGER__CAN_INT_PIN), dev__can__mcp2515__irq_handler, LOW);
  Serial.print("CAN INIT");
}


/*************************************************************************//*
* @brief Converts 2 uint8_t to int16_t
* @param None
* @return None
* @note
*****************************************************************************/
int16_t dev__bytes_2_int16(unsigned char byte1, unsigned char byte2){
    dev__can_data_16.dataBytes[0] = byte1;
    dev__can_data_16.dataBytes[1] = byte2;
    return dev__can_data_16.data;
}

/*************************************************************************//*
* @brief Converts 4 uint8_t to uint32_t
* @param None
* @return None
* @note
*****************************************************************************/
uint32_t dev__bytes_2_uint32(unsigned char byte1, unsigned char byte2, unsigned char byte3, unsigned char byte4){
    dev__can_data_32.dataBytes[0] = byte1;
    dev__can_data_32.dataBytes[1] = byte2;
    dev__can_data_32.dataBytes[2] = byte3;
    dev__can_data_32.dataBytes[3] = byte4;
    return dev__can_data_32.data;
}




/*************************************************************************//**
* @brief Communications service process loop
* @param None
* @return None
* @note
*****************************************************************************/
void dev__can__mcp2515_rx()
{   
  long unsigned int can_id;
  unsigned char len = 0;
  unsigned char rxBuf[8];
  CAN0.readMsgBuf(&can_id, &len, rxBuf);
  can_id = can_id & 0xFFFF;

  Serial.print("Received ID:");
  Serial.print(can_id);
  switch(can_id){
    case DEV__CAN__CMD_DAMPER:{            
      sys__datastore.damperPots.data_fl = dev__bytes_2_uint32(rxBuf[0], rxBuf[1], rxBuf[2], rxBuf[3]);
      sys__datastore.damperPots.data_fr = dev__bytes_2_uint32(rxBuf[4], rxBuf[5], rxBuf[6], rxBuf[7]);
      sys__datastore.damperPots.hasReceived_f = true;
      Serial.print(" -\tDamper Pots Front Left:");
      Serial.print(sys__datastore.damperPots.data_fl);
      Serial.print(" -\tDamper Pots Front Right:");
      Serial.println(sys__datastore.damperPots.data_fr);
      break; 
    }
    case DEV__CAN__CMD_WHEEL_SPEED:{            
      sys__datastore.wheelSpeeds.data_fl = dev__bytes_2_uint32(rxBuf[0], rxBuf[1], rxBuf[2], rxBuf[3]);
      sys__datastore.wheelSpeeds.data_fr = dev__bytes_2_uint32(rxBuf[4], rxBuf[5], rxBuf[6], rxBuf[7]);
      sys__datastore.wheelSpeeds.hasReceived_f = true;
      Serial.print(" -\tWheel Speed Front Left:");
      Serial.print(sys__datastore.wheelSpeeds.data_fl);
      Serial.print(" -\tWheel Speed Front Right:");
      Serial.println(sys__datastore.wheelSpeeds.data_fr);
      break; 
    }
    case DEV__CAN__CMD_RIDE_HEIGHT:{            
      sys__datastore.rideHeight.data_f = dev__bytes_2_uint32(rxBuf[0], rxBuf[1], rxBuf[2], rxBuf[3]);
      sys__datastore.rideHeight.hasReceived_f = true;
      Serial.print(" -\tRide Height Front:");
      Serial.print(sys__datastore.rideHeight.data_f);
      break; 
    }
    case DEV__CAN__CMD_2000:          
      sys__datastore.x2000_data.rpm = dev__bytes_2_int16(rxBuf[0], rxBuf[1]);
      sys__datastore.x2000_data.tps = dev__bytes_2_int16(rxBuf[2], rxBuf[3]);
      sys__datastore.x2000_data.waterTemp = dev__bytes_2_int16(rxBuf[4], rxBuf[5]);
      sys__datastore.x2000_data.airTemp = dev__bytes_2_int16(rxBuf[6], rxBuf[7]);     
      sys__datastore.x2000_data.hasReceived = true; 
      Serial.print(" -\tRPM:");
      Serial.print(sys__datastore.x2000_data.rpm);
      Serial.print("\tTPS: ");
      Serial.print(sys__datastore.x2000_data.tps);
      Serial.print("\tWater Temperature: ");
      Serial.print(sys__datastore.x2000_data.waterTemp);
      Serial.print("\tAir Temperature: ");
      Serial.println(sys__datastore.x2000_data.airTemp);
      break;       
    
    case DEV__CAN__CMD_2001: {           
      sys__datastore.x2001_data.maniPress = dev__bytes_2_int16(rxBuf[0], rxBuf[1]);
      sys__datastore.x2001_data.lambda = dev__bytes_2_int16(rxBuf[2], rxBuf[3]);
      sys__datastore.x2001_data.speed = dev__bytes_2_int16(rxBuf[4], rxBuf[5]);
      sys__datastore.x2001_data.oilPress = dev__bytes_2_int16(rxBuf[6], rxBuf[7]);
      sys__datastore.x2001_data.hasReceived = true;
      Serial.print(" -\tManifol Pressure:");
      Serial.print(sys__datastore.x2001_data.maniPress);
      Serial.print("\tLambda: ");
      Serial.print(sys__datastore.x2001_data.lambda);
      Serial.print("\tSpeed: ");
      Serial.print(sys__datastore.x2001_data.speed);
      Serial.print("\tOil Pressure: ");
      Serial.println(sys__datastore.x2001_data.oilPress);
      break;
    }
    case DEV__CAN__CMD_2002: {           
      sys__datastore.x2002_data.fuelPress = dev__bytes_2_int16(rxBuf[0], rxBuf[1]);
      sys__datastore.x2002_data.oilTemp = dev__bytes_2_int16(rxBuf[2], rxBuf[3]);
      sys__datastore.x2002_data.battery = dev__bytes_2_int16(rxBuf[4], rxBuf[5]);
      sys__datastore.x2002_data.fuelCon = dev__bytes_2_int16(rxBuf[6], rxBuf[7]);
      sys__datastore.x2002_data.hasReceived = true;
      Serial.print(" -\tFuel Pressure:");
      Serial.print(sys__datastore.x2002_data.fuelPress);
      Serial.print("\tOil Pressure: ");
      Serial.print(sys__datastore.x2002_data.oilTemp);
      Serial.print("\tBattery: ");
      Serial.print(sys__datastore.x2002_data.battery);
      Serial.print("\tFuel Consumption: ");
      Serial.println(sys__datastore.x2002_data.fuelCon);
      break;
    }
    case DEV__CAN__CMD_2003:{          
      sys__datastore.x2003_data.gear = dev__bytes_2_int16(rxBuf[0], rxBuf[1]);
      sys__datastore.x2003_data.advance = dev__bytes_2_int16(rxBuf[2], rxBuf[3]);
      sys__datastore.x2003_data.injTime = dev__bytes_2_int16(rxBuf[4], rxBuf[5]);
      sys__datastore.x2003_data.fuelCon = dev__bytes_2_int16(rxBuf[6], rxBuf[7]);
      sys__datastore.x2003_data.hasReceived = true;
      Serial.print(" -\tCurrent Gear:");
      Serial.print(sys__datastore.x2003_data.gear);
      Serial.print("\tAdvance: ");
      Serial.print(sys__datastore.x2003_data.advance);
      Serial.print("\tInjection Time: ");
      Serial.print(sys__datastore.x2003_data.injTime);
      Serial.print("\tFuel Consumption: ");
      Serial.println(sys__datastore.x2003_data.fuelCon);
      break;
    }
    /*case DEV__CAN__CMD_2004:{            
      sys__datastore.x2004_data.ana1 = dev__bytes_2_int16(rxBuf[0], rxBuf[1]);
      sys__datastore.x2004_data.ana2 = dev__bytes_2_int16(rxBuf[2], rxBuf[3]);
      sys__datastore.x2004_data.ana3 = dev__bytes_2_int16(rxBuf[4], rxBuf[5]);
      sys__datastore.x2004_data.camAdv = dev__bytes_2_int16(rxBuf[6], rxBuf[7]);
      sys__datastore.x2004_data.hasReceived = true;
      Serial.print(" -\tAnalogue 1:");
      Serial.print(sys__datastore.x2004_data.ana1);
      Serial.print("\tAnalogue 2: ");
      Serial.print(sys__datastore.x2004_data.ana2);
      Serial.print("\tAnalogue 3: ");
      Serial.print(sys__datastore.x2004_data.ana3);
      Serial.print("\tCam Advance: ");
      Serial.println(sys__datastore.x2004_data.camAdv);
      break;
    }
    case DEV__CAN__CMD_2005:{            
      sys__datastore.x2005_data.camTar = dev__bytes_2_int16(rxBuf[0], rxBuf[1]);
      sys__datastore.x2005_data.camPwm = dev__bytes_2_int16(rxBuf[2], rxBuf[3]);
      sys__datastore.x2005_data.crankErr = dev__bytes_2_int16(rxBuf[4], rxBuf[5]);
      sys__datastore.x2005_data.camErr = dev__bytes_2_int16(rxBuf[6], rxBuf[7]);
      sys__datastore.x2005_data.hasReceived = true;
      Serial.print(" -\tCam Target:");
      Serial.print(sys__datastore.x2005_data.camTar);
      Serial.print("\tCam PWM: ");
      Serial.print(sys__datastore.x2005_data.camPwm);
      Serial.print("\tCrank Errors: ");
      Serial.print(sys__datastore.x2005_data.crankErr);
      Serial.print("\tCam Errors: ");
      Serial.println(sys__datastore.x2005_data.camErr);
      break;
    }*/
    case DEV__CAN__CMD_2006:{            
      sys__datastore.x2006_data.camAdv2 = dev__bytes_2_int16(rxBuf[0], rxBuf[1]);
      sys__datastore.x2006_data.camTar2 = dev__bytes_2_int16(rxBuf[2], rxBuf[3]);
      sys__datastore.x2006_data.camPwm2 = dev__bytes_2_int16(rxBuf[4], rxBuf[5]);
      sys__datastore.x2006_data.external5v = dev__bytes_2_int16(rxBuf[6], rxBuf[7]);
      sys__datastore.x2006_data.hasReceived = true;
      Serial.print(" -\tCam Advance 2:");
      Serial.print(sys__datastore.x2006_data.camAdv2);
      Serial.print("\tCam Target 2: ");
      Serial.print(sys__datastore.x2006_data.camTar2);
      Serial.print("\tCam PWM 2: ");
      Serial.print(sys__datastore.x2006_data.camPwm2);
      Serial.print("\tExternal 5V: ");
      Serial.println(sys__datastore.x2006_data.external5v);
      break;
    }
    case DEV__CAN__CMD_2007:{            
      sys__datastore.x2007_data.injDutyCycle = dev__bytes_2_int16(rxBuf[0], rxBuf[1]);
      sys__datastore.x2007_data.lambdaPid = dev__bytes_2_int16(rxBuf[2], rxBuf[3]);
      sys__datastore.x2007_data.lambdaPidAdj = dev__bytes_2_int16(rxBuf[4], rxBuf[5]);
      sys__datastore.x2007_data.hasReceived = true;
      Serial.print(" -\tInjection Duty Cycle:");
      Serial.print(sys__datastore.x2007_data.injDutyCycle);
      Serial.print("\tLambda PID: ");
      Serial.print(sys__datastore.x2007_data.lambdaPid);
      Serial.print("\tLambda PID Adjustment: ");
      Serial.println(sys__datastore.x2007_data.lambdaPidAdj); 
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
