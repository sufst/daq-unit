/*************************************************************************//**
* @file sys__manager__config__handlers.h
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
  @brief
----------------------------------------------------------------------------*/

#ifndef CONTROLLER_V2_SYS__MANAGER__CONFIG__HANDLERS_H
#define CONTROLLER_V2_SYS__MANAGER__CONFIG__HANDLERS_H
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
#define SYS__MANAGER__CONFIG__HANDLERS__WIRELESS_DAQ_SUB_CONFIG_ID 0x01
/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/
extern uint8_t (*const sys__manager__config__handlers_from_tag[])(uint8_t subConfig, void *data);

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
uint8_t sys__manager__config__handlers__rpm(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__tps(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__water_temp(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__air_temp(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__manifold_press(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__lambda_x1000(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__speed_kph_x10(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__oil_pressure(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__fuel_pressure(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__oil_temp(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__battery_v_x10(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__gear(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__advance_deg_x10(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__injection_time_ms_x100(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__cam_advance_deg_x10(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__cam_target_deg_x10(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__cam_pwm_perc_x10(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__crank_error_nr(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__cam_error_nr(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__external_5v_mv(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__injection_duty_cycle_perc(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__lambda_pid_target_perc_x10(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__lambda_pid_adj_perc_x10(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__evo_scann_sen_1(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__evo_scann_sen_2(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__evo_scann_sen_3(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__evo_scann_sen_4(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__evo_scann_sen_5(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__evo_scann_sen_6(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__evo_scann_sen_7(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__evo_scann_sen_8(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__damper_pot_1(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__damper_pot_2(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__damper_pot_3(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__damper_pot_4(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__damper_pot_5(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__lap_timer(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__not_used(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__wireless_daq_refresh_ms(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__yaw_sensor(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__fuel_flow(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__brake_pressure(uint8_t subConfig, void *data);

uint8_t sys__manager__config__handlers__ride_height(uint8_t subConfid, void *data);
/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif //CONTROLLER_V2_SYS__MANAGER__CONFIG__HANDLERS_H

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
