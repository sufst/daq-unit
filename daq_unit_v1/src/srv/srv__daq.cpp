/*************************************************************************//**
* @file srv__daq.cpp
* @brief DAQ service layer
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
#include "srv__daq.h"

#include "../sys/sys__manager__sensor__handlers.h"
#include "../sys/sys__manager.h"
#include "../sys/sys__datastore.h"

#if SYS__MANAGER__DAMPER_POTS_ENABLED

#include "../dev/dev__damper__pots.h"

#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__LAP_TIMER_ENABLED

#include "../dev/dev__lap__timer.h"

#endif // SYS__MANAGER__LAP_TIMER_ENABLED

#if SYS__MANAGER__SD_ENABLED

#include "../libraries/SdFat/SdFat.h"
#include "../utils/util__cir__buff.h"

#endif // SYS__MANAGER__SD_ENABLED

#if SYS__MANAGER__YAW_SENSOR_ENABLED

#include "../dev/dev__yaw__sensor.h"

#endif // SYS__MANAGER__YAW_SENSOR_ENABLED

#if SYS__MANAGER__FCHMPPLC_ENABLED

#include "../dev/dev__fchmpplc.h"

#endif // #if SYS__MANAGER__FCHMPPLC_ENABLED

#if SYS__MANAGER__BRAKE_PRESS_ENABLED

#include "../dev/dev__brake__pressure.h"

#endif // SYS__MANAGER__BRAKE_PRESS_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED

#include "../dev/dev__ride__height.h"

#endif // SYS__MANAGER_RIDE_HEIGHT_ENABLED

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/
#if SYS__MANAGER__SD_ENABLED

#define SRV__DAQ__SD_BASE_FILE_NAME "DATA"

#endif // SYS__MANAGER__SD_ENABLED

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
#if SYS__MANAGER__LAP_TIMER_ENABLED

typedef struct
{
    bool lapOccurred;
    uint32_t lapTimeMs;
    uint16_t debounceMs;
} srv__daq__lap_timer_obj_t;

#endif // #if SYS__MANAGER__LAP_TIMER_ENABLED

#if SYS__MANAGER__SD_ENABLED

typedef struct
{
    bool enabled;
    SdFat sd;
    SdFile file;
    uint16_t byteCnt;
    util__cir__buff_t txBuff;
} srv__daq__sd_obj_t;

typedef struct
{
    uint8_t block[SRV__DAQ__SD_BYTES_PER_BLOCK_WITH_OVERHEAD];
    uint16_t bytesUsed;
} srv__daq__sd_block_t;

#endif // SYS__MANAGER__SD_ENABLED

#if SYS__MANAGER__DAMPER_POTS_ENABLED

#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__FCHMPPLC_ENABLED

typedef struct
{
    dev__fchmpplc__obj_t dev__fchmpplc__obj;
    util__cir__buff_t blipsCirBuffer;
    uint32_t blipsBuffer[SYS__MANAGER__FCHMPPLC_MAX_SAMPLE_COUNT];
} srv__daq__fchmpplc_obj_t;

#endif // #if SYS__MANAGER__FCHMPPLC_ENABLED

#if SYS__MANAGER__BRAKE_PRESS_ENABLED

#endif // SYS__MANAGER__BRAKE_PRESS_ENABLED
/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
#if SYS__MANAGER__LAP_TIMER_ENABLED

static void srv__daq__lap_timer_handler();

#endif // SYS__MANAGER__LAP_TIMER_ENABLED

#if SYS__MANAGER__SD_ENABLED

static void srv__daq__sd_process();

#endif // SYS__MANAGER__SD_ENABLED

#if SYS__MANAGER__DAMPER_POTS_ENABLED

static void srv__daq__damper_pots_timer_handler();

#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__YAW_SENSOR_ENABLED

static void srv__daq__yaw_sensor_timer_handler();

#endif // SYS__MANAGER__YAW_SENSOR_ENABLED

#if SYS__MANAGER__FCHMPPLC_ENABLED

void srv__daq__fchmpplc_timer_handler(void);

void srv__daq__fchmpplc_handler(void);

#endif // #if SYS__MANAGER__FCHMPPLC_ENABLED

#if SYS__MANAGER__BRAKE_PRESS_ENABLED

void srv__daq__brake_pressure_timer_handler(void);

#endif // SYS__MANAGER__BRAKE_PRESS_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED

static void srv__daq__ride_height_timer_handler();

#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED

/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  global variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/
#if SYS__MANAGER__DAMPER_POTS_ENABLED

static dev__damper__pots__obj_t dev__damper__pots__obj[SYS__MANAGER__DAMPER_POTS_ATTACHED_AMT];

#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__LAP_TIMER_ENABLED

static dev__lap__timer__obj_t dev__lap__timer__obj;

static srv__daq__lap_timer_obj_t srv__daq__lap_timer_obj;

#endif // SYS__MANAGER__LAP_TIMER_ENABLED

#if SYS__MANAGER__SD_ENABLED

static srv__daq__sd_obj_t srv__daq__sd_obj;

static srv__daq__sd_block_t BlockBuff[SRV__DAQ__SD_TX_BLOCK_BUFFER_LEN];

#endif // SYS__MANAGER__SD_ENABLED

#if SYS__MANAGER__YAW_SENSOR_ENABLED

static dev__yaw__sensor__obj_t dev__yaw__sensor__obj;

#endif // SYS__MANAGER__YAW_SENSOR_ENABLED

#if SYS__MANAGER__FCHMPPLC_ENABLED

static srv__daq__fchmpplc_obj_t srv__daq__fchmpplc_obj;

#endif // #if SYS__MANAGER__FCHMPPLC_ENABLED

#if SYS__MANAGER__BRAKE_PRESS_ENABLED

static dev__brake__pressure__obj_t dev__brake__pressure__obj;

#endif // SYS__MANAGER__BRAKE_PRESS_ENABLED

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED

static dev__ride__height__obj_t dev__ride__height__obj;

#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED
/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
#if SYS__MANAGER__DAMPER_POTS_ENABLED

/*************************************************************************//**
* @brief Initialise damper pots
* @param uint16_t ms Damper pots daq frequency
* @param uint8_t *pins Damper pot pins
* @return None
* @note
*****************************************************************************/
void srv__daq__damper_pots_init(uint16_t ms, uint8_t *pins)
{
    for (uint8_t i = 0; i < SYS__MANAGER__DAMPER_POTS_ATTACHED_AMT; i++)
    {
        dev__damper__pots__obj[i].pin = pins[i];
        dev__damper__pots__init(&dev__damper__pots__obj[i]);
    }

    srv__software__timer__register(ms, srv__daq__damper_pots_timer_handler);
}

