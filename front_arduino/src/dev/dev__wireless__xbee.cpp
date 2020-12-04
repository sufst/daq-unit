/*************************************************************************//**
* @file dev__wireless__xbee.cpp
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
  include files
----------------------------------------------------------------------------*/
#include "dev__wireless__xbee.h"

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef struct
{
    dev__wireless__xbee__rx_handler rxHandler;
} dev__wireless__xbee__internal_obj_t;
/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
static void dev__wireless__xbee_response_handler(Rx16Response& rx, uintptr_t);

/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  global variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/
static HardwareSerial *ArduinoUarts[] =
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

static dev__wireless__xbee__internal_obj_t dev__wireless__xbee__internal_obj;
/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Initialises the xbee library serial
* @param dev__wireless__xbee__obj_t *obj Object of the xbee device
* @return dev__wireless__xbee__state_t DEV__WIRELESS__XBEE__OK
* @note
*****************************************************************************/
void dev__wireless__xbee__init(dev__wireless__xbee__obj_t *obj)
{
    ArduinoUarts[obj->hw]->begin(obj->baud);

    obj->xbee.setSerial(*ArduinoUarts[obj->hw]);

    pinMode(obj->ctsPin, INPUT_PULLUP);
    pinMode(obj->rtsPin, OUTPUT);
    digitalWrite(obj->rtsPin, LOW);

    obj->tx64Request.setAddress64(obj->xbeeAddress64);

    obj->xbee.onRx16Response(dev__wireless__xbee_response_handler);

    obj->enabled = true;
}

/*************************************************************************//**
* @brief Register rx handler
* @param dev__wireless__xbee__rx_handler handler Callback function to register
* @return None
* @note
*****************************************************************************/
void dev__wireless__xbee__register_rx_handler(dev__wireless__xbee__rx_handler handler)
{
    dev__wireless__xbee__internal_obj.rxHandler = handler;
}

/*************************************************************************//**
* @brief Checks if the wireless device layer is ready for new data from service layer
* @param dev__wireless__xbee__obj_t *obj Object of the xbee device
* @return dev__wireless__xbee__state_t DEV__WIRELESS__XBEE__READY if ready,
*                                      DEV__WIRELESS__XBEE__NOT_READY if not ready
* @note
*****************************************************************************/
dev__wireless__xbee__state_t dev__wireless__xbee__get_status(dev__wireless__xbee__obj_t *obj)
{
    dev__wireless__xbee__state_t ret = DEV__WIRELESS__XBEE__READY;

    if (!obj->enabled)
    {
        ret = DEV__WIRELESS__XBEE__NOT_READY;
        goto exit;
    }

    /*
     * The xbee should have its flow control pins connected, but the xbee shield ignores them...
     */
//    if (digitalRead(obj->ctsPin))
//    {
//        ret = DEV__WIRELESS__XBEE__NOT_READY;
//        goto exit;
//    }

    /*
     * To ensure we dont block on writes, we ensure we have enough room in the uart buffer before we write
     */
    if (ArduinoUarts[obj->hw]->availableForWrite() < DEV__WIRELESS__XBEE__MAX_DATA_LEN)
    {
        ret = DEV__WIRELESS__XBEE__NOT_READY;
        goto exit;
    }

    exit:
    return ret;
}

/*************************************************************************//**
* @brief Loop the xbee library loop to process any received data from xbee and call callback function
* @param dev__wireless__xbee__obj_t *obj Object of the xbee device
* @return None
* @note
*****************************************************************************/
void dev__wireless__rx_process(dev__wireless__xbee__obj_t *obj)
{
    obj->xbee.loop();
}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Completed xbee response handler from the xbee library
* @param Rx64Response& rx Received rx frame
* @param uintptr_t Some uint16_t pointer not sure really whats it for
* @return None
* @note
*****************************************************************************/
static void dev__wireless__xbee_response_handler(Rx16Response& rx, uintptr_t)
{
    uint8_t *rxData = rx.getFrameData() + rx.getDataOffset();

    dev__wireless__xbee__internal_obj.rxHandler(rxData, rx.getDataLength());
}
/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/


