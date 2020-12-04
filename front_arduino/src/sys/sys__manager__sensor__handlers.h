/*************************************************************************//**
* @file sys__manager__sensor__handlers.h
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
  @brief
----------------------------------------------------------------------------*/

#ifndef CONTROLLER_V2_SYS__MANAGER_SENSORS_H
#define CONTROLLER_V2_SYS__MANAGER_SENSORS_H
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

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/
extern const uint8_t sys__manager__sensor__handlers__tag_length_from_tag[];

extern void (*const sys__manager__sensor__handlers_from_tag[])(void *data, void *timestamp);

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
void sys__manager__sensor__handlers__rpm(void *data, void *timestamp);

void sys__manager__sensor__handlers__tps(void *data, void *timestamp);

void sys__manager__sensor__handlers__water_temp(void *data, void *timestamp);

void sys__manager__sensor__handlers__air_temp(void *data, void *timestamp);

void sys__manager__sensor__handlers__manifold_press(void *data, void *timestamp);

void sys__manager__sensor__handlers__lambda_x1000(void *data, void *timestamp);

void sys__manager__sensor__handlers__speed_kph_x10(void *data, void *timestamp);

void sys__manager__sensor__handlers__oil_pressure(void *data, void *timestamp);

void sys__manager__sensor__handlers__fuel_pressure(void *data, void *timestamp);

void sys__manager__sensor__handlers__oil_temp(void *data, void *timestamp);

void sys__manager__sensor__handlers__battery_v_x10(void *data, void *timestamp);

void sys__manager__sensor__handlers__gear(void *data, void *timestamp);

void sys__manager__sensor__handlers__advance_deg_x10(void *data, void *timestamp);

void sys__manager__sensor__handlers__injection_time_ms_x100(void *data, void *timestamp);

void sys__manager__sensor__handlers__cam_advance_deg_x10(void *data, void *timestamp);

void sys__manager__sensor__handlers__cam_target_deg_x10(void *data, void *timestamp);

void sys__manager__sensor__handlers__cam_pwm_perc_x10(void *data, void *timestamp);

void sys__manager__sensor__handlers__crank_error_nr(void *data, void *timestamp);

void sys__manager__sensor__handlers__cam_error_nr(void *data, void *timestamp);

void sys__manager__sensor__handlers__external_5v_mv(void *data, void *timestamp);

void sys__manager__sensor__handlers__injection_duty_cycle_perc(void *data, void *timestamp);

void sys__manager__sensor__handlers__lambda_pid_target_perc_x10(void *data, void *timestamp);

void sys__manager__sensor__handlers__lambda_pid_adj_perc_x10(void *data, void *timestamp);

void sys__manager__sensor__handlers__evo_scann_sen_1(void *data, void *timestamp);

void sys__manager__sensor__handlers__evo_scann_sen_2(void *data, void *timestamp);

void sys__manager__sensor__handlers__evo_scann_sen_3(void *data, void *timestamp);

void sys__manager__sensor__handlers__evo_scann_sen_4(void *data, void *timestamp);

void sys__manager__sensor__handlers__evo_scann_sen_5(void *data, void *timestamp);

void sys__manager__sensor__handlers__evo_scann_sen_6(void *data, void *timestamp);

void sys__manager__sensor__handlers__evo_scann_sen_7(void *data, void *timestamp);

void sys__manager__sensor__handlers__evo_scann_sen_8(void *data, void *timestamp);

void sys__manager__sensor__handlers__damper_pot_1(void *data, void *timestamp);

void sys__manager__sensor__handlers__damper_pot_2(void *data, void *timestamp);

void sys__manager__sensor__handlers__damper_pot_3(void *data, void *timestamp);

void sys__manager__sensor__handlers__damper_pot_4(void *data, void *timestamp);

void sys__manager__sensor__handlers__damper_pot_5(void *data, void *timestamp);

void sys__manager__sensor__handlers__laptimer(void *data, void *timestamp);

void sys__manager__sensor__handlers__not_used(void *data, void *timestamp);

void sys__manager__sensor__handlers__yaw_sensor(void *data, void *timestamp);

void sys__manager__sensor__handlers__fuel_flow(void *data, void *timestamp);

void sys__manager__sensor__handlers__brake_pressure(void *data, void *timestamp);

void sys__manager__sensor__handlers__ride_height(void *data, void *timestamp);

/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif //CONTROLLER_V2_SYS__MANAGER_SENSORS_H

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
