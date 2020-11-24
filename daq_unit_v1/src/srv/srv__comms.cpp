/*************************************************************************//**
* @file srv__comms.cpp
* @brief Communication service layer
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
#include "srv__comms.h"
#include "srv__comms__handlers.h"

#if SYS__MANAGER__CAN_BUS_ENABLED

#include "../dev/dev__can__mcp2515.h"

#endif // SYS__MANAGER__CAN_BUS_ENABLED

#if SYS__MANAGER__WIRELESS_ENABLED

#include "../dev/dev__wireless__xbee.h"

#endif // SRV__COMMS__WIRELESS_ENABLED

#if SYS__MANAGER__SERIAL_ENABLED

#include "../dev/dev__serial.h"

#endif // SYS__MANAGER__SERIAL_ENABLED

#include "../sys/sys__manager__sensor__handlers.h"
/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
#if SYS__MANAGER__CAN_BUS_ENABLED

typedef struct
{
    srv__comms__can_err_callback_handle errCallback;
    dev__can__mcp2515__obj_t bus[SYS__MANAGER__CAN_BUS_ATTACHED_AMT];
    srv__comms__can_ecu_handle ecuHandler;
} srv__comms__can_obj_t;

#endif // SYS__MANAGER__CAN_BUS_ENABLED

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
#if SYS__MANAGER__CAN_BUS_ENABLED

static void srv__comms__can_process_rx(dev__can__mcp2515__obj_t *busObj);

static void srv__comms__can_process_tx(dev__can__mcp2515__obj_t *busObj);

static void srv__comms__can_bus_handler(srv__comms__can_bus_t bus);

static void srv__comms__can_bus_0_int_handler();

#endif // SYS__MANAGER__CAN_BUS_ENABLED

#if SYS__MANAGER__WIRELESS_ENABLED

static void srv__comms__wireless_process();

static void srv__comms__wireless_process_tag_data(uint8_t *txPayload);

static void srv__comms__wireless_process_status(uint8_t *txPayload);


static void srv__comms__wireless_rx_handler(uint8_t *data, uint8_t len);

#endif // SRV__COMMS__WIRELESS_ENABLED

#if SYS__MANAGER__SERIAL_ENABLED

static void srv__comms__serial_rx_complete_handler(dev__serial__rx_storage_t *rx);

#endif // SYS__MANAGER__SERIAL_ENABLED
/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  global variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/
#if SYS__MANAGER__CAN_BUS_ENABLED

static srv__comms__can_tx_message_t srv__comms__can_bus_0_tx_buff[SRV__COMMS__CAN_TX_BUFFER_LEN];
static srv__comms__can_tx_message_t srv__comms__can_bus_0_rx_buff[SRV__COMMS__CAN_RX_BUFFER_LEN];

static srv__comms__can_obj_t srv__comms__can_obj;

#endif // SYS__MANAGER__CAN_BUS_ENABLED

#if SYS__MANAGER__WIRELESS_ENABLED

static dev__wireless__xbee__obj_t dev__wireless__xbee__obj;

static uint8_t srv__comms__wireless_tx_tag_data_buff[SRV__COMMS__WIRELESS_TX_TAG_DATA_BUFF_LEN];
static uint8_t srv__comms__wireless_tx_status_buff[SRV__COMMS__WIRELESS_TX_STATUS_BUFF_LEN];

#endif // SRV__COMMS__WIRELESS_ENABLED

#if SYS__MANAGER__SERIAL_ENABLED

static dev__serial__obj_t dev__serial__obj[DEV__SERIAL__ATTACHED_UARTS_AMT];

#endif // SYS__MANAGER__SERIAL_ENABLED
/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Communication service process loop
* @param None
* @return None
* @note
*****************************************************************************/
void srv__comms__process()
{
#if SYS__MANAGER__CAN_BUS_ENABLED

    for (uint8_t i = 0; i < SYS__MANAGER__CAN_BUS_ATTACHED_AMT; i++)
    {
        dev__can__mcp2515__obj_t *busObj = &srv__comms__can_obj.bus[i];

        /*
         * Just incase we missed any interrupt events
         */

        while (!digitalRead(busObj->intPin))
        {
            srv__comms__can_bus_handler((srv__comms__can_bus_t) i);
        }

        srv__comms__can_process_rx(busObj);

        srv__comms__can_process_tx(busObj);
    }

#endif // SYS__MANAGER__CAN_BUS_ENABLED

#if SYS__MANAGER__WIRELESS_ENABLED

    srv__comms__wireless_process();

#endif // SRV__COMMS__WIRELESS_ENABLED

#if SYS__MANAGER__SERIAL_ENABLED

    for (uint8_t i = 0; i < DEV__SERIAL__ATTACHED_UARTS_AMT; i++)
    {
        dev__serial__obj_t *serial = &dev__serial__obj[i];
        if (dev__serial__get_enabled(serial))
        {
            dev__serial__process_rx(serial);
        }
    }

#endif // SYS__MANAGER__SERIAL_ENABLED
}

