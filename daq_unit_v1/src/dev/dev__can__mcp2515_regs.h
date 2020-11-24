/*************************************************************************//**
* @file dev__can__mcp2515_regs.h
* @brief MCP2515 CAN Controller register declarations
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

#ifndef DEV__CAN__MCP2515_REGS_H
#define DEV__CAN__MCP2515_REGS_H

/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/
#define DEV__CAN__MCP2515__BFPCTRL_B0BFM_BIT        (uint8_t)(1 << 0)
#define DEV__CAN__MCP2515__BFPCTRL_B1BFM_BIT        (uint8_t)(1 << 1)
#define DEV__CAN__MCP2515__BFPCTRL_B0BFE_BIT        (uint8_t)(1 << 2)
#define DEV__CAN__MCP2515__BFPCTRL_B1BFE_BIT        (uint8_t)(1 << 3)
#define DEV__CAN__MCP2515__BFPCTRL_B0BFS_BIT        (uint8_t)(1 << 4)
#define DEV__CAN__MCP2515__BFPCTRL_B1BFS_BIT        (uint8_t)(1 << 5)

#define DEV__CAN__MCP2515__TXRTSCTRL_B0RTSM_BIT     (uint8_t)(1 << 0)
#define DEV__CAN__MCP2515__TXRTSCTRL_B1RTSM_BIT     (uint8_t)(1 << 1)
#define DEV__CAN__MCP2515__TXRTSCTRL_B2RTSM_BIT     (uint8_t)(1 << 2)
#define DEV__CAN__MCP2515__TXRTSCTRL_B0RTS_BIT      (uint8_t)(1 << 3)
#define DEV__CAN__MCP2515__TXRTSCTRL_B1RTS_BIT      (uint8_t)(1 << 4)
#define DEV__CAN__MCP2515__TXRTSCTRL_B2RTS_BIT      (uint8_t)(1 << 5)

#define DEV__CAN__MCP2515__CANSTAT_ICOD0_BIT        (uint8_t)(1 << 1)
#define DEV__CAN__MCP2515__CANSTAT_ICOD1_BIT        (uint8_t)(1 << 2)
#define DEV__CAN__MCP2515__CANSTAT_ICOD2_BIT        (uint8_t)(1 << 3)
#define DEV__CAN__MCP2515__CANSTAT_OPMOD0_BIT       (uint8_t)(1 << 5)
#define DEV__CAN__MCP2515__CANSTAT_OPMOD1_BIT       (uint8_t)(1 << 6)
#define DEV__CAN__MCP2515__CANSTAT_OPMOD2_BIT       (uint8_t)(1 << 7)

#define DEV__CAN__MCP2515__CANCTRL_CLKPRE0_BIT      (uint8_t)(1 << 0)
#define DEV__CAN__MCP2515__CANCTRL_CLKPRE1_BIT      (uint8_t)(1 << 1)
#define DEV__CAN__MCP2515__CANCTRL_CLKEN_BIT        (uint8_t)(1 << 2)
#define DEV__CAN__MCP2515__CANCTRL_OSM_BIT          (uint8_t)(1 << 3)
#define DEV__CAN__MCP2515__CANCTRL_ABAT_BIT         (uint8_t)(1 << 4)
#define DEV__CAN__MCP2515__CANCTRL_REQOP0_BIT       (uint8_t)(1 << 5)
#define DEV__CAN__MCP2515__CANCTRL_REQOP1_BIT       (uint8_t)(1 << 6)
#define DEV__CAN__MCP2515__CANCTRL_REQOP2_BIT       (uint8_t)(1 << 7)

#define DEV__CAN__MCP2515__CNF3_PHSEG20_BIT         (uint8_t)(1 << 0)
#define DEV__CAN__MCP2515__CNF3_PHSEG21_BIT         (uint8_t)(1 << 1)
#define DEV__CAN__MCP2515__CNF3_PHSEG22_BIT         (uint8_t)(1 << 2)
#define DEV__CAN__MCP2515__CNF3_WAKFIL_BIT          (uint8_t)(1 << 6)
#define DEV__CAN__MCP2515__CNF3_SOF_BIT             (uint8_t)(1 << 7)

#define DEV__CAN__MCP2515__CNF2_PRSEG0_BIT          (uint8_t)(1 << 0)
#define DEV__CAN__MCP2515__CNF2_PRSEG1_BIT          (uint8_t)(1 << 1)
#define DEV__CAN__MCP2515__CNF2_PRSEG2_BIT          (uint8_t)(1 << 2)
#define DEV__CAN__MCP2515__CNF2_PRSEG10_BIT         (uint8_t)(1 << 3)
#define DEV__CAN__MCP2515__CNF2_PRSEG11_BIT         (uint8_t)(1 << 4)
#define DEV__CAN__MCP2515__CNF2_PRSEG12_BIT         (uint8_t)(1 << 5)
#define DEV__CAN__MCP2515__CNF2_SAM_BIT             (uint8_t)(1 << 6)
#define DEV__CAN__MCP2515__CNF2_BTLMODE_BIT         (uint8_t)(1 << 7)

#define DEV__CAN__MCP2515__CNF1_BRP0_BIT            (uint8_t)(1 << 0)
#define DEV__CAN__MCP2515__CNF1_BRP1_BIT            (uint8_t)(1 << 1)
#define DEV__CAN__MCP2515__CNF1_BRP2_BIT            (uint8_t)(1 << 2)
#define DEV__CAN__MCP2515__CNF1_BRP3_BIT            (uint8_t)(1 << 3)
#define DEV__CAN__MCP2515__CNF1_BRP4_BIT            (uint8_t)(1 << 4)
#define DEV__CAN__MCP2515__CNF1_BRP5_BIT            (uint8_t)(1 << 5)
#define DEV__CAN__MCP2515__CNF1_SJW0_BIT            (uint8_t)(1 << 6)
#define DEV__CAN__MCP2515__CNF1_SJW1_BIT            (uint8_t)(1 << 7)

#define DEV__CAN__MCP2515__CANINTE_RX0IE_BIT        (uint8_t)(1 << 0)
#define DEV__CAN__MCP2515__CANINTE_RX1IE_BIT        (uint8_t)(1 << 1)
#define DEV__CAN__MCP2515__CANINTE_TX0IE_BIT        (uint8_t)(1 << 2)
#define DEV__CAN__MCP2515__CANINTE_TX1IE_BIT        (uint8_t)(1 << 3)
#define DEV__CAN__MCP2515__CANINTE_TX2IE_BIT        (uint8_t)(1 << 4)
#define DEV__CAN__MCP2515__CANINTE_ERRIE_BIT        (uint8_t)(1 << 5)
#define DEV__CAN__MCP2515__CANINTE_WAKIE_BIT        (uint8_t)(1 << 6)
#define DEV__CAN__MCP2515__CANINTE_MERRE_BIT        (uint8_t)(1 << 7)

#define DEV__CAN__MCP2515__CANINTF_RX0IF_BIT        (uint8_t)(1 << 0)
#define DEV__CAN__MCP2515__CANINTF_RX1IF_BIT        (uint8_t)(1 << 1)
#define DEV__CAN__MCP2515__CANINTF_TX0IF_BIT        (uint8_t)(1 << 2)
#define DEV__CAN__MCP2515__CANINTF_TX1IF_BIT        (uint8_t)(1 << 3)
#define DEV__CAN__MCP2515__CANINTF_TX2IF_BIT        (uint8_t)(1 << 4)
#define DEV__CAN__MCP2515__CANINTF_ERRIF_BIT        (uint8_t)(1 << 5)
#define DEV__CAN__MCP2515__CANINTF_WAKIF_BIT        (uint8_t)(1 << 6)
#define DEV__CAN__MCP2515__CANINTF_MERRF_BIT        (uint8_t)(1 << 7)

#define DEV__CAN__MCP2515__EFLG_EWARN_BIT           (uint8_t)(1 << 0)
#define DEV__CAN__MCP2515__EFLG_RXWAR_BIT           (uint8_t)(1 << 1)
#define DEV__CAN__MCP2515__EFLG_TXWAR_BIT           (uint8_t)(1 << 2)
#define DEV__CAN__MCP2515__EFLG_RXEP_BIT            (uint8_t)(1 << 3)
#define DEV__CAN__MCP2515__EFLG_TXEP_BIT            (uint8_t)(1 << 4)
#define DEV__CAN__MCP2515__EFLG_TXBO_BIT            (uint8_t)(1 << 5)
#define DEV__CAN__MCP2515__EFLG_RX0OVR_BIT          (uint8_t)(1 << 6)
#define DEV__CAN__MCP2515__EFLG_RX1OVR_BIT          (uint8_t)(1 << 7)

#define DEV__CAN__MCP2515__TXB0CTRL_TXP0_BIT        (uint8_t)(1 << 0)
#define DEV__CAN__MCP2515__TXB0CTRL_TXP1_BIT        (uint8_t)(1 << 1)
#define DEV__CAN__MCP2515__TXB0CTRL_TXREQ_BIT       (uint8_t)(1 << 3)
#define DEV__CAN__MCP2515__TXB0CTRL_TXERR_BIT       (uint8_t)(1 << 4)
#define DEV__CAN__MCP2515__TXB0CTRL_MLOA_BIT        (uint8_t)(1 << 5)
#define DEV__CAN__MCP2515__TXB0CTRL_ABTF_BIT        (uint8_t)(1 << 6)

#define DEV__CAN__MCP2515__TXB1CTRL_TXP0_BIT        (uint8_t)(1 << 0)
#define DEV__CAN__MCP2515__TXB1CTRL_TXP1_BIT        (uint8_t)(1 << 1)
#define DEV__CAN__MCP2515__TXB1CTRL_TXREQ_BIT       (uint8_t)(1 << 3)
#define DEV__CAN__MCP2515__TXB1CTRL_TXERR_BIT       (uint8_t)(1 << 4)
#define DEV__CAN__MCP2515__TXB1CTRL_MLOA_BIT        (uint8_t)(1 << 5)
#define DEV__CAN__MCP2515__TXB1CTRL_ABTF_BIT        (uint8_t)(1 << 6)

#define DEV__CAN__MCP2515__TXB2CTRL_TXP0_BIT        (uint8_t)(1 << 0)
#define DEV__CAN__MCP2515__TXB2CTRL_TXP1_BIT        (uint8_t)(1 << 1)
#define DEV__CAN__MCP2515__TXB2CTRL_TXREQ_BIT       (uint8_t)(1 << 3)
#define DEV__CAN__MCP2515__TXB2CTRL_TXERR_BIT       (uint8_t)(1 << 4)
#define DEV__CAN__MCP2515__TXB2CTRL_MLOA_BIT        (uint8_t)(1 << 5)
#define DEV__CAN__MCP2515__TXB2CTRL_ABTF_BIT        (uint8_t)(1 << 6)

#define DEV__CAN__MCP2515__RXB0CTRL_FILHIT0_BIT     (uint8_t)(1 << 0)
#define DEV__CAN__MCP2515__RXB0CTRL_BUKT1_BIT       (uint8_t)(1 << 1)
#define DEV__CAN__MCP2515__RXB0CTRL_BUKT_BIT        (uint8_t)(1 << 2)
#define DEV__CAN__MCP2515__RXB0CTRL_RXRTR_BIT       (uint8_t)(1 << 3)
#define DEV__CAN__MCP2515__RXB0CTRL_RXM0_BIT        (uint8_t)(1 << 5)
#define DEV__CAN__MCP2515__RXB0CTRL_RXM1_BIT        (uint8_t)(1 << 6)

#define DEV__CAN__MCP2515__RXB1CTRL_FILHIT0_BIT     (uint8_t)(1 << 0)
#define DEV__CAN__MCP2515__RXB1CTRL_BUKT1_BIT       (uint8_t)(1 << 1)
#define DEV__CAN__MCP2515__RXB1CTRL_BUKT_BIT        (uint8_t)(1 << 2)
#define DEV__CAN__MCP2515__RXB1CTRL_RXRTR_BIT       (uint8_t)(1 << 3)
#define DEV__CAN__MCP2515__RXB1CTRL_RXM0_BIT        (uint8_t)(1 << 5)
#define DEV__CAN__MCP2515__RXB1CTRL_RXM1_BIT        (uint8_t)(1 << 6)
/*----------------------------------------------------------------------------
  manifest constants
---------------------------------------------------------------------------*/
/*
 * Timings taken from
 * https://github.com/Seeed-Studio/CAN_BUS_Shield/blob/master/mcp_can_dfs.h
 */
