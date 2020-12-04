/*************************************************************************//**
* @file dev__can__mcp2515.cpp
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
/*----------------------------------------------------------------------------
  include files
----------------------------------------------------------------------------*/
#include "dev__can__mcp2515.h"
#include "../srv/srv__comms.h"

#include <SPI.h>
/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
static void dev__can__mcp2515__read_rx0(dev__can__mcp2515__obj_t *obj, srv__comms__can_rx_message_t *msg);

static void dev__can__mcp2515__read_rx1(dev__can__mcp2515__obj_t *obj, srv__comms__can_rx_message_t *msg);

static void dev__can__mcp2515__write_cmd(dev__can__mcp2515__obj_t *obj, dev__can__mcp2515__cmd_t cmd);

static void
dev__can__mcp2515__write_reg(dev__can__mcp2515__obj_t *obj, dev__can__mcp2515__reg_addr_t regAddr, uint8_t data);

static void
dev__can__mcp2515__read_reg(dev__can__mcp2515__obj_t *obj, dev__can__mcp2515__reg_addr_t regAddr, uint8_t *data);

static void dev__can__mcp2515__write_bit_modify(dev__can__mcp2515__obj_t *obj, dev__can__mcp2515__reg_addr_t regAddr,
                                                dev__can__mcp2515__mask_byte_t mask, uint8_t data);

static dev__can__mcp2515__state_t dev__can__mcp2515__enter_config_mode(dev__can__mcp2515__obj_t *obj);

static void dev__can__mcp2515__init_buffers(dev__can__mcp2515__obj_t *obj);

static void dev__can__mcp2515__init_filters(dev__can__mcp2515__obj_t *obj);

static void dev__can__mcp2515__init_baud_rate(dev__can__mcp2515__obj_t *obj);

static void dev__can__mcp2515__init_interrupts(dev__can__mcp2515__obj_t *obj);

static dev__can__mcp2515__state_t dev__can__mcp2515__init_mcp2515(dev__can__mcp2515__obj_t *obj);

/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  global variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Initialises SPI and an attached MCP2515 controller
* @param dev__can__mcp2515__obj_t *obj Object of the attached MCP2515 controller
* @return dev__can__mcp2515__state_t DEV__CAN__MCP2515__OK if successful,
*                                    DEV__CAN__MCP2515__ERR if failed
* @note
*****************************************************************************/
dev__can__mcp2515__state_t dev__can__mcp2515__init(dev__can__mcp2515__obj_t *obj)
{
    dev__can__mcp2515__state_t ret = DEV__CAN__MCP2515__OK;

    if (obj->handler == NULL)
    {
        ret = DEV__CAN__MCP2515__ERR;
        goto exit;
    }

    if (!obj->enabled)
    {
        /*
         * init spi pins
         */

        pinMode(obj->csPin, OUTPUT);
        digitalWrite(obj->csPin, HIGH);

        SPI.begin();

        delay(1000); // Give the mcp2515 time before we talk to it
    }

    /*
     * reset the device
     */

    if ((ret = dev__can__mcp2515__enter_config_mode(obj)) != DEV__CAN__MCP2515__OK)
    {
        goto exit;
    }

    /*
     * Configure rx controller buffers
     */

    dev__can__mcp2515__init_buffers(obj);

    /*
     * Setup filters
     */

    dev__can__mcp2515__init_filters(obj);

    /*
     * Set 1000kbps baud rate
     */

    dev__can__mcp2515__init_baud_rate(obj);

    /*
     * Enable interrupt sources
     */

    dev__can__mcp2515__init_interrupts(obj);

    /*
     * Configure the mcp2515
     */

    if ((ret = dev__can__mcp2515__init_mcp2515(obj)) != DEV__CAN__MCP2515__OK)
    {
        goto exit;
    }

    if (!obj->enabled)
    {
        /*
         * init interrupt pin
         */

        pinMode(obj->intPin, INPUT_PULLUP);

        attachInterrupt(digitalPinToInterrupt(obj->intPin), obj->handler, FALLING);

        SPI.usingInterrupt(digitalPinToInterrupt(obj->intPin));
    }

    obj->enabled = true;

    exit:
    return ret;
}

