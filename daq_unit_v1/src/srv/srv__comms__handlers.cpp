/*************************************************************************//**
* @file srv__comms__handlers.cpp
* @brief Communication service layer message handlers
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
#include "srv__comms__handlers.h"

#include "../sys/sys__manager__sensor__handlers.h"
#include "../sys/sys__datastore.h"
#include "../sys/sys__manager__config__handlers.h"

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
#if SYS__MANAGER__CAN_BUS_ENABLED

static void srv__comms__handler_can_0x2000(srv__comms__can_rx_message_t *msg);

static void srv__comms__handler_can_0x2001(srv__comms__can_rx_message_t *msg);

static void srv__comms__handler_can_0x2002(srv__comms__can_rx_message_t *msg);

static void srv__comms__handler_can_0x2003(srv__comms__can_rx_message_t *msg);

static void srv__comms__handler_can_0x2004(srv__comms__can_rx_message_t *msg);

static void srv__comms__handler_can_0x2005(srv__comms__can_rx_message_t *msg);

static void srv__comms__handler_can_0x2006(srv__comms__can_rx_message_t *msg);

static void srv__comms__handler_can_0x2007(srv__comms__can_rx_message_t *msg);

static void srv__comms__handler_can_0x2008(srv__comms__can_rx_message_t *msg);

static void srv__comms__handler_can_0x487(srv__comms__can_rx_message_t *msg);

static void srv__comms__handler_can_0x487_mux_0(srv__comms__can_rx_message_t *msg);

static void srv__comms__handler_can_0x487_mux_1(srv__comms__can_rx_message_t *msg);

static void srv__comms__handler_can_0x487_mux_2(srv__comms__can_rx_message_t *msg);

#endif // SYS__MANAGER__CAN_BUS_ENABLED
/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  global variables
----------------------------------------------------------------------------*/
void (*const srv__comms__handlers__from_cmd[])(void *data, uint8_t len) =
        {
                NULL,
                srv__comms__handler_config,
                srv__comms__handler_tag_data
        };

void (*const srv__comms__handlers__from_can_0x2000_region[])(srv__comms__can_rx_message_t *msg) =
        {
                srv__comms__handler_can_0x2000,
                srv__comms__handler_can_0x2001,
                srv__comms__handler_can_0x2002,
                srv__comms__handler_can_0x2003,
                srv__comms__handler_can_0x2004,
                srv__comms__handler_can_0x2005,
                srv__comms__handler_can_0x2006,
                srv__comms__handler_can_0x2007,
                srv__comms__handler_can_0x2008,

        };

void (*const srv__comms__handlers__from_can_0x487_region[])(srv__comms__can_rx_message_t *msg) =
        {
                srv__comms__handler_can_0x487
        };



/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
#if SYS__MANAGER__CAN_BUS_ENABLED

/*************************************************************************//**
* @brief Handles the ecu 0x2000 CAN message
* @param srv__comms__can_rx_message_t *msg Message data from the CAN service layer
* @return None
* @note
*****************************************************************************/
static void srv__comms__handler_can_0x2000(srv__comms__can_rx_message_t *msg)
{
    uint16_t *rpm = &(msg->data16[0]);
    uint16_t *tps = &(msg->data16[1]);
    uint16_t *waterTempC = &(msg->data16[2]);
    uint16_t *airTempC = &(msg->data16[3]);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_RPM](rpm, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_TPS](tps, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_WATER_TEMP_C](waterTempC, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_AIR_TEMP_C](airTempC, &msg->timestamp);
}

/*************************************************************************//**
* @brief Handles the ecu 0x2001 CAN message
* @param srv__comms__can_rx_message_t *msg Message data from the CAN service layer
* @return None
* @note
*****************************************************************************/
static void srv__comms__handler_can_0x2001(srv__comms__can_rx_message_t *msg)
{
    uint16_t *mainifoldPresKpa = &(msg->data16[0]);
    uint16_t *lambdax1000 = &(msg->data16[1]);
    uint16_t *speedKphx10 = &(msg->data16[2]);
    uint16_t *oilPressKpa = &(msg->data16[3]);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_MANIFOLD_PRESS](mainifoldPresKpa, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_LAMBDA_X1000](lambdax1000, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_SPEED_KPH_X10](speedKphx10, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_OIL_PRESS_KPA](oilPressKpa, &msg->timestamp);
}