#if SYS__MANAGER__CAN_BUS_ENABLED

/*************************************************************************//**
* @brief Set a can bus CS pin
* @param srv__comms__can_bus_t bus Bus to set
* @param uint8_t csPin CS pin to set
* @return None
* @note
*****************************************************************************/
void srv__comms__can_set_cs_pin(srv__comms__can_bus_t bus, uint8_t csPin)
{
    srv__comms__can_obj.bus[bus].csPin = csPin;
}

/*************************************************************************//**
* @brief Set a can bus INT pin
* @param srv__comms__can_bus_t bus Bus to set
* @param uint8_t csPin INT pin to set
* @return None
* @note
*****************************************************************************/
void srv__comms__can_set_int_pin(srv__comms__can_bus_t bus, uint8_t intPin)
{
    srv__comms__can_obj.bus[bus].intPin = intPin;
}

/*************************************************************************//**
* @brief Set a can bus INT pin
* @param srv__comms__can_ecu_handle callback ECU event handler function
* @return None
* @note
*****************************************************************************/
void srv__comms__can_register_ecu_handler(srv__comms__can_ecu_handle callback)
{
    srv__comms__can_obj.ecuHandler = callback;
}

/*************************************************************************//**
* @brief Initialise a can bus
* @param srv__comms__can_bus_t bus Bus to initialise
* @return srv__comms__state_t SRV__COMMS__ERROR_NONE if successful,
*                             SRV__COMMS__ERROR if failed
* @note Also registers all CAN handler functions
*****************************************************************************/
srv__comms__state_t srv__comms__init_can(srv__comms__can_bus_t bus)
{
    srv__comms__state_t ret = SRV__COMMS__ERROR_NONE;

    if (bus >= SYS__MANAGER__CAN_BUS_ATTACHED_AMT)
    {
        ret = SRV__COMMS__ERROR;
        goto fail;
    }

    srv__comms__can_obj.bus[0].handler = srv__comms__can_bus_0_int_handler;

    if (dev__can__mcp2515__init(&srv__comms__can_obj.bus[bus]) != DEV__CAN__MCP2515__OK)
    {
        ret = SRV__COMMS__ERROR;
        goto fail;
    }

    util__cir__buff__init(&srv__comms__can_obj.bus[bus].txBuff, srv__comms__can_bus_0_tx_buff,
                          SRV__COMMS__CAN_TX_BUFFER_LEN, sizeof(srv__comms__can_tx_message_t));

    util__cir__buff__init(&srv__comms__can_obj.bus[bus].rxBuff, srv__comms__can_bus_0_rx_buff,
                          SRV__COMMS__CAN_RX_BUFFER_LEN, sizeof(srv__comms__can_rx_message_t));

    return ret;

    fail:
    return ret;
}

/*************************************************************************//**
* @brief Add CAN message to the CAN write buffer
* @param srv__comms__can_bus_t bus Bus to send message over
* @param srv__comms__can_tx_message_t *msg CAN message to send
* @return None
* @note
*****************************************************************************/
void srv__comms__can__write(srv__comms__can_bus_t bus, srv__comms__can_tx_message_t *msg)
{
    dev__can__mcp2515__obj_t *busObj = &(srv__comms__can_obj.bus[bus]);

    util__cir__buff__write(&(busObj->txBuff), msg);
}

/*************************************************************************//**
* @brief Register CAN bus error handler
* @param srv__comms__can_err_callback_handle handle Handler function
* @return None
* @note
*****************************************************************************/
void srv__comms__can_register_err_callback(srv__comms__can_err_callback_handle handle)
{
    srv__comms__can_obj.errCallback = handle;
}

#endif // SYS__MANAGER__CAN_BUS_ENABLED

#if SYS__MANAGER__WIRELESS_ENABLED

/*************************************************************************//**
* @brief Set CTS pin of wireless
* @param None
* @return None
* @note
*****************************************************************************/
void srv__comms__wireless_set_cts_pin(uint8_t ctsPin)
{
    dev__wireless__xbee__obj.ctsPin = ctsPin;
}