/*************************************************************************//**
* @brief Returns any error events an attached MCP2515 controller
* @param dev__can__mcp2515__obj_t *obj Object of the attached MCP2515 controller
* @return dev__can__mcp2515__events_t Error events
* @note
*****************************************************************************/
dev__can__mcp2515__events_t dev__can__mcp2515__get_errors(dev__can__mcp2515__obj_t *obj)
{
    dev__can__mcp2515__events_t events;
    events.events = 0;

    dev__can__mcp2515__canintf_t canintf;
    canintf.reg = 0;

    /*
     * Read the controller interrupts pending reg
     */

    dev__can__mcp2515__read_reg(obj, DEV__CAN__MCP2515__CANINTF_ADDR, &canintf.reg);

    /*
     * Convert raw pending interrupts to service layer events
     */

    if (canintf.errif)
    {
        dev__can__mcp2515__eflg_t errorErrs;

        dev__can__mcp2515__read_reg(obj, DEV__CAN__MCP2515__EFLG_ADDR, &errorErrs.reg);

        events.errorEvents.errorEventsH.reg = errorErrs.reg;

        dev__can__mcp2515__write_bit_modify(obj, DEV__CAN__MCP2515__CANINTF_ADDR, DEV__CAN__MCP2515__CANINTF_ERRIF_BIT,
                                            (uint8_t)~DEV__CAN__MCP2515__CANINTF_ERRIF_BIT);
    }

    if (canintf.merrf)
    {
        dev__can__mcp2515__write_bit_modify(obj, DEV__CAN__MCP2515__CANINTF_ADDR, DEV__CAN__MCP2515__CANINTF_MERRF_BIT,
                                            (uint8_t)~DEV__CAN__MCP2515__CANINTF_MERRF_BIT);

        events.errorEvents.errorEventsL.msgErr = 1;
    }

    return events;
}

/*************************************************************************//**
* @brief Write transmission message to an attached MCP2515 controller
* @param dev__can__mcp2515__obj_t *obj Object of the attached MCP2515 controller
* @param srv__comms__can_tx_message_t *msg transmission message to transmit
* @return dev__can__mcp2515__state_t DEV__CAN__MCP2515__OK if successful,
*                                    DEV__CAN__MCP2515__TX_FULL if all tx buffers full
* @note
*****************************************************************************/
dev__can__mcp2515__state_t dev__can__mcp2515__write(dev__can__mcp2515__obj_t *obj, srv__comms__can_tx_message_t *msg)
{
    dev__can__mcp2515__state_t ret = DEV__CAN__MCP2515__OK;

    /*
     * Read the controller status to see if any tx buffers are empty
     */

    uint8_t readStatusTransfer[2] = {DEV__CAN__MCP2515__CMD_READ_STATUS, 0x00};
    dev__can__mcp2515__read_status_t *const status = (dev__can__mcp2515__read_status_t *) &(readStatusTransfer[1]);

    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    digitalWrite(obj->csPin, LOW);

    SPI.transfer(readStatusTransfer, 2);

    digitalWrite(obj->csPin, HIGH);
    SPI.endTransaction();

    /*
     * If no tx buffers are available then exit
     */

//    if (status->tx0req && status->tx1req && status->tx2req)
    if (status->tx0req)
    {
        ret = DEV__CAN__MCP2515__TX_FULL;
        goto exit;
    }

    /*
     * Reset tx message
     */

    static uint8_t mcpTxConfig[6];

    /*
     * Assign mcp2515 regs to the tx payload
     */

    static dev__can__mcp2515__txb_sidh_t *const sidhReg = (dev__can__mcp2515__txb_sidh_t *) &mcpTxConfig[1];
    static dev__can__mcp2515__txb_sidl_t *const sidlReg = (dev__can__mcp2515__txb_sidl_t *) &mcpTxConfig[2];
    static dev__can__mcp2515__txb_eid8_t *const eid8Reg = (dev__can__mcp2515__txb_eid8_t *) &mcpTxConfig[3];
    static dev__can__mcp2515__txb_eid0_t *const eid0Reg = (dev__can__mcp2515__txb_eid0_t *) &mcpTxConfig[4];
    static dev__can__mcp2515__txb_dlc_t *const dlcReg = (dev__can__mcp2515__txb_dlc_t *) &mcpTxConfig[5];

    /*
     * Determine which tx buffer to use
     */

//    mcpTxConfig[0] = (!status->tx0req) ? DEV__CAN__MCP2515__CMD_LOAD_TX_BUFFER_0_ADDR :
//                     (!status->tx1req) ? DEV__CAN__MCP2515__CMD_LOAD_TX_BUFFER_1_ADDR :
//                     DEV__CAN__MCP2515__CMD_LOAD_TX_BUFFER_2_ADDR;

    mcpTxConfig[0] = DEV__CAN__MCP2515__CMD_LOAD_TX_BUFFER_0_ADDR;

    /*
     * Determine if tx message should be an extended frame or not,
     * standard frame supports addresses up to 0x7FF
     */

    if (msg->addr <= 0x7FF)
    {
        sidhReg->reg = msg->addr >> 3;
        sidlReg->sid = msg->addr;
        sidlReg->exide = 0;
        sidlReg->eid = 0;
        eid8Reg->reg = 0;
        eid0Reg->reg = 0;
    }
    else
    {
        sidlReg->exide = 1;
        eid8Reg->reg = msg->addr >> 8;
        eid0Reg->reg = msg->addr;
    }

    /*
     * Load message length
     */
    dlcReg->dlc = msg->len;
    dlcReg->rtr = 0;

    /*
     * Load the tx buffer with the tx request
     */

    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    digitalWrite(obj->csPin, LOW);

    SPI.transfer(mcpTxConfig, sizeof(mcpTxConfig));
    SPI.transfer(msg->data, msg->len);

    digitalWrite(obj->csPin, HIGH);
    SPI.endTransaction();

    /*
     * Send the ready to transmit command
     */

    dev__can__mcp2515__cmd_t rts;
    rts = DEV__CAN__MCP2515__CMD_RTS_TX_BUFFER_0;
//    rts = (!status->tx0req) ? DEV__CAN__MCP2515__CMD_RTS_TX_BUFFER_0 :
//          (!status->tx1req) ? DEV__CAN__MCP2515__CMD_RTS_TX_BUFFER_1 :
//          DEV__CAN__MCP2515__CMD_RTS_TX_BUFFER_2;

    dev__can__mcp2515__write_cmd(obj, rts);

    exit:
    return ret;
}