/*************************************************************************//**
* @brief Damper pots daq handler for capturing damper pots data
* @param None
* @return None
* @note
*****************************************************************************/
static void srv__daq__damper_pots_timer_handler()
{
    uint32_t potData = 0;
    uint8_t baseTag = SYS__DATASTORE__TAG_DAMP_POT_1;
    uint32_t currentMs = millis();

    for (uint8_t i = 0; i < SYS__MANAGER__DAMPER_POTS_ATTACHED_AMT; i++)
    {
        potData = dev__damper__pots__read_pot_uv(&dev__damper__pots__obj[i]);
        sys__manager__sensor__handlers_from_tag[baseTag + i](&potData, &currentMs);
    }
}

#endif // SYS__MANAGER__DAMPER_POTS_ENABLED

#if SYS__MANAGER__LAP_TIMER_ENABLED

/*************************************************************************//**
* @brief Initialise lap timer
* @param uint8_t intPin Lap timer interrupt pin
* @param uint8_t drivePin Lap timer 5V driven pin
* @param uint16_t debounceMs The time between subsequent lap timer triggers
* @return None
* @note
*****************************************************************************/
void srv__daq__lap_timer_init(uint8_t intPin, uint8_t drivePin, uint16_t debounceMs)
{
    dev__lap__timer__obj.intPin = intPin;
    dev__lap__timer__obj.drivePin = drivePin;
    dev__lap__timer__obj.callback = srv__daq__lap_timer_handler;
    srv__daq__lap_timer_obj.debounceMs = debounceMs;

    dev__lap__timer__init(&dev__lap__timer__obj);
}

/*************************************************************************//**
* @brief Change the debounce ms of the lap timer for a valid trigger
* @param uint16_t debounceMs The time between subsequent lap timer triggers
* @return None
* @note
*****************************************************************************/
void srv__daq__lap_timer_set_debounce_ms(uint16_t debounceMs)
{
    srv__daq__lap_timer_obj.debounceMs = debounceMs;
}

