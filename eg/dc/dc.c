/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  dc.c
 *  \brief  ev3dev-c DC Motors example.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_output.h"
#include "ev3_dc.h"

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
	int i;
	uint8_t sn;
	uint8_t port = OUTPUT_B;

	printf( "Waiting the EV3 brick online...\n" );
	if ( ev3_init() < 1 ) return ( 1 );

	printf( "*** ( EV3 ) Hello! ***\n" );

	printf( "Set mode of the EV3 output port...\n" );
	set_output_mode_inx( port, OUTPUT_RCX_MOTOR );
	if ( get_output_state( port, s, sizeof( s ))) printf( "%s: %s\n", ev3_output_name( port ), s );

	ev3_dc_init();

	printf( "Found DC motors:\n" );
	for ( i = 0; i < DC_DESC__LIMIT_; i++ ) {
		if ( ev3_dc[ i ].type_inx != DC_TYPE__NONE_ ) {
			printf( "  type = %s\n", ev3_dc_type( ev3_dc[ i ].type_inx ));
			printf( "  port = %s\n", ev3_port_name( ev3_dc[ i ].port, ev3_dc[ i ].extport ));
		}
	}
	if ( ev3_search_dc( RCX_MOTOR, &sn, 0 )) {
		printf( "DC motor is found, run for 5 sec...\n" );
		set_dc_ramp_up_ms( sn, 2000 );
		set_dc_duty_cycle( sn, 100 );
		set_dc_command( sn, "run" );
		if ( get_dc_command( sn, s, sizeof( s ))) printf( "command: %s\n", s );
		Sleep( 5000 );
		set_dc_command( sn, "coast" );
		if ( get_dc_command( sn, s, sizeof( s ))) printf( "command: %s\n", s );
	} else {
		printf( "DC motor is NOT found\n" );
	}

	printf( "Reset mode of the EV3 output port...\n" );
	set_output_mode_inx( port, OUTPUT_AUTO );
	if ( get_output_state( port, s, sizeof( s ))) printf( "%s: %s\n", ev3_output_name( port ), s );

	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}