/*************************************************************************//**
* @brief Read any received messages from an attached MCP2515 controller
* @param dev__can__mcp2515__obj_t *obj Object of the attached MCP2515 controller
* @param srv__comms__can_rx_message_t *msg Pointer to message to read to
* @return dev__can__mcp2515__state_t DEV__CAN__MCP2515__OK if successful,
*                                    DEV__CAN__MCP2515__RX_EMPTY if no received messages
* @note
*****************************************************************************/
dev__can__mcp2515__state_t dev__can__mcp2515__read(dev__can__mcp2515__obj_t *obj, srv__comms__can_rx_message_t *msg)
{
    dev__can__mcp2515__state_t ret = DEV__CAN__MCP2515__OK;

    /*
     * Read the can rx status to see if any rx buffers are full
     */

    uint8_t readRxStatusTransfer[2] = {DEV__CAN__MCP2515__CMD_RX_STATUS, 0x00};
    dev__can__mcp2515__rx_status_t *const rxStatus = (dev__can__mcp2515__rx_status_t *) &
            (readRxStatusTransfer[1]);

    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    digitalWrite(obj->csPin, LOW);

    SPI.transfer(readRxStatusTransfer, 2);

    digitalWrite(obj->csPin, HIGH);
    SPI.endTransaction();

    /*
     * If no rx buffers are full then we have received no new messages, so exit
     */

    if (rxStatus->rx == DEV__CAN__MCP2515__RX_STATUS_RX_NONE)
    {
        ret = DEV__CAN__MCP2515__RX_EMPTY;
        goto exit;
    }

    /*
     * Determine which rx buffer is full
     */

    if ((rxStatus->rx == DEV__CAN__MCP2515__RX_STATUS_RX_0) || (rxStatus->rx == DEV__CAN__MCP2515__RX_STATUS_RX_0_1))
    {
        dev__can__mcp2515__read_rx0(obj, msg);
    }
    else
    {
        dev__can__mcp2515__read_rx1(obj, msg);
    }

    exit:
    return ret;
}

