/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  ev3_pool.h
 *  \brief  ev3dev-c example of wrapping of the library functions.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#pragma once

#include "coroutine.h"
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "ev3_tacho.h"

#define IN1        0x01
#define IN2        0x02
#define IN3        0x04
#define IN4        0x08
#define IN_COUNT   4

#define OUTA       0x01
#define OUTB       0x02
#define OUTC       0x04
#define OUTD       0x08
#define OUT_COUNT  4

extern bool tacho_is_plugged( uint8_t pool );
extern bool tacho_is_running( uint8_t pool );
extern bool tacho_command( uint8_t pool, int command );
extern bool tacho_reset( uint8_t pool );
extern bool tacho_run_forever( uint8_t pool );
extern bool tacho_run_to_rel_pos( uint8_t pool );
extern bool tacho_run_timed( uint8_t pool );
extern bool tacho_stop( uint8_t pool );
extern bool tacho_set_duty_cycle( uint8_t pool, int rate );
extern bool tacho_set_position( uint8_t pool, int pos );
extern bool tacho_set_time( uint8_t pool, int ms );

extern bool sensor_is_plugged( uint8_t pool );
extern uint8_t sensor_search( INX_T type_inx );
extern int sensor_get_value( uint8_t in, uint8_t inx );
extern bool sensor_set_mode( uint8_t pool, int mode );
extern bool ir_set_mode_remote( uint8_t pool );
extern bool ir_set_mode_prox( uint8_t pool );

extern bool brick_init( void );
extern void brick_uninit( void );
extern int brick_keys( void );

extern void sleep_ms( uint32_t ms );
