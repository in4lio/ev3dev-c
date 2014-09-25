
/*  ev3_sensor.c was generated by yup.py (yupp) 0.7b5
    out of ev3_sensor.yu-c at 2014-09-25 18:01
 *//**
 *  \file  ev3_sensor.c (ev3_sensor.yu-c)
 *  \brief  EV3 sensors.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define EV3_SENSOR_IMPLEMENT

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "modp_numtoa.h"
#include "ev3.h"
#include "ev3_sensor.h"

/**
 *  \addtogroup ev3_sensor
 *  \{
 */

#define PATH_PREF_LEN  25
#define _ID_SPOT  "///"

#define PATH_BIN_DATA  "/sys/class/msensor/sensor" _ID_SPOT "bin_data"
#define PATH_BIN_DATA_FORMAT  "/sys/class/msensor/sensor" _ID_SPOT "bin_data_format"
#define PATH_DP  "/sys/class/msensor/sensor" _ID_SPOT "dp"
#define PATH_FW_VERSION  "/sys/class/msensor/sensor" _ID_SPOT "fw_version"
#define PATH_I2C_ADDR  "/sys/class/msensor/sensor" _ID_SPOT "i2c_addr"
#define PATH_MODE  "/sys/class/msensor/sensor" _ID_SPOT "mode"
#define PATH_MODES  "/sys/class/msensor/sensor" _ID_SPOT "modes"
#define PATH_NUM_VALUES  "/sys/class/msensor/sensor" _ID_SPOT "num_values"
#define PATH_POLL_MS  "/sys/class/msensor/sensor" _ID_SPOT "poll_ms"
#define PATH_PORT_NAME  "/sys/class/msensor/sensor" _ID_SPOT "port_name"
#define PATH_UNITS  "/sys/class/msensor/sensor" _ID_SPOT "units"
#define PATH_TYPE_ID  "/sys/class/msensor/sensor" _ID_SPOT "type_id"
#define PATH_VALUE0  "/sys/class/msensor/sensor" _ID_SPOT "value0"
#define PATH_VALUE1  "/sys/class/msensor/sensor" _ID_SPOT "value1"
#define PATH_VALUE2  "/sys/class/msensor/sensor" _ID_SPOT "value2"
#define PATH_VALUE3  "/sys/class/msensor/sensor" _ID_SPOT "value3"
#define PATH_VALUE4  "/sys/class/msensor/sensor" _ID_SPOT "value4"
#define PATH_VALUE5  "/sys/class/msensor/sensor" _ID_SPOT "value5"
#define PATH_VALUE6  "/sys/class/msensor/sensor" _ID_SPOT "value6"
#define PATH_VALUE7  "/sys/class/msensor/sensor" _ID_SPOT "value7"

#define PATH_VALUE  "/sys/class/msensor/sensor" _ID_SPOT "value"

size_t get_sensor_bin_data( uint8_t id, byte *buf, size_t sz )
{
	char s[] = PATH_BIN_DATA;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_byte_array( s, buf, sz );
}

size_t set_sensor_bin_data( uint8_t id, byte *value, size_t sz )
{
	char s[] = PATH_BIN_DATA;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_write_byte_array( s, value, sz );
}