/*************************************************************************//**
* @brief Handles the ecu 0x2002 CAN message
* @param srv__comms__can_rx_message_t *msg Message data from the CAN service layer
* @return None
* @note
*****************************************************************************/
static void srv__comms__handler_can_0x2002(srv__comms__can_rx_message_t *msg)
{
    uint16_t *fuelPressKpa = &(msg->data16[0]);
    uint16_t *oilTempC = &(msg->data16[1]);
    uint16_t *batteryVx10 = &(msg->data16[2]);
    uint16_t *fuelComsumLpHrx10 = &(msg->data16[3]);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_FUEL_PRESS_KPA](fuelPressKpa, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_OIL_TEMP_C](oilTempC, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_BATTERY_V_X10](batteryVx10, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_FUEL_COMP_LPHR_X10](fuelComsumLpHrx10, &msg->timestamp);
}

/*************************************************************************//**
* @brief Handles the ecu 0x2003 CAN message
* @param srv__comms__can_rx_message_t *msg Message data from the CAN service layer
* @return None
* @note
*****************************************************************************/
static void srv__comms__handler_can_0x2003(srv__comms__can_rx_message_t *msg)
{
    uint16_t *currentGear = &(msg->data16[0]);
    uint16_t *advanceDegx10 = &(msg->data16[1]);
    uint16_t *injectionTimeMsx100 = &(msg->data16[2]);
    uint16_t *fuelComsumLp100kMx10 = &(msg->data16[3]);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_GEAR](currentGear, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_ADVANCE_DEG_X10](advanceDegx10, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_INJECTION_TIME_MS_X100](injectionTimeMsx100,
                                                                                        &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_FUEL_COMP_PL_100KM_X10](fuelComsumLp100kMx10,
                                                                                        &msg->timestamp);
}

/*************************************************************************//**
* @brief Handles the ecu 0x2004 CAN message
* @param srv__comms__can_rx_message_t *msg Message data from the CAN service layer
* @return None
* @note
*****************************************************************************/
static void srv__comms__handler_can_0x2004(srv__comms__can_rx_message_t *msg)
{
    uint16_t *ana1mV = &(msg->data16[0]);
    uint16_t *ana2mV = &(msg->data16[1]);
    uint16_t *ana3mV = &(msg->data16[2]);
    uint16_t *camAdvanceDegx10 = &(msg->data16[3]);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_ANA1_MV](ana1mV, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_ANA2_MV](ana2mV, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_ANA3_MV](ana3mV, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_CAM_ADVANCE_DEG_X10](camAdvanceDegx10, &msg->timestamp);
}

/*************************************************************************//**
* @brief Handles the ecu 0x2005 CAN message
* @param srv__comms__can_rx_message_t *msg Message data from the CAN service layer
* @return None
* @note
*****************************************************************************/
static void srv__comms__handler_can_0x2005(srv__comms__can_rx_message_t *msg)
{
    uint16_t *camTargDegx10 = &(msg->data16[0]);
    uint16_t *camPwmPercx10 = &(msg->data16[1]);
    uint16_t *crankErrorsNr = &(msg->data16[2]);
    uint16_t *camErrorsNr = &(msg->data16[3]);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_CAM_TARGET_DEG_X10](camTargDegx10, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_CAM_PWM_PERC_X10](camPwmPercx10, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_CRANK_ERRORS_NR](crankErrorsNr, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_CAM_ERRORS_NR](camErrorsNr, &msg->timestamp);
}

/*************************************************************************//**
* @brief Handles the ecu 0x2006 CAN message
* @param srv__comms__can_rx_message_t *msg Message data from the CAN service layer
* @return None
* @note
*****************************************************************************/
static void srv__comms__handler_can_0x2006(srv__comms__can_rx_message_t *msg)
{
    uint16_t *cam2AdvDegx10 = &(msg->data16[0]);
    uint16_t *cam2TargDegx10 = &(msg->data16[1]);
    uint16_t *cam2PwmPercx10 = &(msg->data16[2]);
    uint16_t *external5VmV = &(msg->data16[3]);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_CAM_2_ADVANCE_DEG_X10](cam2AdvDegx10, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_CAM_2_TARGET_DEG_X10](cam2TargDegx10, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_CAM_2_PWM_PERC_X10](cam2PwmPercx10, &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_EXTERNAL_5V_MV](external5VmV, &msg->timestamp);
}