#define DEV__CAN__MCP2515__16MHz_1000kBPS_CFG1 (0x00)
#define DEV__CAN__MCP2515__16MHZ_1000kBPS_CFG2 (0xD0)
#define DEV__CAN__MCP2515__16MHZ_1000kBPS_CFG3 (0x82)

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef uint8_t dev__can__mcp2515__reg_bits_t;

typedef uint8_t dev__can__mcp2515__reg_empty_bits_t;

typedef uint8_t dev__can__mcp2515__reg_t;

typedef uint8_t dev__can__mcp2515__cmd_t;

typedef uint8_t dev__can__mcp2515__mask_byte_t;

typedef enum
{
    DEV__CAN__MCP2515__RXF0SIDH_ADDR = 0x00,
    DEV__CAN__MCP2515__RXF0SIDL_ADDR,
    DEV__CAN__MCP2515__RXF0EID8_ADDR,
    DEV__CAN__MCP2515__RXF0EID0_ADDR,
    DEV__CAN__MCP2515__RXF1SIDH_ADDR,
    DEV__CAN__MCP2515__RXF1SIDL_ADDR,
    DEV__CAN__MCP2515__RXF1EID8_ADDR,
    DEV__CAN__MCP2515__RXF1EID0_ADDR,
    DEV__CAN__MCP2515__RXF2SIDH_ADDR,
    DEV__CAN__MCP2515__RXF2SIDL_ADDR,
    DEV__CAN__MCP2515__RXF2EID8_ADDR,
    DEV__CAN__MCP2515__RXF2EID0_ADDR,
    DEV__CAN__MCP2515__BFPCTRL_ADDR,
    DEV__CAN__MCP2515__TXRTSCTRL_ADDR,
    DEV__CAN__MCP2515__CANSTAT_0_ADDR,
    DEV__CAN__MCP2515__CANCTRL_0_ADDR,

    DEV__CAN__MCP2515__RXF3SIDH_ADDR,
    DEV__CAN__MCP2515__RXF3SIDL_ADDR,
    DEV__CAN__MCP2515__RXF3EID8_ADDR,
    DEV__CAN__MCP2515__RXF3EID0_ADDR,
    DEV__CAN__MCP2515__RXF4SIDH_ADDR,
    DEV__CAN__MCP2515__RXF4SIDL_ADDR,
    DEV__CAN__MCP2515__RXF4EID8_ADDR,
    DEV__CAN__MCP2515__RXF4EID0_ADDR,
    DEV__CAN__MCP2515__RXF5SIDH_ADDR,
    DEV__CAN__MCP2515__RXF5SIDL_ADDR,
    DEV__CAN__MCP2515__RXF5EID8_ADDR,
    DEV__CAN__MCP2515__RXF5EID0_ADDR,
    DEV__CAN__MCP2515__TEC_ADDR,
    DEV__CAN__MCP2515__REC_ADDR,
    DEV__CAN__MCP2515__CANSTAT_1_ADDR,
    DEV__CAN__MCP2515__CANCTRL_1_ADDR,

    DEV__CAN__MCP2515__RXM0SIDH_ADDR,
    DEV__CAN__MCP2515__RXM0SIDL_ADDR,
    DEV__CAN__MCP2515__RXM0EID8_ADDR,
    DEV__CAN__MCP2515__RXM0EID0_ADDR,
    DEV__CAN__MCP2515__RXM1SIDH_ADDR,
    DEV__CAN__MCP2515__RXM1SIDL_ADDR,
    DEV__CAN__MCP2515__RXM1EID8_ADDR,
    DEV__CAN__MCP2515__RXM1EID0_ADDR,
    DEV__CAN__MCP2515__CNF3_ADDR,
    DEV__CAN__MCP2515__CNF2_ADDR,
    DEV__CAN__MCP2515__CNF1_ADDR,
    DEV__CAN__MCP2515__CANINTE_ADDR,
    DEV__CAN__MCP2515__CANINTF_ADDR,
    DEV__CAN__MCP2515__EFLG_ADDR,
    DEV__CAN__MCP2515__CANSTAT_2_ADDR,
    DEV__CAN__MCP2515__CANCTRL_2_ADDR,

    DEV__CAN__MCP2515__TXB0CTRL_ADDR,
    DEV__CAN__MCP2515__TXB0SIDH_ADDR,
    DEV__CAN__MCP2515__TXB0SIDL_ADDR,
    DEV__CAN__MCP2515__TXB0EID8_ADDR,
    DEV__CAN__MCP2515__TXB0EID0_ADDR,
    DEV__CAN__MCP2515__TXB0DLC_ADDR,
    DEV__CAN__MCP2515__TXB0D0_ADDR,
    DEV__CAN__MCP2515__TXB0D1_ADDR,
    DEV__CAN__MCP2515__TXB0D2_ADDR,
    DEV__CAN__MCP2515__TXB0D3_ADDR,
    DEV__CAN__MCP2515__TXB0D4_ADDR,
    DEV__CAN__MCP2515__TXB0D5_ADDR,
    DEV__CAN__MCP2515__TXB0D6_ADDR,
    DEV__CAN__MCP2515__TXB0D7_ADDR,
    DEV__CAN__MCP2515__CANSTAT_3_ADDR,
    DEV__CAN__MCP2515__CANCTRL_3_ADDR,

    DEV__CAN__MCP2515__TXB1CTRL_ADDR,
    DEV__CAN__MCP2515__TXB1SIDH_ADDR,
    DEV__CAN__MCP2515__TXB1SIDL_ADDR,
    DEV__CAN__MCP2515__TXB1EID8_ADDR,
    DEV__CAN__MCP2515__TXB1EID0_ADDR,
    DEV__CAN__MCP2515__TXB1DLC_ADDR,
    DEV__CAN__MCP2515__TXB1D0_ADDR,
    DEV__CAN__MCP2515__TXB1D1_ADDR,
    DEV__CAN__MCP2515__TXB1D2_ADDR,
    DEV__CAN__MCP2515__TXB1D3_ADDR,
    DEV__CAN__MCP2515__TXB1D4_ADDR,
    DEV__CAN__MCP2515__TXB1D5_ADDR,
    DEV__CAN__MCP2515__TXB1D6_ADDR,
    DEV__CAN__MCP2515__TXB1D7_ADDR,
    DEV__CAN__MCP2515__CANSTAT_4_ADDR,
    DEV__CAN__MCP2515__CANCTRL_4_ADDR,

    DEV__CAN__MCP2515__TXB2CTRL_ADDR,
    DEV__CAN__MCP2515__TXB2SIDH_ADDR,
    DEV__CAN__MCP2515__TXB2SIDL_ADDR,
    DEV__CAN__MCP2515__TXB2EID8_ADDR,
    DEV__CAN__MCP2515__TXB2EID0_ADDR,
    DEV__CAN__MCP2515__TXB2DLC_ADDR,
    DEV__CAN__MCP2515__TXB2D0_ADDR,
    DEV__CAN__MCP2515__TXB2D1_ADDR,
    DEV__CAN__MCP2515__TXB2D2_ADDR,
    DEV__CAN__MCP2515__TXB2D3_ADDR,
    DEV__CAN__MCP2515__TXB2D4_ADDR,
    DEV__CAN__MCP2515__TXB2D5_ADDR,
    DEV__CAN__MCP2515__TXB2D6_ADDR,
    DEV__CAN__MCP2515__TXB2D7_ADDR,
    DEV__CAN__MCP2515__CANSTAT_5_ADDR,
    DEV__CAN__MCP2515__CANCTRL_5_ADDR,

    DEV__CAN__MCP2515__RXB0CTRL_ADDR,
    DEV__CAN__MCP2515__RXB0SIDH_ADDR,
    DEV__CAN__MCP2515__RXB0SIDL_ADDR,
    DEV__CAN__MCP2515__RXB0EID8_ADDR,
    DEV__CAN__MCP2515__RXB0EID0_ADDR,
    DEV__CAN__MCP2515__RXB0DLC_ADDR,
    DEV__CAN__MCP2515__RXB0D0_ADDR,
    DEV__CAN__MCP2515__RXB0D1_ADDR,
    DEV__CAN__MCP2515__RXB0D2_ADDR,
    DEV__CAN__MCP2515__RXB0D3_ADDR,
    DEV__CAN__MCP2515__RXB0D4_ADDR,
    DEV__CAN__MCP2515__RXB0D5_ADDR,
    DEV__CAN__MCP2515__RXB0D6_ADDR,
    DEV__CAN__MCP2515__RXB0D7_ADDR,
    DEV__CAN__MCP2515__CANSTAT_6_ADDR,
    DEV__CAN__MCP2515__CANCTRL_6_ADDR,

    DEV__CAN__MCP2515__RXB1CTRL_ADDR,
    DEV__CAN__MCP2515__RXB1SIDH_ADDR,
    DEV__CAN__MCP2515__RXB1SIDL_ADDR,
    DEV__CAN__MCP2515__RXB1EID8_ADDR,
    DEV__CAN__MCP2515__RXB1EID0_ADDR,
    DEV__CAN__MCP2515__RXB1DLC_ADDR,
    DEV__CAN__MCP2515__RXB1D0_ADDR,
    DEV__CAN__MCP2515__RXB1D1_ADDR,
    DEV__CAN__MCP2515__RXB1D2_ADDR,
    DEV__CAN__MCP2515__RXB1D3_ADDR,
    DEV__CAN__MCP2515__RXB1D4_ADDR,
    DEV__CAN__MCP2515__RXB1D5_ADDR,
    DEV__CAN__MCP2515__RXB1D6_ADDR,
    DEV__CAN__MCP2515__RXB1D7_ADDR,
    DEV__CAN__MCP2515__CANSTAT_7_ADDR,
    DEV__CAN__MCP2515__CANCTRL__ADDR7
} dev__can__mcp2515__reg_addr_t;

