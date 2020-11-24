/*************************************************************************//**
* @file sys__manager__config__handlers.cpp
* @brief Handlers for configuration change requests
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
#include "sys__manager__config__handlers.h"

#include "sys__datastore.h"
#include "../srv/srv__software__timer.h"
#include "../srv/srv__daq.h"
/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/
#if SYS__MANAGER__WIRELESS_ENABLED

uint8_t (*const sys__manager__config__handlers_from_tag[])(uint8_t subConfig, void *data) =
        {
                NULL,
                sys__manager__config__handlers__rpm,
                sys__manager__config__handlers__tps,
                sys__manager__config__handlers__water_temp,
                sys__manager__config__handlers__air_temp,
                sys__manager__config__handlers__manifold_press,
                sys__manager__config__handlers__lambda_x1000,
                sys__manager__config__handlers__speed_kph_x10,
                sys__manager__config__handlers__oil_pressure,
                sys__manager__config__handlers__fuel_pressure,
                sys__manager__config__handlers__oil_temp,
                sys__manager__config__handlers__battery_v_x10,
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__gear,
                sys__manager__config__handlers__advance_deg_x10,
                sys__manager__config__handlers__injection_time_ms_x100,
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__cam_advance_deg_x10,
                sys__manager__config__handlers__cam_target_deg_x10,
                sys__manager__config__handlers__cam_pwm_perc_x10,
                sys__manager__config__handlers__crank_error_nr,
                sys__manager__config__handlers__cam_error_nr,
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__external_5v_mv,
                sys__manager__config__handlers__injection_duty_cycle_perc,
                sys__manager__config__handlers__lambda_pid_target_perc_x10,
                sys__manager__config__handlers__lambda_pid_adj_perc_x10,
                sys__manager__config__handlers__not_used,
#if SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED
                sys__manager__config__handlers__evo_scann_sen_1,
                sys__manager__config__handlers__evo_scann_sen_2,
                sys__manager__config__handlers__evo_scann_sen_3,
                sys__manager__config__handlers__evo_scann_sen_4,
                sys__manager__config__handlers__evo_scann_sen_5,
                sys__manager__config__handlers__evo_scann_sen_6,
                sys__manager__config__handlers__evo_scann_sen_7,
                sys__manager__config__handlers__evo_scann_sen_8,
#else
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__not_used,
#endif // SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED
                sys__manager__config__handlers__not_used,
#if SYS__MANAGER__DAMPER_POTS_ENABLED
                sys__manager__config__handlers__damper_pot_1,
                sys__manager__config__handlers__damper_pot_2,
                sys__manager__config__handlers__damper_pot_3,
                sys__manager__config__handlers__damper_pot_4,
                sys__manager__config__handlers__damper_pot_5,
#else
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__not_used,
                sys__manager__config__handlers__not_used,
#endif // SYS__MANAGER__DAMPER_POTS_ENABLED
#if SYS__MANAGER__LAP_TIMER_ENABLED
                sys__manager__config__handlers__lap_timer,
#else
                sys__manager__config__handlers__not_used,
#endif // SYS__MANAGER__LAP_TIMER_ENABLED
                sys__manager__config__handlers__wireless_daq_refresh_ms,
#if SYS__MANAGER__YAW_SENSOR_ENABLED
                sys__manager__config__handlers__yaw_sensor
#else
                sys__manager__config__handlers__not_used,
#endif // SYS__MANAGER__YAW_SENSOR_ENABLED
                sys__manager__config__handlers__fuel_flow,
                sys__manager__config__handlers__brake_pressure
        };

#endif // SYS__MANAGER__WIRELESS_ENABLED
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
#if SYS__MANAGER__WIRELESS_ENABLED

/*************************************************************************//**
* @brief Handle RPM config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__rpm(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_RPM].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle TPS config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__tps(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;
    
    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_TPS].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle water temp config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__water_temp(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_WATER_TEMP_C].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle air temp config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__air_temp(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_AIR_TEMP_C].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle manifold pressure config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__manifold_press(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_MANIFOLD_PRESS].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle lambda config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__lambda_x1000(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_LAMBDA_X1000].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle speed config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__speed_kph_x10(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_SPEED_KPH_X10].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle oil pressure config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__oil_pressure(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_OIL_PRESS_KPA].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle fuel pressure config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__fuel_pressure(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_FUEL_PRESS_KPA].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle oil temperature config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__oil_temp(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_OIL_TEMP_C].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle battery config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__battery_v_x10(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_BATTERY_V_X10].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle gear config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__gear(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_GEAR].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle advance degree config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__advance_deg_x10(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_ADVANCE_DEG_X10].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle injection time config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__injection_time_ms_x100(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_INJECTION_TIME_MS_X100].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle cam advance degree config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__cam_advance_deg_x10(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_CAM_ADVANCE_DEG_X10].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle cam target degree config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__cam_target_deg_x10(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_CAM_TARGET_DEG_X10].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle cam pwm percentage config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__cam_pwm_perc_x10(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_CAM_PWM_PERC_X10].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle crank errors config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__crank_error_nr(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_CRANK_ERRORS_NR].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle cam errors config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__cam_error_nr(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_CAM_ERRORS_NR].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle external 5V config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__external_5v_mv(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_EXTERNAL_5V_MV].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle injection duty cycle percentage config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__injection_duty_cycle_perc(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_INJECTION_DUTY_CYCLE_PERC].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle lambda pid target percentage config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__lambda_pid_target_perc_x10(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_LAMBDA_PID_TARGET_PERC_X10].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle lambda pid adjustment percentage config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__lambda_pid_adj_perc_x10(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.ecu[SYS__DATASTORE__TAG_LAMBDA_PID_ADJ_PERC_X10].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

#if SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED

/*************************************************************************//**
* @brief Handle evo scanner sen 1 config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__evo_scann_sen_1(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.evo[0].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle evo scanner sen 2 config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__evo_scann_sen_2(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.evo[1].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle evo scanner sen 3 config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__evo_scann_sen_3(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.evo[2].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle evo scanner sen 4 config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__evo_scann_sen_4(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.evo[3].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle evo scanner sen 5 config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__evo_scann_sen_5(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.evo[4].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle evo scanner sen 6 config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__evo_scann_sen_6(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.evo[5].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle evo scanner sen 7 config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__evo_scann_sen_7(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.evo[6].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle evo scanner sen 8 config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__evo_scann_sen_8(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.evo[7].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

#endif // SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED

#if SYS__MANAGER__DAMPER_POTS_ENABLED

/*************************************************************************//**
* @brief Handle damper pot 1 config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__damper_pot_1(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.damperPots[0].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle damper pot 2 config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__damper_pot_2(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.damperPots[1].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle damper pot 3 config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__damper_pot_3(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.damperPots[2].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle damper pot 4 config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__damper_pot_4(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.damperPots[3].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

/*************************************************************************//**
* @brief Handle damper pot 5 config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__damper_pot_5(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.damperPots[4].wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__LAP_TIMER_ENABLED

/*************************************************************************//**
* @brief Handle lap timer config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__lap_timer(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    const uint8_t changeDebounceMsSubConfigId = 0x02;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.laptimer.wirelessDaq = *wirelessDaqConfigData;
    }
    else if (subConfig == changeDebounceMsSubConfigId)
    {
        uint8_t *requestedDebounceS = (uint8_t *) data;
        
        sys__datastore.laptimer.debounceS = *requestedDebounceS;
        srv__daq__lap_timer_set_debounce_ms(sys__datastore.laptimer.debounceS * 1000);
    }

    return configDataLen;
}

#endif // SYS__MANAGER__LAP_TIMER_ENABLED

/*************************************************************************//**
* @brief Handle wireless daq interval config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__wireless_daq_refresh_ms(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    const uint8_t changeRefreshMsSubConfigId = 0x02;

    if (subConfig == changeRefreshMsSubConfigId)
    {
        uint8_t *requestRefreshMs = (uint8_t *) data;
        sys__datastore.wireless.wirelessDaqRefreshMs = *requestRefreshMs;
        srv__software__timer__change_ms(sys__datastore.wireless.timerHandle,
                                        sys__datastore.wireless.wirelessDaqRefreshMs);
    }

    return configDataLen;
}

#if SYS__MANAGER__YAW_SENSOR_ENABLED

/*************************************************************************//**
* @brief Handle yaw sensor config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__yaw_sensor(uint8_t subConfig, void *data)
{
    sys__datastore.yaw.wirelessDaq = data;
}

#endif // SYS__MANAGER__YAW_SENSOR_ENABLED

#if SYS__MANAGER__FCHMPPLC_ENABLED

/*************************************************************************//**
* @brief Handle fuel flow config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__fuel_flow(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.fchmpplc.wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

#endif // SYS__MANAGER__FCHMPPLC_ENABLED

#if SYS__MANAGER__BRAKE_PRESS_ENABLED

/*************************************************************************//**
* @brief Handle fuel flow config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__brake_pressure(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.brakePressure.wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}

#endif // SYS__MANAGER__BRAKE_PRESS_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED

/*************************************************************************//**
* @brief Handle ride height sensor config data
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__ride_height(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    if (subConfig == SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID)
    {
        uint8_t *wirelessDaqConfigData = (uint8_t *) data;
        sys__datastore.rideHeight.wirelessDaq = *wirelessDaqConfigData;
    }

    return configDataLen;
}
#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

#endif // SYS__MANAGER__WIRELESS_ENABLED

/*************************************************************************//**
* @brief Handle configs that are not wanted
* @param uint8_t subConfig Sub configuration type
* @param void *data Configuration data
* @return unit8_t configDataLen The length of the configuration data used
* @note
*****************************************************************************/
uint8_t sys__manager__config__handlers__not_used(uint8_t subConfig, void *data)
{
    uint8_t configDataLen = 1;

    (void) subConfig;
    (void) data;

    return configDataLen;
}


/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/