#endif // SYS__MANAGER__LAP_TIMER_ENABLED

#if SYS__MANAGER__SD_ENABLED

/*************************************************************************//**
* @brief Initialise sd card
* @param uint8_t csPin Sd card cs pin
* @return srv__daq__state_t SRV__DAQ__ERROR_NONE if successful,
*                           SRV__DAQ__ERROR if failed
* @note
*****************************************************************************/
srv__daq__state_t srv__daq__sd_init(uint8_t csPin)
{
    srv__daq__state_t ret = SRV__DAQ__ERROR_NONE;

    if (!srv__daq__sd_obj.sd.begin(csPin, SPI_FULL_SPEED))
    {
        ret = SRV__DAQ__ERROR;
        goto fail;
    }

    uint8_t sdBaseFileName;
    sdBaseFileName = sizeof(SRV__DAQ__SD_BASE_FILE_NAME) - 1;

    static char fileName[] = SRV__DAQ__SD_BASE_FILE_NAME "00.bin";

    /*
     * Loop until we find an available file name to use DATA##
     */
    while (srv__daq__sd_obj.sd.exists(fileName))
    {
        if (fileName[sdBaseFileName + 1] != '9')
        {
            fileName[sdBaseFileName + 1]++;
        }
        else if (fileName[sdBaseFileName] != '9')
        {
            fileName[sdBaseFileName + 1] = '0';
            fileName[sdBaseFileName]++;
        }
        else
        {

            ret = SRV__DAQ__ERROR;
            goto fail;
        }
    }

    if (!srv__daq__sd_obj.file.open(fileName, O_WRITE | O_CREAT))
    {

        ret = SRV__DAQ__ERROR;
        goto fail;
    }

    util__cir__buff__init(&srv__daq__sd_obj.txBuff, BlockBuff, SRV__DAQ__SD_TX_BLOCK_BUFFER_LEN,
                          sizeof(srv__daq__sd_block_t));

    srv__daq__sd_obj.enabled = true;

    return ret;

    fail:
    return ret;
}

/*************************************************************************//**
* @brief Write tag data to the sd card
* @param uint8_t tag Data tag
* @param void *data Tag data to write
* @param void *timestamp Timestamp of data
* @return None
* @note
*****************************************************************************/
void srv__daq__sd_write_tag_data(uint8_t tag, void *data, void *timestamp)
{
    if (!srv__daq__sd_obj.enabled)
    {
        return;
    }

    uint8_t tagLen = 1;
    uint8_t dataLen = sys__manager__sensor__handlers__tag_length_from_tag[tag];
    uint8_t timestampLen = 4;

    srv__daq__sd_block_t *headBlock;
    headBlock = (srv__daq__sd_block_t *) util__cir__buff__peek_head(&srv__daq__sd_obj.txBuff);

    /*
     * Add the tag data to the head of the current active block
     */
    memcpy(&(headBlock->block[headBlock->bytesUsed]), &tag, tagLen);
    headBlock->bytesUsed++;
    memcpy(&(headBlock->block[headBlock->bytesUsed]), data, dataLen);
    headBlock->bytesUsed += dataLen;
    memcpy(&(headBlock->block[headBlock->bytesUsed]), timestamp, timestampLen);
    headBlock->bytesUsed += timestampLen;

    /*
     * If we have exceeded the wanted block length, then increment the head block
     */
    if (headBlock->bytesUsed >= SRV__DAQ__SD_BYTES_PER_BLOCK)
    {
        util__cir__buff__increment_head(&srv__daq__sd_obj.txBuff);

        headBlock = (srv__daq__sd_block_t *) util__cir__buff__peek_head(&srv__daq__sd_obj.txBuff);

        if (headBlock->bytesUsed != 0)
        {
            headBlock->bytesUsed = 0;
        }
    }
}

/*************************************************************************//**
* @brief Get the current state of the sd
* @param None
* @return uint8_t status 0x01 if enabled, 0x00 if disabled
* @note
*****************************************************************************/
uint8_t srv__daq__get_sd_state()
{
    return srv__daq__sd_obj.enabled;
}

#endif // SYS__MANAGER__SD_ENABLED

#if SYS__MANAGER__YAW_SENSOR_ENABLED

