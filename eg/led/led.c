/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  led.c
 *  \brief  ev3dev-c RCX LED example.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_output.h"
#include "ev3_led.h"

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
	uint8_t val = 0;

	printf( "Waiting the EV3 brick online...\n" );
	if ( ev3_init() < 1 ) return ( 1 );

	printf( "*** ( EV3 ) Hello! ***\n" );

	printf( "Set mode of the EV3 output port...\n" );
	set_output_mode_inx( OUTPUT_C, OUTPUT_RCX_LED );
	if ( get_output_state( OUTPUT_C, s, sizeof( s ))) printf( "%s: %s\n", ev3_output_name( OUTPUT_C ), s );

	if ( get_led_max_brightness( EV3_LED_OUTC, &val )) printf( "max_brightness: %d\n", val );
	set_led_brightness( EV3_LED_OUTC, val );
	Sleep( 2000 );
	set_led_trigger_inx( EV3_LED_OUTC, TRIGGER_HEARTBEAT );
	if ( get_led_trigger( EV3_LED_OUTC, s, sizeof( s ))) printf( "trigger: %s\n", s );
	Sleep( 5000 );
	set_led_trigger_inx( EV3_LED_OUTC, TRIGGER_NONE );

	printf( "Reset mode of the EV3 output port...\n" );
	set_output_mode_inx( OUTPUT_C, OUTPUT_AUTO );
	if ( get_output_state( OUTPUT_C, s, sizeof( s ))) printf( "%s: %s\n", ev3_output_name( OUTPUT_C ), s );

	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}
