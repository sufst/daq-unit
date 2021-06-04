/*************************************************************************//**
* @file srv__comms.cpp
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
#include "../sys/sys__manager.h"
#include "../sys/sys__datastore.h"
#include "srv__comms.h"

#if SYS__MANAGER__CAN_BUS_ENABLED
#include "../dev/dev__can__mcp2515.h"
#endif SYS__MANAGER__CAN_BUS_ENABLED

#if SYS__MANAGER__XBEE_ENABLED
#include "../dev/dev__xbee.h"
#endif SYS__MANAGER__XBEE_ENABLED

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
#if SYS__MANAGER__CAN_BUS_ENABLED

/*************************************************************************//**
* @brief Initialise MCP2515 CAN
* @param uint8_t pinCS Pin number of connection to SPI CS of MCP2515
* @return None
* @note
*****************************************************************************/
void srv__comms__can_init()
{  
  dev__can__mcp2515__init();

}


/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/

/*************************************************************************//**
* @brief Communications service process loop
* @param sys__datastore_t dataStore
* @param uint8_t canID
* @return None
* @note
*****************************************************************************/
void srv__comms__process(sys__datastore_t *dataStore)
{ 
  if(dataStore->x2000_data.hasReceived == true
    && dataStore->x2001_data.hasReceived == true 
    && dataStore->x2002_data.hasReceived == true
    && dataStore->x2006_data.hasReceived == true)
      dev__xbee_tx(DEV__XBEE__CMD_CORE);
    

  if(dataStore->x2003_data.hasReceived == true
    && dataStore->x2007_data.hasReceived == true)
      dev__xbee_tx(DEV__XBEE__CMD_POWER);

  if(dataStore->rideHeight.hasReceived_f == true
    && dataStore->rideHeight.hasReceived_r == true)
      dev__xbee_tx(DEV__XBEE__CMD_SUSPENSION);

  if(dataStore->accelerometers.hasReceivedXY_f == true
    && dataStore->accelerometers.hasReceivedZ_f == true
    && dataStore->accelerometers.hasReceived_r == true
    && dataStore->damperPots.hasReceived_f == true
    && dataStore->damperPots.hasReceived_r == true
    && dataStore->wheelSpeeds.hasReceived_f == true
    && dataStore->wheelSpeeds.hasReceived_r == true)
      dev__xbee_tx(DEV__XBEE__CMD_MISC);
    
    
}


#endif // SYS__MANAGER__CAN_BUS_ENABLED



