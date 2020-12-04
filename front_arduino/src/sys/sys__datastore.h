/*************************************************************************//**
* @file sys__datastore.h
* @brief System datastore
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
#ifndef CONTROLLER_V2_SYS__DATASTORE_H
#define CONTROLLER_V2_SYS__DATASTORE_H
/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
#include "Arduino.h"

#include "sys__manager.h"
#include "../srv/srv__software__timer.h"
/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/
#define SYS__DATASTORE__STATUS_TAG_AMOUNT 3

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef enum
{
    SYS__DATASTORE_TAG_EMPTY = 0x00,
    SYS__DATASTORE__TAG_RPM,
    SYS__DATASTORE__TAG_TPS,
    SYS__DATASTORE__TAG_WATER_TEMP_C,
    SYS__DATASTORE__TAG_AIR_TEMP_C,
    SYS__DATASTORE__TAG_MANIFOLD_PRESS,
    SYS__DATASTORE__TAG_LAMBDA_X1000,
    SYS__DATASTORE__TAG_SPEED_KPH_X10,
    SYS__DATASTORE__TAG_OIL_PRESS_KPA,
    SYS__DATASTORE__TAG_FUEL_PRESS_KPA,
    SYS__DATASTORE__TAG_OIL_TEMP_C,
    SYS__DATASTORE__TAG_BATTERY_V_X10,
    SYS__DATASTORE__TAG_FUEL_COMP_LPHR_X10,
    SYS__DATASTORE__TAG_GEAR,
    SYS__DATASTORE__TAG_ADVANCE_DEG_X10,
    SYS__DATASTORE__TAG_INJECTION_TIME_MS_X100,
    SYS__DATASTORE__TAG_FUEL_COMP_PL_100KM_X10,
    SYS__DATASTORE__TAG_ANA1_MV,
    SYS__DATASTORE__TAG_ANA2_MV,
    SYS__DATASTORE__TAG_ANA3_MV,
    SYS__DATASTORE__TAG_CAM_ADVANCE_DEG_X10,
    SYS__DATASTORE__TAG_CAM_TARGET_DEG_X10,
    SYS__DATASTORE__TAG_CAM_PWM_PERC_X10,
    SYS__DATASTORE__TAG_CRANK_ERRORS_NR,
    SYS__DATASTORE__TAG_CAM_ERRORS_NR,
    SYS__DATASTORE__TAG_CAM_2_ADVANCE_DEG_X10,
    SYS__DATASTORE__TAG_CAM_2_TARGET_DEG_X10,
    SYS__DATASTORE__TAG_CAM_2_PWM_PERC_X10,
    SYS__DATASTORE__TAG_EXTERNAL_5V_MV,
    SYS__DATASTORE__TAG_INJECTION_DUTY_CYCLE_PERC,
    SYS__DATASTORE__TAG_LAMBDA_PID_TARGET_PERC_X10,
    SYS__DATASTORE__TAG_LAMBDA_PID_ADJ_PERC_X10,
    SYS__DATASTORE__TAG_ECU_SWITCHES_BIT_FIELD,
    SYS__DATASTORE__TAG_EVO_SCANN_SEN_1,
    SYS__DATASTORE__TAG_EVO_SCANN_SEN_2,
    SYS__DATASTORE__TAG_EVO_SCANN_SEN_3,
    SYS__DATASTORE__TAG_EVO_SCANN_SEN_4,
    SYS__DATASTORE__TAG_EVO_SCANN_SEN_5,
    SYS__DATASTORE__TAG_EVO_SCANN_SEN_6,
    SYS__DATASTORE__TAG_EVO_SCANN_SEN_7,
    SYS__DATASTORE__TAG_EVO_SCANN_SEN_8,
    SYS__DATASTORE__TAG_CAN_ERR,
    SYS__DATASTORE__TAG_DAMP_POT_1,
    SYS__DATASTORE__TAG_DAMP_POT_2,
    SYS__DATASTORE__TAG_DAMP_POT_3,
    SYS__DATASTORE__TAG_DAMP_POT_4,
    SYS__DATASTORE__TAG_DAMP_POT_5,
    SYS__DATASTORE__TAG_LAPTIMER,
    SYS__DATASTORE__TAG_WIRELESS_DAQ_REFRESH_MS,
    SYS__DATASTORE__TAG_YAW,
    SYS__DATASTORE__TAG_FUEL_FLOW,
    SYS__DATASTORE__TAG_BRAKE_PRESSURE,
    SYS__DATASTORE__TAG_RIDE_HEIGHT
} sys__datastore__tags_t;

typedef enum
{
    SYS__DATASTORE__STATUS_TAG_CONTROLLER = 0x01,
    SYS__DATASTORE__STATUS_TAG_SD_CARD,
    SYS__DATASTORE__STATUS_TAG_S60_ECU
} sys__datastore__status_tags_t;

typedef struct
{
    uint8_t tag;
    uint32_t timestamp;
    uint16_t data;
#if SYS__MANAGER__WIRELESS_ENABLED
    bool wirelessDaq;
#endif // SYS__MANAGER__WIRELESS_ENABLED
} sys__datastore__ecu_save_t;

#if SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED

typedef struct
{
    uint8_t tag;
    uint32_t timestamp;
    uint32_t data;
#if SYS__MANAGER__WIRELESS_ENABLED
    bool wirelessDaq;
#endif // SYS__MANAGER__WIRELESS_ENABLED
} sys__datastore__evo_scanner_save_t;

#endif // SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED

#if SYS__MANAGER__LAP_TIMER_ENABLED

typedef struct
{
    uint32_t timestamp;
#if SYS__MANAGER__WIRELESS_ENABLED
    bool wirelessDaq;
#endif // SYS__MANAGER__WIRELESS_ENABLED
    uint8_t debounceS;
} sys__datastore__laptimer_save_t;

#endif // SYS__MANAGER__LAP_TIMER_ENABLED

#if SYS__MANAGER__DAMPER_POTS_ENABLED

typedef struct
{
    uint8_t tag;
    uint32_t timestamp;
    uint32_t data;
#if SYS__MANAGER__WIRELESS_ENABLED
    bool wirelessDaq;
#endif // SYS__MANAGER__WIRELESS_ENABLED
} sys__datastore__damper_pots_save_t;

#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__YAW_SENSOR_ENABLED

typedef struct
{
    uint8_t tag;
    uint32_t timestamp;
    int32_t data;
#if SYS__MANAGER__WIRELESS_ENABLED
    bool wirelessDaq;
#endif // SYS__MANAGER__WIRELESS_ENABLED
} sys__datastore__yaw_sensor_save_t;

#endif // SYS__MANAGER__YAW_SENSOR_ENABLED

#if SYS__MANAGER__WIRELESS_ENABLED

typedef struct
{
    uint8_t wirelessDaqRefreshMs;
    srv__software__timer__handle timerHandle;
} sys__datastore__wireless_save_t;

#endif // SYS__MANAGER__WIRELESS_ENABLED

#if SYS__MANAGER__FCHMPPLC_ENABLED

typedef struct
{
    uint8_t tag;
    uint16_t data;
    uint32_t timestamp;
#if SYS__MANAGER__WIRELESS_ENABLED
    bool wirelessDaq;
#endif // SYS__MANAGER__WIRELESS_ENABLED
} sys__datastore__fchmpplc_save_t;

#endif // SYS__MANAGER__FCHMPPLC_ENABLED

#if SYS__MANAGER__BRAKE_PRESS_ENABLED

typedef struct
{
    uint8_t tag;
    uint32_t data;
    uint32_t timestamp;
#if SYS__MANAGER__WIRELESS_ENABLED
    bool wirelessDaq;
#endif // SYS__MANAGER__WIRELESS_ENABLED
} sys__datastore__brake_press_save_t;

#endif // SYS__MANAGER__BRAKE_PRESS_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED

typedef struct
{
    uint8_t tag;
    uint32_t timestamp;
    uint32_t data;
#if SYS__MANAGER__WIRELESS_ENABLED
    bool wirelessDaq;
#endif // SYS__MANAGER__WIRELESS_ENABLED
} sys__datastore__ride_height_save_t;

#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

typedef struct
{
    sys__datastore__ecu_save_t ecu[SYS__MANAGER__ECU_SENSOR_CNT];
#if SYS__MANAGER__LAP_TIMER_ENABLED
    sys__datastore__laptimer_save_t laptimer;
#endif // SYS__MANAGER__LAP_TIMER_ENABLED

#if SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED
    sys__datastore__evo_scanner_save_t evo[SYS__MANAGER__EVO_SCANN_SENSORS_ATTACHED_AMT];
#endif // SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED

#if SYS__MANAGER__DAMPER_POTS_ENABLED
    sys__datastore__damper_pots_save_t damperPots[SYS__MANAGER__DAMPER_POTS_ATTACHED_AMT];
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__WIRELESS_ENABLED
    sys__datastore__wireless_save_t wireless;
#endif // SYS__MANAGER__WIRELESS_ENABLED

#if SYS__MANAGER__YAW_SENSOR_ENABLED
    sys__datastore__yaw_sensor_save_t yaw;
#endif // SYS__MANAGER__WIRELESS_ENABLED

#if SYS__MANAGER__FCHMPPLC_ENABLED
    sys__datastore__fchmpplc_save_t fchmpplc;
#endif // SYS__MANAGER__FCHMPPLC_ENABLED

#if SYS__MANAGER__BRAKE_PRESS_ENABLED
    sys__datastore__brake_press_save_t brakePressure;
#endif // SYS__MANAGER__BRAKE_PRESS_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
    sys__datastore__ride_height_save_t rideHeight;
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

    uint8_t status[SYS__DATASTORE__STATUS_TAG_AMOUNT + 1];
    uint32_t lastEcuMessageSeenTimeMs;

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
