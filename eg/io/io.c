/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  poweroff.c
 *  \brief  ev3dev-c IO example.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"

/*  WARNING!
 *  Please build and install ev3dev-c static library before make this example.
 *  See README.
 */

int main( void )
{
	char s[ 256 ];
	int state;

	if ( ev3_init() < 1 ) return ( 1 );

	if ( ev3_listdir( "/sys/class/leds", s, sizeof( s ))) {
		printf( "leds folder: %s\n", s );
	} else {
		printf( "ERROR: ev3_listdir( leds )\n" );
	}
	if ( ev3_read_int( "/sys/class/leds/ev3:left:red:ev3dev/brightness", &state )) {
		if ( !ev3_write_int( "/sys/class/leds/ev3:left:red:ev3dev/brightness", ( state ) ? 0 : 255 )) {
			printf( "ERROR: ev3_write_int( brightness )\n" );
		}
	} else {
		printf( "ERROR: ev3_read_int( brightness )\n" );
	}
	if ( ev3_listdir( "/sys/class/lego-port", s, sizeof( s ))) {
		printf( "lego-port folder: %s\n", s );
	} else {
		printf( "ERROR: ev3_listdir( lego-port )\n" );
	}
	if ( ev3_listdir( "/sys/class/lego-sensor", s, sizeof( s ))) {
		printf( "lego-sensor folder: %s\n", s );
	} else {
		printf( "ERROR: ev3_listdir( lego-sensor )\n" );
	}
	if ( ev3_listdir( "/sys/class/tacho-motor", s, sizeof( s ))) {
		printf( "tacho-motor folder: %s\n", s );
	} else {
		printf( "ERROR: ev3_listdir( tacho-motor )\n" );
	}
	ev3_uninit();

	return ( 0 );
}