/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Resets and ensures we have entered config mode of an attached MCP2515 controller
* @param dev__can__mcp2515__obj_t *obj Object of the attached MCP2515 controller
* @return dev__can__mcp2515__state_t DEV__CAN__MCP2515__OK if successful,
*                                    DEV__CAN__MCP2515__ERR if failed
* @note
*****************************************************************************/
static dev__can__mcp2515__state_t dev__can__mcp2515__enter_config_mode(dev__can__mcp2515__obj_t *obj)
{
    dev__can__mcp2515__state_t ret = DEV__CAN__MCP2515__OK;

    dev__can__mcp2515__write_cmd(obj, DEV__CAN__MCP2515__CMD_RESET);

    dev__can__mcp2515__canstat_t mcp2515Canstat;
    mcp2515Canstat.reg = 0;

    dev__can__mcp2515__read_reg(obj, DEV__CAN__MCP2515__CANSTAT_0_ADDR, &mcp2515Canstat.reg);

    if (mcp2515Canstat.bits.opmod != DEV__CAN__MCP2515__CANSTAT_OPMOD_CONFIG)
    {
        ret = DEV__CAN__MCP2515__ERR;
        goto exit;
    }

    exit:
    return ret;
}

/*************************************************************************//**
* @brief Initialises the buffers of an attached MCP2515 controller
* @param dev__can__mcp2515__obj_t *obj Object of the attached MCP2515 controller
* @return None
* @note
*****************************************************************************/
static void dev__can__mcp2515__init_buffers(dev__can__mcp2515__obj_t *obj)
{
    dev__can__mcp2515__rxb0ctrl_t rxb0ctrl;
    rxb0ctrl.reg = 0;
    rxb0ctrl.bukt = 1; // Should enable rx1 roll over
    rxb0ctrl.rxm = DEV__CAN__MCP2515__RXM_FILTERS_ENABLED;

    dev__can__mcp2515__write_reg(obj, DEV__CAN__MCP2515__RXB0CTRL_ADDR, rxb0ctrl.reg);

    dev__can__mcp2515__rxb1ctrl_t rxb1Ctrl;
    rxb1Ctrl.reg = 0;
    rxb1Ctrl.rxm = DEV__CAN__MCP2515__RXM_FILTERS_ENABLED;

    dev__can__mcp2515__write_reg(obj, DEV__CAN__MCP2515__RXB1CTRL_ADDR, rxb1Ctrl.reg);
}

/*************************************************************************//**
* @brief Initialises the filters of an attached MCP2515 controller
* @param dev__can__mcp2515__obj_t *obj Object of the attached MCP2515 controller
* @return None
* @note
*****************************************************************************/
static void dev__can__mcp2515__init_filters(dev__can__mcp2515__obj_t *obj)
{
    dev__can__mcp2515__rxf_sidh_t rxfSidh;
    dev__can__mcp2515__rxf_sidl_t rxfSidl;
    dev__can__mcp2515__rxf_eid8_t rxfEid8;
    dev__can__mcp2515__rxf_eid0_t rxfEid0;

    // Setup rxm0 to accept all extended frames
    rxfSidh.reg = 0;
    rxfSidl.reg = 0;
    rxfSidl.exide = 1;
    rxfEid8.reg = 0;
    rxfEid0.reg = 0;

    dev__can__mcp2515__write_reg(obj, DEV__CAN__MCP2515__RXF0SIDH_ADDR, rxfSidh.reg);
    dev__can__mcp2515__write_reg(obj, DEV__CAN__MCP2515__RXF0SIDL_ADDR, rxfSidl.reg);
    dev__can__mcp2515__write_reg(obj, DEV__CAN__MCP2515__RXF0EID8_ADDR, rxfEid8.reg);
    dev__can__mcp2515__write_reg(obj, DEV__CAN__MCP2515__RXF0EID0_ADDR, rxfEid0.reg);

    // Setup rxm1 to accept all standard frames
    rxfSidh.reg = 0;
    rxfSidl.reg = 0;
    rxfEid8.reg = 0;
    rxfEid0.reg = 0;

    dev__can__mcp2515__write_reg(obj, DEV__CAN__MCP2515__RXF1SIDH_ADDR, rxfSidh.reg);
    dev__can__mcp2515__write_reg(obj, DEV__CAN__MCP2515__RXF1SIDL_ADDR, rxfSidl.reg);
    dev__can__mcp2515__write_reg(obj, DEV__CAN__MCP2515__RXF1EID8_ADDR, rxfEid8.reg);
    dev__can__mcp2515__write_reg(obj, DEV__CAN__MCP2515__RXF1EID0_ADDR, rxfEid0.reg);
}