/*************************************************************************//**
* @brief Initialise the yaw sensor
* @param uint16_t intervalMs Interval of yaw sensor readings
* @param uint8_t Pin Analogue pin of the yaw sensor
* @return None
* @note
*****************************************************************************/
void srv__daq__yaw_sensor_init(uint8_t pin, uint16_t intervalMs)
{
    dev__yaw__sensor__obj.pin = pin;

    dev__yaw__sensor__init(&dev__yaw__sensor__obj);

    srv__software__timer__register(intervalMs, srv__daq__yaw_sensor_timer_handler);
}

#endif // SYS__MANAGER__YAW_SENSOR_ENABLED

#if SYS__MANAGER__FCHMPPLC_ENABLED

/*************************************************************************//**
* @brief Initialise fuel flow sensor
* @param uint8_t intPin Interrupt pin of sensor
* @param uint16_t updateMs Sample ms of sensor blips
* @return None
* @note
*****************************************************************************/
void srv__daq__fchmpplc_init(uint8_t intPin, uint16_t updateMs)
{
    srv__daq__fchmpplc_obj.dev__fchmpplc__obj.intPin = intPin;
    srv__daq__fchmpplc_obj.dev__fchmpplc__obj.handler = srv__daq__fchmpplc_handler;

    util__cir__buff__init(&srv__daq__fchmpplc_obj.blipsCirBuffer, srv__daq__fchmpplc_obj.blipsBuffer,
                          SYS__MANAGER__FCHMPPLC_MAX_SAMPLE_COUNT, 4);

    dev__fchmpplc__init(&srv__daq__fchmpplc_obj.dev__fchmpplc__obj);

    srv__software__timer__register(updateMs, srv__daq__fchmpplc_timer_handler);
}

#endif // SYS__MANAGER__FCHMPPLC_ENABLED

#if SYS__MANAGER__BRAKE_PRESS_ENABLED

void srv__daq__brake_pressure_init(uint8_t pin, uint16_t sampleMs)
{
    dev__brake__pressure__obj.pin = pin;

    dev__brake__pressure__init(&dev__brake__pressure__obj);

    srv__software__timer__register(sampleMs, srv__daq__brake_pressure_timer_handler);
}

#endif // SYS__MANAGER__BRAKE_PRESS_ENABLED

/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/
#if SYS__MANAGER__LAP_TIMER_ENABLED

/*************************************************************************//**
* @brief Lap timer interrupt handler
* @param None
* @return None
* @note
*****************************************************************************/
static void srv__daq__lap_timer_handler()
{
    uint32_t currentMs = millis();

    if ((currentMs - srv__daq__lap_timer_obj.lapTimeMs) > srv__daq__lap_timer_obj.debounceMs)
    {
        srv__daq__lap_timer_obj.lapTimeMs = currentMs;

        srv__daq__lap_timer_obj.lapOccurred = true;
    }
}

#endif // SYS__MANAGER__LAP_TIMER_ENABLED

#if SYS__MANAGER__SD_ENABLED

/*************************************************************************//**
* @brief SD process loop checks for any write requests and writes to sd card
* @param None
* @return None
* @note
*****************************************************************************/
static void srv__daq__sd_process()
{
    if (util__cir__buff__available(&srv__daq__sd_obj.txBuff) > 0)
    {
        srv__daq__sd_block_t *block;
        block = (srv__daq__sd_block_t *) util__cir__buff__peek_tail(&srv__daq__sd_obj.txBuff);

        if (!srv__daq__sd_obj.file.write(block->block, block->bytesUsed))
        {
            srv__daq__sd_obj.enabled = false;

            goto fail;
        }

        srv__daq__sd_obj.byteCnt += block->bytesUsed;

        block->bytesUsed = 0;

        util__cir__buff__increment_tail(&srv__daq__sd_obj.txBuff);

        if (srv__daq__sd_obj.byteCnt >= SRV__DAQ__SD_FLUSH_BYTE_COUNT)
        {
            if (!srv__daq__sd_obj.file.sync() || srv__daq__sd_obj.file.getWriteError())
            {
                srv__daq__sd_obj.enabled = false;

                srv__daq__sd_obj.file.clearWriteError();

                goto fail;
            }

            srv__daq__sd_obj.byteCnt = 0;
        }

    }

    fail:
    return;
}

#endif // SYS__MANAGER__SD_ENABLED