size_t get_sensor_bin_data_format( uint8_t id, char *buf, size_t sz )
{
	char s[] = PATH_BIN_DATA_FORMAT;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t get_sensor_dp( uint8_t id, dword *buf )
{
	char s[] = PATH_DP;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_dword( s, buf );
}

size_t get_sensor_fw_version( uint8_t id, char *buf, size_t sz )
{
	char s[] = PATH_FW_VERSION;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t get_sensor_i2c_addr( uint8_t id, int *buf )
{
	char s[] = PATH_I2C_ADDR;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_int( s, buf );
}

size_t get_sensor_mode( uint8_t id, char *buf, size_t sz )
{
	char s[] = PATH_MODE;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t set_sensor_mode( uint8_t id, char *value )
{
	char s[] = PATH_MODE;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_write_char_array( s, value );
}

size_t get_sensor_modes( uint8_t id, char *buf, size_t sz )
{
	char s[] = PATH_MODES;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t get_sensor_num_values( uint8_t id, dword *buf )
{
	char s[] = PATH_NUM_VALUES;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_dword( s, buf );
}

size_t get_sensor_poll_ms( uint8_t id, dword *buf )
{
	char s[] = PATH_POLL_MS;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_dword( s, buf );
}

size_t set_sensor_poll_ms( uint8_t id, dword value )
{
	char s[] = PATH_POLL_MS;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_write_dword( s, value );
}

size_t get_sensor_port_name( uint8_t id, char *buf, size_t sz )
{
	char s[] = PATH_PORT_NAME;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t get_sensor_units( uint8_t id, char *buf, size_t sz )
{
	char s[] = PATH_UNITS;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_char_array( s, buf, sz );
}

size_t get_sensor_type_id( uint8_t id, dword *buf )
{
	char s[] = PATH_TYPE_ID;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_dword( s, buf );
}

size_t get_sensor_value0( uint8_t id, float *buf )
{
	char s[] = PATH_VALUE0;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_float( s, buf );
}

size_t get_sensor_value1( uint8_t id, float *buf )
{
	char s[] = PATH_VALUE1;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_float( s, buf );
}

size_t get_sensor_value2( uint8_t id, float *buf )
{
	char s[] = PATH_VALUE2;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_float( s, buf );
}

size_t get_sensor_value3( uint8_t id, float *buf )
{
	char s[] = PATH_VALUE3;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_float( s, buf );
}

size_t get_sensor_value4( uint8_t id, float *buf )
{
	char s[] = PATH_VALUE4;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_float( s, buf );
}

size_t get_sensor_value5( uint8_t id, float *buf )
{
	char s[] = PATH_VALUE5;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_float( s, buf );
}

size_t get_sensor_value6( uint8_t id, float *buf )
{
	char s[] = PATH_VALUE6;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_float( s, buf );
}

size_t get_sensor_value7( uint8_t id, float *buf )
{
	char s[] = PATH_VALUE7;
	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';

	return ev3_read_float( s, buf );
}

size_t get_sensor_value( uint8_t inx, uint8_t id, int *buf )
{
	char s[] = PATH_VALUE "    ";

	if ( inx > 8 ) return ( 0 );

	*modp_uitoa10( id, s + PATH_PREF_LEN ) = '/';
	modp_uitoa10( inx, s + PATH_PREF_LEN + 3 + 5 );

	return ev3_read_int( s, buf );
}

char *ev3_sensor_type( uint8_t type_id )
{
	switch ( type_id ) {
	case 16:
		return "EV3_TOUCH";
	case 29:
		return "EV3_COLOR";
	case 30:
		return "EV3_ULTRASONIC";
	case 32:
		return "EV3_GYRO";
	case 33:
		return "EV3_INFRARED";

	}
	return "";
}

int ev3_sensor_port( uint8_t type_id )
{
	int i;

	for ( i = 0; i < INPUT__COUNT_; i++ ) {
		if ( ev3_sensor[ i ].connected && ( ev3_sensor[ i ].type_id == type_id )) return ( i );
	}
	return ( EV3_NONE );
}

EV3_SENSOR *ev3_get_sensor( uint8_t port )
{
	return ( ev3_sensor + (( port < INPUT__COUNT_ ) ? port : 0 ));
}

static bool get_str_suffix( const char *prefix, char *s, uint32_t *buf )
{
	char *end;
	uint32_t l = strlen( prefix );

	if ( memcmp( s, prefix, l )) return ( false );
	*buf = strtoul( s + l, &end, 0 );
	if ( *end ) return ( false );

	return ( true );
}

int ev3_sensor_init( void )
{
	char list[ 256 ], s[ 256 ];
	char *p;
	uint32_t id, port;
	uint8_t cnt = 0;

	memset( ev3_sensor, 0, sizeof( ev3_sensor ));

	if ( !ev3_listdir( "/sys/class/msensor", list, sizeof( list ))) return ( EV3_NONE );

	p = strtok( list, " " );
	while ( p ) {
		if ( get_str_suffix( "sensor", p, &id )) {
			if ( get_sensor_port_name( id, s, sizeof( s )) && get_str_suffix( "in", s, &port )) {
				if ( port && ( port <= INPUT__COUNT_ )) {
					ev3_sensor[ --port ].connected = true;
					ev3_sensor[ port ].id = id;
					get_sensor_type_id( id, &ev3_sensor[ port ].type_id );
					cnt++;
				}
			}
		}
		p = strtok( NULL, " " );
	}
	return ( cnt );
}

/** \} */
