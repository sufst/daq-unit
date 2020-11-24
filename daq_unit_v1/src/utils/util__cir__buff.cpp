/*************************************************************************//**
* @file util__cir__buff.cpp
* @brief A circular buffer implementation
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
#include "util__cir__buff.h"


/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
static void util__cir__buff__increment_tail_(util__cir__buff_t *buff);
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
* @brief Initialise circular buffer
* @param util__cir__buff_t *buff Circular buffer handle to initialise
* @param void *arr Underlying data array to use as storage
* @param uint8_t len Length of circular buffer in terms of object size
* @param uint16_t objSize Size of object in bytes
* @return None
* @note
*****************************************************************************/
void util__cir__buff__init(util__cir__buff_t *buff, void *arr, uint16_t len, uint16_t objSize)
{
    buff->head = 0;
    buff->tail = 0;
    buff->capacity = len;
    buff->full = false;
    buff->data = (uint8_t *) arr;
    buff->objSize = objSize;
}

/*************************************************************************//**
* @brief Check if there is any objects in circular buffer
* @param util__cir__buff_t *buff Circular buffer handle to check
* @return uint8_t Circular buffer used capacity
* @note
*****************************************************************************/
uint16_t util__cir__buff__available(util__cir__buff_t *buff)
{
    uint16_t availableForWrite = 0;

    if (!buff->full)
    {
        if (buff->head >= buff->tail)
        {
            availableForWrite = buff->head - buff->tail;
        }
        else
        {
            availableForWrite = buff->capacity - buff->tail + buff->head;
        }
    }
    else
    {
        availableForWrite = buff->capacity;
    }

    return availableForWrite;
}

/*************************************************************************//**
* @brief Checks how much many objects can be written to the circular buffer before being full
* @param util__cir__buff_t *buff Circular buffer handle to check
* @return uint8_t space left for objects
* @note
*****************************************************************************/
uint16_t util__cir__buff__available_for_write(util__cir__buff_t *buff)
{
    return buff->capacity - util__cir__buff__available(buff);
}

/*************************************************************************//**
* @brief Returns pointer to circular buffer head for an external function to write to the buffer directly
* @param util__cir__buff_t *buff Circular buffer handle to write to
* @return util__cir__buff__obj Pointer to the head object
* @note
*****************************************************************************/
util__cir__buff__obj util__cir__buff__external_write(util__cir__buff_t *buff)
{
    uint8_t *head = &(buff->data[buff->head]);

    util__cir__buff__increment_head(buff);

    return (util__cir__buff__obj) head;
}

/*************************************************************************//**
* @brief Return pointer to object at the circular buffer tail
* @param util__cir__buff_t *buff Circular buffer handle to peek at
* @return util__cir__buff__obj Pointer to object at buffer tail
* @note
*****************************************************************************/
util__cir__buff__obj util__cir__buff__peek_tail(util__cir__buff_t *buff)
{
    return (util__cir__buff__obj) &(buff->data[buff->tail * buff->objSize]);
}

/*************************************************************************//**
* @brief Return pointer to object at the circular buffer head
* @param util__cir__buff_t *buff Circular buffer handle to peek at
* @return util__cir__buff__obj Pointer to object at buffer head
* @note
*****************************************************************************/
util__cir__buff__obj util__cir__buff__peek_head(util__cir__buff_t *buff)
{
    return (util__cir__buff__obj) &(buff->data[buff->head * buff->objSize]);
}

/*************************************************************************//**
* @brief Reset the circular buffer
* @param util__cir__buff_t *buff Circular buffer handle
* @return None
* @note
*****************************************************************************/
void util__cir__buff__reset(util__cir__buff_t *buff)
{
    buff->head = 0;
    buff->tail = 0;
    buff->full = 0;
}

/*************************************************************************//**
* @brief Increment the circular buffers head
* @param util__cir__buff_t *buff Circular buffer handle
* @return None
* @note
*****************************************************************************/
void util__cir__buff__increment_head(util__cir__buff_t *buff)
{
    if (++buff->head >= buff->capacity)
    {
        buff->head = 0;
    }

    if (buff->head == buff->tail)
    {
        buff->full = true;

        util__cir__buff__increment_tail_(buff);
    }
}

/*************************************************************************//**
* @brief Increment the circular buffers tail
* @param util__cir__buff_t *buff Circular buffer handle
* @return None
* @note
*****************************************************************************/
void util__cir__buff__increment_tail(util__cir__buff_t *buff)
{
    if (++buff->tail >= buff->capacity)
    {
        buff->tail = 0;
    }

    buff->full = false;
}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/
/*************************************************************************//**
* @brief Internal circular buffer tail increment which touch full parameter
* @param util__cir__buff_t *buff Circular buffer handle
* @return None
* @note
*****************************************************************************/
static void util__cir__buff__increment_tail_(util__cir__buff_t *buff)
{
    if (++buff->tail >= buff->capacity)
    {
        buff->tail = 0;
    }
}

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