/*
 * CMD
 */

enum
{
    DEV__CAN__MCP2515__CMD_RESET = 0xC0,
    DEV__CAN__MCP2515__CMD_READ = 0x03,
    DEV__CAN__MCP2515__CMD_READ_RX_BUFFER_0_ADDR = 0x90,
    DEV__CAN__MCP2515__CMD_READ_RX_BUFFER_0_DATA = 0x92,
    DEV__CAN__MCP2515__CMD_READ_RX_BUFFER_1_ADDR = 0x94,
    DEV__CAN__MCP2515__CMD_READ_RX_BUFFER_1_DATA = 0x96,
    DEV__CAN__MCP2515__CMD_WRITE = 0x02,
    DEV__CAN__MCP2515__CMD_LOAD_TX_BUFFER_0_ADDR = 0x40,
    DEV__CAN__MCP2515__CMD_LOAD_TX_BUFFER_0_DATA = 0x41,
    DEV__CAN__MCP2515__CMD_LOAD_TX_BUFFER_1_ADDR = 0x42,
    DEV__CAN__MCP2515__CMD_LOAD_TX_BUFFER_1_DATA = 0x43,
    DEV__CAN__MCP2515__CMD_LOAD_TX_BUFFER_2_ADDR = 0x44,
    DEV__CAN__MCP2515__CMD_LOAD_TX_BUFFER_2_DATA = 0x45,
    DEV__CAN__MCP2515__CMD_RTS_TX_BUFFER_0 = 0x81,
    DEV__CAN__MCP2515__CMD_RTS_TX_BUFFER_1 = 0x82,
    DEV__CAN__MCP2515__CMD_RTS_TX_BUFFER_2 = 0x84,
    DEV__CAN__MCP2515__CMD_READ_STATUS = 0xA0,
    DEV__CAN__MCP2515__CMD_RX_STATUS = 0xB0,
    DEV__CAN__MCP2515__CMD_BIT_MODIFY = 0x05
};

