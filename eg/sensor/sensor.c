/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  sensor.c
 *  \brief  ev3dev-c Sensors example.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#include <string.h>
#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_sensor.h"

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

//////////////////////////////////////////////////
#endif

const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

static bool _check_pressed( uint8_t sn )
{
	int val;

	if ( sn == SENSOR__NONE_ ) {
		return ( ev3_read_keys(( uint8_t *) &val ) && ( val & EV3_KEY_UP ));
	}
	return ( get_sensor_value( 0, sn, &val ) && ( val != 0 ));
}

int main( void )
{
	char s[ 256 ];
	int val;
	uint32_t n, i, ii;
	uint8_t sn_touch, sn_color, sn_ir;

	printf( "Waiting the EV3 brick online...\n" );
	if ( ev3_init() < 1 ) return ( 1 );

	printf( "*** ( EV3 ) Hello! ***\n" );
	ev3_sensor_init();

	printf( "Found sensors:\n" );
	for ( i = 0; i < DESC_LIMIT; i++ ) {
		if ( ev3_sensor[ i ].type_inx != SENSOR_TYPE__NONE_ ) {
			printf( "  type = %s\n", ev3_sensor_type( ev3_sensor[ i ].type_inx ));
			printf( "  port = %s\n", ev3_sensor_port_name( i, s ));
			if ( get_sensor_mode( i, s, sizeof( s ))) {
				printf( "  mode = %s\n", s );
			}
			if ( get_sensor_num_values( i, &n )) {
				for ( ii = 0; ii < n; ii++ ) {
					if ( get_sensor_value( ii, i, &val )) {
						printf( "  value%d = %d\n", ii, val );
					}
				}
			}
		}
	}
	if ( ev3_search_sensor( LEGO_EV3_IR, &sn_ir, 0 )) {
		printf( "IR sensor is found\n" );
	} else {
		printf( "IR sensor is NOT found\n" );
	}
	if ( ev3_search_sensor( LEGO_EV3_TOUCH, &sn_touch, 0 )) {
		printf( "TOUCH sensor is found, press BUTTON for EXIT...\n" );
	} else {
		printf( "TOUCH sensor is NOT found, press UP on the EV3 brick for EXIT...\n" );
	}
	if ( ev3_search_sensor( LEGO_EV3_COLOR, &sn_color, 0 )) {
		printf( "COLOR sensor is found, reading COLOR...\n" );
		set_sensor_mode( sn_color, "COL-COLOR" );
		for ( ; ; ) {
			if ( !get_sensor_value( 0, sn_color, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
				val = 0;
			}
			printf( "\r(%s)", color[ val ]);
			fflush( stdout );
			if ( _check_pressed( sn_touch )) break;
			Sleep( 200 );
			printf( "\r        " );
			fflush( stdout );
			if ( _check_pressed( sn_touch )) break;
			Sleep( 200 );
		}
	} else {
		printf( "COLOR sensor is NOT found\n" );
		while ( !_check_pressed( sn_touch )) Sleep( 100 );
	}
	ev3_uninit();
	printf( "\n*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}
