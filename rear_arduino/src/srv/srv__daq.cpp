/*************************************************************************//**
* @file srv__daq.cpp
* @brief DAQ service layer
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
#include "srv__daq.h"

#include "../sys/sys__manager.h"
#include "../sys/sys__datastore.h"

#if SYS__MANAGER__DAMPER_POTS_ENABLED
#include "../dev/dev__damper__pots.h"
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__ACCELEROMETERS_ENABLED
#include "../dev/dev__accelerometer.h"
#endif // SYS__MANAGER__ACCELEROMETERS_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
#include "../dev/dev__ride__height.h"
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

#if SYS__MANAGER__WHEEL_SPEEDS_ENABLED
#include "../dev/dev__wheel__speed.h"
#endif // SYS__MANAGER__WHEEL_SPEEDS_ENABLED

#if SYS__MANAGER__FUEL_FLOW_ENABLED
#include "../dev/dev__fuel__flow.h"
#endif // SYS__MANAGER__FUEL_FLOW_ENABLED

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
#if SYS__MANAGER__DAMPER_POTS_ENABLED
static dev__damper__pots__obj_t dev__damper__pots__obj[SYS__MANAGER__DAMPER_POTS_ATTACHED_AMT];
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__ACCELEROMETERS_ENABLED
static dev__accelerometer__obj_t dev__accelerometers__obj[SYS__MANAGER__ACCELEROMETERS_ATTACHED_AMT];
#endif // SYS__MANAGER__ACCELEROMETERS_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
static dev__ride__height__obj_t dev__ride__height__obj;
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

#if SYS__MANAGER__WHEEL_SPEEDS_ENABLED
static dev__wheel__speed__obj_t dev__wheel__speeds__obj[SYS__MANAGER__WHEEL_SPEEDS_ATTACHED_AMT];
#endif // SYS__MANAGER__WHEEL_SPEEDS_ENABLED

#if SYS__MANAGER__FUEL_FLOW_ENABLED
static dev__fuel__flow__obj_t dev__fuel__flow__obj;
#endif // SYS__MANAGER__FUEL_FLOW_ENABLED
/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
#if SYS__MANAGER__DAMPER_POTS_ENABLED
/*************************************************************************//**
* @brief Initialise damper pots
* @param uint16_t ms Damper pots daq frequency
* @param uint8_t *pins Damper pot pins
* @return None
* @note
*****************************************************************************/
void srv__daq__damper_pots_init(uint16_t ms, uint8_t *pins)
{
    for (uint8_t i = 0; i < SYS__MANAGER__DAMPER_POTS_ATTACHED_AMT; i++)
    {
        dev__damper__pots__obj[i].pin = pins[i];
        dev__damper__pots__init(&dev__damper__pots__obj[i]);
    }
}
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__ACCELEROMETERS_ENABLED
/*************************************************************************//**
* @brief Initialise accelerometers
* @param uint8_t *pins Accelerometer pins: x1, y1, z1, x2, y2, z2
* @return None
* @note
*****************************************************************************/
void srv__daq__accelerometers_init(uint8_t *pins)
{
    for (uint8_t i = 0; i < SYS__MANAGER__ACCELEROMETERS_ATTACHED_AMT; i++)
    {
        dev__accelerometers__obj[i].pinX = pins[i+(i*SYS__MANAGER__ACCELEROMETER_ATTACHED_PINS)];
        dev__accelerometers__obj[i].pinY = pins[i+1+(i*SYS__MANAGER__ACCELEROMETER_ATTACHED_PINS)];
        dev__accelerometers__obj[i].pinZ = pins[i+2+(i*SYS__MANAGER__ACCELEROMETER_ATTACHED_PINS)];
        dev__accelerometer__init(&dev__accelerometers__obj[i]);
    }
}
#endif // SYS__MANAGER__ACCELEROMETER_ENABLED


#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
/*************************************************************************//**
* @brief Initialise ride height sensor
* @param uint8_t pins Ride height pin
* @return None
* @note
*****************************************************************************/
void srv__daq__ride_height_init(uint8_t pin)
{
    dev__ride__height__obj.pin = pin;
    dev__ride__height__init(&dev__ride__height__obj);
}
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED


#if SYS__MANAGER__WHEEL_SPEEDS_ENABLED
/*************************************************************************//**
* @brief Initialise wheel speed sensors
* @param uint8_t *pins Wheel speed pins
* @return None
* @note
*****************************************************************************/
void srv__daq__wheel_speeds_init(uint8_t *pins)
{
    for (uint8_t i = 0; i < SYS__MANAGER__WHEEL_SPEEDS_ATTACHED_AMT; i++)
    {
        dev__wheel__speeds__obj[i].pin = pins[i];
        dev__wheel__speed__init(&dev__wheel__speeds__obj[i]);
    }
}
#endif // SYS__MANAGER__WHEEL_SPEEDS_ENABLED

#if SYS__MANAGER__FUEL_FLOW_ENABLED
/*************************************************************************//**
* @brief Initialise ride height sensor
* @param uint8_t pins Ride height pin
* @return None
* @note
*****************************************************************************/
void srv__daq__fuel_flow_init(uint8_t pin)
{
    dev__fuel__flow__obj.pin = pin;
    dev__fuel__flow__init(&dev__fuel__flow__obj);
}
#endif // SYS__MANAGER__FUEL_FLOW_ENABLED

/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/

/*************************************************************************//**
* @brief DAQ service process loop
* @param None
* @return None
* @note
*****************************************************************************/
void srv__daq__process(sys__datastore_t dataStore)
{ 
  // Read damper pots
  for(uint8_t i=0; i<SYS__MANAGER__DAMPER_POTS_ATTACHED_AMT; i++){
    dataStore.damperPots[i].data = dev__damper__pots__read_pot_uv(&dev__damper__pots__obj[i]);
  }

  // Read damper pots
  for(uint8_t i=0; i<SYS__MANAGER__ACCELEROMETERS_ATTACHED_AMT; i++){
    dataStore.accelerometers[i].dataX = dev__accelerometer_x__read_uv(&dev__accelerometers__obj[i]);
    dataStore.accelerometers[i].dataY = dev__accelerometer_y__read_uv(&dev__accelerometers__obj[i]);
    dataStore.accelerometers[i].dataZ = dev__accelerometer_z__read_uv(&dev__accelerometers__obj[i]);
  }

  // Read ride height
  dataStore.rideHeight.data = dev__ride__height__read_uv(&dev__ride__height__obj);

  // Read wheel speed
  for(uint8_t i=0; i<SYS__MANAGER__WHEEL_SPEEDS_ATTACHED_AMT; i++){
    dataStore.wheelSpeeds[i].data = dev__wheel_speed__read_uv(&dev__wheel__speeds__obj[i]);
  }

  // Read fuel flow
  dataStore.fuelFlow.data = dev__fuel__flow__read_uv(&dev__fuel__flow__obj);

}

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/


