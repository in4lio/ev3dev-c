/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  led.c
 *  \brief  ev3dev-c LEDs example.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  The MIT License
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "ev3.h"
#include "ev3_led.h"
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
	ev3_init();
	printf( "*** ( EV3 ) Hello! ***\n" );

	set_light_blink( LIT_RIGHT, LIT_GREEN, 1000, 500 );
	Sleep( 500 );
	set_light_blink( LIT_RIGHT, LIT_RED, 1000, 500 );

	set_light_blink( LIT_LEFT, LIT_GREEN, 1000, 1000 );
	Sleep( 1500 );
	set_light_blink( LIT_LEFT, LIT_RED, 1000, 1000 );
	Sleep( 7500 );

	set_light( LIT_LEFT, LIT_OFF );
	set_light( LIT_RIGHT, LIT_OFF );
	Sleep( 500 );
	set_light( LIT_LEFT, LIT_RED );
	set_light( LIT_RIGHT, LIT_RED );
	Sleep( 500 );
	set_light( LIT_LEFT, LIT_AMBER );
	set_light( LIT_RIGHT, LIT_AMBER );
	Sleep( 500 );
	set_light( LIT_LEFT, LIT_GREEN );
	set_light( LIT_RIGHT, LIT_GREEN );

	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}
