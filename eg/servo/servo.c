/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  servo.c
 *  \brief  ev3dev-c SERVO Motors example.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_input.h"
#include "nxt_input_mux.h"
#include "ev3_sensor.h"
#include "nxt_analog_host.h"
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
	uint8_t port = INPUT_2;

	printf( "Waiting the EV3 brick online...\n" );
	if ( ev3_init() < 1 ) return ( 1 );

	printf( "*** ( EV3 ) Hello! ***\n" );

	printf( "Set mode of the EV3 input port...\n" );
	set_input_mode_inx( port, INPUT_NXT_ANALOG );
	if ( get_input_state( port, s, sizeof( s ))) printf( "%s: %s\n", ev3_input_name( port ), s );

	printf( "Set MS_8CH_SERVO mode of the nxt-analog-host...\n" );
	set_nxt_analog_host_set_sensor( port, INPUT_MUX__NONE_, ( char* ) ev3_sensor_type( MS_8CH_SERVO ));

	Sleep( 200 );
	ev3_servo_init();

	printf( "Found servo motors:\n" );
	for ( i = 0; i < SERVO_DESC__LIMIT_; i++ ) {
		if ( ev3_servo[ i ].type_inx != SERVO_TYPE__NONE_ ) {
			printf( "  type = %s\n", ev3_servo_type( ev3_servo[ i ].type_inx ));
			ev3_servo_port_name( ev3_servo[ i ].port, ev3_servo[ i ].extport, ev3_servo[ i ].addr, s, sizeof( s ));
			printf( "  port = %s\n", s );
		}
	}
	if ( ev3_search_servo_plugged_in( port, INPUT_MUX__NONE_, 1, &sn, 0 )) {
		printf( "Servo motor is found, setting position...\n" );
		set_servo_command( sn, "run" );
		set_servo_position( sn, 100 );
		Sleep( 2000 );
		if ( get_servo_position( sn, &pos )) printf( "position: %d\n", pos );
		set_servo_position( sn, -100 );
		Sleep( 2000 );
		if ( get_servo_position( sn, &pos )) printf( "position: %d\n", pos );
		set_servo_command( sn, "float" );
	} else {
		printf( "Servo motor is NOT found\n" );
	}

	printf( "Reset mode of the EV3 input port...\n" );
	set_input_mode_inx( port, INPUT_AUTO );
	if ( get_input_state( port, s, sizeof( s ))) printf( "%s: %s\n", ev3_input_name( port ), s );

	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}
