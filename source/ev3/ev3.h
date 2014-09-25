
/*  ev3.h was generated by yup.py (yupp) 0.7b5
    out of ev3.yu-h at 2014-09-25 18:00
 *//**
 *  \file  ev3.h (ev3.yu-h)
 *  \brief  EV3 file operations.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#ifndef EV3_H
#define EV3_H

#ifdef  EV3_IMPLEMENT
#define EV3_EXT
#define EV3_EXT_INIT( dec, init ) \
	dec = init
#else
#define EV3_EXT extern
#define EV3_EXT_INIT( dec, init ) \
	extern dec
#endif

#ifndef COMMA
#define COMMA   ,
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \defgroup ev3 EV3 file operations
 *  \{
 */

// CLIENT ////////////////////////////////////////
#ifndef __ARM_ARCH_4T__

EV3_EXT_INIT( char *ev3_brick_addr, NULL );
EV3_EXT_INIT( uint16_t ev3_brick_port, 8800 );

//////////////////////////////////////////////////
#endif

#ifndef DEFINE_H
typedef unsigned char byte;
typedef unsigned int dword;

#endif

#define EV3_NONE  -1

EV3_EXT int ev3_init( void );
EV3_EXT void ev3_uninit( void );

EV3_EXT size_t ev3_write_binary( const char *fn, char *data, size_t sz );
EV3_EXT size_t ev3_write( const char *fn, char *value );
EV3_EXT size_t ev3_write_bool( const char *fn, bool value );
EV3_EXT size_t ev3_write_int( const char *fn, int value );
EV3_EXT size_t ev3_write_dword( const char *fn, uint32_t value );
EV3_EXT size_t ev3_write_float( const char *fn, float value );
EV3_EXT size_t ev3_write_char_array( const char *fn, char *value );
EV3_EXT size_t ev3_write_byte_array( const char *fn, uint8_t *value, size_t sz );

EV3_EXT size_t ev3_read_binary( const char *fn, char *buf, size_t sz );
EV3_EXT size_t ev3_read( const char *fn, char *buf, size_t sz );
EV3_EXT size_t ev3_read_bool( const char *fn, bool *buf );
EV3_EXT size_t ev3_read_int( const char *fn, int *buf );
EV3_EXT size_t ev3_read_dword( const char *fn, uint32_t *buf );
EV3_EXT size_t ev3_read_float( const char *fn, float *buf );
EV3_EXT size_t ev3_read_char_array( const char *fn, char *buf, size_t sz );
EV3_EXT size_t ev3_read_byte_array( const char *fn, uint8_t *buf, size_t sz );

EV3_EXT size_t ev3_listdir( const char *fn, char *buf, size_t sz );

EV3_EXT bool ev3_poweroff( void );

/** \} */

#ifdef __cplusplus
}
#endif

#endif