/*************************************************************************//**
* @brief Handles the ecu 0x2007 CAN message
* @param srv__comms__can_rx_message_t *msg Message data from the CAN service layer
* @return None
* @note
*****************************************************************************/
static void srv__comms__handler_can_0x2007(srv__comms__can_rx_message_t *msg)
{
    uint16_t *injDutyCyclePerc = &(msg->data16[0]);
    uint16_t *lambdaPidTargPercx10 = &(msg->data16[1]);
    uint16_t *lambdaPidAdjPercx10 = &(msg->data16[2]);
    uint16_t *ecuSwitchesBitField = &(msg->data16[3]);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_INJECTION_DUTY_CYCLE_PERC](injDutyCyclePerc,
                                                                                           &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_LAMBDA_PID_TARGET_PERC_X10](lambdaPidTargPercx10,
                                                                                            &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_LAMBDA_PID_ADJ_PERC_X10](lambdaPidAdjPercx10,
                                                                                         &msg->timestamp);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_ECU_SWITCHES_BIT_FIELD](ecuSwitchesBitField,
                                                                                        &msg->timestamp);
}

/*************************************************************************//**
* @brief Handles the ecu 0x2008 CAN message
* @param srv__comms__can_rx_message_t *msg Message data from the CAN service layer
* @return None
* @note
*****************************************************************************/
static void srv__comms__handler_can_0x2008(srv__comms__can_rx_message_t *msg)
{
    (void) msg;
//    uint16_t * rdSpeedKphx10 = &(msg->data16[0]);
//    uint16_t * rUdSpeedKphx10 = &(msg->data16[1]);
//    uint16_t * ldSpeedKphx10 = &(msg->data16[2]);
//    uint16_t * lUdSpeedKphx10 = &(msg->data16[3]);

//    Serial.println(msg->addr, HEX);
}

#if SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED

/*************************************************************************//**
* @brief Handles when evo scanner can message is received
* @param srv__comms__can_rx_message_t *msg Message data from the CAN service layer
* @return None
* @note
*****************************************************************************/
static void srv__comms__handler_can_0x487(srv__comms__can_rx_message_t *msg)
{
    static void (*const evoScannFunc_ptrs[3])(srv__comms__can_rx_message_t *) = {srv__comms__handler_can_0x487_mux_0,
                                                                                 srv__comms__handler_can_0x487_mux_1,
                                                                                 srv__comms__handler_can_0x487_mux_2};


    (*evoScannFunc_ptrs[msg->data[0]])(msg);
}

#endif // SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED

#endif // SYS__MANAGER__CAN_BUS_ENABLED

/*************************************************************************//**
* @brief Handles when configuration command message is received
* @param void *data Received data
* @param uint8_t len Length of data
* @return None
* @note
*****************************************************************************/
void srv__comms__handler_config(void *data, uint8_t len)
{
    uint8_t *configMessage = (uint8_t *) data;
    uint8_t i = 0;

    const uint8_t overheadPerTagConfigData = 2;
    const uint8_t subConfigIdOffset = 1;
    const uint8_t dataOffset = 2;

    while (i < len)
    {
        i = overheadPerTagConfigData +
            sys__manager__config__handlers_from_tag[configMessage[i]](configMessage[i + subConfigIdOffset],
                    &(configMessage[i + dataOffset]));
    }
}

/*************************************************************************//**
* @brief Handles when tag data is received
* @param void *data Received data
* @param uint8_t len Length of data
* @return None
* @note
*****************************************************************************/
void srv__comms__handler_tag_data(void *data, uint8_t len)
{

    uint8_t *datau8 = (uint8_t *) data;

    uint8_t byte = 0;
    const uint8_t timestampLen = 4;

    while (byte < len)
    {
        uint8_t tag = datau8[byte];
        uint8_t tagLen = sys__manager__sensor__handlers__tag_length_from_tag[tag];

        sys__manager__sensor__handlers_from_tag[tag](&(datau8[byte]), &(datau8[tagLen]));

        byte += tagLen + timestampLen;
    }
}

/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/
#if SYS__MANAGER__CAN_BUS_ENABLED

#if SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED

