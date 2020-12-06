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

#if SYS__MANAGER__DAMPER_POTS_ENABLED
typedef struct
{
    uint8_t tag;
    uint32_t timestamp;
    uint32_t data;
} sys__datastore__damper_pots_save_t;
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__ACCELEROMETER_ENABLED
typedef struct
{
    uint8_t tag;
    uint32_t dataX;
    uint32_t dataY;
    uint32_t dataZ;
    uint32_t timestamp;
} sys__datastore__accelerometer_save_t;
#endif // SYS__MANAGER__ACCELEROMETER_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
typedef struct
{
    uint8_t tag;
    uint32_t data;
    uint32_t timestamp;
} sys__datastore__ride_height_save_t;
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

#if SYS__MANAGER__WHEEL_SPEED_ENABLED
typedef struct
{
    uint8_t tag;
    uint32_t data;
    uint32_t timestamp;
} sys__datastore__wheel_speed_save_t;
#endif // SYS__MANAGER__WHEEL_SPEED_ENABLED

typedef struct
{
#if SYS__MANAGER__DAMPER_POTS_ENABLED
    sys__datastore__damper_pots_save_t damperPots[SYS__MANAGER__DAMPER_POTS_ATTACHED_AMT];
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__ACCELEROMETER_ENABLED
    sys__datastore__accelerometer_save_t accelerometer;
#endif // SYS__MANAGER__ACCELEROMETER_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
    sys__datastore__ride_height_save_t rideHeight;
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

#if SYS__MANAGER__WHEEL_SPEED_ENABLED
    sys__datastore__wheel_speed_save_t wheelSpeed;
#endif // SYS__MANAGER__WHEEL_SPEED_ENABLED

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