/*
 * CMD RX STATUS
 */
typedef enum
{
    DEV__CAN__MCP2515__RX_STATUS_RX_NONE = 0x00,
    DEV__CAN__MCP2515__RX_STATUS_RX_0,
    DEV__CAN__MCP2515__RX_STATUS_RX_1,
    DEV__CAN__MCP2515__RX_STATUS_RX_0_1
} dev__can__mcp2515__rx_status_rx_t;

typedef enum
{
    DEV__CAN__MCP2515__RX_STATUS_STANDARD = 0x00,
    DEV__CAN__MCP2515__RX_STATUS_STANDARD_REMOTE,
    DEV__CAN__MCP2515__RX_STATUS_EXTENDED,
    DEV__CAN__MCP2515__RX_STATUS_EXTENDED_REMOTE
} dev__can__mcp2515__rx_status_type_t;

typedef enum
{
    DEV__CAN__MCP2515__RX_STATUS_MATCH_RXF0 = 0x00,
    DEV__CAN__MCP2515__RX_STATUS_MATCH_RXF1,
    DEV__CAN__MCP2515__RX_STATUS_MATCH_RXF2,
    DEV__CAN__MCP2515__RX_STATUS_MATCH_RXF3,
    DEV__CAN__MCP2515__RX_STATUS_MATCH_RXF4,
    DEV__CAN__MCP2515__RX_STATUS_MATCH_RXF5,
    DEV__CAN__MCP2515__RX_STATUS_MATCH_RXF0_R,
    DEV__CAN__MCP2515__RX_STATUS_MATCH_RXF1_R
} dev__can__mcp2515__rx_status_match_t;

