/*************************************************************************//**
* @file dev__accelerometer.h
* @brief device layer for linear 0-5V brake pressure sensor
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
#include "dev__accelerometer.h"

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/
#define DEV__ACCELEROMETER__ADC_CONVERSION_UV 488

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
* @brief Initialise the accelerometer
* @param dev__accelerometer__obj_t* obj Accelerometer device object
* @return None
* @note
*****************************************************************************/
void dev__accelerometer__init(dev__accelerometer__obj_t *obj)
{
    pinMode(obj->pinX, INPUT_PULLUP);
    pinMode(obj->pinY, INPUT_PULLUP);
    pinMode(obj->pinZ, INPUT_PULLUP);
    obj->conversionRate = DEV__ACCELEROMETER__ADC_CONVERSION_UV;
}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