/*************************************************************************//**
* @brief Set RTS pin of wireless
* @param None
* @return None
* @note
*****************************************************************************/
void srv__comms__wireless_set_rts_pin(uint8_t rtsPin)
{
    dev__wireless__xbee__obj.rtsPin = rtsPin;
}

/*************************************************************************//**
* @brief Set uart of the wireless device
* @param srv__comms__wireless_uart_t uart Uart channel
* @return None
* @note
*****************************************************************************/
void srv__comms__wireless_set_uart(srv__comms__wireless_uart_t uart)
{
    dev__wireless__xbee__obj.hw = (dev__wireless__xbee__uart_t) uart;
    dev__wireless__xbee__obj.baud = SYS__MANAGER__WIRELESS_BAUD_RATE;
}

/*************************************************************************//**
* @brief Initialise the wireless device with set configuration
* @param None
* @return None
* @note
*****************************************************************************/
void srv__comms__wireless_init()
{
    dev__wireless__xbee__obj.xbeeAddress64.setMsb(SYS__MANAGER__WIRELESS_TARGET_ADDRESS_UPPER);
    dev__wireless__xbee__obj.xbeeAddress64.setLsb(SYS__MANAGER__WIRELESS_TARGET_ADDRESS_LOWER);

    dev__wireless__xbee__register_rx_handler(srv__comms__wireless_rx_handler);

    util__cir__buff__init(&(dev__wireless__xbee__obj.txTagDataBuff), srv__comms__wireless_tx_tag_data_buff,
                          SRV__COMMS__WIRELESS_TX_TAG_DATA_BUFF_LEN, 1);

    util__cir__buff__init(&(dev__wireless__xbee__obj.txStatusBuff), srv__comms__wireless_tx_status_buff,
                          SRV__COMMS__WIRELESS_TX_STATUS_BUFF_LEN, 1);

    dev__wireless__xbee__init(&dev__wireless__xbee__obj);
}

/*************************************************************************//**
* @brief Add data to the wireless tag data cmd write buffer
* @param void *data Data to add
* @param uint8_t len Length of data
* @return None
* @note
*****************************************************************************/
void srv__comms__wireless_write_cmd_tag_data(uint8_t tag, void *data, void *timestamp)
{
    uint8_t *datau8 = (uint8_t *) data;
    uint8_t *timestampu8 = (uint8_t *) timestamp;

    if (!dev__wireless__xbee__obj.enabled)
    {
        goto fail;
    }

    util__cir__buff__write(&dev__wireless__xbee__obj.txTagDataBuff, &tag);

    for (uint8_t i = 0; i < sys__manager__sensor__handlers__tag_length_from_tag[tag]; i++)
    {
        util__cir__buff__write(&dev__wireless__xbee__obj.txTagDataBuff, &(datau8[i]));
    }

    for (uint8_t i = 0; i < 4; i++)
    {
        util__cir__buff__write(&dev__wireless__xbee__obj.txTagDataBuff, &(timestampu8[i]));
    }

    fail:
    return;
}

/*************************************************************************//**
* @brief Add data to the wireless status cmd write buffer
* @param uint8_t tag Status tag
* @param uint8_t status Status of the tag
* @return None
* @note
*****************************************************************************/
void srv__comms__wireless_write_cmd_status(uint8_t tag, uint8_t status)
{
    if (!dev__wireless__xbee__obj.enabled)
    {
        goto fail;
    }

    util__cir__buff__write(&dev__wireless__xbee__obj.txStatusBuff, &tag);
    util__cir__buff__write(&dev__wireless__xbee__obj.txStatusBuff, &status);

    fail:
    return;
}


#endif // SRV__COMMS__WIRELESS_ENABLED

#if SYS__MANAGER__SERIAL_ENABLED

/*************************************************************************//**
* @brief Initialise uart channel
* @param srv__comms__serial_uart_t uart Uart channel to initialise
* @return uint32_t baud Baud rate of channel
* @note
*****************************************************************************/
void srv__comms__serial_init(srv__comms__serial_uart_t uart, uint32_t baud)
{
    dev__serial__init(&dev__serial__obj[uart], uart, baud, srv__comms__serial_rx_complete_handler);
}

