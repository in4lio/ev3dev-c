/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  servo.c
 *  \brief  ev3dev-c Servo Motors example.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "ev3_servo.h"

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

//////////////////////////////////////////////////
#endif

int main( void )
{
	char s[ 256 ];
	int pos;
	int i;
	uint8_t sn;
	FLAGS_T state;

	printf( "Waiting the EV3 brick online...\n" );
	if ( ev3_init() < 1 ) return ( 1 );

	printf( "*** ( EV3 ) Hello! ***\n" );
	ev3_port_init();
	ev3_servo_init();

	printf( "Found servo motors:\n" );
	for ( i = 0; i < DESC_LIMIT; i++ ) {
		if ( ev3_servo[ i ].type_inx != SERVO_TYPE__NONE_ ) {
			printf( "  type = %s\n", ev3_servo_type( ev3_servo[ i ].type_inx ));
			printf( "  port = %s\n", ev3_servo_port_name( i, s ));
		}
	}
	if ( ev3_search_servo_plugged_in( INPUT_2, SERVO_1, &sn, 0 )) {
		printf( "Servo motor is found, setting position...\n" );
		set_servo_position_sp( sn, 100 );
		set_servo_command_inx( sn, SERVO_RUN );
		do {
			get_servo_state_flags( sn, &state );
		} while ( state );
		if ( get_servo_position_sp( sn, &pos )) {
			printf( "position: %d\n", pos );
		}
		set_servo_position_sp( sn, -100 );
		do {
			get_servo_state_flags( sn, &state );
		} while ( state );
		if ( get_servo_position_sp( sn, &pos )) {
			printf( "position: %d\n", pos );
		}
		set_servo_command_inx( sn, SERVO_FLOAT );
	} else {
		printf( "Servo motor is NOT found\n" );
	}

	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}
