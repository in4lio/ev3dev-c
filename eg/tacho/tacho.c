/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  tacho.c
 *  \brief  ev3dev-c tacho-motors example.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  The MIT License
 */

#include <stdio.h>
#include "ev3.h"
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
	char s[ 256 ];
	int p;
	int i;

#ifndef __ARM_ARCH_4T__
	/* Disable auto-detection of the brick (you have to set the correct address below) */
	ev3_brick_addr = "192.168.0.204";

#endif
	ev3_init();
#ifndef __ARM_ARCH_4T__
	printf( "The EV3 brick auto-detection is DISABLED, waiting %s online...\n", ev3_brick_addr );

#endif
	while ( ev3_tacho_init() == EV3_NONE ) Sleep( 1000 );

	printf( "*** ( EV3 ) Hello! ***\n" );

	printf( "Found tacho-motors:\n" );
	for ( i = 0; i < OUTPUT__COUNT_; i++ ) {
		if ( ev3_tacho[ i ].connected ) {
			printf( "  port = out%d\n", i + 1 );
			if ( get_tacho_type( ev3_tacho[ i ].id, s, sizeof( s ))) {
				printf( "  type = %s\n", s );
			}
		}
	}
	p = ev3_tacho_port( MINITACHO );
	if ( p != EV3_NONE ) {
		uint8_t id = ev3_tacho[ p ].id;

		printf( "MINITACHO is found, run for 5 sec...\n" );
		set_tacho_regulation_mode( id, "off" );
		set_tacho_run_mode( id, "time" );
		set_tacho_stop_mode( id, "brake" );
		set_tacho_duty_cycle_sp( id, 100 );
		set_tacho_time_sp( id, 5000 );
		set_tacho_ramp_up_sp( id, 2000 );
		set_tacho_ramp_down_sp( id, 2000 );
		set_tacho_run( id, true );
	} else {
		printf( "MINITACHO is not found\n" );
	}
	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}
