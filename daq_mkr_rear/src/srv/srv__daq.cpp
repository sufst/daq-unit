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

/*#if SYS__MANAGER__ACCELEROMETERS_ENABLED
#include "../dev/dev__accelerometer.h"
#endif // SYS__MANAGER__ACCELEROMETERS_ENABLED */

#if SYS__MANAGER__DAMPER_POTS_ENABLED
#include "../dev/dev__damper__pots.h"
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED


#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
#include "../dev/dev__ride__height.h"
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

#if SYS__MANAGER__FUEL_FLOW_ENABLED
#include "../dev/dev__fuel__flow.h"
#endif // SYS__MANAGER__FUEL_FLOW_ENABLED 

#if SYS__MANAGER__WHEEL_SPEEDS_ENABLED
#include "../dev/dev__wheel__speed.h"
#endif // SYS__MANAGER__WHEEL_SPEEDS_ENABLED



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
/*#if SYS__MANAGER__ACCELEROMETERS_ENABLED
static dev__accelerometer__obj_t dev__accelerometers__obj[SYS__MANAGER__ACCELEROMETERS_ATTACHED_AMT];
#endif // SYS__MANAGER__ACCELEROMETERS_ENABLED
*/

#if SYS__MANAGER__DAMPER_POTS_ENABLED
static dev__damper__pot__obj_t dev__damper__pots__obj[SYS__MANAGER__DAMPER_POTS_ATTACHED_AMT];
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
static dev__ride__height__obj_t dev__ride__height__obj;
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

#if SYS__MANAGER__FUEL_FLOW_ENABLED
static dev__fuel__flow__obj_t dev__fuel__flow__obj;
#endif // SYS__MANAGER__FUEL_FLOW_ENABLED 

#if SYS__MANAGER__WHEEL_SPEEDS_ENABLED
static dev__wheel__speed__obj_t dev__wheel__speeds__obj[SYS__MANAGER__WHEEL_SPEEDS_ATTACHED_AMT];
#endif // SYS__MANAGER__WHEEL_SPEEDS_ENABLED


/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
#if SYS__MANAGER__DAMPER_POTS_ENABLED
/*************************************************************************//**
* @brief Initialise damper pots
* @param uint8_t *pins Damper pot pins
* @return None
* @note
*****************************************************************************/
void srv__daq__damper_pots_init(uint8_t *pins)
{
    for (uint8_t i = 0; i < SYS__MANAGER__DAMPER_POTS_ATTACHED_AMT; i++)
    {
        dev__damper__pots__obj[i].pin = pins[i];
        dev__damper__pot__init(&dev__damper__pots__obj[i]);
    }
}
#endif // SYS__MANAGER__WHEEL_SPEEDS_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
/*************************************************************************//**
* @brief Initialise ride height
* @param uint8_t pin Ride height pin
* @return None
* @note
*****************************************************************************/
void srv__daq__ride_height_init(uint8_t pin)
{
    dev__ride__height__obj.pin = pin;
    dev__ride__height__init(&dev__ride__height__obj);
}
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

#if SYS__MANAGER__FUEL_FLOW_ENABLED
/*************************************************************************//**
* @brief Initialise fuel flow
* @param uint8_t pin Fuel flow pin
* @return None
* @note
*****************************************************************************/
void srv__daq__fuel_flow_init(uint8_t pin)
{
    dev__fuel__flow__obj.pin = pin;
    dev__fuel__flow__init(&dev__fuel__flow__obj);
}
#endif // SYS__MANAGER__FUEL_FLOW_ENABLED

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



/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/

/*************************************************************************//**
* @brief DAQ service process loop
* @param None
* @return None
* @note
*****************************************************************************/
void srv__daq__process(sys__datastore_t *dataStore)
{ 
  Serial.print("Damper Pots Rear Left - Right: ");
  dataStore->damperPots.data_rl = dev__damper_pot__read_uv(&dev__damper__pots__obj[0]);
  dataStore->damperPots.data_rr = dev__damper_pot__read_uv(&dev__damper__pots__obj[1]);
  dataStore->damperPots.hasReceived_r = true;
  Serial.print(dataStore->damperPots.data_rl);
  Serial.println(dataStore->damperPots.data_rr);


  Serial.print("Ride Height Rear: ");
  dataStore->rideHeight.data_r = dev__ride_height__read_uv(&dev__ride__height__obj);
  dataStore->rideHeight.hasReceived_r = true;
  Serial.println(dataStore->rideHeight.data_r);

  Serial.print("Fuel Flow: ");
  dataStore->fuelFlow.data = dev__fuel_flow__read_uv(&dev__fuel__flow__obj);
  dataStore->fuelFlow.hasReceived = true;
  Serial.println(dataStore->fuelFlow.data);

  Serial.print("Wheel Speed Rear Left - Right: ");
  dataStore->wheelSpeeds.data_rl = dev__wheel_speed__read_uv(&dev__wheel__speeds__obj[0]);
  dataStore->wheelSpeeds.data_rr = dev__wheel_speed__read_uv(&dev__wheel__speeds__obj[1]);
  dataStore->wheelSpeeds.hasReceived_r = true;
  Serial.print(dataStore->wheelSpeeds.data_rl);
  Serial.println(dataStore->wheelSpeeds.data_rr);
    
  delay(SYS__MANAGER__DAQ_SAMPLE_PERIOD);

}

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/