/*************************************************************************//**
* @brief Disable a uart channel
* @param srv__comms__serial_uart_t uart Uart channel to disable
* @note
*****************************************************************************/
void srv__comms__serial_disable(srv__comms__serial_uart_t uart)
{
    dev__serial__disable(&dev__serial__obj[uart]);
}

/*************************************************************************//**
* @brief Write a command with data to the serial uart
* @param srv__comms__serial_uart_t uart Uart channel to write to
* @param srv__comms__protocols__cmd_t cmd Message command
* @param void *data Data to send
* @param uint8_t len Length of data
* @return None
* @note
*****************************************************************************/
void srv__comms__serial_write_cmd_tag_data(srv__comms__serial_uart_t uart, uint8_t tag, void *data, void *timestamp)
{
    dev__serial__obj[uart].tx.cmd = SRV__COMMS__PROTOCOLS__CMD_TAG_DATA;

    static uint8_t txData[16];

    uint8_t tagDataLen = sys__manager__sensor__handlers__tag_length_from_tag[tag];
    const uint8_t timestampLen = 4;

    txData[0] = tag;
    memcpy(&(txData[1]), data, tagDataLen);
    memcpy(&(txData[1 + tagDataLen]), timestamp, timestampLen);

    dev__serial__obj[uart].tx.txData = txData;
    dev__serial__obj[uart].tx.len = 1 + tagDataLen + timestampLen;

    dev__serial__write(&dev__serial__obj[uart]);
}

#endif // SYS__MANAGER__SERIAL_ENABLED
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/
#if SYS__MANAGER__CAN_BUS_ENABLED

/*************************************************************************//**
* @brief Handle CAN bus events and any received data
* @param None
* @return None
* @note
*****************************************************************************/
static void srv__comms__can_bus_handler(srv__comms__can_bus_t bus)
{
    dev__can__mcp2515__obj_t *busObj = &(srv__comms__can_obj.bus[bus]);

    srv__comms__can_rx_message_t msg;

    if (dev__can__mcp2515__read(busObj, &msg) != DEV__CAN__MCP2515__RX_EMPTY)
    {
        util__cir__buff__write(&(busObj->rxBuff), &msg);
    }

    dev__can__mcp2515__events_t events = dev__can__mcp2515__get_errors(busObj);

    if (events.errorEvents.events > 0)
    {
        if (srv__comms__can_obj.errCallback != NULL)
        {
            srv__comms__can_obj.errCallback(bus, (uint32_t *) &events);
        }
    }
}

/*************************************************************************//**
* @brief CAN process any received data and check for any callbacks for the received data addresses
* @param None
* @return None
* @note
*****************************************************************************/
static void srv__comms__can_process_rx(dev__can__mcp2515__obj_t *busObj)
{
    while (util__cir__buff__available(&(busObj->rxBuff)) > 0)
    {
        static srv__comms__can_rx_message_t msg;

        /*
         * Avoid cases where we could received a message as we are reading from the buffer
         */
        noInterrupts();
        util__cir__buff__read(&(busObj->rxBuff), &msg);
        interrupts();

        if ((msg.addr >= 0x2000) && (msg.addr <= 0x2008))
        {
            srv__comms__handlers__from_can_0x2000_region[msg.addr & 0xFF](&msg);
            srv__comms__can_obj.ecuHandler();
        }
#if SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED
        else if (msg.addr == 0x487)
        {
            srv__comms__handlers__from_can_0x487_region[0](&msg);
        }
#endif // SYS__MANAGER__EVO_SCANN_SENSORS_ENABLED
    }
}

/*************************************************************************//**
* @brief CAN process any requested transmissions
* @param dev__can__mcp2515__obj_t *busObj CAN bus object
* @return None
* @note
*****************************************************************************/
static void srv__comms__can_process_tx(dev__can__mcp2515__obj_t *busObj)
{
    if (util__cir__buff__available(&(busObj->txBuff)) > 0)
    {
        srv__comms__can_tx_message_t *txMsg = (srv__comms__can_tx_message_t *) util__cir__buff__peek_tail(
                &(busObj->txBuff));

        if (dev__can__mcp2515__write(busObj, txMsg) == DEV__CAN__MCP2515__TX_FULL)
        {
            return;
        }

        util__cir__buff__increment_tail(&(busObj->txBuff));
    }
}

/*************************************************************************//**
* @brief Handles CAN bus 0 interrupts
* @param None
* @return None
* @note
*****************************************************************************/
static void srv__comms__can_bus_0_int_handler()
{
    srv__comms__can_bus_handler((srv__comms__can_bus_t) 0);
}

