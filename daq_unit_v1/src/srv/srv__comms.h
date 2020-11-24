/*************************************************************************//**
* @file srv__comms.h
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
  @brief Service for communication bus, CAN, wireless and serial
  To do: Modify comms list. // Piotr
----------------------------------------------------------------------------*/
#ifndef CONTROLLER_V2_SRV__COMMS_H
#define CONTROLLER_V2_SRV__COMMS_H
/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
#include "Arduino.h"

#include "../sys/sys__manager.h"
#include "srv__comms__protocols.h"
/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/
#if SYS__MANAGER__CAN_BUS_ENABLED

#define SRV__COMMS__CAN_TX_BUFFER_LEN 16
#define SRV__COMMS__CAN_RX_BUFFER_LEN 16

#endif // SYS__MANAGER__CAN_BUS_ENABLED

#if SYS__MANAGER__WIRELESS_ENABLED

#define SRV__COMMS__WIRELESS_TX_TAG_DATA_BUFF_LEN 512
#define SRV__COMMS__WIRELESS_TX_STATUS_BUFF_LEN 32

#endif // SRV__COMMS__WIRELESS_ENABLED

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef enum
{
    SRV__COMMS__ERROR_NONE,
    SRV__COMMS__ERROR
} srv__comms__state_t;

#if SYS__MANAGER__CAN_BUS_ENABLED

typedef struct
{
    uint16_t addr;
    uint8_t len;
    union
    {
        uint8_t data[8];
        uint16_t data16[4];
        uint32_t data32[2];
    };

} srv__comms__can_tx_message_t;

typedef struct
{
    uint16_t addr;
    uint8_t len;
    uint32_t timestamp;
    union
    {
        uint8_t data[8];
        uint16_t data16[4];
        uint32_t data32[2];
    };

} srv__comms__can_rx_message_t;

typedef enum
{
    SRV__COMMS__CAN_BUS_0 = 0x00,
    SRV__COMMS__CAN_BUS_1,
    SRV__COMMS__CAN_BUS_2,
    SRV__COMMS__CAN_BUS_3,
    SRV__COMMS__CAN_BUS_4
} srv__comms__can_bus_t;

typedef void (*srv__comms__can_err_callback_handle)(srv__comms__can_bus_t bus, uint32_t *events);

typedef void (*srv__comms__can_ecu_handle)(void);

#endif // SYS__MANAGER__CAN_BUS_ENABLED

#if SYS__MANAGER__WIRELESS_ENABLED

typedef enum
{
    SRV__COMMS__WIRELESS_UART_0 = 0x00,
    SRV__COMMS__WIRELESS_UART_1,
    SRV__COMMS__WIRELESS_UART_2,
    SRV__COMMS__WIRELESS_UART_3
} srv__comms__wireless_uart_t;

#endif // SRV__COMMS__WIRELESS_ENABLED

#if SYS__MANAGER__SERIAL_ENABLED

typedef enum
{
    SRV__COMMS__SERIAL_UART_0 = 0x00,
    SRV__COMMS__SERIAL_UART_1,
    SRV__COMMS__SERIAL_UART_2,
    SRV__COMMS__SERIAL_UART_3
} srv__comms__serial_uart_t;

#endif // SYS__MANAGER__SERIAL_ENABLED
/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
#if SYS__MANAGER__CAN_BUS_ENABLED

void srv__comms__can_set_cs_pin(srv__comms__can_bus_t bus, uint8_t csPin);

void srv__comms__can_set_int_pin(srv__comms__can_bus_t bus, uint8_t intPin);

void srv__comms__can_register_ecu_handler(srv__comms__can_ecu_handle callback);

srv__comms__state_t srv__comms__init_can(srv__comms__can_bus_t bus);

void srv__comms__can__write(srv__comms__can_bus_t bus, srv__comms__can_tx_message_t *msg);

void srv__comms__can_register_err_callback(srv__comms__can_err_callback_handle handle);

#endif // SYS__MANAGER__CAN_BUS_ENABLED

#if SYS__MANAGER__WIRELESS_ENABLED

void srv__comms__wireless_set_cts_pin(uint8_t ctsPin);

void srv__comms__wireless_set_rts_pin(uint8_t rtsPin);

void srv__comms__wireless_set_uart(srv__comms__wireless_uart_t uart);

void srv__comms__wireless_init();

void srv__comms__wireless_write_cmd_tag_data(uint8_t tag, void *data, void *timestamp);

void srv__comms__wireless_write_cmd_status(uint8_t tag, uint8_t status);

#endif // SYS__MANAGER__WIRELESS_ENABLED

#if SYS__MANAGER__SERIAL_ENABLED

void srv__comms__serial_init(srv__comms__serial_uart_t uart, uint32_t baud);

void srv__comms__serial_disable(srv__comms__serial_uart_t uart);

void srv__comms__serial_write_cmd_tag_data(srv__comms__serial_uart_t uart, uint8_t tag, void *data, void *timestamp);

#endif // SYS__MANAGER__SERIAL_ENABLED

void srv__comms__process();
/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/
#endif //CONTROLLER_V2_SRV__COMMS_H
/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
