/*************************************************************************//**
* @file util__cir__buff.h
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
  @brief
----------------------------------------------------------------------------*/

#ifndef UTIL__CIR__BUFF_H
#define UTIL__CIR__BUFF_H

/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
#include "Arduino.h"
/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef struct
{
    uint16_t head;
    uint16_t tail;
    bool full;
    uint8_t *data;
    uint16_t capacity;
    uint8_t objSize;
} util__cir__buff_t;

typedef void *util__cir__buff__obj;
/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
void util__cir__buff__init(util__cir__buff_t *buff, void *arr, uint16_t len, uint16_t objSize);

uint16_t util__cir__buff__available(util__cir__buff_t *buff);

uint16_t util__cir__buff__available_for_write(util__cir__buff_t *buff);

util__cir__buff__obj util__cir__buff__external_write(util__cir__buff_t *buff);

util__cir__buff__obj util__cir__buff__peek_tail(util__cir__buff_t *buff);

util__cir__buff__obj util__cir__buff__peek_head(util__cir__buff_t *buff);

void util__cir__buff__reset(util__cir__buff_t *buff);

void util__cir__buff__increment_head(util__cir__buff_t *buff);

void util__cir__buff__increment_tail(util__cir__buff_t *buff);
/*----------------------------------------------------------------------------
  inlines
------------------------------------------------------------------ ----------*/
/*************************************************************************//**
* @brief Return the object at the circular buffer head
* @param util__cir__buff_t *buff Circular buffer handle to read to
* @param util__cir__buff__obj obj Pointer to location to read data to
* @return None
* @note
*****************************************************************************/
inline void util__cir__buff__read(util__cir__buff_t *buff, util__cir__buff__obj obj)
{
    memcpy(obj, &(buff->data[buff->tail * buff->objSize]), buff->objSize);

    if (++buff->tail >= buff->capacity)
    {
        buff->tail = 0;
    }

    buff->full = false;
}

/*************************************************************************//**
* @brief Write object to the circular buffer
* @param util__cir__buff_t *buff Circular buffer handle to write to
* @param util__cir__buff__obj src Object source to write
* @return None
* @note
*****************************************************************************/
inline void util__cir__buff__write(util__cir__buff_t *buff, util__cir__buff__obj src)
{
    memcpy(&(buff->data[buff->head * buff->objSize]), src, buff->objSize);

    if (++buff->head >= buff->capacity)
    {
        buff->head = 0;
    }

    if (buff->head == buff->tail)
    {
        buff->full = true;

        if (++buff->tail >= buff->capacity)
        {
            buff->tail = 0;
        }
    }
}

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif //UTIL__CIR__BUFF_H