#endif // SYS__MANAGER__CAN_BUS_ENABLED

#if SYS__MANAGER__WIRELESS_ENABLED

/*************************************************************************//**
* @brief Wireless process loop
* @param None
* @return None
* @note
*****************************************************************************/
static void srv__comms__wireless_process()
{
    dev__wireless__rx_process(&dev__wireless__xbee__obj);

    static uint8_t txPayload[DEV__WIRELESS__XBEE__MAX_DATA_LEN];

    srv__comms__wireless_process_tag_data(txPayload);

    srv__comms__wireless_process_status(txPayload);
}

/*************************************************************************//**
* @brief Wireless process any tag data in the tag data buffer
* @param None
* @return None
* @note
*****************************************************************************/
static void srv__comms__wireless_process_tag_data(uint8_t *txPayload)
{
    uint16_t available = util__cir__buff__available(&dev__wireless__xbee__obj.txTagDataBuff);

    if (available > 0)
    {
        if (dev__wireless__xbee__get_status(&dev__wireless__xbee__obj) != DEV__WIRELESS__XBEE__READY)
        {
            goto fail;
        }

        txPayload[0] = SRV__COMMS__PROTOCOLS__CMD_TAG_DATA;
        uint8_t len = 1;

        const uint8_t txPayloadAimForLen = 30;

        while ((len < txPayloadAimForLen) &&
               (util__cir__buff__available(&dev__wireless__xbee__obj.txTagDataBuff) > 0))
        {
            uint8_t *tag = &txPayload[len];

            util__cir__buff__read(&dev__wireless__xbee__obj.txTagDataBuff, tag);
            len++;

            const uint8_t timestampLen = 4;

            for (uint8_t i = 0; i < (sys__manager__sensor__handlers__tag_length_from_tag[*tag] + timestampLen); i++)
            {
                util__cir__buff__read(&dev__wireless__xbee__obj.txTagDataBuff, &txPayload[len++]);
            }
        }

        dev__wireless__xbee__write(&dev__wireless__xbee__obj, txPayload, len);
    }

    fail:
    return;
}

/*************************************************************************//**
* @brief Wireless process any status updates in the status buffer
* @param None
* @return None
* @note
*****************************************************************************/
static void srv__comms__wireless_process_status(uint8_t *txPayload)
{
    uint16_t available = util__cir__buff__available(&dev__wireless__xbee__obj.txStatusBuff);

    if (available > 0)
    {
        if (dev__wireless__xbee__get_status(&dev__wireless__xbee__obj) != DEV__WIRELESS__XBEE__READY)
        {
            goto fail;
        }

        txPayload[0] = SRV__COMMS__PROTOCOLS__CMD_STATUS;
        uint8_t len = 1;

        const uint8_t txPayloadAimForLen = 30;

        while ((util__cir__buff__available(&dev__wireless__xbee__obj.txStatusBuff) > 0) &&
               (len <= txPayloadAimForLen))
        {
            // Read status tag and then status data from buffer into payload
            util__cir__buff__read(&dev__wireless__xbee__obj.txStatusBuff, &txPayload[len++]);
            util__cir__buff__read(&dev__wireless__xbee__obj.txStatusBuff, &txPayload[len++]);
        }

        dev__wireless__xbee__write(&dev__wireless__xbee__obj, txPayload, len);
    }

    fail:
    return;
}

/*************************************************************************//**
* @brief Handle received wireless data
* @param uint8_t *data The received data
* @param uint8_t len Length of the received data
* @return None
* @note
*****************************************************************************/
static void srv__comms__wireless_rx_handler(uint8_t *data, uint8_t len)
{
    (void) len;

    const uint8_t cmdOffset = 0;
    const uint8_t dataOffset = 2;
    const uint8_t lenOffset = 1;

    srv__comms__handlers__from_cmd[data[cmdOffset]]((void *) (data + dataOffset), data[lenOffset]);
}

#endif // SRV__COMMS__WIRELESS_ENABLED

#if SYS__MANAGER__SERIAL_ENABLED

/*************************************************************************//**
* @brief Handle when device layer detects a completed rx message
* @param dev__serial__rx_storage_t *rx Complete message
* @return None
* @note
*****************************************************************************/
static void srv__comms__serial_rx_complete_handler(dev__serial__rx_storage_t *rx)
{
    srv__comms__handlers__from_cmd[rx->cmd](rx->rxData, rx->len);
}

#endif // SYS__MANAGER__SERIAL_ENABLED
/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/

