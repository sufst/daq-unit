/*************************************************************************//**
* @file dev__serial.cpp
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
  include files
----------------------------------------------------------------------------*/
#include "dev__serial.h"

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/
#define DEV__SERIAL__START_BYTE 0x57

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
static void dev__serial__rx_state_start(uint8_t uartByte, dev__serial__obj_t *obj);

static void dev__serial__rx_state_cmd(uint8_t uartByte, dev__serial__obj_t *obj);

static void dev__serial__rx_state_len(uint8_t uartByte, dev__serial__obj_t *obj);

static void dev__serial__rx_state_data(uint8_t uartByte, dev__serial__obj_t *obj);

static void dev__serial__rx_state_crc(uint8_t uartByte, dev__serial__obj_t *obj);

static void dev__serial__rx_state_err(uint8_t uartByte, dev__serial__obj_t *obj);

static void dev__serial__rx_state_fin(uint8_t uartByte, dev__serial__obj_t *obj);
/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  global variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/
static void (*const dev__serial__rx_state_funcs[7])(uint8_t uartByte, dev__serial__obj_t *obj) =
        {
                dev__serial__rx_state_start,
                dev__serial__rx_state_cmd,
                dev__serial__rx_state_len,
                dev__serial__rx_state_data,
                dev__serial__rx_state_crc,
                dev__serial__rx_state_err,
                dev__serial__rx_state_fin
        };

static HardwareSerial *const ArduinoUarts[DEV__SERIAL__ATTACHED_UARTS_AMT] =
        {
#if defined(__AVR_ATmega2560__)
                &Serial,
                &Serial1,
                &Serial2,
                &Serial3
#else
                &Serial
#endif
        };

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Initialises the wanted uart hardware layer
* @param dev__serial__obj_t *obj Serial device object
* @return None
* @note
*****************************************************************************/
void
dev__serial__init(dev__serial__obj_t *obj, uint8_t uart, uint32_t baud, dev__serial__rx_msg_callback_handle rxHandler)
{
    obj->arduinoSerial = ArduinoUarts[uart];
    obj->baud = baud;
    obj->rxCallback = rxHandler;

    obj->startByte = DEV__SERIAL__START_BYTE;

    obj->arduinoSerial->begin(obj->baud);

    obj->enabled = true;
}

/*************************************************************************//**
* @brief Process received bytes through corresponding rx state function
* @param dev__serial__obj_t *obj Serial device object
* @return None
* @note
*****************************************************************************/
void dev__serial__process_rx(dev__serial__obj_t *obj)
{
    if (obj->arduinoSerial->available() > 0)
    {
        uint8_t uartByte = obj->arduinoSerial->read();

        dev__serial__rx_state_funcs[obj->rx.rxState](uartByte, obj);
    }
}

/*************************************************************************//**
* @brief Disables the serial device
* @param dev__serial__obj_t *obj Serial device object
* @return None
* @note
*****************************************************************************/
void dev__serial__disable(dev__serial__obj_t *obj)
{
    obj->enabled = false;
}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Process receive byte start state function
* @param uint8_t uartByte Received uart byte to process
* @param dev__serial__obj_t *obj Serial device object
* @return None
* @note
*****************************************************************************/
static void dev__serial__rx_state_start(uint8_t uartByte, dev__serial__obj_t *obj)
{
    if (uartByte == obj->startByte)
    {
        obj->rx.rxState = DEV__SERIAL__RX_STATE_CMD;
    }
}

/*************************************************************************//**
* @brief Process receive byte cmd state function
* @param uint8_t uartByte Received uart byte to process
* @param dev__serial__obj_t *obj Serial device object
* @return None
* @note
*****************************************************************************/
static void dev__serial__rx_state_cmd(uint8_t uartByte, dev__serial__obj_t *obj)
{
    obj->rx.cmd = uartByte;

    obj->rx.rxState = DEV__SERIAL__RX_STATE_LEN;
}

/*************************************************************************//**
* @brief Process receive byte len state function
* @param uint8_t uartByte Received uart byte to process
* @param dev__serial__obj_t *obj Serial device object
* @return None
* @note
*****************************************************************************/
static void dev__serial__rx_state_len(uint8_t uartByte, dev__serial__obj_t *obj)
{
    obj->rx.len = uartByte;

    if ((obj->rx.len <= 0) || (obj->rx.len > DEV__SERIAL__MAX_SUPPORTED_MSG_LEN))
    {
        dev__serial__rx_state_err(uartByte, obj);
    }
    else
    {
        obj->rx.rxState = DEV__SERIAL__RX_STATE_DATA;
    }
}

/*************************************************************************//**
* @brief Process receive byte data state function
* @param uint8_t uartByte Received uart byte to process
* @param dev__serial__obj_t *obj Serial device object
* @return None
* @note
*****************************************************************************/
static void dev__serial__rx_state_data(uint8_t uartByte, dev__serial__obj_t *obj)
{
    obj->rx.rxData[obj->rx.head] = uartByte;

    obj->rx.head++;

    if (obj->rx.head == obj->rx.len)
    {
        obj->rx.rxState = DEV__SERIAL__RX_STATE_CRC;
    }
}

/*************************************************************************//**
* @brief Process receive byte crc state function
* @param uint8_t uartByte Received uart byte to process
* @param dev__serial__obj_t *obj Serial device object
* @return None
* @note
*****************************************************************************/
static void dev__serial__rx_state_crc(uint8_t uartByte, dev__serial__obj_t *obj)
{
    if (uartByte == util__checksum__get_crc8(obj->rx.rxData, obj->rx.len))
    {
        dev__serial__rx_state_fin(uartByte, obj);
    }
    else
    {
        dev__serial__rx_state_err(uartByte, obj);
    }
}

/*************************************************************************//**
* @brief Process receive byte error state function
* @param uint8_t uartByte Received uart byte to process
* @param dev__serial__obj_t *obj Serial device object
* @return None
* @note
*****************************************************************************/
static void dev__serial__rx_state_err(uint8_t uartByte, dev__serial__obj_t *obj)
{
    (void) uartByte;
    /*
     * For now we dont do anything if theres an error, just reset the state machine
     */
    obj->rx.head = 0;

    obj->rx.rxState = DEV__SERIAL__RX_STATE_START;
}

/*************************************************************************//**
* @brief Process receive byte finished state function
* @param uint8_t uartByte Received uart byte to process
* @param dev__serial__obj_t *obj Serial device object
* @return None
* @note
*****************************************************************************/
static void dev__serial__rx_state_fin(uint8_t uartByte, dev__serial__obj_t *obj)
{
    (void) uartByte;

    obj->rxCallback(&obj->rx);

    obj->rx.head = 0;

    obj->rx.rxState = DEV__SERIAL__RX_STATE_START;
}

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/


