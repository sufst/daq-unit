/*************************************************************************//**
* @file dev__serial.h
* @brief Serial device layer
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
#ifndef CONTROLLER_V2_DEV__SERIAL_H
#define CONTROLLER_V2_DEV__SERIAL_H

/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
#include "Arduino.h"

#include "../utils/util__checksum.h"
/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/
#define DEV__SERIAL__MAX_SUPPORTED_MSG_LEN 32

#if defined(__AVR_ATmega2560__)
#define DEV__SERIAL__ATTACHED_UARTS_AMT 4
#else
#define DEV__SERIAL__ATTACHED_UARTS_AMT 1
#endif // defined(__AVR_ATmega2560__)

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef enum
{
    DEV__SERIAL__UART_0 = 0x00,
    DEV__SERIAL__UART_1,
    DEV__SERIAL__UART_2,
    DEV__SERIAL__UART_3
} dev__serial__uart_t;

typedef enum
{
    DEV__SERIAL__RX_STATE_START = 0x00,
    DEV__SERIAL__RX_STATE_CMD,
    DEV__SERIAL__RX_STATE_LEN,
    DEV__SERIAL__RX_STATE_DATA,
    DEV__SERIAL__RX_STATE_CRC,
    DEV__SERIAL__RX_STATE_ERR,
    DEV__SERIAL__RX_STATE_FIN
} dev__serial__rx_state_t;

typedef struct
{
    uint8_t cmd;
    uint8_t len;
    uint8_t rxData[DEV__SERIAL__MAX_SUPPORTED_MSG_LEN];
    uint8_t head;
    dev__serial__rx_state_t rxState;
} dev__serial__rx_storage_t;

typedef struct
{
    uint8_t cmd;
    uint8_t len;
    uint8_t *txData;
} dev__serial__tx_storage_t;

typedef void (*dev__serial__rx_msg_callback_handle)(dev__serial__rx_storage_t *rx);

typedef struct
{
    HardwareSerial *arduinoSerial;
    uint32_t baud;
    dev__serial__tx_storage_t tx;
    dev__serial__rx_storage_t rx;
    dev__serial__rx_msg_callback_handle rxCallback;
    bool enabled;
    uint8_t startByte;
} dev__serial__obj_t;
/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
void
dev__serial__init(dev__serial__obj_t *obj, uint8_t uart, uint32_t baud, dev__serial__rx_msg_callback_handle rxHandler);

void dev__serial__write(dev__serial__obj_t *obj);

void dev__serial__process_rx(dev__serial__obj_t *obj);

void dev__serial__disable(dev__serial__obj_t *obj);
/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Write a message to the uart hardware layer
* @param dev__serial__obj_t *obj Serial device object
* @return None
* @note
*****************************************************************************/
inline void dev__serial__write(dev__serial__obj_t *obj)
{
    obj->arduinoSerial->write(obj->startByte);
    obj->arduinoSerial->write(obj->tx.cmd);
    obj->arduinoSerial->write(obj->tx.len);
    obj->arduinoSerial->write(obj->tx.txData, obj->tx.len);
    obj->arduinoSerial->write(util__checksum__get_crc8(obj->tx.txData, obj->tx.len));
}

/*************************************************************************//**
* @brief Check if serial device is enabled
* @param dev__serial__obj_t *obj Serial device object
* @return None
* @note
*****************************************************************************/
inline bool dev__serial__get_enabled(dev__serial__obj_t *obj)
{
    return obj->enabled;
}
/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif //CONTROLLER_V2_DEV__SERIAL_H
/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
