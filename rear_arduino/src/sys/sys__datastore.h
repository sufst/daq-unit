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

} sys__datastore_t;
/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/
extern sys__datastore_t sys__datastore;

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
