/*************************************************************************//**
* @file dev__can__mcp2515.h
* @brief CAN device layer implementing the MCP2515 CAN Controller
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

#ifndef DEV__MCP2515_H
#define DEV__MCP2515_H
/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
#include "Arduino.h"

#include "../srv/srv__comms.h"
#include "dev__can__mcp2515_regs.h"
#include "../utils/util__cir__buff.h"

/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef void (*dev__can__mcp2515__isr_handler)(void);

typedef union
{
    uint32_t events;
    struct
    {
        union
        {
            struct
            {
                uint8_t tx : 1;
                uint8_t rx: 1;
                uint8_t : 6;
            };
            uint8_t events;
        } infoEvents;

        union
        {
            struct
            {
                uint8_t tx : 1;
                uint8_t rx : 1;
                uint8_t : 6;
            };
            uint8_t events;
        } warningEvents;

        union
        {
            struct
            {
                struct
                {
                    uint8_t msgErr : 1;
                    uint8_t : 7;
                } errorEventsL;

                dev__can__mcp2515__eflg_t errorEventsH;
            };
            uint16_t events;
        } errorEvents;
    };
} dev__can__mcp2515__events_t;

typedef enum
{
    DEV__CAN__MCP2515__OK,
    DEV__CAN__MCP2515__ERR_BUS,
    DEV__CAN__MCP2515__ERR,
    DEV__CAN__MCP2515__TX_FULL,
    DEV__CAN__MCP2515__RX_EMPTY
} dev__can__mcp2515__state_t;

typedef struct
{
    uint8_t csPin;
    uint8_t intPin;
    util__cir__buff_t txBuff;
    util__cir__buff_t rxBuff;
    dev__can__mcp2515__isr_handler handler;
    bool enabled;
} dev__can__mcp2515__obj_t;

/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
dev__can__mcp2515__state_t dev__can__mcp2515__init(dev__can__mcp2515__obj_t *obj);

dev__can__mcp2515__events_t dev__can__mcp2515__get_errors(dev__can__mcp2515__obj_t *obj);

dev__can__mcp2515__state_t dev__can__mcp2515__write(dev__can__mcp2515__obj_t *obj, srv__comms__can_tx_message_t *msg);

dev__can__mcp2515__state_t dev__can__mcp2515__read(dev__can__mcp2515__obj_t *obj, srv__comms__can_rx_message_t *msg);
/*----------------------------------------------------------------------------s
  inlines
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif //DEV__MCP2515_H