/*************************************************************************//**
* @brief Initialises the baud rate of an attached MCP2515 controller
* @param dev__can__mcp2515__obj_t *obj Object of the attached MCP2515 controller
* @return None
* @note
*****************************************************************************/
static void dev__can__mcp2515__init_baud_rate(dev__can__mcp2515__obj_t *obj)
{
    uint8_t mcp1000kbpsCnf1;
    uint8_t mcp1000kbpsCnf2;
    uint8_t mcp1000kbpsCnf3;

    mcp1000kbpsCnf1 = DEV__CAN__MCP2515__16MHz_1000kBPS_CFG1;
    mcp1000kbpsCnf2 = DEV__CAN__MCP2515__16MHZ_1000kBPS_CFG2;
    mcp1000kbpsCnf3 = DEV__CAN__MCP2515__16MHZ_1000kBPS_CFG3;

    dev__can__mcp2515__write_reg(obj, DEV__CAN__MCP2515__CNF1_ADDR, mcp1000kbpsCnf1);
    dev__can__mcp2515__write_reg(obj, DEV__CAN__MCP2515__CNF2_ADDR, mcp1000kbpsCnf2);
    dev__can__mcp2515__write_reg(obj, DEV__CAN__MCP2515__CNF3_ADDR, mcp1000kbpsCnf3);
}

/*************************************************************************//**
* @brief Initialises the interrupts of an attached MCP2515 controller
* @param dev__can__mcp2515__obj_t *obj Object of the attached MCP2515 controller
* @return None
* @note
*****************************************************************************/
static void dev__can__mcp2515__init_interrupts(dev__can__mcp2515__obj_t *obj)
{
    dev__can__mcp2515__caninte_t mcp2515Caninte;
    mcp2515Caninte.reg = 0;
    mcp2515Caninte.rx0ie = 1;
    mcp2515Caninte.rx1ie = 1;
    mcp2515Caninte.tx0ie = 0;
    mcp2515Caninte.tx1ie = 0;
    mcp2515Caninte.tx2ie = 0;
    mcp2515Caninte.errie = 1;
    mcp2515Caninte.wakie = 0;
    mcp2515Caninte.merre = 0;

    dev__can__mcp2515__write_reg(obj, DEV__CAN__MCP2515__CANINTE_ADDR, mcp2515Caninte.reg);
}

/*************************************************************************//**
* @brief Initialises the attached MCP2515 controller
* @param dev__can__mcp2515__obj_t *obj Object of the attached MCP2515 controller
* @return dev__can__mcp2515__state_t DEV__CAN__MCP2515__OK if successful,
*                                    DEV__CAN__MCP2515__ERR if failed
* @note
*****************************************************************************/
static dev__can__mcp2515__state_t dev__can__mcp2515__init_mcp2515(dev__can__mcp2515__obj_t *obj)
{
    dev__can__mcp2515__state_t ret = DEV__CAN__MCP2515__OK;

    dev__can__mcp2515__canctrl_t mcp2515Canctrl;
    mcp2515Canctrl.reg = 0;

    mcp2515Canctrl.clkpre = 0;
    mcp2515Canctrl.clken = 0;   // disable clkout
    mcp2515Canctrl.osm = 0;     // enable tx retransmissions
    mcp2515Canctrl.abat = 0;
    // Configure the can controller operating mode
    mcp2515Canctrl.reqop = DEV__CAN__MCP2515__CANCTRL_REQOP_NORM;

    dev__can__mcp2515__write_reg(obj, DEV__CAN__MCP2515__CANCTRL_0_ADDR, mcp2515Canctrl.reg);

    /*
     * Ensure we have entered the correct mode
     */

    dev__can__mcp2515__canstat_t mcp2515Canstat;
    mcp2515Canstat.reg = 0;

    dev__can__mcp2515__read_reg(obj, DEV__CAN__MCP2515__CANSTAT_0_ADDR, &mcp2515Canstat.reg);

    if (mcp2515Canstat.bits.opmod != DEV__CAN__MCP2515__CANCTRL_REQOP_NORM)
    {
        ret = DEV__CAN__MCP2515__ERR;
        goto exit;
    }

    exit:
    return ret;
}

