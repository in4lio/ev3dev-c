/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  light.c
 *  \brief  ev3dev-c LEDs example.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#include <stdio.h>
#include "ev3.h"
#include "ev3_light.h"

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
	printf( "Waiting the EV3 brick online...\n" );
	if ( ev3_init() < 1 ) return ( 1 );

	printf( "*** ( EV3 ) Hello! ***\n" );

	set_light( LIT_LEFT, LIT_OFF );
	set_light( LIT_RIGHT, LIT_OFF );
	Sleep( 500 );

	set_light_blink( LIT_RIGHT, LIT_GREEN, 1000, 500 );
	Sleep( 500 );
	set_light_blink( LIT_RIGHT, LIT_RED, 1000, 500 );

	set_light_blink( LIT_LEFT, LIT_GREEN, 1000, 1000 );
	Sleep( 1500 );
	set_light_blink( LIT_LEFT, LIT_RED, 1000, 1000 );
	Sleep( 7500 );

	set_light( LIT_LEFT, LIT_OFF );
	set_light( LIT_RIGHT, LIT_OFF );
	printf( "LEFT : %s\n", light_color( get_light( LIT_LEFT )));
	printf( "RIGHT: %s\n", light_color( get_light( LIT_RIGHT )));
	Sleep( 500 );
	set_light( LIT_LEFT, LIT_RED );
	set_light( LIT_RIGHT, LIT_RED );
	printf( "LEFT : %s\n", light_color( get_light( LIT_LEFT )));
	printf( "RIGHT: %s\n", light_color( get_light( LIT_RIGHT )));
	Sleep( 500 );
	set_light( LIT_LEFT, LIT_AMBER );
	set_light( LIT_RIGHT, LIT_AMBER );
	printf( "LEFT : %s\n", light_color( get_light( LIT_LEFT )));
	printf( "RIGHT: %s\n", light_color( get_light( LIT_RIGHT )));
	Sleep( 500 );
	set_light( LIT_LEFT, LIT_GREEN );
	set_light( LIT_RIGHT, LIT_GREEN );
	printf( "LEFT : %s\n", light_color( get_light( LIT_LEFT )));
	printf( "RIGHT: %s\n", light_color( get_light( LIT_RIGHT )));

	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}
