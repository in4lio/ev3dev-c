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
	char s[ 256 ], name_port[ 16 ];
	int i;
	uint8_t sn, sn_port;
	uint8_t port = OUTPUT_B;

	printf( "Waiting the EV3 brick online...\n" );
	if ( ev3_init() < 1 ) return ( 1 );

	printf( "*** ( EV3 ) Hello! ***\n" );
	ev3_port_init();

	printf( "Set mode of the EV3 output port (%s)...\n", ev3_port_name( port, EXT_PORT__NONE_, 0, name_port ));
	sn_port = ev3_search_port( port, EXT_PORT__NONE_ );
	set_port_mode_inx( sn_port, OUTPUT_DC_MOTOR );
	if ( get_port_mode( sn_port, s, sizeof( s ))) {
		printf( "%s: %s\n", name_port, s );
	}
	Sleep( 200 );
	ev3_dc_init();

	printf( "Found DC motors:\n" );
	for ( i = 0; i < DESC_LIMIT; i++ ) {
		if ( ev3_dc[ i ].type_inx != DC_TYPE__NONE_ ) {
			printf( "  type = %s\n", ev3_dc_type( ev3_dc[ i ].type_inx ));
			printf( "  port = %s\n", ev3_dc_port_name( i, s ));
		}
	}
	if ( ev3_search_dc_plugged_in( port, EXT_PORT__NONE_, &sn, 0 )) {
		printf( "DC motor is found, run for 5 sec...\n" );
		set_dc_ramp_up_sp( sn, 2000 );
		set_dc_duty_cycle_sp( sn, 100 );
		set_dc_stop_action_inx( sn, DC_COAST );
		set_dc_command_inx( sn, DC_RUN_FOREVER );
		if ( get_dc_state( sn, s, sizeof( s ))) {
			printf( "state: %s\n", s );
		}
		Sleep( 5000 );
		set_dc_command_inx( sn, DC_STOP );
		if ( get_dc_state( sn, s, sizeof( s ))) {
			printf( "state: %s\n", s );
		}
	} else {
		printf( "DC motor is NOT found\n" );
	}
	Sleep( 200 );
	printf( "Reset mode of the EV3 output port...\n" );
	set_port_mode_inx( sn_port, OUTPUT_AUTO );
	if ( get_port_mode( sn_port, s, sizeof( s ))) {
		printf( "%s: %s\n", name_port, s );
	}
	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}