typedef union
{
    struct
    {
        dev__can__mcp2515__rx_status_match_t match : 3;
        dev__can__mcp2515__rx_status_type_t type : 2;
        dev__can__mcp2515__reg_empty_bits_t : 1;
        dev__can__mcp2515__rx_status_rx_t rx : 2;
    };
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__rx_status_t;

/*
 * CMD READ STATUS
 */

typedef union
{
    struct
    {
        dev__can__mcp2515__reg_bits_t rx0if : 1;
        dev__can__mcp2515__reg_bits_t rx1if : 1;
        dev__can__mcp2515__reg_bits_t tx0req : 1;
        dev__can__mcp2515__reg_bits_t tx0if : 1;
        dev__can__mcp2515__reg_bits_t tx1req : 1;
        dev__can__mcp2515__reg_bits_t tx1if : 1;
        dev__can__mcp2515__reg_bits_t tx2req : 1;
        dev__can__mcp2515__reg_bits_t tx2if : 1;
    };

    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__read_status_t;

/*
 * TXBn
 */

typedef struct
{
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__txb_sidh_t;

typedef union
{
    struct
    {
        dev__can__mcp2515__reg_bits_t eid : 2;
        dev__can__mcp2515__reg_empty_bits_t : 1;
        dev__can__mcp2515__reg_bits_t exide : 1;
        dev__can__mcp2515__reg_empty_bits_t : 1;
        dev__can__mcp2515__reg_bits_t sid : 3;
    };

    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__txb_sidl_t;

typedef struct
{
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__txb_eid8_t;

typedef struct
{
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__txb_eid0_t;

typedef union
{
    struct
    {
        dev__can__mcp2515__reg_bits_t dlc : 4;
        dev__can__mcp2515__reg_empty_bits_t : 2;
        dev__can__mcp2515__reg_bits_t rtr : 1;
        dev__can__mcp2515__reg_empty_bits_t : 1;
    };

    uint8_t reg;
} dev__can__mcp2515__txb_dlc_t;

/*
 * TXBCTRL
 */
typedef enum
{
    DEV__CAN__MCP2515__TXBCTRL_LOWEST_PRIORITY = 0x00,
    DEV__CAN__MCP2515__TXBCTRL_LOW_PRIORITY,
    DEV__CAN__MCP2515__TXBCTRL_HIGH_PRIORITY,
    DEV__CAN__MCP2515__TXBCTRL_HIGHEST_PRIORITY
} dev__can__mcp2515__txbctrl_txp_t;

typedef union
{
    struct
    {
        dev__can__mcp2515__txbctrl_txp_t txp : 2;
        dev__can__mcp2515__reg_empty_bits_t : 1;
        dev__can__mcp2515__reg_bits_t txreq : 1;
        dev__can__mcp2515__reg_bits_t txerr : 1;
        dev__can__mcp2515__reg_bits_t mloa : 1;
        dev__can__mcp2515__reg_bits_t abtf : 1;
        dev__can__mcp2515__reg_empty_bits_t : 1;
    };
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__txbnctrl_t;

/*
 * RXBCTRL
 */

typedef enum
{
    DEV__CAN__MCP2515__RXM_FILTERS_ENABLED = 0x00,
    DEV__CAN__MCP2515__RXM_FILTERS_DISABLED = 0x03
} dev__can__mcp2515__rxbctrl_rxm_t;

typedef union
{
    struct
    {
        dev__can__mcp2515__reg_bits_t filhit : 1;
        dev__can__mcp2515__reg_empty_bits_t : 1;
        dev__can__mcp2515__reg_bits_t bukt : 1;
        dev__can__mcp2515__reg_bits_t rxrtr : 1;
        dev__can__mcp2515__reg_empty_bits_t : 1;
        dev__can__mcp2515__rxbctrl_rxm_t rxm : 2;
        dev__can__mcp2515__reg_empty_bits_t : 1;
    };
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__rxb0ctrl_t;

typedef union
{
    struct
    {
        dev__can__mcp2515__reg_bits_t filhit : 3;
        dev__can__mcp2515__reg_bits_t rxrtr : 1;
        dev__can__mcp2515__reg_empty_bits_t : 1;
        dev__can__mcp2515__rxbctrl_rxm_t rxm : 2;
        dev__can__mcp2515__reg_bits_t : 1;
    };
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__rxb1ctrl_t;

/*
 * RXBn
 */

typedef struct
{
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__rxb_sidh_t;

typedef union
{
    struct
    {
        dev__can__mcp2515__reg_bits_t eid : 2;
        dev__can__mcp2515__reg_empty_bits_t : 1;
        dev__can__mcp2515__reg_bits_t ide : 1;
        dev__can__mcp2515__reg_bits_t srr : 1;
        dev__can__mcp2515__reg_bits_t sid : 3;
    };
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__rxb_sidl_t;

typedef struct
{
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__rxb_eid8_t;

typedef struct
{
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__rxb_eid0_t;

typedef union
{
    struct
    {
        dev__can__mcp2515__reg_bits_t dlc : 4;
        dev__can__mcp2515__reg_bits_t res : 2;
        dev__can__mcp2515__reg_bits_t rtr : 1;
        dev__can__mcp2515__reg_empty_bits_t : 1;
    };
    dev__can__mcp2515__reg_t reg;

} dev__can__mcp2515__rxb_dlc_t;

/*
 * RXMn
 */

typedef struct
{
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__rxm_sidh_t;

typedef union
{
    struct
    {
        dev__can__mcp2515__reg_bits_t eid : 2;
        dev__can__mcp2515__reg_empty_bits_t : 3;
        dev__can__mcp2515__reg_bits_t sid : 3;
    };
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__rxm_sidl_t;

typedef struct
{
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__rxm_eid8_t;

typedef struct
{
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__rxm_eid0_t;

/*
 * RXFn
 */

typedef struct
{
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__rxf_sidh_t;

typedef union
{
    struct
    {
        dev__can__mcp2515__reg_bits_t eid : 2;
        dev__can__mcp2515__reg_empty_bits_t : 1;
        dev__can__mcp2515__reg_bits_t exide : 1;
        dev__can__mcp2515__reg_empty_bits_t : 1;
        dev__can__mcp2515__reg_bits_t sid : 3;
    };
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__rxf_sidl_t;

typedef struct
{
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__rxf_eid8_t;

typedef struct
{
    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__rxf_eid0_t;

/*
 * CANINTE
 */

typedef union
{
    struct
    {
        dev__can__mcp2515__reg_bits_t rx0ie : 1;
        dev__can__mcp2515__reg_bits_t rx1ie : 1;
        dev__can__mcp2515__reg_bits_t tx0ie : 1;
        dev__can__mcp2515__reg_bits_t tx1ie : 1;
        dev__can__mcp2515__reg_bits_t tx2ie : 1;
        dev__can__mcp2515__reg_bits_t errie : 1;
        dev__can__mcp2515__reg_bits_t wakie : 1;
        dev__can__mcp2515__reg_bits_t merre : 1;
    };
    uint8_t reg;
} dev__can__mcp2515__caninte_t;

/*
 * CANINTF
 */

typedef union
{
    struct
    {
        dev__can__mcp2515__reg_bits_t rx0if : 1;
        dev__can__mcp2515__reg_bits_t rx1if : 1;
        dev__can__mcp2515__reg_bits_t tx0if : 1;
        dev__can__mcp2515__reg_bits_t tx1if : 1;
        dev__can__mcp2515__reg_bits_t tx2if : 1;
        dev__can__mcp2515__reg_bits_t errif : 1;
        dev__can__mcp2515__reg_bits_t merrf : 1;
    };

    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__canintf_t;

/*
 * CANCTRL
 */
typedef enum
{
    DEV__CAN__MCP2515__CANCTRL_REQOP_NORM = 0x00,
    DEV__CAN__MCP2515__CANCTRL_REQOP_SLEEP,
    DEV__CAN__MCP2515__CANCTRL_REQOP_LOOPBACK,
    DEV__CAN__MCP2515__CANCTRL_REQOP_LISTEN,
    DEV__CAN__MCP2515__CANCTRL_REQOP_CONFIG
} dev__can__mcp2515__canctrl_reqop_t;

typedef union
{
    struct
    {
        dev__can__mcp2515__reg_bits_t clkpre : 2;
        dev__can__mcp2515__reg_bits_t clken : 1;
        dev__can__mcp2515__reg_bits_t osm : 1;
        dev__can__mcp2515__reg_bits_t abat : 1;
        dev__can__mcp2515__canctrl_reqop_t reqop : 3;
    };
    uint8_t reg;
} dev__can__mcp2515__canctrl_t;

/*
 * CANSTAT
 */
typedef enum
{
    DEV__CAN__MCP2515__CANSTAT_OPMOD_NORM = 0x00,
    DEV__CAN__MCP2515__CANSTAT_OPMOD_SLEEP,
    DEV__CAN__MCP2515__CANSTAT_OPMOD_LOOPBACK,
    DEV__CAN__MCP2515__CANSTAT_OPMOD_LISTEN,
    DEV__CAN__MCP2515__CANSTAT_OPMOD_CONFIG
} dev__can__mcp2515__canstat_opmod_t;

typedef enum
{
    DEV__CAN__MCP2515__CANSTAT_ICOD_NONE = 0x00,
    DEV__CAN__MCP2515__CANSTAT_ICOD_ERR,
    DEV__CAN__MCP2515__CANSTAT_ICOD_WAKEUP,
    DEV__CAN__MCP2515__CANSTAT_ICOD_TXB0,
    DEV__CAN__MCP2515__CANSTAT_ICOD_TXB1,
    DEV__CAN__MCP2515__CANSTAT_ICOD_TXB2,
    DEV__CAN__MCP2515__CANSTAT_ICOD_RXB0,
    DEV__CAN__MCP2515__CANSTAT_ICOD_RXB1
} dev__can__mcp2515__canstat_icod_t;

typedef union
{
    struct
    {
        dev__can__mcp2515__reg_empty_bits_t : 1;
        dev__can__mcp2515__canstat_icod_t icod : 3;
        dev__can__mcp2515__reg_empty_bits_t : 1;
        dev__can__mcp2515__canstat_opmod_t opmod : 3;
    } bits;
    uint8_t reg;
} dev__can__mcp2515__canstat_t;

/*
 * EFLG
 */

typedef union
{
    struct
    {
        dev__can__mcp2515__reg_bits_t ewarn : 1;
        dev__can__mcp2515__reg_bits_t rxwar : 1;
        dev__can__mcp2515__reg_bits_t txwar : 1;
        dev__can__mcp2515__reg_bits_t rxep : 1;
        dev__can__mcp2515__reg_bits_t txep : 1;
        dev__can__mcp2515__reg_bits_t txbo : 1;
        dev__can__mcp2515__reg_bits_t rx0ovr : 1;
        dev__can__mcp2515__reg_bits_t rx1ovr : 1;
    };

    dev__can__mcp2515__reg_t reg;
} dev__can__mcp2515__eflg_t;

/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  inlines
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/


#endif //DEV__CAN__MCP2515_REGS_H
