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

#if SYS__MANAGER__ACCELEROMETER_ENABLED
#include "../dev/dev__accelerometer.h"
#endif // SYS__MANAGER__ACCELEROMETER_ENABLED 

#if SYS__MANAGER__DAMPER_POTS_ENABLED
#include "../dev/dev__damper__pots.h"
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED


#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
#include "../dev/dev__ride__height.h"
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

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
#if SYS__MANAGER__ACCELEROMETER_ENABLED
static dev__accelerometer__obj_t dev__accelerometer__obj[SYS__MANAGER__ACCELEROMETER_ATTACHED_AMT];
#endif // SYS__MANAGER__ACCELEROMETER_ENABLED


#if SYS__MANAGER__DAMPER_POTS_ENABLED
static dev__damper__pot__obj_t dev__damper__pots__obj[SYS__MANAGER__DAMPER_POTS_ATTACHED_AMT];
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
static dev__ride__height__obj_t dev__ride__height__obj;
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

#if SYS__MANAGER__WHEEL_SPEEDS_ENABLED
static dev__wheel__speed__obj_t dev__wheel__speeds__obj[SYS__MANAGER__WHEEL_SPEEDS_ATTACHED_AMT];
#endif // SYS__MANAGER__WHEEL_SPEEDS_ENABLED


/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
#if SYS__MANAGER__ACCELEROMETER_ENABLED
/*************************************************************************//**
* @brief Initialise accelerometer
* @param uint8_t *pins accelerometer pins
* @return None
* @note
*****************************************************************************/
void srv__daq__accelerometer_init(uint8_t *pins)
{
    for (uint8_t i = 0; i < SYS__MANAGER__ACCELEROMETER_ATTACHED_AMT; i++)
    {
        dev__accelerometer__obj[i].pin = pins[i];
        dev__accelerometer__init(&dev__accelerometer__obj[i]);
    }
}
#endif // SYS__MANAGER__ACCELOROMETER_ENABLED

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

  Serial.println("DAQ READ:");
  Serial.print("Accelerometer Front X - Y - Z: ");
  dataStore->accelerometer.dataX_f = dev__accelerometer__read_uv(&dev__accelerometer__obj[0]);
  dataStore->accelerometer.dataY_f = dev__accelerometer__read_uv(&dev__accelerometer__obj[1]);
  dataStore->accelerometer.dataZ_f = dev__accelerometer__read_uv(&dev__accelerometer__obj[2]);
  Serial.print(dataStore->accelerometer.dataX_f);
  Serial.print("\t");
  Serial.print(dataStore->accelerometer.dataY_f);
  Serial.print("\t");
  Serial.println(dataStore->accelerometer.dataZ_f);

  
  Serial.print("Damper Pots Front Left - Right: ");
  dataStore->damperPots.data_fl = dev__damper_pot__read_uv(&dev__damper__pots__obj[0]);
  dataStore->damperPots.data_fr = dev__damper_pot__read_uv(&dev__damper__pots__obj[1]);
  Serial.print(dataStore->damperPots.data_fl);
  Serial.print("\t");
  Serial.println(dataStore->damperPots.data_fr);

  Serial.print("Ride Height Front: ");
  dataStore->rideHeight.data_f = dev__ride_height__read_uv(&dev__ride__height__obj);
  Serial.println(dataStore->rideHeight.data_f);

  Serial.print("Wheel Speed Front Left - Right: ");
  dataStore->wheelSpeeds.data_fl = dev__wheel_speed__read_uv(&dev__wheel__speeds__obj[0]);
  dataStore->wheelSpeeds.data_fr = dev__wheel_speed__read_uv(&dev__wheel__speeds__obj[1]);
  Serial.print(dataStore->wheelSpeeds.data_fl);
  Serial.print("\t");
  Serial.println(dataStore->wheelSpeeds.data_fr);


  delay(SYS__MANAGER__DAQ_SAMPLE_PERIOD);

}

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/


