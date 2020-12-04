/*************************************************************************//**
* @file dev__fchmppic.h
* @brief Flow sensor FCH-M-PP-LC currently used for fuel flow rate.
* @note
* @author nrs1g15@soton.ac.uk
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

#include "dev__fchmpplc.h"

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
* @brief Initialise the flow sensor fchmpplc with interrupt pin and interrupt handler.
* @param dev__fchmpplc__obj_t* obj The fchmpplc object to init.
* @return None
* @note
*****************************************************************************/
void dev__fchmpplc__init(dev__fchmpplc__obj_t* obj)
{
    pinMode(obj->intPin, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(obj->intPin), obj->handler, FALLING);
}

/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/

