/*************************************************************************//**
* @file sys__manager.cpp
* @brief System manager 
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
#include "sys__manager.h"
#include "../srv/srv__comms.h"
#include "../srv/srv__daq.h"
#include "../srv/srv__software__timer.h"

#include "sys__datastore.h"

#include "avr/wdt.h"

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
static void sys__manager__can__err_handler(srv__comms__can_bus_t bus, uint32_t *events);

static void sys__manager__wireless_timer_handler();

static void sys__manager__can_loopback_ecu_emulate();

static void sys__manager__s60_ecu_event_handler();

#if SYS__MANAGER__DASH_ENABLED

static void sys__manager__dash_timer_handler();

#endif // SYS__MANAGER__DASH_ENABLED

static void sys__manager__init_watchdog();

static void sys__manager__status_update_msg_handler();
/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  global variables
----------------------------------------------------------------------------*/
sys__datastore_t sys__datastore;

/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Initialises the system
* @param None
* @return None
* @note
*****************************************************************************/
void sys__manager__init()
{
    /*
     * Initialise serial
     */
    srv__comms__serial_init((srv__comms__serial_uart_t) SYS__MANAGER__DEBUG_UART, 115200);

#if SYS__MANAGER__DASH_ENABLED

    srv__comms__serial_init((srv__comms__serial_uart_t) SYS__MANAGER__DASH_UART, 115200);

#endif // SYS__MANAGER__DASH_ENABLED

#if SYS__MANAGER__WIRELESS_ENABLED

    /*
     * Initialise wireless
     */

    srv__comms__wireless_set_cts_pin(SYS__MANAGER__WIRELESS_CTS_PIN);

    srv__comms__wireless_set_rts_pin(SYS__MANAGER__WIRELESS_RTS_PIN);

    /*
     * NOTE: THIS IS REQUIRED WHEN USING THE XBEE SHIELD
     * Stop the communication layer interfering with the wireless uart, as debug and wireless are on the same uart
     */
    srv__comms__serial_disable((srv__comms__serial_uart_t) SYS__MANAGER__DEBUG_UART);

    srv__comms__wireless_set_uart((srv__comms__wireless_uart_t) SYS__MANAGER__WIRELESS_UART);

    srv__comms__wireless_init();

    sys__datastore.wireless.wirelessDaqRefreshMs = SYS__MANAGER__WIRELESS_TX_INTERVAL_MS;

    sys__datastore.wireless.timerHandle = srv__software__timer__register(sys__datastore.wireless.wirelessDaqRefreshMs,
                                                                         sys__manager__wireless_timer_handler);

#endif // SYS__MANAGER__WIRELESS_ENABLED

    /*
     * Initialise can
     */

    srv__comms__can_register_err_callback(sys__manager__can__err_handler);

    srv__comms__can_set_cs_pin((srv__comms__can_bus_t) SYS__MANAGER__CAN_BUS_ECU,
                               SYS__MANAGER__CAN_BUS_ECU_CS_PIN);

    srv__comms__can_set_int_pin((srv__comms__can_bus_t) SYS__MANAGER__CAN_BUS_ECU,
                                SYS__MANAGER__CAN_BUS_ECU_INT_PIN);

    srv__comms__can_register_ecu_handler(sys__manager__s60_ecu_event_handler);

    if (srv__comms__init_can((srv__comms__can_bus_t) SYS__MANAGER__CAN_BUS_ECU) != SRV__COMMS__ERROR_NONE)
    {
        Serial.println("CAN INIT FAIL");
    }

    /*
     * For internal testing purposes only, to be used with setting the can controller to loop back mode
     */
//    srv__software__timer__register(20, sys__manager__can_loopback_ecu_emulate);
    (void) sys__manager__can_loopback_ecu_emulate;

#if SYS__MANAGER__SD_ENABLED

    /*
     * Initialise sd
     */

    if (srv__daq__sd_init(SYS__MANAGER__SD_CS_PIN) != SRV__DAQ__ERROR_NONE)
    {
        Serial.println("SD INIT FAIL");
    }

#endif // SYS__MANAGER__SD_ENABLED

#if SYS__MANAGER__DAMPER_POTS_ENABLED

    /*
     * Initialise damper pots
     */

    uint8_t dampersPins[SYS__MANAGER__DAMPER_POTS_ATTACHED_AMT] = {SYS__MANAGER__DAMPER_POT_1_PIN,
                                                                   SYS__MANAGER__DAMPER_POT_2_PIN,
                                                                   SYS__MANAGER__DAMPER_POT_3_PIN,
                                                                   SYS__MANAGER__DAMPER_POT_4_PIN};

    srv__daq__damper_pots_init(SYS__MANAGER__DAMPER_POTS_POLL_MS, dampersPins);

#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__LAP_TIMER_ENABLED

    /*
     * Initialise lap timer
     */

    srv__daq__lap_timer_init(SYS__MANAGER__LAP_TIMER_INT_PIN, SYS__MANAGER__LAP_TIMER_DRIVE_PIN,
                             SYS__MANAGER__LAP_TIMER_DEFAULT_DEBOUNCE_MS);

#endif // SYS__MANAGER__LAP_TIMER_ENABLEDs

#if SYS__MANAGER__DASH_ENABLED

    /*
     * Initialise dash updater
     */

    srv__software__timer__register(SYS__MANAGER__DASH_UPDATE_MS, sys__manager__dash_timer_handler);

#endif // SYS__MANAGER__DASH_ENABLED

#if SYS__MANAGER__FCHMPPLC_ENABLED

    srv__daq__fchmpplc_init(SYS__MANAGER__FCHMPPLC_INT_PIN, SYS__MANAGER__FCHMPPLC_SAMPLE_MS);

#endif // SYS__MANAGER__FCHMPPLC_ENABLED

#if SYS__MANAGER__BRAKE_PRESS_ENABLED

    srv__daq__brake_pressure_init(SYS__MANAGER__BRAKE_PRESS_PIN, SYS__MANAGER__BRAKE_PRESS_SAMPLE_MS);

#endif // SYS__MANAGER__BRAKE_PRESS_ENABLED

#if SYS__MANAGER__YAW_SENSOR_ENABLED

    /*
     * Initialise yaw sensor
     */

    srv__daq__yaw_sensor_init(SYS__MANAGER__YAW_SENSOR_PIN, SYS__MANAGER__YAW_SENSOR_POLL_MS);

#endif // SYS__MANAGER__YAW_SENSOR_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED

    srv__daq__ride_height_init(SYS__MANAGER__RIDE_HEIGHT_POLL_MS, SYS__MANAGER__RIDE_HEIGHT_PIN);

#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

    /*
     * Initialise the periodic status update transmission
     */

    srv__software__timer__register(SYS__MANAGER__STATUS_MSG_INTERVAL_MS, sys__manager__status_update_msg_handler);

    /*
     * Initialise software timer
     */

    srv__software__timer__init();

    /*
     * Initialise the watch dog
     */

    sys__manager__init_watchdog();

    Serial.println("SYSTEM INIT FIN");
}

