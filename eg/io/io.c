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
#include "ev3_output.h"
#include "ev3_input.h"

/*  WARNING!
 *  Please build and install ev3dev-c static library before make this example.
 *  See README.
 */

int main( void )
{
	char s[ 256 ];
	uint8_t i;

	if ( ev3_init() < 1 ) return ( 1 );

	if ( ev3_listdir( "/sys/class/msensor", s, sizeof( s ))) {
		printf( "sensors: %s\n", s );
	}
	if ( ev3_listdir( "/sys/class/tacho-motor", s, sizeof( s ))) {
		printf( "tacho-motors: %s\n", s );
	}
	for ( i = OUTPUT__BASE_; i < OUTPUT__BASE_ + OUTPUT__COUNT_; i++ ) {
		if ( get_output_state( i, s, sizeof( s ))) {
			printf( "%s: %s\n", ev3_output_name( i ), s );
		}
	}
	for ( i = INPUT__BASE_; i < INPUT__BASE_ + INPUT__COUNT_; i++ ) {
		if ( get_input_state( i, s, sizeof( s ))) {
			printf( "%s: %s\n", ev3_input_name( i, EV3_PORT__NONE_ ), s );
		}
	}
	ev3_uninit();

	return ( 0 );
}