/*************************************************************************//**
* @brief Read message from an attached MCP2515 controller rx buffer 0
* @param dev__can__mcp2515__obj_t *obj Object of the attached MCP2515 controller
* @param srv__comms__can_rx_message_t *msg Pointer to message to read to
* @return None
* @note
*****************************************************************************/
static void dev__can__mcp2515__read_rx0(dev__can__mcp2515__obj_t *obj, srv__comms__can_rx_message_t *msg)
{
    static uint8_t mcpRxConfig[6];

    /*
     * Set command to read rx buffer 0
     */

    mcpRxConfig[0] = DEV__CAN__MCP2515__CMD_READ_RX_BUFFER_0_ADDR;

    /*
     * Assign mcp2515 registers to rx payload
     */

    static dev__can__mcp2515__rxb_sidh_t *const sidhReg = (dev__can__mcp2515__rxb_sidh_t *) &(mcpRxConfig[1]);
    static dev__can__mcp2515__rxb_sidl_t *const sidlReg = (dev__can__mcp2515__rxb_sidl_t *) &(mcpRxConfig[2]);
    static dev__can__mcp2515__rxb_eid8_t *const eid8Reg = (dev__can__mcp2515__rxb_eid8_t *) &(mcpRxConfig[3]);
    static dev__can__mcp2515__rxb_eid0_t *const eid0Reg = (dev__can__mcp2515__rxb_eid0_t *) &(mcpRxConfig[4]);
    static dev__can__mcp2515__rxb_dlc_t *const dlcReg = (dev__can__mcp2515__rxb_dlc_t *) &(mcpRxConfig[5]);

    /*
     * Read rx buffer 0
     */

    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    digitalWrite(obj->csPin, LOW);

    SPI.transfer(mcpRxConfig, sizeof(mcpRxConfig));
    SPI.transfer(msg->data, dlcReg->dlc);

    digitalWrite(obj->csPin, HIGH);
    SPI.endTransaction();

    /*
     * Determine if message was extended frame
     * *NOTE* only addresses up to 16 bits is support right now
     */

    if (!sidlReg->ide)
    {
        msg->addr = (sidhReg->reg << 3) | sidlReg->sid;
    }
    else
    {
        msg->addr = eid8Reg->reg << 8 | eid0Reg->reg;
    }

    msg->len = dlcReg->dlc;

    msg->timestamp = millis();

    /*
     * Reset rx0 interrupt flag
     */

    dev__can__mcp2515__write_bit_modify(obj, DEV__CAN__MCP2515__CANINTF_ADDR, DEV__CAN__MCP2515__CANINTF_RX0IF_BIT,
                                        ~DEV__CAN__MCP2515__CANINTF_RX0IF_BIT);
}

/*************************************************************************//**
* @brief Read message from an attached MCP2515 controller rx buffer 1
* @param dev__can__mcp2515__obj_t *obj Object of the attached MCP2515 controller
* @param srv__comms__can_rx_message_t *msg Pointer to message to read to
* @return None
* @note
*****************************************************************************/
static void dev__can__mcp2515__read_rx1(dev__can__mcp2515__obj_t *obj, srv__comms__can_rx_message_t *msg)
{
    static uint8_t mcpRxConfig[6];

    /*
     * Set command to read rx buffer 1
     */

    mcpRxConfig[0] = DEV__CAN__MCP2515__CMD_READ_RX_BUFFER_1_ADDR;

    /*
     * Assign mcp2515 registers to rx payload
     */

    static dev__can__mcp2515__rxb_sidh_t *const sidhReg = (dev__can__mcp2515__rxb_sidh_t *) &(mcpRxConfig[1]);
    static dev__can__mcp2515__rxb_sidl_t *const sidlReg = (dev__can__mcp2515__rxb_sidl_t *) &(mcpRxConfig[2]);
    static dev__can__mcp2515__rxb_eid8_t *const eid8Reg = (dev__can__mcp2515__rxb_eid8_t *) &(mcpRxConfig[3]);
    static dev__can__mcp2515__rxb_eid0_t *const eid0Reg = (dev__can__mcp2515__rxb_eid0_t *) &(mcpRxConfig[4]);
    static dev__can__mcp2515__rxb_dlc_t *const dlcReg = (dev__can__mcp2515__rxb_dlc_t *) &(mcpRxConfig[5]);

    /*
     * Read rx buffer 1
     */

    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    digitalWrite(obj->csPin, LOW);

    SPI.transfer(mcpRxConfig, sizeof(mcpRxConfig));
    SPI.transfer(msg->data, dlcReg->dlc);

    digitalWrite(obj->csPin, HIGH);
    SPI.endTransaction();

    /*
     * Determine if message was extended frame
     * *NOTE* only addresses up to 16 bits is support right now
     */

    if (!sidlReg->ide)
    {
        msg->addr = (sidhReg->reg << 3) | sidlReg->sid;
    }
    else
    {
        msg->addr = eid8Reg->reg << 8 | eid0Reg->reg;
    }

    msg->len = dlcReg->dlc;

    msg->timestamp = millis();

    /*
     * Reset rx1 interrupt flag
     */

    dev__can__mcp2515__write_bit_modify(obj, DEV__CAN__MCP2515__CANINTF_ADDR, DEV__CAN__MCP2515__CANINTF_RX1IF_BIT,
                                        ~DEV__CAN__MCP2515__CANINTF_RX1IF_BIT);
}