/*************************************************************************//**
* @brief services loops
* @param None
* @return None
* @note
*****************************************************************************/
void sys__manager__process()
{
    /*
     * Pat the watch dog so it knows we are still alive
     */
    wdt_reset();
    /*
     * Run all service layer's processes
     */
    srv__comms__process();
    srv__software__timer__process();
    srv__daq__process();
}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/

/*************************************************************************//**
* @brief Handles CAN error messages
* @param srv__comms__can_bus_t bus Bus error came from
* @param uint32_t *events Bitfield of the bus error events
* @return None
* @note
*****************************************************************************/
static void sys__manager__can__err_handler(srv__comms__can_bus_t bus, uint32_t *events)
{
    (void) bus;

    uint32_t currentMs = millis();


//    Serial.print(bus);
//    Serial.print(": ");
//    Serial.println(*events);

#if SYS__MANAGER__SD_ENABLED

    //    srv__daq__sd_write_tag_data(SYS__DATASTORE__TAG_CAN_ERR, events, &currentMs);

#endif // SYS__MANAGER__SD_ENABLED

    (void) currentMs;
    (void) events;
}

#if SYS__MANAGER__WIRELESS_ENABLED

/*************************************************************************//**
* @brief Transmits daq wireless data at a fixed frequency
* @param None
* @return None
* @note
*****************************************************************************/
static void sys__manager__wireless_timer_handler()
{

    uint32_t currentMs = millis();

    for (uint8_t i = 0; i < SYS__MANAGER__ECU_SENSOR_CNT; i++)
    {
        sys__datastore__ecu_save_t *data = &sys__datastore.ecu[i];

        if (data->wirelessDaq)
        {
            // The tag field is 0 until the very first instance of the tag is obtained
            if (data->tag != 0)
            {
                srv__comms__wireless_write_cmd_tag_data(data->tag, &data->data, &data->timestamp);
            }

        }
    }

#if SYS__MANAGER__LAP_TIMER_ENABLED

    if (sys__datastore.laptimer.wirelessDaq)
    {
        srv__comms__wireless_write_cmd_tag_data(SYS__DATASTORE__TAG_LAPTIMER, &sys__datastore.laptimer.timestamp,
                                                &sys__datastore.laptimer.timestamp);
    }

#endif // SYS__MANAGER__LAP_TIMER_ENABLED

#if SYS__MANAGER__DAMPER_POTS_ENABLED

    for (uint8_t i = 0; i < SYS__MANAGER__DAMPER_POTS_ATTACHED_AMT; i++)
    {
        sys__datastore__damper_pots_save_t *data = &sys__datastore.damperPots[i];

        if (data->wirelessDaq)
        {
            // The tag field is 0 until the very first instance of the tag is obtained
            if (data->tag != 0)
            {
                srv__comms__wireless_write_cmd_tag_data(data->tag, &data->data, &data->timestamp);
            }
        }
    }

#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED

    for (uint8_t i = 0; i < SYS__MANAGER__EVO_SCANN_SENSORS_ATTACHED_AMT; i++)
    {
        sys__datastore__evo_scanner_save_t *data = &sys__datastore.evo[i];

        if (data->wirelessDaq)
        {
            // The tag field is 0 until the very first instance of the tag is obtained
            if (data->tag != 0)
            {
                srv__comms__wireless_write_cmd_tag_data(data->tag, &data->data, &data->timestamp);
            }
        }
    }

#endif // SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED

#if SYS__MANAGER__YAW_SENSOR_ENABLED

    sys__datastore__yaw_sensor_save_t *data = &sys__datastore.yaw;

    if (data->wirelessDaq)
    {
        if (data->tag != 0)
        {
            srv__comms__wireless_write_cmd_tag_data(data->tag, &data->data, &data->timestamp);
        }
    }

#endif // SYS__MANAGER__YAW_SENSOR_ENABLED

    srv__comms__wireless_write_cmd_tag_data(SYS__DATASTORE__TAG_WIRELESS_DAQ_REFRESH_MS,
                                            &sys__datastore.wireless.wirelessDaqRefreshMs, &currentMs);

#if SYS__MANAGER__FCHMPPLC_ENABLED

    sys__datastore__fchmpplc_save_t *fchmpplc = &sys__datastore.fchmpplc;

    if (fchmpplc->wirelessDaq)
    {
        if (fchmpplc->tag != 0)
        {
            srv__comms__wireless_write_cmd_tag_data(SYS__DATASTORE__TAG_FUEL_FLOW,
                                                    &fchmpplc->data, &fchmpplc->timestamp);
        }
    }

#endif // SYS__MANAGER__FCHMPPLC_ENABLED

#if SYS__MANAGER__BRAKE_PRESS_ENABLED

    sys__datastore__brake_press_save_t *brake = &sys__datastore.brakePressure;

    if (brake->wirelessDaq)
    {
        if (brake->tag != 0)
        {
            srv__comms__wireless_write_cmd_tag_data(SYS__DATASTORE__TAG_BRAKE_PRESSURE,
                                                    &brake->data, &brake->timestamp);
        }
    }

#endif // SYS__MANAGER__BRAKE_PRESS_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED

    sys__datastore__ride_height_save_t *rideHeight = &sys__datastore.rideHeight;

    if (rideHeight->wirelessDaq) {
        if(rideHeight->tag != 0) {
            srv__comms__wireless_write_cmd_tag_data(rideHeight->tag, &rideHeight->data, &rideHeight->timestamp);
        }
    }

#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED
}

