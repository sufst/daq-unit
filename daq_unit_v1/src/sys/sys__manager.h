/*************************************************************************//**
* @file sys__manager.h
* @brief Main system application
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
  @brief sys__manager.h holds all the common configurable compile options for the system
  To be modified, not specified yet //Piotr
----------------------------------------------------------------------------*/
#ifndef SYS__MANAGER_H
#define SYS__MANAGER_H

/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
#include "Arduino.h"

/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/
#define SYS__MANAGER__SERIAL_ENABLED 1
#define SYS__MANAGER__DEBUG_UART 0

#define SYS__MANAGER__STATUS_MSG_INTERVAL_MS 1000
#define SYS__MANAGER__STATUS_ECU_TIMEOUT_MS 5000

#define SYS__MANAGER__SD_ENABLED 1
#define SYS__MANAGER__SD_CS_PIN 4

#define SYS__MANAGER__DAMPER_POTS_ENABLED 1
#define SYS__MANAGER__DAMPER_POTS_ATTACHED_AMT 4
#define SYS__MANAGER__DAMPER_POT_1_PIN A8
#define SYS__MANAGER__DAMPER_POT_2_PIN A9
#define SYS__MANAGER__DAMPER_POT_3_PIN A10
#define SYS__MANAGER__DAMPER_POT_4_PIN A11
#define SYS__MANAGER__DAMPER_POT_5_PIN A0
#define SYS__MANAGER__DAMPER_POTS_POLL_MS 20

#define SYS__MANAGER__LAP_TIMER_ENABLED 1
#define SYS__MANAGER__LAP_TIMER_INT_PIN 20
#define SYS__MANAGER__LAP_TIMER_DRIVE_PIN 22
#define SYS__MANAGER__LAP_TIMER_DEFAULT_DEBOUNCE_MS 2000

#define SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED 1
#define SYS__MANAGER__EVO_SCANN_SENSORS_ATTACHED_AMT 8
#define SYS__MANAGER__EVO_SCANN_SEN_1_CONNECTED 1
#define SYS__MANAGER__EVO_SCANN_SEN_2_CONNECTED 1
#define SYS__MANAGER__EVO_SCANN_SEN_3_CONNECTED 1
#define SYS__MANAGER__EVO_SCANN_SEN_4_CONNECTED 1
#define SYS__MANAGER__EVO_SCANN_SEN_5_CONNECTED 1
#define SYS__MANAGER__EVO_SCANN_SEN_6_CONNECTED 1
#define SYS__MANAGER__EVO_SCANN_SEN_7_CONNECTED 1
#define SYS__MANAGER__EVO_SCANN_SEN_8_CONNECTED 1

#define SYS__MANAGER__WIRELESS_ENABLED 1
#define SYS__MANAGER__WIRELESS_RTS_PIN 28
#define SYS__MANAGER__WIRELESS_CTS_PIN 30
#define SYS__MANAGER__WIRELESS_UART 0
#define SYS__MANAGER__WIRELESS_TX_INTERVAL_MS 50
#define SYS__MANAGER__WIRELESS_BAUD_RATE 115200
#define SYS__MANAGER__WIRELESS_TARGET_ADDRESS_UPPER 0x0013A200
#define SYS__MANAGER__WIRELESS_TARGET_ADDRESS_LOWER 0x410AC922

#define SYS__MANAGER__CAN_BUS_ENABLED 1
#define SYS__MANAGER__CAN_BUS_ATTACHED_AMT 1
#define SYS__MANAGER__CAN_BUS_ECU 0
#define SYS__MANAGER__CAN_BUS_ECU_INT_PIN 2
#define SYS__MANAGER__CAN_BUS_ECU_CS_PIN 9
#define SYS__MANAGER__ECU_SENSOR_CNT 32

#define SYS__MANAGER__YAW_SENSOR_ENABLED 0
#define SYS__MANAGER__YAW_SENSOR_PIN A13
#define SYS__MANAGER__YAW_SENSOR_POLL_MS 20

#define SYS__MANAGER__DASH_ENABLED 1
#define SYS__MANAGER__DASH_UART 2
#define SYS__MANAGER__DASH_UPDATE_MS 20

#define SYS__MANAGER__FCHMPPLC_ENABLED 1
#define SYS__MANAGER__FCHMPPLC_INT_PIN 21
#define SYS__MANAGER__FCHMPPLC_MAX_SAMPLE_COUNT 100
#define SYS__MANAGER__FCHMPPLC_SAMPLE_TIMEOUT_MS 1000
#define SYS__MANAGER__FCHMPPLC_SAMPLE_MS 20

#define SYS__MANAGER__BRAKE_PRESS_ENABLED 1
#define SYS__MANAGER__BRAKE_PRESS_PIN 32
#define SYS__MANAGER__BRAKE_PRESS_SAMPLE_MS 20

#define SYS__MANAGER__RIDE_HEIGHT_ENABLED 1
#define SYS__MANAGER__RIDE_HEIGHT_PIN A15
#define SYS__MANAGER__RIDE_HEIGHT_POLL_MS 20

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
void sys__manager__init();

void sys__manager__process();
/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif //SYS__MANAGER_H
