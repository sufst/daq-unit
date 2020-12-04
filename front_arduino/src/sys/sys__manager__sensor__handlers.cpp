/*************************************************************************//**
* @file sys__manager__sensor__handlers.cpp
* @brief All handler functions for all sensors the system has to handle
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
#include "sys__manager__sensor__handlers.h"

#include "../srv/srv__daq.h"
#include "sys__datastore.h"

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/
void (*const sys__manager__sensor__handlers_from_tag[])(void *data, void *timestamp) =
        {
                sys__manager__sensor__handlers__not_used,
                sys__manager__sensor__handlers__rpm,
                sys__manager__sensor__handlers__tps,
                sys__manager__sensor__handlers__water_temp,
                sys__manager__sensor__handlers__air_temp,
                sys__manager__sensor__handlers__manifold_press,
                sys__manager__sensor__handlers__lambda_x1000,
                sys__manager__sensor__handlers__speed_kph_x10,
                sys__manager__sensor__handlers__oil_pressure,
                sys__manager__sensor__handlers__fuel_pressure,
                sys__manager__sensor__handlers__oil_temp,
                sys__manager__sensor__handlers__battery_v_x10,
                sys__manager__sensor__handlers__not_used,
                sys__manager__sensor__handlers__gear,
                sys__manager__sensor__handlers__advance_deg_x10,
                sys__manager__sensor__handlers__injection_time_ms_x100,
                sys__manager__sensor__handlers__not_used,
                sys__manager__sensor__handlers__not_used,
                sys__manager__sensor__handlers__not_used,
                sys__manager__sensor__handlers__not_used,
                sys__manager__sensor__handlers__cam_advance_deg_x10,
                sys__manager__sensor__handlers__cam_target_deg_x10,
                sys__manager__sensor__handlers__cam_pwm_perc_x10,
                sys__manager__sensor__handlers__crank_error_nr,
                sys__manager__sensor__handlers__cam_error_nr,
                sys__manager__sensor__handlers__not_used,
                sys__manager__sensor__handlers__not_used,
                sys__manager__sensor__handlers__not_used,
                sys__manager__sensor__handlers__external_5v_mv,
                sys__manager__sensor__handlers__injection_duty_cycle_perc,
                sys__manager__sensor__handlers__lambda_pid_target_perc_x10,
                sys__manager__sensor__handlers__lambda_pid_adj_perc_x10,
                sys__manager__sensor__handlers__not_used,
#if SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED
                sys__manager__sensor__handlers__evo_scann_sen_1,
                sys__manager__sensor__handlers__evo_scann_sen_2,
                sys__manager__sensor__handlers__evo_scann_sen_3,
                sys__manager__sensor__handlers__evo_scann_sen_4,
                sys__manager__sensor__handlers__evo_scann_sen_5,
                sys__manager__sensor__handlers__evo_scann_sen_6,
                sys__manager__sensor__handlers__evo_scann_sen_7,
                sys__manager__sensor__handlers__evo_scann_sen_8,
#else
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
#endif // SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED
                sys__manager__sensor__handlers__not_used,
#if SYS__MANAGER__DAMPER_POTS_ENABLED
                sys__manager__sensor__handlers__damper_pot_1,
                sys__manager__sensor__handlers__damper_pot_2,
                sys__manager__sensor__handlers__damper_pot_3,
                sys__manager__sensor__handlers__damper_pot_4,
                sys__manager__sensor__handlers__damper_pot_5,
#else
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED
#if SYS__MANAGER__LAP_TIMER_ENABLED
                sys__manager__sensor__handlers__laptimer,
#else
                NULL,
#endif // SYS__MANAGER__LAP_TIMER_ENABLED
                sys__manager__sensor__handlers__not_used,
#if SYS__MANAGER__YAW_SENSOR_ENABLED
                sys__manager__sensor__handlers__yaw_sensor
#else
                sys__manager__sensor__handlers__not_used,
#endif // SYS__MANAGER__YAW_SENSOR_ENABLED
#if SYS__MANAGER__FCHMPPLC_ENABLED
                sys__manager__sensor__handlers__fuel_flow,
#else
                sys__manager__sensor__handlers__not_used,
#endif // SYS__MANAGER__FCHMPPLC_ENABLED
#if SYS__MANAGER__BRAKE_PRESS_ENABLED
                sys__manager__sensor__handlers__brake_pressure,
#else
                sys__manager__sensor__handlers__not_used
#endif // SYS__MANAGER__BRAKE_PRESS_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED
                sys__manager__sensor__handlers__ride_height
#else
                sys__manager__sensor__handlers__not_used
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED
        };

const uint8_t sys__manager__sensor__handlers__tag_length_from_tag[] =
        {
                0,
                2, // rpm
                2, // tps
                2, // waterTempC
                2, // airTempC
                2, // manifoldPressure
                2, // lambdax1000
                2, // speedKphx10
                2, // oilPressureKpa
                2, // fuelPressureKpa
                2, // oilTempC
                2, // batteryVx10
                2, // fuelComsumptionLpHrx10
                2, // gear
                2, // advanceDegx10
                2, // injectionTimeMsx100
                2, // fuelComsumptionPl100kMx10
                2, // ana1mV
                2, // ana2mV
                2, // ana3mV
                2, // camAdvanceDegx10
                2, // camTargDegx10
                2, // camPwmPercx10
                2, // crankErrorsNr
                2, // camErrorsNr
                2, // cam2AdvDegx10
                2, // cam2TargDegx10
                2, // cam2PwmPercx10
                2, // external5VmV
                2, // injDutyCyclePerc
                2, // lambdaPidTargetPercx10
                2, // lambdaPidAdjPercx10
                2, // ecuSwitchesBitField
                4, // evoScannSen0
                4, // evoScannSen1
                4, // evoScannSen2
                4, // evoScannSen3
                4, // evoScannSen4
                4, // evoScannSen5
                4, // evoScannSen6
                4, // evoScannSen7
                4, // canErrorBitfield
                4, // DampPot1
                4, // DampPot2
                4, // DampPot3
                4, // DampPot4
                4, // DampPot5
                4, // lapTimer
                1, // wireless refresh ms
                4, // yaw sensor
                2, // fuel flow
                4, // brake pressure
                4  // ride height
        };
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
* @brief Handle RPM sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__rpm(void *data, void *timestamp)
{
    uint16_t *rpm = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_RPM;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *rpm;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle TPS sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__tps(void *data, void *timestamp)
{
    uint16_t *tps = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_TPS;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *tps;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle water temp sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__water_temp(void *data, void *timestamp)
{
    uint16_t *waterTempC = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_WATER_TEMP_C;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *waterTempC;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle air temp sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__air_temp(void *data, void *timestamp)
{
    uint16_t *airTempC = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_AIR_TEMP_C;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *airTempC;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle manifold pressure sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__manifold_press(void *data, void *timestamp)
{
    uint16_t *manifoldPress = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_MANIFOLD_PRESS;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *manifoldPress;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle lambda sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__lambda_x1000(void *data, void *timestamp)
{
    uint16_t *lambdax100 = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_LAMBDA_X1000;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *lambdax100;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle speed sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__speed_kph_x10(void *data, void *timestamp)
{
    uint16_t *speedKphx10 = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_SPEED_KPH_X10;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *speedKphx10;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle oil pressure sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__oil_pressure(void *data, void *timestamp)
{
    uint16_t *oilPressKpa = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_OIL_PRESS_KPA;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *oilPressKpa;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle fuel pressure sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__fuel_pressure(void *data, void *timestamp)
{
    uint16_t *fuelPressKpa = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_FUEL_PRESS_KPA;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *fuelPressKpa;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle oil temperature sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__oil_temp(void *data, void *timestamp)
{
    uint16_t *oilTempC = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_OIL_TEMP_C;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *oilTempC;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle battery sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__battery_v_x10(void *data, void *timestamp)
{
    uint16_t *batteryVx10 = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_BATTERY_V_X10;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *batteryVx10;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle gear sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__gear(void *data, void *timestamp)
{
    uint16_t *currentGear = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_GEAR;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *currentGear;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle advance degree sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__advance_deg_x10(void *data, void *timestamp)
{
    uint16_t *advanceDegx10 = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_ADVANCE_DEG_X10;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *advanceDegx10;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle injection time sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__injection_time_ms_x100(void *data, void *timestamp)
{
    uint16_t *injectionTimeMsx100 = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_INJECTION_TIME_MS_X100;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *injectionTimeMsx100;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle cam advance degree sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__cam_advance_deg_x10(void *data, void *timestamp)
{
    uint16_t *camAdvanceDegx10 = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_CAM_ADVANCE_DEG_X10;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *camAdvanceDegx10;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle cam target degree sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__cam_target_deg_x10(void *data, void *timestamp)
{
    uint16_t *camTargDegx10 = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_CAM_TARGET_DEG_X10;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *camTargDegx10;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle cam pwm percentage sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__cam_pwm_perc_x10(void *data, void *timestamp)
{
    uint16_t *camPwmPercx10 = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_CAM_PWM_PERC_X10;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *camPwmPercx10;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle crank errors sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__crank_error_nr(void *data, void *timestamp)
{
    uint16_t *crankErrorsNr = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_CRANK_ERRORS_NR;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *crankErrorsNr;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle cam errors sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__cam_error_nr(void *data, void *timestamp)
{
    uint16_t *camErrorsNr = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_CAM_ERRORS_NR;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *camErrorsNr;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle external 5V sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__external_5v_mv(void *data, void *timestamp)
{
    uint16_t *external5VmV = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_EXTERNAL_5V_MV;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *external5VmV;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle injection duty cycle percentage sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__injection_duty_cycle_perc(void *data, void *timestamp)
{
    uint16_t *injDutyCyclePerc = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_INJECTION_DUTY_CYCLE_PERC;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *injDutyCyclePerc;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle lambda pid target percentage sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__lambda_pid_target_perc_x10(void *data, void *timestamp)
{
    uint16_t *lambdaPidTargPercx10 = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_LAMBDA_PID_TARGET_PERC_X10;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *lambdaPidTargPercx10;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle lambda pid adjustment percentage sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__lambda_pid_adj_perc_x10(void *data, void *timestamp)
{
    uint16_t *lambdaPidAdjPercx10 = (uint16_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_LAMBDA_PID_ADJ_PERC_X10;

    sys__datastore__ecu_save_t *storage = &sys__datastore.ecu[tag];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *lambdaPidAdjPercx10;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

#if SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED

/*************************************************************************//**
* @brief Handle evo scanner sen 1 sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__evo_scann_sen_1(void *data, void *timestamp)
{
    uint32_t *evoScann1 = (uint32_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_EVO_SCANN_SEN_1;

    sys__datastore__evo_scanner_save_t *storage = &sys__datastore.evo[0];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *evoScann1;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle evo scanner sen 2 sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__evo_scann_sen_2(void *data, void *timestamp)
{
    uint32_t *evoScann2 = (uint32_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_EVO_SCANN_SEN_2;

    sys__datastore__evo_scanner_save_t *storage = &sys__datastore.evo[1];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *evoScann2;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle evo scanner sen 3 sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__evo_scann_sen_3(void *data, void *timestamp)
{
    uint32_t *evoScann3 = (uint32_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_EVO_SCANN_SEN_3;

    sys__datastore__evo_scanner_save_t *storage = &sys__datastore.evo[2];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *evoScann3;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle evo scanner sen 4 sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__evo_scann_sen_4(void *data, void *timestamp)
{
    uint32_t *evoScann4 = (uint32_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_EVO_SCANN_SEN_4;

    sys__datastore__evo_scanner_save_t *storage = &sys__datastore.evo[3];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *evoScann4;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle evo scanner sen 5 sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__evo_scann_sen_5(void *data, void *timestamp)
{
    uint32_t *evoScann5 = (uint32_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_EVO_SCANN_SEN_5;

    sys__datastore__evo_scanner_save_t *storage = &sys__datastore.evo[4];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *evoScann5;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle evo scanner sen 6 sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__evo_scann_sen_6(void *data, void *timestamp)
{
    uint32_t *evoScann6 = (uint32_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_EVO_SCANN_SEN_6;

    sys__datastore__evo_scanner_save_t *storage = &sys__datastore.evo[5];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *evoScann6;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle evo scanner sen 7 sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__evo_scann_sen_7(void *data, void *timestamp)
{
    uint32_t *evoScann7 = (uint32_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_EVO_SCANN_SEN_7;

    sys__datastore__evo_scanner_save_t *storage = &sys__datastore.evo[6];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *evoScann7;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle evo scanner sen 8 sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__evo_scann_sen_8(void *data, void *timestamp)
{
    uint32_t *evoScann8 = (uint32_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_EVO_SCANN_SEN_8;

    sys__datastore__evo_scanner_save_t *storage = &sys__datastore.evo[7];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *evoScann8;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

#endif // SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED

#if SYS__MANAGER__DAMPER_POTS_ENABLED

/*************************************************************************//**
* @brief Handle damper pot 1 sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__damper_pot_1(void *data, void *timestamp)
{
    uint32_t *dampPot1 = (uint32_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_DAMP_POT_1;

    sys__datastore__damper_pots_save_t *storage = &sys__datastore.damperPots[0];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *dampPot1;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle damper pot 2 sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__damper_pot_2(void *data, void *timestamp)
{
    uint32_t *dampPot2 = (uint32_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_DAMP_POT_2;

    sys__datastore__damper_pots_save_t *storage = &sys__datastore.damperPots[1];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *dampPot2;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle damper pot 3 sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__damper_pot_3(void *data, void *timestamp)
{
    uint32_t *dampPot3 = (uint32_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_DAMP_POT_3;

    sys__datastore__damper_pots_save_t *storage = &sys__datastore.damperPots[2];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *dampPot3;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle damper pot 4 sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__damper_pot_4(void *data, void *timestamp)
{
    uint32_t *dampPot4 = (uint32_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_DAMP_POT_4;

    sys__datastore__damper_pots_save_t *storage = &sys__datastore.damperPots[3];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *dampPot4;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

/*************************************************************************//**
* @brief Handle damper pot 5 sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__damper_pot_5(void *data, void *timestamp)
{
    uint32_t *dampPot5 = (uint32_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_DAMP_POT_5;

    sys__datastore__damper_pots_save_t *storage = &sys__datastore.damperPots[4];

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *dampPot5;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__LAP_TIMER_ENABLED

/*************************************************************************//**
* @brief Handle lap timer sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__laptimer(void *data, void *timestamp)
{
    (void) data;

    uint8_t tag = SYS__DATASTORE__TAG_LAPTIMER;

    sys__datastore__laptimer_save_t *storage = &sys__datastore.laptimer;

    storage->timestamp = *((uint32_t *) timestamp);

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(tag, &storage->timestamp, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

#endif // SYS__MANAGER__LAP_TIMER_ENABLED

#if SYS__MANAGER__YAW_SENSOR_ENABLED

void sys__manager__sensor__handlers__yaw_sensor(void *data, void *timestamp)
{
    uint32_t *yaw = (uint32_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_YAW;

    sys__datastore__yaw_sensor_save_t *storage = &sys__datastore.yaw;

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *yaw;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

#endif // SYS__MANAGER__YAW_SENSOR_ENABLED


#if SYS__MANAGER__FCHMPPLC_ENABLED

/*************************************************************************//**
* @brief Handle fuel flow sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__fuel_flow(void *data, void *timestamp)
{

    uint16_t *blipsCnt = (uint16_t *) data;

    uint8_t tag = SYS__DATASTORE__TAG_FUEL_FLOW;

    sys__datastore__fchmpplc_save_t *storage = &sys__datastore.fchmpplc;

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *blipsCnt;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

#endif // SYS__MANAGER__FCHMPPLC_ENABLED

#if SYS__MANAGER__FCHMPPLC_ENABLED

/*************************************************************************//**
* @brief Handle brake pressure sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__brake_pressure(void *data, void *timestamp)
{

    uint32_t *pressure = (uint32_t *) data;

    uint8_t tag = SYS__DATASTORE__TAG_BRAKE_PRESSURE;

    sys__datastore__brake_press_save_t *storage = &sys__datastore.brakePressure;

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *pressure;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

#endif // SYS__MANAGER__FCHMPPLC_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED

/*************************************************************************//**
* @brief Handle ride height sensor data
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__ride_height(void *data, void *timestamp)
{
    uint32_t *rideHeight = (uint32_t *) data;
    uint8_t tag = SYS__DATASTORE__TAG_RIDE_HEIGHT;

    sys__datastore__ride_height_save_t *storage = &sys__datastore.rideHeight;

    storage->tag = tag;
    storage->timestamp = *((uint32_t *) timestamp);
    storage->data = *rideHeight;

#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_write_tag_data(storage->tag, &storage->data, &storage->timestamp);

#endif // SYS__MANAGER__SD_ENABLED
}

#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

/*************************************************************************//**
* @brief Handle sensors are not wanted
* @param sys__manager__sensor__handlers_data_t *data Sensor data and timestamp
* @return None
* @note
*****************************************************************************/
void sys__manager__sensor__handlers__not_used(void *data, void *timestamp)
{
    (void) data;
    (void) timestamp;
}

/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/


