/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  tacho.c
 *  \brief  ev3dev-c Tacho Motors example.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"

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
	int i;
	uint8_t sn;
	FLAGS_T state;
	char s[ 256 ];

#ifndef __ARM_ARCH_4T__
	/* Disable auto-detection of the brick (you have to set the correct address below) */
	ev3_brick_addr = "192.168.0.204";

#endif
	if ( ev3_init() == -1 ) return ( 1 );

#ifndef __ARM_ARCH_4T__
	printf( "The EV3 brick auto-detection is DISABLED,\nwaiting %s online with plugged tacho...\n", ev3_brick_addr );

#else
	printf( "Waiting tacho is plugged...\n" );

#endif
	while ( ev3_tacho_init() < 1 ) Sleep( 1000 );

	printf( "*** ( EV3 ) Hello! ***\n" );

	printf( "Found tacho motors:\n" );
	for ( i = 0; i < DESC_LIMIT; i++ ) {
		if ( ev3_tacho[ i ].type_inx != TACHO_TYPE__NONE_ ) {
			printf( "  type = %s\n", ev3_tacho_type( ev3_tacho[ i ].type_inx ));
			printf( "  port = %s\n", ev3_tacho_port_name( i, s ));
		}
	}
	if ( ev3_search_tacho( LEGO_EV3_M_MOTOR, &sn, 0 )) {
		int max_speed;

		printf( "LEGO_EV3_M_MOTOR is found, run for 5 sec...\n" );
		get_tacho_max_speed( sn, &max_speed );
		printf("  max_speed = %d\n", max_speed );
		set_tacho_stop_action_inx( sn, TACHO_COAST );
		set_tacho_speed_sp( sn, max_speed * 2 / 3 );
		set_tacho_time_sp( sn, 5000 );
		set_tacho_ramp_up_sp( sn, 2000 );
		set_tacho_ramp_down_sp( sn, 2000 );
		set_tacho_command_inx( sn, TACHO_RUN_TIMED );
		/* Wait tacho stop */
		Sleep( 100 );
		do {
			get_tacho_state_flags( sn, &state );
		} while ( state );
		printf( "run to relative position...\n" );
		set_tacho_speed_sp( sn, max_speed / 2 );
		set_tacho_ramp_up_sp( sn, 0 );
		set_tacho_ramp_down_sp( sn, 0 );
		set_tacho_position_sp( sn, 90 );
		for ( i = 0; i < 8; i++ ) {
			set_tacho_command_inx( sn, TACHO_RUN_TO_REL_POS );
			Sleep( 500 );
		}
	} else {
		printf( "LEGO_EV3_M_MOTOR is NOT found\n" );
	}
	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}