#endif // SYS__MANAGER__WIRELESS_ENABLED

/*************************************************************************//**
* @brief Emulate the ecu when the CAN controller is set to loopback mode for debugging
* @param None
* @return None
* @note
*****************************************************************************/
static void sys__manager__can_loopback_ecu_emulate()
{
    static srv__comms__can_tx_message_t msg;
    msg.addr = 0x2000;
    msg.len = 8;
    msg.data16[0]++;
    msg.data16[1]++;
    msg.data16[2]++;
    msg.data16[3]++;

    for (uint8_t i = 0; i < 8; i++)
    {
        srv__comms__can__write((srv__comms__can_bus_t) SYS__MANAGER__CAN_BUS_ECU, &msg);

        msg.addr++;
    }
}

#if SYS__MANAGER__DASH_ENABLED

/*************************************************************************//**
* @brief Handle dash information requirements at a given frequency
* @param None
* @return None
* @note
*****************************************************************************/
static void sys__manager__dash_timer_handler()
{

    /*
     * Use tpsTestDataForDashRpm when wanting to test dash rpm LEDs with the tps instead
     */
//    uint16_t tpsTestDataForDashRpm = sys__datastore.ecu[SYS__DATASTORE__TAG_TPS].data * 140;

    sys__datastore__ecu_save_t *tagStore = &sys__datastore.ecu[SYS__DATASTORE__TAG_RPM];

    if (tagStore->tag != 0)
    {
        srv__comms__serial_write_cmd_tag_data((srv__comms__serial_uart_t) SYS__MANAGER__DASH_UART,
                                              tagStore->tag,
                                              &tagStore->data,
//                                              &tpsTestDataForDashRpm,
                                              &tagStore->timestamp);
    }


    tagStore = &sys__datastore.ecu[SYS__DATASTORE__TAG_WATER_TEMP_C];

    if (tagStore->tag != 0)
    {
        srv__comms__serial_write_cmd_tag_data((srv__comms__serial_uart_t) SYS__MANAGER__DASH_UART,
                                              tagStore->tag,
                                              &tagStore->data,
                                              &tagStore->timestamp);
    }

}

