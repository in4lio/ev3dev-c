/*                 _ _     _
     ___ ___ ___ _| |_|___| |_
    |   |  _   _|   | |  _   _|
    |  _|_| |___ ___|_|___  |
    |_|                   |_|
 *//**
 *  \file  crc32.h
 *  \brief  Compute the CRC-32.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#ifndef CRC32_H
#define CRC32_H

#include <stdint.h>

extern uint32_t crc32( uint32_t crc, const char *buf, uint32_t len );

#endif /* CRC32_H */
