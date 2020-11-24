/*************************************************************************//**
* @file dev__wireless__xbee.h
* @brief Wireless device layer implementing a wrapper around the xbee Arduino library
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
    along with this program.  If not, see <https://www.gnu.org/licenses/>
*****************************************************************************/
/*----------------------------------------------------------------------------
  @brief
----------------------------------------------------------------------------*/

#ifndef CONTROLLER_DEV__WIRELESS__XBEE_H
#define CONTROLLER_DEV__WIRELESS__XBEE_H
/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
#include "Arduino.h"

#include "../libraries/XBee/XBee.h"
#include "../utils/util__cir__buff.h"
/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/
#define DEV__WIRELESS__XBEE__MAX_DATA_LEN 50

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef void (*dev__wireless__xbee__rx_handler)(uint8_t *data, uint8_t len);

typedef enum
{
    DEV__WIRELESS__XBEE__OK,
    DEV__WIRELESS__XBEE__ERR,
    DEV__WIRELESS__XBEE__READY,
    DEV__WIRELESS__XBEE__NOT_READY
} dev__wireless__xbee__state_t;

typedef enum
{
    DEV__WIRELESS__XBEE__HW__UART_0 = 0x00,
    DEV__WIRELESS__XBEE__HW__UART_1,
    DEV__WIRELESS__XBEE__HW__UART_2,
    DEV__WIRELESS__XBEE__HW__UART_3
} dev__wireless__xbee__uart_t;

typedef struct
{
    XBeeWithCallbacks xbee;
    XBeeAddress64 xbeeAddress64;
    Tx64Request tx64Request;
    util__cir__buff_t txTagDataBuff;
    util__cir__buff_t txStatusBuff;
    uint32_t baud;
    dev__wireless__xbee__uart_t hw;
    uint8_t ctsPin;
    uint8_t rtsPin;
    dev__wireless__xbee__rx_handler rxHandler;
    bool enabled;
} dev__wireless__xbee__obj_t;

/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
void dev__wireless__xbee__init(dev__wireless__xbee__obj_t *obj);

void dev__wireless__xbee__register_rx_handler(dev__wireless__xbee__rx_handler handler);

dev__wireless__xbee__state_t dev__wireless__xbee__get_status(dev__wireless__xbee__obj_t *obj);

void dev__wireless__rx_process(dev__wireless__xbee__obj_t *obj);
/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Write data to the xbee library
* @param dev__wireless__xbee__obj_t *obj Object of the xbee device
* @param uint8_t *data Data source
* @param uint8_t len Length of data (length of a block registered in dev__wireless__xbee__set_block_size)
* @return dev__wireless__xbee__state_t DEV__WIRELESS__XBEE__OK
* @note
*****************************************************************************/
inline void dev__wireless__xbee__write(dev__wireless__xbee__obj_t *obj, uint8_t *data, uint8_t len)
{
    obj->tx64Request.setPayload(data, len);

    obj->xbee.send(obj->tx64Request);
}
/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif //CONTROLLER_DEV__WIRELESS__XBEE_H