/*************************************************************************//**
* @brief DAQ service process loop
* @param None
* @return None
* @note
*****************************************************************************/
void srv__daq__process()
{
#if SYS__MANAGER__SD_ENABLED

    srv__daq__sd_process();

#endif // SYS__MANAGER__SD_ENABLED

#if SYS__MANAGER__LAP_TIMER_ENABLED

    if (srv__daq__lap_timer_obj.lapOccurred)
    {
        sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_LAPTIMER](&srv__daq__lap_timer_obj.lapTimeMs,
                                                                              &srv__daq__lap_timer_obj.lapTimeMs);

        srv__daq__lap_timer_obj.lapOccurred = false;
    }

#endif // SYS__MANAGER__LAP_TIMER_ENABLED
}

#if SYS__MANAGER__YAW_SENSOR_ENABLED

/*************************************************************************//**
* @brief Handles yaw sensor timer events
* @param None
* @return None
* @note
*****************************************************************************/
static void srv__daq__yaw_sensor_timer_handler()
{
    uint32_t yawData = dev__yaw__sensor__read_pot_uv(&dev__yaw__sensor__obj);
    uint32_t currentMs = millis();

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_YAW](&yawData, &currentMs);
}

#endif // SYS__MANAGER__YAW_SENSOR_ENABLED

#if SYS__MANAGER__FCHMPPLC_ENABLED

/*************************************************************************//**
* @brief Handles when the timer for the fchmpplc has elapsed.
* @param None
* @return None
* @note
*****************************************************************************/
void srv__daq__fchmpplc_timer_handler(void)
{
    uint32_t currentMs = millis();

    // Remove any expired entries from buffer
    uint16_t blips = 0;

    while ((blips = util__cir__buff__available(&srv__daq__fchmpplc_obj.blipsCirBuffer)) > 0)
    {
        if (currentMs - *((uint32_t *) util__cir__buff__peek_tail(&srv__daq__fchmpplc_obj.blipsCirBuffer)) >=
            SYS__MANAGER__FCHMPPLC_SAMPLE_TIMEOUT_MS)
        {
            util__cir__buff__increment_tail(&srv__daq__fchmpplc_obj.blipsCirBuffer);
        }
        else
        {
            break;
        }
    }

    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_FUEL_FLOW](&blips, &currentMs);
}

/*************************************************************************//**
* @brief Handles the fchmpplc device layer interrupts.
* @param None
* @return None
* @note
*****************************************************************************/
void srv__daq__fchmpplc_handler(void)
{
    uint32_t currentMs = millis();

    util__cir__buff__write(&srv__daq__fchmpplc_obj.blipsCirBuffer, &currentMs);
}

#endif // #if SYS__MANAGER__FCHMPPLC_ENABLED

#if SYS__MANAGER__BRAKE_PRESS_ENABLED

void srv__daq__brake_pressure_timer_handler(void)
{
    uint32_t currentMs = millis();

    uint32_t pressureVoltage = dev__brake_pressure__read_uv(&dev__brake__pressure__obj);
    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_BRAKE_PRESSURE](&pressureVoltage,
                                                                                &currentMs);

}

#endif

#if SYS__MANAGER__RIDE_HEIGHT_ENABLED

/*************************************************************************//**
* @brief Initialise ride height sensor
* @param uint16_t ms Ride height sensor timer period
* @param uint8_t pin Ride height sensor pin
* @return None
* @note
*****************************************************************************/
void srv__daq__ride_height_init(uint16_t ms, uint8_t pin)
{
    dev__ride__height__obj.pin = pin;
    dev__ride__height__init(&dev__ride__height__obj);

    srv__software__timer__register(ms, srv__daq__ride_height_timer_handler);
}

/*************************************************************************//**
* @brief Ride height sensor daq handler for capturing ride height sensor data
* @param None
* @return None
* @note
*****************************************************************************/
static void srv__daq__ride_height_timer_handler()
{
    uint32_t rideHeightData = 0;
    uint32_t currentMs = millis();

    rideHeightData = dev__ride__height__read_uv(&dev__ride__height__obj);
    sys__manager__sensor__handlers_from_tag[SYS__DATASTORE__TAG_RIDE_HEIGHT](&rideHeightData, &currentMs);
}

#endif // SYS__MANAGER__RIDE_HEIGHT_ENABLED
/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/