/*************************************************************************//**
* @brief Handles evo scanner mux 0 when the evo scanner is in mux mode
* @param srv__comms__can_rx_message_t *msg Message data from the CAN service layer
* @return None
* @note
*****************************************************************************/
static void srv__comms__handler_can_0x487_mux_0(srv__comms__can_rx_message_t *msg)
{
    int32_t data = 0;
    uint16_t senRaw = 0;

#if SYS__MANAGER__EVO_SCANN_SEN_1_CONNECTED
    senRaw = (msg->data[1] << 8) | msg->data[2];

    data = (senRaw + 60000);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_EVO_SCANN_SEN_1](&data, &msg->timestamp);

#endif // SYS__MANAGER__EVO_SCANN_SEN_1_CONNECTED

#if SYS__MANAGER__EVO_SCANN_SEN_2_CONNECTED
    senRaw = (msg->data[3] << 8) | msg->data[4];

    data = (senRaw + 60000);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_EVO_SCANN_SEN_2](&data, &msg->timestamp);
#endif // SYS__MANAGER__EVO_SCANN_SEN_2_CONNECTED

#if SYS__MANAGER__EVO_SCANN_SEN_3_CONNECTED
    senRaw = (msg->data[5] << 8) | msg->data[6];

    data = (senRaw + 60000);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_EVO_SCANN_SEN_3](&data, &msg->timestamp);
#endif // SYS__MANAGER__EVO_SCANN_SEN_3_CONNECTED

    (void) data;
    (void) senRaw;
    (void) msg;
}

/*************************************************************************//**
* @brief Handles evo scanner mux 1 when the evo scanner is in mux mode
* @param srv__comms__can_rx_message_t *msg Message data from the CAN service layer
* @return None
* @note
*****************************************************************************/
static void srv__comms__handler_can_0x487_mux_1(srv__comms__can_rx_message_t *msg)
{
    uint32_t data = 0;
    uint32_t senRaw = 0;

#if SYS__MANAGER__EVO_SCANN_SEN_4_CONNECTED
    senRaw = (msg->data[1] << 8) | msg->data[2];

    data = (senRaw + 60000);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_EVO_SCANN_SEN_4](&data, &msg->timestamp);
#endif // SYS__MANAGER__EVO_SCANN_SEN_4_CONNECTED

#if SYS__MANAGER__EVO_SCANN_SEN_5_CONNECTED
    senRaw = (msg->data[3] << 8) | msg->data[4];

    data = (senRaw + 60000);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_EVO_SCANN_SEN_5](&data, &msg->timestamp);
#endif // SYS__MANAGER__EVO_SCANN_SEN_5_CONNECTED

#if SYS__MANAGER__EVO_SCANN_SEN_6_CONNECTED
    senRaw = (msg->data[5] << 8) | msg->data[6];

    data = (senRaw + 60000);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_EVO_SCANN_SEN_6](&data, &msg->timestamp);
#endif // SYS__MANAGER__EVO_SCANN_SEN_6_CONNECTED

    (void) data;
    (void) senRaw;
    (void) msg;
}

/*************************************************************************//**
* @brief Handles evo scanner mux 2 when the evo scanner is in mux mode
* @param srv__comms__can_rx_message_t *msg Message data from the CAN service layer
* @return None
* @note
*****************************************************************************/
static void srv__comms__handler_can_0x487_mux_2(srv__comms__can_rx_message_t *msg)
{
    uint32_t data = 0;
    uint32_t senRaw = 0;

#if SYS__MANAGER__EVO_SCANN_SEN_7_CONNECTED
    senRaw = (msg->data[1] << 8) | msg->data[2];

    data = (senRaw + 60000);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_EVO_SCANN_SEN_7](&data, &msg->timestamp);
#endif // SYS__MANAGER__EVO_SCANN_SEN_7_CONNECTED

#if SYS__MANAGER__EVO_SCANN_SEN_8_CONNECTED
    senRaw = (msg->data[3] << 8) | msg->data[4];

    data = (senRaw + 60000);

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_EVO_SCANN_SEN_8](&data, &msg->timestamp);
#endif // SYS__MANAGER__EVO_SCANN_SEN_8_CONNECTED

    (void) data;
    (void) senRaw;
    (void) msg;
}

#endif // SYS__MANAGER__CAN_BUS_ENABLED

#endif // SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED

#if SYS__MANAGER__SERIAL_ENABLED


#endif // SYS__MANAGER__SERIAL_ENABLED
/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/


