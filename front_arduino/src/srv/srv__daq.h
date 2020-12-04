/*************************************************************************//**
* @file srv__daq.h
* @brief DAQ service layer
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
  @brief
----------------------------------------------------------------------------*/

#ifndef CONTROLLER_V2_SRV__DAQ_H
#define CONTROLLER_V2_SRV__DAQ_H
/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
#include "Arduino.h"

#include "../sys/sys__manager.h"
/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/
#if SYS__MANAGER__SD_ENABLED

#define SRV__DAQ__SD_TX_BLOCK_BUFFER_LEN 10
#define SRV__DAQ__SD_BYTES_PER_BLOCK_WITH_OVERHEAD 160
#define SRV__DAQ__SD_BYTES_PER_BLOCK 128
#define SRV__DAQ__SD_FLUSH_BYTE_COUNT 1024

#endif // SYS__MANAGER__SD_ENABLED

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef enum
{
    SRV__DAQ__ERROR_NONE,
    SRV__DAQ__ERROR
} srv__daq__state_t;

/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
#if SYS__MANAGER__DAMPER_POTS_ENABLED

void srv__daq__damper_pots_init(uint16_t ms, uint8_t *pins);

#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__LAP_TIMER_ENABLED

void srv__daq__lap_timer_init(uint8_t intPin, uint8_t drivePin, uint16_t debounceMs);

void srv__daq__lap_timer_set_debounce_ms(uint16_t debounceMs);

#endif // SYS__MANAGER__LAP_TIMER_ENABLED

#if SYS__MANAGER__SD_ENABLED

srv__daq__state_t srv__daq__sd_init(uint8_t csPin);

uint8_t srv__daq__get_sd_state();

void srv__daq__sd_write_tag_data(uint8_t tag, void *data, void *timestamp);

#endif // SYS__MANAGER__SD_ENABLED

#if SYS__MANAGER__YAW_SENSOR_ENABLED

void srv__daq__yaw_sensor_init(uint8_t pin, uint16_t intervalMs);

#endif // SYS__MANAGER__YAW_SENSOR_ENABLED

#if SYS__MANAGER__FCHMPPLC_ENABLED

void srv__daq__fchmpplc_init(uint8_t intPin, uint16_t updateMs);

#endif // SYS__MANAGER__FCHMPPLC_ENABLED

#if SYS__MANAGER__BRAKE_PRESS_ENABLED

void srv__daq__brake_pressure_init(uint8_t pin, uint16_t sampleMs);

#endif // SYS__MANAGER__BRAKE_PRESS_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED

void srv__daq__ride_height_init(uint16_t ms, uint8_t pin);

#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

void srv__daq__process();
/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif //CONTROLLER_V2_SRV__DAQ_H

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