#endif // SYS__MANAGER__DASH_ENABLED

/*************************************************************************//**
* @brief Handles the periodic transmission of the status update msg
* @param None
* @return None
* @note
*****************************************************************************/
static void sys__manager__status_update_msg_handler()
{
    const uint8_t controllerAlive = 0x01;

    sys__datastore.status[SYS__DATASTORE__STATUS_TAG_CONTROLLER] = controllerAlive;
    sys__datastore.status[SYS__DATASTORE__STATUS_TAG_SD_CARD] = srv__daq__get_sd_state();

    sys__datastore.status[SYS__DATASTORE__STATUS_TAG_S60_ECU] = (millis() <= SYS__MANAGER__STATUS_ECU_TIMEOUT_MS) ? 0x00
                                                                                                                  :
                                                                ((millis() - sys__datastore.lastEcuMessageSeenTimeMs) <
                                                                 SYS__MANAGER__STATUS_ECU_TIMEOUT_MS) ? 0x01 : 0x00;

    for (uint8_t i = 1; i <= SYS__DATASTORE__STATUS_TAG_AMOUNT; i++)
    {
        srv__comms__wireless_write_cmd_status(i, sys__datastore.status[i]);
    }
}

/*************************************************************************//**
* @brief Handles when s60 ecu messages are received
* @param None
* @return None
* @note
*****************************************************************************/
static void sys__manager__s60_ecu_event_handler()
{
    sys__datastore.lastEcuMessageSeenTimeMs = millis();
}

/*************************************************************************//**
* @brief Initialise the watch dog to reset the mcu if we crash for whatever reason
* @param None
* @return None
* @note
*****************************************************************************/
static void sys__manager__init_watchdog()
{
    wdt_enable(WDTO_120MS);
}
/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
