/*************************************************************************//**
* @file sys__datastore.h
* @brief System datastore
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
#ifndef CONTROLLER_V2_SYS__DATASTORE_H
#define CONTROLLER_V2_SYS__DATASTORE_H
/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
#include "Arduino.h"

#include "sys__manager.h"

/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
#if SYS__MANAGER__DAMPER_POTS_ENABLED
typedef struct
{
    uint8_t tag;
    uint32_t timestamp;
    uint32_t data;
} sys__datastore__damper_pots_save_t;
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__ACCELEROMETERS_ENABLED
typedef struct
{
    uint8_t tag;
    uint32_t dataX;
    uint32_t dataY;
    uint32_t dataZ;
    uint32_t timestamp;
} sys__datastore__accelerometer_save_t;
#endif // SYS__MANAGER__ACCELEROMETERS_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
typedef struct
{
    uint8_t tag;
    uint32_t data;
    uint32_t timestamp;
} sys__datastore__ride_height_save_t;
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

#if SYS__MANAGER__WHEEL_SPEEDS_ENABLED
typedef struct
{
    uint8_t tag;
    uint32_t data;
    uint32_t timestamp;
} sys__datastore__wheel_speed_save_t;
#endif // SYS__MANAGER__WHEEL_SPEEDS_ENABLED

#if SYS__MANAGER__FUEL_FLOW_ENABLED
typedef struct
{
    uint8_t tag;
    uint32_t data;
    uint32_t timestamp;
} sys__datastore__fuel_flow_save_t;
#endif // SYS__MANAGER__FUEL_FLOW_ENABLED

typedef struct
{
#if SYS__MANAGER__DAMPER_POTS_ENABLED
    // element0=left, element1=right
    sys__datastore__damper_pots_save_t damperPots[SYS__MANAGER__DAMPER_POTS_ATTACHED_AMT];
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__ACCELEROMETERS_ENABLED
    // element0=left, element1=right
    sys__datastore__accelerometer_save_t accelerometers[SYS__MANAGER__ACCELEROMETERS_ATTACHED_AMT];
#endif // SYS__MANAGER__ACCELEROMETERS_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
    sys__datastore__ride_height_save_t rideHeight;
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

#if SYS__MANAGER__WHEEL_SPEEDS_ENABLED
    sys__datastore__wheel_speed_save_t wheelSpeeds[SYS__MANAGER__WHEEL_SPEEDS_ATTACHED_AMT];
#endif // SYS__MANAGER__WHEEL_SPEEDS_ENABLED

#if SYS__MANAGER__FUEL_FLOW_ENABLED
    sys__datastore__fuel_flow_save_t fuelFlow;
#endif // SYS__MANAGER__FUEL_FLOW_ENABLED
} sys__datastore_t;


// ECU CAN Data Packets
typedef struct
{
    int16_t rpm;
    int16_t tps;
    int16_t waterTemp;
    int16_t airTemp;
} sys__datastore__x2000_t;

typedef struct
{
    int16_t maniPress = 1;
    int16_t lambda = 1;
    int16_t speed = 1;
    int16_t oilPress = 1;
} sys__datastore__x2001_t;

typedef struct
{
    int16_t fuelPress = 2;
    int16_t oilTemp = 2;
    int16_t battery = 2;
    int16_t fuelCon = 2;
} sys__datastore__x2002_t;

typedef struct
{
    int16_t gear = 3;
    int16_t advance = 3;
    int16_t injTime = 3;
    int16_t fuelCon = 3;
} sys__datastore__x2003_t;

typedef struct
{
    int16_t ana1 = 4;
    int16_t ana2 = 4;
    int16_t ana3 = 4;
    int16_t camAdv = 4;
} sys__datastore__x2004_t;

typedef struct
{
    int16_t camTar = 5;
    int16_t camPwm = 5;
    int16_t crankErr = 5;
    int16_t camErr = 5;
} sys__datastore__x2005_t;

typedef struct
{
    int16_t camAdv2 = 6;
    int16_t camTar2 = 6;
    int16_t camPwm2 = 6;
    int16_t external5v = 6;
} sys__datastore__x2006_t;

typedef struct
{
    int16_t injDutyCycle = 7;
    int16_t lambdaPid = 7;
    int16_t lambdaPidAsj = 7;
} sys__datastore__x2007_t;


typedef struct
{

  sys__datastore__x2000_t x2000_data;
  sys__datastore__x2001_t x2001_data;
  sys__datastore__x2002_t x2002_data;
  sys__datastore__x2003_t x2003_data;
  sys__datastore__x2004_t x2004_data;
  sys__datastore__x2005_t x2005_data;
  sys__datastore__x2006_t x2006_data;
  sys__datastore__x2007_t x2007_data;

} sys__ecu_datastore_t;

/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/
extern sys__datastore_t sys__datastore;
extern sys__ecu_datastore_t sys__ecu_datastore;

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif //CONTROLLER_V2_SYS__DATASTORE_H
/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