/*************************************************************************//**
* @brief Write command to an attached MCP2515 controller
* @param dev__can__mcp2515__obj_t *obj Object of the attached MCP2515 controller
* @param dev__can__mcp2515__cmd_t cmd Command to write
* @return None
* @note
*****************************************************************************/
static void dev__can__mcp2515__write_cmd(dev__can__mcp2515__obj_t *obj, dev__can__mcp2515__cmd_t cmd)
{
    uint8_t cmdByte = (uint8_t) cmd;

    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    digitalWrite(obj->csPin, LOW);

    SPI.transfer(cmdByte);

    digitalWrite(obj->csPin, HIGH);
    SPI.endTransaction();
}

/*************************************************************************//**
* @brief Write data to MCP2515 register address
* @param dev__can__mcp2515__obj_t *obj Object of the attached MCP2515 controller
* @param dev__can__mcp2515__reg_addr_t regAddr MCP2515 register address to write to
* @param uint8_t data Data to write
* @return None
* @note
*****************************************************************************/
static void
dev__can__mcp2515__write_reg(dev__can__mcp2515__obj_t *obj, dev__can__mcp2515__reg_addr_t regAddr, uint8_t data)
{
    static const uint8_t writeLength = 3;

    uint8_t mcpData[writeLength] = {DEV__CAN__MCP2515__CMD_WRITE, (uint8_t) regAddr, data};

    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    digitalWrite(obj->csPin, LOW);

    SPI.transfer(mcpData, writeLength);

    digitalWrite(obj->csPin, HIGH);
    SPI.endTransaction();
}

/*************************************************************************//**
* @brief Read data from an attached MCP2515 controller register address
* @param dev__can__mcp2515__obj_t *obj Object of the attached MCP2515 controller
* @param dev__can__mcp2515__reg_addr_t regAddr MCP2515 register address to read from
* @param uint8_t data Pointer to location to read data to
* @return None
* @note
*****************************************************************************/
static void
dev__can__mcp2515__read_reg(dev__can__mcp2515__obj_t *obj, dev__can__mcp2515__reg_addr_t regAddr, uint8_t *data)
{
    static const uint8_t readLength = 3;

    uint8_t mcpData[readLength] = {DEV__CAN__MCP2515__CMD_READ, (uint8_t) regAddr, 0x00};

    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    digitalWrite(obj->csPin, LOW);

    SPI.transfer(mcpData, readLength);

    digitalWrite(obj->csPin, HIGH);
    SPI.endTransaction();

    *data = mcpData[2];
}

/*************************************************************************//**
* @brief Modify a bit within an attached MCP2515 controller register
* @param dev__can__mcp2515__obj_t *obj Object of the attached MCP2515 controller
* @param dev__can__mcp2515__reg_addr_t regAddr MCP2515 register address to modify
* @param dev__can__mcp2515__mask_byte_t mask Mask to apply to register write
* @param uint8_t data Data to write to register
* @return None
* @note
*****************************************************************************/
static void dev__can__mcp2515__write_bit_modify(dev__can__mcp2515__obj_t *obj, dev__can__mcp2515__reg_addr_t regAddr,
                                                dev__can__mcp2515__mask_byte_t mask, uint8_t data)
{
    static const uint8_t writeLength = 4;

    uint8_t regAddrU8 = regAddr;

    uint8_t mcpData[writeLength] = {DEV__CAN__MCP2515__CMD_BIT_MODIFY, regAddrU8, mask, data};

    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    digitalWrite(obj->csPin, LOW);

    SPI.transfer(mcpData, writeLength);

    digitalWrite(obj->csPin, HIGH);
    SPI.endTransaction();
}

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/


